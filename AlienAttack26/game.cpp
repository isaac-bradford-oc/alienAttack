/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: game.cpp
 * Description: Main game loop and initialization.
 ****************************************/

#include "gameHeader.h"

int main() {
	// Initialize clock at zero
	clock_t previousClock = 0;
	clock_t currentClock = NULL;

	// Seed RNG
	srand((unsigned int)time({}));

	// Setup window and framerate
	RenderWindow window(VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), GAME_NAME);
	window.setFramerateLimit(FRAMERATE);

	// Initialize game score
	unsigned int gameScore = 0u;

	// Initialize Player Ship
	Ship* ship = new Ship(MAX_PLAYER_LIVES);
	int remainingLives = MAX_PLAYER_LIVES;

	// Entity vectors
	vector<Pixie*> alienVector = {};
	vector<Pixie*> shipMissileVector = {};
	vector<Pixie*> alienMissileVector = {};
	vector<Pixie*> lifeIconVector = {};

	// Initial alien setup
	bool isGoingLeft = true;
	bool isChangingDirection = false;
	spawnAlienWave(alienVector, LEVEL_ONE_ALIENS);

	// Background setup (scaled to window)
	Pixie* background = new Pixie(BACKGROUND_TEXTURE_FILE, ZERO, ZERO, BACKGROUND_PIXIE);
	float bgScaleX = static_cast<float>(WINDOW_WIDTH) / background->getTexture()->getSize().x;
	float bgScaleY = static_cast<float>(WINDOW_HEIGHT) / background->getTexture()->getSize().y;
	background->setScale(bgScaleX, bgScaleY);

	// Start screen
	background->draw(window); // Draw background
	ship->draw(window); // Draw ship
	for (Pixie* alien : alienVector) alien->draw(window); // Draw aliens from vector
	window.display(); // Push window

	// Wait to start until first input
	while (const optional event = window.waitEvent()) {
		if (event->is<Event::KeyPressed>()) {
			break;
		}
	}

	while (window.isOpen())	{

		// --- 1. Event Handling ---
		while (const optional event = window.pollEvent()) {
			// Close the game window
			if (event->is<Event::Closed>()) {
				window.close();
			}
			// Capture keystroke
			else if (const auto* keyPressed = event->getIf<Event::KeyPressed>()) { // If key pressed
				// Pause the game
				if (keyPressed->scancode == Keyboard::Scancode::Escape) { // If escape pressed
					while (const optional event = window.waitEvent()) { // Wait for event (in this case, keystroke)
						// Resume the game
						if (event->is<Event::KeyPressed>()) { // If event is keystroke
							break;
						}
					}
				}
				// Shoot missile
				if (keyPressed->scancode == Keyboard::Scancode::Space
					&& static_cast<int>(shipMissileVector.size()) < MAX_PLAYER_MISSILES) { // If space is pressed and missile limit not reached
					Pixie* missile = createMissile(); // Create missile
					missile->setPosition(ship->centerX(*missile), ship->getY()); // Center missile on ship
					shipMissileVector.push_back(missile); // Add missile to the ship missile vector
				}
			}
		}

		// --- 2. Update Phase (Logic) ---
		if (ship->getLives() < remainingLives) {
			if (ship->getLives() == 0) {
				cout << "You lose!" << endl;
				window.close();
			}

			clock_t initialTime = clock() / CLOCKS_PER_SEC;
			while (((clock() / CLOCKS_PER_SEC) - ONE_SECOND) < initialTime) {}

			spawnAlienWave(alienVector);
			alienMissileVector.clear();

			ship->setPosition(SHIP_X, SHIP_Y);
			--remainingLives;
		}


		moveShip(*ship);

		// Update missiles (move and check bounds)
		for (int i = static_cast<int>(shipMissileVector.size()) - 1; i >= 0; --i) {
			// Move missiles
			shipMissileVector[i]->move(ZERO, -MISSILE_DISTANCE);

			// If missile reaches edge of window, erase it
			if (shipMissileVector[i]->getY() < ZERO) {
				delete shipMissileVector[i];
				shipMissileVector.erase(shipMissileVector.begin() + i);
			}
		}

		// End the game if player defeats all aliens
		if (alienVector.empty()) {
			cout << "You win!" << endl;
			window.close();
		}

		// Move alien army and check if any aliens are hit
		for (int i = static_cast<int>(alienVector.size()) - 1; i >= 0; --i) {
			moveAlien(alienVector[i], isGoingLeft, isChangingDirection);

			// Lose a life if an alien reaches below the player
			if (alienVector[i]->getY() > SHIP_Y) {
				ship->loseLife();
				break;
			}

			// Check if any aliens are hit
			for (int j = static_cast<int>(shipMissileVector.size()) - 1; j >= 0; --j) {
				if (collision(alienVector[i], shipMissileVector[j])) {
					// Delete  alien
					delete alienVector[i];
					alienVector.erase(alienVector.begin() + i);

					// Delete missile
					delete shipMissileVector[j];
					shipMissileVector.erase(shipMissileVector.begin() + j);

					// Increase game score
					gameScore += ALIEN_SCORE;

					break; // Alien destroyed, stop checking missiles for it
				}
			}
		}

		// Move aliens down if they are changing direction
		if (isChangingDirection){
			for (Pixie* alien : alienVector) {
				alien->move(ZERO, ALIEN_VERTICAL_DISTANCE);
			}
			isChangingDirection = false;
		}

		// Periodically have random alien fire missile
		currentClock = clock() / CLOCKS_PER_SEC; // Converts cpu clock unit to seconds
		if (((currentClock - ONE_SECOND) - alienMissileSecondsOffset(ALIEN_MISSILE_MAX_TIME_OFFSET)) >= previousClock) { // If >= 1 + offset seconds has passed since last missile
			int randomAlienIdx = rand() % alienVector.size(); // Chooses random alien

			// Create the missile
			Pixie* missile = createMissile();

			float missileX = alienVector[randomAlienIdx]->centerX(*missile);
			float missileY = alienVector[randomAlienIdx]->getY();
			missile->setPosition(missileX, missileY);

			alienMissileVector.push_back(missile);

			// Prepare clock for next loop
			previousClock = currentClock;
		}

		// Moves alien missiles and detects if the player ship was hit
		for (int i = static_cast<int>(alienMissileVector.size()) - 1; i >= 0; --i) {
			alienMissileVector[i]->move(ZERO, MISSILE_DISTANCE); // Move missiles

			// Delete missiles if they reach the edge of the window
			if (alienMissileVector[i]->getY() < ZERO) {
				delete alienMissileVector[i];
				alienMissileVector.erase(alienMissileVector.begin() + i);
			}

			// Lose a life if an alien missile hits the ship
			if (collision(ship, alienMissileVector[i])) {
				ship->loseLife();
			}
		}

		// Add life icons
		while (static_cast<int>(lifeIconVector.size()) < remainingLives) {
			float iconX = static_cast<float>(WINDOW_WIDTH) - ((lifeIconVector.size() + 1) * LIFE_ICON_OFFSET); // Start at right border and place each alien further left
			float iconY = WINDOW_HEIGHT - LIFE_ICON_OFFSET; // Bottom border minus offset
			Pixie* lifeIcon = new Pixie(SHIP_TEXTURE_FILE, iconX, iconY, LIFE_ICON_PIXIE); // Create life icon
			lifeIconVector.push_back(lifeIcon); // Push icon to vector
		}
		
		// Remove life icons
		while (static_cast<int>(lifeIconVector.size()) > remainingLives) {
			lifeIconVector.pop_back();
		}

		// --- 3. Draw Phase (Rendering) ---
		window.clear();
		background->draw(window); // Draw background
		
		// Draw all missile and alien elements from vectors
		for (Pixie* missile : alienMissileVector) missile->draw(window);
		for (Pixie* missile : shipMissileVector) missile->draw(window);
		for (Pixie* alien : alienVector) alien->draw(window);
		for (Pixie* lifeIcon : lifeIconVector) lifeIcon->draw(window);
		
		ship->draw(window); // Draw ship
		window.display();
	}

	// Cleanup remaining memory
	delete ship;
	delete background;
	for (Pixie* missile : alienMissileVector) delete missile;
	for (Pixie* missile : shipMissileVector) delete missile;
	for (Pixie* alien : alienVector) delete alien;

	// Output game score
	cout << "Your score was: " << gameScore << endl;

	return 0;
}

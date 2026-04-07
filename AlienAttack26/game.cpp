/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: game.cpp
 * Description: Main game loop and initialization.
 ****************************************/

#include "gameHeader.h"

/*
* name
* purpose
* input if any
* return value
*/


/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
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
	unsigned int remainingLives = MAX_PLAYER_LIVES;

	// Entity containers
	MissileContainer* shipMissiles = new MissileContainer();
	MissileContainer* alienMissiles = new MissileContainer();
	LifeIconContainer* lifeIcons = new LifeIconContainer(MAX_PLAYER_LIVES);

	// Initial alien setup
	bool isGoingLeft = true;
	bool isChangingDirection = false;
	AlienArmy* alienArmy = new AlienArmy(LEVEL_ONE_ALIENS);

	// Background setup (scaled to window)
	Pixie* background = new Pixie(BACKGROUND_TEXTURE_FILE, ZERO, ZERO, BACKGROUND_PIXIE);
	float bgScaleX = static_cast<float>(WINDOW_WIDTH) / background->getTexture()->getSize().x;
	float bgScaleY = static_cast<float>(WINDOW_HEIGHT) / background->getTexture()->getSize().y;
	background->setScale(bgScaleX, bgScaleY);

	// Start screen
	background->draw(window); // Draw background
	ship->draw(window); // Draw ship
	alienArmy->draw(window); // Draw alien army
	window.display(); // Push window

	// Wait to start until first input
	while (const optional event = window.waitEvent()) {
		if (event->is<Event::KeyPressed>()) {
			break;
		}
	}

	// While the game is running
	while (window.isOpen()) {

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
				// Fire missiles if space key is pressed
				shipMissiles->fire(ship);
			}
		}

		// --- 2. Update Phase (Logic) ---
		// If player lost a life, lose if out of lives, otherwise, pause the game and reset entity positions
		if (ship->getLives() < remainingLives) {
			// End game if out of lives
			if (ship->getLives() == 0u) {
				cout << GAME_LOSE_MESSAGE << endl;
				window.close();
			}

			// Pause game for one second
			clock_t initialTime = clocksPerSecond();
			while ((clocksPerSecond() - ONE_SECOND) < initialTime) {}

			// Reset alien army position and clear missiles
			alienArmy->spawnWave();
			alienMissiles->clear();

			// Reset ship position, clear missiles, and decrement lives variable
			ship->setPosition(SHIP_X, SHIP_Y);
			shipMissiles->clear();
			remainingLives = ship->getLives();
		}

		// Move ship
		ship->move();

		// Move player missiles and erase them if they are off-screen
		shipMissiles->move(ZERO, -MISSILE_DISTANCE);
		shipMissiles->eraseOffScreenMissiles();

		// End the game if player defeats all aliens
		if (alienArmy->empty()) {
			cout << GAME_WIN_MESSAGE << endl;
			window.close();
		}

		// Move alien army
		alienArmy->move(isGoingLeft, isChangingDirection);

		// Lose a life if aliens reach player
		if (alienArmy->below(SHIP_Y)) {
			ship->loseLife();
		}

		// Check if any aliens are hit
		if (shipMissiles->collision(alienArmy)) {
			// Erase hit aliens
			alienArmy->eraseHitAliens();

			// Erase hit missiles
			shipMissiles->eraseHitMissiles();

			// Increment game score
			gameScore += ALIEN_SCORE;
		}

		// Move aliens down if they are changing direction
		if (isChangingDirection) {
			alienArmy->move(ZERO, ALIEN_VERTICAL_DISTANCE);
			isChangingDirection = false;
		}

		// Periodically have random alien fire missile
		currentClock = clocksPerSecond(); // Converts cpu clock unit to seconds
		if (((currentClock - ONE_SECOND) - alienMissileSecondsOffset(ALIEN_MISSILE_MAX_SECONDS_OFFSET)) >= previousClock) { // If >= 1 + offset seconds has passed since last missile
			// Get a random alien
			Pixie* randomAlien = alienArmy->getRandomAlien();

			// Create the missile
			alienMissiles->createMissile(randomAlien);

			// Prepare clock for next loop
			previousClock = currentClock;
		}

		// Move alien missiles and erase them if they are off-screen
		alienMissiles->move(ZERO, MISSILE_DISTANCE);
		alienMissiles->eraseOffScreenMissiles();

		// If the player gets hit, lose a life
		if (alienMissiles->collision(ship)) {
			ship->loseLife();
		}

		// Remove life icon if player died
		if (lifeIcons->getLives() > ship->getLives()) {
			lifeIcons->loseLife();
		}

		// --- 3. Draw Phase (Rendering) ---
		window.clear(); // Clear the canvas
		background->draw(window); // Draw background
		
		// Draw all missile and life icon elements from vectors
		alienMissiles->draw(window); // Draw alien missiles
		shipMissiles->draw(window); // Draw player missiles
		lifeIcons->draw(window); // Draw life icons
		
		alienArmy->draw(window); // Draw alien army
		ship->draw(window); // Draw ship
		window.display(); // Push window
	}

	// Cleanup remaining memory
	delete ship; // Delete player ship
	delete alienArmy; // Delete alien army
	delete background; // Delete background
	delete alienMissiles; // Delete alien missiles
	delete shipMissiles; // Delete player missiles
	delete lifeIcons; // Delete life icons

	// Output game score
	cout << GAME_SCORE_MESSAGE << gameScore << endl;

	return 0;
}

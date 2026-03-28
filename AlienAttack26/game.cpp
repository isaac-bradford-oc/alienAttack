#include "gameHeader.h"
/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: game.cpp
 * Description: Main game loop and initialization.
 ****************************************/

int main() {
	// Initialize clock at zero
	clock_t prevClock = 0;
	clock_t currClock = NULL;

	// Seed RNG
	srand((unsigned int)time({}));

	// Setup window and framerate
	sf::RenderWindow window(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Aliens!");
	window.setFramerateLimit(FRAMERATE);

	// Initialize Player Ship
	Pixie* ship = new Pixie("ship.png", SHIP_X, SHIP_Y, PLAYER_SHIP_PIXIE);
	ship->setScale(SCALE, SCALE);

	// Entity vectors
	std::vector<Pixie*> shipMissileVector = {};
	std::vector<Pixie*> alienMissileVector = {};
	std::vector<Pixie*> alienVector = {};

	// Initial Alien setup
	bool isGoingLeft = true;
	bool isChangingDirection = false;
	spawnAlienWave(alienVector, 4, 6);

	// Background setup (scaled to window)
	Pixie* background = new Pixie("stars.jpg", ZERO, ZERO, BACKGROUND_PIXIE);
	float bgScaleX = (float)WINDOW_WIDTH / background->getTexture()->getSize().x;
	float bgScaleY = (float)WINDOW_HEIGHT / background->getTexture()->getSize().y;
	background->setScale(bgScaleX, bgScaleY);

	while (window.isOpen())	{

		// --- 1. Event Handling ---
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					// DOESN'T WORK YET
					while (keyPressed == nullptr) {
						std::cout << "yes";
					}
				}
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space
					&& (int)shipMissileVector.size() < MAX_PLAYER_MISSILES)	{
					Pixie* missile = createMissile();
					missile->setPosition(ship->centerX(*missile), ship->getY());
					shipMissileVector.push_back(missile);
				}   
			}
		}

		// --- 2. Update Phase (Logic) ---
		moveShip(*ship);

		// Update missiles (move and check bounds)
		for (int i = (int)shipMissileVector.size() - 1; i >= 0; --i) {
			shipMissileVector[i]->move(ZERO, -MISSILE_DISTANCE);

			if (shipMissileVector[i]->getY() < ZERO) {
				delete shipMissileVector[i];
				shipMissileVector.erase(shipMissileVector.begin() + i);
			}
		}

		// Update aliens and check collisions
		if (alienVector.empty()) {
			std::cout << "You win!" << std::endl;
			exit(0);
		}

		for (int i = (int)alienVector.size() - 1; i >= 0; --i) {
			moveAlien(alienVector[i], isGoingLeft, isChangingDirection);

			if (alienVector[i]->getY() > SHIP_Y) {
				exit(0);
			}

			for (int j = (int)shipMissileVector.size() - 1; j >= 0; --j) {
				if (collision(alienVector[i], shipMissileVector[j])) {
					delete alienVector[i];
					alienVector.erase(alienVector.begin() + i);

					delete shipMissileVector[j];
					shipMissileVector.erase(shipMissileVector.begin() + j);

					break; // Alien destroyed, stop checking missiles for it
				}
			}
		}

		// Move aliens down if they are changing direction
		if (isChangingDirection){
			for (Pixie* alien : alienVector) alien->move(ZERO, ALIEN_VERTICAL_DISTANCE);
			isChangingDirection = false;
		}

		// Periodically have random alien fire missile
		currClock = clock() / CLOCKS_PER_SEC;
		if (((currClock - 1) - ((rand() % 30 + 1) / 10)) >= prevClock) {
			int randomAlienIdx = rand() % (alienVector.size() - 1);

			Pixie* missile = createMissile();
			missile->setPosition(alienVector[randomAlienIdx]->centerX(*missile), alienVector[randomAlienIdx]->getY());
			alienMissileVector.push_back(missile);

			prevClock = currClock;
		}

		for (int i = (int)alienMissileVector.size() - 1; i >= 0; --i) {
			alienMissileVector[i]->move(ZERO, MISSILE_DISTANCE);

			if (alienMissileVector[i]->getY() < ZERO) {
				delete alienMissileVector[i];
				alienMissileVector.erase(alienMissileVector.begin() + i);
			}

			if (collision(ship, alienMissileVector[i])) {
					delete ship;

					delete alienMissileVector[i];
					alienMissileVector.erase(alienMissileVector.begin() + i);

					exit(0);
			}
		}

		// --- 3. Draw Phase (Rendering) ---
		window.clear();
		background->draw(window);
		
		for (Pixie* missile : shipMissileVector) missile->draw(window);
		for (Pixie* missile : alienMissileVector) missile->draw(window);
		for (Pixie* alien : alienVector) alien->draw(window);
		
		ship->draw(window);
		window.display();
	}

	// Cleanup remaining memory
	delete ship;
	delete background;
	for (Pixie* missile : shipMissileVector) delete missile;
	for (Pixie* missile : alienMissileVector) delete missile;
	for (Pixie* alien : alienVector) delete alien;

	return 0;
}

/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: AlienArmy.cpp
 * Description: This file contains the AlienArmy class functions. 
 ****************************************/

#include "gameHeader.h"

// Draws the Pixie's sprite on screen 
void AlienArmy::draw(RenderWindow& window) {
	for (Pixie* alien : alienVector) { 
		alien->draw(window);
	}
}

// Moves aliens by passed x and y values
void AlienArmy::move(float x, float y) {
	for (Pixie* alien : alienVector) {
		alien->move(x, y);
	}
}

// Create a new alien object
Pixie* AlienArmy::createAlien(float alienStartingX, float alienStartingY) {
	Pixie* alien = new Pixie(ALIEN_TEXTURE_FILE, alienStartingX, alienStartingY, ALIEN_PIXIE);
	return alien;
}

// Checks if any alien in army is below passed position
bool AlienArmy::below(float position) {
	bool isBelow = false;
	for (Pixie* alien : alienVector) {
		isBelow = alien->getY() > position;
		break;
	}
	
	return isBelow;
}

// Returns a random alien from vector
Pixie* AlienArmy::getRandomAlien() {
	int randomAlienIdx = rand() % getNumAliens(); // Chooses random alien
	Pixie* randomAlien = alienVector[randomAlienIdx];
	return randomAlien;
}

bool AlienArmy::collision(Pixie* missile) {
	bool collision = false;

	for (Pixie* alien : alienVector) {
		// Missile and victim bounds 
		FloatRect missileBounds = missile->getSprite()->getGlobalBounds();
		FloatRect alienBounds = alien->getSprite()->getGlobalBounds();

		// If missile hits victim, return true
		if (missileBounds.findIntersection(alienBounds)) {
			collision = true;

			// Flag missile and victim as "hit"
			missile->hit();
			alien->hit();
		}
	}

	return collision;
}

// Delete and erase any hit aliens
void AlienArmy::eraseHitAliens() {
	// Iterate through vector
	for (auto iter = alienVector.begin(); iter != alienVector.end();) {
		// If hit, erase alien
		if ((*iter)->isHit()) {
			delete *iter;
			iter = alienVector.erase(iter);
		}
		else {
			++iter;
		}
	}
}

// Moves aliens and changes their direction if one hits a border
void AlienArmy::move(bool& isGoingLeft, bool& isChangingDirection) {
	for (Pixie* alien : alienVector) {
		// Gets width of alien sprite
		float alienWidth = alien->getSprite()->getGlobalBounds().size.x;

		// If alien hits left border, change direction
		if (alien->getX() == ZERO) {
			isGoingLeft = false;
			isChangingDirection = true;
		}
		// If alien hits right border, change direction
		else if (alien->getX() == WINDOW_WIDTH - alienWidth) {
			isGoingLeft = true;
			isChangingDirection = true;
		}

		// If alien is going left, move left
		if (isGoingLeft == true) {
			alien->move(-ALIEN_HORIZONTAL_DISTANCE, ZERO);
		}
		// If alien is going right, move right 
		else {
			alien->move(ALIEN_HORIZONTAL_DISTANCE, ZERO);
		}
	}
}

// Spawn an alien wave based on passed quantity
void AlienArmy::spawnWave(unsigned int numAliens) {
	// Calculate rows, columns, and starting coordinates
	const int rows = static_cast<int>(floor(sqrt(numAliens)));
	const int cols = static_cast<int>(ceil(numAliens / rows));
	const float alienStartingX = ALIEN_X - (((rows - 1) * ALIEN_X_OFFSET) / 2); // Start at middle and subtract half of total distance
	const float alienStartingY = ALIEN_Y - (((cols - 1) * ALIEN_Y_OFFSET) / 2); // Start at middle and subtract half of total distance

	// Iterate through rows and columns, incrementing coordinates and spawning aliens
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
             float x = alienStartingX + (r * ALIEN_X_OFFSET); // 80 pixels apart
			 float y = alienStartingY + (c * ALIEN_Y_OFFSET);
             alienVector.push_back(createAlien(x, y));
		}
	}

	// Spawn remaining aliens under the rest of the army
	int remainingAliens = numAliens - (rows * cols);

	if (remainingAliens > 0) {
		float x = alienStartingX + ((rows - remainingAliens) * (ALIEN_X_OFFSET / 2)); // Start at left and add extra distance for each remaining alien
		float y = alienStartingY + ((cols) * ALIEN_Y_OFFSET); // Go down one more row

		// Spawn aliens and increment x
		for (int pos = 0; pos < remainingAliens; ++pos) {
			alienVector.push_back(createAlien(x, y));
			x += ALIEN_X_OFFSET;
		}
	}
}

// Spawns alien wave based on size of passed vector
void AlienArmy::spawnWave() {
	// Current size of vector
	unsigned int alienVectorSize = static_cast<unsigned int>(alienVector.size());
	
	// If the vector is empty, clear it and create a new wave
	if (!alienVector.empty()) {
		alienVector.clear();
		spawnWave(alienVectorSize);
	}
}

// Constructor spawns wave based on passed number of aliens
AlienArmy::AlienArmy(unsigned int numAliens) {
	spawnWave(numAliens);
}

// Destructor
AlienArmy::~AlienArmy() {
	for (Pixie* alien : alienVector) {
		delete alien;
	}
}

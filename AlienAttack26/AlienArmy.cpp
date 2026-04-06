#include "AlienArmy.h"

// Draws the Pixie's sprite on screen 
void AlienArmy::draw(RenderWindow& window) {
	for (Pixie* alien : alienVector) { alien->draw(window); }
}

// Moves alien and changes direction if it hits a border
void AlienArmy::moveAlien(Pixie* alien, bool& isGoingLeft, bool& isChangingDirection) {
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

AlienArmy::AlienArmy(unsigned int numAliens) {
	setNumAliens(numAliens);
	spawnAlienWave(alienVector, numAliens);
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


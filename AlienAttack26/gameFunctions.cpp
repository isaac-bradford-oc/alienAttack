/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: gameFunctions.cpp
 * Description: This file contains the functions for the game.
 ****************************************/

#include "gameHeader.h"

Pixie* createAlien(float alienStartingX, float alienStartingY) {
	Pixie* alien = new Pixie(ALIEN_TEXTURE_FILE, alienStartingX, alienStartingY, ALIEN_PIXIE);
	return alien;
}

Pixie* createMissile() {
	Pixie* missile = new Pixie(MISSILE_TEXTURE_FILE, ZERO, ZERO, PLAYER_MISSILE_PIXIE);
	return missile;
}

void spawnAlienWave(vector<Pixie*>& alienVector, int numAliens) {
	// Calculate rows, columns, and starting coordinates
	const int rows = static_cast<int>(floor(sqrt(numAliens)));
	const int cols = static_cast<int>(ceil(numAliens / rows));
	const float alienStartingX = ALIEN_X - (((rows - 1) * 80) / 2); // Start at middle and subtract half of total distance
	const float alienStartingY = ALIEN_Y - (((cols - 1) * 60) / 2); // Start at middle and subtract half of total distance

	// Iterate through rows and columns, incrementing coordinates and spawning aliens
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
             float x = alienStartingX + (r * 80); // 80 pixels apart
			 float y = alienStartingY + (c * 60);
             alienVector.push_back(createAlien(x, y));
		}
	}

	// Spawn remaining aliens under the rest of the army
	int remainingAliens = numAliens - (rows * cols);

	if (remainingAliens > 0) {
		float x = alienStartingX + ((rows - remainingAliens) * (80 / 2)); // Start at left and add extra distance for each remaining alien
		float y = alienStartingY + ((cols) * 60); // Go down one more row

		// Spawn aliens and increment x
		for (int pos = 0; pos < remainingAliens; ++pos) {
			alienVector.push_back(createAlien(x, y));
			x += 80;
		}
	}
}

void spawnAlienWave(vector<Pixie*>& alienVector) {
	int alienVectorSize = static_cast<int>(alienVector.size());
	
	if (!alienVector.empty()) {
		alienVector.clear();
		spawnAlienWave(alienVector, alienVectorSize);
	}
}

void moveShip(Pixie& ship)
{
	/*
	 *  This first If-then-else-if Block handles 
	 */
	if (Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		// left arrow is pressed: move our ship.left 5 pixels ( this is -5 pixels to go left)
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		ship.move(-SHIP_DISTANCE, 0);
	}
	else if (Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		// right arrow is pressed: move our ship.right 5 pixels
		ship.move(SHIP_DISTANCE, 0);
	}

	int locationX = static_cast<int>(ship.getX());
	int locationY = static_cast<int>(ship.getY());
}

void moveAlien(Pixie* alien, bool& isGoingLeft, bool& isChangingDirection) {
	float alienWidth = alien->getSprite()->getGlobalBounds().size.x;

	if (alien->getX() == ZERO) {
		isGoingLeft = false;
		isChangingDirection = true;
	}
	else if (alien->getX() == WINDOW_WIDTH - alienWidth) {
		isGoingLeft = true;
		isChangingDirection = true;
	}

	if (isGoingLeft == true) {
		alien->move(-ALIEN_HORIZONTAL_DISTANCE, ZERO);
	}
	else {
		alien->move(ALIEN_HORIZONTAL_DISTANCE, ZERO);
	}
}

bool collision(Pixie* victimOfMissile, Pixie* missile) {
	bool isHit = false;
	FloatRect alienBounds = victimOfMissile->getSprite()->getGlobalBounds();
	FloatRect missileBounds = missile->getSprite()->getGlobalBounds();

	if (alienBounds.findIntersection(missileBounds)) {
		cout << "Hit!" << std::endl;
		isHit = true;
	}

	return isHit;
}

int secondsOffset(int seconds) {
	seconds *= 10;
	return ((rand() % seconds + 1) / 10);
}

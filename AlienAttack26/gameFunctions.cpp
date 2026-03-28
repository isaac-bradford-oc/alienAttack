#include "gameHeader.h"
/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: gameFunctions.cpp
 * Description: This file contains the functions for the game.
 ****************************************/

void moveShip(Pixie& ship)
{
	/*
	 *  This first If-then-else-if Block handles 
	 */
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		// left arrow is pressed: move our ship.left 5 pixels ( this is -5 pixels to go left)
		// 2nd parm is y direction. We don't want to move up/down, so it's zero.
		ship.move(-SHIP_DISTANCE, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		// right arrow is pressed: move our ship.right 5 pixels
		ship.move(SHIP_DISTANCE, 0);
	}

	int locationX = static_cast<int>(ship.getX());
	int locationY = static_cast<int>(ship.getY());
}

Pixie* createMissile() {
	Pixie* missile = new Pixie("missile.bmp", ZERO, ZERO, PLAYER_MISSILE_PIXIE);
	return missile;
}

Pixie* createAlien(float alienX, float alienY) {
	Pixie* alien = new Pixie("alien.bmp", alienX, alienY, ALIEN_PIXIE);
	return alien;
}

bool collision(Pixie* victimOfMissile, Pixie* missile) {
	bool isHit = false;
	sf::FloatRect alienBounds = victimOfMissile->getSprite()->getGlobalBounds();
	sf::FloatRect missileBounds = missile->getSprite()->getGlobalBounds();

	if (alienBounds.findIntersection(missileBounds)) {
		std::cout << "Hit!" << std::endl;
		isHit = true;
	}

	return isHit;
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

void spawnAlienWave(std::vector<Pixie*>& alienVector, int rows, int cols) {
	if (rows % 2 == 1) { ++rows; }
	if (cols % 2 == 1) { ++cols; }
	rows /= 2;
	cols /= 2;
	for (int r = -rows; r < rows; ++r) {
		for (int c = -cols; c < cols; ++c) {
             float x = ALIEN_STARTING_X + (c * 80); // 80 pixels apart
             float y = ALIEN_STARTING_Y + (r * 60);
             alienVector.push_back(createAlien(x, y));
		}
	}
}
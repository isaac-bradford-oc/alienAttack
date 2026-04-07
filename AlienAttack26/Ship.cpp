/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: Ship.cpp
 * Description: This file contains the Ship class functions. 
 ****************************************/

#include "gameHeader.h"

// Move ship based on which key is pressed
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
void Ship::move()
{
	// If left key is pressed
	if (Keyboard::isKeyPressed(Keyboard::Key::Left))
	{
		// Move ship left
		Pixie::move(-SHIP_DISTANCE, ZERO);
	}
	// If right key is pressed
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right))
	{
		// Move ship right
		Pixie::move(SHIP_DISTANCE, ZERO);
	}
}

// Checks for ship collision with missile
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
bool Ship::collision(Pixie* missile) {
	bool collision = false;

	// Missile and victim bounds 
	FloatRect missileBounds = missile->getSprite()->getGlobalBounds();
	FloatRect shipBounds = this->getSprite()->getGlobalBounds();

	// If missile hits victim, return true
	if (missileBounds.findIntersection(shipBounds)) {
		collision = true;

		// Flag missile and victim as "hit"
		missile->hit();
		this->hit();
	}

	return collision;
}

// Decrement lives and reset ship position
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
void Ship::loseLife() {
	--lives;
	setPosition(SHIP_OOB, SHIP_OOB);
}

// Default constructor
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
Ship::Ship(unsigned int lives) {
	setLives(lives);
	setTextureSourceFile(SHIP_TEXTURE_FILE);
	setSprite(getTexture());
	setScale(SCALE, SCALE);
	setPosition(SHIP_X, SHIP_Y);
	setID();
	setType(SHIP_PIXIE);
}
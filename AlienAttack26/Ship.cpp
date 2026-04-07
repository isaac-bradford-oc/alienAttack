/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: Ship.cpp
 * Description: This file contains the Ship class functions. 
 ****************************************/

#include "gameHeader.h"

/*
 * Name: Ship::move
 * Arg(s): ()
 * Returns: void
 *
 * Move ship based on which key is pressed
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

/*
 * Name: Ship::collision
 * Arg(s): Pixie* missile
 * Returns: bool
 *
 * Checks for ship collision with missile
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

/*
 * Name: Ship::loseLife
 * Arg(s): ()
 * Returns: void
 *
 * Decrement lives and reset ship position
 */
void Ship::loseLife() {
	--lives;
	setPosition(SHIP_OOB, SHIP_OOB);
}

/*
 * Name: Ship::Ship
 * Arg(s): unsigned int lives
 * Returns: N/A
 *
 * Default constructor
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
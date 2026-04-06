/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: gameFunctions.cpp
 * Description: This file contains the functions for the game.
 ****************************************/

#include "gameHeader.h"

// Create a new alien object
Pixie* createAlien(float alienStartingX, float alienStartingY) {
	Pixie* alien = new Pixie(ALIEN_TEXTURE_FILE, alienStartingX, alienStartingY, ALIEN_PIXIE);
	return alien;
}

// Create a new missile object
Pixie* createMissile() {
	Pixie* missile = new Pixie(MISSILE_TEXTURE_FILE, ZERO, ZERO, PLAYER_MISSILE_PIXIE);
	return missile;
}

// Move ship based on which key is pressed
void moveShip(Pixie& ship)
{
	// If left key is pressed
	if (Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		// Move ship left
		ship.move(-SHIP_DISTANCE, ZERO);
	}
	// If right key is pressed
	else if (Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		// Move ship right
		ship.move(SHIP_DISTANCE, ZERO);
	}
}

// Moves alien and changes direction if it hits a border
void moveAlien(Pixie* alien, bool& isGoingLeft, bool& isChangingDirection) {
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

// Check for collion between two objects
bool collision(Pixie* victimOfMissile, Pixie* missile) {
	bool isHit = false;
	FloatRect victimBounds = victimOfMissile->getSprite()->getGlobalBounds();
	FloatRect missileBounds = missile->getSprite()->getGlobalBounds();

	// If missile hits victim, return true
	if (victimBounds.findIntersection(missileBounds)) {
		isHit = true;
	}

	return isHit;
}

// Returns randomized seconds offset based on passed max offset
int alienMissileSecondsOffset(unsigned int seconds) {
	unsigned int centiseconds = seconds * SECONDS_TO_CENTISECONDS_FACTOR; // Convert to centiseconds to use with rand()
	unsigned int secondsOffset = (rand() % centiseconds + 1) / SECONDS_TO_CENTISECONDS_FACTOR; // Randomize and convert back to seconds
	return secondsOffset;
}

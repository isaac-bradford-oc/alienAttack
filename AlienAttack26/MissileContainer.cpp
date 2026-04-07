/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: MissileContainer.cpp
 * Description: This file contains the MissileContainer class functions. 
 ****************************************/

#include "gameHeader.h"

/*
 * Name: MissileContainer::draw
 * Arg(s): RenderWindow& window
 * Returns: void
 *
 * Draws the Pixie's sprite on screen
 */
void MissileContainer::draw(RenderWindow& window) {
	for (Pixie* missile : missileVector) { 
		missile->draw(window);
	}
}

/*
 * Name: MissileContainer::move
 * Arg(s): float x, float y
 * Returns: void
 *
 * Moves missiles by passed x and y values
 */
void MissileContainer::move(float x, float y) {
	for (Pixie* missile : missileVector) {
		missile->move(x, y);
	}
}

/*
 * Name: MissileContainer::createMissile
 * Arg(s): Pixie* object
 * Returns: void
 *
 * Create a new missile object
 */
void MissileContainer::createMissile(Pixie* object) {
	// Create missile
	Pixie* missile = new Pixie(MISSILE_TEXTURE_FILE, ZERO, ZERO, MISSILE_PIXIE);

	// Center missile onto object
	float missileX = object->centerX(*missile);
	float missileY = object->getY();
	missile->setPosition(missileX, missileY);

	// Push missile to vector
	missileVector.push_back(missile);
}

/*
 * Name: MissileContainer::fire
 * Arg(s): Pixie* object
 * Returns: void
 *
 * Fires missile if space is pressed
 */
void MissileContainer::fire(Pixie* object) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Space) // Condition continued on next line
	&& (this->getNumMissiles() < MAX_PLAYER_MISSILES)) { // If space is pressed and missile limit not reached
		this->createMissile(object); // Create missile
	}
}

/*
 * Name: MissileContainer::collision
 * Arg(s): Ship* ship
 * Returns: bool
 *
 * Check for collion between missile and victim
 */
bool MissileContainer::collision(Ship* ship) {
	bool collision = false;

	for (Pixie* missile : missileVector) {
		if (ship->collision(missile)) {
			collision = true;
		}
	}

	return collision;
}

/*
 * Name: MissileContainer::collision
 * Arg(s): AlienArmy* alienArmy
 * Returns: bool
 *
 * Check for collion between missile and victim
 */
bool MissileContainer::collision(AlienArmy* alienArmy) {
	bool collision = false;

	for (Pixie* missile : missileVector) {
		if (alienArmy->collision(missile)) {
			collision = true;
		}
	}

	return collision;
}

/*
 * Name: MissileContainer::eraseHitMissiles
 * Arg(s): ()
 * Returns: void
 *
 * Delete and erase any hit missiles
 */
void MissileContainer::eraseHitMissiles() {
	// Iterate through vector
	for (auto iter = missileVector.begin(); iter != missileVector.end();) {
		// If hit, erase missile
		if ((*iter)->isHit()) {
			delete* iter;
			iter = missileVector.erase(iter);
		}
		else {
			++iter;
		}
	}
}

/*
 * Name: MissileContainer::eraseOffScreenMissiles
 * Arg(s): ()
 * Returns: void
 *
 * Clear all missiles from vector
 */
void MissileContainer::eraseOffScreenMissiles() {
	// Iterate through vector
	for (auto iter = missileVector.begin(); iter < missileVector.end();) {
		// If off-screen, erase missile
		if ((*iter)->getY() < ZERO) {
			delete *iter;
			iter = missileVector.erase(iter);
		}
		else {
			++iter;
		}
	}
}

/*
 * Name: MissileContainer::MissileContainer
 * Arg(s): ()
 * Returns: N/A
 *
 * Constructor initializes vector as empty
 */
MissileContainer::MissileContainer() {
	missileVector = {};
}

/*
 * Name: MissileContainer::~MissileContainer
 * Arg(s): ()
 * Returns: N/A
 *
 * Destructor
 */
MissileContainer::~MissileContainer() {
	for (Pixie* missile : missileVector) {
		delete missile;
	}
}

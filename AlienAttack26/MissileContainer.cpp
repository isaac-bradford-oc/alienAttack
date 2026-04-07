/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: MissileContainer.cpp
 * Description: This file contains the MissileContainer class functions. 
 ****************************************/

#include "gameHeader.h"

// Draws the Pixie's sprite on screen 
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
void MissileContainer::draw(RenderWindow& window) {
	for (Pixie* missile : missileVector) { 
		missile->draw(window);
	}
}

// Moves missiles by passed x and y values
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
void MissileContainer::move(float x, float y) {
	for (Pixie* missile : missileVector) {
		missile->move(x, y);
	}
}

// Create a new missile object
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
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

// Fires missile if space is pressed
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
void MissileContainer::fire(Pixie* object) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Space) // Condition continued on next line
	&& (this->getNumMissiles() < MAX_PLAYER_MISSILES)) { // If space is pressed and missile limit not reached
		this->createMissile(object); // Create missile
	}
}

// Check for collion between missile and victim
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
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

// Check for collion between missile and victim
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
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

// Delete and erase any hit missiles
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
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

// Clear all missiles from vector
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
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

// Constructor initializes vector as empty
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
MissileContainer::MissileContainer() {
	missileVector = {};
}

// Destructor
/*
 * Name: main 
 * Arg(s): ()
 * Returns: int 
 *
 * Main function
 */
MissileContainer::~MissileContainer() {
	for (Pixie* missile : missileVector) {
		delete missile;
	}
}

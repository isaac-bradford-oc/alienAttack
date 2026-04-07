/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: MissileContainer.h 
 * Description: This file contains the MissileContainer class (derived from Pixie class). 
 ****************************************/

#pragma once
#include "gameHeader.h"

// AlienArmy class
class MissileContainer : public Pixie {
private:
	vector<Pixie*> missileVector; // Vector for missiles
public:
	// SFML function recreation
	void draw(RenderWindow& window); // Draws missiles
	void move(float x, float y); // Moves missiles by passed x and y values
	float getY(); // Get y value for all missiles in vector

	// Getters
	bool empty() { return missileVector.empty(); } // Returns true if vector is empty
	unsigned int getNumMissiles() { return missileVector.size(); } // Returns number of aliens in vector

	// Game functions
	void createMissile(Pixie* object); // Create a new missile object
	void fire(Pixie* object); // Fires missile if space is pressed
	bool collision(Ship* ship);
	bool collision(AlienArmy* alienArmy);
	void eraseHitMissiles(); // Delete and erase any hit missiles 
	void eraseOffScreenMissiles(); // Delete and erase missiles that reach the window border
	void clear() { missileVector.clear(); } // Clear all missiles from vector

	// Constructors
	MissileContainer(); // Constructor initializes vector as empty
	~MissileContainer(); // Destructor
};

/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: AlienArmy.h 
 * Description: This file contains the AlienArmy class (derived from Pixie class). 
 ****************************************/

#pragma once
#include "gameHeader.h"

// AlienArmy class
class AlienArmy : public Pixie {
private:
	vector<Pixie*> alienVector; // Vector for aliens
public:
	// SFML function recreation
	void draw(RenderWindow& window); // Draws the alien army
	void move(float x, float y); // Moves aliens by passed x and y values

	// Getters
	bool empty() { return alienVector.empty(); } // Returns true if vector is empty
	unsigned int getNumAliens() { return alienVector.size(); } // Returns number of aliens in vector
	Pixie* getRandomAlien(); // Returns a random alien from vector

	// Game functions
	Pixie* createAlien(float alienStartingX, float alienStartingY); // Create a new alien object
	bool below(float position); // Checks if any alien in army is below passed position
	bool collision(Pixie* missile);
	void eraseHitAliens(); // Delete and erase any hit aliens
	void move(bool& isGoingLeft, bool& isChangingDirection); // Moves aliens and changes their direction if one hits a border
	void spawnWave(unsigned int numAliens); // Spawn an alien wave based on passed quantity
	void spawnWave(); // Spawns alien wave based on size of passed vector

	// Constructors
	AlienArmy(unsigned int numAliens); // Constructor spawns wave based on passed number of aliens
	~AlienArmy(); // Destructor
};

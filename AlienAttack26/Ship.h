/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: Ship.h 
 * Description: This file contains the Ship class (derived from Pixie class). 
 ****************************************/

#include "gameHeader.h"

class Ship : public Pixie {
private:
	unsigned int lives; // Player lives
public:
	// Member functions
	void setLives(unsigned int lives) { this->lives = lives; } // Sets player lives
	int getLives() { return lives; } // Gets player lives
	void loseLife(); // Decrement lives and reset ship position

	// Constructors
	Ship(unsigned int lives); // Default constructor
};
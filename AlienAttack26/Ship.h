/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: Ship.h 
 * Description: This file contains the Ship class (derived from Pixie class). 
 ****************************************/

#pragma once
#include "gameHeader.h"

// Ship class
class Ship : public Pixie {
private:
	unsigned int lives; // Player lives
public:
	// SFML function recreation
	void move(); // Move ship based on which key is pressed

	// Setter
	void setLives(unsigned int lives) { this->lives = lives; } // Sets player lives
	
	// Getter
	unsigned int getLives() const { return lives; } // Gets player lives

	// Game functions
	bool collision(Pixie* missile); // Checks for ship collision with missile
	void loseLife(); // Decrement lives and reset ship position

	// Constructor
	Ship(unsigned int lives); // Default constructor
};
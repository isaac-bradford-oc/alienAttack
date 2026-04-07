/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: LifeIconContainer.h 
 * Description: This file contains the LifeIconContainer class (derived from Pixie class). 
 ****************************************/

#pragma once
#include "gameHeader.h"

class LifeIconContainer : public Pixie {
private:
	vector<Pixie*> lifeIconVector;
	unsigned int lives;
public:
	// SFML function recreation
	void draw(RenderWindow& window); // Draws the Pixie's sprite on screen 

	// Getter 
	unsigned int getLives() const { return lives; } // Return lives

	// Game function
	void loseLife(); // Remove life icon from vector and decrement lives

	// Constructors
	LifeIconContainer(unsigned int maxLives); // Default constructor
	~LifeIconContainer(); // Destructor
};

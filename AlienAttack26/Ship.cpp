/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 5
 * File Name: Ship.cpp
 * Description: This file contains the pixie class functions. 
 ****************************************/

#include "gameHeader.h"

// Default constructor
Ship::Ship(int lives) {
	setLives(lives);
	setTextureSourceFile(SHIP_TEXTURE_FILE);
	setSprite(getTexture());
	setID();
	setType(PLAYER_SHIP_PIXIE);
}

// Destructor
Ship::~Ship() {
	delete getTexture();
	delete getSprite();
}
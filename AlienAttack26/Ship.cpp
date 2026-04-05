/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 5
 * File Name: Ship.cpp
 * Description: This file contains the pixie class functions. 
 ****************************************/

#include "gameHeader.h"

void Ship::loseLife() {
	--lives;
	setPosition(SHIP_OOB, SHIP_OOB);
}

// Default constructor
Ship::Ship(unsigned int lives) {
	setLives(lives);
	setTextureSourceFile(SHIP_TEXTURE_FILE);
	setSprite(getTexture());
	setScale(SCALE, SCALE);
	setPosition(SHIP_X, SHIP_Y);
	setID();
	setType(PLAYER_SHIP_PIXIE);
}

// Destructor
Ship::~Ship() {
	delete getTexture();
	delete getSprite();
}
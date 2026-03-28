#include "gameHeader.h"
/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: pixie.cpp
 * Description: This file contains the pixie class functions. 
 ****************************************/

int Pixie::nextPixieID = 0; // Initialize shared ID variable

// Center one object on another object
float Pixie::centerX(Pixie& objectToCenter) {
	float callerObjectCenter = getX() + mySprite->getLocalBounds().getCenter().x;
	float passedObjectCenter = objectToCenter.getSprite()->getLocalBounds().getCenter().x;
	return callerObjectCenter + passedObjectCenter;
}

// Load pixie's texture from file
void Pixie::setTextureSourceFile(std::string filename) {
	// Allocate memory for texture
	myTexture = new sf::Texture();
	// Abort program if unable to load file
	if (!myTexture->loadFromFile(filename)) {
		std::cout << "Unable to load ship texture!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

// Default constructor
Pixie::Pixie() {
	myTexture = nullptr;
	mySprite = nullptr;
	myID = nextPixieID++;
	pixieType = UNDEFINED_PIXIE;
}

// Loads pixie's texture from file, sets sprite position, and assigns pixie type
Pixie::Pixie(std::string filename, float x, float y, int type) {
	setTextureSourceFile(filename);

	mySprite = new sf::Sprite(*myTexture);
	mySprite->setPosition({ x, y });

	myID = nextPixieID++;
	pixieType = type;
}

// Destructor
Pixie::~Pixie() {
	delete myTexture;
	delete mySprite;
}

/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: Pixie.cpp
 * Description: This file contains the Pixie class functions. 
 ****************************************/

#include "gameHeader.h"

int Pixie::nextPixieID = 0; // Initialize shared ID variable

// Center one object on another object
float Pixie::centerX(Pixie& objectToCenter) {
	float callerObjectCenter = getX() + mySprite->getLocalBounds().getCenter().x;
	float passedObjectCenter = objectToCenter.getSprite()->getLocalBounds().getCenter().x;
	return callerObjectCenter + passedObjectCenter;
}

// Load Pixie's texture from file
void Pixie::setTextureSourceFile(string filename) {
	// Allocate memory for texture
	myTexture = new Texture();
	// Abort program if unable to load file
	if (!myTexture->loadFromFile(filename)) {
		cout << "Unable to load ship texture!" << std::endl;
		exit(EXIT_FAILURE);
	}
}

// Default constructor
Pixie::Pixie() {
	setTextureSourceFile();
	setSprite();
	setID();
	setType(UNDEFINED_PIXIE);
}

// Loads Pixie's texture from file, sets sprite position, and assigns pixie type
Pixie::Pixie(string filename, float x, float y, int type) {
	setTextureSourceFile(filename);

	setSprite(myTexture);
	mySprite->setPosition({ x, y });

	setID();
	setType(type);
}

// Destructor
Pixie::~Pixie() {
	delete myTexture;
	delete mySprite;
}

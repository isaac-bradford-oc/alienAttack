/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: Pixie.h
 * Description: This file contains the Pixie class. 
 ****************************************/

#pragma once
#include "gameHeader.h"

// Pixie class
class Pixie {
private:
	Sprite* mySprite; // Pointer to Pixie's sprite
	Texture* myTexture; // Pointer to Pixie's texture
	static int nextPixieID; // Shared ID variable; increments upon object construction
	int myID; // Pixie's ID
	int PixieType; // Pixie's type (as defined in gameHeader.h)
	bool hitStatus; // Is Pixie hit?
public:
	// SFML function recreation
	void draw(RenderWindow& window) { window.draw(*mySprite); } // Draws the Pixie's sprite on screen 
	void move(float x, float y) { mySprite->move({ x, y }); } // Moves Pixie's sprite by x and y pixels
	void setScale(float xScale, float yScale) {	mySprite->setScale({ xScale, yScale }); } // Sets Pixie's sprite's scale
	void setPosition(float x, float y) { mySprite->setPosition({ x, y }); } // Sets Pixie's sprite's position

	// Getters
	float getX() { return mySprite->getPosition().x; } // Gets Pixie's sprite's x position
	float centerX(Pixie& objectToCenter); // Centers passed object to caller object
	float getY() { return mySprite->getPosition().y; } // Gets Pixie's sprite's x position
	Pixie* getSelfPointer() { return this; } // Gets Pixie's self pointer
	Sprite* getSprite() { return mySprite; } // Gets Pixie's sprite pointer
	Texture* getTexture() { return myTexture; } // Gets Pixie's texture pointer
	int getID() const { return myID; } // Gets Pixie's ID
	int getType() const { return PixieType; } // Gets pixie's type
	bool isHit() const { return hitStatus; } // Check if a Pixie is hit
	
	// Setters
	void setX(float x) { mySprite->setPosition({ x, this->getY() }); } // Sets Pixie's sprite's x position
	void setY(float y) { mySprite->setPosition({ this->getX(), y }); } // Sets Pixie's sprite's y position
	void setSprite() { mySprite = nullptr; } // Sets mySprite to nullptr
	void setSprite(Texture* myTexture) { mySprite = new sf::Sprite(*myTexture); } // Creates sprite with myTexture
	void setTextureSourceFile() { myTexture = nullptr; } // Sets myTexture to nullptr
	void setTextureSourceFile(string filename); // Loads Pixie's texture from file with error checking
	void setID() { this->myID = nextPixieID++; } // Sets myID and increments static ID variable
	void setType(int type) { PixieType = type; } // Sets pixie's type
	void hit() { hitStatus = true; } // A Pixie got hit, set hitStatus to true

	// Constructors
	Pixie(); // Default constructor. Sets all variables to null values
	Pixie(string, float, float, int); // Loads Pixie's texture from file, sets sprite position, and assigns pixie type
	~Pixie(); // Destructor
};


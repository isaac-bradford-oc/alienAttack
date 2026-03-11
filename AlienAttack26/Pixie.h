#pragma once
/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: pixie.h
 * Description: This file contains the pixie class. 
 ****************************************/

#include <SFML/Graphics.hpp>
#include <string>

// Pixie class
class Pixie {
private:
	sf::Sprite* mySprite; // Pointer to pixie's sprite
	sf::Texture* myTexture; // Pointer to pixie's texture
	static int nextPixieID; // Shared ID variable; increments upon object construction
	int myID; // Pixie's ID
	int pixieType; // Pixie's type (as defined in gameHeader.h)
public:
	void draw(sf::RenderWindow& window) { window.draw(*mySprite); } // Draws the pixie's sprite on screen 
	void move(float x, float y) { mySprite->move({ x, y }); } // Moves pixie's sprite by x and y pixels
	void setScale(float xScale, float yScale) {	mySprite->setScale({ xScale, yScale }); } // Sets pixie's sprite's scale
	void setPosition(float x, float y) { mySprite->setPosition({ x, y }); } // Sets pixie's sprite's position

	float getX() { return mySprite->getPosition().x; } // Gets pixie's sprite's x position
	float centerX(Pixie& objectToCenter); // Centers passed object to caller object
	float getY() { return mySprite->getPosition().y; } // Gets pixie's sprite's x position
	sf::Sprite* getSprite() { return mySprite; } // Gets pixie's sprite pointer
	sf::Texture* getTexture() { return myTexture; } // Gets pixie's texture pointer
	int getID() { return myID; } // Gets pixie's ID
	int getType() { return pixieType; } // Gets pixie's type
	Pixie* getSelfPointer() { return this; } // Gets pixie's self pointer
	
	void setType(int type) { pixieType = type; } // Sets pixie's type
	void setX(float x) { mySprite->setPosition({ x, this->getY() }); } // Sets pixie's sprite's x position
	void setY(float y) { mySprite->setPosition({ this->getX(), y }); } // Sets pixie's sprite's y position
	void setTextureSourceFile(std::string filename); // Loads pixie's texture from file with error checking

	Pixie(); // Default constructor. Sets all variables to null values
	Pixie(std::string, float, float, int); // Loads pixie's texture from file, sets sprite position, and assigns pixie type
};


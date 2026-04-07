/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: LifeIconContainer.cpp
 * Description: This file contains the LifeIconContainer class functions. 
 ****************************************/

#include "gameHeader.h"

// Draws life icons
void LifeIconContainer::draw(RenderWindow& window) {
	for (Pixie* lifeIcon : lifeIconVector) {
		lifeIcon->draw(window);
	}
}

// Remove life icon from vector and decrement lives
void LifeIconContainer::loseLife() {
	lifeIconVector.pop_back();
	--lives;
}

// Default constructor
LifeIconContainer::LifeIconContainer(unsigned int maxLives) {
	lives = maxLives;

	for (unsigned int i = 0; i < maxLives; ++i) {
		float iconX = static_cast<float>(WINDOW_WIDTH) - ((i + 1) * LIFE_ICON_OFFSET); // Start at right border and place each alien further left
		float iconY = WINDOW_HEIGHT - LIFE_ICON_OFFSET; // Bottom border minus offset
		Pixie* lifeIcon = new Pixie(SHIP_TEXTURE_FILE, iconX, iconY, LIFE_ICON_PIXIE); // Create life icon

		lifeIconVector.push_back(lifeIcon); // Push icon to vector
	}
}

// Destructor
LifeIconContainer::~LifeIconContainer() {
	for (Pixie* lifeIcon : lifeIconVector) {
		delete lifeIcon;
	}
}

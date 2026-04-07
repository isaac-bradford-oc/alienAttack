/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: LifeIconContainer.cpp
 * Description: This file contains the LifeIconContainer class functions. 
 ****************************************/

#include "gameHeader.h"

/*
 * Name: LifeIconContainer::draw
 * Arg(s): RenderWindow& window
 * Returns: void
 *
 * Draws life icons
 */
void LifeIconContainer::draw(RenderWindow& window) {
	for (Pixie* lifeIcon : lifeIconVector) {
		lifeIcon->draw(window);
	}
}

/*
 * Name: LifeIconContainer::loseLife
 * Arg(s): ()
 * Returns: void
 *
 * Remove life icon from vector and decrement lives
 */
void LifeIconContainer::loseLife() {
	lifeIconVector.pop_back();
	--lives;
}

/*
 * Name: LifeIconContainer::LifeIconContainer
 * Arg(s): unsigned int maxLives
 * Returns: N/A
 *
 * Default constructor
 */
LifeIconContainer::LifeIconContainer(unsigned int maxLives) {
	lives = maxLives;

	for (unsigned int i = 0; i < maxLives; ++i) {
		float iconX = static_cast<float>(WINDOW_WIDTH) - ((i + 1) * LIFE_ICON_OFFSET); // Start at right border and place each alien further left
		float iconY = WINDOW_HEIGHT - LIFE_ICON_OFFSET; // Bottom border minus offset
		Pixie* lifeIcon = new Pixie(SHIP_TEXTURE_FILE, iconX, iconY, LIFE_ICON_PIXIE); // Create life icon

		lifeIconVector.push_back(lifeIcon); // Push icon to vector
	}
}

/*
 * Name: LifeIconContainer::~LifeIconContainer
 * Arg(s): ()
 * Returns: N/A
 *
 * Destructor
 */
LifeIconContainer::~LifeIconContainer() {
	for (Pixie* lifeIcon : lifeIconVector) {
		delete lifeIcon;
	}
}

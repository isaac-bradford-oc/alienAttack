#pragma once
#include "gameHeader.h"

class AlienArmy : public Pixie {
private:
	vector<Pixie*> alienVector;
	unsigned int numAliens;

public:
	void setNumAliens(unsigned int numAliens) { this->numAliens = numAliens; }
	unsigned int getNumAliens() { return numAliens; }
	void draw(RenderWindow& window);
	bool empty() { return alienVector.empty(); }
	void moveAlien(Pixie* alien, bool& isGoingLeft, bool& isChangingDirection);
	void spawnWave(unsigned int numAliens);
	void spawnWave();

	AlienArmy(unsigned int numAliens);
};

#include "gameHeader.h"

class Ship : public Pixie {
private:
	unsigned int lives; // Player lives
public:
	// Member functions
	void setLives(unsigned int lives) { this->lives = lives; } // Sets player lives
	int getLives() { return lives; } // Gets player lives
	void loseLife();

	// Constructors
	Ship(unsigned int lives); // Default constructor
	~Ship(); // Destructor
};
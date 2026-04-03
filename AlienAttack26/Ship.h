#include "gameHeader.h"

class Ship : public Pixie {
private:
	int lives; // Player lives
public:
	// Member functions
	void setLives(int lives) { this->lives = lives; } // Sets player lives
	int getLives() { return lives; } // Gets player lives

	// Constructors
	Ship(int lives); // Default constructor
	~Ship(); // Destructor
};
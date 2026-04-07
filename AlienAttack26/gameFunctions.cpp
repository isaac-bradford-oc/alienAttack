/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: gameFunctions.cpp
 * Description: This file contains the functions for the game.
 ****************************************/

#include "gameHeader.h"

// Returns clock time as seconds
clock_t clocksPerSecond() { return clock() / CLOCKS_PER_SEC; }

// Returns randomized seconds offset based on passed max offset
int alienMissileSecondsOffset(unsigned int seconds) {
	unsigned int centiseconds = seconds * SECONDS_TO_CENTISECONDS_FACTOR; // Convert to centiseconds to use with rand()
	unsigned int secondsOffset = (rand() % centiseconds + 1) / SECONDS_TO_CENTISECONDS_FACTOR; // Randomize and convert back to seconds

	return secondsOffset;
}

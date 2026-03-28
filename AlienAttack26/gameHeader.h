#pragma once
/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: gameHeader.h
 * Description: This file contains the includes, constants, and function prototypes.
 ****************************************/

// includes go below
#include "Pixie.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

// Constants for the game 
const int UNDEFINED_PIXIE = 0; // Undefined pixie type
const int PLAYER_SHIP_PIXIE = 1; // Ship pixie type
const int PLAYER_MISSILE_PIXIE = 2; // Missile pixie type
const int ALIEN_PIXIE = 3; // Alien pixie type
const int BACKGROUND_PIXIE = 4; // Background pixie type

const unsigned int WINDOW_WIDTH = 1200u; // window is 800 pixels wide
const unsigned int WINDOW_HEIGHT = 1400u; // window is 600 pixels vertically "high"
const unsigned int FRAMERATE = 60u;
const float ZERO = 0.0f; // Zero as float
const float SHIP_X = (float)WINDOW_WIDTH / 2.0f;
const float SHIP_Y = (float)WINDOW_HEIGHT - ((float)WINDOW_HEIGHT / 5.0f);
const float SHIP_DISTANCE = 10.0f; // When the ship moves it moves 5 pixels at a time. 
const float MISSILE_DISTANCE = 10.0f; // When the ship moves it moves 5 pixels at a time. 
const int MAX_PLAYER_MISSILES = 3;
const float SCALE = 1.5f;
const float ALIEN_LEFT_LIMIT = (float)WINDOW_WIDTH / 4.0f;
const float ALIEN_RIGHT_LIMIT = (float)WINDOW_WIDTH - (float)WINDOW_WIDTH / 4.0f;
const float ALIEN_HORIZONTAL_DISTANCE = 2.5f;
const float ALIEN_VERTICAL_DISTANCE = 250.0f;
const float ALIEN_STARTING_X = (float)WINDOW_WIDTH / 2.0f;
const float ALIEN_STARTING_Y = (float)WINDOW_HEIGHT / 5.0f;

// Game Functions
void moveShip(Pixie& ship); // Moves ship based on which key is pressed
Pixie* createMissile(); // Creates missile object
Pixie* createAlien(float alienX, float alienY); // Creates alien object
bool collision(Pixie* victimOfMissile, Pixie* missile); // Detects alien-missile collision
void moveAlien(Pixie* alien, bool& isGoingLeft, bool& isChangingDirection);
void spawnAlienWave(std::vector<Pixie*>& alienVector, int rows, int cols);

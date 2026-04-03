/****************************************
 * Isaac Bradford
 * March 4, 2026
 * Large Program 3
 * File Name: gameHeader.h
 * Description: This file contains the includes, constants, and function prototypes.
 ****************************************/

// Includes
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>

using namespace std;
using namespace sf;

#include "Pixie.h"
#include "Ship.h"

// Constants for the game 
const string GAME_NAME = "Aliens!";
const string SHIP_TEXTURE_FILE = "ship.png";
const string ALIEN_TEXTURE_FILE = "alien.bmp";
const string MISSILE_TEXTURE_FILE = "missile.bmp";
const string BACKGROUND_TEXTURE_FILE = "stars.jpg";

const int UNDEFINED_PIXIE = 0; // Undefined pixie type
const int PLAYER_SHIP_PIXIE = 1; // Ship pixie type
const int PLAYER_MISSILE_PIXIE = 2; // Missile pixie type
const int ALIEN_PIXIE = 3; // Alien pixie type
const int BACKGROUND_PIXIE = 4; // Background pixie type

const unsigned int WINDOW_WIDTH = 1200u; // Window is 800 pixels wide
const unsigned int WINDOW_HEIGHT = 1400u; // Window is 600 pixels tall
const unsigned int FRAMERATE = 60u; // Window framerate
const float SCALE = 1.5f; // Scale factor for sprite textures

const int ONE_SECOND = 1; // For clarification when using clock
const float ZERO = 0.0f; // Zero as float

const int MAX_PLAYER_LIVES = 3; // Starting player lives
const float SHIP_X = (float)WINDOW_WIDTH / 2.0f; // Ship starting x position
const float SHIP_Y = (float)WINDOW_HEIGHT - ((float)WINDOW_HEIGHT / 5.0f); // Ship starting y position
const float SHIP_DISTANCE = 10.0f; // When the ship moves it moves 5 pixels at a time. 

const int MAX_PLAYER_MISSILES = 3; // Player missile limit
const float MISSILE_DISTANCE = 10.0f; // Distance a missile should move

const float ALIEN_LEFT_LIMIT = (float)WINDOW_WIDTH / 4.0f; // Left limit for alien army
const float ALIEN_RIGHT_LIMIT = (float)WINDOW_WIDTH - (float)WINDOW_WIDTH / 4.0f; // Left limit for alien army
const float ALIEN_HORIZONTAL_DISTANCE = 2.5f; // Alien horizontal movement distance
const float ALIEN_VERTICAL_DISTANCE = 250.0f; //  Alien vertical movement distance
const float ALIEN_STARTING_X = (float)WINDOW_WIDTH / 2.0f; // Starting horizontal position of alien army center
const float ALIEN_STARTING_Y = (float)WINDOW_HEIGHT / 5.0f; // Starting vertical position of alien army center

// Game Functions
Pixie* createAlien(float alienX, float alienY); // Creates alien object
Pixie* createMissile(); // Creates missile object
void spawnAlienWave(std::vector<Pixie*>& alienVector, int rows, int cols); // Spawns aliens in even number of rows and columns
void moveShip(Pixie& ship); // Moves ship based on which key is pressed
void moveAlien(Pixie* alien, bool& isGoingLeft, bool& isChangingDirection); // Moves alien by alien distance constants, checks if alien hits horizontal limit, and changes its direction
bool collision(Pixie* victimOfMissile, Pixie* missile); // Detects alien-missile collision
int secondsOffset(int seconds); // Second offset used with clock

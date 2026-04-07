/****************************************
 * Isaac Bradford
 * April 4, 2026
 * Large Program 5
 * File Name: gameHeader.h
 * Description: This file contains the includes, constants, and function prototypes.
 ****************************************/

// Includes
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <random>

using namespace std;
using namespace sf;

// Constants for the game 
const string GAME_NAME = "Aliens!";
const string SHIP_TEXTURE_FILE = "ship.png";
const string ALIEN_TEXTURE_FILE = "alien.bmp";
const string MISSILE_TEXTURE_FILE = "missile.bmp";
const string BACKGROUND_TEXTURE_FILE = "stars.jpg";

const string GAME_WIN_MESSAGE = "You win!";
const string GAME_LOSE_MESSAGE = "You lose!";
const string GAME_SCORE_MESSAGE = "Your score was: ";

const int UNDEFINED_PIXIE = 0; // Undefined pixie type
const int SHIP_PIXIE = 1; // Ship pixie type
const int ALIEN_PIXIE = 2; // Alien pixie type
const int MISSILE_PIXIE = 3; // Missile pixie type
const int BACKGROUND_PIXIE = 4; // Background pixie type
const int LIFE_ICON_PIXIE = 5; // Player lives icon

const unsigned int WINDOW_WIDTH = 1200u; // Window is 800 pixels wide
const unsigned int WINDOW_HEIGHT = 1400u; // Window is 600 pixels tall
const unsigned int FRAMERATE = 60u; // Window framerate
const float SCALE = 1.5f; // Scale factor for sprite textures

const float ZERO = 0.0f; // Zero as float
const int ONE_SECOND = 1; // For clarification when using clock
const int SECONDS_TO_CENTISECONDS_FACTOR = 10;

const int MAX_PLAYER_LIVES = 3; // Starting player lives
const int LIFE_ICON_OFFSET = 25; // Space between life icons

const float SHIP_X = WINDOW_WIDTH / 2.0f; // Ship starting x position
const float SHIP_Y = WINDOW_HEIGHT - (WINDOW_HEIGHT / 5.0f); // Ship starting y position
const float SHIP_DISTANCE = 10.0f; // When the ship moves it moves 5 pixels at a time. 
const float SHIP_OOB = -50.0f; // Ship out-of-bounds coordinates

const int MAX_PLAYER_MISSILES = 3; // Player missile limit
const float MISSILE_DISTANCE = 10.0f; // Distance a missile should move

const float ALIEN_LEFT_LIMIT = WINDOW_WIDTH / 4.0f; // Left limit for alien army
const float ALIEN_RIGHT_LIMIT = WINDOW_WIDTH - (WINDOW_WIDTH / 4.0f); // Left limit for alien army
const float ALIEN_HORIZONTAL_DISTANCE = 2.5f; // Alien horizontal movement distance
const float ALIEN_VERTICAL_DISTANCE = 250.0f; //  Alien vertical movement distance
const float ALIEN_X = WINDOW_WIDTH / 2.0f; // Starting horizontal position of alien army center
const float ALIEN_Y = WINDOW_HEIGHT / 5.0f; // Starting vertical position of alien army center
const unsigned int ALIEN_X_OFFSET = 80u; // Distance between alien rows
const unsigned int ALIEN_Y_OFFSET = 60u; // Distance between alien columns
const unsigned int ALIEN_SCORE = 250u; // Score for eliminating an alien
const unsigned int LEVEL_ONE_ALIENS = 19u; // Amount of aliens to spawn in level one
const unsigned int ALIEN_MISSILE_MAX_SECONDS_OFFSET = 1u; // Max time to offset firing of alien missile

// Game Functions
clock_t clocksPerSecond(); // Returns clock time as seconds
int alienMissileSecondsOffset(unsigned int seconds); // Returns randomized seconds offset based on passed max offset

// Include classes
#include "Pixie.h"
#include "Ship.h"
#include "AlienArmy.h"
#include "MissileContainer.h"
#include "LifeIconContainer.h"

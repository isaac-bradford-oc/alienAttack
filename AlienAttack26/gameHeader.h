#pragma once
<<<<<<< HEAD
/*
*  gameFunctions.cpp
*     - The functions for the game program are in this file.
*
*  AUTHOR: Most of the work in this program was completed by Prof. Andy Harbert
*          Prof. Pat Smith has made modifications (December 2021)
*
*/
// includes go below
#include <iostream>
using namespace std;
// these two lines are specific to the SFML graphics library. 
#include <SFML/Graphics.hpp>
using namespace sf;

// Constants for the game 
const float DISTANCE = 5.0f; // When the ship moves it moves 5 pixels at a time. 
const int WINDOW_WIDTH = 800; // window is 800 pixels wide
const int WINDOW_HEIGHT = 600;// window is 600 pixels vertically "high"

// Game Functions
void moveShip(Sprite& ship); 
=======
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
// these two lines are specific to the SFML graphics library. 

// Constants for the game 
const int UNDEFINED_PIXIE = 0; // Undefined pixie type
const int PLAYER_SHIP_PIXIE = 1; // Ship pixie type
const int PLAYER_MISSILE_PIXIE = 2; // Missile pixie type
const int BACKGROUND_PIXIE = 3; // Background pixie type

const float ZERO = 0.0f; // Zero as float
const float DISTANCE = 10.0f; // When the ship moves it moves 5 pixels at a time. 
const float SCALE = 1.5f;
const unsigned int WINDOW_WIDTH = 1200u; // window is 800 pixels wide
const unsigned int WINDOW_HEIGHT = 1400u; // window is 600 pixels vertically "high"
const unsigned int FRAMERATE = 60u;

// Game Functions
void moveShip(Pixie& ship); // Moves ship based on which key is pressed
Pixie* createMissile(); // Creates missile object
>>>>>>> 8e4678e (Add project files.)

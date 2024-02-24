#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
//#include <ATMlib.h>
#include "bitmaps.h"
#include "vec2.h"
#include "physics.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5

//define game states (on main menu)
#define STATE_GAME_NEXT_LEVEL        6
#define STATE_GAME_PLAYING           7
#define STATE_GAME_PAUSE             8
#define STATE_GAME_OVER              9

#define FRAME_RATE                   30
#define PHYSICS_TICKS_PER_FRAME      50

#define GAME_TOP                     0
#define GAME_BOTTOM                  48
#define GAME_LEFT                    0
#define GAME_RIGHT                   112

#define FACING_SOUTH                 0
#define FACING_WEST                  1
#define FACING_NORTH                 2
#define FACING_EAST                  3

#define FIRST_LEVEL                  0


Arduboy2Base arduboy;
Sprites sprites;
Physics physics;
//ATMsynth ATM;

byte gameState = STATE_MENU_INTRO;   // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_MENU_PLAY; // PLAY menu item is pre-selected
byte globalCounter = 0;
byte level = FIRST_LEVEL;
byte camY = 0;
vec2 gravity(0, 0.004);

#endif

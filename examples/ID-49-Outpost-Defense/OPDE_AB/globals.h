#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ATMlib.h>
#include "bitmaps.h"
#include "songs.h"

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

#define FIRST_LEVEL                  0


#define POINTER_MOVE                 0
#define POINTER_TARGET               2
Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

byte gameState = STATE_MENU_INTRO;   // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_MENU_PLAY; // PLAY menu item is pre-selected
byte globalCounter = 0;
byte pointer_x   = 64;
byte pointer_y   = 32;
byte pointer_step = 0;
byte pointer_ctr  = 0;
byte pointer_state = POINTER_MOVE;

#endif

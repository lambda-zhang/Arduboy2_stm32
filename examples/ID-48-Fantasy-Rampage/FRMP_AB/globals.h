#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#ifndef STM32F103xB
#include <ATMlib.h>
#endif /* STM32F103xB */
#include <Sprites.h>
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5

//define game states (on main menu)
#define STATE_GAME_SELECT_GAME_MODE   6
#define STATE_GAME_SELECT_PLAYER_MODE 7
#define STATE_GAME_PLAYING            8


Arduboy2Base arduboy;
Sprites sprites;

#ifndef STM32F103xB
ATMsynth ATM;
#endif /* STM32F103xB */


byte gameState = STATE_MENU_INTRO;   // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_MENU_PLAY; // PLAY menu item is pre-selected
byte globalCounter = 0;

boolean blinking = true;
boolean songPlayed = false;

#endif

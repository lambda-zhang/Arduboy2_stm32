#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO                  0
#define STATE_MENU_MAIN                   1
#define STATE_MENU_READ                   2
#define STATE_MENU_DELETE                 3
#define STATE_MENU_RESET                  4

Arduboy2Base arduboy;
Sprites sprites;

byte gameState = STATE_MENU_INTRO;        // start the game with the TEAM a.r.g. logo
byte menuSelection = STATE_MENU_READ;     // PLAY menu item is pre-selected
byte globalCounter = 0;

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

#endif

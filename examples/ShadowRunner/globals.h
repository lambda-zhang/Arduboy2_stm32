#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
// #include <ArduboyTones.h>
const unsigned int FRAME_RATE = 40; // Frame rate in frames per second
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO             0
#define STATE_MENU_MAIN              1
#define STATE_MENU_HELP              2
#define STATE_MENU_PLAY              3
#define STATE_MENU_INFO              4
#define STATE_MENU_SOUNDFX           5

//define game states (on main menu)
#define STATE_GAME_INIT_LEVEL        6
#define STATE_GAME_PLAYING           7
#define STATE_GAME_PAUSE             8
#define STATE_GAME_OVER              9

#define LEVEL_TO_START_WITH          0

static Arduboy2Base arduboy;
static Sprites sprites;
// ArduboyTones sound(arduboy.audio.enabled);
static BeepPin1 beep;

void sound(byte tone, byte duration) {
  if (arduboy.audio.enabled()) {
    beep.tone(beep.freq(tone), duration *2 );
  }
}

//determines the state of the game
static byte gameState = STATE_MENU_INTRO;   // start the game with the TEAM a.r.g. logo
//generic variable to store menuSelection (on screens)
static byte menuSelection = STATE_MENU_PLAY; // PLAY menu item is pre-selected
static byte globalCounter = 0;

// These are all getting a value in STATE_GAME_INIT
static int lifePlayer;
static unsigned long scorePlayer;
static unsigned long nextLevelAt;
static byte level = LEVEL_TO_START_WITH;

#endif

#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <Arduboy2.h>
#include <ATMlib.h>
#include "bitmaps.h"

//define menu states (on main menu)
#define STATE_MENU_INTRO              0
#define STATE_MENU_MAIN               1
#define STATE_MENU_HELP               2
#define STATE_MENU_PLAY               3
#define STATE_MENU_INFO               4
#define STATE_MENU_SOUNDFX            5

//define game states (on main menu)
#define STATE_GAME_PLAYING            6
#define STATE_GAME_PAUSE              7
#define STATE_GAME_OVER               8

#define WALKINGSPEED                  3 // lower number = higher speed

#define WAVE_TO_START_WITH            0
#define WAVE_TO_START_REPEAT          2

Arduboy2Base arduboy;
Sprites sprites;
ATMsynth ATM;

byte gameState = STATE_MENU_INTRO;                             // start the game with the TEAM a.r.g. logo
byte globalCounter = 0;
const unsigned char PROGMEM frameSequence[4] = {0, 1, 2, 1};   // this is the frame frequence we are using for the walking animations
unsigned long playerScore;
boolean menuX = true;
boolean menuY = false;
byte currentWave;
byte previousWave;

void drawScore(byte x, byte y)
{
  sprites.drawPlusMask(x, y, uiScroll_plus_mask, 0);
  char buf[10];
  //playerScore = arduboy.cpuLoad();
  ltoa(playerScore, buf, 10);
  char charLen = strlen(buf);
  char pad = 8 - charLen;
  sprites.drawPlusMask(x + 5  + (8 * charLen), y, uiScroll_plus_mask, 2);
  // draw numbers
  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48) digit = 0;
    else
    {
      digit -= 48;
      if (digit > 9) digit = 0;
    }
    for (byte z = 0; z < 10; z++) if (digit == z) j = z;
    sprites.drawPlusMask(x + 8  + (8 * i), y, numbersInGame_plus_mask, digit);
  }
}

#endif

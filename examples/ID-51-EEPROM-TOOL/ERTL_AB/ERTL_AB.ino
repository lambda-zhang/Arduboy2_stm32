/*
  EEPROM TOOL: http://www.team-arg.org/ertl-manual.html

  Arduboy version 0.0.1:  http://www.team-arg.org/ertl-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2018 - JO3RI GANTOIS

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 51

#include "globals.h"
#include "menu.h"
#include "inputs.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuRead,
  stateMenuDelete,
  stateMenuReset,
};

void setup() {
  arduboy.boot();
  arduboy.setFrameRate(60);
  Serial.begin(9600);
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();

}

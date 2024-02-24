/*
  Pinball: http://www.team-arg.org/pnbl-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/pnbl-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2017 - Gaveno - JO3RI

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 44

#include <Arduino.h>
#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "elements.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGameNextLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};


void setup() {
  arduboy.boot();                                           // begin with the boot logo en setting up the device to work
  arduboy.audio.begin();
  arduboy.bootLogoSpritesSelfMasked();
  arduboy.setFrameRate(FRAME_RATE);
  physics = Physics(FRAME_RATE, PHYSICS_TICKS_PER_FRAME);
  Serial.begin(9600);
}


void loop() {
  if (gameState == STATE_GAME_PLAYING && physics.nextTick()) gameUpdatePhysics();
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}


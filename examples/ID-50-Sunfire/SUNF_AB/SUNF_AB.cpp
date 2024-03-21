/*
  Sunfire  - Space Flight Simulator/Shooter: http://www.team-arg.org/sufi-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/sufi-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2017/2018 - Trodoss

  License: MIT : https://opensource.org/licenses/MIT
*/

//determine the game
#define GAME_ID 50

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "sound_data.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePlaying,
  stateWaveComplete,
  stateGameOver
};


void setup() {
  arduboy.boot();
  arduboy.audio.begin();
  arduboy.setFrameRate(30);                                 // set the frame rate of the game at 30 fps
  arduboy.initRandomSeed();                                 // This sets the random to more random, remove this if no random is needed !
  ATM.play(titleSong);
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}


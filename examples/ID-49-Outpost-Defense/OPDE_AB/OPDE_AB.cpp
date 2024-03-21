/*
  Outpost Defense: http://www.team-arg.org/opde-manual.html

  Arduboy version 0.1:  http://www.team-arg.org/opde-downloads.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2017 - Trodoss

  License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 49

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "elements.h"
#include "levels.h"

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
  //ATM.play(titleSong);
  arduboy.begin();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  arduboy.initRandomSeed();                                 // This sets the random to more random, remove this if no random is needed !
}


void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}


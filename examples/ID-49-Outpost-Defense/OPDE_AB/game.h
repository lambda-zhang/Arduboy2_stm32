#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "inputs.h"
#include "levels.h"
#include "elements.h"

void stateMenuPlay()
//void stateGamePrepareLevel()
{
  gameState = STATE_GAME_NEXT_LEVEL;
  level_element_add(TYPE_EGG, 64, 8, EGG_STATE_FALL, 2, 10);
  level_element_add(TYPE_WALKER, 16, 39, STATE_MOVE_RIGHT, 6,1);
  level_element_add(TYPE_TROOPER, 16, 43, STATE_MOVE_RIGHT, 5,1);
};


void stateGameNextLevel()
{
  //level++;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  level_draw();
  
  checkInputs();
  
  level_element_handle();
};

void stateGamePause()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{
  
};



#endif

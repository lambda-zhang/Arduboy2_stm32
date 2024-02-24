#ifndef INPUTS_H
#define INPUTS_H

#include "globals.h"
#include "levels.h"
#include "elements.h"

void checkInputs()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PAUSE;
  
  pointer_ctr++;
  if (pointer_ctr > 6) {
    pointer_step++;
    if (pointer_step > 1) pointer_step = 0;

    if (arduboy.pressed(UP_BUTTON)) 
    {
      if (pointer_y > 0) pointer_y -= 8;
    }
    if (arduboy.pressed(DOWN_BUTTON))
    {
      if (pointer_y < 40) pointer_y +=8;
    }
    if (arduboy.pressed(LEFT_BUTTON)) {
      if (pointer_x > 0) pointer_x-=8;
    }
    if (arduboy.pressed(RIGHT_BUTTON)) {
       if (pointer_x < 120) pointer_x+=8;
    }
      
    pointer_ctr = 0;
  }

  pointer_state = POINTER_MOVE;
  if (level_check_move(pointer_x, pointer_y) > 0)  pointer_state = POINTER_TARGET;

  if (arduboy.justPressed(B_BUTTON)) {
    level_element_add(TYPE_TROOPER, pointer_x, pointer_y+3, STATE_MOVE_RIGHT, 5,1);
  }
  sprites.drawSelfMasked(pointer_x, pointer_y, pointer_img, pointer_state + pointer_step);
  
}


#endif

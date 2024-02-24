#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>
#include "ball.h"
#include "flipper.h"

extern Ball ball;
extern Flipper flipperLeft;
extern Flipper flipperRight;

void checkInputs()
{
  if (arduboy.justPressed(A_BUTTON)) {
    if (ball.getPos() > vec2(120, 218) && ball.getPos() < vec2(127, 224))
      ball.impulse(vec2(0, -1.5));
  }
  /*if (arduboy.justPressed(B_BUTTON)) {
    Serial.print("Position: ");
    ball.print();
  }*/

  if (arduboy.pressed(B_BUTTON))
    flipperRight.flipping = true;
  else
    flipperRight.flipping = false;

  if (arduboy.pressed(LEFT_BUTTON))
    flipperLeft.flipping = true;
  else
    flipperLeft.flipping = false;
}


#endif

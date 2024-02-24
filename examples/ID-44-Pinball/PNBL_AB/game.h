#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "elements.h"
#include "ball.h"
#include "flipper.h"

Ball ball;
Flipper flipperLeft(33, 213, -1);
Flipper flipperRight(85, 213, 1);
Bumper bumper1(43, 71);
Bumper bumper2(60, 126);
Bumper bumper3(22, 119);

void stateMenuPlay()
//void stateGamePrepareLevel()
{
  ball = Ball(123, 219);
  /*flipperLeft = Flipper(31, 214, -1);
  flipperRight = Flipper(85, 214, 1);*/
  createNormals();
  gameState = STATE_GAME_NEXT_LEVEL;
};


void stateGameNextLevel()
{
  level++;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  checkInputs();
  ball.update();
  flipperLeft.update();
  camY = max(min(232, round(ball.getPos().y) - 32), 0);
  sprites.drawSelfMasked(0, -camY, sprBoard, 0);
  flipperLeft.draw();
  flipperRight.draw();
  bumper1.draw();
  bumper2.draw();
  bumper3.draw();
  ball.draw();
};

void stateGamePause()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{
  
};

void gameUpdatePhysics() {
  ball.physicsUpdate();
  flipperRight.physicsUpdate();
  flipperLeft.physicsUpdate();
  bumper1.physicsUpdate();
  bumper2.physicsUpdate();
  bumper3.physicsUpdate();
}

#endif

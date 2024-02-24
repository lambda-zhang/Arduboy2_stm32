#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"
#include "ball.h"
#include "vec2.h"

extern Ball ball;

class Bumper {
public:
  Bumper(int x, int y) {
    pos = { x, y, 8, 8 };
    imageTimer = 0;
  }

  void draw() {
    sprites.drawOverwrite(pos.x - 2, pos.y - 2 - camY, sprBumper, (imageTimer > 0));
    imageTimer = max(--imageTimer, 0);
  }

  void physicsUpdate() {
    vec2 col = checkCollision();
    if (col != vec2(0, 0)) {
      vec2 newpos(pos.x + 2, pos.y + 2);
      newpos += col * 6;
      ball.setPos(newpos);
      ball.reflect(col);
      ball.impulse(col * 0.2);
      imageTimer = 6;
    }
  }

  vec2 checkCollision() {
    Point bpos = {ball.getPos().x, ball.getPos().y };
    if (arduboy.collide(bpos, pos)) {
      vec2 out(bpos.x - pos.x + 3, bpos.y - pos.y - 3);
      return out.getNormal();
    }
    return vec2(0, 0);
  }

protected:
  Rect pos;
  byte imageTimer;
};

#endif

#ifndef _BALL_
#define _BALL_

#include "globals.h"
#include "board.h"
#include "vec2.h"
#include <math.h>

#define ACCURACY    1
#define EMPTY       0.0

extern Arduboy2Base arduboy;
extern Sprites sprites;

#define sign(x) (x < 0) ? -1 : 1

class Ball {
public:
  Ball(int x, int y) {
    pos = vec2(x, y);
  }
  
  Ball() : Ball(0, 0) {}

  void draw() {
    sprites.drawPlusMask(round(pos.x) - 2, round(pos.y) - 2 - camY, sprBall, 0);
  }

  void physicsUpdate() {
    velocity += gravity;
    if (velocity.getMagnitude() > 2) {
      velocity.convertNormal();
      velocity *= 2;
    }

    vec2 surface_normal = checkCollision(pos + velocity);
    if (surface_normal.getMagnitude() == EMPTY) {
      pos += velocity;
    }
    else {
      pos = pos + velocity + surface_normal;
      pos = vec2(round(pos.x), round(pos.y));
      reflect(surface_normal);
    }
  }

  void update() {
    if (pos.y > 234 ) {
      pos = vec2(123, 219);
      velocity = vec2(0, 0);
    }
  }

  void reflect(vec2 normal_vector) {
    velocity -= normal_vector * 1.3 * (velocity * normal_vector);
  }

  void impulse(vec2 impulse_vector) {
    velocity += impulse_vector;
  }

  vec2 checkCollision(vec2 point) {
    boolean collision = false;
    vec2 reflection_vector(0, 0);
    if (!mapGetCollisionPoint(round(point.x), round(point.y), comBoard)) {
      collision = true;
      reflection_vector += mapGetNormalVector(round(point.x), round(point.y), comBoard);
    }
    if (collision && reflection_vector.getMagnitude() == EMPTY)
      return vec2 (0, 1);
    return reflection_vector;
  }

  vec2 getPos() {
    return pos;
  }

  void setPos(const vec2 &dest) {
    pos = dest;
  }

  void print() {
    Serial.print("Ball: Position: ");
    pos.print();
    Serial.print(" Velocity: ");
    velocity.print();
    Serial.println();
  }
  
protected:
  vec2 pos;
  vec2 velocity;
};


#endif


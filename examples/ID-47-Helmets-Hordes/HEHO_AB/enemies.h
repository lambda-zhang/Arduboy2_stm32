#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"
#include "elements.h"

#define ENEMY_LEFT_OFFSCREEN_LIMIT              -32
#define FLAME_FALL_OFF_LIMIT                    102
#define WEED_HIDING_LIMIT                       80
#define ENEMY_START_X                           144
#define BADWALKINGFLAME_START_X                 160
#define BADFLAME_START_X                        176
#define BADWEED_START_X                         128

#define MAX_ORCS_IN_WAVE                        9
#define MAX_SPIKES_IN_WAVE                      3

#define ORC_Y                                   39
#define SPIKE_Y                                 41
#define BADWALKINGFLAME_Y                       4
#define BADFLAME_Y                              4
#define STATUE_Y                                32
#define ARROW_Y                                 40
#define BADWEED_Y                               36

#define ORC_COLLISION_WIDTH                     14
#define SPEAR_F_COLLISION_WIDTH                 28
#define SPEAR_U_COLLISION_WIDTH                 3
#define SPIKE_COLLISION_WIDTH                   6
#define BADFLAME_COLLISION_WIDTH                12
#define STATUE_COLLISION_WIDTH                  1
#define ARROW_COLLISION_WIDTH                   16
#define BADWEED_COLLISION_WIDTH                 12

#define ORC_COLLISION_HEIGHT                    18
#define SPEAR_F_COLLISION_HEIGHT                3
#define SPEAR_U_COLLISION_HEIGHT                24
#define SPIKE_COLLISION_HEIGHT                  8
#define BADFLAME_COLLISION_HEIGHT               12
#define STATUE_COLLISION_HEIGHT                 16
#define ARROW_COLLISION_HEIGHT                  4
#define BADWEED_COLLISION_HEIGHT                8

#define ENEMY_ORC_NO_SPEAR                      0
#define ENEMY_ORC_FLAT_SPEAR                    1
#define ENEMY_ORC_UP_SPEAR                      2

#define BADFLAME_ON_TORCH                       0
#define BADFLAME_FALLING                        1
#define BADFLAME_RUNNING                        2

#define BADWEED_HIDING                          0
#define BADWEED_PEEKING                         1
#define BADWEED_RUNNING                         2

#define BADFLAME_TOTAL_FALING_FRAMES            10
#define BADWEED_TOTAL_PEEKING_FRAMES            15

byte orcFrames;

const unsigned char PROGMEM flameJumpSequence[] = {3, 0, 0, 0, 3, 6, 10, 15, 21, 32};
const unsigned char PROGMEM weedJumpSequence[] = {0, 0, 0, 0, 11, 14, 15, 14, 11, 9, 4};
const unsigned char PROGMEM weedFrameSequence[] = {0, 1, 2, 3, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0};


//////// Orc functions ///////////////////
//////////////////////////////////////////
struct Orcs
{
  public:
    int x;
    byte characteristics;   //0B00000000;   //this byte holds all the orc characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1 / Orc type: 0 = no spear | 1 = flat spear | 2 = up spear
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};


Orcs orc[MAX_ORCS_IN_WAVE];

void updateOrcs()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) orcFrames++;

  if (arduboy.everyXFrames(WALKINGSPEED))
  {
    for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
    {
      if (orc[i].x > ENEMY_LEFT_OFFSCREEN_LIMIT) orc[i].x -= 3;
      else orc[i].characteristics = 0;
    }
  }
}


void orcsSetInLine(byte orcType, byte firstOrc, byte lastOrc, int x, int spacingX)
{
  for (byte i = firstOrc; i < lastOrc + 1; i++)
  {
    orc[i].characteristics = 0B10010000 + orcType;
    orc[i].x = 128 + x + (spacingX * (i - firstOrc));
  }
}

void drawOrcs()
{
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++)
  {
    if (orc[i].characteristics & 0B00010000)
    {
      sprites.drawPlusMask(orc[i].x - 2, ORC_Y - 12 + ((orcFrames + i) % 2), orcHead_plus_mask, 0);
      switch (orc[i].characteristics & 0B00000011)
      {
        case ENEMY_ORC_NO_SPEAR:
          sprites.drawPlusMask(orc[i].x, ORC_Y + ((orcFrames + i) % 2), orcBody_plus_mask, pgm_read_byte(&frameSequence[(orcFrames + i) % 4]));
          break;
        case ENEMY_ORC_FLAT_SPEAR:
          sprites.drawPlusMask(orc[i].x - 18, ORC_Y + ((orcFrames + i) % 2), orcBodySpearF_plus_mask, pgm_read_byte(&frameSequence[(orcFrames + i) % 4]));
          break;
        case ENEMY_ORC_UP_SPEAR:
          sprites.drawPlusMask(orc[i].x - 1, ORC_Y + ((orcFrames + i) % 2), orcBodySpearU_plus_mask, pgm_read_byte(&frameSequence[(orcFrames + i) % 4]));
          sprites.drawPlusMask(orc[i].x - 2, ORC_Y + ((orcFrames + i) % 2) - 24, orcSpearU_plus_mask, 0);
          break;
      }
    }
  }
}

//////// Spike functions /////////////////
//////////////////////////////////////////
struct Spikes
{
  public:
    int x;
    byte characteristics;   //0B00000000;   //this byte holds all the spike characteristics
    //                          ||||||||
    //                          |||||||└->  0
    //                          ||||||└-->  1
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

Spikes spike[MAX_SPIKES_IN_WAVE];

void updateSpikes()
{
  if (arduboy.everyXFrames(2))
  {
    for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
    {
      if (spike[i].x > ENEMY_LEFT_OFFSCREEN_LIMIT) spike[i].x--;
      else spike[i].characteristics = 0;
    }
  }
}

void spikesSetInLine(byte firstspike, byte lastspike, int x, int spacingX)
{
  for (byte i = firstspike; i < lastspike + 1; i++)
  {
    spike[i].characteristics = 0B11010000;
    spike[i].x = 128 + x + (spacingX * (i - firstspike));
  }
}

void drawSpikes()
{
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++)
  {
    if (spike[i].characteristics & 0B00010000)
    {
      sprites.drawPlusMask(spike[i].x, SPIKE_Y, hazardSpike_plus_mask, 0);
    }
  }
}

//////// Bad Walking Flame functions /////
//////////////////////////////////////////
struct BadWalkingFlames
{
  public:
    int x;
    byte y;
    byte fallingFrame;
    byte characteristics;   //0B00000000;   //this byte holds all the bad flame characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1 / flame type: 0 = on torch | 1 = falling | 2 = running
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

BadWalkingFlames badWalkingFlame;

void updateBadWalkingFlame()
{
  switch (badWalkingFlame.characteristics & 0B00000011)
  {
    case BADFLAME_ON_TORCH:
      if (arduboy.everyXFrames(3))
      {

        if (badWalkingFlame.x > FLAME_FALL_OFF_LIMIT) badWalkingFlame.x--;
        else badWalkingFlame.characteristics++;
      }
      break;
    case BADFLAME_FALLING:
      if (arduboy.everyXFrames(WALKINGSPEED))
      {
        badWalkingFlame.x -= 3;
        if (badWalkingFlame.fallingFrame < BADFLAME_TOTAL_FALING_FRAMES)
        {
          badWalkingFlame.y = pgm_read_byte(&flameJumpSequence[badWalkingFlame.fallingFrame]);
          badWalkingFlame.fallingFrame++;
        }
        else
        {
          badWalkingFlame.fallingFrame = 0;
          badWalkingFlame.characteristics++;
        }
      }
      break;
    case BADFLAME_RUNNING:
      if (arduboy.everyXFrames(WALKINGSPEED))
      {
        if (badWalkingFlame.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badWalkingFlame.x -= 3;
        else badWalkingFlame.characteristics = 0;
      }
      break;
  }
}

void badWalkingFlameSetInLine()
{
  badWalkingFlame.characteristics = 0B11010000;
  badWalkingFlame.x = BADFLAME_START_X;
  badWalkingFlame.y = BADWALKINGFLAME_Y;
}

void drawBadWalkingFlame()
{
  if (badWalkingFlame.characteristics & 0B00010000)
  {
    sprites.drawPlusMask(badWalkingFlame.x, badWalkingFlame.y, monsterFlame_plus_mask, flameFrame);
  }
}

//////// Bad Flame functions /////////////
//////////////////////////////////////////
struct BadFlames
{
  public:
    int x;
    byte y;
    byte characteristics;   //0B00000000;   //this byte holds all the bad flame characteristics
    //                          ||||||||
    //                          |||||||└->  0
    //                          ||||||└-->  1
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

BadFlames badFlame;

void updateBadFlame()
{
  if (arduboy.everyXFrames(3))
  {
    if (badFlame.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badFlame.x--;
    else badFlame.characteristics = 0;
  }
}

void badFlameSetInLine()
{
  badFlame.characteristics = 0B11010000;
  badFlame.x = BADFLAME_START_X;
  badFlame.y = BADFLAME_Y;
}

void drawBadFlame()
{
  if (badFlame.characteristics & 0B00010000)
  {
    sprites.drawPlusMask(badFlame.x, badFlame.y, monsterFlame_plus_mask, flameFrame);
  }
}

//////// Statue functions /////////////
///////////////////////////////////////
struct Statues
{
  public:
    int x;
    byte characteristics;   //0B00000000;   //this byte holds all the statue characteristics
    //                          ||||||||
    //                          |||||||└->  0
    //                          ||||||└-->  1
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

Statues statue;
Statues arrow;


void updateStatue()
{
  if (arduboy.everyXFrames(2))
  {
    if (statue.x > ENEMY_LEFT_OFFSCREEN_LIMIT) statue.x--;
    else statue.characteristics = 0;
    if (statue.x > 102) arrow.x--;
    else
    {
      if (arrow.x > ENEMY_LEFT_OFFSCREEN_LIMIT) arrow.x -= 4;
      else arrow.characteristics = 0;
    }
  }
}

void statueSetInLine()
{
  statue.characteristics = 0B11010000;
  statue.x = ENEMY_START_X;

  arrow.characteristics = 0B11010000;
  arrow.x = ENEMY_START_X;
}

void drawStatueFront()
{
  if (statue.characteristics & 0B00010000)
  {
    sprites.drawPlusMask(statue.x, STATUE_Y, statueFront_plus_mask, 0);
  }
}

void drawStatueBack()
{
  if (statue.characteristics & 0B00010000)
  {
    sprites.drawPlusMask(statue.x + 7, STATUE_Y, statueBack_plus_mask, 0);
  }
}

void drawArrows()
{
  if (arrow.characteristics & 0B00010000)
  {
    sprites.drawPlusMask(arrow.x, ARROW_Y, statueArrow_plus_mask, 0);
  }
}

//////// Bad Weed functions ///////////
///////////////////////////////////////
struct BadWeeds
{
  public:
    int x;
    byte y;
    byte weedFrame;
    byte characteristics;   //0B00000000;   //this byte holds all the bad weed characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1 / Weed type: 0 = hidding | 1 = peeking | 2 = showing
    //                          |||||└--->  2
    //                          ||||└---->  3
    //                          |||└----->  4 the enemy is visible  (0 = false / 1 = true)
    //                          ||└------>  5 the enemy is dying    (0 = false / 1 = true)
    //                          |└------->  6 the enemy is imune    (0 = false / 1 = true)
    //                          └-------->  7 the enemy is alive    (0 = false / 1 = true)
};

BadWeeds badWeed;

void updateBadWeed()
{
  switch (badWeed.characteristics & 0B00000011)
  {
    case BADWEED_HIDING:
      if (arduboy.everyXFrames(2))
      {
        if (badWeed.x > WEED_HIDING_LIMIT) badWeed.x--;
        else
        {
          badWeed.weedFrame = 4;
          badWeed.characteristics++;
        }
      }
      break;
    case BADWEED_PEEKING:
      if (arduboy.everyXFrames(2))
        badWeed.weedFrame++;
      {
        badWeed.x--;
        if (badWeed.weedFrame < BADWEED_TOTAL_PEEKING_FRAMES)
        {
          badWeed.y = BADWEED_Y - pgm_read_byte(&weedJumpSequence[badWeed.weedFrame - 4]);
        }
        else
        {
          badWeed.weedFrame = 0;
          badWeed.characteristics++;
        }
      }
      break;
    case BADWEED_RUNNING:
      if (arduboy.everyXFrames(6))badWeed.weedFrame = (++badWeed.weedFrame) % 4;
      if (arduboy.everyXFrames(WALKINGSPEED))

      {
        if (badWeed.x > ENEMY_LEFT_OFFSCREEN_LIMIT) badWeed.x -= 3;
        else
        {
          badWeed.x = BADWEED_START_X;
          badWeed.y = BADWEED_Y;
          badWeed.characteristics = 0;
        }
      }
      break;
  }
}

void badWeedSetInLine()
{
  badWeed.characteristics = 0B11010000;
  badWeed.weedFrame = 1;
  badWeed.x = BADWEED_START_X;
  badWeed.y = BADWEED_Y;
}

void drawBadWeed()
{
  if (badWeed.characteristics & 0B00010000)
  {
    sprites.drawPlusMask(badWeed.x, badWeed.y, monsterWeed_plus_mask, pgm_read_byte(&weedFrameSequence[badWeed.weedFrame]));
    sprites.drawErase (badWeed.x, BADWEED_Y + 12, weedMask, 0);
  }
}


void setEnemies()
{
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++) orc[i].characteristics = 0;
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++) spike[i].characteristics = 0;
  badWalkingFlame.characteristics = 0;
  badFlame.characteristics = 0;
  statue.characteristics = 0;
  arrow.characteristics = 0;
  badWeed.characteristics = 0;
}
#endif

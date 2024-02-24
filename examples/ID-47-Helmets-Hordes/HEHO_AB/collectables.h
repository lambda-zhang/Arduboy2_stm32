#ifndef COLLACTBLES_H
#define COLLACTBLES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_GOLDBARS                             9

#define GOLDBAR_COLLISION_WIDTH                           10
#define GOLDBAR_COLLISION_HEIGHT                          16

#define DUNGEON_CHEST_Y                                    35

#define DUNGEON_CHEST_COLLISION_WIDTH                      16
#define DUNGEON_CHEST_COLLISION_HEIGHT                     14


byte goldBarFrames = 0;
const unsigned char PROGMEM goldBarSequence[] = {0, 1, 2, 3, 4, 3, 2, 1};
const unsigned char PROGMEM chestSparkleXY[][3] =
{
  { 4, 11, 1},
  { 11, 5, 2},
  { 0,  0, 3},
};

struct DifferentItems
{
  public:
    int x;
    byte y;
    byte characteristics;   //0B00000000;   //this byte holds all the collectable characteristics
    //                          ||||||||
    //                          |||||||└->  0 \
    //                          ||||||└-->  1  | type of item ( 0 to 7 )
    //                          |||||└--->  2 /
    //                          ||||└---->  3
    //                          |||└----->  4 the collectable is visible   (0 = false / 1 = true)
    //                          ||└------>  5
    //                          |└------->  6 the twinkles are visible     (0 = false / 1 = true)
    //                          └-------->  7 the collectable is active    (0 = false / 1 = true)
};

DifferentItems goldBar[MAX_ONSCREEN_GOLDBARS];
DifferentItems dungeonChests;

void updateGoldBars()
{
  if (arduboy.everyXFrames(8))goldBarFrames++;
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (arduboy.everyXFrames(2))goldBar[i].x--;
    if (goldBar[i].x < -16) goldBar[i].characteristics = 0;
  }
}

void goldBarSetInLine(byte firstGold, byte lastGold, int x, int y, int spacingX)
{
  for (byte i = firstGold; i < lastGold + 1; i++)
  {
    goldBar[i].x = 128 + x + (spacingX * (i - firstGold));
    goldBar[i].y = y;
    goldBar[i].characteristics = 0B10010000;
  }
}

void drawGoldBars()
{

  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++)
  {
    if (goldBar[i].characteristics & 0B00010000)
    {
      sprites.drawPlusMask(goldBar[i].x, goldBar[i].y, treasureBar_plus_mask,  pgm_read_byte(&goldBarSequence[(goldBarFrames) % 8]));
    }
  }
}


void updateSecretChest()
{
  if (arduboy.everyXFrames(2))dungeonChests.x--;
  if (dungeonChests.x < -16) dungeonChests.characteristics = 0;
}

void dungeonChestsSetInLine(byte x, byte type)
{
  dungeonChests.x = 128 + x;
  dungeonChests.y = DUNGEON_CHEST_Y;
  dungeonChests.characteristics = 0B10010000 + type;
  sparkleFrame = 7;
}

void drawSecretChest()
{
  if (dungeonChests.characteristics & 0B00010000)
  {
    sprites.drawSelfMasked(dungeonChests.x, dungeonChests.y, dungeonChest, 0);
  }
}

void setCollectables()
{
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++) goldBar[i].characteristics = 0;
  dungeonChests.characteristics = 0;
}

void drawSecretSparkles()
{
  if (dungeonChests.characteristics & 0B01000000)
  {
    if (arduboy.everyXFrames(6))sparkleFrame++;
    for (byte i = 0; i < 3; i++)
    {
      sprites.drawPlusMask(
        dungeonChests.x - pgm_read_byte(&chestSparkleXY[i][0]),
        32 + pgm_read_byte(&chestSparkleXY[i][1]),
        effectShine_plus_mask,
        pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + pgm_read_byte(&chestSparkleXY[i][2]))  % 15]));
    }
  }
}


#endif

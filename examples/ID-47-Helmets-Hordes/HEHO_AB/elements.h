#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"

#define FLOORPART_Y                                       48
#define FLOORWEED_Y                                       39
#define TORCHHANDLE_Y                                     20
#define TORCHFLAME_Y                                      4
#define WINDOW_Y                                          5

byte flameFrame = 0;

const unsigned char PROGMEM chainSetupX[] = {128, 128, 144, 144, 160, 160};
const unsigned char PROGMEM chainAndBricksSetupY[] = {0, 16, 0, 16, 0, 16};
const unsigned char PROGMEM chainSetupVisible[] = { 0B00110100, 0B00000111, 0B00010011, 0B00110101, 0B00111100, 0B00110111, 0B00001101, 0B00001111 };
const unsigned char PROGMEM brickSetupTwo[] =
{
  0B11100001, 0B10010011, 0B00111011, 0B00111100,
  0B10000001, 0B00110110, 0B00010010, 0B10110001,
  0B00110010, 0B00101001, 0B00010011, 0B10010010,
  0B00100100, 0B00011110, 0B00111001, 0B10000011
};



// create all elements
//////////////////////

struct BackGroundWall
{
  boolean isVisible;
};

BackGroundWall torchHandles[3];
BackGroundWall torchFlames[3];
BackGroundWall window[3];

struct BrickParts
{
  byte y;
  byte type;
};

BrickParts bricks[12];

struct BackgroundParts
{
  int x;
};

BackgroundParts floorPart[3];
BackgroundParts floorWeed;
BackgroundParts wallPart[3];

struct ForGroundStuff
{
  int x;
  byte y;
  boolean isVisible;
};

ForGroundStuff chain[6];


// Set all elements
///////////////////
void setFloorPart()
{
  for (byte i = 0; i < 3; i++) floorPart[i].x = 64 * i;
}


void setChains()
{
  byte chainSet = random(8);
  for (byte i = 0; i < 6; i++)
  {
    chain[i].x = pgm_read_byte(&chainSetupX[i]);
    chain[i].y = pgm_read_byte(&chainAndBricksSetupY[i]);
    chain[i].isVisible = pgm_read_byte(&chainSetupVisible[chainSet]) & (1 << i);
    switch ((chainSet * 6) + i)
    {
      case 27: case 31: case 39: case 43:
        chain[i].y = 8;
        break;
    }
  }

}


boolean windowOrTorch()
{ 
  switch (random(3))
  {
    case 0: case 1:
      return true;
      break;
    case 2:
      return false;
      break;
  }
}

byte gifBrick(byte type, byte row)
{
  return ((pgm_read_byte(&brickSetupTwo[type]) >> (row * 2)) & 0B00000011);
}

void setWallParts()
{
  for (byte i = 0; i < 3; i++)
  {
    wallPart[i].x = i * 80;
    byte brickSet = random(16);
    for (byte k = 0; k < 4; k++)
    {
      bricks[k + (4 * i)].type = gifBrick(brickSet, k);
      bricks[k + (4 * i)].y = pgm_read_byte(&chainAndBricksSetupY[k]);
    }
    window[i].isVisible = windowOrTorch();
    torchHandles[i].isVisible = !window[i].isVisible;
    torchFlames[i].isVisible = torchHandles[i].isVisible;
  }
}





// Update all elementes
///////////////////////
void updateWallParts()
{
  if (arduboy.everyXFrames(4)) flameFrame = (++flameFrame) % 4;
  if (arduboy.everyXFrames(3))
  {
    for (byte i = 0; i < 3; i++)
    {
      wallPart[i].x--;
      if (wallPart[i].x < -79)
      {
        wallPart[i].x = 160;
        byte brickSet = random(16);
        for (byte k = 0; k < 4; k++)
        {
          bricks[k + (4 * i)].type = gifBrick(brickSet, k);
        }
        window[i].isVisible = windowOrTorch();
        torchHandles[i].isVisible = !window[i].isVisible;
        torchFlames[i].isVisible = torchHandles[i].isVisible;
      }
    }
  }
}


// Draw all elementes
/////////////////////
void drawFloorPart()
{
  for (byte i = 0; i < 3; i++)
  {
    if (arduboy.everyXFrames(2)) floorPart[i].x--;
    if (floorPart[i].x < -63) floorPart[i].x = 128;
    sprites.drawSelfMasked (floorPart[i].x, FLOORPART_Y, dungeonFloor, 0);
  }
}

void drawFloorWeed()
{
  if (arduboy.everyXFrames(2)) floorWeed.x--;
  if (floorWeed.x < -512) floorWeed.x = 128;
  sprites.drawPlusMask (floorWeed.x, FLOORWEED_Y, monsterWeed_plus_mask, 0);
  sprites.drawErase (floorWeed.x, FLOORWEED_Y + 9, weedMask, 0);
}


void drawChains()
{
  for (byte i = 0; i < 6; i++)
  {
    if (arduboy.everyXFrames(1)) chain[i].x--;
    if (chain[i].isVisible)sprites.drawPlusMask (chain[i].x, chain[i].y, dungeonChain_plus_mask, 0);
  }
  if (chain[5].x < -255) setChains();
}



void drawWallParts()
{
  for (byte i = 0; i < 3; i++)
  {
    if (window[i].isVisible)sprites.drawSelfMasked (wallPart[i].x + 16, WINDOW_Y, dungeonWindow, 0);
    if (torchHandles[i].isVisible)sprites.drawSelfMasked (wallPart[i].x + 19, TORCHHANDLE_Y, torchHandle, 0);
    if (torchFlames[i].isVisible)sprites.drawSelfMasked (wallPart[i].x + 16, TORCHFLAME_Y, torchFlame, flameFrame);
    for (byte k = 0; k < 4; k++)
    {
      sprites.drawSelfMasked (wallPart[i].x + ((k / 2) * 32), bricks[k + (4 * i)].y, dungeonBricks, bricks[k + (4 * i)].type);
    }

  }
}


#endif

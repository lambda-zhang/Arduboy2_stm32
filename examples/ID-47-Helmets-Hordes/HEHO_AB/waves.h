#ifndef WAVES_H
#define WAVES_H

#include "globals.h"
#include "enemies.h"
#include "elements.h"
#include "collectables.h"

// HELPER FUNCTIONS
///////////////////
boolean checkStartWave()
{
  if (currentWave != previousWave)
  {
    previousWave = currentWave;
    return true;
  }
  return false;
}

boolean checkFlamePosition()
{
  for (byte i = 0; i < 3; i++)
  {
    if (wallPart[i].x == 159)
    {
      window[i].isVisible = false;
      torchFlames[i].isVisible = false;
      torchHandles[i].isVisible = true;
      return true;
    }
  }
  return false;
}

boolean checkEndWave()
{
  byte test = 0;
  for (byte i = 0; i < MAX_ORCS_IN_WAVE; i++) test += (orc[i].characteristics & 0B10000000) >> 7;
  for (byte i = 0; i < MAX_SPIKES_IN_WAVE; i++) test += (spike[i].characteristics & 0B10000000) >> 7;
  test += (badWalkingFlame.characteristics & 0B10000000) >> 7;
  test += (badFlame.characteristics & 0B10000000) >> 7;
  test += (statue.characteristics & 0B10000000) >> 7;
  test += (arrow.characteristics & 0B10000000) >> 7;
  test += (badWeed.characteristics & 0B10000000) >> 7;
  for (byte i = 0; i < MAX_ONSCREEN_GOLDBARS; i++) test += (goldBar[i].characteristics & 0B10000000) >> 7;
  test += (dungeonChests.characteristics & 0B10000000) >> 7;
  if (test < 1) currentWave++;
}

void wait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    currentWave++;
    globalCounter = 0;
  }
}


// DIFFERENT WAVES
//////////////////
void wave000()
{
  wait();
}

void wave001()
{
  if (checkStartWave())
  {
    dungeonChestsSetInLine(0, HELMET_FOOTBALL);
  }
  updateSecretChest();
  checkEndWave();
}

void wave002()
{
  if (checkStartWave())
  {
    orcsSetInLine(ENEMY_ORC_NO_SPEAR, 0, 8, 192, 48);
    goldBarSetInLine(0, 4, 0, 28, 48);
    goldBarSetInLine(5, 8, 24, 4, 48);
  }
  updateOrcs();
  updateGoldBars();
  checkEndWave();
}

void wave003()
{
  if (checkStartWave())
  {
    spikesSetInLine(0, 2, 0, 64);
    goldBarSetInLine(0, 2, 0, 4, 64);
  }
  updateSpikes();
  updateGoldBars();
  checkEndWave();
}

void wave004()
{
  if (checkStartWave())
  {

  }

  checkEndWave();
}





void wave005()
{
  if (checkStartWave())
  {

  }
  checkEndWave();
}

void wave006()
{
  if (currentWave != previousWave)
  {
    if (checkFlamePosition())
    {
      if (checkStartWave()) badWalkingFlameSetInLine();
    }
  }
  if (badWalkingFlame.characteristics)
  {
    updateBadWalkingFlame();
    checkEndWave();
  }
}

void wave007()
{
  if (currentWave != previousWave)
  {
    if (checkFlamePosition())
    {
      if (checkStartWave()) badFlameSetInLine();
    }
  }
  if (badFlame.characteristics)
  {
    updateBadFlame();
    checkEndWave();
  }
}

void wave008()
{
  if (checkStartWave())
  {
    statueSetInLine();
  }
  updateStatue();
  checkEndWave();
}

void wave009()
{
  if (checkStartWave())
  {
    badWeedSetInLine();
  }
  updateBadWeed();
  checkEndWave();
}

void wave010()
{
  if (checkStartWave())
  {
    dungeonChestsSetInLine(128, random(1, 8));
  }
  updateSecretChest();
  checkEndWave();
}



void wave255()
{
  currentWave = WAVE_TO_START_WITH;
  previousWave = 255;
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM allWaves[] =
{
  wave000,
  wave001,
  wave002,
  wave000,
  wave003,
  wave255,
};


#endif

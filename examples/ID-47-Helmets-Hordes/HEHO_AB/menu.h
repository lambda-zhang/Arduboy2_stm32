#ifndef MENU_H
#define MENU_H

#include "globals.h"

const unsigned char PROGMEM sparkleFrameSequence[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5};
const unsigned char PROGMEM sparklesY[] = {28, 36, 28, 36, 28};
const unsigned char PROGMEM sparklesStartFrame[] = {9, 15, 3, 6, 12};
const unsigned char PROGMEM eyesFrameSequence[] = {1, 2, 2, 3, 3, 4, 4, 4, 3, 3, 2};


byte sparkleFrame = 0;
byte eyesFrame = 0;


void titleScreen()
{
  sprites.drawSelfMasked(0, 0, titleImage, 0);
  if (eyesFrame < 11)sprites.drawSelfMasked(53, 46, titleEyes, pgm_read_byte(&eyesFrameSequence[eyesFrame]));
  else sprites.drawSelfMasked(53, 46, titleEyes, 0);
}


void showSparkles(byte x, byte y)
{
  if (arduboy.everyXFrames(6))sparkleFrame++;
  if (arduboy.everyXFrames(2))++eyesFrame = (++eyesFrame) % 128;
  for (byte i = 0; i < 5; i++)
  {
    sprites.drawPlusMask(
      (22 + (i * 4) - (9 * y)) + (x * (61 + (y * 18))),
      pgm_read_byte(&sparklesY[i]) + (y * 11),
      effectShine_plus_mask,
      pgm_read_byte(&sparkleFrameSequence[(sparkleFrame + pgm_read_byte(&sparklesStartFrame[i])) % 15])
    );
  }
}

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 120) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  titleScreen();

  for (byte k = 0; k < 2; k++)
  {
    for (byte j = 0; j < 2; j++)
    {
      sprites.drawSelfMasked((24 - (9 * k)) + (j * (61 + (k * 18))), 33 + (k * 11), titleMenu, j + (2 * k));
    }
  }
  showSparkles(menuX, menuY);

  if (arduboy.justPressed(RIGHT_BUTTON) && (!menuX)) menuX = !menuX;
  else if (arduboy.justPressed(LEFT_BUTTON) && (menuX)) menuX = !menuX;
  else if (arduboy.justPressed(DOWN_BUTTON) && (!menuY)) menuY = !menuY;
  else if (arduboy.justPressed(UP_BUTTON) && (menuY)) menuY = !menuY;
  else if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = 2 + menuX + (2 * menuY);
}

void stateMenuHelp()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}


void stateMenuInfo()
{
  sprites.drawSelfMasked(16, 36, info, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  titleScreen();
  for (byte k = 0; k < 2; k++)
  {
    for (byte j = 0; j < 2; j++)
    {
      sprites.drawSelfMasked((24 - (9 * k)) + (j * (61 + (k * 18))), 33 + (k * 11), soundMenu, j + (2 * k));
    }
  }
  showSparkles(true, arduboy.audio.enabled());

  if (arduboy.justPressed(RIGHT_BUTTON | DOWN_BUTTON)) arduboy.audio.on();
  else if (arduboy.justPressed(LEFT_BUTTON | UP_BUTTON)) arduboy.audio.off();
  else if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
}


#endif

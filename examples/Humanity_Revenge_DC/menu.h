#define MENU_START     1
#define MENU_INTRO     2
#define MENU_HELP      3
#define MENU_SOUND     4
#define MENU_HIGHSCORE 5
#define NO_SELECTION   255

byte menuselection = MENU_START;

byte menuManagement()
{
  arduboy.drawBitmap(8, 0, logo, 110, 18, 1);

  drawstring(F("start"), 50, 25);
  drawstring(F("intro"), 49, 33);
  drawstring(F("help"), 50, 41);
  drawstring(F("sound"), 50, 49);
  drawstring(F("highscore"), 50, 57);

  if (arduboy.justPressed(DOWN_BUTTON))
  {
    menuselection = min(menuselection++, MENU_HIGHSCORE);
    sound.tone(200, 20);
  }
  else if (arduboy.justPressed(UP_BUTTON))
  {
    menuselection = max(menuselection--, MENU_START);
    sound.tone(200, 20);
  }

  if (menuselection == MENU_SOUND)
    if (arduboy.justPressed(LEFT_BUTTON) || arduboy.justPressed(RIGHT_BUTTON))
    {
      if (arduboy.audio.enabled())
        arduboy.audio.off();
      else
        arduboy.audio.on();
    }

  if (arduboy.audio.enabled())
    drawstring(F("on"), 74, 49);
  else
    drawstring(F("off"), 74, 49);

  switch (menuselection)
  {
    case MENU_START:
      arduboy.drawRect(48, 23, 23, 9, 1);
      break;
    case MENU_INTRO:
      arduboy.drawRect(48, 31, 22, 9, 1);
      break;
    case MENU_HELP:
      arduboy.drawRect(48, 39, 19, 9, 1);
      break;
    case MENU_SOUND:
      arduboy.drawRect(48, 47, 23, 9, 1);
      break;
    case MENU_HIGHSCORE:
      arduboy.drawRect(48, 55, 39, 9, 1);
      break;
  }

  if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
  {
    sound.tone(1000, 20);
    return menuselection;
  }
  else
    return NO_SELECTION;
}

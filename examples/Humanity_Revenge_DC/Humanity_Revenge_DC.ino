//#define DRAW_ONLY_HITBOX
//#define DEBUG_SERIAL
//#define SCREEN_MIRRORING
#define EEPROM_ENABLED

#include "Arduboy2.h"
#include "ArduboyTones.h"

const float pi = 3.141593;
Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);

// game states
#define MENU_SCREEN           0
#define SHIP_SELECTION        1
#define GAMING                2
#define INTRO                 3
#define HELP                  4
#define GAME_OVER             5
#define VICTORY               6
#define HIGH_SCORE            7

byte gamestate = MENU_SCREEN;

#include "globals.h"
#include "font.h"
#include "sprites.h"
#include "menu.h"
#include "shipweapon.h"
#include "bomb.h"
#include "ship.h"
#include "levels.h"
#include "background.h"
#include "enemy.h"
#include "boss.h"
#include "enemymanager.h"
#include "explosions.h"
#include "items.h"
#include "highscore.h"
#include "game.h"

Game game;

void setup() {
  // put your setup code here, to run once:
  arduboy.boot();
  // arduboy.setFrameRate(60);
#ifdef EEPROM_ENABLED
  setHrDcEEPROM();
#endif
#ifdef SCREEN_MIRRORING
  Serial.begin(9600);
#endif
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!arduboy.nextFrame())
    return;

  arduboy.pollButtons();
  arduboy.clear();

  switch (gamestate)
  {
    case MENU_SCREEN:
      {
        byte result = menuManagement();
        switch (result)
        {
          case MENU_START:
            gamestate = SHIP_SELECTION;
            game.reset();
            game.init(SHIP_ODINO);
            break;
          case MENU_INTRO:
            gamestate = INTRO;
            break;
          case MENU_HELP:
            gamestate = HELP;
            break;
          case MENU_HIGHSCORE:
            gamestate = HIGH_SCORE;
            break;
        }
      }
      break;
    case SHIP_SELECTION:
      {
        byte shipselection = game.shipselectionmenu();
        switch (shipselection)
        {
          case SHIP_ODINO:
          case SHIP_THOR:
          case SHIP_FREYR:
            game.reset();
            game.init(shipselection);
            gamestate = GAMING;
            break;
        }
      }
      break;
    case GAMING:
      switch (game.gameloop())
      {
        case VICTORY:
          gamestate = VICTORY;
          break;
        case GAME_OVER:
          gamestate = GAME_OVER;
          break;
      }
      break;
    case VICTORY:
      arduboy.drawBitmap(20, 8, victory, 88, 8, 1);
      drawstring(F("FOR NOW"), 50, 22);

      drawstring(F("SCORE:"), 50, 38);
      drawnumber(game.getscore(), 72, 38);

      drawstring(F("A  SAVE HIGHSCORE"), 10, 58);
      drawstring(F("B  MENU"), 90, 58);

      if (arduboy.justPressed(A_BUTTON))
      {
#ifdef EEPROM_ENABLED
        savehighscore(game.getscore(), game.getcurrentlevel(), game.getshiptype());
#endif
        gamestate = MENU_SCREEN;
      } else if (arduboy.justPressed(B_BUTTON))
        gamestate = MENU_SCREEN;
      break;
    case GAME_OVER:
      //drawstring(F("GAME OVER"), 46, 20);
      arduboy.drawBitmap(7, 8, gameover, 112, 8, 1);
      drawstring(F("SCORE:"), 46, 26);
      drawnumber(game.getscore(), 68, 26);

      drawstring(F("A  SAVE HIGHSCORE"), 10, 42);
      drawstring(F("B  MENU"), 90, 42);

      if (arduboy.justPressed(A_BUTTON))
      {
#ifdef EEPROM_ENABLED
        savehighscore(game.getscore(), game.getcurrentlevel(), game.getshiptype());
#endif
        gamestate = MENU_SCREEN;
      } else if (arduboy.justPressed(B_BUTTON))
        gamestate = MENU_SCREEN;
      break;
    case INTRO:
      drawstring(F("THEY ARE COMING FROM FAR AWAY"), 0, 2);
      drawstring(F("TO DESTROY EVERYTHING"), 0, 10);
      drawstring(F("   BUT"), 0, 26);
      drawstring(F("ONE SINGLE HERO"), 0, 42);
      drawstring(F("WANT TO DESTROY THEM ALL"), 0, 50);

      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
        gamestate = MENU_SCREEN;
      break;
    case HELP:
      drawstring(F("3 LIVES 3 BOMBS"), 0, 2);
      drawstring(F("A        SHOOT"), 0, 16);
      drawstring(F("B        CHANGE WEAPON"), 0, 24);
      drawstring(F("A AND B  BOMB"), 0, 32);
      drawstring(F("COLLECT LIVES  BOMBS  SHIELDS"), 0, 44);
      drawstring(F("DESTROY THEM ALL"), 0, 58);

      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
        gamestate = MENU_SCREEN;
      break;
    case HIGH_SCORE:
#ifdef EEPROM_ENABLED
      drawstring(F("HIGHSCORE"), 0, 0);

      drawstring(F("LEVEL"), 0, 10);
      drawstring(F("SHIP"), 30, 10);
      drawstring(F("SCORE"), 60, 10);

      byte level1 = EEPROM.read(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_LEVEL_S1);
      byte ship1 = EEPROM.read(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_SHIP_S1);
      unsigned int score1 = 0;
      EEPROM.get(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_HSCORE_S1, score1);

      if (level1 != 0 && score1 != 0)
      {
        drawnumber(level1, 0, 20);
        drawshipname(ship1, 30, 20);
        drawnumber(score1, 60, 20);
      } else
        drawstring(F("NO HIGHSCORE"), 0, 20);

      byte level2 = EEPROM.read(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_LEVEL_S2);
      byte ship2 = EEPROM.read(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_SHIP_S2);
      unsigned int score2 = 0;
      EEPROM.get(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_HSCORE_S2, score2);

      if (level2 != 0 && score2 != 0)
      {
        drawnumber(level2, 0, 30);
        drawshipname(ship2, 30, 30);
        drawnumber(score2, 60, 30);
      } else
        drawstring(F("NO HIGHSCORE"), 0, 30);

      byte level3 = EEPROM.read(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_LEVEL_S3);
      byte ship3 = EEPROM.read(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_SHIP_S3);
      unsigned int score3 = 0;
      EEPROM.get(EEPROM_STORAGE_SPACE_START + EEPROM_HRDC_START + OFFSET_HSCORE_S3, score3);

      if (level3 != 0 && score3 != 0)
      {
        drawnumber(level3, 0, 40);
        drawshipname(ship3, 30, 40);
        drawnumber(score3, 60, 40);
      } else
        drawstring(F("NO HIGHSCORE"), 0, 40);
#else
      drawstring(F("EEPROM DISABLED"), 0, 0);
#endif

      if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
        gamestate = MENU_SCREEN;
      break;
  }

#ifdef SCREEN_MIRRORING
  Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
#endif
  arduboy.display();
}


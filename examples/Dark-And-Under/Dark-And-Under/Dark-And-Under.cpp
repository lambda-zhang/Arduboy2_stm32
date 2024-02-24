// ======================
#include <Arduboy2.h>
#include "src/utils/Arduboy2Ext.h"
#include "Enums.h"
#include "src/levels/Level.h"
#include "images/Images.h"
#include "src/entities/Player.h"
#include "src/entities/Enemy.h"
#include "src/entities/Item.h"
#include "src/levels/MapData.h"
#include "src/controllers/PlayerController.h"
#include "src/controllers/EnemyController.h"
#include "src/fonts/Font3x5.h"
#include "src/utils/Utils.h"
#include "src/utils/EnemyNames.h"
#include "src/levels/MapData.h"

void initialiseGame();
void initialiseLevel(Player *myHero, Level *myLevel, const uint8_t *level);
uint16_t playLoop();
uint16_t inventoryLoop();
uint16_t itemLoop();
void displaySplash();
void displayLogo();
uint16_t battleLoop();
void displayEndOfGame(bool playerDead);
uint16_t displayLevelUp();
void displayNextLevel();
#ifdef USE_LARGE_MAP
void drawMapAndStatistics(Player *player, Level *myLevel, boolean smallMap);
#endif
#ifndef USE_LARGE_MAP
void drawMapAndStatistics(Player *player, Level *myLevel);
#endif
void drawDirectionIndicator(Player *myHero);
void drawLevelDescription(Level *level);
void printStatistic(const __FlashStringHelper * str, const uint8_t stat);
GameState battleEnemyAttacks(void);
GameState battleEnemyAttacksInit(void);
GameState battleEnemyDies(void);
GameState battlePlayerDecides(void);
GameState battlePlayerAttacks(void);
GameState battlePlayerDefends(void);
GameState battlePlayerCastsSpell(void);
uint8_t loadEnemies(const uint8_t * level, Enemy * enemies, uint8_t idx, uint8_t max);
uint8_t loadItems(const uint8_t *level, Item * items, uint8_t idx, uint8_t max);

Arduboy2Ext arduboy;
Font3x5 font3x5 = Font3x5();

Item items[NUMBER_OF_ITEMS];
Item doors[NUMBER_OF_DOORS];
Enemy enemies[NUMBER_OF_ENEMIES];

uint8_t attackingEnemyIdx = 0;

const uint8_t *levels[] =    { level_00, level_01, level_02, level_03, level_04, level_05, level_06, level_07, level_08, level_09 };
const uint8_t *map_images[] = { visionBack, closeWallFront, closeGateLocked, closeDoorLocked, closeDoorUnlocked, closeWallLeft, closeWallRight, closeGateLeft, closeGateRight,
                                midWallFront, midDoorLocked, midDoorLevelLocked, midDoorLevelUnlocked, midWallLeft, midWallRight, midGateLeft, midGateRight,
                                farGateLocked, farDoorLocked, farDoorUnlocked, farWallLeft, farWallRight };


// Inventory settings ..

const uint8_t *inventory_images[] = { NULL, inv_key, inv_potion, inv_scroll, inv_shield, inv_sword };
const Point inventory_Coords[] = { INVENTORY_POSITION_1, INVENTORY_POSITION_2, INVENTORY_POSITION_3, INVENTORY_POSITION_4, INVENTORY_POSITION_5 };
uint8_t inventory_selection = 0;
uint8_t inventory_action = 0;


// Enemy details ..

const uint8_t *enemy_images[] = { enemy_occular, enemy_skeleton, enemy_sparkat, enemy_wraith, enemy_dragon, enemy_rat, enemy_slime };
const uint8_t *enemy_masks[] = { enemy_occular_Mask, enemy_skeleton_Mask, enemy_sparkat_Mask, enemy_wraith_Mask, enemy_dragon_Mask, enemy_rat_Mask, enemy_slime_Mask };


// Item details ..

const uint8_t *item_images[] = { NULL, item_key, item_potion, item_mascroll, item_shield, item_sword };
uint8_t itemAction = 0;
uint8_t savedItem = 0;

GameState gameState = GameState::Splash;
GameState savedState = GameState::Splash;

Level myLevel;
Player myHero;

SplashButtons splashStatus = SplashButtons::Play;
FightButtons fightButton = FightButtons::Attack;
#ifdef LEVEL_UP_SELECT_PRIZE
LevelUpButtons levelUpButton = LevelUpButtons::None;
#endif

uint8_t level = 0;          // Current map
uint8_t playerLevel = 1;    // Levelup level


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Setup ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void setup() {

  arduboy.boot();
  arduboy.flashlight();
  arduboy.setFrameRate(30);

  #ifdef USE_SOUNDS
  arduboy.audio.begin();
  #endif

  arduboy.initRandomSeed();

  #ifdef SAVE_GAME
  initEEPROM();
  #endif

  initialiseGame();

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Main loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void loop() {

  uint16_t delayLength = 0;
  if (!(arduboy.nextFrame())) return;

  arduboy.pollButtons();

  switch (gameState) {

    #ifdef ALTERNATIVE_ENDING 
      case GameState::InvalidSeq:
      font3x5.setCursor(22, 22);
      font3x5.print(F("LEVELS MUST BE PLAYED\n    IN SEQUENCE !"));
      break;
    #endif

    case GameState::InitGame:
      level = 0;
      gameState = GameState::InitLevel;
      break;

    case GameState::InitLevel:
      initialiseLevel(&myHero, &myLevel, levels[level]);
      break;

    case GameState::Move:
    case GameState::ItemIgnore:
      delayLength = playLoop();
      break;

    case GameState::InventorySelect:
    case GameState::InventoryAction:
      delayLength = inventoryLoop();
      break;

    case GameState::ItemSelect:
      delayLength = itemLoop();
      break;

    case GameState::Splash:
      displaySplash();
      break;

    case GameState::About:
      displayLogo();
      break;

    case GameState::Battle_EnemyAttacks_Init:
    case GameState::Battle_EnemyAttacks:
    case GameState::Battle_EnemyDies:
    case GameState::Battle_PlayerDecides:
    case GameState::Battle_PlayerAttacks:
    case GameState::Battle_PlayerDefends:
    case GameState::Battle_PlayerCastsSpell:
      delayLength = battleLoop();
      break;

    case GameState::Battle_PlayerDies:
      displayEndOfGame(true);
      break;

    case GameState::LevelUp:
      delayLength = displayLevelUp();
      break;

    case GameState::NextLevel:
      displayNextLevel();
      break;

    case GameState::EndOfGame:
      displayEndOfGame(false);
      break;

    #ifdef USE_LARGE_MAP
    case GameState::DisplayLargeMap:
      displayLargeMap();
      break;
    #endif

    default:
      break;

  }

  arduboy.display(true);
  delay(delayLength);

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Draw the outside frame ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */ 
const uint8_t frameHLineLookup[] PROGMEM = { 0, 2, 61, 63 };
const uint8_t frameVLineLookup[] PROGMEM = { 0, 2, 125, 127 };
 
void drawFrames() {

  Sprites::drawOverwrite(0, 0, frameTopLH, 0);
  Sprites::drawOverwrite(120, 0, frameTopRH, 0);
  Sprites::drawOverwrite(0, 56, frameBotLH, 0);
  Sprites::drawOverwrite(120, 56, frameBotRH, 0);
  
  for(uint8_t i = 0; i < 4; ++i)
  {
    arduboy.drawFastHLine(8, pgm_read_byte(&frameHLineLookup[i]), 112);
    arduboy.drawFastVLine(pgm_read_byte(&frameVLineLookup[i]), 8, 48);
  }
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Level Up Handler
 *
 *  Display the 'Level Up' graphic and award a point.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint16_t displayLevelUp() {

  drawFrames();
  arduboy.drawCompressed(66, 4, frames_inside, WHITE);

  #ifdef USE_LARGE_MAP
  drawMapAndStatistics(&myHero, &myLevel, true);
  #endif
  #ifndef USE_LARGE_MAP
  drawMapAndStatistics(&myHero, &myLevel);
  #endif
  drawDirectionIndicator(&myHero);
  drawLevelDescription(&myLevel);

  arduboy.drawCompressed(23, 5, levelUp, WHITE);

  #ifndef LEVEL_UP_SELECT_PRIZE

    font3x5.setCursor(20, 40);
    font3x5.print(F("LEVEL "));
    font3x5.print(playerLevel);
    playerLevel++;

    font3x5.setCursor(18, 47);
    font3x5.print(F("YOU GAIN"));
    font3x5.setCursor(26, 54);

    #ifdef LEVEL_UP_INC_HP
      switch (random(0, 3)) {

        case 0:
          font3x5.print(F("1 HP"));
          myHero.setHitPoints(myHero.getHitPoints() + 1);
          break;

        case 1:
          font3x5.print(F("1 AP"));
          myHero.setAttackPower(myHero.getAttackPower() + 1);
          break;

        case 2:
          font3x5.print(F("1 DF"));
          myHero.setDefence(myHero.getDefence() + 1);
          break;


      }
    #endif

    #ifndef LEVEL_UP_INC_HP
      switch (random(0, 2)) {

        case 0:
          font3x5.print(F("1 AP"));
          myHero.setAttackPower(myHero.getAttackPower() + 1);
          break;

        case 1:
          font3x5.print(F("1 DF"));
          myHero.setDefence(myHero.getDefence() + 1);
          break;


      }
    #endif

    gameState = GameState::Move;
    return LEVEL_UP_DELAY;

  #endif

  #ifdef LEVEL_UP_SELECT_PRIZE

    uint8_t buttons = arduboy.justPressedButtons();

    switch (levelUpButton) {

      case LevelUpButtons::None:

        font3x5.setCursor(20, 42);
        font3x5.print(F("LEVEL "));
        font3x5.print(playerLevel);
        font3x5.setCursor(9, 50);
        font3x5.print(F("CHOOSE BONUS"));
        playerLevel++;

        levelUpButton = LevelUpButtons::AP;
        return LEVEL_UP_DELAY;

      default:
        font3x5.setCursor(23, 42);
        font3x5.print(F("ATTACK"));
        font3x5.setCursor(23, 50);
        font3x5.print(F("DEFENCE"));
        break;

    }

    if (levelUpButton == LevelUpButtons::AP) {
      Sprites::drawSelfMasked(17, 43, hMarker, 0);
    }
    else {
      Sprites::drawSelfMasked(17, 51, hMarker, 0);
    }

    if ((buttons & UP_BUTTON_MASK) && levelUpButton == LevelUpButtons::DF)             { levelUpButton = LevelUpButtons::AP; }
    else if ((buttons & DOWN_BUTTON_MASK) && levelUpButton == LevelUpButtons::AP)      { levelUpButton = LevelUpButtons::DF; }
    else if ((buttons & A_BUTTON_MASK) && levelUpButton == LevelUpButtons::AP)         { myHero.setAttackPower(myHero.getAttackPower() + 1); levelUpButton = LevelUpButtons::None, gameState = GameState::Move; }
    else if ((buttons & A_BUTTON_MASK) && levelUpButton == LevelUpButtons::DF)         { myHero.setDefence(myHero.getDefence() + 1); levelUpButton = LevelUpButtons::None, gameState = GameState::Move; }

  #endif

  return 0;

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Next Level Handler
 *
 *  Display the 'Next Level' graphic and initialise the next level ready for play.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void displayNextLevel() {

  drawFrames();
  arduboy.drawCompressed(64, 4, endOfLevel, WHITE);

  font3x5.setHeight(7);
  font3x5.setCursor(10, 7);
  font3x5.print(F("YOU CAN HEAR\nA DISTANT\nYET CLOSER\nDRAGON ROAR\nAS YOU STEP\nTHROUGH THE\nDOOR..."));
  font3x5.setHeight(8);

  uint8_t buttons = arduboy.justPressedButtons();

  if (buttons) {

    level++;
    gameState = GameState::Move;
    initialiseLevel(&myHero, &myLevel, levels[level]);

  }

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  End of Game Handler
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void displayEndOfGame(bool playerDead) {

  drawFrames();

  if (playerDead) {

    arduboy.drawCompressed(66, 4, frames_inside, WHITE);
    Sprites::drawSelfMasked(DIRECTION_X_OFFSET, DIRECTION_Y_OFFSET, fight_icon, 0);
    #ifdef USE_LARGE_MAP
    drawMapAndStatistics(&myHero, &myLevel, true);
    #endif
    #ifndef USE_LARGE_MAP
    drawMapAndStatistics(&myHero, &myLevel);
    #endif

    arduboy.drawCompressed(16, 6, gameOver, WHITE);

  }
  else {

  #ifndef ALTERNATIVE_ENDING 
    arduboy.drawCompressed(43, 4, victory, WHITE);
    font3x5.setCursor(9, 8);
    font3x5.print(F("WELL DONE!\nTHE RICHES\nUNDER THE\nMOUNTAIN\nARE YOURS\nNOW!"));
  #endif

  #ifdef ALTERNATIVE_ENDING 
    arduboy.drawCompressed(ALTERNATE_ENDING_IMAGE_POS_X, ALTERNATE_ENDING_IMAGE_POS_Y, alternate_image, WHITE);
    font3x5.setCursor(ALTERNATE_ENDING_TEXT_POS_X, ALTERNATE_ENDING_TEXT_POS_Y);
    font3x5.print(FlashString(endingText));
    EEPROM.update(EEPROM_SEQ_START, ALTERNATIVE_ENDING_PREFIX);
    EEPROM.update(EEPROM_SEQ_START + 1, ALTERNATIVE_ENDING_SEQ);
  #endif

  }

  uint8_t buttons = arduboy.justPressedButtons();

  if (buttons & SELECT_BUTTON_MASK) {

    initialiseGame();
    gameState = GameState::Splash;

  }

}
// ======================

#define VISION_X_OFFSET   3
#define VISION_Y_OFFSET   4

const int8_t offsetXTable[] = { 0, 1, 0, -1 };
const int8_t offsetYTable[] = { -1, 0, 1, 0 };


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Draw Player Vision.
 *
 *  Renders the dungeon with any doors, enemies and items that are in view.
 *
 *  To save space elsewhere, it automatically calls the drawMapAndStatistics() function to render the map and statistics panel
 *  as these are always rendered when the dungeon is rendered.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void drawPlayerVision(Player *myHero, Level *myLevel) {

  bool horizon3Plus = false;
  bool horizon2Plus = false;

  int8_t farLeftX = 0;
  int8_t farFrontX = 0;
  int8_t farRightX = 0;

  int8_t farLeftY = 0;
  int8_t farFrontY = 0;
  int8_t farRightY = 0;

  int8_t middleLeftX = 0;
  int8_t middleFrontX = 0;
  int8_t middleRightX = 0;

  int8_t middleLeftY = 0;
  int8_t middleFrontY = 0;
  int8_t middleRightY = 0;

  int8_t closeLeftX = 0;
  int8_t closeFrontX = 0;
  int8_t closeRightX = 0;

  int8_t closeLeftY = 0;
  int8_t closeFrontY = 0;
  int8_t closeRightY = 0;

  uint8_t playerX = myHero->getX();
  uint8_t playerY = myHero->getY();

  switch (myHero->getDirection()) {

    case Direction::North:

      horizon3Plus = (playerY - 3 >= 0);
      horizon2Plus = (playerY - 2 >= 0);

      farFrontX = 0;      farFrontY = -3;
      farLeftX = -1;      farLeftY = -2;
      farRightX = 1;      farRightY = -2;

      middleFrontX = 0;   middleFrontY = -2;
      middleLeftX = -1;   middleLeftY = -1;
      middleRightX = 1;   middleRightY = -1;

      closeFrontX = 0;    closeFrontY = -1;
      closeLeftX = -1;    closeLeftY = 0;
      closeRightX = 1;    closeRightY = 0;

      break;

    case Direction::East:

      horizon3Plus = (playerX + 3 >= 0);
      horizon2Plus = (playerX + 2 >= 0);

      farFrontX = 3;      farFrontY = 0;
      farLeftX = 2;       farLeftY = -1;
      farRightX = 2;      farRightY = 1;

      middleFrontX = 2;   middleFrontY = 0;
      middleLeftX = 1;    middleLeftY = -1;
      middleRightX = 1;   middleRightY = 1;

      closeFrontX = 1;    closeFrontY = 0;
      closeLeftX = 0;     closeLeftY = -1;
      closeRightX = 0;    closeRightY = 1;

      break;

    case Direction::South:

      horizon3Plus = (playerY + 3 >= 0);
      horizon2Plus = (playerY + 2 >= 0);

      farFrontX = 0;      farFrontY = 3;
      farLeftX = 1;       farLeftY = 2;
      farRightX = -1;     farRightY = 2;

      middleFrontX = 0;   middleFrontY = 2;
      middleLeftX = 1;    middleLeftY = 1;
      middleRightX = -1;  middleRightY = 1;

      closeFrontX = 0;    closeFrontY = 1;
      closeLeftX = 1;     closeLeftY = 0;
      closeRightX = -1;   closeRightY = 0;

      break;

    case Direction::West:

      horizon3Plus = (playerX - 3 >= 0);
      horizon2Plus = (playerX - 2 >= 0);

      farFrontX = -3;     farFrontY = 0;
      farLeftX = -2;      farLeftY = 1;
      farRightX = -2;     farRightY = -1;

      middleFrontX = -2;  middleFrontY = 0;
      middleLeftX = -1;   middleLeftY = 1;
      middleRightX = -1;  middleRightY = -1;

      closeFrontX = -1;   closeFrontY = 0;
      closeLeftX = 0;     closeLeftY = 1;
      closeRightX = 0;    closeRightY = -1;

      break;

    default: break;

  }

  drawFrames();
  arduboy.drawCompressed(66, 4, frames_inside, WHITE);
  Sprites::drawOverwrite(VISION_X_OFFSET + 1, VISION_Y_OFFSET, map_images[MAP_IMAGE_BACK], 0);


  // Far front wall ..

  if (horizon3Plus) {

    MapElement mapElement = (MapElement)myLevel->getMapElement(playerX + farFrontX, playerY + farFrontY, false);

    int8_t imageIndex = 0;
    int8_t xOffset = 0;
    int8_t yOffset = 0;

    if (mapElement > MapElement::Floor) {

      switch (mapElement) {

      case MapElement::LockedGate:
      case MapElement::SelfLockingDoor:
          imageIndex = MAP_IMAGE_FAR_GATE_LOCKED;
          xOffset = 27;
          yOffset = 26;
          break;

        case MapElement::LockedDoor:
          imageIndex = MAP_IMAGE_FAR_DOOR_LOCKED;
          xOffset = 29;
          yOffset = 25;
          break;

        case MapElement::UnlockedDoor:
          imageIndex = MAP_IMAGE_FAR_DOOR_UNLOCKED;
          xOffset = 29;
          yOffset = 25;
          break;

        default: break;

      }

      for (uint8_t i = VISION_X_OFFSET + 1; i < VISION_X_OFFSET + 62; ++i) {
        arduboy.drawPixel(i, VISION_Y_OFFSET + 27 + (i %2), WHITE);
      }

      if (imageIndex > 0) {
        Sprites::drawOverwrite(VISION_X_OFFSET + xOffset, VISION_Y_OFFSET + yOffset, map_images[imageIndex], 0);
      }

    }

  }


  // Far left wall ..

  if (horizon2Plus) {
    if ((MapElement)myLevel->getMapElement(playerX + farLeftX, playerY + farLeftY, false) > MapElement::Floor) {
     Sprites::drawOverwrite(VISION_X_OFFSET + 1, VISION_Y_OFFSET + 23, map_images[MAP_IMAGE_FAR_LEFT], 0);
    }
  }


  // Far right wall ..

  if (horizon2Plus) {
    if ((MapElement)myLevel->getMapElement(playerX + farRightX, playerY + farRightY, false) > MapElement::Floor) {
     Sprites::drawOverwrite(VISION_X_OFFSET + 35, VISION_Y_OFFSET + 23, map_images[MAP_IMAGE_FAR_RIGHT], 0);
    }
  }


  // Mid front wall ..

  bool renderMiddleFront = false;

  if (horizon2Plus) {

    int8_t imageIndex = 0;
    int8_t xOffset = 0;
    int8_t yOffset = 0;

    MapElement mapElement = (MapElement)myLevel->getMapElement(playerX + middleFrontX, playerY + middleFrontY, false);

    if (mapElement > MapElement::Floor) {

      renderMiddleFront = (horizon2Plus && (mapElement > MapElement::Floor));

      switch (mapElement) {

        case MapElement::LockedGate:
        case MapElement::SelfLockingDoor:
          imageIndex = MAP_IMAGE_MID_GATE_LOCKED;
          xOffset = 24;
          yOffset = 23;
          break;

        case MapElement::LockedDoor:
          imageIndex = MAP_IMAGE_MID_DOOR_LOCKED;
          xOffset = 27;
          yOffset = 25;
          break;

        case MapElement::UnlockedDoor:
          imageIndex = MAP_IMAGE_MID_DOOR_UNLOCKED;
          xOffset = 27;
          yOffset = 25;
          break;

        default: break;

      }

      Sprites::drawOverwrite(VISION_X_OFFSET + 1, VISION_Y_OFFSET + 23, map_images[MAP_IMAGE_MID_FRONT], 0);

      if (imageIndex > 0) {
        Sprites::drawOverwrite(VISION_X_OFFSET + xOffset, VISION_Y_OFFSET + yOffset, map_images[imageIndex], 0);
      }

    }

  }


  // Mid left wall ..

  MapElement mapElement = myLevel->getMapElement(playerX + middleLeftX, playerY + middleLeftY, false);
  if (mapElement == MapElement::Wall) {
    Sprites::drawOverwrite(VISION_X_OFFSET + 1, VISION_Y_OFFSET + 14, map_images[MAP_IMAGE_MID_LEFT], 0);
  }
  else if (mapElement == MapElement::LockedGate || mapElement == MapElement::SelfLockingDoor) {
    Sprites::drawOverwrite(VISION_X_OFFSET + 15, VISION_Y_OFFSET + 15, map_images[MAP_IMAGE_MID_GATE_LEFT], 0);
  }


  // Mid right wall ..

  mapElement = myLevel->getMapElement(playerX + middleRightX, playerY + middleRightY, false);
  if (mapElement == MapElement::Wall) {
    Sprites::drawOverwrite(VISION_X_OFFSET + 39, VISION_Y_OFFSET + 14, map_images[MAP_IMAGE_MID_RIGHT], 0);
  }
  else if (mapElement == MapElement::LockedGate || mapElement == MapElement::SelfLockingDoor) {
    Sprites::drawOverwrite(VISION_X_OFFSET + 39, VISION_Y_OFFSET + 15, map_images[MAP_IMAGE_MID_GATE_RIGHT], 0);
  }


  // Close front wall ..

  mapElement = (MapElement)myLevel->getMapElement(playerX + closeFrontX, playerY + closeFrontY, false);
  bool renderCloseFront = (mapElement > MapElement::Floor);

  if (mapElement > MapElement::Floor) {

    int8_t imageIndex = -1;     //TODO: CHanged to 0 and if (imageIndex > 0) .. added 4 bytes
    int8_t xOffset = 0;
    int8_t yOffset = 0;

    switch (mapElement) {

      case MapElement::Wall:
        imageIndex = MAP_IMAGE_CLOSE_FRONT;
        xOffset = 0;
        yOffset = 14;
        break;

      case MapElement::LockedGate:
      case MapElement::SelfLockingDoor:
        imageIndex = MAP_IMAGE_CLOSE_GATE_LOCKED;
        xOffset = 15;
        yOffset = 14;
        break;

      case MapElement::LockedDoor:
        imageIndex = MAP_IMAGE_CLOSE_DOOR_LOCKED;
        xOffset = 22;
        yOffset = 21;
        break;

      case MapElement::UnlockedDoor:
        imageIndex = MAP_IMAGE_CLOSE_DOOR_UNLOCKED;
        xOffset = 22;
        yOffset = 21;

      default: break;

    }

    Sprites::drawOverwrite(VISION_X_OFFSET, VISION_Y_OFFSET + 14, closeWallFront, 0);
    if (imageIndex >= 0) {
      Sprites::drawOverwrite(VISION_X_OFFSET + xOffset, VISION_Y_OFFSET + yOffset, map_images[imageIndex], 0);
    }

  }


  // Close left wall ..

  mapElement = myLevel->getMapElement(playerX + closeLeftX, playerY + closeLeftY, false);
  if (mapElement == MapElement::Wall) {
    Sprites::drawOverwrite(VISION_X_OFFSET, VISION_Y_OFFSET, map_images[MAP_IMAGE_CLOSE_LEFT], 0);
  }
  else if (mapElement == MapElement::LockedGate || mapElement == MapElement::SelfLockingDoor) {
    Sprites::drawOverwrite(VISION_X_OFFSET, VISION_Y_OFFSET, map_images[MAP_IMAGE_CLOSE_GATE_LEFT], 0);
  }


  // Close right wall ..

  mapElement = myLevel->getMapElement(playerX + closeRightX, playerY + closeRightY, false);
  if (mapElement == MapElement::Wall) {
    Sprites::drawOverwrite(VISION_X_OFFSET + 48, VISION_Y_OFFSET, map_images[MAP_IMAGE_CLOSE_RIGHT], 0);
  }
  else if (mapElement == MapElement::LockedGate || mapElement == MapElement::SelfLockingDoor) {
    Sprites::drawOverwrite(VISION_X_OFFSET + 49, VISION_Y_OFFSET, map_images[MAP_IMAGE_CLOSE_GATE_RIGHT], 0);
  }


  uint8_t selector = static_cast<uint8_t>(myHero->getDirection());
  bool rendered = false;

  if (!renderCloseFront) {

    for (uint8_t i = 0; i < NUMBER_OF_ITEMS; ++i) {

      Enemy enemy = enemies[i];

      if (enemy.getEnabled()) {

        int8_t offsetX = offsetXTable[selector] * 2;
        int8_t offsetY = offsetYTable[selector] * 2;

        if (enemy.getX() == playerX + offsetX && enemy.getY() == playerY + offsetY) {

          Sprites::drawOverwrite(27, 25, enemy_two_tiles, 0);
          rendered = true;
          break;

        }

      }

    }

  }

  if (!renderCloseFront && !renderMiddleFront && !rendered) {

    for (uint8_t i = 0; i < NUMBER_OF_ITEMS; ++i) {

      Enemy enemy = enemies[i];

      if (enemy.getEnabled()) {

        int8_t offsetX = offsetXTable[selector] * 3;
        int8_t offsetY = offsetYTable[selector] * 3;

        if (enemy.getX() == playerX + offsetX && enemy.getY() == playerY + offsetY) {

          Sprites::drawOverwrite(30, 28, enemy_three_tiles, 0);
          break;

        }

      }

    }

  }


  for (uint8_t i = 0; i < NUMBER_OF_ENEMIES; ++i) {

    Enemy enemy = enemies[i];

    if (enemy.getEnabled()) {

      int16_t deltaX = myHero->getX() - enemy.getX();
      int16_t deltaY = myHero->getY() - enemy.getY();

      if ((deltaY == 0 && absT(deltaX) == 1) ^ (deltaX == 0 && absT(deltaY) == 1)) {

        if (deltaX > 0) { myHero->setDirection(Direction::West); }
        else if (deltaX < 0) { myHero->setDirection(Direction::East); }
        else if (deltaY > 0) { myHero->setDirection(Direction::North); }
        else if (deltaY < 0) { myHero->setDirection(Direction::South); }

        EnemyType enemyType = enemy.getEnemyType();
        uint8_t offsetX = 6;  // Occular
        uint8_t offsetY = 5;

        if (enemyType == EnemyType::Skeleton)         { offsetX = 11; offsetY = 5;  }
        else if (enemyType == EnemyType::Sparkat)     { offsetX = 8;  offsetY = 10; }
        else if (enemyType == EnemyType::Wraith)      { offsetX = 16; offsetY = 3;  }
        else if (enemyType == EnemyType::Dragon)      { offsetX = 3;  offsetY = 5;  }
        else if (enemyType == EnemyType::Rat)         { offsetX = 23; offsetY = 16; }
        else if (enemyType == EnemyType::Slime)       { offsetX = 13; offsetY = 22; }

        arduboy.drawCompressed(offsetX, offsetY, enemy_masks[(uint8_t)enemyType], BLACK);
        arduboy.drawCompressed(offsetX, offsetY, enemy_images[(uint8_t)enemyType], WHITE);

        if (gameState == GameState::Move) gameState = GameState::Battle_EnemyAttacks_Init;
        attackingEnemyIdx = i;
        break;

      }

    }

    if (gameState == GameState::Move || gameState == GameState::ItemSelect) {

      Item item = items[i];

      if (item.getEnabled()) {

        uint8_t selector = static_cast<uint8_t>(myHero->getDirection());

        int8_t offsetX = offsetXTable[selector];
        int8_t offsetY = offsetYTable[selector];

        if (item.getX() == playerX + offsetX && item.getY() == playerY + offsetY) {

          ItemType itemType = item.getItemType();

          uint8_t offsetX = 23;  // Potion
          uint8_t offsetY = 19;

          if (itemType == ItemType::Key)          { offsetX = 20; offsetY = 20; }
          else if (itemType == ItemType::Scroll)  { offsetX = 20; offsetY = 18; }
          else if (itemType == ItemType::Shield)  { offsetX = 20; offsetY = 18; }
          else if (itemType == ItemType::Sword)   { offsetX = 20; offsetY = 18; }

          arduboy.fillRect(14, 11, 41, 43, BLACK);
          arduboy.fillRect(15, 12, 39, 41, WHITE);
          arduboy.drawCompressed(offsetX, offsetY, item_images[(uint8_t)itemType], BLACK);

          font3x5.setTextColor(BLACK);
          font3x5.setCursor(17, 12);
          font3x5.print((const __FlashStringHelper*)("YOU FOUND"));

          const __FlashStringHelper * text = nullptr;

          switch (itemType) {

            case ItemType::Key:
              text = (const __FlashStringHelper*)("SOME KEYS");
              break;

            case ItemType::Potion:
              text = (const __FlashStringHelper*)("HP POTION");
              break;

            case ItemType::Scroll:
              text = (const __FlashStringHelper*)("A SCROLL");
              break;

            case ItemType::Shield:
              text = (const __FlashStringHelper*)("A SHIELD");
              break;

            case ItemType::Sword:
              text = (const __FlashStringHelper*)(" A SWORD");
              break;

            default: break;

          }

          if(text != nullptr) {
            font3x5.setCursor(17, 46);
            font3x5.print(text);
          }

          font3x5.setTextColor(WHITE);
          gameState = GameState::ItemSelect;
          savedItem = i;
          break;

        }

      }

    }

  }

  #ifdef USE_LARGE_MAP
  drawMapAndStatistics(myHero, myLevel, true);
  #endif
  #ifndef USE_LARGE_MAP
  drawMapAndStatistics(myHero, myLevel);
  #endif

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Draw the Map and Statistics.
 *
 *  Was originally two separate functions however they are always rendered together.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
#ifndef USE_LARGE_MAP
#define MAP_X_OFFSET   98
#define MAP_Y_OFFSET   6
#endif

#ifdef USE_LARGE_MAP
void drawMapAndStatistics(Player *player, Level *myLevel, boolean smallMap) {
#endif
#ifndef USE_LARGE_MAP
void drawMapAndStatistics(Player *player, Level *myLevel) {
#endif

  uint8_t drawX = 0;
  uint8_t drawY = 0;

  #ifdef USE_LARGE_MAP
  uint8_t mapWidth = (smallMap ? 2 : 11);
  uint8_t mapHeight = (smallMap ? 3 : 5);
  uint8_t mapXOffset = (smallMap ? 98 : 6);
  uint8_t mapYOffset = (smallMap ? 6 : 5);
  #endif

  bool renderMapElement = false;

  #ifdef USE_LARGE_MAP
  for (int16_t mapY = player->getY() - mapHeight; mapY <= player->getY() + mapHeight; ++mapY) {
  #endif
  #ifndef USE_LARGE_MAP
  for (int16_t mapY = player->getY() - 3; mapY <= player->getY() + 3; ++mapY) {
  #endif

    #ifdef USE_LARGE_MAP
    for (int16_t mapX = player->getX() - mapWidth; mapX <= player->getX() + mapWidth; ++mapX) {
    #endif
    #ifndef USE_LARGE_MAP
    for (int16_t mapX = player->getX() - 2; mapX <= player->getX() + 2; ++mapX) {
    #endif

      #ifdef USE_LARGE_MAP
      if (mapX >= 0 && mapX < ((uint8_t)myLevel->getWidth() * MAP_TILE_WIDTH) && mapY >= 0 && mapY < ((uint8_t)myLevel->getHeight() * MAP_TILE_HEIGHT) && (smallMap ? !(drawX == 4 && drawY == 0) : ( !((drawX == 0 || drawX == 22) && drawY == 0) && !((drawX == 0 || drawX == 22) && drawY == 10) ) ) ) {
      #endif
      #ifndef USE_LARGE_MAP
      if (mapX >= 0 && mapX < ((uint8_t)myLevel->getWidth() * MAP_TILE_WIDTH) && mapY >= 0 && mapY < ((uint8_t)myLevel->getHeight() * MAP_TILE_HEIGHT) && !(drawX == 4 && drawY == 0) ) {
      #endif

        MapElement element = myLevel->getMapElement(mapX, mapY, false);

        if (element != MapElement::Wall) {


          // Is there an enemy standing here ?

          renderMapElement = true;

          for (uint8_t i = 0; i < NUMBER_OF_ENEMIES; ++i) {

            Enemy enemy = enemies[i];

            if (enemy.getEnabled() && enemy.getX() == mapX && enemy.getY() == mapY) {

              #ifdef USE_LARGE_MAP
              Sprites::drawSelfMasked(mapXOffset + (drawX * MAP_TILE_OFFSET), mapYOffset + (drawY * MAP_TILE_OFFSET), enemyMap, 0);
              #endif
              #ifndef USE_LARGE_MAP
              Sprites::drawSelfMasked(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET), MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET), enemyMap, 0);
              #endif
              renderMapElement = false;
              break;

            }

          }


          // Is there an item standing here ?

          if (renderMapElement) {

            for (uint8_t i = 0; i < NUMBER_OF_ITEMS; ++i) {

              Item item = items[i];

              if (item.getEnabled() && item.getX() == mapX && item.getY() == mapY) {

                #ifdef USE_LARGE_MAP
                Sprites::drawSelfMasked(mapXOffset + (drawX * MAP_TILE_OFFSET), mapYOffset + (drawY * MAP_TILE_OFFSET), itemMap, 0);
                #endif
                #ifndef USE_LARGE_MAP
                Sprites::drawSelfMasked(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET), MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET), itemMap, 0);
                #endif
                renderMapElement = false;
                break;

              }

            }

          }

          if (renderMapElement) {

            #ifdef USE_LARGE_MAP
            arduboy.fillRect(mapXOffset + (drawX * MAP_TILE_OFFSET), mapYOffset + (drawY * MAP_TILE_OFFSET), MAP_TILE_SIZE, MAP_TILE_SIZE, WHITE);
            #endif
            #ifndef USE_LARGE_MAP
            arduboy.fillRect(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET), MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET), MAP_TILE_SIZE, MAP_TILE_SIZE, WHITE);
            #endif

            switch (element) {

              case MapElement::LockedGate:
              case MapElement::LockedDoor:
              case MapElement::SelfLockingDoor:
                #ifdef USE_LARGE_MAP
//                arduboy.drawLine(mapXOffset + (drawX * MAP_TILE_OFFSET) + 1, mapYOffset + (drawY * MAP_TILE_OFFSET) + 1, mapXOffset + (drawX * MAP_TILE_OFFSET) + 1, mapYOffset + (drawY * MAP_TILE_OFFSET) + 2, BLACK);
                arduboy.drawFastVLine(mapXOffset + (drawX * MAP_TILE_OFFSET) + 1, mapYOffset + (drawY * MAP_TILE_OFFSET) + 1, 2, BLACK);
                #endif
                #ifndef USE_LARGE_MAP
//                arduboy.drawLine(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET) + 1, MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET) + 1, MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET) + 1, MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET) + 2, BLACK);
                arduboy.drawFastVLine(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET) + 1, MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET) + 1, 2, BLACK);
                #endif
                break;

              case MapElement::UnlockedDoor:
                #ifdef USE_LARGE_MAP
//                arduboy.drawLine(mapXOffset + (drawX * MAP_TILE_OFFSET) + 2, mapYOffset + (drawY * MAP_TILE_OFFSET) + 1, mapXOffset + (drawX * MAP_TILE_OFFSET) + 2, mapYOffset + (drawY * MAP_TILE_OFFSET) + 2, BLACK);
                arduboy.drawFastVLine(mapXOffset + (drawX * MAP_TILE_OFFSET) + 2, mapYOffset + (drawY * MAP_TILE_OFFSET) + 1, 2, BLACK);
                #endif
                #ifndef USE_LARGE_MAP
//                arduboy.drawLine(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET) + 2, MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET) + 1, MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET) + 2, MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET) + 2, BLACK);
                arduboy.drawFastVLine(MAP_X_OFFSET + (drawX * MAP_TILE_OFFSET) + 2, MAP_Y_OFFSET + (drawY * MAP_TILE_OFFSET) + 1, 2, BLACK);
                #endif
                break;

                default: break;

            }

          }

        }

      }

      ++drawX;

    }

    drawX = 0;
    ++drawY;

  }


  // Render player ..

  #ifdef USE_LARGE_MAP
  {
    uint8_t x = 0;
    uint8_t y = 0;

    if (smallMap) {

      switch (player->getDirection()) {

        case Direction::North:
          x = 11; y = 15;
          break;

        case Direction::East:
          x = 12; y = 16;
          break;

        case Direction::South:
          x = 11; y = 17;
          break;

        case Direction::West:
          x = 10; y = 16;
          break;

        default: break;

      }

    }
    else {

      switch (player->getDirection()) {

        case Direction::North:
          x = 56; y = 25;
          break;

        case Direction::East:
          x = 57; y = 26;
          break;

        case Direction::South:
          x = 56; y = 27;
          break;

        case Direction::West:
          x = 55; y = 26;
          break;

        default: break;

      }

    }

    arduboy.drawFastHLine(mapXOffset + x, mapYOffset + y, 2, BLACK);
    arduboy.drawFastHLine(mapXOffset + x, mapYOffset + y + 1, 2, BLACK);

  }
  #endif
  #ifndef USE_LARGE_MAP

  { 
    uint8_t x = 0;
    uint8_t y = 0;

    switch (player->getDirection()) {

      case Direction::North:
        x = 11; y = 15;
        break;

      case Direction::East:
        x = 12; y = 16;
        break;

      case Direction::South:
        x = 11; y = 17;
        break;

      case Direction::West:
        x = 10; y = 16;
        break;

      default: break;

    }

    arduboy.drawFastHLine(MAP_X_OFFSET + x, MAP_Y_OFFSET + y, 2, BLACK);
    arduboy.drawFastHLine(MAP_X_OFFSET + x, MAP_Y_OFFSET + y + 1, 2, BLACK);

  }
  #endif


  // Render statistics ..

  #ifdef USE_LARGE_MAP
  if (smallMap) {
  #endif
    font3x5.setCursor(70, 8);
    printStatistic((const __FlashStringHelper*)("HP  "), player->getHitPoints());
    printStatistic((const __FlashStringHelper*)("\nAP  "), player->getAttackPower());
    printStatistic((const __FlashStringHelper*)("\nDF  "), player->getDefence());
    printStatistic((const __FlashStringHelper*)("\nXP  "), player->getExperiencePoints());
  #ifdef USE_LARGE_MAP
  }
  #endif

}


/* -----------------------------------------------------------------------------------------------------------------------------
*  Print Statistic
* -----------------------------------------------------------------------------------------------------------------------------
*/
void printStatistic(const __FlashStringHelper * str, const uint8_t stat) {

  font3x5.print(str);
  if (stat < 10) font3x5.print(F(" "));
  font3x5.print(stat);

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Draw Direction Indicator
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void drawDirectionIndicator(Player *myHero) {

  Sprites::drawSelfMasked(DIRECTION_X_OFFSET, DIRECTION_Y_OFFSET, direction_images, (uint8_t)myHero->getDirection());

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Render Level Description
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void drawLevelDescription(Level *level) {

  font3x5.setCursor(80,44);
  font3x5.print(level->getTitleLine1());
  font3x5.print(F("\n"));
  font3x5.print(level->getTitleLine2());

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Render Enemy Hit Points Bar
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void drawEnemyHitPointsBar(uint8_t hitPoints, uint8_t hitPointsMax) {

  arduboy.drawCompressed(3, 49, fight_HP_bar_Mask, BLACK);
  arduboy.drawCompressed(3, 49, fight_HP_bar, WHITE);

  if(hitPoints == 0)
    return;

  const uint32_t hp = static_cast<uint32_t>(hitPoints) << 16; // U16x16
  const uint16_t hpMax = static_cast<uint16_t>(hitPointsMax) << 8; // U8x8
  const uint32_t divResult = hp / hpMax; // U8x8
  const uint32_t mulResult = divResult * (10 << 8); // U16x16
  const uint8_t resultAsInt = static_cast<uint8_t>(mulResult >> 16); // U8x0
  arduboy.drawRect(17, 54, resultAsInt, 2);

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Render Splash Screen
 *
 *  The player can choose between starting a new game or viewing the credits.
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void displaySplash() {

  drawFrames();
  arduboy.drawCompressed(8, 4, splash, WHITE);

  if (splashStatus == SplashButtons::Play) {
    Sprites::drawSelfMasked(25, 54, hMarker, 0);
  }
  else {
    Sprites::drawSelfMasked(63, 54, hMarker, 0);
  }

  uint8_t buttons = arduboy.justPressedButtons();

  if (buttons & LEFT_BUTTON_MASK)              { splashStatus = SplashButtons::Play; }
  if (buttons & RIGHT_BUTTON_MASK)             { splashStatus = SplashButtons::About; }

  if (buttons & SELECT_BUTTON_MASK) {

    if (splashStatus == SplashButtons::Play) {
      gameState = GameState::InitGame;
    }
    else {
      gameState = GameState::About;
    }

  }

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Display Garage Collective Logo
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void displayLogo() {

  drawFrames();

  arduboy.drawFastHLine(42, 2, 26, BLACK);
  arduboy.drawFastHLine(42, 61, 26, BLACK);
  arduboy.drawCompressed(42, 0, garCol, WHITE);

  font3x5.setCursor(8, 24);
  font3x5.print(F("CODE\nSIMON\nHOLMES"));

  font3x5.setCursor(90, 24);
  font3x5.print(F("     ART\n   CYRIL\nGUICHARD"));

  uint8_t buttons = arduboy.justPressedButtons();

  if (buttons & BACK_BUTTON_MASK) {
    gameState = GameState::Splash;
  }

}

// ======================

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Battle Loop
 *
 *  GameStates:
 *
 *  Battle_EnemyAttacks_Init -    Displays the initial '{enemy} attacks !' message and prepares for and enemy attck.
 *  Battle_EnemyAttacks -         Displays the dice animation and inflicts damage to the player.
 *  Battle_PlayerDecides -        Presents the players battle options including attack, defend, cast a spell ..
 *  Battle_PlayerAttacks -        Throws the dice and inflicts damage on the enemy.
 *  Battle_PlayerDefends -        Inflicts 1 point of damage on the enemy and randomly gains player hit points.
 *  Battle_PlayerCastsSpell -     Inflicts 5 points of damage on the enemy.
 *  Battle_EnemyDies -            Handles and end of battel where the enemy dies.
 *
 *  Returns delay in milliseconds to wait.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint16_t battleLoop() {

  drawPlayerVision(&myHero, &myLevel);
  Sprites::drawSelfMasked(DIRECTION_X_OFFSET, DIRECTION_Y_OFFSET, fight_icon, 0);

  font3x5.setCursor(80,44);

  const GameState priorState = gameState;
  switch (priorState) {
    case GameState::Battle_EnemyAttacks_Init:
      gameState = battleEnemyAttacksInit();
      break;

    case GameState::Battle_EnemyAttacks:
      gameState = battleEnemyAttacks();
      break;

    case GameState::Battle_EnemyDies:
      gameState = battleEnemyDies();
      break;

    case GameState::Battle_PlayerDecides:
      gameState = battlePlayerDecides();
      break;

    case GameState::Battle_PlayerAttacks:
      gameState = battlePlayerAttacks();
      break;

    case GameState::Battle_PlayerDefends:
      gameState = battlePlayerDefends();
      break;

    case GameState::Battle_PlayerCastsSpell:
      gameState = battlePlayerCastsSpell();
      break;

    default:
      break;
  }

  drawEnemyHitPointsBar(enemies[attackingEnemyIdx].getHitPoints(), enemies[attackingEnemyIdx].getHitPointsMax());
  return (priorState != GameState::Battle_PlayerDecides) ? FIGHT_DELAY : 0;

}

void damageEnemy(uint8_t attackingEnemyIdx, uint8_t hpLoss) {

    if (enemies[attackingEnemyIdx].getHitPoints() > hpLoss) {
        enemies[attackingEnemyIdx].setHitPoints(enemies[attackingEnemyIdx].getHitPoints() - hpLoss);
    }
    else {
        enemies[attackingEnemyIdx].setHitPoints(0);
        enemies[attackingEnemyIdx].setEnabled(false);
    }

}

GameState battleEnemyAttacksInit(void) {

  font3x5.print(getEnemyName(enemies[attackingEnemyIdx].getEnemyType()));
  font3x5.print(F("\nATTACKS!"));
  return GameState::Battle_EnemyAttacks;
  
}

GameState battleEnemyAttacks(void) {

  arduboy.drawCompressed(12, 12, fight_scratch_Mask, BLACK);
  arduboy.drawCompressed(12, 12, fight_scratch, WHITE);

  uint8_t hpLoss = random(0, ENEMY_MAX_ATTACK);
  font3x5.print(F("YOU TAKE\n"));
  font3x5.print(hpLoss);
  font3x5.print(F(" DAMAGE!"));
  font3x5.setCursor(33, 26);
  font3x5.print(hpLoss);
  myHero.takeDamage(hpLoss);

  return (myHero.isDead())
  ? GameState::Battle_PlayerDies
  : GameState::Battle_PlayerDecides;
}

GameState battleEnemyDies(void)
{
  arduboy.drawCompressed(18, 14, enemy_defeated_Mask, BLACK);
  arduboy.drawCompressed(18, 14, enemy_defeated, WHITE);

  uint8_t xp = enemies[attackingEnemyIdx].getExperiencePoints();
  font3x5.setCursor(32 + (xp < 10 ? 2 : 0), 26);
  font3x5.print(xp);
  myHero.setExperiencePoints(myHero.getExperiencePoints() + xp);

  if (myHero.getExperiencePoints() >= LEVEL_UP) {
    myHero.setExperiencePoints(myHero.getExperiencePoints() - LEVEL_UP);
    return GameState::LevelUp;
  }
  else {
    return GameState::Move;
  }
}

const uint8_t * const fight_actions[] PROGMEM =
{
  fight_actions_1,
  fight_actions_2,
  fight_actions_3,
  fight_actions_4,
};

GameState battlePlayerDecides(void)
{
  uint8_t buttons = arduboy.justPressedButtons();

  bool fightButtons[4];
  fightButtons[(uint8_t)FightButtons::Attack] = true;
  fightButtons[(uint8_t)FightButtons::Shield] = true;
  fightButtons[(uint8_t)FightButtons::Magic] = (myHero.getInventoryCount(ItemType::Scroll) > 0);
  fightButtons[(uint8_t)FightButtons::Potion] = (myHero.getInventoryCount(ItemType::Potion) > 0);
  
  constexpr uint8_t fightButtonsCount = sizeof(fightButtons) / sizeof(fightButtons[0]);

  for(uint8_t i = 0; i < fightButtonsCount; ++i) {

    if(fightButtons[i])
      arduboy.drawCompressed(80 + 11 * i, 44, static_cast<const uint8_t *>(pgm_read_ptr(&fight_actions[i])), WHITE);

  }
  
  Sprites::drawSelfMasked(81 + (((uint8_t)fightButton) * 11), 56, icnSelect, 0);

  if ((buttons & LEFT_BUTTON_MASK) && (uint8_t)fightButton > 0) {

    for (uint8_t i = (uint8_t)fightButton - 1; i < fightButtonsCount; --i) {
      if (fightButtons[i]) {
        fightButton = (FightButtons)i;
        break;
      }
    }

  }
  else if (buttons & RIGHT_BUTTON_MASK) {

    for (uint8_t i = (uint8_t)fightButton + 1; i < (uint8_t)FightButtons::Count; ++i) {
      if (fightButtons[i]) {
        fightButton = (FightButtons)i;
        break;
      }
    }

  }
  else if (buttons & BACK_BUTTON_MASK)  {
    savedState = GameState::Battle_PlayerDecides;
    return GameState::InventorySelect;
  }
  else if (buttons & SELECT_BUTTON_MASK)  {

    switch (fightButton) {

      case (FightButtons::Attack):
        return GameState::Battle_PlayerAttacks;

      case (FightButtons::Shield):
        return GameState::Battle_PlayerDefends;

      case (FightButtons::Magic):
        fightButton = FightButtons::Attack;
        return GameState::Battle_PlayerCastsSpell;

      case (FightButtons::Potion):
        fightButton = FightButtons::Attack;
        myHero.setHitPoints(myHero.getHitPoints() + INVENTORY_POTION_HP_INC);
        myHero.setInventory(myHero.getSlotNumber(ItemType::Potion), ItemType::None);
        break;

      default:
        break;

    }

  }

  return GameState::Battle_PlayerDecides;

}

GameState battlePlayerAttacks(void) {

  arduboy.drawCompressed(19, 19, fight_hero_strike_Mask, BLACK);
  arduboy.drawCompressed(19, 19, fight_hero_strike, WHITE);

  uint8_t hpLoss = random(1, myHero.getAttackPower() + 1);
  damageEnemy(attackingEnemyIdx, hpLoss);
  
  font3x5.print(F("YOU DEAL\n"));
  font3x5.print(hpLoss);
  font3x5.print(F(" DAMAGE!\n"));
  font3x5.setCursor(32, 24);
  font3x5.print(hpLoss);

  return (enemies[attackingEnemyIdx].getEnabled())
  ? GameState::Battle_EnemyAttacks_Init
  : GameState::Battle_EnemyDies;
  
}

GameState battlePlayerDefends(void) {

  arduboy.drawCompressed(12, 15, fight_hero_shield_Mask, BLACK);
  arduboy.drawCompressed(12, 15, fight_hero_shield, WHITE);

  const uint8_t enemyAttack = enemies[attackingEnemyIdx].getAttackPower();
  const uint8_t playerDefence = myHero.getDefence();

  uint8_t maxHP = (enemyAttack > playerDefence) ? (enemyAttack - playerDefence) : 2;
  if(maxHP < 2) maxHP = 2;
  if(maxHP > 10) maxHP = 10;
  const uint8_t hpLoss = random(0, maxHP);

  font3x5.print(F("TAKE "));
  font3x5.print(hpLoss);
  font3x5.print(F(" DMG\n"));
  font3x5.print(F("DEAL 1 DMG\n"));
  font3x5.setCursor(17, 35);
  font3x5.print(hpLoss);

  myHero.takeDamage(hpLoss);
  damageEnemy(attackingEnemyIdx, 1);

  if(myHero.isDead())
    return GameState::Battle_PlayerDies;

  return (enemies[attackingEnemyIdx].getEnabled())
  ? GameState::Battle_PlayerDecides
  : GameState::Battle_EnemyDies;
  
}

GameState battlePlayerCastsSpell(void) {

  arduboy.drawCompressed(12, 15, fight_hero_spell_Mask, BLACK);
  arduboy.drawCompressed(12, 15, fight_hero_spell, WHITE);

  damageEnemy(attackingEnemyIdx, PLAYER_CASTS_SPELL);
  myHero.setInventory(myHero.getSlotNumber(ItemType::Scroll), ItemType::None);

  return (enemies[attackingEnemyIdx].getEnabled())
  ? GameState::Battle_EnemyAttacks_Init
  : GameState::Battle_EnemyDies;
  
}// ======================

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Initialise Game Play.
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void initialiseGame() {

  #ifdef ALTERNATIVE_ENDING

    if (ALTERNATIVE_ENDING_SEQ != 1) {

      byte game = EEPROM.read(EEPROM_SEQ_START);
      byte seq = EEPROM.read(EEPROM_SEQ_START + 1);

      if (game != ALTERNATIVE_ENDING_PREFIX || seq != (ALTERNATIVE_ENDING_SEQ - 1)) {

        gameState = GameState::InvalidSeq;
        
      }

    }

  #endif

  myHero.setHitPoints(START_HP);
  myHero.setDefence(START_DF);
  myHero.setAttackPower(START_AP);

  myHero.setInventory(0, ItemType::None);
  myHero.setInventory(1, ItemType::None);
  myHero.setInventory(2, ItemType::None);
  myHero.setInventory(3, ItemType::Shield);
  myHero.setInventory(4, ItemType::Sword);

  playerLevel = 1;
  level = 0;

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Initialise Level.
 *
 *  Initialise the player, level and enemy details based on the current level.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void initialiseLevel(Player *myHero, Level *myLevel, const uint8_t *level) {

  uint8_t idx = 0;


  // Read level title ..

  memcpy_P(myLevel->getTitleLine1(), &level[idx], sizeof(char) * 11);
  idx += 11;
  memcpy_P(myLevel->getTitleLine2(), &level[idx], sizeof(char) * 11);
  idx += 11;

  myHero->setX(pgm_read_byte(&level[idx++]));
  myHero->setY(pgm_read_byte(&level[idx++]));
  myHero->setDirection((Direction)pgm_read_byte(&level[idx++]));

  myLevel->setWidth(pgm_read_byte(&level[idx++]));
  myLevel->setHeight(pgm_read_byte(&level[idx++]));


  // Create all enemies ..

  idx = loadEnemies(level, enemies, idx, NUMBER_OF_ENEMIES);


  // Create all items and doors ..

  idx = loadItems(level, items, idx, NUMBER_OF_ITEMS);
  idx = loadItems(level, doors, idx, NUMBER_OF_DOORS);

  myLevel->setLevel(level);
  myLevel->setDoors(doors);
  myLevel->setStartPos(idx);

  gameState = GameState::Move;

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Initialise Level - load items.
 *
 *  Initialise the item and door items from progmem using the 'idx' variable as an index reference.
 *
 *  Returns the 'idx' index reference so the next process can continue reading from that location onwards.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t loadItems(const uint8_t *level, Item * items, uint8_t idx, uint8_t max) {

  uint8_t numberOfItems = pgm_read_byte(&level[idx++]);

  for (uint8_t i = 0; i < max; ++i) {

    items[i].setEnabled(false);

    if (i < numberOfItems) {
      items[i].setItemType((ItemType)pgm_read_byte(&level[idx++]));
      items[i].setX(pgm_read_byte(&level[idx++]));
      items[i].setY(pgm_read_byte(&level[idx++]));
      items[i].setEnabled(true);
    }

  }

  return idx;

}



/* -----------------------------------------------------------------------------------------------------------------------------
 *  Initialise Level - load enemies.
 *
 *  Initialise the enemies items from progmem using the 'idx' variable as an index reference.
 *
 *  Returns the 'idx' index reference so the next process can continue reading from that location onwards.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint8_t loadEnemies(const uint8_t * level, Enemy * enemies, uint8_t idx, uint8_t max) {

  struct StatSet { uint8_t hp, ap, xp; bool moving; };

  static const StatSet loadEnemiesStats[] PROGMEM {
    { ENEMY_OCCULAR_HP, ENEMY_OCCULAR_AP, ENEMY_OCCULAR_XP, ENEMY_OCCULAR_MV },
    { ENEMY_SKELETON_HP, ENEMY_SKELETON_AP, ENEMY_SKELETON_XP, ENEMY_SKELETON_MV },
    { ENEMY_SPARKAT_HP, ENEMY_SPARKAT_AP, ENEMY_SPARKAT_XP, ENEMY_SPARKAT_MV },
    { ENEMY_WRAITH_HP, ENEMY_WRAITH_AP, ENEMY_WRAITH_XP,  ENEMY_WRAITH_MV },
    { ENEMY_DRAGON_HP, ENEMY_DRAGON_AP, ENEMY_DRAGON_XP, ENEMY_DRAGON_MV },
    { ENEMY_RAT_HP, ENEMY_RAT_AP, ENEMY_RAT_XP, ENEMY_RAT_MV, },
    { ENEMY_SLIME_HP, ENEMY_SLIME_AP, ENEMY_SLIME_XP, ENEMY_SLIME_MV }
  };

  uint8_t numberOfEnemies = pgm_read_byte(&level[idx++]);

  for (uint8_t i = 0; i < max; ++i) {

    enemies[i].setEnabled(i < numberOfEnemies);

    if (enemies[i].getEnabled()) {

      const EnemyType enemyType = (EnemyType)pgm_read_byte(&level[idx++]);

      enemies[i].setEnemyType(enemyType);
      enemies[i].setX(pgm_read_byte(&level[idx++]));
      enemies[i].setY(pgm_read_byte(&level[idx++]));

      const uint8_t hp = pgm_read_byte(&loadEnemiesStats[static_cast<uint8_t>(enemyType)].hp);
      const uint8_t ap = pgm_read_byte(&loadEnemiesStats[static_cast<uint8_t>(enemyType)].ap);
      const uint8_t xp = pgm_read_byte(&loadEnemiesStats[static_cast<uint8_t>(enemyType)].xp);
      const bool moving = pgm_read_byte(&loadEnemiesStats[static_cast<uint8_t>(enemyType)].moving) != 0;

      enemies[i].setHitPoints(hp);
      enemies[i].setHitPointsMax(hp);
      enemies[i].setAttackPower(ap);
      enemies[i].setExperiencePoints(xp);
      enemies[i].setMoving(moving);

    }

  }

 return idx;

}

#ifdef SAVE_GAME

#define EEPROM_START            EEPROM_STORAGE_SPACE_START + 100
#define EEPROM_START_C1         EEPROM_START
#define EEPROM_START_C2         EEPROM_START + 1
#define EEPROM_LEVEL_NO         EEPROM_START + 2
#define EEPROM_PLAYER_LEVEL     EEPROM_START + 3
#define EEPROM_PLAYER_START     EEPROM_START + 4
#define EEPROM_PLAYER_LENGTH    12
#define EEPROM_ENEMY_START      EEPROM_PLAYER_START + EEPROM_PLAYER_LENGTH
#define EEPROM_ENEMY_LENGTH     7
#define EEPROM_ITEM_LENGTH      4
#define EEPROM_DOOR_LENGTH      4


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'D' and 'U' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */
bool initEEPROM() {

  byte c1 = EEPROM.read(EEPROM_START_C1);
  byte c2 = EEPROM.read(EEPROM_START_C2);

  if (c1 != 68 || c2 != 85) { // RU 68 85

    EEPROM.update(EEPROM_START_C1, 68);
    EEPROM.update(EEPROM_START_C2, 85);
    EEPROM.update(EEPROM_LEVEL_NO, 255);

  }

}


/* -----------------------------------------------------------------------------
 *   Get the current level number. Should return 255 if no level has been saved.
 */
uint8_t getLevel() {

  return EEPROM.read(EEPROM_LEVEL_NO);

}


/* -----------------------------------------------------------------------------
 *   Save game state.
 */
void saveGame() {

  EEPROM.update(EEPROM_LEVEL_NO, level);
  EEPROM.update(EEPROM_PLAYER_LEVEL, playerLevel);
  EEPROM.put(EEPROM_PLAYER_START, myHero);

  uint16_t loc = EEPROM_ENEMY_START;

  for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
    EEPROM.put(loc, enemies[i]);
    loc = loc + EEPROM_ENEMY_LENGTH;
  }

  for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
    EEPROM.put(loc, items[i]);
    loc = loc + EEPROM_ITEM_LENGTH;
  }

  for (int i = 0; i < NUMBER_OF_DOORS; i++) {
    EEPROM.put(loc, doors[i]);
    loc = loc + EEPROM_DOOR_LENGTH;
  }

}


/* -----------------------------------------------------------------------------
 *   Restore game state.
 */
void restoreGame() {

  level = EEPROM.read(EEPROM_LEVEL_NO);
  playerLevel = EEPROM.read(EEPROM_PLAYER_LEVEL);

  initialiseLevel(&myHero, &myLevel, levels[level]);

  EEPROM.get(EEPROM_PLAYER_START, myHero);

  uint16_t loc = EEPROM_ENEMY_START;

  for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
    Enemy enemy;
    EEPROM.get(loc, enemy);
    enemies[i] = enemy;
    loc = loc + EEPROM_ENEMY_LENGTH;
  }

  for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
    Item item;
    EEPROM.get(loc, item);
    items[i] = item;
    loc = loc + EEPROM_ITEM_LENGTH;
  }

  for (int i = 0; i < NUMBER_OF_DOORS; i++) {
    Item door;
    EEPROM.get(loc, door);
    doors[i] = door;
    loc = loc + EEPROM_DOOR_LENGTH;
  }

}
#endif// ======================

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Inventory loop.
 *
 *  Controls the management and use of the inventory panel.  As a player transitions to this panel, the current GameState is
 *  saved in a variable named 'savedState' which allows the player to exit the panel and return to whence they came.
 *
 *  GameStates:
 *
 *  InventorySelect     - navigate through the five inventory slots.
 *  InventoryAction     - after selecting an item, the user can use or delete an item.
 *
 *  Returns delay in milliseconds to wait.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint16_t inventoryLoop() {

  drawFrames();
  arduboy.drawCompressed(66, 4, frames_inside, WHITE);
  arduboy.drawCompressed(4, 4, inv_background, WHITE);
  drawDirectionIndicator(&myHero);

  #ifdef USE_LARGE_MAP
  drawMapAndStatistics(&myHero, &myLevel, true);
  #endif
  #ifndef USE_LARGE_MAP
  drawMapAndStatistics(&myHero, &myLevel);
  #endif

  #ifndef SAVE_GAME
  for (uint8_t i = 0; i < 5; ++i) {

    if (myHero.getInventory(i) != ItemType::None) {

      Point inventoryCoords = inventory_Coords[i];

      arduboy.fillRect(inventoryCoords.x, inventoryCoords.y, 14, 16, BLACK);
      arduboy.drawCompressed(inventoryCoords.x, inventoryCoords.y, inventory_images[(uint8_t)myHero.getInventory(i)], WHITE);

    }

  }
  #endif
  #ifdef SAVE_GAME
  for (uint8_t i = 0; i < 3; ++i) {

    if (myHero.getInventory(i) != ItemType::None) {

      Point inventoryCoords = inventory_Coords[i];

      arduboy.fillRect(inventoryCoords.x, inventoryCoords.y, 14, 16, BLACK);
      arduboy.drawCompressed(inventoryCoords.x, inventoryCoords.y, inventory_images[(uint8_t)myHero.getInventory(i)], WHITE);

    }

  }
  #endif


  // Render selector ..

  Point inventoryCoords = inventory_Coords[inventory_selection];
  arduboy.drawCompressed(inventoryCoords.x + 3, inventoryCoords.y + 11, inv_select, BLACK);
  uint8_t buttons = arduboy.justPressedButtons();


  // Render AP and DF values ..

  font3x5.setTextColor(BLACK);
  font3x5.setCursor(19, 35);
  font3x5.print(myHero.getAttackPower());
  font3x5.setCursor(19, 45);
  font3x5.print(myHero.getDefence());
  font3x5.setTextColor(WHITE);


  switch (gameState) {

    case GameState::InventorySelect:

      #ifndef SAVE_GAME
      if ((buttons & LEFT_BUTTON_MASK) && inventory_selection > 0)           { --inventory_selection; }
      else if ((buttons & RIGHT_BUTTON_MASK) && inventory_selection < 2)     { ++inventory_selection; }
      #endif

      #ifdef SAVE_GAME
      if ((buttons & LEFT_BUTTON_MASK) && inventory_selection > 0)           { --inventory_selection; }
      else if ((buttons & RIGHT_BUTTON_MASK) && inventory_selection < 4)     { ++inventory_selection; }
      #endif

      else if (buttons & BACK_BUTTON_MASK)                                   { gameState = savedState;}

      else if (buttons & SELECT_BUTTON_MASK) {

        #ifdef SAVE_GAME
        if (inventory_selection == 3) {
          saveGame();
          font3x5.setCursor(90, 44);
          font3x5.print(F(" GAME\nSAVED!"));
          return ITEM_DELAY;
        }
        else if (inventory_selection == 4) {
          if (getLevel() == 255) {
            font3x5.setCursor(86, 44);
            font3x5.print(F("NO GAME\n SAVED"));
          }
          else {
            restoreGame();
            font3x5.setCursor(86, 44);
            font3x5.print(F("  GAME\nRESTORED"));
          }
          return ITEM_DELAY;
        }
        else {
        #endif

          if (myHero.getInventory(inventory_selection) != ItemType::None) {
            gameState = GameState::InventoryAction;
          }

        #ifdef SAVE_GAME
        }
        #endif

      }

      break;

    case GameState::InventoryAction:

      arduboy.drawCompressed(82 + (inventory_action == INVENTORY_ACTION_DROP ? 12 : 0), 56, inv_select, WHITE);
      Sprites::drawOverwrite(81, 45, inv_hand, 0);
      Sprites::drawOverwrite(93, 45, inv_trash, 0);

      if ((buttons & LEFT_BUTTON_MASK) && inventory_action > INVENTORY_ACTION_USE)            { --inventory_action; }
      else if ((buttons & RIGHT_BUTTON_MASK) && inventory_action < INVENTORY_ACTION_DROP)     { ++inventory_action; }
      else if (buttons & BACK_BUTTON_MASK)                                                    { gameState = GameState::InventorySelect;}
      else if (buttons & SELECT_BUTTON_MASK) {

        if (inventory_action == INVENTORY_ACTION_USE) {

          bool success = false;
          switch (myHero.getInventory(inventory_selection)) {

            case ItemType::Key:

              for (uint8_t i = 0; i < NUMBER_OF_DOORS; ++i) {

                int16_t deltaX = doors[i].getX() - myHero.getX();
                int16_t deltaY = doors[i].getY() - myHero.getY();

                if (doors[i].getEnabled() && (doors[i].getItemType() != ItemType::UnlockedDoor) &&
                    absT(deltaX) <= 1 && absT(deltaY) <= 1) {

                  if (doors[i].getItemType() == ItemType::LockedGate)         doors[i].setEnabled(false);
                  if (doors[i].getItemType() == ItemType::LockedDoor)         doors[i].setItemType(ItemType::UnlockedDoor);
                  if (doors[i].getItemType() == ItemType::SelfLockingDoor)    doors[i].setEnabled(false);
                  
                  success = true;

                }

              }
              break;

            case ItemType::Potion:
              myHero.setHitPoints(myHero.getHitPoints() + INVENTORY_POTION_HP_INC);
              success = true;
              break;

            default: break;

          }
          
          if(success)
          {
              myHero.setInventory(inventory_selection, ItemType::None);
              inventory_action = INVENTORY_ACTION_USE;
              gameState = GameState::InventorySelect;
          }

        }

        if (inventory_action == INVENTORY_ACTION_DROP) {

          uint8_t itemIndex = 0;

          for (uint8_t i = 0; i < NUMBER_OF_ITEMS; ++i) {

            Item item = items[i];

            if (item.getItemType() != ItemType::None) {

              if (item.getX() == myHero.getX() && item.getY() == myHero.getY()) {

                font3x5.setCursor(95, 44);
                font3x5.print(F("SPACE\nOCCUPIED!"));
                return ITEM_DELAY;

              }

            }
            else {

              itemIndex = i;

            }

          }
          
          items[itemIndex].setEnabled(true);
          items[itemIndex].setItemType(myHero.getInventory(inventory_selection));
          items[itemIndex].setX(myHero.getX());
          items[itemIndex].setY(myHero.getY());

          myHero.setInventory(inventory_selection, ItemType::None);
          inventory_action = INVENTORY_ACTION_USE;
          gameState = GameState::InventorySelect;
          

        }

      }

      break;

    default: break;

  }

  return 0;

}
// ======================

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Item loop.
 *
 *  Controls the selection or discarding of an item the player has stumbled over.  If a user choses to ignore an item found in
 *  the maze, the GameState is updated to ItemIgnore which will allow them to progress beyond the item.  If th user returns to
 *  the same position in the maze, they will be re-prompted to collect / discard the same item.
 *
 *  The player can press the BACK_BUTTON (as defined in Enums.h) to bring up the inventory management dialogue if they need to
 *  delete an existing inventory item to make space for the new item.  The current GameState is retained in the 'savedState'
 *  field allowing for control to return back to this action after the dialogue is dismissed.
 *
 *  Returns delay in milliseconds to wait.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint16_t itemLoop() {

    drawPlayerVision(&myHero, &myLevel);
    arduboy.drawCompressed(72 + (itemAction == INVENTORY_ACTION_DROP ? 12 : 0), 56, inv_select, WHITE);

    Sprites::drawOverwrite(71, 45, inv_hand, 0);
    Sprites::drawOverwrite(83, 45, inv_trash, 0);
    arduboy.drawFastVLine(66, 43, 16);

    uint8_t buttons = arduboy.justPressedButtons();

    if ((buttons & LEFT_BUTTON_MASK) && itemAction > ITEM_ACTION_USE)             { --itemAction; }
    else if ((buttons & RIGHT_BUTTON_MASK) && itemAction < ITEM_ACTION_DROP)      { ++itemAction; }


    // Return to the previous game state if the user presses the back button ..

    if (buttons & BACK_BUTTON_MASK) {
      savedState = gameState;
      gameState = GameState::InventorySelect;
    }


    // Handle the use of the selected item ..

    if (buttons & SELECT_BUTTON_MASK) {

      if (itemAction == ITEM_ACTION_USE) {

        ItemType inventoryType = items[savedItem].getItemType();
        int8_t inventorySlot = myHero.getConsumableSlot();

        if (inventoryType == ItemType::Shield || inventoryType == ItemType::Sword) {

          if (inventoryType == ItemType::Shield)  myHero.setDefence(myHero.getDefence() + 1);
          if (inventoryType == ItemType::Sword)   myHero.setAttackPower(myHero.getAttackPower() + 1);

          items[savedItem].setEnabled(false);
          gameState = GameState::Move;

        }
        else {
          if (inventorySlot >= 0) {

            myHero.setInventory(inventorySlot, inventoryType);
            items[savedItem].setEnabled(false);
            gameState = GameState::Move;

          }
          else {

            font3x5.setCursor(95, 44);
            font3x5.print(F("NO INV\nSLOTS!"));
            return ITEM_DELAY;

          }

        }


      }

      if (itemAction == ITEM_ACTION_DROP)  {

        gameState = GameState::ItemIgnore;

      }

    }

    return 0;

  }// ======================
#ifdef USE_LARGE_MAP

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Display Large Map.
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void displayLargeMap() {

  drawFrames();
  drawMapAndStatistics(&myHero, &myLevel, false);
  uint8_t buttons = arduboy.justPressedButtons();

  if (buttons & BACK_BUTTON_MASK) { gameState = savedState; }

}
#endif
// ======================

/* -----------------------------------------------------------------------------------------------------------------------------
 *  Play loop.
 *
 *  Handles the players moves around the dungeon.  If the player has moved (as opposed to simply turned), the enemies can then
 *  also move.  If the player and an enemy collide, the gameState is chaged to 'Battle_EnemyAttacks_Init'.
 *
 * -----------------------------------------------------------------------------------------------------------------------------
 */
uint16_t playLoop() {

  bool playerMoved = false ;
  uint16_t delayLength = 0;

  MapElement origLocation = myLevel.getMapElement(myHero.getX(), myHero.getY(), true);

  drawPlayerVision(&myHero, &myLevel);
  drawDirectionIndicator(&myHero);

  uint8_t buttons = arduboy.justPressedButtons();

  if (buttons & UP_BUTTON_MASK)            { playerMoved = PlayerController::move(&myHero, enemies, &myLevel, Button::Up); }
  else if (buttons & DOWN_BUTTON_MASK)     { playerMoved = PlayerController::move(&myHero, enemies, &myLevel, Button::Down); }
  else if (buttons & LEFT_BUTTON_MASK)     { PlayerController::move(&myHero, enemies, &myLevel, Button::Left); }
  else if (buttons & RIGHT_BUTTON_MASK)    { PlayerController::move(&myHero, enemies, &myLevel, Button::Right); }

  #ifdef USE_LARGE_MAP
  else if (buttons & SELECT_BUTTON_MASK)     {

    savedState = gameState;
    gameState = GameState::DisplayLargeMap;

  }
  #endif

  else  if (buttons & BACK_BUTTON_MASK)     {

    savedState = gameState;
    gameState = GameState::InventorySelect;

  }


  // If the player moved then so should the enemies ..

  if (playerMoved) {

    if (origLocation == MapElement::SelfLockingDoor) {

      for (uint8_t i = 0; i < NUMBER_OF_DOORS; ++i) {
  
        if (!myLevel.getDoors()[i].getEnabled() && (myLevel.getDoors()[i].getItemType() == ItemType::SelfLockingDoor) && myHero.getX() && myHero.getY()) { 

          (myLevel.getDoors()[i]).setEnabled(true); 
          delayLength = FIGHT_DELAY;          
          
          font3x5.setCursor(80,44);
          font3x5.print(F("GATE LOCKS\nBEHIND YOU!"));

        }
    
      }

    }

    if (myLevel.getMapElement(myHero.getX(), myHero.getY(), false) == MapElement::UnlockedDoor) {

      if (level < MAX_LEVEL_COUNT) {
        gameState = GameState::NextLevel;
      }
      else {
        gameState = GameState::EndOfGame;
      }

      return delayLength;

    }

    gameState = GameState::Move;        // Play could be at game state ItemIgnore, in which case we only want to ignore this first item only.

    for (uint8_t i = 0; i < NUMBER_OF_ENEMIES; ++i) {

      if (enemies[i].getEnabled() && enemies[i].getMoving()) {

        EnemyController::move(&enemies[i], enemies, &myHero, &myLevel);

      }

    }

  }

  if (delayLength == 0) {

    drawLevelDescription(&myLevel);
    
  }

  return delayLength;

}

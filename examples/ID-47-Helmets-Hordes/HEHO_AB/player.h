#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

#define HELENA_START_X                             20
#define HELENA_START_Y                             33

#define HELENA_DEAD                                 0
#define HELENA_NAKED                                1
#define HELENA_ARMOR                                2
#define HELENA_HELMET                               3

#define HELMET_NO_HELMET                            0
#define HELMET_WARRIOR                              1
#define HELMET_FOOTBALL                             2
#define HELMET_THIEF                                3
#define HELMET_CUTTER                               4
#define HELMET_MAGNET                               5
#define HELMET_MERCURY                              6
#define HELMET_BATTERY                              7

#define WEAPON_NONE                                 0
#define WEAPON_DAGGER                               1
#define WEAPON_SWORD                                2

#define HELENA_IMUNE_TIME                          30
#define HELENA_FLICKER_TIME                        15
#define HELENA_ATTACK_TIME                       10
#define STAB_TIME                                  6

#define HELENA_COLLISION_X_OFFSET                   3
#define HELENA_COLLISION_Y_OFFSET                   -2
#define HELENA_COLLISION_WIDTH                      8
#define HELENA_COLLISION_HEIGHT                     14

#define STAB_COLLISION_WIDTH                        8
#define STAB_COLLISION_HEIGHT                       8



const unsigned char PROGMEM helenaJumpSequence[] = {6, 14, 20, 23, 23, 25, 25, 25, 26, 26, 26, 26, 25, 25, 25, 23, 23, 20, 14, 6};
const unsigned char PROGMEM weaponWithHelmet[] = {WEAPON_SWORD, WEAPON_SWORD, WEAPON_NONE, WEAPON_DAGGER, WEAPON_NONE, WEAPON_SWORD, WEAPON_NONE, WEAPON_NONE};
byte nextStab;

struct Players
{
  public:
    int x, y;
    byte life, frame, helmet, nextHelmet, jumpSequenceCounter, imuneTimer, flickerTimer, attackTimer;
    byte characteristics;   //0B00000000;   //this byte holds all the players characteristics
    //                          ||||||||
    //                          |||||||└->  0 \ weapon type ( 0 = none / 1 = dagger / 2 = sword)
    //                          ||||||└-->  1 /
    //                          |||||└--->  2 - the player is changing helmets                (0 = false / 1 = true)
    //                          ||||└---->  3 - the players helmet is visible                 (0 = false / 1 = true)
    //                          |||└----->  4 - the player is visible                         (0 = false / 1 = true)
    //                          ||└------>  5 - the player is Imune                           (0 = false / 1 = true)
    //                          |└------->  6 - the player is jumping                         (0 = false / 1 = true)
    //                          └-------->  7 - the player is attacking                       (0 = false / 1 = true)
};

struct Stabbing
{
  public:
    byte x, y, type, stabTimer;
    boolean isVisible;
    boolean isActive;
    boolean horizontal;
};


Players helena;
Stabbing stab[2];

void setHelena()
{
  helena =
  {
    HELENA_START_X, HELENA_START_Y,                     // start position
    HELENA_NAKED,
    0,                                                  // start animation at frame 0
    HELMET_NO_HELMET,                                   // start without a helmet
    HELMET_NO_HELMET,                                   // start without a next helmet
    0,                                                  // start the sequence counter at 0
    0,                                                  // start the imuneTimer at 0
    0,                                                  // start the flickerTimer at 0
    0,                                                  // start the attackTimer at 0
    0B00110000,                                         // start visible / imune and without sword
  };
  for (byte i = 0; i < 2; i++ )
  {
    stab[i].isActive = false;
    stab[i].isVisible = false;
  }
  nextStab = 0;
}

void setAttack()
{
  helena.characteristics |= 0B10000000; // if not attacking, attack
  if (helena.characteristics & 0B00000011)
  {
    stab[nextStab].isActive = true;
    stab[nextStab].isVisible = true;
    stab[nextStab].type = (helena.characteristics & 0B00000011) - 1;
    stab[nextStab].stabTimer = 0;
    if (!(helena.characteristics & 0B01000000))
    {
      stab[nextStab].x = helena.x + 25;
      stab[nextStab].y = helena.y - 6;
      stab[nextStab].horizontal = true;
    }
    else
    {
      stab[nextStab].x = helena.x + 1;
      stab[nextStab].y = helena.y - 14;
      stab[nextStab].horizontal = false;
    }
    nextStab = (++nextStab) % 2;
  }
}


void updateHelena()
{
  if (arduboy.everyXFrames(WALKINGSPEED * 3)) helena.frame = (++helena.frame) % 4;

  if (helena.characteristics & 0B00100000) // if imune
  {
    if (arduboy.everyXFrames(3))
    {
      helena.imuneTimer++;
      helena.characteristics ^= 0B00010000;
    }
    if (helena.imuneTimer > HELENA_IMUNE_TIME)
    {
      helena.imuneTimer = 0;
      helena.characteristics &= 0B11011111;
      helena.characteristics |= 0B00010000;
    }
  }
  if (helena.characteristics & 0B01000000)  // if jumping
  {
    if (arduboy.everyXFrames(2)) helena.jumpSequenceCounter++;
    if ((helena.helmet == HELMET_WARRIOR) && (helena.jumpSequenceCounter == 11)) setAttack();
    if (helena.jumpSequenceCounter > 19)
    {
      helena.jumpSequenceCounter = 0;
      helena.characteristics &= 0B10111111;
    }
  }
  else if (helena.x < HELENA_START_X && arduboy.everyXFrames(2)) helena.x++;

  if (helena.characteristics & 0B00000100)  // if helmet is flickering
  {
    if (arduboy.everyXFrames(5))
    {
      helena.flickerTimer++;
      helena.characteristics ^= 0B00001000;
    }
    if (helena.flickerTimer > HELENA_FLICKER_TIME)
    {
      helena.flickerTimer = 0;
      helena.characteristics &= 0B11110011;
      helena.helmet = helena.nextHelmet;
    }
  }

  if (helena.characteristics & 0B10000000)  // if attacking
  {
    if (arduboy.everyXFrames(2)) helena.attackTimer++;
    if (helena.attackTimer > HELENA_ATTACK_TIME)
    {
      helena.attackTimer = 0;
      helena.characteristics &= 0B01111111;
    }
  }

  for (byte i = 0; i < 2; i++ )
  {
    if (stab[i].isActive)
    {
      stab[i].stabTimer++;
      if (stab[i].horizontal) stab[i].x++;
      else stab[i].y++;
      if (stab[i].stabTimer > STAB_TIME * (helena.characteristics & 0B00000011))
      {
        stab[i].stabTimer = 0;
        stab[i].isActive = false;
        stab[i].isVisible = false;
      }
    }
  }

  if (helena.x < 1) helena.life = HELENA_DEAD;
  //if (helena.life < 1) helena.life = 1;
  if (helena.life < HELENA_HELMET) helena.helmet = 0;
  if (helena.life == HELENA_NAKED) helena.characteristics = (helena.characteristics & 0B11111100) + WEAPON_DAGGER;
  else helena.characteristics = (helena.characteristics & 0B11111100) + pgm_read_byte(&weaponWithHelmet[helena.helmet]);

  if (helena.life == HELENA_DEAD) gameState = STATE_MENU_MAIN;


}


void drawHelena()
{
  switch (helena.characteristics & 0B11010000)
  {
    case 0B00010000:        // visible
      sprites.drawPlusMask(helena.x, helena.y + (helena.frame % 2), playerNaked_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
      if (!(helena.characteristics & 0B00001000))sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.helmet);
      if ((helena.characteristics & 0B00001100) == 0B00001100) sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.nextHelmet);
      if (helena.life > HELENA_NAKED)
      {
        if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 13 + pgm_read_byte(&frameSequence[helena.frame]), helena.y  + (helena.frame % 2) + 6, playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
        sprites.drawPlusMask(helena.x - 2 , helena.y + 4 + (helena.frame % 2), playerArmor_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
      }
      else if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 12 + pgm_read_byte(&frameSequence[helena.frame]), helena.y  + (helena.frame % 2) + 6, playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
      break;
    case 0B01010000:        // visible & jumping
      sprites.drawPlusMask(helena.x - 3 , helena.y - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerNakedJump_plus_mask, 0);
      if (!(helena.characteristics & 0B00001000)) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.helmet);
      if ((helena.characteristics & 0B00001100) == 0B00001100) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.nextHelmet);
      if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 16, helena.y  + 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
      if (helena.life > HELENA_NAKED) sprites.drawPlusMask(helena.x - 5 , helena.y + 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerArmorJump_plus_mask, 0);
      break;

    case 0B10010000:        // visible + attacking
      if (helena.helmet == HELMET_FOOTBALL)
      {
        sprites.drawPlusMask(helena.x - 3, helena.y, playerFootballTackle_plus_mask, 0);
      }
      else
      {
        sprites.drawPlusMask(helena.x, helena.y + (helena.frame % 2), playerNaked_plus_mask, pgm_read_byte(&frameSequence[helena.frame]));
        if (helena.life > HELENA_NAKED)
        {
          sprites.drawPlusMask(helena.x - 5, helena.y + 4 + (helena.frame % 2), playerArmorSlash_plus_mask, 0);
          if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 19, helena.y + 2 + (helena.frame % 2), playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
        }
        else
        {
          sprites.drawPlusMask(helena.x - 3, helena.y + 4 + (helena.frame % 2), playerNakedSlash_plus_mask, 0);
          if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 17, helena.y + 3 + (helena.frame % 2), playerWeapon_plus_mask, (helena.characteristics & 0B00000011) - 1);
        }
      }
      if (!(helena.characteristics & 0B00001000))sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.helmet);
      if ((helena.characteristics & 0B00001100) == 0B00001100) sprites.drawPlusMask(helena.x - 4 , helena.y - 9 + (helena.frame % 2), playerHelmets_plus_mask, helena.nextHelmet);
      break;

    case 0B11010000:        // visible + jumping + attacking
      if (helena.helmet == HELMET_FOOTBALL)
      {
        sprites.drawPlusMask(helena.x - 3, helena.y - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerFootballTackle_plus_mask, 0);
      }
      else
      {
        sprites.drawPlusMask(helena.x - 3 , helena.y - 2 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerNakedJumpSlash_plus_mask, 0);
        if (helena.characteristics & 0B00000011) sprites.drawPlusMask(helena.x + 7, helena.y  + 12 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerWeaponJump_plus_mask, (helena.characteristics & 0B00000011) - 1);
        if (helena.life > HELENA_NAKED) sprites.drawPlusMask(helena.x - 5 , helena.y + 1 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerArmorJumpSlash_plus_mask, 0);
      }
      if (!(helena.characteristics & 0B00001000)) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.helmet);
      if ((helena.characteristics & 0B00001100) == 0B00001100) sprites.drawPlusMask(helena.x - 4 , helena.y - 11 - pgm_read_byte(&helenaJumpSequence[helena.jumpSequenceCounter]), playerHelmets_plus_mask, helena.nextHelmet);
      break;
  }
}

void drawStab()
{
  for (byte i = 0; i < 2; i++ )
  {
    if (stab[i].isActive)
    {
      if (stab[i].horizontal)
      {
        if (stab[i].isVisible) sprites.drawSelfMasked(stab[i].x, stab[i].y, stabWalking, stab[i].type);
      }
      else if (stab[i].isVisible) sprites.drawSelfMasked(stab[i].x, stab[i].y, stabJumping, stab[i].type);
    }
  }
}


#endif

#ifndef COLLISION_H
#define COLLISION_H

#include <Arduboy2.h>
#include "variables.h"

/**
 * @brief Call all collision functions.
 */
void checkCollision();

/**
 * @brief Player: Check collision with bullet, enemy and supply.
 */
void checkCollisionPlayer();

/**
 * @brief Enemy: Check shot.
 * TODO: if(noOfSupplies = supplie.length) no supply
 */
void checkCollisionEnemy();

/**
 * @brief Enemy: Check if still in frame
 */
void checkEnemiesInFrame();

/**
 * @brief Bullet: Check if still in frame
 */
void checkBulletsInFrame();

/**
 * @brief Destroy all dead objects. Move the last object to the new 
 * available slot.
 */
void checkAlive();

#endif

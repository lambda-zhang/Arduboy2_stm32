#ifndef MOVMENT_H
#define MOVEMENT_H

#include <Arduboy2.h>
#include "variables.h"

/**
 * @brief Call all functions needed for movement.
 */
void moveGame();

/**
 * @brief Supplies move just straight to the left.
 */
void moveSupplies();

/**
 * @brief Bullets move
 * TODO: Check speed.
 */
void moveBullets();

/**
 * @brief Player moves
 */
void movePlayer();

/**
 * @brief Enemies move
 * TODO: Alter the directions. Check for speed.
 */
void moveEnemies();

/**
 * @brief Stars move
 */
void moveStars();

/**
 * @brief Enemies shoot
 */
void enemiesShoot();

/**
 * @brief Player shoots
 * TODO Add a delay so the player cannot shoot too much at once maybe?
 * Add different directions with different bullets.
 */
void playerShoots();
#endif

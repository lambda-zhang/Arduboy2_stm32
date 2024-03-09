#ifndef GENERATOR_H
#define GENERATOR_H

#include <Arduboy2.h>
#include "variables.h"
#include "draw.h"

/**
 * @brief Initialize player and enemies
 */
void initGame(bool newGame);

/**
 * @brief Initialize the player's position, size etc.
 */
void initPlayer(bool newGame);

/**
 * @brief Kill all enemies for the beginning.
 */
void initEnemies();

/**
 * @brief Destroy all supplies.
 */
void initBullets();

/**
 * @brief Destroy all bullets.
 */
void initSupplies();

/**
 * @brief Stop all explosion animations.
 */
void initExplosions();

/**
 * @brief Generate a random star for the background.
 */
void generateStar();

/**
 * @brief Generate random enemies with their strength based on the player's
 * score and the number of enemies on the screen. May generate nothing.
 * You may use this every second.
 * TODO: Check if the room is free to place the new enemy.
 */
void generateEnemy();

/**
 * @brief Create supply at the place where the enemy died.
 * @param[in] x X-Coordinate of the destroyed enemy.
 * @param[in] y Y-Coordinate of the destroyed enemy.
 */
void createSupply(byte x, byte y);

#endif

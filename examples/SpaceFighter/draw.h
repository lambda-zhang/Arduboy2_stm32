#ifndef DRAW_H
#define DRAW_H

#include <Arduboy2.h>
#include "variables.h"
#include "SpaceFighter_bitmaps.h"

/*
 * @brief Calls all necessary functions to generate the current display.
 * @return True if all explosions have been drawn.
 */
bool drawGame();

/**
 * @brief Titlescreen with sound - SpaceFighter by me.
 * TODO: create nice music.
 */
void showTitle();

/**
 * @brief Display Highscore with the scores.
 * This method is from Sebastian Goscik as seen in
 * https://github.com/Arduboy/Arduboy/blob/master/examples/ArduBreakout/ArduBreakout.ino
 * and slightly modified.
 * Function by nootropic design to display highscores.
 * TODO: Alter for bigger scores.
 */
void showHighscore();

/**
 * @brief Draw all stars in the background.
 */
void drawStars();

/**
 * @brief Draw the player in its current state.
 * TODO: Check for current powerups and choose different ships.
 */
void drawPlayer();

/**
 * @brief draw all the enemies.
 * TODO: Get the size of each image right.
 */
void drawEnemies();

/*
 * @brief Bullets are 2x2 squares which are drawn in this function.
 */
void drawBullets();

/**
 * @brief Draw supply
 */
void drawSupply();

/**
 * @brief Draw supply messages
 */
void drawExtra(byte type);

/*
 * @brief Draws an explosion for destroyed ships.
 * @return: True if all explosions are finished.
 */
bool drawExplosions();

/**
 * @brief Draw score like this: Score: 100
 */
void drawScore();

/**
 * @brief Draw the number of lives like this: symbol heart 5
 * If there are only three or less lives left, draw three hearts.
 */
void drawLives();

/**
 * @brief draw Pause. The Code is taken from ArduBreakout by Sebastian Goscik
 * and has been modified.
 */
void drawPause();

/**
 * @brief draw game over
 */
void drawGameOver();

#endif 

/*
 * SpaceFighter
 * Copyright (C) 2015
 * Maicon Hieronymus <mhierony@students.uni-mainz.de>
 * All rights reserved.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * -----------------------------------------------------------------------------
 *
 * @file        SpaceFighter.ino
 * @date        25.02.2018
 * @version     0.2
 * @author      Maicon Hieronymus <mhierony@students.uni-mainz.de>
 *
 * @brief This program is a shooter game set in space where you control a
 * more or less cool spaceship.
 * It is coded with Arduboy in mind using the Arduboy2 library.
 */

#include <Arduboy2.h>

#include "variables.h"
#include "draw.h"
#include "movement.h"
#include "collision.h"
#include "generator.h"

Arduboy2 arduboy;
byte frameCounter;
Star stars[MAXSTARS];
byte numberOfStars = 0;
byte SCREEN_HEIGHT = 64;
byte SCREEN_WIDTH = 128;
Player player;
Enemy enemies[MAXENEMIES];
byte numberOfEnemies = 0;
Bullet bullets[MAXBULLETS];
byte numberOfBullets = 0;
Supply supplies[MAXSUPPLY];
byte noOfSupplies = 0;
bool gameStarted = false;
Explosion explosions[MAXENEMIES+1];


/**
 * @brief game over
 */
void gameOver() {
    drawGameOver();
    delay(4000);
}


void setup() {
    arduboy.begin();
    arduboy.setFrameRate(60);
    arduboy.initRandomSeed();
}

void loop() {
    // No rendering needed until the next frame is needed. Duh!
    if(!(arduboy.nextFrame()))
        return;
    if(gameStarted) {
        if(player.alive) {
            generateStar();
            generateEnemy();
            drawGame();
            moveGame();
            checkCollision();
            checkAlive();
            if(arduboy.pressed(A_BUTTON)) {
                delay(200);
                drawPause();
            }
        } else  {
            if(drawGame()) {
                gameStarted = false;
                delay(1000);
            } else {
                moveGame();
            }

        }
        if(!gameStarted) {
            if(player.lives == 0) {
                gameOver();
            } else {
                initGame(false);
                gameStarted = true;
            }
        }
    } else {
        showTitle();
        gameStarted = true;
        initGame(true);
    }
}

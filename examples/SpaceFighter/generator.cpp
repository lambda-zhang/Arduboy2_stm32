#include "generator.h"

void initGame(bool newGame) {
    initPlayer(newGame);
    initEnemies();
    initSupplies();
    initBullets();
    initExplosions();
}

void initPlayer(bool newGame) {
    player.x = 0;
    player.y = 0;
    player.width = 14;
    player.height = 14;
    if(newGame)
        player.score = 0;
    player.numberOfSuperbombs = 0;
    player.invincible = 1;
    player.bulletType = 1;
    player.bulletSpeed = 1;
    player.bullets = 0;
    player.maxBullets = 2;
	if(newGame)
		player.speed = 2; // Lower is better.
    player.alive = true;
    if(newGame)
        player.lives = 5;
    player.fireSpeed = 100;
    player.cooldown = 0;
	player.firetype = 0;
}

void initEnemies() {
    for(byte i=0; i<MAXENEMIES; i++) {
        enemies[i].alive=false;
    }
}

void initBullets() {
    for(byte i=0; i<MAXBULLETS; i++) {
        bullets[i].alive=false;
        bullets[i].playersBullet = false;
    }
}

void initSupplies() {
    for(byte i=0; i<MAXSUPPLY; i++) {
        supplies[i].alive=false;
    }
}

void initExplosions() {
    for(byte i=0; i<=MAXENEMIES; i++) {
        explosions[i].tick=100;
    }
}

void generateStar() {
    byte rand = random(1, 100);
    // Make sure there are not too many stars.
    if(rand<5 && numberOfStars < MAXSTARS) {
        Star s;
        s.x = SCREEN_WIDTH-1;
        // Create a y-coordinate between bottom and top.
        s.y = random(0, SCREEN_HEIGHT);
        stars[numberOfStars] = s;
        numberOfStars++;
    }
}

void generateEnemy() {
    if(random(0, 4) > numberOfEnemies
		&& numberOfEnemies < MAXENEMIES && random(0,100) > 85)  {
			
        Enemy e;
        e.x = SCREEN_WIDTH;
        e.y = random(10, SCREEN_HEIGHT-10);
        byte rnd = random(0, 5);
        e.lifepoints = random(1, 1+player.destroyedShips);
        e.alive = true;
        e.direction = MOVE_LEFT; //random(0, 8)
        e.movement = 0; // Straight line
        e.tick = 0;
		// random(0, 100) > 50 && 
        if(MAXSUPPLY >= noOfSupplies) {
            e.supply = true;
        }
        if(rnd == 0) {
            e.movement = 4;
            e.shipType = 1;
            e.height = 7;
            e.width = 8;
            e.speed = 10;
            e.maxBullets = 1;
            e.lifepoints = 1;
        } else if(rnd == 1) {
            e.movement = 8;
            e.shipType = 2;
            e.height = 5;
            e.width = 6;
            e.speed = 4;
            e.maxBullets = 3;
            e.lifepoints = 1;
        } else if(rnd == 2) {
            e.movement = 2;
            e.direction = MOVE_DOWNLEFT;
            e.shipType = 4;
            e.height = 7;
            e.width = 8;
            e.speed = 3;
            e.maxBullets = 10;
            e.lifepoints = 5;
        } else if(rnd == 3) {
            e.shipType = 8;
            e.height = 7;
            e.width = 8;
            e.speed = 10;
            e.maxBullets = 1;
            e.lifepoints = 1;
        } else if(rnd == 4) {
            e.movement = 8;
            e.shipType = 16;
            e.height = 5;
            e.width = 6;
            e.speed = 2;
            e.maxBullets = 8;
            e.lifepoints = 5;
        } else if(rnd == 5) {
            e.shipType = 32;
            e.height = 7;
            e.width = 8;
            e.speed = 3;
            e.maxBullets = 2;
            e.lifepoints = 2;
        } else if(rnd == 6) {
            e.movement = 16;
            e.shipType = 64;
            e.height = 7;
            e.width = 8;
            e.speed = 10;
            e.maxBullets = 1;
            e.lifepoints = 1;
        } else if(rnd == 7) {
            e.shipType = 128;
            e.height = 5;
            e.width = 6;
            e.speed = 2;
            e.maxBullets = 6;
            e.lifepoints = 8;
        }
        enemies[numberOfEnemies] = e;
        numberOfEnemies++;
    }
}

void createSupply(byte x, byte y) {
    Supply s;
    s.x = x;
    s.y = y;
    s.type = random(0,8);
    s.alive = true;
    supplies[noOfSupplies] = s;
	noOfSupplies++;
    drawSupply();
}

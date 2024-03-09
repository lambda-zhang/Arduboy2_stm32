#ifndef VARIABLES_H
#define VARIABLES_H

// Define maximum amount of particles.
#define MAXBULLETS 50
#define MAXSTARS 25
#define MAXENEMIES 10
#define MAXSUPPLY 3
// Define Movements
#define MOVE_UP 0
#define MOVE_UPLEFT 7
#define MOVE_LEFT 6
#define MOVE_DOWNLEFT 5
#define MOVE_DOWN 4
#define MOVE_DOWNRIGHT 3
#define MOVE_RIGHT 2
#define MOVE_UPRIGHT 1
#define DEBUG false

typedef struct
{
    // All coordinates are the upper right corner of an image.
    byte x;
    byte y;
    byte height;
    byte width;
    unsigned int score;
    byte destroyedShips;
    byte lives;
    bool alive;
    byte numberOfSuperbombs;
    // set invincible to 1 and then every two second a right-shift until
    // invincible is zero.
    // This way you are 2 seconds invincible. Or more, if you set
    // invincible to 2, 4 or 8.
    byte invincible;
    byte bulletType;
    byte bulletSpeed;
    // The player cannot fire infinite bullets (and therefore stun the enemy).
    byte bullets;
    byte maxBullets;
	// 0 is normal
    // 1 is two at once 
	// 2 is one straight and two up/down diagonal 
	// 3 is two in the middle in addition
    // 4 is two more diagonal
	byte firetype; 
    byte speed; // Lower is better.
    byte cooldown; // Shoot if cooldown == 0;
    byte fireSpeed; // The lower, the faster you can fire.
} Player;

typedef struct
{
    byte x;
    byte y;
} Star;

typedef struct
{
    // All coordinates are the upper right corner of an image.
    byte x;
    byte y;
    byte height;
    byte width;
    // Each number is a placeholder for different ships. These types define
    // the image, bullettype and speed. The highest 1 indicates the type
    // e.g. 0100 is the same type as 0111 or 0101 or 0110.
    byte shipType;
    byte speed; // Lower is better.
    byte lifepoints;
    bool alive;
    // Each number is a placeholder for another movement, e.g. straight-forward
    // or sine. Needs to be implemented.
    byte movement;
    byte direction;
    // If true, create a random supply after destruction.
    bool supply;
    byte maxBullets;
    byte tick; // Used for altering the direction.
} Enemy;

typedef struct
{
    // All coordinates are the upper right corner of an image.
    byte x;
    byte y;
    byte height;
    byte width;
    byte appearance;
    byte damage;
    byte speed;
    bool alive;
    bool playersBullet;
    // Directions:
    //              7      0      1
    //            6      enemy    2
    //              5     4     3
    byte direction;
} Bullet;

typedef struct
{
    byte x;
    byte y;
    bool alive;
    // Each number is a placeholder for different supplies, e.g. extra live
    // superbomb, weapon upgrade or invincibility (or even ship upgrade?).
    // 0 is most rare, >8 is most common.
    byte type;
} Supply;

typedef struct
{
    byte x;
    byte y;
    byte tick; // Each tick is part of a different animation
} Explosion;


// Counter the frames. Every 60 frames is one second. This can be used for
// measuring time.
extern byte frameCounter;
// The stars in the background are saved here.
extern Star stars[MAXSTARS];
extern byte numberOfStars;
extern byte SCREEN_HEIGHT;
extern byte SCREEN_WIDTH;
extern Player player;
extern Arduboy2 arduboy;
extern Enemy enemies[MAXENEMIES];
extern byte numberOfEnemies;
extern Bullet bullets[MAXBULLETS];
extern byte numberOfBullets;
extern Supply supplies[MAXSUPPLY];
extern byte noOfSupplies;
extern bool gameStarted;
extern Explosion explosions[MAXENEMIES+1];

#endif

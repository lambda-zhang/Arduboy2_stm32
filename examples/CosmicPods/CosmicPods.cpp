/*
  CosmicPods

  CosmicPods is a tiny shoot-'em-up game for Arduboy.
  As cosmic squid, shoot octopuses up!

  Copyright (C) 2017, cubic9com All rights reserved.
  Contact: <https://twitter.com/cubic9com>

  This code is licensed under the BSD 3-Clause license.
  See file LICENSE for more information.
*/

#include <Arduboy2.h>

Arduboy2 arduboy;
static BeepPin1 beep;

#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

#define X_MAX (WIDTH - (CHAR_WIDTH * 3) + 1)
#define Y_MAX (HEIGHT - CHAR_HEIGHT)

#define NUM_PLAYER_BULLETS 4
#define MAX_NUM_ENEMIES 8
#define NUM_STARS 32

#define ENEMY_RECT {0, 0, 12, 12}
#define PLAYER_RECT {0, 1, 16, 6}

struct Vector2 {
  float x;
  float y;
};

struct FloatPoint {
  float x;
  float y;
};

struct PlayerBullet {
  Point point;
  boolean enabled;
};

struct Player {
  Rect rect;
  PlayerBullet bullets[NUM_PLAYER_BULLETS];
};

struct EnemyBullet {
  FloatPoint point;
  Vector2 delta;
  boolean enabled;
};

struct Enemy {
  Rect rect;
  EnemyBullet bullet;
};

struct Star {
  Point point;
  byte speed;
};

struct Player player;
struct Star stars[NUM_STARS];
struct Enemy enemies[MAX_NUM_ENEMIES];

boolean last_a_button_val;
boolean last_b_button_val;
boolean is_gameover;
unsigned int score;
byte num_enemies;
byte bullet_speed_factor;
byte level;

#ifdef STM32F103xB
void beginGame();
void movePlayer();
void moveStars();
void moveEnemies();
void movePlayerBullets();
void drawScore();
void moveEnemiesBullet();
void drawPlayer();
void drawStars();
void drawEnemies();
void drawPlayerBullets();
void drawEnemiesBullet();
void checkEnemyCollision();
void checkPlayerCollision();
void initialize();
void displayTitle();
void spawnStar(byte i);
void spawnEnemy(byte i);
void shiftLevel();
void setLevel(byte lv, byte ne, float spd);
void playTone(unsigned int frequency, unsigned long duration);
void displayGameover();
Vector2 calcDelta(Vector2 v);
#endif /* STM32F103xB */

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);

  for (byte i = 0; i < MAX_NUM_ENEMIES; i++) {
    enemies[i].rect = ENEMY_RECT;
  }
  player.rect = PLAYER_RECT;

  beginGame();
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  if (is_gameover) {
    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
      beginGame();
    }
    return;
  }

  arduboy.clear();

  movePlayer();
  moveStars();
  moveEnemies();
  movePlayerBullets();
  moveEnemiesBullet();

  drawScore();
  drawPlayer();
  drawStars();
  drawEnemies();
  drawPlayerBullets();
  drawEnemiesBullet();

  checkEnemyCollision();
  checkPlayerCollision();

  arduboy.display();
}

void beginGame() {
  initialize();

  displayTitle();
}

void initialize() {
  arduboy.initRandomSeed();

  score = 0;

  player.rect.x = (WIDTH / 4) - (CHAR_WIDTH * 3 / 2);
  player.rect.y = (HEIGHT / 2) - (CHAR_HEIGHT / 2);

  for (byte i = 0; i < NUM_STARS; i++) {
    spawnStar(i);
  }

  for (byte i = 0; i < MAX_NUM_ENEMIES; i++) {
    spawnEnemy(i);
  }

  for (byte i = 0; i < NUM_PLAYER_BULLETS; i++) {
    player.bullets[i].enabled = false;
    player.bullets[i].point.x = 0;
    player.bullets[i].point.y = 0;
  }

  for (byte i = 0; i < MAX_NUM_ENEMIES; i++) {
    enemies[i].bullet.enabled = false;
    enemies[i].bullet.point.x = 0;
    enemies[i].bullet.point.y = 0;
  }

  is_gameover = false;

  shiftLevel();
}

void shiftLevel() {
  switch (score) {
    case 0:
      setLevel(1, 1, 1.4);
      break;
    case 1:
      setLevel(2, 2, 1.4);
      break;
    case 3:
      setLevel(3, 2, 1.4);
      break;
    case 7:
      setLevel(4, 3, 1.5);
      break;
    case 16:
      setLevel(5, 3, 1.6);
      break;
    case 25:
      setLevel(6, 4, 1.8);
      break;
    case 37:
      setLevel(7, 4, 2.0);
      break;
    case 49:
      setLevel(8, 5, 2.3);
      break;
    case 64:
      setLevel(9, 5, 2.4);
      break;
    case 79:
      setLevel(10, 6, 2.6);
      break;
    case 97:
      setLevel(11, 6, 2.8);
      break;
    case 115:
      setLevel(12, 7, 3.1);
      break;
    case 136:
      setLevel(13, 7, 3.4);
      break;
    case 157:
      setLevel(14, MAX_NUM_ENEMIES, 3.7);
      break;
    case 181:
      setLevel(15, MAX_NUM_ENEMIES, 4.1);
      break;
    default:
      break;
  }
}

void setLevel(byte lv, byte ne, float spd) {
  level = lv;
  num_enemies = ne;
  bullet_speed_factor = spd;
}

void displayTitle() {
  arduboy.clear();
  arduboy.setCursor((WIDTH / 2) - (CHAR_WIDTH * 15 / 2), (HEIGHT / 2) - (CHAR_HEIGHT / 2));
  arduboy.print("[ CosmicPods ]");
  arduboy.display();
  arduboy.invert(false);
  delay(250);
  playTone(4186, 225);
  delay(300);
  playTone(4186, 150);
  delay(150);
  playTone(4699, 150);
  delay(150);
  playTone(5274, 150);
  delay(150);
  playTone(6272, 600);
  delay(850);
}

void spawnEnemy(byte i) {
  enemies[i].rect.x = random(WIDTH + 20, WIDTH * 2);
  enemies[i].rect.y = random(0, HEIGHT - 12);
}

void spawnStar(byte i) {
  stars[i].point.x = random(WIDTH, WIDTH * 2);
  stars[i].point.y = random(0, HEIGHT);
  stars[i].speed = random(1, 5);
}

void spawnPlayerBullet(byte i) {
  player.bullets[i].enabled = true;
  player.bullets[i].point.x = player.rect.x + 16;
  player.bullets[i].point.y = player.rect.y + 3;
  playTone(4800, 50);
  delay(10);
  playTone(3200, 50);
  delay(10);
  playTone(1600, 50);
  delay(10);
  playTone(0, 50);
}

void spawnEnemyBullet(byte i) {
  enemies[i].bullet.enabled = true;
  enemies[i].bullet.point.x = enemies[i].rect.x - 4;
  enemies[i].bullet.point.y = enemies[i].rect.y + 4;

  Vector2 orig_delta;
  orig_delta.x = player.rect.x - enemies[i].rect.x;
  orig_delta.y = player.rect.y - enemies[i].rect.y;

  Vector2 new_delta = calcDelta(orig_delta);

  enemies[i].bullet.delta.x = new_delta.x;
  enemies[i].bullet.delta.y = new_delta.y;
}

Vector2 calcDelta(Vector2 v) {
  float mag = bullet_speed_factor / sqrt(v.x * v.x + v.y * v.y);

  Vector2 v2;
  v2.x = v.x * mag;
  v2.y = v.y * mag;

  return v2;
}

void movePlayer() {
  if (arduboy.pressed(RIGHT_BUTTON) && (player.rect.x < X_MAX)) {
    player.rect.x++;
  }

  if (arduboy.pressed(LEFT_BUTTON) && (player.rect.x > 0)) {
    player.rect.x--;
  }

  if (arduboy.pressed(UP_BUTTON) && (player.rect.y > 0)) {
    player.rect.y--;
  }

  if (arduboy.pressed(DOWN_BUTTON) && (player.rect.y < Y_MAX)) {
    player.rect.y++;
  }

  boolean is_just_press_a_button = arduboy.pressed(A_BUTTON) && !last_a_button_val;
  boolean is_just_press_b_button = arduboy.pressed(B_BUTTON) && !last_b_button_val;
  if (is_just_press_a_button || is_just_press_b_button) {
    for (byte i = 0; i < NUM_PLAYER_BULLETS; i++) {
      if (!player.bullets[i].enabled) {
        spawnPlayerBullet(i);
        break;
      }
    }
  }
  last_a_button_val = arduboy.pressed(A_BUTTON);
  last_b_button_val = arduboy.pressed(B_BUTTON);
}

void moveStars() {
  for (byte i = 0; i < NUM_STARS; i++) {
    stars[i].point.x -= stars[i].speed;
    if (stars[i].point.x < 0) {
      spawnStar(i);
    }
  }
}

void moveEnemies() {
  for (byte i = 0; i < num_enemies; i++) {
    enemies[i].rect.x--;

    if (
      (level > 2)
      && (enemies[i].rect.x > player.rect.x + 10)
      && (enemies[i].rect.x < WIDTH - 10)
      && (!enemies[i].bullet.enabled)
      && (random(0, 50) == 10)
    ) {
      spawnEnemyBullet(i);
    }

    if (enemies[i].rect.x <= 0) {
      spawnEnemy(i);
    }
  }
}

void movePlayerBullets() {
  for (byte i = 0; i < NUM_PLAYER_BULLETS; i++) {
    if (player.bullets[i].enabled) {
      player.bullets[i].point.x += 2;
      if (player.bullets[i].point.x > WIDTH) {
        player.bullets[i].enabled = false;
      }
    }
  }
}

void moveEnemiesBullet() {
  for (byte i = 0; i < num_enemies; i++) {
    if (enemies[i].bullet.enabled) {
      enemies[i].bullet.point.x += enemies[i].bullet.delta.x;
      enemies[i].bullet.point.y += enemies[i].bullet.delta.y;
      if (
        (enemies[i].bullet.point.x <= 0)
        || (enemies[i].bullet.point.y <= 0)
        || (enemies[i].bullet.point.y >= HEIGHT)
      ) {
        enemies[i].bullet.enabled = false;
      }
    }
  }
}

void checkEnemyCollision() {
  for (byte j = 0; j < num_enemies; j++) {
    boolean is_col = false;
    for (byte i = 0; i < NUM_PLAYER_BULLETS; i++) {
      if (player.bullets[i].enabled) {
        is_col = arduboy.collide(player.bullets[i].point, enemies[j].rect);
        if (is_col) {
          player.bullets[i].enabled = false;
          break;
        }
      }
    }
    if (is_col) {
      playTone(200, 100);
      score++;
      shiftLevel();
      arduboy.fillCircle(enemies[j].rect.x + 3, enemies[j].rect.y + 6, 6, 1);
      arduboy.fillCircle(enemies[j].rect.x + 7, enemies[j].rect.y + 2, 3, 1);
      spawnEnemy(j);
    }
  }
}

void checkPlayerCollision() {
  for (byte i = 0; i < num_enemies; i++) {
    Point tmp_point;
    tmp_point.x = enemies[i].bullet.point.x;
    tmp_point.y = enemies[i].bullet.point.y;
    boolean is_enemy_col = arduboy.collide(enemies[i].rect, player.rect);
    boolean is_bullet_col = (enemies[i].bullet.enabled) && (arduboy.collide(tmp_point, player.rect));
    if ((is_enemy_col) || (is_bullet_col)) {
      displayGameover();
      return;
    }
  }
}

void displayGameover() {
  arduboy.setCursor((WIDTH / 2) - (CHAR_WIDTH * 9 / 2), (HEIGHT / 2) - (CHAR_HEIGHT / 2));
  arduboy.print("GAME OVER");
  arduboy.invert(true);
  is_gameover = true;
  playTone(66, 500);
  arduboy.display();
  delay(1200);
}

void drawScore() {
  arduboy.setCursor(1, HEIGHT - 8);
  arduboy.print("SCORE:");
  arduboy.setCursor(38, HEIGHT - 8);
  arduboy.print(score);
}

void drawPlayer() {
  byte x = player.rect.x;
  byte y = player.rect.y;

  arduboy.setCursor(x, y);
  arduboy.print(":=>");
  arduboy.setCursor(x - 5, y);
  arduboy.print("_");
  arduboy.setCursor(x - 5, y - 3);
  arduboy.print("_");
  arduboy.setCursor(x - 5, y - 6);
  arduboy.print("_");
}

void drawStars() {
  for (byte i = 0; i < NUM_STARS; i++) {
    byte x = stars[i].point.x;
    byte y = stars[i].point.y;

    arduboy.drawPixel(x, y, WHITE);
  }
}

void drawEnemies() {
  for (byte i = 0; i < num_enemies; i++) {
    byte x = enemies[i].rect.x;
    byte y = enemies[i].rect.y;

    arduboy.drawCircle(x + 3, y + 3, 3, WHITE);
    arduboy.drawPixel(x + 2, y + 3, WHITE);
    arduboy.drawRect(x - 2, y + 3, 3, 3, WHITE);
    arduboy.drawPixel(x, y + 4, BLACK);
    arduboy.drawLine(x + 1, y + 6, x + 2, y + 9, WHITE);
    arduboy.drawLine(x + 4, y + 6, x + 5, y + 9, WHITE);
    arduboy.drawLine(x + 7, y + 6, x + 8, y + 9, WHITE);
  }
}

void drawPlayerBullets() {
  for (byte i = 0; i < NUM_PLAYER_BULLETS; i++) {
    if (player.bullets[i].enabled) {
      byte x = player.bullets[i].point.x;
      byte y = player.bullets[i].point.y;
      arduboy.drawRect(x, y, 2, 2, WHITE);
    }
  }
}

void drawEnemiesBullet() {
  byte i;
  int x, y;

  for (i = 0; i < num_enemies; i++) {
    if (enemies[i].bullet.enabled) {
      x = enemies[i].bullet.point.x;
      y = enemies[i].bullet.point.y;
      arduboy.drawCircle(x, y, 2, WHITE);
    }
  }
}

void playTone(unsigned int frequency, unsigned long duration) {
  if (arduboy.audio.enabled()) {
    beep.tone(frequency, duration);
  }
}

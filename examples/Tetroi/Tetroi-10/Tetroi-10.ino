//   >>>>> Tetroi Version 1.0 for ARDUBOY  GPLv3 <<<<
//         Programmer: (c) Roger Buehler 2023
//         Contact EMAIL: tscha70@gmail.com
//         Official repository:  https://github.com/tscha70/
//  Tetroi version 1 is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// This project was inspired by FamTrinli's channel on YouTube: https://www.youtube.com/@FamTrinli
// and his kindly provided source code in the video description.

// The victory sound on new highscore is strongly related to the intro sound from FlappyBall by Chris Martinez and Scott Allen

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include <EEPROM.h>
#include "Sprites.h"

Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

//********* PROGRAM VERSION **********************
#define PROGRAM_VERSION 10  // next version would be 2, 3, 4.. and so on
//************************************************

#define M 19
#define N 10
#define frameOffset 108 //102
#define boderOffset 2
#define colorNum 1
#define moveDelay 200
#define moveFast 15
#define dropDelay 150
#define fastDrop 15
#define slowDrop 800
#define animationDelay 150
#define EEPROM_MAGIC_VALUE 0x13  // Arbitrary value, to help us know whether we should reinitialize the high score, like in case some other sketch was using EEPROM before.
#define EEPROM_MAGIC_ADDRESS (EEPROM_STORAGE_SPACE_START + 0)
#define EEPROM_HIGHSCORE_ADDRESS (EEPROM_STORAGE_SPACE_START + 1)

unsigned int elapsedTime = 0;
unsigned int startTime = 0;
unsigned int moveLeftTimer = 0;
unsigned int moveRightTimer = 0;
unsigned int dropTimer = 0;
bool isMoveLeftEnabled = true;
bool isMoveRightEnabled = true;
bool isRotateEnabled = true;
unsigned int delta = 0;

// field variables
uint8_t field[M][N] = { 0 };
uint8_t fieldBefore[M][N] = { 0 };
uint8_t reclaimedLines[4];
uint8_t nextFigure = 8;
uint8_t figure = 0;
unsigned int lines = 0;
unsigned int score = 0;
unsigned int highscore = 0;
uint8_t level = 1;
int dy = 0;
int rotate = 0;
bool isGameOver = 0;
unsigned int standardDrop = slowDrop;
unsigned int retard = standardDrop;
bool isDownFallEnabled = true;
bool isNextMovePossible = true;
bool isNewHighscore = false;

Point a[4], b[4];

const uint8_t figures[7][4] = {
  1, 5, 3, 7,  // I = 0
  2, 5, 4, 7,  // Z = 1
  3, 5, 4, 6,  // S = 2
  3, 5, 4, 7,  // T = 3
  3, 5, 7, 6,  // L = 4
  2, 5, 3, 7,  // J = 5
  2, 3, 4, 5,  // O = 6
};

void TETROI() {
  lines = 0;
  score = 0;
  level = 1;
  isGameOver = 0;
  standardDrop = slowDrop;
  nextFigure = 9;  // blank
  figure = 0;
  dy = 0;
  rotate = 0;
  elapsedTime = 0;
  retard = standardDrop;
  isDownFallEnabled = true;
  isNextMovePossible = true;
  isNewHighscore = false;
  randomSeed(millis());
  sound.tone(NOTE_E7, 50);

  while (arduboy.pressed(A_BUTTON)) {
    //nop
    // wait till button released
  }
  // initialize all fields
  RESET_GAME_BOARD();

  INITIALIZE_FIGURE(random(0, 7));
  nextFigure = random(0, 7);

  startTime = millis();
  while (!isGameOver) {
    elapsedTime = millis() - startTime;

    // in this orientation the up-button is the right-button (everything is turned by 90 degrees)
    GET_KEYPAD_INPUT();

    //// <- Move (lef/right)-> ///
    MOVE_PIECE_LEFT_RIGHT();

    //// Rotate //////
    ROTATE_PIECE();

    //// Tick ///// (game over)
    GAME_TICK();

    //// Check for complete lines and update the score and board
    UPDATE_BOARD();

    dy = 0;
    rotate = 0;
    retard = standardDrop;
  }
  SHOW_GAMEOVER();
}

void setup() {
  // initiate arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(30);

  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // first we clear our screen to black
  arduboy.clear();
  arduboy.drawBitmap(0, 0, TETROI_INTRO, 128, 64, 1);
  DISPLAY_VERSION(51, 5, PROGRAM_VERSION);


  // then we finaly we tell the arduboy to display what we just wrote to the display
  arduboy.display();
}


// our main game loop, this runs once every cycle/frame.
// this is where our game logic goes.
void loop() {
  if (arduboy.pressed(B_BUTTON)) {
    if (!(arduboy.nextFrame()))
      return;

    // first we clear our screen to black
    arduboy.clear();
    sound.tone(NOTE_E5, 50);
    UPDATE_SCORE_BOARD();
    Sprites::drawSelfMasked(0, 0, BG, 0);

    // Show highscore and wait for button 'A' to start the game
    highscore = loadHighscore();
    SHOW_HIGHSCOREANIMATION(100, highscore);

    CLEAR_SCREEN();
    TETROI();
  }
}

// check for complete lines and update the board
void UPDATE_BOARD() {
  ///////check lines//////////
  CHECK_FOR_COMPLETE_LINES();

  ///// refresh screen
  UPDATE_GAME_BOARD();

  UPDATE_SCORE_BOARD();
  Sprites::drawSelfMasked(0, 0, BG, 0);
  arduboy.display();
}

void UPDATE_SCORE_BOARD() {
  // cover up the nasty first row once the game is over
  Sprites::drawOverwrite(108, 0, SCORE_BOARD_PANEL, 0);
  DISPLAY_SCORE(score);
  DISPLAY_LINES(lines);
  DISPLAY_LEVEL(level);
  if (isGameOver) nextFigure = 8;  // blank
  DISPLAY_NEXT_TILE(nextFigure);
}

// show scores
void DISPLAY_SCORE(uint16_t score) {
  const uint8_t yOffset = 120;
  const uint8_t xOffset = 57;
  const uint8_t figureWidth = 5;
  uint8_t myDigits[5];
  SPLITDIGITS(score, myDigits);
  for (int i = 4; i >= 0; i--) {
    if (myDigits[i] > 0 || score > pow(10, i) || (score == 0 && i == 0)) {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresBig, myDigits[i]);
    } else {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresBig, 10);
    }
  }
}

// show scores
void DISPLAY_HIGHSCORE(uint16_t score, uint8_t xOffset, uint8_t yOffset) {
  const uint8_t figureWidth = 5;
  uint8_t myDigits[5];
  SPLITDIGITS(score, myDigits);
  for (int i = 4; i >= 0; i--) {
    if (myDigits[i] > 0 || score > pow(10, i) || (score == 0 && i == 0)) {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresBig, myDigits[i]);
    } else {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresBig, 10);
    }
  }
}

// show number of lines played
void DISPLAY_LINES(uint16_t lines) {
  const uint8_t yOffset = 111;
  const uint8_t xOffset = 31;
  const uint8_t figureWidth = 4;
  uint8_t myDigits[5];
  SPLITDIGITS(lines, myDigits);
  for (int i = 2; i >= 0; i--) {
    if (myDigits[i] > 0 || lines > pow(10, i) || (lines == 0 && i == 0)) {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresSmall, myDigits[i]);
    } else {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresSmall, 10);
    }
  }
}

// show the current level
void DISPLAY_LEVEL(uint8_t level) {
  const uint8_t yOffset = 111;
  const uint8_t xOffset = 58;
  const uint8_t figureWidth = 4;
  uint8_t myDigits[5];
  SPLITDIGITS(level, myDigits);
  for (int i = 1; i >= 0; i--) {
    if (myDigits[i] > 0 || level > pow(10, i) || (level == 0 && i == 0)) {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresSmall, myDigits[i]);
    } else {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresSmall, 10);
    }
  }
}

void DISPLAY_VERSION(uint8_t xOffset, uint8_t yOffset, uint8_t version) {
  const uint8_t figureWidth = 4;
  uint8_t myDigits[5];
  SPLITDIGITS(version, myDigits);
  for (int i = 1; i >= 0; i--) {
    if (myDigits[i] > 0 || version > pow(10, i) || (version == 0 && i == 0)) {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresSmall, myDigits[i]);
    } else {
      Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresSmall, 10);
    }
  }
}


void CLEAR_SCREEN() {
  Sprites::drawOverwrite(0, 0, BG, 0);
  arduboy.display();
}

void DISPLAY_NEXT_TILE(uint8_t tile) {
  Sprites::drawOverwrite(118, 0, Tiles, tile);
}

/////CHECK check if the border-boundaries are met
/////or a piece is colliding with the fields in the grid
bool check() {
  for (int i = 0; i < 4; i++)
    if (a[i].y < 0 || a[i].y >= N || a[i].x >= M) return 0;
    else if (field[a[i].x][a[i].y]) return 0;
  return 1;
};

void INITIALIZE_FIGURE(int n) {
  isDownFallEnabled = false;
  for (int i = 0; i < 4; i++) {
    a[i].x = figures[n][i] % 2;
    a[i].y = figures[n][i] / 2;
  }

  for (int i = 0; i < 4; i++) {
    b[i] = a[i];
    a[i].y += 3;
  }
  int previousFigure = figure;
  figure = n;
  if (!check()) {
    for (int i = 0; i < 4; i++) {
      if (b[i].x == 0) {
        // game over
        isGameOver = true;
        break;
      }
    }
    if (isGameOver) {
      if (score > highscore) {
        isNewHighscore = true;
        saveHighscore(score);
      }
      nextFigure = 8;
      figure = previousFigure;
      for (int i = 0; i < 4; i++) a[i] = b[i];
      for (int i = 0; i < 4; i++) {
        b[i] = a[i];
        a[i].x += -1;
        a[i].y += 3;
      }
    }
  }
  dropTimer = millis();
}

void MOVE_PIECE_LEFT_RIGHT() {
  for (int i = 0; i < 4; i++) {
    b[i] = a[i];
    a[i].y += dy;  // left and right
  }
  if (!check())
    for (int i = 0; i < 4; i++) a[i] = b[i];
}

void ROTATE_PIECE() {
  //ccw
  if (rotate == -1) {
    if (figure != 6) {
      //no rotation for the cube tetroid ('O')
      Point p = a[1];  //center of rotation
      for (int i = 0; i < 4; i++) {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;
        a[i].x = p.x - x;
        a[i].y = p.y + y;
      }
      if (!check())
        for (int i = 0; i < 4; i++) a[i] = b[i];
    }
    //cw
  } else if (rotate == 1) {
    if (figure != 6) {
      //no rotation for the cube tetroid ('O')
      Point p = a[1];  //center of rotation
      for (int n = 0; n < 3; n++) {
        for (int i = 0; i < 4; i++) {
          int x = a[i].y - p.y;
          int y = a[i].x - p.x;
          a[i].x = p.x - x;
          a[i].y = p.y + y;
        }
      }
      if (!check())
        for (int i = 0; i < 4; i++) a[i] = b[i];
    }
  }
}

void CHECK_FOR_COMPLETE_LINES() {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      fieldBefore[i][j] = field[i][j];
    }
  }
  for (int i = 0; i < 4; i++) {
    reclaimedLines[i] = 0;
  }
  int k = M - 1;
  int numOfLines = 0;
  for (int i = M - 1; i >= 0; i--) {
    int count = 0;
    for (int j = 0; j < N; j++) {
      if (field[i][j]) count++;
      field[k][j] = field[i][j];
    }
    if (count < N) k--;
    else {
      // you got a line
      reclaimedLines[numOfLines] = i + 1;
      numOfLines += 1;
      lines += 1;
      if (lines % 10 == 0) {
        level += 1;
        if (standardDrop > 100) {
          standardDrop -= 100;
        }
      }
    }
  }
  /// clear the removed lines on the top
  for (int i = 0; i < numOfLines; i++) {
    for (int j = 0; j < N; j++) {
      field[i][j] = 0;
    }
  }

  if (numOfLines > 0) {
    sound.tone(NOTE_D4, 50);
    switch (numOfLines) {
      case 1:
        score += 100;
        break;
      case 2:
        score += 300;
        break;
      case 3:
        score += 500;
        break;
      case 4:
        score += 800;
        break;
    }
  }
}

void RESET_GAME_BOARD() {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      field[i][j] = 0;
      fieldBefore[i][j] = 0;
    }
  }
}

void GET_KEYPAD_INPUT() {  // in this orientation the up-button is the right-button (everything is turned by 90 degrees)
  if (arduboy.notPressed(RIGHT_BUTTON) && arduboy.notPressed(A_BUTTON)) {
    isRotateEnabled = true;
  }

  // reset fallDown
  if (arduboy.notPressed(LEFT_BUTTON)) {
    isDownFallEnabled = true;
    isNextMovePossible = true;
    dropTimer = millis();
  }
  // reset move left timer
  if (arduboy.notPressed(UP_BUTTON)) {
    isMoveLeftEnabled = true;
    moveLeftTimer = millis();
  }
  // reset move right timer
  if (arduboy.notPressed(DOWN_BUTTON)) {
    isMoveRightEnabled = true;
    moveRightTimer = millis();
  }
  // rotate ccw
  if (arduboy.pressed(RIGHT_BUTTON) && isRotateEnabled) {
    rotate = -1;
    isRotateEnabled = false;
    // rotate cw
  } else if (arduboy.pressed(A_BUTTON) && isRotateEnabled) {
    rotate = 1;
    isRotateEnabled = false;
    // move left
  } else if (arduboy.pressed(UP_BUTTON)) {
    delta = millis() - moveLeftTimer;
    if (isMoveLeftEnabled || delta > moveDelay) {
      isMoveLeftEnabled = false;
      dy = -1;
      delay(moveFast);
    }

    // move right
  } else if (arduboy.pressed(DOWN_BUTTON)) {
    delta = millis() - moveRightTimer;
    if (isMoveRightEnabled || delta > moveDelay) {
      isMoveRightEnabled = false;
      dy = 1;
      delay(moveFast);
    }
    // down
  } else if (arduboy.pressed(LEFT_BUTTON)) {
    delta = millis() - dropTimer;
    if (isDownFallEnabled) {
      if (delta > dropDelay) {
        retard = fastDrop;
      } else if (isNextMovePossible) {
        retard = fastDrop;
        isNextMovePossible = false;
      }
    }
    // pause game
  } else if (arduboy.pressed(B_BUTTON)) {
    sound.tone(NOTE_E7, 50);
    while (arduboy.pressed(B_BUTTON)) {  //noop
    }
    Sprites::drawOverwrite(54, 12, PAUSED, 0);
    arduboy.display();
    while (arduboy.notPressed(B_BUTTON)) {  //noop
    }
    while (arduboy.pressed(B_BUTTON)) {  //noop
    }
    sound.tone(NOTE_E7, 50);
    delay(300);
  }
}

void UPDATE_GAME_BOARD() {
  // refresh screen
  // draw tetramino
  Sprites::drawOverwrite(0, 0, BG, 0);
  for (int i = 0; i < 4; i++) {
    Sprites::drawSelfMasked(frameOffset - a[i].x * 6, boderOffset + a[i].y * 6, SquareTile, 5);
  }

  // check if any line are complete (full)
  bool anyLineReclaimed = false;
  for (int i = 0; i < 4; i++) {
    if (reclaimedLines[i] > 0)
      anyLineReclaimed = true;
  }

  // draw grid - before claim if any lines are complete
  if (anyLineReclaimed) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        if (fieldBefore[i][j] == 0) continue;
        Sprites::drawSelfMasked(frameOffset - i * 6, boderOffset + j * 6, SquareTile, 3);
      }
    }
  }

  // full line reclaimed - show flashing line
  for (int i = 0; i < 4; i++) {
    if (reclaimedLines[i] > 0) {
      Sprites::drawOverwrite(frameOffset - (reclaimedLines[i] - 1) * 6, boderOffset, BAR, 0);
    }
  }
  if (anyLineReclaimed == true) {
    UPDATE_SCORE_BOARD();
    Sprites::drawSelfMasked(0, 0, BG, 0);
    arduboy.display();
    delay(animationDelay);
  }
  for (int i = 0; i < 4; i++) {
    if (reclaimedLines[i] > 0) {
      Sprites::drawOverwrite(frameOffset - (reclaimedLines[i] - 1) * 6, boderOffset, BAR, 1);
    }
  }
  if (anyLineReclaimed == true) {
    UPDATE_SCORE_BOARD();
    Sprites::drawSelfMasked(0, 0, BG, 0);
    arduboy.display();
    delay(animationDelay);
  }

  // draw grid
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (field[i][j] == 0) continue;
      Sprites::drawSelfMasked(frameOffset - i * 6, boderOffset + j * 6, SquareTile, 3);
    }
  }
}

void SHOW_GAMEOVER() {
  if (isNewHighscore) {
    Sprites::drawOverwrite(20, 4, NEW_HIGHSCORE, 0);
    DISPLAY_HIGHSCORE(score, 39, 34);
    arduboy.display();
    // celebrate!!
    sound.tones(VICTORY_SOUND);
    for (int i = 0; i < 55; i++) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BLUE_LED, HIGH);
      delay(35);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(BLUE_LED, LOW);
      delay(150);
    }
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
  } else {
    Sprites::drawOverwrite(64, 5, GAME_OVER, 0);
    arduboy.display();
    sound.tone(NOTE_A3, 500);
    for (int i = 0; i < 4; i++) {
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      delay(150);
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      delay(150);
    }
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    sound.tone(NOTE_A1, 200);
    delay(200);
    sound.tone(NOTE_A0, 1000);
    delay(1000);
  }
}

void GAME_TICK() {
  if (elapsedTime > retard) {
    // move one down
    for (int i = 0; i < 4; i++) {
      b[i] = a[i];
      a[i].x += 1;
    }
    if (!check()) {
      for (int i = 0; i < 4; i++) field[b[i].x][b[i].y] = colorNum;

      // update the board immediately before initializing the next figure
      UPDATE_BOARD();

      INITIALIZE_FIGURE(nextFigure);
      nextFigure = random(0, 7);
      isDownFallEnabled = false;
    }

    // reset timer
    startTime = millis();
  }
}

void SHOW_HIGHSCOREANIMATION(uint8_t aniDelay, unsigned int hscore) {
  while (true) {
    Sprites::drawOverwrite(20, 4, HIGHSCORE, 0);
    DISPLAY_HIGHSCORE(hscore, 39, 68);
    arduboy.display();
    if (arduboy.pressed(A_BUTTON)) break;
    delay(aniDelay);
    Sprites::drawOverwrite(20, 4, HIGHSCORE, 1);
    DISPLAY_HIGHSCORE(hscore, 39, 68);
    arduboy.display();
    if (arduboy.pressed(A_BUTTON)) break;
    delay(aniDelay);
    Sprites::drawOverwrite(20, 4, HIGHSCORE, 2);
    DISPLAY_HIGHSCORE(hscore, 39, 68);
    arduboy.display();
    if (arduboy.pressed(A_BUTTON)) break;
    delay(aniDelay);
  }
}



// splits each digit in it's own byte
void SPLITDIGITS(uint16_t val, uint8_t *d) {
  d[4] = val / 10000;
  d[3] = (val - (d[4] * 10000)) / 1000;
  d[2] = (val - (d[3] * 1000) - (d[4] * 10000)) / 100;
  d[1] = (val - (d[2] * 100) - (d[3] * 1000) - (d[4] * 10000)) / 10;
  d[0] = val - (d[1] * 10) - (d[2] * 100) - (d[3] * 1000) - (d[4] * 10000);
}



void saveHighscore(unsigned int value) {
  EEPROM.update(EEPROM_MAGIC_ADDRESS, EEPROM_MAGIC_VALUE);
  EEPROM.put(EEPROM_HIGHSCORE_ADDRESS, value);
}

unsigned int loadHighscore() {
  unsigned int value = 0;
  if (EEPROM.read(EEPROM_MAGIC_ADDRESS) == EEPROM_MAGIC_VALUE) {
    EEPROM.get(EEPROM_HIGHSCORE_ADDRESS, value);
  }
  return value;
}

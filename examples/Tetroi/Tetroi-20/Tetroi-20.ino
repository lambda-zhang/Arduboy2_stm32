//   >>>>> Tetroi Version 1.0 for ARDUBOY  GPLv3 <<<<
//         Programmer: (c) Roger Buehler 2024
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
#define PROGRAM_VERSION 20  // next version would be 2, 3, 4.. and so on
//************************************************

#define M 21
#define N 10
#define frameOffset 120  //114  //108  //102
#define boderOffset 2
#define colorNum 1
#define moveDelay 150 // 200
#define moveFast 10
#define dropDelay 150 // 150
#define fastDrop 5 // 15
#define animationDelay 150

#define EEPROM_MAGIC_VALUE_SPEED 0x74  // Arbitrary value, to help us know whether we should reinitialize the speed, like in case some other sketch was using EEPROM before.
#define EEPROM_MAGIC_ADDRESS_SPEED (EEPROM_STORAGE_SPACE_START + 16)
#define EEPROM_SPEED_ADDRESS (EEPROM_STORAGE_SPACE_START + 17)
uint8_t magics[5] = { 0x30, 0x65, 0x38, 0x58, 0x20 };

unsigned int speed = 2;  //default
unsigned int speeds[5] = { 1700, 1200, 800, 700, 500 };
unsigned int bonuses[5] = { 100, 200, 400, 500, 800 };
unsigned int fourInARowCounter = 0;
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
bool anyLineReclaimed = false;
uint8_t nextFigure = 8;
uint8_t figure = 0;
unsigned int lines = 0;
unsigned int score = 0;
unsigned int highscore = 0;
unsigned int bonus = 0;
uint8_t level = 1;
int dy = 0;
int rotate = 0;
bool isGameOver = 0;
unsigned int slowDrop = speeds[speed];
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
  fourInARowCounter = 0;
  score = bonuses[speed];
  bonus = 0;
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
  anyLineReclaimed = false;
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

    //// in this orientation the up-button is the right-button (everything is turned by 90 degrees)
    GET_KEYPAD_INPUT();

    //// <- Move (lef/right)-> ///
    MOVE_PIECE_LEFT_RIGHT();

    //// Rotate //////
    ROTATE_PIECE();

    //// Tick ///// (game over)
    GAME_TICK();

    //// Check for complete lines and update the score and board
    UPDATE_BOARD();

    // reset input and speed
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
  display_version(51, 5, PROGRAM_VERSION);

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
    update_score_board();
    Sprites::drawSelfMasked(0, 0, BG, 0);

    // Speed: load the default speed from EEPROM
    speed = loadSpeed();
    slowDrop = speeds[speed];

    // Show highscore and wait for button 'A' to start the game
    highscore = loadHighscore(speed);
    SHOW_HIGHSCOREANIMATION(100);

    //CLEAR_SCREEN();
    TETROI();
  }
}

// check for complete lines and update the board
void UPDATE_BOARD() {
  ///////check lines//////////
  check_for_complete_lines();

  ///// refresh screen
  update_game_board();

  update_score_board();
  Sprites::drawSelfMasked(0, 0, BG, 0);
  arduboy.display();
}

void update_score_board() {
  // cover up the nasty first row once the game is over
  Sprites::drawOverwrite(108, 0, SCORE_BOARD_PANEL, 0);
  display_score(score);
  display_lines(lines);
  display_level(level);
  if (isGameOver) nextFigure = 8;  // blank
  display_next_tile(nextFigure);
}

// show scores
void display_score(uint16_t score) {
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
void display_lines(uint16_t lines) {
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
void display_level(uint8_t level) {
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

void display_version(uint8_t xOffset, uint8_t yOffset, uint8_t version) {
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

void display_next_tile(uint8_t tile) {
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
  // interrupt dropping
  isDownFallEnabled = false;

  // intitialize the figure
  for (int i = 0; i < 4; i++) {
    a[i].x = figures[n][i] % 2;
    a[i].y = figures[n][i] / 2;
  }

  int offset = 3;
  if (n == 0) {
    offset = 2;
  }

  // place figure on board
  for (int i = 0; i < 4; i++) {
    b[i] = a[i];
    a[i].x += offset;
    a[i].y += 3;
  }

  // keep the previous figure in mind
  int previousFigure = figure;

  // store the current figure
  figure = n;

  // check if figure can be placed on board
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
        saveHighscore(score, speed);
      }

      // show heart as next figure
      nextFigure = 8;
    }
  }

  // for each figure you get an extrapoint
  if (!isGameOver) { score += 1; }
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
  //no rotation for the cube tetroid ('O')
  if (figure == 6) { return; }
  if (rotate == 1 || rotate == -1) {
    Point p = a[1];  //center of rotation
    for (int i = 0; i < 4; i++) {
      int y = a[i].y - p.y;
      int x = a[i].x - p.x;
      //rotate== -1: (ccw-rotation) (x, y) --> (-y, x)
      //rotate== +1: (cw-rotation)  (x, y) --> (y, -x)
      a[i].x = p.x + (rotate * y);
      a[i].y = p.y - (rotate * x);
    }

    if (!check())
      for (int i = 0; i < 4; i++) a[i] = b[i];
  }
}

void check_for_complete_lines() {
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
        fourInARowCounter = 0;
        break;
      case 2:
        score += 300;
        fourInARowCounter = 0;
        break;
      case 3:
        score += 500;
        fourInARowCounter = 0;
        break;
      case 4:
        score += 800;
        if (fourInARowCounter > 0) {
          bonus = fourInARowCounter * bonuses[speed];
          score += bonus;
        }
        fourInARowCounter += 1;
        break;
    }
  }
}

bool display_bonus(unsigned int score) {
  bonus = 0;
  if (score == 0) { return; }
  Sprites::drawOverwrite(0, 0, BG, 0);
  update_score_board();
  Sprites::drawSelfMasked(0, 0, BG, 0);
  draw_grid();
  arduboy.display();
  sound.tones(BONUS_SOUND);
  const uint8_t xOffset = 51;
  const uint8_t figureWidth = 5;
  uint8_t yOffset = 44;
  uint8_t myDigits[5];
  for (; yOffset <= 124; yOffset += 2) {
    Sprites::drawSelfMasked(0, 0, BG, 0);
    draw_grid();
    Sprites::drawOverwrite(yOffset - 5, xOffset - 47, BONUS, 0);
    SPLITDIGITS(score, myDigits);
    for (int i = 3; i >= 0; i--) {
      if (myDigits[i] > 0 || score > pow(10, i) || (score == 0 && i == 0)) {
        Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresBig, myDigits[i]);
      } else {
        Sprites::drawOverwrite(yOffset, xOffset - (i * figureWidth), FiguresBig, 10);
      }
    }

    Sprites::drawSelfMasked(yOffset - 5, xOffset - 47, BONUS, 0);
    if (yOffset > 100) {
      update_score_board();
      Sprites::drawSelfMasked(0, 0, BG, 0);
    }
    arduboy.display();
    delay(26);
  }
  Sprites::drawOverwrite(0, 0, BG, 0);
  draw_grid();
  update_score_board();
  Sprites::drawSelfMasked(0, 0, BG, 0);
  arduboy.display();
  delay(50);
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
    Sprites::drawSelfMasked(54, 12, PAUSED, 0);
    arduboy.display();
    while (arduboy.notPressed(B_BUTTON)) {  //noop
    }
    while (arduboy.pressed(B_BUTTON)) {  //noop
    }
    sound.tone(NOTE_E7, 50);
    delay(300);
  }
}

void update_game_board() {
  // refresh screen

  // check if any line are complete (full)
  anyLineReclaimed = false;
  for (int i = 0; i < 4; i++) {
    if (reclaimedLines[i] > 0)
      anyLineReclaimed = true;
    break;
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
    update_score_board();
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
    update_score_board();
    Sprites::drawSelfMasked(0, 0, BG, 0);
    arduboy.display();
    delay(animationDelay);
  }

  // show the bonus animation
  display_bonus(bonus);

  // draw tetramino
  draw_tetramino();

  // draw grid;
  draw_grid();
}

void draw_grid() {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      if (field[i][j] == 0) continue;
      Sprites::drawSelfMasked(frameOffset - i * 6, boderOffset + j * 6, SquareTile, 3);
    }
  }
}

void draw_tetramino() {
  Sprites::drawOverwrite(0, 0, BG, 0);
  for (int i = 0; i < 4; i++) {
    Sprites::drawSelfMasked(frameOffset - a[i].x * 6, boderOffset + a[i].y * 6, SquareTile, 5);
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

    //get some extrapoints!
    if (retard == fastDrop) { score++; }

    // reset timer
    startTime = millis();
  }
}

void SHOW_HIGHSCOREANIMATION(uint8_t aniDelay) {
  bool doLoop = true;
  bool enableDecreaseSpeed = true;
  bool enableIncreaseSpeed = true;
  while (doLoop) {
    const int BXO = 4;
    const int BYO = 4;
    const int RXO = 39;
    const int RYO = 72;
    for (int i = 0; i < 3; i++) {
      // debounce buttons
      if (arduboy.notPressed(UP_BUTTON)) { enableDecreaseSpeed = true; }
      if (arduboy.notPressed(DOWN_BUTTON)) { enableIncreaseSpeed = true; }
      score = bonuses[speed];
      lines = 0;
      level = 1;
      update_score_board();
      Sprites::drawSelfMasked(0, 0, BG, 0);
      Sprites::drawOverwrite(BXO, BYO, HIGHSCORE, i);
      DISPLAY_HIGHSCORE(highscore, RXO, RYO);
      Sprites::drawOverwrite(6, 7, SPEEDBAR, speed);
      arduboy.display();
      if (arduboy.pressed(A_BUTTON)) {
        doLoop = false;
        break;
      }
      if (arduboy.pressed(UP_BUTTON) && enableDecreaseSpeed) {
        enableDecreaseSpeed = false;
        decreaseSpeed();
      }
      if (arduboy.pressed(DOWN_BUTTON) && enableIncreaseSpeed) {
        enableIncreaseSpeed = false;
        increaseSpeed();
      }

      delay(aniDelay);
    }
  }
}

// splits each digit in it's own byte
void SPLITDIGITS(uint16_t val, uint8_t* d) {
  d[4] = val / 10000;
  d[3] = (val - (d[4] * 10000)) / 1000;
  d[2] = (val - (d[3] * 1000) - (d[4] * 10000)) / 100;
  d[1] = (val - (d[2] * 100) - (d[3] * 1000) - (d[4] * 10000)) / 10;
  d[0] = val - (d[1] * 10) - (d[2] * 100) - (d[3] * 1000) - (d[4] * 10000);
}


void saveHighscore(unsigned int value, unsigned int index) {

  EEPROM.update(EEPROM_STORAGE_SPACE_START + index, magics[index]);
  EEPROM.put(EEPROM_STORAGE_SPACE_START + index * 2 + 5, value);
}

unsigned int loadHighscore(unsigned int index) {
  unsigned int value = 0;
  if (EEPROM.read(EEPROM_STORAGE_SPACE_START + index) == magics[index]) {
    EEPROM.get(EEPROM_STORAGE_SPACE_START + index * 2 + 5, value);
  }
  return value;
}

unsigned int loadSpeed() {
  unsigned int value = 2;
  if (EEPROM.read(EEPROM_MAGIC_ADDRESS_SPEED) == EEPROM_MAGIC_VALUE_SPEED) {
    EEPROM.get(EEPROM_SPEED_ADDRESS, value);
  }
  return value;
}

void saveSpeed(unsigned int value) {
  EEPROM.update(EEPROM_MAGIC_ADDRESS_SPEED, EEPROM_MAGIC_VALUE_SPEED);
  EEPROM.put(EEPROM_SPEED_ADDRESS, value);
}

void decreaseSpeed() {
  if (speed > 0) {
    speed--;
    updateSpeedAndHighscore();
  }
}

void increaseSpeed() {
  if (speed < 4) {
    speed++;
    updateSpeedAndHighscore();
  }
}

void updateSpeedAndHighscore() {
  slowDrop = speeds[speed];
  saveSpeed(speed);
  highscore = loadHighscore(speed);
}

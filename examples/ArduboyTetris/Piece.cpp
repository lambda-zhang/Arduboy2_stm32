#include "Piece.h"
#include "Arduino.h"

const unsigned char Piece::possibleShapes[][4][4] = {
  {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  {
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  {
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  {
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  {
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  {
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  },
  {
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  }
};  
const unsigned char Piece::possibleWidths[] = {4, 3, 3, 2, 3, 3, 3};

Piece::Piece() {
  
}

Piece::Piece(int col, int row, int index) {
  this->col = col;
  this->row = row;
  shapeIndex = index;

  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      shape[i][j] = possibleShapes[index][i][j];
    }
  }
  width = possibleWidths[index];
}

void transpose(unsigned char a[4][4], int width) {
  for(int i = 0; i < width - 1; ++i) {
    for(int j = i + 1; j < width; ++j) {
      unsigned char temp = a[i][j];
      a[i][j] = a[j][i];
      a[j][i] = temp;
    }
  }
}

void flipColumns(unsigned char a[4][4], int width) {
  for(int i = 0; i < width; ++i) {
    for(int j = 0; j < width / 2; ++j) {
      unsigned char temp = a[i][j];
      a[i][j] = a[i][width - j - 1];
      a[i][width - j - 1] = temp;
    }
  }
}

void flipRows(unsigned char a[4][4], int width) {
  for(int j = 0; j < width; ++j) {
    for(int i = 0; i < width / 2; ++i) {
      unsigned char temp = a[i][j];
      a[i][j] = a[width - i - 1][j];
      a[width - i - 1][j] = temp;
    }
  }
}

void Piece::resetToTop() {
  this->col=5;
  this->row=0;

  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      shape[i][j] = possibleShapes[shapeIndex][i][j];
    }
  }
}

void Piece::rotateCW() {
  transpose(shape, width);
  flipColumns(shape, width);
}

void Piece::rotateCCW() {
  transpose(shape, width);
  flipRows(shape, width);
}


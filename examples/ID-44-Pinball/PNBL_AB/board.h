#ifndef _BOARD_
#define _BOARD_

#include "vec2.h"

// In this setup, black is considered solid,
// white is empty.

// define normal vectors
vec2 normal_tl(-1, -1);
vec2 normal_t(0, -1);
vec2 normal_tr(1, -1);
vec2 normal_l(-1, 0);
vec2 normal_r(1, 0);
vec2 normal_bl(-1, 1);
vec2 normal_b(0, 1);
vec2 normal_br(1, 1);

void createNormals() {
  normal_tl.convertNormal();
  normal_tr.convertNormal();
  normal_bl.convertNormal();
  normal_br.convertNormal();
}

/*
 * mapGetCollisionPoint
 * Takes:
 *  x (int, non-fixed point)
 *  y (int, non-fixed point)
 *  cmap (progmem const unsigned char pointer, arranged with bytes horizontal)
 * 
 * returns whether point on collision map
 * is white (true) or black (false)
 * returns white (true) for out of bounds
 */
boolean mapGetCollisionPoint(int x, int y, const uint8_t *cmap) {
  byte w = pgm_read_byte(cmap);
  byte h = pgm_read_byte(cmap + 1);
  if (x < 0 || x >= w || y < 0 || y >= h)
    return true;
    
  return (pgm_read_byte(cmap + 2 + (x + y*w)/8) & _BV(x % 8));
}

// Takes absolute postion, not fixed point.
vec2 mapGetNormalVector(int x, int y, const uint8_t *cmap) {
  //pos = pos >> FIXED_POINT;
  vec2 vout(0, 0);

  if (mapGetCollisionPoint(x, y, cmap))
    return vout;

  if (mapGetCollisionPoint(x - 1, y - 1, cmap))
    vout += normal_tl;
  if (mapGetCollisionPoint(x, y - 1, cmap))
    vout += normal_t;
  if (mapGetCollisionPoint(x + 1, y - 1, cmap))
    vout += normal_tr;
  if (mapGetCollisionPoint(x - 1, y, cmap))
    vout += normal_l;
  if (mapGetCollisionPoint(x + 1, y, cmap))
    vout += normal_r;
  if (mapGetCollisionPoint(x - 1, y + 1, cmap))
    vout += normal_bl;
  if (mapGetCollisionPoint(x, y + 1, cmap))
    vout += normal_b;
  if (mapGetCollisionPoint(x + 1, y + 1, cmap))
    vout += normal_br;

  vout.convertNormal();
  return vout;
}

#endif

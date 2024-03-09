#ifndef SNAKE_BITMAPS_H
#define SNAKE_BITMAPS_H
#ifndef STM32F103xB
#include <avr/pgmspace.h>
#else
#include "Arduino.h"
#endif /* STM32F103xB */

extern const unsigned char title[];
extern const unsigned char enemy0[];
extern const unsigned char enemy1[];
extern const unsigned char enemy2[];
extern const unsigned char ship0[];
extern const unsigned char ship1[];
// arduboy_logo.png
// 88x16
extern const unsigned char arduboy_logo[];
#endif
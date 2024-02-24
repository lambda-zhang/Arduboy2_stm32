#ifndef BACKGROUND_H
#define BACKGROUND_H

#ifndef STM32F103xB
#include <avr/pgmspace.h>
#else
#include <Arduino.h>
#endif /* STM32F103xB */

extern const unsigned char background[];

#endif

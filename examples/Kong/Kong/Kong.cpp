#include "src/Game.h"

#include "src/utils/Arduboy2Ext.h"

#ifndef STM32F103xB
#ifdef NO_USB
ARDUBOY_NO_USB 
#endif
#endif /* STM32F103xB */

Game game;

void setup() {
	game.setup();
}

void loop() {
	game.loop();
}

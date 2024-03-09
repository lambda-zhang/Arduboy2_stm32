#include "src/Game.h"

#include "src/utils/Enums.h"
#include "src/utils/Arduboy2Ext.h"

#ifndef STM32F103xB
#ifndef DEBUG
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

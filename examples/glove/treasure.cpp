#include "world.h"


void add_treasure(char x, char y, char type)
{
	for(int i=0; i<numTreasures; i++) {
		if(!treasures[i].active) {
			treasures[i].active = true;
			treasures[i].x = x;
			treasures[i].y = y;
			treasures[i].type = type;
			return;
		}
	}
}
void draw_treasure(Treasure& obj)
{
	if(!obj.active) return;
    
    const unsigned char* drawSpr = (unsigned char*) sprites+SPRITE_TREASURE+(obj.type*8);
	arduboy.drawBitmap(obj.x*8+scrollx, obj.y*8+scrolly, drawSpr, 8, 8, 1);
}

void activate_treasure(Treasure& obj)
{
	char i;
	obj.active = false;
	switch(obj.type) {
		case TREASURE_GOLD: // Awards 10 points
			addScore(10);
			#ifndef STM32F103xB
			arduboy.tunes.tone(TONE_GOLD_GET, 20);
			#else
			sound.tone(TONE_GOLD_GET, 20);
			#endif /* STM32F103xB */
			break;
		case TREASURE_POO: // Kills all baddies on screen
			for(i = 0; i < numBadguys; ++i) {
				badguys[i].active = false;
			}
			flashScreen();
			#ifndef STM32F103xB
			arduboy.tunes.tone(TONE_POO_GET, 20);
			#else
			sound.tone(TONE_POO_GET, 20);
			#endif /* STM32F103xB */
			break;
		case TREASURE_CUP: // Awards 6 points
			addScore(6);
			#ifndef STM32F103xB
			arduboy.tunes.tone(TONE_CUP_GET, 20);
			#else
			sound.tone(TONE_CUP_GET, 20);
			#endif /* STM32F103xB */
			break;
		case TREASURE_LEMON: // Awards 300 health
			rollingHealth += 300;
			#ifndef STM32F103xB
			arduboy.tunes.tone(TONE_LEMON_GET, 20);
			#else
			sound.tone(TONE_LEMON_GET, 20);
			#endif /* STM32F103xB */
			break;
	}
	obj.active = false;
}
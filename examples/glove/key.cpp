#include "world.h"


void add_key(char x, char y, unsigned char target)
{
	for(int i=0; i<numKeys; i++) {
		if(!keys[i].active) {
			keys[i].active = true;
			keys[i].x = x;
			keys[i].y = y;
			keys[i].target = target;
			return;
		}
	}
}
void draw_key(Key & obj)
{
    const unsigned char* drawSpr = (unsigned char*) sprites+SPRITE_KEY;
    
	if(obj.active)
		arduboy.drawBitmap(obj.x*8+scrollx, obj.y*8+scrolly, drawSpr, 8, 8, 1);
}
void activate_key(Key& obj)
{
	if(obj.active)
	{
		walls[obj.target].active = false;
		obj.active = false;
		#ifndef STM32F103xB
		arduboy.tunes.tone(TONE_KEY_ACTIVATE, 20);
		#else
		sound.tone(TONE_KEY_ACTIVATE, 20);
		#endif /* STM32F103xB */
	}
}

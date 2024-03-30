#include "Arduboy2.h"

__weak void setup() {
	printf("setup is NULL\r\n");
}

__weak void loop() {
	printf("loop is NULL\r\n");
}

void arduboy2_app_init_hw(void)
{
	lcd_set_bl(1);
#if defined(SND1_ARDUBOYPLAYTUNE)
	audio_timer1_set(1000); // 1ms
	audio_timer4_set(1000); // 1ms
#elif defined(SND2_ARDUBOYTONES)
	audio_timer1_set(1000); // 1ms
	audio_timer4_set(1000); // 1ms
#elif defined(SND3_ATMLIB)
	audio_timer1_set(31250);
#endif
}

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void arduboy2_app_init(void)
{
	arduboy2_app_init_hw();
	setup();
	while (1)
		loop();
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

void _kill(void){};
void _getpid(void){};
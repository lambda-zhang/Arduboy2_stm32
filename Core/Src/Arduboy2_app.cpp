#include "Arduboy2.h"

EEPROMClass EEPROM;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#undef APP_ARDUBREAKOUT
#undef APP_BEEPDEMO
#undef APP_BUTTONS
#undef APP_FONTDEMO
#undef APP_HELLOWORLD
#undef APP_RGBLED
#undef APP_SETSYSTEMEEPROM
#undef APP_PLAYTUNE
#undef APP_RUND
#undef APP_HALLOWEEND
#undef APP_ARDYNIA
#undef APP_CASTLEBOY
#undef APP_FLAPPYBALL
#undef APP_ARDUBOY3D
#undef APP_SHADOWRUNNER
#undef APP_MYSTICBALLOON
#define APP_ARDUBOYTETRIS

#ifdef APP_ARDUBREAKOUT
extern void ArduBreakout_setup();
extern void ArduBreakout_loop();
#elif defined(APP_BEEPDEMO)
extern void BeepDemo_setup();
extern void BeepDemo_loop();
#elif defined(APP_BUTTONS)
extern void Buttons_setup();
extern void Buttons_loop();
#elif defined(APP_FONTDEMO)
extern void FontDemo_setup();
extern void FontDemo_loop();
#elif defined(APP_HELLOWORLD)
extern void HelloWorld_setup();
extern void HelloWorld_loop();
#elif defined(APP_RGBLED)
extern void RGBled_setup();
extern void RGBled_loop();
#elif defined(APP_SETSYSTEMEEPROM)
extern void SetSystemEEPROM_setup();
extern void SetSystemEEPROM_loop();
#elif defined(APP_PLAYTUNE)
extern void PlayTune_setup();
extern void PlayTune_loop();
#elif defined(APP_RUND)
extern void rund_setup();
extern void rund_loop();
#elif defined(APP_HALLOWEEND)
extern void halloweend_setup();
extern void halloweend_loop();
#elif defined(APP_ARDYNIA)
extern void ardynia_setup();
extern void ardynia_loop();
#elif defined(APP_CASTLEBOY)
extern void CastleBoy_setup();
extern void CastleBoy_loop();
#elif defined(APP_FLAPPYBALL)
extern void FlappyBall_setup();
extern void FlappyBall_loop();
#elif defined(APP_ARDUBOY3D)
extern void Arduboy3D_setup();
extern void Arduboy3D_loop();
#elif defined(APP_SHADOWRUNNER)
extern void ShadowRunner_setup();
extern void ShadowRunner_loop();
#elif defined(APP_MYSTICBALLOON)
extern void Mystic_Balloon_setup();
extern void Mystic_Balloon_loop();
#elif defined(APP_ARDUBOYTETRIS)
extern void ArduboyTetris_setup();
extern void ArduboyTetris_loop();
#else
#error Please select the app
#endif

void arduboy2_app_init(void)
{
	lcd_set_bl(0);

#ifdef APP_ARDUBREAKOUT
	ArduBreakout_setup();
	while (1)
		ArduBreakout_loop();
#elif defined(APP_BEEPDEMO)
	BeepDemo_setup();
	while (1)
		BeepDemo_loop();
#elif defined(APP_BUTTONS)
	Buttons_setup();
	while (1)
		Buttons_loop();
#elif defined(APP_FONTDEMO)
	FontDemo_setup();
	while (1)
		FontDemo_loop();
#elif defined(APP_HELLOWORLD)
	HelloWorld_setup();
	while (1)
		HelloWorld_loop();
#elif defined(APP_RGBLED)
	RGBled_setup();
	while (1)
		RGBled_loop();
#elif defined(APP_SETSYSTEMEEPROM)
	SetSystemEEPROM_setup();
	while (1)
		SetSystemEEPROM_loop();
#elif defined(APP_PLAYTUNE)
	PlayTune_setup();
	while (1)
		PlayTune_loop();
#elif defined(APP_RUND)
	rund_setup();
	while (1)
		rund_loop();
#elif defined(APP_HALLOWEEND)
	halloweend_setup();
	while (1)
		halloweend_loop();
#elif defined(APP_ARDYNIA)
	ardynia_setup();
		while (1)
			ardynia_loop();
#elif defined(APP_CASTLEBOY)
	CastleBoy_setup();
		while (1)
			CastleBoy_loop();
#elif defined(APP_FLAPPYBALL)
	FlappyBall_setup();
		while (1)
			FlappyBall_loop();
#elif defined(APP_ARDUBOY3D)
	Arduboy3D_setup();
	while (1)
		Arduboy3D_loop();
#elif defined(APP_SHADOWRUNNER)
	ShadowRunner_setup();
	while (1)
		ShadowRunner_loop();
#elif defined(APP_MYSTICBALLOON)
	Mystic_Balloon_setup();
	while (1)
		Mystic_Balloon_loop();
#elif defined(APP_ARDUBOYTETRIS)
	ArduboyTetris_setup();
	while (1)
		ArduboyTetris_loop();
#else
#error Please select the app
#endif
}

void _kill(void){};
void _getpid(void){};

#ifdef __cplusplus
}
#endif /* __cplusplus */
#include "racer.h"
#include <EEPROM.h>
#ifdef ESP32
#include <ArduinoOTA.h>
#define EEPROM_NEEDED_BYTES 1024
// block in EEPROM to save high scores
#endif

#define EE_FILE 124

void setup()
{
  //WiFi.mode(WIFI_OFF);

  // i think this is only needed for the esp8266 eeprom emulation
#ifdef ESP32
  EEPROM.begin(EEPROM_NEEDED_BYTES);
#endif

  racerSetup();
#ifdef ESP32
  xTaskCreatePinnedToCore(gameLogicLoop, "g", 4096, nullptr, 1, nullptr, 0);
#endif
}

void loop()
{
#ifdef ESP32
  delay(60000);
#else
  racerLoop();
#endif
}

#ifdef ESP32
void gameLogicLoop(void *)
{
  while(1) {
    racerLoop();
    ArduinoOTA.handle();
  }
}
#endif

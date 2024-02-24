#ifndef MENU_H
#define MENU_H

#include "globals.h"

void stateMenuIntro()
{
  globalCounter++;
  sprites.drawSelfMasked(34, 4, T_arg, 0);
  if (globalCounter > 120) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{

}

void stateMenuRead()
{
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    value = EEPROM.read(address + i);
    Serial.print(address + i);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
  }
  gameState = STATE_MENU_MAIN;
}

void stateMenuDelete()
{

}

void stateMenuReset()
{
  for (int i = 16 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
  gameState = STATE_MENU_MAIN;
}

// put your setup code here, to run once:




#endif

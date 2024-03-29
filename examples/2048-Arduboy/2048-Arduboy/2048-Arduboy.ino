#include <Arduboy2.h>
#include <EEPROM.h>
#include "controller.h"
#include "game.h"
#include "draw.h"
#include "defines.h"
#include "platform.h"
#include "font.h"

#ifdef DEBUG
#include "debug.h"
#endif

Arduboy2Base arduboy;

void setup() {
  // put your setup code here, to run once:
  // initiate arduboy instance
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);

  while (!arduboy.pressed(A_BUTTON)) {
    arduboy.idle();
  }

  #ifdef DEBUG
  Serial.begin(9600);
  i = 0;
  #endif

  // We need the delay before the first button press for a good seed
  arduboy.initRandomSeed();
  InitGame();
}

void loop() {
  // put your main code here, to run repeatedly:
  // pause render until it's time for the next frame
  if (arduboy.nextFrame()) {
    arduboy.pollButtons();
    StepGame();
    arduboy.display();
  }
}

uint8_t Platform::ButtonState() {
  return arduboy.buttonsState();
}
// From Draw.h
// Mapped Arduboy Functions

void Platform::PutPixel(uint8_t x, uint8_t y, uint8_t colour)
{
  arduboy.drawPixel(x, y, colour);
}

void Platform::DrawBitmap(const uint8_t* bitmap,  int16_t x, int16_t y,
                          uint8_t w, uint8_t h, uint8_t colour) {
  arduboy.drawBitmap(x, y, bitmap, w, h, colour);
}

void Platform::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                        uint8_t colour) {
  arduboy.drawLine(x0, y0, x1, y1, colour);
}

void Platform::DrawRect(int16_t x, int16_t y, uint8_t w, uint8_t h,
                        uint8_t colour) {
  arduboy.drawRect(x, y, w, h, colour);
}

void Platform::DrawFilledRect(int16_t x, int16_t y, uint8_t w, uint8_t h,
                              uint8_t colour) {
  arduboy.fillRect(x, y, w, h, colour);
}

void Platform::DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t colour) {
  arduboy.drawCircle(x0, y0, r, colour);
}

void Platform::DrawFilledCircle(int16_t x0, int16_t y0, uint8_t r,
                                uint8_t colour) {
  arduboy.fillCircle(x0, y0, r, colour);
}

void Platform::FillScreen(uint8_t colour) {
  arduboy.fillScreen(colour);
}

void Platform::Clear() {
  arduboy.clear();
}

#ifdef DEBUG
void DebugPrint(uint16_t value) {
  Serial.print(value, HEX);
  Serial.print(":");
  if (++i % 4 == 0) {
    Serial.println(" =");
  }
}

void DebugPrint(char* text) {
  Serial.println(" =");
  Serial.println(text);
  i = 0;
}
#endif

// From Game.h
int16_t Platform::Random(int16_t i0, int16_t i1) {
  return random(i0, i1);
}

uint32_t Platform::Millis() {
  return millis();
}

#define EEP(x) EEPROM[EEPROM_STORAGE_SPACE_START + x]

SavedState Platform::ToEEPROM(const uint8_t *bytes, const uint16_t offset,
                              const uint16_t sz) {
  uint16_t i;
  if (offset < 0) {
    return WrongOffset;
  }
  if (EEPROM_STORAGE_SPACE_START + offset + sz > EEPROM.length()) {
    return TooBig;
  }
  // Write Game to EEPROM

  for (i = 0; i < sz; i++) {
    EEP(i + offset) = bytes[i];
  }
  return Saved;
}

SavedState Platform::FromEEPROM(uint8_t *bytes, const uint16_t offset,
                                const uint16_t sz) {
  // Get Game from EEPROM
  uint16_t i = EEPROM_STORAGE_SPACE_START + offset;
  if (i < 0) {
    return WrongOffset;
  }
  if (i + sz > EEPROM.length()) {
    return TooBig; // Can't read from here
  }

  for (i = 0; i < sz; i++) {
    bytes[i] = EEP(i + offset);
  }
  return Saved;
}

// vim: tabstop=2:softtabstop=2:shiftwidth=2:expandtab

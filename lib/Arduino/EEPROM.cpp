#include <stdlib.h>
#include "EEPROM.h"

#if defined(__has_include) && __has_include(<type_traits>)
#include <type_traits>
#endif

uint8_t *eepromPtr = nullptr;

void EEPROMClass::saveAll()
{
	// diskw(eepromPtr,1024);
}
uint8_t EEPROMClass::read(int idx)
{
	// tracef("eeprom  %d", eepromPtr);
	// tracef("idx  %d", idx);
	uint8_t current_val = *(eepromPtr + idx);
	// tracef("v  %d", current_val);
	// tracef("after fetch");
	return current_val;
}
void EEPROMClass::write(int idx, uint8_t val)
{
	update(idx, val);
}
void EEPROMClass::update(int idx, uint8_t val)
{
	uint8_t old_val = read(idx);
	if (old_val == val)
		return;

	*(eepromPtr + idx) = val;
	saveAll();
}
void EEPROMClass::boot()
{
	eepromPtr = (uint8_t *)malloc(1024);
	// diskr(eepromPtr, 1024);
}

uint16_t EEPROMClass::length()
{
	return 1024;
}

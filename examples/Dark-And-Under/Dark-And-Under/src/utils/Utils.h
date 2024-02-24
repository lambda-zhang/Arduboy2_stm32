#pragma once
#include <stdint.h>

const __FlashStringHelper * FlashString(const char * string) {

	return reinterpret_cast<const __FlashStringHelper *>(string);

}

int16_t absT(int16_t v) {
	return (v < 0) ? -v : v;

}

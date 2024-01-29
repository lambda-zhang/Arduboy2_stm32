#ifndef EEPROM_h
#define EEPROM_h

#include <stdint.h>

#if defined(__has_include) && __has_include(<type_traits>)
#include <type_traits>
#endif

extern uint8_t *eepromPtr;

struct EEPROMClass {
	uint8_t read(int idx);
	void write(int idx, uint8_t val);
	void update(int idx, uint8_t val);
	void boot();
	void saveAll();
	template <typename T> const T &put(int idx, const T &t)
	{
#if defined(__has_include) && __has_include(<type_traits>)
		static_assert(
			std::is_trivially_copyable<T>::value,
			"You can not use this type with EEPROM.get"); // the code below only makes sense if you can "memcpy" T
#endif

		int count = sizeof(T);
		uint8_t *ptr = (uint8_t *)&t;
		for (int i = 0; i < count; i++) {
			*(eepromPtr + idx + i) = *ptr++;
		}
		saveAll();

		return t;
	}
	template <typename T> T &get(int idx, T &t)
	{
#if defined(__has_include) && __has_include(<type_traits>)
		static_assert(
			std::is_trivially_copyable<T>::value,
			"You can not use this type with EEPROM.get"); // the code below only makes sense if you can "memcpy" T
#endif

		int count = sizeof(T);
		uint8_t *ptr = (uint8_t *)&t;
		for (int i = 0; i < count; i++) {
			*ptr++ = *(eepromPtr + idx + i);
		}

		return t;
	}
};

#endif
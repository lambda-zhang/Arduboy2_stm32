#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>

EEPROMClass EEPROM;

volatile uint8_t ubrrh;
volatile uint8_t ubrrl;
volatile uint8_t ucsra;
volatile uint8_t ucsrb;
volatile uint8_t ucsrc;
volatile uint8_t udr;
HardwareSerial Serial(&ubrrh, &ubrrl, &ucsra, &ucsrb, &ucsrc, &udr);

void randomSeed(int a)
{
	srand(a);
}

int random(int max)
{
	return (rand() % (max + 1));
}

int random(int min, int max)
{
	return ((rand() % (max - min + 1)) + min);
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int abs(int n)
{
	return n < 0 ? -n : n;
}

void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void ltoa(long n, char s[], int base)
{
	int i, sign;

	if ((sign = n) < 0) /* record sign */
		n = -n; /* make n positive */
	i = 0;
	do { /* generate digits in reverse order */
		s[i++] = n % base + '0'; /* get next digit */
	} while ((n /= base) > 0); /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void ultoa(uint16_t value, char *str, int base)
{
    /** pokItoa:  convert value n to characters
     * Needed to emulate AVR LibC non-standard functions, this is a very fast version of itoa
     *
     * @param value unsigned integer to be converted
     * @param *str pointer to string where function stores the result as characters
     * @param base (not implemented in this function, base is always 10)
     */

    char *p = str;
    uint8_t v;
    if (value > 499)
    {
        if (value > 799)
        {
            if (value > 999)
            {
                // Treated as a special case as there
                // are only 24 values above 999
                *p++ = '1';
                *p++ = '0';
                uint8_t v = value - 1000;

                if      (v > 19) { *p++ = '2'; v -= 20; }
                else if (v >  9) { *p++ = '1'; v -= 10; }
                else             { *p++ = '0'; }

                *p++ = v + '0';
                *p = 0;
                return;
            }

            if (value > 899) { *p++ = '9'; v = value - 900; }
            else             { *p++ = '8'; v = value - 800; }
        }
        else
        {
            if      (value > 699) { *p++ = '7'; v = value - 700; }
            else if (value > 599) { *p++ = '6'; v = value - 600; }
            else                  { *p++ = '5'; v = value - 500; }
        }
    }
    else
    {
        if (value > 299)
        {
            if (value > 399) { *p++ = '4'; v = value - 400; }
            else             { *p++ = '3'; v = value - 300; }
        }
        else
        {
            if      (value > 199) { *p++ = '2'; v = value - 200; }
            else if (value >  99) { *p++ = '1'; v = value - 100; }
            else                  {             v = value; }
        }
    }

    if (v > 49)
    {
        if (v > 69)
        {
            if      (v > 89) { *p++ = '9'; v -= 90; }
            else if (v > 79) { *p++ = '8'; v -= 80; }
            else             { *p++ = '7'; v -= 70; }
        }
        else
        {
            if (v > 59) { *p++ = '6'; v -= 60; }
            else        { *p++ = '5'; v -= 50; }
        }
    }
    else
    {
        if (v > 19)
        {
            if      (v > 39) { *p++ = '4'; v -= 40; }
            else if (v > 29) { *p++ = '3'; v -= 30; }
            else             { *p++ = '2'; v -= 20; }
        }
        else
        {
            if      (v >  9)   { *p++ = '1'; v -= 10; }
            else if (p != str) { *p++ = '0'; }
        }
    }

    *p++ = v + '0';
    *p = 0;
}

char *dtostrf(double val, signed char width, unsigned char prec, char *sout) {
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec);
  sprintf(sout, fmt, val);
  return sout;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    return;
}

void eeprom_busy_wait() {}
uint8_t eeprom_read_byte (const uint8_t *__p)
{
    uint8_t dta;
    EEPROM.get((int)__p, dta);
    return (dta);
}
uint16_t eeprom_read_word (const uint16_t *__p)
{
    uint16_t dta;
    EEPROM.get((int)__p, dta);
    return (dta);
}
uint32_t eeprom_read_dword (const uint32_t *__p)
{
    uint32_t dta;
    EEPROM.get((int)__p, dta);
    return (dta);
}
void eeprom_read_block (void *__dst, const void *__src, size_t __n)
{
    uint8_t dta;
    for (uint8_t i=0; i<__n; i++) {
        EEPROM.get((int)__src+i, dta);
        ((uint8_t*)__dst)[i]=dta;
    };
}
void eeprom_write_byte (uint8_t *__p, uint8_t __value)
{
    EEPROM.put((int)__p, __value);
}
void eeprom_write_word (uint16_t *__p, uint16_t __value)
{
    EEPROM.put((int)__p, __value);
}
void eeprom_write_dword(uint16_t* eepAddr, uint32_t val)
{
    EEPROM.put((int)eepAddr, val);
}
void eeprom_write_block(uint8_t *p, uint16_t* eepAddr, uint8_t n)
{
    for (uint8_t i=0; i<n; i++){
        EEPROM.put((int)eepAddr+i, p[i]);
    }
}
void eeprom_write_dword (uint32_t *__p, uint32_t __value)
{
    eeprom_write_word((uint16_t *)__p, __value);
}
void eeprom_update_block (const void *__src, void *__dst, size_t __n)
{
	uint8_t* p = (uint8_t*)__dst;
	const uint8_t *src = (const uint8_t *)__src;
	while (__n--) {
		eeprom_write_byte(p++, *src++);
	}
}
void eeprom_update_byte (uint8_t *__p, uint8_t __value)
{
	eeprom_write_byte(__p, __value);
}
void eeprom_update_word (uint16_t *__p, uint16_t __value)
{
    eeprom_write_dword(__p, __value);
}
void eeprom_write_float(float *addr, float value)
{
	union {float f; uint32_t u32;} u;
	u.f = value;
	eeprom_write_dword((uint32_t *)addr, u.u32);
}
float eeprom_read_float(const float *addr)
{
	union {float f; uint32_t u32;} u;
	u.u32 = eeprom_read_dword((const uint32_t *)addr);
	return u.f;
}
void eeprom_update_float(float *addr, float value)
{
	union {float f; uint32_t u32;} u;
	u.f = value;
	eeprom_write_dword((uint32_t *)addr, u.u32);
}
void eeprom_update_dword(uint32_t *addr, uint32_t value)
{
	eeprom_write_dword(addr, value);
}
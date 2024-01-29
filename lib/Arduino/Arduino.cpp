#include "Arduino.h"
#include <stdlib.h>
#include <stdio.h>

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
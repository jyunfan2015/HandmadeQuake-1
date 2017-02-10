/*
	Quake Standard Library source file
*/
#include "quakedef.h"

// String copy
void Q_strcpy(uint8 *dest, uint8 *src)
{
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = 0; // End of line
}

// String copy with counter
void Q_strncpy(uint8 *dest, uint8 *src, int32 count)
{
	if (count < 0)
		return;

	while (*src && count)
	{
		*dest++ = *src++;
		--count;
	}

	while (count)
	{
		*dest++ = 0;
		--count;
	}
}

// String length
int32 Q_strlen(uint8 *str)
{
	int32 count = 0;

	while (str[count])
		++count;

	return count;
}

// String compare
int32 Q_strcmp(uint8 *s1, uint8 *s2)
{
	while (*s1 == *s2) // While they're equal
	{
		if (!*s1) // If they're equal, they are both pointing to 0 so we only check the first one.
			return 0;
		++s1;
		++s2;
	}

	return ((*s1 < *s2) ? -1 : 1); // If the first string is smaller than the second, we return -1, otherwise 1
}

// String convertion to an integer value
int32 Q_atoi(uint8 *str)
{
	int32 sign = 1;
	int32 val = 0;
	uint8 c;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	// hexadecimal
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
	{
		str += 2; // Pass the 0x char
		while (1)
		{
			c = *str;
			str++;
			if (c >= '0' && c <= '9')
				val = val * 16 + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = val * 16 + c - 'a' + 10; // We add 10 because the letter A/a in Hex is 10 in Dec
			else if (c >= 'A' && c <= 'F')
				val = val * 16 + c - 'A' + 10;
			else
				return val*sign;
		}
	}

	// decimal
	while (1)
	{
		c = *str;
		str++;
		if (c < '0' || c > '9') // If it's not a number
			return sign * val;
		val = val * 10 + c - '0';
	}
}
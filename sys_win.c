#include <stdint.h> // Use the standards types of C
#include <windows.h>

typedef uint8_t uint8; // Char, there are unsigned
typedef int32_t int32; // Integer
typedef uint32_t uint32;


#define MAX_NUM_ARGVS 3 // Size of the array storing the arguments

int32 argc = 1; // Number of arguments given at the program
uint8 *largv[MAX_NUM_ARGVS+1]; // Array storing the arguments

/*
	The pointer lpCmdLine is used to check the char into the array, like a normal counter.
	But it's a pointer and incrementing a pointer is tricky, so be careful.
*/

// String compare
int32 Q_strcmp(uint8 *s1, uint8 *s2) // Need to be reviewed
{
	while (*s1 == *s2)
	{
		if (!*s1)
			return 0;
		++s1;
		++s2;
	}

	return ((*s1 < *s2) ? -1 : 1);
}

// String convertion to an integer value
// decimal or hexadecimal
// negative and positive
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
				val = val * 16 + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = val * 16 + c - 'A' + 10;
			else
				return val*sign;
		}
	}

	// decimal
	while (1) // Need to be reviewed
	{
		c = *str;
		str++;
		if (c < '0' || c > '9')
			return sign * val;
		val = val * 10 + c - '0';
	}
}

int32 COM_CheckParm(uint8 *parm) // Check the parameters of the command line. COMMON Library
{
	for (int32 i = 1; i < argc; i++)
	{
		if (!Q_strcmp(parm, largv[i]))
			return i;
	}

	return 0;
}

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow)
{
	largv[0] = "";

	// If the lpCmdLine contains a correct ASCII value (or not a 0) and if the number of arguments is correct
	while (*lpCmdLine && (argc < MAX_NUM_ARGVS+1)) 
	{
		// If the char are not printable, increment the pointer
		while (*lpCmdLine && ((*lpCmdLine <= 32) || (*lpCmdLine > 126)))
			lpCmdLine++;

		// If a value exists
		if (*lpCmdLine) 
		{
			// Setting a point in the largv of the beginning of the first command
			largv[argc] = lpCmdLine; // Setting the adress of lpCmdLine in largv at argc (1)
			argc++; // Incrementing the number of arguments


			// While the command line contains a printable value, increment the pointer
			while (*lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126)))
				lpCmdLine++;

			// Reset the value of lpCmdLine to 0 (end of string value) and increment the pointer
			if (*lpCmdLine)
			{
				*lpCmdLine = 0;
				lpCmdLine++;
			}
		}
	}

	int32 test = COM_CheckParm("-setalpha"); // return the index of the array with the value "-setalpha"
	int32 value = Q_atoi(largv[test+1]); // atoi get the pointer of the largv[i], a 3 bytes string, and cast the 2 first bytes into an integer

	return 0;
}
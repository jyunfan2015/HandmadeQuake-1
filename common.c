/*
	COMMON Source file
*/

#include "quakedef.h"

int32 com_argc = 1; // Number of arguments given at the program
uint8 *com_argv[MAX_NUM_ARGVS + 1]; // Array storing the arguments

void COM_ParseCmdLine(uint8 *lpCmdLine)
{
	/*
	The pointer lpCmdLine is used to check the char into the array, like a normal counter.
	But it's a pointer and incrementing a pointer is tricky, so be careful.
	*/

	com_argv[0] = "";

	// If the lpCmdLine contains a correct ASCII value (or not a 0) and if the number of arguments is correct
	while (*lpCmdLine && (com_argc < MAX_NUM_ARGVS + 1))
	{
		// If the char are not printable, increment the pointer
		while (*lpCmdLine && ((*lpCmdLine <= 32) || (*lpCmdLine > 126)))
			lpCmdLine++;

		// If a value exists
		if (*lpCmdLine)
		{
			// Setting a point in the largv of the beginning of the first command
			com_argv[com_argc] = lpCmdLine; // Setting the adress of lpCmdLine in largv at argc (1)
			com_argc++; // Incrementing the number of arguments


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
}

// Check the parameters of the command line. COMMON Library
int32 COM_CheckParm(uint8 *parm)
{
	for (int32 i = 1; i < com_argc; i++)
	{
		if (!Q_strcmp(parm, com_argv[i]))
			return i;
	}

	return 0;
}
/*
	COMMON Header file
*/

#pragma once

#define MAX_NUM_ARGVS 50 // Size of the array storing the arguments

extern int32 com_argc;
extern uint8 *com_argv[MAX_NUM_ARGVS + 1];

/*
	Functions
*/

void COM_ParseCmdLine(uint8 *lpCmdLine);
int32 COM_CheckParm(uint8 *parm);

/********************************************************************************
* Name:			debug.h
* Description:  Debugging support.
* DLL Location:	c:\winnt\system32\iisutils\debug.h
*********************************************************************************/

#ifndef _IISDEBUG
#define _IISDEBUG

/* Need this define to enable MB_SERVICE_NOTIFICATION??? */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define WIN32_LEAN_AN_MEAN

#include <windows.h>

/* For sprintf */
#include <stdio.h>

/* For MessageBox() */
#include <winuser.h>

#include "iisutils.h"

/********************************************************************************/
#define DEST lpBuff
#define DEBUG_TYPE DBMN_DEBUG

/* Debug Macro */
#define Debug(x) { \
	CHAR lpBuff[MAX_BUFF_SIZE]; \
	sprintf x; \
	DebugOutput(DEBUG_TYPE, lpBuff); \
}

/* DLL Debugging Mechanisms */
enum DebugType {MESSAGE_DEBUG, FILE_DEBUG, DBMN_DEBUG};

extern VOID		DebugOutput(enum DebugType eDebugType, LPSTR lpDebugMessage);

#endif

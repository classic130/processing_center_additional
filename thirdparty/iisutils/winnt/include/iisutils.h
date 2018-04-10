/********************************************************************************
* Name:			iisutils.h
* Description:  a static library of support functions for writing ISA DLL's.
* DLL Location:	c:\winnt\system32\iisutils\iisutils.h
*********************************************************************************/

#ifndef IISUTILS
#define IISUTILS

#define WIN32_LEAN_AN_MEAN
#include <windows.h>

/* For strstr() et al */
#include <string.h>

#include "debug.h"

/********************************************************************************/

#define MAX_BUFF_SIZE 4096

extern VOID		FileError_Write(LPSTR lpErrMsg, LPSTR lpMsgBuf);


#endif

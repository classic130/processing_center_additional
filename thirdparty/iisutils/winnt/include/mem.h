/********************************************************************************
* Name:			mem.h
* Description:  Memory allocation support.
* DLL Location:	c:\winnt\system32\iisutils\mem.h
*********************************************************************************/

#ifndef _IISMEM
#define _IISMEM

#define WIN32_LEAN_AN_MEAN
#include <windows.h>

#include "iisutils.h"
#include "debug.h"

/********************************************************************************/

/* Memory Allocation */
extern LPVOID	Mem_Alloc(DWORD dwSize);
extern VOID		Mem_Free(LPVOID lpChunk);

/* Make sure you #define MEM_DEBUG to enable memory accounting */
extern VOID		Mem_DumpInUse(void);

/********************************************************************************/


#endif

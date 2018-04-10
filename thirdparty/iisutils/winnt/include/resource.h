/********************************************************************************
* Name:			resource.h
* Description:  
* DLL Location:	c:\winnt\system32\iisutils\resource.h
*********************************************************************************/

#ifndef _RESOURCE
#define _RESOURCE

#define WIN32_LEAN_AN_MEAN
#include <windows.h>
#include "iisutils.h"
#include "debug.h"
#include "mem.h"

/********************************************************************************/

extern BOOL ResourceList_Find(LPSTR lpszResourceList, LPSTR lpszURL);
extern LPSTR ResourceList_Init(LPSTR lpszAppName);
extern VOID ResourceList_Cleanup(LPSTR lpszResourceList);
extern VOID ResourceList_Dump(LPSTR lpszResourceList);

/********************************************************************************/

#endif
/* SCCSID: inc/cssmport.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.23 8/12/98 19:10:21 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * Copyright (c) 1995, 1996, 1997 Intel Corporation. All rights reserved.
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _CSSMPORT_H
#define _CSSMPORT_H    

#if defined (WIN32)
#include <process.h>
#include <windows.h>
#include <limits.h>
#elif defined (AIX)
#include <unistd.h>
#endif

#if defined (AIX)
#include <pthread.h>  /* Must always be the first include */
#endif 

#include "cssm.h"
#include <stdio.h>

#if defined(UNIX)
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#endif

#if defined(AIX)

#include <filehdr.h>
#include <pwd.h>
#include <sys/shm.h>
#include <odmi.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <sys/select.h>
#include <signal.h>

#define WINAPI

typedef int BOOL;
typedef void * HANDLE;
typedef uint32 DWORD;
typedef void* LPVOID; 
typedef char* LPCTSTR, LPSTR;

#define DLL_PROCESS_ATTACH 1    
#define DLL_THREAD_ATTACH  2    
#define DLL_THREAD_DETACH  3    
#define DLL_PROCESS_DETACH 0    

#define max(a, b)  (((a) > (b)) ? (a) : (b))

#define CSSM_POLL_INT                   20 /* polling interval in ms */

/* ftok() file prefix */
#define CSSM_TMP_FILE_PREFIX  "__cssm"

#endif

#if defined (UNIX)
#define _mkdir(path) mkdir(path, S_IWUSR | S_IRUSR | S_IXUSR)
#endif

#if defined (AIX)
#define cssm_stat stat
#endif

#if defined (WIN32)
#include <sys\types.h>
#include <sys\stat.h>
#define cssm_stat _stat
#endif

#if defined (WIN32)
#define DllImport       __declspec( dllimport )
#define DllExport       __declspec( dllexport )
#else
#define DllImport
#define DllExport
#define __declspec( attr )
#define __stdcall
#define CSSM_THREAD
#endif

typedef void (*NULL_FUNC_PTR) ();
static CSSM_GUID port_guid = 
{ 0xa32fbd82, 0xfbcc, 0x11cf, { 0x81, 0x72, 0x0, 0xaa, 0x0, 0xb1, 0x99, 0xdd } };

#if defined (AIX)
#define CSSM_ODMDIR "CSSM_ODMDIR"
/* ODM search criteria */
#define CSSM_ODM_MAX_RET 512
#define CSSM_GET_CRIT   "section='%s' AND name='%s' AND local=%d" 
#define CSSM_RECURS_DEL_CRIT1 "section LIKE '%s\\*' AND local=%d" 
#define CSSM_RECURS_DEL_CRIT2 "section='%s' AND local=%d"
#define CSSM_GET_VALUE_LIST_CRIT "section='%s' AND local=%d"
#define CSSM_GET_SECTION_LIST_CRIT "section='%s' AND local=%d"
#define CSSM_GET_MAP_CRIT "section='%s' AND subsection='%s' AND local=%d"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Porting Library Functions */

/* GetProcess ID and GetThreadID macros */
#if defined (WIN32)
#define CSSM_GETPROCESSID (uint32)_getpid()
#define CSSM_GETTHREADID (uint32)GetCurrentThreadId()
#elif defined (AIX)
#define CSSM_GETPROCESSID (uint32)getpid()
#define CSSM_GETTHREADID (uint32)pthread_self()
#endif

/* Initialization and termination routines */
CSSM_RETURN CSSMAPI cssm_port_init(void);
CSSM_RETURN CSSMAPI cssm_port_terminate(void);

/* Registry Routines */
#if defined(WIN32)
typedef HKEY
#else
typedef char *
#endif
CSSM_HKEY, *CSSM_HKEY_PTR;

#if !defined (WIN32)
/* Taken from Winnt.h */

#define REG_NONE                    ( 0 )   // No value type
#define REG_SZ                      ( 1 )   // Unicode nul terminated string
#define REG_EXPAND_SZ               ( 2 )   // Unicode nul terminated string
#define REG_BINARY                  ( 3 )   // Free form binary
#define REG_DWORD                   ( 4 )   // 32-bit number
#define REG_DWORD_LITTLE_ENDIAN     ( 4 )   // 32-bit number (same as REG_DWORD)
#define REG_DWORD_BIG_ENDIAN        ( 5 )   // 32-bit number
#define REG_LINK                    ( 6 )   // Symbolic Link (unicode)
#define REG_MULTI_SZ                ( 7 )   // Multiple Unicode strings
#define REG_RESOURCE_LIST           ( 8 )   // Resource list in the resource map
#define REG_FULL_RESOURCE_DESCRIPTOR ( 9 )  // Resource list in the hardware desicription
#define REG_RESOURCE_REQUIREMENTS_LIST ( 10 )
#define HKEY_CURRENT_USER            (CSSM_HKEY) 0x80000001
#define HKEY_LOCAL_MACHINE           (CSSM_HKEY) 0x80000002
#endif

#define CSSM_CONFIG_STRING          REG_SZ
#define CSSM_CONFIG_BINARY          REG_BINARY
#define CSSM_CONFIG_PERSONAL                1
#define CSSM_CONFIG_GLOBAL          0
#define CSSM_VALUE_BINARY           0
#define CSSM_VALUE_STRING           1

typedef char **CSSM_REG_LIST, ***CSSM_REG_LIST_PTR;

CSSM_RETURN CSSMAPI cssm_SetValue (char *Section, char *Name,
                                   void * Value, sint32  ValueLength, 
                                   sint32  ValueType, sint32  PersonalPref);
CSSM_RETURN CSSMAPI cssm_GetValue (char *Section, char *Name,
                                   void * Value, sint32 *ValueLength,
                                   sint32 *ValueType, sint32  PersonalPref);
CSSM_RETURN CSSMAPI cssm_DeleteSection (char *Section, sint32  PersonalPref);
CSSM_RETURN CSSMAPI cssm_GetValueList (char *section, CSSM_REG_LIST_PTR list,
                                       sint32  PersonalPref);
CSSM_RETURN CSSMAPI cssm_GetValueCount (char *section, sint32 * count, 
                                        sint32  PersonalPref);
CSSM_RETURN CSSMAPI cssm_GetSectionCount (char *section, sint32 * count, 
                                          sint32  PersonalPref);
CSSM_RETURN CSSMAPI cssm_GetSectionList (char *section, CSSM_REG_LIST_PTR list,
                                         sint32  PersonalPref);


/* Memory Allocation Routines */

void * cssm_malloc (uint32 size, void* allocRef);
void * cssm_calloc (uint32 num_elem, uint32 num_bytes, void* allocRef);
void cssm_free (void * mem_ptr, void* allocRef);
void * cssm_realloc (void * old_ptr, uint32 num_bytes, void* allocRef);
void * cssm_memset (void * ptr, sint32  value, uint32 num_bytes);
void * cssm_memcpy (void * dest_ptr, void * src_ptr, uint32 num_bytes);
void * cssm_memmove (void * dest_ptr, void * src_ptr, uint32 num_bytes);
sint32 cssm_memcmp (void * ptr1, void * ptr2, uint32 count);

CSSM_BOOL CSSMAPI cssm_IsBadStrPtr (const char *str, uint32  length);
CSSM_BOOL CSSMAPI cssm_IsBadCodePtr (CSSM_CALLBACK  code_ptr);
CSSM_BOOL CSSMAPI cssm_IsBadReadPtr (const void * ptr, uint32 length);
CSSM_BOOL CSSMAPI cssm_IsBadWritePtr (void * ptr, uint32 length);
char * CSSMAPI cssm_strlwr (char *str);
CSSM_RETURN generateRandomNumber (uint32	*randomValue);

/* File I/O Routines */

CSSM_RETURN CSSMAPI cssm_fwrite (void * buffer, uint32 size, uint32 num, 
                                 FILE * stream);
CSSM_RETURN CSSMAPI cssm_fread (void * buffer, uint32 size, uint32 num, 
                                FILE * stream);
sint32 CSSMAPI cssm_GetLength (FILE * stream) ;

#ifdef UNIX 
#define _open  open
#define _close close
#define _read  read
#define _write write
#define remove unlink 
sint32 _filelength(int fd);
#endif

/* Sync Routines */

#if defined (AIX)
typedef pthread_mutex_t CRITICAL_SECTION;
#define EnterCriticalSection pthread_mutex_lock
#define LeaveCriticalSection pthread_mutex_unlock
#define InitializeCriticalSection(cs) pthread_mutex_init((cs),NULL) 
/* Time-out in ms. Approx. 18 days */ 
#define INFINITE 0x5FFFFFFF 
#endif

#define CSSM_INFINITE_WAIT INFINITE
#define CSSM_ZERO_WAIT 0

typedef enum cssm_mutex {
    CSSM_MUTEX_LOCKED, 
    CSSM_MUTEX_BUSY, 
    CSSM_MUTEX_UNLOCKED, 
    CSSM_MUTEX_ERROR
} CSSM_MUTEX;

void * CSSMAPI cssm_CreateGlobalMutex (char *name);
void * CSSMAPI cssm_CreateMutex (char *name);
void * CSSMAPI cssm_CreateMutexHelper (char *name, CSSM_BOOL local);
CSSM_MUTEX CSSMAPI cssm_LockMutex (HANDLE mutex, sint32 timeout);
CSSM_MUTEX CSSMAPI cssm_TrylockMutex (HANDLE mutex);
CSSM_MUTEX CSSMAPI cssm_UnlockMutex (HANDLE mutex); 
CSSM_RETURN CSSMAPI cssm_CloseMutex (HANDLE mutex);

/* Thread related routines */
uint32 CSSMAPI cssm_GetThreadId();

/* Misc */
char * CSSMAPI cssm_GetIdentificationInfo(char *info, uint32  size);
char * CSSMAPI cssm_GetUserName (char *userName, uint32 size);
char * CSSMAPI cssm_getcwd (char *dir, uint32 size);
char * CSSMAPI cssm_getenv (char *env_var);
uint32 CSSMAPI cssm_GetTime();

#if defined (AIX)
#define IsBadReadPtr(lp,ucb) FALSE
#define IsBadCodePtr(lpfn) FALSE
#define stricmp strcasecmp
#endif

/* Dynamic Loading of Libraries */

#if defined(WIN32)
typedef HINSTANCE
#else
typedef void *
#endif
CSSM_LIB_HANDLE, *CSSM_LIB_HANDLE_PTR;

#if defined(WIN32)
typedef HMODULE
#else
typedef void *
#endif
CSSM_MODULE, *CSSM_MODULE_PTR;

#if defined(WIN32)
typedef FARPROC
#else
typedef void *
#endif
CSSM_PROC_ADDR, *CSSM_PROC_ADDR_PTR;

#if defined(WIN32)
typedef HINSTANCE 
#else
typedef void * 
#endif
CSSM_HINSTANCE, *CSSM_HINSTANCE_PTR;

CSSM_RETURN CSSMAPI cssm_FreeLibrary (CSSM_LIB_HANDLE handle);
CSSM_LIB_HANDLE CSSMAPI cssm_LoadLibrary (char *pLibraryPathName);
CSSM_PROC_ADDR CSSMAPI cssm_GetProcAddress (CSSM_MODULE handle, 
                                            char *func_name);  
CSSM_MODULE CSSMAPI cssm_GetModuleHandle (char *module_name);
CSSM_RETURN CSSMAPI cssm_GetModuleFileName (CSSM_MODULE module, char *filename,
                                            sint32 buf_length);


/* Shared Memory Functions */

#if defined(WIN32)
#define CSSM_INVALID_FILE_HANDLE NULL 
typedef HANDLE                      
#else
#define CSSM_INVALID_FILE_HANDLE -1 
typedef int 
#endif
CSSM_SHARED_FILE;

#if defined(WIN32)

#define CSSM_CREATE_READWRITE       PAGE_READWRITE
#define CSSM_CREATE_READ            PAGE_READONLY
#define CSSM_MAP_READWRITE          FILE_MAP_ALL_ACCESS
#define CSSM_MAP_READ               FILE_MAP_READ

#elif defined(AIX)

#define CSSM_CREATE_READWRITE       00000002    
#define CSSM_CREATE_READ            00000000    
#define CSSM_MAP_READWRITE          0 
#define CSSM_MAP_READ               SHM_RDONLY      
#define _O_RDONLY		    O_RDONLY
#define _O_RDWR                     O_RDWR
#define _O_BINARY                   O_BINARY
#define _S_IREAD                    S_IREAD

#endif

CSSM_SHARED_FILE CSSMAPI cssm_CreateMemoryFile (char *name, sint32 perms);
CSSM_SHARED_FILE CSSMAPI cssm_OpenMemoryFile (char *name, sint32 perms);
void * CSSMAPI cssm_MapMemoryFile (CSSM_SHARED_FILE handle, sint32 perms);
CSSM_RETURN CSSMAPI cssm_UnmapMemoryFile (void *file_addr);
CSSM_RETURN CSSMAPI cssm_FlushMemoryFile (void *file_addr);
CSSM_RETURN CSSMAPI cssm_CloseMemoryFile (CSSM_SHARED_FILE handle);

/* error functions */
CSSM_RETURN CSSMAPI cssm_InitError(void);
CSSM_RETURN CSSMAPI cssm_DestroyError(void);
CSSM_ERROR_PTR  CSSMAPI cssm_GetError(void);
CSSM_RETURN CSSMAPI cssm_SetError(CSSM_GUID_PTR guid, uint32 error);
void CSSMAPI cssm_ClearError(void);

/* Misc. functions */
#if defined (AIX) 
#define _timezone timezone
#define itoa(value,string,radix) sprintf ((string),"%d",(value))
#define _itoa(value,string,radix) \
                                  sprintf ((string),"%d",(value))
#define MessageBox(hWnd,lpText,lpCaption,uType) \
    printf ("\n%s: %s\n",lpCaption,lpText)

uint32 GetEnvironmentVariable (char *lpName, char *lpBuffer, uint32 nSize);

#endif


#ifdef __cplusplus
}
#endif

/* Do not edit the following string. It should be expanded at check-in by version control. */
static const char sccs_id_INC_CSSMPORT_H[] = { "@(#) $Header: /cvs/thirdparty/sccstk/inc/Attic/cssmport.h,v 1.1.2.1 2001/11/08 04:09:24 jhuang Exp $" };

#endif

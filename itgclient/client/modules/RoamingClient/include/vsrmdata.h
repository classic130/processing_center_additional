/*
 * $Revision: 1.2.404.1 $
 * $Header: /cvs/itgclient/client/modules/RoamingClient/include/vsrmdata.h,v 1.2.404.1 2003/06/09 23:41:30 sgoginen Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 2000. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

// vsrmdata.h : Defines common data strutures
//

#ifndef VSRMUTIL_H
#define VSRMUTIL_H

#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <tchar.h>
#include <windows.h>
#else
#include <wchar.h>
#include <string.h>
#endif

#include "vsrmerr.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
    #if defined(VSRMUTIL_EXPORTS)
        #define VSRMUTIL_API __declspec(dllexport)
    #elif defined(VSRMUTIL_IMPORTS)
        #define VSRMUTIL_API __declspec(dllimport)
    #else
        #define VSRMUTIL_API    
    #endif
#else
    #define VSRMUTIL_API
#endif

typedef unsigned int VSRM_SESSION_HANDLE;

#ifdef WIN32
typedef WCHAR         VSRM_CHAR;
#else
typedef wchar_t       VSRM_CHAR;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
#endif

/* name value pair data type */
#ifndef _VSRM_CHAR_NVP
#define _VSRM_CHAR_NVP
typedef struct {
    char      *pszName ;
    VSRM_CHAR *pszValue ;
} VSRM_CHAR_NVP;
#endif

#define QUESTIONSTRING "vsrm_question"
#define ANSWERSTRING   "vsrm_answer"
#define FNAMESTRING    "vsrm_firstname"
#define LNAMESTRING    "vsrm_lastname"
#define EMAILSTRING    "vsrm_emailaddress"


#ifndef NULL_PTR
#define NULL_PTR 0
#endif

#define LOCATION __FILE__, __LINE__

typedef enum {
    VSRM_LOG_NONE,  // No logging at all
    VSRM_LOG_ERROR,	// Logs serious errors only
    VSRM_LOG_INFO,  // Logs information messages
    VSRM_LOG_DEBUG	// Logs debug info (max amount of logging)    
} VSRM_LOG_LEVEL;

typedef enum {
    VSRM_FALSE = 0,
    VSRM_TRUE = 1
} VSRM_BOOL;

typedef unsigned int VSRM_USERNAME_STATUS;
#define VSRM_USERNAME_STATUS_UNKNOWN        0
#define VSRM_USERNAME_STATUS_NEW            1
#define VSRM_USERNAME_STATUS_RECOVERABLE    2
#define VSRM_USERNAME_STATUS_PARTIALLY_USED 3

#define SYM_IV_SIZE             8
#define SYM_KEY_SIZE            20
#define SHA_HASH_SIZE           20

typedef struct _vsrm_item {
    unsigned char *data;
    unsigned int   len;
} VSRM_ITEM;

typedef struct {
    int valueType;
#define PASSWORD_VALUE_TYPE_UNICODE 0x00
#define PASSWORD_VALUE_TYPE_HASHED  0x01
    union {
        VSRM_CHAR  *pszValue;
        VSRM_ITEM  *hashedValue; 
    };
} VSRM_PASSWORD;

/* =========================*/
/* Common utility functions */
/* =========================*/

// memory management functions 

VSRMUTIL_API void *VSRM_Malloc(size_t size);
VSRMUTIL_API void *VSRM_Calloc(size_t num, size_t size);
VSRMUTIL_API void *VSRM_Realloc(void *memblock, size_t size);
VSRMUTIL_API void VSRM_Free(void *memblock);
VSRMUTIL_API char *VSRM_Strdup(const char* s);
VSRMUTIL_API void *VSRM_Memcpy(void *dest, const void *src, size_t count);
VSRMUTIL_API int  VSRM_Strcmp(const char *string1, const char *string2);
VSRMUTIL_API char *VSRM_Strcpy(char *strDestination, const char *strSource);
VSRMUTIL_API VSRM_CHAR *VSRM_Wcsdup(const wchar_t *strSource);

// data strcuture management functions 

/* free content of dataItem plus itself */
VSRMUTIL_API void VSRMUTIL_FreeItem(VSRM_ITEM* dataItem);

/* zero-cross the content first and their free its content but not pointer itself */
VSRMUTIL_API void VSRMUTIL_DestroyItem(VSRM_ITEM* dataItem);

VSRMUTIL_API 
VSRM_STATUS VSRMUTIL_CreateItem(
    VSRM_ITEM            **result,
    const unsigned char  *data,
    unsigned int         len);

#ifdef __cplusplus
}
#endif

#endif // VSRMUTIL_H

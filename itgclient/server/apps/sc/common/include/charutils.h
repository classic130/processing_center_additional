#ifndef __MAIN_HXX
#define __MAIN_HXX

//
// System Includes
//

#define UNICODE
#define _UNICODE
#define INC_OLE2
#include <windows.h>

//
// CRunTime Includes
//

#include <stdlib.h>
#include <limits.h>
#include <io.h>
#include <stdio.h>
#include <stddef.h>
#include <time.h>

#include <Winbase.h>
#include "vsstring.h"

#define NULL_TERMINATED 0

//
// *********  Useful macros
//

#define		MAXPOSTVARS			3
#define		MAXGETVARS			4
#define		VARNAMESIZE			256



#define BAIL_ON_NULL(p)       \
        if (!(p)) {           \
                goto error;   \
        }

#define BAIL_ON_FAILURE(hr)   \
        if (FAILED(hr)) {     \
                goto error;   \
        }


#define FREE_INTERFACE(pInterface) \
        if (pInterface) {          \
            pInterface->Release(); \
            pInterface=NULL;       \
        }

#define FREE_UNICODE_STRING(pMem)     \
        if (pMem) {    \
            FreeUnicodeString(pMem); \
            pMem = NULL;     \
        }


#define		CHALLENGE_LEN	20
#define		NAME_LEN		20
#define		SESSIONID_LEN	8
#define		TIMEOUT			15
#define		DELETE_TIME		10
#define PRECANNED_HEADER "The following data is for authentication purpose only."

int
AnsiToUnicodeString(
    LPSTR pAnsi,
    LPWSTR pUnicode,
    DWORD StringLength
    );


int
UnicodeToAnsiString(
    LPWSTR pUnicode,
    LPSTR pAnsi,
    DWORD StringLength
    );


LPWSTR
AllocateUnicodeString(
    LPSTR  pAnsiString
    );

void
FreeUnicodeString(
    LPWSTR  pUnicodeString
    );




LPWSTR
RemoveWhiteSpaces(
    LPWSTR pszText
    );




BSTR _MultiToWideString(LPSTR szInputString) ;
LPSTR _WideToMultiString(BSTR szwcInputString) ;


int Hascii2Bin(PCHAR hasc,
			   PCHAR *OutBuf,
			   int *OutLen);

void getRandomString(BYTE *pbData,
					 int len);

void Base64Encode(
				   PCHAR pInput, 
				   DWORD dwInputSize, 
				   PCHAR pOutput, 
				   DWORD * dwOutputSize);

void Base64Decode(
				   PCHAR pInput, 
				   DWORD dwInputSize, 
				   PCHAR pOutput, 
				   DWORD * dwOutputSize);
#endif  // __MAIN_HXX

#ifndef _VSEXCHANGEUTIL_H_
#define _VSEXCHANGEUTIL_H_

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

//
// Public ADs includes
//

#ifdef __cplusplus
extern "C" {
#endif


#include "activeds.h"
#include "oledb.h"
#include "oledberr.h"

#ifdef __cplusplus
}
#endif

#include <Winbase.h>


#define NULL_TERMINATED 0



//
// *********  Useful macros
//

#define BAIL_ON_NULL(p)       \
	if (!(p)) {           \
		goto error;   \
	}

#define BAIL_ON_FAILURE(hr)   \
	if (FAILED(hr)) {     \
		goto error;   \
	}

#define FREE_UNICODE_STRING(pMem)     \
	if (pMem) {    \
	    FreeUnicodeString(pMem); \
	    pMem = NULL;     \
	}


int AnsiToUnicodeString(LPSTR pAnsi,LPWSTR pUnicode, DWORD StringLength);
int UnicodeToAnsiString(LPWSTR pUnicode,LPSTR pAnsi,DWORD StringLength);
LPWSTR AllocateUnicodeString(LPSTR  pAnsiString );
void FreeUnicodeString(LPWSTR  pUnicodeString);

LPWSTR RemoveWhiteSpaces(LPWSTR pszText );
BSTR _MultiToWideString(LPSTR szInputString);
LPSTR _WideToMultiString(BSTR szwcInputString);
LPSTR LDAP_UTF16ToUTF8(BSTR szwcInputString,DWORD dwInputSize);
LPVOID AllocateTokenInfoBuffer(HANDLE hToken,TOKEN_INFORMATION_CLASS InfoClass,
																	DWORD *dwSize);



PSID    GetMySid(void) ;
PCHAR   EncodeSid(PSID pMySid) ;
void    ErrorHandler(CHAR *szErrorString) ;
void    InitLog(FILE *fp);
int Hascii2Bin(PCHAR InBuf, PCHAR *OutBuf, int *OutLen);
int Bin2Hasc (char **hasc, PBYTE bindata,int datalen);


#endif  // _VSEXCHANGEUTIL_H_

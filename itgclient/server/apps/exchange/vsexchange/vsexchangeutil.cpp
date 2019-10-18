/*
 * $Revision: 1.2.456.2 $
 * $Header: /cvs/itgclient/server/apps/exchange/vsexchange/vsexchangeutil.cpp,v 1.2.456.2 2003/06/18 16:44:56 npaul Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#include "vsexchangeutil.h"


static  FILE *logFile = NULL;

CHAR	szErrorString[1024] ;
HANDLE	hToken ;

int
AnsiToUnicodeString(LPSTR pAnsi,LPWSTR pUnicode,DWORD StringLength)
{
    int iReturn;

    if( StringLength == NULL_TERMINATED )
        StringLength = strlen( pAnsi );

    iReturn = MultiByteToWideChar(CP_ACP,
                                  MB_PRECOMPOSED,
                                  pAnsi,
                                  StringLength + 1,
                                  pUnicode,
                                  StringLength + 1 );

    //
    // Ensure NULL termination.
    //
    pUnicode[StringLength] = 0;

    return iReturn;
}


int
UnicodeToAnsiString(LPWSTR pUnicode,LPSTR pAnsi, DWORD StringLength)
{
    LPSTR pTempBuf = NULL;
    INT   rc = 0;

    if( StringLength == NULL_TERMINATED ) {

        //
        // StringLength is just the
        // number of characters in the string
        //
        StringLength = wcslen( pUnicode );
    }

    //
    // WideCharToMultiByte doesn't NULL terminate if we're copying
    // just part of the string, so terminate here.
    //

    pUnicode[StringLength] = 0;

    //
    // Include one for the NULL
    //
    StringLength++;

    //
    // Unfortunately, WideCharToMultiByte doesn't do conversion in place,
    // so allocate a temporary buffer, which we can then copy:
    //

    if( pAnsi == (LPSTR)pUnicode )
    {
        pTempBuf = (LPSTR)LocalAlloc( LPTR, StringLength );
        pAnsi = pTempBuf;
    }

    if( pAnsi )
    {
        rc = WideCharToMultiByte( CP_ACP,
                                  0,
                                  pUnicode,
                                  StringLength,
                                  pAnsi,
                                  StringLength,
                                  NULL,
                                  NULL );
    }

    /* If pTempBuf is non-null, we must copy the resulting string
     * so that it looks as if we did it in place:
     */
    if( pTempBuf && ( rc > 0 ) )
    {
        pAnsi = (LPSTR)pUnicode;
        strcpy( pAnsi, pTempBuf );
        LocalFree( pTempBuf );
    }

    return rc;
}


LPWSTR 
AllocateUnicodeString(LPSTR  pAnsiString)
{
    LPWSTR  pUnicodeString = NULL;

    if (!pAnsiString)
        return NULL;

    pUnicodeString = (LPWSTR)LocalAlloc(
                        LPTR,
                        strlen(pAnsiString)*sizeof(WCHAR) +sizeof(WCHAR)
                        );

    if (pUnicodeString) {

        AnsiToUnicodeString(
            pAnsiString,
            pUnicodeString,
            NULL_TERMINATED
            );
    }

    return pUnicodeString;
}


void
FreeUnicodeString(LPWSTR  pUnicodeString)
{
    if (!pUnicodeString)
        return;

    LocalFree(pUnicodeString);

    return;
}


/*****************************************************************************/
// _MultiToWideString() : Converts a Multi Byte String to Wide Character String.
//
//  Input :
//	  szInputString : LPSTR
//                Contains the Multi Byte string
//  Output :
//	  NONE
//  Returns : BSTR
//				  Returns the Wide Character String representation of the
//				  input Multi Byte String.
/*****************************************************************************/

BSTR _MultiToWideString(LPSTR szInputString)
{
	BSTR	szwcOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szInputString == NULL)
		return NULL ;

	// Obtain size of the wide char UNICODE string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								NULL,
								0) ;

	// Allocate memory for the BSTR (UNICODE string).
	if ( (szwcOutputString = SysAllocStringLen(NULL, dwSize)) == NULL )
	{
		
		return(NULL) ;
	}

	// Copy from (and convert) Multi Byte string to Wide Char string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								szwcOutputString,
								dwSize) ;
	if (!dwSize)
	{
		
		return(NULL) ;
	}

	return szwcOutputString ;
}

/*****************************************************************************/
// LDAP_UTF-16ToUTF-8() : Converts a Wide Character UTF-16 String From Exchange/AD server
// to UTF-8	Multi Byte String.
//
//  Input :
//	szwcInputString : BSTR       Contains the Wide Character string
//  DwInputSize     : DWORD      Input String Size;
//  Output :
//	  NONE
//  Returns : LPSTR
//				  Returns the Multi Byte String representation of the
//				  input Wide Character String.
/*****************************************************************************/


LPSTR LDAP_UTF16ToUTF8(BSTR szwcInputString,DWORD dwInputSize)
{
	LPSTR	szmbOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szwcInputString == NULL)
		return NULL ;

	
	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_UTF8,
								0,
								szwcInputString,
								dwInputSize,
								NULL,
								0,
								NULL,
								NULL) ;

	// Allocate memory for the Multi Byte String.
	if ( (szmbOutputString = (LPSTR)new char[dwSize]) == NULL )
	{
		
		return(NULL) ;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_UTF8,
								0,
								szwcInputString,
								dwInputSize,
								szmbOutputString,
								dwSize,
								NULL,
								NULL) ;
	if (!dwSize)
	{
		
		return(NULL) ;
	}

	return szmbOutputString ;
}

/*****************************************************************************/
// _WideToMultiString() : Converts a Wide Character String to Multi Byte String.
//
//  Input :
//	  szwcInputString : BSTR
//                Contains the Wide Character string
//  Output :
//	  NONE
//  Returns : LPSTR
//				  Returns the Multi Byte String representation of the
//				  input Wide Character String.
/*****************************************************************************/

LPSTR _WideToMultiString(BSTR szwcInputString)
{
	LPSTR	szmbOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szwcInputString == NULL)
		return NULL ;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP,
								WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString,
								-1,
								NULL,
								0,
								NULL,
								NULL) ;

	// Allocate memory for the Multi Byte String.
	if ( (szmbOutputString = (LPSTR)malloc(dwSize)) == NULL )
	{
		return(NULL) ;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP,
								WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString,
								-1,
								szmbOutputString,
								dwSize,
								NULL,
								NULL) ;
	if (!dwSize)
	{
		return(NULL) ;
	}

	return szmbOutputString ;
}


LPVOID AllocateTokenInfoBuffer(HANDLE hToken,TOKEN_INFORMATION_CLASS InfoClass,
    DWORD *dwSize)
{
    BOOL bRes;

    *dwSize=0;
    //
    // Determine size of buffer needed
    //

    bRes = GetTokenInformation(
        hToken,
        InfoClass,
        NULL,
        *dwSize, dwSize);

    //
    // Allocate a buffer for our token data
    //
    return(LocalAlloc(LPTR,*dwSize));

}


PCHAR	EncodeSid(PSID pMySID)
{
	PCHAR	szmbMySID = NULL ;
	szmbMySID = (PCHAR)malloc(28*2+1) ;

	DWORD		i ;
	CHAR		temp[10] ;

	for ( i = 0 ; i < 28 ; i++ )
	{
		itoa((int)((CHAR *)pMySID)[i] & 0xFF, temp, 16) ;
		szmbMySID[i*2] = (strlen(temp) == 2) ? temp[0] : '0' ;
		szmbMySID[i*2+1] = (strlen(temp) == 2) ? temp[1] : temp[0] ;
	}
	szmbMySID[28*2] = '\0' ;

	return(szmbMySID) ;
}

PSID	GetMySid(void)
{
	HANDLE				hCurrentProcess ;

	hCurrentProcess = GetCurrentProcess() ;
	OpenProcessToken( hCurrentProcess, TOKEN_QUERY|TOKEN_QUERY_SOURCE, &hToken );

	//
    // Get User Information
    //

	TOKEN_USER		*pUserInfo ;
	DWORD			dwSize ;
	BOOL			bRes ;

    pUserInfo = (TOKEN_USER *)AllocateTokenInfoBuffer(hToken,TokenUser,&dwSize);

    bRes = GetTokenInformation(
        hToken,
        TokenUser,
        pUserInfo,
        dwSize, &dwSize);

    if (FALSE == bRes)
    {
        ErrorHandler("GetTokenInformation failed\n");
		return(NULL) ;
    }
    
	return(pUserInfo->User.Sid) ;
}

void    InitLog(FILE *fp)
{
	logFile = fp;
}

void	ErrorHandler(CHAR *szTheErrorString)
{
	fprintf(logFile, szTheErrorString);

}

int Hascii2Bin(PCHAR hasc, PCHAR *OutBuf, int *OutLen)
{
	int status = 0;
	PCHAR data;
	unsigned int i = 0;
	int binNum;

	do {
		*OutLen = (unsigned int)(strlen(hasc)+1)/2;
		if (*OutLen > 0) {
			data = (char *) malloc (*OutLen);
			memset(data, 0, *OutLen);
			if (data != NULL) {
				while ((int)i < *OutLen) {
					status = sscanf (&hasc[2 * i], "%2x", &binNum);
					data[i] = (char)binNum;
					i++;
				}

			} else {
				*OutLen = 0;
			}
		} else {
				*OutBuf = NULL;
		}

	} while (0);
  *OutBuf = data;
  return(status);
}

int Bin2Hasc (char **hasc, PBYTE bindata,int datalen)
{
  int status = 1;
  unsigned int hascLen, i;

  hascLen = 2 * datalen + 1;
  *hasc = (char *) malloc (hascLen);

  if (*hasc != NULL)
  {
    if (datalen>0)
	{
		  for (i = 0; i < datalen; i++)
			sprintf (*hasc + 2 * i, "%02x", bindata[i]);

    } else
	{
      *hasc= '\0';
    }
  } 
  else
  {
    status = 0;
  }
  return(status);
}
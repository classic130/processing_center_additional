//---------------------------------------------------------------------------
//
//  Microsoft Active Directory 1.1 Sample Code
//
//  Copyright (C) Microsoft Corporation, 1992 - 1995
//
//  File:  util.cxx
//
//  Contents:  Ansi to Unicode conversions and misc helper functions
//
//----------------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "charutils.h"

static BOOL _decode(short input, DWORD *output);

int
AnsiToUnicodeString(
    LPSTR pAnsi,
    LPWSTR pUnicode,
    DWORD StringLength
    )
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
UnicodeToAnsiString(
    LPWSTR pUnicode,
    LPSTR pAnsi,
    DWORD StringLength
    )
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
AllocateUnicodeString(
    LPSTR  pAnsiString
    )
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
FreeUnicodeString(
    LPWSTR  pUnicodeString
    )
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






void getRandomString(BYTE *pbData, int len)
{
	DWORD dwRand;
	CHAR szRand[256];
	int i = 0;
	int count = 0;
	srand( (unsigned)time( NULL ) + GetTickCount() );

	while(1)
	{
		dwRand = rand();
		itoa(dwRand,szRand,10);

		while(szRand[i])
		{
			if(count == len)
			{
				pbData[len] = '\0';
				return;
			}
			pbData[count] = szRand[i];
			i ++;
			count ++;

		}
		i = 0;
	}

}


/*****************************************************************************/
// _Base64Decode() : Decodes a message that is in Base64 format. 
//
//				    Implements RFC 1521 - 5.2 Base64 Content-Transfer Decoding.
//
//  Input :
//	  pInput : PCHAR
//                Contains the input message that is the be decoded.
//	  dwInputSize : DWORD
//				  Specifies the size of the input message.
//  Input/Output :
//	  pOutput : PCHAR
//                Specifies the address where the decoded message is to be copied.
//
//				  If it is specified as NULL, then the output formal parameter, dwOutputSize,
//				  specifies the size of the decoded message, corresponding to the 
//				  input message specified through the formal parameter pInput.
//  Input/Output :
//	  dwOutputSize : DWORD *
//				  Specifies the size of the output decoded message.
//  Returns :
//    NONE
/*****************************************************************************/

void Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	if ( pOutput == NULL )
	{
		PCHAR	filteredInputPtr ;
		int		i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		*dwOutputSize = filteredCounter ;
		*dwOutputSize = (*dwOutputSize/4)*3 ;

		free(filteredInputPtr) ;
	}
	else
	{
		DWORD		remainingSize ;
		PCHAR		inputPtr, outputPtr, filteredInputPtr ;
		int			i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		// remainingSize = dwInputSize ;
		remainingSize = filteredCounter ;
		inputPtr = filteredInputPtr ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;

		while((int)remainingSize > 0)
		{
			DWORD tmp, tmpout ;

			_decode(inputPtr[0], &tmpout) ;
			tmp = tmpout ;

			_decode(inputPtr[1], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			_decode(inputPtr[2], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;
				
			_decode(inputPtr[3], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			if ( inputPtr[2] == '=' && inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				*dwOutputSize += 1 ;
			}
			else if ( inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				*dwOutputSize += 2 ;
			}
			else
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				outputPtr[2] = (char)((tmp & 0x000000FF)) ;
				*dwOutputSize += 3 ;
			}

			remainingSize -= 4 ;
			inputPtr += 4 ;
			outputPtr += 3 ;
		}

		free(filteredInputPtr) ;
	}
}

BOOL _decode(short input, DWORD *output)
{
	if ( input >= 'A' && input <= 'Z' )
	{
		*output = input - 'A' ;
		return TRUE ;
	}
	else if ( input >= 'a' && input <= 'z' )
	{
		*output = input - 'a' + 26 ;
		return TRUE ;
	}
	else if ( input >= '1' && input <= '9' )
	{
		*output = input - '1' + 26 + 27 ;
		return TRUE ;
	}
	else if ( input == '0' )
	{
		*output = 26 + 26 ;
		return TRUE ;
	}
	else if ( input == '+' )
	{
		*output = 62 ;
		return TRUE ;
	}
	else if (input == '/' )
	{
		*output = 63 ;
		return TRUE ;
	}
	else if (input == '=' )
	{
		*output = 0 ;
		return TRUE ;
	}
	else
	{
		*output = 0 ;
		return FALSE ;
	}
}


void Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	char _encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'} ;


	if ( pOutput == NULL )
	{
		*dwOutputSize = !(dwInputSize % 3) ? (dwInputSize/3)*4 : ((dwInputSize/3)*4) + 4 ;
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\n' '\r' after 76 chars in encoded output.
	}
	else
	{
		DWORD		remainingSize, seventySixCount ;
		PCHAR		inputPtr, outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}
			else if(remainingSize == 2)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = '=' ;
			}
			else
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[2] ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = _encode[(tmp & 0x0000003F)] ;
			}
			*dwOutputSize += 4 ;
			seventySixCount += 4 ;
			remainingSize -= 3 ;
			inputPtr += 3 ;
			outputPtr += 4 ;

			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\r' ;
				outputPtr[1] = '\n' ;
				outputPtr += 2 ;
			}
		}
	}

}

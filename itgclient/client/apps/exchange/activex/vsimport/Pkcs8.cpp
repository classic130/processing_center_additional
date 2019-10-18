// Pkcs8.cpp: implementation of the CPkcs8 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImportPKCS12.h"
#include "Pkcs8.h"
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPkcs8::CPkcs8()
{
	m_bBreakPKCS8 = FALSE ;
}

CPkcs8::~CPkcs8()
{

}

BOOL CPkcs8::generatePRIVATEKEYBLOB(CRYPT_PRIVATEKEYBLOB *p_PrivateKeyBlob)
{
	if (!m_bBreakPKCS8)
	{
		return FALSE ;
	}

	m_cbPRIVATEKEYBLOB =	sizeof(BLOBHEADER) +
							sizeof(RSAPUBKEY) +
							m_MyPrivateKeyBlob.modulus.cbData +
							m_MyPrivateKeyBlob.prime1.cbData +
							m_MyPrivateKeyBlob.prime2.cbData +
							m_MyPrivateKeyBlob.exponent1.cbData +
							m_MyPrivateKeyBlob.exponent2.cbData +
							m_MyPrivateKeyBlob.coefficient.cbData +
							m_MyPrivateKeyBlob.privateExponent.cbData ;

	DWORD dwOffset = 0 ;

	m_pbPRIVATEKEYBLOB = (PBYTE) malloc(m_cbPRIVATEKEYBLOB) ;

	// BLOBHEADER
	memcpy((void *)m_pbPRIVATEKEYBLOB, (void *)&(m_MyPrivateKeyBlob.blobheader), sizeof(BLOBHEADER)) ;

	dwOffset = sizeof(BLOBHEADER) ;

	// RSAPUBKEY
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)&(m_MyPrivateKeyBlob.rsapubkey), sizeof(RSAPUBKEY)) ;

	dwOffset += sizeof(RSAPUBKEY) ;

	// Modulus
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.modulus.pbData), m_MyPrivateKeyBlob.modulus.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.modulus.cbData ;

	// Prime1
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.prime1.pbData), m_MyPrivateKeyBlob.prime1.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.prime1.cbData ;

	// Prime2
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.prime2.pbData), m_MyPrivateKeyBlob.prime2.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.prime2.cbData ;

	// Exponent1
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.exponent1.pbData), m_MyPrivateKeyBlob.exponent1.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.exponent1.cbData ;

	// Exponent2
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.exponent2.pbData), m_MyPrivateKeyBlob.exponent2.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.exponent2.cbData ;

	// Coefficient
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.coefficient.pbData), m_MyPrivateKeyBlob.coefficient.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.coefficient.cbData ;

	// Private Exponent
	memcpy((void *)(m_pbPRIVATEKEYBLOB+dwOffset), (void *)(m_MyPrivateKeyBlob.privateExponent.pbData), m_MyPrivateKeyBlob.privateExponent.cbData) ;

	dwOffset += m_MyPrivateKeyBlob.privateExponent.cbData ;

	p_PrivateKeyBlob->cbData = m_cbPRIVATEKEYBLOB ;
	p_PrivateKeyBlob->pbData = m_pbPRIVATEKEYBLOB ;

	return TRUE ;
}

CPkcs8::CPkcs8(LPSTR	szBase64PKCS8)
{
	BYTE			*pbPKCS8Blob = NULL ;
	DWORD			cbPKCS8Blob = 0 ;


	_Base64Decode(szBase64PKCS8,
				  strlen(szBase64PKCS8),
				  NULL,
				  &cbPKCS8Blob) ;

	if ( (pbPKCS8Blob = (BYTE *) malloc(cbPKCS8Blob+1)) == NULL )
	{
		_ShowErrorMessage(E_UNEXPECTED, "CPkcs8::CPkcs8 : Out of memory.") ;
	}

	_Base64Decode(szBase64PKCS8,
				  strlen(szBase64PKCS8),
				  (PCHAR)pbPKCS8Blob,
				  &cbPKCS8Blob) ;

	CRYPT_PKCS8_BLOB	pkcs8Blob ;

	pkcs8Blob.cbData = cbPKCS8Blob ;
	pkcs8Blob.pbData = pbPKCS8Blob ;

	if ( !_myCryptDecodeObject(szOID_PKCS8, (PCRYPT_MYDER_BLOB)&pkcs8Blob, (PBYTE) &m_MyPrivateKeyBlob) )
	{
		_ShowErrorMessage(GetLastError(), "CPkcs8::CPkcs8 : Invalid PFX PDU") ;
	}

	m_bBreakPKCS8 = TRUE ;
}


/*****************************************************************************/
// _ShowErrorMessage :This function shows a message box that displays the error 
//					message corresponding to the errorcode passed to it.
//
// Input :
//	 errorCode : DWORD
//					The error code whose corresponding Error Message is to be shown.
//   szExtraString : LPSTR
//					This string is appended to the Error Message string that corresponds
//					to the error code.
// Output :
//	 NONE
// Returns :
//	 NONE 
/*****************************************************************************/

void CPkcs8::_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString)
{
	LPVOID		ErrorMessage ;

	FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			(LPCVOID) NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &ErrorMessage,
			0,
			NULL) ;

	// Display the string.
	CHAR	temp[1024], temp2[1024] ;
	sprintf(temp, "CImpPKCS12::%s", szExtraString) ;
	sprintf(temp2, "%sError Code : 0x%08x", ErrorMessage, errorCode) ;

#ifdef _DEBUG
	::MessageBox( NULL, (LPCTSTR) temp2, (LPCTSTR) _T(temp), MB_OK | MB_ICONINFORMATION );
#endif

	LocalFree( ErrorMessage ) ;
}

/*****************************************************************************/
// _Base64Encode() : Encodes a message in Base64 format. The encoded output contains
//				    a CR-LF sequence after every 76 encoded bytes.
//
//				    Implements RFC 1521 - 5.2 Base64 Content-Transfer Encoding.
//
//  Input :
//	  pInput : PCHAR
//                Contains the input message that is the be encoded.
//	  dwInputSize : DWORD
//				  Specifies the size of the input message.
//  Input/Output :
//	  pOutput : PCHAR
//                Specifies the address where the encoded message is to be copied.
//
//				  If it is specified as NULL, then the output formal parameter, dwOutputSize,
//				  specifies the size of the encoded message, corresponding to the 
//				  input message specified through the formal parameter pInput.
//  Input/Output :
//	  dwOutputSize : DWORD *
//				  Specifies the size of the output encoded message.
//  Returns :
//    NONE
/*****************************************************************************/

void CPkcs8::_Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}
		}
	}
}

BOOL	CPkcs8::_decode(short input, DWORD *output)
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

void CPkcs8::_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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

LPSTR CPkcs8::_WideToMultiString(BSTR szwcInputString)
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
		_ShowErrorMessage(GetLastError(), "_WideToMultiString : Out of memory") ;
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
		_ShowErrorMessage(GetLastError(), "_WideToMultiString : Unable to convert from Wide Char string to Multi Byte string") ;
		return(NULL) ;
	}

	return szmbOutputString ;
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

BSTR CPkcs8::_MultiToWideString(LPSTR szInputString)
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
		_ShowErrorMessage(GetLastError(), "_MultiToWideString : Out of memory") ;
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
		_ShowErrorMessage(GetLastError(), "_MultiToWideString : Unable to convert from Multi Byte string to Wide Char string") ;
		return(NULL) ;
	}

	return szwcOutputString ;
}

BOOL	CPkcs8::_GetASNInfo(PBYTE input, BYTE *type, DWORD *length, DWORD *numberOfLengthBytes)
{
	BOOL	retVal = FALSE ;

	*type = INVALID_ASN_TYPE ;

	switch ( input[0] )
	{
		case SEQUENCE :
		case OCTET_STRING :
		case UNIVERSAL_INTEGER :
			*type = input[0] ;

			if ( input[1] & 0x80 )
			{
				int		i, numberOfBytes ;
				DWORD	tmplength ;

				numberOfBytes = input[1] & 0x7F ;

				*length = 0 ;
				for ( i = 0 ; i < numberOfBytes ; i++ )
				{
					tmplength = 0 ;
					tmplength = input[(2+numberOfBytes-1)-i] ;
					tmplength <<= (i*8) ;
					*length |= tmplength ;
				}
				*numberOfLengthBytes = numberOfBytes ;
			}
			else
			{
				*length = input[1] ;
				*numberOfLengthBytes = 0 ;
			}
			retVal = TRUE ;
			break ;

		case OBJECT_IDENTIFIER :
			*type = OBJECT_IDENTIFIER ;
			*length = input[1] ;
			retVal = TRUE ;
			break ;

		case NULL_STUFF :
			*type = NULL_STUFF ;
			*length = input[1] ;
			retVal = TRUE ;
			break ;

		default :
			_ShowErrorMessage(E_UNEXPECTED, "_GetASNInfo : Invalid ASN type") ;
			retVal = FALSE ;
			break ;
	}
	return retVal ;
}

BOOL	CPkcs8::_myCryptDecodeObject(LPSTR szOID, PCRYPT_MYDER_BLOB pMyDERBlob, PBYTE pOutputStruct)
{
	BOOL	bRetVal = FALSE ;

	if ( strcmp(szOID, szOID_PKCS12) == 0 )
	{
		PPFX		pPFX = NULL ;
		BYTE		ASNtype ;
		DWORD		nolb = 0, dwDEROffset = 0, dwTMP = 0 ;

		pPFX = (PPFX) pOutputStruct ;

		// Check for a SEQUENCE for PFX itself
		if ( !_GetASNInfo(pMyDERBlob->pbData, &ASNtype, &(pPFX->dwPFXDERlength), &nolb) )
		{
			return FALSE ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid PFX PDU") ;
			return FALSE ;
		}

		dwDEROffset = 2 + nolb ;

		// Check for "Version" (UNIVERSAL INTEGER) inside the PFX
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid Version inside PFX PDU") ;
			return FALSE ;
		}

		dwDEROffset += 2 + dwTMP - 1 ;
		pPFX->version = pMyDERBlob->pbData[dwDEROffset] ;
		dwDEROffset++ ;

		pPFX->authSafe.pbData = (PBYTE) (pMyDERBlob->pbData + dwDEROffset) ;

		// Check for "ContentInfo" (SEQUENCE) inside the PFX
		if ( !_GetASNInfo((PBYTE)(pPFX->authSafe.pbData), &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid ContenInfo inside PFX PDU") ;
			return FALSE ;
		}

		pPFX->authSafe.cbData = dwTMP ;

		dwDEROffset += 2 + nolb + dwTMP ;

		pPFX->macData.pbData = (PBYTE) (pMyDERBlob->pbData + dwDEROffset) ;

		// Check for "MacData" (SEQUENCE) inside the PFX
		if ( !_GetASNInfo((PBYTE)(pPFX->macData.pbData), &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid MacData inside PFX PDU") ;
			return FALSE ;
		}
		pPFX->macData.cbData = dwTMP ;

		bRetVal = TRUE ;
	}
	else if ( strcmp(szOID, szOID_PKCS8) == 0 )
	{
		PMY_PRIVATEKEYBLOB	pMyPrivateKeyBlob = NULL ;
		BYTE				ASNtype ;
		DWORD				nolb = 0, dwDEROffset = 0, dwTMP = 0 ;

		pMyPrivateKeyBlob = (PMY_PRIVATEKEYBLOB) pOutputStruct ;

		pMyPrivateKeyBlob->blobheader.bType = PRIVATEKEYBLOB ;
		pMyPrivateKeyBlob->blobheader.bVersion = 0x02 ;
		pMyPrivateKeyBlob->blobheader.reserved = 0x0000 ;
		pMyPrivateKeyBlob->blobheader.aiKeyAlg = CALG_RSA_KEYX ;

		pMyPrivateKeyBlob->rsapubkey.magic = 0x32415352 ; // "RSA2" - LS Byte of magic contains 'R' : MS Byte contains '2'

		// Check for a SEQUENCE for PKCS#8 itself
		if ( !_GetASNInfo(pMyDERBlob->pbData, &ASNtype, &dwTMP, &nolb) )
		{
			return FALSE ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid PKCS#8 DER") ;
			return FALSE ;
		}

		dwDEROffset = 2 + nolb ;

		// Check for "Version" (UNIVERSAL INTEGER) inside the PKCS#8 DER
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid Version inside PKCS#8 DER") ;
			return FALSE ;
		}

		dwDEROffset += 2 + dwTMP ;

		// Check for SEQUENCE which contains the Algorithm Identifier (OBJECT IDENTIFIER) for the PKCS#8
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid SEQUENCE for OID inside PKCS#8") ;
			return FALSE ;
		}

		dwDEROffset += 2 ;

		// Check for "Algorithm Identifier" (OBJECT IDENTIFIER) for the PKCS#8
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != OBJECT_IDENTIFIER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid OBJECT IDENTIFIER inside PKCS#8") ;
			return FALSE ;
		}

		dwDEROffset += 2 + dwTMP ;

		// Check for NULL_STUFF in the PKCS#8
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != NULL_STUFF )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid NULL_STUFF inside PKCS#8") ;
			return FALSE ;
		}

		dwDEROffset += 2 + dwTMP ;

		// Check for OCTET_STRING in the PKCS#8
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != OCTET_STRING )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid NULL_STUFF inside PKCS#8") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		pMyPrivateKeyBlob->pbRSAPrivateKeyBlob = pMyDERBlob->pbData + dwDEROffset ;

		// Check for SEQUENCE for the RSAPrivateKey DER itself
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid SEQUENCE inside PKCS#8 for RSAPrivateKey") ;
			return FALSE ;
		}

		pMyPrivateKeyBlob->cbRSAPrivateKeyBlob = dwTMP ;

#if 0
		FILE	*fp = NULL ;
		fp = fopen("e:\\temp\\junk.der", "wb") ;
		fwrite(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob, 1, dwTMP, fp) ;
		fclose(fp) ;
#endif

		dwDEROffset = 2 + nolb ;

		// Check for "version" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid version inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;
		pMyPrivateKeyBlob->version = pMyPrivateKeyBlob->pbRSAPrivateKeyBlob[dwDEROffset] ;
		dwDEROffset += dwTMP ;

		// Check for "modulus" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid modulus inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbModulus ;
		PBYTE	pbModulus = NULL ;

		cbModulus = dwTMP ; // Number of bytes that make "modulus"
		// pMyPrivateKeyBlob->rsapubkey.bitlen = 1024 ; // Number of bits that make "modulus"

		pbModulus = (PBYTE) malloc(cbModulus) ;

		memcpy((void *)pbModulus, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbModulus) ;
		_Reverse(cbModulus, pbModulus) ;
		pMyPrivateKeyBlob->modulus.cbData = cbModulus & 0xFFFFFFFE ;
		pMyPrivateKeyBlob->modulus.pbData = pbModulus ;

		dwDEROffset += cbModulus ;
		
		// Check for "public exponent" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid public exponent inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	dwPublicExponent = 0x00000000 ;

		memcpy((void *)&dwPublicExponent, ((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), dwTMP) ;
		_Reverse(dwTMP, (PBYTE)&dwPublicExponent) ;

		pMyPrivateKeyBlob->rsapubkey.pubexp = dwPublicExponent ;

		dwDEROffset += dwTMP ;

		// Check for "private exponent" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid private exponent inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbPrivateExponent ;
		PBYTE	pbPrivateExponent = NULL ;

		cbPrivateExponent = dwTMP ;

		pbPrivateExponent = (PBYTE) malloc(cbPrivateExponent) ;
		memcpy((void *)pbPrivateExponent, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbPrivateExponent) ;
		_Reverse(cbPrivateExponent, pbPrivateExponent) ;
		pMyPrivateKeyBlob->privateExponent.cbData = cbPrivateExponent & 0xFFFFFFFE ;
		pMyPrivateKeyBlob->privateExponent.pbData = pbPrivateExponent ;

		dwDEROffset += cbPrivateExponent ;

		// Check for "prime1" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid prime1 inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbPrime1 ;
		PBYTE	pbPrime1 = NULL ;

		cbPrime1 = dwTMP ;

		pbPrime1 = (PBYTE) malloc(cbPrime1) ;
		memcpy((void *)pbPrime1, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbPrime1) ;
		_Reverse(cbPrime1, pbPrime1) ;
		pMyPrivateKeyBlob->prime1.cbData = cbPrime1 & 0xFFFFFFFE ;
		pMyPrivateKeyBlob->prime1.pbData = pbPrime1 ;

		dwDEROffset += cbPrime1 ;

		// Check for "prime2" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid prime2 inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbPrime2 ;
		PBYTE	pbPrime2 = NULL ;

		cbPrime2 = dwTMP ;

		pbPrime2 = (PBYTE) malloc(cbPrime2) ;
		memcpy((void *)pbPrime2, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbPrime2) ;
		_Reverse(cbPrime2, pbPrime2) ;
		pMyPrivateKeyBlob->prime2.cbData = cbPrime2 & 0xFFFFFFFE;
		pMyPrivateKeyBlob->prime2.pbData = pbPrime2 ;

		dwDEROffset += cbPrime2 ;

		// Check for "exponent1" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid exponent1 inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbExponent1 ;
		PBYTE	pbExponent1 = NULL ;

		cbExponent1 = dwTMP ;

		pbExponent1 = (PBYTE) malloc(cbExponent1) ;
		memcpy((void *)pbExponent1, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbExponent1) ;
		_Reverse(cbExponent1, pbExponent1) ;
		pMyPrivateKeyBlob->exponent1.cbData = cbExponent1 & 0xFFFFFFFE ;
		pMyPrivateKeyBlob->exponent1.pbData = pbExponent1 ;

		dwDEROffset += cbExponent1 ;

		// Check for "exponent2" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid exponent2 inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbExponent2 ;
		PBYTE	pbExponent2 = NULL ;

		cbExponent2 = dwTMP ;

		pbExponent2 = (PBYTE) malloc(cbExponent2) ;
		memcpy((void *)pbExponent2, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbExponent2) ;
		_Reverse(cbExponent2, pbExponent2) ;
		pMyPrivateKeyBlob->exponent2.cbData = cbExponent2 & 0xFFFFFFFE ;
		pMyPrivateKeyBlob->exponent2.pbData = pbExponent2 ;

		dwDEROffset += cbExponent2 ;

		// Check for "coefficient" (UNIVERSAL_INTEGER) inside the RSAPrivateKey DER
		if ( !_GetASNInfo(pMyPrivateKeyBlob->pbRSAPrivateKeyBlob + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid coefficient inside RSAPrivateKey") ;
			return FALSE ;
		}

		dwDEROffset += 2 + nolb ;

		DWORD	cbCoefficient ;
		PBYTE	pbCoefficient = NULL ;

		cbCoefficient = dwTMP ;

		pbCoefficient = (PBYTE) malloc(cbCoefficient) ;
		memcpy((void *)pbCoefficient, (void *)((pMyPrivateKeyBlob->pbRSAPrivateKeyBlob) + dwDEROffset), cbCoefficient) ;
		_Reverse(cbCoefficient, pbCoefficient) ;
		pMyPrivateKeyBlob->coefficient.cbData = cbCoefficient & 0xFFFFFFFE;
		pMyPrivateKeyBlob->coefficient.pbData = pbCoefficient ;

		dwDEROffset += cbCoefficient ;

		// Number of bits that make the public key.
		pMyPrivateKeyBlob->rsapubkey.bitlen = (cbCoefficient & 0xFFFFFFFE) * 16 ; 

		bRetVal = TRUE ;
	}
	else
	{
		_ShowErrorMessage(E_UNEXPECTED, "_myCryptDecodeObject : Invalid szOID") ;
		bRetVal = FALSE ;
	}

	return bRetVal ;
}

void	CPkcs8::_Reverse(DWORD dwStream, PBYTE pbStream)
{
	PBYTE	output = NULL ;
	DWORD		i = 0 ;

	output = (PBYTE) malloc(dwStream) ;

	for ( i = 0 ; i < dwStream ; i++ )
		output[i] = pbStream[dwStream-1-i] ;

	memcpy((void *)pbStream, (void *)output, (size_t) dwStream) ;

	free (output) ;
}

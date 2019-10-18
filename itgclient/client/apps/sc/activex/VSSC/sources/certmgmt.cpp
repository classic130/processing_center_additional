#include "stdafx.h"
#include "certmgmt.h"

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

LPTSTR Enc_GetCertIssuerDN(VS_RECIPIENT_INFO *pCertInfo)
{
	CERT_NAME_BLOB NameBlob;
	DWORD dwSize = 0, dwError;
	LPTSTR lpIssuerDN = NULL;
	LPTSTR lpFormattedDN = NULL;

	if(!pCertInfo)
		return NULL;

	NameBlob.cbData = pCertInfo->Issuer.cbData;
	NameBlob.pbData=  pCertInfo->Issuer.pbData;

    // Call CertNameToStr to get the Subject RDN string length.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob,
		      CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, NULL, dwSize);

	// This function always returns a null char (0), so the minimum count returned 
	// will be 1, even if nothing got converted.
    if(dwSize <= 1) 
	{
		dwError = GetLastError();
		return NULL;
	}

    // Allocate memory for the returned string.
    lpIssuerDN = (LPTSTR)malloc((dwSize + 1) * sizeof(TCHAR));
    if(!lpIssuerDN)
	{
		return NULL;
	}
	
    // Call CertNameToStr to get the string.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob,
			  CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, lpIssuerDN, dwSize);

    if(dwSize <= 1)
	{
		dwError = GetLastError();
	
		free(lpIssuerDN);
        return NULL;
	}
    
	// new PTA format is different from old one
	// Strip only quotes from the issuer dn 
	if((lpFormattedDN = (LPTSTR)malloc(sizeof(TCHAR)*(lstrlen(lpIssuerDN) + 1))) == NULL)
	{
		free(lpIssuerDN);
		return NULL;
	}
	else
	{
		for(int i = 0, j = 0; i <lstrlen(lpIssuerDN); i++)
		{
			if(lpIssuerDN[i] != '"')
			{
				lpFormattedDN[j] = lpIssuerDN[i];
				j++;
			}
		}

		lpFormattedDN[j] = '\0';
	}

	free(lpIssuerDN);
	return lpFormattedDN;

}

LPTSTR Enc_GetCertSerNum(VS_RECIPIENT_INFO *pCertInfo)
{
	CRYPT_INTEGER_BLOB SerialNumberBlob ;
	DWORD dwSerialNumber = 0;
	PBYTE SerialNumber ;
	LPTSTR lpSerNum;

	if(!pCertInfo)
		return NULL;

    SerialNumberBlob.cbData = pCertInfo->SerialNumber.cbData;
	SerialNumberBlob.pbData=  pCertInfo->SerialNumber.pbData;
	dwSerialNumber = SerialNumberBlob.cbData;
	
	if((SerialNumber = (PBYTE)malloc(dwSerialNumber)) == NULL)
	{
		
		return NULL;
	}
	else
	{
		// Reverse the bytes
		unsigned int i;
		for (i = 0; i < dwSerialNumber; i++)
			SerialNumber[dwSerialNumber-1-i] = SerialNumberBlob.pbData[i] ;

		if((lpSerNum = (LPTSTR)malloc(((dwSerialNumber*2)+1)*sizeof(TCHAR))) == NULL)
		{
			free(SerialNumber);
			return NULL;
		}
		else
		{
			for(i = 0; i < dwSerialNumber; i++)
				sprintf((lpSerNum)+(i*2), "%02x", (unsigned char)SerialNumber[i]) ;
			
			free(SerialNumber);
		}
	}

	return lpSerNum;

}

LPTSTR GetCertSerNum(PCERT_INFO pCertInfo)
{
	CRYPT_INTEGER_BLOB SerialNumberBlob ;
	DWORD dwSerialNumber = 0;
	PBYTE SerialNumber ;
	LPTSTR lpSerNum;

	if(!pCertInfo)
		return NULL;

    SerialNumberBlob = pCertInfo->SerialNumber;
	dwSerialNumber = SerialNumberBlob.cbData;
	
	if((SerialNumber = (PBYTE)malloc(dwSerialNumber)) == NULL)
	{
		
		return NULL;
	}
	else
	{
		// Reverse the bytes
		unsigned int i;
		for (i = 0; i < dwSerialNumber; i++)
			SerialNumber[dwSerialNumber-1-i] = SerialNumberBlob.pbData[i] ;

		if((lpSerNum = (LPTSTR)malloc(((dwSerialNumber*2)+1)*sizeof(TCHAR))) == NULL)
		{
			free(SerialNumber);
			return NULL;
		}
		else
		{
			for(i = 0; i < dwSerialNumber; i++)
				sprintf((lpSerNum)+(i*2), "%02x", (unsigned char)SerialNumber[i]) ;
			
			free(SerialNumber);
		}
	}

	return lpSerNum;

}

LPTSTR GetCertIssuerDN(PCERT_INFO pCertInfo)
{
	CERT_NAME_BLOB NameBlob;
	DWORD dwSize = 0, dwError;
	LPTSTR lpIssuerDN = NULL;
	LPTSTR lpFormattedDN = NULL;

	if(!pCertInfo)
		return NULL;

	NameBlob = pCertInfo->Issuer;

    // Call CertNameToStr to get the Subject RDN string length.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob,
		      CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, NULL, dwSize);

	// This function always returns a null char (0), so the minimum count returned 
	// will be 1, even if nothing got converted.
    if(dwSize <= 1) 
	{
		dwError = GetLastError();
		return NULL;
	}

    // Allocate memory for the returned string.
    lpIssuerDN = (LPTSTR)malloc((dwSize + 1) * sizeof(TCHAR));
    if(!lpIssuerDN)
	{
		return NULL;
	}
	
    // Call CertNameToStr to get the string.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob,
			  CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, lpIssuerDN, dwSize);

    if(dwSize <= 1)
	{
		dwError = GetLastError();
	
		free(lpIssuerDN);
        return NULL;
	}
    
	// new PTA format is different from old one
	// Strip only quotes from the issuer dn 
	if((lpFormattedDN = (LPTSTR)malloc(sizeof(TCHAR)*(lstrlen(lpIssuerDN) + 1))) == NULL)
	{
		free(lpIssuerDN);
		return NULL;
	}
	else
	{
		for(int i = 0, j = 0; i <lstrlen(lpIssuerDN); i++)
		{
			if(lpIssuerDN[i] != '"')
			{
				lpFormattedDN[j] = lpIssuerDN[i];
				j++;
			}
		}

		lpFormattedDN[j] = '\0';
	}

	free(lpIssuerDN);
	return lpFormattedDN;

}






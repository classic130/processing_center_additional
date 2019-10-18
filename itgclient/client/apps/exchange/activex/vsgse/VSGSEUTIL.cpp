#include "stdafx.h"
#include "ProfAdmin.h"
#include "vsgseutil.h"

#ifdef	_VS_LOG_MSG_
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSGSE

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

void _ShowErrorMessage(DWORD errorCode, LPSTR szExtraString)
{
	LPVOID		ErrorMessage ;
	DWORD       nRetVal;
	BSTR		m_bstrErrorCodeString ;		
	HRESULT     hr=S_OK;

	nRetVal=FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			(LPCVOID) NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &ErrorMessage,
			0,
			NULL);

//	if(nRetVal>0)
//	{
//	     AtlReportError(CLSID_CObj, (LPCTSTR) pMsgBuf, IID_IObj, hr);
//	}

        

	// Display the string.
	CHAR	temp[1024], temp2[1024] ;
	sprintf(temp, "CCertPublish::%s", szExtraString) ;
	sprintf(temp2, "%sError Code : 0x%08x", ErrorMessage, errorCode) ;

#ifdef _DEBUG
	::MessageBox( NULL, (LPCTSTR) temp2, (LPCTSTR) _T(temp), MB_OK | MB_ICONINFORMATION );
#endif

	// Copy Error Information in the 
	hr = HRESULT_FROM_WIN32(errorCode) ;
	m_bstrErrorCodeString = _MultiToWideString((char *)ErrorMessage) ;

	LocalFree( ErrorMessage ) ;
}



HRESULT _SetFriendlyName(HCERTSTORE hCertStore,	PBYTE pbUserCertificate, DWORD cbUserCertificate )
{


	HRESULT hr = S_OK;

	DWORD dwBufLen=MAXLEN;

	PCCERT_CONTEXT	pFriendlyNameContext = NULL ;
	if ( (pFriendlyNameContext = CertCreateCertificateContext(
								X509_ASN_ENCODING, 
								pbUserCertificate,			
								cbUserCertificate)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertCreateCertificateContext falied") ;
		return hr ;
	}

		PCCERT_CONTEXT  pFriendlyNameCert ;
		
		if ( (pFriendlyNameCert = CertFindCertificateInStore(
				  hCertStore,				     // Store handle
				  MY_ENCODING_TYPE,              // Encoding type
				  0,                             // Not used
				  CERT_FIND_PUBLIC_KEY,            // Find type
				  &pFriendlyNameContext->pCertInfo->SubjectPublicKeyInfo,					 // Name string
				  NULL)) == NULL )               // Previous context
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertFindCertificateInStore for friendly name falied") ;
			return hr ;
		}

		WCHAR	pwszNameString[MAXLEN];
		
		if(!CertGetNameStringW(
			pFriendlyNameCert,
			CERT_NAME_SIMPLE_DISPLAY_TYPE,
			0,
			NULL,
			pwszNameString,
			dwBufLen))
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertGetNameString falied") ;
			return hr ;
		}


		///////////TBD
		{
			WCHAR	*tmpstart=NULL;
			tmpstart = wcschr(pwszNameString, L'(') ;
			if(tmpstart!=NULL)
			{
				tmpstart++ ;
				DWORD count = 0 ;
				while (*tmpstart != L',')
				{
					pwszNameString[count++] = *tmpstart++ ;
				}
				pwszNameString[count] = L'\0' ;
			}
		}

		// Find the count of certs 
		
		
		WCHAR pwszRFC822Name[MAXLEN];
		WCHAR pwszSubjectName[MAXLEN];
		WCHAR pwszIssuerName[MAXLEN];



		if(!CertGetNameStringW(
			   pFriendlyNameCert,
			   CERT_NAME_EMAIL_TYPE,
			   0,
			   NULL,
			   pwszRFC822Name,
			   dwBufLen))
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertGetNameString falied") ;
			return hr ;
		}

		if(!CertGetNameStringW(
			   pFriendlyNameCert,
			   CERT_NAME_RDN_TYPE,
			   0,
			   NULL,
			   pwszSubjectName,
			   dwBufLen))
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertGetNameString falied") ;
			return hr ;
		}

		if(!CertGetNameStringW(
			   pFriendlyNameCert,
			   CERT_NAME_RDN_TYPE,
			   CERT_NAME_ISSUER_FLAG,
			   NULL,
			   pwszIssuerName,
			   dwBufLen))
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertGetNameString falied") ;
			return hr ;
		}

		BOOL bUsage;
		BYTE pbUsage;
		DWORD dwBytes = 1;
		BOOL bIntendedKeyUsage = TRUE;
		FRDLYNAMETYPE eType;

		//CRYPT_DATA_BLOB  Friendly_Name_Blob={256,szUsage};
		
		bUsage = CertGetIntendedKeyUsage(
			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
			pFriendlyNameCert->pCertInfo,
			&pbUsage,
			dwBytes);
		if(bUsage)
		{
			//CERT_DATA_ENCIPHERMENT_KEY_USAGE for EFS
			if(pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE) || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE) )
			{
				eType = BOTH;
			}
			else if(pbUsage == CERT_DIGITAL_SIGNATURE_KEY_USAGE || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
			{
				eType = SIGN;
			}
			else if(pbUsage == CERT_KEY_ENCIPHERMENT_KEY_USAGE || pbUsage == (CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
			{
				eType = ENCRYPT;
			}
		}

		int count = 0;
		if ( _GetCertCount(hCertStore, pwszRFC822Name, pwszSubjectName, pwszIssuerName, eType, &count) != S_OK)
		{
			return hr;
		}
		count++;

		WCHAR pwszFriendlyName[MAXLEN];
		WCHAR pwszCount[16];

		wcscpy(pwszFriendlyName,pwszNameString);

		switch(eType)
		{
		case BOTH:
			break;
		case SIGN:
			wcscat(pwszFriendlyName, SIGNCERT);
			break;
		case ENCRYPT:
			wcscat(pwszFriendlyName, ENCRYPTCERT);
			break;
		}

		wcscat(pwszFriendlyName,L"#");
		_itow(count, pwszCount, 10);
		wcscat(pwszFriendlyName, pwszCount);


		DWORD len = (wcslen(pwszFriendlyName) + 1) * sizeof(WCHAR);
		BYTE *pName = (BYTE *)malloc(len);
		memcpy(pName, pwszFriendlyName, len);

		
		CRYPT_DATA_BLOB  Friendly_Name_Blob={len,pName};

		if(!CertSetCertificateContextProperty(
					pFriendlyNameCert,  
					CERT_FRIENDLY_NAME_PROP_ID,      
					0,
					&Friendly_Name_Blob))
		{
   			_ShowErrorMessage(GetLastError(), "CertSetCertificateContextProperty : CertGetNameString falied") ;
			return hr ;
		}
		// freeing up the context to be done.
		if (pFriendlyNameContext)
			CertFreeCertificateContext(pFriendlyNameContext) ;

		if (pFriendlyNameCert)
			CertFreeCertificateContext(pFriendlyNameCert) ;

		if(pName)
			free(pName);


	return hr;

}

HRESULT _SetEFSCertificate(HCERTSTORE hCertStore,
						   PBYTE pbUserCertificate, DWORD cbUserCertificate )
{


		HRESULT hr = S_OK;

		DWORD dwBufLen=MAXLEN;

		PCCERT_CONTEXT	pFriendlyNameContext = NULL ;
		if ( (pFriendlyNameContext = CertCreateCertificateContext(
									X509_ASN_ENCODING, 
									pbUserCertificate,			
									cbUserCertificate)) == NULL )
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertCreateCertificateContext falied") ;
			return hr ;
		}

		PCCERT_CONTEXT  pFriendlyNameCert ;
		
		if ( (pFriendlyNameCert = CertFindCertificateInStore(
				  hCertStore,				     // Store handle
				  MY_ENCODING_TYPE,              // Encoding type
				  0,                             // Not used
				  CERT_FIND_PUBLIC_KEY,            // Find type
				  &pFriendlyNameContext->pCertInfo->SubjectPublicKeyInfo,					 // Name string
				  NULL)) == NULL )               // Previous context
		{
			_ShowErrorMessage(GetLastError(), "put_SigningCertFriendlyName : CertFindCertificateInStore for friendly name falied") ;
			return hr ;
		}


		BOOL bUsage,bSetCert=FALSE;
		BYTE pbUsage;
		DWORD dwBytes = 1;
		BOOL bIntendedKeyUsage = TRUE;
		FRDLYNAMETYPE eType;

		//CRYPT_DATA_BLOB  Friendly_Name_Blob={256,szUsage};
		
		bUsage = CertGetIntendedKeyUsage(
			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
			pFriendlyNameCert->pCertInfo,
			&pbUsage,
			dwBytes);

		if(bUsage)
		{
			//CERT_DATA_ENCIPHERMENT_KEY_USAGE for EFS
			if(pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE) || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE) )
			{
				eType = BOTH;
			}
			else if(pbUsage == CERT_DIGITAL_SIGNATURE_KEY_USAGE || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
			{
				eType = SIGN;
			}
			else if(pbUsage == CERT_KEY_ENCIPHERMENT_KEY_USAGE || pbUsage == (CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
			{
				eType = ENCRYPT;
			}
		}

		
		
		switch(eType)
		{
		case BOTH:
			break;
		case ENCRYPT:
			
			break;
		}

		PSID pMySID=GetMySid();
		if ((pMySID = GetMySid()) == NULL)
		{
				  hr= E_UNABLE_TO_GET_SID;
				  #ifdef	_VS_LOG_MSG_
					
					VSGSE_Log(FALSE,L"ERROR:GetMySid FAILED :Error Code : 0x%08X",hr);
					VSGSE_Log(FALSE,L"ERROR: GetMySID FAILED");

				  #endif
				 
		}


		ENCRYPTION_CERTIFICATE     encCertificate;
		EFS_CERTIFICATE_BLOB       efsCertBlob;
		efsCertBlob.dwCertEncodingType =X509_ASN_ENCODING;
		efsCertBlob.pbData = pbUserCertificate;
		efsCertBlob.cbData = cbUserCertificate;

		encCertificate.cbTotalLength =sizeof(ENCRYPTION_CERTIFICATE);
		encCertificate.pUserSid =(SID*)pMySID;
		encCertificate.pCertBlob =&efsCertBlob;

		DWORD dwRet=SetUserFileEncryptionKey(&encCertificate);
		if(dwRet!=ERROR_SUCCESS)
		{
			hr=HRESULT_FROM_WIN32(GetLastError()) ;
		}



	return hr;

}




HRESULT _GetCertCount(HCERTSTORE hCertStore, WCHAR* pwszRFC822Name, 
							  WCHAR* pwszSubjectName, WCHAR* pwszIssuerName, FRDLYNAMETYPE eType, int *nCount)


{
	
	DWORD dwBufLen=MAXLEN;
	HRESULT hr = S_OK ;

	PCCERT_CONTEXT  pCertContext=NULL;  

	//////TBD
	WCHAR pwszNameString[MAXLEN];
	int count = 0;

	while(pCertContext= CertEnumCertificatesInStore(
			hCertStore,
			pCertContext))
	{
		
		if(CertGetNameStringW(
		   pCertContext,
		   CERT_NAME_EMAIL_TYPE,
		   0,
		   NULL,
		   pwszNameString,
		   dwBufLen))
		{
		   
		   if(wcscmp(pwszRFC822Name,pwszNameString)==0)
		   {
					
			   		if(CertGetNameStringW(
					   pCertContext,
					   CERT_NAME_RDN_TYPE,
					   0,
					   NULL,
					   pwszNameString,
					   dwBufLen))
					{
						
						if(wcscmp(pwszSubjectName,pwszNameString)==0)
						{
				   			if(CertGetNameStringW(
						    pCertContext,
							CERT_NAME_RDN_TYPE,
							CERT_NAME_ISSUER_FLAG,
							NULL,
							pwszNameString,
							dwBufLen))
							{
								if(wcscmp(pwszIssuerName,pwszNameString)==0)
								{

									//count ++;
									DWORD cbData;
									PBYTE pvData;

									if(!(CertGetCertificateContextProperty(
									pCertContext, 
									CERT_FRIENDLY_NAME_PROP_ID, 
									NULL, 
									&cbData)) )
									{
										 continue;
									}
									if(!(pvData = (PBYTE)malloc(cbData)))
									  {
											_ShowErrorMessage(GetLastError(), "_GetCertCount: allocation failed") ;
											return hr ;
									  }
										  
									  if(!(CertGetCertificateContextProperty(
										  pCertContext,
										  CERT_FRIENDLY_NAME_PROP_ID,
										  pvData, 
										  &cbData)))
									  {
											 _ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetCertificateContextProperty falied") ;
											return hr ;
									  }
									  else
									  {
										 WCHAR *pwszTemp = NULL;
										 pwszTemp = wcschr((WCHAR *)pvData, L'#');
										 if(pwszTemp)
										 {
											 BOOL bUsage;
											BYTE pbUsage;
											DWORD dwBytes = 1;

											//CRYPT_DATA_BLOB  Friendly_Name_Blob={256,szUsage};
											
											bUsage = CertGetIntendedKeyUsage(
												X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
												pCertContext->pCertInfo,
												&pbUsage,
												dwBytes);
											if(!bUsage)
												continue;
											/*
											if(pbUsage == CERT_DIGITAL_SIGNATURE_KEY_USAGE  )
											{
												 count ++;
											}
											*/
											switch(eType)
											{
												//CERT_DATA_ENCIPHERMENT_KEY_USAGE for EFS	
											case BOTH:
												if(pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE) || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE) )
												{
													 count ++;
												}
												break;
											case SIGN:
												if(pbUsage == CERT_DIGITAL_SIGNATURE_KEY_USAGE || pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
												{
													 count ++;
												}
												break;
											case ENCRYPT:
												if(pbUsage == CERT_KEY_ENCIPHERMENT_KEY_USAGE || pbUsage == (CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_DATA_ENCIPHERMENT_KEY_USAGE))
												{
													count ++;
												}
												break;
											} // End of Switch

											
										 }
									  }
								}
										

							}
							else
							{
									 _ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetName falied") ;
									return hr ;
							}

						}

					}
					else
					{
							 _ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetName falied") ;
							return hr ;
					}
		   }



			   
		}
		else
		{
			_ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetName falied") ;
			return hr ;
		}

	}
	if(pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
	}

	*nCount = count;
	return hr;

}

BOOL	_decode(short input, DWORD *output)
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

void _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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
	HANDLE				hToken ;

	hCurrentProcess = GetCurrentProcess() ;
	if(!OpenProcessToken( hCurrentProcess, TOKEN_QUERY|TOKEN_QUERY_SOURCE, &hToken ))
	{
		CloseHandle(hCurrentProcess);
		return NULL;
	}

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
        return(NULL) ;
    }

	CloseHandle(hCurrentProcess);
    
	return(pUserInfo->User.Sid) ;
}

void ObjecSidEncode(BYTE *pbSid, char **szMySid)
{
	/////Sid 28 byte
	char *szTemp = (char*)malloc(28*3);
	*szMySid=(char*)malloc(28*3);

	int j=0;

	char *szAscHex = (char *)malloc(3);;

	for(int i=0;i<28;i++)
	{
		if((pbSid[i]<=0x40 || pbSid[i]>0x5a) && (pbSid[i]<0x61 || pbSid[i]>0x7a)&&
			(pbSid[i]<0x30 || pbSid[i]>0x39))
		{
			//convert binary to hex representation
			szTemp[j] = '\\';
			j++;
			BytesToAscHex(&pbSid[i], 1, szAscHex);
			memcpy(&szTemp[j], szAscHex, 2);
			j += 2;
			
		}
		else
		{
			//convert binary to acsii value
			szTemp[j] = pbSid[i];
			j++;

		}
	}
	szTemp[j] = '\0';
	*szMySid = szTemp;
}

int BytesToAscHex(unsigned char* pbVal, int nValSize, char* szVal)
{

	char szDigitAscVal[] = "0123456789ABCDEF";
	char szDigit[2];

	szDigit[1] = '\0';
	for(int i=0,j = 0;i<nValSize;++i, j+=2)
	{
		szDigit[0] = szDigitAscVal[((pbVal[i] & 0xF0)>>4)];
		szVal[0] =  szDigit[0];
		szDigit[0] = szDigitAscVal[(pbVal[i] & 0x0F)];
		szVal[1] = szDigit[0];
	}
	szVal[2] = '\0';

	return 1;
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

HRESULT _GetCertSerNum(CRYPT_INTEGER_BLOB & i_SerialNumber, _bstr_t & o_bstrSerNum)
 {
	HRESULT	hr = S_OK;
	DWORD dwSerialNumber = NULL;
	PBYTE pbSerialNumber = NULL;
	TCHAR* lpSerNum = NULL;

    do
	{
		dwSerialNumber = i_SerialNumber.cbData;
	
		pbSerialNumber = (PBYTE)malloc(dwSerialNumber);
		if(pbSerialNumber==NULL)
		{
			/////return Error
		}

		// Reverse the bytes
		unsigned int i;
		for(i = 0; i < dwSerialNumber; i++)
			pbSerialNumber[dwSerialNumber-1-i] = (i_SerialNumber.pbData)[i];

		lpSerNum = (TCHAR*)malloc(dwSerialNumber*2+1);
		if(lpSerNum!=NULL)
		{
			/////return Error
		}

		for(i = 0; i < dwSerialNumber; i++)
			wsprintf(lpSerNum + i*2, "%02x", (unsigned char)pbSerialNumber[i]) ;
			
		o_bstrSerNum = lpSerNum;

	}while(0);

	if(pbSerialNumber)
		free(pbSerialNumber);
	if(lpSerNum)
		free(lpSerNum);

	return hr;
}

HRESULT _ParseDNIntoComponents(_bstr_t& i_tbstrSubjectDN, int* o_pnNumOfDNAttrs,_bstr_t** o_pptbstrDNAttrs, _bstr_t** o_pptbstrDNVals)
{

	WCHAR*			pwszTempStr;
	WCHAR           wszDelimiter='/';

	HRESULT			retVal = S_OK;
	_bstr_t			tbstrFirstDNAttr = "";
	_bstr_t			tbstrFirstDNVal = "";
	UINT			nFirstDNValLen = 0;

	if(i_tbstrSubjectDN.length() == 0)
	{
		*o_pnNumOfDNAttrs = 0;
		return S_OK;
	}

	//Copy the inputted dn into a temporary string
	pwszTempStr = (WCHAR*)new WCHAR[i_tbstrSubjectDN.length()+1];
	if(!pwszTempStr)
		retVal = E_FAIL;
	
	for(unsigned int i=0;i<i_tbstrSubjectDN.length();++i)
		pwszTempStr[i] = ((WCHAR*)(i_tbstrSubjectDN))[i];
	pwszTempStr[i] = L'\0';

	//Obtain the first component type
	WCHAR *pwszStartPtr, *pwszEndPtr, *pwszSpacePtr;
	BOOL boolDone = FALSE;
	int nState = 0;

	pwszStartPtr = pwszTempStr;
	
	do
	{
		switch(nState)
		{
		case 0:
			if(*pwszStartPtr == L' ')
				pwszStartPtr ++;
			else if(*pwszStartPtr == L'\0')
			{
				boolDone = TRUE;
				retVal = E_DNPARSEERR;
			}
			else if(*pwszStartPtr == wszDelimiter)   ////Delimitor for Exchnage DN
			{
				pwszStartPtr ++;
			}
			else
			{
				pwszEndPtr = pwszStartPtr+1;
				nState = 1;
			}

			break;

		case 1:
			if(*pwszEndPtr == L' ')
			{
				*pwszEndPtr = '\0';
				pwszEndPtr++;
			}
			else if(*pwszEndPtr == L'=')
			{
				*pwszEndPtr = '\0';
				boolDone = TRUE;
			}
		
			else if(*pwszEndPtr == L'\0')
			{
				boolDone = TRUE;
				retVal = E_DNPARSEERR;
			}
			else
			{
				pwszEndPtr++;
			}
			break;

		}
	}while(!boolDone);

	if(retVal == S_OK)
	{
		tbstrFirstDNAttr = pwszStartPtr;
		pwszStartPtr = ++pwszEndPtr;
		pwszSpacePtr = pwszEndPtr;
		boolDone = FALSE;
		nState = 0;

		do
		{
			//Now obtain the first component value
			switch(nState)
			{
			case 0:
				if(*pwszStartPtr == L' ')
					pwszStartPtr ++;
				else if(*pwszStartPtr == L'\0')
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else if(*pwszStartPtr == L'\"')
				{
					pwszEndPtr = pwszStartPtr+1;
					nState = 2;
				}
				else if(*pwszStartPtr == L'<')		// Parsing out "<>" if present
				{
					pwszStartPtr ++;
					nState = 3;
				}
				else if(*pwszStartPtr == L'#')		 // we do not support non-printable strings yet
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else
				{
					pwszEndPtr = pwszStartPtr+1;
					nState = 1;
				}
				break;

			case 1:
				if(*pwszEndPtr == L' ')
				{
					pwszEndPtr++;
					
				}
				else if(*pwszEndPtr == wszDelimiter)   ////Delimitor for Exchnage DN
				{
					*pwszSpacePtr = '\0';
					pwszEndPtr++;
					boolDone = TRUE;
				}
				else if(*pwszEndPtr == L'\0')
				{
					boolDone = TRUE;
					pwszSpacePtr = '\0';
				}
				else if(*pwszEndPtr == L'\"')
				{
					pwszEndPtr++;
					nState = 2;
				}
				else
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
				}
				break;

			case 2:
				if(*pwszEndPtr == L'\"')
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
					nState = 1;
				}
				else
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
				}
				break;

			case 3:
				if(*pwszStartPtr == L'>')
				{
					pwszStartPtr ++;
					nState = 0;
				}
				else if(*pwszStartPtr == L'\0')
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else
					pwszStartPtr ++;
				break;

			}
		}while(!boolDone);
	}

	if(retVal == S_OK)
	{
		WCHAR wcTemp[2];
		wcTemp[0] = '\0';
		nFirstDNValLen = wcslen(pwszStartPtr);
		UINT i = 0;

		// Strip out the quotes from the beginning and end of the string if any. Also if two
		// consecutive quotes are present keep only one because that is the way 'MyCertNameTStr()'
		// has created it
		if(pwszStartPtr[i] == L'"')
		{
			i++;
			nFirstDNValLen--;
		}
		
		for(; i < nFirstDNValLen; i++)
		{
			if(wcTemp[0] == L'"' && pwszStartPtr[i] == L'"')
			{
				wcTemp[0] = '\0';
				continue;
			}

			wcTemp[0] = pwszStartPtr[i];
			wcTemp[1] = '\0';

			tbstrFirstDNVal += wcTemp;
		}

		//Obtain the remaining components
		_bstr_t tbstrRemainingDN = "";
		_bstr_t* ptbstrRemainingAttrs = NULL;
		_bstr_t* ptbstrRemainingVals = NULL;
		int nRemainingAttrs = 0;

		tbstrRemainingDN = pwszEndPtr;
		retVal = _ParseDNIntoComponents(tbstrRemainingDN, &nRemainingAttrs, &ptbstrRemainingAttrs,
			&ptbstrRemainingVals);
		if(retVal == S_OK)
		{
			//Allocate space for all the attributes and values
			*o_pnNumOfDNAttrs = nRemainingAttrs + 1;
			*o_pptbstrDNAttrs = (_bstr_t*) new _bstr_t[*o_pnNumOfDNAttrs];
			*o_pptbstrDNVals = (_bstr_t*) new _bstr_t[*o_pnNumOfDNAttrs];

			//Save all the attributes and values
			(*o_pptbstrDNAttrs)[0] = tbstrFirstDNAttr;
			(*o_pptbstrDNVals)[0] = tbstrFirstDNVal;

			for(int i=0;i<nRemainingAttrs;++i)
			{
				(*o_pptbstrDNAttrs)[i+1] = ptbstrRemainingAttrs[i];
				(*o_pptbstrDNVals)[i+1] = ptbstrRemainingVals[i];
			}
			delete[] ptbstrRemainingAttrs;
			delete[] ptbstrRemainingVals;
		}

	}

	delete[] pwszTempStr;
	return retVal;
	
}


#ifdef	_VS_LOG_MSG_
int VSGSE_Log(BOOL bFileExist,wchar_t *format,	...)
{
	BOOL    bRet;
	DWORD   m_err=0;

	FILE *fp = NULL;
	char szBuffer[2048],szLogFileName[2048];
	char *lptoken=NULL;
    char totalBuffer[1024];
	char timeBuffer[32];
    time_t currentTime;

	va_list ap;

	if(!bFileExist)
	{

		GetWindowsDirectory(szBuffer,MAXLEN);
		lptoken=strtok(szBuffer,":");
		lstrcpy(szLogFileName,lptoken);
		lstrcat(szLogFileName,":\\temp");
		bRet=CreateDirectory(szLogFileName,NULL);
		m_err=GetLastError();
		lstrcat(szLogFileName,"\\VeriSign");
		bRet=CreateDirectory(szLogFileName,NULL);
		lstrcat(szLogFileName,"\\GSE");
		bRet=CreateDirectory(szLogFileName,NULL);
		lstrcat(szLogFileName,"\\vsgse.log");

	}

	va_start(ap, format);
	fp=fopen(szLogFileName,"a+");
	time (&currentTime);
    strftime (timeBuffer,32,"%m/%d/%Y %H:%M:%S ", 
        	   localtime ((const time_t *) &currentTime));

    sprintf (totalBuffer, "%s",timeBuffer);
	fprintf(fp, totalBuffer);

	vfwprintf(fp, format, ap);
	va_end(ap);

	fprintf(fp, "\n");
    fflush(fp);
	fclose(fp);

	return 0;
}

void ShowErrorMsg(DWORD errorCode, LPSTR szExtraString)
{
	LPVOID		ErrorMessage ;
	DWORD       nRetVal;
	HRESULT     hr;

	nRetVal=FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			(LPCVOID) NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &ErrorMessage,
			0,
			NULL);

	// Display the string.
	CHAR	temp[1024], temp2[1024] ;
	sprintf(temp, "Mapi::%s", szExtraString) ;
	sprintf(temp2, "%sError Code : 0x%08x", ErrorMessage, errorCode) ;

	::MessageBox( NULL, (LPCTSTR) temp2, (LPCTSTR) _T(temp), MB_OK | MB_ICONINFORMATION );


	// Copy Error Information in the 
	hr = HRESULT_FROM_WIN32(errorCode) ;


	LocalFree( ErrorMessage ) ;
}
#endif
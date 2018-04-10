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

#include "util.h"

#include <winldap.h>

#if LDAP_UNICODE
#undef LDAP_UNICODE
#endif 



#if LDAP_UNICODE
#define LDAPMod LDAPModW
#define PLDAPMod PLDAPModW
#define ldap_open ldap_openW
#else
#define LDAPMod LDAPModA
#define PLDAPMod PLDAPModA
#define ldap_open ldap_openA
#endif


CHAR	szErrorString[1024] ;
HANDLE	hToken ;

extern PCHAR szUserDN;

void
PrintUsage(
    void
    )
{
    printf("\nUsage: dssrch /b <baseObject> /f <search_filter> [/f <attrlist>] [/p <preference>=value>] ");
    printf(" [/u <UserName> <Password>] [/t <flagName>=<value> \n");
    printf("\n   where:\n" );
    printf("   baseObject     = ADsPath of the base of the search\n");
    printf("   search_filter  = search filter string in LDAP format\n" );
    printf("   attrlist       = list of the attributes to display\n" );
    printf("   preference could be one of:\n");
    printf("   Asynchronous, AttrTypesOnly, DerefAliases, SizeLimit, TimeLimit,\n");
    printf("   TimeOut, PageSize, SearchScope, SortOn, CacheResults\n");
    printf("   flagName could be one of:\n");
    printf("   SecureAuth or UseEncrypt\n");
    printf("   value is yes/no for a Boolean and the respective integer for integers\n");
    printf("   scope is one of \"Base\", \"OneLevel\", or \"Subtree\"\n");

    printf("\nFor Example: dssrch /b NDS://ntmarst/ms /f \"(object Class=*)\" ");
    printf(" /a  \"ADsPath, name, description\" /p searchScope=onelevel /p searchscope=onelevel\n\n OR \n");

    printf("\n dssrch /b \"LDAP://O=Internet/DC=COM/");
    printf("DC=MICROSOFT/DC=NTDEV\"  /f \"(objectClass=*)\"  /a \"ADsPath, name, usnchanged\" ");
    printf(" /u \"CN=NTDS,CN=Users,DC=NTDEV,DC=MICROSOFT,DC=COM,O=INTERNET\" \"\" ");
    printf("/p searchScope=onelevel /t secureauth=yes /p SortOn=name /p CacheResults=no\n");

}




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

void _ShowErrorMessage(DWORD errorCode)
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
	CHAR	temp2[1024] ;

	sprintf(temp2, "%sError Code : 0x%08x", ErrorMessage, errorCode) ;

#ifdef _DEBUG
	printf("%s\n", temp2) ;
#endif

	LocalFree( ErrorMessage ) ;
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
		_ShowErrorMessage(GetLastError()) ;
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
		_ShowErrorMessage(GetLastError()) ;
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
		_ShowErrorMessage(GetLastError()) ;
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
		_ShowErrorMessage(GetLastError()) ;
		return(NULL) ;
	}

	return szmbOutputString ;
}

LPVOID AllocateTokenInfoBuffer(
    HANDLE hToken,
    TOKEN_INFORMATION_CLASS InfoClass,
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


PCHAR	GetAccountName(PSID pMySID)
{
	BSTR		bstrName = NULL, bstrDomain = NULL, bstrFull = NULL ;
	bstrName = (BSTR) malloc(1024) ;
	bstrDomain = (BSTR) malloc(1024) ;
	//bstrFull = (BSTR) malloc(2048) ;


	DWORD		dwName = 512, dwDomain = 512 ;
	SID_NAME_USE sidNameUse ;

	if ( !LookupAccountSid(
				NULL,
				pMySID,
				(unsigned short *)bstrName,
				&dwName,
				(unsigned short *)bstrDomain,
				&dwDomain,
				&sidNameUse) )
	{
		printf("error man!!!") ;
	}

	PCHAR	szName = _WideToMultiString(bstrName) ;
	PCHAR	szDomain = _WideToMultiString(bstrDomain) ;
	PCHAR	szFull = (PCHAR)malloc(2048) ;

	strcpy(szFull, szDomain) ;
	strcat(szFull, "\\") ;
	strcat(szFull, szName) ;

	if(bstrName!=NULL)
		  free(bstrName);

	if(bstrDomain!=NULL)
		  free(bstrDomain);


	if(szName!=NULL)
			free(szName) ;
	if(szDomain!=NULL)
			free(szDomain) ;


	return szFull ;
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
	
	return(pUserInfo->User.Sid);
}


void MyErrorHandler(PCHAR szFDFfile, DWORD dwErrorCode, DWORD dwWinErrorCode, PCHAR szOperation)
{
	sprintf(szErrorString, "<HTML>\n") ;

	sprintf(szErrorString, "%s<HEAD>\n", szErrorString) ;

	sprintf(szErrorString, "%s<SCRIPT Language=JavaScript>\n", szErrorString) ;
	sprintf(szErrorString, "%s<!--\n", szErrorString) ;

	sprintf(szErrorString, "%s  self.location=\"../softbounce.exe?", szErrorString) ;
	sprintf(szErrorString, "%sform_file=%s&", szErrorString, szFDFfile) ;
	sprintf(szErrorString, "%serrorCode=%08x&", szErrorString, dwErrorCode) ;
	sprintf(szErrorString, "%swinerrorcode=%08x&", szErrorString, dwWinErrorCode) ;
	sprintf(szErrorString, "%soperation=%s&", szErrorString, szOperation) ;
	sprintf(szErrorString, "%sshowError=\" ;\n", szErrorString) ;

	sprintf(szErrorString, "%s-->\n", szErrorString) ;
	sprintf(szErrorString, "%s</SCRIPT>\n", szErrorString) ;

	sprintf(szErrorString, "%s</HEAD>\n", szErrorString) ;

	sprintf(szErrorString, "%s<BODY>\n", szErrorString) ;
	sprintf(szErrorString, "%s</BODY>\n", szErrorString) ;
	sprintf(szErrorString, "%s</HTML>\n", szErrorString) ;
}

BOOL StuffExchange_55(PCHAR szExchangeServerName,
						PCHAR szBaseDN,
						PCHAR szUserCertificate,
						PCHAR szUserSMIMECertificate,
						BOOL bUse_AuthUpdate)
{

	LDAP *ld = NULL;
	DWORD dwError = 0;
	LDAPMod		mod[2];
	LDAPMod		*mods[2];
	char		*userCertificateVals[2];
	char		*userSMIMECertificateVals[2];
	HRESULT hr = NULL;


	/*
		Open the LDAP session
		Bind using either simple bind secure bind depending on bUse_AuthUpdate 
		Update the entries.
		Return TRUE or FALSE based on the results from any of the above operations.
	*/

	ld = ldap_open(szExchangeServerName, LDAP_PORT);

	if(ld == NULL) 
	{
		dwError = GetLastError();
		hr = HRESULT_FROM_WIN32(dwError);
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000009, hr, "Exchange Populate Status : Stuff Exchange") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}


	if(!bUse_AuthUpdate) // secure bind
	{
		
		dwError = ldap_bind_sA(	ld,
								NULL,
								NULL,
								LDAP_AUTH_NTLM );
	
		
		if(dwError != LDAP_SUCCESS) 
		{
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000009, dwError, "Exchange Populate Status : Stuff Exchange") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}

	}
	else // simple bind
	{
		dwError =  ldap_simple_bind_sA(	ld,
										NULL,
										NULL);
		if(dwError != LDAP_SUCCESS) 
		{
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000009, dwError, "Exchange Populate Status : Stuff Exchange") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}
	}


	/* list of modifications to be made */
	mod[0].mod_op = LDAP_MOD_REPLACE;
	mod[0].mod_type = "userCertificate";
	userCertificateVals[0] = szUserCertificate;
	userCertificateVals[1] = NULL;
	mod[0].mod_values = userCertificateVals;
	mods[0] = &mod[0];
	mods[1] = NULL;

	dwError = ldap_modify_sA(ld,
							szBaseDN,
							mods );

	if(dwError != LDAP_SUCCESS)
	{
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x0000000B, dwError, "Exchange Populate Status : User Certificate") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}


	mod[1].mod_op = LDAP_MOD_REPLACE;
	mod[1].mod_type = "userSMIMECertificate";
	userSMIMECertificateVals[0] = szUserSMIMECertificate;
	userSMIMECertificateVals[1] = NULL;
	mod[1].mod_values = userSMIMECertificateVals;

	mods[0] = &mod[1];
	mods[1] = NULL;

	dwError = ldap_modify_sA(ld,
							szBaseDN,
							mods );
	if(dwError != LDAP_SUCCESS)
	{
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x0000000C, dwError, "Exchange Populate Status : User S/MIME Attributes") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}
	
	return TRUE;
}



BOOL StuffExchange_Win2k(PCHAR szExchangeServerName,
						PCHAR szBaseDN,
						PCHAR szUserCertificate,
						PCHAR szUserSMIMECertificate,
						BOOL bUse_AuthUpdate)
{

	LDAP *ld = NULL;
	DWORD dwError = 0;
	LDAPMod		mod[2];
	LDAPMod		*mods[2];
	char		*userCertificateVals;
	char		*userSMIMECertificateVals;
	HRESULT hr = NULL;
	int nUserCertificate = 0;
	int nUserSMIMECertificate = 0;
	LDAP_BERVAL *BerValUserCert[2];
	LDAP_BERVAL *BerValSMIMECert[2];


	/*
		Open the LDAP session
		Bind using either simple bind secure bind depending on bUse_AuthUpdate 
		Update the entries.
		Return TRUE or FALSE based on the results from any of the above operations.
	*/

	ld = ldap_open(szExchangeServerName, LDAP_PORT);

	if(ld == NULL) 
	{
		dwError = GetLastError();
		hr = HRESULT_FROM_WIN32(dwError);
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000009, hr, "Exchange Populate Status : Stuff Exchange: ldapopen") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}

	if(!bUse_AuthUpdate) // secure bind
	{
		dwError = ldap_bind_sA(	ld,
								NULL,
								NULL,
							LDAP_AUTH_NTLM );
/*
		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf ("AFTER ldap_bind_sA ,SUCCESSFULL\n");
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return FALSE;
*/
	
		
		if(dwError != LDAP_SUCCESS) 
		{
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000009, dwError, "Exchange Populate Status : Stuff Exchange: ldapbind") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}
	}
	else // simple bind
	{
		dwError =  ldap_simple_bind_sA(	ld,
										NULL,
										NULL);
		if(dwError != LDAP_SUCCESS) 
		{
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000009, dwError, "Exchange Populate Status : Stuff Exchange: ldapsimplebind") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}
	}



	/* list of modifications to be made */
	mod[0].mod_op = LDAP_MOD_REPLACE | LDAP_MOD_BVALUES;
	mod[0].mod_type = "userCertificate";

	Hascii2Bin(szUserCertificate, &userCertificateVals, &nUserCertificate);

	BerValUserCert[0] = (struct berval *)malloc(sizeof(struct berval));
	BerValUserCert[0]->bv_len = nUserCertificate;
    BerValUserCert[0]->bv_val = userCertificateVals;
	BerValUserCert[1] = NULL;

	mod[0].mod_values = NULL;
	mod[0].mod_vals.modv_bvals  = BerValUserCert;
	mods[0] = &mod[0];
	mods[1] = NULL;

	dwError = ldap_modify_sA(ld,
							szBaseDN,
							mods );
	if(dwError != LDAP_SUCCESS)
	{
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x0000000B, dwError, "Exchange Populate Status : User Certificate") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}

	mod[1].mod_op = LDAP_MOD_REPLACE | LDAP_MOD_BVALUES;
	mod[1].mod_type = "userSMIMECertificate";
	Hascii2Bin(szUserSMIMECertificate, &userSMIMECertificateVals, &nUserSMIMECertificate);

	BerValSMIMECert[0] = (struct berval *)malloc(sizeof(struct berval));
	BerValSMIMECert[0]->bv_len = nUserSMIMECertificate;
    BerValSMIMECert[0]->bv_val = userSMIMECertificateVals;
	BerValSMIMECert[1] = NULL;

	mod[1].mod_values = NULL;
	mod[1].mod_vals.modv_bvals  = BerValSMIMECert;
	mods[0] = &mod[1];
	mods[1] = NULL;

	dwError = ldap_modify_sA(ld,
							szBaseDN,
							mods );

	if(dwError != LDAP_SUCCESS)
	{
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x0000000C, dwError, "Exchange Populate Status : User S/MIME Attributes") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}

	if(BerValSMIMECert[0])
		free(BerValSMIMECert[0]);
	if(BerValUserCert[0])
		free(BerValUserCert[0]);
	if(userSMIMECertificateVals)
		free(userSMIMECertificateVals);
	if(userCertificateVals)
		free(userCertificateVals);

	
	return TRUE;

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


AuthData* getAuthData()
{
	AuthData *pAuthSessionData;
	DWORD dwError;
	HRESULT hr;

	pAuthSessionData = (AuthData *)malloc(sizeof(AuthData));

	if( !DeleteRecords())
	{
		
		dwError = GetLastError();
		hr = HRESULT_FROM_WIN32(dwError);
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate Get Authenticated Data : Delete AuthRecords") ;
		printf("%s", szErrorString) ;
		return NULL ;
	}


	if ( (dwError = CreateAuthRecord(pAuthSessionData)) != 0)
	{
		
		//dwError = GetLastError();
		hr = HRESULT_FROM_WIN32(dwError);
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate Get Authenticated Data : Create AuthRecord") ;
		printf("%s", szErrorString) ;
		return NULL ;
	}


	return pAuthSessionData;


}


BOOL verifyChallenge(BYTE *pbSessionID, BYTE *pbData)
{
	
	AuthData AuthSessionData;
	int nReturn;
	DWORD dwError;
	HRESULT hr;
	//BOOL found = FALSE;

	
	nReturn = ReadAuthRecord(pbSessionID, &AuthSessionData);
	if(nReturn == 0)
	{
		// report Record Not found for the Session ID
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate Verify Challenge : Read AuthRecord") ;
		printf("%s", szErrorString) ;
		return FALSE ;
	}
	else if (nReturn == -1)
	{
		dwError = GetLastError();
		hr = HRESULT_FROM_WIN32(dwError);
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate Verify Challenge : Read AuthRecord") ;
		printf("%s", szErrorString) ;
		return FALSE ;

	}
		
	if(memcmp(pbData, AuthSessionData.pbData, CHALLENGE_LEN) == 0)
	{

		if (!SetStateAndDate(VERIFIED, &AuthSessionData))
		{
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000033, 0, "ServerUpdate Verify Challenge : Authenticated Update Timed Out");
			printf("%s", szErrorString) ;
			return FALSE;
		}

		nReturn = WriteAuthRecord(pbSessionID, AuthSessionData);
		if(nReturn == 0)
		{
			// Report Error - Writing Record Failed
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate Verify Challenge : Write AuthRecord") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}
		else if(nReturn == -1)
		{
			dwError = GetLastError();
			hr = HRESULT_FROM_WIN32(dwError);
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate Verify Challenge : Write AuthRecord") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}


		return TRUE;
	}
	return FALSE;


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

/*
DWORD getRandomString(BYTE *pbData, int len)
{
	HCRYPTPROV   hCryptProv = NULL;
	DWORD		 dwSessionId = 0;
	BYTE		*pbRandom = NULL;
	DWORD		dwLen = 0;
	DWORD dwError = 0 ;
	
	//--------------------------------------------------------------------
	//  Acquire a CSP context.

	if(! CryptAcquireContext(    
	   &hCryptProv,
	   L"TEST",
	   NULL,
	   PROV_RSA_FULL,
	   CRYPT_MACHINE_KEYSET)) 
	{
		if(! CryptAcquireContext(    
		&hCryptProv,
		L"TEST",
		NULL,
		PROV_RSA_FULL,
		CRYPT_MACHINE_KEYSET|CRYPT_NEWKEYSET))
		{

			dwError = GetLastError();
			return GetLastError();
		}
	}
	

	pbRandom = (BYTE *)malloc(len);

	if(pbRandom == NULL)
	{
			
		 return GetLastError();
	}

	// Generate a random initialization vector.
	if(! CryptGenRandom(
	   hCryptProv, 
	   len, 
	   pbRandom)) 
	{
	
		return GetLastError();
	}
	

	Base64Encode((PCHAR)pbRandom, len, (PCHAR)pbData, &dwLen);

	//memset(pbData,'A',len);
	pbData[len] = '\0';


	if(hCryptProv)
	{
		CryptReleaseContext(hCryptProv, 0);
	}
	

	if(pbRandom)
		free(pbRandom);
	return 0;
}



void Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD *dwOutputSize)
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
*/

// Covert SYSTEMTIME to String

void FormatDate(SYSTEMTIME stTime, char* szFormatDate)
{
	
	char *DayofWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

	PBYTE pbTime = (BYTE *)&stTime;

	int nLen = sizeof(SYSTEMTIME);
	WORD wTemp;
	PBYTE pbTemp = pbTime;
	int count = 1;
	WORD wDayofWeek;

	while(pbTime < (pbTemp + nLen ))
	{
		if(count == 3)
		{
			// DayofWeek to be printed at the end
			wDayofWeek = *(WORD*)(pbTime);
			pbTime += sizeof(WORD);
			
		}
		else if(count == 8)
		{
			// skipping milliseconds field.
			pbTime += sizeof(WORD);
		}
		else
		{
			
			if((*(WORD*)(pbTime))  <= 9)
				*szFormatDate++ = '0';
			wTemp = *(WORD*)(pbTime);
			itoa(wTemp, szFormatDate, 10);
			szFormatDate += strlen(szFormatDate);
			*szFormatDate++  = ':';
			pbTime += sizeof(WORD);
		}
		
		count ++;
	}
	//print DayofWeek 
	memcpy(szFormatDate, DayofWeek[wDayofWeek], 3);
	szFormatDate += strlen(DayofWeek[wDayofWeek]);


	*szFormatDate = '\0';
	
}

// Convert String to SystemTime

void DecodeStringToSystemTime(char *szFormatString, SYSTEMTIME *stTimeOut)
{
	PBYTE pbTime = (PBYTE) stTimeOut;
	WORD wElement;
	char *szToken = NULL;
	char *szSep = ":";
	int count = 1;
	char *DayofWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	char *szTemp = NULL;

	stTimeOut->wMilliseconds = 0; // This value is not used right now.

	szTemp = (char *)malloc(strlen(szFormatString) + 1);
	strcpy(szTemp, szFormatString);

	szToken = strtok(szTemp, szSep);
	
	
	while(szToken != NULL)
	{
		
    	wElement = atoi(szToken);

		// This is for DayofWeek: for example "Sun" 
		// break out of the loop and assign the proper value. 
		if(count == 7)
		{
			break;
		}

		// if DayofWeek skip
		if(count == 3)
			pbTime += sizeof(WORD);

		memcpy(pbTime, &wElement, sizeof(WORD));

		pbTime += sizeof(WORD);
		szToken = strtok( NULL, szSep );
		count ++ ;

	}
	int i = 0;
	while( DayofWeek[i])
	{
		if(strcmp(DayofWeek[i], szToken) == 0)
		{
			stTimeOut->wDayOfWeek = i;
			break;
		}
		i++ ;
	}
	if(szTemp)
		free(szTemp);
	
}

int DiffTimeInSeconds(SYSTEMTIME st1, SYSTEMTIME st2)
{
	FILETIME ft1;
	FILETIME ft2;

	SystemTimeToFileTime(&st1, &ft1);
	SystemTimeToFileTime(&st2, &ft2);

	_int64 n64FirstTime =  (*(_int64*)(&ft1));
	_int64 n64SecondTime =  (*(_int64*)(&ft2));
	_int64 n64TheDiff = n64FirstTime - n64SecondTime;

	// Difference in Seconds
	int nDiffMinutes = (int)(n64TheDiff/(10000000));
	return nDiffMinutes;
}


BOOL AuthenticateChallenge(char *szUserSMIMECertificate, char *szChallengePhrase, char *szSessionID)
{
		CRYPT_VERIFY_MESSAGE_PARA VerifyParams;
		char		*userSMIMECertificate;
		int nSMIMECertificate = 0;
		DWORD cbDecodedMessageBlob;
		BYTE  *pbDecodedMessageBlob = NULL;

		HRESULT hr;
		DWORD dwError;

		// Convert from Half Ascii to bin
		Hascii2Bin(szUserSMIMECertificate, &userSMIMECertificate, &nSMIMECertificate);

	
		//--------------------------------------------------------------------
		//  Initialize the VerifyParams data structure.

		VerifyParams.cbSize = sizeof(CRYPT_VERIFY_MESSAGE_PARA);
		VerifyParams.dwMsgAndCertEncodingType = PKCS_7_ASN_ENCODING | X509_ASN_ENCODING;
		VerifyParams.hCryptProv = 0;
		VerifyParams.pfnGetSignerCertificate = NULL;
		VerifyParams.pvGetArg = NULL;

		//--------------------------------------------------------------------
		//   With two calls to CryptVerifyMessageSignature, verify and decode
		//   the signed message.
		//   First, call CryptVerifyMessageSignature to get the length of the 
		//   buffer needed to hold the decoded message.

		if(!CryptVerifyMessageSignature(
			&VerifyParams,           // Verify parameters.
			0,                       // Signer index.
			(BYTE*)userSMIMECertificate, // Pointer to signed blob.
			nSMIMECertificate,	// Size of signed blob.
			NULL,                    // Buffer for decoded message.
			&cbDecodedMessageBlob,                    // Size of buffer.
			NULL))                   // Pointer to signer certificate.
		{
			// BUG BUG - new error page needed
			dwError = GetLastError();
			hr = HRESULT_FROM_WIN32(dwError);
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000034, hr, "Exchange Authenticate Challenge : CryptVerifyMessageSignature") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}

		//--------------------------------------------------------------------
		//   Allocate memory for the buffer.

		if(!(pbDecodedMessageBlob = 
		   (BYTE*)malloc(cbDecodedMessageBlob)))
		{
			_ShowErrorMessage(GetLastError()) ;
			return(NULL) ;
		}

		//--------------------------------------------------------------------
		//  Call CryptVerifyMessageSignature again to copy the message into
		//  the buffer.

		if(!CryptVerifyMessageSignature(
			&VerifyParams,           // Verify parameters.
			0,                       // Signer index.
			(BYTE*)userSMIMECertificate,// Pointer to signed blob.
			nSMIMECertificate,			// Size of signed blob
			pbDecodedMessageBlob,    // Buffer for decoded message.
			&cbDecodedMessageBlob,   // Size of buffer.
			NULL))                   // Pointer to signer certificate.
		{
			// BUG BUG - new error page needed
			dwError = GetLastError();
			hr = HRESULT_FROM_WIN32(dwError);
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000034, hr, "Exchange Authenticate Challenge : CryptVerifyMessageSignature") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}

		CHAR		szStringSigned[512];
		PCHAR szHostName = getenv("HTTP_HOST");

		strcpy(szStringSigned, szHostName);
		strcat(szStringSigned, szChallengePhrase);
		strcat(szStringSigned, PRECANNED_HEADER);

		//if(memcmp(szChallengePhrase, pbDecodedMessageBlob, strlen(szChallengePhrase) ) != 0)
		if(memcmp(szStringSigned, pbDecodedMessageBlob, cbDecodedMessageBlob ) != 0)
		{
			// BUG BUG added error page here.
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000032, 0, "ServerUpdate Authenticate Challenge : Challenge Phrase mismatch") ;
			printf("%s", szErrorString) ;
			return FALSE ;
		}
		else
		{
			
			// authenticated - log the date and state.
			AuthData AuthSessionData;
			int nReturn;


			nReturn = ReadAuthRecord((PBYTE)szSessionID, &AuthSessionData);
			if(nReturn == 0)
			{
				// report Record Not found for the Session ID
				MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate Authenticate Challenge : Read AuthRecord") ;
				printf("%s", szErrorString) ;
				return FALSE ;
			}
			else if (nReturn == -1)
			{
				dwError = GetLastError();
				hr = HRESULT_FROM_WIN32(dwError);
				MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate Authenticate Challenge : Read AuthRecord") ;
				printf("%s", szErrorString) ;
				return FALSE ;

			}


			if(!SetStateAndDate(AUTHENTICATED, &AuthSessionData))
			{
				MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000033, 0, "ServerUpdate Authenticate Challenge : Authenticated Update Timed Out") ;
				printf("%s", szErrorString) ;
				return FALSE;
			}

			nReturn = WriteAuthRecord((PBYTE)szSessionID, AuthSessionData);
			if(nReturn == 0)
			{
				// Report Error - Writing Record Failed
				MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate Authenticate Challenge : Write AuthRecord") ;
				printf("%s", szErrorString) ;
				return FALSE ;
			}
			else if(nReturn == -1)
			{
				dwError = GetLastError();
				hr = HRESULT_FROM_WIN32(dwError);
				MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate Authenticate Challenge : Write AuthRecord") ;
				printf("%s", szErrorString) ;
				return FALSE ;
			}

 
		}

		// This code is repeated twice - need to figure out a way for returning errors.
		if(pbDecodedMessageBlob)
		{
			free(pbDecodedMessageBlob);
		}
		return TRUE;
}

DWORD CreateAuthRecord(AuthData *pAuthSessionData)
{
	FILE *stream;
	
	BYTE         pbData[256];
	int i;
	DWORD dwError = 0;


	HANDLE hMutex; 
	SYSTEMTIME stTime;
	SYSTEMTIME stLocalTime;

	// Create a mutex with no initial owner.

	hMutex = CreateMutexA( 
		NULL,                       // no security attributes
		FALSE,                      // initially not owned
		"MutexToProtectDatabase");  // name of mutex

	if (hMutex == NULL) 
	{
		
		return GetLastError();
	}
	
	WaitForSingleObject( 
        hMutex,   
        INFINITE);   


	if( (stream = fopen("flatfile", "a+")) == NULL)
	{
		dwError = GetLastError();
		goto Error;
	}

	// Get Session ID
	getRandomString(pbData, SESSIONID_LEN);
	memcpy(pAuthSessionData->pbSessionId, &pbData[0], SESSIONID_LEN + 1);
	

	// Get Challenge Phrase
	getRandomString(pbData, CHALLENGE_LEN);
	memcpy(pAuthSessionData->pbData, &pbData[0], CHALLENGE_LEN + 1);


	//pAuthSessionData->state = SENT;
	itoa(SENT, pAuthSessionData->state, 10);
	GetSystemTime(&stTime);
	SystemTimeToTzSpecificLocalTime(NULL, &stTime, &stLocalTime );
	FormatDate( stLocalTime, pAuthSessionData->Time);

	memset(pAuthSessionData->pbName,'0',NAME_LEN);
	for( i=0; i < NAME_LEN - 1; i++)
	{
		if(szUserDN[i+3] == ',')
			break;
		//don't copy space
		if(szUserDN[i+3] != ' ')
			pAuthSessionData->pbName[i] = szUserDN[i+3];
	}
	//memcpy(pAuthSessionData->pbName, "Ajay", 4);
	pAuthSessionData->pbName[NAME_LEN - 1] = '\0';

	fprintf(stream,"%s %s %s %s %s\n",pAuthSessionData->pbName,pAuthSessionData->pbSessionId,pAuthSessionData->pbData,pAuthSessionData->state,pAuthSessionData->Time);

	fclose(stream);
	if (! ReleaseMutex(hMutex))
	{ 
		return GetLastError();
	}
	return 0;
Error:
	if(stream)
		fclose(stream);
	ReleaseMutex(hMutex);
	return dwError;

}

// Return Value
// -1 - One of the windows API failed.
// 1 - Success
// 0 - Seesion ID not found 
int ReadAuthRecord(BYTE *pbSessionID, AuthData* Data)
{
	FILE* stream;
	AuthData AuthSessionData;
	HANDLE hMutex;

	
	// Create a mutex with no initial owner.

	hMutex = CreateMutexA( 
		NULL,                       // no security attributes
		FALSE,                      // initially not owned
		"MutexToProtectDatabase");  // name of mutex

	if (hMutex == NULL) 
	{
		return -1;
	}
	
	WaitForSingleObject( 
        hMutex,   
        INFINITE);  

	
	if ( (stream = fopen("flatfile", "r+")) == NULL)
	{
		ReleaseMutex(hMutex);
		return -1;
	
	}

	while(!feof( stream ) )
	{
		
		fscanf(stream, "%s %s %s %s %s\n",AuthSessionData.pbName,AuthSessionData.pbSessionId, AuthSessionData.pbData, AuthSessionData.state, AuthSessionData.Time);

		if(memcmp(AuthSessionData.pbSessionId, pbSessionID, SESSIONID_LEN ) == 0)
		{
			memcpy(Data, &AuthSessionData, sizeof(AuthData));
			fclose(stream);
			ReleaseMutex(hMutex);
			return TRUE;
			
		}
	}  // end while

	fclose(stream);
	if (! ReleaseMutex(hMutex))
	{ 
          // Deal with error
		return -1;
	}
	return FALSE;
}

// Return Value
// -1 - One of the windows API failed.
// 1 - Success
// 0 - Seesion ID not found
int WriteAuthRecord(BYTE *pbSessionID, AuthData Data)
{

	FILE* stream = NULL;
	AuthData AuthSessionData;
	HANDLE hMutex;
	BOOL found = FALSE;
	long noffset = sizeof(AuthData);

	// Create a mutex with no initial owner.

	hMutex = CreateMutexA( 
		NULL,                       // no security attributes
		FALSE,                      // initially not owned
		"MutexToProtectDatabase");  // name of mutex

	if (hMutex == NULL) 
	{
		return -1;
	}
	
	WaitForSingleObject( 
        hMutex,   
        INFINITE); 

	
	if( (stream = fopen("flatfile", "r+")) == NULL)
	{
		ReleaseMutex(hMutex);
		return -1;
	}

	while(!feof( stream ) )
	{
		
		fscanf(stream, "%s %s %s %s %s\n",AuthSessionData.pbName,AuthSessionData.pbSessionId, AuthSessionData.pbData, AuthSessionData.state, AuthSessionData.Time);

		if(memcmp(pbSessionID, AuthSessionData.pbSessionId, SESSIONID_LEN) == 0)
		{			
			fseek(stream, -(noffset+1), SEEK_CUR); 
			fprintf(stream, "%s %s %s %s %s\n",Data.pbName, Data.pbSessionId, Data.pbData, Data.state, Data.Time);
			fclose(stream);
			ReleaseMutex(hMutex);
			return TRUE;
		}
		
		
	}  // end while



	fclose(stream);
	if (! ReleaseMutex(hMutex))
	{ 
          return -1;
	}
	return FALSE;

}

BOOL DeleteRecords()
{
	FILE *stream = NULL;
	HANDLE hMutex;

	DWORD dwRecords = 0;
	long noffset = sizeof(AuthData);
	DWORD dwBytes = 0;
	
	// Create a mutex with no initial owner.

	hMutex = CreateMutexA( 
		NULL,                       // no security attributes
		FALSE,                      // initially not owned
		"MutexToProtectDatabase");  // name of mutex

	if (hMutex == NULL) 
	{
		return FALSE;
	}
	
	WaitForSingleObject( 
        hMutex,   
        INFINITE); 

	
	if( (stream = fopen("flatfile", "r+")) == NULL)
	{
		// Create if it doesn't exist
		if((stream = fopen("flatfile", "a+")) == NULL)
		{
			ReleaseMutex(hMutex);
			return FALSE;
		}
	}

	/*
	while(!feof(stream))
	{
		fscanf(stream, "%s %s %s %s %s\n",AuthSessionData.pbName,AuthSessionData.pbSessionId, AuthSessionData.pbData, AuthSessionData.state, AuthSessionData.Time);
		dwRecords ++;
	}
	*/

	fseek(stream, 0, SEEK_END);
	dwBytes = ftell(stream);
	dwRecords = dwBytes/(noffset+1);

	// No records found in the file - return
	if(dwRecords == 0)
	{
		fclose(stream);
		ReleaseMutex(hMutex);
		return TRUE;

	}
	

	AuthData *Records = (AuthData *)malloc(sizeof(AuthData) * dwRecords);
	AuthData *temp;
	temp = Records;

	fseek(stream,-((noffset+1)*dwRecords), SEEK_CUR);
	while(!feof(stream))
	{
		fscanf(stream, "%s %s %s %s %s\n",Records->pbName,Records->pbSessionId, Records->pbData, Records->state, Records->Time);
		Records++;
	}
	fclose(stream);


	Records = temp;

	if( (stream = fopen("flatfile", "w+")) == NULL)
	{
		ReleaseMutex(hMutex);
		return FALSE;
	}

	while(dwRecords != 0)
	{
		//if(strcmp((char *)Records->state, state ) != 0)
		SYSTEMTIME stFile;
		SYSTEMTIME stTime;
		SYSTEMTIME stLocalTime;

		GetSystemTime(&stTime);
		SystemTimeToTzSpecificLocalTime(NULL, &stTime, &stLocalTime );
		DecodeStringToSystemTime(Records->Time, &stFile);

		int diff = DiffTimeInMinutes(stLocalTime, stFile);

		if(!(diff > DELETE_TIME) )
		{
			fprintf(stream, "%s %s %s %s %s\n",Records->pbName,Records->pbSessionId, Records->pbData, Records->state, Records->Time);
		}
		Records ++;
		dwRecords --;
	}

	fclose(stream);
	free(temp);
	if (! ReleaseMutex(hMutex))
	{ 
          return FALSE;
	}
	
	return TRUE;
}

BOOL SetStateAndDate(STATE state, AuthData* AuthSessionData)
{
	long noffset = sizeof(AuthData);
	SYSTEMTIME stFile;
	SYSTEMTIME stTime;
	SYSTEMTIME stLocalTime;

	GetSystemTime(&stTime);
	SystemTimeToTzSpecificLocalTime(NULL, &stTime, &stLocalTime );
	DecodeStringToSystemTime(AuthSessionData->Time, &stFile);

	int diff = DiffTimeInSeconds(stLocalTime, stFile);

	FormatDate( stLocalTime, AuthSessionData->Time);
	itoa(state, AuthSessionData->state, 10);
	if(diff > TIMEOUT)  // >15 seconds
	{
		// Report Error
		return FALSE;
	}

	//SystemTimeToTzSpecificLocalTime(NULL, &stTime, &stLocalTime); 

	// Format to write to file


	return TRUE;

}

int DiffTimeInMinutes(SYSTEMTIME st1, SYSTEMTIME st2)
{
	FILETIME ft1;
	FILETIME ft2;

	SystemTimeToFileTime(&st1, &ft1);
	SystemTimeToFileTime(&st2, &ft2);

	_int64 n64FirstTime =  (*(_int64*)(&ft1));
	_int64 n64SecondTime =  (*(_int64*)(&ft2));
	_int64 n64TheDiff = n64FirstTime - n64SecondTime;

	// Difference in Seconds
	int nDiffMinutes = (int)(n64TheDiff/(10000000))/60;
	return nDiffMinutes;
}


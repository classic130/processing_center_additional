//
// System Includes
//

#define INC_OLE2
#include <windows.h>
//
// CRunTime Includes
//

#include <stdlib.h>
#include <limits.h>
#include <io.h>
#include <stdio.h>
#include <winbase.h>
#include <userenv.h>

//#include <atl11\atlbase.h>
#include<atlbase.h>
//
// Private defines
//

#define	MAX_NAME	256

#define BAIL_ON_NULL(p)       \
        if (!(p)) {           \
                goto error;   \
        }

#define BAIL_ON_FAILURE(hr)   \
        if (FAILED(hr)) {     \
                goto error;   \
        }

#define  EXCH_55              1
#define  EXCH_2000            2
#define SPACE_ENCODE	"&#34;&#34;"

#include "activeds.h"
#include "util.h"
#include "Http.h"

extern CHAR	szErrorString[10000] ;
extern HANDLE hToken ;

DWORD      hr;
PCHAR szUserDN;

extern void MyErrorHandler(PCHAR szFDFfile, DWORD dwErrorCode, DWORD dwWinErrorCode, PCHAR szOperation) ;
CHAR *	MakeADsPath(CHAR *) ;
char* EncodeDN(char *szDN);

INT _CRTAPI1 main()
{
	AuthData *Data;

	printf ("Content-Type: text/plain\n") ;
	printf ("Pragma: no cache\n") ;
	printf ("Expires: -1\n") ;
	printf ("Cache-control: no cache\n\n\n") ;

	PSID				pMySID ;

	if ( (pMySID = GetMySid()) == NULL )
	{
		printf("Unable to obtain SID of the Logged on user...<BR>") ;
		return (1) ;
	}

	PCHAR szFullLoginName = GetAccountName(pMySID) ;
	if ( !szFullLoginName )
	{
		printf("Unable to obtain Full Login Name is the Logged on user ...<BR>") ;
		return (1) ;
	}

	if(szFullLoginName!=NULL)
		        free(szFullLoginName);

	PCHAR		szmbMySID ;

	szmbMySID = EncodeSid(pMySID) ;


	MAILBOXINFO	*tMailBoxInfo = NULL ;

	CHttp		httpsession ;


	PCHAR		szExchangeServerName = NULL, szExchangeServerDomain = NULL, szFileName = NULL, szType = NULL ;
	PCHAR		szWindowsUserName = NULL, szWindowsUserPassword = NULL ;
	PCHAR		szExchangeServerName_BOTH =  NULL;
	PCHAR		szExchangeVersion = NULL;
	PCHAR		szCertChainblob = NULL;
	PCHAR		szChallengePhrase = NULL;
	PCHAR		szSessionID =  NULL;

	/*
	szFileName = httpsession.getVar("fileName") ;
	if(szFileName==NULL)
	{
		
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000012, 0, "Exchange Search Status : Get FileName") ;

		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf("%s", szErrorString) ;
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return(NULL) ;


	}
	*/
	// BUG BUG - crashing when CertChain is Posted. This value is not used in our implementation
	/*
	if ( szFileName )
	{
		VSString	vsFilePath = szFileName ;
		FixPath(vsFilePath, "htmldocs") ;
		//FixPath(vsFilePath, "htmldocs") ; // required to run srchexce for cert svr installation on ARANADE-PC
		strcpy(szFileName, vsFilePath.GetBuffer()) ;
	}
	*/

/*
	szExchangeServerName = httpsession.getVar("ExchangeServerName") ;
	if(szExchangeServerName==NULL)
	{
		
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000013, 0, "Exchange Search Status : Get Exchange ServerName") ;

		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf("%s", szErrorString) ;
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return(NULL) ;


	}
*/

	szExchangeServerName_BOTH = httpsession.getVar("ExchangeServerName_BOTH") ;
	if(szExchangeServerName_BOTH==NULL)
	{
		
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000013, 0, "Exchange Search Status : Get Exchange ServerName_BOTH") ;

		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf("%s", szErrorString) ;
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return(NULL) ;

	}
	
/*
	szExchangeServerDomain = httpsession.getVar("ExchangeServerDomain") ;
	if(szExchangeServerDomain==NULL)
	{
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000014, 0, "Exchange Search Status : Get ExchangeServerDomain") ;
		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf("%s", szErrorString) ;
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return(NULL) ;

	}
*/
	
	if ( szExchangeServerDomain )
	{
		PCHAR	tmp = CHttp::HTMLDecode(szExchangeServerDomain) ;

		for ( DWORD cnt = 0, j = 0 ; cnt < strlen(tmp) ; cnt++ )
		{
			if (tmp[cnt] != ',')
				szExchangeServerDomain[j++] = tmp[cnt] ;
			else
			{
				szExchangeServerDomain[j++] = '\\' ;
				szExchangeServerDomain[j++] = tmp[cnt] ;
			}
		}
		szExchangeServerDomain[j] = '\0' ;
	}
	
	szExchangeVersion = httpsession.getVar("ExchangeVersion") ;
	if(szExchangeVersion==NULL)
	{
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000025, 0, "Exchange Search Status : Get ExchangeVersion") ;
		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf("%s", szErrorString) ;
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return(NULL) ;

	}

	szType = httpsession.getVar("Type") ;
	szWindowsUserName = httpsession.getVar("WindowsUserName") ;
	szWindowsUserPassword = httpsession.getVar("WindowsUserPassword") ;

	PCHAR		szMyDN=NULL, szMyFullName=NULL, szMyEmailAddress=NULL, szMyHomeMTA=NULL ,szAuthUpdate=NULL;

	if ( strcmp(szType, "Stuff") == 0 )
	{
/*
			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf ("This is a test ... <BR>") ;
			printf("szType is : %s<BR>", szType) ;
			printf("szExchangeServerName is : %s<BR>", szExchangeServerName) ;
			printf("szExchangeServerDomain is : %s<BR>", szExchangeServerDomain) ;
			printf("szFullLoginName is : %s<BR>", szFullLoginName) ;
			printf("szWindowsUserName is : %s<BR>", szWindowsUserName) ;
			printf("szWindowsUserPassword is : %s<BR>", szWindowsUserPassword) ;
			printf("szUserCertificate is : %s<BR>", szUserCertificate) ;
			printf("szUserSMIMECertificate is : %s<BR>", szUserSMIMECertificate) ;
			printf("tmpUserDN is : %s<BR>", tmp) ;
			printf("szMyDN is : %s<BR>", szMyDN) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(1) ;
*/

		PCHAR	szUserCertificate, szUserSMIMECertificate ;
		BOOL    bUse_AuthUpdate; 

		szUserCertificate = httpsession.getVar("userCertificate") ;
		if(szUserCertificate==NULL)
		{
		
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000015, 0, "Exchange Search Status : Get UserCertificate") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;

		}

		szUserSMIMECertificate = httpsession.getVar("userSMIMECertificate") ;
		if(szUserSMIMECertificate==NULL)
		{
			
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000016, 0, "Exchange Search Status : Get UserSMIMECertificate") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;

		}


		szAuthUpdate=httpsession.getVar("Use_AuthUpdate");
		
		if(szAuthUpdate==NULL)
		{
		
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000018, 0, "Exchange Search Status : Get Use_AuthUpdate") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;

		}

		bUse_AuthUpdate=atoi(szAuthUpdate);

		PCHAR	tmp = httpsession.getVar("userDN") ;
	
		if(tmp==NULL)
		{
		
		MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000017, 0, "Exchange Search Status : Get userDN") ;

		printf ("<HTML>\n") ;
		printf ("<BODY>\n") ;
		printf("%s", szErrorString) ;
		printf ("</BODY>\n") ;
		printf ("</HTML>\n") ;
		return(NULL) ;


		}

		szUserDN = (PCHAR)malloc(strlen(tmp)+1) ;
		{
			CHAR	decodedDN[1024] ;
			for ( DWORD ocount = 0, icount = 0 ; icount < strlen(tmp) ; icount++ )
				if ( tmp[icount] == '+' )
					decodedDN[ocount++] = ' ' ;
				else
					decodedDN[ocount++] = tmp[icount] ;
			decodedDN[ocount] = '\0' ;
			strcpy(szUserDN, decodedDN) ;
		}

		szMyDN = szUserDN ;
/*
		szMyDN = httpsession.getVar("userDN") ;
		if(szMyDN == NULL)
		{
		
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000017, 0, "Exchange Search Status : Get userDN") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;

		}
*/
		DWORD dwTmp = 0 ;
		if ( szWindowsUserName && szWindowsUserPassword )
		{
			for ( dwTmp = 0 ; szWindowsUserName[dwTmp] != '\0' ; dwTmp++)
			{
				if ( szWindowsUserName[dwTmp] == '+' )
				{
					szWindowsUserName[dwTmp] = '\0' ;
					break ;
				}
			}

			for ( dwTmp = 0 ; szWindowsUserPassword[dwTmp] != '\0' ; dwTmp++)
			{
				if ( szWindowsUserPassword[dwTmp] == '+' )
				{
					szWindowsUserPassword[dwTmp] = '\0' ;
					break ;
				}
			}
		}
/*
			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("szFullLoginName is : %s<BR>", szFullLoginName) ;
			printf("szWindowsUserName is : %s<BR>", szWindowsUserName) ;
			printf("szWindowsUserPassword is : %s<BR>", szWindowsUserPassword) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(1) ;
*/


		/*
		printf("<HTML>\n") ;
		printf("<BODY>\n") ;
		printf("ADsPath = %s\n", szADSPath);
		printf("After = %s \n", szMyDN);
		printf("</BODY>\n") ;
		printf("</HTML>\n") ;
		return (0) ;
		*/

		
		//DWORD dwSessionID;
		szChallengePhrase = httpsession.getVar("ChallengePhrase") ;
		if(szChallengePhrase==NULL)
		{
			
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000026, 0, "Exchange Search Status : Get ChallengePhrase") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;
		}
		
		
		szSessionID = httpsession.getVar("SessionID") ;
		if(szSessionID==NULL)
		{
			
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000027, 0, "Exchange Search Status : Get SessionID") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;
		}

		// Verify whether the challenge phrase corresponding the session id exists.

		if(! verifyChallenge((BYTE*)szSessionID, (BYTE*)szChallengePhrase))
		{
			// Errors handled inside the function
			return(NULL) ;
		}

		
		if(! AuthenticateChallenge(szUserSMIMECertificate, szChallengePhrase, szSessionID) )
		{
			// Errors handled inside the function
			return(NULL) ;
		}


		int nExchangeVersion;
		nExchangeVersion = atoi(szExchangeVersion);
		AuthData AuthSessionData;
		int nReturn;
		DWORD dwError = 0;
		HRESULT hr = S_OK;
		if(nExchangeVersion == EXCH_55)
		{
			if(StuffExchange_55(szExchangeServerName_BOTH,
						szMyDN,
						szUserCertificate,
						szUserSMIMECertificate,
						bUse_AuthUpdate))
			{
							
				// If you reach here, then it means that the stuffing operation was
				// successful.
				nReturn = ReadAuthRecord((PBYTE)szSessionID, &AuthSessionData);
				if(nReturn == 0)
				{
					// report Record Not found for the Session ID
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate StuffExchange_55 : Read AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;
				}
				else if (nReturn == -1)
				{
					dwError = GetLastError();
					hr = HRESULT_FROM_WIN32(dwError);
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate StuffExchange_55 : Read AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;

				}

				if(!SetStateAndDate(PUBLISHED, &AuthSessionData))
				{
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000033, 0, "ServerUpdate StuffExchange_55 : Authenticated Update Timed Out") ;
					printf("%s", szErrorString) ;
					return FALSE;
				}

				nReturn = WriteAuthRecord((PBYTE)szSessionID, AuthSessionData);
				if(nReturn == 0)
				{
					// Report Error - Writing Record Failed
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate StuffExchange_55 : Write AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;
				}
				else if(nReturn == -1)
				{
					dwError = GetLastError();
					hr = HRESULT_FROM_WIN32(dwError);
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate StuffExchange_55 : Write AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;
				}
						
				printf("<HTML>\n") ;
				printf("<BODY>\n") ;

				CHAR	szRefresh[8192] ;
				sprintf(szRefresh, "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=../softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=10000000&operation=Enrollment%%20Status&showError=\">\n") ;
				printf ("%s", szRefresh) ;

				printf("</BODY>\n") ;
				printf("</HTML>\n") ;
				return (0) ;
		
			}
		 }

		 if(nExchangeVersion == EXCH_2000)
		 {
			 if(StuffExchange_Win2k(szExchangeServerName_BOTH,
						szMyDN,
						szUserCertificate,
						szUserSMIMECertificate,
						bUse_AuthUpdate) )
			 {
				 							
				// If you reach here, then it means that the stuffing operation was
				// successful.
				 nReturn = ReadAuthRecord((PBYTE)szSessionID, &AuthSessionData);
				if(nReturn == 0)
				{
					// report Record Not found for the Session ID
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate StuffExchange_Win2k : Read AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;
				}
				else if (nReturn == -1)
				{
					dwError = GetLastError();
					hr = HRESULT_FROM_WIN32(dwError);
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate StuffExchange_Win2k : Read AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;

				}

				if(!SetStateAndDate(PUBLISHED, &AuthSessionData))
				{
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000033, 0, "ServerUpdate StuffExchange_Win2k : Authenticated Update Timed Out") ;
					printf("%s", szErrorString) ;
					return FALSE;
				}

				nReturn = WriteAuthRecord((PBYTE)szSessionID, AuthSessionData);
				if(nReturn == 0)
				{
					// Report Error - Writing Record Failed
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000030, 0, "ServerUpdate StuffExchange_Win2k : Write AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;
				}
				else if(nReturn == -1)
				{
					dwError = GetLastError();
					hr = HRESULT_FROM_WIN32(dwError);
					MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000031, hr, "ServerUpdate StuffExchange_Win2k : Write AuthRecord") ;
					printf("%s", szErrorString) ;
					return FALSE ;
				}

				printf("<HTML>\n") ;
				printf("<BODY>\n") ;

				CHAR	szRefresh[8192] ;
				sprintf(szRefresh, "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=../softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&errorCode=10000000&operation=Enrollment%%20Status&showError=\">\n") ;
				printf ("%s", szRefresh) ;

				printf("</BODY>\n") ;
				printf("</HTML>\n") ;
				return (0) ;
			 }
		 }

		if(szmbMySID!=NULL)
				free(szmbMySID);
		return (1) ;
	}
	else if(strcmp(szType, "Challenge") == 0)
	{
		
		CHAR	szRefresh[8192] ;
		CHAR	*szMyUserDN = NULL;

		szAuthUpdate=httpsession.getVar("Use_AuthUpdate");
		
		if(szAuthUpdate==NULL)
		{
		
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000018, 0, "Exchange Search Status : Get Use_AuthUpdate") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;

		}
		
		szCertChainblob = httpsession.getVar("CertChainblob") ;
		if(szCertChainblob==NULL)
		{
			
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000028, 0, "Exchange Search Status : Get CertChainBlob") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;
		}

		// Encoded and posted 
		PCHAR buff = httpsession.getVar("userDN") ;
		if(buff==NULL)
			
		{
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000017, 0, "Exchange Search Status : Get userDN_temp") ;
			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;
		}

		szMyUserDN = EncodeDN(buff);


		// Used for extracting the alias of the user in getAuthData.
		PCHAR	tmp = httpsession.getVar("userDN") ;
		if(tmp==NULL)
		{
		
			MyErrorHandler("../fdf/VSApps/client/ExchangeErrors.fdf", 0x00000017, 0, "Exchange Search Status : Get userDN") ;

			printf ("<HTML>\n") ;
			printf ("<BODY>\n") ;
			printf("%s", szErrorString) ;
			printf ("</BODY>\n") ;
			printf ("</HTML>\n") ;
			return(NULL) ;


		}
		CHAR	decodedDN[1024] ;
		szUserDN = (PCHAR)malloc(strlen(tmp)+1) ;
		{
			
			for ( DWORD ocount = 0, icount = 0 ; icount < strlen(tmp) ; icount++ )
				if ( tmp[icount] == '+' )
					decodedDN[ocount++] = ' ' ;
				else
					decodedDN[ocount++] = tmp[icount] ;
			decodedDN[ocount] = '\0' ;
			strcpy(szUserDN, decodedDN) ;
		}


		Data = getAuthData();	// Get the Authenticated Data
		if (Data == NULL)
		{
			// Error reporting handled in getAuthData.
			return (NULL);
		}


		printf("<HTML>\n") ;
		printf("<BODY>\n") ;
		
		//sprintf(szRefresh, "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0;URL=../softbounce.exe?form_file=../fdf/VSApps/client/ExchangeErrors.fdf&ExchangeServerName_2000=%s&SessionID=%d&ChallengePhrase=%s&CertChainblob=%s&errorCode=20000000&operation=Enrollment%%20Status&showError=\">\n",szExchangeServerName_2000,Data->dwSessionId,Data->pbData,szCertChainblob) ;
		sprintf(szRefresh, "<FORM NAME=PASS ACTION=\"../softbounce.exe\" ENCTYPE=x-www-form-encoded METHOD=POST>");
   		printf ("%s", szRefresh) ;

		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"form_file\" VALUE=\"../fdf/VSApps/client/ExchangeErrors.fdf\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"errorCode\" VALUE=\"20000000\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"operation\" VALUE=\"Enrollment Status\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"showError\" VALUE=\"\">");

		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"ChallengePhrase\" VALUE=%s>",Data->pbData);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"CertChainblob\" VALUE=%s>",szCertChainblob);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"SessionID\" VALUE=%s>",Data->pbSessionId);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"userDN\" VALUE=%s>",szMyUserDN);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"exchange_ServerName\" VALUE=%s>",szExchangeServerName_BOTH);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"exchange_Version\" VALUE=%s>",szExchangeVersion);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"Use_AuthUpdate\" VALUE=%s>",szAuthUpdate);

		printf("</FORM>\n");
		printf ("<SCRIPT LANGUAGE=VBScript>\n") ;
		printf ("<!--\n") ;
		printf("document.PASS.submit\n");
		printf ("\'-->\n");
		printf("</SCRIPT>\n");
		
		
		printf("</BODY>\n") ;
		printf("</HTML>\n") ;
		return (0) ;
	

	}

	return(0) ;

}

void	ErrorHandler(CHAR *szTheErrorString)
{
	strcpy(szErrorString, szTheErrorString) ;
}

CHAR *	getName(CHAR *input)
{
  if ( (input[0] == 'c' || input[0] == 'C') && (input[1] == 'n' || input[1] == 'N') && (input[2] == '=') )
  {
	  // You have got cn=
	  CHAR	*retval = (CHAR	*)malloc(4) ;
	  strcpy(retval, "cn=") ;
	  return retval ;
  }
  else if ( (input[0] == 'o' || input[0] == 'O') && (input[1] == '=') )
  {
	  // You have o=
	  CHAR	*retval = (CHAR	*)malloc(3) ;
	  strcpy(retval, "o=") ;
	  return retval ;
  }
  else if ( (input[0] == 'o' || input[0] == 'O') && (input[1] == 'u' || input[1] == 'U') && (input[2] == '=') )
  {
	  // You have ou=
	  CHAR	*retval = (CHAR	*)malloc(4) ;
	  strcpy(retval, "ou=") ;
	  return retval ;
  }
  else
	  return NULL ;
}

CHAR *	MakeADsPath(CHAR *inputDN)
{
	DWORD	i = 0, j = 0 ;
	CHAR	value[256] ;
	BOOL	bFirst = TRUE ;
	CHAR	retDN[1024] ;

	retDN[0] = '\0' ;

	CHAR	*indexptr = inputDN, *retptr = NULL  ;
	while ( *indexptr )
	{
		CHAR	*name ;
		name = getName(indexptr) ;
		indexptr += strlen(name) ;

		strcat(retDN, name) ;
		
		i = 0 ;
		retptr = NULL ;

		while ( (retptr = getName(indexptr)) == NULL )
		{
			if ( strlen(indexptr) )
			{
				if ( *indexptr != '\"' )
					value[i++] = *indexptr ;
				indexptr++ ;
			}
			else 
			{
				if ( *indexptr != '\"' )
					value[i++] = *indexptr ;
				break ;
			}
		}

		if (retptr) 
			free(retptr) ;

		value[i-1] = 0 ;

		CHAR	realValue[256] ;
		for ( i = 0, j = 0 ; i < strlen(value) ; i++, j++ )
		{
			if ( value[i] != ',' )
				realValue[j] = value[i] ;
			else
			{
				realValue[j++] = '\\' ;
				realValue[j] = value[i] ;
			}
		}

		realValue[j] = '\0' ;

		strcat(retDN, realValue) ;
		strcat(retDN, ",") ;

		free(name) ;
	}

	i = strlen(retDN) ;
	retDN[i-1] = '\0' ;

	CHAR	*retVal = (PCHAR) malloc(strlen(retDN)+1) ;

	strcpy(retVal, retDN) ;

	return retVal ;
}

char* EncodeDN(char *szDN)
{
	int i = 0;
	int count = 0;
	char *szEncodeDN = NULL;
	char EncodedDN[1024];
	while(szDN[i++])
	{
		if(szDN[i] == '"')
			count++;

	}

	szEncodeDN = (PCHAR)malloc(strlen(szDN)+ strlen(SPACE_ENCODE) + 1) ;
	if(count)
	{
		for ( DWORD ocount = 0, icount = 0 ; icount < strlen(szDN) ; icount++ )
		{
			if(szDN[icount] == '"')
			{
				strcpy(&EncodedDN[ocount++],SPACE_ENCODE);
				ocount += strlen(SPACE_ENCODE) - 1;
			}
			else
				EncodedDN[ocount++] = szDN[icount] ;
		}
		strcpy(szEncodeDN,EncodedDN);
		EncodedDN[ocount] = '\0' ;
	}
	else
	{
		strcpy(szEncodeDN,szDN);
	}
	return szEncodeDN;
}

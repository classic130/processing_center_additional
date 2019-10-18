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

void
PrintUsage(
    void
    );


HRESULT 
ProcessArgs(
    int argc,
    char * argv[]
    );


LPWSTR
RemoveWhiteSpaces(
    LPWSTR pszText
    );


typedef		struct _mailboxinfo
{
	PCHAR		szMyDN ;
	PCHAR		szMyEmailAddress ;
	PCHAR		szMyFullName ;
} MAILBOXINFO ;


enum STATE {SENT, VERIFIED, AUTHENTICATED, PUBLISHED};

typedef struct{
	BYTE pbName[NAME_LEN];
	BYTE pbData[CHALLENGE_LEN + 1];
	BYTE pbSessionId[9];
	char state[2];
	char Time[24];
}AuthData;

void _ShowErrorMessage(DWORD errorCode) ;
BSTR _MultiToWideString(LPSTR szInputString) ;
LPSTR _WideToMultiString(BSTR szwcInputString) ;

LPVOID AllocateTokenInfoBuffer(
    HANDLE hToken,
    TOKEN_INFORMATION_CLASS InfoClass,
    DWORD *dwSize);

PSID	GetMySid(void) ;
PCHAR	EncodeSid(PSID pMySid) ;
PCHAR	GetAccountName(PSID pMySID) ;
void	ErrorHandler(CHAR *szErrorString) ;

void	FixPath(VSString& szFile, VSString documentRoot) ;

BOOL StuffExchange_55(PCHAR szExchangeServerName,
						PCHAR szBaseDN,
						PCHAR szUserCertificate,
						PCHAR szUserSMIMECertificate,
						BOOL bUse_AuthUpdate);

BOOL StuffExchange_Win2k(PCHAR szExchangeServerName,
						PCHAR szBaseDN,
						PCHAR szUserCertificate,
						PCHAR szUserSMIMECertificate,
						BOOL bUse_AuthUpdate);

int Hascii2Bin(PCHAR hasc,
			   PCHAR *OutBuf,
			   int *OutLen);

PCHAR	HTMLDecode(PCHAR input) ;
void    MyErrorHandler(PCHAR szFDFfile, DWORD dwErrorCode, DWORD dwWinErrorCode, PCHAR szOperation) ;

//Functions for Authenticated Update.

AuthData* getAuthData();

BOOL verifyChallenge(BYTE *pbSessionID,
					 BYTE *pbData);

void Base64Encode(PCHAR pInput, 
				  DWORD dwInputSize, 
				  PCHAR pOutput, 
				  DWORD * dwOutputSize);

void FormatDate(SYSTEMTIME stTime,
				char* szFormatDate);

void getRandomString(BYTE *pbData,
					 int len);

void DecodeStringToSystemTime(char *szFormatString,
							  SYSTEMTIME *stTimeOut);

int DiffTimeInSeconds(SYSTEMTIME st1,
					  SYSTEMTIME st2);

int DiffTimeInMinutes(SYSTEMTIME st1,
					  SYSTEMTIME st2);

BOOL AuthenticateChallenge(char *szUserSMIMECertificate,
						   char *szChallengePhrase,
						   char *szSessionID);

DWORD CreateAuthRecord(AuthData *pAuthSessionData);

int ReadAuthRecord(BYTE *pbSessionID,
				   AuthData* Data);

int WriteAuthRecord(BYTE *pbSessionID,
					AuthData Data);

BOOL DeleteRecords();

BOOL SetStateAndDate(STATE state,
					 AuthData* AuthSessionData);

#endif  // __MAIN_HXX

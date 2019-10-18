/*
 *	VeriSign PTA authentication scheme, (c) VeriSign Inc 2001
 *  Author: Bin Zou
 */
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "SmApi.h"
#include "vssmutil.h"

#ifdef _WIN32
#include <afx.h>
#else
extern "C" {
#define WINAPI
#endif
#ifdef SOLARIS 
#pragma fini (vsSmAuthRelease)
#endif
const int  SCHEME_VERSION   = 0x0300;
const char SCHEME_DESCRIPTION[] = "VeriSign PTA authentication scheme, (c) VeriSign Inc 2001";


/*
// SmAuthQuery:
// The SiteMinder calls this function to request scheme information.
// The function will return description of the scheme or credentials
// required for the authentication.
//
// PARAMETERS:
// [in] lpszParam:        Parameter string specified in the authentication scheme.
// [in] lpszSharedSecret: Shared secret string specified in the authentication scheme.
// [in] Sm_AuthApi_QueryCode_t: Request code is any one of the following
//      1. Sm_AuthApi_QueryDescription    - Request description of the scheme.
//      2. Sm_AuthApi_QueryCredentialsReq - Request the credentials required by the
//                                          scheme and where to obtain them.
// [out] lpszStatusBuffer: Buffer for a character string response.
// [out] lpnStatusCode:  Buffer for a numeric response.
//
// RETURNS:
// Any one of the following  Sm_AuthApi_Status_t values:
//   Sm_AuthApi_Success
//   Sm_AuthApi_Failure
*/


Sm_AuthApi_Status_t WINAPI SmAuthQuery (
    const char*   lpszParam,                    /* parameter (null-terminated) */
    const char*   lpszSharedSecret,             /* shared secret (null-terminated) */
    const         Sm_AuthApi_QueryCode_t nCode, /* query code */
    char*         lpszStatusBuffer,             /* status buffer to hold the null-terminated string */
    int*          lpnStatusCode)                /* status code */
{

    switch (nCode)
    {
        case Sm_AuthApi_QueryDescription:
            strcpy (lpszStatusBuffer, SCHEME_DESCRIPTION);
			if(vsSmAuthInit(lpszParam)!=0) {
				return Sm_AuthApi_Failure;
			}
            *lpnStatusCode = SCHEME_VERSION;
            break;

        case Sm_AuthApi_QueryCredentialsReq:
            //*lpnStatusCode = Sm_AuthApi_Cred_FormRequired|Sm_AuthApi_Cred_SSLRequired;
			*lpnStatusCode = Sm_AuthApi_Cred_FormRequired;
			if(vsSmAuthQuery(lpszStatusBuffer,lpszSharedSecret) !=0)
				return Sm_AuthApi_Failure;
			else
				break;

        default:
            return Sm_AuthApi_Failure;
    }

    return Sm_AuthApi_Success;
}


/*
// SmAuthInit:
// The SiteMinder calls this function to initialize the scheme.
// The scheme should initialize the resources it needs at this time.
// The function is called once when the scheme is loaded for the first time.
// PARAMETERS:
// [in] lpszServerParam:  Parameter string as specified for the authentication scheme.
// [in] lpszSharedSecret: Shared secret string specified in the authentication scheme.
//
// RETURNS:
// Any one of the following Sm_AuthApi_Status_t values:
//   Sm_AuthApi_Success
//   Sm_Authapi_Failure (scheme will not be loaded)
*/
Sm_AuthApi_Status_t WINAPI SmAuthInit (
    const char * lpszServerParam,       /* server parameter */
    const char * lpszSharedSecret)      /* server shared secret */
{
	//if(vsSmAuthInit(lpszServerParam) == 0)
		return Sm_AuthApi_Success;
	//else
		//return Sm_AuthApi_Failure;
}


/*
// SmAuthRelease:
// The SiteMinder calls this functions only when it is shutting down.
// The scheme should release all its resources at this time.
// This function is called once when the SiteMinder is shutting down.
// PARAMETERS:
// [in] lpszServerParam:  Parameter string as specified for the authentication scheme.
// [in] lpszSharedSecret: Shared secret string specified in the authentication scheme.
//
// RETURNS:
// Any one of the following Sm_AuthApi_Status_t values:
//   Sm_AuthApi_Success
//   Sm_Authapi_Failure
*/
Sm_AuthApi_Status_t WINAPI SmAuthRelease (
    const char * lpszServerParam,       /* server parameter */
    const char * lpszSharedSecret)      /* server shared secret */
{
	vsSmAuthRelease();
    return Sm_AuthApi_Success;
}


/*
// SmAuthenticate:
// The SiteMinder calls this function to perform user authentication.
// The scheme authenticates user credentials and returns one of the following results:
// PARAMETERS:
//   [in] lpApiContext
//   [in] lpUserContext
//   [in] lpUserCredentials
//   [in] bChallengeResponse
//   [in] lpszServerParam
//   [in] lpszSharedSecret
//   [in] nBytesUserMsg
//
//   [out] lpszUserMsg
//   [out] nBytesErrMsg
//   [out] lpszErrMsg
//
// RETURNS: One of the following Sm_AuthApi_Status_t
//   Sm_AuthApi_Success
//   Sm_AuthApi_Failure
//   Sm_AuthApi_Accept
//   Sm_AuthApi_Reject
//   Sm_AuthApi_Challenge
//   Sm_AuthApi_Attempt
//   Sm_AuthApi_NoUserContext
//   Sm_AuthApi_SuccessUserDN
//
*/
Sm_AuthApi_Status_t WINAPI SmAuthenticate (
    const Sm_Api_Context_t*                 lpApiContext,           /* the structure that provides API context */
    const Sm_Api_UserContext_t*             lpUserContext,          /* the structure that allows access to user properties */
    const Sm_AuthApi_UserCredentials_t*     lpUserCredentials,      /* the user credentials */
    char                                    bChallengeResponse,     /* the boolean indicating whether or not this is the response to a challenge */
    const char *                            lpszServerParam,        /* the parameter to be passed to the server */
    const char *                            lpszSharedSecret,       /* the secret to be passserver shared secret */
    const int                               nBytesUserMsg,          /* maximum size of the user message buffer */
    char *                                  lpszUserMsg,            /* output buffer to hold the null-terminated user message */
    const int                               nBytesErrMsg,           /* maximum size of the error buffer */
    char *                                  lpszErrMsg)             /* output buffer to hold the null-terminated error message */
{

    /* If the scheme is designed not to disambiguate users, it should return SmAuthApi_NoUserContext. */
    if (!lpUserContext->bIsUserContext) {
		if(vsSmAuthenticate(lpUserCredentials->lpszUsername,lpUserCredentials->lpszPassword,lpszUserMsg, nBytesUserMsg,lpszSharedSecret) == 0)
			return SM_MAKEAUTH_STATUSVALUE (Sm_AuthApi_Success, Sm_Api_Reason_None);
		else
			return Sm_AuthApi_Reject;
	} else {
 
		return SM_MAKEAUTH_STATUSVALUE (Sm_AuthApi_Accept, Sm_Api_Reason_None);
	}

}

/*BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dvReason, LPVOID lpv) {

  switch (dvReason) {

	  case DLL_PROCESS_ATTACH:
		break;

	  case DLL_PROCESS_DETACH:

		break;

	  case DLL_THREAD_ATTACH:
		 break;

	  case DLL_THREAD_DETACH:
		  ;
  }

  return TRUE;
}*/

#ifndef _WIN32
}
#endif

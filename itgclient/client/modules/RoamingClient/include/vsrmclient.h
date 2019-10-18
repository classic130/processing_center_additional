/*
 * $Revision: 1.2.404.1 $
 * $Header: /cvs/itgclient/client/modules/RoamingClient/include/vsrmclient.h,v 1.2.404.1 2003/06/09 23:41:30 sgoginen Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 2000. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef VSRMCLIENT_H
#define VSRMCLIENT_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VSRMCLIENT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VSRMCLIENT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef WIN32
    #ifdef VSRMCLIENT_EXPORTS
        #define VSRMCLIENT_API __declspec(dllexport)
    #elif defined(VSRMCLIENT_IMPORTS)
        #define VSRMCLIENT_API __declspec(dllimport)
    #else
        #define VSRMCLIENT_API
    #endif
#else
    #define VSRMCLIENT_API
#endif

#include "vsrmdata.h"

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef _VSRM_LOG_FUNC_
#define _VSRM_LOG_FUNC_ 
typedef void (*VSRM_LOG_FUNC)(const BYTE* i_pcbyteData, const DWORD i_cdwDataLength);
#endif

VSRM_STATUS
VSRMCLIENT_API VSRM_StartSession(
    VSRM_SESSION_HANDLE* sessionID,
    const VSRM_CHAR*     username, 
    const VSRM_PASSWORD* password, 
    const char*          serverUrlInfo,
    const char*          serverUrlInfoSignature);

VSRM_STATUS 
VSRMCLIENT_API VSRM_ReserveUserName(
    VSRM_SESSION_HANDLE  sessionID,
    VSRM_USERNAME_STATUS *nameStatus);

/**
 * This function creates a user roaming account with given profile.
 *
 * A caller of this API normally creates a session first, and possibly
 * calls VSRM_ReserverUserName() before this call.
 *
 * Input:
 *   sessionID   - session handle that contains server information
 *   privateData - the user private data to be encrypted and saved in roaming account
 *   nvp         - user information, currently we support question, answer, firstname, 
 *                 lastname, and emailaddress.
 *                 To enable the password reset functionality, question and answer can
 *                 not be NULL.
 *                 question is for password reset use. If it is NULL, there will be no 
 *                 password reset keys created.
 *                 answer to the user question is for password reset. If it is NULL,
 *                 there will be no password reset keys created.
 *
 *                 Firtname, lastname, and email address are for the search function
 *                 Email address is for the change password, password reset notification
 *                 purpose.
 *
 * For example:

 VSRM_CHAR_NVP nvp[] = {
  {(char *) QUESTIONSTRING, CharToVSRMChar("What is the name of my favorite city?")},
  {(char *) ANSWERSTRING,   CharToVSRMChar("San Francisco, CA")},
  {(char *) FNAMESTRING,    CharToVSRMChar("John")},
  {(char *) LNAMESTRING,    CharToVSRMChar("Doe")},
  {(char *) EMAILSTRING,    CharToVSRMChar("johndoe@acme.com")},
  {NULL, NULL}
 };

 */
VSRM_STATUS 
VSRMCLIENT_API VSRM_StoreData(
    VSRM_SESSION_HANDLE sessionID,
    const VSRM_ITEM*    privateData,
    VSRM_CHAR_NVP*      nvp);

VSRM_STATUS 
VSRMCLIENT_API VSRM_RecoverData(
    VSRM_SESSION_HANDLE sessionID,
    VSRM_ITEM**         privateData);

VSRM_STATUS 
VSRMCLIENT_API VSRM_UpdateData(
    VSRM_SESSION_HANDLE sessionID,
    const VSRM_ITEM*    privateData);

VSRM_STATUS 
VSRMCLIENT_API VSRM_ChangePassword(
    VSRM_SESSION_HANDLE  sessionID,
    const VSRM_PASSWORD* oldPassword,
    const VSRM_PASSWORD* newPassword);

/**
 * This API returns the status whether the roaming server supports 
 * password reset feature.
 *
 * Input:
 *   sessionID   - session handle that contains server information
 *
 * Output:
 *   b - boolean status of the password reset feature support
 */
VSRM_STATUS 
VSRMCLIENT_API VSRM_ResetPasswordEnabled(
    VSRM_SESSION_HANDLE sessionID,
    VSRM_BOOL*          b);

/**
 * This API returns user's password reset question in UNICODE string.
 *
 * Input:
 *   sessionID   - session handle that contains server information
 *
 * Output:
 *   question - Unicode string of the user password reset question
 */
VSRM_STATUS 
VSRMCLIENT_API VSRM_GetUserQuestion(
    VSRM_SESSION_HANDLE  sessionID,
    VSRM_CHAR**          question);

/**
 * This function resets password according to answer input.
 * It can optionally pass private data back to caller.
 *
 * A caller of this API normally creates a session first with
 * username and server information, and then call VSRM_GetUserQuestion()
 * to get user's password reset question. It prompts user to enter
 * the answer and a new password, then makes call of this API.
 *
 * Input:
 *   sessionID   - session handle that contains server information
 *   answer      - the answer to user question. It must not be null.
 *   newPassword - the new password that user chooses
 *
 * Output:
 *   privateData - it carries recovered private data back. If it is NULL,
 *                 private data won't be returned.
 */
VSRM_STATUS 
VSRMCLIENT_API VSRM_ResetPassword(
    VSRM_SESSION_HANDLE  sessionID,
    const VSRM_CHAR*     answer,
    const VSRM_PASSWORD* newPassword,
    VSRM_ITEM**          privateData);

VSRM_STATUS 
VSRMCLIENT_API VSRM_DeleteData(
    VSRM_SESSION_HANDLE sessionID,
    VSRM_ITEM**         privateData);

VSRM_STATUS 
VSRMCLIENT_API VSRM_EndSession(
    VSRM_SESSION_HANDLE sessionID);

void
VSRMCLIENT_API VSRM_SetLogFunction(
    VSRM_LOG_FUNC f);

void 
VSRMCLIENT_API VSRM_SetLogLevel(
    VSRM_LOG_LEVEL logLevel);

const VSRM_CHAR*
VSRMCLIENT_API VSRM_QueryErrorServerUrl(
    VSRM_SESSION_HANDLE sessionID);

void 
VSRMCLIENT_API VSRM_FreeItem(
    VSRM_ITEM* dataItem);

void 
VSRMCLIENT_API VSRM_DestroyItem(
    VSRM_ITEM* dataItem);

#ifdef  __cplusplus
}
#endif

#endif // VSRMCLIENT_H

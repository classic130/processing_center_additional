//+-----------------------------------------------------------------------
//
// Microsoft Windows
//
// Copyright (c) Microsoft Corporation 1991-1998
//
// File:        Security.h
//
// Contents:    Toplevel include file for security aware components
//
//
// History:     06 Aug 92   RichardW    Created
//              23 Sep 92   PeterWi     Add security object include files
//
//------------------------------------------------------------------------


// This file will go out and pull in all the header files that you need,
// based on defines that you issue.  The following macros are used.
//
// SECURITY_KERNEL      Use the kernel interface, not the usermode
//

#ifdef __cplusplus
extern "C"
{
#endif


//
// These are name that can be used to refer to the builtin packages
//

#ifndef NTLMSP_NAME_A
#define NTLMSP_NAME_A            "NTLM"
#define NTLMSP_NAME              L"NTLM"        // ntifs
#endif // NTLMSP_NAME

#ifndef MICROSOFT_KERBEROS_NAME_A
#define MICROSOFT_KERBEROS_NAME_A   "Kerberos"
#define MICROSOFT_KERBEROS_NAME_W   L"Kerberos"
#ifdef WIN32_CHICAGO
#define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_A
#else
#define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_W
#endif
#endif  // MICROSOFT_KERBEROS_NAME_A


#ifndef NEGOSSP_NAME
#define NEGOSSP_NAME_W  L"Negotiate"
#define NEGOSSP_NAME_A  "Negotiate"

#ifdef UNICODE
#define NEGOSSP_NAME    NEGOSSP_NAME_W
#else
#define NEGOSSP_NAME    NEGOSSP_NAME_A
#endif
#endif // NEGOSSP_NAME

//
// Include the master SSPI header file
//

#include <sspi.h>

#if defined(SECURITY_WIN32) || defined(SECURITY_KERNEL)
#include <secext.h>
#endif

//
// Include the error codes:
//

#if ISSP_LEVEL == 32
#include <issperr.h>
#endif

#if ISSP_LEVEL == 16
#include <issper16.h>
#endif



#ifdef __cplusplus
}
#endif


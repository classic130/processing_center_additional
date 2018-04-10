// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__56855052_DA94_11D3_A1C3_001083023D07__INCLUDED_)
#define AFX_STDAFX_H__56855052_DA94_11D3_A1C3_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>
#include <comdef.h>
#include <wchar.h>

#include <mapix.h>
#include <mapiguid.h>
#include <mapidefs.h>
#include <MAPIUTIL.H>

#include <wincrypt.h>

#define UNICODE
#include <winldap.h>
#undef UNICODE


#include <EDK.H>
#include <EDKUTILS.H>



#include "VSGSEOffice.h"
#include "VSGSEOutlook.h"
#include "signatrb.h"

#define		MY_ENCODING_TYPE	(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING)
enum FRDLYNAMETYPE {BOTH, SIGN, ENCRYPT};
typedef struct _CCERT_CONTEXT_LIST {
	PCCERT_CONTEXT pCertContext ;
	struct _CCERT_CONTEXT_LIST *nextCertContext ;
} CCERT_CONTEXT_LIST, *PCCERT_CONTEXT_LIST ;

#define SIGNCERT	L"(SIGN)"
#define ENCRYPTCERT L"(ENCRYPT)"

#define  MAXLEN               256

#define  EXCH_55              1
#define  EXCH_2000            2

#define  ID_COMA_SEP          ","
#define  ID_DOT_SEP           "."

#include "ProfAdmin.h"






//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__56855052_DA94_11D3_A1C3_001083023D07__INCLUDED)

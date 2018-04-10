// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__C5E8B9D8_D217_11D4_A21E_001083023D07__INCLUDED_)
#define AFX_STDAFX_H__C5E8B9D8_D217_11D4_A21E_001083023D07__INCLUDED_

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

#include <stdio.h>
#include <tchar.h>
#include <wincrypt.h>

#include <mshtml.h>



////////for wininet declaration and Constant////////////////////////
#include "wininet.h"
/*********/
#include "simder_all.h"

/////PTA related headers files///////////////
#include "ptav3_i.c"
#include "ptadllapi_i.c"

#include "ptav3.h"
#include "ptadllapi.h"
#include "ptaerrs.h"
#include "ptadefines.h"

/////bsafelite related headers files
#include "integrate.h"

/////SMIME related files/////////////////
#include "vsmimelib.h"


////PKCS Engine
#include "pkcs7engine.h"
///SGMS COMMON
#include "sgmscommon.h"
//////Global Memory
#include "gmemmgmt.h"
#include "vsgmm_errors.h"

#include "AttachInfo.h"

#include "global.h"
#include "vssc_pta.h"
#include "userinfo.h"
#include "Msg.h" 
#include "AppContext.h"

#include "certmgmt.h"
#include "vsscerrs.h"
#include "vsscmacros.h"
/************/

#include "post.h"
#include "vssc_util.h"





//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__C5E8B9D8_D217_11D4_A21E_001083023D07__INCLUDED)

#ifndef _VS_INCLUDE_LANG_UTILS_
#define _VS_INCLUDE_LANG_UTILS_
#include "stdafx.h"
#include <comdef.h>

HRESULT _LoadStringW(HINSTANCE hInst, WORD wLangId, short nStringID, WCHAR* wstrOutBuff, int nOutBufSize);
BOOL _IsLangSupported(WORD wLangID);
int _GetCharset(WORD wLangID);
void _WhatFontsSupported(int nCharset, BOOL& boolTNRSupport, BOOL& boolCourierSupport, BOOL& boolSystemSupport, BOOL& boolGuiSupport, BOOL& boolAnySupport, _bstr_t& tbstrFontName);
BOOL _DoesFontSupportCharset(_bstr_t& tbstrFontName, int nCharset);
BOOL _IsFontAvailable(_bstr_t& tbstrFontName);
WORD _GetMatchingStringTableLangId(WORD wLangID);

#endif
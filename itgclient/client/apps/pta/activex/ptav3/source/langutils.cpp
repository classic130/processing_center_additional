#include "stdafx.h"
#include "..\Include\langutils.h"
#include "..\Include\ptaerrs.h"
#include "..\Include\ptadefines.h"


int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,int FontType,LPARAM lParam);

//Return - E_FAIL, E_BUFFTOOSMALL, E_OUTOFMEMORY - This function assumes that the 
//		   language table exists and the string id is also correct.
HRESULT _LoadStringW(HINSTANCE hInst, WORD wLangId, short nStringID, WCHAR* wstrOutBuff, int nOutBufSize)
{
	HRSRC hRes;
	HGLOBAL hGlobal;
	PBYTE	pbyteStringTable;
	WORD*	pdwTempPtr;
	int i;
	WORD wStringLen;

	/*Find the string table resource*/
	hRes = FindResourceEx(hInst,RT_STRING,(LPTSTR)(nStringID/16+1),wLangId);
	if(!hRes)
	{
		return (E_FAIL);
	}

	/*Load the resource*/
	hGlobal = LoadResource(hInst,hRes);
	if(!hGlobal)
		return(E_OUTOFMEMORY);

	/*Get the string table*/
	pbyteStringTable = (PBYTE)LockResource(hGlobal);

	/*Get to the right string in the string table*/
	pdwTempPtr = (WORD*)pbyteStringTable;
	wStringLen = 0;
	for(i= 0; i<(nStringID % 16) + 1; ++i)
	{
		//Read the length of the string
		pdwTempPtr = pdwTempPtr + wStringLen;
		wStringLen = (WORD)(*pdwTempPtr);
		pdwTempPtr ++;
	}

	/*Read the string*/
	if(wStringLen <= nOutBufSize)
	{
		memcpy((void*)wstrOutBuff, (void*)pdwTempPtr, sizeof(WCHAR)*wStringLen);
	}
	else
	{
		return E_BUFFTOSMALL;
	}

	wstrOutBuff[wStringLen] = 0x0000;

	return S_OK;

}

BOOL _IsLangSupported(WORD wLangID)
{
	switch(wLangID)
	{
	case VS_LANG_ENGLISH_US :
	case VS_LANG_JAPANESE :

	case VS_LANG_PORTUGUESE_BRAZIL :
//	case VS_LANG_PORTUGUESE_STANDARD :

	case VS_LANG_CHINESE_TRADITIONAL :
	case VS_LANG_CHINESE_SIMPLIFIED:
//	case VS_LANG_CHINESE_HONGKONG :
//	case VS_LANG_CHINESE_SINGAPORE :
//	case VS_LANG_CHINESE_MACAU :

	case VS_LANG_FRENCH_STANDARD :
//	case VS_LANG_FRENCH_BELGIAN :
//	case VS_LANG_FRENCH_CANADIAN :
//	case VS_LANG_FRENCH_SWITZERLAND : 
//	case VS_LANG_FRENCH_LUXEMBOURG : 
//	case VS_LANG_FRENCH_MONACO : 

	case VS_LANG_GERMAN_STANDARD : 
//	case VS_LANG_GERMAN_SWITZERLAND : 
//	case VS_LANG_GERMAN_AUSTRIA : 
//	case VS_LANG_GERMAN_LUXEMBOURG : 
//	case VS_LANG_GERMAN_LIECHTENSTEIN : 

//	case VS_LANG_SPANISH_TRADITIONAL : 
//	case VS_LANG_SPANISH_MEXICAN : 
	case VS_LANG_SPANISH_MODERNPORT : 
//	case VS_LANG_SPANISH_GUATEMALA : 
//	case VS_LANG_SPANISH_COSTA_RICA : 
//	case VS_LANG_SPANISH_PANAMA : 
//	case VS_LANG_SPANISH_DOMINICAN_REPUBLIC : 
//	case VS_LANG_SPANISH_VENEZUELA : 
//	case VS_LANG_SPANISH_COLOMBIA : 
//	case VS_LANG_SPANISH_PERU : 
//	case VS_LANG_SPANISH_ARGENTINA : 
//	case VS_LANG_SPANISH_ECUADOR : 
//	case VS_LANG_SPANISH_CHILE : 
//	case VS_LANG_SPANISH_URUGUAY : 
//	case VS_LANG_SPANISH_PARAGUAY : 
//	case VS_LANG_SPANISH_BOLIVIA : 
//	case VS_LANG_SPANISH_ELSALVADOR : 
//	case VS_LANG_SPANISH_HONDURAS : 
//	case VS_LANG_SPANISH_NICARAGUA : 
//	case VS_LANG_SPANISH_PUERTORICO : 

	case VS_LANG_DANISH : 
	case VS_LANG_DUTCH_NETHERLANDS : 
	case VS_LANG_FINNISH : 
	case VS_LANG_KOREAN : 
	case VS_LANG_SWEDISH : 
	case VS_LANG_ITALIAN_STANDARD : 
		return TRUE;

	default :
		return FALSE;
	}
}


WORD _GetMatchingStringTableLangId(WORD wLangID)
{
	   // Get corresponding language id that was defined in the resource string table
	switch(wLangID)
	{

	case VS_LANG_PORTUGUESE_BRAZIL :
	case VS_LANG_PORTUGUESE_STANDARD :
		return VS_LANG_PORTUGUESE_BRAZIL;

	case VS_LANG_FRENCH_STANDARD :
	case VS_LANG_FRENCH_BELGIAN :
	case VS_LANG_FRENCH_CANADIAN :
	case VS_LANG_FRENCH_SWITZERLAND : 
	case VS_LANG_FRENCH_LUXEMBOURG : 
	case VS_LANG_FRENCH_MONACO : 
		return VS_LANG_FRENCH_STANDARD;

	case VS_LANG_GERMAN_STANDARD : 
	case VS_LANG_GERMAN_SWITZERLAND : 
	case VS_LANG_GERMAN_AUSTRIA : 
	case VS_LANG_GERMAN_LUXEMBOURG : 
	case VS_LANG_GERMAN_LIECHTENSTEIN : 
		return VS_LANG_GERMAN_STANDARD;

	case VS_LANG_SPANISH_TRADITIONAL : 
	case VS_LANG_SPANISH_MEXICAN : 
	case VS_LANG_SPANISH_MODERNPORT : 
	case VS_LANG_SPANISH_GUATEMALA : 
	case VS_LANG_SPANISH_COSTA_RICA : 
	case VS_LANG_SPANISH_PANAMA : 
	case VS_LANG_SPANISH_DOMINICAN_REPUBLIC : 
	case VS_LANG_SPANISH_VENEZUELA : 
	case VS_LANG_SPANISH_COLOMBIA : 
	case VS_LANG_SPANISH_PERU : 
	case VS_LANG_SPANISH_ARGENTINA : 
	case VS_LANG_SPANISH_ECUADOR : 
	case VS_LANG_SPANISH_CHILE : 
	case VS_LANG_SPANISH_URUGUAY : 
	case VS_LANG_SPANISH_PARAGUAY : 
	case VS_LANG_SPANISH_BOLIVIA : 
	case VS_LANG_SPANISH_ELSALVADOR : 
	case VS_LANG_SPANISH_HONDURAS : 
	case VS_LANG_SPANISH_NICARAGUA : 
	case VS_LANG_SPANISH_PUERTORICO : 
		return VS_LANG_SPANISH_MODERNPORT;

	default :
		return wLangID;
	}
}

int _GetCharset(WORD wLangID)
{
	/*Get the code page for this language*/
	TCHAR tcharTemp[7];
	if(!GetLocaleInfo(wLangID,LOCALE_IDEFAULTANSICODEPAGE,tcharTemp, 7))
	{
		return -1;
	}

	/*Get the charset that supports this code page*/
	CHARSETINFO CharSetInfo;
	if(!TranslateCharsetInfo((DWORD*)_ttoi(tcharTemp),&CharSetInfo, TCI_SRCCODEPAGE))
		return -1;

	return CharSetInfo.ciCharset;

}


void _WhatFontsSupported(int nCharset, BOOL& boolMSSFSupport, BOOL& boolCourierSupport, BOOL& boolSystemSupport, BOOL& boolGuiSupport, BOOL& boolAnySupport, _bstr_t& tbstrFontName)
{
	//See if Times New Roman is supported.
	tbstrFontName = "MS Sans Serif";
	boolMSSFSupport = _DoesFontSupportCharset(tbstrFontName, nCharset);

	//See if Courier is supported.
	tbstrFontName = "Courier";
	boolCourierSupport = _DoesFontSupportCharset(tbstrFontName, nCharset);

	
	//Obtain the font that will display the messages
	NONCLIENTMETRICS ncm;
    memset(&ncm, 0, sizeof(ncm));
    ncm.cbSize = sizeof(ncm);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS,  0, &ncm, 0);
    tbstrFontName = ncm.lfMessageFont.lfFaceName;

	//Check if the default gui font supports this charset
	boolGuiSupport = _DoesFontSupportCharset(tbstrFontName,nCharset);

	
	//See if system is supported
	tbstrFontName = "System";
	boolSystemSupport = _DoesFontSupportCharset(tbstrFontName, nCharset);


	//If none are supported, see if any are supported at all
	if(!boolMSSFSupport && !boolCourierSupport && !boolSystemSupport &&!boolGuiSupport)
	{
		tbstrFontName = ""; 
		boolAnySupport = _DoesFontSupportCharset(tbstrFontName, nCharset);
	}
	else
	{
		//Since atleast one of the others is supported, mark any supported as TRUE.
		boolAnySupport = TRUE;
		if(boolMSSFSupport)
			tbstrFontName = "Times New Roman";
		else if(boolCourierSupport)
			tbstrFontName = "Courier";
		else if(boolGuiSupport)
		{
			tbstrFontName = ncm.lfMessageFont.lfFaceName;
		}
		else if(boolSystemSupport)
			tbstrFontName = "System";
	}

	return;
	
}

BOOL _DoesFontSupportCharset(_bstr_t& tbstrFontName, int nCharset)
{
	LOGFONT logfont;
	FONTENUMPROC fontenumproc;
	TCHAR tcharFontName[32] = _T("");

	logfont.lfCharSet = nCharset;
	lstrcpy(logfont.lfFaceName,(TCHAR*)tbstrFontName);
	logfont.lfPitchAndFamily = 0;
	fontenumproc = (FONTENUMPROC)EnumFontFamExProc;
	
	EnumFontFamiliesEx(GetDC(NULL),&logfont,fontenumproc,(LPARAM)tcharFontName,0);
	if(lstrlen(tcharFontName))
	{
		tbstrFontName = tcharFontName;
		return TRUE;
	}
	else 
		return FALSE;

}

BOOL _IsFontAvailable(_bstr_t& tbstrFontName)
{
	LOGFONT logfont;
	FONTENUMPROC fontenumproc;
	TCHAR tcharFontName[32] = _T("");

	lstrcpy(logfont.lfFaceName,(TCHAR*)tbstrFontName);
	fontenumproc = (FONTENUMPROC)EnumFontFamExProc;
	
	EnumFontFamiliesEx(GetDC(NULL),&logfont,fontenumproc,(LPARAM)tcharFontName,0);
	if(lstrlen(tcharFontName))
	{
		tbstrFontName = tcharFontName;
		return TRUE;
	}
	else 
		return FALSE;

}

int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme,int FontType,LPARAM lParam)
{
	if(FontType & TRUETYPE_FONTTYPE )
	{
		lstrcpy((TCHAR*)lParam,(TCHAR*)lpelfe->elfFullName);
	}
	else
	{
		lstrcpy((TCHAR*)lParam,(TCHAR*)lpelfe->elfLogFont.lfFaceName);
	}
	return 0;
}
// Http.h: interface for the Http class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HTTP_H__214B7DB3_8811_11D3_8383_0060B0B32E16__INCLUDED_)
#define AFX_HTTP_H__214B7DB3_8811_11D3_8383_0060B0B32E16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wtypes.h>

typedef struct _httpvars {
	PCHAR name ;
	PCHAR value ;
	struct _httpvars *next ;
} HTTPVARS, *PHTTPVARS ;


class CHttp  
{
public :
	CHttp();
	virtual ~CHttp();

	PHTTPVARS		_hvAllHttpVars ;

	static PCHAR	HTMLDecode(PCHAR input) ;
	PCHAR			getVar(PCHAR szVarName) ;


private :

	PCHAR			_szQueryString, _szContentString ;
	BOOL			_bQueryString, _bContentString, _bFirstVar ;
	DWORD			_VarCount ;
};

#endif // !defined(AFX_HTTP_H__214B7DB3_8811_11D3_8383_0060B0B32E16__INCLUDED_)

// Http.h: interface for the Http class.
//
//////////////////////////////////////////////////////////////////////


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

	static	PCHAR	URLDecodeAlloc(const char *iBuff);
	static  PCHAR	URLEncodeAlloc(const unsigned char *iBuff, int n);

	PCHAR			getVar(PCHAR szVarName) ;

	void PostError(PCHAR szFDFfile, DWORD dwErrorCode, DWORD dwWinErrorCode, PCHAR szOperation);


private :

	PCHAR			_szQueryString, _szContentString ;
	BOOL			_bQueryString, _bContentString, _bFirstVar ;
	DWORD			_VarCount ;
	CHAR			_szErrorString[1024] ;
};



// UTF8String.h: interface for the CUTF8String class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UTF8String_H_INCLUDED_)
#define _UTF8String_H_INCLUDED_

#include "BaseDER.h"

class CUTF8String : public CBaseDER
{
public:
	CUTF8String();
	virtual ~CUTF8String();

	CUTF8String(CUTF8String &cUTF8String) ;
	CUTF8String(_DWORD i_cbData, _PBYTE i_pbData) ;
	CUTF8String operator=(CUTF8String &cUTF8String) ;

	void decode() ;
};

#endif // !defined(_UTF8String_H_INCLUDED_)

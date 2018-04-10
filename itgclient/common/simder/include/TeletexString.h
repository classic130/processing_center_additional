// PrintableString.h: interface for the CTeletexString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TELETEXSTRING_H_INCLUDED_)
#define _TELETEXSTRING_H_INCLUDED_

#include "BaseDER.h"

class CTeletexString : public CBaseDER
{
public:
	CTeletexString();
	virtual ~CTeletexString();

	CTeletexString(CTeletexString &cteletexstring) ;
	CTeletexString(_DWORD i_cbData, _PBYTE i_pbData) ;
	CTeletexString operator=(CTeletexString &cteletexstring) ;

	void decode() ;
};

#endif // !defined(_TELETEXSTRING_H_INCLUDED_)

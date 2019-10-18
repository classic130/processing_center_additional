// BMPString.h: interface for the CBMPString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BMPSTRING_H_INCLUDED_)
#define _BMPSTRING_H_INCLUDED_

#include "BaseDER.h"

class CBMPString : public CBaseDER
{
public:
	CBMPString();
	virtual ~CBMPString();

	CBMPString(CBMPString &cbmpstring) ;
	CBMPString(_DWORD i_cbData, _PBYTE i_pbData) ;
	CBMPString operator=(CBMPString &cbmpstring) ;

	void decode() ;
};

#endif // !defined(_BMPSTRING_H_INCLUDED_)


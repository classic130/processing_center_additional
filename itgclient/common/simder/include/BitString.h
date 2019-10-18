// BitString.h: interface for the CBitString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BITSTRING_H_INCLUDED_)
#define _BITSTRING_H_INCLUDED_

#include "BaseDER.h"

class CBitString : public CBaseDER
{
public:
	CBitString();
	virtual ~CBitString();

	CBitString(CBitString &cbitstring) ;
	CBitString(_DWORD i_cbUnusedBits, _DWORD i_cbData, _PBYTE i_pbData) ;
	CBitString operator=(CBitString &cbitstring) ;

	void decode() ;
};

#endif // !defined(_BITSTRING_H_INCLUDED_)

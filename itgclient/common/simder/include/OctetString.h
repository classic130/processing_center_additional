// OctetString.h: interface for the COctetString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_OCTETSTRING_H_INCLUDED_)
#define _OCTETSTRING_H_INCLUDED_

#include "BaseDER.h"

class COctetString : public CBaseDER
{
public:
	COctetString();
	virtual ~COctetString();

	COctetString(COctetString &coctetstring) ;
	COctetString(_DWORD i_cbData, _PBYTE i_pbData) ;
	COctetString operator=(COctetString &coctetstring) ;

	void decode() ;
};

#endif // !defined(_OCTETSTRING_H_INCLUDED_)

// UniversalInteger.h: interface for the CUniversalInteger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UNIVERSALINTEGER_H_INCLUDED_)
#define _UNIVERSALINTEGER_H_INCLUDED_

#include "BaseDER.h"

class CUniversalInteger : public CBaseDER
{
public:
	CUniversalInteger() ;
	virtual ~CUniversalInteger() ;

	CUniversalInteger(CUniversalInteger &cuniversalinteger) ;
	CUniversalInteger(_DWORD i_cbData, _PBYTE i_pbData) ;
	CUniversalInteger(_DWORD i_cbData, _PBYTE i_pbData, _BOOL i_bEndian) ;
	CUniversalInteger operator=(CUniversalInteger &cuniversalinteger) ;

	void decode() ;
};

#endif // !defined(_UNIVERSALINTEGER_H_INCLUDED_)

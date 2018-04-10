// VisibleString.h: interface for the CVisibleString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_VISIBLESTRING_H_INCLUDED_)
#define _VISIBLESTRING_H_INCLUDED_

#include "BaseDER.h"

class CVisibleString : public CBaseDER
{
public:
	CVisibleString();
	virtual ~CVisibleString();

	CVisibleString(CVisibleString &cvisiblestring) ;
	CVisibleString(_DWORD i_cbData, _PBYTE i_pbData) ;
	CVisibleString operator=(CVisibleString &cvisiblestring) ;

	void decode() ;
};

#endif // !defined(_VISIBLESTRING_H_INCLUDED_)

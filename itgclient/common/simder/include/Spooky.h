// Spooky.h: interface for the CSpooky class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SPOOKY_H_INCLUDED_)
#define _SPOOKY_H_INCLUDED_

#include "BaseDER.h"

class CSpooky : public CBaseDER
{
public:
	CSpooky();
	virtual ~CSpooky();

	CSpooky(CSpooky &cspooky) ;
	CSpooky(_DWORD i_cbData, _PBYTE i_pbData) ;
	CSpooky operator=(CSpooky &cspooky) ;
};

#endif // !defined(_SPOOKY_H_INCLUDED_)

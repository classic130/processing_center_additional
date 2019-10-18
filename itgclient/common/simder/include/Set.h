// Set.h: interface for the CSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SET_H_INCLUDED_)
#define _SET_H_INCLUDED_

#include "BaseDER.h"
#include "BaseDERCollection.h"

class CSet : public CBaseDER
{
public:
	CSet();
	virtual ~CSet();

	CSet(CSet &cset) ;
	CSet(CBaseDER &cbaseder) ;
	CSet(CBaseDERCollection &cbasedercollection) ;
	CSet(_DWORD i_cbData, _PBYTE i_pbData) ;

	CSet(CBaseDER &cbaseder, _BYTE i_cbIndefiniteLength) ;
	CSet(CBaseDERCollection &cbasedercollection, _BYTE i_cbIndefiniteLength) ;
	CSet(_DWORD i_cbData, _PBYTE i_pbData, _BYTE i_cbIndefiniteLength) ;
	
	CSet operator=(CSet &cset) ;
	CSet operator=(CBaseDERCollection &cbasedercollection) ;
	CSet operator=(CBaseDER &cbaseder) ;
	CSet operator+=(CBaseDERCollection &cbasedercollection) ;
	CSet operator+=(CBaseDER &cbaseder) ;

	void decode() ;
};

#endif // !defined(_SET_H_INCLUDED_)

// Sequence.h: interface for the CSequence class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SEQUENCE_H_INCLUDED_)
#define _SEQUENCE_H_INCLUDED_

#include "BaseDER.h"
#include "BaseDERCollection.h"

class CSequence : public CBaseDER
{
public:
	CSequence();
	virtual ~CSequence();

	CSequence(CSequence &csequence) ;
	CSequence(CBaseDER &cbaseder) ;
	CSequence(CBaseDERCollection &cbasedercollection) ;
	CSequence(_DWORD i_cbData, _PBYTE i_pbData) ;
	
	CSequence(CBaseDER &cbaseder, _BYTE i_cbIndefiniteLength) ;
	CSequence(CBaseDERCollection &cbasedercollection, _BYTE i_cbIndefiniteLength) ;
	CSequence(_DWORD i_cbData, _PBYTE i_pbData, _BYTE i_cbIndefiniteLength) ;
	
	CSequence operator=(CSequence &csequence) ;
	CSequence operator=(CBaseDERCollection &cbasedercollection) ;
	CSequence operator=(CBaseDER &cbaseder) ;
	CSequence operator+=(CBaseDERCollection &cbasedercollection) ;
	CSequence operator+=(CBaseDER &cbaseder) ;

	void decode() ;
};

#endif // !defined(_SEQUENCE_H_INCLUDED_)

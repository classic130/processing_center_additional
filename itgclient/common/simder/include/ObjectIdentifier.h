// ObjectIdentifier.h: interface for the CObjectIdentifier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_OBJECTIDENTIFIER_H_INCLUDED_)
#define _OBJECTIDENTIFIER_H_INCLUDED_

#include "BaseDER.h"
#include "DataTypes.h"

class CObjectIdentifier : public CBaseDER
{
public:
	CObjectIdentifier();
	virtual ~CObjectIdentifier();

	CObjectIdentifier(CObjectIdentifier &cobjectidentifier) ;
	CObjectIdentifier(_DWORD i_cbData, _PBYTE i_pbData) ;
	CObjectIdentifier operator=(CObjectIdentifier &cobjectidentifier) ;

	void decode() ;

private:
	_DWORD	getSubId(_PCHAR szObjIdComp, _PBYTE subid) ;
	_DWORD	getSubId1(_PCHAR szObjIdComp, _PBYTE subid) ;
	_DWORD	getSubId2(_PCHAR szObjIdComp1, _PCHAR szObjIdComp2, _PBYTE subid) ;
	_DWORD	EncodeSubId(_DWORD dwSubId, _PBYTE pbSubEncodedSubId) ;

};

#endif // !defined(_OBJECTIDENTIFIER_H_INCLUDED_)

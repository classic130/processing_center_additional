// BaseDERCollection.h: interface for the CBaseDERCollection class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASEDERCOLLECTION_H_INCLUDED_)
#define _BASEDERCOLLECTION_H_INCLUDED_

#include "DERBlob.h"
#include "BaseDER.h"

class CBaseDERCollection  
{
public:
	CBaseDERCollection();
	CBaseDERCollection(CBaseDERCollection &cbasedercollection);
	CBaseDERCollection(_DWORD cbData, _PBYTE pbData) ;
	CBaseDERCollection operator=(CBaseDERCollection &cbasedercollection) ;
	CBaseDERCollection operator=(CBaseDER &cbaseder) ;
	CBaseDERCollection operator+(CBaseDERCollection &cbasedercollection) ;
	CBaseDERCollection operator+(CBaseDER &cbaseder) ;
	// This operator will add CBaseDER object at the beginning of list 
	// pointed by CBaseDERCollection object. artf 39000
	CBaseDERCollection operator%(CBaseDER &cbaseder) ;
	virtual ~CBaseDERCollection();

	CDERBlob	*BaseDERBlob ;
};

#endif // !defined(_BASEDERCOLLECTION_H_INCLUDED_)

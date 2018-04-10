// BaseDERHierarchy.h: interface for the CBaseDERHierarchy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASEDERHIERARCHY_H_INCLUDED_)
#define _BASEDERHIERARCHY_H_INCLUDED_

#include	"BaseDERCollection.h"

typedef struct _DERTree
{
	CBaseDER		*currentBaseDER ;
	struct _DERTree	*nextDERTree ;
	struct _DERTree	*rightDERTree ;
} DERTree ;

class CBaseDERHierarchy  
{
public:
	CBaseDERHierarchy(CBaseDERCollection &cbasedercollection);
	virtual ~CBaseDERHierarchy();

	CBaseDERCollection	m_cbasedercollection ;
	DERTree				m_DERTree ;
	_DWORD				dwErrorCode ;

private:
	void				fillit(DERTree *i_DERTree, CDERBlob *i_DERBlob) ;
	CDERBlob			*getNext(CDERBlob *i_DERBlob) ;
	CDERBlob			*getInside(CDERBlob *i_DERBlob) ;
	_BOOL	GetLengthInfo(CDERBlob *i_DERBlob, _DWORD *insideDERBlobLength, _DWORD *ContentLengthBytes) ;
	void				freeit(DERTree *i_DERTree) ;

	INT4				_RemainingLength ;
};

#endif // !defined(_BASEDERHIERARCHY_H_INCLUDED_)

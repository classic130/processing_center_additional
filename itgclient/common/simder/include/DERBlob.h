// DERBlob.h: interface for the CDERBlob class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DERBLOB_H_INCLUDED_)
#define _DERBLOB_H_INCLUDED_

#include	"DataTypes.h"

class CDERBlob  
{
public:
	CDERBlob() ;
	CDERBlob(_DWORD size) ;
	CDERBlob(CDERBlob &cderblob) ;
	CDERBlob(_DWORD cbData, _PBYTE pbData) ;

	virtual ~CDERBlob() ;

	CDERBlob operator=(CDERBlob &cderblob) ;
	friend CDERBlob operator+(CDERBlob &firstcderblob, CDERBlob &secondcderblob) ;

	_DWORD		cbData ; // Encoded data length.
	_PBYTE		pbData ; // Encoded data pointer.
};

#endif // !defined(_DERBLOB_H_INCLUDED_)

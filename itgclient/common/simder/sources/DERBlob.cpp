// DERBlob.cpp: implementation of the CDERBlob class.
//
//////////////////////////////////////////////////////////////////////

#include "DERBlob.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDERBlob::CDERBlob()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
}

CDERBlob::CDERBlob(_DWORD size)
{
	if ( (pbData = (_PBYTE) malloc(size)) != NULL )
		cbData = size ;
	else
	{
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}
}

CDERBlob::CDERBlob(_DWORD i_cbData, _PBYTE i_pbData)
{
	if ( i_cbData == 0 )
	{
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}

	if ( (pbData = (_PBYTE) malloc(i_cbData)) != NULL )
	{
		cbData = i_cbData ;
		memcpy(pbData, i_pbData, i_cbData) ;
	}
	else
	{
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}

}

CDERBlob::CDERBlob(CDERBlob &cderblob)
{
	if ( (pbData = (_PBYTE) malloc(cderblob.cbData)) != NULL )
	{
		cbData = cderblob.cbData ;
		memcpy(pbData, cderblob.pbData, cbData) ;
	}
	else
	{
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}
}

CDERBlob::~CDERBlob()
{
	if ( pbData )
		(*SIMDER_MemErase)(cbData, pbData) ;

	if (pbData)
		free (pbData) ;

	cbData = 0x00000000 ;
	pbData = _NULL ;
}

CDERBlob CDERBlob::operator=(CDERBlob &cderblob)
{
	if (pbData)
	{
		free (pbData) ;
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}

	if ( (pbData = (_PBYTE) malloc(cderblob.cbData)) != NULL )
	{
		cbData = cderblob.cbData ;
		memcpy(pbData, cderblob.pbData, cbData) ;
	}
	else
	{
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}

	return (*this) ;
}

CDERBlob operator+(CDERBlob &firstcderblob, CDERBlob &secondcderblob)
{
	_PCHAR	tmp ;

	if ( (tmp = (_PCHAR) malloc(firstcderblob.cbData+secondcderblob.cbData)) != NULL )
	{
		if ( firstcderblob.pbData && firstcderblob.cbData )
			memcpy(tmp, firstcderblob.pbData, firstcderblob.cbData) ;

		if ( secondcderblob.pbData && secondcderblob.cbData )
			memcpy(tmp+firstcderblob.cbData, secondcderblob.pbData, secondcderblob.cbData) ;
	}

	CDERBlob	retderblob(firstcderblob.cbData+secondcderblob.cbData, tmp) ;

	if (tmp)
		free (tmp) ;

	return (retderblob) ;
}


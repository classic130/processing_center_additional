// Null.cpp: implementation of the CNull class.
//
//////////////////////////////////////////////////////////////////////

#include "Null.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNull::CNull()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = NULL_DER_TYPE ;

	_PCHAR	tmp ;
	tmp = (_PBYTE) malloc(2) ;
	tmp[0] = NULL_DER_TYPE ;
	tmp[1] = 0x00 ;

	BaseDERBlob = new CDERBlob(2, tmp) ;

	free (tmp) ;
}

CNull::~CNull()
{
	if ( pbData )
		(*SIMDER_MemErase)(cbData, pbData) ;

	if ( pbData )
	{
		free (pbData) ;
		cbData = 0x00000000 ;
		pbData = _NULL;
	}
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CNull::CNull(CNull &cnull)
{
	copyinfo(NULL_DER_TYPE, cnull) ;
}

CNull CNull::operator=(CNull &cnull)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(NULL_DER_TYPE, cnull) ;

	return *this ;
}

void CNull::decode()
{
	if ( BaseDERBlob != _NULL )
	{
		if ( (Type = BaseDERBlob->pbData[0]) == NULL_DER_TYPE )
		{
			NumberOfLengthBytes = 0x00 ;
			cbData = 0x00 ;
			if ( Type & 0x20 )
				Encoding = CONSTRUCTED ;
			Type = Type & 0x1F ;

			if (pbData)
				free(pbData) ;

			pbData = _NULL ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

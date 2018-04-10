// Boolean.cpp: implementation of the CBoolean class.
//
//////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <string.h>
#include "Boolean.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBoolean::CBoolean()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CBoolean::~CBoolean()
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

CBoolean::CBoolean(CBoolean &cbollean)
{
	copyinfo(BOOLEAN, cbollean) ;
}

CBoolean::CBoolean(_BYTE bVal)
{
	_BYTE	tmp[1] ;

	if ( bVal != _FALSE )
		tmp[0] = 0xFF ;
	else
		tmp[0] = 0x00 ;

	this->fillit(BOOLEAN, 1, (_PBYTE)tmp) ;
	this->encode() ;
}

CBoolean CBoolean::operator=(CBoolean &cbollean)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(BOOLEAN, cbollean) ;

	return *this ;
}

void CBoolean::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == BOOLEAN )
		{
			GetLengthInfo(BaseDERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

			if ( dwInsideDERBlobLength == 0 || ((dwInsideDERBlobLength+1+dwContentLengthBytes) > BaseDERBlob->cbData) )
			{
				// You have got invalid InsideDERBlob length. So don't bother to decode.
				dwErrorCode = 0xFFFFFFFF ;
				return ;
			}

			NumberOfLengthBytes = dwContentLengthBytes ;
			cbData = dwInsideDERBlobLength ;
			if ( Type & 0x20 )
				Encoding = CONSTRUCTED ;
			Type = Type & 0x1F ;

			if (pbData)
				free(pbData) ;

			pbData = (_PBYTE) malloc(dwInsideDERBlobLength) ;
			memcpy(pbData, BaseDERBlob->pbData + 1+dwContentLengthBytes, dwInsideDERBlobLength) ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

// GENERALIZEDTime.cpp: implementation of the CGENERALIZEDTime class.
//
//////////////////////////////////////////////////////////////////////

#include "GENERALIZEDTime.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGENERALIZEDTime::CGENERALIZEDTime()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CGENERALIZEDTime::~CGENERALIZEDTime()
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

CGENERALIZEDTime::CGENERALIZEDTime(CGENERALIZEDTime &cvisiblestring)
{
	copyinfo(GENERALIZED_TIME, cvisiblestring) ;
}

CGENERALIZEDTime::CGENERALIZEDTime(_DWORD i_cbData, _PBYTE i_pbData)
{
	_PBYTE	tmp ;
	tmp = (_PBYTE) malloc(i_cbData) ;
	memcpy(tmp, i_pbData, i_cbData) ;
	reverse(i_cbData, tmp) ;
	this->fillit(GENERALIZED_TIME, i_cbData, tmp) ;
	free(tmp) ;
	this->encode() ;
}

CGENERALIZEDTime CGENERALIZEDTime::operator=(CGENERALIZEDTime &cvisiblestring)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(GENERALIZED_TIME, cvisiblestring) ;

	return *this ;
}

void CGENERALIZEDTime::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == GENERALIZED_TIME )
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

			pbData = (_PBYTE) malloc(dwInsideDERBlobLength+1) ;
			memcpy(pbData, BaseDERBlob->pbData + 1+dwContentLengthBytes, dwInsideDERBlobLength) ;
			pbData[dwInsideDERBlobLength] = '\0' ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

// UTF8String.cpp: implementation of the CUTF8String class.
//
//////////////////////////////////////////////////////////////////////

#include "UTF8String.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUTF8String::CUTF8String()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CUTF8String::~CUTF8String()
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

CUTF8String::CUTF8String(CUTF8String &cUTF8String)
{
	copyinfo(UTF8_STRING, cUTF8String) ;
}

CUTF8String::CUTF8String(_DWORD i_cbData, _PBYTE i_pbData)
{
	_PBYTE	tmp ;
	tmp = (_PBYTE) malloc(i_cbData) ;
	memcpy(tmp, i_pbData, i_cbData) ;
	reverse(i_cbData, tmp) ;
	this->fillit(UTF8_STRING, i_cbData, tmp) ;
	free(tmp) ;
	this->encode() ;
}

CUTF8String CUTF8String::operator=(CUTF8String &cUTF8String)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(UTF8_STRING, cUTF8String) ;

	return *this ;
}

void CUTF8String::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == UTF8_STRING )
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

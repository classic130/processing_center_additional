// OctetString.cpp: implementation of the COctetString class.
//
//////////////////////////////////////////////////////////////////////

#include "OctetString.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COctetString::COctetString()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

COctetString::~COctetString()
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

COctetString::COctetString(COctetString &coctetstring)
{
	copyinfo(OCTET_STRING, coctetstring) ;
}

COctetString::COctetString(_DWORD i_cbData, _PBYTE i_pbData)
{
	this->fillit(OCTET_STRING, i_cbData, i_pbData) ;
	this->encode2() ;
}


COctetString COctetString::operator=(COctetString &coctetstring)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(OCTET_STRING, coctetstring) ;

	return *this ;
}

void COctetString::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == OCTET_STRING )
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
			//reverse(dwInsideDERBlobLength, pbData) ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

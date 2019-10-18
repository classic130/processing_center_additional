// UniversalInteger.cpp: implementation of the CUniversalInteger class.
//
//////////////////////////////////////////////////////////////////////

#include "UniversalInteger.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CUniversalInteger::CUniversalInteger()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;

}

CUniversalInteger::~CUniversalInteger()
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

CUniversalInteger::CUniversalInteger(CUniversalInteger &cuniversalinteger)
{
	copyinfo(UNIVERSAL_INTEGER, cuniversalinteger) ;
}

CUniversalInteger::CUniversalInteger(_DWORD i_cbData, _PBYTE i_pbData)
{
	this->fillit(UNIVERSAL_INTEGER, i_cbData, i_pbData) ;
	this->encode() ;
}

CUniversalInteger::CUniversalInteger(_DWORD i_cbData, _PBYTE i_pbData, _BOOL i_bEndian)
{
	this->fillit(UNIVERSAL_INTEGER, i_cbData, i_pbData) ;

	if (i_bEndian == _LITTLEENDIAN)
		this->encode() ;
	else
		this->encode2() ;
}

CUniversalInteger CUniversalInteger::operator=(CUniversalInteger &cuniversalinteger)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(UNIVERSAL_INTEGER, cuniversalinteger) ;

	return *this ;
}

void CUniversalInteger::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == UNIVERSAL_INTEGER )
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
			reverse(dwInsideDERBlobLength, pbData) ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}


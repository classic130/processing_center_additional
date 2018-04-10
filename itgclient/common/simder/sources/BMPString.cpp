// BMPString.cpp: implementation of the CBMPString class.
//
//////////////////////////////////////////////////////////////////////

#include "BMPString.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBMPString::CBMPString()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CBMPString::~CBMPString()
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

CBMPString::CBMPString(CBMPString &cbmpstring)
{
	copyinfo(BMP_STRING, cbmpstring) ;
}

CBMPString::CBMPString(_DWORD i_cbData, _PBYTE i_pbData)
{
    _PBYTE  tmp ;
    _DWORD  count ;
    tmp = (_PBYTE) malloc(i_cbData*_SIZEOFUNICODE) ;
    memcpy(tmp, i_pbData, i_cbData*_SIZEOFUNICODE) ;
    for ( count = 0 ; count < i_cbData ; count++ )
        reverse(2, &tmp[count*_SIZEOFUNICODE]) ;
    this->fillit(BMP_STRING, i_cbData*_SIZEOFUNICODE, tmp) ;
    free(tmp) ;
    this->encode2() ;
}

CBMPString CBMPString::operator=(CBMPString &cbmpstring)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(BMP_STRING, cbmpstring) ;

	return *this ;
}

void CBMPString::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == BMP_STRING )
		{
			GetLengthInfo(BaseDERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

			if ( dwInsideDERBlobLength == 0 || ((dwInsideDERBlobLength+1+dwContentLengthBytes) > BaseDERBlob->cbData) )
			{
				// You have got invalid InsideDERBlob length. So don't bother to decode.
				dwErrorCode = 0xFFFFFFFF ;
				return ;
			}

			NumberOfLengthBytes = dwContentLengthBytes ;
			cbData = dwInsideDERBlobLength/2 ;
			if ( Type & 0x20 )
				Encoding = CONSTRUCTED ;
			Type = Type & 0x1F ;

			if (pbData)
				free(pbData) ;

			pbData = (_PBYTE) malloc(dwInsideDERBlobLength+2) ;
			memcpy(pbData, BaseDERBlob->pbData + 1+dwContentLengthBytes, dwInsideDERBlobLength) ;
			pbData[dwInsideDERBlobLength] = '\0' ;
			pbData[dwInsideDERBlobLength+1] = '\0' ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

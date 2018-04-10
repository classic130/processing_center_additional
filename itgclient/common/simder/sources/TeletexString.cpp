// TeletexString.cpp: implementation of the CTeletexString class.
//
//////////////////////////////////////////////////////////////////////

#include "TeletexString.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTeletexString::CTeletexString()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CTeletexString::~CTeletexString()
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

CTeletexString::CTeletexString(CTeletexString &cteletexstring)
{
	copyinfo(TELETEX_STRING, cteletexstring) ;
}

CTeletexString::CTeletexString(_DWORD i_cbData, _PBYTE i_pbData)
{
	_PBYTE	tmp ;
	tmp = (_PBYTE) malloc(i_cbData) ;
	memcpy(tmp, i_pbData, i_cbData) ;
	reverse(i_cbData, tmp) ;
	this->fillit(TELETEX_STRING, i_cbData, tmp) ;
	free(tmp) ;
	this->encode() ;
}

CTeletexString CTeletexString::operator=(CTeletexString &cteletexstring)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(TELETEX_STRING, cteletexstring) ;

	return *this ;
}

void CTeletexString::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == TELETEX_STRING )
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

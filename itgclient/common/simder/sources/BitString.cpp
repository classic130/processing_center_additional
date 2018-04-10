// BitString.cpp: implementation of the CBitString class.
//
//////////////////////////////////////////////////////////////////////

#include "BitString.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBitString::CBitString()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;

	cbUnusedBits = 0x00 ;
}

CBitString::~CBitString()	
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

	cbUnusedBits = 0x00 ;
}

CBitString::CBitString(CBitString &cbitstring)
{
	copyinfo(BIT_STRING, cbitstring) ;

	cbUnusedBits = cbitstring.cbUnusedBits ;
}

CBitString::CBitString(_DWORD i_cbUnusedBits, _DWORD i_cbData, _PBYTE i_pbData)
{
/*
	_PBYTE	tmp ;
	tmp = (_PBYTE) malloc(i_cbData+1) ;
	memcpy(tmp, i_pbData, i_cbData) ;
	if ( i_cbUnusedBits >= 0 && i_cbUnusedBits <= 7 )
		tmp[i_cbData] = (_BYTE) i_cbUnusedBits ;
	else
		return ;
	tmp[0] = tmp[0] & (0xFF << i_cbUnusedBits) ;
	this->fillit(BIT_STRING, i_cbData+1, tmp) ;
	free(tmp) ;
	this->encode() ;

	cbUnusedBits = i_cbUnusedBits ;
*/
	_PBYTE	tmp ;
	tmp = (_PBYTE) malloc(i_cbData+1) ;
	memcpy(tmp+1, i_pbData, i_cbData) ;
	if ( i_cbUnusedBits >= 0 && i_cbUnusedBits <= 7 )
		tmp[0] = (_BYTE) i_cbUnusedBits ;
	else
		return ;
	tmp[i_cbData] = tmp[i_cbData] & (0xFF << i_cbUnusedBits) ;
	this->fillit(BIT_STRING, i_cbData+1, tmp) ;
	free(tmp) ;
	this->encode2() ;

	cbUnusedBits = i_cbUnusedBits ;
}

CBitString CBitString::operator=(CBitString &cbitstring)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(BIT_STRING, cbitstring) ;

	cbUnusedBits = cbitstring.cbUnusedBits ;

	return *this ;
}

void CBitString::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		Type = BaseDERBlob->pbData[0] ;
		if ( (Type & 0x1F) == BIT_STRING )
		{
			GetLengthInfo(BaseDERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

			if ( dwInsideDERBlobLength == 0 || ((dwInsideDERBlobLength+1+dwContentLengthBytes) > BaseDERBlob->cbData) )
			{
				// You have got invalid InsideDERBlob length. So don't bother to decode.
				dwErrorCode = 0xFFFFFFFF ;
				return ;
			}

			cbUnusedBits = BaseDERBlob->pbData[1+dwContentLengthBytes] ;
			NumberOfLengthBytes = dwContentLengthBytes ;
			cbData = dwInsideDERBlobLength-1 ;
			if ( Type & 0x20 )
				Encoding = CONSTRUCTED ;
			Type = Type & 0x1F ;

			if (pbData)
				free(pbData) ;

			pbData = (_PBYTE) malloc(dwInsideDERBlobLength-1) ;
			memcpy(pbData, BaseDERBlob->pbData + 1+dwContentLengthBytes+1, dwInsideDERBlobLength-1) ;
			reverse(dwInsideDERBlobLength-1, pbData) ;

			return ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;

	return ;
}

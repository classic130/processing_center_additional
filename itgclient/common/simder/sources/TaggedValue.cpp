// TaggedValue.cpp: implementation of the CTaggedValue class.
//
//////////////////////////////////////////////////////////////////////

#include "TaggedValue.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTaggedValue::CTaggedValue()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
	Class = UNIVERSAL ;
	Encoding = PRIMITIVE ;
	TagNumber = 0x00 ;
}

CTaggedValue::~CTaggedValue()
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
	Class = UNIVERSAL ;
	Encoding = PRIMITIVE ;
	TagNumber = 0x00 ;
}

CTaggedValue::CTaggedValue(CTaggedValue &ctaggedvalue)
{
	copyinfo(ctaggedvalue.Type, ctaggedvalue) ;
}

CTaggedValue::CTaggedValue(_BYTE i_cbClass, _BYTE i_cbEncoding, _BYTE i_cbTagNumber, _BYTE i_cbImplicit, CBaseDER Contents)
{
	_BYTE	i_Type = INVALID_DER_TYPE ;

	if ( i_cbClass > 0x03 )
		return ;
	if ( i_cbEncoding != PRIMITIVE && i_cbEncoding != CONSTRUCTED )
		return ;
	if ( i_cbTagNumber > 0x1F )
		return ;
	if ( i_cbImplicit != _TRUE && i_cbImplicit != _FALSE )
		return ;

	i_Type = (i_cbClass << 6) | (i_cbEncoding << 5) | i_cbTagNumber ;

	_PBYTE		Tmp ;
	_DWORD		dwTmp ;

	_DWORD		dwInsideBlobLength ;
	dwInsideBlobLength = 0 ;

	if ( Contents.BaseDERBlob->pbData[1] & 0x80 )
		dwInsideBlobLength = (Contents.BaseDERBlob->pbData[1] & 0x7F) + 2 ;
	else
		dwInsideBlobLength = 2 ;

	if ( i_cbImplicit == _TRUE )
	{
		dwTmp = Contents.BaseDERBlob->cbData - dwInsideBlobLength ;
		Tmp = (_PBYTE) malloc (dwTmp) ;
		memcpy(Tmp, Contents.BaseDERBlob->pbData + dwInsideBlobLength, dwTmp) ;
		reverse(dwTmp, Tmp) ;
	}
	else
	{
		dwTmp = Contents.BaseDERBlob->cbData ;
		Tmp = (_PBYTE) malloc (dwTmp) ;
		memcpy(Tmp, Contents.BaseDERBlob->pbData, dwTmp) ;
		reverse(dwTmp, Tmp) ;
	}

	Class = i_cbClass ;
	Encoding = i_cbEncoding ;
	TagNumber = i_cbTagNumber ;
	IndefiniteLength = _FALSE ;

	this->fillit(i_Type, dwTmp, Tmp) ;

	free(Tmp) ;

	this->encode() ;
}

CTaggedValue::CTaggedValue(_BYTE i_cbClass, _BYTE i_cbEncoding, _BYTE i_cbTagNumber, _BYTE i_cbImplicit, _BYTE i_cbIndefiniteLength, CBaseDER Contents)
{
	_BYTE	i_Type = INVALID_DER_TYPE ;

	if ( i_cbClass > 0x03 )
		return ;
	if ( i_cbEncoding != PRIMITIVE && i_cbEncoding != CONSTRUCTED )
		return ;
	if ( i_cbTagNumber > 0x1F )
		return ;
	if ( i_cbImplicit != _TRUE && i_cbImplicit != _FALSE )
		return ;

	i_Type = (i_cbClass << 6) | (i_cbEncoding << 5) | i_cbTagNumber ;

	_PBYTE		Tmp ;
	_DWORD		dwTmp ;

	_DWORD		dwInsideBlobLength ;
	dwInsideBlobLength = 0 ;

	if ( Contents.BaseDERBlob->pbData[1] & 0x80 )
		dwInsideBlobLength = (Contents.BaseDERBlob->pbData[1] & 0x7F) + 2 ;
	else
		dwInsideBlobLength = 2 ;

	if ( i_cbImplicit == _TRUE )
	{
		dwTmp = Contents.BaseDERBlob->cbData - dwInsideBlobLength ;
		Tmp = (_PBYTE) malloc (dwTmp) ;
		memcpy(Tmp, Contents.BaseDERBlob->pbData + dwInsideBlobLength, dwTmp) ;
		reverse(dwTmp, Tmp) ;
	}
	else
	{
		dwTmp = Contents.BaseDERBlob->cbData ;
		Tmp = (_PBYTE) malloc (dwTmp) ;
		memcpy(Tmp, Contents.BaseDERBlob->pbData, dwTmp) ;
		reverse(dwTmp, Tmp) ;
	}

	Class = i_cbClass ;
	Encoding = i_cbEncoding ;
	TagNumber = i_cbTagNumber ;
	IndefiniteLength = i_cbIndefiniteLength ;

	this->fillit(i_Type, dwTmp, Tmp) ;

	free(Tmp) ;

	this->encode() ;
}

// Use this constructor to create constructed encoding blobs for base primitives.

CTaggedValue::CTaggedValue(_BYTE i_cbClass, _BYTE i_cbEncoding, _BYTE i_cbTagNumber, _BYTE i_cbIndefiniteLength, CBaseDERCollection Contents)
{
	_BYTE	i_Type = INVALID_DER_TYPE ;

	if ( i_cbClass > 0x03 )
		return ;
	if ( i_cbEncoding != PRIMITIVE && i_cbEncoding != CONSTRUCTED )
		return ;
	if ( i_cbTagNumber > 0x1F )
		return ;

	i_Type = (i_cbClass << 6) | (i_cbEncoding << 5) | i_cbTagNumber ;

	_PBYTE		Tmp ;
	_DWORD		dwTmp ;

	_DWORD		dwInsideBlobLength ;
	dwInsideBlobLength = 0 ;

	if ( Contents.BaseDERBlob->pbData[1] & 0x80 )
		dwInsideBlobLength = (Contents.BaseDERBlob->pbData[1] & 0x7F) + 2 ;
	else
		dwInsideBlobLength = 2 ;

	dwTmp = Contents.BaseDERBlob->cbData ;
	Tmp = (_PBYTE) malloc (dwTmp) ;
	memcpy(Tmp, Contents.BaseDERBlob->pbData, dwTmp) ;
	reverse(dwTmp, Tmp) ;

	Class = i_cbClass ;
	Encoding = i_cbEncoding ;
	TagNumber = i_cbTagNumber ;
	IndefiniteLength = i_cbIndefiniteLength ;

	this->fillit(i_Type, dwTmp, Tmp) ;

	free(Tmp) ;

	this->encode() ;
}

CTaggedValue CTaggedValue::operator=(CTaggedValue &ctaggedvalue)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(ctaggedvalue.Type, ctaggedvalue) ;

	return *this ;
}

void CTaggedValue::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		// Make sure that the "Class" field is not UNIVERSAL
		if ( (Type = BaseDERBlob->pbData[0]) && 0xC0 )
		{
			// Do not support "Class" = Private
			if ( (Type & 0xC0) != 0xC0 )
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

				if (pbData)
					free(pbData) ;

				pbData = (_PBYTE) malloc(dwInsideDERBlobLength) ;
				memcpy(pbData, BaseDERBlob->pbData + 1+dwContentLengthBytes, dwInsideDERBlobLength) ;

				Class = (Type & 0xC0) >> 6 ;
				Encoding = (Type & 0x30) ? CONSTRUCTED : PRIMITIVE ;
				TagNumber = Type & 0x1F ;

				return ;
			}
			else
				Type = 0x00 ;
		}
	}

	NumberOfLengthBytes = 0 ;
	cbData = 0 ;
	pbData = _NULL ;
	Type = INVALID_DER_TYPE ;
	Class = UNIVERSAL ;
	Encoding = PRIMITIVE ;
	TagNumber = 0x00 ;

	return ;
}

// Set.cpp: implementation of the CSet class.
//
//////////////////////////////////////////////////////////////////////

#include "Set.h"
#include <stdlib.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSet::CSet()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
	IndefiniteLength = _FALSE ;
}

CSet::~CSet()
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
	IndefiniteLength = _FALSE ;
}

CSet::CSet(_DWORD i_cbData, _PBYTE i_pbData)
{
	IndefiniteLength = _FALSE ;
	this->fillit(SET, i_cbData, i_pbData) ;
	this->encode() ;
}

CSet::CSet(CSet &cset)
{
	IndefiniteLength = _FALSE ;
	copyinfo(SET, cset) ;
}

CSet::CSet(CBaseDER &cbaseder)
{
	IndefiniteLength = _FALSE ;
	if ( cbaseder.BaseDERBlob )
	{
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			this->fillit(SET, cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSet::CSet(CBaseDERCollection &cbasedercollection)
{
	IndefiniteLength = _FALSE ;
	if ( cbasedercollection.BaseDERBlob )
	{
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			this->fillit(SET, cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSet::CSet(_DWORD i_cbData, _PBYTE i_pbData, _BYTE i_cbIndefiniteLength)
{
	IndefiniteLength = i_cbIndefiniteLength ;
	this->fillit(SET, i_cbData, i_pbData) ;
	this->encode() ;
}

CSet::CSet(CBaseDER &cbaseder, _BYTE i_cbIndefiniteLength)
{
	IndefiniteLength = i_cbIndefiniteLength ;
	if ( cbaseder.BaseDERBlob )
	{
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			this->fillit(SET, cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSet::CSet(CBaseDERCollection &cbasedercollection, _BYTE i_cbIndefiniteLength)
{
	IndefiniteLength = i_cbIndefiniteLength ;
	if ( cbasedercollection.BaseDERBlob )
	{
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			this->fillit(SET, cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSet CSet::operator=(CSet &cset)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(SET, cset) ;

	return *this ;
}


CSet CSet::operator=(CBaseDERCollection &cbasedercollection)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	if ( cbasedercollection.BaseDERBlob )
	{
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			this->fillit(SET, cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
	return *this ;
}


CSet CSet::operator+=(CBaseDERCollection &cbasedercollection)
{
	_DWORD	cbRetData = this->cbData+(cbasedercollection.BaseDERBlob ? cbasedercollection.BaseDERBlob->cbData : 0) ;
	_PCHAR	pbRetData = (_PCHAR)malloc(cbRetData) ;

	if ( this->cbData != 0 )
		memcpy((void *)pbRetData, (const void *)this->pbData, this->cbData) ;

	if ( cbasedercollection.BaseDERBlob )
	{
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			memcpy((void *)(pbRetData+this->cbData), (const void *)cbasedercollection.BaseDERBlob->pbData, cbasedercollection.BaseDERBlob->cbData) ;

		if (BaseDERBlob)
			if (BaseDERBlob->cbData != 0x00000000)
				delete (BaseDERBlob) ;
		if ( pbData )
			free(pbData) ;
		cbData = 0 ;

		this->fillit(SET, cbRetData, pbRetData) ;
		this->encode2() ;
	}

	free(pbRetData) ;

	return *this ;
}


CSet CSet::operator=(CBaseDER &cbaseder)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	if ( cbaseder.BaseDERBlob )
	{
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			this->fillit(SET, cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
		this->encode2() ;
	}

	return *this ;
}


CSet CSet::operator+=(CBaseDER &cbaseder)
{
	_DWORD	cbRetData = this->cbData+(cbaseder.BaseDERBlob ? cbaseder.BaseDERBlob->cbData : 0) ;
	_PCHAR	pbRetData = (_PCHAR)malloc(cbRetData) ;

	if ( this->cbData != 0 )
		memcpy((void *)pbRetData, (const void *)this->pbData, this->cbData) ;

	if ( cbaseder.BaseDERBlob )
	{
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			memcpy((void *)(pbRetData+this->cbData), (const void *)cbaseder.BaseDERBlob->pbData, cbaseder.BaseDERBlob->cbData) ;

		if (BaseDERBlob)
			if (BaseDERBlob->cbData != 0x00000000)
				delete (BaseDERBlob) ;
		if ( pbData )
			free(pbData) ;
		cbData = 0 ;

		this->fillit(SET, cbRetData, pbRetData) ;
		this->encode2() ;
	}

	free(pbRetData) ;

	return *this ;
}


void CSet::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		if ( (Type = BaseDERBlob->pbData[0]) == SET )
		{
			GetLengthInfo(BaseDERBlob, &dwInsideDERBlobLength, &dwContentLengthBytes) ;

			if ( dwInsideDERBlobLength == 0 )
			{
				NumberOfLengthBytes = 1 ;
				cbData = 0 ;
				Encoding = CONSTRUCTED ;
				if (pbData)
					free(pbData) ;
				pbData = _NULL ;
				return ;
			}
			else if ( (dwInsideDERBlobLength+1+dwContentLengthBytes) > BaseDERBlob->cbData )
			{
				// You have got invalid InsideDERBlob length. So don't bother to decode.
				dwErrorCode = 0xFFFFFFFF ;
				return ;
			}

			NumberOfLengthBytes = dwContentLengthBytes ;
			cbData = dwInsideDERBlobLength ;

			Encoding = CONSTRUCTED ;

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

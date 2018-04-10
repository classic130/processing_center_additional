// Sequence.cpp: implementation of the CSequence class.
//
//////////////////////////////////////////////////////////////////////

#include "Sequence.h"
#include <stdlib.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSequence::CSequence()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
	IndefiniteLength = _FALSE ;
}

CSequence::~CSequence()
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

CSequence::CSequence(_DWORD i_cbData, _PBYTE i_pbData)
{
	IndefiniteLength = _FALSE ;
	this->fillit(SEQUENCE, i_cbData, i_pbData) ;
	this->encode() ;
}

CSequence::CSequence(CSequence &csequence)
{
	IndefiniteLength = _FALSE ;
	copyinfo(SEQUENCE, csequence) ;
}

CSequence::CSequence(CBaseDER &cbaseder)
{
	IndefiniteLength = _FALSE ;
	if ( cbaseder.BaseDERBlob )
	{
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			this->fillit(SEQUENCE, cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSequence::CSequence(CBaseDERCollection &cbasedercollection)
{
	IndefiniteLength = _FALSE ;
	if ( cbasedercollection.BaseDERBlob )
	{
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			this->fillit(SEQUENCE, cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSequence::CSequence(_DWORD i_cbData, _PBYTE i_pbData, _BYTE i_cbIndefiniteLength)
{
	IndefiniteLength = i_cbIndefiniteLength ;
	this->fillit(SEQUENCE, i_cbData, i_pbData) ;
	this->encode() ;
}

CSequence::CSequence(CBaseDER &cbaseder, _BYTE i_cbIndefiniteLength)
{
	IndefiniteLength = i_cbIndefiniteLength ;
	if ( cbaseder.BaseDERBlob )
	{
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			this->fillit(SEQUENCE, cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSequence::CSequence(CBaseDERCollection &cbasedercollection, _BYTE i_cbIndefiniteLength)
{
	IndefiniteLength = i_cbIndefiniteLength ;
	if ( cbasedercollection.BaseDERBlob )
	{
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			this->fillit(SEQUENCE, cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
}

CSequence CSequence::operator=(CSequence &csequence)
{
	if (BaseDERBlob)
		if (BaseDERBlob->cbData != 0x00000000)
			delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(SEQUENCE, csequence) ;

	return *this ;
}


CSequence CSequence::operator=(CBaseDERCollection &cbasedercollection)
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
			this->fillit(SEQUENCE, cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
		this->encode2() ;
	}
	return *this ;
}


CSequence CSequence::operator+=(CBaseDERCollection &cbasedercollection)
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

		this->fillit(SEQUENCE, cbRetData, pbRetData) ;
		this->encode2() ;
	}

	free(pbRetData) ;

	return *this ;
}


CSequence CSequence::operator=(CBaseDER &cbaseder)
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
			this->fillit(SEQUENCE, cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
		this->encode2() ;
	}

	return *this ;
}


CSequence CSequence::operator+=(CBaseDER &cbaseder)
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

		this->fillit(SEQUENCE, cbRetData, pbRetData) ;
		this->encode2() ;
	}

	free(pbRetData) ;

	return *this ;
}


void CSequence::decode()
{
	_DWORD		dwInsideDERBlobLength, dwContentLengthBytes ;

	if ( BaseDERBlob != _NULL )
	{
		if ( (Type = BaseDERBlob->pbData[0]) == SEQUENCE )
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


// Spooky.cpp: implementation of the CSpooky class.
//
//////////////////////////////////////////////////////////////////////

#include "Spooky.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpooky::CSpooky()
{
	cbData = 0x00000000 ;
	pbData = _NULL ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CSpooky::~CSpooky()
{
	if ( pbData )
		free (pbData) ;
	cbData = 0x00000000 ;
	NumberOfLengthBytes = 0x00000000 ;
	Type = INVALID_DER_TYPE ;
}

CSpooky::CSpooky(CSpooky &cspooky)
{
	copyinfo(SPOOKY, cspooky) ;
}

CSpooky::CSpooky(_DWORD i_cbData, _PBYTE i_pbData)
{
	_PBYTE	tmp ;
	tmp = (_PBYTE) malloc(i_cbData) ;
	memcpy(tmp, i_pbData, i_cbData) ;
	reverse(i_cbData, tmp) ;
	this->fillit(SPOOKY, i_cbData, tmp) ;
	free(tmp) ;
	this->encode() ;
}

CSpooky CSpooky::operator=(CSpooky &cspooky)
{
	if (BaseDERBlob->cbData != 0x00000000)
		delete (BaseDERBlob) ;
	if ( pbData )
		free(pbData) ;
	cbData = 0 ;

	copyinfo(SPOOKY, cspooky) ;

	return *this ;
}

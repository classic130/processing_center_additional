// BaseDERCollection.cpp: implementation of the CBaseDERCollection class.
//
//////////////////////////////////////////////////////////////////////

#include "BaseDERCollection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseDERCollection::CBaseDERCollection()
{
	BaseDERBlob = _NULL ;
}

CBaseDERCollection::~CBaseDERCollection()
{
	if (BaseDERBlob)
		delete BaseDERBlob ;
}

CBaseDERCollection::CBaseDERCollection(CBaseDERCollection &cbasedercollection)
{
	if ( cbasedercollection.BaseDERBlob )
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			BaseDERBlob = new CDERBlob(cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;
}

CBaseDERCollection CBaseDERCollection::operator=(CBaseDERCollection &cbasedercollection)
{
	if (BaseDERBlob)
		delete BaseDERBlob ;

	if ( cbasedercollection.BaseDERBlob )
		if ( cbasedercollection.BaseDERBlob->cbData && cbasedercollection.BaseDERBlob->pbData )
			BaseDERBlob = new CDERBlob(cbasedercollection.BaseDERBlob->cbData, cbasedercollection.BaseDERBlob->pbData) ;

	return *this ;
}

CBaseDERCollection CBaseDERCollection::operator=(CBaseDER &cbaseder)
{
	if (BaseDERBlob)
		delete BaseDERBlob ;

	if ( cbaseder.BaseDERBlob )
		if ( cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData )
			BaseDERBlob = new CDERBlob(cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;

	return *this ;
}

CBaseDERCollection CBaseDERCollection::operator+(CBaseDERCollection &cbasedercollection)
{
	_PCHAR	tmp ;
	_DWORD	dwtmp ;
	dwtmp = ((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData) + cbasedercollection.BaseDERBlob->cbData ;
	tmp = (_PCHAR) malloc(dwtmp) ;
	if ( this->BaseDERBlob != NULL )
		memcpy(tmp, this->BaseDERBlob->pbData, this->BaseDERBlob->cbData) ;
	memcpy(tmp + ((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData), cbasedercollection.BaseDERBlob->pbData, cbasedercollection.BaseDERBlob->cbData) ;

	if (BaseDERBlob)
		delete BaseDERBlob ;

	BaseDERBlob = new CDERBlob(dwtmp, tmp) ;

	if ( tmp )
		(*SIMDER_MemErase)(dwtmp, tmp) ;

	free(tmp) ;

	return *this ;
}

CBaseDERCollection CBaseDERCollection::operator+(CBaseDER &cbaseder)
{
	_PCHAR	tmp ;
	_DWORD  dwtmp ;
	dwtmp = ((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData) + cbaseder.BaseDERBlob->cbData ;
	tmp = (_PCHAR) malloc(dwtmp) ;
	if ( this->BaseDERBlob != NULL )
		memcpy(tmp, this->BaseDERBlob->pbData, this->BaseDERBlob->cbData) ;
	memcpy(tmp + ((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData), cbaseder.BaseDERBlob->pbData, cbaseder.BaseDERBlob->cbData) ;
	BaseDERBlob = new CDERBlob((((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData) + cbaseder.BaseDERBlob->cbData), tmp) ;

	if ( tmp )
		(*SIMDER_MemErase)(dwtmp, tmp) ;

	free(tmp) ;

	return *this ;
}
// Add encryption algorithm details to the beginning of list. artf39000
CBaseDERCollection CBaseDERCollection::operator%(CBaseDER &cbaseder)
{
	_PCHAR	tmp ;
	_DWORD  dwtmp ;
	dwtmp = ((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData) + cbaseder.BaseDERBlob->cbData ;
	tmp = (_PCHAR) malloc(dwtmp) ;
	if ( cbaseder.BaseDERBlob != NULL )
		memcpy(tmp, cbaseder.BaseDERBlob->pbData, cbaseder.BaseDERBlob->cbData) ;
	if ( this->BaseDERBlob != NULL )
	memcpy(tmp + ((cbaseder.BaseDERBlob) == NULL ? 0 : cbaseder.BaseDERBlob->cbData), this->BaseDERBlob->pbData, this->BaseDERBlob->cbData) ;
	BaseDERBlob = new CDERBlob((((this->BaseDERBlob) == NULL ? 0 : this->BaseDERBlob->cbData) + cbaseder.BaseDERBlob->cbData), tmp) ;

	if ( tmp )
		(*SIMDER_MemErase)(dwtmp, tmp) ;

	free(tmp) ;

	return *this ;
}

CBaseDERCollection::CBaseDERCollection(_DWORD cbData, _PBYTE pbData)
{
	if ( cbData && pbData )
		BaseDERBlob = new CDERBlob(cbData, pbData) ;
	else
		BaseDERBlob = _NULL ;
}

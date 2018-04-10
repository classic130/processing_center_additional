// BaseDER.cpp: implementation of the BaseDER class.
//
//////////////////////////////////////////////////////////////////////

#include "DataTypes.h"
#include "BaseDER.h"
#include "BaseDERCollection.h"
#include "UniversalInteger.h"
#include "VisibleString.h"
#include "PrintableString.h"
#include "OctetString.h"
#include "ObjectIdentifier.h"
#include "IA5String.h"
#include "BMPString.h"
#include "UTF8String.h"
#include "Boolean.h"
#include "BitString.h"
#include "TeletexString.h"
#include "Sequence.h"
#include "Set.h"
#include "TaggedValue.h"
#include "Null.h"
#include "UTCTime.h"
#include "GENERALIZEDTime.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseDER::CBaseDER()
{
	Type = INVALID_DER_TYPE ;
	pbData = _NULL ;
	cbData = 0x00000000 ;
	NumberOfLengthBytes = 0x00 ;
	BaseDERBlob = _NULL ;
	cbUnusedBits = 0x00 ;
	Class = UNIVERSAL ;
	Encoding = PRIMITIVE ;
	TagNumber = 0x00 ;
	IndefiniteLength = _FALSE ;
	dwErrorCode = 0x00000000 ;
}

CBaseDER::CBaseDER(CBaseDER &cbaseder)
{
	if ( (cbaseder.BaseDERBlob != _NULL) && (cbaseder.BaseDERBlob->cbData && cbaseder.BaseDERBlob->pbData) )
		BaseDERBlob = new CDERBlob(cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;

	Type = INVALID_DER_TYPE ;
	pbData = _NULL ;
	cbData = 0x00000000 ;
	NumberOfLengthBytes = 0x00 ;
	cbUnusedBits = 0x00 ;
	Class = UNIVERSAL ;
	Encoding = PRIMITIVE ;
	TagNumber = 0x00 ;
	IndefiniteLength = _FALSE ;
	dwErrorCode = 0x00000000 ;
}

CBaseDER::CBaseDER(CDERBlob &cderblob)
{
	if ( cderblob.cbData && cderblob.pbData )
		BaseDERBlob = new CDERBlob(cderblob.cbData, cderblob.pbData) ;
	Type = INVALID_DER_TYPE ;
	pbData = _NULL ;
	cbData = 0x00000000 ;
	NumberOfLengthBytes = 0x00 ;
	cbUnusedBits = 0x00 ;
	Class = UNIVERSAL ;
	Encoding = PRIMITIVE ;
	TagNumber = 0x00 ;
	IndefiniteLength = _FALSE ;
	dwErrorCode = 0x00000000 ;
}

CBaseDER::~CBaseDER()
{
	if ( pbData )
		(*SIMDER_MemErase)(cbData, pbData) ;

	if (pbData)
	{
		free (pbData) ;
		cbData = 0x00000000 ;
		pbData = _NULL ;
	}

	if ( BaseDERBlob != _NULL )
		if (BaseDERBlob->pbData != _NULL)
			delete (BaseDERBlob) ;
}

CBaseDERCollection CBaseDER::operator+(CBaseDER &cbaseder)
{
	_PCHAR	tmp ;
	tmp = (_PCHAR) malloc(this->BaseDERBlob->cbData + cbaseder.BaseDERBlob->cbData) ;
	if ( this->BaseDERBlob->pbData && this->BaseDERBlob->cbData )
		memcpy(tmp, this->BaseDERBlob->pbData, this->BaseDERBlob->cbData) ;
	if ( cbaseder.BaseDERBlob->pbData && cbaseder.BaseDERBlob->cbData )
		memcpy(tmp + this->BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData, cbaseder.BaseDERBlob->cbData) ;

	CBaseDERCollection	*cbasedercollection = new CBaseDERCollection(this->BaseDERBlob->cbData + cbaseder.BaseDERBlob->cbData, tmp) ;

	if ( tmp )
		(*SIMDER_MemErase)(this->BaseDERBlob->cbData + cbaseder.BaseDERBlob->cbData, tmp) ;

	free(tmp) ;

	return *cbasedercollection ;
}

void CBaseDER::reverse(_DWORD size, _PBYTE input)
{
  _DWORD	sizeby2 = size/2 ;
  _CHAR		tmpchar ;

  for (_DWORD i = 0 ; i < sizeby2 ; i++ )
  {
	  tmpchar = input[i] ;
	  input[i] = input[size-1-i] ;
	  input[size-1-i] = tmpchar ;
  }
}

void CBaseDER::encode()
{
	_DWORD	derlength ;
	if ( IndefiniteLength == _TRUE )
	{
		derlength = 2 + cbData + 2 ;
	}
	else
	{
		if ( NumberOfLengthBytes == 1 )
			derlength = 2 + cbData ;
		else
		{
			derlength = 1 + NumberOfLengthBytes + cbData ;
		}
	}

	_PBYTE	tmpbuffer = _NULL ;
	tmpbuffer = (_PBYTE)malloc(derlength) ;

	tmpbuffer[0] = Type ;

	if ( IndefiniteLength == _TRUE )
	{
		tmpbuffer[1] = 0x80 ;
	}
	else
	{
		if (NumberOfLengthBytes == 1)
			tmpbuffer[1] = cbData ;
		else
		{
			tmpbuffer[1] = 0x80 | (NumberOfLengthBytes-1) ;
			memcpy(&tmpbuffer[2], &cbData, 4) ; // This assumes that only 4 bytes will be used 
												// to define length of the encoded blob.
			reverse((NumberOfLengthBytes-1), &tmpbuffer[2]) ;
		}
	}

	if ( IndefiniteLength == _TRUE )
	{
		memcpy(tmpbuffer+2, pbData, cbData) ;
		tmpbuffer[2+cbData] = 0x00 ;
		tmpbuffer[2+cbData+1] = 0x00 ;
		reverse(cbData, tmpbuffer+2) ;
	}
	else
	{
		if( NumberOfLengthBytes == 1 )
		{
			memcpy(tmpbuffer+2, pbData, cbData) ;
			reverse(cbData, tmpbuffer+2) ;
		}
		else
		{
			memcpy(tmpbuffer+1+NumberOfLengthBytes, pbData, cbData) ;
			reverse(cbData, tmpbuffer+1+NumberOfLengthBytes) ;
		}
	}

	BaseDERBlob = new CDERBlob(derlength, tmpbuffer) ;

	if ( tmpbuffer )
		(*SIMDER_MemErase)(derlength, tmpbuffer) ;

	free(tmpbuffer) ;
}

void CBaseDER::encode2()
{
	_DWORD	derlength ;

	if ( IndefiniteLength == _TRUE )
	{
		derlength = 2 + cbData + 2 ;
	}
	else
	{
		if ( NumberOfLengthBytes == 1 )
			derlength = 2 + cbData ;
		else
		{
			derlength = 1 + NumberOfLengthBytes + cbData ;
		}
	}

	_PBYTE	tmpbuffer = _NULL ;
	tmpbuffer = (_PBYTE)malloc(derlength) ;

	tmpbuffer[0] = Type ;

	if ( IndefiniteLength == _TRUE )
	{
		tmpbuffer[1] = 0x80 ;
	}
	else
	{
		if (NumberOfLengthBytes == 1)
			tmpbuffer[1] = cbData ;
		else
		{
			tmpbuffer[1] = 0x80 | (NumberOfLengthBytes-1) ;
			memcpy(&tmpbuffer[2], &cbData, 4) ; // This assumes that only 4 bytes will be used 
												// to define length of the encoded blob.
			reverse((NumberOfLengthBytes-1), &tmpbuffer[2]) ;
		}
	}

	if ( IndefiniteLength == _TRUE )
	{
		memcpy(tmpbuffer+2, pbData, cbData) ;
		tmpbuffer[2+cbData] = 0x00 ;
		tmpbuffer[2+cbData+1] = 0x00 ;
		//reverse(cbData, tmpbuffer+2) ;
	}
	else
	{
		if( NumberOfLengthBytes == 1 )
		{
			memcpy(tmpbuffer+2, pbData, cbData) ;
			//reverse(cbData, tmpbuffer+2) ;
		}
		else
		{
			memcpy(tmpbuffer+1+NumberOfLengthBytes, pbData, cbData) ;
			//reverse(cbData, tmpbuffer+1+NumberOfLengthBytes) ;
		}
	}

	BaseDERBlob = new CDERBlob(derlength, tmpbuffer) ;

	if ( tmpbuffer )
		(*SIMDER_MemErase)(derlength, tmpbuffer) ;

	free(tmpbuffer) ;
}

void CBaseDER::fillit(_BYTE i_Type, _DWORD i_cbData, _PBYTE i_pbData)
{
	if ( IndefiniteLength == _TRUE )
		NumberOfLengthBytes = 1 ;
	else
	{
		if ( i_cbData < 0x00000080 )
			NumberOfLengthBytes = 1 ; // Use short length form
		else 
		{
			// Use long length form
			_DWORD	dwNumberOfBytesNeeded = 0 ;

			if ( i_cbData & 0xFF000000 )
				dwNumberOfBytesNeeded = 4 ;
			else if ( i_cbData & 0x00FF0000 )
				dwNumberOfBytesNeeded = 3 ;
			else if ( i_cbData & 0x0000FF00 )
				dwNumberOfBytesNeeded = 2 ;
			else
				dwNumberOfBytesNeeded = 1 ;

			NumberOfLengthBytes = 1 + dwNumberOfBytesNeeded ;
		}
	}

	if( (pbData = (_PBYTE) malloc(i_cbData)) != _NULL )
	{
		memcpy(pbData, i_pbData, i_cbData) ;
		cbData = i_cbData ;
		Type = i_Type ;
	}
	else
	{
		NumberOfLengthBytes = 0x00000000 ;
		cbData = 0x00000000 ;
		pbData = _NULL ;
		Type = INVALID_DER_TYPE ;
		cbUnusedBits = 0x00 ;
		Class = UNIVERSAL ;
		Encoding = PRIMITIVE ;
		TagNumber = 0x00 ;
		IndefiniteLength = _FALSE ;
	}
}

void CBaseDER::copyinfo(_BYTE i_Type, CBaseDER &cbaseder)
{
	if ( cbaseder.BaseDERBlob )
		BaseDERBlob = new CDERBlob(cbaseder.BaseDERBlob->cbData, cbaseder.BaseDERBlob->pbData) ;
	else
		BaseDERBlob = _NULL ;

	if( (pbData = (_PBYTE) malloc(cbaseder.cbData)) != _NULL )
	{
		memcpy(pbData, cbaseder.pbData, cbaseder.cbData) ;
		cbData = cbaseder.cbData ;
		NumberOfLengthBytes = cbaseder.NumberOfLengthBytes ;
		Type = i_Type ;
		cbUnusedBits = cbaseder.cbUnusedBits ;
		Class = cbaseder.Class ;
		Encoding = cbaseder.Encoding ;
		TagNumber = cbaseder.TagNumber ;
		IndefiniteLength = cbaseder.IndefiniteLength ;
	}
	else
	{
		NumberOfLengthBytes = 0x00000000 ;
		cbData = 0x00000000 ;
		pbData = _NULL ;
		Type = INVALID_DER_TYPE ;
		cbUnusedBits = 0x00 ;
		Class = UNIVERSAL ;
		Encoding = PRIMITIVE ;
		TagNumber = 0x00 ;
		IndefiniteLength = _FALSE ;
	}
}

_BOOL	CBaseDER::GetLengthInfo(CDERBlob *i_DERBlob, _DWORD *insideDERBlobLength, _DWORD *ContentLengthBytes)
{
	if (i_DERBlob->pbData[1] & 0x80)
	{
		if ( (i_DERBlob->pbData[1] & 0x7F) == 0 )
		{
			// You come here if it's Indefinite Length encoding.
			// You cannot check if this Indefinite length encoded blob is indeed terminated
			// with 0x00 0x00 sequence. So just assume it.
			// For example, in a case where the indefinite length encoded sequence is followed
			// by a base primitive, you cannot exactly determine where the 0x00 0x00 combination
			// is and therefore cannot determine exactly the length of the Indefinite length 
			// encoded blob.

			*insideDERBlobLength = i_DERBlob->cbData - 2 ;	// 2 corresponds to the Identifier Octet
															// and the 0x80 that follows it.
			*ContentLengthBytes = 1 ;
			IndefiniteLength = _TRUE ;
			return _TRUE ;
		}
		else
		// There are multiple octets specifying the "Content length"
		if ( (i_DERBlob->pbData[1] & 0x7F) == 1 )
		{
			*insideDERBlobLength = (_DWORD)i_DERBlob->pbData[2] ;
			*ContentLengthBytes = 2 ;
			IndefiniteLength = _FALSE ;
		}
		else if ( (i_DERBlob->pbData[1] & 0x7F) == 2 )
		{
			*insideDERBlobLength = (_DWORD)(i_DERBlob->pbData[2] << 8) |
								(_DWORD)(i_DERBlob->pbData[3]) ;
			*ContentLengthBytes = 3 ;
			IndefiniteLength = _FALSE ;
		}
		else if ( (i_DERBlob->pbData[1] & 0x7F) == 3 )
		{
			*insideDERBlobLength = (_DWORD)(i_DERBlob->pbData[2] << 16) |
								(_DWORD)(i_DERBlob->pbData[3] << 8) |
								(_DWORD)(i_DERBlob->pbData[4]) ;
			*ContentLengthBytes = 4 ;
			IndefiniteLength = _FALSE ;
		}
		else if ( (i_DERBlob->pbData[1] & 0x7F) == 4 )
		{
			*insideDERBlobLength = (_DWORD)(i_DERBlob->pbData[2] << 24) |
								(_DWORD)(i_DERBlob->pbData[3] << 16) |
								(_DWORD)(i_DERBlob->pbData[4] << 8) |
								(_DWORD)(i_DERBlob->pbData[5]) ;
			*ContentLengthBytes = 5 ;
			IndefiniteLength = _FALSE ;
		}
		else
		{
			// This means there are more than 4 octets specifying
			// the "Content Length". Presently, I don't handle this
			// case.

			// BUT

			// You can reach here is you are handling Indefinite length encoding.
			// More on this at a later point of time ....

			return _FALSE ;
		}

		// Check if the total length of the der blob is just
		// two octets more than the length mentioned in the
		// "Content length" octets
		if ( (*insideDERBlobLength + 2) != i_DERBlob->cbData )
		{
			return _FALSE ;
		}
	}
	else
	{
		// Check if the total length of the der blob is just
		// two octets more than the length mentioned in the
		// "Content length" octet
		if ( ((_DWORD)(i_DERBlob->pbData[1]) + 2) != i_DERBlob->cbData )
		{
			*insideDERBlobLength = i_DERBlob->pbData[1] ;
			*ContentLengthBytes = 1 ;
			IndefiniteLength = _FALSE ;
			return _FALSE ;
		}

		// Only one octet specifying the "Content length"
		*insideDERBlobLength = i_DERBlob->pbData[1] ;
		*ContentLengthBytes = 1 ;
		IndefiniteLength = _FALSE ;
	}

	return _TRUE ;
}


void CBaseDER::decode()
{
	_CHAR		lIdentifier, lPrimitiveIdentifier ;
	_DWORD		lClass ;

	lIdentifier = BaseDERBlob->pbData[0] ;
	lPrimitiveIdentifier = lIdentifier & 0x1F ;
	lClass = lIdentifier & 0xC0 ;

	if ( lPrimitiveIdentifier == UNIVERSAL_INTEGER && !lClass )
		((CUniversalInteger *)this)->decode() ;
	else if ( lPrimitiveIdentifier == VISIBLE_STRING && !lClass )
		((CVisibleString *)this)->decode() ;
	else if ( lPrimitiveIdentifier == PRINTABLE_STRING && !lClass )
		((CPrintableString *)this)->decode() ;
	else if ( lPrimitiveIdentifier == TELETEX_STRING && !lClass )
		((CTeletexString *)this)->decode() ;
	else if ( lPrimitiveIdentifier == OCTET_STRING && !lClass )
		((COctetString *)this)->decode() ;
	else if ( lPrimitiveIdentifier == OBJECT_IDENTIFIER && !lClass )
		((CObjectIdentifier *)this)->decode() ;
	else if ( lPrimitiveIdentifier == IA5_STRING && !lClass )
		((CIA5String *)this)->decode() ;
	else if ( lPrimitiveIdentifier == UTF8_STRING && !lClass )
		((CUTF8String *)this)->decode() ;
	else if ( lPrimitiveIdentifier == BOOLEAN && !lClass )
		((CBoolean *)this)->decode() ;
	else if ( lPrimitiveIdentifier == BMP_STRING && !lClass )
		((CBMPString *)this)->decode() ;
	else if ( lPrimitiveIdentifier == BIT_STRING && !lClass )
		((CBitString *)this)->decode() ;
	else if ( lPrimitiveIdentifier == NULL_DER_TYPE && !lClass )
		((CNull *)this)->decode() ;
	else if ( lPrimitiveIdentifier == UTC_TIME && !lClass )
		((CUTCTime *)this)->decode() ;
	else if ( lPrimitiveIdentifier == GENERALIZED_TIME && !lClass )
		((CGENERALIZEDTime *)this)->decode() ;
	else if ( lIdentifier == SEQUENCE )
		((CSequence *)this)->decode() ;
	else if ( lIdentifier == SET )
		((CSet *)this)->decode() ;
	else if ( lIdentifier & 0xC0 )
		((CTaggedValue *)this)->decode() ;

	return ;
}

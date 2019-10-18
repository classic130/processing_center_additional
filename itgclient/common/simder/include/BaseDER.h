// BaseDER.h: interface for the BaseDER class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BASEDER_H_INCLUDED_)
#define _BASEDER_H_INCLUDED_


#include	"DERBlob.h"
#include	"DataTypes.h"

class CBaseDERCollection ;

class CBaseDER
{
public:
	CBaseDER() ;
	CBaseDER(CBaseDER &cbaseder) ;
	CBaseDER(CDERBlob &cderblob) ;
	virtual		~CBaseDER();
	CBaseDERCollection operator+(CBaseDER &cbaseder) ;

	_PBYTE		pbData ;		// Non-encoded information pointer
	_DWORD		cbData ;		// Non-encoded information size

	CDERBlob	*BaseDERBlob ;	// Encoded blob.
	_BYTE		cbUnusedBits ;
	_BYTE		Class ;
	_BYTE		Encoding ;
	_BYTE		TagNumber ;		// This gets used only when
								// you are using Class = APPLICATION or CONTEXT_SPECIFIC
	_BYTE		IndefiniteLength ; // Used to perform indefinite length encoding.

	void		decode() ;

	_BYTE		Type ;
	_BYTE		NumberOfLengthBytes ;	// If this is 1, then we are using Short form for encoding the length
										// If this is more than 1, then we are using Long form for encoding the length.
										// Also, if NumberOfLengthBytes is > 1, then NumberOfLengthBytes includes the
										// length of initial octect (whose MSB is set to 1) plus the octets that make
										// the length
	_DWORD		dwErrorCode ;

protected:
	void reverse(_DWORD size, _PBYTE input) ;
	void encode(), encode2() ;
	void fillit(_BYTE i_Type, _DWORD i_cbData, _PBYTE i_pbData) ;
	void copyinfo(_BYTE i_Type, CBaseDER &cbaseder) ;
	_BOOL GetLengthInfo(CDERBlob *i_DERBlob, _DWORD *insideDERBlobLength, _DWORD *ContentLengthBytes) ;

};

#endif // !defined(_BASEDER_H_INCLUDED_)

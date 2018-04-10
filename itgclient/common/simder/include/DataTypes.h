// DataTypes.h: interface for the Integer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DATATYPES_H_INCLUDED_)
#define _DATATYPES_H_INCLUDED_

typedef		unsigned char		_CHAR, *_PCHAR ;
typedef		unsigned char		_BYTE, *_PBYTE ;
typedef		unsigned short		_WORD, *_PWORD ;
typedef		unsigned int		_DWORD, *_PDWORD ;
typedef		int					INT4, *PINT4 ;

#ifndef FALSE
enum _BOOL
{
	_FALSE = 0,
	_TRUE = 1
} ;
#else
enum _BOOL
{
	_FALSE = FALSE,
	_TRUE = TRUE
} ;
#endif

#define		_LITTLEENDIAN		0x00
#define		_BIGENDIAN			0x01

#define		_NULL				0x00000000

// Type of Encoding
#define		PRIMITIVE			0x00
#define		CONSTRUCTED			0x01

// Class values
#define		UNIVERSAL			0x00
#define		APPLICATION			0x01
#define		CONTEXT_SPECIFIC	0x02
#define		PRIVATE				0x03

/*
<---------- Identifier Octet ----------->
    8    7    6    5    4    3    2    1
+----+----+----+----+----+----+----+----+
|  Class  | P/C|      Number of Tag     |
+----+----+----+----+----+----+----+----+
             |
			 V
			 +-- 0 : Primitive
			 +-- 1 : Constructed

  Encoding of Class of Tag

+-------------------------+------+
| Class				Bit 8	Bit 7|
+-------------------------+------+
| Universal			0		0    |
| Application		0		1    |
| Context-specific	1		0    |
| Private			1		1    |
+-------------------------+------+
*/

// Base DER Types
// This is in fact the "Number of Tag" portion of the first "Identifier Octect"
#define		INVALID_DER_TYPE	0x00
#define		BOOLEAN				0x01
#define		UNIVERSAL_INTEGER	0x02
#define		BIT_STRING			0x03
#define		OCTET_STRING		0x04
#define		NULL_DER_TYPE		0x05
#define		OBJECT_IDENTIFIER	0x06
#define		UTF8_STRING			0x0C
#define		PRINTABLE_STRING	0x13
#define		TELETEX_STRING		0x14
#define		IA5_STRING			0x16
#define		UTC_TIME			0x17
#define		GENERALIZED_TIME	0x18
#define		VISIBLE_STRING		0x1A
#define		BMP_STRING		0x1E

//Derived DER Types
#define		SEQUENCE			0x30
#define		SET					0x31
#define		IMPLICIT			0xA0

extern _DWORD		(*SIMDER_MemErase) (_DWORD cbdata, _PBYTE pbdata) ;

// Define the number of bytes used to represent a UNICODE character
#define _SIZEOFUNICODE 2

#endif // !defined(_DATATYPES_H_INCLUDED_)

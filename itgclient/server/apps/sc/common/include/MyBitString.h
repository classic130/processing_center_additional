#if !defined(_MY_BITSTRING_H_INCLUDED_)
#define _MY_BITSTRING_H_INCLUDED_

#include "BitString.h"

class CMyBitString : public CBitString
{
public:
	CMyBitString(_DWORD i_cbUnusedBits, _DWORD i_cbData, _PBYTE i_pbData) ;
};

#endif // !defined(_BITSTRING_H_INCLUDED_)

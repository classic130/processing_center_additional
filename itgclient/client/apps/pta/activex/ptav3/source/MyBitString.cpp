#include "stdafx.h"
#include "..\Include\MyBitString.h"

CMyBitString::CMyBitString(_DWORD i_cbUnusedBits, _DWORD i_cbData, _PBYTE i_pbData)
{
	_PBYTE	tmp ;
	tmp = (_PBYTE) new _PBYTE[i_cbData+1] ;
	memcpy(tmp+1, i_pbData, i_cbData) ;
	if ( i_cbUnusedBits >= 0 && i_cbUnusedBits <= 7 )
		tmp[0] = (_BYTE) i_cbUnusedBits ;
	else
		return ;
	tmp[i_cbData] = tmp[i_cbData] & (0xFF << i_cbUnusedBits) ;
	this->fillit(BIT_STRING, i_cbData+1, tmp) ;
	delete[](tmp) ;
	this->encode2() ;
}
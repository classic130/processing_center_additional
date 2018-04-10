#if !defined(_MY_UNIVERSALINTEGER_H_INCLUDED_)
#define _MY_UNIVERSALINTEGER_H_INCLUDED_

#include "UniversalInteger.h"

class CMyUniversalInteger : public CUniversalInteger
{
public:
	CMyUniversalInteger(_DWORD i_cbData, _PBYTE i_pbData);
	CMyUniversalInteger(_DWORD i_dwData);
};

#endif // !defined(_UNIVERSALINTEGER_H_INCLUDED_)

#if !defined(_MY_OCTETSTRING_H_INCLUDED_)
#define _MY_OCTETSTRING_H_INCLUDED_

#include "OctetString.h"

class CMyOctetString : public COctetString
{
public:
	CMyOctetString(_DWORD i_cbData, _PBYTE i_pbData) ;
};

#endif // !defined(_OCTETSTRING_H_INCLUDED_)

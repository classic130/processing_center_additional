// PrintableString.h: interface for the CPrintableString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PRINTABLESTRING_H_INCLUDED_)
#define _PRINTABLESTRING_H_INCLUDED_

#include "BaseDER.h"

class CPrintableString : public CBaseDER
{
public:
	CPrintableString();
	virtual ~CPrintableString();

	CPrintableString(CPrintableString &cprintablestring) ;
	CPrintableString(_DWORD i_cbData, _PBYTE i_pbData) ;
	CPrintableString operator=(CPrintableString &cprintablestring) ;

	void decode() ;
};

#endif // !defined(_PRINTABLESTRING_H_INCLUDED_)

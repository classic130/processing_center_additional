// IA5String.h: interface for the CIA5String class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_IA5STRING_H_INCLUDED_)
#define _IA5STRING_H_INCLUDED_

#include "BaseDER.h"

class CIA5String : public CBaseDER
{
public:
	CIA5String();
	virtual ~CIA5String();

	CIA5String(CIA5String &cia5string) ;
	CIA5String(_DWORD i_cbData, _PBYTE i_pbData) ;
	CIA5String operator=(CIA5String &cia5string) ;

	void decode() ;
};

#endif // !defined(_IA5STRING_H_INCLUDED_)

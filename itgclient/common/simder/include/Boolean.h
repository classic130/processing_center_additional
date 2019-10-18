// Boolean.h: interface for the CBoolean class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_BOOLEAN_H_INCLUDED_)
#define _BOOLEAN_H_INCLUDED_

#include "BaseDER.h"

class CBoolean : public CBaseDER
{
public:
	CBoolean();
	virtual ~CBoolean();

	CBoolean(CBoolean &cbollean) ;
	CBoolean(_BYTE cValue) ;
	CBoolean operator=(CBoolean &cbollean) ;

	void decode() ;
};

#endif // !defined(_BOOLEAN_H_INCLUDED_)

// GENERALIZEDTime.h: interface for the CGENERALIZEDTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_GENERALIZEDTIME_H_INCLUDED_)
#define _GENERALIZEDTIME_H_INCLUDED_

#include "BaseDER.h"

class CGENERALIZEDTime : public CBaseDER
{
public:
	CGENERALIZEDTime();
	virtual ~CGENERALIZEDTime();

	CGENERALIZEDTime(CGENERALIZEDTime &cvisiblestring) ;
	CGENERALIZEDTime(_DWORD i_cbData, _PBYTE i_pbData) ;
	CGENERALIZEDTime operator=(CGENERALIZEDTime &cvisiblestring) ;

	void decode() ;
};

#endif // !defined(_GENERALIZEDTIME_H_INCLUDED_)

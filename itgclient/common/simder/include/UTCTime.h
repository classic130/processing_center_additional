// UTCTime.h: interface for the CVisibleString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UTCTIME_H_INCLUDED_)
#define _UTCTIME_H_INCLUDED_

#include "BaseDER.h"

class CUTCTime : public CBaseDER
{
public:
	CUTCTime();
	virtual ~CUTCTime();

	CUTCTime(CUTCTime &cvisiblestring) ;
	CUTCTime(_DWORD i_cbData, _PBYTE i_pbData) ;
	CUTCTime operator=(CUTCTime &cvisiblestring) ;

	void decode() ;
};

#endif // !defined(_UTCTIME_H_INCLUDED_)

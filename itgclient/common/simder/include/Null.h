// Null.h: interface for the CNull class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_NULL_H_INCLUDED_)
#define _NULL_H_INCLUDED_

#include "BaseDER.h"
#include "DataTypes.h"

class CNull : public CBaseDER
{
public:
	CNull();
	virtual ~CNull();

	CNull(CNull &cnull) ;
	CNull operator=(CNull &cnull) ;

	void decode() ;
};

#endif // !defined(_NULL_H_INCLUDED_)

// TaggedValue.h: interface for the CTaggedValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_TAGGEDVALUE_H_INCLUDED_)
#define _TAGGEDVALUE_H_INCLUDED_

#include "BaseDER.h"
#include "BaseDERCollection.h"

class CTaggedValue : public CBaseDER
{
public:
	CTaggedValue();
	virtual ~CTaggedValue();

	CTaggedValue(CTaggedValue &ctaggedvalue) ;

	CTaggedValue(_BYTE Class, _BYTE Encoding, _BYTE TagNumber, _BYTE Implicit, CBaseDER Contents) ;
	CTaggedValue(_BYTE Class, _BYTE Encoding, _BYTE TagNumber, _BYTE Implicit, _BYTE i_cbIndefiniteLength, CBaseDER Contents) ;

	// Use this constructor to create constructed encoding blobs for base primitives.
	CTaggedValue(_BYTE Class, _BYTE Encoding, _BYTE TagNumber, _BYTE i_cbIndefiniteLength, CBaseDERCollection Contents) ;

	CTaggedValue operator=(CTaggedValue &ctaggedvalue) ;

	void decode() ;
};

#endif // !defined(_TAGGEDVALUE_H_INCLUDED_)

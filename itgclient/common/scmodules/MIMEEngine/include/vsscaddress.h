#ifndef _VSSCADDRESS
#define _VSSCADDRESS

#include "fieldbody.h"

class VSSCAddress : public VSSCFieldBody
{
public:	
    virtual ~VSSCAddress();

    _BOOL IsMailbox() const;
    _BOOL IsGroup() const;
	_BOOL IsValid() const;
    
protected:
	VSSCAddress();
    VSSCAddress(const VSSCAddress& adAddress);
    VSSCAddress(const VSSCString& vsscStr, VSSCMsgComponent* Parent=0);

	const VSSCAddress& operator = (const VSSCAddress& adAddress);


	_BOOL m_bIsValid;

};



#endif // _VSSCADDRESS
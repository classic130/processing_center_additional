#ifndef _VSSCMESSAGE
#define _VSSCMESSAGE

#include "vsscentity.h"

class VSSCMessage : public VSSCEntity
{
public:
	VSSCMessage();
	VSSCMessage(const VSSCMessage& Message);
	VSSCMessage(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);

	virtual ~VSSCMessage();

	const VSSCMessage& operator = (const VSSCMessage& Message);

	virtual VSSCMsgComponent* Clone() const;
	
	static VSSCMessage* NewMessage(const VSSCString& vsscString, VSSCMsgComponent* Parent);

};


#endif // _VSSCMESSAGE
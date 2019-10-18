#include "vsscmsgcmp.h"
#include "vsscentity.h"
#include "vsscmessage.h"

VSSCMessage :: VSSCMessage()
: VSSCEntity()
{
	m_ComponentType = eCtMessage;

}

VSSCMessage :: VSSCMessage(const VSSCMessage& Message)
: VSSCEntity(Message)
{
	m_ComponentType = eCtMessage;
}

VSSCMessage :: VSSCMessage(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCEntity(vsscString, Parent)
{
	m_ComponentType = eCtMessage;
}

VSSCMessage :: ~VSSCMessage()
{

}

const VSSCMessage& VSSCMessage :: operator = (const VSSCMessage& Message)
{
	if(&Message == this)
		return *this;
	VSSCEntity :: operator = (Message);
	return *this;

}

VSSCMsgComponent* VSSCMessage :: Clone() const
{
	return new VSSCMessage(*this);
}
	
VSSCMessage* VSSCMessage :: NewMessage(const VSSCString& vsscString, VSSCMsgComponent* Parent)
{
	return new VSSCMessage(vsscString, Parent);
}

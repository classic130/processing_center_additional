#include "vsscbodypart.h"
#include "vsscmsgcmp.h"


VSSCBodyPart :: VSSCBodyPart()
: VSSCEntity()
{
	m_ComponentType = eCtBodyPart;
}

VSSCBodyPart :: VSSCBodyPart(const VSSCBodyPart& BodyPart)
: VSSCEntity(BodyPart)
{
	m_ComponentType = eCtBodyPart;
}

VSSCBodyPart :: VSSCBodyPart(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCEntity(vsscString, Parent)
{
	m_ComponentType = eCtBodyPart;
}

VSSCBodyPart :: ~VSSCBodyPart()
{

}

VSSCMsgComponent* VSSCBodyPart :: Clone() const
{
	return new VSSCBodyPart(*this);
}

const VSSCBodyPart& VSSCBodyPart :: operator = (const VSSCBodyPart& BodyPart)
{
	if(&BodyPart == this)
		return *this;
	VSSCEntity :: operator = (BodyPart);
	return *this;
}

VSSCBodyPart* VSSCBodyPart :: NewBodyPart(const VSSCString& vsscString,
									 VSSCMsgComponent* Parent)
{
	return new VSSCBodyPart(vsscString, Parent);
}

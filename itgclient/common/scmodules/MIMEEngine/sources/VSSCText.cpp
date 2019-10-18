#include "vssctext.h"

VSSCText :: VSSCText()
{
	m_ComponentType = eCtText;
}

VSSCText :: VSSCText(const VSSCText& Text)
: VSSCFieldBody(Text)
{
	m_ComponentType = eCtText;
}

VSSCText :: VSSCText(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCFieldBody(vsscString, Parent)
{	
	m_ComponentType = eCtText;
}

VSSCText :: ~VSSCText()
{

}

// Does nothing - the m_vsscString contains the body
void VSSCText :: Parse()
{

}

// Does nothing - the m_vsscString contains the body
void VSSCText :: Assemble()
{

}

VSSCMsgComponent* VSSCText :: Clone() const
{
	return new VSSCText(*this);
}

VSSCText* VSSCText :: NewText(const VSSCString& vsscString, VSSCMsgComponent* Parent)
{
	return new VSSCText(vsscString, Parent);
}

const VSSCText& VSSCText :: operator = (const VSSCText& Text)
{
	if(this != &Text)
	{
		VSSCFieldBody :: operator = (Text);
	}
	return *this;
}
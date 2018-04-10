#include "vsscmsgcmp.h"

VSSCMsgComponent :: VSSCMsgComponent()
{
	m_ComponentType = eCtMessageComponent;
	m_Parent = 0;
}

VSSCMsgComponent :: VSSCMsgComponent(const VSSCMsgComponent& vsscMsgCmp)
:m_vsscString(vsscMsgCmp.m_vsscString)
{
	m_ComponentType = eCtMessageComponent;
	m_Parent = 0;

}

VSSCMsgComponent :: 	VSSCMsgComponent(const VSSCString& vsscString, VSSCMsgComponent *Parent=0)
:m_vsscString(vsscString)
{
	m_ComponentType = eCtMessageComponent;
	m_Parent = Parent;

}

VSSCMsgComponent :: ~VSSCMsgComponent()
{

}

void VSSCMsgComponent :: SetString(const VSSCString& vsscString)
{
	m_vsscString = vsscString;
}

void VSSCMsgComponent :: SetString(const char* szString)
{
	m_vsscString = szString;
}

const VSSCString& VSSCMsgComponent :: GetString() const
{
	return m_vsscString;
}

int VSSCMsgComponent :: GetCmpType()
{
	return m_ComponentType;
}


const VSSCMsgComponent& VSSCMsgComponent :: operator = (const VSSCMsgComponent& vsscMsgCmp)
{
	m_vsscString = vsscMsgCmp.m_vsscString;
	return *this;
}

VSSCMsgComponent* VSSCMsgComponent :: GetParent()
{
	return m_Parent;
}

void VSSCMsgComponent :: SetParent(VSSCMsgComponent *Parent)
{
	m_Parent = Parent;
}
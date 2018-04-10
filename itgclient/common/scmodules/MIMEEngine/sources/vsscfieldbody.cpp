#include "fieldbody.h"

VSSCFieldBody :: VSSCFieldBody()
{
	m_bFolding = _TRUE;
}


VSSCFieldBody :: VSSCFieldBody(const VSSCFieldBody& fbFieldBody)
:VSSCMsgComponent(fbFieldBody)
{
	m_bFolding = _TRUE;
}

VSSCFieldBody :: VSSCFieldBody(const VSSCString& vsscString, VSSCMsgComponent* Parent)
:VSSCMsgComponent(vsscString, Parent)
{
	m_bFolding = _TRUE;
}


VSSCFieldBody :: ~VSSCFieldBody()
{

}



const VSSCFieldBody& VSSCFieldBody ::  operator = (const VSSCFieldBody& fbFieldBody)
{
	if (this == &fbFieldBody) return *this;
		VSSCMsgComponent::operator = (fbFieldBody);
    
    return *this;
}


void VSSCFieldBody :: SetFolding(_BOOL bFolding)
{
	m_bFolding = bFolding;
}

_BOOL VSSCFieldBody :: IsFolding() const
{
	return m_bFolding;

}
    
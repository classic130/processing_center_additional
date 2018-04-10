#include "vsscaddress.h"

VSSCAddress :: VSSCAddress()
{
	m_bIsValid = _FALSE;
    m_ComponentType = eCtAddress;

}

VSSCAddress :: VSSCAddress(const VSSCAddress& adAddress)
:VSSCFieldBody(adAddress)
{
	m_bIsValid = _FALSE;
    m_ComponentType = eCtAddress;
}

VSSCAddress :: VSSCAddress(const VSSCString& vsscStr, VSSCMsgComponent* Parent)
:VSSCFieldBody(vsscStr, Parent)
{
	m_bIsValid = _FALSE;
    m_ComponentType = eCtAddress;
}

VSSCAddress :: ~VSSCAddress()
{

}

const VSSCAddress& VSSCAddress :: operator = (const VSSCAddress& adAddress)
{
	if(this == &adAddress)
		return *this;

	VSSCFieldBody :: operator = (adAddress);
	m_bIsValid = adAddress.m_bIsValid;
	return *this;

}

_BOOL VSSCAddress :: IsMailbox() const
{
	_BOOL bRet;
	bRet = (m_ComponentType == eCtMailbox) ? _TRUE : _FALSE;
	return bRet;
}

_BOOL VSSCAddress :: IsGroup() const
{
	_BOOL bRet;
	bRet = (m_ComponentType == eCtGroup) ? _TRUE : _FALSE;
	return bRet;

}

_BOOL VSSCAddress :: IsValid() const
{
	return m_bIsValid;
}
#include "fieldbody.h"
#include "vsscmechanism.h"
#include "vsscenum.h"

//constructors
VSSCMechanism :: VSSCMechanism()
{
	m_nCteEnum = VSSCEnumMime :: eCteNull;
	m_ComponentType = eCtMechanism;
}

VSSCMechanism :: VSSCMechanism(const VSSCMechanism& Mechnsm)
: VSSCFieldBody(Mechnsm)
{
	m_nCteEnum = Mechnsm.m_nCteEnum;
	m_ComponentType = Mechnsm.m_ComponentType;
}

VSSCMechanism :: VSSCMechanism(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCFieldBody(vsscString, Parent)
{
	m_nCteEnum = VSSCEnumMime :: eCteNull;
	m_ComponentType = eCtMechanism;
}

VSSCMechanism :: ~VSSCMechanism()
{

}

VSSCMsgComponent* VSSCMechanism :: Clone() const
{
	return new VSSCMechanism(*this);
}

VSSCMechanism* ::VSSCMechanism :: NewMechanism(const VSSCString& vsscString,
			VSSCMsgComponent* Parent)
{
	return new VSSCMechanism(vsscString, Parent);
}

int VSSCMechanism :: GetAsEnum() const
{
	return m_nCteEnum;
}

void VSSCMechanism :: SetFromEnum(int nCte)
{
	m_nCteEnum = nCte;
	_EnumToString();

}

void VSSCMechanism :: Parse()
{
	_StringToEnum();
}

void VSSCMechanism :: Assemble()
{
	// does nothing.
	
}

const VSSCMechanism& VSSCMechanism :: operator = (const VSSCMechanism& Mechnsm)
{
	if(this != &Mechnsm)
	{
		VSSCFieldBody :: operator = (Mechnsm);
		m_nCteEnum = Mechnsm.m_nCteEnum;
	}
	return *this;
}


void VSSCMechanism :: _EnumToString()
{
	switch (m_nCteEnum) 
	{
    case VSSCEnumMime :: eCte7bit:
        m_vsscString = "7bit";
        break;
    case VSSCEnumMime :: eCte8bit:
        m_vsscString = "8bit";
        break;
    case VSSCEnumMime :: eCteBinary:
        m_vsscString = "binary";
        break;
    case VSSCEnumMime :: eCteBase64:
        m_vsscString = "base64";
        break;
    case VSSCEnumMime :: eCteQuotedPrintable:
        m_vsscString = "quoted-printable";
        break;
    }
}

void VSSCMechanism :: _StringToEnum()
{
	if(m_vsscString.Length() == 0)
	{
		m_nCteEnum = VSSCEnumMime :: eCteNull;
		return ;
	}

	int ch = m_vsscString[0];
	
	switch(ch)
	{
	case '7':
		if(VSSCStrcasecmp(m_vsscString, "7bit") == 0)
		{
			m_nCteEnum = VSSCEnumMime :: eCte7bit;
		}
		break;
	case '8':
		if(VSSCStrcasecmp(m_vsscString, "8bit") == 0)
		{
			m_nCteEnum = VSSCEnumMime :: eCte8bit;
		}
		break;
	case 'B':
	case 'b':
		if(VSSCStrcasecmp(m_vsscString, "binary") == 0)
		{
			m_nCteEnum = VSSCEnumMime :: eCteBinary;

		}
		else if(VSSCStrcasecmp(m_vsscString, "base64") == 0)
		{
			m_nCteEnum = VSSCEnumMime :: eCteBase64;
		}

		break;

	case 'Q':
	case 'q':
		if(VSSCStrcasecmp(m_vsscString, "quoted-printable") == 0)
		{
			m_nCteEnum = VSSCEnumMime :: eCteQuotedPrintable;

		}
		break;
	default:
		m_nCteEnum =  VSSCEnumMime :: eCteUnknown;
	}

}
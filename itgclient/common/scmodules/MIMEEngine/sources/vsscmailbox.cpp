#include "vsscmailbox.h"
#include "vssctoken.h"


VSSCMailBox :: VSSCMailBox()
{
	m_ComponentType = eCtMailbox;
}


VSSCMailBox :: VSSCMailBox(const VSSCMailBox& vsscmbMailBox)
:VSSCAddress(vsscmbMailBox)
{
	m_vsscLocalPart = vsscmbMailBox.m_vsscLocalPart;
	m_vsscFullName = vsscmbMailBox.m_vsscFullName;
	m_vsscDomain = vsscmbMailBox.m_vsscDomain;
	m_ComponentType = eCtMailbox;

}


VSSCMailBox :: VSSCMailBox(const VSSCString& vsscString, VSSCMsgComponent *Parent)
:VSSCAddress(vsscString, Parent)
{
	m_ComponentType = eCtMailbox;
}

VSSCMailBox :: ~VSSCMailBox()
{

}

const VSSCMailBox& VSSCMailBox :: operator = (const VSSCMailBox& vsscmbMailbox)
{
	if (this == &vsscmbMailbox) {
        return *this;
    }

    VSSCAddress::operator = (vsscmbMailbox);
	m_vsscFullName = vsscmbMailbox.m_vsscFullName;
	m_vsscLocalPart = vsscmbMailbox.m_vsscLocalPart;
	m_vsscDomain = vsscmbMailbox.m_vsscDomain;

    return *this;
}

const VSSCString& VSSCMailBox :: GetFullName() const
{
	return m_vsscFullName;
}

const VSSCString& VSSCMailBox :: GetLocalPart() const
{
	return m_vsscLocalPart;
}

const VSSCString& VSSCMailBox :: GetDomain() const
{
	return m_vsscDomain;
}

// Ajay Jayaram <ajayaram@bbbb.com>
// <ajayaram@bbb.com>
// Ajay <ajayaram@bbb.com>
// ajay.jayaram@bbb.com (Ajay Jayaram)


void VSSCMailBox :: Parse()
{
	VSSCString vsscEmptyString("");
	VSSCString vsscSpace(" ");
	VSSCString vsscFullName;
	VSSCString vsscLastComment;

	_BOOL bFirstPhrase = _TRUE;
	_BOOL bLTGTFound = _FALSE; // set this true if we find Full Name.
	vsscFullName = vsscEmptyString;
	m_vsscFullName = vsscEmptyString;
	m_vsscLocalPart = vsscEmptyString;
	m_vsscDomain = vsscEmptyString;


	VSSCRfc822Tokenizer Tokenizer(m_vsscString);

	// Define States

	enum
	{
		eStart,
		eAtFound,
		eGTFound,
		eLTFound,
		eAddressSpec
	};
	
	int nType = Tokenizer.GetType();
	int nState = eStart;

	int ch;

	// Either < or @ is found break

	while (nState == eStart && nType != eTkNull)
	{
		switch(nType)
		{
		case(eTkSpecial):
			ch = Tokenizer.GetToken()[0];
			switch(ch)
			{
			case '<':
					bLTGTFound = _TRUE;
					m_vsscLocalPart = vsscEmptyString;
					nState = eLTFound;
				break;

			case '@':
					nState = eAtFound;
				break;
			case '.':
				m_vsscLocalPart += Tokenizer.GetToken();
				break;
			}
			break;
		case eTkAtom:
		case eTkQuotedString:
			// This can be fullname in case of Ajay Jayaram <ajay@bbb.com>
			// This can be localpart in case of ajay.jayaram@bbb.com
			if(bFirstPhrase)
			{
				vsscFullName = Tokenizer.GetToken();
				bFirstPhrase = _FALSE;
			}
			else
			{
				vsscFullName += vsscSpace;
				vsscFullName += Tokenizer.GetToken();
			}
			m_vsscLocalPart += Tokenizer.GetToken();
			break;

		case eTkComment:
			vsscLastComment = Tokenizer.GetToken();
			break;
		}
		++Tokenizer;
		nType = Tokenizer.GetType();
	
	}

	// Less Than found. Process only one token and it is address-spec.
	// We are not supporting route address now.

	while(nState == eLTFound && nType != eTkNull)
	{
		switch(nType)
		{
			case eTkAtom:
			case eTkQuotedString:
				m_vsscLocalPart = Tokenizer.GetToken();
				break;
		}
		++Tokenizer;
		nType = Tokenizer.GetType();
		nState = eAddressSpec;
	}

	// AddressSpec State - break when @ is found

	while(nState == eAddressSpec && nType != eTkNull)
	{
		switch(nType)
		{
		case eTkSpecial:
			ch = Tokenizer.GetToken()[0];
			switch(ch)
			{
			case '@' :
				nState = eAtFound;
				break;
			case '.' :
				m_vsscLocalPart += Tokenizer.GetToken();
				break;
			}
			break;
		case eTkAtom:
		case eTkQuotedString:
			m_vsscLocalPart = Tokenizer.GetToken();
			break; 
		}
		++Tokenizer;
		nType = Tokenizer.GetType();
	}

	// AtFound State - break when > is found or end of string
	while(nState == eAtFound && nType != eTkNull)
	{
		switch(nType)
		{
		case eTkSpecial:
			ch = Tokenizer.GetToken()[0];
			switch(ch)
			{
			case '>':
				nState = eGTFound;
				break;
			case '.':
				m_vsscDomain += Tokenizer.GetToken();
				break;
			}
			break;

		case eTkAtom:
			m_vsscDomain += Tokenizer.GetToken();
			break; 

		case eTkDomainLiteral:
			m_vsscDomain += Tokenizer.GetToken();
			break;

		case eTkComment:
			Tokenizer.StripDelimiters();
			vsscLastComment = Tokenizer.GetToken();
			break;
		}
		++Tokenizer;
		nType = Tokenizer.GetType();
	}

	// GreaterThan State - break when end of string

	while(nState == eGTFound && nType != eTkNull)
	{
		switch(nType)
		{
		case eTkComment:
			Tokenizer.StripDelimiters();
			vsscLastComment = Tokenizer.GetToken();
			break;
		}
		++Tokenizer;
		nType = Tokenizer.GetType();
	}

	// Now set the FullName

	if(bLTGTFound == _FALSE)
		m_vsscFullName = vsscLastComment;

	if(vsscFullName != vsscEmptyString)
		m_vsscFullName = vsscFullName;

	if(vsscLastComment != vsscEmptyString)
		m_vsscFullName = vsscLastComment;
	
	// Check validity

	if(m_vsscLocalPart.Length() > 0 && m_vsscDomain.Length() > 0)
	{
		m_bIsValid = _FALSE;
	}
	else
	{
		m_bIsValid = _TRUE;
	}
}


void VSSCMailBox :: Assemble()
{
	// FullName <localpart@domain>
	m_bIsValid = _TRUE;

	if(m_vsscLocalPart.Length() > 0 && m_vsscDomain.Length() > 0)
	{
		m_bIsValid = _FALSE;
		m_vsscString = "";
		return;
	}

	m_vsscString = "";
	if(m_vsscFullName.Length() > 0)
	{
		m_vsscString += m_vsscFullName;
		m_vsscString += " "; // space
	}

	m_vsscString += "<";
	m_vsscString += m_vsscLocalPart;
	m_vsscString += "@";
	m_vsscString += m_vsscDomain;
	m_vsscString += ">";

}

VSSCMsgComponent* VSSCMailBox ::  Clone() const
{
	return new VSSCMailBox(*this);
}

VSSCMailBox* VSSCMailBox:: NewMailbox(const VSSCString& vsscString, VSSCMsgComponent*
        Parent)
{
	return new VSSCMailBox(vsscString, Parent);
}

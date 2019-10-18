#include <ctype.h>
#include "defines.h"
#include "vsscfield.h"
#include "vsscmailboxlist.h"


	// Constructors
VSSCField :: VSSCField()
{
	m_ComponentType = eCtField;
	m_fbFieldBody = 0;
}

VSSCField :: VSSCField(const VSSCField& fField)
:VSSCMsgComponent(fField),
 m_vsscFieldName(fField.m_vsscFieldName),
 m_vsscFieldBody(fField.m_vsscFieldBody)
{
	 m_ComponentType = eCtField;
	 if(fField.m_fbFieldBody != 0)
	 {
		 m_fbFieldBody = (VSSCFieldBody*)fField.m_fbFieldBody->Clone();
		 if(m_fbFieldBody != 0)
		 {
			 m_fbFieldBody->SetParent(this);
		 }
	 }
	
}

VSSCField :: VSSCField(const VSSCString& vsscString , VSSCMsgComponent *Parent)
 :VSSCMsgComponent(vsscString, Parent)
{
	m_ComponentType = eCtField;
	m_fbFieldBody = 0;
}


// Destructor
VSSCField :: ~VSSCField()
{
	//change
	//if(m_vsscFieldBody != 0)
	if(m_fbFieldBody != 0)
	{
		delete m_fbFieldBody;
		m_fbFieldBody = 0;
	}
}

void VSSCField :: SetFieldName(const VSSCString& vsscString)
{
	m_vsscFieldName = vsscString;
}
const VSSCString& VSSCField :: GetFieldName() const
{
	return m_vsscFieldName;
}

void VSSCField :: SetFieldBodyString(const VSSCString& vsscString)
{
	m_vsscFieldBody = vsscString;
}

const VSSCString& VSSCField ::  GetFieldBodyString() const
{
	return m_vsscFieldBody;
}



VSSCFieldBody* VSSCField :: GetFieldBody() const
{
	return m_fbFieldBody;
}

void VSSCField :: SetFieldBody(VSSCFieldBody* fbFieldBody)
{
	if(m_fbFieldBody != fbFieldBody)
	{
		_SetFieldBody(fbFieldBody);
	}

}

void VSSCField :: _SetFieldBody(VSSCFieldBody* fbFieldBody)
{
	if (m_fbFieldBody != fbFieldBody)
	{
        if (m_fbFieldBody != 0)
		{
            delete m_fbFieldBody;
            m_fbFieldBody = 0;
        }
        m_fbFieldBody = fbFieldBody;
        if (m_fbFieldBody != 0)
		{
            m_fbFieldBody->SetParent(this);
        }
    }
}

VSSCFieldBody* VSSCField :: CreateFieldBody(const VSSCString& vsscFieldName, const VSSCString& vsscFieldBody,
			VSSCMsgComponent *Parent)
{
	VSSCFieldBody* fieldBody;
	fieldBody =  _CreateFieldBody(vsscFieldName, vsscFieldBody, Parent);
	return fieldBody;

}

VSSCFieldBody* VSSCField :: _CreateFieldBody(const VSSCString& vsscFieldName, const VSSCString& vsscFieldBody,
			VSSCMsgComponent *Parent)
{
	    enum
		{
			eAddressList,
			eDispositionType,
			eDateTime,
			eMailbox,
			eMailboxList,
			eMechanism,
			eMediaType,
			eMsgId,
			eStamp,
			eText
		} fieldBodyType;

		// default 
		fieldBodyType = eText;

		int ch = vsscFieldName[0];
		ch = tolower(ch);

		switch(ch)
		{
		case 'f':
			fieldBodyType = eMailboxList;
			break;
		case 't':
			fieldBodyType = eMailboxList;
			break;
		case 'c':
			if(VSSCStrcasecmp(vsscFieldName,"cc") == 0)
			{
				fieldBodyType = eMailboxList;
			}
			else if(VSSCStrcasecmp(vsscFieldName,"content-type") == 0)
			{
				fieldBodyType = eMediaType;
			}
			else if(VSSCStrcasecmp(vsscFieldName,"content-transfer-encoding") == 0)
			{
				fieldBodyType = eMechanism;
			}
			else if(VSSCStrcasecmp(vsscFieldName, "content-disposition") == 0)
			{
				fieldBodyType = eDispositionType;
			}
			break;
		case 'b':
			fieldBodyType = eMailboxList;
			break;

		case 'd':
			fieldBodyType = eText;
			break;
		case 's':
			fieldBodyType = eText;
			break;

		}

		VSSCFieldBody *fbFieldBody = 0;
		switch(fieldBodyType)
		{
		case eMailboxList:
			fbFieldBody = VSSCMailboxList::NewMailboxList(vsscFieldBody, Parent);
			break;
		case eText:
			fbFieldBody = VSSCText :: NewText(vsscFieldBody, Parent);
			break;
		case eMediaType:
			fbFieldBody = VSSCMediaType :: NewMediaType(vsscFieldBody, Parent);
			break;
		case eMechanism:
			fbFieldBody =  VSSCMechanism :: NewMechanism(vsscFieldBody, Parent);
			break;
		case eDispositionType:
			fbFieldBody = VSSCDisposition :: NewDisposition(vsscFieldBody, Parent);
			break;
		}

		return fbFieldBody;


}

VSSCField* VSSCField :: NewField(const VSSCString& vsscString, VSSCMsgComponent *Parent)
{
	return new VSSCField(vsscString, Parent);
}

VSSCMsgComponent* VSSCField :: Clone() const
{
	return new VSSCField(*this);
}

void VSSCField :: Parse()
{
	VSSCFieldParser Parser(m_vsscString);
	m_vsscFieldName = Parser.m_vsscName;
	m_vsscFieldBody = Parser.m_vsscBody;
	m_fbFieldBody = _CreateFieldBody(m_vsscFieldName, m_vsscFieldBody, this);
	if(m_fbFieldBody != 0)
		m_fbFieldBody->Parse();
}
	
	



void VSSCField :: Assemble()
{
	// Field =  fieldname: fieldbody
	if(m_fbFieldBody != 0)
	{
		m_fbFieldBody->Assemble();
		m_vsscFieldBody = m_fbFieldBody->GetString();
	}

	m_vsscString = "";
	m_vsscString += m_vsscFieldName;
	m_vsscString += ": ";
	m_vsscString += m_vsscFieldBody;
	m_vsscString += EOL;



}

// Implementation of VSSCFieldParser

VSSCFieldParser :: VSSCFieldParser(const VSSCString& vsscString)
:m_vsscString(vsscString)
{
	Parse();
}

void VSSCFieldParser :: Parse()
{

	// Note at this point the field is already unfolded by the Headers Class
	// The string upto ":" is field name
	// String after ":" and upto to end of string is the field body

	_DWORD dwPos = 0;
	_DWORD dwStart = 0;
	_DWORD dwLen = 0;
	_DWORD dwTotalLen = m_vsscString.Length();
//	char *szBuf = m_vsscString.GetString();
	char *szBuf = m_vsscString.GetStartPos();

	while(dwPos < dwTotalLen)
	{
		if(szBuf[dwPos] == ':')
		{
			break;
		}
		dwPos ++;
		
	}

	dwLen = dwPos;

	// Skip the white spaces in the field name
	while(dwLen > 0)
	{
		if(!isspace(szBuf[dwLen])  )
			break;
		dwLen --;
	}

	if(dwPos < dwTotalLen)
		dwPos ++; // increment by 1 now it points to after :
		
		

	m_vsscName = m_vsscString.ParseString(dwStart, dwLen);

	
	// Skip White space at the start of the field body
	while(dwPos < dwTotalLen)
	{
		if(szBuf[dwPos] != ' ' && szBuf[dwPos] != '\t')
			break;
		dwPos ++;
	
	}

	// Get the field body here and strip the spaces at the end.
	dwStart = dwPos;
	dwPos = dwTotalLen - 1;
	while(dwPos > dwStart)
	{
		if(!isspace(szBuf[dwPos - 1]))
			break;
		dwPos --;

	}
	dwLen = dwPos - dwStart;	
	m_vsscBody = m_vsscString.ParseString(dwStart, dwLen);


}




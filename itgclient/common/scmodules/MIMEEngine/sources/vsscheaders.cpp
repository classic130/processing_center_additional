#include "vsscheaders.h"



void VSSCHeaders :: _Initialize()
{
	m_ComponentType = eCtHeaders;
	m_Fields = 0;
	m_nFields = 0;
	m_nFieldsSize = 0;

	const int n_FieldsSize = 30;
	m_Fields = new VSSCField* [n_FieldsSize] ;
	if(m_Fields != 0)
	{
		m_nFieldsSize =  n_FieldsSize;
		for(int i = 0; i < n_FieldsSize; i++)
		{
			m_Fields[i] = 0;
		}
	}
}


void VSSCHeaders :: _CopyFields(const VSSCHeaders& Headers)
{
	int nFields =  Headers.m_nFields;
	for ( int i = 0; i < nFields; i ++)
	{
		VSSCField *Field = (VSSCField*)Headers.m_Fields[i]->Clone();
		if(Field == 0)
		{
			break;
		}
		_AddField(Field);
	}


}

void VSSCHeaders :: _AddField(VSSCField* Field)
{
	// Always adds at the last.
	int nIndex = m_nFields;
	_InsertFieldAtPos(nIndex, Field);
}


void VSSCHeaders :: _InsertFieldAtPos(int nIndex, VSSCField* Field) 
{

// Reallocate a larger array, if necessary

    if (m_nFields == m_nFieldsSize)
	{
        int newFieldsSize = 2*m_nFieldsSize;
        if (newFieldsSize == 0) 
		{
            newFieldsSize = 30;
        }
        VSSCField** newFields = new VSSCField* [newFieldsSize];
        if (newFields == 0)
		{
            return;
        }

		// Add the older elements to the new array
        int i;
        for (i=0; i < m_nFields; ++i)
		{
            newFields[i] = m_Fields[i];
            m_Fields[i] = 0;
        }
        for ( ; i < newFieldsSize; ++i)
		{
            newFields[i] = 0;
        }
		// delete the old array.
        delete [] m_Fields;
        m_Fields = newFields;
        m_nFieldsSize = newFieldsSize;
    }

    // If it is to be inserted somewhere in between 
	// make room for it.

    for (int i=m_nFields; i > nIndex; --i)
	{
        m_Fields[i] = m_Fields[i-1];
    }

    m_Fields[nIndex] = Field;
    ++m_nFields;
    Field->SetParent(this);

}

void VSSCHeaders :: _DeleteAllFields()
{
	while(m_nFields > 0)
	{
		int i = m_nFields - 1;
		if(m_Fields[i] != 0)
		{
			delete m_Fields[i];
			m_Fields[i] = 0;
		}
		--m_nFields;
	}

}




// Constructors
VSSCHeaders :: VSSCHeaders()
{
	_Initialize();
}

VSSCHeaders :: VSSCHeaders(const VSSCHeaders& hHeaders)
:VSSCMsgComponent(hHeaders)
{
	_Initialize();
	_CopyFields(hHeaders);	
}

VSSCHeaders :: VSSCHeaders(const VSSCString& vsscString, VSSCMsgComponent *Parent)
:VSSCMsgComponent(vsscString, Parent)
{
	_Initialize();
}

// Destructor
VSSCHeaders :: ~VSSCHeaders()
{
	_DeleteAllFields();
	if(m_Fields != 0)
	{
		delete [] m_Fields;
		m_Fields = 0;
	}
}

int VSSCHeaders :: GetNumofFields() const
{
	return m_nFields;
}

void VSSCHeaders :: AddField(VSSCField* Field)
{
	_AddField(Field);
}

void VSSCHeaders :: DeleteAllFields()
{
	_DeleteAllFields();
}

void VSSCHeaders :: InsertFieldAtPos(int nIndex, VSSCField* Field)
{
	_InsertFieldAtPos(nIndex, Field);
}


VSSCFieldBody& VSSCHeaders :: GetFieldBody(const char* szFieldName)
{ 
	// If the Field or the FieldBody is not found it creates it and then returns.

	VSSCField *field = FindField(szFieldName);

	// Field is not found - create Field and FieldBody

	if(field == 0)
	{
		field = VSSCField :: NewField("", this);
		field->SetFieldName(szFieldName);
		VSSCFieldBody* fieldBody = VSSCField :: CreateFieldBody(szFieldName, "",
			field);
		field->SetFieldBody(fieldBody);
		AddField(field);
	}

	VSSCFieldBody* fieldBody = field->GetFieldBody();


	// Field is found but FieldBody is not found - create fieldbody
	if(fieldBody == 0)
	{
		fieldBody = VSSCField :: CreateFieldBody(szFieldName, "",
						field);
		field->SetFieldBody(fieldBody);

	}

	return *fieldBody;
	
}


VSSCField* VSSCHeaders :: FindField(const VSSCString& vsscFieldName) const
{
	VSSCField *RetField = 0;
	for(int i = 0; i < m_nFields; i ++)
	{
		VSSCString vsscString = m_Fields[i]->GetFieldName();
		if(VSSCStrcasecmp(vsscString, vsscFieldName) == 0)
		{
			RetField = m_Fields[i];
			break;
		}
	}
	return RetField;

}


VSSCField* VSSCHeaders :: FindField(const char* szFieldName) const
{
	VSSCField *RetField = 0;
	for(int i = 0; i < m_nFields; i ++)
	{
		VSSCString vsscString = m_Fields[i]->GetFieldName();
		if(VSSCStrcasecmp(vsscString, szFieldName) == 0)
		{
			RetField = m_Fields[i];
			break;
		}
	}
	return RetField;
}


_BOOL VSSCHeaders :: IsFieldPresent(VSSCString& vsscFieldName) const
{
	return FindField(vsscFieldName) ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsFieldPresent(char* szFieldName) const
{
	return FindField(szFieldName) ? _TRUE : _FALSE;
}


VSSCMsgComponent* VSSCHeaders :: Clone() const
{
	return new VSSCHeaders(*this);
}


VSSCHeaders* VSSCHeaders :: NewHeaders(const VSSCString& vsscString, VSSCMsgComponent* Parent)
{
	return new VSSCHeaders(vsscString, Parent);
}

const VSSCHeaders& VSSCHeaders :: operator = (const VSSCHeaders& Headers)
{
	
    if (this != &Headers)
	{
        _DeleteAllFields();
        VSSCMsgComponent :: operator = (Headers);
        _CopyFields(Headers);
    }
    return *this;
}
	

void VSSCHeaders :: Parse()
{
	_DeleteAllFields();
	VSSCHeadersParser parser(m_vsscString);
	VSSCString vsscStr;
	parser.ParseNextField(vsscStr);
	while(vsscStr.Length() > 0)
	{
		VSSCField* fdField = VSSCField :: NewField(vsscStr, this);
		if(fdField == 0)
			break;
		fdField->Parse();
		_AddField(fdField);
		parser.ParseNextField(vsscStr);
	}
}

void VSSCHeaders :: Assemble()
{
	m_vsscString = "";
	for(int i = 0; i < m_nFields; i ++)
	{
		VSSCField *Field = m_Fields[i];
		Field->Assemble();
		m_vsscString += Field->GetString();
	}

}

_BOOL VSSCHeaders :: IsFromPresent()
{
	return FindField("from") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsToPresent()
{
	return FindField("to") ? _TRUE : _FALSE;
}


_BOOL VSSCHeaders :: IsCcPresent()
{
	return FindField("cc") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsBccPresent()
{
	return FindField("bcc") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsDatePresent()
{
	return FindField("date") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsSubjectPresent()
{
	return FindField("subject") ? _TRUE : _FALSE;
}


_BOOL VSSCHeaders :: IsContentTypePresent()
{
	return FindField("content-type") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsContentTranserEncodingPresent()
{
	return FindField("content-transfer-encoding") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsContentDispositionPresent()
{
	return FindField("content-disposition") ? _TRUE : _FALSE;
}

_BOOL VSSCHeaders :: IsMimeVersionPresent()
{
	return FindField("mime-version") ? _TRUE : _FALSE;
}

VSSCMailboxList& VSSCHeaders :: GetFrom()
{
	return (VSSCMailboxList&) GetFieldBody("From");
}

VSSCMailboxList& VSSCHeaders :: GetTo()
{
		return (VSSCMailboxList&) GetFieldBody("To");
}


VSSCMailboxList& VSSCHeaders :: GetCc()
{
		return (VSSCMailboxList&) GetFieldBody("Cc");
}

VSSCMailboxList& VSSCHeaders :: GetBcc()
{
		return (VSSCMailboxList&) GetFieldBody("Bcc");
}

VSSCText& VSSCHeaders :: GetDate()
{
		return (VSSCText&) GetFieldBody("Date");
}

VSSCText& VSSCHeaders :: GetSubject()
{
		return (VSSCText&) GetFieldBody("Subject");
}

VSSCText& VSSCHeaders :: GetMimeVersion()
{
		return (VSSCText&) GetFieldBody("mime-version");
}


VSSCMediaType& VSSCHeaders :: GetContentType()
{
		return (VSSCMediaType&) GetFieldBody("Content-type");
}

VSSCMechanism& VSSCHeaders :: GetContentTransferEncoding()
{
	return (VSSCMechanism&) GetFieldBody("Content-transfer-encoding");
}

VSSCDisposition& VSSCHeaders :: GetContentDisposition()
{
		return (VSSCDisposition&) GetFieldBody("Content-disposition");
}





// Implementation for VSSCHeadersParser

VSSCHeadersParser :: VSSCHeadersParser(const VSSCString& vsscString)
:m_vsscString(vsscString)
{
	m_dwPos = 0;
}


void VSSCHeadersParser :: ParseNextField(VSSCString& vsscString)
{
	const char* szBuf = m_vsscString.GetStartPos();

    _DWORD dwEnd = m_vsscString.Length();
    _DWORD dwPos = m_dwPos;
    _DWORD dwStart = m_dwPos;

    while (dwPos < dwEnd)
	{
        char ch = szBuf[dwPos++];

		// Takes care of the folding.
        if (ch == '\n'
            && dwPos < dwEnd
            && szBuf[dwPos] != ' '
            && szBuf[dwPos] != '\t') {

            break;
        }
    }

    _DWORD dwLen = dwPos - dwStart;
    vsscString = m_vsscString.ParseString(dwStart, dwLen);
    m_dwPos = dwPos;
}
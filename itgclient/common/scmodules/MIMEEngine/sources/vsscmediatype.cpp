#include <windows.h>
#include <time.h>
#include "defines.h"
#include "vsscmediatype.h"
#include "vsscparameter.h"
#include "vssctoken.h"
#include "vsscenum.h"

VSSCMediaType :: VSSCMediaType()
{
	_Initialize();
}

VSSCMediaType :: VSSCMediaType(const VSSCMediaType& MediaType)
: VSSCFieldBody(MediaType),
  m_vsscType(MediaType.m_vsscType),
  m_vsscSubType(MediaType.m_vsscSubType)
{
	_Initialize();
	_CopyAllParameters(MediaType);
}

VSSCMediaType :: VSSCMediaType(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCFieldBody(vsscString, Parent)
{
	_Initialize();	
}

VSSCMediaType :: ~VSSCMediaType()
{
	_DeleteAllParameters();
	if(m_Parameters != 0)
	{
		delete m_Parameters;
		m_Parameters = 0;
	}	

}

void VSSCMediaType :: SetTypeString(const VSSCString& vsscString)
{
	m_vsscType = vsscString;
	_TypeStrToEnum();
}

const VSSCString& VSSCMediaType :: GetTypeString() const
{
	return m_vsscType;
}

void VSSCMediaType :: SetType(const int nType)
{
	m_nType = nType;
	_TypeEnumToStr();
}

const int VSSCMediaType :: GetType() const
{
	return m_nType;
}


void VSSCMediaType :: SetSubTypeString(const VSSCString& vsscString)
{
	m_vsscSubType = vsscString;
	_SubtypeStrToEnum();
}

const VSSCString& VSSCMediaType :: GetSubTypeString() const
{
	return m_vsscSubType;	
}

void VSSCMediaType :: SetSubType(const int nSubType)
{
	m_nSubType = nSubType;
	_SubtypeEnumToStr();
}

const int VSSCMediaType :: GetSubType() const
{
	return m_nSubType;
}

int VSSCMediaType :: GetNumofParmeters () const
{
	return m_nParameters;
}

void VSSCMediaType :: AddParameter(VSSCParameter* Parameter)
{
	_AddParameter(Parameter);
}

void VSSCMediaType :: DeleteAllParameters()
{
	_DeleteAllParameters();
}


VSSCMsgComponent* VSSCMediaType :: Clone() const
{
	return new VSSCMediaType(*this);
}

VSSCParameter& VSSCMediaType :: GetParameter(int nIndex) const
{
	if(nIndex < 0 && nIndex >= m_nParameters)
	{
		abort();
	}
	return *m_Parameters[nIndex];
}


void VSSCMediaType :: Parse()
{
	m_vsscType = m_vsscSubType = "";
	_DeleteAllParameters();
	if(m_vsscString.Length() == 0)
	{
		return;
	}

	VSSCRfc2045Tokenizer tokenizer(m_vsscString);
	_BOOL bFound = _FALSE;

	
	// Get Type
	while(!bFound && tokenizer.GetType() != eTkNull)
	{
		if(tokenizer.GetType() == eTkToken)
		{
			m_vsscType = tokenizer.GetToken();
			bFound = _TRUE;
		}
		++tokenizer;
	}

	// Get /
	bFound = _FALSE;
	while(!bFound && tokenizer.GetType() != eTkNull)
	{
		if(tokenizer.GetType() == eTkTspecial && 
				tokenizer.GetToken()[0] == '/')
		{
			bFound = _TRUE;
		}
		++tokenizer;
	}

	// Get SubType
	bFound = _FALSE;
	while(!bFound && tokenizer.GetType() != eTkNull)
	{
		if(tokenizer.GetType() == eTkToken)
		{
			m_vsscSubType = tokenizer.GetToken();
			bFound = _TRUE;
		}
		++tokenizer;
	}

	// Get Parameters...
	// I think this parsing can be implemented differently
	// I'm not sure the need of parsing all the parts to parameter. 
	// The only interested character is ";" which can be used as token separater.
	// Try out in leisure.

	VSSCGroupTokens tokensStr(m_vsscString);
	while(1)
	{
		// Get ;
		bFound = _FALSE;
		while(!bFound && tokenizer.GetType() != eTkNull)
		{
			if(tokenizer.GetType() == eTkTspecial && 
				tokenizer.GetToken()[0] == ';')
			{
				bFound = _TRUE;
			}
			++tokenizer;
		}

		if(tokenizer.GetType() == eTkNull)
		{
			// No parameters
			break;
		}

		tokensStr.SetFirstToken(tokenizer);
		
		// Get Attribute
		_BOOL bAttribFound = _FALSE;
		while(!bAttribFound && tokenizer.GetType() != eTkNull)
		{
			if(tokenizer.GetType() == eTkToken)
			{
				bAttribFound = _TRUE;
			}
			++tokenizer;
		}

		// Get =
		bFound = _FALSE;
		while(!bFound && tokenizer.GetType() != eTkNull)
		{
			if(tokenizer.GetType() == eTkTspecial &&
				tokenizer.GetToken()[0] == '=')
			{
				bFound = _TRUE;
			}
			++tokenizer;
		}

		// Get Value
		_BOOL bValueFound = _FALSE;
		while(!bValueFound && tokenizer.GetType() != eTkNull)
		{
			if(tokenizer.GetType() == eTkToken || 
				tokenizer.GetType() == eTkQuotedString)
			{
				bValueFound = _TRUE;
			}
			++tokenizer;
		}

		if(bAttribFound && bValueFound)
		{
			tokensStr.ExtendTo(tokenizer);
			VSSCParameter* Param =
				VSSCParameter::NewParameter(tokensStr.GetTokens(), this);
			if(Param == 0)
				break;
			Param->Parse();
			_AddParameter(Param);
		}

	}
	_TypeStrToEnum();
	_SubtypeStrToEnum();

}

void VSSCMediaType :: Assemble()
{
	//Type/SubType;attribute=value;attribute=value

	m_vsscString = "";
	if(m_vsscType.Length() > 0 && m_vsscSubType.Length() > 0)
	{
		m_vsscString += m_vsscType;
		m_vsscString += "/";
		m_vsscString += m_vsscSubType;
		for(int i = 0; i < m_nParameters; i ++)
		{
			VSSCParameter *Param = m_Parameters[i];
			Param->Assemble();
			if(IsFolding())
			{
				m_vsscString += ";" EOL " ";
			}
			else
			{
				m_vsscString += "; ";
			}
			m_vsscString += Param->GetString();
			
		}
	}

}


const VSSCMediaType& VSSCMediaType :: operator = (const VSSCMediaType& MediaType)
{
	if(this != &MediaType)
	{
		_DeleteAllParameters();
		VSSCFieldBody :: operator = (MediaType);
		m_vsscType = MediaType.m_vsscType;
		m_vsscSubType = MediaType.m_vsscSubType;
		_CopyAllParameters(MediaType);
		
	}
	return *this;
}


VSSCMediaType* VSSCMediaType :: NewMediaType(const VSSCString& vsscString, VSSCMsgComponent* Parent)
{
	return new VSSCMediaType(vsscString, Parent);
}

void VSSCMediaType :: _Initialize()
{
//	m_vsscType = 0;
//	m_vsscSubType = 0;
	m_ComponentType = eCtMediaType;
	m_nParameters = 0;
	m_nSizeofParameter = 0;
	m_Parameters = 0;

	int nSize = 10;
	m_Parameters = new VSSCParameter* [nSize];
	if(m_Parameters != 0)
	{
		for(int i = 0; i < nSize; i++)
		{
			m_Parameters[i] = 0;
		}
	}
	m_nSizeofParameter = nSize; 
}


void VSSCMediaType :: _CopyAllParameters(const VSSCMediaType& MediaType)
{
	int nParams =  MediaType.m_nParameters;
	for(int i = 0; i < nParams; i++)
	{
		VSSCParameter* Param = (VSSCParameter*)MediaType.m_Parameters[i]->Clone();
		if(Param == 0)
		{
			break;
		}
		_AddParameter(Param);
	}
}

void VSSCMediaType :: _AddParameter(VSSCParameter* Parameter)
{
	// By doing this, it increases the size of the array and then adds it.
	int nIndex =  m_nParameters;
	_InsertParameter(nIndex, Parameter);
}

void VSSCMediaType :: _InsertParameter(int nIndex, VSSCParameter* Parameter)
{
	if(m_nParameters == m_nSizeofParameter)
	{
		// need to allocate more space to add the Parameter
		int nNewParameterSize = 2 * m_nSizeofParameter;
		if(nNewParameterSize == 0)
		{
			nNewParameterSize = 10;
		}

		VSSCParameter **NewParameters = new VSSCParameter* [nNewParameterSize];
		if(NewParameters == 0)
		{
			return;
		}
		for(int i = 0; i < m_nParameters; i++)
		{
			NewParameters[i] = m_Parameters[i];
			m_Parameters[i] = 0;
		}

		for(; i < nNewParameterSize; i ++)
		{
			NewParameters[i] = 0;
		}
		delete [] m_Parameters;
		m_Parameters = NewParameters;
		m_nSizeofParameter =  nNewParameterSize;
		

	}

	for(int i = m_nParameters; i > nIndex; i--)
	{
		m_Parameters[i] = m_Parameters[i-1];
	}
	m_Parameters[nIndex] = Parameter;
	++m_nParameters;
	Parameter->SetParent(this);
}


void VSSCMediaType :: _DeleteAllParameters()
{
	while (m_nParameters > 0)
	{
        int i = m_nParameters - 1;
        if (m_Parameters[i] != 0)
		{
            delete m_Parameters[i];
            m_Parameters[i] = 0;
        }
        --m_nParameters;
    }	
}

void VSSCMediaType :: _TypeEnumToStr()
{
	VSSCTypeEnumToStr(m_nType, m_vsscType);
}

void VSSCMediaType :: _TypeStrToEnum()
{
	m_nType = VSSCTypeStrToEnum(m_vsscType);
}

void VSSCMediaType :: _SubtypeEnumToStr()
{
	VSSCSubtypeEnumToStr(m_nSubType, m_vsscSubType);
}

void VSSCMediaType :: _SubtypeStrToEnum()
{
	m_nSubType = VSSCSubtypeStrToEnum(m_vsscSubType);
}

const VSSCString& VSSCMediaType :: GetBoundary() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscBoundary = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "boundary") == 0)
		{
            // Boundary parameter found. Return its value.
            _this->m_vsscBoundary = param->GetValue();
            break;
        }
    }
    return m_vsscBoundary;
}

void VSSCMediaType :: SetBoundary(const VSSCString& vsscStr)
{
	m_vsscBoundary = vsscStr;
	// Search for boundary parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "boundary") == 0)
		{
            param->SetValue(m_vsscBoundary);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // Boundary parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("boundary");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}


void VSSCMediaType :: CreateBoundary()
{
	char *szBoundary = GenBoundary();
	SetBoundary(szBoundary);
	if(szBoundary)
		free(szBoundary);
}

/////////////////////////////////////////
const VSSCString& VSSCMediaType :: GetName() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscName = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "name") == 0)
		{
            // Boundary parameter found. Return its value.
            _this->m_vsscName = param->GetValue();
            break;
        }
    }
    return m_vsscName;
}

void VSSCMediaType :: SetName(const VSSCString& vsscStr)
{
	m_vsscName = vsscStr;
	// Search for boundary parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "name") == 0)
		{
            param->SetValue(m_vsscName);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // Boundary parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("name");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}


const VSSCString& VSSCMediaType :: GetProtocol() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscProtocol = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "protocol") == 0)
		{
            // Boundary parameter found. Return its value.
            _this->m_vsscProtocol = param->GetValue();
            break;
        }
    }
    return m_vsscProtocol;
}

void VSSCMediaType :: SetProtocol(const VSSCString& vsscStr)
{
	m_vsscProtocol = vsscStr;
	// Search for boundary parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "protocol") == 0)
		{
            param->SetValue(m_vsscProtocol);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // Boundary parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("protocol");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}

const VSSCString& VSSCMediaType :: GetFileName() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscFileName = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "filename") == 0)
		{
            // Boundary parameter found. Return its value.
            _this->m_vsscFileName = param->GetValue();
            break;
        }
    }
    return m_vsscFileName;
}

void VSSCMediaType :: SetFileName(const VSSCString& vsscStr)
{
	m_vsscFileName = vsscStr;
	// Search for boundary parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "filename") == 0)
		{
            param->SetValue(m_vsscFileName);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // Boundary parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("filename");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}

const VSSCString& VSSCMediaType :: GetSMIMEType() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscSMIMEType = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "smime-type") == 0)
		{
            // Boundary parameter found. Return its value.
            _this->m_vsscSMIMEType = param->GetValue();
            break;
        }
    }
    return m_vsscSMIMEType;
}

void VSSCMediaType :: SetSMIMEType(const VSSCString& vsscStr)
{
	m_vsscSMIMEType = vsscStr;
	// Search for boundary parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "smime-type") == 0)
		{
            param->SetValue(m_vsscSMIMEType);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // Boundary parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("smime-type");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}

//////////////////
const VSSCString& VSSCMediaType :: GetMicalg() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscMicalg = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "micalg") == 0)
		{
            // Boundary parameter found. Return its value.
            _this->m_vsscMicalg = param->GetValue();
            break;
        }
    }
    return m_vsscMicalg;
}

void VSSCMediaType :: SetMicalg(const VSSCString& vsscStr)
{
	m_vsscMicalg = vsscStr;
	// Search for boundary parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "micalg") == 0)
		{
            param->SetValue(m_vsscMicalg);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // Boundary parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("micalg");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}

const VSSCString& VSSCMediaType :: GetCharset() const
{
	VSSCMediaType* _this = (VSSCMediaType*) this;
    _this->m_vsscCharSet = "";
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "charset") == 0)
		{
            // charset parameter found. Return its value.
            _this->m_vsscCharSet = param->GetValue();
            break;
        }
    }
    return m_vsscCharSet;
}

void VSSCMediaType :: SetCharset(const VSSCString& vsscStr)
{
	m_vsscCharSet = vsscStr;
	// Search for charset parameter in parameter list.  If found, set its
    // value.
    _BOOL bFound = _FALSE;
    for (int i=0; i < m_nParameters; ++i)
	{
        VSSCParameter* param = m_Parameters[i];
        if (VSSCStrcasecmp(param->GetAttribute(), "charset") == 0)
		{
            param->SetValue(m_vsscCharSet);
            bFound = _TRUE;
            break;
        }
    }
    if (! bFound)
	{
        // charset parameter not found. Add it.
        VSSCParameter* param = VSSCParameter :: NewParameter("", 0);
        param->SetAttribute("charset");
        param->SetValue(vsscStr);
        AddParameter(param);
    }
}


char *VSSCMediaType :: GenBoundary()
{
	char szBoundary[256];
	char *szRet = NULL;
	_GetRandomString(szBoundary, 30);
	szRet = (char *)malloc(strlen(szBoundary) + 1);
	strcpy(szRet, szBoundary);
	return szRet;
}

void VSSCMediaType :: _GetRandomString(char *szData, int len)
{
	_DWORD dwRand;
	char szRand[256];
	int i = 0;
	int count = 0;

	srand( (unsigned)time( NULL ) + GetTickCount() + rand() );

	while(1)
	{
		dwRand = rand();
		itoa(dwRand,szRand,10);

		while(szRand[i])
		{
			if(count == len)
			{
				szData[len] = '\0';
				return;
			}
			szData[count] = szRand[i];
			i ++;
			count ++;

		}
		i = 0;
	}
	

}
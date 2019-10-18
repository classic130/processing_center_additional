#include <stdlib.h>
#include "defines.h"
#include "vsscdisposition.h"
#include "vsscenum.h"
#include "vssctoken.h"



VSSCDisposition :: VSSCDisposition()
{
	_Initialize();
}

VSSCDisposition :: VSSCDisposition(const VSSCDisposition& Disp)
: VSSCFieldBody(Disp),
  m_vsscDispType(Disp.m_vsscDispType),
  m_vsscFileName(Disp.m_vsscFileName)
{
	_Initialize();

	m_nDispType = Disp.m_nDispType;
	_CopyAllParameters(Disp);

}

VSSCDisposition :: VSSCDisposition(const VSSCString& vsscString,
	VSSCMsgComponent* Parent)
: VSSCFieldBody(vsscString, Parent)
{
	_Initialize();	
}

VSSCDisposition :: ~VSSCDisposition()
{
	_DeleteAllParameters();
	if(m_Parameters != 0)
	{
		delete m_Parameters;
		m_Parameters = 0;
	}	

}

int VSSCDisposition :: GetNumofParmeters () const
{
	return m_nParameters;
}

void VSSCDisposition :: AddParameter(VSSCParameter* Parameter)
{
	_AddParameter(Parameter);
}

void VSSCDisposition :: DeleteAllParameters()
{
	_DeleteAllParameters();
}

VSSCParameter& VSSCDisposition :: GetParameter(int nIndex) const
{
	if(nIndex <= 0 && nIndex < m_nParameters)
	{
		abort();
	}
	return *m_Parameters[nIndex];
}

const VSSCString& VSSCDisposition :: GetDispTypeString() const
{

    return m_vsscDispType;
}

void VSSCDisposition :: SetDispTypeString(const VSSCString& vsscString)
{
	m_vsscDispType = vsscString;
	_StrToEnum();
}

const int VSSCDisposition :: GetDispType()
{

	return m_nDispType;
}

void VSSCDisposition :: SetDispType(int nDispType)
{
	m_nDispType = nDispType;
	_EnumToStr();
}


const VSSCString& VSSCDisposition :: GetFileName() const
{
	// Implementation note: this member function is const, which
    // forbids us from assigning to mBoundaryStr.  The following
    // cast gets around this.  (ANSI implementations could use the
    // "mutable" declaration).
    VSSCDisposition* _this = (VSSCDisposition*) this;
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

void VSSCDisposition :: SetFileName(const VSSCString& vsscString)
{
	m_vsscFileName = vsscString;
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
        param->SetValue(vsscString);
        AddParameter(param);
    }
}


VSSCDisposition* VSSCDisposition :: NewDisposition(const VSSCString& vsscString,
		VSSCMsgComponent* Parent)
{
	return new VSSCDisposition(vsscString, Parent);
}

const VSSCDisposition& VSSCDisposition :: operator = (const VSSCDisposition& Disp)
{
	if(this != &Disp)
	{
		_DeleteAllParameters();
		VSSCFieldBody :: operator = (Disp);
		m_vsscDispType = Disp.m_vsscDispType;
		m_vsscFileName = Disp.m_vsscFileName;
		m_nDispType = Disp.m_nDispType;
		_CopyAllParameters(Disp);
		
	}
	return *this;
}

void VSSCDisposition :: Parse()
{
	m_vsscDispType = "";
	m_nDispType = VSSCEnumMime :: eDispTypeNull;
	_DeleteAllParameters();
	if(m_vsscString.Length() == 0)
	{
		return;
	}

	VSSCRfc2045Tokenizer tokenizer(m_vsscString);
	_BOOL bFound = _FALSE;

	
	// Get DispType
	while(!bFound && tokenizer.GetType() != eTkNull)
	{
		if(tokenizer.GetType() == eTkToken)
		{
			m_vsscDispType = tokenizer.GetToken();
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
	_StrToEnum();

}

void VSSCDisposition :: Assemble()
{

	m_vsscString = "";
	if(m_vsscDispType.Length() > 0)
	{
		m_vsscString += m_vsscDispType;
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

VSSCMsgComponent* VSSCDisposition :: Clone() const
{
	return new VSSCDisposition(*this);
}



void VSSCDisposition :: _Initialize()
{
	//m_vsscFileName = 0;
	//m_vsscDispType = 0;
	m_nDispType = VSSCEnumMime :: eDispTypeNull;
	m_ComponentType = eCtDispositionType;
	m_nParameters = 0;

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


void VSSCDisposition :: _CopyAllParameters(const VSSCDisposition& Disp)
{
	int nParams =  Disp.m_nParameters;
	for(int i = 0; i < nParams; i++)
	{
		VSSCParameter* Param = (VSSCParameter*)Disp.m_Parameters[i]->Clone();
		if(Param == 0)
		{
			break;
		}
		_AddParameter(Param);
	}
}

void VSSCDisposition :: _AddParameter(VSSCParameter* Parameter)
{
	// By doing this, it increases the size of the array and then adds it.
	int nIndex =  m_nParameters;
	_InsertParameter(nIndex, Parameter);
}


void VSSCDisposition :: _InsertParameter(int nIndex,
										 VSSCParameter* Parameter)
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


void VSSCDisposition :: _DeleteAllParameters()
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

void VSSCDisposition :: _EnumToStr()
{
	switch(m_nDispType)
	{
	case VSSCEnumMime :: eDispTypeInline:
		m_vsscDispType = "inline";
		break;
	case VSSCEnumMime :: eDispTypeAttachment:
		m_vsscDispType = "attachment";
		break;
	}
	
}

void VSSCDisposition :: _StrToEnum()
{
	switch (m_vsscDispType[0])
	{
    case 'i':
        if (VSSCStrcasecmp(m_vsscDispType, "inline") == 0) 
		{
            m_nDispType = VSSCEnumMime :: eDispTypeInline;
        }
        else
		{
            m_nDispType = VSSCEnumMime :: eDispTypeUnknown;
        }
        break;
    case 'a':
        if (VSSCStrcasecmp(m_vsscDispType, "attachment") == 0)
		{
            m_nDispType = VSSCEnumMime :: eDispTypeAttachment;
        }
        else
		{
            m_nDispType = VSSCEnumMime :: eDispTypeUnknown;
        }
        break;
    }
}

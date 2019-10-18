#include "vsscparameter.h"
#include "vsscmsgcmp.h"
#include "vssctoken.h"

VSSCParameter :: VSSCParameter()
{
	m_ComponentType = eCtParameter;
//	m_vsscAttribute = 0;
//	m_vsscValue = 0;
}

VSSCParameter :: VSSCParameter(const VSSCParameter& Parameter)
: VSSCMsgComponent(Parameter),
  m_vsscAttribute(Parameter.m_vsscAttribute), 
  m_vsscValue(Parameter.m_vsscValue)
{
	m_ComponentType = eCtParameter;
}

VSSCParameter :: VSSCParameter(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCMsgComponent(vsscString, Parent)
{
	m_ComponentType = eCtParameter;
}

VSSCParameter :: ~VSSCParameter()
{

}

void VSSCParameter :: SetAttribute(const VSSCString& vsscString)
{
	m_vsscAttribute =  vsscString;
}

const VSSCString& VSSCParameter :: GetAttribute() const
{
	return m_vsscAttribute;
}

void VSSCParameter :: SetValue(const VSSCString& vsscString)
{
	m_vsscValue = vsscString;
}

const VSSCString& VSSCParameter :: GetValue()
{
	return m_vsscValue;
}

void VSSCParameter :: Parse()
{
	m_vsscAttribute = m_vsscValue = "";
	if(m_vsscString.Length() == 0)
	{
		return;
	}
	VSSCRfc2045Tokenizer tokenizer(m_vsscString);
	_BOOL bFound = _FALSE;

	// Get Attribute
	while(!bFound && tokenizer.GetType() != eTkNull)
	{
		if(tokenizer.GetType() == eTkToken)
		{
			m_vsscAttribute = tokenizer.GetToken();
			bFound = _TRUE;
		}
		++tokenizer;
	}
	
	// Get '= '
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

	// Get Value, Value can be a Token or a Qouted String.
	bFound = _FALSE;
	while(!bFound && tokenizer.GetType() != eTkNull)
	{
		if(tokenizer.GetType() == eTkToken)
		{
			m_vsscValue = tokenizer.GetToken();
			bFound = _TRUE;
		}
		else if(tokenizer.GetType() == eTkQuotedString)
		{
			tokenizer.StripDelimiters();
			m_vsscValue = tokenizer.GetToken();
			bFound =_TRUE;
		}
	}

	
}

void VSSCParameter :: Assemble()
{
	// "Attribute=Value"
	m_vsscString = "";
	m_vsscString += m_vsscAttribute;
	m_vsscString += "=\"";
	m_vsscString += m_vsscValue;
	m_vsscString += "\"";
}


VSSCMsgComponent* VSSCParameter :: Clone() const
{
	return new VSSCParameter(*this);
}

VSSCParameter* VSSCParameter :: NewParameter(const VSSCString& vsscString, VSSCMsgComponent* Parent)
{
	return new VSSCParameter(vsscString, Parent);
}

const  VSSCParameter& VSSCParameter :: operator = (const VSSCParameter& Parameter)
{
	if(&Parameter == this)
	{
		return *this;
	}
	
	VSSCMsgComponent :: operator = (Parameter);
	m_vsscAttribute = Parameter.m_vsscAttribute;
	m_vsscValue = Parameter.m_vsscValue;

	return *this;

}



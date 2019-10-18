#include "defines.h"
#include "vsscentity.h"
#include "vsscbody.h"


VSSCEntity :: VSSCEntity()
{
	m_ComponentType = eCtEntity;
	m_Headers = 0;
	m_Body = 0;

	m_Headers = VSSCHeaders :: NewHeaders("", this);
	m_Body = VSSCBody :: NewBody("", this);
	m_bAssembled = _FALSE;


}

VSSCEntity :: VSSCEntity(const VSSCEntity& Entity)
:VSSCMsgComponent(Entity)
{
	m_ComponentType = eCtEntity;
	m_Headers = 0;
	m_Body = 0;

	m_Headers = (VSSCHeaders*)Entity.m_Headers->Clone();
	m_Headers->SetParent(this);
	m_Body = (VSSCBody*)Entity.m_Body->Clone();
	m_Body->SetParent(this);

}

VSSCEntity :: VSSCEntity(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCMsgComponent(vsscString, Parent)
{
	m_ComponentType = eCtEntity;
	m_Headers = 0;
	m_Body = 0;
	m_bAssembled = _FALSE;

	m_Headers = VSSCHeaders :: NewHeaders("", this);
	m_Body = VSSCBody :: NewBody("", this);
}

VSSCEntity :: ~VSSCEntity()
{
	if(m_Headers)
	{
		delete m_Headers;
		m_Headers = 0;
	}
	
	if(m_Body)
	{
		delete m_Body;
		m_Body = 0;
	}
	
}

const VSSCEntity& VSSCEntity :: operator = (const VSSCEntity& Entity)
{
	if(&Entity == this)
	{
		return *this;
	}
	VSSCMsgComponent::operator = (Entity);

	if(m_Headers)
	{
		delete m_Headers;
		m_Headers = 0;
	}

	if(m_Body)
	{
		delete m_Body;
		m_Body = 0;
	}



	m_Headers = (VSSCHeaders*)Entity.m_Headers->Clone();
	m_Headers->SetParent(this);
	m_Body = (VSSCBody*)Entity.m_Body->Clone();
	m_Body->SetParent(this);

	return *this;
}


VSSCHeaders& VSSCEntity :: GetHeaders() const
{
	return *m_Headers;
}


VSSCBody& VSSCEntity :: GetBody() const 
{
	return *m_Body;
}



void VSSCEntity :: Parse()
{
	EntityParser parser(m_vsscString);
	m_Headers->SetString(parser.m_vsscHeaders);
	m_Body->SetString(parser.m_vsscBody);
	m_Headers->Parse();
	m_Body->Parse();
}

void VSSCEntity :: SetAssembled()
{
	m_bAssembled = _TRUE;

}

void VSSCEntity :: Assemble()
{
//	m_vsscString = "";
	if(m_bAssembled == _FALSE)
	{
		m_Headers->Assemble();
		m_Body->Assemble();
		m_vsscString += m_Headers->GetString();
		m_vsscString += EOL;
		m_vsscString += m_Body->GetString();
		m_bAssembled = _TRUE;
	}

}



// Implementation of EntityParser

EntityParser :: EntityParser(const VSSCString& vsscString)
:m_vsscStr(vsscString)
{
	Parse();
}



void EntityParser :: Parse()
{
	//const char *szBuf = m_vsscString.GetString();
	const char *szBuf = m_vsscStr.GetStartPos();
	_DWORD dwLen = m_vsscStr.Length();
	_BOOL bFoundLF = _FALSE;
	_BOOL bFoundCRLF = _FALSE; 
	
	_DWORD dwPos = 0;

	_DWORD dwHeaderLen = 0;
	_DWORD dwBodyLen = 0;
	_DWORD dwHeaderStart = dwPos;

	// If first character is a LF 
	// or if first two characters are CR LF 
	// there are no headers.

	// If the body has no headers find out if it uses LF or CRLF for linefeed
	if(szBuf[dwPos] == '\r' && szBuf[dwPos + 1] == '\n')
	{
		bFoundCRLF = _TRUE;
	}
	else
	{
		bFoundLF = _TRUE;
	}

	if (dwPos < dwLen && szBuf[dwPos] != '\n' 
    && ! (szBuf[dwPos] == '\r' && dwPos + 1 < dwLen && szBuf[dwPos + 1] == '\n')) 
	{
		while(dwPos < dwLen)
		{
			if(szBuf[dwPos] == '\n')
			{
				/*
				if(bFoundCRLF == _TRUE || bFoundLF == _TRUE)
					break;
				*/
				if(szBuf[dwPos - 1] == '\r')
				{
					bFoundCRLF = _TRUE;
					bFoundLF = _FALSE;
				}
				else
				{
					bFoundLF = _TRUE;
					bFoundCRLF = _FALSE;
				}
				if(szBuf[dwPos + 1] == '\r' && szBuf[dwPos + 2] == '\n' || szBuf[dwPos + 1] == '\n')
					break;
			}
			dwPos ++;
		}
	}
	else
	{
		dwPos--; // to compensate for the increment done next
	}
	
	dwPos++;
	if(bFoundCRLF)
	{
		dwHeaderLen = dwPos + 2;
	}
	else if(bFoundLF)
	{
		dwHeaderLen = dwPos + 1;
	}
	
	dwHeaderLen = dwPos;

	//dwHeaderLen = dwPos;
	m_vsscHeaders =  m_vsscStr.ParseString(dwHeaderStart,dwHeaderLen);
	
	
	if(bFoundCRLF == _TRUE)
	{
		dwPos += 2;
	}
	else
	{
		dwPos ++;
	}
	

	//_DWORD dwBodyStart = ++dwPos;
	_DWORD dwBodyStart = dwPos;
	dwBodyLen = m_vsscStr.Length() - dwBodyStart;
	m_vsscBody = m_vsscStr.ParseString(dwBodyStart, dwBodyLen);
}









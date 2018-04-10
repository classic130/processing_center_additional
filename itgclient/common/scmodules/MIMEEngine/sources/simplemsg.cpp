#include "simplemsg.h"
#include "vsscbody.h"
#include "vsscenum.h"

SimpleMessage :: SimpleMessage()
{
	m_Message = VSSCMessage :: NewMessage(m_EmptyStr, 0);
}


//SimpleMessage :: SimpleMessage(VSSCMessage* msg)
SimpleMessage :: SimpleMessage(VSSCEntity* Entity)
{
	//m_Message = msg;
	m_Message = Entity;
}

SimpleMessage :: ~SimpleMessage()
{
	
	if(m_Message != 0 )
	{
		delete m_Message;
	}
	
	


}

const VSSCString& SimpleMessage :: GetString() const
{
	return m_Message->GetString();
}


const VSSCString& SimpleMessage :: GetFrom() const
{
	return m_Message->GetHeaders().GetFrom().GetString();
}

void SimpleMessage :: SetFrom(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetFrom().SetString(vsscStr);
}

const VSSCString& SimpleMessage :: GetTo() const
{
	return m_Message->GetHeaders().GetTo().GetString();
}

void SimpleMessage :: SetTo(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetTo().SetString(vsscStr);
}


const VSSCString& SimpleMessage :: GetCc() const
{
	return m_Message->GetHeaders().GetCc().GetString();
}

void SimpleMessage :: SetCc(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetCc().SetString(vsscStr);
}

const VSSCString& SimpleMessage :: GetBcc() const
{
	return m_Message->GetHeaders().GetBcc().GetString();
}

void SimpleMessage :: SetBcc(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetBcc().SetString(vsscStr);
}

const VSSCString& SimpleMessage :: GetSubject() const
{
	return m_Message->GetHeaders().GetSubject().GetString();
}

void SimpleMessage :: SetSubject(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetSubject().SetString(vsscStr);
}

const VSSCString& SimpleMessage :: GetDate() const
{
	return m_Message->GetHeaders().GetDate().GetString();
}

void SimpleMessage :: SetDate(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetDate().SetString(vsscStr);
}

const VSSCString& SimpleMessage :: GetCteStr() const
{
	return m_Message->GetHeaders().GetContentTransferEncoding().GetString();
}

int SimpleMessage :: GetCte() const
{
	return m_Message->GetHeaders().GetContentTransferEncoding().GetAsEnum();
}

void SimpleMessage :: SetCteStr(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentTransferEncoding().SetString(vsscStr);
}


void SimpleMessage :: SetCte(int nCte)
{
	m_Message->GetHeaders().GetContentTransferEncoding().SetFromEnum(nCte);
}



const VSSCString& SimpleMessage :: GetTypeStr() const
{
	return m_Message->GetHeaders().GetContentType().GetTypeString();
}

int SimpleMessage :: GetType() const
{
	return m_Message->GetHeaders().GetContentType().GetType();
}

void SimpleMessage :: SetTypeStr(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetTypeString(vsscStr);
}

void SimpleMessage :: SetType(int nType)
{
	m_Message->GetHeaders().GetContentType().SetType(nType);
}


const VSSCString& SimpleMessage :: GetSubTypeStr() const
{
	return m_Message->GetHeaders().GetContentType().GetSubTypeString();
}

int SimpleMessage :: GetSubType() const
{
	return m_Message->GetHeaders().GetContentType().GetSubType();
}

void SimpleMessage :: SetSubTypeStr(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetSubTypeString(vsscStr);
}

const VSSCString& SimpleMessage :: GetDispositionTypeStr() const
{
	return m_Message->GetHeaders().GetContentDisposition().GetDispTypeString();
}

void SimpleMessage :: SetSubType(int nSubType)
{
	m_Message->GetHeaders().GetContentType().SetSubType(nSubType);
}

int SimpleMessage :: GetDispositionType() const
{
	return m_Message->GetHeaders().GetContentDisposition().GetDispType();
}

void SimpleMessage :: SetDispositionType(int nDispType)
{
	m_Message->GetHeaders().GetContentDisposition().SetDispType(nDispType);
}

const VSSCString& SimpleMessage :: GetBody() const 
{
	return m_Message->GetBody().GetString();
}

void SimpleMessage :: SetBody(const VSSCString& vsscStr)
{
	m_Message->GetBody().SetString(vsscStr);
}

const VSSCString& SimpleMessage :: GetName() const
{
	return m_Message->GetHeaders().GetContentType().GetName();
}

void SimpleMessage :: SetNameParam(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetName(vsscStr);
}

const VSSCString& SimpleMessage :: GetContentTypeFileName() const
{
	return m_Message->GetHeaders().GetContentType().GetFileName();
}

void SimpleMessage :: SetContentTypeFileName(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetFileName(vsscStr);
}

const VSSCString& SimpleMessage :: GetDispFileName() const
{
	return m_Message->GetHeaders().GetContentDisposition().GetFileName();
}

void SimpleMessage :: SetDispFileName(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentDisposition().SetFileName(vsscStr);
}

const VSSCString& SimpleMessage :: GetSMIMEType() const
{
	return m_Message->GetHeaders().GetContentType().GetSMIMEType();
}

void SimpleMessage :: SetSMIMEType(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetSMIMEType(vsscStr);
}

const VSSCString& SimpleMessage :: GetProtocol() const
{
	return m_Message->GetHeaders().GetContentType().GetProtocol();
}

void SimpleMessage :: SetProtocol(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetProtocol(vsscStr);
}

const VSSCString& SimpleMessage :: GetMicalg() const
{
	return m_Message->GetHeaders().GetContentType().GetMicalg();
}

void SimpleMessage :: SetMicalg(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetMicalg(vsscStr);
}

const VSSCString& SimpleMessage :: GetCharset() const
{
	return m_Message->GetHeaders().GetContentType().GetCharset();
}

void SimpleMessage :: SetCharset(const VSSCString& vsscStr)
{
	m_Message->GetHeaders().GetContentType().SetCharset(vsscStr);
}

int SimpleMessage :: GetMsgType()
{
	int nType = GetType();
	int nSubType = GetSubType();
	VSSCString vsscSubtype = GetSubTypeStr();
	int nRet = eUnknown;
	VSSCString vsscStr;

	if(nType == VSSCEnumMime :: eTypeMultipart && nSubType == VSSCEnumMime :: eSubtypeSigned)
	{
		nRet = eClearSigned;
		
	}
	else if(nType == VSSCEnumMime :: eTypeApplication && 
		(VSSCStrcasecmp(vsscSubtype, "pkcs7-mime") == 0 ||
			VSSCStrcasecmp(vsscSubtype, "x-pkcs7-mime") == 0 ))
	{
		vsscStr = GetSMIMEType();
		if(VSSCStrcasecmp(vsscStr, "enveloped-data") == 0)
		{
			nRet = eEncrypted;
		}
		else if(VSSCStrcasecmp(vsscStr, "signed-data") == 0)
		{
			nRet = eOpaqueSigned;
		}
	}
	else
	{
		nRet = nType;
	}
	return nRet;
	
}



void SimpleMessage :: Assemble()
{
	m_Message->Assemble();
}


void SimpleMessage :: SetDefaultFields()
{
	VSSCHeaders& Headers = m_Message->GetHeaders();
	Headers.GetMimeVersion().SetString("1.0");
}



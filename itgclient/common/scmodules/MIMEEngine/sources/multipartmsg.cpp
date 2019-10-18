#include "multipartmsg.h"
#include "vsscenum.h"
#include "vsscbody.h"

BodyPart :: BodyPart()
:m_Type("Text"),
 m_Subtype("Plain"),
 m_Cte("7bit")
{
}

BodyPart :: ~BodyPart()
{

}

const VSSCString& BodyPart :: GetTypeStr() const
{
	return m_Type;
}

int BodyPart :: GetType() const
{
	int nRet = VSSCTypeStrToEnum(m_Type);
	return nRet;
		
}

void BodyPart :: SetTypeStr(const VSSCString& vsscStr)
{
	m_Type = vsscStr;
}

const VSSCString& BodyPart :: GetSubTypeStr() const
{
	return m_Subtype;
}

int BodyPart :: GetSubType() const
{
	int nRet = VSSCSubtypeStrToEnum(m_Subtype);
	return nRet;
}

void BodyPart :: SetSubTypeStr(const VSSCString& vsscStr)
{
	m_Subtype = vsscStr;
}

const VSSCString& BodyPart :: GetCteStr() const
{
	return m_Cte;
}

int BodyPart :: GetCte() const
{
//	int nRet = VSSCCteStrToEnum(m_Cte);
	return 0;
}

void BodyPart :: SetCteStr(const VSSCString& vsscStr)
{
	m_Cte = vsscStr;
}

const VSSCString& BodyPart :: GetContentDispType() const
{
	return m_ContentDisposition;
}

void BodyPart :: SetContentDispType(const VSSCString& vsscStr)
{
	m_ContentDisposition = vsscStr;
}


const VSSCString& BodyPart :: GetDispFileName() const
{
	return m_DispFileName;
}

void BodyPart :: SetDispFileName(const VSSCString& vsscStr)
{
	m_DispFileName = vsscStr;
}


const VSSCString& BodyPart :: GetContentTypeName() const
{
	return m_ContentTypeName;
}

void BodyPart :: SetContentTypeName(const VSSCString& vsscStr)
{
	m_ContentTypeName = vsscStr;
}

const VSSCString& BodyPart :: GetBody() const
{
	return m_Body;
}

void BodyPart :: SetBody(const VSSCString& vsscStr)
{
	m_Body = vsscStr;
}

const VSSCString& BodyPart :: GetEntityStr() const
{
	return m_Entity;
}

void BodyPart :: SetEntityStr(const VSSCString& vsscStr)
{
	m_Entity = vsscStr;
}

const VSSCString& BodyPart :: GetCharset() const
{
	return m_Charset;
}

void BodyPart :: SetCharset(const VSSCString& vsscStr)
{
	m_Charset = vsscStr;
}



/////////////////Implementation of MultipartMessage

MultipartMessage :: MultipartMessage()
{

}

//MultipartMessage :: MultipartMessage(VSSCMessage* msg)
MultipartMessage :: MultipartMessage(VSSCEntity* msg)
:SimpleMessage(msg)
{

}


MultipartMessage :: ~MultipartMessage()
{

}

int MultipartMessage :: GetNumofBodyParts() const
{
	int nBodyParts = m_Message->GetBody().GetNumofBodyParts();
	return nBodyParts;

}

void MultipartMessage :: GetBodyPart(int nIndex, BodyPart& part)
{

	// We set the all the required values by calling Set functions on BodyPart.

	VSSCBodyPart *bdPart = 0;
	if(nIndex >= 0 && nIndex < m_Message->GetBody().GetNumofBodyParts())
		bdPart = &m_Message->GetBody().GetBodyPart(nIndex);

	if(bdPart != 0)
	{
		VSSCHeaders& headers = bdPart->GetHeaders();

		// Content Type
		if(headers.IsContentTypePresent())
		{
			VSSCString vsscType = headers.GetContentType().GetTypeString();
			VSSCString vsscSubtype = headers.GetContentType().GetSubTypeString();
			VSSCString vsscName = headers.GetContentType().GetName();
			VSSCString vsscCharset = headers.GetContentType().GetCharset();
			part.SetTypeStr(vsscType);
			part.SetSubTypeStr(vsscSubtype);
			part.SetContentTypeName(vsscName);
			part.SetCharset(vsscCharset);

		}
		else
		{
			// Set to defaults
			part.SetTypeStr("Text");
			part.SetSubTypeStr("Plain");
			part.SetContentTypeName("");
			part.SetCharset("");
		}

		// Cte
		if(headers.IsContentTranserEncodingPresent())
		{
			VSSCString vsscCte = headers.GetContentTransferEncoding().GetString();
			part.SetCteStr(vsscCte);

		}
		else
		{
			// Set to default
			part.SetCteStr("7bit");
		}

		// ContentDisposition
		if(headers.IsContentDispositionPresent())
		{
			VSSCString vsscDisp = headers.GetContentDisposition().GetDispTypeString();
			part.SetContentDispType(vsscDisp);
			VSSCString vsscFileName = headers.GetContentDisposition().GetFileName();
			part.SetDispFileName(vsscFileName);
		}
		else
		{
			part.SetContentDispType("");
			part.SetDispFileName("");
		}

		// body
		VSSCString vsscBody = bdPart->GetBody().GetString();
		part.SetBody(vsscBody);

		// entity
		VSSCString vsscEntity = m_Message->GetBody().GetBodyPart(nIndex).GetString();
		part.SetEntityStr(vsscEntity);
	}
	else
	{
		part.SetTypeStr("");
		part.SetSubTypeStr("");
		part.SetContentTypeName("");
		part.SetCharset("");
		part.SetCteStr("");
		part.SetContentDispType("");
		part.SetDispFileName("");
		part.SetBody("");

	}

}

void MultipartMessage :: SetBodyPart (int nIndex, const BodyPart& part)
{
	VSSCBody& body = m_Message->GetBody();
	int nBodyParts = body.GetNumofBodyParts();
	VSSCBodyPart *bodyPart = 0;
	
	if(nIndex >=0 && nIndex < nBodyParts)
	{
		bodyPart = &(body.GetBodyPart(nIndex));
	}
	else if(nIndex > nBodyParts)
	{
		while(nIndex > nBodyParts)
		{
			bodyPart = VSSCBodyPart :: NewBodyPart(m_EmptyStr, 0);
			body.AddBodyPart(bodyPart);
			nBodyParts ++;
		}

	}
	else // if nIndex < 0
	{
		return;
	}

	VSSCString vsscType = part.GetTypeStr();
	VSSCString vsscSubType = part.GetSubTypeStr();
	VSSCString vsscCte = part.GetCteStr();
	VSSCString vsscDisp = part.GetContentDispType();
	VSSCString vsscName = part.GetContentTypeName();
	VSSCString vsscDispFileName = part.GetDispFileName();
	VSSCString vsscBody = part.GetBody();

	VSSCHeaders& headers = bodyPart->GetHeaders();
	
	if(vsscType != "" && vsscSubType != "")
	{
		headers.GetContentType().SetTypeString(vsscType);
		headers.GetContentType().SetSubTypeString(vsscSubType);
	}

	if(vsscCte != "")
	{
		headers.GetContentTransferEncoding().SetString(vsscCte);
	}

	if(vsscDisp != "")
	{
		headers.GetContentDisposition().SetDispTypeString(vsscDisp);
	}

	if(vsscName != "")
	{
		headers.GetContentType().SetName(vsscName);
	}

	if(vsscDispFileName != "")
	{
		headers.GetContentDisposition().SetFileName(vsscDispFileName);
	}


	bodyPart->GetBody().SetString(vsscBody);
	


}

void MultipartMessage :: AddBodyPart(const BodyPart& part)
{
	VSSCBodyPart *bodyPart = VSSCBodyPart :: NewBodyPart(m_EmptyStr, 0);

	VSSCString vsscType = part.GetTypeStr();
	VSSCString vsscSubType = part.GetSubTypeStr();
	VSSCString vsscCte = part.GetCteStr();
	VSSCString vsscDisp = part.GetContentDispType();
	VSSCString vsscName = part.GetContentTypeName();
	VSSCString vsscDispFileName = part.GetDispFileName();
	VSSCString vsscBody = part.GetBody();

	VSSCHeaders& headers = bodyPart->GetHeaders();
	
	if(vsscType != "" && vsscSubType != "")
	{
		headers.GetContentType().SetTypeString(vsscType);
		headers.GetContentType().SetSubTypeString(vsscSubType);
	}

	if(vsscCte != "")
	{
		headers.GetContentTransferEncoding().SetString(vsscCte);
	}

	if(vsscDisp != "")
	{
		headers.GetContentDisposition().SetDispTypeString(vsscDisp);
	}

	if(vsscName != "")
	{
		headers.GetContentType().SetName(vsscName);
	}

	if(vsscDispFileName != "")
	{
		headers.GetContentDisposition().SetFileName(vsscDispFileName);
	}

	bodyPart->GetBody().SetString(vsscBody);
	m_Message->GetBody().AddBodyPart(bodyPart);


}     

void MultipartMessage :: CreateBoundary()
{
	m_Message->GetHeaders().GetContentType().CreateBoundary();
}

void MultipartMessage :: SetDefaultFields()
{
	SimpleMessage :: SetDefaultFields();
	VSSCMediaType& ContentType = m_Message->GetHeaders().GetContentType();
	CreateBoundary();
}
#ifndef _MULTIPARTMESSAGE
#define _MULTIPARTMESSAGE

#include "vsscstring.h"
#include "simplemsg.h"

class BodyPart
{
public:
	BodyPart();
	~BodyPart();
	const VSSCString& GetTypeStr() const;
	int GetType() const;
	void SetTypeStr(const VSSCString& vsscStr);

	const VSSCString& GetSubTypeStr() const;
	int GetSubType() const;
	void SetSubTypeStr(const VSSCString& vsscStr);

	const VSSCString& GetCteStr() const;
	int GetCte() const;
	void SetCteStr(const VSSCString& vsscStr);

	const VSSCString& GetContentDispType() const;
	void SetContentDispType(const VSSCString& vsscStr);

	const VSSCString& GetDispFileName() const;
	void SetDispFileName(const VSSCString& vsscStr);

	const VSSCString& GetContentTypeName() const;
	void SetContentTypeName(const VSSCString& vsscStr);

	const VSSCString& GetBody() const;
	void SetBody(const VSSCString& vsscStr);

	const VSSCString& GetEntityStr() const;
	void SetEntityStr(const VSSCString& vsscStr);

	
	const VSSCString& GetCharset() const;
	void SetCharset(const VSSCString& vsscStr);


protected:
    VSSCString m_Type;
    VSSCString m_Subtype;
    VSSCString m_Cte;
    //VSSCString m_ContentDescription;
    VSSCString m_ContentDisposition;
	VSSCString m_DispFileName;
	VSSCString m_ContentTypeName;
    VSSCString m_Body;
	VSSCString m_Entity;
	VSSCString m_Charset;
};


class MultipartMessage : public SimpleMessage
{
public:
	MultipartMessage();
	//MultipartMessage(VSSCMessage* msg);
	MultipartMessage(VSSCEntity* msg);

	virtual ~MultipartMessage();

	int GetNumofBodyParts() const;

	void GetBodyPart(int nIndex, BodyPart& part);
	void SetBodyPart(int nIndex, const BodyPart& part);
	void AddBodyPart(const BodyPart& part);

	void CreateBoundary();

	virtual void SetDefaultFields();
	
};


#endif // _MULTIPARTMESSAGE
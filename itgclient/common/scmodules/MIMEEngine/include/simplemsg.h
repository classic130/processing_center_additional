#ifndef _SIMPLEMESSAGE
#define _SIMPLEMESSAGE

#include "vsscstring.h"
#include "vsscmessage.h"

/*
#if defined(__cplusplus)
extern "C"
{
#endif
*/


enum MsgType
{
	eClearSigned=100,
	eOpaqueSigned,
	eEncrypted,
	eNoHeaders,
	eUnknown
};

class SimpleMessage
{
public:
	SimpleMessage();
	//SimpleMessage(VSSCMessage* msg);
	SimpleMessage(VSSCEntity* Entity);

	virtual ~SimpleMessage();

	const VSSCString& GetFrom() const;
	void SetFrom(const VSSCString& vsscStr);

	const VSSCString& GetTo() const;
	void SetTo(const VSSCString& vsscStr);

	const VSSCString& GetCc() const;
	void SetCc(const VSSCString& vsscStr);

	const VSSCString& GetBcc() const;
	void SetBcc(const VSSCString& vsscStr);

	const VSSCString& GetSubject() const;
	void SetSubject(const VSSCString& vsscStr);

	const VSSCString& GetDate() const;
	void SetDate(const VSSCString& vsscStr);

	const VSSCString& GetCteStr() const;
	int GetCte() const;
	void SetCteStr(const VSSCString& vsscStr);
	void SetCte(int nCte);


	const VSSCString& GetTypeStr() const;
	int GetType() const;
	void SetTypeStr(const VSSCString& vsscStr);
	void SetType(int nType);

	const VSSCString& GetSubTypeStr() const;
	int GetSubType() const;
	void SetSubTypeStr(const VSSCString& vsscStr);
	void SetSubType(int nSubType);

	const VSSCString& GetDispositionTypeStr() const;
	int GetDispositionType() const;
	void SetDispositionTypeStr(const VSSCString& vsscStr);
	void SetDispositionType(int nDispType);


	// Gets the Name parameter from ContentType field
	const VSSCString& GetName() const;
	void SetNameParam(const VSSCString& vsscStr);

	// FileName parameter of Content-Type
	const VSSCString& GetContentTypeFileName() const;
	void SetContentTypeFileName(const VSSCString& vsscStr);

	// FileName parameter of Disposition-Type
	const VSSCString& GetDispFileName() const;
	void SetDispFileName(const VSSCString& vsscStr);

	// smime-type parameter of Content-type
	const VSSCString& GetSMIMEType() const;
	void SetSMIMEType(const VSSCString& vsscStr);

	// for signed messages.
	const VSSCString& GetProtocol() const;
	void SetProtocol(const VSSCString& vsscStr);

	const VSSCString& GetMicalg() const;
	void SetMicalg(const VSSCString& vsscStr);

	// Charset parameter
	const VSSCString& GetCharset() const;
	void SetCharset(const VSSCString& vsscStr);



	const VSSCString& GetString() const ;

	const VSSCString& GetBody() const ;
	void SetBody(const VSSCString& vsscStr);

	int GetMsgType(); 

	void Assemble();

	virtual void SetDefaultFields();


protected:
	//VSSCMessage *m_Message;

	// Using the Base Class pointer so that Message or BodyPart can be used - ex of polymorphism.
	VSSCEntity *m_Message; 
	VSSCString m_EmptyStr;

};

/*
#if defined(__cplusplus)
}
#endif 
*/


#endif // _SIMPLEMSSAGE
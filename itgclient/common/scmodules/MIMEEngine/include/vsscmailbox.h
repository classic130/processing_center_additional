#ifndef _VSSCMAILBOX
#define _VSSCMAILBOX

#include "vsscaddress.h"
class VSSCMailBox : public VSSCAddress
{
public:
	VSSCMailBox();
	VSSCMailBox(const VSSCMailBox& mbMailBox);
	VSSCMailBox(const VSSCString& vsscString, VSSCMsgComponent *Parent = 0);

	virtual ~VSSCMailBox();

	const VSSCMailBox& operator = (const VSSCMailBox& mbBox);
	
	void SetFullName(const VSSCString& vsscString);
	const VSSCString& GetFullName() const;

	void SetLocalPart(const VSSCString& vsscString);
	const VSSCString& GetLocalPart() const;

	void SetDomain(const VSSCString* vsscString);
	const VSSCString& GetDomain() const;
	static VSSCMailBox* NewMailbox(const VSSCString& vsscString, VSSCMsgComponent *Parent);

	virtual void Parse();
	virtual void Assemble();

	virtual VSSCMsgComponent* Clone() const;


private:
	VSSCString m_vsscFullName;
	VSSCString m_vsscLocalPart;
	VSSCString m_vsscDomain;
};


#endif //_VSSCMAILBOX

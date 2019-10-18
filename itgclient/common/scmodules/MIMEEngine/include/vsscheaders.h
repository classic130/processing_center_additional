#ifndef _VSSCHEADERS
#define _VSSCHEADERS

#include "vsscstring.h"
#include "vsscmsgcmp.h"
#include "fieldbody.h"
#include "vsscfield.h"
#include "vsscmailboxlist.h"
#include "vssctext.h"
#include "vsscmediatype.h"
#include "vsscmechanism.h"
#include "vsscdisposition.h"

class VSSCHeaders : public VSSCMsgComponent
{
	// Pointers to list of fields 

public:
	//Constructors
	VSSCHeaders();
	VSSCHeaders(const VSSCHeaders& hHeaders);
	VSSCHeaders(const VSSCString& vsscString, VSSCMsgComponent *Parent = 0);

	//Destructor
	virtual ~VSSCHeaders();

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;

	_BOOL IsFieldPresent(VSSCString& vsscFieldName) const;
	_BOOL IsFieldPresent(char* szFieldName) const;

	// RFC 822 headers
	_BOOL IsFromPresent();
	_BOOL IsToPresent();
	_BOOL IsCcPresent();
	_BOOL IsBccPresent();
	_BOOL IsDatePresent();
	_BOOL IsSubjectPresent();

	// RFC 2045 headers
	_BOOL IsContentTypePresent();
	_BOOL IsContentTranserEncodingPresent();
	_BOOL IsContentDispositionPresent();
	_BOOL IsMimeVersionPresent();

	VSSCMailboxList& GetFrom();
	VSSCMailboxList& GetTo();
	VSSCMailboxList& GetCc();
	VSSCMailboxList& GetBcc();
	VSSCText& GetDate();
	VSSCText& GetSubject();
	VSSCText& GetMimeVersion();

	VSSCMediaType& GetContentType();
	VSSCMechanism& GetContentTransferEncoding();
	VSSCDisposition& GetContentDisposition();

	// Get the FieldBody class given a FieldName
	// If the FieldBody does not exist create it.
	VSSCFieldBody& GetFieldBody(const char* szFieldName);

	int GetNumofFields() const;

	void AddField(VSSCField* Field);
	void DeleteAllFields();
	void InsertFieldAtPos(int nIndex, VSSCField* Field);

	VSSCField& GetFieldAtPos(int nIndex);

	VSSCField* FindField(const VSSCString& vsscFieldName) const;
	VSSCField* FindField(const char* szFieldName) const;

	static VSSCHeaders* NewHeaders(const VSSCString& vsscString, VSSCMsgComponent* Parent);

	const VSSCHeaders& operator = (const VSSCHeaders& Headers);

protected:

	void _AddField(VSSCField* Field);
	void _DeleteAllFields();
	void _InsertFieldAtPos(int nIndex, VSSCField* Field);
	void _CopyFields(const VSSCHeaders& Headers);

private:
	VSSCField **m_Fields;
	int m_nFields;
	int m_nFieldsSize;

	void _Initialize();

};


// Headers Parser

class VSSCHeadersParser
{
	friend class VSSCHeaders;

public:
	VSSCHeadersParser(const VSSCString& vsscString);
	void ParseNextField(VSSCString& vsscString);

private:
	VSSCString m_vsscString;
	_DWORD m_dwPos;

};



#endif // _VSSCHEADERS
#ifndef _VSSCFIELD
#define _VSSCFIELD

#include "vsscstring.h"
#include "vsscmsgcmp.h"
#include "fieldbody.h"
#include "vssctext.h"
#include "vsscmediatype.h"
#include "vsscmechanism.h"
#include "vsscdisposition.h"



class VSSCField : public VSSCMsgComponent
{
public: 
	// Constructors
	VSSCField();
	VSSCField(const VSSCField& fField);
	VSSCField(const VSSCString& vsscString , VSSCMsgComponent *Parent=0);

	// Destructor
	~VSSCField();

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;

	void SetFieldName(const VSSCString& vsscString);
	const VSSCString& GetFieldName() const;

	void SetFieldBodyString(const VSSCString& vsscString);
	const VSSCString& GetFieldBodyString() const;
	
	VSSCFieldBody* GetFieldBody() const;
	void SetFieldBody(VSSCFieldBody* fbFieldBody);

	static VSSCField* NewField(const VSSCString& vsscString, VSSCMsgComponent *Parent);

	static VSSCFieldBody* CreateFieldBody(const VSSCString& vsscFieldName, const VSSCString& vsscFieldBody,
			VSSCMsgComponent *Parent);

	static VSSCFieldBody* _CreateFieldBody(const VSSCString& vsscFieldName, const VSSCString& vsscFieldBody,
			VSSCMsgComponent *Parent);

private:
	VSSCString m_vsscFieldName;
	VSSCString m_vsscFieldBody;
	VSSCFieldBody *m_fbFieldBody;
	
	void _SetFieldBody(VSSCFieldBody* fbFieldBody);


};

class VSSCFieldParser
{
	friend class VSSCField;	
public:
	VSSCFieldParser(const VSSCString& vsscString);
	void Parse();
private:
	VSSCString m_vsscName;
	VSSCString m_vsscBody;
	VSSCString m_vsscString;
};


#endif // _VSSCFIELD
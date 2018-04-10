#ifndef _VSSCENTITY
#define _VSSCENTITY

//#include "vsscbody.h"
#include "vsscstring.h"
#include "vsscmsgcmp.h"
#include "vsscheaders.h"

class VSSCBody;


class EntityParser
{
friend class VSSCEntity;

public:
	EntityParser(const VSSCString& vsscString);
private:
	VSSCString m_vsscHeaders;
	VSSCString m_vsscBody;
	VSSCString m_vsscStr;
	void Parse();

};

class VSSCEntity : public VSSCMsgComponent
{
public:
	VSSCEntity();
	VSSCEntity(const VSSCEntity& Entity);
	VSSCEntity(const VSSCString& vsscString, VSSCMsgComponent* Parent);
	
	virtual ~VSSCEntity();


	virtual void Assemble();
	virtual void Parse();

	const VSSCEntity& operator = (const VSSCEntity& Entity);

	VSSCHeaders& GetHeaders() const;
	VSSCBody& GetBody() const ;

	// This function sets the m_bAssembled to TRUE
	// If this is set to true Assembled function won't be called.
	// m_bAssembled is set to FALSE in the constructor.
	// This function is mainly called for the bodypart class 
	// when the complete entity is set as the string
	// useful for SMIME
	void SetAssembled();
	

protected:
	VSSCHeaders* m_Headers;
	VSSCBody* m_Body;
	_BOOL m_bAssembled;

};

#endif // _VSSCENTITY

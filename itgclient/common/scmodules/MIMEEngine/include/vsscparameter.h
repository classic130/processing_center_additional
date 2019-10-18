#ifndef _VSSCPARAMETER
#define _VSSCPARAMETER

#include "vsscmsgcmp.h"

class VSSCParameter : public VSSCMsgComponent
{
public:
	VSSCParameter();
	VSSCParameter(const VSSCParameter& Parameter);
	VSSCParameter(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);
	virtual ~VSSCParameter();

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;

	void SetAttribute(const VSSCString& vsscString);
	const VSSCString& GetAttribute() const;

	void SetValue(const VSSCString& vsscString);
	const VSSCString& GetValue();

	static VSSCParameter* NewParameter(const VSSCString& vsscString, VSSCMsgComponent* Parent);
	const VSSCParameter& operator = (const VSSCParameter& Parameter);



private:
	VSSCString m_vsscAttribute;
	VSSCString m_vsscValue;

};


#endif // _VSSCPARAMETER
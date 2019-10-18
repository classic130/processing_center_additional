#ifndef _VSSCTEXT
#define _VSSCTEXT

#include "vsscstring.h"
#include "fieldbody.h"

// This class does not support Encoded Text
// Its a very simple implementation of a Text which is used for unstructured 
// fields like Subject.

class VSSCText : public VSSCFieldBody
{
public:

	// Constructors
	VSSCText();
	VSSCText(const VSSCText& Text);
	VSSCText(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);

	virtual ~VSSCText();

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;

	static VSSCText* NewText(const VSSCString& vsscString, VSSCMsgComponent* Parent);
	const VSSCText& operator = (const VSSCText& Text);

};

#endif // _VSSCTEXT
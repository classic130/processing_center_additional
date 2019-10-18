#ifndef _VSSCBODYPART
#define _VSSCBODYPART

#include "vsscentity.h"

class VSSCBodyPart : public VSSCEntity
{
public:
	VSSCBodyPart();
	VSSCBodyPart(const VSSCBodyPart& BodyPart);
	VSSCBodyPart(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);

	virtual ~VSSCBodyPart();

	virtual VSSCMsgComponent* Clone() const;

	const VSSCBodyPart& operator = (const VSSCBodyPart& BodyPart);
	static VSSCBodyPart* NewBodyPart(const VSSCString& vsscString,
				VSSCMsgComponent* Parent);
	
};

#endif // _VSSCBODYPART
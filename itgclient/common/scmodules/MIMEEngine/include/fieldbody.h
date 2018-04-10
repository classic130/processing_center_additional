#ifndef _VSSCFIELDBODY
#define _VSSCFIELDBODY

#include  "vsscmsgcmp.h"

// Abstract class
// Parent of this will be Field class and can have
// and can have more than one children


class VSSCFieldBody : public VSSCMsgComponent
{

public:
	VSSCFieldBody();
    VSSCFieldBody(const VSSCFieldBody& fbFieldBody);
    VSSCFieldBody(const VSSCString& vsscString, VSSCMsgComponent* Parent=0);

	//Virtual destructor
	virtual ~VSSCFieldBody();

	// Assignment operator for deep copy
	const VSSCFieldBody& operator = (const VSSCFieldBody& fbFieldBody);

	// Default is to fold fields
	// True - Folding
	// False - NoFolding
    void SetFolding(_BOOL bFolding);
    
	//. Returns a boolean indicating if folding of fields is enabled.
    _BOOL IsFolding() const;
    

protected:

   _BOOL m_bFolding;

};


#endif // _VSSCFIELDBODY
#ifndef _VSSCMSGCMP
#define _VSSCMSGCMP


#include "vsscstring.h"
// This class is the base class for all the other message component classes

class VSSCMsgComponent
{
public:

	enum componentType {
        eCtError=-1,
        eCtUnknown=0,
        eCtAddress,
        eCtAddressList,
        eCtBody,
        eCtBodyPart,
        eCtDispositionType,
        eCtMechanism,
        eCtMediaType,
        eCtParameter,
        eCtDateTime,
        eCtEntity,
        eCtField,
        eCtFieldBody,
        eCtGroup,
        eCtHeaders,
        eCtMailbox,
        eCtMailboxList,
        eCtMessage,
        eCtMessageComponent,
        eCtMsgId,
        eCtStamp,
        eCtText,
        eCtEncodedWord
    };


	VSSCMsgComponent();
	VSSCMsgComponent(const VSSCMsgComponent& vsscMsgCmp);
	VSSCMsgComponent(const VSSCString& vsscString, VSSCMsgComponent *Parent);

	virtual ~VSSCMsgComponent();

	// Sets the object's string representation.
	// After setting this string parse() has to called.
	void SetString(const VSSCString& vsscString);
	void SetString(const char* szString);

	// Get the string representation of the object.
	// This function will be called after a call to Assemble()
	const VSSCString& GetString() const;

	int GetCmpType();
	
	virtual void Assemble() = 0;
	virtual void Parse() = 0;

	const VSSCMsgComponent& operator = (const VSSCMsgComponent& vsscMsgCmp);

	VSSCMsgComponent* GetParent();
	void SetParent(VSSCMsgComponent *Parent);

	virtual VSSCMsgComponent* Clone() const = 0;

	
protected:

	// String representation 
	VSSCString m_vsscString;


    // Component that contains this component
	// This is used only if IsModified behaviour is supported.
	// Not decided whether this is needed.
	// This is need otherwise too.
	VSSCMsgComponent* m_Parent;


	// Type indentification of the class;
	componentType m_ComponentType;
    

};




#endif // _VSSCMSGCMP
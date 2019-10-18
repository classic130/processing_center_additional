#ifndef _VSSCMECHANISM
#define _VSSCMECHANISM

class VSSCMechanism : public VSSCFieldBody
{
public:

	//constructors
	VSSCMechanism();
	VSSCMechanism(const VSSCMechanism& Mechnsm);
	VSSCMechanism(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);

	virtual ~VSSCMechanism();

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;
	int GetAsEnum() const;
	void SetFromEnum(int nCte);
	

	static VSSCMechanism* NewMechanism(const VSSCString& vsscString,
			VSSCMsgComponent* Parent);

	const VSSCMechanism& operator = (const VSSCMechanism& Mechnsm) ;



private:
	int m_nCteEnum;

	void _EnumToString();
	void _StringToEnum();

};

#endif // _VSSCMECHANISM
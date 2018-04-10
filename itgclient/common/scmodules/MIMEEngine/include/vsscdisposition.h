#ifndef _VSSCDISPOSITION
#define _VSSCDISPOSITION

#include "fieldbody.h"
#include "vsscparameter.h"

class VSSCDisposition : public VSSCFieldBody
{

public:
	//constructor
	VSSCDisposition();
	VSSCDisposition(const VSSCDisposition& Disp);
	VSSCDisposition(const VSSCString& vsscString,
		VSSCMsgComponent* Parent =0);
	
	virtual ~VSSCDisposition();

	int GetNumofParmeters () const;	

	void AddParameter(VSSCParameter* Parameter);
	void DeleteAllParameters();
	VSSCParameter& GetParameter(int nIndex) const;
	const VSSCDisposition& operator = (const VSSCDisposition& Disp);

	const VSSCString& GetDispTypeString() const;
	void SetDispTypeString(const VSSCString& vsscString);
	const int GetDispType();
	void SetDispType(int nDispType);

	const VSSCString& GetFileName() const;
	void SetFileName(const VSSCString& vsscString);

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;

	static VSSCDisposition* NewDisposition(const VSSCString& vsscString,
		VSSCMsgComponent* Parent);


protected:

	int m_nDispType;
	VSSCString m_vsscDispType;
	VSSCString m_vsscFileName;

	void _EnumToStr();
    void _StrToEnum();


	void _CopyAllParameters(const VSSCDisposition& Disp);
	void _AddParameter(VSSCParameter* Parameter);
	void _DeleteAllParameters();
	void _InsertParameter(int nIndex, VSSCParameter* Parameter);

private:
	int m_nSizeofParameter;
	int m_nParameters;
	VSSCParameter **m_Parameters;

	void _Initialize();


};

#endif // _VSSCDISPOSITION
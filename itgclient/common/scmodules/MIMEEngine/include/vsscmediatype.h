#ifndef _VSSCMEDIATYPE
#define _VSSCMEDIATYPE


#include "vsscstring.h"
#include "vsscmsgcmp.h"
#include "fieldbody.h"
#include "vsscparameter.h"

#if defined(__cplusplus)
extern "C"
{
#endif

class VSSCMediaType : public VSSCFieldBody
{

public:
	// constructors
	VSSCMediaType();
	VSSCMediaType(const VSSCMediaType& MediaType);
	VSSCMediaType(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);


	virtual ~VSSCMediaType();

	void SetTypeString(const VSSCString& vsscString);
	const VSSCString& GetTypeString() const;
	void SetType(const int nType);
	const int GetType() const;
	
	void SetSubTypeString(const VSSCString& vsscString);
	const VSSCString& GetSubTypeString() const;
	void SetSubType(const int nSubType);
	const int GetSubType() const;

	int GetNumofParmeters () const;

	void AddParameter(VSSCParameter* Parameter);
	void DeleteAllParameters();
	VSSCParameter& GetParameter(int nIndex) const;
	const VSSCMediaType& operator = (const VSSCMediaType& MediaType);

	virtual VSSCMsgComponent* Clone() const;
	virtual void Parse();
	virtual void Assemble();

	static VSSCMediaType* NewMediaType(const VSSCString& vsscString,
		VSSCMsgComponent* Parent);

	// Most Commonly used attributes.
	const VSSCString& GetBoundary() const;
	void SetBoundary(const VSSCString& vsscStr);
	void CreateBoundary();

	
	const VSSCString& GetName() const;
	void SetName(const VSSCString& vsscStr);

	const VSSCString& GetProtocol() const;
	void SetProtocol(const VSSCString& vsscStr);

	const VSSCString& GetFileName() const;
	void SetFileName(const VSSCString& vsscStr);

	const VSSCString& GetSMIMEType() const;
	void SetSMIMEType(const VSSCString& vsscStr);

	const VSSCString& GetMicalg() const;
	void SetMicalg(const VSSCString& vsscStr);

	const VSSCString& GetCharset() const;
	void SetCharset(const VSSCString& vsscStr);

	char *GenBoundary();


protected:
	VSSCString m_vsscType;
	VSSCString m_vsscSubType;

	// Most commonly used attributes
	VSSCString m_vsscBoundary;
	VSSCString m_vsscName;
	VSSCString m_vsscProtocol;
	VSSCString m_vsscFileName;
	VSSCString m_vsscSMIMEType;
	VSSCString m_vsscMicalg;
	VSSCString m_vsscCharSet;


	int m_nType;
	int m_nSubType;

	void _CopyAllParameters(const VSSCMediaType& MediaType);
	void _AddParameter(VSSCParameter* Parameter);
	void _DeleteAllParameters();
	void _InsertParameter(int nIndex, VSSCParameter* Parameter);

	void _TypeEnumToStr();
    void _TypeStrToEnum();
    void _SubtypeEnumToStr();
    void _SubtypeStrToEnum();
	
	

	void _GetRandomString(char *szData, int len);


private:
	int m_nSizeofParameter;
	int m_nParameters;
	VSSCParameter **m_Parameters;

	void _Initialize();

};


#if defined(__cplusplus)
}
#endif 



#endif // _VSSCMEDIATYPE
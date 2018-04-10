#ifndef _VSSCBODY
#define _VSSCBODY

#include "vsscbodypart.h"
#include "vsscstring.h"
#include "vsscmsgcmp.h"


class VSSCBody : public VSSCMsgComponent
{
public:
	VSSCBody();
	VSSCBody(const VSSCBody& Body);
	VSSCBody(const VSSCString& vsscString, VSSCMsgComponent* Parent = 0);

	virtual ~VSSCBody();

	virtual void Parse();
	virtual void Assemble();
	virtual VSSCMsgComponent* Clone() const;

	void AddBodyPart(VSSCBodyPart* BodyPart);
	void DeleteAllBodyParts();

	VSSCBodyPart& GetBodyPart(int nIndex) const;
	const VSSCBody& operator = (const VSSCBody& Body);


	int GetNumofBodyParts() const;
	static VSSCBody* NewBody(const VSSCString& vsscString,
		VSSCMsgComponent* Parent);

protected:
	void _CopyAllBodyParts(const VSSCBody& Body);
	void _AddBodyPart(VSSCBodyPart* BodyPart);
	void _DeleteAllBodyParts();
	void _InsertBodyPart(int nIndex, VSSCBodyPart* BodyPart);


private:
	int m_nSizeofBodyParts;
	int m_nBodyParts;
	VSSCBodyPart **m_BodyParts;
	void _Initialize();

};

enum {
    eParseSuccess,
    eParseFail
};

struct BodypartList
{
	BodypartList(const VSSCString& vsscStr) : m_vsscString(vsscStr), m_next(0) {}
	VSSCString m_vsscString;
	BodypartList* m_next;
};

class VSSCBodyParser
{
	friend class VSSCBody;
public:
	~VSSCBodyParser();
private:
	VSSCBodyParser(const VSSCString& vsscString, const VSSCString& vsscBoundary);

	BodypartList* GetFirstBodypart() const {return m_StartList;}
	int Parse();
    int FindBoundary(_DWORD aStartPos, _DWORD* dwBoundaryStart, 
        _DWORD* dwBoundaryEnd, _BOOL* bFinal) const;
	void AddPart(_DWORD dwStart, _DWORD dwLen);
	void DeleteBodyParts();

	BodypartList* m_StartList;
	VSSCString m_vsscBoundary;
	VSSCString m_vsscString;
};

#endif // _VSSCBODY
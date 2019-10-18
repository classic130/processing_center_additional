#ifndef _VSSCMAILBOXLIST
#define _VSSCMAILBOXLIST

#include "vsscstring.h"
#include "vssctoken.h"
#include "fieldbody.h"
#include "vsscmailbox.h"


class VSSCMailboxList : public VSSCFieldBody
{
public:
	VSSCMailboxList();
	VSSCMailboxList(const VSSCMailboxList& vsscMBList);
	VSSCMailboxList(const VSSCString& vsscString, VSSCMsgComponent *Parent = 0);

	virtual ~VSSCMailboxList();

	void AddMailbox(VSSCMailBox *mbBox);
	void DeleteMailbox(int nIndex);
	void DeleteAllMailboxes();
	int GetNumOfMailboxes();
	VSSCMailBox& GetMailBox(int nIndex) const;
	static VSSCMailboxList* NewMailboxList(const VSSCString& vsscString,
        VSSCMsgComponent* Parent);

	virtual VSSCMsgComponent* Clone() const;
	virtual void Parse();
	virtual void Assemble();

private:
	VSSCMailBox **m_Mailboxes;
	int m_nMailboxes;
	int m_nMailboxesSize;
	void _Initialize();
	void _CopyAllMailboxes(const VSSCMailboxList& vsscMBLsit);
	void _AddMailbox(VSSCMailBox *vsscMB);
	void _DeleteAllMailboxes();
	void _InsertMailbox(int nIndex, VSSCMailBox* mbBox);


};




class VSSCMailboxListParser
{
public:
	enum
	{
		eNull,
		eError,
		eEnd,
		eMailbox
	};

	VSSCMailboxListParser(const VSSCString& vsscString);
    virtual ~VSSCMailboxListParser();
    const VSSCString& GetMboxString();
    int MboxPos();
    _BOOL IsNull();
    _BOOL IsEnd();
    int Restart();
    int operator ++ (); // prefix increment operator

protected:
   void ParseNextMailbox();
    VSSCRfc822Tokenizer m_Tokenizer;
    VSSCGroupTokens m_gtTokensString;
    int m_nPos;

};

#endif // _VSSCMAILBOXLIST
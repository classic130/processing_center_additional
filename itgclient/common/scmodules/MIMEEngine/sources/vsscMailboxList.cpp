#include <stdlib.h>
#include "defines.h"
#include "vsscmailboxlist.h"


VSSCMailboxList :: VSSCMailboxList()
{
	_Initialize();
}

VSSCMailboxList :: VSSCMailboxList(const VSSCMailboxList& vsscMBList)
: VSSCFieldBody(vsscMBList)
{
	_Initialize();
	_CopyAllMailboxes(vsscMBList);
}

VSSCMailboxList :: VSSCMailboxList(const VSSCString& vsscString, VSSCMsgComponent *Parent )
: VSSCFieldBody(vsscString, Parent)
{
	_Initialize();
}


VSSCMailboxList::~VSSCMailboxList()
{
    _DeleteAllMailboxes();
    if (m_Mailboxes != 0) {
        delete [] m_Mailboxes;
        m_Mailboxes = 0;
    }
}


void VSSCMailboxList::_DeleteAllMailboxes()
{
    while (m_nMailboxes > 0) {
        int i = m_nMailboxes - 1;
        if (m_Mailboxes[i] != 0) {
            delete m_Mailboxes[i];
            m_Mailboxes[i] = 0;
        }
        --m_nMailboxes;
    }
}


VSSCMsgComponent* VSSCMailboxList :: Clone() const
{
	 return new VSSCMailboxList(*this);
}

void VSSCMailboxList :: AddMailbox(VSSCMailBox *mbBox)
{
	_AddMailbox(mbBox);
}

void VSSCMailboxList :: DeleteAllMailboxes()
{
	_DeleteAllMailboxes();
}


int VSSCMailboxList :: GetNumOfMailboxes()
{
	return m_nMailboxes;
}



VSSCMailBox& VSSCMailboxList :: GetMailBox(int nIndex) const
{
	 if (! (0 <= nIndex && nIndex < m_nMailboxes)) {
        abort();
	 
    }
	return *m_Mailboxes[nIndex];
}

void VSSCMailboxList :: Assemble()
{

	// Assemble the list of mailboxes.
	//m_vsscString = "";
	int nCount  = 0;
	
	for(int i = 0; i < m_nMailboxes; i ++)
	{
		VSSCMailBox *mailBox = m_Mailboxes[i];
		
		mailBox->Assemble();
		
		if(nCount > 0)
		{
			if(IsFolding())
			{
				m_vsscString += "," EOL " ";
			}
			else
			{
				m_vsscString += ",";
			}
		}
		nCount++;
		m_vsscString += mailBox->GetString();
		
		
	}
	


}

void VSSCMailboxList :: Parse()
{
	   _DeleteAllMailboxes();
    // Mailboxes are separated by commas. No support for Route
    
    VSSCMailboxListParser parser(m_vsscString);
	VSSCMailBox* mailbox;
    _BOOL bDone = _FALSE;

    while (! bDone) {
        switch (parser.MboxPos()) {
        case VSSCMailboxListParser::eError:
        case VSSCMailboxListParser::eEnd:
            bDone = _TRUE;
            break;
        case VSSCMailboxListParser::eMailbox:
            mailbox = VSSCMailBox :: NewMailbox(parser.GetMboxString(), this);
            if (mailbox == 0) {
                break;
            }
            mailbox->Parse();
            _AddMailbox(mailbox);
            break;
        case VSSCMailboxListParser::eNull:
            break;
        }
        if (! bDone) {
            ++parser;
        }
    }


}


void VSSCMailboxList :: _Initialize()
{
	m_Mailboxes = 0;
	m_nMailboxes = 0;
	m_nMailboxesSize = 0;
	m_ComponentType = eCtMailboxList;

	int nSize = 10;
		
	m_Mailboxes = new VSSCMailBox* [nSize];
	if(m_Mailboxes != 0)
	{
		
		for(int i = 0; i < nSize;  i++)
		{
			m_Mailboxes[i] = 0;
		}
	}
	m_nMailboxesSize = nSize;

}

void VSSCMailboxList :: _CopyAllMailboxes(const VSSCMailboxList& vsscMBLsit)
{
	int nMailboxes = vsscMBLsit.m_nMailboxes;

    for (int i=0; i < nMailboxes; ++i) {
        VSSCMailBox* mailbox = (VSSCMailBox*) vsscMBLsit.m_Mailboxes[i]->Clone();
        // If we're out of memory, and no exception is thrown, just
        // recover by returning.
        if (mailbox == 0) {
            break;
        }
        _AddMailbox(mailbox);
    }

}

void VSSCMailboxList :: _AddMailbox(VSSCMailBox *vsscMB)
{
	  int nIndex = m_nMailboxes;
    _InsertMailbox(nIndex,vsscMB);

}

void VSSCMailboxList :: _InsertMailbox(int nIndex, VSSCMailBox* mbBox)
{
	if (m_nMailboxes == m_nMailboxesSize)
	{
        int newMailboxesSize = 2 * m_nMailboxesSize;
        if (newMailboxesSize == 0)
		{
            newMailboxesSize = 10;
        }

        VSSCMailBox** newMailboxes = new VSSCMailBox* [newMailboxesSize];
        if (newMailboxes == 0)
		{
            return;
        }

        int i;
        for (i=0; i < m_nMailboxes; ++i) 
		{
            newMailboxes[i] = m_Mailboxes[i];
            m_Mailboxes[i] = 0;
        }
        for ( ; i < newMailboxesSize; ++i) 
		{
		    newMailboxes[i] = 0;
        }

        delete [] m_Mailboxes;
        m_Mailboxes = newMailboxes;
        m_nMailboxesSize = newMailboxesSize;
    }

    // Make room in the array, then assign the mailbox

    for (int i= m_nMailboxes; i > nIndex; --i) 
	{
        m_Mailboxes[i] = m_Mailboxes[i-1];
    }

    m_Mailboxes[nIndex] = mbBox;
    ++m_nMailboxes;
    mbBox->SetParent(this);
	
}


VSSCMailboxList* VSSCMailboxList :: NewMailboxList(const VSSCString& vsscString,
        VSSCMsgComponent* Parent)
{
	return new VSSCMailboxList(vsscString, Parent);
}




VSSCMailboxListParser :: VSSCMailboxListParser(const VSSCString& vsscString)
:m_Tokenizer(vsscString),
 m_gtTokensString(vsscString)
{
	m_nPos = eError;
	ParseNextMailbox();
}

VSSCMailboxListParser :: ~VSSCMailboxListParser()
{
}

const VSSCString& VSSCMailboxListParser :: GetMboxString()
{
	return m_gtTokensString.GetTokens();
}


int VSSCMailboxListParser :: MboxPos()
{
	return m_nPos;
}

_BOOL VSSCMailboxListParser :: IsNull()
{
	_BOOL bRet = (m_nPos == eNull) ? _TRUE : _FALSE;
	return bRet;
}

_BOOL VSSCMailboxListParser :: IsEnd()
{
	_BOOL bRet = (m_nPos == eEnd) ? _TRUE : _FALSE;
	return bRet;
}


int VSSCMailboxListParser :: Restart()
{
	m_Tokenizer.Restart();
    ParseNextMailbox();
    return m_nPos;

}

int VSSCMailboxListParser :: operator ++ ()
{
	ParseNextMailbox();
    return m_nPos;
}


void VSSCMailboxListParser :: ParseNextMailbox()
{
	m_gtTokensString.SetFirstToken(m_Tokenizer);
	m_nPos = eEnd;

	int nType = m_Tokenizer.GetType();

	if(nType == eTkNull)
		return;

	m_nPos = eMailbox;
	while(1)
	{
		if(nType == eTkNull)
		{
			m_gtTokensString.ExtendTo(m_Tokenizer);
			break;
		}
		int ch;
		ch = m_Tokenizer.GetToken()[0];
		if(ch == ',' || ch == ';')
		{
			m_gtTokensString.ExtendTo(m_Tokenizer);
			++m_Tokenizer;
			nType = m_Tokenizer.GetType();
			break;

		}
		++m_Tokenizer;
		nType = m_Tokenizer.GetType();

	}

	if (m_gtTokensString.GetTokens().Length() == 0) 
	{
        m_nPos = eNull;
    }
}
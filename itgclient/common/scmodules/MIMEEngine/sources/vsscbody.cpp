#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "vsscbody.h"
#include "vsscenum.h"


// Constructors
VSSCBody :: VSSCBody()
{
	_Initialize();
}

VSSCBody :: VSSCBody(const VSSCBody& Body)
:VSSCMsgComponent(Body)
{
	_Initialize();
	_CopyAllBodyParts(Body);
}

VSSCBody :: VSSCBody(const VSSCString& vsscString, VSSCMsgComponent* Parent)
: VSSCMsgComponent(vsscString, Parent)
{
	_Initialize();
}

VSSCBody :: ~VSSCBody()
{
	_DeleteAllBodyParts();
	if(m_BodyParts != 0)
	{
		delete m_BodyParts;
		m_BodyParts = 0;
	}	

}

void VSSCBody :: AddBodyPart(VSSCBodyPart* BodyPart)
{
	_AddBodyPart(BodyPart);
}

void VSSCBody :: DeleteAllBodyParts()
{
	_DeleteAllBodyParts();
}

VSSCBodyPart& VSSCBody :: GetBodyPart(int nIndex) const
{
	if(nIndex <= 0 && nIndex > m_nBodyParts)
	{
		abort();
	}
	return *m_BodyParts[nIndex];
}

const VSSCBody& VSSCBody :: operator = (const VSSCBody& Body)
{
	if(this != &Body)
	{
		_DeleteAllBodyParts();
		VSSCMsgComponent :: operator = (Body);
		_CopyAllBodyParts(Body);
		
	}
	return *this;

}


int VSSCBody :: GetNumofBodyParts() const
{
	return m_nBodyParts;
}

VSSCBody* VSSCBody :: NewBody(const VSSCString& vsscString,
		VSSCMsgComponent* Parent)
{
	return new VSSCBody(vsscString, Parent);
}

VSSCMsgComponent* VSSCBody :: Clone() const
{
	return new VSSCBody(*this);
}

void VSSCBody :: Parse()
{
	
    _DeleteAllBodyParts();
    

    // Only types "multipart" and "message" need to be parsed, and
    // we cannot determine the type if there is no header.

    if (m_Parent == 0) 
	{
        return;
    }

    // Get the content type from the headers

    VSSCEntity* entity = (VSSCEntity*) m_Parent;
    if (entity->GetHeaders().IsContentTypePresent())
	{
        const VSSCMediaType& contentType = entity->GetHeaders().GetContentType();
        int type = contentType.GetType();
        if (type == VSSCEnumMime::eTypeMultipart)
		{
            VSSCString boundaryStr = contentType.GetBoundary();
            // Now parse body into body parts
            VSSCBodyParser parser(m_vsscString, boundaryStr);
            
            BodypartList* partStr = parser.GetFirstBodypart();
            while (partStr != 0)
			{
                VSSCBodyPart* part =
                    VSSCBodyPart::NewBodyPart(partStr->m_vsscString, this);
                part->Parse();
                _InsertBodyPart(m_nBodyParts, part);
                partStr = partStr->m_next;
            }
        }
        
    }
}


void VSSCBody :: Assemble()
{
	// Assembly is required only for a multipart message.
	VSSCEntity *Entity = (VSSCEntity*)m_Parent;
	if(Entity != 0 && Entity->GetHeaders().IsContentTypePresent())
	{
		const VSSCMediaType& ContentType = Entity->GetHeaders().GetContentType();
		int nType = ContentType.GetType();
		if(nType == VSSCEnumMime :: eTypeMultipart)
		{
			VSSCString vsscBoundary = ContentType.GetBoundary();
			m_vsscString = "";
			for(int i = 0; i < m_nBodyParts; i ++)
			{
				VSSCBodyPart* BodyPart = m_BodyParts[i];
				BodyPart->Assemble();
				m_vsscString += EOL "--";
				m_vsscString += vsscBoundary;
				m_vsscString += EOL;
				m_vsscString += BodyPart->GetString();
				//m_vsscString += EOL;
			}
			m_vsscString += EOL;
			m_vsscString += EOL "--";
			m_vsscString += vsscBoundary;
			m_vsscString += "--";
			m_vsscString += EOL;
						
		}
		else
		{
			// do nothing.
		}
	}
}


void VSSCBody :: _CopyAllBodyParts(const VSSCBody& Body)
{
	int nBodyParts =  Body.m_nBodyParts;
	for(int i = 0; i < nBodyParts; i++)
	{
		VSSCBodyPart* BodyPart = (VSSCBodyPart*)Body.m_BodyParts[i]->Clone();
		if(BodyPart == 0)
		{
			break;
		}
		_AddBodyPart(BodyPart);
	}
}

void VSSCBody :: _AddBodyPart(VSSCBodyPart* BodyPart)
{
	int nIndex =  m_nBodyParts;
	_InsertBodyPart(nIndex, BodyPart);
}

void VSSCBody :: _DeleteAllBodyParts()
{
	while (m_nBodyParts > 0)
	{
        int i = m_nBodyParts - 1;
        if (m_BodyParts[i] != 0)
		{
            delete m_BodyParts[i];
            m_BodyParts[i] = 0;
        }
        --m_nBodyParts;
    }
}

void VSSCBody :: _InsertBodyPart(int nIndex, VSSCBodyPart* BodyPart)
{
	if(m_nBodyParts == m_nSizeofBodyParts)
	{
		// need to allocate more space to add the BodyPart
		int nNewBodyPartSize = 2 * m_nSizeofBodyParts;
		if(nNewBodyPartSize == 0)
		{
			nNewBodyPartSize = 10;
		}

		VSSCBodyPart **NewBodyParts = new VSSCBodyPart* [nNewBodyPartSize];
		if(NewBodyParts == 0)
		{
			return;
		}

		for(int i = 0; i < m_nBodyParts; i++)
		{
			NewBodyParts[i] = m_BodyParts[i];
			m_BodyParts[i] = 0;
		}

		for(; i < nNewBodyPartSize; i ++)
		{
			NewBodyParts[i] = 0;
		}
		delete [] m_BodyParts;
		m_BodyParts = NewBodyParts;
		m_nSizeofBodyParts =  nNewBodyPartSize;
		

	}

	for(int i = m_nBodyParts; i > nIndex; i--)
	{
		m_BodyParts[i] = m_BodyParts[i-1];
	}
	m_BodyParts[nIndex] = BodyPart;
	++m_nBodyParts;
	BodyPart->SetParent(this);
}


void VSSCBody :: _Initialize()
{
	m_ComponentType = eCtBody;
	m_nBodyParts = 0;
	m_nSizeofBodyParts = 0;
	int nSize = 10;
	m_BodyParts =  new VSSCBodyPart* [nSize];
	if(m_BodyParts != 0)
	{
		for(int i = 0; i < nSize; i++)
		{
			m_BodyParts[i] = 0;
		}
	}
	m_nSizeofBodyParts = nSize;
}


// Implementation of VSSCBodyParser

VSSCBodyParser :: VSSCBodyParser(const VSSCString& vsscString, const VSSCString& vsscBoundary)
:m_vsscString(vsscString), m_vsscBoundary(vsscBoundary)
{
	m_StartList = 0;
	Parse();
}

VSSCBodyParser :: ~VSSCBodyParser()
{
	DeleteBodyParts();
}

int VSSCBodyParser :: Parse()
{
	_DWORD dwPos = 0;
	_DWORD dwBoundaryStart;
	_DWORD dwBoundaryEnd;
	_BOOL bFinal;

	_DWORD dwStart;
	_DWORD dwLen;
	
	int nRet;

	nRet = FindBoundary(dwPos, &dwBoundaryStart, &dwBoundaryEnd, &bFinal);
	if(nRet == eParseFail)
	{
		m_StartList = 0;
		return eParseFail;
	}

	// Not interested in epilogue

	// Find the body parts now.
	dwPos = dwBoundaryEnd;
	while(1)
	{
		nRet = FindBoundary(dwPos, &dwBoundaryStart, &dwBoundaryEnd, &bFinal);
		if(nRet == eParseFail)
		{
			// Whoops! There is no final boundary! Let's just pretend there
            // was one, but report a failure nonetheless.
            dwStart = dwPos;
            dwLen = m_vsscString.Length() - dwPos;
            AddPart(dwStart, dwLen);
            return eParseFail;
		}
		dwStart = dwPos;
		dwLen =  dwBoundaryStart - dwPos;
		AddPart(dwStart, dwLen);
		dwPos = dwBoundaryEnd;
		if(bFinal == _TRUE)
			break;

	}

	// Not interested in epilogue

	return eParseSuccess;


}



int VSSCBodyParser :: FindBoundary(_DWORD dwStartPos, _DWORD* dwBoundaryStart, 
        _DWORD* dwBoundaryEnd, _BOOL* bFinal) const
{

	// Initially the dwStartPos  = 0 
	// For the successive calls, dwStartPos = dwBoundaryEnd


	// Assume the starting position is the beginning of a line
    const char* szBuf = m_vsscString.GetStartPos();
    _DWORD dwPos = dwStartPos;
    _DWORD dwEndPos = m_vsscString.Length();
    _DWORD dwBoundaryLen = m_vsscBoundary.Length();
    const char* szBoundary = m_vsscBoundary.GetStartPos();

	// Search for the first boundary.
    // The leading CR LF ('\n') is part of the boundary	, but if there is
    // no preamble, there may be no leading CR LF ('\n').
    // The case of no leading CR LF ('\n') is a special case that will occur
    // only when '-' is the first character of the body.

	if (dwPos + dwBoundaryLen + 1 < dwEndPos
        && szBuf[dwPos] == '-'
        && szBuf[dwPos + 1] == '-'
        && strncmp(&szBuf[dwPos + 2], szBoundary, dwBoundaryLen) == 0)
	{

        *dwBoundaryStart = dwPos;
        dwPos += dwBoundaryLen + 2;
        // Check for final boundary
        if (dwPos + 1 < dwEndPos
            && szBuf[dwPos] == '-'
            && szBuf[dwPos + 1] == '-')
		{

            dwPos += 2;
            *bFinal = _TRUE;
        }
        else
		{
            *bFinal = _FALSE;
        }
        // Advance position past end of line
        while (dwPos < dwEndPos)
		{
            if (szBuf[dwPos] == '\n')
			{
                ++dwPos;
                break;
            }
            ++dwPos;
        }
        *dwBoundaryEnd = dwPos;
		return eParseSuccess;
	}

	_BOOL bFound = _FALSE;
    while (dwPos + dwBoundaryLen + 2 < dwEndPos)
	{
        // Case of leading LF
        if (szBuf[dwPos] == '\n'
            && szBuf[dwPos + 1] == '-'
            && szBuf[dwPos + 2] == '-'
            && strncmp(&szBuf[dwPos + 3], szBoundary, dwBoundaryLen) == 0)
		{

            *dwBoundaryStart = dwPos;
            dwPos += dwBoundaryLen + 3;
            bFound = _TRUE;
        }
        // Case of leading CR LF
        else if (szBuf[dwPos]== '\r'
            && szBuf[dwPos + 1] == '\n'
            && szBuf[dwPos + 2] == '-'
            && dwPos + dwBoundaryLen + 3 < dwEndPos
            && szBuf[dwPos + 3] == '-'
            && strncmp(&szBuf[dwPos + 4], szBoundary, dwBoundaryLen) == 0)
		{

            *dwBoundaryStart = dwPos;
            dwPos += dwBoundaryLen + 4;
            bFound = _TRUE;
        }
        if (bFound)
		{
            // Check for final boundary
            if (dwPos + 1 < dwEndPos
                && szBuf[dwPos] == '-'
                && szBuf[dwPos + 1] == '-')
			{

                dwPos += 2;
                *bFinal = _TRUE;
            }
            else
			{
                *bFinal = _FALSE;
            }

            // Advance position past end of line
            while (dwPos < dwEndPos)
			{
                if (szBuf[dwPos] == '\n')
				{
                    ++dwPos;
                    break;
                }
                ++dwPos;
            }
            *dwBoundaryEnd = dwPos;
            return eParseSuccess;
        }
        ++dwPos;
    }
    // Exceptional case: no boundary found
    *dwBoundaryStart = *dwBoundaryEnd = m_vsscString.Length();
    *bFinal = _TRUE;
   	return eParseFail;

}


void VSSCBodyParser :: AddPart(_DWORD dwStart, _DWORD dwLen)
{
	BodypartList* toAdd = new BodypartList(m_vsscString.ParseString(dwStart, dwLen));
	if(toAdd != 0)
	{
		BodypartList* present = m_StartList;
		if(present == 0)
		{
			// Zero elements in the list;
			m_StartList =  toAdd; 
			return;
		}
		while(present->m_next != 0)
		{
			present = present->m_next;
		}
		present->m_next = toAdd;
	}
}

void VSSCBodyParser :: DeleteBodyParts()
{
	BodypartList* present = m_StartList;

	while(present != 0)
	{
		BodypartList* next = present->m_next;
		delete present;
		present = next;
	}
	m_StartList = 0;
}

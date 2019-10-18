// AttachInfo.h: interface for the CAttachInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ATTACHINFO_H__C8110D61_8608_11D5_A257_001083023D07__INCLUDED_)
#define AFX_ATTACHINFO_H__C8110D61_8608_11D5_A257_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAttachInfo  
{
public:
	CAttachInfo();
	virtual ~CAttachInfo();
public:
	_bstr_t     m_bstrPathName;
	_bstr_t     m_bstrFileName;
	DWORD       m_dwFileSize;


};

#endif // !defined(AFX_ATTACHINFO_H__C8110D61_8608_11D5_A257_001083023D07__INCLUDED_)

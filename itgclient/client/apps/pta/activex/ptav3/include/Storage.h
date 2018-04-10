// Storage.h: interface for the CStorage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORAGE_H__10F26074_E021_11D3_8168_0060B0F885E6__INCLUDED_)
#define AFX_STORAGE_H__10F26074_E021_11D3_8168_0060B0F885E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../ProtectedStorage/ProtectedStorage.h"
#include "comdef.h"

class CStorage  
{
public:
	CStorage();
	virtual ~CStorage();

private :
	CProtectedStorage* pProtectedStorage;
	_bstr_t bstrProfName;
	bool	boolIsRoaming;
	bool	boolSaveLocal;
	wchar** wcharReadOKDomains;
	wchar** wcharWriteOKDomains;
	int	nPasswordQuality;
	int	nPasswordTimeOut;
	int	nPasswordLength;
	int	nPasswordLockOutTries;
	int	nPasswordUnlockPeriod;

};

#endif // !defined(AFX_STORAGE_H__10F26074_E021_11D3_8168_0060B0F885E6__INCLUDED_)

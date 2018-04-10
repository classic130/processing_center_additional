// AppContext.h: interface for the CAppContext class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPCONTEXT_H__C8110D66_8608_11D5_A257_001083023D07__INCLUDED_)
#define AFX_APPCONTEXT_H__C8110D66_8608_11D5_A257_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAppContext  
{
public:
	CAppContext();
	virtual ~CAppContext();

	_bstr_t                     bstrHostName;
	_bstr_t                     bstrProtocolName;


};

#endif // !defined(AFX_APPCONTEXT_H__C8110D66_8608_11D5_A257_001083023D07__INCLUDED_)

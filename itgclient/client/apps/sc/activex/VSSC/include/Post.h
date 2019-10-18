// Post.h: interface for the CPost class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POST_H__C5E8B9E3_D217_11D4_A21E_001083023D07__INCLUDED_)
#define AFX_POST_H__C5E8B9E3_D217_11D4_A21E_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CPost  
{
public:
	CPost();
	virtual ~CPost();



	HRESULT URLDownloadToBuffer(
								_bstr_t i_bstrURL,
								_bstr_t i_bstrPostVars,
								BYTE**o_pbDownloadData,
								DWORD *dwDataLen
								);
	

	HRESULT ResolveName(
						_bstr_t i_bstrHostName,
						_bstr_t i_bstrUserInfo,
						PCERT_RESOLVE_INFO  pCertResolveInfo,
						PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
						int  nCertReqCertInfo,
						CListUserInfo  *pUserList);

private:

	HRESULT                     hr;
	CListUserInfo::iterator		it;
	CUserInfo					*pObj;
	int							m_nVersion;		  
	int							m_nOperation;		
	int							m_nReqCrit;		  

public:
	DWORD GetUniversalInt(CUniversalInteger *pcuiValue );
	HRESULT CreateCertResolveReq(
								_bstr_t i_bstrEMailAddr,
								PCERT_RESOLVE_INFO  pCertResolveInfo,
								PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
								int  nCertReqCertInfo,
								_bstr_t* o_pbstrEncodedCertReqInfo
								);

	HRESULT DecodeCertResolveReq(
								BYTE*o_pbDownloadData,
								DWORD dwDataLen,
								CListUserInfo  *pUserList
								);

	HRESULT AddCertificatesInGM(
							   CListUserInfo *i_pUserList,
							   CListUserInfo	*g_pCertInGM
							   );

	HRESULT FindCertificateByEmailAddr(
								_bstr_t ibstrUserInfo,
								_bstr_t* o_pbstrResolveUser,
								_bstr_t* o_pbstrUnResolveUser,
								CListUserInfo *o_pFoundUserList,
								CListUserInfo	*g_pCertInGM
								);

	HRESULT FindCertificateByIssuerDNSerialNum(
								PCERT_RESOLVE_INFO  i_pCertResolveInfo,
								PCERT_REQ_CRIT_INFO i_pCertReqCritInfo[],
								int  i_nCertReqCertInfo,
								PCERT_REQ_CRIT_INFO o_pCertReqCritInfo[],
								int  *o_nCertReqCertInfo,

								CListUserInfo *o_pFoundUserList,
								CListUserInfo	*g_pCertInGM
								);



	HRESULT AnalyzeResolutionBlob(
								  CERT_REQ_RESPONSE_INFO     *pstCertReqResponseInfo,	
								  BYTE *pbResolutionBlob,DWORD cbResolutionBlob,
								  BYTE *pbAddtionalInfo,DWORD cbAddtionalInfo,
								  CListUserInfo  *pUserList
								  );
	
	
	_bstr_t						m_bstrPostVar,m_bstrURLData;
	_bstr_t                     m_bstrResponse_ContentType,m_bstrContentType;
	
};

#endif // !defined(AFX_POST_H__C5E8B9E3_D217_11D4_A21E_001083023D07__INCLUDED_)

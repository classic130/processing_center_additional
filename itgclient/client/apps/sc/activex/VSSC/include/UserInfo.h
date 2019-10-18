// UserInfo.h: interface for the CUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERINFO_H__AC743293_4401_11D5_A24A_001083023D07__INCLUDED_)
#define AFX_USERINFO_H__AC743293_4401_11D5_A24A_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CUserInfo  
{
public:
	CUserInfo(CERT_REQ_RESPONSE_INFO  *pstCertReqResponseInfo);
	CUserInfo(CUserInfo&obj);
	CUserInfo();
	virtual ~CUserInfo();

	CUserInfo operator=(CUserInfo &varUserInfo);
	void     copyinfo(CUserInfo &varUserInfo);
	
	
	DWORD		GetStatus();

	VSSC_ENCODED_CERT  GetSignerCert();
	VSSC_ENCODED_CERT  GetEncryptionCert();  


	
public:
	void Init();
	HRESULT AddEncryptCert(BYTE * pbData,DWORD cbData);
	HRESULT AddSignerCert(BYTE *pbData,DWORD cbData);
	
				 
	long					m_lLastDownloadTime;

	BYTE    				*pbSignerEncodedCert;
	DWORD					cbSignerEncodedCert;

	BYTE    				*pbEncryptEncodedCert;
	DWORD					cbEncryptEncodedCert;

	DECCERT_INFO			DecCertInfo;
	CERT_REQ_RESPONSE_INFO  stCertReqResponseInfo;
	CERT_STATUS_INFO        stCertStatusInfo; 

};

#endif // !defined(AFX_USERINFO_H__AC743293_4401_11D5_A24A_001083023D07__INCLUDED_)

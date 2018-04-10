// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__38E424D9_700F_11D5_A251_001083023D07__INCLUDED_)
#define AFX_MSG_H__38E424D9_700F_11D5_A251_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsg  
{
public:
	CMsg();
	virtual ~CMsg();
public:
	HRESULT Clear();
	_bstr_t			m_bstrFrom;
	_bstr_t			m_bstrTo;
	_bstr_t			m_bstrCc;
	_bstr_t			m_bstrBcc;
	_bstr_t			m_bstrSubject;
	_bstr_t			m_bstrDate;
	_bstr_t			m_bstrBody;
	_bstr_t			m_bstrAttachFileNameList;

	_bstr_t			m_bstrSMIMEMsg;

	_bstr_t         m_SCType;

	_bstr_t         m_bstrSMIMECapabilities;
	_bstr_t         m_bstrCertResolutionURL;

	
	

	DWORD           m_dwUsePRC;
	
	
	BOOL            m_ReplyAddAttachment;
	BOOL            m_bUsePKCS7Cert;
	BOOL            m_bURLEncodeData;
	BOOL			m_bUseSimder;

	

	/////Sign related Flag
	BOOL            m_bAddSignerCert;
	BOOL            m_bAddSMIMECap;
	BOOL            m_bAddRFC822Header;
	BOOL            m_bAddMIMEHeader;
	BOOL            m_bOpaqueSign;

	//////Encryption Flag
	BOOL            m_AddSenderRecipientInfo;
	
	DWORD           m_dwCryptStatus;
	DWORD           m_dwResolutionOpr;


	DWORD			m_dwMsgType;
	DWORD           m_dwAllowDecryption;
	DWORD			m_dwSignedMsgType;
	int				m_iMsgObjID;
	int             m_nSignAlgId;
	int             m_nEncryptAlgId;
	int             m_nKeySize;
	int             m_nReqVersion;

	DWORD			m_dwMessageMode;
	

	
	
	FILEINFO		*m_FILEINFO_AttachFileInfoList;

	CListUserInfo   m_SignerCertList;
	CListUserInfo   m_EncryptCertList;

	CListUserInfo   m_PRCCertList;


	
};

#endif // !defined(AFX_MSG_H__38E424D9_700F_11D5_A251_001083023D07__INCLUDED_)

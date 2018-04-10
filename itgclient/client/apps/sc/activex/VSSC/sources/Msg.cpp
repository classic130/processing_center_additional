// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "vssc.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsg::CMsg()
{
	m_bstrFrom="";
	m_bstrTo="";;
	m_bstrCc="";
	m_bstrBcc="";
	m_bstrSubject="";
	m_bstrDate="";
	m_bstrBody="";
	m_bstrAttachFileNameList="";
	
	m_bstrSMIMEMsg="";



    
	m_bstrSMIMECapabilities="";
	m_ReplyAddAttachment=FALSE;

	

	/////Sign related Flag
	m_bAddSignerCert=TRUE;
    m_bAddSMIMECap=TRUE;	
	m_bAddRFC822Header=TRUE;
	m_bAddMIMEHeader=TRUE;
	m_bOpaqueSign=FALSE;
	m_bURLEncodeData=TRUE;

	/////default Hash AlgoID
	m_nSignAlgId=SCRIPT_HASH_SHA1;

	/////default Encrypt AlgoID and KeySize
	/////				SYM_RC2_CBC,16
	/////				SYM_3DES,	24
	m_nEncryptAlgId=SYM_RC2_CBC;
	m_nKeySize=16;
	m_nReqVersion=2;
	m_iMsgObjID=0;

	//////Encryption Flag
	m_AddSenderRecipientInfo=TRUE;

	/////UsePRC or NOT
	m_dwUsePRC=0;
	m_dwCryptStatus=0;
	m_bUsePKCS7Cert=FALSE;
    m_dwAllowDecryption=0;
	m_bUseSimder=TRUE;

	m_FILEINFO_AttachFileInfoList=NULL;



}

CMsg::~CMsg()
{
	Clear();
}

HRESULT CMsg::Clear()
{
	m_bstrFrom="";
	m_bstrTo="";;
	m_bstrCc="";
	m_bstrBcc="";
	m_bstrSubject="";
	m_bstrDate="";
	m_bstrBody="";
	m_bstrAttachFileNameList="";
	m_bstrSMIMEMsg="";
	

  
	m_bstrSMIMECapabilities="";

	/////Sign related Flag
	m_bAddSignerCert=TRUE;
	m_bAddSMIMECap=TRUE;		
	m_bAddRFC822Header=TRUE;
	m_bAddMIMEHeader=TRUE;
	m_bOpaqueSign=FALSE;
	m_bURLEncodeData=TRUE;

	/////default Algo
	m_nSignAlgId=SCRIPT_HASH_SHA1;

	/////default Encrypt AlgoID and KeySize
	/////				SYM_RC2_CBC,16
	/////				SYM_3DES,	24
	m_nEncryptAlgId=SYM_RC2_CBC;
	m_nKeySize=16;

	/////
	m_nReqVersion=2;

	//////Encryption Flag
	m_AddSenderRecipientInfo=TRUE;

	/////UsePRC or NOT
	m_dwUsePRC=0;
	m_dwCryptStatus=0;
	m_bUsePKCS7Cert=FALSE;
	m_bUseSimder=TRUE;
   

	/////Attachmentment info
	if(m_FILEINFO_AttachFileInfoList!=NULL)
	{
		freeFileInfo(m_FILEINFO_AttachFileInfoList);
		m_FILEINFO_AttachFileInfoList=NULL;
	}

    
	
	
	m_dwMsgType=0;
	m_dwSignedMsgType=0;
	m_dwAllowDecryption=0; //valid Certificates 
	
	/////Free the Signer Certlist
	FreeCertList(&m_SignerCertList);
		
	/////Free the Encryption Certlist
	FreeCertList(&m_EncryptCertList);

	/////Free the Signer Certlist
	FreeCertList(&m_PRCCertList);

	
	return S_OK;
}

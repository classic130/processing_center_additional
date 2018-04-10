// UserInfo.cpp: implementation of the CUserInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "vssc.h"
#include "UserInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUserInfo::CUserInfo()
{
	
	Init();
	
}


CUserInfo::CUserInfo(CUserInfo&obj)
{
	Init();
	copyinfo(obj);
}

CUserInfo CUserInfo::operator=( CUserInfo &varUserInfo)
{
	copyinfo(varUserInfo);	
	return *this;
}

void CUserInfo::copyinfo( CUserInfo &varUserInfo)
{
	m_lLastDownloadTime=varUserInfo.m_lLastDownloadTime;


	if(varUserInfo.cbSignerEncodedCert!=0 &&
						varUserInfo.pbSignerEncodedCert!=NULL)
	{
		pbSignerEncodedCert=(BYTE*)malloc(varUserInfo.cbSignerEncodedCert);
		memcpy(
				pbSignerEncodedCert,
				varUserInfo.pbSignerEncodedCert,
				varUserInfo.cbSignerEncodedCert
			  );

		cbSignerEncodedCert=varUserInfo.cbSignerEncodedCert;
	}

	if(varUserInfo.cbEncryptEncodedCert!=0 &&
					varUserInfo.pbEncryptEncodedCert!=NULL)
	{
		pbEncryptEncodedCert=(BYTE*)malloc(varUserInfo.cbEncryptEncodedCert);
		memcpy(
			   pbEncryptEncodedCert,
			   varUserInfo.pbEncryptEncodedCert,
				varUserInfo.cbEncryptEncodedCert
			  );

		cbEncryptEncodedCert=varUserInfo.cbEncryptEncodedCert;
	}
	
	DecCertInfo.bstrIssuerDN=varUserInfo.DecCertInfo.bstrIssuerDN;
	DecCertInfo.bstrSerNum=varUserInfo.DecCertInfo.bstrSerNum;
    DecCertInfo.bstrSubjectDN=varUserInfo.DecCertInfo.bstrSubjectDN;

	DecCertInfo.bstrSubjectDN_CN=varUserInfo.DecCertInfo.bstrSubjectDN_CN;
	DecCertInfo.bstrSubjectDN_E=varUserInfo.DecCertInfo.bstrSubjectDN_E;
	DecCertInfo.bstrSubjectDN_O=varUserInfo.DecCertInfo.bstrSubjectDN_O;
	DecCertInfo.bstrSubjectDN_OU=varUserInfo.DecCertInfo.bstrSubjectDN_OU;

	DecCertInfo.dateEffDate=varUserInfo.DecCertInfo.dateEffDate;
	DecCertInfo.dateExpDate=varUserInfo.DecCertInfo.dateExpDate;
	
	DecCertInfo.nKeySize=varUserInfo.DecCertInfo.nKeySize;
	DecCertInfo.nKeyUsage=varUserInfo.DecCertInfo.nKeyUsage;


	stCertReqResponseInfo.dwVersion=varUserInfo.stCertReqResponseInfo.dwVersion;
	stCertReqResponseInfo.dwOperation=varUserInfo.stCertReqResponseInfo.dwOperation;
	stCertReqResponseInfo.dwReqCrit=varUserInfo.stCertReqResponseInfo.dwReqCrit;
	stCertReqResponseInfo.bstrSCType=varUserInfo.stCertReqResponseInfo.bstrSCType;


	stCertReqResponseInfo.bstrEmailAddr=varUserInfo.stCertReqResponseInfo.bstrEmailAddr;
	stCertReqResponseInfo.bstrSeialNum=varUserInfo.stCertReqResponseInfo.bstrSeialNum;
	stCertReqResponseInfo.bstrIssuerDN=varUserInfo.stCertReqResponseInfo.bstrIssuerDN;
		
	stCertReqResponseInfo.dwStatus=varUserInfo.stCertReqResponseInfo.dwStatus;
	
	stCertStatusInfo.dwResolutionTypeBit=
		varUserInfo.stCertStatusInfo.dwResolutionTypeBit; 
	stCertStatusInfo.dwRevocationStatusBit=
		varUserInfo.stCertStatusInfo.dwRevocationStatusBit;
	stCertStatusInfo.dwRevocationSubTypeBit=
		varUserInfo.stCertStatusInfo.dwRevocationSubTypeBit;
	stCertStatusInfo.dwRevocationTypeBit=
		varUserInfo.stCertStatusInfo.dwRevocationTypeBit;
	stCertStatusInfo.dwRevocationStatus=
		varUserInfo.stCertStatusInfo.dwRevocationStatus;
	stCertStatusInfo.dwChainValidateTypeBit=
		varUserInfo.stCertStatusInfo.dwChainValidateTypeBit;
	stCertStatusInfo.dwChainValidateStatusBit=
		varUserInfo.stCertStatusInfo.dwChainValidateStatusBit;
	stCertStatusInfo.dwChainValidationStatus=
		varUserInfo.stCertStatusInfo.dwChainValidationStatus;

	stCertStatusInfo.bIsExpired=
		varUserInfo.stCertStatusInfo.bIsExpired;

}

CUserInfo::~CUserInfo()
{
	FREE_MEMORY(pbEncryptEncodedCert)
	FREE_MEMORY(pbSignerEncodedCert)
	
}
CUserInfo::CUserInfo(CERT_REQ_RESPONSE_INFO  *pstCertReqResponseInfo)
{
	Init();


	if(pstCertReqResponseInfo!=NULL)
	{
		stCertReqResponseInfo.dwVersion=pstCertReqResponseInfo->dwVersion;
		stCertReqResponseInfo.dwOperation=pstCertReqResponseInfo->dwOperation;
		stCertReqResponseInfo.dwReqCrit=pstCertReqResponseInfo->dwReqCrit;
		stCertReqResponseInfo.dwStatus=pstCertReqResponseInfo->dwStatus;


		stCertReqResponseInfo.bstrEmailAddr=pstCertReqResponseInfo->bstrEmailAddr;
		stCertReqResponseInfo.bstrSCType=pstCertReqResponseInfo->bstrSCType;

		stCertReqResponseInfo.bstrSeialNum=pstCertReqResponseInfo->bstrSeialNum;
		stCertReqResponseInfo.bstrIssuerDN=pstCertReqResponseInfo->bstrIssuerDN;


	}
		

}


DWORD CUserInfo:: GetStatus()
{
	return stCertReqResponseInfo.dwStatus;
}

VSSC_ENCODED_CERT CUserInfo:: GetSignerCert()
{
	
	VSSC_ENCODED_CERT  SignerCert;
	SignerCert.pbData=pbSignerEncodedCert;
	SignerCert.cbData=cbSignerEncodedCert;

	return SignerCert;
}

VSSC_ENCODED_CERT CUserInfo:: GetEncryptionCert()
{

	VSSC_ENCODED_CERT  EncryptCert;
	EncryptCert.pbData=pbEncryptEncodedCert;
	EncryptCert.cbData=cbEncryptEncodedCert;
	return EncryptCert;
}

HRESULT CUserInfo::AddSignerCert(BYTE *pbData, DWORD cbData)
{
	if(pbData!=NULL)
	{
		pbSignerEncodedCert=(BYTE*)malloc(cbData);
		memcpy(pbSignerEncodedCert,pbData,cbData);
		cbSignerEncodedCert=cbData;
		pbEncryptEncodedCert=NULL;
	}
	else
	{
		pbSignerEncodedCert=NULL;
		cbSignerEncodedCert=0;
	}

	return S_OK;

}

HRESULT CUserInfo::AddEncryptCert(BYTE *pbData, DWORD cbData)
{
	if(pbData!=NULL)
	{
		pbEncryptEncodedCert=(BYTE*)malloc(cbData);
		memcpy(pbEncryptEncodedCert,pbData,cbData);
		cbEncryptEncodedCert=cbData;
		pbSignerEncodedCert=NULL;
	}
	else
	{
		pbEncryptEncodedCert=NULL;
		cbEncryptEncodedCert=0;
	}

	return S_OK;

}

void CUserInfo::Init()
{
	_bstr_t   bstrInit(_T(""));

	pbSignerEncodedCert=NULL;
	cbSignerEncodedCert=0;
	pbEncryptEncodedCert=NULL;
	cbEncryptEncodedCert=0;
	m_lLastDownloadTime=0;
	stCertStatusInfo.bIsExpired=FALSE;

	memset(&stCertReqResponseInfo,0,sizeof(CERT_REQ_RESPONSE_INFO));
	memset(&DecCertInfo,0,sizeof(DECCERT_INFO));
	memset(&stCertStatusInfo,0,sizeof(CERT_STATUS_INFO));

	stCertReqResponseInfo.bstrEmailAddr=bstrInit;
	stCertReqResponseInfo.bstrIssuerDN=bstrInit;
	stCertReqResponseInfo.bstrSCType=bstrInit;
	stCertReqResponseInfo.bstrSeialNum=bstrInit;
	
	DecCertInfo.bstrIssuerDN=bstrInit;
	DecCertInfo.bstrSerNum=bstrInit;
	DecCertInfo.bstrSubjectDN=bstrInit;
	DecCertInfo.bstrSubjectDN_CN=bstrInit;
	DecCertInfo.bstrSubjectDN_E=bstrInit;
	DecCertInfo.bstrSubjectDN_O=bstrInit;
	DecCertInfo.bstrSubjectDN_OU=bstrInit;


}

/////////////////VSSC_SMIME.CPP//////////////////////////////
#include "stdafx.h"
#include "vssc_smime.h"

#define     ENC_BLOCK_SIZE       8
extern		DWORD				 g_dwAppErr;

CListUserInfo::iterator it;
CUserInfo * pObj;


HRESULT  CreatePKCS7(VSSC_SIGN_MESSAGE_PARA *pvsscSignMsgPara,char **pszSignedData64)

{
	char				szObjId[512];

	HRESULT				hr=S_OK;
	int                 nRetVal=0;
	VS_SIGNER_INFO		SignerInfo; 
	VS_SIGNATURE_BLOB	signature_blob;
	
	do
	{
	

			////Add the Signature Blob Information
			signature_blob.cbData = pvsscSignMsgPara->cbSignature;
			signature_blob.pbData = pvsscSignMsgPara->pbSignature;
			
			SignerInfo.Issuer.cbData = pvsscSignMsgPara->pSignerCert->Issuer.cbData;
			SignerInfo.Issuer.pbData = pvsscSignMsgPara->pSignerCert->Issuer.pbData;

			


			SignerInfo.SerialNumber.cbData = pvsscSignMsgPara->pSignerCert->SerialNumber.cbData;
			SignerInfo.SerialNumber.pbData = pvsscSignMsgPara->pSignerCert->SerialNumber.pbData;

			if(pvsscSignMsgPara->bAddSignerCert)
			{
				SignerInfo.CertEncoded.cbData = pvsscSignMsgPara->cbEncodedCert;
				SignerInfo.CertEncoded.pbData = pvsscSignMsgPara->pbEncodedCert;
			}
			else
			{
				SignerInfo.CertEncoded.cbData=0;
				SignerInfo.CertEncoded.pbData=NULL;
			}

			
			strcpy(szObjId, szOID_RSA_RSA);
			SignerInfo.EncObjId.pszObjId = szObjId;

			
			
			SignerInfo.EncObjId.Parameters.cbData = 0;
			SignerInfo.EncObjId.Parameters.pbData = NULL;

			
			if(!pvsscSignMsgPara->bAttachSign)
			{
						nRetVal=CreateSignedData(&signature_blob,
										 pvsscSignMsgPara->i_nHashAlgType,
			  							 &SignerInfo, // Note this has to be changed to use simder
										 TRUE,
										 NULL,
										 0,
										 pvsscSignMsgPara->pbAuthAttr,
										 pvsscSignMsgPara->cbAuthAttr,
										 pszSignedData64
										 );

						if(nRetVal!=0)
						{
							hr=E_FAIL;
							break;
						}

			}
			else
			{

					nRetVal=CreateSignedData(&signature_blob,
										 pvsscSignMsgPara->i_nHashAlgType,
			  							 &SignerInfo, // Note this has to be changed to use simder
										 FALSE,
										 (BYTE *)pvsscSignMsgPara->szMIMEMsg,
										 pvsscSignMsgPara->cbMIMELen,
										 pvsscSignMsgPara->pbAuthAttr,
										 pvsscSignMsgPara->cbAuthAttr,
										 pszSignedData64
										 );

					if(nRetVal!=0)
					{
							hr=E_FAIL;
							break;
					}

			}

	}
	while(0);



	////////////////////////////////////
	
	return hr;


}

HRESULT MsgHashToBeSigned(VSSC_HASH_MESSAGE_PARA   *pMsgHashParam,
						  AUTHATTRIB *paaAuthAttrib,BYTE **pbHashData,DWORD *dwHashLen)
{

	HRESULT hr=S_OK;

	BYTE   *pbMIMEHash=NULL;
	DWORD  dwMIMEHashLen=0;

	do
	{

		/////Create Hash of MIME Entity/////////////////
	
		hr=VSSC_HashData(pMsgHashParam->i_nHashAlg,(unsigned char*)pMsgHashParam->szMIMEMsg, 
					pMsgHashParam->dwMIMESize,&pbMIMEHash,	&dwMIMEHashLen);
		CHECK_HRESULT_BREAK

		
		//paaAuthAttrib->szSMIMECapabilities =(TCHAR*)pMsgHashParam->bstrSMIMECap;

		VS_ALGORITHM_IDENTIFIER SMIMECap[3];
		memset(SMIMECap, 0, sizeof(VS_ALGORITHM_IDENTIFIER) * 3);

		/////fix
		SMIMECap[0].pszObjId = vssc_szOID_RSA_RC2CBC;
		unsigned int cbLen = 128;
		SMIMECap[0].Parameters.pbData = (unsigned char*)malloc(sizeof(unsigned int));
		memcpy(SMIMECap[0].Parameters.pbData, &cbLen, sizeof(unsigned int));
		SMIMECap[0].Parameters.cbData = 4;

		SMIMECap[1].pszObjId = vssc_szOID_OIWSEC_sha1;
		SMIMECap[2].pszObjId = vssc_szOID_RSA_MD5;
		
		paaAuthAttrib->SMIMECapabilities = SMIMECap;
		paaAuthAttrib->nCaps = 3;

	

		paaAuthAttrib->cbCertIssuerDN = pMsgHashParam->pSignerCert->Issuer.cbData;
		paaAuthAttrib->pbCertIssuerDN = pMsgHashParam->pSignerCert->Issuer.pbData;
		paaAuthAttrib->cbCertSerialNum =pMsgHashParam->pSignerCert->SerialNumber.cbData;
		paaAuthAttrib->pbCertSerialNum =pMsgHashParam->pSignerCert->SerialNumber.pbData;

		paaAuthAttrib->szDigestAlgoID = (TCHAR*)pMsgHashParam->bstrDigestAlgoID;

		
		
		paaAuthAttrib->cbMimeEntityDigest=dwMIMEHashLen;
		paaAuthAttrib->pbMimeEntityDigest=pbMIMEHash;
		

		if ( CreateAuthAttrib(paaAuthAttrib)!=0 )
		{
			hr=E_PKCS_AA_ERR;
			break;
		}

		CBaseDERCollection bdcAuthAttrib(paaAuthAttrib->cbAuthAttrib, paaAuthAttrib->pbAuthAttrib);
		CSet   cset(bdcAuthAttrib);


		/////Create Hash of AuthAuttrib with set/////////////////
		hr=VSSC_HashData(pMsgHashParam->i_nHashAlg,cset.BaseDERBlob->pbData, 
				cset.BaseDERBlob->cbData,pbHashData,dwHashLen);
		CHECK_HRESULT_BREAK
	}
	while(0);

	FREE_MEMORY(pbMIMEHash);


	return hr;
}

HRESULT ParsePKCS7(MSGINFO  MsgInfo, BOOL bUseSimder, VS_PKCS7_INFO *vsspiPKCS7Info)
{
	HRESULT hr=S_OK;

	int                 nRet=0;
	BYTE				*pbSignature = NULL;
	DWORD				cbSignature = 0;
	

	do
	{
			_Base64Decode(MsgInfo.szPKCS7,strlen(MsgInfo.szPKCS7),NULL,&cbSignature) ;
			if(!cbSignature)
			{
				hr=E_BASE64_DECODE_FAILED;
				break;
			}

				
			pbSignature = (PBYTE) malloc(cbSignature); 
			CHECK_MEM_BREAK(pbSignature)

			_Base64Decode(MsgInfo.szPKCS7,strlen(MsgInfo.szPKCS7),(char *)pbSignature,&cbSignature) ;
			if (!pbSignature)
			{
				hr=E_BASE64_DECODE_FAILED;
				break;
			}

			
		
			if(bUseSimder)
			{
				nRet=ParsePKCS7Data(pbSignature, cbSignature,vsspiPKCS7Info);
				if(nRet==-1)
				{
					hr=E_PARSEPKCS7_FAILED;
					break;
				}
			}
			else
			{
				nRet=ParsePKCS7DataUsingCAPI(pbSignature, cbSignature,vsspiPKCS7Info);
				if(nRet==-1)
				{
					hr=E_PARSEPKCS7_FAILED;
					break;
				}

			}
			
			
	}
	while(0);

	FREE_MEMORY(pbSignature);


	return hr;
}

HRESULT   VSSC_VerifyMessageSignature(MSGINFO MsgInfo,
									  CMsg *pCMsg,
									  VS_PKCS7_INFO *vsspiPKCS7InfoS
									  )
{
	int					iRet=0,nCerts=0;
	char				szAlgID[512];
	int					i_AlgID=0,nRetVal=0; 
	BOOL                bRet;
	
	BYTE				*pbMsgDigest = NULL;

	
	CERT_REQ_CRIT_INFO    *CertReqCritInfo=NULL;

	BOOL                bCertExpired=FALSE;

	BYTE				*pbEndUserCert=NULL,*pbHash = NULL,*pbMsgHash=NULL;
	BYTE				*pAuthAuttribHash=NULL;
	DWORD				cbEndUserCert=0,dwHash = 0;
	DWORD				dwAuthAuttribHashLen=0,dwMsgHash=0;
	
	PCERT_INFO			pSignerCertInfo=NULL,pCertInfo=NULL;
	PCERT_INFO			pResolveSignerInfo=NULL;    
	VSSC_ENCODED_CERT	EncodedCert;
	DECCERT_INFO		DecCertInfo;

	PCERT_REQ_CRIT_INFO *pCertReqCritInfo=NULL;
	AUTHATTRIB			aaAuthAttrib ;

	_bstr_t             bstrAAIssuerDN="",bstrAASerNum="";
	_bstr_t				bstrSignerIssuerDN="",bstrResolveIssuerDN = "";
	_bstr_t				bstrSignerSerialNum="",bstrResolveSerialNum = "";
	
	HRESULT				hr=S_OK;
	
	do
	{
		memset(&aaAuthAttrib,0,sizeof(AUTHATTRIB));

		/////Get the Hash Alg from PKCS7
		lstrcpy(szAlgID,vssc_szOID_OIWSEC_sha1);
		if(lstrcmp(szAlgID,vsspiPKCS7InfoS->SignedDataInfo.DigestAlgId.pszObjId)==0)
			i_AlgID=HASH_SHA1;
		else
		{
			lstrcpy(szAlgID,vssc_szOID_RSA_MD5);
			if(lstrcmp(szAlgID,vsspiPKCS7InfoS->SignedDataInfo.DigestAlgId.pszObjId)==0)
						i_AlgID=HASH_MD5;
			else
			{
				lstrcpy(szAlgID,vssc_szOID_RSA_MD2);
				if(lstrcmp(szAlgID,vsspiPKCS7InfoS->SignedDataInfo.DigestAlgId.pszObjId)==0)
							i_AlgID=HASH_MD2;
			}
			
		}
				
		if(i_AlgID==0)
		{
			hr=E_NO_HASH_ALGID;
			g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
			break;
		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "AuthAttrib-Begin",
												(LPCTSTR) "VSSC", MB_OK );
		#endif


		/////Auth Attributes is present in pkcs7 or not
		if(
			vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.pbData!=NULL &&
			vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.cbData!=0
		  )
		{
			
					
			nRetVal=GetMsgDigestSIDFromAA
						(
						vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.pbData,
						vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.cbData,
						&aaAuthAttrib
						);

			if(nRetVal==-1)
			{
				hr=E_AUTH_MSG_DIGEST_FAILED;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}

			/*Get the cert issuer dn*/
			CERT_NAME_BLOB    nbIssuerDN;
			nbIssuerDN.pbData=aaAuthAttrib.pbCertIssuerDN;
			nbIssuerDN.cbData=aaAuthAttrib.cbCertIssuerDN;

			hr = _GetNameFromBlob(nbIssuerDN,&bstrAAIssuerDN);
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
		
			CRYPT_INTEGER_BLOB   ibSerialNumber;
			ibSerialNumber.pbData=aaAuthAttrib.pbCertSerialNum;
			ibSerialNumber.cbData=aaAuthAttrib.cbCertSerialNum;

			hr = _GetCertSerNum(ibSerialNumber,&bstrAASerNum);
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
					
			
		}
			
		/////Signer Certificate is present or not in PKCS7 	
		if(pCMsg->m_bUsePKCS7Cert)
		{
			if(vsspiPKCS7InfoS->SignedDataInfo.CertificateSet.cbData==0 &&
					vsspiPKCS7InfoS->SignedDataInfo.CertificateSet.pbData==NULL)
			{
				hr=E_CERTNOTFOUND;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
			   		// must be  signed data.
			if(vsspiPKCS7InfoS->ePKCS7Type != PKCS7_SIGNED)
			{
				hr=E_UNKNOWN_PKCS7_TYPE;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}

			//////Number of cert 
			nCerts = GetCertChainLen(
									vsspiPKCS7InfoS->SignedDataInfo.CertificateSet.pbData,
									vsspiPKCS7InfoS->SignedDataInfo.CertificateSet.cbData
									); 
			
			iRet = CertChainParser(
								  vsspiPKCS7InfoS->SignedDataInfo.CertificateSet.pbData,
								  vsspiPKCS7InfoS->SignedDataInfo.CertificateSet.cbData,
								  &pbEndUserCert,
								  &cbEndUserCert,
								  0
								  );
			if(iRet!=0)
			{
				hr=E_CERT_PARSEING_FAILED;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}

			if(pbEndUserCert==NULL && cbEndUserCert==0)
			{
				hr=E_CERTNOTFOUND;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;

			}

			/////Signer Certificates from SignerInfo
			CCertInfo   SignerCertInfo(pbEndUserCert,cbEndUserCert);
			pSignerCertInfo=SignerCertInfo.GetCertInfo();
			if(pSignerCertInfo==NULL)
			{
				hr=E_CERTNOTFOUND;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
			
			hr=_DecodeCertInfo(pSignerCertInfo,&DecCertInfo);
			CHECK_HRESULT_BREAK

			SYSTEMTIME      stSysTime;
			DATE			dtDate;

			GetSystemTime(&stSysTime);
			if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
			{
				hr = E_SYSTIMETOVARTIMEFAILED;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;

			}
			
			if(!(DecCertInfo.dateEffDate<dtDate&&dtDate<DecCertInfo.dateExpDate))
			{
				bCertExpired=TRUE;
				g_dwAppErr=E_SIGNER_CERT_EXPIRED;
				
			}
			
		}
		else
		{
			////Signer Certificate from VS Dir
			int nCertReqCritInfo=1;		  //	
			CERT_RESOLVE_INFO   CertResolveInfo;

			pCMsg->m_dwResolutionOpr=0;
			
			CertResolveInfo.nVersion=pCMsg->m_nReqVersion;
			CertResolveInfo.nOperation=pCMsg->m_dwResolutionOpr; //0--UserCertificate 1->SMIMECertificate
			CertResolveInfo.ReqCrit=1;    //0-Email 1-> IssuerDn and Serial Number 
			CertResolveInfo.pszSCType=pCMsg->m_SCType;
				
			CertReqCritInfo=new CERT_REQ_CRIT_INFO[nCertReqCritInfo] ;

			CertReqCritInfo[0].IssuerDN.cbData=aaAuthAttrib.cbCertIssuerDN;
			CertReqCritInfo[0].IssuerDN.pbData=aaAuthAttrib.pbCertIssuerDN;

			CertReqCritInfo[0].SerialNum.cbData=aaAuthAttrib.cbCertSerialNum;
			CertReqCritInfo[0].SerialNum.pbData=aaAuthAttrib.pbCertSerialNum;

						
			pCertReqCritInfo=
				new PCERT_REQ_CRIT_INFO[nCertReqCritInfo];

			pCertReqCritInfo[0]=CertReqCritInfo;

			FreeCertList(&pCMsg->m_SignerCertList);

			
			
			hr=GetSignerCertificate(
									"",					//No email Address
									pCMsg->m_bstrCertResolutionURL,
									&CertResolveInfo,	//CertResolveInfo
									pCertReqCritInfo,	//REQ_CRIT_INFO
									nCertReqCritInfo,	//Num OF REQ_CRIT_INFO
									&pCMsg->m_SignerCertList
									);	
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
            
			it=pCMsg->m_SignerCertList.begin();
			pObj=(*it);

			/////Check for Status of certificate revoked display this information to user
			EncodedCert=pObj->GetSignerCert();
			if(EncodedCert.pbData==NULL && EncodedCert.cbData==0)
			{
				hr=E_CERTNOTFOUND;
				g_dwAppErr= E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
			
			if(pObj->stCertReqResponseInfo.dwStatus==0)
			{
				////Check the revokation status
				g_dwAppErr= E_SIGNER_CERT_REVOKED;
			}
		
			CCertInfo  ResolveSignerInfo(EncodedCert.pbData,EncodedCert.cbData);
			pResolveSignerInfo=ResolveSignerInfo.GetCertInfo();
			if(pResolveSignerInfo==NULL)
			{
				hr=E_CERTNOTFOUND;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;

			}
		
			hr=_DecodeCertInfo(pResolveSignerInfo,&DecCertInfo);
			CHECK_HRESULT_BREAK

			SYSTEMTIME      stSysTime;
			DATE			dtDate;

			GetSystemTime(&stSysTime);
			if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
			{
				hr = E_SYSTIMETOVARTIMEFAILED;
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
			}
			
			if(!(DecCertInfo.dateEffDate<dtDate &&dtDate <DecCertInfo.dateExpDate))
			{
				bCertExpired=TRUE;
				g_dwAppErr=E_SIGNER_CERT_EXPIRED;
			}
					
		}
										
		/////Opaque Signature
		if(vsspiPKCS7InfoS->SignedDataInfo.EncapContentInfo.cbData!=0)
		{
				MsgInfo.szMimeEntity=(char *)malloc(vsspiPKCS7InfoS->SignedDataInfo.EncapContentInfo.cbData+1);
				CHECK_MEM_BREAK(MsgInfo.szMimeEntity)
				
				memset(
					  MsgInfo.szMimeEntity,
					  0,
					  vsspiPKCS7InfoS->SignedDataInfo.EncapContentInfo.cbData+1
					  );
				memcpy(
					  MsgInfo.szMimeEntity,
					  vsspiPKCS7InfoS->SignedDataInfo.EncapContentInfo.pbData,
					  vsspiPKCS7InfoS->SignedDataInfo.EncapContentInfo.cbData
					  );
		
		}

		/////Verify the Hash which inside the AuthAttrib
		if(aaAuthAttrib.pbMimeEntityDigest!=NULL &&
						aaAuthAttrib.cbMimeEntityDigest!=0)
		{
			hr=VSSC_HashData(
							i_AlgID,
							(unsigned char*)MsgInfo.szMimeEntity, 
							strlen(MsgInfo.szMimeEntity),
							&pbMsgHash,&dwMsgHash
							);
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
				
			/////Compare the Hash
			if(memcmp(
					 pbMsgHash,
					 aaAuthAttrib.pbMimeEntityDigest,
					 aaAuthAttrib.cbMimeEntityDigest
					 ) != 0)
			{
				pCMsg->m_dwCryptStatus=E_HASHNOT_MATCHED;
				//break;
			}
		}

		
		/////Verifiy the signed Msg with/without Attachment 
		ENTITYINFO	   BodyInfo;	

		memset(&BodyInfo,0,sizeof(ENTITYINFO));

		bRet=ParseMimeEntity(
							(PBYTE)MsgInfo.szMimeEntity,
							strlen(MsgInfo.szMimeEntity),
							&BodyInfo,
							&pCMsg->m_FILEINFO_AttachFileInfoList
							);
		if(!bRet)
		{
			hr=E_PARSEMIME_FAILED;
			g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
			break;
		}

		BSTR   BSTRBody=_MultiToWideString((TCHAR*)BodyInfo.szBody);
		pCMsg->m_bstrBody=BSTRBody;
		SysFreeString(BSTRBody);
		FREE_MEMORY(BodyInfo.szBody)

		
		if(!pCMsg->m_bUsePKCS7Cert)
		     	pCertInfo=pResolveSignerInfo;
		else
				pCertInfo=pSignerCertInfo;

		
		hr = VSSC_DecryptSignature
			 (
				  i_AlgID,
				  pCertInfo,
				  vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignatureValue.pbData,
				  vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignatureValue.cbData,
				  &pbHash,
				  &dwHash
			 );
		
		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
			break;
		}
		
		/////Auth Attributes is present in pkcs7 or not
		if(vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.cbData!=0 &&
			vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.pbData!=NULL)
		{
			CBaseDERCollection bdcAuthAttrib(
							   vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.cbData,
							   vsspiPKCS7InfoS->SignedDataInfo.SignerInfo.SignedAttributes.pbData
							   );

			CSet   cset(bdcAuthAttrib);
		
			/////Create Hash of AuthAuttrib with set/////////////////
			hr=VSSC_HashData(
							i_AlgID,
							cset.BaseDERBlob->pbData, 
							cset.BaseDERBlob->cbData,
							&pAuthAuttribHash,
							&dwAuthAuttribHashLen
							);

			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
		
			
		}
		else
		{
			hr=VSSC_HashData(
							i_AlgID,
							(unsigned char*)MsgInfo.szMimeEntity, 
							strlen(MsgInfo.szMimeEntity),
							&pAuthAuttribHash,
							&dwAuthAuttribHashLen
							);
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
		
		
		}

		if(memcmp(pAuthAuttribHash, pbHash, dwAuthAuttribHashLen) != 0)
		{
			pCMsg->m_dwCryptStatus=E_HASHNOT_MATCHED;
					
		}
		
		
	}
	while(0);

	if(pResolveSignerInfo)
		freecertinfo(pResolveSignerInfo);
	if(pSignerCertInfo)
		freecertinfo(pSignerCertInfo);

	
	DELETE_MEMORY(pbHash)
	DELETE_MEMORY(pCertReqCritInfo)
	DELETE_MEMORY(CertReqCritInfo)

    FREE_MEMORY(pResolveSignerInfo)
	FREE_MEMORY(pSignerCertInfo)
	FREE_MEMORY(pbMsgDigest)
	FREE_MEMORY(pbMsgHash)
	FREE_MEMORY(pAuthAuttribHash)

	FREE_MEMORY(aaAuthAttrib.pbAuthAttrib)
	FREE_MEMORY(aaAuthAttrib.pbMimeEntityDigest)

	FREE_MEMORY(aaAuthAttrib.pbCertIssuerDN)
	FREE_MEMORY(aaAuthAttrib.pbCertSerialNum)

	return hr;

}


HRESULT VSSC_DecryptMessage(IVSPTA *pVSPTA,DWORD dwMsgType,
							CMsg *pCMsg,VS_PKCS7_INFO *vsspiPKCS7Info)
{
	int                 i_AlgID=0;
	////fix size
	char				szAlgID[512];
	BOOL				bRet;
	_bstr_t				bstrSelSubjectDN;
	
	DWORD				SelectedCert=0;
	DWORD				dwKeyLen=0,dwDecBlobLen=0;

	BYTE				*pbSessionKey=NULL,*pByteDecBlob=NULL;
	BYTE				*pbDecodedEncryptedContent=NULL;

	PCERT_INFO			pEncryptCertInfo=NULL;
	VSSC_ENCODED_CERT	EncodedCert;
	DECCERT_INFO		DecCertInfo;
	

	VARIANT				varEncSessionKey,varResult;
	VSSC_CERT_RDN_INFO	CertRDNInfo;

	PCERT_REQ_CRIT_INFO *pCertReqCritInfo=NULL;
	CERT_REQ_CRIT_INFO  *CertReqCritInfo=NULL;

	HRESULT				 hr=S_OK;	

	// declare these variables outside of loop, so they can be deallocated properly
	// when error occurs
	char	 *pDecBlob = NULL;

	MSGINFO  MsgInfo;
	memset(&MsgInfo, 0, sizeof(MSGINFO));

	VS_PKCS7_INFO vsspiPKCS7Info1;
	ZeroMemory(&vsspiPKCS7Info1,sizeof(VS_PKCS7_INFO));

	do
	{
		
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "SelectCert-Begin",
												(LPCTSTR) "VSSC", MB_OK );
		#endif

		/////////Use PTA to decrypt the Content//////////////////
		hr=SelectCertForDecryption(pVSPTA,vsspiPKCS7Info,&CertRDNInfo,&SelectedCert);
        if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TO_SELECT_CERT;
			break;
		}
		
        ///// 0-valid cert only 1-valid or expired only 2-valid or revoked
		if(pCMsg->m_dwAllowDecryption==0 ||pCMsg->m_dwAllowDecryption==1||
			pCMsg->m_dwAllowDecryption==2)
		{
			
			/////Get the certificate
			int nCertReqCritInfo=1;		  //	
			CERT_RESOLVE_INFO   CertResolveInfo;

			pCMsg->m_dwResolutionOpr=1;
			
			CertResolveInfo.nVersion=pCMsg->m_nReqVersion;
			CertResolveInfo.nOperation=pCMsg->m_dwResolutionOpr; //0--UserCertificate 1->SMIMECertificate
			CertResolveInfo.ReqCrit=1;    //0-Email 1-> IssuerDn and Serial Number 
			CertResolveInfo.pszSCType=pCMsg->m_SCType;
				
			CertReqCritInfo=new CERT_REQ_CRIT_INFO[nCertReqCritInfo] ;

			CertReqCritInfo[0].IssuerDN.cbData=
				  vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].Issuer.cbData;
			CertReqCritInfo[0].IssuerDN.pbData=
				  vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].Issuer.pbData;

			CertReqCritInfo[0].SerialNum.cbData=
  				  vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].SerialNumber.cbData;
			CertReqCritInfo[0].SerialNum.pbData=
				  vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].SerialNumber.pbData;
					
			pCertReqCritInfo=
				new PCERT_REQ_CRIT_INFO[nCertReqCritInfo];

			pCertReqCritInfo[0]=CertReqCritInfo;

			FreeCertList(&pCMsg->m_EncryptCertList);
					
			//-----------------------------------	
			hr=GetEncryptionCertificates(
				"",
				pCMsg->m_bstrCertResolutionURL,
				&CertResolveInfo,	//CertResolveInfo
				pCertReqCritInfo,	//REQ_CRIT_INFO
				nCertReqCritInfo,	//Num OF REQ_CRIT_INFO
				&pCMsg->m_EncryptCertList);
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
				break;
			}

			#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR)"Got Encryption Cert",
													(LPCTSTR) "VSSC", MB_OK );
			#endif

			it=pCMsg->m_EncryptCertList.begin();
			pObj=(*it);
					
			EncodedCert=pObj->GetEncryptionCert();
			if(EncodedCert.pbData==NULL && EncodedCert.cbData==0)
			{
				hr=E_ENCRYPT_CERTNOTFOUND;
				g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
				break;
			}
			
					
			CCertInfo  EncryptCertInfo(EncodedCert.pbData,EncodedCert.cbData);
			pEncryptCertInfo=EncryptCertInfo.GetCertInfo();
			if(pEncryptCertInfo==NULL)
			{
				hr=E_ENCRYPT_CERTNOTFOUND;
				g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
				break;
			}

			BOOL IsExpired=FALSE;
						
			hr=_DecodeCertInfo(pEncryptCertInfo,&DecCertInfo);
			CHECK_HRESULT_BREAK
			
			if(DecCertInfo.bstrIssuerDN!=CertRDNInfo.bstrIssuerDN &&
					DecCertInfo.bstrSerNum!=CertRDNInfo.bstrSerialNum)
			{
				////Fix
				g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
				break;
			}
			
			/////Check Certificate is expired or not
			SYSTEMTIME      stSysTime;
			DATE			dtDate;

			GetSystemTime(&stSysTime);
			if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
			{
				hr = E_SYSTIMETOVARTIMEFAILED;
				g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
				break;
			}
			
			if(!(DecCertInfo.dateEffDate<dtDate&&dtDate<DecCertInfo.dateExpDate))
			{
				IsExpired=TRUE;
			}
			else
			{
				IsExpired=FALSE;
			}

			/*
			00	Certificate not revoked
			01	Certificiate revoked
			11	Could not determine if certificate is revoked or not	
			*/


			switch(pCMsg->m_dwAllowDecryption)
			{
			case 0:  //Valid Cert only
				if(pObj->stCertStatusInfo.dwRevocationStatus!=0||IsExpired)
				{
					hr=E_DECRYPTION_NOT_ALLOWED;
					g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
						
		
				}

					
					break;
			case 1: // Valid + Expired cert
				if(pObj->stCertStatusInfo.dwRevocationStatus!=0)
				{
					hr=E_DECRYPTION_NOT_ALLOWED;
					g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
			
				}
				break;

            case 2: //valid or Revoked Cert
				if(IsExpired)
				{
					hr=E_DECRYPTION_NOT_ALLOWED;
					g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
			
				}
				break;

			}
			
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
				break;
			}
			
        }	
		
   		
		VariantInit(&varEncSessionKey);
		VariantInit(&varResult);

		varEncSessionKey.vt =	VT_ARRAY;
		varEncSessionKey.parray =	SafeArrayCreateVector(VT_UI1, 0,
			vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.cbData);
		CHECK_MEM_BREAK(varEncSessionKey.parray)
		
		/*
		reverse(
			vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.cbData,
			vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.pbData
			);
        */

		memcpy(
		(BYTE*)varEncSessionKey.parray->pvData,
		 vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.pbData, 
		 vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.cbData);


		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "DecryptSessionKey-Begin",
												(LPCTSTR) "VSSC", MB_OK );
		#endif


		/////decrypt the Session Key
		hr = pVSPTA->DecryptSessionKey(varEncSessionKey, &varResult);
		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
			break;
		}

		hr=SafeArrayAccessData(varResult.parray,(void HUGEP**)&pbSessionKey);
		if(hr==S_OK)
		{
			LONG lBound, uBound;
			SafeArrayGetLBound((SAFEARRAY FAR*)varResult.parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)varResult.parray, 1, &uBound);
			dwKeyLen = uBound - lBound + 1;
		}
		/////
		SafeArrayUnaccessData(varResult.parray);

		/////Get Encrypted AlgID from PKCS7
		lstrcpy(szAlgID,vssc_szOID_RSA_RC2CBC);
        if(lstrcmp(szAlgID,
		   vsspiPKCS7Info->EncryptedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId)
			==0)
					i_AlgID=SYM_RC2_CBC;
		else
		{

			lstrcpy(szAlgID,vssc_szOID_RSA_DES_EDE3_CBC);
			if(lstrcmp(szAlgID,
			vsspiPKCS7Info->EncryptedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId)
				==0)
					i_AlgID=SYM_3DES;
			
		}

		if(i_AlgID==0)
		{
			hr=E_NO_ENCRYPT_ALGID;
			g_dwAppErr=E_UNABLE_TO_SELECT_CERT;
			break;
		}


		////Get the encrypted content from PKCS7
		dwDecBlobLen=vsspiPKCS7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.cbData;
		if(dwDecBlobLen==0)
		{
			hr=E_INVALID_PKCS7;
			g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
			break;
		}
		pByteDecBlob=(BYTE *)malloc(dwDecBlobLen+1);
		CHECK_MEM_BREAK(pByteDecBlob)
		memset(pByteDecBlob,0,dwDecBlobLen+1);

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR)"SymDecryptData",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
	
		
		/////decrypt the data using session key
		hr=VSSC_SymDecryptData(i_AlgID,
		(BYTE*)pbSessionKey,dwKeyLen,
		 vsspiPKCS7Info->EncryptedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,
		 vsspiPKCS7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.pbData,
		 vsspiPKCS7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.cbData,
		 (BYTE *)pByteDecBlob,
		 &dwDecBlobLen
		 );

		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
			break;
		}
		
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR)"SymDecryptData-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
		
		
		int nMsgType=0;
		nMsgType=_GetMsgType(pByteDecBlob,dwDecBlobLen);

		#ifdef	_VSSC_MSG_BOX_
					::MessageBox ( NULL, (LPCTSTR)"GetMsgType",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
			
      
		if(nMsgType == VSSCEnumMime :: eTypeNull || nMsgType == VSSCEnumMime :: eTypeUnknown)
		{
			//return failure;
			hr=E_INVALID_MIME;
			g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
			break;
		}

		if(nMsgType==eOpaqueSigned ||nMsgType==eClearSigned 
			||nMsgType==eNoHeaders )
		{
			

				pDecBlob=(char*)malloc(dwDecBlobLen+1);
				CHECK_MEM_BREAK(pDecBlob)
				memcpy(pDecBlob,pByteDecBlob,dwDecBlobLen);
				pDecBlob[dwDecBlobLen]='\0';

				FREE_MEMORY(pByteDecBlob);


				if(nMsgType==eClearSigned)
				{


					#ifdef	_VSSC_MSG_BOX_
					::MessageBox ( NULL, (LPCTSTR)"ParseSignedMessageStr-Begin",
													(LPCTSTR) "VSSC", MB_OK );
					#endif
			
					dwMsgType=VSSC_MSG_SIGNED;
					bRet=ParseSignedMessageStr((TCHAR*)pDecBlob, &MsgInfo);
					if(!bRet)
					{
						hr=E_PARSE_SIGNEDMSG_FAILED;
						g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
						break;
					}

					#ifdef	_VSSC_MSG_BOX_
					::MessageBox ( NULL, (LPCTSTR)"ParseSignedMessageStr-End",
													(LPCTSTR) "VSSC", MB_OK );
					#endif
			

					
				}
            
				if(nMsgType==eOpaqueSigned)
				{
					dwMsgType=VSSC_MSG_OPAQUE_SIGN;
					bRet=ParseOpaqueSignedMessageStr((TCHAR*)pDecBlob, &MsgInfo);
					if(!bRet)
					{
						hr=E_PARSE_SIGNEDMSG_FAILED;
						g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
						break;
					}
				}
				if(nMsgType==eNoHeaders)
				{
					MsgInfo.szPKCS7=(char*)malloc(dwDecBlobLen+1);
					CHECK_MEM_BREAK(MsgInfo.szPKCS7)
					
					memcpy(MsgInfo.szPKCS7,pDecBlob,dwDecBlobLen);

				}

				FREE_MEMORY(pDecBlob)
				
				hr=ParsePKCS7(MsgInfo,pCMsg->m_bUseSimder,&vsspiPKCS7Info1);
				CHECK_HRESULT_BREAK
			
				if(vsspiPKCS7Info1.ePKCS7Type!=PKCS7_SIGNED)
				{
					hr=E_INVALID_PKCS7;
					g_dwAppErr=E_UNABLE_TODO_VERIFICATION_ERR;
					break;

				}

								 
				hr=VSSC_VerifyMessageSignature(MsgInfo,pCMsg,&vsspiPKCS7Info1);
				CHECK_HRESULT_BREAK
				
                pCMsg->m_dwMsgType=VSSC_MSG_SIGN_ENCRYPT;

				/////free Memory-free outside while loop
				freeMsgInfo(&MsgInfo);
				FreePKCS7Info(&vsspiPKCS7Info1);

		}
		else
		{
				ENTITYINFO			BodyInfo;

				memset(&BodyInfo,0,sizeof(ENTITYINFO));
				
			    bRet=ParseMimeEntity(pByteDecBlob, dwDecBlobLen,
					&BodyInfo, &pCMsg->m_FILEINFO_AttachFileInfoList);
				if(!bRet)
				{
					hr=E_PARSEMIME_FAILED;
					g_dwAppErr=E_UNABLE_TODO_DECRYPTION_ERR;
					break;
				}

				BSTR   BSTRBody=_MultiToWideString((TCHAR*)BodyInfo.szBody);
				pCMsg->m_bstrBody=BSTRBody;
				SysFreeString(BSTRBody);
				FREE_MEMORY(BodyInfo.szBody)


		}
	
	}
	while(0);

	VariantClear(&varEncSessionKey);
	VariantClear(&varResult);

	if(pEncryptCertInfo!=NULL)
			freecertinfo(pEncryptCertInfo);

	/////
	//freeMsgInfo(&MsgInfo);
	//FreePKCS7Info(&vsspiPKCS7Info);

	// free memory again just in case if there are any errors
	FREE_MEMORY(pDecBlob);
	freeMsgInfo(&MsgInfo);
	FreePKCS7Info(&vsspiPKCS7Info1);

	FREE_MEMORY(pbDecodedEncryptedContent);
	FREE_MEMORY(pByteDecBlob);
	FREE_MEMORY(pEncryptCertInfo);
 
	DELETE_MEMORY(CertReqCritInfo);
	DELETE_MEMORY(pCertReqCritInfo);

	return hr;
		
}

HRESULT VSSC_SymDecryptData(int i_AlgID,BYTE* i_pbyteKey, DWORD dwKeyLen,
				  BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize,
				  BYTE* o_pbyteDecBlob, DWORD* o_pdwDecBlobSize)
{
	HRESULT hResult = S_OK;
	void* pvoidCtxt = NULL;
	DWORD dwResidual = 0;
	ITEM itemKey;

	do
	{
		
		itemKey.len = dwKeyLen;
		itemKey.data=(unsigned char *)malloc(dwKeyLen);

		memset(itemKey.data , 0,dwKeyLen);
		memcpy(itemKey.data , i_pbyteKey,dwKeyLen);

		//////Tell Bsafelite to strip off padding
		if(SymDecryptDataBegin(i_AlgID,&itemKey,dwKeyLen*8,&pvoidCtxt,i_pbyteIV,1))
		{
			hResult = E_SYM_DECRYPT_BEGIN_FAILED;
			break;
		}

		if(SymDecryptDataUpdate(pvoidCtxt, i_pbyteEncBlob, i_dwEncBlobSize,
			o_pbyteDecBlob,(unsigned int*)o_pdwDecBlobSize))
		{
			hResult = E_SYM_DECRYPT_DATA_FAILED;
			break;
		}

		dwResidual = i_dwEncBlobSize - (*o_pdwDecBlobSize);
		if(SymDecryptDataEnd(pvoidCtxt,o_pbyteDecBlob+(*o_pdwDecBlobSize),
			(unsigned int*)&dwResidual))
		{
			
			hResult = E_SYM_DECRYPT_END_FAILED;
			break;
		}
		(*o_pdwDecBlobSize) += dwResidual;
		pvoidCtxt = NULL;

	}while(0);

	if(itemKey.data!=NULL)
			free(itemKey.data);

	return hResult;
}


HRESULT  VSSC_DecryptSignature(int i_nAlgID,PCERT_INFO   pSignerCertInfo, BYTE *pbSignature,
									   DWORD dwSignature, BYTE **pbHash, DWORD *dwHash)
{

	HRESULT				hr;
	A_RSA_KEY			RSA_Enc_PublicKey;
	void*				pContext;
	int                 nResult; 

	BYTE				*pbPaddedHash = NULL;
	DWORD				dwPaddedHash = 0;

	BYTE				*pbUnPaddedHash = NULL;
	DWORD				dwUnPaddedHash = 0;

	hr=GetRSAKeyFromKeyInfo(&pSignerCertInfo->SubjectPublicKeyInfo,&RSA_Enc_PublicKey);
	if(hr!=S_OK)
	{
		return hr;
	}

	nResult=RSADataBegin(&RSA_Enc_PublicKey,(void**) &pContext);
	if(nResult!=0)
	{
		hr=E_RSA_DATA_BEGIN_FAILED;
		return hr;
	}
	
	pbPaddedHash = (BYTE*)malloc(dwSignature);
	dwPaddedHash =  dwSignature;

	//noreverse
	//reverse(dwSignature, pbSignature);

	nResult= RSADataUpdate(pContext,pbSignature,dwSignature,pbPaddedHash, 
					(unsigned int*)&dwPaddedHash);
	if(nResult!=0)
	{
		hr=E_RSA_DATA_UPDATE_FAILED;
		return hr;
	}
	nResult =	RSADataEnd(pContext);
	if(nResult!=0)
	{
		hr=E_RSA_DATA_END_FAILED;
		return hr;
	}

	if(UnPadDataForVerify(pbPaddedHash,dwPaddedHash,&pbUnPaddedHash,&dwUnPaddedHash) != S_OK)
	{
		return E_FAIL;
	}

	nResult =	GetDataFromSequence(pbUnPaddedHash,dwUnPaddedHash,i_nAlgID,
						pbHash,dwHash);

	
	FREE_MEMORY(pbPaddedHash)

	DELETE_MEMORY(pbUnPaddedHash)
	DELETE_MEMORY(RSA_Enc_PublicKey.modulus.data)
	DELETE_MEMORY(RSA_Enc_PublicKey.exponent.data)

	return hr;
}



HRESULT VSSC_CreateSignedMessage(IVSPTA *pVSPTA,CMsg *pCMsg )
{

	BOOL						bFoundSigner=FALSE;
	char						*szSMIMEEntity = NULL,*pszPKCS7=NULL;
		
	BYTE						*pAuthAuttribHash=NULL,*pbSignature = NULL	;
	DWORD						dwAuthAuttribHashLen= 0,cbSignature = 0;	

	DATE						dtDate;
	SYSTEMTIME					stSysTime;
	VARIANT						varHashData, varAlg,varResult;

	PCERT_INFO					pSignerCertInfo=NULL;
	AUTHATTRIB					aaAuthAttrib ;
	VSSC_ENCODED_CERT			EncodedCert;
	VSSC_HASH_MESSAGE_PARA		MsgHashParam;
	VSSC_SIGN_MESSAGE_PARA		vsscSignMsgPara;

	VSSCMessage *Msg = NULL;

	

	HRESULT						hr=S_OK;
	ZeroMemory(&aaAuthAttrib,sizeof(AUTHATTRIB));


	do
	{
		
		/////Init Variant Structure
		VariantInit(&varHashData);
		VariantInit(&varAlg);
		VariantInit(&varResult);

		
		/////Select Signer Certificate
		for (it =  pCMsg->m_SignerCertList.begin(); 
						it != pCMsg->m_SignerCertList.end(); ++it)
		{
			pObj=(*it);
			if(pObj->stCertReqResponseInfo.bstrEmailAddr==pCMsg->m_bstrFrom)
			{
				bFoundSigner=TRUE;
				break;
			}
		
		}
		if(!bFoundSigner)
		{
			hr=E_SIGNER_CERTNOTFOUND;
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}

		/////Cert present or not
		EncodedCert=pObj->GetSignerCert();
		if(EncodedCert.pbData==NULL)
		{
			hr=E_SIGNER_CERTNOTFOUND;
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}
		CCertInfo  UserSignerInfo(EncodedCert.pbData,EncodedCert.cbData);
		pSignerCertInfo=UserSignerInfo.GetCertInfo();
		if(pSignerCertInfo==NULL)
		{
			hr=E_SIGNER_CERTNOTFOUND;
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}

		
		/////Check Revocation Status
		if(pObj->stCertStatusInfo.dwRevocationStatus==1)
		{
			hr=E_SIGNER_CERT_REVOKED;
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}

		/////Check Validating period
		GetSystemTime(&stSysTime);
		if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
		{
			hr = E_SYSTIMETOVARTIMEFAILED;
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}
		
		if(!(pObj->DecCertInfo.dateEffDate<dtDate&&
								dtDate<pObj->DecCertInfo.dateExpDate))
		{
		
			g_dwAppErr=E_SIGNER_CERT_EXPIRED;
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
			
		}

			
	
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "SelectCertForSigning-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif	

        /////Select certificate for Signing
		hr=SelectCertForSigning(
								pVSPTA,
								pObj->DecCertInfo.bstrIssuerDN,
								pObj->DecCertInfo.bstrSerNum
								);

		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "SelectCertForSigning-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif	
       
		/////MIME Entity to sign
		hr=FormatMIMEEntityForSigning(pCMsg,&szSMIMEEntity);
		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}
		
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreateSMIMEEntity-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif	

        /////Select Hashing Alg 
		varAlg.vt=VT_I2;
		switch(pCMsg->m_nSignAlgId)
		{
		case SCRIPT_HASH_MD2 :
			varAlg.iVal = SCRIPT_HASH_MD2;
			MsgHashParam.i_nHashAlg = HASH_MD2;
			vsscSignMsgPara.i_nHashAlgType=VSSC_HASH_MD2;
			
			break;
		case SCRIPT_HASH_MD5 :
			varAlg.iVal = SCRIPT_HASH_MD5;
			MsgHashParam.i_nHashAlg = HASH_MD5;
			vsscSignMsgPara.i_nHashAlgType=VSSC_HASH_MD5;
			
			break;
		case SCRIPT_HASH_SHA1 :
			varAlg.iVal = SCRIPT_HASH_SHA1;
			MsgHashParam.i_nHashAlg = HASH_SHA1;
			vsscSignMsgPara.i_nHashAlgType=VSSC_HASH_SHA1;
			break;
		default:
			hr = E_VSSC_INVALIDARGS;
			break;
		}
		
		
		MsgHashParam.szMIMEMsg=szSMIMEEntity;
		MsgHashParam.dwMIMESize=_tcslen(szSMIMEEntity)*sizeof(TCHAR);
		if(pCMsg->m_bAddSMIMECap)
			MsgHashParam.bstrSMIMECap=pCMsg->m_bstrSMIMECapabilities;
		else
			MsgHashParam.bstrSMIMECap="";

		//MsgHashParam.bstrDigestAlgoID=pCMsg->m_bstrDigestAlgoID;
		MsgHashParam.pSignerCert=pSignerCertInfo;

		
		
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "MsgHashToBeSigned-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif	
		hr=MsgHashToBeSigned(
							&MsgHashParam,
							&aaAuthAttrib,
							&pAuthAuttribHash,
							&dwAuthAuttribHashLen
							);

		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "MsgHashToBeSigned-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif	
		
		/////Use PTA to sign this Hash
		varHashData.vt =	VT_ARRAY |VT_UI1;
		varHashData.parray =	SafeArrayCreateVector(VT_UI1, 0, dwAuthAuttribHashLen);
		CHECK_MEM_BREAK(varHashData.parray )
		
		memcpy((BYTE*)varHashData.parray->pvData, pAuthAuttribHash, 
													dwAuthAuttribHashLen);
		
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "SignTransaction-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		hr = pVSPTA->SignTransaction (
									 &varHashData,
									 &varAlg, 
									 &varResult
									 );
		if(hr!=S_OK)
		{
			g_dwAppErr=E_UNABLE_TODO_SIGN_ERR;
			break;
		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "SignTransaction-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		
		_bstr_t   bstrEncodedSignHash(varResult.bstrVal);

				
		
		/////decode Signed hash///////////
		_Base64Decode(
					  bstrEncodedSignHash,
					  bstrEncodedSignHash.length(),
					  NULL,
					  &cbSignature
					  );

		
		
		pbSignature = (PBYTE) malloc(cbSignature);
		CHECK_MEM_BREAK(pbSignature)
		
		_Base64Decode(
					  bstrEncodedSignHash,
					  bstrEncodedSignHash.length(),
					  (char *)pbSignature,
					  &cbSignature
					  );

		
		/////create PKCS7
		vsscSignMsgPara.bAddSignerCert=pCMsg->m_bAddSignerCert;
		vsscSignMsgPara.bAttachSign=pCMsg->m_bOpaqueSign;

		vsscSignMsgPara.pbSignature=pbSignature;
		vsscSignMsgPara.cbSignature=cbSignature;
		
		vsscSignMsgPara.pbAuthAttr=aaAuthAttrib.pbAuthAttrib;
		vsscSignMsgPara.cbAuthAttr=aaAuthAttrib.cbAuthAttrib;
		
		vsscSignMsgPara.pbEncodedCert=EncodedCert.pbData;
		vsscSignMsgPara.cbEncodedCert=EncodedCert.cbData;
		vsscSignMsgPara.pSignerCert=pSignerCertInfo;
		vsscSignMsgPara.szMIMEMsg=szSMIMEEntity;
		vsscSignMsgPara.cbMIMELen=_tcslen(szSMIMEEntity)*sizeof(TCHAR);


		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreatePKCS7-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		hr=CreatePKCS7(&vsscSignMsgPara,&pszPKCS7);
		if(hr!=S_OK)
		{
			hr=E_CREATE_PKCS7_FAILED;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}

		if(pszPKCS7==NULL)
		{
			hr=E_CREATE_PKCS7_FAILED;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;

		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreatePKCS7-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
		
		////Start Building The SMIME Message
		Msg = VSSCMessage :: NewMessage("",0);

		////Add RFC Headers
		if(pCMsg->m_bAddRFC822Header)
		{
			if(pCMsg->m_dwMsgType!=VSSC_MSG_SIGN_ENCRYPT)
			{
				hr=AddRFC822Header(Msg,pCMsg);
				CHECK_HRESULT_BREAK
			}
		}

		VSSCHeaders& headers = Msg->GetHeaders();

		if(!pCMsg->m_bOpaqueSign)
		{

				/////Add MimeHeader
				headers.GetContentType().SetTypeString("Multipart");
				headers.GetContentType().SetSubTypeString("signed");
				headers.GetContentType().SetProtocol("application/pkcs7-signature");
				headers.GetContentType().SetMicalg("SHA1");/////set it from outside
				//headers.GetContentType().SetBoundary("--OutBoudaryAADFSDF");
				headers.GetContentType().CreateBoundary();

				// Create the first outer bodypart
				// This bodypart can be mulitpart.
				VSSCString vsscBodyPart;
				VSSCBodyPart *outerbodyPart1;

				VSSCString vsscEntityStr(szSMIMEEntity);
				outerbodyPart1 = VSSCBodyPart :: NewBodyPart(vsscEntityStr, 0);

				//New Change
				outerbodyPart1->SetAssembled();


				// Now the create the outer second bodypart
				VSSCBodyPart *outerbodyPart2;
				outerbodyPart2 = VSSCBodyPart :: NewBodyPart("", 0);


				////Second body part with base64 signature pkca7
				VSSCHeaders& headers3 = outerbodyPart2->GetHeaders();

				headers3.GetContentType().SetTypeString("application");
				headers3.GetContentType().SetSubTypeString("pkcs7-signature");
				headers3.GetContentType().SetName("smime.p7s");
				headers3.GetContentTransferEncoding().SetString("base64");
				headers3.GetContentDisposition().SetDispTypeString("attachment");
				headers3.GetContentDisposition().SetFileName("smime.p7s");

				//////PKCS7
				outerbodyPart2->GetBody().SetString(pszPKCS7);

				Msg->GetBody().AddBodyPart(outerbodyPart1);
				Msg->GetBody().AddBodyPart(outerbodyPart2);

				Msg->Assemble();
		}
		else
		{
				if(pCMsg->m_bAddMIMEHeader)
				{
					headers.GetContentType().SetTypeString("application");
					headers.GetContentType().SetSubTypeString("pkcs7-mime");
					headers.GetContentType().SetSMIMEType("signed-data");
					headers.GetContentType().SetName("smime.p7m");
					headers.GetContentTransferEncoding().SetString("base64");
					headers.GetContentDisposition().SetDispTypeString("attachment");
					headers.GetContentDisposition().SetFileName("smime.p7m");
				}

				Msg->GetBody().SetString(pszPKCS7);
				Msg->Assemble();

		}

		/////Del Memory
		DELETE_MEMORY(pszPKCS7);	
		FREE_MEMORY(szSMIMEEntity);
		
		VSSCString vsscString = Msg->GetString();
		
		BSTR   bstrSMIME=_MultiToWideString(vsscString.GetString());
		if(bstrSMIME==NULL)
		{
			hr=E_UNABLE_TO_CONSTRUCT_MSG;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;

		}
		pCMsg->m_bstrSMIMEMsg=bstrSMIME;
		SysFreeString(bstrSMIME);

		
		
  }
  while(0);

  VariantClear(&varHashData);
  VariantClear(&varAlg);
  VariantClear(&varResult);

  if(pSignerCertInfo)
	  freecertinfo(pSignerCertInfo);

  FREE_MEMORY(pSignerCertInfo);

  DELETE_MEMORY(Msg)
  DELETE_MEMORY(pszPKCS7)	
  
  FREE_MEMORY(szSMIMEEntity)
  FREE_MEMORY(pbSignature)
  FREE_MEMORY(aaAuthAttrib.pbAuthAttrib)
  FREE_MEMORY(pAuthAuttribHash)

  return hr;

}

HRESULT VSSC_CreateEncryptedMessage(CMsg *pCMsg)
{
	int					i=0,NumOfRecipientsEncCert=0,iRet=0;
	BOOL				bRet=FALSE;
	bool				bDropHeader=false;
	
	char				*szSMIMEEntity = NULL,*szEnvelopedMessage=NULL;
	char				*pszEnvelopedData64 = NULL;
	unsigned char		IV[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

	BYTE				*pbBuffer=NULL,*pbKeyBlob=NULL;
	DWORD				dwKeyBlobLen=0;	
	unsigned int		dwInput=0,dwLen=0;
	ITEM				i_pRCKey;

	PCERT_INFO			pCertInfo=NULL;
	PVS_RECIPIENT_INFO  *pRecipientInfo=NULL;
	VS_RECIPIENT_INFO	*RecipientInfo=NULL;
	VSSCMessage			*Msg=NULL;

	HRESULT  hr=S_OK;

	i_pRCKey.data=NULL;
	i_pRCKey.len=0;

	do
	{

		if(pCMsg->m_dwMsgType!=VSSC_MSG_SIGN_ENCRYPT)
		{
			ENTITYINFO     BodyInfo;
			memset(&BodyInfo,0,sizeof(ENTITYINFO));

			strcpy(BodyInfo.szType,"TEXT");
			strcpy(BodyInfo.szSubType,"Plain");
			strcpy(BodyInfo.szCte,"7bit");
			BodyInfo.szBody=(TCHAR*)pCMsg->m_bstrBody;

			//	if(pCMsg->m_bstrAttachFileNameList.length()>0)
			if(pCMsg->m_bstrAttachFileNameList.length()>0 
					||pCMsg->m_FILEINFO_AttachFileInfoList!=NULL)
			{
				hr=GetAttachments(pCMsg->m_bstrAttachFileNameList,
										&pCMsg->m_FILEINFO_AttachFileInfoList);
				if(hr!=S_OK)
				{
					g_dwAppErr=E_UNABLE_TO_ATTACH;
					break;
				}
			}
		
			
			
			if(pCMsg->m_bAddMIMEHeader)
					bDropHeader=false;
			else
				    bDropHeader=true;


			#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreateSMIMEEntity-Begin",
													(LPCTSTR) "VSSC", MB_OK );
			#endif

			CreateSMIMEEntity(
							pCMsg->m_FILEINFO_AttachFileInfoList,
							&BodyInfo,
							&szSMIMEEntity,
							bDropHeader
							 );

			if(szSMIMEEntity==NULL)
			{
				hr=E_OUTOFMEMORY;
				g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
				break;
			}

			#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreateSMIMEEntity-End",
													(LPCTSTR) "VSSC", MB_OK );
		    #endif

		
			dwLen=strlen(szSMIMEEntity);
			if(dwLen % 8 ==0)
			{
				dwInput = dwLen + 8;
			}
			else
			{
				dwInput=dwLen+(ENC_BLOCK_SIZE-(dwLen%ENC_BLOCK_SIZE));
			}

			pbBuffer = (BYTE *)malloc(dwInput/*8*/);
			CHECK_MEM_BREAK(pbBuffer)
			if (pbBuffer != NULL)
			{
				memcpy(pbBuffer, szSMIMEEntity, dwLen);
			}

			/////Del-memory
			FREE_MEMORY(szSMIMEEntity);


		}
	  else
	  {
		    
		    dwLen=pCMsg->m_bstrSMIMEMsg.length();
			if(dwLen % 8 ==0)
			{
				dwInput = dwLen + 8;
			}
			else
			{
				dwInput=dwLen+(ENC_BLOCK_SIZE-(dwLen%ENC_BLOCK_SIZE));
			}

			pbBuffer = (BYTE *)malloc(dwInput/*8*/);
			CHECK_MEM_BREAK(pbBuffer)
			if (pbBuffer != NULL)
			{
				memcpy(pbBuffer, (TCHAR*)pCMsg->m_bstrSMIMEMsg,dwLen);
			}

			/////Del-memory
			//pCMsg->m_bstrSMIMEMsg="";


	  }


		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "VSBSafeGenSessionKey-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		/////Generate A Session Key
		bRet = VSBSafeGenSessionKey(pCMsg->m_nKeySize, &i_pRCKey);
		if(bRet)
		{
			hr=E_BSAFE_KEYGEN_FAILED;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "VSBSafeGenSessionKey-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "VSBSafeEncrypt-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		/////Encrypt the Data with Session key SYM_3DES ,SYM_RC2_CBC
		bRet =  VSBSafeEncrypt(
							  pCMsg->m_nEncryptAlgId,
							  &i_pRCKey,
							  pCMsg->m_nKeySize*8,
							  IV,pbBuffer,
							  &dwLen,
							  dwInput
							  );
		if(bRet)
		{
			hr=E_BSAFE_ENCRYPT_FAILED;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "VSBSafeEncrypt-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
		
		//////
		DWORD   dwRecipient=pCMsg->m_EncryptCertList.size();
		
		pRecipientInfo=new PVS_RECIPIENT_INFO[dwRecipient];
		CHECK_MEM_BREAK(pRecipientInfo)

		RecipientInfo=new VS_RECIPIENT_INFO[dwRecipient]; 
		CHECK_MEM_BREAK(RecipientInfo)


		char szObjId[512];
		PCERT_INFO         pEncryptCertInfo=NULL;
		

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "RecipientInfo-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		for (it = pCMsg->m_EncryptCertList.begin();
						it != pCMsg->m_EncryptCertList.end(); ++it)
		{
					pObj=(*it);


					VSSC_ENCODED_CERT  EncodedCert;

					SYSTEMTIME      stSysTime;
					DATE			dtDate;

					BOOL   bExpiredCert=FALSE;
					BOOL   bRevokedCert=FALSE;

					memset(&EncodedCert,0,sizeof(VSSC_ENCODED_CERT));


					if(pObj->stCertStatusInfo.dwResolutionTypeBit!=0)
					{

							GetSystemTime(&stSysTime);
							if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
							{
								hr = E_SYSTIMETOVARTIMEFAILED;
								g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
							}
							
							

							if(!(pObj->DecCertInfo.dateEffDate<dtDate &&
								 dtDate <pObj->DecCertInfo.dateExpDate))
								 
							{
								
								bExpiredCert=TRUE;
								
							}
							
							if(pObj->stCertStatusInfo.dwRevocationStatus!=0)
							{
								
								bRevokedCert=TRUE;
								
							}
					}

					if(pObj->stCertStatusInfo.dwResolutionTypeBit!=0 &&
										!bExpiredCert &&!bRevokedCert)
					{
						if(pObj->cbEncryptEncodedCert!=0 ||
							pObj->pbEncryptEncodedCert!=NULL)
						{
							EncodedCert=pObj->GetEncryptionCert();
							CCertInfo  UserEncryptInfo(EncodedCert.pbData,EncodedCert.cbData);
							pEncryptCertInfo=UserEncryptInfo.GetCertInfo();
							pCertInfo=pEncryptCertInfo;
						}
					}
					else
					{
						if(pCMsg->m_dwUsePRC!=0)
						{
							

							///// For Not found Certifiicate Only
							if(
								((pCMsg->m_dwUsePRC & USE_PRC_FOR_NOT_FOUND)&&pObj->stCertStatusInfo.dwResolutionTypeBit==0)
								//(!(pCMsg->m_dwUsePRC & USE_PRC_FOR_EXPIRED)&&!bExpiredCert)&&
								//(!(pCMsg->m_dwUsePRC & USE_PRC_FOR_REVOKED)&&!bRevokedCert)
								)
							{
									hr=HowToUsePRC(
												  &pCMsg->m_PRCCertList,
									              pCMsg->m_dwUsePRC,
									              &pCertInfo
									              );


								
							}

							///// For Expired Certificate Only
							if(
								//((pCMsg->m_dwUsePRC & USE_PRC_FOR_NOT_FOUND)&&pObj->stCertStatusInfo.dwResolutionTypeBit!=0)&&
								((pCMsg->m_dwUsePRC & USE_PRC_FOR_EXPIRED)&&bExpiredCert)
								//(!(pCMsg->m_dwUsePRC & USE_PRC_FOR_REVOKED)&&!bRevokedCert)
								)
							{
								if(pCertInfo==NULL)
								{
									hr=HowToUsePRC(
									&pCMsg->m_PRCCertList,
									pCMsg->m_dwUsePRC,
									&pCertInfo
									);

								}

							}

							///// For Revoked certificate only
							if(
								//(!(pCMsg->m_dwUsePRC & USE_PRC_FOR_NOT_FOUND)&&pObj->stCertStatusInfo.dwResolutionTypeBit!=0)&&
								//(!(pCMsg->m_dwUsePRC & USE_PRC_FOR_EXPIRED)&&!bExpiredCert)&&
								((pCMsg->m_dwUsePRC & USE_PRC_FOR_REVOKED)&&bRevokedCert)
								)
							{
									if(pCertInfo==NULL)
									{
											hr=HowToUsePRC(
											&pCMsg->m_PRCCertList,
											pCMsg->m_dwUsePRC,
											&pCertInfo
											);

									}

							}

							if(pCertInfo==NULL)
							{
								hr=E_PRC_NOTALLOWED;
								g_dwAppErr= E_UNABLE_TO_CONSTRUCT_MSG;
								break;
							}
						

						}
						else
						{
							hr=E_ENCRYPT_CERTNOTFOUND;
							g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
							goto Quit;
						}
							
					}

					
								
					/////Encrypt the Session key With Public Key
					bRet = VSBSafePublicKeyEncrypt(&pCertInfo->SubjectPublicKeyInfo,
							i_pRCKey.data,i_pRCKey.len,	&pbKeyBlob,	(unsigned int *)&dwKeyBlobLen);
					if(bRet) 
					{
						hr=E_BSAFE_PUB_ENCRYPT_FAILED;
						g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
						goto Quit;
					}

					memset(&RecipientInfo[i],0,sizeof(VS_RECIPIENT_INFO));
					
					////allocate and copy IssureDN
					RecipientInfo[i].Issuer.cbData = pCertInfo->Issuer.cbData;
					RecipientInfo[i].Issuer.pbData=(BYTE *)malloc(pCertInfo->Issuer.cbData);
					if(RecipientInfo[i].Issuer.pbData==NULL)
					{
						hr=E_OUTOFMEMORY;
						g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
						goto Quit;
					}

					
					memset(RecipientInfo[i].Issuer.pbData,0,pCertInfo->Issuer.cbData);
					memcpy(RecipientInfo[i].Issuer.pbData,pCertInfo->Issuer.pbData,
																	pCertInfo->Issuer.cbData);

					////Allocate and copy Serial Num
					RecipientInfo[i].SerialNumber.cbData = pCertInfo->SerialNumber.cbData;
					RecipientInfo[i].SerialNumber.pbData=(BYTE *)malloc(pCertInfo->SerialNumber.cbData);
					if(RecipientInfo[i].SerialNumber.pbData==NULL)
					{
						hr=E_OUTOFMEMORY;
						g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
						goto Quit;
					}


					memset(RecipientInfo[i].SerialNumber.pbData,0,pCertInfo->SerialNumber.cbData );
					memcpy(RecipientInfo[i].SerialNumber.pbData,pCertInfo->SerialNumber.pbData,
																		pCertInfo->SerialNumber.cbData);

					
					/////Allocate and Copy Encrypted Session Key
					RecipientInfo[i].EncryptedKey.cbData = dwKeyBlobLen;
					RecipientInfo[i].EncryptedKey.pbData=(unsigned char*)malloc(dwKeyBlobLen);
					if(RecipientInfo[i].EncryptedKey.pbData==NULL)
					{
						hr=E_OUTOFMEMORY;
						g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
						goto Quit;
		
					}
					memset(RecipientInfo[i].EncryptedKey.pbData,0,dwKeyBlobLen); 
					memcpy(RecipientInfo[i].EncryptedKey.pbData,(unsigned char*)pbKeyBlob,dwKeyBlobLen); 


					strcpy(szObjId, szOID_RSA_RSA);
					RecipientInfo[i].KeyEncryptionAlgID.pszObjId  =(char *)malloc(strlen(szObjId)+1);
					if(RecipientInfo[i].KeyEncryptionAlgID.pszObjId==NULL)
					{
						hr=E_OUTOFMEMORY;
						g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
						goto Quit;
					}
					strcpy(RecipientInfo[i].KeyEncryptionAlgID.pszObjId,szObjId);
					
					pRecipientInfo[i] = &RecipientInfo[i];
					
					i++;
					NumOfRecipientsEncCert++;

					if(pCertInfo)
					{
							freecertinfo(pCertInfo);
							FREE_MEMORY(pCertInfo)
								
					}

					FREE_MEMORY(pbKeyBlob)
				//	FREE_MEMORY(pEncryptCertInfo)


		}


		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "RecipientInfo-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif


		/////////////Prepare encrypted content//////////
		VS_ENCRYPTED_CONTENT_INFO EncryptedContentData;

		EncryptedContentData.EncryptedContent.cbData = dwInput;
		EncryptedContentData.EncryptedContent.pbData = (unsigned char*)pbBuffer;

	
		//////Encryption Algo
		////SYM_3DES ,SYM_RC2_CBC

		if(pCMsg->m_nEncryptAlgId==SYM_RC2_CBC)
			strcpy(szObjId, szOID_RSA_RC2CBC);
		else
		{
			strcpy(szObjId, szOID_RSA_DES_EDE3_CBC);
		}
		
		EncryptedContentData.ContentEncryptionAlgID.pszObjId = szObjId;
		

		EncryptedContentData.ContentEncryptionAlgID.Parameters.cbData = 8;
		EncryptedContentData.ContentEncryptionAlgID.Parameters.pbData = IV;

		

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreateEnvelopedData-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
		//////pass encrypted content and recipients info
		iRet=CreateEnvelopedData(&EncryptedContentData,
							pRecipientInfo,
							NumOfRecipientsEncCert,
							&pszEnvelopedData64);

		if(iRet!=0)
		{
			hr=E_CREATE_ENVELOP_DATA_FAILED;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}



		if(pszEnvelopedData64==NULL)
		{
			hr=E_CREATE_ENVELOP_DATA_FAILED;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;

		}
		
		FREE_MEMORY(pbBuffer);

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreateEnvelopedData-End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif


		//VSSCMessage Msg;
		Msg = VSSCMessage :: NewMessage("",0);

		/////CHECK FOR RFC822 Header
		if(pCMsg->m_bAddRFC822Header)
		{
				hr=AddRFC822Header(Msg,pCMsg);
				CHECK_HRESULT_BREAK
		}

		
		VSSCHeaders& headers = Msg->GetHeaders();

		/////application/pkcs7-mime;smime-type=enveloped-data;name=smime.p7m
		/////CHECK FOR MIME Header
		if(pCMsg->m_bAddMIMEHeader)
		{
			headers.GetContentType().SetTypeString("application");
			headers.GetContentType().SetSubTypeString("pkcs7-mime");
			headers.GetContentType().SetSMIMEType("enveloped-data");
			headers.GetContentType().SetName("smime.p7m");
			headers.GetContentTransferEncoding().SetString("base64");
			headers.GetContentDisposition().SetDispTypeString("application");
			headers.GetContentDisposition().SetFileName("smime.p7m");
		}

		Msg->GetBody().SetString(pszEnvelopedData64);
		Msg->Assemble();

		FREE_MEMORY(szEnvelopedMessage)

		
		VSSCString vsscMsg = Msg->GetString();
		BSTR   bstrSMIME=_MultiToWideString(vsscMsg.GetString());
		if(bstrSMIME==NULL)
		{
			hr=E_UNABLE_TO_CONSTRUCT_MSG;
			g_dwAppErr=E_UNABLE_TO_CONSTRUCT_MSG;
			break;
		}

		pCMsg->m_bstrSMIMEMsg=bstrSMIME;
		SysFreeString(bstrSMIME);
	

	}
	while(0);
Quit:
	
	if(RecipientInfo)
			FreeRecipientInfo(
							 RecipientInfo,
							 NumOfRecipientsEncCert
							 );

	DELETE_MEMORY(pRecipientInfo)
	DELETE_MEMORY(RecipientInfo)
	DELETE_MEMORY(pszEnvelopedData64);
	DELETE_MEMORY(Msg)


	FREE_MEMORY(i_pRCKey.data)
	FREE_MEMORY(pbBuffer)
	FREE_MEMORY(szEnvelopedMessage)
	FREE_MEMORY(szSMIMEEntity)
	


    return hr;
}




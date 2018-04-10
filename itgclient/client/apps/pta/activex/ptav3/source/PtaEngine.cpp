// PtaEngine.cpp: implementation of the CPtaEngine class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "PtaEngine.h"
#include "certstructs.h"
#include <wincrypt.h>
#include "vscapi.h"
#include "ptaerrs.h"
#include "ptadefines.h"
#include "utils.h"
#include "simder_all.h"
#include "bsafelite.h"
#include "integrate.h"
#include "cspglobals.h"
#include "MyUniversalInteger.h"
#include "csputil.h"
#include "keycontainer.h"
#include "certinfo.h"
#include "utils.h"
#include "pkcs12info.h"
#include "pkcs12errs.h"
#include "ExportP12.h"

#include <rpcdce.h>
#include <tchar.h>


extern CVirtualSmartCard* _gpVirtualSmartCard;
extern CVSPTA* _gpCurrPTA;
extern BOOL _gboolOpenedWithPassword;
extern PSRCHCRIT _gpSrchCrit;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


HRESULT CPtaEngine::Initialize(short boolCapiFlag)
{
	HRESULT retVal = S_OK;

	switch ( boolCapiFlag )
	{
		case 0:
			boolIsCapi = 0;
			dwIsTPM = 0;
			break;
		case 1:
			boolIsCapi	= 1;
			dwIsTPM		= 0;
			break;
		case 2:
			dwIsTPM		= 1;
			boolIsCapi	= 0;
			break;
		default:
			retVal = E_INVALIDARGS;
			return retVal;
	}

	

	retVal = _InitEngine();
	if(retVal == E_CRYPT32LOADFAILED && !boolCapiFlag)
		retVal = S_OK;


	if(retVal == S_OK)
	{
		/*Init the pta capi functions*/
		if(boolIsCapi || dwIsTPM)
		{
			if(!_InitPtaCapiWithMSCapi())
				return E_CANNOTLOADMSCAPI;
		}
		else
		{
			if(!_InitPtaCapiWithVSCapi())
				return E_CANNOTLOADVSCAPI;
		}
	}

	return retVal;
}

HRESULT CPtaEngine::Close()
{
	boolIsCapi = FALSE;
	dwIsTPM	=	PTA_NO_TPM_MOEE;
	PtaCapi_CertFreeCertitificateContext = NULL;
	PtaCapi_CertDuplicateCertificateContext = NULL;
	return S_OK;
}

HRESULT CPtaEngine::FreeIdList(PIDLISTNODE pIdListHeadNode)
{

	if (!dwIsTPM)
	{
		//Free the list recursively
		if(pIdListHeadNode)
		{
			if(!PtaCapi_CertFreeCertitificateContext(pIdListHeadNode->pCertContext))
			{
				return E_FAIL;
			}
			
			//delete(pIdListHeadNode->pCertContext);
			pIdListHeadNode->pCertContext = NULL;

			delete(pIdListHeadNode->pAuxCertInfo);
			pIdListHeadNode->pAuxCertInfo = NULL;

			delete(pIdListHeadNode->pDecCertInfo);
			pIdListHeadNode->pDecCertInfo = NULL;
			
			FreeIdList(pIdListHeadNode->pidlistnodeNext);
			pIdListHeadNode->pidlistnodeNext = NULL;

			delete pIdListHeadNode;

		}
	}

	return S_OK;
}

HRESULT CPtaEngine::CreateCertHash(PCERT_CONTEXT i_pCertContext, int i_nHashAlgId, unsigned char *o_pbyteHashVal)
{
	return S_OK;
}


HRESULT CPtaEngine::GetSelIDCertContext(PCERT_CONTEXT i_pCertContext, VARIANT *pVal)
{
	HRESULT retVal = S_OK;
	DWORD dwSize = 0;

	if(i_pCertContext)
	{
		pVal->vt = VT_EMPTY;

		if(!MSCapi_CertSerializeCertificateStoreElement(i_pCertContext, 0, NULL, &dwSize))
			retVal = E_CERTSERIALIZEFAILED;
		else
		{
			pVal->parray = SafeArrayCreateVector(VT_UI1, 0, dwSize);
			if(!pVal->parray)
				retVal = E_SAFEARRAYCREATEVECTFAILED;
			else
			{
				if(!MSCapi_CertSerializeCertificateStoreElement(i_pCertContext, 0, (BYTE*)pVal->parray->pvData, &dwSize))
				{
					SafeArrayDestroy(pVal->parray);
					retVal = E_CERTSERIALIZEFAILED;
				}
			}

			pVal->vt = VT_ARRAY;
		}
	}
	else
	{
		pVal->vt = VT_EMPTY;
		retVal = E_INVALIDARGS;
	}

	return retVal;
}


HRESULT CPtaEngine::GetLocalProfilesList(_bstr_t& i_tbstrAppContextName, _bstr_t** o_pptbstrProfiles, int& nNumOfProfiles)
{
	HRESULT retVal = S_OK;

	/*Create the name of the file to be searched*/
	BSTR bstrProfPathName = 0;
	_bstr_t tbstrProfPathName = "";

	if(retVal == S_OK)
	{
		retVal = CreateProfile_Path_Name(L"*",i_tbstrAppContextName,&bstrProfPathName);
		
		if(retVal == S_OK)
		{
			tbstrProfPathName = bstrProfPathName;

			/*Find out how many files match this criteria*/
			retVal = _FindFiles(tbstrProfPathName, NULL, nNumOfProfiles);
			SysFreeString(bstrProfPathName);
		}
	}

	if(retVal != S_OK)
	{
		//If no profiles were found we are done.
		if(retVal = E_FILENOTFOUND || retVal == E_PATHNOTFOUND)
		{	
			*o_pptbstrProfiles = NULL;
			return S_OK;
		}

		return retVal;
	}

	//Allocate memory
	*o_pptbstrProfiles=(_bstr_t*)new _bstr_t[nNumOfProfiles];
	
	/*Search for the files*/
	retVal = _FindFiles(tbstrProfPathName, *o_pptbstrProfiles, nNumOfProfiles);
	if(retVal != S_OK)
	{
		delete[](*o_pptbstrProfiles);
		return retVal;
	}

	/*Now extract the profile names from the entire path*/
	BSTR bstrUserName = 0;
	BSTR bstrPath = 0;
	BSTR bstrApContext = 0;

	for(int i =0;i<nNumOfProfiles;++i)
	{
		retVal = ParseProfile_Path_Name
		(
			(*o_pptbstrProfiles)[i],
			&bstrUserName,
			&bstrPath,
			&bstrApContext
		);

		if(retVal == S_OK)
		{
			(*o_pptbstrProfiles)[i] = bstrUserName;
			SysFreeString(bstrUserName);
			SysFreeString(bstrPath);
			SysFreeString(bstrApContext);

		}
	}

//	VSPTA_CLEAN_TBSTR(tbstrProfPathName)

	return retVal;
}

HRESULT CPtaEngine::GetProfileFilePathAndName(_bstr_t& i_tbstrAppContextName, _bstr_t& i_tbstrUserName, _bstr_t* o_ptbstrProfileFilePathAndName)
{
	HRESULT retVal = S_OK;
	BSTR bstrProfPathName = 0;

	retVal = CreateProfile_Path_Name(i_tbstrUserName,i_tbstrAppContextName,&bstrProfPathName);
	if(retVal == S_OK)
	{
		*o_ptbstrProfileFilePathAndName = bstrProfPathName;
		SysFreeString(bstrProfPathName);
	}
	
	return S_OK;
}

BOOL CPtaEngine::_InitPtaCapiWithMSCapi()
{
	PtaCapi_CertFreeCertitificateContext = MSCapi_CertFreeCertitificateContext;
	if(!PtaCapi_CertFreeCertitificateContext)
		return 0;

	PtaCapi_CertDuplicateCertificateContext = (LPFNCertDuplicateCertificateContext)GetProcAddress(m_hModCapiDll,"CertDuplicateCertificateContext");
	if(!PtaCapi_CertDuplicateCertificateContext)
		return 0;

    MSCapi_CertEnumCertificatesInStore = (LPFNCertEnumCertificatesInStore)GetProcAddress(m_hModCapiDll, "CertEnumCertificatesInStore");
	if(!MSCapi_CertEnumCertificatesInStore)
	{
		return 0;
	}

	MSCapi_CertGetCertificateContextProperty = (LPFNCertGetCertificateContextProperty)GetProcAddress(m_hModCapiDll, "CertGetCertificateContextProperty");
	if(!MSCapi_CertGetCertificateContextProperty)
	{
		return 0;
	}

	MSCapi_CryptSignMessage = (LPFNCryptSignMessage)GetProcAddress(m_hModCapiDll, "CryptSignMessage");
	if(!MSCapi_CryptSignMessage)
	{
		return 0;
	}


	PtaCapi_CertGetIssuerCertificateFromStore = (LPFNCertGetIssuerCertificateFromStore)GetProcAddress(m_hModCapiDll, "CertGetIssuerCertificateFromStore");
	if(!PtaCapi_CertGetIssuerCertificateFromStore )
	{
		return 0;
	}

	PtaCapi_CertCompareCertificate = (LPFNCertCompareCertificate)GetProcAddress(m_hModCapiDll, "CertCompareCertificate");
	if(!PtaCapi_CertCompareCertificate)
	{
		return 0;
	}

	PtaCapi_CertFindCertificateInStore= (LPFNCertFindCertificateInStore)GetProcAddress(m_hModCapiDll, "CertFindCertificateInStore");
	if(!PtaCapi_CertFindCertificateInStore)
	{
		return 0;
	}

	MSCapi_CryptAcquireContext= (LPFNCryptAcquireContext)GetProcAddress(m_hModAdvapiDll, "CryptAcquireContextA");
	if(!MSCapi_CryptAcquireContext)
	{
		return 0;
	}

	MSCapi_CryptReleaseContext= (LPFNCryptReleaseContext)GetProcAddress(m_hModAdvapiDll, "CryptReleaseContext");
	if(!MSCapi_CryptReleaseContext)
	{
		return 0;
	}

	return 1;
}

BOOL CPtaEngine::_InitPtaCapiWithVSCapi()
{
	PtaCapi_CertFreeCertitificateContext = VS_CertFreeCertificateContext;
	PtaCapi_CertDuplicateCertificateContext = VS_CertDuplicateCertificateContext;
	return 1;
}

HRESULT CPtaEngine::_FindFiles(_bstr_t& i_tbstrSrchPath, _bstr_t *o_ptbstrFileNames, int &nNumOfFiles)
{
	HANDLE hFindFileHandle;
	WIN32_FIND_DATA FindFileData;
	int err;

	//Obtain the first file
	hFindFileHandle = FindFirstFile(i_tbstrSrchPath, &FindFileData);
	if(hFindFileHandle == INVALID_HANDLE_VALUE)
	{
		nNumOfFiles = 0;
		err = GetLastError();
		switch(err)
		{
		case ERROR_FILE_NOT_FOUND :
		case ERROR_NO_MORE_FILES:
			return E_FILENOTFOUND;
		case ERROR_PATH_NOT_FOUND :			
			return E_PATHNOTFOUND;

		default :
			return E_FAIL;
		}
	}

	//Obtain the name of the file
	nNumOfFiles = 1;
	if(o_ptbstrFileNames)
	{
		o_ptbstrFileNames[0] = FindFileData.cFileName;
	}

	err = 0;
	do
	{
		if(!FindNextFile(hFindFileHandle, &FindFileData))
			err = GetLastError();
		else
		{
			nNumOfFiles++;
			if(o_ptbstrFileNames)
				o_ptbstrFileNames[nNumOfFiles - 1] = FindFileData.cFileName;
		}
	}while(!err);

	switch(err)
	{
	case ERROR_NO_MORE_FILES :
		return S_OK;

	default :
		return E_FAIL;
	}

	return S_OK;
	
}

void CPtaEngine::FreeLocalProfilesList(_bstr_t *in_ptbstrProfiles)
{
	delete[](in_ptbstrProfiles);
	return;
}

HRESULT CPtaEngine::GetMatchingCerts(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrAppCtxtName, SRCHCRIT &i_theSrchCrit, PIDLISTNODE *o_ppMatchingCertList)
{
	HRESULT retVal = S_OK;
	PIDLISTNODE pCertsInStore = NULL;

	/*Obtain the list of certs*/
	if(boolIsCapi || dwIsTPM)
	{
		retVal = _GetCertsFromMSCapi(&pCertsInStore);
	}
	else
	{
		retVal = _GetCertsFromVSCapi(i_pVirtualSmartCard,&pCertsInStore);
	}

	/*Obtain the decoded cert information*/
	if(retVal == S_OK)
	{
		if(pCertsInStore)
			retVal = _GetDecCertInfo(pCertsInStore);
	}

	/*Obtain the auxilary cert information*/
	if(retVal == S_OK)
	{
		retVal = _GetAuxCertInfo(i_pVirtualSmartCard, i_tbstrAppCtxtName, pCertsInStore);
	}

	/*Filter out this list*/
	if(retVal == S_OK)
	{
		*o_ppMatchingCertList = NULL;
		retVal = _FilterCertList(i_pVirtualSmartCard, pCertsInStore, i_theSrchCrit, o_ppMatchingCertList);
	}

	
	/*Free memory*/
	if(pCertsInStore)
	{
		FreeIdList(pCertsInStore);
	}


	return retVal;
}

PIDLISTNODE CPtaEngine::CopyCert(PIDLISTNODE i_pCertToCopy)
{
	//For debug only
	PIDLISTNODE pidListNodeRetVal;

	pidListNodeRetVal = NewCert();
	pidListNodeRetVal->pidlistnodeNext = NULL;
	
	if(i_pCertToCopy->pAuxCertInfo)
	{
		pidListNodeRetVal->pAuxCertInfo = new AUXCERT_INFO;
		*(pidListNodeRetVal->pAuxCertInfo) = *(i_pCertToCopy->pAuxCertInfo);
	}
	
	if(i_pCertToCopy->pCertContext)
	{
		pidListNodeRetVal->pCertContext = (PCERT_CONTEXT)PtaCapi_CertDuplicateCertificateContext(i_pCertToCopy->pCertContext);
	}
	
	if(i_pCertToCopy->pDecCertInfo)
	{
		pidListNodeRetVal->pDecCertInfo = new DECCERT_INFO;
		*(pidListNodeRetVal->pDecCertInfo) = *(i_pCertToCopy->pDecCertInfo);
	}

	return pidListNodeRetVal;
}

// Modified By: Infosys Technologies Ltd.
// Change Request: CR#21529
// Description: Pass an additional parameters to CreateCertReq 
// to accomodate the IsPrivateKeyExportable flag
HRESULT CPtaEngine::CreateCertReq(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrSubjectDN, int i_nKeyAttribs, int i_nHashAlg, int i_nNumOfAttrs,
		_bstr_t* i_ptbstrAtrrOIDs, _bstr_t* i_ptbstrAttrVals, _bstr_t* o_ptbstrCertReq, PBYTE* o_ppbytePubKeyHash, DWORD* o_pdwPubKeyHashSize, const BOOL i_bIsPrivateKeyExportable)		
// CR#21529: Modification Ends
{
	HRESULT retVal = S_OK;

	int nKeySize;
	int nKeyExportableFlag;
	int nKeyType;
//	int nKeyGenAlgId;
	A_RSA_KEY thePubKey;

	_bstr_t tbstrContainerName = "";
	UUID	uuid;
	unsigned char* pszUuid;
	BYTE*	pbyteModulus			=	NULL;
	DWORD	dwModulusLen			=	0;

	VS_TSS_Key*		pVSTSS_Key;

	unsigned char f4Data[3] = {0x01, 0x00, 0x01 };

	nKeySize = ((i_nKeyAttribs & KEYSIZE_BASE) >> 16);
	nKeyExportableFlag = (i_nKeyAttribs & EXPORTABLE_BASE)?0:VS_CSP_KEY_EXPORTABLE;
	nKeyType = (i_nKeyAttribs & KEYTYPE_BASE);
	
	if(nKeyType == KEY_SIGNATURE)
		m_nCertReqKeyType = VS_RSA_SIGN;
	else if(nKeyType == KEY_ENCRYPTION)
		m_nCertReqKeyType = VS_RSA_KEYX;
	else
		return E_INVALIDKEYTYPE;

	/*Do a key gen*/
	PBYTE pbytePubKey	= NULL;
	DWORD dwPubKeySize	= 0;
	
	if ( dwIsTPM )
	{
		if ( HASH_SHA1 != i_nHashAlg )
		{
			return	E_INVALIDARG;
		}

		pVSTSS_Key =	NULL;

		if ( NULL == _gpVirtualSmartCard )
		{
			UuidCreate(&uuid);
			UuidToString(&uuid,&pszUuid);
			tbstrContainerName = (char*)pszUuid;
			RpcStringFreeA(&pszUuid);

			_gpVirtualSmartCard = new CVirtualSmartCard;

			retVal =	_gpVirtualSmartCard -> VSM_TPMInitialize
						(
							tbstrContainerName,
							VS_TPM_CONTAINER_CREATE,
							m_PTA
						);
			if ( S_OK != retVal )
			{
				return	retVal;
			}
		}

		if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
			
			retVal = ((CVSPTA*)m_PTA)->CreatePassword();
			if( S_OK != retVal )
			{
				return retVal;
			}

		}

		//Do a key gen
		retVal =	_gpVirtualSmartCard->VSTPM_CreateKey
					(
						nKeySize,
						m_nCertReqKeyType,
						&pVSTSS_Key
					);
		if ( S_OK != retVal )
		{
			return	retVal;
		}

		retVal =	pVSTSS_Key -> GetModulus
					(
						(DWORD*) &(thePubKey.modulus.len),
						&(thePubKey.modulus.data)
					);
		if ( S_OK != retVal )
		{
			return	retVal;
		}

		(thePubKey.exponent).len =	3;
		(thePubKey.exponent).data =	new BYTE [(thePubKey.exponent).len];
		memcpy
		(
			(void*) (thePubKey.exponent).data,
			(const void*) f4Data,
			(thePubKey.exponent).len
		);

		dwPubKeySize =	20; // this is actually hash of the pub key and NOT the actual pub key
		pbytePubKey = new BYTE [dwPubKeySize];

		retVal =	HashPublicKey
					(
						&thePubKey,
						pbytePubKey
					);
		if ( S_OK != retVal )
		{
			return	retVal;
		}

/*
		retVal =	GetBlobFromKey
					(
						&thePubKey,
						&pbytePubKey,
						&dwPubKeySize
					);
		if ( S_OK != retVal )
		{
			return	retVal;
		}

*/

	}
	else
	{
		//Do a key gen
                // Modified By: Infosys Technologies Ltd.
                // Change Request: CR#21529
                // Description: Pass the privateKeyExportable flag to VSM_GenKey
                // function.
		retVal = i_pVirtualSmartCard->VSM_GenKey(m_nCertReqKeyType,nKeySize,nKeyExportableFlag,NULL,&dwPubKeySize, i_bIsPrivateKeyExportable);
                // CR#21529: Modification Ends
		if(retVal == S_OK)
		{
			pbytePubKey = new BYTE[dwPubKeySize];
			if(!pbytePubKey)
				retVal = E_FAIL;
			else
			{
                                // Modified By: Infosys Technologies Ltd.
                                // Change Request: CR#21529
                                // Description: Pass the privateKeyExportable flag to VSM_GenKey
                                // function.
				retVal = i_pVirtualSmartCard->VSM_GenKey(m_nCertReqKeyType,nKeySize,nKeyExportableFlag,pbytePubKey,&dwPubKeySize, i_bIsPrivateKeyExportable);
                                // CR#21529: Modification Ends
			}
		}
		
		/*Obtain the actual public key from the smart card*/
		if(retVal == S_OK)
		{
			PBYTE pbyteActualPubKey = NULL;
			DWORD dwActualPubKeyLen;
			
			retVal = i_pVirtualSmartCard->VSM_ExportKey(pbytePubKey,dwPubKeySize,0,NULL,0,0,NULL,&dwActualPubKeyLen);
			if(retVal == S_OK)
			{
				pbyteActualPubKey = (PBYTE)new BYTE[dwActualPubKeyLen];
				if(!pbyteActualPubKey)
					retVal = E_FAIL;
				else
				{
				
					retVal = i_pVirtualSmartCard->VSM_ExportKey(pbytePubKey,dwPubKeySize,0,NULL,0,0,pbyteActualPubKey,&dwActualPubKeyLen);
					if(retVal == S_OK)
					{
						//Convert the byte blob into the pub key data structure
						retVal = GetKeyFromBlob(pbyteActualPubKey,dwActualPubKeyLen,&thePubKey);
					}
					delete[] pbyteActualPubKey;
				}
			}
		}
	}

	/*Create a pkcs10*/
	if(retVal == S_OK)
	{
		retVal = _CreatePKCS10(i_pVirtualSmartCard,pbytePubKey, dwPubKeySize, i_tbstrSubjectDN, &thePubKey, i_nHashAlg,i_nNumOfAttrs,i_ptbstrAtrrOIDs,i_ptbstrAttrVals, o_ptbstrCertReq);
	}
	
	if(retVal == S_OK)
	{
		*o_ppbytePubKeyHash = pbytePubKey;
		*o_pdwPubKeyHashSize = dwPubKeySize;
	}
	else
	{
		delete[] pbytePubKey;
		*o_ppbytePubKeyHash = NULL;
		*o_pdwPubKeyHashSize = 0;
	}

	return retVal;
}

HRESULT CPtaEngine::_CreatePKCS10(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbytePubKeyHandle, int i_nPubKeyHandleSize, _bstr_t& i_tbstrSubjectDN, A_RSA_KEY* i_pRSAPubKey, int i_nHashAlg,int i_nNumOfAttrs,_bstr_t* i_ptbstrAtrrOIDs,_bstr_t* i_ptbstrAttrVals, _bstr_t* o_ptbstrCertReq)
{
	HRESULT retVal = S_OK;
	VS_TSS_Hash* pVSTSSHash = NULL;
	
	BYTE*						pbyteDataSequence			=	NULL;
	DWORD						dwDataSequenceLen			=	0;

	DWORD						dwTSSVendor;

	/* Create Version object
		Version := INTEGER 
	*/
	short int nVersion = 0;
	CUniversalInteger cuiVersion(1,(PBYTE)&nVersion);
	
	/* Create the subject object of type Name defined as
		Name ::=	CHOICE { - - only one possibility for now - -  rdnSequence  RDNSequence }
		RDNSequence ::=	SEQUENCE OF RelativeDistinguishedName
		RelativeDistinguishedName ::= SET SIZE (1..MAX) OF AttributeTypeAndDistinguishedValue
		AttributeTypeAndDistinguishedValue ::= SEQUENCE {
														type			ATTRIBUTE.&id ({SupportedAttributes}),
														value			ATTRIBUTE.&Type({SupportedAttributes}{@type}),
														-- Note default and optional fields have been stripped off because we dont use them.
												}

		
		The subject object that we will create based on the above definition of Name will look as follows 

		subject = SEQUENCE {
						SET {
							SEQUENCE {
								OBJECT IDENTIFIER commonName (2 5 4 3)
								PrintableString 'vsc1enroll'
								}
							}
						}


	*/

	CSequence cseqSubject;

	//Parse the inputted DN into corresponding attribute type and value pairs
	_bstr_t* ptbstrDNAttrs = NULL;
	_bstr_t* ptbstrDNVals = NULL;
	int nNumOfDNAttrs;

	retVal = _ParseDNIntoComponents(i_tbstrSubjectDN,&nNumOfDNAttrs,&ptbstrDNAttrs,&ptbstrDNVals);
	
	//Now create the subject object
	if(retVal == S_OK)
	{
		CBaseDERCollection cbdcSubjectDN;

		for(int i=0; i<nNumOfDNAttrs;++i)
		{
			_bstr_t tbstrObjId = "";

			//Create the object identifier for the attribute
			if(ptbstrDNAttrs[i].length() == 2 && ptbstrDNAttrs[i] == _bstr_t("CN"))
			{
				tbstrObjId = "2.5.4.3";
			}
			else
			{
				retVal = E_SUBJECTDNINVALID;
				break;
			}

			CObjectIdentifier cobjidAttr(tbstrObjId.length(), (PBYTE)(CHAR*)tbstrObjId );

			//Create the printable string for the attribute value
			CPrintableString cpsVal(ptbstrDNVals[i].length(),(PBYTE)(CHAR*)ptbstrDNVals[i]);		

			//Create the sequence for this attribute and value
			CBaseDERCollection cbdcAttrVal;
			cbdcAttrVal = cobjidAttr + cpsVal;
			CSequence cseqAttrVal(cbdcAttrVal);

			//Add this sequence to the SubjectDN DER Blob
			cbdcSubjectDN = cbdcSubjectDN + cseqAttrVal;			
		}

		if(retVal == S_OK)
		{
			//Create the subject rdn
			CSet csetSubjectRDN(cbdcSubjectDN);

			//Create the Subject object
			cseqSubject = CSequence(csetSubjectRDN);
		}

		delete[] ptbstrDNAttrs;
		delete[] ptbstrDNVals;
	}
	
	
	/*
		Create a SubjectPublicKeyInfo object defined as
		SubjectPublicKeyInfo ::= SEQUENCE {  
									algorithm AlgorithmIdentifier,
									subjectPublicKey BIT STRING 
								 }
		AlgorithmIdentifier ::= SEQUENCE {  
									algorithm OBJECT IDENTIFIER,
									parameters ANY DEFINED BY ALGORITHM OPTIONAL 
								}

		where subjectPublicKey is the public key sequence encoded as a bit string.
		The rsa public key sequence is defined as follows
		RSAPublicKey ::= SEQUENCE {  
							 modulus INTEGER, -- n
							 publicExponent INTEGER -- e 
						 }

		The subjectPublicKeyInfo object in our case looks like this
		subjectPublicKeyInfo = SEQUENCE {
									SEQUENCE {
										OBJECT IDENTIFIER rsaEncryption(1 2 840 113549.1.1.1)
										NULL
									}
									BIT STRING
										-- contains an object of type RSAPublicKey
								}

	*/

	CSequence cseqPubKeyInfo;
	
	if(retVal == S_OK)
	{
		//Create the object identifier object for the rsaEncryption algorithm
		_bstr_t tbstrRSAEncObjId = "1.2.840.113549.1.1.1";
		CObjectIdentifier cobjidRSAEnc(tbstrRSAEncObjId.length(), (PBYTE)(CHAR*)tbstrRSAEncObjId);

		//ForDebug
#ifdef DEBUG
		FILE* fp;
		fp = (FILE*)fopen("temp.bin","wb"); 
		for(unsigned int i=0;i<cobjidRSAEnc.BaseDERBlob->cbData; ++i)
		{
			fprintf(fp,"%c",cobjidRSAEnc.BaseDERBlob->pbData[i]);
		}
		fclose(fp);
#endif

		//Create a null object
		CNull cnullObj;

		//Create the sequence for the alogrithm identifier.
		CBaseDERCollection cbdcAlgId;
		cbdcAlgId = cobjidRSAEnc + cnullObj;
		CSequence cseqAlgId(cbdcAlgId);

		

		//Create the modulus integer
		CMyUniversalInteger cmyuiPubKeyMod(i_pRSAPubKey->modulus.len, (PBYTE)i_pRSAPubKey->modulus.data);

		//Create the publicExponent integer
		CMyUniversalInteger cmyuiPubKeyExp(i_pRSAPubKey->exponent.len, (PBYTE)i_pRSAPubKey->exponent.data);

		//Create the sequence for the rsa public key
		CBaseDERCollection cbdcRSAPubKey;
		cbdcRSAPubKey = cmyuiPubKeyMod + cmyuiPubKeyExp;
		CSequence cseqRSAPubKey(cbdcRSAPubKey);

		//Create a bit string containing the public key sequnce
		CBitString bsmyRSAPubKey(0,cseqRSAPubKey.BaseDERBlob->cbData,cseqRSAPubKey.BaseDERBlob->pbData);


		//Create the sequence for the subject public key info
		CBaseDERCollection cbdcSubjPubKeyInfo;
		cbdcSubjPubKeyInfo = cseqAlgId + bsmyRSAPubKey;
		cseqPubKeyInfo = CSequence(cbdcSubjPubKeyInfo);
	}

	

	/* Create the attributes of type Attributes. We always create the attributes as below. This
	indicates that we are requesting a cert with the following cert extensions. The cert extensions
	we request are the key usage and the enhanced key usage.
		[0] {
			SEQUENCE {
				OBJECT IDENTIFIER certExtensions (1 3 6 1 4 1 311 2 1 14)
				SET {
					SEQUENCE {
						SEQUENCE {
							OBJECT IDENTIFIER keyUsage ( 2 5 29 15)
							BOOLEAN TRUE
							OCTET STRING
								03 02 01 38
									-- This a bit string which 
									-- specifies the key usage defined as a bit mask. 38 stand for 
									-- key encipherment, data encipherment and key exchange 
									-- C0 stands for digital signature and non repudiation.
							}
						SEQUENCE {
							OBJECT IDENTIFER enhKeyUsage (2 5 29 37)
							OCTET STRING
								30 0A 06 08 2B 06 01 05 05 07 03 02
									-- This is a sequnece of object identifier, identifying the
									-- extended key usage. The object identifier encoded above is
									-- 1.3.6.1.5.5.7.3.2 which stands for client auth. Note that
									-- this extension is passed to Xenroll while calling createpkcs10
							}
						}
					}
				}
			}
	*/

	CTaggedValue ctvAttributes;
	if(retVal == S_OK)
	{
		int a=0;
		//Create the certExtensions object identifier
		_bstr_t tbstrCertExtensionsOID = "1.3.6.1.4.1.311.2.1.14";
		CObjectIdentifier cobjidCertExtensions(tbstrCertExtensionsOID.length(), (PBYTE)(CHAR*)tbstrCertExtensionsOID);

		CBaseDERCollection cbdcKeyUsageCertExtension;
		for(int i=0;i<i_nNumOfAttrs;++i)
		{
			//Create the object identifier for the attribute
			_bstr_t tbstrAttrOID = i_ptbstrAtrrOIDs[i];
			CObjectIdentifier cobjidAttr(tbstrAttrOID.length(), (PBYTE)(CHAR*)tbstrAttrOID);

			//Create a boolean
			CBoolean cboolTrue(true);

			//Convert the value of the attribute from hex ascii to hex
			int nNumOfBytes = (i_ptbstrAttrVals[i].length())/2;
			BYTE* pbyteVal = (PBYTE)new BYTE[nNumOfBytes];
			if(!pbyteVal)
			{
				retVal = E_FAIL;
				break;
			}
			if(!AscHexToBytes(i_ptbstrAttrVals[i],pbyteVal))
			{
				retVal = E_ASCHEXTTOBYTESFAILED;
				break;
			}

/*
			//Reverse the byte blob
			for(int j=0;j<nNumOfBytes/2;++j)
			{
				BYTE temp = pbyteVal[j];
				pbyteVal[j] = pbyteVal[nNumOfBytes-j-1];
				pbyteVal[nNumOfBytes-j-1] = temp;
			}
*/

			//Create the octet string for this value
			COctetString cosVal(nNumOfBytes, pbyteVal);

			//Create the sequence for the attribute value pair
			CBaseDERCollection cbdcAttrVal;
			if(a==0)
			{
				cbdcAttrVal = cobjidAttr + cboolTrue + cosVal;
				a=1;
			}
			else
			{
				cbdcAttrVal = cobjidAttr  + cosVal;
			}
			CSequence cseqAttrVal(cbdcAttrVal);
			
			cbdcKeyUsageCertExtension = cbdcKeyUsageCertExtension+cseqAttrVal;
			delete[]pbyteVal;

		}

		if(retVal == S_OK)
		{
			//Enclose the attributes in a key usage cert extension sequence
			CSequence cseqKeyUsageCertExtension(cbdcKeyUsageCertExtension);

			//Enclose the key usage cert extension sequence in a set of cert extension
			CSet csetCertExtensions(cseqKeyUsageCertExtension);
			
			//Create a sequence representing the cert extensions attribute
			CBaseDERCollection cbdcCertExtensionsAttr;
			cbdcCertExtensionsAttr = cobjidCertExtensions + csetCertExtensions; 
			CSequence cseqCertExtesionAttr(cbdcCertExtensionsAttr);

			//Create the implicity tagged collection of attributes
			ctvAttributes = CTaggedValue(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(cseqCertExtesionAttr.BaseDERBlob));

		}
	}
	
	/* Create an object of type CertificationRequestInfo defined as
	SEQUENCE {
		version Version
		subject Name
		subjectPublicKeyInfo	SubjectPublicKeyInfo
		attributes [0] IMPLICIT Attributes
	}
	*/
	CSequence cseqCertRequestInfo;
	if(retVal == S_OK)
	{
		CBaseDERCollection cbdcCertRequestInfo;
		cbdcCertRequestInfo = cuiVersion + cseqSubject + cseqPubKeyInfo+ ctvAttributes;
		cseqCertRequestInfo = CSequence(cbdcCertRequestInfo);
	}

	
	
	/*Create the signature object defined below
		Signature = BIT STRING 
		The signature contains a bit string encoding of the an encrypted sha1 hash
		object. The sha1 hash object is encrypted using the private key.
		The sha1 hash object is defined as follows -
		SEQUENCE {
				SEQUENCE {
					OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
					NULL
					}
				OCTET STRING
					-- 20 byte octet string representing the hash value
		}
	*/
	CBitString cbsSignature;
	if(retVal == S_OK)
	{
		//Hash the data
		BYTE* pbyteHash = NULL;
		int nHashSize;
		BYTE* pbyteSignature = NULL;
		DWORD dwSignatureSize;
		void* pvHashCtxt;

		if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
		{
			retVal = E_HASHBEGINERR;
		}
		else
		{
			if(HashData(i_nHashAlg,pvHashCtxt,cseqCertRequestInfo.BaseDERBlob->pbData,cseqCertRequestInfo.BaseDERBlob->cbData) == -1)
			{
				retVal = E_HASHDATAERR;
			}
			else
			{
				//Allocate memory for the hash algorithm
				switch(i_nHashAlg)
				{
				case HASH_SHA1 :
					nHashSize = 20;
					pbyteHash = new BYTE[20];
					break;

				case HASH_MD2 :
				case HASH_MD5:
						nHashSize = 16;
						pbyteHash = new BYTE[16];
					break;

				default :
					retVal = E_INVALIDFLAGS;
					break;
				}

				if(HashEnd(i_nHashAlg,pvHashCtxt,pbyteHash,nHashSize) == -1)
				{
					retVal = E_HASHENDERR;
				}
				else
				{
					if ( dwIsTPM )
					{
						retVal = _gpVirtualSmartCard -> get_VSTPM_TSSVendor(&dwTSSVendor);
						if ( S_OK != retVal )
						{
							return	retVal;
						}

						retVal =	_gpVirtualSmartCard -> VSTPM_CreateHashObject
									(
										&pVSTSSHash
									);
						if ( S_OK != retVal )
						{
							return	retVal;
						}

							// If it is Infineon, then we sign the hash value directly. 
							// Otherwise, create DigestInfo sequence and sign it.
						if(dwTSSVendor == INFINEON_TSS)
						{
							retVal =	pVSTSSHash -> SetHashValue
										(
											nHashSize,
											pbyteHash
										);
						} else {

							retVal =	PutDataInSequenceFunc
										(
											pbyteHash,
											nHashSize,
											i_nHashAlg,
											&pbyteDataSequence,
											&dwDataSequenceLen
										);
							if ( S_OK != retVal )
							{
								return	retVal;
							}

							retVal =	pVSTSSHash -> SetHashValue
										(
											dwDataSequenceLen,
											pbyteDataSequence
										);

						}

						if ( S_OK != retVal )
						{
							return	retVal;
						}

						retVal =	_gpVirtualSmartCard->VSTPM_SignHash
									(
										pVSTSSHash,
										m_nCertReqKeyType,
										NULL,
										&dwSignatureSize
									);
						if ( S_OK == retVal )
						{
							pbyteSignature = new BYTE[dwSignatureSize];
							if(!pbyteSignature)
							{
								retVal = E_FAIL;
							}
							else
							{
								retVal = _gpVirtualSmartCard->VSTPM_SignHash
										(
											pVSTSSHash,
											m_nCertReqKeyType,
											pbyteSignature,
											&dwSignatureSize
										);
								if(retVal == S_OK)
								{
									//Create the bit string for the signature
									cbsSignature = CBitString(0,dwSignatureSize, pbyteSignature);
								}
							}
						}
					}
					else
					{
						//Now call the smart card to sign this hash. The smart card
						//will correctly create a hash object, and encrypt it
						retVal = i_pVirtualSmartCard->VSM_SignData(i_pbytePubKeyHandle,i_nPubKeyHandleSize,
							pbyteHash,nHashSize,i_nHashAlg,TRUE,NULL,&dwSignatureSize);
						if(retVal == S_OK)
						{
							pbyteSignature = new BYTE[dwSignatureSize];
							if(!pbyteSignature)
							{
								retVal = E_FAIL;
							}
							else
							{
								retVal = i_pVirtualSmartCard->VSM_SignData(i_pbytePubKeyHandle,i_nPubKeyHandleSize,
									pbyteHash,nHashSize,i_nHashAlg,TRUE,pbyteSignature,&dwSignatureSize);
								if(retVal == S_OK)
								{
									//Create the bit string for the signature
									cbsSignature = CBitString(0,dwSignatureSize, pbyteSignature);

								}
							}
						}
					}
				}

				delete[]pbyteHash;
			}
		}
	}
	
	/* Create the Certification Request object defined as 
	CertificationRequest := SEQUENCE {
									certificationRequestInfo CertificationRequestInfo
									signatureAlgorithm SignartureAlgorithmIdentifier,
									signature Signature
									}

	AlgorithmIdentifier := SEQUENCE {  
						algorithm OBJECT IDENTIFIER,
						parameters ANY DEFINED BY ALGORITHM OPTIONAL 
					}

	Signature := BIT STRING

	*/
	CSequence cseqCertificationReq;
	if(retVal == S_OK)
	{
		//Create the object identifier object for the sha1WithrsaEncryption(1.3.14.3.2.29) algorithm
		_bstr_t tbstrAlgObjId = "";
		switch(i_nHashAlg)
		{
		case HASH_SHA1 :
			tbstrAlgObjId = szOID_OIWSEC_sha1RSASign;
			break;

		case HASH_MD2:
			tbstrAlgObjId = szOID_RSA_MD2;
			break;

		case HASH_MD5:
			tbstrAlgObjId = szOID_RSA_MD5;
			break;
		}
		CObjectIdentifier cobjidAlgId(tbstrAlgObjId.length(), (PBYTE)(CHAR*)tbstrAlgObjId);

		CNull cnullObj;

		//Create the algorithm identifier sequence
		CBaseDERCollection cbdcAlgId = cobjidAlgId + cnullObj;
		CSequence cseqAlgId (cbdcAlgId);

		//create the certification request object - this is the final p10
		CBaseDERCollection cbdcCertificationReq;
		cbdcCertificationReq = cseqCertRequestInfo + cseqAlgId + cbsSignature;
		cseqCertificationReq = CSequence(cbdcCertificationReq);

#ifdef DEBUG

		//For debug only - store it in a file.
		FILE* fp;
		fp = (FILE*)fopen("temp.bin","wb");
		for(unsigned int i=0;i<cseqCertificationReq.BaseDERBlob->cbData; ++i)
		{
			fprintf(fp,"%c",cseqCertificationReq.BaseDERBlob->pbData[i]);
		}
		fclose(fp);
		
#endif
		//Base64 Encode the pkcs10
		DWORD dwB64P10Size;
		char* pszB64P10 = NULL;
		_Base64Encode((char*)(cseqCertificationReq.BaseDERBlob->pbData),cseqCertificationReq.BaseDERBlob->cbData,
			NULL,&dwB64P10Size);
		pszB64P10 = new char[dwB64P10Size+1];
		if(!pszB64P10)
			retVal = E_FAIL;
		else
		{
			_Base64Encode((char*)(cseqCertificationReq.BaseDERBlob->pbData),cseqCertificationReq.BaseDERBlob->cbData,
				pszB64P10,&dwB64P10Size);
			pszB64P10[dwB64P10Size] = '\0';
			*o_ptbstrCertReq = pszB64P10;
			delete[] pszB64P10;
		}
	}

	if(pbyteDataSequence)
		delete[] pbyteDataSequence;

	return retVal;
}

HRESULT CPtaEngine::Remember_PubKey_SmartCardKeyType_Assoc(CVirtualSmartCard* i_pVirtualSmartCard, DWORD i_dwKeyType, PBYTE i_pbytePubKeyIdentifier,DWORD i_dwPubKeyIdentifierHash)
{
	HRESULT retVal = S_OK;
	
	//Obtain the name of the smart card
	_bstr_t tbstrSmartCardName;

	if(retVal == S_OK)
	{
		VARIANT varProfName;
		if (dwIsTPM)
		{
			retVal = _gpVirtualSmartCard -> get_VSM_ProfileName (&varProfName);
		}
		else
		{
			retVal = i_pVirtualSmartCard->get_VSM_ProfileName(&varProfName);
		}

		if(retVal == S_OK)
		{
			tbstrSmartCardName = varProfName.bstrVal;
			SysFreeString(varProfName.bstrVal);
		}

	}

	/*Base64 encode the public key identifier*/
	_bstr_t tbstrB64EncodedPubKeyId;
	if(retVal == S_OK)
	{
		retVal = _GetB64EncodedPubKeyIdentifier(i_pbytePubKeyIdentifier, i_dwPubKeyIdentifierHash, &tbstrB64EncodedPubKeyId);
	}
	
	//Create an entry in the registry to associate the b64 encoded public key
	//and the name of the smart card
	if(retVal == S_OK)
	{
		HKEY hkPendingCertKey;
		_bstr_t tbstrPendingCertKey(PENDING_CERTS_REG_KEY);
		DWORD disp;

		tbstrPendingCertKey += tbstrB64EncodedPubKeyId;

		if(!RegCreateKeyEx(HKEY_CURRENT_USER,tbstrPendingCertKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hkPendingCertKey, &disp))
		{
			//Create a name value pair for the smart card name
			if(RegSetValueEx(hkPendingCertKey, (TCHAR*)SMARTCARD_NAME, NULL, REG_SZ, (PBYTE)(TCHAR*)tbstrSmartCardName, lstrlen((TCHAR*)tbstrSmartCardName)+1))
			{
				retVal = E_REGSETVALUEFAILED;
			}
			else
			{
				if(RegSetValueEx(hkPendingCertKey, (TCHAR*)KEYTYPE_NAME, NULL, REG_DWORD, (PBYTE)&i_dwKeyType, sizeof(DWORD)))
				{
					retVal = E_REGSETVALUEFAILED;
				}	
			}

			RegCloseKey(hkPendingCertKey);
		}
		else
		{
			retVal = E_REGCREATEKEYFAILED;
		}
	}

//	VSPTA_CLEAN_TBSTR(tbstrSmartCardName)
//	VSPTA_CLEAN_TBSTR(tbstrB64EncodedPubKeyId)

	return retVal;
}

HRESULT CPtaEngine::DecodePKCS7AndGetCerts(_bstr_t& i_tbstrB64EncPKCS7,PIDLISTNODE*	o_ppidCertList)
{
	HRESULT retVal = S_OK;
	
	/*Base64 decode the pkcs7*/
	PBYTE pbytePKCS7 = NULL;
	DWORD dwPKCS7Size;

	if(retVal == S_OK)
	{
		_Base64Decode(i_tbstrB64EncPKCS7,i_tbstrB64EncPKCS7.length(),NULL,&dwPKCS7Size);
		pbytePKCS7 = new BYTE[dwPKCS7Size];
		if(!pbytePKCS7)
			retVal = E_FAIL;
		else
		{
			_Base64Decode(i_tbstrB64EncPKCS7,i_tbstrB64EncPKCS7.length(),(char*)pbytePKCS7,&dwPKCS7Size);
		}
	}

	/*Now start decoding the pkcs7, to obtain the certificate blobs*/
	if(retVal == S_OK)
	{
		retVal = _GetCertsFromPKCS7(pbytePKCS7,dwPKCS7Size,o_ppidCertList);
	}

	/*Now decode each certificate blob into its components*/
	PIDLISTNODE pidListNodeCurr = *o_ppidCertList;
	while(pidListNodeCurr)
	{
		CCertInfo theCertInfo(pidListNodeCurr->pCertContext->pbCertEncoded, pidListNodeCurr->pCertContext->cbCertEncoded);
		pidListNodeCurr->pCertContext->pCertInfo = theCertInfo.GetCertInfo();
		pidListNodeCurr = pidListNodeCurr->pidlistnodeNext;
	}

	return retVal;
}

HRESULT CPtaEngine::GetPubKeyIdentifierFromPubKey(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, PBYTE o_pbytePublicKeyIdentifier,
												  DWORD* o_pdwPublicKeyIdentifierSize)
{
	HRESULT retVal = S_OK;

	*o_pdwPublicKeyIdentifierSize = VS_CSP_SHA1_LEN;
	if(!o_pbytePublicKeyIdentifier)
	{
		return S_OK;
	}

	A_RSA_KEY theKey;
	if(retVal == S_OK)
	{
		retVal = _GetRSAKeyFromKeyInfo(i_CertPublicKeyInfo, &theKey);
	}

	
	/*Now obtain the hash of the public key*/
	if(retVal == S_OK)
	{
		retVal = HashPublicKey(&theKey,o_pbytePublicKeyIdentifier);
	}

	/*Free memory*/
	delete[] theKey.modulus.data;
	delete[] theKey.exponent.data;

	return retVal;
}

HRESULT CPtaEngine::Restore_PubKey_SmartCardKeyType_Assoc(PBYTE i_pbytePublicKeyIdentifier,	DWORD i_dwPubKeyIdentifierSize, _bstr_t* o_ptbstrSmartCardName, DWORD* o_pdwKeyType)
{
	HRESULT retVal = S_OK;
	
	/*Base64 encode the public key identifier*/
	_bstr_t tbstrB64EncodedPubKeyId;
	if(retVal == S_OK)
	{
		retVal = _GetB64EncodedPubKeyIdentifier(i_pbytePublicKeyIdentifier, i_dwPubKeyIdentifierSize, &tbstrB64EncodedPubKeyId);
	}
	
	/*Obtain the smart card name associated with this pub key id from the registry*/
	if(retVal == S_OK)
	{
		HKEY hkPendingCertKey;
		_bstr_t tbstrPendingCertKey(PENDING_CERTS_REG_KEY);
		
		tbstrPendingCertKey += tbstrB64EncodedPubKeyId;

		if(RegOpenKeyEx(HKEY_CURRENT_USER,(TCHAR*)tbstrPendingCertKey,0,KEY_ALL_ACCESS, &hkPendingCertKey))
		{
			retVal = E_REGOPENKEYFAILED;
		}
		else
		{
			DWORD dwType = 0;
			DWORD dwSize = 0;
			PBYTE pbyteSmartCardName;

			/*Get the smart card name*/
			if(RegQueryValueEx(hkPendingCertKey,(TCHAR*)SMARTCARD_NAME,NULL,&dwType,NULL,&dwSize))
				retVal = E_REGQUERYVALFAILED;
			else
			{
				pbyteSmartCardName = new BYTE[dwSize];
				if(!pbyteSmartCardName)
					retVal = E_FAIL;
				else
				{
					if(RegQueryValueEx(hkPendingCertKey,(TCHAR*)SMARTCARD_NAME,NULL,&dwType,pbyteSmartCardName,&dwSize))
						retVal = E_REGQUERYVALFAILED;
					else
					{
						*o_ptbstrSmartCardName = (TCHAR*)pbyteSmartCardName;
					}

					delete[] pbyteSmartCardName;
				}

			}

			/*Get the key type*/
			if(retVal == S_OK)
			{
				dwType = REG_DWORD;
				dwSize = 4;
				if(RegQueryValueEx(hkPendingCertKey,(TCHAR*)KEYTYPE_NAME,NULL,&dwType,(PBYTE)o_pdwKeyType,&dwSize))
					retVal = E_REGQUERYVALFAILED;
			}

			RegCloseKey(hkPendingCertKey);

		}
	}

//	VSPTA_CLEAN_TBSTR(tbstrB64EncodedPubKeyId)

	return retVal;
}

HRESULT CPtaEngine::InstallCerts(CVirtualSmartCard* i_pVirtualSmartCard,
					PIDLISTNODE pidListCertsToInstall, unsigned int *o_pnCertNum)
{
	HRESULT retVal = S_OK;

	/*Install all the certs in the smart card*/
	BOOL boolDone = FALSE, bFirstCert = TRUE;
	PIDLISTNODE pidListNodeCurr = pidListCertsToInstall;
	_bstr_t tbstrPrefName = CERTPREF_STORE;
	_bstr_t tbstrPrefMY = "MY", tbstrPrefCA = "CA";

	do
	{
		VARIANT varCertToAdd;
		varCertToAdd.vt = VT_ARRAY;
		PBYTE pbyteCertToInstall;
		unsigned int nCertNum;
		
		if((varCertToAdd.parray = SafeArrayCreateVector(VT_UI1,0,pidListNodeCurr->pCertContext->cbCertEncoded)) == NULL)
			retVal = E_SAFEARRAYCREATEVECTFAILED;
		else
		{
			if(SafeArrayAccessData(varCertToAdd.parray,(void HUGEP **)&pbyteCertToInstall) != S_OK)
				retVal = E_SAFEARRAYACCDATAFAILED;
			else
			{
				memcpy(pbyteCertToInstall,pidListNodeCurr->pCertContext->pbCertEncoded,
										  pidListNodeCurr->pCertContext->cbCertEncoded);
				SafeArrayUnaccessData(varCertToAdd.parray);
				retVal = i_pVirtualSmartCard->VSM_AddCert(&varCertToAdd, &nCertNum);
				if(retVal == S_OK)
				{
					//If this is the first cert associate the "CertStore" cert pref with MY store
					//If it's not the first cert associate the "CertStore" cert pref with CA store
					if(bFirstCert)
					{
						retVal = i_pVirtualSmartCard->VSM_SetCertPref(nCertNum, tbstrPrefName, (PBYTE)(WCHAR*)tbstrPrefMY, (tbstrPrefMY.length()+1)*sizeof(WCHAR));
						*o_pnCertNum = nCertNum;
						bFirstCert = FALSE;
					}
					else
						retVal = i_pVirtualSmartCard->VSM_SetCertPref(nCertNum, tbstrPrefName, (PBYTE)(WCHAR*)tbstrPrefCA, (tbstrPrefCA.length()+1)*sizeof(WCHAR));
				}

				if(retVal == E_VS_CERT_ALREADY_EXISTS)
					retVal = S_OK;

				if(retVal == S_OK)
				{
					pidListNodeCurr = pidListNodeCurr->pidlistnodeNext;
					if(!pidListNodeCurr)
						boolDone = TRUE;
				}
				else
					boolDone = TRUE;
			}
			SafeArrayDestroy(varCertToAdd.parray);
		}
		
	}while(!boolDone);


	return retVal;
}

HRESULT CPtaEngine::Delete_PubKey_Assoc(PBYTE i_pbytePublicKeyIdentifier, DWORD i_dwPubKeyIdentifierSize)
{
	HRESULT retVal = S_OK;
	
	/*Base64 encode the public key identifier*/
	_bstr_t tbstrB64EncodedPubKeyId;
	if(retVal == S_OK)
	{
		retVal = _GetB64EncodedPubKeyIdentifier(i_pbytePublicKeyIdentifier, i_dwPubKeyIdentifierSize, &tbstrB64EncodedPubKeyId);
	}

	/*Delete this key from the registry*/
	if(retVal == S_OK)
	{
		_bstr_t tbstrPendingCertKey(PENDING_CERTS_REG_KEY);

		tbstrPendingCertKey += tbstrB64EncodedPubKeyId;

		if(RegDeleteKey(HKEY_CURRENT_USER,tbstrPendingCertKey))
			retVal = E_REGDELVALUEFAILED;
	}

//	VSPTA_CLEAN_TBSTR(tbstrB64EncodedPubKeyId)

	return retVal;
}

HRESULT CPtaEngine::_GetB64EncodedPubKeyIdentifier(PBYTE i_pbytePubKeyIdentifier, DWORD i_dwPubKeyIdentifierHash, _bstr_t* o_ptbstrB64EncodedPubKeyId)
{
	HRESULT retVal = S_OK;
	DWORD dwBase64EncodedPubKeySize;
	CHAR* pszBase64EncodedPubKey;

	_Base64Encode((char*)i_pbytePubKeyIdentifier,i_dwPubKeyIdentifierHash,NULL,&dwBase64EncodedPubKeySize);
	pszBase64EncodedPubKey = new CHAR[dwBase64EncodedPubKeySize+1];
	if(!pszBase64EncodedPubKey)
		retVal = E_FAIL;
	else
	{

		_Base64Encode((char*)i_pbytePubKeyIdentifier,i_dwPubKeyIdentifierHash,pszBase64EncodedPubKey,&dwBase64EncodedPubKeySize);
		pszBase64EncodedPubKey[dwBase64EncodedPubKeySize] = '\0';
		*o_ptbstrB64EncodedPubKeyId = pszBase64EncodedPubKey;
		delete[] pszBase64EncodedPubKey;
	}
	return retVal;

}

HRESULT CPtaEngine::_GetCertsFromPKCS7(PBYTE i_pbytePKCS7, DWORD i_dwPKCS7Size, PIDLISTNODE* o_ppidCertList)
{
	HRESULT retVal = S_OK;

#ifdef DEBUG
	FILE* fp;
	fp = (FILE*)fopen("tempinpkcs7.bin","wb");
	for(unsigned int i=0;i<i_dwPKCS7Size; ++i)
	{
		fprintf(fp,"%c",i_pbytePKCS7[i]);
	}
	fclose(fp);
#endif

	//Get the first certificate
	CBaseDERCollection cbdcThePKCS7(i_dwPKCS7Size,i_pbytePKCS7);
	CBaseDERHierarchy cbdhThePKCS7(cbdcThePKCS7);
	if ( 0 != cbdhThePKCS7.dwErrorCode )
	{
		retVal = E_FAIL;
	}

	DERTree* dtCert = NULL;

	if(retVal == S_OK)
	{
		dtCert = cbdhThePKCS7.m_DERTree.rightDERTree; //Now we are at the object identifier for signed data
		if(!dtCert)
			retVal = E_INVALIDPKCS7;

		
		if(retVal == S_OK)
		{
			dtCert = dtCert->nextDERTree; //Now we are at the [0] tag
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}

		if(retVal == S_OK)
		{
			dtCert = dtCert->rightDERTree; //Now we are the next sequence
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}

		
		if(retVal == S_OK)
		{
			dtCert = dtCert->rightDERTree; //Now we are the universal integer
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}

		
		if(retVal == S_OK)
		{
			dtCert = dtCert->nextDERTree; //Now we are the set
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}

		if(retVal == S_OK)
		{
			dtCert = dtCert->nextDERTree; //Now we are the sequence
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}
		
		if(retVal == S_OK)
		{
			dtCert = dtCert->nextDERTree; //Now we are the [0] tag
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}

		if(retVal == S_OK)
		{
			dtCert = dtCert->rightDERTree; //We are finally at the first certificate
			if(!dtCert)
				retVal = E_INVALIDPKCS7;
		}

		
		if(retVal == S_OK)
		{
			if(dtCert->currentBaseDER->Type != SEQUENCE)
			{
				retVal = E_INVALIDPKCS7;
			}
			else
			{
				*o_ppidCertList = (PIDLISTNODE)NewCert();
				(*o_ppidCertList)->pCertContext = (PCERT_CONTEXT)new(CERT_CONTEXT);
				(*o_ppidCertList)->pCertContext->cbCertEncoded = dtCert->currentBaseDER->BaseDERBlob->cbData;
				(*o_ppidCertList)->pCertContext->pbCertEncoded = new BYTE[(*o_ppidCertList)->pCertContext->cbCertEncoded];
				if(!((*o_ppidCertList)->pCertContext->pbCertEncoded))
					retVal = E_FAIL;
				else
				{
					memcpy((*o_ppidCertList)->pCertContext->pbCertEncoded, dtCert->currentBaseDER->BaseDERBlob->pbData, 
						(*o_ppidCertList)->pCertContext->cbCertEncoded);
				}
				(*o_ppidCertList)->pidlistnodeNext = NULL;

			}
				
		}
	}

	//Get subsequent certs till we've got the last one
	if(retVal == S_OK)
	{
		BOOL boolDone = FALSE;
		PIDLISTNODE pidCurrCertNode = (*o_ppidCertList);
	
		do
		{
			dtCert = dtCert->nextDERTree;
			if(!dtCert || (dtCert->currentBaseDER->cbData == 0))
			{
				boolDone = TRUE;
			}
			else
			{
				if(dtCert->currentBaseDER->Type != SEQUENCE)
				{
					retVal = E_INVALIDPKCS7;
				}
				else
				{
					pidCurrCertNode->pidlistnodeNext = (PIDLISTNODE)NewCert();
					pidCurrCertNode->pidlistnodeNext->pCertContext = (PCERT_CONTEXT)new(CERT_CONTEXT);
					pidCurrCertNode->pidlistnodeNext->pCertContext->cbCertEncoded = dtCert->currentBaseDER->BaseDERBlob->cbData;
					pidCurrCertNode->pidlistnodeNext->pCertContext->pbCertEncoded = new BYTE[pidCurrCertNode->pidlistnodeNext->pCertContext->cbCertEncoded];
					if(!(pidCurrCertNode->pidlistnodeNext->pCertContext->pbCertEncoded))
						retVal = E_FAIL;
					else
					{
						memcpy(pidCurrCertNode->pidlistnodeNext->pCertContext->pbCertEncoded, dtCert->currentBaseDER->BaseDERBlob->pbData, 
							pidCurrCertNode->pidlistnodeNext->pCertContext->cbCertEncoded);
					}
					pidCurrCertNode->pidlistnodeNext->pidlistnodeNext = NULL;
					pidCurrCertNode = pidCurrCertNode->pidlistnodeNext;
				}
			}
				
		}while(!boolDone);
	}

	return retVal;
}


HRESULT CPtaEngine::DeleteCertFromCAPI(PIDLISTNODE i_pidListCertsToDelete)
{
	HRESULT retVal = S_OK;
	
	/*Open the MY store*/ 
	HCERTSTORE hCertStoreMy = NULL;
	if(MSCapi_CertOpenSystemStore)
	{
		hCertStoreMy = MSCapi_CertOpenSystemStore(NULL,"MY");
		if(!hCertStoreMy)
			retVal = E_CERTOPENSYSSTOREFAILED;
	}
	else
	{
		//Capi is not available so we cannot delete certificate
		return retVal;
	}

	/*Now install the leaf cert in MY store*/
	PCCERT_CONTEXT pCertContextAddedCert = NULL;
	if(retVal == S_OK)
	{
		if(!MSCapi_CertAddEncodedCertificateToStore(hCertStoreMy,X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,              
			i_pidListCertsToDelete->pCertContext->pbCertEncoded,i_pidListCertsToDelete->pCertContext->cbCertEncoded,                   
			CERT_STORE_ADD_REPLACE_EXISTING,&pCertContextAddedCert))
		{
			retVal = E_ADDCERTTOSTOREFAILED; 
		}
	}

	if(retVal == S_OK)
	{
		if(!MSCapi_CertDeleteCertificateFromStore(pCertContextAddedCert))
		{
			retVal = E_DELETECERTFROMSTOREFAILED;
		}
	}
	
	if(hCertStoreMy)
	{
		MSCapi_CertCloseStore(hCertStoreMy,CERT_CLOSE_STORE_FORCE_FLAG);
	}

	return retVal;
}

//Begin Telia Bug Fix
//The following function is used to disable the enhanced key usages
//for the existing certs whose key usage is non repudiation
HRESULT CPtaEngine::DoDisableNRKeyUsage(SRCHCRIT &i_theSrchCrit, _bstr_t& i_tbstrAppCtxtName)
{

	HRESULT retVal = S_OK;

	PCCERT_CONTEXT pCertContext, pPrevCertContext;
	HCERTSTORE hCertStoreMy;
	_bstr_t tbstrAppCtxtName;
	_bstr_t tbstrPrefName;
	_bstr_t tbstrDefCertIssDN;
	CRYPT_DATA_BLOB enhKeyUsage;
	BYTE noUsageIdentifiers[] = {0x30, 0x00};

	hCertStoreMy = MSCapi_CertOpenSystemStore(NULL,"MY");


	if(hCertStoreMy)	{
	
		/*Enumerate the certs in the MY store*/
		pCertContext = MSCapi_CertEnumCertificatesInStore(hCertStoreMy,NULL);
		while (pCertContext) {
			PCERT_EXTENSION pExtension;
			BOOL bIsNonRepudiation = FALSE;

			if((pCertContext->pCertInfo) && 
				(pCertContext->pCertInfo->cExtension)) {

				if(retVal == S_OK)
				{
					tbstrPrefName = APPPREF_DEFCERTISSDN;

					/*Get the cert issuer dn*/
					retVal = _GetNameFromBlob(pCertContext->pCertInfo->Issuer, &tbstrDefCertIssDN);

					if(retVal != S_OK)
					{
						retVal = S_OK;
						tbstrDefCertIssDN = "";
					}
				}

				if(retVal == S_OK)
				{
					retVal = _CheckIfDNGood(tbstrDefCertIssDN, i_theSrchCrit.tbstrIssuerDN);
				}


				if (retVal != S_OK) {
					retVal = S_OK;
					pPrevCertContext = pCertContext;
					pCertContext = MSCapi_CertEnumCertificatesInStore(hCertStoreMy, pPrevCertContext);		

					// Does not match issuer DN. Go to the next cert.
					continue;
				}
				pExtension = CertFindExtension(szOID_KEY_USAGE, 
					pCertContext->pCertInfo->cExtension,  
					pCertContext->pCertInfo->rgExtension);

				if(pExtension && (pExtension->Value.cbData == 4)) {
					if(pExtension->Value.pbData[3] == 0x40)
						bIsNonRepudiation = TRUE;
				}
			}
			if(bIsNonRepudiation) {
				enhKeyUsage.pbData = noUsageIdentifiers;
				enhKeyUsage.cbData = sizeof(noUsageIdentifiers);
				if(!MSCapi_CertSetCertificateContextProperty(pCertContext, CERT_ENHKEY_USAGE_PROP_ID, 0,&enhKeyUsage)) {
					retVal = E_SETPROPFAILED;
				}
			}


			pPrevCertContext = pCertContext;
			pCertContext = MSCapi_CertEnumCertificatesInStore(hCertStoreMy, pPrevCertContext);		
		}

	}



	if(hCertStoreMy)
	{
		MSCapi_CertCloseStore(hCertStoreMy,CERT_CLOSE_STORE_FORCE_FLAG);
	}


	return retVal;

}
//End Telia Bug Fix

HRESULT CPtaEngine::MakeCapiCompliantCertInstall(CVirtualSmartCard* i_pVirtualSmartCard,
					PIDLISTNODE i_pidListCertsToInstall, PBYTE i_pbytePublicKeyId,
					DWORD i_dwPublicKeyIdSize, BYTE i_byteInstallKeyType, BOOL i_boolIsKeyExportable,
					BOOL i_boolIsRoamProfile, _bstr_t& i_ptbstrClientInfo, _bstr_t& i_ptbstrClientInfoSig,
					int nCertNum, _bstr_t& i_ptbstrContainerName)
{
	HRESULT retVal = S_OK;

	_bstr_t tbstrContainerName = "";
	_bstr_t	tbstrCSPName = "";
	_bstr_t tbstrBackupName = "";
	DWORD	dwContainerNameLen = 0;
	RPC_STATUS	rpcStatus		=	0;
	DWORD	dwRegKeyLen = 0;

	UUID uuid;
	unsigned char* pszUuid;
        //Begin Telia Bug Fix
        BYTE noUsageIdentifiers[] = {0x30, 0x00};
	CRYPT_DATA_BLOB enhKeyUsage;
        //End Telia Bug Fix
	
	/*Open the MY store*/ 
	HCERTSTORE hCertStoreMy = NULL;
	if(MSCapi_CertOpenSystemStore)
	{
		hCertStoreMy = MSCapi_CertOpenSystemStore(NULL,"MY");
		if(!hCertStoreMy)
			retVal = E_CERTOPENSYSSTOREFAILED;
	}
	else
	{
		//Capi is not available so we dont have to make any capi compliant cert install
		return retVal;
	}

	/*Now install the leaf cert in MY store and associate it with this 
	container name*/
	PCCERT_CONTEXT pCertContextAddedCert =	NULL;
	if(retVal == S_OK)
	{
		if(!MSCapi_CertAddEncodedCertificateToStore(hCertStoreMy,X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,              
			i_pidListCertsToInstall->pCertContext->pbCertEncoded,i_pidListCertsToInstall->pCertContext->cbCertEncoded,                   
			CERT_STORE_ADD_NEW,&pCertContextAddedCert))
		{
			DWORD dwLastErr = GetLastError();
			if(dwLastErr == CRYPT_E_EXISTS)
				retVal = E_CERTEXISTS;
			else
			{
				retVal = E_ADDCERTTOSTOREFAILED; 
			}
		}
	}

	/*Associate the container name and the verisign csp with this cert*/
	if(retVal == S_OK)
	{
		CRYPT_KEY_PROV_INFO theKeyProvInfo;

		if ( dwIsTPM )
		{

			if ( 0 == i_ptbstrContainerName.length () )
			{
				return	E_INVALIDARG;
			}

			tbstrContainerName = i_ptbstrContainerName.copy();
			tbstrCSPName = _bstr_t(VS_TPM_CSP_NAME);

			if ( NULL == _gpVirtualSmartCard )
			{
				_gpVirtualSmartCard = new CVirtualSmartCard;

				retVal =	_gpVirtualSmartCard -> VSM_TPMInitialize
							(
								tbstrContainerName,
								VS_TPM_CONTAINER_OPEN,
								m_PTA
							);
				if ( S_OK != retVal )
				{
					return	retVal;
				}
			}

		}
		else
		{
			if(nCertNum != -1)
			{
				//Get a key container name only first time
				rpcStatus =	UuidCreate(&uuid);
				if ( RPC_S_OK != rpcStatus )
				{
					return	E_FAIL;
				}

				rpcStatus =	UuidToString(&uuid,&pszUuid);
				if ( RPC_S_OK != rpcStatus )
				{
					return	E_FAIL;
				}

				tbstrContainerName = (char*)pszUuid;
				tbstrBackupName = tbstrContainerName.copy ();
				RpcStringFreeA(&pszUuid);

				dwContainerNameLen = tbstrContainerName.length ();
				if ( 0 == dwContainerNameLen )
				{
					return	E_FAIL;
				}

				// Store info in smartcard only if this information is added
				// first time. For roaming profile do not add this info again
				// and again. This information associates the container name 
				// with the hash of the public key and its type
				CSP_Key_Container theKeyContainer;
				_bstr_t tbstrPrefName = CERTPREF_CONTAINER_NAME;
				if(i_byteInstallKeyType & KEY_SIGNATURE)
				{
					theKeyContainer.structSign.dwExists = VS_CSP_KEY_EXISTS;
					memcpy(theKeyContainer.structSign.pbytePubKeyHash,i_pbytePublicKeyId,i_dwPublicKeyIdSize);
					theKeyContainer.structSign.dwExportable = i_boolIsKeyExportable;
				}
				if(i_byteInstallKeyType & KEY_ENCRYPTION)
				{
					theKeyContainer.structXchg.dwExists = VS_CSP_KEY_EXISTS;
					memcpy(theKeyContainer.structXchg.pbytePubKeyHash,i_pbytePublicKeyId,i_dwPublicKeyIdSize);
					theKeyContainer.structXchg.dwExportable = i_boolIsKeyExportable;
				}
				
				if ( 0 == tbstrContainerName.length () )
				{
					tbstrContainerName = tbstrBackupName.copy ();
				}

				retVal =	i_pVirtualSmartCard -> VSM_SetInformationBlob
										(
											tbstrContainerName,
											(const unsigned char*) &theKeyContainer,
											(unsigned int) sizeof (CSP_Key_Container)
										);

				// Store the container name as a cert pref. This is needed
				// so that for roaming we can use this container name
				// pref to goto the container and get required info. This
				// provides a mapping from a certificate to a container name
				retVal = i_pVirtualSmartCard->VSM_SetCertPref(nCertNum, tbstrPrefName, (PBYTE)(WCHAR*)tbstrContainerName,
											(tbstrContainerName.length()+1)*sizeof(WCHAR));
			}
			else
			{
				if ( 0 == i_ptbstrContainerName.length () )
				{
					return	E_INVALIDARG;
				}

				// Use container name passed to us. This is the container
				// name which was set in the Profile
				tbstrContainerName = i_ptbstrContainerName.copy();
				tbstrBackupName = tbstrContainerName.copy ();
			}

			tbstrCSPName	= _bstr_t(CSP_NAME);
		}
	
		theKeyProvInfo.pwszContainerName = tbstrContainerName;
		theKeyProvInfo.pwszProvName =	tbstrCSPName;
		
		theKeyProvInfo.dwProvType = PROV_RSA_FULL;
		if(i_byteInstallKeyType & KEY_SIGNATURE)
			theKeyProvInfo.dwKeySpec = AT_SIGNATURE;
		if(i_byteInstallKeyType & KEY_ENCRYPTION)
			theKeyProvInfo.dwKeySpec = AT_KEYEXCHANGE;
		theKeyProvInfo.dwFlags = CERT_SET_KEY_PROV_HANDLE_PROP_ID;
		theKeyProvInfo.cProvParam = 0;
		theKeyProvInfo.rgProvParam = NULL;

		if(!MSCapi_CertSetCertificateContextProperty(pCertContextAddedCert, CERT_KEY_PROV_INFO_PROP_ID,0,(PVOID)&theKeyProvInfo))
		{
			retVal = E_SETPROPFAILED;
		}

                //Begin Telia Bug Fix : The following disables the 
                //enhanced key usage if the key usage is non repudiation
		PCERT_EXTENSION pExtension;
		BOOL bIsNonRepudiation = FALSE;

		if((pCertContextAddedCert->pCertInfo) && 
			(pCertContextAddedCert->pCertInfo->cExtension)) {

			pExtension = CertFindExtension(szOID_KEY_USAGE, 
				pCertContextAddedCert->pCertInfo->cExtension,  
				pCertContextAddedCert->pCertInfo->rgExtension);

			if(pExtension && (pExtension->Value.cbData == 4)) {
				if(pExtension->Value.pbData[3] == 0x40)
					bIsNonRepudiation = TRUE;
			}
		}
		if((bIsNonRepudiation) || (theKeyProvInfo.dwKeySpec == AT_SIGNATURE)) {
			enhKeyUsage.pbData = noUsageIdentifiers;
			enhKeyUsage.cbData = sizeof(noUsageIdentifiers);
			if(!MSCapi_CertSetCertificateContextProperty(pCertContextAddedCert, CERT_ENHKEY_USAGE_PROP_ID, 0,&enhKeyUsage)) {
				retVal = E_SETPROPFAILED;
			}
		}
                //End Telia Bug Fix
	}

	/*Free the cert context and close the store*/
	if(retVal == S_OK || pCertContextAddedCert)
	{	
		MSCapi_CertFreeCertitificateContext(pCertContextAddedCert);
	}

	if(hCertStoreMy)
	{
		MSCapi_CertCloseStore(hCertStoreMy,CERT_CLOSE_STORE_FORCE_FLAG);
	}


	if ( !dwIsTPM )
	{
		//Obtain the name of the smart card
		_bstr_t tbstrSmartCardName;
		if(retVal == S_OK)
		{
			VARIANT varProfName;
			retVal = i_pVirtualSmartCard->get_VSM_ProfileName(&varProfName);
			if(retVal == S_OK)
			{
				tbstrSmartCardName = varProfName.bstrVal;
				SysFreeString(varProfName.bstrVal);
			}
		}

		/*Create entries in the registry associating this container and the profile name*/
		if(retVal == S_OK)
		{
			HKEY hkVeriSignCryptoKey;
			_bstr_t tbstrVeriSignCryptoKey(VS_CRYPTO_REG_KEY);
			DWORD disp;
			
			if ( 0 == tbstrContainerName.length () )
			{
				tbstrContainerName = tbstrBackupName.copy ();
			}

			dwRegKeyLen = tbstrVeriSignCryptoKey.length ();

			tbstrVeriSignCryptoKey += tbstrContainerName;
			tbstrVeriSignCryptoKey += "\\";

			if ( dwRegKeyLen == tbstrVeriSignCryptoKey.length () )
			{
				return	E_FAIL;
			}

			if(!RegCreateKeyEx(HKEY_CURRENT_USER,tbstrVeriSignCryptoKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hkVeriSignCryptoKey, &disp))
			{
				//Create a name value pair
				if(RegSetValueEx(hkVeriSignCryptoKey, (TCHAR*)PROFILE_NAME, NULL, REG_SZ, (PBYTE)(TCHAR*)tbstrSmartCardName, lstrlen((TCHAR*)tbstrSmartCardName)+1))
				{
					retVal = E_REGSETVALUEFAILED;
				}
				else
				{
					// Set the profile type
					DWORD dwProfileType = i_boolIsRoamProfile;
					if(dwProfileType != 0)
						dwProfileType = 1;

					if(RegSetValueEx(hkVeriSignCryptoKey, (TCHAR*)PROFILE_TYPE, NULL, REG_DWORD, (PBYTE)&dwProfileType, sizeof(DWORD)))
					{
						retVal = E_REGSETVALUEFAILED;
					}
					else
					{	// For roaming profile set the roaming preferences
						if(i_boolIsRoamProfile)
						{
							// Roaming preferences
							if(RegSetValueEx(hkVeriSignCryptoKey, (TCHAR*)CLIENT_INFO, NULL, REG_SZ, (PBYTE)(TCHAR*)i_ptbstrClientInfo, lstrlen((TCHAR*)i_ptbstrClientInfo)+1))
							{
								retVal = E_REGSETVALUEFAILED;
							}
							else
							{
								if(RegSetValueEx(hkVeriSignCryptoKey, (TCHAR*)CLIENT_INFO_SIG, NULL, REG_SZ, (PBYTE)(TCHAR*)i_ptbstrClientInfoSig, lstrlen((TCHAR*)i_ptbstrClientInfoSig)+1))
								{
									retVal = E_REGSETVALUEFAILED;
								}
							}
						}
					}
					
					RegCloseKey(hkVeriSignCryptoKey);
				}
			}
			else
			{
				retVal = E_REGCREATEKEYFAILED;
			}
		}
	}

	if(retVal == E_CERTEXISTS)
		retVal = S_OK;


	/*Install the other certs in the intermediat store*/	
	HCERTSTORE hCertStoreCA = NULL;
	if(retVal == S_OK)
	{
		hCertStoreCA = MSCapi_CertOpenSystemStore(NULL,"CA");
		if(!hCertStoreCA)
			retVal = E_CERTOPENSYSSTOREFAILED;
	}

	if(retVal == S_OK)
	{
		PIDLISTNODE pidListNodeCurr = i_pidListCertsToInstall->pidlistnodeNext;
		while(pidListNodeCurr)
		{
			if(!MSCapi_CertAddEncodedCertificateToStore(hCertStoreCA,X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,              
				pidListNodeCurr->pCertContext->pbCertEncoded,pidListNodeCurr->pCertContext->cbCertEncoded,                   
				CERT_STORE_ADD_NEW,NULL))
			{
				DWORD dwLastErr = GetLastError();
				if(dwLastErr == CRYPT_E_EXISTS)
					retVal = S_OK;
				else
				{
					retVal = E_ADDCERTTOSTOREFAILED;
				}
			}
			if(retVal == S_OK)
			{
				pidListNodeCurr = pidListNodeCurr->pidlistnodeNext;
			}
			else 
				pidListNodeCurr = NULL;
		}

		MSCapi_CertCloseStore(hCertStoreCA,CERT_CLOSE_STORE_FORCE_FLAG);
	}
	
//	VSPTA_CLEAN_TBSTR(tbstrContainerName)
//	VSPTA_CLEAN_TBSTR(tbstrSmartCardName)

	return retVal;
}

HRESULT CPtaEngine::_GetCertsFromVSCapi(CVirtualSmartCard* i_pvarVirtualSmartCard, PIDLISTNODE* o_pCertsInStore)
{
	HRESULT retVal = S_OK;
	PBYTE pbyteCertBlob = NULL;
	BOOL boolDone = FALSE;
	int nCertNum = 0;
	PIDLISTNODE pidListNodeCurr = NULL;
	PIDLISTNODE pidListNode = NULL;
	
	/*Till we've found the last cert*/
	do
	{
		pidListNode = NewCert();
		pidListNode->pCertContext = new CERT_CONTEXT;

		/*Obtain cert blobs from the smart card*/
		retVal = i_pvarVirtualSmartCard->VSM_GetCert(nCertNum, NULL, &(pidListNode->pCertContext->cbCertEncoded));
		if(retVal == S_OK)
		{
			pidListNode->pCertContext->pbCertEncoded = new BYTE[pidListNode->pCertContext->cbCertEncoded];
			retVal = i_pvarVirtualSmartCard->VSM_GetCert(nCertNum, pidListNode->pCertContext->pbCertEncoded, &(pidListNode->pCertContext->cbCertEncoded));

			/*Create a cert info from this cert blob*/
			CCertInfo theCertInfo(pidListNode->pCertContext->pbCertEncoded,pidListNode->pCertContext->cbCertEncoded);
			pidListNode->pCertContext->pCertInfo = theCertInfo.GetCertInfo();
			if(pidListNodeCurr)
			{
				pidListNodeCurr->pidlistnodeNext = pidListNode;
				pidListNode = NULL;
				pidListNodeCurr = pidListNodeCurr->pidlistnodeNext;
				pidListNodeCurr->pidlistnodeNext = NULL;
			}
			else
			{
				*o_pCertsInStore = pidListNode;
				pidListNodeCurr = *o_pCertsInStore;
				pidListNodeCurr->pidlistnodeNext = NULL;
			}

			nCertNum++;
		}
		else if (retVal == E_CERTNOTFOUND)
		{
			delete[] pidListNode->pCertContext;
			delete[] pidListNode;
			boolDone = TRUE;
			if(!nCertNum)//No certs have been found
				retVal = E_CERTNOTFOUND;
			else
				retVal = S_OK;
		}
		else
		{
			boolDone = TRUE;
		}
		
	}while (!boolDone);
	return retVal;
}

HRESULT CPtaEngine::_GetCertsFromMSCapi(PIDLISTNODE* o_pCertsInStore)
{
	HRESULT retVal = S_OK;
	PCCERT_CONTEXT pCertContext, pPrevCertContext;
	PIDLISTNODE pidListNodeCurr = NULL;
	PIDLISTNODE pidListNode = NULL;

	do
	{
		/*Open the cert store*/
		if(!m_hLocalCertStore)
			m_hLocalCertStore = MSCapi_CertOpenSystemStore(NULL,"MY");
		if(!m_hLocalCertStore)
		{
			retVal = E_CERTOPENSYSSTOREFAILED;
			break;
		}

		/*Enumerate the certs in the MY store*/
		pCertContext = MSCapi_CertEnumCertificatesInStore(m_hLocalCertStore,NULL);
		if(!pCertContext)
		{
			retVal = E_CERTNOTFOUND;
			break;
		}

		*o_pCertsInStore = 	NewCert();			
		(*o_pCertsInStore)->pCertContext = (PCERT_CONTEXT)PtaCapi_CertDuplicateCertificateContext(pCertContext);
		(*o_pCertsInStore)->pidlistnodeNext = NULL;
		pidListNode = *o_pCertsInStore;

		while(pCertContext != NULL && retVal == S_OK)
		{	
			pPrevCertContext = pCertContext;
			pCertContext = MSCapi_CertEnumCertificatesInStore(m_hLocalCertStore, pPrevCertContext);		
			if(pCertContext)
			{
				pidListNode->pidlistnodeNext = 	NewCert();			
				pidListNode->pidlistnodeNext->pCertContext = (PCERT_CONTEXT)PtaCapi_CertDuplicateCertificateContext(pCertContext);
				pidListNode->pidlistnodeNext->pidlistnodeNext = NULL;
				pidListNode = pidListNode->pidlistnodeNext;
			}

		}

	}while(0);

	
	return retVal;
}

HRESULT CPtaEngine::_GetDecCertInfo(PIDLISTNODE io_pCertList)
{
	HRESULT retVal = S_OK;
	BOOL boolDone = FALSE;
	PIDLISTNODE pCurrNode;

	pCurrNode = io_pCertList;
	do
	{
		pCurrNode->pDecCertInfo = new DECCERT_INFO;
		retVal = _DecodeCertInfo(pCurrNode->pCertContext,pCurrNode->pDecCertInfo);

		if(retVal != S_OK)
		{
			delete pCurrNode->pDecCertInfo;
			boolDone = TRUE;
		}
			
		pCurrNode = pCurrNode->pidlistnodeNext;
		if(!pCurrNode)
			boolDone = TRUE;

	}while(!boolDone);
	return retVal;
}

HRESULT CPtaEngine::_DecodeCertInfo(PCERT_CONTEXT i_pCertContext, PDECCERT_INFO io_pDecCertInfo)
{
	HRESULT retVal = S_OK;

	/*Get the cert issuer dn*/
	retVal = _GetNameFromBlob(i_pCertContext->pCertInfo->Issuer, &io_pDecCertInfo->tbstrIssuerDN);

	/*Get the cert subject dn*/
	if(retVal == S_OK)
	{
		retVal = _GetNameFromBlob(i_pCertContext->pCertInfo->Subject, &io_pDecCertInfo->tbstrSubjectDN);
	}

	/*Get the cert serial number*/
	if(retVal == S_OK)
	{
		retVal = _GetCertSerNum(i_pCertContext->pCertInfo->SerialNumber, &io_pDecCertInfo->tbstrSerNum);
	}

	/*Get the key size*/
	if(retVal == S_OK)
	{
		A_RSA_KEY theRSAKey;
		retVal = _GetRSAKeyFromKeyInfo(i_pCertContext->pCertInfo->SubjectPublicKeyInfo,&theRSAKey);
		if(retVal == S_OK)
		{
			io_pDecCertInfo->nKeySize = theRSAKey.modulus.len * 8; //in bits
		}
		delete[] theRSAKey.modulus.data;
		delete[] theRSAKey.exponent.data;
	}

	/* Get the key usage */
	if(retVal == S_OK)
	{
		io_pDecCertInfo->nKeyUsage = 0;
		for(int i=0;i<i_pCertContext->pCertInfo->cExtension;++i)
		{
			
			if(!lstrcmp(i_pCertContext->pCertInfo->rgExtension[i].pszObjId, _T("2.5.29.15")))
			{
				if(i_pCertContext->pCertInfo->rgExtension[i].Value.cbData == 4)
				{
					io_pDecCertInfo->nKeyUsage = i_pCertContext->pCertInfo->rgExtension[i].Value.pbData[3];
				}
			}
		}
	}


	/*Get the cert effective*/
	if(retVal == S_OK)
	{
		retVal = _GetDateFromFileTime(i_pCertContext->pCertInfo->NotBefore, &io_pDecCertInfo->dateEffDate);
	}

	/*Get the cert expiration date*/
	if(retVal == S_OK)
	{
		retVal = _GetDateFromFileTime(i_pCertContext->pCertInfo->NotAfter, &io_pDecCertInfo->dateExpDate);
	}

	return retVal;
}


HRESULT CPtaEngine::_GetNameFromBlob(CERT_NAME_BLOB& i_TheNameBlob, _bstr_t* o_ptbstrName)
{
	HRESULT retVal = S_OK;
	DWORD   dwSize = NULL;
	TCHAR*	tstrName = NULL;

    dwSize = MyCertNameToStr(MY_ENCODING_TYPE, &i_TheNameBlob, 
							 CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, NULL, dwSize);

    if(dwSize <= 1)		// This function always returns a null char (0), so the minimum count returned will 
						// be 1, even if nothing got converted
        return E_CERTNAMETOSTRFAILED;

	// Allocate memory for the returned string
    tstrName = new TCHAR[dwSize+1];
    if(!(tstrName))
		return E_FAIL;

    dwSize = MyCertNameToStr(MY_ENCODING_TYPE, &i_TheNameBlob,
						     CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, tstrName, dwSize);              // Size of string (chars)

    if(dwSize <= 1)
        retVal =  E_CERTNAMETOSTRFAILED;

	if(retVal == S_OK)
		*o_ptbstrName = tstrName;
	else
		*o_ptbstrName = "";

	delete[] tstrName;

	return retVal;
}


HRESULT CPtaEngine::_GetCertSerNum(CRYPT_INTEGER_BLOB& i_SerialNumber, _bstr_t* o_ptbstrSerNum)
{
	DWORD				dwSerialNumber = NULL;
	PBYTE				SerialNumber = NULL;
	HRESULT				retVal = S_OK;
	TCHAR*				tstrSerNum = NULL;

    
	dwSerialNumber = i_SerialNumber.cbData;
	
	if((SerialNumber = new BYTE[dwSerialNumber]) == NULL)
	{
		retVal = E_FAIL;
	}
	else
	{
		//Reverse the bytes
		unsigned int i ;
		for ( i = 0 ; i < dwSerialNumber ; i++ )
			SerialNumber[dwSerialNumber-1-i] = (i_SerialNumber.pbData)[i] ;

		if((tstrSerNum = new TCHAR[(dwSerialNumber*2)+1]) == NULL)
		{
			retVal = E_FAIL;
		}
		else
		{
			_bstr_t temp("%02x");

			for ( i = 0 ; i < dwSerialNumber ; i++ )
			{
				wsprintf((tstrSerNum)+(i*2), (TCHAR*)temp, (unsigned char)SerialNumber[i]) ;
			}
			
			*o_ptbstrSerNum = tstrSerNum;
			delete[] tstrSerNum;

		}

		delete[] SerialNumber;
	}
	return retVal;
}

HRESULT CPtaEngine::_GetDateFromFileTime(FILETIME& i_ftTheFileTime, DATE* o_pDate)
{
	HRESULT retVal = S_OK;

	DWORD			dwNotAfter = NULL;
	SYSTEMTIME      stSysTime;


	if(!FileTimeToSystemTime(&i_ftTheFileTime,&stSysTime))
	{
		retVal = E_FILETIMETOSYSTIMEFAILED;
	}
	else
	{
		if(!SystemTimeToVariantTime(&stSysTime,o_pDate))
		{
			retVal = E_SYSTIMETOVARTIMEFAILED;
		}
	}

	return retVal;
}

HRESULT CPtaEngine::_FilterCertList(CVirtualSmartCard* i_pVirtualSmartCard, PIDLISTNODE pCertList, SRCHCRIT& i_theSrchCrit, PIDLISTNODE* o_ppMatchingCertList)
{
	HRESULT retVal = S_OK;
	PIDLISTNODE pCurrInNode = pCertList;
	PIDLISTNODE pCurrOutNode = NULL;
	BOOL boolExpiredMatchingCertPresent = FALSE;
	PIDLISTNODE pTmpNode;
	BOOL boolDefaultFound = FALSE;

	*o_ppMatchingCertList = NULL;

	//For debug only
	//Copy the inputted cerlist into the matching cert list
	while(pCurrInNode)
	{
		retVal = _DoesCertMatchSrchCrit(i_pVirtualSmartCard, pCurrInNode,i_theSrchCrit);
		if(retVal == S_OK)
		{
			if(pCurrInNode->pAuxCertInfo->boolIsDef)
			{
				boolDefaultFound = TRUE;
			}

			if(*o_ppMatchingCertList)
			{
				//If this cert is a default cert then add it to the start of the list.
				if(pCurrInNode->pAuxCertInfo->boolIsDef)
				{
					pTmpNode = *o_ppMatchingCertList;
					*o_ppMatchingCertList = CopyCert(pCurrInNode);
					(*o_ppMatchingCertList)->pidlistnodeNext = pTmpNode;
				}
				else //add it to the end of the list
				{
					pCurrOutNode->pidlistnodeNext = CopyCert(pCurrInNode);
					pCurrOutNode = pCurrOutNode->pidlistnodeNext;
				}
			}
			else
			{
				*o_ppMatchingCertList = CopyCert(pCurrInNode);
				pCurrOutNode = *o_ppMatchingCertList;
			}
			pCurrOutNode->pidlistnodeNext = NULL;
		}
		else if(retVal == E_CERTNOMATCHCRIT)
		{
			retVal = S_OK;
		}
		else if(retVal == E_CERTMATCHBUTEXP)
		{
			boolExpiredMatchingCertPresent = TRUE;
			retVal = S_OK;
		}
		else if(retVal == E_DNPARSEERR)
		{
			retVal = S_OK;
		}
		else
		{
			if(*o_ppMatchingCertList)
			{
				FreeIdList(*o_ppMatchingCertList); 
				*o_ppMatchingCertList = NULL;
			}
			break;
		}

		pCurrInNode = pCurrInNode->pidlistnodeNext;
	}
	
	if(retVal == S_OK)
	{
		if(!(*o_ppMatchingCertList) && (boolExpiredMatchingCertPresent))
			retVal = E_CERTMATCHBUTEXP;
		else if(!(*o_ppMatchingCertList))
			retVal = E_CERTNOTFOUND;
		else
		{
			//We have a list - if we want only the default cert then truncate that list to the first one.
			if(i_theSrchCrit.boolUseDefault && boolDefaultFound)
			{
				if((*o_ppMatchingCertList)->pidlistnodeNext)
				{
					FreeIdList((*o_ppMatchingCertList)->pidlistnodeNext);
					(*o_ppMatchingCertList)->pidlistnodeNext = NULL;
				}
			}
		}
	}

	return retVal;
}

PIDLISTNODE CPtaEngine::NewCert()
{
	PIDLISTNODE newCert;
	newCert = new (IDLISTNODE);
	newCert->pAuxCertInfo = NULL;
	newCert->pCertContext = NULL;
	newCert->pDecCertInfo = NULL;
	newCert->pidlistnodeNext = NULL;

	return newCert;
}

HRESULT CPtaEngine::_GetRSAKeyFromKeyInfo(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, A_RSA_KEY* o_pTheKey)
{
	HRESULT retVal = S_OK;

	o_pTheKey->modulus.data = o_pTheKey->exponent.data = NULL;
	
	CBaseDERCollection cbdcTheKeySeq(i_CertPublicKeyInfo.PublicKey.cbData, i_CertPublicKeyInfo.PublicKey.pbData);
	CBaseDERHierarchy cbdhTheKeySeq(cbdcTheKeySeq);
	if ( 0 == cbdhTheKeySeq.dwErrorCode )
	{
		DERTree* pdtTheKeySeq = &cbdhTheKeySeq.m_DERTree;
		if(!pdtTheKeySeq && pdtTheKeySeq->currentBaseDER->Type != SEQUENCE)
		{
			retVal = E_INVALIDASNKEYENC;
		}
		else
		{
			/*Get the modulus*/
			DERTree* pdtTheMod = pdtTheKeySeq->rightDERTree;
			if(!pdtTheMod && pdtTheMod->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				retVal = E_INVALIDASNKEYENC;
			}
			else
			{
				PBYTE pbyteRawData;

				o_pTheKey->modulus.len = pdtTheMod->currentBaseDER->cbData;
				o_pTheKey->modulus.data = new BYTE[o_pTheKey->modulus.len];

				pbyteRawData = pdtTheMod->currentBaseDER->BaseDERBlob->pbData + 
										(pdtTheMod->currentBaseDER->BaseDERBlob->cbData - pdtTheMod->currentBaseDER->cbData);

				if(*pbyteRawData)
					memcpy(o_pTheKey->modulus.data, pbyteRawData,o_pTheKey->modulus.len);
				else if(o_pTheKey->modulus.len > 1)
				{
					o_pTheKey->modulus.len --;
					memcpy(o_pTheKey->modulus.data, pbyteRawData+1,o_pTheKey->modulus.len);
				}
				else
					retVal = E_INVALIDASNKEYENC;

			}

			/*Get the exponent*/
			DERTree* pdtTheExp;
			if(retVal == S_OK)
			{
				pdtTheExp = pdtTheMod->nextDERTree;
				if(!pdtTheExp && pdtTheExp->currentBaseDER->Type != UNIVERSAL_INTEGER)
				{
					retVal = E_INVALIDASNKEYENC;
				}
				else
				{
					PBYTE pbyteRawData;

					o_pTheKey->exponent.len = pdtTheExp->currentBaseDER->cbData;
					o_pTheKey->exponent.data = new BYTE[o_pTheKey->exponent.len];

					pbyteRawData = pdtTheExp->currentBaseDER->BaseDERBlob->pbData + 
										(pdtTheExp->currentBaseDER->BaseDERBlob->cbData - pdtTheExp->currentBaseDER->cbData);
					if(*pbyteRawData)
						memcpy(o_pTheKey->exponent.data, pbyteRawData,o_pTheKey->exponent.len);
					else if(o_pTheKey->exponent.len > 1)
					{
						o_pTheKey->exponent.len --;
						memcpy(o_pTheKey->exponent.data, pbyteRawData+1,o_pTheKey->exponent.len);
					}
					else
						retVal = E_INVALIDASNKEYENC;
				}

			}
		}
	}
	else
	{
		retVal = E_FAIL;
	}

	return retVal;
}

HRESULT CPtaEngine::_GetAuxCertInfo(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrAppCtxtName, PIDLISTNODE io_pCertList)
{
	HRESULT retVal = S_OK;
	PIDLISTNODE pCurrNode = io_pCertList;
	int nCertNum = 0;
	_bstr_t tbstrPrefName = "";
	_bstr_t tbstrRenewedFlagString = "";
	_bstr_t tbstrPubKeyId = "";
	_bstr_t tbstrDefCertIssDN = "";
	_bstr_t tbstrDefCertSerNum = "";
//	_bstr_t tbstrDefCertIssDN = "";
//	_bstr_t tbstrDefCertSerNum = "";

	bool	bResult	=	FALSE;
	DWORD	cbData	=	0;
	CRYPT_KEY_PROV_INFO* pCryptKeyProvInfo	=	NULL;

	while(pCurrNode)
	{
		pCurrNode->pAuxCertInfo = new AUXCERT_INFO;
		if(!pCurrNode->pAuxCertInfo)
			retVal = E_FAIL;
		else
		{
			
			pCurrNode->pAuxCertInfo->boolRenewed = FALSE;
			pCurrNode->pAuxCertInfo->tbstrDispString = "";
			pCurrNode->pAuxCertInfo->tbstrFrndlyName = "";
			pCurrNode->pAuxCertInfo->tbstrLogoUrl = "";
			pCurrNode->pAuxCertInfo->tbstrTextureUrl = "";
			pCurrNode->pAuxCertInfo->tbstrContainerName = "";
			pCurrNode->pAuxCertInfo->tbstrCertStore = "";

			if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM) )
			{
				DWORD dwPubKeyIdSize = 0;
				BYTE* pbytePubKeyId = NULL;

				/*Obtain the hash ascii hex of the public key*/
				retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
					NULL,&dwPubKeyIdSize);
				if(retVal == S_OK)
				{
					pbytePubKeyId = (BYTE*)new BYTE[dwPubKeyIdSize];
					if(!pbytePubKeyId)
						retVal = E_FAIL;
				}

				if(retVal == S_OK)
				{
					retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
						pbytePubKeyId,&dwPubKeyIdSize);
				}

				/*Convert to half ascii*/
				if(retVal == S_OK)
				{
					if(!BytesToAscHex(pbytePubKeyId,dwPubKeyIdSize,tbstrPubKeyId))
						retVal = E_FAIL;
				}

				delete[] pbytePubKeyId;

				/*Obtain the cert preferences from the registry*/
				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_FRNDLYNAME;
					retVal = _GetMSCapiCertPref(tbstrPubKeyId, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrFrndlyName));
				}
				
				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_DISPSTRING;
					retVal = _GetMSCapiCertPref(tbstrPubKeyId, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrDispString));
				}

				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_LOGOURL;
					retVal = _GetMSCapiCertPref(tbstrPubKeyId, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrLogoUrl));
				}

				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_TEXTUREURL;
					retVal = _GetMSCapiCertPref(tbstrPubKeyId, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrTextureUrl));
				}

				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_RENEWED;					
					retVal = _GetMSCapiCertPref(tbstrPubKeyId, tbstrPrefName, &tbstrRenewedFlagString); 
					if(retVal == S_OK)
					{
						if(tbstrRenewedFlagString.length())
						{
							if(tbstrRenewedFlagString == _bstr_t("0"))
								pCurrNode->pAuxCertInfo->boolRenewed = FALSE;
							else
								pCurrNode->pAuxCertInfo->boolRenewed = TRUE;
						}
					}
				}


				if(retVal == S_OK)
				{
					tbstrPrefName = APPPREF_DEFCERTISSDN;
					retVal = _GetMSCapiAppPref(i_tbstrAppCtxtName, tbstrPrefName, &tbstrDefCertIssDN);
					if(retVal != S_OK)
					{
						retVal = S_OK;
						tbstrDefCertIssDN = "";
					}

					if(retVal == S_OK)
					{
						tbstrPrefName = APPPREF_DEFCERTSERNUM;
						retVal = _GetMSCapiAppPref(i_tbstrAppCtxtName, tbstrPrefName, &tbstrDefCertSerNum);
						if(retVal != S_OK)
						{
							retVal = S_OK;
							tbstrDefCertSerNum = "";
						}
					}

					if(retVal == S_OK)
					{
						if(pCurrNode->pDecCertInfo->tbstrIssuerDN == tbstrDefCertIssDN 
						   && pCurrNode->pDecCertInfo->tbstrSerNum == tbstrDefCertSerNum)
						{
							pCurrNode->pAuxCertInfo->boolIsDef = TRUE;
						}
						else
						{
							pCurrNode->pAuxCertInfo->boolIsDef = FALSE;
						}
					}
					

				}

				bResult =	MSCapi_CertGetCertificateContextProperty
							(
								pCurrNode->pCertContext,
								CERT_KEY_PROV_INFO_PROP_ID,
								NULL,
								&cbData
							);
				if (bResult)
				{
					pCryptKeyProvInfo =	(CRYPT_KEY_PROV_INFO*) new BYTE [cbData];

					bResult =	MSCapi_CertGetCertificateContextProperty
								(
									pCurrNode->pCertContext,
									CERT_KEY_PROV_INFO_PROP_ID,
									(void*) pCryptKeyProvInfo,
									&cbData
								);
					if (bResult)
					{
						pCurrNode->pAuxCertInfo->tbstrContainerName =	pCryptKeyProvInfo->pwszContainerName;
						pCurrNode->pAuxCertInfo->nKeySpec = pCryptKeyProvInfo->dwKeySpec;
					}
/*					else
					{
						retVal = E_CERTPREFNOTFOUND;
						break;
					}
*/
				}
/*				else
				{
					retVal = E_CERTPREFNOTFOUND;
					break;
				}
*/
			}
			else
			{
				tbstrPrefName = CERTPREF_FRNDLYNAME;

				/*Obtain the cert preferences from the smart card*/
				retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrFrndlyName)); 
				if(retVal == E_CERTPREFNOTFOUND)
					retVal = S_OK;

				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_DISPSTRING;
					retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrDispString)); 
					if(retVal == E_CERTPREFNOTFOUND)
						retVal = S_OK;

				}
				
				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_LOGOURL;
					retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrLogoUrl)); 
					if(retVal == E_CERTPREFNOTFOUND)
						retVal = S_OK;
				}


				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_TEXTUREURL;
					retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrTextureUrl)); 
					if(retVal == E_CERTPREFNOTFOUND)
						retVal = S_OK;
				}


				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_RENEWED;					
					retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &tbstrRenewedFlagString); 
					if(retVal == S_OK)
					{
						if(tbstrRenewedFlagString == _bstr_t("0"))
							pCurrNode->pAuxCertInfo->boolRenewed = FALSE;
						else
							pCurrNode->pAuxCertInfo->boolRenewed = TRUE;
					}
					else if(retVal == E_CERTPREFNOTFOUND)
						retVal = S_OK;					
				}

				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_CONTAINER_NAME;
					retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrContainerName)); 
					if(retVal == E_CERTPREFNOTFOUND)
						retVal = S_OK;
				}

				if(retVal == S_OK)
				{
					tbstrPrefName = CERTPREF_STORE;
					retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrPrefName, &(pCurrNode->pAuxCertInfo->tbstrCertStore)); 
					if(retVal == E_CERTPREFNOTFOUND)
						retVal = S_OK;
				}

				/*Mark this cert if it is the default cert*/
				if(retVal == S_OK)
				{
					
					VARIANT varDefCertIssDN;
					VARIANT varDefCertSerNum;
					BSTR bstrDefCertIssDN = NULL;
					BSTR bstrDefCertSerNum = NULL;

					varDefCertIssDN.vt = VT_EMPTY;
					varDefCertIssDN.parray = NULL;

					varDefCertSerNum.vt = VT_EMPTY;
					varDefCertSerNum.parray = NULL;

					tbstrPrefName = APPPREF_DEFCERTISSDN;
					retVal = i_pVirtualSmartCard->VSM_GetAppPreference(tbstrPrefName, &varDefCertIssDN);
					if(retVal == S_OK)
					{
						retVal = BstrFromVector(varDefCertIssDN.parray, &bstrDefCertIssDN);
						if(retVal == S_OK)
						{
							tbstrDefCertIssDN = bstrDefCertIssDN;
							SysFreeString(bstrDefCertIssDN);
						}

						VariantClear(&varDefCertIssDN);
					}
					else if(retVal != E_USERCANCELLED)
						retVal = S_OK;

					if(retVal == S_OK)
					{
						tbstrPrefName = APPPREF_DEFCERTSERNUM;
						retVal = i_pVirtualSmartCard->VSM_GetAppPreference(tbstrPrefName, &varDefCertSerNum);
						if(retVal == S_OK)
						{
							retVal = BstrFromVector(varDefCertSerNum.parray, &bstrDefCertSerNum);
							if(retVal == S_OK)
							{
								tbstrDefCertSerNum = bstrDefCertSerNum;
								SysFreeString(bstrDefCertSerNum);
							}
							VariantClear(&varDefCertSerNum);
						}
						else if(retVal != E_USERCANCELLED)
							retVal = S_OK;

					}
					
					if(retVal == S_OK)
					{
						if(pCurrNode->pDecCertInfo->tbstrIssuerDN == tbstrDefCertIssDN 
						   && pCurrNode->pDecCertInfo->tbstrSerNum == tbstrDefCertSerNum)
						{
							pCurrNode->pAuxCertInfo->boolIsDef = TRUE;
						}
						else
						{
							pCurrNode->pAuxCertInfo->boolIsDef = FALSE;
						}
					}
					

				}

			}

			pCurrNode = pCurrNode->pidlistnodeNext;
			nCertNum++;
		}

		if(retVal != S_OK)
			pCurrNode = NULL;
	}

//	VSPTA_CLEAN_TBSTR(tbstrPrefName)
//	VSPTA_CLEAN_TBSTR(tbstrRenewedFlagString)
//	VSPTA_CLEAN_TBSTR(tbstrPubKeyId)
//	VSPTA_CLEAN_TBSTR(tbstrDefCertIssDN)
//	VSPTA_CLEAN_TBSTR(tbstrDefCertSerNum)
//	VSPTA_CLEAN_TBSTR(tbstrDefCertIssDN)
//	VSPTA_CLEAN_TBSTR(tbstrDefCertSerNum)

	return retVal;
}

HRESULT CPtaEngine::_DoesCertMatchSrchCrit(CVirtualSmartCard* i_pVirtualSmartCard, PIDLISTNODE i_pCert,SRCHCRIT& i_theSrchCrit)
{
	HRESULT retVal = S_OK;

	
	if(retVal == S_OK)
	{
		//Is this VS blessed
		retVal = _CheckIfVSBlessed(i_pCert->pCertContext);
	}

	if(retVal == S_OK)
	{
		retVal = _CheckIfDNGood(i_pCert->pDecCertInfo->tbstrIssuerDN, i_theSrchCrit.tbstrIssuerDN);
	}

	if(retVal == S_OK)
	{
		retVal = _CheckIfDNGood(i_pCert->pDecCertInfo->tbstrSubjectDN, i_theSrchCrit.tbstrSubjectDN);
	}

	if(retVal == S_OK)
	{
		retVal = _CheckIfSerNumGood(i_pCert->pDecCertInfo->tbstrSerNum, i_theSrchCrit.tbstrSerNum);
	}

	if(retVal == S_OK)
	{
		if(i_theSrchCrit.dateEffDate)
		{
			DWORD dwDataEq;
			if(i_theSrchCrit.nDateEquality & 0x00000001)
				dwDataEq = VS_LESS; //less than
			else if(i_theSrchCrit.nDateEquality & 0x0000002)
				dwDataEq = VS_EQ; //equal to
			else if(i_theSrchCrit.nDateEquality & 0x0000004)
				dwDataEq = VS_GREATER; //Greater than
			else
				retVal = E_INVALIDFLAGS;
			
			if(retVal == S_OK)
			{
				retVal = _CheckIfDateGood(i_pCert->pDecCertInfo->dateEffDate, i_theSrchCrit.dateEffDate, dwDataEq);
			}
		}
	}

	if(retVal == S_OK)
	{
		_bstr_t tbstrEmailSrchDN = "";
		if(i_theSrchCrit.tbstrEmail.length())
		{
			tbstrEmailSrchDN = "E=";
			tbstrEmailSrchDN += i_theSrchCrit.tbstrEmail;
		}
		retVal = _CheckIfDNGood(i_pCert->pDecCertInfo->tbstrSubjectDN, tbstrEmailSrchDN);

//		VSPTA_CLEAN_TBSTR(tbstrEmailSrchDN)
	}

	if(retVal == S_OK)
	{
		retVal = _CheckIfRenewedGood(i_pCert->pAuxCertInfo->boolRenewed, i_theSrchCrit.boolRenewed);
	}

	if(retVal == S_OK)
	{
		if(i_theSrchCrit.dateExpDate)
		{
			DWORD dwDataEq;
			if(i_theSrchCrit.nDateEquality & 0x00000008)
				dwDataEq = VS_LESS; //less than
			else if(i_theSrchCrit.nDateEquality & 0x00000010)
				dwDataEq = VS_EQ; //equal to
			else if(i_theSrchCrit.nDateEquality & 0x00000020)
				dwDataEq = VS_GREATER; //Greater than
			else
				retVal = E_INVALIDFLAGS;


			if(retVal == S_OK)
			{
				retVal = _CheckIfDateGood(i_pCert->pDecCertInfo->dateExpDate, i_theSrchCrit.dateExpDate, dwDataEq);
				if(retVal == E_CERTNOMATCHCRIT && dwDataEq == VS_GREATER)
					retVal = E_CERTMATCHBUTEXP;
			}
		}		
	}

	/*Is the key usage as required*/
	if(retVal == S_OK)
	{
		retVal = _CheckIfKeyUsageGood(i_pCert->pDecCertInfo->nKeyUsage, i_theSrchCrit.nKeyUsage);
	}

	if(retVal == S_OK)
	{
		//Do we have access to the private keys
		retVal = _CheckPrivKeyAccess(i_pVirtualSmartCard, i_pCert->pCertContext);

	}



	return retVal;
}

HRESULT CPtaEngine::_CheckIfKeyUsageGood(int i_nCertKeyUsage, int i_nSrchCritKeyUsage)
{
	HRESULT retVal = S_OK;

	if(i_nCertKeyUsage && i_nSrchCritKeyUsage)
	{
		if(!(i_nCertKeyUsage & i_nSrchCritKeyUsage))
		{
			retVal = E_CERTNOMATCHCRIT;
		}
	}

	return retVal;
}

HRESULT CPtaEngine::_CheckPrivKeyAccess(CVirtualSmartCard* i_pVirtualSmartCard, PCERT_CONTEXT i_pCertContext)
{
	HRESULT retVal = S_OK;
	if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM))
	{
		DWORD cbData;
		PCRYPT_KEY_PROV_INFO pvData = NULL;
		HCRYPTPROV hCryptProv = 0;
		LPSTR szProvName = NULL;

		//Get the key provider information parameter associated with the Cert Context
		if(!MSCapi_CertGetCertificateContextProperty( i_pCertContext,   CERT_KEY_PROV_INFO_PROP_ID,
											   NULL,  &cbData))
		{
			retVal = E_CERTNOMATCHCRIT;
		}

		//allocate memroy
		if(retVal == S_OK)
		{
			if((pvData = (PCRYPT_KEY_PROV_INFO)new BYTE[cbData]) == NULL)
			{
				retVal = E_FAIL;
			}
		}

		if(retVal == S_OK)
		{
			if(!MSCapi_CertGetCertificateContextProperty( i_pCertContext,   CERT_KEY_PROV_INFO_PROP_ID,
												   (void*)pvData,  &cbData))
			{
				retVal = E_CERTNOMATCHCRIT;

			}
		}


		if(retVal == S_OK)
		{
			//Try to open the key container
			_bstr_t bstrContainer(pvData->pwszContainerName);
			_bstr_t bstrProvName(pvData->pwszProvName);
			//if(!MSCapi_CryptAcquireContext(&hCryptProv, (TCHAR*)bstrContainer,(TCHAR*)bstrProvName, PROV_RSA_FULL,  0))
			if(bstrContainer == _bstr_t("") || bstrProvName == _bstr_t(""))
			{
				retVal = E_CERTNOMATCHCRIT;
			}

//			VSPTA_CLEAN_TBSTR(bstrContainer)
//			VSPTA_CLEAN_TBSTR(bstrProvName)
		}

		delete[] pvData;

		//If it does not open then return false, else return true.
		MSCapi_CryptReleaseContext(hCryptProv, 0);
	}
	else
	{
		/*Obtain the public key identifier for the public key in the cert*/
		PBYTE pbytePubKeyId = NULL;
		DWORD dwPubKeyIdSize;

		retVal = GetPubKeyIdentifierFromPubKey(i_pCertContext->pCertInfo->SubjectPublicKeyInfo,
			NULL, &dwPubKeyIdSize);
		if(retVal == S_OK)
		{
			pbytePubKeyId = new BYTE[dwPubKeyIdSize];
			if(!pbytePubKeyId)
				retVal = E_FAIL;
			else
			{
				retVal = GetPubKeyIdentifierFromPubKey(i_pCertContext->pCertInfo->SubjectPublicKeyInfo,
					pbytePubKeyId, &dwPubKeyIdSize);
			}
		}

		/*Ask the smart card if the private key is available corresponding to 
		this public key*/
		retVal = i_pVirtualSmartCard->VSM_IsPrivKeyAvailable(pbytePubKeyId, dwPubKeyIdSize);
		if(retVal == E_KEYDOESNOTEXIST)
			retVal = E_CERTNOMATCHCRIT;

		delete[] pbytePubKeyId;

	}

	return retVal;
}

HRESULT CPtaEngine::_CheckIfVSBlessed(PCERT_CONTEXT i_ppCertContext)
{
	HRESULT retVal = S_OK;

	return retVal;
}
/*This function finds the name-value pairs in the argument passed.
If the value contains a comma then the whole value is enclosed in double quotes.
This provides fix for artf25786 */
wchar_t* CPtaEngine::FormattedIssuerDNSrchCrit( _bstr_t& i_tbstrSubjectDN)
{
	const unsigned int max_comma = 100;
	unsigned int i, j, temp, flagCommaPresent=0;
	wchar_t *PtrOriStr, *PtrNewStr;
	PtrOriStr = i_tbstrSubjectDN.operator wchar_t *();

	PtrNewStr = (wchar_t*)malloc( (i_tbstrSubjectDN.length() + max_comma) * sizeof(wchar_t));
	if (PtrNewStr)
	{
		for (i=0,j=0; *(PtrOriStr+i);)
		{
			/* The value after '=' is the value part of the name-value pair*/
			if ( *(PtrOriStr+i) == '=')
			{
				*(PtrNewStr+j) = *(PtrOriStr+i);
				i++; j++;
				/*Encapsulate the value in double quotes ("), if the value has comma*/
				temp =i;
				flagCommaPresent =0;
				/* semicolon (;) is the delimiter after which another name-value begins. NULL is the DN string terminator*/
				while (*(PtrOriStr + i) != ';' && *(PtrOriStr + i) != NULL)
				{
					if ( *(PtrOriStr + i) == ',')
					{
						if(!flagCommaPresent)
						{
							*(PtrNewStr + j) = '"';
							j++;
						}
						flagCommaPresent = 1;
					}
					i++;
				}
				while (temp != i)
				{
					*(PtrNewStr + j) = *(PtrOriStr + temp);
					temp++;
					j++;
				}
				if (flagCommaPresent == 1)
				{
					*(PtrNewStr + j) = '"';
					j++;
				}
				*(PtrNewStr + j) = *(PtrOriStr + i);
				if (*(PtrOriStr + i) != NULL)
				{
					i++;
					j++;
				}
			}
			else
			{
				*(PtrNewStr+j) = *(PtrOriStr+i);
				i++; j++;
			}
		}
		*(PtrNewStr+j) = *(PtrOriStr+i);
	}
	return (PtrNewStr);
}

HRESULT CPtaEngine::_CheckIfDNGood(_bstr_t& i_tbstrIssuerDN, _bstr_t& i_tbstrIssDNSrchCrit)
{
	HRESULT retVal = S_OK;
	_bstr_t* ptbstrDNAttrs = NULL;
	_bstr_t* ptbstrDNVals = NULL;
	int nNumOfDNAttrs;

	_bstr_t* ptbstrSrchAttrs = NULL;
	_bstr_t* ptbstrSrchVals = NULL;
	int nNumOfSrchAttrs;
	wchar_t *ptrwcharFormatted;
	_bstr_t bstrFormatIssDNSrchCrit;


	/*Obtain the components of the issuer dn*/
	retVal = _ParseDNIntoComponents(i_tbstrIssuerDN,&nNumOfDNAttrs,&ptbstrDNAttrs, 
		&ptbstrDNVals);

	/*Obtain the components of the issuer search string*/
	if(retVal == S_OK)
	{
		/*If the value in any name-value pair of  i_tbstrIssDNSrchCrit has comma then encapsulate 
		that value in double quotes. Fixed as part of artf25786*/
		ptrwcharFormatted=FormattedIssuerDNSrchCrit(i_tbstrIssDNSrchCrit);
		if (ptrwcharFormatted)
		{
			bstrFormatIssDNSrchCrit= _bstr_t(ptrwcharFormatted);
			free(ptrwcharFormatted);
		}

	/*Pass formatted Issuer DN Search Cirteria to get number of Srch Attrs and Ptr to each Attr */
		retVal = _ParseDNIntoComponents(bstrFormatIssDNSrchCrit,&nNumOfSrchAttrs,&ptbstrSrchAttrs, 
			&ptbstrSrchVals);

	}

	/*Make sure that each component in the search string appears in the issuer dn*/
	if(retVal == S_OK)
	{
		for(int i=0;i<nNumOfSrchAttrs;++i)
		{
			BOOL boolMatchFound = FALSE;
			for(int j=0;j<nNumOfDNAttrs;++j)
			{
				if(ptbstrSrchAttrs[i] == ptbstrDNAttrs[j])
				{
					if(ptbstrSrchVals[i] == ptbstrDNVals[j])
					{
						boolMatchFound = TRUE;
						j = nNumOfDNAttrs;
					}
				}
			}
			if(!boolMatchFound)
			{
				retVal = E_CERTNOMATCHCRIT;
				i = nNumOfSrchAttrs;
			}
		}
	}

	/*Free memory*/
	return retVal;
}


HRESULT CPtaEngine::_CheckIfSerNumGood(_bstr_t& i_tbstrSerNum, _bstr_t& i_tbstrSerNumSrchCrit)
{
	HRESULT retVal = S_OK;
	if(i_tbstrSerNumSrchCrit.length())
	{
		if(i_tbstrSerNum == i_tbstrSerNumSrchCrit)
			retVal = S_OK;
		else
			retVal = E_CERTNOMATCHCRIT;
	}

	return retVal;
}

HRESULT CPtaEngine::_CheckIfDateGood(DATE& i_dateEffDate, DATE& i_dateEffDateSrchCrit, int i_nDateEqualtiy)
{
	HRESULT retVal = S_OK;
	
	
	if(i_dateEffDateSrchCrit == 0)
	{
		return S_OK;
	}
	
	//Get the equality comparitive operator that we need to use
	
	switch(i_nDateEqualtiy)
	{
	case VS_LESS:
		if(i_dateEffDate < i_dateEffDateSrchCrit)
			retVal = S_OK;
		else
			retVal = E_CERTNOMATCHCRIT;
		break;

	case VS_EQ :
		if(i_dateEffDate == i_dateEffDateSrchCrit)
			retVal = S_OK;
		else
			retVal = E_CERTNOMATCHCRIT;
		break;

	case VS_GREATER :
		if(i_dateEffDate > i_dateEffDateSrchCrit)
			retVal = S_OK;
		else
			retVal = E_CERTNOMATCHCRIT;
		break;

	default :
		retVal = E_INVALIDARGS;
	}

	return retVal;
}

HRESULT CPtaEngine::_CheckIfRenewedGood(BOOL i_boolRenewed, BOOL i_boolRenewedSrchCrit)
{
	HRESULT retVal = S_OK;
	
	if(i_boolRenewed == i_boolRenewedSrchCrit)
		retVal = S_OK;
	else 
		retVal = E_CERTNOMATCHCRIT;

	return retVal;
}


HRESULT CPtaEngine::_CreatePKCS7(PBYTE i_pbyteSignature, unsigned int i_nSignatureSize, int i_nHashAlg, PCERT_CONTEXT i_pCertContext, PBYTE i_pbyteSignedData, int i_nSignedDataSize, PBYTE i_pbyteAuthAttrib, DWORD i_dwAuthAttrSize,_bstr_t* o_ptbstrPKCS7)
{
	HRESULT retVal = S_OK;
	
	//Obtain the (DER Encoded) issuer dn sequence of the cert
	CSequence cseqIssuer;
	CDERBlob cdbIssuer(i_pCertContext->pCertInfo->Issuer.cbData, i_pCertContext->pCertInfo->Issuer.pbData);
	CBaseDER cbdIssuer(cdbIssuer);

	//retVal = _GetDERIssuerDN(i_pCertContext, &cseqIssuer);
	
	//Obtain the (DER Encoded) serial number of the cert
	CUniversalInteger cuiSerialNum;
	if(retVal == S_OK)
	{
		
		retVal = _GetDERSerNum(i_pCertContext, &cuiSerialNum);

	}

	if(retVal == S_OK)
	{
		/* Create the following object 
			IssuerAndSerialNumber := SEQUENCE {
												issuer	Name,
												serialNumber CertifcateSerialNumber
									  }
		*/
		CBaseDERCollection cbdcIssSer;
		cbdcIssSer = cbdIssuer + cuiSerialNum; //cseqIssuer + cuiSerialNum;
		CSequence cseqIssSer(cbdcIssSer);

		/** Create a digest algorithm object for sha1 hash which looks as follows -
		SEQUENCE {
					OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
					NULL
				}

		This is the digestAlgorithm object
		**/
		
		//Create the sha1 object identifier
		
		_bstr_t tbstrAlgObjId = "";
		switch(i_nHashAlg)
		{
		case HASH_SHA1 :
			tbstrAlgObjId = szOID_OIWSEC_sha1;
			break;

		case HASH_MD2:
			tbstrAlgObjId = szOID_RSA_MD2;
			break;

		case HASH_MD5:
			tbstrAlgObjId = szOID_RSA_MD5;
			break;
		}
		CObjectIdentifier cobjidAlgId(tbstrAlgObjId.length(), (PBYTE)(CHAR*)tbstrAlgObjId);

		//Create a null object
		CNull cnullObj;
		
		//Create the sha1 algorithm identifier
		CBaseDERCollection cbdcAlgId;
		cbdcAlgId = cobjidAlgId + cnullObj ;
		CSequence cseqDigestAlg(cbdcAlgId);

		/** If authenticated attributes need to be included create the implicit tag for these attribs **/
		CTaggedValue ctvAuthAttrib;
		if(i_pbyteAuthAttrib)
		{
			CBaseDERCollection bdcAuthAttrib(i_dwAuthAttrSize, i_pbyteAuthAttrib); 
			CTaggedValue ctvAuthAttrib_temp(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(bdcAuthAttrib.BaseDERBlob));
			ctvAuthAttrib = ctvAuthAttrib_temp;
		}


		/** Create a rsa encryption algorithm object which looks as follows -
		SEQUENCE {
					OBJECT IDENTIFIER rsaEncryption (1.2.840.113549.1.1.1)
					NULL
				}
		This is the digest
		**/

		//Create an object identifier for the OID 1.2.840.113549.1.1.1
		_bstr_t tbstrRSAEncObjId = szOID_RSA_RSA;
		CObjectIdentifier cobjidRSAEncObjId(tbstrRSAEncObjId.length(),(BYTE*)(CHAR*)tbstrRSAEncObjId);

		//Create a sequence containing the above OID and null object
		cbdcAlgId = cobjidRSAEncObjId + cnullObj;
		CSequence cseqDigestEncAlg(cbdcAlgId );

		//Create an octet string containing the signature (encryptedDigest).
		COctetString cmyosEncryptedDigest(i_nSignatureSize, i_pbyteSignature);

		/* Create the signer info object which is defined as follows -
		SignerInfo := SEQUENCE {
								version INTEGER,
								issuerAndSerialNumber IssuerAndSerialNumber,
								digestAlgorithm DigestAlgorithmIdentifier,
								digestEncryptionAlgorithm DignestEncryptionAlgorithmIdentifier,
								encryptedDigest EncryptedDigest
					  }

		OR if we have authenticated attributes then

		SignerInfo := SEQUENCE {
								version INTEGER,
								issuerAndSerialNumber IssuerAndSerialNumber,
								digestAlgorithm DigestAlgorithmIdentifier,
								authenticatedAttributes   [0] IMPLICIT Attributes OPTIONAL,
								digestEncryptionAlgorithm DignestEncryptionAlgorithmIdentifier,
								encryptedDigest EncryptedDigest
					  }
		*/

		BYTE byteVer = 0x01;
		CUniversalInteger cuiVersion(sizeof(BYTE),(BYTE*)&byteVer);

		CBaseDERCollection cbdcSignerInfo;
		if(i_pbyteAuthAttrib)
			cbdcSignerInfo = cuiVersion + cseqIssSer + cseqDigestAlg + ctvAuthAttrib + cseqDigestEncAlg + cmyosEncryptedDigest;
		else
			cbdcSignerInfo = cuiVersion + cseqIssSer + cseqDigestAlg + cseqDigestEncAlg + cmyosEncryptedDigest;

		CSequence cseqSignerInfo(cbdcSignerInfo);

		/* Create the SignerInfos object defined as
				SignerInfos := CHOICE {
									siSet	SET OF SignerInfo,
									siSequence SEQUENCE OF SignerInfo
								}

				We will choose a set and this set will include only one SignerInfo object created above
		*/
		CBaseDERCollection cbdcSignerInfos;
		cbdcSignerInfos = cseqSignerInfo;
		CSet csetSignerInfos(cbdcSignerInfos);

		/* Create the DigestAlgorithmIdentifiers object defined as follows 
			DigestAlgorithmIdenitifiers := CHOICE {
												daSet SET OF DigestAlgorithmIdentifier
												daSequence SEQUENCE OF DigestAlgorithmIdentifier
											}

			Where the DigestAlgorithmIdentifier specify the digest algorithm being used
			

			We will use a set, and we use only one digest algorithm viz. sha1 so our object will look like
			SET {
				SEQUENCE {
					OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
					NULL
					}
				}

		*/

		CBaseDERCollection cbdcDigestAlgorithms;
		cbdcDigestAlgorithms = cseqDigestAlg;
		CSet csetDigestAlgorithms(cbdcDigestAlgorithms);


		/*
			Create the content info object defined as 
			ContentInfo := SEQUENCE {
										contentType contentType;
										content [0] EXPLICIT CONTENTS.&Type((Contents)(@contentType)) OPTIONAL
									}
			The specific object we will create is
			SEQUENCE {
						OBJECT IDENTIFIER data (1.2.840.113549.1.7.1)
					 }
						
		*/
		
		_bstr_t tbstrDataObjId = szOID_RSA_data;
		CObjectIdentifier cobjidData(tbstrDataObjId.length(), (PBYTE)(CHAR*)tbstrDataObjId);
		CTaggedValue ctvContent;
		if(i_pbyteSignedData && i_nSignedDataSize)
		{
			COctetString cosContent(i_nSignedDataSize, i_pbyteSignedData);
			ctvContent = CTaggedValue(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, cosContent);
		}

		CBaseDERCollection cbdcContentInfo;
		if(i_pbyteSignedData && i_nSignedDataSize)
		{
			cbdcContentInfo = cobjidData + ctvContent;
		}
		else
		{
			cbdcContentInfo = cobjidData;
		}
		
		CSequence cseqContentInfo(cbdcContentInfo);

		/*
			Create the cert chain - for now the cert chain will have only one cert - the end cert.
			In the future we can add the intermediate CAs in the chain
		*/
		//Create the BaseDER object for the cert
		CDERBlob cderblobEndCert(i_pCertContext->cbCertEncoded, i_pCertContext->pbCertEncoded);
		CBaseDER cbasederEndCert(cderblobEndCert);
		
		CTaggedValue ctvCertChain(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, cbasederEndCert);
		
		/* Create the signed data content  which is defined as
			SignedData := SEQUENCE {
								version INTEGER,
								digestAlgorithms DigestAlgorithmIdentifiers,
								conentInfo ContentInfo,
								certificates CHOICE {
											certSet [0] IMPLICIT ExtendedCertificatesAndCertificates
											certSequence [2] IMPLICIT Certificates
										} OPTIONAL,
								signerInfos SignerInfos
							}
								
		*/
		CBaseDERCollection cbdcSignedData;
		cbdcSignedData = cuiVersion + csetDigestAlgorithms + cseqContentInfo + ctvCertChain + csetSignerInfos;
		CSequence cseqSignedData(cbdcSignedData);

		/* Finally create the signed data pkcs7 which looks like this
			SEQUENCE {
					OBJECT IDENTIFIER signedData (1.2.840.113549.1.7.2)
					[0] {
						signedData
					}
				}
			(Note this an object of type ContentInfo)
		*/
		_bstr_t tbstrSignedDataObjId = szOID_RSA_signedData;
		CObjectIdentifier cobjidSignedData(tbstrSignedDataObjId.length(), (PBYTE)(CHAR*)tbstrSignedDataObjId);
		
		CTaggedValue ctvSignedDataContent(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(cseqSignedData.BaseDERBlob));

		cbdcContentInfo = cobjidSignedData + ctvSignedDataContent;

		cseqContentInfo = cbdcContentInfo;
		
#ifdef DEBUG
		FILE* fp;
		fp = (FILE*)fopen("temppkcs7.bin","wb");
		for(unsigned int i=0;i<cseqContentInfo.BaseDERBlob->cbData; ++i)
		{
			fprintf(fp,"%c",cseqContentInfo.BaseDERBlob->pbData[i]);
		}
		fclose(fp);

#endif
		DWORD dwB64P7Size;
		char* pszB64P7 = NULL;

		if(retVal == S_OK)
		{
			_Base64Encode((char*)(cseqContentInfo.BaseDERBlob->pbData),cseqContentInfo.BaseDERBlob->cbData,
				NULL,&dwB64P7Size);
			pszB64P7 = new char[dwB64P7Size+1];
			if(!pszB64P7)
				retVal = E_FAIL;
			else
			{
				_Base64Encode((char*)(cseqContentInfo.BaseDERBlob->pbData),cseqContentInfo.BaseDERBlob->cbData,
					pszB64P7,&dwB64P7Size);
				pszB64P7[dwB64P7Size] = '\0';
				*o_ptbstrPKCS7 = pszB64P7;
				delete[] pszB64P7;
			}

		}

//		VSPTA_CLEAN_TBSTR(tbstrAlgObjId)
	}

	return retVal;
}

HRESULT CPtaEngine::_GetDERIssuerDN(PCERT_CONTEXT i_pCertContext, CSequence* o_pcseqIssuer)
{
	/*CBaseDERCollection cbdcIssDN(i_pCertContext->pCertInfo->Issuer.cbData, i_pCertContext->pCertInfo->Issuer.pbData);
	CBaseDERHierarchy cbdhIssDN(cbdcIssDN);
	CSequence cseqIssDN(*(cbdhIssDN.m_DERTree.currentBaseDER));*/
	CDERBlob cdbIssDN(i_pCertContext->pCertInfo->Issuer.cbData, i_pCertContext->pCertInfo->Issuer.pbData);
	//CBaseDER cbdIssDN(cdbIssDN);

	CSequence cseqIssDN;
	cseqIssDN.BaseDERBlob = &cdbIssDN;
	cseqIssDN.decode();
	*o_pcseqIssuer = cseqIssDN;
	return S_OK;
}

HRESULT CPtaEngine::_GetDERSerNum(PCERT_CONTEXT i_pCertContext, CUniversalInteger* o_pcuiSerialNum)
{
	CUniversalInteger cuiSerNum(i_pCertContext->pCertInfo->SerialNumber.cbData, i_pCertContext->pCertInfo->SerialNumber.pbData);
	*o_pcuiSerialNum = cuiSerNum;
	return S_OK;
}

HRESULT CPtaEngine::SignData(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, BOOL i_boolHashData, BOOL i_boolP7Output, BOOL i_boolAddAuthAttr, DATE i_dateSignDate, _bstr_t* o_ptbstrSignature)

{
	HRESULT retVal = S_OK;

	if(boolIsCapi)
	{
		retVal = _SignDataWithMSCapi(i_pbyteDataToSign, i_nDataToSignSize, i_nHashAlg, i_pSelectedId, i_boolIsAttached, o_ptbstrSignature);
	}
	else
	{
		if ( dwIsTPM )
		{
			retVal = _SignDataWithVSTPM(i_pVirtualSmartCard, i_pbyteDataToSign, i_nDataToSignSize, i_nHashAlg, i_pSelectedId, i_boolIsAttached, i_boolHashData, i_boolP7Output, i_boolAddAuthAttr, i_dateSignDate, o_ptbstrSignature);
		}
		else
		{
			retVal = _SignDataWithVSCapi(i_pVirtualSmartCard, i_pbyteDataToSign, i_nDataToSignSize, i_nHashAlg, i_pSelectedId, i_boolIsAttached, i_boolHashData, i_boolP7Output, i_boolAddAuthAttr, i_dateSignDate, o_ptbstrSignature);
		}

	}

	return retVal;

}

HRESULT CPtaEngine::_SignDataWithMSCapi(PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, _bstr_t* o_ptbstrSignature)
{
	HRESULT retVal = S_OK;
	BYTE			*pbSignedMessageBlob = NULL;

	do
	{
		const BYTE  *MessageArray[] = {i_pbyteDataToSign};

		DWORD		MessageSizeArray[]= {i_nDataToSignSize};

		PCCERT_CONTEXT		MsgCertArray[] = {i_pSelectedId->pCertContext}; 


		//-------------------------------------------------------------
		// Initialize the Algorithm Identifier structure
		//-------------------------------------------------------------

		DWORD                         HashAlgSize;
		CRYPT_ALGORITHM_IDENTIFIER    HashAlgorithm;

		HashAlgSize = sizeof(HashAlgorithm);
		memset(&HashAlgorithm, 0, HashAlgSize);     // Init. to zero.

		switch(i_nHashAlg)
		{
		case HASH_MD2:
			HashAlgorithm.pszObjId = szOID_RSA_MD2;    // Set the necessary field.
			break ;

		case HASH_MD5:
			HashAlgorithm.pszObjId = szOID_RSA_MD5;    
			break ;

		case HASH_SHA1:
			HashAlgorithm.pszObjId = szOID_OIWSEC_sha1;
			break ;

		default :
			HashAlgorithm.pszObjId = szOID_RSA_MD5;   
			break ;
		}

				
		//-------------------------------------------------------------
		// Initialize the signature structure 
		//-------------------------------------------------------------

		CRYPT_SIGN_MESSAGE_PARA    SigParams;
		DWORD SigParamsSize = sizeof(SigParams);

		memset(&SigParams, 0, SigParamsSize);    // Init. to zero
		// Then set the necessary fields.
		SigParams.cbSize = SigParamsSize;
		SigParams.dwMsgEncodingType = MY_ENCODING_TYPE;
		SigParams.pSigningCert = i_pSelectedId->pCertContext;
		SigParams.HashAlgorithm = HashAlgorithm;
		SigParams.cMsgCert = 1;
		SigParams.rgpMsgCert = MsgCertArray;


		// Get the size of the output SignedBlob
		DWORD    cbSignedMessageBlob = NULL;
		BOOL	 fResult = FALSE ;

		fResult = MSCapi_CryptSignMessage(
					&SigParams,            // Signature parameters
					!i_boolIsAttached,     // Attached or detached?
					1,                     // Number of messages
					MessageArray,          // Messages to be signed
					MessageSizeArray,      // Size of messages 
					NULL,                  // Buffer for signed msg
					&cbSignedMessageBlob); // Size of buffer
		if(FALSE == fResult)
		{
			DWORD dwLastError = GetLastError();
			retVal = E_CRYPTSIGNMSGFAILED;
			*o_ptbstrSignature = "";
			break;
		}
				
		// Allocate memory for the signed blob.
		pbSignedMessageBlob = (BYTE*)new BYTE[cbSignedMessageBlob];
		
		if(!pbSignedMessageBlob)
		{
			retVal = E_FAIL;
			*o_ptbstrSignature = "";
			break;
		}
		memset(pbSignedMessageBlob, 49, cbSignedMessageBlob);
		
		// Get the SignedMessageBlob.
		fResult = MSCapi_CryptSignMessage(
			&SigParams,            // Signature parameters
			!i_boolIsAttached,     // Attached or detached
			1,                     // Number of messages
			MessageArray,          // Messages to be signed
			MessageSizeArray,      // Size of messages
			pbSignedMessageBlob,   // Buffer for signed msg
			&cbSignedMessageBlob); // Size of buffer
		if(FALSE == fResult)
		{
			retVal = E_CRYPTSIGNMSGFAILED;
			*o_ptbstrSignature = "";
			break;

		}

		DWORD dwB64P7Size;
		char* pszB64P7 = NULL;

		_Base64Encode((char*)pbSignedMessageBlob,cbSignedMessageBlob,NULL,&dwB64P7Size);
		pszB64P7 = new char[dwB64P7Size+1];
		if(!pszB64P7)
		{

			retVal = E_FAIL;
			*o_ptbstrSignature = "";
			break;
		}
		else
		{
			_Base64Encode((char*)pbSignedMessageBlob,cbSignedMessageBlob,pszB64P7,&dwB64P7Size);
			pszB64P7[dwB64P7Size] = '\0';
			*o_ptbstrSignature = pszB64P7;
			delete[] pszB64P7;
		}

	}while(0);

	delete[] pbSignedMessageBlob;

	return retVal;
}

HRESULT CPtaEngine::_SignDataWithVSCapi(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, BOOL i_boolHashData, BOOL i_boolP7Output, BOOL i_boolAddAuthAttr, DATE i_dateSignDate, _bstr_t* o_ptbstrSignature)
{
	HRESULT retVal = S_OK;
	/*Obtain the public key identifier for this cert*/
	PBYTE pbytePubKeyHandle = NULL;
	DWORD dwPubKeyHandleSize;
	DWORD dwAuthAttrSize = 0;
	PBYTE pbyteAuthAttr = NULL;
	PBYTE pbyteRevAuthAttr = NULL;


	if(retVal == S_OK)
	{
		retVal = GetPubKeyIdentifierFromPubKey(
			(i_pSelectedId->pCertContext->pCertInfo->SubjectPublicKeyInfo),
			NULL,&dwPubKeyHandleSize);
		if(retVal == S_OK)
		{
			pbytePubKeyHandle = new BYTE[dwPubKeyHandleSize];
			if(!pbytePubKeyHandle)
				retVal = E_FAIL;
			else
			{
				retVal = GetPubKeyIdentifierFromPubKey(
							i_pSelectedId->pCertContext->pCertInfo->SubjectPublicKeyInfo,
							pbytePubKeyHandle,&dwPubKeyHandleSize);
			}
		}
	}

	/*Hash and sign the data*/
	BYTE* pbyteSignature = NULL;
	DWORD dwSignatureSize;

	if(retVal == S_OK)
	{
			//
			//	Anand	Dec 14, 2000
			//
			//	This new condition is added. If the application has set the hash
			//	falg to FALSE using the dll api then the value of i_boolHashData will be FALSE.
			//	in that case go ahead instead of hashing the data.
			//
		if ( TRUE == i_boolHashData )
		{
			BYTE* pbyteHash = NULL;
			int nHashSize;
			
			void* pvHashCtxt;
					

			if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
			{
				retVal = E_HASHBEGINERR;
			}
			else
			{
				if(HashData(i_nHashAlg,pvHashCtxt,i_pbyteDataToSign ,i_nDataToSignSize) == -1)
				{
					retVal = E_HASHDATAERR;
				}
				else
				{
					//Allocate memory for the hash algorithm
					switch(i_nHashAlg)
					{
					case HASH_SHA1 :
						nHashSize = 20;
						pbyteHash = new BYTE[20];
						break;

					case HASH_MD2 :
					case HASH_MD5:
						nHashSize = 16;
						pbyteHash = new BYTE[16];
						break;

					default :
						retVal = E_INVALIDFLAGS;
						break;
					}

					if(HashEnd(i_nHashAlg,pvHashCtxt,pbyteHash,nHashSize) == -1)
					{
						retVal = E_HASHENDERR;
					}
					else
					{
						//If we need to add authenticated attributes, create them here
						//and hash them. Then sign this hash.
						if(i_boolAddAuthAttr)
						{
							if((retVal = _GetAuthAttr(pbyteHash,nHashSize,i_dateSignDate,NULL,&dwAuthAttrSize)) == S_OK)
							{
								pbyteAuthAttr = (PBYTE)new BYTE[dwAuthAttrSize];
								if(!pbyteAuthAttr)
									retVal = E_FAIL;
								else
								{
									if((retVal = _GetAuthAttr(pbyteHash,nHashSize,i_dateSignDate,pbyteAuthAttr,&dwAuthAttrSize)) == S_OK)
									{
										// Reverse the auth attributes as passing it to the CSet is 
										// reversing it again!!!
										pbyteRevAuthAttr = (PBYTE) new BYTE[dwAuthAttrSize];
										if(!pbyteRevAuthAttr)
											retVal = E_FAIL;
										else
										{
											for(INT i = 0, j = dwAuthAttrSize - 1; j >= 0; i++, j--)
												pbyteRevAuthAttr[i] = pbyteAuthAttr[j];

											//Now put this auth attr blob within a set
											CSet csetAttribs(dwAuthAttrSize, pbyteRevAuthAttr);
											
											//We have the auth attributes. Now we have to hash them.
											if(pbyteHash)
											{
												delete[] pbyteHash;
												pbyteHash = NULL;
											}


											if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
											{	
												retVal = E_HASHBEGINERR;
											}
											else
											{
												if(HashData(i_nHashAlg,pvHashCtxt,csetAttribs.BaseDERBlob->pbData,csetAttribs.BaseDERBlob->cbData) == -1)
												{
													retVal = E_HASHDATAERR;
												}

												//Allocate memory for the hash algorithm
												switch(i_nHashAlg)
												{
												case HASH_SHA1 :
													nHashSize = 20;
													pbyteHash = new BYTE[20];
													break;

												case HASH_MD2 :
												case HASH_MD5:
													nHashSize = 16;
													pbyteHash = new BYTE[16];
													break;

												default :
													retVal = E_INVALIDFLAGS;
													break;
												}

												if(HashEnd(i_nHashAlg,pvHashCtxt,pbyteHash,nHashSize) == -1)
												{
													retVal = E_HASHENDERR;
												}

											}

										}
									}
								}
							}

						}

						//Now call the smart card to sign this hash. The smart card
						//will correctly create a hash object, and encrypt it
						retVal = i_pVirtualSmartCard->VSM_SignData(pbytePubKeyHandle,dwPubKeyHandleSize,
							pbyteHash,nHashSize,i_nHashAlg,TRUE,NULL,&dwSignatureSize);
						if(retVal == S_OK)
						{
							pbyteSignature = new BYTE[dwSignatureSize];
							if(!pbyteSignature)
							{
								retVal = E_FAIL;
							}
							else
							{
								retVal = i_pVirtualSmartCard->VSM_SignData(pbytePubKeyHandle,dwPubKeyHandleSize,
									pbyteHash,nHashSize,i_nHashAlg,TRUE,pbyteSignature,&dwSignatureSize);
							}
						}
					}
					
					if(pbyteHash)
						delete[]pbyteHash;
				}
			}
		}	//	end		if ( TRUE == i_boolHashData )
		else
		{
			//
			//	Anand	Dec 14, 2000
			//
			//	this else condition is added.
			//	This is the case when the hash flag is set to FALSE using the dll API.
			//	so the input data is the hash which needs to be signed
			//

			//Now call the smart card to sign this hash. The smart card
			//will correctly create a hash object, and encrypt it
			retVal = i_pVirtualSmartCard->VSM_SignData(pbytePubKeyHandle,dwPubKeyHandleSize,
				i_pbyteDataToSign,i_nDataToSignSize,i_nHashAlg,TRUE,NULL,&dwSignatureSize);
			if(retVal == S_OK)
			{
				pbyteSignature = new BYTE[dwSignatureSize];
				if(!pbyteSignature)
				{
					retVal = E_FAIL;
				}
				else
				{
					retVal = i_pVirtualSmartCard->VSM_SignData(pbytePubKeyHandle,dwPubKeyHandleSize,
						i_pbyteDataToSign,i_nDataToSignSize,i_nHashAlg,TRUE,pbyteSignature,&dwSignatureSize);
				}
			}
		}	//	end		else of if ( TRUE == i_boolHashData )
	}
	
		//
		//	Anand	Dec 14, 2000
		//
		//	Added this if condition.
		//	if the boolP7Output is set to fasle using the dll api then it means that the
		//	raw signature is required as output. so no need to do the PKCS7 formating.
		//
		//	NOTE:	Unfortunately the output of this funciton is a string. so the
		//			raw signature is base 64 encoded over here. before passing it
		//			out of PTA we will do the base 64 decoding and pass out the raw
		//			signature.
		//
	if ( FALSE == i_boolP7Output )
	{
		DWORD dwB64P7Size;
		char* pszB64P7 = NULL;

		if(retVal == S_OK)
		{
			_Base64Encode
			(
				(char*)pbyteSignature,
				dwSignatureSize,
				NULL,
				&dwB64P7Size
			);
			pszB64P7 = new char[dwB64P7Size+1];
			if(!pszB64P7)
				retVal = E_FAIL;
			else
			{
				_Base64Encode
				(
					(char*)pbyteSignature,
					dwSignatureSize,
					pszB64P7,
					&dwB64P7Size);
				pszB64P7[dwB64P7Size] = '\0';
				*o_ptbstrSignature = pszB64P7;
				delete[] pszB64P7;
			}

		}
	}	//	end		if ( FLASE == boolP7Output )
	else
	{
		/*Create the pkcs7*/
		if(retVal == S_OK)
		{
			if(i_boolIsAttached)
			{
				retVal = _CreatePKCS7(pbyteSignature, dwSignatureSize, i_nHashAlg, i_pSelectedId->pCertContext, 
					i_pbyteDataToSign,i_nDataToSignSize, pbyteAuthAttr, dwAuthAttrSize, o_ptbstrSignature);
			}
			else
			{
				retVal = _CreatePKCS7(pbyteSignature, dwSignatureSize, i_nHashAlg, i_pSelectedId->pCertContext, 
					NULL, 0, pbyteAuthAttr, dwAuthAttrSize, o_ptbstrSignature);
			}
		}
	}	//	end		else of if ( FLASE == boolP7Output )

	/*Free memory*/
	delete[] pbyteSignature;
	delete[] pbytePubKeyHandle;
	delete[] pbyteAuthAttr;
	delete[] pbyteRevAuthAttr;

	return retVal;
}


HRESULT CPtaEngine::_SignDataWithVSTPM(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, BOOL i_boolHashData, BOOL i_boolP7Output, BOOL i_boolAddAuthAttr, DATE i_dateSignDate, _bstr_t* o_ptbstrSignature)
{
	HRESULT retVal = S_OK;
	HRESULT	hResult =	S_OK;
	/*Obtain the public key identifier for this cert*/
	PBYTE pbytePubKeyHandle = NULL;
	DWORD dwPubKeyHandleSize;
	DWORD dwAuthAttrSize = 0;
	PBYTE pbyteAuthAttr = NULL;
	PBYTE pbyteRevAuthAttr = NULL;
	VS_TSS_Hash*			pVSTSSHash;

	DWORD	dwAlgID	=	0;

	BYTE*						pbyteDataSequence			=	NULL;
	DWORD						dwDataSequenceLen			=	0;

	DWORD						dwTSSVendor;

//	CVirtualSmartCard*		pVirtualSmartCard;

	if ( NULL == _gpVirtualSmartCard )
	{
		_gpVirtualSmartCard = new CVirtualSmartCard;

		retVal =	_gpVirtualSmartCard -> VSM_TPMInitialize
					(
						i_pSelectedId->pAuxCertInfo->tbstrContainerName ,
						VS_TPM_CONTAINER_OPEN,
						m_PTA
					);
		if ( S_OK != retVal )
		{
			return	retVal;
		}
	}

	switch (i_pSelectedId->pAuxCertInfo->nKeySpec)
	{
		case	AT_KEYEXCHANGE:
				dwAlgID =	VS_RSA_KEYX;
				break;
		case	AT_SIGNATURE:
				dwAlgID =	VS_RSA_SIGN;
				break;
		default:
				retVal =	E_INVALIDARG;
				return retVal;
	}

	hResult =	_gpVirtualSmartCard -> VSTPM_CreateHashObject
				(
					&pVSTSSHash
				);
	if ( S_OK != hResult )
	{
		return	hResult;
	}

	// check if we are using Infineon or IBM TSS
	retVal = _gpVirtualSmartCard -> get_VSTPM_TSSVendor(&dwTSSVendor);

	/*Hash and sign the data*/
	BYTE* pbyteSignature = NULL;
	DWORD dwSignatureSize;

	if(retVal == S_OK)
	{
		if ( TRUE == i_boolHashData )
		{
			BYTE* pbyteHash = NULL;
			int nHashSize;
			
			void* pvHashCtxt;
					

			if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
			{
				retVal = E_HASHBEGINERR;
			}
			else
			{
				if(HashData(i_nHashAlg,pvHashCtxt,i_pbyteDataToSign ,i_nDataToSignSize) == -1)
				{
					retVal = E_HASHDATAERR;
				}
				else
				{
					//Allocate memory for the hash algorithm
					switch(i_nHashAlg)
					{
						case HASH_SHA1 :
							nHashSize = 20;
							pbyteHash = new BYTE[20];
							break;

						default :
							retVal = E_INVALIDFLAGS;
							break;
					}

					if(HashEnd(i_nHashAlg,pvHashCtxt,pbyteHash,nHashSize) == -1)
					{
						retVal = E_HASHENDERR;
					}
					else
					{
						//If we need to add authenticated attributes, create them here
						//and hash them. Then sign this hash.
						if(i_boolAddAuthAttr)
						{
							if((retVal = _GetAuthAttr(pbyteHash,nHashSize,i_dateSignDate,NULL,&dwAuthAttrSize)) == S_OK)
							{
								pbyteAuthAttr = (PBYTE)new BYTE[dwAuthAttrSize];
								if(!pbyteAuthAttr)
									retVal = E_FAIL;
								else
								{
									if((retVal = _GetAuthAttr(pbyteHash,nHashSize,i_dateSignDate,pbyteAuthAttr,&dwAuthAttrSize)) == S_OK)
									{
										// Reverse the auth attributes as passing it to the CSet is 
										// reversing it again!!!
										pbyteRevAuthAttr = (PBYTE) new BYTE[dwAuthAttrSize];
										if(!pbyteRevAuthAttr)
											retVal = E_FAIL;
										else
										{
											for(INT i = 0, j = dwAuthAttrSize - 1; j >= 0; i++, j--)
												pbyteRevAuthAttr[i] = pbyteAuthAttr[j];

											//Now put this auth attr blob within a set
											CSet csetAttribs(dwAuthAttrSize, pbyteRevAuthAttr);
											
											//We have the auth attributes. Now we have to hash them.
											if(pbyteHash)
											{
												delete[] pbyteHash;
												pbyteHash = NULL;
											}


											if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
											{	
												retVal = E_HASHBEGINERR;
											}
											else
											{
												if(HashData(i_nHashAlg,pvHashCtxt,csetAttribs.BaseDERBlob->pbData,csetAttribs.BaseDERBlob->cbData) == -1)
												{
													retVal = E_HASHDATAERR;
												}

												//Allocate memory for the hash algorithm
												switch(i_nHashAlg)
												{
													case HASH_SHA1 :
														nHashSize = 20;
														pbyteHash = new BYTE[20];
														break;

													default :
														retVal = E_INVALIDFLAGS;
														break;
												}

												if(HashEnd(i_nHashAlg,pvHashCtxt,pbyteHash,nHashSize) == -1)
												{
													retVal = E_HASHENDERR;
												}

											}

										}
									}
								}
							}

						}

							// If it is Infineon, then we sign the hash value directly. 
							// Otherwise, create DigestInfo sequence and sign it.
						if(dwTSSVendor == INFINEON_TSS)
						{
							hResult =	pVSTSSHash -> SetHashValue
										(
											nHashSize,
											pbyteHash
										);
						} else {

							hResult =	PutDataInSequenceFunc
										(
											pbyteHash,
											nHashSize,
											i_nHashAlg,
											&pbyteDataSequence,
											&dwDataSequenceLen
										);
							if ( S_OK != hResult )
							{
								return	hResult;
							}
							hResult =	pVSTSSHash -> SetHashValue
										(
											dwDataSequenceLen,//nHashSize,
											pbyteDataSequence//pbyteHash
										);
						}

						if ( S_OK != hResult )
						{
							return	hResult;
						}

						retVal =	_gpVirtualSmartCard->VSTPM_SignHash
									(
										pVSTSSHash,
										dwAlgID,
										NULL,
										&dwSignatureSize
									);
						if ( S_OK == retVal )
						{
							pbyteSignature = new BYTE[dwSignatureSize];
							if(!pbyteSignature)
							{
								retVal = E_FAIL;
							}
							else
							{
								retVal = _gpVirtualSmartCard->VSTPM_SignHash
										(
											pVSTSSHash,
											dwAlgID,
											pbyteSignature,
											&dwSignatureSize
										);
							}
						}
					}
					
					if(pbyteHash)
						delete[]pbyteHash;
				}
			}
		}	//	end		if ( TRUE == i_boolHashData )
		else
		{
				// If it is Infineon, then we sign the hash value directly. 
				// Otherwise, create DigestInfo sequence and sign it.
			if(dwTSSVendor == INFINEON_TSS)
			{
				hResult =	pVSTSSHash -> SetHashValue
							(
								i_nDataToSignSize,
								i_pbyteDataToSign
							);

			} else {

				hResult =	PutDataInSequenceFunc
				(
					i_pbyteDataToSign,
					i_nDataToSignSize,
					i_nHashAlg,
					&pbyteDataSequence,
					&dwDataSequenceLen
				);
				if ( S_OK != hResult )
				{
					return	hResult;
				}

				hResult =	pVSTSSHash -> SetHashValue
							(
								dwDataSequenceLen,//i_nDataToSignSize,
								pbyteDataSequence//i_pbyteDataToSign
							);
			}

			if ( S_OK != hResult )
			{
				return	hResult;
			}

			retVal =	_gpVirtualSmartCard->VSTPM_SignHash
						(
							pVSTSSHash,
							dwAlgID,
							NULL,
							&dwSignatureSize
						);
			if ( S_OK == retVal )
			{
				pbyteSignature = new BYTE[dwSignatureSize];
				if(!pbyteSignature)
				{
					retVal = E_FAIL;
				}
				else
				{
					retVal = _gpVirtualSmartCard->VSTPM_SignHash
							(
								pVSTSSHash,
								dwAlgID,
								pbyteSignature,
								&dwSignatureSize
							);
				}
			}
		}	//	end		else of if ( TRUE == i_boolHashData )
	}
	
		//
		//	Anand	Dec 14, 2000
		//
		//	Added this if condition.
		//	if the boolP7Output is set to fasle using the dll api then it means that the
		//	raw signature is required as output. so no need to do the PKCS7 formating.
		//
		//	NOTE:	Unfortunately the output of this funciton is a string. so the
		//			raw signature is base 64 encoded over here. before passing it
		//			out of PTA we will do the base 64 decoding and pass out the raw
		//			signature.
		//
	if ( FALSE == i_boolP7Output )
	{
		DWORD dwB64P7Size;
		char* pszB64P7 = NULL;

		if(retVal == S_OK)
		{
			_Base64Encode
			(
				(char*)pbyteSignature,
				dwSignatureSize,
				NULL,
				&dwB64P7Size
			);
			pszB64P7 = new char[dwB64P7Size+1];
			if(!pszB64P7)
				retVal = E_FAIL;
			else
			{
				_Base64Encode
				(
					(char*)pbyteSignature,
					dwSignatureSize,
					pszB64P7,
					&dwB64P7Size);
				pszB64P7[dwB64P7Size] = '\0';
				*o_ptbstrSignature = pszB64P7;
				delete[] pszB64P7;
			}

		}
	}	//	end		if ( FLASE == boolP7Output )
	else
	{
		/*Create the pkcs7*/
		if(retVal == S_OK)
		{
			if(i_boolIsAttached)
			{
				retVal = _CreatePKCS7(pbyteSignature, dwSignatureSize, i_nHashAlg, i_pSelectedId->pCertContext, 
					i_pbyteDataToSign,i_nDataToSignSize, pbyteAuthAttr, dwAuthAttrSize, o_ptbstrSignature);
			}
			else
			{
				retVal = _CreatePKCS7(pbyteSignature, dwSignatureSize, i_nHashAlg, i_pSelectedId->pCertContext, 
					NULL, 0, pbyteAuthAttr, dwAuthAttrSize, o_ptbstrSignature);
			}
		}
	}	//	end		else of if ( FLASE == boolP7Output )

	/*Free memory*/
	delete[] pbyteSignature;
	delete[] pbytePubKeyHandle;
	delete[] pbyteAuthAttr;
	delete[] pbyteRevAuthAttr;

	if(pbyteDataSequence)
		delete[] pbyteDataSequence;

	return retVal;
}


//
//	Anand	Dec 15, 2000		Start
//
HRESULT CPtaEngine::DecryptData(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToDecrypt, int i_nDataToDecryptLength, PIDLISTNODE i_pSelectedId, BYTE** o_ppbyteOutput, DWORD* o_pdwDecryptedDataLength)
{
	HRESULT retVal = S_OK;

	if(boolIsCapi)
	{
		retVal = _DecryptDataWithMSCapi(i_pbyteDataToDecrypt, i_nDataToDecryptLength, i_pSelectedId, o_ppbyteOutput, o_pdwDecryptedDataLength);
	}
	else
	{
		retVal = _DecryptDataWithVSCapi(i_pVirtualSmartCard, i_pbyteDataToDecrypt, i_nDataToDecryptLength, i_pSelectedId, o_ppbyteOutput, o_pdwDecryptedDataLength);
	}

	return retVal;

}

HRESULT CPtaEngine::_DecryptDataWithVSCapi(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToDecrypt, int i_nDataToDecryptLength, PIDLISTNODE i_pSelectedId, BYTE** o_ppbyteDecryptedData, DWORD* o_pdwDecryptedDataLength)
{
	HRESULT retVal = S_OK;
	/*Obtain the public key identifier for this cert*/
	PBYTE pbytePubKeyHandle = NULL;
	DWORD dwPubKeyHandleSize;

	void*	pvoidContext;

	BYTE*	pbyteBuffer = NULL;

	do
	{
		if ( NULL == i_pSelectedId )
		{
			retVal = E_CERTNOTFOUND;
		}

		if(retVal == S_OK)
		{
			retVal = GetPubKeyIdentifierFromPubKey(
				(i_pSelectedId->pCertContext->pCertInfo->SubjectPublicKeyInfo),
				NULL,&dwPubKeyHandleSize);
			if(retVal == S_OK)
			{
				pbytePubKeyHandle = new BYTE[dwPubKeyHandleSize];
				if(!pbytePubKeyHandle)
					retVal = E_FAIL;
				else
				{
					retVal = GetPubKeyIdentifierFromPubKey(
								i_pSelectedId->pCertContext->pCertInfo->SubjectPublicKeyInfo,
								pbytePubKeyHandle,&dwPubKeyHandleSize);
				}
			}
		}

		if(retVal == S_OK)
		{
			pbyteBuffer = new BYTE [i_nDataToDecryptLength];
			if ( NULL == pbyteBuffer )
			{
				retVal = E_OUTOFMEMORY;
				break;
			}
			*o_pdwDecryptedDataLength = i_nDataToDecryptLength;

			retVal =	i_pVirtualSmartCard -> VSM_DecryptBegin
						(
							pbytePubKeyHandle,
							dwPubKeyHandleSize,
							&pvoidContext
						);
			if ( S_OK != retVal )
			{
				break;
			}

			retVal =	i_pVirtualSmartCard -> VSM_DecryptUpdate
						(
							pvoidContext,
							TRUE,
							i_pbyteDataToDecrypt,
							i_nDataToDecryptLength, 
							pbyteBuffer, 
							o_pdwDecryptedDataLength
						);
			if ( S_OK != retVal )
			{
				break;
			}

			retVal =	i_pVirtualSmartCard -> VSM_DecryptEnd
						(
							pvoidContext
						);
			if ( S_OK != retVal )
			{
				break;
			}

			*o_ppbyteDecryptedData= new BYTE [*o_pdwDecryptedDataLength];
			if ( NULL == *o_ppbyteDecryptedData )
			{
				retVal = E_OUTOFMEMORY;
				break;
			}
			
			::memcpy ((void*)*o_ppbyteDecryptedData, (const void*) pbyteBuffer, *o_pdwDecryptedDataLength);

	/*
			retVal = i_pVirtualSmartCard->VSM_SignData(pbytePubKeyHandle,dwPubKeyHandleSize,
				i_pbyteDataToSign,i_nDataToSignSize,i_nHashAlg,TRUE,NULL,&dwSignatureSize);
			if(retVal == S_OK)
			{
				pbyteSignature = new BYTE[dwSignatureSize];
				if(!pbyteSignature)
				{
					retVal = E_FAIL;
				}
				else
				{
					retVal = i_pVirtualSmartCard->VSM_SignData(pbytePubKeyHandle,dwPubKeyHandleSize,
						i_pbyteDataToSign,i_nDataToSignSize,i_nHashAlg,TRUE,pbyteSignature,&dwSignatureSize);
				}
			}
	*/
		}
	}	while (0);

	if ( NULL != pbyteBuffer )
	{
		delete [] pbyteBuffer;
	}

	return retVal;
}


HRESULT CPtaEngine::_DecryptDataWithMSCapi(PBYTE i_pbyteDataToDecrypt, int i_nDataToDecryptLength, PIDLISTNODE i_pSelectedId, BYTE** o_ppbyteOutput, DWORD* o_pdwDecryptedDataLength)
{
	return	E_NOTIMPL;
}
//
//	Anand	Dec 15, 2000		End
//


HRESULT CPtaEngine::SetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrCertIssDN, _bstr_t& i_tbstrCertSerNum,
		_bstr_t& i_tbstrPrefName, _bstr_t& i_tbstrPrefVal)
{
	HRESULT retVal = S_OK;
	/*Obtain the list of certs from the smart card*/
	PIDLISTNODE pCertsInStore = NULL;
 
	/*Obtain the list of certs*/
	if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM) )
	{
		retVal = _GetCertsFromMSCapi(&pCertsInStore);
	}
	else
	{
		retVal = _GetCertsFromVSCapi(i_pVirtualSmartCard,&pCertsInStore);
	}

	/*Obtain the decoded cert information*/
	if(retVal == S_OK)
	{
		if(pCertsInStore)
			retVal = _GetDecCertInfo(pCertsInStore);
	}

	/*Look at each cert to see if it satisfies the iss and serial number*/
	PIDLISTNODE pCurrNode = pCertsInStore;
	int nCurrNodeIdx = 0;
	while(pCurrNode)
	{
		//if((pCurrNode->pDecCertInfo->tbstrIssuerDN == i_tbstrCertIssDN)
		if((_CheckIfDNGood(pCurrNode->pDecCertInfo->tbstrIssuerDN, i_tbstrCertIssDN) == S_OK)
			&& pCurrNode->pDecCertInfo->tbstrSerNum == i_tbstrCertSerNum)
		{
			/*Set the preference for this cert*/
			if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM) )
			{
				DWORD dwPubKeyIdSize = 0;
				BYTE* pbytePubKeyId = NULL;

				/*Obtain the hash ascii hex of the public key*/
				retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
					NULL,&dwPubKeyIdSize);
				if(retVal == S_OK)
				{
					pbytePubKeyId = (BYTE*)new BYTE[dwPubKeyIdSize];
					if(!pbytePubKeyId)
						retVal = E_FAIL;
				}

				if(retVal == S_OK)
				{
					retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
						pbytePubKeyId,&dwPubKeyIdSize);
				}

				/*Convert to half ascii*/
				_bstr_t tbstrPubKeyId = "";
				if(retVal == S_OK)
				{
					if(!BytesToAscHex(pbytePubKeyId,dwPubKeyIdSize,tbstrPubKeyId))
					{
						retVal = E_FAIL;
						break;
					}
				}

				delete[] pbytePubKeyId;

				
				retVal = _SetMSCapiCertPref(tbstrPubKeyId, i_tbstrPrefName, (TCHAR*)i_tbstrPrefVal,
					lstrlen((TCHAR*)i_tbstrPrefVal)+1);
				break;
			}
			else
			{
				retVal = i_pVirtualSmartCard->VSM_SetCertPref(nCurrNodeIdx, i_tbstrPrefName, (PBYTE)(WCHAR*)i_tbstrPrefVal,
					(i_tbstrPrefVal.length()+1)*sizeof(WCHAR));
				break;
			}
		}
		else
		{
			pCurrNode = pCurrNode->pidlistnodeNext;
			nCurrNodeIdx++;
		}
	}
	
	if(pCurrNode == NULL)
		retVal = E_CERTNOTFOUND;

	/*Free memory*/
	if(pCertsInStore)
	{
		FreeIdList(pCertsInStore);
	}

	return retVal;
}

HRESULT CPtaEngine::GetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrCertIssDN, _bstr_t& i_tbstrCertSerNum,
		_bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal)
{
	HRESULT retVal = S_OK;

	/*Obtain the list of certs from the smart card*/
	PIDLISTNODE pCertsInStore = NULL;

	/*Obtain the list of certs*/
	if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM) )
	{
		retVal = _GetCertsFromMSCapi(&pCertsInStore);
	}
	else
	{
		retVal = _GetCertsFromVSCapi(i_pVirtualSmartCard,&pCertsInStore);
	}

	/*Obtain the decoded cert information*/
	if(retVal == S_OK)
	{
		if(pCertsInStore)
			retVal = _GetDecCertInfo(pCertsInStore);
	}

	/*Look at each cert to see if it satisfies the iss and serial number*/
	PIDLISTNODE pCurrNode = pCertsInStore;
	int nCurrNodeIdx = 0;
	while(pCurrNode)
	{
		if((pCurrNode->pDecCertInfo->tbstrIssuerDN == i_tbstrCertIssDN)
			&& pCurrNode->pDecCertInfo->tbstrSerNum == i_tbstrCertSerNum)
		{
			/*Set the preference for this cert*/
			if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM) )
			{
				DWORD dwPubKeyIdSize = 0;
				BYTE* pbytePubKeyId = NULL;

				/*Obtain the hash ascii hex of the public key*/
				retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
					NULL,&dwPubKeyIdSize);
				if(retVal == S_OK)
				{
					pbytePubKeyId = (BYTE*)new BYTE[dwPubKeyIdSize];
					if(!pbytePubKeyId)
						retVal = E_FAIL;
				}

				if(retVal == S_OK)
				{
					retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
						pbytePubKeyId,&dwPubKeyIdSize);
				}

				/*Convert to half ascii*/
				_bstr_t tbstrPubKeyId = "";
				if(retVal == S_OK)
				{
					if(!BytesToAscHex(pbytePubKeyId,dwPubKeyIdSize,tbstrPubKeyId))
					{
						retVal = E_FAIL;
						break;
					}
				}

				delete[] pbytePubKeyId;

				retVal = _GetMSCapiCertPref(tbstrPubKeyId,i_tbstrPrefName,o_ptbstrPrefVal);
				break;
			}
			else
			{
				retVal = _GetVSCapiCertPref(i_pVirtualSmartCard, nCurrNodeIdx, i_tbstrPrefName, o_ptbstrPrefVal);
				break;
			}
		}
		else
		{
			pCurrNode = pCurrNode->pidlistnodeNext;
			nCurrNodeIdx++;
		}
	}
	
	if(pCurrNode == NULL)
		retVal = E_CERTNOTFOUND;

	/*Free memory*/
	if(pCertsInStore)
	{
		FreeIdList(pCertsInStore);
	}

	return retVal;
}

HRESULT CPtaEngine::_GetVSCapiCertPref(CVirtualSmartCard* i_pVirtualSmartCard, int i_nCertNum, _bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal)
{
	HRESULT retVal = S_OK;
	PBYTE pbytePrefVal = NULL;
	int nPrefValSize;
	
	retVal = i_pVirtualSmartCard->VSM_GetCertPref(i_nCertNum, i_tbstrPrefName, NULL,
		&nPrefValSize);
	if(retVal == S_OK)
	{
		pbytePrefVal = new BYTE[nPrefValSize];
		if(!pbytePrefVal )
			retVal = E_FAIL;
		else
		{
			retVal = i_pVirtualSmartCard->VSM_GetCertPref(i_nCertNum, i_tbstrPrefName, pbytePrefVal,
				&nPrefValSize);
			if(retVal == S_OK)
			{
				*o_ptbstrPrefVal = (WCHAR*)pbytePrefVal;
			}
			else
			{
				*o_ptbstrPrefVal = "";
			}

			delete[] pbytePrefVal;
		}
	}

	return retVal;
}

HRESULT CPtaEngine::_GetMSCapiCertPref(_bstr_t& i_tbstrPubKeyId, _bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal)
{
	HRESULT retVal = S_OK;
	HKEY hkAppCtxt;
	_bstr_t tbstrSubKey(_T(CERTPREF_REG_KEY));

	tbstrSubKey += i_tbstrPubKeyId;

	if(!RegOpenKeyEx(HKEY_CURRENT_USER,(TCHAR*)tbstrSubKey,0,KEY_ALL_ACCESS, &hkAppCtxt))
	{
		
		DWORD dwType;
		DWORD dwSize;

		//Read the value
		if(RegQueryValueEx(hkAppCtxt, (TCHAR*)i_tbstrPrefName, NULL, &dwType, (LPBYTE)NULL, &dwSize))
		{
			*o_ptbstrPrefVal = "";
		}
		else
		{
			TCHAR* tstrVal;
			if((tstrVal = (TCHAR*)malloc(dwSize*sizeof(TCHAR))) == NULL)
			{
				retVal = E_FAIL;
			}
			else
			{
				if(RegQueryValueEx(hkAppCtxt,(TCHAR*)i_tbstrPrefName , NULL, &dwType, (LPBYTE)tstrVal, &dwSize))
				{
					*o_ptbstrPrefVal = "";
				}
				else
				{
					*o_ptbstrPrefVal= (TCHAR*)tstrVal;
				}
				free(tstrVal);
			}
		}

		RegCloseKey(hkAppCtxt);

	}
	else
	{
		*o_ptbstrPrefVal = "";
	}

	return retVal;
					
}

HRESULT CPtaEngine::_SetMSCapiCertPref(_bstr_t& i_tbstrPubKeyId, _bstr_t& i_tbstrPrefName, TCHAR* ptszPrefVal, int i_nPrefValSize)
{
	HRESULT retVal = S_OK;
	
	do
	{
		HKEY hkAppCtxt;
		DWORD dwDisp;
		_bstr_t tbstrSubKey(_T(CERTPREF_REG_KEY));

		tbstrSubKey += i_tbstrPubKeyId;

		if(!RegCreateKeyEx(HKEY_CURRENT_USER,(TCHAR*)tbstrSubKey,0,NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkAppCtxt, &dwDisp))
		{
			if(RegSetValueEx(hkAppCtxt, (TCHAR*)i_tbstrPrefName, NULL, REG_SZ, (LPBYTE)ptszPrefVal, i_nPrefValSize+1))
			{
				retVal = E_UNEXPECTED;
			}		

			RegCloseKey(hkAppCtxt);

		}
		else
		{
			retVal = E_UNEXPECTED;
		}
	}while(0);
	return retVal;
}

/*HRESULT CPtaEngine::GetRoamingProfileParams(_bstr_t& i_tbstrAppCtxtName, _bstr_t& i_tbstrProfName, _bstr_t& i_tbstrProfileIssUniqueId, int i_nNumOfRoamingSrvrs,
							_bstr_t* i_ptbstrRoamingSrvrs, _bstr_t& i_tbstrStorageSrvr, VARIANT* o_pvarWhichSmartCard)*/
HRESULT CPtaEngine::GetRoamingProfileParams(_bstr_t& i_tbstrAppCtxtName, _bstr_t& i_tbstrProfName, _bstr_t& i_tbstrProfileIssUniqueId, 
											_bstr_t& i_tbstrClientInfo, _bstr_t& i_tbstrClientInfoSig, VARIANT* o_pvarWhichSmartCard)
{

	HRESULT retVal = S_OK;
	_bstr_t tbstrProfName = "";

	/*First construct the profile name from the app context and user name*/
	tbstrProfName += i_tbstrProfName;

	/*Add a 's(space) */
	tbstrProfName += USER_NAME_ENDING;

	/*Add the appcontext name*/
	tbstrProfName += i_tbstrAppCtxtName;

	/*Allocate the variants for the array*/
	SAFEARRAYBOUND rgsabound[1];

	rgsabound[0].lLbound = 0;
    //rgsabound[0].cElements = i_nNumOfRoamingSrvrs+3;
	rgsabound[0].cElements = 4;
    
	o_pvarWhichSmartCard->parray = SafeArrayCreate(VT_VARIANT, 1, rgsabound);
	
	if(!o_pvarWhichSmartCard->parray)
	{
		return E_SAFEARRAYCREATEFAILED;
	}

	VARIANT varElem;
	LONG rgIndices[1];

	/*Store the username*/
	varElem.vt = VT_BSTR;
	varElem.bstrVal = tbstrProfName.copy();
	
	rgIndices[0] = 0;
	retVal = SafeArrayPutElement(o_pvarWhichSmartCard->parray, rgIndices, &varElem);
	
	SysFreeString(varElem.bstrVal);

	if (retVal == S_OK)
	{
		varElem.bstrVal =	i_tbstrProfileIssUniqueId.copy();

		rgIndices[0] = 1;
		retVal =	SafeArrayPutElement(o_pvarWhichSmartCard->parray, rgIndices, &varElem);

		SysFreeString(varElem.bstrVal);
	}

	/*Store the client info*/
	if(retVal == S_OK)
	{	
		//varElem.bstrVal = i_tbstrStorageSrvr.copy();
		varElem.bstrVal = i_tbstrClientInfo.copy();
	
		rgIndices[0] = 2;
		retVal = SafeArrayPutElement(o_pvarWhichSmartCard->parray, rgIndices, &varElem);
		
		SysFreeString(varElem.bstrVal);
	}

	/*Store the roaming servers*/
	/*if(retVal == S_OK)
	{
		for(int i=0;i<i_nNumOfRoamingSrvrs; ++i)
		{	
			varElem.bstrVal = (i_ptbstrRoamingSrvrs[i]).copy();
	
			rgIndices[0]++;
			retVal = SafeArrayPutElement(o_pvarWhichSmartCard->parray, rgIndices, &varElem);
		
			SysFreeString(varElem.bstrVal);
		}
	}*/
	
	/*Store the client info*/
	if(retVal == S_OK)
	{	
		//varElem.bstrVal = i_tbstrStorageSrvr.copy();
		varElem.bstrVal = i_tbstrClientInfoSig.copy();
	
		rgIndices[0] = 3;
		retVal = SafeArrayPutElement(o_pvarWhichSmartCard->parray, rgIndices, &varElem);
		
		SysFreeString(varElem.bstrVal);
	}

	if(retVal == S_OK)
	{
		o_pvarWhichSmartCard->vt = (VT_VARIANT|VT_ARRAY);
	}

//	VSPTA_CLEAN_TBSTR(tbstrProfName)

	return retVal;
}

HRESULT CPtaEngine::_InitEngine()
{
	HRESULT retVal = S_OK;
	
	do
	{
		m_hModCapiDll = LoadLibrary("crypt32.dll");
		if(!m_hModCapiDll)
		{
			retVal = E_CRYPT32LOADFAILED; 
			break;
		}

		m_hModAdvapiDll = LoadLibrary("advapi32.dll");
		if(!m_hModAdvapiDll)
		{
			retVal = E_ADVAPI32LOADFAILED; 
			break;
		}

		MSCapi_CertOpenSystemStore = (LPFNCertOpenSystemStore)GetProcAddress(m_hModCapiDll,"CertOpenSystemStoreA");
		if(!MSCapi_CertOpenSystemStore)
		{
			break; //If we could not obtain a pointer to CertOpenSystemStore, it is possible that the machine does not 
				   //have capi 2.0. So we stop here, but it is not an error condition.
		}
		
		MSCapi_CertFreeCertitificateContext = (LPFNCertFreeCertificateContext)GetProcAddress(m_hModCapiDll,"CertFreeCertificateContext");
		if(!MSCapi_CertFreeCertitificateContext)
		{
			retVal = E_CERTFREECERTCTXTLOADFAILED; //This is an error condition because we dont want to have a pointer to only a partial 
													// list of capi functions
			break;
		}

		MSCapi_CertCloseStore = (LPFNCertCloseStore)GetProcAddress(m_hModCapiDll,"CertCloseStore");
		if(!MSCapi_CertCloseStore)
		{
			retVal = E_CERTCLOSESTORELOADFAILED;
			break;
		}

		MSCapi_CertAddEncodedCertificateToStore = (LPFNCertAddEncodedCertificateToStore)GetProcAddress(m_hModCapiDll, "CertAddEncodedCertificateToStore");
		if(!MSCapi_CertAddEncodedCertificateToStore)
		{
			retVal = E_CERTADDENCERTTOSTORELOADFAILED;
			break;
		}

		MSCapi_CertSetCertificateContextProperty = (LPFNCertSetCertificateContextProperty)GetProcAddress(m_hModCapiDll, "CertSetCertificateContextProperty");
		if(!MSCapi_CertSetCertificateContextProperty)
		{
			retVal = E_CERTSETCERTCTXTPROPLOADFAILED;
			break;
		}


		MSCapi_CertSerializeCertificateStoreElement = (LPFNCertSerializeCertificateStoreElement)GetProcAddress(m_hModCapiDll, "CertSerializeCertificateStoreElement");
		if(!MSCapi_CertSerializeCertificateStoreElement)
		{
			retVal = E_CERTSERCERTSTORELEMFAILED;
			break;
		}

		MSCapi_CertDeleteCertificateFromStore = (LPFNCertDeleteCertificateFromStore)GetProcAddress(m_hModCapiDll, "CertDeleteCertificateFromStore");
		if(!MSCapi_CertDeleteCertificateFromStore)
		{
			retVal = E_CERTDELCERTFAILED;
			break;
		}

	}while(0);

	return retVal;
}

HRESULT CPtaEngine::DecodePKCS8AndGetPrivKey(_bstr_t& i_tbstrKeyToImport,PBYTE* o_ppbytePrivKeyBlob, DWORD* o_pdwPrivKeyBlobSize)
{
	HRESULT retVal = S_OK;
	PBYTE pbytePKCS8 = NULL;
	DWORD dwPKCS8Size;
	DWORD dwTheDiff = 0;


	do
	{
		/*Base64 decode the pkcs8*/
		_Base64Decode(i_tbstrKeyToImport,i_tbstrKeyToImport.length(),NULL,&dwPKCS8Size);
		pbytePKCS8 = new BYTE[dwPKCS8Size];
		if(!pbytePKCS8)
		{
			retVal = E_FAIL;
			break;
		}
		
		_Base64Decode(i_tbstrKeyToImport,i_tbstrKeyToImport.length(),(char*)pbytePKCS8,&dwPKCS8Size);
		
		/*Now decode the pkcs8 blob*/
		retVal = _GetPrivKeyFromPKCS8(pbytePKCS8,dwPKCS8Size,o_ppbytePrivKeyBlob, o_pdwPrivKeyBlobSize);
		if(retVal != S_OK)
			break;

	}while(0);


	delete[] pbytePKCS8;
	return retVal;
}

HRESULT CPtaEngine::_GetPrivKeyFromPKCS8(PBYTE i_pbytePKCS8,DWORD i_dwPKCS8Size,PBYTE* o_ppbytePrivKeyBlob, DWORD* o_pdwPrivKeyBlobSize)
{
	HRESULT retVal = S_OK;
	A_RSA_KEY thePrivKey;
	DWORD dwTheDiff = 0;

	do
	{
#ifdef DEBUG
		FILE* fp;
		fp = (FILE*)fopen("tempp8.bin","wb"); 
		for(unsigned int i=0;i<i_dwPKCS8Size; ++i)
		{
			fprintf(fp,"%c",i_pbytePKCS8[i]);
		}
		fclose(fp);
#endif
		CBaseDERCollection cbdcThePKCS12(i_dwPKCS8Size,i_pbytePKCS8);
		CBaseDERHierarchy cbdhThePKCS12(cbdcThePKCS12);
		if ( 0 != cbdhThePKCS12.dwErrorCode )
		{
			retVal =	E_VS_FAIL;
			break;
		}
		
		DERTree* dtCurr = NULL;

		dtCurr = &(cbdhThePKCS12.m_DERTree); //dtCurr points to the pkcs12 sequence.
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != SEQUENCE)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}

		dtCurr = dtCurr->rightDERTree; //dtCurr points to the version universal integer.
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}

		dtCurr = dtCurr->nextDERTree; //dtCurr points to the object identifier sequence for rsaEncryption
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != SEQUENCE)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		
		dtCurr = dtCurr->nextDERTree; //dtCurr points to the octet string containing the p8
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != OCTET_STRING)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}

		CBaseDERCollection cbdcThePKCS8(dtCurr->currentBaseDER->cbData,dtCurr->currentBaseDER->pbData);
		CBaseDERHierarchy cbdhThePKCS8(cbdcThePKCS8);
		if ( 0 != cbdhThePKCS8.dwErrorCode )
		{
			retVal =	E_VS_FAIL;
			break;
		}

		
		dtCurr = &(cbdhThePKCS8.m_DERTree); //dtCurr points to the pkcs12 sequence.
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		
#ifdef DEBUG
		FILE* fp1;
		fp1= (FILE*)fopen("tempp8key.bin","wb"); 
		for(i=0;i<dtCurr->currentBaseDER->BaseDERBlob->cbData; ++i)
		{
			fprintf(fp1,"%c",dtCurr->currentBaseDER->BaseDERBlob->pbData[i]);
		}
		fclose(fp1);
#endif		
		
		if(dtCurr->currentBaseDER->Type != SEQUENCE)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}

		dtCurr = dtCurr->rightDERTree; //dtCurr points to the version universal integer.
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}

		
		dtCurr = dtCurr->nextDERTree; //dtCurr points to the modulus universal integer.
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		//make the A_RSA_KEY's modulus point to this information
		thePrivKey.modulus.len = dtCurr->currentBaseDER->cbData;
		dwTheDiff = dtCurr->currentBaseDER->BaseDERBlob->cbData - dtCurr->currentBaseDER->cbData;

		if(thePrivKey.modulus.len > 1)
		{
			if(*(dtCurr->currentBaseDER->BaseDERBlob->pbData + dwTheDiff))
			{
				thePrivKey.modulus.data = dtCurr->currentBaseDER->BaseDERBlob->pbData + dwTheDiff;
			}
			else
			{
				thePrivKey.modulus.len -- ;
				thePrivKey.modulus.data = dtCurr->currentBaseDER->BaseDERBlob->pbData+dwTheDiff+1;
			}
		}
		else
		{
			thePrivKey.modulus.data = dtCurr->currentBaseDER->BaseDERBlob->pbData;
		}

		dtCurr = dtCurr->nextDERTree; //dtCurr points to the publicExponent
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}

		dtCurr = dtCurr->nextDERTree; //dtCurr points to the privateExponent
		if(!dtCurr)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		if(dtCurr->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = E_INVALIDPKCS8;
			break;
		}
		//make the A_RSA_KEY's exponent point to this information
		thePrivKey.exponent.len = dtCurr->currentBaseDER->cbData;
		dwTheDiff = dtCurr->currentBaseDER->BaseDERBlob->cbData - dtCurr->currentBaseDER->cbData;
		if(thePrivKey.exponent.len > 1)
		{
			if(*(dtCurr->currentBaseDER->BaseDERBlob->pbData + dwTheDiff))
			{
				thePrivKey.exponent.data = dtCurr->currentBaseDER->BaseDERBlob->pbData + dwTheDiff;
			}
			else
			{
				thePrivKey.exponent.len -- ;
				thePrivKey.exponent.data = dtCurr->currentBaseDER->BaseDERBlob->pbData+dwTheDiff+1;
			}
		}
		else
		{
			thePrivKey.exponent.data = dtCurr->currentBaseDER->BaseDERBlob->pbData;
		}

		//Now create a blob out of the RSA_KEY object
		retVal = GetBlobFromKey(&thePrivKey, o_ppbytePrivKeyBlob, o_pdwPrivKeyBlobSize);
		if(retVal != S_OK)
			break;


	}while(0);

	return retVal;
}

HRESULT CPtaEngine::InstallPrivKey(CVirtualSmartCard* i_pVirtualSmartCard,PBYTE i_pbytePrivKeyBlob, DWORD i_dwPrivKeyBlobSize, PBYTE i_pbytePubKeyId)
{
	HRESULT retVal = S_OK;

	do
	{
		BYTE bytePubKeyHash[VS_CSP_SHA1_LEN];
		DWORD dwPubKeyHashSize = VS_CSP_SHA1_LEN;

		/*Call the virtual smart card to install the private key*/
		retVal = i_pVirtualSmartCard->VSM_ImportKey(i_pbytePrivKeyBlob,i_dwPrivKeyBlobSize,i_pbytePubKeyId, 0,NULL,0,0,bytePubKeyHash,&dwPubKeyHashSize);
		if(retVal != S_OK)
			break;


	}while(0);

	return retVal;
}

HRESULT CPtaEngine::SetDefaultCert(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrAppCtxt, _bstr_t& i_tbstrIssuerDN, _bstr_t& i_tbstrSerNum)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrDefCertIssPrefName = APPPREF_DEFCERTISSDN;
	_bstr_t tbstrDefCertSerNumPrefName = APPPREF_DEFCERTSERNUM;
	VARIANT varDefCertIssPref;
	VARIANT varDefCertSerNumPref;

	varDefCertIssPref.vt = VT_ARRAY;
	varDefCertIssPref.parray = NULL;
	varDefCertSerNumPref.vt = VT_ARRAY;
	varDefCertSerNumPref.parray = NULL;

	do
	{
		if(boolIsCapi || (PTA_TPM_MODE == dwIsTPM) )
		{
			/*Store the application preference for the default cert issuerdn*/
			retVal = _SetMSCapiAppPref(i_tbstrAppCtxt, tbstrDefCertIssPrefName, (TCHAR*)i_tbstrIssuerDN,lstrlen((TCHAR*)i_tbstrIssuerDN)+1);
			if(retVal != S_OK)
				break;

			/*Store the application preference for the default cert serial number*/
			retVal = _SetMSCapiAppPref(i_tbstrAppCtxt, tbstrDefCertSerNumPrefName, (TCHAR*)i_tbstrSerNum, lstrlen((TCHAR*)i_tbstrSerNum)+1);
			if(retVal != S_OK)
				break;

		}
		else
		{			
			retVal = VectorFromBstr(i_tbstrIssuerDN, &(varDefCertIssPref.parray));
			if(retVal != S_OK)
				break;

			/*Store the application preference for the default cert issuerdn*/
			retVal = i_pVirtualSmartCard->VSM_SetAppPreference(tbstrDefCertIssPrefName, &varDefCertIssPref, 0);
			if(retVal != S_OK)
				break;

		
			retVal = VectorFromBstr(i_tbstrSerNum, &(varDefCertSerNumPref.parray));
			if(retVal != S_OK)
				break;


			/*Store the application preference for the default cert serial number*/
			retVal = i_pVirtualSmartCard->VSM_SetAppPreference(tbstrDefCertSerNumPrefName, &varDefCertSerNumPref, 0);
			if(retVal != S_OK)
				break;

		}

	}while(0);

	VariantClear(&varDefCertIssPref);
	VariantClear(&varDefCertSerNumPref);

//	VSPTA_CLEAN_TBSTR(tbstrDefCertIssPrefName)
//	VSPTA_CLEAN_TBSTR(tbstrDefCertSerNumPrefName)

	return retVal;
}

HRESULT CPtaEngine::_SetMSCapiAppPref(_bstr_t& i_tbstrAppCtxtName, _bstr_t& i_tbstrPrefName, TCHAR* ptszPrefVal, int i_nPrefValSize)
{
	HRESULT retVal = S_OK;

	do
	{
		HKEY hkAppCtxt;
		DWORD dwDisp;
		_bstr_t tbstrSubKey(_T(APPREF_REG_KEY));

		tbstrSubKey += i_tbstrAppCtxtName;

		if(!RegCreateKeyEx(HKEY_CURRENT_USER,(TCHAR*)tbstrSubKey,0,NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkAppCtxt, &dwDisp))
		{
			if(RegSetValueEx(hkAppCtxt, (TCHAR*)i_tbstrPrefName, NULL, REG_SZ, (LPBYTE)ptszPrefVal, i_nPrefValSize))
			{
				retVal = E_UNEXPECTED;
			}		

			RegCloseKey(hkAppCtxt);

		}
		else
		{
			retVal = E_UNEXPECTED;
		}
	}while(0);


	return retVal;
}


HRESULT CPtaEngine::_GetMSCapiAppPref(_bstr_t& i_tbstrAppCtxt, _bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal)
{
	HRESULT retVal = S_OK;
	HKEY hkAppCtxt;
	_bstr_t tbstrSubKey(_T(APPREF_REG_KEY));

	tbstrSubKey += i_tbstrAppCtxt;

	if(!RegOpenKeyEx(HKEY_CURRENT_USER,(TCHAR*)tbstrSubKey,0,KEY_ALL_ACCESS, &hkAppCtxt))
	{
		
		DWORD dwType;
		DWORD dwSize;

		//Read the value
		if(RegQueryValueEx(hkAppCtxt, (TCHAR*)i_tbstrPrefName, NULL, &dwType, (LPBYTE)NULL, &dwSize))
		{
			*o_ptbstrPrefVal = "";
		}
		else
		{
			TCHAR* tstrVal;
			if((tstrVal = (TCHAR*)malloc(dwSize*sizeof(TCHAR))) == NULL)
			{
				retVal = E_FAIL;
			}
			else
			{
				if(RegQueryValueEx(hkAppCtxt,(TCHAR*)i_tbstrPrefName , NULL, &dwType, (LPBYTE)tstrVal, &dwSize))
				{
					*o_ptbstrPrefVal = "";
				}
				else
				{
					*o_ptbstrPrefVal= (TCHAR*)tstrVal;
				}
				free(tstrVal);
			}
		}

		RegCloseKey(hkAppCtxt);

	}
	else
	{
		*o_ptbstrPrefVal = "";
	}

	return retVal;
					
}

HRESULT CPtaEngine::DecodePKCS12_GetPrivKeyAndCerts(int i_nKeyFileOrBlob,_bstr_t& i_tbstrKeyFileOrBlob,
													_bstr_t& i_tbstrP12Passwd,PBYTE* o_ppbytePrivKeyBlob, DWORD* o_pdwPrivKeyBlobSize,
													PIDLISTNODE* o_ppCertListHead)
{
	HRESULT retVal = S_OK;
	BYTE* pbytePKCS8 = NULL;
	DWORD dwPKCS8Size = 0;

	do
	{
		/*Decode the PKCS12*/
		Pkcs12Info thePKCS12(i_nKeyFileOrBlob, i_tbstrKeyFileOrBlob, i_tbstrP12Passwd);
		if(thePKCS12.m_dwErrCode == E_INTEGRITY_FAIL)
		{
			retVal = E_INVALIDPASSWD;
			break;
		}
		if(thePKCS12.m_dwErrCode != S_OK)
		{
			retVal = thePKCS12.m_dwErrCode;
			break;
		}

		
		/*Obtain the list of certificates from the pkcs12*/
		PIDLISTNODE pidCurrNode = NULL;

		(*o_ppCertListHead) = (PIDLISTNODE)NewCert();
		pidCurrNode = (*o_ppCertListHead);

		for(int i=0;i<thePKCS12.get_NumOfCerts();++i)
		{
			pidCurrNode->pCertContext = (PCERT_CONTEXT)new(CERT_CONTEXT);
			pidCurrNode->pCertContext->cbCertEncoded = thePKCS12.get_CertSize(i);
			if(!pidCurrNode->pCertContext->cbCertEncoded)
			{
				retVal = E_INVALIDCERTSIZE;
				break;
			}
			
			pidCurrNode->pCertContext->pbCertEncoded = new BYTE[pidCurrNode->pCertContext->cbCertEncoded];
			if(!(pidCurrNode->pCertContext->pbCertEncoded))
			{
				retVal = E_FAIL;
				break;
			}
			
			retVal = thePKCS12.GetCert(i, pidCurrNode->pCertContext->pbCertEncoded);
			if(retVal != S_OK)
				break;

			/*Now decode the certificate blob into its components*/
			CCertInfo theCertInfo(pidCurrNode->pCertContext->pbCertEncoded, pidCurrNode->pCertContext->cbCertEncoded);
			pidCurrNode->pCertContext->pCertInfo = theCertInfo.GetCertInfo();
			
			pidCurrNode->pDecCertInfo = new DECCERT_INFO;
			retVal = _DecodeCertInfo(pidCurrNode->pCertContext,pidCurrNode->pDecCertInfo);
			if(retVal != S_OK)
				break;
			
			if(i < thePKCS12.get_NumOfCerts() - 1)
			{
				pidCurrNode->pidlistnodeNext = (PIDLISTNODE)NewCert();
				pidCurrNode = pidCurrNode->pidlistnodeNext;
			}
			else
			{
				pidCurrNode->pidlistnodeNext = NULL;
			}

		}

		if(retVal != S_OK)
			break;

		/*Obtain the private key blob from the pkcs12 blob*/	
		retVal = thePKCS12.GetPKCS8(pbytePKCS8, &dwPKCS8Size);
		if(retVal != S_OK)
			break;
		pbytePKCS8 = (BYTE*)new BYTE[dwPKCS8Size];
		if(!pbytePKCS8)
		{
			retVal = S_OK;
			break;
		}
		retVal = thePKCS12.GetPKCS8(pbytePKCS8, &dwPKCS8Size);
		if(retVal != S_OK)
			break;
		retVal = _GetPrivKeyFromPKCS8(pbytePKCS8,dwPKCS8Size,o_ppbytePrivKeyBlob, o_pdwPrivKeyBlobSize);
		if(retVal != S_OK)
			break;

	}while(0);

	if(retVal != S_OK)
	{
		FreeIdList((*o_ppCertListHead));
		(*o_ppCertListHead) = NULL;
	}

	if(pbytePKCS8)
		delete[] pbytePKCS8;

	return retVal;
}

HRESULT CPtaEngine::ExportP12(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrKeyFile,_bstr_t& i_tbstrPassword,PIDLISTNODE i_pSelectedId)
{
	HRESULT retVal = S_OK;
	A_RSA_KEY thePubKey;
	PBYTE pbytePubKeyBlob = NULL;
	DWORD dwPubKeyBlobLen;
	PBYTE pbytePrivKeyBlob = NULL;
	DWORD dwPrivKeyBlobLen;
	BYTE pbytePubKeyId [20]; // = NULL;
	PBYTE pbyteP12 = NULL;
	DWORD dwP12Len = 0;
	thePubKey.modulus.data = NULL;
	thePubKey.exponent.data = NULL;
	CExportP12			CP12ExportObj;
	BYTE* pbyteContainerContents = NULL;
	DWORD dwContainerContentsLen = 0;
	BOOL bIsKeyExportable = FALSE;

	HANDLE				hP12File		=	NULL;
	BOOL				bResult			=	FALSE;

	DWORD				dwNumOfBytesWritten	=	0;

	_bstr_t				tbstrPath;

	do
	{
	
		//Obtain the public key blob from the certificate
		retVal = _GetRSAKeyFromKeyInfo(i_pSelectedId->pCertContext->pCertInfo->SubjectPublicKeyInfo, &thePubKey);
		if(retVal != S_OK)
			break;
		
		retVal = GetBlobFromKey(&thePubKey,&pbytePubKeyBlob,&dwPubKeyBlobLen);
		if(retVal != S_OK)
			break;

		//Obtain the public key identifier
		retVal = HashPublicKey(&thePubKey,pbytePubKeyId);
		if(retVal != S_OK)
			break;

		//Obtain the container corresponding to this certificate
		retVal = i_pVirtualSmartCard->VSM_GetInformationBlob(i_pSelectedId->pAuxCertInfo->tbstrContainerName, NULL, &dwContainerContentsLen);
		if(retVal != S_OK)
			break;

		pbyteContainerContents = new BYTE [dwContainerContentsLen];

		retVal = i_pVirtualSmartCard->VSM_GetInformationBlob(i_pSelectedId->pAuxCertInfo->tbstrContainerName, pbyteContainerContents, &dwContainerContentsLen);
		if(retVal != S_OK)
			break;

		CSP_Key_Container* pstructContainer = (CSP_Key_Container*)pbyteContainerContents;

		// see which key in this container corresponds to this 
		// public key hash
		if((pstructContainer->structXchg).dwExists == VS_CSP_KEY_EXISTS)
		{
			if(!memcmp((pstructContainer->structXchg).pbytePubKeyHash, pbytePubKeyId,20))
			{
				bIsKeyExportable = (pstructContainer->structXchg).dwExportable;
			}
		}

		if((pstructContainer->structSign).dwExists == VS_CSP_KEY_EXISTS)
		{
			if(!memcmp((pstructContainer->structSign).pbytePubKeyHash, pbytePubKeyId ,20))
			{
				bIsKeyExportable = (pstructContainer->structSign).dwExportable;
			}
		}

	
		if(!bIsKeyExportable)
		{
			retVal = E_P12E_KEYNOTEXPORTABLE;
			break;
		}
	

		//Obtain the private key blob from the virtual smart card
		retVal = i_pVirtualSmartCard->VSM_ExportKey(pbytePubKeyId, VS_CSP_SHA1_LEN, 0,NULL,0,VS_CSP_EXPORT_PRIVATE_KEY,NULL,&dwPrivKeyBlobLen);
		if(retVal != S_OK)
			break;
		
		pbytePrivKeyBlob = (PBYTE)new BYTE[dwPrivKeyBlobLen * sizeof(BYTE)];
		if(!pbytePrivKeyBlob)
		{
			retVal = E_FAIL;
			break;
		}
		
		retVal = i_pVirtualSmartCard->VSM_ExportKey(pbytePubKeyId, VS_CSP_SHA1_LEN, 0,NULL,0,VS_CSP_EXPORT_PRIVATE_KEY,pbytePrivKeyBlob,&dwPrivKeyBlobLen);
		if(retVal != S_OK)
			break;
		
		
		//Call the export class to obtain the p12

		retVal =	CP12ExportObj.Initialize (PKCS12INFO_BYTE_BLOB_P12);
		if(retVal != S_OK)
			break;
		
		retVal =	CP12ExportObj.SetNumberOfCerts (1);
		if(retVal != S_OK)
			break;

		retVal =	CP12ExportObj.SetCertBlob
					(
						0,
						i_pSelectedId->pCertContext->pbCertEncoded,
						i_pSelectedId->pCertContext->cbCertEncoded
					);
		if(retVal != S_OK)
			break;

		retVal =	CP12ExportObj.SetFriendlyName
					(
						i_pSelectedId->pAuxCertInfo->tbstrFrndlyName
					);
		if(retVal != S_OK)
			break;

		retVal =	CP12ExportObj.SetKey
					(
						pbytePrivKeyBlob,
						dwPrivKeyBlobLen,
						pbytePubKeyBlob,
						dwPubKeyBlobLen						
					);
		if(retVal != S_OK)
			break;

		retVal =	CP12ExportObj.SetPassword
					(
						i_tbstrPassword
					);
		if(retVal != S_OK)
			break;

		retVal =	CP12ExportObj.GetP12ByteBlob
					(
						&dwP12Len,
						&pbyteP12
					);
		if(retVal != S_OK)
			break;

/*
		//Write the p12 to the file
		FILE* fp;
		fp = (FILE*)fopen(i_tbstrKeyFile,"wb"); 
		for(unsigned int i=0;i<dwP12Len; ++i)
		{
			fprintf(fp,"%c",pbyteP12[i]);
		}
		fclose(fp);
*/

		GetPathFromFileName
		(
			i_tbstrKeyFile,
			&tbstrPath
		);

		bResult =	CreateRecursiveDirectory (tbstrPath);

		hP12File =	::CreateFile
					(
						i_tbstrKeyFile,
						GENERIC_WRITE | GENERIC_READ,
						0,
						NULL,
						CREATE_NEW,
						FILE_ATTRIBUTE_NORMAL,
						NULL
					);
		if ( INVALID_HANDLE_VALUE == hP12File )
		{
			retVal =	E_CREATEFILEFAILED;
			break;
		}

		bResult =	::WriteFile
					(
						hP12File,
						pbyteP12,
						dwP12Len,
						&dwNumOfBytesWritten,
						NULL
					);
		if ( 0 == bResult )
		{
			retVal =	::GetLastError ();
			break;
		}

	}while(0);

	if(pbyteContainerContents)
		delete[] pbyteContainerContents;

	if(pbytePubKeyBlob)
		delete[] pbytePubKeyBlob;

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbytePrivKeyBlob, dwPrivKeyBlobLen)
	

//	if(pbytePubKeyId)
//		delete[] pbytePubKeyId;

	if(thePubKey.modulus.data)
		delete[] thePubKey.modulus.data;

	if(pbyteP12)
		delete[] pbyteP12;

	if(thePubKey.exponent.data)
		delete[] thePubKey.exponent.data;

	if ( (NULL != hP12File) && (INVALID_HANDLE_VALUE != hP12File) )
	{
		::CloseHandle (hP12File);
	}

	return retVal;
}


// Creates the AuthAtribute DER encoded collection.
// This collection can be used later to form a SET or Tagged Value.
// The digest of the MIMEEntity is one of the members of the AUTHATTRIB struct.
// Signing Time is calculated locally if 'i_dateSignDate' is 0. It is always expected to be in UTC(GMT).
HRESULT CPtaEngine::_GetAuthAttr(PBYTE i_pbyteHash,int i_nHashSize,DATE i_dateSignDate,PBYTE o_pbyteAuthAttr,DWORD* io_pdwAuthAttrSize)
{
	SYSTEMTIME sysTime;
	UDATE udateDate;

	/*
	SEQUENCE {
               OBJECT IDENTIFIER
                 contentType (1 2 840 113549 1 9 3)
              SET {
                 OBJECT IDENTIFIER data (1 2 840 113549 1 7 1)
                 }
              }
	*/
	char *szContentTypeObjID = "1.2.840.113549.1.9.3";

	CObjectIdentifier cobjidContentType(strlen(szContentTypeObjID), (unsigned char *)(szContentTypeObjID));


	CObjectIdentifier cobjidData(strlen(szOID_RSA_data), (unsigned char *)(szOID_RSA_data));

	CSet csetData(cobjidData);

	CBaseDERCollection bdcContentType;
	bdcContentType = cobjidContentType + csetData;
	
	// 1
	CSequence cseqContentType(bdcContentType);

	/*
	          SEQUENCE {
               OBJECT IDENTIFIER
                 signingTime (1 2 840 113549 1 9 5)
               SET {
                 UTCTime '001230003712Z'
                 }
               }
	*/

	char *szSigningTime = "1.2.840.113549.1.9.5";
	CObjectIdentifier cobjidSignTime(strlen(szSigningTime), (unsigned char *)(szSigningTime));
	char szUTCTime[14];

	if(i_dateSignDate == 0)
		GetSystemTime(&sysTime);
	else
	{
		VarUdateFromDate(i_dateSignDate, 0, &udateDate);
		sysTime = udateDate.st;
	}

	_FormatUTCTime(szUTCTime, &sysTime);
	//strcpy(szUTCTime, "010103194943Z");

	CUTCTime cutcSignTime(strlen(szUTCTime), (unsigned char *)szUTCTime);

	CSet	csetSignTime(cutcSignTime);

	CBaseDERCollection	bdcSignTime;
	bdcSignTime = cobjidSignTime + csetSignTime;

	//2
	CSequence cseqSignTime(bdcSignTime);

	/*
	SEQUENCE {
	  OBJECT IDENTIFIER
		messageDigest (1 2 840 113549 1 9 4)
	  SET {
		OCTET STRING
		  Hash of Data
		}
	  }
	*/

	char *szMsgDigestObjId = "1.2.840.113549.1.9.4" ;
	CObjectIdentifier cobjidMsgDigest(strlen(szMsgDigestObjId), (unsigned char *)szMsgDigestObjId) ;

	//New Simder change
	//reverse(aaAuthAttrib->cbMimeEntityDigest, aaAuthAttrib->pbMimeEntityDigest) ;

	COctetString cosMsgDigest(i_nHashSize, (unsigned char *)i_pbyteHash) ;

	CSet csMsgDigest(cosMsgDigest) ;

	CBaseDERCollection cbdcMsgDigest ;

	cbdcMsgDigest = cobjidMsgDigest + csMsgDigest ;

	//3
	CSequence csqMsgDigest(cbdcMsgDigest) ;

	
	CBaseDERCollection bdcAuthAttribute;

	bdcAuthAttribute = cseqContentType + cseqSignTime + csqMsgDigest;

	*io_pdwAuthAttrSize = bdcAuthAttribute.BaseDERBlob->cbData;
	if(o_pbyteAuthAttr)
	{
		memcpy(o_pbyteAuthAttr, bdcAuthAttribute.BaseDERBlob->pbData, *io_pdwAuthAttrSize) ;
	}

	return 0;
}


void CPtaEngine::_FormatUTCTime(char *szUTCTime, LPSYSTEMTIME i_pSystime)
{
	char szTemp[4];
	char szTemp1[4];
	int temp;

	//YYMMDDHHMMSSZ

	//YY
	temp = i_pSystime->wYear % 100;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcpy(szUTCTime, szTemp1);
	}
	else
	{
		strcpy(szUTCTime, szTemp);
	}
		
	//MM Month (1 - 12; January = 1)
	temp = i_pSystime->wMonth;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//DD
	temp = i_pSystime->wDay;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//HH
	temp = i_pSystime->wHour;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//MM
	temp = i_pSystime->wMinute;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//SS
	temp = i_pSystime->wSecond;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//Z
	strcat(szUTCTime, "Z");
}


HRESULT CPtaEngine::ExportProfile(CVirtualSmartCard* i_pVirtualSmartCard, UINT nExportFlags, PBYTE i_pbPassword, DWORD i_dwPassword, _bstr_t& o_tbstrProfileData)
{
	HRESULT retVal = S_OK;
	BOOL bCertExport = FALSE, bKeyExport = FALSE;
	PIDLISTNODE pCurrNode = NULL, pCertsInStore = NULL;
	CSequence CSeqAllCertsInfo, CSeqOneCertInfo, CSeqCertificateData, CSeqPrivateKeyData;
	CSequence CSeqOneCertPref, CSeqOnePrivateKey, CSeqAllPrivateKeys, CSeqExportedProfileWithSalt;
	CSequence CSeqAllInfoBlobs, CSeqOneInfoBlob, CSeqInfoBlobData;
	BYTE *pbKey = NULL, pbSalt[8], *pbEncProfileData = NULL, *pbTemp = NULL, *pbytePubKeyId = NULL, *pbytePrivKeyBlob = NULL;
	BYTE *pbyteContainerContents = NULL;
	DWORD dwNumCertPrefs = 0, dwCertNum = 0, dwRenewed = 0, dwKey = 0, dwSalt = 8, dwTemp = 0, dwB64Size = 0;
	DWORD dwPrivKeyBlobLen = 0, dwPubKeyIdSize = 0, dwNumPvtKeys = 0, dwNumInfoBlobs = 0, dwContainerContentsLen = 0;
	UINT nEncProfileDataLen = 0;
	ITEM ItemRC4Key;
	int	nResult	= 9999;
	void* pvoidEncryptContext = NULL;
	char *pszB64Data = NULL;
	
	do
	{
		if(nExportFlags & EXPORT_CERTS)
		{			
			bCertExport = TRUE;

			retVal = _GetCertsFromVSCapi(i_pVirtualSmartCard, &pCertsInStore);
			if(retVal != S_OK)
				break;

			if(!pCertsInStore)
			{
				retVal = E_FAIL;
				break;
			}
			
			if(pCertsInStore)
				retVal = _GetDecCertInfo(pCertsInStore);
			
			retVal = _GetAuxCertInfo(i_pVirtualSmartCard, _bstr_t(""), pCertsInStore);
			if(retVal != S_OK)
				break;

			pCurrNode = pCertsInStore;
			while(pCurrNode)
			{
				CSequence CSeqAllCertPrefs;

				// Add this certificate to the sequence of certs
				COctetString CosCertificateBlob(pCurrNode->pCertContext->cbCertEncoded, pCurrNode->pCertContext->pbCertEncoded);

				// Add the certificate preferences now
				if(pCurrNode->pAuxCertInfo->tbstrFrndlyName != _bstr_t(""))
				{
					COctetString CosFrndlyName(lstrlen(CERTPREF_FRNDLYNAME), (PBYTE)CERTPREF_FRNDLYNAME);
					COctetString CosFrndlyNameValue(lstrlen(pCurrNode->pAuxCertInfo->tbstrFrndlyName), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrFrndlyName);

					CSeqOneCertPref = CosFrndlyName;
					CSeqOneCertPref += CosFrndlyNameValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;
				}

				if(pCurrNode->pAuxCertInfo->tbstrDispString != _bstr_t(""))
				{
					COctetString CosDispString(lstrlen(CERTPREF_DISPSTRING), (PBYTE)CERTPREF_DISPSTRING);
					COctetString CosDispStringValue(lstrlen(pCurrNode->pAuxCertInfo->tbstrDispString), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrDispString);

					CSeqOneCertPref = CosDispString;
					CSeqOneCertPref += CosDispStringValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;
				}

				if(pCurrNode->pAuxCertInfo->tbstrLogoUrl != _bstr_t(""))
				{
					COctetString CosLogoUrl(lstrlen(CERTPREF_LOGOURL), (PBYTE)CERTPREF_LOGOURL);
					COctetString CosLogoUrlValue(lstrlen(pCurrNode->pAuxCertInfo->tbstrLogoUrl), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrLogoUrl);

					CSeqOneCertPref = CosLogoUrl;
					CSeqOneCertPref += CosLogoUrlValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;
				}

				if(pCurrNode->pAuxCertInfo->tbstrTextureUrl != _bstr_t(""))
				{
					COctetString CosTextureUrl(lstrlen(CERTPREF_TEXTUREURL), (PBYTE)CERTPREF_TEXTUREURL);
					COctetString CosTextureUrlValue(lstrlen(pCurrNode->pAuxCertInfo->tbstrTextureUrl), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrTextureUrl);

					CSeqOneCertPref = CosTextureUrl;
					CSeqOneCertPref += CosTextureUrlValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;
				}

				dwRenewed = pCurrNode->pAuxCertInfo->boolRenewed;
				if(dwRenewed != 0)
				{
					COctetString CosRenewed(lstrlen(CERTPREF_RENEWED), (PBYTE)CERTPREF_RENEWED);
					COctetString CosRenewedValue(sizeof(DWORD), (PBYTE)&dwRenewed);

					CSeqOneCertPref = CosRenewed;
					CSeqOneCertPref += CosRenewedValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;
				}
				
				if(pCurrNode->pAuxCertInfo->tbstrContainerName != _bstr_t(""))
				{
					COctetString CosContainerName(lstrlen(CERTPREF_CONTAINER_NAME), (PBYTE)CERTPREF_CONTAINER_NAME);
					COctetString CosContainerNameValue(lstrlen(pCurrNode->pAuxCertInfo->tbstrContainerName), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrContainerName);

					CSeqOneCertPref = CosContainerName;
					CSeqOneCertPref += CosContainerNameValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;

					// Check if there is an information blob associated with this container name,
					// this information blob will map the container name to the 'CSP_Key_Container' needed
					// for making a CAPI compliant cert install
					if(i_pVirtualSmartCard->VSM_GetInformationBlob(pCurrNode->pAuxCertInfo->tbstrContainerName, NULL, &dwContainerContentsLen) == S_OK)
					{
						pbyteContainerContents = new BYTE [dwContainerContentsLen];
						if(i_pVirtualSmartCard->VSM_GetInformationBlob(pCurrNode->pAuxCertInfo->tbstrContainerName, pbyteContainerContents, &dwContainerContentsLen) == S_OK)
						{
							COctetString CosInfoBlobName(lstrlen((TCHAR*)pCurrNode->pAuxCertInfo->tbstrContainerName), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrContainerName);
							COctetString CosInfoBlobValue(dwContainerContentsLen, pbyteContainerContents);

							CSeqOneInfoBlob = CosInfoBlobName;
							CSeqOneInfoBlob += CosInfoBlobValue;

							CSeqAllInfoBlobs += CSeqOneInfoBlob;

							dwNumInfoBlobs++;
						}

						if(pbyteContainerContents)
						{
							delete [] pbyteContainerContents;
							pbyteContainerContents = NULL;
						}
					}
				}

				if(pCurrNode->pAuxCertInfo->tbstrCertStore != _bstr_t(""))
				{
					COctetString CosCertStoreName(lstrlen(CERTPREF_STORE), (PBYTE)CERTPREF_STORE);
					COctetString CosCertStoreNameValue(lstrlen(pCurrNode->pAuxCertInfo->tbstrCertStore), (PBYTE)(TCHAR*)pCurrNode->pAuxCertInfo->tbstrCertStore);

					CSeqOneCertPref = CosCertStoreName;
					CSeqOneCertPref += CosCertStoreNameValue;

					CSeqAllCertPrefs += CSeqOneCertPref;
					dwNumCertPrefs++;
				}

				CUniversalInteger CuiNumCertPrefs(sizeof(DWORD), (PBYTE)&dwNumCertPrefs);

				CSeqOneCertInfo = CosCertificateBlob;

				// If any preferences are present add them
				if(dwNumCertPrefs > 0)
				{
					CSeqOneCertInfo += CuiNumCertPrefs;
					CSeqOneCertInfo += CSeqAllCertPrefs;
				}

				CSeqAllCertsInfo += CSeqOneCertInfo;
		
				pCurrNode = pCurrNode->pidlistnodeNext;
				dwCertNum++;
				dwNumCertPrefs = 0;
			}
			
			// Construct the sequence for certificate information
			COctetString CosCertificate(lstrlen(CERTIFICATE_STRING), (PBYTE)CERTIFICATE_STRING);
			CUniversalInteger CuiNumOfCerts(sizeof(DWORD), (PBYTE)&dwCertNum);

			CSeqCertificateData = CosCertificate;
			CSeqCertificateData += CuiNumOfCerts;
			CSeqCertificateData += CSeqAllCertsInfo;

		} // if(nExportFlags & EXPORT_CERTS)


		if(nExportFlags & EXPORT_KEYS)
		{
			bKeyExport = TRUE;

			pCurrNode = pCertsInStore;
			while(pCurrNode)
			{
				/*Obtain the public key identifier for the public key in the cert*/
				retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
					NULL, &dwPubKeyIdSize);
				if(retVal != S_OK)
					break;

				pbytePubKeyId = new BYTE[dwPubKeyIdSize];
				if(!pbytePubKeyId)
				{
					retVal = E_FAIL;
					break;
				}
				
				retVal = GetPubKeyIdentifierFromPubKey(pCurrNode->pCertContext->pCertInfo->SubjectPublicKeyInfo,
							pbytePubKeyId, &dwPubKeyIdSize);
				if(retVal != S_OK)
					break;
				
				/*Get the private key corresponding to this public key*/
				retVal = i_pVirtualSmartCard->VSM_IsPrivKeyAvailable(pbytePubKeyId, dwPubKeyIdSize);
				if(retVal == S_OK)
				{
					retVal = i_pVirtualSmartCard->VSM_ExportKey(pbytePubKeyId, dwPubKeyIdSize, 0, NULL, 0, VS_CSP_EXPORT_PRIVATE_KEY, NULL, &dwPrivKeyBlobLen);
					if(retVal != S_OK)
						break;
			
					pbytePrivKeyBlob = (PBYTE)new BYTE[dwPrivKeyBlobLen * sizeof(BYTE)];
					if(!pbytePrivKeyBlob)
					{
						retVal = E_FAIL;
						break;
					}
			
					retVal = i_pVirtualSmartCard->VSM_ExportKey(pbytePubKeyId, dwPubKeyIdSize, 0, NULL, 0, VS_CSP_EXPORT_PRIVATE_KEY, pbytePrivKeyBlob, &dwPrivKeyBlobLen);
					if(retVal != S_OK)
						break;

					COctetString CosAssociatedHash(dwPubKeyIdSize, pbytePubKeyId);
					COctetString CosPrivateKey(dwPrivKeyBlobLen, pbytePrivKeyBlob);

					CSeqOnePrivateKey = CosAssociatedHash;
					CSeqOnePrivateKey += CosPrivateKey;

					CSeqAllPrivateKeys += CSeqOnePrivateKey;
					
					VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbytePrivKeyBlob, dwPrivKeyBlobLen)

					memset(CosPrivateKey.pbData, CosPrivateKey.cbData, 0);
					memset(CSeqOnePrivateKey.pbData, CSeqOnePrivateKey.cbData, 0);
					
					dwNumPvtKeys++;	
				}
							
				delete[] pbytePubKeyId;				
				pCurrNode = pCurrNode->pidlistnodeNext;

				if(retVal != S_OK && retVal != E_KEYDOESNOTEXIST)
					break;

			}	// while(pCurrNode)

			if(retVal != S_OK && retVal != E_KEYDOESNOTEXIST)
				break;

			// Construct the sequence for private key information
			COctetString CosPrivateKey(lstrlen(PRIVATEKEY_STRING), (PBYTE)PRIVATEKEY_STRING);
			CUniversalInteger CuiNumOfPvtKeys(sizeof(DWORD), (PBYTE)&dwNumPvtKeys);

			CSeqPrivateKeyData = CosPrivateKey;
			CSeqPrivateKeyData += CuiNumOfPvtKeys;
			CSeqPrivateKeyData += CSeqAllPrivateKeys;

			memset(CSeqAllPrivateKeys.pbData, CSeqAllPrivateKeys.cbData, 0);

		} // if(nExportFlags & EXPORT_KEYS)

		
		// If unknown flags were specified return error
		if(!bCertExport && !bKeyExport)
		{
			retVal = E_INVALIDFLAGS;
			break;
		}


		// Create the ASN.1 for the exported profile data
		CSequence CSeqExportedProfile;

		// Version number of the export format
		DWORD dwMajorVersion = 1, dwMinorVersion = 0;
		CUniversalInteger CuiMajorVersion(sizeof(DWORD), (BYTE*)&dwMajorVersion);
		CUniversalInteger CuiMinorVersion(sizeof(DWORD), (BYTE*)&dwMinorVersion);

		// Create the version number sequence
		CSequence CSeqVerNum = CuiMajorVersion + CuiMinorVersion;

		CSeqExportedProfile += CSeqVerNum;

		if(bCertExport)
			CSeqExportedProfile += CSeqCertificateData;

		if(bKeyExport)
			CSeqExportedProfile += CSeqPrivateKeyData;

		if(dwNumInfoBlobs > 0)
		{
			// Construct the sequence for information blobs
			COctetString CosInformationBlob(lstrlen(INFORMATION_BLOB), (PBYTE)INFORMATION_BLOB);
			CUniversalInteger CuiNumOfInfoBlobs(sizeof(DWORD), (PBYTE)&dwNumInfoBlobs);

			CSeqInfoBlobData = CosInformationBlob;
			CSeqInfoBlobData += CuiNumOfInfoBlobs;
			CSeqInfoBlobData += CSeqAllInfoBlobs;

			CSeqExportedProfile += CSeqInfoBlobData;
		}

#if 0
		DWORD dwBytesWritten;
		HANDLE hTemp = CreateFile("c:\\temp\\prof.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		
		WriteFile(hTemp, (CSeqExportedProfile.BaseDERBlob)->pbData, (CSeqExportedProfile.BaseDERBlob)->cbData, &dwBytesWritten, NULL);

		CloseHandle(hTemp);
#endif

		// Encrypt the data using the password. Password is constructed using Hash(Password) + Random data.
		// This is again hashed and first 16 bytes are used as the RC4 key
		// SHA1Hash [ SHA1Hash[password] + 8 bytes random data or salt ]
		retVal = GenerateRandomBlock(pbSalt, dwSalt);
		if(retVal != S_OK)
			break;

		retVal = _CreateKeyFromPasswdAndSalt(i_pbPassword, i_dwPassword, pbSalt, dwSalt, &pbKey, &dwKey);
		if(retVal != S_OK)
			break;

		// Encrypt the profile data using the key
		ItemRC4Key.data = pbKey;
		ItemRC4Key.len = dwKey;

		nEncProfileDataLen = (CSeqExportedProfile.BaseDERBlob)->cbData;
		pbEncProfileData = (PBYTE)malloc(nEncProfileDataLen);
		if(!pbEncProfileData)
		{
			retVal = NTE_FAIL;
			break;
		}

		nResult = SymEncryptDataBegin(SYM_RC4, &ItemRC4Key, 0, &pvoidEncryptContext, NULL, 0);
		if(nResult != 0)
		{
			retVal = E_ENCRYPTFAIL;
			break;
		}
		
		nResult = SymEncryptDataUpdate(pvoidEncryptContext, (CSeqExportedProfile.BaseDERBlob)->pbData,
						(CSeqExportedProfile.BaseDERBlob)->cbData, pbEncProfileData, &nEncProfileDataLen);
		if(nResult != 0)
		{
			retVal = E_ENCRYPTFAIL;
			break;
		}

		nResult = SymEncryptDataEnd(pvoidEncryptContext, (unsigned char*) pbTemp, (unsigned int*) &dwTemp);
		if(nResult != 0)
		{
			retVal = E_ENCRYPTFAIL;
			break;
		}

		COctetString CosSalt(dwSalt, pbSalt);
		COctetString CosEncryptedProfile(nEncProfileDataLen, pbEncProfileData);

		CSeqExportedProfileWithSalt += CosSalt;
		CSeqExportedProfileWithSalt += CosEncryptedProfile;

#if 0
		hTemp = CreateFile("c:\\temp\\profsalt.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		
		WriteFile(hTemp, (CSeqExportedProfileWithSalt.BaseDERBlob)->pbData, (CSeqExportedProfileWithSalt.BaseDERBlob)->cbData, &dwBytesWritten, NULL);

		CloseHandle(hTemp);
#endif

		// Base64 encode the profile data
		_Base64Encode((char*)(CSeqExportedProfileWithSalt.BaseDERBlob)->pbData, (CSeqExportedProfileWithSalt.BaseDERBlob)->cbData, NULL, &dwB64Size);
		pszB64Data = (char*)malloc(dwB64Size+1);
		if(!pszB64Data)
		{
			retVal = NTE_FAIL;
			break;
		}

		_Base64Encode((char*)(CSeqExportedProfileWithSalt.BaseDERBlob)->pbData, (CSeqExportedProfileWithSalt.BaseDERBlob)->cbData, pszB64Data, &dwB64Size);
		pszB64Data[dwB64Size] = '\0';
		o_tbstrProfileData = pszB64Data;
		
	}while(0);


	if(pCertsInStore)
		FreeIdList(pCertsInStore);

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbKey, dwKey)

	if(pbEncProfileData)
	{
		free(pbEncProfileData);
		pbEncProfileData = NULL;
	}

	if(pszB64Data)
	{
		free(pszB64Data);
		pszB64Data = NULL;
	}

	return retVal;
}



HRESULT CPtaEngine::ImportProfile(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbPassword, DWORD i_dwPassword, _bstr_t& i_tbstrB64ProfileData)
{
	HRESULT hr = S_OK;
	BYTE *pbEncryptedProfile = NULL, *pbKey = NULL, *pbDecryptedProfile = NULL, *pbData = NULL;
	DWORD dwEncryptedProfile = 0, dwKey = 0, dwMajorVerNum = 0, dwMinorVerNum = 0;
	UINT nDecryptedProfile = 0;
	int	nResult	= 9999;
	ITEM ItemRC4Key;
	void* pvoidDecryptContext = NULL;
	
	do
	{
		// Base64 decode the profile
		_Base64Decode(i_tbstrB64ProfileData, i_tbstrB64ProfileData.length(), NULL, &dwEncryptedProfile);
		pbEncryptedProfile = new BYTE[dwEncryptedProfile];
		if(!pbEncryptedProfile)
		{
			hr = E_FAIL;
			break;
		}

		_Base64Decode(i_tbstrB64ProfileData, i_tbstrB64ProfileData.length(), (char*)pbEncryptedProfile, &dwEncryptedProfile);

		// Decode the profile data
		CBaseDERCollection cbdcEncProfile(dwEncryptedProfile, pbEncryptedProfile);
		CBaseDERHierarchy cbdhEncProfile(cbdcEncProfile);

		if(cbdhEncProfile.dwErrorCode)
		{
			hr = E_INVALIDPROFILE;
			break;
		}

		// Point to the top level sequence
		_DERTree *pProfileDTree = &(cbdhEncProfile.m_DERTree);
		CHECK_PROFILE(pProfileDTree, SEQUENCE)

		_DERTree *pSaltDTree = pProfileDTree->rightDERTree;
		CHECK_PROFILE(pSaltDTree, OCTET_STRING)

		_DERTree *pEncProfDTree = pSaltDTree->nextDERTree;
		CHECK_PROFILE(pEncProfDTree, OCTET_STRING)

		// Construct the key for decrypting the profile
		hr = _CreateKeyFromPasswdAndSalt(i_pbPassword, i_dwPassword, pSaltDTree->currentBaseDER->pbData, pSaltDTree->currentBaseDER->cbData, 
										&pbKey, &dwKey);
		if(hr != S_OK)
			break;

		// Decrypt the profile
		ItemRC4Key.data = pbKey;
		ItemRC4Key.len = dwKey;

		nDecryptedProfile = pEncProfDTree->currentBaseDER->cbData;
		pbDecryptedProfile = new BYTE[nDecryptedProfile];
		if(!pbDecryptedProfile)
		{
			hr = E_FAIL;
			break;
		}

		nResult = SymDecryptDataBegin(SYM_RC4, &ItemRC4Key, 0, &pvoidDecryptContext, NULL, 0);
		if(nResult != 0)
		{
			hr = E_DECRYPTFAIL;
			break;
		}

		nResult = SymDecryptDataUpdate(pvoidDecryptContext, pEncProfDTree->currentBaseDER->pbData,
								pEncProfDTree->currentBaseDER->cbData, pbDecryptedProfile, &nDecryptedProfile);
		if(nResult != 0)
		{
			hr = E_DECRYPTFAIL;
			break;
		}

		nResult = SymDecryptDataEnd(pvoidDecryptContext, pbDecryptedProfile, &nDecryptedProfile);
		if(nResult != 0)
		{
			hr = E_DECRYPTFAIL;
			break;
		}

		// Decode the decrypted profile data
		CBaseDERCollection cbdcDecProfile(nDecryptedProfile, pbDecryptedProfile);
		CBaseDERHierarchy cbdhDecProfile(cbdcDecProfile);

		if(cbdhDecProfile.dwErrorCode)
		{
			hr = E_INVALIDPROFILE;
			break;
		}

		_DERTree *pDecProfileDTree = &(cbdhDecProfile.m_DERTree);
		CHECK_PROFILE(pDecProfileDTree, SEQUENCE)

		_DERTree *pVersionDTree = pDecProfileDTree->rightDERTree;
		CHECK_PROFILE(pVersionDTree, SEQUENCE)

		_DERTree *pMajorVerDTree = pVersionDTree->rightDERTree;
		CHECK_PROFILE(pMajorVerDTree, UNIVERSAL_INTEGER)

		_DERTree *pMinorVerDTree = pMajorVerDTree->nextDERTree;
		CHECK_PROFILE(pMinorVerDTree, UNIVERSAL_INTEGER)

		pbData = new BYTE[pMajorVerDTree->currentBaseDER->cbData];
		if(!pbData)
		{
			hr = E_FAIL;
			break;
		}

		memcpy(pbData, pMajorVerDTree->currentBaseDER->pbData, pMajorVerDTree->currentBaseDER->cbData);

		dwMajorVerNum = (DWORD)(*pbData);

		memcpy(pbData, pMinorVerDTree->currentBaseDER->pbData, pMinorVerDTree->currentBaseDER->cbData);

		dwMinorVerNum = (DWORD)(*pbData);

		if(dwMajorVerNum != 1 && dwMinorVerNum != 0)
		{
			hr = E_INVALIDVERSION;
			break;
		}

		delete [] pbData;
		pbData = NULL;

		_DERTree *pInfoDTree = pVersionDTree->nextDERTree;

		while(pInfoDTree)
		{
			CHECK_PROFILE(pInfoDTree, SEQUENCE)

			_DERTree *pInfoTypeDTree = pInfoDTree->rightDERTree;
			CHECK_PROFILE(pInfoTypeDTree, OCTET_STRING)

			hr = _UpdateProfile(i_pVirtualSmartCard, pInfoTypeDTree);
			if(hr != S_OK)
				break;

			pInfoDTree = pInfoDTree->nextDERTree;
		}
	
	}while(0);

	if(pbEncryptedProfile)
	{
		delete [] pbEncryptedProfile;
		pbEncryptedProfile = NULL;
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbKey, dwKey)

	if(pbDecryptedProfile)
	{
		delete [] pbDecryptedProfile;
		pbDecryptedProfile = NULL;
	}

	if(pbData)
	{
		delete [] pbData;
		pbData = NULL;
	}

	return hr;
}


HRESULT CPtaEngine::_UpdateProfile(CVirtualSmartCard* i_pVirtualSmartCard, _DERTree *pInfoTypeDTree)
{
	HRESULT hr = S_OK;
	VARIANT varCertToAdd;
	UINT nCertNum = 0;
	BYTE *pbyteCertToInstall = NULL, *pbCertPrefName = NULL, *pbCertPrefValue = NULL;
	_bstr_t tbstrCertPrefName, tbstrCertPrefValue;

	do
	{
		if(memcmp(pInfoTypeDTree->currentBaseDER->pbData, CERTIFICATE_STRING, pInfoTypeDTree->currentBaseDER->cbData) == 0)
		{
			// Certificates are present

			// Skip the number of certificates
			_DERTree *pNumCertsDTree = pInfoTypeDTree->nextDERTree;
			CHECK_PROFILE(pNumCertsDTree, UNIVERSAL_INTEGER)

			_DERTree *pCertInfoSeqDTree = pNumCertsDTree->nextDERTree;
			CHECK_PROFILE(pCertInfoSeqDTree, SEQUENCE)

			_DERTree* pCertInfoDTree = pCertInfoSeqDTree->rightDERTree;

			while(pCertInfoDTree)
			{
				CHECK_PROFILE(pCertInfoDTree, SEQUENCE)

				_DERTree *pCertBlobDTree = pCertInfoDTree->rightDERTree;
				CHECK_PROFILE(pCertBlobDTree, OCTET_STRING)

				varCertToAdd.vt = VT_ARRAY;
				varCertToAdd.parray = SafeArrayCreateVector(VT_UI1, 0, pCertBlobDTree->currentBaseDER->cbData);
				if(varCertToAdd.parray == NULL)
				{
					hr = E_SAFEARRAYCREATEVECTFAILED;
					break;
				}

				if(SafeArrayAccessData(varCertToAdd.parray, (void HUGEP **)&pbyteCertToInstall) != S_OK)
				{
					hr = E_SAFEARRAYACCDATAFAILED;
					break;
				}

				memcpy(pbyteCertToInstall, pCertBlobDTree->currentBaseDER->pbData, pCertBlobDTree->currentBaseDER->cbData);

				SafeArrayUnaccessData(varCertToAdd.parray);
				hr = i_pVirtualSmartCard->VSM_AddCert(&varCertToAdd, &nCertNum);
				SafeArrayDestroy(varCertToAdd.parray);

				if(hr == E_VS_CERT_ALREADY_EXISTS)
				{
					hr = S_OK;
					pCertInfoDTree = pCertInfoDTree->nextDERTree;
					continue;
				}
					
				if(hr == S_OK)
				{
					// Check if we have any certificate preferences
					_DERTree *pNumCertPrefs = pCertBlobDTree->nextDERTree;
					if(pNumCertPrefs)
					{
						// Some preferences are present
						CHECK_PROFILE(pNumCertPrefs, UNIVERSAL_INTEGER)

						_DERTree *pCertPrefSeqDTree = pNumCertPrefs->nextDERTree;
						CHECK_PROFILE(pCertPrefSeqDTree, SEQUENCE)

						_DERTree *pCertPrefDTree = pCertPrefSeqDTree->rightDERTree;

						while(pCertPrefDTree)
						{
							CHECK_PROFILE(pCertPrefDTree, SEQUENCE)

							_DERTree *pPrefNameDTree = pCertPrefDTree->rightDERTree;
							CHECK_PROFILE(pPrefNameDTree, OCTET_STRING)

							_DERTree *pPrefValueDTree = pPrefNameDTree->nextDERTree;
							CHECK_PROFILE(pPrefValueDTree, OCTET_STRING)

							pbCertPrefName = new BYTE[pPrefNameDTree->currentBaseDER->cbData + 1];
							if(!pbCertPrefName)
							{
								hr = E_FAIL;
								break;
							}

							memcpy(pbCertPrefName, pPrefNameDTree->currentBaseDER->pbData, pPrefNameDTree->currentBaseDER->cbData);
							pbCertPrefName[pPrefNameDTree->currentBaseDER->cbData] = '\0';

							pbCertPrefValue = new BYTE[pPrefValueDTree->currentBaseDER->cbData + 1];
							if(!pbCertPrefValue)
							{
								hr = E_FAIL;
								break;
							}

							memcpy(pbCertPrefValue, pPrefValueDTree->currentBaseDER->pbData, pPrefValueDTree->currentBaseDER->cbData);
							pbCertPrefValue[pPrefValueDTree->currentBaseDER->cbData] = '\0';

							tbstrCertPrefName = (TCHAR*)pbCertPrefName;

							if(tbstrCertPrefName == _bstr_t(CERTPREF_RENEWED))
							{
								DWORD dwRenewed = 1;
								if(memcmp(pbCertPrefValue, &dwRenewed, sizeof(DWORD)) == 0)
									tbstrCertPrefValue = "1";
								else
									tbstrCertPrefValue = "0";
							}
							else
								tbstrCertPrefValue = (TCHAR*)pbCertPrefValue;

							delete [] pbCertPrefName;
							delete [] pbCertPrefValue;

							i_pVirtualSmartCard->VSM_SetCertPref(nCertNum, tbstrCertPrefName, (PBYTE)(WCHAR*)tbstrCertPrefValue, (tbstrCertPrefValue.length()+1)*sizeof(WCHAR));
							
							pCertPrefDTree = pCertPrefDTree->nextDERTree;
						}	// while(pCertPrefDTree)

						if(hr != S_OK)
							break;
					}
				}
	
				pCertInfoDTree = pCertInfoDTree->nextDERTree;
			}	// while(pCertInfoDTree)

			if(hr != S_OK)
				break;
		}

		if(memcmp(pInfoTypeDTree->currentBaseDER->pbData, PRIVATEKEY_STRING, pInfoTypeDTree->currentBaseDER->cbData) == 0)
		{
			BYTE bytePubKeyHash[VS_CSP_SHA1_LEN];
			DWORD dwPubKeyHashSize = VS_CSP_SHA1_LEN;
			// Private keys are present

			// Skip the number of private keys
			_DERTree *pNumKeysDTree = pInfoTypeDTree->nextDERTree;
			CHECK_PROFILE(pNumKeysDTree, UNIVERSAL_INTEGER)

			_DERTree *pKeyInfoSeqDTree = pNumKeysDTree->nextDERTree;
			CHECK_PROFILE(pKeyInfoSeqDTree, SEQUENCE)

			_DERTree* pKeyInfoDTree = pKeyInfoSeqDTree->rightDERTree;

			while(pKeyInfoDTree)
			{
				CHECK_PROFILE(pKeyInfoDTree, SEQUENCE)

				_DERTree *pKeyHashDTree = pKeyInfoDTree->rightDERTree;
				CHECK_PROFILE(pKeyHashDTree, OCTET_STRING)

				_DERTree *pKeyDTree = pKeyHashDTree->nextDERTree;
				CHECK_PROFILE(pKeyDTree, OCTET_STRING)

				i_pVirtualSmartCard->VSM_ImportKey(pKeyDTree->currentBaseDER->pbData, pKeyDTree->currentBaseDER->cbData, 
												pKeyHashDTree->currentBaseDER->pbData, 0, NULL, 0, 0, bytePubKeyHash, &dwPubKeyHashSize);

				memset(pKeyDTree->currentBaseDER->pbData, pKeyDTree->currentBaseDER->cbData, 0);

				pKeyInfoDTree = pKeyInfoDTree->nextDERTree;
			}	// while(pKeyInfoDTree)
		}


		if(memcmp(pInfoTypeDTree->currentBaseDER->pbData, INFORMATION_BLOB, pInfoTypeDTree->currentBaseDER->cbData) == 0)
		{
			// Skip the number of information blobs
			_DERTree *pNumInfoBlobsDTree = pInfoTypeDTree->nextDERTree;
			CHECK_PROFILE(pNumInfoBlobsDTree, UNIVERSAL_INTEGER)

			_DERTree *pInfoBlobSeqDTree = pNumInfoBlobsDTree->nextDERTree;
			CHECK_PROFILE(pInfoBlobSeqDTree, SEQUENCE)

			_DERTree* pInfoBlobDTree = pInfoBlobSeqDTree->rightDERTree;

			while(pInfoBlobDTree)
			{
				CHECK_PROFILE(pInfoBlobDTree, SEQUENCE)

				_DERTree *pInfoBlobNameDTree = pInfoBlobDTree->rightDERTree;
				CHECK_PROFILE(pInfoBlobNameDTree, OCTET_STRING)

				TCHAR *pBlobName = (TCHAR*)malloc(pInfoBlobNameDTree->currentBaseDER->cbData + 1);
				memcpy(pBlobName, pInfoBlobNameDTree->currentBaseDER->pbData, pInfoBlobNameDTree->currentBaseDER->cbData);
				pBlobName[pInfoBlobNameDTree->currentBaseDER->cbData] = '\0';

				_DERTree *pInfoBlobValueDTree = pInfoBlobNameDTree->nextDERTree;
				CHECK_PROFILE(pInfoBlobValueDTree, OCTET_STRING)

				i_pVirtualSmartCard->VSM_SetInformationBlob(pBlobName, pInfoBlobValueDTree->currentBaseDER->pbData,
												pInfoBlobValueDTree->currentBaseDER->cbData);

				free(pBlobName);
				pBlobName = NULL;

				pInfoBlobDTree = pInfoBlobDTree->nextDERTree;
			}	// while(pInfoBlobDTree)
		}

	}while(0);

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	RemoveCertsInProfileFromCapiStore
//
//	Parameters
//				i_pvarVirtualSmartCard: Input - pointer to opened virtual smartcard
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function enumerates the certificates from the profile and
//						deletes them from CAPI store.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-26-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaEngine::RemoveCertsInProfileFromCapiStore(CVirtualSmartCard* i_pvarVirtualSmartCard)
{
	HRESULT retVal = S_OK;
	BOOL boolDone = FALSE;
	int nCertNum = 0;
	_bstr_t tbstrStorePref = CERTPREF_STORE;
	_bstr_t tbstrStoreVal = "";
	
		/*Open the MY store*/ 
	HCERTSTORE hCertStoreMy = NULL;
	if(MSCapi_CertOpenSystemStore)
	{
		hCertStoreMy = MSCapi_CertOpenSystemStore(NULL,"MY");
		if(!hCertStoreMy)
			retVal = E_CERTOPENSYSSTOREFAILED;
	}
	else
	{
		//Capi is not available so we dont have to make any capi compliant cert removal
		return retVal;
	}

	/*Till we've found the last cert*/
	do
	{
		PCERT_CONTEXT pCertContext;
		pCertContext = new CERT_CONTEXT;

		if(!pCertContext) 
		{
			retVal = E_OUTOFMEMORY;
			break;
		}

		/*Obtain cert blobs from the smart card*/
		retVal = i_pvarVirtualSmartCard->VSM_GetCert(nCertNum, NULL, &(pCertContext->cbCertEncoded));
		if(retVal == S_OK)
		{

			retVal = _GetVSCapiCertPref(i_pvarVirtualSmartCard, nCertNum, tbstrStorePref, &tbstrStoreVal);

			if(tbstrStoreVal == _bstr_t("MY"))
			{

				pCertContext->pbCertEncoded = new BYTE[pCertContext->cbCertEncoded];
				if(!pCertContext->pbCertEncoded) 
				{
					retVal = E_OUTOFMEMORY;
					delete pCertContext;
					break;
				}

				retVal = i_pvarVirtualSmartCard->VSM_GetCert(nCertNum, pCertContext->pbCertEncoded, &(pCertContext->cbCertEncoded));



				if(retVal == S_OK)
				{
					PCCERT_CONTEXT pCertContextAddedCert = NULL;

					/*Create a cert info from this cert blob*/
					if(!MSCapi_CertAddEncodedCertificateToStore(hCertStoreMy,X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,              
						pCertContext->pbCertEncoded,pCertContext->cbCertEncoded,                   
						CERT_STORE_ADD_REPLACE_EXISTING,&pCertContextAddedCert))
					{
						retVal = E_ADDCERTTOSTOREFAILED; 
					}

					if(!MSCapi_CertDeleteCertificateFromStore(pCertContextAddedCert))
					{
						retVal = E_DELETECERTFROMSTOREFAILED;
					}

				}

				delete[] pCertContext->pbCertEncoded;
			}

			// free certificate context
			delete pCertContext;

			nCertNum++;
		}
		else if (retVal == E_CERTNOTFOUND)
		{
			delete pCertContext;
			boolDone = TRUE;
			if(!nCertNum)//No certs have been found
				retVal = E_CERTNOTFOUND;
			else
				retVal = S_OK;
		}
		else
		{
			boolDone = TRUE;
		}
		
	}while (!boolDone);

	if(hCertStoreMy)
	{
		MSCapi_CertCloseStore(hCertStoreMy,CERT_CLOSE_STORE_FORCE_FLAG);
	}

	return retVal;
}

/* 
This function imports Public Key into the profile. This is called while importing p12 file into
PTA Profile.
*/
HRESULT CPtaEngine::ImportPublicKey(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, CVirtualSmartCard* i_pVirtualSmartCard)
{
	HRESULT retVal = S_OK;

	A_RSA_KEY theKey;

	BYTE*						pbyteKey					=	NULL;
	DWORD						dwKeyLen					=	0;

	BYTE*						pbytePubKey					=	NULL;
	DWORD						dwPubKeyLen					=	0;

	do {
		if(retVal == S_OK)
		{
			retVal = _GetRSAKeyFromKeyInfo(i_CertPublicKeyInfo, &theKey);
		}


		if(retVal == S_OK)
		{
			retVal =	GetBlobFromKey
						(
							&theKey,
							&pbyteKey,
							&dwKeyLen
						);

		}

		if(retVal == S_OK)
		{
				// get the length of the public key
			retVal = i_pVirtualSmartCard -> VSM_ImportKey
					  ( pbyteKey,
						dwKeyLen,
 						NULL,
						0,
						0,
						0,
						0,
						NULL,
						&dwPubKeyLen
					  );
		}

		if(retVal == S_OK) 
		{

			pbytePubKey =	new BYTE [dwPubKeyLen];
			if(pbytePubKey == NULL)
			{
				retVal = E_OUTOFMEMORY;
				break;
			}

			retVal = i_pVirtualSmartCard -> VSM_ImportKey
					  ( pbyteKey,
						dwKeyLen,
						NULL,
						0,
						0,
						0,
						0,
						pbytePubKey,
						&dwPubKeyLen
					  );			
		}

	} while(0);

	/*Free memory*/
	delete[] theKey.modulus.data;
	delete[] theKey.exponent.data;

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbytePubKey, dwPubKeyLen)
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteKey, dwKeyLen)


	return retVal;

}

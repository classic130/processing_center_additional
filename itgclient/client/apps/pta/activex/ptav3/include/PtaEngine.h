// PtaEngine.h: interface for the CPtaEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PTAENGINE_H__10F26073_E021_11D3_8168_0060B0F885E6__INCLUDED_)
#define AFX_PTAENGINE_H__10F26073_E021_11D3_8168_0060B0F885E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "certstructs.h"
#include "ptacorestructs.h"
#include "virtualsmartcard.h"

/*CAPI function pointers data types*/
typedef BOOL (WINAPI * LPFNCertFreeCertificateContext) (PCCERT_CONTEXT pCertContext) ;
typedef PCCERT_CONTEXT (WINAPI * LPFNCertDuplicateCertificateContext) (IN PCCERT_CONTEXT i_pCertContext);
typedef HCERTSTORE (WINAPI * LPFNCertOpenSystemStore) (HCRYPTPROV hProv,  LPCTSTR szSubsystemProtocol);
typedef BOOL (WINAPI * LPFNCertCloseStore)(HCERTSTORE hCertStore,  DWORD dwFlags);
typedef BOOL (WINAPI * LPFNCertAddEncodedCertificateToStore)(HCERTSTORE hCertStore,DWORD dwCertEncodingType,const BYTE *pbCertEncoded,
															 DWORD cbCertEncoded,DWORD dwAddDisposition, PCCERT_CONTEXT *ppCertContext);
typedef BOOL (WINAPI * LPFNCertSetCertificateContextProperty)(PCCERT_CONTEXT pCertContext, DWORD dwPropId, DWORD dwFlags, const void *pvData);  
typedef BOOL (WINAPI * LPFNCertGetCertificateContextProperty)(PCCERT_CONTEXT pCertContext, DWORD dwPropId, void *pvData,DWORD *pcbData);
typedef BOOL (WINAPI * LPFNCryptSignMessage) (PCRYPT_SIGN_MESSAGE_PARA pSignPara,BOOL fDetachedSignature,DWORD cToBeSigned,const BYTE *rgpbToBeSigned[ ],
									 DWORD rgcbToBeSigned[ ], BYTE *pbSignedBlob,  DWORD *pcbSignedBlob);
typedef PCCERT_CONTEXT (WINAPI * LPFNCertGetIssuerCertificateFromStore) (HCERTSTORE hCertStore, PCCERT_CONTEXT pSubjectContext,PCCERT_CONTEXT pPrevIssuerContext,DWORD *pdwFlags);
typedef BOOL (WINAPI * LPFNCertCompareCertificate) (DWORD dwCertEncodingType,  PCERT_INFO pCertId1, PCERT_INFO pCertId2);
typedef PCCERT_CONTEXT (WINAPI * LPFNCertFindCertificateInStore)(HCERTSTORE hCertStore, DWORD dwCertEncodingType, DWORD dwFindFlags,DWORD dwFindType,
															 const void *pvFindPara, PCCERT_CONTEXT pPrevCertContext);
typedef PCCERT_CONTEXT (WINAPI * LPFNCertEnumCertificatesInStore)(HCERTSTORE hCertStore, PCCERT_CONTEXT pPrevCertContext);
typedef BOOL (WINAPI * LPFNCryptAcquireContext)(HCRYPTPROV *phProv, LPCTSTR pszContainer, LPCTSTR pszProvider,
												DWORD dwProvType,  DWORD dwFlags);
typedef BOOL (WINAPI * LPFNCryptReleaseContext)(HCRYPTPROV hProv, DWORD dwFlags);
typedef BOOL (WINAPI * LPFNCertSerializeCertificateStoreElement)(PCCERT_CONTEXT pCertContext, DWORD dwFlags,
											BYTE *pbElement, DWORD *pcbElement);
typedef BOOL (WINAPI * LPFNCertDeleteCertificateFromStore)(PCCERT_CONTEXT pCertContext);
										   
class CPtaEngine  
{
private :
	HRESULT _FindFiles(_bstr_t& i_tbstrSrchPath, _bstr_t* i_ptbstrFileNames, int& nNumOfFiles);
	BOOL _InitPtaCapiWithMSCapi();
	BOOL _InitPtaCapiWithVSCapi();
	BOOL        boolIsCapi;
	DWORD		dwIsTPM;

	HCERTSTORE m_hLocalCertStore;
	int		m_nCertReqKeyType;
	void*       m_PTA;


	HRESULT _GetB64EncodedPubKeyIdentifier(PBYTE i_pbytePubKeyIdentifier, DWORD i_dwPubKeyIdentifierHash, _bstr_t* o_ptbstrB64EncodedPubKeyId);
	HRESULT _GetCertsFromPKCS7(PBYTE i_pbytePKCS7, DWORD i_dwPKCS7, PIDLISTNODE* o_ppidCertList);
	HRESULT _GetCertsFromVSCapi(CVirtualSmartCard* i_pvarVirtualSmartCard, PIDLISTNODE* o_pCertsInStore);
	HRESULT _GetCertsFromMSCapi(PIDLISTNODE* o_pCertsInStore);

	HRESULT _GetRSAKeyFromKeyInfo(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, A_RSA_KEY* o_pTheKey);
	HRESULT _GetDecCertInfo(PIDLISTNODE io_pCertList);
	HRESULT _DecodeCertInfo(PCERT_CONTEXT i_pCertContext, PDECCERT_INFO io_pDecCertInfo);
	HRESULT _GetNameFromBlob(CERT_NAME_BLOB& i_pTheNameBlob, _bstr_t* o_ptbstrName);
	HRESULT _GetCertSerNum(CRYPT_INTEGER_BLOB& i_pSerialNumber, _bstr_t* o_ptbstrSerNum);
	HRESULT _GetDateFromFileTime(FILETIME& i_ftTheFileTime, DATE* o_pDate);
	HRESULT _FilterCertList(CVirtualSmartCard* i_pVirtualSmartCard,PIDLISTNODE pCertList, SRCHCRIT& i_theSrchCrit, PIDLISTNODE* o_ppMatchingCertList);
	HRESULT _GetAuxCertInfo(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrAppCtxtName, PIDLISTNODE io_pMatchingCertList);
	HRESULT _DoesCertMatchSrchCrit(CVirtualSmartCard* i_pVirtualSmartCard,PIDLISTNODE i_pCert,SRCHCRIT& i_theSrchCrit);
	HRESULT _CheckIfKeyUsageGood(int i_nCertKeyUsage, int i_nSrchCritKeyUsage);
	HRESULT _CheckPrivKeyAccess(CVirtualSmartCard* i_pVirtualSmartCard,PCERT_CONTEXT i_pCertContext);
	HRESULT _CheckIfVSBlessed(PCERT_CONTEXT i_ppCertContext);
	HRESULT _CheckIfDNGood(_bstr_t& i_tbstrIssuerDN, _bstr_t& i_tbstrIssDNSrchCrit);
	HRESULT _CheckIfSerNumGood(_bstr_t& i_tbstrSerNum, _bstr_t& i_tbstrSerNumSrchCrit);
	HRESULT _CheckIfEmailGood(_bstr_t& i_tbstrSbjDN, _bstr_t& i_tbstrEmailAdd);
	HRESULT _CheckIfRenewedGood(BOOL i_boolRenewed, BOOL i_boolRenewedSrchCrit);
	HRESULT _CheckIfDateGood(DATE& i_dateExpDate, DATE& i_dateExpDateSrchCrit, int i_nDateEqualtiy);
	HRESULT _CreatePKCS7(PBYTE i_pbyteSignature, unsigned int i_nSignatureSize, int i_nHashAlg, PCERT_CONTEXT i_pCertContext, PBYTE i_pbyteSignedData, int i_nSignedDataSize, PBYTE i_pbyteAuthAttr, DWORD i_dwAuthAttrSize,_bstr_t* o_ptbstrPKCS7);
	HRESULT _GetDERIssuerDN(PCERT_CONTEXT i_pCertContext, CSequence* o_pcseqIssuer);
	HRESULT _GetDERSerNum(PCERT_CONTEXT i_pCertContext, CUniversalInteger* o_pcuiSerialNum);
	HRESULT _GetMSCapiCertPref(_bstr_t& i_tbstrPubKeyId, _bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal);
	HRESULT _SetMSCapiCertPref(_bstr_t& i_tbstrPubKeyId, _bstr_t& i_tbstrPrefName, TCHAR* ptszPrefVal, int i_nPrefValSize);
	HRESULT _SetMSCapiAppPref(_bstr_t& i_tbstrAppCtxtName, _bstr_t& i_tbstrPrefName, TCHAR* ptszPrefVal, int i_nPrefValSize);
	HRESULT _GetMSCapiAppPref(_bstr_t& i_tbstrAppCtxt, _bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal);
	HRESULT _SignDataWithVSCapi(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, BOOL i_boolHashData, BOOL i_boolP7Output, BOOL i_boolAddAuthAttr, DATE i_dateSignDate, _bstr_t* o_ptbstrSignature);
	HRESULT _SignDataWithMSCapi(PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, _bstr_t* o_ptbstrSignature);
	HRESULT _GetPrivKeyFromPKCS8(PBYTE i_pbytePKCS8,DWORD i_dwPKCS8Size,PBYTE* o_ppbytePrivKeyBlob, DWORD* o_pdwPrivKeyBlobSize);
	HRESULT _GetAuthAttr(PBYTE i_pbyteHash,int i_nHashSize,DATE i_dateSignDate,PBYTE o_pbyteAuthAttr,DWORD* io_pdwAuthAttrSize);
	void _FormatUTCTime(char *szUTCTime, LPSYSTEMTIME i_pSystime);
//	artf25786 Start
	wchar_t* CPtaEngine::FormattedIssuerDNSrchCrit( _bstr_t& i_tbstrSubjectDN);
//	artf25786 End

//
//	Anand	Dec 15, 2000		Start
//
	HRESULT _DecryptDataWithVSCapi(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToDecrypt, int i_nDataToDecryptLength, PIDLISTNODE i_pSelectedId, BYTE** o_ppbyteDecryptedData, DWORD* o_pdwDecryptedDataLength);
	HRESULT _DecryptDataWithMSCapi(PBYTE i_pbyteDataToDecrypt, int i_nDataToDecryptLength, PIDLISTNODE i_pSelectedId, BYTE** o_ppbyteOutput, DWORD* o_pdwDecryptedDataLength);
//
//	Anand	Dec 15, 2000		End
//

	HRESULT _SignDataWithVSTPM(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, BOOL i_boolHashData, BOOL i_boolP7Output, BOOL i_boolAddAuthAttr, DATE i_dateSignDate, _bstr_t* o_ptbstrSignature);

	HRESULT _InitEngine();

	/*Pta Capi function pointers*/
	LPFNCertFreeCertificateContext PtaCapi_CertFreeCertitificateContext;
	LPFNCertDuplicateCertificateContext PtaCapi_CertDuplicateCertificateContext;
	LPFNCertGetIssuerCertificateFromStore PtaCapi_CertGetIssuerCertificateFromStore;
	LPFNCertCompareCertificate PtaCapi_CertCompareCertificate;
	LPFNCertFindCertificateInStore PtaCapi_CertFindCertificateInStore;

	/* MS Capi function pointers */
	HMODULE m_hModCapiDll;
	HMODULE m_hModAdvapiDll;

	LPFNCertOpenSystemStore MSCapi_CertOpenSystemStore;
	LPFNCertFreeCertificateContext MSCapi_CertFreeCertitificateContext;
	LPFNCertCloseStore MSCapi_CertCloseStore;
	LPFNCertAddEncodedCertificateToStore MSCapi_CertAddEncodedCertificateToStore;
	LPFNCertSetCertificateContextProperty MSCapi_CertSetCertificateContextProperty;
	LPFNCertGetCertificateContextProperty MSCapi_CertGetCertificateContextProperty;
	LPFNCryptSignMessage MSCapi_CryptSignMessage;
	LPFNCertEnumCertificatesInStore MSCapi_CertEnumCertificatesInStore;
	LPFNCryptAcquireContext MSCapi_CryptAcquireContext;
	LPFNCryptReleaseContext MSCapi_CryptReleaseContext;
	LPFNCertSerializeCertificateStoreElement MSCapi_CertSerializeCertificateStoreElement;
	LPFNCertDeleteCertificateFromStore MSCapi_CertDeleteCertificateFromStore;

public:
	PIDLISTNODE NewCert();
	PIDLISTNODE CopyCert(PIDLISTNODE i_pCertToCopy);
	HRESULT GetMatchingCerts(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrAppCtxtName, SRCHCRIT& i_theSrchCrit, PIDLISTNODE* o_ppMatchingCertList);
	void FreeLocalProfilesList(_bstr_t* in_ptbstrProfiles);
	HRESULT GetLocalProfilesList(_bstr_t& tbstrAppContextName, _bstr_t** o_ptbstrProfiles, int& nNumOfProfiles);
	HRESULT CreateCertHash(PCERT_CONTEXT i_pCertContext, int i_nHashAlgId, unsigned char*  o_pbyteHashVal);
	HRESULT FreeIdList(PIDLISTNODE pIdListHeadNode);
	HRESULT GetSelIDCertContext(PCERT_CONTEXT i_pCertContext, VARIANT *pVal);
	HRESULT Close();
	HRESULT Initialize(short boolCapiFlag);
	HRESULT GetProfileFilePathAndName(_bstr_t& i_tbstrAppContextName, _bstr_t& i_tbstrUserName, _bstr_t* o_ptbstrProfileFilePathAndName);
	HRESULT CreateCertReq(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrSubjectDN, int i_nKeyAttribs, int i_nHashAlg, int i_nNumOfAttrs,
		_bstr_t* i_ptbstrAtrrOIDs, _bstr_t* i_ptbstrAttrVals, _bstr_t* o_ptbstrCertReq, 
	PBYTE* o_ppbytePubKeyHash, DWORD* o_pdwPubKeyHashSize, const BOOL i_bIsPrivateKeyExportable);
 	HRESULT _CreatePKCS10(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbytePubKeyHandle, int i_nPubKeyHandleSize, _bstr_t& i_tbstrSubjectDN, A_RSA_KEY* i_pRSAPubKey, int i_nHashAlg,int i_nNumOfAttrs,_bstr_t* i_ptbstrAtrrOIDs,_bstr_t* i_ptbstrAttrVals, _bstr_t* o_ptbstrCertReq);
	HRESULT Remember_PubKey_SmartCardKeyType_Assoc(CVirtualSmartCard* i_pVirtualSmartCard, DWORD dwKeyType, PBYTE i_pbytePubKeyIdentifier,DWORD i_dwPubKeyIdentifierHash);
	HRESULT DecodePKCS7AndGetCerts(_bstr_t& i_tbstrB64EncPKCS7,PIDLISTNODE*	o_ppidCertList);
	HRESULT GetPubKeyIdentifierFromPubKey(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, PBYTE o_pbytePublicKeyIdentifier,
												  DWORD* o_pdwPublicKeyIdentifierSize);
	HRESULT Restore_PubKey_SmartCardKeyType_Assoc(PBYTE i_pbytePublicKeyIdentifier,	DWORD i_dwPubKeyIdentifierSize, _bstr_t* o_ptbstrSmartCardName, DWORD* o_pdwKeyType);
	HRESULT InstallCerts(CVirtualSmartCard* i_pVirtualSmartCard,PIDLISTNODE pidListCertsToInstall, unsigned int *o_pnCertNum);
	HRESULT Delete_PubKey_Assoc(PBYTE i_pbytePublicKeyIdentifier, DWORD i_dwPubKeyIdentifierSize);
	HRESULT MakeCapiCompliantCertInstall(CVirtualSmartCard* i_pVirtualSmartCard,
					PIDLISTNODE i_pidListCertsToInstall, PBYTE i_pbytePublicKeyId,
					DWORD i_dwPublicKeyIdSize, BYTE i_byteInstallKeyType, BOOL i_boolIsKeyExportable, BOOL i_boolIsRoamProfile,
					_bstr_t& i_ptbstrClientInfo, _bstr_t& i_ptbstrClientInfoSig, int nCertNum, _bstr_t& i_ptbstrContainerName);
	HRESULT DeleteCertFromCAPI(PIDLISTNODE i_pidListCertsToDelete);
	HRESULT SetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrCertIssDN, _bstr_t& i_tbstrCertSerNum,
		_bstr_t& i_tbstrPrefName, _bstr_t& i_tbstrPrefVal);

	HRESULT SignData(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToSign, int i_nDataToSignSize, int i_nHashAlg, PIDLISTNODE i_pSelectedId, BOOL i_boolIsAttached, BOOL i_boolHashData, BOOL i_boolP7Output, BOOL i_boolAddAuthAttr, DATE i_dateSignDate, _bstr_t* o_ptbstrSignature);

	HRESULT GetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrCertIssDN, _bstr_t& i_tbstrCertSerNum,
		_bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal);
	HRESULT _GetVSCapiCertPref(CVirtualSmartCard* i_pVirtualSmartCard, int i_nCertNum, _bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal);
	/*HRESULT GetRoamingProfileParams(_bstr_t& i_tbstrAppCtxtName, _bstr_t& i_tbstrProfName, _bstr_t& i_tbstrProfileIssUniqueId, int i_nNumOfRoamingSrvrs,
							_bstr_t* i_ptbstrRoamingSrvrs, _bstr_t& i_tbstrStorageSrvr, VARIANT* o_pvarWhichSmartCard);*/

	HRESULT GetRoamingProfileParams(_bstr_t& i_tbstrAppCtxtName, _bstr_t& i_tbstrProfName, _bstr_t& i_tbstrProfileIssUniqueId, _bstr_t& i_tbstrClientInfo, _bstr_t& i_tbstrClientInfoSig, VARIANT* o_pvarWhichSmartCard);

	HRESULT DecodePKCS8AndGetPrivKey(_bstr_t& i_tbstrKeyToImport,PBYTE* o_ppbytePrivKeyBlob, DWORD* o_dwPrivKeyBlobSize);
	HRESULT InstallPrivKey(CVirtualSmartCard* i_pVirtualSmartCard,PBYTE i_pbytePrivKeyBlob, DWORD i_dwPrivKeyBlobSize, PBYTE i_pbytePubKeyId);
	HRESULT SetDefaultCert(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrAppCtxt, _bstr_t& i_tbstrIssuerDN, _bstr_t& i_tbstrSerNum);
	HRESULT DecodePKCS12_GetPrivKeyAndCerts(int i_nKeyFileOrBlob,_bstr_t& i_tbstrKeyFileOrBlob,
													_bstr_t& i_tbstrP12Passwd,PBYTE* o_ppbytePriveKeyBlob, DWORD* o_pdwPrivKeyBlobSize,
													PIDLISTNODE* o_ppCertListHead);
	HRESULT ExportP12(CVirtualSmartCard* i_pVirtualSmartCard, _bstr_t& i_tbstrKeyFile,_bstr_t& i_tbstrPassword,PIDLISTNODE i_pSelectedId);

//
//	Anand	Dec 15, 2000		Start
//
	HRESULT DecryptData(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbyteDataToDecrypt, int i_nDataToDecryptLength, PIDLISTNODE i_pSelectedId, BYTE** o_ppbyteOutput, DWORD* o_pdwDecryptedDataLength);
//
//	Anand	Dec 15, 2000		End
//

	HRESULT ExportProfile(CVirtualSmartCard* i_pVirtualSmartCard, UINT nExportFlags, PBYTE i_pbPassword, DWORD i_dwPassword, _bstr_t& i_tbstrProfileData);
	HRESULT ImportProfile(CVirtualSmartCard* i_pVirtualSmartCard, PBYTE i_pbPassword, DWORD i_dwPassword, _bstr_t& i_tbstrB64ProfileData);
	HRESULT _UpdateProfile(CVirtualSmartCard* i_pVirtualSmartCard, _DERTree *pInfoTypeDTree);
	HRESULT RemoveCertsInProfileFromCapiStore(CVirtualSmartCard* i_pVirtualSmartCard);

	HRESULT ImportPublicKey(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, CVirtualSmartCard* i_pVirtualSmartCard);
	HRESULT DoDisableNRKeyUsage(SRCHCRIT &i_theSrchCrit, _bstr_t& i_tbstrAppCtxtName);

	CPtaEngine(const void* i_cPTA)
	{
		PtaCapi_CertFreeCertitificateContext = NULL;
		PtaCapi_CertFreeCertitificateContext = NULL;
		PtaCapi_CertDuplicateCertificateContext = NULL;
		PtaCapi_CertGetIssuerCertificateFromStore = NULL;
		PtaCapi_CertCompareCertificate = NULL;
		PtaCapi_CertFindCertificateInStore = NULL;

		m_hModCapiDll = NULL;
		m_hModAdvapiDll = NULL;

		MSCapi_CertOpenSystemStore = NULL;
		MSCapi_CertFreeCertitificateContext = NULL;
		MSCapi_CertCloseStore = NULL;
		MSCapi_CertAddEncodedCertificateToStore = NULL;
		MSCapi_CertSetCertificateContextProperty = NULL;
		MSCapi_CertGetCertificateContextProperty = NULL;
		MSCapi_CryptSignMessage = NULL;
		MSCapi_CertEnumCertificatesInStore = NULL;
		MSCapi_CryptAcquireContext = NULL;
		MSCapi_CryptReleaseContext = NULL;

		m_hLocalCertStore = NULL;
		m_PTA = (void*)i_cPTA;
	}

	~CPtaEngine()
	{
		if(m_hLocalCertStore)
		{
			MSCapi_CertCloseStore(m_hLocalCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
			m_hLocalCertStore = NULL;
		}

		if(m_hModCapiDll)
		{
			FreeLibrary(m_hModCapiDll);
			m_hModCapiDll = NULL;
		}

		if(m_hModAdvapiDll)
		{
			FreeLibrary(m_hModAdvapiDll);
			m_hModAdvapiDll = NULL;
		}

		return;
	}

};

#endif // !defined(AFX_PTAENGINE_H__10F26073_E021_11D3_8168_0060B0F885E6__INCLUDED_)

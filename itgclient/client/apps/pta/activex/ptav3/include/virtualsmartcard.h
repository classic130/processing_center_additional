// Storage.h: interface for the CStorage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORAGE_H__10F26074_E021_11D3_8168_0060B0F885E6__INCLUDED_)
#define AFX_STORAGE_H__10F26074_E021_11D3_8168_0060B0F885E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "stdafx.h"

#include "comdef.h"

#include "vsrmclient.h"
#include "vsrmdata.h"


//#include "cspincludes.h"
//#include "cspstructures.h"

//#include "HelperFunctions.h"
#include "keycontainer.h"


#include "protectedstorage.h"
//#include "tss_all.h"

#ifdef VS_TSSDLL
#include "VS_TSS.h"
#else
#include "vs_tss.h"
#endif // VS_TSSDLL

#define IBM_TSS 1
#define INFINEON_TSS 2

	//	this is a class specific macro. this can be used only from the member functions of the
	//	CVirtualSmartCard class
#define		VSCSP_CHECK_IF_PS_OBJECT_READY	if ( TRUE != boolUsePS )\
	{\
		hResult =	NTE_FAIL;\
		break;\
	}

#define		VSCSP_DELETE_USING_PS_FREE(pBuffer)	{\
		if ( TRUE == boolUsePS )\
		{\
			if ( NULL != pBuffer )\
			{\
				pProtectedStorage -> FreeMemoryBlob ( (void**) &pBuffer );\
				pBuffer =	NULL;\
			}\
		}\
	}


typedef	HRESULT	(FN_PasswordCallback) (void* i_pvoidPTAObj, void* i_pvoidPointer, _VS_CHAR*	o_cszPassword);

typedef LONG (WINAPI * LPFNRegOpenCurrentUser) (REGSAM samDesired, PHKEY phkResult);

#ifdef VS_TSSDLL

typedef VS_TSS_Context* (*LPFNCreateContextObject) (DWORD* o_dwError);

typedef VS_TSS_Data * (*LPFNCreateDataObject) (const VS_TSS_Context* i_chContext,
											const VS_TSS_Key*     i_cTSSKey,
											DWORD*	o_dwError);

typedef VS_TSS_Hash * (*LPFNCreateHashObject) (const VS_TSS_Context* i_chContext, 
											const DWORD           i_cdwAlgorithmId, 
											DWORD*                o_dwError);

typedef VS_TSS_Key* (*LPFNCreateKeyObjectURK) (const VS_TSS_Context* i_chContext, 
							   const UUID            i_cMyUUID,
							   const DWORD           i_cdwMyPasswordLength,
							   const BYTE*           i_cMyPasssword, 
							   DWORD*                o_pdwError);
;

typedef VS_TSS_Key* (*LPFNCreateKeyObjectULK) (const VS_TSS_Context* i_chContext, 
													   const DWORD           i_cdwKeyLength, 
													   const DWORD           i_cdwKeyUsage,
													   const UUID            i_cMyUUID, 
													   const DWORD           i_cdwMyPasswordLength,
													   const BYTE*           i_cMyPassword,
													   const UUID            i_cParentUUID,
													   const DWORD           i_cdwParentPasswordLength,
													   const BYTE*           i_cParentPasssword, 
													   DWORD*                o_pdwError);

typedef VS_TSS_Key* (*LPFNCreateKeyObjectLoadUK) (const VS_TSS_Context* i_chContext, 
												const UUID            i_cMyUUID,
												const DWORD           i_cdwMyPasswordLength,
												const BYTE*           i_cMyPassword, 
												const UUID            i_cParentUUID,
												const DWORD           i_cdwParentPasswordLength,
												const BYTE*           i_cParentPassword, 
												DWORD*                o_pdwError);

typedef VS_TSS_Key* (*LPFNCreateKeyObjectImportPublicKey) (const VS_TSS_Context* i_chContext,
														   const DWORD           i_cdwKeyUsage,
														   const DWORD           i_cdwModulusLength,
														   const BYTE*           i_pbModulusData,
														   DWORD*                o_pdwError,
														   const BYTE            i_cbDummy);

#endif // VS_TSSDLL

class CVirtualSmartCard  
{
public:
	HRESULT VSM_Initialize(VARIANT* i_pvarWhichSmartCard, VARIANT* i_pvarPassword, VARIANT* i_pvarAppCtxt, 
		VARIANT* i_pvarProfileIssFrndlyName, VARIANT* i_pvarAppHostName,
		VARIANT* i_pvarPasswdTimeOut, VARIANT* i_pvarPasswdLockOutTries, VARIANT* i_pvarPasswdUnLockPeriod, 
		FN_PasswordCallback* i_pPasswordCallback, void* i_pObjectPTA);

	HRESULT get_VSM_ProfileName(VARIANT* o_pvarProfileName);
	HRESULT get_VSM_ProfileOpenHostName(_bstr_t* o_pbstrHostName);

	HRESULT put_VSM_ProfileOpenHostWildCard(_bstr_t i_tbstrHostWildCard);
	HRESULT put_VSM_ApplicationCreatorWildCard(_bstr_t i_tbstrCreatorWildCard);

	HRESULT put_VSM_ProfileIssFrndlyName(VARIANT* in_pvarProfileIssFrndlyName);
	HRESULT get_VSM_ProfileIssFrndlyName(VARIANT* o_pvarProfileIssFrndlyName);

	HRESULT put_VSM_PasswdUnLockPeriod(short in_nPasswdUnLockPeriod);
	HRESULT get_VSM_PasswdUnLockPeriod(short* o_pnPasswdUnLockPeriod);

	HRESULT put_VSM_PasswdLockOutTries(short in_nPasswdLockOutTries);
	HRESULT get_VSM_PasswdLockOutTries(short* o_pnPasswdLockOutTries);

	HRESULT put_VSM_PasswdTimeOut(short in_nPasswdTimeOut);
	HRESULT get_VSM_PasswdTimeOut(short* o_pnPasswdTimeOut);

	HRESULT put_VSM_PasswdLength(short in_nPasswdLength);
	HRESULT get_VSM_PasswdLength(short* o_pnPasswdLength);

	HRESULT put_VSM_PasswdQuality(short in_nPasswdQualtiy);
	HRESULT get_VSM_PasswdQuality(short* o_pnPasswdQualtiy);

	HRESULT put_VSM_WriteOKDomains(VARIANT* in_pvarWriteOKDomains);
//	HRESULT get_VSM_WriteOKDomains(VARIANT* o_pvarWriteOKDomains);
	HRESULT get_VSM_WriteOKDomains
	(
		_bstr_t** o_ppbstrWriteOKDomains, 
		DWORD* o_pdwNumOfWriteOKDomains
	);

	HRESULT put_VSM_ReadOKDomains(VARIANT* in_pvarReadOKDomains);
//	HRESULT get_VSM_ReadOKDomains(VARIANT* o_pvarReadOKDomains);
	HRESULT get_VSM_ReadOKDomains
	(
		_bstr_t** o_ppbstrReadOKDomains, 
		DWORD* o_pdwNumOfReadOKDomains
	);

//	HRESULT get_VSM_ApplicationReadOKDomains(VARIANT* o_pvarApplicationReadOKDomains);
	HRESULT get_VSM_ApplicationReadOKDomains
	(
		_bstr_t** o_ppbstrApplicationReadOKDomains, 
		DWORD* o_pdwNumOfApplicationReadOKDomains
	);

	HRESULT put_VSM_ApplicationReadOKDomains(VARIANT* in_pvarApplicationWriteOKDomains);

	HRESULT get_VSM_ApplicationWriteOKDomains
	(
		_bstr_t** o_ppbstrApplicationWriteOKDomains, 
		DWORD* o_pdwNumOfApplicationWriteOKDomains
	);

	HRESULT put_VSM_ApplicationWriteOKDomains(VARIANT* in_pvarApplicationWriteOKDomains);

	// Sasi 05/05/2003
	// property to indicate if the roaming server supports reset password feature
	HRESULT get_VSM_ResetPasswordFeature
	(
		BOOL*	pResetPasswordFeature
	);

	// Sasi 05/05/2003
	// properties to set secret question and answer used while creating a roaming profile
	HRESULT put_VSM_RoamProfSecretQuestion(_bstr_t i_tbstrSecretQuestion);
	HRESULT put_VSM_RoamProfSecretAnswer(_bstr_t i_tbstrSecretAnswer);

	// Sasi 06/05/2003
	// properties to set secret first name, last name and e-mail of the user. This information will be stored in roaming database
	HRESULT put_VSM_RoamProfFirstName(_bstr_t i_tbstrFirstName);
	HRESULT put_VSM_RoamProfLastName(_bstr_t i_tbstrLastName);
	HRESULT put_VSM_RoamProfEmail(_bstr_t i_tbstrEmail);

	HRESULT AmITheApplicationCreator(bool* o_pboolIsCreator);
	HRESULT IsThisHostTheApplicationCreator(BSTR i_bstrHostName, bool* o_pboolIsCreator);

	HRESULT VSM_GetAppPreference(BSTR in_bstrPrefName, VARIANT* o_pvarPrefValue);
	HRESULT VSM_SetAppPreference(BSTR in_bstrPrefName, VARIANT* in_pvarPrefValue, int i_ncAddApplicationIfItDoesNotExist);

	HRESULT BeginRead(CProtectedStorage *i_pProtectedStorage, _VS_DWORD i_cnMode, _VS_DWORD i_cnWaitTime);
	HRESULT BeginWrite(CProtectedStorage *i_pProtectedStorage, _VS_DWORD i_cnMode, _VS_DWORD i_cnWaitTime);
	HRESULT UpgradeReadToWrite(CProtectedStorage* i_pProtectedStorage);

	HRESULT VSM_Close();
	HRESULT VSM_Save();
	HRESULT VSM_ChangeHost(BSTR bstrHostName,  BSTR bstrAppCtxtName);
	HRESULT VSM_AddCert(VARIANT* i_pvarCertToAdd, unsigned int *o_pCertNum);
	HRESULT VSM_Open(VARIANT* i_pvarWhichSmartCard, VARIANT* i_pvarPassword, VARIANT* i_pvarAppCtxt,
		VARIANT* i_pvarProfileIssFrndlyName, VARIANT* i_pvarAppHostName, VARIANT* i_pvarPasswdTimeOut,
		int i_ncAddApplicationIfItDoesNotExist, FN_PasswordCallback* i_pPasswordCallback, void* i_pObjectPTA);
	HRESULT VSM_GetCert(int i_nCertNum, PBYTE o_pbyteCertBlob, DWORD* o_pdwCertBlobSize);
	HRESULT VSM_IsPrivKeyAvailable(PBYTE i_pbytePubKeyId, DWORD i_dwPubKeyIdSize);
	HRESULT VSM_SetCertPref(int i_nCertNum, _bstr_t& i_tbstrPrefName, PBYTE i_pbytePrefVal,
					int i_nPrefValSize);
	HRESULT VSM_GetCertPref(int i_nCertNum, _bstr_t& i_tbstrPrefName, PBYTE o_pbytePrefVal,
					int* o_pnPrefValSize);
	HRESULT	VSM_SetPasswordFunction ( _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut );
	HRESULT VSM_CreatePasswd(_bstr_t& i_tbstrNewPasswd);
	HRESULT VSM_EnterPasswd(_bstr_t i_tbstrThePasswd); // XXX
	HRESULT VSM_IsPasswdEntered();
	HRESULT VSM_ChangePasswd(_bstr_t& i_tbstrOldPasswd, _bstr_t& i_tbstrNewPasswd);

	//-----------------------SAMEER ABOVE---------------------------------------------

	// Modified by - Infosys Technologies Ltd. 
	// Change Request - CR#21529
	// Description - Change the function signature to accomodate the bIsPrivateKeyExportable flag. 
	// CR#21529 - Begin
	// Date Modified - July 5, 2004
	// Pass an parameter to the function and default this parameter to 1. 
	// This parameter is the bIsPrivateKeyExportable flag. 

	HRESULT		VSM_GenKey
	(
//		const CHAR*			i_cszContainerName,	//	the container name
		const int			i_cnAlgid,		//	signature / exchange RSA key
		const int			i_cnSizeOfKey,	//	size
		const DWORD			i_cdwFlags,		//	EXPORTABLE / NOT_EXPORTABLE
		BYTE*				o_pbyteCorrPubKey,	//	if NULL then the req len will be returned in the o_pdwCorrPubKeyLen
		DWORD*				o_pdwCorrPubKeyLen,
		BOOL				o_bIsPrivateKeyExportable = 1 // Default this parameter to 1 i.e. allow private key export.
	);
	// CR#21529 - End

	HRESULT		VSM_DestroyKey
	(
		const BYTE*			i_cpbyteCorrPubKey,
		const DWORD*		i_cpdwCorrPubKeyLen
	);


	HRESULT		VSM_GetKeyParam
	(
		const BYTE*			i_cpbyteCorrPubKey,
		const DWORD			i_cdwCorrPubKeyLen,
		const DWORD			i_cdwParam,		//	KP_ALGID only. the rest of the parameters will not be supported
		BYTE*				o_pbData,		//	the return data
		DWORD*				o_pdwDataLen	//	the return data length
	);


	HRESULT		VSM_ExportKey
	(
		const BYTE*			i_cpbyteCorrPubKey,
		const DWORD			i_cdwCorrPubKeyLen,
		const DWORD			i_cdwTypeOfKeyForEncryption,	//	symmetric / asymmetric
		const BYTE*			i_cpbyteEncryptionKey,
		const DWORD			i_cdwEncryptionKeyLength,
		const DWORD			i_cdwBlobType,					//	public key ONLY or both pub-priv keys
		BYTE*				o_pbData,
		DWORD*				o_pdwDataLen
	);


	HRESULT		VSM_ImportKey
	(
		const BYTE*			i_cpbData,
		const DWORD			i_cdwDataLen,
		const BYTE*			i_pbytePubKeyHash,
		const DWORD			i_cdwTypeOfKeyForEncryption,	//	symmetric / asymmetric
		const BYTE*			i_cpbyteEncryptionKey,
		const DWORD			i_cdwEncryptionKeyLength,
		const DWORD			i_cdwFlags,		//	EXPORTABLE / NOT_EXPORTABLE
		BYTE*				o_pbyteCorrPubKey,
		DWORD*				o_pdwCorrPubKeyLen
	);


	HRESULT		VSM_EncryptBegin
	(
		const BYTE*			i_cpbyteCorrPubKeyHash,
		const DWORD			i_cdwCorrPubKeyHashLen,
		void**				o_ppvoidContext
	);

	HRESULT		VSM_EncryptUpdate
	(
		const void*			i_cpvoidContext,
		const BOOL			i_cboolFinal,
		const BYTE*			i_cpbData,
		const DWORD			i_cdwDataLen,
		BYTE*				i_pbyteOutData,
		DWORD*				i_pdwOutDataLen
	);

	HRESULT		VSM_EncryptEnd
	(
		const void*			i_cpvoidContext
	);

	HRESULT		VSM_DecryptBegin
	(
		const BYTE*			i_cpbyteCorrPubKey,
		const DWORD			i_cdwCorrPubKeyLen,
		void**				o_ppvoidContext
	);

	HRESULT		VSM_DecryptUpdate
	(
		const void*			i_cpvoidContext,
		const BOOL			i_cboolFinal,
		const BYTE*			i_cpbData,
		const DWORD			i_cdwDataLen,
		BYTE*				o_pbyteOutData,
		DWORD*				o_pdwOutDataLen
	);

	HRESULT		VSM_DecryptEnd
	(
		const void*			i_cpvoidContext
	);

	HRESULT		VSM_SignData
	(
		const BYTE*			i_cpbyteCorrSignPubKey,
		const DWORD			i_cdwCorrSignPubKeyLen,
		const BYTE*			i_cpbyteData,
		const DWORD			i_cdwDataLen,
		const DWORD			i_cdwHashAlgID,
		const BOOL			i_cboolIsDataHashed,
		BYTE*				o_pbyteSignature,
		DWORD*				o_pdwSignatureLen,
		const DWORD			i_dwFlags = 0
	);

	HRESULT		VSM_VerifyData
	(
		const BYTE*			i_cpbyteCorrSignPubKey,
		const DWORD			i_cdwCorrSignPubKeyLen,
		const BYTE*			i_cpbyteData,
		const DWORD			i_cpdwDataLen,
		const DWORD			i_cdwHashAlgID,
		const BOOL			i_cboolIsDataHashed,
		const BYTE*			i_cpbyteSignature,
		const DWORD			i_cdwSignatureLen,
		const DWORD			i_dwFlags = 0
	);

	HRESULT		VSM_GetUserKeyHandle
	(
		const CHAR*			i_cszContainerName,
		const DWORD			i_cdwAlgID,
		DWORD*				o_pdwKeyLen,
		DWORD*				o_pdwExportable,
		BYTE*				o_pbyteCorrPubKey,
		DWORD*				o_pdwCorrPubKeyLen
	);

	HRESULT		VSM_GetInformationBlob
	(
		const CHAR*			i_cszName,
		BYTE*				o_pbyteValue,
		DWORD*				o_pdwValueLen
	);

	HRESULT		VSM_SetInformationBlob
	(
		const CHAR*			i_cszName,
		const BYTE*			i_pbyteValue,
		const DWORD			i_dwValueLen
	);

	HRESULT		VSM_DeleteInformationBlob
	(
		const CHAR*			i_cszName
	);


//////////////////////////////////////////////////////////////////////////////
//	NEW SECTION ADDED BELOW FOR THE ADDITIONAL FUNCTIONALITY OF TCPA SUPPORT
//	THE FUNCTIONS IN VIRTUAL SMART CARD WILL BE CALLED BY THE VS_TPM_CSP AS
//	WELL AS THE PTA IN TPM MODE.
//////////////////////////////////////////////////////////////////////////////

	HRESULT		VSM_TPMInitialize
	(
		const CHAR*			i_cszContainerName,
		const DWORD			i_cdwOpenCreate,
		const void*         i_cPTA
	);

	HRESULT		VSTPM_CheckIfKeyExists
	(
		const DWORD		i_cdwAlgID,
		DWORD*			o_pdwExists
	);


	HRESULT		VSTPM_CreateKey
	(
		const DWORD				i_cdwKeyLength,
		const DWORD				i_cdwKeyUsage,
		VS_TSS_Key**			o_ppVSTSSKey
	);

	HRESULT		VSTPM_GetKey
	(
		const DWORD				i_cdwAlgoID,
		DWORD*					o_pdwKeyLength,
		DWORD*					o_pdwKeyExportable,
		VS_TSS_Key**			o_ppVSTSSKey
	);

	HRESULT		VSTPM_CreateHashObject
	(
		VS_TSS_Hash**			o_ppVSTSSHash
	);

	HRESULT		VSTPM_HashData
	(
		const VS_TSS_Hash*		i_cpVSTSSHash,
		const DWORD				i_cdwDataLen,
		const BYTE*				i_cpbyteData
	);

	HRESULT		VSTPM_GetHash
	(
		DWORD*					o_pdwDataLen,
		BYTE**					o_ppbyteData
	);

	HRESULT		VSTPM_SignHash
	(
		VS_TSS_Hash*			i_pVSTSSHash,
		const DWORD				i_cdwKeySpec,
		BYTE*					o_pbSignature,
		DWORD*					o_pdwSigLen
	);

	HRESULT		VSTPM_VerifySignature
	(
		VS_TSS_Hash*			i_pVSTSSHash,
		VS_TSS_Key*				i_pVSTSSKey,
		const BYTE*				i_cpbSignature,
		DWORD					i_dwSigLen
	);

	HRESULT		VSTPM_EncryptDecryptBegin
	(
		const VS_TSS_Key*		i_cpVSTSSKey,
		VS_TSS_Data**			o_ppVSTSSData
	);

	HRESULT		VSTPM_Encrypt
	(
		VS_TSS_Data*			i_pVSTSSData,
		const BYTE*				i_cpbData,
		const DWORD				i_cdwDataLen,
		BYTE*					o_pbyteOutData,
		DWORD*					o_pdwOutDataLen
	);

	HRESULT		VSTPM_Decrypt
	(
		VS_TSS_Data*			i_pVSTSSData,
		const BYTE*				i_cpbData,
		const DWORD				i_cdwDataLen,
		BYTE*					o_pbyteOutData,
		DWORD*					o_pdwOutDataLen
	);

	HRESULT		VSTPM_EncryptDecryptEnd
	(
		const VS_TSS_Data*		i_cpVSTSSData
	);

	// Sasi 05/05/2003
	// Method to check if the roaming server supports reset password feature		
	HRESULT		VSM_IsResetPasswdSupported
	(
		_bstr_t&			i_tbstrClientInfo, 
		_bstr_t&			i_tbstrClientInfoSig,
		BOOL*				o_boolResetPasswd	
	);

	// Sasi 05/05/2003
	// Method to retrieve secret question associated with user's roaming profile
	HRESULT		VSM_GetSecretQuestion
	(
		VARIANT*			i_pvarWhichSmartCard,
		_bstr_t&			o_tbstrSecretQuestion
	);

	// Sasi 05/05/2003
	// Method to reset user's roaming profile password 
	HRESULT		VSM_ResetPassword
	(
		VARIANT*			i_pvarWhichSmartCard, 
		bstr_t&				i_tbstrSecretAnswer, 
		bstr_t&				i_tbstrNewPasswd
	);

	HRESULT get_VSTPM_TSSVendor(DWORD* o_pdwTSSVendor);

	CVirtualSmartCard();
	virtual ~CVirtualSmartCard();

private :
	CProtectedStorage* pProtectedStorage;
	bool	boolUsePS;
	_bstr_t bstrProfName;
	bool	boolIsRoaming;
	bool	boolSaveLocal;
	int		nNumOfReadOKDomains;
	_bstr_t* pbstrReadOKDomains;
	int		nNumOfWriteOKDomains;
	_bstr_t* pbstrWriteOKDomains;
	int	nPasswordQuality;
	int	nPasswordTimeOut;
	int	nPasswordLength;
	int	nPasswordLockOutTries;
	int	nPasswordUnlockPeriod;

//	WCHAR*	pwszContainerName;
	_bstr_t	tbstrContainerName;

//	BYTE*	m_pbyteContainerContents;
//	DWORD	m_dwContainerContentsLen;
//	CSP_Key_Container*	m_pstructContainer;
	BYTE	m_pbytePubKeyHash [20];

	RSA_Context*		pRSA_Context;
	A_RSA_KEY			RSA_Enc_PublicKey;
	A_RSA_KEY			RSA_Dec_PrivateKey;
	A_RSA_KEY			RSA_Sign_PrivateKey;
	A_RSA_KEY			RSA_Verify_PublicKey;
	BOOL				m_boolRoaming;
	VSRM_SESSION_HANDLE	m_SessionHandle;
	BOOL				m_boolRoamingNameReserved;
	BOOL				m_boolResetPasswdFeature;	// indicates if roaming server supports reset password feature
	
	BYTE*		m_pbyteStorage;
	DWORD		m_dwStorageLen;
	DWORD		m_dwStorageChanged;


	//---------SAMEER----------------------------------------------------------
	CProtectedStorage* pPTAProtectedStorage;
	//-------------------------------------------------------------------------
	CProtectedStorage* pEncPTAProtectedStorage;

	// HostName of the site that opened the profile.
	_bstr_t m_tbstrHostName;
	// Wild card to be used to match instead of m_tbstrHostName.
	_bstr_t m_tbstrProfileOpenHostWildCard;

	// HostName of the site that called VSPTA-Initialize i.e. the current site.
	_bstr_t m_tbstrCurrentHostName;

	_bstr_t m_tbstrPassword;
	_bstr_t m_tbstrAppCtxtName;

	// The profile suffix now used to create the profile filename.
	// e.g. <user>'s <profileissfrndlyname> profile.
	_bstr_t m_tbstrProfileIssFrndlyName;

	// Sasi 05/05/2003
	// Secret Question and Answer associated with roaming profile
	_bstr_t m_tbstrSecretQuestion;
	_bstr_t m_tbstrSecretAnswer;

	// Sasi 06/05/2003
	// User's first name, last name and e-mail address
	_bstr_t m_tbstrFirstName;
	_bstr_t m_tbstrLastName;
	_bstr_t m_tbstrEmail;

	friend HRESULT	SetPasswdFn ( void* i_pvoidPointer, _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut );
	FN_PasswordCallback*		m_pPasswordCallback;
	void*						m_pvoidObjectPTA;

	//---------SAMEER------------------------------------------------------------
	
	DWORD						m_dwIsTPM;
	DWORD						m_dwTSSVendor;


	VS_TPM_CSP_Container		m_structTPMContainer;
	UUID						m_uuidUserRootKey;
	_bstr_t						m_tbstrUserRootPassword;

	UUID						m_uuidMyKey;
	_bstr_t 					m_tbstrTPMKeyPassword;
	DWORD                       m_dwTPMKeyPasswordLen;

	VS_TSS_Context*				m_pVSTSSContext;
	VS_TSS_Key*					m_pUsersRootKey;
	VS_TSS_Hash*				m_pVSTSSHash;

	// Advapi32.dll function pointer
	HMODULE						m_hModAdvapiDll;

	LPFNRegOpenCurrentUser		lpfnRegOpenCurrentUser;
	HKEY						m_hCurrUserKey;

#ifdef VS_TSSDLL
	HMODULE						m_hModTSSDll;
	// VS_TSS function pointers. 
	LPFNCreateContextObject		lpfnCreateContextObject;
	LPFNCreateDataObject		lpfnCreateDataObject;
	LPFNCreateHashObject		lpfnCreateHashObject;
	LPFNCreateKeyObjectURK		lpfnCreateKeyObjectURK;
	LPFNCreateKeyObjectULK		lpfnCreateKeyObjectULK;
	LPFNCreateKeyObjectLoadUK	lpfnCreateKeyObjectLoadUK;
	LPFNCreateKeyObjectImportPublicKey	lpfnCreateKeyObjectImportPublicKey;

#endif // VS_TSSDLL

private:
	HRESULT		HashPublicKey
	(
		const A_RSA_KEY*	i_cpPublicKey,
		BYTE*				pbyteHash
	);

	HRESULT		GetBlobFromKey
	(
		const A_RSA_KEY*	i_cpKey,
		BYTE**				o_ppbyteKeyBlob,
		DWORD*				o_pdwKeyBlobLen
	);

	HRESULT		GetKeyFromBlob
	(
		const BYTE*			i_cpbyteKeyBlob,
		const DWORD			i_cdwKeyBlobLen,
		A_RSA_KEY*			o_pKey
	);

	HRESULT		GetArrayFromBlob
	(
		const byte*		in_pbyteBlob, 
		const DWORD		in_numOfElements,
		const WCHAR*	in_delimiter,
		_bstr_t**		o_ppbstrArray
	);

	HRESULT		GetBlobFromArray
	(
		const _bstr_t*	in_pbstrArray,
		DWORD*			io_pdwArraySize,
		_bstr_t*		o_pbstrBlob,
		DWORD*			o_pdwblobLength,
		_bstr_t			in_tbstrCreator
	);

	bool		ValidateBstrArrayWildCardDomains
	(
		const _bstr_t* i_pbstrWildCardDomains, 
		const int i_nNumOfDomains
	);

	bool		ValidateBstrWildCardDomain
	(
		const _bstr_t i_tbstrWildCardDomain
	);

	bool		CompareWildCardHosts
	(
		const _bstr_t	in_tbstrWildCardHost,
		const _bstr_t	in_tbstrCurrentHost
	);

	HRESULT CVirtualSmartCard::_ExtractBstrsFromArray
	(
		SAFEARRAY* i_pSafeArray,
		const int i_nDims,
		const int i_lBound,
		const int i_uBound,
		_bstr_t* o_ptbstrBstrArr
	);

	HRESULT		PadDataForEncryption
	(
		const BYTE*			i_cpbyteData,
		const DWORD			i_cdwDataLen,
		BYTE**				o_ppbytePaddedData,
		DWORD*				o_pdwPaddedDataLen
	);

	HRESULT		UnPadDataForDecryption
	(
		const BYTE*			i_cpbyteData,
		const DWORD			i_cdwDataLen,
		BYTE**				o_ppbyteUnPaddedData,
		DWORD*				o_pdwUnPaddedDataLen
	);

	HRESULT		PadDataForSignature
	(
		const BYTE*			i_cpbyteData,
		const DWORD			i_cdwDataLen,
		BYTE**				o_ppbytePaddedData,
		DWORD*				o_pdwPaddedDataLen
	);

	HRESULT		UnPadDataForVerify
	(
		const BYTE*			i_cpbyteData,
		const DWORD			i_cdwDataLen,
		BYTE**				o_ppbyteUnPaddedData,
		DWORD*				o_pdwUnPaddedDataLen
	);

	HRESULT		PutDataInSequence
	(
		const BYTE*			i_cpbyteData,
		const DWORD			i_cdwDataLen,
		const DWORD			i_cdwAlgID,
		BYTE**				o_ppbyteDataInSequence,
		DWORD*				o_pdwDataInSequenceLen
	);

	HRESULT		GetDataFromSequence
	(
		const BYTE*			i_cpbyteDataInSequence,
		const DWORD			i_cdwDataLenInSequence,
		const DWORD			i_cdwAlgID,
		BYTE**				o_ppbyteData,
		DWORD*				o_pdwDataLen
	);

	/*HRESULT		GetServersFromArray
	(
		VARIANT*			i_pvarWhichSmartCard,
		DWORD*				o_pdwNumRoamingServers,
		WCHAR***			o_ppwszRoamingServers,
		_bstr_t*			o_ptbstrStorageServer,
		_bstr_t*			o_ptbstrUserName,
		VSRM_ITEM*			o_pvsrmItemStorageServerID,
		VSRM_ITEM***		o_pppvsrmItemRoamingServerIDList,
		_bstr_t*			o_ptbstrProfileIssUniqueID
	);*/
	HRESULT		GetServersFromArray
	(
		VARIANT*			i_pvarWhichSmartCard,
		_bstr_t*			o_ptvstrClientInfo,
		_bstr_t*			o_ptbstrClientInfoSig,
		_bstr_t*			o_ptbstrUserName,
		_bstr_t*			o_ptbstrProfileIssUniqueID
	);

	HRESULT GetRoamingStorage (VARIANT* i_pvarWhichSmartCard, VARIANT* i_pvarPassword, _bstr_t* o_ptbstrUserName);

	bool IsThisDomainAllowedToReadProfileData(const _bstr_t i_tbstrHostName);
	bool IsThisDomainAllowedToWriteProfileData(const _bstr_t i_tbstrHostName);
	HRESULT IsThisDomainAllowedToReadThisApplication(const _bstr_t i_tbstrHostName, bool *o_pboolAllowedApplication);
	HRESULT IsThisDomainAllowedToWriteThisApplication(const _bstr_t i_tbstrHostName, bool *o_pboolAllowedApplication);
	HRESULT GetFullAccessApplicationReadOKDomains
	(
		_bstr_t** o_ppbstrApplicationReadOKDomains, 
		DWORD* o_pdwNumOfApplicationReadOKDomains
	);

	HRESULT GetFullAccessApplicationWriteOKDomains
	(
		_bstr_t** o_ppbstrApplicationWriteOKDomains, 
		DWORD* o_pdwNumOfApplicationWriteOKDomains
	);

//////////////////////////////////////////////////////////////////////////////
//	NEW SECTION ADDED BELOW FOR THE ADDITIONAL FUNCTIONALITY OF TCPA SUPPORT
//	THE FUNCTIONS IN VIRTUAL SMART CARD WILL BE CALLED BY THE VS_TPM_CSP AS
//	WELL AS THE PTA IN TPM MODE.
//////////////////////////////////////////////////////////////////////////////


	HRESULT		VSTPM_GetUserStorageRootKey ();
	HRESULT		VSTPM_CreateUserStorageRootKey ();

	HRESULT		VSTPM_GetUserContainerDetails ();
	HRESULT		VSTPM_SetUserContainerDetails ();

	HRESULT		VSTPM_CheckIfContainerExists ();

	HRESULT		VSTPM_CheckGetPasswordTimeout
	(
		_bstr_t*				o_ptbstrPassword
	);

	HRESULT CheckRoamingVersion (VARIANT* i_pvarWhichSmartCard);

	HRESULT CheckForInfineonTPM(BOOL* boolExists);

};

//	This function existed before adding the TPM support
HRESULT	SetPasswdFn ( _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut );




#endif // !defined(AFX_STORAGE_H__10F26074_E021_11D3_8168_0060B0F885E6__INCLUDED_)

#include <stdio.h>
#include <assert.h>
#include <windows.h>

// TSS specific includes 
#include "tcpa_defines.h"
#include "tcpa_struct.h"
#include "tssapi_error.h"
#include "tss_values.h"

#include <VS_TSS_Context.h>
#include <VS_TSS_Key.h>

// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectURK(const VS_TSS_Context* i_cpContext, 
																		   const UUID            i_cMyUUID,
																		   const DWORD           i_cdwMyPasswordLength,
																		   const BYTE*           i_cMyPasssword, 
																		   DWORD*                o_pdwError)
{
	return new VS_TSS_Key(i_cpContext, 
                       i_cMyUUID,
					   i_cdwMyPasswordLength,
                       i_cMyPasssword, 
				       o_pdwError);
}

extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectULK(const VS_TSS_Context* i_cpContext, 
															   const DWORD           i_cdwKeyLength, 
															   const DWORD           i_cdwKeyUsage,
															   const UUID            i_cMyUUID, 
															   const DWORD           i_cdwMyPasswordLength,
															   const BYTE*           i_cMyPassword,
															   const UUID            i_cParentUUID,
															   const DWORD           i_cdwParentPasswordLength,
															   const BYTE*           i_cParentPasssword, 
															   DWORD*                o_pdwError)
{
	return new VS_TSS_Key(i_cpContext, 
		               i_cdwKeyLength, 
					   i_cdwKeyUsage,
                       i_cMyUUID, 
					   i_cdwMyPasswordLength,
					   i_cMyPassword,
					   i_cParentUUID,
					   i_cdwParentPasswordLength,
                       i_cParentPasssword, 
					   o_pdwError);
}

extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectLoadUK(const VS_TSS_Context* i_cpContext, 
																const UUID            i_cMyUUID,
																const DWORD           i_cdwMyPasswordLength,
																const BYTE*           i_cMyPassword, 
																const UUID            i_cParentUUID,
																const DWORD           i_cdwParentPasswordLength,
																const BYTE*           i_cParentPassword, 
																DWORD*                o_pdwError)
{
	return new VS_TSS_Key(i_cpContext, 
 					   i_cMyUUID,
					   i_cdwMyPasswordLength,
                       i_cMyPassword, 
			    	   i_cParentUUID,
					   i_cdwParentPasswordLength,
                       i_cParentPassword, 
					   o_pdwError);


}


extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectImportPublicKey(const VS_TSS_Context* i_cpContext,
					   const DWORD           i_cdwKeyUsage,
		               const DWORD           i_cdwModulusLength,
				       const BYTE*           i_pbModulusData,
					   DWORD*                o_pdwError,
					   const BYTE            i_cbDummy)
{
	return new VS_TSS_Key(i_cpContext,
					   i_cdwKeyUsage,
		               i_cdwModulusLength,
				       i_pbModulusData,
					   o_pdwError,
					   i_cbDummy);


}


// Implementation of VS_TSS_Key

// Create a user storage key
// XXX The input password length had been padded by 1
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_cpContext, 
                       const UUID            i_cMyUUID,
					   const DWORD           i_cdwMyPasswordLength,
                       const BYTE*           i_cMyPasssword, 
				       DWORD*                o_pdwError)
{
	UUID     tssuuidUSK;
    ITCPAKeyPtr	 pSRKKeyObject;

	LPWSTR		 lpszMyUUID = NULL;
	DWORD dwError;

	*o_pdwError = S_OK;

	m_pbModulusData = NULL;
	m_dwModulusLength = 0;

	do {

		try //Handle exceptions
		{

			m_dwKeyUsage = 0; // Neither for encryption, nor for signature 

			memcpy ((void*) &tssuuidUSK, (const void*) &i_cMyUUID, sizeof(UUID));

			dwError = UuidToStringW((UUID *) &i_cMyUUID,&lpszMyUUID);

			if(dwError != RPC_S_OK)
			{
				*o_pdwError = HRESULT_FROM_WIN32(dwError);
				break;
			}

			// get pointers to Context and SRK objects
			((VS_TSS_Context*)i_cpContext)->GetContext( (ITCPAContextPtr *) &m_pContextObject);
			((VS_TSS_Context*)i_cpContext)->GetSRK( (ITCPAKeyPtr *) &pSRKKeyObject);


			// create a key object for user storage key
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_RSAKEY, 
										TSS_KEY_SIZE_2048 | TSS_KEY_TYPE_STORAGE |
										TSS_KEY_MIGRATABLE | TSS_KEY_NO_AUTHORIZATION, 
										(IUnknown **)&m_pKeyObject);


			// set usage and migration policies for a newly created key object
			ITCPAPolicyPtr pKeyUsagePolicyObject = NULL;

			//Create usage policy object, set the secret and assign it to the key object
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_POLICY, TSS_POLICY_USAGE, 
										 (IUnknown **)&pKeyUsagePolicyObject);
			pKeyUsagePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwMyPasswordLength, 
											(unsigned char*)i_cMyPasssword);
			pKeyUsagePolicyObject->AssignToObject(m_pKeyObject);

			//Prepare the migration policy object for create key
			ITCPAPolicyPtr pKeyMigratePolicyObject = NULL;

			//Create migration policy object, set the secret and assign it to the key object
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_POLICY, TSS_POLICY_MIGRATION, 
										 (IUnknown **)&pKeyMigratePolicyObject);
			pKeyMigratePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwMyPasswordLength, 
											  (unsigned char*)i_cMyPasssword);
			pKeyMigratePolicyObject->AssignToObject(m_pKeyObject);
			

			// create user storage key
			m_pKeyObject->CreateKey(pSRKKeyObject, NULL);


			//Register key in persistent user storage
			ITCPAPersistentStoragePtr pPersistentStorage(m_pContextObject);
			pPersistentStorage->RegisterKey(m_pKeyObject,TSS_PS_TYPE_USER,lpszMyUUID,TSS_PS_TYPE_SYSTEM,TSS_GUID_SRK);

			// get modulus for the new key
			ITCPAAttribPtr pKeyAttrib(m_pKeyObject);
			pKeyAttrib->GetAttribData(TSS_TSPATTRIB_RSAKEY_INFO,
									  TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									  (unsigned int*)&m_dwModulusLength, 
									  &m_pbModulusData);

		}
		catch(_com_error e) 
		{
    		*o_pdwError = e.Error();
		}
		catch(...) 
		{
			*o_pdwError = E_FAIL;
		}

	} while (0);

	if(lpszMyUUID)
		RpcStringFreeW(&lpszMyUUID);

}

// Create a user leaf key
// XXX The input password length had been padded by 1
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_cpContext, 
		               const DWORD           i_cdwKeyLength, 
					   const DWORD           i_cdwKeyUsage,
                       const UUID            i_cMyUUID, 
					   const DWORD           i_cdwMyPasswordLength,
					   const BYTE*           i_cMyPassword,
					   const UUID            i_cParentUUID,
					   const DWORD           i_cdwParentPasswordLength,
                       const BYTE*           i_cParentPasssword, 
					   DWORD*                o_pdwError)
{
	UUID     tssuuidUSK;
	UUID     tssuuidUK;
	DWORD        dwKeyFlags;

	LPWSTR		 lpszParentUUID = NULL;
	LPWSTR		 lpszMyUUID = NULL;
	DWORD dwError;

    ITCPAKeyPtr	 pSRKKeyObject;

	*o_pdwError = S_OK;

	m_pbModulusData = NULL;
	m_dwModulusLength = 0;

	do {

		try //Handle exceptions
		{

			m_dwKeyUsage = i_cdwKeyUsage;

			memcpy ((void*) &tssuuidUK, (const void*) &i_cMyUUID, sizeof(UUID));
			memcpy ((void*) &tssuuidUSK, (const void*) &i_cParentUUID, sizeof(UUID));

			dwError = UuidToStringW((UUID *) &i_cParentUUID,&lpszParentUUID);
			if(dwError != RPC_S_OK)
			{
				*o_pdwError = HRESULT_FROM_WIN32(dwError);
				break;
			}

			dwError = UuidToStringW((UUID *) &i_cMyUUID,&lpszMyUUID);
			if(dwError != RPC_S_OK)
			{
				*o_pdwError = HRESULT_FROM_WIN32(dwError);
				break;
			}

			// get pointers to context and SRK objects
			((VS_TSS_Context*)i_cpContext)->GetContext( (ITCPAContextPtr *) &m_pContextObject);
			((VS_TSS_Context*)i_cpContext)->GetSRK( (ITCPAKeyPtr *) &pSRKKeyObject);


			// load parent key (user storage key)
			ITCPAPersistentStoragePtr pPersistentStorage(m_pContextObject);

			// Load SRK
			// set secret for SRK 
			ITCPAAuthPtr pSRKKeyAuth(pSRKKeyObject);
			ITCPAPolicyPtr pSRKPolicyObject = NULL;
			BYTE pbSRKSecret[] = TSS_WELL_KNOWN_SECRET;
			pSRKKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pSRKPolicyObject);
			pSRKPolicyObject->SetSecret(TSS_SECRET_MODE_SHA1, sizeof(pbSRKSecret), pbSRKSecret);

			// load parent key (user storage key)
			ITCPAKeyPtr pParentKeyObject = NULL;
			pPersistentStorage->LoadKeyByUUID(TSS_PS_TYPE_USER,lpszParentUUID,&pParentKeyObject);

			ITCPAAuthPtr pParentKeyAuth(pParentKeyObject);
			ITCPAPolicyPtr pParentUsagePolicyObject;
			pParentKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pParentUsagePolicyObject);
			pParentUsagePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwParentPasswordLength, (unsigned char*)i_cParentPasssword);

			
			dwKeyFlags = TSS_KEY_MIGRATABLE | 
					   TSS_KEY_AUTHORIZATION |
					   TSS_KEY_TYPE_LEGACY ;
			if (i_cdwKeyLength == 512) {
				dwKeyFlags |= TSS_KEY_SIZE_512; 			   
			}
			else if (i_cdwKeyLength == 1024) {
				dwKeyFlags |= TSS_KEY_SIZE_1024; 			   
			}
			else if (i_cdwKeyLength == 2048) {
				dwKeyFlags |= TSS_KEY_SIZE_2048; 			   
			}
			else {
				*o_pdwError = E_INVALIDARG;
				break;	
			}


			// create a key object for user key
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_RSAKEY, 
										   dwKeyFlags, 
										   (IUnknown **)&m_pKeyObject);


			ITCPAAttribPtr pKeyAttrib(m_pKeyObject);
			pKeyAttrib->SetAttribUint32(TSS_TSPATTRIB_KEY_INFO,
										TSS_TSPATTRIB_KEYINFO_ENCSCHEME,
										TSS_ES_RSAESPKCSV15);

			pKeyAttrib->SetAttribUint32(TSS_TSPATTRIB_KEY_INFO,
										TSS_TSPATTRIB_KEYINFO_SIGSCHEME,
										TSS_SS_RSASSAPKCS1V15_DER);

			// set usage and migration policies for a newly created key object
			ITCPAPolicyPtr pKeyUsagePolicyObject = NULL;

			//Create usage policy object, set the secret and assign it to the key object
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_POLICY, TSS_POLICY_USAGE, 
										 (IUnknown **)&pKeyUsagePolicyObject);
			pKeyUsagePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwMyPasswordLength, 
											(unsigned char*)i_cMyPassword);
			pKeyUsagePolicyObject->AssignToObject(m_pKeyObject);

			//Prepare the migration policy object for create key
			ITCPAPolicyPtr pKeyMigratePolicyObject = NULL;
			//Create migration policy object, set the secret and assign it to the key object
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_POLICY, TSS_POLICY_MIGRATION, 
										 (IUnknown **)&pKeyMigratePolicyObject);
			pKeyMigratePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwMyPasswordLength, 
											  (unsigned char*)i_cMyPassword);
			pKeyMigratePolicyObject->AssignToObject(m_pKeyObject);
			
			// create user key
			m_pKeyObject->CreateKey(pParentKeyObject, NULL);


			//RegisterKey
			pPersistentStorage->RegisterKey(m_pKeyObject,TSS_PS_TYPE_USER,lpszMyUUID,TSS_PS_TYPE_USER,lpszParentUUID);

			// get modulus for the new key
			pKeyAttrib->GetAttribData(TSS_TSPATTRIB_RSAKEY_INFO,
									  TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									  (unsigned int*)&m_dwModulusLength, 
									  &m_pbModulusData);


		}
		catch(_com_error e) 
		{
    		*o_pdwError = e.Error();
		}
		catch(...) 
		{
			*o_pdwError = E_FAIL;
		}

	} while (0);

	if(lpszParentUUID)
		RpcStringFreeW(&lpszParentUUID);

	if(lpszMyUUID)
		RpcStringFreeW(&lpszMyUUID);

}

// Load a user leaf key
// XXX The input password length had been padded by 1
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_cpContext, 
 					   const UUID            i_cMyUUID,
					   const DWORD           i_cdwMyPasswordLength,
                       const BYTE*           i_cMyPassword, 
			    	   const UUID            i_cParentUUID,
					   const DWORD           i_cdwParentPasswordLength,
                       const BYTE*           i_cParentPassword, 
					   DWORD*                o_pdwError)
{
	UUID     tssuuidUSK;
	UUID     tssuuidUK;

	LPWSTR		 lpszParentUUID = NULL;
	LPWSTR		 lpszMyUUID = NULL;

    ITCPAKeyPtr	 pSRKKeyObject;
	DWORD dwError;

	*o_pdwError = S_OK;

	m_pbModulusData = NULL;
	m_dwModulusLength = 0;

	do {
		try 
		{
			memcpy ((void*) &tssuuidUSK, (const void*) &i_cParentUUID, sizeof(UUID));
			memcpy ((void*) &tssuuidUK, (const void*) &i_cMyUUID, sizeof(UUID));

			dwError = UuidToStringW((UUID *) &i_cParentUUID,&lpszParentUUID);
			if(dwError != RPC_S_OK)
			{
				*o_pdwError = HRESULT_FROM_WIN32(dwError);
				break;
			}

			dwError = UuidToStringW((UUID *) &i_cMyUUID,&lpszMyUUID);
			if(dwError != RPC_S_OK)
			{
				*o_pdwError = HRESULT_FROM_WIN32(dwError);
				break;
			}

			// get pointers to context and SRK objects
			((VS_TSS_Context*)i_cpContext)->GetContext( (ITCPAContextPtr *) &m_pContextObject);
			((VS_TSS_Context*)i_cpContext)->GetSRK( (ITCPAKeyPtr *) &pSRKKeyObject);

			ITCPAPersistentStoragePtr pPersistentStorage(m_pContextObject);

			// Load SRK
			// set secret for SRK 
			ITCPAAuthPtr pSRKKeyAuth(pSRKKeyObject);
			ITCPAPolicyPtr pSRKPolicyObject = NULL;
			BYTE pbSRKSecret[] = TSS_WELL_KNOWN_SECRET;
			pSRKKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pSRKPolicyObject);
			pSRKPolicyObject->SetSecret(TSS_SECRET_MODE_SHA1, sizeof(pbSRKSecret), pbSRKSecret);


			// load parent key (user storage key)
			ITCPAKeyPtr pParentKeyObject = NULL;
			pPersistentStorage->LoadKeyByUUID(TSS_PS_TYPE_USER,lpszParentUUID,&pParentKeyObject);

			// set secret for parent key
			ITCPAAuthPtr pParentKeyAuth(pParentKeyObject);
			ITCPAPolicyPtr pParentUsagePolicyObject;
			pParentKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pParentUsagePolicyObject);
			pParentUsagePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwParentPasswordLength, (unsigned char*)i_cParentPassword);


			// load user key
			pPersistentStorage->GetKeyByUUID(TSS_PS_TYPE_USER,lpszMyUUID,&m_pKeyObject);
			m_pKeyObject->LoadKey(pParentKeyObject);

			// set secret for user key
			ITCPAAuthPtr pKeyAuth(m_pKeyObject);
			ITCPAPolicyPtr pUsagePolicyObject;
			pKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pUsagePolicyObject);
			pUsagePolicyObject->SetSecret(TSS_SECRET_MODE_PLAIN, i_cdwMyPasswordLength, (unsigned char*)i_cMyPassword);


			// get modulus for the user key
			ITCPAAttribPtr pKeyAttrib(m_pKeyObject);

			pKeyAttrib->GetAttribData(TSS_TSPATTRIB_RSAKEY_INFO,
									  TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									  (unsigned int*)&m_dwModulusLength, 
									  &m_pbModulusData);

		}
		catch(_com_error e) 
		{
    		*o_pdwError = e.Error();
		}
		catch(...) 
		{
			*o_pdwError = E_FAIL;
		}


	} while (0);

	if(lpszParentUUID)
		RpcStringFreeW(&lpszParentUUID);

	if(lpszMyUUID)
		RpcStringFreeW(&lpszMyUUID);

}
       
// Import a public key
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_chContext,
					   const DWORD           i_cdwKeyUsage,
		               const DWORD           i_cdwModulusLength,
				       const BYTE*           i_pbModulusData,
					   DWORD*                o_pdwError,
					   const BYTE            i_cbDummy)
{
	*o_pdwError = E_NOTIMPL;
}

// Destroy the TSS key object
VS_TSS_Key::~VS_TSS_Key()
{
	if(m_pbModulusData)
	{
	    ::CoTaskMemFree(m_pbModulusData);
		m_dwModulusLength = 0;
	}
}

// Get the key usage	   
HRESULT VS_TSS_Key::GetKeyUsage(DWORD* o_pdwKeyUsage)
{
	*o_pdwKeyUsage = m_dwKeyUsage;

	return 0;
}
       
// Get the key length
HRESULT VS_TSS_Key::GetKeyLength(DWORD* o_pdwKeyLength)
{
	*o_pdwKeyLength = m_dwModulusLength * 8;

	return 0;
}

// Get the modulus length
HRESULT VS_TSS_Key::GetModulusLength(DWORD* o_pdwModulusLength)
{
	*o_pdwModulusLength = m_dwModulusLength;

	return 0;
}

	   
HRESULT VS_TSS_Key::GetModulus(DWORD* o_pdwModulusLength, 
		                       BYTE** o_pbModulusData)
{
	*o_pdwModulusLength = m_dwModulusLength;
	*o_pbModulusData = m_pbModulusData;

	return 0;
}

// Get the TSS key handle
HRESULT VS_TSS_Key::GetKey(ITCPAKeyPtr* o_pKey)
{
	*o_pKey = m_pKeyObject;

	return 0;
}


HRESULT VS_TSS_Key::GetPublicKey(DWORD* o_pdwKeyLength, 
		                  BYTE** o_pbPublicKey)
{
	HRESULT hResult = S_OK;

	BYTE*	   pbPublicKey			=	NULL;
	DWORD	   dwPublicKeyLen		=	0;

	do {

		try 
		{
			m_pKeyObject->GetPubKey((unsigned int *) o_pdwKeyLength,
								 o_pbPublicKey);
		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
    		hResult = E_FAIL;
		}

	} while (0);

	return hResult;
}

HRESULT VS_TSS_Key::GetExponent(DWORD* o_pdwExponentLength, 
		                  BYTE** o_pbExponent)
{
	HRESULT hResult = S_OK;

	do {

		try 
		{
			ITCPAAttribPtr pKeyAttrib(m_pKeyObject);

			pKeyAttrib->GetAttribData(TSS_TSPATTRIB_RSAKEY_INFO,
									  TSS_TSPATTRIB_KEYINFO_RSA_EXPONENT,
									  (unsigned int*) o_pdwExponentLength, 
									  o_pbExponent);

		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
    		hResult = E_FAIL;
		}

	} while (0);

	return hResult;
}


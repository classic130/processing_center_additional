#include <stdio.h>
#include <assert.h>
#include <windows.h>

#include <tcpa_literals.h>
#include <tcpa_types.h>
#include <spi_literals.h>
#include <spi_exports.h>

#include <VS_TSS_Context.h>
#include <VS_TSS_Key.h>

// XXX Used only for creating a key object from public key only
#define DEFAULT_UK_DUMMY_PASSOWRD ("userpass")

// XXX IBM CSS always set SRK password to "SRK PWD"
#define IBM_CSS_SRK_PASSWORD ("SRK PWD")

#define VS_TSS_CHECK_RESULT(result) { if (result != TSS_SUCCESS) break; }

// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectURK(const VS_TSS_Context* i_chContext, 
																		   const UUID            i_cMyUUID,
																		   const DWORD           i_cdwMyPasswordLength,
																		   const BYTE*           i_cMyPasssword, 
																		   DWORD*                o_pdwError)
{
	return new VS_TSS_Key(i_chContext, 
                       i_cMyUUID,
					   i_cdwMyPasswordLength,
                       i_cMyPasssword, 
				       o_pdwError);
}

extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectULK(const VS_TSS_Context* i_chContext, 
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
	return new VS_TSS_Key(i_chContext, 
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

extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectLoadUK(const VS_TSS_Context* i_chContext, 
																const UUID            i_cMyUUID,
																const DWORD           i_cdwMyPasswordLength,
																const BYTE*           i_cMyPassword, 
																const UUID            i_cParentUUID,
																const DWORD           i_cdwParentPasswordLength,
																const BYTE*           i_cParentPassword, 
																DWORD*                o_pdwError)
{
	return new VS_TSS_Key(i_chContext, 
 					   i_cMyUUID,
					   i_cdwMyPasswordLength,
                       i_cMyPassword, 
			    	   i_cParentUUID,
					   i_cdwParentPasswordLength,
                       i_cParentPassword, 
					   o_pdwError);


}


extern "C" __declspec(dllexport) VS_TSS_Key* CreateKeyObjectImportPublicKey(const VS_TSS_Context* i_chContext,
					   const DWORD           i_cdwKeyUsage,
		               const DWORD           i_cdwModulusLength,
				       const BYTE*           i_pbModulusData,
					   DWORD*                o_pdwError,
					   const BYTE            i_cbDummy)
{
	return new VS_TSS_Key(i_chContext,
					   i_cdwKeyUsage,
		               i_cdwModulusLength,
				       i_pbModulusData,
					   o_pdwError,
					   i_cbDummy);


}


// Implementation of VS_TSS_Key

// Create a user storage key
// XXX The input password length had been padded by 1
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_chContext, 
                       const UUID            i_cMyUUID,
					   const DWORD           i_cdwMyPasswordLength,
                       const BYTE*           i_cMyPasssword, 
				       DWORD*                o_pdwError)
{
	TSS_HKEY     hSRK;
	TSS_UUID     tssuuidSRK;
	TSS_UUID     tssuuidUSK;
	TSS_HPOLICY  hSRKUsagePolicy;
	TSS_HPOLICY  hSRKMigrationPolicy;
	TSS_HPOLICY  hUSKUsagePolicy;
	TSS_HPOLICY  hUSKMigrationPolicy;
	TSS_RESULT   tssResult;

	*o_pdwError = 0;

	do {
		m_dwKeyUsage = 0; // Neither for encryption, nor for signature

		memcpy ((void*) &tssuuidUSK, (const void*) &i_cMyUUID, sizeof(UUID));

		((VS_TSS_Context*)i_chContext)->GetHContext(&m_hContext);
		((VS_TSS_Context*)i_chContext)->GetSRK(&hSRK);
		((VS_TSS_Context*)i_chContext)->GetSRKUUID(&tssuuidSRK);

		// SRK secret
		tssResult = Tspi_GetPolicyObject(hSRK, 
									     TSS_POLICY_USAGE, 
									     &hSRKUsagePolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetPolicyObject(hSRK, 
			                             TSS_POLICY_MIGRATION, 
									     &hSRKMigrationPolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hSRKUsagePolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              strlen(IBM_CSS_SRK_PASSWORD) + 1, 
			                              (unsigned char*)IBM_CSS_SRK_PASSWORD);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hSRKMigrationPolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              strlen(IBM_CSS_SRK_PASSWORD) + 1, 
			                              (unsigned char*)IBM_CSS_SRK_PASSWORD);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Context_CreateObject(m_hContext, 
			                                  TSS_OBJECT_TYPE_RSAKEY, 
									          TSS_KEY_SIZE_2048 | 
									          TSS_KEY_TYPE_STORAGE | 
									          TSS_KEY_MIGRATABLE | 
									          TSS_KEY_NO_AUTHORIZATION, 
									          &m_hKey);
		VS_TSS_CHECK_RESULT(tssResult);

/*
		tssResult = Tspi_SetAttribUint32(m_hKey,
					TSS_TSPATTRIB_KEY_INFO,
					TSS_TSPATTRIB_KEYINFO_ENCSCHEME,
					//TSS_TSPATTRIB_KEYINFO_SIGSCHEME,
					TSS_ES_RSAESPKCSV15);
					//TSS_SS_RSASSAPKCS1V15_SHA1);

		tssResult = Tspi_SetAttribUint32(m_hKey,
					TSS_TSPATTRIB_KEY_INFO,
					//TSS_TSPATTRIB_KEYINFO_ENCSCHEME,
					TSS_TSPATTRIB_KEYINFO_SIGSCHEME,
					//TSS_ES_RSAESPKCSV15);
					TSS_SS_RSASSAPKCS1V15_SHA1);

*/		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
									     TSS_POLICY_USAGE, 
									     &hUSKUsagePolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
			                             TSS_POLICY_MIGRATION, 
									     &hUSKMigrationPolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hUSKUsagePolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwMyPasswordLength, 
			                              (unsigned char*)i_cMyPasssword);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hUSKMigrationPolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwMyPasswordLength, 
			                              (unsigned char*)i_cMyPasssword);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Key_CreateKey(m_hKey, hSRK, NULL);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Context_RegisterKey(m_hContext, 
										     m_hKey, 
										     TSS_PS_TYPE_SYSTEM, 
			                                 tssuuidUSK,
										     TSS_PS_TYPE_SYSTEM,	
										     tssuuidSRK);
		VS_TSS_CHECK_RESULT(tssResult);

		// XXX IBM TSS seems to fail on this call
		/*
		tssResult = Tspi_GetAttribData(m_hKey,
							           TSS_TSPATTRIB_RSAKEY_INFO,
								       TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									   (unsigned int*)&m_dwModulusLength,
								       &m_pbModulusData);
		VS_TSS_CHECK_RESULT(tssResult);		
		*/

/*
		BYTE *pubKeyData = NULL;
		UINT32 pubKeyLen;

		// get public key blob
		tssResult = Tspi_Key_GetPubKey(m_hKey,
										&pubKeyLen,
										&pubKeyData);

		VS_TSS_CHECK_RESULT(tssResult);

		if(NULL != pubKeyData)
		{
			// get key length
			BYTE keyLen[4];
			keyLen[0] = pubKeyData[27];
			keyLen[1] = pubKeyData[26];
			keyLen[2] = pubKeyData[25];
			keyLen[3] = pubKeyData[24];


			memcpy(&m_dwModulusLength, keyLen, 4);

			m_pbModulusData = (unsigned char*)malloc(m_dwModulusLength);
			if (!m_pbModulusData) {
				*o_pdwError = E_OUTOFMEMORY;
				break;
			}

			memcpy(m_pbModulusData, &pubKeyData[28], m_dwModulusLength);

			Tspi_Context_FreeMemory(m_hContext, pubKeyData);
		}
*/		
		m_dwModulusLength = 0x80;
		m_pbModulusData = 0;

	} while (0);
		
	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		*o_pdwError = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
	}
}

// Create a user leaf key
// XXX The input password length had been padded by 1
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_chContext, 
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
	TSS_UUID     tssuuidUSK;
	TSS_UUID     tssuuidUK;
	TSS_HKEY     hUSK; 
	TSS_HPOLICY  hUSKUsagePolicy;
	TSS_HPOLICY  hUSKMigrationPolicy;
    TSS_HPOLICY  hUKUsagePolicy;
	TSS_HPOLICY  hUKMigrationPolicy;
	DWORD        dwKeyFlags;
	TSS_RESULT   tssResult;

	*o_pdwError = 0;

	do {
		m_dwKeyUsage = i_cdwKeyUsage;

		memcpy ((void*) &tssuuidUK, (const void*) &i_cMyUUID, sizeof(UUID));
		memcpy ((void*) &tssuuidUSK, (const void*) &i_cParentUUID, sizeof(UUID));

		((VS_TSS_Context*)i_chContext)->GetHContext(&m_hContext);

		// Load parent key
        tssResult = Tspi_Context_LoadKeyByUUID(m_hContext,
			                                   TSS_PS_TYPE_SYSTEM, 
											   tssuuidUSK, 
											   &hUSK);
		VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_GetPolicyObject(hUSK, 
			                             TSS_POLICY_USAGE, 
									     &hUSKUsagePolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		tssResult = Tspi_GetPolicyObject(hUSK, 
			                             TSS_POLICY_MIGRATION, 
									     &hUSKMigrationPolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		tssResult = Tspi_Policy_SetSecret(hUSKUsagePolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwParentPasswordLength, 
			                              (unsigned char*)i_cParentPasssword);
		VS_TSS_CHECK_RESULT(tssResult);
		tssResult = Tspi_Policy_SetSecret(hUSKMigrationPolicy, 
									      TSS_SECRET_MODE_PLAIN, 
									      i_cdwParentPasswordLength,
			                              (unsigned char*)i_cParentPasssword);
		VS_TSS_CHECK_RESULT(tssResult);
		
		dwKeyFlags = TSS_KEY_TYPE_LEGACY | 
				   TSS_KEY_MIGRATABLE | 
				   TSS_KEY_AUTHORIZATION;
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
			*o_pdwError = ERROR_INVALID_PARAMETER;
			break;	
		}

		tssResult = Tspi_Context_CreateObject(m_hContext, 
								              TSS_OBJECT_TYPE_RSAKEY, 
									          dwKeyFlags,
									          &m_hKey);
		VS_TSS_CHECK_RESULT(tssResult);


		tssResult = Tspi_SetAttribUint32(m_hKey,
					TSS_TSPATTRIB_KEY_INFO,
					TSS_TSPATTRIB_KEYINFO_ENCSCHEME,
					TSS_ES_RSAESPKCSV15);

		tssResult = Tspi_SetAttribUint32(m_hKey,
					TSS_TSPATTRIB_KEY_INFO,
					TSS_TSPATTRIB_KEYINFO_SIGSCHEME,
					TSS_SS_RSASSAPKCS1V15_DER);


		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
									     TSS_POLICY_USAGE, 
									     &hUKUsagePolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
			                             TSS_POLICY_MIGRATION, 
									     &hUKMigrationPolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hUKUsagePolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwMyPasswordLength, 
			                              (unsigned char*)i_cMyPassword);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hUKMigrationPolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwMyPasswordLength, 
			                              (unsigned char*)i_cMyPassword);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Key_CreateKey(m_hKey, hUSK, NULL);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Context_RegisterKey(m_hContext, 
										     m_hKey, 
										     TSS_PS_TYPE_SYSTEM, 
			                                 tssuuidUK,
										     TSS_PS_TYPE_SYSTEM,	
										     tssuuidUSK);
		VS_TSS_CHECK_RESULT(tssResult);
		
		// XXX IBM TSS seems to fail on this call

//		m_pbModulusData = new BYTE [100];
//		m_dwModulusLength = 100;

		tssResult = Tspi_GetAttribData(m_hKey,
							           TSS_TSPATTRIB_RSAKEY_INFO,
								       TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									   (unsigned int*)&m_dwModulusLength,
								       &m_pbModulusData);
		VS_TSS_CHECK_RESULT(tssResult);
		
/*
		BYTE *pubKeyData = NULL;
		UINT32 pubKeyLen;

		// get public key blob
		tssResult = Tspi_Key_GetPubKey(m_hKey,
										&pubKeyLen,
										&pubKeyData);

		VS_TSS_CHECK_RESULT(tssResult);

		if(NULL != pubKeyData)
		{
			// get key length
			BYTE keyLen[4];
			keyLen[0] = pubKeyData[27];
			keyLen[1] = pubKeyData[26];
			keyLen[2] = pubKeyData[25];
			keyLen[3] = pubKeyData[24];


			memcpy(&m_dwModulusLength, keyLen, 4);

			m_pbModulusData = (unsigned char*)malloc(m_dwModulusLength);
			if (!m_pbModulusData) {
				*o_pdwError = E_OUTOFMEMORY;
				break;
			}

			memcpy(m_pbModulusData, &pubKeyData[28], m_dwModulusLength);

			Tspi_Context_FreeMemory(m_hContext, pubKeyData);
		}
*/		
//		m_dwModulusLength = 0x80;
//		m_pbModulusData = 0;

	} while (0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		*o_pdwError = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
	}
}

// Load a user leaf key
// XXX The input password length had been padded by 1
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_chContext, 
 					   const UUID            i_cMyUUID,
					   const DWORD           i_cdwMyPasswordLength,
                       const BYTE*           i_cMyPassword, 
			    	   const UUID            i_cParentUUID,
					   const DWORD           i_cdwParentPasswordLength,
                       const BYTE*           i_cParentPassword, 
					   DWORD*                o_pdwError)
{
	TSS_UUID     tssuuidUSK;
	TSS_UUID     tssuuidUK;
	TSS_HKEY     hUSK; 
    TSS_HPOLICY  hUKUsagePolicy;
	TSS_HPOLICY  hUKMigrationPolicy;
	TSS_RESULT   tssResult;

	*o_pdwError = 0;

	do {
		memcpy ((void*) &tssuuidUSK, (const void*) &i_cParentUUID, sizeof(UUID));
		memcpy ((void*) &tssuuidUK, (const void*) &i_cMyUUID, sizeof(UUID));

		((VS_TSS_Context*)i_chContext)->GetHContext(&m_hContext);

		// Load parent key
		tssResult = Tspi_Context_LoadKeyByUUID(m_hContext,
			                                   TSS_PS_TYPE_SYSTEM, 
											   tssuuidUSK, 
											   &hUSK);
		VS_TSS_CHECK_RESULT(tssResult);

		// Load this key
		tssResult = Tspi_Context_LoadKeyByUUID(m_hContext,
			                                   TSS_PS_TYPE_SYSTEM, 
											   tssuuidUK, 
											   &m_hKey);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
									     TSS_POLICY_USAGE, 
									     &hUKUsagePolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
			                             TSS_POLICY_MIGRATION, 
									     &hUKMigrationPolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hUKUsagePolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwMyPasswordLength, 
			                              (unsigned char*)i_cMyPassword);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_Policy_SetSecret(hUKMigrationPolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              i_cdwMyPasswordLength, 
			                              (unsigned char*)i_cMyPassword);
		VS_TSS_CHECK_RESULT(tssResult);

		// XXX IBM TSS seems to fail on this call
		/*
		tssResult = Tspi_GetAttribData(m_hKey,
			                           TSS_TSPATTRIB_RSAKEY_INFO,
								       TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									   (unsigned int*)&m_dwModulusLength,
								       &m_pbModulusData);
		VS_TSS_CHECK_RESULT(tssResult);
		*/

		BYTE *pubKeyData = NULL;
		UINT32 pubKeyLen;

		// get public key blob
		tssResult = Tspi_Key_GetPubKey(m_hKey,
										&pubKeyLen,
										&pubKeyData);

		VS_TSS_CHECK_RESULT(tssResult);

		if(NULL != pubKeyData)
		{
			// get key length
			BYTE keyLen[4];
			keyLen[0] = pubKeyData[27];
			keyLen[1] = pubKeyData[26];
			keyLen[2] = pubKeyData[25];
			keyLen[3] = pubKeyData[24];


			memcpy(&m_dwModulusLength, keyLen, 4);

			m_pbModulusData = (unsigned char*)malloc(m_dwModulusLength);
			if (!m_pbModulusData) {
				*o_pdwError = E_OUTOFMEMORY;
				break;
			}

			memcpy(m_pbModulusData, &pubKeyData[28], m_dwModulusLength);

			Tspi_Context_FreeMemory(m_hContext, pubKeyData);
		}

//		m_dwModulusLength = 0x80;
//		m_pbModulusData = 0;

	} while (0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		*o_pdwError = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
	}
}
       
// Import a public key
VS_TSS_Key::VS_TSS_Key(const VS_TSS_Context* i_chContext,
					   const DWORD           i_cdwKeyUsage,
		               const DWORD           i_cdwModulusLength,
				       const BYTE*           i_pbModulusData,
					   DWORD*                o_pdwError,
					   const BYTE            i_cbDummy)
{
	TSS_HPOLICY  hUsagePolicy;
	TSS_HPOLICY  hMigrationPolicy;
	DWORD        dwKeyLength;
	DWORD        dwKeyFlags;
	BYTE*        pubKeyData;
	UINT32       pubKeyLen;
	TSS_RESULT   tssResult;

	*o_pdwError = 0;

	do {
		m_dwKeyUsage = i_cdwKeyUsage;
		dwKeyLength = i_cdwModulusLength * 8;

		((VS_TSS_Context*)i_chContext)->GetHContext(&m_hContext); 
		
		dwKeyFlags = TSS_KEY_TYPE_LEGACY | 
				     TSS_KEY_MIGRATABLE | 
				     TSS_KEY_NO_AUTHORIZATION;
		if (dwKeyLength == 512) {
			dwKeyFlags |= TSS_KEY_SIZE_512; 			   
		}
		else if (dwKeyLength == 1024) {
			dwKeyFlags |= TSS_KEY_SIZE_1024; 			   
		}
		else if (dwKeyLength == 2048) {
			dwKeyFlags |= TSS_KEY_SIZE_2048; 			   
		}
		else {
			*o_pdwError = ERROR_INVALID_PARAMETER;
			break;	
		}

		tssResult = Tspi_Context_CreateObject(m_hContext,
							       		      TSS_OBJECT_TYPE_RSAKEY,
											  dwKeyFlags,
			                                  &m_hKey);
		VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_SetAttribUint32(m_hKey,
					TSS_TSPATTRIB_KEY_INFO,
					TSS_TSPATTRIB_KEYINFO_ENCSCHEME,
					TSS_ES_RSAESPKCSV15);
		VS_TSS_CHECK_RESULT(tssResult);

		
		tssResult = Tspi_GetPolicyObject(m_hKey, 
			                             TSS_POLICY_USAGE, 
									     &hUsagePolicy);
		VS_TSS_CHECK_RESULT(tssResult);
		tssResult = Tspi_GetPolicyObject(m_hKey, 
			                             TSS_POLICY_MIGRATION, 
									     &hMigrationPolicy);
		VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_Policy_SetSecret(hUsagePolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              strlen(DEFAULT_UK_DUMMY_PASSOWRD) + 1, 
			                              (unsigned char*)(DEFAULT_UK_DUMMY_PASSOWRD));
		VS_TSS_CHECK_RESULT(tssResult);
		tssResult = Tspi_Policy_SetSecret(hMigrationPolicy, 
			                              TSS_SECRET_MODE_PLAIN, 
			                              strlen(DEFAULT_UK_DUMMY_PASSOWRD) + 1, 
			                              (unsigned char*)(DEFAULT_UK_DUMMY_PASSOWRD));
		VS_TSS_CHECK_RESULT(tssResult);
		
		// Set public key blob
		pubKeyLen = 28 + i_cdwModulusLength;
		pubKeyData = (unsigned char*)malloc(pubKeyLen);
		if (!pubKeyData) {
			*o_pdwError = E_OUTOFMEMORY;
			break;
		}

		pubKeyData[0] = 00;
		pubKeyData[1] = 00;
		pubKeyData[2] = 00;
		pubKeyData[3] = 01;  // RSA Key
		pubKeyData[4] = 00;
		pubKeyData[5] = 02;  // RSA PKCSv15
		pubKeyData[6] = 00;
		pubKeyData[7] = 02;  // RSA PKCSv15_SHA1
		pubKeyData[8] = 0x00;
		pubKeyData[9] = 0x00;
		pubKeyData[10] = 0x00;
		pubKeyData[11] = 0x0c; // Parm
		pubKeyData[12] = 0x00;
		pubKeyData[13] = 0x00;
		if (dwKeyLength == 512) {
			pubKeyData[14] = 0x02;		   
		}
		else if (dwKeyLength == 1024) {
			pubKeyData[14] = 0x04;			   
		}
		else if (dwKeyLength == 2048) {
			pubKeyData[14] = 0x08;			   
		}
		pubKeyData[15] = 0x00; // Key length
		pubKeyData[16] = 0x00;
		pubKeyData[17] = 0x00;
		pubKeyData[18] = 0x00;
		pubKeyData[19] = 0x02; // Number of primes
		pubKeyData[20] = 0x00;
		pubKeyData[21] = 0x00;
		pubKeyData[22] = 0x00;
		pubKeyData[23] = 0x00; // Exponent
		pubKeyData[24] = 0x00;
		pubKeyData[25] = 0x00;
		pubKeyData[26] = 0x00;
		if (dwKeyLength == 512) {
			pubKeyData[26] = 0x00;
			pubKeyData[27] = 0x40;
		}
		else if (dwKeyLength == 1024) {
			pubKeyData[26] = 0x00;
			pubKeyData[27] = 0x80;			   
		}
		else if (dwKeyLength == 2048) {
			pubKeyData[26] = 0x01;
			pubKeyData[27] = 0x00;		   
		}                                 // Modulus length
		memcpy(&pubKeyData[28], i_pbModulusData, i_cdwModulusLength); // Modulus data

		tssResult = Tspi_SetAttribData(m_hKey,
			                           TSS_TSPATTRIB_KEY_BLOB,
			                           TSS_TSPATTRIB_KEYBLOB_PUBLIC_KEY,
			                           pubKeyLen,
			                           pubKeyData);
        VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_GetAttribData(m_hKey,
		                               TSS_TSPATTRIB_RSAKEY_INFO,
			    					   TSS_TSPATTRIB_KEYINFO_RSA_MODULUS,
									   (unsigned int*)&m_dwModulusLength,
								       &m_pbModulusData);
		VS_TSS_CHECK_RESULT(tssResult);
		
		assert(m_dwModulusLength == i_cdwModulusLength);

		free(pubKeyData);

	} while (0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		*o_pdwError = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
	}
}

// Destroy the TSS key object
VS_TSS_Key::~VS_TSS_Key()
{
	Tspi_Context_FreeMemory(m_hContext, m_pbModulusData);
	Tspi_Context_CloseObject(m_hContext, m_hKey);
}

// Get the key usage	   
HRESULT VS_TSS_Key::GetKeyUsage(DWORD* o_pdwKeyUsage)
{
	*o_pdwKeyUsage = m_dwKeyUsage;

	return(0);
}
       
// Get the key length
HRESULT VS_TSS_Key::GetKeyLength(DWORD* o_pdwKeyLength)
{
	*o_pdwKeyLength = m_dwModulusLength * 8;

	return(0);
}

HRESULT VS_TSS_Key::GetModulusLength(DWORD* o_pdwModulusLength)
{
	*o_pdwModulusLength = m_dwModulusLength;

	return(0);
}

	   
HRESULT VS_TSS_Key::GetModulus(DWORD* o_pdwModulusLength, 
		                       BYTE** o_pbModulusData)
{
	*o_pdwModulusLength = m_dwModulusLength;
	*o_pbModulusData = m_pbModulusData;

	return(0);
}

// Get the TSS key handle
HRESULT VS_TSS_Key::GetKey(TSS_HKEY* o_hKey)
{
	*o_hKey = m_hKey;

	return(0);
}




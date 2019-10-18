#include <stdio.h>
#include <assert.h>
#include <windows.h>

#include <tcpa_literals.h>
#include <tcpa_types.h>
#include <spi_literals.h>
#include <spi_exports.h>

#include <VS_TSS_Context.h>
#include <VS_TSS_Key.h>
#include <VS_TSS_Hash.h>

// XXX From cspglobals.h
#define		VS_SHA_1							32772

#define VS_TSS_CHECK_RESULT(result) { if (result != TSS_SUCCESS) break; }

// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Hash* CreateHashObject(const VS_TSS_Context* i_chContext, 
																const DWORD           i_cdwAlgorithmId, 
																DWORD*                o_dwError)
{
	return new VS_TSS_Hash(i_chContext, i_cdwAlgorithmId, o_dwError);
}


// Implementation of VS_TSS_Hash

VS_TSS_Hash::VS_TSS_Hash(const VS_TSS_Context* i_chContext, 
		                 const DWORD           i_cdwAlgorithmId, 
				         DWORD*                o_dwError)
{
	TSS_RESULT tssResult = TSS_SUCCESS;

	*o_dwError = 0;

	do {
		if (i_cdwAlgorithmId != VS_SHA_1) {
			*o_dwError = NTE_BAD_ALGID;
			break;
		}

		((VS_TSS_Context*)i_chContext)->GetHContext(&m_hContext);
		// XXX TSS_HASH_SHA1 not defined in IBM TSS
		tssResult = Tspi_Context_CreateObject(m_hContext,
										      TSS_OBJECT_TYPE_HASH, 
										      HASH_ALG_SHA1, 
											  //HASH_ALG_OTHER,
										      &m_hHash);
		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		*o_dwError = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		
	}
}

VS_TSS_Hash::~VS_TSS_Hash()
{
	Tspi_Context_CloseObject(m_hContext, m_hHash);
}
    
HRESULT VS_TSS_Hash::UpdateHashValue(const DWORD i_cdwDataLength, 
		                             const BYTE* i_cpbData)
{
	TSS_RESULT tssResult;
	HRESULT    hResult;

	do {
		tssResult = Tspi_Hash_UpdateHashValue(m_hHash, 
			                                  i_cdwDataLength, 
											  (unsigned char*)i_cpbData);

		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		hResult = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		hResult = 0;
	}

	return(hResult);
}

HRESULT VS_TSS_Hash::SetHashValue(const DWORD i_cdwHashLength, 
		                          const BYTE* i_cpbHashData)
{
	TSS_RESULT tssResult;
    HRESULT    hResult;

	do {

		tssResult = Tspi_Hash_SetHashValue(m_hHash,
										   i_cdwHashLength,
										   (unsigned char*)i_cpbHashData);
		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		hResult = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		hResult = 0;
	}

	return(hResult);
}

       
HRESULT VS_TSS_Hash::GetHashValue(DWORD* o_pdwHashLength, 
		                          BYTE** o_ppbHashData)
{
	TSS_RESULT tssResult;
	HRESULT    hResult;

	do {
		tssResult = Tspi_Hash_GetHashValue(m_hHash,
										   (unsigned int*)o_pdwHashLength,
										   o_ppbHashData);
		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		hResult = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		hResult = 0;
	}

	return(hResult);
}


HRESULT VS_TSS_Hash::Sign(const VS_TSS_Key* i_cTSSKey, 
		                  DWORD*            o_pdwSignatureLength, 
					      BYTE**            o_ppbSignatureData)
{
	TSS_HKEY   hKey;
	TSS_RESULT tssResult;
	HRESULT    hResult;

	do {
		((VS_TSS_Key*)i_cTSSKey)->GetKey(&hKey);
		tssResult = Tspi_Hash_Sign(m_hHash, 
			                       hKey, 
			   					   (unsigned int*)o_pdwSignatureLength, 
								   o_ppbSignatureData);
		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		hResult = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		hResult = 0;
	}

	return(hResult);
}
       
HRESULT VS_TSS_Hash::VerifySignature(const VS_TSS_Key* i_cTSSKey, 
		                             const DWORD       i_cdwSignatureLength, 
							         const BYTE*       i_cpbSignatureData)
{
	TSS_HKEY   hKey;
	TSS_RESULT tssResult;
	HRESULT    hResult = 0;

	do {
		((VS_TSS_Key*)i_cTSSKey)->GetKey(&hKey);
		tssResult = Tspi_Hash_VerifySignature(m_hHash, 
			                               hKey, 
										   i_cdwSignatureLength, 
										   (unsigned char*)i_cpbSignatureData);
		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		hResult = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		hResult = 0;
	}

	return(hResult);
}
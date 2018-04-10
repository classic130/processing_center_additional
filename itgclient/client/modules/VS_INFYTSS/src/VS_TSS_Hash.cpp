#include <stdio.h>
#include <assert.h>
#include <windows.h>

// TSS specific includes 
#include "tcpa_defines.h"
#include "tcpa_struct.h"
#include "tssapi_error.h"
#include "tss_values.h"
#include "tss_helpers.h"

#include <VS_TSS_Context.h>
#include <VS_TSS_Key.h>
#include <VS_TSS_Hash.h>

// XXX From cspglobals.h
#define		VS_SHA_1							32772


// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Hash* CreateHashObject(const VS_TSS_Context* i_chContext, 
																const DWORD           i_cdwAlgorithmId, 
																DWORD*                o_dwError)
{
	return new VS_TSS_Hash(i_chContext, i_cdwAlgorithmId, o_dwError);
}


// Implementation of VS_TSS_Hash

VS_TSS_Hash::VS_TSS_Hash(const VS_TSS_Context* i_cpContext, 
		                 const DWORD           i_cdwAlgorithmId, 
				         DWORD*                o_dwError)
{

	*o_dwError = S_OK;

	do {
		try 
		{
			if (i_cdwAlgorithmId != VS_SHA_1) {
				*o_dwError = NTE_BAD_ALGID;
				break;
			}

			// Always create a hash object of HASH_ALG_OTHER type. This way you can sign data of any length.
			((VS_TSS_Context*)i_cpContext)->GetContext( (ITCPAContextPtr *) &m_pContextObject);
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_HASH, HASH_ALG_OTHER, (IUnknown **)&m_pHashObject);

			// set SHA1 hash algorithm identifier
			ITCPAAttribPtr pHashAttrib(m_pHashObject);
			BYTE pbHashOID[DER_PREFIX_SHA1_LEN] = DER_PREFIX_SHA1;
			pHashAttrib->SetAttribData (
								TSS_TSPATTRIB_HASH_IDENTIFIER,
								0,
								DER_PREFIX_SHA1_LEN,
								pbHashOID
						  );

		}
		catch(_com_error e) 
		{
    		*o_dwError = e.Error();
		}
		catch(...) 
		{
			*o_dwError = E_FAIL;
		}

	} while(0);

}

VS_TSS_Hash::~VS_TSS_Hash()
{
}

/*
This method will create SHA1 hash. 
It will not work as we are using a hash object of HASH_ALG_OTHER type.
*/
HRESULT VS_TSS_Hash::UpdateHashValue(const DWORD i_cdwDataLength, 
		                             const BYTE* i_cpbData)
{
	HRESULT    hResult = S_OK;

	do {
		try 
		{
	        m_pHashObject->UpdateHashValue(i_cdwDataLength, (unsigned char*)i_cpbData);
		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
			hResult = E_FAIL;
		}

	} while(0);

	return hResult;
}

/* 
This method will set hash value, which can be signed later
*/
HRESULT VS_TSS_Hash::SetHashValue(const DWORD i_cdwHashLength, 
		                          const BYTE* i_cpbHashData)
{
	HRESULT    hResult = S_OK;

	do {
		try 
		{
	        m_pHashObject->SetHashValue(i_cdwHashLength, (unsigned char*)i_cpbHashData);

		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
			hResult = E_FAIL;
		}

	} while(0);

	return hResult;
}

/*
This method returns hash value stored in the hash object
*/       
HRESULT VS_TSS_Hash::GetHashValue(DWORD* o_pdwHashLength, 
		                          BYTE** o_ppbHashData)
{
	HRESULT    hResult = S_OK;

	do {
		try 
		{
	        m_pHashObject->GetHashValue((unsigned int*) o_pdwHashLength, o_ppbHashData);
		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
			hResult = E_FAIL;
		}

	} while(0);

	return hResult;
}


HRESULT VS_TSS_Hash::Sign(const VS_TSS_Key* i_cpTSSKey, 
		                  DWORD*            o_pdwSignatureLength, 
					      BYTE**            o_ppbSignatureData)
{
	HRESULT    hResult = S_OK;
    ITCPAKeyPtr	pKeyObject;

	do {
		try 
		{
			((VS_TSS_Key*)i_cpTSSKey)->GetKey( (ITCPAKeyPtr *) &pKeyObject); 

			m_pHashObject->Sign(pKeyObject, (unsigned int*) o_pdwSignatureLength, o_ppbSignatureData);

		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
			hResult = E_FAIL;
		}
	} while(0);

	return hResult;
}

/*
This method verifies the signature. It will not work as we are using a hash object of HASH_ALG_OTHER type.
*/
HRESULT VS_TSS_Hash::VerifySignature(const VS_TSS_Key* i_cpTSSKey, 
		                             const DWORD       i_cdwSignatureLength, 
							         const BYTE*       i_cpbSignatureData)
{
	HRESULT    hResult = S_OK;
    ITCPAKeyPtr	pKeyObject;

	do {

		try 
		{
			((VS_TSS_Key*)i_cpTSSKey)->GetKey( (ITCPAKeyPtr *) &pKeyObject); 

			m_pHashObject->VerifySignature(pKeyObject, i_cdwSignatureLength, (unsigned char*)i_cpbSignatureData);
		}
		catch(_com_error e) 
		{
    		hResult = e.Error();
		}
		catch(...) 
		{
			hResult = E_FAIL;
		}

	} while(0);

	return hResult;
}
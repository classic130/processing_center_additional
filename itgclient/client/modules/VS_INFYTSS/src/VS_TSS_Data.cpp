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
#include <VS_TSS_Data.h>

// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Data* CreateDataObject(const VS_TSS_Context* i_chContext,
																	const VS_TSS_Key*     i_cTSSKey,
																	DWORD*	o_dwError)
{
	return new VS_TSS_Data(i_chContext,
							i_cTSSKey,
							o_dwError);
}

// Implementation of VS_TSS_Data

VS_TSS_Data::VS_TSS_Data(const VS_TSS_Context* i_cpContext,
						 const VS_TSS_Key*     i_cpTSSKey,
		                 DWORD*                o_dwError)
{
	*o_dwError = S_OK;

	do {
		try 
		{
			// get pointers to context and key objects
			((VS_TSS_Context*)i_cpContext)->GetContext( (ITCPAContextPtr *) &m_pContextObject);
			((VS_TSS_Key*)i_cpTSSKey)->GetKey( (ITCPAKeyPtr *) &m_pKeyObject); 


			// create a legacy encryption data object, used for encrypting and decrypting data
			m_pEncDataObject = NULL;
			m_pContextObject->CreateObject(TSS_OBJECT_TYPE_ENCDATA, TSS_ENCDATA_LEGACY, 
										(IUnknown **)&m_pEncDataObject);
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

VS_TSS_Data::~VS_TSS_Data()
{
}

HRESULT VS_TSS_Data::Encrypt(const DWORD       i_cdwDataLength, 
					         const BYTE*       i_cpbData,
                             DWORD*            o_pdwEncryptedLength, 
					         BYTE**            o_ppbEncryptedData)
{
	HRESULT    hResult = S_OK;

	do {
		try
		{

			// bind data
			m_pEncDataObject->Bind(m_pKeyObject, i_cdwDataLength, (unsigned char*)i_cpbData);

			// retrieve encrypted data
			ITCPAAttribPtr pEncDataAttrib(m_pEncDataObject);
			pEncDataAttrib->GetAttribData(TSS_TSPATTRIB_ENCDATA_BLOB, TSS_TSPATTRIB_ENCDATABLOB_BLOB, 
										  (unsigned int*) o_pdwEncryptedLength, o_ppbEncryptedData);

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

HRESULT VS_TSS_Data::Decrypt(const DWORD       i_cdwEncryptedLength, 
					         const BYTE*       i_cpbEncryptedData,
                             DWORD*            o_pdwDecryptedLength, 
					         BYTE**            o_ppbDecryptedData)
{
	HRESULT    hResult = S_OK;

	do {

		try
		{
			// set data to be decrypted
			ITCPAAttribPtr pEncDataAttrib(m_pEncDataObject);
			pEncDataAttrib->SetAttribData(TSS_TSPATTRIB_ENCDATA_BLOB, TSS_TSPATTRIB_ENCDATABLOB_BLOB, 
										  i_cdwEncryptedLength, (unsigned char*)i_cpbEncryptedData);

			// decrypt data
			m_pEncDataObject->Unbind(m_pKeyObject, (unsigned int*) o_pdwDecryptedLength, o_ppbDecryptedData);

		}
		catch(_com_error e) 
		{
    		HRESULT hrResult = e.Error();

		}
		catch(...) 
		{
			hResult = E_FAIL;
		}

	} while(0);


	return hResult;
}
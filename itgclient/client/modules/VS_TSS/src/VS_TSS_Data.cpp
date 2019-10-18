#include <stdio.h>
#include <assert.h>
#include <windows.h>

#include <tcpa_literals.h>
#include <tcpa_types.h>
#include <spi_literals.h>
#include <spi_exports.h>

#include <VS_TSS_Context.h>
#include <VS_TSS_Key.h>
#include <VS_TSS_Data.h>

#define VS_TSS_CHECK_RESULT(result) { if (result != TSS_SUCCESS) break; }

VS_TSS_Data::VS_TSS_Data(const VS_TSS_Context* i_chContext,
						 const VS_TSS_Key*     i_cTSSKey,
		                 DWORD*                o_dwError)
{
	TSS_RESULT tssResult;

	do {
		((VS_TSS_Context*)i_chContext)->GetHContext(&m_hContext);
		((VS_TSS_Key*)i_cTSSKey)->GetKey(&m_hKey); 
		
		tssResult = Tspi_Context_CreateObject(m_hContext,
			                                  TSS_OBJECT_TYPE_ENCDATA, 
									          TSS_ENCDATA_BIND, 
									          &m_hEncData);
		VS_TSS_CHECK_RESULT(tssResult);
	} while(0);

	// XXX Error codes aren't fully defined in IBM TSS
    if (tssResult != TSS_SUCCESS) {
		*o_dwError = ERROR_INTERNAL_ERROR;
	}
	else {
		assert(tssResult == TSS_SUCCESS);
		*o_dwError = 0;
	}
}

VS_TSS_Data::~VS_TSS_Data()
{
	Tspi_Context_CloseObject(m_hContext, m_hEncData);
}

HRESULT VS_TSS_Data::Encrypt(const DWORD       i_cdwDataLength, 
					         const BYTE*       i_cpbData,
                             DWORD*            o_pdwEncryptedLength, 
					         BYTE**            o_ppbEncryptedData)
{
	TSS_RESULT tssResult;
	HRESULT    hResult;
	
	do {
		tssResult = Tspi_Data_Bind(m_hEncData, 
			                       m_hKey, 
								   i_cdwDataLength, 
								   (unsigned char*)i_cpbData);
		VS_TSS_CHECK_RESULT(tssResult);
		
		tssResult = Tspi_GetAttribData(m_hEncData,
			                           TSS_TSPATTRIB_ENCDATA_BLOB,
			                           TSS_TSPATTRIB_ENCDATABLOB_BLOB,
			                           (unsigned int*)o_pdwEncryptedLength,
			                           o_ppbEncryptedData);  
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

HRESULT VS_TSS_Data::Decrypt(const DWORD       i_cdwEncryptedLength, 
					         const BYTE*       i_cpbEncryptedData,
                             DWORD*            o_pdwDecryptedLength, 
					         BYTE**            o_ppbDecryptedData)
{
	TSS_RESULT tssResult;
	HRESULT    hResult;

	do {
		tssResult = Tspi_SetAttribData(m_hEncData,
			                           TSS_TSPATTRIB_ENCDATA_BLOB,
			                           TSS_TSPATTRIB_ENCDATABLOB_BLOB,
			                           i_cdwEncryptedLength,
									   (unsigned char*)i_cpbEncryptedData);
		VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_Data_Unbind(m_hEncData, 
			                         m_hKey, 
								     (unsigned int*)o_pdwDecryptedLength, 
								     o_ppbDecryptedData);
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
#include <stdio.h>
#include <windows.h>

#include <tcpa_literals.h>
#include <tcpa_types.h>
#include <spi_literals.h>
#include <spi_exports.h>

#include <VS_TSS_Context.h>

// XXX SRK UUID for IBM TSS only?
#define VS_SRK_UUID_STRING ("00000000-0000-0000-0000-000000000001")

#define VS_TSS_CHECK_RESULT(result) { if (result != TSS_SUCCESS) break; }

// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Context* CreateContextObject(DWORD* o_dwError)
{
	return new VS_TSS_Context(o_dwError);
}

// Implementation of VS_TSS_Context

VS_TSS_Context::VS_TSS_Context(DWORD* o_dwError)
{
	UUID       uuidSRK;
	TSS_RESULT tssResult;

	do {
		UuidFromString((unsigned char*)VS_SRK_UUID_STRING, &uuidSRK);
		memcpy ((void*) &m_tssuuidSRK, (const void*) &uuidSRK, sizeof(UUID));

		tssResult = Tspi_Context_Create(&m_hContext);
		VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_Context_Connect(m_hContext, NULL);
		VS_TSS_CHECK_RESULT(tssResult);

		tssResult = Tspi_Context_LoadKeyByUUID(m_hContext,
			  							       TSS_PS_TYPE_SYSTEM, 
											   m_tssuuidSRK, 
											   &m_hSRK);
		VS_TSS_CHECK_RESULT(tssResult);
	} while (0);

	if (tssResult == TSS_SUCCESS) {
		*o_dwError = 0;
	} else {
		*o_dwError = ERROR_INTERNAL_ERROR;
	}
}

VS_TSS_Context::~VS_TSS_Context()
{
	Tspi_Context_CloseObject(m_hContext, m_hSRK);
	Tspi_Context_Close(m_hContext);
}

HRESULT VS_TSS_Context::GetHContext(TSS_HCONTEXT* o_hContext)
{
	*o_hContext = m_hContext;

	return(0);
}

HRESULT VS_TSS_Context::GetSRK(TSS_HCONTEXT* o_hSRK)
{
	*o_hSRK = m_hSRK;

	return(0);
}

HRESULT VS_TSS_Context::GetSRKUUID(TSS_UUID* o_puuidSRK)
{
	*o_puuidSRK = m_tssuuidSRK;

	return(0);
}

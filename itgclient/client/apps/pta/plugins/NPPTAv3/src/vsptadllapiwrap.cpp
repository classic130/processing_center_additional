#include "ptadllapi.h"
#include "ptadllapi_i.c"
#include "ptav3.h"
#include "vsptadllapiwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

EXTERN_C IVSPTADllApi* PTADllApi_GetInstance(IVSPTA* pPTA)
{
	IVSPTADllApi* pPTADllApi;
	HRESULT hr;

	assert (pPTA != NULL);

	hr = pPTA->QueryInterface (IID_IVSPTADllApi, (void**)&pPTADllApi);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pPTADllApi;
}


EXTERN_C unsigned int PTADllApi_SetHostName (IVSPTADllApi* pPTADllApi, LPSTR szHostName, LPSTR szProtocol)
{
   HRESULT hr;
   int nRetVal, nSize;
   wchar_t *wcHostName=NULL;
   wchar_t *wcProtocol=NULL;
   VARIANT vtHostName, vtProtocol;
   unsigned int nResult = VS_NO_ERROR;

   assert (pPTADllApi != NULL);

   do
   {
		VariantInit(&vtHostName);
		nSize = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szHostName, lstrlen(szHostName), wcHostName, 0); 
		wcHostName = (wchar_t*)malloc(nSize*sizeof(wchar_t));
		nRetVal = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szHostName, lstrlen(szHostName), wcHostName, nSize); 
		if (nRetVal == 0) {
			nResult = VS_GENERIC_ERROR;
			break;
		}
		vtHostName.vt = VT_BSTR;
		vtHostName.bstrVal = SysAllocStringLen(wcHostName,nSize);

		VariantInit(&vtProtocol);
		nSize = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szProtocol, lstrlen(szProtocol), wcProtocol, 0); 
		wcProtocol = (wchar_t*)malloc(nSize*sizeof(wchar_t));
		nRetVal = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szProtocol, lstrlen(szProtocol), wcProtocol, nSize); 
		if (nRetVal == 0) {
			nResult = VS_GENERIC_ERROR;
			break;
		}
		vtProtocol.vt = VT_BSTR;
		vtProtocol.bstrVal = SysAllocStringLen(wcProtocol,nSize);

		hr = pPTADllApi->put_HostFQDN(vtHostName);
		_lastErrCode = hr;
		if (hr != S_OK) {
			nResult = VS_GENERIC_ERROR;
			break;
		}

		hr = pPTADllApi->put_Protocol(vtProtocol);
		_lastErrCode = hr;
		if (hr != S_OK) {
			nResult = VS_GENERIC_ERROR;
			break;
		}
   } while (0);

   if (wcHostName != NULL)
	   free (wcHostName);
   if (wcProtocol != NULL)
	   free (wcProtocol);
	VariantClear(&vtHostName);
	VariantClear(&vtProtocol);

 
   return nResult;
}
#include "vssc.h"
#include "vsscdllapiwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

EXTERN_C HRESULT _lastErrCode;


EXTERN_C IVSSCDllApi* VSSCDllApi_GetInstance(IVSSC* pVSSC)
{
	IVSSCDllApi* pVSSCDllApi;
	HRESULT hr;

	assert (pVSSC != NULL);

	hr = pVSSC->QueryInterface (IID_IVSSCDllApi, (void**)&pVSSCDllApi);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pVSSCDllApi;
}


EXTERN_C unsigned int VSSCDllApi_SetHostName (IVSSCDllApi* pVSSCDllApi, LPSTR szHostName, LPSTR szProtocol)
{
	HRESULT hr;
   int nRetVal, nSize;
   wchar_t *wcHostName=NULL;
   wchar_t *wcProtocol=NULL;
   VARIANT vtHostName, vtProtocol;
   unsigned int nResult = VS_NO_ERROR;

   assert (pVSSCDllApi != NULL);

   do
   {
		if(szHostName == NULL || szProtocol == NULL)
		{
			nResult = E_NO_HOSTNAME;
			_lastErrCode = nResult;
			break;
		}

		VariantInit(&vtHostName);
		nSize = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szHostName, lstrlen(szHostName), wcHostName, 0); 
		wcHostName = (wchar_t*)malloc(nSize*sizeof(wchar_t));
		nRetVal = MultiByteToWideChar (CP_ACP, MB_PRECOMPOSED, szHostName, lstrlen(szHostName), wcHostName, nSize); 
		if (nRetVal == 0) {
			nResult = VS_GENERIC_ERROR;
			_lastErrCode = nResult;
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
			_lastErrCode = nResult;
			break;
		}
		vtProtocol.vt = VT_BSTR;
		vtProtocol.bstrVal = SysAllocStringLen(wcProtocol,nSize);

		hr = pVSSCDllApi->put_HostFQDN(vtHostName);
		_lastErrCode = hr;
		if (hr != S_OK) {
			nResult = VS_GENERIC_ERROR;
			_lastErrCode = nResult;
			break;
		}

		hr = pVSSCDllApi->put_HostProtocol(vtProtocol);
		_lastErrCode = hr;
		if (hr != S_OK) {
			nResult = VS_GENERIC_ERROR;
			_lastErrCode = nResult;
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
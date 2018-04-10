#include "addrootswrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSRootsUpdate* AddRoots_CreateInstance()
{
	IVSRootsUpdate* pAddRoots;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_VSROOTS, NULL, CLSCTX_INPROC_SERVER, IID_IVSRootsUpdate,(void**)&pAddRoots);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pAddRoots;
}


EXTERN_C unsigned int AddRoots_Initialize(IVSRootsUpdate* pAddRoots)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	int err = 0;

	assert(pAddRoots != NULL);

	hr = pAddRoots->Initialize();
	_lastErrCode = hr;
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}

EXTERN_C unsigned int AddRoots_CreateStandardTrustProfile(IVSRootsUpdate* pAddRoots)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	int err = 0;

	assert(pAddRoots != NULL);
	hr = pAddRoots->CreateStandardTrustProfile();
	_lastErrCode = hr;
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}

EXTERN_C unsigned int AddRoots_CreateVerisignTrustProfile(IVSRootsUpdate* pAddRoots)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	int err = 0;

	assert(pAddRoots != NULL);

	hr = pAddRoots->CreateVerisignTrustProfile();
	_lastErrCode = hr;
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}

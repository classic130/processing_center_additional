#include <stdio.h>
#include <windows.h>

// TSS specific includes 
#include "tcpa_defines.h"
#include "tcpa_struct.h"
#include "tssapi_error.h"
#include "tss_values.h"

#include <VS_TSS_Context.h>


#define VS_TSS_CHECK_RESULT(result) { if (result != TSS_SUCCESS) break; }

// DLL export functions.

extern "C" __declspec(dllexport) VS_TSS_Context* CreateContextObject(DWORD* o_dwError)
{
	return new VS_TSS_Context(o_dwError);
}

// Implementation of VS_TSS_Context

VS_TSS_Context::VS_TSS_Context(DWORD* o_dwError)
{
	*o_dwError = S_OK;

	do {

		try 
		{
			ITCPAContextPtr pContextObject(__uuidof(TCPAContext));
			pContextObject->Connect(NULL);

			ITCPAKeyPtr pSRKKeyObject = NULL;
			pContextObject->CreateObject(TSS_OBJECT_TYPE_RSAKEY, TSS_KEY_TSP_SRK, (IUnknown **)&pSRKKeyObject);

			//Use the default policy object for the SRK secret  
			//get the default policy object for the SRK thru the ITCPAAuth interface of the SRK key object
			//and set the secret to the well known secret;
			//the key creation below requires that secret for the wrapping storage root key 
			ITCPAAuthPtr pSRKKeyAuth(pSRKKeyObject);
			ITCPAPolicyPtr pDefaultPolicyObject;
			pSRKKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pDefaultPolicyObject);
			BYTE rgbSRKSecret[] = TSS_WELL_KNOWN_SECRET;
			pDefaultPolicyObject->SetSecret(TSS_SECRET_MODE_SHA1, sizeof(rgbSRKSecret), rgbSRKSecret);

			m_pContextObject = pContextObject;
			m_pSRKKeyObject = pSRKKeyObject;
		}
		catch(_com_error e) 
		{
    		*o_dwError = e.Error();
		}
		catch(...) 
		{
			*o_dwError = E_FAIL;
		}

	} while (0);

}

VS_TSS_Context::~VS_TSS_Context()
{
	HRESULT hr = S_OK;

	try 
	{
		//for the key objects used and created respectively (SRK)
		ITCPAAuthPtr pSRKKeyAuth(m_pSRKKeyObject);

		ITCPAPolicyPtr pDefaultPolicyObject;
		pSRKKeyAuth->GetPolicyObject(TSS_POLICY_USAGE, &pDefaultPolicyObject);

		//FlushSecret for the SRK well known secret
		pDefaultPolicyObject->FlushSecret();

	}
	catch(_com_error e) 
	{
    	hr = e.Error();
	}
	catch(...) 
	{
		hr = E_FAIL;
	}

}

HRESULT VS_TSS_Context::GetContext(ITCPAContextPtr* o_pContext)
{
	*o_pContext = m_pContextObject;

	return(0);
}

HRESULT VS_TSS_Context::GetSRK(ITCPAKeyPtr* o_pSRK)
{
	*o_pSRK = m_pSRKKeyObject;

	return(0);
}

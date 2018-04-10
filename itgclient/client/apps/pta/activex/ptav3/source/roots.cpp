#include "stdafx.h"
#include <comdef.h>
#include <winreg.h>

#include "..\Include\Ptav3.h"
#include "..\Include\VSPTA.h"
#include "..\include\certblobs.h"
#include "..\include\Roots.h"


//
//	The initialize function will check the sanity of the system. It will check if IE4.0
//	or later is installed. 
//	It will also determine if the Verisign Root Certificates (roots)
//	are to be added to the HKLM or the HKCU section of the registry. It will also
//	determine if the certs are to be added as registry keys or values and whether
//	the header is to be attached or not to the certificate blobs.
//
STDMETHODIMP CVSROOTS::Initialize()
{
	return	S_OK;
}	//	end		STDMETHODIMP CVSROOTS::Initialize()


/////////////////////////////////////////////////////////////////////////////
// CVSROOTS::CreateStandardTrustProfile()
//
//	This function will add some Verisign Root Certificates (roots) to the 
//	'Root' store in the registry.
//
//	IE4.0+ needs to be installed on the client machine for this function
//	to succeed.
//
//	If a particular root is already present in the HKLM then it is not
//	added to the HKCU.
//
STDMETHODIMP CVSROOTS::CreateStandardTrustProfile()
{
	return	S_OK;
}	//	end		STDMETHODIMP CVSROOTS::CreateStandardTrustProfile()


/////////////////////////////////////////////////////////////////////////////
// STDMETHODIMP CVSROOTS::CreateVerisignTrustProfile()
//
//	This function will add some Verisign Root Certificates (roots) to the 
//	'Root' store in the registry ( by calling the CreateVerisignTrustProfile) 
//	and also delete some unwanted roots from the store.
//
STDMETHODIMP CVSROOTS::CreateVerisignTrustProfile()
{
	return	S_OK;
}	//	end		STDMETHODIMP CVSROOTS::CreateVerisignTrustProfile()



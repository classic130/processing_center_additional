#include "stdafx.h"

//#include
#include "..\include\vs_tpm_csp.h"
#include "vs_csp.h"
#include "comdef.h"

#include "..\include\cspincludes.h"
#include "..\include\cspstructures.h"
#include "..\include\VSCSP_Macros.h"
#include "..\include\cspglobals.h"
#include "..\include\HelperFunctions.h"
//#include "..\..\ProtectedStorage\VSPS_Defines.h"
//#include "..\..\ProtectedStorage\ProtectedStorage.h"
//#include "..\..\BSafeLite\main.h"
#include "..\include\virtualsmartcard.h"
#include "..\include\keycontainer.h"


#include "mangledprofmgmt.h"
#include "mangleduiprefs.h"
#include "mangledcertprefs.h"
#include "mangledsrchcrit.h"
#include "mangledseldigid.h"
#include "mangledroamprefs.h"

#include "ptadefines.h"

#include "Ptav3.h"

#include "VSPTA.h"

/*
CSP_State*		g_phProv				=	NULL;
DWORD			g_dwNumberOfCSPHandles	=	0;

CSP_AlgoInfo	g_AlgoInfo;
CSP_ExAlgoInfo	g_ExAlgoInfo;
*/

extern CVirtualSmartCard* _gpVirtualSmartCard;


BOOL WINAPI VSTPM_CPAcquireContext
(
	OUT HCRYPTPROV *phProv,
	OUT CHAR *pszIdentity,
	IN DWORD dwFlags,
	IN PVTableProvStruc pVTable
)
{
#ifdef	_VS_MSG_BOX_
		::MessageBox ( NULL, (LPCTSTR) "CPAcquireContext", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult					=	CRYPT_FAILED;
	HRESULT						hResult					=	E_FAIL;
	DWORD						dwResult				=	999;

	CSP_State*					pCSP					=	NULL;

	_variant_t					tvarName;
	_variant_t					tvarRoamFlag;
	_variant_t					tvarSaveLocalFlag;
	VARIANT						vtHostName;

	IVSPTADllApi				*pPTADllApi				=	NULL;

	bool						boolCreate				=	FALSE;
	BOOL						boolSuccessFlag			=	FALSE;

//	CComObject<CVSPTA>*			pCVSPTA					=	NULL;
//	CVirtualSmartCard*			pVSmartCard				=	NULL;

	CSP_Key_Container			structContainer;

	DWORD						dwLastError				=	0;

	int							nIdentityLength;


	while (1)
	{
		_bstr_t					tbstrName = "";
		_bstr_t					tbstrContainerName = "";
		_bstr_t					tbstrProfilePathName = "";
		_bstr_t					tbstrProfileName = "";
		_bstr_t					tbstrVeriSignCryptoKey(VS_CRYPTO_REG_KEY);
		_bstr_t					tbstrSmartCardName =	"";

				//	check input parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL	(phProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL	(pVTable)

		pCSP =	new (CSP_State);
		VSCSP_CHECK_ALLOCATED_MEMORY (pCSP)

		InitCSPGlobalVars ();

		if ( NULL != pszIdentity )
		{
			nIdentityLength =	::lstrlen ( pszIdentity );
			
			pCSP -> pszNameOfContainer =	new CHAR [ nIdentityLength + 1 ];
			::lstrcpy ( pCSP -> pszNameOfContainer, pszIdentity );
			tbstrContainerName =	pszIdentity;
		}
		else
		{
			pCSP -> pszNameOfContainer = NULL;
		}

				//	init the members of the structures
		pCSP -> dwCSPName		=	VS_TPM_CSP;
		pCSP -> dwSizeofStruct	=	sizeof (CSP_State);
		pCSP -> pHashParam		=	NULL;
		pCSP -> pKeyParam		=	NULL;
		pCSP -> pIProfMgmt		=	NULL;
		pCSP -> pIPTA			=	NULL;
		pCSP -> bPvtKeyAccess	=	TRUE;


			// need to initialize like this for Infineon
		CoInitializeEx(NULL,COINIT_MULTITHREADED);

		hResult =	CoCreateInstance
					(
						CLSID_VSPTA,
						NULL,
						CLSCTX_INPROC_SERVER,
						IID_IVSPTA,
						(void**) &(pCSP -> pIPTA)
					);
		VSCSP_CHECK_HRESULT

		hResult =	(pCSP -> pIPTA) -> get_IVSProfMgmt
					(
						(IDispatch **) &(pCSP -> pIProfMgmt)
					);
		VSCSP_CHECK_HRESULT

		// CAPI is not to be used
		_variant_t					tvarCAPIFlag;
		tvarCAPIFlag =	(short) DONT_USE_CAPI;

		pCSP -> pbyteCorrSignPublicKey	=	NULL;
		pCSP -> dwCorrSignPublicKeyLen	=	0;
		pCSP -> pbyteCorrXchgPublicKey	=	NULL;
		pCSP -> dwCorrXchgPublicKeyLen	=	0;

		if ( NULL == _gpVirtualSmartCard )
		{
			_gpVirtualSmartCard = new CVirtualSmartCard;
		}

		switch ( dwFlags )
		{
			case	CRYPT_VERIFYCONTEXT:

				// For a verify context the identity should be NULL
				if ( NULL != pszIdentity && '\0' != pszIdentity[0] )
				{
					hResult =	ERROR_INVALID_PARAMETER;
					VSCSP_CHECK_HRESULT
				}

//				tvarOpenCreateFlag =	(short) OPENPROF_CREATE_ONLY/*OPENPROF_OPEN_ONLY*/;
//				pCSP -> bPvtKeyAccess =	FALSE;

				boolSuccessFlag =	TRUE;
				break;

			case	CRYPT_NEWKEYSET:

				// If no identity exists then return error as we are not supporting the 
				// creating of a NULL/DEFAULT container
				if ( NULL == pszIdentity || ( NULL != pszIdentity && '\0' == pszIdentity[0] ) )
				{
					hResult =	E_NOTIMPL;
					VSCSP_CHECK_HRESULT
				}

//				tvarOpenCreateFlag =	(short) OPENPROF_CREATE_OR_OPEN;
				boolCreate =	TRUE;

				hResult =	_gpVirtualSmartCard -> VSM_TPMInitialize
							(
								tbstrContainerName,
								VS_TPM_CONTAINER_CREATE,
								pCSP -> pIPTA
							);
				VSCSP_CHECK_HRESULT

				boolSuccessFlag =	TRUE;
				break;

			case	CRYPT_MACHINE_KEYSET:
				hResult =	E_NOTIMPL;
				VSCSP_CHECK_HRESULT

				break;

			case	CRYPT_DELETEKEYSET:
//				tvarOpenCreateFlag =	(short) OPENPROF_OPEN_ONLY;
				boolSuccessFlag =	TRUE;
				break;

//			case	CRYPT_SILENT:
//				dwSuccessFlage =	TRUE;
//				break;

			case	0:
			case	1:
				//TBD

				// If no identity exists then return error as we are not supporting the 
				// concept of a NULL/DEFAULT container
				if ( NULL == pszIdentity || ( NULL != pszIdentity && '\0' == pszIdentity[0] ) )
				{
					hResult = NTE_BAD_KEYSET;
					VSCSP_CHECK_HRESULT
				}

//				tvarOpenCreateFlag =	(short) OPENPROF_CREATE_OR_OPEN;	//**** IS THERE A FLAG EQUIVALENT TO OPEN_IF_EXISTS

				hResult =	_gpVirtualSmartCard -> VSM_TPMInitialize
							(
								tbstrContainerName,
								VS_TPM_CONTAINER_OPEN,
								pCSP -> pIPTA
							);
				VSCSP_CHECK_HRESULT

				boolSuccessFlag =	TRUE;
				break;
		}	//	end		switch ( dwFlags )


		if ( TRUE == boolCreate )
		{
			// Fill the app context name
			tbstrName =	CSP_AP_CTXT_NAME;

			// Enrolling through the CSP always ends up creating a local
			// profile, don't support enrolling for a roaming profile
			// from the CSP
			tvarRoamFlag =	(bool) DONT_ROAM;
			tvarSaveLocalFlag =	(bool) SAVE_LOCAL;
		}


		tvarName =	tbstrName;

		// Init the object
		hResult =	(pCSP -> pIPTA) -> Initialize
					(
						&tvarName,
						&tvarCAPIFlag
					);
		VSCSP_CHECK_HRESULT

		hResult =	pCSP -> pIPTA -> QueryInterface
					(
						IID_IVSPTADllApi,
						(void **) &(pPTADllApi)
					);
		VSCSP_CHECK_HRESULT

		VariantInit ( &vtHostName );
		vtHostName.vt = VT_BSTR;
		vtHostName.bstrVal = L"localhost";
		
		// XXX hResult =	pPTADllApi -> put_HostFQDN ( vtHostName );

		pPTADllApi -> Release ();

		VSCSP_CHECK_HRESULT

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		*phProv =	(HCRYPTPROV) pCSP;

		bResult	=	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	
	::SetLastError ( dwLastError );
	return	bResult;
}
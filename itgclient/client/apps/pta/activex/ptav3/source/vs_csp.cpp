#include "stdafx.h"

//#include

#include "..\include\vs_csp.h"
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

#include "..\include\Ptav3.h"

#include "..\include\VSPTA.h"
#include "..\include\vs_tpm_csp.h"


CSP_State*		g_phProv				=	NULL;
DWORD			g_dwNumberOfCSPHandles	=	0;

CSP_AlgoInfo	g_AlgoInfo;
CSP_ExAlgoInfo	g_ExAlgoInfo;

TPM_CSP_AlgoInfo	g_TPM_AlgoInfo;
TPM_CSP_ExAlgoInfo	g_TPM_ExAlgoInfo;


extern CVirtualSmartCard* _gpVirtualSmartCard;

#define		PASSWORD_TIMEOUT				15


/*
HRESULT	passwordfunction ( _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut )
{
	return	S_OK;
}
*/

BOOL
DllInitialize(
    IN PVOID hmod,
    IN ULONG Reason,
    IN PCONTEXT Context
    )
{

    if ( Reason == DLL_PROCESS_ATTACH ) {
//	due to compile error        DisableThreadLibraryCalls(hmod);
        }

	InitCSPGlobalVars ();

    return( TRUE );
}

/*
 -	CPAcquireContext
 -
 *	Purpose:
 *               The CPAcquireContext function is used to acquire a context
 *               handle to a cryptograghic service provider (CSP).
 *
 *
 *	Parameters:
 *               OUT phProv        -  Handle to a CSP
 *               OUT pszIdentity   -  Pointer to a string which is the
 *                                    identity of the logged on user
 *               IN  dwFlags       -  Flags values
 *               IN  pVTable       -  Pointer to table of function pointers
 *
 *	Returns:
 */


BOOL WINAPI CPAcquireContext
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

	CSP_State*					pCSP					=	NULL;

	BOOL						boolSuccessFlag			=	FALSE;

	CComObject<CVSPTA>*			pCVSPTA					=	NULL;
	CVirtualSmartCard*			pVSmartCard				=	NULL;

	CSP_Key_Container			structContainer;

	_variant_t					tvarName;
	_variant_t					tvarCAPIFlag;
	_variant_t					tvarResult;
	_variant_t					tvarOpenCreateFlag;
	_variant_t					tvarRoamFlag;
	_variant_t					tvarSaveLocalFlag;
	_variant_t					tvarProfileName;
	_variant_t					tvarClientInfo;
	_variant_t					tvarClientInfoSig;

	BSTR						bstrProfilePathName		=	0;
	BSTR						bstrClientInfo			=	0;
	BSTR						bstrClientInfoSig		=	0;
	BSTR						bstrProfilePath			=	0;
	BSTR						bstrProfileName			=	0;
	BSTR						bstrApContext			=	0;

	int							nIdentityLength;

	bool						boolCreate				=	FALSE;
	IVSPTADllApi				*pPTADllApi				=	NULL;
	IVSRoamPrefs				*pRoamPrefs				=	NULL;
	VARIANT						vtHostName;
	VARIANT						vtPasswdQuality;
	VARIANT						vtProfileName;
	SAFEARRAY					*psa					=	NULL;

	HKEY						hkVeriSignCryptoKey;
	DWORD						disp;
	VARIANT						varSmartCardName;

	DWORD						dwLastError				=	0;

	while (1)
	{
		
		_bstr_t					tbstrName = "";
		_bstr_t					tbstrContainerName = "";
		_bstr_t					tbstrProfilePathName = "";
		_bstr_t					tbstrProfileName = "";
		_bstr_t					tbstrVeriSignCryptoKey(VS_CRYPTO_REG_KEY);
		_bstr_t					tbstrSmartCardName =	"";

		//	launch update
		{
		

			CoInitialize (NULL);
			
			const CLSID CLSID_NaviClientUpdate = {0xD6C740D2,0x8983,0x4B6E,{0xA4,0x9D,0x85,0xA2,0x31,0x5F,0x92,0x9D}};
			const IID IID_INaviClientUpdate = {0x376B4C53,0x9E73,0x4B6E,{0xA4,0xD6,0x79,0x5A,0x78,0xFB,0x1A,0x11}};

			IDispatch * install = 0;
			if(SUCCEEDED(CoCreateInstance(CLSID_NaviClientUpdate, 0, CLSCTX_LOCAL_SERVER , IID_INaviClientUpdate, (LPVOID *)&install)))
			{

				HRESULT hr = 0;
				_variant_t avarParams[1];
				avarParams[0] = _variant_t("PTA");
				DISPPARAMS params = { avarParams, NULL, 1, 0 };

				hr = install->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, 0, 0, 0);
				install->Release();
			}

			CoUninitialize ();

		}
				//	check input parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL	(phProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL	(pVTable)

		pCSP =	new (CSP_State);
		VSCSP_CHECK_ALLOCATED_MEMORY (pCSP)

		InitCSPGlobalVars ();

		if ( 3 > pVTable -> Version )
		{
			//	This means that the OS is pre W2K
			//	The TPM CSP will not be available on this old platform
			//	Moreover the VTableProvStruc does NOT contain the pszProvName 
			//	and hence we cannot do the name comparision
			//	Therefor the name of the CSP is set to PTA CSP
			pCSP -> dwCSPName = VS_PTA_CSP;
		}
		else
		{
			//	this is W2K+ OS. so check the name of the CSP

				//	check if its PTA CSP

			if (!::strcmp ( (pVTable -> pszProvName), VS_PTA_CSP_NAME))
			{
				pCSP -> dwCSPName = VS_PTA_CSP;
			}
			else
			{

    				//	check if its TPM CSP
				if (!::stricmp ((pVTable -> pszProvName), VS_TPM_CSP_NAME))
				{
					pCSP -> dwCSPName = VS_TPM_CSP;
					//	TODOTPM:	check if TPM chip exists
					//	call the CpAcquireContext in vs_tpm_csp.cpp
					bResult =	VSTPM_CPAcquireContext
								(
									phProv,
									pszIdentity,
									dwFlags,
									pVTable
								);
					if ( TRUE == bResult )
					{
//						::MessageBox(NULL, "Success", "NewCSP", MB_OK);
						bResult =	CRYPT_SUCCEED;
						break;
					}
					else
					{
//						::MessageBox(NULL, "Failure", "NewCSP", MB_OK);
						break;
					}
				}
				else
				{
						//	if none then return error
					hResult =	ERROR_INVALID_PARAMETER;
					::SetLastError ( (DWORD)hResult );
					break;
				}
			}
		}

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
		pCSP -> dwSizeofStruct		=	sizeof (CSP_State);
		pCSP -> pHashParam		=	NULL;
		pCSP -> pKeyParam		=	NULL;
		pCSP -> pIProfMgmt		=	NULL;
		pCSP -> pIPTA			=	NULL;
		pCSP -> bPvtKeyAccess	=	TRUE;

		CoInitialize (NULL);

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

		pCSP -> pbyteCorrSignPublicKey	=	NULL;
		pCSP -> dwCorrSignPublicKeyLen	=	0;
		pCSP -> pbyteCorrXchgPublicKey	=	NULL;
		pCSP -> dwCorrXchgPublicKeyLen	=	0;

		// CAPI is not to be used
		tvarCAPIFlag =	(short) DONT_USE_CAPI;

#if 0
		if ( NULL != pCSP -> pszNameOfContainer )
		{
			tvarRoamFlag =	(bool) DONT_ROAM;
			tvarSaveLocalFlag =	(bool) SAVE_LOCAL;
		}
		else
		{
			// For NULL container treat as a temporary in memory roaming profile, 
			tvarRoamFlag =	(bool) ROAM;
			tvarSaveLocalFlag =	(bool) DONT_SAVE_LOCAL;
		}
#endif

		switch ( dwFlags )
		{
			case	CRYPT_VERIFYCONTEXT:

				// For a verify context the identity should be NULL
				if ( NULL != pszIdentity && '\0' != pszIdentity[0] )
				{
					hResult =	ERROR_INVALID_PARAMETER;
					VSCSP_CHECK_HRESULT
				}

				tvarOpenCreateFlag =	(short) OPENPROF_CREATE_ONLY/*OPENPROF_OPEN_ONLY*/;
				pCSP -> bPvtKeyAccess =	FALSE;

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

				tvarOpenCreateFlag =	(short) OPENPROF_CREATE_OR_OPEN;
				boolCreate =	TRUE;

				boolSuccessFlag =	TRUE;
				break;

			case	CRYPT_MACHINE_KEYSET:
				hResult =	E_NOTIMPL;
				VSCSP_CHECK_HRESULT

				break;

			case	CRYPT_DELETEKEYSET:
				tvarOpenCreateFlag =	(short) OPENPROF_OPEN_ONLY;
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

				tvarOpenCreateFlag =	(short) OPENPROF_CREATE_OR_OPEN;	//**** IS THERE A FLAG EQUIVALENT TO OPEN_IF_EXISTS

				boolSuccessFlag =	TRUE;
				break;
		}	//	end		switch ( dwFlags )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

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
		else
			if ( CRYPT_VERIFYCONTEXT == dwFlags )
			{
				// For NULL container treat as a temporary in memory roaming profile
				tvarRoamFlag =	(bool) ROAM;
				tvarSaveLocalFlag =	(bool) DONT_SAVE_LOCAL;

				if ( NULL == _gpVirtualSmartCard )
				{
					tbstrName = CSP_AP_CTXT_NAME;
					bstrProfileName = L"VS_MEM";
				}
				else
				{
					// If smartcard is already open and application tries
					// to acquire context with NULL container name then
					// use the current card's app name instead of giving
					// a default, if default is given then the PTA feels
					// that a new application is trying to open the card
					// and so it tries to change the smartcard pointer, this
					// results in the profile open dialog which is not desired

					hResult =	_gpVirtualSmartCard->get_VSM_ProfileName
													 (
														&vtProfileName
													 );
					VSCSP_CHECK_HRESULT

					tbstrProfilePathName =	vtProfileName.bstrVal;

					VariantClear ( &vtProfileName );

					hResult =	ParseProfile_Path_Name
								(
									tbstrProfilePathName,
									&bstrProfileName,
									&bstrProfilePath,
									&bstrApContext
								);
					VSCSP_CHECK_HRESULT
					
					tbstrName =	bstrApContext;
				}

			}
			else
			{
				BOOL	bIsRoam;
				hResult =	GetProfileInfoFromRegistry
							(
								tbstrContainerName,
								&bstrProfilePathName,
								&bstrClientInfo,
								&bstrClientInfoSig,
								&bIsRoam
							);
				VSCSP_CHECK_HRESULT

				if( bIsRoam )
				{
					tvarRoamFlag =	(bool) ROAM;
					tvarSaveLocalFlag =	(bool) DONT_SAVE_LOCAL;
					tvarOpenCreateFlag =	(short) OPENPROF_OPEN_ONLY;
				}
				else
				{
					tvarRoamFlag =	(bool) DONT_ROAM;
					tvarSaveLocalFlag =	(bool) SAVE_LOCAL;
				}

				tbstrProfilePathName = bstrProfilePathName;

				hResult =	ParseProfile_Path_Name
							(
								tbstrProfilePathName,
								&bstrProfileName,
								&bstrProfilePath,
								&bstrApContext
							);
				VSCSP_CHECK_HRESULT
				
				tbstrName =	bstrApContext;
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
		
		hResult =	pPTADllApi -> put_HostFQDN ( vtHostName );

		pPTADllApi -> Release ();

		VSCSP_CHECK_HRESULT

		tbstrProfileName =	bstrProfileName;
		tvarProfileName =	tbstrProfileName;

		hResult =	(pCSP -> pIProfMgmt) -> put_ProfMgmt_ProfileName
					(
						tvarProfileName
					);
		if ( VS_SUCCESS != hResult )
		{
			if ( E_CARDALREADYOPEN != hResult )
			{
				dwLastError =	hResult;
				break;
			}
		}

		hResult =	(pCSP -> pIProfMgmt) -> put_ProfMgmt_OpenProfFlags
					(
						tvarOpenCreateFlag
					);
		if ( VS_SUCCESS != hResult )
		{
			if ( E_CARDALREADYOPEN != hResult )
			{
				dwLastError =	hResult;
				break;
			}
		}

		hResult =	(pCSP -> pIProfMgmt) -> put_ProfMgmt_RoamProfile
					(
						tvarRoamFlag
					);
		if ( VS_SUCCESS != hResult )
		{
			if ( E_CARDALREADYOPEN != hResult )
			{
				dwLastError =	hResult;
				break;
			}
		}

		if ( TRUE == (bool)tvarRoamFlag && CRYPT_VERIFYCONTEXT != dwFlags )
		{
			hResult =	pCSP -> pIPTA -> QueryInterface
					(
						IID_IVSRoamPrefs,
						(void **) &(pRoamPrefs)
					);
			VSCSP_CHECK_HRESULT

			tvarClientInfo	=	bstrClientInfo;
			hResult =	pRoamPrefs -> put_RoamPrefs_ClientInfo
						(
							tvarClientInfo
						);
			if ( VS_SUCCESS != hResult )
			{
				if ( E_CARDALREADYOPEN != hResult )
				{
					dwLastError =	hResult;
					pRoamPrefs -> Release ();
					break;
				}
			}

			tvarClientInfoSig	=	bstrClientInfoSig;
			hResult =	pRoamPrefs -> put_RoamPrefs_ClientInfoSig
						(
							tvarClientInfoSig
						);
			if ( VS_SUCCESS != hResult )
			{
				if ( E_CARDALREADYOPEN != hResult )
				{
					dwLastError =	hResult;
					pRoamPrefs -> Release ();
					break;
				}
			}

			pRoamPrefs -> Release ();
		}

		hResult =	(pCSP -> pIProfMgmt) -> put_ProfMgmt_SaveLocal
					(
						tvarSaveLocalFlag
					);
		if ( VS_SUCCESS != hResult )
		{
			if ( E_CARDALREADYOPEN != hResult )
			{
				dwLastError =	hResult;
				break;
			}
		}

		// For verify context put password not required flag because we are opening
		// an in memory profile in this case. 
		// Also set the roaming preferences to NULL
		if ( NULL == pCSP -> pszNameOfContainer && CRYPT_VERIFYCONTEXT == dwFlags )
		{

			VariantInit ( &vtPasswdQuality );
			vtPasswdQuality.vt = VT_I2;
			vtPasswdQuality.iVal = PASSWDQUAL_REQUIRENOPASS;

			hResult =	(pCSP -> pIProfMgmt) -> put_ProfMgmt_PasswdQuality
						(
							vtPasswdQuality
						);
			if ( VS_SUCCESS != hResult )
			{
				if ( E_CARDALREADYOPEN != hResult )
				{
					dwLastError =	hResult;
					break;
				}
			}

			/*hResult =	pCSP -> pIPTA -> QueryInterface
					(
						IID_IVSRoamPrefs,
						(void **) &(pRoamPrefs)
					);
			VSCSP_CHECK_HRESULT

			VariantInit ( &vtNumRoamingSvrs );
			vtNumRoamingSvrs.vt = VT_I2;
			vtNumRoamingSvrs.iVal = 0;

			pRoamPrefs -> put_RoamPrefs_NumOfSrvrs ( vtNumRoamingSvrs );
			VSCSP_CHECK_HRESULT

			rgsabound[0].lLbound	=	0;
			rgsabound[0].cElements	=	1;

			vtRoamingSvrs.vt = VT_ARRAY|VT_VARIANT|VT_BYREF;
			psa	= SafeArrayCreate(VT_BSTR, 1, rgsabound);
			
			if( NULL == psa )
			{
				dwLastError =	E_OUTOFMEMORY;
				break;
			}

			vtRoamingSvrs.pparray =	&psa;
							
			pRoamPrefs -> put_RoamPrefs_RoamingSrvrs ( vtRoamingSvrs );
			VSCSP_CHECK_HRESULT

			SafeArrayDestroy ( vtRoamingSvrs.parray );
			pRoamPrefs -> Release ();*/
		}

		boolSuccessFlag =	FALSE;

		switch ( dwFlags )
		{
			case	CRYPT_VERIFYCONTEXT:
				
				boolSuccessFlag =	TRUE;
				break;

			case	CRYPT_DELETEKEYSET:
			case	0:
			case	1:

						//	check if the container exists
						//	if it exists then the function will return VS_SUCCESS
						//	else it will return NTE_BAD_KEYSET
//				hResult =	CheckIfContainerExists
//							(
//								pCSP,
//								pVSmartCard
//							);
//				if ( VS_SUCCESS != hResult )
//				{
//						//	the container does not exists. so return an error
//					break;
//				}

				boolSuccessFlag =	TRUE;
				break;

			case	CRYPT_NEWKEYSET:
				hResult =	GetVSC
							(
								pCSP,
								&pVSmartCard
							);
				VSCSP_CHECK_HRESULT

						//	check if the container exists
						//	if it exists then the function will return VS_SUCCESS
						//	else it will return NTE_BAD_KEYSET
				hResult =	CheckIfContainerExists
							(
								pCSP,
								pVSmartCard
							);
				if ( NTE_BAD_KEYSET != hResult )
				{
						//	this means that the container already exists (and cannot be recreated)
						//	or there is some other error.
						//	so break
					dwLastError =	hResult;
					break;
				}

				structContainer.structSign.dwExists	=	0;
				structContainer.structXchg.dwExists =	0;

				hResult =	pVSmartCard -> VSM_SetInformationBlob
							(
								tbstrContainerName,
								(const BYTE*) &structContainer,
								sizeof (CSP_Key_Container)
							);
				VSCSP_CHECK_HRESULT

				/*Create entries in the registry associating this container and the profile name*/
				
				tbstrVeriSignCryptoKey += tbstrContainerName;
				tbstrVeriSignCryptoKey += "\\";

				hResult =	pVSmartCard -> get_VSM_ProfileName
							(
								&varSmartCardName
							);
				VSCSP_CHECK_HRESULT

				tbstrSmartCardName =	varSmartCardName;

				if(!RegCreateKeyEx(HKEY_CURRENT_USER,tbstrVeriSignCryptoKey,0,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL, &hkVeriSignCryptoKey, &disp))
				{
					//Create a name value pair
					if(RegSetValueEx(hkVeriSignCryptoKey, (TCHAR*)PROFILE_NAME, NULL, REG_SZ, (PBYTE)(TCHAR*)tbstrSmartCardName, lstrlen((TCHAR*)tbstrSmartCardName)+1))
					{
						hResult = E_REGSETVALUEFAILED;
						break;
					}
					else
					{
						RegCloseKey(hkVeriSignCryptoKey);
					}
				}
				else
				{
					hResult = E_REGCREATEKEYFAILED;
					break;
				}

				boolSuccessFlag =	TRUE;
				break;
		}	//	end		switch ( dwFlags )

		if ( TRUE != boolSuccessFlag )
		{
			break;
		}

		*phProv =	(HCRYPTPROV) pCSP;

//		VSPTA_CLEAN_TBSTR(tbstrName)
//		VSPTA_CLEAN_TBSTR(tbstrContainerName)
//		VSPTA_CLEAN_TBSTR(tbstrProfilePathName)
//		VSPTA_CLEAN_TBSTR(tbstrProfileName)
//		VSPTA_CLEAN_TBSTR(tbstrVeriSignCryptoKey)
//		VSPTA_CLEAN_TBSTR(tbstrSmartCardName)

		bResult	=	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	
	::SetLastError ( dwLastError );

	return	bResult;
}

/*
 -      CPReleaseContext
 -
 *      Purpose:
 *               The CPReleaseContext function is used to release a
 *               context created by CrytAcquireContext.
 *
 *     Parameters:
 *               IN  phProv        -  Handle to a CSP
 *               IN  dwFlags       -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPReleaseContext
(
	IN HCRYPTPROV hProv,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPReleaseContext", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHashNext		=	NULL;
	CSP_KeyParam*				pclassKeyNext		=	NULL;
	DWORD						dwLastError			=	0;

	while (1)
	{

		pCSP =	( CSP_State*) hProv;
		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT


		VSCSP_CHECK_FOR_NULL_AND_DELETE (pCSP -> pszNameOfContainer)
//		VSCSP_CHECK_FOR_NULL_AND_DELETE (pCSP -> pCVSPTAInst)

		DeleteKeyChain (pCSP);
		DeleteHashChain (pCSP);

//		VSCSP_CHECK_FOR_NULL_AND_DELETE (pCSP -> pVTable)
		if ( NULL != (pCSP -> pIProfMgmt) )
		{
			(pCSP -> pIProfMgmt) -> Release ();
		}

		if ( NULL != (pCSP -> pIPTA) )
		{
			(pCSP -> pIPTA) -> Close ();
			(pCSP -> pIPTA) -> Release ();
		}

		CoUninitialize ();

		VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ((pCSP -> pbyteCorrSignPublicKey), (pCSP -> dwCorrSignPublicKeyLen))
//		pCSP -> dwCorrSignPublicKeyLen	=	0;

		VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ((pCSP -> pbyteCorrXchgPublicKey), (pCSP -> dwCorrXchgPublicKeyLen))
//		pCSP -> dwCorrXchgPublicKeyLen	=	0;

		pCSP -> dwSizeofStruct			=	0;

		VSCSP_CHECK_FOR_NULL_AND_DELETE (pCSP)
		pCSP =	NULL;

		hProv =	NULL;

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPGenKey
 -
 *	Purpose:
 *                Generate cryptographic keys
 *
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      Algid   -  Algorithm identifier
 *               IN      dwFlags -  Flags values
 *               OUT     phKey   -  Handle to a generated key
 *
 *	Returns:
 *
 * REV HISTORY
 * Date           Author           Desc
 * ----           ------           ----
 * 04/14/2003     Sasi             Added 3DES key gen support.
 */
BOOL WINAPI CPGenKey
(
	IN HCRYPTPROV hProv,
	IN int Algid,
	IN DWORD dwFlags,
	OUT HCRYPTKEY * phKey
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPGenKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	999;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;

//	WORD						wKeyLength			=	0;
	DWORD						dwKeyLength			=	0;
	DWORD						dwLowerFlags		=	0;

	CVirtualSmartCard*			pVSmartCard			=	NULL;

	CSP_Key_Container			structContainer;
	CSP_PubKeyHash*				pstructPubKeyHash	=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

//	DWORD						dwExportable		=	0;

	DWORD						dwAlgID				=	0;
	DWORD						dwKeyExists			=	999;
	DWORD						dwLastError			=	0;

	while (1)
	{
		_bstr_t					tbstrContainerName;

		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		if (	( CALG_RC2			!= Algid )\
			 &&	( CALG_RC4			!= Algid )\
			 &&	( CALG_3DES			!= Algid )\
			 && ( AT_SIGNATURE		!= Algid )\
			 && ( AT_KEYEXCHANGE	!= Algid ) )
		{
			dwLastError =	NTE_BAD_ALGID;
			break;
		}

		VSCSP_SWITCH_ALGOS

		pCSP =	(CSP_State*) hProv;
		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	GetVSC
					(
						pCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT



			//	TODOTPM: the 3DES support is not there in the old CSP
			//	if we want to add that to the new CSP, since its in the
			//	common code, we can also expose it thru the old CSP

		tbstrContainerName =	pCSP -> pszNameOfContainer;

			//	create a new instance of the key class
		pclassKey =	new (CSP_KeyParam);
		VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey)

		dwLowerFlags =	dwFlags & 0x0000FFFF;

		pclassKey -> dwExportable =	dwLowerFlags & CRYPT_EXPORTABLE;
		
			//	initialize the class
		pclassKey -> dwAlgID				=	dwAlgID;

		if ( CALG_RC4 == dwAlgID )
			pclassKey -> dwBlockLen	=	0;
		else
			pclassKey -> dwBlockLen	=	VS_CSP_DEFAULT_BLOCK_LENGTH;

		pclassKey -> dwCypherModes			=	VS_CSP_DEFAULT_CYPHER_MODES;
		pclassKey -> dwModeBits				=	0;

				//	the key length is the upper 16 bits of the dwFlags.
				//	so shift the dwKeyLength by 16 bits
		dwKeyLength =	dwFlags;
		dwKeyLength =	dwKeyLength >> 16;

		if( ( 0 == dwKeyLength ) &&  ( (VS_RC4 == dwAlgID) || (VS_RC2 == dwAlgID) ))
		{
			dwKeyLength =	SYMMETRIC_KEY_LENGTH;
		}

		if( VS_3DES == dwAlgID)
			dwKeyLength =	VS_3DES_KEY_LENGTH;  
		
		if ( VS_RC2 == dwAlgID )
		{
				//	this parameter is used only if its a rc2 key
			pclassKey -> dwEffectiveKeyLen		=	dwKeyLength;
		}
		else
		{
			pclassKey -> dwEffectiveKeyLen		=	0;
		}

		pclassKey -> dwKeyLenBits			=	dwKeyLength;

		if ( (VS_RSA_KEYX == dwAlgID) || (VS_RSA_SIGN == dwAlgID) )
		{

			//	if TPM CSP then use alternative functions...
			if ( VS_TPM_CSP == pCSP -> dwCSPName )
			{
				hResult = pCSP->pIPTA->CreatePassword(); 
				VSCSP_CHECK_HRESULT

				hResult =	pVSmartCard -> VSTPM_CheckIfKeyExists
							(
								dwAlgID, 
								&dwKeyExists
							);
				VSCSP_CHECK_HRESULT

				//	check if the key exists
				if ( 1 == dwKeyExists )
				{
						//	this means the key already exists... so return error
					dwLastError =	NTE_FAIL;
					break;
				}
				else
				{
						//	else create a key
					hResult =	pVSmartCard -> VSTPM_CreateKey
								(
									dwKeyLength,
									dwAlgID,
									&(pclassKey -> pVSTSSKey)
								);
					VSCSP_CHECK_HRESULT
				}
			}	//	end		if ( VS_TPM_CSP == pCSP -> dwCSPName )
			else
			{
				hResult =	CheckIfKeyExists
							(
								pCSP,
								pVSmartCard,
								dwAlgID,
								&structContainer
							);
				if ( NTE_NO_KEY == hResult )
				{
					hResult =	pVSmartCard -> VSM_GenKey
								(
	//								pCSP -> pszNameOfContainer,
									(const int) dwAlgID,
									(const int) dwKeyLength,
									(const DWORD) pclassKey -> dwExportable,
									NULL,
									(DWORD*) &(pclassKey -> dwCorrPublicKeyLen)
								);
					VSCSP_CHECK_HRESULT

					pclassKey -> pbyteCorrPublicKey =	new BYTE [pclassKey -> dwCorrPublicKeyLen];
					VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteCorrPublicKey)

					hResult =	pVSmartCard -> VSM_GenKey
								(
	//								pCSP -> pszNameOfContainer,
									(const int) dwAlgID,
									(const int) dwKeyLength,
									(const DWORD) pclassKey -> dwExportable,
									(BYTE*) pclassKey -> pbyteCorrPublicKey,
									(DWORD*) &(pclassKey -> dwCorrPublicKeyLen)
								);
					VSCSP_CHECK_HRESULT

					boolSuccessFlag =	FALSE;
					switch ( dwAlgID )
					{
						case	VS_RSA_KEYX:
									//	the code outside this case statement is same for
									//	both exchange and signature key pair.
									//	so assigning the exchange pub key hash structure
									//	to the temp structure
							pstructPubKeyHash =	&(structContainer.structXchg);
										
							boolSuccessFlag =	TRUE;
							break;

						case	VS_RSA_SIGN:
									//	the code outside this case statement is same for
									//	both exchange and signature key pair.
									//	so assigning the signature pub key hash structure
									//	to the temp structure
							pstructPubKeyHash =	&(structContainer.structSign);

							boolSuccessFlag =	TRUE;
							break;

						default:
							hResult =	NTE_BAD_FLAGS;
							break;
					}	//	end		switch ( dwAlgID )
					if ( FALSE == boolSuccessFlag )
					{
						break;
					}

							//	put the pub key hash in the structure and also assign
							//	proper values to the other members of the structure
					pstructPubKeyHash -> dwExists		=	VS_CSP_KEY_EXISTS;
					pstructPubKeyHash -> dwExportable	=	pclassKey -> dwExportable;
					memcpy
					(
						(void*) pstructPubKeyHash -> pbytePubKeyHash,
						(const void*) pclassKey -> pbyteCorrPublicKey,
						VS_CSP_SHA1_LEN
					);

								//	The information blob cannot be updated
								//	so it will have to be deleted and then set with a new value
								//
								//	delete the information blob
					hResult =	pVSmartCard -> VSM_DeleteInformationBlob
								(
									tbstrContainerName
								);
					VSCSP_CHECK_HRESULT

							//	add the info blob with container name and the public key hashes etc.
					hResult =	pVSmartCard -> VSM_SetInformationBlob
								(
									tbstrContainerName,
									(const unsigned char*) &structContainer,
									(unsigned int) sizeof (CSP_Key_Container)
								);
					VSCSP_CHECK_HRESULT

					boolSuccessFlag =	FALSE;
					switch ( dwAlgID )
					{
						case	VS_RSA_KEYX:
							pCSP -> dwCorrXchgPublicKeyLen =	pclassKey -> dwCorrPublicKeyLen;
							pCSP -> pbyteCorrXchgPublicKey =	new BYTE [pCSP -> dwCorrXchgPublicKeyLen];
							VSCSP_CHECK_ALLOCATED_MEMORY (pCSP -> pbyteCorrXchgPublicKey)

							memcpy
							(
								(void*) pCSP -> pbyteCorrXchgPublicKey,
								(const void*) pclassKey -> pbyteCorrPublicKey,
								pCSP -> dwCorrXchgPublicKeyLen
							);
										
							boolSuccessFlag =	TRUE;
							break;

						case	VS_RSA_SIGN:
							pCSP -> dwCorrSignPublicKeyLen =	pclassKey -> dwCorrPublicKeyLen;
							pCSP -> pbyteCorrSignPublicKey =	new BYTE [pCSP -> dwCorrSignPublicKeyLen];
							VSCSP_CHECK_ALLOCATED_MEMORY (pCSP -> pbyteCorrSignPublicKey)

							memcpy
							(
								(void*) pCSP -> pbyteCorrSignPublicKey,
								(const void*) pclassKey -> pbyteCorrPublicKey,
								pCSP -> dwCorrSignPublicKeyLen
							);

							boolSuccessFlag =	TRUE;
							break;

						default:
							hResult =	NTE_BAD_FLAGS;
							break;
					}	//	end		switch ( dwAlgID )
					if ( FALSE == boolSuccessFlag )
					{
						break;
					}

				}	//	end		if ( NTE_NO_KEY == hResult )
			}
		}
		else if ( (VS_RC4 == dwAlgID) || (VS_RC2 == dwAlgID) || (VS_3DES == dwAlgID))
		{
			(pclassKey -> itemKey).data =	new BYTE [dwKeyLength / 8];
			(pclassKey -> itemKey).len	=	dwKeyLength / 8;

			nResult =	GenerateRandomBlock
						(
							(pclassKey -> itemKey).data,
							(pclassKey -> itemKey).len
						);
			VSCSP_CHECK_NRESULT
		}

		pclassKey -> dwPermissions			=	CRYPT_DECRYPT | CRYPT_ENCRYPT | CRYPT_EXPORT | CRYPT_READ | CRYPT_WRITE;

		pclassKey -> dwInitVectorLength		=	VS_CSP_DEFAULT_BLOCK_LENGTH / 8;
		pclassKey -> pbyteInitVector =	new BYTE [pclassKey -> dwInitVectorLength];
		VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteInitVector)
		::memcpy
		(
			(void*) pclassKey -> pbyteInitVector,
			(const void*) VS_CSP_DEFAULT_INIT_VECTOR,
			VS_CSP_DEFAULT_BLOCK_LENGTH / 8
		);

		if ( CRYPT_CREATE_SALT | dwLowerFlags )
		{
			pclassKey -> dwSaltLength =	11;
				//	TBD: generate a random number and copy it in
				//	pclassKey -> pbyteSalt
		}
		else
		{
			pclassKey -> dwSaltLength =	0;
		}

		pclassKey -> dwPadding				=	PKCS5_PADDING;

				//	add the key structure to the list. this is part of a CSP context
		hResult =	AddKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT


				//	the pointer to the key param class is the handle to the key object
		*phKey =	(HCRYPTKEY) pclassKey;

//		VSPTA_CLEAN_TBSTR(tbstrContainerName)

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
	return	bResult;
}

/*
 -	CPDeriveKey
 -
 *	Purpose:
 *                Derive cryptographic keys from base data
 *
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      Algid      -  Algorithm identifier
 *               IN      hHash      -  Handle to hash 
 *               IN      dwFlags    -  Flags values
 *               OUT     phKey      -  Handle to a generated key
 *
 *	Returns:
 */
BOOL WINAPI CPDeriveKey
(
	IN HCRYPTPROV hProv,
	IN int Algid,
	IN HCRYPTHASH hHash,
	IN DWORD dwFlags,
	OUT HCRYPTKEY * phKey
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPDeriveKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	DWORD						dwLowerFlags		=	999;
//	DWORD						dwExportable		=	999;
	DWORD						dwKeyLength			=	0;

	DWORD						dwAlgID				=	0;
	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (phKey)

		VSCSP_SWITCH_ALGOS

		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		if ( HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus )
		{
			pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CLOSED;
		}

		pclassKey =	new CSP_KeyParam;
		VSCSP_CHECK_ALLOCATED_MEMORY (phKey)

		dwLowerFlags =	dwFlags & 0x0000FFFF;

		pclassKey -> dwExportable =	dwLowerFlags & CRYPT_EXPORTABLE;
		
			//	initialize the class
		pclassKey -> dwAlgID				=	dwAlgID;

		if ( CALG_RC4 == dwAlgID )
			pclassKey -> dwBlockLen	=	0;
		else
			pclassKey -> dwBlockLen	=	VS_CSP_DEFAULT_BLOCK_LENGTH;

		pclassKey -> dwCypherModes			=	VS_CSP_DEFAULT_CYPHER_MODES;
		pclassKey -> dwModeBits				=	0;

		::memcpy ( (void*) ( (&dwKeyLength) + 2 ), (const void*) &dwAlgID, sizeof (WORD) );
		
		if ( VS_RC2 == dwAlgID )
		{
				//	this parameter is used only if its a rc2 key
			pclassKey -> dwEffectiveKeyLen		=	dwKeyLength;
		}
		else
		{
			pclassKey -> dwEffectiveKeyLen		=	0;
		}

		pclassKey -> dwKeyLenBits			=	dwKeyLength;

		(pclassKey -> itemKey).len	=	dwKeyLength / 8;
		
		::memcpy
		(
			(pclassKey -> itemKey).data,
			pclassHash -> pbDataHash,
			(pclassKey -> itemKey).len
		);

		pclassKey -> dwPermissions			=	CRYPT_DECRYPT | CRYPT_ENCRYPT | CRYPT_EXPORT | CRYPT_READ | CRYPT_WRITE;

		pclassKey -> dwInitVectorLength		=	VS_CSP_DEFAULT_BLOCK_LENGTH / 8;
		pclassKey -> pbyteInitVector =	new BYTE [pclassKey -> dwInitVectorLength];
		VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteInitVector)
		::memcpy
		(
			(void*) pclassKey -> pbyteInitVector,
			(const void*) VS_CSP_DEFAULT_INIT_VECTOR,
			VS_CSP_DEFAULT_BLOCK_LENGTH / 8
		);

		if ( CRYPT_CREATE_SALT | dwLowerFlags )
		{
			pclassKey -> dwSaltLength =	11;
				//	TBD: generate a random number and copy it in
				//	pclassKey -> pbyteSalt
		}
		else
		{
			pclassKey -> dwSaltLength =	0;
		}

		pclassKey -> dwPadding				=	PKCS5_PADDING;

				//	add the key structure to the list. this is part of a CSP context
		hResult =	AddKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT


				//	the pointer to the key param class is the handle to the key object
		*phKey =	(HCRYPTKEY) pclassKey;
		
		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPDestroyKey
 -
 *	Purpose:
 *                Destroys the cryptographic key that is being referenced
 *                with the hKey parameter
 *
 *
 *	Parameters:
 *               IN      hProv  -  Handle to a CSP
 *               IN      hKey   -  Handle to a key
 *
 *	Returns:
 */
BOOL WINAPI CPDestroyKey
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPDestroyKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;

	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)

		pCSP		=	(CSP_State*) hProv;
		pclassKey	=	(CSP_KeyParam*) hKey;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	DeleteKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPSetKeyParam
 -
 *	Purpose:
 *                Allows applications to customize various aspects of the
 *                operations of a key
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      hKey    -  Handle to a key
 *               IN      dwParam -  Parameter number
 *               IN      pbData  -  Pointer to data
 *               IN      dwFlags -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPSetKeyParam
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey,
	IN DWORD dwParam,
	IN BYTE *pbData,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPSetKeyParam", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	DWORD						dwSaltLen			=	0;

	BLOB*						pblobSalt			=	NULL;

	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)

		pCSP		=	(CSP_State*) hProv;
		pclassKey	=	(CSP_KeyParam*) hKey;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		switch ( dwParam )
		{
			case	KP_SALT:
							//	get the size of the salt.
							//
							//	the pbData is NULL so the required length for the buffer = the length
							//	of the salt will be returned
				bResult =	CPGetKeyParam
							(
								hProv,
								hKey,
								KP_SALT,
								NULL,
								&dwSaltLen,
								0
							);
				if ( CRYPT_FAILED == bResult )
				{
					::SetLastError ( (DWORD) NTE_FAIL );
					break;
				}

					//	copy the salt value
				pclassKey -> pbyteSalt = (BYTE*) new BYTE [dwSaltLen];
				VSCSP_CHECK_ALLOCATED_MEMORY ( pclassKey -> pbyteSalt )

				::memcpy
				(
					(void*) pclassKey -> pbyteSalt,
					(const void*) pbData,
					dwSaltLen
				);

				pclassKey -> dwSaltLength =	dwSaltLen;
				
				boolSuccessFlag =	TRUE;
				break;

			case	KP_SALT_EX:
					//	this is a salt but it is passed as a BLOB. so the length of the salt
					//	is also included in it.

				pblobSalt =	(BLOB*) pbData;

				::memcpy
				(
					(void*) pclassKey -> pbyteSalt,
					pblobSalt -> pBlobData,
					pblobSalt -> cbSize
				);

				pclassKey -> dwSaltLength =	pblobSalt -> cbSize;

				boolSuccessFlag =	TRUE;
				break;

			case	KP_PERMISSIONS:
				pclassKey -> dwPermissions =	(DWORD) *pbData;

				boolSuccessFlag =	TRUE;
				break;

			case	KP_IV:
				pclassKey -> dwInitVectorLength =	VS_CSP_DEFAULT_BLOCK_LENGTH / 8;
				pclassKey -> pbyteInitVector =	new BYTE [pclassKey -> dwInitVectorLength];
				VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteInitVector)

				::memcpy
				(
					(void*) pclassKey -> pbyteInitVector,
					(const void*) pbData,
					VS_CSP_DEFAULT_BLOCK_LENGTH / 8
				);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_PADDING:
				pclassKey -> dwPadding =	(DWORD) *pbData;

				boolSuccessFlag =	TRUE;
				break;

			case	KP_MODE:
				pclassKey -> dwCypherModes =	(DWORD) *pbData;

				boolSuccessFlag =	TRUE;
				break;

			case	KP_MODE_BITS:
				pclassKey -> dwModeBits =	(DWORD) *pbData;

				boolSuccessFlag =	TRUE;
				break;

			case	KP_EFFECTIVE_KEYLEN:
				if ( VS_RC2 != pclassKey -> dwAlgID )
				{
					::SetLastError ( (DWORD) NTE_BAD_TYPE );
					break;
				}

				pclassKey -> dwEffectiveKeyLen =	(DWORD) *pbData;

				boolSuccessFlag =	TRUE;
				break;

		}	//	end		switch ( dwParam )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPGetKeyParam
 -
 *	Purpose:
 *                Allows applications to get various aspects of the
 *                operations of a key
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      hKey       -  Handle to a key
 *               IN      dwParam    -  Parameter number
 *               IN      pbData     -  Pointer to data
 *               IN      pdwDataLen -  Length of parameter data
 *               IN      dwFlags    -  Flags values
 *
 *	Returns:
 * REV HISTORY
 * Date           Author           Desc
 * ----           ------           ----
 * 07/18/2003     Ajay            Fixed bug in returning the size of the KP_BLOCKLEN for public/private key pair.
 */
BOOL WINAPI CPGetKeyParam
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey,
	IN DWORD dwParam,
	IN BYTE *pbData,
	IN DWORD *pdwDataLen,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPGetKeyParam", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwDataLen)

		pCSP		=	(CSP_State*) hProv;
		pclassKey	=	(CSP_KeyParam*) hKey;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		switch ( dwParam )
		{
			case	KP_ALGID:
				if ( NULL != pbData )
				{
					if ( sizeof (ALG_ID) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (ALG_ID);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwAlgID),
						sizeof (ALG_ID)
					);
				}

				*pdwDataLen =	sizeof (ALG_ID);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_BLOCKLEN:
				if ( NULL != pbData )
				{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					// Ajay - From CAPI help....
					// If a public/private key pair is specified by hKey, this parameter returns a
					// BLOB containing the key pair's encryption granularity in bits.
					// For RSA key pairs, this is the size of the modulus

					if(pclassKey -> dwAlgID == VS_RSA_KEYX || pclassKey -> dwAlgID == VS_RSA_SIGN)
					{
						::memcpy
						(
							(void*) pbData,
							(const void*) &(pclassKey -> dwKeyLenBits),
							sizeof (DWORD)
						);

					}
					else // If a session key is specified by hKey, returns the key cipher's block length, in bits
					{
						::memcpy
						(
							(void*) pbData,
							(const void*) &(pclassKey -> dwBlockLen),
							sizeof (DWORD)
						);
					}
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_KEYLEN:
				if ( NULL != pbData )
				{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwKeyLenBits),
						sizeof (DWORD)
					);
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_SALT:
				if ( NULL != pbData )
					{
					if ( pclassKey -> dwSaltLength > *pdwDataLen )
					{
						*pdwDataLen =	pclassKey -> dwSaltLength;
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) pclassKey -> pbyteSalt,
						pclassKey -> dwSaltLength
					);
				}

				*pdwDataLen =	pclassKey -> dwSaltLength;
				
				boolSuccessFlag =	TRUE;
				break;

			case	KP_PERMISSIONS:
				if ( NULL != pbData )
					{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwPermissions),
						sizeof (DWORD)
					);
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_IV:
				if ( NULL != pbData )
					{
					if ( pclassKey -> dwInitVectorLength > *pdwDataLen )
					{
						*pdwDataLen =	pclassKey -> dwInitVectorLength;
						dwLastError = ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) pclassKey -> pbyteInitVector,
						pclassKey -> dwInitVectorLength
					);
				}

				*pdwDataLen =	pclassKey -> dwInitVectorLength;

				boolSuccessFlag =	TRUE;
				break;

			case	KP_PADDING:
				if ( NULL != pbData )
					{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwPadding),
						sizeof (DWORD)
					);
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_MODE:
				if ( NULL != pbData )
					{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwCypherModes),
						sizeof (DWORD)
					);
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_MODE_BITS:
				if ( NULL != pbData )
					{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwModeBits),
						sizeof (DWORD)
					);
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	KP_EFFECTIVE_KEYLEN:
				if ( NULL != pbData )
					{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					::memcpy
					(
						(void*) pbData,
						(const void*) &(pclassKey -> dwEffectiveKeyLen),
						sizeof (DWORD)
					);
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;
		}	//	end		switch (dwParam)

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}



/*
 -	CPSetProvParam
 -
 *	Purpose:
 *                Allows applications to customize various aspects of the
 *                operations of a provider
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      dwParam -  Parameter number
 *               IN      pbData  -  Pointer to data
 *               IN      dwFlags -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPSetProvParam
(
	IN HCRYPTPROV hProv,
	IN DWORD dwParam,
	IN BYTE *pbData,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPSetProvParam", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	::SetLastError ( (DWORD)E_NOTIMPL );
    return(CRYPT_FAILED);
}


/*
 -	CPGetProvParam
 -
 *	Purpose:
 *                Allows applications to get various aspects of the
 *                operations of a provider
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      dwParam    -  Parameter number
 *               IN      pbData     -  Pointer to data
 *               IN      pdwDataLen -  Length of parameter data
 *               IN      dwFlags    -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPGetProvParam
(
	IN HCRYPTPROV hProv,
	IN DWORD dwParam,
	IN BYTE *pbData,
	IN DWORD *pdwDataLen,
	IN DWORD dwFlags
)
{

#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPGetProvParam", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif


	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	BOOL						boolSuccessFlag		=	FALSE;

	CSP_State*					pCSP				=	NULL;

	DWORD						dwTemp				=	0;
	DWORD						dwLastError			=	0;


	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwDataLen)

		pCSP =	(CSP_State*) hProv;
		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		switch ( dwParam )
		{
			case	PP_CONTAINER:
				if ( NULL != pbData )
				{
					if ( (::lstrlen (pCSP -> pszNameOfContainer) + 1) * sizeof (CHAR) > *pdwDataLen )
					{
							//	 check size. if more memory is req then indicated the required
							//	memory and return error
						*pdwDataLen =	(::lstrlen (pCSP -> pszNameOfContainer) + 1) * sizeof (CHAR);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

							//	copy container name and its size
					::lstrcpy ( (CHAR*) pbData, (const CHAR*) (pCSP -> pszNameOfContainer) );
				}

				*pdwDataLen =	(::lstrlen (pCSP -> pszNameOfContainer) + 1) * sizeof (CHAR);

				boolSuccessFlag =	TRUE;
				break;

			case	PP_ENUMALGS:
				if ( VS_TPM_CSP == pCSP -> dwCSPName )
				{
					if ( NULL != pbData )
					{
							//	check if the first algo flag is set
						if ( CRYPT_FIRST == dwFlags )
						{
							g_TPM_AlgoInfo.nIndex =	0;
						}

						if ( NUMBER_OF_TPM_ALGOS > g_TPM_AlgoInfo.nIndex )
						{
								//	check for the required size
							if ( sizeof (PROV_ENUMALGS) > *pdwDataLen )
							{
										//	if the allocated memory is less that what is req
										//	then return an error and the required memory size
								*pdwDataLen =	sizeof (PROV_ENUMALGS);
								dwLastError =	ERROR_MORE_DATA;
								break;
							}

									//	copy the nth algo structure and the corresponding size
							::memcpy ( (void*) pbData, (const void*) &(g_TPM_AlgoInfo.pEnumAlgs[g_TPM_AlgoInfo.nIndex]), sizeof (PROV_ENUMALGS) );

									//	increment the index in the algos array
							g_TPM_AlgoInfo.nIndex ++;
						}
						else
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}
					}
					else
						if ( NUMBER_OF_TPM_ALGOS <= g_TPM_AlgoInfo.nIndex )
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}

					*pdwDataLen =	sizeof (PROV_ENUMALGS);

					boolSuccessFlag =	TRUE;
					break;
				}
				else
				{
					if ( NULL != pbData )
					{
							//	check if the first algo flag is set
						if ( CRYPT_FIRST == dwFlags )
						{
							g_AlgoInfo.nIndex =	0;
						}

						if ( NUMBER_OF_ALGOS > g_AlgoInfo.nIndex )
						{
								//	check for the required size
							if ( sizeof (PROV_ENUMALGS) > *pdwDataLen )
							{
										//	if the allocated memory is less that what is req
										//	then return an error and the required memory size
								*pdwDataLen =	sizeof (PROV_ENUMALGS);
								dwLastError =	ERROR_MORE_DATA;
								break;
							}

									//	copy the nth algo structure and the corresponding size
							::memcpy ( (void*) pbData, (const void*) &(g_AlgoInfo.pEnumAlgs[g_AlgoInfo.nIndex]), sizeof (PROV_ENUMALGS) );

									//	increment the index in the algos array
							g_AlgoInfo.nIndex ++;
						}
						else
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}
					}
					else
						if ( NUMBER_OF_ALGOS <= g_AlgoInfo.nIndex )
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}

					*pdwDataLen =	sizeof (PROV_ENUMALGS);

					boolSuccessFlag =	TRUE;
					break;
				}

			case	PP_ENUMALGS_EX:
				if ( VS_TPM_CSP == pCSP -> dwCSPName )
				{
					if ( NULL != pbData )
					{
							//	check if the first algo flag is set
						if ( CRYPT_FIRST == dwFlags )
						{
							g_TPM_ExAlgoInfo.nIndex =	0;
						}
						if ( NUMBER_OF_TPM_ALGOS > g_TPM_ExAlgoInfo.nIndex )
						{
								//	check for the required size
							if ( sizeof (PROV_ENUMALGS_EX) > *pdwDataLen )
							{
										//	if the allocated memory is less that what is req
										//	then return an error and the required memory size
								*pdwDataLen =	sizeof (PROV_ENUMALGS_EX);
								dwLastError =	ERROR_MORE_DATA;
								break;
							}

									//	copy the nth algo structure and the corresponding size
							::memcpy ( (void*) pbData, (const void*) &(g_TPM_ExAlgoInfo.pEnumAlgsEx[g_TPM_ExAlgoInfo.nIndex]), sizeof (PROV_ENUMALGS_EX) );

									//	increment the index in the algos array
							g_TPM_ExAlgoInfo.nIndex ++;
						}
						else
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}
					}
					else
						if ( NUMBER_OF_TPM_ALGOS <= g_TPM_ExAlgoInfo.nIndex )
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}

					*pdwDataLen =	sizeof (PROV_ENUMALGS_EX);

					boolSuccessFlag =	TRUE;
					break;
				}
				else
				{
					if ( NULL != pbData )
					{
							//	check if the first algo flag is set
						if ( CRYPT_FIRST == dwFlags )
						{
							g_ExAlgoInfo.nIndex =	0;
						}
						if ( NUMBER_OF_ALGOS > g_ExAlgoInfo.nIndex )
						{
								//	check for the required size
							if ( sizeof (PROV_ENUMALGS_EX) > *pdwDataLen )
							{
										//	if the allocated memory is less that what is req
										//	then return an error and the required memory size
								*pdwDataLen =	sizeof (PROV_ENUMALGS_EX);
								dwLastError =	ERROR_MORE_DATA;
								break;
							}

									//	copy the nth algo structure and the corresponding size
							::memcpy ( (void*) pbData, (const void*) &(g_ExAlgoInfo.pEnumAlgsEx[g_ExAlgoInfo.nIndex]), sizeof (PROV_ENUMALGS_EX) );

									//	increment the index in the algos array
							g_ExAlgoInfo.nIndex ++;
						}
						else
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}
					}
					else
						if ( NUMBER_OF_ALGOS <= g_ExAlgoInfo.nIndex )
						{
							*pdwDataLen = 0;
							dwLastError =	ERROR_NO_MORE_ITEMS;
							break;
						}

					*pdwDataLen =	sizeof (PROV_ENUMALGS_EX);

					boolSuccessFlag =	TRUE;
					break;
				}

			case	PP_ENUMCONTAINERS:
				dwLastError =	E_NOTIMPL;
				break;

//				boolSuccessFlag =	TRUE;
//				break;

			case	PP_IMPTYPE:
				if ( NULL != pbData )
				{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
							//	 check size. if more memory is req then indicated the required
							//	memory and return error
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

						//	copy implementation type and the correcponding size
					dwTemp =	CRYPT_IMPL_SOFTWARE;
					::memcpy ( (void*) pbData, (const void*) &dwTemp, sizeof (DWORD) );
				}
				
				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			case	PP_NAME:
				if ( VS_TPM_CSP == pCSP -> dwCSPName )
				{
					if ( NULL != pbData )
					{
						if ( (::lstrlen ((const CHAR*)VS_TPM_CSP_NAME) + 1) * sizeof (CHAR) > *pdwDataLen )
						{
								//	 check size. if more memory is req then indicated the required
								//	memory and return error
							*pdwDataLen =	(::lstrlen ((const CHAR*)VS_TPM_CSP_NAME) + 1) * sizeof (CHAR);
							dwLastError =	ERROR_MORE_DATA;
							break;
						}

							//	copy the CSP name and its size
						::lstrcpy ( (CHAR*) pbData, (const CHAR*) VS_TPM_CSP_NAME );
					}

					*pdwDataLen =	(::lstrlen ((const CHAR*)VS_TPM_CSP_NAME) + 1) * sizeof (CHAR);

					boolSuccessFlag =	TRUE;
					break;
				}
				else
				{
					if ( NULL != pbData )
					{
						if ( (::lstrlen ((const CHAR*)CSP_AP_CTXT_NAME) + 1) * sizeof (CHAR) > *pdwDataLen )
						{
								//	 check size. if more memory is req then indicated the required
								//	memory and return error
							*pdwDataLen =	(::lstrlen ((const CHAR*)CSP_AP_CTXT_NAME) + 1) * sizeof (CHAR);
							dwLastError =	ERROR_MORE_DATA;
							break;
						}

							//	copy the CSP name and its size
						::lstrcpy ( (CHAR*) pbData, (const CHAR*) CSP_AP_CTXT_NAME );
					}

					*pdwDataLen =	(::lstrlen ((const CHAR*)CSP_AP_CTXT_NAME) + 1) * sizeof (CHAR);

					boolSuccessFlag =	TRUE;
					break;
				}

			case	PP_VERSION:
				if ( NULL != pbData )
				{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
							//	 check size. if more memory is req then indicated the required
							//	memory and return error
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

						// copy the CSP version and its size
					dwTemp =	CSP_VERSION;
					::memcpy ( (void*) pbData, (const void*) &dwTemp, sizeof (DWORD) );
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

//			case	PP_SIG_KEYSIZE_INC:
//
//				boolSuccessFlag =	TRUE;
//				break;
//
//			case	PP_KEYX_KEYSIZE_INC:
//
//				boolSuccessFlag =	TRUE;
//				break;
//
			case	PP_KEYSET_SEC_DESCR:

				dwLastError =	E_NOTIMPL;
				break;

//			case	PP_UNIQUE_CONTAINER:
//
//				boolSuccessFlag =	TRUE;
//				break;
//
			case	PP_PROVTYPE:
				if ( NULL != pbData )
				{
					if ( sizeof (DWORD) > *pdwDataLen )
					{
							//	 check size. if more memory is req then indicated the required
							//	memory and return error
						*pdwDataLen =	sizeof (DWORD);
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

						//	copy the CSP type and the corresponding size
					dwTemp =	CSP_TYPE;
					::memcpy ( (void*) pbData, (const void*) &dwTemp, sizeof (DWORD) );
				}

				*pdwDataLen =	sizeof (DWORD);

				boolSuccessFlag =	TRUE;
				break;

			default:
				break;

		}	//	end		switch (dwParam)

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}



/*
 -	CPSetHashParam
 -
 *	Purpose:
 *                Allows applications to customize various aspects of the
 *                operations of a hash
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      hHash   -  Handle to a hash
 *               IN      dwParam -  Parameter number
 *               IN      pbData  -  Pointer to data
 *               IN      dwFlags -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPSetHashParam
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
	IN DWORD dwParam,
	IN BYTE *pbData,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPSetHashParam", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	DWORD						dwLenOfHash			=	0;
	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
	
		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

				//	the only possible value for dwParam is HP_HASHVAL which is not supported.
				//	so in either case the same error is returned.
		if ( HP_HASHVAL == dwParam )
		{
			if ( VS_TPM_CSP == pCSP -> dwCSPName )
			{
				hResult =	pclassHash -> pVSTSSHash->SetHashValue
							(
								//20,
								pclassHash -> dwDataHashLength,
								pbData
							);
				VSCSP_CHECK_HRESULT

				pclassHash -> dwIsEmpty = 0;
				pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CLOSED;
			}
			else
			{
				if ( 1 == pclassHash -> dwIsEmpty ||
					HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus )
				{
					memcpy
					(
						(void*) (pclassHash -> pbDataHash),
						(const void*) pbData,
						(pclassHash -> dwDataHashLength)
					);

					pclassHash -> dwIsEmpty = 0;
					pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CLOSED;
				}
				else
				{
					dwLastError =	NTE_BAD_HASH;
					break;
				}
			}

		}
		else
		{
			dwLastError =	NTE_BAD_TYPE;
			break;
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPGetHashParam
 -
 *	Purpose:
 *                Allows applications to get various aspects of the
 *                operations of a hash
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      hHash      -  Handle to a hash
 *               IN      dwParam    -  Parameter number
 *               IN      pbData     -  Pointer to data
 *               IN      pdwDataLen -  Length of parameter data
 *               IN      dwFlags    -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPGetHashParam
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
	IN DWORD dwParam,
	IN BYTE *pbData,
	IN DWORD *pdwDataLen,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPGetHashParam", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	9999;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	DWORD						dwLastError			=	0;

	while (1)
	{
				//	check input parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwDataLen)
	
		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

					//	check if the hash node is valid
		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		switch ( dwParam )
		{
			case	HP_ALGID:
				if ( NULL != pbData )
				{
					if ( 4 > *pdwDataLen )
					{
								//	if enough memory is not allocated then return error
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

						//	copy the algo id and the length of a int in appropriate out params
					memcpy
					(
						pbData,
						(BYTE*) &(pclassHash -> nHashAlgID),
						4
					);
				}

				*pdwDataLen =	4;

				boolSuccessFlag =	TRUE;
				break;

			case	HP_HASHSIZE:
				if ( NULL != pbData )
				{
					if ( 4 > *pdwDataLen )
					{
								//	if enough memory is not allocated then return error
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

						//	copy the length of the hash and the length of a int in appropriate out params
					memcpy
					(
						pbData,
						(BYTE*) &(pclassHash -> dwDataHashLength),
						4
					);
				}

				*pdwDataLen =	4;

				boolSuccessFlag =	TRUE;
				break;

			case	HP_HASHVAL:
				if ( NULL != pbData )
				{
					if ( pclassHash -> dwDataHashLength > *pdwDataLen )
					{
								//	if enough memory is not allocated then return error
						dwLastError =	ERROR_MORE_DATA;
						break;
					}

					if ( VS_TPM_CSP != pCSP -> dwCSPName )
					{

						if ( (HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus) && 
							 (VS_SSL3_SHAMD5 != pclassHash -> nHashAlgID) )
						{
										//	end/close the hash object
							nResult =	HashEnd
										(
											pclassHash -> nHashAlgID,
											pclassHash -> pvoidContext,
											pclassHash -> pbDataHash,
											pclassHash -> dwDataHashLength
										);
							VSCSP_CHECK_NRESULT
						}
									//	and flag the hash object status
						pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CLOSED;

								//	copy the hash and its length in the appropriate out params
						memcpy
						(
							pbData,
							pclassHash -> pbDataHash,
							pclassHash -> dwDataHashLength
						);
						*pdwDataLen =	pclassHash -> dwDataHashLength;
					}
					else 
					{
						BYTE *pbHashData = NULL;
						hResult =	pclassHash -> pVSTSSHash -> GetHashValue
									(
										pdwDataLen, 
										&pbHashData
									);
						VSCSP_CHECK_HRESULT

						memcpy(pbData, pbHashData, *pdwDataLen);
					}
				}
				else 
				{
					*pdwDataLen =	20; 
				}

				
				boolSuccessFlag =	TRUE;
				break;

			default:
				dwLastError =	NTE_BAD_TYPE;
		}

		if ( FALSE == boolSuccessFlag )
		{
				//	there was an error in one of the case blocks. so break;
			break;
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPExportKey
 -
 *	Purpose:
 *                Export cryptographic keys out of a CSP in a secure manner
 *
 *
 *	Parameters:
 *               IN  hProv      - Handle to the CSP user
 *               IN  hKey       - Handle to the key to export
 *               IN  hPubKey    - Handle to the exchange public key value of
 *                                the destination user
 *               IN  dwBlobType - Type of key blob to be exported
 *               IN  dwFlags -    Flags values
 *               OUT pbData -     Key blob data
 *               OUT pdwDataLen - Length of key blob in bytes
 *
 *	Returns:
 */
BOOL WINAPI CPExportKey
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey,
	IN HCRYPTKEY hPubKey,
	IN DWORD dwBlobType,
	IN DWORD dwFlags,
	OUT BYTE *pbData,
	OUT DWORD *pdwDataLen
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPExportKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif
	
	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	
	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;
	CSP_KeyParam*				pclassPubKey		=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	BYTE*						pbyteKey			=	NULL;
	DWORD						dwKeyLen			=	0;
	DWORD						dwLastError			=	0;

	while (1)
	{
				//	check input parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwDataLen)
		
		pCSP			=	(CSP_State*) hProv;
		pclassKey		=	(CSP_KeyParam*) hKey;
		pclassPubKey	=	(CSP_KeyParam*) hPubKey;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		switch ( dwBlobType )
		{
			case	SIMPLEBLOB:

				hResult =	CheckKeyNode
							(
								pCSP,
								pclassPubKey
							);
				VSCSP_CHECK_HRESULT

				hResult =	ExportSessionKey
							(
								pCSP,
								pclassKey,
								pclassPubKey,
								&pbyteKey,
								&dwKeyLen
							);
				VSCSP_CHECK_HRESULT

				boolSuccessFlag	=	TRUE;
				break;

			case	PUBLICKEYBLOB:
				hResult =	ExportPublicKey
							(
								pCSP,
								pclassKey,
								&pbyteKey,
								&dwKeyLen
							);
				VSCSP_CHECK_HRESULT

				boolSuccessFlag	=	TRUE;
				break;

			case	PRIVATEKEYBLOB:
				dwLastError =	E_NOTIMPL;
				break;

//			case	OPAQUEKEYBLOB:
//				::SetLastError (E_NOTIMPL);
//				break;

			default:
				dwLastError =	NTE_BAD_TYPE;
				break;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		if ( NULL == pbData )
		{
			*pdwDataLen = dwKeyLen;
			bResult =	CRYPT_SUCCEED;
			break;
		}
		if ( dwKeyLen > *pdwDataLen )
		{
			*pdwDataLen = dwKeyLen;
			dwLastError =	ERROR_MORE_DATA;
			break;
		}

		memcpy
		(
			(void*) pbData,
			(const void*) pbyteKey,
			dwKeyLen
		);
		*pdwDataLen = dwKeyLen;

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteKey, dwKeyLen)

	::SetLastError ( dwLastError );
	return	bResult;
}


/*
 -	CPImportKey
 -
 *	Purpose:
 *                Import cryptographic keys
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the CSP user
 *               IN  pbData    -  Key blob data
 *               IN  dwDataLen -  Length of the key blob data
 *               IN  hPubKey   -  Handle to the exchange public key value of
 *                                the destination user
 *               IN  dwFlags   -  Flags values
 *               OUT phKey     -  Pointer to the handle to the key which was
 *                                Imported
 *
 *	Returns:
 */
BOOL WINAPI CPImportKey
(
	IN HCRYPTPROV hProv,
	IN CONST BYTE *pbData,
	IN DWORD dwDataLen,
	IN HCRYPTKEY hPubKey,
	IN DWORD dwFlags,
	OUT HCRYPTKEY *phKey
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPImportKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif
	BOOL						bResult						=	CRYPT_FAILED;
	HRESULT						hResult						=	E_FAIL;
	
	CSP_State*					pCSP						=	NULL;
	CSP_KeyParam*				pclassKey					=	NULL;
	CSP_KeyParam*				pclassPubKey				=	NULL;

	BOOL						boolSuccessFlag				=	FALSE;

	BLOBHEADER					structBlobHeader;

	DWORD						dwLastError					=	0;

	while (1)
	{
				//	check input parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (phKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		if ( 0 >= dwDataLen )
		{
			dwLastError =	ERROR_INVALID_PARAMETER;
			break;
		}

		pCSP			=	(CSP_State*) hProv;
//		ppclassKey		=	(CSP_KeyParam**) phKey;
		pclassPubKey	=	(CSP_KeyParam*) hPubKey;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		pclassKey =	new CSP_KeyParam;
		VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey)

		memcpy
		(
			(void*) &structBlobHeader,
			(const void*) pbData,
			sizeof (BLOBHEADER)
		);

/*
		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT
*/

		switch ( structBlobHeader.bType )
		{
			case	SIMPLEBLOB:

				hResult =	CheckKeyNode
							(
								pCSP,
								pclassPubKey
							);
				VSCSP_CHECK_HRESULT

				hResult =	ImportSessionKey
							(
								pCSP,
								pclassPubKey,
								pbData,
								dwDataLen,
								&pclassKey
							);
				VSCSP_CHECK_HRESULT

				boolSuccessFlag	=	TRUE;
				break;

			case	PUBLICKEYBLOB:
				hResult =	ImportPublicKey
							(
								pCSP,
								pbData,
								dwDataLen,
								dwFlags,
								&pclassKey
							);
				VSCSP_CHECK_HRESULT

				boolSuccessFlag	=	TRUE;
				break;

			case	PRIVATEKEYBLOB:
				dwLastError =	E_NOTIMPL;
				break;

//			case	OPAQUEKEYBLOB:
//				::SetLastError (E_NOTIMPL);
//				break;

			default:
				dwLastError =	NTE_BAD_TYPE;
				break;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		hResult =	AddKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		*phKey =	(HCRYPTKEY) pclassKey;

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPEncrypt
 -
 *	Purpose:
 *                Encrypt data
 *
 *
 *	Parameters:
 *               IN  hProv         -  Handle to the CSP user
 *               IN  hKey          -  Handle to the key
 *               IN  hHash         -  Optional handle to a hash
 *               IN  Final         -  Boolean indicating if this is the final
 *                                    block of plaintext
 *               IN  dwFlags       -  Flags values
 *               IN OUT pbData     -  Data to be encrypted
 *               IN OUT pdwDataLen -  Pointer to the length of the data to be
 *                                    encrypted
 *               IN dwBufLen       -  Size of Data buffer
 *
 *	Returns:
 *
 * REV HISTORY
 * Date           Author           Desc
 * ----           ------           ----
 * 04/14/2003     Sasi             Added 3DES encryption support.
 */
BOOL WINAPI CPEncrypt
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey,
	IN HCRYPTHASH hHash,
	IN BOOL Final,
	IN DWORD dwFlags,
	IN OUT BYTE *pbData,
	IN OUT DWORD *pdwDataLen,
	IN DWORD dwBufLen
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPEncrypt", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	DWORD						nResult				=	999;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	CVirtualSmartCard*			pVSmartCard			=	NULL;

	BYTE*						pbyteOutBuffer		=	NULL;
	DWORD						dwOutBufferSize		=	0;
	DWORD						dwOutBufferLen		=	0;	//	used to zero the allocated memory

	DWORD						dwBlockSize			=	0;
	DWORD						dwLastError			=	0;

	BOOL						boolSuccessFlag		=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwDataLen)

		if ( 0 >= *pdwDataLen )
		{
			dwLastError =	NTE_BAD_DATA;
			break;
		}

		pCSP		=	(CSP_State*) hProv;
		pclassKey	=	(CSP_KeyParam*) hKey;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	GetVSC
					(
						pCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		if ( 0 != hHash )
		{
				//	the hashing is optional. so if the hHash = 0 then don't bother about the hash.
			hResult =	CheckHashNode
						(
							pCSP,
							pclassHash
						);
			VSCSP_CHECK_HRESULT

			if ( TRUE == pclassKey -> boolHashEnded )
			{
				dwLastError =	NTE_BAD_HASH_STATE;
				break;
			}

			nResult =	HashData
						(
							pclassHash -> nHashAlgID,
							pclassHash -> pvoidContext,
							pbData,
							*pdwDataLen
						);
			VSCSP_CHECK_NRESULT

			if ( TRUE == Final )
			{
				nResult =	HashEnd
							(
								pclassHash -> nHashAlgID,
								pclassHash -> pvoidContext,
								pclassHash -> pbDataHash,
								pclassHash -> dwDataHashLength
							);
				VSCSP_CHECK_NRESULT

				pclassKey -> boolHashEnded =	TRUE;
			}
		}

		switch ( pclassKey -> dwAlgID )
		{
			case	VS_RSA_KEYX:
			case	VS_RSA_SIGN:
					//	asymmetric encryption
				dwBlockSize =	(pclassKey -> dwKeyLenBits) / 8;	//	the block size is the key length in bytes

				if ( *pdwDataLen % dwBlockSize )
				{
					if ( TRUE == Final )
					{
							//	26 % 8 gives 2 assuming 8 as block size
							//	so it will enter the if condition
							//	the dwOutBufferSize = ((int) 26 / 8 + 1)  * 8
							//						=	(3 + 1) * 8
							//						=	32
						dwOutBufferSize =	( (int) ( *pdwDataLen / dwBlockSize ) + 1 ) * dwBlockSize;
					}
					else
					{
						dwLastError =	NTE_BAD_DATA;
						break;
					}
				}
				else
				{
						//	24 % 8 = 0 so it will enter the else bolck
					dwOutBufferSize =	*pdwDataLen;
				}

				if ( dwOutBufferSize > dwBufLen )
				{
					dwLastError =	NTE_BAD_LEN;
					break;
				}

				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolEncryptionEnded )
				{
					dwLastError =	NTE_BAD_FLAGS;
					break;
				}

				if ( VS_TPM_CSP == pCSP -> dwCSPName )
				{
					if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
						hResult = pCSP->pIPTA->EnterPassword();
						VSCSP_CHECK_HRESULT
					}

					if ( FALSE == pclassKey -> boolEncryptionStarted )
					{
						hResult =	pVSmartCard -> VSTPM_EncryptDecryptBegin
									(
										pclassKey -> pVSTSSKey,
										&(pclassKey -> pVSTSSData)
									);
						VSCSP_CHECK_HRESULT

						pclassKey -> boolEncryptionStarted =	TRUE;
					}

					hResult =	pVSmartCard -> VSTPM_Encrypt
								(
									pclassKey -> pVSTSSData,
									pbData,
									*pdwDataLen,
									pbyteOutBuffer,
									&dwOutBufferSize
								);
					VSCSP_CHECK_HRESULT;

					::memcpy
					(
						(void*) pbData,
						(const void*) pbyteOutBuffer,
						dwOutBufferSize
					);

					*pdwDataLen =	dwOutBufferSize;

					if ( TRUE == Final )
					{
						hResult =	pVSmartCard -> VSTPM_EncryptDecryptEnd
									(
										pclassKey -> pVSTSSData
									);
						VSCSP_CHECK_HRESULT

						pclassKey -> boolEncryptionEnded =	TRUE;
					}
				}
				else
				{
					if ( FALSE == pclassKey -> boolEncryptionStarted )
					{
						nResult =	pVSmartCard -> VSM_EncryptBegin
									( 
										pclassKey -> pbyteCorrPublicKey,
										pclassKey -> dwCorrPublicKeyLen,
										(void**) &(pclassKey -> pvoidRSA_Context)
									);
						VSCSP_CHECK_NRESULT

						pclassKey -> boolEncryptionStarted =	TRUE;
					}

					nResult =	pVSmartCard -> VSM_EncryptUpdate
								(
									(void*) pclassKey -> pvoidRSA_Context,
									Final,
									pbData,
									*pdwDataLen,
									pbyteOutBuffer,
									&dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT;

					::memcpy
					(
						(void*) pbData,
						(const void*) pbyteOutBuffer,
						dwOutBufferSize
					);

					*pdwDataLen =	dwOutBufferSize;

					if ( TRUE == Final )
					{
						nResult =	pVSmartCard -> VSM_EncryptEnd
									(
										(void*) pclassKey -> pvoidRSA_Context
									);
						VSCSP_CHECK_NRESULT

						pclassKey -> boolEncryptionEnded =	TRUE;
					}
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_RC4:
					//	rc4 symmetric encryption
				dwOutBufferSize =	*pdwDataLen;	//	for a stream cipher the out buffer len = in buffer len

				if ( dwOutBufferSize > dwBufLen )
				{
					dwLastError =	NTE_BAD_LEN;
					break;
				}

				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolEncryptionEnded )
				{
					dwLastError =	NTE_BAD_FLAGS;
					break;
				}

				if ( FALSE == pclassKey -> boolEncryptionStarted )
				{
					nResult =	SymEncryptDataBegin
								( 
									pclassKey -> dwAlgID,
									&(pclassKey -> itemKey),
									pclassKey -> dwEffectiveKeyLen,
									(void**) &(pclassKey -> pvoidRC4_Context),
									pclassKey -> pbyteInitVector,
									0
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolEncryptionStarted =	TRUE;
				}

				nResult =	SymEncryptDataUpdate
							(
								(void*) pclassKey -> pvoidRC4_Context,
								pbData,
								*pdwDataLen,
								pbyteOutBuffer,
								(unsigned int*) &dwOutBufferSize
							);
				VSCSP_CHECK_NRESULT;

				::memcpy
				(
					(void*) pbData,
					(const void*) pbyteOutBuffer,
					dwOutBufferSize
				);

				*pdwDataLen =	dwOutBufferSize;

				if ( TRUE == Final )
				{
					nResult =	SymEncryptDataEnd
								(
									(void*) pclassKey -> pvoidRC4_Context,
									pbyteOutBuffer,
									(unsigned int*) &dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolEncryptionEnded =	TRUE;
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_RC2:
					//	rc2 symmetric encryption
				dwBlockSize =	pclassKey -> dwBlockLen / 8;

				if ( FALSE == Final )
				{
					// If not 'Final' then input data length should be a multiple of the
					// block size
					if ( *pdwDataLen % dwBlockSize )
					{
						::SetLastError ( (DWORD) NTE_BAD_DATA );
						break;
					}
					else
						dwOutBufferSize =	*pdwDataLen;
				}
				else
				{
					// If 'Final' is TRUE then output data could be more than the input data
					// because of padding
					dwOutBufferSize =	( (int) ( *pdwDataLen / dwBlockSize ) + 1 ) * dwBlockSize;
				}


				if ( dwOutBufferSize > dwBufLen )
				{
					dwLastError =	NTE_BAD_LEN;
					break;
				}

				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolEncryptionEnded )
				{
					::SetLastError ( (DWORD) NTE_BAD_FLAGS );
					break;
				}

				if ( FALSE == pclassKey -> boolEncryptionStarted )
				{
					nResult =	SymEncryptDataBegin
								(
									pclassKey -> dwAlgID,
									&(pclassKey -> itemKey),
									pclassKey -> dwEffectiveKeyLen,
									(void**) &(pclassKey -> pvoidRC2_Context),
									pclassKey -> pbyteInitVector,
									1	// we will do the padding in the RSA routines
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolEncryptionStarted =	TRUE;
				}

				nResult =	SymEncryptDataUpdate
							(
								(void*) (pclassKey -> pvoidRC2_Context),
								pbData,
								*pdwDataLen,
								pbyteOutBuffer,
								(unsigned int*) &dwOutBufferSize
							);
				VSCSP_CHECK_NRESULT;

				::memcpy
				(
					(void*) pbData,
					(const void*) pbyteOutBuffer,
					dwOutBufferSize
				);

				*pdwDataLen =	dwOutBufferSize;

				if ( TRUE == Final )
				{
					dwOutBufferSize =	( (int) ( *pdwDataLen / dwBlockSize ) + 1 ) * dwBlockSize;

					nResult =	SymEncryptDataEnd
								(
									(void*) (pclassKey -> pvoidRC2_Context),
									pbyteOutBuffer,
									(unsigned int*) &dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT

					::memcpy
					(
						(void*) &(pbData[*pdwDataLen]),
						(const void*) pbyteOutBuffer,
						dwOutBufferSize
					);

					*pdwDataLen += dwOutBufferSize;

					pclassKey -> boolEncryptionEnded =	TRUE;
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_3DES:
					//	3DES symmetric encryption
				dwBlockSize =	pclassKey -> dwBlockLen / 8;

				if ( FALSE == Final )
				{
					// If not 'Final' then input data length should be a multiple of the
					// block size
					if ( *pdwDataLen % dwBlockSize )
					{
						::SetLastError ( (DWORD) NTE_BAD_DATA );
						break;
					}
					else
						dwOutBufferSize =	*pdwDataLen;
				}
				else
				{
					// If 'Final' is TRUE then output data could be more than the input data
					// because of padding
					dwOutBufferSize =	( (int) ( *pdwDataLen / dwBlockSize ) + 1 ) * dwBlockSize;
				}


				if ( dwOutBufferSize > dwBufLen )
				{
					dwLastError =	NTE_BAD_LEN;
					break;
				}

				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolEncryptionEnded )
				{
					::SetLastError ( (DWORD) NTE_BAD_FLAGS );
					break;
				}

				if ( FALSE == pclassKey -> boolEncryptionStarted )
				{
					nResult =	SymEncryptDataBegin
								(
									SYM_3DES,
									&(pclassKey -> itemKey),
									0,
									(void**) &(pclassKey -> pvoid3DES_Context),
									pclassKey -> pbyteInitVector,
									1	// we will do the padding in the RSA routines
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolEncryptionStarted =	TRUE;
				}

				nResult =	SymEncryptDataUpdate
							(
								(void*) (pclassKey -> pvoid3DES_Context),
								pbData,
								*pdwDataLen,
								pbyteOutBuffer,
								(unsigned int*) &dwOutBufferSize
							);
				VSCSP_CHECK_NRESULT;

				::memcpy
				(
					(void*) pbData,
					(const void*) pbyteOutBuffer,
					dwOutBufferSize
				);

				*pdwDataLen =	dwOutBufferSize;

				if ( TRUE == Final )
				{
					dwOutBufferSize =	( (int) ( *pdwDataLen / dwBlockSize ) + 1 ) * dwBlockSize;

					nResult =	SymEncryptDataEnd
								(
									(void*) (pclassKey -> pvoid3DES_Context),
									pbyteOutBuffer,
									(unsigned int*) &dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT

					::memcpy
					(
						(void*) &(pbData[*pdwDataLen]),
						(const void*) pbyteOutBuffer,
						dwOutBufferSize
					);

					*pdwDataLen += dwOutBufferSize;

					pclassKey -> boolEncryptionEnded =	TRUE;
				}

				boolSuccessFlag =	TRUE;
				break;

			default:
				dwLastError =	NTE_BAD_ALGID;
				break;
		}	//	end		switch ( pclassKey -> dwAlgID )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		bResult	=	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteOutBuffer, dwOutBufferLen)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPDecrypt
 -
 *	Purpose:
 *                Decrypt data
 *
 *
 *	Parameters:
 *               IN  hProv         -  Handle to the CSP user
 *               IN  hKey          -  Handle to the key
 *               IN  hHash         -  Optional handle to a hash
 *               IN  Final         -  Boolean indicating if this is the final
 *                                    block of ciphertext
 *               IN  dwFlags       -  Flags values
 *               IN OUT pbData     -  Data to be decrypted
 *               IN OUT pdwDataLen -  Pointer to the length of the data to be
 *                                    decrypted
 *
 *	Returns:
 * REV HISTORY
 * Date           Author           Desc
 * ----           ------           ----
 * 04/14/2003     Sasi             Added 3DES decryption support.
 */
BOOL WINAPI CPDecrypt
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey,
	IN HCRYPTHASH hHash,
	IN BOOL Final,
	IN DWORD dwFlags,
	IN OUT BYTE *pbData,
	IN OUT DWORD *pdwDataLen
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPDecrypt", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	DWORD						nResult				=	999;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	CVirtualSmartCard*			pVSmartCard			=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	DWORD						dwOutBufferSize		=	0;
	DWORD						dwBlockSize			=	0;
	DWORD						dwTotalDecrLen		=	0;

	DWORD						dwPadLen			=	0;
	DWORD						dwLastError			=	0;

	BYTE*						pbyteOutBuffer		=	NULL;
	DWORD						dwOutBufferLen		=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwDataLen)

		if ( 0 >= *pdwDataLen )
		{
			dwLastError =	NTE_BAD_DATA;
			break;
		}

		pCSP		=	(CSP_State*) hProv;
		pclassKey	=	(CSP_KeyParam*) hKey;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		if ( FALSE == pCSP -> bPvtKeyAccess )
		{
			::SetLastError ( (DWORD) NTE_PERM );
			break;
		}
			
		hResult =	GetVSC
					(
						pCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		switch ( pclassKey -> dwAlgID )
		{
			case	VS_RSA_KEYX:
			case	VS_RSA_SIGN:
					//	asymmetric encryption
				dwBlockSize =	(pclassKey -> dwKeyLenBits) / 8;	//	the block size is the key length in bytes

				if ( *pdwDataLen % dwBlockSize )
				{
					if ( TRUE == Final )
					{
							//	26 % 8 gives 2 assuming 8 as block size
							//	so it will enter the if condition
							//	the dwOutBufferSize = ((int) 26 / 8 + 1)  * 8
							//						=	(3 + 1) * 8
							//						=	32
						dwOutBufferSize =	( (int) ( *pdwDataLen / dwBlockSize ) + 1 ) * dwBlockSize;
					}
					else
					{
						dwLastError =	NTE_BAD_DATA;
						break;
					}
				}
				else
				{
						//	24 % 8 = 0 so it will enter the else bolck
					dwOutBufferSize =	*pdwDataLen;
				}

				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolDecryptionEnded )
				{
					dwLastError =	NTE_BAD_FLAGS;
					break;
				}

				if ( VS_TPM_CSP == pCSP -> dwCSPName )
				{
					if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
						hResult = pCSP->pIPTA->EnterPassword();
						VSCSP_CHECK_HRESULT
					}
	
					if ( FALSE == pclassKey -> boolEncryptionStarted )
					{
						hResult =	pVSmartCard -> VSTPM_EncryptDecryptBegin
									(
										pclassKey -> pVSTSSKey,
										&(pclassKey -> pVSTSSData)
									);
						VSCSP_CHECK_HRESULT

						pclassKey -> boolDecryptionStarted =	TRUE;
					}

					hResult =	pVSmartCard -> VSTPM_Decrypt
								(
									pclassKey -> pVSTSSData,
									pbData,
									*pdwDataLen,
									pbyteOutBuffer,
									&dwOutBufferSize
								);
					VSCSP_CHECK_HRESULT;

					::memcpy
					(
						(void*) pbData,
						(const void*) pbyteOutBuffer,
						dwOutBufferSize
					);

					*pdwDataLen =	dwOutBufferSize;

					if ( TRUE == Final )
					{
						hResult =	pVSmartCard -> VSTPM_EncryptDecryptEnd
									(
										pclassKey -> pVSTSSData
									);
						VSCSP_CHECK_HRESULT

						pclassKey -> boolDecryptionEnded =	TRUE;
					}
				}
				else
				{
					if ( FALSE == pclassKey -> boolDecryptionStarted )
					{
						nResult =	pVSmartCard -> VSM_DecryptBegin
									( 
										pclassKey -> pbyteCorrPublicKey,
										pclassKey -> dwCorrPublicKeyLen,
										(void**) &(pclassKey -> pvoidRSA_Context)
									);
						VSCSP_CHECK_NRESULT

						pclassKey -> boolDecryptionStarted =	TRUE;
					}

					nResult =	pVSmartCard -> VSM_DecryptUpdate
								(
									(void*) pclassKey -> pvoidRSA_Context,
									Final,
									pbData,
									*pdwDataLen,
									pbyteOutBuffer,
									&dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT;

					::memcpy
					(
						(void*) pbData,
						(const void*) pbyteOutBuffer,
						dwOutBufferSize
					);

					*pdwDataLen =	dwOutBufferSize;

					if ( TRUE == Final )
					{
						nResult =	pVSmartCard -> VSM_DecryptEnd
									(
										(void*) pclassKey -> pvoidRSA_Context
									);
						VSCSP_CHECK_NRESULT

						pclassKey -> boolDecryptionEnded =	TRUE;
					}
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_RC4:
					//	rc4 symmetric decryption
				dwOutBufferSize =	*pdwDataLen;	//	for a stream cipher the out buffer len = in buffer len

				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolDecryptionEnded )
				{
					dwLastError =	NTE_BAD_FLAGS;
					break;
				}

				if ( FALSE == pclassKey -> boolDecryptionStarted )
				{
					nResult =	SymDecryptDataBegin
								( 
									pclassKey -> dwAlgID,
									&(pclassKey -> itemKey),
									0,
									(void**) &(pclassKey -> pvoidRC4_Context),
									pclassKey -> pbyteInitVector,
									0
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolDecryptionStarted =	TRUE;
				}

				nResult =	SymDecryptDataUpdate
							(
								(void*) pclassKey -> pvoidRC4_Context,
								pbData,
								*pdwDataLen,
								pbyteOutBuffer,
								(unsigned int*) &dwOutBufferSize
							);
				VSCSP_CHECK_NRESULT;

				::memcpy
				(
					(void*) pbData,
					(const void*) pbyteOutBuffer,
					dwOutBufferSize
				);

				*pdwDataLen =	dwOutBufferSize;

				if ( TRUE == Final )
				{
					nResult =	SymDecryptDataEnd
								(
									(void*) pclassKey -> pvoidRC4_Context,
									pbyteOutBuffer,
									(unsigned int*) &dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolDecryptionEnded =	TRUE;
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_RC2:
					//	rc2 symmetric decryption
				dwBlockSize =	pclassKey -> dwBlockLen / 8;
				dwOutBufferSize = *pdwDataLen;

				if ( dwOutBufferSize % dwBlockSize )
				{
					dwLastError = NTE_BAD_DATA;
					break;
				}


				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolDecryptionEnded )
				{
					dwLastError =	NTE_BAD_FLAGS;
					break;
				}

				if ( FALSE == pclassKey -> boolDecryptionStarted )
				{
					nResult =	SymDecryptDataBegin
								( 
									pclassKey -> dwAlgID,
									&(pclassKey -> itemKey),
									pclassKey -> dwEffectiveKeyLen,
									(void**) &(pclassKey -> pvoidRC2_Context),
									pclassKey -> pbyteInitVector,
									0	// we will remove the padding
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolDecryptionStarted =	TRUE;
				}

				nResult =	SymDecryptDataUpdate
							(
								(void*) (pclassKey -> pvoidRC2_Context),
								pbData,
								*pdwDataLen,
								pbyteOutBuffer,
								(unsigned int*) &dwOutBufferSize
							);
				VSCSP_CHECK_NRESULT;

				dwTotalDecrLen =	dwOutBufferSize;
				dwOutBufferSize =	*pdwDataLen - dwOutBufferSize;

				if ( TRUE == Final )
				{
					nResult =	SymDecryptDataEnd
								(
									(void*) (pclassKey -> pvoidRC2_Context),
									pbyteOutBuffer + dwTotalDecrLen,
									(unsigned int*) &dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT
					dwTotalDecrLen += dwOutBufferSize;

					if ( 0 == dwOutBufferSize )
					{
						// Remove the padding here as SymDecryptDataEnd() did not return any
						// data and SymDecryptDataUpdate() did not remove the padding
						if ((dwPadLen = pbyteOutBuffer[dwTotalDecrLen - 1]) == 0 || dwPadLen > 8)
						{ 
							dwLastError =	NTE_BAD_DATA;
							break;
						}

						for (DWORD i = dwTotalDecrLen - dwPadLen; i < dwTotalDecrLen; i++) 
						{
							if ( pbyteOutBuffer[i] != dwPadLen )
							{ 
								dwLastError =	NTE_BAD_DATA;
								break;
							}
						}

						dwTotalDecrLen -=	dwPadLen;
					}

					pclassKey -> boolDecryptionEnded =	TRUE;
				}

				if ( dwTotalDecrLen > *pdwDataLen )
				{
					dwLastError =	NTE_BAD_LEN;
					*pdwDataLen = dwTotalDecrLen;
					break;
				}

				::memcpy
				(
					(void*) pbData,
					(const void*) pbyteOutBuffer,
					dwTotalDecrLen
				);

				*pdwDataLen = dwTotalDecrLen;

				boolSuccessFlag =	TRUE;
				break;

			case	VS_3DES:
					//	3DES symmetric decryption
				dwBlockSize =	pclassKey -> dwBlockLen / 8;
				dwOutBufferSize = *pdwDataLen;

				if ( dwOutBufferSize % dwBlockSize )
				{
					dwLastError = NTE_BAD_DATA;
					break;
				}


				pbyteOutBuffer =	new BYTE [dwOutBufferSize];
				VSCSP_CHECK_ALLOCATED_MEMORY (pbyteOutBuffer)
				dwOutBufferLen =	dwOutBufferSize;

				if ( TRUE ==	pclassKey -> boolDecryptionEnded )
				{
					dwLastError =	NTE_BAD_FLAGS;
					break;
				}

				if ( FALSE == pclassKey -> boolDecryptionStarted )
				{
					nResult =	SymDecryptDataBegin
								( 
									SYM_3DES,
									&(pclassKey -> itemKey),
									0,
									(void**) &(pclassKey -> pvoid3DES_Context),
									pclassKey -> pbyteInitVector,
									0	// we will remove the padding
								);
					VSCSP_CHECK_NRESULT

					pclassKey -> boolDecryptionStarted =	TRUE;
				}

				nResult =	SymDecryptDataUpdate
							(
								(void*) (pclassKey -> pvoid3DES_Context),
								pbData,
								*pdwDataLen,
								pbyteOutBuffer,
								(unsigned int*) &dwOutBufferSize
							);
				VSCSP_CHECK_NRESULT;

				dwTotalDecrLen =	dwOutBufferSize;
				dwOutBufferSize =	*pdwDataLen - dwOutBufferSize;

				if ( TRUE == Final )
				{
					nResult =	SymDecryptDataEnd
								(
									(void*) (pclassKey -> pvoid3DES_Context),
									pbyteOutBuffer + dwTotalDecrLen,
									(unsigned int*) &dwOutBufferSize
								);
					VSCSP_CHECK_NRESULT
					dwTotalDecrLen += dwOutBufferSize;

					if ( 0 == dwOutBufferSize )
					{
						// Remove the padding here as SymDecryptDataEnd() did not return any
						// data and SymDecryptDataUpdate() did not remove the padding
						if ((dwPadLen = pbyteOutBuffer[dwTotalDecrLen - 1]) == 0 || dwPadLen > 8)
						{ 
							dwLastError =	NTE_BAD_DATA;
							break;
						}

						for (DWORD i = dwTotalDecrLen - dwPadLen; i < dwTotalDecrLen; i++) 
						{
							if ( pbyteOutBuffer[i] != dwPadLen )
							{ 
								dwLastError =	NTE_BAD_DATA;
								break;
							}
						}

						dwTotalDecrLen -=	dwPadLen;
					}

					pclassKey -> boolDecryptionEnded =	TRUE;
				}

				if ( dwTotalDecrLen > *pdwDataLen )
				{
					dwLastError =	NTE_BAD_LEN;
					*pdwDataLen = dwTotalDecrLen;
					break;
				}

				::memcpy
				(
					(void*) pbData,
					(const void*) pbyteOutBuffer,
					dwTotalDecrLen
				);

				*pdwDataLen = dwTotalDecrLen;

				boolSuccessFlag =	TRUE;
				break;

			default:
				dwLastError =	NTE_BAD_ALGID;
				break;
		}	//	end		switch ( pclassKey -> dwAlgID )
		

		if( TRUE == boolSuccessFlag )
			bResult =	CRYPT_SUCCEED;
		else
			bResult =	CRYPT_FAILED;

		break;
	}	//	end		while (1)


	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteOutBuffer, dwOutBufferLen)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPCreateHash
 -
 *	Purpose:
 *                initate the hashing of a stream of data
 *
 *
 *	Parameters:
 *               IN  hUID    -  Handle to the user identifcation
 *               IN  Algid   -  Algorithm identifier of the hash algorithm
 *                              to be used
 *               IN  hKey    -  Optional key for MAC algorithms
 *               IN  dwFlags -  Flags values
 *               OUT pHash   -  Handle to hash object
 *
 *	Returns:
 *
 * REV HISTORY
 * Date           Author           Desc
 * ----           ------           ----
 * 04/14/2003     Sasi             Added support for CALG_SSL3_SHAMD5 hash algorithm used in native SSL client auth.
 * 05/06/2003	  Ajay			   Added support for CALG_SSL3_SHAMD5 in tpm csp
 */
BOOL WINAPI CPCreateHash
(
	IN HCRYPTPROV hProv,
	IN int Algid,
	IN HCRYPTKEY hKey,
	IN DWORD dwFlags,
	OUT HCRYPTHASH *phHash
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPCreateHash", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	DWORD						nResult				=	9999;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;
	CVirtualSmartCard*			pVSmartCard			=	NULL;

	DWORD						dwAlgID				=	0;
	DWORD						dwLastError			=	0;

	while (1)
	{
				//	check parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (phHash)
		if ( 0 != dwFlags )
		{
			dwLastError =	E_INVALIDARG;
			break;
		}
		// support CALG_SSL3_SHAMD5 for SSL client auth
		if ( (CALG_SHA1 != Algid) && (CALG_MD5 != Algid) 
			&& (CALG_MD2 != Algid) && (CALG_SSL3_SHAMD5 != Algid) )
		{
			dwLastError =	E_INVALIDARG;
			break;
		}

		VSCSP_SWITCH_ALGOS

		pCSP =	(CSP_State*) hProv;
		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		if ( VS_TPM_CSP == pCSP -> dwCSPName )
		{
				//	the TPM CSP will support only SHA1
				//	this is because the TPM/TSS supports SHA1 and can sign 
				//  CALG_SSL3_SHAMD5 (36 byte hash)
			if ( (CALG_SHA1 != Algid) && (CALG_SSL3_SHAMD5 != Algid) )
			{
				dwLastError =	E_INVALIDARG;
				break;
			}
		
			hResult =	GetVSC
			(
				pCSP,
				&pVSmartCard
			);
			VSCSP_CHECK_HRESULT
		}
		
		pclassHash =	new ( CSP_HashParam );
		VSCSP_CHECK_ALLOCATED_MEMORY ( pclassHash )


				//	set the algo ID in the structure
		pclassHash -> nHashAlgID =	dwAlgID;

		if ( VS_TPM_CSP == pCSP -> dwCSPName )
		{
			hResult =	pVSmartCard -> VSTPM_CreateHashObject
						(
							&(pclassHash -> pVSTSSHash)
						);
			VSCSP_CHECK_HRESULT
		}
		else
		{
			// for SSL client auth the hash object which is a 
			// concatenation of the SHA and MD5 hashes is passed to
			// us by the schannel.dll. This dll itself does the hashing
			// we are just supposed to sign it, so we support CALG_SSL3_SHAMD5
			// only in the form of setting the hash value in CPSetHashParam()
			// and not creating the hash ourselves.
			if ( CALG_SSL3_SHAMD5 != Algid  )
			{
				nResult =	HashBegin
							(
								dwAlgID,
								&(pclassHash -> pvoidContext)
							);
				VSCSP_CHECK_NRESULT
			}
			else
				pclassHash -> pvoidContext =	NULL;

		}

				//	allocate memory for the HASH.
		switch ( pclassHash -> nHashAlgID )
		{
			case	VS_SHA_1:
				pclassHash -> dwDataHashLength =	HASH_SHA1_LENGTH;
				break;

			case	VS_MD5:
				pclassHash -> dwDataHashLength =	HASH_MD5_LENGTH;
				break;

			case	VS_MD2:
				pclassHash -> dwDataHashLength =	HASH_MD2_LENGTH;
				break;
			case	VS_SSL3_SHAMD5 :
				pclassHash -> dwDataHashLength =	HASH_SSL3_SHAMD5;
				break;
		}

		pclassHash -> pbDataHash =	new BYTE [ pclassHash -> dwDataHashLength ];
		VSCSP_CHECK_ALLOCATED_MEMORY ( pclassHash -> dwDataHashLength )

		pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CREATED;

				//	add the hash structure to the list. this is part of a CSP context
		hResult =	AddHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT


				//	the pointer to the hash param class is the handle to the hash object
		*phHash =	(HCRYPTHASH) pclassHash;
		
		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPHashData
 -
 *	Purpose:
 *                Compute the cryptograghic hash on a stream of data
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the user identifcation
 *               IN  hHash     -  Handle to hash object
 *               IN  pbData    -  Pointer to data to be hashed
 *               IN  dwDataLen -  Length of the data to be hashed
 *               IN  dwFlags   -  Flags values
 *               IN  pdwMaxLen -  Maximum length of the data stream the CSP
 *                                module may handle
 *
 *	Returns:
 */
BOOL WINAPI CPHashData
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
	IN CONST BYTE *pbData,
	IN DWORD dwDataLen,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPHashData", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	9999;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;
	CVirtualSmartCard*			pVSmartCard			=	NULL;

	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbData)
		if ( 0 == dwDataLen )
		{
			dwLastError =	E_INVALIDARG;
			break;
		}

		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		// we don't support direct creation of CALG_SSL3_SHAMD5
		if ( VS_SSL3_SHAMD5 == pclassHash -> nHashAlgID )
		{
			dwLastError =	NTE_BAD_ALGID;
			break;
		}

		if ( HASH_OBJECT_CREATED != pclassHash -> dwHashObjectStatus )
		{
			dwLastError =	NTE_BAD_HASH_STATE;
			break;
		}

		if ( VS_TPM_CSP == pCSP -> dwCSPName )
		{
			hResult =	GetVSC
			(
				pCSP,
				&pVSmartCard
			);
			VSCSP_CHECK_HRESULT

			void *pvoidContext;

			nResult =	HashBegin
						(
							HASH_SHA1,
							&(pvoidContext)
						);
			VSCSP_CHECK_NRESULT

			nResult =	HashData
						(
							HASH_SHA1,
							pvoidContext,
							(BYTE*) pbData,
							dwDataLen
						);
			VSCSP_CHECK_NRESULT

			BYTE *pbDataHash = new BYTE[20];
			DWORD dwDataHashLength = 20;
			nResult =	HashEnd
						(
							HASH_SHA1,
							pvoidContext,
							pbDataHash,
							dwDataHashLength
						);
			VSCSP_CHECK_NRESULT

			pclassHash -> pVSTSSHash->SetHashValue(dwDataHashLength, pbDataHash);

/*
			hResult =	pVSmartCard -> VSTPM_HashData
						(
							pclassHash -> pVSTSSHash,
							dwDataLen,
							(BYTE*) pbData
						);
			VSCSP_CHECK_HRESULT
*/
		}
		else
		{
			nResult =	HashData
						(
							pclassHash -> nHashAlgID,
							pclassHash -> pvoidContext,
							(BYTE*) pbData,
							dwDataLen
						);
			VSCSP_CHECK_NRESULT
		}

		pclassHash -> dwIsEmpty = 0;

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPHashSessionKey
 -
 *	Purpose:
 *                Compute the cryptograghic hash on a key object.
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the user identifcation
 *               IN  hHash     -  Handle to hash object
 *               IN  hKey      -  Handle to a key object
 *               IN  dwFlags   -  Flags values
 *
 *	Returns:
 *               CRYPT_FAILED
 *               CRYPT_SUCCEED
 */
BOOL WINAPI CPHashSessionKey
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
	IN HCRYPTKEY hKey,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPHashSessionKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	BYTE*						pbyteKey			=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	DWORD						dwKeyLen			=	0;
	DWORD						dwLastError			=	0;
	DWORD						i;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hKey)

		pCSP		=	(CSP_State*) hProv;
		pclassKey	=	(CSP_KeyParam*) hKey;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		// we don't support direct creation of CALG_SSL3_SHAMD5
		if ( VS_SSL3_SHAMD5 == pclassHash -> nHashAlgID )
		{
			dwLastError =	NTE_BAD_ALGID;
			break;
		}

		dwKeyLen =	(pclassKey -> itemKey).len;

		pbyteKey =	(BYTE*) new BYTE [dwKeyLen];
		VSCSP_CHECK_ALLOCATED_MEMORY (pbyteKey)

		switch ( dwFlags )
		{
			case	0:
				for ( i = 0; i < dwKeyLen; i++ )
				{
					pbyteKey [i] =	(pclassKey -> itemKey).data [(dwKeyLen - 1) - i];
				}

				boolSuccessFlag =	TRUE;
				break;

			case	CRYPT_LITTLE_ENDIAN:
				::memcpy
				(
					(void*) pbyteKey,
					(const void*) (pclassKey -> itemKey).data,
					dwKeyLen
				);

				boolSuccessFlag =	TRUE;
				break;

			default:
				dwLastError =	NTE_BAD_FLAGS;
				break;
		}	//	end		switch ( dwFlags )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		bResult =	CPHashData
					(
						hProv,
						hHash,
						pbyteKey,
						dwKeyLen,
						0
					);
		if ( FALSE == bResult )
		{
			break;
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteKey, dwKeyLen)

	::SetLastError ( dwLastError );
    return	bResult;
}

/*
 -	CPDestoryHash
 -
 *	Purpose:
 *                Destory the hash object
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the user identifcation
 *               IN  hHash     -  Handle to hash object
 *
 *	Returns:
 */
BOOL WINAPI CPDestroyHash
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPDestroyHash", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	9999;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	BYTE*						pbDataHash			=	NULL;
	DWORD						dwDataHashLength	=	0;
	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)

		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		hResult =	DeleteHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


/*
 -	CPSignHash
 -
 *	Purpose:
 *                Create a digital signature from a hash
 *
 *
 *	Parameters:
 *               IN  hProv        -  Handle to the user identifcation
 *               IN  hHash        -  Handle to hash object
 *               IN  Algid        -  Algorithm identifier of the signature
 *                                   algorithm to be used
 *               IN  sDescription -  Description of data to be signed
 *               IN  dwFlags      -  Flags values
 *               OUT pbSignture   -  Pointer to signature data
 *               OUT dwHashLen    -  Pointer to the len of the signature data
 *
 *	Returns:
 */
BOOL WINAPI CPSignHash
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
	IN DWORD dwKeySpec,
	IN LPCWSTR sDescription,	//	must be NULL
	IN DWORD dwFlags,
	OUT BYTE *pbSignature,
	OUT DWORD *pdwSigLen
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPSignHash", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	9999;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;

	CVirtualSmartCard*			pVSmartCard			=	NULL;

	BYTE*						pbyteRev			=	NULL;
	BYTE*						pbyteCorrPublicKey	=	NULL;
	DWORD						dwCorrPublicKeyLen	=	0;
	DWORD						dwLastError			=	0;

	BOOL						boolSuccessFlag		=	FALSE;
	DWORD						dwAlgID				=	999;
	DWORD						Algid				=	999;

	while (1)
	{
			//	check input parameters
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbSignature)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pdwSigLen)


		if ( 0 != dwFlags && CRYPT_NOHASHOID != dwFlags)
		{
			dwLastError =	NTE_BAD_FLAGS;
			break;
		}

		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		if ( FALSE == pCSP -> bPvtKeyAccess )
		{
			dwLastError =	NTE_PERM;
			break;
		}

		hResult =	GetVSC
					(
						pCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT

					//	check if the HCRYPTHASH provided is valid
		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		if ( VS_TPM_CSP == pCSP -> dwCSPName )
		{
					//	the macro uses Algid and dwAlgID
					//	hence the dwKeySpec is put into Algid and then the macro is called
			Algid =	dwKeySpec;
			VSCSP_SWITCH_ALGOS

			if (_gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
				hResult = pCSP->pIPTA->EnterPassword();
				VSCSP_CHECK_HRESULT
			}

			hResult =	pVSmartCard -> VSTPM_SignHash
						(
							pclassHash -> pVSTSSHash,
							dwAlgID,
							pbSignature,
							pdwSigLen
						);
			VSCSP_CHECK_HRESULT
		}
		else
		{
			switch ( dwKeySpec )
			{
				case	AT_KEYEXCHANGE:
					if ( NULL == pCSP -> pbyteCorrXchgPublicKey )
					{
						dwLastError =	NTE_NO_KEY;
						break;
					}

					pbyteCorrPublicKey =	pCSP -> pbyteCorrXchgPublicKey;
					dwCorrPublicKeyLen =	pCSP -> dwCorrXchgPublicKeyLen;

					boolSuccessFlag =	TRUE;
					break;

				case	AT_SIGNATURE:
					if ( NULL == pCSP -> pbyteCorrSignPublicKey )
					{
						dwLastError =	NTE_NO_KEY;
						break;
					}

					pbyteCorrPublicKey =	pCSP -> pbyteCorrSignPublicKey;
					dwCorrPublicKeyLen =	pCSP -> dwCorrSignPublicKeyLen;

					boolSuccessFlag =	TRUE;
					break;

				default:
					dwLastError =	ERROR_INVALID_PARAMETER;
					break;
			}	//	end		switch ( dwKeySpec )

			if ( FALSE == boolSuccessFlag )
			{
				break;
			}

						//	check if the HCRYPTHASH provided is valid
			hResult =	CheckHashNode
						(
							pCSP,
							pclassHash
						);
			VSCSP_CHECK_HRESULT

					//	if the hash object is not already closed then call hashend and close the object
					//
					//	this check is a MUST because first time this function (cpsignhash) is called
					//	to detect the length of the output data.
					//  We shouldn't call HashEnd for VS_SSL3_SHAMD5 since we don't create this hash. In this case
					//  the hash value is passed to us through CPSetHashParam
			if ( (HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus) &&
				 (VS_SSL3_SHAMD5 != pclassHash -> nHashAlgID) )
			{
				nResult =	HashEnd
							(
								pclassHash -> nHashAlgID,
								pclassHash -> pvoidContext,
								pclassHash -> pbDataHash,
								pclassHash -> dwDataHashLength
							);
				VSCSP_CHECK_NRESULT

				pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CLOSED;
			}

				// Always check to make sure hash object is closed. In case of VS_SSL3_SHAMD5, 
				// we close the object after the hash value is set in CPSetHashParam
			if ( HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus )
			{
				dwLastError =	NTE_BAD_HASH;
				break;
			}

			hResult =	pVSmartCard -> VSM_SignData
						(
							pbyteCorrPublicKey,
							dwCorrPublicKeyLen,
							pclassHash -> pbDataHash,
							pclassHash -> dwDataHashLength,
							pclassHash -> nHashAlgID,
							TRUE,
							pbSignature,
							pdwSigLen,
							dwFlags
						);
			VSCSP_CHECK_HRESULT
		}

		if ( NULL != pbSignature )
		{
			pbyteRev = new BYTE [*pdwSigLen];
			memcpy
			(
				pbyteRev,
				pbSignature,
				*pdwSigLen
			);

			for ( DWORD x = 0; x < *pdwSigLen; x++ )
			{
				pbSignature [x] = pbyteRev [*pdwSigLen - 1 - x];
			}
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_AND_DELETE ( pbyteRev )

	::SetLastError ( dwLastError );
    return	bResult;
}

/*
 -	CPVerifySignature
 -
 *	Purpose:
 *                Used to verify a signature against a hash object
 *
 *
 *	Parameters:
 *               IN  hProv        -  Handle to the user identifcation
 *               IN  hHash        -  Handle to hash object
 *               IN  pbSignture   -  Pointer to signature data
 *               IN  dwSigLen     -  Length of the signature data
 *               IN  hPubKey      -  Handle to the public key for verifying
 *                                   the signature
 *               IN  Algid        -  Algorithm identifier of the signature
 *                                   algorithm to be used
 *               IN  sDescription -  Description of data to be signed
 *               IN  dwFlags      -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPVerifySignature
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
	IN CONST BYTE *pbSignature,
	IN DWORD dwSigLen,
	IN HCRYPTKEY hPubKey,
	IN LPCWSTR sDescription,
	IN DWORD dwFlags
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPVerifySignature", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	DWORD						nResult				=	999;

	CSP_State*					pCSP				=	NULL;
	CSP_HashParam*				pclassHash			=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;

	CVirtualSmartCard*			pVSmartCard			=	NULL;

	DWORD						dwLastError			=	0;
	BYTE*						pbyteRev			=	NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hPubKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbSignature)
		if ( 0 != dwFlags  && CRYPT_NOHASHOID != dwFlags  )
		{
			dwLastError =	NTE_BAD_FLAGS;
			break;
		}

		pCSP		=	(CSP_State*) hProv;
		pclassHash	=	(CSP_HashParam*) hHash;
		pclassKey	=	(CSP_KeyParam*) hPubKey;

		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT


		hResult =	GetVSC
					(
						pCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT

		hResult =	CheckKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

					//	check if the HCRYPTHASH provided is valid
		hResult =	CheckHashNode
					(
						pCSP,
						pclassHash
					);
		VSCSP_CHECK_HRESULT

		if ( NULL != pbSignature && 0 <  dwSigLen )
		{
			pbyteRev = new BYTE [dwSigLen];

			VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbyteRev)

			for ( DWORD x = 0; x < dwSigLen; x++ )
			{
				pbyteRev [x] = pbSignature  [dwSigLen - 1 - x];
			}
		} 
		else
		{
			dwLastError =	NTE_BAD_SIGNATURE;
			break;
		}

		if ( VS_TPM_CSP == pCSP -> dwCSPName )
		{
			if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
				hResult = pCSP->pIPTA->EnterPassword();
				VSCSP_CHECK_HRESULT
			}

			hResult =	pVSmartCard -> VSTPM_VerifySignature
						(
							pclassHash -> pVSTSSHash,
							pclassKey -> pVSTSSKey,
							pbyteRev,
							dwSigLen
						);
			VSCSP_CHECK_HRESULT

		}
		else
		{
					//  We shouldn't call HashEnd for VS_SSL3_SHAMD5 since we don't create this hash. In this case
					//  the hash value is passed to us through CPSetHashParam
			if ( (HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus) && 
				 (VS_SSL3_SHAMD5 != pclassHash -> nHashAlgID) )
			{
				nResult =	HashEnd
							(
								pclassHash -> nHashAlgID,
								pclassHash -> pvoidContext,
								pclassHash -> pbDataHash,
								pclassHash -> dwDataHashLength
							);
				VSCSP_CHECK_NRESULT

				pclassHash -> dwHashObjectStatus =	HASH_OBJECT_CLOSED;
			}

				// Always check to make sure hash object is closed. In case of VS_SSL3_SHAMD5, 
				// we close the object after the hash value is set in CPSetHashParam
			if ( HASH_OBJECT_CLOSED != pclassHash -> dwHashObjectStatus )
			{
				dwLastError =	NTE_BAD_HASH;
				break;
			}

			hResult =	pVSmartCard -> VSM_VerifyData
						(
							pclassKey -> pbyteCorrPublicKey,
							pclassKey -> dwCorrPublicKeyLen,
							pclassHash -> pbDataHash,
							pclassHash -> dwDataHashLength,
							pclassHash -> nHashAlgID,
							TRUE,
							pbyteRev,
							dwSigLen,
							dwFlags
						);
			VSCSP_CHECK_HRESULT
		}

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	while (1)

	VSCSP_CHECK_FOR_NULL_AND_DELETE ( pbyteRev )

	::SetLastError ( dwLastError );
    return	bResult;
}



/*
 -	CPGenRandom
 -
 *	Purpose:
 *                Used to fill a buffer with random bytes
 *
 *
 *	Parameters:
 *               IN  hProv      -  Handle to the user identifcation
 *               OUT pbBuffer   -  Pointer to the buffer where the random
 *                                 bytes are to be placed
 *               IN  dwLen      -  Number of bytes of random data requested
 *
 *	Returns:
 */
BOOL WINAPI CPGenRandom
(
	IN HCRYPTPROV hProv,
	IN DWORD dwLen,
	IN OUT BYTE *pbBuffer
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPGenRandom", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;
	DWORD						nResult				=	999;

	CSP_State*					pCSP				=	NULL;

	DWORD						dwLastError			=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (pbBuffer)
		if ( 0 >= dwLen )
		{
			dwLastError =	NTE_FAIL;
			break;
		}

		pCSP =	( CSP_State* ) hProv;
		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT

		nResult =	GenerateRandomBlock ( pbBuffer, dwLen );
		VSCSP_CHECK_NRESULT

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}

/*
 -	CPGetUserKey
 -
 *	Purpose:
 *                Gets a handle to a permanent user key
 *
 *
 *	Parameters:
 *               IN  hProv      -  Handle to the user identifcation
 *               IN  dwKeySpec  -  Specification of the key to retrieve
 *               OUT phUserKey  -  Pointer to key handle of retrieved key
 *
 *	Returns:
 */
BOOL WINAPI CPGetUserKey
(
	IN HCRYPTPROV hProv,
	IN DWORD dwKeySpec,
	OUT HCRYPTKEY *phUserKey
)
{
#ifdef	_VS_MSG_BOX_
	MessageBox ( NULL, (LPCTSTR) "CPGetUserKey", (LPCTSTR) "VeriSign CSP", MB_OK );
#endif

	BOOL						bResult				=	CRYPT_FAILED;
	HRESULT						hResult				=	E_FAIL;

	CSP_State*					pCSP				=	NULL;
	CSP_KeyParam*				pclassKey			=	NULL;

	CVirtualSmartCard*			pVSmartCard			=	NULL;

	BOOL						boolSuccessFlag		=	FALSE;

	DWORD						dwAlgID				=	999;
	DWORD						Algid				=	999;
	DWORD						dwLastError			=	0;
	BYTE*						pbModulus			=   NULL;
	DWORD						dwModulusLen		=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (hProv)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (phUserKey)

		pCSP =	( CSP_State* ) hProv;
		hResult =	CheckProv ( pCSP );
		VSCSP_CHECK_HRESULT


		hResult =	GetVSC
					(
						pCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT

			//	create a new instance of the key class
		pclassKey =	new (CSP_KeyParam);
		VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey)

		switch ( dwKeySpec )
		{
			case	AT_KEYEXCHANGE:
				pclassKey -> dwAlgID =	VS_RSA_KEYX;

				boolSuccessFlag =	TRUE;
				break;

			case	AT_SIGNATURE:
				pclassKey -> dwAlgID =	VS_RSA_SIGN;

				boolSuccessFlag =	TRUE;
				break;

			default:
				dwLastError =	ERROR_INVALID_PARAMETER;
				break;
		}	//	end		switch ( dwKeySpec )
		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		if ( VS_TPM_CSP == pCSP -> dwCSPName )
		{
			// Ajay - Check is not required, it is done by VSTPM_GetKey
			/*
			if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
				pCSP->pIPTA->EnterPassword();
			}
			*/
				
			hResult =	pVSmartCard -> VSTPM_GetKey
						(
							pclassKey -> dwAlgID,
							&(pclassKey -> dwKeyLenBits),
							&(pclassKey -> dwExportable),
							&(pclassKey -> pVSTSSKey)
						);
			VSCSP_CHECK_HRESULT
		}
		else
		{

			hResult =	pVSmartCard -> VSM_GetUserKeyHandle
						(
							pCSP -> pszNameOfContainer,
							pclassKey -> dwAlgID,
							&(pclassKey -> dwKeyLenBits),
							&(pclassKey -> dwExportable),
							NULL,
							&(pclassKey -> dwCorrPublicKeyLen)
						);
			VSCSP_CHECK_HRESULT

			pclassKey -> pbyteCorrPublicKey =	new BYTE [pclassKey -> dwCorrPublicKeyLen];
			VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteCorrPublicKey)

			hResult =	pVSmartCard -> VSM_GetUserKeyHandle
						(
							pCSP -> pszNameOfContainer,
							pclassKey -> dwAlgID,
							&(pclassKey -> dwKeyLenBits),
							&(pclassKey -> dwExportable),
							pclassKey -> pbyteCorrPublicKey,
							&(pclassKey -> dwCorrPublicKeyLen)
						);
			VSCSP_CHECK_HRESULT
		}

		pclassKey -> dwBlockLen				=	VS_CSP_DEFAULT_BLOCK_LENGTH;
		pclassKey -> dwCypherModes			=	VS_CSP_DEFAULT_CYPHER_MODES;
		pclassKey -> dwModeBits				=	0;

		pclassKey -> dwPermissions			=	CRYPT_DECRYPT | CRYPT_ENCRYPT | CRYPT_EXPORT | CRYPT_READ | CRYPT_WRITE;

		pclassKey -> dwInitVectorLength		=	VS_CSP_DEFAULT_BLOCK_LENGTH / 8;
		pclassKey -> pbyteInitVector =	new BYTE [pclassKey -> dwInitVectorLength];
		VSCSP_CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteInitVector)
		::memcpy
		(
			(void*) pclassKey -> pbyteInitVector,
			(const void*) VS_CSP_DEFAULT_INIT_VECTOR,
			VS_CSP_DEFAULT_BLOCK_LENGTH / 8
		);

//		if ( CRYPT_CREATE_SALT | dwLowerFlags )
//		{
//			pclassKey -> dwSaltLength =	11;
//				//	TBD: generate a random number and copy it in
//				//	pclassKey -> pbyteSalt
//		}
//		else
//		{
			pclassKey -> dwSaltLength =	0;
//		}

		pclassKey -> dwPadding				=	PKCS5_PADDING;

				//	add the key structure to the list. this is part of a CSP context
		hResult =	AddKeyNode
					(
						pCSP,
						pclassKey
					);
		VSCSP_CHECK_HRESULT

		if ( VS_TPM_CSP != pCSP -> dwCSPName )
		{
					//	the macro uses Algid and dwAlgID
					//	hence the dwKeySpec is put into Algid and then the macro is called
			Algid =	dwKeySpec;
			VSCSP_SWITCH_ALGOS

			boolSuccessFlag =	FALSE;
			switch ( dwAlgID )
			{
				case	VS_RSA_KEYX:
					pCSP -> dwCorrXchgPublicKeyLen =	pclassKey -> dwCorrPublicKeyLen;
					pCSP -> pbyteCorrXchgPublicKey =	new BYTE [pCSP -> dwCorrXchgPublicKeyLen];
					VSCSP_CHECK_ALLOCATED_MEMORY (pCSP -> pbyteCorrXchgPublicKey)

					memcpy
					(
						(void*) pCSP -> pbyteCorrXchgPublicKey,
						(const void*) pclassKey -> pbyteCorrPublicKey,
						pCSP -> dwCorrXchgPublicKeyLen
					);
								
					boolSuccessFlag =	TRUE;
					break;

				case	VS_RSA_SIGN:
					pCSP -> dwCorrSignPublicKeyLen =	pclassKey -> dwCorrPublicKeyLen;
					pCSP -> pbyteCorrSignPublicKey =	new BYTE [pCSP -> dwCorrSignPublicKeyLen];
					VSCSP_CHECK_ALLOCATED_MEMORY (pCSP -> pbyteCorrSignPublicKey)

					memcpy
					(
						(void*) pCSP -> pbyteCorrSignPublicKey,
						(const void*) pclassKey -> pbyteCorrPublicKey,
						pCSP -> dwCorrSignPublicKeyLen
					);

					boolSuccessFlag =	TRUE;
					break;

				default:
					hResult =	NTE_BAD_FLAGS;
					break;
			}	//	end		switch ( dwAlgID )
			if ( FALSE == boolSuccessFlag )
			{
				break;
			}
		}
				//	the pointer to the key param class is the handle to the key object
		*phUserKey =	(HCRYPTKEY) pclassKey;

		bResult =	CRYPT_SUCCEED;
		break;
	}	//	end		while (1)

	::SetLastError ( dwLastError );
    return	bResult;
}


void InitCSPGlobalVars ()
{
	g_phProv =	NULL;

		//	initialize the algo enum structures
	g_AlgoInfo.pEnumAlgs[0].aiAlgid				=	VS_RC2;
	g_AlgoInfo.pEnumAlgs[0].dwBitLen			=	128;
	g_AlgoInfo.pEnumAlgs[0].dwNameLen			=	4;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[0].szName, "RC2");

	g_AlgoInfo.pEnumAlgs[1].aiAlgid				=	VS_RC4;
	g_AlgoInfo.pEnumAlgs[1].dwBitLen			=	128;
	g_AlgoInfo.pEnumAlgs[1].dwNameLen			=	4;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[1].szName, "RC4");

	g_AlgoInfo.pEnumAlgs[2].aiAlgid				=	VS_SHA_1;
	g_AlgoInfo.pEnumAlgs[2].dwBitLen			=	160;
	g_AlgoInfo.pEnumAlgs[2].dwNameLen			=	6;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[2].szName, "SHA-1");

	g_AlgoInfo.pEnumAlgs[3].aiAlgid				=	VS_MD2;
	g_AlgoInfo.pEnumAlgs[3].dwBitLen			=	128;
	g_AlgoInfo.pEnumAlgs[3].dwNameLen			=	4;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[3].szName, "MD2");

	g_AlgoInfo.pEnumAlgs[4].aiAlgid				=	VS_MD5;
	g_AlgoInfo.pEnumAlgs[4].dwBitLen			=	128;
	g_AlgoInfo.pEnumAlgs[4].dwNameLen			=	4;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[4].szName, "MD5");

	g_AlgoInfo.pEnumAlgs[5].aiAlgid				=	VS_RSA_SIGN;
	g_AlgoInfo.pEnumAlgs[5].dwBitLen			=	1024;
	g_AlgoInfo.pEnumAlgs[5].dwNameLen			=	9;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[5].szName, "RSA_SIGN");

	g_AlgoInfo.pEnumAlgs[6].aiAlgid				=	VS_RSA_KEYX;
	g_AlgoInfo.pEnumAlgs[6].dwBitLen			=	1024;
	g_AlgoInfo.pEnumAlgs[6].dwNameLen			=	9;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[6].szName, "RSA_KEYX");

		// added 3DES to the list of supported algorithms
	g_AlgoInfo.pEnumAlgs[7].aiAlgid				=	VS_3DES;
	g_AlgoInfo.pEnumAlgs[7].dwBitLen			=	168;
	g_AlgoInfo.pEnumAlgs[7].dwNameLen			=	5;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[7].szName, "3DES");

/*
	g_AlgoInfo.pEnumAlgs[7].aiAlgid				=	CALG_DES;
	g_AlgoInfo.pEnumAlgs[7].dwBitLen			=	26113;
	g_AlgoInfo.pEnumAlgs[7].dwNameLen			=	4;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[7].szName, "DES");

	g_AlgoInfo.pEnumAlgs[8].aiAlgid				=	CALG_3DES;
	g_AlgoInfo.pEnumAlgs[8].dwBitLen			=	26115;
	g_AlgoInfo.pEnumAlgs[8].dwNameLen			=	5;
	::lstrcpy (g_AlgoInfo.pEnumAlgs[8].szName, "3DES");
*/

	g_AlgoInfo.nIndex							=	0;


		//	initialize the extended algo enum structure
	g_ExAlgoInfo.pEnumAlgsEx[0].aiAlgid			=	VS_RC2;
	g_ExAlgoInfo.pEnumAlgsEx[0].dwDefaultLen	=	128;
	g_ExAlgoInfo.pEnumAlgsEx[0].dwMinLen		=	40;
	g_ExAlgoInfo.pEnumAlgsEx[0].dwMaxLen		=	128;
	g_ExAlgoInfo.pEnumAlgsEx[0].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[0].dwNameLen		=	4;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[0].szName, "RC2");
	g_ExAlgoInfo.pEnumAlgsEx[0].dwLongNameLen	=	24;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[0].szLongName, "RSA Data Security's RC2");

	g_ExAlgoInfo.pEnumAlgsEx[1].aiAlgid			=	VS_RC4;
	g_ExAlgoInfo.pEnumAlgsEx[1].dwDefaultLen	=	128;
	g_ExAlgoInfo.pEnumAlgsEx[1].dwMinLen		=	40;
	g_ExAlgoInfo.pEnumAlgsEx[1].dwMaxLen		=	128;
	g_ExAlgoInfo.pEnumAlgsEx[1].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[1].dwNameLen		=	4;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[1].szName, "RC4");
	g_ExAlgoInfo.pEnumAlgsEx[1].dwLongNameLen	=	24;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[1].szLongName, "RSA Data Security's RC4");

	g_ExAlgoInfo.pEnumAlgsEx[2].aiAlgid			=	VS_SHA_1;
	g_ExAlgoInfo.pEnumAlgsEx[2].dwDefaultLen	=	160;
	g_ExAlgoInfo.pEnumAlgsEx[2].dwMinLen		=	160;
	g_ExAlgoInfo.pEnumAlgsEx[2].dwMaxLen		=	160;
	g_ExAlgoInfo.pEnumAlgsEx[2].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[2].dwNameLen		=	6;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[2].szName, "SHA-1");
	g_ExAlgoInfo.pEnumAlgsEx[2].dwLongNameLen	=	30;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[2].szLongName, "Secure Hash Algorithm (SHA-1)");

	g_ExAlgoInfo.pEnumAlgsEx[3].aiAlgid			=	VS_MD2;
	g_ExAlgoInfo.pEnumAlgsEx[3].dwDefaultLen	=	128;
	g_ExAlgoInfo.pEnumAlgsEx[3].dwMinLen		=	128;
	g_ExAlgoInfo.pEnumAlgsEx[3].dwMaxLen		=	128;
	g_ExAlgoInfo.pEnumAlgsEx[3].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[3].dwNameLen		=	4;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[3].szName, "MD2");
	g_ExAlgoInfo.pEnumAlgsEx[3].dwLongNameLen	=	23;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[3].szLongName, "Message Digest 2 (MD2)");

	g_ExAlgoInfo.pEnumAlgsEx[4].aiAlgid			=	VS_MD5;
	g_ExAlgoInfo.pEnumAlgsEx[4].dwDefaultLen	=	128;
	g_ExAlgoInfo.pEnumAlgsEx[4].dwMinLen		=	128;
	g_ExAlgoInfo.pEnumAlgsEx[4].dwMaxLen		=	128;
	g_ExAlgoInfo.pEnumAlgsEx[4].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[4].dwNameLen		=	4;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[4].szName, "MD5");
	g_ExAlgoInfo.pEnumAlgsEx[4].dwLongNameLen	=	23;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[4].szLongName, "Message Digest 5 (MD5)");

	g_ExAlgoInfo.pEnumAlgsEx[5].aiAlgid			=	VS_RSA_SIGN;
	g_ExAlgoInfo.pEnumAlgsEx[5].dwDefaultLen	=	1024;
	g_ExAlgoInfo.pEnumAlgsEx[5].dwMinLen		=	384;
	g_ExAlgoInfo.pEnumAlgsEx[5].dwMaxLen		=	16384;
	g_ExAlgoInfo.pEnumAlgsEx[5].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[5].dwNameLen		=	9;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[5].szName, "RSA_SIGN");
	g_ExAlgoInfo.pEnumAlgsEx[5].dwLongNameLen	=	14;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[5].szLongName, "RSA Signature");

	g_ExAlgoInfo.pEnumAlgsEx[6].aiAlgid			=	VS_RSA_KEYX;
	g_ExAlgoInfo.pEnumAlgsEx[6].dwDefaultLen	=	1024;
	g_ExAlgoInfo.pEnumAlgsEx[6].dwMinLen		=	384;
	g_ExAlgoInfo.pEnumAlgsEx[6].dwMaxLen		=	16384;
	g_ExAlgoInfo.pEnumAlgsEx[6].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[6].dwNameLen		=	9;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[6].szName, "RSA_KEYX");
	g_ExAlgoInfo.pEnumAlgsEx[6].dwLongNameLen	=	17;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[6].szLongName, "RSA Key Exchange");


		// added 3DES to the list of supported algorithms
	g_ExAlgoInfo.pEnumAlgsEx[7].aiAlgid			=	VS_3DES;
	g_ExAlgoInfo.pEnumAlgsEx[7].dwDefaultLen	=	168;
	g_ExAlgoInfo.pEnumAlgsEx[7].dwMinLen		=	168;
	g_ExAlgoInfo.pEnumAlgsEx[7].dwMaxLen		=	168;
	g_ExAlgoInfo.pEnumAlgsEx[7].dwProtocols		=	0;
	g_ExAlgoInfo.pEnumAlgsEx[7].dwNameLen		=	5;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[7].szName, "3DES");
	g_ExAlgoInfo.pEnumAlgsEx[7].dwLongNameLen	=	21;
	::lstrcpy (g_ExAlgoInfo.pEnumAlgsEx[7].szLongName, "Three Key Triple DES");

	g_ExAlgoInfo.nIndex							=	0;

	////////	do the same for TPM algo structures

		//	initialize the algo enum structures
	g_TPM_AlgoInfo.pEnumAlgs[0].aiAlgid				=	VS_RC2;
	g_TPM_AlgoInfo.pEnumAlgs[0].dwBitLen			=	128;
	g_TPM_AlgoInfo.pEnumAlgs[0].dwNameLen			=	4;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[0].szName, "RC2");

	g_TPM_AlgoInfo.pEnumAlgs[1].aiAlgid				=	VS_RC4;
	g_TPM_AlgoInfo.pEnumAlgs[1].dwBitLen			=	128;
	g_TPM_AlgoInfo.pEnumAlgs[1].dwNameLen			=	4;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[1].szName, "RC4");

	g_TPM_AlgoInfo.pEnumAlgs[2].aiAlgid				=	VS_SHA_1;
	g_TPM_AlgoInfo.pEnumAlgs[2].dwBitLen			=	160;
	g_TPM_AlgoInfo.pEnumAlgs[2].dwNameLen			=	6;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[2].szName, "SHA-1");

	g_TPM_AlgoInfo.pEnumAlgs[3].aiAlgid				=	VS_RSA_SIGN;
	g_TPM_AlgoInfo.pEnumAlgs[3].dwBitLen			=	1024;
	g_TPM_AlgoInfo.pEnumAlgs[3].dwNameLen			=	9;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[3].szName, "RSA_SIGN");

	g_TPM_AlgoInfo.pEnumAlgs[4].aiAlgid				=	VS_RSA_KEYX;
	g_TPM_AlgoInfo.pEnumAlgs[4].dwBitLen			=	1024;
	g_TPM_AlgoInfo.pEnumAlgs[4].dwNameLen			=	9;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[4].szName, "RSA_KEYX");

/*
	g_TPM_AlgoInfo.pEnumAlgs[7].aiAlgid				=	CALG_DES;
	g_TPM_AlgoInfo.pEnumAlgs[7].dwBitLen			=	26113;
	g_TPM_AlgoInfo.pEnumAlgs[7].dwNameLen			=	4;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[7].szName, "DES");

	g_TPM_AlgoInfo.pEnumAlgs[8].aiAlgid				=	CALG_3DES;
	g_TPM_AlgoInfo.pEnumAlgs[8].dwBitLen			=	26115;
	g_TPM_AlgoInfo.pEnumAlgs[8].dwNameLen			=	5;
	::lstrcpy (g_TPM_AlgoInfo.pEnumAlgs[8].szName, "3DES");
*/

	g_TPM_AlgoInfo.nIndex							=	0;


		//	initialize the extended algo enum structure
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].aiAlgid			=	VS_RC2;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].dwDefaultLen	=	128;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].dwMinLen		=	40;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].dwMaxLen		=	128;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].dwProtocols		=	0;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].dwNameLen		=	4;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[0].szName, "RC2");
	g_TPM_ExAlgoInfo.pEnumAlgsEx[0].dwLongNameLen	=	24;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[0].szLongName, "RSA Data Security's RC2");

	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].aiAlgid			=	VS_RC4;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].dwDefaultLen	=	128;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].dwMinLen		=	40;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].dwMaxLen		=	128;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].dwProtocols		=	0;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].dwNameLen		=	4;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[1].szName, "RC4");
	g_TPM_ExAlgoInfo.pEnumAlgsEx[1].dwLongNameLen	=	24;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[1].szLongName, "RSA Data Security's RC4");

	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].aiAlgid			=	VS_SHA_1;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].dwDefaultLen	=	160;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].dwMinLen		=	160;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].dwMaxLen		=	160;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].dwProtocols		=	0;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].dwNameLen		=	6;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[2].szName, "SHA-1");
	g_TPM_ExAlgoInfo.pEnumAlgsEx[2].dwLongNameLen	=	30;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[2].szLongName, "Secure Hash Algorithm (SHA-1)");

	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].aiAlgid			=	VS_RSA_SIGN;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].dwDefaultLen	=	1024;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].dwMinLen		=	384;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].dwMaxLen		=	16384;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].dwProtocols		=	0;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].dwNameLen		=	9;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[3].szName, "RSA_SIGN");
	g_TPM_ExAlgoInfo.pEnumAlgsEx[3].dwLongNameLen	=	14;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[3].szLongName, "RSA Signature");

	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].aiAlgid			=	VS_RSA_KEYX;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].dwDefaultLen	=	1024;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].dwMinLen		=	384;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].dwMaxLen		=	16384;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].dwProtocols		=	0;
	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].dwNameLen		=	9;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[4].szName, "RSA_KEYX");
	g_TPM_ExAlgoInfo.pEnumAlgsEx[4].dwLongNameLen	=	17;
	::lstrcpy (g_TPM_ExAlgoInfo.pEnumAlgsEx[4].szLongName, "RSA Key Exchange");

	g_TPM_ExAlgoInfo.nIndex							=	0;

    return;
}
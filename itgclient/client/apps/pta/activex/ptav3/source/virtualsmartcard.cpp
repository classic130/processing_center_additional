// Storage.cpp: implementation of the CStorage class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "..\Include\virtualsmartcard.h"

#include "..\Include\keycontainer.h"
#include "..\Include\VSCSP_Macros.h"
#include "..\Include\cspglobals.h"
#include "..\Include\csputil.h"



#define		LOG_FILE		"c:\\temp\\ptalog.log"
void LogFunc(const BYTE* i_pcbyteData, const DWORD i_cdwDataLength);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVirtualSmartCard::CVirtualSmartCard()  
{
	m_pPasswordCallback =	NULL;
	m_pvoidObjectPTA	=	NULL;
	pProtectedStorage = NULL;
	pPTAProtectedStorage = NULL;
	pEncPTAProtectedStorage = NULL;
	boolUsePS = NULL;

	m_tbstrAppCtxtName = "";
	m_tbstrHostName = "";
	m_tbstrCurrentHostName = "";
	m_tbstrProfileOpenHostWildCard = "";
	m_tbstrTPMKeyPassword = "";
	m_tbstrPassword = "";
	m_tbstrProfileIssFrndlyName = "";
	bstrProfName = "";
	m_boolRoaming =	FALSE;
	m_SessionHandle = 0;
//	m_ppbyteStorage = new BYTE* [1]; 
	m_pbyteStorage	=	NULL;
	pbstrReadOKDomains = NULL;
	pbstrWriteOKDomains = NULL;
	nNumOfReadOKDomains = 0;
	nNumOfWriteOKDomains = 0;
	m_dwStorageLen	=	0;
	m_dwStorageChanged = 0;
	
	m_hModAdvapiDll = NULL;
	lpfnRegOpenCurrentUser = NULL;
	m_hCurrUserKey = HKEY_CURRENT_USER;

#ifdef VS_TSSDLL
	m_hModTSSDll = NULL;
	lpfnCreateContextObject = NULL;
	lpfnCreateDataObject = NULL;
	lpfnCreateHashObject = NULL;
	lpfnCreateKeyObjectURK = NULL;
	lpfnCreateKeyObjectULK = NULL;
	lpfnCreateKeyObjectLoadUK = NULL;
	lpfnCreateKeyObjectImportPublicKey = NULL;

#endif // VS_TSSDLL
	m_dwIsTPM = 0;
	m_dwTSSVendor = IBM_TSS;

	// Sasi 05/06/03
	// Initialize variables used to store info reqd for new roaming profiles
	m_boolResetPasswdFeature = FALSE;
	m_tbstrSecretQuestion = "";
	m_tbstrSecretAnswer = "";

	m_tbstrFirstName = "";
	m_tbstrLastName = "";
	m_tbstrEmail = "";


#ifdef _DEBUG
	VSRM_SetLogFunction(LogFunc);
#endif
	m_boolRoamingNameReserved =	FALSE;
}

CVirtualSmartCard::~CVirtualSmartCard()
{
	if(boolUsePS && m_boolRoaming == FALSE)
 	{
 		VSM_Close();
 	}
 
	if( HKEY_CURRENT_USER != m_hCurrUserKey)
	{
		RegCloseKey (m_hCurrUserKey);
	}

	if(NULL != m_hModAdvapiDll)
	{
		::FreeLibrary(m_hModAdvapiDll);
	}
#ifdef VS_TSSDLL
	if(NULL != m_hModTSSDll)
	{
		::FreeLibrary(m_hModTSSDll);
	}
#endif // VS_TSSDLL
	
 
	VSPTA_CLEAN_TBSTR(m_tbstrSecretQuestion);
	VSPTA_CLEAN_TBSTR(m_tbstrSecretAnswer);
	VSPTA_CLEAN_TBSTR(m_tbstrFirstName);
	VSPTA_CLEAN_TBSTR(m_tbstrLastName);
	VSPTA_CLEAN_TBSTR(m_tbstrEmail);

	/*
	if(pProtectedStorage)
		pProtectedStorage->Close();
	delete pProtectedStorage;
	if(pPTAProtectedStorage)
		pPTAProtectedStorage->Close();
	delete pPTAProtectedStorage;
	*/
}


HRESULT CVirtualSmartCard::VSM_Initialize(VARIANT* i_pvarWhichSmartCard, VARIANT* i_pvarPassword, 
		VARIANT* i_pvarAppCtxt, VARIANT* i_pvarProfileIssFrndlyName, VARIANT* i_pvarAppHostName,
		VARIANT* i_pvarPasswdTimeOut, VARIANT* i_pvarPasswdLockOutTries, VARIANT* i_pvarPasswdUnLockPeriod,
		FN_PasswordCallback* i_pPasswordCallback, void* i_pObjectPTA)
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal;
	BOOL boolProtectedStorageOpen = FALSE;
	BOOL boolPTAProtectedStorageOpen = FALSE;
	BOOL boolEncPTAProtectedStorageOpen = FALSE;

	BOOL boolWriteCalled = FALSE;

	_bstr_t		tbstrUserName = "";
	_bstr_t		tbstrProfileIssUniqueID = "";
	_bstr_t		tbstrClientInfo;
	_bstr_t		tbstrClientInfoSig;

	WCHAR**		pwszRoamingServers = NULL;
	VSRM_STATUS	vsrmStatus;
	VSRM_PASSWORD	vsrmPassword;
	//VSRM_ITEM     vsrmItemStorageServerID;
    VSRM_ITEM**    ppvsrmItemRoamingServerIDList =	NULL;
	//VSRM_ITEM		vsrmItemData;
	VSRM_USERNAME_STATUS	vsrmUserNameStatus =	VSRM_USERNAME_STATUS_UNKNOWN;

	if ( (NULL == i_pPasswordCallback) || (NULL == i_pObjectPTA) )
	{
		return	E_FAIL;
	}
	m_pPasswordCallback =	i_pPasswordCallback;
	m_pvoidObjectPTA	=	i_pObjectPTA;

	/*ROAMING - Obtain the name of the file to be opened if it is a vt_bstr. If it is a vt_array, then obtain the 
	profile name, the roaming servers and the storage server- mark the remote/local flag*/
	if ( (VT_ARRAY|VT_VARIANT) == i_pvarWhichSmartCard -> vt )
	{
		m_boolRoaming =	TRUE;

		
		retVal =	GetServersFromArray
					(
						i_pvarWhichSmartCard,
						&tbstrClientInfo,
						&tbstrClientInfoSig,
						&tbstrUserName,
						&tbstrProfileIssUniqueID
					);

		// Sasi 05/06/03
		// Check if roaming profiles are managed by new roaming server that supports password reset feature
		if(S_OK == retVal)
		{
			BOOL bResetPasswd;
			retVal = VSM_IsResetPasswdSupported(tbstrClientInfo, tbstrClientInfoSig, &bResetPasswd);
		}

	}

	_bstr_t tbstrDummyHostName(DUMMY_HOSTNAME);

	if ( S_OK == retVal )
	{
		pProtectedStorage = new CProtectedStorage;

		if ( FALSE == m_boolRoaming )
		{
			/* Create a protected storage with the given filename, application name, application host name,
			password, and password timeout value
			 - this is an encrypted application*/
			longRetVal = pProtectedStorage->Initialize((_VS_CHAR*)i_pvarAppCtxt->bstrVal,(_VS_CHAR*)i_pvarAppHostName->bstrVal,APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
				TRUE,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_CREATE,(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
				i_pvarPasswdTimeOut->iVal,SetPasswdFn, (void*) this);
		}
		else
		{
			/*ROAMING - If the profile is create the protected storage in memory*/
			longRetVal =	pProtectedStorage -> InitializeForRoaming
							(
								(_VS_CHAR*)i_pvarAppCtxt->bstrVal,
								(_VS_CHAR*)i_pvarAppHostName->bstrVal,
								APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
								TRUE,
								tbstrUserName,
								&m_pbyteStorage,
								(unsigned int*) &m_dwStorageLen,
								(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
								i_pvarPasswdTimeOut->iVal,
								SetPasswdFn,
								(void*) this,
								m_boolResetPasswdFeature
							);
		}
	}	//	end		if ( S_OK == retVal )

	if(longRetVal == VS_SUCCESS)
	{
		boolProtectedStorageOpen = TRUE;

		/*Add the PTA application to this profile. This application will be used to 
		store meta data*/
		_bstr_t tbstrPTAAppCtxtName(PTA_APPCTXT_NAME);
		longRetVal = pProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS,BEGINWRITE_BLOCK_PERIOD);
		if(longRetVal == VS_SUCCESS)
		{
			boolWriteCalled = TRUE;
			longRetVal = pProtectedStorage->AddApplicationToDB((_VS_CHAR*)tbstrPTAAppCtxtName,(_VS_CHAR*)tbstrDummyHostName,APPLICATION_DECRYPTED);
//			longRetVal = pProtectedStorage->EndWrite();
		}

		/*Add the Encrypted PTA application to this profile. This application will be used to 
		store meta data*/
		_bstr_t tbstrEncPTAAppCtxtName(PTA_ENC_APPCTXT_NAME);
		if (longRetVal == VS_SUCCESS)
		{
			longRetVal = pProtectedStorage->AddApplicationToDB((_VS_CHAR *)tbstrEncPTAAppCtxtName, (_VS_CHAR *)tbstrDummyHostName, APPLICATION_ENCRYPTED);
		}

		if (longRetVal == VS_SUCCESS)
		{
			longRetVal = pProtectedStorage->AddApplicationToDB((_VS_CHAR *)i_pvarAppCtxt->bstrVal,
															(_VS_CHAR*)i_pvarAppHostName->bstrVal,
															APPLICATION_ENCRYPTED);
		}

		if (boolWriteCalled == TRUE)
		{
			pProtectedStorage->EndWrite();
			boolWriteCalled = FALSE;
		}

		if(longRetVal == VS_SUCCESS)
		{
			//Close the profile so that the created applications are flushed to the file
			//ROAMING - If remote then call the memory close
			if ( TRUE == m_boolRoaming )
			{
				longRetVal =	pProtectedStorage -> CloseForRoaming
								(
									(unsigned int*) &m_dwStorageChanged
								);

				if ( VS_SUCCESS == longRetVal )
				{
					boolProtectedStorageOpen = FALSE;

						//	now reinit the Protected Storage
					longRetVal =	pProtectedStorage -> InitializeForRoaming
					(
						(_VS_CHAR*)i_pvarAppCtxt->bstrVal,
						(_VS_CHAR*)i_pvarAppHostName->bstrVal,
						APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
						TRUE,
						tbstrUserName,
						&m_pbyteStorage,
						(unsigned int*) &m_dwStorageLen,
						(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
						i_pvarPasswdTimeOut->iVal,
						SetPasswdFn,
						(void*) this,
						m_boolResetPasswdFeature
					);
					if(longRetVal == VS_SUCCESS)
					{
						boolProtectedStorageOpen = TRUE;

						//Create the pta protected storage object and init it
						pPTAProtectedStorage = new CProtectedStorage;

						longRetVal =	pPTAProtectedStorage -> InitializeForRoaming
										(
											(_VS_CHAR*)tbstrPTAAppCtxtName,
											(_VS_CHAR*)tbstrDummyHostName,
											APPLICATION_DECRYPTED,
											FALSE,
											tbstrUserName,
											&m_pbyteStorage,
											(unsigned int*) &m_dwStorageLen,
											NULL,
											i_pvarPasswdTimeOut->iVal,
											SetPasswdFn,
											(void*) this,
											m_boolResetPasswdFeature
										);
						if(longRetVal == VS_SUCCESS)
						{
							boolPTAProtectedStorageOpen = TRUE;
							
							// Create the Encrypted PTA protected storage object and init it.
							pEncPTAProtectedStorage = new CProtectedStorage;
	
							longRetVal =	pEncPTAProtectedStorage -> InitializeForRoaming
											(
												(_VS_CHAR*)tbstrEncPTAAppCtxtName,
												(_VS_CHAR*)tbstrDummyHostName,
												APPLICATION_ENCRYPTED,
												FALSE,
												tbstrUserName,
												&m_pbyteStorage,
												(unsigned int*) &m_dwStorageLen,
												(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
												i_pvarPasswdTimeOut->iVal,
												SetPasswdFn,
												(void*) this,
												m_boolResetPasswdFeature
											);
							if(longRetVal == VS_SUCCESS)
							{
								boolEncPTAProtectedStorageOpen = TRUE;
							}
						}
					}
				}
			}
			else
			{
				if((longRetVal = pProtectedStorage->Close() ) == VS_SUCCESS)
				{
					boolProtectedStorageOpen = FALSE;

					//Now reinit the protected storage objects for the application and the pta
					longRetVal = pProtectedStorage->Initialize((_VS_CHAR*)i_pvarAppCtxt->bstrVal,(_VS_CHAR*)i_pvarAppHostName->bstrVal,APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
						FALSE,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
						i_pvarPasswdTimeOut->iVal,SetPasswdFn, (void*) this);
					//MessageBox(NULL, "Step 1", NULL,MB_OK);
					if(longRetVal == VS_SUCCESS)
					{
						boolProtectedStorageOpen = TRUE;

						//Create the pta protected storage object and init it
						pPTAProtectedStorage = new CProtectedStorage;
						longRetVal = pPTAProtectedStorage->Initialize((_VS_CHAR*)tbstrPTAAppCtxtName,(_VS_CHAR*)tbstrDummyHostName,APPLICATION_DECRYPTED,
							FALSE,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,NULL,
							i_pvarPasswdTimeOut->iVal,SetPasswdFn, (void*) this);
						if(longRetVal == VS_SUCCESS)
						{
							boolPTAProtectedStorageOpen = TRUE;

							//Create the encrypted pta protected storage object and init it
							pEncPTAProtectedStorage = new CProtectedStorage;
							longRetVal = pEncPTAProtectedStorage->Initialize((_VS_CHAR*)tbstrEncPTAAppCtxtName,(_VS_CHAR*)tbstrDummyHostName,APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
								FALSE,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
								i_pvarPasswdTimeOut->iVal,SetPasswdFn, (void*) this);
							if (longRetVal == VS_SUCCESS)
							{
								boolEncPTAProtectedStorageOpen = TRUE;
							}
						}
						
					}


				}
			}


		}

//		VSPTA_CLEAN_TBSTR(tbstrPTAAppCtxtName)
	}

	/*Store the lock out tries, unlock period and password timeout in the application specific protected
	storage*/
	_bstr_t tbstrAppPrefName = "";
	if(longRetVal == VS_SUCCESS)
	{

		tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
		longRetVal = pEncPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		if (longRetVal == VS_SUCCESS)
		{
			boolWriteCalled = TRUE;
			longRetVal = pEncPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(i_pvarPasswdLockOutTries->iVal)),
				sizeof(i_pvarPasswdLockOutTries->iVal), 0);
		}
	}
	if(longRetVal == VS_SUCCESS)
	{
		tbstrAppPrefName = UNLOCK_PERIOD_NAME;
		longRetVal = pEncPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(i_pvarPasswdUnLockPeriod->iVal)),
			sizeof(i_pvarPasswdUnLockPeriod->iVal), 0);
	}
	if(longRetVal == VS_SUCCESS)
	{
		tbstrAppPrefName = TIMEOUT_PERIOD_NAME;
		longRetVal = pEncPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(i_pvarPasswdTimeOut->iVal)),
			sizeof(i_pvarPasswdTimeOut->iVal), 0);
	}
	if (longRetVal == VS_SUCCESS)
	{
		_bstr_t tbstrAllDomains = _bstr_t("*,");
		longRetVal = pEncPTAProtectedStorage->SetApplicationReadOKDomains(1, (_VS_BYTE *)(_VS_CHAR *)tbstrAllDomains, 2*SysStringLen((BSTR)tbstrAllDomains));
	}
	if (longRetVal == VS_SUCCESS)
	{
		_bstr_t tbstrAllDomains = _bstr_t("*,");
		longRetVal = pEncPTAProtectedStorage->SetApplicationWriteOKDomains(1, (_VS_BYTE *)(_VS_CHAR *)tbstrAllDomains, 2*SysStringLen((BSTR)tbstrAllDomains));
	}
	if (boolWriteCalled == TRUE)
	{
		pEncPTAProtectedStorage->EndWrite();
		boolWriteCalled = FALSE;
	}

	/*Store the lock out tries, unlock period, number of invalid tries and the
	timeout period in the pta protected	storage*/
	if(longRetVal == VS_SUCCESS)
	{
		tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
		pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(i_pvarPasswdLockOutTries->iVal)),
			sizeof(i_pvarPasswdLockOutTries->iVal), 0);
		if(longRetVal == VS_SUCCESS)
		{
			tbstrAppPrefName = UNLOCK_PERIOD_NAME;
			longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(i_pvarPasswdUnLockPeriod->iVal)),
				sizeof(i_pvarPasswdUnLockPeriod->iVal), 0);
			if(longRetVal == VS_SUCCESS)
			{
				int nNumOfInvalidTries = 0;
				tbstrAppPrefName = INVALID_TRIES_NAME;
				longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&nNumOfInvalidTries),
					sizeof(nNumOfInvalidTries), 0);
				if(longRetVal == VS_SUCCESS)
				{
					FILETIME ftLastInvalidTry ;
					GetSystemTimeAsFileTime(&ftLastInvalidTry);
					tbstrAppPrefName = LAST_INVALIDTRY_NAME;
					longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&ftLastInvalidTry),
						sizeof(ftLastInvalidTry), 0);
					if(longRetVal == VS_SUCCESS)
					{
						tbstrAppPrefName = TIMEOUT_PERIOD_NAME;
						longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(i_pvarPasswdTimeOut->iVal)),
							sizeof(i_pvarPasswdTimeOut->iVal), 0);
					}
				}
			}
		}
		pPTAProtectedStorage->EndWrite();
	}

	/*If this is a roaming profile, then upload it*/
	if(longRetVal == VS_SUCCESS)
	{
		if ( TRUE == m_boolRoaming )
		{
			vsrmPassword.valueType	=	PASSWORD_VALUE_TYPE_UNICODE;
			vsrmPassword.pszValue	=	_bstr_t(i_pvarPassword -> bstrVal);

			vsrmStatus =	VSRM_StartSession
							(
								&m_SessionHandle,
								tbstrUserName,
								&vsrmPassword,
								(const char*)tbstrClientInfo,
								(const char*)tbstrClientInfoSig
 							);
			if ( VSRM_SUCCESS != vsrmStatus )
			{
				longRetVal =	E_ROAMING_START_SESSION_FAILED;
			}
			else
			{
/*
				vsrmItemData.data	=	m_pbyteStorage;
				vsrmItemData.len	=	m_dwStorageLen;

				vsrmStatus =	VSRM_StoreData
								(
									m_SessionHandle,
									&vsrmItemData
								);
				if ( VSRM_SUCCESS != vsrmStatus )
				{
					if ( VSRM_ERR_USER_ALREADY_EXISTS == vsrmStatus )
					{
						longRetVal =	E_PROFEXISTS;
					}
					else
					{
						longRetVal =	E_ROAMING_STORE_DATA_FAILED;
					}
				}
*/
				vsrmStatus =	VSRM_ReserveUserName
								(
									m_SessionHandle,
									&vsrmUserNameStatus
								);
				if ( VSRM_SUCCESS != vsrmStatus )
				{
					if ( VSRM_USERNAME_STATUS_RECOVERABLE == vsrmUserNameStatus )
					{
						longRetVal =	E_PROFEXISTS;
					}
					else
					{
						longRetVal =	E_ROAM_RESERVE_FAILED;
					}
				}
				else
				{
					m_boolRoamingNameReserved =	TRUE;
				}
			}
		}
	}

	if(longRetVal != VS_SUCCESS)
	{
		retVal = longRetVal;

		if(boolProtectedStorageOpen)
		{
			pProtectedStorage->Close();
		}
		delete pProtectedStorage;
		pProtectedStorage = NULL;

		if(boolPTAProtectedStorageOpen)
		{
			pPTAProtectedStorage->Close();
		}
		delete pPTAProtectedStorage;
		pPTAProtectedStorage = NULL;

		if (boolEncPTAProtectedStorageOpen)
		{
			pEncPTAProtectedStorage->Close();
		}
		delete pEncPTAProtectedStorage;
		pEncPTAProtectedStorage = NULL;
	}
	else
	{
		//Store the profile name
		if(!m_boolRoaming)
		{
			bstrProfName = i_pvarWhichSmartCard->bstrVal; 
		}
		else
		{
			bstrProfName = tbstrUserName;
		}

		boolUsePS = TRUE;

		/*Remember the password, appcontext and the hostname*/
		m_tbstrHostName = i_pvarAppHostName->bstrVal;
		m_tbstrCurrentHostName = m_tbstrHostName;

		if(i_pvarPassword->vt == VT_BSTR)
		{
			m_tbstrPassword = i_pvarPassword->bstrVal;
		}
		else
		{
			m_tbstrPassword = "";
		}
		m_tbstrAppCtxtName = i_pvarAppCtxt->bstrVal;
		m_tbstrProfileIssFrndlyName = i_pvarProfileIssFrndlyName->bstrVal;
		nPasswordTimeOut =	i_pvarPasswdTimeOut -> iVal;

	}

//	VSPTA_CLEAN_TBSTR(tbstrUserName)
//	VSPTA_CLEAN_TBSTR(tbstrProfileIssUniqueID)
//	VSPTA_CLEAN_TBSTR(tbstrClientInfo)
//	VSPTA_CLEAN_TBSTR(tbstrClientInfoSig)
//	VSPTA_CLEAN_TBSTR(tbstrDummyHostName)
//	VSPTA_CLEAN_TBSTR(tbstrAppPrefName)

	return retVal;
}

HRESULT	SetPasswdFn ( void* i_pvoidPointer, _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut )
{
		//	TIMEOUT		pass all these parameters to the callback funciton
	HRESULT				hResult =	E_FAIL;
	HRESULT				longRetVal = VS_SUCCESS;
	CVirtualSmartCard*  pTheVSC = (CVirtualSmartCard*)i_pvoidPointer;
	BOOL				boolStoreData = FALSE;
	_bstr_t				tbstrAppPrefName = "";

	/*Obtain the number of tries, the last invalid try and the maximum no of tries and unlock period*/
	int nMaxTries;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteMaxTries = NULL;
		_VS_DWORD* dwMaxTriesSize;

		tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
		pTheVSC->pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pTheVSC->pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteMaxTries), (_VS_DWORD*)&dwMaxTriesSize);
		if(longRetVal == VS_SUCCESS)
		{
			nMaxTries = *pbyteMaxTries;
			pTheVSC->pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteMaxTries);
		}
		pTheVSC->pPTAProtectedStorage->EndRead();			
	}

	/*Obtain the number of invalid tries this far*/
	int nNumOfInvalidTries = nMaxTries;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteNumOfInvalidTries = NULL;
		_VS_DWORD* dwNumOfInvalidTriesSize;

		tbstrAppPrefName = INVALID_TRIES_NAME;
		pTheVSC->pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pTheVSC->pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteNumOfInvalidTries), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		if(longRetVal == VS_SUCCESS)
		{
			nNumOfInvalidTries = *pbyteNumOfInvalidTries;
			pTheVSC->pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteNumOfInvalidTries);
		}
		pTheVSC->pPTAProtectedStorage->EndRead();			
	}

	/*Obtain the unlock period*/
	int nUnlockPeriod;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteUnlockPeriod = NULL;
		_VS_DWORD* dwUnlockPeriodSize;

		tbstrAppPrefName = UNLOCK_PERIOD_NAME ;
		pTheVSC->pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pTheVSC->pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteUnlockPeriod), (_VS_DWORD*)(&dwUnlockPeriodSize));
		if(longRetVal == VS_SUCCESS)
		{
			nUnlockPeriod = *pbyteUnlockPeriod;
			pTheVSC->pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteUnlockPeriod);
		}
		pTheVSC->pPTAProtectedStorage->EndRead();			
	}

	

	FILETIME ftLastInvalidTry;
	FILETIME ftCurrTime;

	if(longRetVal == VS_SUCCESS)
	{
		/*Obtain the time of the last invalid try*/
		_VS_BYTE* pbyteLastInvalidTry = NULL;
		_VS_DWORD* dwNumOfInvalidTriesSize;

		tbstrAppPrefName = LAST_INVALIDTRY_NAME;
		pTheVSC->pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pTheVSC->pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteLastInvalidTry), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		if(longRetVal == VS_SUCCESS)
		{
			ftLastInvalidTry = *((FILETIME*)pbyteLastInvalidTry);
			pTheVSC->pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteLastInvalidTry);
		}
		pTheVSC->pPTAProtectedStorage->EndRead();			
	

	}

	/*Obtain the current time*/
	GetSystemTimeAsFileTime(&ftCurrTime);
		
	/*If the passwordtimeout parameter is non zero show bad password error, increment number of tries and 
	record it and the last invalid try time*/
	int nUIToShow = 0;
	if(*o_pdwPasswordTimeOut)
	{
		nNumOfInvalidTries ++;
		if(nNumOfInvalidTries >= nMaxTries)
		{
			/*Locked out*/
			nUIToShow = E_PROFLOCKEDOUT & 0x0000FFFF;
			longRetVal =	((CVirtualSmartCard*) i_pvoidPointer) -> m_pPasswordCallback (((CVirtualSmartCard*) i_pvoidPointer)->m_pvoidObjectPTA, (void*)&nUIToShow , o_cszPassword);
			nUIToShow = 0;
		}
		else
		{
			/*Bad password*/
			nUIToShow = E_INVALIDPASSWD & 0x0000FFFF;
			longRetVal =	((CVirtualSmartCard*) i_pvoidPointer) -> m_pPasswordCallback (((CVirtualSmartCard*) i_pvoidPointer)->m_pvoidObjectPTA, (void*)&nUIToShow , o_cszPassword);
			nUIToShow = 0;
		}
		ftLastInvalidTry = ftCurrTime;
		boolStoreData = TRUE;

	}

	/*Show ui*/
	do
	{
		longRetVal =	((CVirtualSmartCard*) i_pvoidPointer) -> m_pPasswordCallback (((CVirtualSmartCard*) i_pvoidPointer)->m_pvoidObjectPTA, (void*)&nUIToShow , o_cszPassword);
		
		if(longRetVal == VS_SUCCESS  && nNumOfInvalidTries >= nMaxTries)
		{
			GetSystemTimeAsFileTime(&ftCurrTime);

			//If currenttime - invalidtime < unlock period
			_int64 n64CurrTime =  (*(_int64*)(&ftCurrTime));
			_int64 n64LastInvalidTry =  (*(_int64*)(&ftLastInvalidTry));
			_int64 n64TheDiff = n64CurrTime - n64LastInvalidTry;
			
			int nDiffMinutes = (int)(n64TheDiff/(10000000))/60;

			if(nDiffMinutes < nUnlockPeriod)
			{
				/*Locked out message box*/
				nUIToShow = E_PROFLOCKEDOUT & 0x0000FFFF;
				longRetVal =	((CVirtualSmartCard*) i_pvoidPointer) -> m_pPasswordCallback (((CVirtualSmartCard*) i_pvoidPointer)->m_pvoidObjectPTA, (void*)&nUIToShow , o_cszPassword);
				nUIToShow = 0;

				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;
				
				//Return locked out error
				longRetVal = E_PROFLOCKEDOUT;

				boolStoreData = TRUE;
			}
			else
			{
				nNumOfInvalidTries = 0;
				boolStoreData = TRUE;
				longRetVal = VS_SUCCESS;
			}
		
			
		}
	}while(longRetVal == E_PROFLOCKEDOUT);   


	hResult = longRetVal; 

	if(boolStoreData)
	{
		tbstrAppPrefName = INVALID_TRIES_NAME;
		//pTheVSC->pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		pTheVSC->pPTAProtectedStorage->UpgradeReadToWrite();//(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		longRetVal = pTheVSC->pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&nNumOfInvalidTries ),
			sizeof(nNumOfInvalidTries), 0);

		tbstrAppPrefName = LAST_INVALIDTRY_NAME;
		longRetVal = pTheVSC->pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&ftLastInvalidTry),
			sizeof(ftLastInvalidTry), 0);
		pTheVSC->pPTAProtectedStorage->EndWrite();


	}
		

	
	*o_pdwPasswordTimeOut =	((CVirtualSmartCard*) i_pvoidPointer) -> nPasswordTimeOut;

/*
	hResult =	((CVirtualSmartCard*) i_pvoidPointer) -> VSM_SetPasswordFunction
				(
					o_cszPassword,
					o_pdwPasswordTimeOut
				);
*/

//	VSPTA_CLEAN_TBSTR(tbstrAppPrefName)

	return	hResult;
}


HRESULT	CVirtualSmartCard::VSM_SetPasswordFunction ( _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut )
{
	HRESULT				hResult				=	E_FAIL;

	memcpy
	(
		(BYTE*) o_cszPassword,
		(const BYTE*) ((WCHAR*) m_tbstrPassword),
		(m_tbstrPassword.length() + 1) * sizeof (_VS_CHAR)
	);

	*o_pdwPasswordTimeOut =	nPasswordTimeOut;

	hResult =	S_OK;
	return	hResult;
}

HRESULT CVirtualSmartCard::VSM_ChangeHost(BSTR bstrHostName, BSTR bstrAppCtxtName)
{

	bool		domainAllowed	= false;
	bool		boolCallEnd		= false;
	HRESULT		hResult			= S_OK;

	if(m_tbstrHostName != _bstr_t(bstrHostName))
	{
		if (pbstrReadOKDomains)
		{
			for (int i = 0; i < nNumOfReadOKDomains; i++)
			{
//				if (pbstrReadOKDomains[i] == _bstr_t(bstrHostName))
				if (CompareWildCardHosts(pbstrReadOKDomains[i], (_bstr_t)bstrHostName))
				{
					domainAllowed = true;
					break;
				}
			}
		}
		if (!domainAllowed && pbstrWriteOKDomains)
		{
			for (int i = 0; i < nNumOfWriteOKDomains; i++)
			{
//				if (pbstrWriteOKDomains[i] == _bstr_t(bstrHostName))
				if (CompareWildCardHosts(pbstrWriteOKDomains[i], (_bstr_t)bstrHostName))
				{
					domainAllowed = true;
					break;
				}
			}
		}
	}
	else
	{
		domainAllowed = true;
	}

	if (!domainAllowed)
		return E_HOSTBAD;

	while (1)
	{
		if ((m_tbstrAppCtxtName != _bstr_t(bstrAppCtxtName)) || 
			(m_tbstrCurrentHostName != _bstr_t(bstrHostName)))
		{
			if (!pProtectedStorage)
			{
				hResult = E_VSCNOTINIT;
				break;
			}

			hResult = pProtectedStorage->ChangeApplicationContext
						(
							(_VS_CHAR *) bstrAppCtxtName,
							(_VS_CHAR *) bstrHostName,
							TRUE	// the assumption here is that all apps. are protected
						);

			VSM_CHECK_HRESULT

			m_tbstrAppCtxtName = _bstr_t(bstrAppCtxtName);
			m_tbstrCurrentHostName = bstrHostName;
		}
		break;
	}

	return hResult;
}

HRESULT CVirtualSmartCard::VSM_Close()
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal = VS_SUCCESS;
	DWORD	dwPTAStorageChanged = 0;
	DWORD	dwStorageChanged = 0;
	DWORD	dwTemp=0;
	VSRM_STATUS	vsrmStatus;
	VSRM_ITEM	vsrmItemData;

	if(!boolUsePS)
		return E_VSCNOTINIT;

	if ( FALSE == m_boolRoaming )
	{
		longRetVal = pProtectedStorage->Close();
		delete pProtectedStorage;
		pProtectedStorage = NULL;

		if(longRetVal == VS_SUCCESS)
		{
			longRetVal = pPTAProtectedStorage->Close();
		}
		else
		{
			pPTAProtectedStorage->Close();
		}
		delete pPTAProtectedStorage;

		pPTAProtectedStorage = NULL;
	}
	else
	{
		retVal =	pPTAProtectedStorage -> CheckIfPSChangedAfterInitialization
					(
						(unsigned int*) &dwPTAStorageChanged
					);
		if ( S_OK != retVal )
		{
			return	E_FAIL;
		}

		retVal =	pProtectedStorage -> CheckIfPSChangedAfterInitialization
					(
						(unsigned int *) &dwStorageChanged
					);
		if ( S_OK != retVal )
		{
			return	E_FAIL;
		}

		longRetVal =	pProtectedStorage -> CloseForRoaming
						(
							(unsigned int*) &dwTemp
						);
		delete pProtectedStorage;
		pProtectedStorage = NULL;
		if(longRetVal == VS_SUCCESS)
		{
			longRetVal = pPTAProtectedStorage->CloseForRoaming
						(
							(unsigned int*) &dwTemp
						);
		}
		else
		{
			pPTAProtectedStorage->CloseForRoaming
			(
				(unsigned int*) &dwTemp
			);		
		}
		delete pPTAProtectedStorage;
		pPTAProtectedStorage = NULL;

		if ( ( 1 == dwStorageChanged ) || ( 1 == dwPTAStorageChanged ) )
		{
			if ( NULL != m_SessionHandle )
			{
				vsrmItemData.data =	m_pbyteStorage;
				vsrmItemData.len =	m_dwStorageLen;

				if ( TRUE == m_boolRoamingNameReserved )
				{
					// Sasi 05/06/03
					// Passing Secret Question and Answer to VSRM_StoreData function
					// This info is required for the profiles managed by new roaming server
					if(m_boolResetPasswdFeature)
					{

						 VSRM_CHAR_NVP nvp[] = {
						  {(char *) QUESTIONSTRING, m_tbstrSecretQuestion},
						  {(char *) ANSWERSTRING,   m_tbstrSecretAnswer},
						  {(char *) FNAMESTRING,    m_tbstrFirstName},
						  {(char *) LNAMESTRING,    m_tbstrLastName},
						  {(char *) EMAILSTRING,    m_tbstrEmail},
						  {NULL, NULL}
						 };


						vsrmStatus =	VSRM_StoreData
										(
											m_SessionHandle,
											&vsrmItemData,
											nvp
										);
					}
					else
					{
						vsrmStatus =	VSRM_StoreData
										(
											m_SessionHandle,
											&vsrmItemData,
											NULL
										);

					}

					m_boolRoamingNameReserved =	FALSE;
				}
				else
				{
					vsrmStatus =	VSRM_UpdateData
									(
										m_SessionHandle,
										&vsrmItemData
									);
				}
				if ( VSRM_SUCCESS != vsrmStatus )
				{
					/*char szMsg[1024];
					sprintf(szMsg, "Length is %d; Return code is  %d", m_dwStorageLen, vsrmStatus);
					MessageBox(NULL,szMsg, "Error", MB_OK);*/
					retVal =	E_ROAMING_UPDATE_FAILED;
				}
			}

		}
	}

	if(retVal == S_OK)
	{
		retVal = longRetVal;
	}

	boolUsePS = FALSE;

	return retVal;
}


HRESULT CVirtualSmartCard::VSM_Save()
{
	HRESULT retVal = S_OK;
	VSRM_STATUS	vsrmStatus;
	VSRM_ITEM	vsrmItemData;
	DWORD		dwStorageChanged		=	0;
	DWORD		dwPTAStorageChanged		=	0;

	if(!boolUsePS)
		return E_VSCNOTINIT;

	if ( FALSE == m_boolRoaming )
	{
		/*longRetVal = pProtectedStorage->Close();

		
		if(longRetVal == VS_SUCCESS)
		{
			longRetVal = pPTAProtectedStorage->Close();
		}
		else
		{
			pPTAProtectedStorage->Close();
		}*/
	}
	else
	{
		retVal =	pPTAProtectedStorage -> CheckIfPSChangedAfterInitialization
					(
						(unsigned int*) &dwPTAStorageChanged
					);
		if ( S_OK != retVal )
		{
			return	E_FAIL;
		}

		retVal =	pProtectedStorage -> CheckIfPSChangedAfterInitialization 
					(
						(unsigned int *) &dwStorageChanged
					);
		if ( S_OK != retVal )
		{
			return	E_FAIL;
		}

		if ( ( 1 == dwStorageChanged ) || ( 1 == dwPTAStorageChanged ) )
		{
			if ( NULL != m_SessionHandle )
			{
				vsrmItemData.data =	m_pbyteStorage;
				vsrmItemData.len =	m_dwStorageLen;

				if ( TRUE == m_boolRoamingNameReserved )
				{
					// Sasi 05/06/03
					// Passing Secret Question and Answer to VSRM_StoreData function
					// This info is required for the profiles managed by new roaming server
					if(m_boolResetPasswdFeature)
					{
						 VSRM_CHAR_NVP nvp[] = {
						  {(char *) QUESTIONSTRING, m_tbstrSecretQuestion},
						  {(char *) ANSWERSTRING,   m_tbstrSecretAnswer},
						  {(char *) FNAMESTRING,    m_tbstrFirstName},
						  {(char *) LNAMESTRING,    m_tbstrLastName},
						  {(char *) EMAILSTRING,    m_tbstrEmail},
						  {NULL, NULL}
						 };

						vsrmStatus =	VSRM_StoreData
										(
											m_SessionHandle,
											&vsrmItemData,
											nvp
										);
					}
					else
					{
						vsrmStatus =	VSRM_StoreData
										(
											m_SessionHandle,
											&vsrmItemData,
											NULL
										);

					}

					m_boolRoamingNameReserved =	FALSE;
				}
				else
				{
					vsrmStatus =	VSRM_UpdateData
									(
										m_SessionHandle,
										&vsrmItemData
									);
				}

				if ( VSRM_SUCCESS != vsrmStatus )
				{
					/*char szMsg[1024];
					sprintf(szMsg, "Length is %d; Return code is  %d", m_dwStorageLen, vsrmStatus);
					MessageBox(NULL,szMsg, "Error", MB_OK);*/
					retVal =	E_ROAMING_UPDATE_FAILED;
				}
				else
				{
					retVal =	pPTAProtectedStorage -> ResetChangedAfterInitializationFlag ();
					if ( S_OK != retVal )
					{
						return	E_FAIL;
					}

					retVal =	pProtectedStorage -> ResetChangedAfterInitializationFlag ();
					if ( S_OK != retVal )
					{
						return	E_FAIL;
					}
				}
			}

		}
	}

	return retVal;
}


HRESULT CVirtualSmartCard::VSM_SetAppPreference(BSTR in_bstrPrefName, VARIANT *in_pvarPrefValue, int i_ncAddApplicationIfItDoesNotExist)
{
	HRESULT			hResult			=	E_FAIL;
	BOOL			boolCallEnd		=	FALSE;
	PBYTE			pbData			=	NULL;
	DWORD			cbData			=	0;

	while (1)
	{
		VSCSP_CHECK_IF_PS_OBJECT_READY

		
		// Supporting only ARRAY for now
		if(VT_ARRAY != in_pvarPrefValue->vt)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		if(SafeArrayAccessData((SAFEARRAY FAR*)in_pvarPrefValue->parray,(void HUGEP* FAR*)&pbData) != S_OK)
		{
			hResult = E_UNEXPECTED;
			break;
		}
		else
		{
			long lBound;    
			long uBound;
			
			// Verify that the SafeArray is the proper shape.
			SafeArrayGetLBound((SAFEARRAY FAR*)in_pvarPrefValue->parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)in_pvarPrefValue->parray, 1, &uBound);
			cbData = uBound - lBound + 1;
			SafeArrayUnaccessData((SAFEARRAY *)in_pvarPrefValue->parray);

			if(cbData <= 0)
			{
				hResult = E_UNEXPECTED;
				break;
			}
		}
		
		/*if (in_pvarPrefValue->vt != VT_BSTR)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		pbData = (byte *)(WCHAR *)in_pvarPrefValue->bstrVal;
		cbData = SysStringLen(in_pvarPrefValue->bstrVal)*2;
		*/

		bool allowedApplication = false;

		hResult = IsThisDomainAllowedToWriteThisApplication(m_tbstrCurrentHostName, &allowedApplication);
		if (hResult != S_OK)
		{
			break;
		}
		else if (allowedApplication == false)
		{
			hResult = E_HOSTBAD;
			break;
		}

		hResult =	BeginWrite
					(
						pProtectedStorage,
						NO_BLOCK_RETURN_ERROR,
						0
					);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> SetApplicationPreference
					(
						in_bstrPrefName,
						pbData,
						cbData,
						i_ncAddApplicationIfItDoesNotExist
					);

		VSM_CHECK_HRESULT
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndWrite ();
	}

	return hResult;
}


HRESULT CVirtualSmartCard::VSM_GetAppPreference(BSTR in_bstrPrefName, VARIANT *o_pvarPrefValue)
{
	HRESULT			hResult			=	E_FAIL;
	BOOL			boolCallEnd		=	FALSE;
	BYTE*			pbyteData		=	NULL;
	DWORD			dwDataLen		=	0;

	while (1)
	{

		VSCSP_CHECK_IF_PS_OBJECT_READY

		o_pvarPrefValue->vt =	VT_EMPTY;

		bool allowedApplication = false;
		hResult = IsThisDomainAllowedToReadThisApplication(m_tbstrCurrentHostName, &allowedApplication);
		if (hResult != S_OK)
		{
			break;
		}
		else if (allowedApplication == false)
		{
			hResult = E_HOSTBAD;
			break;
		}

		hResult =	BeginRead
						( 
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> GetApplicationPreference
					(
						in_bstrPrefName,
						(unsigned char**) &pbyteData,
						(unsigned int*) &dwDataLen
					);
		VSM_CHECK_HRESULT

		o_pvarPrefValue->vt =	VT_ARRAY;
		o_pvarPrefValue->parray =	SafeArrayCreateVector(VT_UI1, 0, dwDataLen);
		if ( NULL == o_pvarPrefValue->parray )
		{
			hResult = E_UNEXPECTED;
			break;
		}

		memcpy((BYTE*)o_pvarPrefValue->parray->pvData, pbyteData, dwDataLen);

		
/*
		o_pvarPrefValue->vt = VT_BSTR;
		o_pvarPrefValue->bstrVal = SysAllocStringByteLen((char *) pbyteData, dwDataLen);
*/
		hResult =	VS_SUCCESS;
		break;

	}	//	end		while (1)

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	VSCSP_DELETE_USING_PS_FREE (pbyteData)

	return hResult;
}

HRESULT CVirtualSmartCard::BeginRead(CProtectedStorage* i_pProtectedStorage, _VS_DWORD i_cnMode, _VS_DWORD i_cnWaitTime)
{

	HRESULT hResult = S_OK;

	bool allowed = IsThisDomainAllowedToReadProfileData(m_tbstrCurrentHostName);
	
	if (allowed)
	{
		hResult = i_pProtectedStorage->BeginRead(i_cnMode, i_cnWaitTime);
	}
	else
	{
		hResult = E_HOSTBAD;
	}
	return hResult;
}

HRESULT CVirtualSmartCard::BeginWrite(CProtectedStorage* i_pProtectedStorage, _VS_DWORD i_cnMode, _VS_DWORD i_cnWaitTime)
{

	HRESULT hResult = S_OK;

	bool allowed = IsThisDomainAllowedToWriteProfileData(m_tbstrCurrentHostName);
	
	if (allowed)
	{
		i_pProtectedStorage->BeginWrite(i_cnMode, i_cnWaitTime);
	}
	else
	{
		hResult = E_HOSTBAD;
	}
	return hResult;
}


HRESULT CVirtualSmartCard::UpgradeReadToWrite(CProtectedStorage* i_pProtectedStorage)
{

	HRESULT hResult = S_OK;

	bool allowed = IsThisDomainAllowedToWriteProfileData(m_tbstrCurrentHostName);
	
	if (allowed)
	{
		i_pProtectedStorage->UpgradeReadToWrite();
	}
	else
	{
		hResult = E_HOSTBAD;
	}
	return hResult;
}

bool CVirtualSmartCard::IsThisDomainAllowedToReadProfileData(const _bstr_t i_tbstrHostName)
{

	HRESULT retVal = S_OK;

	bool allowed = false;

	if ((i_tbstrHostName != m_tbstrHostName) && (!CompareWildCardHosts(m_tbstrProfileOpenHostWildCard, i_tbstrHostName)))
	{		
		for (int i = 0; i < nNumOfReadOKDomains; i++)
		{
//			if (pbstrReadOKDomains[i] == i_tbstrHostName)
			if (CompareWildCardHosts(pbstrReadOKDomains[i], i_tbstrHostName))
			{
				allowed = true;
				break;
			}
		}
		for (int j = 0; j < nNumOfWriteOKDomains; j++)
		{
//			if (pbstrWriteOKDomains[j] == i_tbstrHostName)
			if (CompareWildCardHosts(pbstrWriteOKDomains[j], i_tbstrHostName))
			{
				allowed = true;
				break;
			}
		}
	}
	else
	{
		allowed = true;
	}
	return allowed;
}

bool CVirtualSmartCard::IsThisDomainAllowedToWriteProfileData(const _bstr_t i_tbstrHostName)
{

	HRESULT retVal = S_OK;

	bool allowed = false;

	if ((i_tbstrHostName != m_tbstrHostName) && (!CompareWildCardHosts(m_tbstrProfileOpenHostWildCard, i_tbstrHostName)))
	{
		for (int i = 0; i < nNumOfWriteOKDomains; i++)
		{
//			if (pbstrWriteOKDomains[i] == i_tbstrHostName)
			if (CompareWildCardHosts(pbstrWriteOKDomains[i], i_tbstrHostName))
			{
				allowed = true;
				break;
			}
		}
	}
	else
	{
		allowed = true;
	}
	return allowed;
}


HRESULT CVirtualSmartCard::IsThisDomainAllowedToReadThisApplication(const _bstr_t i_tbstrHostName, bool *o_pboolAllowedApplication)
{

	HRESULT hResult = S_OK;
	byte* pbyteCreator = NULL;
	byte* pbyteCreatorWildCard = NULL;
	bool boolCallEnd = false;

	bool allowedApplication = false;
	
	do
	{

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd = true;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);


		if (hResult == E_VS_INVALID_APP)
		{
			hResult = S_OK;
			allowedApplication = true;
			break;			
		}

		VSM_CHECK_HRESULT


		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT


		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if (tbstrCreator == _bstr_t(DUMMY_HOSTNAME))
		{
			allowedApplication = true;
			break;
		}

		if ((tbstrCreator != i_tbstrHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, i_tbstrHostName)))
		{
			
		}
		else
		{
			allowedApplication = true;
			break;
		}


		if (boolCallEnd)
		{
			pProtectedStorage->EndRead();
			boolCallEnd = false;
		}

/*		if ((allowedApplication))
		{
			break;
			*/
//			*o_pboolAllowedApplication = allowedApplication;
//			return hResult;
//		}

		_bstr_t* pbstrApplicationReadOKDomains = NULL;
		DWORD    dwNumOfApplicationReadOKDomains;
		hResult = GetFullAccessApplicationReadOKDomains(&pbstrApplicationReadOKDomains, &dwNumOfApplicationReadOKDomains);
			
		if (hResult != S_OK)
		{
			if (hResult == E_VS_INVALID_APP)
			{	
				allowedApplication = true;
				hResult = S_OK;
				break;
			}
			else
			{
				break;
			}
		}

		for (unsigned int i = 0; i < dwNumOfApplicationReadOKDomains; i++)
		{
			if ((pbstrApplicationReadOKDomains[i] == i_tbstrHostName) || (CompareWildCardHosts(pbstrApplicationReadOKDomains[i], i_tbstrHostName)))
			{
				allowedApplication = true;
				break;
			}
		}

		if (!allowedApplication) {
			_bstr_t* pbstrApplicationWriteOKDomains = NULL;
			DWORD    dwNumOfApplicationWriteOKDomains;
			hResult = GetFullAccessApplicationWriteOKDomains(&pbstrApplicationWriteOKDomains, &dwNumOfApplicationWriteOKDomains);
				
			if (hResult != S_OK)
			{
				if (hResult == E_VS_INVALID_APP)
				{	
					allowedApplication = true;
					hResult = S_OK;
					break;
				}
				else
				{
					break;
				}
			}

			for (unsigned int i = 0; i < dwNumOfApplicationWriteOKDomains; i++)
			{
				if ((pbstrApplicationWriteOKDomains[i] == i_tbstrHostName) || (CompareWildCardHosts(pbstrApplicationWriteOKDomains[i], i_tbstrHostName)))
				{
					allowedApplication = true;
					break;
				}
			}
		}
	}
	while (0);
	if (boolCallEnd)
	{
		pProtectedStorage->EndRead();
	}
	*o_pboolAllowedApplication = allowedApplication;
	return hResult;

}

HRESULT CVirtualSmartCard::IsThisDomainAllowedToWriteThisApplication(const _bstr_t i_tbstrHostName, bool *o_pboolAllowedApplication)
{

	HRESULT hResult = S_OK;
	byte* pbyteCreator = NULL;
	byte* pbyteCreatorWildCard = NULL;
	bool boolCallEnd = false;

	bool allowedApplication = false;
	
	do
	{

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd = true;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		if (hResult == E_VS_INVALID_APP)
		{
			hResult = S_OK;
			allowedApplication = true;
			break;			
		}

		VSM_CHECK_HRESULT


		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT


		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if (tbstrCreator == _bstr_t(DUMMY_HOSTNAME))
		{
			allowedApplication = true;
			break;
		}

		if ((tbstrCreator != i_tbstrHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, i_tbstrHostName)))
		{
			
		}
		else
		{
			allowedApplication = true;
			break;
		}

		if (boolCallEnd)
		{
			pProtectedStorage->EndRead();
			boolCallEnd = false;
		}

		_bstr_t* pbstrApplicationWriteOKDomains = NULL;
		DWORD    dwNumOfApplicationWriteOKDomains;
		hResult = GetFullAccessApplicationWriteOKDomains(&pbstrApplicationWriteOKDomains, &dwNumOfApplicationWriteOKDomains);
			
		if (hResult != S_OK)
		{
			if (hResult == E_VS_INVALID_APP)
			{	
				allowedApplication = true;
				hResult = S_OK;
				break;
			}
			else
			{
				break;
			}
		}

		for (unsigned int i = 0; i < dwNumOfApplicationWriteOKDomains; i++)
		{
			if ((pbstrApplicationWriteOKDomains[i] == i_tbstrHostName) || (CompareWildCardHosts(pbstrApplicationWriteOKDomains[i], i_tbstrHostName)))
			{
				allowedApplication = true;
				break;
			}
		}
	}
	while (0);

	if (boolCallEnd)
	{
		pProtectedStorage->EndRead();
	}
	*o_pboolAllowedApplication = allowedApplication;
	return hResult;
}

bool CVirtualSmartCard::CompareWildCardHosts
(
	const _bstr_t	in_tbstrWildCardHost,
	const _bstr_t	in_tbstrCurrentHost
)
{

	// lengths do not include the null termination character.
	int lenWild = SysStringLen((BSTR) in_tbstrWildCardHost);
	int lenCurr = SysStringLen((BSTR) in_tbstrCurrentHost);

	if (!lenCurr || !lenWild)
	{
		return false;
	}

	char* pcharWildCard = (char *) in_tbstrWildCardHost;
	char* pcharCurrHost = (char *) in_tbstrCurrentHost;

	int i = 0;
	int index = -1;

	// only the first occurence can be an asterisk. we filter out the rest when we set the wildcards.
	// so check for asterisk only in the 0th location.

	if (pcharWildCard[0] != '*')
	{
		if (in_tbstrWildCardHost != in_tbstrCurrentHost)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// start index for curr host for the remaining characters.
	int startSubIndex = lenCurr - lenWild + 1;

	if (startSubIndex <= 0)
	{
	// doesnt match.
		return false;
	}
			
	_bstr_t tbstrSubWildCard = _bstr_t(&pcharWildCard[1]);
	_bstr_t tbstrSubCurrHost = _bstr_t(&pcharCurrHost[startSubIndex]);

	if (tbstrSubWildCard != tbstrSubCurrHost)
	{
		return false;
	}
	else
	{
		return true;
	}
	return false;
}


// Validate an array of bstr wild card domains.
bool CVirtualSmartCard::ValidateBstrArrayWildCardDomains
(
	const _bstr_t* i_pbstrWildCardDomains,
	const int i_nNumOfDomains
)
{

	bool valid = true;

	for (int i = 0; i < i_nNumOfDomains; i++)
	{
		if (!ValidateBstrWildCardDomain(i_pbstrWildCardDomains[i]))
		{
			valid = false;
			break;
		}
	}
	return valid;
}


// This routine is to allow only *, *.com, *.xyz.com, etc.(wilcard.something) 
// or abc.xyz.com (no wildcard)
bool CVirtualSmartCard::ValidateBstrWildCardDomain(const _bstr_t i_tbstrWildCardDomain)
{

	bool valid = true;

	do
	{
		char* pcszWildCardDomain = (char *) i_tbstrWildCardDomain;
		int len = SysStringLen((BSTR)i_tbstrWildCardDomain);
		if (len == 0)
		{
			valid = false;
			break;
		}
		// if only one char any character except a comm ',' is allowed.
		if (len == 1)
		{
			if (pcszWildCardDomain[0] == ',')
			{
				valid = false;
			}
			continue;
		}
		// wild-card can only be the first character. should not occur anywhere else.
		for (int i = 1; i < len; i++)
		{
			if ((pcszWildCardDomain[i] == '*') || (pcszWildCardDomain[i] == ','))
			{
				valid = false;
				break;
			}
		}
		if (!valid)
		{
			break;
		}

		// if first-char is wild-card second should be '.' and 3rd should be non '.'
		if (pcszWildCardDomain[0] == '*')
		{	
			if (pcszWildCardDomain[1] != '.')
			{
				valid = false;
				break;
			}
			if (!pcszWildCardDomain[2] || pcszWildCardDomain[2] == '.')
			{
				valid = false;
				break;
			}
		}
	}
	while (0);
	return valid;
}

/*
HRESULT CVirtualSmartCard::set_VSM_ProfileCurrentHostName(_bstr_t i_tbstrCurrentHostName)
{
	HRESULT hResult = S_OK;

	while (1)
	{
		m_tbstrCurrentHostName = i_tbstrCurrentHostName;
		break;
	}
	return hResult;

}
*/

HRESULT CVirtualSmartCard::get_VSM_ProfileOpenHostName(_bstr_t* o_pbstrHostName)
{
	HRESULT hResult = S_OK;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pbstrHostName)

		*o_pbstrHostName = m_tbstrHostName;

		break;
	}
	return hResult;

}

HRESULT CVirtualSmartCard::put_VSM_ProfileOpenHostWildCard(_bstr_t i_tbstrHostWildCard)
{
	HRESULT hResult = S_OK;

	while (1)
	{
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_tbstrHostWildCard)

		if (m_tbstrCurrentHostName != m_tbstrHostName)
		{
			hResult = E_HOSTBAD;
			break;
		}

		if (!ValidateBstrWildCardDomain(i_tbstrHostWildCard))
		{
			hResult = E_INVALIDARGS;
			break;
		}
		m_tbstrProfileOpenHostWildCard = i_tbstrHostWildCard;

		break;
	}
	return hResult;

}

HRESULT CVirtualSmartCard::get_VSM_ReadOKDomains(_bstr_t** o_ppbstrReadOKDomains, DWORD* o_pdwNumOfReadOKDomains)
{
	
	HRESULT hResult = S_OK;
//	SAFEARRAY *psa = NULL;

	while(1)
	{
		/*Input validation*/
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrReadOKDomains)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumOfReadOKDomains)

		if ((m_tbstrCurrentHostName != m_tbstrHostName) && 
			(!CompareWildCardHosts(m_tbstrProfileOpenHostWildCard, m_tbstrCurrentHostName))
		   )
		{
			hResult = E_HOSTBAD;
			break;

		}

		/*		long ix[1];

		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = nNumOfReadOKDomains;
		psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

		for (int i = 0; i < nNumOfReadOKDomains; i++) {
			
			VARIANT var;
			ix[0] = i;

			var.vt = VT_BSTR;
			var.bstrVal = (pbstrReadOKDomains[i]).copy();
			SafeArrayPutElement(psa, ix, &var);
			VariantClear(&var);
		}

		o_pvarReadOKDomains->vt = VT_ARRAY;
		o_pvarReadOKDomains->pparray = &psa;
*/
		*o_ppbstrReadOKDomains = pbstrReadOKDomains;
		*o_pdwNumOfReadOKDomains = nNumOfReadOKDomains;

		hResult = S_OK;
		break;
	}
	return hResult;

}

HRESULT CVirtualSmartCard::put_VSM_ReadOKDomains(VARIANT *in_pvarReadOKDomains)
{

	HRESULT hResult = S_OK;

	while (1)
	{

		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_pvarReadOKDomains)

		if ((m_tbstrCurrentHostName != m_tbstrHostName) && 
			(!CompareWildCardHosts(m_tbstrProfileOpenHostWildCard, m_tbstrCurrentHostName))
		   )
		{
			hResult = E_HOSTBAD;
			break;

		}


		/*Extract the bstrs from the variant*/
		//First obtain and make sure that the array has only one dimension
		int nDims = SafeArrayGetDim(in_pvarReadOKDomains->parray);
		if (nDims != 1)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		//Now obtain the number of elements in each dimension and make sure that the second dimension
		//has a bound of 2
		LONG nNumOfElemsInDim1;
		LONG lowerBound;
		LONG upperBound;

		hResult = SafeArrayGetLBound(in_pvarReadOKDomains->parray, 1, &lowerBound);
		if(hResult != S_OK)
		{
			break;
		}

		hResult = SafeArrayGetUBound(in_pvarReadOKDomains->parray, 1, &upperBound);
		if(hResult != S_OK)
		{
			hResult = E_SAFEARRAYGETUBOUNDFAILED;
			break;
		}

		// because lower bound is zero.
		nNumOfElemsInDim1 = upperBound - lowerBound + 1;

		//Now extract the elements
		_bstr_t* pbstrTempReadOKDomains = (_bstr_t *) new _bstr_t[nNumOfElemsInDim1];

		hResult = _ExtractBstrsFromArray(in_pvarReadOKDomains->parray, 1, lowerBound, upperBound, pbstrTempReadOKDomains);
		
		if (hResult == S_OK)
		{
	//		FreeBstrArray(&pbstrReadOKDomains);
			if (!ValidateBstrArrayWildCardDomains(pbstrTempReadOKDomains, nNumOfElemsInDim1))
			{
				hResult = E_INVALIDARGS;
				break;
			}

			pbstrReadOKDomains = pbstrTempReadOKDomains;
			nNumOfReadOKDomains = nNumOfElemsInDim1;
		}
/*		else
		{
			FreeBstrArray(&pbstrTempReadOKDomains);
		} */

		break;

	}
	return hResult;

}

HRESULT CVirtualSmartCard::get_VSM_WriteOKDomains(_bstr_t** o_ppbstrWriteOKDomains, DWORD* o_pdwNumOfWriteOKDomains)
{
	
	HRESULT hResult = S_OK;
//	SAFEARRAY *psa = NULL;

	while(1)
	{
		/*Input validation*/
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrWriteOKDomains)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumOfWriteOKDomains)

		if ((m_tbstrCurrentHostName != m_tbstrHostName) && 
			(!CompareWildCardHosts(m_tbstrProfileOpenHostWildCard, m_tbstrCurrentHostName))
		   )
		{
			hResult = E_HOSTBAD;
			break;

		}

		/*		long ix[1];

		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = nNumOfWriteOKDomains;
		psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

		for (int i = 0; i < nNumOfWriteOKDomains; i++) {
			
			VARIANT var;
			ix[0] = i;

			var.vt = VT_BSTR;
			var.bstrVal = (pbstrWriteOKDomains[i]).copy();
			SafeArrayPutElement(psa, ix, &var);
			VariantClear(&var);
		}

		o_pvarWriteOKDomains->vt = VT_ARRAY;
		o_pvarWriteOKDomains->pparray = &psa;
*/
		*o_ppbstrWriteOKDomains = pbstrWriteOKDomains;
		*o_pdwNumOfWriteOKDomains = nNumOfWriteOKDomains;

		hResult = S_OK;
		break;
	}
	return hResult;

}

HRESULT CVirtualSmartCard::put_VSM_WriteOKDomains(VARIANT *in_pvarWriteOKDomains)
{

	HRESULT hResult = S_OK;

	while (1)
	{

		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_pvarWriteOKDomains)

		if ((m_tbstrCurrentHostName != m_tbstrHostName) && 
			(!CompareWildCardHosts(m_tbstrProfileOpenHostWildCard, m_tbstrCurrentHostName))
		   )
		{
			hResult = E_HOSTBAD;
			break;

		}


		/*Extract the bstrs from the variant*/
		//First obtain and make sure that the array has only one dimension
		int nDims = SafeArrayGetDim(in_pvarWriteOKDomains->parray);
		if (nDims != 1)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		//Now obtain the number of elements in each dimension and make sure that the second dimension
		//has a bound of 2
		LONG nNumOfElemsInDim1;
		LONG lowerBound;
		LONG upperBound;

		hResult = SafeArrayGetLBound(in_pvarWriteOKDomains->parray, 1, &lowerBound);
		if(hResult != S_OK)
		{
			break;
		}

		hResult = SafeArrayGetUBound(in_pvarWriteOKDomains->parray, 1, &upperBound);
		if(hResult != S_OK)
		{
			hResult = E_SAFEARRAYGETUBOUNDFAILED;
			break;
		}

		// because lower bound is zero.
		nNumOfElemsInDim1 = upperBound - lowerBound + 1;

		//Now extract the elements
		_bstr_t* pbstrTempWriteOKDomains = (_bstr_t *) new _bstr_t[nNumOfElemsInDim1];

		hResult = _ExtractBstrsFromArray(in_pvarWriteOKDomains->parray, 1, lowerBound, upperBound, pbstrTempWriteOKDomains);
		
		if (hResult == S_OK)
		{
	//		FreeBstrArray(&pbstrWriteOKDomains);
			if (!ValidateBstrArrayWildCardDomains(pbstrTempWriteOKDomains, nNumOfElemsInDim1))
			{
				hResult = E_INVALIDARGS;
				break;
			}

			pbstrWriteOKDomains = pbstrTempWriteOKDomains;
			nNumOfWriteOKDomains = nNumOfElemsInDim1;
		}
/*		else
		{
			FreeBstrArray(&pbstrTempWriteOKDomains);
		} */

		break;

	}
	return hResult;

}

HRESULT CVirtualSmartCard::get_VSM_ApplicationReadOKDomains(_bstr_t** o_ppbstrApplicationReadOKDomains, DWORD* o_pdwNumOfApplicationReadOKDomains)
{

	HRESULT		hResult						= S_OK;
	SAFEARRAY*	psa							= NULL;

	BOOL		boolCallEnd					= FALSE;
	DWORD		dwNumOfDomains				= 0;
	byte*		pbyteData					= NULL;
	byte*		pbyteCreator				= NULL;
	byte*		pbyteCreatorWildCard		= NULL;
	DWORD		dwDataLen					=	0;
	_bstr_t*	pbstrApplicationReadOKDomains;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrApplicationReadOKDomains)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumOfApplicationReadOKDomains)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT


		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if ((tbstrCreator != m_tbstrCurrentHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, m_tbstrCurrentHostName)))
		{
			hResult = E_HOSTBAD;
			break;
		}

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> GetApplicationReadOKDomains
					(
						(unsigned int*) &dwNumOfDomains,
						(unsigned char**) &pbyteData,
						(unsigned int*) &dwDataLen
					);
		VSM_CHECK_HRESULT

		if (dwNumOfDomains > 0)
		{
			// extract domainnames from the comma-separated string/blob and populate the array.
			hResult = GetArrayFromBlob(pbyteData, dwNumOfDomains, L",", &pbstrApplicationReadOKDomains);
			VSM_CHECK_HRESULT
		}

/*
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = dwNumOfDomains;
		psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

		for (int i = 0; i < dwNumOfDomains; i++) {
			
			VARIANT var;
			ix[0] = i;

			var.vt = VT_BSTR;
			var.bstrVal = (pbstrApplicationReadOKDomains[i]).copy();
			SafeArrayPutElement(psa, ix, &var);
			VariantClear(&var);
		}

		o_pvarApplicationReadOKDomains->vt = VT_ARRAY;
		o_pvarApplicationReadOKDomains->pparray = &psa;
*/
		*o_ppbstrApplicationReadOKDomains = pbstrApplicationReadOKDomains;
		*o_pdwNumOfApplicationReadOKDomains = dwNumOfDomains;
		hResult = S_OK;
		break;
	}

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}
	return hResult;
}

HRESULT CVirtualSmartCard::put_VSM_ApplicationReadOKDomains(VARIANT* in_pvarApplicationReadOKDomains)
{

	HRESULT			hResult			= S_OK;
	BOOL			boolCallEnd		= TRUE;
	byte*			pbyteCreator	= NULL;
	byte*			pbyteCreatorWildCard = NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_pvarApplicationReadOKDomains)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginWrite
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT

		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if ((tbstrCreator != m_tbstrCurrentHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, m_tbstrCurrentHostName)))
		{
			hResult = E_HOSTBAD;
			break;
		}

		/*Extract the bstrs from the variant*/
		//First obtain and make sure that the array has only one dimension
		int nDims = SafeArrayGetDim(in_pvarApplicationReadOKDomains->parray);
		if (nDims != 1)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		//Now obtain the number of elements in each dimension and make sure that the second dimension
		//has a bound of 2
		LONG nNumOfElemsInDim1;		
		LONG lowerBound;
		LONG upperBound;

		hResult = SafeArrayGetLBound(in_pvarApplicationReadOKDomains->parray, 1, &lowerBound);
		if(hResult != S_OK)
		{
			break;
		}

		hResult = SafeArrayGetUBound(in_pvarApplicationReadOKDomains->parray, 1, &upperBound);
		if(hResult != S_OK)
		{
			hResult = E_SAFEARRAYGETUBOUNDFAILED;
			break;
		}

		// because lower bound is zero.
		nNumOfElemsInDim1 = upperBound - lowerBound + 1;

		//Now extract the elements
		_bstr_t* pbstrTempApplicationReadOKDomains = (_bstr_t *) new _bstr_t[nNumOfElemsInDim1];
		DWORD dwNumOfDomains = 0;

		hResult = _ExtractBstrsFromArray(in_pvarApplicationReadOKDomains->parray, 1, lowerBound, upperBound, pbstrTempApplicationReadOKDomains);

		if (hResult != S_OK)
		{
			break;
		}

		if (!ValidateBstrArrayWildCardDomains(pbstrTempApplicationReadOKDomains, nNumOfElemsInDim1))
		{
			hResult = E_INVALIDARGS;
			break;
		}

		if (hResult == S_OK)
		{
			dwNumOfDomains = nNumOfElemsInDim1;
		}
		else
		{
			break;
		}

		_bstr_t bstrApplicationReadOKDomainsBlob;
		DWORD	dwBlobLength;

		// concatenate the domain names into a comma-separated string/blob.
		hResult = GetBlobFromArray(pbstrTempApplicationReadOKDomains, &dwNumOfDomains, &bstrApplicationReadOKDomainsBlob, &dwBlobLength, tbstrCreator);

		VSM_CHECK_HRESULT

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> SetApplicationReadOKDomains
					(
						dwNumOfDomains,
						(byte *)(WCHAR *)bstrApplicationReadOKDomainsBlob,
						dwBlobLength
					);

		break;
	}
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndWrite ();
	}

	return hResult;
//	return S_OK;
}

HRESULT CVirtualSmartCard::get_VSM_ApplicationWriteOKDomains(_bstr_t** o_ppbstrApplicationWriteOKDomains, DWORD* o_pdwNumOfApplicationWriteOKDomains)
{

	HRESULT		hResult						= S_OK;
	SAFEARRAY*	psa							= NULL;

	BOOL		boolCallEnd					= FALSE;
	DWORD		dwNumOfDomains				= 0;
	byte*		pbyteData					= NULL;
	byte*		pbyteCreator				= NULL;
	byte*		pbyteCreatorWildCard		= NULL;
	DWORD		dwDataLen					=	0;
	_bstr_t*	pbstrApplicationWriteOKDomains;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrApplicationWriteOKDomains)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumOfApplicationWriteOKDomains)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT

		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if ((tbstrCreator != m_tbstrCurrentHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, m_tbstrCurrentHostName)))
		{
			hResult = E_HOSTBAD;
			break;
		}

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> GetApplicationWriteOKDomains
					(
						(unsigned int*) &dwNumOfDomains,
						(unsigned char**) &pbyteData,
						(unsigned int*) &dwDataLen
					);
		VSM_CHECK_HRESULT

		if (dwNumOfDomains > 0)
		{
			// extract domainnames from the comma-separated string/blob and populate the array.
			hResult = GetArrayFromBlob(pbyteData, dwNumOfDomains, L",", &pbstrApplicationWriteOKDomains);
			VSM_CHECK_HRESULT
		}

/*
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = dwNumOfDomains;
		psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

		for (int i = 0; i < dwNumOfDomains; i++) {
			
			VARIANT var;
			ix[0] = i;

			var.vt = VT_BSTR;
			var.bstrVal = (pbstrApplicationWriteOKDomains[i]).copy();
			SafeArrayPutElement(psa, ix, &var);
			VariantClear(&var);
		}

		o_pvarApplicationWriteOKDomains->vt = VT_ARRAY;
		o_pvarApplicationWriteOKDomains->pparray = &psa;
*/
		*o_ppbstrApplicationWriteOKDomains = pbstrApplicationWriteOKDomains;
		*o_pdwNumOfApplicationWriteOKDomains = dwNumOfDomains;
		hResult = S_OK;
		break;
	}

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}
	return hResult;
}

HRESULT CVirtualSmartCard::put_VSM_ApplicationWriteOKDomains(VARIANT* in_pvarApplicationWriteOKDomains)
{

	HRESULT			hResult			= S_OK;
	BOOL			boolCallEnd		= TRUE;
	byte*			pbyteCreator	= NULL;
	byte*			pbyteCreatorWildCard = NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_pvarApplicationWriteOKDomains)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginWrite
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT

		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if ((tbstrCreator != m_tbstrCurrentHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, m_tbstrCurrentHostName)))
		{
			hResult = E_HOSTBAD;
			break;
		}

		/*Extract the bstrs from the variant*/
		//First obtain and make sure that the array has only one dimension
		int nDims = SafeArrayGetDim(in_pvarApplicationWriteOKDomains->parray);
		if (nDims != 1)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		//Now obtain the number of elements in each dimension and make sure that the second dimension
		//has a bound of 2
		LONG nNumOfElemsInDim1;		
		LONG lowerBound;
		LONG upperBound;

		hResult = SafeArrayGetLBound(in_pvarApplicationWriteOKDomains->parray, 1, &lowerBound);
		if(hResult != S_OK)
		{
			break;
		}

		hResult = SafeArrayGetUBound(in_pvarApplicationWriteOKDomains->parray, 1, &upperBound);
		if(hResult != S_OK)
		{
			hResult = E_SAFEARRAYGETUBOUNDFAILED;
			break;
		}

		// because lower bound is zero.
		nNumOfElemsInDim1 = upperBound - lowerBound + 1;
		
		//Now extract the elements
		_bstr_t* pbstrTempApplicationWriteOKDomains = (_bstr_t *) new _bstr_t[nNumOfElemsInDim1];
		DWORD dwNumOfDomains = 0;

		hResult = _ExtractBstrsFromArray(in_pvarApplicationWriteOKDomains->parray, 1, lowerBound, upperBound, pbstrTempApplicationWriteOKDomains);

		if (hResult != S_OK)
		{
			break;
		}

		if (!ValidateBstrArrayWildCardDomains(pbstrTempApplicationWriteOKDomains, nNumOfElemsInDim1))
		{
			hResult = E_INVALIDARGS;
			break;
		}

		if (hResult == S_OK)
		{
			dwNumOfDomains = nNumOfElemsInDim1;
		}
		else
		{
			break;
		}

		_bstr_t bstrApplicationWriteOKDomainsBlob;
		DWORD	dwBlobLength;

		// concatenate the domain names into a comma-separated string/blob.
		hResult = GetBlobFromArray(pbstrTempApplicationWriteOKDomains, &dwNumOfDomains, &bstrApplicationWriteOKDomainsBlob, &dwBlobLength, tbstrCreator);

		VSM_CHECK_HRESULT

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> SetApplicationWriteOKDomains
					(
						dwNumOfDomains,
						(byte *)(WCHAR *)bstrApplicationWriteOKDomainsBlob,
						dwBlobLength
					);

		break;
	}
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndWrite ();
	}

	return hResult;
//	return S_OK;
}

HRESULT CVirtualSmartCard::GetFullAccessApplicationReadOKDomains
(
	_bstr_t** o_ppbstrApplicationReadOKDomains, 
	DWORD* o_pdwNumOfApplicationReadOKDomains
)
{

	HRESULT		hResult						= S_OK;
	SAFEARRAY*	psa							= NULL;

	BOOL		boolCallEnd					= FALSE;
	DWORD		dwNumOfDomains				= 0;
	byte*		pbyteData					= NULL;
	DWORD		dwDataLen					=	0;
	_bstr_t*	pbstrApplicationReadOKDomains = NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrApplicationReadOKDomains)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumOfApplicationReadOKDomains)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> GetApplicationReadOKDomains
					(
						(unsigned int*) &dwNumOfDomains,
						(unsigned char**) &pbyteData,
						(unsigned int*) &dwDataLen
					);
		VSM_CHECK_HRESULT

		if (dwNumOfDomains > 0)
		{
			// extract domainnames from the comma-separated string/blob and populate the array.
			hResult = GetArrayFromBlob(pbyteData, dwNumOfDomains, L",", &pbstrApplicationReadOKDomains);
			VSM_CHECK_HRESULT
		}

		*o_ppbstrApplicationReadOKDomains = pbstrApplicationReadOKDomains;
		*o_pdwNumOfApplicationReadOKDomains = dwNumOfDomains;
		hResult = S_OK;
		break;
	}

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}
	return hResult;

}

HRESULT CVirtualSmartCard::GetFullAccessApplicationWriteOKDomains
(
	_bstr_t** o_ppbstrApplicationWriteOKDomains, 
	DWORD* o_pdwNumOfApplicationWriteOKDomains
)
{

	HRESULT		hResult						= S_OK;
	SAFEARRAY*	psa							= NULL;

	BOOL		boolCallEnd					= FALSE;
	DWORD		dwNumOfDomains				= 0;
	byte*		pbyteData					= NULL;
	DWORD		dwDataLen					=	0;
	_bstr_t*	pbstrApplicationWriteOKDomains = NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrApplicationWriteOKDomains)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumOfApplicationWriteOKDomains)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		//	get the contain contents information blob
		hResult =	pProtectedStorage -> GetApplicationWriteOKDomains
					(
						(unsigned int*) &dwNumOfDomains,
						(unsigned char**) &pbyteData,
						(unsigned int*) &dwDataLen
					);
		VSM_CHECK_HRESULT

		if (dwNumOfDomains > 0)
		{
			// extract domainnames from the comma-separated string/blob and populate the array.
			hResult = GetArrayFromBlob(pbyteData, dwNumOfDomains, L",", &pbstrApplicationWriteOKDomains);
			VSM_CHECK_HRESULT
		}

		*o_ppbstrApplicationWriteOKDomains = pbstrApplicationWriteOKDomains;
		*o_pdwNumOfApplicationWriteOKDomains = dwNumOfDomains;
		hResult = S_OK;
		break;
	}

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}
	return hResult;

}

HRESULT CVirtualSmartCard::AmITheApplicationCreator(bool* o_pboolIsCreator)
{

	HRESULT		hResult						= S_OK;

	BOOL		boolCallEnd					= FALSE;
	byte*		pbyteCreator				= NULL;
	byte*		pbyteCreatorWildCard		= NULL;

	*o_pboolIsCreator = false;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pboolIsCreator)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT


		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if ((tbstrCreator != m_tbstrCurrentHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, m_tbstrCurrentHostName)))
		{
			hResult = E_HOSTBAD;
		}
		else
		{
			*o_pboolIsCreator = true;
		}
		break;
	}
	if (boolCallEnd == TRUE)
	{
		pProtectedStorage->EndRead();
	}
	return hResult;
}

HRESULT CVirtualSmartCard::IsThisHostTheApplicationCreator(BSTR i_bstrHostName, bool* o_pboolIsCreator)
{

	HRESULT		hResult						= S_OK;

	BOOL		boolCallEnd					= FALSE;
	byte*		pbyteCreator				= NULL;
	byte*		pbyteCreatorWildCard		= NULL;

	*o_pboolIsCreator = false;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pboolIsCreator)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT

		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);
		_bstr_t i_tbstrHostName = _bstr_t(i_bstrHostName);

		if ((tbstrCreator != i_tbstrHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, i_tbstrHostName)))
		{
			hResult = E_HOSTBAD;
			break;
		}
		else
		{
			*o_pboolIsCreator = true;
		}
		break;
	}
	if (boolCallEnd == TRUE)
	{
		pProtectedStorage->EndRead();
	}
	return hResult;
}

HRESULT CVirtualSmartCard::put_VSM_ApplicationCreatorWildCard(_bstr_t i_tbstrCreatorWildCard)
{
	HRESULT	hResult	= S_OK;
	bool	boolCallEndRead = FALSE;
	bool	boolCallEndWrite = TRUE;
	bool	valid = true;

	do
	{
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_tbstrCreatorWildCard)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEndRead =	TRUE;

		byte*	pbyteCreator = NULL;
		byte* pbyteCreatorWildCard = NULL;

		hResult =	pProtectedStorage -> GetApplicationCreator
					(
						&pbyteCreator
					);

		VSM_CHECK_HRESULT

		hResult =	pProtectedStorage -> GetApplicationCreatorWildCard
					(
						&pbyteCreatorWildCard
					);

		VSM_CHECK_HRESULT

		_bstr_t tbstrCreator = _bstr_t((WCHAR *) pbyteCreator);
		_bstr_t	tbstrCreatorWildCard = _bstr_t((WCHAR *) pbyteCreatorWildCard);

		if ((tbstrCreator != m_tbstrCurrentHostName) && (!CompareWildCardHosts(tbstrCreatorWildCard, m_tbstrCurrentHostName)))
		{
			hResult = E_HOSTBAD;
			break;
		}
		
		char* pcszCreator = (char *) tbstrCreator;
		char* pcszWildCard = (char *) i_tbstrCreatorWildCard;

		int lenCreator = SysStringLen((BSTR)tbstrCreator);
		int lenWildCard = SysStringLen((BSTR)i_tbstrCreatorWildCard);

		valid = true;

		if (lenWildCard < 3)
		{
			valid = false;
		}
		else if (pcszWildCard[0] != '*')
		{
			// while string should match exactly no wild-cards.
			if (tbstrCreator != i_tbstrCreatorWildCard)
			{
				valid = false;
			}
		}
		else
		{
			// it should start with "*."
			if (pcszWildCard[1] != '.')
			{
				valid = false;
			}
			else
			{
				int i = lenCreator - 1;
				int count = 0;
				for (int j = lenWildCard - 1; j > 0; j--)
				{
					if (pcszWildCard[j] == '.')
					{
						count++;
					}
					if (pcszCreator[i] != pcszWildCard[j])
					{
						valid = false;
						break;
					}
					if (i == 0)
					{
						if (j != 2)
						{
							valid = false;
						}
						else
						{
							count ++;
						}
						break;
					}
					i--;
				}
				if (count < 2)
				{
					valid = false;
				}
			}
		}

		if (!valid)
		{
			hResult = E_INVALIDARGS;
			break;
		}

		hResult = UpgradeReadToWrite(pProtectedStorage);

		VSM_CHECK_HRESULT

		boolCallEndWrite = TRUE;

		hResult =	pProtectedStorage -> SetApplicationCreatorWildCard
					(
						(byte *)(WCHAR *) i_tbstrCreatorWildCard,
						lenWildCard * 2
					);

		VSM_CHECK_HRESULT

	}
	while (0);

	if (boolCallEndWrite == TRUE)
	{
		pProtectedStorage->EndWrite();
	}

	if (boolCallEndRead == TRUE)
	{
		pProtectedStorage->EndRead();
	}

	return hResult;
}

HRESULT CVirtualSmartCard::GetArrayFromBlob
(
	const byte*		in_pbyteBlob, 
	const DWORD		in_numOfElements,
	const WCHAR*	in_delimiter,
	_bstr_t**		o_ppbstrArray
)
{

	HRESULT	hResult = VS_SUCCESS;

	while(1)
	{

		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_pbyteBlob)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_delimiter)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppbstrArray)

		WCHAR *pwcharBlob = (WCHAR *) in_pbyteBlob;

		*o_ppbstrArray = new _bstr_t[in_numOfElements];
		WCHAR*	token;

		token = wcstok(pwcharBlob, in_delimiter);
		for (unsigned int i = 0; i < in_numOfElements; i++)
		{
			(*o_ppbstrArray)[i] = _bstr_t(token);

			token = wcstok(NULL, in_delimiter);
			if (token == NULL)
			{
				break;
			}
		}
		if (i < in_numOfElements)
		{
			hResult = E_UNEXPECTED;
			break;
		}
		break;
	}
	return hResult;
}

HRESULT CVirtualSmartCard::GetBlobFromArray
(
	const _bstr_t*	in_pbstrArray,
	DWORD*			io_pdwArraySize,
	_bstr_t*		o_pbstrBlob,
	DWORD*			o_pdwblobLength,
	_bstr_t			in_tbstrCreator
)
{
	HRESULT			hResult = VS_SUCCESS;

	// this converts array into comma separated bstr-blob.
	// and note that there is a comma at the end too.
	while (1)
	{
		bool creatorAlreadyExists = false;

		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (in_pbstrArray)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pbstrBlob)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwblobLength)

		/*
		*o_pbstrBlob = in_pbstrArray[0].copy();
		if (in_pbstrArray[0] == in_tbstrCreator)
		{
			creatorAlreadyExists = true;
		}
		*/
		for (unsigned int i = 0; i < *io_pdwArraySize; i++)
		{
			*o_pbstrBlob += in_pbstrArray[i];
			*o_pbstrBlob += L",";
			if (in_pbstrArray[i] == in_tbstrCreator)
			{
				creatorAlreadyExists = true;
			}
		}

		if (!creatorAlreadyExists)
		{
			*o_pbstrBlob += in_tbstrCreator;
			*o_pbstrBlob += L",";
			*io_pdwArraySize++;
		}

		// multiply by two to get number of bytes. SysStringLen returns number of WCHARs
		*o_pdwblobLength = 2 * SysStringLen(*o_pbstrBlob);
		
		hResult = VS_SUCCESS;
		break;
	}
	return hResult;
}


HRESULT CVirtualSmartCard::_ExtractBstrsFromArray
(
	SAFEARRAY*			i_pSafeArray,
	const int			i_nDims, 
	const int			i_lBound,
	const int			i_uBound,
	_bstr_t*			o_ptbstrBstrArr
)
{
	HRESULT retVal = S_OK;
	LONG lIndices[2];

	lIndices[1] = i_nDims;
	VARIANT varElem;

	for (int i = i_lBound; i <= i_uBound; ++i)
	{
		lIndices[0] = i;
		SafeArrayGetElement(i_pSafeArray, lIndices, (void*) &varElem);
		o_ptbstrBstrArr[i-i_lBound] = varElem.bstrVal;
	}
	return retVal;

}

HRESULT CVirtualSmartCard::get_VSM_PasswdQuality(short* o_pnPasswdQuality)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::put_VSM_PasswdQuality(short in_nPasswdQualtiy)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::get_VSM_PasswdLength(short* o_pnPasswdLength)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::put_VSM_PasswdLength(short in_nPasswdLength)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::get_VSM_PasswdTimeOut(short* o_pnPasswdTimeOut)
{
	*o_pnPasswdTimeOut = nPasswordTimeOut;
	return S_OK;
}

HRESULT CVirtualSmartCard::put_VSM_PasswdTimeOut(short in_nPasswdTimeOut)
{
	HRESULT retVal = S_OK;

	nPasswordTimeOut = in_nPasswdTimeOut;

	DWORD	dwPasswordTimeOut	=	in_nPasswdTimeOut;

	retVal =	pProtectedStorage -> UpdatePasswordTimeout ( dwPasswordTimeOut );

	return retVal;
}

HRESULT CVirtualSmartCard::get_VSM_PasswdLockOutTries(short* o_pnPasswdLockOutTries)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::put_VSM_PasswdLockOutTries(short in_nPasswdLockOutTries)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::get_VSM_PasswdUnLockPeriod(short* o_pnPasswdUnLockPeriod)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::put_VSM_PasswdUnLockPeriod(short in_nPasswdUnLockPeriod)
{
	return S_OK;
}

HRESULT CVirtualSmartCard::VSM_AddCert(VARIANT* i_pvarCertToAdd, unsigned int *o_pCertNum)
{
	HRESULT retVal = S_OK;
	LONG longRetVal;
	if(!boolUsePS)
	{
		retVal = E_VSCNOTINIT;
	}
	
	/*Obtain the cert blob from the variant*/
	PBYTE pbyteCertBlob = NULL;
	DWORD dwCertBlobSize;
	if(retVal == S_OK)
	{
		if(SafeArrayGetUBound(i_pvarCertToAdd->parray,1,(long*)&dwCertBlobSize) != S_OK)
		{
			retVal = E_SAFEARRAYGETUBOUNDFAILED;
		}
		else
		{
			dwCertBlobSize++;
			if(SafeArrayAccessData(i_pvarCertToAdd->parray,(void** HUGEP)&pbyteCertBlob) != S_OK)
			{
				retVal = E_SAFEARRAYACCDATAFAILED;
			}
		}

	}

	/*Add cert in the protected storage*/
	if(retVal == S_OK)
	{
		longRetVal = BeginWrite(pProtectedStorage, BLOCK_FOR_X_SECONDS,BEGINWRITE_BLOCK_PERIOD);
		if(longRetVal == VS_SUCCESS)
		{
			unsigned int nPtrToCert;
			longRetVal = pProtectedStorage->AddCertificateToDB(pbyteCertBlob,dwCertBlobSize, &nPtrToCert);
			if(longRetVal == VS_SUCCESS)
			{
				retVal = pProtectedStorage->GetNumberOfCertificatesInDB(o_pCertNum);
				if(retVal == VS_SUCCESS)
					*o_pCertNum -= 1;	// return 0 based index
			}

			pProtectedStorage->EndWrite();
		}

		if(longRetVal != VS_SUCCESS)
			retVal = longRetVal;
	}

	if(pbyteCertBlob)
		SafeArrayUnaccessData(i_pvarCertToAdd->parray);

	return retVal;
}

HRESULT CVirtualSmartCard::get_VSM_ProfileName(VARIANT* o_pvarProfileName)
{
	if (m_dwIsTPM)
	{
		o_pvarProfileName->vt = VT_BSTR;
		o_pvarProfileName->bstrVal = tbstrContainerName.copy();
		return S_OK;
	}

	if(boolUsePS)
	{
		o_pvarProfileName->vt = VT_BSTR;
		o_pvarProfileName->bstrVal = bstrProfName.copy();
		return S_OK;
	}
	else
	{
		return E_VSCNOTINIT;
	}
	
}

HRESULT CVirtualSmartCard::get_VSM_ProfileIssFrndlyName(VARIANT *o_pvarProfileIssFrndlyName)
{
	if (boolUsePS)
	{
		o_pvarProfileIssFrndlyName->vt = VT_BSTR;
		o_pvarProfileIssFrndlyName->bstrVal = m_tbstrProfileIssFrndlyName.copy();
		return S_OK;
	}
	else
	{
		return E_VSCNOTINIT;
	}
}

HRESULT CVirtualSmartCard::put_VSM_ProfileIssFrndlyName(VARIANT *i_pvarProfileIssFrndlyName)
{
	if (boolUsePS)
	{
		m_tbstrProfileIssFrndlyName = i_pvarProfileIssFrndlyName->bstrVal;
		return S_OK;
	}
	else
	{
		return E_VSCNOTINIT;
	}	
}

HRESULT CVirtualSmartCard::VSM_Open(VARIANT* i_pvarWhichSmartCard, VARIANT* i_pvarPassword, VARIANT* i_pvarAppCtxt,
		VARIANT* i_pvarProfileIssFrndlyName, VARIANT* i_pvarAppHostName, VARIANT* i_pvarPasswdTimeOut, int i_ncAddApplicationIfItDoesNotExist,
		FN_PasswordCallback* i_pPasswordCallback, void* i_pObjectPTA)
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal = VS_SUCCESS;
	BOOL boolProtectedStorageOpen = FALSE;
	BOOL boolPTAProtectedStorageOpen = FALSE;
	BOOL boolEncPTAProtectedStorageOpen = FALSE;

	BOOL boolIsItAnOldVersionProfile = FALSE;

	_bstr_t		tbstrUserName = "";
	VSRM_STATUS	vsrmStatus;
	VSRM_ITEM		vsrmItemData;
	

	if ( (NULL == i_pPasswordCallback) || (NULL == i_pObjectPTA) )
	{
		return	E_FAIL;
	}
	m_pPasswordCallback =	i_pPasswordCallback;
	m_pvoidObjectPTA	=	i_pObjectPTA;

	/*If protected storage is open, return already open error*/
	if(boolUsePS)
	{
		return E_CARDALREADYOPEN;
	}
	
	/*Open the pta protected storage within the given filename, application name, application host name,
	password, and password timeout value
	 - this is an encrypted application, do not add this application*/
	pPTAProtectedStorage = new CProtectedStorage;
	_bstr_t tbstrDummyHostName(DUMMY_HOSTNAME);
	_bstr_t tbstrPTAAppCtxtName(PTA_APPCTXT_NAME);
	_bstr_t tbstrEncPTAAppCtxtName(PTA_ENC_APPCTXT_NAME);
	
	if(i_pvarWhichSmartCard->vt == (VT_ARRAY|VT_VARIANT))
	{

		m_boolRoaming =	TRUE;

		// Check if roaming profiles are managed by new roaming server that supports password reset feature
		retVal = CheckRoamingVersion(i_pvarWhichSmartCard);

		if(retVal == S_OK)
			retVal = GetRoamingStorage(i_pvarWhichSmartCard, i_pvarPassword, &tbstrUserName);
		else
			longRetVal = retVal;

		//Reverse the bytes
		if(retVal == S_OK)
		{
			longRetVal =	pPTAProtectedStorage -> InitializeForRoaming
							(
								(_VS_CHAR*)tbstrPTAAppCtxtName,
								(_VS_CHAR*)tbstrDummyHostName,
								APPLICATION_DECRYPTED,
								FALSE,
								tbstrUserName,
								&m_pbyteStorage,
								(unsigned int*)	&m_dwStorageLen,
								NULL,
								i_pvarPasswdTimeOut->iVal,
								SetPasswdFn,
								(void*) this,
								m_boolResetPasswdFeature
							);
		}
		else
			longRetVal = retVal;
	}
	else
	{
		longRetVal = pPTAProtectedStorage->Initialize((_VS_CHAR*)tbstrPTAAppCtxtName,(_VS_CHAR*)tbstrDummyHostName,APPLICATION_DECRYPTED,
		FALSE,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,NULL,
		i_pvarPasswdTimeOut->iVal,SetPasswdFn, (void*) this);
	}

	if(longRetVal != VS_SUCCESS)
		return longRetVal;
	else
	{
		boolPTAProtectedStorageOpen = TRUE;
	}

	_bstr_t tbstrAppPrefName = "";

	/*Obtain the maximum number of tries that are allowed*/
	int nMaxTries;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteMaxTries = NULL;
		_VS_DWORD* dwMaxTriesSize;

		tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteMaxTries), (_VS_DWORD*)&dwMaxTriesSize);
		if(longRetVal == VS_SUCCESS)
		{
			nMaxTries = *pbyteMaxTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteMaxTries);
		}
		pPTAProtectedStorage->EndRead();			
	}

	/*Obtain the number of invalid tries this far*/
	int nNumOfInvalidTries = nMaxTries;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteNumOfInvalidTries = NULL;
		_VS_DWORD* dwNumOfInvalidTriesSize;

		tbstrAppPrefName = INVALID_TRIES_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteNumOfInvalidTries), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		if(longRetVal == VS_SUCCESS)
		{
			nNumOfInvalidTries = *pbyteNumOfInvalidTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteNumOfInvalidTries);
		}
		pPTAProtectedStorage->EndRead();			
	}

	/*Obtain the unlock period*/
	int nUnlockPeriod;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteUnlockPeriod = NULL;
		_VS_DWORD* dwUnlockPeriodSize;

		tbstrAppPrefName = UNLOCK_PERIOD_NAME ;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteUnlockPeriod), (_VS_DWORD*)(&dwUnlockPeriodSize));
		if(longRetVal == VS_SUCCESS)
		{
			nUnlockPeriod = *pbyteUnlockPeriod;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteUnlockPeriod);
		}
		pPTAProtectedStorage->EndRead();			
	}

	

	FILETIME ftLastInvalidTry;
	FILETIME ftCurrTime;

	/*Obtain the current time*/
	GetSystemTimeAsFileTime(&ftCurrTime);
	
	//If the number of invalid tries is greater than or equal to the max tries
	if(longRetVal == VS_SUCCESS  && nNumOfInvalidTries >= nMaxTries)
	{
		/*Obtain the time of the last invalid try*/
		_VS_BYTE* pbyteLastInvalidTry = NULL;
		_VS_DWORD* dwNumOfInvalidTriesSize;

		tbstrAppPrefName = LAST_INVALIDTRY_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteLastInvalidTry), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		if(longRetVal == VS_SUCCESS)
		{
			ftLastInvalidTry = *((FILETIME*)pbyteLastInvalidTry);
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteLastInvalidTry);
		}
		pPTAProtectedStorage->EndRead();			
	
		//If currenttime - invalidtime < unlock period
		if(longRetVal == VS_SUCCESS)
		{
			_int64 n64CurrTime =  (*(_int64*)(&ftCurrTime));
			_int64 n64LastInvalidTry =  (*(_int64*)(&ftLastInvalidTry));
			_int64 n64TheDiff = n64CurrTime - n64LastInvalidTry;
			
			int nDiffMinutes = (int)(n64TheDiff/(10000000))/60;

			if(nDiffMinutes < nUnlockPeriod)
			{
				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;
				
				//Return locked out error
				longRetVal = E_PROFLOCKEDOUT;
			}
		}
		
	}
	
	/*Obtain the password timeout value*/
	int nPasswdTimeOutPeriod = PASSWDTIMEOUT_DEF;
	if(longRetVal == VS_SUCCESS)
	{
		_VS_BYTE* pbyteNumOfInvalidTries = NULL;
		_VS_DWORD* dwNumOfInvalidTriesSize;

		tbstrAppPrefName = TIMEOUT_PERIOD_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteNumOfInvalidTries), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		if(longRetVal == VS_SUCCESS)
		{
			nPasswdTimeOutPeriod = *pbyteNumOfInvalidTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteNumOfInvalidTries);
		}
		else if(longRetVal == E_VS_INVALID_APP_PREF)
			longRetVal = VS_SUCCESS;
		pPTAProtectedStorage->EndRead();			
	}
	

	if(longRetVal == VS_SUCCESS)
	{		
		
		/*Try to open the Encrypted Verisign PTA AppCtxt profile */
		pEncPTAProtectedStorage = new CProtectedStorage;
		
		if ( TRUE == m_boolRoaming )
		{
			longRetVal =	pEncPTAProtectedStorage -> InitializeForRoaming
							(
								(_VS_CHAR*)tbstrEncPTAAppCtxtName,
								(_VS_CHAR*)tbstrDummyHostName,
								APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
								i_ncAddApplicationIfItDoesNotExist,
								tbstrUserName,
								&m_pbyteStorage,
								(unsigned int*) &m_dwStorageLen,
//								(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,
//								STORAGE_FILE_OPEN,
								(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
								nPasswdTimeOutPeriod,SetPasswdFn,
								(void*) this,
								m_boolResetPasswdFeature
							);

		}
		else
		{
			longRetVal = pEncPTAProtectedStorage->Initialize((_VS_CHAR*)tbstrEncPTAAppCtxtName,(_VS_CHAR*)tbstrDummyHostName,APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
				i_ncAddApplicationIfItDoesNotExist,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
				nPasswdTimeOutPeriod,SetPasswdFn, (void*) this);

		}		
		//If return value is invalid password
		if(E_VS_BAD_PASSWORD == longRetVal)  //The second condition means we tried to open an encrypted or decrypted application when it was not there
		{
			if((i_pvarPassword->vt == VT_BSTR) && lstrlenW(i_pvarPassword->bstrVal) != 0)
			{
				//Increment the number of invalid tries
				nNumOfInvalidTries ++;

				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;	
	
			}
			
			//Return locked out error
			longRetVal = E_INVALIDPASSWD;

			

		}
		else if(longRetVal == E_VS_INVALID_APP)
		{
			//Return locked out error
			longRetVal = E_INVALIDPASSWD;

		}
		else if(longRetVal == VS_SUCCESS)
		{
			// This does not mean that the Encrypted Verisign AppCtxt is present.
			boolEncPTAProtectedStorageOpen = TRUE;
			
			_VS_BYTE* pbyteMaxTries = NULL;
			_VS_DWORD* dwMaxTriesSize;

			// Do a dummy get app preference to see if this app ctxt and preference exists.
			tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
			pEncPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
			longRetVal = pEncPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteMaxTries), (_VS_DWORD*)&dwMaxTriesSize);
			if(longRetVal == VS_SUCCESS)
			{
				boolIsItAnOldVersionProfile = FALSE;
				pEncPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteMaxTries);
			}
			else
			{
				boolIsItAnOldVersionProfile = TRUE;
			}
			pEncPTAProtectedStorage->EndRead();
			longRetVal = VS_SUCCESS;
		}

		if (longRetVal == VS_SUCCESS) {
			/*Try to open the profile with the application context*/
			pProtectedStorage = new CProtectedStorage;
			
			if ( TRUE == m_boolRoaming )
			{
				longRetVal =	pProtectedStorage -> InitializeForRoaming
								(
									(_VS_CHAR*)i_pvarAppCtxt->bstrVal,
									(_VS_CHAR*)i_pvarAppHostName->bstrVal,
									APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
									i_ncAddApplicationIfItDoesNotExist,
									tbstrUserName,
									&m_pbyteStorage,
									(unsigned int*) &m_dwStorageLen,
	//								(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,
	//								STORAGE_FILE_OPEN,
									(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
									nPasswdTimeOutPeriod,SetPasswdFn,
									(void*) this,
									m_boolResetPasswdFeature
								);

			}
			else
			{
				longRetVal = pProtectedStorage->Initialize((_VS_CHAR*)i_pvarAppCtxt->bstrVal,(_VS_CHAR*)i_pvarAppHostName->bstrVal,APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
					i_ncAddApplicationIfItDoesNotExist,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
					nPasswdTimeOutPeriod,SetPasswdFn, (void*) this);

			}
			
			//If return value is invalid password
			if(E_VS_BAD_PASSWORD == longRetVal)  //The second condition means we tried to open an encrypted or decrypted application when it was not there
			{
				if((i_pvarPassword->vt == VT_BSTR) && lstrlenW(i_pvarPassword->bstrVal) != 0)
				{
					//Increment the number of invalid tries
					nNumOfInvalidTries ++;

					//lastinvalidtry = currenttime
					ftLastInvalidTry = ftCurrTime;	
		
				}
				
				//Return locked out error
				longRetVal = E_INVALIDPASSWD;

				

			}
			else if(longRetVal == E_VS_INVALID_APP)
			{
				//Return locked out error
				longRetVal = E_INVALIDPASSWD;

			}
			else if(longRetVal == VS_SUCCESS)
			{
				boolProtectedStorageOpen = TRUE;

				if (boolIsItAnOldVersionProfile == TRUE)
				{
					if (boolEncPTAProtectedStorageOpen == TRUE)
					{
						pEncPTAProtectedStorage -> Close();

					}
					delete pEncPTAProtectedStorage;
					boolEncPTAProtectedStorageOpen = FALSE;
					// It is an old profile so the encrypted verisign app. parameters are in the
					// actual app ctxt itself.
					pEncPTAProtectedStorage  = pProtectedStorage;
				}

				int nMaxTriesConfirm;

				/*Obtain the number of max lockout tries from the 
				application context*/
				if(longRetVal == VS_SUCCESS)
				{
					_VS_BYTE* pbyteMaxTries = NULL;
					_VS_DWORD* dwMaxTriesSize;

					tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
					pEncPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
					longRetVal = pEncPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteMaxTries), (_VS_DWORD*)&dwMaxTriesSize);
					if(longRetVal == VS_SUCCESS)
					{
						nMaxTriesConfirm = *pbyteMaxTries;
						pEncPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteMaxTries);
					}
					pEncPTAProtectedStorage->EndRead();			
				}

				/*Obtain the unlock period from the applcation context*/
				int nUnlockPeriodConfirm;
				if(longRetVal == VS_SUCCESS)
				{
					_VS_BYTE* pbyteUnlockPeriod = NULL;
					_VS_DWORD* dwUnlockPeriodSize;

					tbstrAppPrefName = UNLOCK_PERIOD_NAME ;
					pEncPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
					longRetVal = pEncPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteUnlockPeriod), (_VS_DWORD*)(&dwUnlockPeriodSize));
					if(longRetVal == VS_SUCCESS)
					{
						nUnlockPeriodConfirm = *pbyteUnlockPeriod;
						pEncPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteUnlockPeriod);
					}
					pEncPTAProtectedStorage->EndRead();			
				}

				/*Obtain the password timeout value*/
				int nPasswdTimeOutPeriodConfirm = PASSWDTIMEOUT_DEF;
				if(longRetVal == VS_SUCCESS)
				{
					_VS_BYTE* pbyteNumOfInvalidTries = NULL;
					_VS_DWORD* dwNumOfInvalidTriesSize;

					tbstrAppPrefName = TIMEOUT_PERIOD_NAME;
					pEncPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
					longRetVal = pEncPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteNumOfInvalidTries), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
					if(longRetVal == VS_SUCCESS)
					{
						nPasswdTimeOutPeriodConfirm = *pbyteNumOfInvalidTries;
						pEncPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteNumOfInvalidTries);
					}
					else if(longRetVal == E_VS_INVALID_APP_PREF)
						longRetVal = VS_SUCCESS;
					pEncPTAProtectedStorage->EndRead();			
				}

				/*Make sure they are not tampered with*/
				if(nMaxTriesConfirm != nMaxTries || nUnlockPeriodConfirm != nUnlockPeriod || 
					nPasswdTimeOutPeriodConfirm != nPasswdTimeOutPeriod)
				{
					longRetVal = E_INVALIDPASSWD;
				}

				if(longRetVal == VS_SUCCESS)
				{
					//Number of invalid tries = 0
					nNumOfInvalidTries = 0;
				
					boolUsePS = TRUE;

					//Set the profile name that is opened
					if(!m_boolRoaming)
					{
						bstrProfName = i_pvarWhichSmartCard->bstrVal;
					}
					else
					{
						bstrProfName = tbstrUserName;
					}


					/*Remember the timeout, appcontext and the hostname*/
					m_tbstrHostName = i_pvarAppHostName->bstrVal;
					m_tbstrCurrentHostName = m_tbstrHostName;
					/*if(i_pvarPassword->vt == VT_BSTR)
					{
						m_tbstrPassword = i_pvarPassword->bstrVal;
					}
					else
					{
						m_tbstrPassword = "";
					}*/
					m_tbstrAppCtxtName = i_pvarAppCtxt->bstrVal;
					m_tbstrProfileIssFrndlyName = i_pvarProfileIssFrndlyName->bstrVal;
					//nPasswordTimeOut =	i_pvarPasswdTimeOut -> iVal;
					nPasswordTimeOut =	nPasswdTimeOutPeriod;
				}
			}
		}

		
	}


	retVal = longRetVal;

	/*Set the number of invalid tries*/
	if(!m_boolRoaming)
	{
		tbstrAppPrefName = INVALID_TRIES_NAME;
		pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&nNumOfInvalidTries ),
			sizeof(nNumOfInvalidTries), 0);
		pPTAProtectedStorage->EndWrite();
	}

	if(longRetVal != VS_SUCCESS)
		retVal = longRetVal;

	if(retVal == VS_SUCCESS)
	{
		if (boolIsItAnOldVersionProfile == TRUE)
		{
		
			// It is an old version profile. Upgrade it.
			// Add the Verisign Encrypted PTA Application Context.
			_bstr_t tbstrEncPTAAppCtxtName(PTA_ENC_APPCTXT_NAME);
			longRetVal = pEncPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
			if (longRetVal == VS_SUCCESS)
			{
				longRetVal = pEncPTAProtectedStorage->AddApplicationToDB((_VS_CHAR *)tbstrEncPTAAppCtxtName, (_VS_CHAR *)tbstrDummyHostName, APPLICATION_ENCRYPTED);
			}
			pEncPTAProtectedStorage->EndWrite();

			if (longRetVal == VS_SUCCESS)
			{
				// pEncPTAProtectedStorage currently same as pProtectedStorage. Change it.
				// Initialize ProtectedStorage with Encrypted PTA AppContext.
				pEncPTAProtectedStorage = NULL;
				
				pEncPTAProtectedStorage = new CProtectedStorage;
				boolIsItAnOldVersionProfile = FALSE;

				if ( TRUE == m_boolRoaming )
				{
					longRetVal =	pEncPTAProtectedStorage -> InitializeForRoaming
									(
										(_VS_CHAR*)tbstrEncPTAAppCtxtName,
										(_VS_CHAR*)tbstrDummyHostName,
										APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
										i_ncAddApplicationIfItDoesNotExist,
										tbstrUserName,
										&m_pbyteStorage,
										(unsigned int*) &m_dwStorageLen,
		//								(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,
		//								STORAGE_FILE_OPEN,
										(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
										nPasswdTimeOutPeriod,SetPasswdFn,
										(void*) this,
										m_boolResetPasswdFeature
									);

				}
				else
				{
					longRetVal = pEncPTAProtectedStorage->Initialize((_VS_CHAR*)tbstrEncPTAAppCtxtName,(_VS_CHAR*)tbstrDummyHostName,APPLICATION_ENCRYPTED/*(i_pvarPassword->vt == VT_BSTR?APPLICATION_ENCRYPTED:APPLICATION_DECRYPTED)*/,
						i_ncAddApplicationIfItDoesNotExist,(_VS_CHAR*)i_pvarWhichSmartCard->bstrVal,STORAGE_FILE_OPEN,(i_pvarPassword->vt == VT_BSTR?(_VS_CHAR*)i_pvarPassword->bstrVal:L""/*NULL*/),
						nPasswdTimeOutPeriod,SetPasswdFn, (void*) this);

				}
				if (longRetVal == VS_SUCCESS)
				{
					BOOL boolEncPTAProtectedStorageOpen = TRUE;
				/*Store the lock out tries, unlock period and password timeout in the application specific protected
				storage*/
					BOOL	boolWriteCalled = FALSE;
					_bstr_t tbstrAppPrefName = "";
					if(longRetVal == VS_SUCCESS)
					{

						tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
						longRetVal = pEncPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
						if (longRetVal == VS_SUCCESS)
						{
							boolWriteCalled = TRUE;
							longRetVal = pEncPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(nMaxTries)),
								sizeof(nMaxTries), 0);
						}
					}
					if(longRetVal == VS_SUCCESS)
					{
						tbstrAppPrefName = UNLOCK_PERIOD_NAME;
						longRetVal = pEncPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(nUnlockPeriod)),
							sizeof(nUnlockPeriod), 0);
					}
					if(longRetVal == VS_SUCCESS)
					{
						tbstrAppPrefName = TIMEOUT_PERIOD_NAME;
						longRetVal = pEncPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&(nPasswdTimeOutPeriod)),
							sizeof(nPasswdTimeOutPeriod), 0);
					}
					if (longRetVal == VS_SUCCESS)
					{
						_bstr_t tbstrAllDomains = _bstr_t("*,");
						longRetVal = pEncPTAProtectedStorage->SetApplicationReadOKDomains(1, (_VS_BYTE *)(_VS_CHAR *)tbstrAllDomains, 2*SysStringLen((BSTR)tbstrAllDomains));
					}
					if (longRetVal == VS_SUCCESS)
					{
						_bstr_t tbstrAllDomains = _bstr_t("*,");
						longRetVal = pEncPTAProtectedStorage->SetApplicationWriteOKDomains(1, (_VS_BYTE *)(_VS_CHAR *)tbstrAllDomains, 2*SysStringLen((BSTR)tbstrAllDomains));
					}
					if (boolWriteCalled == TRUE)
					{
						pEncPTAProtectedStorage->EndWrite();
						boolWriteCalled = FALSE;
					}
				}
			}
		}
	}

	if ((retVal != VS_SUCCESS) || (longRetVal != VS_SUCCESS))
	{
		/*Set lastinvalidtry*/
		if(retVal == E_INVALIDPASSWD || retVal == E_PROFLOCKEDOUT)
		{
			tbstrAppPrefName = LAST_INVALIDTRY_NAME;
			pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
			longRetVal = pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&ftLastInvalidTry),
				sizeof(ftLastInvalidTry), 0);
			pPTAProtectedStorage->EndWrite();

		}
		
		if(boolProtectedStorageOpen)
		{
			if ( TRUE == m_boolRoaming )
			{
				pProtectedStorage -> CloseForRoaming ((unsigned int*) &m_dwStorageChanged);

				if ( 1 == m_dwStorageChanged )
				{
					vsrmItemData.data =	m_pbyteStorage;
					vsrmItemData.len =	m_dwStorageLen;

					vsrmStatus =	VSRM_UpdateData
									(
										m_SessionHandle,
										&vsrmItemData
									);
					if ( VSRM_SUCCESS != vsrmStatus )
					{
						retVal =	E_ROAMING_UPDATE_FAILED;
					}
				}
			}
			else
			{
				pProtectedStorage->Close();
			}
		}
		
		delete pProtectedStorage;
		pProtectedStorage = NULL;

		if (boolIsItAnOldVersionProfile == TRUE)
		{
			pEncPTAProtectedStorage = NULL;
			boolEncPTAProtectedStorageOpen = FALSE;
		}

		if(boolPTAProtectedStorageOpen)
		{
			pPTAProtectedStorage->Close();
		}
		delete pPTAProtectedStorage;
		pPTAProtectedStorage = NULL;

		if (boolEncPTAProtectedStorageOpen == TRUE)
		{
			pEncPTAProtectedStorage->Close();
		}
		delete pEncPTAProtectedStorage;
		pEncPTAProtectedStorage = NULL;

	}

//	VSPTA_CLEAN_TBSTR(tbstrUserName)
//	VSPTA_CLEAN_TBSTR(tbstrDummyHostName)
//	VSPTA_CLEAN_TBSTR(tbstrPTAAppCtxtName)
//	VSPTA_CLEAN_TBSTR(tbstrAppPrefName)
	
	return retVal;
}

HRESULT CVirtualSmartCard::VSM_IsPrivKeyAvailable(PBYTE i_pbytePubKeyId, DWORD i_dwPubKeyIdSize)
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal;
	if(!boolUsePS)
		return E_VSCNOTINIT;

	PBYTE pbytePrivKey = NULL;
	_VS_DWORD dwPrivKeySize;
	longRetVal = BeginRead(pProtectedStorage, BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
	if(longRetVal == VS_SUCCESS)
	{
		unsigned int dwptrIsPrivateKeyExportable;
// Modified By: Infosys Technologies Ltd.
// Change Request: CR#21529
// Description: Pass additional parameter to fetch the value of 
// PrivateKeyExportable flag.
		longRetVal = pProtectedStorage-> GetPrivateKeyFromDB
			(
				i_pbytePubKeyId,
				i_dwPubKeyIdSize,
				&pbytePrivKey,
				&dwPrivKeySize,
				&dwptrIsPrivateKeyExportable
			);
// CR#21529: Modification Ends
		pProtectedStorage->EndRead();
	}

	if(longRetVal == E_VS_INVALID_PVK)
		retVal = E_KEYDOESNOTEXIST;
	else 
		retVal = longRetVal;
	
	pProtectedStorage->FreeMemoryBlob((void**)&pbytePrivKey);
	return retVal;
}

HRESULT CVirtualSmartCard::VSM_GetCert(int i_nCertNum, PBYTE o_pbyteCertBlob, DWORD* o_pdwCertBlobSize)
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal = VS_SUCCESS;

	/*Confirm that the card is open*/
	if(!boolUsePS)
		return E_VSCNOTINIT;

	/*Obtain the number of certs in the card*/
	_VS_DWORD dwNumOfCerts;
	longRetVal = BeginRead(pProtectedStorage, BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
	if(longRetVal == VS_SUCCESS)
	{
		longRetVal = pProtectedStorage->GetNumberOfCertificatesInDB(&dwNumOfCerts);
		if(longRetVal == VS_SUCCESS)
			longRetVal = pProtectedStorage->EndRead();
		else
			pProtectedStorage->EndRead();
	}

	/*Make sure that the cert number specified is available in the card*/
	if(longRetVal == VS_SUCCESS)
	{
		if((unsigned int)i_nCertNum >= dwNumOfCerts)
			longRetVal = E_CERTNOTFOUND;
	}

	/*Obtain the cert whose number is specified from the card*/
	PBYTE pbyteCertBlob;
	_VS_DWORD dwCertPtr;
	if(longRetVal == VS_SUCCESS)
	{
		longRetVal = BeginRead(pProtectedStorage, BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		if(longRetVal == VS_SUCCESS)
		{
			longRetVal = pProtectedStorage->GetCertificateFromDB(i_nCertNum,&pbyteCertBlob,(_VS_DWORD*)o_pdwCertBlobSize,&dwCertPtr);
			if(longRetVal == VS_SUCCESS)
			{
				if(o_pbyteCertBlob)
					memcpy(o_pbyteCertBlob,pbyteCertBlob,(unsigned int)(*o_pdwCertBlobSize));
				longRetVal = pProtectedStorage->FreeMemoryBlob((void**)&pbyteCertBlob);
			}

			if(longRetVal == VS_SUCCESS)
				longRetVal = pProtectedStorage->EndRead();
			else
				pProtectedStorage->EndRead();
		}
	}

	retVal = longRetVal;

	return retVal;
}

HRESULT CVirtualSmartCard::VSM_SetCertPref(int i_nCertNum, _bstr_t& i_tbstrPrefName, PBYTE i_pbytePrefVal,
					int i_nPrefValSize)
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal;

	if(!boolUsePS)
		return E_VSCNOTINIT;

	longRetVal = BeginWrite(pProtectedStorage, BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
	
	PBYTE pbyteCertBlob;
	_VS_DWORD dwCertBlobSize;
	_VS_DWORD dwCertPtr;
	if(longRetVal == VS_SUCCESS)
	{
		longRetVal = pProtectedStorage->GetCertificateFromDB(i_nCertNum,&pbyteCertBlob,(_VS_DWORD*)&dwCertBlobSize,&dwCertPtr);
		if(longRetVal == VS_SUCCESS)
		{
			//Set this certs preference
			longRetVal = pProtectedStorage->SetCertificatePreference(dwCertPtr,(_VS_CHAR*)i_tbstrPrefName,i_pbytePrefVal,i_nPrefValSize);
			if(longRetVal == VS_SUCCESS)
				longRetVal =  pProtectedStorage->FreeMemoryBlob((void**)&pbyteCertBlob);
			else
				pProtectedStorage->FreeMemoryBlob((void**)&pbyteCertBlob);
		}

		if(longRetVal == VS_SUCCESS)
			longRetVal = pProtectedStorage->EndWrite();
		else
			pProtectedStorage->EndWrite();
	}

	retVal = longRetVal;

	return retVal;
}

HRESULT CVirtualSmartCard::VSM_GetCertPref(int i_nCertNum, _bstr_t& i_tbstrPrefName, PBYTE o_pbytePrefVal,
					int* o_pnPrefValSize)
{
	HRESULT retVal = S_OK;
	_VS_LONG longRetVal;

	if(!boolUsePS)
		return E_VSCNOTINIT;

	longRetVal = BeginRead(pProtectedStorage, BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
	
	PBYTE pbyteCertBlob;
	_VS_DWORD dwCertPtr;
	_VS_DWORD dwCertBlobSize;
	if(longRetVal == VS_SUCCESS)
	{
		longRetVal = pProtectedStorage->GetCertificateFromDB(i_nCertNum,&pbyteCertBlob,(_VS_DWORD*)&dwCertBlobSize,&dwCertPtr);
		if(longRetVal == VS_SUCCESS)
		{
			_VS_BYTE* pbytePrefVal;

			//Set this certs preference
			longRetVal = pProtectedStorage->GetCertificatePreference(dwCertPtr,(_VS_CHAR*)i_tbstrPrefName,&pbytePrefVal,(_VS_DWORD*)o_pnPrefValSize);
			if(longRetVal == VS_SUCCESS)
			{
				if(o_pbytePrefVal)
					memcpy(o_pbytePrefVal, pbytePrefVal, (*o_pnPrefValSize));

				longRetVal = pProtectedStorage->FreeMemoryBlob((void**)&pbytePrefVal);
			}

			if(longRetVal == VS_SUCCESS)
				longRetVal =  pProtectedStorage->FreeMemoryBlob((void**)&pbyteCertBlob);
			else
				pProtectedStorage->FreeMemoryBlob((void**)&pbyteCertBlob);
		}

		if(longRetVal == VS_SUCCESS)
			longRetVal = pProtectedStorage->EndRead();
		else
			pProtectedStorage->EndRead();
	}

	if(longRetVal == E_VS_INVALID_CERT_PREF)
		retVal = E_CERTPREFNOTFOUND;
	else 
		retVal = longRetVal;

	return retVal;
}

//-------------------SAMEER ABOVE------------------------------------------------------------------------
// Modified by - Infosys Technologies Ltd. 
// Change Request - CR#21529
// Description - Pass the out parameter dwptrIsPrivateKeyExportable to the GetPrivateKeyFromDB function
// CR#21529 - Begin
// Date Modified - July 2, 2004
// Pass an parameter to the function. Default value for this parameter is set to 1.
// This parameter is the bIsPrivateKeyExportable flag. 

HRESULT		CVirtualSmartCard::VSM_GenKey
(
//	const CHAR*			i_cszContainerName,
	const int			i_cnAlgid,		//	signature / exchange RSA key
	const int			i_cnSizeOfKey,	//	size
	const DWORD			i_cdwFlags,		//	EXPORTABLE / NOT_EXPORTABLE
	BYTE*				o_pbyteCorrPubKey,
	DWORD*				o_pdwCorrPubKeyLen,
	BOOL				i_bIsPrivateKeyExportable
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	BOOL						boolSuccessFlag				=	FALSE;

	A_RSA_KEY					RSA_PrivateKey;
	A_RSA_KEY					RSA_PublicKey;

	CSP_PubKeyHash*				pstructPubKeyHash			=	NULL;

	BYTE*						pbytePrivateKey				=	NULL;
	DWORD						dwPrivateKeyLen				=	0;

	BYTE*						pbytePublicKey				=	NULL;
 	DWORD						dwPublicKeyLen				=	0;

	DWORD						dwKeyHashLen				=	VS_CSP_SHA1_LEN;

	BYTE*						pbyteBase64PubKey			=	NULL;
	DWORD						dwBase64PubKeyLen			=	0;
	_bstr_t						tbstrBase64PubKey;

	BOOL						boolCallEnd					=	FALSE;

/*
	BYTE*						pbyteContainerContents		=	NULL;
	DWORD						dwContainerContentsLen		=	0;
	CSP_Key_Container*			pstructContainer			=	NULL;
	BYTE						pbytePubKeyHash [VS_CSP_SHA1_LEN];
*/

	while (1)
	{
			//	check input parameterse
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwCorrPubKeyLen)
		if ( NULL == o_pbyteCorrPubKey )
		{
			*o_pdwCorrPubKeyLen =	VS_CSP_SHA1_LEN;
			
			hResult =	S_OK;
			break;
		}
		if ( VS_CSP_SHA1_LEN > *o_pdwCorrPubKeyLen )
		{
			hResult =	NTE_BAD_LEN;
			break;
		}

		//tbstrContainerName	=	i_cszContainerName;

		VSCSP_CHECK_SIZE_OF_RSA_KEY(i_cnSizeOfKey)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginWrite
					(
						pProtectedStorage,
						NO_BLOCK_RETURN_ERROR,
						0
					);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

					//	generate the key pair
		nResult =	DoRSAKeyGen
					(
						i_cnSizeOfKey,	//	algo	Exchange or Signature
						&RSA_PrivateKey,
						&RSA_PublicKey
					);
		VSCSP_CHECK_NRESULT

					//	hash the public key
		hResult =	HashPublicKey
					(
						&RSA_PublicKey,
						m_pbytePubKeyHash
					);
		VSM_CHECK_HRESULT

					//	faltten the public key
		hResult =	GetBlobFromKey
					(
						&RSA_PublicKey,
						&pbytePublicKey,
						&dwPublicKeyLen
					);
		VSM_CHECK_HRESULT


				//	the public key is stored as an information blob (name value pair)
				//	the hash of the public key could have a '\0'
				//	so base 64 encode the public key hash

			//	get the size for the base 64 encoded byte blob
		_Base64Encode
		(
			(CHAR*) m_pbytePubKeyHash,
			VS_CSP_SHA1_LEN,
			NULL,
			&dwBase64PubKeyLen
		);

				//	allocate memory
		pbyteBase64PubKey =	new BYTE [dwBase64PubKeyLen + 1];
		CHECK_ALLOCATED_MEMORY (pbyteBase64PubKey)

				//	convert the string
		_Base64Encode
		(
			(CHAR*) m_pbytePubKeyHash,
			VS_CSP_SHA1_LEN,
			(CHAR*) pbyteBase64PubKey,
			&dwBase64PubKeyLen
		);

				//	add a end of string 
		pbyteBase64PubKey [dwBase64PubKeyLen] =	'\0';

				//	assign the base 64 encoded byte blob to a _bstr_t
		tbstrBase64PubKey =	(CHAR*) pbyteBase64PubKey;


					//	add the public key in the protected storage as an information blob
		hResult =	pProtectedStorage -> AddInformationBlobToDB
					(
						tbstrBase64PubKey,
						pbytePublicKey,
						dwPublicKeyLen
					);
		VSM_CHECK_HRESULT

						//	flatten the private key 
		hResult =	GetBlobFromKey
					(
						&RSA_PrivateKey,
						&pbytePrivateKey,
						&dwPrivateKeyLen
					);
		VSM_CHECK_HRESULT

	// Modified by - Infosys Technologies Ltd. 
	// Change Request - CR#21529
	// Description - The flag for making the private key exportable/non-exportable
	// would be passed to the function AddPrivateKeyToDB.
	// CR#21529 - Begin
	// Date Modified - July 5, 2004
		DWORD dwIsPrivateKeyExportable = (DWORD) i_bIsPrivateKeyExportable;
		
		
						//	and store it in the profile
		hResult =	pProtectedStorage -> AddPrivateKeyToDB
					(
						pbytePrivateKey,
						dwPrivateKeyLen,
						m_pbytePubKeyHash,
						dwKeyHashLen,
						dwIsPrivateKeyExportable
					);
		// CR#21529 - End 
		VSM_CHECK_HRESULT

		*o_pdwCorrPubKeyLen	=	VS_CSP_SHA1_LEN;
		memcpy
		(
			(void*) o_pbyteCorrPubKey,
			(const void*) m_pbytePubKeyHash,
			*o_pdwCorrPubKeyLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndWrite ();
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbytePrivateKey, dwPrivateKeyLen)
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbytePublicKey, dwPublicKeyLen)

	return	hResult;
}


HRESULT		CVirtualSmartCard::VSM_DestroyKey
(
	const BYTE*			i_cpbyteCorrPubKey,
	const DWORD*		i_cpdwCorrPubKeyLen
)
{
	return	S_OK;
/*
	HRESULT						hResult				=	E_FAIL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrPubKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpdwCorrPubKeyLen)
	}	//	end		while (1)

	return	hResult;
*/
}


HRESULT		CVirtualSmartCard::VSM_GetKeyParam
(
	const BYTE*			i_cpbyteCorrPubKey,
	const DWORD			i_cdwCorrPubKeyLen,
	const DWORD			i_cdwParam,		//	KP_ALGID only. the rest of the parameters will not be supported
	BYTE*				o_pbData,		//	the return data
	DWORD*				o_pdwDataLen	//	the return data length
)
{
	HRESULT						hResult						=	E_FAIL;

	BYTE*						pbyteContainerContents		=	NULL;
	DWORD						dwContainerContentsLen		=	0;
	CSP_Key_Container*			pstructContainer			=	NULL;
//	BYTE						pbytePubKeyHash [VS_CSP_SHA1_LEN];

	int							nMemcmp						=	999;

	CSP_PubKeyHash*				pstructPubKeyHash			=	NULL;

	DWORD						dwAlgo						=	999;
	BOOL						boolFound					=	FALSE;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrPubKey)
		if ( VS_CSP_SHA1_LEN != i_cdwCorrPubKeyLen )
		{
			hResult =	ERROR_INVALID_HANDLE;
			break;
		}
		if ( sizeof (DWORD) < *o_pdwDataLen )
		{
				//	the only params which is supported is Algo 
				//	so a DWORD is enough for the key params
			hResult =	ERROR_MORE_DATA;
			break;
		}

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
					(
						pProtectedStorage,
						NO_BLOCK_RETURN_ERROR,
						0
					);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

					//	get the contain contents information blob
		hResult =	pProtectedStorage -> GetInformationBlob
					(
						tbstrContainerName,
						(unsigned char**) &pbyteContainerContents,
						(unsigned int*) &dwContainerContentsLen
					);
		VSM_CHECK_HRESULT

		pstructContainer =	(CSP_Key_Container*) pbyteContainerContents;

			//	check if the exchange key exists
		if ( VS_CSP_KEY_EXISTS != (pstructContainer -> structXchg).dwExists )
		{
					//	compare the input pub key blob with the exchange pub key blob from the
					//	container contents
			nMemcmp =	memcmp
						(
							(const void*) i_cpbyteCorrPubKey,
							(const void*) (pstructContainer -> structXchg).pbytePubKeyHash,
							i_cdwCorrPubKeyLen
						);
			if ( 0 == nMemcmp )
			{		//	the key passed is the exchange key
				dwAlgo		=	VS_RSA_KEYX;
				boolFound	=	TRUE;
			}
		}
			//	check if the signature key exists. if the matching key has
			//	already been found then skip.
		if ( VS_CSP_KEY_EXISTS != (pstructContainer -> structSign).dwExists && FALSE == boolFound)
		{
					//	compare the input pub key blob with the signature pub key blob from
					//	the container contents
			nMemcmp =	memcmp
						(
							(const void*) i_cpbyteCorrPubKey,
							(const void*) (pstructContainer -> structSign).pbytePubKeyHash,
							i_cdwCorrPubKeyLen
						);
			if ( 0 == nMemcmp )
			{
						//	the key passed is the signature key
				dwAlgo		=	VS_RSA_SIGN;
				boolFound	=	TRUE;
			}
		}
		
		if ( FALSE == boolFound )
		{
				//	both the keys are not matching. so return error
			hResult =	ERROR_INVALID_HANDLE;
			break;
		}

			//	copy the algo in the out byte blob
		memcpy
		(
			(void*) o_pbData,
			(const void*) &dwAlgo,
			sizeof (DWORD)
		);
		*o_pdwDataLen =	sizeof (DWORD);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbyteContainerContents)

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	return	hResult;
}


//
//	Anand	Mar 23, 2001
//
//	This function was ignoring the i_cdwBlobType input parameter.
//	The function used to return only the public key
//
//	The function is now modified to return the public or the private key.
//	2 hash defines are added in cspglobals.h to indicate values to be used
//	by i_cdwBlobType
//
HRESULT		CVirtualSmartCard::VSM_ExportKey
(
	const BYTE*			i_cpbyteCorrPubKey,
	const DWORD			i_cdwCorrPubKeyLen,
	const DWORD			i_cdwTypeOfKeyForEncryption,	//	IGNORED	//	symmetric / asymmetric
	const BYTE*			i_cpbyteEncryptionKey,			//	IGNORED
	const DWORD			i_cdwEncryptionKeyLength,		//	IGNORED
	const DWORD			i_cdwBlobType,
	BYTE*				o_pbData,
	DWORD*				o_pdwDataLen
)
{
	HRESULT						hResult					=	E_FAIL;

	BYTE*				pbyteBase64PubKey				=	NULL;
	DWORD				dwBase64PubKeyLen				=	0;

	BYTE*				pbyteKey						=	NULL;
	DWORD				dwKeyLen						=	0;

	_bstr_t				tbstrPubKey;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrPubKey)
		if ( VS_CSP_SHA1_LEN != i_cdwCorrPubKeyLen )
		{
			hResult =	ERROR_INVALID_HANDLE;
			break;
		}

		if ( (VS_CSP_EXPORT_PUBLIC_KEY != i_cdwBlobType) && (VS_CSP_EXPORT_PRIVATE_KEY != i_cdwBlobType) )
		{
			hResult =	E_VS_WRONG_KEY_TYPE;
			break;
		}

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;
		
		if (VS_CSP_EXPORT_PUBLIC_KEY == i_cdwBlobType)
		{

					//	the public key is stored as an information blob (name value pair)
					//	the hash of the public key could have a '\0'
					//	so base 64 encode the public key hash

				//	get the size for the base 64 encoded byte blob
			_Base64Encode
			(
				(CHAR*) i_cpbyteCorrPubKey,
				i_cdwCorrPubKeyLen,
				NULL,
				&dwBase64PubKeyLen
			);

					//	allocate memory
			pbyteBase64PubKey =	new BYTE [dwBase64PubKeyLen + 1];
			CHECK_ALLOCATED_MEMORY (pbyteBase64PubKey)

					//	convert the string
			_Base64Encode
			(
				(CHAR*) i_cpbyteCorrPubKey,
				i_cdwCorrPubKeyLen,
				(CHAR*) pbyteBase64PubKey,
				&dwBase64PubKeyLen
			);

					//	add a end of string 
			pbyteBase64PubKey [dwBase64PubKeyLen] =	'\0';

					//	assign the base 64 encoded byte blob to a _bstr_t
			tbstrPubKey =	(CHAR*) pbyteBase64PubKey;

			VSCSP_CHECK_IF_PS_OBJECT_READY

						//	get the contain contents information blob
			hResult =	pProtectedStorage -> GetInformationBlob
						(
							tbstrPubKey,
							(unsigned char**) &pbyteKey,
							(unsigned int*) &dwKeyLen
						);
			VSM_CHECK_HRESULT
		}	//	end if part if (VS_CSP_EXPORT_PUBLIC_KEY != i_cdwBlobType)
		else
		{
				//	it is already checked that i_cdwBlobType is either VS_CSP_EXPORT_PUBLIC_KEY
				//	or VS_CSP_EXPORT_PRIVATE_KEY
				//
				//	since it came to else its VS_CSP_EXPORT_PRIVATE_KEY
			unsigned int dwptrIsPrivateKeyExportable;
			hResult =	pProtectedStorage -> GetPrivateKeyFromDB
						(
							i_cpbyteCorrPubKey,
							i_cdwCorrPubKeyLen,
							(unsigned char**) &pbyteKey,
							(unsigned int*) &dwKeyLen,
							&dwptrIsPrivateKeyExportable
						);

		// Change Request (CR#21529): Make Private Key Non-Exportable.
		// Modified by: Infosys Technologies Ltd.
		// This CR proposes enforcing an additional flag to prevent export of key
		// out of the PTA profile.  

		/*  Modification Log
			Version		Date			Author				Description
		-------------------------------------------------------------------------------------------------------------------------------
			1.01		05-Jul-2002		Amol Tavkar			CR#21529: Check to detect whether the 
															key has been marked as non-exportable.
		-------------------------------------------------------------------------------------------------------------------------------
		*/	
		// CR#21529 Begins
		
			// Check if the key is made non-exportable.
			if (!(BOOL)dwptrIsPrivateKeyExportable)
			{
				// If the key is made non-exportable, the send an error response. 
				// This will cause an error page to be displayed to the user, saying
				// that the key has been marked as non-exportable by the user.
				return E_P12E_KEYNOTEXPORTABLE;
			}
		// CR#21529 Ends

			VSM_CHECK_HRESULT

		}	//	end else part if (VS_CSP_EXPORT_PUBLIC_KEY != i_cdwBlobType)

		if ( NULL == o_pbData )
		{
			*o_pdwDataLen =	dwKeyLen;
			hResult =	VS_SUCCESS;
			break;
		}

		if ( dwKeyLen > *o_pdwDataLen )
		{
			*o_pdwDataLen =	dwKeyLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

		*o_pdwDataLen =	dwKeyLen;
		memcpy
		(
			o_pbData,
			pbyteKey,
			*o_pdwDataLen
		);
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbyteKey)

	if ( TRUE == boolCallEnd )
	{
		hResult =	pProtectedStorage -> EndRead ();
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteBase64PubKey, dwBase64PubKeyLen)

	return	hResult;
}


HRESULT		CVirtualSmartCard::VSM_ImportKey
(
	const BYTE*			i_cpbData,
	const DWORD			i_cdwDataLen,
	const BYTE*			i_pbytePubKeyHash,
	const DWORD			i_cdwTypeOfKeyForEncryption,	//	IGNORED //	symmetric / asymmetric
	const BYTE*			i_cpbyteEncryptionKey,			//	IGNORED
	const DWORD			i_cdwEncryptionKeyLength,		//	IGNORED
	const DWORD			i_cdwFlags,			//	IGNORED	//	EXPORTABLE / NOT_EXPORTABLE
	BYTE*				o_pbyteCorrPubKey,
	DWORD*				o_pdwCorrPubKeyLen
)
{
	HRESULT						hResult					=	E_FAIL;

	BYTE*				pbyteBase64PubKey				=	NULL;
	DWORD				dwBase64PubKeyLen				=	0;

	BYTE				pbytePubKeyHash	[VS_CSP_SHA1_LEN];
//	DWORD				dwPubKeyHashLen					=	0;

	_bstr_t				tbstrBase64PubKey;

	BOOL						boolCallEnd					=	FALSE;

	A_RSA_KEY					RSA_PublicKey;

	// Change Request (CR#21529): Make Private Key Non-Exportable.
	// Modified by: Infosys Technologies Ltd.
	// This CR proposes enforcing an additional flag to prevent export/import of key
	// out of the PTA profile.  

	/*  Modification Log
		Version		Date			Author				Description
	-------------------------------------------------------------------------------------------------------------------------------
		1.01		25-Jun-2002		Infosys 
									Technologies		CR#21529: Check to detect whether the 
									Ltd.				key has been marked as non-exportable.
	-------------------------------------------------------------------------------------------------------------------------------
	*/	
	// CR#21529 Begins
		// Check if the key is made non-exportable.
		/*if (!(BOOL)dwptrIsPrivateKeyExportable)
		{
			// If the key is made non-exportable, the send an error response. 
			// This will cause an error page to be displayed to the user, saying
			// that the key has been marked as non-exportable by the user.
			return E_P12E_KEYNOTEXPORTABLE;
		}*/
	// CR#21529 Ends

	while (1)
	{
		VSCSP_CHECK_IF_PS_OBJECT_READY

		if ( NULL == o_pbyteCorrPubKey )
		{
			*o_pdwCorrPubKeyLen =	VS_CSP_SHA1_LEN;
			hResult =	VS_SUCCESS;
			break;
		}
		else
		{
			if ( VS_CSP_SHA1_LEN < *o_pdwCorrPubKeyLen )
			{
				*o_pdwCorrPubKeyLen =	VS_CSP_SHA1_LEN;
				hResult =	ERROR_MORE_DATA;
				break;
			}
		}

		hResult =	BeginWrite
					(
						pProtectedStorage,
						NO_BLOCK_RETURN_ERROR,
						0
					);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		if(!i_pbytePubKeyHash)
		{
		hResult =	GetKeyFromBlob
					(
						i_cpbData,
						i_cdwDataLen,
						&RSA_PublicKey
					);
		VSM_CHECK_HRESULT

					//	hash the public key
		hResult =	HashPublicKey
					(
						&RSA_PublicKey,
						pbytePubKeyHash
					);
		VSM_CHECK_HRESULT

					//	the public key is stored as an information blob (name value pair)
					//	the hash of the public key could have a '\0'
					//	so base 64 encode the public key hash
					//	get the size for the base 64 encoded byte blob
			_Base64Encode
			(
				(CHAR*) pbytePubKeyHash,
				VS_CSP_SHA1_LEN,
				NULL,
				&dwBase64PubKeyLen
			); 

					//	allocate memory
			pbyteBase64PubKey =	new BYTE [dwBase64PubKeyLen + 1];
			CHECK_ALLOCATED_MEMORY (pbyteBase64PubKey)

					//	convert the string
			_Base64Encode
			(
				(CHAR*) pbytePubKeyHash,
				VS_CSP_SHA1_LEN,
				(CHAR*) pbyteBase64PubKey,
				&dwBase64PubKeyLen
			);

					//	add a end of string 
			pbyteBase64PubKey [dwBase64PubKeyLen] =	'\0';

					//	assign the base 64 encoded byte blob to a _bstr_t
			tbstrBase64PubKey =	(CHAR*) pbyteBase64PubKey;

						//	add the public key in the protected storage as an information blob
			hResult =	pProtectedStorage -> AddInformationBlobToDB
						(
							tbstrBase64PubKey,
							i_cpbData,
							i_cdwDataLen
						);
		}
		else
		{
			//This is a private key blob
			memcpy(pbytePubKeyHash,i_pbytePubKeyHash,VS_CSP_SHA1_LEN);
			DWORD dwIsPrivateKeyExportable = 1;
			hResult = pProtectedStorage -> AddPrivateKeyToDB
					(
						i_cpbData,
						i_cdwDataLen,
						i_pbytePubKeyHash,
						VS_CSP_SHA1_LEN,
						dwIsPrivateKeyExportable
					);
		}

#if 1
		if( (E_VS_INFO_BLOB_ALREADY_EXISTS != hResult) && (E_VS_PVK_ALREADY_EXISTS != hResult) )
			VSM_CHECK_HRESULT
#endif

		memcpy
		(
			(void*) o_pbyteCorrPubKey,
			(const void*) pbytePubKeyHash,
			VS_CSP_SHA1_LEN
		);
		*o_pdwCorrPubKeyLen =	VS_CSP_SHA1_LEN;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndWrite ();
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteBase64PubKey, dwBase64PubKeyLen)

	return	hResult;
}



HRESULT		CVirtualSmartCard::VSM_EncryptBegin
(
	const BYTE*			i_cpbyteCorrPubKeyHash,
	const DWORD			i_cdwCorrPubKeyHashLen,
	void**				o_ppvoidContext
)
{
	HRESULT							hResult						=	E_FAIL;
	int								nResult						=	999;
	
//	WCHAR*							pwszBase64KeyHash			=	NULL;
	_bstr_t							tbstrBase64PubKey;

	BYTE*							pbytePubKey					=	NULL;
	DWORD							dwPubKeyLen					=	0;

	BYTE*							pbyteBase64PubKey			=	NULL;
	DWORD							dwBase64PubKeyLen			=	0;

	BOOL							boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrPubKeyHash)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppvoidContext)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
					(
						pProtectedStorage,
						NO_BLOCK_RETURN_ERROR,
						0
					);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

			//	convert the i_cpbyteCorrPubKeyHash to a base64 encoded string
			//	get the size for the base 64 encoded byte blob
		_Base64Encode
		(
			(CHAR*) i_cpbyteCorrPubKeyHash,
			VS_CSP_SHA1_LEN,
			NULL,
			&dwBase64PubKeyLen
		);

				//	allocate memory
		pbyteBase64PubKey =	new BYTE [dwBase64PubKeyLen + 1];
		CHECK_ALLOCATED_MEMORY (pbyteBase64PubKey)

				//	convert the string
		_Base64Encode
		(
			(CHAR*) i_cpbyteCorrPubKeyHash,
			VS_CSP_SHA1_LEN,
			(CHAR*) pbyteBase64PubKey,
			&dwBase64PubKeyLen
		);

				//	add a end of string 
		pbyteBase64PubKey [dwBase64PubKeyLen] =	'\0';

				//	assign the base 64 encoded byte blob to a _bstr_t
		tbstrBase64PubKey =	(CHAR*) pbyteBase64PubKey;

					//	get the key from the protected storage
		hResult =	pProtectedStorage -> GetInformationBlob
					(
						tbstrBase64PubKey,
						(unsigned char**) &pbytePubKey,
						(unsigned int*) &dwPubKeyLen
					);
		VSM_CHECK_HRESULT

					//	get the RSA key from the blob
		hResult =	GetKeyFromBlob
					(
						pbytePubKey,
						dwPubKeyLen,
						&RSA_Enc_PublicKey
					);
		VSM_CHECK_HRESULT

		pRSA_Context =	(RSA_Context*) new RSA_Context;

		pRSA_Context -> dwSizeOfStruct	=	sizeof (RSA_Context);
		pRSA_Context -> dwRemainder		=	0;

					//	begin the rsa encryption
		nResult =	RSADataBegin
					(
						&RSA_Enc_PublicKey,
						(void**) &(pRSA_Context -> pContext)
					);
		VSCSP_CHECK_NRESULT

		*o_ppvoidContext =	pRSA_Context;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbytePubKey)
	dwPubKeyLen =	0;

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteBase64PubKey, dwBase64PubKeyLen)
	dwBase64PubKeyLen =	0;
//	VSPTA_CLEAN_TBSTR(tbstrBase64PubKey)

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_EncryptUpdate
(
	const void*			i_cpvoidContext,
	const BOOL			i_cboolFinal,
	const BYTE*			i_cpbData,
	const DWORD			i_cdwDataLen,
	BYTE*				o_pbyteOutData,
	DWORD*				o_pdwOutDataLen
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	RSA_Context*				pTempRSAContext				=	NULL;

	BYTE*						pbytePaddedData				=	NULL;
	DWORD						dwPaddedDataLen				=	0;
//	BYTE*						pbyteRev					=	NULL;
//	DWORD						dwRevLen					=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpvoidContext)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cdwDataLen)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pbyteOutData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwOutDataLen)

		pTempRSAContext =	(RSA_Context*) i_cpvoidContext;

		if ( sizeof (RSA_Context) != pTempRSAContext -> dwSizeOfStruct )
		{
			hResult =	NTE_BAD_UID;
			break;
		}

					//	pad the data
		hResult =	PadDataForEncryption
					(
						i_cpbData,
						i_cdwDataLen,
						&pbytePaddedData,
						&dwPaddedDataLen
					);
		VSM_CHECK_HRESULT

		if ( NULL == o_pbyteOutData )
		{
			*o_pdwOutDataLen =	dwPaddedDataLen;
			hResult =	VS_SUCCESS;
			break;
		}
		if ( dwPaddedDataLen > *o_pdwOutDataLen )
		{
			*o_pdwOutDataLen =	dwPaddedDataLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

//		dwRevLen =	*o_pdwOutDataLen;
//		pbyteRev =	new BYTE [dwRevLen];

					//	call the RSA update function
		nResult =	RSADataUpdate
					(
						(void*) (pTempRSAContext -> pContext),
						(unsigned char*) pbytePaddedData,
						(unsigned int) dwPaddedDataLen,
//						(unsigned char*) pbyteRev,
						(unsigned char*) o_pbyteOutData,
						(unsigned int*) o_pdwOutDataLen
					);
		VSCSP_CHECK_NRESULT

/*
		for ( DWORD z = 0; z < *o_pdwOutDataLen; z++ )
		{
			o_pbyteOutData [z] =	pbyteRev [ *o_pdwOutDataLen - z - 1];
		}
*/

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ( pbytePaddedData, dwPaddedDataLen )
//	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ( pbyteRev, dwRevLen )

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_EncryptEnd
(
	const void*			i_cpvoidContext
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	RSA_Context*				pTempRSAContext				=	NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpvoidContext)

		pTempRSAContext =	(RSA_Context*) i_cpvoidContext;
		if ( sizeof (RSA_Context) != pTempRSAContext -> dwSizeOfStruct )
		{
			hResult =	NTE_BAD_UID;
			break;
		}

					//	destroy the encryption context
		nResult =	RSADataEnd
					(
						(void*) (pTempRSAContext -> pContext)
					);
		VSCSP_CHECK_NRESULT

		pTempRSAContext -> dwRemainder	=	0;
		pTempRSAContext -> dwRemainder	=	0;
		pTempRSAContext -> pContext		=	NULL;

		VSCSP_CHECK_FOR_NULL_AND_DELETE (pTempRSAContext)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_DecryptBegin
(
	const BYTE*			i_cpbyteCorrPubKey,
	const DWORD			i_cdwCorrPubKeyLen,
	void**				o_ppvoidContext
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	BYTE*						pbytePrivateKey				=	NULL;
	DWORD						dwPrivateKeyLen				=	0;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrPubKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_ppvoidContext)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
					(
						pProtectedStorage,
						NO_BLOCK_RETURN_ERROR,
						0
					);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;
		// Modified by - Infosys Technologies Ltd. 
		// Change Request - CR#21529
		// Description - Pass the out parameter dwptrIsPrivateKeyExportable to the GetPrivateKeyFromDB function
		// CR#21529 - Begin
		// Date Modified - July 2, 2004
		// Pass an parameter to the function and default this parameter to 1. 
		// This parameter is the bIsPrivateKeyExportable flag. 

		unsigned int dwptrIsPrivateKeyExportable;
					//	get the private key
		hResult =	pProtectedStorage -> GetPrivateKeyFromDB
					(
						(unsigned char*) i_cpbyteCorrPubKey,
						(unsigned int) i_cdwCorrPubKeyLen,
						(unsigned char**) &pbytePrivateKey,
						(unsigned int*) &dwPrivateKeyLen,
						&dwptrIsPrivateKeyExportable
					);
		VSM_CHECK_HRESULT

					//	convert the private key from a byte blob to a key struct
		hResult =	GetKeyFromBlob
					(
						(const BYTE*) pbytePrivateKey,
						(const DWORD) dwPrivateKeyLen,
						&RSA_Dec_PrivateKey
					);
		VSM_CHECK_HRESULT

		pRSA_Context =	(RSA_Context*) new RSA_Context;

		pRSA_Context -> dwSizeOfStruct	=	sizeof (RSA_Context);
		pRSA_Context -> dwRemainder		=	0;

					//	begin the rsa decryption
		nResult =	RSADataBegin
					(
						&RSA_Dec_PrivateKey,
						(void**) &(pRSA_Context -> pContext)
					);
		VSCSP_CHECK_NRESULT

		*o_ppvoidContext =	pRSA_Context;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbytePrivateKey)
	dwPrivateKeyLen =	0;
	
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_DecryptUpdate
(
	const void*			i_cpvoidContext,
	const BOOL			i_cboolFinal,
	const BYTE*			i_cpbData,
	const DWORD			i_cdwDataLen,
	BYTE*				o_pbyteOutData,
	DWORD*				o_pdwOutDataLen
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	RSA_Context*				pTempRSAContext				=	NULL;

	BYTE*						pbyteUnPadedData			=	NULL;
	DWORD						dwUnPadedDataLen			=	0;

	BYTE*						pbytePadedData				=	NULL;
	DWORD						dwPadedDataLen				=	0;

//	BYTE*						pbyteRev					=	NULL;
//	DWORD						dwRevLen					=	0;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpvoidContext)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cdwDataLen)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pbyteOutData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwOutDataLen)
		if ( NULL == o_pbyteOutData )
		{
			*o_pdwOutDataLen =	i_cdwDataLen;
			hResult =	VS_SUCCESS;
			break;
		}

		pTempRSAContext =	(RSA_Context*) i_cpvoidContext;

		if ( sizeof (RSA_Context) != pTempRSAContext -> dwSizeOfStruct )
		{
			hResult =	NTE_BAD_UID;
			break;
		}

		dwPadedDataLen =	i_cdwDataLen;
		pbytePadedData =	new BYTE [dwPadedDataLen];
		CHECK_ALLOCATED_MEMORY (pbytePadedData)

//		pbyteRev =	new BYTE [dwPadedDataLen];
//		dwRevLen =	dwPadedDataLen;
//		for ( DWORD z = 0; z < dwPadedDataLen; z++ )
//		{
//			pbyteRev [z] =	i_cpbData [ dwPadedDataLen - z - 1];
//		}

		nResult =	RSADataUpdate
					(
						(void*) (pTempRSAContext -> pContext),
//						(unsigned char*) pbyteRev,
						(unsigned char*) i_cpbData,
						(unsigned int) i_cdwDataLen,
						(unsigned char*) pbytePadedData,
						(unsigned int*) &dwPadedDataLen
					);
		VSCSP_CHECK_NRESULT

		hResult =	UnPadDataForDecryption
					(
						pbytePadedData,
						dwPadedDataLen,
						&pbyteUnPadedData,
						&dwUnPadedDataLen
					);
		VSM_CHECK_HRESULT

		if ( dwUnPadedDataLen > *o_pdwOutDataLen )
		{
			*o_pdwOutDataLen =	dwUnPadedDataLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

		memcpy
		(
			(void*) o_pbyteOutData,
			(const void*) pbyteUnPadedData,
			dwUnPadedDataLen
		);
		*o_pdwOutDataLen =	dwUnPadedDataLen;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ( pbyteUnPadedData, dwUnPadedDataLen )
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ( pbytePadedData, dwPadedDataLen )
//	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE ( pbyteRev, dwRevLen )

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_DecryptEnd
(
	const void*			i_cpvoidContext
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	RSA_Context*				pTempRSAContext				=	NULL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpvoidContext)

		pTempRSAContext =	(RSA_Context*) i_cpvoidContext;
		if ( sizeof (RSA_Context) != pTempRSAContext -> dwSizeOfStruct )
		{
			hResult =	NTE_BAD_UID;
			break;
		}

					//	destroy the decryption context
		nResult =	RSADataEnd
					(
						(void*) (pTempRSAContext -> pContext)
					);
		VSCSP_CHECK_NRESULT

		pTempRSAContext -> dwRemainder	=	0;
		pTempRSAContext -> dwRemainder	=	0;
		pTempRSAContext -> pContext		=	NULL;

		VSCSP_CHECK_FOR_NULL_AND_DELETE (pTempRSAContext)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_SignData
(
	const BYTE*			i_cpbyteCorrSignPubKey,
	const DWORD			i_cdwCorrSignPubKeyLen,
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	const DWORD			i_cdwHashAlgID,
	const BOOL			i_cboolIsDataHashed,
	BYTE*				o_pbyteSignature,
	DWORD*				o_pdwSignatureLen,
	const DWORD			i_dwFlags
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	BYTE*						pbytePrivateKey				=	NULL;
	DWORD						dwPrivateKeyLen				=	0;

	BYTE*						pbyteDataSequence			=	NULL;
	DWORD						dwDataSequenceLen			=	0;

	BYTE*						pbytePaddedData				=	NULL;
	DWORD						dwPaddedDataLen				=	0;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrSignPubKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteData)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pbyteSignature)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwSignatureLen)

		if ( TRUE != i_cboolIsDataHashed )
		{
			hResult =	E_NOTIMPL;
			break;
		}

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		// Modified by - Infosys Technologies Ltd. 
		// Change Request - CR#21529
		// Description - Pass the out parameter dwptrIsPrivateKeyExportable to the GetPrivateKeyFromDB function
		// CR#21529 - Begin
		// Date Modified - July 2, 2004
		// Pass an parameter to the function and default this parameter to 1. 
		// This parameter is the bIsPrivateKeyExportable flag. 
		unsigned int dwptrIsPrivateKeyExportable;
					//	get the private key
		hResult =	pProtectedStorage -> GetPrivateKeyFromDB
					(
						(unsigned char*) i_cpbyteCorrSignPubKey,
						(unsigned int) i_cdwCorrSignPubKeyLen,
						(unsigned char**) &pbytePrivateKey,
						(unsigned int*) &dwPrivateKeyLen,
						&dwptrIsPrivateKeyExportable
					);
		// CR#21529 - End
		VSM_CHECK_HRESULT

					//	convert the private key from a byte blob to a key struct
		hResult =	GetKeyFromBlob
					(
						(const BYTE*) pbytePrivateKey,
						(const DWORD) dwPrivateKeyLen,
						&RSA_Sign_PrivateKey
					);
		VSM_CHECK_HRESULT

		if ( NULL == o_pbyteSignature )
		{
			*o_pdwSignatureLen =	(RSA_Sign_PrivateKey.modulus).len;
			hResult =	VS_SUCCESS;
			break;
		}

				//	check if the buffer provided for the Signature is big enuf
		if ( (RSA_Sign_PrivateKey.modulus).len > *o_pdwSignatureLen )
		{
			*o_pdwSignatureLen =	(RSA_Sign_PrivateKey.modulus).len;
			hResult =	ERROR_MORE_DATA;
			break;
		}

				// check if CRYPT_NOHASHOID flag is set. If this flag is set, do not
				// create DigestInfo Sequence. We should just sign the hash directly
		if ( (i_dwFlags & CRYPT_NOHASHOID) || 	(VS_SSL3_SHAMD5 == i_cdwHashAlgID ) ) 
		{
			// for CALG_SSL3_SHAMD5 no ASN.1 encoding has to be done
			// because there is no OID for this algorithm type. At
			// the point of verification of this signature the 
			// verification routine must take this into consideration
			// ( this was done to support SSL client auth, the CAPI
			// mailing list has this info)

						//	pad the data
			hResult =	PadDataForSignature
						(
							i_cpbyteData,
							i_cdwDataLen,
							&pbytePaddedData,
							&dwPaddedDataLen
						);
			VSM_CHECK_HRESULT

		} 
		else 
		{
					//	this function will put the hashed data in the Sequence
					//	
					//	DigestInfo ::= SEQUENCE {
					//						digestAlgorithm AlgorithmIdentifier,
					//						digest OCTET STRING
					//					}
			hResult =	PutDataInSequence
						(
							i_cpbyteData,
							i_cdwDataLen,
							i_cdwHashAlgID,
							&pbyteDataSequence,
							&dwDataSequenceLen
						);
			VSM_CHECK_HRESULT


						//	pad the data
			hResult =	PadDataForSignature
						(
							pbyteDataSequence,
							dwDataSequenceLen,
							&pbytePaddedData,
							&dwPaddedDataLen
						);
			VSM_CHECK_HRESULT

		}

		pRSA_Context =	(RSA_Context*) new RSA_Context;

		pRSA_Context -> dwSizeOfStruct	=	sizeof (RSA_Context);
		pRSA_Context -> dwRemainder		=	0;

					//	begin the rsa sign
		nResult =	RSADataBegin
					(
						&RSA_Sign_PrivateKey,
						(void**) &(pRSA_Context -> pContext)
					);
		VSCSP_CHECK_NRESULT


		nResult =	RSADataUpdate
					(
						(void*) (pRSA_Context -> pContext),
//						(unsigned char*) pbyteRevData,
						(unsigned char*) pbytePaddedData,
						(unsigned int) dwPaddedDataLen,
						(unsigned char*) o_pbyteSignature,
						(unsigned int*) o_pdwSignatureLen
					);
		VSCSP_CHECK_NRESULT

					//	destroy the sign context
		nResult =	RSADataEnd
					(
						(void*) (pRSA_Context -> pContext)
					);
		VSCSP_CHECK_NRESULT

		pRSA_Context -> dwRemainder	=	0;
		pRSA_Context -> dwRemainder	=	0;
		pRSA_Context -> pContext	=	NULL;

		VSCSP_CHECK_FOR_NULL_AND_DELETE (pRSA_Context)

		hResult	=	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbytePrivateKey)
	dwPrivateKeyLen =	0;
	
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteDataSequence, dwDataSequenceLen)
//	dwDataSequenceLen =	0;

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbytePaddedData, dwPaddedDataLen)
//	dwPaddedDataLen =	0;

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_VerifyData
(
	const BYTE*			i_cpbyteCorrSignPubKey,
	const DWORD			i_cdwCorrSignPubKeyLen,
	const BYTE*			i_cpbyteData,
	const DWORD			i_cpdwDataLen,
	const DWORD			i_cdwHashAlgID,
	const BOOL			i_cboolIsDataHashed,
	const BYTE*			i_cpbyteSignature,
	const DWORD			i_cdwSignatureLen,
	const DWORD			i_dwFlags
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

//	WCHAR*						pwszBase64KeyHash			=	NULL;

	BYTE*						pbytePubKey					=	NULL;
	DWORD						dwPubKeyLen					=	0;

	BYTE*						pbyteDecryptedSignature		=	NULL;
	DWORD						dwDecryptedSignatureLen		=	0;

//	BYTE*						pbyteRevSignature			=	NULL;
//	DWORD						dwRevSignatureLen			=	0;

	BYTE*						pbyteUnPadedData			=	NULL;
	DWORD						dwUnPadedDataLen			=	0;

	BYTE*						pbyteDataHash				=	NULL;
	DWORD						dwDataHashLen				=	0;

//	BYTE*						pbyteRevHash				=	NULL;
//	DWORD						dwRevHashLen				=	0;

	_bstr_t						tbstrBase64PubKey;

	BYTE*						pbyteBase64PubKey			=	NULL;
	DWORD						dwBase64PubKeyLen			=	0;

	int							nCompare					=	999;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteCorrSignPubKey)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteData)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteSignature)
									
		if ( TRUE != i_cboolIsDataHashed )
		{
			hResult =	E_NOTIMPL;
			break;
		}

		VSCSP_CHECK_IF_PS_OBJECT_READY
			
		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

				//	convert the i_cpbyteCorrPubKeyHash to a base64 encoded string
				//	get size for the base 64 encoded blob
		_Base64Encode
		(
			(CHAR*) i_cpbyteCorrSignPubKey,
			VS_CSP_SHA1_LEN,
			NULL,
			&dwBase64PubKeyLen
		);

				//	allocate memory
		pbyteBase64PubKey =	new BYTE [dwBase64PubKeyLen + 1];
		CHECK_ALLOCATED_MEMORY (pbyteBase64PubKey)

				//	convert the string
		_Base64Encode
		(
			(CHAR*) i_cpbyteCorrSignPubKey,
			VS_CSP_SHA1_LEN,
			(CHAR*) pbyteBase64PubKey,
			&dwBase64PubKeyLen
		);

				//	add a end of string 
		pbyteBase64PubKey [dwBase64PubKeyLen] =	'\0';

				//	assign the base 64 encoded byte blob to a _bstr_t
		tbstrBase64PubKey =	(CHAR*) pbyteBase64PubKey;

					//	get the key from the protected storage
		hResult =	pProtectedStorage -> GetInformationBlob
					(
						tbstrBase64PubKey,
						(unsigned char**) &pbytePubKey,
						(unsigned int*) &dwPubKeyLen
					);
		VSM_CHECK_HRESULT

					//	get the RSA key from the blob
		hResult =	GetKeyFromBlob
					(
						pbytePubKey,
						dwPubKeyLen,
						&RSA_Verify_PublicKey
					);
		VSM_CHECK_HRESULT

		pRSA_Context =	(RSA_Context*) new RSA_Context;

		pRSA_Context -> dwSizeOfStruct	=	sizeof (RSA_Context);
		pRSA_Context -> dwRemainder		=	0;

					//	begin the rsa verify
		nResult =	RSADataBegin
					(
						&RSA_Verify_PublicKey,
						(void**) &(pRSA_Context -> pContext)
					);
		VSCSP_CHECK_NRESULT

		dwDecryptedSignatureLen =	i_cdwSignatureLen;
		pbyteDecryptedSignature =	(BYTE*) new BYTE [dwDecryptedSignatureLen];
		CHECK_ALLOCATED_MEMORY (pbyteDecryptedSignature)

/*
#if 1
		dwRevSignatureLen = i_cdwSignatureLen;
		pbyteRevSignature = (BYTE*) new BYTE [dwRevSignatureLen];
		CHECK_ALLOCATED_MEMORY (pbyteRevSignature)

		for (DWORD i = 0; i < dwRevSignatureLen; i++ )
		{
			pbyteRevSignature [i] = i_cpbyteSignature [dwRevSignatureLen - i - 1];
		}		
#endif
*/
		nResult =	RSADataUpdate
					(
						(void*) (pRSA_Context -> pContext),
//						(unsigned char*) pbyteRevSignature/*i_cpbyteSignature*/,
//						(unsigned int) dwRevSignatureLen/*i_cdwSignatureLen*/,
						(unsigned char*) i_cpbyteSignature,
						(unsigned int) i_cdwSignatureLen,
						(unsigned char*) pbyteDecryptedSignature,
						(unsigned int*) &dwDecryptedSignatureLen
					);
		VSCSP_CHECK_NRESULT

					//	destroy the encryption context
		nResult =	RSADataEnd
					(
						(void*) (pRSA_Context -> pContext)
					);
		VSCSP_CHECK_NRESULT

					//	unpad the data
		hResult =	UnPadDataForVerify
					(
						(const BYTE*) pbyteDecryptedSignature,
						(const DWORD) dwDecryptedSignatureLen,
						&pbyteUnPadedData,
						&dwUnPadedDataLen
					);
		VSM_CHECK_HRESULT


				// Check if CRYPT_NOHASHOID flag is set. If this flag is set, the 
				// hashobject identifier (OID) is not expected to be present and 
				// is not checked. 
				// Unpadded data can be either the actual hash of the data or in the 
				// form of DigestInfo sequence.
				// We are assuming that if unpadded data length and hash data length are
				// same, then unpadded data is the actual hash (not ASN.1 encoded DigestInfo sequence).
		if ( i_cpdwDataLen == dwUnPadedDataLen ) 
		{
						//	compare the signature
			nCompare =	memcmp
						(
							(const void*) pbyteUnPadedData,
							(const void*) i_cpbyteData,
							dwUnPadedDataLen
						);

			if ( 0 != nCompare )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}

			hResult =	VS_SUCCESS;
			break;

		}
			// Unpadded data cannot be a sequence when CRYPT_NOHASHOID is set
		if( (i_dwFlags & CRYPT_NOHASHOID) || (VS_SSL3_SHAMD5 == i_cdwHashAlgID) )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

					//	the data along with the algo id is still in form of a sequence
					//	so get the data
		hResult =	GetDataFromSequence
					(
						pbyteUnPadedData,
						dwUnPadedDataLen,
						i_cdwHashAlgID,
						&pbyteDataHash,
						&dwDataHashLen
					);
		VSM_CHECK_HRESULT

		/////////////////////////////////////////////////////////
		//
		//	TBD
		//
		//	The data might have to be reversed over here
		//	Endian funda :-(
		//
		/////////////////////////////////////////////////////////
/*
#if 1
	dwRevHashLen = dwDataHashLen;
	pbyteRevHash = (BYTE*) new BYTE [dwRevHashLen];
	CHECK_ALLOCATED_MEMORY (pbyteRevHash)

	for (i = 0; i < dwRevHashLen; i++ )
	{
		pbyteRevHash [i] = pbyteDataHash [dwRevHashLen - i - 1];
	}		
#endif
*/

					//	compare the signature
		nCompare =	memcmp
					(
//						(const void*) pbyteRevHash/*pbyteDataHash*/,
						(const void*) pbyteDataHash,
						(const void*) i_cpbyteData,
						dwDataHashLen
						);


		if ( 0 != nCompare )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbytePubKey)
	dwPubKeyLen =	0;
	
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

//	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteRevHash, dwRevHashLen)
//	dwRevHashLen =	0;
//	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteRevSignature, dwRevSignatureLen)
//	dwRevSignatureLen =	0;
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteBase64PubKey, dwBase64PubKeyLen)
//	dwBase64PubKeyLen =	0;
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteDecryptedSignature, dwDecryptedSignatureLen)
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteUnPadedData, dwUnPadedDataLen)
//	dwUnPadedDataLen =	0;
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteDataHash, dwDataHashLen)
//	dwDataHashLen =	0;

	return	hResult;
}

HRESULT		CVirtualSmartCard::VSM_GetUserKeyHandle
(
	const CHAR*			i_cszContainerName,
	const DWORD			i_cdwAlgID,
	DWORD*				o_pdwKeyLen,
	DWORD*				o_pdwExportable,
	BYTE*				o_pbyteCorrPubKey,
	DWORD*				o_pdwCorrPubKeyLen
)
{
	HRESULT						hResult						=	E_FAIL;

//	_bstr_t						tbstrContainerName;

	BYTE*						pbyteContainerStruct		=	NULL;
	DWORD						dwContainerStructLen		=	0;

	CSP_Key_Container*			pContainerContents			=	NULL;
	CSP_PubKeyHash*				pKeyStruct					=	NULL;

	BOOL						boolSuccessFlag				=	FALSE;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cszContainerName)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwKeyLen)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwExportable)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwCorrPubKeyLen)
		if ( NULL == o_pbyteCorrPubKey )
		{
			*o_pdwCorrPubKeyLen =	VS_CSP_SHA1_LEN;
			hResult =	VS_SUCCESS;
			break;
		}

		tbstrContainerName =	i_cszContainerName;

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

					//	get the container struct which contains the 
					//	information about the keys in the container
		hResult =	pProtectedStorage -> GetInformationBlob
					(
						(WCHAR*) tbstrContainerName,
						(unsigned char**) &pbyteContainerStruct,
						(unsigned int*) &dwContainerStructLen
					);
		VSM_CHECK_HRESULT

		pContainerContents =	(CSP_Key_Container*) pbyteContainerStruct;

				//	depending on the required key (algo) get the appripriate
				//	key pointer
		switch ( i_cdwAlgID )
		{
			case	VS_RSA_KEYX:
				pKeyStruct =	&(pContainerContents -> structXchg);
							
				boolSuccessFlag =	TRUE;
				break;

			case	VS_RSA_SIGN:
				pKeyStruct =	&(pContainerContents -> structSign);

				boolSuccessFlag =	TRUE;
				break;

			default:
				hResult =	NTE_BAD_FLAGS;
				break;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		if ( VS_CSP_KEY_EXISTS != pKeyStruct -> dwExists )
		{
				//	if key does not exist then return error
			hResult =	NTE_NO_KEY;
			break;
		}

				//	assign the out values
		*o_pdwKeyLen		=	1024;
		*o_pdwExportable	=	pKeyStruct -> dwExportable;
		*o_pdwCorrPubKeyLen	=	VS_CSP_SHA1_LEN;
		memcpy
		(
			(void*) o_pbyteCorrPubKey,
			(const void*) pKeyStruct -> pbytePubKeyHash,
			VS_CSP_SHA1_LEN
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbyteContainerStruct)
	dwContainerStructLen = 0;
	
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	return	hResult;
}


HRESULT		CVirtualSmartCard::VSM_GetInformationBlob
(
	const CHAR*			i_cszName,
	BYTE*				o_pbyteValue,
	DWORD*				o_pdwValueLen
)
{
	HRESULT						hResult						=	E_FAIL;

	BYTE*						pbyteInformationBlob		=	NULL;
	DWORD						dwInformationBlobLen		=	0;

	BOOL						boolCallEnd					=	FALSE;

	_bstr_t						tbstrName;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cszName)
//		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pbyteValue)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (o_pdwValueLen)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginRead
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		tbstrName =	i_cszName;

		hResult =	pProtectedStorage -> GetInformationBlob
					(
						(WCHAR*) tbstrName,
						(unsigned char**) &pbyteInformationBlob,
						(unsigned int*) &dwInformationBlobLen
					);
		VSM_CHECK_HRESULT

		if ( NULL == o_pbyteValue )
		{
			*o_pdwValueLen =	dwInformationBlobLen;
			hResult =	VS_SUCCESS;
			break;
		}

		if ( dwInformationBlobLen > *o_pdwValueLen )
		{
			*o_pdwValueLen =	dwInformationBlobLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

		*o_pdwValueLen =	dwInformationBlobLen;
		memcpy
		(
			(void*) o_pbyteValue,
			(const void*) pbyteInformationBlob,
			dwInformationBlobLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbyteInformationBlob)
	dwInformationBlobLen = 0;

//	VSPTA_CLEAN_TBSTR(tbstrName)
	
	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndRead ();
	}

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSM_GetInformationBlob

HRESULT		CVirtualSmartCard::VSM_SetInformationBlob
(
	const CHAR*			i_cszName,
	const BYTE*			i_cpbyteValue,
	const DWORD			i_cdwValueLen
)
{
	HRESULT						hResult						=	E_FAIL;

	HRESULT						hErr						=	E_FAIL;

	_bstr_t						tbstrName;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cszName)
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpbyteValue)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginWrite
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		tbstrName =	i_cszName;

		hResult =	pProtectedStorage -> AddInformationBlobToDB
					(
						(WCHAR*) tbstrName,
						i_cpbyteValue,
						i_cdwValueLen
					);
		VSM_CHECK_HRESULT
/*
#ifdef	_VS_MSG_BOX_
		::MessageBox ( NULL, "added information blob", "VeriSign CSP", MB_OK );
#endif
*/
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEnd )
	{
		hErr =	pProtectedStorage -> EndWrite ();
/*
#ifdef	_VS_MSG_BOX_
		if ( S_OK != hErr )
			::MessageBox ( NULL, "after end write - failure", "VeriSign CSP", MB_OK );
		else
			::MessageBox ( NULL, "after end write - success", "VeriSign CSP", MB_OK );
#endif
*/
	}

//	VSPTA_CLEAN_TBSTR(tbstrName)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSM_SetInformationBlob


HRESULT		CVirtualSmartCard::VSM_DeleteInformationBlob
(
	const CHAR*			i_cszName
)
{
	HRESULT						hResult						=	E_FAIL;

	_bstr_t						tbstrName;

	BOOL						boolCallEnd					=	FALSE;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cszName)

		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	BeginWrite
						(
							pProtectedStorage,
							NO_BLOCK_RETURN_ERROR,
							0
						);
		VSM_CHECK_HRESULT

		boolCallEnd =	TRUE;

		tbstrName =	i_cszName;

		hResult =	pProtectedStorage -> RemoveInformationBlobFromDB
					(
						(WCHAR*) tbstrName
					);
		VSM_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEnd )
	{
		pProtectedStorage -> EndWrite ();
	}

//	VSPTA_CLEAN_TBSTR(tbstrName)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSM_DeleteInformationBlob



///////////////////////////////////////////////////////////////////////////////
//	some helper functions
///////////////////////////////////////////////////////////////////////////////
/*
///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	CheckIfContainerExists
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS		-	if the container exists
//		NTE_BAD_KEYSET	-	if the container does not exist
//
//	Description		:	the function will check if the specified container exists in
//						the CSP (profile)
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		CVirtualSmartCard::CheckIfContainerExists ()
{
	HRESULT						hResult				=	E_FAIL;

	BYTE*						pbyteData			=	NULL;
	DWORD						dwDataLen			=	0;

	while (1)
	{
		VSCSP_CHECK_IF_PS_OBJECT_READY

		hResult =	pProtectedStorage -> GetInformationBlob
					(
						tbstrContainerName,
						&pbyteData,
						(unsigned int*) &dwDataLen
					);
		if ( VS_SUCCESS != hResult )
		{
			hResult =	NTE_BAD_KEYSET;
		}

		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbyteData)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::CheckIfContainerExists ()
*/
/*
///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	CheckIfKeyExists
//
//	Parameters
//		const DWORD			i_cdwAlgID		-	the algo id.
//												the acceptable values are
//												VS_RSA_KEYX / VS_RSA_SIGN (defined in cspglobals.h)
//
//	Return Values	:
//		VS_SUCCESS		-	if the key exists
//		NTE_NO_KEY		-	if key does not exist
//		NTE_BAD_ALGID	-	bad algo id was specified
//
//	Description		:	the function will check if the specified key exists in the specified
//						container
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		CVirtualSmartCard::CheckIfKeyExists
(
	const DWORD			i_cdwAlgID
)
{
	HRESULT						hResult				=	E_FAIL;

	BOOL						boolSuccessFlag		=	FALSE;

	BYTE*						pbyteContainerContents	=	NULL;
	DWORD						dwContainerContentsLen	=	0;

	while (1)
	{
		VSCSP_CHECK_IF_PS_OBJECT_READY

					//	get the info blob
		hResult =	pProtectedStorage -> GetInformationBlob
					(
						tbstrContainerName,
						&pbyteContainerContents,
						(unsigned int*) &dwContainerContentsLen
					);
		VSM_CHECK_HRESULT

		memcpy
		(
			(void*)	m_pstructContainer,
			(const void*) pbyteContainerContents,
			dwContainerContentsLen
		);

		switch ( i_cdwAlgID )
		{
			case	VS_RSA_KEYX:
				if ( VS_CSP_KEY_EXISTS != (m_pstructContainer -> structXchg).dwExists )
				{
					hResult =	NTE_NO_KEY;
					break;
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_RSA_SIGN:
				if ( VS_CSP_KEY_EXISTS != (m_pstructContainer -> structSign).dwExists )
				{
					hResult =	NTE_NO_KEY;
					break;
				}

				boolSuccessFlag =	TRUE;
				break;

			default:
				hResult =	NTE_BAD_ALGID;
				break;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_DELETE_USING_PS_FREE (pbyteContainerContents)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::CheckIfKeyExists
*/


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	HashPublicKey
//
//	Parameters
//		const A_RSA_KEY*	i_cpPublicKey	-	the public key
//		BYTE*				o_pbyteHash		-	the hash of the flattened public key
//												will be returned in this. the length
//												of this buffer MUST be VS_CSP_SHA1_LEN (=20) as the SHA1
//												algo will be used
//
//	Return Values	:
//		VS_SUCCESS		-	successful
//		NTE_FAIL		-	failure
//
//	Description		:	the function will accept a RSA public key, flatten it, hash it
//						 and return the hash.
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		CVirtualSmartCard::HashPublicKey
(
	const A_RSA_KEY*	i_cpPublicKey,
	BYTE*				o_pbyteHash
)
{
	HRESULT						hResult				=	E_FAIL;
	int							nResult				=	999;

	BYTE*						pbyteKeyBlob		=	NULL;
	DWORD						dwKeyBlobLen		=	0;

	void*						pvoidContext		=	NULL;

	DWORD						dwBufferSize		=	VS_CSP_SHA1_LEN;	//	SHA len

	while (1)
	{
				//	flatten the public key
		hResult =	GetBlobFromKey
					(
						i_cpPublicKey,
						&pbyteKeyBlob,
						&dwKeyBlobLen
					);
		VSM_CHECK_HRESULT

				//	hash the byte blob
		nResult =	HashBegin
					(
						VS_SHA_1,
						&pvoidContext
					);
		if ( 0 != nResult )
		{
			hResult =	NTE_FAIL;
			break;
		}

		nResult =	HashData
					(
						VS_SHA_1,
						pvoidContext,
						(unsigned char*) pbyteKeyBlob,
						(unsigned int) dwKeyBlobLen
					);
		if ( 0 != nResult )
		{
			hResult =	NTE_FAIL;
			break;
		}

		nResult =	HashEnd
					(
						VS_SHA_1,
						pvoidContext,
						o_pbyteHash,
						dwBufferSize
					);
		if ( 0 != nResult )
		{
			hResult =	NTE_FAIL;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)
	
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteKeyBlob, dwKeyBlobLen)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::HashPublicKey


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetBlobFromKey
//
//	Parameters
//		const A_RSA_KEY*	i_cpKey				-	the key
//		BYTE**				o_ppbyteKeyBlob		-	the key will be flattened and copied
//													to this blob. Memory will be allocated
//													by this function. the caller should free
//													the memory
//		DWORD*				o_pdwKeyBlobLen		-	the lenght of the blob will be
//													returned in this
//
//	Return Values	:
//		VS_SUCCESS		-	successful
//
//	Description		:	the function will accept a RSA key, flatten it and return it
//						as a byte blob
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		CVirtualSmartCard::GetBlobFromKey
(
	const A_RSA_KEY*	i_cpKey,
	BYTE**				o_ppbyteKeyBlob,
	DWORD*				o_pdwKeyBlobLen
)
{
	HRESULT						hResult				=	E_FAIL;

	DWORD						dwOffset			=	0;

	while (1)
	{
			//	the A_RSA_KEY strucutre contains 2 ITEM
			//	each ITEM is a char* followed by len
			//
			//	so to flatten out this structure we will have to put the actual char arrays
			//	into the byte blob
		*o_pdwKeyBlobLen =		(i_cpKey -> modulus).len * sizeof (unsigned char)\
							+	sizeof (unsigned int)\
							+	(i_cpKey -> exponent).len * sizeof (unsigned char)\
							+	sizeof (unsigned int);

		*o_ppbyteKeyBlob =	new BYTE [*o_pdwKeyBlobLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteKeyBlob)

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) &((i_cpKey -> modulus).len),
			sizeof (unsigned int)
		);

		dwOffset +=	sizeof (unsigned int);

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) (i_cpKey -> modulus).data,
			(i_cpKey -> modulus).len * sizeof (unsigned char)
		);

		dwOffset += (i_cpKey -> modulus).len * sizeof (unsigned char);

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) &((i_cpKey -> exponent).len),
			sizeof (unsigned int)
		);

		dwOffset +=	sizeof (unsigned int);

		memcpy
		(
			(void*) &((*o_ppbyteKeyBlob) [dwOffset]),
			(const void*) (i_cpKey -> exponent).data,
			(i_cpKey -> exponent).len * sizeof (unsigned char)
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::GetBlobFromKey


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetKeyFromBlob
//
//	Parameters
//		const BYTE*			i_cpbyteKeyBlob	-	the key blob
//		const DWORD			i_cdwKeyBlobLen	-	the length of the key blob
//		A_RSA_KEY*			o_pKey			-	the pointer to the key. the key
//												contains the modulus data ptr and len
//												and the exponent data ptr and len.
//
//	Return Values	:
//		VS_SUCCESS		-	successful
//
//	Description		:	the function will accept a key blob and create a RSA key out of it
//
///////////////////////////////////////////////////////////////////////////////	
HRESULT		CVirtualSmartCard::GetKeyFromBlob
(
	const BYTE*			i_cpbyteKeyBlob,
	const DWORD			i_cdwKeyBlobLen,
	A_RSA_KEY*			o_pKey
)
{
	HRESULT						hResult						=	E_FAIL;

	DWORD						dwOffset					=	0;

	while (1)
	{
				//	copy the modulus length
		memcpy
		(
			(void*) &((o_pKey -> modulus).len),
			(const void*) i_cpbyteKeyBlob,
			sizeof (unsigned int)
		);

		dwOffset += sizeof (unsigned int);

				//	allocate memory for modulus data
		(o_pKey -> modulus).data =	(unsigned char*) new BYTE [(o_pKey -> modulus).len * sizeof (unsigned char)];
		CHECK_ALLOCATED_MEMORY ( (o_pKey -> modulus).data )

				//	copy modulus data
		memcpy
		(
			(void*)	(o_pKey -> modulus).data ,
			(const void*) &(i_cpbyteKeyBlob [dwOffset]),
			(o_pKey -> modulus).len
		);

		dwOffset += (o_pKey -> modulus).len * sizeof (unsigned char);

				//	copy exponent len
		memcpy
		(
			(void*) &((o_pKey -> exponent).len),
			(const void*) &(i_cpbyteKeyBlob [dwOffset]),
			sizeof (unsigned int)
		);

		dwOffset += sizeof (unsigned int);

				//	allocate memory for exponent data
		(o_pKey -> exponent).data =	(unsigned char*) new BYTE [(o_pKey -> exponent).len * sizeof (unsigned char)];
		CHECK_ALLOCATED_MEMORY ( (o_pKey -> exponent).data )

				//	copy exponent data
		memcpy
		(
			(void*)	(o_pKey -> exponent).data ,
			(const void*) &(i_cpbyteKeyBlob [dwOffset]),
			(o_pKey -> exponent).len
		);
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::GetKeyFromBlob


HRESULT		CVirtualSmartCard::PadDataForEncryption
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	BYTE**				o_ppbytePaddedData,
	DWORD*				o_pdwPaddedDataLen
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	DWORD						dwBlockLength				=	0;
	DWORD						dwLengthOfPaddingRequired	=	0;
	DWORD						dwNumOfRandomBytes			=	0;

	DWORD						i, j;

	BYTE*						pbyteRandomData				=	NULL;
	DWORD						dwRandomDataLen				=	0;

	*o_ppbytePaddedData	=	NULL;

	while (1)
	{
					//	the block lenght in case of the assymetric key
					//	is basically the length of the modulus
		dwBlockLength =	(RSA_Enc_PublicKey.modulus).len;

					//	the padding required is the block length - the data length
		dwLengthOfPaddingRequired =	dwBlockLength - i_cdwDataLen;

					//	the minimum required padding is 11 bytes.
					//	so if the required padding length is less than 11 then return error
		if ( RSA_MIN_PAD_LEN > dwLengthOfPaddingRequired )
		{
			hResult =	NTE_BAD_LEN;
			break;
		}

			//	the padding is of the form 0x00 0x02 ... Random Data Bytes (non 0x00) ... 0x00
			//	so the number of Random bytes is required padding - 3
		dwNumOfRandomBytes =	dwLengthOfPaddingRequired - 3;

				//	 allocate memory for the padded input data
		*o_pdwPaddedDataLen =	dwBlockLength;
		*o_ppbytePaddedData =	new BYTE [*o_pdwPaddedDataLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbytePaddedData)

			//	the length of the required random data is dwNumOfRandomBytes.
			//	but 0x00 is cannot be used for padding
			//	so to be on a safe side the random block generated is twice
			//	the length of dwNumOfRandomBytes and the 0x00s and the remaining block
			//	will be discarded
			//
			//	The assumption is that if more than half the bytes of an allocated random block
			//	have the value 0x00 then the random function is not exactly random.
		dwRandomDataLen =	dwNumOfRandomBytes * 2;
		pbyteRandomData =	new BYTE [dwRandomDataLen];
		CHECK_ALLOCATED_MEMORY (pbyteRandomData)

					//	generate the random block
		nResult =	GenerateRandomBlock
					(
						pbyteRandomData,
						dwRandomDataLen
					);
		VSCSP_CHECK_NRESULT

				//	0x00 0x02
		(*o_ppbytePaddedData) [0] =	0x00;
		(*o_ppbytePaddedData) [1] =	0x02;

		for ( i = 0, j = 0; i < dwNumOfRandomBytes; i++, j++ )
		{
					//	discard all the 0x00s from the random block
			while ( 0x00 == pbyteRandomData [j] )
			{
				j++;
			}

					//	copy the random data as padding
			(*o_ppbytePaddedData) [2 + i] = pbyteRandomData [j];
		}

		(*o_ppbytePaddedData) [2 + i] =	0x00;

					//	copy the original (input) data after the padding bytes
		memcpy
		(
			&((*o_ppbytePaddedData) [dwLengthOfPaddingRequired]),
			i_cpbyteData,
			i_cdwDataLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)
	
	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::PadDataForEncryption

HRESULT		CVirtualSmartCard::UnPadDataForDecryption
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	BYTE**				o_ppbyteUnPaddedData,
	DWORD*				o_pdwUnPaddedDataLen
)
{
	HRESULT						hResult						=	E_FAIL;

	DWORD						dwBlockLength				=	0;
	DWORD						dwLengthOfPadding			=	0;
	DWORD						dwNumOfRandomBytes			=	0;

	while (1)
	{
			//	check if the length of the data is equal to the length of the modulus of the key
			//
			//	this is the block length for assymetric operations
		if ( i_cdwDataLen != (RSA_Dec_PrivateKey.modulus).len )
		{
			hResult =	NTE_BAD_DATA;
			break;
		}

		//
		//	the padding is of the form
		//	0x00 0x02 ... (non 0x00) Random Bytes ... 0x00
		//

				//	check the 0x00
		if ( 0x00 != i_cpbyteData [0] )
		{
			hResult =	NTE_BAD_DATA;
			break;
		}

				//	check the 0x02
		if ( 0x02 != i_cpbyteData [1] )
		{
			hResult =	NTE_BAD_DATA;
			break;
		}

				//	get the number of Random bytes
		while ( 0x00 != i_cpbyteData [2 + dwNumOfRandomBytes] )
		{
			dwNumOfRandomBytes ++;
		}

			//	calculate the total length of padding. it should be atleast 11 bytes. if its less
			//	then return error
		dwLengthOfPadding =	dwNumOfRandomBytes + 3;
		if ( RSA_MIN_PAD_LEN > dwLengthOfPadding )
		{
			hResult =	NTE_BAD_DATA;
			break;
		}

		*o_pdwUnPaddedDataLen =	i_cdwDataLen - dwLengthOfPadding;

			//	allocate memory
		*o_ppbyteUnPaddedData =	new BYTE [*o_pdwUnPaddedDataLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteUnPaddedData)

				//	copy data into out buffer
		memcpy
		(
			(void*) *o_ppbyteUnPaddedData,
			(const void*) &(i_cpbyteData [dwLengthOfPadding]),
			*o_pdwUnPaddedDataLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::UnPadDataForDecryption

HRESULT		CVirtualSmartCard::PadDataForSignature
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	BYTE**				o_ppbytePaddedData,
	DWORD*				o_pdwPaddedDataLen
)
{
	HRESULT						hResult						=	E_FAIL;

	DWORD						dwBlockLength				=	0;
	DWORD						dwLengthOfPaddingRequired	=	0;
	DWORD						dwNumOfFFs					=	0;

	DWORD						i;

	while (1)
	{
					//	the block lenght in case of the assymetric key
					//	is basically the length of the modulus
		dwBlockLength =	(RSA_Sign_PrivateKey.modulus).len;

					//	the padding required is the block length - the data length
		dwLengthOfPaddingRequired =	dwBlockLength - i_cdwDataLen;

					//	the minimum required padding is 11 bytes.
					//	so if the required padding length is less than 11 then return error
		if ( RSA_MIN_PAD_LEN > dwLengthOfPaddingRequired )
		{
			hResult =	NTE_BAD_LEN;
			break;
		}

			//	the padding is of the form 0x00 0x01 0xFF .... 0xFF 0x00
			//	so the number of FFs is required padding - 3
		dwNumOfFFs =	dwLengthOfPaddingRequired - 3;

				//	 allocate memory for the padded input data
		*o_pdwPaddedDataLen =	dwBlockLength;
		*o_ppbytePaddedData =	new BYTE [*o_pdwPaddedDataLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbytePaddedData)

		(*o_ppbytePaddedData) [0] =	0x00;
		(*o_ppbytePaddedData) [1] =	0x01;

		for ( i = 0; i < dwNumOfFFs; i++ )
		{
			(*o_ppbytePaddedData) [2 + i] =	0xFF;
		}

		(*o_ppbytePaddedData) [2 + i] =	0x00;

				//	copy the original (input) data after the padding bytes
		memcpy
		(
			&((*o_ppbytePaddedData) [dwLengthOfPaddingRequired]),
			i_cpbyteData,
			i_cdwDataLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::PadDataForSignature


HRESULT		CVirtualSmartCard::UnPadDataForVerify
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	BYTE**				o_ppbyteUnPaddedData,
	DWORD*				o_pdwUnPaddedDataLen
)
{
	HRESULT						hResult						=	E_FAIL;

	DWORD						dwBlockLength				=	0;
	DWORD						dwLengthOfPadding			=	0;
	DWORD						dwNumOfFFs					=	0;

	BOOL						boolSuccessFlag				=	TRUE;

	while (1)
	{
			//	check if the length of the data is equal to the length of the modulus of the key
			//
			//	this is the block length for assymetric operations
		if ( i_cdwDataLen != (RSA_Verify_PublicKey.modulus).len )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

		//
		//	the padding is of the form
		//	0x00 0x01 0xFF....0xFF 0x00
		//

				//	check the 0x00
		if ( 0x00 != i_cpbyteData [0] )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

				//	check the 0x01
		if ( 0x01 != i_cpbyteData [1] )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

				//	get the number of 0xFF
		while ( 0x00 != i_cpbyteData [2 + dwNumOfFFs] )
		{
			if ( 0xFF != i_cpbyteData [2 + dwNumOfFFs] )
			{
				hResult =	NTE_BAD_SIGNATURE;
				boolSuccessFlag =	FALSE;
				break;
			}

			dwNumOfFFs ++;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	calculate the total length of padding. it should be atleast 11 bytes. if its less
			//	then return error
		dwLengthOfPadding =	dwNumOfFFs + 3;
		if ( RSA_MIN_PAD_LEN > dwLengthOfPadding )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

		*o_pdwUnPaddedDataLen =	i_cdwDataLen - dwLengthOfPadding;

			//	allocate memory
		*o_ppbyteUnPaddedData =	new BYTE [*o_pdwUnPaddedDataLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteUnPaddedData)

				//	copy data into out buffer
		memcpy
		(
			(void*) *o_ppbyteUnPaddedData,
			(const void*) &(i_cpbyteData [dwLengthOfPadding]),
			*o_pdwUnPaddedDataLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::UnPadDataForVerify


HRESULT		CVirtualSmartCard::PutDataInSequence
(
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	const DWORD			i_cdwAlgID,
	BYTE**				o_ppbyteDataInSequence,
	DWORD*				o_pdwDataInSequenceLen
)
{
	HRESULT						hResult						=	E_FAIL;

//	BYTE*						pbyteRevHash				=	NULL;
//	DWORD						dwRevHashLen				=	0;

	while (1)
	{
		CNull					CNULL;

				//	put the data in an octet string
		COctetString	CosHashData ( (_DWORD) i_cdwDataLen, (_BYTE*) i_cpbyteData );

				//	create ObjectIdentifiers for all the algos
		CObjectIdentifier	CoiSHA1
					(
						(_DWORD) ::lstrlen(VS_SHA1_OID),
						(_BYTE*) VS_SHA1_OID
					);

		CObjectIdentifier	CoiMD2
					( 
						(_DWORD) ::lstrlen(VS_MD2_OID),
						(_BYTE*) VS_MD2_OID
					);

		CObjectIdentifier	CoiMD5
					( 
						(_DWORD) ::lstrlen(VS_MD5_OID),
						(_BYTE*) VS_MD5_OID
					);

				//			AlgorithmIdentifier ::= SEQUENCE {
				//								  algorithm OBJECT IDENTIFIER,
				//								  parameters ANY DEFINED BY algorithm OPTIONAL }
		CSequence			CSeqAlgoId;

				//	DigestInfo ::= SEQUENCE {
				//						digestAlgorithm AlgorithmIdentifier,
				//						digest OCTET STRING
				//					}
		CSequence			CSeqDataInSequence;

				//	depending on the algo add the appropriate ObjectIdentifier in the algo id sequence
		switch ( i_cdwAlgID )
		{
			case	VS_SHA_1:
				CSeqAlgoId =	CoiSHA1;

				break;

			case	VS_MD2:
				CSeqAlgoId =	CoiMD2;

				break;

			case	VS_MD5:
				CSeqAlgoId =	CoiMD5;

				break;

			default:
				break;
		}	//	end		switch ( i_cdwAlgID )

		CSeqAlgoId += CNULL;

				//	the data in sequence is basically the DigestInfo
		CSeqDataInSequence += CSeqAlgoId;
		CSeqDataInSequence += CosHashData;

		*o_pdwDataInSequenceLen =	(CSeqDataInSequence.BaseDERBlob) -> cbData;
		*o_ppbyteDataInSequence =	new BYTE [*o_pdwDataInSequenceLen];
		CHECK_ALLOCATED_MEMORY ( *o_ppbyteDataInSequence )

		memcpy
		(
			(void*) *o_ppbyteDataInSequence,
			(const void*) (CSeqDataInSequence.BaseDERBlob) -> pbData,
			*o_pdwDataInSequenceLen
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

//	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteRevHash, dwRevHashLen)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::PutDataInSequence


HRESULT		CVirtualSmartCard::GetDataFromSequence
(
	const BYTE*			i_cpbyteDataInSequence,
	const DWORD			i_cdwDataLenInSequence,
	const DWORD			i_cdwAlgID,
	BYTE**				o_ppbyteData,
	DWORD*				o_pdwDataLen
)
{
	HRESULT						hResult						=	E_FAIL;

	_DERTree*					pstructDataSequence			=	NULL;
	_DERTree*					pstructAlgoID				=	NULL;
	_DERTree*					pstructObjectId				=	NULL;
	_DERTree*					pstructData					=	NULL;

	CHAR						szAlgoID [MAX_PATH];
	int							nStrCmp						=	999;

//	CSequence*					pCSeqAlgoID					=	NULL;
//	CObjectIdentifier*			pCoiAlgoID					=	NULL;

	while (1)
	{
			//	copy the data in sequence in a temp base DER collection
		CBaseDERCollection	CbdcData ( (_DWORD) i_cdwDataLenInSequence, (_BYTE*) i_cpbyteDataInSequence );

			//	copy the collection into a hierarchy
		CBaseDERHierarchy	CbdhData ( CbdcData );
		if ( 0 != CbdhData.dwErrorCode )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}


		pstructDataSequence =	&(CbdhData.m_DERTree);
		if ( NULL != pstructDataSequence )
		{
					//	check if its a sequence
			if ( SEQUENCE != ( (pstructDataSequence -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	this will point to the algo sequence
		pstructAlgoID =	pstructDataSequence -> rightDERTree;
		if ( NULL != pstructAlgoID )
		{
					//	check if its a sequence
			if ( SEQUENCE != ( (pstructAlgoID -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}
				//	this will point to the object identifier
		pstructObjectId =	pstructAlgoID -> rightDERTree;
		if ( NULL != pstructObjectId )
		{
					//	check if its a object identifier
			if ( OBJECT_IDENTIFIER != ( (pstructObjectId -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	copy the object identifier into the string
		memcpy
		(
			(void*) szAlgoID,
			(const void*) (pstructObjectId -> currentBaseDER) -> pbData,
			(pstructObjectId -> currentBaseDER) -> cbData
		);

		szAlgoID [ (pstructObjectId -> currentBaseDER) -> cbData ] =	NULL;

		switch ( i_cdwAlgID )
		{
			case	VS_SHA_1:
				nStrCmp =	lstrcmp ( szAlgoID, VS_SHA1_OID );
				break;

			case	VS_MD2:
				nStrCmp =	lstrcmp ( szAlgoID, VS_MD2_OID );
				break;

			case	VS_MD5:
				nStrCmp =	lstrcmp ( szAlgoID, VS_MD5_OID );
				break;

			default:
				break;
		}

		if ( 0 != nStrCmp )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}
				//	this will point to the data OCTET STRING
		pstructData =	pstructAlgoID -> nextDERTree;
		if ( NULL != pstructData )
		{
					//	check if its a octet string
			if ( OCTET_STRING != ( (pstructData -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	allocate memory for the data
		*o_pdwDataLen =	(pstructData -> currentBaseDER) -> cbData;
		*o_ppbyteData =	new BYTE [*o_pdwDataLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteData)

				//	copy the data into the out buffer
		memcpy
		(
			(void*) *o_ppbyteData,
			(const void*) (pstructData -> currentBaseDER) -> pbData,
			*o_pdwDataLen
		);
			
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::GutDataFromSequence


/*HRESULT		CVirtualSmartCard::GetServersFromArray
(
	VARIANT*			i_pvarWhichSmartCard,
	DWORD*				o_pdwNumRoamingServers,
	WCHAR***			o_ppwszRoamingServers,
	_bstr_t*			o_ptbstrStorageServer,
	_bstr_t*			o_ptbstrUserName,
	VSRM_ITEM*			o_pvsrmItemStorageServerID,
	VSRM_ITEM***		o_pppvsrmItemRoamingServerIDList,
	_bstr_t*			o_ptbstrProfileIssUniqueID
)*/
HRESULT		CVirtualSmartCard::GetServersFromArray
(
	VARIANT*			i_pvarWhichSmartCard,
	_bstr_t*	        o_ptbstrClientInfo,
	_bstr_t*			o_ptbstrClientInfoSig,
	_bstr_t*			o_ptbstrUserName,
	_bstr_t*			o_ptbstrProfileIssUniqueID
)

{
	HRESULT		hResult				=	VS_SUCCESS;
	DWORD		dwNumElements		=	0;
	SAFEARRAY*	pSafeArray			=	NULL;
	LONG lIndices[1];
	VARIANT varElem;
	_bstr_t*		ptbstrRoamingServers	=	NULL;

	pSafeArray =	(i_pvarWhichSmartCard -> parray);
	dwNumElements =	(i_pvarWhichSmartCard -> parray) ->rgsabound[0].cElements;

	//*o_pdwNumRoamingServers =	dwNumElements - 3;
	//ptbstrRoamingServers =	new _bstr_t [*o_pdwNumRoamingServers];

	
	lIndices[0] =	0;
	SafeArrayGetElement(pSafeArray,lIndices,(void*)&varElem);
	*o_ptbstrUserName =	varElem.bstrVal;
	if ( varElem.bstrVal )
	{
		SysFreeString (varElem.bstrVal);
	}

	lIndices[0] =	1;
	SafeArrayGetElement(pSafeArray,lIndices,(void*)&varElem);
	*o_ptbstrProfileIssUniqueID =	varElem.bstrVal;
	if ( varElem.bstrVal )
	{
		SysFreeString (varElem.bstrVal);
	}

	lIndices[0] =	2;
	SafeArrayGetElement(pSafeArray,lIndices,(void*)&varElem);
	//*o_ptbstrStorageServer =	varElem.bstrVal;
	*o_ptbstrClientInfo =	varElem.bstrVal;
	if ( varElem.bstrVal )
	{
		SysFreeString (varElem.bstrVal);
	}

	lIndices[0] =	3;
	SafeArrayGetElement(pSafeArray,lIndices,(void*)&varElem);
	//*o_ptbstrStorageServer =	varElem.bstrVal;
	*o_ptbstrClientInfoSig =	varElem.bstrVal;
	if ( varElem.bstrVal )
	{
		SysFreeString (varElem.bstrVal);
	}

//	*o_pvsrmItemStorageServerID =	new (VSRM_ITEM);
//	(*o_pvsrmItemStorageServerID).len =	((*o_ptbstrStorageServer).length () + 1) * sizeof (WCHAR);

//	(*o_pvsrmItemStorageServerID).data =	new BYTE [((*o_ptbstrStorageServer).length () + 1) * sizeof (WCHAR)];

/*	memcpy
	(
		(*o_pvsrmItemStorageServerID).data,
		(WCHAR*) *o_ptbstrStorageServer,
		((*o_ptbstrStorageServer).length () + 1) * sizeof (WCHAR)
	);

*/
/*	for ( int i = 3; i < dwNumElements; i++ )
	{
		lIndices[0] = i;
		SafeArrayGetElement(pSafeArray,lIndices,(void*)&varElem);
		ptbstrRoamingServers[i-3] = varElem.bstrVal;
		if ( varElem.bstrVal )
		{
			SysFreeString (varElem.bstrVal);
		}
	}

	*o_ppwszRoamingServers =	new WCHAR* [dwNumElements -3 + 1];				//	the +1 is there because teh last
	*o_pppvsrmItemRoamingServerIDList =	new VSRM_ITEM* [dwNumElements -3 + 1];	//	element in the array should be NULL

	for ( int j = 0; j < dwNumElements - 3; j++ )
	{
		(*o_ppwszRoamingServers)[j] = new WCHAR [((ptbstrRoamingServers [j]).length () + 1)];

		memcpy
		(
			(*o_ppwszRoamingServers) [j],
			(WCHAR*) (ptbstrRoamingServers [j]),
			((ptbstrRoamingServers [j]).length () + 1) * sizeof (WCHAR)
		);

		(*o_pppvsrmItemRoamingServerIDList)[j] = new (VSRM_ITEM);

		((*o_pppvsrmItemRoamingServerIDList) [j]) -> len = ((ptbstrRoamingServers [j]).length () + 1) * sizeof (WCHAR);
		((*o_pppvsrmItemRoamingServerIDList) [j]) -> data = new BYTE [((*o_pppvsrmItemRoamingServerIDList) [j])->len];

		memcpy
		(
			((*o_pppvsrmItemRoamingServerIDList) [j])->data,
			(WCHAR*) (ptbstrRoamingServers [j]),
			((ptbstrRoamingServers [j]).length () + 1) * sizeof (WCHAR)
		);
	}

	(*o_ppwszRoamingServers)[j] = NULL;
	(*o_pppvsrmItemRoamingServerIDList)[j] = NULL;
*/	
	return	VS_SUCCESS;
}

HRESULT CVirtualSmartCard::GetRoamingStorage (VARIANT* i_pvarWhichSmartCard, VARIANT* i_pvarPassword, _bstr_t* o_ptbstrUserName)
{
	HRESULT retVal = S_OK;
	_bstr_t		tbstrRoamingServers;
	_bstr_t		tbstrClientInfo;
	_bstr_t		tbstrClientInfoSig;
	_bstr_t		tbstrUserName;
	_bstr_t		tbstrProfileIssUniqueID;
	VSRM_STATUS	vsrmStatus;
	VSRM_PASSWORD	vsrmPassword;
	VSRM_ITEM*		pvsrmItemData = NULL;


			/*Obtain the username, roaming servers and storage servers */
	

	retVal     =	GetServersFromArray
					(
						i_pvarWhichSmartCard,
						&tbstrClientInfo,
						&tbstrClientInfoSig,
						&tbstrUserName,
						&tbstrProfileIssUniqueID
					);	

	/*Obtain the blob from the roaming server*/
	if(retVal == VS_SUCCESS)
	{
		
		if(i_pvarPassword->vt == VT_EMPTY)
		{
			vsrmStatus = VSRM_ERR_WRONG_PASSWORD;
		}
		else
		{
			// Roaming Servers do not allow zero-length passwords.
			// If the password length is zero or the password is null we trap the error here.
			if ((i_pvarPassword -> bstrVal == NULL) || (SysStringLen(i_pvarPassword -> bstrVal) == 0))
			{
				vsrmStatus = VSRM_ERR_WRONG_PASSWORD;
			}
			else {
				vsrmPassword.valueType	=	PASSWORD_VALUE_TYPE_UNICODE;
				vsrmPassword.pszValue	=	_bstr_t(i_pvarPassword -> bstrVal);

				vsrmStatus =	VSRM_StartSession
						(
							&m_SessionHandle,
							tbstrUserName,
							&vsrmPassword,
							(const char*)tbstrClientInfo,
							(const char*)tbstrClientInfoSig
						);		
	
				if ( VSRM_SUCCESS != vsrmStatus )
				{
					retVal =	E_ROAMING_START_SESSION_FAILED;
				}
			}
		}
				

	}

	if(retVal == VS_SUCCESS)
	{
		if ((i_pvarPassword->vt != VT_EMPTY) 
			&& (i_pvarPassword -> bstrVal != NULL) 
			&& (SysStringLen(i_pvarPassword -> bstrVal) > 0))
		{
			vsrmStatus = VSRM_RecoverData(m_SessionHandle,&pvsrmItemData);
		}

		if(VSRM_SUCCESS != vsrmStatus)
		{
			if(VSRM_ERR_NO_SUCH_USER == vsrmStatus)
			{
				retVal = E_PROFDOESNOTEXIST;
			}
			else if(VSRM_ERR_WRONG_PASSWORD == vsrmStatus)
			{
				retVal = E_INVALIDPASSWD;
			}
			else if(VSRM_ERR_ATTEMPT_EXCEED_THRESHOLD == vsrmStatus)
			{
				retVal = E_PROFLOCKEDOUT;
			}
			else
			{
				retVal = E_ROAMING_RECDATA_FAILED;
			}
		}
		else
		{
			m_pbyteStorage = new BYTE[pvsrmItemData->len];
			if(!m_pbyteStorage)
				retVal = E_FAIL;
			else
			{
				m_dwStorageLen = pvsrmItemData->len;
				memcpy(m_pbyteStorage, pvsrmItemData -> data, pvsrmItemData->len);
			}

			VSRM_DestroyItem(pvsrmItemData);
			VSRM_FreeItem(pvsrmItemData);
		}
	}

	if(retVal == VS_SUCCESS)
		*o_ptbstrUserName = tbstrUserName;

	/*Free data*/
	if(vsrmPassword.valueType == PASSWORD_VALUE_TYPE_HASHED)
		SafeArrayUnaccessData(i_pvarPassword->parray);

//	VSPTA_CLEAN_TBSTR(tbstrRoamingServers)
//	VSPTA_CLEAN_TBSTR(tbstrClientInfo)
//	VSPTA_CLEAN_TBSTR(tbstrClientInfoSig)
//	VSPTA_CLEAN_TBSTR(tbstrUserName)
//	VSPTA_CLEAN_TBSTR(tbstrProfileIssUniqueID)

	return retVal;

}


void LogFunc(const BYTE* i_pcbyteData, const DWORD i_cdwDataLength)
{
	FILE  *fp = NULL;
	
	fp = fopen(LOG_FILE, "ab");            
	if ( fp )
	{
	    fwrite(i_pcbyteData, 1, i_cdwDataLength, fp);
		fflush(fp);
		fclose(fp);
	}
}

HRESULT CVirtualSmartCard::VSM_CreatePasswd(_bstr_t& i_tbstrNewPasswd)
{
	HRESULT				retVal					=	S_OK;



#if 0
	VSRM_STATUS			vsrmStatus;
	VSRM_PASSWORD		vsrmNewPassword;
	VSRM_PASSWORD		vsrmOldPassword;
	BOOL				boolBeginWriteCalled	=	FALSE;

	int					nMaxTries;
	int					nNumOfInvalidTries		=	0;
	int					nUnlockPeriod;
	_VS_BYTE*			pbyteMaxTries			= NULL;
	_VS_DWORD*			dwMaxTriesSize;
	_VS_BYTE*			pbyteNumOfInvalidTries	= NULL;
	_VS_DWORD*			dwNumOfInvalidTriesSize;
	_VS_BYTE*			pbyteUnlockPeriod		= NULL;
	_VS_DWORD*			dwUnlockPeriodSize;
	_VS_BYTE*			pbyteLastInvalidTry		= NULL;
	_bstr_t				tbstrAppPrefName		= "";
	FILETIME			ftLastInvalidTry;
	FILETIME			ftCurrTime;

	while (1)
	{
		/*Obtain the maximum number of tries that are allowed*/
		tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteMaxTries), (_VS_DWORD*)&dwMaxTriesSize);
		pPTAProtectedStorage->EndRead();

		if ( VS_SUCCESS == retVal )
		{
			nMaxTries = *pbyteMaxTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteMaxTries);
		}
		else
		{
			break;
		}

		/*Obtain the number of invalid tries this far*/
		nNumOfInvalidTries = nMaxTries;

		tbstrAppPrefName = INVALID_TRIES_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteNumOfInvalidTries), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		pPTAProtectedStorage->EndRead();

		if ( VS_SUCCESS == retVal )
		{
			nNumOfInvalidTries = *pbyteNumOfInvalidTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteNumOfInvalidTries);
		}
		else
		{
			break;
		}

		/*Obtain the unlock period*/
		tbstrAppPrefName = UNLOCK_PERIOD_NAME ;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteUnlockPeriod), (_VS_DWORD*)(&dwUnlockPeriodSize));
		pPTAProtectedStorage->EndRead();

		if ( VS_SUCCESS == retVal )
		{
			nUnlockPeriod = *pbyteUnlockPeriod;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteUnlockPeriod);
		}
		else
		{
			break;
		}

		/*Obtain the current time*/
		GetSystemTimeAsFileTime(&ftCurrTime);
		
		//If the number of invalid tries is greater than or equal to the max tries
		if(nNumOfInvalidTries >= nMaxTries)
		{
			/*Obtain the time of the last invalid try*/
			tbstrAppPrefName = LAST_INVALIDTRY_NAME;
			pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
			retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteLastInvalidTry), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
			pPTAProtectedStorage->EndRead();

			if ( VS_SUCCESS == retVal )
			{
				ftLastInvalidTry = *((FILETIME*)pbyteLastInvalidTry);
				pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteLastInvalidTry);
			}
			else
			{
				break;
			}
						
		
			//If currenttime - invalidtime < unlock period
			_int64 n64CurrTime =  (*(_int64*)(&ftCurrTime));
			_int64 n64LastInvalidTry =  (*(_int64*)(&ftLastInvalidTry));
			_int64 n64TheDiff = n64CurrTime - n64LastInvalidTry;
			
			int nDiffMinutes = (int)(n64TheDiff/(10000000))/60;

			if(nDiffMinutes < nUnlockPeriod)
			{
				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;
				
				//Return locked out error
				retVal = E_PROFLOCKEDOUT;
				break;
			}
		}

		retVal = BeginWrite(pProtectedStorage, BLOCK_FOR_X_SECONDS,BEGINWRITE_BLOCK_PERIOD);
		if ( S_OK != retVal )
		{
			break;
		}

		boolBeginWriteCalled =	TRUE;

		if ( m_boolRoaming )
		{
			vsrmNewPassword.valueType	=	PASSWORD_VALUE_TYPE_UNICODE;
			vsrmNewPassword.pszValue	=	i_tbstrNewPasswd;

			vsrmOldPassword.valueType =	PASSWORD_VALUE_TYPE_UNICODE;
			vsrmOldPassword.pszValue =	i_tbstrOldPasswd;

			vsrmStatus =	VSRM_ChangePassword
							(
								m_SessionHandle,
								&vsrmOldPassword,
								&vsrmNewPassword
							);
			if(VSRM_ERR_WRONG_PASSWORD == vsrmStatus)
			{
				retVal = E_INVALIDPASSWD;
				break;
			}
			else if(VSRM_ERR_ATTEMPT_EXCEED_THRESHOLD == vsrmStatus)
			{
				retVal = E_PROFLOCKEDOUT;
				break;
			}
			else if ( VSRM_SUCCESS != vsrmStatus )
			{
				retVal =	E_FAIL;
				break;
			}
		}


		retVal =	pProtectedStorage -> ResetPassword
					(
						i_tbstrOldPasswd,
						i_tbstrNewPasswd
					);
		if ( S_OK != retVal )
		{
			if(E_VS_BAD_PASSWORD == retVal)
			{
				nNumOfInvalidTries ++;

				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;	
				retVal = E_INVALIDPASSWD;
			}

			break;
		}
		else
			nNumOfInvalidTries = 0;


		retVal = S_OK;
		break;
	}

	if ( TRUE == boolBeginWriteCalled ) 
	{
		pProtectedStorage -> EndWrite ();
	}

	/*Set the number of invalid tries*/
	if(!m_boolRoaming)
	{
		tbstrAppPrefName = INVALID_TRIES_NAME;
		pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&nNumOfInvalidTries),
			sizeof(nNumOfInvalidTries), 0);
		pPTAProtectedStorage->EndWrite();

		/*Set lastinvalidtry*/
		if(retVal == E_INVALIDPASSWD || retVal == E_PROFLOCKEDOUT)
		{
			tbstrAppPrefName = LAST_INVALIDTRY_NAME;
			pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
			pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&ftLastInvalidTry),
				sizeof(ftLastInvalidTry), 0);
			pPTAProtectedStorage->EndWrite();
		}

	}

#else
		m_tbstrTPMKeyPassword = i_tbstrNewPasswd.copy();
		m_dwTPMKeyPasswordLen =	(::wcslen ( (const wchar_t*) m_tbstrTPMKeyPassword ) + 1) * sizeof (WCHAR);

#endif
	
    return retVal;
}

HRESULT CVirtualSmartCard::VSM_EnterPasswd(_bstr_t i_tbstrThePasswd)
{
	HRESULT				retVal					=	S_OK;

	m_tbstrTPMKeyPassword = i_tbstrThePasswd.copy();
	m_dwTPMKeyPasswordLen =	(::wcslen ( (const wchar_t*) m_tbstrTPMKeyPassword ) + 1) * sizeof (WCHAR);

    return retVal;
}

HRESULT CVirtualSmartCard::VSM_IsPasswdEntered()
{
	if (m_tbstrTPMKeyPassword.length() == 0) {
		return(0);
	}
	else {
		return(1);
	}
}

HRESULT CVirtualSmartCard::VSM_ChangePasswd(_bstr_t& i_tbstrOldPasswd, _bstr_t& i_tbstrNewPasswd)
{
	HRESULT				retVal					=	S_OK;
	VSRM_STATUS			vsrmStatus;
	VSRM_PASSWORD		vsrmNewPassword;
	VSRM_PASSWORD		vsrmOldPassword;
	BOOL				boolBeginWriteCalled	=	FALSE;

	int					nMaxTries;
	int					nNumOfInvalidTries		=	0;
	int					nUnlockPeriod;
	_VS_BYTE*			pbyteMaxTries			= NULL;
	_VS_DWORD*			dwMaxTriesSize;
	_VS_BYTE*			pbyteNumOfInvalidTries	= NULL;
	_VS_DWORD*			dwNumOfInvalidTriesSize;
	_VS_BYTE*			pbyteUnlockPeriod		= NULL;
	_VS_DWORD*			dwUnlockPeriodSize;
	_VS_BYTE*			pbyteLastInvalidTry		= NULL;
	_bstr_t				tbstrAppPrefName		= "";
	FILETIME			ftLastInvalidTry;
	FILETIME			ftCurrTime;

	while (1)
	{
		/*Obtain the maximum number of tries that are allowed*/
		tbstrAppPrefName = MAX_LOCKOUT_TRIES_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteMaxTries), (_VS_DWORD*)&dwMaxTriesSize);
		pPTAProtectedStorage->EndRead();

		if ( VS_SUCCESS == retVal )
		{
			nMaxTries = *pbyteMaxTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteMaxTries);
		}
		else
		{
			break;
		}

		/*Obtain the number of invalid tries this far*/
		nNumOfInvalidTries = nMaxTries;

		tbstrAppPrefName = INVALID_TRIES_NAME;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteNumOfInvalidTries), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
		pPTAProtectedStorage->EndRead();

		if ( VS_SUCCESS == retVal )
		{
			nNumOfInvalidTries = *pbyteNumOfInvalidTries;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteNumOfInvalidTries);
		}
		else
		{
			break;
		}

		/*Obtain the unlock period*/
		tbstrAppPrefName = UNLOCK_PERIOD_NAME ;
		pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
		retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteUnlockPeriod), (_VS_DWORD*)(&dwUnlockPeriodSize));
		pPTAProtectedStorage->EndRead();

		if ( VS_SUCCESS == retVal )
		{
			nUnlockPeriod = *pbyteUnlockPeriod;
			pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteUnlockPeriod);
		}
		else
		{
			break;
		}

		/*Obtain the current time*/
		GetSystemTimeAsFileTime(&ftCurrTime);
		
		//If the number of invalid tries is greater than or equal to the max tries
		if(nNumOfInvalidTries >= nMaxTries)
		{
			/*Obtain the time of the last invalid try*/
			tbstrAppPrefName = LAST_INVALIDTRY_NAME;
			pPTAProtectedStorage->BeginRead(BLOCK_FOR_X_SECONDS, BEGINREAD_BLOCK_PERIOD);
			retVal = pPTAProtectedStorage->GetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE**)(&pbyteLastInvalidTry), (_VS_DWORD*)(&dwNumOfInvalidTriesSize));
			pPTAProtectedStorage->EndRead();

			if ( VS_SUCCESS == retVal )
			{
				ftLastInvalidTry = *((FILETIME*)pbyteLastInvalidTry);
				pPTAProtectedStorage->FreeMemoryBlob((void**)&pbyteLastInvalidTry);
			}
			else
			{
				break;
			}
						
		
			//If currenttime - invalidtime < unlock period
			_int64 n64CurrTime =  (*(_int64*)(&ftCurrTime));
			_int64 n64LastInvalidTry =  (*(_int64*)(&ftLastInvalidTry));
			_int64 n64TheDiff = n64CurrTime - n64LastInvalidTry;
			
			int nDiffMinutes = (int)(n64TheDiff/(10000000))/60;

			if(nDiffMinutes < nUnlockPeriod)
			{
				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;
				
				//Return locked out error
				retVal = E_PROFLOCKEDOUT;
				break;
			}
		}

		retVal = BeginWrite(pProtectedStorage, BLOCK_FOR_X_SECONDS,BEGINWRITE_BLOCK_PERIOD);
		if ( S_OK != retVal )
		{
			break;
		}

		boolBeginWriteCalled =	TRUE;

		if ( m_boolRoaming )
		{
			vsrmNewPassword.valueType	=	PASSWORD_VALUE_TYPE_UNICODE;
			vsrmNewPassword.pszValue	=	i_tbstrNewPasswd;

			vsrmOldPassword.valueType =	PASSWORD_VALUE_TYPE_UNICODE;
			vsrmOldPassword.pszValue =	i_tbstrOldPasswd;

			vsrmStatus =	VSRM_ChangePassword
							(
								m_SessionHandle,
								&vsrmOldPassword,
								&vsrmNewPassword
							);
			if(VSRM_ERR_WRONG_PASSWORD == vsrmStatus)
			{
				retVal = E_INVALIDPASSWD;
				break;
			}
			else if(VSRM_ERR_ATTEMPT_EXCEED_THRESHOLD == vsrmStatus)
			{
				retVal = E_PROFLOCKEDOUT;
				break;
			}
			else if ( VSRM_SUCCESS != vsrmStatus )
			{
				retVal =	E_FAIL;
				break;
			}
		}


		retVal =	pProtectedStorage -> ResetPassword
					(
						i_tbstrOldPasswd,
						i_tbstrNewPasswd
					);
		if ( S_OK != retVal )
		{
			if(E_VS_BAD_PASSWORD == retVal)
			{
				nNumOfInvalidTries ++;

				//lastinvalidtry = currenttime
				ftLastInvalidTry = ftCurrTime;	
				retVal = E_INVALIDPASSWD;
			}

			break;
		}
		else
			nNumOfInvalidTries = 0;


		retVal = S_OK;
		break;
	}

	if ( TRUE == boolBeginWriteCalled ) 
	{
		pProtectedStorage -> EndWrite ();
	}

	/*Set the number of invalid tries*/
	if(!m_boolRoaming)
	{
		tbstrAppPrefName = INVALID_TRIES_NAME;
		pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
		pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&nNumOfInvalidTries),
			sizeof(nNumOfInvalidTries), 0);
		pPTAProtectedStorage->EndWrite();

		/*Set lastinvalidtry*/
		if(retVal == E_INVALIDPASSWD || retVal == E_PROFLOCKEDOUT)
		{
			tbstrAppPrefName = LAST_INVALIDTRY_NAME;
			pPTAProtectedStorage->BeginWrite(BLOCK_FOR_X_SECONDS, BEGINWRITE_BLOCK_PERIOD);
			pPTAProtectedStorage->SetApplicationPreference((_VS_CHAR*)tbstrAppPrefName, (_VS_BYTE*)(&ftLastInvalidTry),
				sizeof(ftLastInvalidTry), 0);
			pPTAProtectedStorage->EndWrite();
		}

	}

	
    return retVal;
}


HRESULT		CVirtualSmartCard::VSM_TPMInitialize
(
	const CHAR*			i_cszContainerName,
	const DWORD			i_cdwOpenCreate,
	const void*         i_cPTA
)
{
	HRESULT							hResult				=	E_FAIL;
	DWORD							dwResult			=	999;

	while (1)
	{
		_bstr_t		tbstrUserName = "";
		_bstr_t		tbstrProfileIssUniqueID = "";

		m_dwIsTPM = 1;
		m_tbstrTPMKeyPassword =	"";
		m_dwTPMKeyPasswordLen = 0;


	    // Need to use RegOpenCurrentUser to map HKEY_CURRENT_USER to
	    // proper HKEY_USERS\User's SID key. Otherwise, it is not mapped to 
	    // proper user's registry key when the user is impersonated in the service.

	    // RegOpenCurrentUser function is available only on Windows 2000 and later.
		// It is not present on Win95/98/NT and so if the function is called directly the 
		// registration fails. so we have to do a load library followed by the getprocaddress 
		// for the "RegOpenCurrentUser" function.
	    // This fix is specifically made for Windows 2000 and later.

		m_hModAdvapiDll = ::LoadLibrary("advapi32.dll");
		if(NULL == m_hModAdvapiDll)
		{
			hResult = E_ADVAPI32LOADFAILED;
			break;
		}

		lpfnRegOpenCurrentUser = (LPFNRegOpenCurrentUser) ::GetProcAddress
								(
									m_hModAdvapiDll, 
									"RegOpenCurrentUser"
								);

		if(NULL != lpfnRegOpenCurrentUser)
		{
			// It is windows 2000 or later
			HRESULT lResult =	lpfnRegOpenCurrentUser
						(
							KEY_ALL_ACCESS,
							&m_hCurrUserKey
						);

			if ( ERROR_SUCCESS != lResult )
			{
				m_hCurrUserKey = HKEY_CURRENT_USER;
			}

		}

		m_pvoidObjectPTA = (void *)i_cPTA;

		tbstrContainerName =	i_cszContainerName;

#ifdef VS_TSSDLL
		// Check dependency dlls for IBM TSS first. This check is done to avoid the warning dialog that 
		// is displayed when trying to load vs_ibmtss.dll with one of the dependency dlls missing. Otherwise,
		// it will show "Unable to locate dll ..." dialog
		BOOL boolDependencyDlls = FALSE;
		if(::LoadLibrary("tcpatrace.dll") && ::LoadLibrary("calltcs.dll") && ::LoadLibrary("getpin.dll") && ::LoadLibrary("tcpaps.dll"))
			boolDependencyDlls = TRUE;

		if(boolDependencyDlls)
			m_hModTSSDll = ::LoadLibrary("vs_ibmtss.dll");
		else
			m_hModTSSDll  = NULL;

		if(NULL == m_hModTSSDll)
		{
			BOOL boolInfineon = FALSE;
			CheckForInfineonTPM( &boolInfineon );

			if(boolInfineon == TRUE)
			{
				m_dwTSSVendor = INFINEON_TSS;
				m_hModTSSDll = ::LoadLibrary("vs_infytss.dll");	
				if(NULL == m_hModTSSDll)
				{
					hResult = E_TSSLIBLOADFAILED;
					break;
				}

			} else {
				hResult = E_TSSLIBLOADFAILED;
				break;
			}
		}

		lpfnCreateContextObject = (LPFNCreateContextObject) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateContextObject"
								);
		lpfnCreateDataObject = (LPFNCreateDataObject) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateDataObject"
								);
		lpfnCreateHashObject = (LPFNCreateHashObject) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateHashObject"
								);

		lpfnCreateKeyObjectURK = (LPFNCreateKeyObjectURK) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateKeyObjectURK"
								);

		lpfnCreateKeyObjectULK = (LPFNCreateKeyObjectULK) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateKeyObjectULK"
								);

		lpfnCreateKeyObjectLoadUK = (LPFNCreateKeyObjectLoadUK) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateKeyObjectLoadUK"
								);


		lpfnCreateKeyObjectImportPublicKey = (LPFNCreateKeyObjectImportPublicKey) ::GetProcAddress
								(
									m_hModTSSDll, 
									"CreateKeyObjectImportPublicKey"
								);
		m_pVSTSSContext = lpfnCreateContextObject(&dwResult);
		if ( 0 != dwResult )
		{
			break;
		}

#else
		
		m_pVSTSSContext = new (VS_TSS_Context) (&dwResult);
		if ( 0 != dwResult )
		{
			break;
		}
#endif // VS_TSSDLL

		hResult =	VSTPM_GetUserStorageRootKey ();
		if ( S_OK != hResult )
		{
			hResult =	VSTPM_CreateUserStorageRootKey ();
			VS_CHECK_HRESULT

		}


		if ( VS_TPM_CONTAINER_CREATE == i_cdwOpenCreate )
		{
				//	make sure that the container does not exist
				//	and create an empty container
			hResult =	VSTPM_CheckIfContainerExists ();
			if ( S_OK == hResult )
			{
				//	that means the container already exists
				hResult =	E_FAIL;
				break;
			}
			else
			{
					//	create empty container
				m_structTPMContainer.structExchangeKey.dwKeyExists		=	0;
				m_structTPMContainer.structExchangeKey.dwKeyExportable	=	0;
				m_structTPMContainer.structExchangeKey.dwKeyLength		=	0;
				m_structTPMContainer.structSignatureKey.dwKeyExists		=	0;
				m_structTPMContainer.structSignatureKey.dwKeyExportable	=	0;
				m_structTPMContainer.structSignatureKey.dwKeyLength		=	0;
				m_structTPMContainer.pbyteExchangePublicKey				=	NULL;
				m_structTPMContainer.dwExchangePubKeyLen				=	0;
				m_structTPMContainer.pbyteSigningPublicKey				=	NULL;
				m_structTPMContainer.dwSignaturePubKeyLen				=	0;
				VS_TPM_CSP_INIT_UUID_WITH_ZEROS(m_structTPMContainer.structExchangeKey.uuidKeyUUID)
//				VS_TPM_CSP_INIT_UUID_WITH_ZEROS(m_structTPMContainer.structExchangeKey.uuidWrappingKeyUUID)
				VS_TPM_CSP_INIT_UUID_WITH_ZEROS(m_structTPMContainer.structSignatureKey.uuidKeyUUID)
//				VS_TPM_CSP_INIT_UUID_WITH_ZEROS(m_structTPMContainer.structSignatureKey.uuidWrappingKeyUUID)

				hResult =	VSTPM_SetUserContainerDetails ();
				VS_CHECK_HRESULT
			}
		}
		else
		{
			if ( VS_TPM_CONTAINER_OPEN == i_cdwOpenCreate )
			{
					//	make sure that the container exists and
					//	read teh container details
				hResult =	VSTPM_CheckIfContainerExists ();
				VS_CHECK_HRESULT

				hResult =	VSTPM_GetUserContainerDetails ();
				VS_CHECK_HRESULT
			}
		}

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSM_TPMInitialize


HRESULT CVirtualSmartCard::VSTPM_GetUserStorageRootKey ()
{
	HRESULT				hResult								=	9999;
	LONG				lResult								=	9999;

	_bstr_t				tbstrUserSRKRegistry				=	"";
	HKEY				hRegistryUserSRK					=	NULL;
	DWORD				dwDisposition						=	9999;

	_bstr_t				tbstrRegistryValue					=	"";
	DWORD				dwValueType							=	9999;
	BYTE				pbyteValue [MAX_PATH];
	DWORD				dwValueLen							=	MAX_PATH;

	_bstr_t				tbstrUserRootUUID					=	"";
//	_bstr_t				tbstrUserRootPassword				=	"";


	while (1)
	{
		tbstrUserSRKRegistry =	VS_USER_ROOT_KEY_REG;

			//	open the key HKCU\Software\TSS\RootKey0
		lResult =	::RegOpenKeyEx
					(
						m_hCurrUserKey,
						tbstrUserSRKRegistry,
						0,
						KEY_ALL_ACCESS,
						&hRegistryUserSRK
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

		tbstrRegistryValue =	VS_USER_ROOT_KEY_VALUE;

					//	Read the vlaue RootKeyUUID
		lResult =	::RegQueryValueEx
					(
						hRegistryUserSRK,
						tbstrRegistryValue,
						NULL,
						&dwValueType,
						pbyteValue,
						&dwValueLen
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

		tbstrUserRootUUID =	(CHAR*) pbyteValue;
		::UuidFromStringW ( tbstrUserRootUUID, &m_uuidUserRootKey );

		tbstrRegistryValue =	VS_USER_ROOT_KEY_PASSWORD;
		dwValueLen	=	MAX_PATH;

					//	Read the value RootKeyPassword
		lResult =	::RegQueryValueEx
					(
						hRegistryUserSRK,
						tbstrRegistryValue,
						NULL,
						&dwValueType,
						pbyteValue,
						&dwValueLen
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

		m_tbstrUserRootPassword = (CHAR*) pbyteValue;

		hResult =	S_OK;
		break;
	}	//	end	while (1)

	if ( NULL != hRegistryUserSRK )
	{
		::RegCloseKey (hRegistryUserSRK);
	}

	return	hResult;
}	//	end		HRESULT CVirtualSmartCard::VSTPM_GetUserStorageRootKey

HRESULT CVirtualSmartCard::VSTPM_CreateUserStorageRootKey ()
{
	HRESULT				hResult								=	9999;
	LONG				lResult								=	9999;

	_bstr_t				tbstrUserSRKRegistry				=	"";
	HKEY				hRegistryUserSRK					=	NULL;
	DWORD				dwDisposition						=	9999;

	_bstr_t				tbstrValueName						=	"";
	DWORD				dwValueType							=	9999;
	DWORD				dwValueLen							=	0;

	unsigned char*		pszUserRootKey						=	NULL;
	UUID				uuidUserRootPassword;
	unsigned char*		pszUserRootPassword					=	NULL;
	DWORD				dwUserRootPasswordLength			=	0;

	RPC_STATUS			rpcResult							=	999;


	while (1)
	{
		rpcResult =	::UuidCreate
					(
						&m_uuidUserRootKey
					);
		if ( RPC_S_OK != rpcResult )
		{
			hResult =	E_FAIL;
			break;
		}

		rpcResult =	::UuidCreate
					(
						&uuidUserRootPassword
					);
		if ( RPC_S_OK != rpcResult )
		{
			hResult =	E_FAIL;
			break;
		}

		rpcResult =	::UuidToString
					(
						&uuidUserRootPassword,
						&pszUserRootPassword
					);
		if ( RPC_S_OK != rpcResult )
		{
			hResult =	E_FAIL;
			break;
		}

		m_tbstrUserRootPassword =	(char *) pszUserRootPassword;
		dwUserRootPasswordLength =	(::wcslen ( (const wchar_t*) m_tbstrUserRootPassword ) + 1) * sizeof (WCHAR);

#ifdef VS_TSSDLL
		m_pUsersRootKey =	lpfnCreateKeyObjectURK
							(
								m_pVSTSSContext,
								m_uuidUserRootKey,
								dwUserRootPasswordLength,
								(BYTE*) ((WCHAR*) m_tbstrUserRootPassword),
								(DWORD*) &hResult 
							);
#else
			//	call Feng's library to create a root key for the user
		m_pUsersRootKey =	new (VS_TSS_Key)
							(
								m_pVSTSSContext,
								m_uuidUserRootKey,
								dwUserRootPasswordLength,
								(BYTE*) ((WCHAR*) m_tbstrUserRootPassword),
								(DWORD*) &hResult 
							);
#endif // VS_TSSDLL
		VS_CHECK_HRESULT




		tbstrUserSRKRegistry =	VS_USER_ROOT_KEY_REG;

			//	create/open the key HKCU\Software\TSS\RootKey0
		lResult =	::RegCreateKeyEx
					(
						m_hCurrUserKey,
						tbstrUserSRKRegistry,
						0,
						NULL,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,NULL,
						&hRegistryUserSRK,
						&dwDisposition
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

		rpcResult =	::UuidToString
					(
						&m_uuidUserRootKey,
						&pszUserRootKey
					);
		if ( RPC_S_OK != rpcResult )
		{
			hResult =	E_FAIL;
			break;
		}

		tbstrValueName	=	VS_USER_ROOT_KEY_VALUE;
		dwValueType		=	REG_SZ;
					//	set the vlaue RootKeyUUID
		lResult =	::RegSetValueEx
					(
						hRegistryUserSRK,
						tbstrValueName,
						0,
						dwValueType,
						(BYTE *) pszUserRootKey,
						strlen ((const char*)pszUserRootKey)
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

		tbstrValueName	=	VS_USER_ROOT_KEY_PASSWORD;
		dwValueType		=	REG_SZ;

					//	set the vlaue RootKeyPassword
		lResult =	::RegSetValueEx
					(
						hRegistryUserSRK,
						tbstrValueName,
						0,
						dwValueType,
						(BYTE *) pszUserRootPassword,
						strlen ((const char*)pszUserRootPassword)
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}
		
		hResult =	S_OK;
		break;
	}	//	end	while (1)

	if ( NULL != hRegistryUserSRK )
	{
		::RegCloseKey (hRegistryUserSRK);
	}

	return	hResult;
}	//	end		HRESULT CVirtualSmartCard::VSTPM_CreateUserStorageRootKey ()


HRESULT		CVirtualSmartCard::VSTPM_GetUserContainerDetails ()
{
	HRESULT						hResult					=	E_FAIL;
	LONG						lResult					=	9999;

	_bstr_t						tbstrKeyName			=	"";
	HKEY						hKeyContainer			=	NULL;

	_bstr_t						tbstrValueName			=	"";
	DWORD						dwValueType				=	9999;
	BYTE						pbyteValue [10000];
	DWORD						dwValueLen				=	10000;


	while (1)
	{
		tbstrKeyName =	VS_TSS_CONTAINERS;
		tbstrKeyName +=	tbstrContainerName;

			//	open the key HKCU\Software\TSS\RootKey0
		lResult =	::RegOpenKeyEx
					(
						m_hCurrUserKey,
						tbstrKeyName,
						0,
						KEY_ALL_ACCESS,
						&hKeyContainer
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

			//	read exchange key details
		tbstrValueName	=	VS_CONTAINER_XKEY;
		dwValueLen		=	10000;

		lResult =	::RegQueryValueEx
					(
						hKeyContainer,
						tbstrValueName,
						0,
						&dwValueType,
						pbyteValue,
						&dwValueLen
					);
		if ( (ERROR_SUCCESS == lResult) || (REG_BINARY == dwValueType) )
		{
			::memcpy
			(
				(void*) &(m_structTPMContainer.structExchangeKey),
				(const void*) pbyteValue,
				dwValueLen
			);
		}

			//	read signature key details
		tbstrValueName	=	VS_CONTAINER_SKEY;
		dwValueLen		=	10000;

		lResult =	::RegQueryValueEx
					(
						hKeyContainer,
						tbstrValueName,
						0,
						&dwValueType,
						pbyteValue,
						&dwValueLen
					);
		if ( (ERROR_SUCCESS == lResult) || (REG_BINARY == dwValueType) )
		{
			::memcpy
			(
				(void*) &(m_structTPMContainer.structSignatureKey),
				(const void*) pbyteValue,
				dwValueLen
			);
		}

			//	read exchange public key 
		tbstrValueName	=	VS_CONTAINER_X_PUBKEY;
		dwValueLen		=	10000;

		lResult =	::RegQueryValueEx
					(
						hKeyContainer,
						tbstrValueName,
						0,
						&dwValueType,
						pbyteValue,
						&dwValueLen
					);
		if ( (ERROR_SUCCESS == lResult) || (REG_BINARY == dwValueType) )
		{
			::memcpy
			(
				(void*) &(m_structTPMContainer.pbyteExchangePublicKey),
				(const void*) pbyteValue,
				dwValueLen
			);

			m_structTPMContainer.dwExchangePubKeyLen =	dwValueLen;
		}
		else
		{
			m_structTPMContainer.pbyteExchangePublicKey	=	NULL;
			m_structTPMContainer.dwExchangePubKeyLen	=	0;
		}
		
			//	read singature public key 
		tbstrValueName	=	VS_CONTAINER_S_PUBKEY;
		dwValueLen		=	10000;

		lResult =	::RegQueryValueEx
					(
						hKeyContainer,
						tbstrValueName,
						0,
						&dwValueType,
						pbyteValue,
						&dwValueLen
					);
		if ( (ERROR_SUCCESS == lResult) || (REG_BINARY == dwValueType) )
		{
			::memcpy
			(
				(void*) &(m_structTPMContainer.pbyteSigningPublicKey),
				(const void*) pbyteValue,
				dwValueLen
			);

			m_structTPMContainer.dwSignaturePubKeyLen =	dwValueLen;
		}
		else
		{
			m_structTPMContainer.pbyteSigningPublicKey	=	NULL;
			m_structTPMContainer.dwSignaturePubKeyLen	=	0;
		}

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	if ( NULL != hKeyContainer )
	{
		::RegCloseKey (hKeyContainer);
	}

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSTPM_GetUserContainerDetails ()

HRESULT		CVirtualSmartCard::VSTPM_SetUserContainerDetails ()
{
	HRESULT						hResult					=	E_FAIL;
	LONG						lResult					=	999;

	_bstr_t						tbstrKeyName			=	"";
	HKEY						hKeyContainer			=	NULL;
	DWORD						dwDisposition			=	9999;

	_bstr_t						tbstrValueName			=	"";
	DWORD						dwValueType				=	9999;
	DWORD						dwValueLen				=	0;


	while (1)
	{
		tbstrKeyName =	VS_TSS_CONTAINERS;
		tbstrKeyName +=	tbstrContainerName;

			//	create/open the key HKCU\Software\TSS\RootKey0
		lResult =	::RegCreateKeyEx
					(
						m_hCurrUserKey,
						tbstrKeyName,
						0,
						NULL,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,NULL,
						&hKeyContainer,
						&dwDisposition
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}
			//	store the exchange key details if it exists
//		if ( VS_CSP_KEY_EXISTS == m_structTPMContainer.structExchangeKey.dwKeyExists )
		{
			tbstrValueName	=	VS_CONTAINER_XKEY;
			dwValueType		=	REG_BINARY;
			dwValueLen		=	sizeof (VS_TPM_CSP_Key_Container);

			lResult =	::RegSetValueEx
						(
							hKeyContainer,
							tbstrValueName,
							0,
							dwValueType,
							(CONST BYTE *) &(m_structTPMContainer.structExchangeKey),
							dwValueLen
						);
			if ( ERROR_SUCCESS != lResult )
			{
				hResult =	E_FAIL;
				break;
			}
		}

			//	store the signature key details if it exists
//		if ( VS_CSP_KEY_EXISTS == m_structTPMContainer.structSignatureKey.dwKeyExists )
		{
			tbstrValueName	=	VS_CONTAINER_SKEY;
			dwValueType		=	REG_BINARY;
			dwValueLen		=	sizeof (VS_TPM_CSP_Key_Container);

			lResult =	::RegSetValueEx
						(
							hKeyContainer,
							tbstrValueName,
							0,
							dwValueType,
							(CONST BYTE *) &(m_structTPMContainer.structSignatureKey),
							dwValueLen
						);
			if ( ERROR_SUCCESS != lResult )
			{
				hResult =	E_FAIL;
				break;
			}
		}

			//	store the exchange pub key if possible
		if ( NULL != m_structTPMContainer.pbyteExchangePublicKey )
		{
			tbstrValueName	=	VS_CONTAINER_X_PUBKEY;
			dwValueType		=	REG_BINARY;
			dwValueLen		=	m_structTPMContainer.dwExchangePubKeyLen;

			lResult =	::RegSetValueEx
						(
							hKeyContainer,
							tbstrValueName,
							0,
							dwValueType,
							(CONST BYTE *) &(m_structTPMContainer.pbyteExchangePublicKey),
							dwValueLen
						);
			if ( ERROR_SUCCESS != lResult )
			{
				hResult =	E_FAIL;
				break;
			}
		}

			//	store the exchange pub key if possible
		if ( NULL != m_structTPMContainer.pbyteSigningPublicKey )
		{
			tbstrValueName	=	VS_CONTAINER_S_PUBKEY;
			dwValueType		=	REG_BINARY;
			dwValueLen		=	m_structTPMContainer.dwSignaturePubKeyLen;

			lResult =	::RegSetValueEx
						(
							hKeyContainer,
							tbstrValueName,
							0,
							dwValueType,
							(CONST BYTE *) &(m_structTPMContainer.pbyteSigningPublicKey),
							dwValueLen
						);
			if ( ERROR_SUCCESS != lResult )
			{
				hResult =	E_FAIL;
				break;
			}
		}

		hResult =	S_OK;
		break;
	}	//	end		while (0)

	if ( NULL != hKeyContainer )
	{
		::RegCloseKey (hKeyContainer);
	}

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSTPM_SetUserContainerDetails ()

HRESULT		CVirtualSmartCard::VSTPM_CheckIfContainerExists ()
{
	HRESULT						hResult					=	E_FAIL;
	LONG						lResult					=	9999;

	_bstr_t						tbstrKeyName			=	"";
	HKEY						hKeyContainer			=	NULL;

	while (1)
	{
		tbstrKeyName =	VS_TSS_CONTAINERS;
		tbstrKeyName +=	tbstrContainerName;

			//	open the key "HKCU\SOFTWARE\VeriSign, Inc.\Pta3 TSS\Keys\ContainerName
		lResult =	::RegOpenKeyEx
					(
						m_hCurrUserKey,
						tbstrKeyName,
						0,
						KEY_ALL_ACCESS,
						&hKeyContainer
					);
		if ( ERROR_SUCCESS != lResult )
		{
			hResult =	E_FAIL;
			break;
		}

		hResult =	S_OK;
		break;
	}	//	end		while (0)

	if ( NULL != hKeyContainer )
	{
		::RegCloseKey (hKeyContainer);
	}

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSTPM_CheckIfContainerExists ()

HRESULT		CVirtualSmartCard::VSTPM_CheckIfKeyExists
(
	const DWORD		i_cdwAlgID,
	DWORD*			o_pdwExists
)
{
	HRESULT						hResult					=	E_FAIL;

	while (1)
	{
		switch ( i_cdwAlgID )
		{
		case	VS_RSA_KEYX:
			if ( 1 == (m_structTPMContainer.structExchangeKey).dwKeyExists )
			{
				*o_pdwExists =	1;
				hResult =	S_OK;
			}
			else
			{
				*o_pdwExists =	0;
				hResult =	S_OK;
			}

			break;

		case	VS_RSA_SIGN:
			if ( 1 == (m_structTPMContainer.structSignatureKey).dwKeyExists )
			{
				*o_pdwExists =	1;
				hResult =	S_OK;
			}
			else
			{
				*o_pdwExists =	0;
				hResult =	S_OK;
			}

			break;

		default:
			hResult =	E_FAIL;
		}	//	end		switch (i_cdwAlgID)

		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSTPM_CheckIfKeyExists


HRESULT		CVirtualSmartCard::VSTPM_CreateKey
(
	const DWORD				i_cdwKeyLength,
	const DWORD				i_cdwKeyUsage,
	VS_TSS_Key**			o_ppVSTSSKey
)
{
	HRESULT						hResult					=	E_FAIL;
	RPC_STATUS					rpcResult				=	999;
	DWORD						dwRootKeyPasswordLen	=	0;

	while (1)
	{
		rpcResult =	::UuidCreate
					(
						&m_uuidMyKey
					);
		if ( RPC_S_OK != rpcResult )
		{
			hResult =	E_FAIL;
			break;
		}

		dwRootKeyPasswordLen =	(::wcslen ( (const wchar_t*) m_tbstrUserRootPassword ) + 1) * sizeof (WCHAR);
#ifdef VS_TSSDLL
		*o_ppVSTSSKey =	lpfnCreateKeyObjectULK
						(
							m_pVSTSSContext,
							i_cdwKeyLength,
							TSS_KEY_TYPE_LEGACY,
							m_uuidMyKey,
							m_dwTPMKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrTPMKeyPassword),
							m_uuidUserRootKey,
							dwRootKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrUserRootPassword),
							(DWORD*) &hResult
						);

#else
		*o_ppVSTSSKey =	new (VS_TSS_Key)
						(
							m_pVSTSSContext,
							i_cdwKeyLength,
							TSS_KEY_TYPE_LEGACY,
							m_uuidMyKey,
							m_dwTPMKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrTPMKeyPassword),
							m_uuidUserRootKey,
							dwRootKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrUserRootPassword),
							(DWORD*) &hResult
						);
#endif // VS_TSSDLL
		VS_CHECK_HRESULT

		if ( VS_RSA_KEYX == i_cdwKeyUsage )
		{
			m_structTPMContainer.structExchangeKey.dwKeyExists		=	1;
			m_structTPMContainer.structExchangeKey.dwKeyExportable	=	0;
			m_structTPMContainer.structExchangeKey.dwKeyLength		=	i_cdwKeyLength;
			m_structTPMContainer.pbyteExchangePublicKey				=	NULL;
			m_structTPMContainer.dwExchangePubKeyLen				=	0;
			::memcpy
			(
				(void*) &(m_structTPMContainer.structExchangeKey.uuidKeyUUID),
				(const void*) &m_uuidMyKey,
				sizeof (UUID)
			);
//				VS_TPM_CSP_INIT_UUID_WITH_JUNK(m_structTPMContainer.structExchangeKey.uuidWrappingKeyUUID)
		}
		else
		{
			m_structTPMContainer.structSignatureKey.dwKeyExists		=	1;
			m_structTPMContainer.structSignatureKey.dwKeyExportable	=	0;
			m_structTPMContainer.structSignatureKey.dwKeyLength		=	i_cdwKeyLength;
			m_structTPMContainer.pbyteSigningPublicKey				=	NULL;
			m_structTPMContainer.dwSignaturePubKeyLen				=	0;
			::memcpy
			(
				(void*) &(m_structTPMContainer.structSignatureKey.uuidKeyUUID),
				(const void*) &m_uuidMyKey,
				sizeof (UUID)
			);
//				VS_TPM_CSP_INIT_UUID_WITH_JUNK(m_structTPMContainer.structSignatureKey.uuidWrappingKeyUUID)
		}

		hResult =	VSTPM_SetUserContainerDetails ();
		VS_CHECK_HRESULT							

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSTPM_CreateKey

HRESULT		CVirtualSmartCard::VSTPM_GetKey
(
	const DWORD				i_cdwAlgoID,
	DWORD*					o_pdwKeyLength,
	DWORD*					o_pdwKeyExportable,
	VS_TSS_Key**			o_ppVSTSSKey
)
{
	HRESULT						hResult					=	E_FAIL;
	RPC_STATUS					rpcResult				=	999;
	DWORD						dwRootKeyPasswordLen	=	0;
	DWORD						dwExists				=	999;

	while (1)
	{
		hResult =	VSTPM_CheckIfKeyExists
					(
						i_cdwAlgoID,
						&dwExists
					);
		if ( 0 == dwExists || S_OK != hResult )
		{
			hResult =	NTE_NO_KEY;
			break;
		}

		if ( VS_RSA_KEYX == i_cdwAlgoID )
		{
			::memcpy
			(
				(void*) &m_uuidMyKey,
				(const void*) &(m_structTPMContainer.structExchangeKey.uuidKeyUUID),
				sizeof (UUID)
			);
		}
		else
		{
			::memcpy
			(
				(void*) &m_uuidMyKey,
				(const void*) &(m_structTPMContainer.structSignatureKey.uuidKeyUUID),
				sizeof (UUID)
			);
		}

		dwRootKeyPasswordLen =	(::wcslen ( (const wchar_t*) m_tbstrUserRootPassword ) + 1) * sizeof (WCHAR);

		if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
			hResult = ((CVSPTA*)m_pvoidObjectPTA)->EnterPassword();
			VS_CHECK_HRESULT
		}

#ifdef VS_TSSDLL
		*o_ppVSTSSKey =	lpfnCreateKeyObjectLoadUK
						(
							m_pVSTSSContext,
							m_uuidMyKey,
							m_dwTPMKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrTPMKeyPassword),
							m_uuidUserRootKey,
							dwRootKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrUserRootPassword),
							(DWORD*) &hResult
						);

#else
		*o_ppVSTSSKey =	new (VS_TSS_Key)
						(
							m_pVSTSSContext,
							m_uuidMyKey,
							m_dwTPMKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrTPMKeyPassword),
							m_uuidUserRootKey,
							dwRootKeyPasswordLen,
							(BYTE*) ((WCHAR*) m_tbstrUserRootPassword),
							(DWORD*) &hResult
						);
#endif // VS_TSSDLL
		VS_CHECK_HRESULT

		hResult = (*o_ppVSTSSKey) -> GetKeyLength
						   (
								o_pdwKeyLength
						   );

		VS_CHECK_HRESULT

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		HRESULT		CVirtualSmartCard::VSTPM_GetKey


HRESULT		CVirtualSmartCard::VSTPM_CreateHashObject
(
	VS_TSS_Hash**			o_ppVSTSSHash
)
{
	HRESULT						hResult					=	E_FAIL;
	
	DWORD						dwAlgoID				=	VS_SHA_1;

	while (1)
	{
#ifdef VS_TSSDLL

		m_pVSTSSHash =	lpfnCreateHashObject
						(
							m_pVSTSSContext,
							dwAlgoID,
							(DWORD*) &hResult
						);

#else
		m_pVSTSSHash =	new (VS_TSS_Hash)
						(
							m_pVSTSSContext,
							dwAlgoID,
							(DWORD*) &hResult
						);
#endif // VS_TSSDLL
		VS_CHECK_HRESULT

		*o_ppVSTSSHash =	m_pVSTSSHash;

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_CreateHashObject


HRESULT		CVirtualSmartCard::VSTPM_HashData
(
	const VS_TSS_Hash*		i_cpVSTSSHash,
	const DWORD				i_cdwDataLen,
	const BYTE*				i_cpbyteData
)
{
	HRESULT						hResult					=	E_FAIL;

	while (1)
	{
		VSCSP_CHECK_INPUT_POINTER_FOR_NULL (i_cpVSTSSHash)
			
		m_pVSTSSHash =	(VS_TSS_Hash*) i_cpVSTSSHash;

		hResult =	m_pVSTSSHash -> UpdateHashValue
					(
						i_cdwDataLen,
						i_cpbyteData
					);
		VS_CHECK_HRESULT

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_HashData


HRESULT		CVirtualSmartCard::VSTPM_GetHash
(
	DWORD*					o_pdwDataLen,
	BYTE**					o_ppbyteData
)
{
	HRESULT						hResult					=	E_FAIL;

	while (1)
	{
		hResult =	m_pVSTSSHash -> GetHashValue
					(
						o_pdwDataLen,
						o_ppbyteData
					);
		VS_CHECK_HRESULT

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_GetHash


HRESULT		CVirtualSmartCard::VSTPM_SignHash
(
	VS_TSS_Hash*			i_pVSTSSHash,
	const DWORD				i_cdwKeySpec,
	BYTE*					o_pbSignature,
	DWORD*					o_pdwSigLen
)
{
	HRESULT						hResult					=	E_FAIL;

	DWORD						dwAlgID					=	0;
	DWORD						dwKeyLength				=	0;
	DWORD						dwKeyExportable			=	0;
	VS_TSS_Key*					pVSTSSKey				=	NULL;

	DWORD						dwSignatureLen			=	0;
	BYTE*						pbyteSignature			=	NULL;

	while (1)
	{
		hResult =	VSTPM_GetKey
					(
						i_cdwKeySpec,
						&dwKeyLength,
						&dwKeyExportable,
						&pVSTSSKey
					);
		VS_CHECK_HRESULT

		hResult =	pVSTSSKey -> GetModulusLength (&dwSignatureLen);
		VS_CHECK_HRESULT

		if ( NULL == o_pbSignature )
		{
			*o_pdwSigLen =	dwSignatureLen;
			hResult =	S_OK;
			break;
		}

		if ( *o_pdwSigLen < dwSignatureLen )
		{
			*o_pdwSigLen =	dwSignatureLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

		hResult =	i_pVSTSSHash -> Sign
					(
						pVSTSSKey,
						&dwSignatureLen,
						&pbyteSignature
					);
		VS_CHECK_HRESULT
		*o_pdwSigLen =	dwSignatureLen;
		::memcpy
		(
			(void*) o_pbSignature,
			(const void*) pbyteSignature,
			dwSignatureLen
		);

		hResult =	S_OK;
		break;
	}

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_SignHash



HRESULT		CVirtualSmartCard::VSTPM_VerifySignature
(
	VS_TSS_Hash*			i_pVSTSSHash,
	VS_TSS_Key*				i_pVSTSSKey,
	const BYTE*				i_cpbSignature,
	DWORD					i_dwSigLen
)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	BYTE*						pbytePubKey					=	NULL;
	DWORD						dwPubKeyLen					=	0;

	BYTE*						pbyteDecryptedSignature		=	NULL;
	DWORD						dwDecryptedSignatureLen		=	0;

	BYTE*						pbyteUnPadedData			=	NULL;
	DWORD						dwUnPadedDataLen			=	0;

	BYTE*						pbyteDataHash				=	NULL;
	DWORD						dwDataHashLen				=	0;

	BYTE*						pbyteData					=	NULL;
	DWORD						dwDataLen					=	0;

	DWORD						dwHashAlgID					= VS_SHA_1;

	int							nCompare					=	999;

	unsigned char f4Data[3] = {0x01, 0x00, 0x01 };
	RSA_Context*		pRSAContext = NULL;

	memset( &RSA_Verify_PublicKey, 0, sizeof(A_RSA_KEY));

	while (1)
	{
			// Check if we are using Infineon TSS. VerifySignature method returns error
			// if HASH_SHA1 algorithm is not used in Infineon case.
		if( m_dwTSSVendor == INFINEON_TSS)
		{

			// get hash data from the hash object and verify the signature
			hResult =	i_pVSTSSHash -> GetHashValue
						(
							&dwDataLen, 
							&pbyteData
						);
			VS_CHECK_HRESULT

			hResult =	i_pVSTSSKey -> GetModulus
						(
							(unsigned long *) &(RSA_Verify_PublicKey.modulus.len), 
							&(RSA_Verify_PublicKey.modulus.data)
						);
			VS_CHECK_HRESULT

			(RSA_Verify_PublicKey.exponent).len =	3;
			(RSA_Verify_PublicKey.exponent).data =	new BYTE [(RSA_Verify_PublicKey.exponent).len];
			CHECK_ALLOCATED_MEMORY ((RSA_Verify_PublicKey.exponent).data)

			memcpy
			(
				(void*) (RSA_Verify_PublicKey.exponent).data,
				(const void*) f4Data,
				(RSA_Verify_PublicKey.exponent).len
			);
			
			pRSAContext =	(RSA_Context*) new RSA_Context;
			CHECK_ALLOCATED_MEMORY (pRSAContext)

			pRSAContext -> dwSizeOfStruct	=	sizeof (RSA_Context);
			pRSAContext -> dwRemainder		=	0;

						//	begin the rsa verify
			nResult =	RSADataBegin
						(
							&RSA_Verify_PublicKey,
							(void**) &(pRSAContext -> pContext)
						);
			VSCSP_CHECK_NRESULT

			dwDecryptedSignatureLen =	i_dwSigLen;
			pbyteDecryptedSignature =	(BYTE*) new BYTE [dwDecryptedSignatureLen];
			CHECK_ALLOCATED_MEMORY (pbyteDecryptedSignature)


			nResult =	RSADataUpdate
						(
							(void*) (pRSAContext -> pContext),
							(unsigned char*) i_cpbSignature,
							(unsigned int) i_dwSigLen,
							(unsigned char*) pbyteDecryptedSignature,
							(unsigned int*) &dwDecryptedSignatureLen
						);
			VSCSP_CHECK_NRESULT

						//	destroy the encryption context
			nResult =	RSADataEnd
						(
							(void*) (pRSAContext -> pContext)
						);
			VSCSP_CHECK_NRESULT

						//	unpad the data
			hResult =	UnPadDataForVerify
						(
							(const BYTE*) pbyteDecryptedSignature,
							(const DWORD) dwDecryptedSignatureLen,
							&pbyteUnPadedData,
							&dwUnPadedDataLen
						);
			VSM_CHECK_HRESULT

			if ( dwDataLen == dwUnPadedDataLen ) 
			{
							//	compare the signature
				nCompare =	memcmp
							(
								(const void*) pbyteUnPadedData,
								(const void*) pbyteData,
								dwUnPadedDataLen
							);

				if ( 0 != nCompare )
				{
					hResult =	NTE_BAD_SIGNATURE;
					break;
				}

				hResult =	S_OK;
				break;

			}

						//	the data along with the algo id is still in form of a sequence
						//	so get the data
			hResult =	GetDataFromSequence
						(
							pbyteUnPadedData,
							dwUnPadedDataLen,
							dwHashAlgID,
							&pbyteDataHash,
							&dwDataHashLen
						);
			VSM_CHECK_HRESULT


						//	compare the signature
			nCompare =	memcmp
						(
							(const void*) pbyteDataHash,
							(const void*) pbyteData,
							dwDataHashLen
							);


			if ( 0 != nCompare )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}

		} else {

			hResult =	i_pVSTSSHash -> VerifySignature
						(
							i_pVSTSSKey,
							i_dwSigLen,
							i_cpbSignature
						);
			VS_CHECK_HRESULT

		}

		hResult =	S_OK;
		break;

	}

	if(pRSAContext)
		delete pRSAContext;

	VSCSP_CHECK_FOR_NULL_AND_DELETE ((RSA_Verify_PublicKey.exponent).data)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteDecryptedSignature, dwDecryptedSignatureLen)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteUnPadedData, dwUnPadedDataLen)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteDataHash, dwDataHashLen)

	return	hResult;

}	//	end		CVirtualSmartCard::VSTPM_VerifySignature


HRESULT		CVirtualSmartCard::VSTPM_EncryptDecryptBegin
(
	const VS_TSS_Key*		i_cpVSTSSKey,
	VS_TSS_Data**			o_ppVSTSSData
)
{
	HRESULT						hResult						=	E_FAIL;

	VS_TSS_Data*				pVSTSSData					=	NULL;

	while (1)
	{
#ifdef VS_TSSDLL
		pVSTSSData =	lpfnCreateDataObject
						(
							m_pVSTSSContext,
							i_cpVSTSSKey,
							(DWORD*) &hResult
						);
#else
		pVSTSSData =	new VS_TSS_Data
						(
							m_pVSTSSContext,
							i_cpVSTSSKey,
							(DWORD*) &hResult
						);
#endif // VS_TSSDLL
		VS_CHECK_HRESULT

		*o_ppVSTSSData =	pVSTSSData;
		
		hResult =	S_OK;
		break;
	}

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_EncryptDecryptBegin


HRESULT		CVirtualSmartCard::VSTPM_Encrypt
(
	VS_TSS_Data*			i_pVSTSSData,
	const BYTE*				i_cpbData,
	const DWORD				i_cdwDataLen,
	BYTE*					o_pbyteOutData,
	DWORD*					o_pdwOutDataLen

)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	BYTE*						pbyteEncryptedData			=	NULL;
	DWORD						dwEncryptedDataLen			=	0;

	while (1)
	{
		hResult =	i_pVSTSSData -> Encrypt
					(
						i_cdwDataLen,
						i_cpbData,
						&dwEncryptedDataLen,
						&pbyteEncryptedData
					);
		VS_CHECK_HRESULT

		if ( NULL == o_pbyteOutData )
		{
			*o_pdwOutDataLen =	dwEncryptedDataLen;
			hResult =	VS_SUCCESS;
			break;
		}
		if ( dwEncryptedDataLen > *o_pdwOutDataLen )
		{
			*o_pdwOutDataLen =	dwEncryptedDataLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

		::memcpy
		(
			(void*) o_pbyteOutData,
			(const void*) pbyteEncryptedData,
			dwEncryptedDataLen
		);

		*o_pdwOutDataLen =	dwEncryptedDataLen;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_Encrypt


HRESULT		CVirtualSmartCard::VSTPM_Decrypt
(
	VS_TSS_Data*			i_pVSTSSData,
	const BYTE*				i_cpbData,
	const DWORD				i_cdwDataLen,
	BYTE*					o_pbyteOutData,
	DWORD*					o_pdwOutDataLen

)
{
	HRESULT						hResult						=	E_FAIL;
	int							nResult						=	999;

	BYTE*						pbyteDecryptedData			=	NULL;
	DWORD						dwDecryptedDataLen			=	0;

	while (1)
	{
		hResult =	i_pVSTSSData -> Decrypt
					(
						i_cdwDataLen,
						i_cpbData,
						&dwDecryptedDataLen,
						&pbyteDecryptedData
					);
		VS_CHECK_HRESULT

		if ( NULL == o_pbyteOutData )
		{
			*o_pdwOutDataLen =	dwDecryptedDataLen;
			hResult =	VS_SUCCESS;
			break;
		}
		if ( dwDecryptedDataLen > *o_pdwOutDataLen )
		{
			*o_pdwOutDataLen =	dwDecryptedDataLen;
			hResult =	ERROR_MORE_DATA;
			break;
		}

		::memcpy
		(
			(void*) o_pbyteOutData,
			(const void*) pbyteDecryptedData,
			dwDecryptedDataLen
		);

		*o_pdwOutDataLen =	dwDecryptedDataLen;
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_Decrypt



HRESULT		CVirtualSmartCard::VSTPM_EncryptDecryptEnd
(
	const VS_TSS_Data*		i_cpVSTSSData
)
{
	HRESULT						hResult						=	E_FAIL;

	while (1)
	{
		hResult =	S_OK;
		break;
	}

	return	hResult;
}	//	end		CVirtualSmartCard::VSTPM_EncryptDecryptEnd


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	get_VSM_ResetPasswordFeature
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This property returns the boolean value that indicates
//						whether the roaming server supports reset password
//						feature or not. 
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::get_VSM_ResetPasswordFeature	(BOOL*	pResetPasswordFeature )
{
	HRESULT hResult = S_OK;

	*pResetPasswordFeature = m_boolResetPasswdFeature;

	return hResult;
}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	put_VSM_RoamProfSecretQuestion
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This property sets the secret question associated with the 
//						the roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::put_VSM_RoamProfSecretQuestion(_bstr_t i_tbstrSecretQuestion)
{
	HRESULT hResult = S_OK;

	m_tbstrSecretQuestion = i_tbstrSecretQuestion.copy();

	return hResult;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	put_VSM_RoamProfSecretAnswer
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This property sets the secret answer associated with the 
//						the roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::put_VSM_RoamProfSecretAnswer(_bstr_t i_tbstrSecretAnswer)
{
	HRESULT hResult = S_OK;

	m_tbstrSecretAnswer = i_tbstrSecretAnswer.copy();

	return hResult;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	VSM_IsResetPasswdSupported
//
//	Parameters
//				i_tbstrClientInfo, i_tbstrClientInfoSig - Input parameters that contain roaming server information
//				o_boolResetPasswd  - Output parameter that indicates whether the roaming server supports reset password feature or not
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function checks if the roaming server supports reset password
//						feature or not. It will set m_boolResetPasswdFeature to TRUE or FALSE
//						based on that.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::VSM_IsResetPasswdSupported(_bstr_t& i_tbstrClientInfo, _bstr_t& i_tbstrClientInfoSig, BOOL* o_boolResetPasswd)
{
	HRESULT retVal = S_OK;

	VSRM_STATUS	vsrmStatus;
	VSRM_SESSION_HANDLE	SessionHandle;
	VSRM_BOOL	bResetEnabled = VSRM_FALSE;


	/*Obtain the blob from the roaming server*/

	vsrmStatus =	VSRM_StartSession
			(
				&SessionHandle,
				NULL,
				NULL,
				(const char*) i_tbstrClientInfo,
				(const char*) i_tbstrClientInfoSig
			);		

	if ( VSRM_SUCCESS != vsrmStatus )
	{
		retVal =	E_ROAMING_START_SESSION_FAILED;
	}
			


	if(retVal == VS_SUCCESS)
	{
		vsrmStatus = VSRM_ResetPasswordEnabled ( SessionHandle, &bResetEnabled);

		if(VSRM_SUCCESS != vsrmStatus)
		{
			retVal = E_ROAMING_QUERYRESETPASSWORD_FAILED;
		}
		else
		{
			m_boolResetPasswdFeature = bResetEnabled;
			*o_boolResetPasswd = bResetEnabled;
		}


		// close the session
		vsrmStatus = VSRM_EndSession ( SessionHandle );
	}


	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	VSM_GetSecretQuestion
//
//	Parameters
//				i_pvarWhichSmartCard - Input parameter that contains user and server information
//				o_tbstrSecretQuestion  - Output parameter that contains secret question associated with the profile
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function retrieves secret question associated with the
//						roaming profile from the roaming server.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::VSM_GetSecretQuestion(VARIANT* i_pvarWhichSmartCard, bstr_t& o_tbstrSecretQuestion)
{
	HRESULT retVal = S_OK;

	VSRM_STATUS	vsrmStatus;
	VSRM_SESSION_HANDLE	SessionHandle;


	_bstr_t		tbstrUserName = "";
	_bstr_t		tbstrProfileIssUniqueID = "";
	_bstr_t		tbstrClientInfo;
	_bstr_t		tbstrClientInfoSig;

	VSRM_CHAR*	vsrmQuestion;

	if ( (VT_ARRAY|VT_VARIANT) == i_pvarWhichSmartCard -> vt )
	{

		retVal =	GetServersFromArray
					(
						i_pvarWhichSmartCard,
						&tbstrClientInfo,
						&tbstrClientInfoSig,
						&tbstrUserName,
						&tbstrProfileIssUniqueID
					);


		vsrmStatus =	VSRM_StartSession
				(
					&SessionHandle,
					tbstrUserName,
					NULL,
					(const char*) tbstrClientInfo,
					(const char*) tbstrClientInfoSig
				);		

		if ( VSRM_SUCCESS != vsrmStatus )
		{
			retVal =	E_ROAMING_START_SESSION_FAILED;
		}
				

		if(retVal == VS_SUCCESS)
		{
			vsrmStatus = VSRM_GetUserQuestion ( SessionHandle, &vsrmQuestion);

			if(VSRM_SUCCESS != vsrmStatus)
			{
				retVal = E_ROAMING_GETUSERQUESTION_FAILED;
			}
			else
			{
				o_tbstrSecretQuestion = vsrmQuestion;
			}


			// close the session
			vsrmStatus = VSRM_EndSession ( SessionHandle );
		}
		
	}

		
	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	VSM_ResetPassword
//
//	Parameters
//				i_pvarWhichSmartCard - Input parameter that contains user and server information
//				i_tbstrSecretAnswer  - Input parameter that contains secret answer associated with the profile
//				i_tbstrNewPasswd	 - Input parameter that contains new password for the profile
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function resets the roaming profile password 
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::VSM_ResetPassword(VARIANT* i_pvarWhichSmartCard, bstr_t& i_tbstrSecretAnswer, bstr_t& i_tbstrNewPasswd)
{
	HRESULT retVal = S_OK;

	VSRM_STATUS	vsrmStatus;
	VSRM_PASSWORD	vsrmPassword;
	VSRM_SESSION_HANDLE	SessionHandle;
	VSRM_ITEM*		pvsrmItemData = NULL;

	_bstr_t		tbstrUserName = "";
	_bstr_t		tbstrProfileIssUniqueID = "";
	_bstr_t		tbstrClientInfo;
	_bstr_t		tbstrClientInfoSig;

	VSRM_CHAR*	vsrmAnswer;

	if ( (VT_ARRAY|VT_VARIANT) == i_pvarWhichSmartCard -> vt )
	{

		retVal =	GetServersFromArray
					(
						i_pvarWhichSmartCard,
						&tbstrClientInfo,
						&tbstrClientInfoSig,
						&tbstrUserName,
						&tbstrProfileIssUniqueID
					);


		vsrmStatus =	VSRM_StartSession
				(
					&SessionHandle,
					tbstrUserName,
					NULL,
					(const char*) tbstrClientInfo,
					(const char*) tbstrClientInfoSig
				);		

		if ( VSRM_SUCCESS != vsrmStatus )
		{
			retVal =	E_ROAMING_START_SESSION_FAILED;
		}
				

		if(retVal == VS_SUCCESS)
		{
			vsrmAnswer = i_tbstrSecretAnswer;

			vsrmPassword.valueType	=	PASSWORD_VALUE_TYPE_UNICODE;
			vsrmPassword.pszValue	=	i_tbstrNewPasswd;

			vsrmStatus = VSRM_ResetPassword ( SessionHandle, vsrmAnswer, &vsrmPassword, &pvsrmItemData);

			if(VSRM_ERR_WRONG_PASSWORD == vsrmStatus)
			{
				retVal = E_RESETPASSWD_WRONGANSWER;
			}
			else if(VSRM_ERR_ATTEMPT_EXCEED_THRESHOLD == vsrmStatus)
			{
				retVal = E_RESETPASSWD_PROFLOCKOUT;
			}
			else if(VSRM_SUCCESS != vsrmStatus)
			{
				retVal = E_RESETPASSWD_FAILED;
			}
			else
			{
				VSRM_DestroyItem(pvsrmItemData);
				VSRM_FreeItem(pvsrmItemData);
			}


			// close the session
			vsrmStatus = VSRM_EndSession ( SessionHandle );
		}
		
	}

		
	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	put_VSM_RoamProfFirstName
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This property sets the first name of the user associated with the 
//						the roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 06-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::put_VSM_RoamProfFirstName(_bstr_t i_tbstrFirstName)
{
	HRESULT hResult = S_OK;

	m_tbstrFirstName = i_tbstrFirstName.copy();

	return hResult;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	put_VSM_RoamProfLastName
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This property sets the last name of the user associated with the 
//						the roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 06-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::put_VSM_RoamProfLastName(_bstr_t i_tbstrLastName)
{
	HRESULT hResult = S_OK;

	m_tbstrLastName = i_tbstrLastName.copy();

	return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	put_VSM_RoamProfEmail
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This property sets the e-mail address of the user associated with the 
//						the roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 06-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::put_VSM_RoamProfEmail(_bstr_t i_tbstrEmail)
{
	HRESULT hResult = S_OK;

	m_tbstrEmail = i_tbstrEmail.copy();

	return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	CheckRoamingVersion
//
//	Parameters
//				i_pvarWhichSmartCard - Input parameter that contains roaming server information
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function checks if the roaming server supports reset password
//						feature or not. It will set m_boolResetPasswdFeature to TRUE or FALSE
//						based on that.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 07-02-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVirtualSmartCard::CheckRoamingVersion (VARIANT* i_pvarWhichSmartCard)
{
	HRESULT retVal = S_OK;
	_bstr_t		tbstrClientInfo;
	_bstr_t		tbstrClientInfoSig;
	_bstr_t		tbstrUserName;
	_bstr_t		tbstrProfileIssUniqueID;
	BOOL bResetPasswd;


			/*Obtain the username, roaming servers and storage servers */
	retVal     =	GetServersFromArray
					(
						i_pvarWhichSmartCard,
						&tbstrClientInfo,
						&tbstrClientInfoSig,
						&tbstrUserName,
						&tbstrProfileIssUniqueID
					);	

	/*Obtain the blob from the roaming server*/
	if(retVal == VS_SUCCESS)
		retVal = VSM_IsResetPasswdSupported(tbstrClientInfo, tbstrClientInfoSig, &bResetPasswd);


	VSPTA_CLEAN_TBSTR(tbstrClientInfo)
	VSPTA_CLEAN_TBSTR(tbstrClientInfoSig)
	VSPTA_CLEAN_TBSTR(tbstrUserName)
	VSPTA_CLEAN_TBSTR(tbstrProfileIssUniqueID)

	return retVal;

}

/* 
  This function checks if Infineon TSS is installed on the client machine or not.
*/
HRESULT CVirtualSmartCard::CheckForInfineonTPM(BOOL* boolExists)
{

	HRESULT hr  = S_OK;

	const CLSID CLSID_TCPAContext = {0xFBCD9C1A,0x72CB,0x47BB,{0x99,0xDD,0x23,0x17,0x55,0x14,0x91,0xDE}};
	IUnknown * pContext = NULL;

	*boolExists = FALSE;

	if(SUCCEEDED(CoCreateInstance(CLSID_TCPAContext, 0, CLSCTX_ALL , __uuidof(IUnknown), (LPVOID *) &pContext)))
	{
		*boolExists = TRUE;
		pContext->Release();
	}

	return hr;
}

HRESULT CVirtualSmartCard::get_VSTPM_TSSVendor(DWORD* o_pdwTSSVendor)
{
	HRESULT hr  = S_OK;

	*o_pdwTSSVendor = m_dwTSSVendor;

	return hr;
}

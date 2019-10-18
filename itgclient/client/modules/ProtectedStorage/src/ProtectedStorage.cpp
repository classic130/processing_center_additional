///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	VSPS_Macros.h										 //
//																			 //
//	Description		:	The file contains the macros used in the project.	 //
//																			 //
//	Date			:	Sept 13, 1999										 //
//																			 //
//	Author			:	Anand Abhyankar										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#include "ProtectedStorage.h"


CProtectedStorage::CProtectedStorage ()
{
	m_InitializeMembers ();
	return;
}


CProtectedStorage::~CProtectedStorage ()
{
	m_DestroyMembers ();
	return;
}


_VS_LONG	CProtectedStorage::Initialize 
(
	const _VS_CHAR*		i_cszApplicationName,
	const _VS_CHAR*		i_cszApplicationHost,
	const _VS_DWORD		i_cnIsApplicationEncrypted,
	const int			i_ncAddApplicationIfItDoesNotExist,
	const _VS_CHAR*		i_cszStorageFileName,
	const _VS_DWORD		i_ncCreateOpenFlag,
	const _VS_CHAR*		i_cszPassword,
	const _VS_DWORD		i_ncPasswordTimeOutInMinutes,
	_SetPassword*		i_pSetPasswordFunction,
	void*				i_pvoidPasswordFunctionData
)
{
	_VS_LONG			hResult			=	E_VS_FAIL;

//	DWORD				dwTemp;

//	_VS_CHAR			szMutexName [MAX_PATH];
//	_VS_BYTE*			pbyteMutexName;
//	_VS_DWORD			dwMutexNameLength;

	BOOL				boolCallEndWrite	=	FALSE;
	BOOL				boolCallEndRead		=	FALSE;

	while (1)
	{
		m_InitializeMembers ();

		m_dwMemoryOrFile =	PS_FILE;	//	set the flag to file (#define PS_FILE 1)

			//	check the input parameters
		VS_CHECK_INPUT_STRING			( i_cszApplicationName )
		VS_CHECK_INPUT_STRING_LEN		( i_cszApplicationName )

		VS_CHECK_INPUT_STRING			( i_cszApplicationHost )
		VS_CHECK_INPUT_STRING_LEN		( i_cszApplicationHost )
//		VS_CHECK_INPUT_STRING_LEN		( i_pcszApplicationHost )	//	Q: can this be blank string

		VS_CHECK_INPUT_STRING			( i_cszStorageFileName )
		VS_CHECK_INPUT_STRING_LEN		( i_cszStorageFileName )

//		VS_CHECK_INPUT_POINTER_FOR_NULL	( i_pSetPasswordFunction )	//	this can be NULL if the ap does not want to give a callback function

		if ( ( STORAGE_FILE_CREATE != i_ncCreateOpenFlag ) && ( STORAGE_FILE_OPEN != i_ncCreateOpenFlag ) )
		{
			hResult =	E_VS_INVALIDARG;
			break;
		}

		if ( (APPLICATION_ENCRYPTED != i_cnIsApplicationEncrypted) && (APPLICATION_DECRYPTED != i_cnIsApplicationEncrypted ) )
		{
			hResult =	E_VS_INVALIDARG;
			break;
		}

		m_dwIsApplicationEncrypted =	i_cnIsApplicationEncrypted;

			//	set the Initialize called flag
		m_dwInitializeCalled	=	1;

			//	create the heap memory
		hResult =	m_VS_HeapCreate ();
		VS_CHECK_HRESULT

		if ( NULL != i_cszPassword )
		{
//			VS_ALLOC_AND_STRING_COPY (m_szPassword, i_cszPassword)

			time ( &m_longTimePasswordProvided );	//	get the time when the password was set

				//	hash the password
			hResult =	m_HashData
						(
							(const _VS_BYTE*) i_cszPassword,
							(const _VS_DWORD) (_VS_strlenW (i_cszPassword) + 1) * sizeof (_VS_CHAR),
							&m_pbytePasswordHash,
							&m_dwPasswordHashLen
						);
			VS_CHECK_HRESULT

			/***************************************************
				TBD	-	destroy the password string. always
						store password in form of its hash.
						in this case there is no need for the
						member m_szPassword. remove it.
			***************************************************/


/*			if ( 0 == m_dwPasswordTimeOutIntervalInSeconds )
			{
				m_dwPasswordTimeOutAfterOneFunction =	1;
			}*/

			m_nPasswordProvided =	1;	//	set this flag to indicate that the password is set
		}
		else
		{
			if ( APPLICATION_ENCRYPTED == i_cnIsApplicationEncrypted )
			{
				hResult =	E_VS_BAD_PASSWORD;
				break;
			}
		}

				//	copy all the parameters in private members
		VS_ALLOC_AND_STRING_COPY (m_szStorageFileName, i_cszStorageFileName)
		VS_ALLOC_AND_STRING_COPY (m_szApplicationName, i_cszApplicationName)
		VS_ALLOC_AND_STRING_COPY (m_szApplicationHost, i_cszApplicationHost)

		m_nCreateOpenFlag =	i_ncCreateOpenFlag;

			//	copy the callback function pointer and the password timeout (in seconds) in the private members
		m_pSetPasswordFunctionPointer	=	i_pSetPasswordFunction;
		m_pvoidPasswordFunctionData		=	i_pvoidPasswordFunctionData;
		m_dwPasswordTimeOutIntervalInSeconds =	i_ncPasswordTimeOutInMinutes * 60;

#if PLATFORM==VSPS_WIN32

					//	create the concurrency objects required for simultaneous access.
					//	this function will basically create the write mutex, the read mutex and 
					//	the read semaphore
		hResult =	m_CreateConcurrencyObjects ();
		VS_CHECK_HRESULT

#endif
		if ( STORAGE_FILE_CREATE == m_nCreateOpenFlag )
		{
				//	This function will create a protected storage and fill it with all the
				//	default data.
			hResult =	m_CreateProtectedStorage ();
			VS_CHECK_HRESULT

			m_dwPSChangedAfterInitialized =	PS_CHANGED_AFTER_INITIALIZED;
		}	//	end		if ( STORAGE_FILE_CREATE == m_nCreateOpenFlag )


				//	This function will read the protected storage (file), decrypt it, decode it and
				//	fill all the data into the member data structures
		hResult =	m_ReadDataIntoStructures ( UPDATE_ALL_IF_POSSIBLE );
		VS_CHECK_HRESULT


			//	set the Initialize successful flag
		m_dwInitializeSuccessful	=	1;

/*
		hResult =	BeginRead (1, 1);
		boolCallEndRead =	TRUE;	//	turn the end read flag
		VS_CHECK_HRESULT

					//	check if the application
		hResult =	m_CheckIfApplicationExists ();

		if ( VS_SUCCESS != hResult )
		{
			if ( E_VS_INVALID_APP == hResult )
			{
					//	this means that the application does not exist

				if ( i_ncAddApplicationIfItDoesNotExist )
				{
						//	the client has requested to add the application

						//	this flag is turned ON so that the AddApplication function does not return
						//	an error
					m_dwInitializeSuccessful =	1;

					hResult =	UpgradeReadToWrite  ();
					VS_CHECK_HRESULT

					boolCallEndWrite	=	TRUE;	//	turn the end write flag
					boolCallEndRead		=	FALSE;	//	turn off the end read flag after upgrading

								//	this function will add the application
					hResult =	AddApplicationToDB
								(
									m_szApplicationName,
									m_szApplicationHost,
									m_dwIsApplicationEncrypted
								);
					if ( VS_SUCCESS != hResult )
					{
							//	if this function fails then it means that the initialization is
							//	not successful. so turn the flag OFF.
						m_dwInitializeSuccessful =	0;
						break;
					}

//					hResult =	EndWrite ();
//					VS_CHECK_HRESULT
				}
				else
				{
//					hResult =	EndRead ();
//					VS_CHECK_HRESULT

						//	the client has not requested to add the application.
						//	so return the error (E_VS_INVALID_APP)
					break;
				}
			}
			else
			{
					//	the m_CheckIfApplicationExists function failed due to
					//	some other reason.
				break;
			}
		}	//	end		if ( VS_SUCCESS != hResult )
		else
		{
//			hResult =	EndRead ();
//			VS_CHECK_HRESULT
		}
*/
					//	free the data structures
//		hResult =	m_FreeDataStructures ();
//		VS_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEndRead )
	{
		EndRead ();
	}

	if ( TRUE == boolCallEndWrite )
	{
		EndWrite ();
	}

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::Initialize 


_VS_LONG	CProtectedStorage::InitializeForRoaming
(
	const _VS_CHAR*		i_cszApplicationName,
	const _VS_CHAR*		i_cszApplicationHost,
	const _VS_DWORD		i_cnIsApplicationEncrypted,
	const int			i_ncAddApplicationIfItDoesNotExist,
	const _VS_CHAR*		i_cszStorageName,
//	const _VS_BYTE*		i_cpbyteStorage,
//	const _VS_DWORD		i_cdwStorageLen,
	_VS_BYTE**			i_ppbyteStorage,	//	this should be io_ppbyteStorage
	_VS_DWORD*			i_pdwStorageLen,
	const _VS_CHAR*		i_cszPassword,
	const _VS_DWORD		i_ncPasswordTimeOutInMinutes,
	_SetPassword*		i_pSetPasswordFunction,
	void*				i_pvoidPasswordFunctionData,
	const BOOL			i_boolUseFixedKey
)
{
	_VS_LONG			hResult			=	E_VS_FAIL;

	BOOL				boolCallEndWrite	=	FALSE;
	BOOL				boolCallEndRead		=	FALSE;

	while (1)
	{
		m_InitializeMembers ();

		m_dwMemoryOrFile =	PS_MEMORY;		//	set the flag to memory (#define PS_MEMORY 2)

		m_boolUseFixedKey = i_boolUseFixedKey;

			//	check the input parameters
		VS_CHECK_INPUT_STRING			( i_cszApplicationName )
		VS_CHECK_INPUT_STRING_LEN		( i_cszApplicationName )

		VS_CHECK_INPUT_STRING			( i_cszStorageName )
		VS_CHECK_INPUT_STRING_LEN		( i_cszStorageName )

		VS_CHECK_INPUT_STRING			( i_cszApplicationHost )
		VS_CHECK_INPUT_STRING_LEN		( i_cszApplicationHost )
//		VS_CHECK_INPUT_STRING_LEN		( i_pcszApplicationHost )	//	Q: can this be blank string
//		VS_CHECK_INPUT_POINTER_FOR_NULL	( i_pSetPasswordFunction )	//	this can be NULL if the ap does not want to give a callback function

		if ( (APPLICATION_ENCRYPTED != i_cnIsApplicationEncrypted) && (APPLICATION_DECRYPTED != i_cnIsApplicationEncrypted ) )
		{
			hResult =	E_VS_INVALIDARG;
			break;
		}

		m_dwIsApplicationEncrypted =	i_cnIsApplicationEncrypted;

			//	set the Initialize called flag
		m_dwInitializeCalled	=	1;

			//	create the heap memory
		hResult =	m_VS_HeapCreate ();
		VS_CHECK_HRESULT

		if ( NULL != i_cszPassword )
		{
//			VS_ALLOC_AND_STRING_COPY (m_szPassword, i_cszPassword)

			time ( &m_longTimePasswordProvided );	//	get the time when the password was set

				//	hash the password
			hResult =	m_HashData
						(
							(const _VS_BYTE*) i_cszPassword,
							(const _VS_DWORD) (_VS_strlenW (i_cszPassword) + 1) * sizeof (_VS_CHAR),
							&m_pbytePasswordHash,
							&m_dwPasswordHashLen
						);
			VS_CHECK_HRESULT

			/***************************************************
				TBD	-	destroy the password string. always
						store password in form of its hash.
						in this case there is no need for the
						member m_szPassword. remove it.
			***************************************************/


/*			if ( 0 == m_dwPasswordTimeOutIntervalInSeconds )
			{
				m_dwPasswordTimeOutAfterOneFunction =	1;
			}*/

			m_nPasswordProvided =	1;	//	set this flag to indicate that the password is set
		}
		else
		{
			if ( APPLICATION_ENCRYPTED == i_cnIsApplicationEncrypted )
			{
				hResult =	E_VS_BAD_PASSWORD;
				break;
			}
		}

				//	copy all the parameters in private members
		VS_ALLOC_AND_STRING_COPY (m_szApplicationName, i_cszApplicationName)
		VS_ALLOC_AND_STRING_COPY (m_szApplicationHost, i_cszApplicationHost)
		VS_ALLOC_AND_STRING_COPY (m_szRoamingStorageName, i_cszStorageName)
		if ( NULL == (*i_ppbyteStorage) )
		{
				//	this means that the storage does not exist and needs to be created
			m_nCreateOpenFlag =	STORAGE_FILE_CREATE;	//	though we are dealing with memory and not with
														//	files teh same flags are used

		}
		else
		{
				//	the storage exists and is passed as a byte blob
			m_nCreateOpenFlag =	STORAGE_FILE_OPEN;

//			m_dwRoamingBufferLen =	i_cdwStorageLen;
//			VS_ALLOC_AND_BYTEBLOB_COPY (m_pbyteRoamingBuffer, *i_ppbyteStorage, m_dwRoamingBufferLen)
		}

			//	the member variables should point to the appropriate memory locations (passed as in params)
			//	in either (open/create) case.

				//	copy the storage to member varialbes
		(m_pdwRoamingBufferLen) =	(i_pdwStorageLen);
		m_ppbyteRoamingBuffer =	i_ppbyteStorage;


			//	copy the callback function pointer and the password timeout (in seconds) in the private members
		m_pSetPasswordFunctionPointer	=	i_pSetPasswordFunction;
		m_pvoidPasswordFunctionData		=	i_pvoidPasswordFunctionData;
		m_dwPasswordTimeOutIntervalInSeconds =	i_ncPasswordTimeOutInMinutes * 60;

#if PLATFORM==VSPS_WIN32

					//	create the concurrency objects required for simultaneous access.
					//	this function will basically create the write mutex, the read mutex and 
					//	the read semaphore
		hResult =	m_CreateConcurrencyObjects ();
		VS_CHECK_HRESULT

#endif
		if ( STORAGE_FILE_CREATE == m_nCreateOpenFlag )
		{
				//	This function will create a protected storage and fill it with all the
				//	default data.
			hResult =	m_CreateProtectedStorage ();
			VS_CHECK_HRESULT

			m_dwRoamingBufferChanged	=	1;
			m_dwPSChangedAfterInitialized =	PS_CHANGED_AFTER_INITIALIZED;

		}	//	end		if ( STORAGE_FILE_CREATE == m_nCreateOpenFlag )
		else
		{
			m_dwRoamingBufferChanged	=	0;
		}

/*
				//	This function will read the protected storage (file), decrypt it, decode it and
				//	fill all the data into the member data structures
		hResult =	m_ReadDataIntoStructures ();
		VS_CHECK_HRESULT
*/

			//	set the Initialize successful flag
		m_dwInitializeSuccessful	=	1;

/*
		hResult =	BeginRead (1, 1);
		boolCallEndRead =	TRUE;	//	turn the end read flag
		VS_CHECK_HRESULT

					//	check if the application
		hResult =	m_CheckIfApplicationExists ();

		if ( VS_SUCCESS != hResult )
		{
			if ( E_VS_INVALID_APP == hResult )
			{
					//	this means that the application does not exist

				if ( i_ncAddApplicationIfItDoesNotExist )
				{
						//	the client has requested to add the application

						//	this flag is turned ON so that the AddApplication function does not return
						//	an error
					m_dwInitializeSuccessful =	1;

					hResult =	UpgradeReadToWrite  ();
					VS_CHECK_HRESULT

					boolCallEndWrite	=	TRUE;	//	turn the end write flag
					boolCallEndRead		=	FALSE;	//	turn off the end read flag after upgrading

								//	this function will add the application
					hResult =	AddApplicationToDB
								(
									m_szApplicationName,
									m_szApplicationHost,
									m_dwIsApplicationEncrypted
								);
					if ( VS_SUCCESS != hResult )
					{
							//	if this function fails then it means that the initialization is
							//	not successful. so turn the flag OFF.
						m_dwInitializeSuccessful =	0;
						break;
					}

//					hResult =	EndWrite ();
//					VS_CHECK_HRESULT
				}
				else
				{
//					hResult =	EndRead ();
//					VS_CHECK_HRESULT

						//	the client has not requested to add the application.
						//	so return the error (E_VS_INVALID_APP)
					break;
				}
			}
			else
			{
					//	the m_CheckIfApplicationExists function failed due to
					//	some other reason.
				break;
			}
		}	//	end		if ( VS_SUCCESS != hResult )
		else
		{
//			hResult =	EndRead ();
//			VS_CHECK_HRESULT
		}
*/

			//	free the data structures
//		hResult =	m_FreeDataStructures ();
//		VS_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolCallEndRead )
	{
		EndRead ();
	}

	if ( TRUE == boolCallEndWrite )
	{
		EndWrite ();
	}

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::InitializeForRoaming

_VS_LONG	CProtectedStorage::ChangeApplicationContext
(
	const _VS_CHAR* i_cszApplicationName,
	const _VS_CHAR* i_cszApplicationHost, 
	const _VS_DWORD i_cnIsApplicationEncrypted
)
{
	HRESULT		hResult		=		S_OK;

	while (1)
	{

		VS_FREE_MEMORY (m_szApplicationName)
		VS_FREE_MEMORY (m_szApplicationHost)
		VS_ALLOC_AND_STRING_COPY(m_szApplicationName, i_cszApplicationName)
		VS_ALLOC_AND_STRING_COPY(m_szApplicationHost, i_cszApplicationHost)
		m_dwIsApplicationEncrypted = i_cnIsApplicationEncrypted;

		break;
	}
	return hResult;
}

_VS_LONG	CProtectedStorage::Close ()
{
	_VS_LONG			hResult					=	E_VS_FAIL;

	while (1)
	{
		if ( 1 != m_dwInitializeCalled )
		{
			hResult =	E_VS_INITIALIZE_NOT_CALLED;
			break;
		}
		if ( PS_FILE != m_dwMemoryOrFile )
		{
			hResult =	E_VS_INITIALIZE_NOT_CALLED;
			break;
		}

					//	this function will update the storage file if necessary. it will also free all
					//	the data structures if the file is updated.
		hResult =	m_UpdateStorageFileIfNecessary ();
		VS_CHECK_HRESULT

		if ( 0 == m_dwDontDestroyMembers )
		{
			m_DestroyMembers ();
		}
		else
		{
			m_dwDontDestroyMembers = 0;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::Close ()


_VS_LONG	CProtectedStorage::CloseForRoaming
(
//	_VS_BYTE*			o_pbyteStorage,
//	_VS_DWORD*			o_pdwStorageLen,
	_VS_DWORD*			o_pdwChangedFlag
)
{
	_VS_LONG			hResult					=	E_VS_FAIL;

	while (1)
	{
		if ( 1 != m_dwInitializeCalled )
		{
			hResult =	E_VS_INITIALIZE_NOT_CALLED;
			break;
		}
		if ( PS_MEMORY != m_dwMemoryOrFile )
		{
			hResult =	E_VS_INITIALIZE_NOT_CALLED;
			break;
		}

					//	this function will update the storage file if necessary. it will also free all
					//	the data structures if the file is updated.
		hResult =	m_UpdateStorageFileIfNecessary ();
		VS_CHECK_HRESULT

/*
		if ( NULL == o_pbyteStorage )
		{
			*o_pdwChangedFlag =	m_dwRoamingBufferChanged;
			*o_pdwStorageLen =	m_dwRoamingBufferLen;

			hResult =	VS_SUCCESS;
			break;
		}

		if ( *o_pdwStorageLen < m_dwRoamingBufferLen )
		{
			*o_pdwChangedFlag =	m_dwRoamingBufferChanged;
			*o_pdwStorageLen =	m_dwRoamingBufferLen;
			
			hResult =	E_VS_MORE_DATA;
			break;
		}

		*o_pdwStorageLen =	m_dwRoamingBufferLen;
		*o_pdwChangedFlag =	m_dwRoamingBufferChanged;
		_VS_memcpy
		(
			o_pbyteStorage,
			m_pbyteRoamingBuffer,
			*o_pdwStorageLen
		);
*/
		
		*o_pdwChangedFlag =	m_dwRoamingBufferChanged;

		if ( 0 == m_dwDontDestroyMembers )
		{
			m_DestroyMembers ();
		}
		else
		{
			m_dwDontDestroyMembers = 0;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::CloseForRoaming



_VS_LONG	CProtectedStorage::ProvidePassword
(
	const _VS_CHAR*		i_cszPassword
)
{
	_VS_LONG			hResult					=	E_VS_FAIL;

	while (1)
	{
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

		VS_CHECK_INPUT_STRING			( i_cszPassword )
		VS_CHECK_INPUT_STRING_LEN		( i_cszPassword )

//		VS_ALLOC_AND_STRING_COPY (m_szPassword, i_cszPassword)

			//	hash the password
		hResult =	m_HashData
					(
						(const _VS_BYTE*) i_cszPassword,
						(const _VS_DWORD) (_VS_strlenW (i_cszPassword) + 1) * sizeof (_VS_CHAR),
						&m_pbytePasswordHash,
						&m_dwPasswordHashLen
					);
		VS_CHECK_HRESULT


			//	the function will update the data structures if necessary
		hResult =	m_UpdateDataStructuresIfNecessary ( UPDATE_ONLY_PROTECTED );
		VS_CHECK_HRESULT

		time ( &m_longTimePasswordProvided );	//	get the time when the password was set

		m_nPasswordProvided =	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;

}	//	end		_VS_LONG	CProtectedStorage::ProvidePassword


_VS_LONG	CProtectedStorage::AddCertificateToDB
(
	const _VS_BYTE*		i_pcbyteCertificateBlob,
	const _VS_DWORD		i_ncCertificateBlobLength,
	_VS_DWORD*			o_pnPointerToCertificate
)
{
	_VS_LONG			hResult			=	E_VS_FAIL;

	VSPS_CertificateInformation*		pstructCertificates		=	NULL;

	int					i;

	int					nCertCompare	=	999;
	int					nCertExists		=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check the input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteCertificateBlob)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncCertificateBlobLength)

			//	check if the certificate already exists
	
		for ( i = 0; i < (int) m_dwNumberOfCertificates; i++ )
		{
			if( i_ncCertificateBlobLength == m_pstructCertificateInformation[i].dwCertificateBlobLength )
				nCertCompare =	::_VS_memcmp ( i_pcbyteCertificateBlob, m_pstructCertificateInformation[i].pbyteCertificateBlob, m_pstructCertificateInformation[i].dwCertificateBlobLength );

			if ( 0 == nCertCompare )
			{
					//	turn on the cert exists flag
				nCertExists =	1;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfCertificates; i++ )

		if ( 1 == nCertExists )
		{
				//	this means that the certificate already exists. so return this error
			hResult =	E_VS_CERT_ALREADY_EXISTS;
			break;
		}

			//	allocate memory for new structure array with one more element
		pstructCertificates =	(VSPS_CertificateInformation*) m_VS_HeapAlloc
								(
									(m_dwNumberOfCertificates + 1) * sizeof (VSPS_CertificateInformation)
								);
		VS_CHECK_ALLOCATED_MEMORY(pstructCertificates)

			//	copy all existing elements into the new array
		for ( i = 0; i < (int) m_dwNumberOfCertificates; i++ )
		{
			pstructCertificates[i].pbyteCertificateBlob					=	m_pstructCertificateInformation[i].pbyteCertificateBlob;
			pstructCertificates[i].dwCertificateBlobLength				=	m_pstructCertificateInformation[i].dwCertificateBlobLength;
			pstructCertificates[i].dwNumberOfCertificatePreferences		=	m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences;
			pstructCertificates[i].ppbyteCertificatePreferenceName		=	m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName;
			pstructCertificates[i].pdwCertificatePreferenceNameLength	=	m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength;
			pstructCertificates[i].ppbyteCertificatePreferenceData		=	m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData;
			pstructCertificates[i].pdwCertificatePreferenceDataLength	=	m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength;
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfCertificates; i++ )
		
/*		if ( i < (int) m_dwNumberOfCertificates )
		{
			//	this means that the for loop was broken
			//	so free the pstructCertificates, break again and quit
			break;
		}*/

			//	allocate memory for the byte blob (Certificate) and copy it
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructCertificates[i].pbyteCertificateBlob, i_pcbyteCertificateBlob, i_ncCertificateBlobLength)

			//	fill other structure values. The preferences are not set at this point so
			//	set the pointers to NULL and counts to 0
		pstructCertificates[i].dwCertificateBlobLength				=	i_ncCertificateBlobLength;
		pstructCertificates[i].dwNumberOfCertificatePreferences		=	0;
		pstructCertificates[i].ppbyteCertificatePreferenceName		=	NULL;
		pstructCertificates[i].pdwCertificatePreferenceNameLength	=	NULL;
		pstructCertificates[i].ppbyteCertificatePreferenceData		=	NULL;
		pstructCertificates[i].pdwCertificatePreferenceDataLength	=	NULL;

			//	free memory for the private structure array
		VS_FREE_MEMORY( m_pstructCertificateInformation )

			//	the member pointer to array of structure now points to the new data
		m_pstructCertificateInformation =	pstructCertificates;

			//	copy the pointer (actual value) to the certificate in the DWORD and pass it back
		*o_pnPointerToCertificate =	(_VS_DWORD) m_pstructCertificateInformation[i].pbyteCertificateBlob;

			//	increase the count of the certificates
		m_dwNumberOfCertificates ++;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwPlainTextInformationChanged		=	1;
		m_dwCertificateInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}//	end		_VS_LONG	CProtectedStorage::AddCertificateToDB



_VS_LONG	CProtectedStorage::GetCertificateFromDB
(
	const _VS_DWORD		i_ncCertificateIndex,
	_VS_BYTE**			o_ppbyteCertificateBlob,
	_VS_DWORD*			o_pnCertificateBlobLength,
	_VS_DWORD*			o_pnPointerToCertificate
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_ppbyteCertificateBlob)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnCertificateBlobLength)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnPointerToCertificate)

		if ( (i_ncCertificateIndex < 0) || (i_ncCertificateIndex >= m_dwNumberOfCertificates) )
		{
			hResult =	E_VS_CERT_OUT_OF_RANGE;
			break;
		}

			//	copy the certificate blob in the out variable
		VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteCertificateBlob, m_pstructCertificateInformation[i_ncCertificateIndex].pbyteCertificateBlob, m_pstructCertificateInformation[i_ncCertificateIndex].dwCertificateBlobLength)

			//	copy the certificate blob length in the out variable
		*o_pnCertificateBlobLength =	m_pstructCertificateInformation[i_ncCertificateIndex].dwCertificateBlobLength;

			//	copy the pointer (actual value) to the certificate in the DWORD and pass it back
		*o_pnPointerToCertificate =	(_VS_DWORD) m_pstructCertificateInformation[i_ncCertificateIndex].pbyteCertificateBlob;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetCertificateFromDB


_VS_LONG	CProtectedStorage::RemoveCertificateFromDB
(
	const _VS_DWORD		i_cnPointerToCertificate
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	VSPS_CertificateInformation*		pstructCertificates		=	NULL;

	_VS_DWORD				nCertificateIndex;

	int						i, j;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	This function will accept the certificate pointer and return the index in nCertificateIndex
		hResult =	m_GetCertificateIndexFromPointerToCertificate
					(
						i_cnPointerToCertificate,
						&nCertificateIndex
					);
		VS_CHECK_HRESULT

			//	allocate memory for new structure array with one less element
		pstructCertificates =	(VSPS_CertificateInformation*) m_VS_HeapAlloc
								(
									(m_dwNumberOfCertificates - 1) * sizeof (VSPS_CertificateInformation)
								);
		VS_CHECK_ALLOCATED_MEMORY(pstructCertificates)

			//	copy all existing elements into the new array
		for ( i = 0, j = 0; i < (int) m_dwNumberOfCertificates; i++ )
		{
			if ( i != (int) nCertificateIndex )
			{
					//	this is not the certificate to be deleted. so copy the certificate blob and 
					//	preferences etc. into the new structures
				pstructCertificates[j].pbyteCertificateBlob					=	m_pstructCertificateInformation[i].pbyteCertificateBlob;
				pstructCertificates[j].dwCertificateBlobLength				=	m_pstructCertificateInformation[i].dwCertificateBlobLength;
				pstructCertificates[j].dwNumberOfCertificatePreferences		=	m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences;
				pstructCertificates[j].ppbyteCertificatePreferenceName		=	m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName;
				pstructCertificates[j].pdwCertificatePreferenceNameLength	=	m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength;
				pstructCertificates[j].ppbyteCertificatePreferenceData		=	m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData;
				pstructCertificates[j].pdwCertificatePreferenceDataLength	=	m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength;

				j++;
			}
			else
			{
					//	this is the certificate to be deleted.
					//	so free all the memory allocated for this certificate and its preference
				VS_FREE_MEMORY(m_pstructCertificateInformation[i].pbyteCertificateBlob)
				VS_FREE_MEMORY_2D(m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName, m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences)
				VS_FREE_MEMORY(m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength)
				VS_FREE_MEMORY_2D(m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData, m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences)
				VS_FREE_MEMORY(m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength)

					//	reset the blob lenght and number of preferences to zero
				m_pstructCertificateInformation[i].dwCertificateBlobLength				=	0;
				m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences		=	0;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfCertificates; i++ )
		
			//	free memory for the private structure array
		VS_FREE_MEMORY(m_pstructCertificateInformation);

			//	the member pointer to array of structure now points to the new data
		m_pstructCertificateInformation =	pstructCertificates;

			//	decrease the count of the certificates
		m_dwNumberOfCertificates --;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwPlainTextInformationChanged		=	1;
		m_dwCertificateInformationChanged	=	1;
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::RemoveCertificateFromDB


_VS_LONG	CProtectedStorage::SetCertificatePreference
(
	const _VS_DWORD		i_cnPointerToCertificate,
	const _VS_CHAR*		i_cszPreferenceName,
	const _VS_BYTE*		i_pcbyteCertificatePreferencesBlob,
	const _VS_DWORD		i_ncCertificatePreferencesBlobLength
)
{
	_VS_LONG				hResult						=	E_VS_FAIL;

	_VS_DWORD				dwNewNumberOfPreferences	=	0;

	_BYTE**					ppbytePreferenceName		=	NULL;
	_BYTE**					ppbytePreferenceData		=	NULL;
	_DWORD*					pdwPreferenceNameLength		=	NULL;
	_DWORD*					pdwPreferenceDataLength		=	NULL;

	int						i;

	int						nPrefCompare				=	999;
	int						nPrefExists					=	0;

	_VS_DWORD				nCertificateIndex			=	9999;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_STRING(i_cszPreferenceName)
		VS_CHECK_INPUT_STRING_LEN(i_cszPreferenceName)

		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteCertificatePreferencesBlob)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncCertificatePreferencesBlobLength)

			//	This function will accept the certificate pointer and return the index in nCertificateIndex
		hResult =	m_GetCertificateIndexFromPointerToCertificate
					(
						i_cnPointerToCertificate,
						&nCertificateIndex
					);
		VS_CHECK_HRESULT

			//	check if the preference already exists in which case only the data will be modified
		for ( i = 0; i < (int) m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; i ++ )
		{
			if(_VS_strlenW(i_cszPreferenceName) != _VS_strlenW((_VS_CHAR*)m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i]))
			{
				nPrefCompare = -1;
			}
			else
			{
				nPrefCompare =	::_VS_memcmp ( (_BYTE*) i_cszPreferenceName,  m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i], (_VS_strlenW(i_cszPreferenceName) + 1 ) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nPrefCompare )
			{
				VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[i])

				VS_ALLOC_AND_BYTEBLOB_COPY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[i], i_pcbyteCertificatePreferencesBlob, i_ncCertificatePreferencesBlobLength)

				m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[i] =	i_ncCertificatePreferencesBlobLength;
				
				nPrefExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; i ++ )

		if ( 1 != nPrefExists )
		{
			//	this means that the preference does not exist. so its a new preference

				//	new number of preferences = old number of preferences + 1
			dwNewNumberOfPreferences =	m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences + 1;

							//	allocate memory for the preference name array and the preference data array
					//	allocate memory for the first dimension of the preference name array
			ppbytePreferenceName =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY(ppbytePreferenceName)

					//	allocate memory for the first dimension of the preference data array
			ppbytePreferenceData =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY (ppbytePreferenceData)

						//	allocate memory for the preference name length array
			pdwPreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceNameLength)

						//	allocate memory for the preference data length array
			pdwPreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceDataLength)

			for ( i = 0; i < (int) dwNewNumberOfPreferences - 1; i ++ )
			{
					//	copy all the old preference (name, data and lengths) from existing structures into new structures
//				VS_ALLOC_AND_COPY_PRINTABLE_STRING(pszPreferenceName[i], m_pstructCertificateInformation[nCertificateIndex].pszCertificatePreferenceName[i])
				ppbytePreferenceName[i] =	m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i];
//				VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceData[i], m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[i], m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[i])
				ppbytePreferenceData[i] =	m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[i];
				pdwPreferenceNameLength[i] =	m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength[i];
				pdwPreferenceDataLength[i] =	m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[i];
			}	//	end		for ( i = 0; i < dwNewNumberOfPreferences - 1; i ++ )

				//	add the new preference along with the data and the lengths
			VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceName[i], (_BYTE*) i_cszPreferenceName, (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) )
			VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceData[i], i_pcbyteCertificatePreferencesBlob, i_ncCertificatePreferencesBlobLength)
			pdwPreferenceNameLength[i] =	(_VS_strlenW ( i_cszPreferenceName ) + 1) * sizeof (_VS_CHAR);
			pdwPreferenceDataLength[i] =	i_ncCertificatePreferencesBlobLength;

				//	free memory pointed by the old pointers
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName)
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData)
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength)
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength)

				//	make the pointers point to the allocated and filled (with the new pref) memory
			m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName		=	ppbytePreferenceName;
			m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData		=	ppbytePreferenceData;
			m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength	=	pdwPreferenceNameLength;
			m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength	=	pdwPreferenceDataLength;

				//	increase the number of preferences
			m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences ++;

		}	//	end		if ( 1 != nPrefExists )

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwPlainTextInformationChanged		=	1;
		m_dwCertificateInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::SetCertificatePreference


_VS_LONG	CProtectedStorage::GetCertificatePreference
(
	const _VS_DWORD		i_cnPointerToCertificate,
	const _VS_CHAR*		i_cszPreferenceName,
	_VS_BYTE**			o_ppbyteCertificatePreferencesBlob,
	_VS_DWORD*			o_pnCertificatePreferencesBlobLength
)
{
	_VS_LONG				hResult						=	E_VS_FAIL;

	int						i;

	int						nPrefCompare				=	999;
	int						nPrefExists					=	0;

	_VS_DWORD				nCertificateIndex			=	9999;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_STRING(i_cszPreferenceName)
		VS_CHECK_INPUT_STRING_LEN(i_cszPreferenceName)

		VS_CHECK_INPUT_POINTER_FOR_NULL(o_ppbyteCertificatePreferencesBlob)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnCertificatePreferencesBlobLength)

			//	This function will accept the certificate pointer and return the index in nCertificateIndex
		hResult =	m_GetCertificateIndexFromPointerToCertificate
					(
						i_cnPointerToCertificate,
						&nCertificateIndex
					);
		VS_CHECK_HRESULT

				//	for all preferences of the specified certificate
		for ( i = 0; i < (int) m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; i ++ )
		{
			if(_VS_strlenW(i_cszPreferenceName) != _VS_strlenW((_VS_CHAR*)m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i]))
			{
				nPrefCompare = -1;
			}
			else
			{
				nPrefCompare =	::_VS_memcmp ( (_BYTE*) i_cszPreferenceName, m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i], (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nPrefCompare )
			{
					//	thats the certificate preference
					//	copy the preference data and length into the appropriate parameters
				VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteCertificatePreferencesBlob, m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[i], m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[i])

				*o_pnCertificatePreferencesBlobLength =	m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[i];
				
				nPrefExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; i ++ )
		if ( (i < (int) m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences)\
				&& (1 != nPrefExists) )
		{
				//	this means that the for loop was broken due to some error. so break again.
			break;
		}

		if ( 1 != nPrefExists )
		{
				//	this means that the preference does not exist
			hResult =	E_VS_INVALID_CERT_PREF;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetCertificatePreference


_VS_LONG	CProtectedStorage::DeleteCertificatePreference
(
	const _VS_DWORD		i_cnPointerToCertificate,
	const _VS_CHAR*		i_cszPreferenceName
)
{
	_VS_LONG				hResult							=	E_VS_FAIL;

	int						i, j, k;

	_VS_DWORD				dwNewNumberOfPreferences		=	0;

	int						nPrefExists						=	0;
	int						nPrefCompare					=	999;

	_BYTE**					ppbytePreferenceName			=	NULL;
	_BYTE**					ppbytePreferenceData			=	NULL;
	_DWORD*					pdwPreferenceNameLength			=	NULL;
	_DWORD*					pdwPreferenceDataLength			=	NULL;

	_VS_DWORD				nCertificateIndex				=	9999;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_STRING(i_cszPreferenceName)
		VS_CHECK_INPUT_STRING_LEN(i_cszPreferenceName)

			//	This function will accept the certificate pointer and return the index in nCertificateIndex
		hResult =	m_GetCertificateIndexFromPointerToCertificate
					(
						i_cnPointerToCertificate,
						&nCertificateIndex
					);
		VS_CHECK_HRESULT

			//	check if the preference exists
		for ( i = 0; i < (int) m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; i ++ )
		{
			if(_VS_strlenW(i_cszPreferenceName) != _VS_strlenW((_VS_CHAR*)m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i]))
			{
				nPrefCompare = -1;
			}
			else
			{
				nPrefCompare =	::_VS_memcmp ( (_BYTE*) i_cszPreferenceName,  m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[i], (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nPrefCompare )
			{
				nPrefExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; i ++ )

		//
		//	IMPORTANT NOTE:	The value of i when the for loop breaks is the index of the preference to be deleted.
		//					this will be used later.
		//

		if ( 1 == nPrefExists )
		{
						//	this means that the preference exits. so delete it.

				//	new number of preferences = old number of preferences - 1
			dwNewNumberOfPreferences =	m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences - 1;

					//	allocate memory for the preference name array and the preference data array
					//	allocate memory for the first dimension of the preference name array
			ppbytePreferenceName =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY(ppbytePreferenceName)

					//	allocate memory for the first dimension of the preference data array
			ppbytePreferenceData =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY (ppbytePreferenceData)

						//	allocate memory for the preference name length array
			pdwPreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceNameLength)

						//	allocate memory for the preference data length array
			pdwPreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceDataLength)

			for ( j = 0, k = 0; j < (int) m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; j ++ )
			{
				if ( j != i )
				{
						//	this pref is not to be deleted.
						//	so copy all the old preference (name, data and lengths) from existing structures into new structures
//					VS_ALLOC_AND_COPY_PRINTABLE_STRING(pszPreferenceName[k], m_pstructCertificateInformation[nCertificateIndex].pszCertificatePreferenceName[j])
					ppbytePreferenceName[k] =	m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[j];
//					VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceData[k], m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[j], m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[j])
					ppbytePreferenceData[k] =	m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[j];
					pdwPreferenceNameLength[k] =	m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength[j];
					pdwPreferenceDataLength[k] =	m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[j];

					k ++;
				}	//	end		if ( j != i )
				else
				{
						//	this pref is to be deleted. so free the memory for the name and data of this preference
					VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName[j])
					VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData[j])

						//	and set lengths to zero
					m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength[j] =	0;
					m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength[j] =	0;
				}	//	end		else
			}	//	end		for ( j = 0; j < (int) m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences; j ++ )

						//	free memory pointed by the old pointers
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName)
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData)
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength)
			VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength)


				//	make the pointers point to the allocated and filled (with the new pref) memory
			m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName		=	ppbytePreferenceName;
			m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData		=	ppbytePreferenceData;
			m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength	=	pdwPreferenceNameLength;
			m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength	=	pdwPreferenceDataLength;

				//	decrease the number of preferences
			m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences --;

				//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
				//	at the end of the session
			m_dwPlainTextInformationChanged		=	1;
			m_dwCertificateInformationChanged	=	1;

		}	//	end		if ( 1 == nPrefExists )
		else
		{
			hResult =	E_VS_INVALID_CERT_PREF;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::DeleteCertificatePreference



_VS_LONG	CProtectedStorage::DeleteAllCertificatePreference
(
	const _VS_DWORD		i_cnPointerToCertificate
)
{
	_VS_LONG					hResult				=	E_VS_FAIL;

	_VS_DWORD					nCertificateIndex;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	This function will accept the certificate pointer and return the index in nCertificateIndex
		hResult =	m_GetCertificateIndexFromPointerToCertificate
					(
						i_cnPointerToCertificate,
						&nCertificateIndex
					);
		VS_CHECK_HRESULT

			//	free memory occupied by the certificate preference (name, data and lengths)
		VS_FREE_MEMORY_2D(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceName, m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences)
		VS_FREE_MEMORY_2D(m_pstructCertificateInformation[nCertificateIndex].ppbyteCertificatePreferenceData, m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences)
		VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceNameLength)
		VS_FREE_MEMORY(m_pstructCertificateInformation[nCertificateIndex].pdwCertificatePreferenceDataLength)
		
			//	reset the number of preferences to zero
		m_pstructCertificateInformation[nCertificateIndex].dwNumberOfCertificatePreferences =	0;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwPlainTextInformationChanged		=	1;
		m_dwCertificateInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::DeleteAllCertificatePreference


_VS_LONG	CProtectedStorage::AddApplicationToDB
(
	const _VS_CHAR*		i_cszApplicationName,
	const _VS_CHAR*		i_cszApplicationHost,
	const _VS_DWORD		i_cnIsApplicationEncrypted
)
{
	_VS_LONG					hResult					=	E_VS_FAIL;

	int					i;

	int					nAppNameCompare		=	999;
	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	VSPS_ApplicationInformation*			pstructNewApplications		=	NULL;
	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	BOOL				boolSuccessFlag		=	FALSE;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check the input parameters
		VS_CHECK_INPUT_STRING		( i_cszApplicationName )
		VS_CHECK_INPUT_STRING_LEN	( i_cszApplicationName )

		VS_CHECK_INPUT_STRING		( i_cszApplicationHost )
//		VS_CHECK_INPUT_STRING_LEN	( i_pcszApplicationHost )	//	Q: can this be blank string

			//	check the i_cnIsApplicationEncrypted value and assign the appropriate structure array
			//	(Plain Text or Protected) to the local pointer pstructCurrentApplications
		switch ( i_cnIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

				boolSuccessFlag	=	TRUE;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;

				boolSuccessFlag	=	TRUE;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( i_cnIsApplicationEncrypted )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	check if the application already exists
			//	for this compare the application name and application host
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (i_cszApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) i_cszApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (i_cszApplicationName) + 1) * sizeof (_VS_CHAR) );
			}

			if(_VS_strlenW (i_cszApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) i_cszApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (i_cszApplicationHost) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			{
					//	turn on the app exists flag
				nAppExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 1 == nAppExists )
		{
				//	the application already exists. so return this error
			hResult =	E_VS_APP_ALREADY_EXISTS;
			break;
		}

					//	allocate memory for new structure array with one more element
		pstructNewApplications =	(VSPS_ApplicationInformation*) m_VS_HeapAlloc
									(
										(dwNumberOfApplications + 1) * sizeof (VSPS_ApplicationInformation)
									);
		VS_CHECK_ALLOCATED_MEMORY(pstructNewApplications)

			//	copy all existing elements into the new array
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			pstructNewApplications[i].pbyteApplicationName					=	pstructCurrentApplications[i].pbyteApplicationName;
			pstructNewApplications[i].dwApplicationNameLength				=	pstructCurrentApplications[i].dwApplicationNameLength;
			pstructNewApplications[i].pbyteApplicationHost					=	pstructCurrentApplications[i].pbyteApplicationHost;
			pstructNewApplications[i].dwApplicationHostLength				=	pstructCurrentApplications[i].dwApplicationHostLength;
			pstructNewApplications[i].pbyteApplicationCreatorWildCard		=	pstructCurrentApplications[i].pbyteApplicationCreatorWildCard;
			pstructNewApplications[i].dwApplicationCreatorWildCardLength	=	pstructCurrentApplications[i].dwApplicationCreatorWildCardLength;
			pstructNewApplications[i].dwNumOfApplicationReadOKDomains		=	pstructCurrentApplications[i].dwNumOfApplicationReadOKDomains;
			pstructNewApplications[i].pbyteApplicationReadOKDomains			=	pstructCurrentApplications[i].pbyteApplicationReadOKDomains;
			pstructNewApplications[i].dwApplicationReadOKDomainsLength		=	pstructCurrentApplications[i].dwApplicationReadOKDomainsLength;
			pstructNewApplications[i].dwNumOfApplicationWriteOKDomains		=	pstructCurrentApplications[i].dwNumOfApplicationWriteOKDomains;
			pstructNewApplications[i].pbyteApplicationWriteOKDomains		=	pstructCurrentApplications[i].pbyteApplicationWriteOKDomains;
			pstructNewApplications[i].dwApplicationWriteOKDomainsLength		=	pstructCurrentApplications[i].dwApplicationWriteOKDomainsLength;
			pstructNewApplications[i].dwNumberOfApplicationPreferences		=	pstructCurrentApplications[i].dwNumberOfApplicationPreferences;
			pstructNewApplications[i].ppbyteApplicationPreferenceName		=	pstructCurrentApplications[i].ppbyteApplicationPreferenceName;
			pstructNewApplications[i].pdwApplicationPreferenceNameLength	=	pstructCurrentApplications[i].pdwApplicationPreferenceNameLength;
			pstructNewApplications[i].ppbyteApplicationPreferenceData		=	pstructCurrentApplications[i].ppbyteApplicationPreferenceData;
			pstructNewApplications[i].pdwApplicationPreferenceDataLength	=	pstructCurrentApplications[i].pdwApplicationPreferenceDataLength;
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

			//	allocate memory for the application name and copy it and the length
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructNewApplications[i].pbyteApplicationName, (_BYTE*) i_cszApplicationName, (_VS_strlenW (i_cszApplicationName) + 1) * sizeof (_VS_CHAR) )
		pstructNewApplications[i].dwApplicationNameLength = (_VS_strlenW(i_cszApplicationName) + 1) * sizeof (_VS_CHAR);

			//	allocate memory for the application host and copy it and the length
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructNewApplications[i].pbyteApplicationHost, (_BYTE*) i_cszApplicationHost, (_VS_strlenW (i_cszApplicationHost) + 1) * sizeof (_VS_CHAR) )
		pstructNewApplications[i].dwApplicationHostLength =	(_VS_strlenW(i_cszApplicationHost) + 1) * sizeof (_VS_CHAR);

			//	allocate memory for wildcard
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructNewApplications[i].pbyteApplicationCreatorWildCard, (_BYTE*) i_cszApplicationHost, (_VS_strlenW (i_cszApplicationHost) + 1) * sizeof (_VS_CHAR) )
		pstructNewApplications[i].dwApplicationCreatorWildCardLength =	(_VS_strlenW(i_cszApplicationHost) + 1) * sizeof (_VS_CHAR);

			//	fill other structure values. The preferences are not set at this point so
			//	set the pointers to NULL and counts to 0
		pstructNewApplications[i].dwNumberOfApplicationPreferences		=	0;
		pstructNewApplications[i].ppbyteApplicationPreferenceName		=	NULL;
		pstructNewApplications[i].pdwApplicationPreferenceNameLength	=	NULL;
		pstructNewApplications[i].ppbyteApplicationPreferenceData		=	NULL;
		pstructNewApplications[i].pdwApplicationPreferenceDataLength	=	NULL;

			//	free memory for the private structure array
		VS_FREE_MEMORY( pstructCurrentApplications )

		switch ( i_cnIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
					//	the member pointer to array of structure now points to the new data
				m_pstructProtectedApplicationInformation =	pstructNewApplications;

					//	increase the count of the protected applications
				m_dwNumberOfProtectedApplications ++;

					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwProtectedInformationChanged				=	1;
				m_dwProtectedApplicationInformationChanged	=	1;

				// giving readok + writeok for the creator itself.
				pstructNewApplications[i].dwNumOfApplicationReadOKDomains = 1;
				VS_ALLOC_AND_BYTEBLOB_COPY (pstructNewApplications[i].pbyteApplicationReadOKDomains, pstructNewApplications[i].pbyteApplicationHost, pstructNewApplications[i].dwApplicationHostLength)
				pstructNewApplications[i].dwApplicationReadOKDomainsLength = pstructNewApplications[i].dwApplicationHostLength;
				pstructNewApplications[i].dwNumOfApplicationWriteOKDomains = 1;
				VS_ALLOC_AND_BYTEBLOB_COPY (pstructNewApplications[i].pbyteApplicationWriteOKDomains, pstructNewApplications[i].pbyteApplicationHost, pstructNewApplications[i].dwApplicationHostLength)
				pstructNewApplications[i].dwApplicationWriteOKDomainsLength = pstructNewApplications[i].dwApplicationHostLength;

				break;

			case	APPLICATION_DECRYPTED:
					//	the member pointer to array of structure now points to the new data
				m_pstructPlainTextApplicationInformation =	pstructNewApplications;

					//	increase the count of the plain text applications
				m_dwNumberOfPlainTextApplications ++;

					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwPlainTextInformationChanged				=	1;
				m_dwPlainTextApplicationInformationChanged	=	1;

								// assign default values to readok + writeok. not used for plaintext.
				pstructNewApplications[i].dwNumOfApplicationReadOKDomains = 0;
				pstructNewApplications[i].pbyteApplicationReadOKDomains = NULL;
				pstructNewApplications[i].dwApplicationReadOKDomainsLength = 0;
				pstructNewApplications[i].dwNumOfApplicationWriteOKDomains = 0;
				pstructNewApplications[i].pbyteApplicationWriteOKDomains = NULL;
				pstructNewApplications[i].dwApplicationWriteOKDomainsLength = 0;

				break;

			default:
				break;
		}	//	end		switch ( i_cnIsApplicationEncrypted )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::AddApplicationToDB


_VS_LONG	CProtectedStorage::RemoveApplicationFromDB
(
	const _VS_CHAR*		i_cszApplicationName,
	const _VS_CHAR*		i_cszApplicationHost,
	const _VS_DWORD		i_cnIsApplicationEncrypted
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int					i, j;
	
	int					nAppNameCompare		=	999;
	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	VSPS_ApplicationInformation*			pstructNewApplications		=	NULL;
	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	BOOL				boolSuccessFlag		=	FALSE;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check the input parameters
		VS_CHECK_INPUT_STRING		( i_cszApplicationName )
		VS_CHECK_INPUT_STRING_LEN	( i_cszApplicationName )

		VS_CHECK_INPUT_STRING		( i_cszApplicationHost )
//		VS_CHECK_INPUT_STRING_LEN	( i_pcszApplicationHost )	//	Q: can this be blank string

			//	check the i_cnIsApplicationEncrypted value and assign the appropriate structure array
			//	(Plain Text or Protected) to the local pointer pstructCurrentApplications
		switch ( i_cnIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

				boolSuccessFlag	=	TRUE;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;

				boolSuccessFlag	=	TRUE;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( i_cnIsApplicationEncrypted )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	confirm that the application exists
			//	for this compare the application name and application host
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (i_cszApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{	
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) i_cszApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (i_cszApplicationName) + 1) * sizeof (_VS_CHAR) );
			}

			if(_VS_strlenW (i_cszApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) i_cszApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (i_cszApplicationHost) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			{
					//	turn on the app exists flag
				nAppExists =	1;

					//	this index will be used later while actually deleting the application information
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

			//	allocate memory for new structure array with one less element
		pstructNewApplications =	(VSPS_ApplicationInformation*) m_VS_HeapAlloc
									(
										(dwNumberOfApplications - 1) * sizeof (VSPS_ApplicationInformation)
									);
		VS_CHECK_ALLOCATED_MEMORY(pstructNewApplications)

			//	copy all existing elements into the new array
		for ( i = 0, j = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if ( i != nAppIndex )
			{
					//	this is not the application to be deleted. so copy the application name, host and 
					//	preferences etc. into the new structures
				pstructNewApplications[j].pbyteApplicationName					=	pstructCurrentApplications[i].pbyteApplicationName;
				pstructNewApplications[j].dwApplicationNameLength				=	pstructCurrentApplications[i].dwApplicationNameLength;
				pstructNewApplications[j].pbyteApplicationHost					=	pstructCurrentApplications[i].pbyteApplicationHost;
				pstructNewApplications[j].dwApplicationHostLength				=	pstructCurrentApplications[i].dwApplicationHostLength;
				pstructNewApplications[j].pbyteApplicationCreatorWildCard		=	pstructCurrentApplications[i].pbyteApplicationCreatorWildCard;
				pstructNewApplications[j].dwApplicationCreatorWildCardLength	=	pstructCurrentApplications[i].dwApplicationCreatorWildCardLength;
				pstructNewApplications[j].dwNumOfApplicationReadOKDomains		=	pstructCurrentApplications[i].dwNumOfApplicationReadOKDomains;
				pstructNewApplications[j].pbyteApplicationReadOKDomains			=	pstructCurrentApplications[i].pbyteApplicationReadOKDomains;
				pstructNewApplications[j].dwApplicationReadOKDomainsLength		=	pstructCurrentApplications[i].dwApplicationReadOKDomainsLength;
				pstructNewApplications[j].dwNumOfApplicationWriteOKDomains		=	pstructCurrentApplications[i].dwNumOfApplicationWriteOKDomains;
				pstructNewApplications[j].pbyteApplicationWriteOKDomains		=	pstructCurrentApplications[i].pbyteApplicationWriteOKDomains;
				pstructNewApplications[j].dwApplicationWriteOKDomainsLength		=	pstructCurrentApplications[i].dwApplicationWriteOKDomainsLength;
				pstructNewApplications[j].dwNumberOfApplicationPreferences		=	pstructCurrentApplications[i].dwNumberOfApplicationPreferences;
				pstructNewApplications[j].ppbyteApplicationPreferenceName		=	pstructCurrentApplications[i].ppbyteApplicationPreferenceName;
				pstructNewApplications[j].pdwApplicationPreferenceNameLength	=	pstructCurrentApplications[i].pdwApplicationPreferenceNameLength;
				pstructNewApplications[j].ppbyteApplicationPreferenceData		=	pstructCurrentApplications[i].ppbyteApplicationPreferenceData;
				pstructNewApplications[j].pdwApplicationPreferenceDataLength	=	pstructCurrentApplications[i].pdwApplicationPreferenceDataLength;

				j++;
			}
			else
			{
					//	this is the application to be deleted.
					//	so free all the memory allocated for this application and its preference
				VS_FREE_MEMORY(pstructCurrentApplications[i].pbyteApplicationName)
				VS_FREE_MEMORY(pstructCurrentApplications[i].pbyteApplicationHost)
				VS_FREE_MEMORY(pstructCurrentApplications[i].pbyteApplicationCreatorWildCard)
				VS_FREE_MEMORY(pstructCurrentApplications[i].pbyteApplicationReadOKDomains)
				VS_FREE_MEMORY(pstructCurrentApplications[i].pbyteApplicationWriteOKDomains)
				VS_FREE_MEMORY_2D(pstructCurrentApplications[i].ppbyteApplicationPreferenceName, pstructCurrentApplications[i].dwNumberOfApplicationPreferences)
				VS_FREE_MEMORY(pstructCurrentApplications[i].pdwApplicationPreferenceNameLength)
				VS_FREE_MEMORY_2D(pstructCurrentApplications[i].ppbyteApplicationPreferenceData, pstructCurrentApplications[i].dwNumberOfApplicationPreferences)
				VS_FREE_MEMORY(pstructCurrentApplications[i].pdwApplicationPreferenceDataLength)

					//	reset the name/host length and number of preferences to zero
				pstructCurrentApplications[i].dwApplicationNameLength				=	0;
				pstructCurrentApplications[i].dwApplicationHostLength				=	0;
				pstructCurrentApplications[i].dwApplicationCreatorWildCardLength	=	0;
				pstructCurrentApplications[i].dwNumOfApplicationReadOKDomains		=	0;
				pstructCurrentApplications[i].dwApplicationReadOKDomainsLength		=	0;
				pstructCurrentApplications[i].dwNumOfApplicationWriteOKDomains		=	0;
				pstructCurrentApplications[i].dwApplicationWriteOKDomainsLength		=	0;			
				pstructCurrentApplications[i].dwNumberOfApplicationPreferences		=	0;
			}
		}	//	end		for ( i = 0, j = 0; i < (int) dwNumberOfApplications; i++ )

			//	free memory for the private structure array
		VS_FREE_MEMORY( pstructCurrentApplications )

		switch ( i_cnIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
					//	the member pointer to array of structure now points to the new data
				m_pstructProtectedApplicationInformation =	pstructNewApplications;

					//	decrement the count of the protected applications
				m_dwNumberOfProtectedApplications --;

					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwProtectedInformationChanged				=	1;
				m_dwProtectedApplicationInformationChanged	=	1;

				break;

			case	APPLICATION_DECRYPTED:
					//	the member pointer to array of structure now points to the new data
				m_pstructPlainTextApplicationInformation =	pstructNewApplications;

					//	decrement the count of the plain text applications
				m_dwNumberOfPlainTextApplications --;

					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwPlainTextInformationChanged				=	1;
				m_dwPlainTextApplicationInformationChanged	=	1;

				break;

			default:
				break;
		}	//	end		switch ( i_cnIsApplicationEncrypted )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::RemoveApplicationFromDB


_VS_LONG	CProtectedStorage::GetApplicationCreator
(
	_VS_BYTE**	o_ppbyteApplicationHost
)
{

	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;


	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_ppbyteApplicationHost )

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;


			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if ( 0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}
		
		VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteApplicationHost, pstructCurrentApplications[nAppIndex].pbyteApplicationHost, pstructCurrentApplications[nAppIndex].dwApplicationHostLength)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;

}

_VS_LONG	CProtectedStorage::GetApplicationCreatorWildCard
(
	_VS_BYTE**	o_ppbyteApplicationCreatorWildCard
)
{

	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;


	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_ppbyteApplicationCreatorWildCard )

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;


			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if ( 0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}
		
		VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteApplicationCreatorWildCard, pstructCurrentApplications[nAppIndex].pbyteApplicationCreatorWildCard, pstructCurrentApplications[nAppIndex].dwApplicationCreatorWildCardLength)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
	
}

_VS_LONG	CProtectedStorage::SetApplicationCreatorWildCard
(
	const _VS_BYTE*		i_pcbyteApplicationCreatorWildCard,
	const _VS_DWORD		i_ncWildCardBlobLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteApplicationCreatorWildCard)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncWildCardBlobLength)

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{

			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if ( 0 == nAppNameCompare )
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

		VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pbyteApplicationCreatorWildCard)
		
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructCurrentApplications[nAppIndex].pbyteApplicationCreatorWildCard, i_pcbyteApplicationCreatorWildCard, i_ncWildCardBlobLength)

		pstructCurrentApplications[nAppIndex].dwApplicationCreatorWildCardLength = i_ncWildCardBlobLength;

		m_dwProtectedInformationChanged				=	1;
		m_dwProtectedApplicationInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}

_VS_LONG	CProtectedStorage::GetApplicationReadOKDomains
(
	_VS_DWORD*	o_pnNumOfApplicationReadOKDomains,
	_VS_BYTE**	o_ppbyteApplicationReadOKDomainsBlob,
	_VS_DWORD*	o_pnApplicationReadOKDomainsBlobLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;


	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_pnNumOfApplicationReadOKDomains )
		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_ppbyteApplicationReadOKDomainsBlob )
		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_pnApplicationReadOKDomainsBlobLength )

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;


			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if ( 0 == nAppNameCompare )
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

		if (pstructCurrentApplications[nAppIndex].dwNumOfApplicationReadOKDomains > 0)
		{
			*o_pnNumOfApplicationReadOKDomains = pstructCurrentApplications[nAppIndex].dwNumOfApplicationReadOKDomains;
			//	copy the readokdomains data and length into the appropriate parameters
			VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteApplicationReadOKDomainsBlob, pstructCurrentApplications[nAppIndex].pbyteApplicationReadOKDomains, pstructCurrentApplications[nAppIndex].dwApplicationReadOKDomainsLength)

			*o_pnApplicationReadOKDomainsBlobLength =	pstructCurrentApplications[nAppIndex].dwApplicationReadOKDomainsLength;
		}
		else
		{
			*o_pnNumOfApplicationReadOKDomains = 0;
			*o_ppbyteApplicationReadOKDomainsBlob = NULL;
			*o_pnApplicationReadOKDomainsBlobLength = 0;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;

}

_VS_LONG	CProtectedStorage::SetApplicationReadOKDomains
(
	const _VS_DWORD		i_ncNumOfApplicationReadOKDomains,
	const _VS_BYTE*		i_pcbyteApplicationReadOKDomainsBlob,
	const _VS_DWORD		i_ncApplicationReadOKDomainsBlobLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED


		if (i_ncNumOfApplicationReadOKDomains > 0)
		{
			VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteApplicationReadOKDomainsBlob)
			VS_CHECK_LENGTH_FOR_ZERO(i_ncApplicationReadOKDomainsBlobLength)
		}

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{

			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if ( 0 == nAppNameCompare )
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

		VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pbyteApplicationReadOKDomains)
		
		if (i_ncNumOfApplicationReadOKDomains > 0)
		{
			VS_ALLOC_AND_BYTEBLOB_COPY(pstructCurrentApplications[nAppIndex].pbyteApplicationReadOKDomains, i_pcbyteApplicationReadOKDomainsBlob, i_ncApplicationReadOKDomainsBlobLength)

			pstructCurrentApplications[nAppIndex].dwApplicationReadOKDomainsLength = i_ncApplicationReadOKDomainsBlobLength;
		}
		else
		{
			pstructCurrentApplications[nAppIndex].pbyteApplicationReadOKDomains = NULL;
			pstructCurrentApplications[nAppIndex].dwApplicationReadOKDomainsLength = 0;
		}
		pstructCurrentApplications[nAppIndex].dwNumOfApplicationReadOKDomains = i_ncNumOfApplicationReadOKDomains;
		m_dwProtectedInformationChanged				=	1;
		m_dwProtectedApplicationInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::SetApplicationReadOKDomains


_VS_LONG	CProtectedStorage::GetApplicationWriteOKDomains
(
	_VS_DWORD*	o_pnNumOfApplicationWriteOKDomains,
	_VS_BYTE**	o_ppbyteApplicationWriteOKDomainsBlob,
	_VS_DWORD*	o_pnApplicationWriteOKDomainsBlobLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;


	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_pnNumOfApplicationWriteOKDomains )
		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_ppbyteApplicationWriteOKDomainsBlob )
		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_pnApplicationWriteOKDomainsBlobLength )

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;


			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if (0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

		if (pstructCurrentApplications[nAppIndex].dwNumOfApplicationWriteOKDomains > 0)
		{
			*o_pnNumOfApplicationWriteOKDomains = pstructCurrentApplications[nAppIndex].dwNumOfApplicationWriteOKDomains;
			//	copy the Writeokdomains data and length into the appropriate parameters
			VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteApplicationWriteOKDomainsBlob, pstructCurrentApplications[nAppIndex].pbyteApplicationWriteOKDomains, pstructCurrentApplications[nAppIndex].dwApplicationWriteOKDomainsLength)

			*o_pnApplicationWriteOKDomainsBlobLength =	pstructCurrentApplications[nAppIndex].dwApplicationWriteOKDomainsLength;
		}
		else
		{
			*o_pnNumOfApplicationWriteOKDomains = 0;
			*o_ppbyteApplicationWriteOKDomainsBlob = NULL;
			*o_pnApplicationWriteOKDomainsBlobLength = 0;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;

}

_VS_LONG	CProtectedStorage::SetApplicationWriteOKDomains
(
	const _VS_DWORD		i_ncNumOfApplicationWriteOKDomains,
	const _VS_BYTE*		i_pcbyteApplicationWriteOKDomainsBlob,
	const _VS_DWORD		i_ncApplicationWriteOKDomainsBlobLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED


		if (i_ncNumOfApplicationWriteOKDomains > 0)
		{
			VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteApplicationWriteOKDomainsBlob)
			VS_CHECK_LENGTH_FOR_ZERO(i_ncApplicationWriteOKDomainsBlobLength)
		}

		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
		dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{

			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if (0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

		VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pbyteApplicationWriteOKDomains)
		
		if (i_ncNumOfApplicationWriteOKDomains > 0)
		{
			VS_ALLOC_AND_BYTEBLOB_COPY(pstructCurrentApplications[nAppIndex].pbyteApplicationWriteOKDomains, i_pcbyteApplicationWriteOKDomainsBlob, i_ncApplicationWriteOKDomainsBlobLength)

			pstructCurrentApplications[nAppIndex].dwApplicationWriteOKDomainsLength = i_ncApplicationWriteOKDomainsBlobLength;
		}
		else
		{
			pstructCurrentApplications[nAppIndex].pbyteApplicationWriteOKDomains = NULL;
			pstructCurrentApplications[nAppIndex].dwApplicationWriteOKDomainsLength = 0;
		}
		pstructCurrentApplications[nAppIndex].dwNumOfApplicationWriteOKDomains = i_ncNumOfApplicationWriteOKDomains;
		m_dwProtectedInformationChanged				=	1;
		m_dwProtectedApplicationInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::SetApplicationWriteOKDomains


_VS_LONG	CProtectedStorage::SetApplicationPreference
(
	const _VS_CHAR*		i_cszPreferenceName,
	const _VS_BYTE*		i_pcbyteApplicationPreferencesBlob,
	const _VS_DWORD		i_ncApplicationPreferencesBlobLength,
	const int			i_ncAddApplicationIfItDoesNotExist
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	int					nPrefCompare		=	999;
	int					nPrefExists			=	0;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	_VS_DWORD			dwNewNumberOfPreferences;

	_BYTE**					ppbytePreferenceName		=	NULL;
	_BYTE**					ppbytePreferenceData		=	NULL;
	_DWORD*					pdwPreferenceNameLength		=	NULL;
	_DWORD*					pdwPreferenceDataLength		=	NULL;

	BOOL				boolSuccessFlag		=	FALSE;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_STRING(i_cszPreferenceName)
		VS_CHECK_INPUT_STRING_LEN(i_cszPreferenceName)

		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteApplicationPreferencesBlob)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncApplicationPreferencesBlobLength)


		//	check if the application exists
		hResult =	m_CheckIfApplicationExists ();

		if ( VS_SUCCESS != hResult )
		{
			if ( E_VS_INVALID_APP == hResult )
			{
					//	this means that the application does not exist

				if ( i_ncAddApplicationIfItDoesNotExist )
				{
						//	the client has requested to add the application

								//	this function will add the application
					hResult =	AddApplicationToDB
								(
									m_szApplicationName,
									m_szApplicationHost,
									m_dwIsApplicationEncrypted
								);
					if ( VS_SUCCESS != hResult )
					{
						break;
					}

//					hResult =	EndWrite ();
//					VS_CHECK_HRESULT
				}
				else
				{
//					hResult =	EndRead ();
//					VS_CHECK_HRESULT

						//	the client has not requested to add the application.
						//	so return the error (E_VS_INVALID_APP)
					break;
				}
			}
			else
			{
					//	the m_CheckIfApplicationExists function failed due to
					//	some other reason.
				break;
			}

		}

					//	check the m_dwIsApplicationEncrypted value and assign the appropriate structure array
			//	(Plain Text or Protected) to the local pointer pstructCurrentApplications
		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

				boolSuccessFlag	=	TRUE;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;

				boolSuccessFlag	=	TRUE;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( m_dwIsApplicationEncrypted )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		
		//	confirm that the application exists
		//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{

			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if (0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

			//	check if the preference already exists in which case only the data will be modified
		for ( i = 0; i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; i ++ )
		{
			if(_VS_strlenW (i_cszPreferenceName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i]))
			{
				nPrefCompare = -1;
			}
			else
			{
				nPrefCompare =	::_VS_memcmp ( (_BYTE*) i_cszPreferenceName, pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i], (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nPrefCompare )
			{
				VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[i])

				VS_ALLOC_AND_BYTEBLOB_COPY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[i], i_pcbyteApplicationPreferencesBlob, i_ncApplicationPreferencesBlobLength)

				pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[i] =	i_ncApplicationPreferencesBlobLength;
				
				nPrefExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; i ++ )

		if ( 1 != nPrefExists )
		{
			//	this means that the preference does not exist. so its a new preference

				//	new number of preferences = old number of preferences + 1
			dwNewNumberOfPreferences =	pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences + 1;

							//	allocate memory for the preference name array and the preference data array
					//	allocate memory for the first dimension of the preference name array
			ppbytePreferenceName =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY(ppbytePreferenceName)

					//	allocate memory for the first dimension of the preference data array
			ppbytePreferenceData =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY (ppbytePreferenceData)

						//	allocate memory for the preference name length array
			pdwPreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceNameLength)

						//	allocate memory for the preference data length array
			pdwPreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceDataLength)

			for ( i = 0; i < (int) dwNewNumberOfPreferences - 1; i ++ )
			{
					//	copy all the old preference (name, data and lengths) from existing structures into new structures
//				VS_ALLOC_AND_COPY_PRINTABLE_STRING(pszPreferenceName[i], pstructCurrentApplications[nAppIndex].pszApplicationPreferenceName[i])
				ppbytePreferenceName[i] =	pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i];
//				VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceData[i], pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[i], pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceDataLength[i])
				ppbytePreferenceData[i] =	pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[i];
				pdwPreferenceNameLength[i] =	pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength[i];
				pdwPreferenceDataLength[i] =	pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[i];
			}	//	end		for ( i = 0; i < dwNewNumberOfPreferences - 1; i ++ )
		
				//	add the new preference along with the data and the lengths
			VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceName[i], (_BYTE*) i_cszPreferenceName, (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) )
			VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceData[i], i_pcbyteApplicationPreferencesBlob, i_ncApplicationPreferencesBlobLength)
			pdwPreferenceNameLength[i] =	(_VS_strlenW ( i_cszPreferenceName ) + 1) * sizeof (_VS_CHAR) ;
			pdwPreferenceDataLength[i] =	i_ncApplicationPreferencesBlobLength;

				//	free memory pointed by the old pointers
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName)
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData)
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength)
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength)

				//	make the pointers point to the allocated and filled (with the new pref) memory
			pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName		=	ppbytePreferenceName;
			pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData		=	ppbytePreferenceData;
			pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength	=	pdwPreferenceNameLength;
			pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength	=	pdwPreferenceDataLength;

				//	increase the number of preferences
			pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences ++;

		}	//	end		if ( 1 != nPrefExists )

		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwProtectedInformationChanged				=	1;
				m_dwProtectedApplicationInformationChanged	=	1;

				break;

			case	APPLICATION_DECRYPTED:
					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwPlainTextInformationChanged				=	1;
				m_dwPlainTextApplicationInformationChanged	=	1;

				break;

			default:
				break;
		}	//	end		switch ( m_dwIsApplicationEncrypted )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::SetApplicationPreference


_VS_LONG	CProtectedStorage::GetApplicationPreference
(
	const _VS_CHAR*		i_cszPreferenceName,
	_VS_BYTE**			o_ppbyteApplicationPreferencesBlob,
	_VS_DWORD*			o_pnApplicatoinPreferencesBlobLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	int					nPrefCompare		=	999;
	int					nPrefExists			=	0;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	BOOL				boolSuccessFlag		=	FALSE;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check the input parameters
		VS_CHECK_INPUT_STRING		( i_cszPreferenceName )
		VS_CHECK_INPUT_STRING_LEN	( i_cszPreferenceName )

		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_ppbyteApplicationPreferencesBlob )
		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_pnApplicatoinPreferencesBlobLength )


			//	check the m_dwIsApplicationEncrypted value and assign the appropriate structure array
			//	(Plain Text or Protected) to the local pointer pstructCurrentApplications
		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

				boolSuccessFlag	=	TRUE;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;

				boolSuccessFlag	=	TRUE;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( m_dwIsApplicationEncrypted )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if (0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

				//	for all preferences of the specified application
		for ( i = 0; i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; i ++ )
		{
			if(_VS_strlenW (i_cszPreferenceName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i]))
			{
				nPrefCompare = -1;
			}
			else
			{
				nPrefCompare =	::_VS_memcmp ( (_BYTE*) i_cszPreferenceName, pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i], (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) );
			}


			if ( 0 == nPrefCompare )
			{
					//	thats the application preference
					//	copy the preference data and length into the appropriate parameters
				VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteApplicationPreferencesBlob, pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[i], pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[i])

				*o_pnApplicatoinPreferencesBlobLength =	pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[i];
				
				nPrefExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; i ++ )
		if ( (i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences)\
				&& (1 != nPrefExists) )
		{
				//	this means that the for loop was broken due to some error. so break again.
			break;
		}

		if ( 1 != nPrefExists )
		{
				//	this means that the preference does not exist
			hResult =	E_VS_INVALID_APP_PREF;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetApplicationPreference


_VS_LONG	CProtectedStorage::DeleteApplicationPreference
(
	const _VS_CHAR*		i_cszPreferenceName
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	int					i, j, k;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	int					nPrefCompare		=	999;
	int					nPrefExists			=	0;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	_VS_DWORD			dwNewNumberOfPreferences;

	_BYTE**					ppbytePreferenceName		=	NULL;
	_BYTE**					ppbytePreferenceData		=	NULL;
	_DWORD*					pdwPreferenceNameLength		=	NULL;
	_DWORD*					pdwPreferenceDataLength		=	NULL;

	BOOL				boolSuccessFlag		=	FALSE;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_STRING(i_cszPreferenceName)
		VS_CHECK_INPUT_STRING_LEN(i_cszPreferenceName)

			//	check the m_dwIsApplicationEncrypted value and assign the appropriate structure array
			//	(Plain Text or Protected) to the local pointer pstructCurrentApplications
		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

				boolSuccessFlag	=	TRUE;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;

				boolSuccessFlag	=	TRUE;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( m_dwIsApplicationEncrypted )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

			/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
			*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if (0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

			//	check if the preference exists
		for ( i = 0; i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; i ++ )
		{
			if(_VS_strlenW (i_cszPreferenceName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i]))
			{
				nPrefCompare = -1;
			}
			else
			{
				nPrefCompare =	::_VS_memcmp ( (_BYTE*) i_cszPreferenceName, pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[i], (_VS_strlenW (i_cszPreferenceName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nPrefCompare )
			{
				nPrefExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; i ++ )

		//
		//	IMPORTANT NOTE:	The value of i when the for loop breaks is the index of the preference to be deleted.
		//					this will be used later.
		//

		if ( 1 == nPrefExists )
		{
						//	this means that the preference exits. so delete it.

				//	new number of preferences = old number of preferences - 1
			dwNewNumberOfPreferences =	pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences - 1;

					//	allocate memory for the preference name array and the preference data array
					//	allocate memory for the first dimension of the preference name array
			ppbytePreferenceName =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY(ppbytePreferenceName)

					//	allocate memory for the first dimension of the preference data array
			ppbytePreferenceData =	(_BYTE**) m_VS_HeapAlloc
									(
										dwNewNumberOfPreferences * sizeof (_BYTE*)
									);
			VS_CHECK_ALLOCATED_MEMORY (ppbytePreferenceData)

						//	allocate memory for the preference name length array
			pdwPreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceNameLength)

						//	allocate memory for the preference data length array
			pdwPreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
										(
											dwNewNumberOfPreferences * sizeof (_DWORD)
										);
			VS_CHECK_ALLOCATED_MEMORY (pdwPreferenceDataLength)

			for ( j = 0, k = 0; j < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; j ++ )
			{
				if ( j != i )
				{
						//	this pref is not to be deleted.
						//	so copy all the old preference (name, data and lengths) from existing structures into new structures
//					VS_ALLOC_AND_COPY_PRINTABLE_STRING(pszPreferenceName[k], pstructCurrentApplications[nAppIndex].pszApplicationPreferenceName[j])
					ppbytePreferenceName[k] =	pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[j];
//					VS_ALLOC_AND_BYTEBLOB_COPY(ppbytePreferenceData[k], pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[j], pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[j])
					ppbytePreferenceData[k] =	pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[j];
					pdwPreferenceNameLength[k] =	pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength[j];
					pdwPreferenceDataLength[k] =	pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[j];

					k ++;
				}	//	end		if ( j != i )
				else
				{
						//	this pref is to be deleted. so free the memory for the name and data of this preference
					VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName[j])
					VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData[j])

						//	and set lengths to zero
					pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength[j]	=	0;
					pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength[j]	=	0;

				}	//	end		else
			}	//	end		for ( j = 0, k = 0; j < (int) pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences; j ++ )

						//	free memory pointed by the old pointers
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName)
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData)
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength)
			VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength)


				//	make the pointers point to the allocated and filled (with the new pref) memory
			pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName		=	ppbytePreferenceName;
			pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData		=	ppbytePreferenceData;
			pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength	=	pdwPreferenceNameLength;
			pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength	=	pdwPreferenceDataLength;

				//	decrease the number of preferences
			pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences --;

			switch ( m_dwIsApplicationEncrypted )
			{
				case	APPLICATION_ENCRYPTED:
						//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
						//	at the end of the session
					m_dwProtectedInformationChanged				=	1;
					m_dwProtectedApplicationInformationChanged	=	1;

					break;

				case	APPLICATION_DECRYPTED:
						//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
						//	at the end of the session
					m_dwPlainTextInformationChanged				=	1;
					m_dwPlainTextApplicationInformationChanged	=	1;

					break;

				default:
					break;
			}	//	end		switch ( m_dwIsApplicationEncrypted )

		}	//	end		if ( 1 == nPrefExists )
		else
		{
			hResult =	E_VS_INVALID_APP_PREF;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::DeleteApplicationPreference


_VS_LONG	CProtectedStorage::DeleteAllApplicationPreferences ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int					i;
	
	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	int					nAppIndex			=	9999;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;

	_VS_DWORD			dwNumberOfApplications	=	0;

	BOOL				boolSuccessFlag		=	FALSE;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check the m_dwIsApplicationEncrypted value and assign the appropriate structure array
			//	(Plain Text or Protected) to the local pointer pstructCurrentApplications
		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;

				boolSuccessFlag	=	TRUE;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;

				boolSuccessFlag	=	TRUE;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( m_dwIsApplicationEncrypted )

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	confirm that the application exists
			//	and get its index
		for ( i = 0; i < (int) dwNumberOfApplications; i++ )
		{
			if(_VS_strlenW (m_szApplicationName) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationName))
			{
				nAppNameCompare = -1;
			}
			else
			{
				nAppNameCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationName, pstructCurrentApplications[i].pbyteApplicationName, (_VS_strlenW (m_szApplicationName) + 1) * sizeof (_VS_CHAR) ); // l
			}

/*
			if(_VS_strlenW (m_szApplicationHost) != _VS_strlenW ((_VS_CHAR*)pstructCurrentApplications[i].pbyteApplicationHost))
			{
				nAppHostCompare = -1;
			}
			else
			{
				nAppHostCompare =	::_VS_memcmp ( (_BYTE*) m_szApplicationHost, pstructCurrentApplications[i].pbyteApplicationHost, (_VS_strlenW (m_szApplicationHost) + 1) * sizeof (_VS_CHAR) ); // l
			}
*/

//			if ( 0 == nAppNameCompare && 0 == nAppHostCompare )
			if (0 == nAppNameCompare)
			{
					//	turn on the app exists flag
				nAppExists =	1;
				nAppIndex =	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

			//	free memory occupied by the application preference (name, data and lengths)
		VS_FREE_MEMORY_2D(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceName, pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences)
		VS_FREE_MEMORY_2D(pstructCurrentApplications[nAppIndex].ppbyteApplicationPreferenceData, pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences)
		VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceNameLength)
		VS_FREE_MEMORY(pstructCurrentApplications[nAppIndex].pdwApplicationPreferenceDataLength)
		
			//	reset the number of preferences to zero
		pstructCurrentApplications[nAppIndex].dwNumberOfApplicationPreferences =	0;

		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwProtectedInformationChanged				=	1;
				m_dwProtectedApplicationInformationChanged	=	1;

				break;

			case	APPLICATION_DECRYPTED:
					//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
					//	at the end of the session
				m_dwPlainTextInformationChanged				=	1;
				m_dwPlainTextApplicationInformationChanged	=	1;

				break;

			default:
				break;
		}	//	end		switch ( m_dwIsApplicationEncrypted )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::DeleteAllApplicationPreferences ()


// CR#21529 - Changed the method signature to get the values for Private Key exportable flag
_VS_LONG	CProtectedStorage::AddPrivateKeyToDB
(
	const _VS_BYTE*		i_pcbytePrivateKeyBlob,
	const _VS_DWORD		i_ncPrivateKeyBlobLength,
	const _VS_BYTE*		i_pcbyteAssociatedHash,
	const _VS_DWORD		i_ncAssociatedHashLength,
	const _VS_DWORD		i_ncPrivateKeyExportable
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	VSPS_PrivateKeyInformation*		pstructPrivateKeys		=	NULL;

	int					i;

	int					nPvkCompare	=	999;
	int					nPvkExists	=	0;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check the input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbytePrivateKeyBlob)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncPrivateKeyBlobLength)

		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteAssociatedHash)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncAssociatedHashLength)


			//	check if the private key (associated hash) already exists
			//	for this perform _VS_memcmp with the larger size byte blob to avoid subblob match
			//	i.e. blobs 'a' and 'ab' with length 1 will match. so compare them with length 2
		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
		{
			if ( i_ncAssociatedHashLength > m_pstructPrivateKeyInformation[i].dwAssociatedHashLength )
			{
				nPvkCompare =	::_VS_memcmp ( i_pcbyteAssociatedHash, m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, i_ncAssociatedHashLength );
			}
			else
			{
				nPvkCompare =	::_VS_memcmp ( i_pcbyteAssociatedHash, m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, m_pstructPrivateKeyInformation[i].dwAssociatedHashLength );
			}

			if ( 0 == nPvkCompare )
			{
					//	turn on the private key exists flag
				nPvkExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

		if ( 1 == nPvkExists )
		{
				//	this means that the private key already exists. so return this error
			hResult =	E_VS_PVK_ALREADY_EXISTS;
			break;
		}

			//	allocate memory for new structure array with one more element
		pstructPrivateKeys =	(VSPS_PrivateKeyInformation*) m_VS_HeapAlloc
								(
									(m_dwNumberOfPrivateKeys + 1) * sizeof (VSPS_PrivateKeyInformation)
								);
		VS_CHECK_ALLOCATED_MEMORY(pstructPrivateKeys)

			//	copy all existing elements into the new array
		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
		{
			pstructPrivateKeys[i].pbytePrivateKeyBlob		=	m_pstructPrivateKeyInformation[i].pbytePrivateKeyBlob;
			pstructPrivateKeys[i].pbyteAssociatedHash		=	m_pstructPrivateKeyInformation[i].pbyteAssociatedHash;
			pstructPrivateKeys[i].dwPrivateKeyBlobLength	=	m_pstructPrivateKeyInformation[i].dwPrivateKeyBlobLength;
			pstructPrivateKeys[i].dwAssociatedHashLength	=	m_pstructPrivateKeyInformation[i].dwAssociatedHashLength;
			// Modified by - Infosys Technologies Ltd. 
			// Change Request - CR#21529
			// Description - Add the PrivateKeyExportable flag to the structure.
			// CR#21529 Begin
			// Date Modified - July 05, 2004
			pstructPrivateKeys[i].dwPrivateKeyExportableFlag	=	m_pstructPrivateKeyInformation[i].dwPrivateKeyExportableFlag;
			// CR#21529 End
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

			//	allocate memory for the private key blob and the associated hash blob and copy it
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructPrivateKeys[i].pbytePrivateKeyBlob, i_pcbytePrivateKeyBlob, i_ncPrivateKeyBlobLength)
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructPrivateKeys[i].pbyteAssociatedHash, i_pcbyteAssociatedHash, i_ncAssociatedHashLength)

			//	also fill the length structures
		pstructPrivateKeys[i].dwPrivateKeyBlobLength =	i_ncPrivateKeyBlobLength;
		pstructPrivateKeys[i].dwAssociatedHashLength =	i_ncAssociatedHashLength;

		// Modified by - Infosys Technologies Ltd. 
		// Change Request - CR#21529
		// Description - Set the value for privateKeyExportable flag passed to this function.
		// CR#21529 Begin
		// Date Modified - July 06, 2004
		pstructPrivateKeys[i].dwPrivateKeyExportableFlag =	i_ncPrivateKeyExportable;
		// CR#21529 - End
			//	free memory for the private structure array
		VS_FREE_MEMORY( m_pstructPrivateKeyInformation )

			//	the member pointer to array of structure now points to the new data
		m_pstructPrivateKeyInformation =	pstructPrivateKeys;

			//	increase the count of the private keys
		m_dwNumberOfPrivateKeys ++;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwProtectedInformationChanged	=	1;
		m_dwPrivateKeysChanged			=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::AddPrivateKeyToDB



_VS_LONG	CProtectedStorage::RemovePrivateKeyFromDB
(
	const _VS_BYTE*		i_pcbyteAssociatedHash,
	const _VS_DWORD		i_ncAssociatedHashLength
)
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	VSPS_PrivateKeyInformation*		pstructPrivateKeys		=	NULL;

	int						nPvkCompare				=	999;
	int						nPvkExists				=	0;
	int						nPvkIndex				=	9999;

	int			i, j;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteAssociatedHash)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncAssociatedHashLength)

			//	make sure that the private key (associated hash) exists
			//	for this perform _VS_memcmp with the larger size byte blob to avoid subblob match
			//	i.e. blobs 'a' and 'ab' with length 1 will match. so compare them with length 2
		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
		{
			if ( i_ncAssociatedHashLength > m_pstructPrivateKeyInformation[i].dwAssociatedHashLength )
			{
				nPvkCompare =	::_VS_memcmp ( i_pcbyteAssociatedHash, m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, i_ncAssociatedHashLength );
			}
			else
			{
				nPvkCompare =	::_VS_memcmp ( i_pcbyteAssociatedHash, m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, m_pstructPrivateKeyInformation[i].dwAssociatedHashLength );
			}

			if ( 0 == nPvkCompare )
			{
					//	turn on the private key exists flag and set the index
				nPvkExists	=	1;
				nPvkIndex	=	i;
				break;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

		if ( 0 == nPvkExists )
		{
				//	this means that the private key does not exist. so return this error
			hResult =	E_VS_INVALID_PVK;
			break;
		}

			//	allocate memory for new structure array with one less element
		pstructPrivateKeys =	(VSPS_PrivateKeyInformation*) m_VS_HeapAlloc
								(
									(m_dwNumberOfPrivateKeys - 1) * sizeof (VSPS_PrivateKeyInformation)
								);
		VS_CHECK_ALLOCATED_MEMORY(pstructPrivateKeys)

			//	copy all existing elements into the new array
		for ( i = 0, j = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
		{
			if ( i != (int) nPvkIndex )
			{
					//	this is not the private key to be deleted. so copy the private key blob and 
					//	the associated hash and the lengths into the into the new structures
				pstructPrivateKeys[j].pbytePrivateKeyBlob		=	m_pstructPrivateKeyInformation[i].pbytePrivateKeyBlob;
				pstructPrivateKeys[j].pbyteAssociatedHash		=	m_pstructPrivateKeyInformation[i].pbyteAssociatedHash;
				pstructPrivateKeys[j].dwPrivateKeyBlobLength	=	m_pstructPrivateKeyInformation[i].dwPrivateKeyBlobLength;
				pstructPrivateKeys[j].dwAssociatedHashLength	=	m_pstructPrivateKeyInformation[i].dwAssociatedHashLength;

				// Modified by - Infosys Technologies Ltd. 
				// Change Request - CR#21529
				// Description - Retrieve the value for privateKeyExportable flag passed to this function.
				// CR#21529 Begin
				// Date Modified - July 07, 2004				
				pstructPrivateKeys[j].dwPrivateKeyExportableFlag	=	m_pstructPrivateKeyInformation[i].dwPrivateKeyExportableFlag;

				// CR#21529 End

				j++;
			}
			else
			{
					//	this is the private key to be deleted.
					//	so free all the memory allocated for this private key  and the assocaited hash
				VS_FREE_MEMORY(m_pstructPrivateKeyInformation[i].pbytePrivateKeyBlob)
				VS_FREE_MEMORY(m_pstructPrivateKeyInformation[i].pbyteAssociatedHash)

					//	reset the private key and hash length to zero
				m_pstructPrivateKeyInformation[i].dwPrivateKeyBlobLength	=	0;
				m_pstructPrivateKeyInformation[i].dwAssociatedHashLength	=	0;

				// Modified by - Infosys Technologies Ltd. 
				// Change Request - CR#21529
				// Description - Set the value for the dwPrivateKeyExportableFlag to zero.
				// CR#21529 Begin
				// Date Modified - July 07, 2004				
				m_pstructPrivateKeyInformation[i].dwPrivateKeyExportableFlag	=	0;
				// CR#21529 End

			}
		}	//	end		for ( i = 0, j = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
		
			//	free memory for the private structure array
		VS_FREE_MEMORY (m_pstructPrivateKeyInformation);

			//	the member pointer to array of structure now points to the new data
		m_pstructPrivateKeyInformation =	pstructPrivateKeys;

			//	decrease the count of the private keys
		m_dwNumberOfPrivateKeys --;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwProtectedInformationChanged	=	1;
		m_dwPrivateKeysChanged			=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::RemovePrivateKeyFromDB


// Modified by - Infosys Technologies Ltd. 
// Change Request - CR#21529
// Description - Change the method signature to pass additional parameter i_IsPrivateKeyExportable to the method.
// CR#21529 Begin
// Date Modified - July 05, 2004				
_VS_LONG	CProtectedStorage::GetPrivateKeyFromDB
(
	const _VS_BYTE*		i_pcbyteAssociatedHash,
	const _VS_DWORD		i_ncAssociatedHashLength,
	_VS_BYTE**			o_ppbytePrivateKeyBlob,
	_VS_DWORD*			o_pnPrivateKeyBlobLength,
	_VS_DWORD*			i_IsPrivateKeyExportable // additional parameter to retrieve the "private key exportable" flag.
)
// CR#21529 End
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int						i;

	int						nPvkCompare			=	999;
	int						nPvkExists			=	0;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteAssociatedHash)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncAssociatedHashLength)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_ppbytePrivateKeyBlob)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnPrivateKeyBlobLength)
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_IsPrivateKeyExportable)

			//	make sure that the private key (associated hash) exists
			//	for this perform _VS_memcmp with the larger size byte blob to avoid subblob match
			//	i.e. blobs 'a' and 'ab' with length 1 will match. so compare them with length 2
		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
		{
			if ( i_ncAssociatedHashLength > m_pstructPrivateKeyInformation[i].dwAssociatedHashLength )
			{
				nPvkCompare =	::_VS_memcmp ( i_pcbyteAssociatedHash, m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, i_ncAssociatedHashLength );
			}
			else
			{
				nPvkCompare =	::_VS_memcmp ( i_pcbyteAssociatedHash, m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, m_pstructPrivateKeyInformation[i].dwAssociatedHashLength );
			}

			if ( 0 == nPvkCompare )
			{
					//	copy the private key blob in the out parameter and the length
				VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbytePrivateKeyBlob, m_pstructPrivateKeyInformation[i].pbytePrivateKeyBlob, m_pstructPrivateKeyInformation[i].dwPrivateKeyBlobLength)
				*o_pnPrivateKeyBlobLength =	m_pstructPrivateKeyInformation[i].dwPrivateKeyBlobLength;
				// Modified by - Infosys Technologies Ltd. 
				// Change Request - CR#21529
				// Description - Set the value of PrivateKeyExportable flag in the private key information structure.
				// CR#21529 Begin
				// Date Modified - July 08, 2004				
				if(m_dwPSFirstVersionNumber < VSPS_VERSION_FIRST_NUMBER)
				{
					// if the version is less that 6, it means that the profile being read does not
					// support private key non-exportable functionality. Therefore set this flag to 1
					// This will allow private key export functionality for older profile versions.
					*i_IsPrivateKeyExportable = 1;
				}
				else
				{
					*i_IsPrivateKeyExportable = m_pstructPrivateKeyInformation[i].dwPrivateKeyExportableFlag;
				}
				// CR21529 - End
					//	turn on the private key exists flag and set the index
				nPvkExists	=	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

		if ( 0 == nPvkExists )
		{
				//	this means that the private key does not exist. so return this error
			hResult =	E_VS_INVALID_PVK;
			break;
		}

		hResult	=	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetPrivateKeyFromDB


_VS_LONG	CProtectedStorage::AddInformationBlobToDB
(
	const _VS_CHAR*		i_cszInformationBlobName,
	const _VS_BYTE*		i_pcbyteInformationBlob,
	const _VS_DWORD		i_ncInformationBlobLength
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int						i;
	int						nIBCompare			=	999;
	int						nIBExists			=	0;

	VSPS_InformationBlob*	pstructInfoBlob		=	NULL;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check the input parameters
		VS_CHECK_INPUT_STRING(i_cszInformationBlobName)
		VS_CHECK_INPUT_STRING_LEN(i_cszInformationBlobName)
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_pcbyteInformationBlob)
		VS_CHECK_LENGTH_FOR_ZERO(i_ncInformationBlobLength)

			//	check if the information blob already exists
			//	for this compare the information blob name
		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )
		{
			if(_VS_strlenW (i_cszInformationBlobName) != _VS_strlenW ((_VS_CHAR*)m_pstructInformationBlob[i].pbyteInformationBlobName))
			{
				nIBCompare = -1;
			}
			else
			{
				nIBCompare =	::_VS_memcmp ( (_BYTE*) i_cszInformationBlobName, m_pstructInformationBlob[i].pbyteInformationBlobName, (_VS_strlenW (i_cszInformationBlobName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nIBCompare )
			{
					//	turn on the info blob exists flag
				nIBExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )

		if ( 1 == nIBExists )
		{
				//	the information blob already exists. so return this error
			hResult =	E_VS_INFO_BLOB_ALREADY_EXISTS;
			break;
		}

					//	allocate memory for new structure array with one more element
		pstructInfoBlob =	(VSPS_InformationBlob*) m_VS_HeapAlloc
							(
								(m_dwNumberOfInformationBlobs + 1) * sizeof (VSPS_InformationBlob)
							);
		VS_CHECK_ALLOCATED_MEMORY(pstructInfoBlob)

			//	copy all existing elements into the new array
		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )
		{
			pstructInfoBlob[i].pbyteInformationBlobName		=	m_pstructInformationBlob[i].pbyteInformationBlobName;
			pstructInfoBlob[i].dwInformationBlobNameLength	=	m_pstructInformationBlob[i].dwInformationBlobNameLength;
			pstructInfoBlob[i].pbyteInformationBlobData		=	m_pstructInformationBlob[i].pbyteInformationBlobData;
			pstructInfoBlob[i].dwInformationBlobDataLength	=	m_pstructInformationBlob[i].dwInformationBlobDataLength;
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )

			//	allocate memory for the info blob name and copy it and the length
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructInfoBlob[i].pbyteInformationBlobName, (_BYTE*) i_cszInformationBlobName, (_VS_strlenW (i_cszInformationBlobName) + 1) * sizeof (_VS_CHAR) )
		pstructInfoBlob[i].dwInformationBlobNameLength = (_VS_strlenW (i_cszInformationBlobName) + 1) * sizeof (_VS_CHAR);

			//	allocate memory for the info blob data and copy it and the length
		VS_ALLOC_AND_BYTEBLOB_COPY(pstructInfoBlob[i].pbyteInformationBlobData, i_pcbyteInformationBlob, i_ncInformationBlobLength)
		pstructInfoBlob[i].dwInformationBlobDataLength =	i_ncInformationBlobLength;

			//	free memory for the private structure array
		VS_FREE_MEMORY( m_pstructInformationBlob )

			//	the member pointer to array of structure now points to the new data
		m_pstructInformationBlob =	pstructInfoBlob;

			//	increase the count of the information blobs
		m_dwNumberOfInformationBlobs ++;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwProtectedInformationChanged	=	1;
		m_dwInformationBlobChanged		=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::AddInformationBlobToDB


_VS_LONG	CProtectedStorage::GetInformationBlob
(
	const _VS_CHAR*		i_cszInformationBlobName,
	_VS_BYTE**			o_ppbyteInformationBlob,
	_VS_DWORD*			o_pnInformationBlobLength
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int						i;
	int						nIBCompare			=	999;
	int						nIBExists			=	0;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_cszInformationBlobName)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_ppbyteInformationBlob)
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnInformationBlobLength)

			//	make sure that the information blob exists by comparing information blob name
		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )
		{
			if(_VS_strlenW (i_cszInformationBlobName) != _VS_strlenW ((_VS_CHAR*)m_pstructInformationBlob[i].pbyteInformationBlobName))
			{
				nIBCompare = -1;
			}
			else
			{
				nIBCompare =	::_VS_memcmp ( (_BYTE*) i_cszInformationBlobName, m_pstructInformationBlob[i].pbyteInformationBlobName, (_VS_strlenW (i_cszInformationBlobName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nIBCompare )
			{
					//	copy the information blob in the out parameter and the length
				VS_ALLOC_AND_BYTEBLOB_COPY(*o_ppbyteInformationBlob, m_pstructInformationBlob[i].pbyteInformationBlobData, m_pstructInformationBlob[i].dwInformationBlobDataLength)
				*o_pnInformationBlobLength =	m_pstructInformationBlob[i].dwInformationBlobDataLength;

					//	turn on the info blob exists flag
				nIBExists =	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

		if ( 0 == nIBExists )
		{
				//	this means that the private key does not exist. so return this error
			hResult =	E_VS_INVALID_INFO_BLOB;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetInformationBlob


_VS_LONG	CProtectedStorage::RemoveInformationBlobFromDB
(
	const _VS_CHAR*		i_cszInformationBlobName
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int						i, j;
	int						nIBCompare			=	999;
	int						nIBExists			=	0;
	int						nIBIndex			=	9999;

	VSPS_InformationBlob*	pstructInfoBlob		=	NULL;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(i_cszInformationBlobName)

			//	make sure that the information blob exists by comparing information blob name
		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )
		{
			if(_VS_strlenW (i_cszInformationBlobName) != _VS_strlenW ((_VS_CHAR*)m_pstructInformationBlob[i].pbyteInformationBlobName))
			{
				nIBCompare = -1;
			}
			else
			{
				nIBCompare =	::_VS_memcmp ( (_BYTE*) i_cszInformationBlobName, m_pstructInformationBlob[i].pbyteInformationBlobName, (_VS_strlenW (i_cszInformationBlobName) + 1) * sizeof (_VS_CHAR) );
			}

			if ( 0 == nIBCompare )
			{
					//	turn on the info blob exists flag and set the index
				nIBIndex	=	i;
				nIBExists	=	1;
				break;
			}
		}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

		if ( 0 == nIBExists )
		{
				//	this means that the private key does not exist. so return this error
			hResult =	E_VS_INVALID_INFO_BLOB;
			break;
		}

			//	allocate memory for new structure array with one less element
		pstructInfoBlob =	(VSPS_InformationBlob*) m_VS_HeapAlloc
							(
								(m_dwNumberOfInformationBlobs - 1) * sizeof (VSPS_InformationBlob)
							);
		VS_CHECK_ALLOCATED_MEMORY(pstructInfoBlob)

			//	copy all existing elements into the new array
		for ( i = 0, j = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )
		{
			if ( i != (int) nIBIndex )
			{
					//	this is not the information blob to be deleted. so copy the information blob and 
					//	the name and the lengths into the into the new structures
				pstructInfoBlob[j].pbyteInformationBlobName		=	m_pstructInformationBlob[i].pbyteInformationBlobName;
				pstructInfoBlob[j].dwInformationBlobNameLength	=	m_pstructInformationBlob[i].dwInformationBlobNameLength;
				pstructInfoBlob[j].pbyteInformationBlobData		=	m_pstructInformationBlob[i].pbyteInformationBlobData;
				pstructInfoBlob[j].dwInformationBlobDataLength	=	m_pstructInformationBlob[i].dwInformationBlobDataLength;

				j++;
			}
			else
			{
					//	this is the infromation blob to be deleted.
					//	so free all the memory allocated for this information blob and the name
				VS_FREE_MEMORY(m_pstructInformationBlob[i].pbyteInformationBlobData)
				VS_FREE_MEMORY(m_pstructInformationBlob[i].pbyteInformationBlobName)

					//	reset the information blob and name length
				m_pstructInformationBlob[i].dwInformationBlobNameLength	=	0;
				m_pstructInformationBlob[i].dwInformationBlobDataLength	=	0;
			}
		}	//	end		for ( i = 0, j = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )

			//	free memory for the private structure array
		VS_FREE_MEMORY (m_pstructInformationBlob);

			//	the member pointer to array of structure now points to the new data
		m_pstructInformationBlob =	pstructInfoBlob;

			//	decrease the count of the private keys
		m_dwNumberOfInformationBlobs --;

			//	set the 'changed' flags to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwProtectedInformationChanged	=	1;
		m_dwInformationBlobChanged		=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::RemoveInformationBlobFromDB



_VS_LONG	CProtectedStorage::GetNumberOfCertificatesInDB
(
	_VS_DWORD*			o_pnNumberOfCertificates
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnNumberOfCertificates)

		*o_pnNumberOfCertificates =	m_dwNumberOfCertificates;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetNumberOfCertificatesInDB


_VS_LONG	CProtectedStorage::GetNumberOfPrivateKeysInDB
(
	_VS_DWORD*			o_pnNumberOfPrivateKeys
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnNumberOfPrivateKeys)

		*o_pnNumberOfPrivateKeys =	m_dwNumberOfPrivateKeys;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetNumberOfPrivateKeysInDB



_VS_LONG	CProtectedStorage::GetNumberOfPlainTextApplications
(
	_VS_DWORD*			o_pnNumberOfPlainTextApplications
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnNumberOfPlainTextApplications)

		*o_pnNumberOfPlainTextApplications =	m_dwNumberOfPlainTextApplications;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetNumberOfPlainTextApplications



_VS_LONG	CProtectedStorage::GetNumberOfProtectedApplications
(
	_VS_DWORD*			o_pnNumberOfProtectedApplications
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnNumberOfProtectedApplications)

		*o_pnNumberOfProtectedApplications =	m_dwNumberOfProtectedApplications;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetNumberOfProtectedApplications


_VS_LONG	CProtectedStorage::GetNumberOfInformationBlobs
(
	_VS_DWORD*			o_pnNumberOfInformationBlobs
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

			//	check input parameters
		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnNumberOfInformationBlobs)

		*o_pnNumberOfInformationBlobs =	m_dwNumberOfInformationBlobs;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetNumberOfInformationBlobs


_VS_LONG	CProtectedStorage::FreeMemoryBlob
(
	void**				io_ppvoidMemoryBlob
)
{
	VS_FREE_MEMORY(*io_ppvoidMemoryBlob)

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::FreeMemoryBlob



_VS_LONG	CProtectedStorage::GetPasswordStrength
(
	_VS_DWORD*			o_pnPasswordStrength
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_READ_OR_WRITE_CALLED

		VS_CHECK_INPUT_POINTER_FOR_NULL(o_pnPasswordStrength)

		*o_pnPasswordStrength =	m_dwPasswordStrength;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::GetPasswordStrength


_VS_LONG	CProtectedStorage::SetPasswordStrength
(
	const _VS_DWORD		i_ncPasswordStrength
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

		if ( 1 != i_ncPasswordStrength )
		{
			hResult =	E_VS_INVALIDARG;
			break;
		}

		m_dwPasswordStrength =	i_ncPasswordStrength;

			//	set the 'changed' flag to 1. This will ensure that the data is re-encoded 
			//	at the end of the session
		m_dwPlainTextInformationChanged		=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::SetPasswordStrength


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	ProvidePassword
//
//	Parameters
//		const _VS_CHAR* 	i_cszPassword	-	the password will be provided using this
//												parameter
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_BAD_PASSWORD		-	the password provided is wrong
//
//	Description		:	The password will be using this method (by the client to the class).
//						The time when the password is provided (m_longTimePasswordProvided) is
//						recalculated.
//						If the password timeout = 0 (i.e. always ask for password) then the
//						m_dwPasswordTimeOutAfterOneFunction flag is set.			
//
///////////////////////////////////////////////////////////////////////////////
/*
_VS_LONG	CProtectedStorage::ProvidePassword
(
	const _VS_CHAR* 	i_cszPassword
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		if ( ::strcmp ( m_szPassword, i_cszPassword ) )
		{
			hResult =	E_VS_BAD_PASSWORD;
			break;
		}

		time ( &m_longTimePasswordProvided );

		if ( 0 == m_dwPasswordTimeOutIntervalInSeconds )
		{
			m_dwPasswordTimeOutAfterOneFunction =	1;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::ProvidePassword
*/


_VS_LONG	CProtectedStorage::BeginRead
(
	const	_VS_DWORD	i_cnMode,
	const	_VS_DWORD	i_cnWaitTime
)
{
	_VS_LONG				hResult						=	E_VS_FAIL;

	BOOL					bResult						=	FALSE;

	BOOL					boolReleaseMutex			=	FALSE;

//	_VS_DWORD				dwResult					=	9999;

//	_VS_LONG				lPreviousCount				=	9999;

	_VS_DWORD				dwNumberOfReadProcesses		=	9999;
	_VS_DWORD				dwNumberOfWriteprocesses	=	9999;

	while (1)
	{
		VS_CHECK_IF_INITIALIZED

		VS_GET_WAIT_FOR_SINGLE_OBJECT_TIMEOUT

					//	grab the read mutex. the read mutex controls the access to the read semaphore.
					//	grabing the read mutex will insure that only one process is using the read
					//	semaphore at any given instance.
		hResult =	::WaitForSingleObject
					(
						m_hReadMutex,
						m_dwWaitForSingleObjectTimeOut
					);
		VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT

		boolReleaseMutex =	TRUE;

		hResult =	m_CleanPIDList
					(
						&dwNumberOfReadProcesses,
						&dwNumberOfWriteprocesses
					);
		VS_CHECK_HRESULT

		if ( 0 == dwNumberOfReadProcesses )
		{
			hResult =	::WaitForSingleObject
						(
							m_hWriteSemaphore,
							m_dwWaitForSingleObjectTimeOut
						);
			VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT
		}

		hResult =	m_AddToPIDList ();
		VS_CHECK_HRESULT

				//	the function will update the data structures if necessary
		hResult =	m_UpdateDataStructuresIfNecessary ( UPDATE_ALL_IF_POSSIBLE );
		
			//	PID: add code to add the PID of the process to a global list.

				//	set the begin flags
		m_dwBeginReadCalled		=	BEGIN_READ_CALLED;
		m_dwBeginCalledBefore	=	BEGIN_CALLED;


		VS_CHECK_HRESULT	//	this will check the return value of m_UpdateDataStructureIfNecessary
							//	the flags m_dwBeginReadCalled and m_dwBeginCalledBefore should be set
							//	even if the function fails. if those flags are set before calling the funciton
							//	then the function tries to free some memory and crashes.
							//
							//	so the function is called the flags are set and then the funciton value is checked.

//					//	release the read mutex.
//		bResult =	::ReleaseMutex
//					(
//						m_hReadMutex
//					);
//		VS_CHECK_BRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	if ( TRUE == boolReleaseMutex )
	{
					//	release the read mutex.
		bResult =	::ReleaseMutex
					(
						m_hReadMutex
					);
	}

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::BeginRead


_VS_LONG	CProtectedStorage::EndRead ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;
	BOOL					bResult				=	FALSE;

	_VS_LONG				lPreviousCount		=	9999;

	_VS_DWORD				dwNumberOfReadProcesses		=	9999;
	_VS_DWORD				dwNumberOfWriteprocesses	=	9999;
	
	while (1)
	{
		VS_CHECK_IF_INITIALIZED

		if ( BEGIN_READ_CALLED == m_dwBeginReadCalled )
		{
			hResult =	::WaitForSingleObject
						(
							m_hReadMutex,
							m_dwWaitForSingleObjectTimeOut
						);
			VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT

			hResult =	m_CleanPIDList 
						(
							&dwNumberOfReadProcesses,
							&dwNumberOfWriteprocesses
						);
			VS_CHECK_HRESULT

			hResult =	m_DeleteFromPIDList ( &dwNumberOfReadProcesses );
			VS_CHECK_HRESULT

			if ( 0 == dwNumberOfReadProcesses )
			{
						//	release the read semaphore
				bResult =	::ReleaseSemaphore
							(
								m_hWriteSemaphore,
								1,
								&lPreviousCount
							);
				VS_CHECK_BRESULT
			}

				//	reset the begin read flag
			m_dwBeginReadCalled		=	0;

						//	release the read mutex.
			bResult =	::ReleaseMutex
						(
							m_hReadMutex
						);
			VS_CHECK_BRESULT
		}	//	end		if ( BEGIN_READ_CALLED == m_dwBeginReadCalled )
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::EndRead ()


_VS_LONG	CProtectedStorage::BeginWrite
(
	const	_VS_DWORD	i_cnMode,
	const	_VS_DWORD	i_cnWaitTime
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	BOOL					bResult				=	FALSE;

//	_VS_DWORD				dwResult			=	9999;
	
	_VS_DWORD				dwNumberOfReadProcesses		=	9999;
	_VS_DWORD				dwNumberOfWriteprocesses	=	9999;

	while (1)
	{
		VS_CHECK_IF_INITIALIZED

		VS_GET_WAIT_FOR_SINGLE_OBJECT_TIMEOUT

		hResult =	::WaitForSingleObject
					(
						m_hReadMutex,
						m_dwWaitForSingleObjectTimeOut
					);
		VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT

		hResult =	m_CleanPIDList
					(
						&dwNumberOfReadProcesses,
						&dwNumberOfWriteprocesses
					);
		
					//	release the read mutex.
		bResult =	::ReleaseMutex
					(
						m_hReadMutex
					);
		VS_CHECK_BRESULT
		VS_CHECK_HRESULT	//	this will check the return value of the m_CleanPIDList function
							//	even if the function has failed the m_hReadMutex should be released
							//	so this check is done after releasing the mutex

		hResult =	::WaitForSingleObject
					(
						m_hWriteSemaphore,
						m_dwWaitForSingleObjectTimeOut
					);
		VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT

		hResult =	m_SetWritePID ();
		VS_CHECK_HRESULT

				//	the function will update the data structures if necessary
		hResult =	m_UpdateDataStructuresIfNecessary ( UPDATE_ALL_IF_POSSIBLE );

				//	set the begin flags
		m_dwBeginWriteCalled	=	BEGIN_WRITE_CALLED;
		m_dwBeginCalledBefore	=	BEGIN_CALLED;

		VS_CHECK_HRESULT	//	this will check the return value of m_UpdateDataStructureIfNecessary
							//	the flags m_dwBeginReadCalled and m_dwBeginCalledBefore should be set
							//	even if the function fails. if those flags are set before calling the funciton
							//	then the function tries to free some memory and crashes.
							//
							//	so the function is called the flags are set and then the funciton value is checked.


//
//	Anand		May 03, 2001
//
//	At this point the profile contents are already read in the data strucutres.
//	While doing so the version of the protected and the plain text portions
//	of the profile was taken into account.
//
//	while writing the profile we now have to upgrade the profile. The plain-text portion
//	of the profile will definitely be upgraded but the protected portion of the profile
//	will be upgraded only if the password is provided.
//


			// upgrade the version number for the local profiles and roaming profiles managed by
			// old roaming server to VSPS_VERSION_FIRST_NUMBER_4. 
			// For the roaming profiles managed by new roaming 6.0 server, we don't need to upgrade 
			// the version number. They will always have latest version number (VSPS_VERSION_FIRST_NUMBER)
		//if ( VSPS_VERSION_FIRST_NUMBER_4 > m_dwPSFirstVersionNumber )
		
		//If the profile version is lower than the latest version, update the 
		//profile version to the latest version number.
		if ( VSPS_VERSION_FIRST_NUMBER > m_dwPSFirstVersionNumber )
		{
			if ( 1 == m_nPasswordProvided )
			{
				//m_dwPSFirstVersionNumber		=	VSPS_VERSION_FIRST_NUMBER_4;
				//If the profile version is lower than the latest version, update the 
				//profile version to the latest version number.				
				m_dwPSFirstVersionNumber		=	VSPS_VERSION_FIRST_NUMBER;
				m_dwProtectedInformationChanged = 1;


					//	update the version number and set the flag for the plain text section
				m_dwPSSecondVersionNumber		=	VSPS_VERSION_SECOND_NUMBER;
				m_dwPlainTextInformationChanged = 1;

					//	all these things use the octet strings. so these things
					//	should be re-encoded.
				m_dwCertificateInformationChanged			=	1;	
				m_dwPlainTextApplicationInformationChanged	=	1;
				m_dwPrivateKeysChanged						=	1;
				m_dwProtectedApplicationInformationChanged	=	1;
				m_dwInformationBlobChanged					=	1;
			}
		}	//	end		if ( VSPS_VERSION_FIRST_NUMBER != m_dwPSFirstVersionNumber )

		if ( VSPS_VERSION_SECOND_NUMBER > m_dwPSSecondVersionNumber )
		{
				//	update the version number and set the flag for the plain text section
			m_dwPSSecondVersionNumber		=	VSPS_VERSION_SECOND_NUMBER;
			m_dwPlainTextInformationChanged = 1;
		
				//	all these things use the octet strings. so these things
				//	should be re-encoded.
			m_dwCertificateInformationChanged			=	1;	
			m_dwPlainTextApplicationInformationChanged	=	1;
		}


		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)1

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::BeginWrite


_VS_LONG	CProtectedStorage::EndWrite ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	BOOL					bResult				=	FALSE;

	_VS_LONG				lPreviousCount		=	9999;
	
//	_VS_DWORD				dwNumberOfReadProcesses		=	9999;
//	_VS_DWORD				dwNumberOfWriteprocesses	=	9999;

	while (1)
	{
		VS_CHECK_IF_INITIALIZED

		if ( BEGIN_WRITE_CALLED == m_dwBeginWriteCalled )
		{
			hResult =	m_ResetWritePID ();
			VS_CHECK_HRESULT

			hResult =	m_UpdateStorageFileIfNecessary ();
			VS_CHECK_HRESULT

				//	reset the begin write flag
			m_dwBeginWriteCalled	=	0;

					//	release the write semaphore
			bResult =	::ReleaseSemaphore
						(
							m_hWriteSemaphore,
							1,
							&lPreviousCount
						);
			VS_CHECK_BRESULT

/*			hResult =	::WaitForSingleObject
						(
							m_hReadMutex,
							m_dwWaitForSingleObjectTimeOut
						);
			VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT

			hResult =	m_CleanPIDList
						(
							&dwNumberOfReadProcesses,
							&dwNumberOfWriteprocesses
						);
			VS_CHECK_HRESULT

				//	reset the begin write flag
			m_dwBeginWriteCalled	=	0;

			hResult =	m_UpdateStorageFileIfNecessary ();
			VS_CHECK_HRESULT

						//	release the read mutex.
			bResult =	::ReleaseMutex
						(
							m_hReadMutex
						);
			VS_CHECK_BRESULT
*/
		}
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::EndWrite ()


_VS_LONG	CProtectedStorage::UpgradeReadToWrite ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

//	_VS_DWORD				dwResult			=	9999;

	_VS_DWORD				dwNumberOfReadProcesses		=	9999;
	_VS_DWORD				dwNumberOfWriteprocesses	=	9999;

	BOOL					bResult				=	FALSE;

	while (1)
	{
		VS_CHECK_IF_INITIALIZED

//		VS_GET_WAIT_FOR_SINGLE_OBJECT_TIMEOUT

		hResult =	::WaitForSingleObject
					(
						m_hReadMutex,
						m_dwWaitForSingleObjectTimeOut
					);
		VS_CHECK_RETURN_WAIT_FOR_SINGLE_OBJECT

		hResult =	m_CleanPIDList
					(
						&dwNumberOfReadProcesses,
						&dwNumberOfWriteprocesses
					);
		VS_CHECK_HRESULT

		if ( 1 == dwNumberOfReadProcesses )
		{
			hResult =	m_DeleteFromPIDList ( &dwNumberOfReadProcesses );
			VS_CHECK_HRESULT

			hResult =	m_SetWritePID ();
			VS_CHECK_HRESULT
		}

		m_dwBeginReadCalled		=	0;
		m_dwBeginWriteCalled	=	BEGIN_WRITE_CALLED;

//
//	Anand		May 03, 2001
//
//	At this point the profile contents are already read in the data strucutres.
//	While doing so the version of the protected and the plain text portions
//	of the profile was taken into account.
//
//	while writing the profile we now have to upgrade the profile. The plain-text portion
//	of the profile will definitely be upgraded but the protected portion of the profile
//	will be upgraded only if the password is provided.
//


			// upgrade the version number for the local profiles and roaming profiles managed by
			// old roaming server to VSPS_VERSION_FIRST_NUMBER_4. 
			// For the roaming profiles managed by new roaming 6.0 server, we don't need to upgrade 
			// the version number. They will always have latest version number (VSPS_VERSION_FIRST_NUMBER)
		//if ( VSPS_VERSION_FIRST_NUMBER_4 > m_dwPSFirstVersionNumber )
		
		//If the profile version is lower than the latest version, update the 
		//profile version to the latest version number.
		if ( VSPS_VERSION_FIRST_NUMBER > m_dwPSFirstVersionNumber )		
		{
			if ( 1 == m_nPasswordProvided )
			{
				//m_dwPSFirstVersionNumber		=	VSPS_VERSION_FIRST_NUMBER_4;
				
				//If the profile version is lower than the latest version, update the 
				//profile version to the latest version number.
				m_dwPSFirstVersionNumber		=	VSPS_VERSION_FIRST_NUMBER;
								
				m_dwProtectedInformationChanged = 1;

					//	update the version number and set the flag for the plain text section
				m_dwPSSecondVersionNumber		=	VSPS_VERSION_SECOND_NUMBER;
				m_dwPlainTextInformationChanged = 1;

					//	all these things use the octet strings. so these things
					//	should be re-encoded.
				m_dwCertificateInformationChanged			=	1;	
				m_dwPlainTextApplicationInformationChanged	=	1;
				m_dwPrivateKeysChanged						=	1;
				m_dwProtectedApplicationInformationChanged	=	1;
				m_dwInformationBlobChanged					=	1;
			}
		}	//	end		if ( VSPS_VERSION_FIRST_NUMBER != m_dwPSFirstVersionNumber )

		if ( VSPS_VERSION_SECOND_NUMBER > m_dwPSSecondVersionNumber )
		{
				//	update the version number and set the flag for the plain text section
			m_dwPSSecondVersionNumber		=	VSPS_VERSION_SECOND_NUMBER;
			m_dwPlainTextInformationChanged = 1;
		
				//	all these things use the octet strings. so these things
				//	should be re-encoded.
			m_dwCertificateInformationChanged			=	1;	
			m_dwPlainTextApplicationInformationChanged	=	1;
		}

					//	release the read mutex.
		bResult =	::ReleaseMutex
					(
						m_hReadMutex
					);
		VS_CHECK_BRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::UpgradeReadToWrite ()


_VS_LONG	CProtectedStorage::ResetPassword
(
	const _VS_CHAR*		i_cszOldPassword,
	const _VS_CHAR*		i_cszNewPassword
)
{
	_VS_LONG				hResult						=	E_VS_FAIL;

	while (1)
	{
//		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		VS_CHECK_IF_BEGIN_WRITE_CALLED

					//	check the old password
		hResult =	m_CheckPassword
					(
						i_cszOldPassword
					);
		VS_CHECK_HRESULT

					//	hash the new password
		hResult =	m_HashData
					(
						(const _VS_BYTE*) i_cszNewPassword,
						(const _VS_DWORD) (_VS_strlenW (i_cszNewPassword) + 1) * sizeof (_VS_CHAR),
						&m_pbytePasswordHash,
						&m_dwPasswordHashLen
					);
		VS_CHECK_HRESULT

					//	update the time stamp
		time ( &m_longTimePasswordProvided );

					//	since the password is changed the encrypted data needs to be encrypted
					//	with new password.
					//	this flag will indiacate that the protected information from the
					//	protected storage is changed.
		m_dwProtectedInformationChanged	=	1;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::ResetPassword


_VS_LONG	CProtectedStorage::CheckIfPSChangedAfterInitialization
(
	_VS_DWORD*			o_pnPSChanged
)
{
	_VS_LONG				hResult						=	E_FAIL;

	while (1)
	{
		VS_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED
		
		VS_CHECK_INPUT_POINTER_FOR_NULL (o_pnPSChanged)

		if ( PS_CHANGED_AFTER_INITIALIZED == m_dwPSChangedAfterInitialized )
		{
			*o_pnPSChanged =	1;
		}
		else
		{
			*o_pnPSChanged =	0;
		}

		hResult =	VS_SUCCESS;
		break;
	}

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::CheckIfPSChangedAfterInitialization

_VS_LONG	CProtectedStorage::ResetChangedAfterInitializationFlag ()
{
	m_dwPSChangedAfterInitialized =	0;

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::ResetChangedAfterInitializationFlag ()


_VS_LONG	CProtectedStorage::UpdatePasswordTimeout
(
	const	_VS_DWORD	i_ncPasswordTimeOutInMinutes
)
{
	HRESULT						hResult						=	E_FAIL;

	while (1)
	{
		VS_CHECK_AND_UPDATE_PASSWORD_TIMEOUT
		VS_CHECK_IF_INITIALIZED

		m_dwPasswordTimeOutIntervalInSeconds =	i_ncPasswordTimeOutInMinutes * 60;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::UpdatePasswordTimeout ()
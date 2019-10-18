///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	PrivateFunctions.cpp								 //
//																			 //
//	Description		:	The file contains implementation for some private	 //
//						class functions.									 //
//																			 //
//	Date			:	Sept 13, 1999										 //
//																			 //
//	Author			:	Anand Abhyankar										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

#include "ProtectedStorage.h"
#include "comdef.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_CheckPassword
//
//	Parameters
//		const _VS_CHAR*		i_pcszPassword	:	The password which is used to protect information
//												in the storage
//
//	Return Values	:
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_CheckPassword
(
	const _VS_CHAR*		i_pcszPassword
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_VS_BYTE*				pbytePasswordHash	=	NULL;
	_VS_DWORD				dwPasswordHashLen	=	0;

	_VS_DWORD				dwMemCmp			=	999;

	while (1)
	{
		if ( NULL != i_pcszPassword )
		{
					//	hash the password
			hResult =	m_HashData
						(
							(const _VS_BYTE*) i_pcszPassword,
							(const _VS_DWORD) (_VS_strlenW (i_pcszPassword) + 1) * sizeof (_VS_CHAR),
							&pbytePasswordHash,
							&dwPasswordHashLen
						);
			VS_CHECK_HRESULT

						//	compare the hash of the password (entered) with the
						//	hash of the password stored as a private member
			dwMemCmp =	_VS_memcmp
						(
							pbytePasswordHash,
							m_pbytePasswordHash,
							dwPasswordHashLen
						);
			if ( 0 != dwMemCmp )
			{
					//	the password is incorrect
				hResult =	E_VS_BAD_PASSWORD;
				break;
			}

			/***************************************************
				TBD	-	destroy the password string. always
						store password in form of its hash.
			***************************************************/


/*			if ( 0 == m_dwPasswordTimeOutIntervalInSeconds )
			{
				m_dwPasswordTimeOutAfterOneFunction =	1;
			}*/
		}	//	end		if ( NULL != szPassword )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY (pbytePasswordHash)

	return	hResult;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodeProtectedStorage
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will decode start decoding the entire protected storege.
//						structures containing the The plain text data and the protected data will be 
//						created.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodeProtectedStorage ()
{
	_VS_LONG			hResult				=	E_VS_FAIL;

	_DERTree*			pstructDERTreeEntireStorage;

	while (1)
	{
			//	copy the entire storage into a temp collection
		CBaseDERCollection	CbdcEntireStorage (m_dwEntireStorageSize, m_pbyteEntireStorage);

		m_pCbdhEntireStorage =	new ( CBaseDERHierarchy ) ( CbdcEntireStorage );
		VS_CHECK_ALLOCATED_MEMORY (m_pCbdhEntireStorage)

		if ( 0 != m_pCbdhEntireStorage -> dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}

		pstructDERTreeEntireStorage =	&(m_pCbdhEntireStorage -> m_DERTree);
		VS_CHECK_TYPE (SEQUENCE, pstructDERTreeEntireStorage)

/*			//	copy the encoded information into a temp sequence
		CSequence		CsqEntireStorage
						(
							((pstructDERTreeEntireStorage -> currentBaseDER) -> cbData),
							((pstructDERTreeEntireStorage -> currentBaseDER) -> pbData)
						);

			//	copy the encoded information in the m_structASN.CSeqProtectedStorage
		m_structASN.CSeqProtectedStorage =	CsqEntireStorage;
*/
			//	declare a pointer to CSequence
		CSequence*	pCsqEntireStorage;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqEntireStorage = (CSequence*) pstructDERTreeEntireStorage -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqProtectedStorage =	*pCsqEntireStorage;

			//	this will point to the plain text information
		m_pstructDERTreePlainTextInformation =	pstructDERTreeEntireStorage -> rightDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreePlainTextInformation)

			//	declare a pointer to CSequence
		CSequence*	pCsqPlainTextInformation;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqPlainTextInformation = (CSequence*) m_pstructDERTreePlainTextInformation -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqPlainTextInformation =	*pCsqPlainTextInformation;

			//	this will point to the protected information
		m_pstructDERTreeEncryptedProtectedInformation =	m_pstructDERTreePlainTextInformation -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreeEncryptedProtectedInformation)

			//	declare a pointer to CSequence
		CSequence*	pCsqEncryptedProtectedInformation;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqEncryptedProtectedInformation = (CSequence*) m_pstructDERTreeEncryptedProtectedInformation -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqEncryptedProtectedInformation =	*pCsqEncryptedProtectedInformation;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodeProtectedStorage ()

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodePlainTextData
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will decode all the plain text data of the protected storage.
//						The plain text data includes:
//							VeriSign constant string
//							Protected Storage Version number
//							PTA version number
//							Password Strength
//							Certificates along with the associated preferences
//							Plain Text Applications along with the associated preferences
//
//						It will also extract the encoded information from teh structure
//						m_pstructDERTreePlainTextInformation and put it in the sequence
//						m_structASN.CSeqPlainTextInformation. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodePlainTextData ()
{
	_VS_LONG			hResult			=	E_VS_FAIL;

	_DERTree*			pstructDERTreeCurrent;

	_DERTree*			pstructDERTreePSVersion;
	_DERTree*			pstructDERTreePTAVersion;

	_DWORD				dwTemp;

	while (1)
	{
/*				//	extract the encoded information from the structure and store it in a temp sequence
		CSequence			CsqPlainTextInformation
							(
								((m_pstructDERTreePlainTextInformation -> currentBaseDER) -> cbData),
								((m_pstructDERTreePlainTextInformation -> currentBaseDER) -> pbData)
							);

			//	Put the information in the member variable SEQUENCE
		m_structASN.CSeqPlainTextInformation =	CsqPlainTextInformation;
*/

/*
//This portion was placed in m_DecodeProtectedStorage
			//	declare a pointer to CSequence
		CSequence*	pCsqPlainTextInformation;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqPlainTextInformation = (CSequence*) m_pstructDERTreePlainTextInformation -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqPlainTextInformation =	*pCsqPlainTextInformation;
*/

			//	set the changed flag to 0
		m_dwPlainTextInformationChanged = 0;

				//	This will point to the VeriSign constant string
		pstructDERTreeCurrent =	m_pstructDERTreePlainTextInformation -> rightDERTree;
		VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrent)

		VS_FREE_MEMORY(m_pbyteVeriSignConstant)
		VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pbyteVeriSignConstant, pstructDERTreeCurrent, dwTemp)

				//	This will point to the SEQUENCE containing the Protected Storage version number
		pstructDERTreePSVersion =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, pstructDERTreePSVersion)

				//	This will point to the first Universal Integer for the PS version number
				//	copy it into the member variable
		pstructDERTreeCurrent =	pstructDERTreePSVersion -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPSFirstVersionNumber, pstructDERTreeCurrent)

				//	do the same for the remaining 3 Universal Integers for the PS version number
		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPSSecondVersionNumber, pstructDERTreeCurrent)

		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPSThirdVersionNumber, pstructDERTreeCurrent)

		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPSFourthVersionNumber, pstructDERTreeCurrent)

				//	This will point to the SEQUENCE containing the PTA version number
		pstructDERTreePTAVersion =	pstructDERTreePSVersion -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, pstructDERTreePTAVersion)

				//	This will point to the first Universal Integer for the PTA version number
				//	copy it into the member variable
		pstructDERTreeCurrent =	pstructDERTreePTAVersion -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPTAFirstVersionNumber, pstructDERTreeCurrent)

				//	do the same for the remaining 3 Universal Integers for the PTA version number
		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPTASecondVersionNumber, pstructDERTreeCurrent)

		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPTAThirdVersionNumber, pstructDERTreeCurrent)

		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPTAFourthVersionNumber, pstructDERTreeCurrent)

				//	This will point to the Password strength
		pstructDERTreeCurrent =	pstructDERTreePTAVersion -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwPasswordStrength, pstructDERTreeCurrent)

/*
				//	This will point to the number of certificates
		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (m_dwNumberOfCertificates, pstructDERTreeCurrent)

				//	This will point ot the SEQUENCE containing the number of applications
		pstructDERTreeNumberOfApplication =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, pstructDERTreeNumberOfApplication)

				//	this will point to the number of plain text applications
		pstructDERTreeCurrent =	pstructDERTreeNumberOfApplication -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (m_dwNumberOfPlainTextApplications, pstructDERTreeCurrent)

				//	this will point to the number of protected applications
		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (m_dwNumberOfProtectedApplications, pstructDERTreeCurrent)

				//	This will point to the number of private keys
		pstructDERTreeCurrent =	pstructDERTreeNumberOfApplication -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (m_dwNumberOfPrivateKeys, pstructDERTreeCurrent)

				//	This will point to the number of information blobs
		pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (m_dwNumberOfInformationBlobs, pstructDERTreeCurrent)
*/

				//	This will point to the SEQUENCE containing the certificates and the associated preferences
		m_pstructDERTreeCertificates =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreeCertificates)

				//	This funciton will decode the contents of the SEQUENCE containing the certificates and the associated preferences
		hResult =	m_DecodeCertificateInformation ();
		VS_CHECK_HRESULT

				//	This will point to the SEQUENCE containing the plain text applications and the associated preferences
		m_pstructDERTreePlainTextApplication = m_pstructDERTreeCertificates -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreePlainTextApplication)

				//	This function will decode the contents of the SEQUENCE containing the plain text applications and the associated preferences
		hResult =	m_DecodePlainTextApplicationInformation ();
		VS_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}

	return	hResult;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodeCertificateInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take the structure m_pstructDERTreeCertificates
//						and decode the certificate blobs and the associated preferences from it
//						and put it in the structure array m_pstructCertificateInformation
//
//						It will also extract the encoded information from teh structure
//						m_pstructDERTreeCertificates and put it in the sequence
//						m_structASN.CSeqCertificateInformation. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodeCertificateInformation ()
{
	_VS_LONG			hResult			=	E_VS_FAIL;

	_DERTree*			pstructDERTreeCurrent;
	_DERTree*			pstructDERTreeCurrentPreferenceName;
	_DERTree*			pstructDERTreeCurrentPreferenceData;
	_DERTree*			pstructDERTreePreferences;
	_DERTree*			pstructDERTreeCurrentPreference;
	_DERTree*			pstructDERTreeNumberOfPreferences;

	int					i, j;
	
	while (1)
	{
/*
				//	Extract the encoded information from the structure and put it in a temp SEQUENCE
		CSequence			CsqCertificates
							(
								((m_pstructDERTreeCertificates -> currentBaseDER) -> cbData),
								((m_pstructDERTreeCertificates -> currentBaseDER) -> pbData)
							);

				//	Put the infrmation in the member variable SEQUENCE
		m_structASN.CSeqCertificateInformation =	CsqCertificates;
*/
			//	declare a pointer to CSequence
		CSequence*	pCsqCertificates;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqCertificates = (CSequence*) m_pstructDERTreeCertificates -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqCertificateInformation =	*pCsqCertificates;

				//	Initialized the changed flag to 0
		m_dwCertificateInformationChanged =	0;

		pstructDERTreeCurrent = m_pstructDERTreeCertificates -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwNumberOfCertificates, pstructDERTreeCurrent)


		if ( 0 < m_dwNumberOfCertificates )
		{
						//	make sure that the certificate sequence exists

				//	allocate the structures which store the pointers to the certificates and the associated preferences
			m_pstructCertificateInformation =	(VSPS_CertificateInformation*) m_VS_HeapAlloc
												(
													m_dwNumberOfCertificates * sizeof (VSPS_CertificateInformation)
												);
			VS_CHECK_ALLOCATED_MEMORY(m_pstructCertificateInformation)

				//	this will point to the certificate blob
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> rightDERTree;

				//	for all certificates
			for ( i = 0; i < (int) m_dwNumberOfCertificates; i++ )
			{
				_DERTree*		pstructDERTreeCertificateBlob;
				_VS_DWORD		dwNumberOfPreferences			=	0;

					//	make sure that the element is a sequence
				VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)

					//	this will point to the certificate blob
				pstructDERTreeCertificateBlob = pstructDERTreeCurrent -> rightDERTree;

					//	make sure its an octet string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCertificateBlob)

					//	copy the certificate blob into the structure
				VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructCertificateInformation[i].pbyteCertificateBlob, pstructDERTreeCertificateBlob, m_pstructCertificateInformation[i].dwCertificateBlobLength)

					//	this will point to the number of preferences
				pstructDERTreeNumberOfPreferences =	pstructDERTreeCertificateBlob -> nextDERTree;
				VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeNumberOfPreferences)
				VS_CREATE_INTEGER_FROM_STRUCT (&dwNumberOfPreferences, pstructDERTreeNumberOfPreferences)

				m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences =	dwNumberOfPreferences;

				if ( 0 < m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences )
				{
							//	make sure that the preferences exist

								//	allocate memory for the 1st dimension of the preference name array
					m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName =	(_BYTE**) m_VS_HeapAlloc
																							(
																								m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences * sizeof (_BYTE*)
																							);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName)

								//	allocate memory for the 1st dimension of the perference data array
					m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData =	(_BYTE**) m_VS_HeapAlloc
																							(
																								m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences * sizeof (_BYTE*)
																							);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData)

								//	allocate memory for the preference name length array
					m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
																							(
																								m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences * sizeof (_DWORD)
																							);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength)

								//	allocate memory for the preference data length array
					m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
																							(
																								m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences * sizeof (_DWORD)
																							);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength)

							//	this will point to the SEQUENCE of the certificate preferences
					pstructDERTreePreferences =	pstructDERTreeNumberOfPreferences -> nextDERTree;
					VS_CHECK_TYPE (SEQUENCE, pstructDERTreePreferences)

							//this will point to the SEQUENCE containing a particuar preference
					pstructDERTreeCurrentPreference =	pstructDERTreePreferences -> rightDERTree;
					VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrentPreference)

					for ( j = 0; j < (int) m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences; j ++ )
					{
						pstructDERTreeCurrentPreferenceName =	pstructDERTreeCurrentPreference -> rightDERTree;
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrentPreferenceName)
						pstructDERTreeCurrentPreferenceData =	pstructDERTreeCurrentPreferenceName -> nextDERTree;
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrentPreferenceData)

							//	copy the preference name and length into the structure
						VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName[j], pstructDERTreeCurrentPreferenceName, m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength[j])

							//	copy the preference data and length into the structure
						VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData[j], pstructDERTreeCurrentPreferenceData, m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength[j])

							//	this will point to the SEQUENCE contianing the next preference
						pstructDERTreeCurrentPreference =	pstructDERTreeCurrentPreference -> nextDERTree;
						VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrentPreference)
					}	//	end		for ( j = 0; j < m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences; j ++ )
					if ( j < (int) m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences )
					{
							//	this means that the a 'break' occured in the for loop.
							//	in this case the error value is already set to hResult. so break agian
						break;
					}
				}	//	end		if ( 0 < m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences )

					//	This will point to the next certificate
				pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			}	//	end		for ( i = 0; i < m_dwNumberOfCertificates; i++ )
			if ( i < (int) m_dwNumberOfCertificates )
			{
					//	this means that the a 'break' occured in the for loop.
					//	in this case the error value is already set to hResult. so break agian
				break;
			}
		}	//	end		if ( 0 < m_dwNumberOfCertificates )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodeCertificateInformation ()

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodePlainTextApplicationInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take the structure m_pstructDERTreePlainTextApplication
//						and decode the application name, host and the associated preferences from it
//						and put it in the structure array m_pstructPlainTextApplicationInformation.
//
//						It will also extract the encoded information from teh structure
//						m_pstructDERTreePlainTextApplication and put it in the sequence
//						m_structASN.CSeqPlainTextApplicationInformation. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodePlainTextApplicationInformation ()
{
	_VS_LONG			hResult			=	E_VS_FAIL;

	_DERTree*			pstructDERTreeCurrent;
	_DERTree*			pstructDERTreeCurrentPreferenceName;
	_DERTree*			pstructDERTreeCurrentPreferenceData;
	_DERTree*			pstructDERTreePreferences;
	_DERTree*			pstructDERTreeCurrentPreference;
	_DERTree*			pstructDERTreeNumberOfPreferences;

	int					i, j;

	while (1)
	{
/*				//	Extract the encoded information from the structure and put it in a temp SEQUENCE
		CSequence			CsqPlainTextApplications
							(
								((m_pstructDERTreePlainTextApplication -> currentBaseDER) -> cbData),
								((m_pstructDERTreePlainTextApplication -> currentBaseDER) -> pbData)
							);

				//	Put the infrmation in the member variable SEQUENCE
		m_structASN.CSeqPlainTextApplicationInformation =	CsqPlainTextApplications;
*/
			//	declare a pointer to CSequence
		CSequence*			pCsqPlainTextApplications;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqPlainTextApplications = (CSequence*) m_pstructDERTreePlainTextApplication -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqPlainTextApplicationInformation =	*pCsqPlainTextApplications;

				//	Initialized the changed flag to 0
		m_dwPlainTextApplicationInformationChanged =	0;

		pstructDERTreeCurrent =	m_pstructDERTreePlainTextApplication -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwNumberOfPlainTextApplications, pstructDERTreeCurrent)

		if ( 0 < m_dwNumberOfPlainTextApplications )
		{
					//	make sure that the application sequence exists

				//	allocate the structures which store the pointers to the applications and the associated preferences
			m_pstructPlainTextApplicationInformation =	(VSPS_ApplicationInformation*) m_VS_HeapAlloc
														(
															m_dwNumberOfPlainTextApplications * sizeof (VSPS_ApplicationInformation)
														);
			VS_CHECK_ALLOCATED_MEMORY(m_pstructPlainTextApplicationInformation)

				//	this will point to the application name blob
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> rightDERTree;

				//	for all applications
			for ( i = 0; i < (int) m_dwNumberOfPlainTextApplications; i++ )
			{
				_DERTree*		pstructDERTreeApplicationName;
				_DERTree*		pstructDERTreeApplicationHost;

				_VS_DWORD		dwNumberOfPreferences			=	0;

					//	make sure that the element is a sequence
				VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)

					//	this will point to the application name
				pstructDERTreeApplicationName = pstructDERTreeCurrent -> rightDERTree;

					//	make sure its a printable string string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationName)

					//	copy the name and the length into the structure
				VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructPlainTextApplicationInformation[i].pbyteApplicationName, pstructDERTreeApplicationName, m_pstructPlainTextApplicationInformation[i].dwApplicationNameLength)

					//	this will point to the application host
				pstructDERTreeApplicationHost =	pstructDERTreeApplicationName -> nextDERTree;

					//	make sure its a printable string string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationHost)

					//	copy the host and the length into the structure
				VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructPlainTextApplicationInformation[i].pbyteApplicationHost, pstructDERTreeApplicationHost, m_pstructPlainTextApplicationInformation[i].dwApplicationHostLength)

					//	this will point to the number of preferences
				pstructDERTreeNumberOfPreferences =	pstructDERTreeApplicationHost -> nextDERTree;
				VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeNumberOfPreferences)
				VS_CREATE_INTEGER_FROM_STRUCT (&dwNumberOfPreferences, pstructDERTreeNumberOfPreferences)

				m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences =	dwNumberOfPreferences;

				if ( 0 < m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences )
				{
							//	make sure that the preferences exists

								//	allocate memory for the 1st dimension of the preference name array
					m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceName =	(_BYTE**) m_VS_HeapAlloc
																									(
																										m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_BYTE*)
																									);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceName)

								//	allocate memory for the 1st dimension of the perference data array
					m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceData =	(_BYTE**) m_VS_HeapAlloc
																									(
																										m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_BYTE*)
																									);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceData)

								//	allocate memory for the preference name length array
					m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
																										(
																											m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_DWORD)
																										);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceNameLength)

								//	allocate memory for the preference data length array
					m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
																										(
																											m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_DWORD)
																										);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceDataLength)

						//	this will point to the SEQUENCE of the application preferences
					pstructDERTreePreferences =	pstructDERTreeNumberOfPreferences -> nextDERTree;
					VS_CHECK_TYPE (SEQUENCE, pstructDERTreePreferences)

						//	this will point to the SEQUENCE containing the first preference
					pstructDERTreeCurrentPreference =	pstructDERTreePreferences -> rightDERTree;
					VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrentPreference)

					for ( j = 0; j < (int) m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences; j ++ )
					{
						pstructDERTreeCurrentPreferenceName =	pstructDERTreeCurrentPreference -> rightDERTree;
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrentPreferenceName)
						pstructDERTreeCurrentPreferenceData =	pstructDERTreeCurrentPreferenceName -> nextDERTree;
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrentPreferenceData)

							//	copy the preference name and length into the structure
						VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceName[j], pstructDERTreeCurrentPreferenceName, m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceNameLength[j])

							//	copy the preference data and length into the structure
						VS_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceData[j], pstructDERTreeCurrentPreferenceData, m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceDataLength[j])

						pstructDERTreeCurrentPreference =	pstructDERTreeCurrentPreference -> nextDERTree;
						VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrentPreference)
					}	//	end		for ( j = 0; j < m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences; j ++ )
					if ( j < (int) m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences )
					{
							//	this means that the a 'break' occured in the for loop.
							//	in this case the error value is already set to hResult. so break agian
						break;
					}
				}	//	end		if ( 0 < m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences )

				// assign default values to readok + writeok. not used for plaintext.
				m_pstructPlainTextApplicationInformation[i].pbyteApplicationCreatorWildCard = NULL;
				m_pstructPlainTextApplicationInformation[i].dwApplicationCreatorWildCardLength = 0;
				m_pstructPlainTextApplicationInformation[i].dwNumOfApplicationReadOKDomains = 0;
				m_pstructPlainTextApplicationInformation[i].pbyteApplicationReadOKDomains = NULL;
				m_pstructPlainTextApplicationInformation[i].dwApplicationReadOKDomainsLength = 0;
				m_pstructPlainTextApplicationInformation[i].dwNumOfApplicationWriteOKDomains = 0;
				m_pstructPlainTextApplicationInformation[i].pbyteApplicationWriteOKDomains = NULL;
				m_pstructPlainTextApplicationInformation[i].dwApplicationWriteOKDomainsLength = 0;

				//	this will point to the next application
				pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			}	//	end		for ( i = 0; i < m_dwNumberOfPlainTextApplications; i++ )
			if ( i < (int) m_dwNumberOfPlainTextApplications )
			{
					//	this means that the a 'break' occured in the for loop.
					//	in this case the error value is already set to hResult. so break agian
				break;
			}
		}	//	end		if ( 0 < m_dwNumberOfPlainTextApplications )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodePlainTextApplicationInformation ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodeProtectedData
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will decode all the protected data of the protected storage.
//						The protected data includes:
//							VeriSign constant string
//							Private keys
//							Protected Applications along with the associated preferences
//							Information Blobs
//
//						It will also extract the encrypted encoded information from teh structure
//						m_pstructDERTreeEncryptedProtectedInformation, decrypt it and put it in the sequence
//						m_structASN.CSeqProtectedInformation. The encrypted informaiton is put it the sequence
//						m_structASN.CSeqEncryptedProtectedInformation. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodeProtectedData ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_DERTree*				pstructDERTreeCurrent;
	_DERTree*				pstructDERTreeSaltIterationCount;
	_DERTree*				pstructDERTreeSalt;
	_DERTree*				pstructDERTreeIterationCount;

	_DWORD					dwTemp;

//	return	0;

	while (1)
	{
/*
//This portion was placed in m_DecodeProtectedStorage

			//	declare a pointer to CSequence
		CSequence*	pCsqEncryptedProtectedInformation;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqEncryptedProtectedInformation = (CSequence*) m_pstructDERTreeEncryptedProtectedInformation -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqEncryptedProtectedInformation =	*pCsqEncryptedProtectedInformation;
*/

//		if ( VSPS_VERSION_FIRST_NUMBER == m_dwPSFirstVersionNumber )
		if ( VSPS_VERSION_FIRST_NUMBER_1 < m_dwPSFirstVersionNumber )
		{
			pstructDERTreeSaltIterationCount =	m_pstructDERTreeEncryptedProtectedInformation -> rightDERTree;
			VS_CHECK_TYPE (SEQUENCE, pstructDERTreeSaltIterationCount)

			pstructDERTreeSalt =	pstructDERTreeSaltIterationCount -> rightDERTree;
			VS_CHECK_TYPE(OCTET_STRING, pstructDERTreeSalt)

			VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pbyteSalt, pstructDERTreeSalt, m_dwSaltLen)

			pstructDERTreeIterationCount =	pstructDERTreeSalt -> nextDERTree;
			VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeIterationCount)
			VS_CREATE_INTEGER_FROM_STRUCT (&m_dwIterationCount, pstructDERTreeIterationCount)

			pstructDERTreeCurrent =	pstructDERTreeSaltIterationCount -> nextDERTree;
		}
		else
		{
			pstructDERTreeCurrent =	m_pstructDERTreeEncryptedProtectedInformation -> rightDERTree;
		}

		VS_CHECK_TYPE(OCTET_STRING, pstructDERTreeCurrent);

		m_dwEncryptedProtectedInformationLength =	(pstructDERTreeCurrent -> currentBaseDER) -> cbData;

		VS_FREE_MEMORY(m_pbyteEncryptedProtectedInformation)
//		m_pbyteEncryptedProtectedInformation	=	(pstructDERTreeCurrent -> currentBaseDER) -> pbData;
		VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT(m_pbyteEncryptedProtectedInformation, pstructDERTreeCurrent, m_dwEncryptedProtectedInformationLength)

		hResult =	m_DecryptProtectedData ();

		VS_FREE_MEMORY(m_pbyteEncryptedProtectedInformation)
		m_pbyteEncryptedProtectedInformation	=	NULL;
		m_dwEncryptedProtectedInformationLength	=	0;

		VS_CHECK_HRESULT

			//	copy the decrypted protected informaiton into a temp collection
		CBaseDERCollection	CbdcProtectedInformation (m_dwDecryptedProtectedInformationLength, m_pbyteDecryptedProtectedInformation);

		m_pCbdhProtectedInformation =	new ( CBaseDERHierarchy ) ( CbdcProtectedInformation );
		VS_CHECK_ALLOCATED_MEMORY (m_pCbdhProtectedInformation)

		if ( 0 != m_pCbdhProtectedInformation -> dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}

		m_pstructDERTreeProtectedInformation =	&(m_pCbdhProtectedInformation -> m_DERTree);
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreeProtectedInformation)

				//	put the decrypted information in the appropriate member sequence
			//	declare a pointer to CSequence
		CSequence*	pCsqProtectedInformation;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqProtectedInformation = (CSequence*) m_pstructDERTreeProtectedInformation -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqProtectedInformation =	*pCsqProtectedInformation;

			//	set the changed flags to 0
//		m_dwEncryptedProtectedInformationChanged	=	0;
		m_dwProtectedInformationChanged				=	0;

				//	This will point to the VeriSign constant string
		pstructDERTreeCurrent =	m_pstructDERTreeProtectedInformation -> rightDERTree;
		VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrent)

		VS_FREE_MEMORY(m_pbyteEncryptedVeriSignConstant)
		VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pbyteEncryptedVeriSignConstant, pstructDERTreeCurrent, dwTemp)

			//	check password over here

				//	This will point to the private key sequence
		m_pstructDERTreePrivateKeys =	pstructDERTreeCurrent -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreePrivateKeys)

			//	This funciton will decode the contents of the SEQUENCE containing the private keys
		hResult =	m_DecodePrivateKeyInformation ();
		VS_CHECK_HRESULT

				//	This will point to the protected application information
		m_pstructDERTreeProtectedApplication =	m_pstructDERTreePrivateKeys -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreeProtectedApplication)

				//	This funciton will decode the contents of the SEQUENCE containing the protected applications and the associated preferences
		hResult =	m_DecodeProtectedApplicationInformation ();
		VS_CHECK_HRESULT

				//	This will point to the information blobs
		m_pstructDERTreeInformationBlobs =	m_pstructDERTreeProtectedApplication -> nextDERTree;
		VS_CHECK_TYPE (SEQUENCE, m_pstructDERTreeInformationBlobs)

				//	This funciton will decode the contents of the SEQUENCE containing the information blobs
		hResult =	m_DecodeInformationBlobs ();
		VS_CHECK_HRESULT

		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodeProtectedData ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodePrivateKeyInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take the structure m_pstructDERTreePrivateKeys
//						and decode the private keys and the associated hash values from it
//						and put it in the structure array m_pstructPrivateKeyInformation
//
//						It will also extract the encoded information from teh structure
//						m_pstructDERTreePrivateKeys and put it in the sequence
//						m_structASN.CSeqPrivateKeys. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodePrivateKeyInformation ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_DERTree*				pstructDERTreeCurrent;

	int						i;
	_VS_DWORD dwPrivateKeyExportable;
	while (1)
	{
			//	declare a pointer to CSequence
		CSequence*	pCsqPrivateKeys;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqPrivateKeys = (CSequence*) m_pstructDERTreePrivateKeys -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqPrivateKeys =	*pCsqPrivateKeys;

				//	Initialized the changed flag to 0
		m_dwPrivateKeysChanged =	0;

				//	get the number of private keys
		pstructDERTreeCurrent = m_pstructDERTreePrivateKeys -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwNumberOfPrivateKeys, pstructDERTreeCurrent)

		if ( 0 < m_dwNumberOfPrivateKeys )
		{
						//	make sure that the private keys sequence exists

				//	allocate the structures which store the pointers to the private keys and the associated hash
			m_pstructPrivateKeyInformation =	(VSPS_PrivateKeyInformation*) m_VS_HeapAlloc
												(
													m_dwNumberOfPrivateKeys * sizeof (VSPS_PrivateKeyInformation)
												);
			VS_CHECK_ALLOCATED_MEMORY(m_pstructPrivateKeyInformation)

				//	this will point to the  sequence containing private key and associated hash
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> rightDERTree;

				//	for all private keys
			for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )
			{
				_DERTree*		pstructDERTreeAssociatedHash;
				_DERTree*		pstructDERTreePrivateKey;

				// Modified by - Infosys Technologies Ltd. 
				// Change Request - CR#21529
				// Description - Additional DERTree to store the private key exportable flag.
				// Date Modified - July 02, 2004
				// CR#21529 Begin
				_DERTree*		pstructDERTreePrivateKeyExportable;
				// CR#21529 - End

					//	make sure that the element is a sequence
				VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)

					//	this will point to the associated hash
				pstructDERTreeAssociatedHash = pstructDERTreeCurrent -> rightDERTree;

					//	make sure its an octet string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeAssociatedHash)

					//	copy the associated hash into the structure
				VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructPrivateKeyInformation[i].pbyteAssociatedHash, pstructDERTreeAssociatedHash, m_pstructPrivateKeyInformation[i].dwAssociatedHashLength)

					//	this will point to the private key blob
				pstructDERTreePrivateKey =	pstructDERTreeAssociatedHash -> nextDERTree;

					//	make sure its an octet string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreePrivateKey)

					//	copy the associated hash into the structure
				VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructPrivateKeyInformation[i].pbytePrivateKeyBlob, pstructDERTreePrivateKey, m_pstructPrivateKeyInformation[i].dwPrivateKeyBlobLength)

				// Modified by - Infosys Technologies Ltd. 
				// Change Request - CR#21529
				// Description - Additional DERTree to store the private key exportable flag.
				// CR#21529 Begin
				// Date Modified - July 02, 2004
				pstructDERTreePrivateKeyExportable =	pstructDERTreePrivateKey -> nextDERTree;
				// Check if the PrivateKeyExportable exportable flag is available.
				if (pstructDERTreePrivateKeyExportable)
				{
					VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreePrivateKeyExportable)
					VS_CREATE_INTEGER_FROM_STRUCT (&dwPrivateKeyExportable, pstructDERTreePrivateKeyExportable)
					m_pstructPrivateKeyInformation[i].dwPrivateKeyExportableFlag = dwPrivateKeyExportable;
				}
				//	This will point to the next sequence containing the private key and the associated hash
				pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
				// CR#21529 End
				
			}	//	end		for ( i = 0; i < (int) m_dwNumberOfPrivateKeys; i++ )

			if ( i < (int) m_dwNumberOfPrivateKeys )
			{
					//	this means that the a 'break' occured in the for loop.
					//	in this case the error value is already set to hResult. so break agian
				break;
			}
		}	//	end		if ( 0 < m_dwNumberOfPrivateKeys )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodePrivateKeyInformation ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodeProtectedApplicationInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take the structure m_pstructDERTreeProtectedApplication
//						and decode the application name, host and the associated preferences from it
//						and put it in the structure array m_pstructProtectedApplicationInformation.
//
//						It will also extract the encoded information from teh structure
//						m_pstructDERTreeProtectedApplication and put it in the sequence
//						m_structASN.CSeqProtectedApplicationInformation. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodeProtectedApplicationInformation ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_DERTree*				pstructDERTreeCurrent;
	_DERTree*				pstructDERTreeCurrentPreferenceName;
	_DERTree*				pstructDERTreeCurrentPreferenceData;
	_DERTree*				pstructDERTreePreferences;
	_DERTree*				pstructDERTreeCurrentPreference;
	_DERTree*				pstructDERTreeNumberOfPreferences;

	int						i, j;

	while (1)
	{
/*				//	Extract the encoded information from the structure and put it in a temp SEQUENCE
		CSequence			CsqProtectedApplications
							(
								((m_pstructDERTreeProtectedApplication -> currentBaseDER) -> cbData),
								((m_pstructDERTreeProtectedApplication -> currentBaseDER) -> pbData)
							);

				//	Put the infrmation in the member variable SEQUENCE
		m_structASN.CSeqProtectedApplicationInformation =	CsqProtectedApplications;
*/
			//	declare a pointer to CSequence
		CSequence*			pCsqProtectedApplications;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqProtectedApplications = (CSequence*) m_pstructDERTreeProtectedApplication -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqProtectedApplicationInformation =	*pCsqProtectedApplications;

				//	Initialized the changed flag to 0
		m_dwProtectedApplicationInformationChanged =	0;

		pstructDERTreeCurrent =	m_pstructDERTreeProtectedApplication -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwNumberOfProtectedApplications, pstructDERTreeCurrent)

		if ( 0 < m_dwNumberOfProtectedApplications )
		{
					//	make sure that the application sequence exists

				//	allocate the structures which store the pointers to the applications and the associated preferences
			m_pstructProtectedApplicationInformation =	(VSPS_ApplicationInformation*) m_VS_HeapAlloc
														(
															m_dwNumberOfProtectedApplications * sizeof (VSPS_ApplicationInformation)
														);
			VS_CHECK_ALLOCATED_MEMORY(m_pstructProtectedApplicationInformation)

				//	this will point to the application name blob
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> rightDERTree;

				//	for all applications
			for ( i = 0; i < (int) m_dwNumberOfProtectedApplications; i++ )
			{
				_DERTree*		pstructDERTreeApplicationName;
				_DERTree*		pstructDERTreeApplicationHost;
				_DERTree*		pstructDERTreeApplicationCreatorWildCard;
				_DERTree*		pstructDERTreeNumOfApplicationReadOKDomains;
				_DERTree*		pstructDERTreeApplicationReadOKDomains;
				_DERTree*		pstructDERTreeNumOfApplicationWriteOKDomains;
				_DERTree*		pstructDERTreeApplicationWriteOKDomains;

				_VS_DWORD		dwNumberOfPreferences			=	0;

					//	make sure that the element is a sequence
				VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)

					//	this will point to the application name
				pstructDERTreeApplicationName = pstructDERTreeCurrent -> rightDERTree;

					//	make sure its a printable string string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationName)

					//	copy the name and the length into the structure
				VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].pbyteApplicationName, pstructDERTreeApplicationName, m_pstructProtectedApplicationInformation[i].dwApplicationNameLength)

					//	this will point to the application host
				pstructDERTreeApplicationHost =	pstructDERTreeApplicationName -> nextDERTree;

					//	make sure its a printable string string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationHost)

					//	copy the host and the length into the structure
				VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].pbyteApplicationHost, pstructDERTreeApplicationHost, m_pstructProtectedApplicationInformation[i].dwApplicationHostLength)

				if (VSPS_VERSION_FIRST_NUMBER_3 < m_dwPSFirstVersionNumber)
				{

						//	this will point to the application creator wild card
					pstructDERTreeApplicationCreatorWildCard =	pstructDERTreeApplicationHost -> nextDERTree;

						//	make sure its a printable string string (byte blob)
					VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationCreatorWildCard)
	
						//	copy the host and the length into the structure
					VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].pbyteApplicationCreatorWildCard, pstructDERTreeApplicationCreatorWildCard, m_pstructProtectedApplicationInformation[i].dwApplicationCreatorWildCardLength)
	

					pstructDERTreeNumOfApplicationReadOKDomains = pstructDERTreeApplicationCreatorWildCard -> nextDERTree;
						//	this will point to the writeokdomains for this application.
						
					
					VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeNumOfApplicationReadOKDomains)
					VS_CREATE_INTEGER_FROM_STRUCT (&m_pstructProtectedApplicationInformation[i].dwNumOfApplicationReadOKDomains, pstructDERTreeNumOfApplicationReadOKDomains)
					
					if (m_pstructProtectedApplicationInformation[i].dwNumOfApplicationReadOKDomains > 0)
					{
						//	this will point to the readokdomains for this application.
						pstructDERTreeApplicationReadOKDomains = pstructDERTreeNumOfApplicationReadOKDomains -> nextDERTree;
						
							//	make sure the its a printable string string (byte blob)
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationReadOKDomains)
	
							//	copy the readokdomains and the length into the structure
						VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].pbyteApplicationReadOKDomains, pstructDERTreeApplicationReadOKDomains, m_pstructProtectedApplicationInformation[i].dwApplicationReadOKDomainsLength);


						pstructDERTreeNumOfApplicationWriteOKDomains = pstructDERTreeApplicationReadOKDomains -> nextDERTree;
						//	this will point to the num of writeokdomains for this application.
					}						
					else
					{
						pstructDERTreeNumOfApplicationWriteOKDomains = pstructDERTreeNumOfApplicationReadOKDomains -> nextDERTree -> nextDERTree;
					}

					VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeNumOfApplicationWriteOKDomains)
					VS_CREATE_INTEGER_FROM_STRUCT (&m_pstructProtectedApplicationInformation[i].dwNumOfApplicationWriteOKDomains, pstructDERTreeNumOfApplicationWriteOKDomains)

					if (m_pstructProtectedApplicationInformation[i].dwNumOfApplicationWriteOKDomains > 0)
					{					
						pstructDERTreeApplicationWriteOKDomains = pstructDERTreeNumOfApplicationWriteOKDomains -> nextDERTree;
						
							//	make sure that it is a printable string string (byte blob)
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeApplicationWriteOKDomains)	

							//	copy the writeokdomains and the length into the structure
						VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].pbyteApplicationWriteOKDomains, pstructDERTreeApplicationWriteOKDomains, m_pstructProtectedApplicationInformation[i].dwApplicationWriteOKDomainsLength);

							//	this will point to the number of preferences
						pstructDERTreeNumberOfPreferences =	pstructDERTreeApplicationWriteOKDomains -> nextDERTree;
					}
					else
					{
						pstructDERTreeNumberOfPreferences = pstructDERTreeNumOfApplicationWriteOKDomains -> nextDERTree -> nextDERTree;
					}
				}
				else 
				{
					VS_ALLOC_AND_BYTEBLOB_COPY (m_pstructProtectedApplicationInformation[i].pbyteApplicationCreatorWildCard, m_pstructProtectedApplicationInformation[i].pbyteApplicationHost, m_pstructProtectedApplicationInformation[i].dwApplicationHostLength)
					m_pstructProtectedApplicationInformation[i].dwApplicationCreatorWildCardLength = m_pstructProtectedApplicationInformation[i].dwApplicationHostLength;
					m_pstructProtectedApplicationInformation[i].dwNumOfApplicationReadOKDomains = 1;
					VS_ALLOC_AND_BYTEBLOB_COPY (m_pstructProtectedApplicationInformation[i].pbyteApplicationReadOKDomains, m_pstructProtectedApplicationInformation[i].pbyteApplicationHost, m_pstructProtectedApplicationInformation[i].dwApplicationHostLength)
					m_pstructProtectedApplicationInformation[i].dwApplicationReadOKDomainsLength = m_pstructProtectedApplicationInformation[i].dwApplicationHostLength;
					m_pstructProtectedApplicationInformation[i].dwNumOfApplicationWriteOKDomains = 1;
					VS_ALLOC_AND_BYTEBLOB_COPY (m_pstructProtectedApplicationInformation[i].pbyteApplicationWriteOKDomains, m_pstructProtectedApplicationInformation[i].pbyteApplicationHost, m_pstructProtectedApplicationInformation[i].dwApplicationHostLength)
					m_pstructProtectedApplicationInformation[i].dwApplicationWriteOKDomainsLength = m_pstructProtectedApplicationInformation[i].dwApplicationHostLength;

						//	this will point to the number of preferences
					pstructDERTreeNumberOfPreferences =	pstructDERTreeApplicationHost -> nextDERTree;
				}

				VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeNumberOfPreferences)
				VS_CREATE_INTEGER_FROM_STRUCT (&dwNumberOfPreferences, pstructDERTreeNumberOfPreferences)

				m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences =	dwNumberOfPreferences;

				if ( 0 < m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences )
				{
							//	make sure that the preferences exists

								//	allocate memory for the 1st dimension of the preference name array
					m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceName =	(_BYTE**) m_VS_HeapAlloc
																									(
																										m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_BYTE*)
																									);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceName)

								//	allocate memory for the 1st dimension of the perference data array
					m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceData =	(_BYTE**) m_VS_HeapAlloc
																									(
																										m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_BYTE*)
																									);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceData)

								//	allocate memory for the preference name length array
					m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceNameLength =	(_DWORD*) m_VS_HeapAlloc
																										(
																											m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_DWORD)
																										);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceNameLength)

								//	allocate memory for the preference data length array
					m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceDataLength =	(_DWORD*) m_VS_HeapAlloc
																										(
																											m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences * sizeof (_DWORD)
																										);
					VS_CHECK_ALLOCATED_MEMORY (m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceDataLength)

						//	this will point to the SEQUENCE of the application preferences
					pstructDERTreePreferences =	pstructDERTreeNumberOfPreferences -> nextDERTree;
					VS_CHECK_TYPE (SEQUENCE, pstructDERTreePreferences)

						//	this will point to the SEQUENCE contianing the first preference
					pstructDERTreeCurrentPreference =	pstructDERTreePreferences -> rightDERTree;
					VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrentPreference)

					for ( j = 0; j < (int) m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences; j ++ )
					{
						pstructDERTreeCurrentPreferenceName =	pstructDERTreeCurrentPreference -> rightDERTree;
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrentPreferenceName)
						pstructDERTreeCurrentPreferenceData =	pstructDERTreeCurrentPreferenceName -> nextDERTree;
						VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeCurrentPreferenceData)

							//	copy the preference name and length into the structure
						VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceName[j], pstructDERTreeCurrentPreferenceName, m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceNameLength[j])

							//	copy the preference data and length into the structure
						VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceData[j], pstructDERTreeCurrentPreferenceData, m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceDataLength[j])

							//	this will point to the next preference
						pstructDERTreeCurrentPreference =	pstructDERTreeCurrentPreference -> nextDERTree;
						VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrentPreference)
					}	//	end		for ( j = 0; j < m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences; j ++ )
					if ( j < (int) m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences )
					{
							//	this means that the a 'break' occured in the for loop.
							//	in this case the error value is already set to hResult. so break agian
						break;
					}
				}	//	end		if ( 0 < m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences )

					//	this will point to the next application
				pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			}	//	end		for ( i = 0; i < m_dwNumberOfProtectedApplications; i++ )
			if ( i < (int) m_dwNumberOfProtectedApplications )
			{
					//	this means that the a 'break' occured in the for loop.
					//	in this case the error value is already set to hResult. so break agian
				break;
			}
		}	//	end		if ( 0 < m_dwNumberOfProtectedApplications )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodeProtectedApplicationInformation ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecodeInformationBlobs
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take the structure m_pstructDERTreeInformationBlobs
//						and decode the information blob name and data from it
//						and put it in the structure array m_pstructInformationBlob
//
//						It will also extract the encoded information from teh structure
//						m_pstructDERTreeInformationBlobs and put it in the sequence
//						m_structASN.CSeqInformationBlobs. If the data remains unchanged
//						this will be used as is while encoding.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecodeInformationBlobs ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_DERTree*				pstructDERTreeCurrent;

	int						i;

	while (1)
	{
			//	declare a pointer to CSequence
		CSequence*	pCsqInformationBlobs;

			//	the data in the BaseDER structure pointer corresponds to the sequence.
			//	So asign that value to the sequence pointer declared above.
		pCsqInformationBlobs = (CSequence*) m_pstructDERTreeInformationBlobs -> currentBaseDER;

			//	copy the contents of the sequence declared above to the actual structure
		m_structASN.CSeqInformationBlobs =	*pCsqInformationBlobs;

				//	Initialized the changed flag to 0
		m_dwInformationBlobChanged =	0;

				//	get the number of infromation blobs
		pstructDERTreeCurrent = m_pstructDERTreeInformationBlobs -> rightDERTree;
		VS_CHECK_TYPE (UNIVERSAL_INTEGER, pstructDERTreeCurrent)
		VS_CREATE_INTEGER_FROM_STRUCT (&m_dwNumberOfInformationBlobs, pstructDERTreeCurrent)

		if ( 0 < m_dwNumberOfInformationBlobs )
		{
						//	make sure that the information blobs sequence exists

				//	allocate the structures which store the pointers to the information blobs
			m_pstructInformationBlob =	(VSPS_InformationBlob*) m_VS_HeapAlloc
										(
											m_dwNumberOfInformationBlobs * sizeof (VSPS_InformationBlob)
										);
			VS_CHECK_ALLOCATED_MEMORY(m_pstructInformationBlob)

				//	this will point to the  sequence containing information blob name and data
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)
			pstructDERTreeCurrent =	pstructDERTreeCurrent -> rightDERTree;

				//	for all information blobs
			for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )
			{
				_DERTree*		pstructDERTreeName;
				_DERTree*		pstructDERTreeData;

					//	make sure that the element is a sequence
				VS_CHECK_TYPE (SEQUENCE, pstructDERTreeCurrent)

					//	this will point to the information blob name
				pstructDERTreeName = pstructDERTreeCurrent -> rightDERTree;

					//	make sure its a printable string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeName)

					//	copy the information blob name into the structure
				VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructInformationBlob[i].pbyteInformationBlobName, pstructDERTreeName, m_pstructInformationBlob[i].dwInformationBlobNameLength)

					//	this will point to the information blob data
				pstructDERTreeData =	pstructDERTreeName -> nextDERTree;

					//	make sure its an octet string (byte blob)
				VS_CHECK_TYPE (OCTET_STRING, pstructDERTreeData)

					//	copy the information blob data into the structure
				VS_PROTECTED_CREATE_BYTEBLOB_FROM_STRUCT (m_pstructInformationBlob[i].pbyteInformationBlobData, pstructDERTreeData, m_pstructInformationBlob[i].dwInformationBlobDataLength)

					//	This will point to the next sequence containing the information blob name and data
				pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			}	//	end		for ( i = 0; i < (int) m_dwNumberOfInformationBlobs; i++ )

			if ( i < (int) m_dwNumberOfInformationBlobs )
			{
					//	this means that the a 'break' occured in the for loop.
					//	in this case the error value is already set to hResult. so break agian
				break;
			}
		}	//	end		if ( 0 < m_dwNumberOfInformationBlobs )

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecodeInformationBlobs ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodeProtectedStorage
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will encode the plain text information and 
//						the protected information into a sequence and copy
//						the encoded blob into the variable m_pbyteEntireStorage
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodeProtectedStorage ()
{
	_VS_LONG			hResult				=	E_VS_FAIL;

	CSequence			CsqEmpty;

	while (1)
	{
				//	Initialize the m_structASN.CSeqProtectedStorage to an empty sequence
				//	sequence = octet string or integer etc. works fine
				//	but sequence = sequence is an equate operation and does not put one sequence
				//	into other. so the need of an empty sequence.
		m_structASN.CSeqProtectedStorage =	CsqEmpty;

				//	Add the encoded plain text and the protected information to the overall encoded blob
		m_structASN.CSeqProtectedStorage +=	m_structASN.CSeqPlainTextInformation;
		m_structASN.CSeqProtectedStorage +=	m_structASN.CSeqEncryptedProtectedInformation;

				//	allocate memory
		VS_FREE_MEMORY(m_pbyteEntireStorage)

		m_dwEntireStorageSize =	((m_structASN.CSeqProtectedStorage).BaseDERBlob) -> cbData;
		m_pbyteEntireStorage =	(_VS_BYTE*) m_VS_HeapAlloc ( m_dwEntireStorageSize );
		if ( NULL == m_pbyteEntireStorage )
		{
			hResult =	E_VS_OUT_OF_MEMORY;
			break;
		}

				//	and copy the entire encoded byte blob into the byte blob
		_VS_memcpy 
		(
			m_pbyteEntireStorage,
			((m_structASN.CSeqProtectedStorage).BaseDERBlob) -> pbData,
			((m_structASN.CSeqProtectedStorage).BaseDERBlob) -> cbData
		);

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodeProtectedStorage ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodePlainTextData
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will encode all the plain text data of the protected storage.
//						The plain text data includes:
//							VeriSign constant string
//							Protected Storage Version number
//							PTA version number
//							Password Strength
//							Certificates along with the associated preferences
//							Plain Text Applications along with the associated preferences
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodePlainTextData ()
{
	_VS_LONG			hResult			=	E_VS_FAIL;

//	_DWORD				dwTempVersion;

	WCHAR				szVeriSignConstant[VS_VERISIGN_CONSTANT_STRING_LENGTH+2];
	
	while (1)
	{
				//	Initialize the VeriSign constant string sequence from the #defined value
		m_VS_strcpyW (szVeriSignConstant, VS_VERISIGN_CONSTANT_STRING );
		COctetString	CosVeriSignConstant ((_VS_strlenW (szVeriSignConstant) + 1) * sizeof (_VS_CHAR) , (_BYTE*) szVeriSignConstant );

				//	initialize the PS version number using the private members
		CUniversalInteger	CuiPSFirstVersionNumber ( 4, (_BYTE*) &m_dwPSFirstVersionNumber );
		CUniversalInteger	CuiPSSecondVersionNumber ( 4, (_BYTE*) &m_dwPSSecondVersionNumber );
		CUniversalInteger	CuiPSThirdVersionNumber ( 4, (_BYTE*) &m_dwPSThirdVersionNumber );
		CUniversalInteger	CuiPSFourthVersionNumber ( 4, (_BYTE*) &m_dwPSFourthVersionNumber );


				//	fill the PS version numbers in the corresponding sequence
		m_structASN.CSeqPSVersionNumber		=		CuiPSFirstVersionNumber		\
												+	CuiPSSecondVersionNumber	\
												+	CuiPSThirdVersionNumber		\
												+	CuiPSFourthVersionNumber;


				//	initialize the PTA version number using the private members
		CUniversalInteger	CuiPTAFirstVersionNumber ( 4, (_BYTE*) &m_dwPTAFirstVersionNumber );
		CUniversalInteger	CuiPTASecondVersionNumber ( 4, (_BYTE*) &m_dwPTASecondVersionNumber );
		CUniversalInteger	CuiPTAThirdVersionNumber ( 4, (_BYTE*) &m_dwPTAThirdVersionNumber );
		CUniversalInteger	CuiPTAFourthVersionNumber ( 4, (_BYTE*) &m_dwPTAFourthVersionNumber );

				//	fill the PTA version numbers in the correcponding sequence
		m_structASN.CSeqPTAVersionNumber	=		CuiPTAFirstVersionNumber	\
												+	CuiPTASecondVersionNumber	\
												+	CuiPTAThirdVersionNumber	\
												+	CuiPTAFourthVersionNumber;


/*
				//	fill the number of plain text and protected applications in the respective universal integers
		CUniversalInteger		CuiNumberOfPlainTextApplications (4, (_BYTE*)&m_dwNumberOfPlainTextApplications);
		CUniversalInteger		CuiNumberOfProtectedApplications (4, (_BYTE*)&m_dwNumberOfProtectedApplications);

				//	and put them in the corresponding sequence
		m_structASN.CSeqNumberOfApplications =	CuiNumberOfPlainTextApplications + CuiNumberOfProtectedApplications;
*/
				//	fill the password strength
		CUniversalInteger		CuiPasswordStrength			(4, (_BYTE*)&m_dwPasswordStrength);
/*
				//	fill the number of certificates, private keys and information bolobs in the 
				//	respective universal integers
		CUniversalInteger		CuiNumberOfCertificates		(4, (_BYTE*)&m_dwNumberOfCertificates);
		CUniversalInteger		CuiNumberOfPrivateKeys		(4, (_BYTE*)&m_dwNumberOfPrivateKeys);
		CUniversalInteger		CuiNumberOfInformationBlobs	(4, (_BYTE*)&m_dwNumberOfInformationBlobs);
*/
		if ( 0 <  m_dwCertificateInformationChanged )
		{
				//	This means that the certificate information was changed.
				//	This function will encode all the certificates and the associated certificate preferences
			hResult =	m_EncodeCertificateInformation();
			VS_CHECK_HRESULT
		}

		if ( 0 < m_dwPlainTextApplicationInformationChanged )
		{
						//	This function will encode all the (plain text) application related information including the associated application preferences
			hResult =	m_EncodePlainTextApplicationInformation ();
			VS_CHECK_HRESULT
		}

			//	Add all the encoded plain text information of the ProtectedStorage
			//	to the sequence	m_structASN.CSeqPlainTextInformation
		m_structASN.CSeqPlainTextInformation	=	CosVeriSignConstant;
		m_structASN.CSeqPlainTextInformation	+=	m_structASN.CSeqPSVersionNumber;
		m_structASN.CSeqPlainTextInformation	+=	m_structASN.CSeqPTAVersionNumber;
		m_structASN.CSeqPlainTextInformation	+=	CuiPasswordStrength;
//		m_structASN.CSeqPlainTextInformation	+=	CuiNumberOfCertificates;
//		m_structASN.CSeqPlainTextInformation	+=	m_structASN.CSeqNumberOfApplications;
//		m_structASN.CSeqPlainTextInformation	+=	CuiNumberOfPrivateKeys;
//		m_structASN.CSeqPlainTextInformation	+=	CuiNumberOfInformationBlobs;
		m_structASN.CSeqPlainTextInformation	+=	m_structASN.CSeqCertificateInformation;
		m_structASN.CSeqPlainTextInformation	+=	m_structASN.CSeqPlainTextApplicationInformation;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodePlainTextData ()

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodeCertificateInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take all the information regarding the certificate
//						blobs and the associated preferences from the class member structures
//						and encode it and put it in the variable m_structASN.CSeqCertificateInformation
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodeCertificateInformation ()
{
	int					i, j;

	CSequence			CsqEntireInformaitonForAllCertificates;

	CUniversalInteger	CuiNumberOfCertificates (4, (_BYTE*)&m_dwNumberOfCertificates);

	m_structASN.CSeqCertificateInformation =	CuiNumberOfCertificates;

		//	for each certificate
	for ( i =0; i < (int) m_dwNumberOfCertificates; i ++ )
	{
		CSequence			CsqCertificateAllPreferences;	//	this sequence will have the certificate blob 
															//	followed by all the preference name and data
		
						//	The certificate blob is actually a ExtendedCertificateOrCertificate which starts as a SEQUENCE
						//
						//	but for the time being it is been put as an octet string
		COctetString		CosCertificateBlob
							(
								(m_pstructCertificateInformation[i]).dwCertificateBlobLength,
								(_BYTE*) (m_pstructCertificateInformation[i]).pbyteCertificateBlob
							);

		CUniversalInteger	CuiNumberOfPreferences
							(
								4,
								(_BYTE*) &((m_pstructCertificateInformation[i]).dwNumberOfCertificatePreferences)
							);

		CSequence			CsqEntireInformationForOneCertificate;
		
			//	for each certificate preference
		for ( j = 0; j < (int) (m_pstructCertificateInformation[i]).dwNumberOfCertificatePreferences; j ++ )
		{
			CSequence			CSeqOnePreference;

				//	declare local variables (class instances) and copy the values from the structure
				//	The scope of these instances is only within the for loop.
			COctetString		CosCertificatePreferenceName
								(
									(m_pstructCertificateInformation[i]).pdwCertificatePreferenceNameLength[j],
									(_BYTE*) (m_pstructCertificateInformation[i]).ppbyteCertificatePreferenceName[j]
								);

			COctetString		CosCertificatePreferenceData
								(
									(m_pstructCertificateInformation[i]).pdwCertificatePreferenceDataLength[j],
									(_BYTE*) (m_pstructCertificateInformation[i]).ppbyteCertificatePreferenceData[j]
								);

				//	add the certificate preference name and data to the sequence
			CSeqOnePreference	=	CosCertificatePreferenceName;
			CSeqOnePreference	+=	CosCertificatePreferenceData;
		
				//	add this to the sequence of preferences
			CsqCertificateAllPreferences +=	CSeqOnePreference;
		}	//	end		for ( j = 0; j < (m_pstructCertificateInformation[i]).dwNumberOfCertificatePreferences; j ++ );
		//	at the end of this for loop we have all the preference name/data pairs for one certificate
		//	in the CsqCertificateAllPreferences

			
			//	put the certificate blob and the preference name/data pairs in the sequence
		CsqEntireInformationForOneCertificate =		CosCertificateBlob;
		CsqEntireInformationForOneCertificate +=	CuiNumberOfPreferences;
		CsqEntireInformationForOneCertificate +=	CsqCertificateAllPreferences;

			//	This contains the certificate blob and the preference name/data pairs for all the certificates.
			//	so append the certificate blob and the preference name/data pairs for the current certificate.
		CsqEntireInformaitonForAllCertificates += CsqEntireInformationForOneCertificate;
	}	//	end		for ( i =0; i < m_dwNumberOfCertificates; i ++ )

	m_structASN.CSeqCertificateInformation +=	CsqEntireInformaitonForAllCertificates;

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodeCertificateInformation ()

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodePlainTextApplicationInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take all the information regarding the application
//						and the associated preferences from the class member structures
//						and encode it and put it in the variable m_structASN.CSeqPlainTextApplicationInformation
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodePlainTextApplicationInformation ()
{
	int					i, j;

	CSequence			CsqEntireInformationForAllApplication;

	CUniversalInteger	CuiNumberOfPlainTextApplications (4, (_BYTE*)&m_dwNumberOfPlainTextApplications);

	m_structASN.CSeqPlainTextApplicationInformation	=	CuiNumberOfPlainTextApplications;

		//	for each application
	for ( i =0; i < (int) m_dwNumberOfPlainTextApplications; i ++ )
	{
		CSequence			CsqApplicationAllPreferences;	//	this sequence will have the application and host name
															//	followed by all the preference name and data
				
		COctetString		CosApplicationName
							(
								(m_pstructPlainTextApplicationInformation[i]).dwApplicationNameLength,
								(_BYTE*) (m_pstructPlainTextApplicationInformation[i]).pbyteApplicationName
							);

		COctetString		CosApplicationHost
							(
								(m_pstructPlainTextApplicationInformation[i]).dwApplicationHostLength,
								(_BYTE*) (m_pstructPlainTextApplicationInformation[i]).pbyteApplicationHost
							);

		CUniversalInteger	CuiNumberOfPreferences
							(
								4,
								(_BYTE*)&((m_pstructPlainTextApplicationInformation[i]).dwNumberOfApplicationPreferences)
							);

		CSequence			CsqEntireInformationForOneApplication;

			//	for each application preference
		for ( j = 0; j < (int) (m_pstructPlainTextApplicationInformation[i]).dwNumberOfApplicationPreferences; j ++ )
		{
			CSequence			CSeqOnePreference;

				//	declare local variables (class instances) and copy the values from the structure
				//	The scope of these instances is only within the for loop.
			COctetString		CosApplicationPreferenceName
								(
									(m_pstructPlainTextApplicationInformation[i]).pdwApplicationPreferenceNameLength[j],
									(_BYTE*) (m_pstructPlainTextApplicationInformation[i]).ppbyteApplicationPreferenceName[j]
								);

			COctetString		CosApplicationPreferenceData
								(
									(m_pstructPlainTextApplicationInformation[i]).pdwApplicationPreferenceDataLength[j],
									(_BYTE*) (m_pstructPlainTextApplicationInformation[i]).ppbyteApplicationPreferenceData[j]
								);

				//	add the application preference name and data to the sequence
			CSeqOnePreference	=	CosApplicationPreferenceName;
			CSeqOnePreference	+=	CosApplicationPreferenceData;

				//	add this to the sequence of preferences
			CsqApplicationAllPreferences +=	CSeqOnePreference;
		}	//	end		for ( j = 0; j < (m_pstructPlainTextApplicationInformation[i]).dwNumberOfApplicationPreferences; j ++ )
		//	at the end of this for loop we have all the preference name/data pairs for one application
		//	in the CsqApplicationAllPreferences

			
			//	put the application name, host and the preference name/data pairs in the sequence
		CsqEntireInformationForOneApplication =		CosApplicationName;
		CsqEntireInformationForOneApplication +=	CosApplicationHost;
		CsqEntireInformationForOneApplication +=	CuiNumberOfPreferences;
		CsqEntireInformationForOneApplication +=	CsqApplicationAllPreferences;

			//	This contains the application name, host and the preference name/data pairs for all the applications.
			//	so append the application name, host and the preference name/data pairs for the current application.
		CsqEntireInformationForAllApplication +=	CsqEntireInformationForOneApplication;
	}	//	end		for ( i =0; i < m_dwNumberOfPlainTextApplications; i ++ )

	m_structASN.CSeqPlainTextApplicationInformation +=	CsqEntireInformationForAllApplication;

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodePlainTextApplicationInformation ()



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodeProtectedData
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will encode all the protected data of the protected storage.
//						The protected data includes:
//							VeriSign constant string
//							Private Keys
//							Protected Applications along with the associated preferences
//							Information Blobs
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodeProtectedData ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	WCHAR					szVeriSignConstant[VS_VERISIGN_CONSTANT_STRING_LENGTH+2];

	CSequence				CSeqSaltIterationCount;
	CSequence				CSeqEmpty;

	while (1)
	{
			//	Initialize the VeriSign constant string sequence from the #defined value
		m_VS_strcpyW (szVeriSignConstant, VS_VERISIGN_CONSTANT_STRING);
		COctetString	CosVeriSignConstant ((_VS_strlenW (szVeriSignConstant) + 1) * sizeof (_VS_CHAR) , (_BYTE*) szVeriSignConstant );

		if ( 0 < m_dwPrivateKeysChanged )
		{
						//	This function will encode all the private keys
			hResult =	m_EncodePrivateKeyInformation ();
			VS_CHECK_HRESULT
		}

		if ( 0 < m_dwProtectedApplicationInformationChanged )
		{
						//	This function will encode all the (protected) application related information including the associated application preferences
			hResult =	m_EncodeProtectedApplicationInformation ();
			VS_CHECK_HRESULT
		}

		if ( 0 < m_dwInformationBlobChanged )
		{
						//	This function will encode all the information blobs
			hResult =	m_EncodeInformationBlobs ();
			VS_CHECK_HRESULT
		}

			//	Add all the encoded protected information of the ProtectedStorage
			//	to the sequence	m_structASN.CSeqProtectedInformation
		m_structASN.CSeqProtectedInformation	=	CosVeriSignConstant;
		m_structASN.CSeqProtectedInformation	+=	m_structASN.CSeqPrivateKeys;
		m_structASN.CSeqProtectedInformation	+=	m_structASN.CSeqProtectedApplicationInformation;
		m_structASN.CSeqProtectedInformation	+=	m_structASN.CSeqInformationBlobs;

		m_dwDecryptedProtectedInformationLength =	((m_structASN.CSeqProtectedInformation).BaseDERBlob) -> cbData;

		VS_FREE_MEMORY(m_pbyteDecryptedProtectedInformation)
		m_pbyteDecryptedProtectedInformation	=	((m_structASN.CSeqProtectedInformation).BaseDERBlob) -> pbData;

			//	generate the new salt and iteration count before starting encryption
		m_GenerateNewSaltAndIterationCount ();

		hResult =	m_EncryptProtectedData ();

		m_pbyteDecryptedProtectedInformation	=	NULL;
		m_dwDecryptedProtectedInformationLength	=	0;

		VS_CHECK_HRESULT

		COctetString		CosEncryptedProtectedInformation
							(
								m_dwEncryptedProtectedInformationLength,
								m_pbyteEncryptedProtectedInformation
							);

			//	put the octet string salt and the integer iteration count in a sequesnce
		COctetString		CosSalt
							(
								m_dwSaltLen,
								m_pbyteSalt
							);

		CUniversalInteger	CuiIterationCount (4, (_BYTE*)&m_dwIterationCount);

		CSeqSaltIterationCount =	CosSalt;
		CSeqSaltIterationCount +=	CuiIterationCount;

				//	init the m_structASN.CSeqEncryptedProtectedInformation to empty sequence
		m_structASN.CSeqEncryptedProtectedInformation =	CSeqEmpty;

				//	in the encrypted protected informaiton put the sequence containing the
				//	salt and iteration count followed by the actual encrypted protected information
				//
				//	NOTE: we are not doing m_structASN.CSeqEncryptedProtectedInformation	=	CSeqSaltIterationCount;
				//	and instead using += because = will just copy the contents of CSeqSaltIterationCount
				//	into m_structASN.CSeqEncryptedProtectedInformation and will not put one sequence
				//	into other.
				//
		m_structASN.CSeqEncryptedProtectedInformation	+=	CSeqSaltIterationCount;
		m_structASN.CSeqEncryptedProtectedInformation	+=	CosEncryptedProtectedInformation;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodeProtectedData ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodePrivateKeyInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take the private keys from the the class member structures
//						and encode it and put it in the variable m_structASN.CSeqPrivateKeys
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodePrivateKeyInformation ()
{
	int						i;

	CSequence				CSeqAllPrivateKeys;

	CUniversalInteger	CuiNumberOfPrivateKeys (4, (_BYTE*)&m_dwNumberOfPrivateKeys);

	m_structASN.CSeqPrivateKeys =	CuiNumberOfPrivateKeys;

		//	for each private key
	for ( i =0; i < (int) m_dwNumberOfPrivateKeys; i ++ )
	{
		CSequence			CSeqOnePrivateKey;		//	this sequence will have the private key
													//	and the associated hash

						//	put the private key as an octet string
		COctetString		CosPrivateKey
							(
								(m_pstructPrivateKeyInformation[i]).dwPrivateKeyBlobLength,
								(_BYTE*) (m_pstructPrivateKeyInformation[i]).pbytePrivateKeyBlob
							);

						//	put the associated hash as an octet string
		COctetString		CosAssociatedHash
							(
								(m_pstructPrivateKeyInformation[i]).dwAssociatedHashLength,
								(_BYTE*) (m_pstructPrivateKeyInformation[i]).pbyteAssociatedHash
							);

		// Modified by - Infosys Technologies Ltd. 
		// Change Request - CR#21529
		// Description - Add the PrivateKeyExportable flag to the structure.
		// CR#21529 Begin
		// Date Modified - July 05, 2004
		CUniversalInteger	CuiPrivateKeyExportable
							(
								4,
								(_BYTE*) &((m_pstructPrivateKeyInformation[i]).dwPrivateKeyExportableFlag)
							);		
		// CR#21529 - End
		CSeqOnePrivateKey += CosAssociatedHash;
		CSeqOnePrivateKey += CosPrivateKey;
		CSeqOnePrivateKey += CuiPrivateKeyExportable;
		CSeqAllPrivateKeys += CSeqOnePrivateKey;
	}	//	end		for ( i =0; i < m_dwNumberOfPrivateKeys; i ++ );

	m_structASN.CSeqPrivateKeys += CSeqAllPrivateKeys;

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodePrivateKeyInformation ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodeProtectedApplicationInformation
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take all the information regarding the application
//						and the associated preferences from the class member structures
//						and encode it and put it in the variable m_structASN.CSeqProtectedApplicationInformation
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodeProtectedApplicationInformation ()
{
	int					i, j;

	CSequence			CsqEntireInformationForAllApplication;

	CUniversalInteger	CuiNumberOfProtectedApplications (4, (_BYTE*)&m_dwNumberOfProtectedApplications);

	m_structASN.CSeqProtectedApplicationInformation	=	CuiNumberOfProtectedApplications;

		//	for each application
	for ( i =0; i < (int) m_dwNumberOfProtectedApplications; i ++ )
	{
		CSequence			CsqApplicationAllPreferences;	//	this sequence will have the application and host name
															//	followed by all the preference name and data

		COctetString		CosApplicationReadOKDomains;
		COctetString		CosApplicationWriteOKDomains;

		COctetString		CosApplicationName
							(
								(m_pstructProtectedApplicationInformation[i]).dwApplicationNameLength,
								(_BYTE*) (m_pstructProtectedApplicationInformation[i]).pbyteApplicationName
							);

		COctetString		CosApplicationHost
							(
								(m_pstructProtectedApplicationInformation[i]).dwApplicationHostLength,
								(_BYTE*) (m_pstructProtectedApplicationInformation[i]).pbyteApplicationHost
							);

		COctetString		CosApplicationCreatorWildCard
							(
								(m_pstructProtectedApplicationInformation[i]).dwApplicationCreatorWildCardLength,
								(_BYTE*) (m_pstructProtectedApplicationInformation[i]).pbyteApplicationCreatorWildCard
							);

		CUniversalInteger	CuiNumOfApplicationReadOKDomains
							(
								4,
								(_BYTE*)&((m_pstructProtectedApplicationInformation[i]).dwNumOfApplicationReadOKDomains)
							);
		
		if (m_pstructProtectedApplicationInformation[i].dwNumOfApplicationReadOKDomains > 0)
		{
			COctetString	CosTempApplicationReadOKDomains
			(
				(m_pstructProtectedApplicationInformation[i]).dwApplicationReadOKDomainsLength,
				(_BYTE*) (m_pstructProtectedApplicationInformation[i]).pbyteApplicationReadOKDomains
			);
			CosApplicationReadOKDomains = CosTempApplicationReadOKDomains;
		}

		CUniversalInteger	CuiNumOfApplicationWriteOKDomains
							(
								4,
								(_BYTE*)&((m_pstructProtectedApplicationInformation[i]).dwNumOfApplicationWriteOKDomains)
							);

		if (m_pstructProtectedApplicationInformation[i].dwNumOfApplicationWriteOKDomains > 0)
		{
			COctetString	CosTempApplicationWriteOKDomains
			(
				(m_pstructProtectedApplicationInformation[i]).dwApplicationWriteOKDomainsLength,
				(_BYTE*) (m_pstructProtectedApplicationInformation[i]).pbyteApplicationWriteOKDomains
			);
			CosApplicationWriteOKDomains = CosTempApplicationWriteOKDomains;
		}

		CUniversalInteger	CuiNumberOfPreferences
							(
								4,
								(_BYTE*)&((m_pstructProtectedApplicationInformation[i]).dwNumberOfApplicationPreferences)
							);

		CSequence			CsqEntireInformationForOneApplication;

			//	for each application preference
		for ( j = 0; j < (int) (m_pstructProtectedApplicationInformation[i]).dwNumberOfApplicationPreferences; j ++ )
		{
			CSequence			CSeqOnePreference;
				//	declare local variables (class instances) and copy the values from the structure
				//	The scope of these instances is only within the for loop.
			COctetString		CosApplicationPreferenceName
								(
									(m_pstructProtectedApplicationInformation[i]).pdwApplicationPreferenceNameLength[j],
									(_BYTE*) (m_pstructProtectedApplicationInformation[i]).ppbyteApplicationPreferenceName[j]
								);

			COctetString		CosApplicationPreferenceData
								(
									(m_pstructProtectedApplicationInformation[i]).pdwApplicationPreferenceDataLength[j],
									(_BYTE*) (m_pstructProtectedApplicationInformation[i]).ppbyteApplicationPreferenceData[j]
								);

				//	add the application preference name and data to the sequence
			CSeqOnePreference	=	CosApplicationPreferenceName;
			CSeqOnePreference	+=	CosApplicationPreferenceData;

				//	add this to the SEQUENCE of preferences
			CsqApplicationAllPreferences += CSeqOnePreference;
		}	//	end		for ( j = 0; j < (m_pstructProtectedApplicationInformation[i]).dwNumberOfApplicationPreferences; j ++ )
		//	at the end of this for loop we have all the preference name/data pairs for one application
		//	in the CsqApplicationAllPreferences

			
			//	put the application name, host and the preference name/data pairs in the sequence
		CsqEntireInformationForOneApplication =		CosApplicationName;
		CsqEntireInformationForOneApplication +=	CosApplicationHost;
		CsqEntireInformationForOneApplication +=	CosApplicationCreatorWildCard;
		CsqEntireInformationForOneApplication +=	CuiNumOfApplicationReadOKDomains;
		CsqEntireInformationForOneApplication +=	CosApplicationReadOKDomains;
		CsqEntireInformationForOneApplication +=	CuiNumOfApplicationWriteOKDomains;
		CsqEntireInformationForOneApplication +=	CosApplicationWriteOKDomains;
		CsqEntireInformationForOneApplication +=	CuiNumberOfPreferences;
		CsqEntireInformationForOneApplication +=	CsqApplicationAllPreferences;

			//	This contains the application name, host and the preference name/data pairs for all the applications.
			//	so append the application name, host and the preference name/data pairs for the current application.
		CsqEntireInformationForAllApplication +=	CsqEntireInformationForOneApplication;
	}	//	end		for ( i =0; i < m_dwNumberOfProtectedApplications; i ++ )

	m_structASN.CSeqProtectedApplicationInformation +=	CsqEntireInformationForAllApplication;

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodeProtectedApplicationInformation ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncodeInformationBlobs
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS if the function succeeds
//
//	Description		:	This function will take all the information bolbs from the class 
//						member structures and encode it and put it in the variable 
//						m_structASN.CSeqInformationBlobs
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncodeInformationBlobs ()
{
	int					i;

	CSequence			CSeqAllInformationBlobs;

	CUniversalInteger	CuiNumberOfInformationBlobs (4, (_BYTE*)&m_dwNumberOfInformationBlobs);

	m_structASN.CSeqInformationBlobs	=	CuiNumberOfInformationBlobs;

		//	for each information blob
	for ( i =0; i < (int) m_dwNumberOfInformationBlobs; i ++ )
	{
		CSequence			CSeqOneInformationBlob;		//	this sequence will have the information blob name and data

						//	put the information blob name as a printable string
		COctetString		CosInformationBlobName
							(
								(m_pstructInformationBlob[i]).dwInformationBlobNameLength,
								(_BYTE*) (m_pstructInformationBlob[i]).pbyteInformationBlobName
							);

						//	put the information blob data as an octet string
		COctetString		CosInformationBlobData
							(
								(m_pstructInformationBlob[i]).dwInformationBlobDataLength,
								(_BYTE*) (m_pstructInformationBlob[i]).pbyteInformationBlobData
							);

		CSeqOneInformationBlob	+= CosInformationBlobName;
		CSeqOneInformationBlob	+= CosInformationBlobData;

		CSeqAllInformationBlobs	+= CSeqOneInformationBlob;
	}	//	end		for ( i =0; i < (int) m_dwNumberOfInformationBlobs; i ++ )

	m_structASN.CSeqInformationBlobs += CSeqAllInformationBlobs;

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::m_EncodeInformationBlobs ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_OpenAndReadProtectedStorage
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	if the function is succesful
//		E_VS_STORAGE_CORRUPT	-	if the storage file is corrupt
//		E_VS_OUT_OF_MEMORY		-	if the storage cannot be read into memory
//		Win32 file open error
//
//	Description		:
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_OpenAndReadProtectedStorage()
{
	_VS_LONG			hResult					=	E_VS_FAIL;

	BOOL				bResult					=	FALSE;

	DWORD				dwNumberofBytesRead		=	0;
	_bstr_t				tbstrFileName;
/*
#if PLATFORM==VSPS_WIN32
	WIN32_FILE_ATTRIBUTE_DATA	FileInofrmation;
#else
	//	undeclared = 0;
#endif
*/

	while (1)
	{
		if ( PS_FILE == m_dwMemoryOrFile )	//	1
		{
#if PLATFORM==VSPS_WIN32
			tbstrFileName =	m_szStorageFileName;

				//	open the file in read mode
			m_hStorageFile =	::CreateFile
								(
									tbstrFileName,
									GENERIC_READ | GENERIC_WRITE,
									FILE_SHARE_READ,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL,
									NULL
								);
			if ( INVALID_HANDLE_VALUE == m_hStorageFile )
			{
				hResult =	::GetLastError ();
				break;
			}

					//	get the size of the file
			m_dwEntireStorageSize =	::GetFileSize
									(
										m_hStorageFile,
										NULL
									);
			if ( 0xFFFFFFFF == m_dwEntireStorageSize )
			{
				hResult =	E_VS_STORAGE_CORRUPT;
	//			hResult =	::GetLastError ();
				break;
			}
#else
//		undeclared = 0;
#endif
			VS_FREE_MEMORY(m_pbyteEntireStorage)

				//	allocate memory for the entire ProtectedStorage
			m_pbyteEntireStorage =	(_VS_BYTE*) m_VS_HeapAlloc ( m_dwEntireStorageSize );
			if ( NULL == m_pbyteEntireStorage )
			{
				hResult =	E_VS_OUT_OF_MEMORY;
				break;
			}

#if PLATFORM==VSPS_WIN32

						//	Read the contents of the file into the buffer
			bResult =	::ReadFile
						(
							m_hStorageFile,
							m_pbyteEntireStorage,
							m_dwEntireStorageSize,
							&dwNumberofBytesRead,
							NULL
						);
			if ( TRUE != bResult )
			{
				hResult =	::GetLastError ();
				break;
			}

						//	close the file
			bResult =	::CloseHandle
						(
							m_hStorageFile
						);
			m_hStorageFile =	NULL;
 			if ( TRUE != bResult )
			{
				hResult =	::GetLastError ();
				break;
			}
/*
					//	get the time when the file was last modified
		bResult =	::GetFileAttributesEx
					(
						m_szStorageFileName,	//	put this into a _bstr_t
						GetFileExInfoStandard,
						(LPVOID) &FileInofrmation
					);
 		if ( TRUE != bResult )
		{
			hResult =	::GetLastError ();
			break;
		}

					//	and copy it to the member variable
		::_VS_memcpy 
		( 
			(void *) &m_FileTimeLastModified, 
			(const void *) &(FileInofrmation.ftLastWriteTime), 
			sizeof (FILETIME) 
		);
*/
#else
//		undelcared = 0;
#endif
		}
		else
		{
					//	PS_MEMORY = m_dwMemoryOrFile = 2
			m_dwEntireStorageSize =	(*m_pdwRoamingBufferLen);
//			VS_ALLOC_AND_BYTEBLOB_COPY (m_pbyteEntireStorage, m_pbyteRoamingBuffer, m_dwEntireStorageSize)
			VS_ALLOC_AND_BYTEBLOB_COPY (m_pbyteEntireStorage, (*m_ppbyteRoamingBuffer), m_dwEntireStorageSize)
		}

		hResult =	VS_SUCCESS;
		break;
	}//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_OpenAndReadProtectedStorage ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_CreateProtectedStorage
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	if the function is succesful
//
//	Description		:	The storage file is created. A function is called to set the default values
//						to all the variables. 'Close' is called which will encode the variables (defaults
//						in this case) and dump it to the file.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_CreateProtectedStorage ()
{
	_VS_LONG			hResult					=	E_VS_FAIL;

	BOOL				bResult					=	0;

	_bstr_t				tbstrFileName;

//	_VS_DWORD			dwStorageLen			=	999;
	_VS_DWORD			dwChangedFlag			=	999;

	_VS_CHAR			szPath [MAX_PATH];
	_bstr_t				tbstrPath;

	while (1)
	{
		if ( PS_FILE == m_dwMemoryOrFile )	//	1
		{
#if PLATFORM==VSPS_WIN32
		tbstrFileName =	m_szStorageFileName;

			//	get path from the file name
		m_GetPathFromFileName
		(
			(_VS_CHAR*) tbstrFileName,
			szPath
		);
		tbstrPath =	szPath;

		bResult =	m_CreateRecursiveDirectory ( tbstrPath );
		if ( FALSE == bResult )
		{
			hResult =	::GetLastError ();
		}

			//	create the file with full access
		m_hStorageFile =	::CreateFile
							(
								tbstrFileName,
								GENERIC_READ | GENERIC_WRITE,
								0,		//	no sharing
								NULL,
								CREATE_NEW,
								FILE_ATTRIBUTE_NORMAL,
								NULL
							);
		if ( INVALID_HANDLE_VALUE == m_hStorageFile )
		{
			hResult =	::GetLastError ();
			break;
		}

					//	close the file
		bResult =	::CloseHandle
					(
						m_hStorageFile
					);
		m_hStorageFile =	NULL;
 		if ( TRUE != bResult )
		{
			hResult =	::GetLastError ();
			break;
		}

#else
//		undeclared = 0;
#endif
		}
		else
		{
				//	the m_dwMemoryOrFile = PS_MEMORY (2)
			//	so do nothin...
		}

				//	set all the protected storage defaults
		hResult =	m_SetProtectedStorageDefaults ();
		VS_CHECK_HRESULT

				//	this flag will prevent the storage from destroying all the
				//	concurrency objects and other member vars
		m_dwDontDestroyMembers  =	1;

				//	calling close will encode the defaults and create the ProtectedStorage
				//	without any certificates, private keys, applications etc.
		if ( PS_FILE == m_dwMemoryOrFile )		//	1
		{
			hResult =	Close ();
			VS_CHECK_HRESULT
		}
		else
		{
				//	m_dwMemoryOrFile = PS_MEMORY = 2

					//	the data is not required here
					//	the only thing needed is the data to be put into the m_pbyteRoamingBuffer
			hResult =	CloseForRoaming
						(
//							NULL,
//							&dwStorageLen,
							&dwChangedFlag
						);
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CreateProtectedStorage ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_SetProtectedStorageDefaults
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	if the function is succesful
//
//	Description		:	This function will set all the variables to the default values.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_SetProtectedStorageDefaults ()
{
	_VS_LONG			hResult				=	E_VS_FAIL;

	WCHAR				szVeriSignConstant[VS_VERISIGN_CONSTANT_STRING_LENGTH+2];

	while (1)
	{
//		VS_ALLOC_AND_STRING_COPY(szTemp, VS_VERISIGN_CONSTANT_STRING)

		m_VS_strcpyW (szVeriSignConstant, VS_VERISIGN_CONSTANT_STRING );

		VS_FREE_MEMORY(m_pbyteVeriSignConstant)
		VS_ALLOC_AND_BYTEBLOB_COPY(m_pbyteVeriSignConstant, (_BYTE*) szVeriSignConstant, (_VS_strlenW(szVeriSignConstant) + 1) * sizeof (_VS_CHAR) );

		if(m_boolUseFixedKey)
			m_dwPSFirstVersionNumber					=	VSPS_VERSION_FIRST_NUMBER;
		else
			m_dwPSFirstVersionNumber					=	VSPS_VERSION_FIRST_NUMBER; // CR# 21529
			// m_dwPSFirstVersionNumber					=	VSPS_VERSION_FIRST_NUMBER_4;
			

		m_dwPSSecondVersionNumber					=	VSPS_VERSION_SECOND_NUMBER;
		m_dwPSThirdVersionNumber					=	VSPS_VERSION_THIRD_NUMBER;
		m_dwPSFourthVersionNumber					=	VSPS_VERSION_FOURTH_NUMBER;

		m_dwPTAFirstVersionNumber					=	VSPTA_VERSION_FIRST_NUMBER;
		m_dwPTASecondVersionNumber					=	VSPTA_VERSION_SECOND_NUMBER;
		m_dwPTAThirdVersionNumber					=	VSPTA_VERSION_THIRD_NUMBER;
		m_dwPTAFourthVersionNumber					=	VSPTA_VERSION_FOURTH_NUMBER;

		m_dwPasswordStrength						=	999;
			//VSPS_PASSWORD_STRENGTH;

		m_dwNumberOfCertificates					=	0;
		m_dwNumberOfPlainTextApplications			=	0;
		m_dwNumberOfProtectedApplications			=	0;

		m_dwNumberOfPrivateKeys						=	0;
		m_dwNumberOfInformationBlobs				=	0;

		m_dwPlainTextInformationChanged				=	1;
		m_dwProtectedInformationChanged				=	1;

		m_dwCertificateInformationChanged			=	1;
		m_dwPlainTextApplicationInformationChanged	=	1;
		m_dwPrivateKeysChanged						=	1;
		m_dwProtectedApplicationInformationChanged	=	1;
		m_dwInformationBlobChanged					=	1;
		
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_SetProtectedStorageDefaults ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_VS_HeapCreate
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS			-	Successful
//		E_VS_OUT_OF_MEMORY	-	The memory allocation was unsuccessful
//
//	Description		:	This function will create a heap object
//						The minimum size for this heap is HEAP_INITIAL_SIZE (102400) bytes
//						and the maximum size is HEAP_MAXIMUM_SIZE (1048576) bytes.
//						The heap will be pointed by the m_hHeap
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_VS_HeapCreate ()
{
	_VS_LONG			hResult			=	E_VS_FAIL;

	while (1)
	{
				//	create the heap
		m_hHeap =	::HeapCreate
						(
							0,
							HEAP_INITIAL_SIZE,
							//HEAP_MAXIMUM_SIZE
							0
						);
		if ( NULL == m_hHeap )
		{
			hResult =	E_VS_OUT_OF_MEMORY;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_VS_HeapCreate ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_VS_HeapDestroy
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS			-	Successful
//
//	Description		:	This function will destroy the heap and reset the handle to NULL
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_VS_HeapDestroy ()
{
	if ( NULL != m_hHeap)
	{
		HeapDestroy (m_hHeap);
		m_hHeap =	NULL;
	}

	return	VS_SUCCESS;
}	//	end		_VS_LONG	CProtectedStorage::m_VS_HeapDestroy ()

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_VS_HeapAlloc
//
//	Parameters
//		const _VS_DWORD		i_ncSize	-	The size in bytes
//
//	Return Values	:
//		If the function succeeds then the pointer to the allocated memory block is returned.
//		If the function fails then NULL is returned.
//
//	Description		:	The function allocates memory from the heap pointed by mhHeap
//
///////////////////////////////////////////////////////////////////////////////
void*	CProtectedStorage::m_VS_HeapAlloc
(
	const _VS_DWORD		i_ncSize
)
{
	void*	pAllocatedMemory;

	pAllocatedMemory =	::HeapAlloc
						(
							m_hHeap,
							HEAP_ZERO_MEMORY,
							i_ncSize * sizeof (_BYTE)
						);

	return	pAllocatedMemory;
}	//	end		void*	CProtectedStorage::m_VS_HeapAlloc

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_VS_HeapFree
//
//	Parameters
//		void*				i_pFreeBlock	-	pointer to a bolck which is to be freed
//
//	Return Values	:
//
//	Description		:	The function frees block of memory from teh heap
//
///////////////////////////////////////////////////////////////////////////////
void	CProtectedStorage::m_VS_HeapFree
(
	void*				i_pFreeBlock
)
{
	DWORD		dwMemorySize		=	0;

	if ( NULL != i_pFreeBlock )
	{
		dwMemorySize =	::HeapSize
						(
							m_hHeap,
							0,
							i_pFreeBlock
						);

		if ( 0xFFFFFFFF != dwMemorySize )
		{
			EraseMemory ( dwMemorySize, (BYTE*) i_pFreeBlock );
		}

		::HeapFree ( m_hHeap, 0, i_pFreeBlock );
	}

	return;
}	//	end		void	CProtectedStorage::m_VS_HeapFree

/*
This funciton was not used anywhere and therefore is commented out.

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_GetNumberOfElementsInSequence
//
//	Parameters
//		const _DERTree*		i_pcstructDERTree		-	The const pointer to the _DERTree structure. 
//														This structure should correspond to a SEQUENCE 
//														although no check is performed in the function
//		_VS_DWORD*			o_pdwNumberOfElements	-	The number of elements in the SEQUENCE will be
//														returned using this
//
//	Return Values	:
//		VS_SUCCESS		-	if the function is successful
//		E_VS_INVALIDARG	-	if the input parameter is NULl
//
//	Description		:	The function will find out the number of elements contained by a sequence 
//						(only 1 level deep)
//						eg: if the input is
//							SEQUENCE
//								UNIVERSAL INTEGER
//								UNIVERSAL INTEGER
//							then the output will return 2
//
//							if the input is
//							SEQUENCE
//								SEQUENCE
//									UNIVERSAL INTEGER
//								SEQUENCE
//									UNIVERSAL INTEGER
//								UNIVERSAL INTEGER
//							then the output will be 3
//
//						0 will be returned if the SEQUENCE is empty
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_GetNumberOfElementsInSequence
(
	const _DERTree*		i_pcstructDERTree,
	_VS_DWORD*			o_pdwNumberOfElements
)
{
	_VS_LONG			hResult			=	E_VS_FAIL;
	_DERTree*			pstructDERTreeCurrent;

	while (1)
	{
		VS_CHECK_INPUT_POINTER_FOR_NULL (i_pcstructDERTree)
		VS_CHECK_INPUT_POINTER_FOR_NULL (o_pdwNumberOfElements)

		if ( NULL != i_pcstructDERTree -> rightDERTree )
		{
			pstructDERTreeCurrent	=	i_pcstructDERTree -> rightDERTree;
			*o_pdwNumberOfElements	=	1;

			while ( NULL != pstructDERTreeCurrent -> nextDERTree )
			{
				(*o_pdwNumberOfElements) ++;
				pstructDERTreeCurrent =	pstructDERTreeCurrent -> nextDERTree;
			}	//	end		while ( NULL != pstructDERTreeCurrent -> nextDERTree )
		}
		else
		{
			*o_pdwNumberOfElements =	0;
		}

		hResult =	VS_SUCCESS;
		break;
	}

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_GetNumberOfElementsInSequence

*/


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_GetCertificateIndexFromPointerToCertificate
//
//	Parameters
//		const _VS_DWORD		i_cnPointerToCertificate	-	the pointer to the certificate
//		_VS_DWORD*			o_pnCertificateIndex		-	The index of the certificate will be returned
//
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_INVALID_CERT_PTR	-	if the certificate pointer does not actually point to a certificate
//		E_VS_INVALIDARG			-	if a parameter is invalid
//
//	Description		:	The function accepts a pointer to the certificate and then will
//						traverse the Certificate Informaiton structure array to find
//						the matching certificate. It will then return the index it that array
//						using the o_pnCertificateIndex
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_GetCertificateIndexFromPointerToCertificate
(
	const _VS_DWORD		i_cnPointerToCertificate,
	_VS_DWORD*			o_pnCertificateIndex
)
{
	_VS_LONG					hResult				=	E_VS_FAIL;

	int	i;

	int	nFound = 0;

	while (1)
	{
			//	check if the pointer is NULL
		VS_CHECK_INPUT_POINTER_FOR_NULL ( o_pnCertificateIndex )

			//	for each certificate
		for ( i = 0; i < (int) m_dwNumberOfCertificates; i ++ )
		{
				//	check if the pointer to the certificate blob is matching with the passed pointer
			if ( i_cnPointerToCertificate == (_VS_DWORD) (m_pstructCertificateInformation[i].pbyteCertificateBlob) )
			{
					//	if yes then set index to i as the current certificate is the required one
				*o_pnCertificateIndex =	i;
				nFound = 1;
				break;
			}
		}

		if ( 0 == nFound )
		{
				//	this means that the certificate pointer was not valid
			hResult =	E_VS_INVALID_CERT_PTR;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_GetCertificateIndexFromPointerToCertificate



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DecryptProtectedData
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_OUT_OF_MEMORY		-	low on memory
//		E_VS_DECRYPT			-	error performing decryption
//		E_VS_HASH				-	error during hashing
//
//	Description		:	the function will decrypt the protected information.
//						it will call the m_CreateKeyFromPasswordHash function
//						to generate the RC4 key based on user password and then will
//						decrypt the protected information.
//						The data from m_pbyteEncryptedProtectedInformation is decrypted
//						and copied into m_pbyteDecryptedProtectedInformation.
//						the m_dwDecryptedProtectedInformationLength is set to
//						the length ofthe decrypted information.
//
//
// REV HISTORY
// Date           Author           Desc
// ----           ------           ----
// 04/24/2003     Sasi             Made changes to decrypt protected data in roaming 
//								   profiles managed by roaming 6.0 server using fixed RC4 key. 
//								   Old roaming profiles will still be decrypted using the key 
//								   derived from the password.
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DecryptProtectedData ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int						nResult				=	9999;

	_VS_BYTE*				pbyteDecryptedData	=	NULL;

//	_VS_BYTE*				pbyteUnPaddedData	=	NULL;
//	_VS_DWORD				dwUnPaddedDataLen	=	0;

	_VS_BYTE*				pbyteTemp			=	NULL;
	DWORD					dwTemp				=	0;

	int						nMemcmp				=	999;

	void*					pvoidDecryptContext	=	NULL;

	ITEM*					pItemRC4Key			=	NULL;

	while (1)
	{

			// If it is a roaming profile managed by new roaming 6.0 server, then use fixed RC4 key to decrypt protected data
		if (PS_MEMORY == m_dwMemoryOrFile && m_boolUseFixedKey)
		{
			pItemRC4Key =	&m_ItemRoamRC4Key;
		} 
		else 
		{
	//		if ( VSPS_VERSION_FIRST_NUMBER == m_dwPSFirstVersionNumber )
			if ( VSPS_VERSION_FIRST_NUMBER_1 < m_dwPSFirstVersionNumber )
			{
				hResult =	m_CreateKeyFromPasswordSaltIterationCount ();
				pItemRC4Key =	&m_ItemNewRC4Key;
			}
			else
			{
				hResult =	m_CreateKeyFromPasswordHash ();
				pItemRC4Key =	&m_ItemRC4Key;
			}
			VS_CHECK_HRESULT
		}
			//	to be on a safe side allocate twice the memory required
			//	for the decrypted data
		m_dwDecryptedProtectedInformationLength	=	m_dwEncryptedProtectedInformationLength * 2;

		pbyteDecryptedData = (_BYTE*) m_VS_HeapAlloc ( m_dwDecryptedProtectedInformationLength * sizeof (_BYTE) );
		if ( NULL == pbyteDecryptedData )
		{
			hResult =	E_VS_OUT_OF_MEMORY;
			break;
		}

		nResult =	SymDecryptDataBegin
					(
						SYM_RC4,
						pItemRC4Key,
						0,
						&pvoidDecryptContext,
						NULL,
						0
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_DECRYPT;
			break;
		}

		nResult =	SymDecryptDataUpdate
					(
						pvoidDecryptContext,
						(unsigned char*) m_pbyteEncryptedProtectedInformation,
						(unsigned int) m_dwEncryptedProtectedInformationLength,
						(unsigned char*) pbyteDecryptedData,
						(unsigned int*) &m_dwDecryptedProtectedInformationLength
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_DECRYPT;
			break;
		}

		nResult =	SymDecryptDataEnd
					(
						pvoidDecryptContext,
						(unsigned char*) pbyteTemp,
						(unsigned int*) &dwTemp
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_DECRYPT;
			break;
		}

				//	the function will return the decrypted data in pbyteDecryptedData and
				//	the length of the decrypted data in the m_dwDecryptedProtectedInformationLength

				//	even if the password is wrong the decrypt function will return data
				//	so check if decryption was successful by comparing the padding
		if(m_dwDecryptedProtectedInformationLength < VSPS_ENCRYPTION_PADDING_LENGTH)
		{
			nMemcmp = -1;
		}
		else
		{
			nMemcmp =	_VS_memcmp
						(
							pbyteDecryptedData,
							VSPS_ENCRYPTION_PADDING,
							VSPS_ENCRYPTION_PADDING_LENGTH
						);
		}

		if ( 0 == nMemcmp )
		{
					//	the password was correct and the decryption was successful
					//	so allocate required memory for the decrypted data

					//	remove the padding
			m_dwDecryptedProtectedInformationLength = m_dwDecryptedProtectedInformationLength - VSPS_ENCRYPTION_PADDING_LENGTH;
			m_pbyteDecryptedProtectedInformation = (_BYTE*) m_VS_HeapAlloc ( m_dwDecryptedProtectedInformationLength * sizeof (_BYTE) );
			if ( NULL == m_pbyteDecryptedProtectedInformation )
			{
				hResult =	E_VS_OUT_OF_MEMORY;
				break;
			}

			::_VS_memcpy
			(
				m_pbyteDecryptedProtectedInformation,
				&(pbyteDecryptedData [VSPS_ENCRYPTION_PADDING_LENGTH]),
				m_dwDecryptedProtectedInformationLength
			);


	/*		for ( int i = 0; i < (int) m_dwDecryptedProtectedInformationLength; i++ )
			{
				m_pbyteDecryptedProtectedInformation[i] = m_pbyteEncryptedProtectedInformation[m_dwDecryptedProtectedInformationLength - 1 - i];
			}
	*/
		}
		else
		{
			hResult =	m_DestroyKeyFromPassword ();
			VS_CHECK_HRESULT

			hResult =	E_VS_BAD_PASSWORD;
			break;
		}

		hResult =	m_DestroyKeyFromPassword ();
		VS_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY (pbyteDecryptedData)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DecryptProtectedData ()



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_EncryptProtectedData
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_OUT_OF_MEMORY		-	low on memory
//		E_VS_ENCRYPT			-	error performing encryption
//		E_VS_HASH				-	error during hashing
//
//	Description		:	the function will encrypt the protected information.
//						it will call the m_CreateKeyFromPasswordHash function
//						to generate the RC4 key based on user password and then will
//						encrypt the protected information.
//						The data from m_pbyteDecryptedProtectedInformation is encrypted
//						and copied into m_pbyteEncryptedProtectedInformation.
//						the m_dwEncryptedProtectedInformationLength is set to
//						the length ofthe encrypted information.
//
// REV HISTORY
// Date           Author           Desc
// ----           ------           ----
// 04/24/2003     Sasi             Made changes to encrypt protected data in roaming 
//								   profile managed by new roaming server using fixed RC4 key. 
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_EncryptProtectedData ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	int						nResult				=	9999;

	_VS_BYTE*				pbyteEncryptedData	=	NULL;

	_VS_BYTE*				pbytePaddedData		=	NULL;
	_VS_DWORD				dwPaddedDataLen		=	0;

	_VS_BYTE*				pbyteTemp			=	NULL;
	DWORD					dwTemp				=	0;

	void*					pvoidEncryptContext	=	NULL;

	ITEM*					pItemRC4Key			=	NULL;

	while (1)
	{
			// If it is a roaming profile managed by new roaming 6.0 server, then use fixed RC4 key to encrypt protected data
		if (PS_MEMORY == m_dwMemoryOrFile && m_boolUseFixedKey)
		{
			pItemRC4Key =	&m_ItemRoamRC4Key;
		} 
		else 
		{
	//		if ( VSPS_VERSION_FIRST_NUMBER == m_dwPSFirstVersionNumber )
			if ( VSPS_VERSION_FIRST_NUMBER_1 < m_dwPSFirstVersionNumber )
			{
				hResult =	m_CreateKeyFromPasswordSaltIterationCount ();
				pItemRC4Key =	&m_ItemNewRC4Key;
			}
			else
			{
				hResult =	m_CreateKeyFromPasswordHash ();
				pItemRC4Key =	&m_ItemRC4Key;
			}
			VS_CHECK_HRESULT
		}

		dwPaddedDataLen =	m_dwDecryptedProtectedInformationLength + VSPS_ENCRYPTION_PADDING_LENGTH;

		pbytePaddedData = (_BYTE*) m_VS_HeapAlloc ( dwPaddedDataLen * sizeof (_BYTE) );
		if ( NULL == pbytePaddedData )
		{
			hResult =	E_VS_OUT_OF_MEMORY;
			break;
		}

		::_VS_memcpy
		(
			pbytePaddedData,
			VSPS_ENCRYPTION_PADDING,
			VSPS_ENCRYPTION_PADDING_LENGTH
		);

		::_VS_memcpy
		(
			&(pbytePaddedData [VSPS_ENCRYPTION_PADDING_LENGTH]),
			m_pbyteDecryptedProtectedInformation,
			m_dwDecryptedProtectedInformationLength
		);


			//	to be on a safe side allocate twice the memory required
			//	for the decrypted data
		m_dwEncryptedProtectedInformationLength	=	dwPaddedDataLen * 2;

		pbyteEncryptedData = (_BYTE*) m_VS_HeapAlloc ( m_dwEncryptedProtectedInformationLength * sizeof (_BYTE) );
		if ( NULL == pbyteEncryptedData )
		{
			hResult =	E_VS_OUT_OF_MEMORY;
			break;
		}

				//	encrypt the data
		nResult =	SymEncryptDataBegin
					(
						SYM_RC4,
						pItemRC4Key,
						0,
						&pvoidEncryptContext,
						NULL,		//	this should be NULL for RC4
						0
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_ENCRYPT;
			break;
		}

		nResult =	SymEncryptDataUpdate
					(
						pvoidEncryptContext,
						pbytePaddedData,
						dwPaddedDataLen,
						pbyteEncryptedData,
						&m_dwEncryptedProtectedInformationLength
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_ENCRYPT;
			break;
		}

		nResult =	SymEncryptDataEnd
					(
						pvoidEncryptContext,
						(unsigned char*) pbyteTemp,			//	not used for RC4
						(unsigned int*) &dwTemp				//	not used for RC4
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_ENCRYPT;
			break;
		}

				//	the function will return the encrypted data in pbyteEncryptedData and
				//	the length of the encrypted data in the m_dwEncryptedProtectedInformationLength
				//
				//	so allocate required memory for the encrypted data
		m_pbyteEncryptedProtectedInformation = (_BYTE*) m_VS_HeapAlloc ( m_dwEncryptedProtectedInformationLength * sizeof (_BYTE) );
		if ( NULL == m_pbyteEncryptedProtectedInformation )
		{
			hResult =	E_VS_OUT_OF_MEMORY;
			break;
		}

		::_VS_memcpy
		(
			m_pbyteEncryptedProtectedInformation,
			pbyteEncryptedData,
			m_dwEncryptedProtectedInformationLength
		);

/*		for ( int i = 0; i < (int) m_dwEncryptedProtectedInformationLength; i++ )
		{
			m_pbyteEncryptedProtectedInformation[i] = m_pbyteDecryptedProtectedInformation[m_dwEncryptedProtectedInformationLength - 1 - i];
		}*/

		hResult =	m_DestroyKeyFromPassword ();
		VS_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY (pbyteEncryptedData)
	VS_FREE_MEMORY (pbytePaddedData)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_EncryptProtectedData ()



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_HashData
//
//	Parameters
//		const _VS_BYTE*		i_cpbyteInputData	-	The data (byte blob) to be hashed
//		const _VS_DWORD		i_dwInputDataLength	-	length of the data to be hashed
//		_VS_BYTE**			o_ppbyteHash		-	The hash will be returned in this
//		_VS_DWORD*			o_pdwHashLength		-	length of hash returned in this
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_HASH				-	error during hashing
//		E_VS_OUT_OF_MEMORY		-	low on memory
//
//	Description		:	This function will hash the data.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_HashData
(
	const _VS_BYTE*		i_cpbyteInputData,
	const _VS_DWORD		i_cdwInputDataLength,
	_VS_BYTE**			o_ppbyteHash,
	_VS_DWORD*			o_pdwHashLength
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;
	int						nResult				=	999;

	void*					pvoidHashContext	=	NULL;

	while (1)
	{
			//	the length of the hashed data is always 20 bytes.
		*o_pdwHashLength =	20;

			//	allocate memory
		*o_ppbyteHash =	(_VS_BYTE*) m_VS_HeapAlloc (*o_pdwHashLength);
		VS_CHECK_ALLOCATED_MEMORY (*o_ppbyteHash)

					//	Hash the data
		nResult =	HashBegin
					(
						HASH_SHA1,
						&pvoidHashContext
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_HASH;
			break;
		}

		nResult =	HashData
					(
						HASH_SHA1,
						pvoidHashContext,
						(unsigned char*) i_cpbyteInputData,
						(unsigned int) i_cdwInputDataLength
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_HASH;
			break;
		}

		nResult =	HashEnd
					(
						HASH_SHA1,
						pvoidHashContext,
						(unsigned char*) *o_ppbyteHash,
						(unsigned int) *o_pdwHashLength
					);
		if ( 0 != nResult )
		{
			hResult =	E_VS_HASH;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_HashData


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_CheckPasswordTimeOut
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_PASSWORD_TIMEOUT	-	if the password has timed out
//
//	Description		:	The function will check if the provided password has been
//						timed out. If the password has timed out then the user will
//						be prompted for the password using the callback funciton.
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_CheckPasswordTimeOut ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_VS_LONG				longCurrentTime		=	0;

	_VS_CHAR				szPassword [MAX_PATH];
	_VS_DWORD				dwPasswordTimeOutInMinutes	=	0;
	_VS_DWORD				dwPasswordCount				=	0;

	BOOL					boolSuccess					=	FALSE;

	while (1)
	{
		time ( &longCurrentTime );

		if ( (longCurrentTime - m_longTimePasswordProvided) > (_VS_LONG) m_dwPasswordTimeOutIntervalInSeconds )
		{
			if ( NULL != m_pSetPasswordFunctionPointer )
			{
				while ( FALSE == boolSuccess )
				{
								//	this is the call back function which will return the password
								//	and the new timeout value in MINS
					hResult =	m_pSetPasswordFunctionPointer
								(
									m_pvoidPasswordFunctionData,
									szPassword,
									&dwPasswordTimeOutInMinutes
								);
					VS_CHECK_HRESULT

								//	check the password
					hResult =	m_CheckPassword
								(
									(const _VS_CHAR*) szPassword
								);
					if ( VS_SUCCESS == hResult )
					{
									//	the password is correct so update the timeout
						m_dwPasswordTimeOutIntervalInSeconds =	dwPasswordTimeOutInMinutes * 60;

									//	success flag = TRUE
						boolSuccess = TRUE;
					}
					else
					{
						dwPasswordCount ++;
						dwPasswordTimeOutInMinutes =	dwPasswordCount;
					}
				}

				if ( FALSE == boolSuccess )
				{
					break;
				}
			}
			else
			{
				hResult =	E_VS_PASSWORD_TIMEOUT;
				break;
			}
		}

		time ( &m_longTimePasswordProvided );	//	update the password time stamp

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CheckPasswordTimeOut ()


_VS_LONG	CProtectedStorage::m_UpdatePasswordTimeOut ()
{
	if ( 1 == m_nPasswordProvided )
	{
			//	if password is provided then update the timeout
		time ( &m_longTimePasswordProvided );
	}

	return	VS_SUCCESS;
}	//	_VS_LONG	CProtectedStorage::m_UpdatePasswordTimeOut ()



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_CheckIfApplicationExists
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_INVALIDARG			-	invalid parameter
//		E_VS_INVALID_APP		-	if the application does not exist
//
//	Description		:	The function will check if the application name/host specified
//						in initialize exists. if not then an error will be returned.
//
//
//	*****************************************************************************
//	NOTE:	This function should be called ONLY from Initialize. It should NOT be
//			called from any other function.
//	*****************************************************************************
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_CheckIfApplicationExists ()
{
	_VS_LONG				hResult				=E_VS_FAIL;

	int					i;

	int					nAppNameCompare		=	999;
//	int					nAppHostCompare		=	999;
	int					nAppExists			=	0;

	VSPS_ApplicationInformation*			pstructCurrentApplications	=	NULL;
	
	_VS_DWORD			dwNumberOfApplications	=	0;

	while (1)
	{
		switch ( m_dwIsApplicationEncrypted )
		{
			case	APPLICATION_ENCRYPTED:
				pstructCurrentApplications	=	m_pstructProtectedApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfProtectedApplications;
				break;

			case	APPLICATION_DECRYPTED:
				pstructCurrentApplications	=	m_pstructPlainTextApplicationInformation;
				dwNumberOfApplications		=	m_dwNumberOfPlainTextApplications;
				break;

			default:
				pstructCurrentApplications	=	NULL;
				dwNumberOfApplications		=	0;
				hResult =	E_VS_INVALIDARG;
				break;
		}	//	end		switch ( i_cnIsApplicationEncrypted )

		if ( E_VS_INVALIDARG == hResult )
		{
			break;
		}

			//	check if the application already exists
			//	for this compare the application name and application host
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
				break;
			}
		}	//	end		for ( i = 0; i < (int) dwNumberOfApplications; i++ )

		if ( 0 == nAppExists )
		{
				//	the application does not exists. so return this error
			hResult =	E_VS_INVALID_APP;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CheckIfApplicationExists ();


_VS_LONG	CProtectedStorage::m_ReadDataIntoStructures
(
	_VS_DWORD			i_dwUpdateWhat
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		hResult =	m_OpenAndReadProtectedStorage ();
		VS_CHECK_HRESULT

				//	start to decode the protected storage
		hResult =	m_DecodeProtectedStorage ();
		VS_CHECK_HRESULT
		
		if ( UPDATE_ONLY_PLAINTEXT == i_dwUpdateWhat || UPDATE_ALL_IF_POSSIBLE == i_dwUpdateWhat )
		{
					//	decode the plain text data from the storage file
			hResult =	m_DecodePlainTextData ();
			VS_CHECK_HRESULT

					//	reset the changed flags
			m_dwPlainTextInformationChanged				=	0;

			m_dwCertificateInformationChanged			=	0;
			m_dwPlainTextApplicationInformationChanged	=	0;
		}

		if ( UPDATE_ONLY_PROTECTED == i_dwUpdateWhat || UPDATE_ALL_IF_POSSIBLE == i_dwUpdateWhat )
		{
			if ( 1 == m_nPasswordProvided )
			{
					//	if the password is provided then decode the protected data from the storage file
				hResult =	m_DecodeProtectedData ();
				VS_CHECK_HRESULT

					//	turn on the flag m_nProtectedDataParsed to indicate that the protected data
					//	is parsed
				m_nProtectedDataParsed =	1;

					//	reset the changed flags
				m_dwProtectedInformationChanged				=	0;

				m_dwPrivateKeysChanged						=	0;
				m_dwProtectedApplicationInformationChanged	=	0;
				m_dwInformationBlobChanged					=	0;
			}
			else
			{
//				hResult =	E_VS_PASSWORD_NOT_PROVIDED;
//				break;
			}
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_ReadDataIntoStructures ()


_VS_LONG	CProtectedStorage::m_FreeDataStructures
(
	_VS_DWORD			i_dwUpdateWhat
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_VS_DWORD				i;

	while (1)
	{
		//	free all the memory over here

		if ( UPDATE_ONLY_PLAINTEXT == i_dwUpdateWhat || UPDATE_ALL_IF_POSSIBLE == i_dwUpdateWhat )
		{
			if( NULL != m_pstructCertificateInformation )
			{
				for ( i = 0; i < m_dwNumberOfCertificates; i ++ )
				{
					VS_FREE_MEMORY(m_pstructCertificateInformation[i].pbyteCertificateBlob)
					VS_FREE_MEMORY_2D(m_pstructCertificateInformation[i].ppbyteCertificatePreferenceName, m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences)
					VS_FREE_MEMORY(m_pstructCertificateInformation[i].pdwCertificatePreferenceNameLength)
					VS_FREE_MEMORY_2D(m_pstructCertificateInformation[i].ppbyteCertificatePreferenceData, m_pstructCertificateInformation[i].dwNumberOfCertificatePreferences)
					VS_FREE_MEMORY(m_pstructCertificateInformation[i].pdwCertificatePreferenceDataLength)
				}
			}

			VS_FREE_MEMORY(m_pstructCertificateInformation)

			if( NULL != m_pstructPlainTextApplicationInformation )
			{
				for ( i = 0; i < m_dwNumberOfPlainTextApplications; i ++ )
				{
					VS_FREE_MEMORY(m_pstructPlainTextApplicationInformation[i].pbyteApplicationName)
					VS_FREE_MEMORY(m_pstructPlainTextApplicationInformation[i].pbyteApplicationHost)
					VS_FREE_MEMORY_2D(m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceName, m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences)
					VS_FREE_MEMORY(m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceNameLength)
					VS_FREE_MEMORY_2D(m_pstructPlainTextApplicationInformation[i].ppbyteApplicationPreferenceData, m_pstructPlainTextApplicationInformation[i].dwNumberOfApplicationPreferences)
					VS_FREE_MEMORY(m_pstructPlainTextApplicationInformation[i].pdwApplicationPreferenceDataLength)
				}
			}

			VS_FREE_MEMORY(m_pstructPlainTextApplicationInformation)

			if ( NULL != m_pCbdhProtectedInformation )
			{
				delete m_pCbdhProtectedInformation;
				m_pCbdhProtectedInformation =	NULL;
			}

			if ( NULL != m_pCbdhEntireStorage )
			{
				delete m_pCbdhEntireStorage;
				m_pCbdhEntireStorage =	NULL;
			}


					//	reset the numbers of certs, applications etc to 0
			m_dwNumberOfCertificates					=	0;
			m_dwNumberOfPlainTextApplications			=	0;

				//	reset all the changed flags to 0
			m_dwPlainTextInformationChanged				=	0;

			m_dwCertificateInformationChanged			=	0;
			m_dwPlainTextApplicationInformationChanged	=	0;
		}

		if ( UPDATE_ONLY_PROTECTED == i_dwUpdateWhat || UPDATE_ALL_IF_POSSIBLE == i_dwUpdateWhat )
		{
			if ( 1 == m_nPasswordProvided )
			{
				if( NULL != m_pstructProtectedApplicationInformation )
				{
					for ( i = 0; i < m_dwNumberOfProtectedApplications; i ++ )
					{
						VS_FREE_MEMORY(m_pstructProtectedApplicationInformation[i].pbyteApplicationName)
						VS_FREE_MEMORY(m_pstructProtectedApplicationInformation[i].pbyteApplicationHost)
						VS_FREE_MEMORY_2D(m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceName, m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences)
						VS_FREE_MEMORY(m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceNameLength)
						VS_FREE_MEMORY_2D(m_pstructProtectedApplicationInformation[i].ppbyteApplicationPreferenceData, m_pstructProtectedApplicationInformation[i].dwNumberOfApplicationPreferences)
						VS_FREE_MEMORY(m_pstructProtectedApplicationInformation[i].pdwApplicationPreferenceDataLength)
					}
				}

				VS_FREE_MEMORY(m_pstructProtectedApplicationInformation)

				if( NULL != m_pstructPrivateKeyInformation )
				{
					for ( i = 0; i < m_dwNumberOfPrivateKeys;i ++ )
					{
						VS_FREE_MEMORY(m_pstructPrivateKeyInformation[i].pbytePrivateKeyBlob)
						VS_FREE_MEMORY(m_pstructPrivateKeyInformation[i].pbyteAssociatedHash)
					}
				}

				VS_FREE_MEMORY(m_pstructPrivateKeyInformation)

				if( NULL != m_pstructInformationBlob )
				{
					for ( i = 0; i < m_dwNumberOfInformationBlobs;i ++ )
					{
						VS_FREE_MEMORY(m_pstructInformationBlob[i].pbyteInformationBlobData)
						VS_FREE_MEMORY(m_pstructInformationBlob[i].pbyteInformationBlobName)
					}
				}

				VS_FREE_MEMORY(m_pstructInformationBlob)

				VS_FREE_MEMORY(m_pbyteEncryptedProtectedInformation);
				VS_FREE_MEMORY(m_pbyteDecryptedProtectedInformation);


				if ( NULL != m_pCbdhProtectedInformation )
				{
					delete m_pCbdhProtectedInformation;
					m_pCbdhProtectedInformation =	NULL;
				}

				if ( NULL != m_pCbdhEntireStorage )
				{
					delete m_pCbdhEntireStorage;
					m_pCbdhEntireStorage =	NULL;
				}

					//	reset the numbers of keys, applications etc to 0
				m_dwNumberOfProtectedApplications			=	0;
				m_dwNumberOfPrivateKeys						=	0;
				m_dwNumberOfInformationBlobs				=	0;

					//	reset all the changed flags to 0
				m_dwProtectedInformationChanged				=	0;

				m_dwPrivateKeysChanged						=	0;
				m_dwProtectedApplicationInformationChanged	=	0;
				m_dwInformationBlobChanged					=	0;
			}
			else
			{
//				hResult =	E_VS_PASSWORD_NOT_PROVIDED;
//				break;
			}
		}

		VS_FREE_MEMORY(m_pbyteEntireStorage)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_FreeDataStructures ()


//
//	Anand	Apr 14, 2000		start
//
//	The conditional update of datastructures based on time stamps was getting too complicated.
//	moreover for roaming the data is to be read from memory block and so we cannot use the
//	time stamp.
//
//	This entire function is commented out and the same function is written below it.
//	if we find out that the thing is getting really slow then we might have to undo these changes.
//
/*
_VS_LONG	CProtectedStorage::m_UpdateDataStructuresIfNecessary
(
	_VS_DWORD			i_dwUpdateWhat
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	WIN32_FILE_ATTRIBUTE_DATA	FileInofrmation;

	FILETIME*				pFileTimeLastAccess	=	NULL;

	_VS_LONG				lTempTime			=	999;
	_VS_LONG				lTimeCompare		=	999;

	BOOL					bResult				=	FALSE;

	_bstr_t					tbstrFileName;

	while (1)
	{
		tbstrFileName =	m_szStorageFileName;

			//	get the time the file was last modified
		bResult =	::GetFileAttributesEx
					(
						tbstrFileName,
						GetFileExInfoStandard,
						(LPVOID) &FileInofrmation
					);
 		if ( TRUE != bResult )
		{
			hResult =	::GetLastError ();
			break;
		}

			//	depending on what is to be modified we will compare the time.
		switch ( i_dwUpdateWhat )
		{
			case	UPDATE_ONLY_PLAINTEXT:
				pFileTimeLastAccess =	&m_FileTimeLastModifiedPlainText;
				break;

			case	UPDATE_ONLY_PROTECTED:
				pFileTimeLastAccess =	&m_FileTimeLastModifiedProtected;
				break;

			case	UPDATE_ALL_IF_POSSIBLE:
						//	if both needs to be updated then we should compare the time 
						//	with least of the 2
						//
						//	e.g. if plaintext was modified at 23
						//	and the protected was modified at 40
						//	and the file was modified at      30
						//	then we should compare the file time with that of plain text and then
						//	update the structures
						//
				lTempTime =	::CompareFileTime
							(
								(const FILETIME *) &m_FileTimeLastModifiedPlainText,
								(const FILETIME *) &m_FileTimeLastModifiedProtected
							);

				if ( -1 == lTempTime )
				{
					pFileTimeLastAccess =	&m_FileTimeLastModifiedPlainText;
				}
				else
				{
					pFileTimeLastAccess =	&m_FileTimeLastModifiedProtected;
				}
				break;
		}	//	end		switch ( i_dwUpdateWhat )

			//	check if begin read/write has been called before
		if ( BEGIN_CALLED == m_dwBeginCalledBefore )
		{
					//	compare the time the file was modified with the time the file was modified during
					//	the previous begin read/write call
			lTimeCompare =	::CompareFileTime
							(
								(const FILETIME *) pFileTimeLastAccess,
								(const FILETIME *) &(FileInofrmation.ftLastWriteTime)
							);
			if ( -1 == lTimeCompare )
			{
					//	this means that the file was modified since the previous begin read/write call

					//	so free the data structures
				hResult =	m_FreeDataStructures ( i_dwUpdateWhat );
				VS_CHECK_HRESULT

					//	and fill them again
				hResult =	m_ReadDataIntoStructures ( i_dwUpdateWhat );
				VS_CHECK_HRESULT
			}	//	end		if ( -1 == lTimeCompare )

		}	//	end		if ( BEGIN_CALLED == m_dwBeginCalledBefore )
		else
		{
			//	this means that the begin read/write was not called before and this is the first time.

				//	so fill the data structures
			hResult =	m_ReadDataIntoStructures ( i_dwUpdateWhat );
			VS_CHECK_HRESULT

				//	set the begin called before flag
			m_dwBeginCalledBefore =	BEGIN_CALLED;
		}

				//	update the time stamps of the plaintext and/or the protected update
		if ( UPDATE_ONLY_PLAINTEXT == i_dwUpdateWhat || UPDATE_ALL_IF_POSSIBLE == i_dwUpdateWhat )
		{
					//	set the last modified time stamp
			::_VS_memcpy
			( 
				(void *) &m_FileTimeLastModifiedPlainText, 
				(const void *) &(FileInofrmation.ftLastWriteTime), 
				sizeof (FILETIME) 
			);
		}

		if ( UPDATE_ONLY_PROTECTED == i_dwUpdateWhat || UPDATE_ALL_IF_POSSIBLE == i_dwUpdateWhat )
		{
				//	set the last modified time stamp
			::_VS_memcpy
			( 
				(void *) &m_FileTimeLastModifiedProtected, 
				(const void *) &(FileInofrmation.ftLastWriteTime), 
				sizeof (FILETIME) 
			);
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_UpdateDataStructuresIfNecessary ()
*/


_VS_LONG	CProtectedStorage::m_UpdateDataStructuresIfNecessary
(
	_VS_DWORD			i_dwUpdateWhat
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
			//	check if begin read/write has been called before
		if ( BEGIN_CALLED == m_dwBeginCalledBefore )
		{
				//	so free the data structures
			hResult =	m_FreeDataStructures ( i_dwUpdateWhat );
			VS_CHECK_HRESULT

				//	and fill them again
			hResult =	m_ReadDataIntoStructures ( i_dwUpdateWhat );
			VS_CHECK_HRESULT
		}	//	end		if ( BEGIN_CALLED == m_dwBeginCalledBefore )
		else
		{
				//	so fill the data structures
			hResult =	m_ReadDataIntoStructures ( i_dwUpdateWhat );
			VS_CHECK_HRESULT

				//	set the begin called before flag
			m_dwBeginCalledBefore =	BEGIN_CALLED;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_UpdateDataStructuresIfNecessary ()


_VS_LONG	CProtectedStorage::m_UpdateStorageFileIfNecessary ()
{
	_VS_LONG				hResult					=	E_VS_FAIL;

	BOOL					bResult					=	0;

	DWORD					dwNumberOfBytesWritten	=	0;

	BOOL					bUpdateStorageFile		=	FALSE;

	_bstr_t					tbstrFileName;

	while (1)
	{
		if ( 1 != m_dwInitializeCalled )
		{
			hResult =	E_VS_INITIALIZE_NOT_CALLED;
			break;
		}

		if ( 0 < m_dwPlainTextInformationChanged )
		{
				//	this means that the plain text information is changed. so encode it
			hResult =	m_EncodePlainTextData ();
			VS_CHECK_HRESULT

			m_dwPlainTextInformationChanged = 0;	//	reset the flag
			bUpdateStorageFile	=	TRUE;
		}

		if ( 1 == m_nPasswordProvided )
		{
					//	if password is provided then we can also encode the protected informaiton
			if ( 0 < m_dwProtectedInformationChanged )
			{
					//	this means that the protected information is changed. so encode it
				hResult =	m_EncodeProtectedData ();
				VS_CHECK_HRESULT

				m_dwProtectedInformationChanged =	0;	//	reset the flag
				bUpdateStorageFile	=	TRUE;
			}
		}

		if ( TRUE == bUpdateStorageFile )
		{
				//	this variable indicates if the PS was changed after being initialized
				//	(Initialize/InitializeForRoaming).
			m_dwPSChangedAfterInitialized =	PS_CHANGED_AFTER_INITIALIZED;

						//	this function will encode the plain text information and the protected information
						//	into a sequence and store the entire data in a buffer
			hResult =	m_EncodeProtectedStorage ();
			VS_CHECK_HRESULT

			if ( PS_FILE == m_dwMemoryOrFile )	//	1
			{
					//	the storage is in a file. so update the file
#if PLATFORM==VSPS_WIN32
				tbstrFileName =	m_szStorageFileName;

					//	open the file in read mode
				m_hStorageFile =	::CreateFile
									(
										tbstrFileName,
										GENERIC_WRITE,
										0,
										NULL,
										OPEN_EXISTING,
										FILE_ATTRIBUTE_NORMAL,
										NULL
									);
				if ( INVALID_HANDLE_VALUE == m_hStorageFile )
				{
					hResult =	::GetLastError ();
					break;
				}

							//	write the buffer to the file
				bResult =	::WriteFile
						(
							m_hStorageFile,
							m_pbyteEntireStorage,
							m_dwEntireStorageSize,
							&dwNumberOfBytesWritten,
							NULL
						);
 				if ( TRUE != bResult )
				{
					hResult =	::GetLastError ();
					break;
				}

				bResult =	SetEndOfFile
							(
								m_hStorageFile
							);
				if ( TRUE != bResult )
				{
					hResult =	::GetLastError ();
					break;
				}

				::Sleep ( VSPS_SLEEP_MILLISECONDS );

							//	close the file
				bResult =	::CloseHandle
							(
								m_hStorageFile
							);
				m_hStorageFile =	NULL;
 				if ( TRUE != bResult )
				{
					hResult =	::GetLastError ();
					break;
				}

#else
//	undeclared = 0;
#endif
			}	//	end		if ( PS_FILE == m_dwMemoryOrFile )
			else
			{
						//	this means that the storage was in meomory. so update the memory block
						//	m_dwMemoryOrFile = PS_MEMORY (2)

					//	free current contents of the buffer
//				VS_FREE_MEMORY (m_pbyteRoamingBuffer)

					//	allocate memory and copy the entire storage
					//
					//	NOTE:	the memory is explicitly copied instead of just fixing the pointers
					//			because the code to free the memory is same in case of file storage
					//			and memory storage
					//
				*m_pdwRoamingBufferLen =	m_dwEntireStorageSize;

				if ( NULL != (*m_ppbyteRoamingBuffer) )
				{
					delete [] *m_ppbyteRoamingBuffer;
				}

				(*m_ppbyteRoamingBuffer) = new BYTE [*m_pdwRoamingBufferLen];
				VS_CHECK_ALLOCATED_MEMORY ( (*m_ppbyteRoamingBuffer) )

				memcpy
				(
					(*m_ppbyteRoamingBuffer),
					m_pbyteEntireStorage,
					*m_pdwRoamingBufferLen
				);

//				VS_ALLOC_AND_BYTEBLOB_COPY (m_pbyteRoamingBuffer, m_pbyteEntireStorage, m_dwRoamingBufferLen)

				m_dwRoamingBufferChanged = 1;
			}

				//	this variable indicates if the PS was changed after being initialized
				//	(Initialize/InitializeForRoaming).
			m_dwPSChangedAfterInitialized =	PS_CHANGED_AFTER_INITIALIZED;


		}	//	end		if ( TRUE == bUpdateStorageFile )

//
//	Anand	Apr 09, 2000
//	the data structures should not be freed because the next time the BeginRead/BeginWrite is called
//	the data structures are updated only if the file time stamp is changed.
//
//		hResult =	m_FreeDataStructures ( UPDATE_ALL_IF_POSSIBLE );
//		VS_CHECK_HRESULT

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_UpdateStorageFileIfNecessary ()


/*
_VS_LONG	CProtectedStorage::m_BlockDueToContention
(
	const	_VS_DWORD	i_cnMode,
	const	_VS_DWORD	i_cnWaitTime,
	const	_VS_DWORD	i_cnWhatsBlocked
)
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_BlockDueToContention
*/


_VS_LONG	CProtectedStorage::m_CreateConcurrencyObjects ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	_bstr_t					tbstrNamePrefix = "";
	_bstr_t					tbstrMutexName;
	_bstr_t					tbstrSemaphoreName;
	_bstr_t					tbstrFileName = "";

	_VS_BYTE*				pbyteHashData		=	NULL;
	_VS_DWORD				dwHashDataLength	=	0;

	while (1)
	{
#ifdef	_VS_MSG_BOX_
		::MessageBox (NULL, "Enter m_CreateConcurrencyObjects", "ProtectedStorage", MB_OK);
#endif
		if ( PS_FILE == m_dwMemoryOrFile )	//	1
		{
						//	hash the storage file name
			hResult =	m_HashData
						(
							(_VS_BYTE*) m_szStorageFileName,
							( (_VS_strlenW(m_szStorageFileName) + 1) * sizeof (_VS_CHAR) ),
							&pbyteHashData,
							&dwHashDataLength
						);
			VS_CHECK_HRESULT;
		}
		else
		{
				//	m_dwMemoryOrFile = PS_MEMORY (2)
			hResult =	m_HashData
						(
							(_VS_BYTE*) m_szRoamingStorageName,
							( (_VS_strlenW(m_szRoamingStorageName) + 1) * sizeof (_VS_CHAR) ),
							&pbyteHashData,
							&dwHashDataLength
						);
			VS_CHECK_HRESULT
		}

		BytesToAscHex
		(
			pbyteHashData,
			dwHashDataLength,
			tbstrNamePrefix
		);

//		m_VS_strcpyW ( szReadMutexName, tbstrNamePrefix );
//		m_VS_strcpyW ( szWriteSemaphoreName, tbstrNamePrefix );

//		m_VS_strcatW ( szReadMutexName, VSPS_READ_MUTEX_NAME );
//		m_VS_strcatW ( szWriteSemaphoreName, VSPS_WRITE_MUTEX_NAME );

				//	create the read mutex
		tbstrMutexName =	tbstrNamePrefix;
		tbstrMutexName +=	VSPS_READ_MUTEX_NAME;

		m_hReadMutex	=	::CreateMutex
							(
								NULL,
								FALSE,
								tbstrMutexName
							);
		if ( NULL == m_hReadMutex )
		{
				//	error creating the mutex. so return error
			hResult =	E_VS_MUTEX;
			break;
		}


		tbstrSemaphoreName =	tbstrNamePrefix;
		tbstrSemaphoreName +=	VSPS_WRITE_MUTEX_NAME;

				//	create the write semaphore
		m_hWriteSemaphore =	::CreateSemaphore
							(
								NULL,
								INITIAL_WRITE_SEMAPHORE_COUNT,
								MAX_WRITE_SEMAPHORE_COUNT,
								tbstrSemaphoreName
							);

		if ( NULL == m_hWriteSemaphore )
		{
			hResult =	E_VS_SEMAPHORE;
			break;
		}

		tbstrFileName =		tbstrNamePrefix;
		tbstrFileName +=	MEMORY_MAPPED_FILE_NAME;

		m_hMemoryMappedFile =	::CreateFileMapping
								(
									(HANDLE) 0xFFFFFFFF,
									NULL,
									PAGE_READWRITE,
									0,
									MEMORY_MAPPED_FILE_SIZE,
									(LPCTSTR) tbstrFileName
								);
		if ( NULL == m_hMemoryMappedFile )
		{
			hResult =	::GetLastError ();
			break;
		}

#ifdef	_VS_MSG_BOX_
		::MessageBox (NULL, "m_CreateConcurrencyObjects Success", "ProtectedStorage", MB_OK);
#endif

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY(pbyteHashData)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CreateConcurrencyObjects ()


_VS_LONG	CProtectedStorage::m_CleanPIDList
(
	_VS_DWORD*	o_pdwNumberOfReadProcesses,
	_VS_DWORD*	o_pdwNumberOfWriteProcesses
)
{
	HRESULT				hResult				=	E_VS_FAIL;
	BOOL				bResult				=	FALSE;

	void*				pvoidMappedFile		=	NULL;

	_VS_DWORD*			pdwNumberOfReadProcesses	=	NULL;
	_VS_DWORD*			pdwWriteProcessPID			=	NULL;
	_VS_DWORD*			pdwReadProcessPID			=	NULL;

	_VS_DWORD			dwNumberOfLiveReadProcesses	=	0;

//	_VS_DWORD			dwPID;

	int					i							=	0;

	_VS_DWORD*			pdwLiveReadProcessPID		=	NULL;
	_VS_LONG			lPreviousCount				=	9999;

	HANDLE				hReadProcess				=	NULL;

	HANDLE				hWriteProcess				=	NULL;

	while (1)
	{
		*o_pdwNumberOfReadProcesses		=	0;
		*o_pdwNumberOfWriteProcesses	=	0;

							//	map the view of the file.
		pvoidMappedFile =	::MapViewOfFile
							(
								m_hMemoryMappedFile,
								FILE_MAP_WRITE,
								0,
								0,
								MEMORY_MAPPED_FILE_SIZE
							);
		if ( NULL == pvoidMappedFile )
		{
			hResult =	::GetLastError ();
			break;
		}

				//	the first dword ([0])in the mapped file will be the number of read processes
		pdwNumberOfReadProcesses	=	(_VS_DWORD*) pvoidMappedFile;

				//	the second dword ([1]) in the file mapped file will be the PID of the wirte process
		pdwWriteProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + sizeof (_VS_DWORD);

				//	third dword ([2]) onwards is the list of PID of read processes
		pdwReadProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + (2 * sizeof (_VS_DWORD));

		if ( 0 != *pdwNumberOfReadProcesses )
		{
				//	if number of read processes is more than one.

				//	initialize the number of live processes to 0
			dwNumberOfLiveReadProcesses	=	0;

				//	allocate memory for the number of live processes PIDs. the memory is initialized to 0
				//	by the function.
			pdwLiveReadProcessPID		=	(_VS_DWORD*) m_VS_HeapAlloc
											(
												*pdwNumberOfReadProcesses * sizeof (_VS_DWORD)
											);

			for ( i = 0; i < (int) *pdwNumberOfReadProcesses; i++ )
			{
					//	for all the processes

				hReadProcess =	NULL;

								//	try to open the process
				hReadProcess =	::OpenProcess 
								(
									PROCESS_QUERY_INFORMATION, 
									FALSE, 
									pdwReadProcessPID [i]
								);
				if ( NULL == hReadProcess )
				{
					hResult =	::GetLastError ();

							//	if error = 0x00000057 then it means that the process does not exist.
							//	this in turn means that the process has crashed. so should not
							//	put this PID in the new array.

							//	but if we get some other error then it means that the process is live
							//	but we were not able to get the handle to the process.
					if ( 0x00000057 != hResult )
					{
						pdwLiveReadProcessPID [dwNumberOfLiveReadProcesses] = pdwReadProcessPID [i];
						dwNumberOfLiveReadProcesses ++;
					}
				}
				else
				{
							//	the OpenProcess call succeeded. so add the PID to the new list
					pdwLiveReadProcessPID [dwNumberOfLiveReadProcesses] = pdwReadProcessPID [i];
					dwNumberOfLiveReadProcesses ++;

							//	close the handle to the process
					::CloseHandle (hReadProcess);
				}
			}	//	end		for ( i = 0; i < *pdwNumberOfReadProcesses; i++ )

				//	if the two numbers are same then it means that all the processes were alive.
			if ( dwNumberOfLiveReadProcesses != *pdwNumberOfReadProcesses )
			{
				//	if they are different then

				//	copy the new array to the old array.
				//
				//	NOTE:	the unused members of the new array are initialized to zero. so its not a problem.
				//			moreover the number of valid elements in this array is also changed in the next step.
				//
				::_VS_memcpy
				(
					pdwReadProcessPID,
					pdwLiveReadProcessPID,
					*pdwNumberOfReadProcesses * sizeof (_VS_DWORD)
				);

					//	number of read processes is adjusted
				*pdwNumberOfReadProcesses = dwNumberOfLiveReadProcesses;

				if ( 0 == dwNumberOfLiveReadProcesses )
				{
						//	this means that the last read process has crashed.
						//	it was the job of the last read process to release
						//	the WriteSemaphore which was not done. so

								//	release the write semaphore
					bResult =	::ReleaseSemaphore
								(
									m_hWriteSemaphore,
									1,
									&lPreviousCount
								);
					VS_CHECK_BRESULT
				}
			}

				//	put the number of live read processes in teh out parameter
			*o_pdwNumberOfReadProcesses =	dwNumberOfLiveReadProcesses;

		}	//	end		if ( 0 == *pdwNumberOfReadProcesses )
		else
		{
				//	as the number of read processes is 0 
				//	lets check if any write processes are regsitered.
				
			if ( 0 != *pdwWriteProcessPID )
			{
					//	this means that a write process is using the storage

					//	check if the write process is alive

							//	try to open the process
				hWriteProcess =	::OpenProcess 
								(
									PROCESS_QUERY_INFORMATION, 
									FALSE, 
									pdwWriteProcessPID [i]
								);
				if ( NULL == hWriteProcess )
				{
					hResult =	::GetLastError ();

							//	if error = 0x00000057 then it means that the process does not exist.
							//	this in turn means that the process has crashed. 
					if ( 0x00000057 == hResult )
					{
						*pdwWriteProcessPID =	0;

									//	release the write semaphore
						bResult =	::ReleaseSemaphore
									(
										m_hWriteSemaphore,
										1,
										&lPreviousCount
									);
						VS_CHECK_BRESULT
					}
					else
					{
						*o_pdwNumberOfWriteProcesses =	1;
					}
				}
				else
				{
					*o_pdwNumberOfWriteProcesses =	1;

						//	close the handle to the process
					::CloseHandle (hReadProcess);
				}
			}
		}	//	end else

		::UnmapViewOfFile ( pvoidMappedFile );

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY(pdwLiveReadProcessPID)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CleanPIDList ()


_VS_LONG	CProtectedStorage::m_AddToPIDList ()
{
	HRESULT				hResult				=	E_VS_FAIL;

	void*				pvoidMappedFile		=	NULL;

	_VS_DWORD*			pdwNumberOfReadProcesses	=	NULL;
	_VS_DWORD*			pdwWriteProcessPID			=	NULL;
	_VS_DWORD*			pdwReadProcessPID			=	NULL;

//	int					i							=	0;

	_VS_DWORD			dwPID						=	0;

//	_VS_DWORD			dwAlreadyExisitng			=	0;

	while (1)
	{
							//	map the view of the file.
		pvoidMappedFile =	::MapViewOfFile
							(
								m_hMemoryMappedFile,
								FILE_MAP_WRITE,
								0,
								0,
								MEMORY_MAPPED_FILE_SIZE
							);
		if ( NULL == pvoidMappedFile )
		{
			hResult =	::GetLastError ();
			break;
		}

				//	the first dword ([0])in the mapped file will be the number of read processes
		pdwNumberOfReadProcesses	=	(_VS_DWORD*) pvoidMappedFile;

				//	the second dword ([1]) in the file mapped file will be the PID of the wirte process
		pdwWriteProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + sizeof (_VS_DWORD);

				//	third dword ([2]) onwards is the list of PID of read processes
		pdwReadProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + (2 * sizeof (_VS_DWORD));

		dwPID =	::GetCurrentProcessId ();

				//	check if no write process is registered
		if ( 0 != *pdwWriteProcessPID )
		{
			hResult =	E_CANNOT_ADD_READ;
			break;
		}

//
//	Anand	Jul 08, 2000 start
//
//	the same PID was not added to the list if it was already existing. this is changed.
//	now the same PID is added multiple times.
//
/*
			//	for all the read processes
		for ( i = 0; i < (int) *pdwNumberOfReadProcesses; i++ )
		{

			if ( dwPID == pdwReadProcessPID [i] )
			{
					//	if the PID already esists then turn the flag on
				dwAlreadyExisitng =	1;
					//	and break out of the for loop
				break;
			}
		}

		if ( 0 == dwAlreadyExisitng )
		{
				//	add PID to the list
			pdwReadProcessPID [i] = dwPID;

				//	increment the number of read processes
			(*pdwNumberOfReadProcesses) ++;
		}
*/
		
			//	add PID to the list
		pdwReadProcessPID [*pdwNumberOfReadProcesses] = dwPID;

			//	increment the number of read processes
		(*pdwNumberOfReadProcesses) ++;
//
//	Anand	Jul 08, 2000		end
//

		::UnmapViewOfFile ( pvoidMappedFile );

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_AddToPIDList ()


_VS_LONG	CProtectedStorage::m_DeleteFromPIDList
(
	_VS_DWORD*			o_pdwNumberOfReadProcesses
)
{
	HRESULT				hResult				=	E_VS_FAIL;

	void*				pvoidMappedFile		=	NULL;

	_VS_DWORD*			pdwNumberOfReadProcesses	=	NULL;
	_VS_DWORD*			pdwWriteProcessPID			=	NULL;
	_VS_DWORD*			pdwReadProcessPID			=	NULL;

	int					i							=	0;

	_VS_DWORD			dwPID						=	0;

//	_VS_DWORD			dwAlreadyExisitng			=	0;

	_VS_DWORD			dwNumberOfLiveReadProcesses	=	0;
	_VS_DWORD*			pdwLiveReadProcessPID		=	NULL;

	DWORD				dwOnePIDRemoved				=	0;

	while (1)
	{
		*o_pdwNumberOfReadProcesses =	0;

							//	map the view of the file.
		pvoidMappedFile =	::MapViewOfFile
							(
								m_hMemoryMappedFile,
								FILE_MAP_WRITE,
								0,
								0,
								MEMORY_MAPPED_FILE_SIZE
							);
		if ( NULL == pvoidMappedFile )
		{
			hResult =	::GetLastError ();
			break;
		}

				//	the first dword ([0])in the mapped file will be the number of read processes
		pdwNumberOfReadProcesses	=	(_VS_DWORD*) pvoidMappedFile;

				//	the second dword ([1]) in the file mapped file will be the PID of the wirte process
		pdwWriteProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + sizeof (_VS_DWORD);

				//	third dword ([2]) onwards is the list of PID of read processes
		pdwReadProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + (2 * sizeof (_VS_DWORD));

		dwPID =	::GetCurrentProcessId ();

			//	initialize the number of live processes to 0
		dwNumberOfLiveReadProcesses	=	0;

			//	allocate memory for the number of live processes PIDs. the memory is initialized to 0
			//	by the function.
		pdwLiveReadProcessPID		=	(_VS_DWORD*) m_VS_HeapAlloc
										(
											*pdwNumberOfReadProcesses * sizeof (_VS_DWORD)
										);

//
//	Anand	Jul 08, 2000 start
//
//	the same PID was not added to the list if it was already existing. this is changed.
//	now the same PID is added multiple times.
//	so we want to delete only one PID from the list. the dwOnePIDRemoved flag will indicate
//	this
//

			//	for all the read processes
		for ( i = 0; i < (int) *pdwNumberOfReadProcesses; i++ )
		{
			if ( (dwPID != pdwReadProcessPID [i]) || (1 == dwOnePIDRemoved) )
			{
				pdwLiveReadProcessPID [dwNumberOfLiveReadProcesses] = pdwReadProcessPID [i];
				dwNumberOfLiveReadProcesses ++;
			}
			else
			{
				dwOnePIDRemoved =	1;
			}
		}
//
//	Anand	Jul 08, 2000 end
//

		::_VS_memcpy
		(
			pdwReadProcessPID,
			pdwLiveReadProcessPID,
			*pdwNumberOfReadProcesses * sizeof (_VS_DWORD)
		);

			//	number of read processes is adjusted
		*pdwNumberOfReadProcesses = dwNumberOfLiveReadProcesses;

		*o_pdwNumberOfReadProcesses =	dwNumberOfLiveReadProcesses;
				
		::UnmapViewOfFile ( pvoidMappedFile );

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY(pdwLiveReadProcessPID)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DeleteFromPIDList ()



_VS_LONG	CProtectedStorage::m_SetWritePID ()
{
	HRESULT				hResult				=	E_VS_FAIL;

	void*				pvoidMappedFile		=	NULL;

	_VS_DWORD*			pdwNumberOfReadProcesses	=	NULL;
	_VS_DWORD*			pdwWriteProcessPID			=	NULL;
	_VS_DWORD*			pdwReadProcessPID			=	NULL;

	_VS_DWORD			dwPID						=	0;

	while (1)
	{
							//	map the view of the file.
		pvoidMappedFile =	::MapViewOfFile
							(
								m_hMemoryMappedFile,
								FILE_MAP_WRITE,
								0,
								0,
								MEMORY_MAPPED_FILE_SIZE
							);
		if ( NULL == pvoidMappedFile )
		{
			hResult =	::GetLastError ();
			break;
		}

				//	the first dword ([0])in the mapped file will be the number of read processes
		pdwNumberOfReadProcesses	=	(_VS_DWORD*) pvoidMappedFile;

				//	the second dword ([1]) in the file mapped file will be the PID of the wirte process
		pdwWriteProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + sizeof (_VS_DWORD);

				//	third dword ([2]) onwards is the list of PID of read processes
		pdwReadProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + (2 * sizeof (_VS_DWORD));

		dwPID =	::GetCurrentProcessId ();

				//	check if no read and write process is registered
		if ( 0 == *pdwNumberOfReadProcesses && 0 == *pdwWriteProcessPID )
		{
			*pdwWriteProcessPID =	dwPID;
		}
		else
		{
			hResult =	E_CANNOT_ADD_WRITE;
			break;
		}

		::UnmapViewOfFile ( pvoidMappedFile );

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_SetWritePID ()


_VS_LONG	CProtectedStorage::m_ResetWritePID ()
{
	HRESULT				hResult				=	E_VS_FAIL;

	void*				pvoidMappedFile		=	NULL;

	_VS_DWORD*			pdwNumberOfReadProcesses	=	NULL;
	_VS_DWORD*			pdwWriteProcessPID			=	NULL;
	_VS_DWORD*			pdwReadProcessPID			=	NULL;

	_VS_DWORD			dwPID						=	0;

//	_VS_DWORD			dwAlreadyExisitng			=	0;

	while (1)
	{
							//	map the view of the file.
		pvoidMappedFile =	::MapViewOfFile
							(
								m_hMemoryMappedFile,
								FILE_MAP_WRITE,
								0,
								0,
								MEMORY_MAPPED_FILE_SIZE
							);
		if ( NULL == pvoidMappedFile )
		{
			hResult =	::GetLastError ();
			break;
		}

				//	the first dword ([0])in the mapped file will be the number of read processes
		pdwNumberOfReadProcesses	=	(_VS_DWORD*) pvoidMappedFile;

				//	the second dword ([1]) in the file mapped file will be the PID of the wirte process
		pdwWriteProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + sizeof (_VS_DWORD);

				//	third dword ([2]) onwards is the list of PID of read processes
		pdwReadProcessPID			=	(_VS_DWORD*) (pvoidMappedFile) + (2 * sizeof (_VS_DWORD));

		dwPID =	::GetCurrentProcessId ();

		if ( *pdwWriteProcessPID == dwPID )
		{
			*pdwWriteProcessPID =	0;
		}

		::UnmapViewOfFile ( pvoidMappedFile );

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_ResetWritePID ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_CreateKeyFromPasswordHash
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//		E_VS_HASH				-	error during hashing
//		E_VS_OUT_OF_MEMORY		-	low on memory
//
//	Description		:	the function will use the password and get the hash based
//						on that password.
//
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_CreateKeyFromPasswordHash ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
			//	the length of the RC4 key is 128 bits = 16 bytes
		m_ItemRC4Key.len =	16;

			//	so copy the first 16 bytes of the data as the RC4 key
		VS_ALLOC_AND_BYTEBLOB_COPY (m_ItemRC4Key.data, m_pbytePasswordHash, m_ItemRC4Key.len)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CreateKeyFromPasswordHash ()


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	m_DestroyKeyFromPassword 
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS				-	on success
//
//	Description		:	the function delete the key generated form the hash of the password
//
//
///////////////////////////////////////////////////////////////////////////////
_VS_LONG	CProtectedStorage::m_DestroyKeyFromPassword ()
{
	_VS_LONG				hResult				=	E_VS_FAIL;

	while (1)
	{
		m_VS_HeapFree ( (void*) m_ItemRC4Key.data );

		m_ItemRC4Key.data	=	NULL;
		m_ItemRC4Key.len	=	0;

		m_VS_HeapFree ( (void*) m_ItemNewRC4Key.data );
		m_ItemNewRC4Key.data	=	NULL;
		m_ItemNewRC4Key.len		=	0;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_DestroyKeyFromPassword ()


void	CProtectedStorage::m_InitializeMembers ()
{
	m_szApplicationName								=	NULL;
	m_szApplicationHost								=	NULL;
	m_dwIsApplicationEncrypted						=	0;
	m_szStorageFileName								=	NULL;
//	m_szPassword									=	NULL;
	m_pbytePasswordHash								=	NULL;

	m_pbyteSalt										=	NULL;
	m_dwSaltLen										=	0;
	m_dwIterationCount								=	0;

	m_nCreateOpenFlag								=	0;

	m_nPasswordProvided								=	0;
	m_nProtectedDataParsed;

	m_pbyteEntireStorage							=	NULL;
	m_dwEntireStorageSize							=	0;

	m_dwNumberOfPlainTextApplications				=	0;
	m_dwNumberOfProtectedApplications				=	0;

	m_dwPasswordStrength							=	0;
	m_dwNumberOfPrivateKeys							=	0;
	m_dwNumberOfCertificates						=	0;
	m_dwNumberOfInformationBlobs					=	0;

	m_pstructDERTreePlainTextInformation			=	NULL;
	m_pstructDERTreeEncryptedProtectedInformation	=	NULL;
	m_pstructDERTreeProtectedInformation			=	NULL;

	m_pstructDERTreePlainTextApplication			=	NULL;
	m_pstructDERTreeCertificates					=	NULL;

	m_pstructDERTreePrivateKeys						=	NULL;
	m_pstructDERTreeProtectedApplication			=	NULL;
	m_pstructDERTreeInformationBlobs				=	NULL;

	m_pstructCertificateInformation					=	NULL;
	
	m_pstructPlainTextApplicationInformation		=	NULL;
	m_pstructProtectedApplicationInformation		=	NULL;

	m_pstructPrivateKeyInformation					=	NULL;
	m_pstructInformationBlob						=	NULL;

	m_pbyteVeriSignConstant							=	NULL;
	m_pbyteEncryptedVeriSignConstant				=	NULL;

	m_dwPSFirstVersionNumber						=	0;
	m_dwPSSecondVersionNumber						=	0;
	m_dwPSThirdVersionNumber						=	0;
	m_dwPSFourthVersionNumber						=	0;

	m_dwPTAFirstVersionNumber						=	0;
	m_dwPTASecondVersionNumber						=	0;
	m_dwPTAThirdVersionNumber						=	0;
	m_dwPTAFourthVersionNumber						=	0;

	m_dwPlainTextInformationChanged					=	0;
	m_dwProtectedInformationChanged					=	0;
//	m_dwEncryptedProtectedInformationChanged		=	0;

	m_dwCertificateInformationChanged				=	0;
	m_dwPlainTextApplicationInformationChanged		=	0;
	m_dwPrivateKeysChanged							=	0;
	m_dwProtectedApplicationInformationChanged		=	0;
	m_dwInformationBlobChanged						=	0;

	m_pbyteDecryptedProtectedInformation			=	NULL;
	m_dwDecryptedProtectedInformationLength			=	0;

	m_pbyteEncryptedProtectedInformation			=	NULL;
	m_dwEncryptedProtectedInformationLength			=	0;

#if PLATFORM==VSPS_WIN32
	m_hStorageFile									=	NULL;
//	m_hMutex										=	NULL;
	m_hMemoryMappedFile								=	NULL;
#endif

	m_hHeap											=	NULL;

	m_dwInitializeCalled							=	0;
	m_dwInitializeSuccessful						=	0;

	m_longTimePasswordProvided						=	0;
	m_dwPasswordTimeOutIntervalInSeconds			=	0;

	m_dwBeginCalledBefore							=	0;
	m_dwBeginReadCalled								=	0;
	m_dwBeginWriteCalled							=	0;

//	m_hReadSemaphore								=	NULL;
	m_hWriteSemaphore								=	NULL;
	m_hReadMutex									=	NULL;

	m_dwDontDestroyMembers							=	0;

	m_dwMemoryOrFile								=	0;
	m_szRoamingStorageName							=	NULL;
	m_ppbyteRoamingBuffer							=	NULL;
	m_pdwRoamingBufferLen							=	NULL;
	m_dwRoamingBufferChanged						=	0;

	m_pSetPasswordFunctionPointer					=	NULL;
	m_pvoidPasswordFunctionData						=	NULL;

	m_pCbdhProtectedInformation						=	NULL;
	m_pCbdhEntireStorage							=	NULL;

	m_dwPSChangedAfterInitialized					=	0;

	m_ItemNewRC4Key.data							=	NULL;
	m_ItemNewRC4Key.len								=	0;
	m_ItemRC4Key.data								=	NULL;
	m_ItemRC4Key.len								=	0;

		//	Use fixed RC4 key to encrypt/decrypt protected data in roaming profiles
		//  managed by new Roaming 6.0 server
	m_boolUseFixedKey = FALSE;

	m_ItemRoamRC4Key.len =	VSPS_ROAMING_KEY_LEN;
	m_ItemRoamRC4Key.data = (BYTE *) VSPS_ROAMING_KEY;

	return;
}


void	CProtectedStorage::m_DestroyMembers ()
{
	if ( NULL != m_hHeap )
	{
		VS_FREE_MEMORY(m_szApplicationName);
		VS_FREE_MEMORY(m_szApplicationHost);

		VS_FREE_MEMORY(m_szStorageFileName);
	//	VS_FREE_MEMORY(m_szPassword);
		VS_FREE_MEMORY(m_pbytePasswordHash);

		VS_FREE_MEMORY(m_pbyteEntireStorage);

	//	VS_FREE_MEMORY(m_pstructCertificateInformation);
		
	//	VS_FREE_MEMORY(m_pstructPlainTextApplicationInformation);
	//	VS_FREE_MEMORY(m_pstructProtectedApplicationInformation);

	//	VS_FREE_MEMORY(m_pstructPrivateKeyInformation);
	//	VS_FREE_MEMORY(m_pstructInformationBlob);

		VS_FREE_MEMORY(m_pbyteVeriSignConstant);
		VS_FREE_MEMORY(m_pbyteEncryptedVeriSignConstant);

		m_FreeDataStructures( UPDATE_ALL_IF_POSSIBLE );

		VS_FREE_MEMORY (m_pbyteSalt)


#if PLATFORM==VSPS_WIN32
			if ( NULL != m_hStorageFile )
			{
				::CloseHandle ( m_hStorageFile );
				m_hStorageFile		=	NULL;
			}

	/*		if ( NULL != m_hMutex )
			{
				::CloseHandle ( m_hMutex );
				m_hMutex =	NULL;
			}*/

			if ( NULL != m_hMemoryMappedFile )
			{
				::CloseHandle ( m_hMemoryMappedFile );
				m_hMemoryMappedFile =	NULL;
			}


	//		if ( NULL != m_hReadSemaphore )
	//		{
	//			::CloseHandle ( m_hReadSemaphore );
	//			m_hReadSemaphore =	NULL;
	//		}

			if ( NULL != m_hWriteSemaphore )
			{
				::CloseHandle ( m_hWriteSemaphore );
				m_hWriteSemaphore =	NULL;
			}

			if ( NULL != m_hReadMutex )
			{
				::CloseHandle ( m_hReadMutex );
				m_hReadMutex =	NULL;
			}
#endif

//		VS_FREE_MEMORY(*m_ppbyteRoamingBuffer);
//		delete [] (*m_ppbyteRoamingBuffer);
		VS_FREE_MEMORY(m_szRoamingStorageName);

		m_VS_HeapDestroy();
	}	//	end		if ( NULL != m_hHeap )

	if ( NULL != m_pCbdhProtectedInformation )
	{
		delete m_pCbdhProtectedInformation;
		m_pCbdhProtectedInformation =	NULL;
	}

	if ( NULL != m_pCbdhEntireStorage )
	{
		delete m_pCbdhEntireStorage;
		m_pCbdhEntireStorage =	NULL;
	}

	return;
}


void	CProtectedStorage::m_VS_strcpyW
(
	_VS_CHAR*			o_szDestination,
	const _VS_CHAR*		i_cszSource
)
{
	_VS_memcpy
	(
		(BYTE*) o_szDestination,
		(const BYTE*) i_cszSource,
		( (_VS_strlenW ( i_cszSource ) + 1) * sizeof (_VS_CHAR) )
	);

	return;
}


void	CProtectedStorage::m_VS_strcatW
(
	_VS_CHAR*			o_szDestination,
	const _VS_CHAR*		i_cszSource
)
{
	DWORD	dwDestinationLen			=	_VS_strlenW (o_szDestination);

	_VS_memcpy
	(
		(BYTE*) (&(o_szDestination [dwDestinationLen])),
		(const BYTE*)	i_cszSource,
		( (_VS_strlenW ( i_cszSource ) + 1) * sizeof (_VS_CHAR) )
	);

	return;
}

void	CProtectedStorage::m_GetPathFromFileName
(
	_VS_CHAR*			i_szFileName,
	_VS_CHAR*			o_szPath
)
{
	DWORD				dwFileNameLen			=	0;
	DWORD				i;

	_VS_CHAR			szFile [MAX_PATH];

	m_VS_strcpyW (szFile, i_szFileName);

	dwFileNameLen =	_VS_strlenW (szFile);

	for ( i = dwFileNameLen - 1; i >= 0; i -- )
	{
		if ( szFile [i] == L'\\' )
		{
			szFile [i] = L'\0';
			break;
		}
	}

	m_VS_strcpyW ( o_szPath, szFile );

	return;
}



// Create all the directories in the path
BOOL	CProtectedStorage::m_CreateRecursiveDirectory
(
	_VS_CHAR* i_szDirToCreate
)
{
	WIN32_FIND_DATA wfd;
	_bstr_t			tbstrDirectory;
	_VS_DWORD		dwDirectoryLen;

	tbstrDirectory =	i_szDirToCreate;
	dwDirectoryLen = _VS_strlenW ( tbstrDirectory );	

	if(dwDirectoryLen == 2)       // root dirs "a:"
		return TRUE;

	HANDLE hDir = FindFirstFile(tbstrDirectory, &wfd);
	if(hDir != INVALID_HANDLE_VALUE)
	{
			FindClose(hDir);
			return TRUE;
	}

	_VS_CHAR szDirParent[MAX_PATH];

	m_VS_strcpyW(szDirParent, tbstrDirectory);

	for ( int i = dwDirectoryLen - 1; i >= 0; i -- )
	{
		if ( szDirParent [i] == L'\\' )
		{
			szDirParent [i] = L'\0';
			break;
		}
	}

	if(m_CreateRecursiveDirectory(szDirParent))
			if(CreateDirectory(tbstrDirectory, NULL))
			{
					return TRUE;
			}
			else
					return FALSE;

	return FALSE;
}


int		CProtectedStorage::BytesToAscHex
(
	unsigned char* byteHashVal, 
	int nHashValSize, 
	_bstr_t& tbstrAscHexMD5
)
{
	tbstrAscHexMD5 = "";
	char szDigitAscVal[] = "0123456789ABCDEF";
	char szDigit[2];

	szDigit[1] = '\0';
	for(int i=0;i<nHashValSize;++i)
	{
		szDigit[0] = szDigitAscVal[((byteHashVal[i] & 0xF0)>>4)];
		tbstrAscHexMD5 = tbstrAscHexMD5 + szDigit;
		szDigit[0] = szDigitAscVal[(byteHashVal[i] & 0x0F)];
		tbstrAscHexMD5 = tbstrAscHexMD5 + szDigit;
	}

	return 1;
}

/*
void	CProtectedStorage::m_EraseMemory
(
	void*				i_pMemoryBlock,
	_VS_DWORD			i_dwMemoryBlockSize
)
{
	::memset ( i_pMemoryBlock, '0', i_dwMemoryBlockSize );
	return;
}
*/


_VS_LONG	CProtectedStorage::m_CreateKeyFromPasswordSaltIterationCount ()
{
	HRESULT						hResult						=	E_FAIL;
	_DWORD						i							=	0;

	_BYTE*						pbytePasswordSalt			=	NULL;

			//	since the hash is passed through an iterator
			//	lets call the data members new hash and old hash
	_VS_BYTE*					pbyteNewHash				=	NULL;
	_VS_DWORD					dwNewHashLen				=	0;
	_VS_BYTE*					pbyteOldHash				=	NULL;
	_VS_DWORD					dwOldHashLen				=	0;

	while (1)
	{
			//	allocate memory for old hash
			//	this buffer will be reused as the output will be copied into it.
			//	memory is not allocated for the new hash because the hash function does it.
			//	so after each iteration the new hash is copied into the old hash and the new hash
			//	is deleted

		pbyteOldHash =	(_BYTE*) m_VS_HeapAlloc
						(
							SHA1_HASH_LENGTH
						);
		VS_CHECK_ALLOCATED_MEMORY(pbyteOldHash)

		dwOldHashLen	=	SHA1_HASH_LENGTH;


			//	allocate memory for the Password hash + Salt blob
			//	this is hashed multiple times
		pbytePasswordSalt =	(_BYTE*) m_VS_HeapAlloc
							(
								(const _VS_DWORD) ( SHA1_HASH_LENGTH + SALT_LENGTH )
							);
		VS_CHECK_ALLOCATED_MEMORY(pbytePasswordSalt)

				//	copy the password into the Password + Salt blob
		_VS_memcpy
		(
			pbytePasswordSalt,
			(_BYTE*) m_pbytePasswordHash,
			SHA1_HASH_LENGTH
		);

				//	copy the Salt after the password in the Password + Salt blob
		_VS_memcpy
		(
			(_BYTE*) &(pbytePasswordSalt [SHA1_HASH_LENGTH]),
			(_BYTE*) m_pbyteSalt,
			SALT_LENGTH
		);

				//	Hash the password hash + Salt bolb
		hResult =	m_HashData
					(
						pbytePasswordSalt,
						(const _VS_DWORD) ( SHA1_HASH_LENGTH + SALT_LENGTH ),
						&pbyteNewHash,
						&dwNewHashLen
					);
		VS_CHECK_HRESULT

				//	copy the output into the old hash variables
		_VS_memcpy
		(
			pbyteOldHash,
			pbyteNewHash,
			dwNewHashLen
		);

		dwOldHashLen =	dwNewHashLen;

			//	the password + Salt (of any lenght) is hashed once.
			//	so now hash the output in a loop (iterator count - 1) times.
		for ( i = 0; i < m_dwIterationCount - 1; i ++ )
		{
			VS_FREE_MEMORY(pbyteNewHash)	//	the m_HashData function will allocate the memory
											//	for the output (new hash).
											//	so delete the memory for new hash

						//	hash the data
			hResult =	m_HashData
						(
							pbyteOldHash,
							dwOldHashLen,
							&pbyteNewHash,
							&dwNewHashLen
						);
			VS_CHECK_HRESULT

					//	copy the old hash variables into the new hash variables.
			_VS_memcpy
			(
				pbyteOldHash,
				pbyteNewHash,
				dwNewHashLen
			);

			dwOldHashLen =	dwNewHashLen;
		}	//	end		for ( i = 0; i < m_dwIterationCount; i ++ )

			//	after exiting the loop both the old hash and new hash variables contain the same info
			//	use any one of them but delete both in the end.

			//	the length of the RC4 key is 128 bits = 16 bytes
		m_ItemNewRC4Key.len =	16;

			//	so copy the first 16 bytes of the data as the RC4 key
		VS_ALLOC_AND_BYTEBLOB_COPY (m_ItemNewRC4Key.data, pbyteNewHash, m_ItemNewRC4Key.len)

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VS_FREE_MEMORY(pbyteNewHash)
	VS_FREE_MEMORY(pbyteOldHash)

	return	hResult;
}	//	end		_VS_LONG	CProtectedStorage::m_CreateKeyFromPasswordSaltIterationCount ()


void	CProtectedStorage::m_UpdateVersionNumbers ()
{
	m_dwPSFirstVersionNumber					=	VSPS_VERSION_FIRST_NUMBER;
	m_dwPSSecondVersionNumber					=	VSPS_VERSION_SECOND_NUMBER;
	m_dwPSThirdVersionNumber					=	VSPS_VERSION_THIRD_NUMBER;
	m_dwPSFourthVersionNumber					=	VSPS_VERSION_FOURTH_NUMBER;

	m_dwPTAFirstVersionNumber					=	VSPTA_VERSION_FIRST_NUMBER;
	m_dwPTASecondVersionNumber					=	VSPTA_VERSION_SECOND_NUMBER;
	m_dwPTAThirdVersionNumber					=	VSPTA_VERSION_THIRD_NUMBER;
	m_dwPTAFourthVersionNumber					=	VSPTA_VERSION_FOURTH_NUMBER;

	return;
}	//	end		void	CProtectedStorage::m_UpdateVersionNumbers ()


void	CProtectedStorage::m_GenerateNewSaltAndIterationCount ()
{
	int							nResult				=	999;

	_BYTE*						pbyteRandom			=	NULL;

		//	allocate memory
	pbyteRandom =	(_BYTE*) m_VS_HeapAlloc (RANDOM_BLOCK_SIZE);
	if ( NULL == pbyteRandom )
	{
		return;
	}

				//	this is a bsafelite function to generate a random block
	nResult =	GenerateRandomBlock
				(
					pbyteRandom,
					RANDOM_BLOCK_SIZE
				);
	if ( 0 == nResult )
	{
		m_pbyteSalt =	(_BYTE*) m_VS_HeapAlloc (SALT_LENGTH);
		if ( NULL == m_pbyteSalt )
		{
			return;
		}

			//	copy salt
		_VS_memcpy
		(
			m_pbyteSalt,
			pbyteRandom,
			SALT_LENGTH
		);

		m_dwSaltLen =	SALT_LENGTH;

			//	copy iteration count
		_VS_memcpy
		(
			(_BYTE*) &m_dwIterationCount,
			&(pbyteRandom [SALT_LENGTH]),
			sizeof (_DWORD)
		);

			//	we want the count to be in between 1 aned 1024
			//	so we AND it with 0x3FF. this will give us a number between 0 and 1023
			//	this is followed by a ++
		m_dwIterationCount &= 0x3FF;
		m_dwIterationCount ++;

	}	//	end		if ( 0 == nResult )

	VS_FREE_MEMORY (pbyteRandom)

	return;
}	//	end		void	CProtectedStorage::m_GenerateNewSaltAndIterationCount ()
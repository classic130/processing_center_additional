///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	ProtectedStorage									 //
//																			 //
//	Description		:	The file defines the ProtectedStorage class.		 //
//																			 //
//	Date			:	Sept 13, 1999										 //
//																			 //
//	Author			:	Anand Abhyankar										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////

#ifndef		__PROTECTED_STORAGE_H__
#define		__PROTECTED_STORAGE_H__

#ifndef	_WIN32_WINNT
#define	_WIN32_WINNT		0x0400
#endif

//#include <stdio.h>
//#include <conio.h>
//#include <string.h>
#include <atlbase.h>
#include <time.h>
#include <comdef.h>

#include "VSPS_Platforms.h"
#include "VSPS_Defines.h"
#include "VSPS_Macros.h"
#include "VSPS_ASN.h"

#include "simder_all.h"

//#include "..\ptaimpl.h"

#include "integrate.h"


typedef _VS_LONG	(_SetPassword) ( void* i_pvoidPointer, _VS_CHAR*	o_cszPassword, _VS_DWORD*	o_pdwPasswordTimeOut );

class	CProtectedStorage
{
	public:
		CProtectedStorage ();//{}
		~CProtectedStorage ();//{}
		
///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	Initialize
//
//	Parameters
//		const _VS_CHAR*		i_cszApplicationName				-	Name of the application
//		const _VS_CHAR*		i_cszApplicationHost				-	Name of the server where the application 
//																	is hosted
//		const _VS_DWORD		i_cnIsApplicationEncrypted			-	Whether the application is encrypted or not
//																	APPLICATION_ENCRYPTED / APPLICATION_DECRYPTED
//																	(VSPS_Defines.h)
//		const _VS_DWORD		i_ncAddApplicationIfItDoesNotExist	-	Whether to add the application if it does 
//																	not exist.
//																	ADD_APPLICATION (VSPS_Defines.h)
//		const _VS_CHAR*		i_cszStorageFileName				-	Name of the storage file
//		const _VS_DWORD		i_ncCreateOpenFlag					-	Flag indicating whether the storage file is to
//																	be opened or created
//		const _VS_CHAR*		i_cszPassword						-	Password using which the file is protected
//		const _VS_DWORD		i_ncPasswordTimeOutInMinutes		-	The number of Minutes after which the
//																	password timesout.
//		_SetPassword*		i_pSetPasswordFunction				-	A callback function pointer. This function will 
//																	be called whenever the password times out. 
//																	The client will write this funciton and will
//																	return the password and the new timeout interval
//
//	Return Values	:
//
//	Description		:	This function will check the input parameteres and then create/open the Storage.
//						If the storage is opened then it will call functions to decode the contents.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	Initialize 
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
		);

		
		_VS_LONG	InitializeForRoaming
		(
			const _VS_CHAR*		i_cszApplicationName,
			const _VS_CHAR*		i_cszApplicationHost,
			const _VS_DWORD		i_cnIsApplicationEncrypted,
			const int			i_ncAddApplicationIfItDoesNotExist,
			const _VS_CHAR*		i_cszStorageName,
			_VS_BYTE**			i_ppbyteStorage,
			_VS_DWORD*			i_pdwStorageLen,
			const _VS_CHAR*		i_cszPassword,
			const _VS_DWORD		i_ncPasswordTimeOutInMinutes,
			_SetPassword*		i_pSetPasswordFunction,
			void*				i_pvoidPasswordFunctionData,
			const BOOL			i_boolUseFixedKey = FALSE
		);

		_VS_LONG	ChangeApplicationContext
		(
			const _VS_CHAR*		i_cszApplicationName,
			const _VS_CHAR*		i_cszApplicationHost,
			const _VS_DWORD		i_cnIsApplicationEncrypted
		);

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	Close
//
//	Parameters
//
//	Return Values	:
//
//	Description		:	This function will call functions to encode the data and then dump it
//						into the storage.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	Close ();

		_VS_LONG	CloseForRoaming
		(
//			_VS_BYTE*			o_pbyteStorage,
//			_VS_DWORD*			o_pdwStorageLen,
			_VS_DWORD*			o_pdwChangedFlag
		);


		_VS_LONG	ProvidePassword
		(
			const _VS_CHAR*		i_cszPassword
		);

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	AddCertificateToDB
//
//	Parameters
//		const _VS_BYTE*		i_pcbyteCertificateBlob		-	The Certificate blob
//		const _VS_DWORD		i_ncCertificateBlobLength	-	The certificate blob length
//		_VS_DWORD*			o_pnPointerToCertificate	-	A pointer to the certificate will be
//															returned which could be used to refer
//															to the certificate (in the same session)
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_CERT_ALREADY_EXISTS	-	the certificate already exists then it will not be 
//										added again. instead this error will be returned.
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The certificate blob will be added to the Protected Storage.
//						The number of certificate preferences for this certificate will be set to 0
//						and the certificate preferences data pointers will be set to NULL
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	AddCertificateToDB
		(
			const _VS_BYTE*		i_pcbyteCertificateBlob,
			const _VS_DWORD		i_ncCertificateBlobLength,
			_VS_DWORD*			o_pnPointerToCertificate
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	RemoveCertificateFromDB
//
//	Parameters
//		const _VS_DWORD		i_cnPointerToCertificate	-	the pointer to the certificate
//															obtained while adding/getting the certificate
//
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALID_CERT_PTR		-	the certificate pointer does not actually point to a certificate
//
//	Description		:	The certificate refered to by the pointer will be deleted form the
//						Protected storage. 
//						memory (structures) used to store this certificate and its preferences
//						will be freed
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	RemoveCertificateFromDB
		(
			const _VS_DWORD		i_cnPointerToCertificate
		);

		
///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	AddApplicationToDB
//
//	Parameters
//		const _VS_CHAR*		i_cszApplicationName		-	the (case sensitive) name of the application
//		const _VS_CHAR*		i_cszApplicationHost		-	the (case sensitive) host of the application
//		const _VS_DWORD		i_cnIsApplicationEncrypted	-	indicates if the application data is encrypted.
//															the accepted values are APPLICATION_ENCRYPTED
//															or APPLICATION_DECRYPTED (defined in VSPS_Defines.h)
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_APP_ALREADY_EXISTS		-	the application already exists (name and host matches) then it 
//										will not be added again. instead this error will be returned.
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The application name and host will be added to the Protected Storage. This addition
//						will be done to the PlainText applications or the Protected applications depending
//						on the i_cnIsApplicationEncrypted flag.
//						The number of application preferences for this application will be set to 0
//						and the application preferences data pointers will be set to NULL
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	AddApplicationToDB
		(
			const _VS_CHAR*		i_cszApplicationName,
			const _VS_CHAR*		i_cszApplicationHost,
			const _VS_DWORD		i_cnIsApplicationEncrypted
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	RemoveApplicationFromDB
//
//	Parameters
//		const _VS_CHAR*		i_cszApplicationName		-	the (case sensitive) name of the application
//		const _VS_CHAR*		i_cszApplicationHost		-	the (case sensitive) host of the application
//		const _VS_DWORD		i_cnIsApplicationEncrypted	-	indicates if the application data is encrypted.
//															the accepted values are APPLICATION_ENCRYPTED
//															or APPLICATION_DECRYPTED (defined in VSPS_Defines.h)
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_APP_ALREADY_EXISTS		-	the application already exists (name and host matches) then it 
//										will not be added again. instead this error will be returned.
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The specified application will be deleted and the memory for the application
//						and its preferences will be freed.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	RemoveApplicationFromDB
		(
			const _VS_CHAR*		i_cszApplicationName,
			const _VS_CHAR*		i_cszApplicationHost,
			const _VS_DWORD		i_cnIsApplicationEncrypted
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	AddPrivateKeyToDB
//
//	Parameters
//		const _VS_BYTE*		i_pcbytePrivateKeyBlob		-	The private key blob
//		const _VS_DWORD		i_ncPrivateKeyBlobLength	-	The private key blob length
//		const _VS_BYTE*		i_pcbyteAssociatedHash		-	The associated hash
//		const _VS_DWORD		i_ncAssociatedHashLength	-	The associated hash length
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_PVK_ALREADY_EXISTS		-	the private key already exists then it will not be 
//										added again. instead this error will be returned.
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The private key will be added to the Protected Storage.
//
//	NOTE:	The Associated hash will be used to identify the private key. The client
//			will have to supply this associated hash to get access to the key. This could
//			be a certificate hash or a public key hash etc.
//
///////////////////////////////////////////////////////////////////////////////
// Modified By: Infosys Technologies Ltd
// Change Request: CR#21529
// Description: Added a parameter to accomodate IsPrivateKeyExportable flag
		_VS_LONG	AddPrivateKeyToDB
		(
			const _VS_BYTE*		i_pcbytePrivateKeyBlob,
			const _VS_DWORD		i_ncPrivateKeyBlobLength,
			const _VS_BYTE*		i_pcbyteAssociatedHash,
			const _VS_DWORD		i_ncAssociatedHashLength,
			const _VS_DWORD		i_ncPrivateKeyExportable
		);

// CR#21529 Ends
///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	RemovePrivateKeyFromDB
//
//	Parameters
//		const _VS_BYTE*		i_pcbyteAssociatedHash		-	The associated hash. The private key
//															corresponding to this associated hash
//															will be deleted
//		const _VS_DWORD		i_ncAssociatedHashLength	-	The associated hash length
//
//	Return Values	:
//		VS_SUCCESS				-	the function is successful
//		E_VS_NOT_INITIALIZED	-	'Initialize' not called
//		E_VS_INVALID_PVK		-	the private key does not exist
//		E_VS_OUT_OF_MEMORY		-	low on memory
//		E_VS_INVALIDARG			-	the parameters passed are invalid
//
//	Description		:	The private key will be deleted from to the Protected Storage.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	RemovePrivateKeyFromDB
		(
			const _VS_BYTE*		i_pcbyteAssociatedHash,
			const _VS_DWORD		i_ncAssociatedHashLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetNumberOfCertificatesInDB
//
//	Parameters
//		_VS_DWORD*		o_pnNumberOfCertificates -	The number of certificates will be
//													returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The number of certificates in the DB will be returned in
//						o_pnNumberOfCertificates
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetNumberOfCertificatesInDB
		(
			_VS_DWORD*			o_pnNumberOfCertificates
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetNumberOfPrivateKeysInDB
//
//	Parameters
//		_VS_DWORD*		o_pnNumberOfPrivateKeys -	The number of private keys will be
//													returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The number of private keys in the DB will be returned in
//						o_pnNumberOfPrivateKeys
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetNumberOfPrivateKeysInDB
		(
			_VS_DWORD*			o_pnNumberOfPrivateKeys
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetNumberOfPlainTextApplications
//
//	Parameters
//		_VS_DWORD*		o_pnNumberOfPlainTextApplications -	The number of plain text applications
//															will be returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The number of plain text applications in the DB will be returned in
//						o_pnNumberOfPlainTextApplications
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetNumberOfPlainTextApplications
		(
			_VS_DWORD*			o_pnNumberOfPlainTextApplications
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetNumberOfProtectedApplications
//
//	Parameters
//		_VS_DWORD*		o_pnNumberOfProtectedApplications -	The number of protected applications
//															will be returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The number of protected applications in the DB will be returned in
//						o_pnNumberOfProtectedApplications
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetNumberOfProtectedApplications
		(
			_VS_DWORD*			o_pnNumberOfProtectedApplications
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetNumberOfInformationBlobs
//
//	Parameters
//		_VS_DWORD*		o_pnNumberOfInformationBlobs -	The number of information blobs
//														will be returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The number of information blobs in the DB will be returned in
//						o_pnNumberOfInformationBlobs
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetNumberOfInformationBlobs
		(
			_VS_DWORD*			o_pnNumberOfInformationBlobs
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetCertificateFromDB
//
//	Parameters
//		const _VS_DWORD		i_ncCertificateIndex		-	The index of the cert
//		_VS_BYTE**			o_ppbyteCertificateBlob		-	The certificate byte blob will be returned 
//															using this variable. 
//															Memory will be allocated by the 
//															function and the caller should free it 
//															using the FreeMemoryBlob() member function
//		_VS_DWORD*			o_pnCertificateBlobLength	-	The certificate byte blob length will be
//															returned using this variable
//		_VS_DWORD*			o_pnPointerToCertificate	-	A pointer to the certificate will be
//															returned which could be used to refer
//															to the certificate (in the same session)
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_CERT_OUT_OF_RANGE		-	the specified cert index is less than 0 or greater than
//										(or equal to) the number of certs
//
//	Description		:	The certificate byte blob and the length of the certificate specified by 
//						the index will be returned.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetCertificateFromDB
		(
			const _VS_DWORD		i_ncCertificateIndex,
			_VS_BYTE**			o_ppbyteCertificateBlob,
			_VS_DWORD*			o_pnCertificateBlobLength,
			_VS_DWORD*			o_pnPointerToCertificate
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetPrivateKeyFromDB
//
//	Parameters
//		const _VS_BYTE*		i_pcbyteAssociatedHash		-	the associated hash of the required private key
//		const _VS_DWORD		i_ncAssociatedHashLength	-	the associated hash length
//		_VS_BYTE**			o_ppbytePrivateKeyBlob		-	The private key will be returned using this parameter
//															Memory will be allocated by the 
//															function and the caller should free it 
//															using the FreeMemoryBlob() member function
//		_VS_DWORD*			o_pnPrivateKeyBlobLength	-	the length of the private key will be returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS				-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALID_PVK		-	the private key corresponding to the associated hash
//									does not exist
//		E_VS_OUT_OF_MEMORY		-	low on memory
//		E_VS_INVALIDARG			-	the parameters passed are invalid
//
//	Description		:	The private key corresponding to the associated hash will be returned
//
///////////////////////////////////////////////////////////////////////////////
// Modified By: Infosys Technologies Ltd
// Change Request: CR#21529
// Description: Added a parameter to accomodate IsPrivateKeyExportable flag
		_VS_LONG	GetPrivateKeyFromDB
		(
			const _VS_BYTE*		i_pcbyteAssociatedHash,
			const _VS_DWORD		i_ncAssociatedHashLength,
			_VS_BYTE**			o_ppbytePrivateKeyBlob,
			_VS_DWORD*			o_pnPrivateKeyBlobLength,
			_VS_DWORD*			i_IsPrivateKeyExportable
		);
// CR#21529 Ends

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetPasswordStrength
//
//	Parameters
//		_VS_DWORD*			o_pnPasswordStrength -	The password strength will be returned 
//													using this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The password strength will be returned in o_pnPasswordStrength
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetPasswordStrength
		(
			_VS_DWORD*			o_pnPasswordStrength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	SetPasswordStrength
//
//	Parameters
//		const _VS_DWORD		i_ncPasswordStrength -	The password strength to be set
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//
//	Description		:	The password strength will be set.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	SetPasswordStrength
		(
			const _VS_DWORD		i_ncPasswordStrength
		);


		_VS_LONG	ResetPassword
		(
			const _VS_CHAR*		i_cszOldPassword,
			const _VS_CHAR*		i_cszNewPassword
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetApplicationPreference
//
//	Parameters
//		const _VS_CHAR*		i_cszPreferenceName						-	the name of the preference
//		_VS_BYTE**			o_ppbyteApplicationPreferencesBlob		-	the preference data will be returned
//																		in this parameter
//																		Memory will be allocated by the 
//																		function and the caller should free it 
//																		using the FreeMemoryBlob() member function
//		_VS_DWORD*			o_pnApplicatoinPreferencesBlobLength	-	the length of the preference data will
//																		be returned in this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_INVALID_APP			-	the application name and host does not match with any application
//										in the database.
//		E_VS_INVALID_APP_PREF		-	the preference does not exist for the application
//
//	Description		:	The data and the length of the specified preference will be returned.
//
//	NOTE:	The application name, host and IsEncrypted flag provided in 'Initialize' method 
//			will be used over here.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetApplicationPreference
		(
			const _VS_CHAR*		i_cszPreferenceName,
			_VS_BYTE**			o_ppbyteApplicationPreferencesBlob,
			_VS_DWORD*			o_pnApplicatoinPreferencesBlobLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	SetApplicationPreference
//
//	Parameters
//		const _VS_CHAR*		i_cszPreferenceName						-	the name of the preference
//		_VS_BYTE**			o_ppbyteApplicationPreferencesBlob		-	the preference data in form
//																		of a byte blob
//		_VS_DWORD*			o_pnApplicatoinPreferencesBlobLength	-	the length of the preference data
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_INVALID_APP			-	the application name and host does not match with any application
//										in the database.
//
//	Description		:	if the preference name already exists then the preference data is updated else
//						the new preference name-data pair is added.
//
//	NOTE:	The application name, host and IsEncrypted flag provided in 'Initialize' method 
//			will be used over here.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	SetApplicationPreference
		(
			const _VS_CHAR*		i_cszPreferenceName,
			const _VS_BYTE*		i_pcbyteApplicationPreferencesBlob,
			const _VS_DWORD		i_ncApplicationPreferencesBlobLength,
			const int			i_ncAddApplicationIfItDoesNotExist
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	DeleteApplicationPreference
//
//	Parameters
//		const _VS_CHAR*		i_cszPreferenceName						-	the name of the preference
//																		to be deleted
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_INVALID_APP_PREF		-	the preference does not exist for the application
//		E_VS_INVALID_APP			-	the application name and host does not match with any application
//										in the database.
//
//	Description		:	the specified preference will be deleted and the memory occupied by the
//						preference name and data will be freed
//
//	NOTE:	The application name, host and IsEncrypted flag provided in 'Initialize' method 
//			will be used over here.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG DeleteApplicationPreference
		(
			const _VS_CHAR*		i_cszPreferenceName
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	DeleteAllApplicationPreferences
//
//	Parameters
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALID_APP			-	the application name and host does not match with any application
//										in the database.
//
//	Description		:	all the preferences of the specified application will be deleted
//						and the memory for the preference name, data and lengths will be freed
//
//	NOTE:	The application name, host and IsEncrypted flag provided in 'Initialize' method 
//			will be used over here.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG DeleteAllApplicationPreferences ();


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetCertificatePreference
//
//	Parameters
//		const _VS_DWORD		i_cnPointerToCertificate				-	The pointer to the certificate
//		const _VS_CHAR*		i_cszPreferenceName						-	the name of the preference
//		_VS_BYTE**			o_ppbyteCertificatePreferencesBlob		-	the preference data will be returned
//																		in this parameter
//																		Memory will be allocated by the 
//																		function and the caller should free it 
//																		using the FreeMemoryBlob() member function
//		_VS_DWORD*			o_pnCertificatePreferencesBlobLength	-	the length of the preference data will
//																		be returned in this parameter
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_INVALID_CERT_PTR		-	the certificate pointer does not actually point to a certificate
//		E_VS_INVALID_CERT_PREF		-	the preference does not exist for the certificate
//
//	Description		:	The data and the length of the specified preference will be returned.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetCertificatePreference
		(
			const _VS_DWORD		i_cnPointerToCertificate,
			const _VS_CHAR*		i_cszPreferenceName,
			_VS_BYTE**			o_ppbyteCertificatePreferencesBlob,
			_VS_DWORD*			o_pnCertificatePreferencesBlobLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	SetCertificatePreference
//
//	Parameters
//		const _VS_DWORD		i_cnPointerToCertificate				-	the pointer to the certificate
//		const _VS_CHAR*		i_cszPreferenceName						-	the name of the preference
//		const _VS_BYTE*		i_pcbyteCertificatePreferencesBlob		-	the preference data in form 
//																		of a byte blob
//		const _VS_DWORD		i_ncCertificatePreferencesBlobLength	-	the length of the preference
//																		data
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_INVALID_CERT_PTR		-	the certificate pointer does not actually point to a certificate
//
//	Description		:	if the preference name already exists then the preference data is updated else
//						the new preference name-data pair is added.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	SetCertificatePreference
		(
			const _VS_DWORD		i_cnPointerToCertificate,
			const _VS_CHAR*		i_cszPreferenceName,
			const _VS_BYTE*		i_pcbyteCertificatePreferencesBlob,
			const _VS_DWORD		i_ncCertificatePreferencesBlobLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	DeleteCertificatePreference
//
//	Parameters
//		const _VS_DWORD		i_cnPointerToCertificate				-	the pointer to the certificate
//		const _VS_CHAR*		i_cszPreferenceName						-	the name of the preference
//																		to be deleted
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_OUT_OF_MEMORY			-	low on memory
//		E_VS_INVALIDARG				-	the parameters passed are invalid
//		E_VS_INVALID_CERT_PTR		-	the certificate pointer does not actually point to a certificate
//		E_VS_INVALID_CERT_PREF		-	the preference does not exist for the certificate
//
//	Description		:	the specified preference will be deleted and the memory occupied by the
//						preference name and data will be freed
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	DeleteCertificatePreference
		(
			const _VS_DWORD		i_cnPointerToCertificate,
			const _VS_CHAR*		i_cszPreferenceName
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	DeleteAllCertificatePreference
//
//	Parameters
//		const _VS_DWORD		i_cnPointerToCertificate		-	the pointer to the certificate
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//		E_VS_NOT_INITIALIZED		-	'Initialize' not called
//		E_VS_INVALID_CERT_PTR		-	the certificate pointer does not actually point to a certificate
//
//	Description		:	all the preferences of the specified certificate will be deleted
//						and the memory for the preference name, data and lengths will be freed
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	DeleteAllCertificatePreference
		(
			const _VS_DWORD		i_cnPointerToCertificate
		);



				//	not yet implemented 
		_VS_LONG	GetAllCertificatesFromDB
		(
			_VS_BYTE**			o_ppbyteCertificateBlobs,
			_VS_DWORD*			o_pnCertificateBlobsLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	GetInformationBlob
//
//	Parameters
//		const _VS_CHAR*		i_cszInformationBlobName	-	the name of the required information blob
//		_VS_BYTE**			o_ppbyteInformationBlob		-	the information blob will be returned using this parameter
//															Memory will be allocated by the 
//															function and the caller should free it 
//															using the FreeMemoryBlob() member function
//		_VS_DWORD*			o_pnInformationBlobLength	-	the informaiton blob length willb e returned using this parameter
//
//	Return Values	:
//		VS_SUCCESS				-	the function is successful
//		E_VS_NOT_INITIALIZED	-	'Initialize' not called
//		E_VS_INVALID_INFO_BLOB	-	the information blob with the provided name
//									does not exist
//		E_VS_OUT_OF_MEMORY		-	low on memory
//		E_VS_INVALIDARG			-	the parameters passed are invalid
//
//	Description		:	The infromation blob with the provided name will be returned
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	GetInformationBlob
		(
			const _VS_CHAR*		i_cszInformationBlobName,
			_VS_BYTE**			o_ppbyteInformationBlob,
			_VS_DWORD*			o_pnInformationBlobLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	AddInformationBlobToDB
//
//	Parameters
//		const _VS_CHAR*		i_cszInformationBlobName	-	the name of the information blob to be added
//		const _VS_BYTE*		i_pcbyteInformationBlob		-	the data of the information blob to be added
//		const _VS_DWORD		i_ncInformationBlobLength	-	the length of the data of the information blob
//
//	Return Values	:
//		VS_SUCCESS						-	the function is successful
//		E_VS_NOT_INITIALIZED			-	'Initialize' not called
//		E_VS_INFO_BLOB_ALREADY_EXISTS	-	the information blob already exists then it will not be 
//											added again. instead this error will be returned.
//		E_VS_OUT_OF_MEMORY				-	low on memory
//		E_VS_INVALIDARG					-	the parameters passed are invalid
//
//	Description		:	The information blob will be added to the Protected Storage.
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	AddInformationBlobToDB
		(
			const _VS_CHAR*		i_cszInformationBlobName,
			const _VS_BYTE*		i_pcbyteInformationBlob,
			const _VS_DWORD		i_ncInformationBlobLength
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	RemoveInformationBlobFromDB
//
//	Parameters
//		const _VS_CHAR*		i_cszInformationBlobName	-	The name of the information blob to be deleted
//
//	Return Values	:
//		VS_SUCCESS				-	the function is successful
//		E_VS_NOT_INITIALIZED	-	'Initialize' not called
//		E_VS_INVALID_INFO_BLOB	-	the information blob does not exist
//		E_VS_OUT_OF_MEMORY		-	low on memory
//		E_VS_INVALIDARG			-	the parameters passed are invalid
//
//	Description		:	The information blob will be deleted
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	RemoveInformationBlobFromDB
		(
			const _VS_CHAR*		i_cszInformationBlobName
		);


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	FreeMemoryBlob
//
//	Parameters
//		void**				io_ppvoidMemoryBlob -	The pointer to the memory blob to be freed
//
//	Return Values	:
//		VS_SUCCESS					-	the function is successful
//
//	Description		:	The memory blob will be freed and the pointer will be set to NULL
//
///////////////////////////////////////////////////////////////////////////////
		_VS_LONG	FreeMemoryBlob
		(
			void**				io_ppvoidMemoryBlob
		);


		_VS_LONG	BeginRead
		(
			const	_VS_DWORD	i_cnMode,
			const	_VS_DWORD	i_cnWaitTime
		);

		_VS_LONG	EndRead ();

		_VS_LONG	BeginWrite
		(
			const	_VS_DWORD	i_cnMode,
			const	_VS_DWORD	i_cnWaitTime
		);


		_VS_LONG	EndWrite ();

		_VS_LONG	UpgradeReadToWrite ();

		_VS_LONG	CheckIfPSChangedAfterInitialization
		(
			_VS_DWORD*			o_pnPSChanged
		);

		_VS_LONG	ResetChangedAfterInitializationFlag ();

		_VS_LONG	UpdatePasswordTimeout
		(
			const	_VS_DWORD	i_ncPasswordTimeOutInMinutes
		);

		_VS_LONG	GetApplicationCreator
		(
			_VS_BYTE**	o_ppbyteApplicationHost
		);

		_VS_LONG	CProtectedStorage::GetApplicationCreatorWildCard
		(
			_VS_BYTE**	o_ppbyteApplicationCreatorWildCard
		);

		_VS_LONG	CProtectedStorage::SetApplicationCreatorWildCard
		(
			const _VS_BYTE*		i_pcbyteApplicationCreatorWildCard,
			const _VS_DWORD		i_ncWildCardBlobLength
		);

		_VS_LONG	GetApplicationReadOKDomains
		(
			_VS_DWORD*	o_pnNumOfApplicationReadOKDomains,
			_VS_BYTE**	o_ppbyteApplicationReadOKDomainsBlob,
			_VS_DWORD*	o_pnApplicationReadOKDomainsBlobLength
		);

		_VS_LONG	SetApplicationReadOKDomains
		(
			const _VS_DWORD		i_ncNumOfApplicationReadOkDomains,
			const _VS_BYTE*		i_pcbyteApplicationReadOkDomainsBlob,
			const _VS_DWORD		i_ncApplicationReadOKDomainsBlobLength
		);

		_VS_LONG	GetApplicationWriteOKDomains
		(
			_VS_DWORD*	o_pnNumOfApplicationWriteOKDomains,
			_VS_BYTE**	o_ppbyteApplicationWriteOKDomainsBlob,
			_VS_DWORD*	o_pnApplicationWriteOKDomainsBlobLength
		);

		_VS_LONG	SetApplicationWriteOKDomains
		(
			const _VS_DWORD		i_ncNumOfApplicationWriteOkDomains,
			const _VS_BYTE*		i_pcbyteApplicationWriteOkDomainsBlob,
			const _VS_DWORD		i_ncApplicationWriteOKDomainsBlobLength
		);

	private:
		_VS_CHAR*							m_szApplicationName;
		_VS_CHAR*							m_szApplicationHost;
		_VS_DWORD							m_dwIsApplicationEncrypted;
		_VS_CHAR*							m_szStorageFileName;
//		_VS_CHAR*							m_szPassword;
		_VS_BYTE*							m_pbytePasswordHash;
		_VS_DWORD							m_dwPasswordHashLen;

		ITEM								m_ItemRC4Key;
		ITEM								m_ItemNewRC4Key;	//	this will be the key generated using
																//	salt etc.
		ITEM								m_ItemRoamRC4Key;	//	this will be the key used to encrypt/decrypt protected data
																//	in roaming profiles. It contains hard-coded value
		_BYTE*								m_pbyteSalt;
		_DWORD								m_dwSaltLen;
		_DWORD								m_dwIterationCount;

		_VS_DWORD							m_dwDontDestroyMembers;		
	
		_VS_DWORD							m_nCreateOpenFlag;

		_VS_DWORD							m_nPasswordProvided;
		_VS_DWORD							m_nProtectedDataParsed;

		_BYTE*								m_pbyteEntireStorage;
		_DWORD								m_dwEntireStorageSize;

		_DWORD								m_dwNumberOfPlainTextApplications;
		_DWORD								m_dwNumberOfProtectedApplications;

		_DWORD								m_dwPasswordStrength;
		_DWORD								m_dwNumberOfPrivateKeys;
		_DWORD								m_dwNumberOfCertificates;
		_DWORD								m_dwNumberOfInformationBlobs;

		_DERTree*							m_pstructDERTreePlainTextInformation;
		_DERTree*							m_pstructDERTreeEncryptedProtectedInformation;
		_DERTree*							m_pstructDERTreeProtectedInformation;

		_DERTree*							m_pstructDERTreePlainTextApplication;
		_DERTree*							m_pstructDERTreeCertificates;

		_DERTree*							m_pstructDERTreePrivateKeys;
		_DERTree*							m_pstructDERTreeProtectedApplication;
		_DERTree*							m_pstructDERTreeInformationBlobs;

		VSPS_CertificateInformation*		m_pstructCertificateInformation;
		
		VSPS_ApplicationInformation*		m_pstructPlainTextApplicationInformation;
		VSPS_ApplicationInformation*		m_pstructProtectedApplicationInformation;

		VSPS_PrivateKeyInformation*			m_pstructPrivateKeyInformation;
		VSPS_InformationBlob*				m_pstructInformationBlob;

		_BYTE*								m_pbyteVeriSignConstant;
		_BYTE*								m_pbyteEncryptedVeriSignConstant;

		_DWORD								m_dwPSFirstVersionNumber;
		_DWORD								m_dwPSSecondVersionNumber;
		_DWORD								m_dwPSThirdVersionNumber;
		_DWORD								m_dwPSFourthVersionNumber;

		_DWORD								m_dwPTAFirstVersionNumber;
		_DWORD								m_dwPTASecondVersionNumber;
		_DWORD								m_dwPTAThirdVersionNumber;
		_DWORD								m_dwPTAFourthVersionNumber;

		_VS_DWORD							m_dwPlainTextInformationChanged;
		_VS_DWORD							m_dwProtectedInformationChanged;
//		_VS_DWORD							m_dwEncryptedProtectedInformationChanged;

		_VS_DWORD							m_dwCertificateInformationChanged;
		_VS_DWORD							m_dwPlainTextApplicationInformationChanged;
		_VS_DWORD							m_dwPrivateKeysChanged;
		_VS_DWORD							m_dwProtectedApplicationInformationChanged;
		_VS_DWORD							m_dwInformationBlobChanged;

		_BYTE*								m_pbyteDecryptedProtectedInformation;
		_DWORD								m_dwDecryptedProtectedInformationLength;
//		_BYTE*								m_pbytePaddedInformation;
//		_DWORD								m_dwPaddedInformationLen;

		_BYTE*								m_pbyteEncryptedProtectedInformation;
		_DWORD								m_dwEncryptedProtectedInformationLength;

		_VS_DWORD							m_dwInitializeCalled;
		_VS_DWORD							m_dwInitializeSuccessful;

		_SetPassword*						m_pSetPasswordFunctionPointer;
		void*								m_pvoidPasswordFunctionData;

//		HANDLE								m_hReadSemaphore;
		HANDLE								m_hWriteSemaphore;	//	this will have max count = 1.
																//	i.e. only one process will be allowed to
																//	perform a write operation.
		HANDLE								m_hReadMutex;

//		_VS_CHAR*							m_szReadSemaphoreName;
//		_VS_CHAR*							m_szWriteMutexName;
//		_VS_CHAR*							m_szReadMutexName;

		_VS_DWORD							m_dwBeginCalledBefore;
		_VS_DWORD							m_dwBeginReadCalled;
		_VS_DWORD							m_dwBeginWriteCalled;

		_VS_DWORD							m_dwWaitForSingleObjectTimeOut;


#if PLATFORM==VSPS_WIN32
		HANDLE								m_hStorageFile;
//		HANDLE								m_hMutex;

		HANDLE								m_hHeap;

		HANDLE								m_hMemoryMappedFile;

//		FILETIME							m_FileTimeCreation;
//		FILETIME							m_FileTimeLastAccess;
//		FILETIME							m_FileTimeLastModified;



//
//	Anand	Apr 14, 2000		start
//
//	The conditional update of datastructures based on time stamps was getting too complicated.
//	moreover for roaming the data is to be read from memory block and so we cannot use the
//	time stamp.
//
//		FILETIME							m_FileTimeLastModifiedPlainText;
//		FILETIME							m_FileTimeLastModifiedProtected;

#endif

		VSPS_ASN							m_structASN;

		_VS_LONG							m_longTimePasswordProvided;
		_VS_DWORD							m_dwPasswordTimeOutIntervalInSeconds;
//		_VS_DWORD							m_dwPasswordTimeOutAfterOneFunction;

		_VS_DWORD							m_dwMemoryOrFile;
		_VS_CHAR*							m_szRoamingStorageName;
		_VS_BYTE**							m_ppbyteRoamingBuffer;
		_VS_DWORD*							m_pdwRoamingBufferLen;
		_VS_DWORD							m_dwRoamingBufferChanged;

		CBaseDERHierarchy*					m_pCbdhProtectedInformation;
		CBaseDERHierarchy*					m_pCbdhEntireStorage;

		_VS_DWORD							m_dwPSChangedAfterInitialized;


		_VS_DWORD							m_dwReverseOS;
		
		BOOL								m_boolUseFixedKey;

	private:
		_VS_LONG				m_CheckPassword
		(
			const _VS_CHAR*		i_cszPassword
		);

		_VS_LONG				m_DecodeProtectedStorage ();
		_VS_LONG				m_DecodePlainTextData ();
		_VS_LONG				m_DecodeCertificateInformation ();
		_VS_LONG				m_DecodePlainTextApplicationInformation ();
		_VS_LONG				m_DecodeProtectedData ();
		_VS_LONG				m_DecodeProtectedApplicationInformation ();
		_VS_LONG				m_DecodePrivateKeyInformation ();
		_VS_LONG				m_DecodeInformationBlobs ();

		_VS_LONG				m_EncodeProtectedStorage ();
		_VS_LONG				m_EncodePlainTextData ();
		_VS_LONG				m_EncodeProtectedData ();
		_VS_LONG				m_EncodeCertificateInformation ();
		_VS_LONG				m_EncodePlainTextApplicationInformation ();
		_VS_LONG				m_EncodeProtectedApplicationInformation ();
		_VS_LONG				m_EncodePrivateKeyInformation ();
		_VS_LONG				m_EncodeInformationBlobs ();

/*
This funciton was not used anywhere and therefore is commented out.
		
		_VS_LONG				m_GetNumberOfElementsInSequence
		(
			const _DERTree*		i_pcstructDERTree,
			_VS_DWORD*			o_pdwNumberOfElements
		);
*/

		_VS_LONG				m_OpenAndReadProtectedStorage ();
		_VS_LONG				m_CreateProtectedStorage ();
		_VS_LONG				m_SetProtectedStorageDefaults ();

		_VS_LONG				m_VS_HeapCreate ();
		_VS_LONG				m_VS_HeapDestroy ();
		void*					m_VS_HeapAlloc
		(
			const _DWORD		i_ncSize
		);
		void					m_VS_HeapFree
		(
			void*				i_pFreeBlock
		);

		_VS_LONG				m_GetCertificateIndexFromPointerToCertificate
		(
			const _VS_DWORD		i_cnPointerToCertificate,
			_VS_DWORD*			o_pnCertificateIndex
		);

		_VS_LONG				m_DecryptProtectedData ();
		_VS_LONG				m_EncryptProtectedData ();
		_VS_LONG				m_HashData
		(
			const _VS_BYTE*		i_cpbyteInputData,
			const _VS_DWORD		i_cdwInputDataLength,
			_VS_BYTE**			o_ppbyteHash,
			_VS_DWORD*			o_pdwHashLength
		);

		_VS_LONG				m_CreateKeyFromPasswordHash ();
		_VS_LONG				m_DestroyKeyFromPassword ();

		_VS_LONG				m_CreateKeyFromPasswordSaltIterationCount ();
		void					m_GenerateNewSaltAndIterationCount ();
		void					m_UpdateVersionNumbers ();

		_VS_LONG				m_CheckPasswordTimeOut ();
		_VS_LONG				m_UpdatePasswordTimeOut ();

		_VS_LONG				m_CheckIfApplicationExists ();

		_VS_LONG				m_ReadDataIntoStructures
		(
			_VS_DWORD			i_dwUpdateWhat
		);

		_VS_LONG				m_FreeDataStructures
		(
			_VS_DWORD			i_dwUpdateWhat
		);

		_VS_LONG				m_UpdateDataStructuresIfNecessary
		(
			_VS_DWORD			i_dwUpdateWhat
		);

		_VS_LONG				m_UpdateStorageFileIfNecessary ();

/*		_VS_LONG				m_BlockDueToContention
		(
			const	_VS_DWORD	i_cnMode,
			const	_VS_DWORD	i_cnWaitTime,
			const	_VS_DWORD	i_cnWhatsBlocked
		);*/

		_VS_LONG				m_CreateConcurrencyObjects ();

		_VS_LONG				m_CleanPIDList
		(
			_VS_DWORD*			o_pdwNumberOfReadProcesses,
			_VS_DWORD*			o_pdwNumberOfWriteProcesses
		);
		
		_VS_LONG				m_AddToPIDList ();
		
		_VS_LONG				m_DeleteFromPIDList
		(
			_VS_DWORD*			o_pdwNumberOfReadProcesses
		);

		_VS_LONG				m_SetWritePID ();
		_VS_LONG				m_ResetWritePID ();

		void					m_InitializeMembers ();
		void					m_DestroyMembers ();

		void					m_VS_strcpyW
		(
			_VS_CHAR*			o_szDestination,
			const _VS_CHAR*		i_cszSource
		);

		void					m_VS_strcatW
		(
			_VS_CHAR*			o_szDestination,
			const _VS_CHAR*		i_cszSource
		);

		void					m_GetPathFromFileName
		(
			_VS_CHAR*			i_szFileName,
			_VS_CHAR*			o_szPath
		);

		BOOL					m_CreateRecursiveDirectory
		(
			_VS_CHAR*			i_szDirToCreate
		);

		int						BytesToAscHex
		(
			_VS_BYTE*			byteHashVal, 
			int					nHashValSize, 
			_bstr_t&			tbstrAscHexMD5
		);

/*
		void					m_EraseMemory
		(
			void*				i_pMemoryBlock,
			_VS_DWORD			i_dwMemoryBlockSize
		);
*/
};

#endif
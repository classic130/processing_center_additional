The ASN.1 notation for the file will be:

VeriSignDB ::= SEQUENCE 
{
	VS_Plain_Text_Information					VS_PlainTextInformation,
	VS_Protected_Information					VS_ProtectedInformation
}

VS_PlainTextInformation ::= SEQUENCE
{
	VeriSignConstantString						PrintableString,
	VS_PS_VersionNumber							VS_VersionNumber,
	VS_PTA_VersionNumber						VS_VersionNumber,
	VS_Password_Strength						INTEGER,
	VS_Number_And_Certificates					VS_NumberAndCertificates,
	VS_Number_And_Application_Information		VS_NumberAndApplicationInformation	
}

VS_ProtectedInformation ::= SEQUENCE
{
	VeriSignConstantString						PrintableString,
	VS_Number_And_Private_Key					NumberAndPrivateKey,
	VS_Number_And_Application_Information		VS_NumberAndApplicationInformation,
	VS_Number_And_Informaiton_Blobs				VS_NumberAndInformationBlobs	
}

VS_VersionNumber ::= SEQUENCE
{
	VS_FirstVersionNumber						INTEGER,
	VS_SecondVersionNumber						INTEGER,
	VS_ThirdVersionNumber						INTEGER,
	VS_FourthVersionNumber						INTEGER
}

VS_NumberAndCertificates ::= SEQUENCE
{
	NumberOfElements							INTEGER,
	VS_Certificate_Information					SEQUENCE OF VS_CertificateInformation,
}

VS_CertificateInformation ::= SEQUENCE
{
	CertificateBlob								ExtendedCertificateOrCertificate,
	NumberOfElements							INTEGER,
	VS_Certificate_Preferences					SEQUENCE OF VS_CertificatePreference
}

VS_NumberAndApplicationInformation ::= SEQUENCE
{
	NumberOfElements							INTEGER,
	VS_Application_Information					SEQUENCE OF VS_ApplicationInformation
}

VS_ApplicationInformation ::= SEQUENCE
{
	ApplicationName								PrintableString,
	ApplicationHostName							PrintableString,
	NumberOfElements							INTEGER,
	VS_Application_Preferences					SEQUENCE OF VS_ApplicationPreference DEFAULT {}
}

VS_NumberAndPrivateKey ::= SEQUENCE
{
	NumberOfElements							INTEGER,
	VS_Private_Keys								SEQUENCE OF VS_PrivateKey,
}

VS_PrivateKey ::= SEQUENCE
{
	AssociatedHash								VS_AssociatedHash,
	PrivateKeyBlob								OCTET STRING
}

VS_CertificatePreference ::= SEQUENCE
{
	CertificatePreferenceName					PrintableString,
	CertificatePreferenceData					OCTET STRING
}

VS_ApplicationPreference ::= SEQUENCE
{
	ApplicationPreferenceName					PrintableString,
	ApplicationPreferenceData					OCTET STRING
}

VS_AssociatedHash ::= OCTET_STRING

VS_NumberAndInformationBlobs ::= SEQUENCE
{
	NumberOfElements							INTEGER,
	VS_Information_Blobs						SEQUENCE OF	VS_InformationBlobs
}

VS_InformationBlobs ::= SEQUENCE
{
	InformationBlobName							PrintableString,
	InformationBlobData							OCTET STRING
}




class	CProtectedStorage
{
	public:
		CProtectedStorage ();
		~CProtectedStorage ();
		
		_VS_LONG	Initialize 
		(
			const _VS_CHAR*		i_pcszApplicationName,
			const _VS_CHAR*		i_pcszApplicationHostName,
			const _VS_CHAR*		i_pcszStorageFileName,
			const _VS_DWORD		i_ncCreateOpenFlag,
			const _VS_CHAR*		i_pcszPassword
		);

		_VS_LONG	ProvidePassword
		(
			const _VS_CHAR* 	i_pcszPassword
		);
		
		_VS_LONG	Close ();

		_VS_LONG	AddCertificateToDB
		(
			const _VS_BYTE*		i_pcbyteCertificateBlob,
			const _VS_DWORD		i_ncCertificateBlobLength
		);

		_VS_LONG	RemoveCertificateFromDB
		(
			const _VS_DWORD		i_ncCertificateIndex
		);

// Modified By: Infosys Technologies Ltd
// Change Request: CR#21529
// Description: Added a parameter to accomodate IsPrivateKeyExportable flag
		_VS_LONG	AddPrivateKeyToDB
		(
			const _VS_BYTE*		i_pcbytePrivateKeyBlob,
			const _VS_DWORD		i_ncPrivateKeyBlobLength,
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength,
			const _VS_DWORD		i_IsPrivateKeyExportable
		);
// CR#21529 Ends
		_VS_LONG	RemovePrivateKeyFromDB
		(
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength
		);

		_VS_LONG	GetNumberOfCertificatesInDB
		(
			_VS_DWORD*			o_pnNumberOfCertificates
		);

		_VS_LONG	GetNumberOfPrivateKeysInDB
		(
			_VS_DWORD*			o_pnNumberOfPrivateKeys
		);

		_VS_LONG	GetCertificateFromDB
		(
			const _VS_DWORD*	i_ncCertificateIndex,
			_VS_BYTE**			o_ppbyteCertificateBlob,
			_VS_DWORD*			o_pnCertificateBlobLength
		);

// Modified By: Infosys Technologies Ltd
// Change Request: CR#21529
// Description: Added a parameter to accomodate IsPrivateKeyExportable flag
		_VS_LONG	GetPrivateKeyFromDB
		(
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength,
			_VS_BYTE**			o_ppbytePrivateKeyBlob,
			_VS_DWORD*			o_pnPrivateKeyBlobLength,
			_VS_DWORD*				i_IsPrivateKeyExportable
		);
// CR#21529 Ends
		_VS_LONG	GetPasswordStrength
		(
			_VS_DWORD*			o_pnPasswordStrength
		);

		_VS_LONG	SetPasswordStrength
		(
			const _VS_DWORD		i_ncPasswordStrength
		);

		_VS_LONG	ResetPassword
		(
			const _VS_CHAR*		i_pcszOldPassword,
			const _VS_CHAR*		i_pcszNewPassword
		);

		_VS_LONG	GetApplicationPreferences
		(
			const _VS_CHAR*		i_pcszApplicationName,
			const _VS_CHAR*		i_pcszPreferenceName,
			const _VS_DWORD		i_cnIsPreferenceEncrypted,
			_VS_BYTE**			o_ppbyteApplicationPreferences,
			_VS_DWORD*			o_pnApplicatoinPreferencesLength
		);

		_VS_LONG	SetApplicationPreferences
		(
			const _VS_CHAR*		i_pcszApplicationName,
			const _VS_CHAR*		i_pcszPreferenceName,
			const _VS_DWORD		i_cnIsPreferenceEncrypted,
			const _VS_BYTE*		i_pcbyteApplicationPreferencesBlob,
			const _VS_DWORD		i_ncApplicationPreferencesBlobLength
		);

		_VS_LONG DeleteApplicationPreferences
		(
			const _VS_CHAR*		i_pcszApplicationName,
			const _VS_CHAR*		i_pcszPreferenceName,
			const _VS_DWORD		i_cnIsPreferenceEncrypted
		);

		_VS_LONG DeleteAllApplicationPreferences
		(
			const _VS_CHAR*		i_pcszApplicationName,
			const _VS_DWORD		i_cnIsPreferenceEncrypted
		);

		_VS_LONG	GetCertificatePreferences
		(
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength,
			const _VS_CHAR*		i_pcszPreferenceName,
			_VS_BYTE**			o_ppbyteCertificatePreferences,
			_VS_DWORD*			o_pnCertificatePreferencesLength
		);

		_VS_LONG	SetCertificatePreferences
		(
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength,
			const _VS_CHAR*		i_pcszPreferenceName,
			const _VS_BYTE*		i_pcbyteCertificatePreferencesBlob,
			const _VS_DWORD		i_ncCertificatePreferencesBlobLength
		);

		_VS_LONG	DeleteCertificatePreferences
		(
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength,
			const _VS_CHAR*		i_pcszPreferenceName
		);

		_VS_LONG	DeleteAllCertificatePreferences
		(
			const _VS_BYTE*		i_pcbyteCertificateHash,
			const _VS_DWORD		i_ncCertificateHashLength
		);

		_VS_LONG	GetAllCertificatesFromDB
		(
			_VS_BYTE**			o_ppbyteCertificateBlobs,
			_VS_DWORD*			o_pnCertificateBlobsLength
		);
};
///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	VSPS_ASN.	h										 //
//																			 //
//	Description		:	The file contains the structure of the storage which //
//						is later ASN encoded.								 //
//																			 //
//	Date			:	Sept 13, 1999										 //
//																			 //
//	Author			:	Anand Abhyankar										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#ifndef	__VS_PS_ASN_H__
#define	__VS_PS_ASN_H__

#include "simder_all.h"

struct	VSPS_ASN
{
	CSequence				CSeqProtectedStorage;
	CSequence				CSeqPlainTextInformation;
	CSequence				CSeqEncryptedProtectedInformation;
	CSequence				CSeqProtectedInformation;
	CSequence				CSeqCertificateInformation;
	CSequence				CSeqPlainTextApplicationInformation;
	CSequence				CSeqProtectedApplicationInformation;
	CSequence				CSeqPTAVersionNumber;
	CSequence				CSeqPSVersionNumber;
	CSequence				CSeqPrivateKeys;
	CSequence				CSeqInformationBlobs;
};

struct	VSPS_CertificateInformation
{
	_BYTE*					pbyteCertificateBlob;				//	This is actually an ExtendedCertificateOrCertificate
	_DWORD					dwCertificateBlobLength;
	DWORD					dwNumberOfCertificatePreferences;
	_BYTE**					ppbyteCertificatePreferenceName;
	_DWORD*					pdwCertificatePreferenceNameLength;
	_BYTE**					ppbyteCertificatePreferenceData;
	_DWORD*					pdwCertificatePreferenceDataLength;
};

struct	VSPS_ApplicationInformation
{
	_BYTE*					pbyteApplicationName;
	_DWORD					dwApplicationNameLength;
	_BYTE*					pbyteApplicationHost;
	_DWORD					dwApplicationHostLength;
	_BYTE*					pbyteApplicationCreatorWildCard;
	DWORD					dwApplicationCreatorWildCardLength;
	DWORD					dwNumOfApplicationReadOKDomains;
	_BYTE*					pbyteApplicationReadOKDomains;
	DWORD					dwApplicationReadOKDomainsLength;
	_DWORD					dwNumOfApplicationWriteOKDomains;
	_BYTE*					pbyteApplicationWriteOKDomains;
	_DWORD					dwApplicationWriteOKDomainsLength;
	DWORD					dwNumberOfApplicationPreferences;
	_BYTE**					ppbyteApplicationPreferenceName;
	_DWORD*					pdwApplicationPreferenceNameLength;
	_BYTE**					ppbyteApplicationPreferenceData;
	_DWORD*					pdwApplicationPreferenceDataLength;
};

struct	VSPS_PrivateKeyInformation
{
	_BYTE*					pbyteAssociatedHash;
	_DWORD					dwAssociatedHashLength;
	_BYTE*					pbytePrivateKeyBlob;
	_DWORD					dwPrivateKeyBlobLength;
	// Modified by - Infosys Technologies Ltd. 
	// Change Request - CR#21529
	// Description - Declare an additional element in the structure to store the value of PrivateKeyExportableFlag flag.
	// CR#21529 Begin
	// Date Modified - July 1, 2004
	DWORD					dwPrivateKeyExportableFlag;
	// CR 21529 - End
};

struct	VSPS_InformationBlob
{
	_BYTE*					pbyteInformationBlobName;
	_DWORD					dwInformationBlobNameLength;
	_BYTE*					pbyteInformationBlobData;
	_DWORD					dwInformationBlobDataLength;
};

#endif

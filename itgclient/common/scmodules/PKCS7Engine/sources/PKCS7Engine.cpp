#include "pkcs7engine.h"


// BUG BUG - SMIME capabalities to be added - Implement a function to Enum capablities by using PTA for implementation
// BUGBUG - support for CRLs - another input parameter to the function.

/* Note the other items above sMIMECapabilities, probably this is needed too - refer (smimestuff\tools\oesigned.out)
SEQUENCE {
3694 06    5:             OBJECT IDENTIFIER sha1 (1 3 14 3 2 26)
3701 05    0:             NULL
            :             }
3703 A0  186:           [0] {
3706 30   24:             SEQUENCE {
3708 06    9:               OBJECT IDENTIFIER
            :                 contentType (1 2 840 113549 1 9 3)
3719 31   11:               SET {
3721 06    9:                 OBJECT IDENTIFIER data (1 2 840 113549 1 7 1)
            :                 }
            :               }
3732 30   28:             SEQUENCE {
3734 06    9:               OBJECT IDENTIFIER
            :                 signingTime (1 2 840 113549 1 9 5)
3745 31   15:               SET {
3747 17   13:                 UTCTime '001206200524Z'
            :                 }
            :               }
3762 30   35:             SEQUENCE {
3764 06    9:               OBJECT IDENTIFIER
            :                 messageDigest (1 2 840 113549 1 9 4)
3775 31   22:               SET {
3777 04   20:                 OCTET STRING
            :                   EA 6D 92 AB FD 8D 0A BE A1 27 28 48 B9 61 86 F4
            :                   3F B7 15 0E
            :                 }
            :               }
3799 30   91:             SEQUENCE {
3801 06    9:               OBJECT IDENTIFIER
            :                 sMIMECapabilities (1 2 840 113549 1 9 15)
3812 31   78:               SET {
3814 30   76:                 SEQUENCE {
3816 30   10:                   SEQUENCE {
3818 06    8:                     OBJECT IDENTIFIER
            :                       DES-EDE3-CBC (1 2 840 113549 3 7)
            :                     }
3828 30   14:                   SEQUENCE {
3830 06    8:                     OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
3840 02    2:                     INTEGER 128
            :                     }
3844 30   13:                   SEQUENCE {
3846 06    8:                     OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
3856 02    1:                     INTEGER 64
            :                     }
3859 30    7:                   SEQUENCE {
3861 06    5:                     OBJECT IDENTIFIER desCBC (1 3 14 3 2 7)
            :                     }
3868 30   13:                   SEQUENCE {
3870 06    8:                     OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
3880 02    1:                     INTEGER 40
            :                     }
3883 30    7:                   SEQUENCE {
3885 06    5:                     OBJECT IDENTIFIER
            :                       sha-1WithRSAEncryption (1 3 14 3 2 29)
            :                     }
            :                   }
            :                 }
            :               }
            :             }
*/
int CreateSignedData(PVS_SIGNATURE_BLOB pSignatureBlob,
					 int i_nHashAlg,
					 PVS_SIGNER_INFO pSignerInfo, 
					 bool bDetached, // TRUE if Detached 
					 unsigned char *pbData, // only for attached, NULL if Detached.
					 unsigned int cbData,   // only for attached, 0 if Detached.
					 unsigned char *pbAuthAttribCollection,
					 unsigned int cbAuthAttribCollection,
					 char **pszSignedData64)
{

	int retVal = 0;
	bool bAuthAtrrib = false;

	// Construction of SignerInfo

	if(pSignerInfo == NULL)
	{
		return -1;
	}

	if(pSignatureBlob->pbData == NULL || pSignatureBlob->pbData <= 0)
	{
		return -1;
	}
		
	//Obtain the (DER Encoded) issuer dn sequence of the cert
	CSequence cseqIssuer;
	if(pSignerInfo->Issuer.pbData == NULL || pSignerInfo->Issuer.cbData <= 0)
	{
		return -1;
	}

	CDERBlob cdbIssuer(pSignerInfo->Issuer.cbData, pSignerInfo->Issuer.pbData);

	CBaseDER cbdIssuer(cdbIssuer);

	// Deleting the input/decoded data
	if(cdbIssuer.pbData)
	{
		free(cdbIssuer.pbData);
		cdbIssuer.pbData = 0;
	}

	cbdIssuer.destroy(DESTROY_DEC);

	//Obtain the (DER Encoded) serial number of the cert
	if(pSignerInfo->SerialNumber.pbData == NULL || pSignerInfo->SerialNumber.cbData <= 0)
	{
		return -1;
	}

	CUniversalInteger cuiSerialNum(pSignerInfo->SerialNumber.cbData, pSignerInfo->SerialNumber.pbData);
	CHECKNULLANDSIZE(cuiSerialNum)

	// Deleting the input/decoded data
	cuiSerialNum.destroy(DESTROY_DEC);

		
	

	/* Create the following object 
		IssuerAndSerialNumber := SEQUENCE {
											issuer	Name,
											serialNumber CertifcateSerialNumber
								  }
	*/
	CBaseDERCollection cbdcIssSer;
	cbdcIssSer = cbdIssuer + cuiSerialNum; //cseqIssuer + cuiSerialNum;
	CHECKNULLANDSIZE(cbdcIssSer)

	// Deleting the encoded data
	cbdIssuer.destroy(DESTROY_ENC);
	cuiSerialNum.destroy(DESTROY_ENC);

	CSequence cseqIssSer(cbdcIssSer);
	CHECKNULLANDSIZE(cseqIssSer)

	// Deleting the input/decoded data
	cseqIssSer.destroy(DESTROY_DEC);
	if(cbdcIssSer.BaseDERBlob)
	{
		delete cbdcIssSer.BaseDERBlob;
		cbdcIssSer.BaseDERBlob = NULL;
	}

	
	/** Create a digest algorithm object which looks as follows -
	SEQUENCE {
				OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
				NULL
			}

	This is the digestAlgorithm object - ex; For SHA1
	**/
	
	//Create the digest algorithm object identifier
	
	char szAlgObjId[256];
	switch(i_nHashAlg)
	{
	case VSSC_HASH_SHA1 :
		strcpy(szAlgObjId, vssc_szOID_OIWSEC_sha1);
		break;

	case VSSC_HASH_MD2:
		strcpy(szAlgObjId, vssc_szOID_RSA_MD2);
		break;

	case VSSC_HASH_MD5:
		strcpy(szAlgObjId, vssc_szOID_RSA_MD5);
		break;
	}

	CObjectIdentifier cobjidAlgId(strlen(szAlgObjId), (unsigned char *)szAlgObjId);
	CHECKNULLANDSIZE(cobjidAlgId)

	// Deleting the input/decoded data
	cobjidAlgId.destroy(DESTROY_DEC);

	//Create a null object
	CNull cnullObj;
	
	//Create the digest algorithm identifier
	CBaseDERCollection cbdcAlgId;
	cbdcAlgId = cobjidAlgId + cnullObj ;
	CHECKNULLANDSIZE(cbdcAlgId)

	// Deleting the encoded data
	cobjidAlgId.destroy(DESTROY_ENC);

	CSequence cseqDigestAlg(cbdcAlgId);
	CHECKNULLANDSIZE(cseqDigestAlg)

	// Deleting the input/decoded data
	cseqDigestAlg.destroy(DESTROY_DEC);
	if(cbdcAlgId.BaseDERBlob)
	{
		delete cbdcAlgId.BaseDERBlob;
		cbdcAlgId.BaseDERBlob = NULL;
	}
	

	// Create Signed Attributes.
	// We expect a DER encoded collection as the input to this function (pbAuthAttribColection, cbAuthAttribColection) 
	// It is then encoded as a Tagged value. We expect only the collection since a function can be used to construct the
	// DER collection and then this DER collection is formed into a SET for Signing according to RFC 2630(CMS) and then
	// we use the same DER collection to form a Tagged Value. 

	CTaggedValue ctvAuthAttrib;
	
	if(cbAuthAttribCollection != 0 && pbAuthAttribCollection != NULL)
	{
		//CDERBlob cderblobAuthAttrib(cbAuthAttribColection, pbAuthAttribColection);
		//CBaseDER cbasederAuthAttrib(cderblobAuthAttrib);
		CBaseDERCollection bdcAuthAttrib(cbAuthAttribCollection, pbAuthAttribCollection); 
		CHECKNULLANDSIZE(bdcAuthAttrib)
		CTaggedValue ctvAuthAttrib_temp(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, false, *(bdcAuthAttrib.BaseDERBlob));
		CHECKNULLANDSIZE(ctvAuthAttrib_temp)

		// Deleting the input/decoded data
		ctvAuthAttrib_temp.destroy(DESTROY_DEC);

		ctvAuthAttrib = ctvAuthAttrib_temp;
		bAuthAtrrib = true;
	}

	/** Create a rsa encryption algorithm object which looks as follows -
	SEQUENCE {
				OBJECT IDENTIFIER rsaEncryption (1.2.840.113549.1.1.1)
				NULL
			}
	This is the digestEncryptionAlgorithm object.
	**/

	//Create an object identifier for the OID 1.2.840.113549.1.1.1
	char szRSAEncObjID[512];

	if(pSignerInfo->EncObjId.pszObjId == NULL)
	{
		return -1;
	}

	if(strcmp(pSignerInfo->EncObjId.pszObjId, vssc_szOID_RSA_RSA) != 0)
	{
		// return saying not supported value;
		return -1;
	}
	strcpy(szRSAEncObjID, pSignerInfo->EncObjId.pszObjId);

	CObjectIdentifier cobjidRSAEncObjId(strlen(szRSAEncObjID), (unsigned char *)szRSAEncObjID);
	CHECKNULLANDSIZE(cobjidRSAEncObjId)

	// Deleting the input/decoded data
	cobjidRSAEncObjId.destroy(DESTROY_DEC);

	//Create a sequence containing the above OID and null object
	cbdcAlgId = cobjidRSAEncObjId + cnullObj;
	CHECKNULLANDSIZE(cbdcAlgId)

	// Deleting the encoded data
	cobjidRSAEncObjId.destroy(DESTROY_ENC);

	CSequence cseqDigestEncAlg(cbdcAlgId );
	CHECKNULLANDSIZE(cseqDigestEncAlg)

	// Deleting the input/decoded data
	cseqDigestEncAlg.destroy(DESTROY_DEC);
	if(cbdcAlgId.BaseDERBlob)
	{
		delete cbdcAlgId.BaseDERBlob;
		cbdcAlgId.BaseDERBlob = NULL;
	}

	//Create an octet string containing the signature (encryptedDigest).
	// The signature is already in the Network Byte order and also the COctetString again 
	// converts it into Network Byte order. So, reverse it before passing it to COctetString.

	// New Simder change
	//reverse(pSignatureBlob->cbData, pSignatureBlob->pbData);

	COctetString cosEncryptedDigest(pSignatureBlob->cbData, pSignatureBlob->pbData);
	CHECKNULLANDSIZE(cosEncryptedDigest)
	// Deleting the input/decoded data
	cosEncryptedDigest.destroy(DESTROY_DEC);


	
		/* Create the signer info object which is defined as follows -
	SignerInfo := SEQUENCE {
							version INTEGER,
							issuerAndSerialNumber IssuerAndSerialNumber,
							digestAlgorithm DigestAlgorithmIdentifier,
							authenticate Attributes 
											[0] IMPLICIT Attributes OPTIONAL
							digestEncryptionAlgorithm DignestEncryptionAlgorithmIdentifier,
							encryptedDigest EncryptedDigest
				  }
	*/

	unsigned char byteVer = 0x01;
	CUniversalInteger cuiVersion(sizeof(unsigned char),(unsigned char*)&byteVer);
	CHECKNULLANDSIZE(cuiVersion)

	// Deleting the input/decoded data
	cuiVersion.destroy(DESTROY_DEC);

	CBaseDERCollection cbdcSignerInfo;
	// AuthAttrib present
	if(bAuthAtrrib == true)
	{
		cbdcSignerInfo = cuiVersion + cseqIssSer + cseqDigestAlg + ctvAuthAttrib + cseqDigestEncAlg + cosEncryptedDigest;
	}
	else // AuthAttrib not present
	{
		cbdcSignerInfo = cuiVersion + cseqIssSer + cseqDigestAlg + cseqDigestEncAlg + cosEncryptedDigest;
	}

	CHECKNULLANDSIZE(cbdcSignerInfo)

	// Deleting the encoded data
	//cuiVersion.destroy(DESTROY_ENC);
	cseqIssSer.destroy(DESTROY_ENC);
	//cseqDigestAlg.destroy(DESTROY_ENC);
	cosEncryptedDigest.destroy(DESTROY_ENC);

	CSequence cseqSignerInfo(cbdcSignerInfo);
	CHECKNULLANDSIZE(cseqSignerInfo)

	// Deleting the input/decoded data
	cseqSignerInfo.destroy(DESTROY_DEC);
	if(cbdcSignerInfo.BaseDERBlob)
	{
		delete cbdcSignerInfo.BaseDERBlob;
		cbdcSignerInfo.BaseDERBlob = NULL;
	}

	/* Create the SignerInfos object defined as
			SignerInfos := CHOICE {
								siSet	SET OF SignerInfo,
								siSequence SEQUENCE OF SignerInfo
							}

			We will choose a set and this set will include only one SignerInfo object created above
	*/

	CBaseDERCollection cbdcSignerInfos;
	cbdcSignerInfos = cseqSignerInfo;

	// Deleting the encoded data
	cseqSignerInfo.destroy(DESTROY_ENC);

	CSet csetSignerInfos(cbdcSignerInfos);
	CHECKNULLANDSIZE(csetSignerInfos)

	// Deleting the input/decoded data
	csetSignerInfos.destroy(DESTROY_DEC);
	if(cbdcSignerInfos.BaseDERBlob)
	{
		delete cbdcSignerInfos.BaseDERBlob;
		cbdcSignerInfos.BaseDERBlob = NULL;

	}

	/* Create the DigestAlgorithmIdentifiers object defined as follows 
		DigestAlgorithmIdenitifiers := CHOICE {
											daSet SET OF DigestAlgorithmIdentifier
											daSequence SEQUENCE OF DigestAlgorithmIdentifier
										}

		Where the DigestAlgorithmIdentifier specify the digest algorithm being used
		

		We will use a set, and we use only one digest algorithm viz. sha1 so our object will look like
		SET {
			SEQUENCE {
				OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
				NULL
				}
			}

	*/

	CBaseDERCollection cbdcDigestAlgorithms;
	cbdcDigestAlgorithms = cseqDigestAlg; // cseqDigestAlg constructed earlier.

	CHECKNULLANDSIZE(cbdcDigestAlgorithms)

	// Deleting the encoded data
	cseqDigestAlg.destroy(DESTROY_ENC);

	CSet csetDigestAlgorithms(cbdcDigestAlgorithms);
	CHECKNULLANDSIZE(csetDigestAlgorithms)

	// Deleting the input/decoded data
	csetDigestAlgorithms.destroy(DESTROY_DEC);
	if(cbdcDigestAlgorithms.BaseDERBlob)
	{
		delete cbdcDigestAlgorithms.BaseDERBlob;
		cbdcDigestAlgorithms.BaseDERBlob = NULL;
	}


	/*
		Create the content info object defined as 
		ContentInfo := SEQUENCE {
									contentType contentType;
									content [0] EXPLICIT CONTENTS.&Type((Contents)(@contentType)) OPTIONAL
								}
					
	*/
	
	
	char szDataObjID[512];
	strcpy(szDataObjID, vssc_szOID_RSA_data);

	CObjectIdentifier cobjidData(strlen(szDataObjID), (unsigned char*)szDataObjID);
	CHECKNULLANDSIZE(cobjidData)

	// Deleting the input/decoded data
	cobjidData.destroy(DESTROY_DEC);

	CBaseDERCollection cbdcContentInfo;

	
	if(bDetached == true) // detached signature
	{
		cbdcContentInfo = cobjidData;
	}
	else // attached signature
	{
		// New Simder change
		//reverse(cbData, pbData);
		if(pbData && cbData > 0)
		{
			COctetString cosData(cbData, pbData);
			CHECKNULLANDSIZE(cosData)
			// Deleting the input/decoded data
			cosData.destroy(DESTROY_DEC);

			CTaggedValue ctvData(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, false, *(cosData.BaseDERBlob));
			CHECKNULLANDSIZE(ctvData)

			// Deleting the input/decoded data
			ctvData.destroy(DESTROY_DEC);

			// Deleting the encoded data
			cosData.destroy(DESTROY_ENC);
		
			cbdcContentInfo = cobjidData + ctvData;
			CHECKNULLANDSIZE(cbdcContentInfo)

			// Deleting the encoded data
			ctvData.destroy(DESTROY_ENC);

		}
		else
		{
			return -1;
		}
	}

	// Deleting the encoded data
	cobjidData.destroy(DESTROY_ENC);

	CSequence cseqContentInfo(cbdcContentInfo);
	CHECKNULLANDSIZE(cseqContentInfo)

	// Deleting the input/decoded data
	cseqContentInfo.destroy(DESTROY_DEC);
	if(cbdcContentInfo.BaseDERBlob)
	{	
		delete cbdcContentInfo.BaseDERBlob;
		cbdcContentInfo.BaseDERBlob = NULL;

	}

	/*

		Create the cert chain - for now the cert chain will have only one cert - the end cert.
		In the future we can add the intermediate CAs in the chain
	*/
	//Create the BaseDER object for the cert

	// But the input ie pSignerInfo->CertEncoded should have the complete chain.
	// if we don't assume a complete chain in pSignerInfo->CertEncoded then we may have to construct something like this
	// cbdc = cbdcert1 + cbdcert2 + ....
	// ctvcertChain(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(cbdc.BaseDERBlob));
	// for this input should be array of CertEncoded instead of just CertEncoded
	// I think the above comments have been take care of -- remove the comments later.

	// certs are optional find out if they are present

	bool bCertsPresent = false;
	if(pSignerInfo->CertEncoded.pbData && pSignerInfo->CertEncoded.cbData > 0)
	{
		bCertsPresent = true;
	}
	else
	{
		bCertsPresent = false;
	}

	CBaseDERCollection cbdcSignedData;
	if(bCertsPresent)
	{
		CDERBlob cderblobEndCert(pSignerInfo->CertEncoded.cbData, pSignerInfo->CertEncoded.pbData);
		CBaseDER cbasederEndCert(cderblobEndCert);

		// Deleting the input/decoded data
		if(cderblobEndCert.pbData)
		{
			free(cderblobEndCert.pbData);
			cderblobEndCert.pbData = NULL;
		}
		cbasederEndCert.destroy(DESTROY_DEC);

		CTaggedValue ctvCertChain(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, false, cbasederEndCert);
		CHECKNULLANDSIZE(ctvCertChain)

		// Deleting the input/decoded data
		ctvCertChain.destroy(DESTROY_DEC);

		// Deleting the encoded data
		cbasederEndCert.destroy(DESTROY_ENC);

		/* Create the signed data content  which is defined as
			SignedData := SEQUENCE {
								version INTEGER,
								digestAlgorithms DigestAlgorithmIdentifiers,
								conentInfo ContentInfo,
								certificates CHOICE {
											certSet [0] IMPLICIT ExtendedCertificatesAndCertificates
											certSequence [2] IMPLICIT Certificates
										} OPTIONAL,
								signerInfos SignerInfos
							}
								
		*/

		cbdcSignedData = cuiVersion + csetDigestAlgorithms + cseqContentInfo + ctvCertChain + csetSignerInfos;

		// Deleting the encoded data
		ctvCertChain.destroy(DESTROY_ENC);
	}
	else
	{
		cbdcSignedData = cuiVersion + csetDigestAlgorithms + cseqContentInfo + csetSignerInfos;
	}

	CHECKNULLANDSIZE(cbdcSignedData)

	// Deleting the encoded data
	cuiVersion.destroy(DESTROY_ENC);
//	csetDigestAlgorithms.destroy(DESTROY_ENC);
	cseqContentInfo.destroy(DESTROY_ENC);
	csetSignerInfos.destroy(DESTROY_ENC);


		

	CSequence cseqSignedData(cbdcSignedData);
	CHECKNULLANDSIZE(cseqSignedData)

	// Deleting the input/decoded data
	cseqSignedData.destroy(DESTROY_DEC);
	if(cbdcSignedData.BaseDERBlob)
	{
		delete cbdcSignedData.BaseDERBlob;
		cbdcSignedData.BaseDERBlob = NULL;
	}



	/* Finally create the signed data pkcs7 which looks like this
		SEQUENCE {
				OBJECT IDENTIFIER signedData (1.2.840.113549.1.7.2)
				[0] {
					signedData
				}
			}
		(Note this an object of type ContentInfo)
	*/

	char szSignedDataObjId[512];
	strcpy(szSignedDataObjId, vssc_szOID_RSA_signedData);

	
	CObjectIdentifier cobjidSignedData(strlen(szSignedDataObjId), (unsigned char*)szSignedDataObjId);
	CHECKNULLANDSIZE(cobjidSignedData)

	// Deleting the input/decoded data
	cobjidSignedData.destroy(DESTROY_DEC);
	
	CTaggedValue ctvSignedDataContent(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, false, *(cseqSignedData.BaseDERBlob));
	CHECKNULLANDSIZE(ctvSignedDataContent)

	// Deleting the input/decoded data
	ctvSignedDataContent.destroy(DESTROY_DEC);

	cbdcContentInfo = cobjidSignedData + ctvSignedDataContent;
	CHECKNULLANDSIZE(cbdcContentInfo)

	// Deleting the encoded data
	cobjidSignedData.destroy(DESTROY_ENC);
	ctvSignedDataContent.destroy(DESTROY_ENC);

	cseqContentInfo = cbdcContentInfo;
	CHECKNULLANDSIZE(cseqContentInfo)

	// Deleting the input/decoded data
	cseqContentInfo.destroy(DESTROY_DEC);

	
	
	unsigned int dwB64P7Size;
	char* pszB64P7 = NULL;


	_Base64Encode((char*)(cseqContentInfo.BaseDERBlob->pbData),cseqContentInfo.BaseDERBlob->cbData,
		NULL,&dwB64P7Size);
	if(dwB64P7Size == 0)
	{
		return -1;
	}
	pszB64P7 = new char[dwB64P7Size+1];
	if(!pszB64P7)
		retVal = -1;
	else
	{
		_Base64Encode((char*)(cseqContentInfo.BaseDERBlob->pbData),cseqContentInfo.BaseDERBlob->cbData,
			pszB64P7,&dwB64P7Size);
		if(dwB64P7Size == 0)
		{
			return -1;
		}
		pszB64P7[dwB64P7Size] = '\0';
		*pszSignedData64 = pszB64P7;
	}

	return retVal;

}




int CreateEnvelopedData(PVS_ENCRYPTED_CONTENT_INFO pEncryptedContent,
						PVS_RECIPIENT_INFO pRecipientInfo[],
						int nRecipientInfo,
						char **ppszEnvelopedData64)
{

	int retVal = 0;
	if(nRecipientInfo == 0 || pEncryptedContent == NULL || pRecipientInfo == NULL)
	{
		return -1;
	}
	
	unsigned char byteVer = 0x00;
	CUniversalInteger cuiVersion(sizeof(unsigned char),(unsigned char*)&byteVer);
	CHECKNULLANDSIZE(cuiVersion)

	// Deleting the input/decoded data
	cuiVersion.destroy(DESTROY_DEC);


	CBaseDERCollection cbdcRecipientInfos;
	for(int i = 0; i < nRecipientInfo; i++)
	{

		// Check for NULL and len for all the elements before creating the recipient info.
		if(pRecipientInfo[i] == NULL 
			|| pRecipientInfo[i]->Issuer.pbData == NULL || pRecipientInfo[i]->Issuer.cbData <= 0
			|| pRecipientInfo[i]->SerialNumber.pbData == NULL || pRecipientInfo[i]->SerialNumber.cbData <= 0
			|| pRecipientInfo[i]->KeyEncryptionAlgID.pszObjId == NULL
			|| pRecipientInfo[i]->EncryptedKey.pbData == NULL || pRecipientInfo[i]->EncryptedKey.cbData <= 0)
		{
			return -1;
		}
		
		//Obtain the (DER Encoded) issuer dn sequence of the cert
		CSequence cseqIssuer;
		CDERBlob cdbIssuer(pRecipientInfo[i]->Issuer.cbData, pRecipientInfo[i]->Issuer.pbData);

		CBaseDER cbdIssuer(cdbIssuer);

		// Deleting the input/decoded data
		
		if(cdbIssuer.pbData)
		{
			free(cdbIssuer.pbData);
			cdbIssuer.pbData = 0;
		}
		


		//Obtain the (DER Encoded) serial number of the cert
			
		CUniversalInteger cuiSerialNum(pRecipientInfo[i]->SerialNumber.cbData, pRecipientInfo[i]->SerialNumber.pbData);
		CHECKNULLANDSIZE(cuiSerialNum)

		// Deleting the input/decoded data
		cuiSerialNum.destroy(DESTROY_DEC);
			
		

		/* Create the following object 
			IssuerAndSerialNumber := SEQUENCE {
												issuer	Name,
												serialNumber CertifcateSerialNumber
									  }
		*/
		CBaseDERCollection cbdcIssSer;
		cbdcIssSer = cbdIssuer + cuiSerialNum; //cseqIssuer + cuiSerialNum;
		CHECKNULLANDSIZE(cbdcIssSer)

		// Deleting the encoded data
		cbdIssuer.destroy(DESTROY_ENC);
		cuiSerialNum.destroy(DESTROY_ENC);

		CSequence cseqIssSer(cbdcIssSer);
		CHECKNULLANDSIZE(cseqIssSer)

		// Deleting the input/decoded data
		cseqIssSer.destroy(DESTROY_DEC);

		// Deleting the input/decoded data
		if(cbdcIssSer.BaseDERBlob)
		{
			delete cbdcIssSer.BaseDERBlob;
			cbdcIssSer.BaseDERBlob = NULL;
		}
		
		

		//Create an object identifier for the OID 1.2.840.113549.1.1.1

		char szRSAEncObjID[512];
			
		if(strcmp(vssc_szOID_RSA_RSA, pRecipientInfo[i]->KeyEncryptionAlgID.pszObjId) != 0)
		{ 
			// return not supported;
			return -1;
		}
		strcpy(szRSAEncObjID, pRecipientInfo[i]->KeyEncryptionAlgID.pszObjId);

		CObjectIdentifier cobjidRSAEncObjId(strlen(szRSAEncObjID), (unsigned char *)szRSAEncObjID);
		CHECKNULLANDSIZE(cobjidRSAEncObjId)

		// Deleting the input/decoded data
		cobjidRSAEncObjId.destroy(DESTROY_DEC);

	
		//Create a null object
		CNull cnullObj;

		//Create a sequence containing the above OID and null object
		CBaseDERCollection cbdcAlgId;
		cbdcAlgId = cobjidRSAEncObjId + cnullObj;

		CHECKNULLANDSIZE(cbdcAlgId)

		// Deleting the encoded data
		cobjidRSAEncObjId.destroy(DESTROY_ENC);
		

		CSequence cseqKeyEncAlg(cbdcAlgId );
		CHECKNULLANDSIZE(cbdcAlgId)

		// Deleting the input/decoded data
		cseqKeyEncAlg.destroy(DESTROY_DEC);

		// Deleting the input/decoded data
		
		if(cbdcAlgId.BaseDERBlob)
		{
			delete cbdcAlgId.BaseDERBlob;
			cbdcAlgId.BaseDERBlob = NULL;

		}
		

		//Create an octet string containing the Asymmetrically encrypted key.
		// New Simder change
		reverse(pRecipientInfo[i]->EncryptedKey.cbData, pRecipientInfo[i]->EncryptedKey.pbData);
		COctetString cmyosEncryptedKey(pRecipientInfo[i]->EncryptedKey.cbData, pRecipientInfo[i]->EncryptedKey.pbData);
		CHECKNULLANDSIZE(cmyosEncryptedKey)

		// Deleting the input/decoded data
		cmyosEncryptedKey.destroy(DESTROY_DEC);

		/*Create the Recipient object which is defined as follows
			RecipientInfo ::= SEQUENCE {
									version Version,
									issuerAndSerialNumber IssuerAndSerialNumber,
									keyEncryptionAlgorithm KeyEncryptionAlgorithmIdentifier,
									encryptedKey EncryptedKey }
		 */


		CBaseDERCollection cbdcRecipientInfo;
		cbdcRecipientInfo = cuiVersion + cseqIssSer + cseqKeyEncAlg + cmyosEncryptedKey;
		CHECKNULLANDSIZE(cbdcRecipientInfo)

		// Deleting the encoded data
		//cuiVersion.destroy(DESTROY_ENC);		
		cmyosEncryptedKey.destroy(DESTROY_ENC);
		cseqIssSer.destroy(DESTROY_ENC);
		cseqKeyEncAlg.destroy(DESTROY_ENC);



		CSequence cseqRecipientInfo(cbdcRecipientInfo);
		CHECKNULLANDSIZE(cseqRecipientInfo)

		// Deleting the input/decoded data
		cseqRecipientInfo.destroy(DESTROY_DEC);

		// Deleting the input/decoded data
		if(cbdcRecipientInfo.BaseDERBlob)
		{
			delete cbdcRecipientInfo.BaseDERBlob;
			cbdcRecipientInfo.BaseDERBlob = NULL;

		}
		
		cbdcRecipientInfos = cbdcRecipientInfos + cseqRecipientInfo;
		CHECKNULLANDSIZE(cbdcRecipientInfos)

		// Deleting the encoded data
		cseqRecipientInfo.destroy(DESTROY_ENC);


	}


	/*Create the RecipientInfos object which is defined as 
		RecipientInfos ::= SET OF RecipientInfo 
	*/

	CSet csetRecipientInfos(cbdcRecipientInfos);

	CHECKNULLANDSIZE(csetRecipientInfos)

	// Deleting the input/decoded data
	csetRecipientInfos.destroy(DESTROY_DEC);
	if(cbdcRecipientInfos.BaseDERBlob)
	{
		delete cbdcRecipientInfos.BaseDERBlob;
		cbdcRecipientInfos.BaseDERBlob = NULL;
	}
	

	// Now we create the EncryptedContentInfo
	char szDataObjID[512];
	strcpy(szDataObjID, vssc_szOID_RSA_data);


	CObjectIdentifier cobjidData(strlen(szDataObjID), (unsigned char*)szDataObjID);
	CHECKNULLANDSIZE(cobjidData)

	// Deleting the input/decoded data
	cobjidData.destroy(DESTROY_DEC);



	//Create an object identifier for the OID 1.2.840.113549.3.7
	//Note this OID can be passed as a parameter (symmetric key), in which case switch block is needed.
	// Need to use the OID passed in RecipientInfo structure to set the OIDs.
	
	char szEncObjID[512];

	if(pEncryptedContent->ContentEncryptionAlgID.pszObjId == NULL)
	{
		return -1;
	}

	if(pEncryptedContent->ContentEncryptionAlgID.Parameters.pbData == NULL 
		|| pEncryptedContent->ContentEncryptionAlgID.Parameters.cbData <= 0)
	{
		return -1;
	}


	strcpy(szEncObjID, pEncryptedContent->ContentEncryptionAlgID.pszObjId);

	CObjectIdentifier cobjidEncObjId(strlen(szEncObjID), (unsigned char *)szEncObjID);
	CHECKNULLANDSIZE(cobjidEncObjId)
	cobjidEncObjId.destroy(DESTROY_DEC);
	
	CNull cnullObj;
	
	CBaseDERCollection cbdcAlgId;

	if(strcmp(szEncObjID, vssc_szOID_RSA_RC2CBC) == 0)
	{
		// Required for RC2 only
		unsigned int byteLen = 0x0000003A;
		CUniversalInteger cuiLen(1,(unsigned char*)&byteLen);

		// Deleting the input/decoded data
		cuiLen.destroy(DESTROY_DEC);

		//This reverse was required only for PTA cert.
		// BUGBUG - check this.
		reverse(pEncryptedContent->ContentEncryptionAlgID.Parameters.cbData, pEncryptedContent->ContentEncryptionAlgID.Parameters.pbData);
		COctetString myosEncAlgIDParam(pEncryptedContent->ContentEncryptionAlgID.Parameters.cbData, 
							pEncryptedContent->ContentEncryptionAlgID.Parameters.pbData);

		CHECKNULLANDSIZE(myosEncAlgIDParam)

		// Deleting the input/decoded data
		myosEncAlgIDParam.destroy(DESTROY_DEC);

		CBaseDERCollection cbdcParam;
		cbdcParam = cuiLen + myosEncAlgIDParam;

		CHECKNULLANDSIZE(cbdcParam)
		
		// Deleting the encoded data
		cuiLen.destroy(DESTROY_ENC);
		myosEncAlgIDParam.destroy(DESTROY_ENC);

		CSequence cseqParam(cbdcParam);
		CHECKNULLANDSIZE(cseqParam)

		// Deleting the input/decoded data
		cseqParam.destroy(DESTROY_DEC);

		// Deleting the input/decoded data
		if(cbdcParam.BaseDERBlob)
		{
			delete cbdcParam.BaseDERBlob;
			cbdcParam.BaseDERBlob = NULL;
		}
		

		cbdcAlgId = cobjidEncObjId + cseqParam;
		CHECKNULLANDSIZE(cbdcAlgId)

		// Deleting the encoded data
		cobjidEncObjId.destroy(DESTROY_ENC);

		// Deleting the encoded data
		cseqParam.destroy(DESTROY_ENC);
	
	}
	else // 3DES
	{
		if(pEncryptedContent->ContentEncryptionAlgID.Parameters.pbData != NULL)
		{
			
			COctetString myosEncAlgIDParam(pEncryptedContent->ContentEncryptionAlgID.Parameters.cbData, 
				pEncryptedContent->ContentEncryptionAlgID.Parameters.pbData);
			CHECKNULLANDSIZE(myosEncAlgIDParam)

			// Deleting the input/decoded data
			myosEncAlgIDParam.destroy(DESTROY_DEC);

			cbdcAlgId = cobjidEncObjId + myosEncAlgIDParam;
			CHECKNULLANDSIZE(cbdcAlgId)

			// Deleting the encoded data
			myosEncAlgIDParam.destroy(DESTROY_ENC);
		}
		else
		{
			cbdcAlgId = cobjidEncObjId + cnullObj;
		}

		// Deleting the encoded data
		cobjidEncObjId.destroy(DESTROY_ENC);
	}
	


	//Create a sequence containing the above OID and param
	CSequence cseqSymmKeyEncAlg(cbdcAlgId );
	CHECKNULLANDSIZE(cseqSymmKeyEncAlg)

	// Deleting the input/decoded data
	cseqSymmKeyEncAlg.destroy(DESTROY_DEC);
	if(cbdcAlgId.BaseDERBlob)
	{
		delete cbdcAlgId.BaseDERBlob;
		cbdcAlgId.BaseDERBlob = NULL;
	}
	
	
	//Create an octet string containing the Encrypted Content.
	// New Simder change
	//reverse(pEncryptedContent->EncryptedContent.cbData, pEncryptedContent->EncryptedContent.pbData);

	// EncryptedContent is optional
	bool bEncryptedContentPresent = false;
	if(pEncryptedContent->EncryptedContent.pbData && pEncryptedContent->EncryptedContent.cbData > 0 )
	{
		bEncryptedContentPresent = true;

	}
	else
	{
		bEncryptedContentPresent = false;
	}

	/*Create the EncryptedContentInfo object which is defined as follows
			EncryptedContentInfo ::= SEQUENCE {
									contentType ContentType,
									contentEncryptionAlgorithm
										ContentEncryptionAlgorithmIdentifier,
									encryptedContent
										[0] IMPLICIT EncryptedContent OPTIONAL }

		*/

	CBaseDERCollection cbdcEncryptedContentInfo;
	if(bEncryptedContentPresent)
	{
		COctetString cmyosEncryptedContent(pEncryptedContent->EncryptedContent.cbData, 
											pEncryptedContent->EncryptedContent.pbData);
		CHECKNULLANDSIZE(cmyosEncryptedContent)
		
		// Deleting the input/decoded data
		cmyosEncryptedContent.destroy(DESTROY_DEC);

		CTaggedValue ctvEncryptedContent(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, true,  *(cmyosEncryptedContent.BaseDERBlob));

		CHECKNULLANDSIZE(ctvEncryptedContent)


		// Deleting the input/decoded data
		ctvEncryptedContent.destroy(DESTROY_DEC);

		// Deleting the encoded data
		cmyosEncryptedContent.destroy(DESTROY_ENC);

		cbdcEncryptedContentInfo = cobjidData + cseqSymmKeyEncAlg + ctvEncryptedContent;

		CHECKNULLANDSIZE(cbdcEncryptedContentInfo)

		// Deleting the encoded data
		ctvEncryptedContent.destroy(DESTROY_ENC);
		cseqSymmKeyEncAlg.destroy(DESTROY_ENC);

		// Deleting the encoded data
		cobjidData.destroy(DESTROY_ENC);
	}
	else
	{
		cbdcEncryptedContentInfo = cobjidData + cseqSymmKeyEncAlg;
		CHECKNULLANDSIZE(cbdcEncryptedContentInfo)
	}


	//Indefinite length
	CSequence cseqEncryptedContentInfo(cbdcEncryptedContentInfo, true);

	CHECKNULLANDSIZE(cseqEncryptedContentInfo)

	// Deleting the input/decoded data
	cseqEncryptedContentInfo.destroy(DESTROY_DEC);
	if(cbdcEncryptedContentInfo.BaseDERBlob)
	{
		delete cbdcEncryptedContentInfo.BaseDERBlob;
		cbdcEncryptedContentInfo.BaseDERBlob = NULL;
	}
	

	/*Create the Enveloped Data content which is defined as 
			EnvelopedData ::= SEQUENCE {
						version Version,
						recipientInfos RecipientInfos,
						encryptedContentInfo EncryptedContentInfo }
	*/

	CBaseDERCollection cbdcEnvelopedData;
	cbdcEnvelopedData = cuiVersion + csetRecipientInfos + cseqEncryptedContentInfo;
	CHECKNULLANDSIZE(cbdcEnvelopedData)


	// Deleting the encoded data
	cuiVersion.destroy(DESTROY_ENC);

	// Deleting the encoded data
	csetRecipientInfos.destroy(DESTROY_ENC);
	cseqEncryptedContentInfo.destroy(DESTROY_ENC);


	//Indefinite length
	CSequence cseqEnvelopedData(cbdcEnvelopedData, true);

	CHECKNULLANDSIZE(cseqEnvelopedData)

	// Deleting the input/decoded data
	cseqEnvelopedData.destroy(DESTROY_DEC);
	if(cbdcEnvelopedData.BaseDERBlob)
	{
		delete cbdcEnvelopedData.BaseDERBlob;
		cbdcEnvelopedData.BaseDERBlob = NULL;
	}
	


	/* Finally create the enveloped data pkcs7 which looks like this
		SEQUENCE {
				OBJECT IDENTIFIER envelopedData (1.2.840.113549.1.7.3)
				[0] {
					envelopedData
				}
			}
		(Note this an object of type ContentInfo)
	*/

	char szEnvelopedDataObjId[512];
	strcpy(szEnvelopedDataObjId, vssc_szOID_RSA_envelopedData);

	CObjectIdentifier cobjidEnvelopedData(strlen(szEnvelopedDataObjId), (unsigned char*)szEnvelopedDataObjId);
	if(cobjidEnvelopedData.BaseDERBlob->pbData == NULL || cobjidEnvelopedData.BaseDERBlob->cbData == 0)
	{
		return -1;
	}

	// Deleting the input/decoded data
	cobjidEnvelopedData.destroy(DESTROY_DEC);
		

	//Indefinite length
	CTaggedValue ctvEnvelopedDataContent(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, true, *(cseqEnvelopedData.BaseDERBlob));

	CHECKNULLANDSIZE(ctvEnvelopedDataContent)
		
	// Deleting the encoded data
	cseqEnvelopedData.destroy(DESTROY_ENC);

	CBaseDERCollection cbdcContentInfo;
	
	cbdcContentInfo = cobjidEnvelopedData + ctvEnvelopedDataContent;

	CHECKNULLANDSIZE(cbdcContentInfo)

	// Deleting the encoded data
	ctvEnvelopedDataContent.destroy(DESTROY_ENC);

	// Deleting the encoded data
	cobjidEnvelopedData.destroy(DESTROY_ENC);


	//Indefinite length
	CSequence cseqContentInfo(cbdcContentInfo, true);

	CHECKNULLANDSIZE(cseqContentInfo)
	
	// Deleting the input/decoded data
	cseqContentInfo.destroy(DESTROY_DEC);
	if(cbdcContentInfo.BaseDERBlob)
	{
		delete cbdcContentInfo.BaseDERBlob;
		cbdcContentInfo.BaseDERBlob = NULL;
	}
	

		
	unsigned int dwB64P7Size;
	char* pszB64P7 = NULL;


	_Base64Encode((char*)(cseqContentInfo.BaseDERBlob->pbData),cseqContentInfo.BaseDERBlob->cbData,
		NULL,&dwB64P7Size);
	if(dwB64P7Size == 0)
	{
		return -1;
	}

	pszB64P7 = new char[dwB64P7Size+1];

	if(!pszB64P7)
	{
		retVal = -1;
	}
	else
	{
		_Base64Encode((char*)(cseqContentInfo.BaseDERBlob->pbData),cseqContentInfo.BaseDERBlob->cbData,
			pszB64P7,&dwB64P7Size);
		if(dwB64P7Size == 0)
		{
			return -1;
		}
		pszB64P7[dwB64P7Size] = '\0';
		*ppszEnvelopedData64 = pszB64P7;

	}

	return retVal;
	

}


/*
void _Base64Encode(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize)
{
	char _encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'} ;


	if ( pOutput == NULL )
	{
		*dwOutputSize = !(dwInputSize % 3) ? (dwInputSize/3)*4 : ((dwInputSize/3)*4) + 4 ;
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\n' '\r' after 76 chars in encoded output.
	}
	else
	{
		unsigned int		remainingSize, seventySixCount ;
		char		*inputPtr, *outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				unsigned int tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}
			else if(remainingSize == 2)
			{
				unsigned int tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = '=' ;
			}
			else
			{
				unsigned int tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[2] ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = _encode[(tmp & 0x0000003F)] ;
			}
			*dwOutputSize += 4 ;
			seventySixCount += 4 ;
			remainingSize -= 3 ;
			inputPtr += 3 ;
			outputPtr += 4 ;

			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}
		}
	}

}



void reverse(unsigned int size,
			 unsigned char *input)
{
  unsigned int	sizeby2 = size/2 ;
  char		tmpchar ;

  for (unsigned int i = 0 ; i < sizeby2 ; i++ )
  {
	  tmpchar = input[i] ;
	  input[i] = input[size-1-i] ;
	  input[size-1-i] = tmpchar ;
  }
}
*/

void FormatUTCTime(char *szUTCTime)
{
	time_t ltime;
	struct tm  *gmt;
	char szTemp[4];
	char szTemp1[4];
	int temp;

	//YYMMDDHHMMSSZ

	time( &ltime );
	gmt = gmtime( &ltime );

	//YY
	itoa(gmt->tm_year, szTemp, 10);
	temp = gmt->tm_year;
	if(temp > 100)
	{
		temp = temp - 100;
		itoa(temp , szTemp, 10);
	}
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcpy(szUTCTime, szTemp1);
	}
	else
	{
		strcpy(szUTCTime, szTemp);
	}
		

	
	//MM Month (0 - 11; January = 0)

	temp = gmt->tm_mon + 1;
	itoa(temp, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//DD
	temp = gmt->tm_mday;
	itoa(gmt->tm_mday, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//HH
	temp = gmt->tm_hour;
	itoa(gmt->tm_hour, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//MM
	temp = gmt->tm_min;
	itoa(gmt->tm_min, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//SS
	temp = gmt->tm_sec;
	itoa(gmt->tm_sec, szTemp, 10);
	if(temp < 10)
	{
		strcpy(szTemp1, "0");
		strcat(szTemp1, szTemp);
		strcat(szUTCTime, szTemp1);
	}else
	{
		strcat(szUTCTime, szTemp);
	}

	//Z
	strcat(szUTCTime, "Z");

	
}


// Creates the AuthAtribute DER encoded collection.
// This collection can be used later to form a SET or Tagged Value.
// The digest of the MIMEEntity is one of the members of the AUTHATTRIB struct.
// Singing Time is calculated locally.

int CreateAuthAttrib(AUTHATTRIB *aaAuthAttrib)
{
		/*
	SEQUENCE {
               OBJECT IDENTIFIER
                 contentType (1 2 840 113549 1 9 3)
              SET {
                 OBJECT IDENTIFIER data (1 2 840 113549 1 7 1)
                 }
              }
	*/

	if(aaAuthAttrib->pbMimeEntityDigest == NULL || aaAuthAttrib->cbMimeEntityDigest <= 0
		|| aaAuthAttrib->pbCertIssuerDN == NULL || aaAuthAttrib->cbCertIssuerDN <= 0
		|| aaAuthAttrib->pbCertSerialNum == NULL || aaAuthAttrib->cbCertSerialNum <= 0)
	{
		return -1;
	}

	char *szContentTypeObjID = "1.2.840.113549.1.9.3";

	CObjectIdentifier cobjidContentType(strlen(szContentTypeObjID), (unsigned char *)(szContentTypeObjID));
	CHECKNULLANDSIZE(cobjidContentType)

	// Deleting the input/decoded data
	cobjidContentType.destroy(DESTROY_DEC);

	CObjectIdentifier cobjidData(strlen(vssc_szOID_RSA_data), (unsigned char *)(vssc_szOID_RSA_data));
	CHECKNULLANDSIZE(cobjidData)

	// Deleting the input/decoded data
	cobjidData.destroy(DESTROY_DEC);

	CSet csetData(cobjidData);
	CHECKNULLANDSIZE(csetData)

	// Deleting the input/decoded data
	csetData.destroy(DESTROY_DEC);

	CBaseDERCollection bdcContentType;
	bdcContentType = cobjidContentType + csetData;

	CHECKNULLANDSIZE(bdcContentType)
	
	// Deleting the encoded data
	cobjidContentType.destroy(DESTROY_ENC);
	csetData.destroy(DESTROY_ENC);

	
	// 1
	CSequence cseqContentType(bdcContentType);
	CHECKNULLANDSIZE(cseqContentType)

	// Deleting the input/decoded data
	cseqContentType.destroy(DESTROY_DEC);
	if(bdcContentType.BaseDERBlob)
	{
		delete bdcContentType.BaseDERBlob;
		bdcContentType.BaseDERBlob = NULL;
	}

	/*
	          SEQUENCE {
               OBJECT IDENTIFIER
                 signingTime (1 2 840 113549 1 9 5)
               SET {
                 UTCTime '001230003712Z'
                 }
               }
	*/

	char *szSigningTime = "1.2.840.113549.1.9.5";
	CObjectIdentifier cobjidSignTime(strlen(szSigningTime), (unsigned char *)(szSigningTime));
	CHECKNULLANDSIZE(cobjidSignTime)

	// Deleting the input/decoded data
	cobjidSignTime.destroy(DESTROY_DEC);


	char szUTCTime[64];
	FormatUTCTime(szUTCTime);
	//strcpy(szUTCTime, "010103194943Z");

	CUTCTime cutcSignTime(strlen(szUTCTime), (unsigned char *)szUTCTime);
	CHECKNULLANDSIZE(cutcSignTime)
	// Deleting the input/decoded data
	cutcSignTime.destroy(DESTROY_DEC);

	CSet	csetSignTime(cutcSignTime);
	CHECKNULLANDSIZE(csetSignTime)

	// Deleting the input/decoded data
	csetSignTime.destroy(DESTROY_DEC);

	// Deleting the encoded data
	cutcSignTime.destroy(DESTROY_ENC);

	CBaseDERCollection	bdcSignTime;
	bdcSignTime = cobjidSignTime + csetSignTime;
	CHECKNULLANDSIZE(bdcSignTime)

	// Deleting the encoded data
	cobjidSignTime.destroy(DESTROY_ENC);
	csetSignTime.destroy(DESTROY_ENC);

	//2
	CSequence cseqSignTime(bdcSignTime);
	CHECKNULLANDSIZE(cseqSignTime)

	// Deleting the input/decoded data
	cseqSignTime.destroy(DESTROY_DEC);

	/*
	SEQUENCE {
	  OBJECT IDENTIFIER
		messageDigest (1 2 840 113549 1 9 4)
	  SET {
		OCTET STRING
		  Hash of Mime Entity ONLY ...
		}
	  }
	*/

	char *szMsgDigestObjId = "1.2.840.113549.1.9.4" ;
	CObjectIdentifier cobjidMsgDigest(strlen(szMsgDigestObjId), (unsigned char *)szMsgDigestObjId) ;
	CHECKNULLANDSIZE(cobjidMsgDigest)

	// Deleting the input/decoded data
	cobjidMsgDigest.destroy(DESTROY_DEC);

	//New Simder change
	//reverse(aaAuthAttrib->cbMimeEntityDigest, aaAuthAttrib->pbMimeEntityDigest) ;

	
	COctetString cosMsgDigest(aaAuthAttrib->cbMimeEntityDigest, (unsigned char *)aaAuthAttrib->pbMimeEntityDigest) ;
	CHECKNULLANDSIZE(cosMsgDigest)
	// Deleting the input/decoded data
	cosMsgDigest.destroy(DESTROY_DEC);

	CSet csMsgDigest(cosMsgDigest);
	CHECKNULLANDSIZE(csMsgDigest)

	// Deleting the input/decoded data
	csMsgDigest.destroy(DESTROY_DEC);

	// Deleting the encoded data
	cosMsgDigest.destroy(DESTROY_ENC);



	CBaseDERCollection cbdcMsgDigest ;

	cbdcMsgDigest = cobjidMsgDigest + csMsgDigest ;
	CHECKNULLANDSIZE(cbdcMsgDigest)

	// Deleting the encoded data
	cobjidMsgDigest.destroy(DESTROY_ENC);
	csMsgDigest.destroy(DESTROY_ENC);

	//3
	CSequence csqMsgDigest(cbdcMsgDigest) ;
	CHECKNULLANDSIZE(csqMsgDigest)

	// Deleting the input/decoded data
	csqMsgDigest.destroy(DESTROY_DEC);
	if(cbdcMsgDigest.BaseDERBlob)
	{
		delete cbdcMsgDigest.BaseDERBlob;
		cbdcMsgDigest.BaseDERBlob = NULL;
	}

	
	/*
            SEQUENCE {
             OBJECT IDENTIFIER
               sMIMECapabilities (1 2 840 113549 1 9 15)
             SET {
               SEQUENCE {
                 SEQUENCE {
                   OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
                   INTEGER 128
                   }
                 SEQUENCE {
                   OBJECT IDENTIFIER sha1 (1 3 14 3 2 26)
                   }
                 SEQUENCE {
                   OBJECT IDENTIFIER md5 (1 2 840 113549 2 5)
                   }
                 }
               }
             }

	*/


	CObjectIdentifier cobjidSMIMECap(strlen(vssc_szOID_RSA_SMIMECapabilities), (unsigned char *)vssc_szOID_RSA_SMIMECapabilities);
	CHECKNULLANDSIZE(cobjidSMIMECap)

	// Deleting the input/decoded data
	cobjidSMIMECap.destroy(DESTROY_DEC);

	/*
	CObjectIdentifier cobjidRC2CBC(strlen(vssc_szOID_RSA_RC2CBC), (unsigned char *)vssc_szOID_RSA_RC2CBC);

	unsigned int byteLen = 0x00000080;
	CUniversalInteger cuiLen(2,(unsigned char*)&byteLen);

	CBaseDERCollection bdcRC2CBC;

	bdcRC2CBC = cobjidRC2CBC + cuiLen;

	CSequence cseqRC2CBC(bdcRC2CBC);

	CObjectIdentifier cobjidSHA1(strlen(vssc_szOID_OIWSEC_sha1), (unsigned char *)vssc_szOID_OIWSEC_sha1);
	CSequence cseqSHA1(cobjidSHA1);

	CObjectIdentifier cobjidMD5(strlen(vssc_szOID_RSA_MD5), (unsigned char *)vssc_szOID_RSA_MD5);
	CSequence cseqMD5(cobjidMD5);

	CBaseDERCollection bdcSMIMECap;
	bdcSMIMECap =  cseqRC2CBC + cseqSHA1 + cseqMD5;

	CSequence csqSMIMECap(bdcSMIMECap) ;
	*/

	CBaseDERCollection bdcSMIMECap;
	for(int i = 0; i < aaAuthAttrib->nCaps; i++)
	{
		CBaseDERCollection bdcCap;
		char *szObjID = aaAuthAttrib->SMIMECapabilities[i].pszObjId;
		if(szObjID)
		{
			CObjectIdentifier cobjidCap(strlen(szObjID), (unsigned char *)szObjID);
			if(aaAuthAttrib->SMIMECapabilities[i].Parameters.pbData &&
				aaAuthAttrib->SMIMECapabilities[i].Parameters.cbData > 0)
			{
				CUniversalInteger cuiLen(2,(unsigned char*)aaAuthAttrib->SMIMECapabilities[i].Parameters.pbData);
				bdcCap = cobjidCap + cuiLen;
				
			}
			else
			{
				bdcCap = cobjidCap;
			}
		}

		CHECKNULLANDSIZE(bdcCap)

		CSequence csqCap(bdcCap);
		CHECKNULLANDSIZE(csqCap)
		bdcSMIMECap = bdcSMIMECap + csqCap;
		CHECKNULLANDSIZE(bdcSMIMECap)

	}

	CSequence csqSMIMECap(bdcSMIMECap) ;
	CHECKNULLANDSIZE(csqSMIMECap)


	// Deleting the input/decoded data
	csqSMIMECap.destroy(DESTROY_DEC);
	if(bdcSMIMECap.BaseDERBlob)
	{
		delete bdcSMIMECap.BaseDERBlob;
		bdcSMIMECap.BaseDERBlob = NULL;
	}

	CSet csetSMIMECap(csqSMIMECap);
	CHECKNULLANDSIZE(csetSMIMECap)

	// Deleting the input/decoded data
	csetSMIMECap.destroy(DESTROY_DEC);

	// Deleting the encoded data
	csqSMIMECap.destroy(DESTROY_ENC);


	CBaseDERCollection bdcSMIMECaps;

	bdcSMIMECaps = cobjidSMIMECap + csetSMIMECap;

	CHECKNULLANDSIZE(bdcSMIMECaps)

	// Deleting the encoded data
	cobjidSMIMECap.destroy(DESTROY_ENC);
	csetSMIMECap.destroy(DESTROY_ENC);


	//4
	CSequence cseqSMIMECaps(bdcSMIMECaps);
	CHECKNULLANDSIZE(cseqSMIMECaps)

	// Deleting the input/decoded data
	cseqSMIMECaps.destroy(DESTROY_DEC);
	if(bdcSMIMECaps.BaseDERBlob)
	{	

		delete bdcSMIMECaps.BaseDERBlob;
		bdcSMIMECaps.BaseDERBlob = NULL;
	}

	/*
         SEQUENCE {
           OBJECT IDENTIFIER '1 3 6 1 4 1 311 16 4'
           SET {
             SEQUENCE {
               SEQUENCE {
                 SET {
                   SEQUENCE {
                     OBJECT IDENTIFIER
                       organizationName (2 5 4 10)
                     PrintableString 'VeriSign'
                     }
                   }
                 SET {
                   SEQUENCE {
                     OBJECT IDENTIFIER
                       organizationalUnitName (2 5 4 11)
                     PrintableString 'VeriSign Class 2 OnSite Individual CA'
                     }
                   }
                 }
               INTEGER
               38 4C 91 DE D1 FA 78 8C CF D7 C8 2D E4 A4 64 13
               }
             }
           }
         
	*/

	
	char *szUnKnown = "1.3.6.1.4.1.311.16.4";
	CObjectIdentifier cobjidUnKnown(strlen(szUnKnown), (unsigned char*)szUnKnown);
	CHECKNULLANDSIZE(cobjidUnKnown)
	// Deleting the input/decoded data
	cobjidUnKnown.destroy(DESTROY_DEC);

	//Obtain the (DER Encoded) issuer dn sequence of the cert
	CSequence cseqIssuer;
	CDERBlob cdbIssuer(aaAuthAttrib->cbCertIssuerDN, aaAuthAttrib->pbCertIssuerDN);
	CBaseDER cbdIssuer(cdbIssuer);

	// Deleting the input/decoded data
	cbdIssuer.destroy(DESTROY_DEC);
	

	//Obtain the (DER Encoded) serial number of the cert
		
	CUniversalInteger cuiSerialNum(aaAuthAttrib->cbCertSerialNum, aaAuthAttrib->pbCertSerialNum);
	CHECKNULLANDSIZE(cuiSerialNum)
	// Deleting the input/decoded data
	cuiSerialNum.destroy(DESTROY_DEC);

	CBaseDERCollection cbdcIssuerNameSerialNum;
	cbdcIssuerNameSerialNum = cbdIssuer + cuiSerialNum; //cseqIssuer + cuiSerialNum;
	CHECKNULLANDSIZE(cbdcIssuerNameSerialNum)

	// Deleting the encoded data
	cbdIssuer.destroy(DESTROY_ENC);
	cuiSerialNum.destroy(DESTROY_ENC);

	CSequence cseqIssuerNameSerialNum(cbdcIssuerNameSerialNum);
	CHECKNULLANDSIZE(cseqIssuerNameSerialNum)

	// Deleting the input/decoded data
	cseqIssuerNameSerialNum.destroy(DESTROY_DEC);
	if(cbdcIssuerNameSerialNum.BaseDERBlob)
	{
		delete cbdcIssuerNameSerialNum.BaseDERBlob; 
		cbdcIssuerNameSerialNum.BaseDERBlob = NULL;
	}

	CSet csetIssuerNameSerialNum(cseqIssuerNameSerialNum) ;
	CHECKNULLANDSIZE(csetIssuerNameSerialNum)

	// Deleting the input/decoded data
	csetIssuerNameSerialNum.destroy(DESTROY_DEC);

	// Deleting the encoded data
	cseqIssuerNameSerialNum.destroy(DESTROY_ENC);

	CBaseDERCollection bdcUnknown;

	bdcUnknown = cobjidUnKnown + csetIssuerNameSerialNum;
	CHECKNULLANDSIZE(bdcUnknown)

	// Deleting the encoded data
	cobjidUnKnown.destroy(DESTROY_ENC);
	csetIssuerNameSerialNum.destroy(DESTROY_ENC);

	//5
	CSequence cseqUnknown(bdcUnknown);
	CHECKNULLANDSIZE(cseqUnknown)

	// Deleting the input/decoded data
	cseqUnknown.destroy(DESTROY_DEC);
	if(bdcUnknown.BaseDERBlob)
	{
		delete bdcUnknown.BaseDERBlob;
		bdcUnknown.BaseDERBlob = NULL;
	}

	CBaseDERCollection bdcAuthAttribute;

	bdcAuthAttribute = cseqContentType + cseqSignTime + csqMsgDigest + cseqSMIMECaps + cseqUnknown;
	CHECKNULLANDSIZE(bdcAuthAttribute)

	// Deleting the encoded data
	cseqContentType.destroy(DESTROY_ENC);
	cseqSignTime.destroy(DESTROY_ENC); 
	csqMsgDigest.destroy(DESTROY_ENC); 
	cseqSMIMECaps.destroy(DESTROY_ENC); 
	cseqUnknown.destroy(DESTROY_ENC); 

	//CTaggedValue ctvAuthAttribute(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(bdcAuthAttribute.BaseDERBlob));
	//CSet csetAuthAttribute(bdcAuthAttribute);

	//aaAuthAttrib->cbAuthAttrib = ctvAuthAttribute.BaseDERBlob->cbData ;
	//aaAuthAttrib->cbAuthAttrib = csetAuthAttribute.BaseDERBlob->cbData;

	aaAuthAttrib->cbAuthAttrib = bdcAuthAttribute.BaseDERBlob->cbData;

	aaAuthAttrib->pbAuthAttrib = (unsigned char*) malloc(aaAuthAttrib->cbAuthAttrib) ;

	//memcpy(aaAuthAttrib->pbAuthAttrib, ctvAuthAttribute.BaseDERBlob->pbData, aaAuthAttrib->cbAuthAttrib) ;
	//memcpy(aaAuthAttrib->pbAuthAttrib, csetAuthAttribute.BaseDERBlob->pbData, aaAuthAttrib->cbAuthAttrib) ;
	memcpy(aaAuthAttrib->pbAuthAttrib, bdcAuthAttribute.BaseDERBlob->pbData, aaAuthAttrib->cbAuthAttrib) ;

	return 0;

}

#if 0
int CreateAuthAttrib (AUTHATTRIB *aaAuthAttrib)
{
	/*
	SEQUENCE {
               OBJECT IDENTIFIER
                 contentType (1 2 840 113549 1 9 3)
              SET {
                 OBJECT IDENTIFIER data (1 2 840 113549 1 7 1)
                 }
              }
	*/

	if(aaAuthAttrib->pbMimeEntityDigest == NULL || aaAuthAttrib->cbMimeEntityDigest <= 0
		|| aaAuthAttrib->pbCertIssuerDN == NULL || aaAuthAttrib->cbCertIssuerDN <= 0
		|| aaAuthAttrib->pbCertSerialNum == NULL || aaAuthAttrib->cbCertSerialNum <= 0)
	{
		return -1;
	}

	char *szContentTypeObjID = "1.2.840.113549.1.9.3";

	CObjectIdentifier cobjidContentType(strlen(szContentTypeObjID), (unsigned char *)(szContentTypeObjID));


	CObjectIdentifier cobjidData(strlen(vssc_szOID_RSA_data), (unsigned char *)(vssc_szOID_RSA_data));

	CSet csetData(cobjidData);

	CBaseDERCollection bdcContentType;
	bdcContentType = cobjidContentType + csetData;
	
	// 1
	CSequence cseqContentType(bdcContentType);

	/*
	          SEQUENCE {
               OBJECT IDENTIFIER
                 signingTime (1 2 840 113549 1 9 5)
               SET {
                 UTCTime '001230003712Z'
                 }
               }
	*/

	char *szSigningTime = "1.2.840.113549.1.9.5";
	CObjectIdentifier cobjidSignTime(strlen(szSigningTime), (unsigned char *)(szSigningTime));
	char szUTCTime[64];
	FormatUTCTime(szUTCTime);
	//strcpy(szUTCTime, "010103194943Z");

	CUTCTime cutcSignTime(strlen(szUTCTime), (unsigned char *)szUTCTime);

	CSet	csetSignTime(cutcSignTime);

	CBaseDERCollection	bdcSignTime;
	bdcSignTime = cobjidSignTime + csetSignTime;

	//2
	CSequence cseqSignTime(bdcSignTime);

	/*
	SEQUENCE {
	  OBJECT IDENTIFIER
		messageDigest (1 2 840 113549 1 9 4)
	  SET {
		OCTET STRING
		  Hash of Mime Entity ONLY ...
		}
	  }
	*/

	char *szMsgDigestObjId = "1.2.840.113549.1.9.4" ;
	CObjectIdentifier cobjidMsgDigest(strlen(szMsgDigestObjId), (unsigned char *)szMsgDigestObjId) ;

	//New Simder change
	//reverse(aaAuthAttrib->cbMimeEntityDigest, aaAuthAttrib->pbMimeEntityDigest) ;

	
	COctetString cosMsgDigest(aaAuthAttrib->cbMimeEntityDigest, (unsigned char *)aaAuthAttrib->pbMimeEntityDigest) ;

	CSet csMsgDigest(cosMsgDigest) ;

	CBaseDERCollection cbdcMsgDigest ;

	cbdcMsgDigest = cobjidMsgDigest + csMsgDigest ;

	//3
	CSequence csqMsgDigest(cbdcMsgDigest) ;

	/*
            SEQUENCE {
             OBJECT IDENTIFIER
               sMIMECapabilities (1 2 840 113549 1 9 15)
             SET {
               SEQUENCE {
                 SEQUENCE {
                   OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
                   INTEGER 128
                   }
                 SEQUENCE {
                   OBJECT IDENTIFIER sha1 (1 3 14 3 2 26)
                   }
                 SEQUENCE {
                   OBJECT IDENTIFIER md5 (1 2 840 113549 2 5)
                   }
                 }
               }
             }

	*/


	CObjectIdentifier cobjidSMIMECap(strlen(vssc_szOID_RSA_SMIMECapabilities), (unsigned char *)vssc_szOID_RSA_SMIMECapabilities);

	CObjectIdentifier cobjidRC2CBC(strlen(vssc_szOID_RSA_RC2CBC), (unsigned char *)vssc_szOID_RSA_RC2CBC);

	unsigned int byteLen = 0x00000080;
	CUniversalInteger cuiLen(2,(unsigned char*)&byteLen);

	CBaseDERCollection bdcRC2CBC;

	bdcRC2CBC = cobjidRC2CBC + cuiLen;

	CSequence cseqRC2CBC(bdcRC2CBC);

	CObjectIdentifier cobjidSHA1(strlen(vssc_szOID_OIWSEC_sha1), (unsigned char *)vssc_szOID_OIWSEC_sha1);
	CSequence cseqSHA1(cobjidSHA1);

	CObjectIdentifier cobjidMD5(strlen(vssc_szOID_RSA_MD5), (unsigned char *)vssc_szOID_RSA_MD5);
	CSequence cseqMD5(cobjidMD5);

	CBaseDERCollection bdcSMIMECap;
	bdcSMIMECap =  cseqRC2CBC + cseqSHA1 + cseqMD5;

	CSequence csqSMIMECap(bdcSMIMECap) ;

	CSet csetSMIMECap(csqSMIMECap);

	CBaseDERCollection bdcSMIMECaps;

	bdcSMIMECaps = cobjidSMIMECap + csetSMIMECap;

	//4
	CSequence cseqSMIMECaps(bdcSMIMECaps);

	/*
         SEQUENCE {
           OBJECT IDENTIFIER '1 3 6 1 4 1 311 16 4'
           SET {
             SEQUENCE {
               SEQUENCE {
                 SET {
                   SEQUENCE {
                     OBJECT IDENTIFIER
                       organizationName (2 5 4 10)
                     PrintableString 'VeriSign'
                     }
                   }
                 SET {
                   SEQUENCE {
                     OBJECT IDENTIFIER
                       organizationalUnitName (2 5 4 11)
                     PrintableString 'VeriSign Class 2 OnSite Individual CA'
                     }
                   }
                 }
               INTEGER
               38 4C 91 DE D1 FA 78 8C CF D7 C8 2D E4 A4 64 13
               }
             }
           }
         
	*/

	
	char *szUnKnown = "1.3.6.1.4.1.311.16.4";
	CObjectIdentifier cobjidUnKnown(strlen(szUnKnown), (unsigned char*)szUnKnown);

	//Obtain the (DER Encoded) issuer dn sequence of the cert
	CSequence cseqIssuer;
	CDERBlob cdbIssuer(aaAuthAttrib->cbCertIssuerDN, aaAuthAttrib->pbCertIssuerDN);
	CBaseDER cbdIssuer(cdbIssuer);

	//Obtain the (DER Encoded) serial number of the cert
		
	CUniversalInteger cuiSerialNum(aaAuthAttrib->cbCertSerialNum, aaAuthAttrib->pbCertSerialNum);

	CBaseDERCollection cbdcIssuerNameSerialNum;
	cbdcIssuerNameSerialNum = cbdIssuer + cuiSerialNum; //cseqIssuer + cuiSerialNum;
	CSequence cseqIssuerNameSerialNum(cbdcIssuerNameSerialNum);

	CSet csetIssuerNameSerialNum(cseqIssuerNameSerialNum) ;

	CBaseDERCollection bdcUnknown;

	bdcUnknown = cobjidUnKnown + csetIssuerNameSerialNum;

	//5
	CSequence cseqUnknown(bdcUnknown);

	CBaseDERCollection bdcAuthAttribute;

	bdcAuthAttribute = cseqContentType + cseqSignTime + csqMsgDigest + cseqSMIMECaps + cseqUnknown;

	//CTaggedValue ctvAuthAttribute(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(bdcAuthAttribute.BaseDERBlob));
	//CSet csetAuthAttribute(bdcAuthAttribute);

	//aaAuthAttrib->cbAuthAttrib = ctvAuthAttribute.BaseDERBlob->cbData ;
	//aaAuthAttrib->cbAuthAttrib = csetAuthAttribute.BaseDERBlob->cbData;

	aaAuthAttrib->cbAuthAttrib = bdcAuthAttribute.BaseDERBlob->cbData;

	aaAuthAttrib->pbAuthAttrib = (unsigned char*) malloc(aaAuthAttrib->cbAuthAttrib) ;

	//memcpy(aaAuthAttrib->pbAuthAttrib, ctvAuthAttribute.BaseDERBlob->pbData, aaAuthAttrib->cbAuthAttrib) ;
	//memcpy(aaAuthAttrib->pbAuthAttrib, csetAuthAttribute.BaseDERBlob->pbData, aaAuthAttrib->cbAuthAttrib) ;
	memcpy(aaAuthAttrib->pbAuthAttrib, bdcAuthAttribute.BaseDERBlob->pbData, aaAuthAttrib->cbAuthAttrib) ;

	return 0;
}
#endif //0


////////////PKCS7 Parser functions////////////////

int ParseSignerInfo2(unsigned char* pbSignerDataDerBlob,
					 unsigned int cbSignerDataBlobLen,
					 VS_SIGNER_INFO_PARSE *vssipSignerInfo )
{
	// BUG BUG - while returning from the errors the memory allocated has to be freed.

	memset(vssipSignerInfo, 0, sizeof(VS_SIGNER_INFO_PARSE));
	
	CBaseDERCollection cbdcSignerInfo(cbSignerDataBlobLen, pbSignerDataDerBlob);

	CBaseDERHierarchy cbdhSignerData(cbdcSignerInfo);
	if(cbdhSignerData.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree *dtSingerInfoSeq = &cbdhSignerData.m_DERTree;
	if(!dtSingerInfoSeq || dtSingerInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtCMSVersion = dtSingerInfoSeq->rightDERTree;

	//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
	if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}
	
	CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

	//We limit this implementation to assume that the version information can fit in a DWORD
	if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
	{
		return -1;
	}

	//Obtain the version bytes
	unsigned char byteVersion[4];
	for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
		byteVersion[i] = pcuiCMSVersion->pbData[i];
	for(unsigned int j=i;j<4; ++j)
		byteVersion[j] = 0x00;
	
	//Store the version in the SignedDataInfo
	//1
	vssipSignerInfo->dwSIVersion = *((_DWORD*)byteVersion);

	DERTree *dtIssuerDNSerNumSeq = dtCMSVersion->nextDERTree;

	if(!dtIssuerDNSerNumSeq || dtIssuerDNSerNumSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtIssuerDN = dtIssuerDNSerNumSeq->rightDERTree;
	
	if(!dtIssuerDN || dtIssuerDN->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	//copy the Issuer DN DER blob
	vssipSignerInfo->Issuer.cbData = dtIssuerDN->currentBaseDER->BaseDERBlob->cbData;
	vssipSignerInfo->Issuer.pbData = (unsigned char*)malloc(vssipSignerInfo->Issuer.cbData);
	
	if(!vssipSignerInfo->Issuer.pbData)
	{
		return -1;
	}

	memcpy(vssipSignerInfo->Issuer.pbData, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData,
			vssipSignerInfo->Issuer.cbData);

	DERTree *dtSerNum = dtIssuerDN->nextDERTree;

	//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
	if(!dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}

	CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
	if(!pcuiSerNum)
	{
		return -1;
	}

	vssipSignerInfo->SerialNumber.cbData = pcuiSerNum->cbData;
	vssipSignerInfo->SerialNumber.pbData = (_PBYTE)malloc(sizeof(unsigned char) * pcuiSerNum->cbData);
	if(!vssipSignerInfo->SerialNumber.pbData)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SerialNumber.pbData, pcuiSerNum->pbData, vssipSignerInfo->SerialNumber.cbData);


	DERTree *dtDigestAlgIdSeq = dtIssuerDNSerNumSeq->nextDERTree;
	if(!dtDigestAlgIdSeq || dtDigestAlgIdSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}


	DERTree *dtDigestAlgId = dtDigestAlgIdSeq->rightDERTree;
	if(!dtDigestAlgId || dtDigestAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	// 2 DigestAlgID
	vssipSignerInfo->DigestAlgId.pszObjId = (char*)malloc(dtDigestAlgId->currentBaseDER->cbData + 1);
	if(!vssipSignerInfo->DigestAlgId.pszObjId)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->DigestAlgId.pszObjId, dtDigestAlgId->currentBaseDER->pbData, dtDigestAlgId->currentBaseDER->cbData);
	vssipSignerInfo->DigestAlgId.pszObjId[dtDigestAlgId->currentBaseDER->cbData] = '\0';
	//vssdiSignedDataInfo->DigestAlgId.cbData = dtDigestAlgId->currentBaseDER->cbData;


	DERTree *dtDigestAlgIdParam = dtDigestAlgId->nextDERTree;
	if(!dtDigestAlgIdParam)
	{
		return -1;
	}

	// 3 DigestAlgID param
	if(dtDigestAlgIdParam->currentBaseDER->pbData)
	{
		vssipSignerInfo->DigestAlgId.Parameters.pbData = (unsigned char*)malloc(dtDigestAlgIdParam->currentBaseDER->cbData);
		if(!vssipSignerInfo->DigestAlgId.Parameters.pbData)
		{
			return -1;
		}
		memcpy(vssipSignerInfo->DigestAlgId.Parameters.pbData, dtDigestAlgIdParam->currentBaseDER->pbData, dtDigestAlgIdParam->currentBaseDER->cbData);
		vssipSignerInfo->DigestAlgId.Parameters.cbData = dtDigestAlgIdParam->currentBaseDER->cbData;
	}


	DERTree *dtSignedAttribs = dtDigestAlgIdSeq->nextDERTree;
	DERTree *dtSignedAttribsPre = NULL;
	DERTree *dtSigAlgIDSeq = NULL;

	bool bAttribPresent = false;

	if(dtSignedAttribs && (dtSignedAttribs->currentBaseDER->Class == CONTEXT_SPECIFIC && dtSignedAttribs->currentBaseDER->Encoding == CONSTRUCTED
			&& dtSignedAttribs->currentBaseDER->TagNumber == 0))
	{
		bAttribPresent = true;
	}

	if(bAttribPresent == true)
	{
		//copy signed attributes.
		dtSignedAttribsPre = dtDigestAlgIdSeq->nextDERTree;
		vssipSignerInfo->SignedAttributes.pbData = (unsigned char*)malloc(dtSignedAttribsPre->currentBaseDER->cbData);
		if(!vssipSignerInfo->SignedAttributes.pbData)
		{
			return -1;
		}
		vssipSignerInfo->SignedAttributes.cbData = dtSignedAttribsPre->currentBaseDER->cbData;
		memcpy(vssipSignerInfo->SignedAttributes.pbData, dtSignedAttribsPre->currentBaseDER->pbData,
		vssipSignerInfo->SignedAttributes.cbData);

	}

	if(dtSignedAttribsPre)
	{
		//Attrib present AlgID is Attribs next
		dtSigAlgIDSeq = dtSignedAttribsPre->nextDERTree;
	}
	else
	{
		// Attrib not present AlgID is IssuerDNSerialNum next
		dtSigAlgIDSeq = dtDigestAlgIdSeq->nextDERTree;
	}

	if(!dtSigAlgIDSeq || dtSigAlgIDSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}


	DERTree *dtSigAlgID = dtSigAlgIDSeq->rightDERTree;
	if(!dtSigAlgID || dtSigAlgID->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	vssipSignerInfo->SignatureAlgId.pszObjId = (char*)malloc(dtSigAlgID->currentBaseDER->cbData + 1);
	if(!vssipSignerInfo->SignatureAlgId.pszObjId)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SignatureAlgId.pszObjId, dtSigAlgID->currentBaseDER->pbData, dtSigAlgID->currentBaseDER->cbData);
	vssipSignerInfo->SignatureAlgId.pszObjId[dtSigAlgID->currentBaseDER->cbData] = '\0';
	

		
	DERTree *dtSigAlgIdParam = dtSigAlgID->nextDERTree;

	// 3 SigAlgID param
	if(dtSigAlgIdParam->currentBaseDER->pbData)
	{
		vssipSignerInfo->SignatureAlgId.Parameters.pbData = (unsigned char*)malloc(dtSigAlgIdParam->currentBaseDER->cbData);
		if(!vssipSignerInfo->SignatureAlgId.Parameters.pbData)
		{
			return -1;
		}
		memcpy(vssipSignerInfo->SignatureAlgId.Parameters.pbData, dtSigAlgIdParam->currentBaseDER->pbData,
				dtSigAlgIdParam->currentBaseDER->cbData);
		vssipSignerInfo->SignatureAlgId.Parameters.cbData = dtSigAlgIdParam->currentBaseDER->cbData;
	}

	// Signature Blob
	DERTree *dtSignatureValue = dtSigAlgIDSeq->nextDERTree;
		
	if(!dtSignatureValue || dtSignatureValue->currentBaseDER->Type != OCTET_STRING)
	{
		return -1;
	}
	vssipSignerInfo->SignatureValue.cbData = dtSignatureValue->currentBaseDER->cbData;
	vssipSignerInfo->SignatureValue.pbData = (unsigned char*)malloc(vssipSignerInfo->SignatureValue.cbData);
	if(!vssipSignerInfo->SignatureValue.pbData)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SignatureValue.pbData, dtSignatureValue->currentBaseDER->pbData, vssipSignerInfo->SignatureValue.cbData);
	
	return 0;
}

int ParseEnvelopedUsingCAPI(
							HCRYPTMSG hMsg,
							VS_ENVELOPEDDATA_INFO& vsEnvelopedDataInfo)
{
	// now we need to fill in all the Enveloped stuff
	DWORD errorCode = 0;
	
	do
	{

		DWORD cbDecoded = 0;

		// get the size of the encrypted contents
		if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_CONTENT_PARAM,     // Parameter type
			  0,                      // Index
			  NULL,              // Address for returned 
									  // information
			  &cbDecoded))            // Size of the returned 
									  // information
		{
			errorCode = GetLastError();

			if ( errorCode != ERROR_MORE_DATA )
				break;
		}
		
		vsEnvelopedDataInfo.EncryptedContent.EncryptedContent.pbData = (BYTE *) malloc(cbDecoded);
		
		if ( NULL == vsEnvelopedDataInfo.EncryptedContent.EncryptedContent.pbData )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}

		// now allocate for it
		if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_CONTENT_PARAM,     // Parameter type
			  0,                      // Index
			  vsEnvelopedDataInfo.EncryptedContent.EncryptedContent.pbData,              // Address for returned 
									  // information
			  &cbDecoded))            // Size of the returned 
									  // information
		{
			errorCode = GetLastError();
			break;
		}
		
		vsEnvelopedDataInfo.EncryptedContent.EncryptedContent.cbData = cbDecoded;

		// now get the version
		cbDecoded = sizeof(DWORD);

		if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_VERSION_PARAM,     // Parameter type
			  0,                      // Index
			  &vsEnvelopedDataInfo.dwVersion,
			  &cbDecoded))            // Size of the returned 
									  // information
		{
			errorCode = GetLastError();
			break;
		}

		// lets get the recipient information now

		// first find out how many of them are there
		cbDecoded = sizeof(DWORD);
		if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_RECIPIENT_COUNT_PARAM,     // Parameter type
			  0,                      // Index
			  &vsEnvelopedDataInfo.nRecipientInfos,
			  &cbDecoded))            // Size of the returned 
									  // information
		{
			errorCode = GetLastError();
			break;
		}

		// now for each of them we have to find the approp info
		// first allocate some space for the pointers
		vsEnvelopedDataInfo.pRecipientInfo = (PVS_RECIPIENT_INFO)malloc(
													sizeof(VS_RECIPIENT_INFO) * vsEnvelopedDataInfo.nRecipientInfos );

		if ( NULL == vsEnvelopedDataInfo.pRecipientInfo )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}
	

		// now lets get the required info in a loop
		for(int i = 0; i < vsEnvelopedDataInfo.nRecipientInfos; i++)
		{	
			memset(&(vsEnvelopedDataInfo.pRecipientInfo[i]),0, sizeof(VS_RECIPIENT_INFO));
			
			CMSG_CMS_RECIPIENT_INFO *pCertInfo = NULL;
			cbDecoded=0;

			if ( !CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_CMS_RECIPIENT_INFO_PARAM,     // Parameter type
			  i,                      // Index
			  NULL,
			  &cbDecoded))
			{
				errorCode = GetLastError();

				if ( errorCode != ERROR_MORE_DATA )
					break;				
			}
		
			// now allocate for it
			pCertInfo = (CMSG_CMS_RECIPIENT_INFO *) malloc(cbDecoded);
			if ( NULL == pCertInfo )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}

			memset(pCertInfo,0,cbDecoded);
		
			// now get the information
			if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_CMS_RECIPIENT_INFO_PARAM,     // Parameter type
			  i,                      // Index
			  (void*)pCertInfo,
			  &cbDecoded))            // Size of the returned 
									  // information
			{
				errorCode = GetLastError();
				break;
			}
			
			// we obtained the info lets fill the structures
			vsEnvelopedDataInfo.pRecipientInfo[i].EncryptedKey.cbData = pCertInfo->pKeyTrans->EncryptedKey.cbData;
			vsEnvelopedDataInfo.pRecipientInfo[i].EncryptedKey.pbData = (unsigned char*)malloc(
																		pCertInfo->pKeyTrans->EncryptedKey.cbData);
			if ( NULL == vsEnvelopedDataInfo.pRecipientInfo[i].EncryptedKey.pbData )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}
			memcpy(
					vsEnvelopedDataInfo.pRecipientInfo[i].EncryptedKey.pbData,
					pCertInfo->pKeyTrans->EncryptedKey.pbData,
					pCertInfo->pKeyTrans->EncryptedKey.cbData
				   );

			vsEnvelopedDataInfo.pRecipientInfo[i].Issuer.cbData = pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.Issuer.cbData;
			vsEnvelopedDataInfo.pRecipientInfo[i].Issuer.pbData = (unsigned char*)malloc(
													pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.Issuer.cbData);
			if ( NULL == vsEnvelopedDataInfo.pRecipientInfo[i].Issuer.pbData )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}
			memcpy(
					vsEnvelopedDataInfo.pRecipientInfo[i].Issuer.pbData,
					pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.Issuer.pbData,
					pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.Issuer.cbData
				  );	
				
			vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.Parameters.cbData = pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.Parameters.cbData;
			vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.Parameters.cbData);
			if ( NULL == vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}
			memcpy(vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData, pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.Parameters.pbData, pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.Parameters.cbData);	

			vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.pszObjId = (char*)malloc(strlen(pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.pszObjId)+1);
			if ( NULL == vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.pszObjId )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}
			memcpy(vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.pszObjId, pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.pszObjId,strlen(pCertInfo->pKeyTrans->KeyEncryptionAlgorithm.pszObjId)+1);	
				
			vsEnvelopedDataInfo.pRecipientInfo[i].SerialNumber.cbData = pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.SerialNumber.cbData;
			vsEnvelopedDataInfo.pRecipientInfo[i].SerialNumber.pbData = (unsigned char*)malloc(pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.SerialNumber.cbData);
			if ( NULL == vsEnvelopedDataInfo.pRecipientInfo[i].SerialNumber.pbData )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}
			memcpy(vsEnvelopedDataInfo.pRecipientInfo[i].SerialNumber.pbData,pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.SerialNumber.pbData,pCertInfo->pKeyTrans->RecipientId.IssuerSerialNumber.SerialNumber.cbData);	

			// now free the certInfo structure
			free(pCertInfo);
		
		} // end for

		// check to see if an error occured in the loop
		if ( 0 != errorCode )
			break;

		// now get the algid
		DWORD dwCryptAlgoIDLen = 0;
		CRYPT_ALGORITHM_IDENTIFIER* pstructCryptAlgoID = NULL;
		
		if ( !CryptMsgGetParam(
		  hMsg,                   // Handle to the message
		  CMSG_ENVELOPE_ALGORITHM_PARAM,     // Parameter type
		  0,                      // Index
		  NULL,
		  &dwCryptAlgoIDLen))
		{
			errorCode = GetLastError();

			if ( errorCode != ERROR_MORE_DATA )
				break;				
		}

		pstructCryptAlgoID = (CRYPT_ALGORITHM_IDENTIFIER*) malloc (dwCryptAlgoIDLen);
		if ( NULL == pstructCryptAlgoID )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}
		
		if (!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_ENVELOPE_ALGORITHM_PARAM,     // Parameter type
			  0,                      // Index
			  pstructCryptAlgoID,
			  &dwCryptAlgoIDLen))
		{
			errorCode = GetLastError();
			break;
		}
		
		vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId = (char*)malloc(strlen(pstructCryptAlgoID->pszObjId)+1);
		if ( NULL == vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}
		memcpy(vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId,pstructCryptAlgoID->pszObjId,strlen(pstructCryptAlgoID->pszObjId)+1);	

		vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.cbData = pstructCryptAlgoID->Parameters.cbData;
		vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(pstructCryptAlgoID->Parameters.cbData);
		if ( NULL == vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}
		// temp for now
		memset(vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,0,pstructCryptAlgoID->Parameters.cbData);
		free(pstructCryptAlgoID);
		
	}
	while(0);
	
	if ( 0 != errorCode )
	{
		/*// something went wrong
		// free whatever was allocated and set the params back to NULL
		if ( NULL != vsEnvelopedDataInfo.EncryptedContent.EncryptedContent.pbData )
			free(vsEnvelopedDataInfo.EncryptedContent.EncryptedContent.pbData);
		
		if ( NULL != vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData )
			free(vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData);

		if ( NULL != vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId )
			free ( vsEnvelopedDataInfo.EncryptedContent.ContentEncryptionAlgID.pszObjId);

		for(int i = 0; i < vsEnvelopedDataInfo.nRecipientInfos; i++)
		{
			if ( NULL != vsEnvelopedDataInfo.pRecipientInfo[i].EncryptedKey.pbData )
				free ( vsEnvelopedDataInfo.pRecipientInfo[i].EncryptedKey.pbData );

			if ( NULL != vsEnvelopedDataInfo.pRecipientInfo[i].Issuer.pbData )
				free ( vsEnvelopedDataInfo.pRecipientInfo[i].Issuer.pbData );

			if ( NULL != vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData )
				free ( vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData );

			if ( NULL != vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.pszObjId )
				free ( vsEnvelopedDataInfo.pRecipientInfo[i].KeyEncryptionAlgID.pszObjId );
			
			if ( NULL != vsEnvelopedDataInfo.pRecipientInfo[i].SerialNumber.pbData )
				free ( vsEnvelopedDataInfo.pRecipientInfo[i].SerialNumber.pbData );
		}
		*/

		return -1;
	}

	return 0;
}

int ParseSignedUsingCAPI(
						 HCRYPTMSG hMsg,
						 VS_SIGNEDDATA_INFO& vsSignedDataInfo)
{
	DWORD errorCode = 0;
	DWORD cbData = sizeof(DWORD);
	int retVal = 0;
	// algid
	DWORD dwCryptAlgoIDLen = 0;
	CRYPT_ALGORITHM_IDENTIFIER* pstructCryptAlgoID = NULL;
		
	
	do
	{

		// Get the version
		if ( !CryptMsgGetParam(
				  hMsg,                   // Handle to the message
				  CMSG_VERSION_PARAM,     // Parameter type
				  0,                      // Index
				  &vsSignedDataInfo.dwSDVersion,
				  &cbData))           // Size of the returned 
		{
			errorCode = GetLastError();
			break;
		}
		
		// now get the algid
		if ( !CryptMsgGetParam(
		  hMsg,                   // Handle to the message
		  CMSG_SIGNER_HASH_ALGORITHM_PARAM,     // Parameter type
		  0,                      // Index
		  NULL,
		  &dwCryptAlgoIDLen))
		{
			errorCode = GetLastError();

			if ( errorCode != ERROR_MORE_DATA )
				break;				
		}

		pstructCryptAlgoID = (CRYPT_ALGORITHM_IDENTIFIER*) malloc (dwCryptAlgoIDLen);
		if ( NULL == pstructCryptAlgoID )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}
		
		if (!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_SIGNER_HASH_ALGORITHM_PARAM,     // Parameter type
			  0,                      // Index
			  pstructCryptAlgoID,
			  &dwCryptAlgoIDLen))
		{
			errorCode = GetLastError();
			break;
		}
		
		
		vsSignedDataInfo.DigestAlgId.pszObjId = (char*)malloc(strlen(pstructCryptAlgoID->pszObjId)+1);
		if ( NULL == vsSignedDataInfo.DigestAlgId.pszObjId )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}
		memcpy(vsSignedDataInfo.DigestAlgId.pszObjId,pstructCryptAlgoID->pszObjId,strlen(pstructCryptAlgoID->pszObjId)+1);	

		if ( 0 != pstructCryptAlgoID->Parameters.cbData )
		{	
			vsSignedDataInfo.DigestAlgId.Parameters.pbData = (unsigned char*)malloc(pstructCryptAlgoID->Parameters.cbData);
			if ( NULL == vsSignedDataInfo.DigestAlgId.Parameters.pbData )
			{
				errorCode = E_OUTOFMEMORY;
				break;
			}	
			memcpy(vsSignedDataInfo.DigestAlgId.Parameters.pbData, pstructCryptAlgoID->Parameters.pbData,pstructCryptAlgoID->Parameters.cbData );
			vsSignedDataInfo.DigestAlgId.Parameters.cbData = pstructCryptAlgoID->Parameters.cbData;
		}

		free(pstructCryptAlgoID);
		
		// now get the contents
		DWORD cbDecoded = 0;
		
		if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_CONTENT_PARAM,     // Parameter type
			  0,                      // Index
			  NULL,              // Address for returned 
									  // information
			  &cbDecoded))            // Size of the returned 
									  // information
		{
			errorCode = GetLastError();

			if ( errorCode != ERROR_MORE_DATA )
				break;
		}
		
		vsSignedDataInfo.EncapContentInfo.pbData = (BYTE *) malloc(cbDecoded);
		
		if ( NULL == vsSignedDataInfo.EncapContentInfo.pbData )
		{
			errorCode = E_OUTOFMEMORY;
			break;
		}

		// now allocate for it
		if(!CryptMsgGetParam(
			  hMsg,                   // Handle to the message
			  CMSG_CONTENT_PARAM,     // Parameter type
			  0,                      // Index
			  vsSignedDataInfo.EncapContentInfo.pbData,              // Address for returned 
									  // information
			  &cbDecoded))            // Size of the returned 
									  // information
		{
			errorCode = GetLastError();
			break;
		}
		
		vsSignedDataInfo.EncapContentInfo.cbData = cbDecoded;

		// now get the signer information
		cbDecoded = 0;

		if(!CryptMsgGetParam(
				   hMsg,                   // Handle to the message
				   CMSG_ENCODED_SIGNER,		   // Parameter type
				   0,                      // Index
				   NULL,                   // Address for returned information
				   &cbDecoded))            // Size of the returned 										   
		{
			errorCode = GetLastError();
			break;
		}
		
		// Allocate memory.
		BYTE* pbSignerInfoBlob = NULL;
		pbSignerInfoBlob = (BYTE*) malloc(cbDecoded);
		
		// get the encrypted content
		if(!CryptMsgGetParam(
				  hMsg,                   // Handle to the message
				  CMSG_ENCODED_SIGNER,     // Parameter type
				  0,                      // Index
				  pbSignerInfoBlob,              // Address for returned 
										  // information
				  &cbDecoded))            // Size of the returned 
										  // information
		{
			errorCode = GetLastError();
			break;
		}
		
		retVal = ParseSignerInfo2(pbSignerInfoBlob,cbDecoded, &vsSignedDataInfo.SignerInfo);		
		// free the encoded signer info blob
		free(pbSignerInfoBlob);
		
		if ( 0 != retVal )
		{
			errorCode = -1;
			break;
		}


		// get the signer cert
		cbDecoded = 0;

		if(!CryptMsgGetParam(
				   hMsg,                   // Handle to the message
				   CMSG_CERT_PARAM,		   // Parameter type
				   0,                      // Index
				   NULL,                   // Address for returned 
										   // information
				   &cbDecoded))            // Size of the returned information
		{
			errorCode = GetLastError();
			break;
		}
	
		vsSignedDataInfo.CertificateSet.pbData = (BYTE *) malloc(cbDecoded);
		
		if(!CryptMsgGetParam(
				  hMsg,                   // Handle to the message
				  CMSG_CERT_PARAM,     // Parameter type
				  0,                      // Index
				  vsSignedDataInfo.CertificateSet.pbData, // Address for returned 
										  // information
				  &cbDecoded))            // Size of the returned 
										  // information
		{
			errorCode = GetLastError();
			break;		
		}
		
		vsSignedDataInfo.CertificateSet.cbData = cbDecoded;			
	
		// get the digest alg id


	}
	while(0);
	
	if ( 0 != errorCode )	
	{
		// do some clean ups and
		return -1;
	}

	return 0;
}

int ParsePKCS7DataUsingCAPI(
				  unsigned char *pbPKCS7Data,
				  unsigned int cbPKCS7Data,
				  VS_PKCS7_INFO *vsspiPKCS7Info
				   )
{
	
	int retVal = 0;
	HCRYPTPROV  hCryptProv;          // Provider handle
	DWORD errorCode = 0;
	// decode the message 
	HCRYPTMSG hMsg = NULL;

	memset(vsspiPKCS7Info, 0,  sizeof(VS_PKCS7_INFO));

	do
	{
		// get a handle to the provider
		if(!CryptAcquireContext(
				&hCryptProv,       // Address for handle to be returned.
				"prcuser",              // Use the current user's logon name.
				NULL,              // Use the default provider.
				PROV_RSA_FULL,     // Provider type.
				CRYPT_MACHINE_KEYSET))                // Zero allows access to private keys.
		{		
			errorCode = GetLastError();

			if ( !CryptAcquireContext(
				&hCryptProv,       // Address for handle to be returned.
				"prcuser",              // Use the current user's logon name.
				NULL,              // Use the default provider.
				PROV_RSA_FULL,     // Provider type.
				CRYPT_NEWKEYSET|CRYPT_MACHINE_KEYSET))// Zero allows access to private keys.
			{
				errorCode = GetLastError();
				break;
			}
		}
	
		hMsg = CryptMsgOpenToDecode(
			   PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,       // Encoding type
			   0,                      // Flags
			   0,                      // Message type (get from message)
			   hCryptProv,             // Cryptographic provider
			   NULL,                   // Recipient information
			   NULL);                  // Stream information
		
		
		// Update the message with the encoded BLOB
		if(!CryptMsgUpdate(
				hMsg,                 // Handle to the message
				pbPKCS7Data,        // Pointer to the encoded BLOB
				cbPKCS7Data,        // Size of the encoded BLOB
				TRUE))                // Last call
		{
			errorCode = GetLastError();
			break;
		}

		// now lets try and find the message type. 
		// do i have to call decode before this
		DWORD dwMsgType;
		DWORD cbData = sizeof(DWORD);
		
			if(!CryptMsgGetParam(
			hMsg,                   // Handle to the message
			CMSG_TYPE_PARAM,        // Parameter type
			0,                      // Index
			&dwMsgType,             // Address for returned 									// information
			&cbData))               // Size of the returned 
									// information
		{
			errorCode = GetLastError();
			break;
		}

		// ok now that we have the message type we will parse accordingly
		if ( dwMsgType == CMSG_ENVELOPED)
		{
			vsspiPKCS7Info->ePKCS7Type = PKCS7_ENVELOPED;
			retVal = ParseEnvelopedUsingCAPI(hMsg,vsspiPKCS7Info->EncryptedDataInfo);
		}
		else if ( dwMsgType == CMSG_SIGNED )
		{
			vsspiPKCS7Info->ePKCS7Type = PKCS7_SIGNED;
			retVal = ParseSignedUsingCAPI(hMsg,vsspiPKCS7Info->SignedDataInfo);
		}
	}
	while(0);
	
	if(hMsg)
		 CryptMsgClose(hMsg);


	//--------------------------------------------------------------------
	// Release the CSP.

	if(hCryptProv) 
	   CryptReleaseContext(hCryptProv,0);
	
	if ( 0 != errorCode )
	{
		return -1;
	}

	return retVal;
}




int ParsePKCS7Data(
				  unsigned char *pbPKCS7Data,
				  unsigned int cbPKCS7Data,
				  VS_PKCS7_INFO *vsspiPKCS7Info
				   )
{
	int retVal = 0;
	int nRecipients = 0;

	VS_PKCS7_TYPE ePKCS7_Type;

	memset(vsspiPKCS7Info, 0,  sizeof(VS_PKCS7_INFO));

	
	CBaseDERCollection bdcPKCS7Data(cbPKCS7Data, pbPKCS7Data);
	CBaseDERHierarchy	cbdhPKCS7Data(bdcPKCS7Data);

	if(cbdhPKCS7Data.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree* dtPKCS7ContentInfo = &cbdhPKCS7Data.m_DERTree;

	if(!dtPKCS7ContentInfo && dtPKCS7ContentInfo->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtPKCS7DataObjID = dtPKCS7ContentInfo->rightDERTree;
	
	//If OBJECT IDENTIFIER is not EnvelopedData (1.2.840.113549.1.7.3)
	if(memcmp(dtPKCS7DataObjID->currentBaseDER->pbData,
		vssc_szOID_RSA_envelopedData, dtPKCS7DataObjID->currentBaseDER->cbData) == 0)
	{
		ePKCS7_Type = PKCS7_ENVELOPED;
	}
	else if(memcmp(dtPKCS7DataObjID->currentBaseDER->pbData,
		vssc_szOID_RSA_signedData, dtPKCS7DataObjID->currentBaseDER->cbData) == 0)
	{
		ePKCS7_Type = PKCS7_SIGNED;
	}
	else
	{
		return -1;
	}
	
	vsspiPKCS7Info->ePKCS7Type = ePKCS7_Type;
	if(ePKCS7_Type == PKCS7_SIGNED)
	{
		retVal = ParseSignedData(dtPKCS7ContentInfo, &vsspiPKCS7Info->SignedDataInfo);
		if(retVal != 0)
		{
			return retVal;
		}

	}
	else if(ePKCS7_Type == PKCS7_ENVELOPED)
	{
		
		retVal = ParseEnvelopedData(dtPKCS7ContentInfo,
					&vsspiPKCS7Info->EncryptedDataInfo);


		if(retVal != 0)
		{
			return retVal;
		}

	}
	else 
	{
		//error return appropriate error code.
		return -1;
	}
	return 0;

}


#if 0


int ParseSignedData(unsigned char* pbSignedDataDerBlob,
					 unsigned int cbSignedDataBlobLen,
					 VS_SIGNEDDATA_INFO *vssdiSignedDataInfo )
{
	// BUG BUG - while returning from the errors the memory allocated has to be freed.

	int nRetVal = 0;
	memset(vssdiSignedDataInfo, 0, sizeof(VS_SIGNEDDATA_INFO));

	CBaseDERCollection cbdcSignedData(cbSignedDataBlobLen, pbSignedDataDerBlob);

	CBaseDERHierarchy cbdhSignedData(cbdcSignedData);
	if(cbdhSignedData.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree* dtSignedDataContentInfo = &cbdhSignedData.m_DERTree;

	if(!dtSignedDataContentInfo && dtSignedDataContentInfo->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}
	else
	{
		DERTree *dtSignedDataObjID = dtSignedDataContentInfo->rightDERTree;
		DERTree *dtSignedDataTag = dtSignedDataObjID->nextDERTree;

		if(!dtSignedDataObjID)
		{
			return -1;
		}
		
		//If OBJECT IDENTIFIER is not signedData (1.2.840.113549.1.7.2)
		if(memcmp(dtSignedDataObjID->currentBaseDER->pbData, vssc_szOID_RSA_signedData, dtSignedDataObjID->currentBaseDER->cbData) != 0)
		{
			return -1;
		}
		
		// Parse the SignedData
		if(!dtSignedDataTag || (dtSignedDataTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtSignedDataTag->currentBaseDER->Encoding != CONSTRUCTED
			|| dtSignedDataTag->currentBaseDER->TagNumber != 0))
		{
			return -1;
		}
		/*
			SignedData ::= SEQUENCE {
			version CMSVersion,
			digestAlgorithms DigestAlgorithmIdentifiers,
			encapContentInfo EncapsulatedContentInfo,
			certificates [0] IMPLICIT CertificateSet OPTIONAL,
			crls [1] IMPLICIT CertificateRevocationLists OPTIONAL,
			signerInfos SignerInfos }
		*/

		
		DERTree *dtSignedSeq = dtSignedDataTag->rightDERTree;
		
		//Check if SignedData is sequence
		if(!dtSignedSeq && dtSignedSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtCMSVersion = dtSignedSeq->rightDERTree;

		//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
		if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			return -1;
		}
		
		CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

		//We limit this implementation to assume that the version information can fit in a DWORD
		if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
		{
			return -1;
		}

		//Obtain the version bytes
		unsigned char byteVersion[4];
		for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
			byteVersion[i] = pcuiCMSVersion->pbData[i];
		for(unsigned int j=i;j<4; ++j)
			byteVersion[j] = 0x00;
		
		//Store the version in the SignedDataInfo
		//1
		vssdiSignedDataInfo->dwSDVersion = *((_DWORD*)byteVersion);

		/*
			digestAlgorithms DigestAlgorithmIdentifiers
			DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentifier
			DigestAlgorithmIdentifier ::= AlgorithmIdentifier
			Assuming only one DigestAlgorithmIdentifier.
		*/
		DERTree *dtSetDigestAlgID = dtCMSVersion->nextDERTree;

		if(!dtSetDigestAlgID || dtSetDigestAlgID->currentBaseDER->Type != SET)
		{
			return -1;
		}

		DERTree *dtDigestAlgIDSeq = dtSetDigestAlgID->rightDERTree;
		if(!dtDigestAlgIDSeq || dtDigestAlgIDSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtDigestAlgId = dtDigestAlgIDSeq->rightDERTree;
		if(!dtDigestAlgId || dtDigestAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			return -1;
		}

		// 2 DigestAlgID
		vssdiSignedDataInfo->DigestAlgId.pszObjId = (char*)malloc(dtDigestAlgId->currentBaseDER->cbData + 1);
		if(!vssdiSignedDataInfo->DigestAlgId.pszObjId)
		{
			return -1;
		}
		memcpy(vssdiSignedDataInfo->DigestAlgId.pszObjId, dtDigestAlgId->currentBaseDER->pbData, dtDigestAlgId->currentBaseDER->cbData);
		vssdiSignedDataInfo->DigestAlgId.pszObjId[dtDigestAlgId->currentBaseDER->cbData] = '\0';



		DERTree *dtDigestAlgIdParam = dtDigestAlgId->nextDERTree;
		if(!dtDigestAlgIdParam)
		{
			return -1;
		}

		// 3 DigestAlgID param
		if(dtDigestAlgIdParam->currentBaseDER->pbData)
		{
			vssdiSignedDataInfo->DigestAlgId.Parameters.pbData = (unsigned char*)malloc(dtDigestAlgIdParam->currentBaseDER->cbData);
			if(!vssdiSignedDataInfo->DigestAlgId.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vssdiSignedDataInfo->DigestAlgId.Parameters.pbData, dtDigestAlgIdParam->currentBaseDER->pbData, dtDigestAlgIdParam->currentBaseDER->cbData);
			vssdiSignedDataInfo->DigestAlgId.Parameters.cbData = dtDigestAlgIdParam->currentBaseDER->cbData;
		}


		DERTree *dtDataContSeq = dtSetDigestAlgID->nextDERTree;

		if(!dtDataContSeq || dtDataContSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtDataObjId = dtDataContSeq->rightDERTree;
		if(!dtDataObjId )
		{
			return -1;
		}

		//If OBJECT IDENTIFIER is not Data (1.2.840.113549.1.7.1)
		if(memcmp(dtDataObjId->currentBaseDER->pbData, vssc_szOID_RSA_data, dtDataObjId->currentBaseDER->cbData) != 0)
		{
			return -1;
		}

		DERTree *dtDataOctetsTag = dtDataObjId->nextDERTree;

		if(dtDataOctetsTag)
		{
			if((dtDataOctetsTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtDataOctetsTag->currentBaseDER->Encoding != CONSTRUCTED
			|| dtDataOctetsTag->currentBaseDER->TagNumber != 0)) 
			{
				return -1;
			}

			DERTree *dtDataOctets = dtDataOctetsTag->rightDERTree;

			// 4 Content signed  
			// Check whether it is Constructed encoding of simple type, octet string.
			DERTree* dtDataOctetsConstructed = dtDataOctetsTag->rightDERTree;

			if(dtDataOctetsConstructed && dtDataOctetsConstructed->currentBaseDER->Encoding == CONSTRUCTED && dtDataOctetsConstructed->currentBaseDER->Type == OCTET_STRING)
			{
				// Concatenate all the OCTET Strings and then copy
				DERTree* dtDataOctetsStart = dtDataOctetsConstructed->rightDERTree;
				if(!dtDataOctetsStart)
				{
					return -1;
				}

				DERTree* dtDataTemp = dtDataOctetsStart;
				unsigned long dwDataLen = 0;
				unsigned char* pbContentData = NULL;
				unsigned char* pbContentDataTmp = NULL;

				while(dtDataTemp)
				{
					dwDataLen += dtDataTemp->currentBaseDER->cbData;
					dtDataTemp = dtDataTemp->nextDERTree;
				}
				pbContentData = (unsigned char*)malloc(dwDataLen);
				pbContentDataTmp = pbContentData;

				dtDataTemp = dtDataOctetsStart;
				while(dtDataTemp)
				{
					memcpy(pbContentData, dtDataTemp->currentBaseDER->pbData, dtDataTemp->currentBaseDER->cbData);
					pbContentData += dtDataTemp->currentBaseDER->cbData;
					dtDataTemp = dtDataTemp->nextDERTree;
				}

				vssdiSignedDataInfo->EncapContentInfo.pbData = (unsigned char*)malloc(dwDataLen);
				memcpy(vssdiSignedDataInfo->EncapContentInfo.pbData, pbContentDataTmp, dwDataLen);
				vssdiSignedDataInfo->EncapContentInfo.cbData = dwDataLen;

				if(pbContentDataTmp)
				{
					free(pbContentDataTmp);
				}

			}
			else
			{
				if(dtDataOctets && dtDataOctets->currentBaseDER->pbData && dtDataOctets->currentBaseDER->cbData)
				{
					vssdiSignedDataInfo->EncapContentInfo.pbData = (unsigned char*)malloc(dtDataOctets->currentBaseDER->cbData);
					if(!vssdiSignedDataInfo->EncapContentInfo.pbData)
					{
						return -1;
					}
					memcpy(vssdiSignedDataInfo->EncapContentInfo.pbData, dtDataOctets->currentBaseDER->pbData, dtDataOctets->currentBaseDER->cbData);
					vssdiSignedDataInfo->EncapContentInfo.cbData = dtDataOctets->currentBaseDER->cbData;
				}
			}
		}

		//optional
		bool bCertPresent = false;
		bool bCRLPresent = false;
		
		//Determine whether the optional Certs and CRLs are present.
		DERTree *dtCertPresent = NULL;
		DERTree *dtCertPresentTemp = NULL;
		DERTree *dtCertPresentPrev = NULL;

		DERTree *dtCRLPresent = NULL;
		DERTree *dtCertSet = dtDataContSeq->nextDERTree;
		if(dtCertSet && (dtCertSet->currentBaseDER->Class == CONTEXT_SPECIFIC && dtCertSet->currentBaseDER->Encoding == CONSTRUCTED
			&& dtCertSet->currentBaseDER->TagNumber == 0))
		{
			//Certs present.
			bCertPresent = true;
			if(dtCertSet->nextDERTree && (dtCertSet->nextDERTree->currentBaseDER->Class == CONTEXT_SPECIFIC && dtCertSet->nextDERTree->currentBaseDER->Encoding == CONSTRUCTED
			     && dtCertSet->nextDERTree->currentBaseDER->TagNumber == 1)) // check for CRLs
			{
				//CRLs present
				bCRLPresent = true;
			}

		} 
		else if( dtCertSet && (dtCertSet->currentBaseDER->Class == CONTEXT_SPECIFIC && dtCertSet->currentBaseDER->Encoding == CONSTRUCTED
			&& dtCertSet->currentBaseDER->TagNumber == 1)) // check for CRLs
		{
			// CRLs present.
			bCRLPresent = true;
		}
		
		if(bCertPresent == true)
		{
			//copy certs - stripping of the SET headers and then copying. If SET is required copy dtCertPresent->currentBaseDER->BaseDERBlob->pbData
			//dtCertPresent = dtDataContSeq->nextDERTree; // need this pointer later for accessing the SingerInfo
			dtCertPresent = dtCertSet->rightDERTree;
		
			dtCertPresentTemp = dtCertPresent;
			CBaseDERCollection cbdcCertChain;
			while(dtCertPresentTemp != NULL)
			{
				CBaseDERCollection cbdcCertChainTemp(dtCertPresentTemp->currentBaseDER->BaseDERBlob->cbData,
								dtCertPresentTemp->currentBaseDER->BaseDERBlob->pbData);
				cbdcCertChain = cbdcCertChain + cbdcCertChainTemp;

				dtCertPresentPrev = dtCertPresentTemp;
				dtCertPresentTemp = dtCertPresentTemp->nextDERTree;
			}

			vssdiSignedDataInfo->CertificateSet.cbData = cbdcCertChain.BaseDERBlob->cbData;
			vssdiSignedDataInfo->CertificateSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			if(!vssdiSignedDataInfo->CertificateSet.pbData)
			{
				return -1;
			}
			memcpy(vssdiSignedDataInfo->CertificateSet.pbData, cbdcCertChain.BaseDERBlob->pbData,
							vssdiSignedDataInfo->CertificateSet.cbData); 

			//vssdiSignedDataInfo->CertificateSet.cbData = dtCertPresent->currentBaseDER->BaseDERBlob->cbData;
			//vssdiSignedDataInfo->CertificateSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			//memcpy(vssdiSignedDataInfo->CertificateSet.pbData, dtCertPresent->currentBaseDER->BaseDERBlob->pbData, vssdiSignedDataInfo->CertificateSet.cbData); 

			/* Code for getting end entity cert.
			dtCertPresentTemp = dtCertPresent;
			// if there are is a cert chain get the end entity cert
			// we assume the last cert in the chain to be the end entity cert
			while(dtCertPresentTemp != NULL)
			{
				dtCertPresentPrev = dtCertPresentTemp;
				dtCertPresentTemp = dtCertPresentTemp->nextDERTree;
			}
			vssdiSignedDataInfo->CertificateSet.cbData = dtCertPresentPrev->currentBaseDER->BaseDERBlob->cbData;
			vssdiSignedDataInfo->CertificateSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			memcpy(vssdiSignedDataInfo->CertificateSet.pbData, dtCertPresentPrev->currentBaseDER->BaseDERBlob->pbData, vssdiSignedDataInfo->CertificateSet.cbData); 
			*/

		}
		if(bCRLPresent == true)
		{
			//copy crls
			if(dtCertPresent)
				dtCRLPresent = dtCertPresent->nextDERTree;
			else
				dtCRLPresent = dtDataContSeq->nextDERTree;
			
			vssdiSignedDataInfo->CrlSet.cbData = dtCRLPresent->currentBaseDER->cbData;
			vssdiSignedDataInfo->CrlSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			if(!vssdiSignedDataInfo->CrlSet.pbData)
			{
				return -1;
			}
			memcpy(vssdiSignedDataInfo->CrlSet.pbData, dtCRLPresent->currentBaseDER->pbData, vssdiSignedDataInfo->CrlSet.cbData); 

		}

		DERTree *dtSignerInfo = NULL;
		if(bCertPresent == false && bCRLPresent == false)
		{
			dtSignerInfo = dtDataContSeq->nextDERTree;
		}
		else if(bCertPresent == true && bCRLPresent == true)
		{
			// BUG BUG check this later
			dtSignerInfo = dtCRLPresent->nextDERTree;
			
		}
		else
		{
			//dtSignerInfo = dtCertPresent->nextDERTree;
			dtSignerInfo = dtCertSet->nextDERTree;
		}

		if(!dtSignerInfo || dtSignerInfo->currentBaseDER->Type != SET)
		{
			return -1;
		}

		nRetVal = ParseSignerInfo(dtSignerInfo->currentBaseDER->pbData,
			dtSignerInfo->currentBaseDER->cbData, &vssdiSignedDataInfo->SignerInfo );
		//nRetVal = ParseSignerInfoNew(dtSignerInfo, &vssdiSignedDataInfo->SignerInfo);

		if(nRetVal != 0)
		{
			return -1;
		}

	}


	return 0;
}


int ParseSignerInfo(unsigned char* pbSignerDataDerBlob,
					 unsigned int cbSignerDataBlobLen,
					 VS_SIGNER_INFO_PARSE *vssipSignerInfo )
{
	// BUG BUG - while returning from the errors the memory allocated has to be freed.

	memset(vssipSignerInfo, 0, sizeof(VS_SIGNER_INFO_PARSE));
	
	CBaseDERCollection cbdcSignerInfo(cbSignerDataBlobLen, pbSignerDataDerBlob);

	CBaseDERHierarchy cbdhSignerData(cbdcSignerInfo);
	if(cbdhSignerData.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree *dtSingerInfoSeq = &cbdhSignerData.m_DERTree;
	if(!dtSingerInfoSeq || dtSingerInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtCMSVersion = dtSingerInfoSeq->rightDERTree;

	//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
	if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}
	
	CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

	//We limit this implementation to assume that the version information can fit in a DWORD
	if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
	{
		return -1;
	}

	//Obtain the version bytes
	unsigned char byteVersion[4];
	for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
		byteVersion[i] = pcuiCMSVersion->pbData[i];
	for(unsigned int j=i;j<4; ++j)
		byteVersion[j] = 0x00;
	
	//Store the version in the SignedDataInfo
	//1
	vssipSignerInfo->dwSIVersion = *((_DWORD*)byteVersion);

	DERTree *dtIssuerDNSerNumSeq = dtCMSVersion->nextDERTree;

	if(!dtIssuerDNSerNumSeq || dtIssuerDNSerNumSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtIssuerDN = dtIssuerDNSerNumSeq->rightDERTree;
	
	if(!dtIssuerDN || dtIssuerDN->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	//copy the Issuer DN DER blob
	vssipSignerInfo->Issuer.cbData = dtIssuerDN->currentBaseDER->BaseDERBlob->cbData;
	vssipSignerInfo->Issuer.pbData = (unsigned char*)malloc(vssipSignerInfo->Issuer.cbData);
	
	if(!vssipSignerInfo->Issuer.pbData)
	{
		return -1;
	}

	memcpy(vssipSignerInfo->Issuer.pbData, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData,
			vssipSignerInfo->Issuer.cbData);

	DERTree *dtSerNum = dtIssuerDN->nextDERTree;

	//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
	if(!dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}

	CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
	if(!pcuiSerNum)
	{
		return -1;
	}

	vssipSignerInfo->SerialNumber.cbData = pcuiSerNum->cbData;
	vssipSignerInfo->SerialNumber.pbData = (_PBYTE)malloc(sizeof(unsigned char) * pcuiSerNum->cbData);
	if(!vssipSignerInfo->SerialNumber.pbData)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SerialNumber.pbData, pcuiSerNum->pbData, vssipSignerInfo->SerialNumber.cbData);


	DERTree *dtDigestAlgIdSeq = dtIssuerDNSerNumSeq->nextDERTree;
	if(!dtDigestAlgIdSeq || dtDigestAlgIdSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}


	DERTree *dtDigestAlgId = dtDigestAlgIdSeq->rightDERTree;
	if(!dtDigestAlgId || dtDigestAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	// 2 DigestAlgID
	vssipSignerInfo->DigestAlgId.pszObjId = (char*)malloc(dtDigestAlgId->currentBaseDER->cbData + 1);
	if(!vssipSignerInfo->DigestAlgId.pszObjId)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->DigestAlgId.pszObjId, dtDigestAlgId->currentBaseDER->pbData, dtDigestAlgId->currentBaseDER->cbData);
	vssipSignerInfo->DigestAlgId.pszObjId[dtDigestAlgId->currentBaseDER->cbData] = '\0';
	//vssdiSignedDataInfo->DigestAlgId.cbData = dtDigestAlgId->currentBaseDER->cbData;


	DERTree *dtDigestAlgIdParam = dtDigestAlgId->nextDERTree;
	if(!dtDigestAlgIdParam)
	{
		return -1;
	}

	// 3 DigestAlgID param
	if(dtDigestAlgIdParam->currentBaseDER->pbData)
	{
		vssipSignerInfo->DigestAlgId.Parameters.pbData = (unsigned char*)malloc(dtDigestAlgIdParam->currentBaseDER->cbData);
		if(!vssipSignerInfo->DigestAlgId.Parameters.pbData)
		{
			return -1;
		}
		memcpy(vssipSignerInfo->DigestAlgId.Parameters.pbData, dtDigestAlgIdParam->currentBaseDER->pbData, dtDigestAlgIdParam->currentBaseDER->cbData);
		vssipSignerInfo->DigestAlgId.Parameters.cbData = dtDigestAlgIdParam->currentBaseDER->cbData;
	}


	DERTree *dtSignedAttribs = dtDigestAlgIdSeq->nextDERTree;
	DERTree *dtSignedAttribsPre = NULL;
	DERTree *dtSigAlgIDSeq = NULL;

	bool bAttribPresent = false;

	if(dtSignedAttribs && (dtSignedAttribs->currentBaseDER->Class == CONTEXT_SPECIFIC && dtSignedAttribs->currentBaseDER->Encoding == CONSTRUCTED
			&& dtSignedAttribs->currentBaseDER->TagNumber == 0))
	{
		bAttribPresent = true;
	}

	if(bAttribPresent == true)
	{
		//copy signed attributes.
		dtSignedAttribsPre = dtDigestAlgIdSeq->nextDERTree;
		vssipSignerInfo->SignedAttributes.pbData = (unsigned char*)malloc(dtSignedAttribsPre->currentBaseDER->cbData);
		if(!vssipSignerInfo->SignedAttributes.pbData)
		{
			return -1;
		}
		vssipSignerInfo->SignedAttributes.cbData = dtSignedAttribsPre->currentBaseDER->cbData;
		memcpy(vssipSignerInfo->SignedAttributes.pbData, dtSignedAttribsPre->currentBaseDER->pbData,
		vssipSignerInfo->SignedAttributes.cbData);

	}

	if(dtSignedAttribsPre)
	{
		//Attrib present AlgID is Attribs next
		dtSigAlgIDSeq = dtSignedAttribsPre->nextDERTree;
	}
	else
	{
		// Attrib not present AlgID is IssuerDNSerialNum next
		dtSigAlgIDSeq = dtDigestAlgIdSeq->nextDERTree;
	}

	if(!dtSigAlgIDSeq || dtSigAlgIDSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}


	DERTree *dtSigAlgID = dtSigAlgIDSeq->rightDERTree;
	if(!dtSigAlgID || dtSigAlgID->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	vssipSignerInfo->SignatureAlgId.pszObjId = (char*)malloc(dtSigAlgID->currentBaseDER->cbData + 1);
	if(!vssipSignerInfo->SignatureAlgId.pszObjId)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SignatureAlgId.pszObjId, dtSigAlgID->currentBaseDER->pbData, dtSigAlgID->currentBaseDER->cbData);
	vssipSignerInfo->SignatureAlgId.pszObjId[dtSigAlgID->currentBaseDER->cbData] = '\0';
	

		
	DERTree *dtSigAlgIdParam = dtSigAlgID->nextDERTree;

	// 3 SigAlgID param
	if(dtSigAlgIdParam->currentBaseDER->pbData)
	{
		vssipSignerInfo->SignatureAlgId.Parameters.pbData = (unsigned char*)malloc(dtSigAlgIdParam->currentBaseDER->cbData);
		if(!vssipSignerInfo->SignatureAlgId.Parameters.pbData)
		{
			return -1;
		}
		memcpy(vssipSignerInfo->SignatureAlgId.Parameters.pbData, dtSigAlgIdParam->currentBaseDER->pbData,
				dtSigAlgIdParam->currentBaseDER->cbData);
		vssipSignerInfo->SignatureAlgId.Parameters.cbData = dtSigAlgIdParam->currentBaseDER->cbData;
	}

	// Signature Blob
	DERTree *dtSignatureValue = dtSigAlgIDSeq->nextDERTree;
		
	if(!dtSignatureValue || dtSignatureValue->currentBaseDER->Type != OCTET_STRING)
	{
		return -1;
	}
	vssipSignerInfo->SignatureValue.cbData = dtSignatureValue->currentBaseDER->cbData;
	vssipSignerInfo->SignatureValue.pbData = (unsigned char*)malloc(vssipSignerInfo->SignatureValue.cbData);
	if(!vssipSignerInfo->SignatureValue.pbData)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SignatureValue.pbData, dtSignatureValue->currentBaseDER->pbData, vssipSignerInfo->SignatureValue.cbData);
	
	return 0;
}

int ParseEnvelopedData(unsigned char *pbEnvelopedData, 
						unsigned int cbEnvelopedData,
						VS_ENVELOPEDDATA_INFO *vseiEnvelopedDataInfo
						)
{

	// BUG BUG - while returning from the errors the memory allocated has to be freed.
	// this is bit tricky while looping thro the RecipientInfos.

	memset(vseiEnvelopedDataInfo, 0, sizeof(VS_ENVELOPEDDATA_INFO));

	CBaseDERCollection bdcEnvelopedData(cbEnvelopedData, pbEnvelopedData);
	CBaseDERHierarchy	cbdhEnvelopedData(bdcEnvelopedData);

	if(cbdhEnvelopedData.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree* dtEnvelopedContentInfo = &cbdhEnvelopedData.m_DERTree;

	if(!dtEnvelopedContentInfo && dtEnvelopedContentInfo->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtEnvelopedDataObjID = dtEnvelopedContentInfo->rightDERTree;
	DERTree *dtEnvelopedDataTag = dtEnvelopedDataObjID->nextDERTree;

	if(!dtEnvelopedDataObjID || !dtEnvelopedDataTag)
	{
		return -1;
	}

	//If OBJECT IDENTIFIER is not EnvelopedData (1.2.840.113549.1.7.3)
	if(memcmp(dtEnvelopedDataObjID->currentBaseDER->pbData, vssc_szOID_RSA_envelopedData, dtEnvelopedDataObjID->currentBaseDER->cbData) != 0)
	{
		return -1;
	}
	
	// Parse the EnvelopedData
	if(!dtEnvelopedDataTag || (dtEnvelopedDataTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtEnvelopedDataTag->currentBaseDER->Encoding != CONSTRUCTED
		|| dtEnvelopedDataTag->currentBaseDER->TagNumber != 0))
	{
		return -1;
	}

	/*
		EnvelopedData ::= SEQUENCE {
			 version Version,
			 recipientInfos RecipientInfos,
			 encryptedContentInfo EncryptedContentInfo }
	*/


	DERTree *dtEnvelopedSeq = dtEnvelopedDataTag->rightDERTree;
		
	//Check if EnvelopedData is sequence
	if(!dtEnvelopedSeq && dtEnvelopedSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtCMSVersion = dtEnvelopedSeq->rightDERTree;

	//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
	if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}
	
	CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

	//We limit this implementation to assume that the version information can fit in a DWORD
	if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
	{
		return -1;
	}

	//Obtain the version bytes
	unsigned char byteVersion[4];
	for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
		byteVersion[i] = pcuiCMSVersion->pbData[i];
	for(unsigned int j=i;j<4; ++j)
		byteVersion[j] = 0x00;
	
	//Store the version in the EnvelopedDataInfo
	//1
	vseiEnvelopedDataInfo->dwVersion = *((_DWORD*)byteVersion);

	DERTree *dtRecipientInfoSet = dtCMSVersion->nextDERTree;

	if(!dtRecipientInfoSet || dtRecipientInfoSet->currentBaseDER->Type != SET)
	{
		return -1;
	}

	//Find out the number of RecipientInfo 

	DERTree *dtRecipientInfoSeq = dtRecipientInfoSet->rightDERTree;

	if(!dtRecipientInfoSeq || dtRecipientInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	int nCount = 0;
	while(dtRecipientInfoSeq)
	{
		nCount++;
		dtRecipientInfoSeq = dtRecipientInfoSeq->nextDERTree;
	}

	vseiEnvelopedDataInfo->pRecipientInfo = (PVS_RECIPIENT_INFO)malloc(sizeof(VS_RECIPIENT_INFO) * nCount++);
	if(!vseiEnvelopedDataInfo->pRecipientInfo)
	{
		return -1;
	}

	dtRecipientInfoSeq = dtRecipientInfoSet->rightDERTree;
	nCount = 0;
	while(dtRecipientInfoSeq)
	{
		if(!dtRecipientInfoSeq || dtRecipientInfoSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		
		DERTree *dtCMSVersion = dtRecipientInfoSeq->rightDERTree;

		//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
		if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			return -1;
		}
		
		CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

		//We limit this implementation to assume that the version information can fit in a DWORD
		if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
		{
			return -1;
		}

		//Obtain the version bytes
		unsigned char byteVersion[4];
		for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
			byteVersion[i] = pcuiCMSVersion->pbData[i];
		for(unsigned int j=i;j<4; ++j)
			byteVersion[j] = 0x00;
		
		//Store the version in the EnvelopedDataInfo
		//1
		unsigned int dwVersion = *((_DWORD*)byteVersion);
		if(dwVersion != 0)
		{
			return -1;
		}
		
		DERTree *dtIssuerDNSerNumSeq = dtCMSVersion->nextDERTree;

		if(!dtIssuerDNSerNumSeq || dtIssuerDNSerNumSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtIssuerDN = dtIssuerDNSerNumSeq->rightDERTree;
		
		if(!dtIssuerDN || dtIssuerDN->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		//copy the Issuer DN DER blob
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.cbData = dtIssuerDN->currentBaseDER->BaseDERBlob->cbData;
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.pbData = (unsigned char*)malloc(vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.cbData);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.pbData)
		{
			return -1;
		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.pbData, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData,
				vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.cbData);

		DERTree *dtSerNum = dtIssuerDN->nextDERTree;

		//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
		if(!dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			return -1;
		}

		CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
		if(!pcuiSerNum)
		{
			return -1;
		}

		vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.cbData = pcuiSerNum->cbData;
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.pbData = (_PBYTE)malloc(sizeof(unsigned char) * pcuiSerNum->cbData);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.pbData)
		{
			return -1;
		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.pbData, pcuiSerNum->pbData, vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.cbData);

		DERTree *dtKeyEncAlgIdSeq = dtIssuerDNSerNumSeq->nextDERTree;

		if(!dtKeyEncAlgIdSeq || dtKeyEncAlgIdSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtKeyEncAlgId = dtKeyEncAlgIdSeq->rightDERTree;
		if(!dtKeyEncAlgId || dtKeyEncAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			return -1;
		}

		// 2 
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId = (char*)malloc(dtKeyEncAlgId->currentBaseDER->cbData + 1);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId)
		{
			return -1;

		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId, dtKeyEncAlgId->currentBaseDER->pbData, dtKeyEncAlgId->currentBaseDER->cbData);
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId[dtKeyEncAlgId->currentBaseDER->cbData] = '\0';
		


		DERTree *dtKeyEncAlgIdParam = dtKeyEncAlgId->nextDERTree;

		if(!dtKeyEncAlgIdParam)
		{
			return -1;
		}

		if(dtKeyEncAlgIdParam->currentBaseDER->pbData)
		{
			vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(dtKeyEncAlgIdParam->currentBaseDER->cbData);
			if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.pbData, dtKeyEncAlgIdParam->currentBaseDER->pbData, dtKeyEncAlgIdParam->currentBaseDER->cbData);
			vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.cbData = dtKeyEncAlgIdParam->currentBaseDER->cbData;
		}

		DERTree *dtEncryptedKey = dtKeyEncAlgIdSeq->nextDERTree;

		if(!dtEncryptedKey || dtEncryptedKey->currentBaseDER->Type != OCTET_STRING)
		{
			return -1;
		}
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.pbData = (unsigned char*)malloc(dtEncryptedKey->currentBaseDER->cbData);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.pbData)
		{
			return -1;
		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.pbData, 
			dtEncryptedKey->currentBaseDER->pbData, dtEncryptedKey->currentBaseDER->cbData);
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.cbData = dtEncryptedKey->currentBaseDER->cbData;
		nCount ++;
		dtRecipientInfoSeq = dtRecipientInfoSeq->nextDERTree;

	}
	vseiEnvelopedDataInfo->nRecipientInfos = nCount++;


	DERTree *dtEncryptedContentInfoSeq = dtRecipientInfoSet->nextDERTree;

	if(!dtEncryptedContentInfoSeq || dtEncryptedContentInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtDataObjId = dtEncryptedContentInfoSeq->rightDERTree;

	if(!dtDataObjId)
	{
		return -1;
	}

	//If OBJECT IDENTIFIER is not Data (1.2.840.113549.1.7.1)
	if(memcmp(dtDataObjId->currentBaseDER->pbData, vssc_szOID_RSA_data, dtDataObjId->currentBaseDER->cbData) != 0)
	{
		return -1;
	}

	DERTree *dtEncryptionAlgIDSeq = dtDataObjId->nextDERTree;

	if(!dtEncryptionAlgIDSeq || dtEncryptionAlgIDSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtEncAlgId = dtEncryptionAlgIDSeq->rightDERTree;
	if(!dtEncAlgId || dtEncAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	
	vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId = (char*)malloc(dtEncAlgId->currentBaseDER->cbData + 1);
	if(!vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId)
	{
		return -1;
	}
	memcpy(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId, dtEncAlgId->currentBaseDER->pbData, dtEncAlgId->currentBaseDER->cbData);
	vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId[dtEncAlgId->currentBaseDER->cbData] = '\0';

	// RC2
	if(strcmp(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId, vssc_szOID_RSA_RC2CBC) == 0)
	{
		DERTree *dtEncAlgIdSeq = dtEncAlgId->nextDERTree;

		// Right now not using the integer value
		DERTree *dtEncAlgIdInt = dtEncAlgIdSeq->rightDERTree;

		DERTree *dtEncAlgIdParam = dtEncAlgIdInt->nextDERTree;
		if(dtEncAlgIdParam->currentBaseDER->pbData)
		{
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(dtEncAlgIdParam->currentBaseDER->cbData);
			if(!vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,
				dtEncAlgIdParam->currentBaseDER->pbData, dtEncAlgIdParam->currentBaseDER->cbData);
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.cbData = dtEncAlgIdParam->currentBaseDER->cbData;
		}

		
	}

	else
	{
		DERTree *dtEncAlgIdParam = dtEncAlgId->nextDERTree;
	
		if(!dtEncAlgIdParam)
		{
			return -1;
		}

		if(dtEncAlgIdParam->currentBaseDER->pbData)
		{
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(dtEncAlgIdParam->currentBaseDER->cbData);
			if(!vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,
				dtEncAlgIdParam->currentBaseDER->pbData, dtEncAlgIdParam->currentBaseDER->cbData);
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.cbData = dtEncAlgIdParam->currentBaseDER->cbData;
		}
	}


	DERTree *dtEncryptedContentTag = dtEncryptionAlgIDSeq->nextDERTree;

	//if(!dtEncryptedContentTag || (dtEncryptedContentTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtEncryptedContentTag->currentBaseDER->Encoding != CONSTRUCTED
	//		|| dtEncryptedContentTag->currentBaseDER->TagNumber != 0))
	
	if(!dtEncryptedContentTag || (dtEncryptedContentTag->currentBaseDER->Class != CONTEXT_SPECIFIC 
			|| dtEncryptedContentTag->currentBaseDER->TagNumber != 0))

	{
		return -1;
	}

	DERTree *dtEncryptedContent = NULL;
	DERTree *dtEncryptedContentNext = NULL;

	// Support for both explicit and implicit tag.
	// Not constructed
	if(dtEncryptedContentTag->currentBaseDER->Encoding != CONSTRUCTED)
	{

		dtEncryptedContent = dtEncryptedContentTag;
		dtEncryptedContentNext = dtEncryptedContent->nextDERTree;


	}
	else
	{
		dtEncryptedContent = dtEncryptedContentTag->rightDERTree;
		dtEncryptedContentNext = dtEncryptedContent->nextDERTree;
		
	}
	
	// Check if the data is broken into chunks
	//DERTree *dtEncryptedContent = dtEncryptedContentTag->rightDERTree;
	//DERTree *dtEncryptedContentNext = dtEncryptedContent->nextDERTree;

	DERTree *dtEncryptedContentTemp = dtEncryptedContent;
	unsigned long dwContentLen = 0;
	unsigned char *pbContentLen = NULL;

	// Check if the data is broken into chunks
	if(dtEncryptedContentNext == NULL)
	{
		
		//if(!dtEncryptedContent || dtEncryptedContent->currentBaseDER->Type != OCTET_STRING)
		if(!dtEncryptedContent)
		{
			return -1;
		}
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData = (unsigned char *)malloc(dtEncryptedContent->currentBaseDER->cbData);
		if(!vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData)
		{
			return -1;
		}
		//New Simder change
		//reverse(dtEncryptedContent->currentBaseDER->cbData, dtEncryptedContent->currentBaseDER->pbData);
		memcpy(vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData, dtEncryptedContent->currentBaseDER->pbData, dtEncryptedContent->currentBaseDER->cbData);
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.cbData = dtEncryptedContent->currentBaseDER->cbData;
	}
	else // chunks concatenate.
	{
		// Find the lenght first
		while(dtEncryptedContentTemp)
		{
			dwContentLen += dtEncryptedContentTemp->currentBaseDER->cbData;
			dtEncryptedContentTemp = dtEncryptedContentTemp->nextDERTree;

		}
		dtEncryptedContentTemp = dtEncryptedContent;
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData = (unsigned char*)malloc(dwContentLen);
		if(!vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData)
		{
			return -1;
		}
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.cbData = dwContentLen;
		pbContentLen = vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData;
		
		while(dtEncryptedContentTemp)
		{
			//New Simder change
			//reverse(dtEncryptedContentTemp->currentBaseDER->cbData,
			//		dtEncryptedContentTemp->currentBaseDER->pbData);
					
			memcpy(pbContentLen,
					dtEncryptedContentTemp->currentBaseDER->pbData,
					dtEncryptedContentTemp->currentBaseDER->cbData);
			pbContentLen += dtEncryptedContentTemp->currentBaseDER->cbData;
			dtEncryptedContentTemp = dtEncryptedContentTemp->nextDERTree;
		}
	}


	return 0;

}

int GetMsgDigestFromAA(unsigned char* pbAuthAttrib, 
						unsigned int cbAuthAttrib,
						unsigned char** ppbMsgDigest,
						unsigned int *cbMsgDigest)
{

/* Example of Signed/Authenticate Attributes
 [0] {
1436 30   24:             SEQUENCE {
1438 06    9:               OBJECT IDENTIFIER
            :                 contentType (1 2 840 113549 1 9 3)
1449 31   11:               SET {
1451 06    9:                 OBJECT IDENTIFIER data (1 2 840 113549 1 7 1)
            :                 }
            :               }
1462 30   28:             SEQUENCE {
1464 06    9:               OBJECT IDENTIFIER
            :                 signingTime (1 2 840 113549 1 9 5)
1475 31   15:               SET {
1477 17   13:                 UTCTime '001231021656Z'
            :                 }
            :               }
1492 30   35:             SEQUENCE {
1494 06    9:               OBJECT IDENTIFIER
            :                 messageDigest (1 2 840 113549 1 9 4)
1505 31   22:               SET {
1507 04   20:                 OCTET STRING
            :                   67 41 27 B3 13 17 32 DB F4 25 1B 8D 1D 5A 84 00
            :                   C7 9C 1F A7
            :                 }
            :               }
1529 30   52:             SEQUENCE {
1531 06    9:               OBJECT IDENTIFIER
            :                 sMIMECapabilities (1 2 840 113549 1 9 15)
1542 31   39:               SET {
1544 30   37:                 SEQUENCE {
1546 30   14:                   SEQUENCE {
1548 06    8:                     OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
1558 02    2:                     INTEGER 128
            :                     }
1562 30    7:                   SEQUENCE {
1564 06    5:                     OBJECT IDENTIFIER sha1 (1 3 14 3 2 26)
            :                     }
1571 30   10:                   SEQUENCE {
1573 06    8:                     OBJECT IDENTIFIER md5 (1 2 840 113549 2 5)
            :                     }
            :                   }
            :                 }
            :               }
*/



	CBaseDERCollection bdcAuthAttrib(cbAuthAttrib, pbAuthAttrib);
	CBaseDERHierarchy	cbdhAuthAttrib(bdcAuthAttrib);

	if(cbdhAuthAttrib.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree *dtAuthAttribSeq = &cbdhAuthAttrib.m_DERTree;

	if(!dtAuthAttribSeq && dtAuthAttribSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtMessageDigestSeq = dtAuthAttribSeq->nextDERTree->nextDERTree;
	DERTree *dtMessageDigestObjID = dtMessageDigestSeq->rightDERTree;

	char *szMsgDigestObjId = "1.2.840.113549.1.9.4" ;
	if(memcmp(dtMessageDigestObjID->currentBaseDER->pbData,
				szMsgDigestObjId,
				dtMessageDigestObjID->currentBaseDER->cbData) != 0)
	{
		return -1;
	}

	DERTree *dtMsgDigestSet = dtMessageDigestObjID->nextDERTree;

	if(!dtMsgDigestSet || dtMsgDigestSet->currentBaseDER->Type != SET)
	{
		return -1;
	}

	DERTree *dtMessageDigestData = dtMsgDigestSet->rightDERTree;

	if(!dtMessageDigestData || dtMessageDigestData->currentBaseDER->Type != OCTET_STRING)
	{
		return -1;
	}

	*ppbMsgDigest = (unsigned char*)malloc(dtMessageDigestData->currentBaseDER->cbData);

	if(*ppbMsgDigest == NULL)
		return -1;
	memcpy(*ppbMsgDigest, dtMessageDigestData->currentBaseDER->pbData,
				dtMessageDigestData->currentBaseDER->cbData);
	*cbMsgDigest = dtMessageDigestData->currentBaseDER->cbData;

	return 0;
	

}

#endif // 0

int GetMsgDigestSIDFromAA(unsigned char* pbAuthAttrib, 
						unsigned int cbAuthAttrib,
						AUTHATTRIB *pAuthAtrib)
{
	

/* Example of Signed/Authenticate Attributes
 [0] {
1436 30   24:             SEQUENCE {
1438 06    9:               OBJECT IDENTIFIER
            :                 contentType (1 2 840 113549 1 9 3)
1449 31   11:               SET {
1451 06    9:                 OBJECT IDENTIFIER data (1 2 840 113549 1 7 1)
            :                 }
            :               }
1462 30   28:             SEQUENCE {
1464 06    9:               OBJECT IDENTIFIER
            :                 signingTime (1 2 840 113549 1 9 5)
1475 31   15:               SET {
1477 17   13:                 UTCTime '001231021656Z'
            :                 }
            :               }
1492 30   35:             SEQUENCE {
1494 06    9:               OBJECT IDENTIFIER
            :                 messageDigest (1 2 840 113549 1 9 4)
1505 31   22:               SET {
1507 04   20:                 OCTET STRING
            :                   67 41 27 B3 13 17 32 DB F4 25 1B 8D 1D 5A 84 00
            :                   C7 9C 1F A7
            :                 }
            :               }
1529 30   52:             SEQUENCE {
1531 06    9:               OBJECT IDENTIFIER
            :                 sMIMECapabilities (1 2 840 113549 1 9 15)
1542 31   39:               SET {
1544 30   37:                 SEQUENCE {
1546 30   14:                   SEQUENCE {
1548 06    8:                     OBJECT IDENTIFIER rc2CBC (1 2 840 113549 3 2)
1558 02    2:                     INTEGER 128
            :                     }
1562 30    7:                   SEQUENCE {
1564 06    5:                     OBJECT IDENTIFIER sha1 (1 3 14 3 2 26)
            :                     }
1571 30   10:                   SEQUENCE {
1573 06    8:                     OBJECT IDENTIFIER md5 (1 2 840 113549 2 5)
            :                     }
            :                   }
            :                 }
            :               }
*/



	memset(pAuthAtrib, 0, sizeof(AUTHATTRIB));

	CBaseDERCollection bdcAuthAttrib(cbAuthAttrib, pbAuthAttrib);
	CBaseDERHierarchy	cbdhAuthAttrib(bdcAuthAttrib);

	if(cbdhAuthAttrib.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree *dtAuthAttribSeq = &cbdhAuthAttrib.m_DERTree;

	if(!dtAuthAttribSeq && dtAuthAttribSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtMessageDigestSeq = dtAuthAttribSeq->nextDERTree->nextDERTree;
	DERTree *dtMessageDigestObjID = dtMessageDigestSeq->rightDERTree;

	char *szMsgDigestObjId = "1.2.840.113549.1.9.4" ;
	if(memcmp(dtMessageDigestObjID->currentBaseDER->pbData,
				szMsgDigestObjId,
				dtMessageDigestObjID->currentBaseDER->cbData) != 0)
	{
		return -1;
	}

	DERTree *dtMsgDigestSet = dtMessageDigestObjID->nextDERTree;

	if(!dtMsgDigestSet || dtMsgDigestSet->currentBaseDER->Type != SET)
	{
		return -1;
	}

	DERTree *dtMessageDigestData = dtMsgDigestSet->rightDERTree;

	if(!dtMessageDigestData || dtMessageDigestData->currentBaseDER->Type != OCTET_STRING)
	{
		return -1;
	}


	
	pAuthAtrib->pbMimeEntityDigest = (unsigned char*)malloc(dtMessageDigestData->currentBaseDER->cbData);

	if(pAuthAtrib->pbMimeEntityDigest == NULL)
		return -1;
	memcpy(pAuthAtrib->pbMimeEntityDigest, dtMessageDigestData->currentBaseDER->pbData,
				dtMessageDigestData->currentBaseDER->cbData);
	pAuthAtrib->cbMimeEntityDigest = dtMessageDigestData->currentBaseDER->cbData;

	
	DERTree *dtSMIMECab = dtMessageDigestSeq->nextDERTree;
	DERTree *dtSIDSeq = dtSMIMECab->nextDERTree;

	DERTree *dtSIDObjID = dtSIDSeq->rightDERTree;

	char *szSIDObjID = "1.3.6.1.4.1.311.16.4" ;
	if(memcmp(dtSIDObjID->currentBaseDER->pbData,
				szSIDObjID,
				dtSIDObjID->currentBaseDER->cbData) != 0)
	{
		return -1;
	}

	DERTree *dtSIDSet = dtSIDObjID->nextDERTree;
	DERTree *dtSIDInSeq = dtSIDSet->rightDERTree;
	DERTree *dtIssuerDN = dtSIDInSeq->rightDERTree;

	if(!dtIssuerDN || dtIssuerDN->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	//copy the Issuer DN DER blob
	pAuthAtrib->cbCertIssuerDN= dtIssuerDN->currentBaseDER->BaseDERBlob->cbData;
	pAuthAtrib->pbCertIssuerDN = (unsigned char*)malloc(dtIssuerDN->currentBaseDER->BaseDERBlob->cbData);
	if(!pAuthAtrib->pbCertIssuerDN)
	{
		return -1;
	}
	memcpy(	pAuthAtrib->pbCertIssuerDN, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData,
			pAuthAtrib->cbCertIssuerDN);


	DERTree *dtSerNum = dtIssuerDN->nextDERTree;
	//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
	if(!dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}

	CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
	if(!pcuiSerNum)
	{
		return -1;
	}

	pAuthAtrib->cbCertSerialNum = pcuiSerNum->cbData;
	pAuthAtrib->pbCertSerialNum = (_PBYTE)malloc(sizeof(unsigned char) * pcuiSerNum->cbData);
	if(!pAuthAtrib->pbCertSerialNum)
	{
		return -1;
	}
	memcpy(pAuthAtrib->pbCertSerialNum, pcuiSerNum->pbData, pcuiSerNum->cbData);

	return 0;

}




int GetPKCS7Type(
				 unsigned char *pbPKCS7Data,
				 unsigned int cbPKCS7Data,
				 VS_PKCS7_TYPE *ePKCS7Type
				 )
{
	CBaseDERCollection bdcPKCS7Data(cbPKCS7Data, pbPKCS7Data);
	CBaseDERHierarchy	cbdhPKCS7Data(bdcPKCS7Data);

	if(cbdhPKCS7Data.dwErrorCode == 0xFFFFFFFF)
	{
		return -1;
	}

	DERTree* dtPKCS7ContentInfo = &cbdhPKCS7Data.m_DERTree;

	if(!dtPKCS7ContentInfo && dtPKCS7ContentInfo->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtPKCS7DataObjID = dtPKCS7ContentInfo->rightDERTree;
	
	//If OBJECT IDENTIFIER is not EnvelopedData (1.2.840.113549.1.7.3)
	if(memcmp(dtPKCS7DataObjID->currentBaseDER->pbData,
		vssc_szOID_RSA_envelopedData, dtPKCS7DataObjID->currentBaseDER->cbData) == 0)
	{
		*ePKCS7Type = PKCS7_ENVELOPED;
	}
	else if(memcmp(dtPKCS7DataObjID->currentBaseDER->pbData,
		vssc_szOID_RSA_signedData, dtPKCS7DataObjID->currentBaseDER->cbData) == 0)
	{
		*ePKCS7Type = PKCS7_SIGNED;
	}
	else
	{
		return -1;
	}

	return 0;
}

// Given a chain or a end entity cert the input, returns the required 
// certificate in the chain which is controlled by nDepth input parameter,
// To get an end entity cert nDepth should be equal to 0
// If the length of the chain is 1, and nDept = 0, it returns the same cert.

// It is important to locate the end entity cert as the nDepth is relative to 
// the EndEntity cert.
// What determines an endentity cert - 1.Basic Constraints should be 0
//									   2.Should not be self signed
//									   3.in a loop,  if current.Subject != next.Issuer

int CertChainParser(	unsigned char* pbCertData,
						unsigned long cbCertData,
						unsigned char** ppbCertOut,
						unsigned long* pcbCertOut,
						int	nDepth
					)
{

	// BUG BUG - while returning from the errors the memory allocated has to be freed.

	bool bFirst = false;
	bool bLast = false;
	int i = 0;

	if(nDepth < 0)
		return -1;

	if(pbCertData == NULL || cbCertData == 0)
	{
		return -1;
	}

	CBaseDERCollection cbdcCertChain(cbCertData, pbCertData);
	CBaseDERHierarchy cbdhCertChain(cbdcCertChain);
	
	if(cbdhCertChain.dwErrorCode ==  0xFFFFFFFF)
	{
		return -1;
	}

	DERTree *dtEndEntityCert = &cbdhCertChain.m_DERTree;
	if(!dtEndEntityCert)
	{
		return -1;
	}
	DERTree *dtEndEntityCertPrev = NULL;

	int nCount = GetCertChainLen(pbCertData, cbCertData);
	if(nCount == -1)
	{
		return -1;
	}

	// End Entity Cert
	if( nDepth == 0)
	{
		if(nCount == 1)
		{
			// If its 1 handle it differently
			// copy it as is
			*ppbCertOut = (unsigned char*)malloc(dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData);
			if(!(*ppbCertOut))
			{
				return -1;
			}
			*pcbCertOut = dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData;
			memcpy(*ppbCertOut, dtEndEntityCert->currentBaseDER->BaseDERBlob->pbData, *pcbCertOut);
			return 0;
		}
		else
		{
			bool bLast;
			bLast = IsEndEntityCertLast(pbCertData, cbCertData);

			if(bLast)
			{
				while(dtEndEntityCert)
				{
					dtEndEntityCertPrev = dtEndEntityCert;
					dtEndEntityCert = dtEndEntityCert->nextDERTree;
				}
				// now dtEndEntityCertPrev points to the end entity cert
				// Allocate memory and copy it.
				*ppbCertOut = (unsigned char*)malloc(dtEndEntityCertPrev->currentBaseDER->BaseDERBlob->cbData);
				if(!(*ppbCertOut))
				{
					return -1;
				}
				*pcbCertOut = dtEndEntityCertPrev->currentBaseDER->BaseDERBlob->cbData;
				memcpy(*ppbCertOut, dtEndEntityCertPrev->currentBaseDER->BaseDERBlob->pbData, *pcbCertOut);
				return 0;

			}
			else
			{
				*ppbCertOut = (unsigned char*)malloc(dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData);
				if(!(*ppbCertOut))
				{
					return -1;
				}
				*pcbCertOut = dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData;
				memcpy(*ppbCertOut, dtEndEntityCert->currentBaseDER->BaseDERBlob->pbData, *pcbCertOut);
				return 0;
			}
		}

			
	}
	else  // Non End Entity Cert
	{
		// If its not End Entity Cert requested and # of count in the cert is 1 
		// then report Error.
		if(nCount == 1 && nDepth != 0)
			return -1;

		// if the nDepth requested is greater than the certs available
		// report Error
		if(nDepth + 1 > nCount)
			return -1;

		bool bLast;
		bLast = IsEndEntityCertLast(pbCertData, cbCertData);

		if(bLast)
		{
			int nReqCert = nCount - nDepth;
			int i = 1;
			while(dtEndEntityCert)
			{
				
				if ( i == nReqCert)
				{
					*ppbCertOut = (unsigned char*)malloc(dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData);
					if(!(*ppbCertOut))
					{
						return -1;
					}
					*pcbCertOut = dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData;
					memcpy(*ppbCertOut, dtEndEntityCert->currentBaseDER->BaseDERBlob->pbData, *pcbCertOut);
					return 0;

				}
				dtEndEntityCert = dtEndEntityCert->nextDERTree;
				i++;

			}
		}
		else
		{
			int i = 0;
			while(dtEndEntityCert)
			{
				if ( i == nDepth)
				{
					*ppbCertOut = (unsigned char*)malloc(dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData);
					if(!(*ppbCertOut))
					{
						return -1;
					}
					*pcbCertOut = dtEndEntityCert->currentBaseDER->BaseDERBlob->cbData;
					memcpy(*ppbCertOut, dtEndEntityCert->currentBaseDER->BaseDERBlob->pbData, *pcbCertOut);
					return 0;

				}
				dtEndEntityCert = dtEndEntityCert->nextDERTree;
				i ++;

			}
		}



	}
	
	return 0;

}

// Returns true is the last cert in the chain is the End Entity Cert
// Returns false if the first cert in the chain is the End Entity Cert.
bool IsEndEntityCertLast(
						 unsigned char *pbCertChain, 
						 unsigned long cbCertChain
						 )
{

	bool bFirst = false;
	bool bLast = false;
	int i = 0;


	PCERT_INFO	pCurrentCertInfo,pNextCertInfo;

	CBaseDERCollection cbdcCertChain(cbCertChain, pbCertChain);
	CBaseDERHierarchy cbdhCertChain(cbdcCertChain);

	DERTree *dtCertCurrent = &cbdhCertChain.m_DERTree;
	
	DERTree *dtCertNext = NULL;

	while(dtCertCurrent)
	{
		dtCertNext = dtCertCurrent->nextDERTree;
		
		if(dtCertNext == NULL)
		{
			bFirst = false;
			bLast = true;
			break;
		}
		
		
		CCertInfo   CurrentCertInfo(dtCertCurrent->currentBaseDER->BaseDERBlob->pbData,
							dtCertCurrent->currentBaseDER->BaseDERBlob->cbData);

		pCurrentCertInfo = CurrentCertInfo.GetCertInfo();

		CCertInfo   NextCertInfo(dtCertNext->currentBaseDER->BaseDERBlob->pbData,
				dtCertNext->currentBaseDER->BaseDERBlob->cbData);

		pNextCertInfo = NextCertInfo.GetCertInfo();

		if(memcmp(pCurrentCertInfo->Subject.pbData, pNextCertInfo->Issuer.pbData, pNextCertInfo->Issuer.cbData) != 0)
		{
			if(i == 0)
			{
				bFirst = true;
				bLast = false;
			}

		}


		
		dtCertCurrent = dtCertCurrent->nextDERTree;

	}
	if(bLast == true)
		return true;
	else
		return false;

}

// Returns no. of certs in the Cert Chain. 
// Returns 1 if the chain contains only one cert.
// Returns -1 if there is an error.
int GetCertChainLen(	unsigned char* pbCertData,
						unsigned long cbCertData
					)
{
	int nCount = 0;
	CBaseDERCollection cbdcCertChain(cbCertData, pbCertData);
	CBaseDERHierarchy cbdhCertChain(cbdcCertChain);

	if(cbdhCertChain.dwErrorCode ==  0xFFFFFFFF)
	{
		return -1;
	}

	DERTree *dtCertChain = &cbdhCertChain.m_DERTree;

	// Check for sequence
	if(!dtCertChain || dtCertChain->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	while(dtCertChain)
	{
		nCount++;
		dtCertChain = dtCertChain->nextDERTree;
		
		//need of chain.
		if(dtCertChain == NULL)
		{
			break;
		}

		// Check for sequence 
		if(dtCertChain->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

	}

	return nCount;
}



int ParseEnvelopedData(DERTree *dtPKCS7, VS_ENVELOPEDDATA_INFO *vseiEnvelopedDataInfo)
{
	
	memset(vseiEnvelopedDataInfo, 0, sizeof(VS_ENVELOPEDDATA_INFO));
	
	DERTree* dtEnvelopedContentInfo = dtPKCS7;

	if(!dtEnvelopedContentInfo && dtEnvelopedContentInfo->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtEnvelopedDataObjID = dtEnvelopedContentInfo->rightDERTree;
	DERTree *dtEnvelopedDataTag = dtEnvelopedDataObjID->nextDERTree;

	if(!dtEnvelopedDataObjID || !dtEnvelopedDataTag)
	{
		return -1;
	}

	//If OBJECT IDENTIFIER is not EnvelopedData (1.2.840.113549.1.7.3)
	if(memcmp(dtEnvelopedDataObjID->currentBaseDER->pbData, vssc_szOID_RSA_envelopedData, dtEnvelopedDataObjID->currentBaseDER->cbData) != 0)
	{
		return -1;
	}
	
	// Parse the EnvelopedData
	if(!dtEnvelopedDataTag || (dtEnvelopedDataTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtEnvelopedDataTag->currentBaseDER->Encoding != CONSTRUCTED
		|| dtEnvelopedDataTag->currentBaseDER->TagNumber != 0))
	{
		return -1;
	}

	/*
		EnvelopedData ::= SEQUENCE {
			 version Version,
			 recipientInfos RecipientInfos,
			 encryptedContentInfo EncryptedContentInfo }
	*/


	DERTree *dtEnvelopedSeq = dtEnvelopedDataTag->rightDERTree;
		
	//Check if EnvelopedData is sequence
	if(!dtEnvelopedSeq && dtEnvelopedSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtCMSVersion = dtEnvelopedSeq->rightDERTree;

	//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
	if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}
	
	CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

	//We limit this implementation to assume that the version information can fit in a DWORD
	if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
	{
		return -1;
	}

	//Obtain the version bytes
	unsigned char byteVersion[4];
	for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
		byteVersion[i] = pcuiCMSVersion->pbData[i];
	for(unsigned int j=i;j<4; ++j)
		byteVersion[j] = 0x00;
	
	//Store the version in the EnvelopedDataInfo
	//1
	vseiEnvelopedDataInfo->dwVersion = *((_DWORD*)byteVersion);

	DERTree *dtRecipientInfoSet = dtCMSVersion->nextDERTree;

	if(!dtRecipientInfoSet || dtRecipientInfoSet->currentBaseDER->Type != SET)
	{
		return -1;
	}

	//Find out the number of RecipientInfo 

	DERTree *dtRecipientInfoSeq = dtRecipientInfoSet->rightDERTree;

	if(!dtRecipientInfoSeq || dtRecipientInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	int nCount = 0;
	while(dtRecipientInfoSeq)
	{
		nCount++;
		dtRecipientInfoSeq = dtRecipientInfoSeq->nextDERTree;
	}

	vseiEnvelopedDataInfo->pRecipientInfo = (PVS_RECIPIENT_INFO)malloc(sizeof(VS_RECIPIENT_INFO) * nCount);

	for(int nRecCount = 0; nRecCount < nCount; nRecCount++)
	{
		memset(&vseiEnvelopedDataInfo->pRecipientInfo[nRecCount],0, sizeof(VS_RECIPIENT_INFO));
	}
	
	if(!vseiEnvelopedDataInfo->pRecipientInfo)
	{
		return -1;
	}

	dtRecipientInfoSeq = dtRecipientInfoSet->rightDERTree;
	nCount = 0;
	while(dtRecipientInfoSeq)
	{
		if(!dtRecipientInfoSeq || dtRecipientInfoSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		
		DERTree *dtCMSVersion = dtRecipientInfoSeq->rightDERTree;

		//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
		if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			return -1;
		}
		
		CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

		//We limit this implementation to assume that the version information can fit in a DWORD
		if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
		{
			return -1;
		}

		//Obtain the version bytes
		unsigned char byteVersion[4];
		for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
			byteVersion[i] = pcuiCMSVersion->pbData[i];
		for(unsigned int j=i;j<4; ++j)
			byteVersion[j] = 0x00;
		
		//Store the version in the EnvelopedDataInfo
		//1
		unsigned int dwVersion = *((_DWORD*)byteVersion);
		if(dwVersion != 0)
		{
			return -1;
		}
		
		DERTree *dtIssuerDNSerNumSeq = dtCMSVersion->nextDERTree;

		if(!dtIssuerDNSerNumSeq || dtIssuerDNSerNumSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtIssuerDN = dtIssuerDNSerNumSeq->rightDERTree;
		
		if(!dtIssuerDN || dtIssuerDN->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		//copy the Issuer DN DER blob
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.cbData = dtIssuerDN->currentBaseDER->BaseDERBlob->cbData;
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.pbData = (unsigned char*)malloc(vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.cbData);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.pbData)
		{
			return -1;
		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.pbData, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData,
				vseiEnvelopedDataInfo->pRecipientInfo[nCount].Issuer.cbData);

		DERTree *dtSerNum = dtIssuerDN->nextDERTree;

		//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
		if(!dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			return -1;
		}

		CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
		if(!pcuiSerNum)
		{
			return -1;
		}

		vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.cbData = pcuiSerNum->cbData;
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.pbData = (_PBYTE)malloc(sizeof(unsigned char) * pcuiSerNum->cbData);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.pbData)
		{
			return -1;
		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.pbData, pcuiSerNum->pbData, vseiEnvelopedDataInfo->pRecipientInfo[nCount].SerialNumber.cbData);

		DERTree *dtKeyEncAlgIdSeq = dtIssuerDNSerNumSeq->nextDERTree;

		if(!dtKeyEncAlgIdSeq || dtKeyEncAlgIdSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtKeyEncAlgId = dtKeyEncAlgIdSeq->rightDERTree;
		if(!dtKeyEncAlgId || dtKeyEncAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			return -1;
		}

		// 2 
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId = (char*)malloc(dtKeyEncAlgId->currentBaseDER->cbData + 1);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId)
		{
			return -1;

		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId, dtKeyEncAlgId->currentBaseDER->pbData, dtKeyEncAlgId->currentBaseDER->cbData);
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.pszObjId[dtKeyEncAlgId->currentBaseDER->cbData] = '\0';
		


		DERTree *dtKeyEncAlgIdParam = dtKeyEncAlgId->nextDERTree;

		if(!dtKeyEncAlgIdParam)
		{
			return -1;
		}

		if(dtKeyEncAlgIdParam->currentBaseDER->pbData)
		{
			vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(dtKeyEncAlgIdParam->currentBaseDER->cbData);
			if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.pbData, dtKeyEncAlgIdParam->currentBaseDER->pbData, dtKeyEncAlgIdParam->currentBaseDER->cbData);
			vseiEnvelopedDataInfo->pRecipientInfo[nCount].KeyEncryptionAlgID.Parameters.cbData = dtKeyEncAlgIdParam->currentBaseDER->cbData;
		}

		DERTree *dtEncryptedKey = dtKeyEncAlgIdSeq->nextDERTree;

		if(!dtEncryptedKey || dtEncryptedKey->currentBaseDER->Type != OCTET_STRING)
		{
			return -1;
		}
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.pbData = (unsigned char*)malloc(dtEncryptedKey->currentBaseDER->cbData);
		if(!vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.pbData)
		{
			return -1;
		}
		memcpy(vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.pbData, 
			dtEncryptedKey->currentBaseDER->pbData, dtEncryptedKey->currentBaseDER->cbData);
		vseiEnvelopedDataInfo->pRecipientInfo[nCount].EncryptedKey.cbData = dtEncryptedKey->currentBaseDER->cbData;
		nCount ++;
		dtRecipientInfoSeq = dtRecipientInfoSeq->nextDERTree;

	}
	vseiEnvelopedDataInfo->nRecipientInfos = nCount++;


	DERTree *dtEncryptedContentInfoSeq = dtRecipientInfoSet->nextDERTree;

	if(!dtEncryptedContentInfoSeq || dtEncryptedContentInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtDataObjId = dtEncryptedContentInfoSeq->rightDERTree;

	if(!dtDataObjId)
	{
		return -1;
	}

	//If OBJECT IDENTIFIER is not Data (1.2.840.113549.1.7.1)
	if(memcmp(dtDataObjId->currentBaseDER->pbData, vssc_szOID_RSA_data, dtDataObjId->currentBaseDER->cbData) != 0)
	{
		return -1;
	}

	DERTree *dtEncryptionAlgIDSeq = dtDataObjId->nextDERTree;

	if(!dtEncryptionAlgIDSeq || dtEncryptionAlgIDSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtEncAlgId = dtEncryptionAlgIDSeq->rightDERTree;
	if(!dtEncAlgId || dtEncAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	
	vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId = (char*)malloc(dtEncAlgId->currentBaseDER->cbData + 1);
	if(!vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId)
	{
		return -1;
	}
	memcpy(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId, dtEncAlgId->currentBaseDER->pbData, dtEncAlgId->currentBaseDER->cbData);
	vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId[dtEncAlgId->currentBaseDER->cbData] = '\0';

	// RC2
	if(strcmp(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId, vssc_szOID_RSA_RC2CBC) == 0)
	{
		DERTree *dtEncAlgIdSeq = dtEncAlgId->nextDERTree;

		// Right now not using the integer value
		DERTree *dtEncAlgIdInt = dtEncAlgIdSeq->rightDERTree;

		DERTree *dtEncAlgIdParam = dtEncAlgIdInt->nextDERTree;
		if(dtEncAlgIdParam->currentBaseDER->pbData)
		{
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(dtEncAlgIdParam->currentBaseDER->cbData);
			if(!vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,
				dtEncAlgIdParam->currentBaseDER->pbData, dtEncAlgIdParam->currentBaseDER->cbData);
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.cbData = dtEncAlgIdParam->currentBaseDER->cbData;
		}

		
	}

	else
	{
		DERTree *dtEncAlgIdParam = dtEncAlgId->nextDERTree;
	
		if(!dtEncAlgIdParam)
		{
			return -1;
		}

		if(dtEncAlgIdParam->currentBaseDER->pbData)
		{
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData = (unsigned char*)malloc(dtEncAlgIdParam->currentBaseDER->cbData);
			if(!vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,
				dtEncAlgIdParam->currentBaseDER->pbData, dtEncAlgIdParam->currentBaseDER->cbData);
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.cbData = dtEncAlgIdParam->currentBaseDER->cbData;
		}
	}


	DERTree *dtEncryptedContentTag = dtEncryptionAlgIDSeq->nextDERTree;

	//if(!dtEncryptedContentTag || (dtEncryptedContentTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtEncryptedContentTag->currentBaseDER->Encoding != CONSTRUCTED
	//		|| dtEncryptedContentTag->currentBaseDER->TagNumber != 0))
	
	if(!dtEncryptedContentTag || (dtEncryptedContentTag->currentBaseDER->Class != CONTEXT_SPECIFIC 
			|| dtEncryptedContentTag->currentBaseDER->TagNumber != 0))

	{
		return -1;
	}

	DERTree *dtEncryptedContent = NULL;
	DERTree *dtEncryptedContentNext = NULL;

	// Support for both explicit and implicit tag.
	// Not constructed
	if(dtEncryptedContentTag->currentBaseDER->Encoding != CONSTRUCTED)
	{

		dtEncryptedContent = dtEncryptedContentTag;
		dtEncryptedContentNext = dtEncryptedContent->nextDERTree;


	}
	else
	{
		dtEncryptedContent = dtEncryptedContentTag->rightDERTree;
		dtEncryptedContentNext = dtEncryptedContent->nextDERTree;
		
	}
	
	// Check if the data is broken into chunks
	//DERTree *dtEncryptedContent = dtEncryptedContentTag->rightDERTree;
	//DERTree *dtEncryptedContentNext = dtEncryptedContent->nextDERTree;

	DERTree *dtEncryptedContentTemp = dtEncryptedContent;
	unsigned long dwContentLen = 0;
	unsigned char *pbContentLen = NULL;

	// Check if the data is broken into chunks
	if(dtEncryptedContentNext == NULL)
	{
		
		//if(!dtEncryptedContent || dtEncryptedContent->currentBaseDER->Type != OCTET_STRING)
		if(!dtEncryptedContent)
		{
			return -1;
		}
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData = (unsigned char *)malloc(dtEncryptedContent->currentBaseDER->cbData);
		if(!vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData)
		{
			return -1;
		}
		//New Simder change
		//reverse(dtEncryptedContent->currentBaseDER->cbData, dtEncryptedContent->currentBaseDER->pbData);
		memcpy(vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData, dtEncryptedContent->currentBaseDER->pbData, dtEncryptedContent->currentBaseDER->cbData);
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.cbData = dtEncryptedContent->currentBaseDER->cbData;
	}
	else // chunks concatenate.
	{
		// Find the lenght first
		while(dtEncryptedContentTemp)
		{
			dwContentLen += dtEncryptedContentTemp->currentBaseDER->cbData;
			dtEncryptedContentTemp = dtEncryptedContentTemp->nextDERTree;

		}
		dtEncryptedContentTemp = dtEncryptedContent;
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData = (unsigned char*)malloc(dwContentLen);
		if(!vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData)
		{
			return -1;
		}
		vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.cbData = dwContentLen;
		pbContentLen = vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData;
		
		while(dtEncryptedContentTemp)
		{
			//New Simder change
			//reverse(dtEncryptedContentTemp->currentBaseDER->cbData,
			//		dtEncryptedContentTemp->currentBaseDER->pbData);
					
			memcpy(pbContentLen,
					dtEncryptedContentTemp->currentBaseDER->pbData,
					dtEncryptedContentTemp->currentBaseDER->cbData);
			pbContentLen += dtEncryptedContentTemp->currentBaseDER->cbData;
			dtEncryptedContentTemp = dtEncryptedContentTemp->nextDERTree;
		}
	}


	return 0;

}


int ParseSignedData(DERTree *dtPKCS7, VS_SIGNEDDATA_INFO *vssdiSignedDataInfo)
{
	
	// BUG BUG - while returning from the errors the memory allocated has to be freed.

	int nRetVal = 0;
	memset(vssdiSignedDataInfo, 0, sizeof(VS_SIGNEDDATA_INFO));
	
	DERTree* dtSignedDataContentInfo = dtPKCS7;

	if(!dtSignedDataContentInfo && dtSignedDataContentInfo->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}
	else
	{
		DERTree *dtSignedDataObjID = dtSignedDataContentInfo->rightDERTree;
		DERTree *dtSignedDataTag = dtSignedDataObjID->nextDERTree;

		if(!dtSignedDataObjID)
		{
			return -1;
		}
		
		//If OBJECT IDENTIFIER is not signedData (1.2.840.113549.1.7.2)
		if(memcmp(dtSignedDataObjID->currentBaseDER->pbData, vssc_szOID_RSA_signedData, dtSignedDataObjID->currentBaseDER->cbData) != 0)
		{
			return -1;
		}
		
		// Parse the SignedData
		if(!dtSignedDataTag || (dtSignedDataTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtSignedDataTag->currentBaseDER->Encoding != CONSTRUCTED
			|| dtSignedDataTag->currentBaseDER->TagNumber != 0))
		{
			return -1;
		}
		/*
			SignedData ::= SEQUENCE {
			version CMSVersion,
			digestAlgorithms DigestAlgorithmIdentifiers,
			encapContentInfo EncapsulatedContentInfo,
			certificates [0] IMPLICIT CertificateSet OPTIONAL,
			crls [1] IMPLICIT CertificateRevocationLists OPTIONAL,
			signerInfos SignerInfos }
		*/

		
		DERTree *dtSignedSeq = dtSignedDataTag->rightDERTree;
		
		//Check if SignedData is sequence
		if(!dtSignedSeq && dtSignedSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtCMSVersion = dtSignedSeq->rightDERTree;

		//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
		if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			return -1;
		}
		
		CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

		//We limit this implementation to assume that the version information can fit in a DWORD
		if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
		{
			return -1;
		}

		//Obtain the version bytes
		unsigned char byteVersion[4];
		for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
			byteVersion[i] = pcuiCMSVersion->pbData[i];
		for(unsigned int j=i;j<4; ++j)
			byteVersion[j] = 0x00;
		
		//Store the version in the SignedDataInfo
		//1
		vssdiSignedDataInfo->dwSDVersion = *((_DWORD*)byteVersion);

		/*
			digestAlgorithms DigestAlgorithmIdentifiers
			DigestAlgorithmIdentifiers ::= SET OF DigestAlgorithmIdentifier
			DigestAlgorithmIdentifier ::= AlgorithmIdentifier
			Assuming only one DigestAlgorithmIdentifier.
		*/
		DERTree *dtSetDigestAlgID = dtCMSVersion->nextDERTree;

		if(!dtSetDigestAlgID || dtSetDigestAlgID->currentBaseDER->Type != SET)
		{
			return -1;
		}

		DERTree *dtDigestAlgIDSeq = dtSetDigestAlgID->rightDERTree;
		if(!dtDigestAlgIDSeq || dtDigestAlgIDSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtDigestAlgId = dtDigestAlgIDSeq->rightDERTree;
		if(!dtDigestAlgId || dtDigestAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			return -1;
		}

		// 2 DigestAlgID
		vssdiSignedDataInfo->DigestAlgId.pszObjId = (char*)malloc(dtDigestAlgId->currentBaseDER->cbData + 1);
		if(!vssdiSignedDataInfo->DigestAlgId.pszObjId)
		{
			return -1;
		}
		memcpy(vssdiSignedDataInfo->DigestAlgId.pszObjId, dtDigestAlgId->currentBaseDER->pbData, dtDigestAlgId->currentBaseDER->cbData);
		vssdiSignedDataInfo->DigestAlgId.pszObjId[dtDigestAlgId->currentBaseDER->cbData] = '\0';



		DERTree *dtDigestAlgIdParam = dtDigestAlgId->nextDERTree;
		if(!dtDigestAlgIdParam)
		{
			return -1;
		}

		// 3 DigestAlgID param
		if(dtDigestAlgIdParam->currentBaseDER->pbData)
		{
			vssdiSignedDataInfo->DigestAlgId.Parameters.pbData = (unsigned char*)malloc(dtDigestAlgIdParam->currentBaseDER->cbData);
			if(!vssdiSignedDataInfo->DigestAlgId.Parameters.pbData)
			{
				return -1;
			}
			memcpy(vssdiSignedDataInfo->DigestAlgId.Parameters.pbData, dtDigestAlgIdParam->currentBaseDER->pbData, dtDigestAlgIdParam->currentBaseDER->cbData);
			vssdiSignedDataInfo->DigestAlgId.Parameters.cbData = dtDigestAlgIdParam->currentBaseDER->cbData;
		}


		DERTree *dtDataContSeq = dtSetDigestAlgID->nextDERTree;

		if(!dtDataContSeq || dtDataContSeq->currentBaseDER->Type != SEQUENCE)
		{
			return -1;
		}

		DERTree *dtDataObjId = dtDataContSeq->rightDERTree;
		if(!dtDataObjId )
		{
			return -1;
		}

		//If OBJECT IDENTIFIER is not Data (1.2.840.113549.1.7.1)
		if(memcmp(dtDataObjId->currentBaseDER->pbData, vssc_szOID_RSA_data, dtDataObjId->currentBaseDER->cbData) != 0)
		{
			return -1;
		}

		DERTree *dtDataOctetsTag = dtDataObjId->nextDERTree;

		if(dtDataOctetsTag)
		{
			if((dtDataOctetsTag->currentBaseDER->Class != CONTEXT_SPECIFIC || dtDataOctetsTag->currentBaseDER->Encoding != CONSTRUCTED
			|| dtDataOctetsTag->currentBaseDER->TagNumber != 0)) 
			{
				return -1;
			}

			DERTree *dtDataOctets = dtDataOctetsTag->rightDERTree;

			// 4 Content signed  
			// Check whether it is Constructed encoding of simple type, octet string.
			DERTree* dtDataOctetsConstructed = dtDataOctetsTag->rightDERTree;

			if(dtDataOctetsConstructed && dtDataOctetsConstructed->currentBaseDER->Encoding == CONSTRUCTED && dtDataOctetsConstructed->currentBaseDER->Type == OCTET_STRING)
			{
				// Concatenate all the OCTET Strings and then copy
				DERTree* dtDataOctetsStart = dtDataOctetsConstructed->rightDERTree;
				if(!dtDataOctetsStart)
				{
					return -1;
				}

				DERTree* dtDataTemp = dtDataOctetsStart;
				unsigned long dwDataLen = 0;
				unsigned char* pbContentData = NULL;
				unsigned char* pbContentDataTmp = NULL;

				while(dtDataTemp)
				{
					dwDataLen += dtDataTemp->currentBaseDER->cbData;
					dtDataTemp = dtDataTemp->nextDERTree;
				}
				pbContentData = (unsigned char*)malloc(dwDataLen);
				pbContentDataTmp = pbContentData;

				dtDataTemp = dtDataOctetsStart;
				while(dtDataTemp)
				{
					memcpy(pbContentData, dtDataTemp->currentBaseDER->pbData, dtDataTemp->currentBaseDER->cbData);
					pbContentData += dtDataTemp->currentBaseDER->cbData;
					dtDataTemp = dtDataTemp->nextDERTree;
				}

				vssdiSignedDataInfo->EncapContentInfo.pbData = (unsigned char*)malloc(dwDataLen);
				memcpy(vssdiSignedDataInfo->EncapContentInfo.pbData, pbContentDataTmp, dwDataLen);
				vssdiSignedDataInfo->EncapContentInfo.cbData = dwDataLen;

				if(pbContentDataTmp)
				{
					free(pbContentDataTmp);
				}

			}
			else
			{
				if(dtDataOctets && dtDataOctets->currentBaseDER->pbData && dtDataOctets->currentBaseDER->cbData)
				{
					vssdiSignedDataInfo->EncapContentInfo.pbData = (unsigned char*)malloc(dtDataOctets->currentBaseDER->cbData);
					if(!vssdiSignedDataInfo->EncapContentInfo.pbData)
					{
						return -1;
					}
					memcpy(vssdiSignedDataInfo->EncapContentInfo.pbData, dtDataOctets->currentBaseDER->pbData, dtDataOctets->currentBaseDER->cbData);
					vssdiSignedDataInfo->EncapContentInfo.cbData = dtDataOctets->currentBaseDER->cbData;
				}
			}
		}

		//optional
		bool bCertPresent = false;
		bool bCRLPresent = false;
		
		//Determine whether the optional Certs and CRLs are present.
		DERTree *dtCertPresent = NULL;
		DERTree *dtCertPresentTemp = NULL;
		DERTree *dtCertPresentPrev = NULL;

		DERTree *dtCRLPresent = NULL;
		DERTree *dtCertSet = dtDataContSeq->nextDERTree;
		if(dtCertSet && (dtCertSet->currentBaseDER->Class == CONTEXT_SPECIFIC && dtCertSet->currentBaseDER->Encoding == CONSTRUCTED
			&& dtCertSet->currentBaseDER->TagNumber == 0))
		{
			//Certs present.
			bCertPresent = true;
			if(dtCertSet->nextDERTree && (dtCertSet->nextDERTree->currentBaseDER->Class == CONTEXT_SPECIFIC && dtCertSet->nextDERTree->currentBaseDER->Encoding == CONSTRUCTED
			     && dtCertSet->nextDERTree->currentBaseDER->TagNumber == 1)) // check for CRLs
			{
				//CRLs present
				bCRLPresent = true;
			}

		} 
		else if( dtCertSet && (dtCertSet->currentBaseDER->Class == CONTEXT_SPECIFIC && dtCertSet->currentBaseDER->Encoding == CONSTRUCTED
			&& dtCertSet->currentBaseDER->TagNumber == 1)) // check for CRLs
		{
			// CRLs present.
			bCRLPresent = true;
		}
		
		if(bCertPresent == true)
		{
			//copy certs - stripping of the SET headers and then copying. If SET is required copy dtCertPresent->currentBaseDER->BaseDERBlob->pbData
			//dtCertPresent = dtDataContSeq->nextDERTree; // need this pointer later for accessing the SingerInfo
			dtCertPresent = dtCertSet->rightDERTree;
		
			dtCertPresentTemp = dtCertPresent;
			CBaseDERCollection cbdcCertChain;
			while(dtCertPresentTemp != NULL)
			{
				CBaseDERCollection cbdcCertChainTemp(dtCertPresentTemp->currentBaseDER->BaseDERBlob->cbData,
								dtCertPresentTemp->currentBaseDER->BaseDERBlob->pbData);
				cbdcCertChain = cbdcCertChain + cbdcCertChainTemp;

				dtCertPresentPrev = dtCertPresentTemp;
				dtCertPresentTemp = dtCertPresentTemp->nextDERTree;
			}

			vssdiSignedDataInfo->CertificateSet.cbData = cbdcCertChain.BaseDERBlob->cbData;
			vssdiSignedDataInfo->CertificateSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			if(!vssdiSignedDataInfo->CertificateSet.pbData)
			{
				return -1;
			}
			memcpy(vssdiSignedDataInfo->CertificateSet.pbData, cbdcCertChain.BaseDERBlob->pbData,
							vssdiSignedDataInfo->CertificateSet.cbData); 

			//vssdiSignedDataInfo->CertificateSet.cbData = dtCertPresent->currentBaseDER->BaseDERBlob->cbData;
			//vssdiSignedDataInfo->CertificateSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			//memcpy(vssdiSignedDataInfo->CertificateSet.pbData, dtCertPresent->currentBaseDER->BaseDERBlob->pbData, vssdiSignedDataInfo->CertificateSet.cbData); 

			/* Code for getting end entity cert.
			dtCertPresentTemp = dtCertPresent;
			// if there are is a cert chain get the end entity cert
			// we assume the last cert in the chain to be the end entity cert
			while(dtCertPresentTemp != NULL)
			{
				dtCertPresentPrev = dtCertPresentTemp;
				dtCertPresentTemp = dtCertPresentTemp->nextDERTree;
			}
			vssdiSignedDataInfo->CertificateSet.cbData = dtCertPresentPrev->currentBaseDER->BaseDERBlob->cbData;
			vssdiSignedDataInfo->CertificateSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			memcpy(vssdiSignedDataInfo->CertificateSet.pbData, dtCertPresentPrev->currentBaseDER->BaseDERBlob->pbData, vssdiSignedDataInfo->CertificateSet.cbData); 
			*/

		}
		if(bCRLPresent == true)
		{
			//copy crls
			if(dtCertPresent)
				dtCRLPresent = dtCertPresent->nextDERTree;
			else
				dtCRLPresent = dtDataContSeq->nextDERTree;
			
			vssdiSignedDataInfo->CrlSet.cbData = dtCRLPresent->currentBaseDER->cbData;
			vssdiSignedDataInfo->CrlSet.pbData = (unsigned char*)malloc(vssdiSignedDataInfo->CertificateSet.cbData);
			if(!vssdiSignedDataInfo->CrlSet.pbData)
			{
				return -1;
			}
			memcpy(vssdiSignedDataInfo->CrlSet.pbData, dtCRLPresent->currentBaseDER->pbData, vssdiSignedDataInfo->CrlSet.cbData); 

		}

		DERTree *dtSignerInfo = NULL;
		if(bCertPresent == false && bCRLPresent == false)
		{
			dtSignerInfo = dtDataContSeq->nextDERTree;
		}
		else if(bCertPresent == true && bCRLPresent == true)
		{
			// BUG BUG check this later
			dtSignerInfo = dtCRLPresent->nextDERTree;
			
		}
		else
		{
			//dtSignerInfo = dtCertPresent->nextDERTree;
			dtSignerInfo = dtCertSet->nextDERTree;
		}

		nRetVal = ParseSignerInfo(dtSignerInfo, &vssdiSignedDataInfo->SignerInfo);
		

		if(nRetVal != 0)
		{
			return -1;
		}

	}


	return 0;

}

int ParseSignerInfo(DERTree *dtPKCS7,
					  VS_SIGNER_INFO_PARSE *vssipSignerInfo )
{
	// BUG BUG - while returning from the errors the memory allocated has to be freed.

	memset(vssipSignerInfo, 0, sizeof(VS_SIGNER_INFO_PARSE));

	DERTree *dtSingerInfoSet = dtPKCS7;

	if(!dtSingerInfoSet || dtSingerInfoSet->currentBaseDER->Type != SET)
	{
			return -1;
	}

	DERTree *dtSingerInfoSeq = dtSingerInfoSet->rightDERTree;

	if(!dtSingerInfoSeq || dtSingerInfoSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtCMSVersion = dtSingerInfoSeq->rightDERTree;

	//Make sure that the derblob in the dtCMSVersion is of type UniversalInteger
	if(!dtCMSVersion || dtCMSVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}
	
	CUniversalInteger* pcuiCMSVersion = (CUniversalInteger*)dtCMSVersion->currentBaseDER;

	//We limit this implementation to assume that the version information can fit in a DWORD
	if(!pcuiCMSVersion || (pcuiCMSVersion->cbData > sizeof(_DWORD)))
	{
		return -1;
	}

	//Obtain the version bytes
	unsigned char byteVersion[4];
	for(unsigned int i = 0;i < pcuiCMSVersion->cbData; ++i)
		byteVersion[i] = pcuiCMSVersion->pbData[i];
	for(unsigned int j=i;j<4; ++j)
		byteVersion[j] = 0x00;
	
	//Store the version in the SignedDataInfo
	//1
	vssipSignerInfo->dwSIVersion = *((_DWORD*)byteVersion);

	DERTree *dtIssuerDNSerNumSeq = dtCMSVersion->nextDERTree;

	if(!dtIssuerDNSerNumSeq || dtIssuerDNSerNumSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	DERTree *dtIssuerDN = dtIssuerDNSerNumSeq->rightDERTree;
	
	if(!dtIssuerDN || dtIssuerDN->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}

	//copy the Issuer DN DER blob
	vssipSignerInfo->Issuer.cbData = dtIssuerDN->currentBaseDER->BaseDERBlob->cbData;
	vssipSignerInfo->Issuer.pbData = (unsigned char*)malloc(vssipSignerInfo->Issuer.cbData);
	
	if(!vssipSignerInfo->Issuer.pbData)
	{
		return -1;
	}

	memcpy(vssipSignerInfo->Issuer.pbData, dtIssuerDN->currentBaseDER->BaseDERBlob->pbData,
			vssipSignerInfo->Issuer.cbData);

	DERTree *dtSerNum = dtIssuerDN->nextDERTree;

	//Make sure that the blob corresponding to dtSerNum is of type UniversalInteger
	if(!dtSerNum || dtSerNum->currentBaseDER->Type != UNIVERSAL_INTEGER)
	{
		return -1;
	}

	CUniversalInteger* pcuiSerNum = (CUniversalInteger*)dtSerNum->currentBaseDER;
	if(!pcuiSerNum)
	{
		return -1;
	}

	vssipSignerInfo->SerialNumber.cbData = pcuiSerNum->cbData;
	vssipSignerInfo->SerialNumber.pbData = (_PBYTE)malloc(sizeof(unsigned char) * pcuiSerNum->cbData);
	if(!vssipSignerInfo->SerialNumber.pbData)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SerialNumber.pbData, pcuiSerNum->pbData, vssipSignerInfo->SerialNumber.cbData);


	DERTree *dtDigestAlgIdSeq = dtIssuerDNSerNumSeq->nextDERTree;
	if(!dtDigestAlgIdSeq || dtDigestAlgIdSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}


	DERTree *dtDigestAlgId = dtDigestAlgIdSeq->rightDERTree;
	if(!dtDigestAlgId || dtDigestAlgId->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	// 2 DigestAlgID
	vssipSignerInfo->DigestAlgId.pszObjId = (char*)malloc(dtDigestAlgId->currentBaseDER->cbData + 1);
	if(!vssipSignerInfo->DigestAlgId.pszObjId)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->DigestAlgId.pszObjId, dtDigestAlgId->currentBaseDER->pbData, dtDigestAlgId->currentBaseDER->cbData);
	vssipSignerInfo->DigestAlgId.pszObjId[dtDigestAlgId->currentBaseDER->cbData] = '\0';
	//vssdiSignedDataInfo->DigestAlgId.cbData = dtDigestAlgId->currentBaseDER->cbData;


	DERTree *dtDigestAlgIdParam = dtDigestAlgId->nextDERTree;
	if(!dtDigestAlgIdParam)
	{
		return -1;
	}

	// 3 DigestAlgID param
	if(dtDigestAlgIdParam->currentBaseDER->pbData)
	{
		vssipSignerInfo->DigestAlgId.Parameters.pbData = (unsigned char*)malloc(dtDigestAlgIdParam->currentBaseDER->cbData);
		if(!vssipSignerInfo->DigestAlgId.Parameters.pbData)
		{
			return -1;
		}
		memcpy(vssipSignerInfo->DigestAlgId.Parameters.pbData, dtDigestAlgIdParam->currentBaseDER->pbData, dtDigestAlgIdParam->currentBaseDER->cbData);
		vssipSignerInfo->DigestAlgId.Parameters.cbData = dtDigestAlgIdParam->currentBaseDER->cbData;
	}


	DERTree *dtSignedAttribs = dtDigestAlgIdSeq->nextDERTree;
	DERTree *dtSignedAttribsPre = NULL;
	DERTree *dtSigAlgIDSeq = NULL;

	bool bAttribPresent = false;

	if(dtSignedAttribs && (dtSignedAttribs->currentBaseDER->Class == CONTEXT_SPECIFIC && dtSignedAttribs->currentBaseDER->Encoding == CONSTRUCTED
			&& dtSignedAttribs->currentBaseDER->TagNumber == 0))
	{
		bAttribPresent = true;
	}

	if(bAttribPresent == true)
	{
		//copy signed attributes.
		dtSignedAttribsPre = dtDigestAlgIdSeq->nextDERTree;
		vssipSignerInfo->SignedAttributes.pbData = (unsigned char*)malloc(dtSignedAttribsPre->currentBaseDER->cbData);
		if(!vssipSignerInfo->SignedAttributes.pbData)
		{
			return -1;
		}
		vssipSignerInfo->SignedAttributes.cbData = dtSignedAttribsPre->currentBaseDER->cbData;
		memcpy(vssipSignerInfo->SignedAttributes.pbData, dtSignedAttribsPre->currentBaseDER->pbData,
		vssipSignerInfo->SignedAttributes.cbData);

	}

	if(dtSignedAttribsPre)
	{
		//Attrib present AlgID is Attribs next
		dtSigAlgIDSeq = dtSignedAttribsPre->nextDERTree;
	}
	else
	{
		// Attrib not present AlgID is IssuerDNSerialNum next
		dtSigAlgIDSeq = dtDigestAlgIdSeq->nextDERTree;
	}

	if(!dtSigAlgIDSeq || dtSigAlgIDSeq->currentBaseDER->Type != SEQUENCE)
	{
		return -1;
	}


	DERTree *dtSigAlgID = dtSigAlgIDSeq->rightDERTree;
	if(!dtSigAlgID || dtSigAlgID->currentBaseDER->Type != OBJECT_IDENTIFIER)
	{
		return -1;
	}

	vssipSignerInfo->SignatureAlgId.pszObjId = (char*)malloc(dtSigAlgID->currentBaseDER->cbData + 1);
	if(!vssipSignerInfo->SignatureAlgId.pszObjId)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SignatureAlgId.pszObjId, dtSigAlgID->currentBaseDER->pbData, dtSigAlgID->currentBaseDER->cbData);
	vssipSignerInfo->SignatureAlgId.pszObjId[dtSigAlgID->currentBaseDER->cbData] = '\0';
	

		
	DERTree *dtSigAlgIdParam = dtSigAlgID->nextDERTree;

	// 3 SigAlgID param
	if(dtSigAlgIdParam->currentBaseDER->pbData)
	{
		vssipSignerInfo->SignatureAlgId.Parameters.pbData = (unsigned char*)malloc(dtSigAlgIdParam->currentBaseDER->cbData);
		if(!vssipSignerInfo->SignatureAlgId.Parameters.pbData)
		{
			return -1;
		}
		memcpy(vssipSignerInfo->SignatureAlgId.Parameters.pbData, dtSigAlgIdParam->currentBaseDER->pbData,
				dtSigAlgIdParam->currentBaseDER->cbData);
		vssipSignerInfo->SignatureAlgId.Parameters.cbData = dtSigAlgIdParam->currentBaseDER->cbData;
	}

	// Signature Blob
	DERTree *dtSignatureValue = dtSigAlgIDSeq->nextDERTree;
		
	if(!dtSignatureValue || dtSignatureValue->currentBaseDER->Type != OCTET_STRING)
	{
		return -1;
	}
	vssipSignerInfo->SignatureValue.cbData = dtSignatureValue->currentBaseDER->cbData;
	vssipSignerInfo->SignatureValue.pbData = (unsigned char*)malloc(vssipSignerInfo->SignatureValue.cbData);
	if(!vssipSignerInfo->SignatureValue.pbData)
	{
		return -1;
	}
	memcpy(vssipSignerInfo->SignatureValue.pbData, dtSignatureValue->currentBaseDER->pbData, vssipSignerInfo->SignatureValue.cbData);
	
	return 0;

}

 
							
void FreePKCS7Info(VS_PKCS7_INFO *vsspiPKCS7Info)
{
	if(vsspiPKCS7Info)
	{
		if(vsspiPKCS7Info->ePKCS7Type == PKCS7_SIGNED)
		{
			FreeSignedDataInfo(&vsspiPKCS7Info->SignedDataInfo);
		}
		else if(vsspiPKCS7Info->ePKCS7Type == PKCS7_ENVELOPED)
		{
			FreeEnvelopedInfo(&vsspiPKCS7Info->EncryptedDataInfo);
		}
		else
		{
			// do nothing
		}
	}

}

void FreeEnvelopedInfo(VS_ENVELOPEDDATA_INFO *vseiEnvelopedDataInfo)
{
	if(vseiEnvelopedDataInfo)
	{
		FreeRecipientInfo(vseiEnvelopedDataInfo->pRecipientInfo, 
							vseiEnvelopedDataInfo->nRecipientInfos);
		if(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId)
		{
			free(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId);
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.pszObjId = NULL;
		}
		if(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData)
		{
			free(vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData);
			vseiEnvelopedDataInfo->EncryptedContent.ContentEncryptionAlgID.Parameters.pbData = NULL;
		}
		if(vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData)
		{
			free(vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData);
			vseiEnvelopedDataInfo->EncryptedContent.EncryptedContent.pbData = NULL;
		}

	}
}

void FreeRecipientInfo(VS_RECIPIENT_INFO	*pRecipientInfo, int nRecipientCount)
{

	if(pRecipientInfo)
	{
		for(int i = 0; i < nRecipientCount; i ++)
		{
			if(pRecipientInfo[i].Issuer.pbData)
			{
				free(pRecipientInfo[i].Issuer.pbData);
				pRecipientInfo[i].Issuer.pbData = NULL;
			}

			if(pRecipientInfo[i].EncryptedKey.pbData)
			{
				free(pRecipientInfo[i].EncryptedKey.pbData);
				pRecipientInfo[i].EncryptedKey.pbData = NULL;
			}

			if(pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData)
			{
				free(pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData);
				pRecipientInfo[i].KeyEncryptionAlgID.Parameters.pbData = NULL;
			}

			if(pRecipientInfo[i].KeyEncryptionAlgID.pszObjId)
			{
				free(pRecipientInfo[i].KeyEncryptionAlgID.pszObjId);
				pRecipientInfo[i].KeyEncryptionAlgID.pszObjId = NULL;
			}

			if(pRecipientInfo[i].SerialNumber.pbData)
			{
				free(pRecipientInfo[i].SerialNumber.pbData);
				pRecipientInfo[i].SerialNumber.pbData = NULL;
			}

		}

		//free(pRecipientInfo);
	}
		
}

void FreeSignedDataInfo(VS_SIGNEDDATA_INFO *vssdiSignedDataInfo)
{

	if(vssdiSignedDataInfo)
	{
		if(vssdiSignedDataInfo->DigestAlgId.pszObjId)
		{
			free(vssdiSignedDataInfo->DigestAlgId.pszObjId);
			vssdiSignedDataInfo->DigestAlgId.pszObjId = NULL;
		}

		if(vssdiSignedDataInfo->DigestAlgId.Parameters.pbData)
		{
			free(vssdiSignedDataInfo->DigestAlgId.Parameters.pbData);
			vssdiSignedDataInfo->DigestAlgId.Parameters.pbData = NULL;
		}

		if(vssdiSignedDataInfo->EncapContentInfo.pbData)
		{
			free(vssdiSignedDataInfo->EncapContentInfo.pbData);
			vssdiSignedDataInfo->EncapContentInfo.pbData = NULL;
		}

		if(vssdiSignedDataInfo->CertificateSet.pbData)
		{
			free(vssdiSignedDataInfo->CertificateSet.pbData);
			vssdiSignedDataInfo->CertificateSet.pbData = NULL;
		}

		if(vssdiSignedDataInfo->CrlSet.pbData)
		{
			free(vssdiSignedDataInfo->CrlSet.pbData);
			vssdiSignedDataInfo->CrlSet.pbData = NULL;
		}

		FreeSignerInfo(&vssdiSignedDataInfo->SignerInfo);
	}

}

void FreeSignerInfo(VS_SIGNER_INFO_PARSE *vssipSignerInfo)
{
	if(vssipSignerInfo)
	{
		if(vssipSignerInfo->Issuer.pbData)
		{
			free(vssipSignerInfo->Issuer.pbData);
			vssipSignerInfo->Issuer.pbData = NULL;
		}

		if(vssipSignerInfo->SerialNumber.pbData)
		{
			free(vssipSignerInfo->SerialNumber.pbData);
			vssipSignerInfo->SerialNumber.pbData = NULL;
		}

		if(vssipSignerInfo->DigestAlgId.pszObjId)
		{
			free(vssipSignerInfo->DigestAlgId.pszObjId);
			vssipSignerInfo->DigestAlgId.pszObjId = NULL;
		}

		if(vssipSignerInfo->DigestAlgId.Parameters.pbData)
		{
			free(vssipSignerInfo->DigestAlgId.Parameters.pbData);
			vssipSignerInfo->DigestAlgId.Parameters.pbData = NULL;
		}

		if(vssipSignerInfo->SignedAttributes.pbData)
		{
			free(vssipSignerInfo->SignedAttributes.pbData);
			vssipSignerInfo->SignedAttributes.pbData = NULL;
		}

		if(vssipSignerInfo->SignatureAlgId.pszObjId)
		{
			free(vssipSignerInfo->SignatureAlgId.pszObjId);
			vssipSignerInfo->SignatureAlgId.pszObjId = NULL;
		}

		if(vssipSignerInfo->SignatureAlgId.Parameters.pbData)
		{
			free(vssipSignerInfo->SignatureAlgId.Parameters.pbData);
			vssipSignerInfo->SignatureAlgId.Parameters.pbData = NULL;
		}

		if(vssipSignerInfo->SignatureValue.pbData)
		{
			free(vssipSignerInfo->SignatureValue.pbData);
			vssipSignerInfo->SignatureValue.pbData = NULL;
		}
	}

}



				   

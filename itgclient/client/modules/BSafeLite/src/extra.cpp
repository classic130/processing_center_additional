
#define SHA1HASH_SIZE 20

/*
main()
{
	A_RSA_KEY RSAPrivKey;
	A_RSA_KEY RSAPubKey;
	ITEM RC4Key;

	BYTE* pbPKCS10;
	unsigned int nPKCS10Len;
	
	
	printf("Press any key to create a new key pair");
	getch();
*/
/*	
	BYTE decryptThis[] = {
		0x7D, 0xDD, 0xA8, 0x23, 0x85, 0x27, 0x95, 0xE2, 0x6C, 0xDB, 0x7E, 0xA3, 0x12, 0xBE, 0x83, 0x14,
		0xEC, 0x26, 0xEA, 0xDD, 0x77, 0x7E, 0xF6, 0x81, 0x4D, 0x9E, 0x80, 0x73, 0xF9, 0x5F, 0x58, 0x0F,
        0x5E, 0xF3, 0x31, 0xE8, 0x7B, 0x20, 0xF3, 0xBD, 0xC4, 0xAE, 0x21, 0x24, 0x3B, 0x60, 0xFA, 0x65,
        0x6B, 0xF6, 0x67, 0xFB, 0x9C, 0xEA, 0x69, 0xFF, 0x4C, 0xB7, 0xDC, 0x4A, 0xB9, 0x9E, 0xDA, 0x8E,
        0x2C, 0xE8, 0x2A, 0xBF, 0x37, 0xE8, 0xD1, 0xC2, 0x5F, 0xD3, 0x06, 0x36, 0x47, 0xB9, 0xB3, 0x88,
        0xBC, 0x9E, 0x98, 0x56, 0xEA, 0x60, 0x41, 0x92, 0x5D, 0xCE, 0x6A, 0x80, 0xF0, 0x29, 0x75, 0x97,
        0xD2, 0x49, 0xB4, 0xC0, 0x75, 0xD2, 0xF2, 0x69, 0x6A, 0x31, 0xED, 0xE8, 0xAF, 0x6D, 0x7C, 0xA7,
        0xC8, 0xCE, 0x67, 0xA1, 0xB1, 0xCF, 0x0B, 0x59, 0x69, 0x4D, 0xBD, 0x04, 0x02, 0xBB, 0x87, 0x59
	};
	
	BYTE pubkeymod[] = { 
		0xA4, 0x0A, 0xE5, 0x00, 0xDE, 0xB2, 0xC5, 0xD2, 0x6C, 0xEC, 0x23, 0x5F, 0x8E, 0xB2, 0x62,
		0xD2, 0xBB, 0x52, 0xCB, 0x27, 0x88, 0x43, 0x14, 0xB3, 0x43, 0x0D, 0x8B, 0xF2, 0x0A, 0xAD, 0x66,
		0xF2, 0x77, 0x2E, 0x8F, 0x94, 0xD0, 0xFF, 0x2F, 0xB3, 0x59, 0x1A, 0x4D, 0x93, 0x8E, 0x0F, 0xEE,
		0x59, 0xA9, 0xE5, 0x86, 0xC2, 0x2B, 0x10, 0x12, 0x87, 0x9B, 0x2E, 0x4B, 0xBE, 0xC5, 0xB3, 0x6A,
		0x41, 0x24, 0xDA, 0x4A, 0x1D, 0x1A, 0x16, 0xCF, 0x36, 0x08, 0x1B, 0x76, 0x56, 0xAF, 0x22, 0xCD,
		0x90, 0x2C, 0x17, 0x22, 0x56, 0x93, 0x7B, 0x94, 0x30, 0x5B, 0xC0, 0x38, 0x43, 0x09, 0x40, 0xC4,
		0x0C, 0xF5, 0xF4, 0xCF, 0x6F, 0xB4, 0x0B, 0x02, 0xAF, 0xD8, 0x7B, 0x76, 0x2E, 0x3E, 0xDB, 0x3B,
		0x28, 0xE1, 0x9F, 0x04, 0x71, 0x9D, 0xBA, 0xCB, 0x8F, 0xBF, 0x0F, 0x8F, 0x18, 0x1C, 0x9C, 0x74, 0x1F
	};

	BYTE pubkeyexp[] = {0x01, 0x00, 0x01};

	RSAPubKey.exponent.len = 3;
	RSAPubKey.exponent.data = pubkeyexp;

	RSAPubKey.modulus.len = 128;
	RSAPubKey.modulus.data = pubkeymod;

	BYTE decryptedData[128];
	unsigned int decDataSize = 128;
	DecryptData(&RSAPubKey, decryptThis, 128, decryptedData, &decDataSize);
*/
/*

	//Do KeyGen
	if(DoKeyGen(&RSAPrivKey, &RSAPubKey))
	{
		printf("Error generating keys");
	}



	BYTE hashVal[20];
	BYTE Signature[255];
	unsigned int nSignatureSize = 255;
	
	

	//Store the pkcs10 in a file

	//Read the X.509 cert
	BYTE byteCert[1024];
	int index = 0;
	FILE* fpCert;
	fpCert = fopen("cert2.bin","rb");
	while(!feof(fpCert))
	{
		fscanf(fpCert,"%c", byteCert+index);
		index ++;
	}
	index --;

	CCertInfo cciCertInfo(byteCert, index);
	cciCertInfo.GetCertInfo ();

	//Input the data to be signed
	unsigned char szDataToSign[1024];
	printf("\nEnter the data to be signed.\n");
	scanf("%s",szDataToSign);

	HashData(szDataToSign,strlen((const char*)szDataToSign),hashVal);

	//Test symmetric algorithm
	//Use the first 16 bytes of the hashVal as the symmetric key to do symmetric encryption and decryption
	BYTE byteEncData[1024];
	BYTE byteDecData[1024];
	unsigned int nEncDataSize = 1024;
	unsigned int nDecDataSize = 1024;
	RC4Key.len = 16;
	RC4Key.data = hashVal;
	SymEncryptData(&RC4Key, szDataToSign,strlen((const char*)szDataToSign),byteEncData,&nEncDataSize);
	SymDecryptData(&RC4Key, byteEncData, nEncDataSize, byteDecData, &nDecDataSize);

	EncryptData(&RSAPrivKey,hashVal,20,Signature,&nSignatureSize);
	//Create a pkcs10
	if(CreatePKCS10(&RSAPubKey, &RSAPrivKey, &pbPKCS10, &nPKCS10Len))
	{
		printf("Error generating keys");
	}

	//Sign the data
	BYTE* pbSignedPKCS7;
	unsigned int nSignedPKCS7Size;
	SignData(szDataToSign, strlen((const char*)szDataToSign), &RSAPrivKey, byteCert,index, &pbSignedPKCS7, &nSignedPKCS7Size);

	//Store the pkcs7 in a file

}
*/

#if 0
int SignData(BYTE* pbDataToSign, unsigned int nDataToSignSize, A_RSA_KEY* rsaPrivKey, BYTE* pbCert, unsigned int nCertSize, BYTE** ppbSignedPKCS7, unsigned int* pnSignedPKCS7Size)
{
	int retVal = 0;
	BYTE pbHash[20];

	//Hash the data to be signed
	if(HashData(pbDataToSign,nDataToSignSize,pbHash))
	{
		retVal = VS_HASH_ERR;
	}
	else
	{
		//Encrypt the hash with the private key to obtain the signature
		PBYTE pbSignature;
		unsigned int nSignatureSize;
		nSignatureSize = rsaPrivKey->modulus.len;
		pbSignature = (PBYTE)malloc(sizeof(BYTE)*nSignatureSize);
		if(!pbSignature)
		{
			retVal = VS_MEM_ERR;
		}
		else
		{
			/* Create the object of type DigestInfo. This is the object that will be encrypted. This is defined as 
			DigestInfo := SEQUENCE {
							digestAlgorithm DigestAlgorithmIdentifier
							digest			Digest
							}

			where 
				Digest := OCTET STRING
			*/

			//Create the octet string for the digest
			CMyOctetString cmyosDigest(SHA1HASH_SIZE, pbHash);

			//Create the sha1 object identifier
			char szSha1OID[] = "1.3.14.3.2.26";
			CObjectIdentifier cobjidSha1(strlen(szSha1OID),(PBYTE)szSha1OID);

			//Create a null object
			CNull cnullObj;
			
			//Create the sha1 algorithm identifier
			CBaseDERCollection cbdcAlgId;
			cbdcAlgId = cobjidSha1 + cnullObj ;
			CSequence cseqDigestAlg(cbdcAlgId);

			CBaseDERCollection cbdcDigestInfo;
			cbdcDigestInfo = cseqDigestAlg + cmyosDigest;
			CSequence cseqDigestInfo(cbdcDigestInfo);
			
			//Create the Algorithm identifier for sha
			if(EncryptData(rsaPrivKey, cseqDigestInfo.BaseDERBlob->pbData,cseqDigestInfo.BaseDERBlob->cbData,pbSignature,&nSignatureSize))
			{
				retVal = VS_ENC_ERR;
			}
			else
			{
				//Generate the pkcs7
				if(CreatePKCS7(pbSignature,nSignatureSize, pbCert, nCertSize, ppbSignedPKCS7, pnSignedPKCS7Size ))
				{
					retVal = VS_PKCS7_GEN_ERR;
				}
			}
			//Create the pkcs7 
			free(pbSignature);
		}
	}
	return retVal;
}

int CreatePKCS10(A_RSA_KEY* rsakeyPubKey, A_RSA_KEY* rsakeyPrivKey, PBYTE* pbPKCS10, unsigned int* pnPKCS10Len)
{

	int retVal = 0;

	/* Create Version object
		Version := INTEGER 
	*/
	short int nVersion = 0;
	CUniversalInteger cuiVersion(1,(PBYTE)&nVersion);

	/* Create the subject object of type Name defined as
		Name ::=	CHOICE { - - only one possibility for now - -  rdnSequence  RDNSequence }
		RDNSequence ::=	SEQUENCE OF RelativeDistinguishedName
		RelativeDistinguishedName ::= SET SIZE (1..MAX) OF AttributeTypeAndDistinguishedValue
		AttributeTypeAndDistinguishedValue ::= SEQUENCE {
														type			ATTRIBUTE.&id ({SupportedAttributes}),
														value			ATTRIBUTE.&Type({SupportedAttributes}{@type}),
														-- Note default and optional fields have been stripped off because we dont use them.
												}

		
		The subject object that we will create based on the above definition of Name will look as follows 

		subject = SEQUENCE {
						SET {
							SEQUENCE {
								OBJECT IDENTIFIER commonName (2 5 4 3)
								PrintableString 'vsc1enroll'
								}
							}
						}
				  }

	*/

	//Create the object identifier for CN
	char szCNObjId[] = "2.5.4.3";
	CObjectIdentifier cobjidCN(strlen(szCNObjId), (PBYTE)szCNObjId );

	//Create the printable string for Verisign Enrollment 'vsc1enroll'
	char szVSEnrollCN[] = "vsc1enroll"; //Common name for generating pkcs10 for verisign cert enrollment
	CPrintableString cpsVSEnrollString(strlen(szVSEnrollCN),(PBYTE)szVSEnrollCN);

	//Create the sequence for the CommonName (CN)
	CBaseDERCollection cbdcVSEnrollCN;
	cbdcVSEnrollCN = cobjidCN + cpsVSEnrollString;
	CSequence cseqVSEnrollCN(cbdcVSEnrollCN);
	
	//Create the SubjectRDN
	CSet csetSubjectRDN(cseqVSEnrollCN);
	
	//Create the Subject object
	CSequence cseqSubject(csetSubjectRDN);


	/*
		Create a SubjectPublicKeyInfo object defined as
		SubjectPublicKeyInfo ::= SEQUENCE {  
									algorithm AlgorithmIdentifier,
									subjectPublicKey BIT STRING 
								 }
		AlgorithmIdentifier ::= SEQUENCE {  
									algorithm OBJECT IDENTIFIER,
									parameters ANY DEFINED BY ALGORITHM OPTIONAL 
								}

		where subjectPublicKey is the public key sequence encoded as a bit string.
		The rsa public key sequence is defined as follows
		RSAPublicKey ::= SEQUENCE {  
							 modulus INTEGER, -- n
							 publicExponent INTEGER -- e 
						 }

		The subjectPublicKeyInfo object in our case looks like this
		subjectPublicKeyInfo = SEQUENCE {
									SEQUENCE {
										OBJECT IDENTIFIER rsaEncryption(1 2 840 113549.1.1.1)
										NULL
									}
									BIT STRING
										-- contains an object of type RSAPublicKey
								}

	*/

	//Create the object identifier object for the rsaEncryption algorithm
	char szRSAEncObjId[] = "1.2.840.113549.1.1.1";
	CObjectIdentifier cobjidRSAEnc(strlen(szRSAEncObjId), (PBYTE)szRSAEncObjId);

	//Create a null object
	CNull cnullObj;

	//Create the sequence for the alogrithm identifier.
	CBaseDERCollection cbdcAlgId;
	cbdcAlgId = cobjidRSAEnc + cnullObj;
	CSequence cseqAlgId(cbdcAlgId);


	//Create the modulus integer
	CMyUniversalInteger cmyuiPubKeyMod(rsakeyPubKey->modulus.len, (PBYTE)rsakeyPubKey->modulus.data);

	//Create the publicExponent integer
	CMyUniversalInteger cmyuiPubKeyExp(rsakeyPubKey->exponent.len, (PBYTE)rsakeyPubKey->exponent.data);

	//Create the sequence for the rsa public key
	CBaseDERCollection cbdcRSAPubKey;
	cbdcRSAPubKey = cmyuiPubKeyMod + cmyuiPubKeyExp;
	CSequence cseqRSAPubKey(cbdcRSAPubKey);

	//Create a bit string containing the public key sequnce
	CMyBitString bsmyRSAPubKey(0,cseqRSAPubKey.BaseDERBlob->cbData,cseqRSAPubKey.BaseDERBlob->pbData);


	//Create the sequence for the subject public key info
	CBaseDERCollection cbdcSubjPubKeyInfo;
	cbdcSubjPubKeyInfo = cseqAlgId + bsmyRSAPubKey;
	CSequence cseqSubjPubKeyInfo(cbdcSubjPubKeyInfo);

	

	/* Create the attributes of type Attributes. We always create the attributes as below. This
	indicates that we are requesting a cert with the following cert extensions. The cert extensions
	we request are the key usage and the enhanced key usage.
		[0] {
			SEQUENCE {
				OBJECT IDENTIFIER certExtensions (1 3 6 1 4 1 311 2 1 14)
				SET {
					SEQUENCE {
						SEQUENCE {
							OBJECT IDENTIFIER keyUsage ( 2 5 29 15)
							BOOLEAN TRUE
							OCTET STRING
								03 02 01 38
									-- This a bit string which 
									-- specifies the key usage defined as a bit mask. 38 stand for 
									-- key encipherment, data encipherment and key exchange 
									-- C0 stands for digital signature and non repudiation.
							}
						SEQUENCE {
							OBJECT IDENTIFER enhKeyUsage (2 5 29 37)
							OCTET STRING
								30 0A 06 08 2B 06 01 05 05 07 03 02
									-- This is a sequnece of object identifier, identifying the
									-- extended key usage. The object identifier encoded above is
									-- 1.3.6.1.5.5.7.3.2 which stands for client auth. Note that
									-- this extension is passed to Xenroll while calling createpkcs10
							}
						}
					}
				}
			}
	*/

	//Create the certExtensions object identifier
	char szCertExtensionsOID[] = "1.3.6.1.4.1.311.2.1.14";
	CObjectIdentifier cobjidCertExtensions(strlen(szCertExtensionsOID), (PBYTE)szCertExtensionsOID);

	//Create the object identifier for the keyUsage
	char szKeyUsageOID[] = "2.5.29.15";
	CObjectIdentifier cobjidKeyUsage(strlen(szKeyUsageOID), (PBYTE)szKeyUsageOID);

	//Create a boolean
	CBoolean cboolTrue(true);

	// Create the octet string specifying the key usage
	// For now we will hard code the key usage octet string to contain an asn.1 bit string encoding of 0011100 
	// (which stands for key encipherment|data encipherment|key agreement.
	// Later when we want to support signature keys we will create the octet string so that it 
	// contains an asn.1 encoded bit string representing  1100000 (which stands for digital 
	// signature|non-repudiation)

	BYTE byteKeyExchangeBitString[] = {0x38, 0x01, 0x02, 0x03} ; //Note this is the reverse of the acutal encoding
																 // becuase COctetString reverses the inputted data
																 // 03 represents bit string; 02 is the lenght of the
																 // encoded data; 01 is the number of unused bits and
																 // 38 is the actual string of bits.
	COctetString cosKeyUsage(4, (PBYTE)byteKeyExchangeBitString);

	//Create the sequence for the key usage
	CBaseDERCollection cbdcKeyUsage;
	cbdcKeyUsage = cobjidKeyUsage + cboolTrue + cosKeyUsage;
	CSequence cseqKeyUsage(cbdcKeyUsage);

	//Create the object identifier enhanced key usage
	char szEnhKeyUsage[] = "2.5.29.37";
	CObjectIdentifier cobjidEnhKeyUsage(strlen(szEnhKeyUsage), (PBYTE)szEnhKeyUsage);

	//Create the octet string representing the enhanced key usage
	//For now we will hard code this octet string to contain an asn.1 encoding of a sequnece
	//containing the OID for clientAuth(1.3.6.1.5.5.7.3.2).
	//Later the OID to be inserted in the sequence will be passed as a parameter.
	BYTE byteSeqOfClientAuthOID[] = {0x02, 0x03, 0x07, 0x05, 0x05, 0x01, 0x06, 0x2b, 0x08, 0x06, 0x0a, 0x30};
										//This is specified in the reverse order since COctetString reverses
										//the inputted data. So 0x30 represents a sequence; 0x0a is the length
										//0x06 represents the OID type; 0x08 represents the length of the OID
										//and the remaining bytes represent the OID value.
	COctetString cosEnhKeyUsage(12, (PBYTE)byteSeqOfClientAuthOID);
	
	//Create the sequence for the enhanced key usage
	CBaseDERCollection cbdcEnhKeyUsage;
	cbdcEnhKeyUsage = cobjidEnhKeyUsage + cosEnhKeyUsage;
	CSequence cseqEnhKeyUsage(cbdcEnhKeyUsage);

	//Enclose the key usage and the enh key usage sequences in a key usage cert extension sequence
	CBaseDERCollection cbdcKeyUsageCertExtension;
	cbdcKeyUsageCertExtension = cseqKeyUsage + cseqEnhKeyUsage;
	CSequence cseqKeyUsageCertExtension(cbdcKeyUsageCertExtension);

	//Enclose the key usage cert extension sequence in a set of cert extension
	CSet csetCertExtensions(cseqKeyUsageCertExtension);
	
	//Create a sequence representing the cert extensions attribute
	CBaseDERCollection cbdcCertExtensionsAttr;
	cbdcCertExtensionsAttr = cobjidCertExtensions + csetCertExtensions; 
	CSequence cseqCertExtesionAttr(cbdcCertExtensionsAttr);

	//Create the implicity tagged collection of attributes
	CTaggedValue ctvAttributes(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(cseqCertExtesionAttr.BaseDERBlob));

	
	/* Create an object of type CertificationRequestInfo defined as
	SEQUENCE {
		version Version
		subject Name
		subjectPublicKeyInfo	SubjectPublicKeyInfo
		attributes [0] IMPLICIT Attributes
	}
	*/
	CBaseDERCollection cbdcCertRequestInfo;
	cbdcCertRequestInfo = cuiVersion + cseqSubject + cseqSubjPubKeyInfo + ctvAttributes;
	CSequence cseqCertRequestInfo(cbdcCertRequestInfo);


	/*Create the signature object defined below
		Signature = BIT STRING 
		The signature contains a bit string encoding of the an encrypted sha1 hash
		object. The sha1 hash object is encrypted using the private key.
		The sha1 hash object is defined as follows -
		SEQUENCE {
				SEQUENCE {
					OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
					NULL
					}
				OCTET STRING
					-- 20 byte octet string representing the hash value
	*/
	
	//Hash the data
	BYTE byteSha1Hash[20];
	BYTE* pbyteSignature;
	unsigned int cbyteSignature;

	if(HashData((PBYTE)cseqCertRequestInfo.BaseDERBlob->pbData ,cseqCertRequestInfo.BaseDERBlob->cbData, byteSha1Hash))
	{
		retVal = VS_HASH_ERR;
	}
	else
	{
		//Create the octet string encoding for the hash value
		CMyOctetString myosSha1Hash(SHA1HASH_SIZE, byteSha1Hash);

		//Create the sha1 algorithm identifier sequence
		char szSha1OID[] = "1.3.14.3.2.26";
		CObjectIdentifier cobjidSha1(strlen(szSha1OID),(PBYTE)szSha1OID);
		cbdcAlgId = cobjidSha1 + cnullObj ;
		cseqAlgId = cbdcAlgId;

		
		//Create the sha1 hash object sequence
		CBaseDERCollection cbdcSha1Hash;
		cbdcSha1Hash = cseqAlgId + myosSha1Hash;
		CSequence cseqSha1Hash(cbdcSha1Hash);

		//Encrypt this sha1 hash sequence to obtain the signature.
		cbyteSignature = rsakeyPrivKey->modulus.len;
		pbyteSignature = (BYTE*)malloc(sizeof(BYTE)*cbyteSignature);
		if(!pbyteSignature)
		{
			retVal = VS_MEM_ERR;
		}
		else
		{
			if(EncryptData(rsakeyPrivKey,cseqSha1Hash.BaseDERBlob->pbData ,cseqSha1Hash.BaseDERBlob->cbData ,pbyteSignature,&cbyteSignature))
			{
				retVal = VS_ENC_ERR;
			}
			else
			{
				/* Create the Certification Request object defined as 
				CertificationRequest := SEQUENCE {
												certificationRequestInfo CertificationRequestInfo
												signatureAlgorithm SignartureAlgorithmIdentifier,
												signature Signature
												}

				AlgorithmIdentifier := SEQUENCE {  
									algorithm OBJECT IDENTIFIER,
									parameters ANY DEFINED BY ALGORITHM OPTIONAL 
								}

				Signature := BIT STRING

				*/

				//Create the object identifier object for the sha1WithrsaEncryption(1.3.14.3.2.29) algorithm
				char szSha1WithRSAEncObjId[] = "1.3.14.3.2.29";
				CObjectIdentifier cobjidSha1WithRSAEnc(strlen(szSha1WithRSAEncObjId), (PBYTE)szSha1WithRSAEncObjId);
				
				//Create the algorithm identifier sequence
				cbdcAlgId = cobjidSha1WithRSAEnc + cnullObj;
				cseqAlgId = cbdcAlgId;

				//Create the bit string for the signature
				CMyBitString mybsSignature(0,cbyteSignature, pbyteSignature);

				//create the certification request object - this is the final p10
				CBaseDERCollection cbdcCertificationReq;
				cbdcCertificationReq = cseqCertRequestInfo + cseqAlgId + mybsSignature;
				CSequence cseqCertificationReq(cbdcCertificationReq );

				FILE* fp;
				fp = (FILE*)fopen("temp.bin","wb");
				for(int i=0;i<cseqCertificationReq.BaseDERBlob->cbData; ++i)
				{
					fprintf(fp,"%c",cseqCertificationReq.BaseDERBlob->pbData[i]);
				}
				fclose(fp);
				

			}

			free(pbyteSignature);
		}
	}

	
	return retVal;
}

int CreatePKCS7(PBYTE pbSignature, unsigned int nSignatureSize, PBYTE pbCert, unsigned int nCertSize, PBYTE* ppbSignedPKCS7, unsigned int* pnSignedPKCS7Size)
{
	int retVal= 0;
	
	//Obtain the (DER Encoded) issuer dn sequence of the cert
	CSequence cseqIssuer;

	if(GetDERIssuerDN(pbCert, nCertSize, cseqIssuer))
	{
		retVal = VS_DER_ISS_DN_ACC_ERR;
	}
	else
	{
		//Obtain the (DER Encoded) serial number of the cert
		CUniversalInteger cuiSerialNum;

		if(GetDERSerNum(pbCert, nCertSize, cuiSerialNum))
		{
			retVal = VS_DER_SER_NUM_ACC_ERR;
		}
		else
		{
			/* Create the following object 
				IssuerAndSerialNumber := SEQUENCE {
													issuer	Name,
													serialNumber CertifcateSerialNumber
										  }
			*/
			CBaseDERCollection cbdcIssSer;
			cbdcIssSer = cseqIssuer + cuiSerialNum;
			CSequence cseqIssSer(cbdcIssSer);

			/** Create a digest algorithm object for sha1 hash which looks as follows -
			SEQUENCE {
						OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
						NULL
					}

			This is the digestAlgorithm object
			**/
			
			//Create the sha1 object identifier
			char szSha1OID[] = "1.3.14.3.2.26";
			CObjectIdentifier cobjidSha1(strlen(szSha1OID),(PBYTE)szSha1OID);

			//Create a null object
			CNull cnullObj;
			
			//Create the sha1 algorithm identifier
			CBaseDERCollection cbdcAlgId;
			cbdcAlgId = cobjidSha1 + cnullObj ;
			CSequence cseqDigestAlg(cbdcAlgId);


			/** Create a rsa encryption algorithm object which looks as follows -
			SEQUENCE {
						OBJECT IDENTIFIER rsaEncryption (1.2.840.113549.1.1.1)
						NULL
					}
			This is the digest
			**/

			//Create an object identifier for the OID 1.2.840.113549.1.1.1
			char szRSAEncObjId[] = "1.2.840.113549.1.1.1";
			CObjectIdentifier cobjidRSAEncObjId(strlen(szRSAEncObjId),(BYTE*)szRSAEncObjId);

			//Create a sequence containing the above OID and null object
			cbdcAlgId = cobjidRSAEncObjId + cnullObj;
			CSequence cseqDigestEncAlg(cbdcAlgId );

			//Create an octet string containing the signature (encryptedDigest).
			CMyOctetString cmyosEncryptedDigest(nSignatureSize, pbSignature);

			/* Create the signer info object which is defined as follows -
			SignerInfo := SEQUENCE {
									version INTEGER,
									issuerAndSerialNumber IssuerAndSerialNumber,
									digestAlgorithm DigestAlgorithmIdentifier,
									digestEncryptionAlgorithm DignestEncryptionAlgorithmIdentifier,
									encryptedDigest EncryptedDigest
						  }
			*/

			BYTE byteVer = 0x01;
			CUniversalInteger cuiVersion(sizeof(BYTE),(BYTE*)&byteVer);

			CBaseDERCollection cbdcSignerInfo;
			cbdcSignerInfo = cuiVersion + cseqIssSer + cseqDigestAlg + cseqDigestEncAlg + cmyosEncryptedDigest;

			CSequence cseqSignerInfo(cbdcSignerInfo);

			/* Create the SignerInfos object defined as
					SignerInfos := CHOICE {
										siSet	SET OF SignerInfo,
										siSequence SEQUENCE OF SignerInfo
									}

					We will choose a set and this set will include only one SignerInfo object created above
			*/
			CBaseDERCollection cbdcSignerInfos;
			cbdcSignerInfos = cseqSignerInfo;
			CSet csetSignerInfos(cbdcSignerInfos);

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
			cbdcDigestAlgorithms = cseqDigestAlg;
			CSet csetDigestAlgorithms(cbdcDigestAlgorithms);


			/*
				Create the content info object defined as 
				ContentInfo := SEQUENCE {
											contentType contentType;
											content [0] EXPLICIT CONTENTS.&Type((Contents)(@contentType)) OPTIONAL
										}
				The specific object we will create is
				SEQUENCE {
							OBJECT IDENTIFIER data (1.2.840.113549.1.7.1)
						 }
							
			*/
			
			char szDataObjId[] = "1.2.840.113549.1.7.1";
			CObjectIdentifier cobjidData(strlen(szDataObjId), (PBYTE)szDataObjId);
			CBaseDERCollection cbdcContentInfo;
			cbdcContentInfo = cobjidData;
			CSequence cseqContentInfo(cbdcContentInfo);

			/*
				Create the cert chain - for now the cert chain will have only one cert - the end cert.
				In the future we can add the intermediate CAs in the chain
			*/
			//Create the BaseDER object for the cert
			CDERBlob cderblobEndCert(nCertSize, pbCert);
			CBaseDER cbasederEndCert(cderblobEndCert);

			CTaggedValue ctvCertChain(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, cbasederEndCert);
			
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
			CBaseDERCollection cbdcSignedData;
			cbdcSignedData = cuiVersion + csetDigestAlgorithms + cseqContentInfo + ctvCertChain + csetSignerInfos;
			CSequence cseqSignedData(cbdcSignedData);

			/* Finally create the signed data pkcs7 which looks like this
				SEQUENCE {
						OBJECT IDENTIFIER signedData (1.2.840.113549.1.7.2)
						[0] {
							signedData
						}
					}
				(Note this an object of type ContentInfo)
			*/
			char szSignedDataObjId[] = "1.2.840.113549.1.7.2";
			CObjectIdentifier cobjidSignedData(strlen(szSignedDataObjId), (PBYTE)szSignedDataObjId);
			
			CTaggedValue ctvSignedDataContent(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(cseqSignedData.BaseDERBlob));

			cbdcContentInfo = cobjidSignedData + ctvSignedDataContent;

			cseqContentInfo = cbdcContentInfo;
			
			FILE* fp;
			fp = (FILE*)fopen("temppkcs7.bin","wb");
			for(int i=0;i<cseqContentInfo.BaseDERBlob->cbData; ++i)
			{
				fprintf(fp,"%c",cseqContentInfo.BaseDERBlob->pbData[i]);
			}
			fclose(fp);


		}
	}


	return retVal;
}

int GetDERIssuerDN(PBYTE pbCert, unsigned int nCertSize, CSequence& cseqIssuerDN)
{
	//This function will extract a issuer dn from a cert
	//For now we will create a dummy issuer dn sequence

	/*** Create this structure 

	  SET {
		  SEQUENCE {
			OBJECT IDENTIFIER organizationName (2 5 4 10)
			Printable String 'VeriSign'
			}
		  }

			-- Call this SET1

	******/

	//Create a printable string that stores the O of the issuer dn
	char szIssuerO[] = "VeriSign";
	CPrintableString cpsIssuerO(strlen(szIssuerO),(BYTE*)szIssuerO);

	//Create the object identifier for the organization name
	char szIssuerOObjId[] = "2.5.4.10";
	CObjectIdentifier cobjidIssuerO(strlen(szIssuerOObjId),(BYTE*)szIssuerOObjId);

	//Create a collection of the object identifier and the the printable string
	CBaseDERCollection cbdcIssuerO;
	cbdcIssuerO = cobjidIssuerO + cpsIssuerO;

	//Create the sequence for the O of the issuer dn
	CSequence cseqIssuerO(cbdcIssuerO);

	//Put the sequence in the set
	CSet csetIssuerO(cseqIssuerO);
	

	/*** Create this structure 

	  SET {
		  SEQUENCE {
			OBJECT IDENTIFIER organizationUnitName (2 5 4 11)
			Printable String 'VeriSign Class 2 Onsite Individual CA'
			}
		  }
			
			  -- Call this SET2

	******/

	//Create a printable string that stores the O of the issuer dn
	char szIssuerOU[] = "VeriSign Class 2 OnSite Individual CA";
	CPrintableString cpsIssuerOU(strlen(szIssuerOU),(BYTE*)szIssuerOU);

	//Create the object identifier for the organization name
	char szIssuerOUObjId[] = "2.5.4.11";
	CObjectIdentifier cobjidIssuerOU(strlen(szIssuerOUObjId),(BYTE*)szIssuerOUObjId);

	//Create a collection of the object identifier and the the printable string
	CBaseDERCollection cbdcIssuerOU;
	cbdcIssuerOU = cobjidIssuerOU + cpsIssuerOU;

	//Create the sequence for the O of the issuer dn
	CSequence cseqIssuerOU(cbdcIssuerOU);

	//Put this sequence in the set
	CSet csetIssuerOU(cseqIssuerOU);

	
	/*** Create this structure 

	  SEQUENCE {
		SET1
		SET2
		}
			
			  -- Call this SEQ_ISS
	******/

	//Create a collection of the IssuerO set(SET1) and IssuerOU set(SET2)
	CBaseDERCollection cbdcIssuer;
	cbdcIssuer = csetIssuerO + csetIssuerOU;
	
	//Put this collection into a sequence
	cseqIssuerDN = cbdcIssuer;
	
	return 0;

}

int GetDERSerNum(PBYTE pbCert, unsigned int nCertSize, CUniversalInteger& cuiSerNum)
{
	//this function extracts the cert ser num from the cert.
	//For now it contstructs the ser num.
	BYTE byteSerNum[] = {0x2B, 0x60, 0x8B, 0x4E, 0x0F, 0x49, 0xD4, 0x21, 0xAD, 0x0C, 0x27, 0xEC, 0xC8, 0x8A, 0x05, 0x8B};
	unsigned int nSerNumSize = 16;

	CMyUniversalInteger cmyuiSerialNum(16, (PBYTE)byteSerNum);
	cuiSerNum = cmyuiSerialNum;
	return 0;

}
#endif

#if 0
int EncryptRSAData(A_RSA_KEY* RSAKey, unsigned char* plainText, unsigned int plainTextSize, unsigned char* encText, unsigned int* encTextSize)
{
	A_RSA_CTX context;
	unsigned int contextLen = sizeof(A_RSA_CTX);
	unsigned int iters;
	unsigned char* currInBlock;
	unsigned int currInBlockSize;
	unsigned int currOutBlockSize;
	unsigned int i;
	unsigned int nBlockSize;
	unsigned int nBlockSizeNoPad;

	nBlockSize = RSAKey->modulus.len;
	nBlockSizeNoPad = nBlockSize - 11;
	currInBlock = (BYTE*)malloc(sizeof(BYTE)*nBlockSize );

	if(plainTextSize % nBlockSizeNoPad)
	{
		iters = plainTextSize/nBlockSizeNoPad + 1;
	}
	else
	{
		iters = plainTextSize/nBlockSizeNoPad;
	}

	//Check if the output buffer size is sufficient
	if(*encTextSize < (iters*nBlockSize))
	{
		return -1; //output buffer size too small
	}


	//Create the context
	ALG_RSAInit ((A_RSA_CTX *)&context, (A_RSA_KEY *)RSAKey );

	
	for(i=0;i< iters; ++i)
	{
		//Pad the block with 0xff. 
		//The current block is of the format 0x00 0x01 0xFF...0xFF 0x00 data
		//There are atleast 8 bytes of the padding (0xFF)
		memset(currInBlock,0xff,nBlockSize);
		currInBlock[0] = 0;
		currInBlock[1] = 1;

		currInBlockSize = ((i+1)*nBlockSizeNoPad  < plainTextSize ? nBlockSizeNoPad : plainTextSize - (i*nBlockSizeNoPad));
		currInBlock[nBlockSize-currInBlockSize-1] = 0;
		memcpy(currInBlock+(nBlockSize-currInBlockSize),plainText+(nBlockSizeNoPad*i),currInBlockSize);

		//Update
		ALG_RSAUpdate(&context,(encText+(i*nBlockSize)),&currOutBlockSize,nBlockSize,currInBlock,nBlockSize,NULL);

	}


	//Final
	ALG_RSAFinal(&context );

	//Destroy the context
	ALG_RSAContextDestroy (&context);

	*encTextSize = iters * nBlockSize;
	free(currInBlock );

	return 0;

}


int DecryptRSAData(A_RSA_KEY* RSAKey, unsigned char* encText, unsigned int encTextSize, unsigned char* plainText, unsigned int* plainTextSize)
{
	A_RSA_CTX context;
	unsigned int contextLen = sizeof(A_RSA_CTX);
	unsigned int iters;
	unsigned char* currOutBlock;
	unsigned int currOutBlockSize;
	unsigned int i,j;	
	unsigned int nBlockSize;
	unsigned int nBlockSizeNoPad;

	nBlockSize = RSAKey->modulus.len;
	nBlockSizeNoPad = nBlockSize - 11;

	
	if(encTextSize % nBlockSize )
	{
		return -1;  //Error becuase encrypted data is always a multiple of 64 bytes.
	}
	else
	{
		iters = encTextSize/nBlockSize ;
	}

	//Check if the output buffer size is sufficient
	if(*plainTextSize < (iters*nBlockSizeNoPad ))
	{
		return -1; //output buffer size too small
	}


	currOutBlock = (BYTE*)malloc(sizeof(BYTE)*nBlockSize);

	//Create the context
	ALG_RSAInit ((A_RSA_CTX *)&context, (A_RSA_KEY *)RSAKey );

	*plainTextSize = 0;
	for(i=0;i< iters; ++i)
	{
		//Update
		ALG_RSAUpdate(&context,currOutBlock,&currOutBlockSize,nBlockSize,(encText+(i*nBlockSize)),nBlockSize,NULL);
		
		//Make sure that the first 2 bytes are in the correct format
		if(currOutBlock[0] != 0 || currOutBlock[1] != 1 )
			return -1;

		//Make sure that there are atleast 8 bytes of pasdding
		for(j=2;j<10;++j)
		{
			if(currOutBlock[j] != (unsigned char)0xff)
				return -1;
		}

		//Extract the plain text - find out the number of bytes to skip from the beginning
		for(j=10; j< nBlockSize  && currOutBlock[j] != 0;++j);

		j++;

		//Make sure that there is atleast one byte of data.
		if(j== nBlockSize)
			return -1;

		//Now j has the first data byte - copy data into the plain text buffer
		memcpy(plainText+(*plainTextSize),currOutBlock+j,nBlockSize-j);
		*plainTextSize += (nBlockSize-j);
	}


	//Final
	ALG_RSAFinal(&context );

	//Destroy the context
	ALG_RSAContextDestroy (&context);

	return 0;

}
#endif

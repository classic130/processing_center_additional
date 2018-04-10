#ifndef _MYDEFS
#define _MYDEFS

typedef		struct	_myBLOB {
    DWORD		cbData ;
	BYTE		*pbData;
} CRYPT_CONTENT_INFO_BLOB, *PCRYPT_CONTENT_INFO_BLOB,
  CRYPT_MAC_DATA_BLOB, *PCRYPT_MAC_DATA_BLOB, 
  CRYPT_PKCS12_BLOB, *PCRYPT_PKCS12_BLOB,
  CRYPT_PKCS8_BLOB, *PCRYPT_PKCS8_BLOB,
  CRYPT_MYDER_BLOB, *PCRYPT_MYDER_BLOB,
  CRYPT_PRIVATEKEYBLOB, *PCRYPT_PRIVATEKEYBLOB ;

typedef		struct	_PFX {
	DWORD						dwPFXDERlength ;
	DWORD						version ;
	CRYPT_CONTENT_INFO_BLOB		authSafe ;
	CRYPT_MAC_DATA_BLOB			macData ;
} PFX, *PPFX ;


// Stores information from a RSAPrivateKey DER
typedef		struct	_MY_PRIVATEKEYBLOB {
	BLOBHEADER				blobheader ;
	RSAPUBKEY				rsapubkey ;
	DWORD					cbRSAPrivateKeyBlob ;
	PBYTE					pbRSAPrivateKeyBlob ;
	DWORD					version ;				// Stores the Version of RSAPrivateKey as found inside PKCS#8
	CRYPT_MYDER_BLOB		modulus ;
	CRYPT_MYDER_BLOB		prime1 ;
	CRYPT_MYDER_BLOB		prime2 ;
	CRYPT_MYDER_BLOB		exponent1 ;
	CRYPT_MYDER_BLOB		exponent2 ;
	CRYPT_MYDER_BLOB		coefficient ;
	CRYPT_MYDER_BLOB		privateExponent ;
} MY_PRIVATEKEYBLOB, *PMY_PRIVATEKEYBLOB ;

// Valid ASN Types
#define		SEQUENCE				0x30
#define		UNIVERSAL_INTEGER		0x02
#define		INVALID_ASN_TYPE		0x00
#define		OBJECT_IDENTIFIER		0x06
#define		NULL_STUFF				0x05
#define		OCTET_STRING			0x04


// My OIDs
#define		szOID_PKCS8				"1.2.840.113549.1.8"
#define		szOID_PKCS12			"1.2.840.113549.1.12"

#endif

#ifndef _PKCS12DEFINES_H
#define _PKCS12DEFINES_H

#define PKCS12INFO_FILENAME 0x0001
#define PKCS12INFO_B64ENCP12 0x0002
#define PKCS12INFO_BYTE_BLOB_P12 0x0003

#define DWORD_SIZE 4
#define P12_VERSION 3

#define IMPP12_MD2 1
#define IMPP12_MD5 2
#define IMPP12_SHA 3

#define HMAC_KEY_SIZE 20
#define SHA_SIZE_INBYTES 20
#define MD_SIZE_INBYTES 16
#define HASH_BLOCKSIZE_INBYTES 64


#define ID_ENCKEY 1
#define ID_IV 2
#define ID_HMAC 3

#define ID_40BIT_RC2CBC 1
#define ID_3DES 2 

#define RC2CBC_40BIT_KEYSIZE 5
#define RC2CBC_IVSIZE 8
#define DES3_KEYSIZE 24
#define DES3_IVSIZE 8

#define szOID_PBE_SHA_40RC2CBC "1.2.840.113549.1.12.1.6"
#define szOID_PBE_SHA_3KEY_3DES "1.2.840.113549.1.12.1.3"

#define szOID_P12_BAGTYPE_SHRP8 "1.2.840.113549.1.12.10.1.2" 
#define szOID_P12_BAGTYPE_CERT "1.2.840.113549.1.12.10.1.3" 
#define szOID_X509_CERT "1.2.840.113549.1.9.22.1" 


#endif

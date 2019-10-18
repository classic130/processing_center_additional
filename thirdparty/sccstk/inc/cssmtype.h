/* SCCSID: inc/cssmtype.h, dss_cdsa_fwk, fwk_rel1a, dss_cdsa_970916 1.28 9/16/97 16:30:38 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * Copyright (c) 1995, 1996, 1997 Intel Corporation. All rights reserved.
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _CSSMTYPE_H
#define _CSSMTYPE_H

#include "cssmdefs.h"

/* Operating System Dependent Primitive Declarations */

#if defined (WIN32)

#define CSSMAPI __stdcall

#elif defined (WIN31)

#ifndef PASCAL
#define PASCAL __stdcall
#endif
#define CSSMAPI PASCAL

#elif defined (UNIX) 

#define CSSMAPI
#define CALLBACK

#endif

/* Basic Types */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef short sint16;
typedef unsigned int uint32;
typedef int sint32;

#if defined (WIN32)

#if defined (_WINDOWS)

#include <windows.h>

#endif /* defined (_WINDOWS) */

/* Thread types */
#define CSSM_THREAD __declspec(thread);

#endif /* defined(WIN32) */

typedef uint32 CSSM_HANDLE, *CSSM_HANDLE_PTR;
typedef uint32 CSSM_TP_HANDLE;    /* Trust Policy Handle */
typedef uint32 CSSM_CL_HANDLE;    /* Certificate Library Handle */
typedef uint32 CSSM_DL_HANDLE;    /* Database Library Handle */
typedef uint32 CSSM_DB_HANDLE;    /* Database Handle */
typedef uint32 CSSM_CC_HANDLE;    /* Cryptographic Context Handle */
typedef uint32 CSSM_CSP_HANDLE;   /* Cryptographic Service Provider Handle */
typedef uint32 CSSM_MODULE_HANDLE, *CSSM_MODULE_HANDLE_PTR; /* Service provider
                                                            Handle*/
#ifdef KEY_RECOVERY
#define MAXPOLICYLEN 128
typedef uint32 CSSM_KRSP_HANDLE;  /* Key Recovery Service Provider Handle */
typedef uint32 CSSM_KRC_HANDLE;      /* Key Recovery Context Handle */
#endif

#define CSSM_INVALID_HANDLE         (0)

typedef uint32 CSSM_TP_ACTION;

typedef enum cssm_tp_stop_on {
    CSSM_TP_STOP_ON_POLICY = 0,
    CSSM_TP_STOP_ON_NONE = 1,
    CSSM_TP_STOP_ON_FIRST_PASS = 2,
    CSSM_TP_STOP_ON_FIRST_FAIL = 3
} CSSM_TP_STOP_ON;

typedef uint32 CSSM_EVENT_TYPE, *CSSM_EVENT_TYPE_PTR;

#define CSSM_EVENT_ATTACH          (0)
#define CSSM_EVENT_DETACH          (1)
#define CSSM_EVENT_INFOATTACH      (2)
#define CSSM_EVENT_INFODETACH      (3)
#define CSSM_EVENT_CREATE_CONTEXT  (4)
#define CSSM_EVENT_DELETE_CONTEXT  (5)
#define CSSM_EVENT_UPDATE_CONTEXT  (6)

typedef uint32 CSSM_KEY_TYPE, *CSSM_KEY_TYPE_PTR;

typedef uint32 CSSM_BOOL;

#define CSSM_TRUE   1
#define CSSM_FALSE  0

typedef enum cssm_return {
    CSSM_OK = 0,
    CSSM_FAIL = -1
} CSSM_RETURN;

typedef struct cssm_guid {
    uint32 Data1;
    uint16 Data2;
    uint16 Data3;
    uint8 Data4[8];
} CSSM_GUID, *CSSM_GUID_PTR;

typedef struct cssm_error {
    uint32 error;
    CSSM_GUID guid;
} CSSM_ERROR, *CSSM_ERROR_PTR;


/*
    CSSM_VERSION
*/
typedef struct cssm_version {
    uint32 Major;
    uint32 Minor;
} CSSM_VERSION, *CSSM_VERSION_PTR;

typedef enum cssm_revoke_reason { 
    CSSM_REVOKE_CUSTOM = 0,
    CSSM_REVOKE_UNSPECIFIC = 1,
    CSSM_REVOKE_KEYCOMPROMISE = 2,
    CSSM_REVOKE_CACOMPROMISE = 3,
    CSSM_REVOKE_AFFILIATIONCHANGED = 4,
    CSSM_REVOKE_SUPERCEDED = 5,
    CSSM_REVOKE_CESSATIONOFOPERATION = 6,
    CSSM_REVOKE_CERTIFICATEHOLD = 7,
    CSSM_REVOKE_CERTIFICATEHOLDRELEASE = 8,
    CSSM_REVOKE_REMOVEFROMCRL = 9
} CSSM_REVOKE_REASON;

typedef struct cssm_data {
    uint32 Length;            /* in bytes */
    uint8 *Data;
} CSSM_DATA, *CSSM_DATA_PTR;

#define CSSM_MODULE_STRING_SIZE  64
typedef char CSSM_STRING [CSSM_MODULE_STRING_SIZE + 4];

/* Multi service modules */
typedef uint32 CSSM_SERVICE_MASK;
typedef CSSM_SERVICE_MASK CSSM_SERVICE_TYPE;

#define CSSM_SERVICE_CSSM         0x1
#define CSSM_SERVICE_CSP          0x2
#define CSSM_SERVICE_DL           0x4
#define CSSM_SERVICE_CL           0x8
#define CSSM_SERVICE_TP           0x10
#ifdef KEY_RECOVERY
#define CSSM_SERVICE_KR           0x20
#define CSSM_SERVICE_LAST CSSM_SERVICE_KR
#else
#define CSSM_SERVICE_LAST CSSM_SERVICE_TP
#endif

#define CSSM_DB_DATASTORES_UNKNOWN (0xFFFFFFFF)
#define CSSM_ALL_SUBSERVICES (0xFFFFFFFF)

/* indicates level of information disclosure by GetModuleInfo func */
typedef enum cssm_info_level {
    CSSM_INFO_LEVEL_MODULE    = 0,
            /* values from XXinfo struct */
    CSSM_INFO_LEVEL_SUBSERVICE    = 1,
            /* values from XXinfo and XXsubservice struct */
    CSSM_INFO_LEVEL_STATIC_ATTR    = 2,
            /* values from XXinfo and XXsubservice and
               all static-valued attributes of a subservice */
    CSSM_INFO_LEVEL_ALL_ATTR    = 3
            /* values from XXinfo and XXsubservice and
               all attributes, static and dynamic,
               of a subservice */
} CSSM_INFO_LEVEL;

/*  CSSM_USER_AUTHENTICATION_MECHANISM  */ 
typedef enum cssm_user_authentication_mechanism {
    CSSM_AUTHENTICATION_NONE = 0,
    CSSM_AUTHENTICATION_CUSTOM = 1,
    CSSM_AUTHENTICATION_PASSWORD = 2,
    CSSM_AUTHENTICATION_USERID_AND_PASSWORD = 3,
    CSSM_AUTHENTICATION_CERTIFICATE_AND_PASSPHRASE = 4,
    CSSM_AUTHENTICATION_LOGIN_AND_WRAP = 5
} CSSM_USER_AUTHENTICATION_MECHANISM;

typedef CSSM_DATA_PTR (CSSMAPI *CSSM_CALLBACK) (void *allocRef, uint32 ID);

typedef struct cssm_crypto_data {
    CSSM_DATA_PTR Param;
    CSSM_CALLBACK Callback;
    uint32 CallbackID;
} CSSM_CRYPTO_DATA, *CSSM_CRYPTO_DATA_PTR;

/*  CSSM_USER_AUTHENTICATION  */
typedef struct cssm_user_authentication {
    CSSM_DATA_PTR Credential;      /* a cert, a shared secret, other */
    CSSM_CRYPTO_DATA_PTR MoreAuthenticationData;
} CSSM_USER_AUTHENTICATION, *CSSM_USER_AUTHENTICATION_PTR;

typedef CSSM_DATA CSSM_OID, *CSSM_OID_PTR;

typedef struct cssm_list_item {
    CSSM_GUID GUID;
    char *Name;
} CSSM_LIST_ITEM, *CSSM_LIST_ITEM_PTR;

typedef struct cssm_list {
    uint32 NumberItems;
    CSSM_LIST_ITEM_PTR Items;
} CSSM_LIST, *CSSM_LIST_PTR;

typedef struct cssm_name_list {
    uint32 NumStrings;
    char** String;
} CSSM_NAME_LIST, *CSSM_NAME_LIST_PTR;


typedef uint32 CSSM_CERT_TYPE,*CSSM_CERT_TYPE_PTR;
/* bit masks for supported cert types */
#define	CSSM_CERT_UNKNOWN		0x00000000
#define	CSSM_CERT_X_509v1		0x00000001
#define CSSM_CERT_X_509v2		0x00000002
#define CSSM_CERT_X_509v3		0x00000004
#define CSSM_CERT_Fortezza		0x00000008
#define CSSM_CERT_PGP			0x00000010
#define CSSM_CERT_SPKI			0x00000020
#define CSSM_CERT_SDSIv1		0x00000040
#define CSSM_CERT_Intel			0x00000080
#define CSSM_CERT_ATTRIBUTE_BER 0x00000100
#define CSSM_CERT_X509_CRL		0x00000200
#define CSSM_CERT_LAST			0x00007fff


/* Applications wishing to define their own custom certificate 
 * type should create a random uint32 whose value is greater than 
 * the CSSM_CL_CUSTOM_CERT_TYPE */
#define CSSM_CL_CUSTOM_CERT_TYPE  0x08000 

typedef struct cssm_certgroup {
    uint32 NumCerts;
    CSSM_DATA_PTR CertList;
    void* reserved;
} CSSM_CERTGROUP, *CSSM_CERTGROUP_PTR;

typedef struct cssm_dl_db_handle {
    CSSM_DL_HANDLE DLHandle;
    CSSM_DB_HANDLE DBHandle;
} CSSM_DL_DB_HANDLE, *CSSM_DL_DB_HANDLE_PTR;

typedef struct cssm_dl_db_list {
    uint32 NumHandles;
    CSSM_DL_DB_HANDLE_PTR DLDBHandle;
} CSSM_DL_DB_LIST, *CSSM_DL_DB_LIST_PTR;

/*  CSSM_DB_ATTRIBUTE_NAME_FORMAT  */ 
typedef enum cssm_db_attribute_name_format {
    CSSM_DB_ATTRIBUTE_NAME_AS_STRING = 0, 
    CSSM_DB_ATTRIBUTE_NAME_AS_OID = 1,
    CSSM_DB_ATTRIBUTE_NAME_AS_NUMBER = 2
} CSSM_DB_ATTRIBUTE_NAME_FORMAT, *CSSM_DB_ATTRIBUTE_NAME_FORMAT_PTR;

/*  CSSM_DB_ATTRIBUTE_INFO  */
typedef struct cssm_db_attribute_info {
    CSSM_DB_ATTRIBUTE_NAME_FORMAT AttributeNameFormat; 
    union {
        char * AttributeName;             /* eg. "record label" */
        CSSM_OID AttributeID;             /* eg. CSSMOID_RECORDLABEL */
        uint32 AttributeNumber;
    };
} CSSM_DB_ATTRIBUTE_INFO, *CSSM_DB_ATTRIBUTE_INFO_PTR;

/*  CSSM_DB_ATTRIBUTE_DATA  */
typedef struct cssm_db_attribute_data {
    CSSM_DB_ATTRIBUTE_INFO Info; 
    CSSM_DATA Value;
} CSSM_DB_ATTRIBUTE_DATA, *CSSM_DB_ATTRIBUTE_DATA_PTR;


/*  *****  Record-related structures  *****  */

/*  CSSM_DB_RECORDTYPE  */
typedef enum cssm_db_recordtype {
    CSSM_DL_DB_RECORD_GENERIC = 0,
    CSSM_DL_DB_RECORD_CERT = 1,
    CSSM_DL_DB_RECORD_CRL = 2,
    CSSM_DL_DB_RECORD_PUBLIC_KEY = 3,
    CSSM_DL_DB_RECORD_PRIVATE_KEY = 4,
    CSSM_DL_DB_RECORD_SYMMETRIC_KEY = 5,
    CSSM_DL_DB_RECORD_POLICY = 6
} CSSM_DB_RECORDTYPE;

/*  CSSM_DB_XXXRECORD_SEMANTICS  */
/* (XXX can be Cert, CRL, Policy, etc.)  */
/* It is expected that there will be certain semantic types associated
   with certs, CRLs, policies, etc.
   Each type is expected to have a bit mask which is capable of describing
   general information about how the record should be used.  CRL, KEY, 
   and POLICY semantic bit masks will be defined as needed .  */

/*  CSSM_DB_CERTRECORD_SEMANTICS  */
/*  Optional semantic information associated with certificate records.  */
#define CSSM_DB_CERT_USE_ROOT    0x00000001 /* a self-signed root cert */ 
#define CSSM_DB_CERT_USE_TRUSTED 0x00000002 /* re-issued locally (DL must protect?) */
#define CSSM_DB_CERT_USE_SYSTEM  0x00000004 /* contains CSSM system cert */ 
#define CSSM_DB_CERT_USE_OWNER   0x00000008 /* private key is owned by the sys's user */
#define CSSM_DB_CERT_USE_REVOKED 0x00000010 /* revoked cert - used w\ CRL APIs */
#define CSSM_DB_CERT_SIGNING     0x00000011 /* use cert for signing only */ 
#define CSSM_DB_CERT_PRIVACY     0x00000012 /* use cert for encryption only */

/*  CSSM_DB_RECORD_ATTRIBUTE_INFO  */
typedef struct cssm_db_record_attribute_info {
    CSSM_DB_RECORDTYPE DataRecordType;
    uint32 NumberOfAttributes; 
    CSSM_DB_ATTRIBUTE_INFO_PTR AttributeInfo;
} CSSM_DB_RECORD_ATTRIBUTE_INFO, *CSSM_DB_RECORD_ATTRIBUTE_INFO_PTR;

/*  CSSM_DB_RECORD_ATTRIBUTE_DATA  */
typedef struct cssm_db_record_attribute_data {
    CSSM_DB_RECORDTYPE DataRecordType;
    uint32 SemanticInformation; 
    uint32 NumberOfAttributes; 
    CSSM_DB_ATTRIBUTE_DATA_PTR AttributeData;
} CSSM_DB_RECORD_ATTRIBUTE_DATA, *CSSM_DB_RECORD_ATTRIBUTE_DATA_PTR;

/*  CSSM_DB_RECORD_PARSING_FUNCTION_TABLE  */ 
typedef struct cssm_db_record_parsing_fntable {
    CSSM_DATA_PTR (CSSMAPI *RecordGetFirstFieldValue) 
                                           (CSSM_HANDLE Handle,
                                            CSSM_DB_RECORDTYPE RecordType,
                                            const CSSM_DATA_PTR Data,
                                            const CSSM_OID_PTR DataField,
                                            CSSM_HANDLE_PTR ResultsHandle,
                                            uint32 *NumberOfMatchedFields);
    CSSM_DATA_PTR (CSSMAPI *RecordGetNextFieldValue) 
                                           (CSSM_HANDLE Handle,
                                            CSSM_HANDLE ResultsHandle);
    CSSM_RETURN (CSSMAPI *RecordAbortQuery)
                                       (CSSM_HANDLE Handle,
                                        CSSM_HANDLE ResultsHandle);
} CSSM_DB_RECORD_PARSING_FNTABLE, *CSSM_DB_RECORD_PARSING_FNTABLE_PTR;

/* CSSM_DB_PARSING_INFO */
typedef struct cssm_db_parsing_module_info {
    CSSM_DB_RECORDTYPE RecordType;
    CSSM_GUID Module;
} CSSM_DB_PARSING_MODULE_INFO, *CSSM_DB_PARSING_MODULE_INFO_PTR;

/*  CSSM_DB_INDEX_TYPE  */
typedef enum cssm_db_index_type {
    CSSM_DB_INDEX_UNIQUE = 0,
    CSSM_DB_INDEX_NONUNIQUE = 1
} CSSM_DB_INDEX_TYPE;

/*  CSSM_DB_INDEXED_DATA_LOCATION  */ 
typedef enum cssm_db_indexed_data_location {
    CSSM_DB_INDEX_ON_UNKNOWN = 0,
    CSSM_DB_INDEX_ON_ATTRIBUTE = 1,
    CSSM_DB_INDEX_ON_RECORD = 2
} CSSM_DB_INDEXED_DATA_LOCATION;

/*  CSSM_DB_INDEX_INFO  */
typedef struct cssm_db_index_info {
    CSSM_DB_INDEX_TYPE IndexType; 
    CSSM_DB_INDEXED_DATA_LOCATION IndexedDataLocation; 
    CSSM_DB_ATTRIBUTE_INFO Info;
} CSSM_DB_INDEX_INFO, *CSSM_DB_INDEX_INFO_PTR;

/*  CSSM_DB_UNIQUE_RECORD  */
typedef struct cssm_db_unique_record {
    CSSM_DB_INDEX_INFO RecordLocator; 
    CSSM_DATA RecordIdentifier;
} CSSM_DB_UNIQUE_RECORD, *CSSM_DB_UNIQUE_RECORD_PTR;

/*  CSSM_DB_RECORD_INDEX_INFO  */
typedef struct cssm_db_record_indexinfo {
    CSSM_DB_RECORDTYPE DataRecordType; 
    uint32 NumberOfIndexes; 
    CSSM_DB_INDEX_INFO_PTR IndexInfo;
} CSSM_DB_RECORD_INDEX_INFO, *CSSM_DB_RECORD_INDEX_INFO_PTR;


/*  CSSM_DB_ACCESS_TYPE  */
typedef struct cssm_db_access_type {
    CSSM_BOOL ReadAccess;
    CSSM_BOOL WriteAccess;
    CSSM_BOOL PrivilegedMode; /* versus user mode */
    CSSM_BOOL Asynchronous;   /* versus synchronous */
} CSSM_DB_ACCESS_TYPE, *CSSM_DB_ACCESS_TYPE_PTR;

/*  CSSM_DBINFO  */
typedef struct cssm_dbInfo {
/* meta information about each record type stored in this data store 
   including meta information about record attributes and indexes */
    uint32 NumberOfRecordTypes;
    CSSM_DB_PARSING_MODULE_INFO_PTR DefaultParsingModules;
    CSSM_DB_RECORD_ATTRIBUTE_INFO_PTR RecordAttributeNames;
    CSSM_DB_RECORD_INDEX_INFO_PTR RecordIndexes;

    /* access restrictions for opening this data store */
    CSSM_USER_AUTHENTICATION_MECHANISM AuthenticationMechanism;

    /* transparent integrity checking options for this data store */
    CSSM_BOOL RecordSigningImplemented;
    CSSM_DATA SigningCertificate;
    CSSM_GUID SigningCsp;

    /* additional information */
    CSSM_BOOL IsLocal;
    char *AccessPath;           /* URL, dir path, etc */
    void *Reserved;
} CSSM_DBINFO, *CSSM_DBINFO_PTR;


/*  CSSM_DB_OPERATOR  */
typedef enum cssm_db_operator {
    CSSM_DB_EQUAL = 0,
    CSSM_DB_NOT_EQUAL = 1,
    CSSM_DB_APPROX_EQUAL = 2,
    CSSM_DB_LESS_THAN = 3,
    CSSM_DB_GREATER_THAN = 4,
    CSSM_DB_EQUALS_INITIAL_SUBSTRING = 5,
    CSSM_DB_EQUALS_ANY_SUBSTRING = 6,
    CSSM_DB_EQUALS_FINAL_SUBSTRING = 7,
    CSSM_DB_EXISTS = 8
} CSSM_DB_OPERATOR, *CSSM_DB_OPERATOR_PTR;

/*  CSSM_DB_CONJUNCTIVE  */
typedef enum cssm_db_conjunctive{
    CSSM_DB_NONE = 0,
    CSSM_DB_AND = 1,
    CSSM_DB_OR = 2
} CSSM_DB_CONJUNCTIVE, *CSSM_DB_CONJUNCTIVE_PTR;

/* CSSM_SELECTION_PREDICATE  */
typedef struct cssm_selection_predicate {
    CSSM_DB_OPERATOR DbOperator;
    CSSM_DB_ATTRIBUTE_DATA Attribute;
} CSSM_SELECTION_PREDICATE, *CSSM_SELECTION_PREDICATE_PTR;

#define CSSM_QUERY_TIMELIMIT_NONE   0
#define CSSM_QUERY_SIZELIMIT_NONE   0

/*  CSSM_QUERY_LIMITS  */
typedef struct cssm_query_limits {
    uint32 TimeLimit;         /* in seconds */
    uint32 SizeLimit;         /* max. number of records to return */
} CSSM_QUERY_LIMITS, *CSSM_QUERY_LIMITS_PTR;

typedef uint32 CSSM_QUERY_FLAGS;

#define CSSM_QUERY_RETURN_DATA  0x1  /* On = Output in common data format
                                        Off = Output in DL native format */

/*  CSSM_QUERY  */
typedef struct cssm_query {
    CSSM_DB_RECORDTYPE RecordType;
    CSSM_DB_CONJUNCTIVE Conjunctive;
    uint32 NumSelectionPredicates;
    CSSM_SELECTION_PREDICATE_PTR SelectionPredicate;
    CSSM_QUERY_LIMITS QueryLimits;
    CSSM_QUERY_FLAGS QueryFlags;
} CSSM_QUERY, *CSSM_QUERY_PTR;

/*  CSSM_DLTYPE  */
typedef enum cssm_dltype {
    CSSM_DL_UNKNOWN = 0,
    CSSM_DL_CUSTOM = 1,
    CSSM_DL_LDAP = 2,
    CSSM_DL_ODBC = 3,
    CSSM_DL_PKCS11 = 4,
    CSSM_DL_FFS = 5,          /* flat file system  or fast file system */
    CSSM_DL_MEMORY = 6, 
    CSSM_DL_REMOTEDIR = 7
} CSSM_DLTYPE, *CSSM_DLTYPE_PTR;

/*  CSSM_DL_PKCS11_ATTRIBUTES  */
typedef struct cssm_dl_pkcs11_attributes {
    uint32 DeviceAccessFlags;
} *CSSM_DL_PKCS11_ATTRIBUTES;

typedef void *CSSM_DL_CUSTOM_ATTRIBUTES;
typedef void *CSSM_DL_LDAP_ATTRIBUTES;
typedef void *CSSM_DL_ODBC_ATTRIBUTES;
typedef void *CSSM_DL_FFS_ATTRIBUTES;

/*
    CSSM_DL_WRAPPEDPRODUCT_INFO
*/

typedef struct cssm_dl_wrappedproductinfo {
    CSSM_VERSION StandardVersion;                           /* Version of standard this product conforms to */
    CSSM_STRING StandardDescription;  /* Description of standard this product conforms to */
    CSSM_VERSION ProductVersion;                            /* Version of wrapped product/library */
    CSSM_STRING ProductDescription;   /* Description of wrapped product/library */
    CSSM_STRING ProductVendor;        /* Vendor of wrapped product/library */
    uint32 ProductFlags;                                    /* ProductFlags */
} CSSM_DL_WRAPPEDPRODUCT_INFO, *CSSM_DL_WRAPPEDPRODUCT_INFO_PTR;

typedef struct cssm_dlsubservice {
    uint32 SubServiceId;
    CSSM_STRING Description;          /* Description of this sub service */
    CSSM_DLTYPE Type;
    union {
        CSSM_DL_CUSTOM_ATTRIBUTES CustomAttributes;
        CSSM_DL_LDAP_ATTRIBUTES LdapAttributes;
        CSSM_DL_ODBC_ATTRIBUTES OdbcAttributes;
        CSSM_DL_PKCS11_ATTRIBUTES Pkcs11Attributes;
        CSSM_DL_FFS_ATTRIBUTES FfsAttributes;
    } Attributes;

    CSSM_DL_WRAPPEDPRODUCT_INFO WrappedProduct;
    CSSM_USER_AUTHENTICATION_MECHANISM AuthenticationMechanism;

    /* meta information about the query support provided by the module */
    uint32 NumberOfRelOperatorTypes;
    CSSM_DB_OPERATOR_PTR RelOperatorTypes;
    uint32 NumberOfConjOperatorTypes;
    CSSM_DB_CONJUNCTIVE_PTR ConjOperatorTypes;
    CSSM_BOOL QueryLimitsSupported;

    /* meta information about the encapsulated data stores (if known) */
    uint32 NumberOfDataStores;
    CSSM_NAME_LIST_PTR DataStoreNames;
    CSSM_DBINFO_PTR DataStoreInfo;

    /* additional information */
    void *Reserved;
} CSSM_DLSUBSERVICE, *CSSM_DLSUBSERVICE_PTR;

/* Static data associated with a data storage library add-in module */

typedef enum cssm_algorithms {
    CSSM_ALGID_NONE      = 0,
    CSSM_ALGID_CUSTOM    = CSSM_ALGID_NONE+1, /* Custom algorithm */
    CSSM_ALGID_DH        = CSSM_ALGID_NONE+2, /* Diffie Hellman key exchange algorithm */
    CSSM_ALGID_PH        = CSSM_ALGID_NONE+3, /* Pohlig Hellman key exchange algorithm */
    CSSM_ALGID_KEA       = CSSM_ALGID_NONE+4, /* Key Exchange Algorithm */
    CSSM_ALGID_MD2       = CSSM_ALGID_NONE+5, /* MD2  hash algorithm  (invented by Ron Rivest) */
    CSSM_ALGID_MD4       = CSSM_ALGID_NONE+6, /* MD4  hash algorithm  (invented by Ron Rivest) */
    CSSM_ALGID_MD5       = CSSM_ALGID_NONE+7, /* MD5  hash algorithm  (invented by Ron Rivest) */
    CSSM_ALGID_SHA1      = CSSM_ALGID_NONE+8, /* Secure Hash Algorithm  (developed by NIST/NSA) */
    CSSM_ALGID_NHASH     = CSSM_ALGID_NONE+9, /* N-Hash algorithm(developed by Nippon Telephone and Telegraph) */
    CSSM_ALGID_HAVAL     = CSSM_ALGID_NONE+10,/* HAVAL  hash algorithm  (MD5 variant) */
    CSSM_ALGID_RIPEMD    = CSSM_ALGID_NONE+11,/* RIPE-MD  (160) hash algorithm  (MD4 variant - developed for the European Community's RIPE project) */
    CSSM_ALGID_IBCHASH   = CSSM_ALGID_NONE+12,/* IBC-Hash (keyed hash algorithm or MAC) */
    CSSM_ALGID_RIPEMAC   = CSSM_ALGID_NONE+13,/* RIPE-MAC (invented by Bart Preneel) */
    CSSM_ALGID_DES       = CSSM_ALGID_NONE+14,/* Data Encryption Standard block cipher */
    CSSM_ALGID_DESX      = CSSM_ALGID_NONE+15,/* DESX block cipher  (DES variant from RSA) */
    CSSM_ALGID_RDES      = CSSM_ALGID_NONE+16,/* RDES block cipher  (DES variant) */
    CSSM_ALGID_3DES_3KEY = CSSM_ALGID_NONE+17,/* Triple-DES block cipher  (with 3 keys) */
    CSSM_ALGID_3DES_2KEY = CSSM_ALGID_NONE+18,/* Triple-DES block cipher  (with 2 keys) */
    CSSM_ALGID_3DES_1KEY = CSSM_ALGID_NONE+19,/* Triple-DES block cipher  (with 1 key) */
    CSSM_ALGID_IDEA      = CSSM_ALGID_NONE+20,/* IDEA block cipher  (invented by Lai and Massey) */
    CSSM_ALGID_RC2       = CSSM_ALGID_NONE+21,/* RC2 block cipher  (invented by Ron Rivest) */
    CSSM_ALGID_RC5       = CSSM_ALGID_NONE+22,/* RC5 block cipher  (invented by Ron Rivest) */
    CSSM_ALGID_RC4       = CSSM_ALGID_NONE+23,/* RC4 stream cipher  (invented by Ron Rivest) */
    CSSM_ALGID_SEAL      = CSSM_ALGID_NONE+24,/* SEAL stream cipher  (invented by Rogaway and Coppersmith) */
    CSSM_ALGID_CAST      = CSSM_ALGID_NONE+25,/* CAST block cipher  (invented by Adams and Tavares) */
    CSSM_ALGID_BLOWFISH  = CSSM_ALGID_NONE+26,/* BLOWFISH block cipher  (invented by Schneier) */
    CSSM_ALGID_SKIPJACK  = CSSM_ALGID_NONE+27,/* Skipjack block cipher  (developed by NSA) */
    CSSM_ALGID_LUCIFER   = CSSM_ALGID_NONE+28,/* Lucifer block cipher  (developed by IBM) */
    CSSM_ALGID_MADRYGA   = CSSM_ALGID_NONE+29,/* Madryga block cipher  (invented by Madryga) */
    CSSM_ALGID_FEAL      = CSSM_ALGID_NONE+30,/* FEAL block cipher  (invented by Shimizu and Miyaguchi) */
    CSSM_ALGID_REDOC     = CSSM_ALGID_NONE+31,/* REDOC 2 block cipher  (invented by Michael Wood) */
    CSSM_ALGID_REDOC3    = CSSM_ALGID_NONE+32,/* REDOC 3 block cipher  (invented by Michael Wood) */
    CSSM_ALGID_LOKI      = CSSM_ALGID_NONE+33,/* LOKI block cipher */
    CSSM_ALGID_KHUFU     = CSSM_ALGID_NONE+34,/* KHUFU block cipher  (invented by Ralph Merkle) */
    CSSM_ALGID_KHAFRE    = CSSM_ALGID_NONE+35,/* KHAFRE block cipher  (invented by Ralph Merkle) */
    CSSM_ALGID_MMB       = CSSM_ALGID_NONE+36,/* MMB block cipher  (IDEA variant) */
    CSSM_ALGID_GOST      = CSSM_ALGID_NONE+37,/* GOST block cipher  (developed by the former Soviet Union) */
    CSSM_ALGID_SAFER     = CSSM_ALGID_NONE+38,/* SAFER K-64 block cipher  (invented by Massey) */
    CSSM_ALGID_CRAB      = CSSM_ALGID_NONE+39,/* CRAB block cipher  (invented by Kaliski and Robshaw) */
    CSSM_ALGID_RSA       = CSSM_ALGID_NONE+40,/* RSA public key cipher */
    CSSM_ALGID_DSA       = CSSM_ALGID_NONE+41,/* Digital Signature Algorithm */
    CSSM_ALGID_MD5WithRSA= CSSM_ALGID_NONE+42,/* MD5/RSA signature algorithm */
    CSSM_ALGID_MD2WithRSA= CSSM_ALGID_NONE+43,/* MD2/RSA signature algorithm */
    CSSM_ALGID_ElGamal   = CSSM_ALGID_NONE+44,/* ElGamal signature algorithm */
    CSSM_ALGID_MD2Random = CSSM_ALGID_NONE+45,/* MD2-based random numbers */
    CSSM_ALGID_MD5Random = CSSM_ALGID_NONE+46,/* MD5-based random numbers */
    CSSM_ALGID_SHARandom = CSSM_ALGID_NONE+47,/* SHA-based random numbers */
    CSSM_ALGID_DESRandom = CSSM_ALGID_NONE+48, /* DES-based random numbers */
    CSSM_ALGID_SHA1WithRSA = CSSM_ALGID_NONE+49, /* SHA1/RSA signature algorithm */
    CSSM_ALGID_RSA_PKCS  = CSSM_ALGID_RSA,     /* RSA as specified in PKCS #1 */
    CSSM_ALGID_RSA_ISO9796 = CSSM_ALGID_NONE+50, /* RSA as specified in ISO 9796 */
    CSSM_ALGID_RSA_RAW   = CSSM_ALGID_NONE+51, /* Raw RSA as assumed in X.509 */
    CSSM_ALGID_CDMF      = CSSM_ALGID_NONE+52, /* CDMF block cipher */
    CSSM_ALGID_CAST3     = CSSM_ALGID_NONE+53, /* Entrust's CAST3 block cipher */
    CSSM_ALGID_CAST5     = CSSM_ALGID_NONE+54, /* Entrust's CAST5 block cipher */
    CSSM_ALGID_GenericSecret = CSSM_ALGID_NONE+55, /* Generic secret operations */
    CSSM_ALGID_ConcatBaseAndKey = CSSM_ALGID_NONE+56, /* Concatenate two keys, base key first */
    CSSM_ALGID_ConcatKeyAndBase = CSSM_ALGID_NONE+57, /* Concatenate two keys, base key last */
    CSSM_ALGID_ConcatBaseAndData = CSSM_ALGID_NONE+58, /* Concatenate base key and random data, key first */
    CSSM_ALGID_ConcatDataAndBase = CSSM_ALGID_NONE+59, /* Concatenate base key and data, data first */
    CSSM_ALGID_XORBaseAndData = CSSM_ALGID_NONE+60, /* XOR a byte string with the base key */
    CSSM_ALGID_ExtractFromKey = CSSM_ALGID_NONE+61, /* Extract a key from base key, starting at arbitrary bit position */
    CSSM_ALGID_SSL3PreMasterGen = CSSM_ALGID_NONE+62, /* Generate a 48 byte SSL 3 pre-master key */
    CSSM_ALGID_SSL3MasterDerive = CSSM_ALGID_NONE+63, /* Derive an SSL 3 key from a pre-master key */
    CSSM_ALGID_SSL3KeyAndMacDerive = CSSM_ALGID_NONE+64, /* Derive the keys and MACing keys for the SSL cipher suite */
    CSSM_ALGID_SSL3MD5_MAC = CSSM_ALGID_NONE+65, /* Performs SSL 3 MD5 MACing */
    CSSM_ALGID_SSL3SHA1_MAC = CSSM_ALGID_NONE+66, /* Performs SSL 3 SHA-1 MACing */
    CSSM_ALGID_MD5_PBE   = CSSM_ALGID_NONE+67, /* Generate key and IV by MD5 hashing a base key */
    CSSM_ALGID_MD2_PBE   = CSSM_ALGID_NONE+68, /* Generate key and IV by MD2 hashing a base key */
    CSSM_ALGID_SHA1_PBE  = CSSM_ALGID_NONE+69, /* Generate key and IV by SHA-1 hashing a base key */
    CSSM_ALGID_WrapLynks = CSSM_ALGID_NONE+70, /* Spyrus LYNKS DES based wrapping scheme w/checksum */
    CSSM_ALGID_WrapSET_OAEP = CSSM_ALGID_NONE+71, /* SET key wrapping */
    CSSM_ALGID_BATON     = CSSM_ALGID_NONE+72, /* Fortezza BATON cipher */
    CSSM_ALGID_ECDSA     = CSSM_ALGID_NONE+73, /* Elliptic Curve DSA */
    CSSM_ALGID_MAYFLY    = CSSM_ALGID_NONE+74, /* Fortezza MAYFLY cipher */
    CSSM_ALGID_JUNIPER   = CSSM_ALGID_NONE+75, /* Fortezza JUNIPER cipher */
    CSSM_ALGID_FASTHASH  = CSSM_ALGID_NONE+76, /* Fortezza FASTHASH */
    CSSM_ALGID_3DES      = CSSM_ALGID_NONE+77, /* Generic 3DES */
    CSSM_ALGID_SSL3MD5   = CSSM_ALGID_NONE+78, /* SSL3MD5 */
    CSSM_ALGID_SSL3SHA1  = CSSM_ALGID_NONE+79, /* SSL3SHA1 */
    CSSM_ALGID_FortezzaTimestamp = CSSM_ALGID_NONE+80, /* FortezzaTimestamp */
    CSSM_ALGID_SHA1WithDSA = CSSM_ALGID_NONE+81, /* SHA1WithDSA */
    CSSM_ALGID_SHA1WithECDSA = CSSM_ALGID_NONE+82, /* SHA1WithECDSA */
    CSSM_ALGID_DSA_BSAFE = CSSM_ALGID_NONE+83,  /* BSafe Key format */
	CSSM_ALGID_MDWithRSA_BSAFE1_RAW = CSSM_ALGID_NONE+84,	/* BSAFE v1 */
	CSSM_ALGID_MDWithRSA_BSAFE1_PAD = CSSM_ALGID_NONE+85,	/* BSAFE v1 with pad */
	CSSM_ALGID_MDWithRSA_BSAFE1_PAD_CHECKSUM = CSSM_ALGID_NONE+86, /* BSAFE v1 with pad/checksum */
	CSSM_ALGID_PKCS11Random = CSSM_ALGID_NONE+87, /* PKCS11-based random numbers */

#ifdef KEY_RECOVERY
	CSSM_ALGID_WILDCARD		= CSSM_ALGID_NONE+99999
#endif

} CSSM_ALGORITHMS;

typedef enum cssm_encrypt_mode {
    CSSM_ALGMODE_NONE       = 0,
    CSSM_ALGMODE_CUSTOM     = CSSM_ALGMODE_NONE+1, /* Custom mode */
    CSSM_ALGMODE_ECB        = CSSM_ALGMODE_NONE+2, /* Electronic Code Book */
    CSSM_ALGMODE_ECBPad     = CSSM_ALGMODE_NONE+3, /* ECB with padding */
    CSSM_ALGMODE_CBC        = CSSM_ALGMODE_NONE+4, /* Cipher Block Chaining */
    CSSM_ALGMODE_CBC_IV8    = CSSM_ALGMODE_NONE+5, /* CBC with Initialization Vector of 8 bytes */
    CSSM_ALGMODE_CBCPadIV8  = CSSM_ALGMODE_NONE+6, /* CBC with padding and Initialization Vector of 8 bytes */
    CSSM_ALGMODE_CFB        = CSSM_ALGMODE_NONE+7, /* Cipher FeedBack */
    CSSM_ALGMODE_CFB_IV8    = CSSM_ALGMODE_NONE+8, /* CFB with Initialization Vector of 8 bytes */
    CSSM_ALGMODE_CFBPadIV8  = CSSM_ALGMODE_NONE+9, /* CFB used in MS CAPI 2.0 */
    CSSM_ALGMODE_OFB        = CSSM_ALGMODE_NONE+10, /* Output FeedBack */
    CSSM_ALGMODE_OFB_IV8    = CSSM_ALGMODE_NONE+11, /* OFB with Initialization Vector of 8 bytes */
    CSSM_ALGMODE_OFBPadIV8  = CSSM_ALGMODE_NONE+12, /* OFB used in MS CAPI 2.0 */
    CSSM_ALGMODE_COUNTER    = CSSM_ALGMODE_NONE+13, /* Counter */
    CSSM_ALGMODE_BC         = CSSM_ALGMODE_NONE+14, /* Block Chaining */
    CSSM_ALGMODE_PCBC       = CSSM_ALGMODE_NONE+15, /* Propagating CBC */
    CSSM_ALGMODE_CBCC       = CSSM_ALGMODE_NONE+16, /* CBC with Checksum */
    CSSM_ALGMODE_OFBNLF     = CSSM_ALGMODE_NONE+17, /* OFB with NonLinear Function */
    CSSM_ALGMODE_PBC        = CSSM_ALGMODE_NONE+18, /* Plaintext Block Chaining */
    CSSM_ALGMODE_PFB        = CSSM_ALGMODE_NONE+19, /* Plaintext FeedBack */
    CSSM_ALGMODE_CBCPD      = CSSM_ALGMODE_NONE+20, /* CBC of Plaintext Difference */
    CSSM_ALGMODE_PUBLIC_KEY = CSSM_ALGMODE_NONE+21, /* Encrypt with the public key */
    CSSM_ALGMODE_PRIVATE_KEY= CSSM_ALGMODE_NONE+22, /* Encrypt with the private key */
    CSSM_ALGMODE_SHUFFLE    = CSSM_ALGMODE_NONE+23, /* Fortezza shuffle mode */
    CSSM_ALGMODE_ECB64      = CSSM_ALGMODE_NONE+24,
    CSSM_ALGMODE_CBC64      = CSSM_ALGMODE_NONE+25,
    CSSM_ALGMODE_OFB64      = CSSM_ALGMODE_NONE+26,
    CSSM_ALGMODE_CFB64      = CSSM_ALGMODE_NONE+27,
    CSSM_ALGMODE_CFB32      = CSSM_ALGMODE_NONE+28,
    CSSM_ALGMODE_CFB16      = CSSM_ALGMODE_NONE+29,
    CSSM_ALGMODE_CFB8       = CSSM_ALGMODE_NONE+30,
    CSSM_ALGMODE_WRAP       = CSSM_ALGMODE_NONE+31,
    CSSM_ALGMODE_PRIVATE_WRAP = CSSM_ALGMODE_NONE+32,
    CSSM_ALGMODE_RELAYX     = CSSM_ALGMODE_NONE+33,
    CSSM_ALGMODE_ECB128     = CSSM_ALGMODE_NONE+34,
    CSSM_ALGMODE_ECB96      = CSSM_ALGMODE_NONE+35,
    CSSM_ALGMODE_CBC128     = CSSM_ALGMODE_NONE+36,
    CSSM_ALGMODE_OAEP_HASH  = CSSM_ALGMODE_NONE+37,

#ifdef KEY_RECOVERY
	CSSM_ALGMODE_WILDCARD	= CSSM_ALGMODE_NONE+99999
#endif

} CSSM_ENCRYPT_MODE;

typedef enum cssm_context_type {
    CSSM_ALGCLASS_NONE      = 0,
    CSSM_ALGCLASS_CUSTOM    = CSSM_ALGCLASS_NONE+1,
    CSSM_ALGCLASS_KEYXCH    = CSSM_ALGCLASS_NONE+2,
    CSSM_ALGCLASS_SIGNATURE = CSSM_ALGCLASS_NONE+3,
    CSSM_ALGCLASS_SYMMETRIC = CSSM_ALGCLASS_NONE+4,
    CSSM_ALGCLASS_DIGEST    = CSSM_ALGCLASS_NONE+5,
    CSSM_ALGCLASS_RANDOMGEN = CSSM_ALGCLASS_NONE+6,
    CSSM_ALGCLASS_UNIQUEGEN = CSSM_ALGCLASS_NONE+7,
    CSSM_ALGCLASS_MAC       = CSSM_ALGCLASS_NONE+8,
    CSSM_ALGCLASS_ASYMMETRIC= CSSM_ALGCLASS_NONE+9,
    CSSM_ALGCLASS_KEYGEN    = CSSM_ALGCLASS_NONE+10,
    CSSM_ALGCLASS_DERIVEKEY = CSSM_ALGCLASS_NONE+11
#ifdef KEY_RECOVERY
    ,
    CSSM_ALGCLASS_KEY_RECOVERY_ENABLEMENT    = CSSM_ALGCLASS_NONE+12,
    CSSM_ALGCLASS_KEY_RECOVERY_REGISTRATION = CSSM_ALGCLASS_NONE+13,
    CSSM_ALGCLASS_KEY_RECOVERY_REQUEST        = CSSM_ALGCLASS_NONE+14
#endif
}CSSM_CONTEXT_TYPE;

/* Attribute data type tags */
#define CSSM_ATTRIBUTE_DATA_NONE        0x00000000
#define CSSM_ATTRIBUTE_DATA_UINT32      0x10000000
#define CSSM_ATTRIBUTE_DATA_CSSM_DATA   0x20000000
#define CSSM_ATTRIBUTE_DATA_CRYPTO_DATA 0x30000000
#define CSSM_ATTRIBUTE_DATA_KEY         0x40000000
#define CSSM_ATTRIBUTE_DATA_STRING      0x50000000
#define CSSM_ATTRIBUTE_DATA_DATE        0x60000000
#define CSSM_ATTRIBUTE_DATA_RANGE       0x70000000
#define CSSM_ATTRIBUTE_DATA_VERSION     0x01000000
#ifdef KEY_RECOVERY
#define CSSM_ATTRIBUTE_DATA_KR_PROFILE  0x02000000
#endif

#define CSSM_ATTRIBUTE_TYPE_MASK        0xFF000000

typedef enum cssm_attribute_type {
    CSSM_ATTRIBUTE_NONE         = 0,
    CSSM_ATTRIBUTE_CUSTOM       = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 1),
    CSSM_ATTRIBUTE_DESCRIPTION  = (CSSM_ATTRIBUTE_DATA_STRING | 2),
    CSSM_ATTRIBUTE_KEY          = (CSSM_ATTRIBUTE_DATA_KEY | 3),
    CSSM_ATTRIBUTE_INIT_VECTOR  = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 4),
    CSSM_ATTRIBUTE_SALT         = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 5),
    CSSM_ATTRIBUTE_PADDING      = (CSSM_ATTRIBUTE_DATA_UINT32 | 6),
    CSSM_ATTRIBUTE_RANDOM       = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 7),
    CSSM_ATTRIBUTE_SEED         = (CSSM_ATTRIBUTE_DATA_CRYPTO_DATA | 8),
    CSSM_ATTRIBUTE_PASSPHRASE   = (CSSM_ATTRIBUTE_DATA_CRYPTO_DATA | 9),
    CSSM_ATTRIBUTE_KEY_LENGTH   = (CSSM_ATTRIBUTE_DATA_UINT32 | 10),
    CSSM_ATTRIBUTE_KEY_LENGTH_RANGE = (CSSM_ATTRIBUTE_DATA_RANGE | 11),
    CSSM_ATTRIBUTE_BLOCK_SIZE   = (CSSM_ATTRIBUTE_DATA_UINT32 | 12),
    CSSM_ATTRIBUTE_OUTPUT_SIZE  = (CSSM_ATTRIBUTE_DATA_UINT32 | 13),
    CSSM_ATTRIBUTE_ROUNDS       = (CSSM_ATTRIBUTE_DATA_UINT32 | 14),
    CSSM_ATTRIBUTE_IV_SIZE        = (CSSM_ATTRIBUTE_DATA_UINT32 | 15),
    CSSM_ATTRIBUTE_ALG_PARAMS    = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 16),
    CSSM_ATTRIBUTE_LABEL        = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 17),
    CSSM_ATTRIBUTE_KEY_TYPE        = (CSSM_ATTRIBUTE_DATA_UINT32 | 18),
    CSSM_ATTRIBUTE_MODE        = (CSSM_ATTRIBUTE_DATA_UINT32 | 19),
    CSSM_ATTRIBUTE_EFFECTIVE_BITS = (CSSM_ATTRIBUTE_DATA_UINT32 | 20),
    CSSM_ATTRIBUTE_START_DATE     = (CSSM_ATTRIBUTE_DATA_DATE | 21),
    CSSM_ATTRIBUTE_END_DATE       = (CSSM_ATTRIBUTE_DATA_DATE | 22),
    CSSM_ATTRIBUTE_KEYUSAGE     = (CSSM_ATTRIBUTE_DATA_UINT32 | 23),
    CSSM_ATTRIBUTE_KEYATTR      = (CSSM_ATTRIBUTE_DATA_UINT32 | 24),
    CSSM_ATTRIBUTE_VERSION      = (CSSM_ATTRIBUTE_DATA_VERSION | 25),
    CSSM_ATTRIBUTE_PRIME        = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 26),
    CSSM_ATTRIBUTE_BASE         = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 27),
    CSSM_ATTRIBUTE_SUBPRIME     = (CSSM_ATTRIBUTE_DATA_CSSM_DATA | 28),
    CSSM_ATTRIBUTE_ALG_ID       = (CSSM_ATTRIBUTE_DATA_UINT32 | 29),
    CSSM_ATTRIBUTE_INTERATION_COUNT = (CSSM_ATTRIBUTE_DATA_UINT32 | 30),
    CSSM_ATTRIBUTE_ROUNDS_RANGE     = (CSSM_ATTRIBUTE_DATA_RANGE | 31),
#ifdef KEY_RECOVERY
    CSSM_ATTRIBUTE_KRPROFILE_LOCAL  = (CSSM_ATTRIBUTE_DATA_KR_PROFILE | 31),
    CSSM_ATTRIBUTE_KRPROFILE_REMOTE = (CSSM_ATTRIBUTE_DATA_KR_PROFILE | 32),
#endif /* KEY_RECOVERY */
	CSSM_ATTRIBUTE_CSP_HANDLE		= (CSSM_ATTRIBUTE_DATA_UINT32 | 33)
} CSSM_ATTRIBUTE_TYPE;

typedef enum cssm_padding { 
    CSSM_PADDING_NONE           = 0,
    CSSM_PADDING_CUSTOM         = CSSM_PADDING_NONE+1,
    CSSM_PADDING_ZERO           = CSSM_PADDING_NONE+2,
    CSSM_PADDING_ONE            = CSSM_PADDING_NONE+3,
    CSSM_PADDING_ALTERNATE      = CSSM_PADDING_NONE+4,
    CSSM_PADDING_FF             = CSSM_PADDING_NONE+5,
    CSSM_PADDING_PKCS5          = CSSM_PADDING_NONE+6,
    CSSM_PADDING_PKCS7          = CSSM_PADDING_NONE+7,
    CSSM_PADDING_CipherStealing = CSSM_PADDING_NONE+8,
    CSSM_PADDING_RANDOM         = CSSM_PADDING_NONE+9
} CSSM_PADDING;


/*
    CSSM_KEY & CSSM_KEYHEADER Data Structures  
*/

/*
    Blob Type
*/

#define CSSM_KEYBLOB_RAW                0            /* The blob is a clear, raw key */
#define CSSM_KEYBLOB_RAW_BERDER            1            /* The blob is a clear key, DER encoded */
#define CSSM_KEYBLOB_REFERENCE            2            /* The blob is a reference to a key */
#define CSSM_KEYBLOB_WRAPPED            3            /* The blob is a wrapped RAW key */
#define CSSM_KEYBLOB_WRAPPED_BERDER        4            /* The blob is a wrapped DER encoded key */
#define CSSM_KEYBLOB_OTHER                0xFFFFFFFF  /* The blob is a wrapped DER encoded key */

/*
    Raw Format 
*/

#define CSSM_KEYBLOB_RAW_FORMAT_NONE	  0            /* No further conversion need to be done */
#define CSSM_KEYBLOB_RAW_FORMAT_PKCS1     1            /* RSA PKCS1 V1.5 */
#define CSSM_KEYBLOB_RAW_FORMAT_PKCS3     2            /* RSA PKCS3 V1.5 */
#define CSSM_KEYBLOB_RAW_FORMAT_MSCAPI    3            /* Microsoft CAPI V2.0 */
#define CSSM_KEYBLOB_RAW_FORMAT_PGP       4            /* PGP V??? */
#define CSSM_KEYBLOB_RAW_FORMAT_FIPS186   5            /* US Gov. FIPS 186 - DSS V??? */
#define CSSM_KEYBLOB_RAW_FORMAT_BSAFE     6            /* RSA Bsafe V3.0 */
#define CSSM_KEYBLOB_RAW_FORMAT_PKCS11    7            /* RSA PKCS11 V2.0 */
#define CSSM_KEYBLOB_RAW_FORMAT_CDSA      8            /* CDSA */
#define CSSM_KEYBLOB_RAW_FORMAT_CCA       9            /* CCA clear public key blob */
#define CSSM_KEYBLOB_RAW_FORMAT_OTHER     0xFFFFFFFF   /* Other, CSP defined */

/*
    Reference Format
*/

#define CSSM_KEYBLOB_REF_FORMAT_INTEGER     0            /* Reference is a number or handle */
#define CSSM_KEYBLOB_REF_FORMAT_STRING      1           /* Reference is a string or name */
#define CSSM_KEYBLOB_REF_FORMAT_CCA         2           /* Reference is a CCA key token */
#define CSSM_KEYBLOB_REF_FORMAT_OTHER       0xFFFFFFFF  /* Other, CSP defined */


/*
    Key Class
*/

#define CSSM_KEYCLASS_PUBLIC_KEY     0                    /* Key is public key */
#define CSSM_KEYCLASS_PRIVATE_KEY    1                    /* Key is private key */
#define CSSM_KEYCLASS_SESSION_KEY    2                    /* Key is session or symmetric key */
#define CSSM_KEYCLASS_SECRET_PART    3                    /* Key is part of secret key */ 
#define CSSM_KEYCLASS_PARAMETERS	 4
#define CSSM_KEYCLASS_OTHER          0xFFFFFFFF            /* Other */ 


/*
    Key Use Flags
*/

#define CSSM_KEYUSE_ANY                 0x80000000
#define CSSM_KEYUSE_ENCRYPT             0x00000001
#define CSSM_KEYUSE_DECRYPT             0x00000002
#define CSSM_KEYUSE_SIGN                0x00000004
#define CSSM_KEYUSE_VERIFY              0x00000008
#define CSSM_KEYUSE_SIGN_RECOVER        0x00000010
#define CSSM_KEYUSE_VERIFY_RECOVER      0x00000020
#define CSSM_KEYUSE_WRAP                0x00000040
#define CSSM_KEYUSE_UNWRAP              0x00000080
#define CSSM_KEYUSE_DERIVE              0x00000100



/*
    CSSM_DATE
*/

typedef struct cssm_date {
    uint8 Year[4];                            /* 1997-9999, year 10000 problem!!! */
    uint8 Month[2];                            /* 01-12 */
    uint8 Day[2];                            /* 01-31 */
} CSSM_DATE, *CSSM_DATE_PTR;


/*
    CSSM_RANGE
*/
typedef struct cssm_range {
    uint32 Min;          /* inclusive minimium value */
    uint32 Max;          /* inclusive maximium value */
} CSSM_RANGE, *CSSM_RANGE_PTR;

typedef uint32 CSSM_HEADERVERSION;
/*
    CSSM_KEYHEADER
*/

typedef struct cssm_keyheader {
    CSSM_HEADERVERSION HeaderVersion;    /* Key header version */
    CSSM_GUID CspId;                    /* GUID of CSP generating the key */
    uint32 BlobType;                    /* See BlobType #define's */
    uint32 Format;                        /* Raw or Reference format */
    uint32 AlgorithmId;                    /* Algoritm ID of key */
    uint32 KeyClass;                    /* Public/Private/Secret etc. */
    uint32 KeySizeInBits;                /* Size of actual key/modulus/prime in bits */
    uint32 KeyAttr;                        /* Attribute flags */
    uint32 KeyUsage;                    /* Key use flags */
    CSSM_DATE StartDate;                /* Effective date of key */
    CSSM_DATE EndDate;                    /* Expiration date of key */
    uint32 WrapAlgorithmId;                /* == CSSM_ALGID_NONE if clear key */
    uint32 WrapMode;                    /* if alg supports multiple wrapping modes */
    uint32 Reserved;
} CSSM_KEYHEADER, *CSSM_KEYHEADER_PTR;


/*
    CSSM_KEY
*/

typedef struct cssm_key    {
    CSSM_KEYHEADER KeyHeader;       /* Key header which is of fixed length */
    CSSM_DATA KeyData;              /* Key data which is of variable length */
} CSSM_KEY, *CSSM_KEY_PTR;

typedef CSSM_KEY CSSM_WRAP_KEY, *CSSM_WRAP_KEY_PTR;

#define CSSM_KEYHEADER_VERSION    (2)

typedef struct cssm_key_size {
    uint32 KeySizeInBits;            /* Key size in bits */
    uint32 EffectiveKeySizeInBits;   /* Effective key size in bits */
} CSSM_KEY_SIZE, *CSSM_KEY_SIZE_PTR;

typedef struct cssm_query_size_data {
    uint32 SizeInputBlock;
    uint32 SizeOutputBlock;
} CSSM_QUERY_SIZE_DATA, *CSSM_QUERY_SIZE_DATA_PTR;

#ifdef KEY_RECOVERY
/*
    KEY RECOVERY DATA TYPES
*/

typedef struct kr_policy_list_item {
    struct kr_policy_list_item  *next;
    uint32              AlgorithmId;
    uint32              Mode;
    uint32              MaxKeyLength;
	uint32				MaxRounds;
    uint8               WorkFactor;
    uint8               PolicyFlags; /* to indicate which jurisdiction required the policy */
    uint32              AlgClass; /* SYMMETRIC versus ASYMMETRIC */
} CSSM_KR_POLICY_LIST_ITEM;


typedef struct policy_info {
	CSSM_BOOL		krbNotAllowed;
	uint32			numberOfEntries;
	CSSM_KR_POLICY_LIST_ITEM *policyEntry;
} CSSM_POLICY_INFO, *CSSM_POLICY_INFO_PTR;


typedef struct cssm_kr_name { 
    uint8    Type;        /* namespace type */
    uint32  Length;        /* namespace length */
    char    *Name;        /* name string */
} CSSM_KR_NAME, *CSSM_KR_NAME_PTR;

typedef struct cssm_kr_profile {
    CSSM_KR_NAME            UserName;                   // Name of user this profile profiles
    CSSM_DATA_PTR           UserCertificate;            // PK certificate of user

    CSSM_CERTGROUP_PTR      KRSCertChain; /* Added by shabnam to ensure backward compat. */

    uint8                   LE_KRANum;                  // number of law enforcement cert chain following
    CSSM_CERTGROUP_PTR      LE_KRACertChainList;        // list of certificate chains for law enforcement
    uint8                   ENT_KRANum;                 // number of enterprise cert chain following
    CSSM_CERTGROUP_PTR      ENT_KRACertChainList;       // list of certificate chains for enterprise 
    uint8                   INDIV_KRANum;               // number of individual cert chains following
    CSSM_CERTGROUP_PTR      INDIV_KRACertChainList;     // list of certificate chains for individual KR
    CSSM_DATA_PTR           INDIV_AuthenticationInfo;   // auth info for user recovery
    uint32                  KRSPFlags;                  // flag values interpreted by KRSP
    CSSM_DATA_PTR           KRSPExtensions;             // reserved for extensions specific to KRSP
} CSSM_KR_PROFILE, *CSSM_KR_PROFILE_PTR;
#endif /* KEY_RECOVERY */

typedef struct cssm_context_attribute{
    uint32 AttributeType;    /* one of the defined CSSM_ATTRIBUTE_TYPEs */
    uint32 AttributeLength;  /* length of attribute */
    union {
        char *String;
        uint32 Uint32;
        CSSM_CRYPTO_DATA_PTR Crypto;
        CSSM_KEY_PTR Key;
        CSSM_DATA_PTR Data;
        CSSM_DATE_PTR Date;
        CSSM_RANGE_PTR Range;
        CSSM_VERSION_PTR Version;
#ifdef KEY_RECOVERY
        CSSM_KR_PROFILE_PTR KRProfile;    /* the profile of the local or remote client */
#endif
    } Attribute;            /* data that describes attribute */
} CSSM_CONTEXT_ATTRIBUTE, *CSSM_CONTEXT_ATTRIBUTE_PTR;

typedef struct cssm_context {
    uint32 ContextType;        /* one of the defined CSSM_CONTEXT_TYPEs */
    uint32 AlgorithmType;      /* one of the defined CSSM_ALGORITHMSs */
    uint32 Reserve;            /* reserved for future use */
    uint32 NumberOfAttributes; /* number of attributes associated with context */
    CSSM_CONTEXT_ATTRIBUTE_PTR ContextAttributes;    /* pointer to attributes */
#ifdef KEY_RECOVERY
    CSSM_BOOL Privileged;       /* when this flag is CSSM_TRUE, the context can perform
                                   crypto operations without being forced to follow the
                                   key recovery policy */
    uint32 EncryptionProhibited;/* if 0, then encryption is allowed.  Otherwise, the
                                    flags indicate which policy disallowed encryption */
    uint32 WorkFactor;            /* WorkFactor is the maximum number of bits which can 
                                be left out of key recovery fields when they are generated.  
                                The recovered of the key must then search this number of bits 
                                to recover the key.  */
#endif
	CSSM_CSP_HANDLE	CSPHandle;	
} CSSM_CONTEXT, *CSSM_CONTEXT_PTR;

/* --- Key Recovery Policy API Flags --- */
#define KR_INDIV			0x01
#define KR_ENT				0x02
#define KR_LE				KR_LE_MAN | KR_LE_USE	
#define KR_LE_MAN			0x08
#define KR_LE_USE			0x10
#define KR_ALL				0x20
#define KR_OPTIMIZE			0x40
#define KR_DROP_WORKFACTOR	0x80


typedef CSSM_CONTEXT CSSM_CONTEXT_INFO;

/*
    CSSM_CSP_CAPABILITY
*/

typedef CSSM_CONTEXT CSSM_CSP_CAPABILITY, *CSSM_CSP_CAPABILITY_PTR;


/*
    CspType
*/

typedef uint32 CSSM_CSPTYPE;
#define CSSM_CSP_SOFTWARE         1
#define CSSM_CSP_HARDWARE         2

/*
    Software Csp SubService Info
*/

typedef struct cssm_softwarecspsubserviceinfo {
    uint32 NumberOfCapabilities;                /* Number of capabilities in list */
    CSSM_CSP_CAPABILITY_PTR CapabilityList;     /* List of capabilitites */
    void* Reserved;                             /* Reserved field */
} CSSM_SOFTWARE_CSPSUBSERVICE_INFO, *CSSM_SOFTWARE_CSPSUBSERVICE_INFO_PTR;


/*
    Hardware Csp SubService Info
*/

/* ReaderFlags */

#define CSSM_CSP_RDR_TOKENPRESENT  0x00000001    /* Token is present in reader/slot */
#define CSSM_CSP_RDR_EXISTS        0x00000002    /* Device is a reader with removable token */
#define CSSM_CSP_RDR_HW            0x00000004    /* Slot is a hardware slot */


/* TokenFlags */

#define CSSM_CSP_TOK_RNG                    0x00000001    /* Token has random number generator */ 
#define CSSM_CSP_TOK_WRITE_PROTECTED        0x00000002    /* Token is write protected */
#define CSSM_CSP_TOK_LOGIN_REQUIRED         0x00000004    /* User must login to access private obj */
#define CSSM_CSP_TOK_USER_PIN_INITIALIZED   0x00000008    /* User's PIN has been initialized */
#define CSSM_CSP_TOK_EXCLUSIVE_SESSION      0x00000010    /* An exclusive session currently exists */
#define CSSM_CSP_TOK_CLOCK_EXISTS           0x00000040    /* Token has built in clock */
#define CSSM_CSP_TOK_ASYNC_SESSION          0x00000080    /* Token supports asynchronous operations */
#define CSSM_CSP_TOK_PROT_AUTHENTICATION    0x00000100    /* Token has protected authentication path */
#define CSSM_CSP_TOK_DUAL_CRYPTO_OPS        0x00000200    /* Token supports dual crypto ops */
 

typedef struct cssm_hardwarecspsubserviceinfo {
    uint32 NumberOfCapabilities;                       /* Number of capabilities in list */
    CSSM_CSP_CAPABILITY_PTR CapabilityList;            /* List of capabilitites */
    void* Reserved;                                    /* Reserved field */

    /* Reader/Slot Info */
    CSSM_STRING ReaderDescription;
    CSSM_STRING ReaderVendor;
    CSSM_STRING ReaderSerialNumber;
    CSSM_VERSION ReaderHardwareVersion;
    CSSM_VERSION ReaderFirmwareVersion;
    uint32 ReaderFlags;                                /* See ReaderFlags #define's */
    uint32 ReaderCustomFlags;

    /* 
        Token Info, may not be available if reader supports removable device 
        AND device is not present.
    */
    CSSM_STRING TokenDescription;   
    CSSM_STRING TokenVendor;            
    CSSM_STRING TokenSerialNumber;    
    CSSM_VERSION TokenHardwareVersion;    
    CSSM_VERSION TokenFirmwareVersion;    
    
    uint32 TokenFlags;                                /* See TokenFlags #defines's */
    uint32 TokenCustomFlags;
    uint32 TokenMaxSessionCount;
    uint32 TokenOpenedSessionCount;
    uint32 TokenMaxRWSessionCount;
    uint32 TokenOpenedRWSessionCount;
    uint32 TokenTotalPublicMem;
    uint32 TokenFreePublicMem;
    uint32 TokenTotalPrivateMem;
    uint32 TokenFreePrivateMem;
    uint32 TokenMaxPinLen;
    uint32 TokenMinPinLen;
    char TokenUTCTime[16];

    /*
        User Info, may not be available if reader supports removable device 
        AND device is not present.
    */
    CSSM_STRING UserLabel;
    CSSM_DATA UserCACertificate;                    /* Certificate of CA */ 

} CSSM_HARDWARE_CSPSUBSERVICE_INFO, *CSSM_HARDWARE_CSPSUBSERVICE_INFO_PTR;


/*
    CSSM_CSP_WRAPPEDPRODUCT_INFO
*/

/* (Wrapped)ProductFlags */
/* None curently defined */

typedef struct cssm_csp_wrappedproductinfo {
    CSSM_VERSION StandardVersion;                           /* Version of standard this product conforms to */
    CSSM_STRING StandardDescription;  /* Description of standard this product conforms to */
    CSSM_VERSION ProductVersion;                            /* Version of wrapped product/library */
    CSSM_STRING ProductDescription;   /* Description of wrapped product/library */
    CSSM_STRING ProductVendor;        /* Vendor of wrapped product/library */
    uint32 ProductFlags;                                    /* ProductFlags */
} CSSM_CSP_WRAPPEDPRODUCT_INFO, *CSSM_CSP_WRAPPEDPRODUCT_INFO_PTR;

/*
    CSSM_CSPINFO
*/

/* CspFlags */
typedef uint32 CSSM_CSP_FLAGS;
#define CSSM_CSP_STORES_PRIVATE_KEYS    0x00000001    /* CSP can store private keys */
#define CSSM_CSP_STORES_PUBLIC_KEYS     0x00000002    /* CSP can store public keys */
#define CSSM_CSP_STORES_SESSION_KEYS    0x00000004    /* CSP can store session/secret keys */

typedef struct cssm_cspsubservice {
    uint32 SubServiceId;
    CSSM_STRING Description;
    CSSM_CSP_FLAGS CspFlags;       /* General flags defined by CSSM for CSPs */   
    uint32 CspCustomFlags;         /* Flags defined by individual CSP */  
    uint32 AccessFlags;            /* Access Flags used by CSP */
    CSSM_CSPTYPE CspType;          /* CSP type number for dereferencing CspInfo*/
    union {                        /* info struct of type defined by CspType */
        CSSM_SOFTWARE_CSPSUBSERVICE_INFO SoftwareCspSubService;
        CSSM_HARDWARE_CSPSUBSERVICE_INFO HardwareCspSubService;
    };
    CSSM_CSP_WRAPPEDPRODUCT_INFO WrappedProduct;    /* Pointer to wrapped product info */
} CSSM_CSPSUBSERVICE, *CSSM_CSPSUBSERVICE_PTR;

#define CSSM_VALUE_NOT_AVAILABLE    (0xFFFFFFFF)

/* 
    Key Attribute Flags
*/
/* Valid only during call to an API. Will never be valid when set in a key header */
#define CSSM_KEYATTR_RETURN_DATA      0x10000000
#define CSSM_KEYATTR_RETURN_REF       0x20000000
#define CSSM_KEYATTR_RETURN_NONE      0x30000000
#define CSSM_KEYATTR_RETURN_CDSA	  0x01000000

/* Valid during an API call and in a key header */
#define CSSM_KEYATTR_PERMANENT        0x00000001
#define CSSM_KEYATTR_PRIVATE          0x00000002
#define CSSM_KEYATTR_MODIFIABLE       0x00000004
#define CSSM_KEYATTR_SENSITIVE        0x00000008
#define CSSM_KEYATTR_EXTRACTABLE      0x00000020

/* Valid only in a key header generated by a CSP, not valid during an API call */
#define CSSM_KEYATTR_ALWAYS_SENSITIVE 0x00000010
#define CSSM_KEYATTR_NEVER_EXTRACTABLE 0x00000040

/* The effects of specifying the NOT_EXTRACTABLE & SENSATIVE bits in an API call
 * is summarized in this table.
 * SENSATIVE  NOT_EXTRACTABLE    Effect
 * ---------- ----------------- --------------------------------------------
 * FALSE      FALSE                Key extractable wrapped or plaintext
 * TRUE       FALSE                Key extractable only when wrapped
 *                                *This mode is an error condition for Cryptoki v1.0
 * TRUE/FALSE TRUE                Key NEVER extractable in any form
 *                                *Sensative forced to TRUE for Cryptoki v1.0
 */

typedef struct cssm_field {
    CSSM_OID FieldOid;
    CSSM_DATA FieldValue;
} CSSM_FIELD, *CSSM_FIELD_PTR;

typedef struct cssm_tp_wrappedproductinfo {
    CSSM_VERSION StandardVersion;                           /* Version of standard this product conforms to */
    CSSM_STRING StandardDescription;  /* Description of standard this product conforms to */
    CSSM_STRING ProductVendor;        /* Vendor of wrapped product/library */
    uint32 ProductFlags;                                    /* ProductFlags */
} CSSM_TP_WRAPPEDPRODUCT_INFO, *CSSM_TP_WRAPPEDPRODUCT_INFO_PTR;

typedef struct cssm_tpsubservice {
    uint32 SubServiceId;
    CSSM_STRING Description; /* Description of this sub service */
    CSSM_CERT_TYPE CertType;       /* Type of certificate accepted by the TP */
    CSSM_USER_AUTHENTICATION_MECHANISM AuthenticationMechanism; 
    uint32 NumberOfPolicyIdentifiers;    
    CSSM_FIELD_PTR PolicyIdentifiers;
    CSSM_TP_WRAPPEDPRODUCT_INFO WrappedProduct;  /* Pointer to wrapped product info */
} CSSM_TPSUBSERVICE, *CSSM_TPSUBSERVICE_PTR;

typedef struct cssm_cssminfo {
    CSSM_VERSION Version; 
    char *Description;       /* Description of CSSM */ 
    char *Vendor;            /* Vendor of CSSM */
    CSSM_BOOL ThreadSafe;
    char *Location;
    CSSM_GUID GUID;
}CSSM_CSSMINFO, *CSSM_CSSMINFO_PTR;

typedef enum cssm_cert_encoding {
    CSSM_CERT_ENCODING_UNKNOWN =   0x00,
    CSSM_CERT_ENCODING_CUSTOM  =   0x01,
    CSSM_CERT_ENCODING_BER     =  0x02,
    CSSM_CERT_ENCODING_DER     =  0x03,
    CSSM_CERT_ENCODING_NDR     =  0x04
} CSSM_CERT_ENCODING, *CSSM_CERT_ENCODING_PTR;

typedef uint32 CSSM_CA_SERVICES;
/*  bit masks for additional CA services at cert enroll  */
#define    CSSM_CA_KEY_ARCHIVE        0x0001
#define    CSSM_CA_CERT_PUBLISH        0x0002
#define    CSSM_CA_CERT_NOTIFY_RENEW    0x0004
#define    CSSM_CA_CRL_DISTRIBUTE        0x0008


/*
    CSSM_CL_WRAPPEDPRODUCT_INFO
*/

/* CL_CA_ProductInfo */
typedef struct cssm_cl_ca_cert_classinfo {
    CSSM_STRING CertClassName;        /* Name of a cert class issued by this CA */
    CSSM_DATA CACert;                                       /* CA Certificate for this cert class */
} CSSM_CL_CA_CERT_CLASSINFO, *CSSM_CL_CA_CERT_CLASSINFO_PTR;

typedef struct cssm_cl_ca_productinfo {
    CSSM_VERSION StandardVersion;                           /* Version of standard this product conforms to */
    CSSM_STRING StandardDescription;  /* Description of standard this product conforms to */
    CSSM_VERSION ProductVersion;                            /* Version of wrapped product/library */
    CSSM_STRING ProductDescription;   /* Description of wrapped product/library */
    CSSM_STRING ProductVendor;        /* Vendor of wrapped product/library */
    CSSM_CERT_TYPE CertType;                                /* Type of certs and CRLs supported by the CA */
    CSSM_CA_SERVICES AdditionalServiceFlags;                /* Mask of additional services a caller can request */
    uint32 NumberOfCertClasses;                             /* Number of different cert types or classes the CA can issue */
    CSSM_CL_CA_CERT_CLASSINFO_PTR CertClasses;                                  
} CSSM_CL_CA_PRODUCTINFO, *CSSM_CL_CA_PRODUCTINFO_PTR;

/* CL_Encoder_ProductInfo */
typedef struct cssm_cl_encoder_productinfo {
    CSSM_VERSION StandardVersion;       /* Version of standard this product conforms to */
    CSSM_STRING StandardDescription;  /* Description of standard this product conforms to */
    CSSM_VERSION ProductVersion;        /* Version of wrapped product/library */
    CSSM_STRING ProductDescription; /* Description of wrapped product/library */
    CSSM_STRING ProductVendor;    /* Vendor of wrapped product/library */       
    CSSM_CERT_TYPE CertType;            /* Type of certs and CRLs supported by the CA */
    uint32 ProductFlags;                /* Mask of selectable encoder features actually used by the CL */
} CSSM_CL_ENCODER_PRODUCTINFO, *CSSM_CL_ENCODER_PRODUCTINFO_PTR;


typedef struct cssm_cl_wrappedproductinfo {
    /* List of encode/decode/parse libraries embedded in the CL module */
    CSSM_CL_ENCODER_PRODUCTINFO_PTR EmbeddedEncoderProducts;    /* library product description */
    uint32 NumberOfEncoderProducts;     /* number of encode/decode/parse libraries used in CL */

    /* List of CAs accessible to the CL module */
    CSSM_CL_CA_PRODUCTINFO_PTR AccessibleCAProducts;            /* CA product description*/
    uint32 NumberOfCAProducts;    /* Number of accessible CAs */
} CSSM_CL_WRAPPEDPRODUCT_INFO, *CSSM_CL_WRAPPEDPRODUCT_INFO_PTR;


typedef struct cssm_clsubservice {
    uint32 SubServiceId;
    CSSM_STRING Description;          /* Description of this sub service */
    CSSM_CERT_TYPE CertType;
    CSSM_CERT_ENCODING CertEncoding;
    CSSM_USER_AUTHENTICATION_MECHANISM AuthenticationMechanism;
    uint32 NumberOfTemplateFields;
    CSSM_OID_PTR CertTemplates;
    uint32 NumberOfTranslationTypes;
    CSSM_CERT_TYPE_PTR CertTranslationTypes;
    CSSM_CL_WRAPPEDPRODUCT_INFO WrappedProduct;
} CSSM_CLSUBSERVICE, *CSSM_CLSUBSERVICE_PTR;

typedef CSSM_RETURN (CSSMAPI *CSSM_NOTIFY_CALLBACK) (
                                                CSSM_MODULE_HANDLE ModuleHandle,
                                                uint32 Application,
                                                uint32 Reason,
                                                void * Param);
#define CSSM_NOTIFY_SURRENDER           0
#define CSSM_NOTIFY_COMPLETE            1
#define CSSM_NOTIFY_DEVICE_REMOVED      2
#define CSSM_NOTIFY_DEVICE_INSERTED     3


#define CSSM_CSP_SESSION_EXCLUSIVE        0x0001 
#define CSSM_CSP_SESSION_READWRITE        0x0002
#define CSSM_CSP_SESSION_SERIAL           0x0004


#define CSSM_DL_STORE_ACCESS_SERIAL       CSSM_CSP_SESSION_SERIAL
#define CSSM_DL_STORE_ACCESS_EXCLUSIVE    CSSM_CSP_SESSION_EXCLUSIVE
#define CSSM_DL_STROE_ACCESS_READWRITE    CSSM_CSP_SESSION_READWRITE

typedef enum cssm_country_origin {
    CSSM_COUNTRY_US = 1,
    CSSM_COUNTRY_NONUS = 2
} CSSM_COUNTRY_ORIGIN;

typedef enum cssm_crypto_type {
    CSP_TYPE_NONE = 0,
    CSP_TYPE_EXPORT = 1,
    CSP_TYPE_SSL = 2,
    CSP_TYPE_FINANCIAL = 3,
    CSP_TYPE_EXPORTVERIFY = 4,
    CSP_TYPE_AUTHENTICATE = 5
} CSSM_CRYPTO_TYPE;

typedef struct cssm_csp_manifest {
    char *Vendor;
    CSSM_COUNTRY_ORIGIN CountryOrigin;
    CSSM_CRYPTO_TYPE CryptoType;
    uint32 NumberCapabilities;
    CSSM_CSP_CAPABILITY_PTR Capabilities;
} CSSM_CSP_MANIFEST, * CSSM_CSP_MANIFEST_PTR;

/* structure for passing a memory function table to cssm */
typedef struct cssm_memory_funcs {
    void *(*malloc_func) (uint32 Size, void *AllocRef);
    void (*free_func) (void *MemPtr, void *AllocRef);
    void *(*realloc_func) (void *MemPtr, uint32 Size, void *AllocRef);
    void *(*calloc_func) (uint32 Num, uint32 Size, void *AllocRef);
    void *AllocRef;
} CSSM_MEMORY_FUNCS, *CSSM_MEMORY_FUNCS_PTR;

typedef CSSM_MEMORY_FUNCS CSSM_API_MEMORY_FUNCS;
typedef CSSM_API_MEMORY_FUNCS *CSSM_API_MEMORY_FUNCS_PTR;

/* structure for passing a memory function table to an add-in */
typedef struct cssm_spi_func_tbl {
    void *(*malloc_func) (CSSM_HANDLE AddInHandle, uint32 Size);
    void (*free_func) (CSSM_HANDLE AddInHandle, void *MemPtr);
    void  *(*realloc_func) (CSSM_HANDLE AddInHandle, void *MemPtr, uint32 Size);
    void  *(*calloc_func) (CSSM_HANDLE AddInHandle, uint32 Num, uint32 Size);
} CSSM_SPI_MEMORY_FUNCS, *CSSM_SPI_MEMORY_FUNCS_PTR;


#ifdef KEY_RECOVERY

typedef struct cssm_kr_wrappedproductinfo {
    CSSM_VERSION StandardVersion;      /* Version of standard this product conforms to */
    CSSM_STRING  StandardDescription;  /* Description of standard this product conforms to */
    CSSM_VERSION ProductVersion;       /* Version of wrapped product/library */
    CSSM_STRING ProductDescription;    /* Description of wrapped product/library */
    CSSM_STRING ProductVendor;         /* Vendor of wrapped product/library */
    uint32 ProductFlags;    
} CSSM_KR_WRAPPEDPRODUCT_INFO, *CSSM_KR_WRAPPEDPRODUCT_INFO_PTR;

typedef struct cssm_krspsubservice {
    uint32 SubServiceId;
    CSSM_STRING Description;      /* Description of this sub service */
    CSSM_KR_WRAPPEDPRODUCT_INFO WrappedProduct;
} CSSM_KRSPSUBSERVICE, *CSSM_KRSPSUBSERVICE_PTR;

#endif /* KEY_RECOVERY */

typedef uint32 CSSM_SERVICE_FLAGS;

#define CSSM_SERVICE_ISWRAPPEDPRODUCT 0x1

/*
    Service Info
*/

typedef struct cssm_serviceinfo {
    CSSM_STRING Description;  /* Service description */
    CSSM_SERVICE_TYPE Type;                         /* Service type */    
    CSSM_SERVICE_FLAGS Flags;                       /* Service flags */
    
    uint32 NumberOfSubServices;                     /* Number of sub services in SubServiceList */ 
    union {                                         /* List of sub services */
        void *SubServiceList;                        
        CSSM_CSPSUBSERVICE_PTR CspSubServiceList;
        CSSM_DLSUBSERVICE_PTR DlSubServiceList;
        CSSM_CLSUBSERVICE_PTR ClSubServiceList;
        CSSM_TPSUBSERVICE_PTR TpSubServiceList;
#ifdef KEY_RECOVERY
        CSSM_KRSPSUBSERVICE_PTR KrSubServiceList;
#endif
    };

    void* Reserved;
} CSSM_SERVICE_INFO, *CSSM_SERVICE_INFO_PTR;

/* 
    Module Flags 
*/

typedef uint32 CSSM_MODULE_FLAGS;

#define CSSM_MODULE_THREADSAFE            0x1
#define CSSM_MODULE_EXPORTABLE            0x2

/* 
    Module Info 
*/

typedef struct cssm_moduleinfo {
    CSSM_VERSION Version;                          /* Module version */
    CSSM_VERSION CompatibleCSSMVersion;            /* Module written for CSSM version */
    CSSM_STRING Description; /* Module description */
    CSSM_STRING Vendor;      /* Vendor name, etc */
    CSSM_MODULE_FLAGS Flags;                       /* Flags to describe and control module use */
    CSSM_SERVICE_MASK ServiceMask;                 /* Bit mask of supported services */
    uint32 NumberOfServices;                       /* Num of services in ServiceList */
    CSSM_SERVICE_INFO_PTR ServiceList;          /* Pointer to list of service infos */
    void* Reserved;
} CSSM_MODULE_INFO, *CSSM_MODULE_INFO_PTR;

/* 
 * CSSM Privilege flag definitions
 */

typedef uint32 CSSM_EXEMPTION_MASK;

#ifdef CSSM_PRIVILEGE

#define CSSM_EXEMPT_NONE	0x00000000	/* no privileges */
#define CSSM_EXEMPT_MULTI_ENCRYPT_CHECK		0x00000001	/* no multiple encryption constraint */
#define CSSM_STRONG_CRYPTO_WITH_KR	0x00000002	/* strong cryptography available but with KR required */
#define CSSM_EXEMPT_LE_KR	0x00000004	/* strong cryptography available without LE KR requirement */
#define CSSM_EXEMPT_ENT_KR	0x00000008	/* strong cryptography available without ENT KR requirement */
#define CSSM_EXEMPT_ALL	0xffffffff	/* all possible privileges */


#endif /* CSSM_PRIVILEGE */

/* Do not edit the following string. It should be expanded at check-in by version control. */
static const char sccs_id_INC_CSSMTYPE_H[] = { "@(#) $Archive: /cdsa/r1_2/inc/cssmtype.h $, $Revision: 1.1.2.1 $, $Modtime: 3/14/97 1:41p $" }; 

#endif /* _CSSMTYPE_H */


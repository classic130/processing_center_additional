/* SCCSID: inc/ibmcl.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.11 8/12/98 19:10:28 */
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

#ifndef _IBMCL_H
#define _IBMCL_H

/* 
 * GUID of IBM CL service provider
 */
static CSSM_GUID ibmcl_guid =
{ 0x790eee0, 0xebf8, 0x11d0, { 0xb1, 0xce, 0x0, 0x20, 0x35, 0x68, 0xb, 0x0 } };

/*
 * current version number
 */

#define IBM_CL_MAJOR_VERSION	(1)
#define IBM_CL_MINOR_VERSION	(0)

/* 
 *	OID definitions
 */

#define IBMCL_OID_ISSUER_NAME			0
#define IBMCL_OID_VERSION				1
#define IBMCL_OID_SERIAL_NUM			2
#define	IBMCL_OID_SIGNATURE_ALGID		3
#define	IBMCL_OID_VALIDITY				4 /* supply GMT */
#define	IBMCL_OID_SUBJECT_NAME			5
#define	IBMCL_OID_SUBJECT_PUB_KEY		6
#define IBMCL_OID_PUB_KEY_ALGID			7
#define IBMCL_OID_PUB_KEY_PARAMETERS	8
#define	IBMCL_OID_ISSUER_UNIQUE_ID		9
#define	IBMCL_OID_SUBJECT_UNIQUE_ID		10
#define	IBMCL_OID_UNSIGNED_CERT_DER		11
#define IBMCL_OID_SIGNATURE				12
#define IBMCL_OID_SIGNATURE_PARAMETERS	13
#define IBMCL_OID_EXTENSIONS			14 

#define IBMCL_OID_COUNT					15

/* 
 * OID definitions for X.500 NAME attributes
 */

#define IBMCL_OID_NAME_COUNTRY			0
#define IBMCL_OID_NAME_ORGANIZATION		1
#define IBMCL_OID_NAME_ORG_UNIT			2
#define IBMCL_OID_NAME_LOCALITY			3
#define IBMCl_OID_NAME_SURNAME			4
#define IBMCL_OID_NAME_COMMON_NAME		5
#define IBMCL_OID_NAME_STATEorPROVINCE	6
#define IBMCL_OID_NAME_STREET_ADDRESS	7
#define	IBMCL_OID_NAME_TITLE			8
#define IBMCL_OID_NAME_DESCRIPTION		9
#define IBMCL_OID_NAME_SERIAL_NUMBER	10

#define IBMCL_OID_NAME_COUNT			11
/* 
 * OID definitions for the supported X.509 extensions
 */
#define IBMCL_OID_EXTENSION_UNKNOWN				0
#define IBMCL_OID_EXTENSION_BASIC_CONSTRAINTS	1
#define IBMCL_OID_EXTENSION_AUTH_KEY_ID			2
#define IBMCL_OID_EXTENSION_KEY_USAGE			3

 
/* 
 * Supported Data structures
 */	


/* attribute structure for X500 names */
typedef struct X500AttributeTag {
	uint32	type;
	uint32	length;
	void	*data;
} X500Attribute;

/* structure of X500 relative distinguished name */
typedef struct RDNameTag {
	struct RDNameTag    *next;
	X500Attribute		*value;
	uint32				numberOfAttributes;
} RDName;

/* X500 name structure which in turn is a list of relative distinguished names.
 * CssmField.value points to this sructure as shown:
 *		
 *		cssmField.oid	:= IBM_OID_ISSUER_NAME or SUBJECT_NAME
 *		cssmField.value := pointer to X500Name structure
 *
 */

typedef struct X500Name {
	struct RDNameTag	*RDNSequence;
} X500Name;


/*
 * Supported X509 Extensions 
 */ 

/* pass all the extensions as a linked list*/
typedef struct extension{
	CSSM_BOOL	critical;
	uint32		objectId;
	CSSM_DATA	extensionValue;
} X509Extension;

typedef struct extensionsTag {
	uint32			NumberOfExtensions;
	X509Extension	*ext;
} *ExtensionsList;

typedef struct ObjectIDTag {
	struct ObjectIDTag	*next;
	uint32		value;
} GenericObjectID;
/* data strcutures for supported extensions */



#define      NAME_ASSIGNER_PRESENT 0x80	/* bit mask value */
typedef struct EDIPartyNameTag {
    uint8   bit_mask;
	/* only printable strings supported */
    uint8        nameAssigner[65];  /* optional */
    uint8        partyName[65];
} X509EDIPartyName;

#define      OTHER_NAME_CHOSEN		1		/* choice values */
#define      RFC822_NAME_CHOSEN		2
#define      DNS_NAME_CHOSEN		3
#define      X400_ADDRESS_CHOSEN	4
#define      DIRECTORY_NAME_CHOSEN	5
#define      EDIPARTY_NAME_CHOSEN	6
#define      URI_CHOSEN				7
#define      IP_ADDRESS_CHOSEN		8
#define      REGISTERED_ID_CHOSEN	9


typedef struct X509GeneralNameTag {
    uint16  choice;
    union _union {
        struct otherNameTag {
            GenericObjectID *type_id;
            CSSM_DATA        value;	/* DER encoding should be supplied */
        } otherName;
        char				*rfc822Name;
        char				*dNSName;
        CSSM_DATA			x400Address;	/* DER encoding of the address */
        X500Name			directoryName;
        X509EDIPartyName    ediPartyName;	/* only printable string type is supported */
        char				*uniformResourceIdentifier;
        CSSM_DATA			iPAddress;
        GenericObjectID		*registeredID;
    } u;

} X509GeneralName;

typedef struct GeneralNamesTag {
    struct GeneralNamesTag *next;
    X509GeneralName     value;
} *X509GeneralNames;

/* Authority key identifier */
#define      KEY_IDENTIFIER_PRESENT		0x80
#define      CERT_ISSUER_PRESENT		0x40
#define      CERT_SERIAL_NUMBER_PRESENT 0x20

typedef struct AuthorityKeyIdentifierTag {
    uint8		bit_mask;
    CSSM_DATA   keyIdentifier;  /* optional */
    X509GeneralNames	authorityCertIssuer;  /* optional */
    CSSM_DATA   authorityCertSerialNumber;  /* optional */
} X509AuthorityKeyIdentifier;

/* basic constraints */
#define      CA_PRESENT						0x80
#define      PATH_LENGTH_CONSTRAINT_PRESENT 0x40
typedef struct BasicConstraints {
    uint8			bit_mask;
    CSSM_BOOL		cA;  /* default assumed if omitted */
    uint32			pathLenConstraint;  /* optional */
} X509BasicConstraints;


/* Key Usage */
typedef enum keyUsagesTag {
	DIGITAL_SIGNATURE=0x80,
	NON_REPUDIATION	 =0x40,
	KEY_ENCIPHERMENT =0x20,
	DATA_ENCIPHERMENT=0x10,
	KEY_AGREEMENT	 =0x08,
	KEY_CERT_SIGN	 =0x04,
	CRL_SIGN		 =0x02
} KeyUsageValues;

typedef KeyUsageValues   X509KeyUsage;

#endif

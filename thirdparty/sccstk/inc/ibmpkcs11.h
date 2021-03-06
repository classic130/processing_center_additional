/* SCCSID: inc/ibmpkcs11.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.6 8/12/98 19:14:04 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef __IBMPKCS11_H
#define __IBMPKCS11_H

#include "cssm.h"

/*
 *	Version numbers
 */

#define IBMPKCS11_MAJOR_VERSION			1
#define IBMPKCS11_MINOR_VERSION			0


/*
 *	GUID
 */

/* 31ff5080-a631-11d0-9808-0004ac61389a */
#define IBMPKCS11_GUID {0x31ff5080, 0xa631, 0x11d0, {0x98, 0x08, 0x00, 0x04, 0xac, 0x61, 0x38, 0x9a}}


/*
 *	RSA public exponents used when generating key pair
 */

#define IBMPKCS11_RSAF0					{0x03}
#define IBMPKCS11_RSAF4					{0x01, 0x00, 0x01}


/*
 *	Buffer size limits
 */

#define IBMPKCS11_RC4MAXBUFLEN						512			/* Max RC4 bytes to be enc/dec */
#define IBMPKCS11_REQWRAPPEDPRIVATEKEYBUFLEN		(32*1024)	/* Required buffer size for a 
																   wrapped private key */

/* 
 *	IBMPKCS11 specific return codes
 */

#define IBMPKCS11_OK                               (CSSM_CSP_PRIVATE_ERROR + 0x0000)
#define IBMPKCS11_CANCEL                           (CSSM_CSP_PRIVATE_ERROR + 0x0001)
#define IBMPKCS11_HOST_MEMORY                      (CSSM_CSP_PRIVATE_ERROR + 0x0002)
#define IBMPKCS11_SLOT_ID_INVALID                  (CSSM_CSP_PRIVATE_ERROR + 0x0003)
#define IBMPKCS11_FLAGS_INVALID                    (CSSM_CSP_PRIVATE_ERROR + 0x0004)
#define IBMPKCS11_ATTRIBUTE_READ_ONLY              (CSSM_CSP_PRIVATE_ERROR + 0x0010)
#define IBMPKCS11_ATTRIBUTE_SENSITIVE              (CSSM_CSP_PRIVATE_ERROR + 0x0011)
#define IBMPKCS11_ATTRIBUTE_TYPE_INVALID           (CSSM_CSP_PRIVATE_ERROR + 0x0012)
#define IBMPKCS11_ATTRIBUTE_VALUE_INVALID          (CSSM_CSP_PRIVATE_ERROR + 0x0013)
#define IBMPKCS11_DATA_INVALID                     (CSSM_CSP_PRIVATE_ERROR + 0x0020)
#define IBMPKCS11_DATA_LEN_RANGE                   (CSSM_CSP_PRIVATE_ERROR + 0x0021)
#define IBMPKCS11_DEVICE_ERROR                     (CSSM_CSP_PRIVATE_ERROR + 0x0030)
#define IBMPKCS11_DEVICE_MEMORY                    (CSSM_CSP_PRIVATE_ERROR + 0x0031)
#define IBMPKCS11_DEVICE_REMOVED                   (CSSM_CSP_PRIVATE_ERROR + 0x0032)
#define IBMPKCS11_ENCRYPTED_DATA_INVALID           (CSSM_CSP_PRIVATE_ERROR + 0x0040)
#define IBMPKCS11_ENCRYPTED_DATA_LEN_RANGE         (CSSM_CSP_PRIVATE_ERROR + 0x0041)
#define IBMPKCS11_FUNCTION_CANCELED                (CSSM_CSP_PRIVATE_ERROR + 0x0050)
#define IBMPKCS11_FUNCTION_NOT_PARALLEL            (CSSM_CSP_PRIVATE_ERROR + 0x0051)
#define IBMPKCS11_FUNCTION_PARALLEL                (CSSM_CSP_PRIVATE_ERROR + 0x0052)
#define IBMPKCS11_KEY_HANDLE_INVALID               (CSSM_CSP_PRIVATE_ERROR + 0x0060)
#define IBMPKCS11_KEY_SENSITIVE                    (CSSM_CSP_PRIVATE_ERROR + 0x0061)
#define IBMPKCS11_KEY_SIZE_RANGE                   (CSSM_CSP_PRIVATE_ERROR + 0x0062)
#define IBMPKCS11_KEY_TYPE_INCONSISTENT            (CSSM_CSP_PRIVATE_ERROR + 0x0063)
#define IBMPKCS11_MECHANISM_INVALID                (CSSM_CSP_PRIVATE_ERROR + 0x0070)
#define IBMPKCS11_MECHANISM_PARAM_INVALID          (CSSM_CSP_PRIVATE_ERROR + 0x0071)
#define IBMPKCS11_OBJECT_CLASS_INCONSISTENT        (CSSM_CSP_PRIVATE_ERROR + 0x0080)
#define IBMPKCS11_OBJECT_CLASS_INVALID             (CSSM_CSP_PRIVATE_ERROR + 0x0081)
#define IBMPKCS11_OBJECT_HANDLE_INVALID            (CSSM_CSP_PRIVATE_ERROR + 0x0082)
#define IBMPKCS11_OPERATION_ACTIVE                 (CSSM_CSP_PRIVATE_ERROR + 0x0090)
#define IBMPKCS11_OPERATION_NOT_INITIALIZED        (CSSM_CSP_PRIVATE_ERROR + 0x0091)
#define IBMPKCS11_PIN_INCORRECT                    (CSSM_CSP_PRIVATE_ERROR + 0x00A0)
#define IBMPKCS11_PIN_INVALID                      (CSSM_CSP_PRIVATE_ERROR + 0x00A1)
#define IBMPKCS11_PIN_LEN_RANGE                    (CSSM_CSP_PRIVATE_ERROR + 0x00A2)
#define IBMPKCS11_SESSION_CLOSED                   (CSSM_CSP_PRIVATE_ERROR + 0x00B0)
#define IBMPKCS11_SESSION_COUNT                    (CSSM_CSP_PRIVATE_ERROR + 0x00B1)
#define IBMPKCS11_SESSION_EXCLUSIVE_EXISTS         (CSSM_CSP_PRIVATE_ERROR + 0x00B2)
#define IBMPKCS11_SESSION_HANDLE_INVALID           (CSSM_CSP_PRIVATE_ERROR + 0x00B3)
#define IBMPKCS11_SESSION_PARALLEL_NOT_SUPPORTED   (CSSM_CSP_PRIVATE_ERROR + 0x00B4)
#define IBMPKCS11_SESSION_READ_ONLY                (CSSM_CSP_PRIVATE_ERROR + 0x00B5)
#define IBMPKCS11_SIGNATURE_INVALID                (CSSM_CSP_PRIVATE_ERROR + 0x00C0)
#define IBMPKCS11_SIGNATURE_LEN_RANGE              (CSSM_CSP_PRIVATE_ERROR + 0x00C1)
#define IBMPKCS11_TEMPLATE_INCOMPLETE              (CSSM_CSP_PRIVATE_ERROR + 0x00D0)
#define IBMPKCS11_TEMPLATE_INCONSISTENT            (CSSM_CSP_PRIVATE_ERROR + 0x00D1)
#define IBMPKCS11_TOKEN_NOT_PRESENT                (CSSM_CSP_PRIVATE_ERROR + 0x00E0)
#define IBMPKCS11_TOKEN_NOT_RECOGNIZED             (CSSM_CSP_PRIVATE_ERROR + 0x00E1)
#define IBMPKCS11_TOKEN_WRITE_PROTECTED            (CSSM_CSP_PRIVATE_ERROR + 0x00E2)
#define IBMPKCS11_UNWRAPPING_KEY_HANDLE_INVALID    (CSSM_CSP_PRIVATE_ERROR + 0x00F0)
#define IBMPKCS11_UNWRAPPING_KEY_SIZE_RANGE        (CSSM_CSP_PRIVATE_ERROR + 0x00F1)
#define IBMPKCS11_UNWRAPPING_KEY_TYPE_INCONSISTENT (CSSM_CSP_PRIVATE_ERROR + 0x00F2)
#define IBMPKCS11_USER_ALREADY_LOGGED_IN           (CSSM_CSP_PRIVATE_ERROR + 0x0100)
#define IBMPKCS11_USER_NOT_LOGGED_IN               (CSSM_CSP_PRIVATE_ERROR + 0x0101)
#define IBMPKCS11_USER_PIN_NOT_INITIALIZED         (CSSM_CSP_PRIVATE_ERROR + 0x0102)
#define IBMPKCS11_USER_TYPE_INVALID                (CSSM_CSP_PRIVATE_ERROR + 0x0103)
#define IBMPKCS11_WRAPPED_KEY_INVALID              (CSSM_CSP_PRIVATE_ERROR + 0x0110)
#define IBMPKCS11_WRAPPED_KEY_LEN_RANGE            (CSSM_CSP_PRIVATE_ERROR + 0x0112)
#define IBMPKCS11_WRAPPING_KEY_HANDLE_INVALID      (CSSM_CSP_PRIVATE_ERROR + 0x0113)
#define IBMPKCS11_WRAPPING_KEY_SIZE_RANGE          (CSSM_CSP_PRIVATE_ERROR + 0x0114)
#define IBMPKCS11_WRAPPING_KEY_TYPE_INCONSISTENT   (CSSM_CSP_PRIVATE_ERROR + 0x0115)
#define IBMPKCS11_VENDOR_DEFINED                   (CSSM_CSP_PRIVATE_ERROR + 0x8000)


/*
 *
 *	The followings are various values mapped one to one from RSADSI
 *	PKCS11 Ver. 1.X defined values. They are to be used in DL operations
 *	supported by the addin.
 *
 */


/*
 *	PKCS11 data types
 */

typedef unsigned char					IBMPKCS11_CK_BYTE;
typedef IBMPKCS11_CK_BYTE				IBMPKCS11_CK_CHAR;
typedef IBMPKCS11_CK_BYTE				IBMPKCS11_CK_BBOOL;
typedef unsigned short int				IBMPKCS11_CK_USHORT;
typedef unsigned long int				IBMPKCS11_CK_ULONG;
typedef IBMPKCS11_CK_ULONG				IBMPKCS11_CK_FLAGS;
typedef IBMPKCS11_CK_BYTE*				IBMPKCS11_CK_BYTE_PTR;
typedef IBMPKCS11_CK_CHAR*				IBMPKCS11_CK_CHAR_PTR;
typedef IBMPKCS11_CK_USHORT*			IBMPKCS11_CK_USHORT_PTR;
typedef void*							IBMPKCS11_CK_VOID_PTR;
typedef IBMPKCS11_CK_ULONG				IBMPKCS11_CK_SLOT_ID;
typedef IBMPKCS11_CK_SLOT_ID*			IBMPKCS11_CK_SLOT_ID_PTR;
typedef IBMPKCS11_CK_ULONG				IBMPKCS11_CK_SESSION_HANDLE;
typedef IBMPKCS11_CK_SESSION_HANDLE*	IBMPKCS11_CK_SESSION_HANDLE_PTR;
typedef IBMPKCS11_CK_ULONG				IBMPKCS11_CK_OBJECT_HANDLE;
typedef IBMPKCS11_CK_OBJECT_HANDLE*		IBMPKCS11_CK_OBJECT_HANDLE_PTR;
typedef IBMPKCS11_CK_USHORT				IBMPKCS11_CK_OBJECT_CLASS;
typedef IBMPKCS11_CK_OBJECT_CLASS*		IBMPKCS11_CK_OBJECT_CLASS_PTR;
typedef IBMPKCS11_CK_USHORT				IBMPKCS11_CK_KEY_TYPE;
typedef IBMPKCS11_CK_USHORT				IBMPKCS11_CK_CERTIFICATE_TYPE;
typedef IBMPKCS11_CK_USHORT				IBMPKCS11_CK_ATTRIBUTE_TYPE;
typedef IBMPKCS11_CK_USHORT				IBMPKCS11_CK_MECHANISM_TYPE;
typedef IBMPKCS11_CK_MECHANISM_TYPE*	IBMPKCS11_CK_MECHANISM_TYPE_PTR;
typedef IBMPKCS11_CK_USHORT				IBMPKCS11_CK_RV;


/* 
 *	Object types 
 */

#define IBMPKCS11_CKO_DATA					0x0000 
#define IBMPKCS11_CKO_CERTIFICATE           0x0001
#define IBMPKCS11_CKO_PUBLIC_KEY            0x0002
#define IBMPKCS11_CKO_PRIVATE_KEY           0x0003
#define IBMPKCS11_CKO_SECRET_KEY            0x0004
#define IBMPKCS11_CKO_VENDOR_DEFINED        0x8000


/* 
 *	Key types 
 */

#define IBMPKCS11_CKK_RSA					0x0000 
#define IBMPKCS11_CKK_DSA					0x0001
#define IBMPKCS11_CKK_DH					0x0002
#define IBMPKCS11_CKK_GENERIC_SECRET		0x0010
#define IBMPKCS11_CKK_RC2					0x0011
#define IBMPKCS11_CKK_RC4					0x0012
#define IBMPKCS11_CKK_DES					0x0013
#define IBMPKCS11_CKK_DES2					0x0014
#define IBMPKCS11_CKK_DES3					0x0015
#define IBMPKCS11_CKK_VENDOR_DEFINED		0x8000


/* 
 *	Certificate types 
 */

#define IBMPKCS11_CKC_X_509					0x0000
#define IBMPKCS11_CKC_VENDOR_DEFINED		0x8000


/* 
 *	Attribute types 
 */

#define IBMPKCS11_CKA_CLASS                  0x0000
#define IBMPKCS11_CKA_TOKEN                  0x0001
#define IBMPKCS11_CKA_PRIVATE                0x0002
#define IBMPKCS11_CKA_LABEL                  0x0003
#define IBMPKCS11_CKA_APPLICATION            0x0010
#define IBMPKCS11_CKA_VALUE                  0x0011
#define IBMPKCS11_CKA_CERTIFICATE_TYPE       0x0080
#define IBMPKCS11_CKA_ISSUER                 0x0081
#define IBMPKCS11_CKA_SERIAL_NUMBER          0x0082   
#define IBMPKCS11_CKA_KEY_TYPE               0x0100
#define IBMPKCS11_CKA_SUBJECT                0x0101
#define IBMPKCS11_CKA_ID                     0x0102
#define IBMPKCS11_CKA_SENSITIVE              0x0103   
#define IBMPKCS11_CKA_ENCRYPT                0x0104
#define IBMPKCS11_CKA_DECRYPT                0x0105
#define IBMPKCS11_CKA_WRAP                   0x0106
#define IBMPKCS11_CKA_UNWRAP                 0x0107
#define IBMPKCS11_CKA_SIGN                   0x0108
#define IBMPKCS11_CKA_SIGN_RECOVER           0x0109
#define IBMPKCS11_CKA_VERIFY                 0x010A
#define IBMPKCS11_CKA_VERIFY_RECOVER         0x010B
#define IBMPKCS11_CKA_DERIVE                 0x010C
#define IBMPKCS11_CKA_START_DATE             0x0110
#define IBMPKCS11_CKA_END_DATE               0x0111
#define IBMPKCS11_CKA_MODULUS                0x0120
#define IBMPKCS11_CKA_MODULUS_BITS           0x0121
#define IBMPKCS11_CKA_PUBLIC_EXPONENT        0x0122
#define IBMPKCS11_CKA_PRIVATE_EXPONENT       0x0123
#define IBMPKCS11_CKA_PRIME_1                0x0124
#define IBMPKCS11_CKA_PRIME_2                0x0125
#define IBMPKCS11_CKA_EXPONENT_1             0x0126
#define IBMPKCS11_CKA_EXPONENT_2             0x0127
#define IBMPKCS11_CKA_COEFFICIENT            0x0128
#define IBMPKCS11_CKA_PRIME                  0x0130
#define IBMPKCS11_CKA_SUBPRIME               0x0131
#define IBMPKCS11_CKA_BASE                   0x0132
#define IBMPKCS11_CKA_VALUE_BITS             0x0160
#define IBMPKCS11_CKA_VALUE_LEN              0x0161
#define IBMPKCS11_CKA_VENDOR_DEFINED         0x8000

#endif

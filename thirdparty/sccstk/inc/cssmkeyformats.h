/* SCCSID: inc/cssmkeyformats.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.9 8/12/98 19:10:35 */
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

#ifndef __CSSMKEYFORMATS_H
#define __CSSMKEYFORMATS_H


//The Symmetric keys can be treated as array of bytes so we
// do not need new types.

//
// RSA Key Formats
//

typedef struct cssm_rsa_public {
	CSSM_DATA		modulus;							/* Modulus n */
	uint32			modulusBits;						/* Size of modulus n in bits */
	CSSM_DATA		publicExponent;						/* Public exponent e */
} CSSM_RSA_PUBLIC, *CSSM_RSA_PUBLIC_PTR;


typedef struct cssm_rsa_private {
	CSSM_DATA		modulus;							/* Modulus n */
	CSSM_DATA		publicExponent;						/* Public exponent e */
	CSSM_DATA		privateExponent;					/* Private exponent d */
	CSSM_DATA		primeOne;							/* Prime p */
	CSSM_DATA		primeTwo;							/* Prime q */	
	CSSM_DATA		exponentOne;		                /* Private exponent d modulo p-1 */
	CSSM_DATA		exponentTwo;						/* Private exponent d modulo q-1 */
	CSSM_DATA		coefficient;                        /* CRT coefficient (1/q) modulo p */
} CSSM_RSA_PRIVATE, *CSSM_RSA_PRIVATE_PTR;


//
// DSA Key Formats
//

typedef struct cssm_dsa_public {
	CSSM_DATA		prime;								/* Prime p */
	CSSM_DATA		subPrime;							/* Subprime q */
	CSSM_DATA		base;								/* Base g */
	CSSM_DATA		publicValue;						/* Public value y */
} CSSM_DSA_PUBLIC, *CSSM_DSA_PUBLIC_PTR;


typedef struct cssm_dsa_private {
	CSSM_DATA		prime;								/* Prime p */
	CSSM_DATA		subPrime;							/* Subprime q */
	CSSM_DATA		base;								/* Base g */
	CSSM_DATA		privateValue;						/* Private value x */
} CSSM_DSA_PRIVATE, *CSSM_DSA_PRIVATE_PTR;


//
// DH Params and Key Formats
//

typedef struct cssm_dh_params {
	CSSM_DATA		prime;								/* Prime p */
	CSSM_DATA		base;								/* Base g */
	uint32			exponentBits;						/* Size of exponent in bits */
} CSSM_DH_PARAMS, *CSSM_DH_PARAMS_PTR;


typedef struct cssm_dh_public {
	CSSM_DATA		prime;								/* Prime p */
	CSSM_DATA		base;								/* Base g */
	CSSM_DATA		publicValue;						/* Public value y */
} CSSM_DH_PUBLIC, *CSSM_DH_PUBLIC_PTR;


typedef struct cssm_dh_private {
	CSSM_DATA		prime;								/* Prime p */
	CSSM_DATA		base;								/* Base g */
	CSSM_DATA		privateValue;						/* Private value x */
	uint32			exponentBits;						/* Size of exponent in bits */
} CSSM_DH_PRIVATE, *CSSM_DH_PRIVATE_PTR;

#endif


/*
$Revision: 1.2.72.1 $
$Header: /cvs/itgclient/server/apps/cpm/include/cdr.h,v 1.2.72.1 2003/07/17 20:31:44 sgoginen Exp $
*/
 
/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1996. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {  
  /* This allows for C++ inclusion/use of this header file */
#endif
 

#ifndef _CDR_H_
#define _CDR_H_ 1

	/*	
			Functions return zero for success. 
			Output fields are listed first.	 
			If successful the functions will return null terminated strings.
			The caller owns the memory and should free all strings returned.
			If a call fails, the output char * will be set to NULL (char *)0 . 
 

			all functions take a base 64 encoded cert DER in a null 
			terminated string as their last parameter 
			
			the output strings (eg char **commonNameString) should be passed 
			in as the address of a (char *), NOT a (char **) 
			organizationUnitStrings should be passed in as the address of a 
			char **.																												

	 
			VARIABLE							 EXAMPLE VALUE						
			------------------------------------------------------------------------
		 commonNameString				"Goofy"
		 emailAddressString			"goofy@nowhere"
		 addressString			"1122 Boogie Woogie Avenue\rMiami, Fl\r33133\rUS"
		 uniqueIDString					 32 byte character field
		 organizationString			"VeriSign, Inc."
		 organizationUnitString [0]="VeriSign Class 1 Individual Subscriber"
														[1]="TEST ONLY" 
		 organizationUnitStringCount	2
		 notBeforeString				951201000000*
		 notAfterString					961130000000*
		 * format is YYMMDDHHMMSS in UTC time.	Note also that 011111000000 would
		 represent November 11, 2001 at precisely 00:00:00 UTC
		 
		 
		 NOTE:	All functions are actually thin wrappers around the
		 GetAllFieldsAlloc() function.	Output fields that
		 are == NULL (as opposed to pointers) will NOT be filled, that is,
		 it is OK to send a 0 (zero) as an ouput argument (instead of the
		 address of a real pointer).
		 */

#ifdef WIN32
#ifdef EXPORT
#define Dll	__declspec( dllexport )
#else
#define Dll	__declspec( dllimport )
#endif  /* EXPORT */
#else /* not WIN32 */
#define Dll
#endif /* not WIN32 */
#include "extparser.h"
Dll int GetCommonNameStringAlloc (char **commonNameString, char *b64CertDER);
Dll int GetEmailAddressStringAlloc (char **emailAddressString, char *b64CertDER);
Dll int GetAddressStringAlloc (char **addressString, char *b64CertDER);
Dll int GetUniqueIDStringAlloc (char **uniqueIDString, char *b64CertDER);
Dll int GetOrganizationUnitStringsAlloc (char ***ouStrings,
																				 int *ouCount, char *b64CertDER);
Dll int GetOrganizationString (char **organizationString, char *b64CertDER);
Dll void CDR_Free (char *pointer);

Dll int GetAllFieldsAlloc (char **emailAddressString, char **commonNameString,
                           char **uniqueIDString, char **addressString, 
                           char ***ouStrings, int *ouCount, char *b64CertDER);

Dll int VSGetAllFieldsAlloc (
        char **emailAddress, char **commonName, char **title,
        char **uniqueID, char **address, char **organization, 
        char ***organizationUnits, int *orgUnitCount, 
        char **issuerOrganization, char **issuerLocality,
        char **issuerCountry, char **issuerCommonName,
        char ***issuerOrganizationUnits, int *issuerOrgUnitCount, 
        char **notBefore, char **notAfter, VSCertV3Extensions_MV *v3Extenstions, 
        char *b64CertDER);

#ifndef _ITEM_
#define _ITEM_ 1
typedef struct {
  unsigned char *data;
  unsigned int len;
} ITEM;
#endif

#define MAX_OU 10
  /* support a maximum of 10 Organization Unit fields */ 

#define CDRE_DER 0x1
  /* trouble parsing DER */
#define CDRE_ISSUER_FORMAT 0x2
  /* issuer format not recognized */
#define CDRE_ALLOC 0x3
  /* memory allocation failed */
#define CDRE_BAD_B64 0x4
  /* base 64 decoding failed */

#define	OSS_ERROR				0x06
#define	EXTENSIONS_NOTPRESENT	0x07 

#ifdef __cplusplus
}
#endif
/* end of C wrapper for C++ */
 
#endif
/* _CDR_H_ protect against unnecessary multiple inclusion */

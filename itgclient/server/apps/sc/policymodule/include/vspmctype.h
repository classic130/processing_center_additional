/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmctype.h,v 1.1.2.1 2001/09/06 22:32:14 ajayaram Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSPMCTYPE_H_
#define _VSPMCTYPE_H_


#ifdef __cplusplus
extern "C" {
#endif

int isPrintableString(const char* value);
int isT61String(const char* value);
int isValidEmailAddress(const char* value);
int isBase64String(const char* value);
int isValidNumber(const char* number);
int isValidPhoneNumber(const char* value);
int isValidDate(const char* value);

#ifdef  __cplusplus
}
#endif

#endif /* _VSPMCTYPE_H_ */


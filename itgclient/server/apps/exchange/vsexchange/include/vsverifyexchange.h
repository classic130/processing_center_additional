/*
 * $Revision: 1.2.456.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/vsexchange/include/vsverifyexchange.h,v 1.2.456.1 2003/06/06 22:46:31 npaul Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSVERIFYEXCHANGE_H_
#define _VSVERIFYEXCHANGE_H_

#include "../include/vsverify.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VS_VERIFY_EXCHANGE_NAME	"VerifyExchange"
#define VS_EXCHANGE_DLL			"vsexchange.dll"

typedef VSAA_STATUS (*VS_VERIFY_EXCHANGE_FUNC)(
			const VSAA_NAME userInput[], 
			FILE *fp);

VSAA_STATUS VerifyExchange(
			const VSAA_NAME userInput[], 
			FILE *fp);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
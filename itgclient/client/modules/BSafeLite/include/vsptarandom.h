
/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VS_PTA_RANDOM_H_
#define _VS_PTA_RANDOM_H_

#define VSERR_SUCCESS         0
#define VSERR_INTERNAL_ERROR  1
#define VSERR_OUT_OF_MEMORY   2
#define VSERR_TOOBIG          3
#define VSERR_MD5             4

int  Init_PRNG (void);
void Uninit_PRNG (void);
int  GetRandom (unsigned char *block, unsigned int blockLen);

#endif

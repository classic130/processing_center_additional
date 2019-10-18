/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/exchange/srchexce/Attic/post-que.h,v 1.1.2.1 2000/03/15 00:13:38 aranade Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1996. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _POST_QUE_H_
#define _POST_QUE_H_ 1
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ENTRY_
#define _ENTRY_ 1
typedef struct {
  char* 	name;
  char*		val;
  char*		message;	
} ENTRY;

#endif

int GetEntriesAlloc PROTO_LIST ((ENTRY **, int *));
int AddEntry PROTO_LIST ((ENTRY **, int *, const char *, const char *));
int GetEntriesFromString PROTO_LIST ((const char*, ENTRY**, int*));

#ifdef __cplusplus
}
#endif
#endif

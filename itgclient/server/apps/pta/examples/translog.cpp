/*
 * $Revision: 1.1.4.1 $
 * $Header: /cvs/itgclient/server/apps/pta/examples/Attic/translog.cpp,v 1.1.4.1 2000/07/07 20:56:11 mwilson Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <vsverify.h>
#include "../include/vsutil.h"

#define TRANSLOGFILENAME "signtrns.log" 

VSAA_STATUS WriteTransactionLogFile(VSAA_ENTRY *anInput)
{
  FILE *fp ;
  if( (fp = fopen(TRANSLOGFILENAME, "a")) != NULL )
  {
    fprintf(fp, "---BEGIN RECORD---\nAt: %s Verified Transaction with following input\n", ctime(time(NULL))) ;
    for( i = 0 ; anInput[i] != NULL ; i++ )
    {
      fprintf(fp, "Name: %s, Value: %s\n", anInput[i].pszName, anInput[i].pszValue) ;
    }
    fprintf(fp, "---END RECORD---\n") ;
  }
}

/*
 * $Revision: 1.1.4.1 $
 * $Header: /cvs/itgclient/server/apps/pta/examples/Attic/pestub.cpp,v 1.1.4.1 2000/07/07 20:56:10 mwilson Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*--------------------------------------------------------------------\
 This is a sample file to log verified requests
\-------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <vsverify.h>


#define TRANSLOGFILENAME "../log/signtrns.log" 

/*******************************************************************/
VSAA_STATUS ProcessEntries(VSAA_NAME anInput[], VSAA_NAME **panOutput)
/*******************************************************************/
{
  FILE *fp ;
  int i ;
  time_t currenttime ;
  VSAA_STATUS rval = VSAA_SUCCESS ;
  if( (fp = fopen(TRANSLOGFILENAME, "a")) != NULL )
  {
    currenttime = time(NULL) ;
    fprintf(fp, "---BEGIN RECORD---\nAt: %s Verified Transaction with following input\n", ctime(&currenttime)) ;
    for( i = 0 ; anInput[i].pszName != NULL ; i++ )
    {
      fprintf(fp, "Name: %s, Value: %s\n", anInput[i].pszName, anInput[i].pszValue) ;
    }
    fprintf(fp, "---END RECORD---\n") ;
  }
  else
  {
    rval = VSAA_LOG_FAILED ;
  }
  *panOutput = anInput ;

  return rval ;
}


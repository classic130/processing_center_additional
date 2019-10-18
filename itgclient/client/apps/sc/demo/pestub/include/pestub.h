///////define global variable and Constant////////////////
/*
 * Section 1. Hook API. This API should be implemented by the customer.
 */

/*
 * The VSAA_Name structure is used to store a name value pair.
 */

#ifndef _PESTUB_MSG_H_
#define _PESTUB_MSG_H_


typedef struct
{
  char *pszName ;
  char *pszValue ;
} VSAA_NAME ;

typedef enum 
{
  VSAA_SUCCESS=0, 
  VSSMSG_SUCCESS = 0,
  VSSC_ERROR=1	
   
  
} VSAA_STATUS;

/*
 * The arrays of VSAA_NAME are always terminated with an empty entry
 * (i.e. a struct in which pszName and pszValue are NULL). The output
 * structure need not physically copy the strings from the input if
 * they are not modified, it may simply point to those strings. Do not
 * delete / free any of the strings passed as input.
 */
//////////Function Proto type /////////////////////////

/*
 * Hook API function: ProcessEntries

 * If the function succeeds, it returns VSAA_SUCCESS and
 * (*panOutput) contains the name value pairs.
 *
 * The entry list is guaranteed to have "operation" as the first name-value
 * pair and it should be used to switch what the function is expected to do.
 *
 * If the function fails, the function should return one of the
 * error codes above. the (*panOutput) parameter should
 * still contain name value pairs that are sent to VeriSign site.
 *
 * If there is any unexpected error, VSAA_STATUS should be
 * (VSAA_ONSITE_BASE+n), where n >= 0. This error code will be mapped to
 * an error code that can be specified in the "Form Description File"
 * and (*panOutput) will contain name value pairs that can be substituted
 * in the output file.
 */

VSAA_STATUS  ProcessEntries(VSAA_NAME anInput[], VSAA_NAME **panOutput) ;


/*
 * The FreeEntries() function is used to free data returning from 
 * ProcessEntries() function
 */

void FreeEntries(VSAA_NAME **freeNames);

#endif


/****************************************************************************************
* 
* ptaexternal.h
* -------------
* This is the top level header file containing all the definitions and 
* routines that we use in the PTA code but these are implemented by the 
* Validation SDK.
* 
* Include this file in your plugin specific code 
*
* Author - Siddharth Bajaj 03/03/01
* 
* Change History
* -
* -
*
*****************************************************************************************/


#ifndef _PTAEXTERNAL_H
#define _PTAEXTERNAL_H 1

#define MAX_DIGEST_LEN 20
#ifdef __cplusplus
extern "C" {  
  /* This allows for C++ inclusion/use of this header file */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "valsdk.h"
/*Defines*/


#ifndef vsMIN
#define vsMIN(x1, x2)     (((x1) <= (x2)) ? (x1) : (x2))
#endif
#ifndef vsMAX
#define vsMAX(x1, x2)     (((x1) >= (x2)) ? (x1) : (x2))
#endif



/* num_err = last + 1; */


/* use MAX_DIGEST_LEN=20 from tipem.h */

#define MD5_LEN 16
#define SHA_LEN 20

/* These must be duplicated here so we can ship the api header file to customers. */


#ifndef _ITEM_
#define _ITEM_ 1
typedef struct {
  unsigned char *data;
  unsigned int len;
} ITEM;
#endif

/*Prototypes*/
/* need to move this prototype to pta.h once the hash functions accept void* */
typedef struct client_data_s {
  char *url; /* the url they were trying to access. */
  char *pkcs7; /* the posted pkcs7 (b64). Freed after it's put in cgi env once. */
  int authorized; /* has this entry been authenticated already? */
  unsigned long int absolute_timeout; /* In GMT seconds. */
  unsigned long int inactive_timeout; /* In GMT seconds. */
  unsigned long int revocation_timeout; /* In GMT seconds. */
  unsigned char iSDigest[MD5_LEN]; /* MD5 Issuer Serial Digest. */
  char *userName; /* the subject dn from the cert. Saved if env-vars or js-vars. */
  ITEM cert; /* saved unless no-save-certs. */
} client_data_t;




/* from util.c */
char *vs_strstr_ni(char *s1, char *s2, long ns1);

typedef struct link_s {
  ITEM key;
  client_data_t *data;
  struct link_s *next;
} link_t;

struct hash_table_s;

typedef int (*pHashFn) (struct hash_table_s *htable, ITEM key);

typedef struct hash_table_s {
  link_t **heads;
  int size;
  pHashFn fn;
} hash_table_t;
/* For client_data access */
/* this function is used by functions like vsLinkDelete */
void vsDestroyClientData(client_data_t *cd);

/* web stuff. */

/* end wrappers */

#ifdef __cplusplus
}
#endif
/* end of C wrapper for C++ */


#endif

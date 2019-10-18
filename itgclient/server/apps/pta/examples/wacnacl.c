
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ssc_api.h"


/* A simple example of how to extend the web access control with its acl api. */

/* To use it, change the #define'd file names to their correct values. */
/* Then compile this file into a DLL or shared library. Define EXPORT for WIN32. */
/* Next, point the WAC to it with the "shlib-name" configuration option. */

/* This program will read a file of cert subject name pieces and corresponding urls. */
/* It will then block access to the specified urls for corresponding users. */

/* For example, the following file will block access to "/ssc/page.html" for users */
/* with the email address "rob@verisign.com".  User "jdoe@verisign.com" will be */
/* denied access to any protected url. */

/* The program does simple substring matching for both components. The comma at */
/* the end of the email address ensures that the entire address is matched. */
/* If you modify the program, make sure you only return */
/* CS_VALID or CS_SSC_PLUGIN_DENIED for SscCheck() */


/* SAMPLE FILE: */
/*
mail=rob@verisign.com, /ssc/page.html
mail=jdoe@verisign.com, /
*/


/* Hard-code some filenames. */
#ifdef WIN32
#define NACL_LOG_FILE "c:\\temp\\nacl.log"
#define NACL_INPUT_FILE "c:\\nacl.txt"
#else
#define NACL_LOG_FILE "/tmp/nacl.log"
#define NACL_INPUT_FILE "/tmp/nacl.txt" /* Not a real good place for this! */
#define Dll 
#endif

#define MAX_ENTRIES 500
#define MAX_LEN 1024

typedef struct pair_s {
  char *name;
  char *url;
} pair_t;

/* Global list of entries to deny access. */
pair_t gList[MAX_ENTRIES];
int gListCount = 0;
FILE *gFp = 0;


void freeList(int *count, pair_t *list) {

  int i;
  
  for (i=0; i<*count; i++) {
    free(list[i].name);
    free(list[i].url);
  }

  *count = 0;

}

/* add an entry. 0 for success. */
int addListEntry(char *name, char *url, int *count, pair_t *list) {
  
  int status = 0;

  if (*count + 1 >= MAX_ENTRIES) {
    return -1;
  }

  fprintf(gFp, "NACL: adding entry %s %s\n", name, url);

  list[*count].name = strdup(name);
  list[*count].url = strdup(url);

  (*count)++;

  return 0;
}


/* Looks for a substring match of name, url in the table. */
/* True if it finds one, else false. */
int findMatch(char *name, char *url, int count, pair_t *list) {

  int i, match = 0;

  for (i=0; i<count; i++) {

    if (strstr(name, list[i].name) && strstr(url, list[i].url)) {
      match = 1;
      break;
    }
  }

  return match;
}


Dll int SscInit(char *version, char *cfgString) {

  FILE *aclFp;
  char buf[MAX_LEN], name[MAX_LEN], url[MAX_LEN];
  char *rc = 0;
  int line = 0;

  gFp = fopen(NACL_LOG_FILE, "a");
  aclFp = fopen(NACL_INPUT_FILE, "r");

  if (gFp==0 || aclFp==0) {
    return -1;
  }

  fprintf(gFp, "NACL Init: version=%s, cfg=%s\n", version, cfgString);

  do {
    
    buf[0] = '\0';
    rc = fgets(buf, MAX_LEN, aclFp);
    line++;

    if (rc) {
      if (buf[0]!='#' && (sscanf(buf, "%s %s", name, url)==2)) {

        if (addListEntry(name, url, &gListCount, gList)) {
          fprintf(gFp, "NACL: Too many entries in file.  %d is the limit.", MAX_ENTRIES);
          freeList(&gListCount, gList);
          return -1;
        }
      }
      else {
        fprintf(gFp, "NACL: Error at line %d: %s", line, buf);
        freeList(&gListCount, gList);
        return -1;
      }
    }
  } while (rc);

  fclose(aclFp);

  return 0;
}

Dll int SscCheck(int certStatus, char *url, 
                 unsigned char *certBuf, unsigned int certLen, 
                 char *pkcs7, char *userName) {

  char *myUrl, *myUserName;

  myUrl = url ? url : "(nil url)";
  myUserName = userName ? userName : "(nil userName)";

  fprintf(gFp, "NACL: Check %s, dn=%s, st=%d\n", myUrl, myUserName, certStatus);

  if (certStatus!=CS_VALID) return certStatus;

  if (findMatch(myUserName, myUrl, gListCount, gList)) {
    return CS_SSC_PLUGIN_DENIED;
  }
  else {
    return CS_VALID;
  }
}


Dll int SscFinal(void) {

  fprintf(gFp, "NACL Final\n");

  freeList(&gListCount, gList);
  fclose(gFp);

  return 0;
}


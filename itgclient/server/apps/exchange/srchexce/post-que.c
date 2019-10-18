/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/exchange/srchexce/Attic/post-que.c,v 1.1.2.1 2000/03/15 00:13:37 aranade Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1996. All rights reserved.     |
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
#include "global.h"
#include "tipem.h"
#include "post-que.h"
#if 0
#include "util.h"

int GetEntriesAlloc  (ENTRY** entries, int* count){

  int 		x = 0;
  int 		cl = 0;
  char*		tempPointer = (char *)0;
  FILE*		tempfile = (FILE *)NULL_PTR;
  
  *count = 0;
  
  tempPointer = getenv (REQUEST_METHOD);

  if (tempPointer) {
    if (strcmp (tempPointer, "POST")) {
      tempfile = tmpfile ();
      if (tempfile == (FILE *)NULL_PTR)
        return (TE_IO);
      tempPointer = getenv ("QUERY_STRING");
      if (tempPointer)
        cl = T_strlen(tempPointer);
      else
        cl = 0;

      fprintf(tempfile, "%s\n", tempPointer);
      rewind (tempfile);
      for (x = 0; cl &&  (!feof (tempfile)); x++) {
        *count = x + 1;
        *entries = (ENTRY *)T_realloc((POINTER)*entries, sizeof(ENTRY) * (x+1));
        if (*entries == NULL)
  	  return (TE_ALLOC);
        (*entries)[x].val = fmakeword (tempfile, '&', &cl);
        if ((*entries)[x].val == NULL)
          return (TE_ALLOC);
        plustospace ((*entries)[x].val);
        unescape_url ((*entries)[x].val);
        (*entries)[x].name = makeword ((*entries)[x].val, '=');
      }
      fclose(tempfile);
    } 
    else {
      if(strcmp(getenv ("CONTENT_TYPE"), "application/x-www-form-urlencoded")) {
        printf ("Content-type: text/html%c%c", 10, 10);
        printf ("This script can only be used to decode form results. \n");
        return (TE_IO);
      }
      tempPointer = getenv ("CONTENT_LENGTH");
      if (tempPointer)
        cl = atoi (tempPointer);
      else
        cl = 0;
      for (x = 0; cl &&  (!feof (stdin)); x++) {
        *entries = (ENTRY *)T_realloc((POINTER)*entries, sizeof(ENTRY) * (x+1));
        if (*entries == NULL)
  	  return (TE_ALLOC);
        (*entries)[x].val  = fmakeword(stdin, '&', &cl);
        if ((*entries)[x].val == NULL)
          return (TE_ALLOC);
        plustospace ((*entries)[x].val);
        unescape_url ((*entries)[x].val);
        (*entries)[x].name = makeword ((*entries)[x].val, '=');
      }
      *count = x;
    }
    return (0);
  }
#else
/*
 * CopyString
 *
 */
static int CopyString (char** copy, char* string){

  char *p = NULL;
  int status = 0;

  *copy = NULL;
  if (string != NULL) {
    p = (char *)T_malloc (T_strlen (string) + 1);
    if (p == NULL)
      status = TE_ALLOC;
    else {
      T_strcpy (p, string);
      *copy = p;
    }
  }
  return (status);
}

/*
 * X2C
 *
 */
static
unsigned char X2C (char* str){

  char c1, c2;

  c1 = (str[0] >= 'A' ? ((str[0] & 0xdf) - 'A')+10 : (str[0] - '0'));
  c2 = (str[1] >= 'A' ? ((str[1] & 0xdf) - 'A')+10 : (str[1] - '0'));
  return ((c1 << 4) + c2);
}

/*
 * DecodeEscapes
 *
 */
static
void DecodeEscapes (unsigned char* str){

  int x, y;

  for(x=0, y=0; str[y]; x++, y++) {
    if((str[x] = str[y]) == '%') {
      str[x] = X2C ((char*)&str[y+1]);
      y += 2;
    }
  }
  str[x] = '\0';
}

/*
 * PlusToSpace
 *
 */
static
void PlusToSpace (char *str)
{
  while (*str) {
    if (*str == '+')
      *str = ' ';
    str++;
  }
}

/*
 * GetWord
 *
 * Purpose:
 *   Get the first word from line up to delimiter
 *   with leading and trailing spaces removed.
 *   Return new line pointer.
 *
 */
char *GetWord (char* line, char* word, char delimiter){

  char *lp = line;
  int i;

  if (*lp == '\0')
    return (NULL);
  /* remove leading spaces */
  while (isspace (*lp) && *lp != '\0')
    lp++;
  /* copy word */
  for (i=0; *lp != delimiter && *lp != '\0'; i++)
    word[i] = *lp++;
  /* remove trailing spaces */
  while (isspace (word[i-1]) && i > 0)
    i--;
  /* skip delimiter */
  if (*lp != '\0')
    lp++;
  /* skip spaces */
  while (isspace (*lp) && *lp != '\0')
    lp++;
  /* end word */
  word[i] = '\0';
  return (lp);
}

/*
 * GetEntriesAlloc
 *
 * Purpose:
 *   Create a list of Entries
 *   accepts either GET or POST methods
 * TODO:
 *   should either return a pointer to buffer, so that it can be freed, or,
 *   CopyString() all names and values, and supply a function to free them all,
 *   or, better yet, fill an associative table that manages it's own space.
 *
 */
int GetEntriesAlloc (ENTRY** entries, int* count){

  char 		*requestMethod, *queryString, *contentType, *contentLength;
  static char	formEnc[] = "application/x-www-form-urlencoded";
  char 		*buffer = NULL, *lp, *cp;
  char 		*name, *value;
  int 		x, bufferLen;
  int 		status = 0;

  *entries = (ENTRY *)NULL_PTR;
  *count = 0;

  do {
    requestMethod = getenv ("REQUEST_METHOD");
    /* make sure this is CGI */
    if (requestMethod == NULL) {
      status = TE_IO;
      break;
    }
    /* read data into buffer */
    if (T_strcmp (requestMethod, "GET") == 0) {
      /* GET method */
      queryString = getenv ("QUERY_STRING");
      if( queryString == NULL )
      {
        status = TE_IO ;
        break ;
      }
      bufferLen = T_strlen (queryString);
      buffer = (char *)T_malloc (bufferLen+1);
      if (buffer == NULL) {
        status = TE_ALLOC;
        break;
      }
      T_strcpy (buffer, queryString);
    }
    else if (T_strcmp (requestMethod, "POST") == 0) {
      /* POST method */
      contentType = getenv ("CONTENT_TYPE");
      if( contentType == NULL )
      {
        status = TE_IO ;
        break ;
      }
      if (strcmp (contentType, formEnc) != 0) {
        status = TE_IO;
        break;
      }
      contentLength = getenv ("CONTENT_LENGTH");
      if( contentLength == NULL )
      {
        status = TE_IO ;
        break ;
      }
      bufferLen = atoi (contentLength);
      buffer = (char *)T_malloc (bufferLen+1);
      if (buffer == NULL) {
        status = TE_ALLOC;
        break;
      }
      fread (buffer, bufferLen, 1, stdin);
      buffer[bufferLen] = '\0';
    }
    else {
      /* unknown method */
      status = TE_IO;
      break;
    }
    if (!*buffer) {
      /* empty buffer */
      status = TE_IO;
      break;
    }
    *count = 1;
    lp = buffer;
    while (*lp) {
      if (*lp == '&')
        (*count)++;
      lp++;
    }
    /* create entries */
    *entries = (ENTRY *)T_malloc (*count * sizeof (ENTRY));
    if (*entries == NULL) {
      status = TE_ALLOC;
      break;
    }
    lp = buffer;
    for (x=0; x<*count; x++) {
      name = lp;
      lp = GetWord (lp, name, '&');
      PlusToSpace (name);
      DecodeEscapes ((unsigned char*)name);
      cp = (char *)strchr (name, '=');
      value = cp + 1;
      *cp = '\0';
      (*entries)[x].name = name;
      (*entries)[x].val = value;
    }
  } while (0);
  return (status);
}


int GetRequestString (char** queryString){

  char 		*requestMethod, *contentType, *contentLength;
  static char	formEnc[] = "application/x-www-form-urlencoded";
  char 		*buffer = NULL;
  int 		bufferLen;
  int 		status = 0;

  do {
    requestMethod = getenv ("REQUEST_METHOD");
    /* make sure this is CGI */
    if (requestMethod == NULL) {
      status = TE_IO;
      break;
    }
    /* read data into buffer */
    if (T_strcmp (requestMethod, "GET") == 0) {
      /* GET method */
      *queryString = getenv ("QUERY_STRING");
      if( *queryString == NULL )
      {
        status = TE_IO ;
        break ;
      }
    }
    else if (T_strcmp (requestMethod, "POST") == 0) {
      /* POST method */
      contentType = getenv ("CONTENT_TYPE");
      if( contentType == NULL )
      {
        status = TE_IO ;
        break ;
      }
      if (strcmp (contentType, formEnc) != 0) {
        status = TE_IO;
        break;
      }
      contentLength = getenv ("CONTENT_LENGTH");
      if( contentLength == NULL )
      {
        status = TE_IO ;
        break ;
      }
      bufferLen = atoi (contentLength);
      *queryString = (char *)T_malloc (bufferLen+1);
      if (*queryString == NULL) {
        status = TE_ALLOC;
        break;
      }
      fread (*queryString, bufferLen, 1, stdin);
      (*queryString)[bufferLen] = '\0';
    }
    else {
      /* unknown method */
      status = TE_IO;
      break;
    }
    if (!**queryString) {
      /* empty buffer */
      status = TE_IO;
      break;
    }
  } while (0);
  return (status);
}


int GetEntriesFromString(const char* queryString, ENTRY** entries, int* count){

  char 		*lp, *cp;
  char 		*name, *value;
  int           status =0;
  int 		x; 

  do {
    if (!queryString) {
      status = 99;
      return status;
    }

    *count = 1;
    lp = (char*)queryString;
    while (*lp) {
      if (*lp == '&')
        (*count)++;
      lp++;
    }
    /* create entries */
    *entries = (ENTRY *)T_malloc (*count * sizeof (ENTRY));
    if (*entries == NULL) {
      status = TE_ALLOC;
      break;
    }
    lp = (char*)queryString;
    for (x=0; x<*count; x++) {
      name = lp;
      lp = GetWord (lp, name, '&');
      PlusToSpace (name);
      DecodeEscapes ((unsigned char*)name);
      cp = (char *)strchr (name, '=');
      value = cp + 1;
      *cp = '\0';
      (*entries)[x].name = name;
      (*entries)[x].val = value;
    }
  }while (0);
  return status;
}

int AddEntry(ENTRY **pEntries, int *pCount, const char *pszName, const char *pszValue)
{
  *pEntries = (ENTRY *)T_realloc( (POINTER)*pEntries, sizeof(ENTRY) * (++ *pCount) ) ;
  if( *pEntries == NULL ) return 1 ;
  (*pEntries)[*pCount-1].name = (char *)pszName ;
  (*pEntries)[*pCount-1].val = (char *)pszValue ;
  return 0 ;
}

#endif


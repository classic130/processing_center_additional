/*
 * $Revision: 1.3.84.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/vsexchange/vsutil.cpp,v 1.3.84.1 2003/06/06 22:46:30 npaul Exp $
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
#include <errno.h>
#include <stdarg.h>


#include "vsverify.h"
#include "vsutil.h"
#include "vsaautil.h"

#ifndef WIN32
#include <unistd.h>
  #ifdef _REENTRANT
    #include <pthread.h>
  #endif
#else
#include <windows.h>
#include <process.h>
#include <io.h>
#include "vsverifyexchange.h"
#endif

extern FILE    *logFP; // defined in vslog.cpp
#ifdef WIN32
  extern CRITICAL_SECTION logFileLock;
#elif defined(_REENTRANT)
  extern pthread_mutex_t  logFileLock;
#endif
extern int logFileLockInit;

/*******************************************************************/
void Dump(FILE *debugFile, const char *msg, const VSAA_NAME list[])
/*
 * Print the content of the list to the debug file
 * 
 * file pointer debugFile will not be used because the log uses the file
 * pointer from vslog.cpp
 */
/*******************************************************************/
{
	int i;
	time_t now = time(NULL);

	if ((list == NULL) || (logFP == NULL))
		return;
	VSAA_Log(VS_LOG_INFO, __LINE__, __FILE__, (char *)"%s at %s", msg, ctime(&now));
	for (i=0; list[i].pszName; i++)
	{
		VSAA_Log(VS_LOG_INFO, __LINE__, __FILE__,  (char *)"%s=[%s]", list[i].pszName,
			list[i].pszValue);
	}
}


/*******************************************************************/
VSAA_NAME *Duplicate(const VSAA_NAME list[])
/*
 * Create a duplication of list
 */
/*******************************************************************/
{
	size_t i;
	VSAA_NAME *panOutput;

	panOutput = (VSAA_NAME *)calloc(Entries(list), sizeof(VSAA_NAME));
	if (panOutput == NULL)
		return NULL;

	for (i=0; list[i].pszName; i++)
	{
		panOutput[i].pszName = strdup(list[i].pszName);
		if (panOutput[i].pszName == NULL)
		{
			Release(&panOutput);
			return NULL;
		}
		if (list[i].pszValue)
		{
			panOutput[i].pszValue = strdup(list[i].pszValue);
			if (panOutput[i].pszValue == NULL)
			{
				Release(&panOutput);
				return NULL;
			}
		}
		else
			panOutput[i].pszValue = NULL;
	}

	/* null out the last entry */
	panOutput[i].pszName  = NULL;
	panOutput[i].pszValue = NULL;
	return panOutput;
}


/*******************************************************************/
size_t Entries(const VSAA_NAME list[])
/*
 * Return the number of entries in the list including the last NULL
 * entry
 */
/*******************************************************************/
{
	size_t sz;

	if (list == NULL)
		return 1;
	for (sz=0; list[sz].pszName; sz++)
		;
	return ++sz;
}


/*******************************************************************/
const char *FindName(const char *pszName, size_t nameLen,
							const VSAA_NAME userInput[])
/*
 * Find the name-value pair with matching pszName in the input
 * Return NULL if not found
 */
/*******************************************************************/
{
	int i;

	for (i=0; userInput[i].pszName != NULL; i++)
	{
		if (nameLen == strlen(userInput[i].pszName))
		{
			if (!strncmp(pszName, userInput[i].pszName, nameLen)) /* if equal */
				return userInput[i].pszValue;           /* return the value */
		}
	}
	return NULL;
}


/*******************************************************************/
VSAA_STATUS GetConfig(const char *configFile, VSAA_NAME param[])
/*
 * Get the configuration from the configFile associated with names
 * in param
 */
/*******************************************************************/
{
    /* 
        A configuration entry might have a longer value than 80 bytes
        in a normal line such as LDAP DN name. Multiple lines should 
        also be handled. 

        To not change code too much, we limit the maximal length of
        a value to be at most 1024 bytes.

        A entry value between inside [...] will be considered to be single
        value with space between it allowed.
    */

	char s[1024], *tmpBuf;
	char name[1024];
	char value[1024];
	int i, l, k;
	FILE *fp = fopen(configFile, "r");
    if (fp == NULL) {
        return VSAA_ERR_CFG_FILE_OPEN;
    }

    memset(s, 0, sizeof(s));

	while (fgets(s, sizeof(s), fp))
	{
		if (s[0] != '#') /* skip comments */
		{
			name[0] = value[0] = '\0';
            
            tmpBuf = s;
            l = sizeof(s);
            do {
                i = strlen(tmpBuf);
                if(tmpBuf[i-1] != '\n') {
                    /* the line is too long, we should report an error */
                    fclose(fp);
                    return VSAA_ERR_CFG_FILE_LINE_TOO_LONG;
                } else {
                    k = i-2;
                    while(k>=0 && isspace(tmpBuf[k])) k--;
                    if(k>=0 && tmpBuf[k] == '\\') {
                        tmpBuf = &tmpBuf[k];
                        l -= k+1;
                        fgets(tmpBuf, l, fp);
                    } else {
                        break;
                    }
                }
            } while(l>0);
            
            /* MLP */
            if(strchr(s, '[') && strchr(s, ']')) {
                char* tmp = NULL;
                i = 0;
                while(isspace(s[i])) i++;
                strcpy(name, &s[i]);
                i = 0;
                while(!isspace(name[i])) i++;
                name[i] = 0;
                strcpy(s, &name[i+1]);
                i = 0;
                while(isspace(s[i])) i++;
                if(s[i] == '[') {
                    strcpy(value, &s[i+1]);
                    tmp = strchr(value, ']');
                    if(tmp && (tmp[1] == 0 || isspace(tmp[1]))) {
                        *tmp = 0;
                    } else {
                        fclose(fp);
                        return VSAA_ERR_CFG_ILLEGAL_SPACE_MARKER;
                    }
                } else { 
                    /* there are multiple values in this entry, and the second value is not using '[' */
                    continue;
                }
            }
            /* End MLP */
            else
			    sscanf(s, "%s %s", name, value);

			for (i=0; param[i].pszName; i++)
			{
				if (!strcmp(param[i].pszName, name))
				{
					param[i].pszValue = strdup(value);
                    if(!param[i].pszValue && value) { 
                        /* 
                           need to free those already allocated, but hard to 
                           determined which are allocated here rather than
                           from input. Need a track of what allocated or
                           ignore them, and leave to the caller process to
                           end with this error, and memory is freed then.
                        */
                        fclose(fp);
                        return VSAA_OUT_OF_MEMORY;
                    }
					break;
				}
			}
		}

        memset(s, 0, sizeof(s));
	}
	fclose(fp);
	return VSAA_SUCCESS;
}


/*******************************************************************/
void Release(VSAA_NAME **list)
/*
 * Release the entire list of name-value pairs
 */
/*******************************************************************/
{
	int i;

	if (*list == NULL)
		return;
	for (i=0; (*list)[i].pszName != NULL; i++)
	{
		free((*list)[i].pszName);
		if ((*list)[i].pszValue)
			free((*list)[i].pszValue);
	}
	free (*list);
	*list = NULL;
}


/***************************************************************************/
int FlattenNamesAlloc(VSAA_STATUS status, const VSAA_NAME *anInput,
	unsigned long *len, unsigned char **buffer)
/***************************************************************************/
{
  int i ;
  unsigned int nbTotal ;
  unsigned short nPairs ;
  unsigned short l;
  unsigned char *s;
  
  /*
  * first find out how many name value pairs are in the input
  */
  nbTotal = 4 + 2;
  if (anInput)
  {
    for( nPairs = 0; anInput[nPairs].pszName != NULL ; nPairs++ )
    {
      if (anInput[nPairs].pszValue)
        nbTotal += strlen(anInput[nPairs].pszName) + strlen(anInput[nPairs].pszValue) + 4; /* 2 for length */
      else
        nbTotal += strlen(anInput[nPairs].pszName) + 4; /* 2 for length */
    }
  }
  else
    nPairs = 0;
  
  *buffer = (unsigned char *)calloc(1, nbTotal);
  if (*buffer == NULL)
    return errno;
  *len = nbTotal;
  
  s = *buffer;
  for (i=0; i<4; i++)
  {
    *(s++) = (unsigned char)((unsigned)status & 0xFF) ;
    status = (VSAA_STATUS)( (unsigned)status >> 8 );
  }
  *(s++) = (unsigned char)(nPairs & 0xFF) ;
  *(s++) = (unsigned char)(nPairs >> 8) ;
  
  if (nPairs == 0)
    return 0;
  
  for( i = 0 ; anInput[i].pszName != NULL ; i++ )
  {
    /* first roll in the name */
    l = strlen(anInput[i].pszName) ;
    *(s++) = (unsigned char)(l & 0xFF);    /* first write the LSB        */
    *(s++) = (unsigned char)(l >> 8);      /* then the MSB                */
    memcpy(s, anInput[i].pszName, l);
    s += l;
    
    /* now roll in the value */
    if (anInput[i].pszValue)
      l = strlen(anInput[i].pszValue) ;
    else
      l = 0;
    *(s++) = (unsigned char)(l & 0xFF);    /* first write the LSB        */
    *(s++) = (unsigned char)(l >> 8);      /* then the MSB                */
    if (l)
      memcpy(s, anInput[i].pszValue, l);
    s += l;
  }
  return 0;
}


/***************************************************************************/
VSAA_NAME *ResurrectNamesAlloc(unsigned long len, const unsigned char *buffer,
    VSAA_STATUS *status)
/***************************************************************************/
{
    int i, j ;
    VSAA_NAME *anOutput ;
    unsigned short  nPairs, nbStrlen ;

	*status = (VSAA_STATUS)0;
	for (i=0; i<4; i++, buffer++)
	{
		*status = (VSAA_STATUS) ( (buffer[0] << (8 * i)) | (unsigned)(*status) );
	}
    nPairs = (*buffer) + (*(buffer+1) * 0x100) ;
    buffer += 2 ;
    anOutput = (VSAA_NAME *)calloc(nPairs+1, sizeof(VSAA_NAME) ) ;
    if (anOutput == NULL)
        return NULL;
    for(i = 0 ; i < nPairs ; i++ )
    {
        nbStrlen = (*buffer) + (*(buffer + 1) * 0x100) ;
        buffer +=2 ;
        anOutput[i].pszName = (char *)calloc(nbStrlen + 1, sizeof(char)) ;
        if (anOutput[i].pszName == NULL)
        {
            for (j=0; j<i; j++)
            {
                free(anOutput[j].pszName);
                free(anOutput[j].pszValue);
            }
            free(anOutput);
            return NULL;
        }
        memcpy(anOutput[i].pszName, buffer, nbStrlen) ;
        anOutput[i].pszName[nbStrlen] = '\0' ;
        buffer += nbStrlen ;
        nbStrlen = (*buffer) + (*(buffer+1) * 0x100) ;
        buffer += 2 ;
        anOutput[i].pszValue = (char *)calloc(nbStrlen + 1, sizeof(char)) ;
        if (anOutput[i].pszValue == NULL)
        {
            for (j=0; j<i; j++)
            {
                free(anOutput[j].pszName);
                free(anOutput[j].pszValue);
            }
            free(anOutput[i].pszName);
            free(anOutput);
            return NULL;
        }
        memcpy(anOutput[i].pszValue, buffer, nbStrlen) ;
        anOutput[i].pszValue[nbStrlen] = '\0' ;
        buffer += nbStrlen ;
    }
    anOutput[i].pszName = anOutput[i].pszValue = NULL ;
    return anOutput ;
}


/***************************************************************************/
static char *CopyAndTrim(const char *s, int l)
/***************************************************************************/
{
	char *v = (char *)calloc(l + 1, 1);
	int i, j;

	if (v == NULL)
		return v;
	for (i=0; i<l; i++)
		if (!isspace(s[i]))
			break;
	for (j=l-1; j>i; j--)
		if (!isspace(s[j]))
			break;
	memcpy(v, &s[i], j-i+1);
	return v;
}


/***************************************************************************/
VSAA_STATUS Append(VSAA_NAME **panOutput, const char *name, int nameLen,
				   const char *value, int valueLen)
/***************************************************************************/
{
	size_t i;

	if (*panOutput == NULL)
	{
		*panOutput = (VSAA_NAME *)calloc(2, sizeof(VSAA_NAME));
		if (*panOutput == NULL)
			return VSAA_OUT_OF_MEMORY;
		i = 0;
	}
	else /* existing data */
	{
		VSAA_NAME *newList;

		i = Entries(*panOutput) - 1;
		newList = (VSAA_NAME *)realloc(*panOutput, sizeof(VSAA_NAME) * (i + 2));
		if (newList == NULL)
			return VSAA_OUT_OF_MEMORY;
		*panOutput = newList;
	}

	/* null out the last entry */
	(*panOutput)[i].pszName  = NULL;
	(*panOutput)[i].pszValue = NULL;
	(*panOutput)[i+1].pszName  = NULL;
	(*panOutput)[i+1].pszValue = NULL;

	/* add an entry to the near end of the list */
	(*panOutput)[i].pszName = CopyAndTrim(name, nameLen);
	if ((*panOutput)[i].pszName == NULL)
		return VSAA_OUT_OF_MEMORY;

	(*panOutput)[i].pszValue = CopyAndTrim(value, valueLen);
	if ((*panOutput)[i].pszValue == NULL)
		return VSAA_OUT_OF_MEMORY;
	return VSAA_SUCCESS;
}


/***************************************************************************/
VSAA_STATUS ExtractDn(const VSAA_NAME *input, VSAA_NAME **dn)
/*	cert_DN=[Organization = batman<br>
             Organizational Unit = EmployeeID - 2<br>
             Organizational Unit = MailStop - 3<br>
			 Organizational Unit = test - 4<br>
			 Title = 1<br>
			 Common Name = Oanh Q Hoang<br>
			 Email Address = ohoang@verisign.com<br>] */
/***************************************************************************/
{
	const char *certDN = FindName("cert_DN", strlen("cert_DN"), input);
	int dnSize = 10;
	int dnUsed = 0;
	char *br;
	char *eq;

	*dn = NULL;
	if (certDN == NULL)
		return VSAA_INVALID_CERT;

    while (*certDN)
	{
		br = (char *)strstr(certDN, "<br>");
		if (br)
		{
			eq = (char *)strstr(certDN, "=");
			if ((eq == NULL) || (eq > br)) /* if no equal sign */
			{
				certDN = br + 4; /* skip the <br> */
				continue;
			}
			Append(dn, certDN, eq - certDN, eq + 1, br - eq - 1);
		}
		certDN = br + 4;
	}
	return VSAA_SUCCESS;
}

/***************************************************************************/
void StartDebugger(const char *fileName)
/*
 * If fileName exists, bring up the debugger
 */
/***************************************************************************/
{
#ifdef WIN32
	if (_access(fileName, 0) == 0)
	{
		DebugBreak();
	}
#else
	/* Rename the file to make this function exits */
	while (access(fileName, 0) == 0)
		sleep(5);
#endif
}


/***************************************************************************/
VSAA_STATUS VerifyExchangeDll(
	const VSAA_NAME anInput[], 
	char *exchangeServer,
	char *exchangeDomain,
	FILE *debugFile)
/* file pointer debugFile will not be used here. Instead it uses logFP */
/***************************************************************************/
{
  VSAA_STATUS status = VSAA_INTERNAL_ERROR;
#ifdef WIN32
  HINSTANCE hVsExchange = LoadLibrary(VS_EXCHANGE_DLL);
  if (hVsExchange == NULL)
  {
    VSAA_Log(VS_LOG_INFO, __LINE__, __FILE__, (char *)"Cannot load %s, error %d", VS_EXCHANGE_DLL, GetLastError());
  }
  else
  {
    VS_VERIFY_EXCHANGE_FUNC pfnVerifyExchange =
      (VS_VERIFY_EXCHANGE_FUNC) GetProcAddress(hVsExchange, VS_VERIFY_EXCHANGE_NAME);
    if (pfnVerifyExchange)
    {
      // locking the log file pointer
      if (!logFileLockInit)
      {
        InitializeCriticalSection(&logFileLock);
        logFileLockInit = 1;
      }    
      
      EnterCriticalSection(&logFileLock); 
      
      status = pfnVerifyExchange(anInput,logFP);
      // releasing the log file pointer
      LeaveCriticalSection(&logFileLock);
    }
    else
    {
      VSAA_Log(VS_LOG_INFO, __LINE__, __FILE__,  (char *)"Cannot file function %s in %s, error %d", VS_VERIFY_EXCHANGE_NAME,
        VS_EXCHANGE_DLL, GetLastError());
    }
    FreeLibrary(hVsExchange);
  }
#endif
  return status;
}


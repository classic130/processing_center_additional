

/* Win32 exe to read a file of name=value pairs, and insert them into a */

/* registry key. */



#include <windows.h>



#include <stdio.h>
#include <stdlib.h>
#include "pta.h"


#define MAX_LINE_LENGTH 4096



LONG setValue(PHKEY hkey, const char *name, const char *value) {


  BYTE valueBuf[MAX_LINE_LENGTH];
  DWORD valueLen = 0;

  sprintf((char *) valueBuf, "%s", value);
  valueLen = strlen((char *) valueBuf) + 1;

  return RegSetValueEx(*hkey, name, 0, REG_SZ, valueBuf, valueLen);

}


/* Take a line of name="value" options, and parse it into name and value. */
/* Reads from line_buf into name, value_buf.  */
/* All buffers must already be allocated. */
int vsGetNameValue(char *line_buf, char *name_buf, char *value_buf) {

  int status = 0;
  int quoted = 0;
  char *p, *q;

  do {
    name_buf[0] = value_buf[0] = '\0';


    /* 1. skip space 2. read until space,'=' */
    /* 3. skip space, '=','"' 4. read until space, or '"' if we got one earlier. */

    /* 1. */
    p = line_buf;
    while(*p && isspace(*p)) { p++; }

    /* 2. */
    q = name_buf;
    while(*p && !(isspace(*p) || *p=='=')) { *q = *p; q++; p++; }
    *q = '\0';

    /* 3. */
    while(*p && (isspace(*p) || *p=='='|| *p=='\"')) { if (*p=='\"') quoted = 1; p++; }

    if (*p=='\0') {
      status = -1;
      break;
    }

    /* 4. */
    q = value_buf;
    while(*p && ((quoted && *p!='\"') || 
                 (!quoted && !(isspace(*p) || *p=='\r' || *p=='\n'))))
      { *q = *p; q++; p++; }

    *q = '\0';

  } while(0);

  return status;
}



/* Get the next non-comment, non-blank line from the file. */
/* Not using one in val.dll since we can't pass a FILE pointer across dlls. */

char *isscGetNextLine(char *lineBuf, int maxLen, FILE *fp) {

  char *rc = 0;
  int comment = 0;
  char tmpBuf[MAX_LINE_LENGTH];

  do {

    rc = fgets(lineBuf, maxLen, fp);

    if (lineBuf[0]=='#' || (sscanf(lineBuf, "%s", tmpBuf) <= 0)) comment = 1;
    else comment = 0;

  } while (rc && comment);

  return rc;
}





/* Read a file of name=value options and place them all in a pblock. */

int vsAddOptionsToReg(char *optionFile, PHKEY hkey) {

  int status = 0;

  FILE *fp = 0;
  char line_buf[MAX_LINE_LENGTH];
  char name_buf[MAX_LINE_LENGTH], value_buf[MAX_LINE_LENGTH];
  char *read_status;

  do {

    if (!(fp = fopen(optionFile, "r"))) {
      status = 10;
      break;
    }

    /* Read the config file */
    do {

      if (read_status = isscGetNextLine(line_buf, MAX_LINE_LENGTH, fp)) {

        if (vsGetNameValue(line_buf, name_buf, value_buf)!=0) {
          fprintf(stderr, "Error: reading line '%s'\n", line_buf);
          status = 11;
          break;
        }
        if (setValue(hkey, name_buf, value_buf)!=ERROR_SUCCESS) {

          fprintf(stderr, "Error: setting %s=\"%s\"\n", name_buf, value_buf);
          status = 12;
          break;
        }

      }

    } while (read_status != 0 && status==0);

  } while (0);

  if (fp) fclose(fp);

  return status;
}



/* Get info about a key.  For debugging. */

void vsPrintKeyInfo(PHKEY hkey) {

  LONG rc = 0L;
  char valueBuf[MAX_LINE_LENGTH];
  DWORD valueLen;
  FILETIME filetime;
  DWORD nKeys = 0, maxKeys = 0, maxClass = 0, num = 0;
  DWORD a, b, c;

  fprintf(stderr, "printing key info\n");

  valueLen = MAX_LINE_LENGTH;
  rc = RegQueryInfoKey(*hkey, valueBuf, &valueLen, 0, &nKeys,
                       &maxKeys, &maxClass, &num,
                       &a, &b, &c, &filetime);

  fprintf(stderr, "rc=%d\n",rc);

  fprintf(stderr, "%d keys, %d values\n", nKeys, num);
}



int vsPrintRegKey(PHKEY hkey) {

  LONG rc = 0L;
  DWORD i, regType;
  char nameBuf[MAX_LINE_LENGTH], valueBuf[MAX_LINE_LENGTH];
  DWORD nameLen, valueLen;

  i=0;
  do {
    nameLen = valueLen = MAX_LINE_LENGTH;

    rc = RegEnumValue(*hkey, i, nameBuf, &nameLen,
                      0, &regType, valueBuf, &valueLen);

    if (rc==ERROR_SUCCESS) {
      if (nameLen > MAX_LINE_LENGTH - 1) {
        nameBuf[MAX_LINE_LENGTH - 1] = '\0';
        fprintf(stderr, "Error: key too long! %d for '%s'\n",
                nameLen, nameBuf);
        return -1;
      }
      if (valueLen > MAX_LINE_LENGTH - 1) {
        valueBuf[MAX_LINE_LENGTH - 1] = '\0';
        fprintf(stderr, "Error: key too long! %d for '%s'\n",
                valueLen, valueBuf);
        return -1;
      }
		
      printf("%s=\"%s\"\n", nameBuf, valueBuf);
    }

    i++;
		
  } while (rc == ERROR_SUCCESS);

  if (rc==ERROR_NO_MORE_ITEMS) {
    return 0;
  }
  else {
    fprintf(stderr, "Error: 0x%x reading registry.\n", rc);
    return -1;
  }
}



/* returns 0 if good usage.  */
/* *preserve = 1 if we shouldn't delete the key first */
/* *filename gets the name of options.txt. */
/* *comvsssc gets whether -comvsssc options was specified */

int getUsage(int *dump, int *preserve, int *comvsssc, char **filename,
			 int argc, char *argv[]) {

  int bad = 0;

  *dump = 0;
  *preserve = 0;
  *filename = 0;
  *comvsssc = 0;

  switch(argc) {

  case 2:
    if (argv[1][0]=='-') {
      if (_stricmp(argv[1], "-dump")!=0) {
        bad = 1;
      }
      else {
        *dump = 1;
      }
    }
    else {
      *filename = argv[1];
    }
    break;

  case 3:
	  if (_stricmp(argv[1], "-o") == 0) {
		*preserve = 1;
		*filename = argv[2];
	  } else 
		  if (_stricmp(argv[1], "-comvsssc") == 0) {
			  *comvsssc = 1;
			  if (_stricmp(argv[2], "-dump")==0) 
				  *dump = 1;
			  else
				  *filename = argv[2];					
		  } else 
			  bad = 1;		 
    break;

  case 4:
	  if ( (_stricmp(argv[1], "-comvsssc") == 0) && (_stricmp(argv[2], "-o") == 0) ) {
		  *comvsssc = 1;
		  *preserve = 1;
		  *filename = argv[3];
	  } else
		  bad = 1;
	  break;

  default:
    bad = 1;
  }

  return bad;

}



void print_usage(char *exeName) {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "%s [-comvsssc] -dump\n", exeName);
  fprintf(stderr, "%s [-comvsssc] [-o] option_filename\n", exeName);
}



int main(int argc, char *argv[]) {



  int status = 0;
  HKEY hkey = 0;
  int rc, isNewKey;
  int dump = 0, preserve = 0, comvsssc = 0;
  char *filename = 0;

  do {

    if (getUsage(&dump, &preserve, &comvsssc, &filename, argc, argv)) {
      print_usage(argv[0]);
      status = 1;
      break;
    }

	if (!comvsssc)
		rc = RegCreateKeyEx(HKEY_LOCAL_MACHINE, PTA_REGISTRY_KEY, 0, 0,
                             REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                             0, &hkey, &isNewKey);
	else
		rc = RegCreateKeyEx(HKEY_LOCAL_MACHINE, COMVSSSC_REGISTRY_KEY, 0, 0,
                             REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
                             0, &hkey, &isNewKey);
		
	if (rc != ERROR_SUCCESS) {
		fprintf(stderr, "Error: 0x%x opening registry\n", rc);
		status = 2;
	}	

    if (dump) {
	  if (!comvsssc) 
		printf("# Contents of registry key '%s'\n\n", PTA_REGISTRY_KEY);
	  else
		printf("# Contents of registry key '%s'\n\n", COMVSSSC_REGISTRY_KEY);
      vsPrintRegKey(&hkey);
    }
    else {
      /* delete the key and reopen it */
      /* This remove values for lines taken out of the file. */
      if (!preserve) {
        if ((rc = RegDeleteKey(hkey, ""))
            != ERROR_SUCCESS) {
          fprintf(stderr, "Error: 0x%x deleting key.\n", rc);
          status = 2;
        }
        else {
			if (!comvsssc)
				rc = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                                      PTA_REGISTRY_KEY, 0, 0,
                                      REG_OPTION_NON_VOLATILE,
                                      KEY_ALL_ACCESS,
                                      0, &hkey, &isNewKey);
			else
				rc = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                                      COMVSSSC_REGISTRY_KEY, 0, 0,
                                      REG_OPTION_NON_VOLATILE,
                                      KEY_ALL_ACCESS,
                                      0, &hkey, &isNewKey);

             if (rc != ERROR_SUCCESS) {
				fprintf(stderr, "Error: 0x%x opening registry\n", rc);
				status = 3;
			 }
		}
      }

      if (status = vsAddOptionsToReg(filename, &hkey)) {

        if (status==10) {
          fprintf(stderr, "Error: unable to open file '%s'\n", argv[1]);
        }
        else {
          fprintf(stderr, "Error: reading file '%s'\n", argv[1]);
        }
				
        break;
      }
    }
		
  } while (0);


  if (hkey) {
    RegCloseKey(hkey);
  }

  return status;

}




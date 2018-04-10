
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "cvmglobal.h"

/* For a Macintosh, where time is returned in seconds since
     1/1/1904 12:00:00 AM, YEAR_BASE should be defined as 1904.
   For Microsoft C 7.0, YEAR_BASE should be defined as 1900.
   The following defines YEAR_BASE as 1970 if it has not already been
     defined as something else with C compiler flags.
 */
#ifndef YEAR_BASE
#define YEAR_BASE 1970
#endif

/* Calculate the time adjustment the number of seconds between the year
     base and 1970. */
#define TIME_ADJUSTMENT \
  ((CVMTIME)(365 * (1970 - YEAR_BASE) + ((1970 - YEAR_BASE) + 2) / 4) * \
   (CVMTIME)24 * (CVMTIME)3600)

/* If the time() function returns local time, define GMT_OFFSET to be
     the number of hours that local time is EARLIER than GMT.
*/
#ifndef GMT_OFFSET
#define GMT_OFFSET 0
#endif

void cvm_time (CVMTIME *theTime)
{
  time ((time_t *)theTime);

  /* Correct for a year base different than 1970 */
  (*theTime) -= TIME_ADJUSTMENT;

  /* Correct for local time to GMT */
  (*theTime) += (CVMTIME)3600 * GMT_OFFSET;
}

/* Replace newline characters in string with NULLs. */
void cvm_make_newline_null(char *str) {

  unsigned int i;

  if (str) {
    for (i=0; i<strlen(str); i++) {
      if (str[i]=='\n' || str[i]=='\r') str[i]='\0';
    }
  }
}

/* See if a string is on. */
/* OFF = "0", "off", "false", "OFF", "FALSE", etc... */
/* ON  = !OFF */
/* Note that a random string "lskdja" will be considered on. */
/* A non-existent string will be considered off. */
int cvmCfgStringIsOn(const char *value) {

  int off = 0;

  if (value==0 ||
      strcmp(value, "0")==0 ||
      strcmp(value, "off")==0 ||
      strcmp(value, "Off")==0 ||
      strcmp(value, "OFF")==0 ||
      strcmp(value, "false")==0 ||
      strcmp(value, "False")==0 ||
      strcmp(value, "FALSE")==0 ) off = 1;
  else off = 0;

  return !off;
}


/* Used for doing url form encoding/decoding. */

#include <stdlib.h>
#include <string.h>
#include "escape.h"

/* Begin pieces of mkparse.c */

#define HEX_ESCAPE '%'


/* DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
   DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
   DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER

								   TOXIC!

	 Do not even think of changing IS_OK or anything anywhere near it.

	 There is much spooky voodoo involving signed and unsigned chars
	 when using gcc on SunOS 4.1.3.

	 If you think you understand it, the smart money says you're wrong.

								   TOXIC!

   DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
   DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
   DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER DANGER
 */

int netCharType[256] =
/*	Bit 0		xalpha		-- the alphas
**	Bit 1		xpalpha		-- as xalpha but 
**                             converts spaces to plus and plus to %20
**	Bit 3 ...	path		-- as xalphas but doesn't escape '/'
*/
    /*   0 1 2 3 4 5 6 7 8 9 A B C D E F */
    {    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	/* 0x */
		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	/* 1x */
		 0,0,0,0,0,0,0,0,0,0,7,4,0,7,7,4,	/* 2x   !"#$%&'()*+,-./	 */
         7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,0,	/* 3x  0123456789:;<=>?	 */
	     0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,	/* 4x  @ABCDEFGHIJKLMNO  */
	     /* bits for '@' changed from 7 to 0 so '@' can be escaped   */
	     /* in usernames and passwords in publishing.                */
	     7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,7,	/* 5X  PQRSTUVWXYZ[\]^_	 */
	     0,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,	/* 6x  `abcdefghijklmno	 */
	     7,7,7,7,7,7,7,7,7,7,7,0,0,0,0,0,	/* 7X  pqrstuvwxyz{\}~	DEL */
		 0, };

#define IS_OK(C) (netCharType[((unsigned int) (C))] & (mask))

/* encode illegal characters into % escaped hex codes.
 *
 * mallocs and returns a string that must be freed
 */
  
char *NET_EscapeBytes (const char * str, int32 len, int mask, int32 * out_len)
{
    register  unsigned char *src;
    register unsigned char *dst;
    char        *result;
    int32       i, extra = 0;
    char        *hexChars = "0123456789ABCDEF";

	if(!str)
		return(0);

	src = (unsigned char *) str;
    for(i = 0; i < len; i++)
	  {
        if (!IS_OK(src[i]))
            extra+=2; /* the escape, plus an extra byte for each nibble */
	  }

    if(!(result = (char *) malloc(len + extra + 1)))
        return(0);

    dst = (unsigned char *) result;
    for(i = 0; i < len; i++)
	  {
		unsigned char c = src[i];
		if (IS_OK(c))
		  {
			*dst++ = c;
		  }
		else if(mask == URL_XPALPHAS && c == ' ')
		  {
			*dst++ = '+'; /* convert spaces to pluses */
		  }
		else 
		  {
			*dst++ = HEX_ESCAPE;
			*dst++ = hexChars[c >> 4];		/* high nibble */
			*dst++ = hexChars[c & 0x0f];	/* low nibble */
		  }
	  }

    *dst = '\0';     /* tack on eos */
	if(out_len)
		*out_len = dst - (unsigned char *) result;
    return result;
}

char *NET_Escape (const char * str, int mask)
{
    if(!str)
        return 0;
    return NET_EscapeBytes (str, (int32)strlen(str), mask, 0);
}


/* return the size of a string if it were to be escaped.
 */
int32 NET_EscapedSize (const char * str, int mask)
{
	int32                         extra = 0;
	register unsigned char * src;

	if(!str)
		return(0);

	for(src=((unsigned char *)str); *src; src++)
        if (!IS_OK(*src))
            extra+=2; /* the escape, plus an extra byte for each nibble */

	return((int32)(src - ((unsigned char *)str)) + extra + 1);
}


/* decode % escaped hex codes into character values
 */
#define UNHEX(C) \
    ((C >= '0' && C <= '9') ? C - '0' : \
     ((C >= 'A' && C <= 'F') ? C - 'A' + 10 : \
     ((C >= 'a' && C <= 'f') ? C - 'a' + 10 : 0)))

/* In-place rewrite of str, code copied from NET_UnEscapeCnt to avoid imposing
 * an PL_strlen and making that function call this one.
 */
int32 NET_UnEscapeBytes (char * str, int32 len)
{
	int32 i = 0;
    register char *dst = str;
	char c, d;

	while (i < len)
	  {
		c = str[i++];
        if (c == HEX_ESCAPE && i < len)
		  {
			d = str[i++];
			c = UNHEX(d);
			if (i < len)
			  {
				d = str[i++];
				c = (c << 4) | UNHEX(d);
			  }
		  }
		*dst++ = c;
	  }
    *dst = '\0';

    return (int32)(dst - str);
}

int NET_UnEscapeCnt (char * str)
{
    register char *src = str;
    register char *dst = str;

    while(*src) {

      if (*src == '+') {
        /* I added this case. (Stan.)*/
        *dst++ = ' ';
        src++;
      }
      else if (*src != HEX_ESCAPE) {

        *dst++ = *src++;
      }
      else {

        src++; /* walk over escape */
        
        if (*src) {

          *dst = UNHEX(*src) << 4;
          src++;
        }
        if (*src)
          {
            *dst = (*dst + UNHEX(*src));
            src++;
          }
        dst++;
      }
    }

    *dst = 0;

    return (int)(dst - str);

} /* NET_UnEscapeCnt */



char *NET_UnEscape(char * str)
{
	(void)NET_UnEscapeCnt(str);

	return str;
}

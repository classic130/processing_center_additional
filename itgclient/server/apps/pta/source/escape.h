
#ifndef __ESCAPE_H__
#define __ESCAPE_H__

/* Added by Stan. */
/* do not define this for AIX - Sasi 05/22/03 */

/* Begin Change : Fix for CR30756, Porting to Linux */
#if !defined(AIX) && !defined(PROTYPES_H)
/* End Change : Fix for CR30756, Porting to Linux */
typedef int int32;
#endif

/* From other files. */
/*	Bit 0		xalpha		-- the alphas
**	Bit 1		xpalpha		-- as xalpha but 
**                             converts spaces to plus and plus to %20
**	Bit 3 ...	path		-- as xalphas but doesn't escape '/'
*/

#define URL_XALPHAS  (unsigned char)  1
#define URL_XPALPHAS (unsigned char)  2
#define URL_PATH     (unsigned char)  4



/* Prototypes. */
/* mallocs */
char *NET_EscapeBytes (const char * str, int32 len, int mask, int32 * out_len);
char *NET_Escape (const char * str, int mask);

int32 NET_EscapedSize (const char * str, int mask);

/* don't know if this works.*/
int32 NET_UnEscapeBytes (char * str, int32 len);

/* In place. Use these. */
int NET_UnEscapeCnt (char * str);
char *NET_UnEscape(char * str);

#endif /* __ESCAPE_H__ */

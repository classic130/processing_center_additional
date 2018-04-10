#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "base64.h"

// ------------------------------------------------------------------
//
// 0xfc = 11111100
// 0x03 = 00000011
// 0xf0 = 11110000
// 0x0f = 00001111
// 0xc0 = 11000000
// 0x3f = 00111111
// 0x30 = 00110000
// 0x3c = 00111100
//
// ------------------------------------------------------------------
// The Base64 alphabet

const
char szB64[] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";


// ------------------------------------------------------------------
//
// Base64Encode()
//
// This function takes a character string as input and
// transforms it to Base64 encoding. The return value
// is dynamically allocated and must be freed by the caller.
//

char * Base64Encode(const char *szStr, unsigned int szLen)
{
  char *szEnc;
  int iLen,
      i,
      j;

  iLen = szLen;
  szEnc = (char *) malloc ((int)((float)iLen * 1.5)); // Space for the encoded string.

  j = 0;
  for (i = 0; i < (iLen - (iLen % 3)); i+=3)   // Encode 3 bytes at a time.
    {
      szEnc[j]   = szB64[ (szStr[i] & 0xfc) >> 2 ];
      szEnc[j+1] = szB64[ ((szStr[i] & 0x03) << 4)   | ((szStr[i+1] & 0xf0) >> 4) ];
      szEnc[j+2] = szB64[ ((szStr[i+1] & 0x0f) << 2) | ((szStr[i+2] & 0xc0) >> 6) ];
      szEnc[j+3] = szB64[ (szStr[i+2] & 0x3f) ];
      j += 4;
    }

  i = iLen - (iLen % 3);  // Where we left off before.
  switch (iLen % 3)
    {
      case 2:  // One character padding needed.
        {
          szEnc[j] = szB64[ (szStr[i] & 0xfc) >> 2 ];
          szEnc[j+1] = szB64[ ((szStr[i] & 0x03) << 4) | ((szStr[i+1] & 0xf0) >> 4) ];
          szEnc[j+2] = szB64[ (szStr[i+1] & 0x0f) << 2 ];
          szEnc[j+3] = szB64[64];  // Pad
          break;
        }
      case 1:  // Two character padding needed.
        {
          szEnc[j] = szB64[ (szStr[i] & 0xfc) >> 2 ];
          szEnc[j+1] = szB64[ (szStr[i] & 0x03) << 4 ];
          szEnc[j+2] = szB64[64];  // Pad
          szEnc[j+3] = szB64[64];  // Pad
          break;
        }
    }
  szEnc[j+4] = NULL;
  return (szEnc);
}

// ------------------------------------------------------------------
//
// Base64Decode()
//
// This function takes an encoded Base64 string and returns the
// unencoded string. The return value is dynamically allocated
// and must be freed by the caller.
//

// Helper macro
#define  Val(i)  ( szStr[i] == '=' ? 0 : strchr(szB64, szStr[i]) - szB64 )

char * Base64Decode(const char *szStr, unsigned int *rLen)
{
  char *szDecode;
  int iLen,
      i,
      j;

  iLen = strlen(szStr);
  szDecode = (char *) malloc(iLen); // Space for the decoded string.

  j = 0;
  for (i = 0; i < iLen; i+=4) // Work on 4 bytes at a time.
    {                         // Twiddle bits.
      szDecode[j]   = (Val(i) << 2) | ((Val(i+1) & 0x30) >> 4);
      szDecode[j+1] = ((Val(i+1) & 0x0f) << 4) | ((Val(i+2) & 0x3c) >> 2);
      szDecode[j+2] = ((Val(i+2) & 0x03) << 6) | (Val(i+3) & 0x3f);
      j += 3;
    }

  *rLen = j - 1;
  szDecode[j] = NULL;
  return (szDecode);
}


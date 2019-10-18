#ifndef		__VS_CSP_UTIL__
#define		__VS_CSP_UTIL__


#include "cspincludes.h"

void _Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize);
void _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize);

#endif
///////////Misc.h contain defination for misc function

#ifndef _VSSC_MISC_H_
#define _VSSC_MISC_H_

BOOL	_decode(short input, DWORD *output);
void _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize);
void _Base64Encode(char* pInput, unsigned int dwInputSize,char* pOutput,
												unsigned int * dwOutputSize);

VSAA_STATUS Test(VSAA_NAME anInput[], VSAA_NAME **panOutput);
void debugInfo(char * buf);
bool PestubInit();
void InitiliazeInfo(char *szName, char *szValue);

#endif

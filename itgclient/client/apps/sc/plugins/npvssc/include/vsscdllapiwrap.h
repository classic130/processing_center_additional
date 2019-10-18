#include "vssc.h"

#define E_NO_HOSTNAME 0x80003556


EXTERN_C IVSSCDllApi* VSSCDllApi_GetInstance(IVSSC* pVSSC);

EXTERN_C unsigned int VSSCDllApi_SetHostName (IVSSCDllApi* pVSSCDllApi, LPSTR szHostName, LPSTR szProtocol);
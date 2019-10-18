#include "ptadllapi.h"

EXTERN_C IVSPTADllApi* PTADllApi_GetInstance(IVSPTA* pPTA);
EXTERN_C unsigned int PTADllApi_SetHostName (IVSPTADllApi* pPTADllApi, LPSTR szHostName, LPSTR szProtocol);
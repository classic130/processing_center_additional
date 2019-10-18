#include <stdio.h>
#include "vspmsmp.h"

#ifdef __cplusplus

#ifdef WIN32
#define EXPORT extern "C" __declspec (dllexport)
#else
#define EXPORT 
#endif

#else

#ifdef WIN32
#define EXPORT __declspec (dllexport)
#else
#define EXPORT
#endif

#endif

extern "C"
{
EXPORT void UserEnrollGeneratePolicy (VSPM_Container policy, VSPM_STATUS *status);
}

EXPORT void UserEnrollGeneratePolicy (VSPM_Container policy, VSPM_STATUS *status)
{

	printf("UserEnrollGeneratePolicy is called\n");

	*status = VSPM_STATUS_NO_ERROR;

}

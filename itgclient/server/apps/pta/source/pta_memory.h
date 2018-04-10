#ifndef _PTA_SM_MEMORY_
#define _PTA_SM_MEMORY_ 1

#define NAME_OF_SHARED_MEMORY "PTA_SM_SHARED_MEMORY" 
#define UNIQUE_SHARED_MEMORY_ID 3212339
#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

#ifdef WIN32
#include <windows.h>
#elif defined SOLARIS 
typedef int HANDLE;
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#else 
#error unsupported plateform
#endif

unsigned char* Pta_SM_malloc(int m_size, HANDLE *hMapObject,char* optionFileName);
void Pta_SM_free(HANDLE hMapObject, unsigned char * lpvMem);

#ifdef __cplusplus
}
#endif

#endif

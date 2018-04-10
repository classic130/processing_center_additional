/*
 * pta_memory.cpp
 * Author Bin Zou, 9/28/01
 */

#include "pta_memory.h"

/* For WIN32 platform */
#ifdef WIN32

/*
 *	Pta_SM_malloc(int m_size,HANDLE * hMapObject,char* optionFileName)
 *           int m_size: size of the memory
 *           HANDLE * hMapObject: handle to the shared memory later can be used for clean up
 *           char* optionFileName: NULL, not used for NT platform
 */
unsigned char * Pta_SM_malloc(int m_size,HANDLE * hMapObject,char* optionFileName) {    
	HANDLE handle = NULL;  /* handle to file mapping*/
        BOOL fInit; 
	LPVOID lpvMem = NULL; 

    handle = CreateFileMapping( 
                INVALID_HANDLE_VALUE, /* use paging file*/
                NULL,                 /* no security attributes*/
                PAGE_READWRITE,       /* read/write access*/
                0,                    /* size: high 32-bits*/
                m_size,            /* size: low 32-bits*/
                NAME_OF_SHARED_MEMORY);     /* name of map object*/
    if (handle == NULL) 
          return NULL; 
 
    /* The first process to attach initializes memory.*/
 
    fInit = (GetLastError() != ERROR_ALREADY_EXISTS); 
    /* Get a pointer to the file-mapped shared memory.*/
    lpvMem = MapViewOfFile( 
        handle,     // object to map view of
        FILE_MAP_WRITE, // read/write access
        0,              // high offset:  map from
        0,              // low offset:   beginning
        0);             // default: map entire file
    if (lpvMem == NULL) 
        return NULL; 

    // Initialize memory if this is the first process.
    if (fInit) {
        memset(lpvMem, '\0', m_size); 
	}
	*hMapObject = handle;
	return (unsigned char *) lpvMem;
}
 
/*
 * Pta_SM_free(HANDLE hMapObject, unsigned char * lpvMem)
 *       HANDLE hMapObject: handle to shared memory
 *       char * lpvMem: pointer to shared memory
 *
 * Note: This function Unmap shared memory from the process's address space.
 */
void Pta_SM_free(HANDLE hMapObject, unsigned char * lpvMem) {
    UnmapViewOfFile((LPVOID)lpvMem); 
    CloseHandle(hMapObject); 
} 

#elif defined SOLARIS
/*Solaris implementation */

/*
 *	Pta_SM_malloc(int m_size,HANDLE * hMapObject,char* optionFileName)
 *           int m_size: size of the memory
 *           HANDLE * hMapObject: handle to the shared memory later can be used for clean up
 *           char* optionFileName: full name for PTA option file this is used to get key for 
 *                                 shared memory on Solaris  
 */
unsigned char * Pta_SM_malloc(int m_size,HANDLE * hMapObject, char* optionFileName) {
   key_t m_shmKey;
   int m_handle;
   void * m_retvalue;
   m_shmKey = ftok(optionFileName, UNIQUE_SHARED_MEMORY_ID);
   m_handle = shmget(m_shmKey, m_size, SHM_R|SHM_W|IPC_CREAT  );
   if(!m_handle){
	return 0;
   } else {
       m_retvalue = shmat(m_handle, 0,SHM_R|SHM_W);
       *hMapObject = m_handle;
       return (unsigned char *) m_retvalue;
   }
}

/*
 * Pta_SM_free(HANDLE hMapObject, unsigned char * lpvMem)
 *       HANDLE hMapObject: handle to shared memory
 *       char * lpvMem: pointer to shared memory
 *
 * Note: This function Unmap shared memory from the process's address space.
 */
void Pta_SM_free(HANDLE hMapObject, unsigned char * lpvMem) {
   shmdt((char *) lpvMem);
   shmctl( hMapObject,IPC_RMID,0);
}
#else
#error WRONG PLATFORM
#endif 



#ifndef _ssc_hash_sh_h
#define _ssc_hash_sh_h 1


/* 
 *  File: ssc_hash.h
 *
 *  Description: This header file contains the definitions
 *  for the super-signing-control hashing functions.
 */

#include "pta.h"
#include "mm.h"


typedef struct {
  MM *pPoolMM;
  hash_table_t *pHashTable;
  int reference_count;
} sscHashPool;

/* Public Hash table stuff. */

void sscPrintHashTable(hash_table_t *htable);
Dll hash_table_t *sscHashInit(sscHashPool **hash_pool, int powerOfTwo);
Dll void sscHashAttach(sscHashPool *hash_pool);
Dll void sscHashDetach(sscHashPool *hash_pool);
Dll void sscHashInsert(hash_table_t *htable, ITEM key, client_data_t *data);
Dll link_t *sscHashSearch(hash_table_t *htable, ITEM key);
Dll link_t *sscHashDelete(hash_table_t *htable, ITEM key);
Dll link_t *sscHashDeleteHasc(hash_table_t *htable, char *hascKey);
Dll int sscHashDeleteISDigest(hash_table_t *htable, char *hascDigest);
Dll void sscHashDestroy(sscHashPool *hash_pool);
Dll hash_table_t *sscHashReset(sscHashPool *hash_pool);
client_data_t *sscInitClientData();
void sscDestroyClientData(client_data_t *cd);
Dll int sscAuthorizeCookie(hash_table_t *htable, char *hascKey, 
                          client_data_t **newClientData);
Dll int sscAuthorizePost(hash_table_t *htable, ITEM key, ITEM *outCert,
                        char *pkcs7, client_data_t **newClientData);

void * sscHash_malloc(size_t size);
void * sscHash_realloc(void *ptr, size_t size);
char * sscHash_strdup(const char *str);
void sscHash_free(void *ptr);

#ifdef DEBUG_HASHMEM
#define sscHash_free(arg) \
	fprintf(stderr, "file:%s line:%d ptr=0x%lx (pid=%d)\n", \
     __FILE__, __LINE__, (unsigned long) (arg), getpid()); \
    sscHash_free(arg);
#endif

/* Macro to return orig ptr if not null, else "null" */
#define IsNullStr(ORG_PTR) ( (ORG_PTR) ? (ORG_PTR) : "<null>" )

#endif

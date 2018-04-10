#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*#include "global.h"*/
/*#include "bsafe2.h"*/

/*#include "ssc.h"*/
#include "ssc_hash_sh.h"
#include <time.h>
#ifdef WIN32
#include <windows.h> /* Sleep. */
#include <process.h>  /* getpid */
#else
#include <unistd.h> /* for pid_t, sleep, getpid, etc.. */
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef DEBUG
#define DEBUG_HASHMEM
#endif


/* static function declarations */
static void sscPrintLink(link_t *l);
static int sscCountLink(link_t *l);
static link_t *sscLinkInit(link_t *next, ITEM key, client_data_t *data);
static int sscHashFn(hash_table_t *htable, ITEM key);
static hash_table_t *sscHash_tableInit(int powerOfTwo);
static void sscHash_tableDestroy(hash_table_t *htable);
static link_t *sscLinkDelete(link_t *l, ITEM key);
static link_t *sscLinkDeleteISDigest(link_t *l, ITEM digest, int *deleted);
static link_t *sscLinkInsert(link_t *list, link_t *newLink);
static link_t *sscLinkSearch(link_t *l, ITEM key);
static link_t *sscLinkGarbageCollect(link_t *l, PTATIME tm);
static void sscLinkDestroy(link_t *l);
static void sscHash_lock(mm_lock_mode mode);
static void sscHash_unlock();
static void sscHash_attach();
static void sscHash_detach();
static void sscHash_destroy();


/*
 * pointer to HashPool stored in the shared mem segment
 */
static sscHashPool *pHashPool = 0;


/* hash table code roughly based on sedgewick, p584 */

static void sscPrintLink(link_t *l) {
  /* Note: expects shared mem to be already locked on entry */
  char *hascData;
  VSVAL_UserCtx ctx = {0};
  while (l) {
	hascData = (char*)sscT_malloc(2*l->key.len+1);
	if (hascData != NULL) {
		VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,(unsigned char*)l->key.data, l->key.len , hascData);
		fprintf(stderr, "%s  d=0x%lx   ", hascData, (unsigned long) l->data);
		sscT_free((unsigned char *)hascData);
	}

    fprintf(stderr, "%lx  %s  ", (unsigned long) l->data->url, l->data->url ? l->data->url : "nil");
    fprintf(stderr, "%lu %lu  ", l->data->absolute_timeout, l->data->inactive_timeout);

    fprintf(stderr, "%s %s\n", ctime(&l->data->absolute_timeout), 
            ctime(&l->data->inactive_timeout));  
    fflush(stderr);
    l = l->next;
  }
}


static int sscCountLink(link_t *l) {

  int c = 0;

  while (l) {
    c++;
    l = l->next;
  }
  return c;
}

void sscPrintHashTable(hash_table_t *htable) {
  int i;
  int max = 0, c;
  int head_count = 0;

  if (htable==0) {
    fprintf(stderr, "(nil htable)\n");
    fflush(stderr);
    return;
  }

  sscHash_lock(MM_LOCK_RD);

  for (i=0; i < htable->size; i++) {
    c = sscCountLink(htable->heads[i]);
    if (c > 0) {
      head_count++;
      fprintf(stderr, "table[%d]\n", i);
      sscPrintLink(htable->heads[i]);
      if (c > max) max = c;
  /*    fprintf(stderr, "\n"); */
    }
    fflush(stderr);
  }

  sscHash_unlock();

  if (head_count == 0) {
    fprintf(stderr, "(empty htable)\n");
  }

  fprintf(stderr, "max=%d\n", max);
  fflush(stderr);

}

/* Inherits the client data, will free it when done. */
static link_t *sscLinkInit(link_t *next, ITEM key, client_data_t *data) {

  link_t *n = 0;

  n = sscHash_malloc(sizeof(link_t));

  if (n==0) return 0;

  n->data = data;

  n->key.len = key.len;
  n->key.data = sscHash_malloc(MAX_DIGEST_LEN);

  if (n->key.data==0) {
    /* free 'data' since we can't inherit it. */
    sscDestroyClientData(data);
    sscHash_free(n);
    return 0;
  }

  memcpy(n->key.data, key.data, key.len);

  if (n) n->next = next;
  
  return n;
}

/* assumes htable->size is a power of two. */
static int sscHashFn(hash_table_t *htable, ITEM key) {
  unsigned int firstWord;

  if (key.len < 4) return 0; /* null values will hash to the first bucket. */

  memcpy(&firstWord, key.data, 4);

  return (firstWord & (htable->size - 1));
}


hash_table_t *sscHashInit(sscHashPool **ppHashPool, int powerOfTwo) {

  int i;
  char tmpfile[30];
  sscHashPool hash_pool = {0};

  if (powerOfTwo>18) {
    gCfg.InfoLog( 0, "Warning: hTable size very large!");
  }

#ifdef DEBUGMSG
    fprintf(stderr, "sscHashInit: powerOfTwo=%d\n", powerOfTwo);
    fflush(stderr);
#endif

  sprintf(tmpfile, "/tmp/sschash%ld", (long) getpid());
  hash_pool.pPoolMM = mm_create(0, tmpfile);

  if ( hash_pool.pPoolMM == 0 ) {

    fprintf(stderr, "sscHashInit: could not create hash pool!\n");
    fprintf(stderr, "sscHashInit:mm_error()-->[%s]\n", IsNullStr(mm_error()));
    fflush(stderr);

    return 0;
  }

  pHashPool = &hash_pool; /* temporarily assign to local hash_pool struct */

#ifdef DEBUGMSG
  fprintf(stderr, "sscHashInit: hash_pool.pPoolMM=0x%lx  size=%lu bytes\n",
          (unsigned long) hash_pool.pPoolMM,
          (unsigned long) mm_available(hash_pool.pPoolMM));
  fflush(stderr);
#endif

  sscHash_lock(MM_LOCK_RW);

  do {

    /* Let's put the pool handle into the shared mem segment, so it's visible
     * to all child procs.
     */
    pHashPool = sscHash_malloc(sizeof(sscHashPool));
    if (pHashPool == 0) break;

    pHashPool->pPoolMM = hash_pool.pPoolMM; /* self-ref to shared mem seg */
    *ppHashPool = pHashPool;  /* Let the caller know where it is */

    sscHash_attach(pHashPool);

    /* Now let's setup the hash table */
    pHashPool->pHashTable = sscHash_tableInit(powerOfTwo);
  } while (0);

  sscHash_unlock();

#ifdef DEBUGMSG
  fprintf(stderr, "sscHashInit: Done - hash memory now avail=%lu bytes\n",
          (unsigned long) mm_available(pHashPool->pPoolMM)); fflush(stderr);
  mm_display_info(pHashPool->pPoolMM);
  fflush(stderr);
#endif

  return pHashPool->pHashTable;
}


static hash_table_t *sscHash_tableInit(int powerOfTwo) {

  int i;

  if (powerOfTwo>18) {
    gCfg.InfoLog( 0, "Warning: hTable size very large!");
  }

#ifdef DEBUGMSG
    fprintf(stderr, "sscHash_tableInit: powerOfTwo=%d\n", powerOfTwo);
    fflush(stderr);
#endif

  do {

    /* Setup the hash table */
    pHashPool->pHashTable = sscHash_malloc(sizeof(hash_table_t));
    if (pHashPool->pHashTable==0) break;

    for (i=0, pHashPool->pHashTable->size = 1; i<powerOfTwo; i++) {
      pHashPool->pHashTable->size *= 2;
    }

#ifdef DEBUGMSG
    fprintf(stderr, "sscHash_tableInit: pHashTable->size=%d bytes\n",
            pHashPool->pHashTable->size);
    fflush(stderr);
#endif

    pHashPool->pHashTable->fn = &sscHashFn;

    pHashPool->pHashTable->heads = 
      sscHash_malloc(pHashPool->pHashTable->size * sizeof(link_t));

    if (pHashPool->pHashTable->heads==0) {
      sscHash_free(pHashPool->pHashTable);
      pHashPool->pHashTable = 0;
      break;
    }

    memset(pHashPool->pHashTable->heads, 0,
           pHashPool->pHashTable->size * sizeof(link_t));
  } while(0);

  return pHashPool->pHashTable;
}

/*
 * Destroy Hash Table
 */
static void sscHash_tableDestroy(hash_table_t *htable) {
  
  int i;

  if (htable) {

#ifdef DEBUGMSG
    fprintf(stderr, "destroying hash table...\n");
    fflush(stderr);
#endif

    for (i=0; i < htable->size; i++) {
      sscLinkDestroy(htable->heads[i]);
    }
    sscHash_free(htable->heads);
    sscHash_free(htable);
  }
  else {
#ifdef DEBUGMSG
    fprintf(stderr, "hash table is null\n");
    fflush(stderr);
#endif
  }
}


void sscHashAttach(sscHashPool *hash_pool) {
  /* Initialize the static pointer for this proc. */
  pHashPool = hash_pool;
  sscHash_lock(MM_LOCK_RW);
  sscHash_attach();
  sscHash_unlock();
}

void sscHashDetach(sscHashPool *hash_pool) {
  if ( pHashPool != hash_pool ) {
    fprintf(stderr, "sscHashDetach: pool mismatch! (pid=%ld)\n",
            (long) getpid());
    fprintf(stderr, "pHashPool=0x%lx  hash_pool=0x%lx\n",
             (unsigned long) pHashPool, (unsigned long) hash_pool);
    fflush(stderr);
  }
  sscHash_lock(MM_LOCK_RW);
  sscHash_detach();
  sscHash_unlock();
}


/* delete an entry with the given key from a hash table bucket. */
static link_t *sscLinkDelete(link_t *l, ITEM key) {

  link_t *t;

  if (l==0) return 0;

  if (ptaKeyEq(key, l->key)) {  
    t = l->next;

    sscDestroyClientData(l->data);

    sscHash_free(l->key.data);
    sscHash_free(l);
    return sscLinkDelete(t, key);
  }
  else {
    l->next = sscLinkDelete(l->next, key);
    return l;
  }
}

/* delete an entry with the given issuer serial digest key from a hash table bucket. */
static link_t *sscLinkDeleteISDigest(link_t *l, ITEM digest, int *deleted) {

  link_t *t;
  ITEM clientISDigest;

  if (l==0) return 0;

  clientISDigest.len = MD5_LEN;

  if (l->data) {
    clientISDigest.data = l->data->iSDigest;
  }
  else {
    clientISDigest.data = 0;
  }

  if (ptaKeyEq(digest, clientISDigest)) {
    t = l->next;

    sscDestroyClientData(l->data);

    sscHash_free(l->key.data);
    sscHash_free(l);
    
    *deleted = 1;
    return sscLinkDeleteISDigest(t, digest, deleted);
  }
  else {
    l->next = sscLinkDeleteISDigest(l->next, digest, deleted);
    return l;
  }
}


static link_t *sscLinkInsert(link_t *list, link_t *newLink) {

  newLink->next = list;

  list = newLink;

  return list;
}

static link_t *sscLinkSearch(link_t *l, ITEM key) {

  if (l==0) return 0;

  if (ptaKeyEq(key, l->key)) return l;
  else return sscLinkSearch(l->next, key);
}

void sscHashInsert(hash_table_t *htable, ITEM key, client_data_t *data) {
  int i = htable->fn(htable, key);
  link_t *newLink;
#ifdef DEBUGMSG
  char *hascData;
#endif

  VSVAL_UserCtx ctx = {0};
  newLink = sscLinkInit(0, key, data);

#ifdef DEBUGMSG
  hascData=(char*)sscT_malloc(key.len*2 + 1);
  if (hascData != NULL) {
	VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,(unsigned char*)key.data, key.len, hascData);
	fprintf(stderr, "sscHashInsert: pid=%ld key=%s\n", (long) getpid(),hascData);
	sscT_free((unsigned char *)hascData);
  }
  fflush(stderr);
#endif

  sscHash_lock(MM_LOCK_RW);
  htable->heads[i] = sscLinkInsert(htable->heads[i], newLink);
  sscHash_unlock();
}

/*
** Delete everything that has an expiration time < tm.
** Should pass in a time before the current time, to give users expired error msgs.
*/
static link_t *sscLinkGarbageCollect(link_t *l, PTATIME tm) {

  link_t *t;
#ifdef DEBUGMSG
  char *hascData;
#endif

  VSVAL_UserCtx ctx = {0};
  if (l==0) return 0;

#ifdef DEBUGMSG
  fprintf(stderr, "comparing tm %lu >= abs_tmout %lu\n", l->data->absolute_timeout, tm);
  fflush(stderr);
#endif

  if (l->data && (tm >= l->data->absolute_timeout)) {

    t = l->next;

#ifdef DEBUGMSG
    hascData=(char*)sscT_malloc(l->key.len*2 + 1);
    if (hascData != NULL) {
		VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,(unsigned char*)l->key.data, l->key.len, hascData);
		fprintf(stderr, "delete link %s\n", hascData);
		fflush(stderr);
		sscT_free((unsigned char *)hascData);
	}
#endif

    sscDestroyClientData(l->data);

    sscHash_free(l->key.data);
    sscHash_free(l);
    return sscLinkGarbageCollect(t, tm);
  }
  else {
    l->next = sscLinkGarbageCollect(l->next, tm);
    return l;
  }
}

/* Does a search, and also does gargabe collection of expired items on this bucket. */
link_t *sscHashSearchGarbageCollect(hash_table_t *htable, ITEM key) {

  int i = htable->fn(htable, key);
  link_t *link;
  PTATIME tm = 0;
#ifdef DEBUGMSG
  char *hascData;
#endif

  VSVAL_UserCtx ctx = {0};

  if (key.len < 4) return 0; /* Null keys aren't here. */

  pta_time(&tm);
  tm -= gCfg.garbageTime; /* This is how long we keep old links in the cache. */
  /* This allows us to give an 'expired' message on the login page. */

#ifdef DEBUGMSG
  fprintf(stderr, "sscHashSearchGarbageCollect: pid=%ld\n", (long) getpid());
  fflush(stderr);
#endif

  /* Must do the garbage collect first. Otherwise we can invalidate the ptr we found. */
  sscHash_lock(MM_LOCK_RW);
  htable->heads[i] = sscLinkGarbageCollect(htable->heads[i], tm);
  sscHash_unlock();

#ifdef DEBUGMSG
  hascData=(char*)sscT_malloc(key.len*2 + 1);
  if (hascData != NULL) {
	VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,(unsigned char*)key.data, key.len, hascData);
	fprintf(stderr, "search link GC  %d for %s\n", i, hascData);
	fflush(stderr);
	sscT_free((unsigned char *)hascData);
  }
#endif

  sscHash_lock(MM_LOCK_RD);
  link = sscLinkSearch(htable->heads[i], key);
  sscHash_unlock();

#ifdef DEBUGMSG
  fprintf(stderr, "got %lx\n", (unsigned long) link);
  fflush(stderr);
#endif

  return link;
}


link_t *sscHashSearch(hash_table_t *htable, ITEM key) {

  int i = htable->fn(htable, key);
  link_t *link;
#ifdef DEBUGMSG
  char *hascData;
#endif

  VSVAL_UserCtx ctx = {0};
  if (key.len < 4) return 0; /* Null keys aren't here. */

#ifdef DEBUGMSG
  fprintf(stderr, "sscHashSearch: pid=%ld\n", (long) getpid());
  hascData=(char*)sscT_malloc(key.len*2 + 1);
  if (hascData != NULL) {
	VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx, (unsigned char*)key.data, key.len, hascData);
	fprintf(stderr, "search link %d for %s\n", i, hascData);
	sscT_free((unsigned char *)hascData);
  }
  fflush(stderr);
#endif

  sscHash_lock(MM_LOCK_RD);
  link = sscLinkSearch(htable->heads[i], key);
  sscHash_unlock();

#ifdef DEBUGMSG
  fprintf(stderr, "got %lx\n", (unsigned long) link);
  fflush(stderr);
#endif

  return link;
}


link_t *sscHashDelete(hash_table_t *htable, ITEM key) {

  int i = htable->fn(htable, key);
#ifdef DEBUGMSG
  char *hascData;
#endif

  VSVAL_UserCtx ctx = {0};

#ifdef DEBUGMSG
  hascData=(char*)sscT_malloc(key.len*2 + 1);
  if (hascData != NULL) {
	VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,(unsigned char*)key.data, key.len, hascData);
	fprintf(stderr, "sscHashDelete: pid=%ld key=%s\n", (long) getpid(),hascData);
	fflush(stderr);
	sscT_free((unsigned char *)hascData);
  }
#endif

  sscHash_lock(MM_LOCK_RW);
  htable->heads[i] = sscLinkDelete(htable->heads[i], key);
  sscHash_unlock();

  return 0;
}

link_t *sscHashDeleteHasc(hash_table_t *htable, char *hascKey) {

  ITEM key = {0,0};
  unsigned char keyBuf[MAX_DIGEST_LEN];

  key.data = keyBuf;
  ptaHasc2ItemBuf(hascKey, &key);

  return sscHashDelete(htable, key);
}

/* return true if it did delete something. */
int sscHashDeleteISDigest(hash_table_t *htable, char *hascDigest) {

  ITEM iSDigest = {0,0};
  unsigned char digestBuf[MAX_DIGEST_LEN];
  int i, deleted = 0;

  iSDigest.data = digestBuf;
  ptaHasc2ItemBuf(hascDigest, &iSDigest);

  
  sscHash_lock(MM_LOCK_RW);
  for (i=0; i< htable->size; i++) {    
    htable->heads[i] = sscLinkDeleteISDigest(htable->heads[i], iSDigest, &deleted);
  }
  sscHash_unlock();

  return deleted;
}


static void sscLinkDestroy(link_t *l) {

  link_t *t;

  while (l) {
    
    t = l->next;

    /* free 'data' */
    sscDestroyClientData(l->data);

    sscHash_free(l->key.data);
    sscHash_free(l);
    
    l = t;
  }

}

/*
 * Destroy Hash Table, then Pool
 */
void sscHashDestroy(sscHashPool *hash_pool) {
  sscHash_lock(MM_LOCK_RW);
  sscHash_tableDestroy(hash_pool->pHashTable);
  sscHash_unlock(); /* NSW: or should we just leave locked here??? */
  sscHash_destroy();
}


/*
 * Reset Hash Table
 */
hash_table_t *sscHashReset(sscHashPool *hash_pool) {
  int size = ptaLogBase2(hash_pool->pHashTable->size);
  hash_table_t *htable = 0;

  sscHash_lock(MM_LOCK_RW);
  sscHash_tableDestroy(hash_pool->pHashTable);
  htable = sscHash_tableInit(size);
  sscHash_unlock();
  return htable;
}



/* This is where we store data for a particular client. */

client_data_t *sscInitClientData() {

  client_data_t *cd = 0;

  cd = (client_data_t *) sscHash_malloc(sizeof(client_data_t));

  if (cd==0) return 0;
  
  memset(cd, 0, sizeof(client_data_t));

  return cd;
}


void sscDestroyClientData(client_data_t *cd) {

  if (cd) {
    sscHash_free((unsigned char *) (cd->url));
    sscHash_free((unsigned char *) (cd->pkcs7));
    sscHash_free((unsigned char *) (cd->userName));
    sscHash_free(cd->cert.data);
  }
  sscHash_free((unsigned char *) cd);
}



/* Looks up the key in the hash table and sees if it is authorized. */
/* Returns CS_VALID, CS_SSC_AUTH_EXPIRED, or  CS_SSC_NOT_AUTH. */
int sscAuthorizeCookie(hash_table_t *htable, char *hascKey, 
                      client_data_t **newClientData) {

  ITEM key = {0,0};
  unsigned char keyBuf[MAX_DIGEST_LEN];
  link_t *link;
  int status = 0, certStatus = 0;
  client_data_t *clientData;
  char *userName = 0;
  PTATIME tm = 0, statusExpires = 0;

  key.data = keyBuf;
  ptaHasc2ItemBuf(hascKey, &key);

  link = sscHashSearch(htable, key);

  /* If we found it in the hash table, check it out. */
  if (link) {

    clientData = link->data;
    *newClientData = clientData;

    /* See if it's authorized (not just in the table waiting for a post.) */
    if (clientData->authorized) {
      
      /* See if the authorization has expired. */
      pta_time(&tm);
#ifdef DEBUGMSG
      fprintf(stderr, "tm=%lu  abs_tmout=%lu  inac_tmout=%lu\n",
                 tm,
                 clientData->absolute_timeout,
                 clientData->inactive_timeout);
      fflush(stderr);
#endif

      if ((tm < clientData->inactive_timeout) &&
          (tm < clientData->absolute_timeout)) {

        /* Bump the inactivity timeout. */
        clientData->inactive_timeout = tm + gCfg.inactiveTimeout;

        if (tm < clientData->revocation_timeout) {
          status = CS_VALID; /* if our revocation info hasn't expired, we're good. */
        }
        else {
          /* would be CS_VALID, but still need to check revocation... */
          if (gCfg.fnGetRevocationInfo(&clientData->cert, &certStatus, 
                                       &statusExpires, &userName)==0) {
            status = certStatus;

            clientData->revocation_timeout = statusExpires;
            /* No need to update clientData->userName since the cert hasn't changed. */
          }
          else {
            status = CS_SSC_COOKIE_REVOKED;
          }
          
          /* If the cert got revoked, it's no longer authorized. */
          if (certStatus != CS_VALID) {
            clientData->authorized = 0; 
          }

        }
      }
      else {
        status = CS_SSC_COOKIE_EXPIRED;
      }

    }
    else {
      status = CS_SSC_COOKIE_UNAUTH;
    }
  }
  else {
    /* Not found in hash table. */
    status = CS_SSC_COOKIE_BAD;
  }

  return status;
}



/* Looks up the key in the hash table and sees if it is expired.
 * If not, sets the authorized bit.
 * Returns CS_VALID, CS_SSC_AUTH_EXPIRED, or  CS_SSC_BAD_AUTH.
 * Inherits the certItem, pkcs7.
 */
int sscAuthorizePost(hash_table_t *htable, ITEM key, ITEM *certItem,
                    char *pkcs7, client_data_t **newClientData) {

  link_t *link;
  int status = 0;
  PTATIME tm = 0, statusExpires = 0;
  client_data_t *clientData;
  int certStatus = 0;
  char *userName = 0;
  VSVAL_UserCtx userCtx={0};

  userCtx.logFn = gCfg.InfoLog;
  link = sscHashSearchGarbageCollect(htable, key);

  /* If we found it in the hash table, check it out. */
  if (link) {

    clientData = link->data;

    /* Save the cert item. */
    if (! gCfg.noSaveCerts) {

      /* If a bad version was already posted, free it. */
      sscHash_free((unsigned char *) clientData->cert.data);

      clientData->cert = *certItem; 
    }

    /* Also save the signature. */
    /* If a bad version was already posted, free it. */
    sscHash_free((unsigned char *) clientData->pkcs7);
    clientData->pkcs7 = pkcs7;
    
	/*vsCertISDigest(gCfg.vsValSDK, &internalCtx, clientData->iSDigest, certItem);*/
	VSVAL_CertMD5ISDigest(gCfg.vsValSDK,&userCtx, certItem->data, certItem->len,clientData->iSDigest);

    *newClientData = clientData;

    /* See if the authorization has expired. */
    pta_time(&tm);

    /* For signature posts, only check against the absolute timeout. */
    if (tm < clientData->absolute_timeout) {

      *newClientData = clientData;

      /* Bump the inactivity timeout. */
      clientData->inactive_timeout = tm + gCfg.inactiveTimeout;

      /* would be CS_VALID, but still need to check revocation... */
      if (gCfg.fnGetRevocationInfo(certItem, &certStatus,
                                   &statusExpires, &userName)==0) {
        status = certStatus;

        if (status == CS_VALID) {
          clientData->authorized = 1;
        }

        if (gCfg.noSaveCerts) { 
          /* We won't be able to use the cert to re-check revocation. */
          /* User must replay the cert. */
          clientData->absolute_timeout = vsMIN(clientData->absolute_timeout,
                                               clientData->revocation_timeout);
          clientData->revocation_timeout = clientData->absolute_timeout;
        }
        else {
          clientData->revocation_timeout = statusExpires;
        }
        
        /* Save the new subject dn. (Should already be one there.) */
        if (userName) {
          sscHash_free((unsigned char *) clientData->userName);
          clientData->userName = sscHash_strdup(userName ? userName : "client");
        }
      }
      else {
        status = CS_SSC_POST_REVOKED;
      }
      
    }
    else {
      status = CS_SSC_POST_EXPIRED;
    }

  }
  else {
    status = CS_SSC_POST_BAD;

    /* In this case we can't save these in the hash table. */
    /* Free them now. */
    sscHash_free((unsigned char *) pkcs7);
    sscHash_free((unsigned char *) (certItem->data));
  }

  return status;
}



/* Interface to Hash Pool */

void * sscHash_malloc(size_t size) {

  void *ptr;

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_malloc: malloc'g size=%lu bytes (pid=%ld)\n", 
     (unsigned long) size, (long) getpid());
  fflush(stderr);
#endif

  ptr = mm_malloc(pHashPool->pPoolMM, size);

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_malloc: size=%lu ptr=0x%lx (pid=%ld)\n", 
     (unsigned long) size, (unsigned long) ptr, (long) getpid());
  fflush(stderr);
#endif

  if (ptr==0) {
    fprintf(stderr, "mm_malloc() error trying to get %ld bytes (pid=%ld)\n",
            (long) size, (long) getpid()); fflush(stderr);
    fprintf(stderr, "mm_error()-->[%s]\n", IsNullStr(mm_error()));
    fflush(stderr);
  }

  return ptr;
}

void * sscHash_realloc(void *oldptr, size_t size) {

  void *newptr;

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_realloc: malloc'g size=%lu bytes (pid=%ld)\n", 
     (unsigned long) size, (long) getpid());
  fflush(stderr);
#endif

  newptr = mm_realloc(pHashPool->pPoolMM, oldptr, size);

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_realloc: size=%lu oldptr=0x%lx newptr=0x%lx (pid=%ld)\n", 
     (unsigned long) size, (unsigned long) oldptr, (unsigned long) newptr,
     (long) getpid());
  fflush(stderr);
#endif

  if (newptr==0) {
    fprintf(stderr, "mm_realloc() error trying to get %ld bytes (pid=%ld)\n",
           (long) size, (long) getpid());
    fprintf(stderr, "mm_error()-->[%s]\n", IsNullStr(mm_error()));
    fflush(stderr);
  }

  return newptr;
}

char * sscHash_strdup(const char *oldstr) {
  char *newstr;

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_strdup: oldptr=0x%lx (pid=%ld)\n", 
     (unsigned long) oldstr, (long) getpid());
  fflush(stderr);
#endif

  newstr = mm_strdup(pHashPool->pPoolMM, oldstr);

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_strdup: oldptr=0x%lx newptr=0x%lx (pid=%ld)\n", 
     (unsigned long) oldstr, (unsigned long) newstr, (long) getpid());
  fflush(stderr);
#endif

  return newstr;
}

#undef sscHash_free

void sscHash_free(void *ptr) {

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_free: ptr=0x%lx (pid=%ld)\n", 
     (unsigned long) ptr, (long) getpid());
  fflush(stderr);
#endif

  mm_free(pHashPool->pPoolMM, ptr);

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_free: ptr=0x%lx freed (pid=%ld)\n", 
     (unsigned long) ptr, (long) getpid());
  fflush(stderr);
#endif
}

static void sscHash_lock(mm_lock_mode mode) {

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_lock: (pid=%ld)\n", (long) getpid());
  fflush(stderr);
#endif

  if ( mm_lock(pHashPool->pPoolMM, mode) == FALSE ) {
    fprintf(stderr, "mm_lock:mm_error()-->[%s]\n", IsNullStr(mm_error()));
    fflush(stderr);
  }
}

static void sscHash_unlock() {

#ifdef DEBUG_HASHMEM
  fprintf(stderr, "sscHash_unlock: (pid=%ld)\n", (long) getpid());
  fflush(stderr);
#endif

  if ( mm_unlock(pHashPool->pPoolMM) == FALSE ) {
    fprintf(stderr, "mm_unlock:mm_error()-->[%s]\n", IsNullStr(mm_error()));
    fflush(stderr);
  }
}

static void sscHash_attach() {
  pHashPool->reference_count += 1;
#ifdef DEBUGMSG
  fprintf(stderr, "sscHash_attach: ref_cnt=%d  (pid=%ld)\n",
          pHashPool->reference_count, (long) getpid());
  fflush(stderr);
#endif
}

static void sscHash_detach() {
  pHashPool->reference_count -= 1;
#ifdef DEBUGMSG
  fprintf(stderr, "sscHash_detach: ref_cnt=%d  (pid=%ld)\n",
          pHashPool->reference_count, (long) getpid());
  fflush(stderr);
#endif
}

static void sscHash_destroy() {

  MM *pPoolMM;

  if ( pHashPool == 0 ) {
#ifdef DEBUGMSG
    fprintf(stderr, "sscHash_destroy: pHashPool is null  (pid=%ld)\n",
             (long) getpid());
    fflush(stderr);
#endif
    return;
  }

  pPoolMM = pHashPool->pPoolMM;

  if ( pPoolMM != NULL ) {
    sscHash_detach();
    sscHash_free(pHashPool);
    pHashPool = NULL;
#ifdef DEBUGMSG
    fprintf(stderr, "destroying pPoolMM=0x%lx (pid=%ld)\n",
             (unsigned long) pPoolMM, (long) getpid());
    fflush(stderr);
#endif
    mm_destroy(pPoolMM);
#ifdef DEBUGMSG
    fprintf(stderr, "sscHash_destroy: pPoolMM destroyed  (pid=%ld)\n", (long) getpid());
    fflush(stderr);
#endif
  }
  else {
#ifdef DEBUGMSG
    fprintf(stderr, "sscHash_destroy: pPoolMM is null  (pid=%ld)\n",
             (long) getpid());
    fflush(stderr);
#endif
  }
}

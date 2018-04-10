/*
 * $Revision: $
 * $Header: $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/


//#include "stdafx.h"
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <stdio.h>
#include <memory.h>
#include "vsrandom.h"
#include "md5.h"

#ifdef WIN32
#include "windows.h"
#endif


#define kTOTAL_BYTES             34000
#define kBYTE_INCREMENT          3000
#define kPOOL_SIZE               10 * 1024
//#define kPOOL_SIZE               96

/* We know we are using MD5, and that it takes 64 and returns 16.
 * These are #defines, so they can be changed if you change
 * the digest algorithm.
 */
#define kDIGEST_DATA_SIZE        64
#define kDIGEST_RESULT_SIZE      16

#define eFALSE 0
#define eTRUE  1


/* gPool is a pointer to the pool of random data.
 * gNext is a pointer to the next spot in the pool
 * from which to return random numbers. gSmallNext
 * is a pointer to the next spot in the pool to 
 * which small entropy is added.
 */
static unsigned char *gPool = NULL;
static unsigned char *gNext = NULL;
static unsigned int  *gSmallNext = NULL;
  
static int gPRNGinitialized = eFALSE;


static void AddLargeEntropy (void);
static void *AddSmallEntropy (void *);
static void MixRandomPool (void);


typedef struct VSBlock {
  unsigned int length;
  void         *data;
} VSBlock;



/*******************************************************************/
int Init_PRNG (void)
/*
 * Initialize the pseudo-random number generator.
 */
{
  int status = VSERR_INTERNAL_ERROR;

  do {
    gPool = (unsigned char *) malloc (kPOOL_SIZE);

    if (gPool == NULL) {
      status = VSERR_OUT_OF_MEMORY;
      break;
    }

    gNext = gPool;
    gSmallNext = (unsigned int *) gPool;

    AddLargeEntropy();

    gPRNGinitialized = eTRUE;

#ifdef WIN32
    HANDLE        threadHandle;
    unsigned long threadId;
 
    threadHandle = CreateThread (NULL, 0,
      (LPTHREAD_START_ROUTINE) AddSmallEntropy, (LPVOID) 0, 0, &threadId);
    SetThreadPriority (threadHandle, THREAD_PRIORITY_BELOW_NORMAL);
    status = VSERR_SUCCESS;
#endif
  } while (0);

  return (status);
}



/*******************************************************************/
static void AddLargeEntropy (void)
/*
 * Add a large chunk of entropy to the pseudo-random number generator.
 * I expect that this will not get called very frequently.
 */
{
#ifdef WIN32
  PPERF_DATA_BLOCK perfData = NULL;    
  DWORD            currentSize, bufferSize = kTOTAL_BYTES;
  LONG             rv = 0;
#endif
#ifdef SOLARIS
  unsigned char    *perfData = NULL;    
  int              bufferSize = kTOTAL_BYTES;
#endif
  unsigned int     *pool, *seed, i;

#ifdef WIN32
  /* Keep track of the current size in a separate variable, in
   * case the call returns ERROR_MORE_DATA but modifies bufferSize.
   */
  currentSize = bufferSize;
#endif

  do {
#ifdef WIN32
    perfData = (PPERF_DATA_BLOCK) malloc (bufferSize + 256);
    while ((rv = RegQueryValueEx (HKEY_PERFORMANCE_DATA, "Global", 
        NULL, NULL,( LPBYTE) perfData, &bufferSize)) == ERROR_MORE_DATA) {
      currentSize += kBYTE_INCREMENT;
			bufferSize = currentSize;
      perfData = (PPERF_DATA_BLOCK) realloc (perfData, bufferSize + 256);    
    }

    if (rv != 0) {
      break;
    }
#endif

    /* Initialize the pool by "folding" the performance data over
     * the pool as many times as will fit. We don't clear the pool
     * before we start because that would make it more deterministic.
     */
    pool = (unsigned int *) gPool;
    seed = (unsigned int *) perfData;

    while (bufferSize >= kPOOL_SIZE) {
      for (i = 0; i < kPOOL_SIZE; i += sizeof (unsigned int)) {
        *pool++ ^= *seed++;
      }
      bufferSize -= kPOOL_SIZE;
      pool = (unsigned int *) gPool;
    }

  } while (0);

  free (perfData);
#ifdef WIN32
  RegCloseKey (HKEY_PERFORMANCE_DATA);
#endif
}



/*******************************************************************/
int GetRandom (unsigned char *block, unsigned int blockLen)
/*
 * Return an array of random numbers of the requested size.
 */
{
  int  status = VSERR_INTERNAL_ERROR;
  unsigned int bytesLeft = kPOOL_SIZE - (gNext - gPool);

  do {
     MixRandomPool();

    /* If someone asks for more random numbers than we
     * have in the pool, I just return an error.
     * This is not very good, but I don't expect anyone
     * to ask for more than kPOOL_SIZE.
     */

    if (blockLen > kPOOL_SIZE) {
			status = VSERR_TOOBIG;
      break;
    }

    /* First handle the simple case: there are enough bytes
     * between gNext and the end of the pool to satisy the
     * request.
     */
    if (blockLen <= bytesLeft) {
      memcpy (block, gNext, blockLen);
      gNext += blockLen;
    } else {
      /* Not enough bytes left from gNext to the end of the pool.
       * Do two copies.
       */
      memcpy (block, gNext, bytesLeft);
      gNext = gPool;
      memcpy (block + bytesLeft, gNext, (blockLen - bytesLeft));
      gNext += (blockLen - bytesLeft);
    }

    status = VSERR_SUCCESS;

  } while (0);

  return (status);
}


/*******************************************************************/
static void MixRandomPool (void)
/*
 * Mix up the random pool.
 */
{
  VSBlock       dataBlock, digestBlock;
  unsigned int  i;
  unsigned char tmpPool[kDIGEST_DATA_SIZE];

  dataBlock.data = tmpPool;
  dataBlock.length = kDIGEST_DATA_SIZE;

  /* We use the tmpPool to form a contiguous block of size 
   * kDIGEST_DATA_SIZE to digest. Except for the edges, where
   * we wrap, we digest the previous 16 and following 48 bytes
   * to make a new 16-byte chunk.
      kDIGEST_RESULT_SIZE   kDIGEST_DATA_SIZE - kDIGEST_RESULT_SIZE
           |         |               |
           v         v               v
       |        |        |                  |
       |        |        |                  |
       |........|        |..................|
       |        |        |                  |
     +-+--------+xxxxxxxx+------------------+--------------------+
                     ^        gPool
                     |
          digest inserted here

   */
  for (i = 0; i < kPOOL_SIZE; i += kDIGEST_RESULT_SIZE) {
    if (i < kDIGEST_RESULT_SIZE) {
      /* Left edge boundary case
       */
      memcpy (tmpPool, gPool + kPOOL_SIZE - kDIGEST_RESULT_SIZE, kDIGEST_RESULT_SIZE);
      memcpy (tmpPool + kDIGEST_RESULT_SIZE, gPool + kDIGEST_RESULT_SIZE, 
        kDIGEST_DATA_SIZE - kDIGEST_RESULT_SIZE);

    } else {
      /* Easy to get the first chunk. Check for boundary condition
       * for the second chunk.
       */
      memcpy (tmpPool, gPool + i - kDIGEST_RESULT_SIZE, kDIGEST_RESULT_SIZE);
      
      if (i > (kPOOL_SIZE - kDIGEST_DATA_SIZE)) {
        /* Right edge boundary cases
         */
        memcpy (tmpPool + kDIGEST_RESULT_SIZE, gPool + i + kDIGEST_RESULT_SIZE,
          kPOOL_SIZE - i - kDIGEST_RESULT_SIZE);
        memcpy (tmpPool + kDIGEST_RESULT_SIZE + (kPOOL_SIZE - i - kDIGEST_RESULT_SIZE), gPool,
          kDIGEST_DATA_SIZE - (kPOOL_SIZE - i));
      } else { 
        memcpy (tmpPool + kDIGEST_RESULT_SIZE, gPool + i + kDIGEST_RESULT_SIZE, kDIGEST_DATA_SIZE - kDIGEST_RESULT_SIZE);
      }
    }
    
    digestBlock.data = gPool + i;
    digestBlock.length = kDIGEST_RESULT_SIZE;

    if (DigestDataAlloc (&dataBlock, &digestBlock) != VSERR_SUCCESS) {
      int x = 0;      // placeholder for a breakpoint
    }
  }
}



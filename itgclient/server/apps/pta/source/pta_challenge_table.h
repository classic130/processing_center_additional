/**
 *	PTA_CHALLENGE_TABLE
 *	This table is used to store fixed size keys and values such as 
 *      challenge and expiration time. The whole table is stored on 
 *      a block of pre-allocated memory.

 *	Bin Zou 9/29/01
 */
#ifndef _VS_PTA_CHALLENGE_TABLE_
#define _VS_PTA_CHALLENGE_TABLE_ 1

#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

#include "pta.h"
#ifndef _ITEM_
#define _ITEM_ 1
typedef struct {
  unsigned char *data;
  unsigned int len;
} ITEM;
#endif

typedef struct {
  unsigned char  * m_ChallengePool;
  int m_KeyLen;
  int m_ValueLen;
  int m_EntryLen;
  int m_TableSize;
} PTA_CHALLENGE_TABLE;

/* error code definitions */
#define VS_PTA_CT_ERROR_BASE  8900
#define VS_PTA_CT_WRONG_VALUE_LENGTH  (VS_PTA_CT_ERROR_BASE + 1)
#define VS_PTA_CT_WRONG_KEY_SIZE (VS_PTA_CT_ERROR_BASE + 2)
#define VS_PTA_CT_CHALLENGE_VALID (VS_PTA_CT_ERROR_BASE + 3)
#define VS_PTA_CT_CHALLENGE_EXPIRED (VS_PTA_CT_ERROR_BASE + 4)
#define VS_PTA_CT_CHALLENGE_UNFOUND (VS_PTA_CT_ERROR_BASE + 5)
#define VS_PTA_CT_EXCEEDED_SIZE (VS_PTA_CT_ERROR_BASE + 6)
#define VS_PTA_CT_INIT_ERROR (VS_PTA_CT_ERROR_BASE + 7)
#define VS_PTA_TOKEN_EXPIRED  (VS_PTA_CT_ERROR_BASE + 8)
#define VS_PTA_TOKEN_VALID  (VS_PTA_CT_ERROR_BASE + 9)
#define VS_PTA_TOKEN_ERROR_SEARCH_CACHE_TABLE  (VS_PTA_CT_ERROR_BASE + 10)
#define VS_PTA_TOKEN_EXCEEDED_LIMIT_TRIES  (VS_PTA_CT_ERROR_BASE + 11)
#define VS_PTA_TOKEN_SIGNATURE_NO_MATCH  (VS_PTA_CT_ERROR_BASE + 12)
#define VS_PTA_CT_MAX_ERROR (VS_PTA_CT_ERROR_BASE + 13)

#define VS_PTA_CT_OK 0
#define VS_PTA_TOKEN_OK 0

/* functions, CT stands for Challenge Table */
int Pta_CT_Init(PTA_CHALLENGE_TABLE *ptaChallengeTable, unsigned char * buffer, int BufferLen,int keyLen, int powerOfTwo);
int Pta_CT_Insert( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key, PTATIME *value);
int Pta_CT_Delete( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key);
int Pta_CT_Search( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key, int* index);
int Pta_CT_ValidateChallenge( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key);
void Pta_CT_PrintTable(PTA_CHALLENGE_TABLE *ptaChallengeTable);
char * Pta_CT_ErrorString (int status);

#ifdef __cplusplus
}
#endif

#endif

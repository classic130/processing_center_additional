#include "pta.h"
#include "pta_challenge_table.h"
#include <string.h>


/*
 *  PTA_CT_HashFn(PTA_CHALLENGE_TABLE *ptaChallengeTable, ITEM key)
 *
 *  This function calculate an index based on the first 4 bytes of the key
 */
static int PTA_CT_HashFn(PTA_CHALLENGE_TABLE *ptaChallengeTable, ITEM key) {
  unsigned int firstWord;

  if (key.len < 4) return 0; /* null values will hash to the first bucket. */
  memcpy(&firstWord, key.data, 4);
  return (firstWord & (ptaChallengeTable->m_TableSize - 1));
}

/*
 *  Table initialization
 */
int Pta_CT_Init(PTA_CHALLENGE_TABLE *ptaChallengeTable, unsigned char * buffer,int buffLen, int keyLen, int powerOfTwo) {
	int i;
	ptaChallengeTable->m_EntryLen = keyLen + sizeof(PTATIME) + 1;
	ptaChallengeTable->m_ChallengePool = buffer;
	ptaChallengeTable->m_KeyLen = keyLen;
	ptaChallengeTable->m_ValueLen = sizeof(PTATIME);

    for (i=0, ptaChallengeTable->m_TableSize = 1; i<powerOfTwo; i++) {
      ptaChallengeTable->m_TableSize *= 2;
    }

	/* check if the there is enough buffer located*/
    if(ptaChallengeTable->m_TableSize*ptaChallengeTable->m_EntryLen> buffLen) {		 
		return VS_PTA_CT_INIT_ERROR;
	}

	/* pre-set all usage byte to 0 
	 * (This is removed because if multiple processes initialize this
         * we will lose the data. Instead, the memory is already zeroed when 
	 * shared memory is created 
	 * unsigned char * position;
	 * for (i=0; i< ptaChallengeTable->m_TableSize; i++) {
         *		position = buffer + i * ptaChallengeTable->m_EntryLen;
         *		*position = 0;
	 * }
         */
	return VS_PTA_CT_OK;
}

/* 
 * This function find a available entry and insert the value. It also 
 * overwrite the entry where the expiration time is older than current time
 */
int Pta_CT_Insert_GC( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key, PTATIME *value, int indexBegin, int indexEnd ) {
    int  i;
	unsigned char *position;
    PTATIME currentTime = 0, expireTime = 0;

	i = indexBegin;
	do {
		position = 	(unsigned char*) ptaChallengeTable->m_ChallengePool + i * ptaChallengeTable->m_EntryLen;
		if(*position == 0) {
			*position = 1;
			memcpy(position+1,key.data,key.len);
			memcpy(position+1+key.len, value, sizeof(PTATIME));
			return VS_PTA_CT_OK;
		} else {
			pta_time(&currentTime);
			memcpy(&expireTime, position + 1 + ptaChallengeTable->m_KeyLen, ptaChallengeTable->m_ValueLen);
			if( currentTime > expireTime) {
				/* set key */
				memcpy(position+1,key.data,key.len);
				memcpy(position+1+key.len, value, sizeof(PTATIME));
				return VS_PTA_CT_OK;
			}
		}
		i++;
	} while(i <  indexEnd);
	/* reached the bottom of the table, return error */
	return VS_PTA_CT_EXCEEDED_SIZE;
}

/*
 * Insert an entry to hash table, it first tries to insert it to the entry at index. 
 * If the entry at index is in use, it tries to insert to the next entry untill the bottom
 * If it still fails, it tries to insert from the top of the table downward.
 */
int Pta_CT_Insert( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key, PTATIME *value) {
	/* get an index */
	unsigned char *position;
	int i = PTA_CT_HashFn(ptaChallengeTable, key);
	position = ptaChallengeTable->m_ChallengePool + i * ptaChallengeTable->m_EntryLen;
	
	/* check if this is in use*/
	if(*position == 0) {
		/* set in use */
		*position = 1 ;
		/* set key */
		memcpy(position+1,key.data,key.len);
		memcpy(position+1+key.len, value, sizeof(PTATIME));
		return VS_PTA_CT_OK;
	} else {
		/* first try to insert from current to end*/
		if( Pta_CT_Insert_GC( ptaChallengeTable, key, value,i,ptaChallengeTable->m_TableSize ) == VS_PTA_CT_OK) {
			return VS_PTA_CT_OK;
		} else { /*then from begining to current*/
			return Pta_CT_Insert_GC( ptaChallengeTable, key, value,0, i );
		}
	}
}

/*
 * search the key in specified region 
 */
int Pta_CT_Search_GC( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key, int *index, int indexBegin, int indexEnd ){
	unsigned char * position;
	int i;
	i = indexBegin;
	do {
		position = ptaChallengeTable->m_ChallengePool + i * ptaChallengeTable->m_EntryLen;
		if(*position >=	1) {
			if(memcmp(key.data,position + 1, key.len)==0) {
				*index = i;
				return VS_PTA_CT_OK;
			}
		}
		i++;
	} while (i <  indexEnd);
	return VS_PTA_CT_CHALLENGE_UNFOUND;
}
 
/*
 * Search an entry based on key
 */
int Pta_CT_Search( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key, int *index){
	unsigned char * position;
	int i = PTA_CT_HashFn(ptaChallengeTable, key);
	position = ptaChallengeTable->m_ChallengePool + i * ptaChallengeTable->m_EntryLen;
	if(*position >=	1) {
		if(memcmp(key.data,position + 1, key.len)==0) {
			*index = i;
			return VS_PTA_CT_OK;
		}
	}
	if(Pta_CT_Search_GC( ptaChallengeTable,key, index,i,ptaChallengeTable->m_TableSize) == VS_PTA_CT_OK) {
		return VS_PTA_CT_OK;
	} else {
		return Pta_CT_Search_GC( ptaChallengeTable,key, index,0,i);
	}
	
	return VS_PTA_CT_CHALLENGE_UNFOUND;
}

/*
 * remove an entry
 */
int Pta_CT_Delete( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key){
	unsigned char * position;
	int index;
	if( Pta_CT_Search( ptaChallengeTable,key, &index) == VS_PTA_CT_OK) {
		position = ptaChallengeTable->m_ChallengePool + index * ptaChallengeTable->m_EntryLen;
		*position = 0;
	}
	return VS_PTA_CT_OK;
}

/*
 * validate challenge is in the table and current
 */
int Pta_CT_ValidateChallenge( PTA_CHALLENGE_TABLE *ptaChallengeTable,ITEM key) {
	unsigned char * position;
	PTATIME currentTime, expireTime;
	int index;
	if( Pta_CT_Search( ptaChallengeTable,key, &index) == VS_PTA_CT_OK) {
		position = ptaChallengeTable->m_ChallengePool + index * ptaChallengeTable->m_EntryLen;
                /* not going to clean the entry because Policy server might come back again*/
		/* *position = 0; */ 
		/* check if current entry expire */
		pta_time(&currentTime);
		memcpy(&expireTime,position + 1 + ptaChallengeTable->m_KeyLen, ptaChallengeTable->m_ValueLen);
		if( currentTime < expireTime) {
			return VS_PTA_CT_CHALLENGE_VALID;
		} else {
                   /* clean expired entry*/
		   *position = 0;  
		}
	}
	return VS_PTA_CT_CHALLENGE_EXPIRED;
}

/*
 * Print the entries in the table using log functions specified in gCfg
 */
void Pta_CT_PrintTable(PTA_CHALLENGE_TABLE *ptaChallengeTable) {
	int i;
	unsigned char * position;
	PTATIME expireTime;
	VSVAL_UserCtx ctx = {0};
	char * hascData;
	for (i =0; i<ptaChallengeTable->m_TableSize; i++) {
		position = ptaChallengeTable->m_ChallengePool + i * ptaChallengeTable->m_EntryLen;
		if(*position == 0) {
                        /* don't print empty entry */
			/* gCfg.InfoLog(0,"[%d]\n",i);*/
		} else {
			hascData=(char*)sscT_malloc(ptaChallengeTable->m_KeyLen*2 + 1);
			if (hascData != NULL) {
				VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx, (unsigned char*)position+1, ptaChallengeTable->m_KeyLen, hascData);
				memcpy(&expireTime,position+1+ptaChallengeTable->m_KeyLen,ptaChallengeTable->m_ValueLen);
				gCfg.InfoLog(0,"[%d] %d :%d : %s\n",i,*position,expireTime,hascData);
				sscT_free((unsigned char *)hascData);
			}
		}
	}
	return;
}


char * Pta_CT_ErrorString (int status) 
{
  char *status_string = 0;

  switch (status) {

  case VS_PTA_CT_WRONG_VALUE_LENGTH:
    status_string = "Wrong Value Length.";
    break;

  case VS_PTA_CT_WRONG_KEY_SIZE:
    status_string = "Wrong Key Size.";
    break;

  case VS_PTA_CT_CHALLENGE_VALID:
    status_string = "The Challenge is Valid.";
    break;

  case VS_PTA_CT_CHALLENGE_EXPIRED:
    status_string = "Challenge is not found. Incorrect server-name configured or Challenge has expired.";
    break;

  case VS_PTA_CT_CHALLENGE_UNFOUND:
    status_string = "Challenge does not exist.";
    break;

  case VS_PTA_CT_EXCEEDED_SIZE:
    status_string = "Challenge size exceeded limit.";
    break;

  case VS_PTA_CT_INIT_ERROR:
    status_string = "Error in initializing Challenge table.";
    break;

  case VS_PTA_TOKEN_EXCEEDED_LIMIT_TRIES:
    status_string = "The token has already been used for authentication in a previous session.";
    break;
  case VS_PTA_TOKEN_EXPIRED:
    status_string = "The token used for authentication has been expired.";
    break;
  case VS_PTA_TOKEN_ERROR_SEARCH_CACHE_TABLE:
    status_string = "an error occured during search the cache table.";
    break;
  case VS_PTA_TOKEN_SIGNATURE_NO_MATCH:
    status_string = "The signature does not match";
    break;
  default:
    status_string = "Challenge Table: Unknown error.";
    break;
  }

  return status_string;
}

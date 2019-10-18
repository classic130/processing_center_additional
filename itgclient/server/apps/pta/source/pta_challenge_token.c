#include "pta_challenge_token.h"
#include <string.h>

/* Following are RC4 encryption utilities */
/* a RC4 expanded key session */
struct rc4_key {
    unsigned char state[256];
    unsigned x, y;
};

/* expand a key (makes a rc4_key) */
void prepare_key(unsigned char *keydata, unsigned len, struct rc4_key *key)
{
    unsigned index1, index2, counter;
    unsigned char *state;

    state = key->state;

    for (counter = 0; counter < 256; counter++)
        state[counter] = counter;

    key->x = key->y = index1 = index2 = 0;

    for (counter = 0; counter < 256; counter++) {
        index2 = (keydata[index1] + state[counter] + index2) & 255;

        /* swap */
        state[counter] ^= state[index2];
        state[index2]  ^= state[counter];
        state[counter] ^= state[index2];

        index1 = (index1 + 1) % len;
    }
}

/* reversible encryption, will encode a buffer updating the key */
void rc4(unsigned char *buffer, unsigned len, struct rc4_key *key)
{
    unsigned x, y, xorIndex, counter;
    unsigned char *state;

    /* get local copies */
    x = key->x; y = key->y;
    state = key->state;

    for (counter = 0; counter < len; counter++) {
        x = (x + 1) & 255;
        y = (state[x] + y) & 255;

        /* swap */
        state[x] ^= state[y];
        state[y] ^= state[x];
        state[x] ^= state[y];

        xorIndex = (state[y] + state[x]) & 255;

        buffer[counter] ^= state[xorIndex];
    }

    key->x = x; key->y = y;
}
/* encrypt an item */
int encryptTokenRC4( const char *pswd, ITEM *token) {
  struct rc4_key key;
  prepare_key((unsigned char*) pswd,strlen(pswd), &key);
  rc4(token->data,token->len,&key);
  return VS_PTA_CT_OK;
}

/* decrypt an item */
int decryptTokenRC4( const char *pswd, ITEM *token) {
  struct rc4_key key;
  prepare_key((unsigned char *) pswd,strlen(pswd), &key);
  rc4(token->data,token->len,&key);
  return VS_PTA_CT_OK;
}

/* VS_PTA_TOKEN_encode
 * encode the toekn with a password
 * returns VS_PTA_CT_OK for successful operations
 * const char *pswd: password used to encrypt the token
 * ITEM *encodedToken: pointer to the encoded token, normally this should be  
 *                     The caller is responsible for allocate and freeing encodedToken->data.
 * PTA_CHALLENGE_TOKEN *token: pointer to the PTA_CHALLENGE_TOKEN to be encoded 
 */
 int VS_PTA_TOKEN_encode(const char *pswd, ITEM *encodedToken, PTA_CHALLENGE_TOKEN *token) {
   int sizeOfEncodedToken = token->randomChallenge->len + sizeof(PTATIME);
   encodedToken->len = sizeOfEncodedToken;
   /* encode the token as randomchallenge+expirationTime */
   memcpy(encodedToken->data,token->randomChallenge->data,token->randomChallenge->len);
   memcpy(encodedToken->data+token->randomChallenge->len,&token->expirationTime, sizeof(PTATIME));
   /* encrypt the data with password (RC4) */
   encryptTokenRC4( pswd,encodedToken); 
   return VS_PTA_CT_OK;
 }

/* VS_PTA_TOKEN_decode
 * decode the toekn with a password
 * const char *pswd: password used to decrypt the token 
 * ITEM *encodedToken: pointer to a encoded token
 * PTA_CHALLENGE_TOKEN *token: pointer to decoded token. Normally this
 *                             should be initialized like PTA_CHALLENGE_TOKEN token = {0}; 
                               the caller is responsible for allocating and freeing token.randomChallenge.data
 * returns VS_PTA_CT_OK for successful operations
 */
 int VS_PTA_TOKEN_decode(const char * pswd, ITEM *encodedToken, PTA_CHALLENGE_TOKEN *token) {
   /*decrypt the item first*/
   decryptTokenRC4( pswd,encodedToken);
   /* encode the token */
   token->randomChallenge->len = encodedToken->len - sizeof(PTATIME);
   memcpy( token->randomChallenge->data,encodedToken->data,token->randomChallenge->len);
   memcpy(&token->expirationTime,encodedToken->data+token->randomChallenge->len,sizeof(PTATIME));

   return VS_PTA_CT_OK;
 }

/* VS_PTA_TOKEN_validate
 * This function does the following
 * 1. validate the time stamp
 * 2. check if this token has aready been used
 * 3. add this token to cached token table
 *
 * PTA_CHALLENGE_TOKEN *token: input, the token to be validated
 * PTA_CHALLENGE_TABLE *cachedTokenTable: pointer to the cached token table
 * int maxNumberOfChecks: input, by design, we should not reject any token
 *                        that is already in the cached table, but sometimes, 
 *                        an authentication server (such as siteminder 
 *                        policy server validate the token more than once, this number defines the maximum
 *                        number you can validate the token. This should be defined in configuration file. 
 *
 */
 int VS_PTA_TOKEN_validate(PTA_CHALLENGE_TOKEN *token, PTA_CHALLENGE_TABLE *cachedTokenTable, int maxNumberOfChecks) {
   /* first check if the token timed out */
   PTATIME currentTime;
   int index, rc, numberOfAccess;
   unsigned char * position;

   /* check token time */
   pta_time(&currentTime);
   if(token->expirationTime < currentTime)
       return VS_PTA_TOKEN_EXPIRED; /* token timed out */

   /* check if this token is already in the cache table */
   rc = Pta_CT_Search( cachedTokenTable, *(token->randomChallenge), &index); 
   /* if no entry found, add the entry and returns ok */
   if(rc == VS_PTA_CT_CHALLENGE_UNFOUND) {
      Pta_CT_Insert( cachedTokenTable,*(token->randomChallenge), &token->expirationTime);
      return VS_PTA_TOKEN_VALID;
   } else if(rc == VS_PTA_CT_OK) {
   /*  entry found, see if it is allowed */
       position = cachedTokenTable->m_ChallengePool+ index *  cachedTokenTable->m_EntryLen; 
       if(*position >= maxNumberOfChecks) {
           /* increment the number of tries */
           *position = *position +1;
           /* return error */
           return VS_PTA_TOKEN_EXCEEDED_LIMIT_TRIES;
       } 
       /* increment the number of tries */
       *position = *position +1;
       return VS_PTA_TOKEN_VALID;
   } 
   /* if the code reaches here, something has gone wrong*/
   return VS_PTA_TOKEN_ERROR_SEARCH_CACHE_TABLE;
 }




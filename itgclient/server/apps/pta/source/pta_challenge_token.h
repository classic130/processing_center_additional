/**
 *	PTA_CHALLENGE_TOKEN
 *	This token is used for pta server authentication purpose
 *      it contains an expiration time and random byte array.
 *      the token is encrypted(encoded) when sent out to client to sign.
 *	Bin Zou 2/11/03
 */
#ifndef _VS_PTA_CHALLENGE_TOEKN_
#define _VS_PTA_CHALLENGE_TOKEN_ 1

#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

#include "pta_challenge_table.h"

/* definition of PTA_CHALLENGE_TOKEN */
typedef struct {
  ITEM *randomChallenge;
  PTATIME expirationTime;
} PTA_CHALLENGE_TOKEN;


/* functions */
/* VS_PTA_TOKEN_encode
 * encode the toekn with a password
 * returns VS_PTA_CT_OK for successful operations
 * const char *pswd: password used to encrypt the token
 * ITEM *encodedToken: pointer to the encoded token, normally this should be
 *                     initialized as ITEM encodedToken = {0} by caller. The caller
 *                     is responsible for allocateing and freeing encodedToken->data.
 * PTA_CHALLENGE_TOKEN *token: pointer to the PTA_CHALLENGE_TOKEN to be encoded
 */
 int VS_PTA_TOKEN_encode(const char *pswd, ITEM *encodedToken, PTA_CHALLENGE_TOKEN *token);

/* VS_PTA_TOKEN_decode
 * decode the toekn with a password
 * const char *pswd: password used to decrypt the token
 * ITEM *encodedToken: pointer to a encoded token
 * PTA_CHALLENGE_TOKEN *token: pointer to decoded token. Normally this
 *                             should be initialized like PTA_CHALLENGE_TOKEN token = {0};
 *                             caller should allocate and free token.randomChallenge.data
 * returns VS_PTA_CT_OK for successful operations
 */
 int VS_PTA_TOKEN_decode(const char * pswd, ITEM *encodedToken, PTA_CHALLENGE_TOKEN *token);

/* VS_PTA_TOKEN_validate
 * This function does the following
 * 1. validate the time stamp
 * 2. check if this token has aready been used
 * 3. add this token to cached token table
 *
 * PTA_CHALLENGE_TOKEN *token: input, the token to be validated
 * PTA_CHALLENGE_TABLE *cachedTokenTable: pointer to the cached token table
 * int maxNumberOfChecks: input, by design, we should not reject any token
 *                        that is already in the cache table, but sometimes, 
 *                        an authentication server (such as siteminder
 *                        policy server validate the token more than once, this number defines the maximum 
 *                        number you can validate the token. This should be defined in configuration file.
 *                        default is 4;
 *
 */
 int VS_PTA_TOKEN_validate(PTA_CHALLENGE_TOKEN *token, PTA_CHALLENGE_TABLE *cachedTokenTable, int maxNumberOfChecks);
#ifdef __cplusplus
}
#endif

#endif

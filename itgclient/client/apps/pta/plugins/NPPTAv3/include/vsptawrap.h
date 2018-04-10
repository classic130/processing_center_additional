#include "ptav3.h"

EXTERN_C IVSPTA* PTA_CreateInstance();

EXTERN_C unsigned int PTA_Initialize (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, int intVal);
EXTERN_C unsigned int PTA_Close (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_AppPreference (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, wchar_t* pwstrNameB, int nLenB);
EXTERN_C wchar_t* PTA_get_AppPreference (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);

EXTERN_C unsigned int PTA_set_CSPName (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* PTA_get_CSPName (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_InstallCert (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C unsigned int PTA_InstallKeyPair (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, wchar_t* pkcs7, int pkcs7len);

EXTERN_C unsigned int PTA_SelectIDForTrans (IVSPTA *pPTA);
EXTERN_C unsigned int PTA_SelectIDForChallenge (IVSPTA *pPTA);

EXTERN_C wchar_t* PTA_SignTransaction (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, short nHashAlg);
EXTERN_C wchar_t* PTA_SignChallenge (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, short nHashAlg);
EXTERN_C wchar_t* PTA_SignRenewal (IVSPTA *pPTA, short nHashAlg);

EXTERN_C wchar_t* PTA_CreateCertReq (IVSPTA *pPTA,wchar_t* subjectDN, int subjectDNLen, 
				                     int KeyAttributes, int HashAlg, wchar_t** attributes, int *nLenArray, int noOfEntries);

EXTERN_C unsigned int PTA_set_ProtocolName (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* PTA_get_ProtocolName (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_UserDefCertFlag (IVSPTA *pPTA,short shortFlag);
EXTERN_C short PTA_get_UserDefCertFlag (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_AuthDll (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* PTA_get_AuthDll (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_ProfileIssFrndlyName (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* PTA_get_ProfileIssFrndlyName (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_ProfileIssUniqueId (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* PTA_get_ProfileIssUniqueId (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_AffLogoUrl (IVSPTA *pPTA, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* PTA_get_AffLogoUrl (IVSPTA *pPTA);

EXTERN_C unsigned int PTA_set_EnableCertForCapi(IVSPTA *pPTA, BOOL boolEnableForCapi);
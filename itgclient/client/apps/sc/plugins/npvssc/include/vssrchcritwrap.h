#include "srchcrit.h"
#include "ptav3.h"

EXTERN_C IVSSrchCrit* SrchCrit_GetInstance(IVSPTA* pPTA);

EXTERN_C unsigned int SrchCrit_set_IssuerDN (IVSSrchCrit *pSrchCrit, wchar_t* pwstIssuerDN, int nLen);
EXTERN_C wchar_t* SrchCrit_get_IssuerDN (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_SubjectDN (IVSSrchCrit *pSrchCrit, wchar_t* pwstSubjectDN, int nLen);
EXTERN_C wchar_t* SrchCrit_get_SubjectDN (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_SerNum(IVSSrchCrit *pSrchCrit, wchar_t* pwstSerNum, int nLen);
EXTERN_C wchar_t* SrchCrit_get_SerNum (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_Email (IVSSrchCrit *pSrchCrit, wchar_t* pwstEmail, int nLen);
EXTERN_C wchar_t* SrchCrit_get_Email (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_ExtOID (IVSSrchCrit *pSrchCrit, wchar_t* pwstExtOID, int nLen);
EXTERN_C wchar_t* SrchCrit_get_ExtOID (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_ExtVal(IVSSrchCrit *pSrchCrit, wchar_t* pwstExtVal, int nLen);
EXTERN_C wchar_t* SrchCrit_get_ExtVal (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_EffDate (IVSSrchCrit *pSrchCrit, DATE effDate);
EXTERN_C DATE SrchCrit_get_EffDate (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_ExpDate(IVSSrchCrit *pSrchCrit, DATE expDate);
EXTERN_C DATE SrchCrit_get_ExpDate (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_DateEquality(IVSSrchCrit *pSrchCrit, short dateEquality);
EXTERN_C short SrchCrit_get_DateEquality (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_Renewed(IVSSrchCrit *pSrchCrit, BOOL boolRenewed);
EXTERN_C BOOL SrchCrit_get_Renewed (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_KeySize(IVSSrchCrit *pSrchCrit, short keySize);
EXTERN_C short SrchCrit_get_KeySize (IVSSrchCrit *pSrchCrit);

EXTERN_C unsigned int SrchCrit_set_KeyUsage(IVSSrchCrit *pSrchCrit, short keyUsage);
EXTERN_C short SrchCrit_get_KeyUsage (IVSSrchCrit *pSrchCrit);


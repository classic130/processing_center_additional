#define _WIN32_WINNT 0x0400
#include "XEnroll.h"
#include <stddef.h>

EXTERN_C ICEnroll* Enroll_CreateInstance();
EXTERN_C unsigned int Enroll_set_ProviderType(ICEnroll* pEnroll, DWORD dwProviderType);
EXTERN_C DWORD Enroll_get_ProviderType(ICEnroll* pEnroll);
EXTERN_C unsigned int Enroll_set_GenKeyFlags(ICEnroll* pEnroll, DWORD dwGenKeyFlags);
EXTERN_C DWORD Enroll_get_GenKeyFlags(ICEnroll* pEnroll);
EXTERN_C unsigned int Enroll_set_ProviderName(ICEnroll* pEnroll, wchar_t* pwstrProviderName, int nLen);
EXTERN_C wchar_t* Enroll_get_ProviderName(ICEnroll* pEnroll);
EXTERN_C unsigned int Enroll_set_HashAlgorithm(ICEnroll* pEnroll, wchar_t* pwstrHashAlgorithm, int nLen);
EXTERN_C wchar_t* Enroll_get_HashAlgorithm(ICEnroll* pEnroll);
EXTERN_C unsigned int Enroll_set_KeySpec(ICEnroll* pEnroll, DWORD dwKeySpec);
EXTERN_C DWORD Enroll_get_KeySpec(ICEnroll* pEnroll);
EXTERN_C unsigned int Enroll_set_DeleteRequestCert(ICEnroll* pEnroll, BOOL boolDeleteCertRequest);
EXTERN_C DWORD Enroll_get_DeleteRequestCert(ICEnroll* pEnroll);
EXTERN_C unsigned int Enroll_set_WriteCertToCSP(ICEnroll* pEnroll, BOOL boolWriteCertToCSP);
EXTERN_C DWORD Enroll_get_WriteCertToCSP(ICEnroll* pEnroll);
EXTERN_C wchar_t* Enroll_enumProvider(ICEnroll* pEnroll, DWORD dwIndex, DWORD dwFlags);
EXTERN_C wchar_t* Enroll_createPKCS10(ICEnroll* pEnroll, wchar_t* pwstrDN, int nDNLen, wchar_t* pwstrUsage, int nUsageLen);
EXTERN_C unsigned int Enroll_acceptPKCS7(ICEnroll* pEnroll, wchar_t* pwstrPKCS7, int nLen);
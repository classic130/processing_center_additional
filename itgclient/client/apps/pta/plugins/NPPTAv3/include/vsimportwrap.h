#include "VSImport.h"

EXTERN_C IImpPKCS12* Import_CreateInstance();
EXTERN_C unsigned int Import_Import(IImpPKCS12* pImport, wchar_t* pwstrPKCS12, int nPKCS12Len, wchar_t* pwstrPKCS7, int nPKCS7Len, wchar_t** ppwstrErrString);
EXTERN_C unsigned int Import_set_KeyExportable(IImpPKCS12* pImport, long lKeyExp);
EXTERN_C long Import_get_KeyExportable(IImpPKCS12* pImport);
EXTERN_C unsigned int Import_set_ProviderName (IImpPKCS12* pImport, wchar_t* pwstProviderName, int nLen);
EXTERN_C wchar_t* Import_get_ProviderName (IImpPKCS12* pImport);

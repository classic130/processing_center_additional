#include "vssc.h"

EXTERN_C IVSSignerInfo* SignerInfo_GetInstance(IVSSC *pVSSC);

EXTERN_C wchar_t* get_SignerInfo_SubjectCN(IVSSignerInfo *pVSSignerInfo);

EXTERN_C wchar_t* get_SignerInfo_SubjectDN(IVSSignerInfo *pVSSignerInfo);

EXTERN_C wchar_t* get_SignerInfo_IssuerDN(IVSSignerInfo *pVSSignerInfo);

EXTERN_C wchar_t* get_SignerInfo_SubjectSerialNumber(IVSSignerInfo *pVSSignerInfo);

EXTERN_C DATE get_SignerInfo_SubjectValidFrom(IVSSignerInfo *pVSSignerInfo);

EXTERN_C DATE get_SignerInfo_SubjectValidTo(IVSSignerInfo *pVSSignerInfo);

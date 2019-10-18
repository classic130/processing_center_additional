#ifndef _VS_PTA_VSCAPI_
#define _VS_PTA_VSCAPI_
#include "..\Include\certstructs.h"

BOOL WINAPI VS_CertFreeCertificateContext(PCCERT_CONTEXT pCertContext);
PCCERT_CONTEXT WINAPI VS_CertDuplicateCertificateContext(IN PCCERT_CONTEXT i_pCertContext);
#endif



#include "vssc.h"
//#include "ResolveRcpt.h"

/*********************** ResolveRcpt Properties ********************/

EXTERN_C IResolveRcpt* ResolveRcpt_GetInstance(IVSSC *pVSSC);

EXTERN_C wchar_t* get_ResolveRcpt_EmailAddress(IResolveRcpt *pResolveRcpt);
EXTERN_C short get_ResolveRcpt_Recipient_Count(IResolveRcpt *pResolveRcpt);

EXTERN_C unsigned int get_ResolveRcpt_Status(IResolveRcpt *pResolveRcpt);
EXTERN_C wchar_t* get_ResolveRcpt_IssuerDN(IResolveRcpt *pResolveRcpt);
EXTERN_C wchar_t* get_ResolveRcpt_SerialNumber(IResolveRcpt *pResolveRcpt);

EXTERN_C int get_ResolveRcpt_RevocationStatus(IResolveRcpt *pResolveRcpt);
EXTERN_C int get_ResolveRcpt_ChainValidationStatus(IResolveRcpt *pResolveRcpt);
EXTERN_C BOOL get_ResolveRcpt_IsCertExpired(IResolveRcpt *pResolveRcpt);

/*********************** ResolveRcpt Methods ********************/
EXTERN_C unsigned int ResolveRcpt_First(IResolveRcpt *pResolveRcpt);
EXTERN_C unsigned int ResolveRcpt_Next(IResolveRcpt *pResolveRcpt);
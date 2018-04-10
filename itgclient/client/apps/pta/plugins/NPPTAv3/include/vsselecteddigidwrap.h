#include "seldigid.h"
#include "ptav3.h"

EXTERN_C IVSSelectedDigID* SelectedDigID_GetInstance(IVSPTA* pPTA);

EXTERN_C wchar_t* SelectedDigID_get_IssuerDN (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_SubjectDN (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_SerNum (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_FrndlyName (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_LogoUrl (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_TextureUrl (IVSSelectedDigID *pSelectedDigID);

EXTERN_C DATE SelectedDigID_get_ExpDate (IVSSelectedDigID *pSelectedDigID);

EXTERN_C DATE SelectedDigID_get_EffDate (IVSSelectedDigID *pSelectedDigID);

EXTERN_C BOOL SelectedDigID_get_Renewed (IVSSelectedDigID *pSelectedDigID);

EXTERN_C short SelectedDigID_get_KeyUsage (IVSSelectedDigID *pSelectedDigID);

EXTERN_C short SelectedDigID_get_KeySize (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_PubKeySHA1 (IVSSelectedDigID *pSelectedDigID);

EXTERN_C wchar_t* SelectedDigID_get_PubKeyMD5 (IVSSelectedDigID *pSelectedDigID);

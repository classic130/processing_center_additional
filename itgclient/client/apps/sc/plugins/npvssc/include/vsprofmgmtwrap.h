#include "profmgmt.h"
#include "ptav3.h"

EXTERN_C IVSProfMgmt* ProfMgmt_GetInstance(IVSPTA* pPTA);

EXTERN_C unsigned int ProfMgmt_set_PasswdQuality (IVSProfMgmt *pProfMgmt, int nParam);
EXTERN_C int ProfMgmt_get_PasswdQuality (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_PasswdLength (IVSProfMgmt *pProfMgmt, int nParam);
EXTERN_C int ProfMgmt_get_PasswdLength (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_PasswdTimeOut (IVSProfMgmt *pProfMgmt, int nParam);
EXTERN_C int ProfMgmt_get_PasswdTimeOut (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_PasswdLockOutTries (IVSProfMgmt *pProfMgmt, int nParam);
EXTERN_C int ProfMgmt_get_PasswdLockOutTries (IVSProfMgmt *pProfMgmt);


EXTERN_C unsigned int ProfMgmt_set_PasswdUnLockPeriod (IVSProfMgmt *pProfMgmt, int nParam);
EXTERN_C int ProfMgmt_get_PasswdUnLockPeriod (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_OpenProfFlags (IVSProfMgmt *pProfMgmt, int nParam);
EXTERN_C int ProfMgmt_get_OpenProfFlags (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_ProfileName (IVSProfMgmt *pProfMgmt, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* ProfMgmt_get_ProfileName (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_Password (IVSProfMgmt *pProfMgmt, wchar_t* pwstrName, int nLen);


EXTERN_C unsigned int ProfMgmt_set_RoamProfile (IVSProfMgmt *pProfMgmt, BOOL boolParam);
EXTERN_C BOOL ProfMgmt_get_RoamProfile (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_SaveLocal (IVSProfMgmt *pProfMgmt, BOOL boolParam);
EXTERN_C BOOL ProfMgmt_get_SaveLocal (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_OpenProfile (IVSProfMgmt *pProfMgmt);
EXTERN_C unsigned int ProfMgmt_CloseProfile (IVSProfMgmt *pProfMgmt);
EXTERN_C unsigned int ProfMgmt_SaveProfile (IVSProfMgmt *pProfMgmt);
EXTERN_C unsigned int ProfMgmt_ChangePassword (IVSProfMgmt *pProfMgmt);

EXTERN_C unsigned int ProfMgmt_set_IsUsernameEditable(IVSProfMgmt *pProfMgmt, BOOL boolParam);
EXTERN_C int ProfMgmt_get_IsUsernameEditable(IVSProfMgmt *pProfMgmt);
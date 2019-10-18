#include "vsdnotz.h"

EXTERN_C IVSNZ* NZ_CreateInstance();
EXTERN_C IVSNZUIPrefs* NZ_UIPrefs_GetInstance(IVSNZ* pVSNZ);
EXTERN_C IVSNZAppPrefs* NZ_AppPrefs_GetInstance(IVSNZ* pVSNZ);
EXTERN_C IVSPTA* NZ_CreatePTAInstance(IVSNZ* pVSNZ);

// The primary digital notarization interface implementations
EXTERN_C unsigned int NZ_Initialize(IVSNZ *pVSNZ);
EXTERN_C unsigned int NZ_Close(IVSNZ *pVSNZ);
EXTERN_C unsigned int NZ_set_NotarizationServer(IVSNZ *pVSNZ, wchar_t* pwstrServerName, int nServerName);
EXTERN_C unsigned int NZ_set_HashAlg(IVSNZ *pVSNZ, wchar_t* pwstrHashAlg, int nHashAlg);
EXTERN_C unsigned int NZ_set_DisplayDigitalID(IVSNZ *pVSNZ, int DisplayID);
EXTERN_C unsigned int NZ_set_CRLLocation(IVSNZ *pVSNZ, wchar_t* pwstrCrl, int nCrl);
EXTERN_C unsigned int NZ_set_ValidationPref(IVSNZ *pVSNZ, int ValPref);
EXTERN_C unsigned int NZ_set_NotarizationDescription(IVSNZ *pVSNZ, wchar_t* pwstrDescription, int nDescription);
EXTERN_C wchar_t* NZ_NotarizeDocument(IVSNZ *pVSNZ, wchar_t* pwstrDocName, int nDocName, int uiMask, int ResponseType);
EXTERN_C wchar_t* NZ_NotarizeHash(IVSNZ *pVSNZ, wchar_t* pwstrHash, int nHash, int uiMask);
EXTERN_C unsigned int NZ_VerifyNotarizationRecord(IVSNZ *pVSNZ, wchar_t* pwstrRecord, int nRecord, wchar_t* pwstrDocument, int nDocument, int RecordType, int UIMask);
EXTERN_C unsigned int NZ_AddCertificate(IVSNZ *pVSNZ, wchar_t* pwstrCertificate, int nCertificate);


// The ui preferences interface implementations
EXTERN_C unsigned int NZ_set_UIPrefs_LogoUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrLogoUrl, int nLogoUrl);
EXTERN_C unsigned int NZ_set_UIPrefs_SelFileTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrSelFileTitle, int nSelFileTitle);
EXTERN_C unsigned int NZ_set_UIPrefs_SelFileDesc(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrSelFileDesc, int nSelFileDesc);
EXTERN_C unsigned int NZ_set_UIPrefs_SelFileHelpUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrSelFileHelpUrl, int nSelFileHelpUrl);
EXTERN_C unsigned int NZ_set_UIPrefs_ProgressTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrProgressTitle, int nProgressTitle);
EXTERN_C unsigned int NZ_set_UIPrefs_ProgressDesc(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrProgressDesc, int nProgressDesc);
EXTERN_C unsigned int NZ_set_UIPrefs_ProgressHelpUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrProgressHelpUrl, int nProgressHelpUrl);
EXTERN_C unsigned int NZ_set_UIPrefs_ReceiptTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrReceiptTitle, int nReceiptTitle);
EXTERN_C unsigned int NZ_set_UIPrefs_ReceiptDesc(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrReceiptDesc, int nReceiptDesc);
EXTERN_C unsigned int NZ_set_UIPrefs_ReceiptHelpUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrReceiptHelpUrl, int nReceiptHelpUrl);
EXTERN_C unsigned int NZ_set_UIPrefs_WizardTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrWizardTitle, int nWizardTitle);


// The app preferences interface implementations
EXTERN_C unsigned int NZ_set_ApplicationPref(IVSNZAppPrefs* pNZAppPref, wchar_t* pwstrAppName, int nAppName, wchar_t* pwstrPrefName,
											 int nPrefName, int PrefType, wchar_t* pwstrPrefValue, int nPrefValue);
EXTERN_C wchar_t* NZ_get_ApplicationPref(IVSNZAppPrefs* pNZAppPref, wchar_t* pwstrAppName, int nAppName, wchar_t* pwstrPrefName, int nPrefName);

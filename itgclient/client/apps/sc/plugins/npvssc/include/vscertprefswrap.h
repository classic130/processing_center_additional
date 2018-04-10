#include "certprefs.h"
#include "ptav3.h"

EXTERN_C IVSCertPrefs* CertPrefs_GetInstance(IVSPTA* pPTA);

EXTERN_C unsigned int CertPrefs_set_CertSerNum (IVSCertPrefs *pCertPrefs, wchar_t* pwstCertSerNum, int nLen);
EXTERN_C wchar_t* CertPrefs_get_CertSerNum (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_CertIssDN (IVSCertPrefs *pCertPrefs, wchar_t* pwstCertIssDN, int nLen);
EXTERN_C wchar_t* CertPrefs_get_CertIssDN (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_CertFrndlyName (IVSCertPrefs *pCertPrefs, wchar_t* pwstCertFrndlyName, int nLen);
EXTERN_C wchar_t* CertPrefs_get_CertFrndlyName (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_CertLogoUrl (IVSCertPrefs *pCertPrefs, wchar_t* pwstCertLogoUrl, int nLen);
EXTERN_C wchar_t* CertPrefs_get_CertLogoUrl (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_CertDispString (IVSCertPrefs *pCertPrefs, wchar_t* pwstCertDispString, int nLen);
EXTERN_C wchar_t* CertPrefs_get_CertDispString (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_CertTextureUrl(IVSCertPrefs *pCertPrefs, wchar_t* pwstCertTextureUrl, int nLen);
EXTERN_C wchar_t* CertPrefs_get_CertTextureUrl (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_MarkAsRenewed (IVSCertPrefs *pCertPrefs, BOOL markAsRenewed);
EXTERN_C BOOL CertPrefs_get_MarkAsRenewed (IVSCertPrefs *pCertPrefs);

EXTERN_C unsigned int CertPrefs_set_CertPreference(IVSCertPrefs *pCertPrefs, wchar_t* pwstCertPref, int nLen, wchar_t* pwstVal, int nValLen);
EXTERN_C wchar_t* CertPrefs_get_CertPreference (IVSCertPrefs *pCertPrefs, wchar_t* pwstCertPref, int nLen);
#include "uiprefs.h"
#include "ptav3.h"

EXTERN_C IVSUIPrefs* UIPrefs_GetInstance(IVSPTA* pPTA);

EXTERN_C unsigned int UIPrefs_set_UILogoUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstUILogoUrl, int nLen);
EXTERN_C wchar_t* UIPrefs_get_UILogoUrl (IVSUIPrefs *pUIPrefs);


EXTERN_C unsigned int UIPrefs_set_NewPasswd_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_NewPasswd_Title (IVSUIPrefs *pUIPrefs);


EXTERN_C unsigned int UIPrefs_set_NewPasswd_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_NewPasswd_Text (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_NewPasswd_OKBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_NewPasswd_OKBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_NewPasswd_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_NewPasswd_CancelBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_NewPasswd_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_NewPasswd_HelpUrl (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_RvwMsg_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_RvwMsg_Text (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_RvwMsg_OKBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_RvwMsg_OKBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_RvwMsg_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_RvwMsg_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_RvwMsg_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_RvwMsg_CancelBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_RvwMsg_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_RvwMsg_HelpUrl (IVSUIPrefs *pUIPrefs);


EXTERN_C unsigned int UIPrefs_set_SgnDlg_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_SgnDlg_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_SelID_HelpUrl (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_SelID_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_SelID_Text (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_OKBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_SelID_OKBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_SelID_CancelBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_ChkBoxText(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_SelID_ChkBoxText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_SelID_ShowDefChkBox(IVSUIPrefs *pUIPrefs, BOOL boolShowDef);
EXTERN_C BOOL UIPrefs_get_SelID_ShowDefChkBox (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_LgnDlg_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_LgnDlg_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_OpenProf_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_OpenProf_HelpUrl (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_OpenProf_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_OpenProf_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_OpenProf_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_OpenProf_Text (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_OpenProf_OKBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_OpenProf_OKBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_OpenProf_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_OpenProf_CancelBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_TitleFont(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_TitleFont (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_TextFont (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_TextFont (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_BtnFont (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_BtnFont (IVSUIPrefs *pUIPrefs);


EXTERN_C unsigned int UIPrefs_set_Language (IVSUIPrefs *pUIPrefs, int nLanguage);
EXTERN_C int UIPrefs_get_Language (IVSUIPrefs *pUIPrefs);


EXTERN_C unsigned int UIPrefs_set_IntroDlg_Title (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_IntroDlg_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_IntroDlg_Text (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_IntroDlg_Text (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_IntroDlg_HelpUrl (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_IntroDlg_HelpUrl (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_CreateNewProf_Title (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_CreateNewProf_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_ChangePasswd_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_ChangePasswd_HelpUrl (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_ChangePasswd_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_ChangePasswd_Title (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_ChangePasswd_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_ChangePasswd_Text (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_ChangePasswd_OKBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_ChangePasswd_OKBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_ChangePasswd_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText);
EXTERN_C int UIPrefs_get_ChangePasswd_CancelBtnText (IVSUIPrefs *pUIPrefs);

EXTERN_C unsigned int UIPrefs_set_Timeout_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen);
EXTERN_C wchar_t* UIPrefs_get_Timeout_HelpUrl (IVSUIPrefs *pUIPrefs);

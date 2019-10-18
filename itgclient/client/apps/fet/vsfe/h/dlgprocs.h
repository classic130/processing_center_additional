#ifndef DLGPROCS_H
#define DLGPROCS_H

#define ID_ANIMATE	2002

BOOL APIENTRY Safe(HWND, UINT, UINT, LONG);
BOOL APIENTRY AdvancedOpts(HWND, UINT, UINT, LONG);
BOOL APIENTRY SafeProperties(HWND, UINT, UINT, LONG);
BOOL APIENTRY FileProperties(HWND, UINT, UINT, LONG);
BOOL APIENTRY FolderProperties(HWND, UINT, UINT, LONG);
BOOL APIENTRY MultipleFileProperties(HWND, UINT, UINT, LONG);
BOOL APIENTRY ReplaceConfirm(HWND, UINT, UINT, LONG);
BOOL APIENTRY EncryptError(HWND, UINT, UINT, LONG);
BOOL APIENTRY DecryptError(HWND, UINT, UINT, LONG);
BOOL APIENTRY SafeSecurity(HWND, UINT, UINT, LONG);
BOOL APIENTRY FilterProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY FilterExtProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY CertMgmt(HWND, UINT, UINT, LONG);
BOOL APIENTRY AnimateDlg(HWND, UINT, UINT, LONG);
BOOL APIENTRY PasswdAcceptProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY SafeUnlockProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY PasswdVerifyProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY RecoverPasswordProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY NewPasswordProc(HWND, UINT, UINT, LONG);

/* PRRemove
BOOL APIENTRY PasswordChangeProc(HWND, UINT, UINT, LONG);
*/
BOOL APIENTRY DlgEncrDecr(HWND, UINT, UINT, LONG);
BOOL APIENTRY DisplayTextProc(HWND, UINT, UINT, LONG);
BOOL APIENTRY ChangeCertProc(HWND, UINT, UINT, LONG);
BOOL CALLBACK EncryptHookProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SelectHookProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ImportHookProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK RemoveContextHelpProc(HWND, UINT, LPARAM);
BOOL AddCspToList(HWND);
BOOL AddAlgorithms(LPCSTR, HWND, BOOL);
void GetCertSubjectDisplayName(PCCERT_CONTEXT, TCHAR *);
BOOL IsAlgSupported(LPCTSTR, BOOL);
void ModifyAlgorithm(LPCSTR, BOOL);
void AddScreenSaver(HWND, LPCTSTR, LPCTSTR);
BOOL GetScrnSvrFile(LPCTSTR, LPCSTR, LPTSTR);

#endif   //DLGPROCS_H
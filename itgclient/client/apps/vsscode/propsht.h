#ifndef __VS_PROPSHT_
#define __VS_PROPSHT_

// Structure to hold time related information
typedef struct tagTimeSettings
{
	BOOL bCurrentTime;
	SYSTEMTIME sysTime;
}TimeSettings, *LPTimeSettings;


VOID DoSignatureProp(LPTimeSettings i_pTimeSettings);
BOOL APIENTRY DlgTimeProc(HWND hDlg, UINT message, UINT wParam, LONG lParam);

#endif // __VS_PROPSHT_
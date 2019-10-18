#include "stdafx.h"
#include <comutil.h>
#include "macros.h"
#include "resource.h"
#include "propsht.h"
#include "util.h"
#include "certmgmt.h"
#include "settings.h"


VOID DoSignatureProp(LPTimeSettings i_pTimeSettings)
{
	PROPSHEETHEADER psh;
	PROPSHEETPAGE psp[1];

	WCHAR *pwcharCaption = NULL;
	_bstr_t tbstrCaption = "";

	// Page
	memset(&psp[0], 0, sizeof(PROPSHEETPAGE));

	psp[0].dwSize = sizeof(PROPSHEETPAGE);
	psp[0].hInstance = AfxGetInstanceHandle();
	psp[0].pszTemplate = MAKEINTRESOURCE(IDD_TIME);
	psp[0].pfnDlgProc = (DLGPROC)DlgTimeProc;
	psp[0].lParam = (LONG)i_pTimeSettings;		// Used in DlgTimeProc


	// Header
	memset(&psh, 0, sizeof(PROPSHEETHEADER));
	
	psh.dwSize = sizeof(PROPSHEETHEADER);
	psh.dwFlags = PSH_PROPSHEETPAGE;
	psh.hInstance = AfxGetInstanceHandle();
	psh.hwndParent = GetFocus();

	if(LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID() , IDS_PROP_CAPTION, &pwcharCaption) == S_OK)
	{
		tbstrCaption = pwcharCaption;
		psh.pszCaption = tbstrCaption;
	}

	psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
	psh.nStartPage = 0;
	psh.ppsp = (LPCPROPSHEETPAGE) &psp;

	PropertySheet(&psh);

	FREE_MEMORY(pwcharCaption)
}


BOOL APIENTRY DlgTimeProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	static LPTimeSettings pTimeSettings;
	
	switch(message)
	{
		case WM_INITDIALOG :
		{
			HWND hTimeSetting = NULL, hDateTime = NULL;
			LPPROPSHEETPAGE pPropSheet = NULL;
			
			// Get the currently held time value from 'lParam'
			pPropSheet = (LPPROPSHEETPAGE)lParam;
			pTimeSettings = (LPTimeSettings)(pPropSheet->lParam);
			
			// Format for the Date-Time control
			hDateTime = GetDlgItem(hDlg, IDC_DATETIME);
			DateTime_SetFormat(hDateTime, "MMM dd',' yyyy hh':'mm':'ss tt");

			DateTime_SetSystemtime(hDateTime, GDT_VALID, &(pTimeSettings->sysTime));

			if(pTimeSettings->bCurrentTime)
			{
				hTimeSetting = GetDlgItem(hDlg, IDC_CURRENT_TIME);
				SendMessage(hTimeSetting, BM_SETCHECK, BST_CHECKED, 0);

				EnableWindow(hDateTime, FALSE);
			}
			else
			{
				hTimeSetting = GetDlgItem(hDlg, IDC_DIFF_TIME);
				SendMessage(hTimeSetting, BM_SETCHECK, BST_CHECKED, 0);
			}

			break;
		}

		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case BN_CLICKED:
				{
					switch(LOWORD(wParam))
					{
						case IDC_CURRENT_TIME:
						{
							if(pTimeSettings->bCurrentTime == FALSE)
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);

							HWND hDateTime = NULL;
							hDateTime = GetDlgItem(hDlg, IDC_DATETIME);
							EnableWindow(hDateTime, FALSE);
							
							break;
						}

						case IDC_DIFF_TIME:
						{
							if(pTimeSettings->bCurrentTime == TRUE)
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							
							HWND hDateTime = NULL;
							hDateTime = GetDlgItem(hDlg, IDC_DATETIME);
							EnableWindow(hDateTime, TRUE);
							
							break;
						}

						case IDOK:
						{
							HWND hCurrTime = NULL;

							// Store the time info in the 'lParam' which points to the mainframe member var
							DateTime_GetSystemtime((HWND)lParam, &(pTimeSettings->sysTime));

							hCurrTime = GetDlgItem(hDlg, IDC_CURRENT_TIME);

							if(SendMessage(hCurrTime, BM_GETCHECK, 0, 0) == BST_CHECKED)
								pTimeSettings->bCurrentTime = TRUE;
							else
								pTimeSettings->bCurrentTime = FALSE;

							EndDialog(hDlg, IDOK);
							return TRUE;
						}
					}

					break;
				}

			}

			break;
		}

		case WM_NOTIFY:
		{
			switch(((LPNMHDR)lParam)->code)
			{
				case DTN_DATETIMECHANGE:
				{
					SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
					break;
				}

				case PSN_APPLY:
				{
					// Store the time info in the 'lParam' which points to the mainframe member var
					HWND hDateTime = NULL, hCurrTime = NULL;

					hDateTime = GetDlgItem(hDlg, IDC_DATETIME);
			
					DateTime_GetSystemtime(hDateTime, &(pTimeSettings->sysTime));

					hCurrTime = GetDlgItem(hDlg, IDC_CURRENT_TIME);

					if(SendMessage(hCurrTime, BM_GETCHECK, 0, 0) == BST_CHECKED)
						pTimeSettings->bCurrentTime = TRUE;
					else
						pTimeSettings->bCurrentTime = FALSE;

					return PSNRET_NOERROR;
				}
			}
			
			break;
		}

	}

	return FALSE;
}
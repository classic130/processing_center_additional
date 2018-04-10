#include "stdafx.h"
#include <shlobj.h>
#include <hlink.h>
#include <regstr.h>
#include "resource.h"
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "ShlFldr.h"
#include "ContMenu.h"
#include "dlgprocs.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "encdeclist.h"
#include "certmgmt.h"

#include <pshpack1.h>
typedef struct DLGTEMPLATEEX
{
    WORD dlgVer;
    WORD signature;
    DWORD helpID;
    DWORD exStyle;
    DWORD style;
    WORD cDlgItems;
    short x;
    short y;
    short cx;
    short cy;
} DLGTEMPLATEEX, *LPDLGTEMPLATEEX;
#include <poppack.h>


#define ID_LISTVIEW_FILTER_ITEMS	2002
#define MY_ENCODING_TYPE		(PKCS_7_ASN_ENCODING | CRYPT_ASN_ENCODING)


extern IVSProfMgmt *g_pProfMgmt;
extern BOOL g_bVeriSignCSP;
extern SelectedCERT currSelCert;
extern TCHAR g_szTokenFile[MAX_PATH_LEN];
extern PolicyVars g_LocalPolicy;
extern SafeSettings g_SafeProp;
extern UINT g_nTimerId;
extern CEncDecList *g_EncrAtLogoffList, *g_DecrAtLogonList;
extern TCHAR g_szWinDir[MAX_PATH_LEN], g_szWinSysDir[MAX_PATH_LEN], g_szDesktopDir[MAX_PATH_LEN];

typedef struct 
{
	TCHAR	szCspName[256];
	UINT	nCspType;
}CSPInfo, *LPCSPInfo;

CSPInfo g_CspInfo[10];
int g_nCSPs = 0;


HashInfo g_PasswdHash;

/* PRRemove
// Dialog procedure for the "Advanced Safe" dialog
BOOL APIENTRY AdvancedOpts(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    static PROPSHEETPAGE * ps;
	static EncryptMethod CurrEncrMethod;
	static PasswordMethod CurrPasswdMethod;
	static BOOL bSecureDel;
	static TCHAR szMinutes[16];	// whether the no of minutes has changed
	static TCHAR szEncryptionAlg[MAX_PATH], szSignatureAlg[MAX_PATH];
	TCHAR szString[MAX_PATH];
    
    switch (message)
    {
        case WM_INITDIALOG:    
		{
			HWND hWnd, hWndBuddy;

            // Save the PROPSHEETPAGE information.
            ps = (PROPSHEETPAGE *)lParam;

			if(g_bVeriSignCSP) 
			{
				// For VeriSign CSP change password not supported
				hWnd = GetDlgItem(hDlg, IDB_PASSWD_CHANGE);
				ShowWindow(hWnd, SW_HIDE);
				
				LoadString(g_hInst, IDS_VS_PASSWD1, szString, sizeof(szString));
				SetDlgItemText(hDlg, IDB_ENCDEC, szString);

				LoadString(g_hInst, IDS_VS_PASSWD2, szString, sizeof(szString));
				SetDlgItemText(hDlg, IDC_STATIC_ENCDEC, szString);

				LoadString(g_hInst, IDS_VS_PASSWD3, szString, sizeof(szString));
				SetDlgItemText(hDlg, IDB_TIMEOUT, szString);

				// Disable prompt everytime option for VSCSP
				hWnd = GetDlgItem(hDlg, IDB_ENCDEC);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_ENCDEC);
				EnableWindow(hWnd, FALSE);
			}
			else
			{
				LoadString(g_hInst, IDS_MS_PASSWD1, szString, sizeof(szString));
				SetDlgItemText(hDlg, IDB_ENCDEC, szString);

				LoadString(g_hInst, IDS_MS_PASSWD2, szString, sizeof(szString));
				SetDlgItemText(hDlg, IDC_STATIC_ENCDEC, szString);

				LoadString(g_hInst, IDS_MS_PASSWD3, szString, sizeof(szString));
				SetDlgItemText(hDlg, IDB_TIMEOUT, szString);

				hWnd = GetDlgItem(hDlg, IDB_ENCDEC);
				EnableWindow(hWnd, TRUE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_ENCDEC);
				EnableWindow(hWnd, TRUE);
			}

			// Assign the buddy to the spin ctrl
			hWnd = GetDlgItem(hDlg, IDC_SPIN);
			hWndBuddy = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
			SendMessage(hWnd, UDM_SETBUDDY, (WPARAM)hWndBuddy, 0);

			// Set the range for the spin ctrl
			SendMessage(hWnd, UDM_SETRANGE, 0,(LPARAM)MAKELONG(30, 1));

			// Set limit text for the buddy
			SendMessage(hWndBuddy, EM_LIMITTEXT, 2, 0);

			CurrEncrMethod	 = g_LocalPolicy.EncryptMethod;
			CurrPasswdMethod = g_LocalPolicy.PasswdMethod;
			bSecureDel		 = g_LocalPolicy.bSecureDelete;

			if(g_LocalPolicy.bPasswdMethodForced)
			{
				hWnd = GetDlgItem(hDlg, IDB_ENCDEC);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDB_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_ENCDEC);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_MINUTES);
				EnableWindow(hWnd, FALSE);
			}

			if(CurrPasswdMethod == ENCDEC)
			{
				hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDB_ENCDEC);
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
			}
			else
			{
				hWnd = GetDlgItem(hDlg, IDB_TIMEOUT);
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

				TCHAR szTimeOut[28];
				itoa(g_LocalPolicy.PasswordPromptTimeout, szTimeOut, 10);
				SetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szTimeOut);
				lstrcpy(szMinutes, szTimeOut);

				if(g_LocalPolicy.bPasswdTimeoutForced)
				{
					hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
					EnableWindow(hWnd, FALSE);
				}
			}

			if(g_LocalPolicy.bEncrMethodForced)
			{
				hWnd = GetDlgItem(hDlg, IDC_BUTTON_MOVE);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_BUTTON_LINK);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_BUTTON_INPLACE);
				EnableWindow(hWnd, FALSE);
			}

			int idButton = IDC_BUTTON_MOVE;
			if(CurrEncrMethod == LINK)
				idButton = IDC_BUTTON_LINK;
			else
				if(CurrEncrMethod == INPLACE)
					idButton = IDC_BUTTON_INPLACE;

			hWnd = GetDlgItem(hDlg, idButton);
			::SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

            return (TRUE);
		}


		case WM_COMMAND:
			switch(HIWORD(wParam))
			{
				case EN_CHANGE:
				{
					TCHAR szCurrMinutes[16];
					GetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szCurrMinutes, 16);
					if(lstrcmpi(szCurrMinutes, szMinutes))
					{
						// Not same
						lstrcpy(szMinutes, szCurrMinutes);
						SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
					}
				}
					break;

				case BN_CLICKED:    
				{
					switch(LOWORD(wParam))
					{
						case IDB_ENCDEC:
							if(CurrPasswdMethod != ENCDEC)
							{	
								HWND hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
								EnableWindow(hWnd, FALSE);

								CurrPasswdMethod = ENCDEC;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDB_TIMEOUT:
							if(CurrPasswdMethod != TIMEOUT)
							{	
								TCHAR szText[28];

								HWND hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
								if(g_LocalPolicy.bPasswdTimeoutForced)
									EnableWindow(hWnd, FALSE);
								else
									EnableWindow(hWnd, TRUE);

								itoa(g_LocalPolicy.PasswordPromptTimeout, szText, 10);
								SetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szText);
								lstrcpy(szMinutes, szText);

								CurrPasswdMethod = TIMEOUT;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDC_BUTTON_MOVE:
							if(CurrEncrMethod != MOVE)
							{
								CurrEncrMethod = MOVE;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDC_BUTTON_LINK:
							if(CurrEncrMethod != LINK)
							{
								CurrEncrMethod = LINK;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDC_BUTTON_INPLACE:
							if(CurrEncrMethod != IDC_BUTTON_INPLACE)
							{
								CurrEncrMethod = INPLACE;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;


						case IDB_SECURITY:
							DialogBox(g_hInst, MAKEINTRESOURCE(IDD_SAFE_SECURITY), 
									  hDlg, (DLGPROC)SafeSecurity);
							break;

						case IDB_PASSWD_CHANGE:
						{
							DialogBox(g_hInst, MAKEINTRESOURCE(IDD_CHANGE_PASSWD), 
									  hDlg, (DLGPROC)PasswordChangeProc);
							break;
						}
						
					}

					return TRUE;
				}
			}

			break;

        case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
                case PSN_APPLY:
				{
					TCHAR szTimeOut[28];
					if(CurrPasswdMethod == TIMEOUT)
						GetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szTimeOut, 28);
					
					if(g_bVeriSignCSP)
					{
						HRESULT hr;
						VARIANT varTimeOut;
						HWND hWnd;

						varTimeOut.vt = VT_I2;

						if(CurrPasswdMethod == ENCDEC)
							varTimeOut.iVal = 0;
						else
							varTimeOut.iVal = atoi(szTimeOut);

						// Apply is called when Apply button is
						// pressed and also when OK button is 
						// pressed. This may cause the passwd prompt
						// to happen. This check is to prevent it.
						if(CurrPasswdMethod != g_LocalPolicy.PasswdMethod || 
						 (CurrPasswdMethod == TIMEOUT && ((UINT)varTimeOut.iVal != g_LocalPolicy.PasswordPromptTimeout)))
						{
							hr = g_pProfMgmt->put_PasswdTimeOut(varTimeOut);
							if(hr != S_OK)
							{
								LogErrorMessage("AdvancedOpts() : g_pProfMgmt->put_PasswdTimeOut() failed", hr);

								if(g_LocalPolicy.PasswdMethod == ENCDEC)
								{
									hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
									EnableWindow(hWnd, FALSE);

									hWnd = GetDlgItem(hDlg, IDB_ENCDEC);
									SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

									hWnd = GetDlgItem(hDlg, IDB_TIMEOUT);
									SendMessage(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
								}
								else
								{
									hWnd = GetDlgItem(hDlg, IDB_TIMEOUT);
									SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

									hWnd = GetDlgItem(hDlg, IDB_ENCDEC);
									SendMessage(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);


									TCHAR szTimeOut[28];
									itoa(g_LocalPolicy.PasswordPromptTimeout, szTimeOut, 10);
									SetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szTimeOut);
								}

								CurrPasswdMethod = g_LocalPolicy.PasswdMethod;
							}
							else
							{
								g_LocalPolicy.PasswdMethod		= CurrPasswdMethod;
								if(CurrPasswdMethod == TIMEOUT)
									g_LocalPolicy.PasswordPromptTimeout = atoi(szTimeOut);
							}
						}

						g_LocalPolicy.EncryptMethod		= CurrEncrMethod;
					}
					else
					{
						g_LocalPolicy.EncryptMethod		= CurrEncrMethod;
						g_LocalPolicy.PasswdMethod		= CurrPasswdMethod;

						if(g_nTimerId)
						{
							KillTimer(NULL, g_nTimerId);
							g_nTimerId = 0;
						}

						if(CurrPasswdMethod == TIMEOUT)
							g_LocalPolicy.PasswordPromptTimeout = atoi(szTimeOut);
					}

					return PSNRET_NOERROR;
				}

                case PSN_KILLACTIVE:
                    SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
                    return TRUE;
                    

				case PSN_HELP:
				{
					ShowHelp("fet_advanced.htm");
					return TRUE;
				}
        }
    }

    return (FALSE);
}*/



// Dialog procedure for the "Advanced Safe" dialog
BOOL APIENTRY AdvancedOpts(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    static EncryptMethod CurrEncrMethod;
	static TCHAR szMinutes[16];	// whether the no of minutes has changed
	TCHAR szTimeOut[16];
	HWND hWnd, hWndBuddy;
    
    switch (message)
    {
        case WM_INITDIALOG:    
		{
    		// Assign the buddy to the spin ctrl
			hWnd = GetDlgItem(hDlg, IDC_SPIN);
			hWndBuddy = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
			SendMessage(hWnd, UDM_SETBUDDY, (WPARAM)hWndBuddy, 0);

			// Set the range for the spin ctrl
			SendMessage(hWnd, UDM_SETRANGE, 0,(LPARAM)MAKELONG(60, 0));

			// Set limit text for the buddy
			SendMessage(hWndBuddy, EM_LIMITTEXT, 2, 0);

			itoa(g_LocalPolicy.PasswordPromptTimeout, szTimeOut, 10);
			lstrcpy(szMinutes, szTimeOut);	

			if(g_bVeriSignCSP)
				SetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szTimeOut);

			if(!g_bVeriSignCSP || g_LocalPolicy.bPasswdMethodForced)
			{
				hWnd = GetDlgItem(hDlg, IDC_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_TIMEOUT);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_STATIC_MINUTES);
				EnableWindow(hWnd, FALSE);
			}

			if(g_LocalPolicy.bEncrMethodForced)
			{
				hWnd = GetDlgItem(hDlg, IDC_BUTTON_MOVE);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_BUTTON_LINK);
				EnableWindow(hWnd, FALSE);

				hWnd = GetDlgItem(hDlg, IDC_BUTTON_INPLACE);
				EnableWindow(hWnd, FALSE);
			}

			int idButton = IDC_BUTTON_MOVE;
			CurrEncrMethod	 = g_LocalPolicy.EncryptMethod;

			if(CurrEncrMethod == LINK)
				idButton = IDC_BUTTON_LINK;
			else
				if(CurrEncrMethod == INPLACE)
					idButton = IDC_BUTTON_INPLACE;

			hWnd = GetDlgItem(hDlg, idButton);
			::SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

            return TRUE;
		}


		case WM_COMMAND:
			switch(HIWORD(wParam))
			{
				case EN_CHANGE:
				{
					TCHAR szCurrMinutes[16];
					GetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szCurrMinutes, 16);
					if(lstrcmpi(szCurrMinutes, szMinutes))
					{
						lstrcpy(szMinutes, szCurrMinutes);
						SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
					}
				}
					break;

				case BN_CLICKED:    
				{
					switch(LOWORD(wParam))
					{
						case IDC_BUTTON_MOVE:
							if(CurrEncrMethod != MOVE)
							{
								CurrEncrMethod = MOVE;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDC_BUTTON_LINK:
							if(CurrEncrMethod != LINK)
							{
								CurrEncrMethod = LINK;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDC_BUTTON_INPLACE:
							if(CurrEncrMethod != IDC_BUTTON_INPLACE)
							{
								CurrEncrMethod = INPLACE;
								SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);
							}
							break;

						case IDB_SECURITY:
							DialogBox(g_hInst, MAKEINTRESOURCE(IDD_SAFE_SECURITY), hDlg, (DLGPROC)SafeSecurity);
							break;
					}

					return TRUE;
				}
			}

			break;

        case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
				case PSN_SETACTIVE:
				{
					// Set the password setting here also in addition to WM_INITDIALOG bcos
					// WM_INITDIALOG is called only once, if user switches between property 
					// pages and modifies the currently selected cert, then the password settings
					// will have to be modified also
					if(g_bVeriSignCSP) 
						SetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szMinutes);
					else
					{
						TCHAR szTemp[32];

						lstrcpy(szTemp, szMinutes);

						SetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, "");

						lstrcpy(szMinutes, szTemp);
					}

					if(g_bVeriSignCSP && !g_LocalPolicy.bPasswdMethodForced)
					{
						hWnd = GetDlgItem(hDlg, IDC_TIMEOUT);
						EnableWindow(hWnd, TRUE);
		
						hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
						EnableWindow(hWnd, TRUE);

						hWnd = GetDlgItem(hDlg, IDC_STATIC_TIMEOUT);
						EnableWindow(hWnd, TRUE);

						hWnd = GetDlgItem(hDlg, IDC_STATIC_MINUTES);
						EnableWindow(hWnd, TRUE);
					}
					else
					{
						hWnd = GetDlgItem(hDlg, IDC_TIMEOUT);
						EnableWindow(hWnd, FALSE);
		
						hWnd = GetDlgItem(hDlg, IDE_PASSWD_TIMEOUT);
						EnableWindow(hWnd, FALSE);

						hWnd = GetDlgItem(hDlg, IDC_STATIC_TIMEOUT);
						EnableWindow(hWnd, FALSE);

						hWnd = GetDlgItem(hDlg, IDC_STATIC_MINUTES);
						EnableWindow(hWnd, FALSE);
					}

					break;
				}

                case PSN_APPLY:
				{
					if(g_bVeriSignCSP && !g_LocalPolicy.bPasswdMethodForced)
					{
						GetDlgItemText(hDlg, IDE_PASSWD_TIMEOUT, szTimeOut, 28);

						// Set timeout value only if it has changed
						if(g_LocalPolicy.PasswordPromptTimeout != (UINT)atoi(szTimeOut))
						{
							HRESULT hr;
							VARIANT varTimeOut;

							varTimeOut.vt = VT_I2;
							varTimeOut.iVal = atoi(szTimeOut);

							hr = g_pProfMgmt->put_PasswdTimeOut(varTimeOut);
							if(hr != S_OK)
								LogErrorMessage("AdvancedOpts() : g_pProfMgmt->put_PasswdTimeOut() failed", hr);
							else
								g_LocalPolicy.PasswordPromptTimeout = atoi(szTimeOut);
						}
					}
					
					g_LocalPolicy.EncryptMethod	= CurrEncrMethod;
					
					return PSNRET_NOERROR;
				}

                case PSN_KILLACTIVE:
                    SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
                    return TRUE;
                    

				case PSN_HELP:
				{
					ShowHelp("fet_advanced.htm");
					return TRUE;
				}
        }
    }

    return FALSE;
}


// Dialog procedure for the "Safe General Properties" dialog
BOOL APIENTRY SafeProperties(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	ULONG ulFiles = 0, ulFolders = 0;
	__int64 FileSize = 0;
	static BOOL bSignature;
	BYTE KeyUsageBits;
	TCHAR szEncryptCertName[MAX_MSG_LEN], szEncryptExpiryDate[MAX_MSG_LEN], szEncryptSerial[MAX_MSG_LEN];
	TCHAR szText[MAX_MSG_LEN];
	HWND hWnd;
	
	switch (message)
    {
        case WM_INITDIALOG:    
		{
			// Get no of files and total size of Safe
			GetSafeParameters(g_szStoragePath, &FileSize, NULL, &ulFiles, &ulFolders);

			GetDisplaySize(FileSize, szText, TRUE);
			SetDlgItemText(hDlg, IDC_SAFE_SIZE, szText);

			wsprintf(szText, "%u Encrypted Files", ulFiles);
			SetDlgItemText(hDlg, IDC_SAFE_FILES, szText);	

			// Check if the cert is dual usage cert, only then enable signing
			hWnd = GetDlgItem(hDlg, IDC_CHECK_SIGN);
			if(CertGetIntendedKeyUsage(X509_ASN_ENCODING, currSelCert.pCertContext->pCertInfo, &KeyUsageBits, 1))
			{
				if(KeyUsageBits & CERT_DIGITAL_SIGNATURE_KEY_USAGE)
				{
					bSignature = g_LocalPolicy.bSignatureReqd;
					if(bSignature)
						SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

					if(g_LocalPolicy.bSigReqdForced) // user cannot modify this option
						EnableWindow(hWnd, FALSE);  
				}
				else
					EnableWindow(hWnd, FALSE);
			}
			else
				EnableWindow(hWnd, FALSE);
			
			if(g_SafeProp.pCurrEncrCert)
			{
				GetCertSubjectDisplayName(currSelCert.pCertContext, szEncryptCertName);
				GetDisplayTime(&currSelCert.pCertContext->pCertInfo->NotAfter, szEncryptExpiryDate, FALSE);
				lstrcpy(szEncryptSerial, g_SafeProp.pCurrEncrCert->szSerialNum);
			}
			else
			{
				lstrcpy(szEncryptCertName, "<None>");
				lstrcpy(szEncryptExpiryDate, "<None>");
				lstrcpy(szEncryptSerial, "<None>");
			}

			SetDlgItemText(hDlg, IDC_ISSUEDTO_ENCR, szEncryptCertName);
			SetDlgItemText(hDlg, IDC_EXPIRY_ENCR, szEncryptExpiryDate);
			SetDlgItemText(hDlg, IDC_SERIAL_ENCRYPT, szEncryptSerial);

	        return TRUE;
		}

		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case BN_CLICKED:    
				{
					switch(LOWORD(wParam))
					{
						case IDC_CHECK_SIGN:
						{
							bSignature = !bSignature;
							SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);

							return TRUE;
						}

						case IDB_MODIFY_ENCR:
						{
							if(ChangeCertificate())
							{
								UpdateListOfCerts();
									
/*								TCHAR szTemp[MAX_PATH];
								LoadString(g_hInst, IDS_BACKUP, szTemp, sizeof(szTemp));
								DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DISP_TEXT), GetFocus(),
											   (DLGPROC)DisplayTextProc, (LONG)szTemp);*/

								GetCertSubjectDisplayName(currSelCert.pCertContext, szEncryptCertName);
								GetDisplayTime(&currSelCert.pCertContext->pCertInfo->NotAfter, szEncryptExpiryDate, FALSE);

								// Display the common name, exp date, serial num
								SetDlgItemText(hDlg, IDC_SERIAL_ENCRYPT, g_SafeProp.pCurrEncrCert->szSerialNum);
								SetDlgItemText(hDlg, IDC_EXPIRY_ENCR, szEncryptExpiryDate);
								SetDlgItemText(hDlg, IDC_ISSUEDTO_ENCR, szEncryptCertName);

								// Check if the encr alg selected in the policy is supported by the modified certificate
								ModifyAlgorithm(g_LocalPolicy.EncryptionAlg, 1);

								// Update the 'sign' check box depending on the certificate selected
								hWnd = GetDlgItem(hDlg, IDC_CHECK_SIGN);
								if(CertGetIntendedKeyUsage(X509_ASN_ENCODING, currSelCert.pCertContext->pCertInfo, &KeyUsageBits, 1))
								{
									if(KeyUsageBits & CERT_DIGITAL_SIGNATURE_KEY_USAGE)
									{
										bSignature = g_LocalPolicy.bSignatureReqd;
										if(bSignature)
											SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

										if(g_LocalPolicy.bSigReqdForced) // user cannot modify this option
											EnableWindow(hWnd, FALSE);  
										else
											EnableWindow(hWnd, TRUE);
									}
									else
									{
										SendMessage(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
										EnableWindow(hWnd, FALSE);
									}
								}
								else
								{
									SendMessage(hWnd, BM_SETCHECK, BST_UNCHECKED, 0);
									EnableWindow(hWnd, FALSE);
								}
							}

							return TRUE;
						}

					}
	
				}	// BN_CLICKED
			}
		}

			break;

        case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
                case PSN_APPLY:
				{
					g_LocalPolicy.bSignatureReqd = bSignature;
					return PSNRET_NOERROR;
				}
			
                case PSN_KILLACTIVE:
                    SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
                    return TRUE;
                    
				case PSN_HELP:
				{
					ShowHelp("fet_general.htm");
					return TRUE;
				}
        }
    }

    return FALSE;
}



// Dialog procedure for the "Single Folder Properties" dialog
BOOL APIENTRY FolderProperties(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	PROPSHEETPAGE * ps = (PROPSHEETPAGE *)lParam;
	static CContextMenu *pCxtMenu;
	static TCHAR szLocInSafe[MAX_PATH_LEN];

	SHFILEINFO  sfi;
	HDC dlgDC;

	switch (message)
    {
        case WM_INITDIALOG:    
		{
			TCHAR *pFolderName = NULL, szLocInSafe[MAX_PATH_LEN];
			TCHAR *lpszOrigLoc = NULL;

			pCxtMenu = (CContextMenu *)ps->lParam;
			UINT uNoItems = pCxtMenu->GetSelItemCount();

			if(uNoItems == 1)
			{
				pCxtMenu->GetSafeLocation(0, szLocInSafe);
				lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(0);

				pFolderName = strrchr(szLocInSafe, '\\') + 1;

				SetDlgItemText(hDlg, IDC_FOLDER_NAME, (LPCSTR)pFolderName);

				// Get the folder type
				SHGetFileInfo(szLocInSafe, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
				SetDlgItemText(hDlg, IDC_FOLDER_TYPE, sfi.szTypeName);
			}
			else
				SetDlgItemText(hDlg, IDC_FOLDER_TYPE, "All of type File Folder");

			__int64 FileSize = 0, OrigSize = 0;
			DWORD dwNoFolders = 0, dwNoFiles = 0;
			TCHAR szTemp[MAX_MSG_LEN];

			for(UINT i = 0; i < uNoItems; i++)
			{
				pCxtMenu->GetSafeLocation(i, szLocInSafe);
				lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(i);

				dwNoFolders++;
				GetSafeParameters(szLocInSafe, &FileSize, &OrigSize, &dwNoFiles, &dwNoFolders);
			}

			GetDisplaySize(OrigSize, szTemp, TRUE);
			SetDlgItemText(hDlg, IDC_FOLDER_ORIG_SIZE, szTemp);

			GetDisplaySize(FileSize, szTemp, TRUE);
			SetDlgItemText(hDlg, IDC_FOLDER_ENCR_SIZE, szTemp);

			if(uNoItems > 1)
			{
				wsprintf(szTemp, "%d Files, %d Folder", (UINT)dwNoFiles, (UINT)dwNoFolders);
				SetDlgItemText(hDlg, IDC_FOLDER_NAME, szTemp);
			}

			return TRUE;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT pst;
			HICON hIcon = NULL;

			dlgDC = BeginPaint(hDlg, &pst);

			UINT uNoItems = pCxtMenu->GetSelItemCount();

			if(uNoItems == 1)
			{
				SHGetFileInfo(szLocInSafe, 0, &sfi, sizeof(sfi), SHGFI_ICON);
				DrawIcon(dlgDC, 19, 21, sfi.hIcon);
			}
			else
			{
				HICON icon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_MULTIPLE_SEL));
				DrawIcon(dlgDC, 19, 21, icon);
			}

			EndPaint(hDlg, &pst);

			return FALSE;
		}
	}

	return FALSE;
}



// Dialog procedure for the "File Properties" dialog
BOOL APIENTRY FileProperties(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	PROPSHEETPAGE * ps = (PROPSHEETPAGE *)lParam;
	static CContextMenu *pCxtMenu;
	static TCHAR szLocInSafe[MAX_PATH_LEN];

	HDC dlgDC;
	HWND hWnd;
	SHFILEINFO  sfi;
			
	switch (message)
    {
        case WM_INITDIALOG:    
		{
			TCHAR szTime[MAX_MSG_LEN], *pFileName = NULL, *lpszOrigLoc = NULL;
			TCHAR szTemp[MAX_PATH];

			pCxtMenu = (CContextMenu *)ps->lParam;
			pCxtMenu->GetSafeLocation(0, szLocInSafe);
			lpszOrigLoc = (TCHAR *)pCxtMenu->GetOriginalLocation(0);

			pFileName = strrchr(szLocInSafe, '\\') + 1;

			SetDlgItemText(hDlg, IDC_FILE_NAME, (LPCSTR)pFileName);
			hWnd = GetDlgItem(hDlg, IDC_FILE_ENCRYPTED);
			SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
			EnableWindow(hWnd, FALSE);

			// Get the file type
			SHGetFileInfo(szLocInSafe, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
			SetDlgItemText(hDlg, IDC_FILE_TYPE, sfi.szTypeName);

			// Get the file attributes
			HANDLE hFind;
			WIN32_FIND_DATA wfd;
			HANDLE hFile = NULL;
			DWORD dwSigOffset = 0, dwBytesRead = 0, dwFileSize = 0;

			hFind = FindFirstFile(szLocInSafe, &wfd);
			if(INVALID_HANDLE_VALUE != hFind)
				FindClose(hFind);
			else
				return TRUE;

			// Get the creation time, this is the date encrypted. 
			GetDisplayTime(&wfd.ftCreationTime, szTime, TRUE);
			SetDlgItemText(hDlg, IDC_ENCRYPTED, szTime);

			// The creation time is when the plaintext file was originally 
			// created. This is stored in the fileinfo file
			GetDisplayTime(&pCxtMenu->GetCreationDate(0), szTime, TRUE);
			SetDlgItemText(hDlg, IDC_CREATED, szTime);

			hFile = CreateFile(szLocInSafe, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
							   FILE_ATTRIBUTE_ARCHIVE, NULL);

			dwFileSize = GetFileSize(hFile, NULL);

			// The DWORD at the beginning of the file contains the offset of the signature
			ReadFile(hFile, (LPVOID)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

			hWnd = GetDlgItem(hDlg, IDC_FILE_SIGNED);

			// Signature present at the end of file
			if(dwSigOffset != dwFileSize)
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

			EnableWindow(hWnd, FALSE);

			hWnd = GetDlgItem(hDlg, IDC_FILE_ENCR_AT_LOGOFF);
			if(g_EncrAtLogoffList->GetLocInSafe(lpszOrigLoc))
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
				
			hWnd = GetDlgItem(hDlg, IDC_FILE_DECR_LOGON);
			if(g_DecrAtLogonList->GetLocInSafe(lpszOrigLoc))
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

			GetDisplaySize(pCxtMenu->GetOriginalSize(0), szTemp, TRUE);
			SetDlgItemText(hDlg, IDC_ORIG_SIZE, szTemp);

			GetDisplaySize(dwFileSize, szTemp, TRUE);
			SetDlgItemText(hDlg, IDC_ENCR_SIZE, szTemp);

			CloseHandle(hFile);

            return (TRUE);
		}

		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case BN_CLICKED:    
				{
					SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);			
					return TRUE;
				}
			}
		}
			break;

		case WM_PAINT:
		{
			PAINTSTRUCT pst;
			HICON hIcon = NULL;

			dlgDC = BeginPaint(hDlg, &pst);

			SHGetFileInfo(szLocInSafe, 0, &sfi, sizeof(sfi), SHGFI_ICON);
			DrawIcon(dlgDC, 19, 21, sfi.hIcon);

			EndPaint(hDlg, &pst);

			return FALSE;
		}

        case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
                case PSN_APPLY:
				{
					TCHAR szLocInSafe[MAX_PATH_LEN], *lpszOrigLoc = NULL;
					UINT state = IsDlgButtonChecked(hDlg, IDC_FILE_ENCR_AT_LOGOFF);

					if(state == BST_CHECKED)
					{
						pCxtMenu->GetSafeLocation(0, szLocInSafe);
						lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(0);
						g_EncrAtLogoffList->SetLocInSafe(lpszOrigLoc, szLocInSafe);
					}
					else
						if(state == BST_UNCHECKED)
						{
							pCxtMenu->GetSafeLocation(0, szLocInSafe);
							lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(0);
							g_EncrAtLogoffList->RemoveFromList(lpszOrigLoc);
						}

					state = IsDlgButtonChecked(hDlg, IDC_FILE_DECR_LOGON);

					if(state == BST_CHECKED)
					{
						pCxtMenu->GetSafeLocation(0, szLocInSafe);
						lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(0);
						g_DecrAtLogonList->SetLocInSafe(lpszOrigLoc, szLocInSafe);
					}
					else
						if(state == BST_UNCHECKED)
						{
							pCxtMenu->GetSafeLocation(0, szLocInSafe);
							lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(0);
							g_DecrAtLogonList->RemoveFromList(lpszOrigLoc);
						}
				}
                    break;

                case PSN_KILLACTIVE:
                    SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
                    return TRUE;
                    

				case PSN_HELP:
				{
					ShowHelp("fet_fileprops.htm");
					return TRUE;
				}
        }
    }

    return FALSE;
}



// Dialog procedure for the "Multiple File Properties" dialog
BOOL APIENTRY MultipleFileProperties(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	PROPSHEETPAGE * ps = (PROPSHEETPAGE *)lParam;
	static CContextMenu *pCxtMenu;

	switch(message)
	{
        case WM_INITDIALOG:    
		{
			TCHAR szLocInSafe[MAX_PATH_LEN], szFileType[MAX_MSG_LEN], *lpszOrigLoc = NULL;
			TCHAR szTemp[MAX_MSG_LEN];
			DWORD fAttr, dwSigOffset = 0, dwBytesRead = 0, dwFileSize = 0, dwNoFiles = 0, dwNoFolders = 0;
			BOOL bFileTypeSame = TRUE;
			HANDLE hFile = NULL;
			__int64 FileSize = 0, OrigSize = 0;
			int AllSigned = -2, AllEncryptAtLogoff = -2, AllDecryptAtLogon = -2;

			pCxtMenu = (CContextMenu *)ps->lParam;

			pCxtMenu->GetSafeLocation(0, szLocInSafe);
			lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(0);

			SHFILEINFO sfi;
			SHGetFileInfo(szLocInSafe, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
			lstrcpy(szFileType, sfi.szTypeName);

			UINT uNoItems = pCxtMenu->GetSelItemCount();

			for(UINT i = 0; i < uNoItems; i++)
			{
				pCxtMenu->GetSafeLocation(i, szLocInSafe);
				lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(i);

				fAttr = GetFileAttributes(szLocInSafe);

				if(fAttr & FILE_ATTRIBUTE_DIRECTORY)
					dwNoFolders++;
				else
				{
					dwNoFiles++;
					hFile = CreateFile(szLocInSafe, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
									   FILE_ATTRIBUTE_ARCHIVE, NULL);

					dwFileSize = GetFileSize(hFile, NULL);

					if(AllSigned != -1)
					{
						// The DWORD at the beginning of the file contains the offset of the signature
						ReadFile(hFile, (LPVOID)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

						// No Signature present at the end of file
						if(dwSigOffset == dwFileSize)
						{
							if(AllSigned == 1)
								AllSigned = -1;
							else
								if(AllSigned == -2)
									AllSigned = 0;
						}
						else
						{
							if(AllSigned == 0)
								AllSigned = -1;
							else
								if(AllSigned == -2)
									AllSigned = 1;
						}
					}

					if(AllEncryptAtLogoff != -1)
					{
						if(!g_EncrAtLogoffList->GetLocInSafe(lpszOrigLoc))
						{
							if(AllEncryptAtLogoff == 1)
								AllEncryptAtLogoff = -1;
							else
								if(AllEncryptAtLogoff == -2)
									AllEncryptAtLogoff = 0;
						}
						else
						{
							if(AllEncryptAtLogoff == 0)
								AllEncryptAtLogoff = -1;
							else
								if(AllEncryptAtLogoff == -2)
									AllEncryptAtLogoff = 1;
						}
					}

					if(AllDecryptAtLogon != -1)
					{
						if(!g_DecrAtLogonList->GetLocInSafe(lpszOrigLoc))
						{
							if(AllDecryptAtLogon == 1)
								AllDecryptAtLogon = -1;
							else
								if(AllDecryptAtLogon == -2)
									AllDecryptAtLogon = 0;
						}
						else
						{
							if(AllDecryptAtLogon == 0)
								AllDecryptAtLogon = -1;
							else
								if(AllDecryptAtLogon == -2)
									AllDecryptAtLogon = 1;
						}
					}

					FileSize += dwFileSize;
					OrigSize += pCxtMenu->GetOriginalSize(i);
				
					CloseHandle(hFile);

					if(bFileTypeSame)
					{
						SHGetFileInfo(szLocInSafe, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);

						if(strcmpi(szFileType, sfi.szTypeName))
							bFileTypeSame = FALSE;
					}
				}
			}	// for()

			GetDisplaySize(OrigSize, szTemp, TRUE);
			SetDlgItemText(hDlg, IDC_MULTI_ORIG_SIZE, szTemp);

			GetDisplaySize(FileSize, szTemp, TRUE);
			SetDlgItemText(hDlg, IDC_MULTI_ENCR_SIZE, szTemp);

			wsprintf(szTemp, "%d Files, %d Folder", (UINT)dwNoFiles, (UINT)dwNoFolders);
			SetDlgItemText(hDlg, IDC_NO_SEL, szTemp);

			if(bFileTypeSame)
			{
				wsprintf(szTemp, "All of type %s", szFileType);
				SetDlgItemText(hDlg, IDC_MULTI_FILE_TYPE, szTemp);
			}
			else
				SetDlgItemText(hDlg, IDC_MULTI_FILE_TYPE, "Multiple Types");


			HWND hWnd;
			hWnd = GetDlgItem(hDlg, IDC_MULTI_FILE_ENCRYPTED);
			SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
			EnableWindow(hWnd, FALSE);

			hWnd = GetDlgItem(hDlg, IDC_MULTI_SIGNED);
			if(AllSigned == -1)
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
			else
				if(AllSigned == 1)
					SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

			EnableWindow(hWnd, FALSE);

			hWnd = GetDlgItem(hDlg, IDC_MULTI_ENCR_AT_LOGOFF);
			if(AllEncryptAtLogoff == -1)
				CheckDlgButton(hDlg, IDC_MULTI_ENCR_AT_LOGOFF, BST_INDETERMINATE);
			else
				if(AllEncryptAtLogoff == 1)
					SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

			
			hWnd = GetDlgItem(hDlg, IDC_MULTI_DECR_LOGON);
			if(AllDecryptAtLogon == -1)
				CheckDlgButton(hDlg, IDC_MULTI_DECR_LOGON, BST_INDETERMINATE);
			else
				if(AllDecryptAtLogon == 1)
					SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
			
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case BN_CLICKED:    
				{
					SendMessage(GetParent(hDlg), PSM_CHANGED, (WPARAM)hDlg, 0L);			
					return TRUE;
				}
			}
		}
			break;
			
        case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
                case PSN_APPLY:
				{
					UINT uNoItems = pCxtMenu->GetSelItemCount(), i;
					TCHAR szLocInSafe[MAX_PATH_LEN], *lpszOrigLoc = NULL;
					UINT state = IsDlgButtonChecked(hDlg, IDC_MULTI_ENCR_AT_LOGOFF);

					if(state == BST_CHECKED)
					{
						for(i = 0; i < uNoItems; i++)
						{
							pCxtMenu->GetSafeLocation(i, szLocInSafe);
							lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(i);
							g_EncrAtLogoffList->SetLocInSafe(lpszOrigLoc, szLocInSafe);
						}
					}
					else
						if(state == BST_UNCHECKED)
						{
							for(i = 0; i < uNoItems; i++)
							{
								pCxtMenu->GetSafeLocation(i, szLocInSafe);
								lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(i);
								g_EncrAtLogoffList->RemoveFromList(lpszOrigLoc);
							}
						}

					state = IsDlgButtonChecked(hDlg, IDC_MULTI_DECR_LOGON);

					if(state == BST_CHECKED)
					{
						for(i = 0; i < uNoItems; i++)
						{
							pCxtMenu->GetSafeLocation(i, szLocInSafe);
							lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(i);
							g_DecrAtLogonList->SetLocInSafe(lpszOrigLoc, szLocInSafe);
						}
					}
					else
						if(state == BST_UNCHECKED)
						{
							for(i = 0; i < uNoItems; i++)
							{
								pCxtMenu->GetSafeLocation(i, szLocInSafe);
								lpszOrigLoc = (LPTSTR)pCxtMenu->GetOriginalLocation(i);
								g_DecrAtLogonList->RemoveFromList(lpszOrigLoc);
							}
						}
				}
                    break;

                case PSN_KILLACTIVE:
                    SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
                    return TRUE;

        }
			break;
	}

	return FALSE;
}



BOOL APIENTRY ReplaceConfirm(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:    
		{
			TCHAR szOverWrite[MAX_MSG_LEN], szTemp[MAX_MSG_LEN], szDisplay[MAX_MSG_LEN], *pStr = NULL;

			if(!_strnicmp((LPCTSTR)lParam, g_szStoragePath, lstrlen(g_szStoragePath)))
			{
				pStr = strrchr((LPCTSTR)lParam, '\\');

				DWORD dwFattr = 0;
				dwFattr = GetFileAttributes((LPCTSTR)lParam);

				LoadString(g_hInst, IDS_FILE_FOLDER_PRESENT, szTemp, sizeof(szTemp));
				if(dwFattr & FILE_ATTRIBUTE_DIRECTORY)
				{
					wsprintf(szDisplay, szTemp, "folder", pStr + 1);
					LoadString(g_hInst, IDS_FOLDER_OVERWRITE, szOverWrite, sizeof(szOverWrite));
				}
				else
				{
					wsprintf(szDisplay, szTemp, "file", pStr + 1);
					LoadString(g_hInst, IDS_FILE_OVERWRITE, szOverWrite, sizeof(szOverWrite));
				}
			}
			else
			{
				lstrcpy(szTemp, (LPCTSTR)lParam);
				pStr = strrchr(szTemp, '\\');
				if(pStr)
					*pStr = '\0';

				wsprintf(szDisplay, "The file \'%s\' is already present in \'%s\'", pStr + 1, szTemp);
				LoadString(g_hInst, IDS_FILE_OVERWRITE, szOverWrite, sizeof(szOverWrite));
			}

			SetDlgItemText(hDlg, IDC_FILE_FOLDER, szDisplay);
			SetDlgItemText(hDlg, IDC_REPLACE_TEXT, szOverWrite);

            return TRUE;
		}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:    
					EndDialog(hDlg, IDOK);
					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return TRUE;

				case IDB_YESTOALL:
					EndDialog(hDlg, IDB_YESTOALL);
					return TRUE;

				case IDB_NO:
					EndDialog(hDlg, IDB_NO);
					return TRUE;
			}

			break;

    }

    return FALSE;
}




// Dialog procedure for the "Encrypt Error" dialog
BOOL APIENTRY EncryptError(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:    
		{
			SetDlgItemText(hDlg, IDC_ERROR_TEXT, (LPCSTR)lParam);
            return (TRUE);
		}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:    
					EndDialog(hDlg, IDOK);
					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return TRUE;

				case ID_YES_TO_ALL:
					EndDialog(hDlg, ID_YES_TO_ALL);
					return TRUE;

				case ID_NO:
					EndDialog(hDlg, ID_NO);
					return TRUE;

			}

			break;

    }
    return (FALSE);
}


// Dialog procedure for the "Decrypt Error" dialog
BOOL APIENTRY DecryptError(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:    
		{
			TCHAR szText[MAX_MSG_LEN];

			if(!_strnicmp((LPCSTR)lParam, "File", 4))
				LoadString(g_hInst, IDS_DECRYPT_FILE_ERROR, szText, MAX_MSG_LEN);
			else
				LoadString(g_hInst, IDS_DECRYPT_FOLDER_ERROR, szText, MAX_MSG_LEN);

			SetDlgItemText(hDlg, IDC_FOLDER_TEXT, szText);

			SetDlgItemText(hDlg, IDC_ERROR_MSG, (LPCSTR)lParam);
            return (TRUE);
		}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:    
					EndDialog(hDlg, IDOK);
					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return TRUE;

				case ID_YES_TO_ALL:
					EndDialog(hDlg, ID_YES_TO_ALL);
					return TRUE;

				case ID_NO:
					EndDialog(hDlg, ID_NO);
					return TRUE;
			}

			break;

    }

    return FALSE;
}



// Dialog procedure for the "Safe Security" dialog
BOOL APIENTRY SafeSecurity(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	HWND hWnd;
	PCCERT_CONTEXT pCertCxt = NULL;
	DWORD dwErr = 0;
	TCHAR szMsg[MAX_MSG_LEN];
		
	switch (message)
    {
        case WM_INITDIALOG:
		{
			// Assign the buddy to the spin ctrl
			hWnd = GetDlgItem(hDlg, IDC_SPIN);
			HWND hWndBuddy = GetDlgItem(hDlg, IDE_WAIT);
			SendMessage(hWnd, UDM_SETBUDDY, (WPARAM)hWndBuddy, 0);

			// Set the range for the spin ctrl
			SendMessage(hWnd, UDM_SETRANGE, 0,(LPARAM)MAKELONG(60, 1));

			// Set limit text for the buddy
			SendMessage(hWndBuddy, EM_LIMITTEXT, 2, 0);

			// Hide the 'Change' button in case of Winnt
			HWND hToHide;
			if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
			{
				hToHide = GetDlgItem(hDlg, IDB_PASSWORD);
				EnableWindow(hToHide, FALSE);
				ShowWindow(hToHide, SW_HIDE);
			}

			HWND hEncryptAlgo = GetDlgItem(hDlg, IDC_ENCRYPT_ALGO);
			HWND hSignAlgo	  = GetDlgItem(hDlg, IDC_HASH_ALGO);

			SendMessage(hEncryptAlgo, CB_RESETCONTENT, 0, 0);
			SendMessage(hSignAlgo, CB_RESETCONTENT, 0, 0);

			if(g_LocalPolicy.bEncrAlgForced)
				EnableWindow(hEncryptAlgo, FALSE);

			if(g_LocalPolicy.bHashAlgForced)
				EnableWindow(hSignAlgo, FALSE);

			if(g_LocalPolicy.bLockPeriodForced)
			{
				hWnd = GetDlgItem(hDlg, IDE_WAIT);
				EnableWindow(hWnd, FALSE);
			}

			hWnd = GetDlgItem(hDlg, IDC_SECURE_DEL);
			if(g_LocalPolicy.bSecDelForced)
				EnableWindow(hWnd, FALSE);

			if(g_LocalPolicy.bSecureDelete)
				SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);

			// Show current encryption alg and all algs for this CSP
			if(currSelCert.pCertContext)
			{
				ULONG nSize;
			
				PCRYPT_KEY_PROV_INFO pKeyProv;
				if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
												  NULL, &nSize))
				{
					dwErr = GetLastError();
					DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
					LogErrorMessage("SafeSecurity:CertGetCertificateContextProperty() failed", dwErr);
					return FALSE;
				}

				pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
				if(!pKeyProv)
				{
					DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
					LogErrorMessage("SafeSecurity() : Out of memory", 0);
					return FALSE;
				}

				
				if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
													  pKeyProv, &nSize))
				{
					dwErr = GetLastError();
					DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
					LogErrorMessage("SafeSecurity:CertGetCertificateContextProperty() failed", dwErr);
					return FALSE;
				}

				LPSTR szProviderName ;
				szProviderName	= _WideToMultiString(pKeyProv->pwszProvName);
				AddAlgorithms(szProviderName, hDlg, 1);
				free(pKeyProv);
				free(szProviderName);

				UINT CurSel;
				if((CurSel = SendMessage(hEncryptAlgo, CB_FINDSTRINGEXACT, -1, (LPARAM)(LPCSTR)g_LocalPolicy.EncryptionAlg)) != CB_ERR)
					SendMessage(hEncryptAlgo, CB_SETCURSEL, CurSel, 0);
				else
				{
					// The algs in ComboBox don't match the alg in the Policy File
					// Select any one alg from the list and modify the policy var
					SendMessage(hEncryptAlgo, CB_SETCURSEL, 0, 0);
					SendMessage(hEncryptAlgo, CB_GETLBTEXT, 0, (LPARAM)(LPCSTR)g_LocalPolicy.EncryptionAlg);
				}
			}
			else
			{
				SendMessage(hEncryptAlgo, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"<None>");
				SendMessage(hEncryptAlgo, CB_SETCURSEL, 0, 0);
			}

			BYTE KeyUsageBits;
			if(CertGetIntendedKeyUsage(X509_ASN_ENCODING, currSelCert.pCertContext->pCertInfo, &KeyUsageBits, 1))
			{
				if(KeyUsageBits & CERT_DIGITAL_SIGNATURE_KEY_USAGE)
				{
					// Show current signature alg and all algs for this CSP
					if(currSelCert.pCertContext)
					{
						ULONG nSize;
					
						PCRYPT_KEY_PROV_INFO pKeyProv;
						if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
														  NULL, &nSize))
						{
							dwErr = GetLastError();
							DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
							LogErrorMessage("SafeSecurity:CertGetCertificateContextProperty failed", dwErr);
							return FALSE;
						}

						pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
						if(!pKeyProv)
						{
							DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
							LogErrorMessage("SafeSecurity() : Out of memory", 0);
							return FALSE;
						}
						
						if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
														  pKeyProv, &nSize))
						{
							dwErr = GetLastError();
							DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
							LogErrorMessage("SafeSecurity:CertGetCertificateContextProperty failed", dwErr);
							return FALSE;
						}

						LPSTR szProviderName ;
						szProviderName	= _WideToMultiString(pKeyProv->pwszProvName);
						AddAlgorithms(szProviderName, hDlg, 0);
						free(pKeyProv);
						free(szProviderName);

						UINT CurSel;
						if((CurSel = SendMessage(hSignAlgo, CB_FINDSTRINGEXACT, -1, (LPARAM)(LPCSTR)g_LocalPolicy.HashAlg)) != CB_ERR)
							SendMessage(hSignAlgo, CB_SETCURSEL, CurSel, 0);
						else
						{
							// The algs in ComboBox don't match the alg in the Policy File
							// Select any one alg from the list and modify the policy var
							SendMessage(hSignAlgo, CB_SETCURSEL, 0, 0);
							SendMessage(hSignAlgo, CB_GETLBTEXT, 0, (LPARAM)(LPCSTR)g_LocalPolicy.HashAlg);
						}
					}
					else
					{
						SendMessage(hSignAlgo, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"<None>");
						SendMessage(hSignAlgo, CB_SETCURSEL, 0, 0);
					}
				}
			}
			else
				EnableWindow(hSignAlgo, FALSE);

			// See if Screen Saving is enabled
			LRESULT	lResult;
			HKEY	hKey;
			DWORD	dwType, dwSize = MAX_PATH_LEN;
			BOOL	bScrnSave;
			TCHAR	szScrnSvr[MAX_PATH_LEN];
								
			SystemParametersInfo(SPI_GETSCREENSAVEACTIVE, 0, &bScrnSave, 0);
			lstrcpy(szScrnSvr, "(None)");

			// If enabled get the active screen saver
			if(bScrnSave)
			{
				if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
				{
					dwSize = MAX_PATH;

					lResult = RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, 0, KEY_ALL_ACCESS, &hKey);
					if(lResult != ERROR_SUCCESS)
					{
						dwErr = GetLastError();
						wsprintf(szMsg, "SafeSecurity:RegOpenKeyEx() for \'%s\' failed", REGSTR_PATH_SCREENSAVE);
						LogErrorMessage(szMsg, dwErr);
						RegCloseKey(hKey);
						return TRUE;
					}

					lResult = RegQueryValueEx(hKey, "SCRNSAVE.EXE", NULL, &dwType, (LPBYTE)szScrnSvr, &dwSize);
					if(lResult != ERROR_SUCCESS)
					{
						dwErr = GetLastError();
						LogErrorMessage("SafeSecurity:RegQueryValueEx() SCRNSAVE.EXE failed", dwErr);
						lstrcpy(szScrnSvr, "(None)");
					}

					RegCloseKey(hKey);
				}	// if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
				else
				{
					TCHAR szSystemFile[MAX_PATH_LEN];
					lstrcpy(szSystemFile, g_szWinDir);
					lstrcat(szSystemFile, "\\system.ini");

					GetPrivateProfileString("boot", "SCRNSAVE.EXE", "(None)", szScrnSvr, MAX_PATH, szSystemFile);
				}
			} //if(bScrnSave)


			// Fill the screen savers in the combo box and if any screen
			// saver is selected thro the desktop then set focus to it
			AddScreenSaver(hDlg, g_szWinDir, szScrnSvr);
			AddScreenSaver(hDlg, g_szWinSysDir, szScrnSvr);

			HWND hScrSvr = GetDlgItem(hDlg, IDC_SCREEN_SAVER);
			SendMessage(hScrSvr, CB_ADDSTRING, 0, (LPARAM)"(None)");

			if(!lstrcmpi(szScrnSvr, "(None)"))
				SendMessage(hScrSvr, CB_SELECTSTRING, 0, (LPARAM)(LPCSTR)"(None)");

			// Get the screen saver timeout
			int uTimeOut;
			TCHAR szTimeOut[32];
			dwSize = 32;

			if(RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
			{
				dwErr = GetLastError();
				wsprintf(szMsg, "SafeSecurity:RegOpenKeyEx() for \'%s\' failed", REGSTR_PATH_SCREENSAVE);
				LogErrorMessage(szMsg, dwErr);
				RegCloseKey(hKey);
				return TRUE;
			}

			if(RegQueryValueEx(hKey, "ScreenSaveTimeOut", NULL, &dwType, (LPBYTE)szTimeOut, &dwSize)!= ERROR_SUCCESS)
				lstrcpy(szTimeOut, "0");

			RegCloseKey(hKey);

			uTimeOut = atoi(szTimeOut);
			uTimeOut /= 60;	// in minutes

			SetDlgItemInt(hDlg, IDE_WAIT, uTimeOut, FALSE);

			if(!lstrcmpi(szScrnSvr, "(None)"))
			{
				hWnd = GetDlgItem(hDlg, IDC_PASSWORD);
				EnableWindow(hWnd, FALSE);

				if(g_dwPlatform != VER_PLATFORM_WIN32_NT)
				{
					hWnd = GetDlgItem(hDlg, IDB_PASSWORD);
					EnableWindow(hWnd, FALSE);
				}

				hWnd = GetDlgItem(hDlg, IDE_WAIT);
				EnableWindow(hWnd, FALSE);
			} // if(!lstrcmpi(szScrnSvr, "(None)"))
			else
			{
				LRESULT	lResult;
				HKEY	hKey;
				DWORD	dwType, dwSize;
				BOOL	bPassword = FALSE;
				if(RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
				{
					dwErr = GetLastError();
					wsprintf(szMsg, "SafeSecurity:RegOpenKeyEx() for \'%s\' failed", REGSTR_PATH_SCREENSAVE);
					LogErrorMessage(szMsg, dwErr);
					RegCloseKey(hKey);
					return TRUE;
				}

				TCHAR szQueryStr[MAX_MSG_LEN]; 
				if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
					lstrcpy(szQueryStr, "ScreenSaverIsSecure");
				else
					lstrcpy(szQueryStr, "ScreenSaveUsePassword");

				// On some machines the type is string on some it is hex no
				lResult = RegQueryValueEx(hKey, szQueryStr, NULL, &dwType, NULL, NULL);
				if(dwType == REG_SZ)
				{
					TCHAR szTemp[12];
					dwSize = 12;
					lResult = RegQueryValueEx(hKey, szQueryStr, NULL, &dwType, (LPBYTE)szTemp, &dwSize);
					if(!lstrcmpi(szTemp, "1"))
						bPassword = TRUE;
				}
				else
				{
					DWORD dwTemp;
					dwSize = sizeof(DWORD);
					lResult = RegQueryValueEx(hKey, szQueryStr, NULL, &dwType, (LPBYTE)&dwTemp, &dwSize);
					bPassword = (BOOL)dwTemp;
				}

				RegCloseKey(hKey);

				if(bPassword)
				{
					hWnd = GetDlgItem(hDlg, IDC_PASSWORD);
					SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
				}
				else
				{
					// Disable the 'change' password button for Win95/98
					if(g_dwPlatform != VER_PLATFORM_WIN32_NT)
					{
						hWnd = GetDlgItem(hDlg, IDB_PASSWORD);
						EnableWindow(hWnd, FALSE);
					}
				}
			} // Some Screen Saver present

			return (TRUE);
		} // WM_INITDLG

		case WM_COMMAND:
		{
			switch(HIWORD(wParam))
			{
				case CBN_SELCHANGE:
				{
					UINT CurSel;
					TCHAR szCurrScrnSvr[MAX_MSG_LEN];

					if(LOWORD(wParam) == IDC_SCREEN_SAVER)
					{
						if((CurSel = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0)) != CB_ERR)
						{
							SendMessage((HWND)lParam, CB_GETLBTEXT, CurSel, (LPARAM) (LPCSTR)szCurrScrnSvr);

							if(!lstrcmpi(szCurrScrnSvr, "(None)"))
							{
								hWnd = GetDlgItem(hDlg, IDE_WAIT);
								EnableWindow(hWnd, FALSE);

								hWnd = GetDlgItem(hDlg, IDC_PASSWORD);
								EnableWindow(hWnd, FALSE);

								if(g_dwPlatform != VER_PLATFORM_WIN32_NT)
								{
									hWnd = GetDlgItem(hDlg, IDB_PASSWORD);
									EnableWindow(hWnd, FALSE);
								}
							}
							else
							{
								hWnd = GetDlgItem(hDlg, IDE_WAIT);
								EnableWindow(hWnd, TRUE);

								hWnd = GetDlgItem(hDlg, IDC_PASSWORD);
								EnableWindow(hWnd, TRUE);

								if(g_dwPlatform != VER_PLATFORM_WIN32_NT)
								{
									if(SendMessage(hWnd, BM_GETCHECK, 0, 0) == BST_CHECKED)
									{
										hWnd = GetDlgItem(hDlg, IDB_PASSWORD);
										EnableWindow(hWnd, TRUE);
									}
								}
							}
						}
					} // if(LOWORD(wParam) == IDC_SCREEN_SAVER)

					return TRUE;
				}

				case BN_CLICKED:    
				{
					switch(LOWORD(wParam))
					{
						case IDB_PASSWORD:
							{
								int CurSel;
								hWnd = GetDlgItem(hDlg, IDC_SCREEN_SAVER);
								if((CurSel = SendMessage(hWnd, CB_GETCURSEL, 0, 0)) != CB_ERR)
								{
									// Get the screen saver executable which represents
									// the selected screen saver
									TCHAR szCurrScrnSvr[MAX_PATH_LEN], szScrnSvrFile[MAX_PATH_LEN];
									SendMessage(hWnd, CB_GETLBTEXT, CurSel, (LPARAM)(LPCSTR)szCurrScrnSvr);
									if(!GetScrnSvrFile(szCurrScrnSvr, g_szWinSysDir, szScrnSvrFile))
										GetScrnSvrFile(szCurrScrnSvr, g_szWinDir, szScrnSvrFile);

									STARTUPINFO si;
									PROCESS_INFORMATION pi;
									memset(&si,0,sizeof(STARTUPINFO));
									si.cb = sizeof(STARTUPINFO);
									si.wShowWindow = SW_SHOW;

									TCHAR szTemp[MAX_PATH_LEN];
									wsprintf(szTemp, "%s /a", szScrnSvrFile);

									CreateProcess(NULL, szTemp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
								}
							}

							break;

						case IDC_PASSWORD:
							if(g_dwPlatform != VER_PLATFORM_WIN32_NT)
							{
								hWnd = GetDlgItem(hDlg, IDB_PASSWORD);
					
								if(SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) 
											   == BST_CHECKED)
									EnableWindow(hWnd, TRUE);
								else
									EnableWindow(hWnd, FALSE);
							}
								
							break;

						case IDB_HELP:
						{
							ShowHelp("fet_security.htm");
							break;
						}

						case IDOK:    
						{
							LRESULT	lResult;
							HKEY	hKey;

							// Some of the selections may have been modified
							// update them
							hWnd = GetDlgItem(hDlg, IDC_SECURE_DEL);
							if(SendMessage(hWnd, BM_GETCHECK, 0, 0) == BST_CHECKED)
								g_LocalPolicy.bSecureDelete = TRUE;
							else
								g_LocalPolicy.bSecureDelete = FALSE;


							UINT CurSel;
							hWnd = GetDlgItem(hDlg, IDC_ENCRYPT_ALGO);
							if((CurSel = SendMessage(hWnd, CB_GETCURSEL, 0, 0)) != CB_ERR)
								SendMessage(hWnd, CB_GETLBTEXT, CurSel, (LPARAM)(LPCSTR)g_LocalPolicy.EncryptionAlg);

							hWnd = GetDlgItem(hDlg, IDC_HASH_ALGO);
							if((CurSel = SendMessage(hWnd, CB_GETCURSEL, 0, 0)) != CB_ERR)
								SendMessage(hWnd, CB_GETLBTEXT, CurSel, (LPARAM)(LPCSTR)g_LocalPolicy.HashAlg);

							hWnd = GetDlgItem(hDlg, IDC_SCREEN_SAVER);
							if((CurSel = SendMessage(hWnd, CB_GETCURSEL, 0, 0)) != CB_ERR)
							{
								// Get the screen saver executable which represents								
								// the selected screen saver
								TCHAR szCurrScrnSvr[MAX_PATH_LEN], szScrnSvrFile[MAX_PATH_LEN];
								SendMessage(hWnd, CB_GETLBTEXT, CurSel, (LPARAM)(LPCSTR)szCurrScrnSvr);
								
								if(!lstrcmpi(szCurrScrnSvr, "(None)"))
								{
									/*LoadString(g_hInst, IDS_SEL_SCRNSVR, szMsg, MAX_PATH);
									if(MessageBox(hDlg, szMsg, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDYES)
										return FALSE;*/

									if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
									{
										if(RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, 0,
											 KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
										{
											dwErr = GetLastError();
											wsprintf(szMsg, "SafeSecurity:RegOpenKeyEx() for \'%s\' failed", REGSTR_PATH_SCREENSAVE);
											LogErrorMessage(szMsg, dwErr);
											RegCloseKey(hKey);
										}

										RegDeleteKey(hKey, "SCRNSAVE.EXE");
										RegCloseKey(hKey);
									}
									else
									{
										TCHAR szSystemFile[MAX_PATH_LEN];
										lstrcpy(szSystemFile, g_szWinDir);
										lstrcat(szSystemFile, "\\system.ini");

										WritePrivateProfileString("boot", "SCRNSAVE.EXE", NULL, szSystemFile);
									}

									SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, FALSE, 0, SPIF_SENDCHANGE);
								} // if(!lstrcmpi(szCurrScrnSvr, "(None)"))
								else
								{
									if(!GetScrnSvrFile(szCurrScrnSvr, g_szWinSysDir, szScrnSvrFile))
										GetScrnSvrFile(szCurrScrnSvr, g_szWinDir, szScrnSvrFile);

									UINT uTimeOut = GetDlgItemInt(hDlg, IDE_WAIT, NULL, FALSE);
									TCHAR szTimeOut[32];

									uTimeOut *= 60; // in seconds
									SystemParametersInfo(SPI_SETSCREENSAVETIMEOUT, uTimeOut, 0, SPIF_SENDCHANGE);

									// Check if password protection is ON
									BOOL bPasswordProtect = TRUE;
									hWnd = GetDlgItem(hDlg, IDC_PASSWORD);
									if(SendMessage(hWnd, BM_GETCHECK, 0, 0) != BST_CHECKED)
									{
										/*LoadString(g_hInst, IDS_SCRNSVR_PASSWD, szMsg, MAX_PATH);
										if(MessageBox(hDlg, szMsg,  "Safe", MB_YESNO | MB_ICONINFORMATION) == IDYES)
											return FALSE;*/

										bPasswordProtect = FALSE;
									}
									
									if(RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, 0,
												    KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
									{
										dwErr = GetLastError();
										wsprintf(szMsg, "SafeSecurity:RegOpenKeyEx() for \'%s\' failed", REGSTR_PATH_SCREENSAVE);
										LogErrorMessage(szMsg, dwErr);
										RegCloseKey(hKey);
									}

									TCHAR szQueryStr[MAX_MSG_LEN]; 
									DWORD dwType;
									if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
										lstrcpy(szQueryStr, "ScreenSaverIsSecure");
									else
										lstrcpy(szQueryStr, "ScreenSaveUsePassword");

									lResult = RegQueryValueEx(hKey, szQueryStr, NULL, &dwType, NULL, NULL);
									if(dwType == REG_SZ)
									{
										bPasswordProtect += '0';
										lResult = RegSetValueEx(hKey, szQueryStr, NULL, REG_SZ, 
																(LPBYTE)&bPasswordProtect, 1);
									}
									else
										lResult = RegSetValueEx(hKey, szQueryStr, NULL, REG_DWORD, 
																(LPBYTE)&bPasswordProtect, sizeof(DWORD));

									if(lResult != ERROR_SUCCESS)
									{
										dwErr = GetLastError();
										wsprintf(szMsg, "SafeSecurity:RegSetValueEx() for 'Password Protect' failed", REGSTR_PATH_SCREENSAVE);
										LogErrorMessage(szMsg, dwErr);
									}

									// Set the 'ScreenSaveTimeOut'
									itoa(uTimeOut, szTimeOut, 10);
									lResult = RegSetValueEx(hKey, "ScreenSaveTimeOut", 0, REG_SZ,
												(LPBYTE)&szTimeOut, (lstrlen(szTimeOut) + 1) * sizeof(TCHAR));

									if(lResult != ERROR_SUCCESS)
									{
										dwErr = GetLastError();
										wsprintf(szMsg, "SafeSecurity:RegSetValueEx() for 'ScreenSaveTimeOut' failed", REGSTR_PATH_SCREENSAVE);
										LogErrorMessage(szMsg, dwErr);
									}

									RegCloseKey(hKey);
									
									// put the currently selected Screen Saver
									if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
									{
										if(RegOpenKeyEx(HKEY_CURRENT_USER, REGSTR_PATH_SCREENSAVE, 0,
											KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
										{
											dwErr = GetLastError();
											wsprintf(szMsg, "SafeSecurity:RegOpenKeyEx() for \'%s\' failed.", REGSTR_PATH_SCREENSAVE);
											LogErrorMessage(szMsg, dwErr);
										}
										else
											if(RegSetValueEx(hKey, "SCRNSAVE.EXE", NULL, REG_SZ, 
   												(LPBYTE)szScrnSvrFile, lstrlen(szScrnSvrFile)) != ERROR_SUCCESS)
											{
												dwErr = GetLastError();
												LogErrorMessage("SafeSecurity:RegSetValueEx() for 'SCRNSAVE.EXE' failed", dwErr);
											}
										
										RegCloseKey(hKey);
									}									
									else
									{
										TCHAR szSystemFile[MAX_PATH_LEN], *pStr = NULL;
										lstrcpy(szSystemFile, g_szWinDir);
										lstrcat(szSystemFile, "\\system.ini");

										// Get the short file name of 'szScrnSvrFile'
										WIN32_FIND_DATA wfd;
										HANDLE hFind = FindFirstFile(szScrnSvrFile, &wfd);
										if(hFind != INVALID_HANDLE_VALUE)
										{
											pStr = strrchr(szScrnSvrFile, '\\');
											lstrcpy(pStr + 1, wfd.cAlternateFileName);
											FindClose(hFind);

											WritePrivateProfileString("boot", "SCRNSAVE.EXE", szScrnSvrFile, szSystemFile);
										}
									}

									SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, TRUE, 0, SPIF_SENDCHANGE);
								}
							}	
		
							EndDialog(hDlg, IDOK);

							return TRUE;
						}

						case IDCANCEL:
							EndDialog(hDlg, IDCANCEL);
							return TRUE;
					}

					return TRUE;
				}
			}

			break;
		}
    }

    return FALSE;
}



void EnumCSPs()
{
	HKEY    hEnumKey, hKey;
	TCHAR   szSubKey[MAX_MSG_LEN], szTypeKey[MAX_MSG_LEN];
	DWORD	dwSize = MAX_PATH, dwType, dwErr;
	BOOL	bRetVal = TRUE;

	wsprintf(szSubKey, TEXT("Software\\Microsoft\\Cryptography\\Defaults\\Provider"));
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0, KEY_ENUMERATE_SUB_KEYS, &hEnumKey) == NOERROR)
	{
		for(int i = 0; ; i++)
		{
			dwSize = MAX_MSG_LEN;

			if(RegEnumKeyEx(hEnumKey, i, szSubKey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
			{
				lstrcpy(g_CspInfo[i].szCspName, szSubKey);

				lstrcpy(szTypeKey, "Software\\Microsoft\\Cryptography\\Defaults\\Provider\\");
				lstrcat(szTypeKey, szSubKey);

				dwSize = sizeof(DWORD);

				RegOpenKeyEx(HKEY_LOCAL_MACHINE, szTypeKey, NULL, KEY_READ, &hKey);
				RegQueryValueEx(hKey, "Type", NULL, NULL, (LPBYTE)&dwType, &dwSize);
				RegCloseKey(hKey);

				g_CspInfo[i].nCspType = (UINT)dwType;
				g_nCSPs++;
			}
			else
				break;
		}
	}
	else
	{
		TCHAR szMsg[MAX_MSG_LEN];
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_OPEN, MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "EnumCSPs:RegOpenKeyEx() for \'%s\' failed", szSubKey);
		LogErrorMessage(szMsg, dwErr);
	}

	RegCloseKey(hEnumKey);
}



BOOL AddAlgorithms(LPCSTR lpszProviderName, HWND hDlg, BOOL bEncrypt)
{
	HCRYPTPROV hCryptProv;
	DWORD dwFlags = 0, cbData = 0, dwNameLen = 0, dwBits = 0, dwErr = 0;
	BYTE *pbData = NULL, *ptr = NULL;
	ALG_ID Algid;
	HWND hEncryptAlgo, hSignAlgo;
	TCHAR szAlgName[MAX_MSG_LEN], szAlgorithm[MAX_MSG_LEN];

	hEncryptAlgo = GetDlgItem(hDlg, IDC_ENCRYPT_ALGO);
	hSignAlgo = GetDlgItem(hDlg, IDC_HASH_ALGO);
	
	for(int i = 0; i < g_nCSPs; i++)
		if(!lstrcmpi(g_CspInfo[i].szCspName, lpszProviderName))
			break;

	if(i == g_nCSPs)
	{
		LogErrorMessage("AddAlgorithm:CSP selection failure", 0);
		return FALSE;
	}

	if(!CryptAcquireContext(&hCryptProv, NULL, lpszProviderName, g_CspInfo[i].nCspType, 
							CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("AddAlgorithm:CryptAcquireContext() failed", dwErr);
		return FALSE;
	}

	// Enum the supported algorithms
	for(i = 0; ; i++)
	{
		if(i == 0)
			dwFlags = CRYPT_FIRST;
		else
			dwFlags = 0;

		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, NULL, &cbData, dwFlags))
			break;

		pbData = (BYTE *)malloc(cbData);
		if(!pbData)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("AddAlgorithms() : Out of memory", 0);
			return FALSE;
		}

		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, pbData, &cbData, dwFlags))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("AddAlgorithms:CryptGetProvParam() failed", dwErr);
			break;
		}

		ptr = pbData;

		Algid = *(ALG_ID *)ptr;
		ptr += sizeof(ALG_ID);
		dwBits = *(DWORD *)ptr;
		ptr += sizeof(DWORD);

		dwNameLen = *(DWORD *)ptr;

		ptr += sizeof(DWORD);
		strncpy(szAlgName, (const char *)ptr, dwNameLen);
		wsprintf(szAlgorithm, "%s-%d bits", szAlgName, dwBits);

		// Determine the algorithm type.    
		switch(GET_ALG_CLASS(Algid)) 
		{
			case ALG_CLASS_DATA_ENCRYPT:
			{
				if(bEncrypt)
					if(IsAlgSupported(szAlgorithm, 1))
						SendMessage(hEncryptAlgo, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szAlgorithm);
			}
				break;

			case ALG_CLASS_HASH:
			{
				if(!bEncrypt)
					if(IsAlgSupported(szAlgName, 0))
						SendMessage(hSignAlgo, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szAlgName);
			}
				break;
		}

		free(pbData);
	}

	CryptReleaseContext(hCryptProv, 0);

	return TRUE;
}


void ModifyAlgorithm(LPCSTR lpAlg, BOOL bEncrypt)
{
	HCRYPTPROV hCryptProv;
	DWORD dwFlags = 0, cbData = 0, dwNameLen = 0, dwBits = 0, dwErr = 0;
	BYTE *pbData = NULL, *ptr = NULL;
	ALG_ID Algid;
	TCHAR szAlgName[MAX_MSG_LEN], szEncrAlg[MAX_MSG_LEN], szHashAlg[MAX_MSG_LEN];
	TCHAR szAlgorithm[MAX_MSG_LEN];
	BOOL bPresent = FALSE;

	if(!currSelCert.pCertContext)
		return;

	ULONG nSize;
	
	PCRYPT_KEY_PROV_INFO pKeyProv;
	CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
									  NULL, &nSize);

	pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
	if(!pKeyProv)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("ModifyAlgorithm() : Out of memory", 0);
		return;
	}
	
	CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
									  pKeyProv, &nSize);
	LPSTR szProviderName ;
	szProviderName	= _WideToMultiString(pKeyProv->pwszProvName);

	free(pKeyProv);

	for(int i = 0; i < g_nCSPs; i++)
		if(!lstrcmpi(g_CspInfo[i].szCspName, szProviderName))
			break;

	if(i == g_nCSPs)
	{
		LogErrorMessage("ModifyAlgorithm:CSP selection failure", 0);
		free(szProviderName);
		return;
	}

	if(!CryptAcquireContext(&hCryptProv, NULL, szProviderName, g_CspInfo[i].nCspType, CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("ModifyAlgorithm:CryptAcquireContext() failed", dwErr);
		free(szProviderName);
		return;
	}

	free(szProviderName);
	
	// Enum the supported algorithms
	for(i = 0; ; i++)
	{
		if(i == 0)
			dwFlags = CRYPT_FIRST;
		else
			dwFlags = 0;

		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, NULL, &cbData, dwFlags))
			break;

		pbData = (BYTE *)malloc(cbData);
		if(!pbData)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("ModifyAlgorithm() : Out of memory", 0);
			return;
		}

		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, pbData, &cbData, dwFlags))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ModifyAlgorithm:CryptGetProvParam() failed", dwErr);
			break;
		}

		ptr = pbData;

		Algid = *(ALG_ID *)ptr;
		ptr += sizeof(ALG_ID);
		dwBits = *(DWORD *)ptr;
		ptr += sizeof(DWORD);

		dwNameLen = *(DWORD *)ptr;    

		ptr += sizeof(DWORD);
		strncpy(szAlgName, (const char *)ptr, dwNameLen);
		wsprintf(szAlgorithm, "%s-%d bits", szAlgName, dwBits);

		// Determine the algorithm type.    
		switch(GET_ALG_CLASS(Algid)) 
		{
			case ALG_CLASS_DATA_ENCRYPT:
			{
				if(bEncrypt)
					if(IsAlgSupported(szAlgorithm, 1))
					{
						if(!strnicmp(szAlgorithm, "RC2", 3))
							lstrcpy(szEncrAlg, szAlgorithm);

						if(!lstrcmpi(szEncrAlg, lpAlg))	// Alg in policy is supported by curr CSP
							bPresent = TRUE;
					}
			}

				break;

			case ALG_CLASS_HASH:
			{
				if(!bEncrypt)
					if(IsAlgSupported(szAlgName, 0))
					{
						if(!lstrcmpi(szAlgName, "SHA-1"))
							lstrcpy(szHashAlg, szAlgName);

						if(!lstrcmpi(szHashAlg, lpAlg))	// Alg in policy is supported by curr CSP
							bPresent = TRUE;
					}
			}
				break;
		}

		free(pbData);
	}

	CryptReleaseContext(hCryptProv, 0);

	if(!bPresent)
	{
		// modify the global policy to one of the valid Encr/Hash algs
		if(bEncrypt)
			lstrcpy(g_LocalPolicy.EncryptionAlg, szEncrAlg);
		else
			lstrcpy(g_LocalPolicy.HashAlg, szHashAlg);
	}

	return;
}




void GetCertSubjectDisplayName(PCCERT_CONTEXT pCertCxt, TCHAR *lpszDisplayName)
{
	DWORD dwSize = 0, dwErr;
	TCHAR *lpszSubjectDN = NULL, *lpszFormattedDN;
	CERT_NAME_BLOB NameBlob = pCertCxt->pCertInfo->Subject;

    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob, CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, 
						   NULL, dwSize);
    if(dwSize <= 1)
    {
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetCertSubjectDisplayName:CertNameToStr() failed", dwErr);
		strcpy(lpszDisplayName, "<None>");
        return;
    }

    lpszSubjectDN = (TCHAR*)malloc((dwSize + 1) * sizeof(TCHAR));
    if(!lpszSubjectDN)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetCertSubjectDisplayName() : Out of memory", 0);
		strcpy(lpszDisplayName, "<None>");
		return;
	}

    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob, CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG,
						   lpszSubjectDN, dwSize);
    if(dwSize <= 1)
    {
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetCertSubjectDisplayName:CertNameToStr() failed", dwErr);
		strcpy(lpszDisplayName, "<None>");
        return;
    }

	lpszFormattedDN = (TCHAR*) malloc(sizeof(TCHAR)*(strlen(lpszSubjectDN) + 1));
	if(!lpszFormattedDN)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetCertSubjectDisplayName() : Out of memory", 0);
		strcpy(lpszDisplayName, "<None>");
		return;
	}

	// Get the CN at the leaf
	TCHAR *pOldDisplayName = NULL;
	TCHAR *pDisplayName = strstr(lpszSubjectDN, "CN=");
	while(pDisplayName)
	{
		pOldDisplayName = pDisplayName;
		pDisplayName = strstr(pDisplayName + 3, "CN=");
	}
	
	if(pOldDisplayName)
	{
		pOldDisplayName = strchr(pOldDisplayName, '=');
		lstrcpy(lpszDisplayName, pOldDisplayName + 1);
		pOldDisplayName = strchr(lpszDisplayName, ';');
		if(pOldDisplayName)
			*pOldDisplayName = '\0';

		// Remove the quotes if present at start and end as in case of certs issued by the Exchange server
		if(lpszDisplayName[0] == '"')
		{
			for(int i = 0; i < lstrlen(lpszDisplayName) - 2; i++)
				lpszDisplayName[i] = lpszDisplayName[i + 1];

			lpszDisplayName[i] = '\0';
		}
	}

	free(lpszFormattedDN);
	free(lpszSubjectDN);
	return;
}



// Dialog procedure for the "Animate dialog" dialog
BOOL APIENTRY AnimateDlg(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	static HWND hWndAnimate;

    switch (message)
    {
        case WM_INITDIALOG:    
		{
			RECT rc, rc2;
			GetClientRect(hDlg, &rc);

			HWND hWndParent = GetParent(hDlg);
			GetWindowRect(hWndParent, &rc2);

			MoveWindow(hDlg, rc2.left, rc2.top + 40, rc.right, rc.bottom, FALSE);

			hWndAnimate = CreateWindowEx(0, ANIMATE_CLASS, "", WS_CHILD | ACS_CENTER | WS_VISIBLE | ACS_TRANSPARENT,
						   0, 0, rc.right, rc.bottom/3, hDlg, (HMENU)ID_ANIMATE, g_hInst, 0);

			if(hWndAnimate)
				SetWindowPos(hWndAnimate, NULL, 0, 0, rc.right, rc.bottom/3,
							 SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE|SWP_SHOWWINDOW);

			Animate_Open(hWndAnimate, MAKEINTRESOURCE(ID_FILECOPY_AVI));
			Animate_Play(hWndAnimate, 0, -1, -1);
            return (TRUE);
		}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDCANCEL:
					g_bCancelled = TRUE;
					return TRUE;
			}

			break;
    }

    return FALSE;
}


BOOL APIENTRY DlgEncrDecr(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:    
            return TRUE;
    }

    return FALSE;
}




// Dialog procedure for the "Certificate life cycle management" dialog
BOOL APIENTRY CertMgmt(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	HWND hWnd;

    switch (message)
    {
        case WM_INITDIALOG:    
		{
			// Disable "Recover DigId for now
			hWnd = GetDlgItem(hDlg, IDB_RECOVER_DIGID);
			EnableWindow(hWnd, FALSE);

			hWnd = GetDlgItem(hDlg, IDB_RENEW_DIGID);
			EnableWindow(hWnd, FALSE);

            return (TRUE);
		}

		case WM_COMMAND:
		{
			TCHAR szTempUrl[MAX_MSG_LEN];
			WCHAR wcUrl[MAX_MSG_LEN];

			lstrcpy(szTempUrl, g_LocalPolicy.szRemoteHost);
			if(lstrcmpi(szTempUrl, "https://digitalid.verisign.com/client/index.html") != 0)
			{
				SmartAppendFrontslash(szTempUrl);
				lstrcat(szTempUrl, "VSApps/");
				lstrcat(szTempUrl, DIGID_CENTER);
			}

			MultiByteToWideChar(CP_ACP, 0, szTempUrl, lstrlen(szTempUrl) + 1, wcUrl, sizeof(wcUrl));

			switch(LOWORD(wParam))
			{
				case IDB_GET_DIGID:    
					HlinkSimpleNavigateToString(wcUrl, NULL, NULL, NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
					return TRUE;

				case IDB_REVOKE_DIGID:
					HlinkSimpleNavigateToString(wcUrl, NULL, NULL, NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
					return TRUE;

				case IDB_RENEW_DIGID:
					//DoCertificateRenewal(1, 1);
					return TRUE;

				case IDB_RECOVER_DIGID:
					return TRUE;
			}
		}

			break;

		 case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
				case PSN_HELP:
				{
					ShowHelp("fet_digitalid.htm");
					return TRUE;
				}
        }
    }

    return FALSE;
}


// Dialog procedure for the "Filter" dialog
BOOL APIENTRY FilterProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	static dwExclusionAttr = 0;
	static HWND hWndList;

    switch (message)
    {
        case WM_INITDIALOG:
		{
			HWND hWndFilter = GetDlgItem(hDlg, IDC_FILTER);
			SendMessage(hWndFilter, CB_ADDSTRING, 0, (LPARAM)"with extension");
			SendMessage(hWndFilter, CB_ADDSTRING, 0, (LPARAM)"in folders");
			SendMessage(hWndFilter, CB_ADDSTRING, 0, (LPARAM)"having attributes");
			SendMessage(hWndFilter, CB_SELECTSTRING, -1, (LPARAM)"with extension");

			// Create a list view 
			DWORD dwStyle;
			dwStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
					  LVS_SORTASCENDING | LVS_LIST; 

			hWndList = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, NULL, dwStyle,
							120, 130, 125, 80, hDlg, (HMENU)ID_LISTVIEW_FILTER_ITEMS, g_hInst, NULL);

			LPCTSTR pItem;
			LVITEM lvItem;
			pItem = g_ExtensionList->GetNextItem(NULL);
			while(pItem)
			{
				ZeroMemory(&lvItem, sizeof(lvItem));

				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = 0;
				lvItem.pszText = (LPSTR)pItem;
				ListView_InsertItem(hWndList, &lvItem);

				pItem = g_ExtensionList->GetNextItem(pItem);
			}

			if(g_LocalPolicy.bFilterForced)
			{	
				HWND hWndButton = GetDlgItem(hDlg, IDB_ADD);
				EnableWindow(hWndButton, FALSE);

				hWndButton = GetDlgItem(hDlg, IDB_REMOVE);
				EnableWindow(hWndButton, FALSE);

			    EnableWindow(hWndList, FALSE);
			}

			return TRUE;
		}

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDB_REMOVE:
				{
					UINT nSelected = ListView_GetSelectedCount(hWndList);

					if(nSelected)
					{
						UINT i, nCurSel;
						LVITEM lvItem;
						TCHAR szTemp[MAX_MSG_LEN], szCurSel[MAX_MSG_LEN];
						HWND hWndFilter;
						CSList *pSelList = NULL;

						hWndFilter = GetDlgItem(hDlg, IDC_FILTER);
						nCurSel = SendMessage(hWndFilter, CB_GETCURSEL, 0, 0);
						SendMessage(hWndFilter, CB_GETLBTEXT, nCurSel, (LPARAM)szCurSel);

						ZeroMemory(&lvItem, sizeof(lvItem));
						lvItem.mask = LVIF_STATE | LVIF_TEXT;
						lvItem.stateMask = LVIS_SELECTED;
						lvItem.iItem = 0;
						lvItem.iSubItem = 0;
						lvItem.pszText = szTemp;
						lvItem.cchTextMax = MAX_MSG_LEN;
						i = 0;

						if(!lstrcmpi(szCurSel, "with Extension"))
							pSelList = g_ExtensionList;
						else
							pSelList = g_FoldersList;

						while(ListView_GetItem(hWndList, &lvItem) && (i < nSelected))
						{
							if(lvItem.state & LVIS_SELECTED)
							{
								ListView_DeleteItem(hWndList, lvItem.iItem);
								pSelList->RemoveFromList(szTemp);
								i++;
							}
							else
								lvItem.iItem++;
						}
					}
					else
						MessageBox(hDlg, "Please make a selection.", "Safe", MB_OK | MB_ICONERROR);

					return TRUE;
				}
					
				case IDB_ADD:
				{
					switch(HIWORD(wParam))
					{
						case BN_CLICKED:
						{
							TCHAR szCurSel[MAX_MSG_LEN];
							LVITEM lvItem;

							HWND hWndFilter = GetDlgItem(hDlg, IDC_FILTER);
							
							UINT nCurSel = SendMessage(hWndFilter, CB_GETCURSEL, 0, 0);
							SendMessage(hWndFilter, CB_GETLBTEXT, nCurSel, (LPARAM)szCurSel);

							if(!lstrcmpi(szCurSel, "with Extension"))
								DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_EXT), hDlg, (DLGPROC)FilterExtProc, (LONG)hWndList);
							else
								if(!lstrcmpi(szCurSel, "in Folders"))
								{
									TCHAR szDir[MAX_PATH_LEN], szDispText[MAX_MSG_LEN];
									lstrcpy(szDispText, "Select the Folder");

									if(GetDirectory(szDir, szDispText))
									{
										_strlwr(szDir);

										LVFINDINFO lvfi;
										memset(&lvfi, 0, sizeof(LVFINDINFO));

										lvfi.flags = LVFI_STRING;
										lvfi.psz = szDir;

										if(ListView_FindItem(hWndList, -1, &lvfi) == -1)
										{
											ZeroMemory(&lvItem, sizeof(lvItem));

											lvItem.mask = LVIF_TEXT;
											lvItem.iItem = 0;
											lvItem.pszText = (LPSTR)szDir;
											ListView_InsertItem(hWndList, &lvItem);

											if(szDir[lstrlen(szDir) - 1] == '\\')
												szDir[lstrlen(szDir) - 1] = '\0';

											g_FoldersList->AddToList(szDir);
										}
									}
								}
								
							return TRUE;
						}
					}
				}
					break;

				case IDC_FILTER:
				{
					switch(HIWORD(wParam))
					{
						case CBN_SELCHANGE:
						{
							TCHAR szCurSel[MAX_MSG_LEN];
							LPCTSTR pItem;
							LVITEM lvItem;

							HWND hWndFilter = GetDlgItem(hDlg, IDC_FILTER);

							UINT nCurSel = SendMessage(hWndFilter, CB_GETCURSEL, 0, 0);
							SendMessage(hWndFilter, CB_GETLBTEXT, nCurSel, (LPARAM)szCurSel);
							
							ListView_DeleteAllItems(hWndList);

							if(!lstrcmpi(szCurSel, "with Extension"))
							{
								DWORD dwStyle = ListView_GetExtendedListViewStyle(hWndList);
								dwStyle &= ~(LVS_EX_CHECKBOXES);
								ListView_SetExtendedListViewStyle(hWndList, dwStyle);

								pItem = g_ExtensionList->GetNextItem(NULL);
								while(pItem)
								{
									ZeroMemory(&lvItem, sizeof(lvItem));

									lvItem.mask = LVIF_TEXT;
									lvItem.iItem = 0;
									lvItem.pszText = (LPSTR)pItem;
									ListView_InsertItem(hWndList, &lvItem);

									pItem = g_ExtensionList->GetNextItem(pItem);
								}

								HWND hWndButton;
								hWndButton = GetDlgItem(hDlg, IDB_ADD);
								ShowWindow(hWndButton, SW_SHOW);

								hWndButton = GetDlgItem(hDlg, IDB_REMOVE);
								ShowWindow(hWndButton, SW_SHOW);
							}
							else
								if(!lstrcmpi(szCurSel, "in Folders"))
								{
									DWORD dwStyle = ListView_GetExtendedListViewStyle(hWndList);
									dwStyle &= ~(LVS_EX_CHECKBOXES);
									ListView_SetExtendedListViewStyle(hWndList, dwStyle);

									pItem = g_FoldersList->GetNextItem(NULL);
									while(pItem)
									{
										ZeroMemory(&lvItem, sizeof(lvItem));

										lvItem.mask = LVIF_TEXT;
										lvItem.iItem = 0;
										lvItem.pszText = (LPSTR)pItem;
										ListView_InsertItem(hWndList, &lvItem);

										pItem = g_FoldersList->GetNextItem(pItem);
									}

									HWND hWndButton;
									hWndButton = GetDlgItem(hDlg, IDB_ADD);
									ShowWindow(hWndButton, SW_SHOW);

									hWndButton = GetDlgItem(hDlg, IDB_REMOVE);
									ShowWindow(hWndButton, SW_SHOW);
								}
								else
								{
									ListView_SetExtendedListViewStyle(hWndList, LVS_EX_CHECKBOXES);

									ZeroMemory(&lvItem, sizeof(lvItem));
									lvItem.mask = LVIF_TEXT;
									lvItem.iItem = 0;
									lvItem.pszText = (LPSTR)"Hidden";
									ListView_InsertItem(hWndList, &lvItem);

									ZeroMemory(&lvItem, sizeof(lvItem));
									lvItem.mask = LVIF_TEXT;
									lvItem.iItem = 1;
									lvItem.pszText = (LPSTR)"Read Only";
									ListView_InsertItem(hWndList, &lvItem);

									ZeroMemory(&lvItem, sizeof(lvItem));
									lvItem.mask = LVIF_TEXT;
									lvItem.iItem = 2;
									lvItem.pszText = (LPSTR)"System";
									ListView_InsertItem(hWndList, &lvItem);

									if(g_ExclusionAttr & ATTR_HIDDEN)
										ListView_SetItemState(hWndList, 0,
											INDEXTOSTATEIMAGEMASK((TRUE) + 1), LVIS_STATEIMAGEMASK);

									if(g_ExclusionAttr & ATTR_READ_ONLY)
										ListView_SetItemState(hWndList, 1,
											INDEXTOSTATEIMAGEMASK((TRUE) + 1), LVIS_STATEIMAGEMASK);

									if(g_ExclusionAttr & ATTR_SYSTEM)
										ListView_SetItemState(hWndList, 2,
											INDEXTOSTATEIMAGEMASK((TRUE) + 1), LVIS_STATEIMAGEMASK);

									HWND hWndButton;
									hWndButton = GetDlgItem(hDlg, IDB_ADD);
									ShowWindow(hWndButton, SW_HIDE);

									hWndButton = GetDlgItem(hDlg, IDB_REMOVE);
									ShowWindow(hWndButton, SW_HIDE);
								}

							return TRUE;
						}

						case CBN_SETFOCUS:
						{
							TCHAR szCurSel[MAX_MSG_LEN];
							HWND hWndFilter = GetDlgItem(hDlg, IDC_FILTER);
							UINT nCurSel = SendMessage(hWndFilter, CB_GETCURSEL, 0, 0);
							SendMessage(hWndFilter, CB_GETLBTEXT, nCurSel, (LPARAM)szCurSel);
							
							if(!lstrcmpi(szCurSel, "having Attributes"))
							{
								UINT nState;
								g_ExclusionAttr = 0;

								nState = ListView_GetCheckState(hWndList, 0);
								g_ExclusionAttr |= nState;

								nState = ListView_GetCheckState(hWndList, 1);
								nState = nState << 1;
								g_ExclusionAttr |= nState;
								
								nState = ListView_GetCheckState(hWndList, 2);
								nState = nState << 2;
								g_ExclusionAttr |= nState;
							}
							
							return TRUE;
						}
					}
				}
					break;

			}

			break;


		case WM_NOTIFY:
            switch (((NMHDR FAR *) lParam)->code) 
            {
                case PSN_APPLY:
				{
					TCHAR szCurSel[MAX_MSG_LEN];
					HWND hWndFilter = GetDlgItem(hDlg, IDC_FILTER);
					UINT nCurSel = SendMessage(hWndFilter, CB_GETCURSEL, 0, 0);
					SendMessage(hWndFilter, CB_GETLBTEXT, nCurSel, (LPARAM)szCurSel);
					
					if(!lstrcmpi(szCurSel, "having Attributes"))
					{
						UINT nState;
						g_ExclusionAttr = 0;

						nState = ListView_GetCheckState(hWndList, 0);
						g_ExclusionAttr |= nState;

						nState = ListView_GetCheckState(hWndList, 1);
						nState = nState << 1;
						g_ExclusionAttr |= nState;
						
						nState = ListView_GetCheckState(hWndList, 2);
						nState = nState << 2;
						g_ExclusionAttr |= nState;
					}
				}

                case PSN_KILLACTIVE:
                    SetWindowLong(hDlg, DWL_MSGRESULT, FALSE);
                    return TRUE;

				case PSN_HELP:
				{
					ShowHelp("fet_filters.htm");
					return TRUE;
				}
        }
    }

    return FALSE;
}



// Dialog procedure for the "Filter Extensions" dialog
BOOL APIENTRY FilterExtProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	static HWND hWndList;

    switch (message)
    {
        case WM_INITDIALOG:
		{
			hWndList = (HWND)lParam;
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDOK:    
				{
					TCHAR szExt[MAX_MSG_LEN], *pStr = NULL;
					LVITEM lvItem;

					GetDlgItemText(hDlg, IDE_EXT, szExt, MAX_MSG_LEN);

					pStr = strrchr(szExt, '.');
					if(!pStr)
					{
						MessageBox(hDlg, "Invalid format for extension.", "Safe", MB_OK | MB_ICONERROR);
						return FALSE;
					}

					_strlwr(pStr);

					LVFINDINFO lvfi;
					memset(&lvfi, 0, sizeof(LVFINDINFO));

					lvfi.flags = LVFI_STRING;
					lvfi.psz = pStr;

					if(ListView_FindItem(hWndList, -1, &lvfi) == -1)
					{
						ZeroMemory(&lvItem, sizeof(lvItem));
						lvItem.mask = LVIF_TEXT;
						lvItem.iItem = 0;
						lvItem.pszText = (LPSTR)pStr;
						ListView_InsertItem(hWndList, &lvItem);
					}

					g_ExtensionList->AddToList((LPCTSTR)pStr);
					
					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case IDCANCEL:
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
			}
		}
			break;
	}

	return FALSE;
}

/*
// Dialog procedure for the "Password accept" dialog
BOOL APIENTRY PasswdAcceptProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
		{
			int cxScreen, cyScreen;
			cxScreen = GetSystemMetrics(SM_CXSCREEN);
			cyScreen = GetSystemMetrics(SM_CYSCREEN);

			// Center the dialog box
			HWND hWndParent = GetParent(hDlg);
			RECT rcChild, rcParent;
			INT iWidth, iHeight, xPos, yPos;
			POINT ptScreen;

			GetClientRect(hWndParent, &rcParent);

			GetWindowRect(hDlg, &rcChild);
			iWidth = rcChild.right - rcChild.left;
			iHeight = rcChild.bottom - rcChild.top;

			xPos = (rcParent.right - iWidth)/2;
			yPos = (rcParent.bottom - iHeight)/2;

			ptScreen.x = xPos;
			ptScreen.y = yPos;
			ClientToScreen(hWndParent, &ptScreen);

			if(ptScreen.x >= (cxScreen - iWidth))
				ptScreen.x = cxScreen - iWidth;
			else
				if(ptScreen.x < 0)
					ptScreen.x = 0;

			if(ptScreen.y >= (cyScreen - iHeight))
				ptScreen.y = cyScreen - iHeight;
			else
				if(ptScreen.y < 0)
					ptScreen.y = 0;


			MoveWindow(hDlg, ptScreen.x, ptScreen.y, iWidth, iHeight, TRUE);

			HWND hWnd = GetDlgItem(hDlg, IDC_DISP_TXT);
			SetWindowText(hWnd, (LPCTSTR)lParam);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDOK:    
				{
					TCHAR szPassword[MAX_PATH];
					GetDlgItemText(hDlg, IDE_PASSWD, szPassword, MAX_PATH);
					PBYTE pbHash = NULL;
					DWORD dwLen = 0;

					dwLen = HashData((PBYTE)szPassword, 
							   		 lstrlen(szPassword), &pbHash);

					memcpy(g_PasswdHash.pbHash, pbHash, dwLen);
					g_PasswdHash.dwLen = dwLen;

					free(pbHash);
	
					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}
*/

/*
// Dialog procedure for the "Safe unlock" dialog
BOOL APIENTRY SafeUnlockProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
		{
			int cxScreen, cyScreen;
			cxScreen = GetSystemMetrics(SM_CXSCREEN);
			cyScreen = GetSystemMetrics(SM_CYSCREEN);

			// Center the dialog box
			HWND hWndParent = GetParent(hDlg);
			if(hWndParent == NULL)
				hWndParent = GetDesktopWindow();

			RECT rcChild, rcParent;
			INT iWidth, iHeight, xPos, yPos;
			POINT ptScreen;

			GetClientRect(hWndParent, &rcParent);

			GetWindowRect(hDlg, &rcChild);
			iWidth = rcChild.right - rcChild.left;
			iHeight = rcChild.bottom - rcChild.top;

			xPos = (rcParent.right - iWidth)/2;
			yPos = (rcParent.bottom - iHeight)/2;

			ptScreen.x = xPos;
			ptScreen.y = yPos;
			ClientToScreen(hWndParent, &ptScreen);

			if(ptScreen.x >= (cxScreen - iWidth))
				ptScreen.x = cxScreen - iWidth;
			else
				if(ptScreen.x < 0)
					ptScreen.x = 0;

			if(ptScreen.y >= (cyScreen - iHeight))
				ptScreen.y = cyScreen - iHeight;
			else
				if(ptScreen.y < 0)
					ptScreen.y = 0;

			MoveWindow(hDlg, ptScreen.x, ptScreen.y, iWidth, iHeight, TRUE);

			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDOK:    
				{
					TCHAR szPassword[MAX_PATH];
					GetDlgItemText(hDlg, IDE_PASSWD, szPassword, MAX_PATH);
					PBYTE pbHash = NULL;
					DWORD dwLen = 0;

					dwLen = HashData((PBYTE)szPassword, 
							   		 lstrlen(szPassword), &pbHash);

					memcpy(g_PasswdHash.pbHash, pbHash, dwLen);
					g_PasswdHash.dwLen = dwLen;

					free(pbHash);
	
					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}
*/

/*
// Dialog procedure for the "Password verify" dialog
BOOL APIENTRY PasswdVerifyProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
		{
			int cxScreen, cyScreen;
			cxScreen = GetSystemMetrics(SM_CXSCREEN);
			cyScreen = GetSystemMetrics(SM_CYSCREEN);

			// Center the dialog box
			HWND hWndParent = GetParent(hDlg);
			RECT rcChild, rcParent;
			INT iWidth, iHeight, xPos, yPos;
			POINT ptScreen;

			GetClientRect(hWndParent, &rcParent);

			GetWindowRect(hDlg, &rcChild);
			iWidth = rcChild.right - rcChild.left;
			iHeight = rcChild.bottom - rcChild.top;

			xPos = (rcParent.right - iWidth)/2;
			yPos = (rcParent.bottom - iHeight)/2;

			ptScreen.x = xPos;
			ptScreen.y = yPos;
			ClientToScreen(hWndParent, &ptScreen);

			if(ptScreen.x >= (cxScreen - iWidth))
				ptScreen.x = cxScreen - iWidth;
			else
				if(ptScreen.x < 0)
					ptScreen.x = 0;

			if(ptScreen.y >= (cyScreen - iHeight))
				ptScreen.y = cyScreen - iHeight;
			else
				if(ptScreen.y < 0)
					ptScreen.y = 0;

			MoveWindow(hDlg, ptScreen.x, ptScreen.y, iWidth, iHeight, TRUE);

			SetDlgItemText(hDlg, IDC_DISP_TXT, (LPCTSTR)lParam);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDOK:    
				{
					TCHAR szPassword[MAX_PATH];
					GetDlgItemText(hDlg, IDE_PASSWD, szPassword, MAX_PATH);
					PBYTE pbHash = NULL;
					DWORD dwLen = 0;

					dwLen = HashData((PBYTE)szPassword, 
									 lstrlen(szPassword), &pbHash);

					if(!memcmp(pbHash, g_PasswdHash.pbHash, dwLen))
					{
						free(pbHash);
						EndDialog(hDlg, IDOK);
					}
					else
					{
						DisplayMessage(hDlg, IDS_INVALID_PASSWD, MB_OK | MB_ICONERROR);
						free(pbHash);
						return FALSE;
					}
					
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}*/


/*
// Dialog procedure for the "New Password" dialog
BOOL APIENTRY NewPasswordProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	TCHAR szRecoveryFile[MAX_PATH], *pExtension = NULL;

    switch (message)
    {
        case WM_INITDIALOG:
		{
			int cxScreen, cyScreen;
			cxScreen = GetSystemMetrics(SM_CXSCREEN);
			cyScreen = GetSystemMetrics(SM_CYSCREEN);

			// Set the display text. This proc can be called 
			// either first time passwd is setup or after a 
			// recover passwd operation
			TCHAR szTemp[MAX_PATH];
			LoadString(g_hInst, lParam, szTemp, MAX_PATH);
			SetDlgItemText(hDlg, IDC_DISP_TEXT, szTemp);

			// Set default value for the recovery file
			SetDlgItemText(hDlg, IDE_RECOVERY_FILE, g_szTokenFile);

			// Center the dialog box
			HWND hWndParent = GetParent(hDlg);
			RECT rcChild, rcParent;
			INT iWidth, iHeight, xPos, yPos;
			POINT ptScreen;

			GetClientRect(hWndParent, &rcParent);

			GetWindowRect(hDlg, &rcChild);
			iWidth = rcChild.right - rcChild.left;
			iHeight = rcChild.bottom - rcChild.top;

			xPos = (rcParent.right - iWidth)/2;
			yPos = (rcParent.bottom - iHeight)/2;

			ptScreen.x = xPos;
			ptScreen.y = yPos;
			ClientToScreen(hWndParent, &ptScreen);

			if(ptScreen.x >= (cxScreen - iWidth))
				ptScreen.x = cxScreen - iWidth;
			else
				if(ptScreen.x < 0)
					ptScreen.x = 0;

			if(ptScreen.y >= (cyScreen - iHeight))
				ptScreen.y = cyScreen - iHeight;
			else
				if(ptScreen.y < 0)
					ptScreen.y = 0;

			MoveWindow(hDlg, ptScreen.x, ptScreen.y, iWidth, iHeight, TRUE);

			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case ID_BROWSE:
				{
					TCHAR szFilter[MAX_PATH], szTitle[MAX_PATH];
					LoadString(g_hInst, IDS_RECOVERY_FILE, szFilter, MAX_PATH);
					lstrcat(szFilter, " (*.req)");
					lstrcpy(&szFilter[lstrlen(szFilter) + 1], "*.req");
					szFilter[lstrlen(szFilter) + 1 + 6] = '\0';

					LoadString(g_hInst, IDS_SEL_RECOVERY_FILE, szTitle, MAX_PATH);

					OPENFILENAME ofn;
					memset(&ofn, 0, sizeof(OPENFILENAME));
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner	= hDlg;
					ofn.hInstance	= NULL;
					ofn.lpstrFilter	= szFilter;
					ofn.nFilterIndex = 1;
					ofn.lpstrFile	= szRecoveryFile;
					ofn.nMaxFile	= sizeof(szRecoveryFile);
					ofn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK |
								OFN_OVERWRITEPROMPT | OFN_NODEREFERENCELINKS | OFN_NONETWORKBUTTON;
					szRecoveryFile[0] = '\0';
					ofn.lpstrTitle	= szTitle;
					ofn.lpfnHook    = (LPOFNHOOKPROC)SelectHookProc;

					if(GetOpenFileName(&ofn))
						SetDlgItemText(hDlg, IDE_RECOVERY_FILE, szRecoveryFile);
										
					return TRUE;
				}

				case IDOK:    
				{
					HWND hWnd;
					TCHAR szPassword[MAX_PATH], szConfirmPasswd[MAX_PATH];
					GetDlgItemText(hDlg, IDE_PASSWD, szPassword, MAX_PATH);

					if(szPassword[0] == '\0')
					{
						DisplayMessage(hDlg, IDS_ENTER_PASSWD, MB_OK | MB_ICONERROR);
						hWnd = GetDlgItem(hDlg, IDE_PASSWD);
						SetFocus(hWnd);
						return FALSE;
					}

					GetDlgItemText(hDlg, IDE_CONFIRM_PASSWD, szConfirmPasswd, MAX_PATH);

					if(lstrcmpi(szPassword, szConfirmPasswd) != 0)
					{
						DisplayMessage(GetFocus(), IDS_PASSWD_MISMATCH, MB_OK | MB_ICONERROR);
						hWnd = GetDlgItem(hDlg, IDE_CONFIRM_PASSWD);
						SetFocus(hWnd);
						return FALSE;
					}

					// Get the password hash
					PBYTE pbHash = NULL;
					DWORD dwLen = 0;

					dwLen = HashData((PBYTE)szPassword, 
					   			     lstrlen(szPassword), &pbHash);
					memcpy(g_PasswdHash.pbHash, pbHash, dwLen);
					g_PasswdHash.dwLen = dwLen;

					free(pbHash);

					// Check if need to save password token
					GetDlgItemText(hDlg, IDE_RECOVERY_FILE, szRecoveryFile, sizeof(szRecoveryFile));
					if(szRecoveryFile[0] != '\0')
					{
						if(CreatePasswordFile())
						{
							// If the user chooses the default filename
							// then no need to copy
							if(lstrcmpi(g_szTokenFile, szRecoveryFile))
							{
								// Append the '.req' extension to the recovery file if not already present
								pExtension = strchr(szRecoveryFile, '.');
								if(pExtension == NULL)
									lstrcat(szRecoveryFile, ".req");
								else
								{
									if(lstrcmpi(pExtension, ".req") != NULL)
										lstrcat(szRecoveryFile, ".req");
								}

								if(!CopyFile(g_szTokenFile, szRecoveryFile, FALSE))
								{
									TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH];
									DWORD dwError = GetLastError();
									LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_PATH);
									wsprintf(szFmt, szMsg, g_szTokenFile, szRecoveryFile);
									MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
									wsprintf(szMsg, "NewPasswordProc() : Error overwritting token file \'%s\'", szRecoveryFile);
									LogErrorMessage(szMsg, dwError);
								}
							}

							// Save location of recovery file
							// in the registry
							HKEY hKey;
							DWORD dwDisp;
							if(RegCreateKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
											  KEY_WRITE, NULL, &hKey, &dwDisp) == ERROR_SUCCESS)
							{
								RegSetValueEx(hKey, "RecoveryFile", 0, REG_SZ, (LPBYTE)szRecoveryFile,
											  lstrlen(szRecoveryFile) + 1);
								RegCloseKey(hKey);
							}
						}
					}

					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case ID_HELP:
				{
					ShowHelp("fet_pwdhelp.htm");
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}
*/


BOOL IsAlgSupported(LPCTSTR lpszAlg, BOOL bEncrypt)
{
	if(bEncrypt)
	{
		if(!lstrcmpi(lpszAlg, "RC2-40 bits") || !lstrcmpi(lpszAlg, "RC2-56 bits") ||
		   !lstrcmpi(lpszAlg, "RC2-128 bits") || !strnicmp(lpszAlg, "RC4", 3) ||
		   //!lstrcmpi(lpszAlg, "RC5") ||
		   !lstrcmpi(lpszAlg, "DES-56 bits") || !lstrcmpi(lpszAlg, "3DES-168 bits") 
		  )
		  return TRUE;
	}
	else
	{
		if(!lstrcmpi(lpszAlg, "SHA-1") ||
		   //!lstrcmpi(lpszAlg, "MD2") ||	// removed MD2, CryptMsgUpdate() is failing for it for Win95
		   !lstrcmpi(lpszAlg, "MD4") || !lstrcmpi(lpszAlg, "MD5")
		  )
		  return TRUE;
	}

	return FALSE;
}


void AddScreenSaver(HWND hDlg, LPCTSTR lpszDir, LPCTSTR lpszActiveSrnPath)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind = NULL;
	TCHAR szFilePath[MAX_PATH_LEN], szScreenSaver[MAX_PATH_LEN], szActiveScrnLongPath[MAX_PATH_LEN];
	TCHAR *lpDesc = NULL, *lpOpenGL = NULL, szDesc[MAX_MSG_LEN], szTemp[MAX_MSG_LEN];
	DWORD dwInput = 0, dwSize = 0, dwErr = 0;
	UINT uLen = 0;
	void *pFileVersion = NULL;

	// Get long name of 'lpszActiveSrnPath'
	lstrcpy(szActiveScrnLongPath, lpszActiveSrnPath);
	hFind = FindFirstFile(szActiveScrnLongPath, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		lpDesc = strrchr(szActiveScrnLongPath, '\\');
		lstrcpy(lpDesc + 1, wfd.cFileName);
		FindClose(hFind);
	}

	HWND hScrSvr = GetDlgItem(hDlg, IDC_SCREEN_SAVER);
	
	lstrcpy(szFilePath, lpszDir);
	lstrcat(szFilePath, "\\*.scr");

	hFind = FindFirstFile(szFilePath, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			lstrcpy(szScreenSaver, lpszDir);
			lstrcat(szScreenSaver, "\\");
			lstrcat(szScreenSaver, wfd.cFileName);

			dwSize = GetFileVersionInfoSize(szScreenSaver, &dwInput);

			if(dwSize)
			{
				pFileVersion = malloc(dwSize);
				if(!pFileVersion)
				{
					DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
					LogErrorMessage("AddScreenSaver() : Out of memory", 0);
					break;
				}

				if(!GetFileVersionInfo(szScreenSaver, 0, dwSize, pFileVersion))
				{
					dwErr = GetLastError();
					wsprintf(szTemp, "AddScreenSaver:GetFileVersionInfo() failed for \'%s\'", szScreenSaver);
					LogErrorMessage(szTemp, dwErr);
					free(pFileVersion);
					continue;
				}

				lpDesc = NULL;
				VerQueryValue(pFileVersion, TEXT("\\StringFileInfo\\040904B0\\FileDescription"), 
							  (void **)&lpDesc, &uLen); 

				if(!lpDesc)
					VerQueryValue(pFileVersion, TEXT("\\StringFileInfo\\040904E4\\FileDescription"),
								  (void **)&lpDesc, &uLen); 

				if(lpDesc)
				{
					lpOpenGL = strstr(lpDesc, "OpenGL");
					if(lpDesc == lpOpenGL)
						lstrcpy(szDesc, lpDesc + 7);
					else
					{
						for(int j = 0, i = 0; i < lstrlen(lpDesc); i++)
						{
							if(lpDesc == lpOpenGL)
								i += 7;

							szDesc[j++] = lpDesc[i];
						}	

						szDesc[j] = '\0';
					}

					int Sel = SendMessage(hScrSvr, CB_ADDSTRING, 0, (LPARAM)szDesc);

					if(!lstrcmpi(szActiveScrnLongPath, szScreenSaver))
						SendMessage(hScrSvr, CB_SETCURSEL, Sel, 0);
				}
				else
				{	
					wsprintf(szTemp, "AddScreenSaver:Version information not present for '%s'", szScreenSaver);
					LogErrorMessage(szTemp, 0);
				}

				free(pFileVersion);
			} // if(dwSize)
			else
			{
				dwErr = GetLastError();
				wsprintf(szTemp, "AddScreenSaver:GetFileVersionInfoSize() failed for '%s'", szScreenSaver);
				LogErrorMessage(szTemp, dwErr);
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

}



BOOL GetScrnSvrFile(LPCTSTR lpszSelectedScrnSvr, LPCSTR lpszSrchDir, LPTSTR lpszScrnSvrFile)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind = NULL;
	TCHAR szFilePath[MAX_PATH_LEN], szScreenSaver[MAX_PATH_LEN];
	TCHAR *lpDesc = NULL, *lpOpenGL = NULL, szDesc[MAX_MSG_LEN], szTemp[MAX_MSG_LEN];
	DWORD dwInput = 0, dwSize = 0, dwErr;
	UINT uLen = 0;
	void *pFileVersion = NULL;
	BOOL retVal = FALSE;

	lstrcpy(szFilePath, lpszSrchDir);
	lstrcat(szFilePath, "\\*.scr");

	hFind = FindFirstFile(szFilePath, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			lstrcpy(szScreenSaver, lpszSrchDir);
			lstrcat(szScreenSaver, "\\");
			lstrcat(szScreenSaver, wfd.cFileName);

			dwSize = GetFileVersionInfoSize(szScreenSaver, &dwInput);

			if(dwSize)
			{
				pFileVersion = malloc(dwSize);
				if(!pFileVersion)
				{
					DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
					LogErrorMessage("GetScrnSvrFile() : Out of memory", 0);
					break;
				}

				if(!GetFileVersionInfo(szScreenSaver, 0, dwSize, pFileVersion))
				{
					dwErr = GetLastError();
					wsprintf(szTemp, "GetScrnSvrFile:GetFileVersionInfo() failed for '%s'", szScreenSaver);
					LogErrorMessage(szTemp, dwErr);
					free(pFileVersion);
					continue;
				}


				lpDesc = NULL;
				VerQueryValue(pFileVersion, TEXT("\\StringFileInfo\\040904B0\\FileDescription"), 
							  (void **)&lpDesc, &uLen); 

				if(!lpDesc)
					VerQueryValue(pFileVersion, TEXT("\\StringFileInfo\\040904E4\\FileDescription"),
								  (void **)&lpDesc, &uLen); 

				if(lpDesc)
				{
					lpOpenGL = strstr(lpDesc, "OpenGL");
					if(lpDesc == lpOpenGL)
						lstrcpy(szDesc, lpDesc + 7);
					else
					{
						for(int j = 0, i = 0; i < lstrlen(lpDesc); i++)
						{
							if(lpDesc == lpOpenGL)
								i += 7;

							szDesc[j++] = lpDesc[i];
						}	

						szDesc[j] = '\0';
					}


					if(!lstrcmpi(lpszSelectedScrnSvr, szDesc))
					{
						retVal = TRUE;
						lstrcpy(lpszScrnSvrFile, szScreenSaver);
						free(pFileVersion);
						break;
					}
				}
				else
				{	
					wsprintf(szTemp, "GetScrnSvrFile:Version information not present for '%s'", szScreenSaver);
					LogErrorMessage(szTemp, 0);
				}

				free(pFileVersion);
			} // if(dwSize)
			else
			{
				dwErr = GetLastError();
				wsprintf(szTemp, "GetScrnSvrFile:GetFileVersionInfoSize() failed for '%s'", szScreenSaver);
				LogErrorMessage(szTemp, dwErr);
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}
	
	return retVal;
}


/* PRRemove
// Dialog procedure for the "Password Change Proc" dialog
BOOL APIENTRY PasswordChangeProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	TCHAR szSelectedFile[MAX_PATH], *pExtension = NULL;

    switch (message)
    {
        case WM_INITDIALOG:
		{
			// Get the recovery file path from the registry,
			// If not present then set default path in Safe
			HKEY hKey = NULL;
			TCHAR szRecoveryFile[MAX_PATH];
			lstrcpy(szRecoveryFile, g_szTokenFile);

			if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_QUERY_VALUE,
							&hKey) == ERROR_SUCCESS)
			{
				DWORD dwType, dwSize = MAX_PATH;
				if(RegQueryValueEx(hKey, "RecoveryFile", NULL, &dwType, (LPBYTE)szRecoveryFile, 
								   &dwSize) != ERROR_SUCCESS)
					lstrcpy(szRecoveryFile, g_szTokenFile);

				RegCloseKey(hKey);
			}

			SetDlgItemText(hDlg, IDE_RECOVERY_FILE, szRecoveryFile);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case ID_BROWSE:
				{
					TCHAR szFilter[MAX_PATH], szTitle[MAX_PATH];
					LoadString(g_hInst, IDS_RECOVERY_FILE, szFilter, MAX_PATH);
					lstrcat(szFilter, " (*.req)");
					lstrcpy(&szFilter[lstrlen(szFilter) + 1], "*.req");
					szFilter[lstrlen(szFilter) + 1 + 6] = '\0';

					LoadString(g_hInst, IDS_SEL_RECOVERY_FILE, szTitle, MAX_PATH);

					OPENFILENAME ofn;
					memset(&ofn, 0, sizeof(OPENFILENAME));
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner	= hDlg;
					ofn.hInstance	= NULL;
					ofn.lpstrFilter	= szFilter;
					ofn.nFilterIndex = 1;
					ofn.lpstrFile	= szSelectedFile;
					ofn.nMaxFile	= sizeof(szSelectedFile);
					ofn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK |
								OFN_OVERWRITEPROMPT | OFN_NODEREFERENCELINKS | OFN_NONETWORKBUTTON;
					szSelectedFile[0] = '\0';
					ofn.lpstrTitle = szTitle;
					ofn.lpfnHook    = (LPOFNHOOKPROC)SelectHookProc;

					if(GetOpenFileName(&ofn))
						SetDlgItemText(hDlg, IDE_RECOVERY_FILE, szSelectedFile);

					return TRUE;
				}


				case IDOK:    
				{
					HWND hWnd;
					TCHAR szOldPassword[MAX_PATH], szNewPassword[MAX_PATH];
					TCHAR szConfirmPasswd[MAX_PATH];

					GetDlgItemText(hDlg, IDE_OLD_PASSWD, szOldPassword, MAX_PATH);
					GetDlgItemText(hDlg, IDE_NEW_PASSWD, szNewPassword, MAX_PATH);
					GetDlgItemText(hDlg, IDE_CONFIRM_PASSWD, szConfirmPasswd, MAX_PATH);

					if(szOldPassword[0] == '\0')
					{
						DisplayMessage(hDlg, IDS_OLD_PASSWD, MB_OK | MB_ICONERROR);
						hWnd = GetDlgItem(hDlg, IDE_OLD_PASSWD);
						SetFocus(hWnd);
						return FALSE;
					}

					PBYTE pbHash = NULL;
					DWORD dwLen = 0;

					dwLen = HashData((PBYTE)szOldPassword, 
					   			     lstrlen(szOldPassword), &pbHash);
					if(memcmp(g_PasswdHash.pbHash, pbHash, dwLen) != 0)
					{
						DisplayMessage(hDlg, IDS_INVALID_PASSWD, MB_OK | MB_ICONERROR);
						hWnd = GetDlgItem(hDlg, IDE_OLD_PASSWD);
						SetFocus(hWnd);
						free(pbHash);
						return FALSE;
					}

					if(szNewPassword[0] == '\0')
					{
						DisplayMessage(hDlg, IDS_ENTER_NEW_PASSWD, MB_OK | MB_ICONERROR);
						hWnd = GetDlgItem(hDlg, IDE_NEW_PASSWD);
						SetFocus(hWnd);
						free(pbHash);
						return FALSE;
					}

					if(lstrcmpi(szNewPassword, szConfirmPasswd) != 0)
					{
						DisplayMessage(GetFocus(), IDS_PASSWD_MISMATCH, MB_OK | MB_ICONERROR);
						hWnd = GetDlgItem(hDlg, IDE_CONFIRM_PASSWD);
						SetFocus(hWnd);
						free(pbHash);
						return FALSE;
					}
 
					free(pbHash);

					dwLen = HashData((PBYTE)szNewPassword, 
					   			     lstrlen(szNewPassword), &pbHash);
					memcpy(g_PasswdHash.pbHash, pbHash, dwLen);
					g_PasswdHash.dwLen = dwLen;
					free(pbHash);

					// Check if need to save password token
					GetDlgItemText(hDlg, IDE_RECOVERY_FILE, szSelectedFile, sizeof(szSelectedFile));
					if(szSelectedFile[0] != '\0')
					{
						if(CreatePasswordFile())
						{
							// If the user chooses the default filename
							// then no need to copy
							if(lstrcmpi(g_szTokenFile, szSelectedFile))
							{
								// Append the '.req' extension to the recovery file if not already present
								pExtension = strchr(szSelectedFile, '.');
								if(pExtension == NULL)
									lstrcat(szSelectedFile, ".req");
								else
								{
									if(lstrcmpi(pExtension, ".req") != NULL)
										lstrcat(szSelectedFile, ".req");
								}

								if(!CopyFile(g_szTokenFile, szSelectedFile, FALSE))
								{
									TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH];
									DWORD dwError = GetLastError();
									LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_PATH);
									wsprintf(szFmt, szMsg, g_szTokenFile, szSelectedFile);
									MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
									wsprintf(szMsg, "PasswordChangeProc() : Error overwritting token file \'%s\'.", szSelectedFile);
									LogErrorMessage(szMsg, dwError);
								}
							}

							// Save location of recovery file
							// in the registry
							HKEY hKey;
							DWORD dwDisp;
							if(RegCreateKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
											  KEY_WRITE, NULL, &hKey, &dwDisp) == ERROR_SUCCESS)
							{
								RegSetValueEx(hKey, "RecoveryFile", 0, REG_SZ, (LPBYTE)szSelectedFile,
											  lstrlen(szSelectedFile) + 1);
								RegCloseKey(hKey);
							}
						}
						
					}
					
					DisplayMessage(hDlg, IDS_PASSWD_CHANGE, MB_ICONINFORMATION);

					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case ID_HELP:
				{
					ShowHelp("fet_password.htm");
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}*/

/*
// Dialog procedure for the "Recover Password" dialog
BOOL APIENTRY RecoverPasswordProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	static LPTSTR lpPasswdFile;
	TCHAR szRecoveryFile[MAX_PATH],szFilter[MAX_PATH], szTitle[MAX_PATH];
	TCHAR *pExtension = NULL;

    switch (message)
    {
        case WM_INITDIALOG:
		{
			lpPasswdFile = (LPTSTR)lParam;
			lpPasswdFile[0] = '\0';
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case ID_CREATE:
				{
					LoadString(g_hInst, IDS_RECOVERY_FILE, szFilter, MAX_PATH);
					lstrcat(szFilter, " (*.req)");
					lstrcpy(&szFilter[lstrlen(szFilter) + 1], "*.req");
					szFilter[lstrlen(szFilter) + 1 + 6] = '\0';

					LoadString(g_hInst, IDS_SEL_RECOVERY_FILE, szTitle, MAX_PATH);

					OPENFILENAME ofn;
					memset(&ofn, 0, sizeof(OPENFILENAME));
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner	= hDlg;
					ofn.hInstance	= NULL;
					ofn.lpstrFilter	= szFilter;
					ofn.nFilterIndex = 1;
					ofn.lpstrFile	= szRecoveryFile;
					ofn.nMaxFile	= sizeof(szRecoveryFile);
					ofn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK |
								OFN_OVERWRITEPROMPT | OFN_NODEREFERENCELINKS | OFN_NONETWORKBUTTON;
					szRecoveryFile[0] = '\0';
					ofn.lpstrTitle	= szTitle;
					ofn.lpfnHook    = (LPOFNHOOKPROC)SelectHookProc;

					if(GetOpenFileName(&ofn))
					{
						// If the user chooses the default filename
						// then no need to copy
						if(lstrcmpi(g_szTokenFile, szRecoveryFile))
						{
							// Append the '.req' extension to the recovery file if not already present
							pExtension = strchr(szRecoveryFile, '.');
							if(pExtension == NULL)
								lstrcat(szRecoveryFile, ".req");
							else
							{
								if(lstrcmpi(pExtension, ".req") != NULL)
									lstrcat(szRecoveryFile, ".req");
							}

							if(!CopyFile(g_szTokenFile, szRecoveryFile, FALSE))
							{
								TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH];
								DWORD dwError = GetLastError();
								LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_PATH);
								wsprintf(szFmt, szMsg, g_szTokenFile, szRecoveryFile);
								MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
								wsprintf(szMsg, "NewPasswordProc() : Error overwritting token file \'%s\'", szRecoveryFile);
								LogErrorMessage(szMsg, dwError);
							}
							else
								DisplayMessage(GetFocus(), IDS_RECOVERY_FILE_CREATED, MB_OK);
						}
						else
							DisplayMessage(GetFocus(), IDS_RECOVERY_FILE_CREATED, MB_OK);

					}

					return TRUE;
				}

				case ID_IMPORT:
				{
					TCHAR szFilter2[80] = TEXT("All Files (*.*)\0*.*\0\0");

					LoadString(g_hInst, IDS_IMPORT_RECOVERY_FILE, szTitle, MAX_PATH);

					OPENFILENAME ofn;
					memset(&ofn, 0, sizeof(OPENFILENAME));
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner	= hDlg;
					ofn.hInstance	= NULL;
					ofn.lpstrFilter	= szFilter2;
					ofn.nFilterIndex = 1;
					ofn.lpstrFile	= szRecoveryFile;
					ofn.nMaxFile	= sizeof(szRecoveryFile);
					ofn.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_ENABLEHOOK |
								OFN_OVERWRITEPROMPT | OFN_NODEREFERENCELINKS | OFN_NONETWORKBUTTON;
					szRecoveryFile[0] = '\0';
					ofn.lpstrTitle	= szTitle;
					ofn.lpfnHook    = (LPOFNHOOKPROC)ImportHookProc;

					if(GetOpenFileName(&ofn))
					{
						lstrcpy(lpPasswdFile, szRecoveryFile);
						EndDialog(hDlg, IDOK);
						return TRUE;
					}
										
					return TRUE;
				}

				case IDOK:    
				{
					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}

				case ID_HELP:
				{
					ShowHelp("fet_pwdtoken.htm");
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}
*/

/*
// Dialog procedure for the "DisplayText" dialog
BOOL APIENTRY DisplayTextProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
		{
			SetDlgItemText(hDlg, IDC_TEXT, (LPCTSTR)lParam);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDOK:    
				{
					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}

				case ID_HELP:
				{
					HKEY hKey;
					LRESULT lResult;
					TCHAR szHelp[MAX_PATH] = {"ie4_imexid.htm"};
					lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Internet Explorer", 0, 
								   KEY_QUERY_VALUE, &hKey);
					if(lResult == ERROR_SUCCESS)
					{
						TCHAR szVersion[MAX_PATH];
						DWORD dwType, dwSize = MAX_PATH;
						if(RegQueryValueEx(hKey, "Version", NULL, &dwType,
								(LPBYTE)szVersion, &dwSize) == ERROR_SUCCESS)
						{
							if(szVersion[0] == '5')
								lstrcpy(szHelp, "ie5_impexp.htm");
						}

						RegCloseKey(hKey);
					}

					ShowHelp(szHelp);
					return TRUE;
				}

			}
		}
			break;
	}

	return FALSE;
}
*/


// Dialog procedure for the "Change certificate" dialog
BOOL APIENTRY ChangeCertProc(HWND hDlg, UINT message, UINT wParam, LONG lParam)
{
	TCHAR szTemp[MAX_MSG_LEN];

    switch (message)
    {
        case WM_INITDIALOG:
		{
			if(lParam == 0)
				LoadString(g_hInst, IDS_MS_TO_VS, szTemp, sizeof(szTemp));
			else
				if(lParam == 1)
					LoadString(g_hInst, IDS_VS_TO_MS, szTemp, sizeof(szTemp));
				else
					LoadString(g_hInst, IDS_DIFF_PROFILE, szTemp, sizeof(szTemp));


			SetDlgItemText(hDlg, IDC_TEXT, szTemp);
			return TRUE;
		}

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				case IDOK:    
				{
					EndDialog(hDlg, IDOK);
					return TRUE;
				}

				case IDCANCEL:
				{
					EndDialog(hDlg, IDCANCEL);
					return TRUE;
				}
			}
		}
			break;
	}

	return FALSE;
}


BOOL CALLBACK EncryptHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
		case WM_INITDIALOG:
		{
			// This dlg proc is the proc for the child window which is created, we need to 
			// set the text for the parent windows IDOK
			CommDlg_OpenSave_SetControlText(GetParent(hWnd), IDOK, _T("&Encrypt"));
			return TRUE;
		}
	}

	return FALSE;
}



BOOL CALLBACK SelectHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
		case WM_INITDIALOG:
		{
			// This dlg proc is the proc for the child window which is created, we need to 
			// set the text for the parent windows IDOK
			CommDlg_OpenSave_SetControlText(GetParent(hWnd), IDOK, _T("&Save"));
			return TRUE;
		}
	}

	return FALSE;
}


/*
BOOL CALLBACK ImportHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
		case WM_INITDIALOG:
		{
			// This dlg proc is the proc for the child window which is created, we need to 
			// set the text for the parent windows IDOK
			CommDlg_OpenSave_SetControlText(GetParent(hWnd), IDOK, _T("&Import"));
			return TRUE;
		}
	}

	return FALSE;
}
*/


int CALLBACK RemoveContextHelpProc(HWND hwnd, UINT message, LPARAM lParam)
{
	switch(message)
	{    
		case PSCB_PRECREATE:
        // Remove the DS_CONTEXTHELP style from the dialog template
        if(((LPDLGTEMPLATEEX)lParam)->signature ==  0xFFFF)
		    ((LPDLGTEMPLATEEX)lParam)->style &= ~DS_CONTEXTHELP;        
		else 
			((LPDLGTEMPLATE)lParam)->style &= ~DS_CONTEXTHELP;
        
		return TRUE;    
	}    

	return TRUE;
}

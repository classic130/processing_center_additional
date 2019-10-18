// PTAUI.h : Declaration of the CPTAUI

#ifndef __PTAUI_H_
#define __PTAUI_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include "ptauistructs.h"
#include "utils.h"
#include "ptadefines.h"
#include <commctrl.h>

/////////////////////////////////////////////////////////////////////////////
// CPTAUI
class CPtaUI : 
	public CAxDialogImpl<CPtaUI>
{
public:
	CPtaUI()
	{
		m_szTempFileName = NULL;
		m_pUICtxt = NULL;
		m_pOpCtxt = NULL;

		m_hFontDefWizTitleFont = NULL;
		m_hFontDefUITitleFont = NULL;
		m_hFontDefTextFont = NULL;
		m_hFontDefBtnFont = NULL;

		m_hFontCustWizTitleFont = NULL;
		m_hFontCustUITitleFont = NULL;
		m_hFontCustTextFont = NULL;
		m_hFontCustBtnFont = NULL;
			
		m_hFontCertInfoFont = NULL;
		m_hFontValidityLabelFont = NULL;

		m_nCYSet = 0;
		m_boolFontsSet = FALSE;
		m_nCurrWiz = -1;

		m_nDefWizTitleFontSize = WIZARD_TITLE_FONT_SIZE;
		m_nDefUITitleFontSize = UI_TITLE_FONT_SIZE;
		m_nDefTextFontSize = UI_TEXT_FONT_SIZE;
		m_nDefBtnFontSize = UI_BTN_FONT_SIZE;

		m_nCustWizTitleFontSize = WIZARD_TITLE_FONT_SIZE;
		m_nCustUITitleFontSize = UI_TITLE_FONT_SIZE;
		m_nCustTextFontSize = UI_TEXT_FONT_SIZE;
		m_nCustBtnFontSize = UI_BTN_FONT_SIZE;

		m_nCertInfoFontSize = CERT_INFO_FONT_SIZE;
		m_nValidityLabelFontSize = CERT_VALIDITYLBL_FONT_SIZE;

		m_hBitmap = NULL;
		m_hCertBitmap = NULL;
		m_hTextureBrush = NULL;
		
		m_tbstrMsgToShow = "";		

		m_boolFocusSet = FALSE;

	}

	~CPtaUI()
	{
		if(m_pUICtxt)
		{
			_FreeUIContext(m_pUICtxt);
			delete(m_pUICtxt);
		}

		
	}

	enum { IDD = IDD_PTAUI };

BEGIN_MSG_MAP(CPTAUI)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_CTLCOLORSTATIC,OnCtlColorStatic)
	COMMAND_ID_HANDLER(IDOK, OnBtn1)
	COMMAND_ID_HANDLER(IDBTN2, OnBtn2)
	COMMAND_ID_HANDLER(IDBTN3, OnBtn3)
	COMMAND_ID_HANDLER(IDBTN4, OnBtn4)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	NOTIFY_HANDLER(IDC_LIST_CERTLIST,LVN_ITEMCHANGED,OnItemchangedList_CertList)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	
	HRESULT ConfirmAction(int i_nActionType);
	HRESULT ShowMessage(int nMessageType);
	HRESULT Close();
	HRESULT Initialize();
	HRESULT put_UIContext(PUICTXT i_pUICtxt);
	HRESULT get_UIContext(PUICTXT o_ppUICtxt);
	HRESULT ShowUI(POPCTXT pOpCtxt);
	HRESULT put_NextMessageToShow(VARIANT* i_pvarMsgToShow);


private :
	CAxWindow m_pCAxWindow;
	char *m_szTempFileName;
	PUICTXT m_pUICtxt;
	POPCTXT m_pOpCtxt;
	int m_nCYSet;
	BOOL m_boolFontsSet;
	BOOL m_nCurrWiz;
	HBITMAP m_hBitmap;
	HBITMAP m_hCertBitmap;
	HBRUSH  m_hTextureBrush;
	int m_nHeaderSize;
	int m_nUISize;
	int m_nCertPosY;
	_bstr_t m_tbstrMsgToShow;
	BOOL m_boolFocusSet;
	double lXMult;
	double lYMult;

	//Default fonts
	HFONT m_hFontDefWizTitleFont;
	HFONT m_hFontDefUITitleFont;
	HFONT m_hFontDefTextFont;
	HFONT m_hFontDefBtnFont;

	//Custom fonts
	HFONT m_hFontCustWizTitleFont;
	HFONT m_hFontCustUITitleFont;
	HFONT m_hFontCustTextFont;
	HFONT m_hFontCustBtnFont;

	//Fonts for the cert
	HFONT m_hFontCertInfoFont;
	HFONT m_hFontValidityLabelFont;

	//Default Font sizes
	int m_nDefWizTitleFontSize;
	int m_nDefUITitleFontSize;
	int m_nDefTextFontSize;
	int m_nDefBtnFontSize;
	
	//Custom Font sizes
	int m_nCustWizTitleFontSize;
	int m_nCustUITitleFontSize;
	int m_nCustTextFontSize;
	int m_nCustBtnFontSize;
	
	//Cert Fonts sizes
	int m_nCertInfoFontSize;
	int m_nValidityLabelFontSize;
	
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	HRESULT _DoSetup();
	HRESULT _SetDialogDims();
	HRESULT _SetSeparators();
	HRESULT _CreateFonts();
	HRESULT _SetHeader();
	HRESULT _SetButtons();
	HRESULT _SetOpenUI(BOOL boolIsOpen);
	HRESULT _SetSelectUI();
	HRESULT _SetSignUI();

	HRESULT _SetIntroUI();
	HRESULT _SetCreatePasswdUI();
	HRESULT _SetEnterPasswdUI();
	HRESULT _SetChangePasswdUI();
	HRESULT _SetImportP12UI();	
	HRESULT _SetExportP12UI();
	HRESULT _SetVRSNLogo();

	// Sasi 05/02/2003
	// Added functions to set up UI for GetSecretQuestion, ResetPassword and CreateSecret dialogs
	HRESULT _SetGetSecretQuestionUI();
	HRESULT _SetResetPasswdUI();
	HRESULT _SetCreateSecretUI();


	HFONT	_CreateFont(int i_nCharset,_bstr_t& i_tbstrFontName, int i_nFontSize, int i_nFontWeight, int* o_pnActFontHeight);
	HRESULT _SetField_FontAndText(int i_nFieldId, HFONT i_phFont, _bstr_t& i_tbstrText, int i_nTruncWidth = 0, int i_nWidth = 0, int i_nHeight = 0, int i_nTopBtmMargin = 0, int i_nInterCharSpace = 0);
	HRESULT _SetField_FontAndTextWeb(int i_nFieldId, HFONT i_phFont, _bstr_t& i_tbstrText, int i_nTruncWidth = 0, int i_nWidth = 0, int i_nHeight = 0, int i_nTopBtmMargin = 0, int i_nInterCharSpace = 0);
	HRESULT _SetField_PlacementInRegion(int i_nFieldId, int i_nFieldMaxWidth, int i_nFieldMaxHeigth, int i_nLeftMargin, int i_nRightMargin, int i_nTopMargin, int i_nBottomMargin, 
											int i_nRegionMinWidth, int i_nRegionMinHeight, int i_nRegionX, int i_nRegionY, int i_nRegionAnch, int i_nFieldXAnch, int i_nFieldYAnch,
											int* o_pRegionWidth, int* o_pRegionHeight, BOOL i_boolEnabelField = TRUE);
	HRESULT _FillListBox(int i_nListField, HFONT i_hFontTextFont, _bstr_t* i_ptbstrList, int i_nNumOfElems, _bstr_t& i_tbstrCurrSel);
	HRESULT _GetCurrListItem(int i_nListField, _bstr_t* o_ptbstrSelectedItem);

	HRESULT _CreateCertRect(HDC hDC,int i_nCertRectX,int i_nCertRectY);
	HRESULT _DisplayCert();
	HRESULT _ShowTransparentBitmap(LONG resourceId);
	HRESULT _CreateListCtrlHeaders(int i_nListCtrlId);
	HRESULT _AddColHeader(HWND i_nhwndCtrlWnd,int i_nColHeaderName,int i_nColHeaderWidth,int i_nHeaderNum);
	HRESULT _FillListCtrl(int i_nListCtrlId, PALL_SELID_UIELEMENTS i_pAllSelIDUIElems);
	HRESULT _AddItemInListCtrl(HWND i_hwndListCtrl,int i_nItem,int i_nSubItem,_bstr_t& i_tbstrItemText);
	HRESULT _StoreParams();
	HRESULT _DoTearDown(int i_nCurrOperation);
	HRESULT _StoreOpenUIParams(BOOL boolFlag);
	HRESULT _StoreCreatePasswdParams();
	HRESULT _StoreEnterPasswdParams();
	HRESULT _StoreChangePasswdParams();
	HRESULT _StoreImportP12Params();
	HRESULT _StoreExportP12Params();
	HRESULT _StoreSelectUIParams();
	HRESULT _StoreSignUIParams();

	// Sasi 05/02/2003
	// Added functions to store values of dialog box elements in GetSecretQuestion, ResetPassword and CreateSecret dialogs
	HRESULT _StoreGetSecretQuestionUIParams();
	HRESULT _StoreResetPasswdParams();
	HRESULT _StoreCreateSecretParams();

	HRESULT _GetDlgItemText(int i_nDlgItemId, _bstr_t* o_ptbstrDlgItemText);
	HRESULT _TeardownSeparator();
	HRESULT _TeardownOpenUI(BOOL boolIsOpen);
	HRESULT _TeardownCreatePasswdUI();
	HRESULT _TeardownEnterPasswdUI();
	HRESULT _TeardownChngPasswdUI();
	HRESULT _TeardownImportP12UI();
	HRESULT _TeardownExportP12UI();
	HRESULT _TeardownSelectUI();
	HRESULT _TeardownSignUI();
	HRESULT _TeardownIntroUI();
	HRESULT _TeardownHeader();
	HRESULT _TeardownFonts();

	// Sasi 05/02/2003
	// Added functions to destroy GetSecretQuestion, ResetPassword and CreateSecret dialogs
	HRESULT _TeardownGetSecretQuestionUI();
	HRESULT _TeardownResetPasswdUI();
	HRESULT _TeardownCreateSecretUI();

	HRESULT _DoBrowse(BOOL i_boolSaveFile = TRUE);
	HRESULT _SelectFile(HWND hParent, UINT idOFFilter, BOOL i_boolSaveFile, _bstr_t* o_ptbstrSelFile);

	LRESULT OnBtn1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBtn2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBtn3(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBtn4(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnItemchangedList_CertList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	HRESULT _TeardownVRSNLogo();
};

#endif //__PTAUI_H_

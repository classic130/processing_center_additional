// DNZUI.h : Declaration of the CDNZUI

#ifndef __DNZUI_H_
#define __DNZUI_H_

#include "resource.h"       // main symbols
#include <atlhost.h>
#include <commctrl.h>
#include <comutil.h>
#include "dnzuistructs.h"
#include "nzutils.h"
#include "nzdefines.h"
#include "shlink.h"

/////////////////////////////////////////////////////////////////////////////
// CDNZUI
class CDNZUI : 
	public CAxDialogImpl<CDNZUI>
{
public:
	CDNZUI()
	{
		m_pUICtxt = NULL;
		m_pOpCtxt = NULL;

		m_hFontDefWizTitleFont = NULL;
		m_hFontDefUITitleFont = NULL;
		m_hFontDefTextFont = NULL;
		m_hFontDefBtnFont = NULL;
		m_hFontDefUndTextFont = NULL;

		m_hFontCustWizTitleFont = NULL;
		m_hFontCustUITitleFont = NULL;
		m_hFontCustTextFont = NULL;
		m_hFontCustBtnFont = NULL;
			
		m_nCYSet = 0;
		m_nReceiptDisplayPos = 0;
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

		m_hBitmap = NULL;
		m_hTextureBrush = NULL;
		
		m_tbstrMsgToShow = "";		

		m_boolFocusSet = FALSE;

		m_bModeless = FALSE;
		m_bIsCancelled = FALSE;
	}

	~CDNZUI()
	{
		if(m_pUICtxt)
		{
			_FreeUIContext(m_pUICtxt);
			delete(m_pUICtxt);
		}

		
	}

	enum { IDD = IDD_DNZUI };

BEGIN_MSG_MAP(CDNZUI)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_CTLCOLORSTATIC,OnCtlColorStatic)
	COMMAND_ID_HANDLER(IDOK, OnBtn1)
	COMMAND_ID_HANDLER(IDBTN2, OnBtn2)
	COMMAND_ID_HANDLER(IDBTN3, OnBtn3)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	COMMAND_ID_HANDLER(IDBTN4, OnBtn4)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	REFLECT_NOTIFICATIONS()				// reflect messages back to static links
END_MSG_MAP()

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::InvalidateRect(::GetDlgItem(m_hWnd, IDC_LABEL7), NULL, TRUE);
		::InvalidateRect(::GetDlgItem(m_hWnd, IDC_LABEL8), NULL, TRUE);
		::InvalidateRect(::GetDlgItem(m_hWnd, IDC_LABEL3_3), NULL, TRUE);
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_HyperLink.UnsubclassWindow();
		m_SaveLink.UnsubclassWindow();
		m_ViewLink.UnsubclassWindow();
		return 1;
	}


// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
	
#if 0
	HRESULT ConfirmAction(int i_nActionType);	//This function will bring up a Yes/No message box asking the user to confirm the action
												//specified by the i_nActionType
	HRESULT ShowMessage(int nMessageType);		//This function will bring up a Ok message box showing the user a message
												//specified by the i_nMessageType
#endif

	HRESULT Close();							//This will close the UI instance.
	HRESULT Initialize();						//This will initialize the UI instance.
	HRESULT put_UIContext(PUICTXT i_pUICtxt);	//This will set the UI context. The UI context specifies which UI is to be shown and the 
												//behaviour of the UI
	HRESULT get_UIContext(PUICTXT o_ppUICtxt);	//This function will return the context of the current UI
	HRESULT ShowUI(POPCTXT pOpCtxt);			//This function must be called to show the UI specified by the current UI context.
	HRESULT put_NextMessageToShow(VARIANT* i_pvarMsgToShow);	//This function can be used to specify a message to be shown after the
																//call to the callback function returns, before showing the next UI.
	HRESULT BeginUI(POPCTXT pOpCtxt);
	HRESULT UpdateUI();
	HRESULT EndUI();

	BOOL IsModelessDlg();
	BOOL IsDialogCancelled();
	VOID SetCancelled(BOOL i_IsCancelled);

private :
	//Internal data
	PUICTXT m_pUICtxt;
	POPCTXT m_pOpCtxt;
	int m_nCYSet;
	BOOL m_boolFontsSet;
	BOOL m_nCurrWiz;
	HBITMAP m_hBitmap;
	HBRUSH  m_hTextureBrush;
	int m_nHeaderSize;
	int m_nUISize;
	int m_nCertPosY;
	int m_nReceiptDisplayPos;
	_bstr_t m_tbstrMsgToShow;
	BOOL m_boolFocusSet;
	double lXMult;
	double lYMult;
	HWND m_hDlgWnd;
	BOOL m_bModeless;		// Is a modeless dialog box been shown currently
	BOOL m_bIsCancelled;

	//Default fonts
	HFONT m_hFontDefWizTitleFont;
	HFONT m_hFontDefUITitleFont;
	HFONT m_hFontDefTextFont;
	HFONT m_hFontDefBtnFont;
	HFONT m_hFontDefUndTextFont;

	//Custom fonts
	HFONT m_hFontCustWizTitleFont;
	HFONT m_hFontCustUITitleFont;
	HFONT m_hFontCustTextFont;
	HFONT m_hFontCustBtnFont;

	
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

	CHLink m_HyperLink;		// Represents a hyperlink, subclasses the IDC_LABEL7 static control
	CHLink m_SaveLink;		// hyperlink, subclasses the IDC_LABEL8 static control
	CHLink m_ViewLink;		// hyperlink, subclasses the IDC_LABEL9 static control

	//Dialog Init routine
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	//Routines that will render the UI corresponding to the current UI context.
	HRESULT _DoSetup();
	HRESULT _SetDialogDims();
	HRESULT _SetSeparators();
	HRESULT _CreateFonts();
	HRESULT _SetHeader();
	HRESULT _SetButtons();
	HRESULT _SetSelectFileUI();
	HRESULT _SetProgressUI();
	HRESULT _SetVerifyRcptUI();
	HRESULT _SetErrorUI();
	HRESULT _SetVRSNLogo();
	//HRESULT _SetRBSLogo(int i_nRegionY);
	HRESULT _SetDigRcpt(int i_nRegionY);
	HRESULT _SetErrorBmp(int i_nRegionY, int i_nRegionHeight);
	HRESULT _DisplayLogo(int i_nContainer, int i_nBitmap);
	HRESULT _ShowReceiptDetails();

	//Function to create a font given its character set, size,weight and name
	HFONT _CreateFont(int i_nCharset,_bstr_t& i_tbstrFontName, int i_nFontSize, int i_nFontWeight, int* o_pnActFontHeight, BOOL bUnderline = FALSE);

	//Function to set the font and text of a text widget
	HRESULT _SetField_FontAndText(int i_nFieldId, HFONT i_phFont, _bstr_t& i_tbstrText, int i_nTruncWidth = 0, int i_nWidth = 0, int i_nHeight = 0, int i_nTopBtmMargin = 0, int i_nInterCharSpace = 0, int i_nTruncHeight=0);

	//Function to place a widget in a region
	HRESULT _SetField_PlacementInRegion(int i_nFieldId, int i_nFieldMaxWidth, int i_nFieldMaxHeigth, int i_nLeftMargin, int i_nRightMargin, int i_nTopMargin, int i_nBottomMargin, 
											int i_nRegionMinWidth, int i_nRegionMinHeight, int i_nRegionX, int i_nRegionY, int i_nRegionAnch, int i_nFieldXAnch, int i_nFieldYAnch,
											int* o_pRegionWidth, int* o_pRegionHeight, BOOL i_boolEnabelField = TRUE);
	
	
	//Function to store any input params specified by the user to the UI	
	HRESULT _StoreParams();
	HRESULT _StoreSelectFileParams();
	HRESULT _StoreProgressParams();
	HRESULT _StoreVerifyRcptParams();
	HRESULT _GetDlgItemText(int i_nDlgItemId, _bstr_t* o_ptbstrDlgItemText);

	//Functions to teardown the UI
	HRESULT _DoTearDown(int i_nCurrOperation);
	HRESULT _TeardownSeparator();
	HRESULT _TeardownSelectFileUI();
	HRESULT _TeardownProgressUI();
	HRESULT _TeardownVerifyRcptUI();
	HRESULT _TeardownErrorUI();
	HRESULT _TeardownHeader();
	HRESULT _TeardownFonts();
	HRESULT _TeardownVRSNLogo();

	LRESULT OnBtn1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBtn2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBtn3(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBtn4(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	//Functions called while rendering the UI
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
	HRESULT _DoBrowse();
	
};

#endif //__DNZUI_H_

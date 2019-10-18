#pragma once

#include "npapi.h"

#include "CCharFlipper.h"

/////////////////////////////////////////////////////////////////////////////

#define ID_VIDEO_PLAY           1000
#define ID_VIDEO_STOP           1001
#define ID_VIDEO_REWIND         1002
#define ID_VIDEO_FORWARD        1003
#define ID_VIDEO_FRAME_BACK     1004
#define ID_VIDEO_FRAME_FORWARD  1005

// CWinFlipView:
//
class CWinFlipView : public CWnd, public CPluginView {
	public:
							CWinFlipView( CCharFlipper* inController );
		virtual				~CWinFlipView();
		
		virtual WNDPROC* 	GetSuperWndProcAddr();
	
	//{{AFX_MSG( CMainWindow )
		afx_msg void 		OnPaint();
		afx_msg void 		OnPaletteChanged(CWnd* pWnd);
		afx_msg void 		OnLButtonDown(UINT flags, CPoint point);
		afx_msg void 		OnRButtonDown(UINT flags, CPoint point);
    
		afx_msg void 		OnPlay();

		afx_msg void 		OnStop();
		afx_msg void 		OnRewind();
		afx_msg void 		OnForward();
		afx_msg void 		OnFrameBack();
		afx_msg void 		OnFrameForward();
	//}}AFX_MSG

		DECLARE_MESSAGE_MAP()
		
	protected:
		char				mLastCharacter;
};

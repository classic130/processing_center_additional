// The class is basically created to take advantage of the message handling functionality
// of MFC

// The child window created by Netscape Navigator for the plug-in will be sub-classed to
// the CWinFlipView by my npshell.cpp code.  

// This particular example handles left and right mouse clicks, paint messages, and has a
// set of Avi specific calls.

#include "stdafx.h"
#include "CWinFlipView.h"
#include "CCharFlipper.h"

// CWinFlipView constructor:
//
CWinFlipView::CWinFlipView( CCharFlipper* inController )
:	CPluginView( inController )
{
}

// The following functions all simply call the relevant AVI function of the CAvi member.
// They don't do any error checking because they are only called if the data is valid (we
// hope...*grin*)
void CWinFlipView::OnPlay() 
{
	CCharFlipper* flipper = (CCharFlipper*)mController
    flipper->SetRunning( TRUE );
}

void CWinFlipView::OnStop() 
{
	CCharFlipper* flipper = (CCharFlipper*)mController
    flipper->SetRunning( FALSE );
}

void CWinFlipView::OnRewind() 
{
    
}

void CWinFlipView::OnForward() 
{
    
}

void CWinFlipView::OnFrameBack() 
{
    
}

void CWinFlipView::OnFrameForward() 
{
    
}

void CWinFlipView::OnLButtonDown(UINT flags, CPoint point) 
{
	CCharFlipper* flipper = (CCharFlipper*)mController
    NPBool isRunning = flipper->GetRunning();
    flipper->SetRunning( ! isRunning );
}

void CWinFlipView::OnRButtonDown(UINT uFlags, CPoint cpPoint) 
{
    UINT uState;
    //	Call the base class to handle the click.
	CWnd::OnRButtonDown(uFlags, cpPoint);
	CCharFlipper* flipper = (CCharFlipper*)mController

	CMenu cmPopup;
	if(cmPopup.CreatePopupMenu() == 0)	{
		return;
	}

    if(flipper->GetRunning()) {
    	uState = MF_GRAYED;
    }
	else {
		uState = MF_ENABLED;
	}
	cmPopup.AppendMenu(uState, ID_VIDEO_PLAY, "Play...");	

    if(!(flipper->GetRunning())) {
    	uState = MF_GRAYED;
    }
	else {
		uState = MF_ENABLED;
	}
	cmPopup.AppendMenu(uState, ID_VIDEO_STOP, "Pause...");

	//	Separator
	cmPopup.AppendMenu(MF_SEPARATOR);

    uState = MF_ENABLED;	
	cmPopup.AppendMenu(uState, ID_VIDEO_REWIND,  "Rewind (Start of movie)...");
	cmPopup.AppendMenu(uState, ID_VIDEO_FORWARD, "Forward (End of movie)...");

    //	Separator
	cmPopup.AppendMenu(MF_SEPARATOR);
	
    cmPopup.AppendMenu(uState, ID_VIDEO_FRAME_BACK,  "Frame Back...");
	cmPopup.AppendMenu(uState, ID_VIDEO_FRAME_FORWARD, "Frame Forward...");

	ClientToScreen(&cpPoint);
	cmPopup.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, cpPoint.x, cpPoint.y, this, NULL);

}

void CWinFlipView::OnPaint() {
	CPaintDC dc(this); // device context for painting

    //CWnd::OnPaint();
}

void CWinFlipView::OnPaletteChanged(CWnd* pFocusWnd) {
	//	Don't do this if we caused it to happen.
	if(pFocusWnd == (CWnd *)this)	{
		return;
	}
//	if (m_data && m_data->cAvi) {        
//        m_data->cAvi->Realize();
//    }    
}

//////////////////
// Return place to hold original window proc
WNDPROC* CWinFlipView::GetSuperWndProcAddr()
{   
#ifdef WIN32
	return CWnd::GetSuperWndProcAddr();
#else
    static WNDPROC pfnSuper;   // place to store window proc
    return &pfnSuper;          // always return the same address
#endif
}

// CMainWindow message map:
// Associate messages with member functions.
//
// It is implied that the ON_WM_PAINT macro expects a member function
// "void OnPaint()".
//
BEGIN_MESSAGE_MAP( CWinFlipView, CWnd )
	//{{AFX_MSG_MAP( CMainWindow )
	ON_WM_PAINT()
 	ON_WM_PALETTECHANGED()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_VIDEO_PLAY,OnPlay)
    ON_COMMAND(ID_VIDEO_STOP,OnStop)
    ON_COMMAND(ID_VIDEO_REWIND,OnRewind)
    ON_COMMAND(ID_VIDEO_FORWARD,OnForward)
    ON_COMMAND(ID_VIDEO_FRAME_BACK,OnFrameBack)
    ON_COMMAND(ID_VIDEO_FRAME_FORWARD,OnFrameForward)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


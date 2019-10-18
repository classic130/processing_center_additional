// WinFlipView.cpp : implementation file
//

#include "stdafx.h"

#include "WinFlipView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define EVENT_TIMEPASSED	10

/////////////////////////////////////////////////////////////////////////////
// CWinFlipView

CWinFlipView::CWinFlipView( CCharFlipper* inController )
:	CFlipView( inController ),
	mWindow( NULL ),
	mTimer( 0 )
{

}

CWinFlipView::~CWinFlipView()
{
}


BEGIN_MESSAGE_MAP(CWinFlipView, CWnd)
	//{{AFX_MSG_MAP(CWinFlipView)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinFlipView message handlers

void CWinFlipView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetFlipper()->HandleMouseClick();

	CWnd::OnLButtonDown(nFlags, point);
}


void CWinFlipView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CString	outText;
	CFont outFont;

	outFont.CreateFont( mWindow->height,	// height
						mWindow->width/2,	// width
						0,				// escapement
						0,				// orientation
						FW_BOLD,		// weight
						FALSE,			// italics
						FALSE,			// underline
						FALSE,			// strikeout
						ANSI_CHARSET,	// character set
						OUT_DEVICE_PRECIS,			// outprecision
						CLIP_DEFAULT_PRECIS,		// clipprecision
						DEFAULT_QUALITY,			// quality
						DEFAULT_PITCH | FF_MODERN,	// pitchandfamily
						NULL );				// facename

	CFont* oldFont = (CFont*) dc.SelectObject( & outFont );

	outText.Format("%c", mCurrentChar );
	dc.TextOut( 0, 0, outText );
	// Do not call CWnd::OnPaint() for painting messages
}

//---------------------------------------------------------
// CWinFlipView::GetWindow
//---------------------------------------------------------
NPWindow*
CWinFlipView::GetWindow()
{
	return mWindow;
}

//---------------------------------------------------------
// CWinFlipView::SetWindow
//---------------------------------------------------------
NPError
CWinFlipView::SetWindow( NPWindow* inWindow )
{
	if( mWindow != NULL ) {
		if( mTimer ) {
			KillTimer( mTimer );
			mTimer = 0;
		}
		UnsubclassWindow();
		mWindow = NULL;
	}
	if( inWindow != NULL ) {
		if( inWindow->window != NULL ) {
			SubclassWindow( (HWND) (inWindow->window) );
			mWindow = inWindow;
			Paint();
			mTimer = SetTimer( EVENT_TIMEPASSED, 10, NULL );
		}
	}
	return NPERR_NO_ERROR;
}

//---------------------------------------------------------
// CWinFlipView::Paint
//---------------------------------------------------------
void
CWinFlipView::Paint()
{
	if( mWindow != NULL ) {
		Invalidate();
		UpdateWindow();
	}
}


void CWinFlipView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if( nIDEvent == EVENT_TIMEPASSED ) {
		GetFlipper()->HandleTimePassed();
	}
	CWnd::OnTimer(nIDEvent);
}
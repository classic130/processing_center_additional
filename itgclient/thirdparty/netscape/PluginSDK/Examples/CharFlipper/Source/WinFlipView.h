// WinFlipView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWinFlipView window
#include "CFlipView.h"

class CFlipView;
class CCharFlipper;

class CWinFlipView : public CWnd, public CFlipView
{
// Construction
public:
	CWinFlipView( CCharFlipper* inController );

// Attributes
public:

// Operations

public:
//	virtual NPError		SetWindow( NPWindow* inWindow );
//	virtual void		Paint();

//	CCharFlipper*		GetCFController() {return (CCharFlipper*) mController;};
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinFlipView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWinFlipView();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWinFlipView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
// CPluginView implementations
public:
	NPWindow*			GetWindow();

	virtual NPError		SetWindow( NPWindow* inWindow );
	virtual void		Paint();

protected:
	NPWindow*			mWindow;
	UINT				mTimer;
};

/////////////////////////////////////////////////////////////////////////////
#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CMacFlipView.h"

//======================================================================
//		CMacFlipView::CMacFlipView()
//======================================================================

CMacFlipView::CMacFlipView( CCharFlipper* inController )
:	CFlipView( inController )
{
	mSavePort.clipRgn = ::NewRgn();
}

//======================================================================
//		CMacFlipView::~CMacFlipView()
//======================================================================
CMacFlipView::~CMacFlipView()
{
	if( mSavePort.clipRgn ) {
		::DisposeRgn(mSavePort.clipRgn);
	}
}

//---------------------------------------------------------
// CMacFlipView::GetWindow
//---------------------------------------------------------
NPWindow*
CMacFlipView::GetWindow()
{
	return mWindow;
}

//======================================================================
//		CMacFlipView::SetWindow
//======================================================================
NPError
CMacFlipView::SetWindow( NPWindow* inWindow )
{
	mWindow = inWindow;
	Paint();
	return NPERR_NO_ERROR;
};

//======================================================================
//		CMacFlipView::Paint()
//======================================================================
void
CMacFlipView::Paint()
{
	if( mWindow ) {
		if( StartDraw( mWindow ) ) {
			DoDraw( mCurrentChar, mWindow );
			EndDraw( mWindow );
		}
	}
}

//------------------------------------------------------------------------------------
// CMacFlipView::StartDraw:
//------------------------------------------------------------------------------------
Boolean
CMacFlipView::StartDraw(NPWindow* inWindow)
{
	if (inWindow == NULL)
		return FALSE;
	NP_Port* port = (NP_Port*) inWindow->window;
	if (inWindow->clipRect.left < inWindow->clipRect.right)
	{
	// Preserve the old port
		::GetPort((GrafPtr*)&mOldPort);
		::SetPort((GrafPtr)port->port);
	// Preserve the old drawing environment
		mSavePort.portRect = port->port->portRect;
		mSavePort.txFont = port->port->txFont;
		mSavePort.txFace = port->port->txFace;
		mSavePort.txMode = port->port->txMode;
		mSavePort.rgbFgColor = port->port->rgbFgColor;
		mSavePort.rgbBkColor = port->port->rgbBkColor;
		::GetClip(mSavePort.clipRgn);
	// Setup our drawing environment
		Rect clipRect;
		clipRect.top = inWindow->clipRect.top + port->porty;
		clipRect.left = inWindow->clipRect.left + port->portx;
		clipRect.bottom = inWindow->clipRect.bottom + port->porty;
		clipRect.right = inWindow->clipRect.right + port->portx;
		::SetOrigin(port->portx,port->porty);
		::ClipRect(&clipRect);
		clipRect.top = clipRect.left = 0;
		TextSize(inWindow->height);
		TextFont(geneva);
		TextMode(srcCopy);
		RGBColor  col;
		col.red = col.green = col.blue = 30000;
		RGBForeColor(&col);
		col.red = col.green = col.blue = 65000;
		RGBBackColor(&col);
		return TRUE;
	}
	else
		return FALSE;
}


//------------------------------------------------------------------------------------
// CMacFlipView::EndDraw:
//------------------------------------------------------------------------------------
void
CMacFlipView::EndDraw(NPWindow* inWindow)
{
	NP_Port* port = (NP_Port*) inWindow->window;
	::SetOrigin(mSavePort.portRect.left, mSavePort.portRect.top);
	::SetClip(mSavePort.clipRgn);
	CGrafPtr myPort;
	::GetPort((GrafPtr*)&myPort);
	myPort->txFont = mSavePort.txFont;
	myPort->txFace = mSavePort.txFace;
	myPort->txMode = mSavePort.txMode;
	::RGBForeColor(&mSavePort.rgbFgColor);
	::RGBBackColor(&mSavePort.rgbBkColor);
	::SetPort((GrafPtr)mOldPort);
}


//------------------------------------------------------------------------------------
// CMacFlipView::DoDraw:
//------------------------------------------------------------------------------------
void
CMacFlipView::DoDraw( char inChar, NPWindow* inWindow )
{
		Rect drawRect;
		drawRect.top = 0;
		drawRect.left = 0;
		drawRect.bottom = drawRect.top + inWindow->height;
		drawRect.right = drawRect.left + inWindow->width;
		::EraseRect(&drawRect);
	
		MoveTo(drawRect.left, drawRect.bottom - 10);
		::DrawChar( inChar );
}


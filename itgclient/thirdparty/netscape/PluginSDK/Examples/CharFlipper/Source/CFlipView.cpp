// CFlipView.cpp : implementation file
//
#include "CFlipView.h"



CFlipView::CFlipView( CCharFlipper* inController )
:	CPluginView( inController ),
	mCurrentChar( ' ' )
{

}

CFlipView::~CFlipView()
{
}

//---------------------------------------------------------
// CFlipView::SetChar
//---------------------------------------------------------
void
CFlipView::SetChar( char inChar )
{
	mCurrentChar = inChar;
}

//---------------------------------------------------------
// CFlipView::GetCFController
//---------------------------------------------------------
CCharFlipper*
CFlipView::GetFlipper()
{
	return (CCharFlipper*) mController ;
}

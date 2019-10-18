// CFlipView.h : header file
//

#ifndef CFLIPVIEW_H
#define CFLIPVIEW_H

/////////////////////////////////////////////////////////////////////////////
// CFlipView window
#include "CPluginView.h"
#include "CCharFlipper.h"

class CFlipView : public CPluginView
{
public:
	CFlipView( CCharFlipper* inController );
	virtual ~CFlipView();

	// CFlipView methods
	virtual void		SetChar( char inChar );
	CCharFlipper*		GetFlipper();

protected:
	char				mCurrentChar;
};

/////////////////////////////////////////////////////////////////////////////
#endif /*CFLIPVIEW_H*/
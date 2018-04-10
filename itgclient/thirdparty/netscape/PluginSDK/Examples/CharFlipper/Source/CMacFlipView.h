#pragma once

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CFlipView.h"
#include "CCharFlipper.h"

class CNetscapePlugin;

class CMacFlipView : public CFlipView {
	public:
							CMacFlipView( CCharFlipper* inController );
		virtual				~CMacFlipView();

		NPWindow*			GetWindow();
		virtual NPError		SetWindow( NPWindow* inWindow );

		virtual void		Paint();
		
	protected:
		Boolean 			StartDraw(NPWindow * inWindow);
		void 				EndDraw(NPWindow * inWindow);
		void 				DoDraw( char inChar, NPWindow* inWindow );

		NPWindow*			mWindow;
		CGrafPort			mSavePort;
		CGrafPtr			mOldPort;
};

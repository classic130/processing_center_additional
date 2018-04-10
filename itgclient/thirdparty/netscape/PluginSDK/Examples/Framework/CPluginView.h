// CPluginView.h
#ifndef CPLUGINVIEW_H
#define CPLUGINVIEW_H


#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CNetscapePlugin.h"

class CNetscapePlugin;

class CPluginView {
	public:
							CPluginView( CNetscapePlugin* controller );
		virtual				~CPluginView();

		virtual NPError		SetWindow( NPWindow* window );
		virtual void		Paint();
		
		CNetscapePlugin*	GetController();
	
	protected:
		CNetscapePlugin*	mController;	
	
};

#endif /* CPLUGINVIEW_H */
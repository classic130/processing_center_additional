// CNetscapePlugin.h

#ifndef CNETSCAPEPLUGIN_H
#define CNETSCAPEPLUGIN_H

#ifndef _NPAPI_H_
#include "npapi.h"
#endif

#include "CPluginArgs.h"
#include "CNetscapeStream.h"
#include "CPluginView.h"
#include "CNetscapeMemObject.h"
#include "CNavigator.h"

class CPluginView;

class CNetscapePlugin : public CNetscapeMemObject {
	public:
		static NPError		Initialize( void ) { return NPERR_NO_ERROR; };
		static NPError		Shutdown( void ) { return NPERR_NO_ERROR; };
		
							CNetscapePlugin( NPP instance, uint16 mode, CPluginArguments* adoptedArgs );
		virtual				~CNetscapePlugin();

		virtual NPError		SaveData( NPSavedData** );
		
		virtual NPError				SetWindow( NPWindow* window );
		virtual void				Print( NPPrint* printInfo );
		virtual NPBool				Handle_Event( void* event );
		
		CPluginView*				GetView() { return mView; };
		
		virtual CNetscapeStream*	CreateStream( NPMIMEType type, NPStream *stream, NPBool seekable, uint16 stype );
		virtual CPluginView* 		CreatePluginView( ) ;
		
		CNavigator*			GetNavigator();
		
	protected:
		virtual NPBool		PrintFull( NPFullPrint& fullPrintInfo );
		virtual void		PrintEmbeded( NPEmbedPrint& embedPrintInfo );

		CPluginView*		mView;
		unsigned short		mMode;
		CPluginArguments*	mArgs;
		CNavigator*			mNavigator;
};

CNetscapePlugin* CreateNetscapePlugin( NPP instance, uint16 mode, CPluginArguments* adoptedArgs, NPSavedData* saved );
NPError InitializeNetscapePlugin( void );
void ShutdownNetscapePlugin( void );
jref InitializeJavaClass( void );

#endif /* CNETSCAPEPLUGIN_H */
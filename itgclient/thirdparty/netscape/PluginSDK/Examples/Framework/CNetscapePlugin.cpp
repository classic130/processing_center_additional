//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// CNetscapePlugin.cpp
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#include "CNetscapePlugin.h"

extern CNetscapePlugin* CreateNetscapePlugin( uint16 mode, CPluginArguments* adoptedArgs, NPSavedData* saved );
extern NPError InitializeNetscapePlugin( void );
extern void ShutdownNetscapePlugin( void );
extern jref InitializeJavaClass( void );


//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//	Procedural Methods
// 
//	This are the methods called by npmac.cpp. NPP_New, NPP_SetWindow, NPP_Print,
//  and NPP_HandleEvent are dispatched to a CNetscapePlugin object. NPP_NewStream calls the
//  CNetscapePlugin object to create a CNetscapeStream object. NPP_WriteReady, NPP_Write,
//  and NPP_DestroyStream are dispatched to that CNetscapeStream object.
//
//  Four external methods must be defined to initialize and shutdown the appropriate 
//  classes: InitializeNetscapePlugin, CreateNetscapePlugin, ShutdownNetscapePlugin, 
//  and InitializeJavaClass.
// 
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


//------------------------------------------------------------------------------------
// NPP_Initialize:
//------------------------------------------------------------------------------------
NPError NPP_Initialize(void)
{
	NPError error = InitializeNetscapePlugin();
	return error;
}


//------------------------------------------------------------------------------------
// NPP_Shutdown:
//------------------------------------------------------------------------------------
void NPP_Shutdown(void)
{
	ShutdownNetscapePlugin();
}


//------------------------------------------------------------------------------------
// NPP_New:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_New(NPMIMEType pluginType,
				NPP instance,
				uint16 mode,
				int16 argc,
				char* argn[],
				char* argv[],
				NPSavedData* saved)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
														// Had to perform the (const char *[]) casts
														// because MSVC++ is retarded.
	CPluginArguments* theArgs = new CPluginArguments( argc, (const char **)argn, (const char **)argv );

	CNetscapePlugin* thePlugin = CreateNetscapePlugin( instance, mode, theArgs, saved );
	
	if( thePlugin == 0 )
		return NPERR_OUT_OF_MEMORY_ERROR;
	
	return NPERR_NO_ERROR;

}




//------------------------------------------------------------------------------------
// NPP_Destroy:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_Destroy(NPP instance, NPSavedData** save)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
		
	CNetscapePlugin* thePlugin = (CNetscapePlugin*) instance->pdata;
	if (thePlugin == 0)
		return NPERR_INVALID_PLUGIN_ERROR;
		
	NPError result = thePlugin->SaveData( save );
	delete thePlugin;
	
	return result;
}




//------------------------------------------------------------------------------------
// NPP_SetWindow:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_SetWindow(NPP instance, NPWindow* window)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	CNetscapePlugin* thePlugin = (CNetscapePlugin*) instance->pdata;
	if( thePlugin == 0 )
		return NPERR_INVALID_PLUGIN_ERROR;
	
	return thePlugin->SetWindow( window );
}



//------------------------------------------------------------------------------------
// NPP_NewStream:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_NewStream(NPP instance,
							NPMIMEType type,
							NPStream *stream, 
							NPBool seekable,
							uint16 *stype)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
				
	CNetscapePlugin* controller = (CNetscapePlugin*) instance->pdata;
	
	CNetscapeStream* theStream = controller->CreateStream(type, stream, seekable, *stype );
	
	if( theStream == 0 )
		return NPERR_OUT_OF_MEMORY_ERROR;
		
	*stype = theStream->GetStreamType();
	
	return NPERR_NO_ERROR;
}


//------------------------------------------------------------------------------------
// NPP_WriteReady:
//------------------------------------------------------------------------------------
int32 NP_LOADDS
NPP_WriteReady(NPP instance, NPStream *stream)
{
	if (instance == NULL)
		return -1;

	CNetscapeStream* theStream = CNetscapeStream::EvolveStream( stream );	
	if( theStream == 0 )
		return -1;
	
	return theStream->WriteReady(); 
}



//------------------------------------------------------------------------------------
// NPP_Write:
//------------------------------------------------------------------------------------
int32 NP_LOADDS
NPP_Write(NPP instance, NPStream *stream, int32 offset, int32 len, void *buffer)
{
	if (instance == NULL)
		return -1;
	
	CNetscapeStream* theStream = CNetscapeStream::EvolveStream( stream );	
	if( theStream == 0 )
		return -1;
		
	return theStream->Write( offset, len, buffer );
}



//------------------------------------------------------------------------------------
// NPP_DestroyStream:
//------------------------------------------------------------------------------------
NPError NP_LOADDS
NPP_DestroyStream(NPP instance, NPStream *stream, NPError reason)
{
	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
		
	CNetscapeStream* theStream = CNetscapeStream::EvolveStream( stream );
	if( theStream == 0 )
		return NPERR_GENERIC_ERROR;
	
	NPError retErr = theStream->Finish( reason );		
	delete theStream;
	
	return retErr;
}


//------------------------------------------------------------------------------------
// NPP_StreamAsFile:
//------------------------------------------------------------------------------------
void NP_LOADDS
NPP_StreamAsFile(NPP instance, NPStream *stream, const char* fname)
{
	if (instance == NULL)
		return;
		
	CNetscapeStream* theStream = CNetscapeStream::EvolveStream( stream );	
	if( theStream == 0 )
		return;

	theStream->StreamAsFile( fname );
}



//------------------------------------------------------------------------------------
// NPP_Print:
//------------------------------------------------------------------------------------
void NP_LOADDS
NPP_Print(NPP instance, NPPrint* printInfo)
{
    if(printInfo == NULL)   // trap invalid parm
        return;

	if (instance != NULL)
	{
		CNetscapePlugin* This = (CNetscapePlugin*) instance->pdata;
		This->Print( printInfo );
	}

}


//------------------------------------------------------------------------------------
// NPP_HandleEvent:
// Mac-only.
//------------------------------------------------------------------------------------
int16 NPP_HandleEvent(NPP instance, void* event)
{
	NPBool eventHandled = FALSE;
	if (instance == NULL)
		return eventHandled;
		
	CNetscapePlugin* This = (CNetscapePlugin*) instance->pdata;
	if( This )
		eventHandled = This->Handle_Event( event );
	
	return eventHandled;
}

//------------------------------------------------------------------------------------
// NPP_URLNotify:
//------------------------------------------------------------------------------------
void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
	if( instance != NULL )
	{
		//
	}
}


//------------------------------------------------------------------------------------
// NPP_GetJavaClass:
//------------------------------------------------------------------------------------
jref NPP_GetJavaClass(void)
{

	return InitializeJavaClass();
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//	Object Allocation Methods
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//======================================================================
//		CNetscapePlugin::CNetscapePlugin()
//======================================================================

CNetscapePlugin::CNetscapePlugin( NPP instance, uint16 mode, CPluginArguments* adoptedArgs )
:	mMode( mode ),
	mArgs( adoptedArgs ),
	mView( 0 )
{
	mNavigator = new CNavigator( instance );
	instance->pdata = (void*) this;
}

//======================================================================
//		CNetscapePlugin::~CNetscapePlugin()
//======================================================================

CNetscapePlugin::~CNetscapePlugin()
{
	delete mArgs;
	delete mView;
	delete mNavigator;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
//	Object Interface Methods
//
//	These methods are called by the procedural methods above. They take care of basic housekeeping,
//	such as keeping track of streams and windows, then notify any inherited classes through the
//	virtual Handle_*() member functions.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//------------------------------------------------------------------------------------
// CNetscapePlugin::SaveData
//
// Override this method to save critical plugin data in the NPSavedData structure. This
// Data can then be restored in CreateNetscapePlugin.
//------------------------------------------------------------------------------------
NPError
CNetscapePlugin::SaveData( NPSavedData** ) 
{
	return NPERR_NO_ERROR;
}

//------------------------------------------------------------------------------------
// CNetscapePlugin::SetWindow
//
// In general, you should not override CNetscapePlugin::SetWindow. Instead, you should
// override the CPluginView::SetWindow method in your view class.
//------------------------------------------------------------------------------------
NPError	
CNetscapePlugin::SetWindow( NPWindow* window )
{	
	if( mView == 0 )
	{
		mView = CreatePluginView( );
	}
	
	if( mView == 0 ) {
		return NPERR_OUT_OF_MEMORY_ERROR;
	}
	
	NPError result = mView->SetWindow( window );
	return result;
}


//------------------------------------------------------------------------------------
// CNetscapePlugin::Print
// 
// In general, you should not override this method. Instead, override
// CNetscapePlugin::PrintFull for full-page printing, and CtscapePlugin::PrintEmbeded
// for embedded printing.
//------------------------------------------------------------------------------------
void
CNetscapePlugin::Print( NPPrint* printInfo )
{
    if(printInfo == NULL)   // trap invalid parm
        return;

	if (printInfo->mode == NP_FULL)
	{
		NPBool printResult = PrintFull( printInfo->print.fullPrint );
		printInfo->print.fullPrint.pluginPrinted = printResult; // Do the default
	}
	else	// If not fullscreen, we must be embedded
	{
		PrintEmbeded( printInfo->print.embedPrint );
	}

}

//------------------------------------------------------------------------------------
// CNetscapePlugin::PrintFull
//------------------------------------------------------------------------------------
NPBool
CNetscapePlugin::PrintFull( NPFullPrint& fullPrintInfo ) 
{
	return FALSE;
}

//------------------------------------------------------------------------------------
// CNetscapePlugin::PrintEmbeded
//------------------------------------------------------------------------------------
void
CNetscapePlugin::PrintEmbeded( NPEmbedPrint& embedPrintInfo ) 
{
}

//------------------------------------------------------------------------------------
// CNetscapePlugin::Handle_Event
//
// Only Mac plugins need override this method. Note that event can be cast to
// (EventRecord*)
//------------------------------------------------------------------------------------
NPBool 
CNetscapePlugin::Handle_Event( void* event)
{
	return FALSE;
}


//------------------------------------------------------------------------------------
// CNetscapePlugin::CreateStream
//
// Override this method to associate new streams with your stream-handling classes.
//------------------------------------------------------------------------------------
CNetscapeStream*
CNetscapePlugin::CreateStream( NPMIMEType type, NPStream *stream, NPBool seekable, uint16 stype )
{
	return new CNetscapeStream( type, stream, seekable, stype );
}

//------------------------------------------------------------------------------------
// CNetscapePlugin::CreatePluginView
//
// Override this method to associate your plugin with a view class.
//------------------------------------------------------------------------------------
CPluginView*
CNetscapePlugin::CreatePluginView( )
{
	return new CPluginView( this );
}
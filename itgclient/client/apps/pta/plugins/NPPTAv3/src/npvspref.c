/* -*- Mode: C; tab-width: 4; -*- */
/*******************************************************************************
 * npsimple.c
 ******************************************************************************
 * Simple LiveConnect Sample Plugin
 * Copyright (c) 1996 Netscape Communications. All rights reserved.
 ******************************************************************************
 * OVERVIEW
 * --------
 * Section 1 - Includes
 * Section 2 - Instance Structs
 * Section 3 - API Plugin Implementations
 * Section 4 - Java Native Method Implementations
 * Section 5 - Utility Method Implementations
 *******************************************************************************/


/*******************************************************************************
 * SECTION 1 - Includes
 ******************************************************************************/
#ifdef _WINDOWS
#define _WIN32_WINNT 0x0400
#endif

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <tchar.h>
#include "npapi.h"
/*------------------------------------------------------------------------------
 * Define IMPLEMENT_Simple before including Simple.h to state that we're
 * implementing the native methods of this plug-in here, and consequently
 * need to access it's protected and private memebers.
 *----------------------------------------------------------------------------*/

#define IMPLEMENT_VSPTAv3
#include "VSPTAv3.h"
#include "netscape_plugin_Plugin.h"
#include "java_util_Date.h"
#include "java_lang_StringBuffer.h"
#include "java_lang_reflect_Array.h"

//#include "Simple.h"
#include "global.h"


/*------------------------------------------------------------------------------
 * Windows Includes
 *----------------------------------------------------------------------------*/
#ifdef _WINDOWS /* Windows Includes */
#include "windows.h"
#include "wincrypt.h"

#define COBJMACROS

#include "oaidl.h"

//#include "ptav3.h"
//#include "roamprefs.h"
//#include "seldigid.h"
//#include "srchcrit.h"
//#include "uiprefs.h"
//#include "profmgmt.h"
//#include "certprefs.h"
#include "XEnrollWrap.h"
//#include "roots.h"

//#include "ConfigChk.h"
//#include "cnfchkwrap.h"

//#include "VSImport.h"
#include "VSImportWrap.h"

#include "vscertprefswrap.h"
#include "vsprofmgmtwrap.h"
#include "vsptawrap.h"
#include "vsroamprefswrap.h"
#include "vsselecteddigidwrap.h"
#include "vssrchcritwrap.h"
#include "vsuiprefswrap.h"
#include "vsptadllapiwrap.h"
#include "addrootswrap.h"
#include "p12wrap.h"
#include "vsdnzwrap.h"
//#include "addrootswrap.h"

#endif /* _WINDOWS */


unsigned long _lastErrCode;
LPSTR	szHostName;
LPSTR	szProtocol;
LPSTR	szUAgent = NULL;

/*------------------------------------------------------------------------------
 * UNIX includes
 *----------------------------------------------------------------------------*/
#ifdef XP_UNIX
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#endif /* XP_UNIX */



/*******************************************************************************
 * SECTION 2 - Instance Structs
 *******************************************************************************
 * Instance state information about the plugin.
 *
 * PLUGIN DEVELOPERS:
 *	Use this struct to hold per-instance information that you'll
 *	need in the various functions in this file.
 ******************************************************************************
 * First comes the PlatformInstance struct, which contains platform specific
 * information for each instance.
 *****************************************************************************/
 
/*------------------------------------------------------------------------------
 * Windows PlatformInstance
 *----------------------------------------------------------------------------*/
#ifdef XP_PC
typedef struct _PlatformInstance
{
	HWND			fhWnd ;
	WNDPROC			fDefaultWindowProc;
	ICEnroll*		pEnroll;
	//IConfigChkr*	pCnfChk;
	IImpPKCS12*		pImport;
	IVSRootsUpdate*	pAddRoots;

	// pta v2 interfaces
	IVSUIPrefs*     pUIPrefs;
	IVSProfMgmt*    pProfMgmt;
	IVSCertPrefs*   pCertPrefs;
	IVSSrchCrit*    pSrchCrit;
	IVSSelectedDigID* pSelectedDigID;
	IVSP12Import*   pP12Import;
	IVSP12Export*   pP12Export;
	IVSRoamPrefs*   pRoamPrefs;
	IVSPTA*         pPTA;
	IVSPTADllApi*    pPTAApi;

	// Digital Notarization interfaces
	IVSNZ*			pVSNZ;
	IVSNZUIPrefs*	pNZUIPrefs;
	IVSNZAppPrefs*	pNZAppPrefs;

	BOOL            boolXenrollInitialized;
	BOOL            boolImportInitialized;
	BOOL			boolAddRootsInitialized;
} PlatformInstance;

#define		NZ_CLSID		"d66256e2-b99c-11d4-8c74-0010830169af"

NPError InitControls(PlatformInstance* fPlatform, const char* pControlClsid);

#endif /* XP_PC */
/*------------------------------------------------------------------------------
 * UNIX PlatformInstance
 *----------------------------------------------------------------------------*/
#ifdef XP_UNIX
typedef struct _PlatformInstance
{
    Window 			window;
    Display *		display;
    uint32 			x, y;
    uint32 			width, height;
} PlatformInstance;
#endif /* XP_UNIX */
/*------------------------------------------------------------------------------
 * Macintosh PlatformInstance
 *----------------------------------------------------------------------------*/
#ifdef XP_MAC
typedef struct _PlatformInstance
{
	int				placeholder;
} PlatformInstance;
#endif /* macintosh */
/*------------------------------------------------------------------------------
 * Cross-Platform PluginInstance
 *----------------------------------------------------------------------------*/
typedef struct _PluginInstance
{
	NPWindow*			fWindow;
	uint16				fMode;
	PlatformInstance	fPlatform;
} PluginInstance;


/******************************************************************************
 * Method Declarations
 ******************************************************************************/
void		PlatformNew( PluginInstance* This );
NPError		PlatformDestroy( PluginInstance* This );
NPError		PlatformSetWindow( PluginInstance* This, NPWindow* window );
int16		PlatformHandleEvent( PluginInstance* This, void* event );


/*******************************************************************************
 * SECTION 3 - API Plugin Implementations
 ******************************************************************************/
 
/*------------------------------------------------------------------------------
 * UNIX-only API calls
 *----------------------------------------------------------------------------*/
#ifdef XP_UNIX
/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_GetMIMEDescription:
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
char* NPP_GetMIMEDescription(void)
{
	return("application/x-simple-plugin:smp:Simple LiveConnect Sample Plug-in");
}

#define PLUGIN_NAME			"Simple LiveConnect Sample Plug-in"
#define PLUGIN_DESCRIPTION	"Demonstrates a simple LiveConnected plug-in."
/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_GetValue:
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
NPP_GetValue(void *future, NPPVariable variable, void *value)
{
    NPError err = NPERR_NO_ERROR;
    if (variable == NPPVpluginNameString)
		*((char **)value) = PLUGIN_NAME;
    else if (variable == NPPVpluginDescriptionString)
		*((char **)value) = PLUGIN_DESCRIPTION;
    else
		err = NPERR_GENERIC_ERROR;

    return err;
}
#endif /* XP_UNIX */

/*------------------------------------------------------------------------------
 * Cross-Platform Plug-in API Calls
 *----------------------------------------------------------------------------*/
 
/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Initialize:
 * Provides global initialization for a plug-in, and returns an error value. 
 *
 * This function is called once when a plug-in is loaded, before the first instance
 * is created. You should allocate any memory or resources shared by all
 * instances of your plug-in at this time. After the last instance has been deleted,
 * NPP_Shutdown will be called, where you can release any memory or
 * resources allocated by NPP_Initialize. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
NPP_Initialize(void)
{
	
#ifdef XP_PC
	if(CoInitialize(NULL) == RPC_E_CHANGED_MODE )
	{
		return NPERR_GENERIC_ERROR; 
	}
	_lastErrCode = 0;
#endif 
	szHostName = NULL;
	szProtocol = NULL;
	szUAgent = NULL;
    return NPERR_NO_ERROR; 
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_GetJavaClass:
 * New in Netscape Navigator 3.0. 
 *
 * NPP_GetJavaClass is called during initialization to ask your plugin
 * what its associated Java class is. If you don't have one, just return
 * NULL. Otherwise, use the javah-generated "use_" function to both
 * initialize your class and return it. If you can't find your class, an
 * error will be signalled by "use_" and will cause the Navigator to
 * complain to the user.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
jref
NPP_GetJavaClass(void)
{
	struct java_lang_Class* myClass;
	JRIEnv* env = NPN_GetJavaEnv();
	if (env == NULL)
		return NULL;		/* Java disabled */
 
	myClass = use_VSPTAv3(env);
	use_java_lang_StringBuffer(env);
	use_netscape_plugin_Plugin( env );
	use_java_util_Date(env);
	use_java_lang_reflect_Array (env);
	//use_Simple(env);
	//return myClass;
	return myClass;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Shutdown:
 * Provides global deinitialization for a plug-in. 
 * 
 * This function is called once after the last instance of your plug-in is destroyed.
 * Use this function to release any memory or resources shared across all
 * instances of your plug-in. You should be a good citizen and declare that
 * you're not using your java class any more. This allows java to unload
 * it, freeing up memory.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
NPP_Shutdown(void)
{
	JRIEnv* env = NPN_GetJavaEnv(); 
//	CoUninitialize();	
	if (env) {
		unuse_VSPTAv3(env);
		unuse_netscape_plugin_Plugin( env );
		unuse_java_util_Date(env);
		unuse_java_lang_StringBuffer(env);
		unuse_java_lang_reflect_Array(env);		
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_New:
 * Creates a new instance of a plug-in and returns an error value. 
 * 
 * NPP_New creates a new instance of your plug-in with MIME type specified
 * by pluginType. The parameter mode is NP_EMBED if the instance was created
 * by an EMBED tag, or NP_FULL if the instance was created by a separate file.
 * You can allocate any instance-specific private data in instance->pdata at this
 * time. The NPP pointer is valid until the instance is destroyed. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError 
NPP_New(NPMIMEType pluginType,
	NPP instance,
	uint16 mode,
	int16 argc,
	char* argn[],
	char* argv[],
	NPSavedData* saved)
{
	
	NPError result = NPERR_NO_ERROR;
	PluginInstance* This;
	JRIEnv* env = NPN_GetJavaEnv();
	char* pControlClsid = NULL;
	int i;
	
	if (instance == NULL) {
		return NPERR_INVALID_INSTANCE_ERROR;
	}
	instance->pdata = NPN_MemAlloc(sizeof(PluginInstance));
	This = (PluginInstance*) instance->pdata;
	if (This == NULL) {
	    return NPERR_OUT_OF_MEMORY_ERROR;
	}
	/* mode is NP_EMBED, NP_FULL, or NP_BACKGROUND (see npapi.h) */
	This->fWindow = NULL;
	This->fMode = mode;
	
	PlatformNew( This ); 	/* Call Platform-specific initializations */
#ifdef XP_PC

	for(i = 0; i < argc; i++)
	{
		if(stricmp(argn[i], "CLSID") == 0)
		{
			pControlClsid = argv[i];
			break;
		}
	}

	result = InitControls(&(This->fPlatform), pControlClsid);

	/*This->fPlatform.boolXenrollInitialized = TRUE;
    This->fPlatform.boolImportInitialized = TRUE;
	This->fPlatform.boolAddRootsInitialized = TRUE;
	if ((This->fPlatform.pPTA = PTA_CreateInstance()) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0001","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	}
	else if((This->fPlatform.pCertPrefs = CertPrefs_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0002","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if ((This->fPlatform.pPTAApi = PTADllApi_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0009","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;		
	}
	else if ((This->fPlatform.pProfMgmt = ProfMgmt_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0004","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((This->fPlatform.pRoamPrefs = RoamPrefs_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0005","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((This->fPlatform.pSelectedDigID = SelectedDigID_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0006","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((This->fPlatform.pSrchCrit = SrchCrit_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0007","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((This->fPlatform.pUIPrefs = UIPrefs_GetInstance(This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0008","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;	
	}
	else if((This->fPlatform.pP12Import = P12Import_GetInstance (This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0009","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;	
	}
	else if((This->fPlatform.pP12Export = P12Export_GetInstance (This->fPlatform.pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x000A","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;	
	}
	else {
		if((This->fPlatform.pEnroll = Enroll_CreateInstance()) == NULL) {
			This->fPlatform.boolXenrollInitialized = FALSE;
			This->fPlatform.pEnroll = NULL;
		}
    
		if((This->fPlatform.pImport = Import_CreateInstance()) == NULL) {
			This->fPlatform.pImport = NULL;
			This->fPlatform.boolImportInitialized = FALSE;
		}
	
		if ((This->fPlatform.pAddRoots = AddRoots_CreateInstance()) == NULL) {
			This->fPlatform.boolAddRootsInitialized = FALSE;
			This->fPlatform.pAddRoots = NULL;
		}
	}
*/
#endif

		/* PLUGIN DEVELOPERS:
		 *	Initialize fields of your plugin
		 *	instance data here.  If the NPSavedData is non-
		 *	NULL, you can use that data (returned by you from
		 *	NPP_Destroy to set up the new plugin instance).
		 */


	//Call NPN_GetURL to obtain the address of the current page
	NPN_GetURL(instance, "javascript:document.location;", NULL) ;

	return result;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Destroy:
 * Deletes a specific instance of a plug-in and returns an error value. 
 * NPP_Destroy is called when a plug-in instance is deleted, typically because the
 * user has left the page containing the instance, closed the window, or quit the
 * application. You should delete any private instance-specific information stored
 * in instance->pdata. If the instance being deleted is the last instance created
 * by your plug-in, NPP_Shutdown will subsequently be called, where you can
 * delete any data allocated in NPP_Initialize to be shared by all your plug-in's
 * instances. Note that you should not perform any graphics operations in
 * NPP_Destroy as the instance's window is no longer guaranteed to be valid. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError 
NPP_Destroy(NPP instance, NPSavedData** save)
{
	PluginInstance* This;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	This = (PluginInstance*) instance->pdata;
	PlatformDestroy( This ); /* Perform platform specific cleanup */

#ifdef XP_PC
	//This->fPlatform.pVSPTAv3Obj->Release();
#endif
	/* PLUGIN DEVELOPERS:
	 *	If desired, call NP_MemAlloc to create a
	 *	NPSavedDate structure containing any state information
	 *	that you want restored if this plugin instance is later
	 *	recreated.
	 */

	if (This != NULL) {
		NPN_MemFree(instance->pdata);
		instance->pdata = NULL;
	}

	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_SetWindow:
 * Sets the window in which a plug-in draws, and returns an error value. 
 * 
 * NPP_SetWindow informs the plug-in instance specified by instance of the
 * the window denoted by window in which the instance draws. This NPWindow
 * pointer is valid for the life of the instance, or until NPP_SetWindow is called
 * again with a different value. Subsequent calls to NPP_SetWindow for a given
 * instance typically indicate that the window has been resized. If either window
 * or window->window are NULL, the plug-in must not perform any additional
 * graphics operations on the window and should free any resources associated
 * with the window. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError 
NPP_SetWindow(NPP instance, NPWindow* window)
{
	NPError result = NPERR_NO_ERROR;
	PluginInstance* This;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR; 

	This = (PluginInstance*) instance->pdata;

	/*
	 * PLUGIN DEVELOPERS:
	 *	Before setting window to point to the
	 *	new window, you may wish to compare the new window
	 *	info to the previous window (if any) to note window
	 *	size changes, etc.
	 */
	result = PlatformSetWindow( This, window );
	
	This->fWindow = window;
	return result;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_NewStream:
 * Notifies an instance of a new data stream and returns an error value. 
 * 
 * NPP_NewStream notifies the instance denoted by instance of the creation of
 * a new stream specifed by stream. The NPStream* pointer is valid until the
 * stream is destroyed. The MIME type of the stream is provided by the
 * parameter type. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError 
NPP_NewStream(NPP instance,
	      NPMIMEType type,
	      NPStream *stream, 
	      NPBool seekable,
	      uint16 *stype)
{
	PluginInstance* This;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	This = (PluginInstance*) instance->pdata;

	return NPERR_NO_ERROR;
}


/* PLUGIN DEVELOPERS:
 *	These next 2 functions are directly relevant in a plug-in which
 *	handles the data in a streaming manner. If you want zero bytes
 *	because no buffer space is YET available, return 0. As long as
 *	the stream has not been written to the plugin, Navigator will
 *	continue trying to send bytes.  If the plugin doesn't want them,
 *	just return some large number from NPP_WriteReady(), and
 *	ignore them in NPP_Write().  For a NP_ASFILE stream, they are
 *	still called but can safely be ignored using this strategy.
 */

int32 STREAMBUFSIZE = 0X0FFFFFFF; /* If we are reading from a file in NPAsFile
								   * mode so we can take any size stream in our
								   * write call (since we ignore it) */

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_WriteReady:
 * Returns the maximum number of bytes that an instance is prepared to accept
 * from the stream. 
 * 
 * NPP_WriteReady determines the maximum number of bytes that the
 * instance will consume from the stream in a subsequent call NPP_Write. This
 * function allows Netscape to only send as much data to the instance as the
 * instance is capable of handling at a time, allowing more efficient use of
 * resources within both Netscape and the plug-in. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
int32 
NPP_WriteReady(NPP instance, NPStream *stream)
{
	PluginInstance* This;
	if (instance != NULL)
		This = (PluginInstance*) instance->pdata;


	/* Number of bytes ready to accept in NPP_Write() */
	return STREAMBUFSIZE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Write:
 * Delivers data from a stream and returns the number of bytes written. 
 * 
 * NPP_Write is called after a call to NPP_NewStream in which the plug-in
 * requested a normal-mode stream, in which the data in the stream is delivered
 * progressively over a series of calls to NPP_WriteReady and NPP_Write. The
 * function delivers a buffer buf of len bytes of data from the stream identified
 * by stream to the instance. The parameter offset is the logical position of
 * buf from the beginning of the data in the stream. 
 * 
 * The function returns the number of bytes written (consumed by the instance).
 * A negative return value causes an error on the stream, which will
 * subsequently be destroyed via a call to NPP_DestroyStream. 
 * 
 * Note that a plug-in must consume at least as many bytes as it indicated in the
 * preceeding NPP_WriteReady call. All data consumed must be either processed
 * immediately or copied to memory allocated by the plug-in: the buf parameter
 * is not persistent. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
int32 
NPP_Write(NPP instance, NPStream *stream, int32 offset, int32 len, void *buffer)
{
	LPSTR szURL;
	LPSTR szptrTemp;
	int nProtocolSize;
	int nHostNameSize, nUAgent = 0;
	TCHAR* pUAgent = NULL;

	if (instance != NULL) {
		PluginInstance* This = (PluginInstance*) instance->pdata;
	}

	//The buffer contains the URL of the current page. 
	szURL = buffer;

	//Separate out the host name and the protocol
	if(szProtocol)
			free(szProtocol);
	szptrTemp = strtok(szURL,":");	
	if(szptrTemp)
	{	
		nProtocolSize = strlen(szptrTemp);
		szProtocol = (LPSTR)malloc(sizeof(char)*(nProtocolSize+1));
		strcpy(szProtocol,szptrTemp);
		szProtocol[nProtocolSize] = '\0';
	}
	else
	{
		szProtocol = NULL;
	}
	
	if(szHostName)
		free(szHostName);
	szptrTemp = szptrTemp + nProtocolSize + 3;
	szptrTemp = strtok(szptrTemp,":/");
	if(szptrTemp)
	{
		nHostNameSize = strlen(szptrTemp);
		szHostName = (LPSTR)malloc(sizeof(char)*(nHostNameSize+1));
		strcpy(szHostName,szptrTemp);
		szHostName[nHostNameSize] = '\0';
	}
	else
	{
		szHostName = NULL;
	}

	// Get the user agent string
	pUAgent = NPN_UserAgent(instance);

	if(szUAgent)
	{
		free(szUAgent);
		szUAgent = NULL;
	}

	if(pUAgent)
	{
		nUAgent = lstrlen(pUAgent);
		szUAgent = (LPSTR)malloc(sizeof(TCHAR)*(nUAgent+1));
		if(szUAgent)
		{
			lstrcpy(szUAgent, pUAgent);
			szUAgent[nUAgent] = '\0';
		}
	}

	//MessageBox(NULL,szHostName, "Message", MB_OK);
	return len;		/* The number of bytes accepted */
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_DestroyStream:
 * Indicates the closure and deletion of a stream, and returns an error value. 
 * 
 * The NPP_DestroyStream function is called when the stream identified by
 * stream for the plug-in instance denoted by instance will be destroyed. You
 * should delete any private data allocated in stream->pdata at this time. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError 
NPP_DestroyStream(NPP instance, NPStream *stream, NPError reason)
{
	PluginInstance* This;

	if (instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;
	This = (PluginInstance*) instance->pdata;

	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_StreamAsFile:
 * Provides a local file name for the data from a stream. 
 * 
 * NPP_StreamAsFile provides the instance with a full path to a local file,
 * identified by fname, for the stream specified by stream. NPP_StreamAsFile is
 * called as a result of the plug-in requesting mode NP_ASFILEONLY or
 * NP_ASFILE in a previous call to NPP_NewStream. If an error occurs while
 * retrieving the data or writing the file, fname may be NULL. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void 
NPP_StreamAsFile(NPP instance, NPStream *stream, const char* fname)
{
	PluginInstance* This;
	if (instance != NULL)
		This = (PluginInstance*) instance->pdata;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Print:
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void 
NPP_Print(NPP instance, NPPrint* printInfo)
{

	if(printInfo == NULL)
		return;

	if (instance != NULL) {
		PluginInstance* This = (PluginInstance*) instance->pdata;
	
		if (printInfo->mode == NP_FULL) {
		    /*
		     * PLUGIN DEVELOPERS:
		     *	If your plugin would like to take over
		     *	printing completely when it is in full-screen mode,
		     *	set printInfo->pluginPrinted to TRUE and print your
		     *	plugin as you see fit.  If your plugin wants Netscape
		     *	to handle printing in this case, set
		     *	printInfo->pluginPrinted to FALSE (the default) and
		     *	do nothing.  If you do want to handle printing
		     *	yourself, printOne is true if the print button
		     *	(as opposed to the print menu) was clicked.
		     *	On the Macintosh, platformPrint is a THPrint; on
		     *	Windows, platformPrint is a structure
		     *	(defined in npapi.h) containing the printer name, port,
		     *	etc.
		     */

			void* platformPrint =
				printInfo->print.fullPrint.platformPrint;
			NPBool printOne =
				printInfo->print.fullPrint.printOne;
			
			/* Do the default*/
			printInfo->print.fullPrint.pluginPrinted = FALSE;
		}
		else {	/* If not fullscreen, we must be embedded */
		    /*
		     * PLUGIN DEVELOPERS:
		     *	If your plugin is embedded, or is full-screen
		     *	but you returned false in pluginPrinted above, NPP_Print
		     *	will be called with mode == NP_EMBED.  The NPWindow
		     *	in the printInfo gives the location and dimensions of
		     *	the embedded plugin on the printed page.  On the
		     *	Macintosh, platformPrint is the printer port; on
		     *	Windows, platformPrint is the handle to the printing
		     *	device context.
		     */

			NPWindow* printWindow =
				&(printInfo->print.embedPrint.window);
			void* platformPrint =
				printInfo->print.embedPrint.platformPrint;
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_URLNotify:
 * Notifies the instance of the completion of a URL request. 
 * 
 * NPP_URLNotify is called when Netscape completes a NPN_GetURLNotify or
 * NPN_PostURLNotify request, to inform the plug-in that the request,
 * identified by url, has completed for the reason specified by reason. The most
 * common reason code is NPRES_DONE, indicating simply that the request
 * completed normally. Other possible reason codes are NPRES_USER_BREAK,
 * indicating that the request was halted due to a user action (for example,
 * clicking the "Stop" button), and NPRES_NETWORK_ERR, indicating that the
 * request could not be completed (for example, because the URL could not be
 * found). The complete list of reason codes is found in npapi.h. 
 * 
 * The parameter notifyData is the same plug-in-private value passed as an
 * argument to the corresponding NPN_GetURLNotify or NPN_PostURLNotify
 * call, and can be used by your plug-in to uniquely identify the request. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
	/* Not used in the Simple plugin. */
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_HandleEvent:
 * Mac-only, but stub must be present for Windows
 * Delivers a platform-specific event to the instance. 
 * 
 * On the Macintosh, event is a pointer to a standard Macintosh EventRecord.
 * All standard event types are passed to the instance as appropriate. In general,
 * return TRUE if you handle the event and FALSE if you ignore the event. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef XP_UNIX
int16
NPP_HandleEvent(NPP instance, void* event)
{
	PluginInstance* This;
	int16 eventHandled = FALSE;
	
	if (instance == NULL)
		return eventHandled;
	
	This = (PluginInstance*) instance->pdata;
	eventHandled = PlatformHandleEvent(This, event);
	return eventHandled;
}
#endif /* ndef XP_UNIX */
/*******************************************************************************/





/*******************************************************************************
 * SECTION 4 - Java Native Method Implementations
 ******************************************************************************/


/******************************************************************************
 * Native Method Implementations for CertPrefs interface 
 ******************************************************************************/



/*** public native set_CertPref_CertSerNum (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fCertSerNum(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CertPrefs_set_CertSerNum(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_CertPref_CertSerNum ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fCertSerNum(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = CertPrefs_get_CertSerNum(This->fPlatform.pCertPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_CertPref_CertIssDN (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fCertIssDN(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CertPrefs_set_CertIssDN(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_CertPref_CertIssDN ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fCertIssDN(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = CertPrefs_get_CertIssDN(This->fPlatform.pCertPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_CertPref_CertFrndlyName (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fCertFrndlyName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CertPrefs_set_CertFrndlyName(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_CertPref_CertFrndlyName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fCertFrndlyName(JRIEnv* env, struct VSPTAv3* self)
{
		struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = CertPrefs_get_CertFrndlyName(This->fPlatform.pCertPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_CertPref_CertLogoUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fCertLogoUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CertPrefs_set_CertLogoUrl(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_CertPref_CertLogoUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fCertLogoUrl(JRIEnv* env, struct VSPTAv3* self)
{
		struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = CertPrefs_get_CertLogoUrl(This->fPlatform.pCertPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_CertPref_CertDispString (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fCertDispString(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CertPrefs_set_CertDispString(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_CertPref_CertDispString ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fCertDispString(JRIEnv* env, struct VSPTAv3* self)
{
		struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = CertPrefs_get_CertDispString(This->fPlatform.pCertPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_CertPref_CertTextureUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fCertTextureUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CertPrefs_set_CertTextureUrl(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_CertPref_CertTextureUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fCertTextureUrl(JRIEnv* env, struct VSPTAv3* self)
{
		struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = CertPrefs_get_CertTextureUrl(This->fPlatform.pCertPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_CertPref_MarkAsRenewed (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fMarkAsRenewed(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL boolRenewed;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			boolRenewed = a;
			
			//Call our wrapper
			err = CertPrefs_set_MarkAsRenewed(This->fPlatform.pCertPrefs, boolRenewed);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_CertPref_MarkAsRenewed ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fCertPref_0005fMarkAsRenewed(JRIEnv* env, struct VSPTAv3* self)
{
	BOOL retVal = FALSE;
	BOOL boolRenewed;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = 0;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = 0;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((boolRenewed = CertPrefs_get_MarkAsRenewed(This->fPlatform.pCertPrefs)) == -1)
			{
				retVal = 0;
			}
			else
			{
				retVal = boolRenewed;
			}
		}
	}

	return retVal;
}

/*** public native set_CertPref_SetPreference (Ljava/lang/String;Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fCertPref_0005fSetPreference(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars, *stringCharsB;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL || b == NULL) 
	{ 
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			stringCharsB = (wchar_t*)JRI_GetStringChars(env, b);
			
			//Call our wrapper
			err = CertPrefs_set_CertPreference(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a), 
				stringCharsB, JRI_GetStringLength(env,b));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_CertPref_GetPreference (Ljava/lang/String;)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fCertPref_0005fGetPreference(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
		struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;
	wchar_t* stringChars;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			if((pwstrName = CertPrefs_get_CertPreference(This->fPlatform.pCertPrefs, stringChars, JRI_GetStringLength(env,a))) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/******************************************************************************
* SrchCrit methods
*******************************************************************************/


/*** public native set_SrchCrit_IssuerDN (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fIssuerDN(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = SrchCrit_set_IssuerDN(This->fPlatform.pSrchCrit, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_SrchCrit_IssuerDN ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSrchCrit_0005fIssuerDN(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SrchCrit_get_IssuerDN(This->fPlatform.pSrchCrit)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_SrchCrit_SubjectDN (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fSubjectDN(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = SrchCrit_set_SubjectDN(This->fPlatform.pSrchCrit, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_SrchCrit_SubjectDN ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSrchCrit_0005fSubjectDN(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SrchCrit_get_SubjectDN(This->fPlatform.pSrchCrit)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_SrchCrit_SerNum (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fSerNum(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = SrchCrit_set_SerNum(This->fPlatform.pSrchCrit, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_SrchCrit_SerNum ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSrchCrit_0005fSerNum(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SrchCrit_get_SerNum(This->fPlatform.pSrchCrit)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_SrchCrit_Email (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fEmail(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = SrchCrit_set_Email(This->fPlatform.pSrchCrit, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_SrchCrit_Email ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSrchCrit_0005fEmail(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SrchCrit_get_Email(This->fPlatform.pSrchCrit)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_SrchCrit_ExpDate (Ljava/util/Date;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fExpDate(JRIEnv* env, struct VSPTAv3* self, struct java_util_Date *a)
{
	unsigned int retVal = VS_NO_ERROR;
	SYSTEMTIME sysTime;
	DATE dateExpDate;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Create DATE
			sysTime.wDayOfWeek = (short)	(env,a);
			sysTime.wMilliseconds = 0;
			sysTime.wHour = (short)java_util_Date_getHours(env,a);
			sysTime.wMinute = (short)java_util_Date_getMinutes(env,a);
			sysTime.wSecond = (short)java_util_Date_getSeconds(env,a);
			sysTime.wYear = (short)java_util_Date_getYear(env,a) + 1900;
			sysTime.wMonth = (short)java_util_Date_getMonth(env,a) + 1;
			sysTime.wDay = (short)java_util_Date_getDate(env,a);

			SystemTimeToVariantTime(&sysTime, &dateExpDate);
			
			//Call our wrapper
			err = SrchCrit_set_ExpDate(This->fPlatform.pSrchCrit, dateExpDate);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;

}

/*** public native get_SrchCrit_ExpDate ()Ljava/util/Date; ***/
extern JRI_PUBLIC_API(struct java_util_Date *)
native_VSPTAv3_get_0005fSrchCrit_0005fExpDate(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_util_Date* retVal = NULL;
	DATE a;
	SYSTEMTIME sysTime;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((a = SrchCrit_get_ExpDate(This->fPlatform.pSrchCrit)) == -1)
			{
				retVal = NULL;
			}
			else
			{
				VariantTimeToSystemTime(a, &sysTime);
				retVal = java_util_Date_new(env, class_java_util_Date(env));
				java_util_Date_setYear(env,retVal,sysTime.wYear - 1900);
				java_util_Date_setMonth(env,retVal,sysTime.wMonth-1);
				java_util_Date_setDate(env,retVal,sysTime.wDay);
			}
		}
	}

	return retVal;
}

/*** public native set_SrchCrit_EffDate (Ljava/util/Date;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fEffDate(JRIEnv* env, struct VSPTAv3* self, struct java_util_Date *a)
{
	unsigned int retVal = VS_NO_ERROR;
	SYSTEMTIME sysTime;
	DATE dateExpDate;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Create DATE
			sysTime.wDayOfWeek = (short)java_util_Date_getDay(env,a);
			sysTime.wMilliseconds = 0;
			sysTime.wHour = (short)java_util_Date_getHours(env,a);
			sysTime.wMinute = (short)java_util_Date_getMinutes(env,a);
			sysTime.wSecond = (short)java_util_Date_getSeconds(env,a);
			sysTime.wYear = (short)java_util_Date_getYear(env,a) + 1900;
			sysTime.wMonth = (short)java_util_Date_getMonth(env,a) + 1;
			sysTime.wDay = (short)java_util_Date_getDate(env,a);

			SystemTimeToVariantTime(&sysTime, &dateExpDate);
			
			//Call our wrapper
			err = SrchCrit_set_EffDate(This->fPlatform.pSrchCrit, dateExpDate);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;

}

/*** public native get_SrchCrit_EffDate ()Ljava/util/Date; ***/
extern JRI_PUBLIC_API(struct java_util_Date *)
native_VSPTAv3_get_0005fSrchCrit_0005fEffDate(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_util_Date* retVal = NULL;
	DATE a;
	SYSTEMTIME sysTime;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((a = SrchCrit_get_EffDate(This->fPlatform.pSrchCrit)) == -1)
			{
				retVal = NULL;
			}
			else
			{
				VariantTimeToSystemTime(a, &sysTime);
				retVal = java_util_Date_new(env, class_java_util_Date(env));
				java_util_Date_setYear(env,retVal,sysTime.wYear - 1900);
				java_util_Date_setMonth(env,retVal,sysTime.wMonth-1);
				java_util_Date_setDate(env,retVal,sysTime.wDay);
			}
		}
	}

	return retVal;
}

/*** public native set_SrchCrit_DateEquality (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fDateEquality(JRIEnv* env, struct VSPTAv3* self, jshort a)
{
	unsigned int retVal = VS_NO_ERROR;
	short wDateEq;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			wDateEq = a;

			//Call our wrapper
			err = SrchCrit_set_DateEquality(This->fPlatform.pSrchCrit, wDateEq);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_SrchCrit_DateEquality ()I ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fSrchCrit_0005fDateEquality(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	short wDateEq;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((wDateEq = SrchCrit_get_DateEquality(This->fPlatform.pSrchCrit)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = wDateEq;
			}
		}
	}

	return retVal;
}


/*** public native set_SrchCrit_Renewed (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fRenewed(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL boolRenewed;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			boolRenewed = a;

			//Call our wrapper
			err = SrchCrit_set_Renewed(This->fPlatform.pSrchCrit, boolRenewed);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_SrchCrit_Renewed ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fSrchCrit_0005fRenewed(JRIEnv* env, struct VSPTAv3* self)
{
	BOOL retVal = -1;
	BOOL boolRenewed;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((boolRenewed = SrchCrit_get_Renewed(This->fPlatform.pSrchCrit)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = boolRenewed;
			}
		}
	}

	return retVal;
}

/*** public native set_SrchCrit_KeyUsage (S)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fKeyUsage(JRIEnv* env, struct VSPTAv3* self, jshort a)
{
	unsigned int retVal = VS_NO_ERROR;
	short keyUsage;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			keyUsage = a;

			//Call our wrapper
			err = SrchCrit_set_KeyUsage(This->fPlatform.pSrchCrit, keyUsage);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_SrchCrit_KeyUsage ()S ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fSrchCrit_0005fKeyUsage(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	short keyUsage;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((keyUsage = SrchCrit_get_KeyUsage(This->fPlatform.pSrchCrit)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = keyUsage;
			}
		}
	}

	return retVal;
}


/*** public native set_SrchCrit_KeySize (S)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fKeySize(JRIEnv* env, struct VSPTAv3* self, jshort a)
{
	unsigned int retVal = VS_NO_ERROR;
	short keySize;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			keySize = a;

			//Call our wrapper
			err = SrchCrit_set_KeySize(This->fPlatform.pSrchCrit, keySize);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_SrchCrit_KeySize ()S ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fSrchCrit_0005fKeySize(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	short keySize;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((keySize = SrchCrit_get_KeySize(This->fPlatform.pSrchCrit)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = keySize;
			}
		}
	}

	return retVal;
}



/*** public native set_SrchCrit_ExtOID (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fExtOID(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = SrchCrit_set_ExtOID(This->fPlatform.pSrchCrit, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_SrchCrit_ExtOID ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSrchCrit_0005fExtOID(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SrchCrit_get_ExtOID(This->fPlatform.pSrchCrit)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_SrchCrit_ExtVal (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fSrchCrit_0005fExtVal(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = SrchCrit_set_ExtVal(This->fPlatform.pSrchCrit, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_SrchCrit_ExtVal ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSrchCrit_0005fExtVal(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SrchCrit_get_ExtVal(This->fPlatform.pSrchCrit)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/******************************************************************************
* SelectedDigID methods
*******************************************************************************/

/*** public native get_SelectedDigID_IssuerDN ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fIssuerDN(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_IssuerDN(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native get_SelectedDigID_SubjectDN ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fSubjectDN(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_SubjectDN(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native get_SelectedDigID_SerNum ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fSerNum(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_SerNum(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native get_SelectedDigID_ExpDate ()Ljava/util/Date; ***/
extern JRI_PUBLIC_API(struct java_util_Date *)
native_VSPTAv3_get_0005fSelectedDigID_0005fExpDate(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_util_Date* retVal = NULL;
	DATE a;
	SYSTEMTIME sysTime;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((a = SelectedDigID_get_ExpDate(This->fPlatform.pSelectedDigID)) == -1)
			{
				retVal = NULL;
			}
			else
			{
				VariantTimeToSystemTime(a, &sysTime);
				retVal = java_util_Date_new(env, class_java_util_Date(env));
				java_util_Date_setYear(env,retVal,sysTime.wYear - 1900);
				java_util_Date_setMonth(env,retVal,sysTime.wMonth-1);
				java_util_Date_setDate(env,retVal,sysTime.wDay);
			}
		}
	}

	return retVal;
}

/*** public native get_SelectedDigID_EffDate ()Ljava/util/Date; ***/
extern JRI_PUBLIC_API(struct java_util_Date *)
native_VSPTAv3_get_0005fSelectedDigID_0005fEffDate(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_util_Date* retVal = NULL;
	DATE a;
	SYSTEMTIME sysTime;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((a = SelectedDigID_get_EffDate(This->fPlatform.pSelectedDigID)) == -1)
			{
				retVal = NULL;
			}
			else
			{
				VariantTimeToSystemTime(a, &sysTime);
				retVal = java_util_Date_new(env, class_java_util_Date(env));
				java_util_Date_setYear(env,retVal,sysTime.wYear - 1900);
				java_util_Date_setMonth(env,retVal,sysTime.wMonth-1);
				java_util_Date_setDate(env,retVal,sysTime.wDay);
			}
		}
	}

	return retVal;
}


/*** public native get_SelectedDigID_KeyUsage ()I ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fSelectedDigID_0005fKeyUsage(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	short keyUsage;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((keyUsage = SelectedDigID_get_KeyUsage(This->fPlatform.pSelectedDigID)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = keyUsage;
			}
		}
	}

	return retVal;
}

/*** public native get_SelectedDigID_KeySize ()I ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fSelectedDigID_0005fKeySize(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	short keySize;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((keySize = SelectedDigID_get_KeySize(This->fPlatform.pSelectedDigID)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = keySize;
			}
		}
	}

	return retVal;
}

/*** public native get_SelectedDigID_Renewed ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fSelectedDigID_0005fRenewed(JRIEnv* env, struct VSPTAv3* self)
{
	BOOL retVal = -1;
	BOOL boolRenewed;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((boolRenewed = SelectedDigID_get_Renewed(This->fPlatform.pSelectedDigID)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = boolRenewed;
			}
		}
	}

	return retVal;
}

/*** public native get_SelectedDigID_PubKeyMD5 ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fPubKeyMD5(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_PubKeyMD5(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native get_SelectedDigID_PubKeySHA1 ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fPubKeySHA1(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_PubKeySHA1(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native get_SelectedDigID_FrndlyName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fFrndlyName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_FrndlyName(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native get_SelectedDigID_LogoUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fLogoUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_LogoUrl(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native get_SelectedDigID_TextureUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fSelectedDigID_0005fTextureUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = SelectedDigID_get_TextureUrl(This->fPlatform.pSelectedDigID)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/******************************************************************************
* RoamPrefs interface methods
*******************************************************************************/


/*** public native set_RoamPrefs_NumOfSrvrs (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fRoamPrefs_0005fNumOfSrvrs(JRIEnv* env, struct VSPTAv3* self, jshort a)
{
	unsigned int retVal = VS_NO_ERROR;
	short NumOfSrvrs;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			NumOfSrvrs = a;

			//Call our wrapper
			err = RoamPrefs_set_NumOfSrvrs(This->fPlatform.pRoamPrefs, NumOfSrvrs);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_RoamPrefs_NumOfSrvrs ()I ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fRoamPrefs_0005fNumOfSrvrs(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	short NumOfSrvrs;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((NumOfSrvrs = RoamPrefs_get_NumOfSrvrs(This->fPlatform.pRoamPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = NumOfSrvrs;
			}
		}
	}

	return retVal;
}

/*** public native set_RoamPrefs_StorageSrvr (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fRoamPrefs_0005fStorageSrvr(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = RoamPrefs_set_StorageSrvr(This->fPlatform.pRoamPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_RoamPrefs_StorageSrvr ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fRoamPrefs_0005fStorageSrvr(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = RoamPrefs_get_StorageSrvr(This->fPlatform.pRoamPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native get_RoamPrefs_NumOfSrvrs ()S ***/
//extern JRI_PUBLIC_API(jshort)
//VSPTAv3_get_0005fRoamPrefs_0005fNumOfSrvrs(JRIEnv* env, struct VSPTAv3* self);

/*** public native set_RoamPrefs_RoamingSrvrs (Ljava/lang/reflect/Array;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fRoamPrefs_0005fRoamingSrvrs(JRIEnv* env, 
													struct VSPTAv3* self, 
													struct java_lang_Object *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t** stringChars;
	int *nLenArray;
	int noOfStrings, nIndx;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	struct java_lang_String *tempString;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;


			noOfStrings = JRI_GetObjectArrayLength(env, a);
			/* allocate the array stringChars */
			stringChars = (wchar_t**)malloc(noOfStrings * sizeof (wchar_t*));
			nLenArray = (int *)malloc(noOfStrings * sizeof(int));

			/*extract the strings*/
			for (nIndx = 0; nIndx < noOfStrings; ++nIndx)
			{
				tempString = JRI_GetObjectArrayElement (env, a, nIndx);
			    stringChars[nIndx] = (wchar_t*)JRI_GetStringChars(env,tempString);
				nLenArray[nIndx] = JRI_GetStringLength(env,tempString);
			}

			//Call our wrapper
			err = RoamPrefs_set_RoamingServers (This->fPlatform.pRoamPrefs, stringChars, nLenArray, noOfStrings);

			if (stringChars != NULL)
			    free (stringChars);
			if (nLenArray != NULL)
			    free (nLenArray);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_RoamPrefs_RoamingSrvrs ()Ljava/lang/Object; ***/
extern JRI_PUBLIC_API(struct java_lang_Object *)
native_VSPTAv3_get_0005fRoamPrefs_0005fRoamingSrvrs(JRIEnv* env, struct VSPTAv3* self)
{
    int noOfElements;
    wchar_t** roamArray;
	struct java_lang_Object* retVal = NULL;
	struct java_lang_String* tempString;
	NPP instance;
	PluginInstance* This;
	int nIndx;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((roamArray = RoamPrefs_get_RoamingSrvrs(This->fPlatform.pRoamPrefs, &noOfElements)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				 retVal = JRI_NewObjectArray(env, noOfElements, ((struct java_lang_Class*)JRI_FindClass(env, "java/lang/String")), NULL);
			    /*extract the strings*/
			    for (nIndx = 0; nIndx < noOfElements; ++nIndx)
				{
      				tempString = JRI_NewString(env, (const jchar*)roamArray[nIndx], SysStringLen((BSTR)roamArray[nIndx]));
	     		    JRI_SetObjectArrayElement(env, retVal, nIndx, tempString);
					//SysFreeString((BSTR)roamArray[nIndx]);
				}
                if (roamArray != NULL)
					free(roamArray);

			}
		}
	}

	return retVal;


	return NULL;
}


/*** public native set_RoamPrefs_ClientInfo (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fRoamPrefs_0005fClientInfo(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = RoamPrefs_set_ClientInfo(This->fPlatform.pRoamPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_RoamPrefs_ClientInfo ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fRoamPrefs_0005fClientInfo(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = RoamPrefs_get_ClientInfo(This->fPlatform.pRoamPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_RoamPrefs_ClientInfoSig (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fRoamPrefs_0005fClientInfoSig(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = RoamPrefs_set_ClientInfoSig(This->fPlatform.pRoamPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_RoamPrefs_ClientInfoSig ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fRoamPrefs_0005fClientInfoSig (JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = RoamPrefs_get_ClientInfoSig (This->fPlatform.pRoamPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/******************************************************************************
* UIPrefs interface methods
*******************************************************************************/


/*** public native set_UIPrefs_UILogoUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fUILogoUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_UILogoUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_UILogoUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fUILogoUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_UILogoUrl(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_NewPasswd_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fNewPasswd_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_NewPasswd_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_NewPasswd_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fNewPasswd_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_NewPasswd_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_NewPasswd_Text (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fNewPasswd_0005fText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_NewPasswd_Text (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_NewPasswd_Text ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fNewPasswd_0005fText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_NewPasswd_Text(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_NewPasswd_OKBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fNewPasswd_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int OKBtnText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			OKBtnText = a;
			
			//Call our wrapper
			err = UIPrefs_set_NewPasswd_OKBtnText (This->fPlatform.pUIPrefs, a);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_NewPasswd_OKBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fNewPasswd_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int OKBtnText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if ((OKBtnText = UIPrefs_get_NewPasswd_OKBtnText(This->fPlatform.pUIPrefs)) == -1)
				retVal = -1;
			else
				retVal = OKBtnText;
		}
	}

	return retVal;

}



/*** public native set_UIPrefs_NewPasswd_CancelBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fNewPasswd_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_NewPasswd_CancelBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_NewPasswd_CancelBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fNewPasswd_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_NewPasswd_CancelBtnText(This->fPlatform.pUIPrefs)) == -1)
				retVal = -1;
			else
				retVal = nText;
				
		}
	}

	return retVal;

}


/*** public native set_UIPrefs_NewPasswd_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fNewPasswd_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_NewPasswd_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_NewPasswd_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fNewPasswd_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_NewPasswd_HelpUrl(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_UIPrefs_RvwMsg_Text (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fRvwMsg_0005fText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_RvwMsg_Text (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_RvwMsg_Text ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fRvwMsg_0005fText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_RvwMsg_Text(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_RvwMsg_OKBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fRvwMsg_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_RvwMsg_OKBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_RvwMsg_OKBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fRvwMsg_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = -1;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if(( nText = UIPrefs_get_RvwMsg_OKBtnText(This->fPlatform.pUIPrefs)) == -1)
				retVal = -1;
			else
				retVal = nText;
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_RvwMsg_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fRvwMsg_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_RvwMsg_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_RvwMsg_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fRvwMsg_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_RvwMsg_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_RvwMsg_CancelBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fRvwMsg_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_RvwMsg_CancelBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_RvwMsg_CancelBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fRvwMsg_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_RvwMsg_CancelBtnText(This->fPlatform.pUIPrefs)) == -1)
				retVal = -1;
			else
				retVal = nText;
		}
	}

	return retVal;

}


/*** public native set_UIPrefs_RvwMsg_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fRvwMsg_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_RvwMsg_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_RvwMsg_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fRvwMsg_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_RvwMsg_HelpUrl(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_UIPrefs_SelID_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_SelID_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SelID_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_SelID_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_SelID_Text (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_SelID_Text (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SelID_Text ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_SelID_Text(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_SelID_OKBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText =a;
			
			//Call our wrapper
			err = UIPrefs_set_SelID_OKBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SelID_OKBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if(( nText= UIPrefs_get_SelID_OKBtnText(This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nText;
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_SelID_CancelBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_SelID_CancelBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SelID_CancelBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_SelID_CancelBtnText(This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nText;
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_SelID_ShowDefChkBox (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fShowDefChkBox(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL boolShowDef;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			boolShowDef = a;

			//Call our wrapper
			err = UIPrefs_set_SelID_ShowDefChkBox(This->fPlatform.pUIPrefs, boolShowDef);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_UIPrefs_SelID_ShowDefChkBox ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fShowDefChkBox(JRIEnv* env, struct VSPTAv3* self)
{
	BOOL retVal = -1;
	BOOL boolShowDef;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((boolShowDef = UIPrefs_get_SelID_ShowDefChkBox(This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = boolShowDef;
			}
		}
	}

	return retVal;
}



/*** public native set_UIPrefs_SelID_ChkBoxText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fChkBoxText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_SelID_ChkBoxText (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SelID_ChkBoxText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fChkBoxText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_SelID_ChkBoxText(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_SelID_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSelID_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_SelID_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SelID_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fSelID_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_SelID_HelpUrl(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_SgnDlg_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSgnDlg_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_SgnDlg_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_SgnDlg_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fSgnDlg_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_SgnDlg_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_UIPrefs_LgnDlg_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fLgnDlg_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_LgnDlg_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native get_UIPrefs_LgnDlg_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fLgnDlg_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_LgnDlg_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_UIPrefs_OpenProf_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fOpenProf_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_OpenProf_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_OpenProf_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fOpenProf_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_OpenProf_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_OpenProf_Text (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fOpenProf_0005fText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_OpenProf_Text (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_UIPrefs_OpenProf_Text ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fOpenProf_0005fText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_OpenProf_Text (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_OpenProf_OKBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fOpenProf_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_OpenProf_OKBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_OpenProf_OKBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fOpenProf_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_OpenProf_OKBtnText(This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nText;
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_OpenProf_CancelBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fOpenProf_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_OpenProf_CancelBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_OpenProf_CancelBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fOpenProf_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_OpenProf_CancelBtnText (This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nText;
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_OpenProf_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fOpenProf_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_OpenProf_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_OpenProf_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fOpenProf_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_OpenProf_HelpUrl (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_UIPrefs_TitleFont (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fTitleFont(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_TitleFont (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_TitleFont ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fTitleFont(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_TitleFont (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_TextFont (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fTextFont(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_TextFont (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_TextFont ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fTextFont(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_TextFont (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_BtnFont (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fBtnFont(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_BtnFont (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_BtnFont ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fBtnFont(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_BtnFont (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_Language (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fLanguage(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int Language;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			Language = a;

			//Call our wrapper
			err = UIPrefs_set_Language(This->fPlatform.pUIPrefs, Language);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native get_UIPrefs_Language ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fLanguage(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int Language;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((Language = UIPrefs_get_Language(This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = Language;
			}
		}
	}

	return retVal;
}


/*** public native set_UIPrefs_IntroDlg_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fIntroDlg_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_IntroDlg_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_UIPrefs_IntroDlg_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fIntroDlg_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_IntroDlg_Title (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_UIPrefs_IntroDlg_Text (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fIntroDlg_0005fText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_IntroDlg_Text (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_IntroDlg_Text ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fIntroDlg_0005fText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_IntroDlg_Text (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_IntroDlg_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fIntroDlg_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_IntroDlg_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_IntroDlg_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fIntroDlg_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_IntroDlg_HelpUrl (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_UIPrefs_CreateNewProf_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fCreateNewProf_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_CreateNewProf_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_CreateNewProf_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fCreateNewProf_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_CreateNewProf_Title (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_UIPrefs_ChangePasswd_Title (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fChangePasswd_0005fTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_ChangePasswd_Title (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_ChangePasswd_Title ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fChangePasswd_0005fTitle(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_ChangePasswd_Title(This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_ChangePasswd_Text (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fChangePasswd_0005fText(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_ChangePasswd_Text (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_UIPrefs_ChangePasswd_Text ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fChangePasswd_0005fText(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_ChangePasswd_Text (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_ChangePasswd_OKBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fChangePasswd_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_ChangePasswd_OKBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_ChangePasswd_OKBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fChangePasswd_0005fOKBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_ChangePasswd_OKBtnText(This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nText;
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_ChangePasswd_CancelBtnText (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fChangePasswd_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nText = a;
			
			//Call our wrapper
			err = UIPrefs_set_ChangePasswd_CancelBtnText (This->fPlatform.pUIPrefs, nText);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_ChangePasswd_CancelBtnText ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fChangePasswd_0005fCancelBtnText(JRIEnv* env, struct VSPTAv3* self)
{
	int retVal = VS_NO_ERROR;
	int nText;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nText = UIPrefs_get_ChangePasswd_CancelBtnText (This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nText;
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_ChangePasswd_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fChangePasswd_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_ChangePasswd_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_ChangePasswd_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fChangePasswd_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_ChangePasswd_HelpUrl (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_UIPrefs_ChangePasswd_HelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fTimeout_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = UIPrefs_set_Timeout_HelpUrl (This->fPlatform.pUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_UIPrefs_ChangePasswd_HelpUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fUIPrefs_0005fTimeout_0005fHelpUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = UIPrefs_get_Timeout_HelpUrl (This->fPlatform.pUIPrefs)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_UIPrefs_EnableTopMostWindow (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fEnableTopMostWindow(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL EnableTopMost;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			EnableTopMost = a;

			//Call our wrapper
			err = UIPrefs_set_EnableTopMost (This->fPlatform.pUIPrefs, EnableTopMost);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native set_UIPrefs_SignTransDlgWidth (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSignTransDlgWidth(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nWidth;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nWidth = a;
			
			//Call our wrapper
			err = UIPrefs_set_SignTransDlgWidth (This->fPlatform.pUIPrefs, nWidth);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}

/*** public native get_UIPref_SignTransDlgWidth ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fSignTransDlgWidth(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	int nWidth;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nWidth = UIPrefs_get_SignTransDlgWidth (This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nWidth;
			}
		}
	}

	return retVal;
}

/*** public native set_UIPrefs_SignTransDlgHeight (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fUIPrefs_0005fSignTransDlgHeight(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nHeight;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nHeight = a;
			
			//Call our wrapper
			err = UIPrefs_set_SignTransDlgHeight (This->fPlatform.pUIPrefs, nHeight);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}

/*** public native get_UIPref_SignTransDlgHeight ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fUIPrefs_0005fSignTransDlgHeight(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	int nHeight;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((nHeight = UIPrefs_get_SignTransDlgHeight (This->fPlatform.pUIPrefs)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = nHeight;
			}

		}
	}

	return retVal;
}

/******************************************************************************
* ProfMgmt Interface methods.
*******************************************************************************/


/*** public native set_ProfMgmt_PasswdQuality (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fPasswdQuality(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int PasswordQuality;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			PasswordQuality = a;

			//Call our wrapper
			err = ProfMgmt_set_PasswdQuality(This->fPlatform.pProfMgmt, PasswordQuality);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_ProfMgmt_PasswdQuality ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fProfMgmt_0005fPasswdQuality(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int PasswordQuality;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((PasswordQuality = ProfMgmt_get_PasswdQuality (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = PasswordQuality;
			}
		}
	}

	return retVal;
}


/*** public native set_ProfMgmt_PasswdLength (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fPasswdLength(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int PasswordLength;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			PasswordLength = a;

			//Call our wrapper
			err = ProfMgmt_set_PasswdLength(This->fPlatform.pProfMgmt, PasswordLength);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_ProfMgmt_PasswdLength ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fProfMgmt_0005fPasswdLength(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int PasswordLength;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((PasswordLength = ProfMgmt_get_PasswdLength (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = PasswordLength;
			}
		}
	}

	return retVal;
}

/*** public native set_ProfMgmt_PasswdTimeOut (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fPasswdTimeOut(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int PasswdTimeOut;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			PasswdTimeOut = a;

			//Call our wrapper
			err = ProfMgmt_set_PasswdTimeOut(This->fPlatform.pProfMgmt, PasswdTimeOut);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_ProfMgmt_PasswdTimeOut ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fProfMgmt_0005fPasswdTimeOut(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int PasswdTimeOut;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((PasswdTimeOut = ProfMgmt_get_PasswdTimeOut (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = PasswdTimeOut;
			}
		}
	}

	return retVal;
}


/*** public native set_ProfMgmt_PasswdLockOutTries (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fPasswdLockOutTries(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int PasswdLockOutTries;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			PasswdLockOutTries = a;

			//Call our wrapper
			err = ProfMgmt_set_PasswdLockOutTries(This->fPlatform.pProfMgmt, PasswdLockOutTries);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_ProfMgmt_PasswdLockOutTries ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fProfMgmt_0005fPasswdLockOutTries(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int PasswdLockOutTries;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((PasswdLockOutTries = ProfMgmt_get_PasswdLockOutTries (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = PasswdLockOutTries;
			}
		}
	}

	return retVal;
}

/*** public native set_ProfMgmt_PasswdUnLockPeriod (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fPasswdUnLockPeriod(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int PasswdUnLockPeriod;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			PasswdUnLockPeriod = a;

			//Call our wrapper
			err = ProfMgmt_set_PasswdUnLockPeriod(This->fPlatform.pProfMgmt, PasswdUnLockPeriod);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_ProfMgmt_PasswdUnLockPeriod ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fProfMgmt_0005fPasswdUnLockPeriod(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int PasswdUnLockPeriod;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((PasswdUnLockPeriod = ProfMgmt_get_PasswdUnLockPeriod (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = PasswdUnLockPeriod;
			}
		}
	}

	return retVal;
}

/*** public native set_ProfMgmt_ProfileName (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fProfileName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = ProfMgmt_set_ProfileName (This->fPlatform.pProfMgmt, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_ProfMgmt_ProfileName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fProfMgmt_0005fProfileName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = ProfMgmt_get_ProfileName (This->fPlatform.pProfMgmt)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_ProfMgmt_Password (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fPassword(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = ProfMgmt_set_Password (This->fPlatform.pProfMgmt, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native set_ProfMgmt_SaveLocal (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fSaveLocal(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL SaveLocal;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			SaveLocal = a;

			//Call our wrapper
			err = ProfMgmt_set_SaveLocal (This->fPlatform.pProfMgmt, SaveLocal);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_ProfMgmt_SaveLocal ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fProfMgmt_0005fSaveLocal(JRIEnv* env, struct VSPTAv3* self)
{
	BOOL retVal = -1;
	BOOL boolSaveLocal;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((boolSaveLocal = ProfMgmt_get_SaveLocal (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = boolSaveLocal;
			}
		}
	}

	return retVal;
}

/*** public native set_ProfMgmt_RoamProfile (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fRoamProfile(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL RoamProfile;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			RoamProfile = a;

			//Call our wrapper
			err = ProfMgmt_set_RoamProfile (This->fPlatform.pProfMgmt, RoamProfile);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_ProfMgmt_RoamProfile ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fProfMgmt_0005fRoamProfile(JRIEnv* env, struct VSPTAv3* self)
{
	BOOL retVal = -1;
	BOOL boolRoamProfile;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((boolRoamProfile = ProfMgmt_get_RoamProfile (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = boolRoamProfile;
			}
		}
	}

	return retVal;
}

/*** public native set_ProfMgmt_OpenProfFlags (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fProfMgmt_0005fOpenProfFlags(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int OpenProfFlags;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			OpenProfFlags = a;

			//Call our wrapper
			err = ProfMgmt_set_OpenProfFlags(This->fPlatform.pProfMgmt, OpenProfFlags);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_ProfMgmt_OpenProfFlags ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fProfMgmt_0005fOpenProfFlags(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int OpenProfFlags;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((OpenProfFlags = ProfMgmt_get_OpenProfFlags (This->fPlatform.pProfMgmt)) == -1)
			{
				retVal = -1;
			}
			else
			{
				retVal = OpenProfFlags;
			}
		}
	}

	return retVal;
}

/*** public native ProfMgmt_OpenProfile ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_ProfMgmt_0005fOpenProfile(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = ProfMgmt_OpenProfile (This->fPlatform.pProfMgmt);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native ProfMgmt_CloseProfile ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_ProfMgmt_0005fCloseProfile(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = ProfMgmt_CloseProfile (This->fPlatform.pProfMgmt);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


extern JRI_PUBLIC_API(jint)
native_VSPTAv3_ProfMgmt_0005fSaveProfile(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = ProfMgmt_SaveProfile (This->fPlatform.pProfMgmt);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native ProfMgmt_ChangePassword ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_ProfMgmt_0005fChangePassword(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = ProfMgmt_ChangePassword (This->fPlatform.pProfMgmt);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/******************************************************************************
* PTA Interface methods
*******************************************************************************/



/*** public native PTA_Initialize (Ljava/lang/String;Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_PTA_0005fInitialize(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, jint b)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	int intVal;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			intVal = b;

			//Call our wrapper
			err = PTA_Initialize (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a), intVal);
		
			if(err != VS_NO_ERROR) 
				retVal = err;
			else
			{
				err = PTADllApi_SetHostName (This->fPlatform.pPTAApi, szHostName, szProtocol);
     			if(err != VS_NO_ERROR) 
	     			retVal = err;		
			}
		}
	}
	return retVal;
}

/*** public native PTA_Close ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_PTA_0005fClose(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = PTA_Close (This->fPlatform.pPTA);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native set_PTA_AppPreference (Ljava/lang/String;Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fAppPreference(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	wchar_t* stringCharsB;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL || b==NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			stringCharsB = (wchar_t*)JRI_GetStringChars(env, b);

			//Call our wrapper
			err = PTA_set_AppPreference (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a), stringCharsB, JRI_GetStringLength(env,b));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_PTA_AppPreference (Ljava/lang/String;)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fAppPreference(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			if((pwstrName = PTA_get_AppPreference (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a))) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native set_PTA_CSPName (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fCSPName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_set_CSPName (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_PTA_CSPName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fCSPName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = PTA_get_CSPName (This->fPlatform.pPTA)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_PTA_0005fCreateCertReq(JRIEnv* env, 
									  struct VSPTAv3* self, 
									  struct java_lang_String *a, 
									  jint b, 
									  jint c, 
									  struct java_lang_Object *d)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* stringChars;
	int KeyAttributes;
	int HashAlg;
	NPP instance;
	PluginInstance* This;
	wchar_t* pwstrName;

	int *nLenArray;
	int noOfStrings, nIndx;
	wchar_t** attributes;
	struct java_lang_String *tempString;

	if(env == NULL || self == NULL || a == NULL || d == NULL)
	{
		retVal = (struct java_lang_String*)NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = (struct java_lang_String*)NULL;
			_lastErrCode = VS_INVALID_ARG;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			KeyAttributes = b;
			HashAlg = c;

			noOfStrings = JRI_GetObjectArrayLength(env, d);
			nLenArray = (int*)malloc(noOfStrings*sizeof(int));
			attributes  = (wchar_t**)malloc(noOfStrings*sizeof(wchar_t*));
			for (nIndx = 0; nIndx < noOfStrings; ++nIndx)
			{
				tempString = JRI_GetObjectArrayElement (env, d, nIndx);
			    attributes[nIndx] = (wchar_t*)JRI_GetStringChars(env,tempString);
				nLenArray[nIndx] = JRI_GetStringLength(env,tempString);
			}


			//Call our wrapper
			pwstrName = PTA_CreateCertReq (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a), 
				                  KeyAttributes, HashAlg, attributes, nLenArray, noOfStrings);
			if (pwstrName == NULL) {
				retVal = NULL;
			} else {
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}

			// free dynamically allocated memories 
			//for (nIndx = 0; nIndx < noOfStrings; ++nIndx)
			//{
			//   if (attributes[nIndx] != NULL)
			//			SysFreeString((BSTR)attributes[nIndx]);
			//}
			if (attributes != NULL)
			     free (attributes);
			if (nLenArray != NULL)
			     free (nLenArray);
		

		}
	}
	return retVal;       
}



/*** public native PTA_InstallCert (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_PTA_0005fInstallCert(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_InstallCert (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native PTA_InstallKeyPair (Ljava/lang/String;Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_PTA_0005fInstallKeyPair(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	wchar_t* pkcs7Chars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL || b==NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
            pkcs7Chars = (wchar_t*)JRI_GetStringChars(env, b);
			//Call our wrapper
			err = PTA_InstallKeyPair (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a), pkcs7Chars, JRI_GetStringLength(env,b));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native PTA_SelectIDForTrans (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_PTA_0005fSelectIDForTrans(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			//Call our wrapper
			err = PTA_SelectIDForTrans (This->fPlatform.pPTA);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native PTA_SelectIDForChallenge (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_PTA_0005fSelectIDForChallenge(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			//Call our wrapper
			err = PTA_SelectIDForChallenge (This->fPlatform.pPTA);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native PTA_SignChallenge (Ljava/lang/String;I)I ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_PTA_0005fSignChallenge(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, jint b)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	wchar_t* stringChars;
	int nHashAlg;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			nHashAlg = b;
			if((pwstrName = PTA_SignChallenge (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a),nHashAlg)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}

/*** public native PTA_SignTransaction (Ljava/lang/String;I)I ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_PTA_0005fSignTransaction(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, jint b)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	wchar_t* stringChars;
	int nHashAlg;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			nHashAlg = b;
			if((pwstrName = PTA_SignTransaction (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a),nHashAlg)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native PTA_SignRenewal (I)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_PTA_0005fSignRenewal(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	int nHashAlg;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			nHashAlg = a;
			if((pwstrName = PTA_SignRenewal (This->fPlatform.pPTA, nHashAlg)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_PTA_ProtocolName (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fProtocolName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_set_ProtocolName (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

/*** public native get_PTA_ProtocolName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fProtocolName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = PTA_get_ProtocolName (This->fPlatform.pPTA)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native get_PTA_UseDefCertFlag ()S ***/
extern JRI_PUBLIC_API(jshort)
native_VSPTAv3_get_0005fPTA_0005fUseDefCertFlag(JRIEnv* env, struct VSPTAv3* self)
{
	jshort retVal = -1;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			retVal = PTA_get_UserDefCertFlag (This->fPlatform.pPTA);
		}
	}
	return retVal;
}

/*** public native set_PTA_UseDefCertFlag (S)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fUseDefCertFlag(JRIEnv* env, struct VSPTAv3* self, jshort a)
{	unsigned int retVal = VS_NO_ERROR;
	short shortFlag;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			shortFlag = a;

			//Call our wrapper
			err = PTA_set_UserDefCertFlag (This->fPlatform.pPTA, shortFlag);		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native set_PTA_AuthDll (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fAuthDll(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_set_AuthDll (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native get_PTA_AuthDll ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fAuthDll(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = PTA_get_AuthDll (This->fPlatform.pPTA)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}



/*** public native set_PTA_ProfileIssFrndlyName (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fProfileIssFrndlyName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_set_ProfileIssFrndlyName (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}



/*** public native get_PTA_ProfileIssFrndlyName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fProfileIssFrndlyName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = PTA_get_ProfileIssFrndlyName (This->fPlatform.pPTA)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_PTA_ProfileIssUniqueId (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fProfileIssUniqueId(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_set_ProfileIssUniqueId (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/*** public native get_PTA_ProfileIssUniqueId ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fProfileIssUniqueId(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = PTA_get_ProfileIssUniqueId (This->fPlatform.pPTA)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;

}


/*** public native set_PTA_AffLogoUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fAffLogoUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			//Call our wrapper
			err = PTA_set_AffLogoUrl (This->fPlatform.pPTA, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}



/*** public native get_PTA_AffLogoUrl ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fPTA_0005fAffLogoUrl(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if((pwstrName = PTA_get_AffLogoUrl (This->fPlatform.pPTA)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;
}


extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fPTA_0005fEnableCertForCapi(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL boolEnableForCapi;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			boolEnableForCapi = a;
			
			//Call our wrapper
			err = PTA_set_EnableCertForCapi(This->fPlatform.pPTA, boolEnableForCapi);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}



/******************************************************************************
* Xenroll methods
*******************************************************************************/

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fProviderType(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	DWORD dwProviderType;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{
				dwProviderType = a;
				
				//Call our wrapper
				err = Enroll_set_ProviderType(This->fPlatform.pEnroll, dwProviderType);
			
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}

/*** public native get_XEnroll_ProviderType ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fXEnroll_0005fProviderType(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal;
	DWORD dwProviderType;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{
				if((dwProviderType = Enroll_get_ProviderType(This->fPlatform.pEnroll)) == -1)
				{
					retVal = -1;
				}
				else
				{
					retVal = dwProviderType;
				}
			}
		}
	}

	return retVal;
}

/*** public native set_XEnroll_GenKeyFlags (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fGenKeyFlags(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	DWORD dwGenKeyFlags;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{
				dwGenKeyFlags = a;
			
				//Call our wrapper
				err = Enroll_set_GenKeyFlags(This->fPlatform.pEnroll, dwGenKeyFlags);
			
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}

/*** public native get_XEnroll_GenKeyFlags ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fXEnroll_0005fGenKeyFlags(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal;
	DWORD dwGenKeyFlags;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{

				if((dwGenKeyFlags = Enroll_get_GenKeyFlags(This->fPlatform.pEnroll)) == -1)
				{
					retVal = -1;
				}
				else
				{	
					retVal = dwGenKeyFlags;
				}
			}
		}
	}

	return retVal;
}

/*** public native set_XEnroll_ProviderName (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fProviderName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{
				stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
				//Call our wrapper
				err = Enroll_set_ProviderName(This->fPlatform.pEnroll, stringChars, JRI_GetStringLength(env,a));
		
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}


/*** public native get_XEnroll_ProviderName ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fXEnroll_0005fProviderName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrProviderName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = NULL;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				if((pwstrProviderName = Enroll_get_ProviderName(This->fPlatform.pEnroll)) == NULL)
				{
						retVal = NULL;
				}
				else
				{
					retVal = JRI_NewString(env, (const jchar*)pwstrProviderName, SysStringLen((BSTR)pwstrProviderName));
					SysFreeString((BSTR)pwstrProviderName);
				}
			}
		}
	}

	return retVal;
}


/*** public native set_XEnroll_HashAlgorithm (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fHashAlgorithm(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{
				stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
				//Call our wrapper
				err = Enroll_set_HashAlgorithm(This->fPlatform.pEnroll, stringChars, JRI_GetStringLength(env,a));
		
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}


/*** public native get_XEnroll_HashAlgorith ()Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fXEnroll_0005fHashAlgorithm(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrHashAlogrithm;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = NULL;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				if((pwstrHashAlogrithm = Enroll_get_HashAlgorithm(This->fPlatform.pEnroll)) == NULL)
				{
					retVal = NULL;
				}
				else
				{
					retVal = JRI_NewString(env, (const jchar*)pwstrHashAlogrithm, SysStringLen((BSTR)pwstrHashAlogrithm));
					SysFreeString((BSTR)pwstrHashAlogrithm);
				}
			}
		}
	}

	return retVal;
}


/*** public native set_XEnroll_KeySpec (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fKeySpec(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	DWORD dwKeySpec;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				dwKeySpec = a;
			
				//Call our wrapper
				err = Enroll_set_KeySpec(This->fPlatform.pEnroll, dwKeySpec);
			
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}


/*** public native get_XEnroll_KeySpec ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fXEnroll_0005fKeySpec(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = 0;
	DWORD dwKeySpec;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				if((dwKeySpec = Enroll_get_KeySpec(This->fPlatform.pEnroll)) == -1)
				{
					retVal = -1;
				}
				else
				{
					retVal = dwKeySpec;
				}
			}
		}
	}

	return retVal;
}


/*** public native set_XEnroll_DeleteRequestCert (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fDeleteRequestCert(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL boolDeleteRequest;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				boolDeleteRequest = a;
				
				//Call our wrapper
				err = Enroll_set_DeleteRequestCert(This->fPlatform.pEnroll, boolDeleteRequest);
		
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}


/*** public native get_XEnroll_DeleteRequestCert ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fXEnroll_0005fDeleteRequestCert(JRIEnv* env, struct VSPTAv3* self)
{
	jbool retVal = FALSE;
	BOOL boolDeleteRequest;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = FALSE;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = FALSE;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = FALSE;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				boolDeleteRequest = Enroll_get_KeySpec(This->fPlatform.pEnroll);			
				retVal = boolDeleteRequest;
			}
			
		}
	}

	return retVal;
}


/*** public native set_XEnroll_WriteCertToCSP (Z)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fXEnroll_0005fWriteCertToCSP(JRIEnv* env, struct VSPTAv3* self, jbool a)
{
	unsigned int retVal = VS_NO_ERROR;
	BOOL boolWriteCertToCSP;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				boolWriteCertToCSP = a;
			
				//Call our wrapper
				err = Enroll_set_WriteCertToCSP(This->fPlatform.pEnroll, boolWriteCertToCSP);
		
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}


/*** public native get_XEnroll_WriteCertToCSP ()Z ***/
extern JRI_PUBLIC_API(jbool)
native_VSPTAv3_get_0005fXEnroll_0005fWriteCertToCSP(JRIEnv* env, struct VSPTAv3* self)
{
	jbool retVal = FALSE;
	BOOL boolWriteCertToCSP;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = FALSE;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = FALSE;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = FALSE;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				boolWriteCertToCSP = Enroll_get_WriteCertToCSP(This->fPlatform.pEnroll);
			
				retVal = boolWriteCertToCSP;
			}
		}
	}

	return retVal;
}


/*** public native XEnroll_enumProviders (II)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_XEnroll_0005fenumProviders(JRIEnv* env, struct VSPTAv3* self, jint a, jint b)
{
	struct java_lang_String* retVal = NULL;
	DWORD dwIndex, dwFlags;
	NPP instance;
	PluginInstance* This;
	wchar_t* pwstrProvider;

	if(env == NULL || self == NULL )
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = NULL;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				dwIndex = a;
				dwFlags = b;
			
				//Call our wrapper
				if((pwstrProvider = Enroll_enumProvider(This->fPlatform.pEnroll, dwIndex, dwFlags)) == NULL)
				{
					retVal = NULL;
				}
				else
				{
					retVal = JRI_NewString(env, (const jchar*)pwstrProvider, SysStringLen((BSTR)pwstrProvider));
					SysFreeString((BSTR)pwstrProvider);
				}
			}
		}
	}
	return retVal;
}


/*** public native XEnroll_createPKCS10 (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_XEnroll_0005fcreatePKCS10(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b)
{
	struct java_lang_String* retVal = NULL;
	wchar_t *pwstrDN, *pwstrUsage, *pwstrPKCS10;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL )
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = NULL;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				pwstrDN = (wchar_t*)JRI_GetStringChars(env, a);
				pwstrUsage = (wchar_t*)JRI_GetStringChars(env, b);
			
				//Call our wrapper
				 pwstrPKCS10= Enroll_createPKCS10(This->fPlatform.pEnroll, pwstrDN, JRI_GetStringLength(env,a), pwstrUsage, JRI_GetStringLength(env,b));
				 if (pwstrPKCS10 == NULL)
				 {					 
					retVal = JRI_NewString(env,(const jchar*)"", 0);
				}
				else
				{
					 retVal = JRI_NewString(env, (const jchar*)pwstrPKCS10, SysStringLen((BSTR)pwstrPKCS10));
					SysFreeString((BSTR)pwstrPKCS10);
				}	
			}		
		}
	}
	return retVal;
}


/*** public native XEnroll_acceptPKCS7 (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_XEnroll_0005facceptPKCS7(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolXenrollInitialized == FALSE)
			{
			   retVal = VS_XENROLL_NOT_LOADED;
               _lastErrCode = VS_XENROLL_NOT_LOADED;
			} 
			else
			{
				stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
				//Call our wrapper
				err = Enroll_acceptPKCS7(This->fPlatform.pEnroll, stringChars, JRI_GetStringLength(env,a));
			
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}

/******************************************************
    Error related functions 
	***************************************************/
/*** public native GetLastError ()I ***/
extern JRI_PUBLIC_API(jlong)
native_VSPTAv3_GetLastError(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int errCode;
	errCode = _lastErrCode;
	return errCode;

}

/*** public native CnfChk_CheckMSESEnhCSP ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_CnfChk_0005fCheckMSEnhCSP(JRIEnv* env, struct VSPTAv3* self)
{
#if 0
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	long lResult;
#endif

	return VS_NOT_IMPL;

#if 0
	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = CnfChk_CheckMSEnhCSP(This->fPlatform.pCnfChk, &lResult);
		
			if(err != VS_NO_ERROR)
				retVal = err;
			else
				retVal = lResult;
		}
	}
	return retVal;
#endif
}

/*** public native CnfChk_FixEnhCSP (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_CnfChk_0005fFixEnhCSP(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	/*
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	long lResult;
	*/
	return VS_NOT_IMPL;

#if 0
	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CnfChk_FixEnhCSP(This->fPlatform.pCnfChk, stringChars, JRI_GetStringLength(env,a), &lResult);
		
			if(err != VS_NO_ERROR)
				retVal = err;
			else
				retVal = lResult;
		}
	}
	return retVal;
#endif
}

/*** public native CnfChk_GetVersion (Ljava/lang/String;Ljava/lang/StringBuffer;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_CnfChk_0005fGetVersion(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_StringBuffer *b)
{
#if 0
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	wchar_t* pwstrVer;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	long lResult;
	jcharArray charArrayVer;
#endif

	return VS_NOT_IMPL;

#if 0
	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = CnfChk_GetVersion(This->fPlatform.pCnfChk, stringChars, JRI_GetStringLength(env,a), &pwstrVer, &lResult);
		
			if(err != VS_NO_ERROR)
				retVal = err;
			else
			{
				charArrayVer = JRI_NewCharArray(env,SysStringLen(pwstrVer),(void*)pwstrVer);
				java_lang_StringBuffer_setLength(env,b,0);
				java_lang_StringBuffer_insert_2(env,b,0, charArrayVer); // ?? do we need to free the char array ??
				SysFreeString((BSTR)pwstrVer);
				retVal = lResult;
			}
		}
	}
	return retVal;
#endif
}

/*** public native CnfChk_VerCompare (Ljava/lang/String;Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_CnfChk_0005fVerCompare(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b)
{
#if 0	
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringCharsA;
	wchar_t* stringCharsB;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	long lResult;
#endif

	return VS_NOT_IMPL;

#if 0
	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			stringCharsA = (wchar_t*)JRI_GetStringChars(env, a);
			stringCharsB = (wchar_t*)JRI_GetStringChars(env, b);

			//Call our wrapper
			err = CnfChk_VerCompare(This->fPlatform.pCnfChk, stringCharsA, JRI_GetStringLength(env,a), stringCharsB, JRI_GetStringLength(env,b), &lResult);
		
			if(err != VS_NO_ERROR)
				retVal = err;
			else
				retVal = lResult;
		}
	}
	return retVal;
#endif
}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_VSImport_0005fImport(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b, struct java_lang_StringBuffer *c)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringCharsA;
	wchar_t* stringCharsB;
	wchar_t* pwstrErrString = NULL;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	jcharArray charArrayErrString;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if (This->fPlatform.boolImportInitialized == FALSE)
			{
			   retVal = VS_IMPORT_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
		    if(!This->fPlatform.pImport)
			{
				retVal = VS_NOT_IMPL;
				_lastErrCode = retVal;
			}		
			else
			{

				stringCharsA = (wchar_t*)JRI_GetStringChars(env, a);
				stringCharsB = (wchar_t*)JRI_GetStringChars(env, b);

				//Call our wrapper
				err = Import_Import(This->fPlatform.pImport, stringCharsA, JRI_GetStringLength(env,a), stringCharsB, JRI_GetStringLength(env,b), &pwstrErrString);
				
				if(err != VS_NO_ERROR)
				{
					if(pwstrErrString)
					{
						charArrayErrString = JRI_NewCharArray(env,SysStringLen(pwstrErrString),(void*)pwstrErrString);
						java_lang_StringBuffer_setLength(env,c,0);
						java_lang_StringBuffer_insert_2(env,c,0, charArrayErrString); // ?? do we need to free the char array ??
						SysFreeString((BSTR)pwstrErrString);
					}
					
					retVal = err;
				}
				else
				{
					retVal = VS_NO_ERROR;
				}
			}
		}
	}
	return retVal;

}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_VSImport_0005fset_0005fKeyExportable(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	long lKeyExp;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolImportInitialized == FALSE)
			{
			   retVal = VS_IMPORT_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			if(!This->fPlatform.pImport)
			{
				retVal = VS_NOT_IMPL;
				_lastErrCode = retVal;
			}
			else
			{
				lKeyExp = a;
				
				//Call our wrapper
				err = Import_set_KeyExportable(This->fPlatform.pImport, lKeyExp);
				
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;

}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_VSImport_0005fget_0005fKeyExportable(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = 0;
	long lKeyExp;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if (This->fPlatform.boolImportInitialized == FALSE)
			{
			   retVal = VS_IMPORT_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			if(!This->fPlatform.pImport)
			{
				retVal = VS_NOT_IMPL;
				_lastErrCode = retVal;
			}
			else
			{
				if((lKeyExp = Import_get_KeyExportable(This->fPlatform.pImport)) == -1)
				{
					retVal = -1;
				}
				else
				{
					retVal = lKeyExp;
				}
			}
		}
	}

	return retVal;
}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_VSImport_0005fset_0005fProviderName(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolImportInitialized == FALSE)
			{
			   retVal = VS_IMPORT_NOT_LOADED;
               _lastErrCode = retVal;
			} 
			else
			{
				//Convert from java string to wchar
				stringChars = (wchar_t*)JRI_GetStringChars(env, a);
				
				//Call our wrapper
				err = Import_set_ProviderName(This->fPlatform.pImport, stringChars, JRI_GetStringLength(env,a));
			
				if(err != VS_NO_ERROR)
					retVal = err;
			}
		}
	}
	return retVal;
}

extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_VSImport_0005fget_0005fProviderName(JRIEnv* env, struct VSPTAv3* self)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			if (This->fPlatform.boolImportInitialized == FALSE)
			{
			   retVal = NULL;
               _lastErrCode = VS_IMPORT_NOT_LOADED;
			} 
			else
			{
				if((pwstrName = Import_get_ProviderName(This->fPlatform.pImport)) == NULL)
				{
					retVal = NULL;
				}
				else
				{
					retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
					SysFreeString((BSTR)pwstrName);
				}
			}
		}
	}

	return retVal;
}


extern JRI_PUBLIC_API(jint)
native_VSPTAv3_AddRootCerts_0005fInitialize(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	err = 0;
	
	
	//Check input
	if(env == NULL || self == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if (This->fPlatform.boolAddRootsInitialized == FALSE)
			{
			   retVal = VS_ADDROOTS_NOT_LOADED;
               _lastErrCode = VS_ADDROOTS_NOT_LOADED;
			} 
			else
			{
			//Intialize
				err = AddRoots_Initialize(This->fPlatform.pAddRoots);
		
				if(err != VS_NO_ERROR)
					retVal = VS_GENERIC_ERROR;
			}
		}
	}
	
	return retVal;
}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_AddRootCerts_0005fCreateStandardTrustProfile(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	err = 0;
	
	
	//Check input
	if(env == NULL || self == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if (This->fPlatform.boolAddRootsInitialized == FALSE)
			{
			   retVal = VS_ADDROOTS_NOT_LOADED;
               _lastErrCode = VS_ADDROOTS_NOT_LOADED;
			} 
			else
			{
				//Intialize
				err = AddRoots_CreateStandardTrustProfile(This->fPlatform.pAddRoots);
		
				if(err != VS_NO_ERROR)
					retVal = VS_GENERIC_ERROR;
			}
		}
	}
	
	return retVal;
}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_AddRootCerts_0005fCreateVerisignTrustProfile(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;
	err = 0;
	
	
	//Check input
	if(env == NULL || self == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if (This->fPlatform.boolAddRootsInitialized == FALSE)
			{
			   retVal = VS_ADDROOTS_NOT_LOADED;
               _lastErrCode = VS_ADDROOTS_NOT_LOADED;
			} 
			else
			{
				//Intialize
				err = AddRoots_CreateVerisignTrustProfile(This->fPlatform.pAddRoots);
		
				if(err != VS_NO_ERROR)
					retVal = VS_GENERIC_ERROR;
			}
		}
	}
	
	return retVal;
}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_P12Import_0005fImportP12(JRIEnv* env, struct VSPTAv3* self, jint a, struct java_lang_String *b, struct java_lang_StringBuffer *c, struct java_lang_StringBuffer *d)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	wchar_t* pwstrSerNum;
	wchar_t* pwstrIssDN;
	jcharArray charArraySerNum;
	jcharArray charArrayIssDN;
	int nParamType;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			//MessageBox(NULL,"Before extracting the filename",NULL,MB_OK);
			stringChars = (wchar_t*)JRI_GetStringChars(env, b);
			nParamType = a;

			//Call our wrapper
			//MessageBox(NULL,"Before calling the wrapper",NULL,MB_OK);
			err = P12Import_ImportP12(This->fPlatform.pP12Import, nParamType, stringChars, JRI_GetStringLength(env,b),&pwstrSerNum, &pwstrIssDN);
		
			if(err != VS_NO_ERROR)
				retVal = VS_GENERIC_ERROR;
			else
			{
				charArraySerNum = JRI_NewCharArray(env,SysStringLen(pwstrSerNum),(void*)pwstrSerNum);
				java_lang_StringBuffer_setLength(env,c,0);
				java_lang_StringBuffer_insert_2(env,c,0, charArraySerNum); // ?? do we need to free the char array ??
				SysFreeString((BSTR)pwstrSerNum);

				charArrayIssDN = JRI_NewCharArray(env,SysStringLen(pwstrIssDN),(void*)pwstrIssDN);
				java_lang_StringBuffer_setLength(env,d,0);
				java_lang_StringBuffer_insert_2(env,d,0, charArrayIssDN); // ?? do we need to free the char array ??
				SysFreeString((BSTR)pwstrIssDN);
			}
		}
	}
	return retVal;
}


extern JRI_PUBLIC_API(jint)
native_VSPTAv3_P12Export_0005fExportP12(JRIEnv* env, struct VSPTAv3* self, jint a, jint b, struct java_lang_String *c)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;

	int nType;
	int nFlags;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || c == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			//MessageBox(NULL,"Before extracting the filename",NULL,MB_OK);
			stringChars = (wchar_t*)JRI_GetStringChars(env, c);
			nType = a;
			nFlags = b;

			//Call our wrapper
			//MessageBox(NULL,"Before calling the wrapper",NULL,MB_OK);
			err = P12Export_ExportP12(This->fPlatform.pP12Export, nType, nFlags, stringChars, JRI_GetStringLength(env,c));
		
			if(err != VS_NO_ERROR)
				retVal = VS_GENERIC_ERROR;
		}
	}
	return retVal;
}


extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fP12Export_0005fPasswdQuality(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int nPasswordQuality;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if ((nPasswordQuality = P12Export_get_PasswdQuality(This->fPlatform.pP12Export)) == -1)
				retVal = -1;
			else
				retVal = nPasswordQuality;
		}
	}

	return retVal;

}


extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fP12Export_0005fPasswdQuality(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nPasswordQuality;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nPasswordQuality = a;
			
			//Call our wrapper
			err = P12Export_set_PasswdQuality (This->fPlatform.pP12Export, nPasswordQuality);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_get_0005fP12Export_0005fPasswdLength(JRIEnv* env, struct VSPTAv3* self)
{
	jint retVal = -1;
	int nPasswordLength;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL)
	{
		retVal = -1;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = -1;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			if ((nPasswordLength = P12Export_get_PasswdLength(This->fPlatform.pP12Export)) == -1)
				retVal = -1;
			else
				retVal = nPasswordLength;
		}
	}

	return retVal;

}

extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fP12Export_0005fPasswdLength(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nPasswordLength;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nPasswordLength = a;
			
			//Call our wrapper
			err = P12Export_set_PasswdLength (This->fPlatform.pP12Export, nPasswordLength);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}
	return retVal;
}


/******************************************************************************
* Digital Notarization Interface methods
*******************************************************************************/

/*** public native VSNZ_Initialize ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_NZ_0005fInitialize(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = NZ_Initialize(This->fPlatform.pVSNZ);
		
			if(err != VS_NO_ERROR) 
				retVal = err;
		}
	}

	return retVal;
}


/*** public native VSNZ_Close ()I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_NZ_0005fClose(JRIEnv* env, struct VSPTAv3* self)
{
	unsigned int retVal = VS_NO_ERROR;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL )
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Call our wrapper
			err = NZ_Close(This->fPlatform.pVSNZ);
		
			if(err != VS_NO_ERROR) 
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_NotarizationServer (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fNotarizationServer(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
		
			//Call our wrapper
			err = NZ_set_NotarizationServer(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_HashAlg (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fHashAlg(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
		
			//Call our wrapper
			err = NZ_set_HashAlg(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_DisplayDigitalID (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fDisplayDigitalID(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nDisplayID;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nDisplayID = a;

			//Call our wrapper
			err = NZ_set_DisplayDigitalID(This->fPlatform.pVSNZ, nDisplayID);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_CrlLocation (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fCrlLocation(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
		
			//Call our wrapper
			err = NZ_set_CRLLocation(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_ValidationPreference (I)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fValidationPreference(JRIEnv* env, struct VSPTAv3* self, jint a)
{
	unsigned int retVal = VS_NO_ERROR;
	int nValPref;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			nValPref = a;

			//Call our wrapper
			err = NZ_set_ValidationPref(This->fPlatform.pVSNZ, nValPref);
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_NotarizationDescription (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fNotarizationDescription(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
		
			//Call our wrapper
			err = NZ_set_NotarizationDescription(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native NZ_NotarizeDocument (Ljava/lang/String;II)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_NZ_0005fNotarizeDocument(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, jint b, jint c)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	wchar_t* stringChars;
	int UIMask, ResponseType;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			UIMask = b;
			ResponseType = c;

			if((pwstrName = NZ_NotarizeDocument(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a),UIMask, ResponseType)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;
}


/*** public native NZ_NotarizeHash (Ljava/lang/String;I)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_NZ_0005fNotarizeHash(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, jint b)
{
	struct java_lang_String* retVal = NULL;
	wchar_t* pwstrName;
	wchar_t* stringChars;
	int UIMask;
	NPP instance;
	PluginInstance* This;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = NULL;
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = NULL;
			_lastErrCode = VS_PLUGIN_NOINST;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			UIMask = b;
			
			if((pwstrName = NZ_NotarizeHash(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a),UIMask)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrName, SysStringLen((BSTR)pwstrName));
				SysFreeString((BSTR)pwstrName);
			}
		}
	}

	return retVal;
}

/*** public native NZ_VerifyNotarizationRecord (Ljava/lang/String;II)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_NZ_0005fVerifyNotarizationRecord(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b, jint c, jint d)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars, *stringChars2;
	int nRecordType, nUIMask;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);

			nRecordType = c;
			nUIMask = d;
		
			//Call our wrapper
			if(b == NULL)
				err = NZ_VerifyNotarizationRecord(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a), NULL, 0, nRecordType, nUIMask);
			else
			{
				//Convert from java string to wchar
				stringChars2 = (wchar_t*)JRI_GetStringChars(env, b);
				err = NZ_VerifyNotarizationRecord(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a), stringChars2, JRI_GetStringLength(env,b), nRecordType, nUIMask);
			}
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native NZ_AddCertificate (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_NZ_0005fAddCertificate(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
		
			//Call our wrapper
			err = NZ_AddCertificate(This->fPlatform.pVSNZ, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_LogoUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fLogoUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_LogoUrl(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_SelFileTitle (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fSelFileTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_SelFileTitle(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_SelFileDescription (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fSelFileDescription(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_SelFileDesc(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_SelFileHelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fSelFileHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_SelFileHelpUrl(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_ProgressTitle (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fProgressTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_ProgressTitle(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_ProgressDescription (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fProgressDescription(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_ProgressDesc(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_ProgressHelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fProgressHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_ProgressHelpUrl(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}

/*** public native set_NZ_UIPrefs_ReceiptTitle (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fReceiptTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_ReceiptTitle(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_ReceiptDescription (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fReceiptDescription(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_ReceiptDesc(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_ReceiptHelpUrl (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fReceiptHelpUrl(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_ReceiptHelpUrl(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_UIPrefs_WizardTitle (Ljava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fUIPrefs_0005fWizardTitle(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL) 
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			
			//Call our wrapper
			err = NZ_set_UIPrefs_WizardTitle(This->fPlatform.pNZUIPrefs, stringChars, JRI_GetStringLength(env,a));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}


/*** public native set_NZ_ApplicationPreference (Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)I ***/
extern JRI_PUBLIC_API(jint)
native_VSPTAv3_set_0005fNZ_0005fApplicationPreference(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b, jint c, struct java_lang_String *d)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars, *stringCharsB, *stringCharsD;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL || b == NULL || d == NULL || c > 1)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			stringCharsB = (wchar_t*)JRI_GetStringChars(env, b);
			stringCharsD = (wchar_t*)JRI_GetStringChars(env, d);

			//Call our wrapper
			err = NZ_set_ApplicationPref(This->fPlatform.pNZAppPrefs, stringChars, JRI_GetStringLength(env,a),
									stringCharsB, JRI_GetStringLength(env,b), c, stringCharsD, JRI_GetStringLength(env,d));
		
			if(err != VS_NO_ERROR)
				retVal = err;
		}
	}

	return retVal;
}



/*** public native get_NZ_ApplicationPreference (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String; ***/
extern JRI_PUBLIC_API(struct java_lang_String *)
native_VSPTAv3_get_0005fNZ_0005fApplicationPreference(JRIEnv* env, struct VSPTAv3* self, struct java_lang_String *a, struct java_lang_String *b)
{
	unsigned int retVal = VS_NO_ERROR;
	wchar_t* stringChars, *stringCharsB;
	wchar_t* pwstrPref;
	NPP instance;
	PluginInstance* This;
	unsigned int err;

	if(env == NULL || self == NULL || a == NULL || b == NULL)
	{
		retVal = VS_INVALID_ARG;
		_lastErrCode = retVal;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = retVal;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;

			//Convert from java string to wchar
			stringChars = (wchar_t*)JRI_GetStringChars(env, a);
			stringCharsB = (wchar_t*)JRI_GetStringChars(env, b);
			
			//Call our wrapper
			if((pwstrPref = NZ_get_ApplicationPref(This->fPlatform.pNZAppPrefs, stringChars, JRI_GetStringLength(env,a),
										stringCharsB, JRI_GetStringLength(env,b))) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				retVal = JRI_NewString(env, (const jchar*)pwstrPref, SysStringLen((BSTR)pwstrPref));
				SysFreeString((BSTR)pwstrPref);
			}
		}
	}

	return retVal;
}

/*******************************************************************************
 * SECTION 5 - Utility Method Implementations
 ******************************************************************************

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * DisplayJavaMessage
 *
 * This function is a utility routine that calls back into Java to print
 * messages to the Java Console and to stdout (via the native method,
 * native_Simple_printToStdout, defined below).  Sure, it's not a very
 * interesting use of Java, but it gets the point across.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

/*------------------------------------------------------------------------------
 * Platform-Specific Implemenations
 *------------------------------------------------------------------------------
 * UNIX Implementations
 *----------------------------------------------------------------------------*/
#ifdef XP_UNIX
void Redraw(Widget w, XtPointer closure, XEvent *event);

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
PlatformNew( PluginInstance* This )
{
	This->fPlatform.window = 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformDestroy( PluginInstance* This )
{
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformSetWindow( PluginInstance* This, NPWindow* window )
{
	Widget netscape_widget;

	This->fPlatform.window = (Window) window->window;
	This->fPlatform.x = window->x;
	This->fPlatform.y = window->y;
	This->fPlatform.width = window->width;
	This->fPlatform.height = window->height;
	This->fPlatform.display = ((NPSetWindowCallbackStruct *)window->ws_info)->display;
	
    netscape_widget = XtWindowToWidget(This->fPlatform.display, This->fPlatform.window);
	XtAddEventHandler(netscape_widget, ExposureMask, FALSE, (XtEventHandler)Redraw, This);
	Redraw(netscape_widget, (XtPointer)This, NULL);
	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
int16
PlatformHandleEvent( PluginInstance* This, void* event )
{
	/* UNIX Plugins do not use HandleEvent */
	return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * Redraw
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
Redraw(Widget w, XtPointer closure, XEvent *event)
{
	PluginInstance* This = (PluginInstance*)closure;
	GC gc;
	XGCValues gcv;
	const char* text = This->fOutString;

	XtVaGetValues(w, XtNbackground, &gcv.background,
				  XtNforeground, &gcv.foreground, 0);
	gc = XCreateGC(This->fPlatform.display, This->fPlatform.window, 
				   GCForeground|GCBackground, &gcv);
	XDrawRectangle(This->fPlatform.display, This->fPlatform.window, gc, 
				   0, 0, This->fPlatform.width-1, This->fPlatform.height-1);
	XDrawString(This->fPlatform.display, This->fPlatform.window, gc, 
				This->fPlatform.width/2 - 100, This->fPlatform.height/2,
				text, strlen(text));
}
#endif /* XP_UNIX */

/*------------------------------------------------------------------------------
 * Windows Implementations
 *----------------------------------------------------------------------------*/
#ifdef XP_PC
LRESULT CALLBACK PluginWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
const char* gInstanceLookupString = "instance->pdata";

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
PlatformNew( PluginInstance* This )
{
	This->fPlatform.fhWnd = NULL;
	This->fPlatform.fDefaultWindowProc = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformDestroy( PluginInstance* This )
{

	if( This->fWindow != NULL ) { /* If we have a window, clean

								 * it up. */

		SetWindowLong( This->fPlatform.fhWnd, GWL_WNDPROC, (LONG)This->fPlatform.fDefaultWindowProc);

		This->fPlatform.fDefaultWindowProc = NULL;

		This->fPlatform.fhWnd = NULL;

	}



	return NPERR_NO_ERROR;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformSetWindow( PluginInstance* This, NPWindow* window )
{
	if( This->fWindow != NULL ) /* If we already have a window, clean
								 * it up before trying to subclass
								 * the new window. */
	{
		if( (window == NULL) || ( window->window == NULL ) ) {
			/* There is now no window to use. get rid of the old
			 * one and exit. */
			SetWindowLong( This->fPlatform.fhWnd, GWL_WNDPROC, (LONG)This->fPlatform.fDefaultWindowProc);
			This->fPlatform.fDefaultWindowProc = NULL;
			This->fPlatform.fhWnd = NULL;
			return NPERR_NO_ERROR;
		}

		else if ( This->fPlatform.fhWnd == (HWND) window->window ) {
			/* The new window is the same as the old one. Redraw and get out. */

			InvalidateRect( This->fPlatform.fhWnd, NULL, TRUE );

			UpdateWindow( This->fPlatform.fhWnd );


			return NPERR_NO_ERROR;
		}
		else {
			/* Clean up the old window, so that we can subclass the new
			 * one later. */
			SetWindowLong( This->fPlatform.fhWnd, GWL_WNDPROC, (LONG)This->fPlatform.fDefaultWindowProc);
			This->fPlatform.fDefaultWindowProc = NULL;
			This->fPlatform.fhWnd = NULL;
		}
	}
	else if( (window == NULL) || ( window->window == NULL ) ) {
		/* We can just get out of here if there is no current
		 * window and there is no new window to use. */
		return NPERR_NO_ERROR;
	}

	/* At this point, we will subclass
	 * window->window so that we can begin drawing and
	 * receiving window messages. */
	This->fPlatform.fDefaultWindowProc = (WNDPROC)SetWindowLong( (HWND)window->window, GWL_WNDPROC, (LONG)PluginWindowProc);
	This->fPlatform.fhWnd = (HWND) window->window;
	SetProp( This->fPlatform.fhWnd, gInstanceLookupString, (HANDLE)This);

	InvalidateRect( This->fPlatform.fhWnd, NULL, TRUE );
	UpdateWindow( This->fPlatform.fhWnd );
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
int16
PlatformHandleEvent( PluginInstance* This, void* event )
{
	/* Windows Plugins use the Windows event call-back mechanism
	   for events. (See PluginWindowProc) */
	return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PluginWindowProc
 *
 * Handle the Windows window-event loop.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
LRESULT CALLBACK PluginWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	PluginInstance* This = (PluginInstance*) GetProp(hWnd, gInstanceLookupString);

	switch( Msg ) {
		//case WM_PAINT: {
		//	PAINTSTRUCT paintStruct;
		//	HDC hdc;

		//	hdc = BeginPaint( hWnd, &paintStruct );
		//	TextOut(hdc, 0, 0, "Hello", strlen( "Hello" ) );

		//	EndPaint( hWnd, &paintStruct );
		//	break;
		//}
		default: {
			This->fPlatform.fDefaultWindowProc( hWnd, Msg, wParam, lParam);
		}
	}
	return 0;
}
#endif /* XP_PC */




/*------------------------------------------------------------------------------
 * Macintosh Implementations
 *----------------------------------------------------------------------------*/
#ifdef macintosh
NPBool	StartDraw(NPWindow* window);
void 	EndDraw(NPWindow* window);
void 	DoDraw(PluginInstance* This);

CGrafPort 		gSavePort;
CGrafPtr		gOldPort;

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
PlatformNew( PluginInstance* This )
{
	return;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformDestroy( PluginInstance* This )
{
	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPError
PlatformSetWindow( PluginInstance* This, NPWindow* window )
{
	This->fWindow = window;
	if( StartDraw( window ) ) {
		DoDraw(This);
		EndDraw( window );
	}
	return NPERR_NO_ERROR;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
int16
PlatformHandleEvent( PluginInstance* This, void* event )
{
	int16 eventHandled = FALSE;
	
	EventRecord* ev = (EventRecord*) event;
	if (This != NULL && event != NULL)
	{
		switch (ev->what)
		{
			/*
			 * Draw ourselves on update events
			 */
			case updateEvt:
				if( StartDraw( This->fWindow ) ) {
					DoDraw(This);
					EndDraw( This->fWindow );
				}
				eventHandled = true;
				break;
			default:
				break;
		}
	}
	return eventHandled;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * StartDraw
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
NPBool
StartDraw(NPWindow* window)
{
	NP_Port* port;
	Rect clipRect;
	RGBColor  col;
	
	if (window == NULL)
		return FALSE;
	port = (NP_Port*) window->window;
	if (window->clipRect.left < window->clipRect.right)
	{
	/* Preserve the old port */
		GetPort((GrafPtr*)&gOldPort);
		SetPort((GrafPtr)port->port);
	/* Preserve the old drawing environment */
		gSavePort.portRect = port->port->portRect;
		gSavePort.txFont = port->port->txFont;
		gSavePort.txFace = port->port->txFace;
		gSavePort.txMode = port->port->txMode;
		gSavePort.rgbFgColor = port->port->rgbFgColor;
		gSavePort.rgbBkColor = port->port->rgbBkColor;
		GetClip(gSavePort.clipRgn);
	/* Setup our drawing environment */
		clipRect.top = window->clipRect.top + port->porty;
		clipRect.left = window->clipRect.left + port->portx;
		clipRect.bottom = window->clipRect.bottom + port->porty;
		clipRect.right = window->clipRect.right + port->portx;
		SetOrigin(port->portx,port->porty);
		ClipRect(&clipRect);
		clipRect.top = clipRect.left = 0;
		TextSize(12);
		TextFont(geneva);
		TextMode(srcCopy);
		col.red = col.green = col.blue = 0;
		RGBForeColor(&col);
		col.red = col.green = col.blue = 65000;
		RGBBackColor(&col);
		return TRUE;
	}
	else
		return FALSE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * EndDraw
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
EndDraw(NPWindow* window)
{
	CGrafPtr myPort;
	NP_Port* port = (NP_Port*) window->window;
	SetOrigin(gSavePort.portRect.left, gSavePort.portRect.top);
	SetClip(gSavePort.clipRgn);
	GetPort((GrafPtr*)&myPort);
	myPort->txFont = gSavePort.txFont;
	myPort->txFace = gSavePort.txFace;
	myPort->txMode = gSavePort.txMode;
	RGBForeColor(&gSavePort.rgbFgColor);
	RGBBackColor(&gSavePort.rgbBkColor);
	SetPort((GrafPtr)gOldPort);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * DoDraw
 +++++++++++++++++++++++++++++++++++++++++++++++++*/
void
DoDraw(PluginInstance* This)
{
	Rect drawRect;
	char* pascalString;
	
	pascalString = (char*) NPN_MemAlloc( strlen( This->fOutString ) + 1);
	strcpy( pascalString, This->fOutString );
	
	drawRect.top = 0;
	drawRect.left = 0;
	drawRect.bottom = drawRect.top + This->fWindow->height;
	drawRect.right = drawRect.left + This->fWindow->width;
	EraseRect( &drawRect );
	MoveTo( 2, 12 );
	DrawString(c2pstr(pascalString));
}
#endif /* macintosh */

/******************************************************************************/


NPError InitControls(PlatformInstance* fPlatform, const char* pControlClsid)
{
	NPError result = NPERR_GENERIC_ERROR;
	int errNo = 0;

	do
	{
		fPlatform->pVSNZ = NULL;
		fPlatform->pNZUIPrefs = NULL;
		fPlatform->pNZAppPrefs = NULL;

		fPlatform->boolXenrollInitialized = TRUE;
		fPlatform->boolImportInitialized = TRUE;
		fPlatform->boolAddRootsInitialized = TRUE;

		if(pControlClsid == NULL)	// PTA is not getting aggregated
		{
			if((fPlatform->pPTA = PTA_CreateInstance()) == NULL)
			{
				errNo = 1;
				break;
			}
		}
		else 
			if(stricmp(pControlClsid, NZ_CLSID) == 0)
			{
				if((fPlatform->pVSNZ = NZ_CreateInstance()) == NULL)
				{
					return NPERR_GENERIC_ERROR;

					//errNo = 2;
					//break;
				}
		
				if((fPlatform->pPTA = NZ_CreatePTAInstance(fPlatform->pVSNZ)) == NULL)
				{
					errNo = 3;
					break;
				}

				if((fPlatform->pNZUIPrefs = NZ_UIPrefs_GetInstance(fPlatform->pVSNZ)) == NULL)
				{
					errNo = 4;
					break;
				}

				if((fPlatform->pNZAppPrefs = NZ_AppPrefs_GetInstance(fPlatform->pVSNZ)) == NULL)
				{
					errNo = 5;
					break;
				}
			}
			else
			{
				errNo = 6;
				break;
			}

		if((fPlatform->pCertPrefs = CertPrefs_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 7;
			break;
		}

		if((fPlatform->pPTAApi = PTADllApi_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 8;
			break;
		}

		if((fPlatform->pProfMgmt = ProfMgmt_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 9;
			break;
		}

		if((fPlatform->pRoamPrefs = RoamPrefs_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 10;
			break;
		}

		if((fPlatform->pSelectedDigID = SelectedDigID_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 11;
			break;
		}
	
		if((fPlatform->pSrchCrit = SrchCrit_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 12;
			break;
		}
	
		if((fPlatform->pUIPrefs = UIPrefs_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 13;
			break;
		}
		
		if((fPlatform->pP12Import = P12Import_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 14;
			break;
		}

		if((fPlatform->pP12Export = P12Export_GetInstance(fPlatform->pPTA)) == NULL)
		{
			errNo = 15;
			break;
		}

		if((fPlatform->pEnroll = Enroll_CreateInstance()) == NULL) 
		{
			fPlatform->boolXenrollInitialized = FALSE;
			fPlatform->pEnroll = NULL;
		}
    
		if((fPlatform->pImport = Import_CreateInstance()) == NULL) 
		{
			fPlatform->boolImportInitialized = FALSE;
			fPlatform->pImport = NULL;
		}
	
		if((fPlatform->pAddRoots = AddRoots_CreateInstance()) == NULL) 
		{
			fPlatform->boolAddRootsInitialized = FALSE;
			fPlatform->pAddRoots = NULL;
		}
	
		result = NPERR_NO_ERROR;

	}while(0);

	if(result == NPERR_GENERIC_ERROR)
	{
		TCHAR szErrMsg[256];
		wsprintf(szErrMsg, "An error occured while loading the plugin. Please contact your administrator.\nError %x", errNo);
		MessageBox(NULL, szErrMsg, "Plugin Error", MB_OK);
	}

	return result;
}
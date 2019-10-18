/*******************************************************************************
 * SECTION 1 - Includes
 ******************************************************************************/
//#include "h:\helperaps\include\generic.h"

#include <stdio.h>
#include <string.h>

#include "nsplugin.h"
#include "nsIServiceManager.h"
#include "nsISupports.h"
#include "nsIFactory.h"
#include "nsIGenericFactory.h"
#include "nsMemory.h"
#include "nsString.h"
#include "..\include\N6PTACID.h"

#include "..\include\N6PTA.h"
#include "nsIScriptablePlugin.h"

#include "addrootswrap.h"
#include "p12wrap.h"
#include "vscertprefswrap.h"
#include "vsimport.h"
#include "vsimportwrap.h"
#include "vsprofmgmtwrap.h"
#include "vsptadllapiwrap.h"
#include "vsptawrap.h"
#include "vsroamprefswrap.h"
#include "vsselecteddigidwrap.h"
#include "vssrchcritwrap.h"
#include "vsuiprefswrap.h"
#include "XEnrollWrap.h"
#include "vsdnzwrap.h"
#include "global.h"
#include "time.h"

#include "..\resource.h"

/*------------------------------------------------------------------------------
 * Windows Includes
 *----------------------------------------------------------------------------*/
#ifdef _WINDOWS /* Windows Includes */
#include <windows.h>
#endif /* _WINDOWS */


HRESULT	_lastErrCode;

HINSTANCE hInst = NULL;
HWND hwndDlgBox = NULL;
LPSTR	szUAgent = NULL;

/*------------------------------------------------------------------------------
 * UNIX includes
 *----------------------------------------------------------------------------*/
#ifdef XP_UNIX
#include <gdk/gdk.h>
#include <gdk/gdkprivate.h>
#include <gtk/gtk.h>
#include <gdksuperwin.h>
#include <gtkmozbox.h>
#endif /* XP_UNIX */

#ifdef XP_UNIX

gboolean draw (GtkWidget *widget, GdkEventExpose *event, gpointer data);

#endif


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

#if defined(XP_PC) && !defined(XP_OS2)          // XXXX OS2TODO
typedef struct _PlatformInstance
{
    HWND		fhWnd;
    WNDPROC		fDefaultWindowProc;
} PlatformInstance;

/*------------------------------------------------------------------------------
 * UNIX PlatformInstance
 *----------------------------------------------------------------------------*/

#elif defined(XP_UNIX)
typedef struct _PlatformInstance
{
    Window 		       window;
    GtkWidget         *moz_box;
    GdkSuperWin       *superwin;
    GtkWidget         *label;
    Display *		   display;
    uint32 		       x, y;
    uint32 		       width, height;
} PlatformInstance;

/*------------------------------------------------------------------------------
 * Macintosh PlatformInstance
 *----------------------------------------------------------------------------*/

#elif defined(XP_MAC)
typedef struct _PlatformInstance
{
    int			placeholder;
} PlatformInstance;

/*------------------------------------------------------------------------------
 * Stub PlatformInstance
 *----------------------------------------------------------------------------*/

#else
typedef struct _PlatformInstance
{
    int			placeholder;
} PlatformInstance;
#endif /* end Section 2 */


// Define constants for easy use
static NS_DEFINE_CID(kSimplePluginCID, NS6_PTA_PLUGIN_CID);
static NS_DEFINE_CID(kPluginManagerCID, NS_PLUGINMANAGER_CID);

#define PLUGIN_MIME_TYPE "application/x-vspta2-plugin"

static const char kPluginName[] = "VeriSign Personal Trust Agent";
static const char kPluginDescription[] = "3505";

static const char* kMimeTypes[] = {
    PLUGIN_MIME_TYPE
};

static const char* kMimeDescriptions[] = {
    "Personal Trust Agent"
};

static const char* kFileExtensions[] = {
    "pta"
};

static const PRInt32 kNumMimeTypes = sizeof(kMimeTypes) / sizeof(*kMimeTypes);



////////////////////////////////////////////////////////////////////////////////
// Simple Plugin Classes
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// cns6PTA represents an instance of the simple plugin class.

#define		NZ_CLSID		"d66256e2-b99c-11d4-8c74-0010830169af"

class cns6PTA : 
    public nsIPluginInstance, 
    public nsIScriptablePlugin,
    public ns6IPTA {
private:
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
	BOOL            boolXenrollInitialized;
	BOOL            boolImportInitialized;
	BOOL			boolAddRootsInitialized;

	// Digital Notarization interfaces
	IVSNZ*			pVSNZ;
	IVSNZUIPrefs*	pNZUIPrefs;
	IVSNZAppPrefs*	pNZAppPrefs;

	LPSTR			m_szPageURL;
	LPSTR			m_szHostName;
	LPSTR			m_szProtocol;

public:
    ////////////////////////////////////////////////////////////////////////////
    // for implementing a generic module
    static NS_METHOD
    Create(nsISupports* aOuter, REFNSIID aIID, void** aResult);

    static NS_METHOD
    RegisterSelf(nsIComponentManager* aCompMgr,
                 nsIFile* aPath,
                 const char* aRegistryLocation,
                 const char* aComponentType);

    static NS_METHOD
    UnregisterSelf(nsIComponentManager* aCompMgr,
                   nsIFile* aPath,
                   const char* aRegistryLocation);


    NS_DECL_ISUPPORTS
    NS_DECL_NSISCRIPTABLEPLUGIN
    NS_DECL_NS6IPTA

	PRInt32 SetPageURL (const char* i_cszPageURL);

    ////////////////////////////////////////////////////////////////////////////
    // from nsIEventHandler:

    // (Corresponds to NPP_HandleEvent.)
    // Note that for Unix and Mac the nsPluginEvent structure is different
    // from the old NPEvent structure -- it's no longer the native event
    // record, but is instead a struct. This was done for future extensibility,
    // and so that the Mac could receive the window argument too. For Windows
    // and OS2, it's always been a struct, so there's no change for them.
    NS_IMETHOD
    HandleEvent(nsPluginEvent* event, PRBool* handled);

    ////////////////////////////////////////////////////////////////////////////
    // from nsIPluginInstance:

    NS_IMETHOD
    Initialize(nsIPluginInstancePeer* peer);

    // Required backpointer to the peer.
    NS_IMETHOD
    GetPeer(nsIPluginInstancePeer* *result);

    // See comment for nsIPlugin::CreateInstance, above.
    NS_IMETHOD
    Start(void);

    // The old NPP_Destroy call has been factored into two plugin instance 
    // methods:
    //
    // Stop -- called when the plugin instance is to be stopped (e.g. by 
    // displaying another plugin manager window, causing the page containing 
    // the plugin to become removed from the display).
    //
    // Destroy -- called once, before the plugin instance peer is to be 
    // destroyed. This method is used to destroy the plugin instance. 

    NS_IMETHOD
    Stop(void);

    NS_IMETHOD
    Destroy(void);

    // (Corresponds to NPP_SetWindow.)
    NS_IMETHOD
    SetWindow(nsPluginWindow* window);

    NS_IMETHOD
    NewStream(nsIPluginStreamListener** listener);

    // (Corresponds to NPP_Print.)
    NS_IMETHOD
    Print(nsPluginPrint* platformPrint);

    NS_IMETHOD
    GetValue(nsPluginInstanceVariable variable, void *value);


    ////////////////////////////////////////////////////////////////////////////
    // cns6PTA specific methods:

    cns6PTA(void);
    virtual ~cns6PTA(void);

    void            PlatformNew(void);
    nsresult        PlatformDestroy(void);
    nsresult    	PlatformSetWindow(nsPluginWindow* window);
    PRInt16         PlatformHandleEvent(nsPluginEvent* event);

    void SetMode(nsPluginMode mode) { fMode = mode; }

#ifdef XP_UNIX
    NS_IMETHOD Repaint(void);
#endif

#if defined(XP_PC) && !defined(XP_OS2)
    static LRESULT CALLBACK 
    PluginWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
#endif

	// For initializing all the activex controls
	NS_METHOD InitControls(const char* pControlClsid);

    char*                       fText;
	PRInt32						number;
	PRInt32						ans;


protected:
    nsIPluginInstancePeer*      fPeer;
    nsPluginWindow*             fWindow;
    nsPluginMode                fMode;
    PlatformInstance            fPlatform;
};

////////////////////////////////////////////////////////////////////////////////
// SimplePluginStream represents the stream used by SimplePluginInstances
// to receive data from the browser. 

class SimplePluginStreamListener : public nsIPluginStreamListener {
public:

    NS_DECL_ISUPPORTS

    ////////////////////////////////////////////////////////////////////////////
    // from nsIPluginStreamListener:

    /**
     * Notify the observer that the URL has started to load.  This method is
     * called only once, at the beginning of a URL load.<BR><BR>
     *
     * @return The return value is currently ignored.  In the future it may be
     * used to cancel the URL load..
     */
    NS_IMETHOD
    OnStartBinding(nsIPluginStreamInfo* pluginInfo);

    /**
     * Notify the client that data is available in the input stream.  This
     * method is called whenver data is written into the input stream by the
     * networking library...<BR><BR>
     * 
     * @param aIStream  The input stream containing the data.  This stream can
     * be either a blocking or non-blocking stream.
     * @param length    The amount of data that was just pushed into the stream.
     * @return The return value is currently ignored.
     */
    NS_IMETHOD
    OnDataAvailable(nsIPluginStreamInfo* pluginInfo, 
                                            nsIInputStream* input, 
                                            PRUint32 length);

    NS_IMETHOD
    OnFileAvailable(nsIPluginStreamInfo* pluginInfo, const char* fileName);

    /**
     * Notify the observer that the URL has finished loading.  This method is 
     * called once when the networking library has finished processing the 
     * URL transaction initiatied via the nsINetService::Open(...) call.<BR><BR>
     * 
     * This method is called regardless of whether the URL loaded successfully.<BR><BR>
     * 
     * @param status    Status code for the URL load.
     * @param msg   A text string describing the error.
     * @return The return value is currently ignored.
     */
    NS_IMETHOD
    OnStopBinding(nsIPluginStreamInfo* pluginInfo, nsresult status);

    NS_IMETHOD
    OnNotify(const char* url, nsresult status);

    NS_IMETHOD
    GetStreamType(nsPluginStreamType *result);

    ////////////////////////////////////////////////////////////////////////////
    // SimplePluginStreamListener specific methods:

    SimplePluginStreamListener(cns6PTA* inst, const char* url);
    virtual ~SimplePluginStreamListener(void);

protected:
    const char*                 fMessageName;
	cns6PTA*					pcsn6PTAInst;
};

/*******************************************************************************
 * SECTION 3 - API Plugin Implementations
 ******************************************************************************/
// XXXwaterson document!
static nsModuleComponentInfo gComponentInfo[] = {
    { "VeriSign Personal Trust Agent",
      NS6_PTA_PLUGIN_CID,
      NS_INLINE_PLUGIN_CONTRACTID_PREFIX PLUGIN_MIME_TYPE,
      cns6PTA::Create,
      cns6PTA::RegisterSelf,
      cns6PTA::UnregisterSelf },
};

NS_IMPL_NSGETMODULE("VeriSignTestPlugin", gComponentInfo);



////////////////////////////////////////////////////////////////////////////////
// nsIScriptablePlugin methods
////////////////////////////////////////////////////////////////////////////////
NS_METHOD
cns6PTA::GetScriptablePeer(void **aScriptablePeer)
{
   // We implement the interface we want to be scriptable by
   // (ns6IPTA) so we just return this.

   // NOTE if this function returns something other than
   // nsIPluginInstance, then that object will also need to implement
   // nsISecurityCheckedComponent to be scriptable.  The security
   // system knows to special-case nsIPluginInstance when checking
   // security, but in general, XPCOM components must implement
   // nsISecurityCheckedComponent to be scriptable from content
   // javascript.

   *aScriptablePeer = NS_STATIC_CAST(ns6IPTA *, this);
   NS_ADDREF(NS_STATIC_CAST(ns6IPTA *, *aScriptablePeer));
   return NS_OK;
}

NS_METHOD
cns6PTA::GetScriptableInterface(nsIID **aScriptableInterface)
{
  *aScriptableInterface = (nsIID *)nsMemory::Alloc(sizeof(nsIID));
  NS_ENSURE_TRUE(*aScriptableInterface, NS_ERROR_OUT_OF_MEMORY);

  **aScriptableInterface = NS_GET_IID(ns6IPTA);

  return NS_OK;
}

////////////////////////////////////////////////////////////////////////////////
// cns6PTA Methods
////////////////////////////////////////////////////////////////////////////////

NS_METHOD
cns6PTA::Create(nsISupports* aOuter, REFNSIID aIID, void** aResult)
{
//	::MessageBox(NULL, "Create", "VeriSign Test", MB_OK);
    NS_PRECONDITION(aOuter == nsnull, "no aggregation");
    if (aOuter)
        return NS_ERROR_NO_AGGREGATION;

    cns6PTA* plugin = new cns6PTA();
    if (! plugin)
        return NS_ERROR_OUT_OF_MEMORY;

    nsresult rv;
    NS_ADDREF(plugin);
    rv = plugin->QueryInterface(aIID, aResult);
    NS_RELEASE(plugin);
    return rv;
}

NS_METHOD
cns6PTA::RegisterSelf(nsIComponentManager* aCompMgr,
                                   nsIFile* aPath,
                                   const char* aRegistryLocation,
                                   const char* aComponentType)
{
    nsresult rv;
	
//	::MessageBox(NULL, "Register", "VeriSign Test", MB_OK);
    nsIPluginManager* pm;

    rv = nsServiceManager::GetService(kPluginManagerCID, NS_GET_IID(nsIPluginManager),
                                      NS_REINTERPRET_CAST(nsISupports**, &pm));

    if (NS_SUCCEEDED(rv)) {
        rv = pm->RegisterPlugin(kSimplePluginCID,
                                kPluginName,
                                kPluginDescription,
                                kMimeTypes,
                                kMimeDescriptions,
                                kFileExtensions,
                                kNumMimeTypes);

        NS_RELEASE(pm);
    }

    return rv;
}


NS_METHOD
cns6PTA::UnregisterSelf(nsIComponentManager* aCompMgr,
                                     nsIFile* aPath,
                                     const char* aRegistryLocation)
{
    nsresult rv;

//	::MessageBox(NULL, "unregister", "VeriSign Test", MB_OK);

    nsIPluginManager* pm;
    rv = nsServiceManager::GetService(kPluginManagerCID, NS_GET_IID(nsIPluginManager),
                                      NS_REINTERPRET_CAST(nsISupports**, &pm));
    if (NS_SUCCEEDED(rv)) {
        rv = pm->UnregisterPlugin(kSimplePluginCID);
        NS_RELEASE(pm);
    }

    return rv;
}


cns6PTA::cns6PTA(void)
//    : fText(NULL), fPeer(NULL), fWindow(NULL), fMode(nsPluginMode_Embedded)
{
    NS_INIT_REFCNT();

    static const char text[] = "Hello World!";
    fText = (char*) nsMemory::Clone(text, sizeof(text));
	number = 0;
	ans = 0;

	pEnroll = NULL;
//	pCnfChk = NULL;
	pImport = NULL;
	pAddRoots = NULL;
	pUIPrefs = NULL;
	pProfMgmt = NULL;
	pCertPrefs = NULL;
	pSrchCrit = NULL;
	pSelectedDigID = NULL;
	pP12Import = NULL;
	pP12Export = NULL;
	pRoamPrefs = NULL;
	pPTA = NULL;
	pPTAApi = NULL;
	
	boolXenrollInitialized = FALSE;
	boolImportInitialized = FALSE;
	boolAddRootsInitialized = FALSE;

	m_szPageURL = NULL;
	m_szHostName = NULL;
	m_szProtocol = NULL;


#ifdef XP_UNIX
    fPlatform.moz_box = nsnull;
    fPlatform.superwin = nsnull;
    fPlatform.label = nsnull;
#endif

}

cns6PTA::~cns6PTA(void)
{
    if(fText)
        nsMemory::Free(fText);
    PlatformDestroy(); // Perform platform specific cleanup
}


PRInt32 cns6PTA::SetPageURL (const char* i_cszPageURL)
{
//	::MessageBox(NULL, "enter", "setpageurl", MB_OK);

	LPSTR szURL;
	LPSTR szptrTemp;
	int nProtocolSize;
	int nHostNameSize;

	if (NULL == i_cszPageURL)
	{
		return	VS_INVALID_ARG;
	}

	if (NULL != m_szPageURL)
	{
		delete [] m_szPageURL;
		m_szPageURL = NULL;
	}

	m_szPageURL = new char [strlen(i_cszPageURL) + 1];
	if ( NULL == m_szPageURL )
	{
		return	NPERR_GENERIC_ERROR;
	}

	strcpy (m_szPageURL, i_cszPageURL);

//	::MessageBox(NULL, m_szPageURL, "Plugin", MB_OK);

	szURL = (char*) i_cszPageURL;
	
	//Separate out the host name and the protocol
	if(m_szProtocol)
			free(m_szProtocol);
	szptrTemp = strtok(szURL,":");	
	if(szptrTemp)
	{	
		nProtocolSize = strlen(szptrTemp);
		m_szProtocol = (LPSTR)malloc(sizeof(char)*(nProtocolSize+1));
		strcpy(m_szProtocol,szptrTemp);
		m_szProtocol[nProtocolSize] = '\0';
	}
	else
	{
		m_szProtocol = NULL;
	}
	
	if(m_szHostName)
		free(m_szHostName);
	szptrTemp = szptrTemp + nProtocolSize + 3;
	szptrTemp = strtok(szptrTemp,":/");
	if(szptrTemp)
	{
		nHostNameSize = strlen(szptrTemp);
		m_szHostName = (LPSTR)malloc(sizeof(char)*(nHostNameSize+1));
		strcpy(m_szHostName,szptrTemp);
		m_szHostName[nHostNameSize] = '\0';
	}
	else
	{
		m_szHostName = NULL;
	}

	if(hwndDlgBox)
	{
		SendMessage(hwndDlgBox,WM_QUIT,0,0);
	}

//	::MessageBox(NULL, m_szHostName, "Plugin", MB_OK);
//	::MessageBox(NULL, m_szProtocol, "Plugin", MB_OK);
	

	return NS_OK;
}

// These macros produce simple version of QueryInterface and AddRef.
// See the nsISupports.h header file for details.

NS_IMPL_ISUPPORTS3(cns6PTA, nsIPluginInstance, ns6IPTA, nsIScriptablePlugin)

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NewInstance:
 * Creates a new instance of a plug-in and returns an error value. 
 * 
 * NewInstance creates a new instance of your plug-in with MIME type specified
 * by pluginType. The parameter mode is NP_EMBED if the instance was created
 * by an EMBED tag, or NP_FULL if the instance was created by a separate file.
 * You can allocate any instance-specific private data in instance->pdata at this
 * time. The NPP pointer is valid until the instance is destroyed. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

NS_METHOD
cns6PTA::Initialize(nsIPluginInstancePeer* peer)
{
#ifdef NS_DEBUG
    printf("cns6PTA::Initialize\n");
#endif

	_lastErrCode = 0;
    
    NS_ASSERTION(peer != NULL, "null peer");

    fPeer = peer;
    nsIPluginTagInfo* taginfo;
    const char* const* names = nsnull;
    const char* const* values = nsnull;
	char* pControlClsid = NULL;
    PRUint16 count = 0;
    nsresult result;
/*

	pEnroll = NULL;
//	pCnfChk = NULL;
	pImport = NULL;
	pAddRoots = NULL;
	pUIPrefs = NULL;
	pProfMgmt = NULL;
	pCertPrefs = NULL;
	pSrchCrit = NULL;
	pSelectedDigID = NULL;
	pP12Import = NULL;
	pRoamPrefs = NULL;
	pPTA = NULL;
	pPTAApi = NULL;
	
	boolXenrollInitialized = FALSE;
	boolImportInitialized = FALSE;
	boolAddRootsInitialized = FALSE;

	m_szPageURL = NULL;
*/
    peer->AddRef();
    result = peer->GetMode(&fMode);
    if (NS_FAILED(result)) return result;

   result = peer->QueryInterface(NS_GET_IID(nsIPluginTagInfo), (void **)&taginfo);

    if (!NS_FAILED(result))
    {
        taginfo->GetAttributes(count, names, values);
        NS_IF_RELEASE(taginfo);

		for(int i = 0; i < count; i++)
		{
			if(stricmp(names[i], "CLSID") == 0)
			{
				pControlClsid = (char *)values[i];
				break;
			}
		}
    }

	/*
#ifdef NS_DEBUG
    printf("Attribute count = %d\n", count);

    for (int i = 0; i < count; i++)
    {
        printf("plugin param=%s, value=%s\n", names[i], values[i]);
    }
#endif
*/
    PlatformNew(); 	/* Call Platform-specific initializations */

	result = InitControls(pControlClsid);

	/*boolXenrollInitialized = TRUE;
    boolImportInitialized = TRUE;
	boolAddRootsInitialized = TRUE;
	if ((pPTA = PTA_CreateInstance()) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0001","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	}
	else if((pCertPrefs = CertPrefs_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0002","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if ((pPTAApi = PTADllApi_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0009","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;		
	}
	else if ((pProfMgmt = ProfMgmt_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0004","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((pRoamPrefs = RoamPrefs_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0005","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((pSelectedDigID = SelectedDigID_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0006","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((pSrchCrit = SrchCrit_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0007","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;
	
	}
	else if((pUIPrefs = UIPrefs_GetInstance(pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0008","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;	
	}
	else if((pP12Import = P12Import_GetInstance (pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x0009","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;	
	}
	else if((pP12Export = P12Export_GetInstance (pPTA)) == NULL)
	{
		MessageBox(NULL, "An error occured while loading the plugin. Please contact your administrator.\nError 0x000A","Plugin Error", MB_OK);
		result = NPERR_GENERIC_ERROR;	
	}
	else {
		if((pEnroll = Enroll_CreateInstance()) == NULL) {
			boolXenrollInitialized = FALSE;
			pEnroll = NULL;
		}
    
		if((pImport = Import_CreateInstance()) == NULL) {
			pImport = NULL;
			boolImportInitialized = FALSE;
		}
	
		if ((pAddRoots = AddRoots_CreateInstance()) == NULL) {
			boolAddRootsInitialized = FALSE;
			pAddRoots = NULL;
		}
	}

    return NS_OK;*/

	if(result == NPERR_GENERIC_ERROR)
	{
		_lastErrCode = NS_ERROR_FAILURE;
		return NS_ERROR_FAILURE;
	}
}


NS_METHOD
cns6PTA::InitControls(const char* pControlClsid)
{
	nsresult result = NPERR_GENERIC_ERROR;
	int errNo = 0;

	do
	{
		pVSNZ = NULL;
		pNZUIPrefs = NULL;
		pNZAppPrefs = NULL;

		boolXenrollInitialized = TRUE;
		boolImportInitialized = TRUE;
		boolAddRootsInitialized = TRUE;

		if(pControlClsid == NULL)	// PTA is not getting aggregated
		{
			if((pPTA = PTA_CreateInstance()) == NULL)
			{
				errNo = 1;
				break;
			}
		}
		else 
			if(stricmp(pControlClsid, NZ_CLSID) == 0)
			{
				if((pVSNZ = NZ_CreateInstance()) == NULL)
				{
					return result;
					//errNo = 2;
					//break;
				}
		
				if((pPTA = NZ_CreatePTAInstance(pVSNZ)) == NULL)
				{
					errNo = 3;
					break;
				}

				if((pNZUIPrefs = NZ_UIPrefs_GetInstance(pVSNZ)) == NULL)
				{
					errNo = 4;
					break;
				}

				if((pNZAppPrefs = NZ_AppPrefs_GetInstance(pVSNZ)) == NULL)
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

		if((pCertPrefs = CertPrefs_GetInstance(pPTA)) == NULL)
		{
			errNo = 7;
			break;
		}

		if((pPTAApi = PTADllApi_GetInstance(pPTA)) == NULL)
		{
			errNo = 8;
			break;
		}

		if((pProfMgmt = ProfMgmt_GetInstance(pPTA)) == NULL)
		{
			errNo = 9;
			break;
		}

		if((pRoamPrefs = RoamPrefs_GetInstance(pPTA)) == NULL)
		{
			errNo = 10;
			break;
		}

		if((pSelectedDigID = SelectedDigID_GetInstance(pPTA)) == NULL)
		{
			errNo = 11;
			break;
		}
	
		if((pSrchCrit = SrchCrit_GetInstance(pPTA)) == NULL)
		{
			errNo = 12;
			break;
		}
	
		if((pUIPrefs = UIPrefs_GetInstance(pPTA)) == NULL)
		{
			errNo = 13;
			break;
		}
		
		if((pP12Import = P12Import_GetInstance(pPTA)) == NULL)
		{
			errNo = 14;
			break;
		}

		if((pP12Export = P12Export_GetInstance(pPTA)) == NULL)
		{
			errNo = 15;
			break;
		}

		if((pEnroll = Enroll_CreateInstance()) == NULL) 
		{
			boolXenrollInitialized = FALSE;
			pEnroll = NULL;
		}
    
		if((pImport = Import_CreateInstance()) == NULL) 
		{
			boolImportInitialized = FALSE;
			pImport = NULL;
		}
	
		if((pAddRoots = AddRoots_CreateInstance()) == NULL) 
		{
			boolAddRootsInitialized = FALSE;
			pAddRoots = NULL;
		}
	
		result = NS_OK;

	}while(0);

	if(result == NPERR_GENERIC_ERROR)
	{
		TCHAR szErrMsg[256];
		wsprintf(szErrMsg, "An error occured while loading the plugin. Please contact your administrator.\nError %x", errNo);
		MessageBox(NULL, szErrMsg, "Plugin Error", MB_OK);
	}

	return result;
}


NS_METHOD
cns6PTA::GetPeer(nsIPluginInstancePeer* *result)
{
#ifdef NS_DEBUG
    printf("cns6PTA::GetPeer\n");
#endif

    fPeer->AddRef();
    *result = fPeer;
    return NS_OK;
}

NS_METHOD
cns6PTA::Start(void)
{
#ifdef NS_DEBUG
    printf("cns6PTA::Start\n");
#endif

    return NS_OK;
}

NS_METHOD
cns6PTA::Stop(void)
{
#ifdef NS_DEBUG
    printf("cns6PTA::Stop\n");
#endif

    return NS_OK;
}

NS_METHOD
cns6PTA::Destroy(void)
{
#ifdef NS_DEBUG
    printf("cns6PTA::Destroy\n");
#endif

    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_SetWindow:
 * Sets the window in which a plug-in draws, and returns an error value. 
 * 
 * NPP_SetWindow informs the plug-in instance specified by instance of the
 * the window denoted by window in which the instance draws. This nsPluginWindow
 * pointer is valid for the life of the instance, or until NPP_SetWindow is called
 * again with a different value. Subsequent calls to NPP_SetWindow for a given
 * instance typically indicate that the window has been resized. If either window
 * or window->window are NULL, the plug-in must not perform any additional
 * graphics operations on the window and should free any resources associated
 * with the window. 
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

NS_METHOD
cns6PTA::SetWindow(nsPluginWindow* window)
{
#ifdef NS_DEBUG
    printf("cns6PTA::SetWindow\n");
#endif

    nsresult result;

    /*
     * PLUGIN DEVELOPERS:
     *	Before setting window to point to the
     *	new window, you may wish to compare the new window
     *	info to the previous window (if any) to note window
     *	size changes, etc.
     */
    result = PlatformSetWindow(window);
    fWindow = window;
    return result;
}

NS_METHOD
cns6PTA::NewStream(nsIPluginStreamListener** listener)
{
#ifdef NS_DEBUG
    printf("cns6PTA::NewStream\n");
#endif

    if(listener != NULL)
    {
        SimplePluginStreamListener* sl = 
                new SimplePluginStreamListener(this, "http://www.mozilla.org");
        if(!sl)
            return NS_ERROR_UNEXPECTED;
        sl->AddRef();
        *listener = sl;
    }
    
    return NS_OK;
}




/******************************************************************************
 * Native Method Implementations for CertPrefs interface 
 ******************************************************************************/

NS_IMETHODIMP	cns6PTA::Set_CertPref_CertSerNum(const PRUnichar *CertSerNum, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CertSerNum == NULL) 
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertSerNum(pCertPrefs, (wchar_t*)CertSerNum, wcslen(CertSerNum));
		
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_CertPref_CertSerNum(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = CertPrefs_get_CertSerNum(pCertPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_CertPref_CertIssDN(const PRUnichar *CertIssDN, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CertIssDN == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertIssDN(pCertPrefs, (wchar_t*)CertIssDN, wcslen(CertIssDN));
		
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_CertPref_CertIssDN(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = CertPrefs_get_CertIssDN(pCertPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName);
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_CertPref_CertFrndlyName(const PRUnichar *CertFrndlyName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CertFrndlyName == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertFrndlyName(pCertPrefs, (wchar_t*)CertFrndlyName, wcslen(CertFrndlyName));
		
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_CertPref_CertFrndlyName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = CertPrefs_get_CertFrndlyName(pCertPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_CertPref_CertLogoUrl(const PRUnichar *CertLogoUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CertLogoUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertLogoUrl(pCertPrefs, (wchar_t*)CertLogoUrl, wcslen(CertLogoUrl));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_CertPref_CertLogoUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = CertPrefs_get_CertLogoUrl(pCertPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_CertPref_CertDispString(const PRUnichar *CertDispString, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CertDispString == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertDispString(pCertPrefs, (wchar_t*)CertDispString, wcslen(CertDispString));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_CertPref_CertDispString(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = CertPrefs_get_CertDispString(pCertPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_CertPref_CertTextureUrl(const PRUnichar *CertTextureUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CertTextureUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertTextureUrl(pCertPrefs, (wchar_t*)CertTextureUrl, wcslen(CertTextureUrl));
		
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_CertPref_CertTextureUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = CertPrefs_get_CertTextureUrl(pCertPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_CertPref_MarkAsRenewed(PRBool boolMarkAsRenewed, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	*_retval = CertPrefs_set_MarkAsRenewed(pCertPrefs, (BOOL)boolMarkAsRenewed);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_CertPref_MarkAsRenewed(PRBool *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	BOOL boolRenewed;
	
	if((boolRenewed = CertPrefs_get_MarkAsRenewed(pCertPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = boolRenewed;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_CertPref_SetPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(PrefName == NULL || Value == NULL) 
	{ 
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = CertPrefs_set_CertPreference(pCertPrefs, (wchar_t*)PrefName, wcslen(PrefName), 
			(wchar_t*)Value, wcslen(Value));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_CertPref_GetPreference(const PRUnichar *PrefName, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(PrefName == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		if((pwstrName = CertPrefs_get_CertPreference(pCertPrefs, (wchar_t*)PrefName, wcslen(PrefName))) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;

}


/******************************************************************************
* PTA Interface methods
*******************************************************************************/
extern "C" BOOL NS_EXPORT DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	hInst = hInstance;
	return true;
}

BOOL CALLBACK DummyDialogProc(
  HWND hwndDlg,  // handle to dialog box
  UINT uMsg,     // message
  WPARAM wParam, // first message parameter
  LPARAM lParam  // second message parameter
  ) {
	
	switch (uMsg) {
	case WM_INITDIALOG :
		ShowWindow(hwndDlg,SW_HIDE);
		hwndDlgBox = hwndDlg;
		break;
	case WM_QUIT :
		EndDialog(hwndDlg,0);
		hwndDlgBox = NULL;
		break;
	}

	return 0;
}


NS_IMETHODIMP	cns6PTA::PTA_Initialize(const PRUnichar *AppCtxtName, PRInt32 UseCapi, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(!m_szHostName)
	{
		DialogBox(hInst,MAKEINTRESOURCE(IDD_DUMMY),GetFocus(),DummyDialogProc);
	}

	if(AppCtxtName == NULL )
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = ::PTA_Initialize (pPTA, (wchar_t*)AppCtxtName, wcslen(AppCtxtName), UseCapi);
	
		if(*_retval != VS_NO_ERROR) 
		{
//			_lastErrCode = *_retval;
		}
		else
		{
			*_retval = PTADllApi_SetHostName (pPTAApi, m_szHostName, m_szProtocol);
//     		if(*_retval != VS_NO_ERROR) 
//	     		_lastErrCode = *_retval;		
		}
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::PTA_Close(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	
	

	//Call our wrapper
	*_retval = ::PTA_Close (pPTA);
	
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_PTA_AppPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	

	if(PrefName == NULL || Value==NULL )
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_AppPreference (pPTA, (wchar_t*)PrefName, wcslen(PrefName), (wchar_t*)Value, wcslen(Value));
		
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_PTA_AppPreference(const PRUnichar *PrefName, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(PrefName == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		if((pwstrName = PTA_get_AppPreference (pPTA, (wchar_t*)PrefName, wcslen(PrefName))) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_PTA_CSPName(const PRUnichar *CSPName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CSPName == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_CSPName (pPTA, (wchar_t*)CSPName, wcslen(CSPName));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_PTA_CSPName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	{
		if((pwstrName = PTA_get_CSPName (pPTA)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::PTA_CreateCertReq(const PRUnichar *SubjectDN, PRInt32 KeyGenFlag, PRInt32 HashAlg, PRUint32 count, const PRUnichar **Attribs, PRUnichar **_retval)
{
	
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* stringChars;
	
	wchar_t* pwstrName;

	int *nLenArray;
	int noOfStrings, nIndex;
	const PRUnichar *tempString;

	if(SubjectDN == NULL || Attribs == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		nLenArray = (int*)malloc(count*sizeof(int));
		for (nIndex = 0; nIndex < count; ++nIndex)
		{
			nLenArray[nIndex] = wcslen(((wchar_t**)Attribs)[nIndex]);
		}

		//Call our wrapper
		pwstrName = ::PTA_CreateCertReq (pPTA, (wchar_t*)SubjectDN, wcslen(SubjectDN), 
				              KeyGenFlag, HashAlg, (wchar_t**)Attribs, nLenArray, count);
		if (pwstrName == NULL) {
			*_retval = NULL;
		} else {
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}

		// free dynamically allocated memories 
		//for (nIndx = 0; nIndx < noOfStrings; ++nIndx)
		//{
		//   if (attributes[nIndx] != NULL)
		//			SysFreeString((BSTR)attributes[nIndx]);
		//}
		if (nLenArray != NULL)
			 free (nLenArray);
	}
	
	return NS_OK;       
}



NS_IMETHODIMP	cns6PTA::PTA_InstallCert(const PRUnichar *Cert, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(Cert == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = ::PTA_InstallCert (pPTA, (wchar_t*)Cert, wcslen(Cert));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::PTA_InstallKeyPair(const PRUnichar *privKeyBlob, const PRUnichar *pkcs7Cert, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(privKeyBlob == NULL || pkcs7Cert==NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = ::PTA_InstallKeyPair (pPTA, (wchar_t*)privKeyBlob, wcslen(privKeyBlob), (wchar_t*)pkcs7Cert, wcslen(pkcs7Cert));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::PTA_SelectIDForTrans(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	
	

	//Call our wrapper
	*_retval = ::PTA_SelectIDForTrans (pPTA);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::PTA_SelectIDForChallenge(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	
	


	//Call our wrapper
	*_retval = ::PTA_SelectIDForChallenge (pPTA);
	

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::PTA_SignChallenge(const PRUnichar *Challenge, PRInt32 AlgID, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(Challenge == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		if((pwstrName = ::PTA_SignChallenge (pPTA, (wchar_t*)Challenge, wcslen(Challenge),AlgID)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::PTA_SignTransaction(const PRUnichar *Message, PRInt32 AlgID, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(Message == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		if((pwstrName = ::PTA_SignTransaction (pPTA, (wchar_t*)Message, wcslen(Message),AlgID)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::PTA_SignRenewal(PRInt32 AlgID, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = ::PTA_SignRenewal (pPTA, AlgID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_PTA_ProtocolName(const PRUnichar *protocolName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(protocolName == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_ProtocolName (pPTA, (wchar_t*)protocolName, wcslen(protocolName));
		
	}
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_PTA_ProtocolName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = PTA_get_ProtocolName (pPTA)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Get_PTA_UseDefCertFlag(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	*_retval = PTA_get_UserDefCertFlag (pPTA);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_PTA_UseDefCertFlag(PRInt16 defCertFlag, PRInt32 *_retval)
{	
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = PTA_set_UserDefCertFlag (pPTA, defCertFlag);
	

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Set_PTA_AuthDll(const PRUnichar *authDllName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(authDllName == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_AuthDll (pPTA, (wchar_t*)authDllName, wcslen(authDllName));
		
	}
	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Get_PTA_AuthDll(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = PTA_get_AuthDll (pPTA)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_PTA_ProfileIssFrndlyName(const PRUnichar *profileIssFrndlyName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(profileIssFrndlyName == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_ProfileIssFrndlyName (pPTA, (wchar_t*)profileIssFrndlyName, wcslen(profileIssFrndlyName));
		
	}
	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Get_PTA_ProfileIssFrndlyName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = PTA_get_ProfileIssFrndlyName (pPTA)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_PTA_ProfileIssUniqueId(const PRUnichar *profileIssUniqId, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(profileIssUniqId == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_ProfileIssUniqueId (pPTA, (wchar_t*)profileIssUniqId, wcslen(profileIssUniqId));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_PTA_ProfileIssUniqueId(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = PTA_get_ProfileIssUniqueId (pPTA)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_PTA_AffLogoUrl(const PRUnichar *affLogoUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
    _lastErrCode = NS_OK;

	if(affLogoUrl == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = PTA_set_AffLogoUrl (pPTA, (wchar_t*)affLogoUrl, wcslen(affLogoUrl));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_PTA_AffLogoUrl(PRUnichar **_retval)
{
    //unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = PTA_get_AffLogoUrl (pPTA)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;
}


NS_IMETHODIMP cns6PTA::Set_PTA_EnableCertForCapi(PRBool boolEnableForCapi, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	*_retval = PTA_set_EnableCertForCapi(pPTA, (BOOL)boolEnableForCapi);

	return NS_OK;
}

/******************************************************************************
* ProfMgmt Interface methods.
*******************************************************************************/


NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_PasswdQuality(PRInt32 PasswdQuality, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ProfMgmt_set_PasswdQuality(pProfMgmt, PasswdQuality);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_PasswdQuality(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int PasswordQuality;
	
	if((PasswordQuality = ProfMgmt_get_PasswdQuality (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = PasswordQuality;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_PasswdLength(PRInt32 PasswdLength, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ProfMgmt_set_PasswdLength(pProfMgmt, PasswdLength);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_PasswdLength(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int PasswordLength;
	
	if((PasswordLength = ProfMgmt_get_PasswdLength (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = PasswordLength;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_PasswdTimeOut(PRInt32 PasswdTimeOut, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = ProfMgmt_set_PasswdTimeOut(pProfMgmt, PasswdTimeOut);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_PasswdTimeOut(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int PasswdTimeOut;
	
	if((PasswdTimeOut = ProfMgmt_get_PasswdTimeOut (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = PasswdTimeOut;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_PasswdLockOutTries(PRInt32 PasswdLockOutTries, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ProfMgmt_set_PasswdLockOutTries(pProfMgmt, PasswdLockOutTries);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_PasswdLockOutTries(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int PasswdLockOutTries;
	
	if((PasswdLockOutTries = ProfMgmt_get_PasswdLockOutTries (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = PasswdLockOutTries;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_PasswdUnLockPeriod(PRInt32 PasswdUnLockPeriod, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = ProfMgmt_set_PasswdUnLockPeriod(pProfMgmt, PasswdUnLockPeriod);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_PasswdUnLockPeriod(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int PasswdUnLockPeriod;
	
	if((PasswdUnLockPeriod = ProfMgmt_get_PasswdUnLockPeriod (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = PasswdUnLockPeriod;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_ProfileName(const PRUnichar *ProfileName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(ProfileName == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = ProfMgmt_set_ProfileName (pProfMgmt, (wchar_t*)ProfileName, wcslen(ProfileName));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_ProfileName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = ProfMgmt_get_ProfileName (pProfMgmt)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName);
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_Password(const PRUnichar *Password, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(Password == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = ProfMgmt_set_Password (pProfMgmt, (wchar_t*)Password, wcslen(Password));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_SaveLocal(PRBool boolSaveLocal, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ProfMgmt_set_SaveLocal (pProfMgmt, boolSaveLocal);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_SaveLocal(PRBool *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	BOOL boolSaveLocal;
	
	if((boolSaveLocal = ProfMgmt_get_SaveLocal (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = boolSaveLocal;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_RoamProfile(PRBool boolRoamProfile, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = ProfMgmt_set_RoamProfile (pProfMgmt, boolRoamProfile);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_RoamProfile(PRBool *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	BOOL boolRoamProfile;
	
	if((boolRoamProfile = ProfMgmt_get_RoamProfile (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = boolRoamProfile;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_ProfMgmt_OpenProfFlags(PRInt32 flags, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ProfMgmt_set_OpenProfFlags(pProfMgmt, flags);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_ProfMgmt_OpenProfFlags(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int OpenProfFlags;

	if((OpenProfFlags = ProfMgmt_get_OpenProfFlags (pProfMgmt)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = OpenProfFlags;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::ProfMgmt_OpenProfile(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ::ProfMgmt_OpenProfile (pProfMgmt);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::ProfMgmt_CloseProfile(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ::ProfMgmt_CloseProfile (pProfMgmt);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::ProfMgmt_SaveProfile(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ::ProfMgmt_SaveProfile (pProfMgmt);
	

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::ProfMgmt_ChangePassword(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = ::ProfMgmt_ChangePassword (pProfMgmt);
	

	return NS_OK;
}


/******************************************************************************
* SrchCrit methods
*******************************************************************************/


NS_IMETHODIMP	cns6PTA::Set_SrchCrit_IssuerDN(const PRUnichar *IssuerDN, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(IssuerDN == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}

	//Call our wrapper
	*_retval = SrchCrit_set_IssuerDN(pSrchCrit, (wchar_t*)IssuerDN, wcslen(IssuerDN));
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SrchCrit_IssuerDN(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SrchCrit_get_IssuerDN(pSrchCrit)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_SubjectDN(const PRUnichar *SubjectDN, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(SubjectDN == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = SrchCrit_set_SubjectDN(pSrchCrit, (wchar_t*)SubjectDN, wcslen(SubjectDN));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SrchCrit_SubjectDN(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SrchCrit_get_SubjectDN(pSrchCrit)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_SerNum(const PRUnichar *SerNum, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(SerNum == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = SrchCrit_set_SerNum(pSrchCrit, (wchar_t*)SerNum, wcslen(SerNum));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SrchCrit_SerNum(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SrchCrit_get_SerNum(pSrchCrit)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_Email(const PRUnichar *Email, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(Email == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = SrchCrit_set_Email(pSrchCrit, (wchar_t*)Email, wcslen(Email));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SrchCrit_Email(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = SrchCrit_get_Email(pSrchCrit)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_ExpDate(PRUint64 ExpDate, PRInt32 *_retval)
{

	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	SYSTEMTIME sysTime;
	DATE dateExpDate;

	struct tm*	pstructTm;
	time_t	ExpTime;
	

	ExpTime = (time_t)(ExpDate/1000);
	pstructTm = gmtime(&ExpTime);

	sysTime.wDayOfWeek = pstructTm->tm_wday;
	sysTime.wMilliseconds = 0;
	sysTime.wHour = pstructTm->tm_hour;
	sysTime.wMinute = pstructTm->tm_min;
	sysTime.wSecond = pstructTm->tm_sec;
	sysTime.wYear = pstructTm->tm_year + 1900;
	sysTime.wMonth = pstructTm->tm_mon + 1;
	sysTime.wDay = pstructTm->tm_mday;

	SystemTimeToVariantTime(&sysTime, &dateExpDate);

	//Call our wrapper
	*_retval = SrchCrit_set_ExpDate(pSrchCrit, dateExpDate);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SrchCrit_ExpDate(PRUint64 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	DATE ExpDate;
	SYSTEMTIME sysTime;

	struct tm	structTm;
	time_t	ExpTime;
	
	if((ExpDate = SrchCrit_get_ExpDate(pSrchCrit)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		VariantTimeToSystemTime(ExpDate, &sysTime);

		structTm.tm_wday = sysTime.wDayOfWeek;
//		sysTime.wMilliseconds = 0;
		structTm.tm_hour = sysTime.wHour;
		structTm.tm_min = sysTime.wMinute;
		structTm.tm_sec = sysTime.wSecond;
		structTm.tm_year  = sysTime.wYear - 1900;
		structTm.tm_mon = sysTime.wMonth - 1;
		structTm.tm_mday = sysTime.wDay;

		ExpTime = mktime (&structTm);

		*_retval = ExpTime * 1000;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_EffDate(PRUint64 EffDate, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	SYSTEMTIME sysTime;
	DATE dateEffDate;
	
	struct tm*	pstructTm;
	time_t	EffTime;
	
	
	EffTime = (time_t)(EffDate/1000);
	pstructTm = gmtime(&EffTime);

	sysTime.wDayOfWeek = pstructTm->tm_wday;
	sysTime.wMilliseconds = 0;
	sysTime.wHour = pstructTm->tm_hour;
	sysTime.wMinute = pstructTm->tm_min;
	sysTime.wSecond = pstructTm->tm_sec;
	sysTime.wYear = pstructTm->tm_year + 1900;
	sysTime.wMonth = pstructTm->tm_mon + 1;
	sysTime.wDay = pstructTm->tm_mday;

	SystemTimeToVariantTime(&sysTime, &dateEffDate);
			
	//Call our wrapper
	*_retval = SrchCrit_set_EffDate(pSrchCrit, dateEffDate);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SrchCrit_EffDate(PRUint64 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	DATE EffDate;
	SYSTEMTIME sysTime;

	struct tm	structTm;
	time_t	EffTime;
	
	if((EffDate = SrchCrit_get_EffDate(pSrchCrit)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		VariantTimeToSystemTime(EffDate, &sysTime);

		structTm.tm_wday = sysTime.wDayOfWeek;
//		sysTime.wMilliseconds = 0;
		structTm.tm_hour = sysTime.wHour;
		structTm.tm_min = sysTime.wMinute;
		structTm.tm_sec = sysTime.wSecond;
		structTm.tm_year  = sysTime.wYear - 1900;
		structTm.tm_mon = sysTime.wMonth - 1;
		structTm.tm_mday = sysTime.wDay;

		EffTime = mktime (&structTm);

		*_retval = EffTime * 1000;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_DateEquality(PRInt16 DateEquality, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = SrchCrit_set_DateEquality(pSrchCrit, DateEquality);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SrchCrit_DateEquality(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	short wDateEq;

	if((wDateEq = SrchCrit_get_DateEquality(pSrchCrit)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = wDateEq;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_SrchCrit_Renewed(PRBool Renewed, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = SrchCrit_set_Renewed(pSrchCrit, Renewed);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SrchCrit_Renewed(PRBool *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	BOOL boolRenewed;
	
	if((boolRenewed = SrchCrit_get_Renewed(pSrchCrit)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = boolRenewed;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_KeyUsage(PRInt16 KeyUsage, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = SrchCrit_set_KeyUsage(pSrchCrit, KeyUsage);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SrchCrit_KeyUsage(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	short keyUsage;
	
	if((keyUsage = SrchCrit_get_KeyUsage(pSrchCrit)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = keyUsage;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_SrchCrit_KeySize(PRInt16 KeySize, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = SrchCrit_set_KeySize(pSrchCrit, KeySize);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SrchCrit_KeySize(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	short keySize;
	
	if((keySize = SrchCrit_get_KeySize(pSrchCrit)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = keySize;
	}

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Set_SrchCrit_ExtOID(const PRUnichar *ExtOID, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(ExtOID == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = SrchCrit_set_ExtOID(pSrchCrit, (wchar_t*)ExtOID, wcslen(ExtOID));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SrchCrit_ExtOID(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SrchCrit_get_ExtOID(pSrchCrit)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_SrchCrit_ExtVal(const PRUnichar *ExtVal, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(ExtVal == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = SrchCrit_set_ExtVal(pSrchCrit, (wchar_t*)ExtVal, wcslen(ExtVal));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SrchCrit_ExtVal(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = SrchCrit_get_ExtVal(pSrchCrit)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


/******************************************************************************
* SelectedDigID methods
*******************************************************************************/

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_IssuerDN(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SelectedDigID_get_IssuerDN(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_SubjectDN(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SelectedDigID_get_SubjectDN(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_SerNum(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SelectedDigID_get_SerNum(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_ExpDate(PRUint64 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	DATE ExpDate;
	SYSTEMTIME sysTime;

	struct tm	structTm;
	time_t	ExpTime;
	
	if((ExpDate = SelectedDigID_get_ExpDate(pSelectedDigID)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		VariantTimeToSystemTime(ExpDate, &sysTime);

		structTm.tm_wday = sysTime.wDayOfWeek;
//		sysTime.wMilliseconds = 0;
		structTm.tm_hour = sysTime.wHour;
		structTm.tm_min = sysTime.wMinute;
		structTm.tm_sec = sysTime.wSecond;
		structTm.tm_year  = sysTime.wYear - 1900;
		structTm.tm_mon = sysTime.wMonth - 1;
		structTm.tm_mday = sysTime.wDay;

		ExpTime = mktime (&structTm);

		*_retval = ExpTime * 1000;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_EffDate(PRUint64 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	DATE EffDate;
	SYSTEMTIME sysTime;

	struct tm	structTm;
	time_t	EffTime;

	if((EffDate = SelectedDigID_get_EffDate(pSelectedDigID)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		VariantTimeToSystemTime(EffDate, &sysTime);

		structTm.tm_wday = sysTime.wDayOfWeek;
//		sysTime.wMilliseconds = 0;
		structTm.tm_hour = sysTime.wHour;
		structTm.tm_min = sysTime.wMinute;
		structTm.tm_sec = sysTime.wSecond;
		structTm.tm_year  = sysTime.wYear - 1900;
		structTm.tm_mon = sysTime.wMonth - 1;
		structTm.tm_mday = sysTime.wDay;

		EffTime = mktime (&structTm);

		*_retval = EffTime * 1000;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_KeyUsage(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	short keyUsage;
	
	if((keyUsage = SelectedDigID_get_KeyUsage(pSelectedDigID)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = keyUsage;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_KeySize(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	short keySize;
	
	if((keySize = SelectedDigID_get_KeySize(pSelectedDigID)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = keySize;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_Renewed(PRBool *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	BOOL boolRenewed;
	
	if((boolRenewed = SelectedDigID_get_Renewed(pSelectedDigID)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = boolRenewed;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_PubKeyMD5(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SelectedDigID_get_PubKeyMD5(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_PubKeySHA1(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = SelectedDigID_get_PubKeySHA1(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_FrndlyName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SelectedDigID_get_FrndlyName(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_LogoUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = SelectedDigID_get_LogoUrl(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Get_SelectedDigID_TextureUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = SelectedDigID_get_TextureUrl(pSelectedDigID)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;
}


/******************************************************************************
* RoamPrefs interface methods
*******************************************************************************/


NS_IMETHODIMP	cns6PTA::Set_RoamPrefs_NumOfSrvrs(PRInt16 NumOfSrvrs, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = RoamPrefs_set_NumOfSrvrs(pRoamPrefs, NumOfSrvrs);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_RoamPrefs_NumOfSrvrs(PRInt16 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	short NumOfSrvrs;
	
	if((NumOfSrvrs = RoamPrefs_get_NumOfSrvrs(pRoamPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = NumOfSrvrs;
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_RoamPrefs_StorageSrvr(const PRUnichar *StorageSrvr, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(StorageSrvr == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = RoamPrefs_set_StorageSrvr(pRoamPrefs, (wchar_t*)StorageSrvr, wcslen(StorageSrvr));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_RoamPrefs_StorageSrvr(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = RoamPrefs_get_StorageSrvr(pRoamPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

/*
NS_IMETHODIMP	cns6PTA::Set_RoamPrefs_RoamingSrvrs(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	wchar_t** stringChars;
	int *nLenArray;
	int noOfStrings, nIndx;
	
	
	
	const PRUnichar *tempString;

	if(a == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Get the current instance
		instance = (NPP)netscape_plugin_Plugin_getPeer(env, (netscape_plugin_Plugin*)self);
		if(instance == NULL)
		{
			retVal = VS_PLUGIN_NOINST;
			_lastErrCode = *_retval;
		}
		else
		{
			This = (PluginInstance*)instance->pdata;


			noOfStrings = JRI_GetObjectArrayLength(env, a);
			// allocate the array stringChars 
			stringChars = (wchar_t**)malloc(noOfStrings * sizeof (wchar_t*));
			nLenArray = (int *)malloc(noOfStrings * sizeof(int));

			//extract the strings
			for (nIndx = 0; nIndx < noOfStrings; ++nIndx)
			{
				tempString = JRI_GetObjectArrayElement (env, a, nIndx);
			    stringChars[nIndx] = (wchar_t*)JRI_GetStringChars(env,tempString);
				nLenArray[nIndx] = JRI_GetStringLength(env,tempString);
			}

			//Call our wrapper
			*_retval = RoamPrefs_set_RoamingServers (pRoamPrefs, stringChars, nLenArray, noOfStrings);

			if (stringChars != NULL)
			    free (stringChars);
			if (nLenArray != NULL)
			    free (nLenArray);
		
			if(*_retval != VS_NO_ERROR)
				retVal = *_retval;
		}
	}

	return NS_OK;
}
*/

/*
NS_IMETHODIMP	cns6PTA::Get_RoamPrefs_RoamingSrvrs(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;


    int noOfElements;
    wchar_t** roamArray;
	struct java_lang_Object* retVal = NULL;
	const PRUnichar* tempString;
	
	
	int nIndx;

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

			if((roamArray = RoamPrefs_get_RoamingSrvrs(pRoamPrefs, &noOfElements)) == NULL)
			{
				retVal = NULL;
			}
			else
			{
				 retVal = JRI_NewObjectArray(env, noOfElements, ((struct java_lang_Class*)JRI_FindClass(env, "java/lang/String")), NULL);
			    //extract the strings
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

	return NS_OK;
}
*/


NS_IMETHODIMP	cns6PTA::Set_RoamPrefs_ClientInfo(const PRUnichar *ClientInfo, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(ClientInfo == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = RoamPrefs_set_ClientInfo(pRoamPrefs, (wchar_t*)ClientInfo, wcslen(ClientInfo));
		
	}
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_RoamPrefs_ClientInfo(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = RoamPrefs_get_ClientInfo(pRoamPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_RoamPrefs_ClientInfoSig(const PRUnichar *ClientInfoSig, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(ClientInfoSig == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = RoamPrefs_set_ClientInfoSig(pRoamPrefs, (wchar_t*)ClientInfoSig, wcslen(ClientInfoSig));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_RoamPrefs_ClientInfoSig(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = RoamPrefs_get_ClientInfoSig (pRoamPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


/******************************************************************************
* UIPrefs interface methods
*******************************************************************************/


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_UILogoUrl(const PRUnichar *UILogoUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(UILogoUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_UILogoUrl (pUIPrefs, (wchar_t*)UILogoUrl, wcslen(UILogoUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_UILogoUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_UILogoUrl(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_NewPasswd_Title(const PRUnichar *NewPasswd_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(NewPasswd_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_NewPasswd_Title (pUIPrefs, (wchar_t*)NewPasswd_Title, wcslen(NewPasswd_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_NewPasswd_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_NewPasswd_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_NewPasswd_Text(const PRUnichar *NewPasswd_Text, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(NewPasswd_Text == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_NewPasswd_Text (pUIPrefs, (wchar_t*)NewPasswd_Text, wcslen(NewPasswd_Text));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_NewPasswd_Text(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_NewPasswd_Text(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_NewPasswd_OKBtnText(PRInt32 NewPasswd_OKBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_NewPasswd_OKBtnText (pUIPrefs, NewPasswd_OKBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_NewPasswd_OKBtnText(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int OKBtnText;
	
	if ((OKBtnText = UIPrefs_get_NewPasswd_OKBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = OKBtnText;
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_NewPasswd_CancelBtnText(PRInt32 NewPasswd_CancelBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = UIPrefs_set_NewPasswd_CancelBtnText (pUIPrefs, NewPasswd_CancelBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_NewPasswd_CancelBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if((nText = UIPrefs_get_NewPasswd_CancelBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_NewPasswd_HelpUrl(const PRUnichar *NewPasswd_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(NewPasswd_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_NewPasswd_HelpUrl (pUIPrefs, (wchar_t*)NewPasswd_HelpUrl, wcslen(NewPasswd_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_NewPasswd_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_NewPasswd_HelpUrl(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_RvwMsg_Text(const PRUnichar *RvwMsg_Text, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(RvwMsg_Text == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_RvwMsg_Text (pUIPrefs, (wchar_t*)RvwMsg_Text, wcslen(RvwMsg_Text));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_RvwMsg_Text(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_RvwMsg_Text(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_RvwMsg_OKBtnText(PRInt32 RvwMsg_OKBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = UIPrefs_set_RvwMsg_OKBtnText (pUIPrefs, RvwMsg_OKBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_RvwMsg_OKBtnText(PRInt32 *_retval)
{
	int retVal = -1;
	int nText;
	
	if(( nText = UIPrefs_get_RvwMsg_OKBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_RvwMsg_Title(const PRUnichar *RvwMsg_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(RvwMsg_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_RvwMsg_Title (pUIPrefs, (wchar_t*)RvwMsg_Title, wcslen(RvwMsg_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_RvwMsg_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_RvwMsg_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_RvwMsg_CancelBtnText(PRInt32 RvwMsg_CancelBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = UIPrefs_set_RvwMsg_CancelBtnText (pUIPrefs, RvwMsg_CancelBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_RvwMsg_CancelBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if((nText = UIPrefs_get_RvwMsg_CancelBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_RvwMsg_HelpUrl(const PRUnichar *RvwMsg_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(RvwMsg_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_RvwMsg_HelpUrl (pUIPrefs, (wchar_t*)RvwMsg_HelpUrl, wcslen(RvwMsg_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_RvwMsg_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_RvwMsg_HelpUrl(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_Title(const PRUnichar *SelID_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(SelID_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_SelID_Title (pUIPrefs, (wchar_t*)SelID_Title, wcslen(SelID_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_SelID_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_Text(const PRUnichar *SelID_Text, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(SelID_Text == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_SelID_Text (pUIPrefs, (wchar_t*)SelID_Text, wcslen(SelID_Text));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_Text(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_SelID_Text(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_OKBtnText(PRInt32 SelID_OKBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_SelID_OKBtnText (pUIPrefs, SelID_OKBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_OKBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if(( nText= UIPrefs_get_SelID_OKBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_CancelBtnText(PRInt32 SelID_CancelBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

		//Call our wrapper
	*_retval = UIPrefs_set_SelID_CancelBtnText (pUIPrefs, SelID_CancelBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_CancelBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if((nText = UIPrefs_get_SelID_CancelBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_ShowDefChkBox(PRBool SelID_ShowDefChkBox, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_SelID_ShowDefChkBox(pUIPrefs, SelID_ShowDefChkBox);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_ShowDefChkBox(PRBool *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	BOOL boolShowDef;
	
	if((boolShowDef = UIPrefs_get_SelID_ShowDefChkBox(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = boolShowDef;
	}

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_ChkBoxText(const PRUnichar *SelID_ChkBoxText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(SelID_ChkBoxText == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_SelID_ChkBoxText (pUIPrefs, (wchar_t*)SelID_ChkBoxText, wcslen(SelID_ChkBoxText));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_ChkBoxText(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_SelID_ChkBoxText(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SelID_HelpUrl(const PRUnichar *SelID_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(SelID_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_SelID_HelpUrl (pUIPrefs, (wchar_t*)SelID_HelpUrl, wcslen(SelID_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SelID_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_SelID_HelpUrl(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_SgnDlg_Title(const PRUnichar *SgnDlg_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(SgnDlg_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_SgnDlg_Title (pUIPrefs, (wchar_t*)SgnDlg_Title, wcslen(SgnDlg_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_SgnDlg_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_SgnDlg_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_LgnDlg_Title(const PRUnichar *LgnDlg_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(LgnDlg_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_LgnDlg_Title (pUIPrefs, (wchar_t*)LgnDlg_Title, wcslen(LgnDlg_Title));
		
	}

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Get_UIPrefs_LgnDlg_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_LgnDlg_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_OpenProf_Title(const PRUnichar *OpenProf_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(OpenProf_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_OpenProf_Title (pUIPrefs, (wchar_t*)OpenProf_Title, wcslen(OpenProf_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_OpenProf_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_OpenProf_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_OpenProf_Text(const PRUnichar *OpenProf_Text, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(OpenProf_Text == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_OpenProf_Text (pUIPrefs, (wchar_t*)OpenProf_Text, wcslen(OpenProf_Text));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_UIPrefs_OpenProf_Text(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_OpenProf_Text (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_OpenProf_OKBtnText(PRInt32 OpenProf_OKBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_OpenProf_OKBtnText (pUIPrefs, OpenProf_OKBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_OpenProf_OKBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if((nText = UIPrefs_get_OpenProf_OKBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_OpenProf_CancelBtnText(PRInt32 OpenProf_CancelBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_OpenProf_CancelBtnText (pUIPrefs, OpenProf_CancelBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_OpenProf_CancelBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if((nText = UIPrefs_get_OpenProf_CancelBtnText (pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_OpenProf_HelpUrl(const PRUnichar *OpenProf_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(OpenProf_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_OpenProf_HelpUrl (pUIPrefs, (wchar_t*)OpenProf_HelpUrl, wcslen(OpenProf_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_OpenProf_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_OpenProf_HelpUrl (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_TitleFont(const PRUnichar *TitleFont, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(TitleFont == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_TitleFont (pUIPrefs, (wchar_t*)TitleFont, wcslen(TitleFont));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_TitleFont(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_TitleFont (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_TextFont(const PRUnichar *TextFont, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(TextFont == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_TextFont (pUIPrefs, (wchar_t*)TextFont, wcslen(TextFont));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_TextFont(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_TextFont (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_BtnFont(const PRUnichar *BtnFont, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(BtnFont == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_BtnFont (pUIPrefs, (wchar_t*)BtnFont, wcslen(BtnFont));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_BtnFont(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_BtnFont (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_Language(PRInt32 Language, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_Language(pUIPrefs, Language);
	

	return NS_OK;
}



NS_IMETHODIMP	cns6PTA::Get_UIPrefs_Language(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	int Language;
	
	if((Language = UIPrefs_get_Language(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = Language;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_IntroDlg_Title(const PRUnichar *IntroDlg_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(IntroDlg_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_IntroDlg_Title (pUIPrefs, (wchar_t*)IntroDlg_Title, wcslen(IntroDlg_Title));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_UIPrefs_IntroDlg_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_IntroDlg_Title (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_IntroDlg_Text(const PRUnichar *IntroDlg_Text, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(IntroDlg_Text == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_IntroDlg_Text (pUIPrefs, (wchar_t*)IntroDlg_Text, wcslen(IntroDlg_Text));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_IntroDlg_Text(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_IntroDlg_Text (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_IntroDlg_HelpUrl(const PRUnichar *IntroDlg_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(IntroDlg_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_IntroDlg_HelpUrl (pUIPrefs, (wchar_t*)IntroDlg_HelpUrl, wcslen(IntroDlg_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_IntroDlg_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if((pwstrName = UIPrefs_get_IntroDlg_HelpUrl (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_CreateNewProf_Title(const PRUnichar *CreateNewProf_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(CreateNewProf_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_CreateNewProf_Title (pUIPrefs, (wchar_t*)CreateNewProf_Title, wcslen(CreateNewProf_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_CreateNewProf_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_CreateNewProf_Title (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}



NS_IMETHODIMP	cns6PTA::Set_UIPrefs_ChangePasswd_Title(const PRUnichar *ChangePasswd_Title, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	if(ChangePasswd_Title == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_ChangePasswd_Title (pUIPrefs, (wchar_t*)ChangePasswd_Title, wcslen(ChangePasswd_Title));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_ChangePasswd_Title(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_ChangePasswd_Title(pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_ChangePasswd_Text(const PRUnichar *ChangePasswd_Text, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(ChangePasswd_Text == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_ChangePasswd_Text (pUIPrefs, (wchar_t*)ChangePasswd_Text, wcslen(ChangePasswd_Text));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_UIPrefs_ChangePasswd_Text(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_ChangePasswd_Text (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_ChangePasswd_OKBtnText(PRInt32 ChangePasswd_OKBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_ChangePasswd_OKBtnText (pUIPrefs, ChangePasswd_OKBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_ChangePasswd_OKBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;

	if((nText = UIPrefs_get_ChangePasswd_OKBtnText(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 ChangePasswd_CancelBtnText, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = UIPrefs_set_ChangePasswd_CancelBtnText (pUIPrefs, ChangePasswd_CancelBtnText);
	

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nText;
	
	if((nText = UIPrefs_get_ChangePasswd_CancelBtnText (pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nText;
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_ChangePasswd_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(ChangePasswd_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_ChangePasswd_HelpUrl (pUIPrefs, (wchar_t*)ChangePasswd_HelpUrl, wcslen(ChangePasswd_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_ChangePasswd_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_ChangePasswd_HelpUrl (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::Set_UIPrefs_Timeout_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(ChangePasswd_HelpUrl == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = UIPrefs_set_Timeout_HelpUrl (pUIPrefs, (wchar_t*)ChangePasswd_HelpUrl, wcslen(ChangePasswd_HelpUrl));
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_UIPrefs_Timeout_HelpUrl(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if((pwstrName = UIPrefs_get_Timeout_HelpUrl (pUIPrefs)) == NULL)
	{
		*_retval = NULL;
	}
	else
	{
		ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
		SysFreeString((BSTR)pwstrName);
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_UIPrefs_EnableTopMostWindow(PRBool boolEnableTopMost, PRInt32 *_retval)
{
    _lastErrCode = NS_OK;

	*_retval = UIPrefs_set_EnableTopMost(pUIPrefs, (BOOL)boolEnableTopMost);
	

	return NS_OK;
}


NS_IMETHODIMP cns6PTA::Set_UIPrefs_SignTransDlgWidth(PRInt32 nWidth, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_SignTransDlgWidth(pUIPrefs, nWidth);
	
	return NS_OK;
}

NS_IMETHODIMP cns6PTA::Get_UIPrefs_SignTransDlgWidth(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nWidth;

	if((nWidth = UIPrefs_get_SignTransDlgWidth(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nWidth;
	}

	return NS_OK;
}
 
NS_IMETHODIMP cns6PTA::Set_UIPrefs_SignTransDlgHeight(PRInt32 nHeight, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = UIPrefs_set_SignTransDlgHeight(pUIPrefs, nHeight);
	
	return NS_OK;
}
 
NS_IMETHODIMP cns6PTA::Get_UIPrefs_SignTransDlgHeight(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nHeight;

	if((nHeight = UIPrefs_get_SignTransDlgHeight(pUIPrefs)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nHeight;
	}

	return NS_OK;
}


/******************************************************************************
* Xenroll methods
*******************************************************************************/

NS_IMETHODIMP	cns6PTA::Set_XEnroll_ProviderType(PRInt32 nProviderType, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_set_ProviderType(pEnroll, nProviderType);
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_XEnroll_ProviderType(PRInt32 *_retval)
{
	PRInt32 retVal;
	DWORD dwProviderType;
	
	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	{
		if((dwProviderType = Enroll_get_ProviderType(pEnroll)) == -1)
		{
			*_retval = -1;
		}
		else
		{
			*_retval = dwProviderType;
		}
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_XEnroll_GenKeyFlags(PRInt32 nGenKeyFlags, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_set_GenKeyFlags(pEnroll, nGenKeyFlags);
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Get_XEnroll_GenKeyFlags(PRInt32 *_retval)
{
	PRInt32 retVal;
	DWORD dwGenKeyFlags;
	
	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	{

		if((dwGenKeyFlags = Enroll_get_GenKeyFlags(pEnroll)) == -1)
		{
			*_retval = -1;
		}
		else
		{	
			*_retval = dwGenKeyFlags;
		}
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::Set_XEnroll_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_set_ProviderName(pEnroll, (wchar_t*)szProviderName, wcslen(szProviderName));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_XEnroll_ProviderName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrProviderName;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = NULL;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		if((pwstrProviderName = Enroll_get_ProviderName(pEnroll)) == NULL)
		{
				*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrProviderName)
			SysFreeString((BSTR)pwstrProviderName);
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_XEnroll_HashAlgorithm(const PRUnichar *szHashAlgo, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_set_HashAlgorithm(pEnroll, (wchar_t*)szHashAlgo, wcslen(szHashAlgo));
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_XEnroll_HashAlgorithm(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrHashAlogrithm;
	
	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = NULL;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		if((pwstrHashAlogrithm = Enroll_get_HashAlgorithm(pEnroll)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrHashAlogrithm)
			SysFreeString((BSTR)pwstrHashAlogrithm);
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_XEnroll_KeySpec(PRInt32 nKeySpec, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_set_KeySpec(pEnroll, nKeySpec);
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_XEnroll_KeySpec(PRInt32 *_retval)
{
	PRInt32 retVal = 0;
	DWORD dwKeySpec;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		if((dwKeySpec = Enroll_get_KeySpec(pEnroll)) == -1)
		{
			*_retval = -1;
		}
		else
		{
			*_retval = dwKeySpec;
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_XEnroll_DeleteRequestCert(PRBool boolFlag, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
//		boolDeleteRequest = a;
		
		//Call our wrapper
		*_retval = Enroll_set_DeleteRequestCert(pEnroll, boolFlag);
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_XEnroll_DeleteRequestCert(PRBool *_retval)
{
	PRBool retVal = FALSE;
	BOOL boolDeleteRequest;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = FALSE;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		boolDeleteRequest = Enroll_get_KeySpec(pEnroll);			
		*_retval = boolDeleteRequest;
	}
			
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_XEnroll_WriteCertToCSP(PRBool boolFlag, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_set_WriteCertToCSP(pEnroll, boolFlag);
		
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_XEnroll_WriteCertToCSP(PRBool *_retval)
{
	PRBool retVal = FALSE;
	BOOL boolWriteCertToCSP;
	
	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = FALSE;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		boolWriteCertToCSP = Enroll_get_WriteCertToCSP(pEnroll);
	
		*_retval = boolWriteCertToCSP;
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::XEnroll_enumProviders(const PRInt32 nIndex, const PRInt32 nFlags, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrProvider;
	
	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = NULL;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		//Call our wrapper
		if((pwstrProvider = Enroll_enumProvider(pEnroll, nIndex, nFlags)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrProvider)
			SysFreeString((BSTR)pwstrProvider);
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::XEnroll_createPKCS10(const PRUnichar *szDNName, const PRUnichar *szUsage, PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t *pwstrPKCS10;
	
	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = NULL;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		//Call our wrapper
		pwstrPKCS10= Enroll_createPKCS10(pEnroll, (wchar_t*)szDNName, wcslen(szDNName), (wchar_t*)szUsage, wcslen(szUsage));
		if (pwstrPKCS10 == NULL)
		{					 
			*_retval = NULL;
		}
		else
		{
			 ALLOC_AND_WSTRING_COPY(*_retval, pwstrPKCS10)
			SysFreeString((BSTR)pwstrPKCS10);
		}	
	}		

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::XEnroll_acceptPKCS7(const PRUnichar *szPKCS7, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolXenrollInitialized == FALSE)
	{
	   *_retval = VS_XENROLL_NOT_LOADED;
       _lastErrCode = VS_XENROLL_NOT_LOADED;
	} 
	else
	{
		//Call our wrapper
		*_retval = Enroll_acceptPKCS7(pEnroll, (wchar_t*)szPKCS7, wcslen(szPKCS7));
		
	}

	return NS_OK;
}

/******************************************************
    Error related functions 
	***************************************************/
NS_IMETHODIMP	cns6PTA::GetLastError(PRUint32 *_retval)
{
//	unsigned int errCode;
//	errCode = _lastErrCode;
	*_retval = _lastErrCode;
	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::VSImport_Import(const PRUnichar *PKCS12, const PRUnichar *PKCS7, PRUnichar **szErrCodeString, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrErrString = NULL;
	
	if (boolImportInitialized == FALSE)
	{
	   *_retval = VS_IMPORT_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	if(!pImport)
	{
		*_retval = VS_NOT_IMPL;
		_lastErrCode = *_retval;
	}		
	else
	{
		//Call our wrapper
		*_retval = Import_Import(pImport, (wchar_t*)PKCS12, wcslen(PKCS12), (wchar_t*)PKCS7, wcslen(PKCS7), &pwstrErrString);

		if(*_retval != VS_NO_ERROR)
		{
			ALLOC_AND_WSTRING_COPY((*szErrCodeString), pwstrErrString)
		}
	}

	return NS_OK;

}

NS_IMETHODIMP	cns6PTA::VSImport_set_KeyExportable(const PRInt32 nFlag, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if (boolImportInitialized == FALSE)
	{
	   *_retval = VS_IMPORT_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	if(!pImport)
	{
		*_retval = VS_NOT_IMPL;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = Import_set_KeyExportable(pImport, nFlag);
		
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::VSImport_get_KeyExportable(PRInt32 *_retval)
{
	PRInt32 retVal = 0;
	long lKeyExp;
	
	if (boolImportInitialized == FALSE)
	{
	   *_retval = VS_IMPORT_NOT_LOADED;
       _lastErrCode = *_retval;
	} 
	else
	if(!pImport)
	{
		*_retval = VS_NOT_IMPL;
		_lastErrCode = *_retval;
	}
	else
	{
		if((lKeyExp = Import_get_KeyExportable(pImport)) == -1)
		{
			*_retval = -1;
		}
		else
		{
			*_retval = lKeyExp;
		}
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::VSImport_set_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(szProviderName == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		if (boolImportInitialized == FALSE)
		{
		   *_retval = NULL;
		   _lastErrCode = VS_IMPORT_NOT_LOADED;
		} 
		{
			//Call our wrapper
			*_retval = Import_set_ProviderName(pImport, (wchar_t*)szProviderName, wcslen(szProviderName));
			
		}
	}

	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::VSImport_get_ProviderName(PRUnichar **_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;
	
	if (boolImportInitialized == FALSE)
	{
	   *_retval = NULL;
       _lastErrCode = VS_IMPORT_NOT_LOADED;
	} 
	else
	{
		if((pwstrName = Import_get_ProviderName(pImport)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::AddRootCerts_Initialize(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	

	*_retval = 0;
	
	if (boolAddRootsInitialized == FALSE)
	{
	   *_retval = VS_ADDROOTS_NOT_LOADED;
       _lastErrCode = VS_ADDROOTS_NOT_LOADED;
	} 
	else
	{
	//Intialize
		*_retval = AddRoots_Initialize(pAddRoots);
		
	}
	
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::AddRootCerts_CreateStandardTrustProfile(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	*_retval = 0;
	
	if (boolAddRootsInitialized == FALSE)
	{
	   *_retval = VS_ADDROOTS_NOT_LOADED;
       _lastErrCode = VS_ADDROOTS_NOT_LOADED;
	} 
	else
	{
		//Intialize
		*_retval = AddRoots_CreateStandardTrustProfile(pAddRoots);
		
	}
	
	return NS_OK;
}

NS_IMETHODIMP	cns6PTA::AddRootCerts_CreateVerisignTrustProfile(PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	*_retval = 0;
	
	if (boolAddRootsInitialized == FALSE)
	{
	   *_retval = VS_ADDROOTS_NOT_LOADED;
       _lastErrCode = VS_ADDROOTS_NOT_LOADED;
	} 
	else
	{
		//Intialize
		*_retval = AddRoots_CreateVerisignTrustProfile(pAddRoots);
		
	}
	
	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::P12Import_ImportP12(PRInt32 nType, const PRUnichar *strP12, PRUnichar **strSerialNum, PRUnichar **strIssuerDN, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

//	wchar_t* stringChars;
	wchar_t* pwstrSerNum;
	wchar_t* pwstrIssDN;
//	int nParamType;

	if(strP12 == NULL || strSerialNum == NULL )//|| strIssuerDN == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
			//Call our wrapper
		*_retval = ::P12Import_ImportP12(pP12Import, nType, (wchar_t*) strP12, wcslen(strP12), &pwstrSerNum, &pwstrIssDN);

		if(*_retval == VS_NO_ERROR)
		{
			ALLOC_AND_WSTRING_COPY((*strSerialNum), pwstrSerNum);
			ALLOC_AND_WSTRING_COPY((*strIssuerDN), pwstrIssDN);

			SysFreeString((BSTR)pwstrSerNum);
			SysFreeString((BSTR)pwstrIssDN);

		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::P12Export_ExportP12(PRInt32 nOutputType, PRInt32 nFlags, const PRUnichar *strFile, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;

	if(strFile == NULL)//|| strIssuerDN == NULL) 
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
			//Call our wrapper
		*_retval = ::P12Export_ExportP12(pP12Export, nOutputType, nFlags, (wchar_t*) strFile, wcslen(strFile));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_P12Export_PasswdQuality(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nPasswordQuality;
	
	if((nPasswordQuality = P12Export_get_PasswdQuality(pP12Export)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nPasswordQuality;
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_P12Export_PasswdQuality(PRInt32 newVal, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = P12Export_set_PasswdQuality(pP12Export, newVal);
	

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_P12Export_PasswdLength(PRInt32 *_retval)
{
	int retVal = VS_NO_ERROR;
	int nPasswordLength;
	
	if((nPasswordLength = P12Export_get_PasswdLength(pP12Export)) == -1)
	{
		*_retval = -1;
	}
	else
	{
		*_retval = nPasswordLength;
	}

	return NS_OK;

}


NS_IMETHODIMP	cns6PTA::Set_P12Export_PasswdLength(PRInt32 newVal, PRInt32 *_retval)
{
	//unsigned int retVal = VS_NO_ERROR;
	_lastErrCode = NS_OK;
	
	//Call our wrapper
	*_retval = P12Export_set_PasswdLength(pP12Export, newVal);
	

	return NS_OK;
}


// Digital Notarization methods

NS_IMETHODIMP	cns6PTA::NZ_Initialize(PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = ::NZ_Initialize(pVSNZ);

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::NZ_Close(PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = ::NZ_Close(pVSNZ);

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_NotarizationServer(const PRUnichar *ServerName, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ServerName == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_NotarizationServer(pVSNZ, (wchar_t*)ServerName, wcslen(ServerName));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_HashAlg(const PRUnichar *HashAlg, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(HashAlg == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_HashAlg(pVSNZ, (wchar_t*)HashAlg, wcslen(HashAlg));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_DisplayDigitalID(PRInt32 DisplayID, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = NZ_set_DisplayDigitalID(pVSNZ, DisplayID);

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_CrlLocation(const PRUnichar *CrlLocation, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(CrlLocation == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_CRLLocation(pVSNZ, (wchar_t*)CrlLocation, wcslen(CrlLocation));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_ValidationPreference(PRInt32 ValPref, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	//Call our wrapper
	*_retval = NZ_set_ValidationPref(pVSNZ, ValPref);

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_NotarizationDescription(const PRUnichar *Description, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(Description == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_NotarizationDescription(pVSNZ, (wchar_t*)Description, wcslen(Description));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::NZ_NotarizeDocument(const PRUnichar *DocumentName, PRInt32 UIMask, PRInt32 ResponseType, PRUnichar **_retval)
{
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(DocumentName == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		// Get the user agent string
		nsresult rv;
		nsIPluginManager* pm = NULL;

		rv = nsServiceManager::GetService(kPluginManagerCID, NS_GET_IID(nsIPluginManager),
										  NS_REINTERPRET_CAST(nsISupports**, &pm));
		if(NS_SUCCEEDED(rv))
		{
			rv = pm->UserAgent((const char**)&szUAgent);

			NS_RELEASE(pm);
		}

		if((pwstrName = ::NZ_NotarizeDocument(pVSNZ, (wchar_t*)DocumentName, wcslen(DocumentName), UIMask, ResponseType)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::NZ_NotarizeHash(const PRUnichar *Hash, PRInt32 UIMask, PRUnichar **_retval)
{
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(Hash == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		if((pwstrName = ::NZ_NotarizeHash(pVSNZ, (wchar_t*)Hash, wcslen(Hash), UIMask)) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::NZ_VerifyNotarizationRecord(const PRUnichar *Record, const PRUnichar *Description, PRInt32 RecordType, PRInt32 UIMask, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(Record == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		// Get the user agent string
		nsresult rv;
		nsIPluginManager* pm = NULL;

		rv = nsServiceManager::GetService(kPluginManagerCID, NS_GET_IID(nsIPluginManager),
										  NS_REINTERPRET_CAST(nsISupports**, &pm));
		if(NS_SUCCEEDED(rv))
		{
			rv = pm->UserAgent((const char**)&szUAgent);

			NS_RELEASE(pm);
		}

		//Call our wrapper
		if(Description == NULL)
			*_retval = ::NZ_VerifyNotarizationRecord(pVSNZ, (wchar_t*)Record, wcslen(Record), NULL, 0, RecordType, UIMask);
		else
			*_retval = ::NZ_VerifyNotarizationRecord(pVSNZ, (wchar_t*)Record, wcslen(Record), (wchar_t*)Description, wcslen(Description), RecordType, UIMask);
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::NZ_AddCertificate(const PRUnichar *Certificate, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(Certificate == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = ::NZ_AddCertificate(pVSNZ, (wchar_t*)Certificate, wcslen(Certificate));
	}

	return NS_OK;
}


/**** User Preferences methods of Digital Notarization ****/

NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_LogoUrl(const PRUnichar *LogoUrl, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(LogoUrl == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_LogoUrl(pNZUIPrefs, (wchar_t*)LogoUrl, wcslen(LogoUrl));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_SelFileTitle(const PRUnichar *SelFileTitle, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(SelFileTitle == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_SelFileTitle(pNZUIPrefs, (wchar_t*)SelFileTitle, wcslen(SelFileTitle));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_SelFileDescription(const PRUnichar *SelFileDesc, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(SelFileDesc == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_SelFileDesc(pNZUIPrefs, (wchar_t*)SelFileDesc, wcslen(SelFileDesc));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_SelFileHelpUrl(const PRUnichar *SelFileHelpUrl, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(SelFileHelpUrl == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_SelFileHelpUrl(pNZUIPrefs, (wchar_t*)SelFileHelpUrl, wcslen(SelFileHelpUrl));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_ProgressTitle(const PRUnichar *ProgressTitle, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ProgressTitle == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_ProgressTitle(pNZUIPrefs, (wchar_t*)ProgressTitle, wcslen(ProgressTitle));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_ProgressDescription(const PRUnichar *ProgressDesc, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ProgressDesc == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_ProgressDesc(pNZUIPrefs, (wchar_t*)ProgressDesc, wcslen(ProgressDesc));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_ProgressHelpUrl(const PRUnichar *ProgressHelpUrl, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ProgressHelpUrl == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_ProgressHelpUrl(pNZUIPrefs, (wchar_t*)ProgressHelpUrl, wcslen(ProgressHelpUrl));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_ReceiptTitle(const PRUnichar *ReceiptTitle, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ReceiptTitle == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_ReceiptTitle(pNZUIPrefs, (wchar_t*)ReceiptTitle, wcslen(ReceiptTitle));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_ReceiptDescription(const PRUnichar *ReceiptDesc, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ReceiptDesc == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_ReceiptDesc(pNZUIPrefs, (wchar_t*)ReceiptDesc, wcslen(ReceiptDesc));
	}

	return NS_OK;
}


NS_IMETHODIMP cns6PTA::Set_NZ_UIPrefs_ReceiptHelpUrl(const PRUnichar *ReceiptHelpUrl, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ReceiptHelpUrl == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_ReceiptHelpUrl(pNZUIPrefs, (wchar_t*)ReceiptHelpUrl, wcslen(ReceiptHelpUrl));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Set_NZ_UIPrefs_WizardTitle(const PRUnichar *WizardTitle, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(WizardTitle == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_UIPrefs_WizardTitle(pNZUIPrefs, (wchar_t*)WizardTitle, wcslen(WizardTitle));
	}

	return NS_OK;
}


/**** Application Preferences methods of Digital Notarization ****/

NS_IMETHODIMP	cns6PTA::Set_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRInt32 PreferenceType, const PRUnichar *PreferenceValue, PRInt32 *_retval)
{
	_lastErrCode = NS_OK;

	if(ApplicationName == NULL || PreferenceName == NULL || PreferenceValue == NULL)
	{
		*_retval = VS_INVALID_ARG;
		_lastErrCode = *_retval;
	}
	else
	{
		//Call our wrapper
		*_retval = NZ_set_ApplicationPref(pNZAppPrefs, (wchar_t*)ApplicationName, wcslen(ApplicationName),
						(wchar_t*)PreferenceName, wcslen(PreferenceName), PreferenceType, 
						(wchar_t*)PreferenceValue, wcslen(PreferenceValue));
	}

	return NS_OK;
}


NS_IMETHODIMP	cns6PTA::Get_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRUnichar **_retval)
{
	_lastErrCode = NS_OK;
	wchar_t* pwstrName;

	if(ApplicationName == NULL || PreferenceName == NULL)
	{
		_lastErrCode = VS_INVALID_ARG;
	}
	else
	{
		if((pwstrName = NZ_get_ApplicationPref(pNZAppPrefs, (wchar_t*)ApplicationName, wcslen(ApplicationName), 
							(wchar_t*)PreferenceName, wcslen(PreferenceName))) == NULL)
		{
			*_retval = NULL;
		}
		else
		{
			ALLOC_AND_WSTRING_COPY(*_retval, pwstrName)
			SysFreeString((BSTR)pwstrName);
		}
	}

	return NS_OK;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * NPP_Print:
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

NS_METHOD
cns6PTA::Print(nsPluginPrint* printInfo)
{
#ifdef NS_DEBUG
    printf("cns6PTA::Print\n");
#endif

    if (printInfo == NULL)
        return NS_ERROR_FAILURE;

    if (printInfo->mode == nsPluginMode_Full) {
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

        /* Do the default*/
        printInfo->print.fullPrint.pluginPrinted = PR_FALSE;
    }
    else {	/* If not fullscreen, we must be embedded */
        /*
         * PLUGIN DEVELOPERS:
         *	If your plugin is embedded, or is full-screen
         *	but you returned false in pluginPrinted above, NPP_Print
         *	will be called with mode == nsPluginMode_Embedded.  The nsPluginWindow
         *	in the printInfo gives the location and dimensions of
         *	the embedded plugin on the printed page.  On the
         *	Macintosh, platformPrint is the printer port; on
         *	Windows, platformPrint is the handle to the printing
         *	device context.
         */
    }
    return NS_OK;
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

NS_METHOD
cns6PTA::HandleEvent(nsPluginEvent* event, PRBool* handled)
{
#ifdef NS_DEBUG
    printf("cns6PTA::HandleEvent\n");
#endif

    *handled = (PRBool)PlatformHandleEvent(event);
    return NS_OK;
}

NS_METHOD
cns6PTA::GetValue(nsPluginInstanceVariable variable, void *value)
{
#ifdef NS_DEBUG
    printf("cns6PTA::GetValue\n");
#endif

    return NS_ERROR_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////
// SimplePluginStreamListener Methods
////////////////////////////////////////////////////////////////////////////////

SimplePluginStreamListener::SimplePluginStreamListener(cns6PTA* inst,
                                                       const char* msgName)
    : fMessageName(msgName)
{
    NS_INIT_REFCNT();
	pcsn6PTAInst = inst;
    char msg[256];
    sprintf(msg, "### Creating SimplePluginStreamListener for %s\n", fMessageName);
}

SimplePluginStreamListener::~SimplePluginStreamListener(void)
{
    char msg[256];
    sprintf(msg, "### Destroying SimplePluginStreamListener for %s\n", fMessageName);
}

// This macro produces a simple version of QueryInterface, AddRef and Release.
// See the nsISupports.h header file for details.

NS_IMPL_ISUPPORTS1(SimplePluginStreamListener, nsIPluginStreamListener);

NS_METHOD
SimplePluginStreamListener::OnStartBinding(nsIPluginStreamInfo* pluginInfo)
{
#ifdef NS_DEBUG
    printf("SimplePluginStreamListener::OnStartBinding\n");
#endif

	PRInt32	dwResult = 0;

	char *pcURL;
	dwResult =	pluginInfo->GetURL ((const char**) &pcURL);
//	::MessageBox(NULL, pcURL, "Plugin", MB_OK);

	if (NS_OK == dwResult)
	{
		dwResult =	pcsn6PTAInst->SetPageURL ((const char*) pcURL);
	}

    char msg[256];
    sprintf(msg, "### Opening plugin stream for %s\n", fMessageName);
    return NS_OK;
}

NS_METHOD
SimplePluginStreamListener::OnDataAvailable(nsIPluginStreamInfo* pluginInfo, 
                                            nsIInputStream* input, 
                                            PRUint32 length)
{
#ifdef NS_DEBUG
    printf("SimplePluginStreamListener::OnDataAvailable\n");
#endif

    char* buffer = new char[length];
    if (buffer) {
        PRUint32 amountRead = 0;
        nsresult rslt = input->Read(buffer, length, &amountRead);
        if (rslt == NS_OK) {
            char msg[256];
            sprintf(msg, "### Received %d bytes for %s\n", length, fMessageName);
        }
        delete buffer;
    }
    return NS_OK;
}

NS_METHOD
SimplePluginStreamListener::OnFileAvailable(nsIPluginStreamInfo* pluginInfo, 
                                            const char* fileName)
{
#ifdef NS_DEBUG
    printf("SimplePluginStreamListener::OnFileAvailable\n");
#endif

    char msg[256];
    sprintf(msg, "### File available for %s: %s\n", fMessageName, fileName);
    return NS_OK;
}

NS_METHOD
SimplePluginStreamListener::OnStopBinding(nsIPluginStreamInfo* pluginInfo, nsresult status )
{
#ifdef NS_DEBUG
    printf("SimplePluginStreamListener::OnStopBinding\n");
#endif

    char msg[256];
    sprintf(msg, "### Closing plugin stream for %s\n", fMessageName);
    return NS_OK;
}

NS_METHOD
SimplePluginStreamListener::OnNotify(const char* url, nsresult status)
{
#ifdef NS_DEBUG
    printf("SimplePluginStreamListener::OnNotify\n");
#endif

    return NS_OK;
}

NS_METHOD
SimplePluginStreamListener::GetStreamType(nsPluginStreamType *result)
{
#ifdef NS_DEBUG
    printf("SimplePluginStreamListener::GetStreamType\n");
#endif

    *result = nsPluginStreamType_Normal;
    return NS_OK;
}

/*******************************************************************************
 * SECTION 4 - Utility Method Implementations
 *******************************************************************************/

/*------------------------------------------------------------------------------
 * Platform-Specific Implemenations
 *------------------------------------------------------------------------------
 * UNIX Implementations
 *----------------------------------------------------------------------------*/

#if defined(XP_UNIX)

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

void
cns6PTA::PlatformNew(void)
{
    fPlatform.window = 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

nsresult
cns6PTA::PlatformDestroy(void)
{
    gtk_widget_destroy(fPlatform.moz_box);
    fPlatform.moz_box = 0;
    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

nsresult
cns6PTA::PlatformSetWindow(nsPluginWindow* window)
{
#ifdef NS_DEBUG
    printf("cns6PTA::PlatformSetWindow\n");
#endif

    if (window == NULL || window->window == NULL)
        return NS_ERROR_NULL_POINTER;
    if ( fPlatform.superwin == (GdkSuperWin *)window->window )
        return NS_OK;
    
    fPlatform.superwin = (GdkSuperWin *)window->window;

    // a little cleanup
    if (fPlatform.label)
        gtk_widget_destroy(fPlatform.label);
    if (fPlatform.moz_box)
        gtk_widget_destroy(fPlatform.moz_box);

    // create a containing mozbox and a label to put in it
    fPlatform.moz_box = gtk_mozbox_new(fPlatform.superwin->bin_window);
    fPlatform.label = gtk_label_new(fText);
    gtk_container_add(GTK_CONTAINER(fPlatform.moz_box), fPlatform.label);

    // grow the label to fit the entire mozbox
    gtk_widget_set_usize(fPlatform.label, window->width, window->height);

    // connect to expose events
    gtk_signal_connect (GTK_OBJECT(fPlatform.label), "expose_event",
                        GTK_SIGNAL_FUNC(draw), this);

    gtk_widget_show(fPlatform.label);
    gtk_widget_show(fPlatform.moz_box);

    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

int16
cns6PTA::PlatformHandleEvent(nsPluginEvent* event)
{
    /* UNIX Plugins do not use HandleEvent */
    return 0;
}

NS_IMETHODIMP
cns6PTA::Repaint(void)
{
#ifdef DEBUG
    printf("cns6PTA::Repaint()\n");
#endif
    
    if ( !fPlatform.moz_box || !fPlatform.label )
        return NS_ERROR_FAILURE;

    // Set the label text
    gtk_label_set_text(GTK_LABEL(fPlatform.label), fText);

    // show the new label
    gtk_widget_show(fPlatform.label);
    gtk_widget_show(fPlatform.moz_box);

    return NS_OK;
}

gboolean draw (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    cns6PTA * pthis = (cns6PTA *)data;

    pthis->Repaint();
    return TRUE;
}

/*------------------------------------------------------------------------------
 * Windows Implementations
 *----------------------------------------------------------------------------*/

#elif defined(XP_PC) && !defined(XP_OS2)
const char* gInstanceLookupString = "instance->pdata";

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

void
cns6PTA::PlatformNew(void)
{
    fPlatform.fhWnd = NULL;
    fPlatform.fDefaultWindowProc = NULL;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

nsresult
cns6PTA::PlatformDestroy(void)
{
    if( fWindow != NULL ) { /* If we have a window, clean
                                   * it up. */
        SetWindowLong( fPlatform.fhWnd, GWL_WNDPROC, (LONG)fPlatform.fDefaultWindowProc);
        fPlatform.fDefaultWindowProc = NULL;
        fPlatform.fhWnd = NULL;
    }

    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

nsresult
cns6PTA::PlatformSetWindow(nsPluginWindow* window)
{
    if( fWindow != NULL ) /* If we already have a window, clean
                           * it up before trying to subclass
                           * the new window. */
    {
        if( (window == NULL) || ( window->window == NULL ) ) {
            /* There is now no window to use. get rid of the old
             * one and exit. */
            SetWindowLong( fPlatform.fhWnd, GWL_WNDPROC, (LONG)fPlatform.fDefaultWindowProc);
            fPlatform.fDefaultWindowProc = NULL;
            fPlatform.fhWnd = NULL;
            return NS_OK;
        }

        else if ( fPlatform.fhWnd == (HWND) window->window ) {
            /* The new window is the same as the old one. Exit now. */
            return NS_OK;
        }
        else {
            /* Clean up the old window, so that we can subclass the new
             * one later. */
            SetWindowLong( fPlatform.fhWnd, GWL_WNDPROC, (LONG)fPlatform.fDefaultWindowProc);
            fPlatform.fDefaultWindowProc = NULL;
            fPlatform.fhWnd = NULL;
        }
    }
    else if( (window == NULL) || ( window->window == NULL ) ) {
        /* We can just get out of here if there is no current
         * window and there is no new window to use. */
        return NS_OK;
    }

    /* At this point, we will subclass
     * window->window so that we can begin drawing and
     * receiving window messages. */
    fPlatform.fDefaultWindowProc =
        (WNDPROC)SetWindowLong( (HWND)window->window,
                                GWL_WNDPROC, (LONG)cns6PTA::PluginWindowProc);
    fPlatform.fhWnd = (HWND) window->window;
    SetProp(fPlatform.fhWnd, gInstanceLookupString, (HANDLE)this);

    InvalidateRect( fPlatform.fhWnd, NULL, TRUE );
    UpdateWindow( fPlatform.fhWnd );
    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

PRInt16
cns6PTA::PlatformHandleEvent(nsPluginEvent* event)
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

LRESULT CALLBACK 
cns6PTA::PluginWindowProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    cns6PTA* inst = (cns6PTA*) GetProp(hWnd, gInstanceLookupString);

    switch( Msg ) {
		/*
      case WM_PAINT: {
		  
          PAINTSTRUCT paintStruct;
          HDC hdc;

          hdc = BeginPaint( hWnd, &paintStruct );

          if(paintStruct.fErase)
            FillRect(hdc, &paintStruct.rcPaint, 
                     (HBRUSH) GetStockObject(WHITE_BRUSH)); 
          
          if(inst->fText)
            TextOut(hdc, 0, 0, inst->fText, strlen(inst->fText));

          EndPaint( hWnd, &paintStruct );
          break;
		  
      }
	  */
      default: {
          inst->fPlatform.fDefaultWindowProc(hWnd, Msg, wParam, lParam);
      }
    }
    return 0;
}



/*------------------------------------------------------------------------------
 * Macintosh Implementations
 *----------------------------------------------------------------------------*/

#elif defined(XP_MAC)

PRBool	StartDraw(nsPluginWindow* window);
void 	EndDraw(nsPluginWindow* window);
void 	DoDraw(cns6PTA* This);

CGrafPort 		gSavePort;
CGrafPtr		gOldPort;

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformNew
 *
 * Initialize any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

void
cns6PTA::PlatformNew(void)
{
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformDestroy
 *
 * Destroy any Platform-Specific instance data.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

nsresult
cns6PTA::PlatformDestroy(void)
{
    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformSetWindow
 *
 * Perform platform-specific window operations
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

nsresult
cns6PTA::PlatformSetWindow(nsPluginWindow* window)
{
    fWindow = window;
    if( StartDraw( window ) ) {
        DoDraw(This);
        EndDraw( window );
    }
    return NS_OK;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++
 * PlatformHandleEvent
 *
 * Handle platform-specific events.
 +++++++++++++++++++++++++++++++++++++++++++++++++*/

int16
cns6PTA::PlatformHandleEvent(nsPluginEvent* event)
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
            if( StartDraw( fWindow ) ) {
                DoDraw(This);
                EndDraw( fWindow );
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

PRBool
cns6PTA::StartDraw(nsPluginWindow* window)
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
cns6PTA::EndDraw(nsPluginWindow* window)
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
cns6PTA::DoDraw(void)
{
    Rect drawRect;
    drawRect.top = 0;
    drawRect.left = 0;
    drawRect.bottom = drawRect.top + fWindow->height;
    drawRect.right = drawRect.left + fWindow->width;
    EraseRect( &drawRect );
    MoveTo( 2, 12 );
    DrawString("\pHello, World!");
}



/*------------------------------------------------------------------------------
 * Stub Implementations
 *----------------------------------------------------------------------------*/

#else

void
cns6PTA::PlatformNew(void)
{
}

nsresult
cns6PTA::PlatformDestroy(void)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

nsresult
cns6PTA::PlatformSetWindow(nsPluginWindow* window)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

int16
cns6PTA::PlatformHandleEvent(nsPluginEvent* event)
{
    int16 eventHandled = FALSE;
    return eventHandled;
}

#endif /* end Section 5 */

/******************************************************************************/

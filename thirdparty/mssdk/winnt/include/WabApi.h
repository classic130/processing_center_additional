#ifndef _WABAPI_H_
#define _WABAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN16
#ifdef GetLastError
#undef GetLastError
#endif // GetLastError
#endif // WIN16

typedef struct _WABACTIONITEM * LPWABACTIONITEM;

/* IWABObject Interface ---------------------------------------------------- */

#define CBIWABOBJECT sizeof(IWABOBJECT)


#define WAB_IWABOBJECT_METHODS(IPURE)                       \
        MAPIMETHOD(GetLastError)                            \
            (THIS_  HRESULT hResult,                        \
                    ULONG   ulFlags,                        \
                    LPMAPIERROR FAR * lppMAPIError) IPURE;  \
        MAPIMETHOD(AllocateBuffer)                          \
            (THIS_  ULONG   cbSize,                         \
                    LPVOID FAR *    lppBuffer) IPURE;       \
        MAPIMETHOD(AllocateMore)                            \
            (THIS_  ULONG   cbSize,                         \
                    LPVOID  lpObject,                       \
                    LPVOID  FAR *   lppBuffer) IPURE;       \
        MAPIMETHOD(FreeBuffer)                              \
            (THIS_  LPVOID  lpBuffer) IPURE;                \
        MAPIMETHOD(Backup)                                  \
            (THIS_  LPTSTR  lpFileName) IPURE;              \
        MAPIMETHOD(Import)                                  \
            (THIS_   LPTSTR lpImportParam) IPURE;           \
        MAPIMETHOD(Find)                                    \
            (THIS_  LPADRBOOK lpIAB,                        \
                    HWND    hWnd) IPURE;                    \
        MAPIMETHOD(VCardDisplay)                            \
            (THIS_  LPADRBOOK lpIAB,                        \
                    HWND    hWnd,                           \
                    LPTSTR  lpszFileName) IPURE;            \
        MAPIMETHOD(LDAPUrl)                                 \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    HWND        hWnd,                       \
                    ULONG       ulFlags,                    \
                    LPTSTR      lpszURL,                    \
                    LPMAILUSER *lppMailUser) IPURE;         \
        MAPIMETHOD(VCardCreate)                             \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    LPTSTR      lpszVCard,                  \
                    LPMAILUSER  lpMailUser) IPURE;          \
        MAPIMETHOD(VCardRetrieve)                           \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    LPTSTR      lpszVCard,                  \
                    LPMAILUSER *lppMailUser) IPURE;         \
        MAPIMETHOD(GetMe)                                   \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    DWORD *     lpdwAction,                 \
                    SBinary *   lpsbEID,                    \
                    ULONG       ulParam) IPURE;          \
        MAPIMETHOD(SetMe)                                   \
            (THIS_  LPADRBOOK   lpIAB,                      \
                    ULONG       ulFlags,                    \
                    SBinary     sbEID,                      \
                    ULONG       ulParam) IPURE;          \



#undef           INTERFACE
#define          INTERFACE      IWABObject
DECLARE_MAPI_INTERFACE_(IWABObject, IUnknown)
{
        BEGIN_INTERFACE
        MAPI_IUNKNOWN_METHODS(PURE)
        WAB_IWABOBJECT_METHODS(PURE)
};

DECLARE_MAPI_INTERFACE_PTR(IWABObject, LPWABOBJECT);


#undef  INTERFACE
#define INTERFACE       struct _IWABOBJECT

#undef  METHOD_PREFIX
#define METHOD_PREFIX   IWABOBJECT_

#undef  LPVTBL_ELEM
#define LPVTBL_ELEM             lpvtbl

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)       MAPIMETHOD_DECLARE(type, method, IWABOBJECT_)
                MAPI_IUNKNOWN_METHODS(IMPL)
       WAB_IWABOBJECT_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)       MAPIMETHOD_TYPEDEF(type, method, IWABOBJECT_)
                MAPI_IUNKNOWN_METHODS(IMPL)
       WAB_IWABOBJECT_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)       STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IWABOBJECT_)
{
        BEGIN_INTERFACE
        MAPI_IUNKNOWN_METHODS(IMPL)
   WAB_IWABOBJECT_METHODS(IMPL)
};


// WABObject_LDAPUrl flag
// If this flag is specified and the LDAPUrl returns a single
// query result, instructs the WAB to return the result in the
// form of a MailUser object instead of displaying Details on it
// If there are multiple results to the query, fail ..
#define WABOBJECT_LDAPURL_RETURN_MAILUSER   0x00000001


// WABObject_GetMe returned parameter
// If the GetMe call results in the creation of a new 'Me' contact,
// the lpdwAction returned parameter will contain this value
// indicating to the caller that the object is freshly created and
// does not have any properties in it
#define WABOBJECT_ME_NEW                    0x00000001

// WABObject_GetMe flags
// WABObject_GetMe will create a new ME object by default, if 
// none already exists. To force the call to not-create an object, if
// one doesn't already exist, specify the WABOBJECT_ME_NOCREATE flag.
// If no me is found, the call fails with MAPI_E_NOT_FOUND.
// Other flag for WABObject_GetMe is AB_NO_DIALOG defined in wabdefs.h
#define WABOBJECT_ME_NOCREATE               0x00000002

// IWABObject_VCard Create/Retrieve
// Flags the WAB whether the lpszVCard parameter is a filename or if
// it is a NULL terminated string containing the compelte VCard contents
//
#define WAB_VCARD_FILE                      0x00000000
#define WAB_VCARD_STREAM                    0x00000001

#ifdef WIN16
BOOL WINAPI WABInitThread();
#endif


//
// Input information to pass to WABOpen
//
typedef struct _tagWAB_PARAM
{
    ULONG   cbSize;         // sizeof(WAB_PARAM).
    HWND    hwnd;           // hWnd of calling client Application. Can be NULL
    LPTSTR  szFileName;     // WAB File name to open. if NULL, opens default.
    ULONG   ulFlags;        // 
    LPTSTR  lpszProfileID;  // NULL terminated string containing a profile ID to use
    LPTSTR  lpszProfileName;// NULL terminated string containing a profile name
} WAB_PARAM, * LPWAB_PARAM;

//flags for WAB_PARAM
#define WAB_ENABLE_PROFILES     0x00400000

//
// Root public entry points for WAB API
//
STDMETHODIMP WABOpen(LPADRBOOK FAR * lppAdrBook, LPWABOBJECT FAR * lppWABObject,
  LPWAB_PARAM lpWP, DWORD Reserved2);

typedef HRESULT (STDMETHODCALLTYPE WABOPEN)(
    LPADRBOOK FAR * lppAdrBook,
    LPWABOBJECT FAR * lppWABObject,
    LPWAB_PARAM lpWP,
    DWORD Reserved2
);
typedef WABOPEN FAR * LPWABOPEN;


STDMETHODIMP WABOpenEx(LPADRBOOK FAR * lppAdrBook,
  LPWABOBJECT FAR * lppWABObject,
  LPWAB_PARAM lpWP,
  DWORD Reserved,
  ALLOCATEBUFFER * fnAllocateBuffer,
  ALLOCATEMORE * fnAllocateMore,
  FREEBUFFER * fnFreeBuffer);

typedef HRESULT (STDMETHODCALLTYPE WABOPENEX)(
    LPADRBOOK FAR * lppAdrBook,
    LPWABOBJECT FAR * lppWABObject,
    LPWAB_PARAM lpWP,
    DWORD Reserved,
    ALLOCATEBUFFER * fnAllocateBuffer,
    ALLOCATEMORE * fnAllocateMore,
    FREEBUFFER * fnFreeBuffer
);
typedef WABOPENEX FAR * LPWABOPENEX;

/* --------------------- */
typedef struct _WABIMPORTPARAM
{
    ULONG cbSize;       // sizeof(WABIMPORTPARAM)
    LPADRBOOK lpAdrBook;// ptr to the IAdrBook object (required)
    HWND hWnd;          // Parent HWND for any dialogs
    ULONG ulFlags;      // 0 or MAPI_DIALOG to show progress dialog and messages
    LPTSTR lpszFileName;// FileName to import or NULL .. if NULL will show FileOpen dialog 
} WABIMPORTPARAM, FAR * LPWABIMPORTPARAM;

/* --------------------- */
/* Structure used in extending the WAB Details Property Dialogs 
    and for doing WAB Context Menu verb extensions.
   The structure is passed into the IWABExtInit::Initialize method
    of the implementor */

// Flags
#define WAB_DISPLAY_LDAPURL 0x00000001  // The object being displayed is an LDAP URL
                                        // The URL can be found in the lpsz struct member
#define WAB_CONTEXT_ADRLIST 0x00000002  // THe lpv parameter contains a pointer to an
                                        // AdrList structure corresponding to selected items
                                        // on which to display a context menu
#define WAB_DISPLAY_ISNTDS  0x00000004  // Identifies that the entry being displayed originated
                                        // on the NT Directory Service, for clients that use ADSI and
                                        // retrieve additional information from the service.

// Struct
typedef struct _WABEXTDISPLAY
{
    ULONG cbSize;
    LPWABOBJECT lpWABObject;    // pointer to IWABObject
    LPADRBOOK lpAdrBook;        // pointer to IAdrBook object
    LPMAPIPROP lpPropObj;       // Object being displayed
    BOOL fReadOnly;             // Indicates if this is a ReadOnly mode
    BOOL fDataChanged;          // Set by extension sheet to signal data change
    ULONG ulFlags;              // See above
    LPVOID lpv;                 // Used for passing in specific data
    LPTSTR lpsz;                // Used for passing in specific data
} WABEXTDISPLAY, FAR * LPWABEXTDISPLAY;

/* --------------------- */

#define WAB_IWABEXTINIT_METHODS(IPURE)                          \
        MAPIMETHOD(Initialize)                                  \
            (THIS_  LPWABEXTDISPLAY lpWABExtDisplay)    IPURE;  \

#undef           INTERFACE
#define          INTERFACE      IWABExtInit
DECLARE_MAPI_INTERFACE_(IWABExtInit, IUnknown)
{
        BEGIN_INTERFACE
        MAPI_IUNKNOWN_METHODS(PURE)
        WAB_IWABEXTINIT_METHODS(PURE)
};

DECLARE_MAPI_INTERFACE_PTR(IWABExtInit, LPWABEXTINIT);

DEFINE_GUID(IID_IWABExtInit, 
0xea22ebf0, 0x87a4, 0x11d1, 0x9a, 0xcf, 0x0, 0xa0, 0xc9, 0x1f, 0x9c, 0x8b);


/* --------------------- */

#ifndef WIN16
#define WAB_DLL_NAME "WAB32.DLL"
#else
#define WAB_DLL_NAME "WAB16.DLL"
#endif

#define WAB_DLL_PATH_KEY TEXT("Software\\Microsoft\\WAB\\DLLPath")

#ifdef __cplusplus
}
#endif

#endif /* _WABAPI_H */

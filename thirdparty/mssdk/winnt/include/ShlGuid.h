//===========================================================================
//
// Copyright (c) Microsoft Corporation 1995-1998
//
// File: shlguid.h
//
//===========================================================================

#ifndef _SHLGUID_H_
#define _SHLGUID_H_

#ifndef _WIN32_IE
#define _WIN32_IE 0x0500
#else
#if (_WIN32_IE < 0x0400) && defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0500)
#error _WIN32_IE setting conflicts with _WIN32_WINNT setting
#endif
#endif

//
// For shell-reserved GUID
//
//  The Win95 Shell has been allocated a block of 256 GUIDs,
// which follow the general format:
//
//  000214xx-0000-0000-C000-000000000046
//
//
#define DEFINE_SHLGUID(name, l, w1, w2) DEFINE_GUID(name, l, w1, w2, 0xC0,0,0,0,0,0,0,0x46)


//
// Class IDs        xx=00-8F
//
DEFINE_SHLGUID(CLSID_ShellDesktop,      0x00021400L, 0, 0);
DEFINE_SHLGUID(CLSID_ShellLink,         0x00021401L, 0, 0);


#if (_WIN32_IE >= 0x0400)
//
// CatInformation IDs   xx=90-9F
//
DEFINE_SHLGUID(CATID_BrowsableShellExt, 0x00021490L, 0, 0);
DEFINE_SHLGUID(CATID_BrowseInPlace,     0x00021491L, 0, 0);
DEFINE_SHLGUID(CATID_DeskBand,          0x00021492L, 0, 0);
DEFINE_SHLGUID(CATID_InfoBand,          0x00021493L, 0, 0);
DEFINE_SHLGUID(CATID_CommBand,          0x00021494L, 0, 0);
#endif

// Format IDs       xx=A0-CF
DEFINE_SHLGUID(FMTID_Intshcut,          0x000214A0L, 0, 0);
DEFINE_SHLGUID(FMTID_InternetSite,      0x000214A1L, 0, 0);

// command group ids xx=D0-DF
DEFINE_SHLGUID(CGID_Explorer,           0x000214D0L, 0, 0);
DEFINE_SHLGUID(CGID_ShellDocView,       0x000214D1L, 0, 0);

#if (_WIN32_IE >= 0x0400)
DEFINE_SHLGUID(CGID_ShellServiceObject, 0x000214D2L, 0, 0);
DEFINE_SHLGUID(CGID_ExplorerBarDoc,     0x000214D3L, 0, 0);
#endif



//
// Interface IDs    xx=E0-FF
//
DEFINE_SHLGUID(IID_INewShortcutHookA,   0x000214E1L, 0, 0);
DEFINE_SHLGUID(IID_IShellBrowser,       0x000214E2L, 0, 0);
DEFINE_SHLGUID(IID_IShellView,          0x000214E3L, 0, 0);
DEFINE_SHLGUID(IID_IContextMenu,        0x000214E4L, 0, 0);
DEFINE_SHLGUID(IID_IShellIcon,          0x000214E5L, 0, 0);
DEFINE_SHLGUID(IID_IShellFolder,        0x000214E6L, 0, 0);
DEFINE_SHLGUID(IID_IShellExtInit,       0x000214E8L, 0, 0);
DEFINE_SHLGUID(IID_IShellPropSheetExt,  0x000214E9L, 0, 0);
DEFINE_SHLGUID(IID_IPersistFolder,      0x000214EAL, 0, 0);
DEFINE_SHLGUID(IID_IExtractIconA,       0x000214EBL, 0, 0);
DEFINE_SHLGUID(IID_IShellDetails,       0x000214ECL, 0, 0);
DEFINE_SHLGUID(IID_IDelayedRelease,     0x000214EDL, 0, 0);
DEFINE_SHLGUID(IID_IShellLinkA,         0x000214EEL, 0, 0);
DEFINE_SHLGUID(IID_IShellCopyHookA,     0x000214EFL, 0, 0);
DEFINE_SHLGUID(IID_IFileViewerA,        0x000214F0L, 0, 0);
DEFINE_SHLGUID(IID_ICommDlgBrowser,     0x000214F1L, 0, 0);
DEFINE_SHLGUID(IID_IEnumIDList,         0x000214F2L, 0, 0);
DEFINE_SHLGUID(IID_IFileViewerSite,     0x000214F3L, 0, 0);
DEFINE_SHLGUID(IID_IContextMenu2,       0x000214F4L, 0, 0);
DEFINE_SHLGUID(IID_IShellExecuteHookA,  0x000214F5L, 0, 0);
DEFINE_SHLGUID(IID_IPropSheetPage,      0x000214F6L, 0, 0);
DEFINE_SHLGUID(IID_INewShortcutHookW,   0x000214F7L, 0, 0);
DEFINE_SHLGUID(IID_IFileViewerW,        0x000214F8L, 0, 0);
DEFINE_SHLGUID(IID_IShellLinkW,         0x000214F9L, 0, 0);
DEFINE_SHLGUID(IID_IExtractIconW,       0x000214FAL, 0, 0);
DEFINE_SHLGUID(IID_IShellExecuteHookW,  0x000214FBL, 0, 0);
DEFINE_SHLGUID(IID_IShellCopyHookW,     0x000214FCL, 0, 0);

DEFINE_SHLGUID(IID_IRemoteComputer,     0x000214FEL, 0, 0);

#if (_WIN32_IE >= 0x0400)
DEFINE_SHLGUID(IID_IQueryInfo,          0x00021500L, 0, 0);
#endif

DEFINE_GUID(IID_IBriefcaseStg,          0x8BCE1FA1L, 0x0921, 0x101B, 0xB1, 0xFF, 0x00, 0xDD, 0x01, 0x0C, 0xCC, 0x48);
DEFINE_GUID(IID_IShellView2,            0x88E39E80L, 0x3578, 0x11CF, 0xAE, 0x69, 0x08, 0x00, 0x2B, 0x2E, 0x12, 0x62);

#if (_WIN32_IE >= 0x0400)
DEFINE_GUID(IID_IURLSearchHook,         0xAC60F6A0L, 0x0FD9, 0x11D0, 0x99, 0xCB, 0x00, 0xC0, 0x4F, 0xD6, 0x44, 0x97);
DEFINE_GUID(IID_IDelegateFolder,        0xADD8BA80L, 0x002B, 0x11D0, 0x8F, 0x0F, 0x00, 0xC0, 0x4F, 0xD7, 0xD0, 0x62);

#if (_WIN32_IE >= 0x0500)
// CLSID_DelegateShellFolder {4CD2D514-B890-11d1-8E73-00C04FA31A86}
DEFINE_GUID(CLSID_DelegateShellFolder, 0x4cd2d514, 0xb890, 0x11d1, 0x8e, 0x73, 0x0, 0xc0, 0x4f, 0xa3, 0x1a, 0x86);
DEFINE_GUID(IID_IDelegateShellFolder, 0x4cd2d515, 0xb890, 0x11d1, 0x8e, 0x73, 0x0, 0xc0, 0x4f, 0xa3, 0x1a, 0x86);
#endif

#if (_WIN32_IE >= 0x0500)
// CLSID_FolderShortcut {0AFACED1-E828-11D1-9187-B532F1E9575D}
DEFINE_GUID(CLSID_FolderShortcut, 0x0AFACED1,0xE828,0x11D1,0x91,0x87,0xB5,0x32,0xF1,0xE9,0x57,0x5D);
#endif

DEFINE_GUID(IID_IInputObject,           0x68284faa, 0x6a48, 0x11d0, 0x8c, 0x78, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0xb4);
DEFINE_GUID(IID_IInputObjectSite,       0xf1db8392, 0x7331, 0x11d0, 0x8c, 0x99, 0x0, 0xa0, 0xc9, 0x2d, 0xbf, 0xe8);

DEFINE_GUID(IID_IDockingWindow,         0x12dd920, 0x7b26, 0x11d0, 0x8c, 0xa9, 0x0, 0xa0, 0xc9, 0x2d, 0xbf, 0xe8);
DEFINE_GUID(IID_IDockingWindowSite,     0x2a342fc2, 0x7b26, 0x11d0, 0x8c, 0xa9, 0x0, 0xa0, 0xc9, 0x2d, 0xbf, 0xe8);
DEFINE_GUID(IID_IDockingWindowFrame,    0x47d2657a, 0x7b27, 0x11d0, 0x8c, 0xa9, 0x0, 0xa0, 0xc9, 0x2d, 0xbf, 0xe8);

DEFINE_GUID(IID_IShellIconOverlay,      0x7D688A70L, 0xC613, 0x11D0, 0x99, 0x9B, 0x00, 0xC0, 0x4F, 0xD6, 0x55, 0xE1);
DEFINE_GUID(IID_IShellIconOverlayManager, 0x63B51F80L, 0xC868, 0x11D0, 0x99, 0x9C, 0x00, 0xC0, 0x4F, 0xD6, 0x55, 0xE1);
DEFINE_GUID(IID_IShellIconOverlayIdentifier,  0x0C6C4200L, 0xC589, 0x11D0, 0x99, 0x9A, 0x00, 0xC0, 0x4F, 0xD6, 0x55, 0xE1);

DEFINE_GUID(IID_ICommDlgBrowser2,       0x6d71532e, 0x889e, 0x11d1, 0x99, 0x7f, 0x8, 0x0, 0x36, 0xaf, 0x3f, 0x3);


// {1AC3D9F0-175C-11d1-95BE-00609797EA4F}
DEFINE_GUID(IID_IPersistFolder2,        0x1ac3d9f0, 0x175c, 0x11d1, 0x95, 0xbe, 0x0, 0x60, 0x97, 0x97, 0xea, 0x4f);
// {C7264BF0-EDB6-11d1-8546-006008059367}
DEFINE_GUID(IID_IPersistFolder3,        0xc7264bf0, 0xedb6, 0x11d1, 0x85, 0x46, 0x0, 0x60, 0x8, 0x5, 0x93, 0x67);

// {63B51F81-C868-11D0-999C-00C04FD655E1}
DEFINE_GUID(CLSID_CFSIconOverlayManager, 0x63B51F81L, 0xC868, 0x11D0, 0x99, 0x9C, 0x00, 0xC0, 0x4F, 0xD6, 0x55, 0xE1);

// {BB2E617C-0920-11d1-9A0B-00C04FC2D6C1}
DEFINE_GUID(IID_IExtractImage,               0xbb2e617c, 0x920, 0x11d1, 0x9a, 0xb, 0x0, 0xc0, 0x4f, 0xc2, 0xd6, 0xc1);

// {85788D00-6807-11d0-B810-00C04FD706EC}
DEFINE_GUID( IID_IRunnableTask,              0x85788d00, 0x6807, 0x11d0, 0xb8, 0x10, 0x0, 0xc0, 0x4f, 0xd7, 0x6, 0xec);


#if (_WIN32_IE >= 0x0500)
// {953BB1EE-93B4-11d1-98A3-00C04FB687DA}
DEFINE_GUID(IID_IExtractImage2,              0x953bb1ee, 0x93b4, 0x11d1, 0x98, 0xa3, 0x0, 0xc0, 0x4f, 0xb6, 0x87, 0xda);

#endif


// {BCFCE0A0-EC17-11d0-8D10-00A0C90F2719}
DEFINE_GUID(IID_IContextMenu3,          0xbcfce0a0, 0xec17, 0x11d0, 0x8d, 0x10, 0x0, 0xa0, 0xc9, 0xf, 0x27, 0x19);


/// DeskBar stuff
DEFINE_GUID(IID_IDeskBand,              0xEB0FE172L, 0x1A3A, 0x11D0, 0x89, 0xB3, 0x00, 0xA0, 0xC9, 0x0A, 0x90, 0xAC);
#define CGID_DeskBand IID_IDeskBand
#ifdef ISHELLTOOLBAND_COMPAT
DEFINE_GUID(IID_IShellToolband,         0xEB0FE171L, 0x1A3A, 0x11D0, 0x89, 0xB3, 0x00, 0xA0, 0xC9, 0x0A, 0x90, 0xAC);
#endif
#endif


#define SID_SShellBrowser IID_IShellBrowser
#if (_WIN32_IE >= 0x0400)
#define SID_SShellDesktop CLSID_ShellDesktop
#endif

//
//  IShellDiscardable is an IID-only interface. If the object supports this
// interface it can be discarded anytime. IWebBrowser::PutProperty QI's for
// this interface to detect discardable properties. 
//
DEFINE_GUID(IID_IDiscardableBrowserProperty, 0x49c3de7c, 0xd329, 0x11d0, 0xab, 0x73, 0x00, 0xc0, 0x4f, 0xc3, 0x3e, 0x80);

#ifdef UNICODE
#define IID_IFileViewer         IID_IFileViewerW
#define IID_IShellLink          IID_IShellLinkW
#define IID_IExtractIcon        IID_IExtractIconW
#define IID_IShellCopyHook      IID_IShellCopyHookW
#define IID_IShellExecuteHook   IID_IShellExecuteHookW
#define IID_INewShortcutHook    IID_INewShortcutHookW
#else
#define IID_IFileViewer         IID_IFileViewerA
#define IID_IShellLink          IID_IShellLinkA
#define IID_IExtractIcon        IID_IExtractIconA
#define IID_IShellCopyHook      IID_IShellCopyHookA
#define IID_IShellExecuteHook   IID_IShellExecuteHookA
#define IID_INewShortcutHook    IID_INewShortcutHookA
#endif

#ifndef NO_INTSHCUT_GUIDS
// Include internet shortcut GUIDs
#include <isguids.h>
#endif

#ifndef NO_SHDOCVW_GUIDS

#include <exdisp.h>
#include <shldisp.h>


#if (_WIN32_IE >= 0x0400)
// UrlHistory Guids
DEFINE_GUID(CLSID_CUrlHistory,          0x3C374A40L, 0xBAE4, 0x11CF, 0xBF, 0x7D, 0x00, 0xAA, 0x00, 0x69, 0x46, 0xEE);
#define SID_SUrlHistory         CLSID_CUrlHistory

//UrlSearchHook Guids
DEFINE_GUID(CLSID_CURLSearchHook,       0xCFBFAE00L, 0x17A6, 0x11D0, 0x99, 0xCB, 0x00, 0xC0, 0x4F, 0xD6, 0x44, 0x97);


#define SID_SInternetExplorer IID_IWebBrowserApp
#define SID_SWebBrowserApp    IID_IWebBrowserApp


//
// Top-most browser implementation in the heirarchy. use IServiceProvider::QueryService()
// to get to interfaces (IID_IShellBrowser, IID_IBrowserService, etc.)
//
DEFINE_GUID(SID_STopLevelBrowser,       0x4C96BE40L, 0x915C, 0x11CF, 0x99, 0xD3, 0x00, 0xAA, 0x00, 0x4A, 0xE8, 0x37);

#endif

#endif


#if (_WIN32_IE >= 0x0400)

// {75048700-EF1F-11D0-9888-006097DEACF9}
DEFINE_GUID( CLSID_ActiveDesktop, 0x75048700L, 0xEF1F, 0x11D0, 0x98, 0x88, 0x00, 0x60, 0x97, 0xDE, 0xAC, 0xF9);

// {F490EB00-1240-11D1-9888-006097DEACF9}
DEFINE_GUID(IID_IActiveDesktop, 0xF490EB00L, 0x1240, 0x11D1, 0x98, 0x88, 0x00, 0x60, 0x97, 0xDE, 0xAC, 0xF9);


// {56FDF344-FD6D-11d0-958A-006097C9A090}
DEFINE_GUID(CLSID_TaskbarList, 0x56fdf344, 0xfd6d, 0x11d0, 0x95, 0x8a, 0x0, 0x60, 0x97, 0xc9, 0xa0, 0x90);

// {56FDF342-FD6D-11d0-958A-006097C9A090}
DEFINE_GUID(IID_ITaskbarList, 0x56fdf342, 0xfd6d, 0x11d0, 0x95, 0x8a, 0x0, 0x60, 0x97, 0xc9, 0xa0, 0x90);

// a5df1ea0-5702-11d1-83fa-00a0c90dc849
DEFINE_GUID(IID_IDocFindFolder, 0xa5df1ea0, 0x5702, 0x11d1, 0x83, 0xfa, 0x00, 0xa0, 0xc9, 0x0d, 0xc8, 0x49);

// {74C26041-70D1-11d1-B75A-00A0C90564FE}
DEFINE_GUID(IID_ISynchronizedCallBack, 0x74c26041, 0x70d1, 0x11d1, 0xb7, 0x5a, 0x0, 0xa0, 0xc9, 0x5, 0x64, 0xfe);

// Extended column handler interfaces
// {D2A105C0-87D5-11d1-8391-0000F80461CF}
DEFINE_GUID(IID_IShellDetails3,     0xd2a105c0, 0x87d5, 0x11d1, 0x83, 0x91, 0x0, 0x0, 0xf8, 0x4, 0x61, 0xcf);

// {24F14F00-7B1C-11d1-838f-0000F80461CF}
DEFINE_GUID(IID_IColumnProvider,    0x24f14f00, 0x7b1c, 0x11d1, 0x83, 0x8f, 0x0, 0x0, 0xf8, 0x4, 0x61, 0xcf);

// {24F14F01-7B1C-11d1-838f-0000F80461CF}
DEFINE_GUID(CLSID_DocObjColumnProvider, 0x24f14f01, 0x7b1c, 0x11d1, 0x83, 0x8f, 0x0, 0x0, 0xf8, 0x4, 0x61, 0xcf);

// {24F14F02-7B1C-11d1-838f-0000F80461CF}
DEFINE_GUID(CLSID_URLColumnProvider,    0x24f14f02, 0x7b1c, 0x11d1, 0x83, 0x8f, 0x0, 0x0, 0xf8, 0x4, 0x61, 0xcf);

// For Internet Shortcut Creation Command
// The shell uses this command to allow trident to save off it's per frame data in the shortcut
// and to allow it to fire the OnPersist() event on every frame
// {93A68750-951A-11d1-946F-000000000000}
DEFINE_GUID(CGID_ShortCut, 0x93a68750, 0x951a, 0x11d1, 0x94, 0x6f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);


// {FB700430-952C-11d1-946F-000000000000}
DEFINE_GUID(IID_INamedPropertyBag, 0xfb700430, 0x952c, 0x11d1, 0x94, 0x6f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

// {1E796980-9CC5-11D1-A83F-00C04FC99D61}
DEFINE_GUID(CLSID_InternetButtons, 0x1E796980L, 0x9CC5, 0x11D1, 0xA8, 0x3F, 0x00, 0xC0, 0x4F, 0xC9, 0x9D, 0x61);

// {CFCCC7A0-A282-11D1-9082-006008059382}
DEFINE_GUID(CLSID_DarwinAppPublisher, 0xCFCCC7A0L, 0xA282, 0x11D1, 0x90, 0x82, 0x00, 0x60, 0x08, 0x05, 0x93, 0x82);

// {7057E952-BD1B-11d1-8919-00C04FC2C836}
DEFINE_GUID(CLSID_DocHostUIHandler, 0x7057e952, 0xbd1b, 0x11d1, 0x89, 0x19, 0x0, 0xc0, 0x4f, 0xc2, 0xc8, 0x36);
#endif  // _WIN32_IE

#if (_WIN32_IE >= 0x0500)

// {51D366C0-F5AA-11D1-9E60-00C04FC99D61}
DEFINE_GUID(IID_IShellFolder2, 0x51D366C0L, 0xF5AA, 0x11D1, 0x9E, 0x60, 0x00, 0xC0, 0x4F, 0xC9, 0x9D, 0x61);

// {0E700BE1-9DB6-11d1-A1CE-00C04FD75D13}
DEFINE_GUID(IID_IEnumExtraSearch,  0xe700be1, 0x9db6, 0x11d1, 0xa1, 0xce, 0x0, 0xc0, 0x4f, 0xd7, 0x5d, 0x13);

// {12518493-00B2-11d2-9FA5-9E3420524153}								 
DEFINE_GUID(CLSID_MountedVolume, 0x12518493, 0x00B2, 0x11d2, 0x9F, 0xA5, 0x9E, 0x34, 0x20, 0x52, 0x41, 0x53);

// {12518492-00B2-11d2-9FA5-9E3420524153}
DEFINE_GUID(IID_IMountedVolume, 0x12518492, 0x00B2, 0x11d2, 0x9F, 0xA5, 0x9E, 0x34, 0x20, 0x52, 0x41, 0x53);
#endif

#endif // _SHLGUID_H_

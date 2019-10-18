/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Fri Jul 31 15:04:35 1998
 */
/* Compiler settings for mshtmhst.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data , no_format_optimization
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __mshtmhst_h__
#define __mshtmhst_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDocHostUIHandler_FWD_DEFINED__
#define __IDocHostUIHandler_FWD_DEFINED__
typedef interface IDocHostUIHandler IDocHostUIHandler;
#endif 	/* __IDocHostUIHandler_FWD_DEFINED__ */


#ifndef __ICustomDoc_FWD_DEFINED__
#define __ICustomDoc_FWD_DEFINED__
typedef interface ICustomDoc ICustomDoc;
#endif 	/* __ICustomDoc_FWD_DEFINED__ */


#ifndef __IDocHostShowUI_FWD_DEFINED__
#define __IDocHostShowUI_FWD_DEFINED__
typedef interface IDocHostShowUI IDocHostShowUI;
#endif 	/* __IDocHostShowUI_FWD_DEFINED__ */


#ifndef __ICSSFilterSite_FWD_DEFINED__
#define __ICSSFilterSite_FWD_DEFINED__
typedef interface ICSSFilterSite ICSSFilterSite;
#endif 	/* __ICSSFilterSite_FWD_DEFINED__ */


#ifndef __ICSSFilter_FWD_DEFINED__
#define __ICSSFilter_FWD_DEFINED__
typedef interface ICSSFilter ICSSFilter;
#endif 	/* __ICSSFilter_FWD_DEFINED__ */


#ifndef __IElementBehavior_FWD_DEFINED__
#define __IElementBehavior_FWD_DEFINED__
typedef interface IElementBehavior IElementBehavior;
#endif 	/* __IElementBehavior_FWD_DEFINED__ */


#ifndef __IElementBehaviorSite_FWD_DEFINED__
#define __IElementBehaviorSite_FWD_DEFINED__
typedef interface IElementBehaviorSite IElementBehaviorSite;
#endif 	/* __IElementBehaviorSite_FWD_DEFINED__ */


#ifndef __IElementBehaviorSiteOM_FWD_DEFINED__
#define __IElementBehaviorSiteOM_FWD_DEFINED__
typedef interface IElementBehaviorSiteOM IElementBehaviorSiteOM;
#endif 	/* __IElementBehaviorSiteOM_FWD_DEFINED__ */


#ifndef __IElementBehaviorRender_FWD_DEFINED__
#define __IElementBehaviorRender_FWD_DEFINED__
typedef interface IElementBehaviorRender IElementBehaviorRender;
#endif 	/* __IElementBehaviorRender_FWD_DEFINED__ */


#ifndef __IElementBehaviorSiteRender_FWD_DEFINED__
#define __IElementBehaviorSiteRender_FWD_DEFINED__
typedef interface IElementBehaviorSiteRender IElementBehaviorSiteRender;
#endif 	/* __IElementBehaviorSiteRender_FWD_DEFINED__ */


#ifndef __ISubDivisionProvider_FWD_DEFINED__
#define __ISubDivisionProvider_FWD_DEFINED__
typedef interface ISubDivisionProvider ISubDivisionProvider;
#endif 	/* __ISubDivisionProvider_FWD_DEFINED__ */


#ifndef __IElementBehaviorUI_FWD_DEFINED__
#define __IElementBehaviorUI_FWD_DEFINED__
typedef interface IElementBehaviorUI IElementBehaviorUI;
#endif 	/* __IElementBehaviorUI_FWD_DEFINED__ */


#ifndef __IElementBehaviorCategory_FWD_DEFINED__
#define __IElementBehaviorCategory_FWD_DEFINED__
typedef interface IElementBehaviorCategory IElementBehaviorCategory;
#endif 	/* __IElementBehaviorCategory_FWD_DEFINED__ */


#ifndef __IElementBehaviorSiteCategory_FWD_DEFINED__
#define __IElementBehaviorSiteCategory_FWD_DEFINED__
typedef interface IElementBehaviorSiteCategory IElementBehaviorSiteCategory;
#endif 	/* __IElementBehaviorSiteCategory_FWD_DEFINED__ */


#ifndef __IElementBehaviorFactory_FWD_DEFINED__
#define __IElementBehaviorFactory_FWD_DEFINED__
typedef interface IElementBehaviorFactory IElementBehaviorFactory;
#endif 	/* __IElementBehaviorFactory_FWD_DEFINED__ */


#ifndef __IClassFactory3_FWD_DEFINED__
#define __IClassFactory3_FWD_DEFINED__
typedef interface IClassFactory3 IClassFactory3;
#endif 	/* __IClassFactory3_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"
#include "docobj.h"
#include "mshtml.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_mshtmhst_0000 */
/* [local] */ 

//=--------------------------------------------------------------------------=
// mshtmhst.h
//=--------------------------------------------------------------------------=
// (C) Copyright 1995-1998 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#pragma comment(lib,"uuid.lib")

//--------------------------------------------------------------------------
// MSTHML Advanced Host Interfaces.

#ifndef MSHTMHST_H
#define MSHTMHST_H
#define CONTEXT_MENU_DEFAULT        0
#define CONTEXT_MENU_IMAGE          1
#define CONTEXT_MENU_CONTROL        2
#define CONTEXT_MENU_TABLE          3
// in browse mode
#define CONTEXT_MENU_TEXTSELECT     4
#define CONTEXT_MENU_ANCHOR         5
#define CONTEXT_MENU_UNKNOWN        6
// These 2 are mapped to IMAGE for the public
#define CONTEXT_MENU_IMGDYNSRC      7
#define CONTEXT_MENU_IMGART         8
#define CONTEXT_MENU_DEBUG          9
#define MENUEXT_SHOWDIALOG           0x1
#define DOCHOSTUIFLAG_BROWSER       DOCHOSTUIFLAG_DISABLE_HELP_MENU | DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE 
EXTERN_C const GUID CGID_MSHTML;
#define CMDSETID_Forms3 CGID_MSHTML
#define SZ_HTML_CLIENTSITE_OBJECTPARAM L"{d4db6850-5385-11d0-89e9-00a0c90a90ac}"
typedef HRESULT STDAPICALLTYPE SHOWHTMLDIALOGFN (HWND hwndParent, IMoniker *pmk, VARIANT *pvarArgIn, WCHAR* pchOptions, VARIANT *pvArgOut);

STDAPI ShowHTMLDialog(                   
    HWND        hwndParent,              
    IMoniker *  pMk,                     
    VARIANT *   pvarArgIn,               
    WCHAR *     pchOptions,              
    VARIANT *   pvarArgOut               
    );                                   

STDAPI RunHTMLApplication(               
    HINSTANCE hinst,                     
    HINSTANCE hPrevInst,                 
    LPSTR szCmdLine,                     
    int nCmdShow                         
    );                                   

typedef 
enum tagDOCHOSTUITYPE
    {	DOCHOSTUITYPE_BROWSE	= 0,
	DOCHOSTUITYPE_AUTHOR	= 1
    }	DOCHOSTUITYPE;

typedef 
enum tagDOCHOSTUIDBLCLK
    {	DOCHOSTUIDBLCLK_DEFAULT	= 0,
	DOCHOSTUIDBLCLK_SHOWPROPERTIES	= 1,
	DOCHOSTUIDBLCLK_SHOWCODE	= 2
    }	DOCHOSTUIDBLCLK;

typedef 
enum tagDOCHOSTUIFLAG
    {	DOCHOSTUIFLAG_DIALOG	= 1,
	DOCHOSTUIFLAG_DISABLE_HELP_MENU	= 2,
	DOCHOSTUIFLAG_NO3DBORDER	= 4,
	DOCHOSTUIFLAG_SCROLL_NO	= 8,
	DOCHOSTUIFLAG_DISABLE_SCRIPT_INACTIVE	= 16,
	DOCHOSTUIFLAG_OPENNEWWIN	= 32,
	DOCHOSTUIFLAG_DISABLE_OFFSCREEN	= 64,
	DOCHOSTUIFLAG_FLAT_SCROLLBAR	= 128,
	DOCHOSTUIFLAG_DIV_BLOCKDEFAULT	= 256,
	DOCHOSTUIFLAG_ACTIVATE_CLIENTHIT_ONLY	= 512
    }	DOCHOSTUIFLAG;



extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0000_v0_0_s_ifspec;

#ifndef __IDocHostUIHandler_INTERFACE_DEFINED__
#define __IDocHostUIHandler_INTERFACE_DEFINED__

/* interface IDocHostUIHandler */
/* [local][unique][uuid][object] */ 

typedef struct  _DOCHOSTUIINFO
    {
    ULONG cbSize;
    DWORD dwFlags;
    DWORD dwDoubleClick;
    }	DOCHOSTUIINFO;


EXTERN_C const IID IID_IDocHostUIHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("bd3f23c0-d43e-11cf-893b-00aa00bdce1a")
    IDocHostUIHandler : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShowContextMenu( 
            /* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHostInfo( 
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowUI( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
            /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
            /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HideUI( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateUI( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableModeless( 
            /* [in] */ BOOL fEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnDocWindowActivate( 
            /* [in] */ BOOL fActivate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
            /* [in] */ BOOL fRameWindow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOptionKeyPath( 
            /* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDropTarget( 
            /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExternal( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FilterDataObject( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDocHostUIHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDocHostUIHandler __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDocHostUIHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowContextMenu )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHostInfo )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowUI )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
            /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
            /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HideUI )( 
            IDocHostUIHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateUI )( 
            IDocHostUIHandler __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableModeless )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ BOOL fEnable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDocWindowActivate )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ BOOL fActivate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnFrameWindowActivate )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ BOOL fActivate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResizeBorder )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
            /* [in] */ BOOL fRameWindow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TranslateAccelerator )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOptionKeyPath )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDropTarget )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExternal )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TranslateUrl )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FilterDataObject )( 
            IDocHostUIHandler __RPC_FAR * This,
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet);
        
        END_INTERFACE
    } IDocHostUIHandlerVtbl;

    interface IDocHostUIHandler
    {
        CONST_VTBL struct IDocHostUIHandlerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDocHostUIHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDocHostUIHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDocHostUIHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDocHostUIHandler_ShowContextMenu(This,dwID,ppt,pcmdtReserved,pdispReserved)	\
    (This)->lpVtbl -> ShowContextMenu(This,dwID,ppt,pcmdtReserved,pdispReserved)

#define IDocHostUIHandler_GetHostInfo(This,pInfo)	\
    (This)->lpVtbl -> GetHostInfo(This,pInfo)

#define IDocHostUIHandler_ShowUI(This,dwID,pActiveObject,pCommandTarget,pFrame,pDoc)	\
    (This)->lpVtbl -> ShowUI(This,dwID,pActiveObject,pCommandTarget,pFrame,pDoc)

#define IDocHostUIHandler_HideUI(This)	\
    (This)->lpVtbl -> HideUI(This)

#define IDocHostUIHandler_UpdateUI(This)	\
    (This)->lpVtbl -> UpdateUI(This)

#define IDocHostUIHandler_EnableModeless(This,fEnable)	\
    (This)->lpVtbl -> EnableModeless(This,fEnable)

#define IDocHostUIHandler_OnDocWindowActivate(This,fActivate)	\
    (This)->lpVtbl -> OnDocWindowActivate(This,fActivate)

#define IDocHostUIHandler_OnFrameWindowActivate(This,fActivate)	\
    (This)->lpVtbl -> OnFrameWindowActivate(This,fActivate)

#define IDocHostUIHandler_ResizeBorder(This,prcBorder,pUIWindow,fRameWindow)	\
    (This)->lpVtbl -> ResizeBorder(This,prcBorder,pUIWindow,fRameWindow)

#define IDocHostUIHandler_TranslateAccelerator(This,lpMsg,pguidCmdGroup,nCmdID)	\
    (This)->lpVtbl -> TranslateAccelerator(This,lpMsg,pguidCmdGroup,nCmdID)

#define IDocHostUIHandler_GetOptionKeyPath(This,pchKey,dw)	\
    (This)->lpVtbl -> GetOptionKeyPath(This,pchKey,dw)

#define IDocHostUIHandler_GetDropTarget(This,pDropTarget,ppDropTarget)	\
    (This)->lpVtbl -> GetDropTarget(This,pDropTarget,ppDropTarget)

#define IDocHostUIHandler_GetExternal(This,ppDispatch)	\
    (This)->lpVtbl -> GetExternal(This,ppDispatch)

#define IDocHostUIHandler_TranslateUrl(This,dwTranslate,pchURLIn,ppchURLOut)	\
    (This)->lpVtbl -> TranslateUrl(This,dwTranslate,pchURLIn,ppchURLOut)

#define IDocHostUIHandler_FilterDataObject(This,pDO,ppDORet)	\
    (This)->lpVtbl -> FilterDataObject(This,pDO,ppDORet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDocHostUIHandler_ShowContextMenu_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ DWORD dwID,
    /* [in] */ POINT __RPC_FAR *ppt,
    /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
    /* [in] */ IDispatch __RPC_FAR *pdispReserved);


void __RPC_STUB IDocHostUIHandler_ShowContextMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_GetHostInfo_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo);


void __RPC_STUB IDocHostUIHandler_GetHostInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_ShowUI_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ DWORD dwID,
    /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
    /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
    /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
    /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc);


void __RPC_STUB IDocHostUIHandler_ShowUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_HideUI_Proxy( 
    IDocHostUIHandler __RPC_FAR * This);


void __RPC_STUB IDocHostUIHandler_HideUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_UpdateUI_Proxy( 
    IDocHostUIHandler __RPC_FAR * This);


void __RPC_STUB IDocHostUIHandler_UpdateUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_EnableModeless_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ BOOL fEnable);


void __RPC_STUB IDocHostUIHandler_EnableModeless_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_OnDocWindowActivate_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ BOOL fActivate);


void __RPC_STUB IDocHostUIHandler_OnDocWindowActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_OnFrameWindowActivate_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ BOOL fActivate);


void __RPC_STUB IDocHostUIHandler_OnFrameWindowActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_ResizeBorder_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ LPCRECT prcBorder,
    /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
    /* [in] */ BOOL fRameWindow);


void __RPC_STUB IDocHostUIHandler_ResizeBorder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_TranslateAccelerator_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ LPMSG lpMsg,
    /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
    /* [in] */ DWORD nCmdID);


void __RPC_STUB IDocHostUIHandler_TranslateAccelerator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_GetOptionKeyPath_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *pchKey,
    /* [in] */ DWORD dw);


void __RPC_STUB IDocHostUIHandler_GetOptionKeyPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_GetDropTarget_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
    /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);


void __RPC_STUB IDocHostUIHandler_GetDropTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_GetExternal_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);


void __RPC_STUB IDocHostUIHandler_GetExternal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_TranslateUrl_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ DWORD dwTranslate,
    /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);


void __RPC_STUB IDocHostUIHandler_TranslateUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostUIHandler_FilterDataObject_Proxy( 
    IDocHostUIHandler __RPC_FAR * This,
    /* [in] */ IDataObject __RPC_FAR *pDO,
    /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet);


void __RPC_STUB IDocHostUIHandler_FilterDataObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDocHostUIHandler_INTERFACE_DEFINED__ */


#ifndef __ICustomDoc_INTERFACE_DEFINED__
#define __ICustomDoc_INTERFACE_DEFINED__

/* interface ICustomDoc */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_ICustomDoc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f3f0-98b5-11cf-bb82-00aa00bdce0b")
    ICustomDoc : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetUIHandler( 
            /* [in] */ IDocHostUIHandler __RPC_FAR *pUIHandler) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICustomDocVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICustomDoc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICustomDoc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICustomDoc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUIHandler )( 
            ICustomDoc __RPC_FAR * This,
            /* [in] */ IDocHostUIHandler __RPC_FAR *pUIHandler);
        
        END_INTERFACE
    } ICustomDocVtbl;

    interface ICustomDoc
    {
        CONST_VTBL struct ICustomDocVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICustomDoc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICustomDoc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICustomDoc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICustomDoc_SetUIHandler(This,pUIHandler)	\
    (This)->lpVtbl -> SetUIHandler(This,pUIHandler)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICustomDoc_SetUIHandler_Proxy( 
    ICustomDoc __RPC_FAR * This,
    /* [in] */ IDocHostUIHandler __RPC_FAR *pUIHandler);


void __RPC_STUB ICustomDoc_SetUIHandler_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICustomDoc_INTERFACE_DEFINED__ */


#ifndef __IDocHostShowUI_INTERFACE_DEFINED__
#define __IDocHostShowUI_INTERFACE_DEFINED__

/* interface IDocHostShowUI */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IDocHostShowUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c4d244b0-d43e-11cf-893b-00aa00bdce1a")
    IDocHostShowUI : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ShowMessage( 
            /* [in] */ HWND hwnd,
            /* [in] */ LPOLESTR lpstrText,
            /* [in] */ LPOLESTR lpstrCaption,
            /* [in] */ DWORD dwType,
            /* [in] */ LPOLESTR lpstrHelpFile,
            /* [in] */ DWORD dwHelpContext,
            /* [out] */ LRESULT __RPC_FAR *plResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowHelp( 
            /* [in] */ HWND hwnd,
            /* [in] */ LPOLESTR pszHelpFile,
            /* [in] */ UINT uCommand,
            /* [in] */ DWORD dwData,
            /* [in] */ POINT ptMouse,
            /* [out] */ IDispatch __RPC_FAR *pDispatchObjectHit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDocHostShowUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDocHostShowUI __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDocHostShowUI __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDocHostShowUI __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowMessage )( 
            IDocHostShowUI __RPC_FAR * This,
            /* [in] */ HWND hwnd,
            /* [in] */ LPOLESTR lpstrText,
            /* [in] */ LPOLESTR lpstrCaption,
            /* [in] */ DWORD dwType,
            /* [in] */ LPOLESTR lpstrHelpFile,
            /* [in] */ DWORD dwHelpContext,
            /* [out] */ LRESULT __RPC_FAR *plResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowHelp )( 
            IDocHostShowUI __RPC_FAR * This,
            /* [in] */ HWND hwnd,
            /* [in] */ LPOLESTR pszHelpFile,
            /* [in] */ UINT uCommand,
            /* [in] */ DWORD dwData,
            /* [in] */ POINT ptMouse,
            /* [out] */ IDispatch __RPC_FAR *pDispatchObjectHit);
        
        END_INTERFACE
    } IDocHostShowUIVtbl;

    interface IDocHostShowUI
    {
        CONST_VTBL struct IDocHostShowUIVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDocHostShowUI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDocHostShowUI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDocHostShowUI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDocHostShowUI_ShowMessage(This,hwnd,lpstrText,lpstrCaption,dwType,lpstrHelpFile,dwHelpContext,plResult)	\
    (This)->lpVtbl -> ShowMessage(This,hwnd,lpstrText,lpstrCaption,dwType,lpstrHelpFile,dwHelpContext,plResult)

#define IDocHostShowUI_ShowHelp(This,hwnd,pszHelpFile,uCommand,dwData,ptMouse,pDispatchObjectHit)	\
    (This)->lpVtbl -> ShowHelp(This,hwnd,pszHelpFile,uCommand,dwData,ptMouse,pDispatchObjectHit)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDocHostShowUI_ShowMessage_Proxy( 
    IDocHostShowUI __RPC_FAR * This,
    /* [in] */ HWND hwnd,
    /* [in] */ LPOLESTR lpstrText,
    /* [in] */ LPOLESTR lpstrCaption,
    /* [in] */ DWORD dwType,
    /* [in] */ LPOLESTR lpstrHelpFile,
    /* [in] */ DWORD dwHelpContext,
    /* [out] */ LRESULT __RPC_FAR *plResult);


void __RPC_STUB IDocHostShowUI_ShowMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDocHostShowUI_ShowHelp_Proxy( 
    IDocHostShowUI __RPC_FAR * This,
    /* [in] */ HWND hwnd,
    /* [in] */ LPOLESTR pszHelpFile,
    /* [in] */ UINT uCommand,
    /* [in] */ DWORD dwData,
    /* [in] */ POINT ptMouse,
    /* [out] */ IDispatch __RPC_FAR *pDispatchObjectHit);


void __RPC_STUB IDocHostShowUI_ShowHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDocHostShowUI_INTERFACE_DEFINED__ */


#ifndef __ICSSFilterSite_INTERFACE_DEFINED__
#define __ICSSFilterSite_INTERFACE_DEFINED__

/* interface ICSSFilterSite */
/* [object][uuid][dual][oleautomation] */ 


EXTERN_C const IID IID_ICSSFilterSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f3ed-98b5-11cf-bb82-00aa00bdce0b")
    ICSSFilterSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetElement( 
            /* [out][retval] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FireOnFilterChangeEvent( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICSSFilterSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICSSFilterSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICSSFilterSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICSSFilterSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetElement )( 
            ICSSFilterSite __RPC_FAR * This,
            /* [out][retval] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElem);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireOnFilterChangeEvent )( 
            ICSSFilterSite __RPC_FAR * This);
        
        END_INTERFACE
    } ICSSFilterSiteVtbl;

    interface ICSSFilterSite
    {
        CONST_VTBL struct ICSSFilterSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICSSFilterSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICSSFilterSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICSSFilterSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICSSFilterSite_GetElement(This,ppElem)	\
    (This)->lpVtbl -> GetElement(This,ppElem)

#define ICSSFilterSite_FireOnFilterChangeEvent(This)	\
    (This)->lpVtbl -> FireOnFilterChangeEvent(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICSSFilterSite_GetElement_Proxy( 
    ICSSFilterSite __RPC_FAR * This,
    /* [out][retval] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElem);


void __RPC_STUB ICSSFilterSite_GetElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICSSFilterSite_FireOnFilterChangeEvent_Proxy( 
    ICSSFilterSite __RPC_FAR * This);


void __RPC_STUB ICSSFilterSite_FireOnFilterChangeEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICSSFilterSite_INTERFACE_DEFINED__ */


#ifndef __ICSSFilter_INTERFACE_DEFINED__
#define __ICSSFilter_INTERFACE_DEFINED__

/* interface ICSSFilter */
/* [object][uuid][dual][oleautomation] */ 


EXTERN_C const IID IID_ICSSFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f3ec-98b5-11cf-bb82-00aa00bdce0b")
    ICSSFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSite( 
            /* [in] */ ICSSFilterSite __RPC_FAR *pSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnAmbientPropertyChange( 
            /* [in] */ LONG dispid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICSSFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICSSFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICSSFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICSSFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSite )( 
            ICSSFilter __RPC_FAR * This,
            /* [in] */ ICSSFilterSite __RPC_FAR *pSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnAmbientPropertyChange )( 
            ICSSFilter __RPC_FAR * This,
            /* [in] */ LONG dispid);
        
        END_INTERFACE
    } ICSSFilterVtbl;

    interface ICSSFilter
    {
        CONST_VTBL struct ICSSFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICSSFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICSSFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICSSFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICSSFilter_SetSite(This,pSink)	\
    (This)->lpVtbl -> SetSite(This,pSink)

#define ICSSFilter_OnAmbientPropertyChange(This,dispid)	\
    (This)->lpVtbl -> OnAmbientPropertyChange(This,dispid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICSSFilter_SetSite_Proxy( 
    ICSSFilter __RPC_FAR * This,
    /* [in] */ ICSSFilterSite __RPC_FAR *pSink);


void __RPC_STUB ICSSFilter_SetSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICSSFilter_OnAmbientPropertyChange_Proxy( 
    ICSSFilter __RPC_FAR * This,
    /* [in] */ LONG dispid);


void __RPC_STUB ICSSFilter_OnAmbientPropertyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICSSFilter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0489 */
/* [local] */ 


#define BEHAVIOREVENT_CONTENTCHANGE 0
#define BEHAVIOREVENT_DOCUMENTREADY 1


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0489_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0489_v0_0_s_ifspec;

#ifndef __IElementBehavior_INTERFACE_DEFINED__
#define __IElementBehavior_INTERFACE_DEFINED__

/* interface IElementBehavior */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehavior;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f425-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehavior : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ IElementBehaviorSite __RPC_FAR *pBehaviorSite) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ DWORD dwEvent,
            /* [out][in] */ VARIANT __RPC_FAR *pVar) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehavior __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehavior __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehavior __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IElementBehavior __RPC_FAR * This,
            /* [in] */ IElementBehaviorSite __RPC_FAR *pBehaviorSite);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Notify )( 
            IElementBehavior __RPC_FAR * This,
            /* [in] */ DWORD dwEvent,
            /* [out][in] */ VARIANT __RPC_FAR *pVar);
        
        END_INTERFACE
    } IElementBehaviorVtbl;

    interface IElementBehavior
    {
        CONST_VTBL struct IElementBehaviorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehavior_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehavior_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehavior_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehavior_Init(This,pBehaviorSite)	\
    (This)->lpVtbl -> Init(This,pBehaviorSite)

#define IElementBehavior_Notify(This,dwEvent,pVar)	\
    (This)->lpVtbl -> Notify(This,dwEvent,pVar)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehavior_Init_Proxy( 
    IElementBehavior __RPC_FAR * This,
    /* [in] */ IElementBehaviorSite __RPC_FAR *pBehaviorSite);


void __RPC_STUB IElementBehavior_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehavior_Notify_Proxy( 
    IElementBehavior __RPC_FAR * This,
    /* [in] */ DWORD dwEvent,
    /* [out][in] */ VARIANT __RPC_FAR *pVar);


void __RPC_STUB IElementBehavior_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehavior_INTERFACE_DEFINED__ */


#ifndef __IElementBehaviorSite_INTERFACE_DEFINED__
#define __IElementBehaviorSite_INTERFACE_DEFINED__

/* interface IElementBehaviorSite */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f427-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorSite : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetElement( 
            /* [out] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElement) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorSite __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetElement )( 
            IElementBehaviorSite __RPC_FAR * This,
            /* [out] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElement);
        
        END_INTERFACE
    } IElementBehaviorSiteVtbl;

    interface IElementBehaviorSite
    {
        CONST_VTBL struct IElementBehaviorSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorSite_GetElement(This,ppElement)	\
    (This)->lpVtbl -> GetElement(This,ppElement)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSite_GetElement_Proxy( 
    IElementBehaviorSite __RPC_FAR * This,
    /* [out] */ IHTMLElement __RPC_FAR *__RPC_FAR *ppElement);


void __RPC_STUB IElementBehaviorSite_GetElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorSite_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0491 */
/* [local] */ 

#define BEHAVIOREVENTFLAGS_BUBBLE 1 


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0491_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0491_v0_0_s_ifspec;

#ifndef __IElementBehaviorSiteOM_INTERFACE_DEFINED__
#define __IElementBehaviorSiteOM_INTERFACE_DEFINED__

/* interface IElementBehaviorSiteOM */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorSiteOM;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f489-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorSiteOM : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegisterEvent( 
            /* [in] */ LPOLESTR pchEvent,
            /* [in] */ DWORD dwFlags,
            /* [out] */ DWORD __RPC_FAR *pdwCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEventCookie( 
            /* [in] */ LPOLESTR pchEvent,
            /* [out] */ DWORD __RPC_FAR *pdwCookie) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FireEvent( 
            /* [in] */ DWORD dwCookie,
            /* [out][in] */ IHTMLEventObj __RPC_FAR *pEventObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateEventObject( 
            /* [out] */ IHTMLEventObj __RPC_FAR *__RPC_FAR *ppEventObject) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RegisterName( 
            /* [in] */ LPOLESTR pchName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorSiteOMVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorSiteOM __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorSiteOM __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorSiteOM __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterEvent )( 
            IElementBehaviorSiteOM __RPC_FAR * This,
            /* [in] */ LPOLESTR pchEvent,
            /* [in] */ DWORD dwFlags,
            /* [out] */ DWORD __RPC_FAR *pdwCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventCookie )( 
            IElementBehaviorSiteOM __RPC_FAR * This,
            /* [in] */ LPOLESTR pchEvent,
            /* [out] */ DWORD __RPC_FAR *pdwCookie);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FireEvent )( 
            IElementBehaviorSiteOM __RPC_FAR * This,
            /* [in] */ DWORD dwCookie,
            /* [out][in] */ IHTMLEventObj __RPC_FAR *pEventObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateEventObject )( 
            IElementBehaviorSiteOM __RPC_FAR * This,
            /* [out] */ IHTMLEventObj __RPC_FAR *__RPC_FAR *ppEventObject);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterName )( 
            IElementBehaviorSiteOM __RPC_FAR * This,
            /* [in] */ LPOLESTR pchName);
        
        END_INTERFACE
    } IElementBehaviorSiteOMVtbl;

    interface IElementBehaviorSiteOM
    {
        CONST_VTBL struct IElementBehaviorSiteOMVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorSiteOM_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorSiteOM_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorSiteOM_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorSiteOM_RegisterEvent(This,pchEvent,dwFlags,pdwCookie)	\
    (This)->lpVtbl -> RegisterEvent(This,pchEvent,dwFlags,pdwCookie)

#define IElementBehaviorSiteOM_GetEventCookie(This,pchEvent,pdwCookie)	\
    (This)->lpVtbl -> GetEventCookie(This,pchEvent,pdwCookie)

#define IElementBehaviorSiteOM_FireEvent(This,dwCookie,pEventObject)	\
    (This)->lpVtbl -> FireEvent(This,dwCookie,pEventObject)

#define IElementBehaviorSiteOM_CreateEventObject(This,ppEventObject)	\
    (This)->lpVtbl -> CreateEventObject(This,ppEventObject)

#define IElementBehaviorSiteOM_RegisterName(This,pchName)	\
    (This)->lpVtbl -> RegisterName(This,pchName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteOM_RegisterEvent_Proxy( 
    IElementBehaviorSiteOM __RPC_FAR * This,
    /* [in] */ LPOLESTR pchEvent,
    /* [in] */ DWORD dwFlags,
    /* [out] */ DWORD __RPC_FAR *pdwCookie);


void __RPC_STUB IElementBehaviorSiteOM_RegisterEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteOM_GetEventCookie_Proxy( 
    IElementBehaviorSiteOM __RPC_FAR * This,
    /* [in] */ LPOLESTR pchEvent,
    /* [out] */ DWORD __RPC_FAR *pdwCookie);


void __RPC_STUB IElementBehaviorSiteOM_GetEventCookie_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteOM_FireEvent_Proxy( 
    IElementBehaviorSiteOM __RPC_FAR * This,
    /* [in] */ DWORD dwCookie,
    /* [out][in] */ IHTMLEventObj __RPC_FAR *pEventObject);


void __RPC_STUB IElementBehaviorSiteOM_FireEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteOM_CreateEventObject_Proxy( 
    IElementBehaviorSiteOM __RPC_FAR * This,
    /* [out] */ IHTMLEventObj __RPC_FAR *__RPC_FAR *ppEventObject);


void __RPC_STUB IElementBehaviorSiteOM_CreateEventObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteOM_RegisterName_Proxy( 
    IElementBehaviorSiteOM __RPC_FAR * This,
    /* [in] */ LPOLESTR pchName);


void __RPC_STUB IElementBehaviorSiteOM_RegisterName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorSiteOM_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0492 */
/* [local] */ 

#define BEHAVIORRENDERINFO_BEFOREBACKGROUND   0x00000001
#define BEHAVIORRENDERINFO_AFTERBACKGROUND    0x00000002
#define BEHAVIORRENDERINFO_BEFORECONTENT      0x00000004
#define BEHAVIORRENDERINFO_AFTERCONTENT       0x00000008
//#define BEHAVIORRENDERINFO_BEFOREFOREGROUND 0x00000010 // equivalent to BEHAVIORRENDERINFO_AFTERTEXT
#define BEHAVIORRENDERINFO_AFTERFOREGROUND    0x00000020
#define BEHAVIORRENDERINFO_DISABLEBACKGROUND  0x00000100
#define BEHAVIORRENDERINFO_DISABLENEGATIVEZ   0x00000200
#define BEHAVIORRENDERINFO_DISABLECONTENT     0x00000400
#define BEHAVIORRENDERINFO_DISABLEPOSITIVEZ   0x00000800


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0492_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0492_v0_0_s_ifspec;

#ifndef __IElementBehaviorRender_INTERFACE_DEFINED__
#define __IElementBehaviorRender_INTERFACE_DEFINED__

/* interface IElementBehaviorRender */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorRender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4aa-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorRender : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ HDC hdc,
            /* [in] */ DWORD dwLayer,
            /* [in] */ LPRECT prc,
            /* [out][in] */ IUnknown __RPC_FAR *pReserved) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRenderInfo( 
            /* [in] */ LPDWORD pdwRenderInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorRenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorRender __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorRender __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorRender __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IElementBehaviorRender __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ DWORD dwLayer,
            /* [in] */ LPRECT prc,
            /* [out][in] */ IUnknown __RPC_FAR *pReserved);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRenderInfo )( 
            IElementBehaviorRender __RPC_FAR * This,
            /* [in] */ LPDWORD pdwRenderInfo);
        
        END_INTERFACE
    } IElementBehaviorRenderVtbl;

    interface IElementBehaviorRender
    {
        CONST_VTBL struct IElementBehaviorRenderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorRender_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorRender_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorRender_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorRender_Draw(This,hdc,dwLayer,prc,pReserved)	\
    (This)->lpVtbl -> Draw(This,hdc,dwLayer,prc,pReserved)

#define IElementBehaviorRender_GetRenderInfo(This,pdwRenderInfo)	\
    (This)->lpVtbl -> GetRenderInfo(This,pdwRenderInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorRender_Draw_Proxy( 
    IElementBehaviorRender __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ DWORD dwLayer,
    /* [in] */ LPRECT prc,
    /* [out][in] */ IUnknown __RPC_FAR *pReserved);


void __RPC_STUB IElementBehaviorRender_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorRender_GetRenderInfo_Proxy( 
    IElementBehaviorRender __RPC_FAR * This,
    /* [in] */ LPDWORD pdwRenderInfo);


void __RPC_STUB IElementBehaviorRender_GetRenderInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorRender_INTERFACE_DEFINED__ */


#ifndef __IElementBehaviorSiteRender_INTERFACE_DEFINED__
#define __IElementBehaviorSiteRender_INTERFACE_DEFINED__

/* interface IElementBehaviorSiteRender */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorSiteRender;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4a7-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorSiteRender : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Invalidate( 
            /* [in] */ LPRECT pRect) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvalidateRenderInfo( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorSiteRenderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorSiteRender __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorSiteRender __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorSiteRender __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invalidate )( 
            IElementBehaviorSiteRender __RPC_FAR * This,
            /* [in] */ LPRECT pRect);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRenderInfo )( 
            IElementBehaviorSiteRender __RPC_FAR * This);
        
        END_INTERFACE
    } IElementBehaviorSiteRenderVtbl;

    interface IElementBehaviorSiteRender
    {
        CONST_VTBL struct IElementBehaviorSiteRenderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorSiteRender_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorSiteRender_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorSiteRender_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorSiteRender_Invalidate(This,pRect)	\
    (This)->lpVtbl -> Invalidate(This,pRect)

#define IElementBehaviorSiteRender_InvalidateRenderInfo(This)	\
    (This)->lpVtbl -> InvalidateRenderInfo(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteRender_Invalidate_Proxy( 
    IElementBehaviorSiteRender __RPC_FAR * This,
    /* [in] */ LPRECT pRect);


void __RPC_STUB IElementBehaviorSiteRender_Invalidate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteRender_InvalidateRenderInfo_Proxy( 
    IElementBehaviorSiteRender __RPC_FAR * This);


void __RPC_STUB IElementBehaviorSiteRender_InvalidateRenderInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorSiteRender_INTERFACE_DEFINED__ */


#ifndef __ISubDivisionProvider_INTERFACE_DEFINED__
#define __ISubDivisionProvider_INTERFACE_DEFINED__

/* interface ISubDivisionProvider */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISubDivisionProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4d2-98b5-11cf-bb82-00aa00bdce0b")
    ISubDivisionProvider : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSubDivisionCount( 
            /* [out] */ ULONG __RPC_FAR *pcSubDivision) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSubDivisionTabs( 
            /* [out] */ LONG __RPC_FAR *pSubDivisionTabs,
            /* [in] */ LONG cSubDivisions) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SubDivisionFromPt( 
            /* [in] */ POINT pt,
            /* [out] */ LONG __RPC_FAR *piSubDivision) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISubDivisionProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISubDivisionProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISubDivisionProvider __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubDivisionCount )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcSubDivision);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubDivisionTabs )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [out] */ LONG __RPC_FAR *pSubDivisionTabs,
            /* [in] */ LONG cSubDivisions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubDivisionFromPt )( 
            ISubDivisionProvider __RPC_FAR * This,
            /* [in] */ POINT pt,
            /* [out] */ LONG __RPC_FAR *piSubDivision);
        
        END_INTERFACE
    } ISubDivisionProviderVtbl;

    interface ISubDivisionProvider
    {
        CONST_VTBL struct ISubDivisionProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISubDivisionProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISubDivisionProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISubDivisionProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISubDivisionProvider_GetSubDivisionCount(This,pcSubDivision)	\
    (This)->lpVtbl -> GetSubDivisionCount(This,pcSubDivision)

#define ISubDivisionProvider_GetSubDivisionTabs(This,pSubDivisionTabs,cSubDivisions)	\
    (This)->lpVtbl -> GetSubDivisionTabs(This,pSubDivisionTabs,cSubDivisions)

#define ISubDivisionProvider_SubDivisionFromPt(This,pt,piSubDivision)	\
    (This)->lpVtbl -> SubDivisionFromPt(This,pt,piSubDivision)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISubDivisionProvider_GetSubDivisionCount_Proxy( 
    ISubDivisionProvider __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcSubDivision);


void __RPC_STUB ISubDivisionProvider_GetSubDivisionCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISubDivisionProvider_GetSubDivisionTabs_Proxy( 
    ISubDivisionProvider __RPC_FAR * This,
    /* [out] */ LONG __RPC_FAR *pSubDivisionTabs,
    /* [in] */ LONG cSubDivisions);


void __RPC_STUB ISubDivisionProvider_GetSubDivisionTabs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISubDivisionProvider_SubDivisionFromPt_Proxy( 
    ISubDivisionProvider __RPC_FAR * This,
    /* [in] */ POINT pt,
    /* [out] */ LONG __RPC_FAR *piSubDivision);


void __RPC_STUB ISubDivisionProvider_SubDivisionFromPt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISubDivisionProvider_INTERFACE_DEFINED__ */


#ifndef __IElementBehaviorUI_INTERFACE_DEFINED__
#define __IElementBehaviorUI_INTERFACE_DEFINED__

/* interface IElementBehaviorUI */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4bf-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorUI : public IUnknown
    {
    public:
        virtual /* [helpstring] */ void STDMETHODCALLTYPE OnReceiveFocus( 
            /* [in] */ BOOL fFocus,
            /* [in] */ LONG iSubDivision) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSubDivisionProvider( 
            /* [out] */ ISubDivisionProvider __RPC_FAR *__RPC_FAR *pp) = 0;
        
        virtual /* [helpstring] */ BOOL STDMETHODCALLTYPE CanTakeFocus( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorUI __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorUI __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorUI __RPC_FAR * This);
        
        /* [helpstring] */ void ( STDMETHODCALLTYPE __RPC_FAR *OnReceiveFocus )( 
            IElementBehaviorUI __RPC_FAR * This,
            /* [in] */ BOOL fFocus,
            /* [in] */ LONG iSubDivision);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubDivisionProvider )( 
            IElementBehaviorUI __RPC_FAR * This,
            /* [out] */ ISubDivisionProvider __RPC_FAR *__RPC_FAR *pp);
        
        /* [helpstring] */ BOOL ( STDMETHODCALLTYPE __RPC_FAR *CanTakeFocus )( 
            IElementBehaviorUI __RPC_FAR * This);
        
        END_INTERFACE
    } IElementBehaviorUIVtbl;

    interface IElementBehaviorUI
    {
        CONST_VTBL struct IElementBehaviorUIVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorUI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorUI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorUI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorUI_OnReceiveFocus(This,fFocus,iSubDivision)	\
    (This)->lpVtbl -> OnReceiveFocus(This,fFocus,iSubDivision)

#define IElementBehaviorUI_GetSubDivisionProvider(This,pp)	\
    (This)->lpVtbl -> GetSubDivisionProvider(This,pp)

#define IElementBehaviorUI_CanTakeFocus(This)	\
    (This)->lpVtbl -> CanTakeFocus(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ void STDMETHODCALLTYPE IElementBehaviorUI_OnReceiveFocus_Proxy( 
    IElementBehaviorUI __RPC_FAR * This,
    /* [in] */ BOOL fFocus,
    /* [in] */ LONG iSubDivision);


void __RPC_STUB IElementBehaviorUI_OnReceiveFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorUI_GetSubDivisionProvider_Proxy( 
    IElementBehaviorUI __RPC_FAR * This,
    /* [out] */ ISubDivisionProvider __RPC_FAR *__RPC_FAR *pp);


void __RPC_STUB IElementBehaviorUI_GetSubDivisionProvider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ BOOL STDMETHODCALLTYPE IElementBehaviorUI_CanTakeFocus_Proxy( 
    IElementBehaviorUI __RPC_FAR * This);


void __RPC_STUB IElementBehaviorUI_CanTakeFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorUI_INTERFACE_DEFINED__ */


#ifndef __IElementBehaviorCategory_INTERFACE_DEFINED__
#define __IElementBehaviorCategory_INTERFACE_DEFINED__

/* interface IElementBehaviorCategory */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorCategory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4ed-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorCategory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCategory( 
            /* [out] */ LPOLESTR __RPC_FAR *ppchCategory) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorCategoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorCategory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorCategory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorCategory __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCategory )( 
            IElementBehaviorCategory __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *ppchCategory);
        
        END_INTERFACE
    } IElementBehaviorCategoryVtbl;

    interface IElementBehaviorCategory
    {
        CONST_VTBL struct IElementBehaviorCategoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorCategory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorCategory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorCategory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorCategory_GetCategory(This,ppchCategory)	\
    (This)->lpVtbl -> GetCategory(This,ppchCategory)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorCategory_GetCategory_Proxy( 
    IElementBehaviorCategory __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *ppchCategory);


void __RPC_STUB IElementBehaviorCategory_GetCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorCategory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0497 */
/* [local] */ 

#define BEHAVIOR_FIRSTRELATION   0
#define BEHAVIOR_SAMEELEMENT     0
#define BEHAVIOR_PARENT          1
#define BEHAVIOR_CHILD           2
#define BEHAVIOR_SIBLING         3
#define BEHAVIOR_LASTRELATION    3


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0497_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0497_v0_0_s_ifspec;

#ifndef __IElementBehaviorSiteCategory_INTERFACE_DEFINED__
#define __IElementBehaviorSiteCategory_INTERFACE_DEFINED__

/* interface IElementBehaviorSiteCategory */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorSiteCategory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f4ee-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorSiteCategory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRelatedBehaviors( 
            /* [in] */ DWORD dwDirection,
            /* [in] */ LPTSTR pchCategory,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppEnumerator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorSiteCategoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorSiteCategory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorSiteCategory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorSiteCategory __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRelatedBehaviors )( 
            IElementBehaviorSiteCategory __RPC_FAR * This,
            /* [in] */ DWORD dwDirection,
            /* [in] */ LPTSTR pchCategory,
            /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppEnumerator);
        
        END_INTERFACE
    } IElementBehaviorSiteCategoryVtbl;

    interface IElementBehaviorSiteCategory
    {
        CONST_VTBL struct IElementBehaviorSiteCategoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorSiteCategory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorSiteCategory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorSiteCategory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorSiteCategory_GetRelatedBehaviors(This,dwDirection,pchCategory,ppEnumerator)	\
    (This)->lpVtbl -> GetRelatedBehaviors(This,dwDirection,pchCategory,ppEnumerator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorSiteCategory_GetRelatedBehaviors_Proxy( 
    IElementBehaviorSiteCategory __RPC_FAR * This,
    /* [in] */ DWORD dwDirection,
    /* [in] */ LPTSTR pchCategory,
    /* [out] */ IEnumUnknown __RPC_FAR *__RPC_FAR *ppEnumerator);


void __RPC_STUB IElementBehaviorSiteCategory_GetRelatedBehaviors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorSiteCategory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0498 */
/* [local] */ 

#define SID_SElementBehaviorFactory IID_IElementBehaviorFactory


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0498_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0498_v0_0_s_ifspec;

#ifndef __IElementBehaviorFactory_INTERFACE_DEFINED__
#define __IElementBehaviorFactory_INTERFACE_DEFINED__

/* interface IElementBehaviorFactory */
/* [local][unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IElementBehaviorFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3050f429-98b5-11cf-bb82-00aa00bdce0b")
    IElementBehaviorFactory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindBehavior( 
            /* [in] */ LPOLESTR pchNameSpace,
            /* [in] */ LPOLESTR pchBehavior,
            /* [in] */ IUnknown __RPC_FAR *pUnkArg,
            /* [out] */ IElementBehavior __RPC_FAR *__RPC_FAR *ppBehavior) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IElementBehaviorFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IElementBehaviorFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IElementBehaviorFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IElementBehaviorFactory __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindBehavior )( 
            IElementBehaviorFactory __RPC_FAR * This,
            /* [in] */ LPOLESTR pchNameSpace,
            /* [in] */ LPOLESTR pchBehavior,
            /* [in] */ IUnknown __RPC_FAR *pUnkArg,
            /* [out] */ IElementBehavior __RPC_FAR *__RPC_FAR *ppBehavior);
        
        END_INTERFACE
    } IElementBehaviorFactoryVtbl;

    interface IElementBehaviorFactory
    {
        CONST_VTBL struct IElementBehaviorFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IElementBehaviorFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IElementBehaviorFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IElementBehaviorFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IElementBehaviorFactory_FindBehavior(This,pchNameSpace,pchBehavior,pUnkArg,ppBehavior)	\
    (This)->lpVtbl -> FindBehavior(This,pchNameSpace,pchBehavior,pUnkArg,ppBehavior)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IElementBehaviorFactory_FindBehavior_Proxy( 
    IElementBehaviorFactory __RPC_FAR * This,
    /* [in] */ LPOLESTR pchNameSpace,
    /* [in] */ LPOLESTR pchBehavior,
    /* [in] */ IUnknown __RPC_FAR *pUnkArg,
    /* [out] */ IElementBehavior __RPC_FAR *__RPC_FAR *ppBehavior);


void __RPC_STUB IElementBehaviorFactory_FindBehavior_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IElementBehaviorFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0499 */
/* [local] */ 

DEFINE_GUID(SID_SEditCommandTarget,0x3050f4b5,0x98b5,0x11cf,0xbb,0x82,0x00,0xaa,0x00,0xbd,0xce,0x0b);
DEFINE_GUID(CGID_EditStateCommands,0x3050f4b6,0x98b5,0x11cf,0xbb,0x82,0x00,0xaa,0x00,0xbd,0xce,0x0b);
DEFINE_GUID(CGID_DocHostCommandHandler,0xf38bc242,0xb950,0x11d1,0x89,0x18,0x00,0xc0,0x4f,0xc2,0xc8,0x36);


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0499_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0499_v0_0_s_ifspec;

#ifndef __IClassFactory3_INTERFACE_DEFINED__
#define __IClassFactory3_INTERFACE_DEFINED__

/* interface IClassFactory3 */
/* [local][unique][uuid][object] */ 


EXTERN_C const IID IID_IClassFactory3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("342D1EA0-AE25-11D1-89C5-006008C3FBFC")
    IClassFactory3 : public IClassFactory
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateInstanceWithContext( 
            IUnknown __RPC_FAR *punkContext,
            IUnknown __RPC_FAR *punkOuter,
            REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClassFactory3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IClassFactory3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IClassFactory3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IClassFactory3 __RPC_FAR * This);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstance )( 
            IClassFactory3 __RPC_FAR * This,
            /* [unique][in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockServer )( 
            IClassFactory3 __RPC_FAR * This,
            /* [in] */ BOOL fLock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstanceWithContext )( 
            IClassFactory3 __RPC_FAR * This,
            IUnknown __RPC_FAR *punkContext,
            IUnknown __RPC_FAR *punkOuter,
            REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppv);
        
        END_INTERFACE
    } IClassFactory3Vtbl;

    interface IClassFactory3
    {
        CONST_VTBL struct IClassFactory3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClassFactory3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClassFactory3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClassFactory3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClassFactory3_CreateInstance(This,pUnkOuter,riid,ppvObject)	\
    (This)->lpVtbl -> CreateInstance(This,pUnkOuter,riid,ppvObject)

#define IClassFactory3_LockServer(This,fLock)	\
    (This)->lpVtbl -> LockServer(This,fLock)


#define IClassFactory3_CreateInstanceWithContext(This,punkContext,punkOuter,riid,ppv)	\
    (This)->lpVtbl -> CreateInstanceWithContext(This,punkContext,punkOuter,riid,ppv)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IClassFactory3_CreateInstanceWithContext_Proxy( 
    IClassFactory3 __RPC_FAR * This,
    IUnknown __RPC_FAR *punkContext,
    IUnknown __RPC_FAR *punkOuter,
    REFIID riid,
    /* [out] */ void __RPC_FAR *__RPC_FAR *ppv);


void __RPC_STUB IClassFactory3_CreateInstanceWithContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClassFactory3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_mshtmhst_0500 */
/* [local] */ 

#endif


extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0500_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mshtmhst_0500_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

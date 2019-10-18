/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Feb 26 12:23:59 2000
 */
/* Compiler settings for D:\Dev\SnEnCmd\IDlFiles\VSGSEOffice.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __VSGSEOffice_h__
#define __VSGSEOffice_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAccessible_FWD_DEFINED__
#define __IAccessible_FWD_DEFINED__
typedef interface IAccessible IAccessible;
#endif 	/* __IAccessible_FWD_DEFINED__ */


#ifndef ___IMsoDispObj_FWD_DEFINED__
#define ___IMsoDispObj_FWD_DEFINED__
typedef interface _IMsoDispObj _IMsoDispObj;
#endif 	/* ___IMsoDispObj_FWD_DEFINED__ */


#ifndef ___IMsoOleAccDispObj_FWD_DEFINED__
#define ___IMsoOleAccDispObj_FWD_DEFINED__
typedef interface _IMsoOleAccDispObj _IMsoOleAccDispObj;
#endif 	/* ___IMsoOleAccDispObj_FWD_DEFINED__ */


#ifndef __CommandBars_FWD_DEFINED__
#define __CommandBars_FWD_DEFINED__
typedef interface CommandBars CommandBars;
#endif 	/* __CommandBars_FWD_DEFINED__ */


#ifndef __CommandBar_FWD_DEFINED__
#define __CommandBar_FWD_DEFINED__
typedef interface CommandBar CommandBar;
#endif 	/* __CommandBar_FWD_DEFINED__ */


#ifndef __CommandBarControls_FWD_DEFINED__
#define __CommandBarControls_FWD_DEFINED__
typedef interface CommandBarControls CommandBarControls;
#endif 	/* __CommandBarControls_FWD_DEFINED__ */


#ifndef __CommandBarControl_FWD_DEFINED__
#define __CommandBarControl_FWD_DEFINED__
typedef interface CommandBarControl CommandBarControl;
#endif 	/* __CommandBarControl_FWD_DEFINED__ */


#ifndef __CommandBarButton_FWD_DEFINED__
#define __CommandBarButton_FWD_DEFINED__
typedef interface CommandBarButton CommandBarButton;
#endif 	/* __CommandBarButton_FWD_DEFINED__ */


#ifndef __CommandBarPopup_FWD_DEFINED__
#define __CommandBarPopup_FWD_DEFINED__
typedef interface CommandBarPopup CommandBarPopup;
#endif 	/* __CommandBarPopup_FWD_DEFINED__ */


#ifndef __CommandBarComboBox_FWD_DEFINED__
#define __CommandBarComboBox_FWD_DEFINED__
typedef interface CommandBarComboBox CommandBarComboBox;
#endif 	/* __CommandBarComboBox_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Office_LIBRARY_DEFINED__
#define __Office_LIBRARY_DEFINED__

/* library Office */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 











typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0001
    {
	msoBarLeft	= 0,
	msoBarTop	= 1,
	msoBarRight	= 2,
	msoBarBottom	= 3,
	msoBarFloating	= 4,
	msoBarPopup	= 5,
	msoBarMenuBar	= 6
    }	MsoBarPosition;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0002
    {	msoBarNoProtection	= 0,
	msoBarNoCustomize	= 1,
	msoBarNoResize	= 2,
	msoBarNoMove	= 4,
	msoBarNoChangeVisible	= 8,
	msoBarNoChangeDock	= 16,
	msoBarNoVerticalDock	= 32,
	msoBarNoHorizontalDock	= 64
    }	MsoBarProtection;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0003
    {	msoBarTypeNormal	= 0,
	msoBarTypeMenuBar	= 1,
	msoBarTypePopup	= 2
    }	MsoBarType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0004
    {	msoControlCustom	= 0,
	msoControlButton	= 1,
	msoControlEdit	= 2,
	msoControlDropdown	= 3,
	msoControlComboBox	= 4,
	msoControlButtonDropdown	= 5,
	msoControlSplitDropdown	= 6,
	msoControlOCXDropdown	= 7,
	msoControlGenericDropdown	= 8,
	msoControlGraphicDropdown	= 9,
	msoControlPopup	= 10,
	msoControlGraphicPopup	= 11,
	msoControlButtonPopup	= 12,
	msoControlSplitButtonPopup	= 13,
	msoControlSplitButtonMRUPopup	= 14,
	msoControlLabel	= 15,
	msoControlExpandingGrid	= 16,
	msoControlSplitExpandingGrid	= 17,
	msoControlGrid	= 18,
	msoControlGauge	= 19,
	msoControlGraphicCombo	= 20
    }	MsoControlType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0005
    {	msoButtonUp	= 0,
	msoButtonDown	= -1,
	msoButtonMixed	= 2
    }	MsoButtonState;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0006
    {	msoControlOLEUsageNeither	= 0,
	msoControlOLEUsageServer	= 1,
	msoControlOLEUsageClient	= 2,
	msoControlOLEUsageBoth	= 3
    }	MsoControlOLEUsage;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0007
    {	msoButtonAutomatic	= 0,
	msoButtonIcon	= 1,
	msoButtonCaption	= 2,
	msoButtonIconAndCaption	= 3
    }	MsoButtonStyle;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0008
    {	msoComboNormal	= 0,
	msoComboLabel	= 1
    }	MsoComboStyle;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0009
    {	msoOLEMenuGroupNone	= -1,
	msoOLEMenuGroupFile	= 0,
	msoOLEMenuGroupEdit	= 1,
	msoOLEMenuGroupContainer	= 2,
	msoOLEMenuGroupObject	= 3,
	msoOLEMenuGroupWindow	= 4,
	msoOLEMenuGroupHelp	= 5
    }	MsoOLEMenuGroup;

typedef 
enum __MIDL___MIDL_itf_VSGSEOffice_0000_0010
    {	msoMenuAnimationNone	= 0,
	msoMenuAnimationRandom	= 1,
	msoMenuAnimationUnfold	= 2,
	msoMenuAnimationSlide	= 3
    }	MsoMenuAnimation;


DEFINE_GUID(LIBID_Office,0x2DF8D04C,0x5BFA,0x101B,0xBD,0xE5,0x00,0xAA,0x00,0x44,0xDE,0x52);

#ifndef __IAccessible_INTERFACE_DEFINED__
#define __IAccessible_INTERFACE_DEFINED__

/* interface IAccessible */
/* [object][oleautomation][dual][hidden][uuid] */ 


DEFINE_GUID(IID_IAccessible,0x618736E0,0x3C3D,0x11CF,0x81,0x0C,0x00,0xAA,0x00,0x38,0x9B,0x71);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("618736E0-3C3D-11CF-810C-00AA00389B71")
    IAccessible : public IDispatch
    {
    public:
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accParent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accChildCount( 
            /* [retval][out] */ long __RPC_FAR *pcountChildren) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accChild( 
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accName( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accValue( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accDescription( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accRole( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accState( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accHelp( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accHelpTopic( 
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accKeyboardShortcut( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accFocus( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accSelection( 
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_accDefaultAction( 
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE accSelect( 
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE accLocation( 
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE accNavigate( 
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE accHitTest( 
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE accDoDefaultAction( 
            /* [optional][in] */ VARIANT varChild) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_accName( 
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_accValue( 
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAccessibleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAccessible __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAccessible __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAccessible __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            IAccessible __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            IAccessible __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            IAccessible __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            IAccessible __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            IAccessible __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            IAccessible __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            IAccessible __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            IAccessible __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        END_INTERFACE
    } IAccessibleVtbl;

    interface IAccessible
    {
        CONST_VTBL struct IAccessibleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAccessible_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAccessible_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAccessible_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAccessible_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAccessible_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAccessible_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAccessible_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAccessible_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define IAccessible_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define IAccessible_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define IAccessible_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define IAccessible_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define IAccessible_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define IAccessible_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define IAccessible_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define IAccessible_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define IAccessible_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define IAccessible_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define IAccessible_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define IAccessible_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define IAccessible_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define IAccessible_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define IAccessible_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define IAccessible_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define IAccessible_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define IAccessible_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define IAccessible_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define IAccessible_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accParent_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);


void __RPC_STUB IAccessible_get_accParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accChildCount_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pcountChildren);


void __RPC_STUB IAccessible_get_accChildCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accChild_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [in] */ VARIANT varChild,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);


void __RPC_STUB IAccessible_get_accChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accName_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ BSTR __RPC_FAR *pszName);


void __RPC_STUB IAccessible_get_accName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accValue_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ BSTR __RPC_FAR *pszValue);


void __RPC_STUB IAccessible_get_accValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accDescription_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ BSTR __RPC_FAR *pszDescription);


void __RPC_STUB IAccessible_get_accDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accRole_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);


void __RPC_STUB IAccessible_get_accRole_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accState_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarState);


void __RPC_STUB IAccessible_get_accState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accHelp_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ BSTR __RPC_FAR *pszHelp);


void __RPC_STUB IAccessible_get_accHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accHelpTopic_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pszHelpFile,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ long __RPC_FAR *pidTopic);


void __RPC_STUB IAccessible_get_accHelpTopic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accKeyboardShortcut_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);


void __RPC_STUB IAccessible_get_accKeyboardShortcut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accFocus_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);


void __RPC_STUB IAccessible_get_accFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accSelection_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);


void __RPC_STUB IAccessible_get_accSelection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAccessible_get_accDefaultAction_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);


void __RPC_STUB IAccessible_get_accDefaultAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IAccessible_accSelect_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [in] */ long flagsSelect,
    /* [optional][in] */ VARIANT varChild);


void __RPC_STUB IAccessible_accSelect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IAccessible_accLocation_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pxLeft,
    /* [out] */ long __RPC_FAR *pyTop,
    /* [out] */ long __RPC_FAR *pcxWidth,
    /* [out] */ long __RPC_FAR *pcyHeight,
    /* [optional][in] */ VARIANT varChild);


void __RPC_STUB IAccessible_accLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IAccessible_accNavigate_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [in] */ long navDir,
    /* [optional][in] */ VARIANT varStart,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);


void __RPC_STUB IAccessible_accNavigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IAccessible_accHitTest_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [in] */ long xLeft,
    /* [in] */ long yTop,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);


void __RPC_STUB IAccessible_accHitTest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE IAccessible_accDoDefaultAction_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild);


void __RPC_STUB IAccessible_accDoDefaultAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE IAccessible_put_accName_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [in] */ BSTR pszName);


void __RPC_STUB IAccessible_put_accName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE IAccessible_put_accValue_Proxy( 
    IAccessible __RPC_FAR * This,
    /* [optional][in] */ VARIANT varChild,
    /* [in] */ BSTR pszValue);


void __RPC_STUB IAccessible_put_accValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAccessible_INTERFACE_DEFINED__ */


#ifndef ___IMsoDispObj_INTERFACE_DEFINED__
#define ___IMsoDispObj_INTERFACE_DEFINED__

/* interface _IMsoDispObj */
/* [object][oleautomation][nonextensible][dual][hidden][uuid] */ 


DEFINE_GUID(IID__IMsoDispObj,0x000C0300,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C0300-0000-0000-C000-000000000046")
    _IMsoDispObj : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Creator( 
            /* [retval][out] */ long __RPC_FAR *plCreator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _IMsoDispObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IMsoDispObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IMsoDispObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            _IMsoDispObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        END_INTERFACE
    } _IMsoDispObjVtbl;

    interface _IMsoDispObj
    {
        CONST_VTBL struct _IMsoDispObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMsoDispObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMsoDispObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMsoDispObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMsoDispObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMsoDispObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMsoDispObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMsoDispObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _IMsoDispObj_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define _IMsoDispObj_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _IMsoDispObj_get_Application_Proxy( 
    _IMsoDispObj __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);


void __RPC_STUB _IMsoDispObj_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _IMsoDispObj_get_Creator_Proxy( 
    _IMsoDispObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCreator);


void __RPC_STUB _IMsoDispObj_get_Creator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___IMsoDispObj_INTERFACE_DEFINED__ */


#ifndef ___IMsoOleAccDispObj_INTERFACE_DEFINED__
#define ___IMsoOleAccDispObj_INTERFACE_DEFINED__

/* interface _IMsoOleAccDispObj */
/* [object][oleautomation][nonextensible][dual][hidden][uuid] */ 


DEFINE_GUID(IID__IMsoOleAccDispObj,0x000C0301,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C0301-0000-0000-C000-000000000046")
    _IMsoOleAccDispObj : public IAccessible
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Creator( 
            /* [retval][out] */ long __RPC_FAR *plCreator) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _IMsoOleAccDispObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IMsoOleAccDispObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IMsoOleAccDispObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            _IMsoOleAccDispObj __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        END_INTERFACE
    } _IMsoOleAccDispObjVtbl;

    interface _IMsoOleAccDispObj
    {
        CONST_VTBL struct _IMsoOleAccDispObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMsoOleAccDispObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMsoOleAccDispObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMsoOleAccDispObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMsoOleAccDispObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMsoOleAccDispObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMsoOleAccDispObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMsoOleAccDispObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _IMsoOleAccDispObj_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define _IMsoOleAccDispObj_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define _IMsoOleAccDispObj_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define _IMsoOleAccDispObj_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define _IMsoOleAccDispObj_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define _IMsoOleAccDispObj_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define _IMsoOleAccDispObj_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define _IMsoOleAccDispObj_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define _IMsoOleAccDispObj_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define _IMsoOleAccDispObj_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define _IMsoOleAccDispObj_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define _IMsoOleAccDispObj_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define _IMsoOleAccDispObj_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define _IMsoOleAccDispObj_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define _IMsoOleAccDispObj_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define _IMsoOleAccDispObj_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define _IMsoOleAccDispObj_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define _IMsoOleAccDispObj_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define _IMsoOleAccDispObj_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define _IMsoOleAccDispObj_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define _IMsoOleAccDispObj_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)


#define _IMsoOleAccDispObj_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define _IMsoOleAccDispObj_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _IMsoOleAccDispObj_get_Application_Proxy( 
    _IMsoOleAccDispObj __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);


void __RPC_STUB _IMsoOleAccDispObj_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _IMsoOleAccDispObj_get_Creator_Proxy( 
    _IMsoOleAccDispObj __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCreator);


void __RPC_STUB _IMsoOleAccDispObj_get_Creator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___IMsoOleAccDispObj_INTERFACE_DEFINED__ */


#ifndef __CommandBars_INTERFACE_DEFINED__
#define __CommandBars_INTERFACE_DEFINED__

/* interface CommandBars */
/* [object][oleautomation][nonextensible][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBars,0x000C0302,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C0302-0000-0000-C000-000000000046")
    CommandBars : public _IMsoDispObj
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActionControl( 
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ActiveMenuBar( 
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [optional][in] */ VARIANT Name,
            /* [optional][in] */ VARIANT Position,
            /* [optional][in] */ VARIANT MenuBar,
            /* [optional][in] */ VARIANT Temporary,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ int __RPC_FAR *pcToolbars) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayTooltips( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfDisplayTooltips) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DisplayTooltips( 
            /* [in] */ VARIANT_BOOL pvarfDisplayTooltips) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayKeysInTooltips( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfDisplayKeys) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DisplayKeysInTooltips( 
            /* [in] */ VARIANT_BOOL pvarfDisplayKeys) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE FindControl( 
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Id,
            /* [optional][in] */ VARIANT Tag,
            /* [optional][in] */ VARIANT Visible,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_LargeButtons( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfLargeButtons) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_LargeButtons( 
            /* [in] */ VARIANT_BOOL pvarfLargeButtons) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_MenuAnimationStyle( 
            /* [retval][out] */ MsoMenuAnimation __RPC_FAR *pma) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_MenuAnimationStyle( 
            /* [in] */ MsoMenuAnimation pma) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppienum) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ReleaseFocus( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBars __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBars __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBars __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActionControl )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ActiveMenuBar )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            CommandBars __RPC_FAR * This,
            /* [optional][in] */ VARIANT Name,
            /* [optional][in] */ VARIANT Position,
            /* [optional][in] */ VARIANT MenuBar,
            /* [optional][in] */ VARIANT Temporary,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pcToolbars);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayTooltips )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfDisplayTooltips);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayTooltips )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfDisplayTooltips);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayKeysInTooltips )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfDisplayKeys);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayKeysInTooltips )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfDisplayKeys);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindControl )( 
            CommandBars __RPC_FAR * This,
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Id,
            /* [optional][in] */ VARIANT Tag,
            /* [optional][in] */ VARIANT Visible,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LargeButtons )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfLargeButtons);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LargeButtons )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfLargeButtons);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MenuAnimationStyle )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ MsoMenuAnimation __RPC_FAR *pma);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MenuAnimationStyle )( 
            CommandBars __RPC_FAR * This,
            /* [in] */ MsoMenuAnimation pma);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppienum);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBars __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseFocus )( 
            CommandBars __RPC_FAR * This);
        
        END_INTERFACE
    } CommandBarsVtbl;

    interface CommandBars
    {
        CONST_VTBL struct CommandBarsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBars_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBars_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBars_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBars_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBars_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBars_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBars_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBars_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBars_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBars_get_ActionControl(This,ppcbc)	\
    (This)->lpVtbl -> get_ActionControl(This,ppcbc)

#define CommandBars_get_ActiveMenuBar(This,ppcb)	\
    (This)->lpVtbl -> get_ActiveMenuBar(This,ppcb)

#define CommandBars_Add(This,Name,Position,MenuBar,Temporary,ppcb)	\
    (This)->lpVtbl -> Add(This,Name,Position,MenuBar,Temporary,ppcb)

#define CommandBars_get_Count(This,pcToolbars)	\
    (This)->lpVtbl -> get_Count(This,pcToolbars)

#define CommandBars_get_DisplayTooltips(This,pvarfDisplayTooltips)	\
    (This)->lpVtbl -> get_DisplayTooltips(This,pvarfDisplayTooltips)

#define CommandBars_put_DisplayTooltips(This,pvarfDisplayTooltips)	\
    (This)->lpVtbl -> put_DisplayTooltips(This,pvarfDisplayTooltips)

#define CommandBars_get_DisplayKeysInTooltips(This,pvarfDisplayKeys)	\
    (This)->lpVtbl -> get_DisplayKeysInTooltips(This,pvarfDisplayKeys)

#define CommandBars_put_DisplayKeysInTooltips(This,pvarfDisplayKeys)	\
    (This)->lpVtbl -> put_DisplayKeysInTooltips(This,pvarfDisplayKeys)

#define CommandBars_FindControl(This,Type,Id,Tag,Visible,ppcbc)	\
    (This)->lpVtbl -> FindControl(This,Type,Id,Tag,Visible,ppcbc)

#define CommandBars_get_Item(This,Index,ppcb)	\
    (This)->lpVtbl -> get_Item(This,Index,ppcb)

#define CommandBars_get_LargeButtons(This,pvarfLargeButtons)	\
    (This)->lpVtbl -> get_LargeButtons(This,pvarfLargeButtons)

#define CommandBars_put_LargeButtons(This,pvarfLargeButtons)	\
    (This)->lpVtbl -> put_LargeButtons(This,pvarfLargeButtons)

#define CommandBars_get_MenuAnimationStyle(This,pma)	\
    (This)->lpVtbl -> get_MenuAnimationStyle(This,pma)

#define CommandBars_put_MenuAnimationStyle(This,pma)	\
    (This)->lpVtbl -> put_MenuAnimationStyle(This,pma)

#define CommandBars_get__NewEnum(This,ppienum)	\
    (This)->lpVtbl -> get__NewEnum(This,ppienum)

#define CommandBars_get_Parent(This,ppidisp)	\
    (This)->lpVtbl -> get_Parent(This,ppidisp)

#define CommandBars_ReleaseFocus(This)	\
    (This)->lpVtbl -> ReleaseFocus(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_ActionControl_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBars_get_ActionControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_ActiveMenuBar_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);


void __RPC_STUB CommandBars_get_ActiveMenuBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBars_Add_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [optional][in] */ VARIANT Name,
    /* [optional][in] */ VARIANT Position,
    /* [optional][in] */ VARIANT MenuBar,
    /* [optional][in] */ VARIANT Temporary,
    /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);


void __RPC_STUB CommandBars_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_Count_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pcToolbars);


void __RPC_STUB CommandBars_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_DisplayTooltips_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfDisplayTooltips);


void __RPC_STUB CommandBars_get_DisplayTooltips_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBars_put_DisplayTooltips_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfDisplayTooltips);


void __RPC_STUB CommandBars_put_DisplayTooltips_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_DisplayKeysInTooltips_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfDisplayKeys);


void __RPC_STUB CommandBars_get_DisplayKeysInTooltips_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBars_put_DisplayKeysInTooltips_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfDisplayKeys);


void __RPC_STUB CommandBars_put_DisplayKeysInTooltips_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBars_FindControl_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [optional][in] */ VARIANT Type,
    /* [optional][in] */ VARIANT Id,
    /* [optional][in] */ VARIANT Tag,
    /* [optional][in] */ VARIANT Visible,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBars_FindControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_Item_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);


void __RPC_STUB CommandBars_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_LargeButtons_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfLargeButtons);


void __RPC_STUB CommandBars_get_LargeButtons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBars_put_LargeButtons_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfLargeButtons);


void __RPC_STUB CommandBars_put_LargeButtons_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_MenuAnimationStyle_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ MsoMenuAnimation __RPC_FAR *pma);


void __RPC_STUB CommandBars_get_MenuAnimationStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBars_put_MenuAnimationStyle_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [in] */ MsoMenuAnimation pma);


void __RPC_STUB CommandBars_put_MenuAnimationStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get__NewEnum_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppienum);


void __RPC_STUB CommandBars_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBars_get_Parent_Proxy( 
    CommandBars __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);


void __RPC_STUB CommandBars_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBars_ReleaseFocus_Proxy( 
    CommandBars __RPC_FAR * This);


void __RPC_STUB CommandBars_ReleaseFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBars_INTERFACE_DEFINED__ */


#ifndef __CommandBar_INTERFACE_DEFINED__
#define __CommandBar_INTERFACE_DEFINED__

/* interface CommandBar */
/* [object][oleautomation][nonextensible][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBar,0x000C0304,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C0304-0000-0000-C000-000000000046")
    CommandBar : public _IMsoOleAccDispObj
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_BuiltIn( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Context( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContext) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Context( 
            /* [in] */ BSTR pbstrContext) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Controls( 
            /* [retval][out] */ CommandBarControls __RPC_FAR *__RPC_FAR *ppcbcs) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL pvarfEnabled) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE FindControl( 
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Id,
            /* [optional][in] */ VARIANT Tag,
            /* [optional][in] */ VARIANT Visible,
            /* [optional][in] */ VARIANT Recursive,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ int __RPC_FAR *pdy) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ int pdy) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ int __RPC_FAR *pi) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_InstanceId( 
            /* [retval][out] */ long __RPC_FAR *pid) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ int __RPC_FAR *pxpLeft) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ int pxpLeft) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR pbstrName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_NameLocal( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNameLocal) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_NameLocal( 
            /* [in] */ BSTR pbstrNameLocal) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ MsoBarPosition __RPC_FAR *ppos) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ MsoBarPosition ppos) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_RowIndex( 
            /* [retval][out] */ int __RPC_FAR *piRow) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_RowIndex( 
            /* [in] */ int piRow) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Protection( 
            /* [retval][out] */ MsoBarProtection __RPC_FAR *pprot) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Protection( 
            /* [in] */ MsoBarProtection pprot) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ShowPopup( 
            /* [optional][in] */ VARIANT x,
            /* [optional][in] */ VARIANT y) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ int __RPC_FAR *pypTop) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ int pypTop) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ MsoBarType __RPC_FAR *ptype) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL pvarfVisible) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int __RPC_FAR *pdx) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int pdx) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBar __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBar __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBar __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            CommandBar __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            CommandBar __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuiltIn )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Context )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContext);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Context )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ BSTR pbstrContext);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Controls )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ CommandBarControls __RPC_FAR *__RPC_FAR *ppcbcs);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            CommandBar __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfEnabled);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindControl )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Id,
            /* [optional][in] */ VARIANT Tag,
            /* [optional][in] */ VARIANT Visible,
            /* [optional][in] */ VARIANT Recursive,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdy);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ int pdy);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pi);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InstanceId )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pxpLeft);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ int pxpLeft);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NameLocal )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrNameLocal);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NameLocal )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ BSTR pbstrNameLocal);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ MsoBarPosition __RPC_FAR *ppos);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ MsoBarPosition ppos);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RowIndex )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piRow);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RowIndex )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ int piRow);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Protection )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ MsoBarProtection __RPC_FAR *pprot);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Protection )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ MsoBarProtection pprot);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            CommandBar __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowPopup )( 
            CommandBar __RPC_FAR * This,
            /* [optional][in] */ VARIANT x,
            /* [optional][in] */ VARIANT y);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pypTop);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ int pypTop);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ MsoBarType __RPC_FAR *ptype);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfVisible);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            CommandBar __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdx);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            CommandBar __RPC_FAR * This,
            /* [in] */ int pdx);
        
        END_INTERFACE
    } CommandBarVtbl;

    interface CommandBar
    {
        CONST_VTBL struct CommandBarVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBar_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBar_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBar_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBar_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBar_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBar_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBar_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBar_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define CommandBar_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define CommandBar_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define CommandBar_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define CommandBar_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define CommandBar_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define CommandBar_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define CommandBar_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define CommandBar_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define CommandBar_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define CommandBar_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define CommandBar_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define CommandBar_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define CommandBar_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define CommandBar_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define CommandBar_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define CommandBar_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define CommandBar_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define CommandBar_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define CommandBar_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define CommandBar_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)


#define CommandBar_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBar_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBar_get_BuiltIn(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> get_BuiltIn(This,pvarfBuiltIn)

#define CommandBar_get_Context(This,pbstrContext)	\
    (This)->lpVtbl -> get_Context(This,pbstrContext)

#define CommandBar_put_Context(This,pbstrContext)	\
    (This)->lpVtbl -> put_Context(This,pbstrContext)

#define CommandBar_get_Controls(This,ppcbcs)	\
    (This)->lpVtbl -> get_Controls(This,ppcbcs)

#define CommandBar_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define CommandBar_get_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,pvarfEnabled)

#define CommandBar_put_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> put_Enabled(This,pvarfEnabled)

#define CommandBar_FindControl(This,Type,Id,Tag,Visible,Recursive,ppcbc)	\
    (This)->lpVtbl -> FindControl(This,Type,Id,Tag,Visible,Recursive,ppcbc)

#define CommandBar_get_Height(This,pdy)	\
    (This)->lpVtbl -> get_Height(This,pdy)

#define CommandBar_put_Height(This,pdy)	\
    (This)->lpVtbl -> put_Height(This,pdy)

#define CommandBar_get_Index(This,pi)	\
    (This)->lpVtbl -> get_Index(This,pi)

#define CommandBar_get_InstanceId(This,pid)	\
    (This)->lpVtbl -> get_InstanceId(This,pid)

#define CommandBar_get_Left(This,pxpLeft)	\
    (This)->lpVtbl -> get_Left(This,pxpLeft)

#define CommandBar_put_Left(This,pxpLeft)	\
    (This)->lpVtbl -> put_Left(This,pxpLeft)

#define CommandBar_get_Name(This,pbstrName)	\
    (This)->lpVtbl -> get_Name(This,pbstrName)

#define CommandBar_put_Name(This,pbstrName)	\
    (This)->lpVtbl -> put_Name(This,pbstrName)

#define CommandBar_get_NameLocal(This,pbstrNameLocal)	\
    (This)->lpVtbl -> get_NameLocal(This,pbstrNameLocal)

#define CommandBar_put_NameLocal(This,pbstrNameLocal)	\
    (This)->lpVtbl -> put_NameLocal(This,pbstrNameLocal)

#define CommandBar_get_Parent(This,ppidisp)	\
    (This)->lpVtbl -> get_Parent(This,ppidisp)

#define CommandBar_get_Position(This,ppos)	\
    (This)->lpVtbl -> get_Position(This,ppos)

#define CommandBar_put_Position(This,ppos)	\
    (This)->lpVtbl -> put_Position(This,ppos)

#define CommandBar_get_RowIndex(This,piRow)	\
    (This)->lpVtbl -> get_RowIndex(This,piRow)

#define CommandBar_put_RowIndex(This,piRow)	\
    (This)->lpVtbl -> put_RowIndex(This,piRow)

#define CommandBar_get_Protection(This,pprot)	\
    (This)->lpVtbl -> get_Protection(This,pprot)

#define CommandBar_put_Protection(This,pprot)	\
    (This)->lpVtbl -> put_Protection(This,pprot)

#define CommandBar_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define CommandBar_ShowPopup(This,x,y)	\
    (This)->lpVtbl -> ShowPopup(This,x,y)

#define CommandBar_get_Top(This,pypTop)	\
    (This)->lpVtbl -> get_Top(This,pypTop)

#define CommandBar_put_Top(This,pypTop)	\
    (This)->lpVtbl -> put_Top(This,pypTop)

#define CommandBar_get_Type(This,ptype)	\
    (This)->lpVtbl -> get_Type(This,ptype)

#define CommandBar_get_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> get_Visible(This,pvarfVisible)

#define CommandBar_put_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> put_Visible(This,pvarfVisible)

#define CommandBar_get_Width(This,pdx)	\
    (This)->lpVtbl -> get_Width(This,pdx)

#define CommandBar_put_Width(This,pdx)	\
    (This)->lpVtbl -> put_Width(This,pdx)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_BuiltIn_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);


void __RPC_STUB CommandBar_get_BuiltIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Context_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrContext);


void __RPC_STUB CommandBar_get_Context_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Context_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ BSTR pbstrContext);


void __RPC_STUB CommandBar_put_Context_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Controls_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ CommandBarControls __RPC_FAR *__RPC_FAR *ppcbcs);


void __RPC_STUB CommandBar_get_Controls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBar_Delete_Proxy( 
    CommandBar __RPC_FAR * This);


void __RPC_STUB CommandBar_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Enabled_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);


void __RPC_STUB CommandBar_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Enabled_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfEnabled);


void __RPC_STUB CommandBar_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBar_FindControl_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [optional][in] */ VARIANT Type,
    /* [optional][in] */ VARIANT Id,
    /* [optional][in] */ VARIANT Tag,
    /* [optional][in] */ VARIANT Visible,
    /* [optional][in] */ VARIANT Recursive,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBar_FindControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Height_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pdy);


void __RPC_STUB CommandBar_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Height_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ int pdy);


void __RPC_STUB CommandBar_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Index_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pi);


void __RPC_STUB CommandBar_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_InstanceId_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pid);


void __RPC_STUB CommandBar_get_InstanceId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Left_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pxpLeft);


void __RPC_STUB CommandBar_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Left_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ int pxpLeft);


void __RPC_STUB CommandBar_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Name_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB CommandBar_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Name_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ BSTR pbstrName);


void __RPC_STUB CommandBar_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_NameLocal_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrNameLocal);


void __RPC_STUB CommandBar_get_NameLocal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_NameLocal_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ BSTR pbstrNameLocal);


void __RPC_STUB CommandBar_put_NameLocal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Parent_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);


void __RPC_STUB CommandBar_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Position_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ MsoBarPosition __RPC_FAR *ppos);


void __RPC_STUB CommandBar_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Position_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ MsoBarPosition ppos);


void __RPC_STUB CommandBar_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_RowIndex_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piRow);


void __RPC_STUB CommandBar_get_RowIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_RowIndex_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ int piRow);


void __RPC_STUB CommandBar_put_RowIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Protection_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ MsoBarProtection __RPC_FAR *pprot);


void __RPC_STUB CommandBar_get_Protection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Protection_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ MsoBarProtection pprot);


void __RPC_STUB CommandBar_put_Protection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBar_Reset_Proxy( 
    CommandBar __RPC_FAR * This);


void __RPC_STUB CommandBar_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBar_ShowPopup_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [optional][in] */ VARIANT x,
    /* [optional][in] */ VARIANT y);


void __RPC_STUB CommandBar_ShowPopup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Top_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pypTop);


void __RPC_STUB CommandBar_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Top_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ int pypTop);


void __RPC_STUB CommandBar_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Type_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ MsoBarType __RPC_FAR *ptype);


void __RPC_STUB CommandBar_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Visible_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);


void __RPC_STUB CommandBar_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Visible_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfVisible);


void __RPC_STUB CommandBar_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBar_get_Width_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pdx);


void __RPC_STUB CommandBar_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBar_put_Width_Proxy( 
    CommandBar __RPC_FAR * This,
    /* [in] */ int pdx);


void __RPC_STUB CommandBar_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBar_INTERFACE_DEFINED__ */


#ifndef __CommandBarControls_INTERFACE_DEFINED__
#define __CommandBarControls_INTERFACE_DEFINED__

/* interface CommandBarControls */
/* [object][oleautomation][nonextensible][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBarControls,0x000C0306,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C0306-0000-0000-C000-000000000046")
    CommandBarControls : public _IMsoDispObj
    {
    public:
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Id,
            /* [optional][in] */ VARIANT Parameter,
            /* [optional][in] */ VARIANT Before,
            /* [optional][in] */ VARIANT Temporary,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ int __RPC_FAR *pcToolbarControls) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppienum) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBarControls __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBarControls __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBarControls __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBarControls __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBarControls __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBarControls __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBarControls __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBarControls __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBarControls __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            CommandBarControls __RPC_FAR * This,
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Id,
            /* [optional][in] */ VARIANT Parameter,
            /* [optional][in] */ VARIANT Before,
            /* [optional][in] */ VARIANT Temporary,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            CommandBarControls __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pcToolbarControls);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            CommandBarControls __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            CommandBarControls __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppienum);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBarControls __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        END_INTERFACE
    } CommandBarControlsVtbl;

    interface CommandBarControls
    {
        CONST_VTBL struct CommandBarControlsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBarControls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBarControls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBarControls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBarControls_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBarControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBarControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBarControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBarControls_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBarControls_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBarControls_Add(This,Type,Id,Parameter,Before,Temporary,ppcbc)	\
    (This)->lpVtbl -> Add(This,Type,Id,Parameter,Before,Temporary,ppcbc)

#define CommandBarControls_get_Count(This,pcToolbarControls)	\
    (This)->lpVtbl -> get_Count(This,pcToolbarControls)

#define CommandBarControls_get_Item(This,Index,ppcbc)	\
    (This)->lpVtbl -> get_Item(This,Index,ppcbc)

#define CommandBarControls_get__NewEnum(This,ppienum)	\
    (This)->lpVtbl -> get__NewEnum(This,ppienum)

#define CommandBarControls_get_Parent(This,ppcb)	\
    (This)->lpVtbl -> get_Parent(This,ppcb)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControls_Add_Proxy( 
    CommandBarControls __RPC_FAR * This,
    /* [optional][in] */ VARIANT Type,
    /* [optional][in] */ VARIANT Id,
    /* [optional][in] */ VARIANT Parameter,
    /* [optional][in] */ VARIANT Before,
    /* [optional][in] */ VARIANT Temporary,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBarControls_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControls_get_Count_Proxy( 
    CommandBarControls __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pcToolbarControls);


void __RPC_STUB CommandBarControls_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControls_get_Item_Proxy( 
    CommandBarControls __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBarControls_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControls_get__NewEnum_Proxy( 
    CommandBarControls __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppienum);


void __RPC_STUB CommandBarControls_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControls_get_Parent_Proxy( 
    CommandBarControls __RPC_FAR * This,
    /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);


void __RPC_STUB CommandBarControls_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBarControls_INTERFACE_DEFINED__ */


#ifndef __CommandBarControl_INTERFACE_DEFINED__
#define __CommandBarControl_INTERFACE_DEFINED__

/* interface CommandBarControl */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBarControl,0x000C0308,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C0308-0000-0000-C000-000000000046")
    CommandBarControl : public _IMsoOleAccDispObj
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_BeginGroup( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBeginGroup) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_BeginGroup( 
            /* [in] */ VARIANT_BOOL pvarfBeginGroup) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_BuiltIn( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCaption) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR pbstrCaption) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_Control( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [optional][in] */ VARIANT Temporary) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DescriptionText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DescriptionText( 
            /* [in] */ BSTR pbstrText) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL pvarfEnabled) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Execute( void) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ int __RPC_FAR *pdy) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ int pdy) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_HelpContextId( 
            /* [retval][out] */ int __RPC_FAR *pid) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_HelpContextId( 
            /* [in] */ int pid) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_HelpFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_HelpFile( 
            /* [in] */ BSTR pbstrFilename) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Id( 
            /* [retval][out] */ int __RPC_FAR *pid) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ int __RPC_FAR *pi) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_InstanceId( 
            /* [retval][out] */ long __RPC_FAR *pid) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ int __RPC_FAR *px) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OLEUsage( 
            /* [retval][out] */ MsoControlOLEUsage __RPC_FAR *pcou) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_OLEUsage( 
            /* [in] */ MsoControlOLEUsage pcou) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OnAction( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOnAction) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_OnAction( 
            /* [in] */ BSTR pbstrOnAction) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parameter( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrParam) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Parameter( 
            /* [in] */ BSTR pbstrParam) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Priority( 
            /* [retval][out] */ int __RPC_FAR *pnPri) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Priority( 
            /* [in] */ int pnPri) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetFocus( void) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Tag( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTag) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Tag( 
            /* [in] */ BSTR pbstrTag) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_TooltipText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTooltip) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_TooltipText( 
            /* [in] */ BSTR pbstrTooltip) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ int __RPC_FAR *py) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ MsoControlType __RPC_FAR *ptype) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL pvarfVisible) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ int __RPC_FAR *pdx) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ int pdx) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved1( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved2( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved3( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved4( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved5( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved6( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved7( void) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE Reserved8( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBarControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBarControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBarControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            CommandBarControl __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            CommandBarControl __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BeginGroup )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBeginGroup);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BeginGroup )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfBeginGroup);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuiltIn )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCaption);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrCaption);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT Temporary);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DescriptionText )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DescriptionText )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfEnabled);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdy);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ int pdy);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContextId )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpContextId )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ int pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFile )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrFilename);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Id )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pi);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InstanceId )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pid);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            CommandBarControl __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *px);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OLEUsage )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ MsoControlOLEUsage __RPC_FAR *pcou);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OLEUsage )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ MsoControlOLEUsage pcou);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OnAction )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOnAction);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OnAction )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrOnAction);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parameter )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrParam);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parameter )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrParam);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnPri);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ int pnPri);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFocus )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTag);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrTag);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TooltipText )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTooltip);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TooltipText )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ BSTR pbstrTooltip);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *py);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ MsoControlType __RPC_FAR *ptype);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfVisible);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            CommandBarControl __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdx);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            CommandBarControl __RPC_FAR * This,
            /* [in] */ int pdx);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved1 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved2 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved3 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved4 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved5 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved6 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved7 )( 
            CommandBarControl __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved8 )( 
            CommandBarControl __RPC_FAR * This);
        
        END_INTERFACE
    } CommandBarControlVtbl;

    interface CommandBarControl
    {
        CONST_VTBL struct CommandBarControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBarControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBarControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBarControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBarControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBarControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBarControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBarControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBarControl_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define CommandBarControl_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define CommandBarControl_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define CommandBarControl_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define CommandBarControl_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define CommandBarControl_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define CommandBarControl_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define CommandBarControl_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define CommandBarControl_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define CommandBarControl_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define CommandBarControl_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define CommandBarControl_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define CommandBarControl_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define CommandBarControl_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define CommandBarControl_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define CommandBarControl_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define CommandBarControl_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define CommandBarControl_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define CommandBarControl_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define CommandBarControl_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define CommandBarControl_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)


#define CommandBarControl_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBarControl_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBarControl_get_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> get_BeginGroup(This,pvarfBeginGroup)

#define CommandBarControl_put_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> put_BeginGroup(This,pvarfBeginGroup)

#define CommandBarControl_get_BuiltIn(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> get_BuiltIn(This,pvarfBuiltIn)

#define CommandBarControl_get_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pbstrCaption)

#define CommandBarControl_put_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> put_Caption(This,pbstrCaption)

#define CommandBarControl_get_Control(This,ppidisp)	\
    (This)->lpVtbl -> get_Control(This,ppidisp)

#define CommandBarControl_Copy(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Copy(This,Bar,Before,ppcbc)

#define CommandBarControl_Delete(This,Temporary)	\
    (This)->lpVtbl -> Delete(This,Temporary)

#define CommandBarControl_get_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> get_DescriptionText(This,pbstrText)

#define CommandBarControl_put_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> put_DescriptionText(This,pbstrText)

#define CommandBarControl_get_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,pvarfEnabled)

#define CommandBarControl_put_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> put_Enabled(This,pvarfEnabled)

#define CommandBarControl_Execute(This)	\
    (This)->lpVtbl -> Execute(This)

#define CommandBarControl_get_Height(This,pdy)	\
    (This)->lpVtbl -> get_Height(This,pdy)

#define CommandBarControl_put_Height(This,pdy)	\
    (This)->lpVtbl -> put_Height(This,pdy)

#define CommandBarControl_get_HelpContextId(This,pid)	\
    (This)->lpVtbl -> get_HelpContextId(This,pid)

#define CommandBarControl_put_HelpContextId(This,pid)	\
    (This)->lpVtbl -> put_HelpContextId(This,pid)

#define CommandBarControl_get_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> get_HelpFile(This,pbstrFilename)

#define CommandBarControl_put_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> put_HelpFile(This,pbstrFilename)

#define CommandBarControl_get_Id(This,pid)	\
    (This)->lpVtbl -> get_Id(This,pid)

#define CommandBarControl_get_Index(This,pi)	\
    (This)->lpVtbl -> get_Index(This,pi)

#define CommandBarControl_get_InstanceId(This,pid)	\
    (This)->lpVtbl -> get_InstanceId(This,pid)

#define CommandBarControl_Move(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Move(This,Bar,Before,ppcbc)

#define CommandBarControl_get_Left(This,px)	\
    (This)->lpVtbl -> get_Left(This,px)

#define CommandBarControl_get_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> get_OLEUsage(This,pcou)

#define CommandBarControl_put_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> put_OLEUsage(This,pcou)

#define CommandBarControl_get_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> get_OnAction(This,pbstrOnAction)

#define CommandBarControl_put_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> put_OnAction(This,pbstrOnAction)

#define CommandBarControl_get_Parent(This,ppcb)	\
    (This)->lpVtbl -> get_Parent(This,ppcb)

#define CommandBarControl_get_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> get_Parameter(This,pbstrParam)

#define CommandBarControl_put_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> put_Parameter(This,pbstrParam)

#define CommandBarControl_get_Priority(This,pnPri)	\
    (This)->lpVtbl -> get_Priority(This,pnPri)

#define CommandBarControl_put_Priority(This,pnPri)	\
    (This)->lpVtbl -> put_Priority(This,pnPri)

#define CommandBarControl_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define CommandBarControl_SetFocus(This)	\
    (This)->lpVtbl -> SetFocus(This)

#define CommandBarControl_get_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> get_Tag(This,pbstrTag)

#define CommandBarControl_put_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> put_Tag(This,pbstrTag)

#define CommandBarControl_get_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> get_TooltipText(This,pbstrTooltip)

#define CommandBarControl_put_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> put_TooltipText(This,pbstrTooltip)

#define CommandBarControl_get_Top(This,py)	\
    (This)->lpVtbl -> get_Top(This,py)

#define CommandBarControl_get_Type(This,ptype)	\
    (This)->lpVtbl -> get_Type(This,ptype)

#define CommandBarControl_get_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> get_Visible(This,pvarfVisible)

#define CommandBarControl_put_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> put_Visible(This,pvarfVisible)

#define CommandBarControl_get_Width(This,pdx)	\
    (This)->lpVtbl -> get_Width(This,pdx)

#define CommandBarControl_put_Width(This,pdx)	\
    (This)->lpVtbl -> put_Width(This,pdx)

#define CommandBarControl_Reserved1(This)	\
    (This)->lpVtbl -> Reserved1(This)

#define CommandBarControl_Reserved2(This)	\
    (This)->lpVtbl -> Reserved2(This)

#define CommandBarControl_Reserved3(This)	\
    (This)->lpVtbl -> Reserved3(This)

#define CommandBarControl_Reserved4(This)	\
    (This)->lpVtbl -> Reserved4(This)

#define CommandBarControl_Reserved5(This)	\
    (This)->lpVtbl -> Reserved5(This)

#define CommandBarControl_Reserved6(This)	\
    (This)->lpVtbl -> Reserved6(This)

#define CommandBarControl_Reserved7(This)	\
    (This)->lpVtbl -> Reserved7(This)

#define CommandBarControl_Reserved8(This)	\
    (This)->lpVtbl -> Reserved8(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_BeginGroup_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBeginGroup);


void __RPC_STUB CommandBarControl_get_BeginGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_BeginGroup_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfBeginGroup);


void __RPC_STUB CommandBarControl_put_BeginGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_BuiltIn_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);


void __RPC_STUB CommandBarControl_get_BuiltIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Caption_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCaption);


void __RPC_STUB CommandBarControl_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Caption_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrCaption);


void __RPC_STUB CommandBarControl_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Control_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);


void __RPC_STUB CommandBarControl_get_Control_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Copy_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [optional][in] */ VARIANT Bar,
    /* [optional][in] */ VARIANT Before,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBarControl_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Delete_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [optional][in] */ VARIANT Temporary);


void __RPC_STUB CommandBarControl_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_DescriptionText_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrText);


void __RPC_STUB CommandBarControl_get_DescriptionText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_DescriptionText_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrText);


void __RPC_STUB CommandBarControl_put_DescriptionText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Enabled_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);


void __RPC_STUB CommandBarControl_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Enabled_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfEnabled);


void __RPC_STUB CommandBarControl_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Execute_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Height_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pdy);


void __RPC_STUB CommandBarControl_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Height_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ int pdy);


void __RPC_STUB CommandBarControl_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_HelpContextId_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pid);


void __RPC_STUB CommandBarControl_get_HelpContextId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_HelpContextId_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ int pid);


void __RPC_STUB CommandBarControl_put_HelpContextId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_HelpFile_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);


void __RPC_STUB CommandBarControl_get_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_HelpFile_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrFilename);


void __RPC_STUB CommandBarControl_put_HelpFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Id_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pid);


void __RPC_STUB CommandBarControl_get_Id_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Index_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pi);


void __RPC_STUB CommandBarControl_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_InstanceId_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pid);


void __RPC_STUB CommandBarControl_get_InstanceId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Move_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [optional][in] */ VARIANT Bar,
    /* [optional][in] */ VARIANT Before,
    /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);


void __RPC_STUB CommandBarControl_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Left_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *px);


void __RPC_STUB CommandBarControl_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_OLEUsage_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ MsoControlOLEUsage __RPC_FAR *pcou);


void __RPC_STUB CommandBarControl_get_OLEUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_OLEUsage_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ MsoControlOLEUsage pcou);


void __RPC_STUB CommandBarControl_put_OLEUsage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_OnAction_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrOnAction);


void __RPC_STUB CommandBarControl_get_OnAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_OnAction_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrOnAction);


void __RPC_STUB CommandBarControl_put_OnAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Parent_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);


void __RPC_STUB CommandBarControl_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Parameter_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrParam);


void __RPC_STUB CommandBarControl_get_Parameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Parameter_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrParam);


void __RPC_STUB CommandBarControl_put_Parameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Priority_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pnPri);


void __RPC_STUB CommandBarControl_get_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Priority_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ int pnPri);


void __RPC_STUB CommandBarControl_put_Priority_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reset_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_SetFocus_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_SetFocus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Tag_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTag);


void __RPC_STUB CommandBarControl_get_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Tag_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrTag);


void __RPC_STUB CommandBarControl_put_Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_TooltipText_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrTooltip);


void __RPC_STUB CommandBarControl_get_TooltipText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_TooltipText_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ BSTR pbstrTooltip);


void __RPC_STUB CommandBarControl_put_TooltipText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Top_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *py);


void __RPC_STUB CommandBarControl_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Type_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ MsoControlType __RPC_FAR *ptype);


void __RPC_STUB CommandBarControl_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Visible_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);


void __RPC_STUB CommandBarControl_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Visible_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfVisible);


void __RPC_STUB CommandBarControl_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_get_Width_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pdx);


void __RPC_STUB CommandBarControl_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_put_Width_Proxy( 
    CommandBarControl __RPC_FAR * This,
    /* [in] */ int pdx);


void __RPC_STUB CommandBarControl_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved1_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved2_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved3_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved4_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved5_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved5_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved6_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved6_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved7_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved7_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE CommandBarControl_Reserved8_Proxy( 
    CommandBarControl __RPC_FAR * This);


void __RPC_STUB CommandBarControl_Reserved8_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBarControl_INTERFACE_DEFINED__ */


#ifndef __CommandBarButton_INTERFACE_DEFINED__
#define __CommandBarButton_INTERFACE_DEFINED__

/* interface CommandBarButton */
/* [object][oleautomation][nonextensible][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBarButton,0x000C030E,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C030E-0000-0000-C000-000000000046")
    CommandBarButton : public CommandBarControl
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_BuiltInFace( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_BuiltInFace( 
            /* [in] */ VARIANT_BOOL pvarfBuiltIn) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CopyFace( void) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_FaceId( 
            /* [retval][out] */ int __RPC_FAR *pid) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_FaceId( 
            /* [in] */ int pid) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE PasteFace( void) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ShortcutText( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ShortcutText( 
            /* [in] */ BSTR pbstrText) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ MsoButtonState __RPC_FAR *pstate) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_State( 
            /* [in] */ MsoButtonState pstate) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ MsoButtonStyle __RPC_FAR *pstyle) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ MsoButtonStyle pstyle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarButtonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBarButton __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBarButton __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBarButton __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            CommandBarButton __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            CommandBarButton __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BeginGroup )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBeginGroup);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BeginGroup )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfBeginGroup);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuiltIn )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCaption);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrCaption);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT Temporary);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DescriptionText )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DescriptionText )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfEnabled);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdy);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ int pdy);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContextId )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpContextId )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ int pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFile )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrFilename);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Id )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pi);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InstanceId )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pid);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            CommandBarButton __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *px);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OLEUsage )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ MsoControlOLEUsage __RPC_FAR *pcou);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OLEUsage )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ MsoControlOLEUsage pcou);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OnAction )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOnAction);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OnAction )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrOnAction);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parameter )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrParam);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parameter )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrParam);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnPri);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ int pnPri);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFocus )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTag);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrTag);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TooltipText )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTooltip);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TooltipText )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrTooltip);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *py);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ MsoControlType __RPC_FAR *ptype);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfVisible);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdx);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ int pdx);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved1 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved2 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved3 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved4 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved5 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved6 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved7 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved8 )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuiltInFace )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BuiltInFace )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfBuiltIn);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyFace )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FaceId )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FaceId )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ int pid);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PasteFace )( 
            CommandBarButton __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShortcutText )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShortcutText )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ BSTR pbstrText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ MsoButtonState __RPC_FAR *pstate);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_State )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ MsoButtonState pstate);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            CommandBarButton __RPC_FAR * This,
            /* [retval][out] */ MsoButtonStyle __RPC_FAR *pstyle);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            CommandBarButton __RPC_FAR * This,
            /* [in] */ MsoButtonStyle pstyle);
        
        END_INTERFACE
    } CommandBarButtonVtbl;

    interface CommandBarButton
    {
        CONST_VTBL struct CommandBarButtonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBarButton_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBarButton_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBarButton_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBarButton_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBarButton_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBarButton_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBarButton_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBarButton_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define CommandBarButton_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define CommandBarButton_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define CommandBarButton_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define CommandBarButton_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define CommandBarButton_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define CommandBarButton_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define CommandBarButton_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define CommandBarButton_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define CommandBarButton_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define CommandBarButton_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define CommandBarButton_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define CommandBarButton_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define CommandBarButton_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define CommandBarButton_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define CommandBarButton_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define CommandBarButton_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define CommandBarButton_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define CommandBarButton_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define CommandBarButton_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define CommandBarButton_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)


#define CommandBarButton_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBarButton_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBarButton_get_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> get_BeginGroup(This,pvarfBeginGroup)

#define CommandBarButton_put_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> put_BeginGroup(This,pvarfBeginGroup)

#define CommandBarButton_get_BuiltIn(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> get_BuiltIn(This,pvarfBuiltIn)

#define CommandBarButton_get_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pbstrCaption)

#define CommandBarButton_put_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> put_Caption(This,pbstrCaption)

#define CommandBarButton_get_Control(This,ppidisp)	\
    (This)->lpVtbl -> get_Control(This,ppidisp)

#define CommandBarButton_Copy(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Copy(This,Bar,Before,ppcbc)

#define CommandBarButton_Delete(This,Temporary)	\
    (This)->lpVtbl -> Delete(This,Temporary)

#define CommandBarButton_get_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> get_DescriptionText(This,pbstrText)

#define CommandBarButton_put_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> put_DescriptionText(This,pbstrText)

#define CommandBarButton_get_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,pvarfEnabled)

#define CommandBarButton_put_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> put_Enabled(This,pvarfEnabled)

#define CommandBarButton_Execute(This)	\
    (This)->lpVtbl -> Execute(This)

#define CommandBarButton_get_Height(This,pdy)	\
    (This)->lpVtbl -> get_Height(This,pdy)

#define CommandBarButton_put_Height(This,pdy)	\
    (This)->lpVtbl -> put_Height(This,pdy)

#define CommandBarButton_get_HelpContextId(This,pid)	\
    (This)->lpVtbl -> get_HelpContextId(This,pid)

#define CommandBarButton_put_HelpContextId(This,pid)	\
    (This)->lpVtbl -> put_HelpContextId(This,pid)

#define CommandBarButton_get_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> get_HelpFile(This,pbstrFilename)

#define CommandBarButton_put_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> put_HelpFile(This,pbstrFilename)

#define CommandBarButton_get_Id(This,pid)	\
    (This)->lpVtbl -> get_Id(This,pid)

#define CommandBarButton_get_Index(This,pi)	\
    (This)->lpVtbl -> get_Index(This,pi)

#define CommandBarButton_get_InstanceId(This,pid)	\
    (This)->lpVtbl -> get_InstanceId(This,pid)

#define CommandBarButton_Move(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Move(This,Bar,Before,ppcbc)

#define CommandBarButton_get_Left(This,px)	\
    (This)->lpVtbl -> get_Left(This,px)

#define CommandBarButton_get_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> get_OLEUsage(This,pcou)

#define CommandBarButton_put_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> put_OLEUsage(This,pcou)

#define CommandBarButton_get_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> get_OnAction(This,pbstrOnAction)

#define CommandBarButton_put_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> put_OnAction(This,pbstrOnAction)

#define CommandBarButton_get_Parent(This,ppcb)	\
    (This)->lpVtbl -> get_Parent(This,ppcb)

#define CommandBarButton_get_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> get_Parameter(This,pbstrParam)

#define CommandBarButton_put_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> put_Parameter(This,pbstrParam)

#define CommandBarButton_get_Priority(This,pnPri)	\
    (This)->lpVtbl -> get_Priority(This,pnPri)

#define CommandBarButton_put_Priority(This,pnPri)	\
    (This)->lpVtbl -> put_Priority(This,pnPri)

#define CommandBarButton_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define CommandBarButton_SetFocus(This)	\
    (This)->lpVtbl -> SetFocus(This)

#define CommandBarButton_get_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> get_Tag(This,pbstrTag)

#define CommandBarButton_put_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> put_Tag(This,pbstrTag)

#define CommandBarButton_get_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> get_TooltipText(This,pbstrTooltip)

#define CommandBarButton_put_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> put_TooltipText(This,pbstrTooltip)

#define CommandBarButton_get_Top(This,py)	\
    (This)->lpVtbl -> get_Top(This,py)

#define CommandBarButton_get_Type(This,ptype)	\
    (This)->lpVtbl -> get_Type(This,ptype)

#define CommandBarButton_get_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> get_Visible(This,pvarfVisible)

#define CommandBarButton_put_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> put_Visible(This,pvarfVisible)

#define CommandBarButton_get_Width(This,pdx)	\
    (This)->lpVtbl -> get_Width(This,pdx)

#define CommandBarButton_put_Width(This,pdx)	\
    (This)->lpVtbl -> put_Width(This,pdx)

#define CommandBarButton_Reserved1(This)	\
    (This)->lpVtbl -> Reserved1(This)

#define CommandBarButton_Reserved2(This)	\
    (This)->lpVtbl -> Reserved2(This)

#define CommandBarButton_Reserved3(This)	\
    (This)->lpVtbl -> Reserved3(This)

#define CommandBarButton_Reserved4(This)	\
    (This)->lpVtbl -> Reserved4(This)

#define CommandBarButton_Reserved5(This)	\
    (This)->lpVtbl -> Reserved5(This)

#define CommandBarButton_Reserved6(This)	\
    (This)->lpVtbl -> Reserved6(This)

#define CommandBarButton_Reserved7(This)	\
    (This)->lpVtbl -> Reserved7(This)

#define CommandBarButton_Reserved8(This)	\
    (This)->lpVtbl -> Reserved8(This)


#define CommandBarButton_get_BuiltInFace(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> get_BuiltInFace(This,pvarfBuiltIn)

#define CommandBarButton_put_BuiltInFace(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> put_BuiltInFace(This,pvarfBuiltIn)

#define CommandBarButton_CopyFace(This)	\
    (This)->lpVtbl -> CopyFace(This)

#define CommandBarButton_get_FaceId(This,pid)	\
    (This)->lpVtbl -> get_FaceId(This,pid)

#define CommandBarButton_put_FaceId(This,pid)	\
    (This)->lpVtbl -> put_FaceId(This,pid)

#define CommandBarButton_PasteFace(This)	\
    (This)->lpVtbl -> PasteFace(This)

#define CommandBarButton_get_ShortcutText(This,pbstrText)	\
    (This)->lpVtbl -> get_ShortcutText(This,pbstrText)

#define CommandBarButton_put_ShortcutText(This,pbstrText)	\
    (This)->lpVtbl -> put_ShortcutText(This,pbstrText)

#define CommandBarButton_get_State(This,pstate)	\
    (This)->lpVtbl -> get_State(This,pstate)

#define CommandBarButton_put_State(This,pstate)	\
    (This)->lpVtbl -> put_State(This,pstate)

#define CommandBarButton_get_Style(This,pstyle)	\
    (This)->lpVtbl -> get_Style(This,pstyle)

#define CommandBarButton_put_Style(This,pstyle)	\
    (This)->lpVtbl -> put_Style(This,pstyle)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_get_BuiltInFace_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);


void __RPC_STUB CommandBarButton_get_BuiltInFace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_put_BuiltInFace_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL pvarfBuiltIn);


void __RPC_STUB CommandBarButton_put_BuiltInFace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_CopyFace_Proxy( 
    CommandBarButton __RPC_FAR * This);


void __RPC_STUB CommandBarButton_CopyFace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_get_FaceId_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pid);


void __RPC_STUB CommandBarButton_get_FaceId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_put_FaceId_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [in] */ int pid);


void __RPC_STUB CommandBarButton_put_FaceId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_PasteFace_Proxy( 
    CommandBarButton __RPC_FAR * This);


void __RPC_STUB CommandBarButton_PasteFace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_get_ShortcutText_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrText);


void __RPC_STUB CommandBarButton_get_ShortcutText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_put_ShortcutText_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [in] */ BSTR pbstrText);


void __RPC_STUB CommandBarButton_put_ShortcutText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_get_State_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [retval][out] */ MsoButtonState __RPC_FAR *pstate);


void __RPC_STUB CommandBarButton_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_put_State_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [in] */ MsoButtonState pstate);


void __RPC_STUB CommandBarButton_put_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_get_Style_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [retval][out] */ MsoButtonStyle __RPC_FAR *pstyle);


void __RPC_STUB CommandBarButton_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarButton_put_Style_Proxy( 
    CommandBarButton __RPC_FAR * This,
    /* [in] */ MsoButtonStyle pstyle);


void __RPC_STUB CommandBarButton_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBarButton_INTERFACE_DEFINED__ */


#ifndef __CommandBarPopup_INTERFACE_DEFINED__
#define __CommandBarPopup_INTERFACE_DEFINED__

/* interface CommandBarPopup */
/* [object][oleautomation][nonextensible][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBarPopup,0x000C030A,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C030A-0000-0000-C000-000000000046")
    CommandBarPopup : public CommandBarControl
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CommandBar( 
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Controls( 
            /* [retval][out] */ CommandBarControls __RPC_FAR *__RPC_FAR *ppcbcs) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OLEMenuGroup( 
            /* [retval][out] */ MsoOLEMenuGroup __RPC_FAR *pomg) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_OLEMenuGroup( 
            /* [in] */ MsoOLEMenuGroup pomg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarPopupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBarPopup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBarPopup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBarPopup __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            CommandBarPopup __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            CommandBarPopup __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BeginGroup )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBeginGroup);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BeginGroup )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfBeginGroup);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuiltIn )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCaption);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrCaption);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT Temporary);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DescriptionText )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DescriptionText )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfEnabled);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdy);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ int pdy);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContextId )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpContextId )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ int pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFile )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrFilename);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Id )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pi);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InstanceId )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pid);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            CommandBarPopup __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *px);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OLEUsage )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ MsoControlOLEUsage __RPC_FAR *pcou);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OLEUsage )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ MsoControlOLEUsage pcou);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OnAction )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOnAction);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OnAction )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrOnAction);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parameter )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrParam);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parameter )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrParam);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnPri);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ int pnPri);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFocus )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTag);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrTag);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TooltipText )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTooltip);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TooltipText )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ BSTR pbstrTooltip);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *py);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ MsoControlType __RPC_FAR *ptype);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfVisible);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdx);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ int pdx);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved1 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved2 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved3 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved4 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved5 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved6 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved7 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved8 )( 
            CommandBarPopup __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommandBar )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Controls )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ CommandBarControls __RPC_FAR *__RPC_FAR *ppcbcs);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OLEMenuGroup )( 
            CommandBarPopup __RPC_FAR * This,
            /* [retval][out] */ MsoOLEMenuGroup __RPC_FAR *pomg);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OLEMenuGroup )( 
            CommandBarPopup __RPC_FAR * This,
            /* [in] */ MsoOLEMenuGroup pomg);
        
        END_INTERFACE
    } CommandBarPopupVtbl;

    interface CommandBarPopup
    {
        CONST_VTBL struct CommandBarPopupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBarPopup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBarPopup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBarPopup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBarPopup_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBarPopup_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBarPopup_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBarPopup_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBarPopup_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define CommandBarPopup_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define CommandBarPopup_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define CommandBarPopup_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define CommandBarPopup_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define CommandBarPopup_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define CommandBarPopup_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define CommandBarPopup_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define CommandBarPopup_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define CommandBarPopup_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define CommandBarPopup_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define CommandBarPopup_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define CommandBarPopup_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define CommandBarPopup_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define CommandBarPopup_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define CommandBarPopup_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define CommandBarPopup_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define CommandBarPopup_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define CommandBarPopup_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define CommandBarPopup_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define CommandBarPopup_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)


#define CommandBarPopup_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBarPopup_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBarPopup_get_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> get_BeginGroup(This,pvarfBeginGroup)

#define CommandBarPopup_put_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> put_BeginGroup(This,pvarfBeginGroup)

#define CommandBarPopup_get_BuiltIn(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> get_BuiltIn(This,pvarfBuiltIn)

#define CommandBarPopup_get_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pbstrCaption)

#define CommandBarPopup_put_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> put_Caption(This,pbstrCaption)

#define CommandBarPopup_get_Control(This,ppidisp)	\
    (This)->lpVtbl -> get_Control(This,ppidisp)

#define CommandBarPopup_Copy(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Copy(This,Bar,Before,ppcbc)

#define CommandBarPopup_Delete(This,Temporary)	\
    (This)->lpVtbl -> Delete(This,Temporary)

#define CommandBarPopup_get_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> get_DescriptionText(This,pbstrText)

#define CommandBarPopup_put_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> put_DescriptionText(This,pbstrText)

#define CommandBarPopup_get_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,pvarfEnabled)

#define CommandBarPopup_put_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> put_Enabled(This,pvarfEnabled)

#define CommandBarPopup_Execute(This)	\
    (This)->lpVtbl -> Execute(This)

#define CommandBarPopup_get_Height(This,pdy)	\
    (This)->lpVtbl -> get_Height(This,pdy)

#define CommandBarPopup_put_Height(This,pdy)	\
    (This)->lpVtbl -> put_Height(This,pdy)

#define CommandBarPopup_get_HelpContextId(This,pid)	\
    (This)->lpVtbl -> get_HelpContextId(This,pid)

#define CommandBarPopup_put_HelpContextId(This,pid)	\
    (This)->lpVtbl -> put_HelpContextId(This,pid)

#define CommandBarPopup_get_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> get_HelpFile(This,pbstrFilename)

#define CommandBarPopup_put_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> put_HelpFile(This,pbstrFilename)

#define CommandBarPopup_get_Id(This,pid)	\
    (This)->lpVtbl -> get_Id(This,pid)

#define CommandBarPopup_get_Index(This,pi)	\
    (This)->lpVtbl -> get_Index(This,pi)

#define CommandBarPopup_get_InstanceId(This,pid)	\
    (This)->lpVtbl -> get_InstanceId(This,pid)

#define CommandBarPopup_Move(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Move(This,Bar,Before,ppcbc)

#define CommandBarPopup_get_Left(This,px)	\
    (This)->lpVtbl -> get_Left(This,px)

#define CommandBarPopup_get_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> get_OLEUsage(This,pcou)

#define CommandBarPopup_put_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> put_OLEUsage(This,pcou)

#define CommandBarPopup_get_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> get_OnAction(This,pbstrOnAction)

#define CommandBarPopup_put_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> put_OnAction(This,pbstrOnAction)

#define CommandBarPopup_get_Parent(This,ppcb)	\
    (This)->lpVtbl -> get_Parent(This,ppcb)

#define CommandBarPopup_get_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> get_Parameter(This,pbstrParam)

#define CommandBarPopup_put_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> put_Parameter(This,pbstrParam)

#define CommandBarPopup_get_Priority(This,pnPri)	\
    (This)->lpVtbl -> get_Priority(This,pnPri)

#define CommandBarPopup_put_Priority(This,pnPri)	\
    (This)->lpVtbl -> put_Priority(This,pnPri)

#define CommandBarPopup_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define CommandBarPopup_SetFocus(This)	\
    (This)->lpVtbl -> SetFocus(This)

#define CommandBarPopup_get_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> get_Tag(This,pbstrTag)

#define CommandBarPopup_put_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> put_Tag(This,pbstrTag)

#define CommandBarPopup_get_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> get_TooltipText(This,pbstrTooltip)

#define CommandBarPopup_put_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> put_TooltipText(This,pbstrTooltip)

#define CommandBarPopup_get_Top(This,py)	\
    (This)->lpVtbl -> get_Top(This,py)

#define CommandBarPopup_get_Type(This,ptype)	\
    (This)->lpVtbl -> get_Type(This,ptype)

#define CommandBarPopup_get_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> get_Visible(This,pvarfVisible)

#define CommandBarPopup_put_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> put_Visible(This,pvarfVisible)

#define CommandBarPopup_get_Width(This,pdx)	\
    (This)->lpVtbl -> get_Width(This,pdx)

#define CommandBarPopup_put_Width(This,pdx)	\
    (This)->lpVtbl -> put_Width(This,pdx)

#define CommandBarPopup_Reserved1(This)	\
    (This)->lpVtbl -> Reserved1(This)

#define CommandBarPopup_Reserved2(This)	\
    (This)->lpVtbl -> Reserved2(This)

#define CommandBarPopup_Reserved3(This)	\
    (This)->lpVtbl -> Reserved3(This)

#define CommandBarPopup_Reserved4(This)	\
    (This)->lpVtbl -> Reserved4(This)

#define CommandBarPopup_Reserved5(This)	\
    (This)->lpVtbl -> Reserved5(This)

#define CommandBarPopup_Reserved6(This)	\
    (This)->lpVtbl -> Reserved6(This)

#define CommandBarPopup_Reserved7(This)	\
    (This)->lpVtbl -> Reserved7(This)

#define CommandBarPopup_Reserved8(This)	\
    (This)->lpVtbl -> Reserved8(This)


#define CommandBarPopup_get_CommandBar(This,ppcb)	\
    (This)->lpVtbl -> get_CommandBar(This,ppcb)

#define CommandBarPopup_get_Controls(This,ppcbcs)	\
    (This)->lpVtbl -> get_Controls(This,ppcbcs)

#define CommandBarPopup_get_OLEMenuGroup(This,pomg)	\
    (This)->lpVtbl -> get_OLEMenuGroup(This,pomg)

#define CommandBarPopup_put_OLEMenuGroup(This,pomg)	\
    (This)->lpVtbl -> put_OLEMenuGroup(This,pomg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarPopup_get_CommandBar_Proxy( 
    CommandBarPopup __RPC_FAR * This,
    /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);


void __RPC_STUB CommandBarPopup_get_CommandBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarPopup_get_Controls_Proxy( 
    CommandBarPopup __RPC_FAR * This,
    /* [retval][out] */ CommandBarControls __RPC_FAR *__RPC_FAR *ppcbcs);


void __RPC_STUB CommandBarPopup_get_Controls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarPopup_get_OLEMenuGroup_Proxy( 
    CommandBarPopup __RPC_FAR * This,
    /* [retval][out] */ MsoOLEMenuGroup __RPC_FAR *pomg);


void __RPC_STUB CommandBarPopup_get_OLEMenuGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarPopup_put_OLEMenuGroup_Proxy( 
    CommandBarPopup __RPC_FAR * This,
    /* [in] */ MsoOLEMenuGroup pomg);


void __RPC_STUB CommandBarPopup_put_OLEMenuGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBarPopup_INTERFACE_DEFINED__ */


#ifndef __CommandBarComboBox_INTERFACE_DEFINED__
#define __CommandBarComboBox_INTERFACE_DEFINED__

/* interface CommandBarComboBox */
/* [object][oleautomation][nonextensible][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_CommandBarComboBox,0x000C030C,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("000C030C-0000-0000-C000-000000000046")
    CommandBarComboBox : public CommandBarControl
    {
    public:
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddItem( 
            /* [in] */ BSTR Text,
            /* [optional][in] */ VARIANT Index) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DropDownLines( 
            /* [retval][out] */ int __RPC_FAR *pcLines) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DropDownLines( 
            /* [in] */ int pcLines) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DropDownWidth( 
            /* [retval][out] */ int __RPC_FAR *pdx) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DropDownWidth( 
            /* [in] */ int pdx) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_List( 
            /* [in] */ int Index,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrItem) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_List( 
            /* [in] */ int Index,
            /* [in] */ BSTR pbstrItem) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ListCount( 
            /* [retval][out] */ int __RPC_FAR *pcItems) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ListHeaderCount( 
            /* [retval][out] */ int __RPC_FAR *pcItems) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ListHeaderCount( 
            /* [in] */ int pcItems) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ListIndex( 
            /* [retval][out] */ int __RPC_FAR *pi) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ListIndex( 
            /* [in] */ int pi) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE RemoveItem( 
            /* [in] */ int Index) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Style( 
            /* [retval][out] */ MsoComboStyle __RPC_FAR *pstyle) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Style( 
            /* [in] */ MsoComboStyle pstyle) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR pbstrText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CommandBarComboBoxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CommandBarComboBox __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CommandBarComboBox __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accParent )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispParent);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChildCount )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pcountChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accChild )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ VARIANT varChild,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accName )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszName);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accValue )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszValue);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDescription )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDescription);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accRole )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarRole);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accState )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarState);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelp )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszHelp);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accHelpTopic )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pszHelpFile,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ long __RPC_FAR *pidTopic);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accKeyboardShortcut )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszKeyboardShortcut);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accFocus )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accSelection )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChildren);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_accDefaultAction )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [retval][out] */ BSTR __RPC_FAR *pszDefaultAction);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accSelect )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ long flagsSelect,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accLocation )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pxLeft,
            /* [out] */ long __RPC_FAR *pyTop,
            /* [out] */ long __RPC_FAR *pcxWidth,
            /* [out] */ long __RPC_FAR *pcyHeight,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accNavigate )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ long navDir,
            /* [optional][in] */ VARIANT varStart,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarEndUpAt);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accHitTest )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ long xLeft,
            /* [in] */ long yTop,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarChild);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *accDoDefaultAction )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accName )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszName);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_accValue )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT varChild,
            /* [in] */ BSTR pszValue);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Creator )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCreator);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BeginGroup )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBeginGroup);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BeginGroup )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfBeginGroup);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BuiltIn )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfBuiltIn);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCaption);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrCaption);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Control )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppidisp);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT Temporary);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DescriptionText )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DescriptionText )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfEnabled);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfEnabled);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdy);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pdy);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpContextId )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpContextId )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HelpFile )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrFilename);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HelpFile )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrFilename);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Id )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pid);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pi);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InstanceId )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pid);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [optional][in] */ VARIANT Bar,
            /* [optional][in] */ VARIANT Before,
            /* [retval][out] */ CommandBarControl __RPC_FAR *__RPC_FAR *ppcbc);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *px);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OLEUsage )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ MsoControlOLEUsage __RPC_FAR *pcou);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OLEUsage )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ MsoControlOLEUsage pcou);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OnAction )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrOnAction);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OnAction )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrOnAction);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ CommandBar __RPC_FAR *__RPC_FAR *ppcb);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parameter )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrParam);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Parameter )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrParam);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Priority )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pnPri);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Priority )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pnPri);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFocus )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Tag )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTag);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Tag )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrTag);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TooltipText )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrTooltip);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TooltipText )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrTooltip);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *py);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ MsoControlType __RPC_FAR *ptype);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pvarfVisible);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL pvarfVisible);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdx);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pdx);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved1 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved2 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved3 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved4 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved5 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved6 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved7 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reserved8 )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddItem )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR Text,
            /* [optional][in] */ VARIANT Index);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            CommandBarComboBox __RPC_FAR * This);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DropDownLines )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pcLines);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DropDownLines )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pcLines);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DropDownWidth )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pdx);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DropDownWidth )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pdx);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_List )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int Index,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrItem);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_List )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int Index,
            /* [in] */ BSTR pbstrItem);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListCount )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pcItems);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListHeaderCount )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pcItems);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ListHeaderCount )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pcItems);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListIndex )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *pi);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ListIndex )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int pi);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveItem )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ int Index);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Style )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ MsoComboStyle __RPC_FAR *pstyle);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Style )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ MsoComboStyle pstyle);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Text )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Text )( 
            CommandBarComboBox __RPC_FAR * This,
            /* [in] */ BSTR pbstrText);
        
        END_INTERFACE
    } CommandBarComboBoxVtbl;

    interface CommandBarComboBox
    {
        CONST_VTBL struct CommandBarComboBoxVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CommandBarComboBox_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CommandBarComboBox_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CommandBarComboBox_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CommandBarComboBox_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CommandBarComboBox_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CommandBarComboBox_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CommandBarComboBox_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CommandBarComboBox_get_accParent(This,ppdispParent)	\
    (This)->lpVtbl -> get_accParent(This,ppdispParent)

#define CommandBarComboBox_get_accChildCount(This,pcountChildren)	\
    (This)->lpVtbl -> get_accChildCount(This,pcountChildren)

#define CommandBarComboBox_get_accChild(This,varChild,ppdispChild)	\
    (This)->lpVtbl -> get_accChild(This,varChild,ppdispChild)

#define CommandBarComboBox_get_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> get_accName(This,varChild,pszName)

#define CommandBarComboBox_get_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> get_accValue(This,varChild,pszValue)

#define CommandBarComboBox_get_accDescription(This,varChild,pszDescription)	\
    (This)->lpVtbl -> get_accDescription(This,varChild,pszDescription)

#define CommandBarComboBox_get_accRole(This,varChild,pvarRole)	\
    (This)->lpVtbl -> get_accRole(This,varChild,pvarRole)

#define CommandBarComboBox_get_accState(This,varChild,pvarState)	\
    (This)->lpVtbl -> get_accState(This,varChild,pvarState)

#define CommandBarComboBox_get_accHelp(This,varChild,pszHelp)	\
    (This)->lpVtbl -> get_accHelp(This,varChild,pszHelp)

#define CommandBarComboBox_get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)	\
    (This)->lpVtbl -> get_accHelpTopic(This,pszHelpFile,varChild,pidTopic)

#define CommandBarComboBox_get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)	\
    (This)->lpVtbl -> get_accKeyboardShortcut(This,varChild,pszKeyboardShortcut)

#define CommandBarComboBox_get_accFocus(This,pvarChild)	\
    (This)->lpVtbl -> get_accFocus(This,pvarChild)

#define CommandBarComboBox_get_accSelection(This,pvarChildren)	\
    (This)->lpVtbl -> get_accSelection(This,pvarChildren)

#define CommandBarComboBox_get_accDefaultAction(This,varChild,pszDefaultAction)	\
    (This)->lpVtbl -> get_accDefaultAction(This,varChild,pszDefaultAction)

#define CommandBarComboBox_accSelect(This,flagsSelect,varChild)	\
    (This)->lpVtbl -> accSelect(This,flagsSelect,varChild)

#define CommandBarComboBox_accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)	\
    (This)->lpVtbl -> accLocation(This,pxLeft,pyTop,pcxWidth,pcyHeight,varChild)

#define CommandBarComboBox_accNavigate(This,navDir,varStart,pvarEndUpAt)	\
    (This)->lpVtbl -> accNavigate(This,navDir,varStart,pvarEndUpAt)

#define CommandBarComboBox_accHitTest(This,xLeft,yTop,pvarChild)	\
    (This)->lpVtbl -> accHitTest(This,xLeft,yTop,pvarChild)

#define CommandBarComboBox_accDoDefaultAction(This,varChild)	\
    (This)->lpVtbl -> accDoDefaultAction(This,varChild)

#define CommandBarComboBox_put_accName(This,varChild,pszName)	\
    (This)->lpVtbl -> put_accName(This,varChild,pszName)

#define CommandBarComboBox_put_accValue(This,varChild,pszValue)	\
    (This)->lpVtbl -> put_accValue(This,varChild,pszValue)


#define CommandBarComboBox_get_Application(This,ppidisp)	\
    (This)->lpVtbl -> get_Application(This,ppidisp)

#define CommandBarComboBox_get_Creator(This,plCreator)	\
    (This)->lpVtbl -> get_Creator(This,plCreator)


#define CommandBarComboBox_get_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> get_BeginGroup(This,pvarfBeginGroup)

#define CommandBarComboBox_put_BeginGroup(This,pvarfBeginGroup)	\
    (This)->lpVtbl -> put_BeginGroup(This,pvarfBeginGroup)

#define CommandBarComboBox_get_BuiltIn(This,pvarfBuiltIn)	\
    (This)->lpVtbl -> get_BuiltIn(This,pvarfBuiltIn)

#define CommandBarComboBox_get_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> get_Caption(This,pbstrCaption)

#define CommandBarComboBox_put_Caption(This,pbstrCaption)	\
    (This)->lpVtbl -> put_Caption(This,pbstrCaption)

#define CommandBarComboBox_get_Control(This,ppidisp)	\
    (This)->lpVtbl -> get_Control(This,ppidisp)

#define CommandBarComboBox_Copy(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Copy(This,Bar,Before,ppcbc)

#define CommandBarComboBox_Delete(This,Temporary)	\
    (This)->lpVtbl -> Delete(This,Temporary)

#define CommandBarComboBox_get_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> get_DescriptionText(This,pbstrText)

#define CommandBarComboBox_put_DescriptionText(This,pbstrText)	\
    (This)->lpVtbl -> put_DescriptionText(This,pbstrText)

#define CommandBarComboBox_get_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,pvarfEnabled)

#define CommandBarComboBox_put_Enabled(This,pvarfEnabled)	\
    (This)->lpVtbl -> put_Enabled(This,pvarfEnabled)

#define CommandBarComboBox_Execute(This)	\
    (This)->lpVtbl -> Execute(This)

#define CommandBarComboBox_get_Height(This,pdy)	\
    (This)->lpVtbl -> get_Height(This,pdy)

#define CommandBarComboBox_put_Height(This,pdy)	\
    (This)->lpVtbl -> put_Height(This,pdy)

#define CommandBarComboBox_get_HelpContextId(This,pid)	\
    (This)->lpVtbl -> get_HelpContextId(This,pid)

#define CommandBarComboBox_put_HelpContextId(This,pid)	\
    (This)->lpVtbl -> put_HelpContextId(This,pid)

#define CommandBarComboBox_get_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> get_HelpFile(This,pbstrFilename)

#define CommandBarComboBox_put_HelpFile(This,pbstrFilename)	\
    (This)->lpVtbl -> put_HelpFile(This,pbstrFilename)

#define CommandBarComboBox_get_Id(This,pid)	\
    (This)->lpVtbl -> get_Id(This,pid)

#define CommandBarComboBox_get_Index(This,pi)	\
    (This)->lpVtbl -> get_Index(This,pi)

#define CommandBarComboBox_get_InstanceId(This,pid)	\
    (This)->lpVtbl -> get_InstanceId(This,pid)

#define CommandBarComboBox_Move(This,Bar,Before,ppcbc)	\
    (This)->lpVtbl -> Move(This,Bar,Before,ppcbc)

#define CommandBarComboBox_get_Left(This,px)	\
    (This)->lpVtbl -> get_Left(This,px)

#define CommandBarComboBox_get_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> get_OLEUsage(This,pcou)

#define CommandBarComboBox_put_OLEUsage(This,pcou)	\
    (This)->lpVtbl -> put_OLEUsage(This,pcou)

#define CommandBarComboBox_get_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> get_OnAction(This,pbstrOnAction)

#define CommandBarComboBox_put_OnAction(This,pbstrOnAction)	\
    (This)->lpVtbl -> put_OnAction(This,pbstrOnAction)

#define CommandBarComboBox_get_Parent(This,ppcb)	\
    (This)->lpVtbl -> get_Parent(This,ppcb)

#define CommandBarComboBox_get_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> get_Parameter(This,pbstrParam)

#define CommandBarComboBox_put_Parameter(This,pbstrParam)	\
    (This)->lpVtbl -> put_Parameter(This,pbstrParam)

#define CommandBarComboBox_get_Priority(This,pnPri)	\
    (This)->lpVtbl -> get_Priority(This,pnPri)

#define CommandBarComboBox_put_Priority(This,pnPri)	\
    (This)->lpVtbl -> put_Priority(This,pnPri)

#define CommandBarComboBox_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define CommandBarComboBox_SetFocus(This)	\
    (This)->lpVtbl -> SetFocus(This)

#define CommandBarComboBox_get_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> get_Tag(This,pbstrTag)

#define CommandBarComboBox_put_Tag(This,pbstrTag)	\
    (This)->lpVtbl -> put_Tag(This,pbstrTag)

#define CommandBarComboBox_get_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> get_TooltipText(This,pbstrTooltip)

#define CommandBarComboBox_put_TooltipText(This,pbstrTooltip)	\
    (This)->lpVtbl -> put_TooltipText(This,pbstrTooltip)

#define CommandBarComboBox_get_Top(This,py)	\
    (This)->lpVtbl -> get_Top(This,py)

#define CommandBarComboBox_get_Type(This,ptype)	\
    (This)->lpVtbl -> get_Type(This,ptype)

#define CommandBarComboBox_get_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> get_Visible(This,pvarfVisible)

#define CommandBarComboBox_put_Visible(This,pvarfVisible)	\
    (This)->lpVtbl -> put_Visible(This,pvarfVisible)

#define CommandBarComboBox_get_Width(This,pdx)	\
    (This)->lpVtbl -> get_Width(This,pdx)

#define CommandBarComboBox_put_Width(This,pdx)	\
    (This)->lpVtbl -> put_Width(This,pdx)

#define CommandBarComboBox_Reserved1(This)	\
    (This)->lpVtbl -> Reserved1(This)

#define CommandBarComboBox_Reserved2(This)	\
    (This)->lpVtbl -> Reserved2(This)

#define CommandBarComboBox_Reserved3(This)	\
    (This)->lpVtbl -> Reserved3(This)

#define CommandBarComboBox_Reserved4(This)	\
    (This)->lpVtbl -> Reserved4(This)

#define CommandBarComboBox_Reserved5(This)	\
    (This)->lpVtbl -> Reserved5(This)

#define CommandBarComboBox_Reserved6(This)	\
    (This)->lpVtbl -> Reserved6(This)

#define CommandBarComboBox_Reserved7(This)	\
    (This)->lpVtbl -> Reserved7(This)

#define CommandBarComboBox_Reserved8(This)	\
    (This)->lpVtbl -> Reserved8(This)


#define CommandBarComboBox_AddItem(This,Text,Index)	\
    (This)->lpVtbl -> AddItem(This,Text,Index)

#define CommandBarComboBox_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define CommandBarComboBox_get_DropDownLines(This,pcLines)	\
    (This)->lpVtbl -> get_DropDownLines(This,pcLines)

#define CommandBarComboBox_put_DropDownLines(This,pcLines)	\
    (This)->lpVtbl -> put_DropDownLines(This,pcLines)

#define CommandBarComboBox_get_DropDownWidth(This,pdx)	\
    (This)->lpVtbl -> get_DropDownWidth(This,pdx)

#define CommandBarComboBox_put_DropDownWidth(This,pdx)	\
    (This)->lpVtbl -> put_DropDownWidth(This,pdx)

#define CommandBarComboBox_get_List(This,Index,pbstrItem)	\
    (This)->lpVtbl -> get_List(This,Index,pbstrItem)

#define CommandBarComboBox_put_List(This,Index,pbstrItem)	\
    (This)->lpVtbl -> put_List(This,Index,pbstrItem)

#define CommandBarComboBox_get_ListCount(This,pcItems)	\
    (This)->lpVtbl -> get_ListCount(This,pcItems)

#define CommandBarComboBox_get_ListHeaderCount(This,pcItems)	\
    (This)->lpVtbl -> get_ListHeaderCount(This,pcItems)

#define CommandBarComboBox_put_ListHeaderCount(This,pcItems)	\
    (This)->lpVtbl -> put_ListHeaderCount(This,pcItems)

#define CommandBarComboBox_get_ListIndex(This,pi)	\
    (This)->lpVtbl -> get_ListIndex(This,pi)

#define CommandBarComboBox_put_ListIndex(This,pi)	\
    (This)->lpVtbl -> put_ListIndex(This,pi)

#define CommandBarComboBox_RemoveItem(This,Index)	\
    (This)->lpVtbl -> RemoveItem(This,Index)

#define CommandBarComboBox_get_Style(This,pstyle)	\
    (This)->lpVtbl -> get_Style(This,pstyle)

#define CommandBarComboBox_put_Style(This,pstyle)	\
    (This)->lpVtbl -> put_Style(This,pstyle)

#define CommandBarComboBox_get_Text(This,pbstrText)	\
    (This)->lpVtbl -> get_Text(This,pbstrText)

#define CommandBarComboBox_put_Text(This,pbstrText)	\
    (This)->lpVtbl -> put_Text(This,pbstrText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_AddItem_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ BSTR Text,
    /* [optional][in] */ VARIANT Index);


void __RPC_STUB CommandBarComboBox_AddItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_Clear_Proxy( 
    CommandBarComboBox __RPC_FAR * This);


void __RPC_STUB CommandBarComboBox_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_DropDownLines_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pcLines);


void __RPC_STUB CommandBarComboBox_get_DropDownLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_DropDownLines_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int pcLines);


void __RPC_STUB CommandBarComboBox_put_DropDownLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_DropDownWidth_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pdx);


void __RPC_STUB CommandBarComboBox_get_DropDownWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_DropDownWidth_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int pdx);


void __RPC_STUB CommandBarComboBox_put_DropDownWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_List_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int Index,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrItem);


void __RPC_STUB CommandBarComboBox_get_List_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_List_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int Index,
    /* [in] */ BSTR pbstrItem);


void __RPC_STUB CommandBarComboBox_put_List_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_ListCount_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pcItems);


void __RPC_STUB CommandBarComboBox_get_ListCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_ListHeaderCount_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pcItems);


void __RPC_STUB CommandBarComboBox_get_ListHeaderCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_ListHeaderCount_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int pcItems);


void __RPC_STUB CommandBarComboBox_put_ListHeaderCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_ListIndex_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *pi);


void __RPC_STUB CommandBarComboBox_get_ListIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_ListIndex_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int pi);


void __RPC_STUB CommandBarComboBox_put_ListIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_RemoveItem_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ int Index);


void __RPC_STUB CommandBarComboBox_RemoveItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_Style_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ MsoComboStyle __RPC_FAR *pstyle);


void __RPC_STUB CommandBarComboBox_get_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_Style_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ MsoComboStyle pstyle);


void __RPC_STUB CommandBarComboBox_put_Style_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_get_Text_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrText);


void __RPC_STUB CommandBarComboBox_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE CommandBarComboBox_put_Text_Proxy( 
    CommandBarComboBox __RPC_FAR * This,
    /* [in] */ BSTR pbstrText);


void __RPC_STUB CommandBarComboBox_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CommandBarComboBox_INTERFACE_DEFINED__ */

#endif /* __Office_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

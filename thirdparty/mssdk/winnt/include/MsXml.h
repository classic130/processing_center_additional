/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Fri Jul 31 15:05:44 1998
 */
/* Compiler settings for msxml.idl:
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

#ifndef __msxml_h__
#define __msxml_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IXMLElementCollection_FWD_DEFINED__
#define __IXMLElementCollection_FWD_DEFINED__
typedef interface IXMLElementCollection IXMLElementCollection;
#endif 	/* __IXMLElementCollection_FWD_DEFINED__ */


#ifndef __IXMLDocument_FWD_DEFINED__
#define __IXMLDocument_FWD_DEFINED__
typedef interface IXMLDocument IXMLDocument;
#endif 	/* __IXMLDocument_FWD_DEFINED__ */


#ifndef __IXMLDocument2_FWD_DEFINED__
#define __IXMLDocument2_FWD_DEFINED__
typedef interface IXMLDocument2 IXMLDocument2;
#endif 	/* __IXMLDocument2_FWD_DEFINED__ */


#ifndef __IXMLElement_FWD_DEFINED__
#define __IXMLElement_FWD_DEFINED__
typedef interface IXMLElement IXMLElement;
#endif 	/* __IXMLElement_FWD_DEFINED__ */


#ifndef __IXMLElement2_FWD_DEFINED__
#define __IXMLElement2_FWD_DEFINED__
typedef interface IXMLElement2 IXMLElement2;
#endif 	/* __IXMLElement2_FWD_DEFINED__ */


#ifndef __IXMLAttribute_FWD_DEFINED__
#define __IXMLAttribute_FWD_DEFINED__
typedef interface IXMLAttribute IXMLAttribute;
#endif 	/* __IXMLAttribute_FWD_DEFINED__ */


#ifndef __IXMLDocument2Ex_FWD_DEFINED__
#define __IXMLDocument2Ex_FWD_DEFINED__
typedef interface IXMLDocument2Ex IXMLDocument2Ex;
#endif 	/* __IXMLDocument2Ex_FWD_DEFINED__ */


#ifndef __IXMLError_FWD_DEFINED__
#define __IXMLError_FWD_DEFINED__
typedef interface IXMLError IXMLError;
#endif 	/* __IXMLError_FWD_DEFINED__ */


#ifndef __IXMLError2_FWD_DEFINED__
#define __IXMLError2_FWD_DEFINED__
typedef interface IXMLError2 IXMLError2;
#endif 	/* __IXMLError2_FWD_DEFINED__ */


#ifndef __IDOMNode_FWD_DEFINED__
#define __IDOMNode_FWD_DEFINED__
typedef interface IDOMNode IDOMNode;
#endif 	/* __IDOMNode_FWD_DEFINED__ */


#ifndef __IDOMNodeList_FWD_DEFINED__
#define __IDOMNodeList_FWD_DEFINED__
typedef interface IDOMNodeList IDOMNodeList;
#endif 	/* __IDOMNodeList_FWD_DEFINED__ */


#ifndef __IDOMDocument_FWD_DEFINED__
#define __IDOMDocument_FWD_DEFINED__
typedef interface IDOMDocument IDOMDocument;
#endif 	/* __IDOMDocument_FWD_DEFINED__ */


#ifndef __IDOMError_FWD_DEFINED__
#define __IDOMError_FWD_DEFINED__
typedef interface IDOMError IDOMError;
#endif 	/* __IDOMError_FWD_DEFINED__ */


#ifndef __IXMLDOMNode_FWD_DEFINED__
#define __IXMLDOMNode_FWD_DEFINED__
typedef interface IXMLDOMNode IXMLDOMNode;
#endif 	/* __IXMLDOMNode_FWD_DEFINED__ */


#ifndef __IXMLDOMDocument_FWD_DEFINED__
#define __IXMLDOMDocument_FWD_DEFINED__
typedef interface IXMLDOMDocument IXMLDOMDocument;
#endif 	/* __IXMLDOMDocument_FWD_DEFINED__ */


#ifndef __DOMDocument_FWD_DEFINED__
#define __DOMDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class DOMDocument DOMDocument;
#else
typedef struct DOMDocument DOMDocument;
#endif /* __cplusplus */

#endif 	/* __DOMDocument_FWD_DEFINED__ */


#ifndef __IXMLIslandPeer_FWD_DEFINED__
#define __IXMLIslandPeer_FWD_DEFINED__
typedef interface IXMLIslandPeer IXMLIslandPeer;
#endif 	/* __IXMLIslandPeer_FWD_DEFINED__ */


#ifndef __XMLIslandPeer_FWD_DEFINED__
#define __XMLIslandPeer_FWD_DEFINED__

#ifdef __cplusplus
typedef class XMLIslandPeer XMLIslandPeer;
#else
typedef struct XMLIslandPeer XMLIslandPeer;
#endif /* __cplusplus */

#endif 	/* __XMLIslandPeer_FWD_DEFINED__ */


#ifndef __IXMLElementNotificationSink_FWD_DEFINED__
#define __IXMLElementNotificationSink_FWD_DEFINED__
typedef interface IXMLElementNotificationSink IXMLElementNotificationSink;
#endif 	/* __IXMLElementNotificationSink_FWD_DEFINED__ */


#ifndef __XMLDocument_FWD_DEFINED__
#define __XMLDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class XMLDocument XMLDocument;
#else
typedef struct XMLDocument XMLDocument;
#endif /* __cplusplus */

#endif 	/* __XMLDocument_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_msxml_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1997-1998.
//
//--------------------------------------------------------------------------
typedef struct  _xml_error
    {
    unsigned int _nLine;
    BSTR _pchBuf;
    unsigned int _cchBuf;
    unsigned int _ich;
    BSTR _pszFound;
    BSTR _pszExpected;
    DWORD _reserved1;
    DWORD _reserved2;
    }	XML_ERROR;



extern RPC_IF_HANDLE __MIDL_itf_msxml_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_msxml_0000_v0_0_s_ifspec;


#ifndef __MSXML_LIBRARY_DEFINED__
#define __MSXML_LIBRARY_DEFINED__

/* library MSXML */
/* [version][lcid][helpstring][uuid] */ 










//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1998.
//
//--------------------------------------------------------------------------




typedef /* [helpstring] */ 
enum tagXMLNodeType
    {	NODE_ELEMENT	= 0,
	NODE_PCDATA	= NODE_ELEMENT + 1,
	NODE_COMMENT	= NODE_PCDATA + 1,
	NODE_DOCUMENT	= NODE_COMMENT + 1,
	NODE_DOCTYPE	= NODE_DOCUMENT + 1,
	NODE_PI	= NODE_DOCTYPE + 1,
	NODE_CDATA	= NODE_PI + 1,
	NODE_NAMESPACE	= NODE_CDATA + 1,
	NODE_ENTITYREF	= NODE_NAMESPACE + 1,
	NODE_WHITESPACE	= NODE_ENTITYREF + 1,
	NODE_ATTRIBUTE	= NODE_WHITESPACE + 1,
	NODE_XMLDECL	= NODE_ATTRIBUTE + 1
    }	XMLNodeType;

typedef /* [helpstring] */ 
enum tagXMLEMEM_TYPE
    {	XMLELEMTYPE_ELEMENT	= 0,
	XMLELEMTYPE_TEXT	= XMLELEMTYPE_ELEMENT + 1,
	XMLELEMTYPE_COMMENT	= XMLELEMTYPE_TEXT + 1,
	XMLELEMTYPE_DOCUMENT	= XMLELEMTYPE_COMMENT + 1,
	XMLELEMTYPE_DTD	= XMLELEMTYPE_DOCUMENT + 1,
	XMLELEMTYPE_PI	= XMLELEMTYPE_DTD + 1,
	XMLELEMTYPE_OTHER	= XMLELEMTYPE_PI + 1
    }	XMLELEM_TYPE;


EXTERN_C const IID LIBID_MSXML;

#ifndef __IXMLElementCollection_INTERFACE_DEFINED__
#define __IXMLElementCollection_INTERFACE_DEFINED__

/* interface IXMLElementCollection */
/* [helpstring][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLElementCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("65725580-9B5D-11d0-9BFE-00C04FC99C8E")
    IXMLElementCollection : public IDispatch
    {
    public:
        virtual /* [id][hidden][restricted][propput] */ HRESULT STDMETHODCALLTYPE put_length( 
            /* [in] */ long v) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [out][retval] */ long __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__newEnum( 
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE item( 
            /* [in][optional] */ VARIANT var1,
            /* [in][optional] */ VARIANT var2,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLElementCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLElementCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLElementCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][hidden][restricted][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_length )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [in] */ long v);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__newEnum )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IXMLElementCollection __RPC_FAR * This,
            /* [in][optional] */ VARIANT var1,
            /* [in][optional] */ VARIANT var2,
            /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        END_INTERFACE
    } IXMLElementCollectionVtbl;

    interface IXMLElementCollection
    {
        CONST_VTBL struct IXMLElementCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLElementCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLElementCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLElementCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLElementCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLElementCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLElementCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLElementCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLElementCollection_put_length(This,v)	\
    (This)->lpVtbl -> put_length(This,v)

#define IXMLElementCollection_get_length(This,p)	\
    (This)->lpVtbl -> get_length(This,p)

#define IXMLElementCollection_get__newEnum(This,ppUnk)	\
    (This)->lpVtbl -> get__newEnum(This,ppUnk)

#define IXMLElementCollection_item(This,var1,var2,ppDisp)	\
    (This)->lpVtbl -> item(This,var1,var2,ppDisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][hidden][restricted][propput] */ HRESULT STDMETHODCALLTYPE IXMLElementCollection_put_length_Proxy( 
    IXMLElementCollection __RPC_FAR * This,
    /* [in] */ long v);


void __RPC_STUB IXMLElementCollection_put_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElementCollection_get_length_Proxy( 
    IXMLElementCollection __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *p);


void __RPC_STUB IXMLElementCollection_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLElementCollection_get__newEnum_Proxy( 
    IXMLElementCollection __RPC_FAR * This,
    /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IXMLElementCollection_get__newEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElementCollection_item_Proxy( 
    IXMLElementCollection __RPC_FAR * This,
    /* [in][optional] */ VARIANT var1,
    /* [in][optional] */ VARIANT var2,
    /* [out][retval] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IXMLElementCollection_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLElementCollection_INTERFACE_DEFINED__ */


#ifndef __IXMLDocument_INTERFACE_DEFINED__
#define __IXMLDocument_INTERFACE_DEFINED__

/* interface IXMLDocument */
/* [helpstring][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F52E2B61-18A1-11d1-B105-00805F49916B")
    IXMLDocument : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_root( 
            /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_fileSize( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_fileModifiedDate( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_fileUpdatedDate( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_mimeType( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_readyState( 
            /* [out][retval] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_charset( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_charset( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_version( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_doctype( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_dtdURL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createElement( 
            /* [in] */ VARIANT vType,
            /* [in][optional] */ VARIANT var1,
            /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *ppElem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLDocument __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_root )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileSize )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileModifiedDate )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileUpdatedDate )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URL )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URL )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_mimeType )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_readyState )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *pl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_charset )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_charset )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_version )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_doctype )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dtdURL )( 
            IXMLDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createElement )( 
            IXMLDocument __RPC_FAR * This,
            /* [in] */ VARIANT vType,
            /* [in][optional] */ VARIANT var1,
            /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *ppElem);
        
        END_INTERFACE
    } IXMLDocumentVtbl;

    interface IXMLDocument
    {
        CONST_VTBL struct IXMLDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLDocument_get_root(This,p)	\
    (This)->lpVtbl -> get_root(This,p)

#define IXMLDocument_get_fileSize(This,p)	\
    (This)->lpVtbl -> get_fileSize(This,p)

#define IXMLDocument_get_fileModifiedDate(This,p)	\
    (This)->lpVtbl -> get_fileModifiedDate(This,p)

#define IXMLDocument_get_fileUpdatedDate(This,p)	\
    (This)->lpVtbl -> get_fileUpdatedDate(This,p)

#define IXMLDocument_get_URL(This,p)	\
    (This)->lpVtbl -> get_URL(This,p)

#define IXMLDocument_put_URL(This,p)	\
    (This)->lpVtbl -> put_URL(This,p)

#define IXMLDocument_get_mimeType(This,p)	\
    (This)->lpVtbl -> get_mimeType(This,p)

#define IXMLDocument_get_readyState(This,pl)	\
    (This)->lpVtbl -> get_readyState(This,pl)

#define IXMLDocument_get_charset(This,p)	\
    (This)->lpVtbl -> get_charset(This,p)

#define IXMLDocument_put_charset(This,p)	\
    (This)->lpVtbl -> put_charset(This,p)

#define IXMLDocument_get_version(This,p)	\
    (This)->lpVtbl -> get_version(This,p)

#define IXMLDocument_get_doctype(This,p)	\
    (This)->lpVtbl -> get_doctype(This,p)

#define IXMLDocument_get_dtdURL(This,p)	\
    (This)->lpVtbl -> get_dtdURL(This,p)

#define IXMLDocument_createElement(This,vType,var1,ppElem)	\
    (This)->lpVtbl -> createElement(This,vType,var1,ppElem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_root_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_root_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_fileSize_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_fileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_fileModifiedDate_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_fileModifiedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_fileUpdatedDate_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_fileUpdatedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_URL_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument_put_URL_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument_put_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_mimeType_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_mimeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_readyState_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *pl);


void __RPC_STUB IXMLDocument_get_readyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_charset_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_charset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument_put_charset_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument_put_charset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_version_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_doctype_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_doctype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument_get_dtdURL_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument_get_dtdURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDocument_createElement_Proxy( 
    IXMLDocument __RPC_FAR * This,
    /* [in] */ VARIANT vType,
    /* [in][optional] */ VARIANT var1,
    /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *ppElem);


void __RPC_STUB IXMLDocument_createElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLDocument_INTERFACE_DEFINED__ */


#ifndef __IXMLDocument2_INTERFACE_DEFINED__
#define __IXMLDocument2_INTERFACE_DEFINED__

/* interface IXMLDocument2 */
/* [hidden][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLDocument2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B8DE2FE-8D2D-11d1-B2FC-00C04FD915A9")
    IXMLDocument2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_root( 
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_fileSize( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_fileModifiedDate( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_fileUpdatedDate( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_mimeType( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_readyState( 
            /* [out][retval] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_charset( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_charset( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_version( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_doctype( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get_dtdURL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createElement( 
            /* [in] */ VARIANT vType,
            /* [in][optional] */ VARIANT var1,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppElem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_async( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_async( 
            /* [in] */ VARIANT_BOOL f) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLDocument2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLDocument2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLDocument2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_root )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileSize )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileModifiedDate )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileUpdatedDate )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URL )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URL )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_mimeType )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_readyState )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *pl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_charset )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_charset )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_version )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_doctype )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dtdURL )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createElement )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT vType,
            /* [in][optional] */ VARIANT var1,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppElem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_async )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_async )( 
            IXMLDocument2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL f);
        
        END_INTERFACE
    } IXMLDocument2Vtbl;

    interface IXMLDocument2
    {
        CONST_VTBL struct IXMLDocument2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLDocument2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLDocument2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLDocument2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLDocument2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLDocument2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLDocument2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLDocument2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLDocument2_get_root(This,p)	\
    (This)->lpVtbl -> get_root(This,p)

#define IXMLDocument2_get_fileSize(This,p)	\
    (This)->lpVtbl -> get_fileSize(This,p)

#define IXMLDocument2_get_fileModifiedDate(This,p)	\
    (This)->lpVtbl -> get_fileModifiedDate(This,p)

#define IXMLDocument2_get_fileUpdatedDate(This,p)	\
    (This)->lpVtbl -> get_fileUpdatedDate(This,p)

#define IXMLDocument2_get_URL(This,p)	\
    (This)->lpVtbl -> get_URL(This,p)

#define IXMLDocument2_put_URL(This,p)	\
    (This)->lpVtbl -> put_URL(This,p)

#define IXMLDocument2_get_mimeType(This,p)	\
    (This)->lpVtbl -> get_mimeType(This,p)

#define IXMLDocument2_get_readyState(This,pl)	\
    (This)->lpVtbl -> get_readyState(This,pl)

#define IXMLDocument2_get_charset(This,p)	\
    (This)->lpVtbl -> get_charset(This,p)

#define IXMLDocument2_put_charset(This,p)	\
    (This)->lpVtbl -> put_charset(This,p)

#define IXMLDocument2_get_version(This,p)	\
    (This)->lpVtbl -> get_version(This,p)

#define IXMLDocument2_get_doctype(This,p)	\
    (This)->lpVtbl -> get_doctype(This,p)

#define IXMLDocument2_get_dtdURL(This,p)	\
    (This)->lpVtbl -> get_dtdURL(This,p)

#define IXMLDocument2_createElement(This,vType,var1,ppElem)	\
    (This)->lpVtbl -> createElement(This,vType,var1,ppElem)

#define IXMLDocument2_get_async(This,pf)	\
    (This)->lpVtbl -> get_async(This,pf)

#define IXMLDocument2_put_async(This,f)	\
    (This)->lpVtbl -> put_async(This,f)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_root_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_root_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_fileSize_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_fileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_fileModifiedDate_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_fileModifiedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_fileUpdatedDate_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_fileUpdatedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_URL_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_put_URL_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument2_put_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_mimeType_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_mimeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_readyState_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *pl);


void __RPC_STUB IXMLDocument2_get_readyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_charset_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_charset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_put_charset_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument2_put_charset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_version_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_doctype_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_doctype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_dtdURL_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2_get_dtdURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_createElement_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [in] */ VARIANT vType,
    /* [in][optional] */ VARIANT var1,
    /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppElem);


void __RPC_STUB IXMLDocument2_createElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_get_async_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf);


void __RPC_STUB IXMLDocument2_get_async_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2_put_async_Proxy( 
    IXMLDocument2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL f);


void __RPC_STUB IXMLDocument2_put_async_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLDocument2_INTERFACE_DEFINED__ */


#ifndef __IXMLElement_INTERFACE_DEFINED__
#define __IXMLElement_INTERFACE_DEFINED__

/* interface IXMLElement */
/* [helpstring][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F7F31AC-E15F-11d0-9C25-00C04FC99C8E")
    IXMLElement : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tagName( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_tagName( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *ppParent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT PropertyValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [out][retval] */ VARIANT __RPC_FAR *PropertyValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeAttribute( 
            /* [in] */ BSTR strPropertyName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_children( 
            /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [out][retval] */ long __RPC_FAR *plType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_text( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_text( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addChild( 
            /* [in] */ IXMLElement __RPC_FAR *pChildElem,
            long lIndex,
            long lReserved) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeChild( 
            /* [in] */ IXMLElement __RPC_FAR *pChildElem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tagName )( 
            IXMLElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tagName )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IXMLElement __RPC_FAR * This,
            /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *ppParent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT PropertyValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [out][retval] */ VARIANT __RPC_FAR *PropertyValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IXMLElement __RPC_FAR * This,
            /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IXMLElement __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_text )( 
            IXMLElement __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_text )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addChild )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ IXMLElement __RPC_FAR *pChildElem,
            long lIndex,
            long lReserved);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeChild )( 
            IXMLElement __RPC_FAR * This,
            /* [in] */ IXMLElement __RPC_FAR *pChildElem);
        
        END_INTERFACE
    } IXMLElementVtbl;

    interface IXMLElement
    {
        CONST_VTBL struct IXMLElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLElement_get_tagName(This,p)	\
    (This)->lpVtbl -> get_tagName(This,p)

#define IXMLElement_put_tagName(This,p)	\
    (This)->lpVtbl -> put_tagName(This,p)

#define IXMLElement_get_parent(This,ppParent)	\
    (This)->lpVtbl -> get_parent(This,ppParent)

#define IXMLElement_setAttribute(This,strPropertyName,PropertyValue)	\
    (This)->lpVtbl -> setAttribute(This,strPropertyName,PropertyValue)

#define IXMLElement_getAttribute(This,strPropertyName,PropertyValue)	\
    (This)->lpVtbl -> getAttribute(This,strPropertyName,PropertyValue)

#define IXMLElement_removeAttribute(This,strPropertyName)	\
    (This)->lpVtbl -> removeAttribute(This,strPropertyName)

#define IXMLElement_get_children(This,pp)	\
    (This)->lpVtbl -> get_children(This,pp)

#define IXMLElement_get_type(This,plType)	\
    (This)->lpVtbl -> get_type(This,plType)

#define IXMLElement_get_text(This,p)	\
    (This)->lpVtbl -> get_text(This,p)

#define IXMLElement_put_text(This,p)	\
    (This)->lpVtbl -> put_text(This,p)

#define IXMLElement_addChild(This,pChildElem,lIndex,lReserved)	\
    (This)->lpVtbl -> addChild(This,pChildElem,lIndex,lReserved)

#define IXMLElement_removeChild(This,pChildElem)	\
    (This)->lpVtbl -> removeChild(This,pChildElem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement_get_tagName_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLElement_get_tagName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLElement_put_tagName_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLElement_put_tagName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement_get_parent_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [out][retval] */ IXMLElement __RPC_FAR *__RPC_FAR *ppParent);


void __RPC_STUB IXMLElement_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement_setAttribute_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [in] */ VARIANT PropertyValue);


void __RPC_STUB IXMLElement_setAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement_getAttribute_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [out][retval] */ VARIANT __RPC_FAR *PropertyValue);


void __RPC_STUB IXMLElement_getAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement_removeAttribute_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName);


void __RPC_STUB IXMLElement_removeAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement_get_children_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp);


void __RPC_STUB IXMLElement_get_children_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement_get_type_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plType);


void __RPC_STUB IXMLElement_get_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement_get_text_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLElement_get_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLElement_put_text_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLElement_put_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement_addChild_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ IXMLElement __RPC_FAR *pChildElem,
    long lIndex,
    long lReserved);


void __RPC_STUB IXMLElement_addChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement_removeChild_Proxy( 
    IXMLElement __RPC_FAR * This,
    /* [in] */ IXMLElement __RPC_FAR *pChildElem);


void __RPC_STUB IXMLElement_removeChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLElement_INTERFACE_DEFINED__ */


#ifndef __IXMLElement2_INTERFACE_DEFINED__
#define __IXMLElement2_INTERFACE_DEFINED__

/* interface IXMLElement2 */
/* [helpstring][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLElement2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B8DE2FF-8D2D-11d1-B2FC-00C04FD915A9")
    IXMLElement2 : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_tagName( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_tagName( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_parent( 
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppParent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT PropertyValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [out][retval] */ VARIANT __RPC_FAR *PropertyValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeAttribute( 
            /* [in] */ BSTR strPropertyName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_children( 
            /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [out][retval] */ long __RPC_FAR *plType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_text( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_text( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addChild( 
            /* [in] */ IXMLElement2 __RPC_FAR *pChildElem,
            long lIndex,
            long lReserved) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeChild( 
            /* [in] */ IXMLElement2 __RPC_FAR *pChildElem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_attributes( 
            /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLElement2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLElement2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLElement2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tagName )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tagName )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parent )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppParent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT PropertyValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [out][retval] */ VARIANT __RPC_FAR *PropertyValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_children )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_type )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_text )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_text )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addChild )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ IXMLElement2 __RPC_FAR *pChildElem,
            long lIndex,
            long lReserved);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeChild )( 
            IXMLElement2 __RPC_FAR * This,
            /* [in] */ IXMLElement2 __RPC_FAR *pChildElem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            IXMLElement2 __RPC_FAR * This,
            /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp);
        
        END_INTERFACE
    } IXMLElement2Vtbl;

    interface IXMLElement2
    {
        CONST_VTBL struct IXMLElement2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLElement2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLElement2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLElement2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLElement2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLElement2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLElement2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLElement2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLElement2_get_tagName(This,p)	\
    (This)->lpVtbl -> get_tagName(This,p)

#define IXMLElement2_put_tagName(This,p)	\
    (This)->lpVtbl -> put_tagName(This,p)

#define IXMLElement2_get_parent(This,ppParent)	\
    (This)->lpVtbl -> get_parent(This,ppParent)

#define IXMLElement2_setAttribute(This,strPropertyName,PropertyValue)	\
    (This)->lpVtbl -> setAttribute(This,strPropertyName,PropertyValue)

#define IXMLElement2_getAttribute(This,strPropertyName,PropertyValue)	\
    (This)->lpVtbl -> getAttribute(This,strPropertyName,PropertyValue)

#define IXMLElement2_removeAttribute(This,strPropertyName)	\
    (This)->lpVtbl -> removeAttribute(This,strPropertyName)

#define IXMLElement2_get_children(This,pp)	\
    (This)->lpVtbl -> get_children(This,pp)

#define IXMLElement2_get_type(This,plType)	\
    (This)->lpVtbl -> get_type(This,plType)

#define IXMLElement2_get_text(This,p)	\
    (This)->lpVtbl -> get_text(This,p)

#define IXMLElement2_put_text(This,p)	\
    (This)->lpVtbl -> put_text(This,p)

#define IXMLElement2_addChild(This,pChildElem,lIndex,lReserved)	\
    (This)->lpVtbl -> addChild(This,pChildElem,lIndex,lReserved)

#define IXMLElement2_removeChild(This,pChildElem)	\
    (This)->lpVtbl -> removeChild(This,pChildElem)

#define IXMLElement2_get_attributes(This,pp)	\
    (This)->lpVtbl -> get_attributes(This,pp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement2_get_tagName_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLElement2_get_tagName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLElement2_put_tagName_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLElement2_put_tagName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement2_get_parent_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppParent);


void __RPC_STUB IXMLElement2_get_parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement2_setAttribute_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [in] */ VARIANT PropertyValue);


void __RPC_STUB IXMLElement2_setAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement2_getAttribute_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [out][retval] */ VARIANT __RPC_FAR *PropertyValue);


void __RPC_STUB IXMLElement2_getAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement2_removeAttribute_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName);


void __RPC_STUB IXMLElement2_removeAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement2_get_children_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp);


void __RPC_STUB IXMLElement2_get_children_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement2_get_type_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plType);


void __RPC_STUB IXMLElement2_get_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement2_get_text_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLElement2_get_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLElement2_put_text_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLElement2_put_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement2_addChild_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ IXMLElement2 __RPC_FAR *pChildElem,
    long lIndex,
    long lReserved);


void __RPC_STUB IXMLElement2_addChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLElement2_removeChild_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [in] */ IXMLElement2 __RPC_FAR *pChildElem);


void __RPC_STUB IXMLElement2_removeChild_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLElement2_get_attributes_Proxy( 
    IXMLElement2 __RPC_FAR * This,
    /* [out][retval] */ IXMLElementCollection __RPC_FAR *__RPC_FAR *pp);


void __RPC_STUB IXMLElement2_get_attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLElement2_INTERFACE_DEFINED__ */


#ifndef __IXMLAttribute_INTERFACE_DEFINED__
#define __IXMLAttribute_INTERFACE_DEFINED__

/* interface IXMLAttribute */
/* [helpstring][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLAttribute;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4D4A0FC-3B73-11d1-B2B4-00C04FB92596")
    IXMLAttribute : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [out][retval] */ BSTR __RPC_FAR *n) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_value( 
            /* [out][retval] */ BSTR __RPC_FAR *v) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLAttributeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLAttribute __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLAttribute __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLAttribute __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLAttribute __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLAttribute __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLAttribute __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLAttribute __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_name )( 
            IXMLAttribute __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *n);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_value )( 
            IXMLAttribute __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *v);
        
        END_INTERFACE
    } IXMLAttributeVtbl;

    interface IXMLAttribute
    {
        CONST_VTBL struct IXMLAttributeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLAttribute_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLAttribute_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLAttribute_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLAttribute_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLAttribute_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLAttribute_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLAttribute_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLAttribute_get_name(This,n)	\
    (This)->lpVtbl -> get_name(This,n)

#define IXMLAttribute_get_value(This,v)	\
    (This)->lpVtbl -> get_value(This,v)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLAttribute_get_name_Proxy( 
    IXMLAttribute __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *n);


void __RPC_STUB IXMLAttribute_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLAttribute_get_value_Proxy( 
    IXMLAttribute __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *v);


void __RPC_STUB IXMLAttribute_get_value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLAttribute_INTERFACE_DEFINED__ */


#ifndef __IXMLDocument2Ex_INTERFACE_DEFINED__
#define __IXMLDocument2Ex_INTERFACE_DEFINED__

/* interface IXMLDocument2Ex */
/* [unique][hidden][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLDocument2Ex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F9CF1EFE-56E0-11d1-A69C-00C04FD91555")
    IXMLDocument2Ex : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_root( 
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_fileSize( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_fileModifiedDate( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_fileUpdatedDate( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_URL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_URL( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_mimeType( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_readyState( 
            /* [out][retval] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_charset( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_charset( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_version( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_doctype( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_dtdURL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createElement( 
            /* [in] */ VARIANT vType,
            /* [in][optional] */ VARIANT var1,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppElem) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_async( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_async( 
            /* [in] */ VARIANT_BOOL f) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_root( 
            /* [in] */ IXMLElement2 __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_caseInsensitive( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_baseURL( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_baseURL( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_xml( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_xml( 
            /* [in] */ BSTR p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_lastError( 
            /* [out][retval] */ IXMLError2 __RPC_FAR *__RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_trimWhitespace( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE commit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLDocument2ExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLDocument2Ex __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLDocument2Ex __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_root )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileSize )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileModifiedDate )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_fileUpdatedDate )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_URL )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_URL )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_mimeType )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_readyState )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *pl);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_charset )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_charset )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_version )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_doctype )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dtdURL )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createElement )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ VARIANT vType,
            /* [in][optional] */ VARIANT var1,
            /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppElem);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_async )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_async )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL f);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_root )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ IXMLElement2 __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_caseInsensitive )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_baseURL )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_baseURL )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_xml )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_xml )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastError )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [out][retval] */ IXMLError2 __RPC_FAR *__RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_trimWhitespace )( 
            IXMLDocument2Ex __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *commit )( 
            IXMLDocument2Ex __RPC_FAR * This);
        
        END_INTERFACE
    } IXMLDocument2ExVtbl;

    interface IXMLDocument2Ex
    {
        CONST_VTBL struct IXMLDocument2ExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLDocument2Ex_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLDocument2Ex_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLDocument2Ex_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLDocument2Ex_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLDocument2Ex_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLDocument2Ex_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLDocument2Ex_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLDocument2Ex_get_root(This,p)	\
    (This)->lpVtbl -> get_root(This,p)

#define IXMLDocument2Ex_get_fileSize(This,p)	\
    (This)->lpVtbl -> get_fileSize(This,p)

#define IXMLDocument2Ex_get_fileModifiedDate(This,p)	\
    (This)->lpVtbl -> get_fileModifiedDate(This,p)

#define IXMLDocument2Ex_get_fileUpdatedDate(This,p)	\
    (This)->lpVtbl -> get_fileUpdatedDate(This,p)

#define IXMLDocument2Ex_get_URL(This,p)	\
    (This)->lpVtbl -> get_URL(This,p)

#define IXMLDocument2Ex_put_URL(This,p)	\
    (This)->lpVtbl -> put_URL(This,p)

#define IXMLDocument2Ex_get_mimeType(This,p)	\
    (This)->lpVtbl -> get_mimeType(This,p)

#define IXMLDocument2Ex_get_readyState(This,pl)	\
    (This)->lpVtbl -> get_readyState(This,pl)

#define IXMLDocument2Ex_get_charset(This,p)	\
    (This)->lpVtbl -> get_charset(This,p)

#define IXMLDocument2Ex_put_charset(This,p)	\
    (This)->lpVtbl -> put_charset(This,p)

#define IXMLDocument2Ex_get_version(This,p)	\
    (This)->lpVtbl -> get_version(This,p)

#define IXMLDocument2Ex_get_doctype(This,p)	\
    (This)->lpVtbl -> get_doctype(This,p)

#define IXMLDocument2Ex_get_dtdURL(This,p)	\
    (This)->lpVtbl -> get_dtdURL(This,p)

#define IXMLDocument2Ex_createElement(This,vType,var1,ppElem)	\
    (This)->lpVtbl -> createElement(This,vType,var1,ppElem)

#define IXMLDocument2Ex_get_async(This,pf)	\
    (This)->lpVtbl -> get_async(This,pf)

#define IXMLDocument2Ex_put_async(This,f)	\
    (This)->lpVtbl -> put_async(This,f)

#define IXMLDocument2Ex_put_root(This,p)	\
    (This)->lpVtbl -> put_root(This,p)

#define IXMLDocument2Ex_put_caseInsensitive(This,newVal)	\
    (This)->lpVtbl -> put_caseInsensitive(This,newVal)

#define IXMLDocument2Ex_get_baseURL(This,p)	\
    (This)->lpVtbl -> get_baseURL(This,p)

#define IXMLDocument2Ex_put_baseURL(This,p)	\
    (This)->lpVtbl -> put_baseURL(This,p)

#define IXMLDocument2Ex_get_xml(This,p)	\
    (This)->lpVtbl -> get_xml(This,p)

#define IXMLDocument2Ex_put_xml(This,p)	\
    (This)->lpVtbl -> put_xml(This,p)

#define IXMLDocument2Ex_get_lastError(This,p)	\
    (This)->lpVtbl -> get_lastError(This,p)

#define IXMLDocument2Ex_put_trimWhitespace(This,newVal)	\
    (This)->lpVtbl -> put_trimWhitespace(This,newVal)

#define IXMLDocument2Ex_commit(This)	\
    (This)->lpVtbl -> commit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_root_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_root_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_fileSize_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_fileSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_fileModifiedDate_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_fileModifiedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_fileUpdatedDate_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_fileUpdatedDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_URL_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_URL_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument2Ex_put_URL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_mimeType_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_mimeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_readyState_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *pl);


void __RPC_STUB IXMLDocument2Ex_get_readyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_charset_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_charset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_charset_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument2Ex_put_charset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_version_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_doctype_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_doctype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_dtdURL_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_dtdURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_createElement_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ VARIANT vType,
    /* [in][optional] */ VARIANT var1,
    /* [out][retval] */ IXMLElement2 __RPC_FAR *__RPC_FAR *ppElem);


void __RPC_STUB IXMLDocument2Ex_createElement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_async_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf);


void __RPC_STUB IXMLDocument2Ex_get_async_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_async_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL f);


void __RPC_STUB IXMLDocument2Ex_put_async_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_root_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ IXMLElement2 __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_put_root_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_caseInsensitive_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IXMLDocument2Ex_put_caseInsensitive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_baseURL_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_baseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_baseURL_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument2Ex_put_baseURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_xml_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_xml_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_xml_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDocument2Ex_put_xml_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_get_lastError_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [out][retval] */ IXMLError2 __RPC_FAR *__RPC_FAR *p);


void __RPC_STUB IXMLDocument2Ex_get_lastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_put_trimWhitespace_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IXMLDocument2Ex_put_trimWhitespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDocument2Ex_commit_Proxy( 
    IXMLDocument2Ex __RPC_FAR * This);


void __RPC_STUB IXMLDocument2Ex_commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLDocument2Ex_INTERFACE_DEFINED__ */


#ifndef __IXMLError_INTERFACE_DEFINED__
#define __IXMLError_INTERFACE_DEFINED__

/* interface IXMLError */
/* [helpstring][hidden][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLError;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("948C5AD3-C58D-11d0-9C0B-00C04FC99C8E")
    IXMLError : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetErrorInfo( 
            XML_ERROR __RPC_FAR *pErrorReturn) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLErrorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLError __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLError __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorInfo )( 
            IXMLError __RPC_FAR * This,
            XML_ERROR __RPC_FAR *pErrorReturn);
        
        END_INTERFACE
    } IXMLErrorVtbl;

    interface IXMLError
    {
        CONST_VTBL struct IXMLErrorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLError_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLError_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLError_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLError_GetErrorInfo(This,pErrorReturn)	\
    (This)->lpVtbl -> GetErrorInfo(This,pErrorReturn)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXMLError_GetErrorInfo_Proxy( 
    IXMLError __RPC_FAR * This,
    XML_ERROR __RPC_FAR *pErrorReturn);


void __RPC_STUB IXMLError_GetErrorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLError_INTERFACE_DEFINED__ */


#ifndef __IXMLError2_INTERFACE_DEFINED__
#define __IXMLError2_INTERFACE_DEFINED__

/* interface IXMLError2 */
/* [unique][helpstring][hidden][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLError2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12a22d96-75da-11d1-bc2a-00c04fb925f3")
    IXMLError2 : public IDispatch
    {
    public:
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_reason( 
            /* [out][retval] */ BSTR __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_line( 
            /* [out][retval] */ long __RPC_FAR *p) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_pos( 
            /* [out][retval] */ long __RPC_FAR *p) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLError2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLError2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLError2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLError2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLError2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLError2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLError2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLError2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_reason )( 
            IXMLError2 __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_line )( 
            IXMLError2 __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *p);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_pos )( 
            IXMLError2 __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *p);
        
        END_INTERFACE
    } IXMLError2Vtbl;

    interface IXMLError2
    {
        CONST_VTBL struct IXMLError2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLError2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLError2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLError2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLError2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLError2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLError2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLError2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLError2_get_reason(This,p)	\
    (This)->lpVtbl -> get_reason(This,p)

#define IXMLError2_get_line(This,p)	\
    (This)->lpVtbl -> get_line(This,p)

#define IXMLError2_get_pos(This,p)	\
    (This)->lpVtbl -> get_pos(This,p)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLError2_get_reason_Proxy( 
    IXMLError2 __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *p);


void __RPC_STUB IXMLError2_get_reason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLError2_get_line_Proxy( 
    IXMLError2 __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *p);


void __RPC_STUB IXMLError2_get_line_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IXMLError2_get_pos_Proxy( 
    IXMLError2 __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *p);


void __RPC_STUB IXMLError2_get_pos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLError2_INTERFACE_DEFINED__ */


#ifndef __IDOMNode_INTERFACE_DEFINED__
#define __IDOMNode_INTERFACE_DEFINED__

/* interface IDOMNode */
/* [unique][helpstring][nonextensible][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IDOMNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("71978480-A88F-11d1-A6B6-00C04FD91555")
    IDOMNode : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nodeType( 
            /* [out][retval] */ XMLNodeType __RPC_FAR *plType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nodeName( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nodeValue( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_nodeValue( 
            /* [in] */ BSTR bstrVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_parentNode( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getAttribute( 
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *pvarVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setAttribute( 
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT bstrVal,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeAttribute( 
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_specified( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbool) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE insertNode( 
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [in][optional] */ VARIANT After,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeNode( 
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE replaceNode( 
            /* [in] */ IDOMNode __RPC_FAR *pOld,
            /* [in] */ IDOMNode __RPC_FAR *pNew,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_attributes( 
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_childNodes( 
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDOMNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDOMNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDOMNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDOMNode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ XMLNodeType __RPC_FAR *plType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeValue )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeValue )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *pvarVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT bstrVal,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_specified )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertNode )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [in][optional] */ VARIANT After,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeNode )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceNode )( 
            IDOMNode __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pOld,
            /* [in] */ IDOMNode __RPC_FAR *pNew,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            IDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        END_INTERFACE
    } IDOMNodeVtbl;

    interface IDOMNode
    {
        CONST_VTBL struct IDOMNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDOMNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDOMNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDOMNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDOMNode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDOMNode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDOMNode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDOMNode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDOMNode_get_nodeType(This,plType)	\
    (This)->lpVtbl -> get_nodeType(This,plType)

#define IDOMNode_get_nodeName(This,pbstrName)	\
    (This)->lpVtbl -> get_nodeName(This,pbstrName)

#define IDOMNode_get_nodeValue(This,pbstrVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pbstrVal)

#define IDOMNode_put_nodeValue(This,bstrVal)	\
    (This)->lpVtbl -> put_nodeValue(This,bstrVal)

#define IDOMNode_get_parentNode(This,ppNode)	\
    (This)->lpVtbl -> get_parentNode(This,ppNode)

#define IDOMNode_getAttribute(This,bstrName,NameSpaceDecl,pvarVal)	\
    (This)->lpVtbl -> getAttribute(This,bstrName,NameSpaceDecl,pvarVal)

#define IDOMNode_setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)

#define IDOMNode_removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)

#define IDOMNode_get_specified(This,pbool)	\
    (This)->lpVtbl -> get_specified(This,pbool)

#define IDOMNode_insertNode(This,pChild,After,ppNode)	\
    (This)->lpVtbl -> insertNode(This,pChild,After,ppNode)

#define IDOMNode_removeNode(This,pChild,ppNode)	\
    (This)->lpVtbl -> removeNode(This,pChild,ppNode)

#define IDOMNode_replaceNode(This,pOld,pNew,ppNode)	\
    (This)->lpVtbl -> replaceNode(This,pOld,pNew,ppNode)

#define IDOMNode_get_attributes(This,ppNodeList)	\
    (This)->lpVtbl -> get_attributes(This,ppNodeList)

#define IDOMNode_get_childNodes(This,ppNodeList)	\
    (This)->lpVtbl -> get_childNodes(This,ppNodeList)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_nodeType_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ XMLNodeType __RPC_FAR *plType);


void __RPC_STUB IDOMNode_get_nodeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_nodeName_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IDOMNode_get_nodeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_nodeValue_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrVal);


void __RPC_STUB IDOMNode_get_nodeValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDOMNode_put_nodeValue_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ BSTR bstrVal);


void __RPC_STUB IDOMNode_put_nodeValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_parentNode_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNode_get_parentNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNode_getAttribute_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ VARIANT __RPC_FAR *pvarVal);


void __RPC_STUB IDOMNode_getAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNode_setAttribute_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in] */ VARIANT bstrVal,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);


void __RPC_STUB IDOMNode_setAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNode_removeAttribute_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ BSTR bstrName,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);


void __RPC_STUB IDOMNode_removeAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_specified_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbool);


void __RPC_STUB IDOMNode_get_specified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNode_insertNode_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ IDOMNode __RPC_FAR *pChild,
    /* [in][optional] */ VARIANT After,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNode_insertNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNode_removeNode_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ IDOMNode __RPC_FAR *pChild,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNode_removeNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNode_replaceNode_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [in] */ IDOMNode __RPC_FAR *pOld,
    /* [in] */ IDOMNode __RPC_FAR *pNew,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNode_replaceNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_attributes_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);


void __RPC_STUB IDOMNode_get_attributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNode_get_childNodes_Proxy( 
    IDOMNode __RPC_FAR * This,
    /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);


void __RPC_STUB IDOMNode_get_childNodes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDOMNode_INTERFACE_DEFINED__ */


#ifndef __IDOMNodeList_INTERFACE_DEFINED__
#define __IDOMNodeList_INTERFACE_DEFINED__

/* interface IDOMNodeList */
/* [unique][helpstring][nonextensible][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IDOMNodeList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("71978481-A88F-11d1-A6B6-00C04FD91555")
    IDOMNodeList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_length( 
            /* [out][retval] */ long __RPC_FAR *plLength) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE item( 
            /* [in] */ long index,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE nextNode( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE currentNode( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE previousNode( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE moveTo( 
            /* [in] */ long lIndex,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE moveToNode( 
            /* [in] */ IDOMNode __RPC_FAR *pNode,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__newEnum( 
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDOMNodeListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDOMNodeList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDOMNodeList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDOMNodeList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_length )( 
            IDOMNodeList __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plLength);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *item )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ long index,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *nextNode )( 
            IDOMNodeList __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *currentNode )( 
            IDOMNodeList __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *previousNode )( 
            IDOMNodeList __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *moveTo )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *moveToNode )( 
            IDOMNodeList __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pNode,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [id][hidden][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__newEnum )( 
            IDOMNodeList __RPC_FAR * This,
            /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        END_INTERFACE
    } IDOMNodeListVtbl;

    interface IDOMNodeList
    {
        CONST_VTBL struct IDOMNodeListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDOMNodeList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDOMNodeList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDOMNodeList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDOMNodeList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDOMNodeList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDOMNodeList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDOMNodeList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDOMNodeList_get_length(This,plLength)	\
    (This)->lpVtbl -> get_length(This,plLength)

#define IDOMNodeList_item(This,index,ppNode)	\
    (This)->lpVtbl -> item(This,index,ppNode)

#define IDOMNodeList_nextNode(This,ppNode)	\
    (This)->lpVtbl -> nextNode(This,ppNode)

#define IDOMNodeList_currentNode(This,ppNode)	\
    (This)->lpVtbl -> currentNode(This,ppNode)

#define IDOMNodeList_previousNode(This,ppNode)	\
    (This)->lpVtbl -> previousNode(This,ppNode)

#define IDOMNodeList_moveTo(This,lIndex,ppNode)	\
    (This)->lpVtbl -> moveTo(This,lIndex,ppNode)

#define IDOMNodeList_moveToNode(This,pNode,ppNode)	\
    (This)->lpVtbl -> moveToNode(This,pNode,ppNode)

#define IDOMNodeList_get__newEnum(This,ppUnk)	\
    (This)->lpVtbl -> get__newEnum(This,ppUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_get_length_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plLength);


void __RPC_STUB IDOMNodeList_get_length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_item_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [in] */ long index,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNodeList_item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_nextNode_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNodeList_nextNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_currentNode_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNodeList_currentNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_previousNode_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNodeList_previousNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_moveTo_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNodeList_moveTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_moveToNode_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [in] */ IDOMNode __RPC_FAR *pNode,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMNodeList_moveToNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden][restricted][propget] */ HRESULT STDMETHODCALLTYPE IDOMNodeList_get__newEnum_Proxy( 
    IDOMNodeList __RPC_FAR * This,
    /* [out][retval] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IDOMNodeList_get__newEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDOMNodeList_INTERFACE_DEFINED__ */


#ifndef __IDOMDocument_INTERFACE_DEFINED__
#define __IDOMDocument_INTERFACE_DEFINED__

/* interface IDOMDocument */
/* [unique][helpstring][nonextensible][oleautomation][hidden][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IDOMDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("09b75a24-6bb5-11d1-bc29-00c04fb925f3")
    IDOMDocument : public IDOMNode
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_documentType( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_documentNode( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_documentNode( 
            /* [in] */ VARIANT varNode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE createNode( 
            /* [in] */ XMLNodeType lType,
            /* [in][optional] */ BSTR bstrText,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDOMDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDOMDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDOMDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDOMDocument __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ XMLNodeType __RPC_FAR *plType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeValue )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeValue )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *pvarVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT bstrVal,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_specified )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [in][optional] */ VARIANT After,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pOld,
            /* [in] */ IDOMNode __RPC_FAR *pNew,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_documentType )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_documentNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_documentNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ VARIANT varNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createNode )( 
            IDOMDocument __RPC_FAR * This,
            /* [in] */ XMLNodeType lType,
            /* [in][optional] */ BSTR bstrText,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        END_INTERFACE
    } IDOMDocumentVtbl;

    interface IDOMDocument
    {
        CONST_VTBL struct IDOMDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDOMDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDOMDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDOMDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDOMDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDOMDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDOMDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDOMDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDOMDocument_get_nodeType(This,plType)	\
    (This)->lpVtbl -> get_nodeType(This,plType)

#define IDOMDocument_get_nodeName(This,pbstrName)	\
    (This)->lpVtbl -> get_nodeName(This,pbstrName)

#define IDOMDocument_get_nodeValue(This,pbstrVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pbstrVal)

#define IDOMDocument_put_nodeValue(This,bstrVal)	\
    (This)->lpVtbl -> put_nodeValue(This,bstrVal)

#define IDOMDocument_get_parentNode(This,ppNode)	\
    (This)->lpVtbl -> get_parentNode(This,ppNode)

#define IDOMDocument_getAttribute(This,bstrName,NameSpaceDecl,pvarVal)	\
    (This)->lpVtbl -> getAttribute(This,bstrName,NameSpaceDecl,pvarVal)

#define IDOMDocument_setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)

#define IDOMDocument_removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)

#define IDOMDocument_get_specified(This,pbool)	\
    (This)->lpVtbl -> get_specified(This,pbool)

#define IDOMDocument_insertNode(This,pChild,After,ppNode)	\
    (This)->lpVtbl -> insertNode(This,pChild,After,ppNode)

#define IDOMDocument_removeNode(This,pChild,ppNode)	\
    (This)->lpVtbl -> removeNode(This,pChild,ppNode)

#define IDOMDocument_replaceNode(This,pOld,pNew,ppNode)	\
    (This)->lpVtbl -> replaceNode(This,pOld,pNew,ppNode)

#define IDOMDocument_get_attributes(This,ppNodeList)	\
    (This)->lpVtbl -> get_attributes(This,ppNodeList)

#define IDOMDocument_get_childNodes(This,ppNodeList)	\
    (This)->lpVtbl -> get_childNodes(This,ppNodeList)


#define IDOMDocument_get_documentType(This,ppNode)	\
    (This)->lpVtbl -> get_documentType(This,ppNode)

#define IDOMDocument_get_documentNode(This,ppNode)	\
    (This)->lpVtbl -> get_documentNode(This,ppNode)

#define IDOMDocument_put_documentNode(This,varNode)	\
    (This)->lpVtbl -> put_documentNode(This,varNode)

#define IDOMDocument_createNode(This,lType,bstrText,NameSpaceDecl,ppNode)	\
    (This)->lpVtbl -> createNode(This,lType,bstrText,NameSpaceDecl,ppNode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMDocument_get_documentType_Proxy( 
    IDOMDocument __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMDocument_get_documentType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMDocument_get_documentNode_Proxy( 
    IDOMDocument __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMDocument_get_documentNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDOMDocument_put_documentNode_Proxy( 
    IDOMDocument __RPC_FAR * This,
    /* [in] */ VARIANT varNode);


void __RPC_STUB IDOMDocument_put_documentNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDOMDocument_createNode_Proxy( 
    IDOMDocument __RPC_FAR * This,
    /* [in] */ XMLNodeType lType,
    /* [in][optional] */ BSTR bstrText,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IDOMDocument_createNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDOMDocument_INTERFACE_DEFINED__ */


#ifndef __IDOMError_INTERFACE_DEFINED__
#define __IDOMError_INTERFACE_DEFINED__

/* interface IDOMError */
/* [unique][helpstring][nonextensible][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IDOMError;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d0402a96-7662-11d1-bc2a-00c04fb925f3")
    IDOMError : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_errorCode( 
            /* [out][retval] */ ULONG __RPC_FAR *pulErrorCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_url( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrUrl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_reason( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrReason) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_srcText( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrText) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_line( 
            /* [out][retval] */ long __RPC_FAR *plLine) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_linepos( 
            /* [out][retval] */ long __RPC_FAR *plLinePos) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_filepos( 
            /* [out][retval] */ long __RPC_FAR *plFilePos) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDOMErrorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDOMError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDOMError __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDOMError __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDOMError __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDOMError __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDOMError __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDOMError __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_errorCode )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ ULONG __RPC_FAR *pulErrorCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_url )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrUrl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_reason )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrReason);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_srcText )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_line )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plLine);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_linepos )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plLinePos);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_filepos )( 
            IDOMError __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plFilePos);
        
        END_INTERFACE
    } IDOMErrorVtbl;

    interface IDOMError
    {
        CONST_VTBL struct IDOMErrorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDOMError_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDOMError_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDOMError_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDOMError_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDOMError_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDOMError_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDOMError_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDOMError_get_errorCode(This,pulErrorCode)	\
    (This)->lpVtbl -> get_errorCode(This,pulErrorCode)

#define IDOMError_get_url(This,pbstrUrl)	\
    (This)->lpVtbl -> get_url(This,pbstrUrl)

#define IDOMError_get_reason(This,pbstrReason)	\
    (This)->lpVtbl -> get_reason(This,pbstrReason)

#define IDOMError_get_srcText(This,pbstrText)	\
    (This)->lpVtbl -> get_srcText(This,pbstrText)

#define IDOMError_get_line(This,plLine)	\
    (This)->lpVtbl -> get_line(This,plLine)

#define IDOMError_get_linepos(This,plLinePos)	\
    (This)->lpVtbl -> get_linepos(This,plLinePos)

#define IDOMError_get_filepos(This,plFilePos)	\
    (This)->lpVtbl -> get_filepos(This,plFilePos)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_errorCode_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ ULONG __RPC_FAR *pulErrorCode);


void __RPC_STUB IDOMError_get_errorCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_url_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrUrl);


void __RPC_STUB IDOMError_get_url_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_reason_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrReason);


void __RPC_STUB IDOMError_get_reason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_srcText_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrText);


void __RPC_STUB IDOMError_get_srcText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_line_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plLine);


void __RPC_STUB IDOMError_get_line_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_linepos_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plLinePos);


void __RPC_STUB IDOMError_get_linepos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDOMError_get_filepos_Proxy( 
    IDOMError __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plFilePos);


void __RPC_STUB IDOMError_get_filepos_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDOMError_INTERFACE_DEFINED__ */


#ifndef __IXMLDOMNode_INTERFACE_DEFINED__
#define __IXMLDOMNode_INTERFACE_DEFINED__

/* interface IXMLDOMNode */
/* [unique][helpstring][nonextensible][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLDOMNode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AB9CD7D0-C05A-11d1-B1BF-00C04F983E60")
    IXMLDOMNode : public IDOMNode
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_definition( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_qualifiedNodeName( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nameSpace( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nodeTypedValue( 
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_nodeTypedValue( 
            /* [in] */ VARIANT TypedValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTypedAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setTypedAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT TypedValue,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dataType( 
            /* [out][retval] */ VARIANT __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dataType( 
            /* [in] */ BSTR p) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLDOMNodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLDOMNode __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLDOMNode __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ XMLNodeType __RPC_FAR *plType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeValue )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeValue )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *pvarVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT bstrVal,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_specified )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertNode )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [in][optional] */ VARIANT After,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeNode )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceNode )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pOld,
            /* [in] */ IDOMNode __RPC_FAR *pNew,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_definition )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_qualifiedNodeName )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nameSpace )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeTypedValue )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeTypedValue )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ VARIANT TypedValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTypedAttribute )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTypedAttribute )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT TypedValue,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dataType )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [out][retval] */ VARIANT __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dataType )( 
            IXMLDOMNode __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        END_INTERFACE
    } IXMLDOMNodeVtbl;

    interface IXMLDOMNode
    {
        CONST_VTBL struct IXMLDOMNodeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLDOMNode_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLDOMNode_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLDOMNode_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLDOMNode_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLDOMNode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLDOMNode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLDOMNode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLDOMNode_get_nodeType(This,plType)	\
    (This)->lpVtbl -> get_nodeType(This,plType)

#define IXMLDOMNode_get_nodeName(This,pbstrName)	\
    (This)->lpVtbl -> get_nodeName(This,pbstrName)

#define IXMLDOMNode_get_nodeValue(This,pbstrVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pbstrVal)

#define IXMLDOMNode_put_nodeValue(This,bstrVal)	\
    (This)->lpVtbl -> put_nodeValue(This,bstrVal)

#define IXMLDOMNode_get_parentNode(This,ppNode)	\
    (This)->lpVtbl -> get_parentNode(This,ppNode)

#define IXMLDOMNode_getAttribute(This,bstrName,NameSpaceDecl,pvarVal)	\
    (This)->lpVtbl -> getAttribute(This,bstrName,NameSpaceDecl,pvarVal)

#define IXMLDOMNode_setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)

#define IXMLDOMNode_removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)

#define IXMLDOMNode_get_specified(This,pbool)	\
    (This)->lpVtbl -> get_specified(This,pbool)

#define IXMLDOMNode_insertNode(This,pChild,After,ppNode)	\
    (This)->lpVtbl -> insertNode(This,pChild,After,ppNode)

#define IXMLDOMNode_removeNode(This,pChild,ppNode)	\
    (This)->lpVtbl -> removeNode(This,pChild,ppNode)

#define IXMLDOMNode_replaceNode(This,pOld,pNew,ppNode)	\
    (This)->lpVtbl -> replaceNode(This,pOld,pNew,ppNode)

#define IXMLDOMNode_get_attributes(This,ppNodeList)	\
    (This)->lpVtbl -> get_attributes(This,ppNodeList)

#define IXMLDOMNode_get_childNodes(This,ppNodeList)	\
    (This)->lpVtbl -> get_childNodes(This,ppNodeList)


#define IXMLDOMNode_get_definition(This,ppNode)	\
    (This)->lpVtbl -> get_definition(This,ppNode)

#define IXMLDOMNode_get_qualifiedNodeName(This,pbstrName)	\
    (This)->lpVtbl -> get_qualifiedNodeName(This,pbstrName)

#define IXMLDOMNode_get_nameSpace(This,ppNS)	\
    (This)->lpVtbl -> get_nameSpace(This,ppNS)

#define IXMLDOMNode_get_nodeTypedValue(This,TypedValue)	\
    (This)->lpVtbl -> get_nodeTypedValue(This,TypedValue)

#define IXMLDOMNode_put_nodeTypedValue(This,TypedValue)	\
    (This)->lpVtbl -> put_nodeTypedValue(This,TypedValue)

#define IXMLDOMNode_getTypedAttribute(This,strPropertyName,NameSpaceDecl,TypedValue)	\
    (This)->lpVtbl -> getTypedAttribute(This,strPropertyName,NameSpaceDecl,TypedValue)

#define IXMLDOMNode_setTypedAttribute(This,strPropertyName,TypedValue,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> setTypedAttribute(This,strPropertyName,TypedValue,NameSpaceDecl,ppAttribute)

#define IXMLDOMNode_get_dataType(This,p)	\
    (This)->lpVtbl -> get_dataType(This,p)

#define IXMLDOMNode_put_dataType(This,p)	\
    (This)->lpVtbl -> put_dataType(This,p)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_get_definition_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IXMLDOMNode_get_definition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_get_qualifiedNodeName_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IXMLDOMNode_get_qualifiedNodeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_get_nameSpace_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNS);


void __RPC_STUB IXMLDOMNode_get_nameSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_get_nodeTypedValue_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);


void __RPC_STUB IXMLDOMNode_get_nodeTypedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_put_nodeTypedValue_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [in] */ VARIANT TypedValue);


void __RPC_STUB IXMLDOMNode_put_nodeTypedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_getTypedAttribute_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);


void __RPC_STUB IXMLDOMNode_getTypedAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_setTypedAttribute_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [in] */ VARIANT TypedValue,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);


void __RPC_STUB IXMLDOMNode_setTypedAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_get_dataType_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [out][retval] */ VARIANT __RPC_FAR *p);


void __RPC_STUB IXMLDOMNode_get_dataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDOMNode_put_dataType_Proxy( 
    IXMLDOMNode __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDOMNode_put_dataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLDOMNode_INTERFACE_DEFINED__ */


#ifndef __IXMLDOMDocument_INTERFACE_DEFINED__
#define __IXMLDOMDocument_INTERFACE_DEFINED__

/* interface IXMLDOMDocument */
/* [unique][helpstring][hidden][nonextensible][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLDOMDocument;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AB9CD7D1-C05A-11d1-B1BF-00C04F983E60")
    IXMLDOMDocument : public IDOMDocument
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE nodeFromID( 
            /* [in] */ BSTR pbstrID,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_documentNameSpaces( 
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE load( 
            /* [in] */ BSTR bstrUrl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_readyState( 
            /* [out][retval] */ long __RPC_FAR *plState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_lastError( 
            /* [out][retval] */ IDOMError __RPC_FAR *__RPC_FAR *pError) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_url( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrUrl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_async( 
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_async( 
            /* [in] */ VARIANT_BOOL f) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE abort( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE saveNode( 
            /* [in] */ IDOMNode __RPC_FAR *ppNode,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrXml) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE loadXML( 
            /* [in] */ BSTR pbstrXML) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_definition( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_qualifiedNodeName( 
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nameSpace( 
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNS) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_nodeTypedValue( 
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_nodeTypedValue( 
            /* [in] */ VARIANT TypedValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getTypedAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setTypedAttribute( 
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT TypedValue,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_dataType( 
            /* [out][retval] */ VARIANT __RPC_FAR *p) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_dataType( 
            /* [in] */ BSTR p) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLDOMDocumentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLDOMDocument __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLDOMDocument __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeType )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ XMLNodeType __RPC_FAR *plType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeName )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeValue )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeValue )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_parentNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAttribute )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *pvarVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setAttribute )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in] */ VARIANT bstrVal,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeAttribute )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_specified )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pbool);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *insertNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [in][optional] */ VARIANT After,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removeNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pChild,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *replaceNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *pOld,
            /* [in] */ IDOMNode __RPC_FAR *pNew,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_attributes )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_childNodes )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_documentType )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_documentNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_documentNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ VARIANT varNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ XMLNodeType lType,
            /* [in][optional] */ BSTR bstrText,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *nodeFromID )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR pbstrID,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_documentNameSpaces )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *load )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR bstrUrl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_readyState )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ long __RPC_FAR *plState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_lastError )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMError __RPC_FAR *__RPC_FAR *pError);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_url )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrUrl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_async )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_async )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL f);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *abort )( 
            IXMLDOMDocument __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *saveNode )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ IDOMNode __RPC_FAR *ppNode,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrXml);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *loadXML )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR pbstrXML);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_definition )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_qualifiedNodeName )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ BSTR __RPC_FAR *pbstrName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nameSpace )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNS);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_nodeTypedValue )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_nodeTypedValue )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ VARIANT TypedValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getTypedAttribute )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setTypedAttribute )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR strPropertyName,
            /* [in] */ VARIANT TypedValue,
            /* [in][optional] */ VARIANT NameSpaceDecl,
            /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_dataType )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [out][retval] */ VARIANT __RPC_FAR *p);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_dataType )( 
            IXMLDOMDocument __RPC_FAR * This,
            /* [in] */ BSTR p);
        
        END_INTERFACE
    } IXMLDOMDocumentVtbl;

    interface IXMLDOMDocument
    {
        CONST_VTBL struct IXMLDOMDocumentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLDOMDocument_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLDOMDocument_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLDOMDocument_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLDOMDocument_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLDOMDocument_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLDOMDocument_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLDOMDocument_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLDOMDocument_get_nodeType(This,plType)	\
    (This)->lpVtbl -> get_nodeType(This,plType)

#define IXMLDOMDocument_get_nodeName(This,pbstrName)	\
    (This)->lpVtbl -> get_nodeName(This,pbstrName)

#define IXMLDOMDocument_get_nodeValue(This,pbstrVal)	\
    (This)->lpVtbl -> get_nodeValue(This,pbstrVal)

#define IXMLDOMDocument_put_nodeValue(This,bstrVal)	\
    (This)->lpVtbl -> put_nodeValue(This,bstrVal)

#define IXMLDOMDocument_get_parentNode(This,ppNode)	\
    (This)->lpVtbl -> get_parentNode(This,ppNode)

#define IXMLDOMDocument_getAttribute(This,bstrName,NameSpaceDecl,pvarVal)	\
    (This)->lpVtbl -> getAttribute(This,bstrName,NameSpaceDecl,pvarVal)

#define IXMLDOMDocument_setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> setAttribute(This,bstrName,bstrVal,NameSpaceDecl,ppAttribute)

#define IXMLDOMDocument_removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> removeAttribute(This,bstrName,NameSpaceDecl,ppAttribute)

#define IXMLDOMDocument_get_specified(This,pbool)	\
    (This)->lpVtbl -> get_specified(This,pbool)

#define IXMLDOMDocument_insertNode(This,pChild,After,ppNode)	\
    (This)->lpVtbl -> insertNode(This,pChild,After,ppNode)

#define IXMLDOMDocument_removeNode(This,pChild,ppNode)	\
    (This)->lpVtbl -> removeNode(This,pChild,ppNode)

#define IXMLDOMDocument_replaceNode(This,pOld,pNew,ppNode)	\
    (This)->lpVtbl -> replaceNode(This,pOld,pNew,ppNode)

#define IXMLDOMDocument_get_attributes(This,ppNodeList)	\
    (This)->lpVtbl -> get_attributes(This,ppNodeList)

#define IXMLDOMDocument_get_childNodes(This,ppNodeList)	\
    (This)->lpVtbl -> get_childNodes(This,ppNodeList)


#define IXMLDOMDocument_get_documentType(This,ppNode)	\
    (This)->lpVtbl -> get_documentType(This,ppNode)

#define IXMLDOMDocument_get_documentNode(This,ppNode)	\
    (This)->lpVtbl -> get_documentNode(This,ppNode)

#define IXMLDOMDocument_put_documentNode(This,varNode)	\
    (This)->lpVtbl -> put_documentNode(This,varNode)

#define IXMLDOMDocument_createNode(This,lType,bstrText,NameSpaceDecl,ppNode)	\
    (This)->lpVtbl -> createNode(This,lType,bstrText,NameSpaceDecl,ppNode)


#define IXMLDOMDocument_nodeFromID(This,pbstrID,ppNode)	\
    (This)->lpVtbl -> nodeFromID(This,pbstrID,ppNode)

#define IXMLDOMDocument_get_documentNameSpaces(This,ppNodeList)	\
    (This)->lpVtbl -> get_documentNameSpaces(This,ppNodeList)

#define IXMLDOMDocument_load(This,bstrUrl)	\
    (This)->lpVtbl -> load(This,bstrUrl)

#define IXMLDOMDocument_get_readyState(This,plState)	\
    (This)->lpVtbl -> get_readyState(This,plState)

#define IXMLDOMDocument_get_lastError(This,pError)	\
    (This)->lpVtbl -> get_lastError(This,pError)

#define IXMLDOMDocument_get_url(This,pbstrUrl)	\
    (This)->lpVtbl -> get_url(This,pbstrUrl)

#define IXMLDOMDocument_get_async(This,pf)	\
    (This)->lpVtbl -> get_async(This,pf)

#define IXMLDOMDocument_put_async(This,f)	\
    (This)->lpVtbl -> put_async(This,f)

#define IXMLDOMDocument_abort(This)	\
    (This)->lpVtbl -> abort(This)

#define IXMLDOMDocument_saveNode(This,ppNode,pbstrXml)	\
    (This)->lpVtbl -> saveNode(This,ppNode,pbstrXml)

#define IXMLDOMDocument_loadXML(This,pbstrXML)	\
    (This)->lpVtbl -> loadXML(This,pbstrXML)

#define IXMLDOMDocument_get_definition(This,ppNode)	\
    (This)->lpVtbl -> get_definition(This,ppNode)

#define IXMLDOMDocument_get_qualifiedNodeName(This,pbstrName)	\
    (This)->lpVtbl -> get_qualifiedNodeName(This,pbstrName)

#define IXMLDOMDocument_get_nameSpace(This,ppNS)	\
    (This)->lpVtbl -> get_nameSpace(This,ppNS)

#define IXMLDOMDocument_get_nodeTypedValue(This,TypedValue)	\
    (This)->lpVtbl -> get_nodeTypedValue(This,TypedValue)

#define IXMLDOMDocument_put_nodeTypedValue(This,TypedValue)	\
    (This)->lpVtbl -> put_nodeTypedValue(This,TypedValue)

#define IXMLDOMDocument_getTypedAttribute(This,strPropertyName,NameSpaceDecl,TypedValue)	\
    (This)->lpVtbl -> getTypedAttribute(This,strPropertyName,NameSpaceDecl,TypedValue)

#define IXMLDOMDocument_setTypedAttribute(This,strPropertyName,TypedValue,NameSpaceDecl,ppAttribute)	\
    (This)->lpVtbl -> setTypedAttribute(This,strPropertyName,TypedValue,NameSpaceDecl,ppAttribute)

#define IXMLDOMDocument_get_dataType(This,p)	\
    (This)->lpVtbl -> get_dataType(This,p)

#define IXMLDOMDocument_put_dataType(This,p)	\
    (This)->lpVtbl -> put_dataType(This,p)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_nodeFromID_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ BSTR pbstrID,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IXMLDOMDocument_nodeFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_documentNameSpaces_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ IDOMNodeList __RPC_FAR *__RPC_FAR *ppNodeList);


void __RPC_STUB IXMLDOMDocument_get_documentNameSpaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_load_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ BSTR bstrUrl);


void __RPC_STUB IXMLDOMDocument_load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_readyState_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ long __RPC_FAR *plState);


void __RPC_STUB IXMLDOMDocument_get_readyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_lastError_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ IDOMError __RPC_FAR *__RPC_FAR *pError);


void __RPC_STUB IXMLDOMDocument_get_lastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_url_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrUrl);


void __RPC_STUB IXMLDOMDocument_get_url_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_async_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ VARIANT_BOOL __RPC_FAR *pf);


void __RPC_STUB IXMLDOMDocument_get_async_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_put_async_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL f);


void __RPC_STUB IXMLDOMDocument_put_async_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_abort_Proxy( 
    IXMLDOMDocument __RPC_FAR * This);


void __RPC_STUB IXMLDOMDocument_abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_saveNode_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ IDOMNode __RPC_FAR *ppNode,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrXml);


void __RPC_STUB IXMLDOMDocument_saveNode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_loadXML_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ BSTR pbstrXML);


void __RPC_STUB IXMLDOMDocument_loadXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_definition_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNode);


void __RPC_STUB IXMLDOMDocument_get_definition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_qualifiedNodeName_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB IXMLDOMDocument_get_qualifiedNodeName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_nameSpace_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppNS);


void __RPC_STUB IXMLDOMDocument_get_nameSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_nodeTypedValue_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);


void __RPC_STUB IXMLDOMDocument_get_nodeTypedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_put_nodeTypedValue_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ VARIANT TypedValue);


void __RPC_STUB IXMLDOMDocument_put_nodeTypedValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_getTypedAttribute_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ VARIANT __RPC_FAR *TypedValue);


void __RPC_STUB IXMLDOMDocument_getTypedAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_setTypedAttribute_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ BSTR strPropertyName,
    /* [in] */ VARIANT TypedValue,
    /* [in][optional] */ VARIANT NameSpaceDecl,
    /* [out][retval] */ IDOMNode __RPC_FAR *__RPC_FAR *ppAttribute);


void __RPC_STUB IXMLDOMDocument_setTypedAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_get_dataType_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [out][retval] */ VARIANT __RPC_FAR *p);


void __RPC_STUB IXMLDOMDocument_get_dataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IXMLDOMDocument_put_dataType_Proxy( 
    IXMLDOMDocument __RPC_FAR * This,
    /* [in] */ BSTR p);


void __RPC_STUB IXMLDOMDocument_put_dataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLDOMDocument_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_DOMDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("e54941b2-7756-11d1-bc2a-00c04fb925f3")
DOMDocument;
#endif

#ifndef __IXMLIslandPeer_INTERFACE_DEFINED__
#define __IXMLIslandPeer_INTERFACE_DEFINED__

/* interface IXMLIslandPeer */
/* [unique][helpstring][hidden][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLIslandPeer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7108ECB4-AFDC-11D1-ADC1-00805FC752D8")
    IXMLIslandPeer : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IXMLIslandPeerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLIslandPeer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLIslandPeer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLIslandPeer __RPC_FAR * This);
        
        END_INTERFACE
    } IXMLIslandPeerVtbl;

    interface IXMLIslandPeer
    {
        CONST_VTBL struct IXMLIslandPeerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLIslandPeer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLIslandPeer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLIslandPeer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXMLIslandPeer_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_XMLIslandPeer;

#ifdef __cplusplus

class DECLSPEC_UUID("379E501F-B231-11d1-ADC1-00805FC752D8")
XMLIslandPeer;
#endif

#ifndef __IXMLElementNotificationSink_INTERFACE_DEFINED__
#define __IXMLElementNotificationSink_INTERFACE_DEFINED__

/* interface IXMLElementNotificationSink */
/* [hidden][oleautomation][dual][uuid][object][local] */ 


EXTERN_C const IID IID_IXMLElementNotificationSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D9F1E15A-CCDB-11d0-9C0C-00C04FC99C8E")
    IXMLElementNotificationSink : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ChildAdded( 
            /* [in] */ IDispatch __RPC_FAR *pChildElem) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXMLElementNotificationSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXMLElementNotificationSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXMLElementNotificationSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXMLElementNotificationSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXMLElementNotificationSink __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXMLElementNotificationSink __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXMLElementNotificationSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXMLElementNotificationSink __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChildAdded )( 
            IXMLElementNotificationSink __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pChildElem);
        
        END_INTERFACE
    } IXMLElementNotificationSinkVtbl;

    interface IXMLElementNotificationSink
    {
        CONST_VTBL struct IXMLElementNotificationSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXMLElementNotificationSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXMLElementNotificationSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXMLElementNotificationSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXMLElementNotificationSink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXMLElementNotificationSink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXMLElementNotificationSink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXMLElementNotificationSink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IXMLElementNotificationSink_ChildAdded(This,pChildElem)	\
    (This)->lpVtbl -> ChildAdded(This,pChildElem)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IXMLElementNotificationSink_ChildAdded_Proxy( 
    IXMLElementNotificationSink __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pChildElem);


void __RPC_STUB IXMLElementNotificationSink_ChildAdded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXMLElementNotificationSink_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_XMLDocument;

#ifdef __cplusplus

class DECLSPEC_UUID("CFC399AF-D876-11d0-9C10-00C04FC99C8E")
XMLDocument;
#endif
#endif /* __MSXML_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

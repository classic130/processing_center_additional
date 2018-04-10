/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Feb 26 12:23:58 2000
 */
/* Compiler settings for D:\Dev\SnEnCmd\IDlFiles\VSGSEOutlook.idl:
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

#ifndef __VSGSEOutlook_h__
#define __VSGSEOutlook_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __Action_FWD_DEFINED__
#define __Action_FWD_DEFINED__
typedef interface Action Action;
#endif 	/* __Action_FWD_DEFINED__ */


#ifndef ___Application_FWD_DEFINED__
#define ___Application_FWD_DEFINED__
typedef interface _Application _Application;
#endif 	/* ___Application_FWD_DEFINED__ */


#ifndef __Actions_FWD_DEFINED__
#define __Actions_FWD_DEFINED__
typedef interface Actions Actions;
#endif 	/* __Actions_FWD_DEFINED__ */


#ifndef __NameSpace_FWD_DEFINED__
#define __NameSpace_FWD_DEFINED__
typedef interface NameSpace NameSpace;
#endif 	/* __NameSpace_FWD_DEFINED__ */


#ifndef __Recipient_FWD_DEFINED__
#define __Recipient_FWD_DEFINED__
typedef interface Recipient Recipient;
#endif 	/* __Recipient_FWD_DEFINED__ */


#ifndef __AddressLists_FWD_DEFINED__
#define __AddressLists_FWD_DEFINED__
typedef interface AddressLists AddressLists;
#endif 	/* __AddressLists_FWD_DEFINED__ */


#ifndef __AddressList_FWD_DEFINED__
#define __AddressList_FWD_DEFINED__
typedef interface AddressList AddressList;
#endif 	/* __AddressList_FWD_DEFINED__ */


#ifndef __AddressEntry_FWD_DEFINED__
#define __AddressEntry_FWD_DEFINED__
typedef interface AddressEntry AddressEntry;
#endif 	/* __AddressEntry_FWD_DEFINED__ */


#ifndef __AddressEntries_FWD_DEFINED__
#define __AddressEntries_FWD_DEFINED__
typedef interface AddressEntries AddressEntries;
#endif 	/* __AddressEntries_FWD_DEFINED__ */


#ifndef __Attachments_FWD_DEFINED__
#define __Attachments_FWD_DEFINED__
typedef interface Attachments Attachments;
#endif 	/* __Attachments_FWD_DEFINED__ */


#ifndef __Attachment_FWD_DEFINED__
#define __Attachment_FWD_DEFINED__
typedef interface Attachment Attachment;
#endif 	/* __Attachment_FWD_DEFINED__ */


#ifndef __Recipients_FWD_DEFINED__
#define __Recipients_FWD_DEFINED__
typedef interface Recipients Recipients;
#endif 	/* __Recipients_FWD_DEFINED__ */


#ifndef __FormDescription_FWD_DEFINED__
#define __FormDescription_FWD_DEFINED__
typedef interface FormDescription FormDescription;
#endif 	/* __FormDescription_FWD_DEFINED__ */


#ifndef __UserProperties_FWD_DEFINED__
#define __UserProperties_FWD_DEFINED__
typedef interface UserProperties UserProperties;
#endif 	/* __UserProperties_FWD_DEFINED__ */


#ifndef __UserProperty_FWD_DEFINED__
#define __UserProperty_FWD_DEFINED__
typedef interface UserProperty UserProperty;
#endif 	/* __UserProperty_FWD_DEFINED__ */


#ifndef __Folders_FWD_DEFINED__
#define __Folders_FWD_DEFINED__
typedef interface Folders Folders;
#endif 	/* __Folders_FWD_DEFINED__ */


#ifndef __MAPIFolder_FWD_DEFINED__
#define __MAPIFolder_FWD_DEFINED__
typedef interface MAPIFolder MAPIFolder;
#endif 	/* __MAPIFolder_FWD_DEFINED__ */


#ifndef __Items_FWD_DEFINED__
#define __Items_FWD_DEFINED__
typedef interface Items Items;
#endif 	/* __Items_FWD_DEFINED__ */


#ifndef __Explorer_FWD_DEFINED__
#define __Explorer_FWD_DEFINED__
typedef interface Explorer Explorer;
#endif 	/* __Explorer_FWD_DEFINED__ */


#ifndef __Inspector_FWD_DEFINED__
#define __Inspector_FWD_DEFINED__
typedef interface Inspector Inspector;
#endif 	/* __Inspector_FWD_DEFINED__ */


#ifndef ___MailItem_FWD_DEFINED__
#define ___MailItem_FWD_DEFINED__
typedef interface _MailItem _MailItem;
#endif 	/* ___MailItem_FWD_DEFINED__ */


#ifndef __Exceptions_FWD_DEFINED__
#define __Exceptions_FWD_DEFINED__
typedef interface Exceptions Exceptions;
#endif 	/* __Exceptions_FWD_DEFINED__ */


#ifndef __Exception_FWD_DEFINED__
#define __Exception_FWD_DEFINED__
typedef interface Exception Exception;
#endif 	/* __Exception_FWD_DEFINED__ */


#ifndef __Application_FWD_DEFINED__
#define __Application_FWD_DEFINED__

#ifdef __cplusplus
typedef class Application Application;
#else
typedef struct Application Application;
#endif /* __cplusplus */

#endif 	/* __Application_FWD_DEFINED__ */


#ifndef __MailItem_FWD_DEFINED__
#define __MailItem_FWD_DEFINED__

#ifdef __cplusplus
typedef class MailItem MailItem;
#else
typedef struct MailItem MailItem;
#endif /* __cplusplus */

#endif 	/* __MailItem_FWD_DEFINED__ */


#ifndef __ItemEvents_FWD_DEFINED__
#define __ItemEvents_FWD_DEFINED__
typedef interface ItemEvents ItemEvents;
#endif 	/* __ItemEvents_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __Outlook_LIBRARY_DEFINED__
#define __Outlook_LIBRARY_DEFINED__

/* library Outlook */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 
























typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0001
    {	olReply	= 0,
	olReplyAll	= 1,
	olForward	= 2,
	olReplyFolder	= 3,
	olRespond	= 4
    }	OlActionCopyLike;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0002
    {	olNoFlag	= 0,
	olFlagComplete	= 1,
	olFlagMarked	= 2
    }	OlFlagStatus;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0003
    {	olText	= 1,
	olNumber	= 3,
	olDateTime	= 5,
	olYesNo	= 6,
	olDuration	= 7,
	olKeywords	= 11,
	olPercent	= 12,
	olCurrency	= 14,
	olFormula	= 18,
	olCombination	= 19
    }	OlUserPropertyType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0004
    {	olImportanceLow	= 0,
	olImportanceNormal	= 1,
	olImportanceHigh	= 2
    }	OlImportance;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0005
    {	olNormal	= 0,
	olPersonal	= 1,
	olPrivate	= 2,
	olConfidential	= 3
    }	OlSensitivity;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0006
    {	olDefaultRegistry	= 0,
	olPersonalRegistry	= 2,
	olFolderRegistry	= 3,
	olOrganizationRegistry	= 4
    }	OlFormRegistry;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0007
    {	olRemoteStatusNone	= 0,
	olUnMarked	= 1,
	olMarkedForDownload	= 2,
	olMarkedForCopy	= 3,
	olMarkedForDelete	= 4
    }	OlRemoteStatus;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0008
    {	olOmitOriginalText	= 0,
	olEmbedOriginalItem	= 1,
	olIncludeOriginalText	= 2,
	olIndentOriginalText	= 3,
	olLinkOriginalItem	= 4,
	olUserPreference	= 5,
	olReplyTickOriginalText	= 1000
    }	OlActionReplyStyle;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0009
    {	olOpen	= 0,
	olSend	= 1,
	olPrompt	= 2
    }	OlActionResponseStyle;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0010
    {	olDontShow	= 0,
	olMenu	= 1,
	olMenuAndToolbar	= 2
    }	OlActionShowOn;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0011
    {	olByValue	= 1,
	olByReference	= 4,
	olEmbeddeditem	= 5,
	olOLE	= 6
    }	OlAttachmentType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0012
    {	olFree	= 0,
	olTentative	= 1,
	olBusy	= 2,
	olOutOfOffice	= 3
    }	OlBusyStatus;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0013
    {	olSave	= 0,
	olDiscard	= 1,
	olPromptForSave	= 2
    }	OlInspectorClose;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0014
    {	olUser	= 0,
	olDistList	= 1,
	olForum	= 2,
	olAgent	= 3,
	olOrganization	= 4,
	olPrivateDistList	= 5,
	olRemoteUser	= 6
    }	OlDisplayType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0015
    {	olEditorText	= 1,
	olEditorHTML	= 2,
	olEditorRTF	= 3,
	olEditorWord	= 4
    }	OlEditorType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0016
    {	olTrackingNone	= 0,
	olTrackingDelivered	= 1,
	olTrackingNotDelivered	= 2,
	olTrackingNotRead	= 3,
	olTrackingRecallFailure	= 4,
	olTrackingRecallSuccess	= 5,
	olTrackingRead	= 6,
	olTrackingReplied	= 7
    }	OlTrackingStatus;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0017
    {	olResponseNone	= 0,
	olResponseOrganized	= 1,
	olResponseTentative	= 2,
	olResponseAccepted	= 3,
	olResponseDeclined	= 4,
	olResponseNotResponded	= 5
    }	OlResponseStatus;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0018
    {	olMailItem	= 0,
	olAppointmentItem	= 1,
	olContactItem	= 2,
	olTaskItem	= 3,
	olJournalItem	= 4,
	olNoteItem	= 5,
	olPostItem	= 6
    }	OlItemType;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0019
    {	olFolderDeletedItems	= 3,
	olFolderOutbox	= 4,
	olFolderSentMail	= 5,
	olFolderInbox	= 6,
	olFolderCalendar	= 9,
	olFolderContacts	= 10,
	olFolderJournal	= 11,
	olFolderNotes	= 12,
	olFolderTasks	= 13,
	olFolderDrafts	= 16
    }	OlDefaultFolders;

typedef 
enum __MIDL___MIDL_itf_VSGSEOutlook_0000_0020
    {	olApplication	= 0,
	olNamespace	= 1,
	olFolder	= 2,
	olRecipient	= 4,
	olAttachment	= 5,
	olAddressList	= 7,
	olAddressEntry	= 8,
	olFolders	= 15,
	olItems	= 16,
	olRecipients	= 17,
	olAttachments	= 18,
	olAddressLists	= 20,
	olAddressEntries	= 21,
	olAppointment	= 26,
	olMeetingRequest	= 53,
	olMeetingCancellation	= 54,
	olMeetingResponseNegative	= 55,
	olMeetingResponsePositive	= 56,
	olMeetingResponseTentative	= 57,
	olRecurrencePattern	= 28,
	olExceptions	= 29,
	olException	= 30,
	olAction	= 32,
	olActions	= 33,
	olExplorer	= 34,
	olInspector	= 35,
	olPages	= 36,
	olFormDescription	= 37,
	olUserProperties	= 38,
	olUserProperty	= 39,
	olContact	= 40,
	olDocument	= 41,
	olJournal	= 42,
	olMail	= 43,
	olNote	= 44,
	olPost	= 45,
	olReport	= 46,
	olRemote	= 47,
	olTask	= 48,
	olTaskRequest	= 49,
	olTaskRequestUpdate	= 50,
	olTaskRequestAccept	= 51,
	olTaskRequestDecline	= 52
    }	OlObjectClass;


DEFINE_GUID(LIBID_Outlook,0x00062FFF,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#ifndef __Action_INTERFACE_DEFINED__
#define __Action_INTERFACE_DEFINED__

/* interface Action */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Action,0x00063043,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063043-0000-0000-C000-000000000046")
    Action : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CopyLike( 
            /* [retval][out] */ OlActionCopyLike __RPC_FAR *CopyLike) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_CopyLike( 
            /* [in] */ OlActionCopyLike CopyLike) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_MessageClass( 
            /* [retval][out] */ BSTR __RPC_FAR *MessageClass) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_MessageClass( 
            /* [in] */ BSTR MessageClass) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Prefix( 
            /* [retval][out] */ BSTR __RPC_FAR *Prefix) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Prefix( 
            /* [in] */ BSTR Prefix) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReplyStyle( 
            /* [retval][out] */ OlActionReplyStyle __RPC_FAR *ReplyStyle) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReplyStyle( 
            /* [in] */ OlActionReplyStyle ReplyStyle) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ResponseStyle( 
            /* [retval][out] */ OlActionResponseStyle __RPC_FAR *ResponseStyle) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ResponseStyle( 
            /* [in] */ OlActionResponseStyle ResponseStyle) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ShowOn( 
            /* [retval][out] */ OlActionShowOn __RPC_FAR *ShowOn) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ShowOn( 
            /* [in] */ OlActionShowOn ShowOn) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Execute( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ActionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Action __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Action __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Action __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Action __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Action __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Action __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Action __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CopyLike )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ OlActionCopyLike __RPC_FAR *CopyLike);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CopyLike )( 
            Action __RPC_FAR * This,
            /* [in] */ OlActionCopyLike CopyLike);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            Action __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageClass )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *MessageClass);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MessageClass )( 
            Action __RPC_FAR * This,
            /* [in] */ BSTR MessageClass);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            Action __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Prefix )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Prefix);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Prefix )( 
            Action __RPC_FAR * This,
            /* [in] */ BSTR Prefix);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReplyStyle )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ OlActionReplyStyle __RPC_FAR *ReplyStyle);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReplyStyle )( 
            Action __RPC_FAR * This,
            /* [in] */ OlActionReplyStyle ReplyStyle);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResponseStyle )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ OlActionResponseStyle __RPC_FAR *ResponseStyle);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ResponseStyle )( 
            Action __RPC_FAR * This,
            /* [in] */ OlActionResponseStyle ResponseStyle);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowOn )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ OlActionShowOn __RPC_FAR *ShowOn);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowOn )( 
            Action __RPC_FAR * This,
            /* [in] */ OlActionShowOn ShowOn);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            Action __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Execute )( 
            Action __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        END_INTERFACE
    } ActionVtbl;

    interface Action
    {
        CONST_VTBL struct ActionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Action_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Action_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Action_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Action_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Action_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Action_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Action_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Action_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Action_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Action_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Action_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Action_get_CopyLike(This,CopyLike)	\
    (This)->lpVtbl -> get_CopyLike(This,CopyLike)

#define Action_put_CopyLike(This,CopyLike)	\
    (This)->lpVtbl -> put_CopyLike(This,CopyLike)

#define Action_get_Enabled(This,Enabled)	\
    (This)->lpVtbl -> get_Enabled(This,Enabled)

#define Action_put_Enabled(This,Enabled)	\
    (This)->lpVtbl -> put_Enabled(This,Enabled)

#define Action_get_MessageClass(This,MessageClass)	\
    (This)->lpVtbl -> get_MessageClass(This,MessageClass)

#define Action_put_MessageClass(This,MessageClass)	\
    (This)->lpVtbl -> put_MessageClass(This,MessageClass)

#define Action_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define Action_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define Action_get_Prefix(This,Prefix)	\
    (This)->lpVtbl -> get_Prefix(This,Prefix)

#define Action_put_Prefix(This,Prefix)	\
    (This)->lpVtbl -> put_Prefix(This,Prefix)

#define Action_get_ReplyStyle(This,ReplyStyle)	\
    (This)->lpVtbl -> get_ReplyStyle(This,ReplyStyle)

#define Action_put_ReplyStyle(This,ReplyStyle)	\
    (This)->lpVtbl -> put_ReplyStyle(This,ReplyStyle)

#define Action_get_ResponseStyle(This,ResponseStyle)	\
    (This)->lpVtbl -> get_ResponseStyle(This,ResponseStyle)

#define Action_put_ResponseStyle(This,ResponseStyle)	\
    (This)->lpVtbl -> put_ResponseStyle(This,ResponseStyle)

#define Action_get_ShowOn(This,ShowOn)	\
    (This)->lpVtbl -> get_ShowOn(This,ShowOn)

#define Action_put_ShowOn(This,ShowOn)	\
    (This)->lpVtbl -> put_ShowOn(This,ShowOn)

#define Action_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define Action_Execute(This,Item)	\
    (This)->lpVtbl -> Execute(This,Item)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Application_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Action_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Class_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Action_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Session_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Action_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Parent_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Action_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_CopyLike_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ OlActionCopyLike __RPC_FAR *CopyLike);


void __RPC_STUB Action_get_CopyLike_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_CopyLike_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ OlActionCopyLike CopyLike);


void __RPC_STUB Action_put_CopyLike_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Enabled_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);


void __RPC_STUB Action_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_Enabled_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB Action_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_MessageClass_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *MessageClass);


void __RPC_STUB Action_get_MessageClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_MessageClass_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ BSTR MessageClass);


void __RPC_STUB Action_put_MessageClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Name_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB Action_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_Name_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB Action_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_Prefix_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Prefix);


void __RPC_STUB Action_get_Prefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_Prefix_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ BSTR Prefix);


void __RPC_STUB Action_put_Prefix_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_ReplyStyle_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ OlActionReplyStyle __RPC_FAR *ReplyStyle);


void __RPC_STUB Action_get_ReplyStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_ReplyStyle_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ OlActionReplyStyle ReplyStyle);


void __RPC_STUB Action_put_ReplyStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_ResponseStyle_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ OlActionResponseStyle __RPC_FAR *ResponseStyle);


void __RPC_STUB Action_get_ResponseStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_ResponseStyle_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ OlActionResponseStyle ResponseStyle);


void __RPC_STUB Action_put_ResponseStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Action_get_ShowOn_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ OlActionShowOn __RPC_FAR *ShowOn);


void __RPC_STUB Action_get_ShowOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Action_put_ShowOn_Proxy( 
    Action __RPC_FAR * This,
    /* [in] */ OlActionShowOn ShowOn);


void __RPC_STUB Action_put_ShowOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Action_Delete_Proxy( 
    Action __RPC_FAR * This);


void __RPC_STUB Action_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Action_Execute_Proxy( 
    Action __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Action_Execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Action_INTERFACE_DEFINED__ */


#ifndef ___Application_INTERFACE_DEFINED__
#define ___Application_INTERFACE_DEFINED__

/* interface _Application */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID__Application,0x00063001,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063001-0000-0000-C000-000000000046")
    _Application : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Assistant( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Assistant) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *Version) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ActiveExplorer( 
            /* [retval][out] */ Explorer __RPC_FAR *__RPC_FAR *ActiveExplorer) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ActiveInspector( 
            /* [retval][out] */ Inspector __RPC_FAR *__RPC_FAR *ActiveInspector) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CreateItem( 
            /* [in] */ OlItemType ItemType,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CreateItemFromTemplate( 
            /* [in] */ BSTR TemplatePath,
            /* [optional][in] */ VARIANT InFolder,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CreateObject( 
            /* [in] */ BSTR ObjectName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Object) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetNamespace( 
            /* [in] */ BSTR Type,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *NameSpace) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Quit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _ApplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _Application __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _Application __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _Application __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _Application __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _Application __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _Application __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _Application __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Assistant )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Assistant);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Version);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActiveExplorer )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ Explorer __RPC_FAR *__RPC_FAR *ActiveExplorer);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActiveInspector )( 
            _Application __RPC_FAR * This,
            /* [retval][out] */ Inspector __RPC_FAR *__RPC_FAR *ActiveInspector);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItem )( 
            _Application __RPC_FAR * This,
            /* [in] */ OlItemType ItemType,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateItemFromTemplate )( 
            _Application __RPC_FAR * This,
            /* [in] */ BSTR TemplatePath,
            /* [optional][in] */ VARIANT InFolder,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateObject )( 
            _Application __RPC_FAR * This,
            /* [in] */ BSTR ObjectName,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Object);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamespace )( 
            _Application __RPC_FAR * This,
            /* [in] */ BSTR Type,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *NameSpace);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Quit )( 
            _Application __RPC_FAR * This);
        
        END_INTERFACE
    } _ApplicationVtbl;

    interface _Application
    {
        CONST_VTBL struct _ApplicationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _Application_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _Application_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _Application_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _Application_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _Application_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _Application_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _Application_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _Application_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define _Application_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define _Application_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define _Application_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define _Application_get_Assistant(This,Assistant)	\
    (This)->lpVtbl -> get_Assistant(This,Assistant)

#define _Application_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define _Application_get_Version(This,Version)	\
    (This)->lpVtbl -> get_Version(This,Version)

#define _Application_ActiveExplorer(This,ActiveExplorer)	\
    (This)->lpVtbl -> ActiveExplorer(This,ActiveExplorer)

#define _Application_ActiveInspector(This,ActiveInspector)	\
    (This)->lpVtbl -> ActiveInspector(This,ActiveInspector)

#define _Application_CreateItem(This,ItemType,Item)	\
    (This)->lpVtbl -> CreateItem(This,ItemType,Item)

#define _Application_CreateItemFromTemplate(This,TemplatePath,InFolder,Item)	\
    (This)->lpVtbl -> CreateItemFromTemplate(This,TemplatePath,InFolder,Item)

#define _Application_CreateObject(This,ObjectName,Object)	\
    (This)->lpVtbl -> CreateObject(This,ObjectName,Object)

#define _Application_GetNamespace(This,Type,NameSpace)	\
    (This)->lpVtbl -> GetNamespace(This,Type,NameSpace)

#define _Application_Quit(This)	\
    (This)->lpVtbl -> Quit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Application_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB _Application_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Class_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB _Application_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Session_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB _Application_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Parent_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB _Application_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Assistant_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Assistant);


void __RPC_STUB _Application_get_Assistant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Name_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB _Application_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _Application_get_Version_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Version);


void __RPC_STUB _Application_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_ActiveExplorer_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ Explorer __RPC_FAR *__RPC_FAR *ActiveExplorer);


void __RPC_STUB _Application_ActiveExplorer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_ActiveInspector_Proxy( 
    _Application __RPC_FAR * This,
    /* [retval][out] */ Inspector __RPC_FAR *__RPC_FAR *ActiveInspector);


void __RPC_STUB _Application_ActiveInspector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_CreateItem_Proxy( 
    _Application __RPC_FAR * This,
    /* [in] */ OlItemType ItemType,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _Application_CreateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_CreateItemFromTemplate_Proxy( 
    _Application __RPC_FAR * This,
    /* [in] */ BSTR TemplatePath,
    /* [optional][in] */ VARIANT InFolder,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _Application_CreateItemFromTemplate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_CreateObject_Proxy( 
    _Application __RPC_FAR * This,
    /* [in] */ BSTR ObjectName,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Object);


void __RPC_STUB _Application_CreateObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_GetNamespace_Proxy( 
    _Application __RPC_FAR * This,
    /* [in] */ BSTR Type,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *NameSpace);


void __RPC_STUB _Application_GetNamespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _Application_Quit_Proxy( 
    _Application __RPC_FAR * This);


void __RPC_STUB _Application_Quit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___Application_INTERFACE_DEFINED__ */


#ifndef __Actions_INTERFACE_DEFINED__
#define __Actions_INTERFACE_DEFINED__

/* interface Actions */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Actions,0x0006303E,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006303E-0000-0000-C000-000000000046")
    Actions : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Action __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [retval][out] */ Action __RPC_FAR *__RPC_FAR *Action) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ActionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Actions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Actions __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Actions __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Actions __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Actions __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Actions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Actions __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Actions __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Actions __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Actions __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Actions __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            Actions __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            Actions __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Action __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            Actions __RPC_FAR * This,
            /* [retval][out] */ Action __RPC_FAR *__RPC_FAR *Action);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            Actions __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } ActionsVtbl;

    interface Actions
    {
        CONST_VTBL struct ActionsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Actions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Actions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Actions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Actions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Actions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Actions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Actions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Actions_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Actions_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Actions_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Actions_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Actions_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define Actions_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define Actions_Add(This,Action)	\
    (This)->lpVtbl -> Add(This,Action)

#define Actions_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Actions_get_Application_Proxy( 
    Actions __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Actions_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Actions_get_Class_Proxy( 
    Actions __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Actions_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Actions_get_Session_Proxy( 
    Actions __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Actions_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Actions_get_Parent_Proxy( 
    Actions __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Actions_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Actions_get_Count_Proxy( 
    Actions __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB Actions_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Actions_Item_Proxy( 
    Actions __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ Action __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Actions_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Actions_Add_Proxy( 
    Actions __RPC_FAR * This,
    /* [retval][out] */ Action __RPC_FAR *__RPC_FAR *Action);


void __RPC_STUB Actions_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Actions_Remove_Proxy( 
    Actions __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB Actions_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Actions_INTERFACE_DEFINED__ */


#ifndef __NameSpace_INTERFACE_DEFINED__
#define __NameSpace_INTERFACE_DEFINED__

/* interface NameSpace */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_NameSpace,0x00063002,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063002-0000-0000-C000-000000000046")
    NameSpace : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CurrentUser( 
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *CurrentUser) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Folders( 
            /* [retval][out] */ Folders __RPC_FAR *__RPC_FAR *Folders) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR __RPC_FAR *Type) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_AddressLists( 
            /* [retval][out] */ AddressLists __RPC_FAR *__RPC_FAR *AddressLists) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CreateRecipient( 
            /* [in] */ BSTR RecipientName,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetDefaultFolder( 
            /* [in] */ OlDefaultFolders FolderType,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetFolderFromID( 
            /* [in] */ BSTR EntryIDFolder,
            /* [optional][in] */ VARIANT EntryIDStore,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetItemFromID( 
            /* [in] */ BSTR EntryIDItem,
            /* [optional][in] */ VARIANT EntryIDStore,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetRecipientFromID( 
            /* [in] */ BSTR EntryID,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetSharedDefaultFolder( 
            /* [in] */ Recipient __RPC_FAR *Recipient,
            /* [in] */ OlDefaultFolders FolderType,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Logoff( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Logon( 
            /* [optional][in] */ VARIANT Profile,
            /* [optional][in] */ VARIANT Password,
            /* [optional][in] */ VARIANT ShowDialog,
            /* [optional][in] */ VARIANT NewSession) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE PickFolder( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE RefreshRemoteHeaders( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct NameSpaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            NameSpace __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            NameSpace __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            NameSpace __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentUser )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *CurrentUser);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Folders )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ Folders __RPC_FAR *__RPC_FAR *Folders);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Type);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressLists )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ AddressLists __RPC_FAR *__RPC_FAR *AddressLists);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateRecipient )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ BSTR RecipientName,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDefaultFolder )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ OlDefaultFolders FolderType,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFolderFromID )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ BSTR EntryIDFolder,
            /* [optional][in] */ VARIANT EntryIDStore,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemFromID )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ BSTR EntryIDItem,
            /* [optional][in] */ VARIANT EntryIDStore,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRecipientFromID )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ BSTR EntryID,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSharedDefaultFolder )( 
            NameSpace __RPC_FAR * This,
            /* [in] */ Recipient __RPC_FAR *Recipient,
            /* [in] */ OlDefaultFolders FolderType,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Logoff )( 
            NameSpace __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Logon )( 
            NameSpace __RPC_FAR * This,
            /* [optional][in] */ VARIANT Profile,
            /* [optional][in] */ VARIANT Password,
            /* [optional][in] */ VARIANT ShowDialog,
            /* [optional][in] */ VARIANT NewSession);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PickFolder )( 
            NameSpace __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshRemoteHeaders )( 
            NameSpace __RPC_FAR * This);
        
        END_INTERFACE
    } NameSpaceVtbl;

    interface NameSpace
    {
        CONST_VTBL struct NameSpaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define NameSpace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define NameSpace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define NameSpace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define NameSpace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define NameSpace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define NameSpace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define NameSpace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define NameSpace_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define NameSpace_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define NameSpace_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define NameSpace_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define NameSpace_get_CurrentUser(This,CurrentUser)	\
    (This)->lpVtbl -> get_CurrentUser(This,CurrentUser)

#define NameSpace_get_Folders(This,Folders)	\
    (This)->lpVtbl -> get_Folders(This,Folders)

#define NameSpace_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define NameSpace_get_AddressLists(This,AddressLists)	\
    (This)->lpVtbl -> get_AddressLists(This,AddressLists)

#define NameSpace_CreateRecipient(This,RecipientName,Recipient)	\
    (This)->lpVtbl -> CreateRecipient(This,RecipientName,Recipient)

#define NameSpace_GetDefaultFolder(This,FolderType,Folder)	\
    (This)->lpVtbl -> GetDefaultFolder(This,FolderType,Folder)

#define NameSpace_GetFolderFromID(This,EntryIDFolder,EntryIDStore,Folder)	\
    (This)->lpVtbl -> GetFolderFromID(This,EntryIDFolder,EntryIDStore,Folder)

#define NameSpace_GetItemFromID(This,EntryIDItem,EntryIDStore,Item)	\
    (This)->lpVtbl -> GetItemFromID(This,EntryIDItem,EntryIDStore,Item)

#define NameSpace_GetRecipientFromID(This,EntryID,Recipient)	\
    (This)->lpVtbl -> GetRecipientFromID(This,EntryID,Recipient)

#define NameSpace_GetSharedDefaultFolder(This,Recipient,FolderType,Folder)	\
    (This)->lpVtbl -> GetSharedDefaultFolder(This,Recipient,FolderType,Folder)

#define NameSpace_Logoff(This)	\
    (This)->lpVtbl -> Logoff(This)

#define NameSpace_Logon(This,Profile,Password,ShowDialog,NewSession)	\
    (This)->lpVtbl -> Logon(This,Profile,Password,ShowDialog,NewSession)

#define NameSpace_PickFolder(This,Folder)	\
    (This)->lpVtbl -> PickFolder(This,Folder)

#define NameSpace_RefreshRemoteHeaders(This)	\
    (This)->lpVtbl -> RefreshRemoteHeaders(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_Application_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB NameSpace_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_Class_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB NameSpace_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_Session_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB NameSpace_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_Parent_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB NameSpace_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_CurrentUser_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *CurrentUser);


void __RPC_STUB NameSpace_get_CurrentUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_Folders_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ Folders __RPC_FAR *__RPC_FAR *Folders);


void __RPC_STUB NameSpace_get_Folders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_Type_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Type);


void __RPC_STUB NameSpace_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE NameSpace_get_AddressLists_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ AddressLists __RPC_FAR *__RPC_FAR *AddressLists);


void __RPC_STUB NameSpace_get_AddressLists_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_CreateRecipient_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [in] */ BSTR RecipientName,
    /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient);


void __RPC_STUB NameSpace_CreateRecipient_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_GetDefaultFolder_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [in] */ OlDefaultFolders FolderType,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB NameSpace_GetDefaultFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_GetFolderFromID_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [in] */ BSTR EntryIDFolder,
    /* [optional][in] */ VARIANT EntryIDStore,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB NameSpace_GetFolderFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_GetItemFromID_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [in] */ BSTR EntryIDItem,
    /* [optional][in] */ VARIANT EntryIDStore,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB NameSpace_GetItemFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_GetRecipientFromID_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [in] */ BSTR EntryID,
    /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient);


void __RPC_STUB NameSpace_GetRecipientFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_GetSharedDefaultFolder_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [in] */ Recipient __RPC_FAR *Recipient,
    /* [in] */ OlDefaultFolders FolderType,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB NameSpace_GetSharedDefaultFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_Logoff_Proxy( 
    NameSpace __RPC_FAR * This);


void __RPC_STUB NameSpace_Logoff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_Logon_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [optional][in] */ VARIANT Profile,
    /* [optional][in] */ VARIANT Password,
    /* [optional][in] */ VARIANT ShowDialog,
    /* [optional][in] */ VARIANT NewSession);


void __RPC_STUB NameSpace_Logon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE NameSpace_PickFolder_Proxy( 
    NameSpace __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB NameSpace_PickFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE NameSpace_RefreshRemoteHeaders_Proxy( 
    NameSpace __RPC_FAR * This);


void __RPC_STUB NameSpace_RefreshRemoteHeaders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __NameSpace_INTERFACE_DEFINED__ */


#ifndef __Recipient_INTERFACE_DEFINED__
#define __Recipient_INTERFACE_DEFINED__

/* interface Recipient */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Recipient,0x00063045,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063045-0000-0000-C000-000000000046")
    Recipient : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ BSTR __RPC_FAR *Address) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_AddressEntry( 
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry) = 0;
        
        virtual /* [helpcontext][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_AddressEntry( 
            /* [in] */ AddressEntry __RPC_FAR *AddressEntry) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_AutoResponse( 
            /* [retval][out] */ BSTR __RPC_FAR *AutoResponse) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_AutoResponse( 
            /* [in] */ BSTR AutoResponse) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayType( 
            /* [retval][out] */ OlDisplayType __RPC_FAR *DisplayType) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_EntryID( 
            /* [retval][out] */ BSTR __RPC_FAR *EntryID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ long __RPC_FAR *Index) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_MeetingResponseStatus( 
            /* [retval][out] */ OlResponseStatus __RPC_FAR *MeetingResponseStatus) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Resolved( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Resolved) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_TrackingStatus( 
            /* [retval][out] */ OlTrackingStatus __RPC_FAR *TrackingStatus) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_TrackingStatus( 
            /* [in] */ OlTrackingStatus TrackingStatus) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_TrackingStatusTime( 
            /* [retval][out] */ DATE __RPC_FAR *TrackingStatusTime) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_TrackingStatusTime( 
            /* [in] */ DATE TrackingStatusTime) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ long __RPC_FAR *Type) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ long Type) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE FreeBusy( 
            /* [in] */ DATE Start,
            /* [in] */ long MinPerChar,
            /* [optional][in] */ VARIANT CompleteFormat,
            /* [retval][out] */ BSTR __RPC_FAR *FreeBusyInfo) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Resolve( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Success) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct RecipientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Recipient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Recipient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Recipient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Recipient __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Recipient __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Recipient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Recipient __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Address);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressEntry )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);
        
        /* [helpcontext][propputref][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_AddressEntry )( 
            Recipient __RPC_FAR * This,
            /* [in] */ AddressEntry __RPC_FAR *AddressEntry);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoResponse )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *AutoResponse);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoResponse )( 
            Recipient __RPC_FAR * This,
            /* [in] */ BSTR AutoResponse);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayType )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ OlDisplayType __RPC_FAR *DisplayType);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntryID )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *EntryID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Index);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MeetingResponseStatus )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ OlResponseStatus __RPC_FAR *MeetingResponseStatus);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Resolved )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Resolved);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TrackingStatus )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ OlTrackingStatus __RPC_FAR *TrackingStatus);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TrackingStatus )( 
            Recipient __RPC_FAR * This,
            /* [in] */ OlTrackingStatus TrackingStatus);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TrackingStatusTime )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *TrackingStatusTime);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TrackingStatusTime )( 
            Recipient __RPC_FAR * This,
            /* [in] */ DATE TrackingStatusTime);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Type);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            Recipient __RPC_FAR * This,
            /* [in] */ long Type);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            Recipient __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeBusy )( 
            Recipient __RPC_FAR * This,
            /* [in] */ DATE Start,
            /* [in] */ long MinPerChar,
            /* [optional][in] */ VARIANT CompleteFormat,
            /* [retval][out] */ BSTR __RPC_FAR *FreeBusyInfo);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resolve )( 
            Recipient __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Success);
        
        END_INTERFACE
    } RecipientVtbl;

    interface Recipient
    {
        CONST_VTBL struct RecipientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Recipient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Recipient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Recipient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Recipient_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Recipient_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Recipient_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Recipient_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Recipient_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Recipient_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Recipient_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Recipient_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Recipient_get_Address(This,Address)	\
    (This)->lpVtbl -> get_Address(This,Address)

#define Recipient_get_AddressEntry(This,AddressEntry)	\
    (This)->lpVtbl -> get_AddressEntry(This,AddressEntry)

#define Recipient_putref_AddressEntry(This,AddressEntry)	\
    (This)->lpVtbl -> putref_AddressEntry(This,AddressEntry)

#define Recipient_get_AutoResponse(This,AutoResponse)	\
    (This)->lpVtbl -> get_AutoResponse(This,AutoResponse)

#define Recipient_put_AutoResponse(This,AutoResponse)	\
    (This)->lpVtbl -> put_AutoResponse(This,AutoResponse)

#define Recipient_get_DisplayType(This,DisplayType)	\
    (This)->lpVtbl -> get_DisplayType(This,DisplayType)

#define Recipient_get_EntryID(This,EntryID)	\
    (This)->lpVtbl -> get_EntryID(This,EntryID)

#define Recipient_get_Index(This,Index)	\
    (This)->lpVtbl -> get_Index(This,Index)

#define Recipient_get_MeetingResponseStatus(This,MeetingResponseStatus)	\
    (This)->lpVtbl -> get_MeetingResponseStatus(This,MeetingResponseStatus)

#define Recipient_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define Recipient_get_Resolved(This,Resolved)	\
    (This)->lpVtbl -> get_Resolved(This,Resolved)

#define Recipient_get_TrackingStatus(This,TrackingStatus)	\
    (This)->lpVtbl -> get_TrackingStatus(This,TrackingStatus)

#define Recipient_put_TrackingStatus(This,TrackingStatus)	\
    (This)->lpVtbl -> put_TrackingStatus(This,TrackingStatus)

#define Recipient_get_TrackingStatusTime(This,TrackingStatusTime)	\
    (This)->lpVtbl -> get_TrackingStatusTime(This,TrackingStatusTime)

#define Recipient_put_TrackingStatusTime(This,TrackingStatusTime)	\
    (This)->lpVtbl -> put_TrackingStatusTime(This,TrackingStatusTime)

#define Recipient_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define Recipient_put_Type(This,Type)	\
    (This)->lpVtbl -> put_Type(This,Type)

#define Recipient_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define Recipient_FreeBusy(This,Start,MinPerChar,CompleteFormat,FreeBusyInfo)	\
    (This)->lpVtbl -> FreeBusy(This,Start,MinPerChar,CompleteFormat,FreeBusyInfo)

#define Recipient_Resolve(This,Success)	\
    (This)->lpVtbl -> Resolve(This,Success)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Application_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Recipient_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Class_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Recipient_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Session_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Recipient_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Parent_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Recipient_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Address_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Address);


void __RPC_STUB Recipient_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_AddressEntry_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);


void __RPC_STUB Recipient_get_AddressEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propputref][id] */ HRESULT STDMETHODCALLTYPE Recipient_putref_AddressEntry_Proxy( 
    Recipient __RPC_FAR * This,
    /* [in] */ AddressEntry __RPC_FAR *AddressEntry);


void __RPC_STUB Recipient_putref_AddressEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_AutoResponse_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *AutoResponse);


void __RPC_STUB Recipient_get_AutoResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Recipient_put_AutoResponse_Proxy( 
    Recipient __RPC_FAR * This,
    /* [in] */ BSTR AutoResponse);


void __RPC_STUB Recipient_put_AutoResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_DisplayType_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ OlDisplayType __RPC_FAR *DisplayType);


void __RPC_STUB Recipient_get_DisplayType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_EntryID_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *EntryID);


void __RPC_STUB Recipient_get_EntryID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Index_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Index);


void __RPC_STUB Recipient_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_MeetingResponseStatus_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ OlResponseStatus __RPC_FAR *MeetingResponseStatus);


void __RPC_STUB Recipient_get_MeetingResponseStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Name_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB Recipient_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Resolved_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Resolved);


void __RPC_STUB Recipient_get_Resolved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_TrackingStatus_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ OlTrackingStatus __RPC_FAR *TrackingStatus);


void __RPC_STUB Recipient_get_TrackingStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Recipient_put_TrackingStatus_Proxy( 
    Recipient __RPC_FAR * This,
    /* [in] */ OlTrackingStatus TrackingStatus);


void __RPC_STUB Recipient_put_TrackingStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_TrackingStatusTime_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *TrackingStatusTime);


void __RPC_STUB Recipient_get_TrackingStatusTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Recipient_put_TrackingStatusTime_Proxy( 
    Recipient __RPC_FAR * This,
    /* [in] */ DATE TrackingStatusTime);


void __RPC_STUB Recipient_put_TrackingStatusTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipient_get_Type_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Type);


void __RPC_STUB Recipient_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Recipient_put_Type_Proxy( 
    Recipient __RPC_FAR * This,
    /* [in] */ long Type);


void __RPC_STUB Recipient_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipient_Delete_Proxy( 
    Recipient __RPC_FAR * This);


void __RPC_STUB Recipient_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipient_FreeBusy_Proxy( 
    Recipient __RPC_FAR * This,
    /* [in] */ DATE Start,
    /* [in] */ long MinPerChar,
    /* [optional][in] */ VARIANT CompleteFormat,
    /* [retval][out] */ BSTR __RPC_FAR *FreeBusyInfo);


void __RPC_STUB Recipient_FreeBusy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipient_Resolve_Proxy( 
    Recipient __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Success);


void __RPC_STUB Recipient_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Recipient_INTERFACE_DEFINED__ */


#ifndef __AddressLists_INTERFACE_DEFINED__
#define __AddressLists_INTERFACE_DEFINED__

/* interface AddressLists */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_AddressLists,0x00063048,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063048-0000-0000-C000-000000000046")
    AddressLists : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ AddressList __RPC_FAR *__RPC_FAR *Item) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AddressListsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            AddressLists __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            AddressLists __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            AddressLists __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            AddressLists __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            AddressLists __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            AddressLists __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            AddressLists __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            AddressLists __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            AddressLists __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            AddressLists __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            AddressLists __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            AddressLists __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            AddressLists __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ AddressList __RPC_FAR *__RPC_FAR *Item);
        
        END_INTERFACE
    } AddressListsVtbl;

    interface AddressLists
    {
        CONST_VTBL struct AddressListsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AddressLists_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define AddressLists_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define AddressLists_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define AddressLists_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define AddressLists_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define AddressLists_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define AddressLists_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define AddressLists_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define AddressLists_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define AddressLists_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define AddressLists_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define AddressLists_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define AddressLists_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressLists_get_Application_Proxy( 
    AddressLists __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB AddressLists_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressLists_get_Class_Proxy( 
    AddressLists __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB AddressLists_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressLists_get_Session_Proxy( 
    AddressLists __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB AddressLists_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressLists_get_Parent_Proxy( 
    AddressLists __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB AddressLists_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressLists_get_Count_Proxy( 
    AddressLists __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB AddressLists_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressLists_Item_Proxy( 
    AddressLists __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ AddressList __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB AddressLists_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __AddressLists_INTERFACE_DEFINED__ */


#ifndef __AddressList_INTERFACE_DEFINED__
#define __AddressList_INTERFACE_DEFINED__

/* interface AddressList */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_AddressList,0x00063049,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063049-0000-0000-C000-000000000046")
    AddressList : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_AddressEntries( 
            /* [retval][out] */ AddressEntries __RPC_FAR *__RPC_FAR *AddressEntries) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ BSTR __RPC_FAR *ID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ long __RPC_FAR *Index) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_IsReadOnly( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsReadOnly) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AddressListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            AddressList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            AddressList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            AddressList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            AddressList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            AddressList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            AddressList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            AddressList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressEntries )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ AddressEntries __RPC_FAR *__RPC_FAR *AddressEntries);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Index);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsReadOnly )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsReadOnly);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            AddressList __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        END_INTERFACE
    } AddressListVtbl;

    interface AddressList
    {
        CONST_VTBL struct AddressListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AddressList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define AddressList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define AddressList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define AddressList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define AddressList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define AddressList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define AddressList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define AddressList_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define AddressList_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define AddressList_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define AddressList_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define AddressList_get_AddressEntries(This,AddressEntries)	\
    (This)->lpVtbl -> get_AddressEntries(This,AddressEntries)

#define AddressList_get_ID(This,ID)	\
    (This)->lpVtbl -> get_ID(This,ID)

#define AddressList_get_Index(This,Index)	\
    (This)->lpVtbl -> get_Index(This,Index)

#define AddressList_get_IsReadOnly(This,IsReadOnly)	\
    (This)->lpVtbl -> get_IsReadOnly(This,IsReadOnly)

#define AddressList_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_Application_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB AddressList_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_Class_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB AddressList_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_Session_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB AddressList_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_Parent_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB AddressList_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_AddressEntries_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ AddressEntries __RPC_FAR *__RPC_FAR *AddressEntries);


void __RPC_STUB AddressList_get_AddressEntries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_ID_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ID);


void __RPC_STUB AddressList_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_Index_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Index);


void __RPC_STUB AddressList_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_IsReadOnly_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsReadOnly);


void __RPC_STUB AddressList_get_IsReadOnly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressList_get_Name_Proxy( 
    AddressList __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB AddressList_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __AddressList_INTERFACE_DEFINED__ */


#ifndef __AddressEntry_INTERFACE_DEFINED__
#define __AddressEntry_INTERFACE_DEFINED__

/* interface AddressEntry */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_AddressEntry,0x0006304B,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006304B-0000-0000-C000-000000000046")
    AddressEntry : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ BSTR __RPC_FAR *Address) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Address( 
            /* [in] */ BSTR Address) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayType( 
            /* [retval][out] */ OlDisplayType __RPC_FAR *DisplayType) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ BSTR __RPC_FAR *ID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Manager( 
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Manager) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_MAPIOBJECT( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT) = 0;
        
        virtual /* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE put_MAPIOBJECT( 
            /* [in] */ IUnknown __RPC_FAR *MAPIOBJECT) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Members( 
            /* [retval][out] */ AddressEntries __RPC_FAR *__RPC_FAR *Members) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR __RPC_FAR *Type) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ BSTR Type) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Details( 
            /* [optional][in] */ VARIANT HWnd) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetFreeBusy( 
            /* [in] */ DATE Start,
            /* [in] */ long MinPerChar,
            /* [optional][in] */ VARIANT CompleteFormat,
            /* [retval][out] */ BSTR __RPC_FAR *FreeBusyInfo) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Update( 
            /* [optional][in] */ VARIANT MakePermanent,
            /* [optional][in] */ VARIANT Refresh) = 0;
        
        virtual /* [hidden][id] */ HRESULT STDMETHODCALLTYPE UpdateFreeBusy( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AddressEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            AddressEntry __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            AddressEntry __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            AddressEntry __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Address);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Address )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ BSTR Address);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayType )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ OlDisplayType __RPC_FAR *DisplayType);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Manager )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Manager);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MAPIOBJECT )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT);
        
        /* [hidden][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MAPIOBJECT )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *MAPIOBJECT);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Members )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ AddressEntries __RPC_FAR *__RPC_FAR *Members);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            AddressEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Type);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ BSTR Type);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            AddressEntry __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Details )( 
            AddressEntry __RPC_FAR * This,
            /* [optional][in] */ VARIANT HWnd);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFreeBusy )( 
            AddressEntry __RPC_FAR * This,
            /* [in] */ DATE Start,
            /* [in] */ long MinPerChar,
            /* [optional][in] */ VARIANT CompleteFormat,
            /* [retval][out] */ BSTR __RPC_FAR *FreeBusyInfo);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            AddressEntry __RPC_FAR * This,
            /* [optional][in] */ VARIANT MakePermanent,
            /* [optional][in] */ VARIANT Refresh);
        
        /* [hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateFreeBusy )( 
            AddressEntry __RPC_FAR * This);
        
        END_INTERFACE
    } AddressEntryVtbl;

    interface AddressEntry
    {
        CONST_VTBL struct AddressEntryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AddressEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define AddressEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define AddressEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define AddressEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define AddressEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define AddressEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define AddressEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define AddressEntry_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define AddressEntry_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define AddressEntry_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define AddressEntry_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define AddressEntry_get_Address(This,Address)	\
    (This)->lpVtbl -> get_Address(This,Address)

#define AddressEntry_put_Address(This,Address)	\
    (This)->lpVtbl -> put_Address(This,Address)

#define AddressEntry_get_DisplayType(This,DisplayType)	\
    (This)->lpVtbl -> get_DisplayType(This,DisplayType)

#define AddressEntry_get_ID(This,ID)	\
    (This)->lpVtbl -> get_ID(This,ID)

#define AddressEntry_get_Manager(This,Manager)	\
    (This)->lpVtbl -> get_Manager(This,Manager)

#define AddressEntry_get_MAPIOBJECT(This,MAPIOBJECT)	\
    (This)->lpVtbl -> get_MAPIOBJECT(This,MAPIOBJECT)

#define AddressEntry_put_MAPIOBJECT(This,MAPIOBJECT)	\
    (This)->lpVtbl -> put_MAPIOBJECT(This,MAPIOBJECT)

#define AddressEntry_get_Members(This,Members)	\
    (This)->lpVtbl -> get_Members(This,Members)

#define AddressEntry_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define AddressEntry_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define AddressEntry_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define AddressEntry_put_Type(This,Type)	\
    (This)->lpVtbl -> put_Type(This,Type)

#define AddressEntry_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define AddressEntry_Details(This,HWnd)	\
    (This)->lpVtbl -> Details(This,HWnd)

#define AddressEntry_GetFreeBusy(This,Start,MinPerChar,CompleteFormat,FreeBusyInfo)	\
    (This)->lpVtbl -> GetFreeBusy(This,Start,MinPerChar,CompleteFormat,FreeBusyInfo)

#define AddressEntry_Update(This,MakePermanent,Refresh)	\
    (This)->lpVtbl -> Update(This,MakePermanent,Refresh)

#define AddressEntry_UpdateFreeBusy(This)	\
    (This)->lpVtbl -> UpdateFreeBusy(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Application_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB AddressEntry_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Class_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB AddressEntry_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Session_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB AddressEntry_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Parent_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB AddressEntry_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Address_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Address);


void __RPC_STUB AddressEntry_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_put_Address_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [in] */ BSTR Address);


void __RPC_STUB AddressEntry_put_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_DisplayType_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ OlDisplayType __RPC_FAR *DisplayType);


void __RPC_STUB AddressEntry_get_DisplayType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_ID_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ID);


void __RPC_STUB AddressEntry_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Manager_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Manager);


void __RPC_STUB AddressEntry_get_Manager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_MAPIOBJECT_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT);


void __RPC_STUB AddressEntry_get_MAPIOBJECT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propput][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_put_MAPIOBJECT_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *MAPIOBJECT);


void __RPC_STUB AddressEntry_put_MAPIOBJECT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Members_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ AddressEntries __RPC_FAR *__RPC_FAR *Members);


void __RPC_STUB AddressEntry_get_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Name_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB AddressEntry_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_put_Name_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB AddressEntry_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_get_Type_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Type);


void __RPC_STUB AddressEntry_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_put_Type_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [in] */ BSTR Type);


void __RPC_STUB AddressEntry_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_Delete_Proxy( 
    AddressEntry __RPC_FAR * This);


void __RPC_STUB AddressEntry_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_Details_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [optional][in] */ VARIANT HWnd);


void __RPC_STUB AddressEntry_Details_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_GetFreeBusy_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [in] */ DATE Start,
    /* [in] */ long MinPerChar,
    /* [optional][in] */ VARIANT CompleteFormat,
    /* [retval][out] */ BSTR __RPC_FAR *FreeBusyInfo);


void __RPC_STUB AddressEntry_GetFreeBusy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_Update_Proxy( 
    AddressEntry __RPC_FAR * This,
    /* [optional][in] */ VARIANT MakePermanent,
    /* [optional][in] */ VARIANT Refresh);


void __RPC_STUB AddressEntry_Update_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][id] */ HRESULT STDMETHODCALLTYPE AddressEntry_UpdateFreeBusy_Proxy( 
    AddressEntry __RPC_FAR * This);


void __RPC_STUB AddressEntry_UpdateFreeBusy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __AddressEntry_INTERFACE_DEFINED__ */


#ifndef __AddressEntries_INTERFACE_DEFINED__
#define __AddressEntries_INTERFACE_DEFINED__

/* interface AddressEntries */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_AddressEntries,0x0006304A,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006304A-0000-0000-C000-000000000046")
    AddressEntries : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_RawTable( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Type,
            /* [optional][in] */ VARIANT Name,
            /* [optional][in] */ VARIANT Address,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Entry) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetFirst( 
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetLast( 
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetNext( 
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetPrevious( 
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Sort( 
            /* [optional][in] */ VARIANT Property,
            /* [optional][in] */ VARIANT Order) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AddressEntriesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            AddressEntries __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            AddressEntries __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            AddressEntries __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            AddressEntries __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            AddressEntries __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            AddressEntries __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            AddressEntries __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            AddressEntries __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Item);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RawTable )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            AddressEntries __RPC_FAR * This,
            /* [in] */ BSTR Type,
            /* [optional][in] */ VARIANT Name,
            /* [optional][in] */ VARIANT Address,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Entry);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirst )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLast )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNext )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrevious )( 
            AddressEntries __RPC_FAR * This,
            /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sort )( 
            AddressEntries __RPC_FAR * This,
            /* [optional][in] */ VARIANT Property,
            /* [optional][in] */ VARIANT Order);
        
        END_INTERFACE
    } AddressEntriesVtbl;

    interface AddressEntries
    {
        CONST_VTBL struct AddressEntriesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define AddressEntries_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define AddressEntries_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define AddressEntries_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define AddressEntries_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define AddressEntries_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define AddressEntries_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define AddressEntries_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define AddressEntries_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define AddressEntries_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define AddressEntries_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define AddressEntries_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define AddressEntries_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define AddressEntries_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define AddressEntries_get_RawTable(This,RawTable)	\
    (This)->lpVtbl -> get_RawTable(This,RawTable)

#define AddressEntries_Add(This,Type,Name,Address,Entry)	\
    (This)->lpVtbl -> Add(This,Type,Name,Address,Entry)

#define AddressEntries_GetFirst(This,AddressEntry)	\
    (This)->lpVtbl -> GetFirst(This,AddressEntry)

#define AddressEntries_GetLast(This,AddressEntry)	\
    (This)->lpVtbl -> GetLast(This,AddressEntry)

#define AddressEntries_GetNext(This,AddressEntry)	\
    (This)->lpVtbl -> GetNext(This,AddressEntry)

#define AddressEntries_GetPrevious(This,AddressEntry)	\
    (This)->lpVtbl -> GetPrevious(This,AddressEntry)

#define AddressEntries_Sort(This,Property,Order)	\
    (This)->lpVtbl -> Sort(This,Property,Order)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_get_Application_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB AddressEntries_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_get_Class_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB AddressEntries_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_get_Session_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB AddressEntries_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_get_Parent_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB AddressEntries_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_get_Count_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB AddressEntries_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_Item_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB AddressEntries_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_get_RawTable_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable);


void __RPC_STUB AddressEntries_get_RawTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_Add_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [in] */ BSTR Type,
    /* [optional][in] */ VARIANT Name,
    /* [optional][in] */ VARIANT Address,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *Entry);


void __RPC_STUB AddressEntries_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_GetFirst_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);


void __RPC_STUB AddressEntries_GetFirst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_GetLast_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);


void __RPC_STUB AddressEntries_GetLast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_GetNext_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);


void __RPC_STUB AddressEntries_GetNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_GetPrevious_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [retval][out] */ AddressEntry __RPC_FAR *__RPC_FAR *AddressEntry);


void __RPC_STUB AddressEntries_GetPrevious_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE AddressEntries_Sort_Proxy( 
    AddressEntries __RPC_FAR * This,
    /* [optional][in] */ VARIANT Property,
    /* [optional][in] */ VARIANT Order);


void __RPC_STUB AddressEntries_Sort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __AddressEntries_INTERFACE_DEFINED__ */


#ifndef __Attachments_INTERFACE_DEFINED__
#define __Attachments_INTERFACE_DEFINED__

/* interface Attachments */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Attachments,0x0006303C,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006303C-0000-0000-C000-000000000046")
    Attachments : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Attachment __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ VARIANT Source,
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Position,
            /* [optional][in] */ VARIANT DisplayName,
            /* [retval][out] */ Attachment __RPC_FAR *__RPC_FAR *Attachment) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AttachmentsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Attachments __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Attachments __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Attachments __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Attachments __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Attachments __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Attachments __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Attachments __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Attachments __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Attachments __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Attachments __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Attachments __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            Attachments __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            Attachments __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Attachment __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            Attachments __RPC_FAR * This,
            /* [in] */ VARIANT Source,
            /* [optional][in] */ VARIANT Type,
            /* [optional][in] */ VARIANT Position,
            /* [optional][in] */ VARIANT DisplayName,
            /* [retval][out] */ Attachment __RPC_FAR *__RPC_FAR *Attachment);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            Attachments __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } AttachmentsVtbl;

    interface Attachments
    {
        CONST_VTBL struct AttachmentsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Attachments_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Attachments_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Attachments_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Attachments_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Attachments_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Attachments_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Attachments_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Attachments_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Attachments_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Attachments_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Attachments_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Attachments_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define Attachments_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define Attachments_Add(This,Source,Type,Position,DisplayName,Attachment)	\
    (This)->lpVtbl -> Add(This,Source,Type,Position,DisplayName,Attachment)

#define Attachments_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachments_get_Application_Proxy( 
    Attachments __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Attachments_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachments_get_Class_Proxy( 
    Attachments __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Attachments_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachments_get_Session_Proxy( 
    Attachments __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Attachments_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachments_get_Parent_Proxy( 
    Attachments __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Attachments_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachments_get_Count_Proxy( 
    Attachments __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB Attachments_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Attachments_Item_Proxy( 
    Attachments __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ Attachment __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Attachments_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Attachments_Add_Proxy( 
    Attachments __RPC_FAR * This,
    /* [in] */ VARIANT Source,
    /* [optional][in] */ VARIANT Type,
    /* [optional][in] */ VARIANT Position,
    /* [optional][in] */ VARIANT DisplayName,
    /* [retval][out] */ Attachment __RPC_FAR *__RPC_FAR *Attachment);


void __RPC_STUB Attachments_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Attachments_Remove_Proxy( 
    Attachments __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB Attachments_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Attachments_INTERFACE_DEFINED__ */


#ifndef __Attachment_INTERFACE_DEFINED__
#define __Attachment_INTERFACE_DEFINED__

/* interface Attachment */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Attachment,0x00063007,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063007-0000-0000-C000-000000000046")
    Attachment : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR __RPC_FAR *DisplayName) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR DisplayName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *FileName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Index( 
            /* [retval][out] */ long __RPC_FAR *Index) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_MAPIOBJECT( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_PathName( 
            /* [retval][out] */ BSTR __RPC_FAR *PathName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ long __RPC_FAR *Position) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ long Position) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ OlAttachmentType __RPC_FAR *Type) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SaveAsFile( 
            /* [in] */ BSTR Path) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct AttachmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Attachment __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Attachment __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Attachment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Attachment __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Attachment __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Attachment __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Attachment __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *DisplayName);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            Attachment __RPC_FAR * This,
            /* [in] */ BSTR DisplayName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *FileName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Index )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Index);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MAPIOBJECT )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PathName )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *PathName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Position);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            Attachment __RPC_FAR * This,
            /* [in] */ long Position);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            Attachment __RPC_FAR * This,
            /* [retval][out] */ OlAttachmentType __RPC_FAR *Type);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            Attachment __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAsFile )( 
            Attachment __RPC_FAR * This,
            /* [in] */ BSTR Path);
        
        END_INTERFACE
    } AttachmentVtbl;

    interface Attachment
    {
        CONST_VTBL struct AttachmentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Attachment_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Attachment_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Attachment_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Attachment_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Attachment_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Attachment_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Attachment_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Attachment_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Attachment_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Attachment_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Attachment_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Attachment_get_DisplayName(This,DisplayName)	\
    (This)->lpVtbl -> get_DisplayName(This,DisplayName)

#define Attachment_put_DisplayName(This,DisplayName)	\
    (This)->lpVtbl -> put_DisplayName(This,DisplayName)

#define Attachment_get_FileName(This,FileName)	\
    (This)->lpVtbl -> get_FileName(This,FileName)

#define Attachment_get_Index(This,Index)	\
    (This)->lpVtbl -> get_Index(This,Index)

#define Attachment_get_MAPIOBJECT(This,MAPIOBJECT)	\
    (This)->lpVtbl -> get_MAPIOBJECT(This,MAPIOBJECT)

#define Attachment_get_PathName(This,PathName)	\
    (This)->lpVtbl -> get_PathName(This,PathName)

#define Attachment_get_Position(This,Position)	\
    (This)->lpVtbl -> get_Position(This,Position)

#define Attachment_put_Position(This,Position)	\
    (This)->lpVtbl -> put_Position(This,Position)

#define Attachment_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define Attachment_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define Attachment_SaveAsFile(This,Path)	\
    (This)->lpVtbl -> SaveAsFile(This,Path)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Application_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Attachment_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Class_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Attachment_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Session_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Attachment_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Parent_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Attachment_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_DisplayName_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *DisplayName);


void __RPC_STUB Attachment_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Attachment_put_DisplayName_Proxy( 
    Attachment __RPC_FAR * This,
    /* [in] */ BSTR DisplayName);


void __RPC_STUB Attachment_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_FileName_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *FileName);


void __RPC_STUB Attachment_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Index_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Index);


void __RPC_STUB Attachment_get_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_MAPIOBJECT_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT);


void __RPC_STUB Attachment_get_MAPIOBJECT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_PathName_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *PathName);


void __RPC_STUB Attachment_get_PathName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Position_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Position);


void __RPC_STUB Attachment_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Attachment_put_Position_Proxy( 
    Attachment __RPC_FAR * This,
    /* [in] */ long Position);


void __RPC_STUB Attachment_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Attachment_get_Type_Proxy( 
    Attachment __RPC_FAR * This,
    /* [retval][out] */ OlAttachmentType __RPC_FAR *Type);


void __RPC_STUB Attachment_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Attachment_Delete_Proxy( 
    Attachment __RPC_FAR * This);


void __RPC_STUB Attachment_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE Attachment_SaveAsFile_Proxy( 
    Attachment __RPC_FAR * This,
    /* [in] */ BSTR Path);


void __RPC_STUB Attachment_SaveAsFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Attachment_INTERFACE_DEFINED__ */


#ifndef __Recipients_INTERFACE_DEFINED__
#define __Recipients_INTERFACE_DEFINED__

/* interface Recipients */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Recipients,0x0006303B,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006303B-0000-0000-C000-000000000046")
    Recipients : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ResolveAll( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Success) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct RecipientsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Recipients __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Recipients __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Recipients __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Recipients __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Recipients __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Recipients __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Recipients __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Recipients __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Recipients __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Recipients __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Recipients __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            Recipients __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            Recipients __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            Recipients __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            Recipients __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResolveAll )( 
            Recipients __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Success);
        
        END_INTERFACE
    } RecipientsVtbl;

    interface Recipients
    {
        CONST_VTBL struct RecipientsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Recipients_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Recipients_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Recipients_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Recipients_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Recipients_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Recipients_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Recipients_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Recipients_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Recipients_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Recipients_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Recipients_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Recipients_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define Recipients_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define Recipients_Add(This,Name,Recipient)	\
    (This)->lpVtbl -> Add(This,Name,Recipient)

#define Recipients_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define Recipients_ResolveAll(This,Success)	\
    (This)->lpVtbl -> ResolveAll(This,Success)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipients_get_Application_Proxy( 
    Recipients __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Recipients_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipients_get_Class_Proxy( 
    Recipients __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Recipients_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipients_get_Session_Proxy( 
    Recipients __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Recipients_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipients_get_Parent_Proxy( 
    Recipients __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Recipients_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Recipients_get_Count_Proxy( 
    Recipients __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB Recipients_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipients_Item_Proxy( 
    Recipients __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Recipients_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipients_Add_Proxy( 
    Recipients __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ Recipient __RPC_FAR *__RPC_FAR *Recipient);


void __RPC_STUB Recipients_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipients_Remove_Proxy( 
    Recipients __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB Recipients_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Recipients_ResolveAll_Proxy( 
    Recipients __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Success);


void __RPC_STUB Recipients_ResolveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Recipients_INTERFACE_DEFINED__ */


#ifndef __FormDescription_INTERFACE_DEFINED__
#define __FormDescription_INTERFACE_DEFINED__

/* interface FormDescription */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_FormDescription,0x00063046,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063046-0000-0000-C000-000000000046")
    FormDescription : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Category( 
            /* [retval][out] */ BSTR __RPC_FAR *Category) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Category( 
            /* [in] */ BSTR Category) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CategorySub( 
            /* [retval][out] */ BSTR __RPC_FAR *CategorySub) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_CategorySub( 
            /* [in] */ BSTR CategorySub) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Comment( 
            /* [retval][out] */ BSTR __RPC_FAR *Comment) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Comment( 
            /* [in] */ BSTR Comment) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ContactName( 
            /* [retval][out] */ BSTR __RPC_FAR *ContactName) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ContactName( 
            /* [in] */ BSTR ContactName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR __RPC_FAR *DisplayName) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DisplayName( 
            /* [in] */ BSTR DisplayName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Hidden( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Hidden) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Hidden( 
            /* [in] */ VARIANT_BOOL Hidden) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Icon( 
            /* [retval][out] */ BSTR __RPC_FAR *Icon) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Icon( 
            /* [in] */ BSTR Icon) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Locked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Locked) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Locked( 
            /* [in] */ VARIANT_BOOL Locked) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_MessageClass( 
            /* [retval][out] */ BSTR __RPC_FAR *MessageClass) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_MiniIcon( 
            /* [retval][out] */ BSTR __RPC_FAR *MiniIcon) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_MiniIcon( 
            /* [in] */ BSTR MiniIcon) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Number( 
            /* [retval][out] */ BSTR __RPC_FAR *Number) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Number( 
            /* [in] */ BSTR Number) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OneOff( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *OneOff) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_OneOff( 
            /* [in] */ VARIANT_BOOL OneOff) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Password( 
            /* [retval][out] */ BSTR __RPC_FAR *Password) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ BSTR Password) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ScriptText( 
            /* [retval][out] */ BSTR __RPC_FAR *ScriptText) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Template( 
            /* [retval][out] */ BSTR __RPC_FAR *Template) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Template( 
            /* [in] */ BSTR Template) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_UseWordMail( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UseWordMail) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_UseWordMail( 
            /* [in] */ VARIANT_BOOL UseWordMail) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *Version) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Version( 
            /* [in] */ BSTR Version) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE PublishForm( 
            /* [in] */ OlFormRegistry Registry,
            /* [optional][in] */ VARIANT Folder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FormDescriptionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            FormDescription __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            FormDescription __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            FormDescription __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Category )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Category);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Category )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Category);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CategorySub )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *CategorySub);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CategorySub )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR CategorySub);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Comment);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Comment);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContactName )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ContactName);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContactName )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR ContactName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *DisplayName);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DisplayName )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR DisplayName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hidden )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Hidden);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Hidden )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Hidden);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Icon )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Icon);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Icon )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Icon);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Locked )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Locked);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Locked )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Locked);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageClass )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *MessageClass);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MiniIcon )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *MiniIcon);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MiniIcon )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR MiniIcon);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Number )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Number);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Number )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Number);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OneOff )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *OneOff);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OneOff )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL OneOff);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Password )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Password);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Password )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Password);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScriptText )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ScriptText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Template )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Template);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Template )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Template);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseWordMail )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UseWordMail);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseWordMail )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL UseWordMail);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            FormDescription __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Version);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Version )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ BSTR Version);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PublishForm )( 
            FormDescription __RPC_FAR * This,
            /* [in] */ OlFormRegistry Registry,
            /* [optional][in] */ VARIANT Folder);
        
        END_INTERFACE
    } FormDescriptionVtbl;

    interface FormDescription
    {
        CONST_VTBL struct FormDescriptionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define FormDescription_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define FormDescription_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define FormDescription_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define FormDescription_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define FormDescription_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define FormDescription_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define FormDescription_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define FormDescription_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define FormDescription_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define FormDescription_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define FormDescription_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define FormDescription_get_Category(This,Category)	\
    (This)->lpVtbl -> get_Category(This,Category)

#define FormDescription_put_Category(This,Category)	\
    (This)->lpVtbl -> put_Category(This,Category)

#define FormDescription_get_CategorySub(This,CategorySub)	\
    (This)->lpVtbl -> get_CategorySub(This,CategorySub)

#define FormDescription_put_CategorySub(This,CategorySub)	\
    (This)->lpVtbl -> put_CategorySub(This,CategorySub)

#define FormDescription_get_Comment(This,Comment)	\
    (This)->lpVtbl -> get_Comment(This,Comment)

#define FormDescription_put_Comment(This,Comment)	\
    (This)->lpVtbl -> put_Comment(This,Comment)

#define FormDescription_get_ContactName(This,ContactName)	\
    (This)->lpVtbl -> get_ContactName(This,ContactName)

#define FormDescription_put_ContactName(This,ContactName)	\
    (This)->lpVtbl -> put_ContactName(This,ContactName)

#define FormDescription_get_DisplayName(This,DisplayName)	\
    (This)->lpVtbl -> get_DisplayName(This,DisplayName)

#define FormDescription_put_DisplayName(This,DisplayName)	\
    (This)->lpVtbl -> put_DisplayName(This,DisplayName)

#define FormDescription_get_Hidden(This,Hidden)	\
    (This)->lpVtbl -> get_Hidden(This,Hidden)

#define FormDescription_put_Hidden(This,Hidden)	\
    (This)->lpVtbl -> put_Hidden(This,Hidden)

#define FormDescription_get_Icon(This,Icon)	\
    (This)->lpVtbl -> get_Icon(This,Icon)

#define FormDescription_put_Icon(This,Icon)	\
    (This)->lpVtbl -> put_Icon(This,Icon)

#define FormDescription_get_Locked(This,Locked)	\
    (This)->lpVtbl -> get_Locked(This,Locked)

#define FormDescription_put_Locked(This,Locked)	\
    (This)->lpVtbl -> put_Locked(This,Locked)

#define FormDescription_get_MessageClass(This,MessageClass)	\
    (This)->lpVtbl -> get_MessageClass(This,MessageClass)

#define FormDescription_get_MiniIcon(This,MiniIcon)	\
    (This)->lpVtbl -> get_MiniIcon(This,MiniIcon)

#define FormDescription_put_MiniIcon(This,MiniIcon)	\
    (This)->lpVtbl -> put_MiniIcon(This,MiniIcon)

#define FormDescription_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define FormDescription_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define FormDescription_get_Number(This,Number)	\
    (This)->lpVtbl -> get_Number(This,Number)

#define FormDescription_put_Number(This,Number)	\
    (This)->lpVtbl -> put_Number(This,Number)

#define FormDescription_get_OneOff(This,OneOff)	\
    (This)->lpVtbl -> get_OneOff(This,OneOff)

#define FormDescription_put_OneOff(This,OneOff)	\
    (This)->lpVtbl -> put_OneOff(This,OneOff)

#define FormDescription_get_Password(This,Password)	\
    (This)->lpVtbl -> get_Password(This,Password)

#define FormDescription_put_Password(This,Password)	\
    (This)->lpVtbl -> put_Password(This,Password)

#define FormDescription_get_ScriptText(This,ScriptText)	\
    (This)->lpVtbl -> get_ScriptText(This,ScriptText)

#define FormDescription_get_Template(This,Template)	\
    (This)->lpVtbl -> get_Template(This,Template)

#define FormDescription_put_Template(This,Template)	\
    (This)->lpVtbl -> put_Template(This,Template)

#define FormDescription_get_UseWordMail(This,UseWordMail)	\
    (This)->lpVtbl -> get_UseWordMail(This,UseWordMail)

#define FormDescription_put_UseWordMail(This,UseWordMail)	\
    (This)->lpVtbl -> put_UseWordMail(This,UseWordMail)

#define FormDescription_get_Version(This,Version)	\
    (This)->lpVtbl -> get_Version(This,Version)

#define FormDescription_put_Version(This,Version)	\
    (This)->lpVtbl -> put_Version(This,Version)

#define FormDescription_PublishForm(This,Registry,Folder)	\
    (This)->lpVtbl -> PublishForm(This,Registry,Folder)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Application_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB FormDescription_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Class_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB FormDescription_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Session_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB FormDescription_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Parent_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB FormDescription_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Category_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Category);


void __RPC_STUB FormDescription_get_Category_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Category_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Category);


void __RPC_STUB FormDescription_put_Category_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_CategorySub_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *CategorySub);


void __RPC_STUB FormDescription_get_CategorySub_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_CategorySub_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR CategorySub);


void __RPC_STUB FormDescription_put_CategorySub_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Comment_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Comment);


void __RPC_STUB FormDescription_get_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Comment_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Comment);


void __RPC_STUB FormDescription_put_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_ContactName_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ContactName);


void __RPC_STUB FormDescription_get_ContactName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_ContactName_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR ContactName);


void __RPC_STUB FormDescription_put_ContactName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_DisplayName_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *DisplayName);


void __RPC_STUB FormDescription_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_DisplayName_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR DisplayName);


void __RPC_STUB FormDescription_put_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Hidden_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Hidden);


void __RPC_STUB FormDescription_get_Hidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Hidden_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Hidden);


void __RPC_STUB FormDescription_put_Hidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Icon_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Icon);


void __RPC_STUB FormDescription_get_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Icon_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Icon);


void __RPC_STUB FormDescription_put_Icon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Locked_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Locked);


void __RPC_STUB FormDescription_get_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Locked_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Locked);


void __RPC_STUB FormDescription_put_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_MessageClass_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *MessageClass);


void __RPC_STUB FormDescription_get_MessageClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_MiniIcon_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *MiniIcon);


void __RPC_STUB FormDescription_get_MiniIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_MiniIcon_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR MiniIcon);


void __RPC_STUB FormDescription_put_MiniIcon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Name_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB FormDescription_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Name_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB FormDescription_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Number_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Number);


void __RPC_STUB FormDescription_get_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Number_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Number);


void __RPC_STUB FormDescription_put_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_OneOff_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *OneOff);


void __RPC_STUB FormDescription_get_OneOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_OneOff_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL OneOff);


void __RPC_STUB FormDescription_put_OneOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Password_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Password);


void __RPC_STUB FormDescription_get_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Password_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Password);


void __RPC_STUB FormDescription_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_ScriptText_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ScriptText);


void __RPC_STUB FormDescription_get_ScriptText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Template_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Template);


void __RPC_STUB FormDescription_get_Template_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Template_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Template);


void __RPC_STUB FormDescription_put_Template_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_UseWordMail_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UseWordMail);


void __RPC_STUB FormDescription_get_UseWordMail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_UseWordMail_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL UseWordMail);


void __RPC_STUB FormDescription_put_UseWordMail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE FormDescription_get_Version_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Version);


void __RPC_STUB FormDescription_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE FormDescription_put_Version_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ BSTR Version);


void __RPC_STUB FormDescription_put_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE FormDescription_PublishForm_Proxy( 
    FormDescription __RPC_FAR * This,
    /* [in] */ OlFormRegistry Registry,
    /* [optional][in] */ VARIANT Folder);


void __RPC_STUB FormDescription_PublishForm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __FormDescription_INTERFACE_DEFINED__ */


#ifndef __UserProperties_INTERFACE_DEFINED__
#define __UserProperties_INTERFACE_DEFINED__

/* interface UserProperties */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_UserProperties,0x0006303D,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006303D-0000-0000-C000-000000000046")
    UserProperties : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [in] */ OlUserPropertyType Type,
            /* [optional][in] */ VARIANT AddToFolderFields,
            /* [optional][in] */ VARIANT DisplayFormat,
            /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *UserProperty) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Custom,
            /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *UserProperty) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct UserPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            UserProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            UserProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            UserProperties __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            UserProperties __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            UserProperties __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            UserProperties __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            UserProperties __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            UserProperties __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ OlUserPropertyType Type,
            /* [optional][in] */ VARIANT AddToFolderFields,
            /* [optional][in] */ VARIANT DisplayFormat,
            /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *UserProperty);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Custom,
            /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *UserProperty);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            UserProperties __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } UserPropertiesVtbl;

    interface UserProperties
    {
        CONST_VTBL struct UserPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define UserProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define UserProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define UserProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define UserProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define UserProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define UserProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define UserProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define UserProperties_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define UserProperties_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define UserProperties_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define UserProperties_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define UserProperties_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define UserProperties_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define UserProperties_Add(This,Name,Type,AddToFolderFields,DisplayFormat,UserProperty)	\
    (This)->lpVtbl -> Add(This,Name,Type,AddToFolderFields,DisplayFormat,UserProperty)

#define UserProperties_Find(This,Name,Custom,UserProperty)	\
    (This)->lpVtbl -> Find(This,Name,Custom,UserProperty)

#define UserProperties_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperties_get_Application_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB UserProperties_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperties_get_Class_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB UserProperties_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperties_get_Session_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB UserProperties_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperties_get_Parent_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB UserProperties_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperties_get_Count_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB UserProperties_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE UserProperties_Item_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB UserProperties_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE UserProperties_Add_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ OlUserPropertyType Type,
    /* [optional][in] */ VARIANT AddToFolderFields,
    /* [optional][in] */ VARIANT DisplayFormat,
    /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *UserProperty);


void __RPC_STUB UserProperties_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE UserProperties_Find_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [optional][in] */ VARIANT Custom,
    /* [retval][out] */ UserProperty __RPC_FAR *__RPC_FAR *UserProperty);


void __RPC_STUB UserProperties_Find_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE UserProperties_Remove_Proxy( 
    UserProperties __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB UserProperties_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __UserProperties_INTERFACE_DEFINED__ */


#ifndef __UserProperty_INTERFACE_DEFINED__
#define __UserProperty_INTERFACE_DEFINED__

/* interface UserProperty */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_UserProperty,0x00063042,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063042-0000-0000-C000-000000000046")
    UserProperty : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Formula( 
            /* [retval][out] */ BSTR __RPC_FAR *Formula) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Formula( 
            /* [in] */ BSTR Formula) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ OlUserPropertyType __RPC_FAR *Type) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ValidationFormula( 
            /* [retval][out] */ BSTR __RPC_FAR *ValidationFormula) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ValidationFormula( 
            /* [in] */ BSTR ValidationFormula) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ValidationText( 
            /* [retval][out] */ BSTR __RPC_FAR *ValidationText) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ValidationText( 
            /* [in] */ BSTR ValidationText) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [retval][out] */ VARIANT __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Value( 
            /* [in] */ VARIANT Value) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct UserPropertyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            UserProperty __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            UserProperty __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            UserProperty __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Formula )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Formula);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Formula )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ BSTR Formula);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ OlUserPropertyType __RPC_FAR *Type);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ValidationFormula )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ValidationFormula);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ValidationFormula )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ BSTR ValidationFormula);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ValidationText )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ValidationText);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ValidationText )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ BSTR ValidationText);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            UserProperty __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *Value);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Value )( 
            UserProperty __RPC_FAR * This,
            /* [in] */ VARIANT Value);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            UserProperty __RPC_FAR * This);
        
        END_INTERFACE
    } UserPropertyVtbl;

    interface UserProperty
    {
        CONST_VTBL struct UserPropertyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define UserProperty_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define UserProperty_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define UserProperty_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define UserProperty_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define UserProperty_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define UserProperty_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define UserProperty_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define UserProperty_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define UserProperty_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define UserProperty_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define UserProperty_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define UserProperty_get_Formula(This,Formula)	\
    (This)->lpVtbl -> get_Formula(This,Formula)

#define UserProperty_put_Formula(This,Formula)	\
    (This)->lpVtbl -> put_Formula(This,Formula)

#define UserProperty_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define UserProperty_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define UserProperty_get_ValidationFormula(This,ValidationFormula)	\
    (This)->lpVtbl -> get_ValidationFormula(This,ValidationFormula)

#define UserProperty_put_ValidationFormula(This,ValidationFormula)	\
    (This)->lpVtbl -> put_ValidationFormula(This,ValidationFormula)

#define UserProperty_get_ValidationText(This,ValidationText)	\
    (This)->lpVtbl -> get_ValidationText(This,ValidationText)

#define UserProperty_put_ValidationText(This,ValidationText)	\
    (This)->lpVtbl -> put_ValidationText(This,ValidationText)

#define UserProperty_get_Value(This,Value)	\
    (This)->lpVtbl -> get_Value(This,Value)

#define UserProperty_put_Value(This,Value)	\
    (This)->lpVtbl -> put_Value(This,Value)

#define UserProperty_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Application_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB UserProperty_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Class_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB UserProperty_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Session_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB UserProperty_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Parent_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB UserProperty_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Formula_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Formula);


void __RPC_STUB UserProperty_get_Formula_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE UserProperty_put_Formula_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [in] */ BSTR Formula);


void __RPC_STUB UserProperty_put_Formula_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Name_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB UserProperty_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Type_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ OlUserPropertyType __RPC_FAR *Type);


void __RPC_STUB UserProperty_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_ValidationFormula_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ValidationFormula);


void __RPC_STUB UserProperty_get_ValidationFormula_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE UserProperty_put_ValidationFormula_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [in] */ BSTR ValidationFormula);


void __RPC_STUB UserProperty_put_ValidationFormula_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_ValidationText_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ValidationText);


void __RPC_STUB UserProperty_get_ValidationText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE UserProperty_put_ValidationText_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [in] */ BSTR ValidationText);


void __RPC_STUB UserProperty_put_ValidationText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE UserProperty_get_Value_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *Value);


void __RPC_STUB UserProperty_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE UserProperty_put_Value_Proxy( 
    UserProperty __RPC_FAR * This,
    /* [in] */ VARIANT Value);


void __RPC_STUB UserProperty_put_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE UserProperty_Delete_Proxy( 
    UserProperty __RPC_FAR * This);


void __RPC_STUB UserProperty_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __UserProperty_INTERFACE_DEFINED__ */


#ifndef __Folders_INTERFACE_DEFINED__
#define __Folders_INTERFACE_DEFINED__

/* interface Folders */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Folders,0x00063040,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063040-0000-0000-C000-000000000046")
    Folders : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_RawTable( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Type,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetFirst( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetLast( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetNext( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetPrevious( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FoldersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Folders __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Folders __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Folders __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Folders __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Folders __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Folders __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Folders __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            Folders __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Item);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RawTable )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            Folders __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Type,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirst )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLast )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNext )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrevious )( 
            Folders __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            Folders __RPC_FAR * This,
            /* [in] */ long Index);
        
        END_INTERFACE
    } FoldersVtbl;

    interface Folders
    {
        CONST_VTBL struct FoldersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Folders_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Folders_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Folders_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Folders_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Folders_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Folders_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Folders_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Folders_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Folders_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Folders_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Folders_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Folders_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define Folders_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define Folders_get_RawTable(This,RawTable)	\
    (This)->lpVtbl -> get_RawTable(This,RawTable)

#define Folders_Add(This,Name,Type,Folder)	\
    (This)->lpVtbl -> Add(This,Name,Type,Folder)

#define Folders_GetFirst(This,Folder)	\
    (This)->lpVtbl -> GetFirst(This,Folder)

#define Folders_GetLast(This,Folder)	\
    (This)->lpVtbl -> GetLast(This,Folder)

#define Folders_GetNext(This,Folder)	\
    (This)->lpVtbl -> GetNext(This,Folder)

#define Folders_GetPrevious(This,Folder)	\
    (This)->lpVtbl -> GetPrevious(This,Folder)

#define Folders_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Folders_get_Application_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Folders_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Folders_get_Class_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Folders_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Folders_get_Session_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Folders_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Folders_get_Parent_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Folders_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Folders_get_Count_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB Folders_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_Item_Proxy( 
    Folders __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Folders_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE Folders_get_RawTable_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable);


void __RPC_STUB Folders_get_RawTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_Add_Proxy( 
    Folders __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [optional][in] */ VARIANT Type,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB Folders_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_GetFirst_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB Folders_GetFirst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_GetLast_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB Folders_GetLast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_GetNext_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB Folders_GetNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_GetPrevious_Proxy( 
    Folders __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB Folders_GetPrevious_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Folders_Remove_Proxy( 
    Folders __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB Folders_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Folders_INTERFACE_DEFINED__ */


#ifndef __MAPIFolder_INTERFACE_DEFINED__
#define __MAPIFolder_INTERFACE_DEFINED__

/* interface MAPIFolder */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_MAPIFolder,0x00063006,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063006-0000-0000-C000-000000000046")
    MAPIFolder : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DefaultItemType( 
            /* [retval][out] */ OlItemType __RPC_FAR *DefaultItemType) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DefaultMessageClass( 
            /* [retval][out] */ BSTR __RPC_FAR *DefaultMessageClass) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *Description) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR Description) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_EntryID( 
            /* [retval][out] */ BSTR __RPC_FAR *EntryID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Folders( 
            /* [retval][out] */ Folders __RPC_FAR *__RPC_FAR *Folders) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Items( 
            /* [retval][out] */ Items __RPC_FAR *__RPC_FAR *Items) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_StoreID( 
            /* [retval][out] */ BSTR __RPC_FAR *StoreID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_UnReadItemCount( 
            /* [retval][out] */ long __RPC_FAR *UnReadItemCount) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CopyTo( 
            /* [in] */ MAPIFolder __RPC_FAR *DestinationFolder,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetExplorer( 
            /* [optional][in] */ VARIANT DisplayMode,
            /* [retval][out] */ Explorer __RPC_FAR *__RPC_FAR *Explorer) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ MAPIFolder __RPC_FAR *DestinationFolder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct MAPIFolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            MAPIFolder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            MAPIFolder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            MAPIFolder __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultItemType )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ OlItemType __RPC_FAR *DefaultItemType);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DefaultMessageClass )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *DefaultMessageClass);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Description);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ BSTR Description);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntryID )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *EntryID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Folders )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ Folders __RPC_FAR *__RPC_FAR *Folders);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Items )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ Items __RPC_FAR *__RPC_FAR *Items);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StoreID )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *StoreID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UnReadItemCount )( 
            MAPIFolder __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *UnReadItemCount);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyTo )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ MAPIFolder __RPC_FAR *DestinationFolder,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            MAPIFolder __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            MAPIFolder __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExplorer )( 
            MAPIFolder __RPC_FAR * This,
            /* [optional][in] */ VARIANT DisplayMode,
            /* [retval][out] */ Explorer __RPC_FAR *__RPC_FAR *Explorer);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveTo )( 
            MAPIFolder __RPC_FAR * This,
            /* [in] */ MAPIFolder __RPC_FAR *DestinationFolder);
        
        END_INTERFACE
    } MAPIFolderVtbl;

    interface MAPIFolder
    {
        CONST_VTBL struct MAPIFolderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define MAPIFolder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define MAPIFolder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define MAPIFolder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define MAPIFolder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define MAPIFolder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define MAPIFolder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define MAPIFolder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define MAPIFolder_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define MAPIFolder_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define MAPIFolder_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define MAPIFolder_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define MAPIFolder_get_DefaultItemType(This,DefaultItemType)	\
    (This)->lpVtbl -> get_DefaultItemType(This,DefaultItemType)

#define MAPIFolder_get_DefaultMessageClass(This,DefaultMessageClass)	\
    (This)->lpVtbl -> get_DefaultMessageClass(This,DefaultMessageClass)

#define MAPIFolder_get_Description(This,Description)	\
    (This)->lpVtbl -> get_Description(This,Description)

#define MAPIFolder_put_Description(This,Description)	\
    (This)->lpVtbl -> put_Description(This,Description)

#define MAPIFolder_get_EntryID(This,EntryID)	\
    (This)->lpVtbl -> get_EntryID(This,EntryID)

#define MAPIFolder_get_Folders(This,Folders)	\
    (This)->lpVtbl -> get_Folders(This,Folders)

#define MAPIFolder_get_Items(This,Items)	\
    (This)->lpVtbl -> get_Items(This,Items)

#define MAPIFolder_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define MAPIFolder_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define MAPIFolder_get_StoreID(This,StoreID)	\
    (This)->lpVtbl -> get_StoreID(This,StoreID)

#define MAPIFolder_get_UnReadItemCount(This,UnReadItemCount)	\
    (This)->lpVtbl -> get_UnReadItemCount(This,UnReadItemCount)

#define MAPIFolder_CopyTo(This,DestinationFolder,Folder)	\
    (This)->lpVtbl -> CopyTo(This,DestinationFolder,Folder)

#define MAPIFolder_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define MAPIFolder_Display(This)	\
    (This)->lpVtbl -> Display(This)

#define MAPIFolder_GetExplorer(This,DisplayMode,Explorer)	\
    (This)->lpVtbl -> GetExplorer(This,DisplayMode,Explorer)

#define MAPIFolder_MoveTo(This,DestinationFolder)	\
    (This)->lpVtbl -> MoveTo(This,DestinationFolder)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Application_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB MAPIFolder_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Class_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB MAPIFolder_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Session_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB MAPIFolder_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Parent_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB MAPIFolder_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_DefaultItemType_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ OlItemType __RPC_FAR *DefaultItemType);


void __RPC_STUB MAPIFolder_get_DefaultItemType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_DefaultMessageClass_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *DefaultMessageClass);


void __RPC_STUB MAPIFolder_get_DefaultMessageClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Description_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Description);


void __RPC_STUB MAPIFolder_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_put_Description_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [in] */ BSTR Description);


void __RPC_STUB MAPIFolder_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_EntryID_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *EntryID);


void __RPC_STUB MAPIFolder_get_EntryID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Folders_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ Folders __RPC_FAR *__RPC_FAR *Folders);


void __RPC_STUB MAPIFolder_get_Folders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Items_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ Items __RPC_FAR *__RPC_FAR *Items);


void __RPC_STUB MAPIFolder_get_Items_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_Name_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB MAPIFolder_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_put_Name_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB MAPIFolder_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_StoreID_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *StoreID);


void __RPC_STUB MAPIFolder_get_StoreID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_get_UnReadItemCount_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *UnReadItemCount);


void __RPC_STUB MAPIFolder_get_UnReadItemCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_CopyTo_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [in] */ MAPIFolder __RPC_FAR *DestinationFolder,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB MAPIFolder_CopyTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_Delete_Proxy( 
    MAPIFolder __RPC_FAR * This);


void __RPC_STUB MAPIFolder_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_Display_Proxy( 
    MAPIFolder __RPC_FAR * This);


void __RPC_STUB MAPIFolder_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_GetExplorer_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [optional][in] */ VARIANT DisplayMode,
    /* [retval][out] */ Explorer __RPC_FAR *__RPC_FAR *Explorer);


void __RPC_STUB MAPIFolder_GetExplorer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE MAPIFolder_MoveTo_Proxy( 
    MAPIFolder __RPC_FAR * This,
    /* [in] */ MAPIFolder __RPC_FAR *DestinationFolder);


void __RPC_STUB MAPIFolder_MoveTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __MAPIFolder_INTERFACE_DEFINED__ */


#ifndef __Items_INTERFACE_DEFINED__
#define __Items_INTERFACE_DEFINED__

/* interface Items */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Items,0x00063041,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063041-0000-0000-C000-000000000046")
    Items : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_RawTable( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_IncludeRecurrences( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IncludeRecurrences) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_IncludeRecurrences( 
            /* [in] */ VARIANT_BOOL IncludeRecurrences) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [optional][in] */ VARIANT Type,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Find( 
            /* [in] */ BSTR Filter,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE FindNext( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetFirst( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetLast( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetNext( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE GetPrevious( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ResetColumns( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Restrict( 
            /* [in] */ BSTR Filter,
            /* [retval][out] */ Items __RPC_FAR *__RPC_FAR *Items) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetColumns( 
            /* [in] */ BSTR Columns) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Sort( 
            /* [in] */ BSTR Property,
            /* [optional][in] */ VARIANT Descending) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Items __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Items __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Items __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Items __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Items __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Items __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Items __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            Items __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RawTable )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IncludeRecurrences )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IncludeRecurrences);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IncludeRecurrences )( 
            Items __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL IncludeRecurrences);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            Items __RPC_FAR * This,
            /* [optional][in] */ VARIANT Type,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )( 
            Items __RPC_FAR * This,
            /* [in] */ BSTR Filter,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindNext )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirst )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLast )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNext )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrevious )( 
            Items __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            Items __RPC_FAR * This,
            /* [in] */ long Index);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetColumns )( 
            Items __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Restrict )( 
            Items __RPC_FAR * This,
            /* [in] */ BSTR Filter,
            /* [retval][out] */ Items __RPC_FAR *__RPC_FAR *Items);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColumns )( 
            Items __RPC_FAR * This,
            /* [in] */ BSTR Columns);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sort )( 
            Items __RPC_FAR * This,
            /* [in] */ BSTR Property,
            /* [optional][in] */ VARIANT Descending);
        
        END_INTERFACE
    } ItemsVtbl;

    interface Items
    {
        CONST_VTBL struct ItemsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Items_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Items_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Items_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Items_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Items_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Items_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Items_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Items_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Items_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Items_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Items_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Items_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define Items_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#define Items_get_RawTable(This,RawTable)	\
    (This)->lpVtbl -> get_RawTable(This,RawTable)

#define Items_get_IncludeRecurrences(This,IncludeRecurrences)	\
    (This)->lpVtbl -> get_IncludeRecurrences(This,IncludeRecurrences)

#define Items_put_IncludeRecurrences(This,IncludeRecurrences)	\
    (This)->lpVtbl -> put_IncludeRecurrences(This,IncludeRecurrences)

#define Items_Add(This,Type,Item)	\
    (This)->lpVtbl -> Add(This,Type,Item)

#define Items_Find(This,Filter,Item)	\
    (This)->lpVtbl -> Find(This,Filter,Item)

#define Items_FindNext(This,Item)	\
    (This)->lpVtbl -> FindNext(This,Item)

#define Items_GetFirst(This,Item)	\
    (This)->lpVtbl -> GetFirst(This,Item)

#define Items_GetLast(This,Item)	\
    (This)->lpVtbl -> GetLast(This,Item)

#define Items_GetNext(This,Item)	\
    (This)->lpVtbl -> GetNext(This,Item)

#define Items_GetPrevious(This,Item)	\
    (This)->lpVtbl -> GetPrevious(This,Item)

#define Items_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define Items_ResetColumns(This)	\
    (This)->lpVtbl -> ResetColumns(This)

#define Items_Restrict(This,Filter,Items)	\
    (This)->lpVtbl -> Restrict(This,Filter,Items)

#define Items_SetColumns(This,Columns)	\
    (This)->lpVtbl -> SetColumns(This,Columns)

#define Items_Sort(This,Property,Descending)	\
    (This)->lpVtbl -> Sort(This,Property,Descending)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_Application_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Items_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_Class_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Items_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_Session_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Items_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_Parent_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Items_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_Count_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB Items_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_Item_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_RawTable_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *RawTable);


void __RPC_STUB Items_get_RawTable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Items_get_IncludeRecurrences_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IncludeRecurrences);


void __RPC_STUB Items_get_IncludeRecurrences_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE Items_put_IncludeRecurrences_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL IncludeRecurrences);


void __RPC_STUB Items_put_IncludeRecurrences_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_Add_Proxy( 
    Items __RPC_FAR * This,
    /* [optional][in] */ VARIANT Type,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_Find_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ BSTR Filter,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_Find_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_FindNext_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_FindNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_GetFirst_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_GetFirst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_GetLast_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_GetLast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_GetNext_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_GetNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_GetPrevious_Proxy( 
    Items __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Items_GetPrevious_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_Remove_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ long Index);


void __RPC_STUB Items_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_ResetColumns_Proxy( 
    Items __RPC_FAR * This);


void __RPC_STUB Items_ResetColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_Restrict_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ BSTR Filter,
    /* [retval][out] */ Items __RPC_FAR *__RPC_FAR *Items);


void __RPC_STUB Items_Restrict_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_SetColumns_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ BSTR Columns);


void __RPC_STUB Items_SetColumns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Items_Sort_Proxy( 
    Items __RPC_FAR * This,
    /* [in] */ BSTR Property,
    /* [optional][in] */ VARIANT Descending);


void __RPC_STUB Items_Sort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Items_INTERFACE_DEFINED__ */


#ifndef __Explorer_INTERFACE_DEFINED__
#define __Explorer_INTERFACE_DEFINED__

/* interface Explorer */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Explorer,0x00063003,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063003-0000-0000-C000-000000000046")
    Explorer : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CommandBars( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CommandBars) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CurrentFolder( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *CurrentFolder) = 0;
        
        virtual /* [helpcontext][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_CurrentFolder( 
            /* [in] */ MAPIFolder __RPC_FAR *CurrentFolder) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ExplorerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Explorer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Explorer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Explorer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Explorer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Explorer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Explorer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Explorer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Explorer __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Explorer __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Explorer __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Explorer __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommandBars )( 
            Explorer __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CommandBars);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentFolder )( 
            Explorer __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *CurrentFolder);
        
        /* [helpcontext][propputref][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_CurrentFolder )( 
            Explorer __RPC_FAR * This,
            /* [in] */ MAPIFolder __RPC_FAR *CurrentFolder);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            Explorer __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            Explorer __RPC_FAR * This);
        
        END_INTERFACE
    } ExplorerVtbl;

    interface Explorer
    {
        CONST_VTBL struct ExplorerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Explorer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Explorer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Explorer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Explorer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Explorer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Explorer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Explorer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Explorer_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Explorer_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Explorer_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Explorer_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Explorer_get_CommandBars(This,CommandBars)	\
    (This)->lpVtbl -> get_CommandBars(This,CommandBars)

#define Explorer_get_CurrentFolder(This,CurrentFolder)	\
    (This)->lpVtbl -> get_CurrentFolder(This,CurrentFolder)

#define Explorer_putref_CurrentFolder(This,CurrentFolder)	\
    (This)->lpVtbl -> putref_CurrentFolder(This,CurrentFolder)

#define Explorer_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define Explorer_Display(This)	\
    (This)->lpVtbl -> Display(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Explorer_get_Application_Proxy( 
    Explorer __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Explorer_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Explorer_get_Class_Proxy( 
    Explorer __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Explorer_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Explorer_get_Session_Proxy( 
    Explorer __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Explorer_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Explorer_get_Parent_Proxy( 
    Explorer __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Explorer_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Explorer_get_CommandBars_Proxy( 
    Explorer __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CommandBars);


void __RPC_STUB Explorer_get_CommandBars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Explorer_get_CurrentFolder_Proxy( 
    Explorer __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *CurrentFolder);


void __RPC_STUB Explorer_get_CurrentFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propputref][id] */ HRESULT STDMETHODCALLTYPE Explorer_putref_CurrentFolder_Proxy( 
    Explorer __RPC_FAR * This,
    /* [in] */ MAPIFolder __RPC_FAR *CurrentFolder);


void __RPC_STUB Explorer_putref_CurrentFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Explorer_Close_Proxy( 
    Explorer __RPC_FAR * This);


void __RPC_STUB Explorer_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Explorer_Display_Proxy( 
    Explorer __RPC_FAR * This);


void __RPC_STUB Explorer_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Explorer_INTERFACE_DEFINED__ */


#ifndef __Inspector_INTERFACE_DEFINED__
#define __Inspector_INTERFACE_DEFINED__

/* interface Inspector */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Inspector,0x00063005,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063005-0000-0000-C000-000000000046")
    Inspector : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CommandBars( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CommandBars) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CurrentItem( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CurrentItem) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_EditorType( 
            /* [retval][out] */ OlEditorType __RPC_FAR *EditorType) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ModifiedFormPages( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ModifiedFormPages) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [in] */ OlInspectorClose SaveMode) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Display( 
            /* [optional][in] */ VARIANT Modal) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE HideFormPage( 
            /* [in] */ BSTR PageName) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE IsWordMail( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsWordMail) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE SetCurrentFormPage( 
            /* [in] */ BSTR PageName) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ShowFormPage( 
            /* [in] */ BSTR PageName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_HTMLEditor( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *HTMLEditor) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_WordEditor( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *WordEditor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct InspectorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Inspector __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Inspector __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Inspector __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Inspector __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Inspector __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Inspector __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Inspector __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommandBars )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CommandBars);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentItem )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CurrentItem);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EditorType )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ OlEditorType __RPC_FAR *EditorType);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModifiedFormPages )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ModifiedFormPages);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            Inspector __RPC_FAR * This,
            /* [in] */ OlInspectorClose SaveMode);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            Inspector __RPC_FAR * This,
            /* [optional][in] */ VARIANT Modal);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HideFormPage )( 
            Inspector __RPC_FAR * This,
            /* [in] */ BSTR PageName);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsWordMail )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsWordMail);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentFormPage )( 
            Inspector __RPC_FAR * This,
            /* [in] */ BSTR PageName);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowFormPage )( 
            Inspector __RPC_FAR * This,
            /* [in] */ BSTR PageName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HTMLEditor )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *HTMLEditor);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WordEditor )( 
            Inspector __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *WordEditor);
        
        END_INTERFACE
    } InspectorVtbl;

    interface Inspector
    {
        CONST_VTBL struct InspectorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Inspector_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Inspector_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Inspector_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Inspector_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Inspector_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Inspector_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Inspector_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Inspector_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Inspector_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Inspector_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Inspector_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Inspector_get_CommandBars(This,CommandBars)	\
    (This)->lpVtbl -> get_CommandBars(This,CommandBars)

#define Inspector_get_CurrentItem(This,CurrentItem)	\
    (This)->lpVtbl -> get_CurrentItem(This,CurrentItem)

#define Inspector_get_EditorType(This,EditorType)	\
    (This)->lpVtbl -> get_EditorType(This,EditorType)

#define Inspector_get_ModifiedFormPages(This,ModifiedFormPages)	\
    (This)->lpVtbl -> get_ModifiedFormPages(This,ModifiedFormPages)

#define Inspector_Close(This,SaveMode)	\
    (This)->lpVtbl -> Close(This,SaveMode)

#define Inspector_Display(This,Modal)	\
    (This)->lpVtbl -> Display(This,Modal)

#define Inspector_HideFormPage(This,PageName)	\
    (This)->lpVtbl -> HideFormPage(This,PageName)

#define Inspector_IsWordMail(This,IsWordMail)	\
    (This)->lpVtbl -> IsWordMail(This,IsWordMail)

#define Inspector_SetCurrentFormPage(This,PageName)	\
    (This)->lpVtbl -> SetCurrentFormPage(This,PageName)

#define Inspector_ShowFormPage(This,PageName)	\
    (This)->lpVtbl -> ShowFormPage(This,PageName)

#define Inspector_get_HTMLEditor(This,HTMLEditor)	\
    (This)->lpVtbl -> get_HTMLEditor(This,HTMLEditor)

#define Inspector_get_WordEditor(This,WordEditor)	\
    (This)->lpVtbl -> get_WordEditor(This,WordEditor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_Application_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Inspector_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_Class_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Inspector_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_Session_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Inspector_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_Parent_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Inspector_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_CommandBars_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CommandBars);


void __RPC_STUB Inspector_get_CommandBars_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_CurrentItem_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *CurrentItem);


void __RPC_STUB Inspector_get_CurrentItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_EditorType_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ OlEditorType __RPC_FAR *EditorType);


void __RPC_STUB Inspector_get_EditorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_ModifiedFormPages_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ModifiedFormPages);


void __RPC_STUB Inspector_get_ModifiedFormPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Inspector_Close_Proxy( 
    Inspector __RPC_FAR * This,
    /* [in] */ OlInspectorClose SaveMode);


void __RPC_STUB Inspector_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Inspector_Display_Proxy( 
    Inspector __RPC_FAR * This,
    /* [optional][in] */ VARIANT Modal);


void __RPC_STUB Inspector_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Inspector_HideFormPage_Proxy( 
    Inspector __RPC_FAR * This,
    /* [in] */ BSTR PageName);


void __RPC_STUB Inspector_HideFormPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Inspector_IsWordMail_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *IsWordMail);


void __RPC_STUB Inspector_IsWordMail_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Inspector_SetCurrentFormPage_Proxy( 
    Inspector __RPC_FAR * This,
    /* [in] */ BSTR PageName);


void __RPC_STUB Inspector_SetCurrentFormPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Inspector_ShowFormPage_Proxy( 
    Inspector __RPC_FAR * This,
    /* [in] */ BSTR PageName);


void __RPC_STUB Inspector_ShowFormPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_HTMLEditor_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *HTMLEditor);


void __RPC_STUB Inspector_get_HTMLEditor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Inspector_get_WordEditor_Proxy( 
    Inspector __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *WordEditor);


void __RPC_STUB Inspector_get_WordEditor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Inspector_INTERFACE_DEFINED__ */


#ifndef ___MailItem_INTERFACE_DEFINED__
#define ___MailItem_INTERFACE_DEFINED__

/* interface _MailItem */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID__MailItem,0x00063034,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00063034-0000-0000-C000-000000000046")
    _MailItem : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Actions( 
            /* [retval][out] */ Actions __RPC_FAR *__RPC_FAR *Actions) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Attachments( 
            /* [retval][out] */ Attachments __RPC_FAR *__RPC_FAR *Attachments) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_BillingInformation( 
            /* [retval][out] */ BSTR __RPC_FAR *BillingInformation) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_BillingInformation( 
            /* [in] */ BSTR BillingInformation) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Body( 
            /* [retval][out] */ BSTR __RPC_FAR *Body) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Body( 
            /* [in] */ BSTR Body) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Categories( 
            /* [retval][out] */ BSTR __RPC_FAR *Categories) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Categories( 
            /* [in] */ BSTR Categories) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Companies( 
            /* [retval][out] */ BSTR __RPC_FAR *Companies) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Companies( 
            /* [in] */ BSTR Companies) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ConversationIndex( 
            /* [retval][out] */ BSTR __RPC_FAR *ConversationIndex) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ConversationTopic( 
            /* [retval][out] */ BSTR __RPC_FAR *ConversationTopic) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CreationTime( 
            /* [retval][out] */ DATE __RPC_FAR *CreationTime) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_EntryID( 
            /* [retval][out] */ BSTR __RPC_FAR *EntryID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_FormDescription( 
            /* [retval][out] */ FormDescription __RPC_FAR *__RPC_FAR *FormDescription) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_GetInspector( 
            /* [retval][out] */ Inspector __RPC_FAR *__RPC_FAR *GetInspector) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Importance( 
            /* [retval][out] */ OlImportance __RPC_FAR *Importance) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Importance( 
            /* [in] */ OlImportance Importance) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_LastModificationTime( 
            /* [retval][out] */ DATE __RPC_FAR *LastModificationTime) = 0;
        
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_MAPIOBJECT( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_MessageClass( 
            /* [retval][out] */ BSTR __RPC_FAR *MessageClass) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_MessageClass( 
            /* [in] */ BSTR MessageClass) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Mileage( 
            /* [retval][out] */ BSTR __RPC_FAR *Mileage) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Mileage( 
            /* [in] */ BSTR Mileage) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_NoAging( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *NoAging) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_NoAging( 
            /* [in] */ VARIANT_BOOL NoAging) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OutlookInternalVersion( 
            /* [retval][out] */ long __RPC_FAR *OutlookInternalVersion) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OutlookVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *OutlookVersion) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Saved( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Saved) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Sensitivity( 
            /* [retval][out] */ OlSensitivity __RPC_FAR *Sensitivity) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Sensitivity( 
            /* [in] */ OlSensitivity Sensitivity) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ long __RPC_FAR *Size) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Subject( 
            /* [retval][out] */ BSTR __RPC_FAR *Subject) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_Subject( 
            /* [in] */ BSTR Subject) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_UnRead( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UnRead) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_UnRead( 
            /* [in] */ VARIANT_BOOL UnRead) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_UserProperties( 
            /* [retval][out] */ UserProperties __RPC_FAR *__RPC_FAR *UserProperties) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Close( 
            /* [in] */ OlInspectorClose SaveMode) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Copy( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Delete( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Display( 
            /* [optional][in] */ VARIANT Modal) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ MAPIFolder __RPC_FAR *DestFldr,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE PrintOut( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE SaveAs( 
            /* [in] */ BSTR Path,
            /* [optional][in] */ VARIANT Type) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_AlternateRecipientAllowed( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AlternateRecipientAllowed) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_AlternateRecipientAllowed( 
            /* [in] */ VARIANT_BOOL AlternateRecipientAllowed) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_AutoForwarded( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AutoForwarded) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_AutoForwarded( 
            /* [in] */ VARIANT_BOOL AutoForwarded) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_BCC( 
            /* [retval][out] */ BSTR __RPC_FAR *BCC) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_BCC( 
            /* [in] */ BSTR BCC) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_CC( 
            /* [retval][out] */ BSTR __RPC_FAR *CC) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_CC( 
            /* [in] */ BSTR CC) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DeferredDeliveryTime( 
            /* [retval][out] */ DATE __RPC_FAR *DeferredDeliveryTime) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DeferredDeliveryTime( 
            /* [in] */ DATE DeferredDeliveryTime) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_DeleteAfterSubmit( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *DeleteAfterSubmit) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_DeleteAfterSubmit( 
            /* [in] */ VARIANT_BOOL DeleteAfterSubmit) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ExpiryTime( 
            /* [retval][out] */ DATE __RPC_FAR *ExpiryTime) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ExpiryTime( 
            /* [in] */ DATE ExpiryTime) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_FlagDueBy( 
            /* [retval][out] */ DATE __RPC_FAR *FlagDueBy) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_FlagDueBy( 
            /* [in] */ DATE FlagDueBy) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_FlagRequest( 
            /* [retval][out] */ BSTR __RPC_FAR *FlagRequest) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_FlagRequest( 
            /* [in] */ BSTR FlagRequest) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_FlagStatus( 
            /* [retval][out] */ OlFlagStatus __RPC_FAR *FlagStatus) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_FlagStatus( 
            /* [in] */ OlFlagStatus FlagStatus) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_HTMLBody( 
            /* [retval][out] */ BSTR __RPC_FAR *HTMLBody) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_HTMLBody( 
            /* [in] */ BSTR HTMLBody) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OriginatorDeliveryReportRequested( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *OriginatorDeliveryReportRequested) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_OriginatorDeliveryReportRequested( 
            /* [in] */ VARIANT_BOOL OriginatorDeliveryReportRequested) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReadReceiptRequested( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReadReceiptRequested) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReadReceiptRequested( 
            /* [in] */ VARIANT_BOOL ReadReceiptRequested) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReceivedByEntryID( 
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedByEntryID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReceivedByName( 
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedByName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReceivedOnBehalfOfEntryID( 
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedOnBehalfOfEntryID) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReceivedOnBehalfOfName( 
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedOnBehalfOfName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReceivedTime( 
            /* [retval][out] */ DATE __RPC_FAR *ReceivedTime) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_RecipientReassignmentProhibited( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *RecipientReassignmentProhibited) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_RecipientReassignmentProhibited( 
            /* [in] */ VARIANT_BOOL RecipientReassignmentProhibited) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Recipients( 
            /* [retval][out] */ Recipients __RPC_FAR *__RPC_FAR *Recipients) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReminderOverrideDefault( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderOverrideDefault) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReminderOverrideDefault( 
            /* [in] */ VARIANT_BOOL ReminderOverrideDefault) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReminderPlaySound( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderPlaySound) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReminderPlaySound( 
            /* [in] */ VARIANT_BOOL ReminderPlaySound) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReminderSet( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderSet) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReminderSet( 
            /* [in] */ VARIANT_BOOL ReminderSet) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReminderSoundFile( 
            /* [retval][out] */ BSTR __RPC_FAR *ReminderSoundFile) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReminderSoundFile( 
            /* [in] */ BSTR ReminderSoundFile) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReminderTime( 
            /* [retval][out] */ DATE __RPC_FAR *ReminderTime) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_ReminderTime( 
            /* [in] */ DATE ReminderTime) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_RemoteStatus( 
            /* [retval][out] */ OlRemoteStatus __RPC_FAR *RemoteStatus) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_RemoteStatus( 
            /* [in] */ OlRemoteStatus RemoteStatus) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReplyRecipientNames( 
            /* [retval][out] */ BSTR __RPC_FAR *ReplyRecipientNames) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReplyRecipients( 
            /* [retval][out] */ Recipients __RPC_FAR *__RPC_FAR *ReplyRecipients) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_SaveSentMessageFolder( 
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *SaveSentMessageFolder) = 0;
        
        virtual /* [helpcontext][propputref][id] */ HRESULT STDMETHODCALLTYPE putref_SaveSentMessageFolder( 
            /* [in] */ MAPIFolder __RPC_FAR *SaveSentMessageFolder) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_SenderName( 
            /* [retval][out] */ BSTR __RPC_FAR *SenderName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Sent( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Sent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_SentOn( 
            /* [retval][out] */ DATE __RPC_FAR *SentOn) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_SentOnBehalfOfName( 
            /* [retval][out] */ BSTR __RPC_FAR *SentOnBehalfOfName) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_SentOnBehalfOfName( 
            /* [in] */ BSTR SentOnBehalfOfName) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Submitted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Submitted) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_To( 
            /* [retval][out] */ BSTR __RPC_FAR *To) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_To( 
            /* [in] */ BSTR To) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_VotingOptions( 
            /* [retval][out] */ BSTR __RPC_FAR *VotingOptions) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_VotingOptions( 
            /* [in] */ BSTR VotingOptions) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_VotingResponse( 
            /* [retval][out] */ BSTR __RPC_FAR *VotingResponse) = 0;
        
        virtual /* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE put_VotingResponse( 
            /* [in] */ BSTR VotingResponse) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ClearConversationIndex( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Forward( 
            /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Reply( 
            /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ReplyAll( 
            /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Send( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _MailItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _MailItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _MailItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _MailItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Actions )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ Actions __RPC_FAR *__RPC_FAR *Actions);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Attachments )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ Attachments __RPC_FAR *__RPC_FAR *Attachments);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BillingInformation )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *BillingInformation);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BillingInformation )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR BillingInformation);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Body )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Body);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Body )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR Body);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Categories )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Categories);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Categories )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR Categories);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Companies )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Companies);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Companies )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR Companies);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConversationIndex )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ConversationIndex);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConversationTopic )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ConversationTopic);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreationTime )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *CreationTime);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EntryID )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *EntryID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FormDescription )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ FormDescription __RPC_FAR *__RPC_FAR *FormDescription);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetInspector )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ Inspector __RPC_FAR *__RPC_FAR *GetInspector);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Importance )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ OlImportance __RPC_FAR *Importance);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Importance )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ OlImportance Importance);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastModificationTime )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *LastModificationTime);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MAPIOBJECT )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageClass )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *MessageClass);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MessageClass )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR MessageClass);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Mileage )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Mileage);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Mileage )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR Mileage);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NoAging )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *NoAging);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NoAging )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL NoAging);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutlookInternalVersion )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *OutlookInternalVersion);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OutlookVersion )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *OutlookVersion);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Saved )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Saved);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Sensitivity )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ OlSensitivity __RPC_FAR *Sensitivity);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Sensitivity )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ OlSensitivity Sensitivity);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Size);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Subject )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Subject);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Subject )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR Subject);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UnRead )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UnRead);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UnRead )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL UnRead);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserProperties )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ UserProperties __RPC_FAR *__RPC_FAR *UserProperties);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ OlInspectorClose SaveMode);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Copy )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            _MailItem __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            _MailItem __RPC_FAR * This,
            /* [optional][in] */ VARIANT Modal);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ MAPIFolder __RPC_FAR *DestFldr,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PrintOut )( 
            _MailItem __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            _MailItem __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAs )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR Path,
            /* [optional][in] */ VARIANT Type);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AlternateRecipientAllowed )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AlternateRecipientAllowed);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AlternateRecipientAllowed )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL AlternateRecipientAllowed);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoForwarded )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AutoForwarded);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoForwarded )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL AutoForwarded);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BCC )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *BCC);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BCC )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR BCC);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CC )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *CC);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CC )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR CC);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeferredDeliveryTime )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *DeferredDeliveryTime);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeferredDeliveryTime )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ DATE DeferredDeliveryTime);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteAfterSubmit )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *DeleteAfterSubmit);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeleteAfterSubmit )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL DeleteAfterSubmit);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpiryTime )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *ExpiryTime);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ExpiryTime )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ DATE ExpiryTime);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FlagDueBy )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *FlagDueBy);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FlagDueBy )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ DATE FlagDueBy);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FlagRequest )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *FlagRequest);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FlagRequest )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR FlagRequest);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FlagStatus )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ OlFlagStatus __RPC_FAR *FlagStatus);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FlagStatus )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ OlFlagStatus FlagStatus);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HTMLBody )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *HTMLBody);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HTMLBody )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR HTMLBody);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OriginatorDeliveryReportRequested )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *OriginatorDeliveryReportRequested);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OriginatorDeliveryReportRequested )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL OriginatorDeliveryReportRequested);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadReceiptRequested )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReadReceiptRequested);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReadReceiptRequested )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL ReadReceiptRequested);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceivedByEntryID )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedByEntryID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceivedByName )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedByName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceivedOnBehalfOfEntryID )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedOnBehalfOfEntryID);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceivedOnBehalfOfName )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ReceivedOnBehalfOfName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceivedTime )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *ReceivedTime);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RecipientReassignmentProhibited )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *RecipientReassignmentProhibited);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RecipientReassignmentProhibited )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL RecipientReassignmentProhibited);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Recipients )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ Recipients __RPC_FAR *__RPC_FAR *Recipients);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReminderOverrideDefault )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderOverrideDefault);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReminderOverrideDefault )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL ReminderOverrideDefault);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReminderPlaySound )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderPlaySound);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReminderPlaySound )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL ReminderPlaySound);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReminderSet )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderSet);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReminderSet )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL ReminderSet);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReminderSoundFile )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ReminderSoundFile);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReminderSoundFile )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR ReminderSoundFile);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReminderTime )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *ReminderTime);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReminderTime )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ DATE ReminderTime);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteStatus )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ OlRemoteStatus __RPC_FAR *RemoteStatus);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RemoteStatus )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ OlRemoteStatus RemoteStatus);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReplyRecipientNames )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ReplyRecipientNames);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReplyRecipients )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ Recipients __RPC_FAR *__RPC_FAR *ReplyRecipients);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SaveSentMessageFolder )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *SaveSentMessageFolder);
        
        /* [helpcontext][propputref][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *putref_SaveSentMessageFolder )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ MAPIFolder __RPC_FAR *SaveSentMessageFolder);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SenderName )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *SenderName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Sent )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Sent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SentOn )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *SentOn);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SentOnBehalfOfName )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *SentOnBehalfOfName);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SentOnBehalfOfName )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR SentOnBehalfOfName);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Submitted )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Submitted);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_To )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *To);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_To )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR To);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VotingOptions )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *VotingOptions);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VotingOptions )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR VotingOptions);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VotingResponse )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *VotingResponse);
        
        /* [helpcontext][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_VotingResponse )( 
            _MailItem __RPC_FAR * This,
            /* [in] */ BSTR VotingResponse);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearConversationIndex )( 
            _MailItem __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forward )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reply )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReplyAll )( 
            _MailItem __RPC_FAR * This,
            /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            _MailItem __RPC_FAR * This);
        
        END_INTERFACE
    } _MailItemVtbl;

    interface _MailItem
    {
        CONST_VTBL struct _MailItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _MailItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _MailItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _MailItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _MailItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _MailItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _MailItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _MailItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define _MailItem_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define _MailItem_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define _MailItem_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define _MailItem_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define _MailItem_get_Actions(This,Actions)	\
    (This)->lpVtbl -> get_Actions(This,Actions)

#define _MailItem_get_Attachments(This,Attachments)	\
    (This)->lpVtbl -> get_Attachments(This,Attachments)

#define _MailItem_get_BillingInformation(This,BillingInformation)	\
    (This)->lpVtbl -> get_BillingInformation(This,BillingInformation)

#define _MailItem_put_BillingInformation(This,BillingInformation)	\
    (This)->lpVtbl -> put_BillingInformation(This,BillingInformation)

#define _MailItem_get_Body(This,Body)	\
    (This)->lpVtbl -> get_Body(This,Body)

#define _MailItem_put_Body(This,Body)	\
    (This)->lpVtbl -> put_Body(This,Body)

#define _MailItem_get_Categories(This,Categories)	\
    (This)->lpVtbl -> get_Categories(This,Categories)

#define _MailItem_put_Categories(This,Categories)	\
    (This)->lpVtbl -> put_Categories(This,Categories)

#define _MailItem_get_Companies(This,Companies)	\
    (This)->lpVtbl -> get_Companies(This,Companies)

#define _MailItem_put_Companies(This,Companies)	\
    (This)->lpVtbl -> put_Companies(This,Companies)

#define _MailItem_get_ConversationIndex(This,ConversationIndex)	\
    (This)->lpVtbl -> get_ConversationIndex(This,ConversationIndex)

#define _MailItem_get_ConversationTopic(This,ConversationTopic)	\
    (This)->lpVtbl -> get_ConversationTopic(This,ConversationTopic)

#define _MailItem_get_CreationTime(This,CreationTime)	\
    (This)->lpVtbl -> get_CreationTime(This,CreationTime)

#define _MailItem_get_EntryID(This,EntryID)	\
    (This)->lpVtbl -> get_EntryID(This,EntryID)

#define _MailItem_get_FormDescription(This,FormDescription)	\
    (This)->lpVtbl -> get_FormDescription(This,FormDescription)

#define _MailItem_get_GetInspector(This,GetInspector)	\
    (This)->lpVtbl -> get_GetInspector(This,GetInspector)

#define _MailItem_get_Importance(This,Importance)	\
    (This)->lpVtbl -> get_Importance(This,Importance)

#define _MailItem_put_Importance(This,Importance)	\
    (This)->lpVtbl -> put_Importance(This,Importance)

#define _MailItem_get_LastModificationTime(This,LastModificationTime)	\
    (This)->lpVtbl -> get_LastModificationTime(This,LastModificationTime)

#define _MailItem_get_MAPIOBJECT(This,MAPIOBJECT)	\
    (This)->lpVtbl -> get_MAPIOBJECT(This,MAPIOBJECT)

#define _MailItem_get_MessageClass(This,MessageClass)	\
    (This)->lpVtbl -> get_MessageClass(This,MessageClass)

#define _MailItem_put_MessageClass(This,MessageClass)	\
    (This)->lpVtbl -> put_MessageClass(This,MessageClass)

#define _MailItem_get_Mileage(This,Mileage)	\
    (This)->lpVtbl -> get_Mileage(This,Mileage)

#define _MailItem_put_Mileage(This,Mileage)	\
    (This)->lpVtbl -> put_Mileage(This,Mileage)

#define _MailItem_get_NoAging(This,NoAging)	\
    (This)->lpVtbl -> get_NoAging(This,NoAging)

#define _MailItem_put_NoAging(This,NoAging)	\
    (This)->lpVtbl -> put_NoAging(This,NoAging)

#define _MailItem_get_OutlookInternalVersion(This,OutlookInternalVersion)	\
    (This)->lpVtbl -> get_OutlookInternalVersion(This,OutlookInternalVersion)

#define _MailItem_get_OutlookVersion(This,OutlookVersion)	\
    (This)->lpVtbl -> get_OutlookVersion(This,OutlookVersion)

#define _MailItem_get_Saved(This,Saved)	\
    (This)->lpVtbl -> get_Saved(This,Saved)

#define _MailItem_get_Sensitivity(This,Sensitivity)	\
    (This)->lpVtbl -> get_Sensitivity(This,Sensitivity)

#define _MailItem_put_Sensitivity(This,Sensitivity)	\
    (This)->lpVtbl -> put_Sensitivity(This,Sensitivity)

#define _MailItem_get_Size(This,Size)	\
    (This)->lpVtbl -> get_Size(This,Size)

#define _MailItem_get_Subject(This,Subject)	\
    (This)->lpVtbl -> get_Subject(This,Subject)

#define _MailItem_put_Subject(This,Subject)	\
    (This)->lpVtbl -> put_Subject(This,Subject)

#define _MailItem_get_UnRead(This,UnRead)	\
    (This)->lpVtbl -> get_UnRead(This,UnRead)

#define _MailItem_put_UnRead(This,UnRead)	\
    (This)->lpVtbl -> put_UnRead(This,UnRead)

#define _MailItem_get_UserProperties(This,UserProperties)	\
    (This)->lpVtbl -> get_UserProperties(This,UserProperties)

#define _MailItem_Close(This,SaveMode)	\
    (This)->lpVtbl -> Close(This,SaveMode)

#define _MailItem_Copy(This,Item)	\
    (This)->lpVtbl -> Copy(This,Item)

#define _MailItem_Delete(This)	\
    (This)->lpVtbl -> Delete(This)

#define _MailItem_Display(This,Modal)	\
    (This)->lpVtbl -> Display(This,Modal)

#define _MailItem_Move(This,DestFldr,Item)	\
    (This)->lpVtbl -> Move(This,DestFldr,Item)

#define _MailItem_PrintOut(This)	\
    (This)->lpVtbl -> PrintOut(This)

#define _MailItem_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define _MailItem_SaveAs(This,Path,Type)	\
    (This)->lpVtbl -> SaveAs(This,Path,Type)

#define _MailItem_get_AlternateRecipientAllowed(This,AlternateRecipientAllowed)	\
    (This)->lpVtbl -> get_AlternateRecipientAllowed(This,AlternateRecipientAllowed)

#define _MailItem_put_AlternateRecipientAllowed(This,AlternateRecipientAllowed)	\
    (This)->lpVtbl -> put_AlternateRecipientAllowed(This,AlternateRecipientAllowed)

#define _MailItem_get_AutoForwarded(This,AutoForwarded)	\
    (This)->lpVtbl -> get_AutoForwarded(This,AutoForwarded)

#define _MailItem_put_AutoForwarded(This,AutoForwarded)	\
    (This)->lpVtbl -> put_AutoForwarded(This,AutoForwarded)

#define _MailItem_get_BCC(This,BCC)	\
    (This)->lpVtbl -> get_BCC(This,BCC)

#define _MailItem_put_BCC(This,BCC)	\
    (This)->lpVtbl -> put_BCC(This,BCC)

#define _MailItem_get_CC(This,CC)	\
    (This)->lpVtbl -> get_CC(This,CC)

#define _MailItem_put_CC(This,CC)	\
    (This)->lpVtbl -> put_CC(This,CC)

#define _MailItem_get_DeferredDeliveryTime(This,DeferredDeliveryTime)	\
    (This)->lpVtbl -> get_DeferredDeliveryTime(This,DeferredDeliveryTime)

#define _MailItem_put_DeferredDeliveryTime(This,DeferredDeliveryTime)	\
    (This)->lpVtbl -> put_DeferredDeliveryTime(This,DeferredDeliveryTime)

#define _MailItem_get_DeleteAfterSubmit(This,DeleteAfterSubmit)	\
    (This)->lpVtbl -> get_DeleteAfterSubmit(This,DeleteAfterSubmit)

#define _MailItem_put_DeleteAfterSubmit(This,DeleteAfterSubmit)	\
    (This)->lpVtbl -> put_DeleteAfterSubmit(This,DeleteAfterSubmit)

#define _MailItem_get_ExpiryTime(This,ExpiryTime)	\
    (This)->lpVtbl -> get_ExpiryTime(This,ExpiryTime)

#define _MailItem_put_ExpiryTime(This,ExpiryTime)	\
    (This)->lpVtbl -> put_ExpiryTime(This,ExpiryTime)

#define _MailItem_get_FlagDueBy(This,FlagDueBy)	\
    (This)->lpVtbl -> get_FlagDueBy(This,FlagDueBy)

#define _MailItem_put_FlagDueBy(This,FlagDueBy)	\
    (This)->lpVtbl -> put_FlagDueBy(This,FlagDueBy)

#define _MailItem_get_FlagRequest(This,FlagRequest)	\
    (This)->lpVtbl -> get_FlagRequest(This,FlagRequest)

#define _MailItem_put_FlagRequest(This,FlagRequest)	\
    (This)->lpVtbl -> put_FlagRequest(This,FlagRequest)

#define _MailItem_get_FlagStatus(This,FlagStatus)	\
    (This)->lpVtbl -> get_FlagStatus(This,FlagStatus)

#define _MailItem_put_FlagStatus(This,FlagStatus)	\
    (This)->lpVtbl -> put_FlagStatus(This,FlagStatus)

#define _MailItem_get_HTMLBody(This,HTMLBody)	\
    (This)->lpVtbl -> get_HTMLBody(This,HTMLBody)

#define _MailItem_put_HTMLBody(This,HTMLBody)	\
    (This)->lpVtbl -> put_HTMLBody(This,HTMLBody)

#define _MailItem_get_OriginatorDeliveryReportRequested(This,OriginatorDeliveryReportRequested)	\
    (This)->lpVtbl -> get_OriginatorDeliveryReportRequested(This,OriginatorDeliveryReportRequested)

#define _MailItem_put_OriginatorDeliveryReportRequested(This,OriginatorDeliveryReportRequested)	\
    (This)->lpVtbl -> put_OriginatorDeliveryReportRequested(This,OriginatorDeliveryReportRequested)

#define _MailItem_get_ReadReceiptRequested(This,ReadReceiptRequested)	\
    (This)->lpVtbl -> get_ReadReceiptRequested(This,ReadReceiptRequested)

#define _MailItem_put_ReadReceiptRequested(This,ReadReceiptRequested)	\
    (This)->lpVtbl -> put_ReadReceiptRequested(This,ReadReceiptRequested)

#define _MailItem_get_ReceivedByEntryID(This,ReceivedByEntryID)	\
    (This)->lpVtbl -> get_ReceivedByEntryID(This,ReceivedByEntryID)

#define _MailItem_get_ReceivedByName(This,ReceivedByName)	\
    (This)->lpVtbl -> get_ReceivedByName(This,ReceivedByName)

#define _MailItem_get_ReceivedOnBehalfOfEntryID(This,ReceivedOnBehalfOfEntryID)	\
    (This)->lpVtbl -> get_ReceivedOnBehalfOfEntryID(This,ReceivedOnBehalfOfEntryID)

#define _MailItem_get_ReceivedOnBehalfOfName(This,ReceivedOnBehalfOfName)	\
    (This)->lpVtbl -> get_ReceivedOnBehalfOfName(This,ReceivedOnBehalfOfName)

#define _MailItem_get_ReceivedTime(This,ReceivedTime)	\
    (This)->lpVtbl -> get_ReceivedTime(This,ReceivedTime)

#define _MailItem_get_RecipientReassignmentProhibited(This,RecipientReassignmentProhibited)	\
    (This)->lpVtbl -> get_RecipientReassignmentProhibited(This,RecipientReassignmentProhibited)

#define _MailItem_put_RecipientReassignmentProhibited(This,RecipientReassignmentProhibited)	\
    (This)->lpVtbl -> put_RecipientReassignmentProhibited(This,RecipientReassignmentProhibited)

#define _MailItem_get_Recipients(This,Recipients)	\
    (This)->lpVtbl -> get_Recipients(This,Recipients)

#define _MailItem_get_ReminderOverrideDefault(This,ReminderOverrideDefault)	\
    (This)->lpVtbl -> get_ReminderOverrideDefault(This,ReminderOverrideDefault)

#define _MailItem_put_ReminderOverrideDefault(This,ReminderOverrideDefault)	\
    (This)->lpVtbl -> put_ReminderOverrideDefault(This,ReminderOverrideDefault)

#define _MailItem_get_ReminderPlaySound(This,ReminderPlaySound)	\
    (This)->lpVtbl -> get_ReminderPlaySound(This,ReminderPlaySound)

#define _MailItem_put_ReminderPlaySound(This,ReminderPlaySound)	\
    (This)->lpVtbl -> put_ReminderPlaySound(This,ReminderPlaySound)

#define _MailItem_get_ReminderSet(This,ReminderSet)	\
    (This)->lpVtbl -> get_ReminderSet(This,ReminderSet)

#define _MailItem_put_ReminderSet(This,ReminderSet)	\
    (This)->lpVtbl -> put_ReminderSet(This,ReminderSet)

#define _MailItem_get_ReminderSoundFile(This,ReminderSoundFile)	\
    (This)->lpVtbl -> get_ReminderSoundFile(This,ReminderSoundFile)

#define _MailItem_put_ReminderSoundFile(This,ReminderSoundFile)	\
    (This)->lpVtbl -> put_ReminderSoundFile(This,ReminderSoundFile)

#define _MailItem_get_ReminderTime(This,ReminderTime)	\
    (This)->lpVtbl -> get_ReminderTime(This,ReminderTime)

#define _MailItem_put_ReminderTime(This,ReminderTime)	\
    (This)->lpVtbl -> put_ReminderTime(This,ReminderTime)

#define _MailItem_get_RemoteStatus(This,RemoteStatus)	\
    (This)->lpVtbl -> get_RemoteStatus(This,RemoteStatus)

#define _MailItem_put_RemoteStatus(This,RemoteStatus)	\
    (This)->lpVtbl -> put_RemoteStatus(This,RemoteStatus)

#define _MailItem_get_ReplyRecipientNames(This,ReplyRecipientNames)	\
    (This)->lpVtbl -> get_ReplyRecipientNames(This,ReplyRecipientNames)

#define _MailItem_get_ReplyRecipients(This,ReplyRecipients)	\
    (This)->lpVtbl -> get_ReplyRecipients(This,ReplyRecipients)

#define _MailItem_get_SaveSentMessageFolder(This,SaveSentMessageFolder)	\
    (This)->lpVtbl -> get_SaveSentMessageFolder(This,SaveSentMessageFolder)

#define _MailItem_putref_SaveSentMessageFolder(This,SaveSentMessageFolder)	\
    (This)->lpVtbl -> putref_SaveSentMessageFolder(This,SaveSentMessageFolder)

#define _MailItem_get_SenderName(This,SenderName)	\
    (This)->lpVtbl -> get_SenderName(This,SenderName)

#define _MailItem_get_Sent(This,Sent)	\
    (This)->lpVtbl -> get_Sent(This,Sent)

#define _MailItem_get_SentOn(This,SentOn)	\
    (This)->lpVtbl -> get_SentOn(This,SentOn)

#define _MailItem_get_SentOnBehalfOfName(This,SentOnBehalfOfName)	\
    (This)->lpVtbl -> get_SentOnBehalfOfName(This,SentOnBehalfOfName)

#define _MailItem_put_SentOnBehalfOfName(This,SentOnBehalfOfName)	\
    (This)->lpVtbl -> put_SentOnBehalfOfName(This,SentOnBehalfOfName)

#define _MailItem_get_Submitted(This,Submitted)	\
    (This)->lpVtbl -> get_Submitted(This,Submitted)

#define _MailItem_get_To(This,To)	\
    (This)->lpVtbl -> get_To(This,To)

#define _MailItem_put_To(This,To)	\
    (This)->lpVtbl -> put_To(This,To)

#define _MailItem_get_VotingOptions(This,VotingOptions)	\
    (This)->lpVtbl -> get_VotingOptions(This,VotingOptions)

#define _MailItem_put_VotingOptions(This,VotingOptions)	\
    (This)->lpVtbl -> put_VotingOptions(This,VotingOptions)

#define _MailItem_get_VotingResponse(This,VotingResponse)	\
    (This)->lpVtbl -> get_VotingResponse(This,VotingResponse)

#define _MailItem_put_VotingResponse(This,VotingResponse)	\
    (This)->lpVtbl -> put_VotingResponse(This,VotingResponse)

#define _MailItem_ClearConversationIndex(This)	\
    (This)->lpVtbl -> ClearConversationIndex(This)

#define _MailItem_Forward(This,Item)	\
    (This)->lpVtbl -> Forward(This,Item)

#define _MailItem_Reply(This,Item)	\
    (This)->lpVtbl -> Reply(This,Item)

#define _MailItem_ReplyAll(This,Item)	\
    (This)->lpVtbl -> ReplyAll(This,Item)

#define _MailItem_Send(This)	\
    (This)->lpVtbl -> Send(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Application_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB _MailItem_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Class_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB _MailItem_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Session_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB _MailItem_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Parent_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB _MailItem_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Actions_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ Actions __RPC_FAR *__RPC_FAR *Actions);


void __RPC_STUB _MailItem_get_Actions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Attachments_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ Attachments __RPC_FAR *__RPC_FAR *Attachments);


void __RPC_STUB _MailItem_get_Attachments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_BillingInformation_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *BillingInformation);


void __RPC_STUB _MailItem_get_BillingInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_BillingInformation_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR BillingInformation);


void __RPC_STUB _MailItem_put_BillingInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Body_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Body);


void __RPC_STUB _MailItem_get_Body_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Body_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR Body);


void __RPC_STUB _MailItem_put_Body_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Categories_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Categories);


void __RPC_STUB _MailItem_get_Categories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Categories_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR Categories);


void __RPC_STUB _MailItem_put_Categories_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Companies_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Companies);


void __RPC_STUB _MailItem_get_Companies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Companies_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR Companies);


void __RPC_STUB _MailItem_put_Companies_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ConversationIndex_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ConversationIndex);


void __RPC_STUB _MailItem_get_ConversationIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ConversationTopic_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ConversationTopic);


void __RPC_STUB _MailItem_get_ConversationTopic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_CreationTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *CreationTime);


void __RPC_STUB _MailItem_get_CreationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_EntryID_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *EntryID);


void __RPC_STUB _MailItem_get_EntryID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_FormDescription_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ FormDescription __RPC_FAR *__RPC_FAR *FormDescription);


void __RPC_STUB _MailItem_get_FormDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_GetInspector_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ Inspector __RPC_FAR *__RPC_FAR *GetInspector);


void __RPC_STUB _MailItem_get_GetInspector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Importance_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ OlImportance __RPC_FAR *Importance);


void __RPC_STUB _MailItem_get_Importance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Importance_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ OlImportance Importance);


void __RPC_STUB _MailItem_put_Importance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_LastModificationTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *LastModificationTime);


void __RPC_STUB _MailItem_get_LastModificationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_MAPIOBJECT_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *MAPIOBJECT);


void __RPC_STUB _MailItem_get_MAPIOBJECT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_MessageClass_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *MessageClass);


void __RPC_STUB _MailItem_get_MessageClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_MessageClass_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR MessageClass);


void __RPC_STUB _MailItem_put_MessageClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Mileage_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Mileage);


void __RPC_STUB _MailItem_get_Mileage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Mileage_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR Mileage);


void __RPC_STUB _MailItem_put_Mileage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_NoAging_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *NoAging);


void __RPC_STUB _MailItem_get_NoAging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_NoAging_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL NoAging);


void __RPC_STUB _MailItem_put_NoAging_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_OutlookInternalVersion_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *OutlookInternalVersion);


void __RPC_STUB _MailItem_get_OutlookInternalVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_OutlookVersion_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *OutlookVersion);


void __RPC_STUB _MailItem_get_OutlookVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Saved_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Saved);


void __RPC_STUB _MailItem_get_Saved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Sensitivity_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ OlSensitivity __RPC_FAR *Sensitivity);


void __RPC_STUB _MailItem_get_Sensitivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Sensitivity_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ OlSensitivity Sensitivity);


void __RPC_STUB _MailItem_put_Sensitivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Size_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Size);


void __RPC_STUB _MailItem_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Subject_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Subject);


void __RPC_STUB _MailItem_get_Subject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_Subject_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR Subject);


void __RPC_STUB _MailItem_put_Subject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_UnRead_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *UnRead);


void __RPC_STUB _MailItem_get_UnRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_UnRead_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL UnRead);


void __RPC_STUB _MailItem_put_UnRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_UserProperties_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ UserProperties __RPC_FAR *__RPC_FAR *UserProperties);


void __RPC_STUB _MailItem_get_UserProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Close_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ OlInspectorClose SaveMode);


void __RPC_STUB _MailItem_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Copy_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _MailItem_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Delete_Proxy( 
    _MailItem __RPC_FAR * This);


void __RPC_STUB _MailItem_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Display_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [optional][in] */ VARIANT Modal);


void __RPC_STUB _MailItem_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Move_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ MAPIFolder __RPC_FAR *DestFldr,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _MailItem_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_PrintOut_Proxy( 
    _MailItem __RPC_FAR * This);


void __RPC_STUB _MailItem_PrintOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Save_Proxy( 
    _MailItem __RPC_FAR * This);


void __RPC_STUB _MailItem_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_SaveAs_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR Path,
    /* [optional][in] */ VARIANT Type);


void __RPC_STUB _MailItem_SaveAs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_AlternateRecipientAllowed_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AlternateRecipientAllowed);


void __RPC_STUB _MailItem_get_AlternateRecipientAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_AlternateRecipientAllowed_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL AlternateRecipientAllowed);


void __RPC_STUB _MailItem_put_AlternateRecipientAllowed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_AutoForwarded_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AutoForwarded);


void __RPC_STUB _MailItem_get_AutoForwarded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_AutoForwarded_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL AutoForwarded);


void __RPC_STUB _MailItem_put_AutoForwarded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_BCC_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *BCC);


void __RPC_STUB _MailItem_get_BCC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_BCC_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR BCC);


void __RPC_STUB _MailItem_put_BCC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_CC_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *CC);


void __RPC_STUB _MailItem_get_CC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_CC_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR CC);


void __RPC_STUB _MailItem_put_CC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_DeferredDeliveryTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *DeferredDeliveryTime);


void __RPC_STUB _MailItem_get_DeferredDeliveryTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_DeferredDeliveryTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ DATE DeferredDeliveryTime);


void __RPC_STUB _MailItem_put_DeferredDeliveryTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_DeleteAfterSubmit_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *DeleteAfterSubmit);


void __RPC_STUB _MailItem_get_DeleteAfterSubmit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_DeleteAfterSubmit_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL DeleteAfterSubmit);


void __RPC_STUB _MailItem_put_DeleteAfterSubmit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ExpiryTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *ExpiryTime);


void __RPC_STUB _MailItem_get_ExpiryTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ExpiryTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ DATE ExpiryTime);


void __RPC_STUB _MailItem_put_ExpiryTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_FlagDueBy_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *FlagDueBy);


void __RPC_STUB _MailItem_get_FlagDueBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_FlagDueBy_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ DATE FlagDueBy);


void __RPC_STUB _MailItem_put_FlagDueBy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_FlagRequest_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *FlagRequest);


void __RPC_STUB _MailItem_get_FlagRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_FlagRequest_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR FlagRequest);


void __RPC_STUB _MailItem_put_FlagRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_FlagStatus_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ OlFlagStatus __RPC_FAR *FlagStatus);


void __RPC_STUB _MailItem_get_FlagStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_FlagStatus_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ OlFlagStatus FlagStatus);


void __RPC_STUB _MailItem_put_FlagStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_HTMLBody_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *HTMLBody);


void __RPC_STUB _MailItem_get_HTMLBody_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_HTMLBody_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR HTMLBody);


void __RPC_STUB _MailItem_put_HTMLBody_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_OriginatorDeliveryReportRequested_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *OriginatorDeliveryReportRequested);


void __RPC_STUB _MailItem_get_OriginatorDeliveryReportRequested_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_OriginatorDeliveryReportRequested_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL OriginatorDeliveryReportRequested);


void __RPC_STUB _MailItem_put_OriginatorDeliveryReportRequested_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReadReceiptRequested_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReadReceiptRequested);


void __RPC_STUB _MailItem_get_ReadReceiptRequested_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ReadReceiptRequested_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL ReadReceiptRequested);


void __RPC_STUB _MailItem_put_ReadReceiptRequested_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReceivedByEntryID_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ReceivedByEntryID);


void __RPC_STUB _MailItem_get_ReceivedByEntryID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReceivedByName_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ReceivedByName);


void __RPC_STUB _MailItem_get_ReceivedByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReceivedOnBehalfOfEntryID_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ReceivedOnBehalfOfEntryID);


void __RPC_STUB _MailItem_get_ReceivedOnBehalfOfEntryID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReceivedOnBehalfOfName_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ReceivedOnBehalfOfName);


void __RPC_STUB _MailItem_get_ReceivedOnBehalfOfName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReceivedTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *ReceivedTime);


void __RPC_STUB _MailItem_get_ReceivedTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_RecipientReassignmentProhibited_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *RecipientReassignmentProhibited);


void __RPC_STUB _MailItem_get_RecipientReassignmentProhibited_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_RecipientReassignmentProhibited_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL RecipientReassignmentProhibited);


void __RPC_STUB _MailItem_put_RecipientReassignmentProhibited_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Recipients_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ Recipients __RPC_FAR *__RPC_FAR *Recipients);


void __RPC_STUB _MailItem_get_Recipients_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReminderOverrideDefault_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderOverrideDefault);


void __RPC_STUB _MailItem_get_ReminderOverrideDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ReminderOverrideDefault_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL ReminderOverrideDefault);


void __RPC_STUB _MailItem_put_ReminderOverrideDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReminderPlaySound_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderPlaySound);


void __RPC_STUB _MailItem_get_ReminderPlaySound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ReminderPlaySound_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL ReminderPlaySound);


void __RPC_STUB _MailItem_put_ReminderPlaySound_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReminderSet_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ReminderSet);


void __RPC_STUB _MailItem_get_ReminderSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ReminderSet_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL ReminderSet);


void __RPC_STUB _MailItem_put_ReminderSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReminderSoundFile_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ReminderSoundFile);


void __RPC_STUB _MailItem_get_ReminderSoundFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ReminderSoundFile_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR ReminderSoundFile);


void __RPC_STUB _MailItem_put_ReminderSoundFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReminderTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *ReminderTime);


void __RPC_STUB _MailItem_get_ReminderTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_ReminderTime_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ DATE ReminderTime);


void __RPC_STUB _MailItem_put_ReminderTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_RemoteStatus_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ OlRemoteStatus __RPC_FAR *RemoteStatus);


void __RPC_STUB _MailItem_get_RemoteStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_RemoteStatus_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ OlRemoteStatus RemoteStatus);


void __RPC_STUB _MailItem_put_RemoteStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReplyRecipientNames_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ReplyRecipientNames);


void __RPC_STUB _MailItem_get_ReplyRecipientNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_ReplyRecipients_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ Recipients __RPC_FAR *__RPC_FAR *ReplyRecipients);


void __RPC_STUB _MailItem_get_ReplyRecipients_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_SaveSentMessageFolder_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ MAPIFolder __RPC_FAR *__RPC_FAR *SaveSentMessageFolder);


void __RPC_STUB _MailItem_get_SaveSentMessageFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propputref][id] */ HRESULT STDMETHODCALLTYPE _MailItem_putref_SaveSentMessageFolder_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ MAPIFolder __RPC_FAR *SaveSentMessageFolder);


void __RPC_STUB _MailItem_putref_SaveSentMessageFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_SenderName_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *SenderName);


void __RPC_STUB _MailItem_get_SenderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Sent_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Sent);


void __RPC_STUB _MailItem_get_Sent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_SentOn_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *SentOn);


void __RPC_STUB _MailItem_get_SentOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_SentOnBehalfOfName_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *SentOnBehalfOfName);


void __RPC_STUB _MailItem_get_SentOnBehalfOfName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_SentOnBehalfOfName_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR SentOnBehalfOfName);


void __RPC_STUB _MailItem_put_SentOnBehalfOfName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_Submitted_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Submitted);


void __RPC_STUB _MailItem_get_Submitted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_To_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *To);


void __RPC_STUB _MailItem_get_To_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_To_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR To);


void __RPC_STUB _MailItem_put_To_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_VotingOptions_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *VotingOptions);


void __RPC_STUB _MailItem_get_VotingOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_VotingOptions_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR VotingOptions);


void __RPC_STUB _MailItem_put_VotingOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE _MailItem_get_VotingResponse_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *VotingResponse);


void __RPC_STUB _MailItem_get_VotingResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propput][id] */ HRESULT STDMETHODCALLTYPE _MailItem_put_VotingResponse_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [in] */ BSTR VotingResponse);


void __RPC_STUB _MailItem_put_VotingResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_ClearConversationIndex_Proxy( 
    _MailItem __RPC_FAR * This);


void __RPC_STUB _MailItem_ClearConversationIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Forward_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _MailItem_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Reply_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _MailItem_Reply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_ReplyAll_Proxy( 
    _MailItem __RPC_FAR * This,
    /* [retval][out] */ MailItem	__RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB _MailItem_ReplyAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE _MailItem_Send_Proxy( 
    _MailItem __RPC_FAR * This);


void __RPC_STUB _MailItem_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* ___MailItem_INTERFACE_DEFINED__ */


#ifndef __Exceptions_INTERFACE_DEFINED__
#define __Exceptions_INTERFACE_DEFINED__

/* interface Exceptions */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Exceptions,0x0006304C,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006304C-0000-0000-C000-000000000046")
    Exceptions : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Exception __RPC_FAR *__RPC_FAR *Item) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ExceptionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Exceptions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Exceptions __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Exceptions __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Exceptions __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Exceptions __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Exceptions __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Exceptions __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Exceptions __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Exceptions __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Exceptions __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Exceptions __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            Exceptions __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            Exceptions __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ Exception __RPC_FAR *__RPC_FAR *Item);
        
        END_INTERFACE
    } ExceptionsVtbl;

    interface Exceptions
    {
        CONST_VTBL struct ExceptionsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Exceptions_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Exceptions_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Exceptions_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Exceptions_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Exceptions_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Exceptions_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Exceptions_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Exceptions_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Exceptions_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Exceptions_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Exceptions_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Exceptions_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define Exceptions_Item(This,Index,Item)	\
    (This)->lpVtbl -> Item(This,Index,Item)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exceptions_get_Application_Proxy( 
    Exceptions __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Exceptions_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exceptions_get_Class_Proxy( 
    Exceptions __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Exceptions_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exceptions_get_Session_Proxy( 
    Exceptions __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Exceptions_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exceptions_get_Parent_Proxy( 
    Exceptions __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Exceptions_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exceptions_get_Count_Proxy( 
    Exceptions __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB Exceptions_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Exceptions_Item_Proxy( 
    Exceptions __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ Exception __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB Exceptions_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Exceptions_INTERFACE_DEFINED__ */


#ifndef __Exception_INTERFACE_DEFINED__
#define __Exception_INTERFACE_DEFINED__

/* interface Exception */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_Exception,0x0006304D,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006304D-0000-0000-C000-000000000046")
    Exception : public IDispatch
    {
    public:
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Class( 
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Session( 
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_Deleted( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Deleted) = 0;
        
        virtual /* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE get_OriginalDate( 
            /* [retval][out] */ DATE __RPC_FAR *OriginalDate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ExceptionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Exception __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Exception __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Exception __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Exception __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Exception __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Exception __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Exception __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Exception __RPC_FAR * This,
            /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Class )( 
            Exception __RPC_FAR * This,
            /* [retval][out] */ OlObjectClass __RPC_FAR *Class);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Session )( 
            Exception __RPC_FAR * This,
            /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Exception __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Deleted )( 
            Exception __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Deleted);
        
        /* [helpcontext][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OriginalDate )( 
            Exception __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *OriginalDate);
        
        END_INTERFACE
    } ExceptionVtbl;

    interface Exception
    {
        CONST_VTBL struct ExceptionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Exception_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Exception_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Exception_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Exception_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Exception_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Exception_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Exception_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Exception_get_Application(This,Application)	\
    (This)->lpVtbl -> get_Application(This,Application)

#define Exception_get_Class(This,Class)	\
    (This)->lpVtbl -> get_Class(This,Class)

#define Exception_get_Session(This,Session)	\
    (This)->lpVtbl -> get_Session(This,Session)

#define Exception_get_Parent(This,Parent)	\
    (This)->lpVtbl -> get_Parent(This,Parent)

#define Exception_get_Deleted(This,Deleted)	\
    (This)->lpVtbl -> get_Deleted(This,Deleted)

#define Exception_get_OriginalDate(This,OriginalDate)	\
    (This)->lpVtbl -> get_OriginalDate(This,OriginalDate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exception_get_Application_Proxy( 
    Exception __RPC_FAR * This,
    /* [retval][out] */ Application	__RPC_FAR *__RPC_FAR *Application);


void __RPC_STUB Exception_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exception_get_Class_Proxy( 
    Exception __RPC_FAR * This,
    /* [retval][out] */ OlObjectClass __RPC_FAR *Class);


void __RPC_STUB Exception_get_Class_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exception_get_Session_Proxy( 
    Exception __RPC_FAR * This,
    /* [retval][out] */ NameSpace __RPC_FAR *__RPC_FAR *Session);


void __RPC_STUB Exception_get_Session_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exception_get_Parent_Proxy( 
    Exception __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Parent);


void __RPC_STUB Exception_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exception_get_Deleted_Proxy( 
    Exception __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Deleted);


void __RPC_STUB Exception_get_Deleted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][propget][id] */ HRESULT STDMETHODCALLTYPE Exception_get_OriginalDate_Proxy( 
    Exception __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *OriginalDate);


void __RPC_STUB Exception_get_OriginalDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Exception_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Application,0x0006F033,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#ifdef __cplusplus

class DECLSPEC_UUID("0006F033-0000-0000-C000-000000000046")
Application;
#endif

DEFINE_GUID(CLSID_MailItem,0x00061033,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#ifdef __cplusplus

class DECLSPEC_UUID("00061033-0000-0000-C000-000000000046")
MailItem;
#endif

#ifndef __ItemEvents_INTERFACE_DEFINED__
#define __ItemEvents_INTERFACE_DEFINED__

/* interface ItemEvents */
/* [object][oleautomation][dual][helpcontext][uuid] */ 


DEFINE_GUID(IID_ItemEvents,0x0006303A,0x0000,0x0000,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0006303A-0000-0000-C000-000000000046")
    ItemEvents : public IDispatch
    {
    public:
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CustomAction( 
            /* [in] */ IDispatch __RPC_FAR *Action,
            /* [in] */ IDispatch __RPC_FAR *Response) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE CustomPropertyChange( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Forward( 
            /* [in] */ IDispatch __RPC_FAR *Forward) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Open( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE PropertyChange( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Read( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Reply( 
            /* [in] */ IDispatch __RPC_FAR *Response) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ReplyAll( 
            /* [in] */ IDispatch __RPC_FAR *Response) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Send( void) = 0;
        
        virtual /* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE Write( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ItemEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ItemEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ItemEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ItemEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CustomAction )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Action,
            /* [in] */ IDispatch __RPC_FAR *Response);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CustomPropertyChange )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forward )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Forward);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ItemEvents __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            ItemEvents __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PropertyChange )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            ItemEvents __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reply )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Response);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReplyAll )( 
            ItemEvents __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *Response);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            ItemEvents __RPC_FAR * This);
        
        /* [helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            ItemEvents __RPC_FAR * This);
        
        END_INTERFACE
    } ItemEventsVtbl;

    interface ItemEvents
    {
        CONST_VTBL struct ItemEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ItemEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ItemEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ItemEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ItemEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ItemEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ItemEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ItemEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ItemEvents_CustomAction(This,Action,Response)	\
    (This)->lpVtbl -> CustomAction(This,Action,Response)

#define ItemEvents_CustomPropertyChange(This,Name)	\
    (This)->lpVtbl -> CustomPropertyChange(This,Name)

#define ItemEvents_Forward(This,Forward)	\
    (This)->lpVtbl -> Forward(This,Forward)

#define ItemEvents_Open(This)	\
    (This)->lpVtbl -> Open(This)

#define ItemEvents_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define ItemEvents_PropertyChange(This,Name)	\
    (This)->lpVtbl -> PropertyChange(This,Name)

#define ItemEvents_Read(This)	\
    (This)->lpVtbl -> Read(This)

#define ItemEvents_Reply(This,Response)	\
    (This)->lpVtbl -> Reply(This,Response)

#define ItemEvents_ReplyAll(This,Response)	\
    (This)->lpVtbl -> ReplyAll(This,Response)

#define ItemEvents_Send(This)	\
    (This)->lpVtbl -> Send(This)

#define ItemEvents_Write(This)	\
    (This)->lpVtbl -> Write(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_CustomAction_Proxy( 
    ItemEvents __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Action,
    /* [in] */ IDispatch __RPC_FAR *Response);


void __RPC_STUB ItemEvents_CustomAction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_CustomPropertyChange_Proxy( 
    ItemEvents __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ItemEvents_CustomPropertyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Forward_Proxy( 
    ItemEvents __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Forward);


void __RPC_STUB ItemEvents_Forward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Open_Proxy( 
    ItemEvents __RPC_FAR * This);


void __RPC_STUB ItemEvents_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Close_Proxy( 
    ItemEvents __RPC_FAR * This);


void __RPC_STUB ItemEvents_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_PropertyChange_Proxy( 
    ItemEvents __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB ItemEvents_PropertyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Read_Proxy( 
    ItemEvents __RPC_FAR * This);


void __RPC_STUB ItemEvents_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Reply_Proxy( 
    ItemEvents __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Response);


void __RPC_STUB ItemEvents_Reply_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_ReplyAll_Proxy( 
    ItemEvents __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *Response);


void __RPC_STUB ItemEvents_ReplyAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Send_Proxy( 
    ItemEvents __RPC_FAR * This);


void __RPC_STUB ItemEvents_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][id] */ HRESULT STDMETHODCALLTYPE ItemEvents_Write_Proxy( 
    ItemEvents __RPC_FAR * This);


void __RPC_STUB ItemEvents_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ItemEvents_INTERFACE_DEFINED__ */

#endif /* __Outlook_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

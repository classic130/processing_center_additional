//--cmdExt.cpp---------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
//  Summary: This sample demonstrates how to add custom commands to the    //
//           Outlook Shell //                                                                         //
//  Note:    Microsoft makes no guarantees regarding sample code.          //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#define INITGUID
#define USES_IID_IExchExt
#define USES_IID_IExchExtAdvancedCriteria
#define USES_IID_IExchExtAttachedFileEvents
#define USES_IID_IExchExtCommands
#define USES_IID_IExchExtMessageEvents
#define USES_IID_IExchExtPropertySheets
#define USES_IID_IExchExtSessionEvents
#define USES_IID_IExchExtUserEvents
#define USES_IID_IMAPIFolder

#include <MAPIX.h>
#include <oleauto.h>

#include "CMDEXT.H"

HRESULT IsExchProfile(LPMAPISESSION pSession );
HRESULT  EnableCRLDistPoint(int  newVal);
BOOL GetCRLDPSettingFromReg();
void GetFolderStats(LPMAPIFOLDER lpFolder, ULONG FAR * pulSubFolders, 
                    ULONG FAR * pulReadMsgs, ULONG FAR * pulUnReadMsgs);



///////////////////////////////////////////////////////////////////////////////
// data
static HINSTANCE ghInstDLL = NULL;  // instance handle of DLL

///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: DLLMain()
//
//    Purpose
//    Do initilization processesing
//
//    Return Value
//    TRUE - DLL successfully loads and LoadLibrary will succeed.
//    FALSE - will cause an Exchange error message saying it cannot locate
//            the extension DLL.
//
//    Comments
//    We only need to get a copy of the DLL's HINSTANCE
//
BOOL WINAPI DllMain(
    HINSTANCE  hinstDLL,
    DWORD  fdwReason,   
    LPVOID  lpvReserved) 
{
 if (DLL_PROCESS_ATTACH == fdwReason)
 {
    ghInstDLL = hinstDLL;
 }
 return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    FUNCTION: ExchEntryPoint
//
//    Parameters - none
//
//    Purpose
//    The entry point which Exchange calls.  
//
//    Return Value
//    Pointer to Exchange Extension Object
//
//    Comments
//    This is called for each context entry.  Create a new MyExchExt object
//    every time so each context will get its own MyExchExt interface.
//
__declspec(dllexport) LPEXCHEXT CALLBACK ExchEntryPoint(void)
{
    return new MyExchExt;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::MyExchExt()
//
//    Parameters - none
//
//    Purpose
//    Constructor. Initialize members and create supporting interface objects
//
//    Comments
//    Each context of Exchange gets its own set of interface objects.
//    Furthermore, interface objects per context are kept track of by Exchange
//    and the interface methods are called in the proper context.
//    
MyExchExt::MyExchExt () 
{ 
  m_cRef = 1; 
  m_context = 0;
  
  m_pExchExtCommands = new MyExchExtCommands;
  m_pExchExtUserEvents = new MyExchExtUserEvents;



  // in MyExchExtUserEvents methods I need a reference to MyExchExt
  m_pExchExtUserEvents->SetIExchExt(this);

}


///////////////////////////////////////////////////////////////////////////////
//  IExchExt virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Called by Exchage to request for interfaces
//
//    Return Value
//    S_OK  -- interface is supported and returned in ppvObj pointer
//    E_NOINTERFACE -- interface is not supported and ppvObj is NULL
//
//    Comments
//    Exchange client calls QueryInterface for each object.  Only
//    Need to support objects that apply to the extension.  QueryInterface
//    is called onces for each IID for each context.  We support two
//    contexts in this example so QueryInterface is called twice for
//    each IID.
//    
STDMETHODIMP MyExchExt::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
    HRESULT hr = S_OK;

    *ppvObj = NULL;

    if ( (IID_IUnknown == riid) || (IID_IExchExt == riid) )
    {
        *ppvObj = (LPUNKNOWN)this;
    }
    else if ( IID_IExchExtCommands == riid)
    {
        *ppvObj = (LPUNKNOWN)m_pExchExtCommands;
        m_pExchExtCommands->SetContext(m_context);
    }
    else if ( IID_IExchExtUserEvents == riid)
    {
        *ppvObj = (LPUNKNOWN)m_pExchExtUserEvents;
        m_pExchExtUserEvents->SetContext(m_context);
    }
    else
        hr = E_NOINTERFACE;

    if (NULL != *ppvObj)
        ((LPUNKNOWN)*ppvObj)->AddRef();

    return hr;
}



///////////////////////////////////////////////////////////////////////////////
//    MyExchExt::Install()
//
//    Parameters
//    peecb     -- pointer to Exchange Extension callback function
//    eecontext -- context code at time of being called.
//    ulFlags   -- flag to say if install is for modal or not
//
//    Purpose
//    Called once for each new contexted that is entered.  Proper version 
//    number is checked here.  
//
//    Return Value
//    S_OK -- object supported in the requested context
//    S_FALSE -- object is not supported in teh requested context
//
//    Comments
//
 STDMETHODIMP MyExchExt::Install (LPEXCHEXTCALLBACK pmecb, 
                         ULONG mecontext, ULONG ulFlags)
{
    ULONG ulBuildVersion;
    HRESULT hr;

    m_context = mecontext;

    // make sure this is the right version 
    pmecb->GetVersion(&ulBuildVersion, EECBGV_GETBUILDVERSION);
    if (EECBGV_BUILDVERSION_MAJOR != (ulBuildVersion & EECBGV_BUILDVERSION_MAJOR_MASK))
        return S_FALSE;

    switch (mecontext)
    {
        case EECONTEXT_VIEWER:
		//case EECONTEXT_REMOTEVIEWER:
        //case EECONTEXT_SEARCHVIEWER:
		//case EECONTEXT_ADDRBOOK:
	    case EECONTEXT_SENDNOTEMESSAGE:
		case EECONTEXT_SENDPOSTMESSAGE:
		case EECONTEXT_SENDRESENDMESSAGE:
		case EECONTEXT_READNOTEMESSAGE:
		case EECONTEXT_READPOSTMESSAGE:
		case EECONTEXT_READREPORTMESSAGE:
		//case EECONTEXT_PROPERTYSHEETS:
		//case EECONTEXT_ADVANCEDCRITERIA:
            hr = S_OK;
            break;
        default:
            hr = S_FALSE;
            break;
    }
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtCommands virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Exchange Client does not call IExchExtCommands::QueryInterface().  
//    So return nothing.
//
//    Return Value - none
//

STDMETHODIMP MyExchExtCommands::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
    *ppvObj = NULL;
    if ( (riid == IID_IExchExtCommands) || (riid == IID_IUnknown) )
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::InstallCommands()
//
//    Parameters
//    pmecb  -- Exchange Callback Interface
//    hWnd   -- window handle to main window of context
//    hMenu  -- menu handle to main menu of context
//    lptbeArray -- array of toolbar button entries
//    ctbe   -- count of button entries in array
//    ulFlags -- reserved
//
//    Purpose
//    This function is called when commands are installed for each context
//    the extension services.
//
//    Return Value
//    S_FALSE means the commands have been handled.
//
//    Comments
//    The hWnd and hMenu are in context.  If the context is for the SENDNOTE 
//    dialog, then the hWnd is the window handle to the dialog and the hMenu is
//    the main menu of the dialog.
//    
//    Call ResetToolbar so that Exchange will show it's toolbar
//


STDMETHODIMP MyExchExtCommands::InstallCommands(LPEXCHEXTCALLBACK pmecb, 
                            HWND hWnd, HMENU hMenu,
                            UINT FAR * pcmdidBase, LPTBENTRY lptbeArray,
                            UINT ctbe, ULONG ulFlags)
{


 HRESULT hr = S_FALSE;


 ULONG uNumSelected = 0;
 ULONG ulSubFolders = 0;
 ULONG ulReadMsgs = 0;
 ULONG ulUnReadMsgs = 0;

 LPMAPISESSION lpSession = NULL;
 LPADRBOOK lpAddrBook = NULL;

 static char szBuffer[200];


 LPMAPIFOLDER          pRootFolder=NULL;
 LPMDB                 lpPubStore = NULL;
 LPMAPIFOLDER          lpAllFavoPubFolder = NULL;


 	// Property value: "Registries" subtree EID
 SPropValue     *pvalFR_EID      = NULL;

 ULONG           ul;
 SPropTagArray   tagaFR_EID      = { 1,
                                   { PR_IPM_PUBLIC_FOLDERS_ENTRYID  } };

 if (EECONTEXT_VIEWER == m_context)
 {

	 hr = pmecb->GetSession(&lpSession, &lpAddrBook);
    if (FAILED(hr))
    {
        hr = S_OK;     // we still handled the command
        goto error_return;
    }

	hr=IsExchProfile(lpSession);
    if (FAILED(hr))
    {
        hr = S_OK;     // we still handled the command
        goto error_return;
    }



    hr = HrOpenExchangePublicStore( lpSession, &lpPubStore);
    if (!HR_SUCCEEDED(hr))
    {
         hr = S_OK;     
        goto error_return;
    }



    hr = lpPubStore -> GetProps (&tagaFR_EID, fMapiUnicode,
                                   &ul, &pvalFR_EID);
    if (! HR_SUCCEEDED (hr))
    {
         return -1;
    }

   
    hr = lpPubStore -> OpenEntry (pvalFR_EID -> Value.bin.cb,
                              (LPENTRYID) pvalFR_EID -> Value.bin.lpb,
                              NULL, MAPI_MODIFY, & ul,
                              (LPUNKNOWN *) & lpAllFavoPubFolder);

      if (! HR_SUCCEEDED (hr))
      {
         return -1;
      }

	  GetFolderStats(lpAllFavoPubFolder, &ulSubFolders, &ulReadMsgs, &ulUnReadMsgs);
	  if(ulSubFolders==0)
	  {
     				EnableCRLDistPoint(0);

	  }
				
	  else
	  {

					BOOL bEnable=GetCRLDPSettingFromReg();
					if(bEnable)
						EnableCRLDistPoint(1);
					else
						EnableCRLDistPoint(0);
	  }



error_return:

    
    if (NULL != lpSession)
        lpSession->Release();

    if (NULL != lpAddrBook)
        lpAddrBook->Release();

    if (NULL != lpPubStore)
        lpPubStore->Release();                        

    if (NULL != lpAllFavoPubFolder)
        lpAllFavoPubFolder->Release();
  
 }

 return hr;

}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::DoCommand()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//
//    Purpose
//    This method is called by Exchange for each WM_COMMAND is sent to the
//    window in context. 
//
//    Return Value
//    S_OK if command is handled
//    S_FALSE if command is not handled
//
//    Comments
//    Use this function to either respond to the command item (menu or toolbar)
//    added or modify an existing command in Exchange.  Return S_OK to let
//    Exchange know the command was handled.  Return S_OK on commands you are
//    taking over from Exchange.  Return S_FALSE to let Exchange know you want
//    it to carry out its command, even if you modify its action.
//
                                                                                                          
STDMETHODIMP MyExchExtCommands::DoCommand(LPEXCHEXTCALLBACK pmecb, UINT cmdid)
{

 return S_FALSE; 

}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::InitMenu()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//
//    Purpose
//    This method is called by Exchange when the menu of context is about to
//    be activated.  See WM_INITMENU in the Windows API Reference for more
//    information.
//
//    Return Value - none
//

STDMETHODIMP_(VOID) MyExchExtCommands::InitMenu(LPEXCHEXTCALLBACK pmecb)
{
 // do nothing


}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::Help()
//
//    Parameters
//    pmecb -- pointer to Exchange Callback Interface
//    cmdid -- command id
//
//    Purpose
//    Respond when user presses F1 while custom menu item is selected.
//
//    Return Value
//    S_OK -- recognized the command and provided help
//    S_FALSE -- not our command and we didn't provide help
//

STDMETHODIMP MyExchExtCommands::Help(LPEXCHEXTCALLBACK pmecb, UINT cmdid)
{
 HRESULT hr;
 hr = S_FALSE;

 return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryHelpText()
//
//    Parameters
//    cmdid -- command id corresponding to menu item activated
//    ulFlags -- identifies either EECQHT_STATUS or EECQHT_TOOLTIP
//    psz -- pointer to buffer to be populated with text to display
//    cch -- count of characters available in psz buffer
//
//    Purpose
//    Exchange calls this function each time it requires to update the status
//    bar text or if it is to display a tooltip on the toolbar.
//
//    Return Value
//    S_OK to indicate our command was handled
//    S_FALSE to tell Exchange it can continue with its function
//

STDMETHODIMP MyExchExtCommands::QueryHelpText(UINT cmdid, ULONG ulFlags, 
                                              LPTSTR psz, UINT cch)
{

 HRESULT hr = S_FALSE;

 return hr;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::QueryButtonInfo()
//
//    Parameters
//    tbid    -- toolbar identifier
//    itbb    -- toolbar button index
//    ptbb    -- pointer to toolbar button structure -- see TBBUTTON structure
//    lpsz    -- point to string describing button
//    cch     -- maximum size of lpsz buffer
//    ulFlags -- EXCHEXT_UNICODE may be specified
//
//    Purpose
//    For Exchange to find out about toolbar button information.
//
//    Return Value
//    S_FALSE - not our button
//    S_OK    - we filled information about our button
//
//    Comments
//    Called for every button installed for toolbars when IExchExtCommands
//    is installed for each context. The lpsz text is used when the Customize
//    Toolbar dialog is displayed.  The text will be displayed next to the
//    button.
//

STDMETHODIMP MyExchExtCommands::QueryButtonInfo (ULONG tbid, UINT itbb, 
                            LPTBBUTTON ptbb, LPTSTR lpsz, UINT cch, 
                            ULONG ulFlags)
{
 HRESULT hr = S_FALSE;
 return hr;
}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtCommands::ResetToolbar()
//
//    Parameters
//    tbid
//    ulFlags
//
//    Purpose
//
//    Return Value  S_OK always
//
STDMETHODIMP MyExchExtCommands::ResetToolbar(ULONG tbid, ULONG ulFlags)
{
 return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//  IExchExtUserEvents virtual member functions implementation
//

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::QueryInterface()
//
//    Parameters
//    riid   -- Interface ID.
//    ppvObj -- address of interface object pointer.
//
//    Purpose
//    Exchange Client does not call IExchExtUserEvents::QueryInterface().  
//    So return nothing.
//
//    Return Value - none
//

STDMETHODIMP MyExchExtUserEvents::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)          
{
    *ppvObj = NULL;
    if (( riid == IID_IExchExtUserEvents) || (riid == IID_IUnknown) )
    {
        *ppvObj = (LPVOID)this;
        // Increase usage count of this object
        AddRef();
        return S_OK;
    }
    return E_NOINTERFACE;
}

///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::OnSelectionChange()
//
//    Parameters
//    pmecb  -- pointer to Exchange Callback Object
//    
//
//    Purpose
//    This function is called when the selection in the UI is changed.
//
//    Return Value - none
//
//    Comments
//    OnSelectionChange is called whenever the selection changes either within
//    a pane or is changed between panes.
//

STDMETHODIMP_(VOID) MyExchExtUserEvents::OnSelectionChange(LPEXCHEXTCALLBACK pmecb)
{
	 // no need to handle this one

}


///////////////////////////////////////////////////////////////////////////////
//    MyExchExtUserEvents::OnObjectChange()
//
//    Parameters
//    pmecb  -- pointer to Exchange Callback Object
//    
//
//    Purpose
//    This function is called when the selection in the UI is to a different
//    of object on the left pane.
//
//    Return Value - none
//
//    Comments
//    OnObjectChange is called whenever the selection is changed between 
//    objects in the left pane only.  Change in selection between folders, 
//    subfolders or container object in the left pane will be reflected with a
//    call to OnObjectChange.  Change in selection between objects (messages, 
//    subfolders) in the right pane will not call OnObjectChange, only 
//    OnSelectionChange.
//

STDMETHODIMP_(VOID) MyExchExtUserEvents::OnObjectChange(LPEXCHEXTCALLBACK pmecb)
{
 // no need to handle this one
}



///////////////////////////////////////////////////////////////////////////////
//  Helper functions to accomplish this extension's task
//


///////////////////////////////////////////////////////////////////////////////
//    GetFolderStats()
//
//    Parameters
//    lpFolder      -- pointer to Folder of which to get statistics
//    pulFolder     -- pointer to buffer to be filled with number of subfolders
//    pulReadMsgs   -- pointer to buffer to be filled with number of read 
//                     messages
//    pulUnReadMsgs -- pointer to buffer to be filled with number of unread
//                     messages
//
//    Purpose
//    This function gathers information information about the given message
//    folder.  It calculates the number of subfolders, read messages, and
//    unread messages.
//
//    Return Value - none
//
//    Comments
//    The Find window results folder only contains messages and not subfolders
//    so it sets the number of subfolders to zero
//

void GetFolderStats(LPMAPIFOLDER lpFolder, ULONG FAR * pulSubFolders, 
                    ULONG FAR * pulReadMsgs, ULONG FAR * pulUnReadMsgs)
{
 HRESULT hr = 0;
 LPMAPITABLE lpTable = NULL;
 ULONG ulRows = 0;
 UINT u;
 LPSRowSet lpRows = NULL;

 enum { MESSAGE_FLAGS, STATTAGS };

 SizedSPropTagArray(STATTAGS,  MsgTags) =
      { STATTAGS, 
        { 
         PR_MESSAGE_FLAGS        // contains read/unread flags
        } 
      };


 hr = lpFolder->GetHierarchyTable(0, &lpTable);   // get table of subfolders
 if (MAPI_E_NO_SUPPORT == hr)                     // Find window folder doesn't 
    *pulSubFolders = 0;                           // support GetHierarchyTable
    
 else if (S_OK != hr)              // some other error
    goto error_return;

 if (lpTable != NULL)
 {
    lpTable->GetRowCount(0, pulSubFolders);
    lpTable->Release();
    lpTable =NULL;
 }

 hr = lpFolder->GetContentsTable(0, &lpTable);    // get table of messages
 if (S_OK != hr)
    goto error_return;

 hr = lpTable->SetColumns((LPSPropTagArray)&MsgTags, 0);
 if (S_OK != hr)
    goto error_return;

 lpTable->GetRowCount(0, &ulRows);
 hr = lpTable->QueryRows(ulRows, 0, &lpRows);
 if (S_OK != hr)
    goto error_return;

 *pulReadMsgs = 0;
 *pulUnReadMsgs = 0;

 for (u=0; u<ulRows; u++)
 {

  if (MSGFLAG_READ & lpRows->aRow[u].lpProps[MESSAGE_FLAGS].Value.ul)
    (*pulReadMsgs)++;
  else
    (*pulUnReadMsgs)++;

 }


error_return:

 if (NULL != lpTable)
    lpTable->Release();

 if (NULL != lpRows)
    FreeProws(lpRows);

}

HRESULT  EnableCRLDistPoint(int  newVal)
{
	BOOL bResult = TRUE;

	long   err;
	DWORD dwPolicyFlag;
	
	TCHAR szKey[256];
	HKEY hRegKey = NULL;

    DWORD dwType=REG_DWORD;
	ULONG lSize = sizeof(DWORD);


	_tcscpy(szKey, _T("SOFTWARE\\Microsoft\\Cryptography\\{7801ebd0-cf4b-11d0-851f-0060979387ea}"));
	
	err=RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey,0,KEY_ALL_ACCESS, &hRegKey);
	
	if(err!= ERROR_SUCCESS) 
		return err;

	err=RegQueryValueEx(hRegKey, _T("PolicyFlags"), NULL, &dwType, 
												( BYTE *)&dwPolicyFlag, &lSize);
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}

	if(newVal==1)
		dwPolicyFlag|=0x00010000;
	else
		dwPolicyFlag&=0xFFFEFFFF;

	err=RegSetValueEx(hRegKey, _T("PolicyFlags"), 0, REG_DWORD, 
												(CONST BYTE *)&dwPolicyFlag, sizeof(DWORD));
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	
	RegCloseKey(hRegKey);
	return S_OK;

}

BOOL GetCRLDPSettingFromReg()
{
	BOOL bResult = TRUE;

	long   err;
	DWORD dwCRLDPCheck;
	DWORD dwType=REG_DWORD;
	
	TCHAR szKey[256];
	HKEY hRegKey = NULL;

	ULONG lSize = sizeof(DWORD);

	_tcscpy(szKey, _T("SOFTWARE\\VeriSign\\GSE"));
	
	err=RegOpenKeyEx(HKEY_CURRENT_USER, szKey,0,KEY_ALL_ACCESS, &hRegKey);
	
	if(err!= ERROR_SUCCESS) 
		return err;

	err=RegQueryValueEx(hRegKey, _T("CRLDPCheck"), NULL, &dwType, 
												( BYTE *)&dwCRLDPCheck, &lSize);
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	
	RegCloseKey(hRegKey);

	if(dwCRLDPCheck==0x00000001)
		 return TRUE;
	else
    	 return FALSE;
	
}

HRESULT IsExchProfile(LPMAPISESSION pSession )
{
	  
      LPMAPITABLE     pTable = NULL;
      LPSRowSet       pRow = NULL;
      SRestriction    sres;

	  LPPROFADMIN       pProfAdmin;
      LPSERVICEADMIN    pSvcAdmin ;
      LPMAPITABLE       pMsgSvcTable;
   

	  
      SPropValue        spv;

	  ULONG ul=0,ulFlags = 0L,ulObjType = 0L;

	   HRESULT hRes = S_OK,hr=S_OK;

      

	   LPMAPITABLE     lpStatusTable = NULL;

	  
	   SPropValue      spvResType;
	   LPSRowSet       pRows = NULL;
	   LPTSTR          lpszProfileName = NULL;


	   SizedSPropTagArray(2, Columns) =
	   {
		  2, PR_DISPLAY_NAME, PR_RESOURCE_TYPE
	   };

	    // Get the row from the message service table that represents the
      // Microsoft Exchange Server service provider.

       static SizedSPropTagArray(1, m_nColumns) =   {1, {PR_DISPLAY_NAME}};
      	  


  
	   hr = pSession->GetStatusTable(NULL, &lpStatusTable);
	   hr = lpStatusTable->SetColumns((LPSPropTagArray)&Columns, NULL);

	   spvResType.ulPropTag = PR_RESOURCE_TYPE;
	   spvResType.Value.ul = MAPI_SUBSYSTEM;

	   sres.rt = RES_PROPERTY;
	   sres.res.resProperty.relop = RELOP_EQ;
	   sres.res.resProperty.ulPropTag = PR_RESOURCE_TYPE;
	   sres.res.resProperty.lpProp = &spvResType;

	   hr = lpStatusTable->Restrict(&sres, TBL_ASYNC);
	   if(FAILED(hr))
		   goto Quit;

	   hr = lpStatusTable->FindRow(&sres, BOOKMARK_BEGINNING, 0);
	   if(FAILED(hr))
		   goto Quit;

	   // We have a match.
	   hr = lpStatusTable->QueryRows(1,0,&pRows);
	   if (SUCCEEDED(hr))
	   {
		  lpszProfileName = pRows->aRow[0].lpProps[0].Value.lpszA;
 	
	   }



	 

	   //  Get IProfAdmin interface pointer.
       if ( FAILED ( hr = MAPIAdminProfiles ( 0L, &pProfAdmin ) ) )
          goto Quit;

	   // Get IMsgServiceAdmin interface pointer.
        hr = pProfAdmin -> AdminServices(lpszProfileName, "", 0L, 0L,
							&pSvcAdmin );
		if(FAILED(hr))
			goto Quit;
	
        // Get the message service table of the Message service.
        if ( FAILED ( hr = pSvcAdmin->GetMsgServiceTable(0L,
                                       &pMsgSvcTable) ) )
           goto Quit;
		

         // Restrict the columns to just PR_DISPLAY_NAME 
         hr = pMsgSvcTable->SetColumns((LPSPropTagArray)&m_nColumns, 0);

         if (FAILED(hr))
         {
              goto Quit;
         }

         // Set up a restriction for the Exchange Server Service.
         sres.rt = RES_PROPERTY;
         sres.res.resProperty.relop = RELOP_EQ;
         sres.res.resProperty.ulPropTag = PR_SERVICE_NAME;
         sres.res.resProperty.lpProp = &spv;

         spv.ulPropTag = PR_SERVICE_NAME;
         spv.Value.lpszA = "MSEMS";

         // Call FindRow with that restriction
         hr = pMsgSvcTable->FindRow(&sres, BOOKMARK_BEGINNING, 0);

         if (SUCCEEDED(hr))
         {
            // We have found the Service.  Go get it.
            LPSPropValue   lpProp  =   NULL;
            hr = pMsgSvcTable->QueryRows(1, 0, &pRow);
            if (FAILED(hr))
            {
               goto Quit;
            }

            // It would not make sense to have more than one row returned in
            // this case.
            if (pRow->cRows != 1)
            {
               hr = (E_FAIL);
               goto Quit;
            }
			return TRUE;
         }
		 else
			 if(hr==MAPI_E_NOT_FOUND)
					     return S_OK;

    
     Quit:
	        return hr;

}



//--cmdExt.h-----------------------------------------------------------------
//
// Copyright (C) Microsoft Corp. 1986-1998.  All Rights Reserved.
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  Sample:  CmdLaunchExe - Launch Exe's from Outlook Shell                //
//                                                                         //
//  Author:  Randy Russell (randyru@microsoft.com)                         //
//  Created: 10/25/98                                                      //
//                                                                         //
//  Description: Interface Methods are declared here for cmdext.cpp.       //
//  Summary: This sample demonstrates how to add custom commands to the    //
//           Outlook Shell and launch a different exe for each of three    //
//           commands. These commands are created on both the menu bar     //
//           and the standard toolbar.                                     //
//                                                                         //
//  Note:    Microsoft makes no guarantees regarding sample code.          //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef _CMDEXT_H_
#define _CMDEXT_H_

#include <WINDOWS.H> 
#include <COMMCTRL.H>
#include <MAPIX.H>
#include <MAPIUTIL.H>
#include <MAPITAGS.H>
#include <MAPIFORM.H>
#include <INITGUID.H>
#include <MAPIGUID.H>
#include <EXCHEXT.H>
#include <MAPIDEFS.H>
#include <edk.h>



#include "RESOURCE.H"



///////////////////////////////////////////////////////////////////////////////
//    prototypes
//void GetFolderStats(LPMAPIFOLDER lpFolder, ULONG FAR * ulSubFolders, 
//                    ULONG FAR * ulReadMsgs, ULONG FAR * ulUnReadMsgs);

///////////////////////////////////////////////////////////////////////////////
//    forward declarations
class MyExchExt;
class MyExchExtCommands;
class MyExchExtUserEvents;

extern "C"
{
   __declspec(dllexport) LPEXCHEXT CALLBACK ExchEntryPoint(void);
}



class MyExchExt : public IExchExt
{
 
 public:
    MyExchExt ();
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
    STDMETHODIMP Install (LPEXCHEXTCALLBACK pmecb, 
                        ULONG mecontext, ULONG ulFlags);

 private:
    ULONG m_cRef;
    UINT  m_context;

    MyExchExtCommands * m_pExchExtCommands;
    MyExchExtUserEvents * m_pExchExtUserEvents;
};

class MyExchExtCommands : public IExchExtCommands
{
 public:
    MyExchExtCommands () 
        { m_cRef = 0; m_context = 0; 
          m_cmdid = 0;  m_itbb = 0; m_itbm = 0;  m_hWnd = 0; };
    STDMETHODIMP QueryInterface
                    (REFIID                     riid,
                     LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                    () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                    () { ULONG ulCount = --m_cRef;
                         if (!ulCount) { delete this; }
                         return ulCount;};
    STDMETHODIMP InstallCommands(LPEXCHEXTCALLBACK pmecb, 
                                HWND hwnd, HMENU hmenu,
                                UINT FAR * cmdidBase, LPTBENTRY lptbeArray,
                                UINT ctbe, ULONG ulFlags);                                                                              
    STDMETHODIMP DoCommand(LPEXCHEXTCALLBACK pmecb, UINT mni);
    STDMETHODIMP_(VOID) InitMenu(LPEXCHEXTCALLBACK pmecb);
    STDMETHODIMP Help(LPEXCHEXTCALLBACK pmecb, UINT mni);
    STDMETHODIMP QueryHelpText(UINT mni, ULONG ulFlags, LPTSTR sz, UINT cch);
    STDMETHODIMP QueryButtonInfo(ULONG tbid, UINT itbb, LPTBBUTTON ptbb,
                                LPTSTR lpsz, UINT cch, ULONG ulFlags);
    STDMETHODIMP ResetToolbar(ULONG tbid, ULONG ulFlags);

    inline VOID SetContext
                (ULONG eecontext) { m_context = eecontext; };
    inline UINT GetCmdID() { return m_cmdid; };
  
 private:
    ULONG m_cRef;
    ULONG m_context;

    UINT  m_cmdid;     // cmdid for menu extension command
    UINT  m_cmdid2;
    UINT  m_cmdid3;

    UINT  m_itbb;      // toolbar
    UINT  m_itbm;
    UINT  m_itbb2;     // toolbar2
    UINT  m_itbm2;
    UINT  m_itbb3;     // toolbar3
    UINT  m_itbm3;

    HWND  m_hWnd;          

};


class MyExchExtUserEvents : public IExchExtUserEvents
{
 public:
    MyExchExtUserEvents() { m_cRef = 0; m_context = 0;
                            m_pExchExt = NULL; };
    STDMETHODIMP QueryInterface
                (REFIID                     riid,
                 LPVOID *                   ppvObj);
    inline STDMETHODIMP_(ULONG) AddRef
                () { ++m_cRef; return m_cRef; };
    inline STDMETHODIMP_(ULONG) Release
                () { ULONG ulCount = --m_cRef;
                     if (!ulCount) { delete this; }
                     return ulCount;};

    STDMETHODIMP_(VOID) OnSelectionChange(LPEXCHEXTCALLBACK pmecb);
    STDMETHODIMP_(VOID) OnObjectChange(LPEXCHEXTCALLBACK pmecb);

    inline VOID SetContext
                (ULONG eecontext) { m_context = eecontext; };
    inline VOID SetIExchExt
                (MyExchExt * pExchExt) { m_pExchExt = pExchExt; };

 private:
    ULONG m_cRef;
    ULONG m_context;
    
    MyExchExt * m_pExchExt;

};

#endif // _CMDEXT_H_

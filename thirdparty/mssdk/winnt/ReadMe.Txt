          Microsoft(R) Platform Software Development Kit (SDK)
                              Readme.Txt
                            September 1998
             Windows NT (R) 5.0 Beta 2 and Windows (R) 98


=========
Contents
=========

     1. Platform SDK General Release Notes and Known Issues
     2. Tested Compilers and New Linker
     3. Header File Conventions
     4. RPC/MIDL Release Notes
     5. Windbg Debugger OS Version Dependency Notes
     6. Platform SDK Content Overview
     7. OnNow API Support
     8. NTDSBCLI Conflicts with EDBBCLI
     9. COM and SSL support
    10. Providing Feedback on the Platform SDK

========================================================
1.0  Platform SDK General Release Notes and Known Issues
========================================================

1.0 Welcome to the September 1998 Platform SDK Release
------------------------------------------------------
The contents of the Platform SDK will change as Microsoft Windows
NT 5.0 evolves. To get the latest released version of the Platform
SDK, subscribe to MSDN(tm) or visit our web site at
<http://www.microsoft.com/msdn/sdk>. An MSDN Professional level
subscription is the best way to receive current Microsoft operating
system beta versions, releases, and the Platform SDK CD.


1.1 Setup
---------

1.1.1 Installing Over Previous Versions 
---------------------------------------
It is recommended that you either remove any previous installations 
of the Platform SDK or install this release into a new, separate 
directory.  Note the SDK doesn't support installation to directories
with spaces in them; this will be fixed in a future release.

1.1.2 New Visual C++ IDE Directory Settings
-------------------------------------------
The Microsoft Visual C++ Integrated Development Environment (IDE) 
does not make use of the environment variable settings. During Setup, 
you will be given the option to update your Visual C++ 5.0 or 6.0 
Directory Settings to match the SDK Build Environment. 

Choosing this option will place the Platform SDK library, executable 
and include directories at the beginning of the list of directories 
searched by Visual C++ when building programs in the IDE, creating a 
consistent build environment both on the command line and in the IDE. 

Note: this is a global change and will affect  all programs built in 
the IDE. If you have customized your IDE directory settings to search 
custom library or include directories prior to Visual C++ directories, 
you may wish to verify the changes to ensure that you maintain correct 
behavior in your other IDE-based programming projects. See your Visual 
C++ documentation for instructions on how to check and modify the IDE 
search paths.

1.2 Environment Variables
-------------------------
To set the SDK path, run SetEnv.bat from your Platform SDK installation
directory. The MSSDK path must appear before your compiler path.

If you are using Microsoft Visual C++ (R) as your compiler, run
VCVars32.bat before running SetEnv.bat from the Platform SDK directory.

Usage:   SetEnv MSSDK
Where:   MSSDK specifies where the Platform SDK was installed

Example: SetEnv C:\MSSDK sets the environment relative to C:\MSSDK


1.3 Documentation Setup
-----------------------

1.3.1 New HTML Help Format
--------------------------
The Platform SDK documentation is now provided in HTML Help format.
If you are running on Windows NT, the update program for HTML Help
may fail during setup unless you have Administrator privileges.
If you encounter an error such as

"Cannot open the file d:\%MSSDK%\help\psdk.col"

be sure that you have Internet Explorer 3.02 or later installed and
run the HTML Help update program, HHUpd.exe, from the Platform
SDK CD. 

HHUpd.exe is located in <CD-Drive>:\cabs\[i386|alpha]\HHUpd.exe 
and can be run from the command line or from Explorer to verify 
that your version of HTML Help is up to date.


1.3.2 Infoviewer Integration
----------------------------
The Platform SDK documentation is no longer integrated with the
Visual Studio 97 documentation.  If you have previously installed
the Platform SDK and deleted the %MSSDK%\Help directory, Visual
Studio Help may encounter an error indicating that it cannot find
the Platform SDK documentation files.  This occurs because the
registry settings are pointing the Infoviewer to files that no
longer exist.

If this occurs uninstall the "Microsoft Developer Network Library
Edition - January 1998" (or which ever version you have installed)
and reinstall it.

To verify that Infoviewer is looking for files that really exist,
check whether the following registry keys point to valid file locations:

 "HKLM","SOFTWARE\Microsoft\Infoviewer\5.0\Titles\<BASENAME>","Content"
 should point to "<HelpFileCDPath><BASENAME>.ivt"

 "HKLM","SOFTWARE\Microsoft\Infoviewer\5.0\Titles\<BASENAME>","Index"
 should point to "<HelpFileLocalPath><BASENAME>.ivi"

where <BASENAME> is in the following list of Platform SDK Infoviewer
files and <HelpFileCDPath> is the full path to the MSDN CD directory
containing the .ivt file. <HelpFileLocalPath> is the full path to the
MSDN installed directory containing the .ivi file.

If you have MSDN installed you can verify what the paths are by looking
at a different Title\<BASENAME> key.

The following is the list of Platform SDK Infoviewer file <BASENAME>'s:
   pdintro
   pdapp
   pdmsg
   pdgrmm
   pdinet
   pdnds
   pdobj
   pdsms
   pdui
   pdwbase
   pdref

1.4 Known Issues
----------------

- For Windows NT 5.0 Beta 2, MoveFileEx with the
  MOVEFILE_DELAY_UNTIL_REBOOT flag fails if lpExistingFileName is a
  relative path. This will be fixed in the final release of Windows
  NT 5.0 to work with both absolute and relative paths.

- New linker format (see "2.0 Tested Compilers and New Linker"
  following).

- Building all of the samples requires more than 2 GB of disk space.

- Building assembler files.

  A few of the samples build some components out of .asm files. If you
  do not have a program equivalent to ML.exe, the Microsoft Assembler
  product, MASM, can be purchased.  No assembler is provided with the
  Platform SDK. If you are an MSDN Universal subscriber, MASM is
  included in your Office Test Platform CDs on Disc 13.

- The following samples do not build on Digital Alpha systems. In some
  cases, the Microsoft Visual C++ makefile shipped with the sample
  specifically targets x86. In these cases, you can load the sample into
  Microsoft (R) Developer Studio (R) and create an Alpha target.

    Mssdk\Samples\Multimedia\BA\Tvxsamp
    Mssdk\Samples\Multimedia\DirectX\Memtime
    Mssdk\Samples\Internet\IE\ColBtn
    Mssdk\Samples\Internet\IE\Drill\Driller
    Mssdk\Samples\Internet\IE\IELnk
    Mssdk\Samples\Internet\IE\IEMime
    Mssdk\Samples\Internet\IE\IISLog
    Mssdk\Samples\Internet\IE\Percy
    Mssdk\Samples\Internet\IE\TDC
    Mssdk\Samples\Internet\IE\UrlMon\Progress
    Mssdk\Samples\Internet\IE\WabTool
    Mssdk\Samples\Internet\IE\WalkAll
    Mssdk\Samples\Internet\MSChat\Chat2000
    Mssdk\Samples\Internet\NetMeeting\InstCodc
    Mssdk\Samples\Internet\NetMeeting\NMFT
    Mssdk\Samples\Internet\NetMeeting\NMShare
    Mssdk\Samples\Internet\NetMeeting\NMUI
    Mssdk\Samples\Internet\NetMeeting\Skippy

  The following samples contain inline assembly and do not build on
  Digital Alpha systems.

    Mssdk\Samples\WinBase\Security\WinNT\SampSSP
    Mssdk\Samples\MultiMedia\DirectX\Duel
    Mssdk\Samples\MultiMedia\DirectX\Flip2D

- In WinError.h, the old error define
    CERT_E_VALIDIYPERIODNESTING
  has been changed to
    CERT_E_VALIDITYPERIODNESTING

===================================
2.0 Tested Compilers and New Linker
===================================
The Platform SDK has been tested with Microsoft Visual C++ version 5.0.
Most samples will build with other compilers, but other compilers were
not completely tested. Visual C++ 6.0 was tested and ATL requires
updates to work with the current headers.  These updates can be found
in the %mssdk%\Include\ATL30 directory.  The files in this subdirectory
need to replace the ones shipped with Visual C++ 6.0.

2.1  New Import Library Format
------------------------------
The import libraries included with this release of the Platform SDK
have a new format that reduces their size and allows for faster link
times.  If you cannot use the linker that comes with the Platform SDK,
or if you do not have Visual C++ 5.0 with Service Pack 3, then the
supplied libraries will need to be converted to the old format using
the linker supplied with this Platform SDK in the MSSDK\BIN\LINK
subdirectory. Create a new directory that will contain the old format
import libraries. For each import library, use the command:

    link /lib /convert /out:.\{oldformat}\{library}.lib {library}.lib

where {oldformat} is the directory that will contain the converted 
library and {library} is the import library to be converted. Visual C++
SP3 users can replace the linker supplied with VC++ with the one in this 
Platform SDK.

Visual C++ 6.0 users should not use this linker as it does not understand
the updated (PDB6) symbol format.

2.2  Common Sources of Warnings
---------------------------------
* MakeProcInstance: Do not use this function.  Pass 
  DLGPROC directly (the first parameter to MakeProcInstance).
  Also, be sure to delete the FreeProcInstance function
  that is paired with MakeProcInstance.

* Explicit casts are now necessary in many situations 
  where intrinsic casts worked before.  An example:
  MSSDK\samples\dbmsg\sql\dblib\c\sqltestn\SqltestN.c(186).
  The (DLGPROC) cast was not necessary before. A warning
  is now generated if a cast is omitted.

* CODE and DATA statements are not supported for use in 
  makefiles on the Win32 (R) platform.

===========================
3.0 Header File Conventions
===========================
While this SDK can be used to target applications for Windows 95,
Windows NT 4.0, and Windows 98 using the header file conventions
below, it is primarily intended for Windows NT 5.0 pre-release 
development and testing.

Target Platform                    Value to set
---------------                    ------------

  Microsoft Windows 95             WINVER=0x0400
  and Windows NT 4.0 (and later)     

  Microsoft Windows 98             _WIN32_WINDOWS=0x0410
  and Windows NT 4.0 (and later)   WINVER=0x0400

  Windows NT 4.0 (and later)       _WIN32_WINNT=0x0400
                                   WINVER=0x0400

  Windows 98 and Windows NT 5.0    WINVER=0x0500
  (and later)

  Internet Explorer 3.0            _WIN32_IE=0x0300
  (and later)

  Internet Explorer 4.0            _WIN32_IE=0x0400
  (and later)

  Internet Explorer 5.0            _WIN32_IE=0x0500
  (and later)


  Setting a WINVER of 0x0500 implies _WIN32_IE=0x0400

Examining the headers will reveal which platforms implement the
various technologies.  This section can help to decode the headers.

In the header files, 
information protected by        Implemented in
------------------------        --------------

 #if _WIN32_WINNT >= 0x0400     Windows NT 4.0 and later. 
                                It is not implemented on
                                Windows 95.

 #if _WIN32_WINDOWS >= 0x0410   Windows 98 and later: Image
                                may not run on Windows 95.   

 #if _WIN32_WINNT >= 0x0500     Windows NT 5.0 and later: Image
                                may not run on Windows 95.

 #if WINVER >= 0x0410           Windows 98 and later.

 #if WINVER >= 0x0500           Windows NT 5.0 and later.

 #if _WIN32_IE >= 0x0300        Internet Explorer 3.0 
                                and later.

 #if _WIN32_IE >= 0x0400        Internet Explorer 4.0 
                                and later.

 #ifdef _WIN32_WINCE            Microsoft Windows CE 1.0
                                and later. (Note that some Windows
                                CE platforms may not support all
                                APIs.)

The value of _WIN32_WINNT is set in Win32.mak, depending on the
platform you choose to target.  By default, Win32.mak sets the
TARGETOS to WINNT and the APPVER to 4.0.  As a result, by default, 
_WIN32_WINNT is now defined as 0x0400.  

By default, Win32.mak sets _WIN32_IE to 0x0300 if it is not
already defined. To specifically target Internet Explorer 4.x or
to take advantage of the new CommCtrl features introduced in
Internet Explorer 4.0 (ReBar, VListVw, etc.), set _WIN32_IE to 0x0400.

If you are building an application to run on Windows 95 and you want 
compile-time notification of compatibility issues, set TARGETOS=BOTH 
in your makefile. When TARGETOS is defined as BOTH, _WIN32_WINNT is 
not defined for the precompiler, and the only information parsed at 
compile-time is applicable to both Windows 95 and Windows NT.

If you do not include Win32.mak in your makefile, you must
explicitly define _WIN32_WINNT as 0x0500 to get the Windows NT 
5.0-specific material from the header files.

CryptoAPI is one of several API sets present in Windows 95,
OEM Service Release 2 (OSR2) that are still guarded by
(_WIN32_WINNT >= 0x0400). If you are writing an application
specifically for OSR2, and you want the header files to provide
compile time access to these functions, it is necessary to define
_WIN32_WINNT as 0x0400. Notice that an application that uses these
technologies does not run correctly on the retail release of
Windows 95.  Most applications that are expected to run on unmodified
Windows 95 should be built without defining _WIN32_WINNT.

Previous releases of the Platform SDK and the Win32 SDK included
the following definitions in Win32.mak to map structured exception
handling keywords to their proper underscored names:
    try -> __try 
    except -> __except 
    finally -> __finally 
    leave -> __leave

This caused problems for developers who chose to use C++ 
structured exception handling in which "try" is supposed to
be "try" and not "__try".  For this reason, by default, 
the mapping has been removed from Win32.mak. This  may
cause build-time errors for your applications.  To get 
the old behavior add 
    SEHMAP = TRUE 
to your makefile before including Win32.mak.


==========================
4.0 RPC/MIDL Release Notes
==========================

4.1 What's New
--------------
Asynchronous RPC
The RPC run-time environment now supports asynchronous remote
procedure calls to allow your programs to handle multiple outstanding
calls from a single-threaded client. This prevents data transmission
bottlenecks that can arise from slow or delayed clients or servers.
With asynchronous pipe parameters, client/server applications can
transfer large amounts of data incrementally, without blocking the
client or server threads from performing other tasks. For more
information, see the "Asynchronous RPC" section in the Platform SDK
documentation.

New HTTP Protocol Sequence
The ncacn_http protocol allows client and server applications to
communicate across the Internet by using the Microsoft Internet
Information Server (IIS) as a proxy. Because calls are tunneled through
an established HTTP port, they can cross most firewalls.

Name Service
The Remote Procedure Call (RPC) Name Service (Locator) uses Windows NT
5.0 Active Directory as its database. This means that exported entries
can be made persistent even when a server is rebooted. For more
information, see the RPC reference pages for RpcNsBindingExport,
RpcNsBindingImportNext, RpcNsBindingLookupBegin, and
RpcNsBindingUnexport in the Platform SDK documentation.

New Type Library (TLB) Attributes
Microsoft Interface Definition Language (MIDL) supports double-byte
character set (DBCS) international locales. TLB file generation has
been significantly improved and all the type library attributes
are supported. For more information, see "Type Library Attributes"
in the Platform SDK documentation.

4.2 Using New and Updated SDK Headers
-------------------------------------
New Headers and MIDL
Headers that were compiled with the new MIDL compiler (including most
MIDL-generated headers in the Platform SDK) require the new SDK
headers to work.  This is intentional.  As long as the SDK remains
in the include path ahead of the compiler everything should work.

===================================================
5.0 Windbg Debugger and Visual C++ 6.0/PDB6 Support
===================================================

The debuggers in the Platform SDK (WinDbg, i386KD, AlphaKD, NTSD, and
CDB) have been updated to support the new PDB symbol format used by
Microsoft Visual C++ 6.0, part of the Microsoft Visual Studio (R)
suite. This SDK was tested primarily with Visual C++ 5.0 because Visual
C++ 6.0 is not yet generally available. Visual C++ 6.0 coverage was
not as complete as with Visual C++ 5.0.  For example Visual C++ 6.0
is more stringent about warnings and errors in code; not all of the
samples have been cleaned up to compile cleanly under Visual C++ 6.0.
For more information, see the Visual C++ 6.0 release notes and
<http://msdn.microsoft.com/visualc/>.

========================
6.0 SDK Content Overview
========================

The Platform SDK is the successor to the Win32 and BackOffice (R) SDKs.
It is intended to support development for Microsoft's Distributed
Network Architecture--the infrastructure provided by Microsoft for
the "digital nervous system."

Many of the technology components of this infrastructure were once
shipped in separate SDKs and did not always work well together.
The Platform SDK integrates these SDK components and tests the
build environment as a whole, provides a unified set of documentation,
and provides "one-stop shopping" for samples, headers, etc.

The following is a partial list of SDKs that are now integrated into
the Platform SDK:

  Win32 SDK
  BackOffice SDK
  ODBC SDK
  OLEDB SDK
  Data Access SDK
  BackOffice SDK
  ActiveX (R) SDK
  Internet Client SDK
  MAPI SDK
  OLE SDK
  SDK for Java

Here is a brief description of the contents of the Platform SDK:

BIN       SDK tools, DLLs, and self-extracting .exe files
HELP      SDK documentation files which can be viewed with Infoviewer
          5.0. Infoviewer 5.0 can be installed by running Setup.exe from
          the root of the Platform SDK CD
INCLUDE   Headers, IDL files, and global Platform SDK makefiles--
          Win32.mak and BkOffice.mak--used from most SDK command-line
          makefiles
LIB       Libraries
REDIST    Redistributables
SAMPLES   Platform SDK samples (see following)

This readme file refers to the tools, the INCLUDE files, and the LIB
files collectively as the "build environment." The samples include
subdirectories covering the following areas:

\MSSDK\SAMPLES\Begin
* Generic Win32 DLL
* Generic Win32 EXE
* Basic Win32 Help

\MSSDK\SAMPLES\COM
* Base COM
* COM Tutorial Samples
* DCOM (including security)
* Microsoft Transaction Server
* ActiveX Controls
* OLE 2
* Automation
* Active Documents

\MSSDK\SAMPLES\DbMsg: Database and Messaging
* ADO
* OLEDB
* Microsoft Exchange
* Microsoft SQL Server
* ODBC
* MAPI

\MSSDK\SAMPLES\Internet
* IE         - Internet Explorer capabilities and extensions
               (including WinInet)
* IIS        - Internet Information Server; ISAPI and Active Server
* Index      - Programmatic access to the Content Indexing catalogs
* MSAgent    - Demonstrate "interactive personalities" from web pages
* MSChat     - ActiveX chat control and what can be done with it
* NetMeeting - NetMeeting ActiveX control and related tools
* Scripting  - ActiveX Scripting
* WebPost    - APIs for updating content on Web sites

\MSSDK\SAMPLES\Multimedia
* Broadcast Architecture
* Direct3D Immediate Mode and Retained Mode
* DirectAnimation
* DirectDraw
* DirectInput
* DirectPlay
* DirectShow
* DirectSound
* DirectX Foundation
* GDI
* Image Color Management (ICM) 2.0
* OpenGL
* Win32 Audio, Input, and Video

\MSSDK\SAMPLES\NetDS: Networking and Distributed Services
* Active Directory Service Interface (ADSI)
* Microsoft Message Queue
* Routing and Remote Access Service
* TAPI 3.0 and TAPI 2.0
* Windows Sockets
* SNA Server
* RPC
* SNMP
* NetAPI
* DLC

\MSSDK\SAMPLES\SdkTools
* Source code to selected SDK tools

\MSSDK\SAMPLES\SysMgmt: Systems Management
* Microsoft Management Console (MMC)
* Task Scheduler
* Windows 95 Migration DLLs for Windows NT 5 setup (beta)
* Microsoft System Management Server
* Setup and Microsoft Installer Service (beta)
* SMS samples

\MSSDK\SAMPLES\WinBase: Windows Base Services
* Cluster
* Fibers
* I/O
* IPC
* Memory
* Registry
* Smart Card
* Security
* Windows NT Media Services (Windows NT 5.0)

\MSSDK\SAMPLES\WinUI: Windows User Interface
* Base graphical user interface (GUI) capabilities
* Win32 console functions
* Win32 DLL templates
* Common dialog boxes, including File
* Common controls, including RichEdit, Rebar, and
  ListView
* Wheel mouse and associated APIs
* Combo boxes and Owner Draw boxes
* Dynamic dialog box templates
* Icon manipulation
* Message tables
* Band objects
* Namespace extensions
* Drag-and-drop context menus
* File viewers
* File parsing
* Basic shell extensions, including context menu,
  property sheet, icon handler, and copy hook extensions          

======================
 7.0 OnNow API Support
======================
The following OnNow functions are not supported in Windows NT 5.0
Beta 2. They will be supported in a future release.

* RequestDeviceWakeup
* CancelDeviceWakeupRequest
* SetMessageWaitingIndicator
* IsSystemResumeAutomatic

====================================
 8.0 NTDSBCLI conflicts with EDBBCLI
====================================
In this release of the Platform SDK the NTDSBCLI functions conflict
with some of the EDBBCLI APIs.  This conflict will be resolved in a
future release.

========================
 9.0 COM and SSL Support
========================
The Platform SDK documentation refers to using the SSL security
protocol with COM. This feature is not supported in Windows NT 5
Beta 2.

===========================================
10.0 Providing Feedback on the Platform SDK
===========================================
We are sincerely interested in your feedback on the Platform SDK.  
Please mail suggestions or bug reports for the Platform SDK
to SdkFdBk@Microsoft.com. This is not a support alias, but your
feedback will help us to plan future changes for the Platform SDK and
will make the SDK more useful to you in the future.

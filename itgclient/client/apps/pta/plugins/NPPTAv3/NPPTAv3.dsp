# Microsoft Developer Studio Project File - Name="NPPTAv3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=NPPTAv3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "NPPTAv3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NPPTAv3.mak" CFG="NPPTAv3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NPPTAv3 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NPPTAv3 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NPPTAV3_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Common" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "HAVE_LONG_LONG" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "..\..\..\..\modules\lib\static\release\bsafelite.lib" /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NPPTAV3_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "HAVE_LONG_LONG" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "..\..\..\..\modules\lib\static\debug\bsafelite.lib" /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "NPPTAv3 - Win32 Release"
# Name "NPPTAv3 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\addrootswrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\NPPTAv3.def
# End Source File
# Begin Source File

SOURCE=.\src\npvspref.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\thirdparty\netscape\PluginSDK\Common\npwin.cpp
# End Source File
# Begin Source File

SOURCE=.\src\P12wrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\stubs.c
# End Source File
# Begin Source File

SOURCE=.\src\vscertprefswrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsdnzwrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsimportwrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsprofmgmtwrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsptadllapiwrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsptawrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsroamprefswrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsselecteddigidwrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vssrchcritwrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsuiprefswrap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\XEnrollWrap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\addrootswrap.h
# End Source File
# Begin Source File

SOURCE=.\include\global.h
# End Source File
# Begin Source File

SOURCE=.\include\java_lang_reflect_Array.h
# End Source File
# Begin Source File

SOURCE=.\include\java_lang_StringBuffer.h
# End Source File
# Begin Source File

SOURCE=.\include\java_util_Date.h
# End Source File
# Begin Source File

SOURCE=.\include\p12wrap.h
# End Source File
# Begin Source File

SOURCE=.\include\resource.h
# End Source File
# Begin Source File

SOURCE=.\include\vscertprefswrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsdnzwrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsimportwrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsprofmgmtwrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsptadllapiwrap.h
# End Source File
# Begin Source File

SOURCE=.\include\VSPTAv3.h
# End Source File
# Begin Source File

SOURCE=.\include\vsptawrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsroamprefswrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsselecteddigidwrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vssrchcritwrap.h
# End Source File
# Begin Source File

SOURCE=.\include\vsuiprefswrap.h
# End Source File
# Begin Source File

SOURCE=.\include\XEnrollWrap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\NPPTAv3.rc
# End Source File
# End Group
# End Target
# End Project

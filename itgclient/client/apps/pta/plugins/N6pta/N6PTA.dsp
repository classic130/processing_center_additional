# Microsoft Developer Studio Project File - Name="N6PTA" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=N6PTA - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "N6PTA.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "N6PTA.mak" CFG="N6PTA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "N6PTA - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "N6PTA - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "N6PTA - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "N6PTA_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\NPPTAv3\src" /I "i:\N6PluginSDK\include" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\NPPTAv3\include" /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "N6PTA_EXPORTS" /D "XP_PC" /D WINVER=0x400 /D _MSC_VER=1200 /D "_X86_" /D "_NS6_PTA_" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "i:\N6PluginSDK\lib\xpcom.lib" "..\..\..\..\modules\lib\static\release\bsafelite.lib" /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "N6PTA - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "N6PTA_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\NPPTAv3\src" /I "i:\N6PluginSDK\include" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\NPPTAv3\include" /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /D "DEBUG" /D "XP_PC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D WINVER=0x400 /D _MSC_VER=1200 /D "_X86_" /D "N6PTA_EXPORTS" /D "_NS6_PTA_" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "i:\N6PluginSDK\lib\xpcom.lib" "..\..\..\..\modules\lib\static\debug\bsafelite.lib" /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "N6PTA - Win32 Release"
# Name "N6PTA - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\NPPTAv3\src\addrootswrap.cpp
# End Source File
# Begin Source File

SOURCE=.\source\N6PTA.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\P12wrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vscertprefswrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsdnzwrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsimportwrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsprofmgmtwrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsptadllapiwrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsptawrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsroamprefswrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsselecteddigidwrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vssrchcritwrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\vsuiprefswrap.cpp
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\src\XEnrollWrap.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\NPPTAv3\include\addrootswrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\global.h
# End Source File
# Begin Source File

SOURCE=.\include\N6PTA.h
# End Source File
# Begin Source File

SOURCE=.\include\N6PTACID.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\p12wrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vscertprefswrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsdnzwrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsimportwrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsprofmgmtwrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsptadllapiwrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsptawrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsroamprefswrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsselecteddigidwrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vssrchcritwrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\vsuiprefswrap.h
# End Source File
# Begin Source File

SOURCE=..\NPPTAv3\include\XEnrollWrap.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\N6PTA.rc
# End Source File
# End Group
# End Target
# End Project

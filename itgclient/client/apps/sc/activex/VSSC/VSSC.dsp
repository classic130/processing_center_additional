# Microsoft Developer Studio Project File - Name="VSSC" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VSSC - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VSSC.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VSSC.mak" CFG="VSSC - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VSSC - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VSSC - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VSSC - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "include" /I "..\..\..\..\..\common\utils\include" /I "..\..\..\..\..\common\scmodules\pkcs7engine\include" /I "..\..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\..\common\gmemmgmt\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\..\itgclient\client\modules\bsafelite\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /FR /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /X
# SUBTRACT MTL /nologo /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib Version.lib crypt32.lib ..\..\..\..\..\common\lib\debug\mimeengine.lib ..\..\..\..\..\common\lib\debug\utils.lib ..\..\..\..\..\common\lib\debug\gmemmgmt.lib ..\..\..\..\..\common\lib\debug\pkcs7engine.lib ..\..\..\..\..\common\lib\debug\simder.lib ..\..\..\..\..\..\itgclient\client\modules\lib\static\debug\bsafelite.lib /nologo /subsystem:windows /dll /debug /machine:I386
# SUBTRACT LINK32 /profile /map
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\VSSC.dll
InputPath=.\Debug\VSSC.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zd /O1 /I ".\\" /I "include" /I "..\..\..\..\..\common\utils\include" /I "..\..\..\..\..\common\scmodules\pkcs7engine\include" /I "..\..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\..\common\gmemmgmt\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\..\itgclient\client\modules\bsafelite\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib Version.lib crypt32.lib ..\..\..\..\..\common\lib\release\mimeengine.lib ..\..\..\..\..\common\lib\release\utils.lib ..\..\..\..\..\common\lib\release\gmemmgmt.lib ..\..\..\..\..\common\lib\release\pkcs7engine.lib ..\..\..\..\..\common\lib\release\simder.lib ..\..\..\..\..\..\itgclient\client\modules\lib\static\release\bsafelite.lib /nologo /subsystem:windows /dll /profile /map /debug /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VSSC.dll
InputPath=.\ReleaseMinDependency\VSSC.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "VSSC - Win32 Debug"
# Name "VSSC - Win32 Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\sources\AppContext.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\AttachInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\certmgmt.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Msg.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Post.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\sources\UserInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\VSSC.cpp
# End Source File
# Begin Source File

SOURCE=.\VSSC.def
# End Source File
# Begin Source File

SOURCE=.\sources\VSSC.idl

!IF  "$(CFG)" == "VSSC - Win32 Debug"

# ADD MTL /tlb "VSSC.tlb" /h "vssc.h" /iid "vssc_i.c" /Oicf

!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"

# ADD MTL /tlb ".\VSSC.tlb" /h "vssc.h" /iid "vssc_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\VSSC.rc
# End Source File
# Begin Source File

SOURCE=.\sources\vssc_pta.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\VSSC_SMIME.CPP
# End Source File
# Begin Source File

SOURCE=.\sources\vssc_util.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\VSSMC.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\AppContext.h
# End Source File
# Begin Source File

SOURCE=.\include\AttachInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\certmgmt.h
# End Source File
# Begin Source File

SOURCE=.\include\Global.h
# End Source File
# Begin Source File

SOURCE=.\include\Msg.h
# End Source File
# Begin Source File

SOURCE=.\include\Post.h
# End Source File
# Begin Source File

SOURCE=.\include\resource.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\include\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\include\UserInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\vssc_pta.h
# End Source File
# Begin Source File

SOURCE=.\include\VSSC_SMIME.H
# End Source File
# Begin Source File

SOURCE=.\include\vssc_util.h
# End Source File
# Begin Source File

SOURCE=.\include\VSSCErrs.h
# End Source File
# Begin Source File

SOURCE=.\include\VSSCMacros.h
# End Source File
# Begin Source File

SOURCE=.\include\VSSMC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\ISignerInfo.rgs
# End Source File
# Begin Source File

SOURCE=.\ResolveRcpt.rgs
# End Source File
# Begin Source File

SOURCE=.\vssc.bmp
# End Source File
# Begin Source File

SOURCE=.\VSSC.rgs
# End Source File
# Begin Source File

SOURCE=.\VSSCDllApi.rgs
# End Source File
# Begin Source File

SOURCE=.\VSSignerInfo.rgs
# End Source File
# End Group
# End Target
# End Project

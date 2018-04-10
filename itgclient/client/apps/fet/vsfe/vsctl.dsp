# Microsoft Developer Studio Project File - Name="vsctl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=vsctl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vsctl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsctl.mak" CFG="vsctl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vsctl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsctl - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsctl - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsctl - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsctl - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsctl - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vsctl - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "res" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /map /debug /machine:I386 /out:"debug/vsfe.dll" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"vsfectl" /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\vsfectl
InputPath=.\vsfectl
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /machine:I386 /out:"vsfectl"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\vsfectl
InputPath=.\vsfectl
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"

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
# ADD CPP /nologo /MT /W3 /O1 /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /map /machine:I386 /out:"releasemindependency/vsfe.dll"

!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /machine:I386 /out:"vsfectl"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\vsfectl
InputPath=.\vsfectl
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /machine:I386 /out:"vsfectl"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\vsfectl
InputPath=.\vsfectl
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "vsctl - Win32 Debug"
# Name "vsctl - Win32 Unicode Debug"
# Name "vsctl - Win32 Release MinSize"
# Name "vsctl - Win32 Release MinDependency"
# Name "vsctl - Win32 Unicode Release MinSize"
# Name "vsctl - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\certmgmt.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ClsFact.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\ContMenu.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\cryptsup.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DataObj.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\dlgprocs.cpp
# End Source File
# Begin Source File

SOURCE=.\src\DropSrc.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\Droptgt.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\encdeclist.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Enumidl.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\ExtrIcon.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\PidlMgr.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\policysup.cpp
# End Source File
# Begin Source File

SOURCE=.\src\safedel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\ShlFldr.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\ShlView.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\slist.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\src\util.cpp
# End Source File
# Begin Source File

SOURCE=.\src\Viewlist.Cpp
# End Source File
# Begin Source File

SOURCE=.\src\vscontainer.cpp
# End Source File
# Begin Source File

SOURCE=.\vsctl.cpp
# End Source File
# Begin Source File

SOURCE=.\vsctl.def
# End Source File
# Begin Source File

SOURCE=.\vsctl.idl
# ADD MTL /tlb ".\vsctl.tlb" /h "vsctl.h" /iid "vsctl_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=res\vsctl.rc
# End Source File
# Begin Source File

SOURCE=.\vsctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsnvp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vsnvp_file.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vspmsp.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vspmutil.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vspolicyfile.cpp
# End Source File
# Begin Source File

SOURCE=.\src\vssafe.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\h\certmgmt.h
# End Source File
# Begin Source File

SOURCE=.\h\ClsFact.h
# End Source File
# Begin Source File

SOURCE=.\h\Commands.h
# End Source File
# Begin Source File

SOURCE=.\h\ContMenu.h
# End Source File
# Begin Source File

SOURCE=.\h\cryptsup.h
# End Source File
# Begin Source File

SOURCE=.\h\DataObj.h
# End Source File
# Begin Source File

SOURCE=.\h\dlgprocs.h
# End Source File
# Begin Source File

SOURCE=.\h\DropSrc.h
# End Source File
# Begin Source File

SOURCE=.\h\Droptgt.h
# End Source File
# Begin Source File

SOURCE=.\h\encdeclist.h
# End Source File
# Begin Source File

SOURCE=.\h\Enumidl.h
# End Source File
# Begin Source File

SOURCE=.\h\ExtrIcon.h
# End Source File
# Begin Source File

SOURCE=.\h\global.h
# End Source File
# Begin Source File

SOURCE=.\h\Guid.h
# End Source File
# Begin Source File

SOURCE=.\h\PidlMgr.h
# End Source File
# Begin Source File

SOURCE=.\h\policysup.h
# End Source File
# Begin Source File

SOURCE=.\res\resource.h
# End Source File
# Begin Source File

SOURCE=.\h\safedel.h
# End Source File
# Begin Source File

SOURCE=.\h\ShlFldr.h
# End Source File
# Begin Source File

SOURCE=.\h\ShlView.h
# End Source File
# Begin Source File

SOURCE=.\h\slist.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\h\Tools.h
# End Source File
# Begin Source File

SOURCE=.\h\util.h
# End Source File
# Begin Source File

SOURCE=.\h\Viewlist.h
# End Source File
# Begin Source File

SOURCE=.\vsctrl.h
# End Source File
# Begin Source File

SOURCE=.\h\vsferrs.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\banner.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\check.ico
# End Source File
# Begin Source File

SOURCE=.\res\closedsafe.ico
# End Source File
# Begin Source File

SOURCE=.\res\closesafe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cross.ico
# End Source File
# Begin Source File

SOURCE=.\res\decrypted.bmp
# End Source File
# Begin Source File

SOURCE=.\res\encrypted.bmp
# End Source File
# Begin Source File

SOURCE=.\res\face.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\line.bmp
# End Source File
# Begin Source File

SOURCE=.\res\lock2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\multiplesel.ico
# End Source File
# Begin Source File

SOURCE=.\res\open.bmp
# End Source File
# Begin Source File

SOURCE=.\res\opensafe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\opensafe.ico
# End Source File
# Begin Source File

SOURCE=.\res\overlay.ico
# End Source File
# Begin Source File

SOURCE=.\res\recdecr.bmp
# End Source File
# Begin Source File

SOURCE=.\res\safe.bmp
# End Source File
# Begin Source File

SOURCE=.\res\safelock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\test.ico
# End Source File
# Begin Source File

SOURCE=.\res\toolbarlock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\unlock.ico
# End Source File
# Begin Source File

SOURCE=.\res\valid.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ver_07.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ver_10.bmp
# End Source File
# Begin Source File

SOURCE=C:\TEMP\ver_logo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ver_logo_1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vsctrl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vsctrl.rgs
# End Source File
# Begin Source File

SOURCE=.\res\vslogo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vslogosmall.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\filecopy.avi
# End Source File
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="Ptav3" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Ptav3 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ptav3.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ptav3.mak" CFG="Ptav3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ptav3 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ptav3 - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ptav3 - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ptav3 - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ptav3 - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Ptav3 - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /Gi /ZI /Od /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "..\..\..\..\modules\RoamingClient\include" /I "..\..\..\..\modules\VS_IBMTSS\include" /I "i:\Platform SDK\include" /I "i:\TSS SDK\IBM\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D VS_TSSDLL=1 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib crypt32.lib Ws2_32.lib "..\..\..\..\modules\lib\static\debug\bsafelite.lib" "..\..\..\..\modules\lib\static\debug\ProtectedStorage.lib" "..\..\..\..\..\common\lib\Debug\simder.lib" "..\..\..\..\modules\RoamingClient\lib\debug\vsrmclient.lib" "I:\TSS SDK\IBM\lib\tspi.lib" /nologo /subsystem:windows /dll /pdb:"./Debug/Ptav3.pdb" /debug /machine:I386 /nodefaultlib:"libm.lib" /out:"./Debug/Ptav3.dll" /pdbtype:sept /libpath:"I:\Platform SDK\Lib" /libpath:"I:\TSS SDK\IBM\lib"
# SUBTRACT LINK32 /pdb:none /incremental:no
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\Ptav3.dll
InputPath=.\Debug\Ptav3.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	REM regsvr32 /s /c "$(TargetPath)" 
	REM echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=if not exist "..\..\..\..\lib\dynamic\debug" md "..\..\..\..\lib\dynamic\debug"	copy debug\ptav3.dll "..\..\..\..\lib\dynamic\debug"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\Ptav3.dll
InputPath=.\DebugU\Ptav3.dll
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

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

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
# ADD CPP /nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Ptav3.dll
InputPath=.\ReleaseMinSize\Ptav3.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

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
# ADD CPP /nologo /MD /W3 /O1 /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "..\..\..\..\modules\RoamingClient\include" /I "..\..\..\..\modules\VS_IBMTSS\include" /I "i:\TSS SDK\IBM\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D VS_TSSDLL=1 /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib crypt32.lib Ws2_32.lib "..\..\..\..\modules\lib\static\release\bsafelite.lib" "..\..\..\..\modules\lib\static\release\ProtectedStorage.lib" "..\..\..\..\..\common\lib\Release\simder.lib" "..\..\..\..\modules\RoamingClient\lib\release\vsrmclient.lib" "I:\TSS SDK\IBM\lib\tspi.lib" /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libm.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib"
# SUBTRACT LINK32 /verbose
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Ptav3.dll
InputPath=.\ReleaseMinDependency\Ptav3.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=if not exist "..\..\..\..\lib\dynamic\Release" md "..\..\..\..\lib\dynamic\Release"	copy ReleaseMinDependency\ptav3.dll "..\..\..\..\lib\dynamic\Release"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

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
# ADD CPP /nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Ptav3.dll
InputPath=.\ReleaseUMinSize\Ptav3.dll
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

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

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
# ADD CPP /nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ../BSafeLite/Release/bsafelite.lib crypt32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Ptav3.dll
InputPath=.\ReleaseUMinDependency\Ptav3.dll
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

# Name "Ptav3 - Win32 Debug"
# Name "Ptav3 - Win32 Unicode Debug"
# Name "Ptav3 - Win32 Release MinSize"
# Name "Ptav3 - Win32 Release MinDependency"
# Name "Ptav3 - Win32 Unicode Release MinSize"
# Name "Ptav3 - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "IDLS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\certprefs.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\export.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "Include/export.h" /iid "source/export_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "Include/export.h" /iid "source/export_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\import.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "Include/import.h" /iid "source/import_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "Include/import.h" /iid "source/import_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "Include/import.h" /iid "source/import_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "Include/import.h" /iid "source/import_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "Include/import.h" /iid "source/import_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "Include/import.h" /iid "source/import_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Source\profmgmt.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\ptadllapi.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\source\Ptav3.idl
# ADD MTL /tlb "ptav3.tlb" /h "Include\ptav3.h" /iid "source\ptav3_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\source\roamprefs.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Source\seldigid.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Source\srchcrit.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Source\uiprefs.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

# ADD MTL /tlb "" /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

# ADD MTL /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

# ADD MTL /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

# ADD MTL /tlb "" /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

# ADD MTL /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

# ADD MTL /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf

!ENDIF 

# End Source File
# End Group
# Begin Group "CSP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\csputil.cpp
# End Source File
# Begin Source File

SOURCE=.\source\HelperFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\source\vs_csp.cpp
# End Source File
# Begin Source File

SOURCE=.\source\vs_tpm_csp.cpp
# End Source File
# End Group
# Begin Group "PTA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\certinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\ExportP12.cpp
# End Source File
# Begin Source File

SOURCE=.\source\FindPrimes.cpp
# End Source File
# Begin Source File

SOURCE=.\source\langutils.cpp
# End Source File
# Begin Source File

SOURCE=.\source\MyUniversalInteger.cpp
# End Source File
# Begin Source File

SOURCE=.\source\P12Helper.cpp
# End Source File
# Begin Source File

SOURCE=.\source\pkcs12info.cpp
# End Source File
# Begin Source File

SOURCE=.\source\PtaEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\source\PTAUI.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\Ptav3.cpp
# End Source File
# Begin Source File

SOURCE=.\source\Ptav3.def
# End Source File
# Begin Source File

SOURCE=.\source\utils.cpp
# End Source File
# Begin Source File

SOURCE=.\source\virtualsmartcard.cpp
# End Source File
# Begin Source File

SOURCE=.\source\vscapi.cpp
# End Source File
# Begin Source File

SOURCE=.\Source\VSPTA.cpp
# End Source File
# End Group
# Begin Group "RootsUpdate"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\roots.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\source\Ptav3.rc
# End Source File
# Begin Source File

SOURCE=.\Source\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "CSPHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Include\cspglobals.h
# End Source File
# Begin Source File

SOURCE=.\Include\cspincludes.h
# End Source File
# Begin Source File

SOURCE=.\Include\cspstructures.h
# End Source File
# Begin Source File

SOURCE=.\Include\csputil.h
# End Source File
# Begin Source File

SOURCE=.\Include\HelperFunctions.h
# End Source File
# Begin Source File

SOURCE=.\Include\keycontainer.h
# End Source File
# Begin Source File

SOURCE=.\Include\vs_csp.h
# End Source File
# Begin Source File

SOURCE=.\include\vs_tpm_csp.h
# End Source File
# Begin Source File

SOURCE=.\Include\VSCSP_Macros.h
# End Source File
# End Group
# Begin Group "MangledHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Include\mangledcertprefs.h
# End Source File
# Begin Source File

SOURCE=.\include\mangledexport.h
# End Source File
# Begin Source File

SOURCE=.\include\mangledimport.h
# End Source File
# Begin Source File

SOURCE=.\Include\mangledprofmgmt.h
# End Source File
# Begin Source File

SOURCE=.\include\mangledptadllapi.h
# End Source File
# Begin Source File

SOURCE=.\Include\mangledroamprefs.h
# End Source File
# Begin Source File

SOURCE=.\Include\mangledseldigid.h
# End Source File
# Begin Source File

SOURCE=.\Include\mangledsrchcrit.h
# End Source File
# Begin Source File

SOURCE=.\Include\mangleduiprefs.h
# End Source File
# End Group
# Begin Group "PTAHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Include\certinfo.h
# End Source File
# Begin Source File

SOURCE=.\Include\certstructs.h
# End Source File
# Begin Source File

SOURCE=.\include\ExportP12.h
# End Source File
# Begin Source File

SOURCE=.\include\FindPrimes.h
# End Source File
# Begin Source File

SOURCE=.\Include\langutils.h
# End Source File
# Begin Source File

SOURCE=.\Include\MyUniversalInteger.h
# End Source File
# Begin Source File

SOURCE=.\include\P12Helper.h
# End Source File
# Begin Source File

SOURCE=.\include\pkcs12defines.h
# End Source File
# Begin Source File

SOURCE=.\include\pkcs12errs.h
# End Source File
# Begin Source File

SOURCE=.\include\pkcs12info.h
# End Source File
# Begin Source File

SOURCE=.\include\pkcs12macros.h
# End Source File
# Begin Source File

SOURCE=.\Include\ptacorestructs.h
# End Source File
# Begin Source File

SOURCE=.\Include\ptadefines.h
# End Source File
# Begin Source File

SOURCE=.\Include\PtaEngine.h
# End Source File
# Begin Source File

SOURCE=.\Include\ptaerrs.h
# End Source File
# Begin Source File

SOURCE=.\Include\PtaUI.h
# End Source File
# Begin Source File

SOURCE=.\Include\ptauistructs.h
# End Source File
# Begin Source File

SOURCE=.\Include\utils.h
# End Source File
# Begin Source File

SOURCE=.\Include\virtualsmartcard.h
# End Source File
# Begin Source File

SOURCE=.\Include\vscapi.h
# End Source File
# Begin Source File

SOURCE=.\Include\VSPTA.h
# End Source File
# End Group
# Begin Group "RootsUpdateHeaders"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\roots.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Include\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Include\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\source\bitmap8.bmp
# End Source File
# Begin Source File

SOURCE=.\Resources\registry.bin
# End Source File
# Begin Source File

SOURCE=.\Resources\RootsUpdate.rgs
# End Source File
# Begin Source File

SOURCE=.\Resource\Vspta.bmp
# End Source File
# Begin Source File

SOURCE=.\Resources\VSPTA.BMP
# End Source File
# Begin Source File

SOURCE=.\Resource\VSPTA.rgs
# End Source File
# Begin Source File

SOURCE=.\Resources\Vspta.rgs
# End Source File
# End Group
# End Target
# End Project
# Section Ptav3 : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
# Section Ptav3 : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section

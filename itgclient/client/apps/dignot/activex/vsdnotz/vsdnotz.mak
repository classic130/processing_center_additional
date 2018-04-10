# Microsoft Developer Studio Generated NMAKE File, Based on vsdnotz.dsp
!IF "$(CFG)" == ""
CFG=vsdnotz - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vsdnotz - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vsdnotz - Win32 Debug" && "$(CFG)" != "vsdnotz - Win32 Unicode Debug" && "$(CFG)" != "vsdnotz - Win32 Release MinSize" && "$(CFG)" != "vsdnotz - Win32 Release MinDependency" && "$(CFG)" != "vsdnotz - Win32 Unicode Release MinSize" && "$(CFG)" != "vsdnotz - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsdnotz.mak" CFG="vsdnotz - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vsdnotz - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsdnotz - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsdnotz - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsdnotz - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsdnotz - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsdnotz - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vsdnotz - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\vsdnotz.dll" "$(OUTDIR)\vsdnotz.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DNZUI.obj"
	-@erase "$(INTDIR)\DNZUI.sbr"
	-@erase "$(INTDIR)\notarize.obj"
	-@erase "$(INTDIR)\notarize.sbr"
	-@erase "$(INTDIR)\nzapprefs.obj"
	-@erase "$(INTDIR)\nzapprefs.sbr"
	-@erase "$(INTDIR)\nzcxtmenu.obj"
	-@erase "$(INTDIR)\nzcxtmenu.sbr"
	-@erase "$(INTDIR)\nzdatacc.obj"
	-@erase "$(INTDIR)\nzdatacc.sbr"
	-@erase "$(INTDIR)\nzrecord.obj"
	-@erase "$(INTDIR)\nzrecord.sbr"
	-@erase "$(INTDIR)\nzshlext.obj"
	-@erase "$(INTDIR)\nzshlext.sbr"
	-@erase "$(INTDIR)\nzuiprefs.obj"
	-@erase "$(INTDIR)\nzuiprefs.sbr"
	-@erase "$(INTDIR)\nzuser.obj"
	-@erase "$(INTDIR)\nzuser.sbr"
	-@erase "$(INTDIR)\nzutils.obj"
	-@erase "$(INTDIR)\nzutils.sbr"
	-@erase "$(INTDIR)\shlink.obj"
	-@erase "$(INTDIR)\shlink.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsdnotz.obj"
	-@erase "$(INTDIR)\vsdnotz.pch"
	-@erase "$(INTDIR)\vsdnotz.res"
	-@erase "$(INTDIR)\vsdnotz.sbr"
	-@erase "$(INTDIR)\VSNZ.obj"
	-@erase "$(INTDIR)\VSNZ.sbr"
	-@erase "$(OUTDIR)\vsdnotz.bsc"
	-@erase "$(OUTDIR)\vsdnotz.dll"
	-@erase "$(OUTDIR)\vsdnotz.exp"
	-@erase "$(OUTDIR)\vsdnotz.ilk"
	-@erase "$(OUTDIR)\vsdnotz.lib"
	-@erase "$(OUTDIR)\vsdnotz.pdb"
	-@erase ".\include\nzapprefs.h"
	-@erase ".\include\nzdllapi.h"
	-@erase ".\include\nzuiprefs.h"
	-@erase ".\include\vsdnotz.h"
	-@erase ".\source\nzapprefs_i.c"
	-@erase ".\source\nzdllapi_i.c"
	-@erase ".\source\nzuiprefs_i.c"
	-@erase ".\source\vsdnotz_i.c"
	-@erase ".\vsdnotz.tlb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsdnotz.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsdnotz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DNZUI.sbr" \
	"$(INTDIR)\notarize.sbr" \
	"$(INTDIR)\nzapprefs.sbr" \
	"$(INTDIR)\nzcxtmenu.sbr" \
	"$(INTDIR)\nzdatacc.sbr" \
	"$(INTDIR)\nzrecord.sbr" \
	"$(INTDIR)\nzshlext.sbr" \
	"$(INTDIR)\nzuiprefs.sbr" \
	"$(INTDIR)\nzuser.sbr" \
	"$(INTDIR)\nzutils.sbr" \
	"$(INTDIR)\shlink.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vsdnotz.sbr" \
	"$(INTDIR)\VSNZ.sbr"

"$(OUTDIR)\vsdnotz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS="..\..\..\..\modules\lib\static\debug\bsafelite.lib" "..\..\..\..\..\common\lib\debug\simder.lib" crypt32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib wininet.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\vsdnotz.pdb" /debug /machine:I386 /nodefaultlib:"MSVCRT" /nodefaultlib:"LIBCD" /def:".\vsdnotz.def" /out:"$(OUTDIR)\vsdnotz.dll" /implib:"$(OUTDIR)\vsdnotz.lib" /pdbtype:sept 
DEF_FILE= \
	".\vsdnotz.def"
LINK32_OBJS= \
	"$(INTDIR)\DNZUI.obj" \
	"$(INTDIR)\notarize.obj" \
	"$(INTDIR)\nzapprefs.obj" \
	"$(INTDIR)\nzcxtmenu.obj" \
	"$(INTDIR)\nzdatacc.obj" \
	"$(INTDIR)\nzrecord.obj" \
	"$(INTDIR)\nzshlext.obj" \
	"$(INTDIR)\nzuiprefs.obj" \
	"$(INTDIR)\nzuser.obj" \
	"$(INTDIR)\nzutils.obj" \
	"$(INTDIR)\shlink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsdnotz.obj" \
	"$(INTDIR)\VSNZ.obj" \
	"$(INTDIR)\vsdnotz.res"

"$(OUTDIR)\vsdnotz.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\vsdnotz.dll
InputPath=.\Debug\vsdnotz.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\vsdnotz.dll" ".\include\nzapprefs.h" ".\source\nzapprefs_i.c" ".\include\nzdllapi.h" ".\source\nzdllapi_i.c" ".\include\nzuiprefs.h" ".\source\nzuiprefs_i.c" ".\vsdnotz.tlb" ".\include\vsdnotz.h" ".\source\vsdnotz_i.c" "$(OUTDIR)\vsdnotz.bsc" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DNZUI.obj"
	-@erase "$(INTDIR)\DNZUI.sbr"
	-@erase "$(INTDIR)\notarize.obj"
	-@erase "$(INTDIR)\notarize.sbr"
	-@erase "$(INTDIR)\nzapprefs.obj"
	-@erase "$(INTDIR)\nzapprefs.sbr"
	-@erase "$(INTDIR)\nzcxtmenu.obj"
	-@erase "$(INTDIR)\nzcxtmenu.sbr"
	-@erase "$(INTDIR)\nzdatacc.obj"
	-@erase "$(INTDIR)\nzdatacc.sbr"
	-@erase "$(INTDIR)\nzrecord.obj"
	-@erase "$(INTDIR)\nzrecord.sbr"
	-@erase "$(INTDIR)\nzshlext.obj"
	-@erase "$(INTDIR)\nzshlext.sbr"
	-@erase "$(INTDIR)\nzuiprefs.obj"
	-@erase "$(INTDIR)\nzuiprefs.sbr"
	-@erase "$(INTDIR)\nzuser.obj"
	-@erase "$(INTDIR)\nzuser.sbr"
	-@erase "$(INTDIR)\nzutils.obj"
	-@erase "$(INTDIR)\nzutils.sbr"
	-@erase "$(INTDIR)\shlink.obj"
	-@erase "$(INTDIR)\shlink.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsdnotz.obj"
	-@erase "$(INTDIR)\vsdnotz.pch"
	-@erase "$(INTDIR)\vsdnotz.res"
	-@erase "$(INTDIR)\vsdnotz.sbr"
	-@erase "$(INTDIR)\VSNZ.obj"
	-@erase "$(INTDIR)\VSNZ.sbr"
	-@erase "$(OUTDIR)\vsdnotz.bsc"
	-@erase "$(OUTDIR)\vsdnotz.dll"
	-@erase "$(OUTDIR)\vsdnotz.exp"
	-@erase "$(OUTDIR)\vsdnotz.ilk"
	-@erase "$(OUTDIR)\vsdnotz.lib"
	-@erase "$(OUTDIR)\vsdnotz.pdb"
	-@erase ".\include\nzapprefs.h"
	-@erase ".\include\nzdllapi.h"
	-@erase ".\include\nzuiprefs.h"
	-@erase ".\include\vsdnotz.h"
	-@erase ".\source\nzapprefs_i.c"
	-@erase ".\source\nzdllapi_i.c"
	-@erase ".\source\nzuiprefs_i.c"
	-@erase ".\source\vsdnotz_i.c"
	-@erase ".\vsdnotz.tlb"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsdnotz.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsdnotz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DNZUI.sbr" \
	"$(INTDIR)\notarize.sbr" \
	"$(INTDIR)\nzapprefs.sbr" \
	"$(INTDIR)\nzcxtmenu.sbr" \
	"$(INTDIR)\nzdatacc.sbr" \
	"$(INTDIR)\nzrecord.sbr" \
	"$(INTDIR)\nzshlext.sbr" \
	"$(INTDIR)\nzuiprefs.sbr" \
	"$(INTDIR)\nzuser.sbr" \
	"$(INTDIR)\nzutils.sbr" \
	"$(INTDIR)\shlink.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vsdnotz.sbr" \
	"$(INTDIR)\VSNZ.sbr"

"$(OUTDIR)\vsdnotz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib wininet.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\vsdnotz.pdb" /debug /machine:I386 /def:".\vsdnotz.def" /out:"$(OUTDIR)\vsdnotz.dll" /implib:"$(OUTDIR)\vsdnotz.lib" /pdbtype:sept 
DEF_FILE= \
	".\vsdnotz.def"
LINK32_OBJS= \
	"$(INTDIR)\DNZUI.obj" \
	"$(INTDIR)\notarize.obj" \
	"$(INTDIR)\nzapprefs.obj" \
	"$(INTDIR)\nzcxtmenu.obj" \
	"$(INTDIR)\nzdatacc.obj" \
	"$(INTDIR)\nzrecord.obj" \
	"$(INTDIR)\nzshlext.obj" \
	"$(INTDIR)\nzuiprefs.obj" \
	"$(INTDIR)\nzuser.obj" \
	"$(INTDIR)\nzutils.obj" \
	"$(INTDIR)\shlink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsdnotz.obj" \
	"$(INTDIR)\VSNZ.obj" \
	"$(INTDIR)\vsdnotz.res"

"$(OUTDIR)\vsdnotz.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\vsdnotz.dll
InputPath=.\DebugU\vsdnotz.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\vsdnotz.dll" ".\include\nzapprefs.h" ".\source\nzapprefs_i.c" ".\include\nzdllapi.h" ".\source\nzdllapi_i.c" ".\include\nzuiprefs.h" ".\source\nzuiprefs_i.c" ".\vsdnotz.tlb" ".\include\vsdnotz.h" ".\source\vsdnotz_i.c" "$(OUTDIR)\vsdnotz.bsc" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DNZUI.obj"
	-@erase "$(INTDIR)\DNZUI.sbr"
	-@erase "$(INTDIR)\notarize.obj"
	-@erase "$(INTDIR)\notarize.sbr"
	-@erase "$(INTDIR)\nzapprefs.obj"
	-@erase "$(INTDIR)\nzapprefs.sbr"
	-@erase "$(INTDIR)\nzcxtmenu.obj"
	-@erase "$(INTDIR)\nzcxtmenu.sbr"
	-@erase "$(INTDIR)\nzdatacc.obj"
	-@erase "$(INTDIR)\nzdatacc.sbr"
	-@erase "$(INTDIR)\nzrecord.obj"
	-@erase "$(INTDIR)\nzrecord.sbr"
	-@erase "$(INTDIR)\nzshlext.obj"
	-@erase "$(INTDIR)\nzshlext.sbr"
	-@erase "$(INTDIR)\nzuiprefs.obj"
	-@erase "$(INTDIR)\nzuiprefs.sbr"
	-@erase "$(INTDIR)\nzuser.obj"
	-@erase "$(INTDIR)\nzuser.sbr"
	-@erase "$(INTDIR)\nzutils.obj"
	-@erase "$(INTDIR)\nzutils.sbr"
	-@erase "$(INTDIR)\shlink.obj"
	-@erase "$(INTDIR)\shlink.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsdnotz.obj"
	-@erase "$(INTDIR)\vsdnotz.pch"
	-@erase "$(INTDIR)\vsdnotz.res"
	-@erase "$(INTDIR)\vsdnotz.sbr"
	-@erase "$(INTDIR)\VSNZ.obj"
	-@erase "$(INTDIR)\VSNZ.sbr"
	-@erase "$(OUTDIR)\vsdnotz.bsc"
	-@erase "$(OUTDIR)\vsdnotz.dll"
	-@erase "$(OUTDIR)\vsdnotz.exp"
	-@erase "$(OUTDIR)\vsdnotz.lib"
	-@erase ".\include\nzapprefs.h"
	-@erase ".\include\nzdllapi.h"
	-@erase ".\include\nzuiprefs.h"
	-@erase ".\include\vsdnotz.h"
	-@erase ".\source\nzapprefs_i.c"
	-@erase ".\source\nzdllapi_i.c"
	-@erase ".\source\nzuiprefs_i.c"
	-@erase ".\source\vsdnotz_i.c"
	-@erase ".\vsdnotz.tlb"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsdnotz.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsdnotz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DNZUI.sbr" \
	"$(INTDIR)\notarize.sbr" \
	"$(INTDIR)\nzapprefs.sbr" \
	"$(INTDIR)\nzcxtmenu.sbr" \
	"$(INTDIR)\nzdatacc.sbr" \
	"$(INTDIR)\nzrecord.sbr" \
	"$(INTDIR)\nzshlext.sbr" \
	"$(INTDIR)\nzuiprefs.sbr" \
	"$(INTDIR)\nzuser.sbr" \
	"$(INTDIR)\nzutils.sbr" \
	"$(INTDIR)\shlink.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vsdnotz.sbr" \
	"$(INTDIR)\VSNZ.sbr"

"$(OUTDIR)\vsdnotz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib wininet.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsdnotz.pdb" /machine:I386 /def:".\vsdnotz.def" /out:"$(OUTDIR)\vsdnotz.dll" /implib:"$(OUTDIR)\vsdnotz.lib" 
DEF_FILE= \
	".\vsdnotz.def"
LINK32_OBJS= \
	"$(INTDIR)\DNZUI.obj" \
	"$(INTDIR)\notarize.obj" \
	"$(INTDIR)\nzapprefs.obj" \
	"$(INTDIR)\nzcxtmenu.obj" \
	"$(INTDIR)\nzdatacc.obj" \
	"$(INTDIR)\nzrecord.obj" \
	"$(INTDIR)\nzshlext.obj" \
	"$(INTDIR)\nzuiprefs.obj" \
	"$(INTDIR)\nzuser.obj" \
	"$(INTDIR)\nzutils.obj" \
	"$(INTDIR)\shlink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsdnotz.obj" \
	"$(INTDIR)\VSNZ.obj" \
	"$(INTDIR)\vsdnotz.res"

"$(OUTDIR)\vsdnotz.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\vsdnotz.dll
InputPath=.\ReleaseMinSize\vsdnotz.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\vsdnotz.dll" ".\include\nzapprefs.h" ".\source\nzapprefs_i.c" ".\include\nzdllapi.h" ".\source\nzdllapi_i.c" ".\include\nzuiprefs.h" ".\source\nzuiprefs_i.c" ".\vsdnotz.tlb" ".\include\vsdnotz.h" ".\source\vsdnotz_i.c" "$(OUTDIR)\vsdnotz.bsc" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DNZUI.obj"
	-@erase "$(INTDIR)\DNZUI.sbr"
	-@erase "$(INTDIR)\notarize.obj"
	-@erase "$(INTDIR)\notarize.sbr"
	-@erase "$(INTDIR)\nzapprefs.obj"
	-@erase "$(INTDIR)\nzapprefs.sbr"
	-@erase "$(INTDIR)\nzcxtmenu.obj"
	-@erase "$(INTDIR)\nzcxtmenu.sbr"
	-@erase "$(INTDIR)\nzdatacc.obj"
	-@erase "$(INTDIR)\nzdatacc.sbr"
	-@erase "$(INTDIR)\nzrecord.obj"
	-@erase "$(INTDIR)\nzrecord.sbr"
	-@erase "$(INTDIR)\nzshlext.obj"
	-@erase "$(INTDIR)\nzshlext.sbr"
	-@erase "$(INTDIR)\nzuiprefs.obj"
	-@erase "$(INTDIR)\nzuiprefs.sbr"
	-@erase "$(INTDIR)\nzuser.obj"
	-@erase "$(INTDIR)\nzuser.sbr"
	-@erase "$(INTDIR)\nzutils.obj"
	-@erase "$(INTDIR)\nzutils.sbr"
	-@erase "$(INTDIR)\shlink.obj"
	-@erase "$(INTDIR)\shlink.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsdnotz.obj"
	-@erase "$(INTDIR)\vsdnotz.pch"
	-@erase "$(INTDIR)\vsdnotz.res"
	-@erase "$(INTDIR)\vsdnotz.sbr"
	-@erase "$(INTDIR)\VSNZ.obj"
	-@erase "$(INTDIR)\VSNZ.sbr"
	-@erase "$(OUTDIR)\vsdnotz.bsc"
	-@erase "$(OUTDIR)\vsdnotz.dll"
	-@erase "$(OUTDIR)\vsdnotz.exp"
	-@erase "$(OUTDIR)\vsdnotz.lib"
	-@erase ".\include\nzapprefs.h"
	-@erase ".\include\nzdllapi.h"
	-@erase ".\include\nzuiprefs.h"
	-@erase ".\include\vsdnotz.h"
	-@erase ".\source\nzapprefs_i.c"
	-@erase ".\source\nzdllapi_i.c"
	-@erase ".\source\nzuiprefs_i.c"
	-@erase ".\source\vsdnotz_i.c"
	-@erase ".\vsdnotz.tlb"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsdnotz.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsdnotz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DNZUI.sbr" \
	"$(INTDIR)\notarize.sbr" \
	"$(INTDIR)\nzapprefs.sbr" \
	"$(INTDIR)\nzcxtmenu.sbr" \
	"$(INTDIR)\nzdatacc.sbr" \
	"$(INTDIR)\nzrecord.sbr" \
	"$(INTDIR)\nzshlext.sbr" \
	"$(INTDIR)\nzuiprefs.sbr" \
	"$(INTDIR)\nzuser.sbr" \
	"$(INTDIR)\nzutils.sbr" \
	"$(INTDIR)\shlink.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vsdnotz.sbr" \
	"$(INTDIR)\VSNZ.sbr"

"$(OUTDIR)\vsdnotz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS="..\..\..\..\modules\lib\static\release\bsafelite.lib" "..\..\..\..\..\common\lib\release\simder.lib" kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib wininet.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsdnotz.pdb" /machine:I386 /nodefaultlib:"LIBC" /def:".\vsdnotz.def" /out:"$(OUTDIR)\vsdnotz.dll" /implib:"$(OUTDIR)\vsdnotz.lib" 
DEF_FILE= \
	".\vsdnotz.def"
LINK32_OBJS= \
	"$(INTDIR)\DNZUI.obj" \
	"$(INTDIR)\notarize.obj" \
	"$(INTDIR)\nzapprefs.obj" \
	"$(INTDIR)\nzcxtmenu.obj" \
	"$(INTDIR)\nzdatacc.obj" \
	"$(INTDIR)\nzrecord.obj" \
	"$(INTDIR)\nzshlext.obj" \
	"$(INTDIR)\nzuiprefs.obj" \
	"$(INTDIR)\nzuser.obj" \
	"$(INTDIR)\nzutils.obj" \
	"$(INTDIR)\shlink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsdnotz.obj" \
	"$(INTDIR)\VSNZ.obj" \
	"$(INTDIR)\vsdnotz.res"

"$(OUTDIR)\vsdnotz.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\vsdnotz.dll
InputPath=.\ReleaseMinDependency\vsdnotz.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\vsdnotz.dll" ".\include\nzapprefs.h" ".\source\nzapprefs_i.c" ".\include\nzdllapi.h" ".\source\nzdllapi_i.c" ".\include\nzuiprefs.h" ".\source\nzuiprefs_i.c" ".\vsdnotz.tlb" ".\include\vsdnotz.h" ".\source\vsdnotz_i.c" "$(OUTDIR)\vsdnotz.bsc" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DNZUI.obj"
	-@erase "$(INTDIR)\DNZUI.sbr"
	-@erase "$(INTDIR)\notarize.obj"
	-@erase "$(INTDIR)\notarize.sbr"
	-@erase "$(INTDIR)\nzapprefs.obj"
	-@erase "$(INTDIR)\nzapprefs.sbr"
	-@erase "$(INTDIR)\nzcxtmenu.obj"
	-@erase "$(INTDIR)\nzcxtmenu.sbr"
	-@erase "$(INTDIR)\nzdatacc.obj"
	-@erase "$(INTDIR)\nzdatacc.sbr"
	-@erase "$(INTDIR)\nzrecord.obj"
	-@erase "$(INTDIR)\nzrecord.sbr"
	-@erase "$(INTDIR)\nzshlext.obj"
	-@erase "$(INTDIR)\nzshlext.sbr"
	-@erase "$(INTDIR)\nzuiprefs.obj"
	-@erase "$(INTDIR)\nzuiprefs.sbr"
	-@erase "$(INTDIR)\nzuser.obj"
	-@erase "$(INTDIR)\nzuser.sbr"
	-@erase "$(INTDIR)\nzutils.obj"
	-@erase "$(INTDIR)\nzutils.sbr"
	-@erase "$(INTDIR)\shlink.obj"
	-@erase "$(INTDIR)\shlink.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsdnotz.obj"
	-@erase "$(INTDIR)\vsdnotz.pch"
	-@erase "$(INTDIR)\vsdnotz.res"
	-@erase "$(INTDIR)\vsdnotz.sbr"
	-@erase "$(INTDIR)\VSNZ.obj"
	-@erase "$(INTDIR)\VSNZ.sbr"
	-@erase "$(OUTDIR)\vsdnotz.bsc"
	-@erase "$(OUTDIR)\vsdnotz.dll"
	-@erase "$(OUTDIR)\vsdnotz.exp"
	-@erase "$(OUTDIR)\vsdnotz.lib"
	-@erase ".\include\nzapprefs.h"
	-@erase ".\include\nzdllapi.h"
	-@erase ".\include\nzuiprefs.h"
	-@erase ".\include\vsdnotz.h"
	-@erase ".\source\nzapprefs_i.c"
	-@erase ".\source\nzdllapi_i.c"
	-@erase ".\source\nzuiprefs_i.c"
	-@erase ".\source\vsdnotz_i.c"
	-@erase ".\vsdnotz.tlb"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsdnotz.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsdnotz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DNZUI.sbr" \
	"$(INTDIR)\notarize.sbr" \
	"$(INTDIR)\nzapprefs.sbr" \
	"$(INTDIR)\nzcxtmenu.sbr" \
	"$(INTDIR)\nzdatacc.sbr" \
	"$(INTDIR)\nzrecord.sbr" \
	"$(INTDIR)\nzshlext.sbr" \
	"$(INTDIR)\nzuiprefs.sbr" \
	"$(INTDIR)\nzuser.sbr" \
	"$(INTDIR)\nzutils.sbr" \
	"$(INTDIR)\shlink.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vsdnotz.sbr" \
	"$(INTDIR)\VSNZ.sbr"

"$(OUTDIR)\vsdnotz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib wininet.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsdnotz.pdb" /machine:I386 /def:".\vsdnotz.def" /out:"$(OUTDIR)\vsdnotz.dll" /implib:"$(OUTDIR)\vsdnotz.lib" 
DEF_FILE= \
	".\vsdnotz.def"
LINK32_OBJS= \
	"$(INTDIR)\DNZUI.obj" \
	"$(INTDIR)\notarize.obj" \
	"$(INTDIR)\nzapprefs.obj" \
	"$(INTDIR)\nzcxtmenu.obj" \
	"$(INTDIR)\nzdatacc.obj" \
	"$(INTDIR)\nzrecord.obj" \
	"$(INTDIR)\nzshlext.obj" \
	"$(INTDIR)\nzuiprefs.obj" \
	"$(INTDIR)\nzuser.obj" \
	"$(INTDIR)\nzutils.obj" \
	"$(INTDIR)\shlink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsdnotz.obj" \
	"$(INTDIR)\VSNZ.obj" \
	"$(INTDIR)\vsdnotz.res"

"$(OUTDIR)\vsdnotz.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\vsdnotz.dll
InputPath=.\ReleaseUMinSize\vsdnotz.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\vsdnotz.dll" ".\include\nzapprefs.h" ".\source\nzapprefs_i.c" ".\include\nzdllapi.h" ".\source\nzdllapi_i.c" ".\include\nzuiprefs.h" ".\source\nzuiprefs_i.c" ".\vsdnotz.tlb" ".\include\vsdnotz.h" ".\source\vsdnotz_i.c" "$(OUTDIR)\vsdnotz.bsc" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\DNZUI.obj"
	-@erase "$(INTDIR)\DNZUI.sbr"
	-@erase "$(INTDIR)\notarize.obj"
	-@erase "$(INTDIR)\notarize.sbr"
	-@erase "$(INTDIR)\nzapprefs.obj"
	-@erase "$(INTDIR)\nzapprefs.sbr"
	-@erase "$(INTDIR)\nzcxtmenu.obj"
	-@erase "$(INTDIR)\nzcxtmenu.sbr"
	-@erase "$(INTDIR)\nzdatacc.obj"
	-@erase "$(INTDIR)\nzdatacc.sbr"
	-@erase "$(INTDIR)\nzrecord.obj"
	-@erase "$(INTDIR)\nzrecord.sbr"
	-@erase "$(INTDIR)\nzshlext.obj"
	-@erase "$(INTDIR)\nzshlext.sbr"
	-@erase "$(INTDIR)\nzuiprefs.obj"
	-@erase "$(INTDIR)\nzuiprefs.sbr"
	-@erase "$(INTDIR)\nzuser.obj"
	-@erase "$(INTDIR)\nzuser.sbr"
	-@erase "$(INTDIR)\nzutils.obj"
	-@erase "$(INTDIR)\nzutils.sbr"
	-@erase "$(INTDIR)\shlink.obj"
	-@erase "$(INTDIR)\shlink.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsdnotz.obj"
	-@erase "$(INTDIR)\vsdnotz.pch"
	-@erase "$(INTDIR)\vsdnotz.res"
	-@erase "$(INTDIR)\vsdnotz.sbr"
	-@erase "$(INTDIR)\VSNZ.obj"
	-@erase "$(INTDIR)\VSNZ.sbr"
	-@erase "$(OUTDIR)\vsdnotz.bsc"
	-@erase "$(OUTDIR)\vsdnotz.dll"
	-@erase "$(OUTDIR)\vsdnotz.exp"
	-@erase "$(OUTDIR)\vsdnotz.lib"
	-@erase ".\include\nzapprefs.h"
	-@erase ".\include\nzdllapi.h"
	-@erase ".\include\nzuiprefs.h"
	-@erase ".\include\vsdnotz.h"
	-@erase ".\source\nzapprefs_i.c"
	-@erase ".\source\nzdllapi_i.c"
	-@erase ".\source\nzuiprefs_i.c"
	-@erase ".\source\vsdnotz_i.c"
	-@erase ".\vsdnotz.tlb"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsdnotz.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsdnotz.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DNZUI.sbr" \
	"$(INTDIR)\notarize.sbr" \
	"$(INTDIR)\nzapprefs.sbr" \
	"$(INTDIR)\nzcxtmenu.sbr" \
	"$(INTDIR)\nzdatacc.sbr" \
	"$(INTDIR)\nzrecord.sbr" \
	"$(INTDIR)\nzshlext.sbr" \
	"$(INTDIR)\nzuiprefs.sbr" \
	"$(INTDIR)\nzuser.sbr" \
	"$(INTDIR)\nzutils.sbr" \
	"$(INTDIR)\shlink.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\vsdnotz.sbr" \
	"$(INTDIR)\VSNZ.sbr"

"$(OUTDIR)\vsdnotz.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib wininet.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsdnotz.pdb" /machine:I386 /def:".\vsdnotz.def" /out:"$(OUTDIR)\vsdnotz.dll" /implib:"$(OUTDIR)\vsdnotz.lib" 
DEF_FILE= \
	".\vsdnotz.def"
LINK32_OBJS= \
	"$(INTDIR)\DNZUI.obj" \
	"$(INTDIR)\notarize.obj" \
	"$(INTDIR)\nzapprefs.obj" \
	"$(INTDIR)\nzcxtmenu.obj" \
	"$(INTDIR)\nzdatacc.obj" \
	"$(INTDIR)\nzrecord.obj" \
	"$(INTDIR)\nzshlext.obj" \
	"$(INTDIR)\nzuiprefs.obj" \
	"$(INTDIR)\nzuser.obj" \
	"$(INTDIR)\nzutils.obj" \
	"$(INTDIR)\shlink.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsdnotz.obj" \
	"$(INTDIR)\VSNZ.obj" \
	"$(INTDIR)\vsdnotz.res"

"$(OUTDIR)\vsdnotz.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\vsdnotz.dll
InputPath=.\ReleaseUMinDependency\vsdnotz.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("vsdnotz.dep")
!INCLUDE "vsdnotz.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsdnotz.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vsdnotz - Win32 Debug" || "$(CFG)" == "vsdnotz - Win32 Unicode Debug" || "$(CFG)" == "vsdnotz - Win32 Release MinSize" || "$(CFG)" == "vsdnotz - Win32 Release MinDependency" || "$(CFG)" == "vsdnotz - Win32 Unicode Release MinSize" || "$(CFG)" == "vsdnotz - Win32 Unicode Release MinDependency"
SOURCE=.\source\nzapprefs.idl
MTL_SWITCHES=/h "include/nzapprefs.h" /iid "source/nzapprefs_i.c" /Oicf 

".\include\nzapprefs.h"	".\source\nzapprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\source\nzdllapi.idl
MTL_SWITCHES=/h "include/nzdllapi.h" /iid "source/nzdllapi_i.c" /Oicf 

".\include\nzdllapi.h"	".\source\nzdllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\source\nzuiprefs.idl
MTL_SWITCHES=/h "include/nzuiprefs.h" /iid "source/nzuiprefs_i.c" /Oicf 

".\include\nzuiprefs.h"	".\source\nzuiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\source\vsdnotz.idl
MTL_SWITCHES=/tlb "vsdnotz.tlb" /h "include/vsdnotz.h" /iid "source/vsdnotz_i.c" /Oicf 

".\vsdnotz.tlb"	".\include\vsdnotz.h"	".\source\vsdnotz_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\source\DNZUI.cpp

"$(INTDIR)\DNZUI.obj"	"$(INTDIR)\DNZUI.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\notarize.cpp

"$(INTDIR)\notarize.obj"	"$(INTDIR)\notarize.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzapprefs.cpp

"$(INTDIR)\nzapprefs.obj"	"$(INTDIR)\nzapprefs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch" ".\include\vsdnotz.h" ".\include\nzdllapi.h" ".\include\nzuiprefs.h" ".\include\nzapprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzcxtmenu.cpp

"$(INTDIR)\nzcxtmenu.obj"	"$(INTDIR)\nzcxtmenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch" ".\include\vsdnotz.h" ".\include\nzdllapi.h" ".\include\nzuiprefs.h" ".\include\nzapprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzdatacc.cpp

"$(INTDIR)\nzdatacc.obj"	"$(INTDIR)\nzdatacc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzrecord.cpp

"$(INTDIR)\nzrecord.obj"	"$(INTDIR)\nzrecord.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzshlext.cpp

"$(INTDIR)\nzshlext.obj"	"$(INTDIR)\nzshlext.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch" ".\include\vsdnotz.h" ".\include\nzdllapi.h" ".\include\nzuiprefs.h" ".\include\nzapprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzuiprefs.cpp

"$(INTDIR)\nzuiprefs.obj"	"$(INTDIR)\nzuiprefs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch" ".\include\vsdnotz.h" ".\include\nzdllapi.h" ".\include\nzuiprefs.h" ".\include\nzapprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzuser.cpp

"$(INTDIR)\nzuser.obj"	"$(INTDIR)\nzuser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\nzutils.cpp

"$(INTDIR)\nzutils.obj"	"$(INTDIR)\nzutils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\shlink.cpp

"$(INTDIR)\shlink.obj"	"$(INTDIR)\shlink.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\StdAfx.cpp

!IF  "$(CFG)" == "vsdnotz - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "_DEBUG" /D "_MBCS" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsdnotz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "_DEBUG" /D "_UNICODE" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsdnotz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsdnotz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsdnotz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsdnotz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\..\..\..\modules\protectedstorage\include" /I "include" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\modules\bsafelite\include" /I "..\..\..\..\..\common\simder\include" /D "NDEBUG" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_NO_UUIDOF" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsdnotz.pch" /Yc /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsdnotz.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\source\vsdnotz.cpp

"$(INTDIR)\vsdnotz.obj"	"$(INTDIR)\vsdnotz.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch" ".\include\vsdnotz.h" ".\source\vsdnotz_i.c" ".\include\nzdllapi.h" ".\include\nzuiprefs.h" ".\include\nzapprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\vsdnotz.rc

!IF  "$(CFG)" == "vsdnotz - Win32 Debug"


"$(INTDIR)\vsdnotz.res" : $(SOURCE) "$(INTDIR)" ".\vsdnotz.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsdnotz.res" /i "source" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Debug"


"$(INTDIR)\vsdnotz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsdnotz.res" /i "source" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Release MinSize"


"$(INTDIR)\vsdnotz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsdnotz.res" /i "source" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Release MinDependency"


"$(INTDIR)\vsdnotz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsdnotz.res" /i "source" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Release MinSize"


"$(INTDIR)\vsdnotz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsdnotz.res" /i "source" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsdnotz - Win32 Unicode Release MinDependency"


"$(INTDIR)\vsdnotz.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsdnotz.res" /i "source" /d "NDEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\source\VSNZ.cpp

"$(INTDIR)\VSNZ.obj"	"$(INTDIR)\VSNZ.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsdnotz.pch" ".\include\vsdnotz.h" ".\source\nzdllapi_i.c" ".\source\nzuiprefs_i.c" ".\include\nzdllapi.h" ".\include\nzuiprefs.h" ".\source\nzapprefs_i.c" ".\include\nzapprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


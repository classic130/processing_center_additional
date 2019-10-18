# Microsoft Developer Studio Generated NMAKE File, Based on ConfigChk.dsp
!IF "$(CFG)" == ""
CFG=ConfigChk - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ConfigChk - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ConfigChk - Win32 Debug" && "$(CFG)" != "ConfigChk - Win32 Unicode Debug" && "$(CFG)" != "ConfigChk - Win32 Release MinSize" && "$(CFG)" != "ConfigChk - Win32 Release MinDependency" && "$(CFG)" != "ConfigChk - Win32 Unicode Release MinSize" && "$(CFG)" != "ConfigChk - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ConfigChk.mak" CFG="ConfigChk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ConfigChk - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConfigChk - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConfigChk - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConfigChk - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConfigChk - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ConfigChk - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ConfigChk - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VSCnfChk.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ConfigChk.obj"
	-@erase "$(INTDIR)\ConfigChk.pch"
	-@erase "$(INTDIR)\ConfigChk.res"
	-@erase "$(INTDIR)\ConfigChkr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\VSCnfChk.dll"
	-@erase "$(OUTDIR)\VSCnfChk.exp"
	-@erase "$(OUTDIR)\VSCnfChk.ilk"
	-@erase "$(OUTDIR)\VSCnfChk.lib"
	-@erase "$(OUTDIR)\VSCnfChk.pdb"
	-@erase ".\ConfigChk.h"
	-@erase ".\ConfigChk.tlb"
	-@erase ".\ConfigChk_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ConfigChk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ConfigChk.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ConfigChk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\VSCnfChk.pdb" /debug /machine:I386 /def:".\ConfigChk.def" /out:"$(OUTDIR)\VSCnfChk.dll" /implib:"$(OUTDIR)\VSCnfChk.lib" /pdbtype:sept 
DEF_FILE= \
	".\ConfigChk.def"
LINK32_OBJS= \
	"$(INTDIR)\ConfigChk.obj" \
	"$(INTDIR)\ConfigChkr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ConfigChk.res"

"$(OUTDIR)\VSCnfChk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\VSCnfChk.dll
InputPath=.\Debug\VSCnfChk.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\VSCnfChk.dll" ".\Debug\regsvr32.trg"
   if not exist "..\..\lib\dynamic\debug" md "..\..\lib\dynamic\debug"
	copy debug\vscnfchk.dll "..\..\lib\dynamic\debug"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\ConfigChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ConfigChk.obj"
	-@erase "$(INTDIR)\ConfigChk.pch"
	-@erase "$(INTDIR)\ConfigChk.res"
	-@erase "$(INTDIR)\ConfigChkr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ConfigChk.dll"
	-@erase "$(OUTDIR)\ConfigChk.exp"
	-@erase "$(OUTDIR)\ConfigChk.ilk"
	-@erase "$(OUTDIR)\ConfigChk.lib"
	-@erase "$(OUTDIR)\ConfigChk.pdb"
	-@erase ".\ConfigChk.h"
	-@erase ".\ConfigChk.tlb"
	-@erase ".\ConfigChk_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ConfigChk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ConfigChk.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ConfigChk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ConfigChk.pdb" /debug /machine:I386 /def:".\ConfigChk.def" /out:"$(OUTDIR)\ConfigChk.dll" /implib:"$(OUTDIR)\ConfigChk.lib" /pdbtype:sept 
DEF_FILE= \
	".\ConfigChk.def"
LINK32_OBJS= \
	"$(INTDIR)\ConfigChk.obj" \
	"$(INTDIR)\ConfigChkr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ConfigChk.res"

"$(OUTDIR)\ConfigChk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\ConfigChk.dll
InputPath=.\DebugU\ConfigChk.dll
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
	
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ConfigChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\DebugU\regsvr32.trg"
   if not exist "..\..\bin\debug" md "..\..\bin\debug"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ConfigChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ConfigChk.obj"
	-@erase "$(INTDIR)\ConfigChk.pch"
	-@erase "$(INTDIR)\ConfigChk.res"
	-@erase "$(INTDIR)\ConfigChkr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ConfigChk.dll"
	-@erase "$(OUTDIR)\ConfigChk.exp"
	-@erase "$(OUTDIR)\ConfigChk.lib"
	-@erase ".\ConfigChk.h"
	-@erase ".\ConfigChk.tlb"
	-@erase ".\ConfigChk_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ConfigChk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ConfigChk.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ConfigChk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ConfigChk.pdb" /machine:I386 /def:".\ConfigChk.def" /out:"$(OUTDIR)\ConfigChk.dll" /implib:"$(OUTDIR)\ConfigChk.lib" 
DEF_FILE= \
	".\ConfigChk.def"
LINK32_OBJS= \
	"$(INTDIR)\ConfigChk.obj" \
	"$(INTDIR)\ConfigChkr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ConfigChk.res"

"$(OUTDIR)\ConfigChk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\ConfigChk.dll
InputPath=.\ReleaseMinSize\ConfigChk.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\VSCnfChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ConfigChk.obj"
	-@erase "$(INTDIR)\ConfigChk.pch"
	-@erase "$(INTDIR)\ConfigChk.res"
	-@erase "$(INTDIR)\ConfigChkr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\VSCnfChk.dll"
	-@erase "$(OUTDIR)\VSCnfChk.exp"
	-@erase "$(OUTDIR)\VSCnfChk.lib"
	-@erase ".\ConfigChk.h"
	-@erase ".\ConfigChk.tlb"
	-@erase ".\ConfigChk_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "MSG_BOX" /Fp"$(INTDIR)\ConfigChk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ConfigChk.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ConfigChk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VSCnfChk.pdb" /machine:I386 /def:".\ConfigChk.def" /out:"$(OUTDIR)\VSCnfChk.dll" /implib:"$(OUTDIR)\VSCnfChk.lib" 
DEF_FILE= \
	".\ConfigChk.def"
LINK32_OBJS= \
	"$(INTDIR)\ConfigChk.obj" \
	"$(INTDIR)\ConfigChkr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ConfigChk.res"

"$(OUTDIR)\VSCnfChk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VSCnfChk.dll
InputPath=.\ReleaseMinDependency\VSCnfChk.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\VSCnfChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\ReleaseMinDependency\regsvr32.trg"
   if not exist "..\..\lib\dynamic\release" md "..\..\lib\dynamic\release"
	copy ReleaseMinDependency\vscnfchk.dll "..\..\lib\dynamic\release"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\ConfigChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ConfigChk.obj"
	-@erase "$(INTDIR)\ConfigChk.pch"
	-@erase "$(INTDIR)\ConfigChk.res"
	-@erase "$(INTDIR)\ConfigChkr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ConfigChk.dll"
	-@erase "$(OUTDIR)\ConfigChk.exp"
	-@erase "$(OUTDIR)\ConfigChk.lib"
	-@erase ".\ConfigChk.h"
	-@erase ".\ConfigChk.tlb"
	-@erase ".\ConfigChk_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ConfigChk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ConfigChk.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ConfigChk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ConfigChk.pdb" /machine:I386 /def:".\ConfigChk.def" /out:"$(OUTDIR)\ConfigChk.dll" /implib:"$(OUTDIR)\ConfigChk.lib" 
DEF_FILE= \
	".\ConfigChk.def"
LINK32_OBJS= \
	"$(INTDIR)\ConfigChk.obj" \
	"$(INTDIR)\ConfigChkr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ConfigChk.res"

"$(OUTDIR)\ConfigChk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\ConfigChk.dll
InputPath=.\ReleaseUMinSize\ConfigChk.dll
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
	

!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\ConfigChk.dll" ".\ConfigChk.tlb" ".\ConfigChk.h" ".\ConfigChk_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ConfigChk.obj"
	-@erase "$(INTDIR)\ConfigChk.pch"
	-@erase "$(INTDIR)\ConfigChk.res"
	-@erase "$(INTDIR)\ConfigChkr.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ConfigChk.dll"
	-@erase "$(OUTDIR)\ConfigChk.exp"
	-@erase "$(OUTDIR)\ConfigChk.lib"
	-@erase ".\ConfigChk.h"
	-@erase ".\ConfigChk.tlb"
	-@erase ".\ConfigChk_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ConfigChk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ConfigChk.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ConfigChk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ConfigChk.pdb" /machine:I386 /def:".\ConfigChk.def" /out:"$(OUTDIR)\ConfigChk.dll" /implib:"$(OUTDIR)\ConfigChk.lib" 
DEF_FILE= \
	".\ConfigChk.def"
LINK32_OBJS= \
	"$(INTDIR)\ConfigChk.obj" \
	"$(INTDIR)\ConfigChkr.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ConfigChk.res"

"$(OUTDIR)\ConfigChk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\ConfigChk.dll
InputPath=.\ReleaseUMinDependency\ConfigChk.dll
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
!IF EXISTS("ConfigChk.dep")
!INCLUDE "ConfigChk.dep"
!ELSE 
!MESSAGE Warning: cannot find "ConfigChk.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ConfigChk - Win32 Debug" || "$(CFG)" == "ConfigChk - Win32 Unicode Debug" || "$(CFG)" == "ConfigChk - Win32 Release MinSize" || "$(CFG)" == "ConfigChk - Win32 Release MinDependency" || "$(CFG)" == "ConfigChk - Win32 Unicode Release MinSize" || "$(CFG)" == "ConfigChk - Win32 Unicode Release MinDependency"
SOURCE=.\ConfigChk.cpp

"$(INTDIR)\ConfigChk.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ConfigChk.pch" ".\ConfigChk.h" ".\ConfigChk_i.c"


SOURCE=.\ConfigChk.idl
MTL_SWITCHES=/tlb ".\ConfigChk.tlb" /h "ConfigChk.h" /iid "ConfigChk_i.c" /Oicf 

".\ConfigChk.tlb"	".\ConfigChk.h"	".\ConfigChk_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\ConfigChk.rc

"$(INTDIR)\ConfigChk.res" : $(SOURCE) "$(INTDIR)" ".\ConfigChk.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ConfigChkr.cpp

"$(INTDIR)\ConfigChkr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ConfigChk.pch" ".\ConfigChk.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ConfigChk - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Fp"$(INTDIR)\ConfigChk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ConfigChk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\ConfigChk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ConfigChk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ConfigChk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ConfigChk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "MSG_BOX" /Fp"$(INTDIR)\ConfigChk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ConfigChk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ConfigChk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ConfigChk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ConfigChk - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\ConfigChk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ConfigChk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


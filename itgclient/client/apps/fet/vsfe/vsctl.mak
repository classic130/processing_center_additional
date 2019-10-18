# Microsoft Developer Studio Generated NMAKE File, Based on vsctl.dsp
!IF "$(CFG)" == ""
CFG=vsctl - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vsctl - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vsctl - Win32 Debug" && "$(CFG)" != "vsctl - Win32 Unicode Debug" && "$(CFG)" != "vsctl - Win32 Release MinSize" && "$(CFG)" != "vsctl - Win32 Release MinDependency" && "$(CFG)" != "vsctl - Win32 Unicode Release MinSize" && "$(CFG)" != "vsctl - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
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

!IF  "$(CFG)" == "vsctl - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\vsfe.dll" "$(OUTDIR)\vsctl.bsc"


CLEAN :
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\certmgmt.sbr"
	-@erase "$(INTDIR)\ClsFact.obj"
	-@erase "$(INTDIR)\ClsFact.sbr"
	-@erase "$(INTDIR)\ContMenu.obj"
	-@erase "$(INTDIR)\ContMenu.sbr"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\cryptsup.sbr"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DataObj.sbr"
	-@erase "$(INTDIR)\dlgprocs.obj"
	-@erase "$(INTDIR)\dlgprocs.sbr"
	-@erase "$(INTDIR)\DropSrc.obj"
	-@erase "$(INTDIR)\DropSrc.sbr"
	-@erase "$(INTDIR)\Droptgt.obj"
	-@erase "$(INTDIR)\Droptgt.sbr"
	-@erase "$(INTDIR)\encdeclist.obj"
	-@erase "$(INTDIR)\encdeclist.sbr"
	-@erase "$(INTDIR)\Enumidl.obj"
	-@erase "$(INTDIR)\Enumidl.sbr"
	-@erase "$(INTDIR)\ExtrIcon.obj"
	-@erase "$(INTDIR)\ExtrIcon.sbr"
	-@erase "$(INTDIR)\PidlMgr.obj"
	-@erase "$(INTDIR)\PidlMgr.sbr"
	-@erase "$(INTDIR)\policysup.obj"
	-@erase "$(INTDIR)\policysup.sbr"
	-@erase "$(INTDIR)\safedel.obj"
	-@erase "$(INTDIR)\safedel.sbr"
	-@erase "$(INTDIR)\ShlFldr.obj"
	-@erase "$(INTDIR)\ShlFldr.sbr"
	-@erase "$(INTDIR)\ShlView.obj"
	-@erase "$(INTDIR)\ShlView.sbr"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\slist.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Viewlist.obj"
	-@erase "$(INTDIR)\Viewlist.sbr"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vscontainer.sbr"
	-@erase "$(INTDIR)\vsctl.obj"
	-@erase "$(INTDIR)\vsctl.pch"
	-@erase "$(INTDIR)\vsctl.res"
	-@erase "$(INTDIR)\vsctl.sbr"
	-@erase "$(INTDIR)\vsctrl.obj"
	-@erase "$(INTDIR)\vsctrl.sbr"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp.sbr"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vsnvp_file.sbr"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmsp.sbr"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspmutil.sbr"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(INTDIR)\vspolicyfile.sbr"
	-@erase "$(INTDIR)\vssafe.obj"
	-@erase "$(INTDIR)\vssafe.sbr"
	-@erase "$(OUTDIR)\vsctl.bsc"
	-@erase "$(OUTDIR)\vsfe.dll"
	-@erase "$(OUTDIR)\vsfe.exp"
	-@erase "$(OUTDIR)\vsfe.ilk"
	-@erase "$(OUTDIR)\vsfe.lib"
	-@erase "$(OUTDIR)\vsfe.map"
	-@erase "$(OUTDIR)\vsfe.pdb"
	-@erase ".\vsctl.h"
	-@erase ".\vsctl.tlb"
	-@erase ".\vsctl_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsctl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsctl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\certmgmt.sbr" \
	"$(INTDIR)\ClsFact.sbr" \
	"$(INTDIR)\ContMenu.sbr" \
	"$(INTDIR)\cryptsup.sbr" \
	"$(INTDIR)\DataObj.sbr" \
	"$(INTDIR)\dlgprocs.sbr" \
	"$(INTDIR)\DropSrc.sbr" \
	"$(INTDIR)\Droptgt.sbr" \
	"$(INTDIR)\encdeclist.sbr" \
	"$(INTDIR)\Enumidl.sbr" \
	"$(INTDIR)\ExtrIcon.sbr" \
	"$(INTDIR)\PidlMgr.sbr" \
	"$(INTDIR)\policysup.sbr" \
	"$(INTDIR)\safedel.sbr" \
	"$(INTDIR)\ShlFldr.sbr" \
	"$(INTDIR)\ShlView.sbr" \
	"$(INTDIR)\slist.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Viewlist.sbr" \
	"$(INTDIR)\vscontainer.sbr" \
	"$(INTDIR)\vsctl.sbr" \
	"$(INTDIR)\vsctrl.sbr" \
	"$(INTDIR)\vsnvp.sbr" \
	"$(INTDIR)\vsnvp_file.sbr" \
	"$(INTDIR)\vspmsp.sbr" \
	"$(INTDIR)\vspmutil.sbr" \
	"$(INTDIR)\vspolicyfile.sbr" \
	"$(INTDIR)\vssafe.sbr"

"$(OUTDIR)\vsctl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\vsfe.pdb" /map:"$(INTDIR)\vsfe.map" /debug /machine:I386 /def:".\vsctl.def" /out:"$(OUTDIR)\vsfe.dll" /implib:"$(OUTDIR)\vsfe.lib" /pdbtype:sept 
DEF_FILE= \
	".\vsctl.def"
LINK32_OBJS= \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\ClsFact.obj" \
	"$(INTDIR)\ContMenu.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\dlgprocs.obj" \
	"$(INTDIR)\DropSrc.obj" \
	"$(INTDIR)\Droptgt.obj" \
	"$(INTDIR)\encdeclist.obj" \
	"$(INTDIR)\Enumidl.obj" \
	"$(INTDIR)\ExtrIcon.obj" \
	"$(INTDIR)\PidlMgr.obj" \
	"$(INTDIR)\policysup.obj" \
	"$(INTDIR)\safedel.obj" \
	"$(INTDIR)\ShlFldr.obj" \
	"$(INTDIR)\ShlView.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Viewlist.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsctl.obj" \
	"$(INTDIR)\vsctrl.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj" \
	"$(INTDIR)\vssafe.obj" \
	"$(INTDIR)\vsctl.res"

"$(OUTDIR)\vsfe.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU

ALL : ".\vsfectl" ".\vsctl.tlb" ".\vsctl.h" ".\vsctl_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\ClsFact.obj"
	-@erase "$(INTDIR)\ContMenu.obj"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\dlgprocs.obj"
	-@erase "$(INTDIR)\DropSrc.obj"
	-@erase "$(INTDIR)\Droptgt.obj"
	-@erase "$(INTDIR)\encdeclist.obj"
	-@erase "$(INTDIR)\Enumidl.obj"
	-@erase "$(INTDIR)\ExtrIcon.obj"
	-@erase "$(INTDIR)\PidlMgr.obj"
	-@erase "$(INTDIR)\policysup.obj"
	-@erase "$(INTDIR)\safedel.obj"
	-@erase "$(INTDIR)\ShlFldr.obj"
	-@erase "$(INTDIR)\ShlView.obj"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Viewlist.obj"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vsctl.obj"
	-@erase "$(INTDIR)\vsctl.pch"
	-@erase "$(INTDIR)\vsctl.res"
	-@erase "$(INTDIR)\vsctrl.obj"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(INTDIR)\vssafe.obj"
	-@erase "$(OUTDIR)\vsfectl.exp"
	-@erase "$(OUTDIR)\vsfectl.lib"
	-@erase "$(OUTDIR)\vsfectl.pdb"
	-@erase ".\vsctl.h"
	-@erase ".\vsctl.tlb"
	-@erase ".\vsctl_i.c"
	-@erase ".\vsfectl"
	-@erase ".\vsfectl.ilk"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\vsctl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsctl.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsctl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\vsfectl.pdb" /debug /machine:I386 /def:".\vsctl.def" /out:"vsfectl" /implib:"$(OUTDIR)\vsfectl.lib" /pdbtype:sept 
DEF_FILE= \
	".\vsctl.def"
LINK32_OBJS= \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\ClsFact.obj" \
	"$(INTDIR)\ContMenu.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\dlgprocs.obj" \
	"$(INTDIR)\DropSrc.obj" \
	"$(INTDIR)\Droptgt.obj" \
	"$(INTDIR)\encdeclist.obj" \
	"$(INTDIR)\Enumidl.obj" \
	"$(INTDIR)\ExtrIcon.obj" \
	"$(INTDIR)\PidlMgr.obj" \
	"$(INTDIR)\policysup.obj" \
	"$(INTDIR)\safedel.obj" \
	"$(INTDIR)\ShlFldr.obj" \
	"$(INTDIR)\ShlView.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Viewlist.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsctl.obj" \
	"$(INTDIR)\vsctrl.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj" \
	"$(INTDIR)\vssafe.obj" \
	"$(INTDIR)\vsctl.res"

".\vsfectl" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\vsfectl
InputPath=.\vsfectl
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
	

!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize

ALL : ".\vsfectl" ".\vsctl.tlb" ".\vsctl.h" ".\vsctl_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\ClsFact.obj"
	-@erase "$(INTDIR)\ContMenu.obj"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\dlgprocs.obj"
	-@erase "$(INTDIR)\DropSrc.obj"
	-@erase "$(INTDIR)\Droptgt.obj"
	-@erase "$(INTDIR)\encdeclist.obj"
	-@erase "$(INTDIR)\Enumidl.obj"
	-@erase "$(INTDIR)\ExtrIcon.obj"
	-@erase "$(INTDIR)\PidlMgr.obj"
	-@erase "$(INTDIR)\policysup.obj"
	-@erase "$(INTDIR)\safedel.obj"
	-@erase "$(INTDIR)\ShlFldr.obj"
	-@erase "$(INTDIR)\ShlView.obj"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Viewlist.obj"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vsctl.obj"
	-@erase "$(INTDIR)\vsctl.pch"
	-@erase "$(INTDIR)\vsctl.res"
	-@erase "$(INTDIR)\vsctrl.obj"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(INTDIR)\vssafe.obj"
	-@erase "$(OUTDIR)\vsfectl.exp"
	-@erase "$(OUTDIR)\vsfectl.lib"
	-@erase ".\vsctl.h"
	-@erase ".\vsctl.tlb"
	-@erase ".\vsctl_i.c"
	-@erase ".\vsfectl"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\vsctl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsctl.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsctl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsfectl.pdb" /machine:I386 /def:".\vsctl.def" /out:"vsfectl" /implib:"$(OUTDIR)\vsfectl.lib" 
DEF_FILE= \
	".\vsctl.def"
LINK32_OBJS= \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\ClsFact.obj" \
	"$(INTDIR)\ContMenu.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\dlgprocs.obj" \
	"$(INTDIR)\DropSrc.obj" \
	"$(INTDIR)\Droptgt.obj" \
	"$(INTDIR)\encdeclist.obj" \
	"$(INTDIR)\Enumidl.obj" \
	"$(INTDIR)\ExtrIcon.obj" \
	"$(INTDIR)\PidlMgr.obj" \
	"$(INTDIR)\policysup.obj" \
	"$(INTDIR)\safedel.obj" \
	"$(INTDIR)\ShlFldr.obj" \
	"$(INTDIR)\ShlView.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Viewlist.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsctl.obj" \
	"$(INTDIR)\vsctrl.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj" \
	"$(INTDIR)\vssafe.obj" \
	"$(INTDIR)\vsctl.res"

".\vsfectl" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\vsfectl
InputPath=.\vsfectl
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\vsfe.dll" "$(OUTDIR)\vsctl.bsc"


CLEAN :
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\certmgmt.sbr"
	-@erase "$(INTDIR)\ClsFact.obj"
	-@erase "$(INTDIR)\ClsFact.sbr"
	-@erase "$(INTDIR)\ContMenu.obj"
	-@erase "$(INTDIR)\ContMenu.sbr"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\cryptsup.sbr"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\DataObj.sbr"
	-@erase "$(INTDIR)\dlgprocs.obj"
	-@erase "$(INTDIR)\dlgprocs.sbr"
	-@erase "$(INTDIR)\DropSrc.obj"
	-@erase "$(INTDIR)\DropSrc.sbr"
	-@erase "$(INTDIR)\Droptgt.obj"
	-@erase "$(INTDIR)\Droptgt.sbr"
	-@erase "$(INTDIR)\encdeclist.obj"
	-@erase "$(INTDIR)\encdeclist.sbr"
	-@erase "$(INTDIR)\Enumidl.obj"
	-@erase "$(INTDIR)\Enumidl.sbr"
	-@erase "$(INTDIR)\ExtrIcon.obj"
	-@erase "$(INTDIR)\ExtrIcon.sbr"
	-@erase "$(INTDIR)\PidlMgr.obj"
	-@erase "$(INTDIR)\PidlMgr.sbr"
	-@erase "$(INTDIR)\policysup.obj"
	-@erase "$(INTDIR)\policysup.sbr"
	-@erase "$(INTDIR)\safedel.obj"
	-@erase "$(INTDIR)\safedel.sbr"
	-@erase "$(INTDIR)\ShlFldr.obj"
	-@erase "$(INTDIR)\ShlFldr.sbr"
	-@erase "$(INTDIR)\ShlView.obj"
	-@erase "$(INTDIR)\ShlView.sbr"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\slist.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Viewlist.obj"
	-@erase "$(INTDIR)\Viewlist.sbr"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vscontainer.sbr"
	-@erase "$(INTDIR)\vsctl.obj"
	-@erase "$(INTDIR)\vsctl.pch"
	-@erase "$(INTDIR)\vsctl.res"
	-@erase "$(INTDIR)\vsctl.sbr"
	-@erase "$(INTDIR)\vsctrl.obj"
	-@erase "$(INTDIR)\vsctrl.sbr"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp.sbr"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vsnvp_file.sbr"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmsp.sbr"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspmutil.sbr"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(INTDIR)\vspolicyfile.sbr"
	-@erase "$(INTDIR)\vssafe.obj"
	-@erase "$(INTDIR)\vssafe.sbr"
	-@erase "$(OUTDIR)\vsctl.bsc"
	-@erase "$(OUTDIR)\vsfe.dll"
	-@erase "$(OUTDIR)\vsfe.exp"
	-@erase "$(OUTDIR)\vsfe.lib"
	-@erase "$(OUTDIR)\vsfe.map"
	-@erase ".\vsctl.h"
	-@erase ".\vsctl.tlb"
	-@erase ".\vsctl_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsctl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsctl.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsctl.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\certmgmt.sbr" \
	"$(INTDIR)\ClsFact.sbr" \
	"$(INTDIR)\ContMenu.sbr" \
	"$(INTDIR)\cryptsup.sbr" \
	"$(INTDIR)\DataObj.sbr" \
	"$(INTDIR)\dlgprocs.sbr" \
	"$(INTDIR)\DropSrc.sbr" \
	"$(INTDIR)\Droptgt.sbr" \
	"$(INTDIR)\encdeclist.sbr" \
	"$(INTDIR)\Enumidl.sbr" \
	"$(INTDIR)\ExtrIcon.sbr" \
	"$(INTDIR)\PidlMgr.sbr" \
	"$(INTDIR)\policysup.sbr" \
	"$(INTDIR)\safedel.sbr" \
	"$(INTDIR)\ShlFldr.sbr" \
	"$(INTDIR)\ShlView.sbr" \
	"$(INTDIR)\slist.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\Viewlist.sbr" \
	"$(INTDIR)\vscontainer.sbr" \
	"$(INTDIR)\vsctl.sbr" \
	"$(INTDIR)\vsctrl.sbr" \
	"$(INTDIR)\vsnvp.sbr" \
	"$(INTDIR)\vsnvp_file.sbr" \
	"$(INTDIR)\vspmsp.sbr" \
	"$(INTDIR)\vspmutil.sbr" \
	"$(INTDIR)\vspolicyfile.sbr" \
	"$(INTDIR)\vssafe.sbr"

"$(OUTDIR)\vsctl.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsfe.pdb" /map:"$(INTDIR)\vsfe.map" /machine:I386 /def:".\vsctl.def" /out:"$(OUTDIR)\vsfe.dll" /implib:"$(OUTDIR)\vsfe.lib" 
DEF_FILE= \
	".\vsctl.def"
LINK32_OBJS= \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\ClsFact.obj" \
	"$(INTDIR)\ContMenu.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\dlgprocs.obj" \
	"$(INTDIR)\DropSrc.obj" \
	"$(INTDIR)\Droptgt.obj" \
	"$(INTDIR)\encdeclist.obj" \
	"$(INTDIR)\Enumidl.obj" \
	"$(INTDIR)\ExtrIcon.obj" \
	"$(INTDIR)\PidlMgr.obj" \
	"$(INTDIR)\policysup.obj" \
	"$(INTDIR)\safedel.obj" \
	"$(INTDIR)\ShlFldr.obj" \
	"$(INTDIR)\ShlView.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Viewlist.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsctl.obj" \
	"$(INTDIR)\vsctrl.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj" \
	"$(INTDIR)\vssafe.obj" \
	"$(INTDIR)\vsctl.res"

"$(OUTDIR)\vsfe.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize

ALL : ".\vsfectl" ".\vsctl.tlb" ".\vsctl.h" ".\vsctl_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\ClsFact.obj"
	-@erase "$(INTDIR)\ContMenu.obj"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\dlgprocs.obj"
	-@erase "$(INTDIR)\DropSrc.obj"
	-@erase "$(INTDIR)\Droptgt.obj"
	-@erase "$(INTDIR)\encdeclist.obj"
	-@erase "$(INTDIR)\Enumidl.obj"
	-@erase "$(INTDIR)\ExtrIcon.obj"
	-@erase "$(INTDIR)\PidlMgr.obj"
	-@erase "$(INTDIR)\policysup.obj"
	-@erase "$(INTDIR)\safedel.obj"
	-@erase "$(INTDIR)\ShlFldr.obj"
	-@erase "$(INTDIR)\ShlView.obj"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Viewlist.obj"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vsctl.obj"
	-@erase "$(INTDIR)\vsctl.pch"
	-@erase "$(INTDIR)\vsctl.res"
	-@erase "$(INTDIR)\vsctrl.obj"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(INTDIR)\vssafe.obj"
	-@erase "$(OUTDIR)\vsfectl.exp"
	-@erase "$(OUTDIR)\vsfectl.lib"
	-@erase ".\vsctl.h"
	-@erase ".\vsctl.tlb"
	-@erase ".\vsctl_i.c"
	-@erase ".\vsfectl"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\vsctl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsctl.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsctl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsfectl.pdb" /machine:I386 /def:".\vsctl.def" /out:"vsfectl" /implib:"$(OUTDIR)\vsfectl.lib" 
DEF_FILE= \
	".\vsctl.def"
LINK32_OBJS= \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\ClsFact.obj" \
	"$(INTDIR)\ContMenu.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\dlgprocs.obj" \
	"$(INTDIR)\DropSrc.obj" \
	"$(INTDIR)\Droptgt.obj" \
	"$(INTDIR)\encdeclist.obj" \
	"$(INTDIR)\Enumidl.obj" \
	"$(INTDIR)\ExtrIcon.obj" \
	"$(INTDIR)\PidlMgr.obj" \
	"$(INTDIR)\policysup.obj" \
	"$(INTDIR)\safedel.obj" \
	"$(INTDIR)\ShlFldr.obj" \
	"$(INTDIR)\ShlView.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Viewlist.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsctl.obj" \
	"$(INTDIR)\vsctrl.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj" \
	"$(INTDIR)\vssafe.obj" \
	"$(INTDIR)\vsctl.res"

".\vsfectl" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\vsfectl
InputPath=.\vsfectl
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
	

!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency

ALL : ".\vsfectl" ".\vsctl.tlb" ".\vsctl.h" ".\vsctl_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\ClsFact.obj"
	-@erase "$(INTDIR)\ContMenu.obj"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\DataObj.obj"
	-@erase "$(INTDIR)\dlgprocs.obj"
	-@erase "$(INTDIR)\DropSrc.obj"
	-@erase "$(INTDIR)\Droptgt.obj"
	-@erase "$(INTDIR)\encdeclist.obj"
	-@erase "$(INTDIR)\Enumidl.obj"
	-@erase "$(INTDIR)\ExtrIcon.obj"
	-@erase "$(INTDIR)\PidlMgr.obj"
	-@erase "$(INTDIR)\policysup.obj"
	-@erase "$(INTDIR)\safedel.obj"
	-@erase "$(INTDIR)\ShlFldr.obj"
	-@erase "$(INTDIR)\ShlView.obj"
	-@erase "$(INTDIR)\slist.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Viewlist.obj"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vsctl.obj"
	-@erase "$(INTDIR)\vsctl.pch"
	-@erase "$(INTDIR)\vsctl.res"
	-@erase "$(INTDIR)\vsctrl.obj"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(INTDIR)\vssafe.obj"
	-@erase "$(OUTDIR)\vsfectl.exp"
	-@erase "$(OUTDIR)\vsfectl.lib"
	-@erase ".\vsctl.h"
	-@erase ".\vsctl.tlb"
	-@erase ".\vsctl_i.c"
	-@erase ".\vsfectl"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\vsctl.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vsctl.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsctl.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib crypt32.lib urlmon.lib version.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\vsfectl.pdb" /machine:I386 /def:".\vsctl.def" /out:"vsfectl" /implib:"$(OUTDIR)\vsfectl.lib" 
DEF_FILE= \
	".\vsctl.def"
LINK32_OBJS= \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\ClsFact.obj" \
	"$(INTDIR)\ContMenu.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\DataObj.obj" \
	"$(INTDIR)\dlgprocs.obj" \
	"$(INTDIR)\DropSrc.obj" \
	"$(INTDIR)\Droptgt.obj" \
	"$(INTDIR)\encdeclist.obj" \
	"$(INTDIR)\Enumidl.obj" \
	"$(INTDIR)\ExtrIcon.obj" \
	"$(INTDIR)\PidlMgr.obj" \
	"$(INTDIR)\policysup.obj" \
	"$(INTDIR)\safedel.obj" \
	"$(INTDIR)\ShlFldr.obj" \
	"$(INTDIR)\ShlView.obj" \
	"$(INTDIR)\slist.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\Viewlist.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsctl.obj" \
	"$(INTDIR)\vsctrl.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj" \
	"$(INTDIR)\vssafe.obj" \
	"$(INTDIR)\vsctl.res"

".\vsfectl" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\vsfectl
InputPath=.\vsfectl
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
!IF EXISTS("vsctl.dep")
!INCLUDE "vsctl.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsctl.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vsctl - Win32 Debug" || "$(CFG)" == "vsctl - Win32 Unicode Debug" || "$(CFG)" == "vsctl - Win32 Release MinSize" || "$(CFG)" == "vsctl - Win32 Release MinDependency" || "$(CFG)" == "vsctl - Win32 Unicode Release MinSize" || "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"
SOURCE=.\src\certmgmt.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\certmgmt.obj"	"$(INTDIR)\certmgmt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\certmgmt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\certmgmt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\certmgmt.obj"	"$(INTDIR)\certmgmt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\certmgmt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\certmgmt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\ClsFact.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\ClsFact.obj"	"$(INTDIR)\ClsFact.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\ClsFact.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\ClsFact.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\ClsFact.obj"	"$(INTDIR)\ClsFact.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\ClsFact.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\ClsFact.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\ContMenu.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\ContMenu.obj"	"$(INTDIR)\ContMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\ContMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\ContMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\ContMenu.obj"	"$(INTDIR)\ContMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\ContMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\ContMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\cryptsup.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\cryptsup.obj"	"$(INTDIR)\cryptsup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\cryptsup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\cryptsup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\cryptsup.obj"	"$(INTDIR)\cryptsup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\cryptsup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\cryptsup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\DataObj.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\DataObj.obj"	"$(INTDIR)\DataObj.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\DataObj.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\dlgprocs.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\dlgprocs.obj"	"$(INTDIR)\dlgprocs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\dlgprocs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\dlgprocs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\dlgprocs.obj"	"$(INTDIR)\dlgprocs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\dlgprocs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\dlgprocs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\DropSrc.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\DropSrc.obj"	"$(INTDIR)\DropSrc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\DropSrc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\DropSrc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\DropSrc.obj"	"$(INTDIR)\DropSrc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\DropSrc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\DropSrc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Droptgt.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\Droptgt.obj"	"$(INTDIR)\Droptgt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\Droptgt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\Droptgt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\Droptgt.obj"	"$(INTDIR)\Droptgt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\Droptgt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\Droptgt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\encdeclist.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\encdeclist.obj"	"$(INTDIR)\encdeclist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\encdeclist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\encdeclist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\encdeclist.obj"	"$(INTDIR)\encdeclist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\encdeclist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\encdeclist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Enumidl.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\Enumidl.obj"	"$(INTDIR)\Enumidl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\Enumidl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\Enumidl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\Enumidl.obj"	"$(INTDIR)\Enumidl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\Enumidl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\Enumidl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\ExtrIcon.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\ExtrIcon.obj"	"$(INTDIR)\ExtrIcon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\ExtrIcon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\ExtrIcon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\ExtrIcon.obj"	"$(INTDIR)\ExtrIcon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\ExtrIcon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\ExtrIcon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\PidlMgr.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\PidlMgr.obj"	"$(INTDIR)\PidlMgr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\PidlMgr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\PidlMgr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\PidlMgr.obj"	"$(INTDIR)\PidlMgr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\PidlMgr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\PidlMgr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\policysup.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\policysup.obj"	"$(INTDIR)\policysup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\policysup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\policysup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\policysup.obj"	"$(INTDIR)\policysup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\policysup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\policysup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\safedel.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\safedel.obj"	"$(INTDIR)\safedel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\safedel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\safedel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\safedel.obj"	"$(INTDIR)\safedel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\safedel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\safedel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\ShlFldr.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\ShlFldr.obj"	"$(INTDIR)\ShlFldr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\ShlFldr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\ShlFldr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\ShlFldr.obj"	"$(INTDIR)\ShlFldr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\ShlFldr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\ShlFldr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\ShlView.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\ShlView.obj"	"$(INTDIR)\ShlView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\ShlView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\ShlView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\ShlView.obj"	"$(INTDIR)\ShlView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\ShlView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\ShlView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\slist.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\slist.obj"	"$(INTDIR)\slist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\slist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\slist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\slist.obj"	"$(INTDIR)\slist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\slist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\slist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsctl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsctl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\vsctl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsctl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\vsctl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsctl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsctl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\vsctl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\vsctl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsctl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I ".\\" /I "\datafiles\onsite\corbu\clients\modules\policymanager\include" /I "\datafiles\onsite\common\include" /I "res" /I "h" /I "..\..\pta\activex\ptav3\include" /I "..\..\..\modules\protectedstorage\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\vsctl.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsctl.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\src\util.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\util.obj"	"$(INTDIR)\util.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\util.obj"	"$(INTDIR)\util.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\Viewlist.Cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\Viewlist.obj"	"$(INTDIR)\Viewlist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\Viewlist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\Viewlist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\Viewlist.obj"	"$(INTDIR)\Viewlist.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\Viewlist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\Viewlist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vscontainer.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vscontainer.obj"	"$(INTDIR)\vscontainer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vscontainer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vscontainer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vscontainer.obj"	"$(INTDIR)\vscontainer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vscontainer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vscontainer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\vsctl.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vsctl.obj"	"$(INTDIR)\vsctl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch" ".\vsctl.h" ".\vsctl_i.c"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vsctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vsctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vsctl.obj"	"$(INTDIR)\vsctl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vsctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vsctl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ENDIF 

SOURCE=.\vsctl.idl
MTL_SWITCHES=/tlb ".\vsctl.tlb" /h "vsctl.h" /iid "vsctl_i.c" /Oicf 

".\vsctl.tlb"	".\vsctl.h"	".\vsctl_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=res\vsctl.rc

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vsctl.res" : $(SOURCE) "$(INTDIR)" ".\vsctl.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vsctl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vsctl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vsctl.res" : $(SOURCE) "$(INTDIR)" ".\vsctl.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vsctl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vsctl.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\vsctl.res" /i "res" /d "NDEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\vsctrl.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vsctrl.obj"	"$(INTDIR)\vsctrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch" ".\vsctl.h"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vsctrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vsctrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vsctrl.obj"	"$(INTDIR)\vsctrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vsctrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vsctrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"


!ENDIF 

SOURCE=.\src\vsnvp.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vsnvp.obj"	"$(INTDIR)\vsnvp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vsnvp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vsnvp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vsnvp.obj"	"$(INTDIR)\vsnvp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vsnvp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vsnvp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsnvp_file.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vsnvp_file.obj"	"$(INTDIR)\vsnvp_file.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vsnvp_file.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vsnvp_file.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vsnvp_file.obj"	"$(INTDIR)\vsnvp_file.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vsnvp_file.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vsnvp_file.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vspmsp.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vspmsp.obj"	"$(INTDIR)\vspmsp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vspmsp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vspmsp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vspmsp.obj"	"$(INTDIR)\vspmsp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vspmsp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vspmsp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vspmutil.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vspmutil.obj"	"$(INTDIR)\vspmutil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vspmutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vspmutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vspmutil.obj"	"$(INTDIR)\vspmutil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vspmutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vspmutil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vspolicyfile.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vspolicyfile.obj"	"$(INTDIR)\vspolicyfile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vspolicyfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vspolicyfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vspolicyfile.obj"	"$(INTDIR)\vspolicyfile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vspolicyfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vspolicyfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vssafe.cpp

!IF  "$(CFG)" == "vsctl - Win32 Debug"


"$(INTDIR)\vssafe.obj"	"$(INTDIR)\vssafe.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Debug"


"$(INTDIR)\vssafe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinSize"


"$(INTDIR)\vssafe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Release MinDependency"


"$(INTDIR)\vssafe.obj"	"$(INTDIR)\vssafe.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinSize"


"$(INTDIR)\vssafe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "vsctl - Win32 Unicode Release MinDependency"


"$(INTDIR)\vssafe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsctl.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


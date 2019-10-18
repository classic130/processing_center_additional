# Microsoft Developer Studio Generated NMAKE File, Based on Ptav3.dsp
!IF "$(CFG)" == ""
CFG=Ptav3 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Ptav3 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ptav3 - Win32 Debug" && "$(CFG)" != "Ptav3 - Win32 Unicode Debug" && "$(CFG)" != "Ptav3 - Win32 Release MinSize" && "$(CFG)" != "Ptav3 - Win32 Release MinDependency" && "$(CFG)" != "Ptav3 - Win32 Unicode Release MinSize" && "$(CFG)" != "Ptav3 - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
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

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Ptav3.dll" ".\Include\certprefs.h" ".\Source\certprefs_i.c" ".\Include\export.h" ".\source\export_i.c" ".\Include\import.h" ".\source\import_i.c" ".\Include\profmgmt.h" ".\Source\profmgmt_i.c" ".\Include\ptadllapi.h" ".\Source\ptadllapi_i.c" ".\ptav3.tlb" ".\Include\ptav3.h" ".\source\ptav3_i.c" ".\include\roamprefs.h" ".\source\roamprefs_i.c" ".\include\seldigid.h" ".\source\seldigid_i.c" ".\include\srchcrit.h" ".\source\srchcrit_i.c" ".\include\uiprefs.h" ".\source\uiprefs_i.c" "$(OUTDIR)\Ptav3.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certinfo.obj"
	-@erase "$(INTDIR)\certinfo.sbr"
	-@erase "$(INTDIR)\csputil.obj"
	-@erase "$(INTDIR)\csputil.sbr"
	-@erase "$(INTDIR)\ExportP12.obj"
	-@erase "$(INTDIR)\ExportP12.sbr"
	-@erase "$(INTDIR)\FindPrimes.obj"
	-@erase "$(INTDIR)\FindPrimes.sbr"
	-@erase "$(INTDIR)\HelperFunctions.obj"
	-@erase "$(INTDIR)\HelperFunctions.sbr"
	-@erase "$(INTDIR)\langutils.obj"
	-@erase "$(INTDIR)\langutils.sbr"
	-@erase "$(INTDIR)\MyUniversalInteger.obj"
	-@erase "$(INTDIR)\MyUniversalInteger.sbr"
	-@erase "$(INTDIR)\P12Helper.obj"
	-@erase "$(INTDIR)\P12Helper.sbr"
	-@erase "$(INTDIR)\pkcs12info.obj"
	-@erase "$(INTDIR)\pkcs12info.sbr"
	-@erase "$(INTDIR)\PtaEngine.obj"
	-@erase "$(INTDIR)\PtaEngine.sbr"
	-@erase "$(INTDIR)\PTAUI.obj"
	-@erase "$(INTDIR)\PTAUI.sbr"
	-@erase "$(INTDIR)\Ptav3.obj"
	-@erase "$(INTDIR)\Ptav3.pch"
	-@erase "$(INTDIR)\Ptav3.res"
	-@erase "$(INTDIR)\Ptav3.sbr"
	-@erase "$(INTDIR)\roots.obj"
	-@erase "$(INTDIR)\roots.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\virtualsmartcard.obj"
	-@erase "$(INTDIR)\virtualsmartcard.sbr"
	-@erase "$(INTDIR)\vs_csp.obj"
	-@erase "$(INTDIR)\vs_csp.sbr"
	-@erase "$(INTDIR)\vs_tpm_csp.obj"
	-@erase "$(INTDIR)\vs_tpm_csp.sbr"
	-@erase "$(INTDIR)\vscapi.obj"
	-@erase "$(INTDIR)\vscapi.sbr"
	-@erase "$(INTDIR)\VSPTA.obj"
	-@erase "$(INTDIR)\VSPTA.sbr"
	-@erase "$(OUTDIR)\Ptav3.bsc"
	-@erase "$(OUTDIR)\Ptav3.dll"
	-@erase "$(OUTDIR)\Ptav3.exp"
	-@erase "$(OUTDIR)\Ptav3.ilk"
	-@erase "$(OUTDIR)\Ptav3.lib"
	-@erase "$(OUTDIR)\Ptav3.pdb"
	-@erase ".\Include\certprefs.h"
	-@erase ".\Include\export.h"
	-@erase ".\Include\import.h"
	-@erase ".\Include\profmgmt.h"
	-@erase ".\Include\ptadllapi.h"
	-@erase ".\Include\ptav3.h"
	-@erase ".\include\roamprefs.h"
	-@erase ".\include\seldigid.h"
	-@erase ".\include\srchcrit.h"
	-@erase ".\include\uiprefs.h"
	-@erase ".\ptav3.tlb"
	-@erase ".\Source\certprefs_i.c"
	-@erase ".\source\export_i.c"
	-@erase ".\source\import_i.c"
	-@erase ".\Source\profmgmt_i.c"
	-@erase ".\Source\ptadllapi_i.c"
	-@erase ".\source\ptav3_i.c"
	-@erase ".\source\roamprefs_i.c"
	-@erase ".\source\seldigid_i.c"
	-@erase ".\source\srchcrit_i.c"
	-@erase ".\source\uiprefs_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /Gi /ZI /Od /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "..\..\..\..\modules\RoamingClient\include" /I "..\..\..\..\modules\VS_IBMTSS\include" /I "i:\Platform SDK\include" /I "i:\TSS SDK\IBM\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D VS_TSSDLL=1 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptav3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ptav3.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptav3.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\csputil.sbr" \
	"$(INTDIR)\HelperFunctions.sbr" \
	"$(INTDIR)\vs_csp.sbr" \
	"$(INTDIR)\vs_tpm_csp.sbr" \
	"$(INTDIR)\certinfo.sbr" \
	"$(INTDIR)\ExportP12.sbr" \
	"$(INTDIR)\FindPrimes.sbr" \
	"$(INTDIR)\langutils.sbr" \
	"$(INTDIR)\MyUniversalInteger.sbr" \
	"$(INTDIR)\P12Helper.sbr" \
	"$(INTDIR)\pkcs12info.sbr" \
	"$(INTDIR)\PtaEngine.sbr" \
	"$(INTDIR)\PTAUI.sbr" \
	"$(INTDIR)\Ptav3.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\virtualsmartcard.sbr" \
	"$(INTDIR)\vscapi.sbr" \
	"$(INTDIR)\VSPTA.sbr" \
	"$(INTDIR)\roots.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Ptav3.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib crypt32.lib Ws2_32.lib "..\..\..\..\modules\lib\static\debug\bsafelite.lib" "..\..\..\..\modules\lib\static\debug\ProtectedStorage.lib" "..\..\..\..\..\common\lib\Debug\simder.lib" "..\..\..\..\modules\RoamingClient\lib\debug\vsrmclient.lib" "I:\TSS SDK\IBM\lib\tspi.lib" /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Ptav3.pdb" /debug /machine:I386 /nodefaultlib:"libm.lib" /def:".\source\Ptav3.def" /out:"$(OUTDIR)\Ptav3.dll" /implib:"$(OUTDIR)\Ptav3.lib" /pdbtype:sept /libpath:"I:\Platform SDK\Lib" /libpath:"I:\TSS SDK\IBM\lib" 
DEF_FILE= \
	".\source\Ptav3.def"
LINK32_OBJS= \
	"$(INTDIR)\csputil.obj" \
	"$(INTDIR)\HelperFunctions.obj" \
	"$(INTDIR)\vs_csp.obj" \
	"$(INTDIR)\vs_tpm_csp.obj" \
	"$(INTDIR)\certinfo.obj" \
	"$(INTDIR)\ExportP12.obj" \
	"$(INTDIR)\FindPrimes.obj" \
	"$(INTDIR)\langutils.obj" \
	"$(INTDIR)\MyUniversalInteger.obj" \
	"$(INTDIR)\P12Helper.obj" \
	"$(INTDIR)\pkcs12info.obj" \
	"$(INTDIR)\PtaEngine.obj" \
	"$(INTDIR)\PTAUI.obj" \
	"$(INTDIR)\Ptav3.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\virtualsmartcard.obj" \
	"$(INTDIR)\vscapi.obj" \
	"$(INTDIR)\VSPTA.obj" \
	"$(INTDIR)\roots.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptav3.res"

"$(OUTDIR)\Ptav3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Ptav3.dll
InputPath=.\Debug\Ptav3.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	REM regsvr32 /s /c "$(TargetPath)" 
	REM echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	
SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\Ptav3.dll" ".\Include\certprefs.h" ".\Source\certprefs_i.c" ".\Include\export.h" ".\source\export_i.c" ".\Include\import.h" ".\source\import_i.c" ".\Include\profmgmt.h" ".\Source\profmgmt_i.c" ".\Include\ptadllapi.h" ".\Source\ptadllapi_i.c" ".\ptav3.tlb" ".\Include\ptav3.h" ".\source\ptav3_i.c" ".\include\roamprefs.h" ".\source\roamprefs_i.c" ".\include\seldigid.h" ".\source\seldigid_i.c" ".\include\srchcrit.h" ".\source\srchcrit_i.c" ".\include\uiprefs.h" ".\source\uiprefs_i.c" "$(OUTDIR)\Ptav3.bsc" ".\Debug\regsvr32.trg"
   if not exist "..\..\..\..\lib\dynamic\debug" md "..\..\..\..\lib\dynamic\debug"
	copy debug\ptav3.dll "..\..\..\..\lib\dynamic\debug"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\Ptav3.dll" "$(OUTDIR)\certprefs.tlb" ".\Include\certprefs.h" ".\Source\certprefs_i.c" "$(OUTDIR)\export.tlb" "$(OUTDIR)\import.tlb" ".\Include\import.h" ".\source\import_i.c" "$(OUTDIR)\profmgmt.tlb" ".\Include\profmgmt.h" ".\Source\profmgmt_i.c" "$(OUTDIR)\ptadllapi.tlb" ".\Include\ptadllapi.h" ".\Source\ptadllapi_i.c" ".\ptav3.tlb" ".\Include\ptav3.h" ".\source\ptav3_i.c" "$(OUTDIR)\roamprefs.tlb" ".\include\roamprefs.h" ".\source\roamprefs_i.c" "$(OUTDIR)\seldigid.tlb" ".\include\seldigid.h" ".\source\seldigid_i.c" "$(OUTDIR)\srchcrit.tlb" ".\include\srchcrit.h" ".\source\srchcrit_i.c" "$(OUTDIR)\uiprefs.tlb" ".\include\uiprefs.h" ".\source\uiprefs_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certinfo.obj"
	-@erase "$(INTDIR)\certprefs.tlb"
	-@erase "$(INTDIR)\csputil.obj"
	-@erase "$(INTDIR)\export.tlb"
	-@erase "$(INTDIR)\ExportP12.obj"
	-@erase "$(INTDIR)\FindPrimes.obj"
	-@erase "$(INTDIR)\HelperFunctions.obj"
	-@erase "$(INTDIR)\import.tlb"
	-@erase "$(INTDIR)\langutils.obj"
	-@erase "$(INTDIR)\MyUniversalInteger.obj"
	-@erase "$(INTDIR)\P12Helper.obj"
	-@erase "$(INTDIR)\pkcs12info.obj"
	-@erase "$(INTDIR)\profmgmt.tlb"
	-@erase "$(INTDIR)\ptadllapi.tlb"
	-@erase "$(INTDIR)\PtaEngine.obj"
	-@erase "$(INTDIR)\PTAUI.obj"
	-@erase "$(INTDIR)\Ptav3.obj"
	-@erase "$(INTDIR)\Ptav3.pch"
	-@erase "$(INTDIR)\Ptav3.res"
	-@erase "$(INTDIR)\roamprefs.tlb"
	-@erase "$(INTDIR)\roots.obj"
	-@erase "$(INTDIR)\seldigid.tlb"
	-@erase "$(INTDIR)\srchcrit.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\uiprefs.tlb"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\virtualsmartcard.obj"
	-@erase "$(INTDIR)\vs_csp.obj"
	-@erase "$(INTDIR)\vs_tpm_csp.obj"
	-@erase "$(INTDIR)\vscapi.obj"
	-@erase "$(INTDIR)\VSPTA.obj"
	-@erase "$(OUTDIR)\Ptav3.dll"
	-@erase "$(OUTDIR)\Ptav3.exp"
	-@erase "$(OUTDIR)\Ptav3.ilk"
	-@erase "$(OUTDIR)\Ptav3.lib"
	-@erase "$(OUTDIR)\Ptav3.pdb"
	-@erase ".\Include\certprefs.h"
	-@erase ".\Include\import.h"
	-@erase ".\Include\profmgmt.h"
	-@erase ".\Include\ptadllapi.h"
	-@erase ".\Include\ptav3.h"
	-@erase ".\include\roamprefs.h"
	-@erase ".\include\seldigid.h"
	-@erase ".\include\srchcrit.h"
	-@erase ".\include\uiprefs.h"
	-@erase ".\ptav3.tlb"
	-@erase ".\Source\certprefs_i.c"
	-@erase ".\source\import_i.c"
	-@erase ".\Source\profmgmt_i.c"
	-@erase ".\Source\ptadllapi_i.c"
	-@erase ".\source\ptav3_i.c"
	-@erase ".\source\roamprefs_i.c"
	-@erase ".\source\seldigid_i.c"
	-@erase ".\source\srchcrit_i.c"
	-@erase ".\source\uiprefs_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Ptav3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ptav3.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptav3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Ptav3.pdb" /debug /machine:I386 /def:".\source\Ptav3.def" /out:"$(OUTDIR)\Ptav3.dll" /implib:"$(OUTDIR)\Ptav3.lib" /pdbtype:sept 
DEF_FILE= \
	".\source\Ptav3.def"
LINK32_OBJS= \
	"$(INTDIR)\csputil.obj" \
	"$(INTDIR)\HelperFunctions.obj" \
	"$(INTDIR)\vs_csp.obj" \
	"$(INTDIR)\vs_tpm_csp.obj" \
	"$(INTDIR)\certinfo.obj" \
	"$(INTDIR)\ExportP12.obj" \
	"$(INTDIR)\FindPrimes.obj" \
	"$(INTDIR)\langutils.obj" \
	"$(INTDIR)\MyUniversalInteger.obj" \
	"$(INTDIR)\P12Helper.obj" \
	"$(INTDIR)\pkcs12info.obj" \
	"$(INTDIR)\PtaEngine.obj" \
	"$(INTDIR)\PTAUI.obj" \
	"$(INTDIR)\Ptav3.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\virtualsmartcard.obj" \
	"$(INTDIR)\vscapi.obj" \
	"$(INTDIR)\VSPTA.obj" \
	"$(INTDIR)\roots.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptav3.res"

"$(OUTDIR)\Ptav3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Ptav3.dll
InputPath=.\DebugU\Ptav3.dll
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
	

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\Ptav3.dll" "$(OUTDIR)\certprefs.tlb" ".\Include\certprefs.h" ".\Source\certprefs_i.c" "$(OUTDIR)\export.tlb" "$(OUTDIR)\import.tlb" ".\Include\import.h" ".\source\import_i.c" "$(OUTDIR)\profmgmt.tlb" ".\Include\profmgmt.h" ".\Source\profmgmt_i.c" "$(OUTDIR)\ptadllapi.tlb" ".\Include\ptadllapi.h" ".\Source\ptadllapi_i.c" ".\ptav3.tlb" ".\Include\ptav3.h" ".\source\ptav3_i.c" "$(OUTDIR)\roamprefs.tlb" ".\include\roamprefs.h" ".\source\roamprefs_i.c" "$(OUTDIR)\seldigid.tlb" ".\include\seldigid.h" ".\source\seldigid_i.c" "$(OUTDIR)\srchcrit.tlb" ".\include\srchcrit.h" ".\source\srchcrit_i.c" "$(OUTDIR)\uiprefs.tlb" ".\include\uiprefs.h" ".\source\uiprefs_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certinfo.obj"
	-@erase "$(INTDIR)\certprefs.tlb"
	-@erase "$(INTDIR)\csputil.obj"
	-@erase "$(INTDIR)\export.tlb"
	-@erase "$(INTDIR)\ExportP12.obj"
	-@erase "$(INTDIR)\FindPrimes.obj"
	-@erase "$(INTDIR)\HelperFunctions.obj"
	-@erase "$(INTDIR)\import.tlb"
	-@erase "$(INTDIR)\langutils.obj"
	-@erase "$(INTDIR)\MyUniversalInteger.obj"
	-@erase "$(INTDIR)\P12Helper.obj"
	-@erase "$(INTDIR)\pkcs12info.obj"
	-@erase "$(INTDIR)\profmgmt.tlb"
	-@erase "$(INTDIR)\ptadllapi.tlb"
	-@erase "$(INTDIR)\PtaEngine.obj"
	-@erase "$(INTDIR)\PTAUI.obj"
	-@erase "$(INTDIR)\Ptav3.obj"
	-@erase "$(INTDIR)\Ptav3.pch"
	-@erase "$(INTDIR)\Ptav3.res"
	-@erase "$(INTDIR)\roamprefs.tlb"
	-@erase "$(INTDIR)\roots.obj"
	-@erase "$(INTDIR)\seldigid.tlb"
	-@erase "$(INTDIR)\srchcrit.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\uiprefs.tlb"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\virtualsmartcard.obj"
	-@erase "$(INTDIR)\vs_csp.obj"
	-@erase "$(INTDIR)\vs_tpm_csp.obj"
	-@erase "$(INTDIR)\vscapi.obj"
	-@erase "$(INTDIR)\VSPTA.obj"
	-@erase "$(OUTDIR)\Ptav3.dll"
	-@erase "$(OUTDIR)\Ptav3.exp"
	-@erase "$(OUTDIR)\Ptav3.lib"
	-@erase ".\Include\certprefs.h"
	-@erase ".\Include\import.h"
	-@erase ".\Include\profmgmt.h"
	-@erase ".\Include\ptadllapi.h"
	-@erase ".\Include\ptav3.h"
	-@erase ".\include\roamprefs.h"
	-@erase ".\include\seldigid.h"
	-@erase ".\include\srchcrit.h"
	-@erase ".\include\uiprefs.h"
	-@erase ".\ptav3.tlb"
	-@erase ".\Source\certprefs_i.c"
	-@erase ".\source\import_i.c"
	-@erase ".\Source\profmgmt_i.c"
	-@erase ".\Source\ptadllapi_i.c"
	-@erase ".\source\ptav3_i.c"
	-@erase ".\source\roamprefs_i.c"
	-@erase ".\source\seldigid_i.c"
	-@erase ".\source\srchcrit_i.c"
	-@erase ".\source\uiprefs_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Ptav3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ptav3.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptav3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Ptav3.pdb" /machine:I386 /def:".\source\Ptav3.def" /out:"$(OUTDIR)\Ptav3.dll" /implib:"$(OUTDIR)\Ptav3.lib" 
DEF_FILE= \
	".\source\Ptav3.def"
LINK32_OBJS= \
	"$(INTDIR)\csputil.obj" \
	"$(INTDIR)\HelperFunctions.obj" \
	"$(INTDIR)\vs_csp.obj" \
	"$(INTDIR)\vs_tpm_csp.obj" \
	"$(INTDIR)\certinfo.obj" \
	"$(INTDIR)\ExportP12.obj" \
	"$(INTDIR)\FindPrimes.obj" \
	"$(INTDIR)\langutils.obj" \
	"$(INTDIR)\MyUniversalInteger.obj" \
	"$(INTDIR)\P12Helper.obj" \
	"$(INTDIR)\pkcs12info.obj" \
	"$(INTDIR)\PtaEngine.obj" \
	"$(INTDIR)\PTAUI.obj" \
	"$(INTDIR)\Ptav3.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\virtualsmartcard.obj" \
	"$(INTDIR)\vscapi.obj" \
	"$(INTDIR)\VSPTA.obj" \
	"$(INTDIR)\roots.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptav3.res"

"$(OUTDIR)\Ptav3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Ptav3.dll
InputPath=.\ReleaseMinSize\Ptav3.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\Ptav3.dll" "$(OUTDIR)\Ptav3.bsc" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certinfo.obj"
	-@erase "$(INTDIR)\certinfo.sbr"
	-@erase "$(INTDIR)\csputil.obj"
	-@erase "$(INTDIR)\csputil.sbr"
	-@erase "$(INTDIR)\ExportP12.obj"
	-@erase "$(INTDIR)\ExportP12.sbr"
	-@erase "$(INTDIR)\FindPrimes.obj"
	-@erase "$(INTDIR)\FindPrimes.sbr"
	-@erase "$(INTDIR)\HelperFunctions.obj"
	-@erase "$(INTDIR)\HelperFunctions.sbr"
	-@erase "$(INTDIR)\langutils.obj"
	-@erase "$(INTDIR)\langutils.sbr"
	-@erase "$(INTDIR)\MyUniversalInteger.obj"
	-@erase "$(INTDIR)\MyUniversalInteger.sbr"
	-@erase "$(INTDIR)\P12Helper.obj"
	-@erase "$(INTDIR)\P12Helper.sbr"
	-@erase "$(INTDIR)\pkcs12info.obj"
	-@erase "$(INTDIR)\pkcs12info.sbr"
	-@erase "$(INTDIR)\PtaEngine.obj"
	-@erase "$(INTDIR)\PtaEngine.sbr"
	-@erase "$(INTDIR)\PTAUI.obj"
	-@erase "$(INTDIR)\PTAUI.sbr"
	-@erase "$(INTDIR)\Ptav3.obj"
	-@erase "$(INTDIR)\Ptav3.pch"
	-@erase "$(INTDIR)\Ptav3.res"
	-@erase "$(INTDIR)\Ptav3.sbr"
	-@erase "$(INTDIR)\roots.obj"
	-@erase "$(INTDIR)\roots.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\utils.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\virtualsmartcard.obj"
	-@erase "$(INTDIR)\virtualsmartcard.sbr"
	-@erase "$(INTDIR)\vs_csp.obj"
	-@erase "$(INTDIR)\vs_csp.sbr"
	-@erase "$(INTDIR)\vs_tpm_csp.obj"
	-@erase "$(INTDIR)\vs_tpm_csp.sbr"
	-@erase "$(INTDIR)\vscapi.obj"
	-@erase "$(INTDIR)\vscapi.sbr"
	-@erase "$(INTDIR)\VSPTA.obj"
	-@erase "$(INTDIR)\VSPTA.sbr"
	-@erase "$(OUTDIR)\Ptav3.bsc"
	-@erase "$(OUTDIR)\Ptav3.dll"
	-@erase "$(OUTDIR)\Ptav3.exp"
	-@erase "$(OUTDIR)\Ptav3.lib"
	-@erase ".\Include\certprefs.h"
	-@erase ".\Include\export.h"
	-@erase ".\Include\import.h"
	-@erase ".\Include\profmgmt.h"
	-@erase ".\Include\ptadllapi.h"
	-@erase ".\Include\ptav3.h"
	-@erase ".\include\roamprefs.h"
	-@erase ".\include\seldigid.h"
	-@erase ".\include\srchcrit.h"
	-@erase ".\include\uiprefs.h"
	-@erase ".\ptav3.tlb"
	-@erase ".\Source\certprefs_i.c"
	-@erase ".\source\export_i.c"
	-@erase ".\source\import_i.c"
	-@erase ".\Source\profmgmt_i.c"
	-@erase ".\Source\ptadllapi_i.c"
	-@erase ".\source\ptav3_i.c"
	-@erase ".\source\roamprefs_i.c"
	-@erase ".\source\seldigid_i.c"
	-@erase ".\source\srchcrit_i.c"
	-@erase ".\source\uiprefs_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /O1 /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "..\..\..\..\modules\RoamingClient\include" /I "..\..\..\..\modules\VS_IBMTSS\include" /I "i:\TSS SDK\IBM\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D VS_TSSDLL=1 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptav3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ptav3.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptav3.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\csputil.sbr" \
	"$(INTDIR)\HelperFunctions.sbr" \
	"$(INTDIR)\vs_csp.sbr" \
	"$(INTDIR)\vs_tpm_csp.sbr" \
	"$(INTDIR)\certinfo.sbr" \
	"$(INTDIR)\ExportP12.sbr" \
	"$(INTDIR)\FindPrimes.sbr" \
	"$(INTDIR)\langutils.sbr" \
	"$(INTDIR)\MyUniversalInteger.sbr" \
	"$(INTDIR)\P12Helper.sbr" \
	"$(INTDIR)\pkcs12info.sbr" \
	"$(INTDIR)\PtaEngine.sbr" \
	"$(INTDIR)\PTAUI.sbr" \
	"$(INTDIR)\Ptav3.sbr" \
	"$(INTDIR)\utils.sbr" \
	"$(INTDIR)\virtualsmartcard.sbr" \
	"$(INTDIR)\vscapi.sbr" \
	"$(INTDIR)\VSPTA.sbr" \
	"$(INTDIR)\roots.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\Ptav3.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib crypt32.lib Ws2_32.lib "..\..\..\..\modules\lib\static\release\bsafelite.lib" "..\..\..\..\modules\lib\static\release\ProtectedStorage.lib" "..\..\..\..\..\common\lib\Release\simder.lib" "..\..\..\..\modules\RoamingClient\lib\release\vsrmclient.lib" "I:\TSS SDK\IBM\lib\tspi.lib" /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Ptav3.pdb" /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libm.lib" /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /def:".\source\Ptav3.def" /out:"$(OUTDIR)\Ptav3.dll" /implib:"$(OUTDIR)\Ptav3.lib" 
DEF_FILE= \
	".\source\Ptav3.def"
LINK32_OBJS= \
	"$(INTDIR)\csputil.obj" \
	"$(INTDIR)\HelperFunctions.obj" \
	"$(INTDIR)\vs_csp.obj" \
	"$(INTDIR)\vs_tpm_csp.obj" \
	"$(INTDIR)\certinfo.obj" \
	"$(INTDIR)\ExportP12.obj" \
	"$(INTDIR)\FindPrimes.obj" \
	"$(INTDIR)\langutils.obj" \
	"$(INTDIR)\MyUniversalInteger.obj" \
	"$(INTDIR)\P12Helper.obj" \
	"$(INTDIR)\pkcs12info.obj" \
	"$(INTDIR)\PtaEngine.obj" \
	"$(INTDIR)\PTAUI.obj" \
	"$(INTDIR)\Ptav3.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\virtualsmartcard.obj" \
	"$(INTDIR)\vscapi.obj" \
	"$(INTDIR)\VSPTA.obj" \
	"$(INTDIR)\roots.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptav3.res"

"$(OUTDIR)\Ptav3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Ptav3.dll
InputPath=.\ReleaseMinDependency\Ptav3.dll
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

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\Ptav3.dll" "$(OUTDIR)\Ptav3.bsc" ".\ReleaseMinDependency\regsvr32.trg"
   if not exist "..\..\..\..\lib\dynamic\Release" md "..\..\..\..\lib\dynamic\Release"
	copy ReleaseMinDependency\ptav3.dll "..\..\..\..\lib\dynamic\Release"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\Ptav3.dll" "$(OUTDIR)\certprefs.tlb" ".\Include\certprefs.h" ".\Source\certprefs_i.c" "$(OUTDIR)\export.tlb" "$(OUTDIR)\import.tlb" ".\Include\import.h" ".\source\import_i.c" "$(OUTDIR)\profmgmt.tlb" ".\Include\profmgmt.h" ".\Source\profmgmt_i.c" "$(OUTDIR)\ptadllapi.tlb" ".\Include\ptadllapi.h" ".\Source\ptadllapi_i.c" ".\ptav3.tlb" ".\Include\ptav3.h" ".\source\ptav3_i.c" "$(OUTDIR)\roamprefs.tlb" ".\include\roamprefs.h" ".\source\roamprefs_i.c" "$(OUTDIR)\seldigid.tlb" ".\include\seldigid.h" ".\source\seldigid_i.c" "$(OUTDIR)\srchcrit.tlb" ".\include\srchcrit.h" ".\source\srchcrit_i.c" "$(OUTDIR)\uiprefs.tlb" ".\include\uiprefs.h" ".\source\uiprefs_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certinfo.obj"
	-@erase "$(INTDIR)\certprefs.tlb"
	-@erase "$(INTDIR)\csputil.obj"
	-@erase "$(INTDIR)\export.tlb"
	-@erase "$(INTDIR)\ExportP12.obj"
	-@erase "$(INTDIR)\FindPrimes.obj"
	-@erase "$(INTDIR)\HelperFunctions.obj"
	-@erase "$(INTDIR)\import.tlb"
	-@erase "$(INTDIR)\langutils.obj"
	-@erase "$(INTDIR)\MyUniversalInteger.obj"
	-@erase "$(INTDIR)\P12Helper.obj"
	-@erase "$(INTDIR)\pkcs12info.obj"
	-@erase "$(INTDIR)\profmgmt.tlb"
	-@erase "$(INTDIR)\ptadllapi.tlb"
	-@erase "$(INTDIR)\PtaEngine.obj"
	-@erase "$(INTDIR)\PTAUI.obj"
	-@erase "$(INTDIR)\Ptav3.obj"
	-@erase "$(INTDIR)\Ptav3.pch"
	-@erase "$(INTDIR)\Ptav3.res"
	-@erase "$(INTDIR)\roamprefs.tlb"
	-@erase "$(INTDIR)\roots.obj"
	-@erase "$(INTDIR)\seldigid.tlb"
	-@erase "$(INTDIR)\srchcrit.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\uiprefs.tlb"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\virtualsmartcard.obj"
	-@erase "$(INTDIR)\vs_csp.obj"
	-@erase "$(INTDIR)\vs_tpm_csp.obj"
	-@erase "$(INTDIR)\vscapi.obj"
	-@erase "$(INTDIR)\VSPTA.obj"
	-@erase "$(OUTDIR)\Ptav3.dll"
	-@erase "$(OUTDIR)\Ptav3.exp"
	-@erase "$(OUTDIR)\Ptav3.lib"
	-@erase ".\Include\certprefs.h"
	-@erase ".\Include\import.h"
	-@erase ".\Include\profmgmt.h"
	-@erase ".\Include\ptadllapi.h"
	-@erase ".\Include\ptav3.h"
	-@erase ".\include\roamprefs.h"
	-@erase ".\include\seldigid.h"
	-@erase ".\include\srchcrit.h"
	-@erase ".\include\uiprefs.h"
	-@erase ".\ptav3.tlb"
	-@erase ".\Source\certprefs_i.c"
	-@erase ".\source\import_i.c"
	-@erase ".\Source\profmgmt_i.c"
	-@erase ".\Source\ptadllapi_i.c"
	-@erase ".\source\ptav3_i.c"
	-@erase ".\source\roamprefs_i.c"
	-@erase ".\source\seldigid_i.c"
	-@erase ".\source\srchcrit_i.c"
	-@erase ".\source\uiprefs_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Ptav3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ptav3.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptav3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Ptav3.pdb" /machine:I386 /def:".\source\Ptav3.def" /out:"$(OUTDIR)\Ptav3.dll" /implib:"$(OUTDIR)\Ptav3.lib" 
DEF_FILE= \
	".\source\Ptav3.def"
LINK32_OBJS= \
	"$(INTDIR)\csputil.obj" \
	"$(INTDIR)\HelperFunctions.obj" \
	"$(INTDIR)\vs_csp.obj" \
	"$(INTDIR)\vs_tpm_csp.obj" \
	"$(INTDIR)\certinfo.obj" \
	"$(INTDIR)\ExportP12.obj" \
	"$(INTDIR)\FindPrimes.obj" \
	"$(INTDIR)\langutils.obj" \
	"$(INTDIR)\MyUniversalInteger.obj" \
	"$(INTDIR)\P12Helper.obj" \
	"$(INTDIR)\pkcs12info.obj" \
	"$(INTDIR)\PtaEngine.obj" \
	"$(INTDIR)\PTAUI.obj" \
	"$(INTDIR)\Ptav3.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\virtualsmartcard.obj" \
	"$(INTDIR)\vscapi.obj" \
	"$(INTDIR)\VSPTA.obj" \
	"$(INTDIR)\roots.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptav3.res"

"$(OUTDIR)\Ptav3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Ptav3.dll
InputPath=.\ReleaseUMinSize\Ptav3.dll
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
	

!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\Ptav3.dll" "$(OUTDIR)\certprefs.tlb" ".\Include\certprefs.h" ".\Source\certprefs_i.c" "$(OUTDIR)\export.tlb" "$(OUTDIR)\import.tlb" ".\Include\import.h" ".\source\import_i.c" "$(OUTDIR)\profmgmt.tlb" ".\Include\profmgmt.h" ".\Source\profmgmt_i.c" "$(OUTDIR)\ptadllapi.tlb" ".\Include\ptadllapi.h" ".\Source\ptadllapi_i.c" ".\ptav3.tlb" ".\Include\ptav3.h" ".\source\ptav3_i.c" "$(OUTDIR)\roamprefs.tlb" ".\include\roamprefs.h" ".\source\roamprefs_i.c" "$(OUTDIR)\seldigid.tlb" ".\include\seldigid.h" ".\source\seldigid_i.c" "$(OUTDIR)\srchcrit.tlb" ".\include\srchcrit.h" ".\source\srchcrit_i.c" "$(OUTDIR)\uiprefs.tlb" ".\include\uiprefs.h" ".\source\uiprefs_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\certinfo.obj"
	-@erase "$(INTDIR)\certprefs.tlb"
	-@erase "$(INTDIR)\csputil.obj"
	-@erase "$(INTDIR)\export.tlb"
	-@erase "$(INTDIR)\ExportP12.obj"
	-@erase "$(INTDIR)\FindPrimes.obj"
	-@erase "$(INTDIR)\HelperFunctions.obj"
	-@erase "$(INTDIR)\import.tlb"
	-@erase "$(INTDIR)\langutils.obj"
	-@erase "$(INTDIR)\MyUniversalInteger.obj"
	-@erase "$(INTDIR)\P12Helper.obj"
	-@erase "$(INTDIR)\pkcs12info.obj"
	-@erase "$(INTDIR)\profmgmt.tlb"
	-@erase "$(INTDIR)\ptadllapi.tlb"
	-@erase "$(INTDIR)\PtaEngine.obj"
	-@erase "$(INTDIR)\PTAUI.obj"
	-@erase "$(INTDIR)\Ptav3.obj"
	-@erase "$(INTDIR)\Ptav3.pch"
	-@erase "$(INTDIR)\Ptav3.res"
	-@erase "$(INTDIR)\roamprefs.tlb"
	-@erase "$(INTDIR)\roots.obj"
	-@erase "$(INTDIR)\seldigid.tlb"
	-@erase "$(INTDIR)\srchcrit.tlb"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\uiprefs.tlb"
	-@erase "$(INTDIR)\utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\virtualsmartcard.obj"
	-@erase "$(INTDIR)\vs_csp.obj"
	-@erase "$(INTDIR)\vs_tpm_csp.obj"
	-@erase "$(INTDIR)\vscapi.obj"
	-@erase "$(INTDIR)\VSPTA.obj"
	-@erase "$(OUTDIR)\Ptav3.dll"
	-@erase "$(OUTDIR)\Ptav3.exp"
	-@erase "$(OUTDIR)\Ptav3.lib"
	-@erase ".\Include\certprefs.h"
	-@erase ".\Include\import.h"
	-@erase ".\Include\profmgmt.h"
	-@erase ".\Include\ptadllapi.h"
	-@erase ".\Include\ptav3.h"
	-@erase ".\include\roamprefs.h"
	-@erase ".\include\seldigid.h"
	-@erase ".\include\srchcrit.h"
	-@erase ".\include\uiprefs.h"
	-@erase ".\ptav3.tlb"
	-@erase ".\Source\certprefs_i.c"
	-@erase ".\source\import_i.c"
	-@erase ".\Source\profmgmt_i.c"
	-@erase ".\Source\ptadllapi_i.c"
	-@erase ".\source\ptav3_i.c"
	-@erase ".\source\roamprefs_i.c"
	-@erase ".\source\seldigid_i.c"
	-@erase ".\source\srchcrit_i.c"
	-@erase ".\source\uiprefs_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\Ptav3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Ptav3.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Ptav3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../BSafeLite/Release/bsafelite.lib crypt32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Ptav3.pdb" /machine:I386 /def:".\source\Ptav3.def" /out:"$(OUTDIR)\Ptav3.dll" /implib:"$(OUTDIR)\Ptav3.lib" 
DEF_FILE= \
	".\source\Ptav3.def"
LINK32_OBJS= \
	"$(INTDIR)\csputil.obj" \
	"$(INTDIR)\HelperFunctions.obj" \
	"$(INTDIR)\vs_csp.obj" \
	"$(INTDIR)\vs_tpm_csp.obj" \
	"$(INTDIR)\certinfo.obj" \
	"$(INTDIR)\ExportP12.obj" \
	"$(INTDIR)\FindPrimes.obj" \
	"$(INTDIR)\langutils.obj" \
	"$(INTDIR)\MyUniversalInteger.obj" \
	"$(INTDIR)\P12Helper.obj" \
	"$(INTDIR)\pkcs12info.obj" \
	"$(INTDIR)\PtaEngine.obj" \
	"$(INTDIR)\PTAUI.obj" \
	"$(INTDIR)\Ptav3.obj" \
	"$(INTDIR)\utils.obj" \
	"$(INTDIR)\virtualsmartcard.obj" \
	"$(INTDIR)\vscapi.obj" \
	"$(INTDIR)\VSPTA.obj" \
	"$(INTDIR)\roots.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Ptav3.res"

"$(OUTDIR)\Ptav3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Ptav3.dll
InputPath=.\ReleaseUMinDependency\Ptav3.dll
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
!IF EXISTS("Ptav3.dep")
!INCLUDE "Ptav3.dep"
!ELSE 
!MESSAGE Warning: cannot find "Ptav3.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Ptav3 - Win32 Debug" || "$(CFG)" == "Ptav3 - Win32 Unicode Debug" || "$(CFG)" == "Ptav3 - Win32 Release MinSize" || "$(CFG)" == "Ptav3 - Win32 Release MinDependency" || "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize" || "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"
SOURCE=.\source\certprefs.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf 

".\Include\certprefs.h"	".\Source\certprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\certprefs.tlb" /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf 

"$(INTDIR)\certprefs.tlb"	".\Include\certprefs.h"	".\Source\certprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\certprefs.tlb" /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf 

"$(INTDIR)\certprefs.tlb"	".\Include\certprefs.h"	".\Source\certprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf 

".\Include\certprefs.h"	".\Source\certprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\certprefs.tlb" /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf 

"$(INTDIR)\certprefs.tlb"	".\Include\certprefs.h"	".\Source\certprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\certprefs.tlb" /h "Include/certprefs.h" /iid "Source/certprefs_i.c" /Oicf 

"$(INTDIR)\certprefs.tlb"	".\Include\certprefs.h"	".\Source\certprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\source\export.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "Include/export.h" /iid "source/export_i.c" /Oicf 

".\Include\export.h"	".\source\export_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\export.tlb" 

"$(INTDIR)\export.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\export.tlb" 

"$(INTDIR)\export.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "Include/export.h" /iid "source/export_i.c" /Oicf 

".\Include\export.h"	".\source\export_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\export.tlb" 

"$(INTDIR)\export.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\export.tlb" 

"$(INTDIR)\export.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\source\import.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "Include/import.h" /iid "source/import_i.c" /Oicf 

".\Include\import.h"	".\source\import_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\import.tlb" /h "Include/import.h" /iid "source/import_i.c" /Oicf 

"$(INTDIR)\import.tlb"	".\Include\import.h"	".\source\import_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\import.tlb" /h "Include/import.h" /iid "source/import_i.c" /Oicf 

"$(INTDIR)\import.tlb"	".\Include\import.h"	".\source\import_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "Include/import.h" /iid "source/import_i.c" /Oicf 

".\Include\import.h"	".\source\import_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\import.tlb" /h "Include/import.h" /iid "source/import_i.c" /Oicf 

"$(INTDIR)\import.tlb"	".\Include\import.h"	".\source\import_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\import.tlb" /h "Include/import.h" /iid "source/import_i.c" /Oicf 

"$(INTDIR)\import.tlb"	".\Include\import.h"	".\source\import_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Source\profmgmt.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf 

".\Include\profmgmt.h"	".\Source\profmgmt_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\profmgmt.tlb" /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf 

"$(INTDIR)\profmgmt.tlb"	".\Include\profmgmt.h"	".\Source\profmgmt_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\profmgmt.tlb" /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf 

"$(INTDIR)\profmgmt.tlb"	".\Include\profmgmt.h"	".\Source\profmgmt_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf 

".\Include\profmgmt.h"	".\Source\profmgmt_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\profmgmt.tlb" /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf 

"$(INTDIR)\profmgmt.tlb"	".\Include\profmgmt.h"	".\Source\profmgmt_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\profmgmt.tlb" /h "Include/profmgmt.h" /iid "Source/profmgmt_i.c" /Oicf 

"$(INTDIR)\profmgmt.tlb"	".\Include\profmgmt.h"	".\Source\profmgmt_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\source\ptadllapi.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf 

".\Include\ptadllapi.h"	".\Source\ptadllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\ptadllapi.tlb" /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf 

"$(INTDIR)\ptadllapi.tlb"	".\Include\ptadllapi.h"	".\Source\ptadllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\ptadllapi.tlb" /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf 

"$(INTDIR)\ptadllapi.tlb"	".\Include\ptadllapi.h"	".\Source\ptadllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf 

".\Include\ptadllapi.h"	".\Source\ptadllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\ptadllapi.tlb" /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf 

"$(INTDIR)\ptadllapi.tlb"	".\Include\ptadllapi.h"	".\Source\ptadllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\ptadllapi.tlb" /h "Include/ptadllapi.h" /iid "Source/ptadllapi_i.c" /Oicf 

"$(INTDIR)\ptadllapi.tlb"	".\Include\ptadllapi.h"	".\Source\ptadllapi_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\source\Ptav3.idl
MTL_SWITCHES=/tlb "ptav3.tlb" /h "Include\ptav3.h" /iid "source\ptav3_i.c" /Oicf 

".\ptav3.tlb"	".\Include\ptav3.h"	".\source\ptav3_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\source\roamprefs.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf 

".\include\roamprefs.h"	".\source\roamprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\roamprefs.tlb" /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf 

"$(INTDIR)\roamprefs.tlb"	".\include\roamprefs.h"	".\source\roamprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\roamprefs.tlb" /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf 

"$(INTDIR)\roamprefs.tlb"	".\include\roamprefs.h"	".\source\roamprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf 

".\include\roamprefs.h"	".\source\roamprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\roamprefs.tlb" /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf 

"$(INTDIR)\roamprefs.tlb"	".\include\roamprefs.h"	".\source\roamprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\roamprefs.tlb" /h "include/roamprefs.h" /iid "source/roamprefs_i.c" /Oicf 

"$(INTDIR)\roamprefs.tlb"	".\include\roamprefs.h"	".\source\roamprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Source\seldigid.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf 

".\include\seldigid.h"	".\source\seldigid_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\seldigid.tlb" /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf 

"$(INTDIR)\seldigid.tlb"	".\include\seldigid.h"	".\source\seldigid_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\seldigid.tlb" /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf 

"$(INTDIR)\seldigid.tlb"	".\include\seldigid.h"	".\source\seldigid_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf 

".\include\seldigid.h"	".\source\seldigid_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\seldigid.tlb" /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf 

"$(INTDIR)\seldigid.tlb"	".\include\seldigid.h"	".\source\seldigid_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\seldigid.tlb" /h "include\seldigid.h" /iid "source\seldigid_i.c" /Oicf 

"$(INTDIR)\seldigid.tlb"	".\include\seldigid.h"	".\source\seldigid_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Source\srchcrit.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf 

".\include\srchcrit.h"	".\source\srchcrit_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\srchcrit.tlb" /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf 

"$(INTDIR)\srchcrit.tlb"	".\include\srchcrit.h"	".\source\srchcrit_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\srchcrit.tlb" /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf 

"$(INTDIR)\srchcrit.tlb"	".\include\srchcrit.h"	".\source\srchcrit_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf 

".\include\srchcrit.h"	".\source\srchcrit_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\srchcrit.tlb" /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf 

"$(INTDIR)\srchcrit.tlb"	".\include\srchcrit.h"	".\source\srchcrit_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\srchcrit.tlb" /h "include\srchcrit.h" /iid "source\srchcrit_i.c" /Oicf 

"$(INTDIR)\srchcrit.tlb"	".\include\srchcrit.h"	".\source\srchcrit_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Source\uiprefs.idl

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

MTL_SWITCHES=/h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf 

".\include\uiprefs.h"	".\source\uiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

MTL_SWITCHES=/tlb "$(OUTDIR)\uiprefs.tlb" /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf 

"$(INTDIR)\uiprefs.tlb"	".\include\uiprefs.h"	".\source\uiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\uiprefs.tlb" /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf 

"$(INTDIR)\uiprefs.tlb"	".\include\uiprefs.h"	".\source\uiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

MTL_SWITCHES=/h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf 

".\include\uiprefs.h"	".\source\uiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb "$(OUTDIR)\uiprefs.tlb" /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf 

"$(INTDIR)\uiprefs.tlb"	".\include\uiprefs.h"	".\source\uiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb "$(OUTDIR)\uiprefs.tlb" /h "include\uiprefs.h" /iid "source\uiprefs_i.c" /Oicf 

"$(INTDIR)\uiprefs.tlb"	".\include\uiprefs.h"	".\source\uiprefs_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\source\csputil.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\csputil.obj"	"$(INTDIR)\csputil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\csputil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\csputil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\csputil.obj"	"$(INTDIR)\csputil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\csputil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\csputil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\HelperFunctions.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\HelperFunctions.obj"	"$(INTDIR)\HelperFunctions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\HelperFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\HelperFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\HelperFunctions.obj"	"$(INTDIR)\HelperFunctions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\HelperFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\HelperFunctions.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\vs_csp.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\vs_csp.obj"	"$(INTDIR)\vs_csp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\vs_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\vs_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\vs_csp.obj"	"$(INTDIR)\vs_csp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\vs_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\vs_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\vs_tpm_csp.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\vs_tpm_csp.obj"	"$(INTDIR)\vs_tpm_csp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\vs_tpm_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\vs_tpm_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\vs_tpm_csp.obj"	"$(INTDIR)\vs_tpm_csp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\vs_tpm_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\vs_tpm_csp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\certinfo.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\certinfo.obj"	"$(INTDIR)\certinfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\certinfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\certinfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\certinfo.obj"	"$(INTDIR)\certinfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\certinfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\certinfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\ExportP12.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\ExportP12.obj"	"$(INTDIR)\ExportP12.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\ExportP12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\ExportP12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\ExportP12.obj"	"$(INTDIR)\ExportP12.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\ExportP12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\ExportP12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\FindPrimes.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\FindPrimes.obj"	"$(INTDIR)\FindPrimes.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\FindPrimes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\FindPrimes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\FindPrimes.obj"	"$(INTDIR)\FindPrimes.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\FindPrimes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\FindPrimes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\langutils.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\langutils.obj"	"$(INTDIR)\langutils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\langutils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\langutils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\langutils.obj"	"$(INTDIR)\langutils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\langutils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\langutils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\MyUniversalInteger.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\MyUniversalInteger.obj"	"$(INTDIR)\MyUniversalInteger.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\MyUniversalInteger.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\MyUniversalInteger.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\MyUniversalInteger.obj"	"$(INTDIR)\MyUniversalInteger.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\MyUniversalInteger.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\MyUniversalInteger.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\P12Helper.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\P12Helper.obj"	"$(INTDIR)\P12Helper.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\P12Helper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\P12Helper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\P12Helper.obj"	"$(INTDIR)\P12Helper.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\P12Helper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\P12Helper.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\pkcs12info.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\pkcs12info.obj"	"$(INTDIR)\pkcs12info.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\pkcs12info.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\pkcs12info.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\pkcs12info.obj"	"$(INTDIR)\pkcs12info.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\pkcs12info.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\pkcs12info.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PtaEngine.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\PtaEngine.obj"	"$(INTDIR)\PtaEngine.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\PtaEngine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\PtaEngine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\PtaEngine.obj"	"$(INTDIR)\PtaEngine.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\PtaEngine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\PtaEngine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\PTAUI.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\PTAUI.obj"	"$(INTDIR)\PTAUI.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\PTAUI.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\PTAUI.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\PTAUI.obj"	"$(INTDIR)\PTAUI.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\PTAUI.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\PTAUI.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Source\Ptav3.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\Ptav3.obj"	"$(INTDIR)\Ptav3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\Ptav3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\Ptav3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\Ptav3.obj"	"$(INTDIR)\Ptav3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\source\export_i.c" ".\source\roamprefs_i.c" ".\Source\certprefs_i.c" ".\source\ptav3_i.c" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Source\ptadllapi_i.c" ".\source\srchcrit_i.c" ".\Source\profmgmt_i.c" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h" ".\source\import_i.c" ".\source\seldigid_i.c" ".\source\uiprefs_i.c"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\Ptav3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\Ptav3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\utils.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\utils.obj"	"$(INTDIR)\utils.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\utils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\virtualsmartcard.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\virtualsmartcard.obj"	"$(INTDIR)\virtualsmartcard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\virtualsmartcard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\virtualsmartcard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\virtualsmartcard.obj"	"$(INTDIR)\virtualsmartcard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\virtualsmartcard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\virtualsmartcard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\vscapi.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\vscapi.obj"	"$(INTDIR)\vscapi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\vscapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\vscapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\vscapi.obj"	"$(INTDIR)\vscapi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\vscapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\vscapi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Source\VSPTA.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\VSPTA.obj"	"$(INTDIR)\VSPTA.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\VSPTA.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\VSPTA.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\VSPTA.obj"	"$(INTDIR)\VSPTA.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\uiprefs.h" ".\include\srchcrit.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\VSPTA.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\VSPTA.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\roots.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\roots.obj"	"$(INTDIR)\roots.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\roots.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\roots.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\roots.obj"	"$(INTDIR)\roots.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch" ".\Include\import.h" ".\Include\certprefs.h" ".\include\roamprefs.h" ".\Include\export.h" ".\Include\ptav3.h" ".\include\seldigid.h" ".\Include\profmgmt.h" ".\Include\ptadllapi.h" ".\include\srchcrit.h" ".\include\uiprefs.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\roots.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\roots.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Ptav3.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\source\Ptav3.rc

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"


"$(INTDIR)\Ptav3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Ptav3.res" /i "source" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"


"$(INTDIR)\Ptav3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Ptav3.res" /i "source" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"


"$(INTDIR)\Ptav3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Ptav3.res" /i "source" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"


"$(INTDIR)\Ptav3.res" : $(SOURCE) "$(INTDIR)" ".\ptav3.tlb"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Ptav3.res" /i "source" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"


"$(INTDIR)\Ptav3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Ptav3.res" /i "source" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"


"$(INTDIR)\Ptav3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\Ptav3.res" /i "source" /d "NDEBUG" $(SOURCE)


!ENDIF 

SOURCE=.\Source\StdAfx.cpp

!IF  "$(CFG)" == "Ptav3 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /Gi /ZI /Od /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "..\..\..\..\modules\RoamingClient\include" /I "..\..\..\..\modules\VS_IBMTSS\include" /I "i:\Platform SDK\include" /I "i:\TSS SDK\IBM\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D VS_TSSDLL=1 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptav3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Ptav3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\Ptav3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Ptav3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Ptav3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Ptav3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /O1 /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "..\..\..\..\modules\RoamingClient\include" /I "..\..\..\..\modules\VS_IBMTSS\include" /I "i:\TSS SDK\IBM\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D VS_TSSDLL=1 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Ptav3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Ptav3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\Ptav3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Ptav3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Ptav3 - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I ".\Inlcude" /I "Include\\" /I "roaminclude" /I "..\..\..\..\..\vsrm\vsrmclientconsole\include" /I "include" /I "..\..\..\..\modules\BSafeLite\include" /I "..\..\..\..\modules\ProtectedStorage\include" /I "..\..\..\..\..\common\simder\include" /I "i:\RoamingSDK\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\Ptav3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Ptav3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


# Microsoft Developer Studio Generated NMAKE File, Based on VSSC.dsp
!IF "$(CFG)" == ""
CFG=VSSC - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VSSC - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VSSC - Win32 Debug" && "$(CFG)" != "VSSC - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "VSSC - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VSSC.dll" "$(OUTDIR)\VSSC.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AppContext.obj"
	-@erase "$(INTDIR)\AppContext.sbr"
	-@erase "$(INTDIR)\AttachInfo.obj"
	-@erase "$(INTDIR)\AttachInfo.sbr"
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\certmgmt.sbr"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Msg.sbr"
	-@erase "$(INTDIR)\Post.obj"
	-@erase "$(INTDIR)\Post.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\UserInfo.obj"
	-@erase "$(INTDIR)\UserInfo.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VSSC.obj"
	-@erase "$(INTDIR)\VSSC.pch"
	-@erase "$(INTDIR)\VSSC.res"
	-@erase "$(INTDIR)\VSSC.sbr"
	-@erase "$(INTDIR)\vssc_pta.obj"
	-@erase "$(INTDIR)\vssc_pta.sbr"
	-@erase "$(INTDIR)\VSSC_SMIME.OBJ"
	-@erase "$(INTDIR)\VSSC_SMIME.SBR"
	-@erase "$(INTDIR)\vssc_util.obj"
	-@erase "$(INTDIR)\vssc_util.sbr"
	-@erase "$(INTDIR)\VSSMC.obj"
	-@erase "$(INTDIR)\VSSMC.sbr"
	-@erase "$(OUTDIR)\VSSC.bsc"
	-@erase "$(OUTDIR)\VSSC.dll"
	-@erase "$(OUTDIR)\VSSC.exp"
	-@erase "$(OUTDIR)\VSSC.ilk"
	-@erase "$(OUTDIR)\VSSC.lib"
	-@erase "$(OUTDIR)\VSSC.pdb"
	-@erase ".\vssc.h"
	-@erase ".\VSSC.tlb"
	-@erase ".\vssc_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "include" /I "..\..\..\..\..\common\utils\include" /I "..\..\..\..\..\common\scmodules\pkcs7engine\include" /I "..\..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\..\common\gmemmgmt\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\..\itgclient\client\modules\bsafelite\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VSSC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VSSC.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSSC.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AppContext.sbr" \
	"$(INTDIR)\AttachInfo.sbr" \
	"$(INTDIR)\certmgmt.sbr" \
	"$(INTDIR)\Msg.sbr" \
	"$(INTDIR)\Post.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\UserInfo.sbr" \
	"$(INTDIR)\VSSC.sbr" \
	"$(INTDIR)\vssc_pta.sbr" \
	"$(INTDIR)\VSSC_SMIME.SBR" \
	"$(INTDIR)\vssc_util.sbr" \
	"$(INTDIR)\VSSMC.sbr"

"$(OUTDIR)\VSSC.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib Version.lib crypt32.lib ..\..\..\..\..\common\lib\debug\mimeengine.lib ..\..\..\..\..\common\lib\debug\utils.lib ..\..\..\..\..\common\lib\debug\gmemmgmt.lib ..\..\..\..\..\common\lib\debug\pkcs7engine.lib ..\..\..\..\..\common\lib\debug\simder.lib ..\..\..\..\..\..\itgclient\client\modules\lib\static\debug\bsafelite.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\VSSC.pdb" /debug /machine:I386 /def:".\VSSC.def" /out:"$(OUTDIR)\VSSC.dll" /implib:"$(OUTDIR)\VSSC.lib" 
DEF_FILE= \
	".\VSSC.def"
LINK32_OBJS= \
	"$(INTDIR)\AppContext.obj" \
	"$(INTDIR)\AttachInfo.obj" \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Post.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UserInfo.obj" \
	"$(INTDIR)\VSSC.obj" \
	"$(INTDIR)\vssc_pta.obj" \
	"$(INTDIR)\VSSC_SMIME.OBJ" \
	"$(INTDIR)\vssc_util.obj" \
	"$(INTDIR)\VSSMC.obj" \
	"$(INTDIR)\VSSC.res"

"$(OUTDIR)\VSSC.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\VSSC.dll
InputPath=.\Debug\VSSC.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\VSSC.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\AppContext.obj"
	-@erase "$(INTDIR)\AttachInfo.obj"
	-@erase "$(INTDIR)\certmgmt.obj"
	-@erase "$(INTDIR)\Msg.obj"
	-@erase "$(INTDIR)\Post.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\UserInfo.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VSSC.obj"
	-@erase "$(INTDIR)\VSSC.pch"
	-@erase "$(INTDIR)\VSSC.res"
	-@erase "$(INTDIR)\vssc_pta.obj"
	-@erase "$(INTDIR)\VSSC_SMIME.OBJ"
	-@erase "$(INTDIR)\vssc_util.obj"
	-@erase "$(INTDIR)\VSSMC.obj"
	-@erase "$(OUTDIR)\VSSC.dll"
	-@erase "$(OUTDIR)\VSSC.exp"
	-@erase "$(OUTDIR)\VSSC.lib"
	-@erase "$(OUTDIR)\VSSC.map"
	-@erase ".\vssc.h"
	-@erase ".\VSSC.tlb"
	-@erase ".\vssc_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /Zd /O1 /I ".\\" /I "include" /I "..\..\..\..\..\common\utils\include" /I "..\..\..\..\..\common\scmodules\pkcs7engine\include" /I "..\..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\..\common\gmemmgmt\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\..\itgclient\client\modules\bsafelite\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VSSC.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VSSC.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSSC.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wininet.lib Version.lib crypt32.lib ..\..\..\..\..\common\lib\release\mimeengine.lib ..\..\..\..\..\common\lib\release\utils.lib ..\..\..\..\..\common\lib\release\gmemmgmt.lib ..\..\..\..\..\common\lib\release\pkcs7engine.lib ..\..\..\..\..\common\lib\release\simder.lib ..\..\..\..\..\..\itgclient\client\modules\lib\static\release\bsafelite.lib /nologo /subsystem:windows /dll /profile /map:"$(INTDIR)\VSSC.map" /debug /machine:I386 /def:".\VSSC.def" /out:"$(OUTDIR)\VSSC.dll" /implib:"$(OUTDIR)\VSSC.lib" 
DEF_FILE= \
	".\VSSC.def"
LINK32_OBJS= \
	"$(INTDIR)\AppContext.obj" \
	"$(INTDIR)\AttachInfo.obj" \
	"$(INTDIR)\certmgmt.obj" \
	"$(INTDIR)\Msg.obj" \
	"$(INTDIR)\Post.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\UserInfo.obj" \
	"$(INTDIR)\VSSC.obj" \
	"$(INTDIR)\vssc_pta.obj" \
	"$(INTDIR)\VSSC_SMIME.OBJ" \
	"$(INTDIR)\vssc_util.obj" \
	"$(INTDIR)\VSSMC.obj" \
	"$(INTDIR)\VSSC.res"

"$(OUTDIR)\VSSC.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VSSC.dll
InputPath=.\ReleaseMinDependency\VSSC.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VSSC.dep")
!INCLUDE "VSSC.dep"
!ELSE 
!MESSAGE Warning: cannot find "VSSC.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VSSC - Win32 Debug" || "$(CFG)" == "VSSC - Win32 Release MinDependency"
SOURCE=.\sources\AppContext.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\AppContext.obj"	"$(INTDIR)\AppContext.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\AppContext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\AttachInfo.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\AttachInfo.obj"	"$(INTDIR)\AttachInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\AttachInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\certmgmt.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\certmgmt.obj"	"$(INTDIR)\certmgmt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\certmgmt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\Msg.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\Msg.obj"	"$(INTDIR)\Msg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\Msg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\Post.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\Post.obj"	"$(INTDIR)\Post.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\Post.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\StdAfx.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\\" /I "include" /I "..\..\..\..\..\common\utils\include" /I "..\..\..\..\..\common\scmodules\pkcs7engine\include" /I "..\..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\..\common\gmemmgmt\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\..\itgclient\client\modules\bsafelite\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VSSC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\VSSC.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MD /W3 /GX /Zd /O1 /I ".\\" /I "include" /I "..\..\..\..\..\common\utils\include" /I "..\..\..\..\..\common\scmodules\pkcs7engine\include" /I "..\..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\..\common\gmemmgmt\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\..\itgclient\client\modules\bsafelite\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\VSSC.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VSSC.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\sources\UserInfo.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\UserInfo.obj"	"$(INTDIR)\UserInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\UserInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\VSSC.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\VSSC.obj"	"$(INTDIR)\VSSC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch" ".\vssc.h" ".\vssc_i.c"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\VSSC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch" ".\vssc_i.c" ".\vssc.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\VSSC.idl

!IF  "$(CFG)" == "VSSC - Win32 Debug"

MTL_SWITCHES=/tlb "VSSC.tlb" /h "vssc.h" /iid "vssc_i.c" /Oicf 

".\VSSC.tlb"	".\vssc.h"	".\vssc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\VSSC.tlb" /h "vssc.h" /iid "vssc_i.c" /Oicf 

".\VSSC.tlb"	".\vssc.h"	".\vssc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VSSC.rc

"$(INTDIR)\VSSC.res" : $(SOURCE) "$(INTDIR)" ".\VSSC.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\sources\vssc_pta.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\vssc_pta.obj"	"$(INTDIR)\vssc_pta.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\vssc_pta.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\VSSC_SMIME.CPP

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\VSSC_SMIME.OBJ"	"$(INTDIR)\VSSC_SMIME.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\VSSC_SMIME.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vssc_util.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\vssc_util.obj"	"$(INTDIR)\vssc_util.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\vssc_util.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\VSSMC.cpp

!IF  "$(CFG)" == "VSSC - Win32 Debug"


"$(INTDIR)\VSSMC.obj"	"$(INTDIR)\VSSMC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch" ".\vssc.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VSSC - Win32 Release MinDependency"


"$(INTDIR)\VSSMC.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VSSC.pch" ".\vssc.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


# Microsoft Developer Studio Generated NMAKE File, Based on VGSE.dsp
!IF "$(CFG)" == ""
CFG=VGSE - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VGSE - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VGSE - Win32 Debug" && "$(CFG)" != "VGSE - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VGSE.mak" CFG="VGSE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VGSE - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VGSE - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "VGSE - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VSGSE.dll" "$(OUTDIR)\VGSE.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ProfAdmin.obj"
	-@erase "$(INTDIR)\ProfAdmin.sbr"
	-@erase "$(INTDIR)\signatrb_i.obj"
	-@erase "$(INTDIR)\signatrb_i.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VGSE.obj"
	-@erase "$(INTDIR)\VGSE.pch"
	-@erase "$(INTDIR)\VGSE.res"
	-@erase "$(INTDIR)\VGSE.sbr"
	-@erase "$(INTDIR)\VSGSE.obj"
	-@erase "$(INTDIR)\VSGSE.sbr"
	-@erase "$(INTDIR)\VSGSEOffice.obj"
	-@erase "$(INTDIR)\VSGSEOffice.sbr"
	-@erase "$(INTDIR)\VSGSEOutlook.obj"
	-@erase "$(INTDIR)\VSGSEOutlook.sbr"
	-@erase "$(INTDIR)\vsgseutil.obj"
	-@erase "$(INTDIR)\vsgseutil.sbr"
	-@erase "$(OUTDIR)\VGSE.bsc"
	-@erase "$(OUTDIR)\VSGSE.dll"
	-@erase "$(OUTDIR)\VSGSE.exp"
	-@erase "$(OUTDIR)\VSGSE.ilk"
	-@erase "$(OUTDIR)\VSGSE.lib"
	-@erase "$(OUTDIR)\VSGSE.pdb"
	-@erase ".\VGSE.h"
	-@erase ".\VGSE.tlb"
	-@erase ".\VGSE_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/MTd /W3 /Gm /GX /ZI /Od /I "./IDLFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VGSE.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /GZ "_DEBUG" /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VGSE.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VGSE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ProfAdmin.sbr" \
	"$(INTDIR)\signatrb_i.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\VGSE.sbr" \
	"$(INTDIR)\VSGSE.sbr" \
	"$(INTDIR)\VSGSEOffice.sbr" \
	"$(INTDIR)\VSGSEOutlook.sbr" \
	"$(INTDIR)\vsgseutil.sbr"

"$(OUTDIR)\VGSE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mapi32.lib wldap32.lib comsupp.lib Edkdebug.lib msvcrtd.lib Version.lib wsock32.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\VSGSE.pdb" /debug /machine:I386 /def:".\VGSE.def" /out:"$(OUTDIR)\VSGSE.dll" /implib:"$(OUTDIR)\VSGSE.lib" /pdbtype:sept 
DEF_FILE= \
	".\VGSE.def"
LINK32_OBJS= \
	"$(INTDIR)\ProfAdmin.obj" \
	"$(INTDIR)\signatrb_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VGSE.obj" \
	"$(INTDIR)\VSGSE.obj" \
	"$(INTDIR)\VSGSEOffice.obj" \
	"$(INTDIR)\VSGSEOutlook.obj" \
	"$(INTDIR)\vsgseutil.obj" \
	"$(INTDIR)\VGSE.res"

"$(OUTDIR)\VSGSE.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\VSGSE.dll
InputPath=.\Debug\VSGSE.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\VSGSE.dll" "$(OUTDIR)\VGSE.pch" ".\VGSE.tlb" ".\VGSE.h" ".\VGSE_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ProfAdmin.obj"
	-@erase "$(INTDIR)\signatrb_i.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VGSE.obj"
	-@erase "$(INTDIR)\VGSE.pch"
	-@erase "$(INTDIR)\VGSE.res"
	-@erase "$(INTDIR)\VSGSE.obj"
	-@erase "$(INTDIR)\VSGSEOffice.obj"
	-@erase "$(INTDIR)\VSGSEOutlook.obj"
	-@erase "$(INTDIR)\vsgseutil.obj"
	-@erase "$(OUTDIR)\VSGSE.dll"
	-@erase "$(OUTDIR)\VSGSE.exp"
	-@erase "$(OUTDIR)\VSGSE.lib"
	-@erase ".\VGSE.h"
	-@erase ".\VGSE.tlb"
	-@erase ".\VGSE_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "./IDLFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VGSE.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VGSE.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comsupp.lib mapi32.lib wldap32.lib MSVCRT.lib Version.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VSGSE.pdb" /machine:I386 /def:".\VGSE.def" /out:"$(OUTDIR)\VSGSE.dll" /implib:"$(OUTDIR)\VSGSE.lib" 
DEF_FILE= \
	".\VGSE.def"
LINK32_OBJS= \
	"$(INTDIR)\ProfAdmin.obj" \
	"$(INTDIR)\signatrb_i.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\VGSE.obj" \
	"$(INTDIR)\VSGSE.obj" \
	"$(INTDIR)\VSGSEOffice.obj" \
	"$(INTDIR)\VSGSEOutlook.obj" \
	"$(INTDIR)\vsgseutil.obj" \
	"$(INTDIR)\VGSE.res"

"$(OUTDIR)\VSGSE.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VSGSE.dll
InputPath=.\ReleaseMinDependency\VSGSE.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
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
!IF EXISTS("VGSE.dep")
!INCLUDE "VGSE.dep"
!ELSE 
!MESSAGE Warning: cannot find "VGSE.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VGSE - Win32 Debug" || "$(CFG)" == "VGSE - Win32 Release MinDependency"
SOURCE=.\ProfAdmin.cpp

!IF  "$(CFG)" == "VGSE - Win32 Debug"


"$(INTDIR)\ProfAdmin.obj"	"$(INTDIR)\ProfAdmin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VGSE.pch"


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"


"$(INTDIR)\ProfAdmin.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\signatrb_i.c

!IF  "$(CFG)" == "VGSE - Win32 Debug"

CPP_SWITCHES=/MTd /W3 /Gm /GX /ZI /Od /I "./IDLFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /GZ "_DEBUG" /c 

"$(INTDIR)\signatrb_i.obj"	"$(INTDIR)\signatrb_i.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "./IDLFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\signatrb_i.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "VGSE - Win32 Debug"

CPP_SWITCHES=/MTd /W3 /Gm /GX /ZI /Od /I "./IDLFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VGSE.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /GZ "_DEBUG" /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\VGSE.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "./IDLFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\VGSE.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\VGSE.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\VGSE.cpp

!IF  "$(CFG)" == "VGSE - Win32 Debug"


"$(INTDIR)\VGSE.obj"	"$(INTDIR)\VGSE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VGSE.pch" ".\VGSE.h" ".\VGSE_i.c"


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"


"$(INTDIR)\VGSE.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\VGSE.idl
MTL_SWITCHES=/tlb ".\VGSE.tlb" /h "VGSE.h" /iid "VGSE_i.c" /Oicf 

".\VGSE.tlb"	".\VGSE.h"	".\VGSE_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\VGSE.rc

"$(INTDIR)\VGSE.res" : $(SOURCE) "$(INTDIR)" ".\VGSE.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\VSGSE.cpp

!IF  "$(CFG)" == "VGSE - Win32 Debug"


"$(INTDIR)\VSGSE.obj"	"$(INTDIR)\VSGSE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VGSE.pch" ".\VGSE.h"


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"


"$(INTDIR)\VSGSE.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\IDlFiles\VSGSEOffice.c

!IF  "$(CFG)" == "VGSE - Win32 Debug"

CPP_SWITCHES=/MTd /W3 /Gm /GX /ZI /Od /I "./IDLFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /GZ "_DEBUG" /c 

"$(INTDIR)\VSGSEOffice.obj"	"$(INTDIR)\VSGSEOffice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "./IDLFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\VSGSEOffice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\IDlFiles\VSGSEOutlook.c

!IF  "$(CFG)" == "VGSE - Win32 Debug"

CPP_SWITCHES=/MTd /W3 /Gm /GX /ZI /Od /I "./IDLFiles" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /D /GZ "_DEBUG" /c 

"$(INTDIR)\VSGSEOutlook.obj"	"$(INTDIR)\VSGSEOutlook.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "./IDLFiles" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\VSGSEOutlook.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\vsgseutil.cpp

!IF  "$(CFG)" == "VGSE - Win32 Debug"


"$(INTDIR)\vsgseutil.obj"	"$(INTDIR)\vsgseutil.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\VGSE.pch"


!ELSEIF  "$(CFG)" == "VGSE - Win32 Release MinDependency"


"$(INTDIR)\vsgseutil.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 


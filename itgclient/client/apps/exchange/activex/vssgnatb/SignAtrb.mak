# Microsoft Developer Studio Generated NMAKE File, Based on SignAtrb.dsp
!IF "$(CFG)" == ""
CFG=SignAtrb - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SignAtrb - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SignAtrb - Win32 Debug" && "$(CFG)" != "SignAtrb - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SignAtrb.mak" CFG="SignAtrb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SignAtrb - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SignAtrb - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SignAtrb - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SignAtrb.dll" "$(OUTDIR)\SignAtrb.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\SignAtrb.obj"
	-@erase "$(INTDIR)\SignAtrb.pch"
	-@erase "$(INTDIR)\SignAtrb.res"
	-@erase "$(INTDIR)\SignAtrb.sbr"
	-@erase "$(INTDIR)\SignAttributes.obj"
	-@erase "$(INTDIR)\SignAttributes.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SignAtrb.bsc"
	-@erase "$(OUTDIR)\SignAtrb.dll"
	-@erase "$(OUTDIR)\SignAtrb.exp"
	-@erase "$(OUTDIR)\SignAtrb.ilk"
	-@erase "$(OUTDIR)\SignAtrb.lib"
	-@erase "$(OUTDIR)\SignAtrb.pdb"
	-@erase ".\SignAtrb.h"
	-@erase ".\SignAtrb.tlb"
	-@erase ".\SignAtrb_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "..\..\..\..\..\common\simder\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SignAtrb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SignAtrb.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SignAtrb.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\SignAtrb.sbr" \
	"$(INTDIR)\SignAttributes.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SignAtrb.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib crypt32.lib simder.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\SignAtrb.pdb" /debug /machine:I386 /def:".\SignAtrb.def" /out:"$(OUTDIR)\SignAtrb.dll" /implib:"$(OUTDIR)\SignAtrb.lib" /pdbtype:sept /libpath:"..\..\..\..\..\common\lib\debug" 
DEF_FILE= \
	".\SignAtrb.def"
LINK32_OBJS= \
	"$(INTDIR)\SignAtrb.obj" \
	"$(INTDIR)\SignAttributes.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SignAtrb.res"

"$(OUTDIR)\SignAtrb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\SignAtrb.dll
InputPath=.\Debug\SignAtrb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "SignAtrb - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\SignAtrb.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\SignAtrb.obj"
	-@erase "$(INTDIR)\SignAtrb.pch"
	-@erase "$(INTDIR)\SignAtrb.res"
	-@erase "$(INTDIR)\SignAttributes.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SignAtrb.dll"
	-@erase "$(OUTDIR)\SignAtrb.exp"
	-@erase "$(OUTDIR)\SignAtrb.lib"
	-@erase ".\SignAtrb.h"
	-@erase ".\SignAtrb.tlb"
	-@erase ".\SignAtrb_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /O1 /I "..\..\..\..\..\common\simder\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\SignAtrb.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SignAtrb.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SignAtrb.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib crypt32.lib simder.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\SignAtrb.pdb" /machine:I386 /def:".\SignAtrb.def" /out:"$(OUTDIR)\SignAtrb.dll" /implib:"$(OUTDIR)\SignAtrb.lib" /libpath:"..\..\..\..\..\common\lib\release" 
DEF_FILE= \
	".\SignAtrb.def"
LINK32_OBJS= \
	"$(INTDIR)\SignAtrb.obj" \
	"$(INTDIR)\SignAttributes.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SignAtrb.res"

"$(OUTDIR)\SignAtrb.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\SignAtrb.dll
InputPath=.\ReleaseMinDependency\SignAtrb.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SignAtrb.dep")
!INCLUDE "SignAtrb.dep"
!ELSE 
!MESSAGE Warning: cannot find "SignAtrb.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SignAtrb - Win32 Debug" || "$(CFG)" == "SignAtrb - Win32 Release MinDependency"
SOURCE=.\SignAtrb.cpp

!IF  "$(CFG)" == "SignAtrb - Win32 Debug"


"$(INTDIR)\SignAtrb.obj"	"$(INTDIR)\SignAtrb.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SignAtrb.pch" ".\SignAtrb_i.c" ".\SignAtrb.h"


!ELSEIF  "$(CFG)" == "SignAtrb - Win32 Release MinDependency"


"$(INTDIR)\SignAtrb.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SignAtrb.pch" ".\SignAtrb_i.c" ".\SignAtrb.h"


!ENDIF 

SOURCE=.\SignAtrb.idl

!IF  "$(CFG)" == "SignAtrb - Win32 Debug"

MTL_SWITCHES=/tlb ".\SignAtrb.tlb" /h "SignAtrb.h" /iid "SignAtrb_i.c" /Oicf 

".\SignAtrb.tlb"	".\SignAtrb.h"	".\SignAtrb_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SignAtrb - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\SignAtrb.tlb" /h "SignAtrb.h" /iid "SignAtrb_i.c" /Oicf 

".\SignAtrb.tlb"	".\SignAtrb.h"	".\SignAtrb_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SignAtrb.rc

"$(INTDIR)\SignAtrb.res" : $(SOURCE) "$(INTDIR)" ".\SignAtrb.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SignAttributes.cpp

!IF  "$(CFG)" == "SignAtrb - Win32 Debug"


"$(INTDIR)\SignAttributes.obj"	"$(INTDIR)\SignAttributes.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SignAtrb.pch" ".\SignAtrb.h"


!ELSEIF  "$(CFG)" == "SignAtrb - Win32 Release MinDependency"


"$(INTDIR)\SignAttributes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SignAtrb.pch" ".\SignAtrb.h"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SignAtrb - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /ZI /Od /I "..\..\..\..\..\common\simder\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SignAtrb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SignAtrb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SignAtrb - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "..\..\..\..\..\common\simder\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\SignAtrb.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SignAtrb.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


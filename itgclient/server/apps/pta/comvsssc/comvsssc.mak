# Microsoft Developer Studio Generated NMAKE File, Based on comvsssc.dsp
!IF "$(CFG)" == ""
CFG=comvsssc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to comvsssc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "comvsssc - Win32 Debug" && "$(CFG)" != "comvsssc - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "comvsssc.mak" CFG="comvsssc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "comvsssc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "comvsssc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "comvsssc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\comvsssc.exe" "$(OUTDIR)\comvsssc.pch" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\comvsssc.obj"
	-@erase "$(INTDIR)\comvsssc.pch"
	-@erase "$(INTDIR)\comvsssc.res"
	-@erase "$(INTDIR)\ptautil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsVerify.obj"
	-@erase "$(OUTDIR)\comvsssc.exe"
	-@erase "$(OUTDIR)\comvsssc.ilk"
	-@erase "$(OUTDIR)\comvsssc.pdb"
	-@erase ".\comvsssc.h"
	-@erase ".\comvsssc.tlb"
	-@erase ".\comvsssc_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../../../thirdparty/vsvalsdk/include" /I "../source" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\comvsssc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\comvsssc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\comvsssc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../source/make/libvsssc/dynamic/winnt-debug/libvsssc.lib ../../../../thirdparty/vsvalsdk/lib/winnt/libvsvalsdk.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\comvsssc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\comvsssc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\comvsssc.obj" \
	"$(INTDIR)\ptautil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsVerify.obj" \
	"$(INTDIR)\comvsssc.res"

"$(OUTDIR)\comvsssc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\comvsssc.exe
InputPath=.\Debug\comvsssc.exe
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
<< 
	

!ELSEIF  "$(CFG)" == "comvsssc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\comvsssc.exe" ".\comvsssc.tlb" ".\comvsssc.h" ".\comvsssc_i.c" "$(OUTDIR)\comvsssc.pch"


CLEAN :
	-@erase "$(INTDIR)\comvsssc.obj"
	-@erase "$(INTDIR)\comvsssc.pch"
	-@erase "$(INTDIR)\comvsssc.res"
	-@erase "$(INTDIR)\ptautil.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsVerify.obj"
	-@erase "$(OUTDIR)\comvsssc.exe"
	-@erase "$(OUTDIR)\comvsssc.ilk"
	-@erase ".\comvsssc.h"
	-@erase ".\comvsssc.tlb"
	-@erase ".\comvsssc_i.c"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /I "../../../../thirdparty/vsvalsdk/include" /I "../source" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\comvsssc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\comvsssc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../source/make/libvsssc/dynamic/winnt-release/libvsssc.lib ../../../../thirdparty/vsvalsdk/lib/winnt/libvsvalsdk.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\comvsssc.pdb" /machine:I386 /out:"$(OUTDIR)\comvsssc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\comvsssc.obj" \
	"$(INTDIR)\ptautil.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsVerify.obj" \
	"$(INTDIR)\comvsssc.res"

"$(OUTDIR)\comvsssc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("comvsssc.dep")
!INCLUDE "comvsssc.dep"
!ELSE 
!MESSAGE Warning: cannot find "comvsssc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "comvsssc - Win32 Debug" || "$(CFG)" == "comvsssc - Win32 Release"
SOURCE=.\comvsssc.cpp

"$(INTDIR)\comvsssc.obj" : $(SOURCE) "$(INTDIR)" ".\comvsssc.h" ".\comvsssc_i.c"


SOURCE=.\comvsssc.idl

!IF  "$(CFG)" == "comvsssc - Win32 Debug"

MTL_SWITCHES=/tlb ".\comvsssc.tlb" /h "comvsssc.h" /iid "comvsssc_i.c" /Oicf 

".\comvsssc.tlb"	".\comvsssc.h"	".\comvsssc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "comvsssc - Win32 Release"

MTL_SWITCHES=/tlb ".\comvsssc.tlb" /h "comvsssc.h" /iid "comvsssc_i.c" /Oicf 

".\comvsssc.tlb"	".\comvsssc.h"	".\comvsssc_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\comvsssc.rc

"$(INTDIR)\comvsssc.res" : $(SOURCE) "$(INTDIR)" ".\comvsssc.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\source\ptautil.cpp

"$(INTDIR)\ptautil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "comvsssc - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../../../thirdparty/vsvalsdk/include" /I "../source" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\comvsssc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\comvsssc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "comvsssc - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /I "../../../../thirdparty/vsvalsdk/include" /I "../source" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\comvsssc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\comvsssc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\vsVerify.cpp

"$(INTDIR)\vsVerify.obj" : $(SOURCE) "$(INTDIR)" ".\comvsssc.h"



!ENDIF 


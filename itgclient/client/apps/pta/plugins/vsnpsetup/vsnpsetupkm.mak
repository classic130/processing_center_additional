# Microsoft Developer Studio Generated NMAKE File, Based on vsnpsetupkm.dsp
!IF "$(CFG)" == ""
CFG=vsnpsetupkm - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vsnpsetupkm - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vsnpsetupkm - Win32 Release" && "$(CFG)" != "vsnpsetupkm - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsnpsetupkm.mak" CFG="vsnpsetupkm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vsnpsetupkm - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vsnpsetupkm - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "vsnpsetupkm - Win32 Release"

OUTDIR=.\ReleaseKM
INTDIR=.\ReleaseKM
# Begin Custom Macros
OutDir=.\ReleaseKM
# End Custom Macros

ALL : "$(OUTDIR)\vsnpsetupkm.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsnpsetupkm.obj"
	-@erase "$(OUTDIR)\vsnpsetupkm.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\vsnpsetupkm.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsnpsetupkm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\vsnpsetupkm.pdb" /machine:I386 /out:"$(OUTDIR)\vsnpsetupkm.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsnpsetupkm.obj"

"$(OUTDIR)\vsnpsetupkm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsnpsetupkm - Win32 Debug"

OUTDIR=.\DebugKM
INTDIR=.\DebugKM
# Begin Custom Macros
OutDir=.\DebugKM
# End Custom Macros

ALL : "$(OUTDIR)\vsnpsetupkm.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsnpsetupkm.obj"
	-@erase "$(OUTDIR)\vsnpsetupkm.exe"
	-@erase "$(OUTDIR)\vsnpsetupkm.ilk"
	-@erase "$(OUTDIR)\vsnpsetupkm.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\vsnpsetupkm.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsnpsetupkm.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\vsnpsetupkm.pdb" /debug /machine:I386 /out:"$(OUTDIR)\vsnpsetupkm.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsnpsetupkm.obj"

"$(OUTDIR)\vsnpsetupkm.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("vsnpsetupkm.dep")
!INCLUDE "vsnpsetupkm.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsnpsetupkm.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vsnpsetupkm - Win32 Release" || "$(CFG)" == "vsnpsetupkm - Win32 Debug"
SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vsnpsetupkm.cpp

"$(INTDIR)\vsnpsetupkm.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 


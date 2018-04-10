# Microsoft Developer Studio Generated NMAKE File, Based on ResolutionLib.dsp
!IF "$(CFG)" == ""
CFG=ResolutionLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ResolutionLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ResolutionLib - Win32 Release" && "$(CFG)" != "ResolutionLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ResolutionLib.mak" CFG="ResolutionLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ResolutionLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ResolutionLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ResolutionLib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ResolutionLib.lib"


CLEAN :
	-@erase "$(INTDIR)\CertResolution.obj"
	-@erase "$(INTDIR)\EmailResolution.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vssc_util.obj"
	-@erase "$(OUTDIR)\ResolutionLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ResolutionLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ResolutionLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ResolutionLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\vssc_util.obj" \
	"$(INTDIR)\EmailResolution.obj" \
	"$(INTDIR)\CertResolution.obj"

"$(OUTDIR)\ResolutionLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ResolutionLib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ResolutionLib.lib"


CLEAN :
	-@erase "$(INTDIR)\CertResolution.obj"
	-@erase "$(INTDIR)\EmailResolution.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vssc_util.obj"
	-@erase "$(OUTDIR)\ResolutionLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ResolutionLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ResolutionLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ResolutionLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\vssc_util.obj" \
	"$(INTDIR)\EmailResolution.obj" \
	"$(INTDIR)\CertResolution.obj"

"$(OUTDIR)\ResolutionLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("ResolutionLib.dep")
!INCLUDE "ResolutionLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "ResolutionLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ResolutionLib - Win32 Release" || "$(CFG)" == "ResolutionLib - Win32 Debug"
SOURCE=.\sources\CertResolution.cpp

"$(INTDIR)\CertResolution.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\EmailResolution.cpp

"$(INTDIR)\EmailResolution.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vssc_util.cpp

"$(INTDIR)\vssc_util.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


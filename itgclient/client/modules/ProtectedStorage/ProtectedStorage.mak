# Microsoft Developer Studio Generated NMAKE File, Based on ProtectedStorage.dsp
!IF "$(CFG)" == ""
CFG=ProtectedStorage - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ProtectedStorage - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ProtectedStorage - Win32 Release" && "$(CFG)" != "ProtectedStorage - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProtectedStorage.mak" CFG="ProtectedStorage - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProtectedStorage - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ProtectedStorage - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ProtectedStorage - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ProtectedStorage.lib"


CLEAN :
	-@erase "$(INTDIR)\PrivateFunctions.obj"
	-@erase "$(INTDIR)\ProtectedStorage.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ProtectedStorage.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /GX /O2 /I "include" /I "..\..\..\common\simder\include" /I "..\BSafeLite\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\ProtectedStorage.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProtectedStorage.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ProtectedStorage.lib" 
LIB32_OBJS= \
	"$(INTDIR)\PrivateFunctions.obj" \
	"$(INTDIR)\ProtectedStorage.obj"

"$(OUTDIR)\ProtectedStorage.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ProtectedStorage.lib"
   if not exist "..\lib\static\release" md "..\lib\static\release"
	copy release\ProtectedStorage.lib "..\lib\static\release"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "ProtectedStorage - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ProtectedStorage.lib" "$(OUTDIR)\ProtectedStorage.bsc"


CLEAN :
	-@erase "$(INTDIR)\PrivateFunctions.obj"
	-@erase "$(INTDIR)\PrivateFunctions.sbr"
	-@erase "$(INTDIR)\ProtectedStorage.obj"
	-@erase "$(INTDIR)\ProtectedStorage.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ProtectedStorage.bsc"
	-@erase "$(OUTDIR)\ProtectedStorage.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W4 /Gm /GX /ZI /Od /I "include" /I "..\..\..\common\simder\include" /I "..\BSafeLite\include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D PLATFORM=VSPS_WIN32 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ProtectedStorage.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ProtectedStorage.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\PrivateFunctions.sbr" \
	"$(INTDIR)\ProtectedStorage.sbr"

"$(OUTDIR)\ProtectedStorage.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ProtectedStorage.lib" 
LIB32_OBJS= \
	"$(INTDIR)\PrivateFunctions.obj" \
	"$(INTDIR)\ProtectedStorage.obj"

"$(OUTDIR)\ProtectedStorage.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\ProtectedStorage.lib" "$(OUTDIR)\ProtectedStorage.bsc"
   if not exist "..\lib\static\debug" md "..\lib\static\debug"
	copy debug\ProtectedStorage.lib "..\lib\static\debug"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ProtectedStorage.dep")
!INCLUDE "ProtectedStorage.dep"
!ELSE 
!MESSAGE Warning: cannot find "ProtectedStorage.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ProtectedStorage - Win32 Release" || "$(CFG)" == "ProtectedStorage - Win32 Debug"
SOURCE=.\src\PrivateFunctions.cpp

!IF  "$(CFG)" == "ProtectedStorage - Win32 Release"


"$(INTDIR)\PrivateFunctions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ProtectedStorage - Win32 Debug"


"$(INTDIR)\PrivateFunctions.obj"	"$(INTDIR)\PrivateFunctions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\ProtectedStorage.cpp

!IF  "$(CFG)" == "ProtectedStorage - Win32 Release"


"$(INTDIR)\ProtectedStorage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ProtectedStorage - Win32 Debug"


"$(INTDIR)\ProtectedStorage.obj"	"$(INTDIR)\ProtectedStorage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


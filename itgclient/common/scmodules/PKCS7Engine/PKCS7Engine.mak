# Microsoft Developer Studio Generated NMAKE File, Based on PKCS7Engine.dsp
!IF "$(CFG)" == ""
CFG=PKCS7Engine - Win32 Debug
!MESSAGE No configuration specified. Defaulting to PKCS7Engine - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PKCS7Engine - Win32 Release" && "$(CFG)" != "PKCS7Engine - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PKCS7Engine.mak" CFG="PKCS7Engine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PKCS7Engine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "PKCS7Engine - Win32 Debug" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "PKCS7Engine - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\PKCS7Engine.lib"


CLEAN :
	-@erase "$(INTDIR)\PKCS7Engine.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PKCS7Engine.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\include" /I "..\..\utils\include" /I "..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\itgclient\client\modules\bsafelite\include" /I "..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\PKCS7Engine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PKCS7Engine.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\PKCS7Engine.lib" 
LIB32_OBJS= \
	"$(INTDIR)\PKCS7Engine.obj"

"$(OUTDIR)\PKCS7Engine.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\PKCS7Engine.lib"
   copy release\pkcs7engine.lib ..\..\lib\release
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "PKCS7Engine - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\PKCS7Engine.lib"


CLEAN :
	-@erase "$(INTDIR)\PKCS7Engine.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PKCS7Engine.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\include" /I "..\..\utils\include" /I "..\..\..\..\itgclient\common\simder\include" /I "..\..\..\..\itgclient\client\modules\bsafelite\include" /I "..\..\..\..\itgclient\client\apps\pta\activex\ptav3\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\PKCS7Engine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PKCS7Engine.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\PKCS7Engine.lib" 
LIB32_OBJS= \
	"$(INTDIR)\PKCS7Engine.obj"

"$(OUTDIR)\PKCS7Engine.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\PKCS7Engine.lib"
   copy debug\pkcs7engine.lib ..\..\lib\debug
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("PKCS7Engine.dep")
!INCLUDE "PKCS7Engine.dep"
!ELSE 
!MESSAGE Warning: cannot find "PKCS7Engine.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PKCS7Engine - Win32 Release" || "$(CFG)" == "PKCS7Engine - Win32 Debug"
SOURCE=.\sources\PKCS7Engine.cpp

"$(INTDIR)\PKCS7Engine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


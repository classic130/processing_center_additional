# Microsoft Developer Studio Generated NMAKE File, Based on vsprs.dsp
!IF "$(CFG)" == ""
CFG=vsprs - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vsprs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vsprs - Win32 Release" && "$(CFG)" != "vsprs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsprs.mak" CFG="vsprs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vsprs - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "vsprs - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "vsprs - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\vsprs.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsprs.obj"
	-@erase "$(INTDIR)\vsprs_pta.obj"
	-@erase "$(INTDIR)\vsprsattachments.obj"
	-@erase "$(OUTDIR)\vsprs.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /I "..\..\..\..\common\utils\include" /I "..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\client\modules\bsafelite\include" /I "..\..\..\..\common\simder\include" /I "..\..\..\..\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\itgclient\client\apps\sc\activex\vssc" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\vsprs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsprs.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\vsprs.lib" 
LIB32_OBJS= \
	"$(INTDIR)\vsprs.obj" \
	"$(INTDIR)\vsprs_pta.obj" \
	"$(INTDIR)\vsprsattachments.obj"

"$(OUTDIR)\vsprs.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsprs - Win32 Debug"

OUTDIR=.\..\lib\static\Debug
INTDIR=.\Debug

ALL : ".\Debug\vsprs.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsprs.obj"
	-@erase "$(INTDIR)\vsprs_pta.obj"
	-@erase "$(INTDIR)\vsprsattachments.obj"
	-@erase ".\Debug\vsprs.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "..\..\..\..\common\utils\include" /I "..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\client\modules\bsafelite\include" /I "..\..\..\..\common\simder\include" /I "..\..\..\..\client\apps\pta\activex\ptav3\include" /I "..\..\..\..\itgclient\client\apps\pta\activex\ptav3\source" /I "..\..\..\..\..\itgclient\client\apps\sc\activex\vssc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\vsprs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsprs.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"Debug\vsprs.lib" 
LIB32_OBJS= \
	"$(INTDIR)\vsprs.obj" \
	"$(INTDIR)\vsprs_pta.obj" \
	"$(INTDIR)\vsprsattachments.obj"

".\Debug\vsprs.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("vsprs.dep")
!INCLUDE "vsprs.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsprs.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vsprs - Win32 Release" || "$(CFG)" == "vsprs - Win32 Debug"
SOURCE=.\sources\vsprs.cpp

"$(INTDIR)\vsprs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsprs_pta.cpp

"$(INTDIR)\vsprs_pta.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsprsattachments.cpp

"$(INTDIR)\vsprsattachments.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


# Microsoft Developer Studio Generated NMAKE File, Based on vsprsauth.dsp
!IF "$(CFG)" == ""
CFG=authdll - Win32 Debug
!MESSAGE No configuration specified. Defaulting to authdll - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "authdll - Win32 Release" && "$(CFG)" != "authdll - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsprsauth.mak" CFG="authdll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "authdll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "authdll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "authdll - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\vsprsauth.dll"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsprsauth.obj"
	-@erase "$(OUTDIR)\vsprsauth.dll"
	-@erase "$(OUTDIR)\vsprsauth.exp"
	-@erase "$(OUTDIR)\vsprsauth.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\lib\include" /I "include" /I "..\policymodule\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AUTHDLL_EXPORTS" /Fp"$(INTDIR)\vsprsauth.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsprsauth.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=policymodule.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\vsprsauth.pdb" /machine:I386 /def:".\vsprsauth.def" /out:"$(OUTDIR)\vsprsauth.dll" /implib:"$(OUTDIR)\vsprsauth.lib" /libpath:"..\..\..\lib\static\release" 
DEF_FILE= \
	".\vsprsauth.def"
LINK32_OBJS= \
	"$(INTDIR)\vsprsauth.obj"

"$(OUTDIR)\vsprsauth.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "authdll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\vsprsauth.dll"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsprsauth.obj"
	-@erase "$(OUTDIR)\vsprsauth.dll"
	-@erase "$(OUTDIR)\vsprsauth.exp"
	-@erase "$(OUTDIR)\vsprsauth.ilk"
	-@erase "$(OUTDIR)\vsprsauth.lib"
	-@erase "$(OUTDIR)\vsprsauth.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "..\policymodule\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "AUTHDLL_EXPORTS" /Fp"$(INTDIR)\vsprsauth.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsprsauth.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=policymodule.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\vsprsauth.pdb" /debug /machine:I386 /def:".\vsprsauth.def" /out:"$(OUTDIR)\vsprsauth.dll" /implib:"$(OUTDIR)\vsprsauth.lib" /pdbtype:sept /libpath:"..\..\..\lib\static\debug" 
DEF_FILE= \
	".\vsprsauth.def"
LINK32_OBJS= \
	"$(INTDIR)\vsprsauth.obj"

"$(OUTDIR)\vsprsauth.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("vsprsauth.dep")
!INCLUDE "vsprsauth.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsprsauth.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "authdll - Win32 Release" || "$(CFG)" == "authdll - Win32 Debug"
SOURCE=.\sources\vsprsauth.cpp

"$(INTDIR)\vsprsauth.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


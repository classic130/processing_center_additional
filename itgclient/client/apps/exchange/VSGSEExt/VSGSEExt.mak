# Microsoft Developer Studio Generated NMAKE File, Based on VSGSEExt.dsp
!IF "$(CFG)" == ""
CFG=VSGSEExt - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VSGSEExt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VSGSEExt - Win32 Release" && "$(CFG)" != "VSGSEExt - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VSGSEExt.mak" CFG="VSGSEExt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VSGSEExt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VSGSEExt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "VSGSEExt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VSGSEExt.dll"


CLEAN :
	-@erase "$(INTDIR)\cmdExt.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VSGSEExt.res"
	-@erase "$(OUTDIR)\VSGSEExt.dll"
	-@erase "$(OUTDIR)\VSGSEExt.exp"
	-@erase "$(OUTDIR)\VSGSEExt.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VSGSEEXT_EXPORTS" /Fp"$(INTDIR)\VSGSEExt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VSGSEExt.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSGSEExt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mapi32.lib EDKMAPI.LIB edkutils.lib msvcrt.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\VSGSEExt.pdb" /machine:I386 /out:"$(OUTDIR)\VSGSEExt.dll" /implib:"$(OUTDIR)\VSGSEExt.lib" 
LINK32_OBJS= \
	"$(INTDIR)\cmdExt.obj" \
	"$(INTDIR)\VSGSEExt.res"

"$(OUTDIR)\VSGSEExt.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VSGSEExt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VSGSEExt.dll"


CLEAN :
	-@erase "$(INTDIR)\cmdExt.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VSGSEExt.res"
	-@erase "$(OUTDIR)\VSGSEExt.dll"
	-@erase "$(OUTDIR)\VSGSEExt.exp"
	-@erase "$(OUTDIR)\VSGSEExt.ilk"
	-@erase "$(OUTDIR)\VSGSEExt.lib"
	-@erase "$(OUTDIR)\VSGSEExt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VSGSEEXT_EXPORTS" /Fp"$(INTDIR)\VSGSEExt.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\VSGSEExt.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VSGSEExt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mapi32.lib EDKMAPI.LIB edkutils.lib msvcrt.lib edkdebug.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\VSGSEExt.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VSGSEExt.dll" /implib:"$(OUTDIR)\VSGSEExt.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\cmdExt.obj" \
	"$(INTDIR)\VSGSEExt.res"

"$(OUTDIR)\VSGSEExt.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("VSGSEExt.dep")
!INCLUDE "VSGSEExt.dep"
!ELSE 
!MESSAGE Warning: cannot find "VSGSEExt.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VSGSEExt - Win32 Release" || "$(CFG)" == "VSGSEExt - Win32 Debug"
SOURCE=.\cmdExt.Cpp

"$(INTDIR)\cmdExt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\VSGSEExt.rc

"$(INTDIR)\VSGSEExt.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 


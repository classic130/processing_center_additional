# Microsoft Developer Studio Generated NMAKE File, Based on VerifySignature.dsp
!IF "$(CFG)" == ""
CFG=VerifySignature - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VerifySignature - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VerifySignature - Win32 Release" && "$(CFG)" != "VerifySignature - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VerifySignature.mak" CFG="VerifySignature - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VerifySignature - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "VerifySignature - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "VerifySignature - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VerifySignature.exe" "$(OUTDIR)\VerifySignature.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VerifySignature.obj"
	-@erase "$(INTDIR)\VerifySignature.sbr"
	-@erase "$(OUTDIR)\VerifySignature.bsc"
	-@erase "$(OUTDIR)\VerifySignature.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VerifySignature.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VerifySignature.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\VerifySignature.sbr"

"$(OUTDIR)\VerifySignature.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\VerifySignature.pdb" /machine:I386 /out:"$(OUTDIR)\VerifySignature.exe" 
LINK32_OBJS= \
	"$(INTDIR)\VerifySignature.obj"

"$(OUTDIR)\VerifySignature.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VerifySignature - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VerifySignature.exe"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VerifySignature.obj"
	-@erase "$(OUTDIR)\VerifySignature.exe"
	-@erase "$(OUTDIR)\VerifySignature.ilk"
	-@erase "$(OUTDIR)\VerifySignature.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\VerifySignature.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VerifySignature.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\VerifySignature.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VerifySignature.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\VerifySignature.obj"

"$(OUTDIR)\VerifySignature.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("VerifySignature.dep")
!INCLUDE "VerifySignature.dep"
!ELSE 
!MESSAGE Warning: cannot find "VerifySignature.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VerifySignature - Win32 Release" || "$(CFG)" == "VerifySignature - Win32 Debug"
SOURCE=..\VerifySignature.cpp

!IF  "$(CFG)" == "VerifySignature - Win32 Release"


"$(INTDIR)\VerifySignature.obj"	"$(INTDIR)\VerifySignature.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VerifySignature - Win32 Debug"


"$(INTDIR)\VerifySignature.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


# Microsoft Developer Studio Generated NMAKE File, Based on SrchExcE.dsp
!IF "$(CFG)" == ""
CFG=SrchExcE - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SrchExcE - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SrchExcE - Win32 Release" && "$(CFG)" != "SrchExcE - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SrchExcE.mak" CFG="SrchExcE - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SrchExcE - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SrchExcE - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SrchExcE - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SrchExcE.exe" "$(OUTDIR)\SrchExcE.bsc"


CLEAN :
	-@erase "$(INTDIR)\fixpath.obj"
	-@erase "$(INTDIR)\fixpath.sbr"
	-@erase "$(INTDIR)\Http.obj"
	-@erase "$(INTDIR)\Http.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\ntfuncs.obj"
	-@erase "$(INTDIR)\ntfuncs.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsstring.obj"
	-@erase "$(INTDIR)\vsstring.sbr"
	-@erase "$(OUTDIR)\SrchExcE.bsc"
	-@erase "$(OUTDIR)\SrchExcE.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "../../include" /I "../../include/atl11" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SrchExcE.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrchExcE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\fixpath.sbr" \
	"$(INTDIR)\Http.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\ntfuncs.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\vsstring.sbr"

"$(OUTDIR)\SrchExcE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib odbc32.lib odbccp32.lib OleDb.lib advapi32.lib user32.lib userenv.lib Wldap32.lib crypt32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SrchExcE.pdb" /machine:I386 /out:"$(OUTDIR)\SrchExcE.exe" 
LINK32_OBJS= \
	"$(INTDIR)\fixpath.obj" \
	"$(INTDIR)\Http.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\ntfuncs.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\vsstring.obj"

"$(OUTDIR)\SrchExcE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SrchExcE - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SrchExcE.exe" "$(OUTDIR)\SrchExcE.bsc"


CLEAN :
	-@erase "$(INTDIR)\fixpath.obj"
	-@erase "$(INTDIR)\fixpath.sbr"
	-@erase "$(INTDIR)\Http.obj"
	-@erase "$(INTDIR)\Http.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\ntfuncs.obj"
	-@erase "$(INTDIR)\ntfuncs.sbr"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\util.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsstring.obj"
	-@erase "$(INTDIR)\vsstring.sbr"
	-@erase "$(OUTDIR)\SrchExcE.bsc"
	-@erase "$(OUTDIR)\SrchExcE.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SrchExcE.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SrchExcE.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\fixpath.sbr" \
	"$(INTDIR)\Http.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\ntfuncs.sbr" \
	"$(INTDIR)\util.sbr" \
	"$(INTDIR)\vsstring.sbr"

"$(OUTDIR)\SrchExcE.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib odbc32.lib odbccp32.lib OleDb.lib advapi32.lib user32.lib userenv.lib Wldap32.lib crypt32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\SrchExcE.pdb" /machine:I386 /out:"$(OUTDIR)\SrchExcE.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\fixpath.obj" \
	"$(INTDIR)\Http.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\ntfuncs.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\vsstring.obj"

"$(OUTDIR)\SrchExcE.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SrchExcE.dep")
!INCLUDE "SrchExcE.dep"
!ELSE 
!MESSAGE Warning: cannot find "SrchExcE.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SrchExcE - Win32 Release" || "$(CFG)" == "SrchExcE - Win32 Debug"
SOURCE=.\fixpath.cpp

"$(INTDIR)\fixpath.obj"	"$(INTDIR)\fixpath.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Http.cpp

"$(INTDIR)\Http.obj"	"$(INTDIR)\Http.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\main.cpp

"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ntfuncs.cpp

"$(INTDIR)\ntfuncs.obj"	"$(INTDIR)\ntfuncs.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\util.cpp

"$(INTDIR)\util.obj"	"$(INTDIR)\util.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vsstring.cpp

"$(INTDIR)\vsstring.obj"	"$(INTDIR)\vsstring.sbr" : $(SOURCE) "$(INTDIR)"



!ENDIF 


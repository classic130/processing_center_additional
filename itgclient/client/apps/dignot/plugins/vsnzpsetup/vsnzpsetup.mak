# Microsoft Developer Studio Generated NMAKE File, Based on vsnzpsetup.dsp
!IF "$(CFG)" == ""
CFG=vsnzpsetup - Win32 Debug Pta
!MESSAGE No configuration specified. Defaulting to vsnzpsetup - Win32 Debug Pta.
!ENDIF 

!IF "$(CFG)" != "vsnzpsetup - Win32 Release" && "$(CFG)" != "vsnzpsetup - Win32 Debug" && "$(CFG)" != "vsnzpsetup - Win32 Release Pta" && "$(CFG)" != "vsnzpsetup - Win32 Debug Pta"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsnzpsetup.mak" CFG="vsnzpsetup - Win32 Debug Pta"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vsnzpsetup - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "vsnzpsetup - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "vsnzpsetup - Win32 Release Pta" (based on "Win32 (x86) Application")
!MESSAGE "vsnzpsetup - Win32 Debug Pta" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "vsnzpsetup - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\vsnzpsetup.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsnzpsetup.obj"
	-@erase "$(INTDIR)\vsnzpsetup.pch"
	-@erase "$(OUTDIR)\vsnzpsetup.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsnzpsetup.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\vsnzpsetup.pdb" /machine:I386 /out:"$(OUTDIR)\vsnzpsetup.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsnzpsetup.obj"

"$(OUTDIR)\vsnzpsetup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsnzpsetup - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\vsnzpsetup.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsnzpsetup.obj"
	-@erase "$(INTDIR)\vsnzpsetup.pch"
	-@erase "$(OUTDIR)\vsnzpsetup.exe"
	-@erase "$(OUTDIR)\vsnzpsetup.ilk"
	-@erase "$(OUTDIR)\vsnzpsetup.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsnzpsetup.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\vsnzpsetup.pdb" /debug /machine:I386 /out:"$(OUTDIR)\vsnzpsetup.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsnzpsetup.obj"

"$(OUTDIR)\vsnzpsetup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsnzpsetup - Win32 Release Pta"

OUTDIR=.\vsnzpsetup___Win32_Release_Pta
INTDIR=.\vsnzpsetup___Win32_Release_Pta
# Begin Custom Macros
OutDir=.\vsnzpsetup___Win32_Release_Pta
# End Custom Macros

ALL : "$(OUTDIR)\vsnzptasetup.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsnzpsetup.obj"
	-@erase "$(INTDIR)\vsnzpsetup.pch"
	-@erase "$(OUTDIR)\vsnzptasetup.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "PTA" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsnzpsetup.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\vsnzptasetup.pdb" /machine:I386 /out:"$(OUTDIR)\vsnzptasetup.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsnzpsetup.obj"

"$(OUTDIR)\vsnzptasetup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsnzpsetup - Win32 Debug Pta"

OUTDIR=.\vsnzpsetup___Win32_Debug_Pta
INTDIR=.\vsnzpsetup___Win32_Debug_Pta
# Begin Custom Macros
OutDir=.\vsnzpsetup___Win32_Debug_Pta
# End Custom Macros

ALL : "$(OUTDIR)\vsnzptasetup.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsnzpsetup.obj"
	-@erase "$(INTDIR)\vsnzpsetup.pch"
	-@erase "$(OUTDIR)\vsnzptasetup.exe"
	-@erase "$(OUTDIR)\vsnzptasetup.ilk"
	-@erase "$(OUTDIR)\vsnzptasetup.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "PTA" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsnzpsetup.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\vsnzptasetup.pdb" /debug /machine:I386 /out:"$(OUTDIR)\vsnzptasetup.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vsnzpsetup.obj"

"$(OUTDIR)\vsnzptasetup.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("vsnzpsetup.dep")
!INCLUDE "vsnzpsetup.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsnzpsetup.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vsnzpsetup - Win32 Release" || "$(CFG)" == "vsnzpsetup - Win32 Debug" || "$(CFG)" == "vsnzpsetup - Win32 Release Pta" || "$(CFG)" == "vsnzpsetup - Win32 Debug Pta"
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "vsnzpsetup - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsnzpsetup.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsnzpsetup - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsnzpsetup.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsnzpsetup - Win32 Release Pta"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "PTA" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsnzpsetup.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "vsnzpsetup - Win32 Debug Pta"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "PTA" /Fp"$(INTDIR)\vsnzpsetup.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\vsnzpsetup.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\vsnzpsetup.cpp

"$(INTDIR)\vsnzpsetup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\vsnzpsetup.pch"



!ENDIF 


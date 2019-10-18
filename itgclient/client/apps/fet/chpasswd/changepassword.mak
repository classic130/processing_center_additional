# Microsoft Developer Studio Generated NMAKE File, Based on changepassword.dsp
!IF "$(CFG)" == ""
CFG=changepassword - Win32 Debug
!MESSAGE No configuration specified. Defaulting to changepassword - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "changepassword - Win32 Release" && "$(CFG)" != "changepassword - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "changepassword.mak" CFG="changepassword - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "changepassword - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "changepassword - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "changepassword - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\chpasswd.exe"


CLEAN :
	-@erase "$(INTDIR)\changepassword.obj"
	-@erase "$(INTDIR)\changepassword.pch"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\chpasswd.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\changepassword.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\changepassword.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib crypt32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\chpasswd.pdb" /machine:I386 /out:"$(OUTDIR)\chpasswd.exe" 
LINK32_OBJS= \
	"$(INTDIR)\changepassword.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\chpasswd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "changepassword - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\chpasswd.exe" "$(OUTDIR)\changepassword.bsc"


CLEAN :
	-@erase "$(INTDIR)\changepassword.obj"
	-@erase "$(INTDIR)\changepassword.pch"
	-@erase "$(INTDIR)\changepassword.sbr"
	-@erase "$(INTDIR)\cryptsup.obj"
	-@erase "$(INTDIR)\cryptsup.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\changepassword.bsc"
	-@erase "$(OUTDIR)\chpasswd.exe"
	-@erase "$(OUTDIR)\chpasswd.ilk"
	-@erase "$(OUTDIR)\chpasswd.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\changepassword.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\changepassword.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\changepassword.sbr" \
	"$(INTDIR)\cryptsup.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\changepassword.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib crypt32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\chpasswd.pdb" /debug /machine:I386 /out:"$(OUTDIR)\chpasswd.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\changepassword.obj" \
	"$(INTDIR)\cryptsup.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\chpasswd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("changepassword.dep")
!INCLUDE "changepassword.dep"
!ELSE 
!MESSAGE Warning: cannot find "changepassword.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "changepassword - Win32 Release" || "$(CFG)" == "changepassword - Win32 Debug"
SOURCE=.\changepassword.cpp

!IF  "$(CFG)" == "changepassword - Win32 Release"


"$(INTDIR)\changepassword.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\changepassword.pch"


!ELSEIF  "$(CFG)" == "changepassword - Win32 Debug"


"$(INTDIR)\changepassword.obj"	"$(INTDIR)\changepassword.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\changepassword.pch"


!ENDIF 

SOURCE=.\cryptsup.cpp

!IF  "$(CFG)" == "changepassword - Win32 Release"


"$(INTDIR)\cryptsup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\changepassword.pch"


!ELSEIF  "$(CFG)" == "changepassword - Win32 Debug"


"$(INTDIR)\cryptsup.obj"	"$(INTDIR)\cryptsup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\changepassword.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "changepassword - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\changepassword.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\changepassword.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "changepassword - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\changepassword.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\changepassword.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


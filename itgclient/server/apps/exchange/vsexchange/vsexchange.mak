# Microsoft Developer Studio Generated NMAKE File, Based on vsexchange.dsp
!IF "$(CFG)" == ""
CFG=vsexchange - Win32 Debug
!MESSAGE No configuration specified. Defaulting to vsexchange - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "vsexchange - Win32 Release" && "$(CFG)" != "vsexchange - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vsexchange.mak" CFG="vsexchange - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vsexchange - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "vsexchange - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "vsexchange - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\vsexchange.dll" "$(OUTDIR)\vsexchange.bsc"


CLEAN :
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsaanls.obj"
	-@erase "$(INTDIR)\vsaanls.sbr"
	-@erase "$(INTDIR)\vsaautil.obj"
	-@erase "$(INTDIR)\vsaautil.sbr"
	-@erase "$(INTDIR)\vsexchangeutil.obj"
	-@erase "$(INTDIR)\vsexchangeutil.sbr"
	-@erase "$(INTDIR)\vslog.obj"
	-@erase "$(INTDIR)\vslog.sbr"
	-@erase "$(INTDIR)\vsutil.obj"
	-@erase "$(INTDIR)\vsutil.sbr"
	-@erase "$(INTDIR)\vsverifyexchange.obj"
	-@erase "$(INTDIR)\vsverifyexchange.sbr"
	-@erase "$(OUTDIR)\vsexchange.bsc"
	-@erase "$(OUTDIR)\vsexchange.dll"
	-@erase "$(OUTDIR)\vsexchange.exp"
	-@erase "$(OUTDIR)\vsexchange.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VSEXCHANGE_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\vsexchange.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsexchange.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\vsaanls.sbr" \
	"$(INTDIR)\vsaautil.sbr" \
	"$(INTDIR)\vsexchangeutil.sbr" \
	"$(INTDIR)\vslog.sbr" \
	"$(INTDIR)\vsutil.sbr" \
	"$(INTDIR)\vsverifyexchange.sbr"

"$(OUTDIR)\vsexchange.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  wldap32.lib advapi32.lib ws2_32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\vsexchange.pdb" /machine:I386 /def:".\vsexchange.def" /out:"$(OUTDIR)\vsexchange.dll" /implib:"$(OUTDIR)\vsexchange.lib" 
DEF_FILE= \
	".\vsexchange.def"
LINK32_OBJS= \
	"$(INTDIR)\vsaanls.obj" \
	"$(INTDIR)\vsaautil.obj" \
	"$(INTDIR)\vsexchangeutil.obj" \
	"$(INTDIR)\vslog.obj" \
	"$(INTDIR)\vsutil.obj" \
	"$(INTDIR)\vsverifyexchange.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\vsexchange.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\vsexchange.dll"


CLEAN :
	-@erase "$(INTDIR)\resource.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsaanls.obj"
	-@erase "$(INTDIR)\vsaautil.obj"
	-@erase "$(INTDIR)\vsexchangeutil.obj"
	-@erase "$(INTDIR)\vslog.obj"
	-@erase "$(INTDIR)\vsutil.obj"
	-@erase "$(INTDIR)\vsverifyexchange.obj"
	-@erase "$(OUTDIR)\vsexchange.dll"
	-@erase "$(OUTDIR)\vsexchange.exp"
	-@erase "$(OUTDIR)\vsexchange.ilk"
	-@erase "$(OUTDIR)\vsexchange.lib"
	-@erase "$(OUTDIR)\vsexchange.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /ZI /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VSEXCHANGE_EXPORTS" /Fp"$(INTDIR)\vsexchange.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\vsexchange.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  wldap32.lib advapi32.lib ws2_32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\vsexchange.pdb" /debug /machine:I386 /def:".\vsexchange.def" /out:"$(OUTDIR)\vsexchange.dll" /implib:"$(OUTDIR)\vsexchange.lib" /pdbtype:sept 
DEF_FILE= \
	".\vsexchange.def"
LINK32_OBJS= \
	"$(INTDIR)\vsaanls.obj" \
	"$(INTDIR)\vsaautil.obj" \
	"$(INTDIR)\vsexchangeutil.obj" \
	"$(INTDIR)\vslog.obj" \
	"$(INTDIR)\vsutil.obj" \
	"$(INTDIR)\vsverifyexchange.obj" \
	"$(INTDIR)\resource.res"

"$(OUTDIR)\vsexchange.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("vsexchange.dep")
!INCLUDE "vsexchange.dep"
!ELSE 
!MESSAGE Warning: cannot find "vsexchange.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "vsexchange - Win32 Release" || "$(CFG)" == "vsexchange - Win32 Debug"
SOURCE=.\resource.rc

"$(INTDIR)\resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\vsaanls.cpp

!IF  "$(CFG)" == "vsexchange - Win32 Release"


"$(INTDIR)\vsaanls.obj"	"$(INTDIR)\vsaanls.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"


"$(INTDIR)\vsaanls.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\vsaautil.cpp

!IF  "$(CFG)" == "vsexchange - Win32 Release"


"$(INTDIR)\vsaautil.obj"	"$(INTDIR)\vsaautil.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"


"$(INTDIR)\vsaautil.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\vsexchangeutil.cpp

!IF  "$(CFG)" == "vsexchange - Win32 Release"


"$(INTDIR)\vsexchangeutil.obj"	"$(INTDIR)\vsexchangeutil.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"


"$(INTDIR)\vsexchangeutil.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\vslog.cpp

!IF  "$(CFG)" == "vsexchange - Win32 Release"


"$(INTDIR)\vslog.obj"	"$(INTDIR)\vslog.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"


"$(INTDIR)\vslog.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\vsutil.cpp

!IF  "$(CFG)" == "vsexchange - Win32 Release"


"$(INTDIR)\vsutil.obj"	"$(INTDIR)\vsutil.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"


"$(INTDIR)\vsutil.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\vsverifyexchange.cpp

!IF  "$(CFG)" == "vsexchange - Win32 Release"


"$(INTDIR)\vsverifyexchange.obj"	"$(INTDIR)\vsverifyexchange.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "vsexchange - Win32 Debug"


"$(INTDIR)\vsverifyexchange.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 


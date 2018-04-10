# Microsoft Developer Studio Generated NMAKE File, Based on sgmsprs.dsp
!IF "$(CFG)" == ""
CFG=sgmsprs - Win32 Debug
!MESSAGE No configuration specified. Defaulting to sgmsprs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "sgmsprs - Win32 Release" && "$(CFG)" != "sgmsprs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sgmsprs.mak" CFG="sgmsprs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sgmsprs - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "sgmsprs - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sgmsprs - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\sgmsprs.exe"


CLEAN :
	-@erase "$(INTDIR)\getconfig.obj"
	-@erase "$(INTDIR)\Http.obj"
	-@erase "$(INTDIR)\LogWrapper.obj"
	-@erase "$(INTDIR)\sgmsprs.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vslog.obj"
	-@erase "$(OUTDIR)\sgmsprs.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /I "..\policymodule\include" /I "..\vsprs\include" /I "..\..\..\..\common\utils\include" /I "..\..\..\..\client\modules\bsafelite\include" /I "..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\common\simder\include" /I "..\..\..\..\client\apps\pta\activex\ptav3\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\sgmsprs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sgmsprs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib utils.lib mimeengine.lib policymodule.lib BSafeLite.lib crypt32.lib simder.lib vsprs.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\sgmsprs.pdb" /machine:I386 /out:"$(OUTDIR)\sgmsprs.exe" /libpath:"..\..\..\..\common\lib\release" /libpath:"..\..\..\..\client\modules\lib\static\release" /libpath:"..\..\..\lib\static\release" 
LINK32_OBJS= \
	"$(INTDIR)\getconfig.obj" \
	"$(INTDIR)\Http.obj" \
	"$(INTDIR)\LogWrapper.obj" \
	"$(INTDIR)\sgmsprs.obj" \
	"$(INTDIR)\vslog.obj"

"$(OUTDIR)\sgmsprs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sgmsprs - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\sgmsprs.exe"


CLEAN :
	-@erase "$(INTDIR)\getconfig.obj"
	-@erase "$(INTDIR)\Http.obj"
	-@erase "$(INTDIR)\LogWrapper.obj"
	-@erase "$(INTDIR)\sgmsprs.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vslog.obj"
	-@erase "$(OUTDIR)\sgmsprs.exe"
	-@erase "$(OUTDIR)\sgmsprs.ilk"
	-@erase "$(OUTDIR)\sgmsprs.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "..\policymodule\include" /I "..\vsprs\include" /I "..\..\..\..\common\utils\include" /I "..\..\..\..\client\modules\bsafelite\include" /I "..\..\..\..\common\scmodules\mimeengine\include" /I "..\..\..\..\common\simder\include" /I "..\..\..\..\client\apps\pta\activex\ptav3\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\sgmsprs.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sgmsprs.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=utils.lib mimeengine.lib policymodule.lib BSafeLite.lib ProtectedStorage.lib vsprs.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib crypt32.lib simder.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\sgmsprs.pdb" /debug /machine:I386 /out:"$(OUTDIR)\sgmsprs.exe" /pdbtype:sept /libpath:"..\..\..\..\common\lib\debug" /libpath:"..\..\..\..\client\modules\lib\static\debug" /libpath:"..\..\..\lib\static\debug" 
LINK32_OBJS= \
	"$(INTDIR)\getconfig.obj" \
	"$(INTDIR)\Http.obj" \
	"$(INTDIR)\LogWrapper.obj" \
	"$(INTDIR)\sgmsprs.obj" \
	"$(INTDIR)\vslog.obj"

"$(OUTDIR)\sgmsprs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("sgmsprs.dep")
!INCLUDE "sgmsprs.dep"
!ELSE 
!MESSAGE Warning: cannot find "sgmsprs.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "sgmsprs - Win32 Release" || "$(CFG)" == "sgmsprs - Win32 Debug"
SOURCE=.\sources\getconfig.cpp

"$(INTDIR)\getconfig.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\Http.cpp

"$(INTDIR)\Http.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\LogWrapper.cpp

"$(INTDIR)\LogWrapper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\sgmsprs.cpp

"$(INTDIR)\sgmsprs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vslog.cpp

"$(INTDIR)\vslog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


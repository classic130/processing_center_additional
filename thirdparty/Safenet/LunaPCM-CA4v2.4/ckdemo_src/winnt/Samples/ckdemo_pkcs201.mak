# Microsoft Developer Studio Generated NMAKE File, Based on ckdemo_pkcs201.dsp
!IF "$(CFG)" == ""
CFG=ckdemo_pkcs201 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ckdemo_pkcs201 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ckdemo_pkcs201 - Win32 Release" && "$(CFG)" != "ckdemo_pkcs201 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ckdemo_pkcs201.mak" CFG="ckdemo_pkcs201 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ckdemo_pkcs201 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ckdemo_pkcs201 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ckdemo_pkcs201 - Win32 Release"

OUTDIR=.\Release_201
INTDIR=.\Release_201

ALL : ".\Release\ckdemo.exe"


CLEAN :
	-@erase "$(INTDIR)\c_bridge.obj"
	-@erase "$(INTDIR)\ChrystokiConfiguration.obj"
	-@erase "$(INTDIR)\ckbridge.obj"
	-@erase "$(INTDIR)\Ckdemo.obj"
	-@erase "$(INTDIR)\Ckodesc.obj"
	-@erase "$(INTDIR)\console.obj"
	-@erase "$(INTDIR)\DynamicLibrary.obj"
	-@erase "$(INTDIR)\editor.obj"
	-@erase "$(INTDIR)\template.obj"
	-@erase "$(INTDIR)\Utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\Release\ckdemo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "OS_WIN32" /D "_CONSOLE" /D "_MBCS" /D "PKCS11_2_0" /D "_WINDOWS" /I "source" /Fp"$(INTDIR)\ckdemo_pkcs201.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ckdemo_pkcs201.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ckdemo.pdb" /machine:I386 /out:"Release/ckdemo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\c_bridge.obj" \
	"$(INTDIR)\ChrystokiConfiguration.obj" \
	"$(INTDIR)\ckbridge.obj" \
	"$(INTDIR)\Ckdemo.obj" \
	"$(INTDIR)\Ckodesc.obj" \
	"$(INTDIR)\console.obj" \
	"$(INTDIR)\DynamicLibrary.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\template.obj" \
	"$(INTDIR)\Utils.obj"

".\Release\ckdemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ckdemo_pkcs201 - Win32 Debug"

OUTDIR=.\Debug_201
INTDIR=.\Debug_201

ALL : ".\Debug\ckdemo.exe"


CLEAN :
	-@erase "$(INTDIR)\c_bridge.obj"
	-@erase "$(INTDIR)\ChrystokiConfiguration.obj"
	-@erase "$(INTDIR)\ckbridge.obj"
	-@erase "$(INTDIR)\Ckdemo.obj"
	-@erase "$(INTDIR)\Ckodesc.obj"
	-@erase "$(INTDIR)\console.obj"
	-@erase "$(INTDIR)\DynamicLibrary.obj"
	-@erase "$(INTDIR)\editor.obj"
	-@erase "$(INTDIR)\template.obj"
	-@erase "$(INTDIR)\Utils.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ckdemo.pdb"
	-@erase ".\Debug\ckdemo.exe"
	-@erase ".\Debug\ckdemo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WINDOWS" /D "_WINDOWS" /D "WIN32" /D "OS_WIN32" /D "_CONSOLE" /D "_MBCS" /D "PKCS11_2_0" /I "source" /Fp"$(INTDIR)\ckdemo_pkcs201.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ckdemo_pkcs201.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ckdemo.pdb" /debug /machine:I386 /out:"Debug/ckdemo.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\c_bridge.obj" \
	"$(INTDIR)\ChrystokiConfiguration.obj" \
	"$(INTDIR)\ckbridge.obj" \
	"$(INTDIR)\Ckdemo.obj" \
	"$(INTDIR)\Ckodesc.obj" \
	"$(INTDIR)\console.obj" \
	"$(INTDIR)\DynamicLibrary.obj" \
	"$(INTDIR)\editor.obj" \
	"$(INTDIR)\template.obj" \
	"$(INTDIR)\Utils.obj"

".\Debug\ckdemo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ckdemo_pkcs201.dep")
!INCLUDE "ckdemo_pkcs201.dep"
!ELSE 
!MESSAGE Warning: cannot find "ckdemo_pkcs201.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ckdemo_pkcs201 - Win32 Release" || "$(CFG)" == "ckdemo_pkcs201 - Win32 Debug"
SOURCE=.\source\c_bridge.cpp

"$(INTDIR)\c_bridge.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\ChrystokiConfiguration.cpp

"$(INTDIR)\ChrystokiConfiguration.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\ckbridge.cpp

"$(INTDIR)\ckbridge.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\Ckdemo.cpp

"$(INTDIR)\Ckdemo.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\source\Ckodesc.cpp

"$(INTDIR)\Ckodesc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\console.cpp

"$(INTDIR)\console.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\DynamicLibrary.cpp

"$(INTDIR)\DynamicLibrary.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\editor.cpp

"$(INTDIR)\editor.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\template.cpp

"$(INTDIR)\template.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\Utils.cpp

"$(INTDIR)\Utils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


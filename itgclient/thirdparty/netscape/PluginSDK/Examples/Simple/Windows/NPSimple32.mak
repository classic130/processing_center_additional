# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=NPSimple32 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to NPSimple32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NPSimple32 - Win32 Release" && "$(CFG)" !=\
 "NPSimple32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "NPSimple32.mak" CFG="NPSimple32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NPSimple32 - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NPSimple32 - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "NPSimple32 - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "NPSimple32 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\NPSimp32.dll"

CLEAN : 
	-@erase "$(INTDIR)\npsimple.obj"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\Simple32.res"
	-@erase "$(INTDIR)\stubs.obj"
	-@erase "$(OUTDIR)\NPSimp32.exp"
	-@erase "$(OUTDIR)\NPSimp32.lib"
	-@erase ".\NPSimp32.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./" /I "../Source" /I "../../../Common" /I "../../../Include" /I "../Source/_gen" /I "../Source/_stubs" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "XP_PC" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "./" /I "../Source" /I "../../../Common" /I\
 "../../../Include" /I "../Source/_gen" /I "../Source/_stubs" /D "NDEBUG" /D\
 "WIN32" /D "_WINDOWS" /D "XP_PC" /Fp"$(INTDIR)/NPSimple32.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Simple32.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NPSimple32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"NPSimp32.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/NPSimp32.pdb" /machine:I386 /def:".\Simple32.def"\
 /out:"NPSimp32.dll" /implib:"$(OUTDIR)/NPSimp32.lib" 
DEF_FILE= \
	".\Simple32.def"
LINK32_OBJS= \
	"$(INTDIR)\npsimple.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\Simple32.res" \
	"$(INTDIR)\stubs.obj"

".\NPSimp32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NPSimple32 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\NPSimp32.dll"

CLEAN : 
	-@erase "$(INTDIR)\npsimple.obj"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\Simple32.res"
	-@erase "$(INTDIR)\stubs.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\NPSimp32.exp"
	-@erase "$(OUTDIR)\NPSimp32.lib"
	-@erase "$(OUTDIR)\NPSimp32.pdb"
	-@erase ".\NPSimp32.dll"
	-@erase ".\NPSimp32.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "./" /I "../Source" /I "../../../Common" /I "../../../Include" /I "../Source/_gen" /I "../Source/_stubs" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "XP_PC" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "./" /I "../Source" /I\
 "../../../Common" /I "../../../Include" /I "../Source/_gen" /I\
 "../Source/_stubs" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "XP_PC"\
 /Fp"$(INTDIR)/NPSimple32.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Simple32.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/NPSimple32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"NPSimp32.dll"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/NPSimp32.pdb" /debug /machine:I386 /def:".\Simple32.def"\
 /out:"NPSimp32.dll" /implib:"$(OUTDIR)/NPSimp32.lib" 
DEF_FILE= \
	".\Simple32.def"
LINK32_OBJS= \
	"$(INTDIR)\npsimple.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\Simple32.res" \
	"$(INTDIR)\stubs.obj"

".\NPSimp32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "NPSimple32 - Win32 Release"
# Name "NPSimple32 - Win32 Debug"

!IF  "$(CFG)" == "NPSimple32 - Win32 Release"

!ELSEIF  "$(CFG)" == "NPSimple32 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Simple32.rc

!IF  "$(CFG)" == "NPSimple32 - Win32 Release"

NODEP_RSC_SIMPL=\
	".\resource.h"\
	

"$(INTDIR)\Simple32.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPSimple32 - Win32 Debug"


"$(INTDIR)\Simple32.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Simple32.def

!IF  "$(CFG)" == "NPSimple32 - Win32 Release"

!ELSEIF  "$(CFG)" == "NPSimple32 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\simple\Source\npsimple.c
DEP_CPP_NPSIM=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\..\Include\jri_md.h"\
	"..\..\..\Include\jritypes.h"\
	"..\Source\_gen\java_lang_Object.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\Simple.h"\
	

"$(INTDIR)\npsimple.obj" : $(SOURCE) $(DEP_CPP_NPSIM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\simple\Source\stubs.c
DEP_CPP_STUBS=\
	"..\..\..\common\npunix.c"\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\..\Include\jri_md.h"\
	"..\..\..\Include\jritypes.h"\
	"..\Source\_gen\java_lang_Object.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../../Include\npupp.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\Simple.h"\
	".\../Source/_stubs\netscape_plugin_Plugin.c"\
	".\../Source/_stubs\Simple.c"\
	

"$(INTDIR)\stubs.obj" : $(SOURCE) $(DEP_CPP_STUBS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Common\npwin.cpp
DEP_CPP_NPWIN=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\..\Include\jri_md.h"\
	"..\..\..\Include\jritypes.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../../Include\npupp.h"\
	

"$(INTDIR)\npwin.obj" : $(SOURCE) $(DEP_CPP_NPWIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################

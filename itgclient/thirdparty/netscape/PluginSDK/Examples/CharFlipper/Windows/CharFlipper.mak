# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=CharFlipper - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to CharFlipper - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CharFlipper - Win32 Release" && "$(CFG)" !=\
 "CharFlipper - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "CharFlipper.mak" CFG="CharFlipper - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CharFlipper - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "CharFlipper - Win32 Debug" (based on\
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
# PROP Target_Last_Scanned "CharFlipper - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\NPFlip.dll"

CLEAN : 
	-@erase "$(INTDIR)\CCharFlipper.obj"
	-@erase "$(INTDIR)\CCharFlipper_Win.obj"
	-@erase "$(INTDIR)\CCharFlipperStream.obj"
	-@erase "$(INTDIR)\CFlipView.obj"
	-@erase "$(INTDIR)\CharFlipper.res"
	-@erase "$(INTDIR)\CharFlipperFactory.obj"
	-@erase "$(INTDIR)\CNavigator.obj"
	-@erase "$(INTDIR)\CNetscapePlugin.obj"
	-@erase "$(INTDIR)\CNetscapeStream.obj"
	-@erase "$(INTDIR)\CPluginArgs.obj"
	-@erase "$(INTDIR)\CPluginView.obj"
	-@erase "$(INTDIR)\javastubs.obj"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TimeMediaNatives.obj"
	-@erase "$(INTDIR)\WinFlipView.obj"
	-@erase "$(OUTDIR)\NPFlip.exp"
	-@erase "$(OUTDIR)\NPFlip.lib"
	-@erase ".\NPFlip.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "./" /I "../Source" /I "../../../Common" /I "../../../Include" /I "../../Framework" /I "../Source/_gen" /I "../Source/_stubs" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "XP_PC" /D "DEBUG" /c
# SUBTRACT CPP /X /YX
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "./" /I "../Source" /I "../../../Common" /I\
 "../../../Include" /I "../../Framework" /I "../Source/_gen" /I\
 "../Source/_stubs" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D\
 "_AFXDLL" /D "_MBCS" /D "XP_PC" /D "DEBUG" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CharFlipper.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CharFlipper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"NPFlip.dll"
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/NPFlip.pdb" /machine:I386 /def:".\CharFlipper.def"\
 /out:"NPFlip.dll" /implib:"$(OUTDIR)/NPFlip.lib" 
DEF_FILE= \
	".\CharFlipper.def"
LINK32_OBJS= \
	"$(INTDIR)\CCharFlipper.obj" \
	"$(INTDIR)\CCharFlipper_Win.obj" \
	"$(INTDIR)\CCharFlipperStream.obj" \
	"$(INTDIR)\CFlipView.obj" \
	"$(INTDIR)\CharFlipper.res" \
	"$(INTDIR)\CharFlipperFactory.obj" \
	"$(INTDIR)\CNavigator.obj" \
	"$(INTDIR)\CNetscapePlugin.obj" \
	"$(INTDIR)\CNetscapeStream.obj" \
	"$(INTDIR)\CPluginArgs.obj" \
	"$(INTDIR)\CPluginView.obj" \
	"$(INTDIR)\javastubs.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TimeMediaNatives.obj" \
	"$(INTDIR)\WinFlipView.obj"

".\NPFlip.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\NPFlip.dll"

CLEAN : 
	-@erase "$(INTDIR)\CCharFlipper.obj"
	-@erase "$(INTDIR)\CCharFlipper_Win.obj"
	-@erase "$(INTDIR)\CCharFlipperStream.obj"
	-@erase "$(INTDIR)\CFlipView.obj"
	-@erase "$(INTDIR)\CharFlipper.res"
	-@erase "$(INTDIR)\CharFlipperFactory.obj"
	-@erase "$(INTDIR)\CNavigator.obj"
	-@erase "$(INTDIR)\CNetscapePlugin.obj"
	-@erase "$(INTDIR)\CNetscapeStream.obj"
	-@erase "$(INTDIR)\CPluginArgs.obj"
	-@erase "$(INTDIR)\CPluginView.obj"
	-@erase "$(INTDIR)\javastubs.obj"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TimeMediaNatives.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\WinFlipView.obj"
	-@erase "$(OUTDIR)\NPFlip.exp"
	-@erase "$(OUTDIR)\NPFlip.lib"
	-@erase "$(OUTDIR)\NPFlip.pdb"
	-@erase ".\NPFlip.dll"
	-@erase ".\NPFlip.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "./" /I "../Source" /I "../../../Common" /I "../../../Include" /I "../../Framework" /I "../Source/_gen" /I "../Source/_stubs" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "XP_PC" /D "DEBUG" /c
# SUBTRACT CPP /X /YX
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "./" /I "../Source" /I\
 "../../../Common" /I "../../../Include" /I "../../Framework" /I\
 "../Source/_gen" /I "../Source/_stubs" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "XP_PC" /D "DEBUG" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/CharFlipper.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/CharFlipper.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"NPFlip.dll"
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/NPFlip.pdb" /debug /machine:I386 /def:".\CharFlipper.def"\
 /out:"NPFlip.dll" /implib:"$(OUTDIR)/NPFlip.lib" 
DEF_FILE= \
	".\CharFlipper.def"
LINK32_OBJS= \
	"$(INTDIR)\CCharFlipper.obj" \
	"$(INTDIR)\CCharFlipper_Win.obj" \
	"$(INTDIR)\CCharFlipperStream.obj" \
	"$(INTDIR)\CFlipView.obj" \
	"$(INTDIR)\CharFlipper.res" \
	"$(INTDIR)\CharFlipperFactory.obj" \
	"$(INTDIR)\CNavigator.obj" \
	"$(INTDIR)\CNetscapePlugin.obj" \
	"$(INTDIR)\CNetscapeStream.obj" \
	"$(INTDIR)\CPluginArgs.obj" \
	"$(INTDIR)\CPluginView.obj" \
	"$(INTDIR)\javastubs.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TimeMediaNatives.obj" \
	"$(INTDIR)\WinFlipView.obj"

".\NPFlip.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "CharFlipper - Win32 Release"
# Name "CharFlipper - Win32 Debug"

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=\PluginSDK\Common\npwin.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_NPWIN=\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../../Include\npupp.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	

"$(INTDIR)\npwin.obj" : $(SOURCE) $(DEP_CPP_NPWIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_NPWIN=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../../Include\npupp.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	

"$(INTDIR)\npwin.obj" : $(SOURCE) $(DEP_CPP_NPWIN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\Framework\CPluginView.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CPLUG=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	

"$(INTDIR)\CPluginView.obj" : $(SOURCE) $(DEP_CPP_CPLUG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CPLUG=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	

"$(INTDIR)\CPluginView.obj" : $(SOURCE) $(DEP_CPP_CPLUG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\Framework\CNetscapePlugin.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CNETS=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	

"$(INTDIR)\CNetscapePlugin.obj" : $(SOURCE) $(DEP_CPP_CNETS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CNETS=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	

"$(INTDIR)\CNetscapePlugin.obj" : $(SOURCE) $(DEP_CPP_CNETS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\Framework\CNetscapeStream.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CNETSC=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	

"$(INTDIR)\CNetscapeStream.obj" : $(SOURCE) $(DEP_CPP_CNETSC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CNETSC=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	

"$(INTDIR)\CNetscapeStream.obj" : $(SOURCE) $(DEP_CPP_CNETSC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\Framework\CPluginArgs.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CPLUGI=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CPluginArgs.h"\
	

"$(INTDIR)\CPluginArgs.obj" : $(SOURCE) $(DEP_CPP_CPLUGI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CPLUGI=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CPluginArgs.h"\
	

"$(INTDIR)\CPluginArgs.obj" : $(SOURCE) $(DEP_CPP_CPLUGI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\Framework\CNavigator.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CNAVI=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	

"$(INTDIR)\CNavigator.obj" : $(SOURCE) $(DEP_CPP_CNAVI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CNAVI=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	

"$(INTDIR)\CNavigator.obj" : $(SOURCE) $(DEP_CPP_CNAVI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\CCharFlipper.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CCHAR=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\TimeMediaPlugin.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\_gen\java_lang_Object.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CCharFlipperStream.h"\
	".\..\Source\CFlipView.h"\
	

"$(INTDIR)\CCharFlipper.obj" : $(SOURCE) $(DEP_CPP_CCHAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CCHAR=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\TimeMediaPlugin.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\_gen\java_lang_Object.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CCharFlipperStream.h"\
	".\..\Source\CFlipView.h"\
	

"$(INTDIR)\CCharFlipper.obj" : $(SOURCE) $(DEP_CPP_CCHAR) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\TimeMediaNatives.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_TIMEM=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\TimeMediaPlugin.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\_gen\java_lang_Object.h"\
	".\..\Source\CCharFlipper.h"\
	

"$(INTDIR)\TimeMediaNatives.obj" : $(SOURCE) $(DEP_CPP_TIMEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_TIMEM=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\TimeMediaPlugin.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\_gen\java_lang_Object.h"\
	".\..\Source\CCharFlipper.h"\
	

"$(INTDIR)\TimeMediaNatives.obj" : $(SOURCE) $(DEP_CPP_TIMEM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\CCharFlipperStream.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CCHARF=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CCharFlipperStream.h"\
	

"$(INTDIR)\CCharFlipperStream.obj" : $(SOURCE) $(DEP_CPP_CCHARF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CCHARF=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CCharFlipperStream.h"\
	

"$(INTDIR)\CCharFlipperStream.obj" : $(SOURCE) $(DEP_CPP_CCHARF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\CFlipView.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CFLIP=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CFlipView.h"\
	

"$(INTDIR)\CFlipView.obj" : $(SOURCE) $(DEP_CPP_CFLIP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CFLIP=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CFlipView.h"\
	

"$(INTDIR)\CFlipView.obj" : $(SOURCE) $(DEP_CPP_CFLIP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\CharFlipperFactory.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CHARF=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	

"$(INTDIR)\CharFlipperFactory.obj" : $(SOURCE) $(DEP_CPP_CHARF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CHARF=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	

"$(INTDIR)\CharFlipperFactory.obj" : $(SOURCE) $(DEP_CPP_CHARF) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\CCharFlipper_Win.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_CCHARFL=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CFlipView.h"\
	".\..\Source\WinFlipView.h"\
	".\./stdafx.h"\
	

"$(INTDIR)\CCharFlipper_Win.obj" : $(SOURCE) $(DEP_CPP_CCHARFL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_CCHARFL=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CFlipView.h"\
	".\..\Source\WinFlipView.h"\
	".\./stdafx.h"\
	

"$(INTDIR)\CCharFlipper_Win.obj" : $(SOURCE) $(DEP_CPP_CCHARFL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\WinFlipView.cpp

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_WINFL=\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CFlipView.h"\
	".\..\Source\WinFlipView.h"\
	".\./stdafx.h"\
	

"$(INTDIR)\WinFlipView.obj" : $(SOURCE) $(DEP_CPP_WINFL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_WINFL=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	"..\..\Framework\CNetscapeMemObject.h"\
	".\../../../Include\jri.h"\
	".\../../../Include\npapi.h"\
	".\../../Framework\CNetscapePlugin.h"\
	".\../../Framework\CNetscapeStream.h"\
	".\../../Framework\CPluginView.h"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\..\Framework\CNavigator.h"\
	".\..\..\Framework\CPluginArgs.h"\
	".\..\Source\CCharFlipper.h"\
	".\..\Source\CFlipView.h"\
	".\..\Source\WinFlipView.h"\
	".\./stdafx.h"\
	

"$(INTDIR)\WinFlipView.obj" : $(SOURCE) $(DEP_CPP_WINFL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\./stdafx.h"\
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CharFlipper.def

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\PluginSDK\Examples\CharFlipper\Source\javastubs.c

!IF  "$(CFG)" == "CharFlipper - Win32 Release"

DEP_CPP_JAVAS=\
	".\../../../Include\jri.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\TimeMediaPlugin.h"\
	".\../Source/_stubs\netscape_plugin_Plugin.c"\
	".\../Source/_stubs\TimeMediaPlugin.c"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\Source\_gen\java_lang_Object.h"\
	

"$(INTDIR)\javastubs.obj" : $(SOURCE) $(DEP_CPP_JAVAS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "CharFlipper - Win32 Debug"

DEP_CPP_JAVAS=\
	"..\..\..\Include\jni.h"\
	"..\..\..\Include\jni_md.h"\
	".\../../../Include\jri.h"\
	".\../Source/_gen\netscape_plugin_Plugin.h"\
	".\../Source/_gen\TimeMediaPlugin.h"\
	".\../Source/_stubs\netscape_plugin_Plugin.c"\
	".\../Source/_stubs\TimeMediaPlugin.c"\
	".\..\..\..\Include\jri_md.h"\
	".\..\..\..\Include\jritypes.h"\
	".\..\Source\_gen\java_lang_Object.h"\
	

"$(INTDIR)\javastubs.obj" : $(SOURCE) $(DEP_CPP_JAVAS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CharFlipper.rc
DEP_RSC_CHARFL=\
	".\res\CharFlipper.rc2"\
	

"$(INTDIR)\CharFlipper.res" : $(SOURCE) $(DEP_RSC_CHARFL) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################

# Microsoft Developer Studio Generated NMAKE File, Based on pestub.dsp
!IF "$(CFG)" == ""
CFG=pestub - Win32 Debug
!MESSAGE No configuration specified. Defaulting to pestub - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "pestub - Win32 Release" && "$(CFG)" != "pestub - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pestub.mak" CFG="pestub - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pestub - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "pestub - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "pestub - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\pestub.dll"


CLEAN :
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\MsgFunc.obj"
	-@erase "$(INTDIR)\pestub.obj"
	-@erase "$(INTDIR)\pestub.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vslog.obj"
	-@erase "$(INTDIR)\vsutil.obj"
	-@erase "$(OUTDIR)\pestub.dll"
	-@erase "$(OUTDIR)\pestub.exp"
	-@erase "$(OUTDIR)\pestub.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "include" /I "..\..\..\..\..\..\itgclient\common\scmodules\certres\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PESTUB_EXPORTS" /Fp"$(INTDIR)\pestub.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pestub.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pestub.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wldap32.lib wsock32.lib  ..\..\..\..\..\common\lib\release\ResolutionLib.lib ..\..\..\..\..\common\lib\release\simder.lib ..\..\..\..\..\common\lib\release\msgstorelib.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\pestub.pdb" /machine:I386 /def:".\pestub.def" /out:"$(OUTDIR)\pestub.dll" /implib:"$(OUTDIR)\pestub.lib" 
DEF_FILE= \
	".\pestub.def"
LINK32_OBJS= \
	"$(INTDIR)\vsutil.obj" \
	"$(INTDIR)\MsgFunc.obj" \
	"$(INTDIR)\pestub.obj" \
	"$(INTDIR)\vslog.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\pestub.res"

"$(OUTDIR)\pestub.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pestub - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\pestub.dll"


CLEAN :
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\MsgFunc.obj"
	-@erase "$(INTDIR)\pestub.obj"
	-@erase "$(INTDIR)\pestub.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vslog.obj"
	-@erase "$(INTDIR)\vsutil.obj"
	-@erase "$(OUTDIR)\pestub.dll"
	-@erase "$(OUTDIR)\pestub.exp"
	-@erase "$(OUTDIR)\pestub.ilk"
	-@erase "$(OUTDIR)\pestub.lib"
	-@erase "$(OUTDIR)\pestub.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /I "include" /I "..\..\..\..\..\..\itgclient\common\scmodules\certres\include" /I "..\..\..\..\..\..\itgclient\common\simder\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PESTUB_EXPORTS" /Fp"$(INTDIR)\pestub.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pestub.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pestub.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wldap32.lib wsock32.lib ..\..\..\..\..\common\lib\debug\ResolutionLib.lib ..\..\..\..\..\common\lib\debug\simder.lib ..\..\..\..\..\common\lib\debug\msgstorelib.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\pestub.pdb" /debug /machine:I386 /def:".\pestub.def" /out:"$(OUTDIR)\pestub.dll" /implib:"$(OUTDIR)\pestub.lib" /pdbtype:sept 
DEF_FILE= \
	".\pestub.def"
LINK32_OBJS= \
	"$(INTDIR)\vsutil.obj" \
	"$(INTDIR)\MsgFunc.obj" \
	"$(INTDIR)\pestub.obj" \
	"$(INTDIR)\vslog.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\pestub.res"

"$(OUTDIR)\pestub.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\pestub.dll"
   copy debug\pestub.dll  pMsgTest
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("pestub.dep")
!INCLUDE "pestub.dep"
!ELSE 
!MESSAGE Warning: cannot find "pestub.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "pestub - Win32 Release" || "$(CFG)" == "pestub - Win32 Debug"
SOURCE=.\sources\misc.cpp

"$(INTDIR)\misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\MsgFunc.cpp

"$(INTDIR)\MsgFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\pestub.cpp

"$(INTDIR)\pestub.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\pestub.rc

"$(INTDIR)\pestub.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\sources\vslog.cpp

"$(INTDIR)\vslog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsutil.cpp

"$(INTDIR)\vsutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


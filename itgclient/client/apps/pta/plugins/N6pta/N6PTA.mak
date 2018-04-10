# Microsoft Developer Studio Generated NMAKE File, Based on N6PTA.dsp
!IF "$(CFG)" == ""
CFG=N6PTA - Win32 Debug
!MESSAGE No configuration specified. Defaulting to N6PTA - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "N6PTA - Win32 Release" && "$(CFG)" != "N6PTA - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "N6PTA.mak" CFG="N6PTA - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "N6PTA - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "N6PTA - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "N6PTA - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\N6PTA.dll" "$(OUTDIR)\N6PTA.bsc"


CLEAN :
	-@erase "$(INTDIR)\addrootswrap.obj"
	-@erase "$(INTDIR)\addrootswrap.sbr"
	-@erase "$(INTDIR)\N6PTA.obj"
	-@erase "$(INTDIR)\N6PTA.res"
	-@erase "$(INTDIR)\N6PTA.sbr"
	-@erase "$(INTDIR)\P12wrap.obj"
	-@erase "$(INTDIR)\P12wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vscertprefswrap.obj"
	-@erase "$(INTDIR)\vscertprefswrap.sbr"
	-@erase "$(INTDIR)\vsdnzwrap.obj"
	-@erase "$(INTDIR)\vsdnzwrap.sbr"
	-@erase "$(INTDIR)\vsimportwrap.obj"
	-@erase "$(INTDIR)\vsimportwrap.sbr"
	-@erase "$(INTDIR)\vsprofmgmtwrap.obj"
	-@erase "$(INTDIR)\vsprofmgmtwrap.sbr"
	-@erase "$(INTDIR)\vsptadllapiwrap.obj"
	-@erase "$(INTDIR)\vsptadllapiwrap.sbr"
	-@erase "$(INTDIR)\vsptawrap.obj"
	-@erase "$(INTDIR)\vsptawrap.sbr"
	-@erase "$(INTDIR)\vsroamprefswrap.obj"
	-@erase "$(INTDIR)\vsroamprefswrap.sbr"
	-@erase "$(INTDIR)\vsselecteddigidwrap.obj"
	-@erase "$(INTDIR)\vsselecteddigidwrap.sbr"
	-@erase "$(INTDIR)\vssrchcritwrap.obj"
	-@erase "$(INTDIR)\vssrchcritwrap.sbr"
	-@erase "$(INTDIR)\vsuiprefswrap.obj"
	-@erase "$(INTDIR)\vsuiprefswrap.sbr"
	-@erase "$(INTDIR)\XEnrollWrap.obj"
	-@erase "$(INTDIR)\XEnrollWrap.sbr"
	-@erase "$(OUTDIR)\N6PTA.bsc"
	-@erase "$(OUTDIR)\N6PTA.dll"
	-@erase "$(OUTDIR)\N6PTA.exp"
	-@erase "$(OUTDIR)\N6PTA.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\NPPTAv3\src" /I "i:\N6PluginSDK\include" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\NPPTAv3\include" /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "N6PTA_EXPORTS" /D "XP_PC" /D WINVER=0x400 /D _MSC_VER=1200 /D "_X86_" /D "_NS6_PTA_" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\N6PTA.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\N6PTA.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\N6PTA.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addrootswrap.sbr" \
	"$(INTDIR)\N6PTA.sbr" \
	"$(INTDIR)\P12wrap.sbr" \
	"$(INTDIR)\vscertprefswrap.sbr" \
	"$(INTDIR)\vsdnzwrap.sbr" \
	"$(INTDIR)\vsimportwrap.sbr" \
	"$(INTDIR)\vsprofmgmtwrap.sbr" \
	"$(INTDIR)\vsptadllapiwrap.sbr" \
	"$(INTDIR)\vsptawrap.sbr" \
	"$(INTDIR)\vsroamprefswrap.sbr" \
	"$(INTDIR)\vsselecteddigidwrap.sbr" \
	"$(INTDIR)\vssrchcritwrap.sbr" \
	"$(INTDIR)\vsuiprefswrap.sbr" \
	"$(INTDIR)\XEnrollWrap.sbr"

"$(OUTDIR)\N6PTA.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "i:\N6PluginSDK\lib\xpcom.lib" "..\..\..\..\modules\lib\static\release\bsafelite.lib" /nologo /dll /incremental:no /pdb:"$(OUTDIR)\N6PTA.pdb" /machine:I386 /out:"$(OUTDIR)\N6PTA.dll" /implib:"$(OUTDIR)\N6PTA.lib" 
LINK32_OBJS= \
	"$(INTDIR)\addrootswrap.obj" \
	"$(INTDIR)\N6PTA.obj" \
	"$(INTDIR)\P12wrap.obj" \
	"$(INTDIR)\vscertprefswrap.obj" \
	"$(INTDIR)\vsdnzwrap.obj" \
	"$(INTDIR)\vsimportwrap.obj" \
	"$(INTDIR)\vsprofmgmtwrap.obj" \
	"$(INTDIR)\vsptadllapiwrap.obj" \
	"$(INTDIR)\vsptawrap.obj" \
	"$(INTDIR)\vsroamprefswrap.obj" \
	"$(INTDIR)\vsselecteddigidwrap.obj" \
	"$(INTDIR)\vssrchcritwrap.obj" \
	"$(INTDIR)\vsuiprefswrap.obj" \
	"$(INTDIR)\XEnrollWrap.obj" \
	"$(INTDIR)\N6PTA.res"

"$(OUTDIR)\N6PTA.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "N6PTA - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\N6PTA.dll" "$(OUTDIR)\N6PTA.bsc"


CLEAN :
	-@erase "$(INTDIR)\addrootswrap.obj"
	-@erase "$(INTDIR)\addrootswrap.sbr"
	-@erase "$(INTDIR)\N6PTA.obj"
	-@erase "$(INTDIR)\N6PTA.res"
	-@erase "$(INTDIR)\N6PTA.sbr"
	-@erase "$(INTDIR)\P12wrap.obj"
	-@erase "$(INTDIR)\P12wrap.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vscertprefswrap.obj"
	-@erase "$(INTDIR)\vscertprefswrap.sbr"
	-@erase "$(INTDIR)\vsdnzwrap.obj"
	-@erase "$(INTDIR)\vsdnzwrap.sbr"
	-@erase "$(INTDIR)\vsimportwrap.obj"
	-@erase "$(INTDIR)\vsimportwrap.sbr"
	-@erase "$(INTDIR)\vsprofmgmtwrap.obj"
	-@erase "$(INTDIR)\vsprofmgmtwrap.sbr"
	-@erase "$(INTDIR)\vsptadllapiwrap.obj"
	-@erase "$(INTDIR)\vsptadllapiwrap.sbr"
	-@erase "$(INTDIR)\vsptawrap.obj"
	-@erase "$(INTDIR)\vsptawrap.sbr"
	-@erase "$(INTDIR)\vsroamprefswrap.obj"
	-@erase "$(INTDIR)\vsroamprefswrap.sbr"
	-@erase "$(INTDIR)\vsselecteddigidwrap.obj"
	-@erase "$(INTDIR)\vsselecteddigidwrap.sbr"
	-@erase "$(INTDIR)\vssrchcritwrap.obj"
	-@erase "$(INTDIR)\vssrchcritwrap.sbr"
	-@erase "$(INTDIR)\vsuiprefswrap.obj"
	-@erase "$(INTDIR)\vsuiprefswrap.sbr"
	-@erase "$(INTDIR)\XEnrollWrap.obj"
	-@erase "$(INTDIR)\XEnrollWrap.sbr"
	-@erase "$(OUTDIR)\N6PTA.bsc"
	-@erase "$(OUTDIR)\N6PTA.dll"
	-@erase "$(OUTDIR)\N6PTA.exp"
	-@erase "$(OUTDIR)\N6PTA.ilk"
	-@erase "$(OUTDIR)\N6PTA.lib"
	-@erase "$(OUTDIR)\N6PTA.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\NPPTAv3\src" /I "i:\N6PluginSDK\include" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\NPPTAv3\include" /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /D "DEBUG" /D "XP_PC" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D WINVER=0x400 /D _MSC_VER=1200 /D "_X86_" /D "N6PTA_EXPORTS" /D "_NS6_PTA_" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\N6PTA.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\N6PTA.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\N6PTA.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addrootswrap.sbr" \
	"$(INTDIR)\N6PTA.sbr" \
	"$(INTDIR)\P12wrap.sbr" \
	"$(INTDIR)\vscertprefswrap.sbr" \
	"$(INTDIR)\vsdnzwrap.sbr" \
	"$(INTDIR)\vsimportwrap.sbr" \
	"$(INTDIR)\vsprofmgmtwrap.sbr" \
	"$(INTDIR)\vsptadllapiwrap.sbr" \
	"$(INTDIR)\vsptawrap.sbr" \
	"$(INTDIR)\vsroamprefswrap.sbr" \
	"$(INTDIR)\vsselecteddigidwrap.sbr" \
	"$(INTDIR)\vssrchcritwrap.sbr" \
	"$(INTDIR)\vsuiprefswrap.sbr" \
	"$(INTDIR)\XEnrollWrap.sbr"

"$(OUTDIR)\N6PTA.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "i:\N6PluginSDK\lib\xpcom.lib" "..\..\..\..\modules\lib\static\debug\bsafelite.lib" /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\N6PTA.pdb" /debug /machine:I386 /out:"$(OUTDIR)\N6PTA.dll" /implib:"$(OUTDIR)\N6PTA.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\addrootswrap.obj" \
	"$(INTDIR)\N6PTA.obj" \
	"$(INTDIR)\P12wrap.obj" \
	"$(INTDIR)\vscertprefswrap.obj" \
	"$(INTDIR)\vsdnzwrap.obj" \
	"$(INTDIR)\vsimportwrap.obj" \
	"$(INTDIR)\vsprofmgmtwrap.obj" \
	"$(INTDIR)\vsptadllapiwrap.obj" \
	"$(INTDIR)\vsptawrap.obj" \
	"$(INTDIR)\vsroamprefswrap.obj" \
	"$(INTDIR)\vsselecteddigidwrap.obj" \
	"$(INTDIR)\vssrchcritwrap.obj" \
	"$(INTDIR)\vsuiprefswrap.obj" \
	"$(INTDIR)\XEnrollWrap.obj" \
	"$(INTDIR)\N6PTA.res"

"$(OUTDIR)\N6PTA.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("N6PTA.dep")
!INCLUDE "N6PTA.dep"
!ELSE 
!MESSAGE Warning: cannot find "N6PTA.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "N6PTA - Win32 Release" || "$(CFG)" == "N6PTA - Win32 Debug"
SOURCE=..\NPPTAv3\src\addrootswrap.cpp

"$(INTDIR)\addrootswrap.obj"	"$(INTDIR)\addrootswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\source\N6PTA.cpp

"$(INTDIR)\N6PTA.obj"	"$(INTDIR)\N6PTA.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\P12wrap.cpp

"$(INTDIR)\P12wrap.obj"	"$(INTDIR)\P12wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vscertprefswrap.cpp

"$(INTDIR)\vscertprefswrap.obj"	"$(INTDIR)\vscertprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsdnzwrap.cpp

"$(INTDIR)\vsdnzwrap.obj"	"$(INTDIR)\vsdnzwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsimportwrap.cpp

"$(INTDIR)\vsimportwrap.obj"	"$(INTDIR)\vsimportwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsprofmgmtwrap.cpp

"$(INTDIR)\vsprofmgmtwrap.obj"	"$(INTDIR)\vsprofmgmtwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsptadllapiwrap.cpp

"$(INTDIR)\vsptadllapiwrap.obj"	"$(INTDIR)\vsptadllapiwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsptawrap.cpp

"$(INTDIR)\vsptawrap.obj"	"$(INTDIR)\vsptawrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsroamprefswrap.cpp

"$(INTDIR)\vsroamprefswrap.obj"	"$(INTDIR)\vsroamprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsselecteddigidwrap.cpp

"$(INTDIR)\vsselecteddigidwrap.obj"	"$(INTDIR)\vsselecteddigidwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vssrchcritwrap.cpp

"$(INTDIR)\vssrchcritwrap.obj"	"$(INTDIR)\vssrchcritwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\vsuiprefswrap.cpp

"$(INTDIR)\vsuiprefswrap.obj"	"$(INTDIR)\vsuiprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\NPPTAv3\src\XEnrollWrap.cpp

"$(INTDIR)\XEnrollWrap.obj"	"$(INTDIR)\XEnrollWrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\N6PTA.rc

"$(INTDIR)\N6PTA.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 


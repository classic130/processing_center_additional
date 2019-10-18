# Microsoft Developer Studio Generated NMAKE File, Based on NPPTAv3.dsp
!IF "$(CFG)" == ""
CFG=NPPTAv3 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NPPTAv3 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NPPTAv3 - Win32 Release" && "$(CFG)" != "NPPTAv3 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NPPTAv3.mak" CFG="NPPTAv3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NPPTAv3 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "NPPTAv3 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\NPPTAv3.dll"


CLEAN :
	-@erase "$(INTDIR)\addrootswrap.obj"
	-@erase "$(INTDIR)\NPPTAv3.res"
	-@erase "$(INTDIR)\npvspref.obj"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\P12wrap.obj"
	-@erase "$(INTDIR)\stubs.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vscertprefswrap.obj"
	-@erase "$(INTDIR)\vsdnzwrap.obj"
	-@erase "$(INTDIR)\vsimportwrap.obj"
	-@erase "$(INTDIR)\vsprofmgmtwrap.obj"
	-@erase "$(INTDIR)\vsptadllapiwrap.obj"
	-@erase "$(INTDIR)\vsptawrap.obj"
	-@erase "$(INTDIR)\vsroamprefswrap.obj"
	-@erase "$(INTDIR)\vsselecteddigidwrap.obj"
	-@erase "$(INTDIR)\vssrchcritwrap.obj"
	-@erase "$(INTDIR)\vsuiprefswrap.obj"
	-@erase "$(INTDIR)\XEnrollWrap.obj"
	-@erase "$(OUTDIR)\NPPTAv3.dll"
	-@erase "$(OUTDIR)\NPPTAv3.exp"
	-@erase "$(OUTDIR)\NPPTAv3.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Common" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "HAVE_LONG_LONG" /Fp"$(INTDIR)\NPPTAv3.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NPPTAv3.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NPPTAv3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "..\..\..\..\modules\lib\static\release\bsafelite.lib" /nologo /dll /incremental:no /pdb:"$(OUTDIR)\NPPTAv3.pdb" /machine:I386 /def:".\src\NPPTAv3.def" /out:"$(OUTDIR)\NPPTAv3.dll" /implib:"$(OUTDIR)\NPPTAv3.lib" 
DEF_FILE= \
	".\src\NPPTAv3.def"
LINK32_OBJS= \
	"$(INTDIR)\addrootswrap.obj" \
	"$(INTDIR)\npvspref.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\P12wrap.obj" \
	"$(INTDIR)\stubs.obj" \
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
	"$(INTDIR)\NPPTAv3.res"

"$(OUTDIR)\NPPTAv3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\NPPTAv3.dll" "$(OUTDIR)\NPPTAv3.bsc"


CLEAN :
	-@erase "$(INTDIR)\addrootswrap.obj"
	-@erase "$(INTDIR)\addrootswrap.sbr"
	-@erase "$(INTDIR)\NPPTAv3.res"
	-@erase "$(INTDIR)\npvspref.obj"
	-@erase "$(INTDIR)\npvspref.sbr"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\npwin.sbr"
	-@erase "$(INTDIR)\P12wrap.obj"
	-@erase "$(INTDIR)\P12wrap.sbr"
	-@erase "$(INTDIR)\stubs.obj"
	-@erase "$(INTDIR)\stubs.sbr"
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
	-@erase "$(OUTDIR)\NPPTAv3.bsc"
	-@erase "$(OUTDIR)\NPPTAv3.dll"
	-@erase "$(OUTDIR)\NPPTAv3.exp"
	-@erase "$(OUTDIR)\NPPTAv3.ilk"
	-@erase "$(OUTDIR)\NPPTAv3.lib"
	-@erase "$(OUTDIR)\NPPTAv3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\dignot\activex\vsdnotz\include" /I "..\..\..\dignot\activex\vsdnotz\source" /I "..\..\activex\Ptav3\include\\" /I "..\..\activex\Ptav3\source\\" /I "include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Common" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "HAVE_LONG_LONG" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\NPPTAv3.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\NPPTAv3.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NPPTAv3.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addrootswrap.sbr" \
	"$(INTDIR)\npvspref.sbr" \
	"$(INTDIR)\npwin.sbr" \
	"$(INTDIR)\P12wrap.sbr" \
	"$(INTDIR)\stubs.sbr" \
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

"$(OUTDIR)\NPPTAv3.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib "..\..\..\..\modules\lib\static\debug\bsafelite.lib" /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\NPPTAv3.pdb" /debug /machine:I386 /def:".\src\NPPTAv3.def" /out:"$(OUTDIR)\NPPTAv3.dll" /implib:"$(OUTDIR)\NPPTAv3.lib" /pdbtype:sept 
DEF_FILE= \
	".\src\NPPTAv3.def"
LINK32_OBJS= \
	"$(INTDIR)\addrootswrap.obj" \
	"$(INTDIR)\npvspref.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\P12wrap.obj" \
	"$(INTDIR)\stubs.obj" \
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
	"$(INTDIR)\NPPTAv3.res"

"$(OUTDIR)\NPPTAv3.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NPPTAv3.dep")
!INCLUDE "NPPTAv3.dep"
!ELSE 
!MESSAGE Warning: cannot find "NPPTAv3.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NPPTAv3 - Win32 Release" || "$(CFG)" == "NPPTAv3 - Win32 Debug"
SOURCE=.\src\addrootswrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\addrootswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\addrootswrap.obj"	"$(INTDIR)\addrootswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\npvspref.c

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\npvspref.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\npvspref.obj"	"$(INTDIR)\npvspref.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\..\thirdparty\netscape\PluginSDK\Common\npwin.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\npwin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\npwin.obj"	"$(INTDIR)\npwin.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\P12wrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\P12wrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\P12wrap.obj"	"$(INTDIR)\P12wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\stubs.c

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\stubs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\stubs.obj"	"$(INTDIR)\stubs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vscertprefswrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vscertprefswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vscertprefswrap.obj"	"$(INTDIR)\vscertprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsdnzwrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsdnzwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsdnzwrap.obj"	"$(INTDIR)\vsdnzwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsimportwrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsimportwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsimportwrap.obj"	"$(INTDIR)\vsimportwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsprofmgmtwrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsprofmgmtwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsprofmgmtwrap.obj"	"$(INTDIR)\vsprofmgmtwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsptadllapiwrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsptadllapiwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsptadllapiwrap.obj"	"$(INTDIR)\vsptadllapiwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsptawrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsptawrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsptawrap.obj"	"$(INTDIR)\vsptawrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsroamprefswrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsroamprefswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsroamprefswrap.obj"	"$(INTDIR)\vsroamprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsselecteddigidwrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsselecteddigidwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsselecteddigidwrap.obj"	"$(INTDIR)\vsselecteddigidwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vssrchcritwrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vssrchcritwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vssrchcritwrap.obj"	"$(INTDIR)\vssrchcritwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\vsuiprefswrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\vsuiprefswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\vsuiprefswrap.obj"	"$(INTDIR)\vsuiprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\XEnrollWrap.cpp

!IF  "$(CFG)" == "NPPTAv3 - Win32 Release"


"$(INTDIR)\XEnrollWrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NPPTAv3 - Win32 Debug"


"$(INTDIR)\XEnrollWrap.obj"	"$(INTDIR)\XEnrollWrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\NPPTAv3.rc

"$(INTDIR)\NPPTAv3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 


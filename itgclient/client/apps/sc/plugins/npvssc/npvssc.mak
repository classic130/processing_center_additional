# Microsoft Developer Studio Generated NMAKE File, Based on npvssc.dsp
!IF "$(CFG)" == ""
CFG=npvssc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to npvssc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "npvssc - Win32 Release" && "$(CFG)" != "npvssc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "npvssc.mak" CFG="npvssc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "npvssc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "npvssc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "npvssc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\npvssc.dll"


CLEAN :
	-@erase "$(INTDIR)\addrootswrap.obj"
	-@erase "$(INTDIR)\implementation.obj"
	-@erase "$(INTDIR)\npvssc.res"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\P12wrap.obj"
	-@erase "$(INTDIR)\resolvercptwrap.obj"
	-@erase "$(INTDIR)\signerinfowrap.obj"
	-@erase "$(INTDIR)\stubs.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vscertprefswrap.obj"
	-@erase "$(INTDIR)\vsimportwrap.obj"
	-@erase "$(INTDIR)\vsprofmgmtwrap.obj"
	-@erase "$(INTDIR)\vsptadllapiwrap.obj"
	-@erase "$(INTDIR)\vsptawrap.obj"
	-@erase "$(INTDIR)\vsroamprefswrap.obj"
	-@erase "$(INTDIR)\vsscdllapiwrap.obj"
	-@erase "$(INTDIR)\vsscwrap.obj"
	-@erase "$(INTDIR)\vsselecteddigidwrap.obj"
	-@erase "$(INTDIR)\vssrchcritwrap.obj"
	-@erase "$(INTDIR)\vsuiprefswrap.obj"
	-@erase "$(INTDIR)\XEnrollWrap.obj"
	-@erase "$(OUTDIR)\npvssc.dll"
	-@erase "$(OUTDIR)\npvssc.exp"
	-@erase "$(OUTDIR)\npvssc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /I "..\..\activex\vssc" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Common" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Examples\CharFlipper\Source\_gen" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NPVSSC_EXPORTS" /D "HAVE_LONG_LONG" /Fp"$(INTDIR)\npvssc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\npvssc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\npvssc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bsafelite.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\npvssc.pdb" /machine:I386 /def:".\sources\NPVSSC.def" /out:"$(OUTDIR)\npvssc.dll" /implib:"$(OUTDIR)\npvssc.lib" /libpath:"..\..\..\..\modules\BSafeLite\ReleaseASM" /FORCE:MULTIPLE 
DEF_FILE= \
	".\sources\NPVSSC.def"
LINK32_OBJS= \
	"$(INTDIR)\addrootswrap.obj" \
	"$(INTDIR)\implementation.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\P12wrap.obj" \
	"$(INTDIR)\resolvercptwrap.obj" \
	"$(INTDIR)\signerinfowrap.obj" \
	"$(INTDIR)\stubs.obj" \
	"$(INTDIR)\vscertprefswrap.obj" \
	"$(INTDIR)\vsimportwrap.obj" \
	"$(INTDIR)\vsprofmgmtwrap.obj" \
	"$(INTDIR)\vsptadllapiwrap.obj" \
	"$(INTDIR)\vsptawrap.obj" \
	"$(INTDIR)\vsroamprefswrap.obj" \
	"$(INTDIR)\vsscdllapiwrap.obj" \
	"$(INTDIR)\vsscwrap.obj" \
	"$(INTDIR)\vsselecteddigidwrap.obj" \
	"$(INTDIR)\vssrchcritwrap.obj" \
	"$(INTDIR)\vsuiprefswrap.obj" \
	"$(INTDIR)\XEnrollWrap.obj" \
	"$(INTDIR)\npvssc.res"

"$(OUTDIR)\npvssc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\npvssc.dll" "$(OUTDIR)\npvssc.bsc"


CLEAN :
	-@erase "$(INTDIR)\addrootswrap.obj"
	-@erase "$(INTDIR)\addrootswrap.sbr"
	-@erase "$(INTDIR)\implementation.obj"
	-@erase "$(INTDIR)\implementation.sbr"
	-@erase "$(INTDIR)\npvssc.res"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\npwin.sbr"
	-@erase "$(INTDIR)\P12wrap.obj"
	-@erase "$(INTDIR)\P12wrap.sbr"
	-@erase "$(INTDIR)\resolvercptwrap.obj"
	-@erase "$(INTDIR)\resolvercptwrap.sbr"
	-@erase "$(INTDIR)\signerinfowrap.obj"
	-@erase "$(INTDIR)\signerinfowrap.sbr"
	-@erase "$(INTDIR)\stubs.obj"
	-@erase "$(INTDIR)\stubs.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vscertprefswrap.obj"
	-@erase "$(INTDIR)\vscertprefswrap.sbr"
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
	-@erase "$(INTDIR)\vsscdllapiwrap.obj"
	-@erase "$(INTDIR)\vsscdllapiwrap.sbr"
	-@erase "$(INTDIR)\vsscwrap.obj"
	-@erase "$(INTDIR)\vsscwrap.sbr"
	-@erase "$(INTDIR)\vsselecteddigidwrap.obj"
	-@erase "$(INTDIR)\vsselecteddigidwrap.sbr"
	-@erase "$(INTDIR)\vssrchcritwrap.obj"
	-@erase "$(INTDIR)\vssrchcritwrap.sbr"
	-@erase "$(INTDIR)\vsuiprefswrap.obj"
	-@erase "$(INTDIR)\vsuiprefswrap.sbr"
	-@erase "$(INTDIR)\XEnrollWrap.obj"
	-@erase "$(INTDIR)\XEnrollWrap.sbr"
	-@erase "$(OUTDIR)\npvssc.bsc"
	-@erase "$(OUTDIR)\npvssc.dll"
	-@erase "$(OUTDIR)\npvssc.exp"
	-@erase "$(OUTDIR)\npvssc.ilk"
	-@erase "$(OUTDIR)\npvssc.lib"
	-@erase "$(OUTDIR)\npvssc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "..\..\activex\vssc" /I "..\..\..\pta\activex\ptav3\include" /I "..\..\..\pta\activex\ptav3\source" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Include" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Common" /I "..\..\..\..\..\thirdparty\netscape\PluginSDK\Examples\CharFlipper\Source\_gen" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "NPVSSC_EXPORTS" /D "HAVE_LONG_LONG" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\npvssc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\npvssc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\npvssc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\addrootswrap.sbr" \
	"$(INTDIR)\implementation.sbr" \
	"$(INTDIR)\npwin.sbr" \
	"$(INTDIR)\P12wrap.sbr" \
	"$(INTDIR)\resolvercptwrap.sbr" \
	"$(INTDIR)\signerinfowrap.sbr" \
	"$(INTDIR)\stubs.sbr" \
	"$(INTDIR)\vscertprefswrap.sbr" \
	"$(INTDIR)\vsimportwrap.sbr" \
	"$(INTDIR)\vsprofmgmtwrap.sbr" \
	"$(INTDIR)\vsptadllapiwrap.sbr" \
	"$(INTDIR)\vsptawrap.sbr" \
	"$(INTDIR)\vsroamprefswrap.sbr" \
	"$(INTDIR)\vsscdllapiwrap.sbr" \
	"$(INTDIR)\vsscwrap.sbr" \
	"$(INTDIR)\vsselecteddigidwrap.sbr" \
	"$(INTDIR)\vssrchcritwrap.sbr" \
	"$(INTDIR)\vsuiprefswrap.sbr" \
	"$(INTDIR)\XEnrollWrap.sbr"

"$(OUTDIR)\npvssc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib bsafelite.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\npvssc.pdb" /debug /machine:I386 /def:".\sources\NPVSSC.def" /out:"$(OUTDIR)\npvssc.dll" /implib:"$(OUTDIR)\npvssc.lib" /pdbtype:sept /libpath:"..\..\..\..\modules\BSafeLite\DebugASM" 
DEF_FILE= \
	".\sources\NPVSSC.def"
LINK32_OBJS= \
	"$(INTDIR)\addrootswrap.obj" \
	"$(INTDIR)\implementation.obj" \
	"$(INTDIR)\npwin.obj" \
	"$(INTDIR)\P12wrap.obj" \
	"$(INTDIR)\resolvercptwrap.obj" \
	"$(INTDIR)\signerinfowrap.obj" \
	"$(INTDIR)\stubs.obj" \
	"$(INTDIR)\vscertprefswrap.obj" \
	"$(INTDIR)\vsimportwrap.obj" \
	"$(INTDIR)\vsprofmgmtwrap.obj" \
	"$(INTDIR)\vsptadllapiwrap.obj" \
	"$(INTDIR)\vsptawrap.obj" \
	"$(INTDIR)\vsroamprefswrap.obj" \
	"$(INTDIR)\vsscdllapiwrap.obj" \
	"$(INTDIR)\vsscwrap.obj" \
	"$(INTDIR)\vsselecteddigidwrap.obj" \
	"$(INTDIR)\vssrchcritwrap.obj" \
	"$(INTDIR)\vsuiprefswrap.obj" \
	"$(INTDIR)\XEnrollWrap.obj" \
	"$(INTDIR)\npvssc.res"

"$(OUTDIR)\npvssc.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("npvssc.dep")
!INCLUDE "npvssc.dep"
!ELSE 
!MESSAGE Warning: cannot find "npvssc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "npvssc - Win32 Release" || "$(CFG)" == "npvssc - Win32 Debug"
SOURCE=.\sources\addrootswrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\addrootswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\addrootswrap.obj"	"$(INTDIR)\addrootswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\implementation.c

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\implementation.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\implementation.obj"	"$(INTDIR)\implementation.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\npvssc.rc

"$(INTDIR)\npvssc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\..\..\..\..\thirdparty\netscape\PluginSDK\Common\npwin.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\npwin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\npwin.obj"	"$(INTDIR)\npwin.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\P12wrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\P12wrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\P12wrap.obj"	"$(INTDIR)\P12wrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\resolvercptwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\resolvercptwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\resolvercptwrap.obj"	"$(INTDIR)\resolvercptwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\signerinfowrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\signerinfowrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\signerinfowrap.obj"	"$(INTDIR)\signerinfowrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\stubs.c

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\stubs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\stubs.obj"	"$(INTDIR)\stubs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vscertprefswrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vscertprefswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vscertprefswrap.obj"	"$(INTDIR)\vscertprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsimportwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsimportwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsimportwrap.obj"	"$(INTDIR)\vsimportwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsprofmgmtwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsprofmgmtwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsprofmgmtwrap.obj"	"$(INTDIR)\vsprofmgmtwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsptadllapiwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsptadllapiwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsptadllapiwrap.obj"	"$(INTDIR)\vsptadllapiwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsptawrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsptawrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsptawrap.obj"	"$(INTDIR)\vsptawrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsroamprefswrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsroamprefswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsroamprefswrap.obj"	"$(INTDIR)\vsroamprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsscdllapiwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsscdllapiwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsscdllapiwrap.obj"	"$(INTDIR)\vsscdllapiwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsscwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsscwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsscwrap.obj"	"$(INTDIR)\vsscwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsselecteddigidwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsselecteddigidwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsselecteddigidwrap.obj"	"$(INTDIR)\vsselecteddigidwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vssrchcritwrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vssrchcritwrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vssrchcritwrap.obj"	"$(INTDIR)\vssrchcritwrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\vsuiprefswrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\vsuiprefswrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\vsuiprefswrap.obj"	"$(INTDIR)\vsuiprefswrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\XEnrollWrap.cpp

!IF  "$(CFG)" == "npvssc - Win32 Release"


"$(INTDIR)\XEnrollWrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "npvssc - Win32 Debug"


"$(INTDIR)\XEnrollWrap.obj"	"$(INTDIR)\XEnrollWrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


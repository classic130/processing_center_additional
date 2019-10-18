# Microsoft Developer Studio Generated NMAKE File, Based on ImportPKCS12.dsp
!IF "$(CFG)" == ""
CFG=ImportPKCS12 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ImportPKCS12 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ImportPKCS12 - Win32 Debug" && "$(CFG)" != "ImportPKCS12 - Win32 Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImportPKCS12.mak" CFG="ImportPKCS12 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImportPKCS12 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ImportPKCS12 - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "ImportPKCS12 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VSImport.dll" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ImportPKCS12.obj"
	-@erase "$(INTDIR)\ImportPKCS12.pch"
	-@erase "$(INTDIR)\ImportPKCS12.res"
	-@erase "$(INTDIR)\ImpPKCS12.obj"
	-@erase "$(INTDIR)\Pkcs8.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\VSImport.dll"
	-@erase "$(OUTDIR)\VSImport.exp"
	-@erase "$(OUTDIR)\VSImport.ilk"
	-@erase "$(OUTDIR)\VSImport.lib"
	-@erase "$(OUTDIR)\VSImport.pdb"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ImportPKCS12.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ImportPKCS12.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ImportPKCS12.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib crypt32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\VSImport.pdb" /debug /machine:I386 /def:".\ImportPKCS12.def" /out:"$(OUTDIR)\VSImport.dll" /implib:"$(OUTDIR)\VSImport.lib" /pdbtype:sept 
DEF_FILE= \
	".\ImportPKCS12.def"
LINK32_OBJS= \
	"$(INTDIR)\ImportPKCS12.obj" \
	"$(INTDIR)\ImpPKCS12.obj" \
	"$(INTDIR)\Pkcs8.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ImportPKCS12.res"

"$(OUTDIR)\VSImport.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\VSImport.dll
InputPath=.\Debug\VSImport.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "ImportPKCS12 - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : ".\ImportPKCS12_i.c" ".\ImportPKCS12.tlb" ".\ImportPKCS12.h" "$(OUTDIR)\VSImport.dll" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\ImportPKCS12.obj"
	-@erase "$(INTDIR)\ImportPKCS12.pch"
	-@erase "$(INTDIR)\ImportPKCS12.res"
	-@erase "$(INTDIR)\ImpPKCS12.obj"
	-@erase "$(INTDIR)\Pkcs8.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\VSImport.dll"
	-@erase "$(OUTDIR)\VSImport.exp"
	-@erase "$(OUTDIR)\VSImport.lib"
	-@erase ".\ImportPKCS12.h"
	-@erase ".\ImportPKCS12.tlb"
	-@erase ".\ImportPKCS12_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ImportPKCS12.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ImportPKCS12.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ImportPKCS12.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib crypt32.lib rpcrt4.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\VSImport.pdb" /machine:I386 /def:".\ImportPKCS12.def" /out:"$(OUTDIR)\VSImport.dll" /implib:"$(OUTDIR)\VSImport.lib" 
DEF_FILE= \
	".\ImportPKCS12.def"
LINK32_OBJS= \
	"$(INTDIR)\ImportPKCS12.obj" \
	"$(INTDIR)\ImpPKCS12.obj" \
	"$(INTDIR)\Pkcs8.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ImportPKCS12.res"

"$(OUTDIR)\VSImport.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\VSImport.dll
InputPath=.\ReleaseMinDependency\VSImport.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
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
!IF EXISTS("ImportPKCS12.dep")
!INCLUDE "ImportPKCS12.dep"
!ELSE 
!MESSAGE Warning: cannot find "ImportPKCS12.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ImportPKCS12 - Win32 Debug" || "$(CFG)" == "ImportPKCS12 - Win32 Release MinDependency"
SOURCE=.\ImportPKCS12.cpp

"$(INTDIR)\ImportPKCS12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImportPKCS12.pch" ".\ImportPKCS12_i.c" ".\ImportPKCS12.h"


SOURCE=.\ImportPKCS12.idl

!IF  "$(CFG)" == "ImportPKCS12 - Win32 Debug"

InputPath=.\ImportPKCS12.idl

".\ImportPKCS12.tlb"	".\ImportPKCS12.h"	".\ImportPKCS12_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ImportPKCS12.h" /iid "ImportPKCS12_i.c" "ImportPKCS12.idl"
<< 
	

!ELSEIF  "$(CFG)" == "ImportPKCS12 - Win32 Release MinDependency"

InputPath=.\ImportPKCS12.idl

".\ImportPKCS12.tlb"	".\ImportPKCS12.h"	".\ImportPKCS12_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	midl /Oicf /h "ImportPKCS12.h" /iid "ImportPKCS12_i.c" "ImportPKCS12.idl"
<< 
	

!ENDIF 

SOURCE=.\ImportPKCS12.rc

"$(INTDIR)\ImportPKCS12.res" : $(SOURCE) "$(INTDIR)" ".\ImportPKCS12.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ImpPKCS12.cpp

"$(INTDIR)\ImpPKCS12.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImportPKCS12.pch" ".\ImportPKCS12.h"


SOURCE=.\Pkcs8.cpp

"$(INTDIR)\Pkcs8.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImportPKCS12.pch" ".\ImportPKCS12.h"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ImportPKCS12 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Fp"$(INTDIR)\ImportPKCS12.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ImportPKCS12.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ImportPKCS12 - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /Fp"$(INTDIR)\ImportPKCS12.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ImportPKCS12.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 


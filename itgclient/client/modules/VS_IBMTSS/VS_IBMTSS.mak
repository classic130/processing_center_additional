# Microsoft Developer Studio Generated NMAKE File, Based on VS_IBMTSS.dsp
!IF "$(CFG)" == ""
CFG=VS_IBMTSS - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VS_IBMTSS - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VS_IBMTSS - Win32 Release" && "$(CFG)" != "VS_IBMTSS - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VS_IBMTSS.mak" CFG="VS_IBMTSS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VS_IBMTSS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VS_IBMTSS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "VS_IBMTSS - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VS_IBMTSS.dll"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vs_ibmtssv.res"
	-@erase "$(INTDIR)\VS_TSS_auth.obj"
	-@erase "$(INTDIR)\VS_TSS_Context.obj"
	-@erase "$(INTDIR)\VS_TSS_Data.obj"
	-@erase "$(INTDIR)\VS_TSS_Hash.obj"
	-@erase "$(INTDIR)\VS_TSS_Key.obj"
	-@erase "$(OUTDIR)\VS_IBMTSS.dll"
	-@erase "$(OUTDIR)\VS_IBMTSS.exp"
	-@erase "$(OUTDIR)\VS_IBMTSS.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "include" /I "I:\TSS SDK\IBM\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VS_IBMTSS_EXPORTS" /Fp"$(INTDIR)\VS_IBMTSS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vs_ibmtssv.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VS_IBMTSS.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib "I:\TSS SDK\IBM\lib\tspi.lib" /nologo /dll /incremental:no /pdb:"$(OUTDIR)\VS_IBMTSS.pdb" /machine:I386 /out:"$(OUTDIR)\VS_IBMTSS.dll" /implib:"$(OUTDIR)\VS_IBMTSS.lib" 
LINK32_OBJS= \
	"$(INTDIR)\VS_TSS_auth.obj" \
	"$(INTDIR)\VS_TSS_Context.obj" \
	"$(INTDIR)\VS_TSS_Data.obj" \
	"$(INTDIR)\VS_TSS_Hash.obj" \
	"$(INTDIR)\VS_TSS_Key.obj" \
	"$(INTDIR)\vs_ibmtssv.res"

"$(OUTDIR)\VS_IBMTSS.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VS_IBMTSS - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VS_IBMTSS.dll"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vs_ibmtss.res"
	-@erase "$(INTDIR)\VS_TSS_auth.obj"
	-@erase "$(INTDIR)\VS_TSS_Context.obj"
	-@erase "$(INTDIR)\VS_TSS_Data.obj"
	-@erase "$(INTDIR)\VS_TSS_Hash.obj"
	-@erase "$(INTDIR)\VS_TSS_Key.obj"
	-@erase "$(OUTDIR)\VS_IBMTSS.dll"
	-@erase "$(OUTDIR)\VS_IBMTSS.exp"
	-@erase "$(OUTDIR)\VS_IBMTSS.ilk"
	-@erase "$(OUTDIR)\VS_IBMTSS.lib"
	-@erase "$(OUTDIR)\VS_IBMTSS.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "I:\TSS SDK\IBM\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VS_IBMTSS_EXPORTS" /Fp"$(INTDIR)\VS_IBMTSS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vs_ibmtss.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VS_IBMTSS.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib "I:\TSS SDK\IBM\lib\tspi.lib" /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\VS_IBMTSS.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VS_IBMTSS.dll" /implib:"$(OUTDIR)\VS_IBMTSS.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\VS_TSS_auth.obj" \
	"$(INTDIR)\VS_TSS_Context.obj" \
	"$(INTDIR)\VS_TSS_Data.obj" \
	"$(INTDIR)\VS_TSS_Hash.obj" \
	"$(INTDIR)\VS_TSS_Key.obj" \
	"$(INTDIR)\vs_ibmtss.res"

"$(OUTDIR)\VS_IBMTSS.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("VS_IBMTSS.dep")
!INCLUDE "VS_IBMTSS.dep"
!ELSE 
!MESSAGE Warning: cannot find "VS_IBMTSS.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VS_IBMTSS - Win32 Release" || "$(CFG)" == "VS_IBMTSS - Win32 Debug"
SOURCE=.\vs_ibmtssv.rc

!IF  "$(CFG)" == "VS_IBMTSS - Win32 Release"


"$(INTDIR)\vs_ibmtssv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_IBMTSS - Win32 Debug"


"$(INTDIR)\vs_ibmtss.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_auth.cpp

"$(INTDIR)\VS_TSS_auth.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\VS_TSS_Context.cpp

"$(INTDIR)\VS_TSS_Context.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\VS_TSS_Data.cpp

"$(INTDIR)\VS_TSS_Data.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\VS_TSS_Hash.cpp

"$(INTDIR)\VS_TSS_Hash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\VS_TSS_Key.cpp

"$(INTDIR)\VS_TSS_Key.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


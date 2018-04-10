# Microsoft Developer Studio Generated NMAKE File, Based on VS_INFYTSS.dsp
!IF "$(CFG)" == ""
CFG=VS_INFYTSS - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VS_INFYTSS - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VS_INFYTSS - Win32 Release" && "$(CFG)" != "VS_INFYTSS - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VS_INFYTSS.mak" CFG="VS_INFYTSS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VS_INFYTSS - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VS_INFYTSS - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "VS_INFYTSS - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VS_INFYTSS.dll"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vs_infytssv.res"
	-@erase "$(INTDIR)\VS_TSS_Context.obj"
	-@erase "$(INTDIR)\VS_TSS_Data.obj"
	-@erase "$(INTDIR)\VS_TSS_Hash.obj"
	-@erase "$(INTDIR)\VS_TSS_Key.obj"
	-@erase "$(OUTDIR)\VS_INFYTSS.dll"
	-@erase "$(OUTDIR)\VS_INFYTSS.exp"
	-@erase "$(OUTDIR)\VS_INFYTSS.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "include" /I "I:\Infineon\TSS SDK\Include" /I "I:\Infineon\TSS SDK\Lib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VS_INFYTSS_EXPORTS" /Fp"$(INTDIR)\VS_INFYTSS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vs_infytssv.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VS_INFYTSS.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\VS_INFYTSS.pdb" /machine:I386 /out:"$(OUTDIR)\VS_INFYTSS.dll" /implib:"$(OUTDIR)\VS_INFYTSS.lib" 
LINK32_OBJS= \
	"$(INTDIR)\VS_TSS_Context.obj" \
	"$(INTDIR)\VS_TSS_Data.obj" \
	"$(INTDIR)\VS_TSS_Hash.obj" \
	"$(INTDIR)\VS_TSS_Key.obj" \
	"$(INTDIR)\vs_infytssv.res"

"$(OUTDIR)\VS_INFYTSS.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VS_INFYTSS - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VS_INFYTSS.dll" "$(OUTDIR)\VS_INFYTSS.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vs_infytss.res"
	-@erase "$(INTDIR)\VS_TSS_Context.obj"
	-@erase "$(INTDIR)\VS_TSS_Context.sbr"
	-@erase "$(INTDIR)\VS_TSS_Data.obj"
	-@erase "$(INTDIR)\VS_TSS_Data.sbr"
	-@erase "$(INTDIR)\VS_TSS_Hash.obj"
	-@erase "$(INTDIR)\VS_TSS_Hash.sbr"
	-@erase "$(INTDIR)\VS_TSS_Key.obj"
	-@erase "$(INTDIR)\VS_TSS_Key.sbr"
	-@erase "$(OUTDIR)\VS_INFYTSS.bsc"
	-@erase "$(OUTDIR)\VS_INFYTSS.dll"
	-@erase "$(OUTDIR)\VS_INFYTSS.exp"
	-@erase "$(OUTDIR)\VS_INFYTSS.ilk"
	-@erase "$(OUTDIR)\VS_INFYTSS.lib"
	-@erase "$(OUTDIR)\VS_INFYTSS.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /I "I:\Infineon\TSS SDK\Include" /I "I:\Infineon\TSS SDK\Lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VS_INFYTSS_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VS_INFYTSS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\vs_infytss.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VS_INFYTSS.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\VS_TSS_Context.sbr" \
	"$(INTDIR)\VS_TSS_Data.sbr" \
	"$(INTDIR)\VS_TSS_Hash.sbr" \
	"$(INTDIR)\VS_TSS_Key.sbr"

"$(OUTDIR)\VS_INFYTSS.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\VS_INFYTSS.pdb" /debug /machine:I386 /out:"$(OUTDIR)\VS_INFYTSS.dll" /implib:"$(OUTDIR)\VS_INFYTSS.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\VS_TSS_Context.obj" \
	"$(INTDIR)\VS_TSS_Data.obj" \
	"$(INTDIR)\VS_TSS_Hash.obj" \
	"$(INTDIR)\VS_TSS_Key.obj" \
	"$(INTDIR)\vs_infytss.res"

"$(OUTDIR)\VS_INFYTSS.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("VS_INFYTSS.dep")
!INCLUDE "VS_INFYTSS.dep"
!ELSE 
!MESSAGE Warning: cannot find "VS_INFYTSS.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VS_INFYTSS - Win32 Release" || "$(CFG)" == "VS_INFYTSS - Win32 Debug"
SOURCE=.\vs_infytssv.rc

!IF  "$(CFG)" == "VS_INFYTSS - Win32 Release"


"$(INTDIR)\vs_infytssv.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_INFYTSS - Win32 Debug"


"$(INTDIR)\vs_infytss.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Context.cpp

!IF  "$(CFG)" == "VS_INFYTSS - Win32 Release"


"$(INTDIR)\VS_TSS_Context.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_INFYTSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Context.obj"	"$(INTDIR)\VS_TSS_Context.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Data.cpp

!IF  "$(CFG)" == "VS_INFYTSS - Win32 Release"


"$(INTDIR)\VS_TSS_Data.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_INFYTSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Data.obj"	"$(INTDIR)\VS_TSS_Data.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Hash.cpp

!IF  "$(CFG)" == "VS_INFYTSS - Win32 Release"


"$(INTDIR)\VS_TSS_Hash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_INFYTSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Hash.obj"	"$(INTDIR)\VS_TSS_Hash.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Key.cpp

!IF  "$(CFG)" == "VS_INFYTSS - Win32 Release"


"$(INTDIR)\VS_TSS_Key.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_INFYTSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Key.obj"	"$(INTDIR)\VS_TSS_Key.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


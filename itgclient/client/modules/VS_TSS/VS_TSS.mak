# Microsoft Developer Studio Generated NMAKE File, Based on VS_TSS.dsp
!IF "$(CFG)" == ""
CFG=VS_TSS - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VS_TSS - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VS_TSS - Win32 Release" && "$(CFG)" != "VS_TSS - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VS_TSS.mak" CFG="VS_TSS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VS_TSS - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "VS_TSS - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "VS_TSS - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\VS_TSS.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VS_TSS_auth.obj"
	-@erase "$(INTDIR)\VS_TSS_Context.obj"
	-@erase "$(INTDIR)\VS_TSS_Data.obj"
	-@erase "$(INTDIR)\VS_TSS_Hash.obj"
	-@erase "$(INTDIR)\VS_TSS_Key.obj"
	-@erase "$(OUTDIR)\VS_TSS.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "include" /I "I:\TSS SDK\IBM\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\VS_TSS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VS_TSS.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\VS_TSS.lib" 
LIB32_OBJS= \
	"$(INTDIR)\VS_TSS_auth.obj" \
	"$(INTDIR)\VS_TSS_Context.obj" \
	"$(INTDIR)\VS_TSS_Data.obj" \
	"$(INTDIR)\VS_TSS_Hash.obj" \
	"$(INTDIR)\VS_TSS_Key.obj"

"$(OUTDIR)\VS_TSS.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VS_TSS - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\VS_TSS.lib" "$(OUTDIR)\VS_TSS.bsc"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VS_TSS_auth.obj"
	-@erase "$(INTDIR)\VS_TSS_auth.sbr"
	-@erase "$(INTDIR)\VS_TSS_Context.obj"
	-@erase "$(INTDIR)\VS_TSS_Context.sbr"
	-@erase "$(INTDIR)\VS_TSS_Data.obj"
	-@erase "$(INTDIR)\VS_TSS_Data.sbr"
	-@erase "$(INTDIR)\VS_TSS_Hash.obj"
	-@erase "$(INTDIR)\VS_TSS_Hash.sbr"
	-@erase "$(INTDIR)\VS_TSS_Key.obj"
	-@erase "$(INTDIR)\VS_TSS_Key.sbr"
	-@erase "$(OUTDIR)\VS_TSS.bsc"
	-@erase "$(OUTDIR)\VS_TSS.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "include" /I "I:\TSS SDK\IBM\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VS_TSS.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VS_TSS.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\VS_TSS_auth.sbr" \
	"$(INTDIR)\VS_TSS_Context.sbr" \
	"$(INTDIR)\VS_TSS_Data.sbr" \
	"$(INTDIR)\VS_TSS_Hash.sbr" \
	"$(INTDIR)\VS_TSS_Key.sbr"

"$(OUTDIR)\VS_TSS.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\VS_TSS.lib" 
LIB32_OBJS= \
	"$(INTDIR)\VS_TSS_auth.obj" \
	"$(INTDIR)\VS_TSS_Context.obj" \
	"$(INTDIR)\VS_TSS_Data.obj" \
	"$(INTDIR)\VS_TSS_Hash.obj" \
	"$(INTDIR)\VS_TSS_Key.obj"

"$(OUTDIR)\VS_TSS.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VS_TSS.dep")
!INCLUDE "VS_TSS.dep"
!ELSE 
!MESSAGE Warning: cannot find "VS_TSS.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VS_TSS - Win32 Release" || "$(CFG)" == "VS_TSS - Win32 Debug"
SOURCE=.\src\VS_TSS_auth.cpp

!IF  "$(CFG)" == "VS_TSS - Win32 Release"


"$(INTDIR)\VS_TSS_auth.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_TSS - Win32 Debug"


"$(INTDIR)\VS_TSS_auth.obj"	"$(INTDIR)\VS_TSS_auth.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Context.cpp

!IF  "$(CFG)" == "VS_TSS - Win32 Release"


"$(INTDIR)\VS_TSS_Context.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_TSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Context.obj"	"$(INTDIR)\VS_TSS_Context.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Data.cpp

!IF  "$(CFG)" == "VS_TSS - Win32 Release"


"$(INTDIR)\VS_TSS_Data.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_TSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Data.obj"	"$(INTDIR)\VS_TSS_Data.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Hash.cpp

!IF  "$(CFG)" == "VS_TSS - Win32 Release"


"$(INTDIR)\VS_TSS_Hash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_TSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Hash.obj"	"$(INTDIR)\VS_TSS_Hash.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\VS_TSS_Key.cpp

!IF  "$(CFG)" == "VS_TSS - Win32 Release"


"$(INTDIR)\VS_TSS_Key.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "VS_TSS - Win32 Debug"


"$(INTDIR)\VS_TSS_Key.obj"	"$(INTDIR)\VS_TSS_Key.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


# Microsoft Developer Studio Generated NMAKE File, Based on policymodule.dsp
!IF "$(CFG)" == ""
CFG=policymodule - Win32 Debug
!MESSAGE No configuration specified. Defaulting to policymodule - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "policymodule - Win32 Release" && "$(CFG)" != "policymodule - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "policymodule.mak" CFG="policymodule - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "policymodule - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "policymodule - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "policymodule - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\policymodule.lib"


CLEAN :
	-@erase "$(INTDIR)\base64.obj"
	-@erase "$(INTDIR)\callbacktest.obj"
	-@erase "$(INTDIR)\pmctest.obj"
	-@erase "$(INTDIR)\pmsptest.obj"
	-@erase "$(INTDIR)\pmutiltest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vspmc.obj"
	-@erase "$(INTDIR)\vspmctype.obj"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(OUTDIR)\policymodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\policymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\policymodule.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\policymodule.lib" 
LIB32_OBJS= \
	"$(INTDIR)\base64.obj" \
	"$(INTDIR)\callbacktest.obj" \
	"$(INTDIR)\pmctest.obj" \
	"$(INTDIR)\pmsptest.obj" \
	"$(INTDIR)\pmutiltest.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmc.obj" \
	"$(INTDIR)\vspmctype.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj"

"$(OUTDIR)\policymodule.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "policymodule - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\policymodule.lib"


CLEAN :
	-@erase "$(INTDIR)\base64.obj"
	-@erase "$(INTDIR)\callbacktest.obj"
	-@erase "$(INTDIR)\pmctest.obj"
	-@erase "$(INTDIR)\pmsptest.obj"
	-@erase "$(INTDIR)\pmutiltest.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vscontainer.obj"
	-@erase "$(INTDIR)\vsnvp.obj"
	-@erase "$(INTDIR)\vsnvp_file.obj"
	-@erase "$(INTDIR)\vspmc.obj"
	-@erase "$(INTDIR)\vspmctype.obj"
	-@erase "$(INTDIR)\vspmsp.obj"
	-@erase "$(INTDIR)\vspmutil.obj"
	-@erase "$(INTDIR)\vspolicyfile.obj"
	-@erase "$(OUTDIR)\policymodule.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\policymodule.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\policymodule.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\policymodule.lib" 
LIB32_OBJS= \
	"$(INTDIR)\base64.obj" \
	"$(INTDIR)\callbacktest.obj" \
	"$(INTDIR)\pmctest.obj" \
	"$(INTDIR)\pmsptest.obj" \
	"$(INTDIR)\pmutiltest.obj" \
	"$(INTDIR)\vscontainer.obj" \
	"$(INTDIR)\vsnvp.obj" \
	"$(INTDIR)\vsnvp_file.obj" \
	"$(INTDIR)\vspmc.obj" \
	"$(INTDIR)\vspmctype.obj" \
	"$(INTDIR)\vspmsp.obj" \
	"$(INTDIR)\vspmutil.obj" \
	"$(INTDIR)\vspolicyfile.obj"

"$(OUTDIR)\policymodule.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("policymodule.dep")
!INCLUDE "policymodule.dep"
!ELSE 
!MESSAGE Warning: cannot find "policymodule.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "policymodule - Win32 Release" || "$(CFG)" == "policymodule - Win32 Debug"
SOURCE=.\sources\base64.cpp

"$(INTDIR)\base64.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\callbacktest.cpp

"$(INTDIR)\callbacktest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\pmctest.cpp

"$(INTDIR)\pmctest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\pmsptest.cpp

"$(INTDIR)\pmsptest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\pmutiltest.cpp

"$(INTDIR)\pmutiltest.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vscontainer.cpp

"$(INTDIR)\vscontainer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsnvp.cpp

"$(INTDIR)\vsnvp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsnvp_file.cpp

"$(INTDIR)\vsnvp_file.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vspmc.cpp

"$(INTDIR)\vspmc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vspmctype.cpp

"$(INTDIR)\vspmctype.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vspmsp.cpp

"$(INTDIR)\vspmsp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vspmutil.cpp

"$(INTDIR)\vspmutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vspolicyfile.cpp

"$(INTDIR)\vspolicyfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


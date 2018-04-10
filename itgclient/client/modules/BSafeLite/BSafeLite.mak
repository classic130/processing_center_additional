# Microsoft Developer Studio Generated NMAKE File, Based on BSafeLite.dsp
!IF "$(CFG)" == ""
CFG=BSafeLite - Win32 DebugASM
!MESSAGE No configuration specified. Defaulting to BSafeLite - Win32 DebugASM.
!ENDIF 

!IF "$(CFG)" != "BSafeLite - Win32 Release" && "$(CFG)" != "BSafeLite - Win32 Debug" && "$(CFG)" != "BSafeLite - Win32 DebugASM" && "$(CFG)" != "BSafeLite - Win32 ReleaseASM"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BSafeLite.mak" CFG="BSafeLite - Win32 DebugASM"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BSafeLite - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BSafeLite - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "BSafeLite - Win32 DebugASM" (based on "Win32 (x86) Static Library")
!MESSAGE "BSafeLite - Win32 ReleaseASM" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"


CLEAN :
	-@erase "$(INTDIR)\cmparith.obj"
	-@erase "$(INTDIR)\cmparith.sbr"
	-@erase "$(INTDIR)\cmpbits.obj"
	-@erase "$(INTDIR)\cmpbits.sbr"
	-@erase "$(INTDIR)\cmpcnv.obj"
	-@erase "$(INTDIR)\cmpcnv.sbr"
	-@erase "$(INTDIR)\cmpmdexp.obj"
	-@erase "$(INTDIR)\cmpmdexp.sbr"
	-@erase "$(INTDIR)\cmpmem.obj"
	-@erase "$(INTDIR)\cmpmem.sbr"
	-@erase "$(INTDIR)\cmpmod.obj"
	-@erase "$(INTDIR)\cmpmod.sbr"
	-@erase "$(INTDIR)\cmpmontg.obj"
	-@erase "$(INTDIR)\cmpmontg.sbr"
	-@erase "$(INTDIR)\cmpmuldv.obj"
	-@erase "$(INTDIR)\cmpmuldv.sbr"
	-@erase "$(INTDIR)\cmpspprt.obj"
	-@erase "$(INTDIR)\cmpspprt.sbr"
	-@erase "$(INTDIR)\cmpvectr.obj"
	-@erase "$(INTDIR)\cmpvectr.sbr"
	-@erase "$(INTDIR)\des.obj"
	-@erase "$(INTDIR)\des.sbr"
	-@erase "$(INTDIR)\desedec.obj"
	-@erase "$(INTDIR)\desedec.sbr"
	-@erase "$(INTDIR)\deseded.obj"
	-@erase "$(INTDIR)\deseded.sbr"
	-@erase "$(INTDIR)\desedee.obj"
	-@erase "$(INTDIR)\desedee.sbr"
	-@erase "$(INTDIR)\digrand.obj"
	-@erase "$(INTDIR)\digrand.sbr"
	-@erase "$(INTDIR)\integrate.obj"
	-@erase "$(INTDIR)\integrate.sbr"
	-@erase "$(INTDIR)\md2.obj"
	-@erase "$(INTDIR)\md2.sbr"
	-@erase "$(INTDIR)\md5.obj"
	-@erase "$(INTDIR)\md5.sbr"
	-@erase "$(INTDIR)\md5rand.obj"
	-@erase "$(INTDIR)\md5rand.sbr"
	-@erase "$(INTDIR)\prime.obj"
	-@erase "$(INTDIR)\prime.sbr"
	-@erase "$(INTDIR)\rc2.obj"
	-@erase "$(INTDIR)\rc2.sbr"
	-@erase "$(INTDIR)\rc2cbd.obj"
	-@erase "$(INTDIR)\rc2cbd.sbr"
	-@erase "$(INTDIR)\rc2cbe.obj"
	-@erase "$(INTDIR)\rc2cbe.sbr"
	-@erase "$(INTDIR)\rc4.obj"
	-@erase "$(INTDIR)\rc4.sbr"
	-@erase "$(INTDIR)\rsa.obj"
	-@erase "$(INTDIR)\rsa.sbr"
	-@erase "$(INTDIR)\rsakeygn.obj"
	-@erase "$(INTDIR)\rsakeygn.sbr"
	-@erase "$(INTDIR)\seccbcd.obj"
	-@erase "$(INTDIR)\seccbcd.sbr"
	-@erase "$(INTDIR)\seccbce.obj"
	-@erase "$(INTDIR)\seccbce.sbr"
	-@erase "$(INTDIR)\secrcbc.obj"
	-@erase "$(INTDIR)\secrcbc.sbr"
	-@erase "$(INTDIR)\sha.obj"
	-@erase "$(INTDIR)\sha.sbr"
	-@erase "$(INTDIR)\shacomm.obj"
	-@erase "$(INTDIR)\shacomm.sbr"
	-@erase "$(INTDIR)\uint4.obj"
	-@erase "$(INTDIR)\uint4.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\BSafeLite.bsc"
	-@erase "$(OUTDIR)\BSafeLite.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BSafeLite.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BSafeLite.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cmparith.sbr" \
	"$(INTDIR)\cmpbits.sbr" \
	"$(INTDIR)\cmpcnv.sbr" \
	"$(INTDIR)\cmpmdexp.sbr" \
	"$(INTDIR)\cmpmem.sbr" \
	"$(INTDIR)\cmpmod.sbr" \
	"$(INTDIR)\cmpmontg.sbr" \
	"$(INTDIR)\cmpmuldv.sbr" \
	"$(INTDIR)\cmpspprt.sbr" \
	"$(INTDIR)\cmpvectr.sbr" \
	"$(INTDIR)\des.sbr" \
	"$(INTDIR)\desedec.sbr" \
	"$(INTDIR)\deseded.sbr" \
	"$(INTDIR)\desedee.sbr" \
	"$(INTDIR)\digrand.sbr" \
	"$(INTDIR)\md2.sbr" \
	"$(INTDIR)\md5.sbr" \
	"$(INTDIR)\md5rand.sbr" \
	"$(INTDIR)\prime.sbr" \
	"$(INTDIR)\rc2.sbr" \
	"$(INTDIR)\rc2cbd.sbr" \
	"$(INTDIR)\rc2cbe.sbr" \
	"$(INTDIR)\rc4.sbr" \
	"$(INTDIR)\rsa.sbr" \
	"$(INTDIR)\rsakeygn.sbr" \
	"$(INTDIR)\seccbcd.sbr" \
	"$(INTDIR)\seccbce.sbr" \
	"$(INTDIR)\secrcbc.sbr" \
	"$(INTDIR)\sha.sbr" \
	"$(INTDIR)\shacomm.sbr" \
	"$(INTDIR)\uint4.sbr" \
	"$(INTDIR)\integrate.sbr"

"$(OUTDIR)\BSafeLite.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\BSafeLite.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cmparith.obj" \
	"$(INTDIR)\cmpbits.obj" \
	"$(INTDIR)\cmpcnv.obj" \
	"$(INTDIR)\cmpmdexp.obj" \
	"$(INTDIR)\cmpmem.obj" \
	"$(INTDIR)\cmpmod.obj" \
	"$(INTDIR)\cmpmontg.obj" \
	"$(INTDIR)\cmpmuldv.obj" \
	"$(INTDIR)\cmpspprt.obj" \
	"$(INTDIR)\cmpvectr.obj" \
	"$(INTDIR)\des.obj" \
	"$(INTDIR)\desedec.obj" \
	"$(INTDIR)\deseded.obj" \
	"$(INTDIR)\desedee.obj" \
	"$(INTDIR)\digrand.obj" \
	"$(INTDIR)\md2.obj" \
	"$(INTDIR)\md5.obj" \
	"$(INTDIR)\md5rand.obj" \
	"$(INTDIR)\prime.obj" \
	"$(INTDIR)\rc2.obj" \
	"$(INTDIR)\rc2cbd.obj" \
	"$(INTDIR)\rc2cbe.obj" \
	"$(INTDIR)\rc4.obj" \
	"$(INTDIR)\rsa.obj" \
	"$(INTDIR)\rsakeygn.obj" \
	"$(INTDIR)\seccbcd.obj" \
	"$(INTDIR)\seccbce.obj" \
	"$(INTDIR)\secrcbc.obj" \
	"$(INTDIR)\sha.obj" \
	"$(INTDIR)\shacomm.obj" \
	"$(INTDIR)\uint4.obj" \
	"$(INTDIR)\integrate.obj"

"$(OUTDIR)\BSafeLite.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"
   if not exist "..\lib\static\release" md "..\lib\static\release"
	copy release\BSafeLite.lib "..\lib\static\release"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"


CLEAN :
	-@erase "$(INTDIR)\cmparith.obj"
	-@erase "$(INTDIR)\cmparith.sbr"
	-@erase "$(INTDIR)\cmpbits.obj"
	-@erase "$(INTDIR)\cmpbits.sbr"
	-@erase "$(INTDIR)\cmpcnv.obj"
	-@erase "$(INTDIR)\cmpcnv.sbr"
	-@erase "$(INTDIR)\cmpmdexp.obj"
	-@erase "$(INTDIR)\cmpmdexp.sbr"
	-@erase "$(INTDIR)\cmpmem.obj"
	-@erase "$(INTDIR)\cmpmem.sbr"
	-@erase "$(INTDIR)\cmpmod.obj"
	-@erase "$(INTDIR)\cmpmod.sbr"
	-@erase "$(INTDIR)\cmpmontg.obj"
	-@erase "$(INTDIR)\cmpmontg.sbr"
	-@erase "$(INTDIR)\cmpmuldv.obj"
	-@erase "$(INTDIR)\cmpmuldv.sbr"
	-@erase "$(INTDIR)\cmpspprt.obj"
	-@erase "$(INTDIR)\cmpspprt.sbr"
	-@erase "$(INTDIR)\cmpvectr.obj"
	-@erase "$(INTDIR)\cmpvectr.sbr"
	-@erase "$(INTDIR)\des.obj"
	-@erase "$(INTDIR)\des.sbr"
	-@erase "$(INTDIR)\desedec.obj"
	-@erase "$(INTDIR)\desedec.sbr"
	-@erase "$(INTDIR)\deseded.obj"
	-@erase "$(INTDIR)\deseded.sbr"
	-@erase "$(INTDIR)\desedee.obj"
	-@erase "$(INTDIR)\desedee.sbr"
	-@erase "$(INTDIR)\digrand.obj"
	-@erase "$(INTDIR)\digrand.sbr"
	-@erase "$(INTDIR)\integrate.obj"
	-@erase "$(INTDIR)\integrate.sbr"
	-@erase "$(INTDIR)\md2.obj"
	-@erase "$(INTDIR)\md2.sbr"
	-@erase "$(INTDIR)\md5.obj"
	-@erase "$(INTDIR)\md5.sbr"
	-@erase "$(INTDIR)\md5rand.obj"
	-@erase "$(INTDIR)\md5rand.sbr"
	-@erase "$(INTDIR)\prime.obj"
	-@erase "$(INTDIR)\prime.sbr"
	-@erase "$(INTDIR)\rc2.obj"
	-@erase "$(INTDIR)\rc2.sbr"
	-@erase "$(INTDIR)\rc2cbd.obj"
	-@erase "$(INTDIR)\rc2cbd.sbr"
	-@erase "$(INTDIR)\rc2cbe.obj"
	-@erase "$(INTDIR)\rc2cbe.sbr"
	-@erase "$(INTDIR)\rc4.obj"
	-@erase "$(INTDIR)\rc4.sbr"
	-@erase "$(INTDIR)\rsa.obj"
	-@erase "$(INTDIR)\rsa.sbr"
	-@erase "$(INTDIR)\rsakeygn.obj"
	-@erase "$(INTDIR)\rsakeygn.sbr"
	-@erase "$(INTDIR)\seccbcd.obj"
	-@erase "$(INTDIR)\seccbcd.sbr"
	-@erase "$(INTDIR)\seccbce.obj"
	-@erase "$(INTDIR)\seccbce.sbr"
	-@erase "$(INTDIR)\secrcbc.obj"
	-@erase "$(INTDIR)\secrcbc.sbr"
	-@erase "$(INTDIR)\sha.obj"
	-@erase "$(INTDIR)\sha.sbr"
	-@erase "$(INTDIR)\shacomm.obj"
	-@erase "$(INTDIR)\shacomm.sbr"
	-@erase "$(INTDIR)\uint4.obj"
	-@erase "$(INTDIR)\uint4.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BSafeLite.bsc"
	-@erase "$(OUTDIR)\BSafeLite.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/MD /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BSafeLite.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BSafeLite.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cmparith.sbr" \
	"$(INTDIR)\cmpbits.sbr" \
	"$(INTDIR)\cmpcnv.sbr" \
	"$(INTDIR)\cmpmdexp.sbr" \
	"$(INTDIR)\cmpmem.sbr" \
	"$(INTDIR)\cmpmod.sbr" \
	"$(INTDIR)\cmpmontg.sbr" \
	"$(INTDIR)\cmpmuldv.sbr" \
	"$(INTDIR)\cmpspprt.sbr" \
	"$(INTDIR)\cmpvectr.sbr" \
	"$(INTDIR)\des.sbr" \
	"$(INTDIR)\desedec.sbr" \
	"$(INTDIR)\deseded.sbr" \
	"$(INTDIR)\desedee.sbr" \
	"$(INTDIR)\digrand.sbr" \
	"$(INTDIR)\md2.sbr" \
	"$(INTDIR)\md5.sbr" \
	"$(INTDIR)\md5rand.sbr" \
	"$(INTDIR)\prime.sbr" \
	"$(INTDIR)\rc2.sbr" \
	"$(INTDIR)\rc2cbd.sbr" \
	"$(INTDIR)\rc2cbe.sbr" \
	"$(INTDIR)\rc4.sbr" \
	"$(INTDIR)\rsa.sbr" \
	"$(INTDIR)\rsakeygn.sbr" \
	"$(INTDIR)\seccbcd.sbr" \
	"$(INTDIR)\seccbce.sbr" \
	"$(INTDIR)\secrcbc.sbr" \
	"$(INTDIR)\sha.sbr" \
	"$(INTDIR)\shacomm.sbr" \
	"$(INTDIR)\uint4.sbr" \
	"$(INTDIR)\integrate.sbr"

"$(OUTDIR)\BSafeLite.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\BSafeLite.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cmparith.obj" \
	"$(INTDIR)\cmpbits.obj" \
	"$(INTDIR)\cmpcnv.obj" \
	"$(INTDIR)\cmpmdexp.obj" \
	"$(INTDIR)\cmpmem.obj" \
	"$(INTDIR)\cmpmod.obj" \
	"$(INTDIR)\cmpmontg.obj" \
	"$(INTDIR)\cmpmuldv.obj" \
	"$(INTDIR)\cmpspprt.obj" \
	"$(INTDIR)\cmpvectr.obj" \
	"$(INTDIR)\des.obj" \
	"$(INTDIR)\desedec.obj" \
	"$(INTDIR)\deseded.obj" \
	"$(INTDIR)\desedee.obj" \
	"$(INTDIR)\digrand.obj" \
	"$(INTDIR)\md2.obj" \
	"$(INTDIR)\md5.obj" \
	"$(INTDIR)\md5rand.obj" \
	"$(INTDIR)\prime.obj" \
	"$(INTDIR)\rc2.obj" \
	"$(INTDIR)\rc2cbd.obj" \
	"$(INTDIR)\rc2cbe.obj" \
	"$(INTDIR)\rc4.obj" \
	"$(INTDIR)\rsa.obj" \
	"$(INTDIR)\rsakeygn.obj" \
	"$(INTDIR)\seccbcd.obj" \
	"$(INTDIR)\seccbce.obj" \
	"$(INTDIR)\secrcbc.obj" \
	"$(INTDIR)\sha.obj" \
	"$(INTDIR)\shacomm.obj" \
	"$(INTDIR)\uint4.obj" \
	"$(INTDIR)\integrate.obj"

"$(OUTDIR)\BSafeLite.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"
   if not exist "..\lib\static\debug" md "..\lib\static\debug"
	copy debug\BSafeLite.lib "..\lib\static\debug"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

OUTDIR=.\DebugASM
INTDIR=.\DebugASM
# Begin Custom Macros
OutDir=.\DebugASM
# End Custom Macros

ALL : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"


CLEAN :
	-@erase "$(INTDIR)\cmparith.obj"
	-@erase "$(INTDIR)\cmparith.sbr"
	-@erase "$(INTDIR)\cmpbits.obj"
	-@erase "$(INTDIR)\cmpbits.sbr"
	-@erase "$(INTDIR)\cmpcnv.obj"
	-@erase "$(INTDIR)\cmpcnv.sbr"
	-@erase "$(INTDIR)\cmpmdi32.obj"
	-@erase "$(INTDIR)\cmpmdi32.sbr"
	-@erase "$(INTDIR)\cmpmem.obj"
	-@erase "$(INTDIR)\cmpmem.sbr"
	-@erase "$(INTDIR)\cmpmgi32.obj"
	-@erase "$(INTDIR)\cmpmgi32.sbr"
	-@erase "$(INTDIR)\cmpmod.obj"
	-@erase "$(INTDIR)\cmpmod.sbr"
	-@erase "$(INTDIR)\cmpmxi32.obj"
	-@erase "$(INTDIR)\cmpmxi32.sbr"
	-@erase "$(INTDIR)\cmpspprt.obj"
	-@erase "$(INTDIR)\cmpspprt.sbr"
	-@erase "$(INTDIR)\cmpvectr.obj"
	-@erase "$(INTDIR)\cmpvectr.sbr"
	-@erase "$(INTDIR)\des.obj"
	-@erase "$(INTDIR)\des.sbr"
	-@erase "$(INTDIR)\desedec.obj"
	-@erase "$(INTDIR)\desedec.sbr"
	-@erase "$(INTDIR)\deseded.obj"
	-@erase "$(INTDIR)\deseded.sbr"
	-@erase "$(INTDIR)\desedee.obj"
	-@erase "$(INTDIR)\desedee.sbr"
	-@erase "$(INTDIR)\digrand.obj"
	-@erase "$(INTDIR)\digrand.sbr"
	-@erase "$(INTDIR)\integrate.obj"
	-@erase "$(INTDIR)\integrate.sbr"
	-@erase "$(INTDIR)\md2.obj"
	-@erase "$(INTDIR)\md2.sbr"
	-@erase "$(INTDIR)\md5.obj"
	-@erase "$(INTDIR)\md5.sbr"
	-@erase "$(INTDIR)\md5rand.obj"
	-@erase "$(INTDIR)\md5rand.sbr"
	-@erase "$(INTDIR)\prime.obj"
	-@erase "$(INTDIR)\prime.sbr"
	-@erase "$(INTDIR)\rc2.obj"
	-@erase "$(INTDIR)\rc2.sbr"
	-@erase "$(INTDIR)\rc2cbd.obj"
	-@erase "$(INTDIR)\rc2cbd.sbr"
	-@erase "$(INTDIR)\rc2cbe.obj"
	-@erase "$(INTDIR)\rc2cbe.sbr"
	-@erase "$(INTDIR)\rc4.obj"
	-@erase "$(INTDIR)\rc4.sbr"
	-@erase "$(INTDIR)\rsa.obj"
	-@erase "$(INTDIR)\rsa.sbr"
	-@erase "$(INTDIR)\rsakeygn.obj"
	-@erase "$(INTDIR)\rsakeygn.sbr"
	-@erase "$(INTDIR)\seccbcd.obj"
	-@erase "$(INTDIR)\seccbcd.sbr"
	-@erase "$(INTDIR)\seccbce.obj"
	-@erase "$(INTDIR)\seccbce.sbr"
	-@erase "$(INTDIR)\secrcbc.obj"
	-@erase "$(INTDIR)\secrcbc.sbr"
	-@erase "$(INTDIR)\sha.obj"
	-@erase "$(INTDIR)\sha.sbr"
	-@erase "$(INTDIR)\shacomm.obj"
	-@erase "$(INTDIR)\shacomm.sbr"
	-@erase "$(INTDIR)\uint4.obj"
	-@erase "$(INTDIR)\uint4.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\BSafeLite.bsc"
	-@erase "$(OUTDIR)\BSafeLite.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BSafeLite.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BSafeLite.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cmparith.sbr" \
	"$(INTDIR)\cmpbits.sbr" \
	"$(INTDIR)\cmpcnv.sbr" \
	"$(INTDIR)\cmpmdi32.sbr" \
	"$(INTDIR)\cmpmem.sbr" \
	"$(INTDIR)\cmpmgi32.sbr" \
	"$(INTDIR)\cmpmod.sbr" \
	"$(INTDIR)\cmpmxi32.sbr" \
	"$(INTDIR)\cmpspprt.sbr" \
	"$(INTDIR)\cmpvectr.sbr" \
	"$(INTDIR)\des.sbr" \
	"$(INTDIR)\desedec.sbr" \
	"$(INTDIR)\deseded.sbr" \
	"$(INTDIR)\desedee.sbr" \
	"$(INTDIR)\digrand.sbr" \
	"$(INTDIR)\md2.sbr" \
	"$(INTDIR)\md5.sbr" \
	"$(INTDIR)\md5rand.sbr" \
	"$(INTDIR)\prime.sbr" \
	"$(INTDIR)\rc2.sbr" \
	"$(INTDIR)\rc2cbd.sbr" \
	"$(INTDIR)\rc2cbe.sbr" \
	"$(INTDIR)\rc4.sbr" \
	"$(INTDIR)\rsa.sbr" \
	"$(INTDIR)\rsakeygn.sbr" \
	"$(INTDIR)\seccbcd.sbr" \
	"$(INTDIR)\seccbce.sbr" \
	"$(INTDIR)\secrcbc.sbr" \
	"$(INTDIR)\sha.sbr" \
	"$(INTDIR)\shacomm.sbr" \
	"$(INTDIR)\uint4.sbr" \
	"$(INTDIR)\integrate.sbr"

"$(OUTDIR)\BSafeLite.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\BSafeLite.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cmparith.obj" \
	"$(INTDIR)\cmpbits.obj" \
	"$(INTDIR)\cmpcnv.obj" \
	"$(INTDIR)\cmpmdi32.obj" \
	"$(INTDIR)\cmpmem.obj" \
	"$(INTDIR)\cmpmgi32.obj" \
	"$(INTDIR)\cmpmod.obj" \
	"$(INTDIR)\cmpmxi32.obj" \
	"$(INTDIR)\cmpspprt.obj" \
	"$(INTDIR)\cmpvectr.obj" \
	"$(INTDIR)\des.obj" \
	"$(INTDIR)\desedec.obj" \
	"$(INTDIR)\deseded.obj" \
	"$(INTDIR)\desedee.obj" \
	"$(INTDIR)\digrand.obj" \
	"$(INTDIR)\md2.obj" \
	"$(INTDIR)\md5.obj" \
	"$(INTDIR)\md5rand.obj" \
	"$(INTDIR)\prime.obj" \
	"$(INTDIR)\rc2.obj" \
	"$(INTDIR)\rc2cbd.obj" \
	"$(INTDIR)\rc2cbe.obj" \
	"$(INTDIR)\rc4.obj" \
	"$(INTDIR)\rsa.obj" \
	"$(INTDIR)\rsakeygn.obj" \
	"$(INTDIR)\seccbcd.obj" \
	"$(INTDIR)\seccbce.obj" \
	"$(INTDIR)\secrcbc.obj" \
	"$(INTDIR)\sha.obj" \
	"$(INTDIR)\shacomm.obj" \
	"$(INTDIR)\uint4.obj" \
	"$(INTDIR)\integrate.obj" \
	"$(INTDIR)\cmpati32.obj" \
	"$(INTDIR)\cmpmpi32.obj" \
	"$(INTDIR)\cmpmsi32.obj" \
	"$(INTDIR)\cmpvmi32.obj"

"$(OUTDIR)\BSafeLite.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\DebugASM
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"
   if not exist "..\lib\static\debug" md "..\lib\static\debug"
	copy debugASM\BSafeLite.lib "..\lib\static\debug"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

OUTDIR=.\ReleaseASM
INTDIR=.\ReleaseASM
# Begin Custom Macros
OutDir=.\ReleaseASM
# End Custom Macros

ALL : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"


CLEAN :
	-@erase "$(INTDIR)\cmparith.obj"
	-@erase "$(INTDIR)\cmparith.sbr"
	-@erase "$(INTDIR)\cmpbits.obj"
	-@erase "$(INTDIR)\cmpbits.sbr"
	-@erase "$(INTDIR)\cmpcnv.obj"
	-@erase "$(INTDIR)\cmpcnv.sbr"
	-@erase "$(INTDIR)\cmpmdi32.obj"
	-@erase "$(INTDIR)\cmpmdi32.sbr"
	-@erase "$(INTDIR)\cmpmem.obj"
	-@erase "$(INTDIR)\cmpmem.sbr"
	-@erase "$(INTDIR)\cmpmgi32.obj"
	-@erase "$(INTDIR)\cmpmgi32.sbr"
	-@erase "$(INTDIR)\cmpmod.obj"
	-@erase "$(INTDIR)\cmpmod.sbr"
	-@erase "$(INTDIR)\cmpmxi32.obj"
	-@erase "$(INTDIR)\cmpmxi32.sbr"
	-@erase "$(INTDIR)\cmpspprt.obj"
	-@erase "$(INTDIR)\cmpspprt.sbr"
	-@erase "$(INTDIR)\cmpvectr.obj"
	-@erase "$(INTDIR)\cmpvectr.sbr"
	-@erase "$(INTDIR)\des.obj"
	-@erase "$(INTDIR)\des.sbr"
	-@erase "$(INTDIR)\desedec.obj"
	-@erase "$(INTDIR)\desedec.sbr"
	-@erase "$(INTDIR)\deseded.obj"
	-@erase "$(INTDIR)\deseded.sbr"
	-@erase "$(INTDIR)\desedee.obj"
	-@erase "$(INTDIR)\desedee.sbr"
	-@erase "$(INTDIR)\digrand.obj"
	-@erase "$(INTDIR)\digrand.sbr"
	-@erase "$(INTDIR)\integrate.obj"
	-@erase "$(INTDIR)\integrate.sbr"
	-@erase "$(INTDIR)\md2.obj"
	-@erase "$(INTDIR)\md2.sbr"
	-@erase "$(INTDIR)\md5.obj"
	-@erase "$(INTDIR)\md5.sbr"
	-@erase "$(INTDIR)\md5rand.obj"
	-@erase "$(INTDIR)\md5rand.sbr"
	-@erase "$(INTDIR)\prime.obj"
	-@erase "$(INTDIR)\prime.sbr"
	-@erase "$(INTDIR)\rc2.obj"
	-@erase "$(INTDIR)\rc2.sbr"
	-@erase "$(INTDIR)\rc2cbd.obj"
	-@erase "$(INTDIR)\rc2cbd.sbr"
	-@erase "$(INTDIR)\rc2cbe.obj"
	-@erase "$(INTDIR)\rc2cbe.sbr"
	-@erase "$(INTDIR)\rc4.obj"
	-@erase "$(INTDIR)\rc4.sbr"
	-@erase "$(INTDIR)\rsa.obj"
	-@erase "$(INTDIR)\rsa.sbr"
	-@erase "$(INTDIR)\rsakeygn.obj"
	-@erase "$(INTDIR)\rsakeygn.sbr"
	-@erase "$(INTDIR)\seccbcd.obj"
	-@erase "$(INTDIR)\seccbcd.sbr"
	-@erase "$(INTDIR)\seccbce.obj"
	-@erase "$(INTDIR)\seccbce.sbr"
	-@erase "$(INTDIR)\secrcbc.obj"
	-@erase "$(INTDIR)\secrcbc.sbr"
	-@erase "$(INTDIR)\sha.obj"
	-@erase "$(INTDIR)\sha.sbr"
	-@erase "$(INTDIR)\shacomm.obj"
	-@erase "$(INTDIR)\shacomm.sbr"
	-@erase "$(INTDIR)\uint4.obj"
	-@erase "$(INTDIR)\uint4.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\BSafeLite.bsc"
	-@erase "$(OUTDIR)\BSafeLite.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "INTELx86i32" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\BSafeLite.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\BSafeLite.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\cmparith.sbr" \
	"$(INTDIR)\cmpbits.sbr" \
	"$(INTDIR)\cmpcnv.sbr" \
	"$(INTDIR)\cmpmdi32.sbr" \
	"$(INTDIR)\cmpmem.sbr" \
	"$(INTDIR)\cmpmgi32.sbr" \
	"$(INTDIR)\cmpmod.sbr" \
	"$(INTDIR)\cmpmxi32.sbr" \
	"$(INTDIR)\cmpspprt.sbr" \
	"$(INTDIR)\cmpvectr.sbr" \
	"$(INTDIR)\des.sbr" \
	"$(INTDIR)\desedec.sbr" \
	"$(INTDIR)\deseded.sbr" \
	"$(INTDIR)\desedee.sbr" \
	"$(INTDIR)\digrand.sbr" \
	"$(INTDIR)\md2.sbr" \
	"$(INTDIR)\md5.sbr" \
	"$(INTDIR)\md5rand.sbr" \
	"$(INTDIR)\prime.sbr" \
	"$(INTDIR)\rc2.sbr" \
	"$(INTDIR)\rc2cbd.sbr" \
	"$(INTDIR)\rc2cbe.sbr" \
	"$(INTDIR)\rc4.sbr" \
	"$(INTDIR)\rsa.sbr" \
	"$(INTDIR)\rsakeygn.sbr" \
	"$(INTDIR)\seccbcd.sbr" \
	"$(INTDIR)\seccbce.sbr" \
	"$(INTDIR)\secrcbc.sbr" \
	"$(INTDIR)\sha.sbr" \
	"$(INTDIR)\shacomm.sbr" \
	"$(INTDIR)\uint4.sbr" \
	"$(INTDIR)\integrate.sbr"

"$(OUTDIR)\BSafeLite.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\BSafeLite.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cmparith.obj" \
	"$(INTDIR)\cmpbits.obj" \
	"$(INTDIR)\cmpcnv.obj" \
	"$(INTDIR)\cmpmdi32.obj" \
	"$(INTDIR)\cmpmem.obj" \
	"$(INTDIR)\cmpmgi32.obj" \
	"$(INTDIR)\cmpmod.obj" \
	"$(INTDIR)\cmpmxi32.obj" \
	"$(INTDIR)\cmpspprt.obj" \
	"$(INTDIR)\cmpvectr.obj" \
	"$(INTDIR)\des.obj" \
	"$(INTDIR)\desedec.obj" \
	"$(INTDIR)\deseded.obj" \
	"$(INTDIR)\desedee.obj" \
	"$(INTDIR)\digrand.obj" \
	"$(INTDIR)\md2.obj" \
	"$(INTDIR)\md5.obj" \
	"$(INTDIR)\md5rand.obj" \
	"$(INTDIR)\prime.obj" \
	"$(INTDIR)\rc2.obj" \
	"$(INTDIR)\rc2cbd.obj" \
	"$(INTDIR)\rc2cbe.obj" \
	"$(INTDIR)\rc4.obj" \
	"$(INTDIR)\rsa.obj" \
	"$(INTDIR)\rsakeygn.obj" \
	"$(INTDIR)\seccbcd.obj" \
	"$(INTDIR)\seccbce.obj" \
	"$(INTDIR)\secrcbc.obj" \
	"$(INTDIR)\sha.obj" \
	"$(INTDIR)\shacomm.obj" \
	"$(INTDIR)\uint4.obj" \
	"$(INTDIR)\integrate.obj" \
	"$(INTDIR)\cmpati32.obj" \
	"$(INTDIR)\cmpmpi32.obj" \
	"$(INTDIR)\cmpmsi32.obj" \
	"$(INTDIR)\cmpvmi32.obj"

"$(OUTDIR)\BSafeLite.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\ReleaseASM
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\BSafeLite.lib" "$(OUTDIR)\BSafeLite.bsc"
   if not exist "..\lib\static\release" md "..\lib\static\release"
	copy releaseASM\BSafeLite.lib "..\lib\static\release"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("BSafeLite.dep")
!INCLUDE "BSafeLite.dep"
!ELSE 
!MESSAGE Warning: cannot find "BSafeLite.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "BSafeLite - Win32 Release" || "$(CFG)" == "BSafeLite - Win32 Debug" || "$(CFG)" == "BSafeLite - Win32 DebugASM" || "$(CFG)" == "BSafeLite - Win32 ReleaseASM"
SOURCE=.\src\cmparith.c

"$(INTDIR)\cmparith.obj"	"$(INTDIR)\cmparith.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpati32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

IntDir=.\DebugASM
InputPath=.\src\cmpati32.asm

"$(INTDIR)\cmpati32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpati32.obj $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

IntDir=.\ReleaseASM
InputPath=.\src\cmpati32.asm

"$(INTDIR)\cmpati32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpati32.obj $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\src\cmpbits.c

"$(INTDIR)\cmpbits.obj"	"$(INTDIR)\cmpbits.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpcnv.c

"$(INTDIR)\cmpcnv.obj"	"$(INTDIR)\cmpcnv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpmdexp.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"


"$(INTDIR)\cmpmdexp.obj"	"$(INTDIR)\cmpmdexp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"


"$(INTDIR)\cmpmdexp.obj"	"$(INTDIR)\cmpmdexp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

!ENDIF 

SOURCE=.\src\cmpmdi32.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"


"$(INTDIR)\cmpmdi32.obj"	"$(INTDIR)\cmpmdi32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"


"$(INTDIR)\cmpmdi32.obj"	"$(INTDIR)\cmpmdi32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\cmpmem.c

"$(INTDIR)\cmpmem.obj"	"$(INTDIR)\cmpmem.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpmgi32.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"


"$(INTDIR)\cmpmgi32.obj"	"$(INTDIR)\cmpmgi32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"


"$(INTDIR)\cmpmgi32.obj"	"$(INTDIR)\cmpmgi32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\cmpmod.c

"$(INTDIR)\cmpmod.obj"	"$(INTDIR)\cmpmod.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpmontg.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"


"$(INTDIR)\cmpmontg.obj"	"$(INTDIR)\cmpmontg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"


"$(INTDIR)\cmpmontg.obj"	"$(INTDIR)\cmpmontg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

!ENDIF 

SOURCE=.\src\cmpmpi32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

IntDir=.\DebugASM
InputPath=.\src\cmpmpi32.asm

"$(INTDIR)\cmpmpi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmpi32.obj $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

IntDir=.\ReleaseASM
InputPath=.\src\cmpmpi32.asm

"$(INTDIR)\cmpmpi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmpi32.obj $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\src\cmpmsi32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

IntDir=.\DebugASM
InputPath=.\src\cmpmsi32.asm

"$(INTDIR)\cmpmsi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmsi32.obj $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

IntDir=.\ReleaseASM
InputPath=.\src\cmpmsi32.asm

"$(INTDIR)\cmpmsi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpmsi32.obj $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\src\cmpmuldv.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"


"$(INTDIR)\cmpmuldv.obj"	"$(INTDIR)\cmpmuldv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"


"$(INTDIR)\cmpmuldv.obj"	"$(INTDIR)\cmpmuldv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

!ENDIF 

SOURCE=.\src\cmpmxi32.c

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"


"$(INTDIR)\cmpmxi32.obj"	"$(INTDIR)\cmpmxi32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"


"$(INTDIR)\cmpmxi32.obj"	"$(INTDIR)\cmpmxi32.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\src\cmpspprt.c

"$(INTDIR)\cmpspprt.obj"	"$(INTDIR)\cmpspprt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpvectr.c

"$(INTDIR)\cmpvectr.obj"	"$(INTDIR)\cmpvectr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\cmpvmi32.asm

!IF  "$(CFG)" == "BSafeLite - Win32 Release"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 Debug"

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 DebugASM"

IntDir=.\DebugASM
InputPath=.\src\cmpvmi32.asm

"$(INTDIR)\cmpvmi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpvmi32.obj $(InputPath)
<< 
	

!ELSEIF  "$(CFG)" == "BSafeLite - Win32 ReleaseASM"

IntDir=.\ReleaseASM
InputPath=.\src\cmpvmi32.asm

"$(INTDIR)\cmpvmi32.obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	I:\MASM611\BIN\ml /c /Cx /coff /Fo $(IntDir)\cmpvmi32.obj $(InputPath)
<< 
	

!ENDIF 

SOURCE=.\src\des.c

"$(INTDIR)\des.obj"	"$(INTDIR)\des.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\desedec.c

"$(INTDIR)\desedec.obj"	"$(INTDIR)\desedec.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\deseded.c

"$(INTDIR)\deseded.obj"	"$(INTDIR)\deseded.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\desedee.c

"$(INTDIR)\desedee.obj"	"$(INTDIR)\desedee.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\digrand.c

"$(INTDIR)\digrand.obj"	"$(INTDIR)\digrand.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\md2.c

"$(INTDIR)\md2.obj"	"$(INTDIR)\md2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\md5.c

"$(INTDIR)\md5.obj"	"$(INTDIR)\md5.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\md5rand.c

"$(INTDIR)\md5rand.obj"	"$(INTDIR)\md5rand.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\prime.c

"$(INTDIR)\prime.obj"	"$(INTDIR)\prime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rc2.c

"$(INTDIR)\rc2.obj"	"$(INTDIR)\rc2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rc2cbd.c

"$(INTDIR)\rc2cbd.obj"	"$(INTDIR)\rc2cbd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rc2cbe.c

"$(INTDIR)\rc2cbe.obj"	"$(INTDIR)\rc2cbe.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rc4.c

"$(INTDIR)\rc4.obj"	"$(INTDIR)\rc4.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rsa.c

"$(INTDIR)\rsa.obj"	"$(INTDIR)\rsa.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\rsakeygn.c

"$(INTDIR)\rsakeygn.obj"	"$(INTDIR)\rsakeygn.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\seccbcd.c

"$(INTDIR)\seccbcd.obj"	"$(INTDIR)\seccbcd.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\seccbce.c

"$(INTDIR)\seccbce.obj"	"$(INTDIR)\seccbce.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\secrcbc.c

"$(INTDIR)\secrcbc.obj"	"$(INTDIR)\secrcbc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\sha.c

"$(INTDIR)\sha.obj"	"$(INTDIR)\sha.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\shacomm.c

"$(INTDIR)\shacomm.obj"	"$(INTDIR)\shacomm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\uint4.c

"$(INTDIR)\uint4.obj"	"$(INTDIR)\uint4.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\integrate.cpp

"$(INTDIR)\integrate.obj"	"$(INTDIR)\integrate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


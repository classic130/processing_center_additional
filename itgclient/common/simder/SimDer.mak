# Microsoft Developer Studio Generated NMAKE File, Based on SimDer.dsp
!IF "$(CFG)" == ""
CFG=SimDer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SimDer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SimDer - Win32 Release" && "$(CFG)" != "SimDer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimDer.mak" CFG="SimDer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimDer - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "SimDer - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "SimDer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SimDer.lib"


CLEAN :
	-@erase "$(INTDIR)\BaseDER.obj"
	-@erase "$(INTDIR)\BaseDERCollection.obj"
	-@erase "$(INTDIR)\BaseDERHierarchy.obj"
	-@erase "$(INTDIR)\BitString.obj"
	-@erase "$(INTDIR)\BMPString.obj"
	-@erase "$(INTDIR)\Boolean.obj"
	-@erase "$(INTDIR)\DERBlob.obj"
	-@erase "$(INTDIR)\GeneralizedTime.obj"
	-@erase "$(INTDIR)\IA5String.obj"
	-@erase "$(INTDIR)\MemFuncs.obj"
	-@erase "$(INTDIR)\Null.obj"
	-@erase "$(INTDIR)\ObjectIdentifier.obj"
	-@erase "$(INTDIR)\OctetString.obj"
	-@erase "$(INTDIR)\PrintableString.obj"
	-@erase "$(INTDIR)\Sequence.obj"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\TaggedValue.obj"
	-@erase "$(INTDIR)\TeletexString.obj"
	-@erase "$(INTDIR)\UniversalInteger.obj"
	-@erase "$(INTDIR)\UTCTime.obj"
	-@erase "$(INTDIR)\UTF8String.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VisibleString.obj"
	-@erase "$(OUTDIR)\SimDer.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O1 /I ".\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\SimDer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimDer.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\SimDer.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BaseDER.obj" \
	"$(INTDIR)\BaseDERCollection.obj" \
	"$(INTDIR)\BaseDERHierarchy.obj" \
	"$(INTDIR)\BitString.obj" \
	"$(INTDIR)\BMPString.obj" \
	"$(INTDIR)\Boolean.obj" \
	"$(INTDIR)\DERBlob.obj" \
	"$(INTDIR)\GeneralizedTime.obj" \
	"$(INTDIR)\IA5String.obj" \
	"$(INTDIR)\MemFuncs.obj" \
	"$(INTDIR)\Null.obj" \
	"$(INTDIR)\ObjectIdentifier.obj" \
	"$(INTDIR)\OctetString.obj" \
	"$(INTDIR)\PrintableString.obj" \
	"$(INTDIR)\Sequence.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\TaggedValue.obj" \
	"$(INTDIR)\TeletexString.obj" \
	"$(INTDIR)\UniversalInteger.obj" \
	"$(INTDIR)\UTCTime.obj" \
	"$(INTDIR)\UTF8String.obj" \
	"$(INTDIR)\VisibleString.obj"

"$(OUTDIR)\SimDer.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\SimDer.lib"
   if not exist "..\lib\release" md "..\lib\release"
	copy release\simder.lib "..\lib\release\simder.lib"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SimDer.lib" "$(OUTDIR)\SimDer.bsc"


CLEAN :
	-@erase "$(INTDIR)\BaseDER.obj"
	-@erase "$(INTDIR)\BaseDER.sbr"
	-@erase "$(INTDIR)\BaseDERCollection.obj"
	-@erase "$(INTDIR)\BaseDERCollection.sbr"
	-@erase "$(INTDIR)\BaseDERHierarchy.obj"
	-@erase "$(INTDIR)\BaseDERHierarchy.sbr"
	-@erase "$(INTDIR)\BitString.obj"
	-@erase "$(INTDIR)\BitString.sbr"
	-@erase "$(INTDIR)\BMPString.obj"
	-@erase "$(INTDIR)\BMPString.sbr"
	-@erase "$(INTDIR)\Boolean.obj"
	-@erase "$(INTDIR)\Boolean.sbr"
	-@erase "$(INTDIR)\DERBlob.obj"
	-@erase "$(INTDIR)\DERBlob.sbr"
	-@erase "$(INTDIR)\GeneralizedTime.obj"
	-@erase "$(INTDIR)\GeneralizedTime.sbr"
	-@erase "$(INTDIR)\IA5String.obj"
	-@erase "$(INTDIR)\IA5String.sbr"
	-@erase "$(INTDIR)\MemFuncs.obj"
	-@erase "$(INTDIR)\MemFuncs.sbr"
	-@erase "$(INTDIR)\Null.obj"
	-@erase "$(INTDIR)\Null.sbr"
	-@erase "$(INTDIR)\ObjectIdentifier.obj"
	-@erase "$(INTDIR)\ObjectIdentifier.sbr"
	-@erase "$(INTDIR)\OctetString.obj"
	-@erase "$(INTDIR)\OctetString.sbr"
	-@erase "$(INTDIR)\PrintableString.obj"
	-@erase "$(INTDIR)\PrintableString.sbr"
	-@erase "$(INTDIR)\Sequence.obj"
	-@erase "$(INTDIR)\Sequence.sbr"
	-@erase "$(INTDIR)\Set.obj"
	-@erase "$(INTDIR)\Set.sbr"
	-@erase "$(INTDIR)\TaggedValue.obj"
	-@erase "$(INTDIR)\TaggedValue.sbr"
	-@erase "$(INTDIR)\TeletexString.obj"
	-@erase "$(INTDIR)\TeletexString.sbr"
	-@erase "$(INTDIR)\UniversalInteger.obj"
	-@erase "$(INTDIR)\UniversalInteger.sbr"
	-@erase "$(INTDIR)\UTCTime.obj"
	-@erase "$(INTDIR)\UTCTime.sbr"
	-@erase "$(INTDIR)\UTF8String.obj"
	-@erase "$(INTDIR)\UTF8String.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VisibleString.obj"
	-@erase "$(INTDIR)\VisibleString.sbr"
	-@erase "$(OUTDIR)\SimDer.bsc"
	-@erase "$(OUTDIR)\SimDer.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /I ".\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SimDer.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SimDer.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\BaseDER.sbr" \
	"$(INTDIR)\BaseDERCollection.sbr" \
	"$(INTDIR)\BaseDERHierarchy.sbr" \
	"$(INTDIR)\BitString.sbr" \
	"$(INTDIR)\BMPString.sbr" \
	"$(INTDIR)\Boolean.sbr" \
	"$(INTDIR)\DERBlob.sbr" \
	"$(INTDIR)\GeneralizedTime.sbr" \
	"$(INTDIR)\IA5String.sbr" \
	"$(INTDIR)\MemFuncs.sbr" \
	"$(INTDIR)\Null.sbr" \
	"$(INTDIR)\ObjectIdentifier.sbr" \
	"$(INTDIR)\OctetString.sbr" \
	"$(INTDIR)\PrintableString.sbr" \
	"$(INTDIR)\Sequence.sbr" \
	"$(INTDIR)\Set.sbr" \
	"$(INTDIR)\TaggedValue.sbr" \
	"$(INTDIR)\TeletexString.sbr" \
	"$(INTDIR)\UniversalInteger.sbr" \
	"$(INTDIR)\UTCTime.sbr" \
	"$(INTDIR)\UTF8String.sbr" \
	"$(INTDIR)\VisibleString.sbr"

"$(OUTDIR)\SimDer.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\SimDer.lib" 
LIB32_OBJS= \
	"$(INTDIR)\BaseDER.obj" \
	"$(INTDIR)\BaseDERCollection.obj" \
	"$(INTDIR)\BaseDERHierarchy.obj" \
	"$(INTDIR)\BitString.obj" \
	"$(INTDIR)\BMPString.obj" \
	"$(INTDIR)\Boolean.obj" \
	"$(INTDIR)\DERBlob.obj" \
	"$(INTDIR)\GeneralizedTime.obj" \
	"$(INTDIR)\IA5String.obj" \
	"$(INTDIR)\MemFuncs.obj" \
	"$(INTDIR)\Null.obj" \
	"$(INTDIR)\ObjectIdentifier.obj" \
	"$(INTDIR)\OctetString.obj" \
	"$(INTDIR)\PrintableString.obj" \
	"$(INTDIR)\Sequence.obj" \
	"$(INTDIR)\Set.obj" \
	"$(INTDIR)\TaggedValue.obj" \
	"$(INTDIR)\TeletexString.obj" \
	"$(INTDIR)\UniversalInteger.obj" \
	"$(INTDIR)\UTCTime.obj" \
	"$(INTDIR)\UTF8String.obj" \
	"$(INTDIR)\VisibleString.obj"

"$(OUTDIR)\SimDer.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\SimDer.lib" "$(OUTDIR)\SimDer.bsc"
   if not exist "..\lib\debug" md "..\lib\debug"
	copy debug\simder.lib "..\lib\debug\simder.lib"
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SimDer.dep")
!INCLUDE "SimDer.dep"
!ELSE 
!MESSAGE Warning: cannot find "SimDer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SimDer - Win32 Release" || "$(CFG)" == "SimDer - Win32 Debug"
SOURCE=.\sources\BaseDER.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\BaseDER.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\BaseDER.obj"	"$(INTDIR)\BaseDER.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\BaseDERCollection.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\BaseDERCollection.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\BaseDERCollection.obj"	"$(INTDIR)\BaseDERCollection.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\BaseDERHierarchy.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\BaseDERHierarchy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\BaseDERHierarchy.obj"	"$(INTDIR)\BaseDERHierarchy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\BitString.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\BitString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\BitString.obj"	"$(INTDIR)\BitString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\BMPString.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\BMPString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\BMPString.obj"	"$(INTDIR)\BMPString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\Boolean.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\Boolean.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\Boolean.obj"	"$(INTDIR)\Boolean.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\DERBlob.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\DERBlob.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\DERBlob.obj"	"$(INTDIR)\DERBlob.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\GeneralizedTime.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\GeneralizedTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\GeneralizedTime.obj"	"$(INTDIR)\GeneralizedTime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\IA5String.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\IA5String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\IA5String.obj"	"$(INTDIR)\IA5String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\MemFuncs.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\MemFuncs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\MemFuncs.obj"	"$(INTDIR)\MemFuncs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\Null.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\Null.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\Null.obj"	"$(INTDIR)\Null.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\ObjectIdentifier.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\ObjectIdentifier.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\ObjectIdentifier.obj"	"$(INTDIR)\ObjectIdentifier.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\OctetString.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\OctetString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\OctetString.obj"	"$(INTDIR)\OctetString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\PrintableString.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\PrintableString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\PrintableString.obj"	"$(INTDIR)\PrintableString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\Sequence.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\Sequence.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\Sequence.obj"	"$(INTDIR)\Sequence.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\Set.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\Set.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\Set.obj"	"$(INTDIR)\Set.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\TaggedValue.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\TaggedValue.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\TaggedValue.obj"	"$(INTDIR)\TaggedValue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\TeletexString.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\TeletexString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\TeletexString.obj"	"$(INTDIR)\TeletexString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\UniversalInteger.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\UniversalInteger.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\UniversalInteger.obj"	"$(INTDIR)\UniversalInteger.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\UTCTime.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\UTCTime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\UTCTime.obj"	"$(INTDIR)\UTCTime.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\UTF8String.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\UTF8String.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\UTF8String.obj"	"$(INTDIR)\UTF8String.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\sources\VisibleString.cpp

!IF  "$(CFG)" == "SimDer - Win32 Release"


"$(INTDIR)\VisibleString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "SimDer - Win32 Debug"


"$(INTDIR)\VisibleString.obj"	"$(INTDIR)\VisibleString.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 


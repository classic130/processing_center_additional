# Microsoft Developer Studio Generated NMAKE File, Based on mimeengine.dsp
!IF "$(CFG)" == ""
CFG=mimeengine - Win32 Debug
!MESSAGE No configuration specified. Defaulting to mimeengine - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "mimeengine - Win32 Release" && "$(CFG)" != "mimeengine - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mimeengine.mak" CFG="mimeengine - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mimeengine - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mimeengine - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mimeengine - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mimeengine.lib"


CLEAN :
	-@erase "$(INTDIR)\multipartmsg.obj"
	-@erase "$(INTDIR)\simplemsg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vsmimelib.obj"
	-@erase "$(INTDIR)\vsscaddress.obj"
	-@erase "$(INTDIR)\vsscbody.obj"
	-@erase "$(INTDIR)\vsscbodypart.obj"
	-@erase "$(INTDIR)\vsscdisposition.obj"
	-@erase "$(INTDIR)\vsscEntity.obj"
	-@erase "$(INTDIR)\vsscenum.obj"
	-@erase "$(INTDIR)\vsscfield.obj"
	-@erase "$(INTDIR)\vsscfieldbody.obj"
	-@erase "$(INTDIR)\vsscheaders.obj"
	-@erase "$(INTDIR)\vsscmailbox.obj"
	-@erase "$(INTDIR)\vsscMailboxList.obj"
	-@erase "$(INTDIR)\vsscmechanism.obj"
	-@erase "$(INTDIR)\vsscmediatype.obj"
	-@erase "$(INTDIR)\vsscmessage.obj"
	-@erase "$(INTDIR)\vsscmsgcmp.obj"
	-@erase "$(INTDIR)\vsscparameter.obj"
	-@erase "$(INTDIR)\vsscstring.obj"
	-@erase "$(INTDIR)\VSSCText.obj"
	-@erase "$(INTDIR)\vssctoken.obj"
	-@erase "$(OUTDIR)\mimeengine.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I ".\include" /I "..\..\..\..\itgclient\common\simder\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "EOL_CRLF" /Fp"$(INTDIR)\mimeengine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mimeengine.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\mimeengine.lib" 
LIB32_OBJS= \
	"$(INTDIR)\multipartmsg.obj" \
	"$(INTDIR)\simplemsg.obj" \
	"$(INTDIR)\vsmimelib.obj" \
	"$(INTDIR)\vsscaddress.obj" \
	"$(INTDIR)\vsscbody.obj" \
	"$(INTDIR)\vsscbodypart.obj" \
	"$(INTDIR)\vsscdisposition.obj" \
	"$(INTDIR)\vsscEntity.obj" \
	"$(INTDIR)\vsscenum.obj" \
	"$(INTDIR)\vsscfield.obj" \
	"$(INTDIR)\vsscfieldbody.obj" \
	"$(INTDIR)\vsscheaders.obj" \
	"$(INTDIR)\vsscmailbox.obj" \
	"$(INTDIR)\vsscMailboxList.obj" \
	"$(INTDIR)\vsscmechanism.obj" \
	"$(INTDIR)\vsscmediatype.obj" \
	"$(INTDIR)\vsscmessage.obj" \
	"$(INTDIR)\vsscmsgcmp.obj" \
	"$(INTDIR)\vsscparameter.obj" \
	"$(INTDIR)\vsscstring.obj" \
	"$(INTDIR)\VSSCText.obj" \
	"$(INTDIR)\vssctoken.obj"

"$(OUTDIR)\mimeengine.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\mimeengine.lib"
   copy release\mimeengine.lib ..\..\lib\release
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "mimeengine - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mimeengine.lib"


CLEAN :
	-@erase "$(INTDIR)\multipartmsg.obj"
	-@erase "$(INTDIR)\simplemsg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vsmimelib.obj"
	-@erase "$(INTDIR)\vsscaddress.obj"
	-@erase "$(INTDIR)\vsscbody.obj"
	-@erase "$(INTDIR)\vsscbodypart.obj"
	-@erase "$(INTDIR)\vsscdisposition.obj"
	-@erase "$(INTDIR)\vsscEntity.obj"
	-@erase "$(INTDIR)\vsscenum.obj"
	-@erase "$(INTDIR)\vsscfield.obj"
	-@erase "$(INTDIR)\vsscfieldbody.obj"
	-@erase "$(INTDIR)\vsscheaders.obj"
	-@erase "$(INTDIR)\vsscmailbox.obj"
	-@erase "$(INTDIR)\vsscMailboxList.obj"
	-@erase "$(INTDIR)\vsscmechanism.obj"
	-@erase "$(INTDIR)\vsscmediatype.obj"
	-@erase "$(INTDIR)\vsscmessage.obj"
	-@erase "$(INTDIR)\vsscmsgcmp.obj"
	-@erase "$(INTDIR)\vsscparameter.obj"
	-@erase "$(INTDIR)\vsscstring.obj"
	-@erase "$(INTDIR)\VSSCText.obj"
	-@erase "$(INTDIR)\vssctoken.obj"
	-@erase "$(OUTDIR)\mimeengine.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I ".\include" /I "..\..\..\..\itgclient\common\simder\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "EOL_CRLF" /Fp"$(INTDIR)\mimeengine.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mimeengine.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\mimeengine.lib" 
LIB32_OBJS= \
	"$(INTDIR)\multipartmsg.obj" \
	"$(INTDIR)\simplemsg.obj" \
	"$(INTDIR)\vsmimelib.obj" \
	"$(INTDIR)\vsscaddress.obj" \
	"$(INTDIR)\vsscbody.obj" \
	"$(INTDIR)\vsscbodypart.obj" \
	"$(INTDIR)\vsscdisposition.obj" \
	"$(INTDIR)\vsscEntity.obj" \
	"$(INTDIR)\vsscenum.obj" \
	"$(INTDIR)\vsscfield.obj" \
	"$(INTDIR)\vsscfieldbody.obj" \
	"$(INTDIR)\vsscheaders.obj" \
	"$(INTDIR)\vsscmailbox.obj" \
	"$(INTDIR)\vsscMailboxList.obj" \
	"$(INTDIR)\vsscmechanism.obj" \
	"$(INTDIR)\vsscmediatype.obj" \
	"$(INTDIR)\vsscmessage.obj" \
	"$(INTDIR)\vsscmsgcmp.obj" \
	"$(INTDIR)\vsscparameter.obj" \
	"$(INTDIR)\vsscstring.obj" \
	"$(INTDIR)\VSSCText.obj" \
	"$(INTDIR)\vssctoken.obj"

"$(OUTDIR)\mimeengine.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\mimeengine.lib"
   copy debug\mimeengine.lib ..\..\lib\debug
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("mimeengine.dep")
!INCLUDE "mimeengine.dep"
!ELSE 
!MESSAGE Warning: cannot find "mimeengine.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mimeengine - Win32 Release" || "$(CFG)" == "mimeengine - Win32 Debug"
SOURCE=.\sources\multipartmsg.cpp

"$(INTDIR)\multipartmsg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\simplemsg.cpp

"$(INTDIR)\simplemsg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsmimelib.cpp

"$(INTDIR)\vsmimelib.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscaddress.cpp

"$(INTDIR)\vsscaddress.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscbody.cpp

"$(INTDIR)\vsscbody.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscbodypart.cpp

"$(INTDIR)\vsscbodypart.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscdisposition.cpp

"$(INTDIR)\vsscdisposition.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscEntity.cpp

"$(INTDIR)\vsscEntity.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscenum.cpp

"$(INTDIR)\vsscenum.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscfield.cpp

"$(INTDIR)\vsscfield.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscfieldbody.cpp

"$(INTDIR)\vsscfieldbody.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscheaders.cpp

"$(INTDIR)\vsscheaders.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscmailbox.cpp

"$(INTDIR)\vsscmailbox.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscMailboxList.cpp

"$(INTDIR)\vsscMailboxList.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscmechanism.cpp

"$(INTDIR)\vsscmechanism.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscmediatype.cpp

"$(INTDIR)\vsscmediatype.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscmessage.cpp

"$(INTDIR)\vsscmessage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscmsgcmp.cpp

"$(INTDIR)\vsscmsgcmp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscparameter.cpp

"$(INTDIR)\vsscparameter.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vsscstring.cpp

"$(INTDIR)\vsscstring.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\VSSCText.cpp

"$(INTDIR)\VSSCText.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\sources\vssctoken.cpp

"$(INTDIR)\vssctoken.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


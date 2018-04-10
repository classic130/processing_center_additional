# Microsoft Visual C++ generated build script - Do not modify

PROJ = NPBAS16
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = Y:\NS\PLUGINS\SDK\EXAMPLES\BASIC\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = NPSHELL.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /D "WIN16" /D "XP_PC" /D "XP_WIN" /GD /Fd"BASIC16.PDB"
CFLAGS_R_WDLL = /nologo /W3 /ALw /O1 /D "NDEBUG" /D "WIN16" /D "XP_PC" /D "XP_WIN" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = oldnames libw ldllcew 
LIBS_R_WDLL = oldnames libw ldllcew 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = NPBAS16.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = NPSHELL.SBR \
		PLUGIN.SBR \
		NPWIN.SBR


NPSHELL_DEP = y:\ns\plugins\sdk\include\npapi.h \
	y:\ns\plugins\sdk\include\jri.h \
	y:\ns\plugins\sdk\include\jritypes.h \
	y:\ns\plugins\sdk\include\jni.h \
	y:\ns\plugins\sdk\include\jni_md.h \
	y:\ns\plugins\sdk\include\jri_md.h \
	x11/xlib.h \
	x11/xutil.h \
	y:\ns\plugins\sdk\examples\basic\plugin.hpp


PLUGIN_DEP = y:\ns\plugins\sdk\examples\basic\plugin.hpp \
	y:\ns\plugins\sdk\include\npapi.h


NPWIN_DEP = y:\ns\plugins\sdk\include\npapi.h


NPWIN_DEP = y:\ns\plugins\sdk\include\jri.h \
	y:\ns\plugins\sdk\include\jritypes.h \
	y:\ns\plugins\sdk\include\jni.h \
	y:\ns\plugins\sdk\include\jni_md.h \
	y:\ns\plugins\sdk\include\jri_md.h \
	x11/xlib.h \
	x11/xutil.h \
	y:\ns\plugins\sdk\include\npupp.h \
	y:\ns\plugins\sdk\include\npapi.h


all:	$(PROJ).DLL

NPSHELL.OBJ:	NPSHELL.CPP $(NPSHELL_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c NPSHELL.CPP

PLUGIN.OBJ:	PLUGIN.CPP $(PLUGIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c PLUGIN.CPP

BASIC16.RES:	BASIC16.RC $(BASIC16_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r BASIC16.RC

NPWIN.OBJ:	..\..\COMMON\NPWIN.CPP $(NPWIN_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ..\..\COMMON\NPWIN.CPP


$(PROJ).DLL::	BASIC16.RES

$(PROJ).DLL::	NPSHELL.OBJ PLUGIN.OBJ NPWIN.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
NPSHELL.OBJ +
PLUGIN.OBJ +
NPWIN.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
e:\msvc\lib\+
e:\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) BASIC16.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	BASIC16.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) BASIC16.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<

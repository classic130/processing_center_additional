#	GNUmakefile 
#       Developed by Narinder 
#	$Id: GNUmakefile,v 1.1.4.3 2001/11/03 10:04:39 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../lib

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f vsprsauth.mak CFG="authdll - Win32 Release" CLEAN
	-${MAKE} /f vsprsauth.mak CFG="authdll - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vsprsauth.dll
	-rm $(APPSLIBPATH)/dynamic/release/vsprsauth.dll
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug: $(APPSLIBPATH)/dynamic/debug/vsprsauth.dll 
$(APPSLIBPATH)/dynamic/debug/vsprsauth.dll:
	${MAKE} /f vsprsauth.mak CFG="authdll - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/vsprsauth.dll $(APPSLIBPATH)/dynamic/debug/vsprsauth.dll

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(APPSLIBPATH)/dynamic/release/vsprsauth.dll 
$(APPSLIBPATH)/dynamic/release/vsprsauth.dll:
	${MAKE} /f vsprsauth.mak CFG="authdll - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/vsprsauth.dll $(APPSLIBPATH)/dynamic/release/vsprsauth.dll

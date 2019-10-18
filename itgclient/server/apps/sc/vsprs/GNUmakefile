#	GNUmakefile 
#       Developed by Narinder
#	$Id: GNUmakefile,v 1.1.4.3 2001/11/03 10:04:35 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../lib

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f vsprs.mak CFG="vsprs - Win32 Release" CLEAN
	-${MAKE} /f vsprs.mak CFG="vsprs - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/static/debug/vsprs.lib
	-rm $(APPSLIBPATH)/static/release/vsprs.lib
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug: $(APPSLIBPATH)/static/debug/vsprs.lib
$(APPSLIBPATH)/static/debug/vsprs.lib:
	${MAKE} /f vsprs.mak CFG="vsprs - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/static
	mkdir -p $(APPSLIBPATH)/static/debug
	cp Debug/vsprs.lib $(APPSLIBPATH)/static/debug/vsprs.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(APPSLIBPATH)/static/release/vsprs.lib
$(APPSLIBPATH)/static/release/vsprs.lib:
	${MAKE} /f vsprs.mak CFG="vsprs - Win32 Release"
	mkdir -p $(APPSLIBPATH)/static
	mkdir -p $(APPSLIBPATH)/static/release
	cp Release/vsprs.lib $(APPSLIBPATH)/static/release/vsprs.lib

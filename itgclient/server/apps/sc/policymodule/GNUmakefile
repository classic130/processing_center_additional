#	GNUmakefile 
#       Developed by Narinder
#	$Id: GNUmakefile,v 1.1.4.3 2001/11/03 10:04:15 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../lib

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f policymodule.mak CFG="policymodule - Win32 Release" CLEAN
	-${MAKE} /f policymodule.mak CFG="policymodule - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/static/debug/policymodule.lib
	-rm $(APPSLIBPATH)/static/release/policymodule.lib
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug: $(APPSLIBPATH)/static/debug/policymodule.lib
$(APPSLIBPATH)/static/debug/policymodule.lib:
	${MAKE} /f policymodule.mak CFG="policymodule - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/static
	mkdir -p $(APPSLIBPATH)/static/debug
	cp Debug/policymodule.lib $(APPSLIBPATH)/static/debug/policymodule.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(APPSLIBPATH)/static/release/policymodule.lib
$(APPSLIBPATH)/static/release/policymodule.lib:
	${MAKE} /f policymodule.mak CFG="policymodule - Win32 Release"
	mkdir -p $(APPSLIBPATH)/static
	mkdir -p $(APPSLIBPATH)/static/release
	cp Release/policymodule.lib $(APPSLIBPATH)/static/release/policymodule.lib

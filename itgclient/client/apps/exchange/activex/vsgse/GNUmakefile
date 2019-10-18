#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.3.560.1 2003/06/06 22:14:10 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: debug release

uninstall-local:clean
cd-uninstall:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f VGSE.mak CFG="VGSE - Win32 Release MinDependency" CLEAN
	-${MAKE} /f VGSE.mak CFG="VGSE - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vsgse.dll
	-rm $(APPSLIBPATH)/dynamic/release/vsgse.dll
	-rm $(APPSLIBPATH)/dynamic/debug/vsgse.inf
	-rm $(APPSLIBPATH)/dynamic/release/vsgse.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMinDependency
	-rmdir ReleaseMinDependency


debug-install: debug
debug: 
	${MAKE} /f VGSE.mak CFG="VGSE - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/VSGSE.dll $(APPSLIBPATH)/dynamic/debug/vsgse.dll
	cp vsgse.inf $(APPSLIBPATH)/dynamic/debug/vsgse.inf


release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f VGSE.mak CFG="VGSE - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/VSGSE.dll $(APPSLIBPATH)/dynamic/release/vsgse.dll
	cp vsgse.inf $(APPSLIBPATH)/dynamic/release/vsgse.inf


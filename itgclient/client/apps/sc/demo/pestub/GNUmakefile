#	GNUmakefile 
#       Developed by Abhay Ranade
#       Modified  by Narinder
#	$Id: GNUmakefile,v 1.1.2.2 2001/09/12 00:25:00 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: debug release

uninstall-local:clean
cd-uninstall:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f pestub.mak CFG="pestub - Win32 Release MinDependency" CLEAN
	-${MAKE} /f pestub.mak CFG="pestub - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/pestub.dll
	-rm $(APPSLIBPATH)/dynamic/release/pestub.dll
	
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release


debug-install: debug
debug: 
	${MAKE} /f pestub.mak CFG="pestub - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/pestub.dll $(APPSLIBPATH)/dynamic/debug/pestub.dll
	


release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f pestub.mak CFG="pestub - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/pestub.dll $(APPSLIBPATH)/dynamic/release/pestub.dll
	


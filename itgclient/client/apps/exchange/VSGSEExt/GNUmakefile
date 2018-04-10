#	GNUmakefile 
#       Developed by Narinder Paul
#	$Id: GNUmakefile,v 1.1.2.2 2000/04/18 02:04:08 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../lib

all: release debug

uninstall-local:clean
cd-uninstall:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f VSGSEExt.mak CFG="VSGSEEXT - Win32 Release" CLEAN
	-${MAKE} /f VSGSEExt.mak CFG="VSGSEEXT - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/Debug/VSGSEExt.dll
	-rm $(APPSLIBPATH)/dynamic/Release/VSGSEExt.dll
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release


debug-install: debug
debug: 
	$(MAKE) /f VSGSEExt.mak CFG="VSGSEExt - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/Dynamic/Debug
	cp Debug/VSGSEExt.dll $(APPSLIBPATH)/dynamic/debug/VSGSEExt.dll

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	$(MAKE) /f VSGSEExt.mak CFG="VSGSEExt - Win32 Release"
	mkdir -p $(APPSLIBPATH)/Dynamic/Release
	cp Release/VSGSEExt.dll $(APPSLIBPATH)/dynamic/Release/VSGSEExt.dll


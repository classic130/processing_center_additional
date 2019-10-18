#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.2.1 2003/10/22 17:44:15 sgoginen Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f VS_INFYTSS.mak CFG="VS_INFYTSS - Win32 Release" CLEAN
	${MAKE} /f VS_INFYTSS.mak CFG="VS_INFYTSS - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/VS_INFYTSS.dll
	-rm $(APPSLIBPATH)/dynamic/release/VS_INFYTSS.dll
	-rm -rf Debug
#	-rmdir Debug
	-rm -rf Release
#	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f VS_INFYTSS.mak CFG="VS_INFYTSS - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/VS_INFYTSS.dll $(APPSLIBPATH)/dynamic/debug/VS_INFYTSS.dll

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f VS_INFYTSS.mak CFG="VS_INFYTSS - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/VS_INFYTSS.dll $(APPSLIBPATH)/dynamic/release/VS_INFYTSS.dll

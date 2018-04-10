#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.1 2003/05/12 22:00:18 sgoginen Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f VS_IBMTSS.mak CFG="VS_IBMTSS - Win32 Release" CLEAN
	${MAKE} /f VS_IBMTSS.mak CFG="VS_IBMTSS - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/VS_IBMTSS.dll
	-rm $(APPSLIBPATH)/dynamic/release/VS_IBMTSS.dll
	-rm -rf Debug
#	-rmdir Debug
	-rm -rf Release
#	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f VS_IBMTSS.mak CFG="VS_IBMTSS - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/VS_IBMTSS.dll $(APPSLIBPATH)/dynamic/debug/VS_IBMTSS.dll

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f VS_IBMTSS.mak CFG="VS_IBMTSS - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/VS_IBMTSS.dll $(APPSLIBPATH)/dynamic/release/VS_IBMTSS.dll

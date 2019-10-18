#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.2.3 2000/05/02 03:38:38 sbajaj Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f NPPTAv3.mak CFG="NPPTAv3 - Win32 Release" CLEAN
	${MAKE} /f NPPTAv3.mak CFG="NPPTAv3 - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/NPPTAv3.dll
	-rm $(APPSLIBPATH)/dynamic/release/NPPTAv3.dll
	-rm $(APPSLIBPATH)/dynamic/debug/VSPTAv3.class
	-rm $(APPSLIBPATH)/dynamic/release/VSPTAv3.class
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f NPPTAv3.mak CFG="NPPTAv3 - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/NPPTAv3.dll $(APPSLIBPATH)/dynamic/debug/NPPTAv3.dll
	cp src/VSPTAv3.class $(APPSLIBPATH)/dynamic/debug/VSPTAv3.class

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f NPPTAv3.mak CFG="NPPTAv3 - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/NPPTAv3.dll $(APPSLIBPATH)/dynamic/release/NPPTAv3.dll
	cp src/VSPTAv3.class $(APPSLIBPATH)/dynamic/release/VSPTAv3.class

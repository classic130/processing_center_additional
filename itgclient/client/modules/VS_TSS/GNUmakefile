#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.1 2003/05/12 22:00:19 sgoginen Exp $
#

MAKE = nmake
unexport MAKEFLAGS

MODULESLIBPATH=../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f VS_TSS.mak CFG="VS_TSS - Win32 Release" CLEAN
	${MAKE} /f VS_TSS.mak CFG="VS_TSS - Win32 Debug" CLEAN
	-rm $(MODULESLIBPATH)/static/debug/VS_TSS.lib
	-rm $(MODULESLIBPATH)/static/release/VS_TSS.lib
	-rm -rf Debug
#	-rmdir Debug
	-rm -rf Release
#	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f VS_TSS.mak CFG="VS_TSS - Win32 Debug"
	mkdir -p $(MODULESLIBPATH)/static/debug
	cp Debug/VS_TSS.lib $(MODULESLIBPATH)/static/debug/VS_TSS.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f VS_TSS.mak CFG="VS_TSS - Win32 Release"
	mkdir -p $(MODULESLIBPATH)/static/release
	cp Release/VS_TSS.lib $(MODULESLIBPATH)/static/release/VS_TSS.lib

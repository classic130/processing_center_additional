#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.6.1 2000/05/12 23:11:19 mwilson Exp $
#

MAKE = nmake
unexport MAKEFLAGS

MODULESLIBPATH=../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f ProtectedStorage.mak CFG="ProtectedStorage - Win32 Release" CLEAN
	${MAKE} /f ProtectedStorage.mak CFG="ProtectedStorage - Win32 Debug" CLEAN
	-rm $(MODULESLIBPATH)/static/debug/ProtectedStorage.lib
	-rm $(MODULESLIBPATH)/static/release/ProtectedStorage.lib
	-rm -rf Debug
#	-rmdir Debug
	-rm -rf Release
#	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f ProtectedStorage.mak CFG="ProtectedStorage - Win32 Debug"
	mkdir -p $(MODULESLIBPATH)/static/debug
	cp Debug/ProtectedStorage.lib $(MODULESLIBPATH)/static/debug/ProtectedStorage.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f ProtectedStorage.mak CFG="ProtectedStorage - Win32 Release"
	mkdir -p $(MODULESLIBPATH)/static/release
	cp Release/ProtectedStorage.lib $(MODULESLIBPATH)/static/release/ProtectedStorage.lib

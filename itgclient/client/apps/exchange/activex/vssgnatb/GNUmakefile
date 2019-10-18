#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2000/04/30 00:47:14 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: debug release

uninstall-local:clean
cd-uninstall:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f SignAtrb.mak CFG="SignAtrb - Win32 Release MinDependency" CLEAN
	-${MAKE} /f SignAtrb.mak CFG="SignAtrb - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vssgnatb.dll
	-rm $(APPSLIBPATH)/dynamic/release/vssgnatb.dll
	-rm $(APPSLIBPATH)/dynamic/debug/vssgnatb.inf
	-rm $(APPSLIBPATH)/dynamic/release/vssgnatb.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMinDependency
	-rmdir ReleaseMinDependency


debug-install: debug
debug: 
	${MAKE} /f SignAtrb.mak CFG="SignAtrb - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/SignAtrb.dll $(APPSLIBPATH)/dynamic/debug/vssgnatb.dll
	cp vssgnatb.inf $(APPSLIBPATH)/dynamic/debug/vssgnatb.inf


release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f SignAtrb.mak CFG="SignAtrb - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/SignAtrb.dll $(APPSLIBPATH)/dynamic/release/vssgnatb.dll
	cp vssgnatb.inf $(APPSLIBPATH)/dynamic/release/vssgnatb.inf


#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.1 2000/05/18 23:30:25 mwilson Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: debug release

uninstall-local:clean
cd-uninstall:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f ImportPKCS12.mak CFG="ImportPKCS12 - Win32 Release MinDependency" CLEAN
	-${MAKE} /f ImportPKCS12.mak CFG="ImportPKCS12 - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/VSImport.dll
	-rm $(APPSLIBPATH)/dynamic/release/VSImport.dll
	-rm $(APPSLIBPATH)/dynamic/debug/VSImport.inf
	-rm $(APPSLIBPATH)/dynamic/release/VSImport.inf
	-rm -rf Debug
	-rm -rf ReleaseMinDependency


debug-install: debug
debug: 
	${MAKE} /f ImportPKCS12.mak CFG="ImportPKCS12 - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/VSImport.dll $(APPSLIBPATH)/dynamic/debug/VSImport.dll
	cp VSImport.inf $(APPSLIBPATH)/dynamic/debug/VSImport.inf


release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f ImportPKCS12.mak CFG="ImportPKCS12 - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/VSImport.dll $(APPSLIBPATH)/dynamic/release/VSImport.dll
	cp VSImport.inf $(APPSLIBPATH)/dynamic/release/VSImport.inf


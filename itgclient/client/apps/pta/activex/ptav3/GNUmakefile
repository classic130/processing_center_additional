#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.6.1 2000/05/12 23:09:43 mwilson Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f Ptav3.mak CFG="Ptav3 - Win32 Release MinDependency" CLEAN
	${MAKE} /f Ptav3.mak CFG="Ptav3 - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/Ptav3.dll
	-rm $(APPSLIBPATH)/dynamic/release/Ptav3.dll
	-rm $(APPSLIBPATH)/dynamic/debug/Ptav3.inf
	-rm $(APPSLIBPATH)/dynamic/release/Ptav3.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMinDependency
	-rmdir ReleaseMinDependency

debug-install: debug
debug:
	${MAKE} /f Ptav3.mak CFG="Ptav3 - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/Ptav3.dll $(APPSLIBPATH)/dynamic/debug/Ptav3.dll
	cp Source/Ptav3.inf $(APPSLIBPATH)/dynamic/debug/Ptav3.inf

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f Ptav3.mak CFG="Ptav3 - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/Ptav3.dll $(APPSLIBPATH)/dynamic/release/Ptav3.dll
	cp Source/Ptav3.inf $(APPSLIBPATH)/dynamic/release/Ptav3.inf
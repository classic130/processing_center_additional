#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.1 2001/12/11 22:35:39 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../../bin

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f npsesetup.mak CFG="npsesetup - Win32 Release" CLEAN
	${MAKE} /f npsesetup.mak CFG="npsesetup - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/npsesetup.exe
	-rm $(APPSBINPATH)/release/npsesetup.exe
	-rm -rf Debug
	-rm -rf Release

debug-install: debug
debug:
	${MAKE} /f npsesetup.mak CFG="npsesetup - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/npsesetup.exe $(APPSBINPATH)/debug/npsesetup.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f npsesetup.mak CFG="npsesetup - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/npsesetup.exe $(APPSBINPATH)/release/npsesetup.exe

	
#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.1 2001/02/23 00:08:07 ajayaram Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f gsesetupw.mak CFG="gsesetupw - Win32 Release" CLEAN
	-${MAKE} /f gsesetupw.mak CFG="gsesetupw - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/gsesetupw.exe
	-rm $(APPSBINPATH)/release/gsesetupw.exe
	-rm -rf Debug
	-rm -rf Release

debug-install: debug
debug:
	${MAKE} /f gsesetupw.mak CFG="gsesetupw - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/gsesetupw.exe $(APPSBINPATH)/debug/gsesetupw.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f gsesetupw.mak CFG="gsesetupw - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/gsesetupw.exe $(APPSBINPATH)/release/gsesetupw.exe


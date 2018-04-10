#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.2.1 2001/12/24 18:43:29 ajayaram Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../../bin

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f vsscsetup.mak CFG="vsscsetup - Win32 Release" CLEAN
	${MAKE} /f vsscsetup.mak CFG="vsscsetup - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/vsscsetup.exe
	-rm $(APPSBINPATH)/release/vsscsetup.exe
	-rm -rf Debug
	-rm -rf Release

debug-install: debug
debug:
	${MAKE} /f vsscsetup.mak CFG="vsscsetup - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/vsscsetup.exe $(APPSBINPATH)/debug/vsscsetup.exe
	
release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vsscsetup.mak CFG="vsscsetup - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/vsscsetup.exe $(APPSBINPATH)/release/vsscsetup.exe
		
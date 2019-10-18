#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.1 2000/05/18 23:31:02 mwilson Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f oesetupw.mak CFG="oesetupw - Win32 Release" CLEAN
	-${MAKE} /f oesetupw.mak CFG="oesetupw - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/oesetupw.exe
	-rm $(APPSBINPATH)/release/oesetupw.exe
	-rm -rf Debug
	-rm -rf Release

debug-install: debug
debug:
	${MAKE} /f oesetupw.mak CFG="oesetupw - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/oesetupw.exe $(APPSBINPATH)/debug/oesetupw.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f oesetupw.mak CFG="oesetupw - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/oesetupw.exe $(APPSBINPATH)/release/oesetupw.exe


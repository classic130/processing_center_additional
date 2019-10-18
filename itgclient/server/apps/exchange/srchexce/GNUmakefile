#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.2 2000/03/15 22:50:22 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f srchexce.mak CFG="SrchExcE - Win32 Release" CLEAN
	-${MAKE} /f srchexce.mak CFG="SrchExcE - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/srchexce.exe
	-rm $(APPSBINPATH)/release/srchexce.exe
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f srchexce.mak CFG="SrchExcE - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/srchexce.exe $(APPSBINPATH)/debug/srchexce.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f srchexce.mak CFG="SrchExcE - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/srchexce.exe $(APPSBINPATH)/release/srchexce.exe


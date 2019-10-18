#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.2.2 2000/03/15 22:46:14 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: release debug

uninstall-local:clean
uninstall-ecas:clean
cd-uninstall:clean
clean :
	${MAKE} /f vslog.mak "CFG=vslog - Win32 Release" CLEAN
	${MAKE} /f vslog.mak "CFG=vslog - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/vslog.exe
	-rm $(APPSBINPATH)/release/vslog.exe
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f vslog.mak "CFG=vslog - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/vslog.exe $(APPSBINPATH)/debug/vslog.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vslog.mak "CFG=vslog - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/vslog.exe $(APPSBINPATH)/release/vslog.exe


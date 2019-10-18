#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.2.2 2000/03/15 22:42:25 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f changepassword.mak "CFG=changepassword - Win32 Release" CLEAN
	${MAKE} /f changepassword.mak "CFG=changepassword - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/chpasswd.exe
	-rm $(APPSBINPATH)/release/chpasswd.exe
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f changepassword.mak "CFG=changepassword - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/chpasswd.exe $(APPSBINPATH)/debug/chpasswd.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f changepassword.mak "CFG=changepassword - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/chpasswd.exe $(APPSBINPATH)/release/chpasswd.exe


#	GNUmakefile 
#       Developed by Wasim Ilkal


MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: debug release

uninstall-local:clean
uninstall-ecas:clean
cd-uninstall:clean

clean :
	${MAKE} /f setup.mak "CFG=setup - Win32 Release" CLEAN
	${MAKE} /f setup.mak "CFG=setup - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/setup.exe
	-rm $(APPSBINPATH)/release/setup.exe
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f setup.mak "CFG=setup - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/setup.exe $(APPSBINPATH)/debug/setup.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f setup.mak "CFG=setup - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/setup.exe $(APPSBINPATH)/release/setup.exe


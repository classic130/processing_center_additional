#	GNUmakefile 
#       Developed by Narinder
#	$Id: GNUmakefile,v 1.1.4.3 2001/11/03 10:04:42 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../bin

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f sgmsprs.mak CFG="sgmsprs - Win32 Release" CLEAN
	-${MAKE} /f sgmsprs.mak CFG="sgmsprs - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/vsprs.exe
	-rm $(APPSBINPATH)/release/vsprs.exe
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug: $(APPSBINPATH)/debug/vsprs.exe
$(APPSBINPATH)/debug/vsprs.exe:
	${MAKE} /f sgmsprs.mak CFG="sgmsprs - Win32 Debug"
	mkdir -p $(APPSBINPATH)
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/sgmsprs.exe $(APPSBINPATH)/debug/vsprs.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(APPSBINPATH)/release/vsprs.exe
$(APPSBINPATH)/release/vsprs.exe:
	${MAKE} /f sgmsprs.mak CFG="sgmsprs - Win32 Release"
	mkdir -p $(APPSBINPATH)
	mkdir -p $(APPSBINPATH)/release
	cp Release/sgmsprs.exe $(APPSBINPATH)/release/vsprs.exe

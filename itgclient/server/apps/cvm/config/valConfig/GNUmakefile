#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.1 2000/11/21 00:01:17 sbajaj Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../../bin
DESTDIR=$(CDINSTALL)/../server/cvm/iis/config

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	${MAKE} /f valconfig.mak CFG="valConfig - Win32 Release" CLEAN
	${MAKE} /f valconfig.mak CFG="valConfig - Win32 Debug" CLEAN
	rm $(APPSBINPATH)/debug/valConfig.exe
	rm $(APPSBINPATH)/release/valConfig.exe
	rm $(DESTDIR)/valConfig.exe
	rm -rf Debug
	rm -rf Release

debug-install: debug
debug:
	${MAKE} /f valconfig.mak CFG="valConfig - Win32 Debug" 
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/valConfig.exe $(APPSBINPATH)/debug/valConfig.exe

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f valconfig.mak CFG="valConfig - Win32 Release" 
	mkdir -p $(APPSBINPATH)/release
	cp Release/valConfig.exe $(APPSBINPATH)/release/valConfig.exe
	mkdir -p $(DESTDIR)
	cp Release/valconfig.exe $(DESTDIR)/valConfig.exe


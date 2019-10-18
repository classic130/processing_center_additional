#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.2.2 2001/11/03 09:56:49 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../../bin

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f vsscnpsetup.mak CFG="vsscnpsetup - Win32 Release" CLEAN
	${MAKE} /f vsscnpsetup.mak CFG="vsscnpsetup - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/vsscnpsetup.exe
	-rm $(APPSBINPATH)/release/vsscnpsetup.exe
	-rm $(APPSBINPATH)/debug/vsnpsmpta.js
	-rm $(APPSBINPATH)/release/vsnpsmpta.js
	-rm -rf Debug
	-rm -rf Release

debug-install: debug
debug:
	${MAKE} /f vsscnpsetup.mak CFG="vsscnpsetup - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/vsscnpsetup.exe $(APPSBINPATH)/debug/vsscnpsetup.exe
	cp vsnpsmpta.js $(APPSBINPATH)/debug/vsnpsmpta.js

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vsscnpsetup.mak CFG="vsscnpsetup - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/vsscnpsetup.exe $(APPSBINPATH)/release/vsscnpsetup.exe
	cp ./vsnpsmpta.js $(APPSBINPATH)/release/vsnpsmpta.js
	
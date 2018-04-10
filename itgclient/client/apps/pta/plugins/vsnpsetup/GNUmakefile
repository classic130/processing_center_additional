#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.346.1 2001/02/12 18:06:32 aabhyank Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../../bin

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f vsnpsetupkm.mak CFG="vsnpsetupkm - Win32 Release" CLEAN
	${MAKE} /f vsnpsetup.mak CFG="vsnpsetup - Win32 Release" CLEAN
	${MAKE} /f vsnpsetupkm.mak CFG="vsnpsetupkm - Win32 Debug" CLEAN
	${MAKE} /f vsnpsetup.mak CFG="vsnpsetup - Win32 Debug" CLEAN
	-rm $(APPSBINPATH)/debug/vsnpsetup.exe
	-rm $(APPSBINPATH)/release/vsnpsetup.exe
	-rm $(APPSBINPATH)/debug/vsnpsetupkm.exe
	-rm $(APPSBINPATH)/release/vsnpsetupkm.exe
	-rm $(APPSBINPATH)/debug/vspta3.js
	-rm $(APPSBINPATH)/release/vspta3.js
	-rm $(APPSBINPATH)/debug/vspta3km.js
	-rm $(APPSBINPATH)/release/vspta3km.js
	-rm $(APPSBINPATH)/debug/install.js
	-rm $(APPSBINPATH)/release/install.js
	-rm $(APPSBINPATH)/debug/install_km.js
	-rm $(APPSBINPATH)/release/install_km.js
	-rm -rf Debug
	-rm -rf DebugKM
#	-rmdir Debug
	-rm -rf Release
	-rm -rf ReleaseKM
#	-rmdir Release

debug-install: debug
debug:
	${MAKE} /f vsnpsetup.mak CFG="vsnpsetup - Win32 Debug"
	${MAKE} /f vsnpsetupkm.mak CFG="vsnpsetupkm - Win32 Debug"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/vsnpsetup.exe $(APPSBINPATH)/debug/vsnpsetup.exe
	cp DebugKM/vsnpsetupkm.exe $(APPSBINPATH)/debug/vsnpsetupkm.exe
	cp vspta3.js $(APPSBINPATH)/debug/vspta3.js
	cp vspta3km.js $(APPSBINPATH)/debug/vspta3km.js
	cp install.js $(APPSBINPATH)/debug/install.js
	cp install_km.js $(APPSBINPATH)/debug/install_km.js

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vsnpsetup.mak CFG="vsnpsetup - Win32 Release"
	${MAKE} /f vsnpsetupkm.mak CFG="vsnpsetupkm - Win32 Release"
	mkdir -p $(APPSBINPATH)/release
	cp Release/vsnpsetup.exe $(APPSBINPATH)/release/vsnpsetup.exe
	cp ReleaseKM/vsnpsetupkm.exe $(APPSBINPATH)/release/vsnpsetupkm.exe
	cp ./vspta3.js $(APPSBINPATH)/release/vspta3.js
	cp ./vspta3km.js $(APPSBINPATH)/release/vspta3km.js
	cp install.js $(APPSBINPATH)/release/install.js
	cp install_km.js $(APPSBINPATH)/release/install_km.js

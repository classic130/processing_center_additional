#	GNUmakefile 
#       Developed by Wasim Ilkal
#

MAKE = nmake
unexport MAKEFLAGS

APPSBINPATH=../../../../bin

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Release" CLEAN
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Debug" CLEAN
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Release Pta" CLEAN
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Debug Pta" CLEAN
	-rm $(APPSBINPATH)/debug/vsnzpsetup.exe
	-rm $(APPSBINPATH)/release/vsnzpsetup.exe
	-rm $(APPSBINPATH)/debug/vsnzptasetup.exe
	-rm $(APPSBINPATH)/release/vsnzptasetup.exe
	-rm $(APPSBINPATH)/debug/vsdnotz.js
	-rm $(APPSBINPATH)/release/vsdnotz.js
	-rm $(APPSBINPATH)/debug/vsnzpta.js
	-rm $(APPSBINPATH)/release/vsnzpta.js
	-rm $(APPSBINPATH)/debug/install_nz.js
	-rm $(APPSBINPATH)/release/install_nz.js
	-rm $(APPSBINPATH)/debug/install_nzpta.js
	-rm $(APPSBINPATH)/release/install_nzpta.js
	-rm -rf Debug
	-rm -rf vsnzpsetup___Win32_Debug_Pta
	-rm -rf Release
	-rm -rf vsnzpsetup___Win32_Release_Pta

debug-install: debug
debug:
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Debug"
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Debug Pta"
	mkdir -p $(APPSBINPATH)/debug
	cp Debug/vsnzpsetup.exe $(APPSBINPATH)/debug/vsnzpsetup.exe
	cp vsnzpsetup___Win32_Debug_Pta/vsnzptasetup.exe $(APPSBINPATH)/debug/vsnzptasetup.exe
	cp vsdnotz.js $(APPSBINPATH)/debug/vsdnotz.js
	cp vsnzpta.js $(APPSBINPATH)/debug/vsnzpta.js
	cp install_nz.js $(APPSBINPATH)/debug/install_nz.js
	cp install_nzpta.js $(APPSBINPATH)/debug/install_nzpta.js

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Release"
	${MAKE} /f vsnzpsetup.mak CFG="vsnzpsetup - Win32 Release Pta"
	mkdir -p $(APPSBINPATH)/release
	cp Release/vsnzpsetup.exe $(APPSBINPATH)/release/vsnzpsetup.exe
	cp vsnzpsetup___Win32_Release_Pta/vsnzptasetup.exe $(APPSBINPATH)/release/vsnzptasetup.exe
	cp ./vsdnotz.js $(APPSBINPATH)/release/vsdnotz.js
	cp ./vsnzpta.js $(APPSBINPATH)/release/vsnzpta.js
	cp install_nz.js $(APPSBINPATH)/release/install_nz.js
	cp install_nzpta.js $(APPSBINPATH)/release/install_nzpta.js

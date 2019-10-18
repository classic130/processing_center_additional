#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.1 2001/02/12 18:05:58 aabhyank Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f N6PTA.mak CFG="N6PTA - Win32 Release" CLEAN
	${MAKE} /f N6PTA.mak CFG="N6PTA - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/N6PTA.dll
	-rm $(APPSLIBPATH)/dynamic/release/N6PTA.dll
	-rm $(APPSLIBPATH)/dynamic/debug/N6PTA.xpt
	-rm $(APPSLIBPATH)/dynamic/release/N6PTA.xpt
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	cp source/N6PTA.idl .
	xpidl -v -I i:/N6PluginSDK/idl -o include/N6PTA -m header N6PTA.idl
	xpidl -v -I i:/N6PluginSDK/idl -o _xpidlgen/N6PTA -m typelib N6PTA.idl
	rm N6PTA.idl
	${MAKE} /f N6PTA.mak CFG="N6PTA - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/N6PTA.dll $(APPSLIBPATH)/dynamic/debug/N6PTA.dll
	cp _xpidlgen/N6PTA.xpt $(APPSLIBPATH)/dynamic/debug/N6PTA.xpt

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	cp source/N6PTA.idl .
	xpidl -v -I i:/N6PluginSDK/idl -o include/N6PTA -m header N6PTA.idl
	xpidl -v -I i:/N6PluginSDK/idl -o _xpidlgen/N6PTA -m typelib N6PTA.idl
	rm N6PTA.idl
	${MAKE} /f N6PTA.mak CFG="N6PTA - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/N6PTA.dll $(APPSLIBPATH)/dynamic/release/N6PTA.dll
	cp _xpidlgen/N6PTA.xpt $(APPSLIBPATH)/dynamic/release/N6PTA.xpt

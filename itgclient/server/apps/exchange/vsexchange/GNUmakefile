#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.3.10.1 2000/04/20 03:02:03 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../lib

all: release debug

uninstall-local: clean
uninstall-ecas: clean
cd-uninstall: clean
clean :
	-${MAKE} /f vsexchange.mak CFG="vsexchange - Win32 Release" CLEAN
	-${MAKE} /f vsexchange.mak CFG="vsexchange - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vsexchange.dll
	-rm $(APPSLIBPATH)/dynamic/release/vsexchange.dll
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug: $(APPSLIBPATH)/dynamic/debug/vsexchange.dll 
$(APPSLIBPATH)/dynamic/debug/vsexchange.dll:
	${MAKE} /f vsexchange.mak CFG="vsexchange - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/vsexchange.dll $(APPSLIBPATH)/dynamic/debug/vsexchange.dll

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(APPSLIBPATH)/dynamic/release/vsexchange.dll 
$(APPSLIBPATH)/dynamic/release/vsexchange.dll:
	${MAKE} /f vsexchange.mak CFG="vsexchange - Win32 Release"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/vsexchange.dll $(APPSLIBPATH)/dynamic/release/vsexchange.dll

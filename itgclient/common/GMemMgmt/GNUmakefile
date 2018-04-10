#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.1 2001/09/08 00:31:18 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f GMemMgmt.mak "CFG=GMemMgmt - Win32 Release" CLEAN
	-${MAKE} /f GMemMgmt.mak "CFG=GMemMgmt - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/GMemMgmt.lib
	-rm $(COMMONLIBPATH)/Release/GMemMgmt.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/GMemMgmt.lib
$(COMMONLIBPATH)/Debug/GMemMgmt.lib:
	${MAKE} /f GMemMgmt.mak "CFG=GMemMgmt - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/GMemMgmt.lib $(COMMONLIBPATH)/Debug/GMemMgmt.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/GMemMgmt.lib
$(COMMONLIBPATH)/Release/GMemMgmt.lib:
	${MAKE} /f GMemMgmt.mak "CFG=GMemMgmt - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/GMemMgmt.lib $(COMMONLIBPATH)/Release/GMemMgmt.lib


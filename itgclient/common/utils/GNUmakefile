#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2001/09/08 00:32:25 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f utils.mak "CFG=utils - Win32 Release" CLEAN
	-${MAKE} /f utils.mak "CFG=utils - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/utils.lib
	-rm $(COMMONLIBPATH)/Release/utils.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/utils.lib
$(COMMONLIBPATH)/Debug/utils.lib:
	${MAKE} /f utils.mak "CFG=utils - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/utils.lib $(COMMONLIBPATH)/Debug/utils.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/utils.lib
$(COMMONLIBPATH)/Release/utils.lib:
	${MAKE} /f utils.mak "CFG=utils - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/utils.lib $(COMMONLIBPATH)/Release/utils.lib


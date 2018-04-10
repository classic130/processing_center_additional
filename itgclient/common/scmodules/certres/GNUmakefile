#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2001/09/08 00:31:40 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f ResolutionLib.mak "CFG=ResolutionLib - Win32 Release" CLEAN
	-${MAKE} /f ResolutionLib.mak "CFG=ResolutionLib - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/ResolutionLib.lib
	-rm $(COMMONLIBPATH)/Release/ResolutionLib.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/ResolutionLib.lib
$(COMMONLIBPATH)/Debug/ResolutionLib.lib:
	${MAKE} /f ResolutionLib.mak "CFG=ResolutionLib - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/ResolutionLib.lib $(COMMONLIBPATH)/Debug/ResolutionLib.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/ResolutionLib.lib
$(COMMONLIBPATH)/Release/ResolutionLib.lib:
	${MAKE} /f ResolutionLib.mak "CFG=ResolutionLib - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/ResolutionLib.lib $(COMMONLIBPATH)/Release/ResolutionLib.lib


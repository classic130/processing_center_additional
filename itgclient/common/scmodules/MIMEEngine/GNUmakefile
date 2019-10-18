#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2001/09/08 00:31:25 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f mimeengine.mak "CFG=mimeengine - Win32 Release" CLEAN
	-${MAKE} /f mimeengine.mak "CFG=mimeengine - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/mimeengine.lib
	-rm $(COMMONLIBPATH)/Release/mimeengine.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/mimeengine.lib
$(COMMONLIBPATH)/Debug/mimeengine.lib:
	${MAKE} /f mimeengine.mak "CFG=mimeengine - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/mimeengine.lib $(COMMONLIBPATH)/Debug/mimeengine.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/mimeengine.lib
$(COMMONLIBPATH)/Release/mimeengine.lib:
	${MAKE} /f mimeengine.mak "CFG=mimeengine - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/mimeengine.lib $(COMMONLIBPATH)/Release/mimeengine.lib


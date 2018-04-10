#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.3 2000/04/19 23:00:05 aranade Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f SimDer.mak "CFG=SimDer - Win32 Release" CLEAN
	-${MAKE} /f SimDer.mak "CFG=SimDer - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/simder.lib
	-rm $(COMMONLIBPATH)/Release/simder.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/simder.lib
$(COMMONLIBPATH)/Debug/simder.lib:
	${MAKE} /f SimDer.mak "CFG=SimDer - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/simder.lib $(COMMONLIBPATH)/Debug/simder.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/simder.lib
$(COMMONLIBPATH)/Release/simder.lib:
	${MAKE} /f SimDer.mak "CFG=SimDer - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/simder.lib $(COMMONLIBPATH)/Release/simder.lib


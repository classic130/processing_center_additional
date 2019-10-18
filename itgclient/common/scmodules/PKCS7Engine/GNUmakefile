#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2001/09/08 00:31:34 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f PKCS7Engine.mak "CFG=PKCS7Engine - Win32 Release" CLEAN
	-${MAKE} /f PKCS7Engine.mak "CFG=PKCS7Engine - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/PKCS7Engine.lib
	-rm $(COMMONLIBPATH)/Release/PKCS7Engine.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/PKCS7Engine.lib
$(COMMONLIBPATH)/Debug/PKCS7Engine.lib:
	${MAKE} /f PKCS7Engine.mak "CFG=PKCS7Engine - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/PKCS7Engine.lib $(COMMONLIBPATH)/Debug/PKCS7Engine.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/PKCS7Engine.lib
$(COMMONLIBPATH)/Release/PKCS7Engine.lib:
	${MAKE} /f PKCS7Engine.mak "CFG=PKCS7Engine - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/PKCS7Engine.lib $(COMMONLIBPATH)/Release/PKCS7Engine.lib


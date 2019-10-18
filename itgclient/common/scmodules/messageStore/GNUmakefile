#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2001/09/08 00:31:51 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

COMMONLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f MsgStoreLib.mak "CFG=MsgStoreLib - Win32 Release" CLEAN
	-${MAKE} /f MsgStoreLib.mak "CFG=MsgStoreLib - Win32 Debug" CLEAN
	-rm $(COMMONLIBPATH)/Debug/MsgStoreLib.lib
	-rm $(COMMONLIBPATH)/Release/MsgStoreLib.lib
	-rm -rf Debug
	-rm -rf Release
	-rm *.ncb
	-rm *.opt
	-rm *.plg
	-rm *.def

debug-install: debug
debug: $(COMMONLIBPATH)/Debug/MsgStoreLib.lib
$(COMMONLIBPATH)/Debug/MsgStoreLib.lib:
	${MAKE} /f MsgStoreLib.mak "CFG=MsgStoreLib - Win32 Debug"
	mkdir -p $(COMMONLIBPATH)/Debug
	cp Debug/MsgStoreLib.lib $(COMMONLIBPATH)/Debug/MsgStoreLib.lib

release-install: release
cd-install: release
install-ecas: release
install-local: release
release: $(COMMONLIBPATH)/Release/MsgStoreLib.lib
$(COMMONLIBPATH)/Release/MsgStoreLib.lib:
	${MAKE} /f MsgStoreLib.mak "CFG=MsgStoreLib - Win32 Release"
	mkdir -p $(COMMONLIBPATH)/Release
	cp Release/MsgStoreLib.lib $(COMMONLIBPATH)/Release/MsgStoreLib.lib


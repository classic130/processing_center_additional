#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.4.86.1 2000/06/23 23:46:37 mwilson Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../lib

all: debug release

uninstall-local:clean
uninstall-ecas:clean
cd-uninstall:clean
clean :
	${MAKE} /f vsctl.mak "CFG=vsctl - Win32 Release MinDependency" CLEAN
	${MAKE} /f vsctl.mak "CFG=vsctl - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vsfe.dll
	-rm $(APPSLIBPATH)/dynamic/release/vsfe.dll
	-rm $(APPSLIBPATH)/dynamic/debug/vsfe.inf
	-rm $(APPSLIBPATH)/dynamic/release/vsfe.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMindependency
	-rmdir ReleaseMindependency 


debug-install: debug
debug: 
	${MAKE} /f vsctl.mak "CFG=vsctl - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/vsfe.dll $(APPSLIBPATH)/dynamic/debug/vsfe.dll
	cp vsfe.inf $(APPSLIBPATH)/dynamic/debug/vsfe.inf

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vsctl.mak "CFG=vsctl - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMindependency/vsfe.dll $(APPSLIBPATH)/dynamic/release/vsfe.dll
	cp vsfe.inf $(APPSLIBPATH)/dynamic/release/vsfe.inf


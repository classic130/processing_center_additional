#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.1 2001/09/12 00:04:33 npaul Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: debug release

uninstall-local:clean
cd-uninstall:clean
uninstall-ecas:clean
clean :
	-${MAKE} /f vssc.mak CFG="VSSC - Win32 Release MinDependency" CLEAN
	-${MAKE} /f vssc.mak CFG="VSSC - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/VSSC.dll
	-rm $(APPSLIBPATH)/dynamic/release/VSSC.dll
	-rm $(APPSLIBPATH)/dynamic/debug/VSSC.inf
	-rm $(APPSLIBPATH)/dynamic/release/VSSC.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMinDependency
	-rmdir ReleaseMinDependency


debug-install: debug
debug: 
	# building of the PTA idls to be removed when the itgclient_v1_sc simder gets merged with TOT
	midl Ptav3.idl 
	midl certprefs.idl 
	midl export.idl
	midl import.idl
	midl profmgmt.idl
	midl ptadllapi.idl
	midl roamprefs.idl 	
	midl seldigid.idl
	midl srchcrit.idl
	midl uiprefs.idl
	${MAKE} /f vssc.mak CFG="VSSC - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/vssc.dll $(APPSLIBPATH)/dynamic/debug/VSSC.dll
	cp vssc.inf $(APPSLIBPATH)/dynamic/debug/VSSC.inf


release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	# building of the PTA idls to be removed when the itgclient_v1_sc simder gets merged with TOT
	midl Ptav3.idl 
	midl certprefs.idl 
	midl export.idl
	midl import.idl
	midl profmgmt.idl
	midl ptadllapi.idl
	midl roamprefs.idl 	
	midl seldigid.idl
	midl srchcrit.idl
	midl uiprefs.idl
	${MAKE} /f vssc.mak CFG="VSSC - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/vssc.dll $(APPSLIBPATH)/dynamic/release/VSSC.dll
	cp vssc.inf $(APPSLIBPATH)/dynamic/release/VSSC.inf


#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.40.7 2007/02/15 04:01:27 vkulkarni Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f ConfigChk.mak CFG="ConfigChk - Win32 Release MinDependency" CLEAN
	${MAKE} /f ConfigChk.mak CFG="ConfigChk - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vscnfchk.dll
	-rm $(APPSLIBPATH)/dynamic/release/vscnfchk.dll
	-rm $(APPSLIBPATH)/dynamic/debug/vscnfchk.inf
	-rm $(APPSLIBPATH)/dynamic/release/vscnfchk.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMinDependency
	-rmdir ReleaseMinDependency

debug-install: debug
debug:
	${MAKE} /f ConfigChk.mak CFG="ConfigChk - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/vscnfchk.dll $(APPSLIBPATH)/dynamic/debug/vscnfchk.dll
	cp vscnfchk.inf $(APPSLIBPATH)/dynamic/debug/vscnfchk.inf

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f ConfigChk.mak CFG="ConfigChk - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/vscnfchk.dll $(APPSLIBPATH)/dynamic/release/vscnfchk.dll
	cp vscnfchk.inf $(APPSLIBPATH)/dynamic/release/vscnfchk.inf
	ISCmdBld -p iDefenseFix/mpki_vscnfchk_eu_sp1.ism -a English
	ISCmdBld -p iDefenseFix/mpki_vscnfchk_eu_sp1.ism -a Japanese
	ISCmdBld -p iDefenseFix/mpki_vscnfchk_eu2_sp1.ism -a English
	ISCmdBld -p iDefenseFix/mpki_vscnfchk_eu2_sp1.ism -a Japanese

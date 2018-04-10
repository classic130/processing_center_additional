#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.3.236.1 2000/09/01 01:03:30 mwilson Exp $
#

ECAS_HOME=../../../..
include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/main.cfg

MAKE = nmake
unexport MAKEFLAGS

MODULESLIBPATH=../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 ReleaseASM" CLEAN; \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 DebugASM" CLEAN; \
		rm $(MODULESLIBPATH)/static/debug/BSafeLite.lib; \
		rm $(MODULESLIBPATH)/static/release/BSafeLite.lib; \
		rm -r DebugASM; \
		rm -r ReleaseASM; \
	else \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 Release" CLEAN; \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 Debug" CLEAN; \
		rm $(MODULESLIBPATH)/static/debug/BSafeLite.lib; \
		rm $(MODULESLIBPATH)/static/release/BSafeLite.lib; \
		rm -r Debug; \
		rm -r Release; \
	fi;


debug-install: debug
debug:
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 DebugASM"; \
		mkdir -p $(MODULESLIBPATH)/static/debug; \
		cp DebugASM/BSafeLite.lib $(MODULESLIBPATH)/static/debug/BSafeLite.lib; \
	else \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 Debug"; \
		mkdir -p $(MODULESLIBPATH)/static/debug; \
		cp Debug/BSafeLite.lib $(MODULESLIBPATH)/static/debug/BSafeLite.lib; \
	fi;

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 ReleaseASM"; \
		mkdir -p $(MODULESLIBPATH)/static/release; \
		cp ReleaseASM/BSafeLite.lib $(MODULESLIBPATH)/static/release/BSafeLite.lib; \
	else \
		${MAKE} /f BSafeLite.mak CFG="BSafeLite - Win32 Release"; \
		mkdir -p $(MODULESLIBPATH)/static/release; \
		cp Release/BSafeLite.lib $(MODULESLIBPATH)/static/release/BSafeLite.lib; \
	fi;

#	GNUmakefile
#       Developed by Wasim Ilkal


MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f vsdnotz.mak CFG="vsdnotz - Win32 Release MinDependency" CLEAN
	${MAKE} /f vsdnotz.mak CFG="vsdnotz - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/vsdnotz.dll
	-rm $(APPSLIBPATH)/dynamic/release/vsdnotz.dll
	-rm $(APPSLIBPATH)/dynamic/debug/vsdnotz.inf
	-rm $(APPSLIBPATH)/dynamic/debug/vsnzpta.inf
	-rm $(APPSLIBPATH)/dynamic/release/vsdnotz.inf
	-rm $(APPSLIBPATH)/dynamic/release/vsnzpta.inf
	-rm -rf Debug
	-rmdir Debug
	-rm -rf ReleaseMinDependency
	-rmdir ReleaseMinDependency

debug-install: debug
debug:
	${MAKE} /f vsdnotz.mak CFG="vsdnotz - Win32 Debug"
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/vsdnotz.dll $(APPSLIBPATH)/dynamic/debug/vsdnotz.dll
	cp Source/vsdnotz.inf $(APPSLIBPATH)/dynamic/debug/vsdnotz.inf
	cp Source/vsnzpta.inf $(APPSLIBPATH)/dynamic/debug/vsnzpta.inf

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f vsdnotz.mak CFG="vsdnotz - Win32 Release MinDependency"
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp ReleaseMinDependency/vsdnotz.dll $(APPSLIBPATH)/dynamic/release/vsdnotz.dll
	cp Source/vsdnotz.inf $(APPSLIBPATH)/dynamic/release/vsdnotz.inf
	cp Source/vsnzpta.inf $(APPSLIBPATH)/dynamic/release/vsnzpta.inf
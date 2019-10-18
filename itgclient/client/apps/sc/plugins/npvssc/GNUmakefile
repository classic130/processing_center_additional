#	GNUmakefile 
#       Developed by Ajay Jayaram
#	$Id: GNUmakefile,v 1.2 2002/03/08 18:29:06 usha Exp $
#

MAKE = nmake
unexport MAKEFLAGS

APPSLIBPATH=../../../../lib
PLUGINSDKPATH=../../../../../thirdparty/netscape/PluginSDK
NETSCAPEJAVA40PATH=../../../../../thirdparty/netscape/java40
JC=javac
JH=javah

all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f npvssc.mak CFG="npvssc - Win32 Release" CLEAN
	${MAKE} /f npvssc.mak CFG="npvssc - Win32 Debug" CLEAN
	-rm $(APPSLIBPATH)/dynamic/debug/npvssc.dll
	-rm $(APPSLIBPATH)/dynamic/release/npvssc.dll
	-rm $(APPSLIBPATH)/dynamic/debug/npvssc.class
	-rm $(APPSLIBPATH)/dynamic/release/npvssc.class
	-rm -rf Debug
	-rmdir Debug
	-rm -rf Release
	-rmdir Release

debug-install: debug
debug:
	$(JC) -verbose -classpath ".;$(PLUGINSDKPATH)\classes\java_30.zip;$(NETSCAPEJAVA40PATH)\java40.jar" sources/NPVSSC.java
	cp sources/NPVSSC.class .
	$(PLUGINSDKPATH)/bin/win32/$(JH) -v -jri -classpath ".;$(PLUGINSDKPATH)/Classes/java_30.zip;$(NETSCAPEJAVA40PATH)/java.jar" NPVSSC
	$(PLUGINSDKPATH)/bin/win32/$(JH) -v -jri -stubs -classpath ".;$(PLUGINSDKPATH)/Classes/java_30.zip;$(NETSCAPEJAVA40PATH)/java.jar" NPVSSC
	cp NPVSSC.h include
	cp NPVSSC.c sources
	${MAKE} /f npvssc.mak CFG="npvssc - Win32 Debug"
	mv NPVSSC.class ./sources
	mkdir -p $(APPSLIBPATH)/dynamic
	mkdir -p $(APPSLIBPATH)/dynamic/debug
	cp Debug/npvssc.dll $(APPSLIBPATH)/dynamic/debug/npvssc.dll
	cp sources/npvssc.class $(APPSLIBPATH)/dynamic/debug/npvssc.class

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	$(JC) -verbose -classpath ".;$(PLUGINSDKPATH)\classes\java_30.zip;$(NETSCAPEJAVA40PATH)\java40.jar" sources/NPVSSC.java
	cp sources/NPVSSC.class .
	$(PLUGINSDKPATH)/bin/win32/$(JH) -v -jri -classpath ".;$(PLUGINSDKPATH)/Classes/java_30.zip;$(NETSCAPEJAVA40PATH)/java.jar" NPVSSC
	$(PLUGINSDKPATH)/bin/win32/$(JH) -v -jri -stubs -classpath ".;$(PLUGINSDKPATH)/Classes/java_30.zip;$(NETSCAPEJAVA40PATH)/java.jar" NPVSSC
	cp NPVSSC.c sources
	cp NPVSSC.h include
	${MAKE} /f npvssc.mak CFG="npvssc - Win32 Release"
	mv NPVSSC.class ./sources
	mkdir -p $(APPSLIBPATH)/dynamic
	mkdir -p $(APPSLIBPATH)/dynamic/release
	cp Release/npvssc.dll $(APPSLIBPATH)/dynamic/release/npvssc.dll
	cp sources/npvssc.class $(APPSLIBPATH)/dynamic/release/npvssc.class

#
#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.6.126.3 2003/08/13 22:46:56 ajayaram Exp $
#

#
# make for : Signed vspta3.jar
#	     Ptav3.dll
#            NPPTAv3.dll
#            VSPTAv3.class
#            vsnpsetup.exe OR vsnpsetupkm.exe
#            (vsimport.dll)
#
# Target Description :
#
# all : This will create the installables from the "Release" version.
#	It will also copy the installables locally 
#	(itgclient/packager/local-install) as well as in the sitekit
#	CD directory.
#
# install-ecas:
# cd-install: Both these targets will behave same and will create and copy
#	the "Release" version of the installables to the sitekit CD directory.
#
# debug-install-ecas:
# debug-cd-install: Both these targets will behave same and will create and copy
#	the "Debug" version of the installables to the sitekit CD directory.
#
# install-local: This will create and copy the "Release" version of the
#	installables to the local install directory 
#	(itgclient/packager/local-install).
#
# debug-install-local: This will create and copy the "Debug" version of the
#	installables to the local install directory 
#	(itgclient/packager/local-install).
#
# clean:
#	This will remove the installables from the sitekit CD directory as
#	well as the local install directory.
#
# cd-uninstall:
# uninstall-ecas:
#	Both these targets will remove the installables from the sitekit CD
#	directory.
#
# uninstall-local:
#	This will remove the installables from the local install directory.

ECAS_HOME=../../../../..

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/local-install
RELEASECLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/release
RELEASECLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/release
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
DEBUGCLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/debug
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGSERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
CSPDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign
PTADIR=../../activex/pta3

DLLNAME1=Ptav3
DLLNAME2=NPPTAv3
DLLNAME3=VSImport
CLASS1=VSPTAv3
JSINSTALL=vspta3
JSINSTALLKM=vspta3km
SETUP=vsnpsetup
SETUPKM=vsnpsetupkm
SIGNFILE=vscspsign

all: install-ecas install-local

signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Release
	mkdir -p ReleaseKM
	mkdir -p c:\NSJar_Release
	cp $(PTADIR)/$(DLLNAME1).dll Release
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll Release
	cp $(RELEASECLIENTLIBDIR)/$(CLASS1).class Release
	cp $(RELEASECLIENTBINDIR)/$(SETUP).exe Release
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALL).js Release
	cp $(CSPDIR)/$(SIGNFILE) Release
	cp $(PTADIR)/$(DLLNAME1).dll ReleaseKM
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll ReleaseKM
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll ReleaseKM
	cp $(RELEASECLIENTLIBDIR)/$(CLASS1).class ReleaseKM 
	cp $(RELEASECLIENTBINDIR)/$(SETUPKM).exe ReleaseKM
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALLKM).js ReleaseKM
	cp $(CSPDIR)/$(SIGNFILE) ReleaseKM
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vspta3.js" -p "ver1sign" -Z c:\\NSJar_Release\\vspta3.jar Release
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vspta3km.js" -p "ver1sign" -Z c:\\NSJar_Release\\vspta3km.jar ReleaseKM
	cp c:/NSJar_Release/vspta3.jar Release
	cp c:/NSJar_Release/vspta3km.jar ReleaseKM

debug-signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Debug
	mkdir -p DebugKM
	mkdir -p c:\NSJar_Debug
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll Debug
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll Debug
	cp $(DEBUGCLIENTLIBDIR)/$(CLASS1).class Debug
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALL).js Debug
	cp $(DEBUGCLIENTBINDIR)/$(SETUP).exe Debug
	cp $(CSPDIR)/$(SIGNFILE) Debug
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(CLASS1).class DebugKM
	cp $(DEBUGCLIENTBINDIR)/$(SETUPKM).exe DebugKM
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALLKM).js DebugKM
	cp $(CSPDIR)/$(SIGNFILE) DebugKM
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vspta3.js" -p "ver1sign" -Z c:\\NSJar_Debug\\vspta3.jar Debug
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vspta3km.js" -p "ver1sign" -Z c:\\NSJar_Debug\\vspta3km.jar DebugKM
	cp c:/NSJar_Debug/vspta3.jar Debug
	cp c:/NSJar_Debug/vspta3km.jar Debug

debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.jar --> $(CDINSTALLHTMLDOCSDIR)"
	cp Release/vspta3.jar $(CDINSTALLHTMLDOCSDIR)
	cp ReleaseKM/vspta3km.jar $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug vspta3.cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp Debug/vspta3.jar $(CDINSTALLHTMLDOCSDIR)
	cp DebugKM/vspta3km.jar $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.jar --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Release/vspta3.jar $(LOCAL_INSTALL_DIR)
	cp ReleaseKM/vspta3km.jar $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.jar --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Debug/vspta3.jar $(LOCAL_INSTALL_DIR)
	cp DebugKM/vspta3km.jar $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	-rm -rf Debug
	-rm -rf Release
	-rm -rf DebugKM
	-rm -rf ReleaseKM
	-rm -rf c:/NSJar_Release
	-rm -rf c:/NSJar_Debug

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local vspta3.jar"
	$(RM) $(LOCAL_INSTALL_DIR)/vspta3.jar
	$(RM) $(LOCAL_INSTALL_DIR)/vspta3km.jar
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/vspta3.jar"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vspta3.jar
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vspta3km.jar
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


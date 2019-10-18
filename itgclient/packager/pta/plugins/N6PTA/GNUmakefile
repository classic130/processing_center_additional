#
#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.3.10.1 2004/07/24 20:29:29 eleung Exp $
#

#
# make for : Signed vspta3.xpi
#	     Ptav3.dll
#            N6PTA.dll
#            N6PTA.xpt
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
DLLNAME2=N6PTA
DLLNAME3=VSImport
XPT1=N6PTA
JSINSTALL=install
JSINSTALLKM=install_km
SETUP=vsnpsetup
SETUPKM=vsnpsetupkm
SIGNFILE=vscspsign

all: install-ecas install-local

signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Release
	mkdir -p Release/components
	mkdir -p ReleaseKM
	mkdir -p ReleaseKM/components
	cp $(PTADIR)/$(DLLNAME1).dll Release/components
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll Release/components
	cp $(RELEASECLIENTLIBDIR)/$(XPT1).xpt Release/components
	cp $(RELEASECLIENTBINDIR)/$(SETUP).exe Release/components
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALL).js Release/install.js
	cp $(CSPDIR)/$(SIGNFILE) Release/components
	cp $(PTADIR)/$(DLLNAME1).dll ReleaseKM/components
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll ReleaseKM/components
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll ReleaseKM/components
	cp $(RELEASECLIENTLIBDIR)/$(XPT1).xpt ReleaseKM/components
	cp $(RELEASECLIENTBINDIR)/$(SETUPKM).exe ReleaseKM/components
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALLKM).js ReleaseKM/install.js
	cp $(CSPDIR)/$(SIGNFILE) ReleaseKM/components
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\Release\\vspta3.xpi Release
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\ReleaseKM\\vspta3km.xpi ReleaseKM

debug-signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Debug
	mkdir -p DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll Debug
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll Debug
	cp $(DEBUGCLIENTLIBDIR)/$(XPT1).xpt Debug
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALL).js Debug/install.js
	cp $(DEBUGCLIENTBINDIR)/$(SETUP).exe Debug
	cp $(CSPDIR)/$(SIGNFILE) Debug
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll DebugKM
	cp $(DEBUGCLIENTLIBDIR)/$(XPT1).xpt DebugKM
	cp $(DEBUGCLIENTBINDIR)/$(SETUPKM).exe DebugKM
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALLKM).js DebugKM/install.js
	cp $(CSPDIR)/$(SIGNFILE) DebugKM
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\Debug\\vspta3.xpi Debug
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\DebugKM\\vspta3km.xpi DebugKM


debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.xpi --> $(CDINSTALLHTMLDOCSDIR)"
	cp Release/vspta3.xpi $(CDINSTALLHTMLDOCSDIR)
	cp ReleaseKM/vspta3km.xpi $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug vspta3.cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp Debug/vspta3.xpi $(CDINSTALLHTMLDOCSDIR)
	cp DebugKM/vspta3km.xpi $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.xpi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Release/vspta3.xpi $(LOCAL_INSTALL_DIR)
	cp ReleaseKM/vspta3km.xpi $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.xpi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Debug/vspta3.xpi $(LOCAL_INSTALL_DIR)
	cp DebugKM/vspta3km.xpi $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	-rm -rf Debug
	-rm -rf Release
	-rm -rf DebugKM
	-rm -rf ReleaseKM

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local vspta3.xpi"
	$(RM) $(LOCAL_INSTALL_DIR)/vspta3.xpi
	$(RM) $(LOCAL_INSTALL_DIR)/vspta3km.xpi
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/vspta3.xpi"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vspta3.xpi
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vspta3km.xpi
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


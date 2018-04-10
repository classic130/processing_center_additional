#
#       GNUmakefile 
#       Developed by Wasim Ilkal
#

#
# make for : Signed vsdnotz.xpi
#	     Signed vsnzpta.xpi	
#	     vsdnotz.dll
#	     ptav3.dll
#	     n6pta.dll
#	     n6pta.xpt
#            vsnzpsetup.exe
#	     vsnzptasetup.exe
#
# Target Description :
#
# all : This will create the installables from the "Release" version. It will #	create 2 xpi files, one will contain only the vsdnotz.dll and the other
#	will contain the vsdnotz.dll and all files required by the PTA.
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

DLLNAME1=vsdnotz
DLLNAME2=Ptav3
DLLNAME3=N6PTA
XPT1=N6PTA
JSINSTALL=install_nz
JSINSTALLPTA=install_nzpta
SETUP=vsnzpsetup
SETUPPTA=vsnzptasetup
SIGNFILE=vscspsign

all: install-ecas install-local

signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating vsdnotz.xpi and vsnzpta.xpi"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Release
	mkdir -p Release/components
	mkdir -p ReleasePta
	mkdir -p ReleasePta/components
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll Release/components
	cp $(RELEASECLIENTBINDIR)/$(SETUP).exe Release/components
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALL).js Release/install.js

	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll ReleasePta/components	
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll ReleasePta/components
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll ReleasePta/components
	cp $(RELEASECLIENTLIBDIR)/$(XPT1).xpt ReleasePta/components
	cp $(RELEASECLIENTBINDIR)/$(SETUPPTA).exe ReleasePta/components
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALLPTA).js ReleasePta/install.js
	cp $(CSPDIR)/$(SIGNFILE) ReleasePta/components
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\Release\\vsdnotz.xpi Release
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\ReleasePta\\vsnzpta.xpi ReleasePta

debug-signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - vsdnotz.xpi and vsnzpta.xpi"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Debug
	mkdir -p DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll Debug
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALL).js Debug/install.js
	cp $(DEBUGCLIENTBINDIR)/$(SETUP).exe Debug

	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(XPT1).xpt DebugPta
	cp $(DEBUGCLIENTBINDIR)/$(SETUPPTA).exe DebugPta
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALLPTA).js DebugPta/install.js
	cp $(CSPDIR)/$(SIGNFILE) DebugPta
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\Debug\\vsdnotz.xpi Debug
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "install.js" -p "ver1sign" -Z .\\DebugPta\\vsnzpta.xpi DebugPta

debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vsdnotz.xpi and vsnzpta.xpi --> $(CDINSTALLHTMLDOCSDIR)"
	cp Release/vsdnotz.xpi $(CDINSTALLHTMLDOCSDIR)
	cp ReleasePta/vsnzpta.xpi $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug vsdnotz.xpi and vsnzpta.xpi --> $(CDINSTALLHTMLDOCSDIR)"
	cp Debug/vsdnotz.xpi $(CDINSTALLHTMLDOCSDIR)
	cp DebugPta/vsnzpta.xpi $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vsdnotz.xpi and vsnzpta.xpi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Release/vsdnotz.xpi $(LOCAL_INSTALL_DIR)
	cp ReleasePta/vsnzpta.xpi $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vsdnotz.xpi and vsnzpta.xpi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Debug/vsdnotz.xpi $(LOCAL_INSTALL_DIR)
	cp DebugPta/vsnzpta.xpi $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	-rm -rf Debug
	-rm -rf Release
	-rm -rf DebugPta
	-rm -rf ReleasePta

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local vsdnotz.xpi and vsnzpta.xpi"
	$(RM) $(LOCAL_INSTALL_DIR)/vsdnotz.xpi
	$(RM) $(LOCAL_INSTALL_DIR)/vsnzpta.xpi
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/vsdnotz.xpi and vsnzpta.xpi"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vsdnotz.xpi
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vsnzpta.xpi
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


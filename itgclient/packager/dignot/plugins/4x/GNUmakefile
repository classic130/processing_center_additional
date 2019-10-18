#
#       GNUmakefile 
#       Developed by Wasim Ilkal
#

#
# make for : Signed vsdnotz.jar
#	     Signed vsnzpta.jar
#	     vsdnotz.dll
#            vsnzpsetup.exe
#	     ptav3.dll
#	     npptav3.dll
#	     VSPTAv3.class
#	     vsnzptasetup.exe
#
# Target Description :
#
# all : This will create the installables from the "Release" version. It will create 2 jar
#	files, one will contain only the vsdnotz.dll, other will contain vsdnotz.dll and
#	all the files that are needed for the PTA plugin.
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
DLLNAME3=NPPTAv3
CLASS1=VSPTAv3
JSINSTALL=vsdnotz
JSINSTALLPTA=vsnzpta
SETUP=vsnzpsetup
SETUPPTA=vsnzptasetup
SIGNFILE=vscspsign

all: install-ecas install-local

signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating vsdnotz.jar and vsnzpta.jar"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Release
	mkdir -p ReleasePta
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll Release
	cp $(RELEASECLIENTBINDIR)/$(SETUP).exe Release
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALL).js Release

	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll ReleasePta
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll ReleasePta
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll ReleasePta
	cp $(RELEASECLIENTLIBDIR)/$(CLASS1).class ReleasePta
	cp $(RELEASECLIENTBINDIR)/$(SETUPPTA).exe ReleasePta
	cp $(RELEASECLIENTBINDIR)/$(JSINSTALLPTA).js ReleasePta
	cp $(CSPDIR)/$(SIGNFILE) ReleasePta

	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vsdnotz.js" -p "ver1sign" -Z .\\Release\\vsdnotz.jar Release
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vsnzpta.js" -p "ver1sign" -Z .\\ReleasePta\\vsnzpta.jar ReleasePta

debug-signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - vsdnotz.jar and vsnzpta.jar"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p Debug
	mkdir -p DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll Debug
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALL).js Debug
	cp $(DEBUGCLIENTBINDIR)/$(SETUP).exe Debug

	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll DebugPta
	cp $(DEBUGCLIENTLIBDIR)/$(CLASS1).class DebugPta
	cp $(DEBUGCLIENTBINDIR)/$(SETUPPTA).exe DebugPta
	cp $(DEBUGCLIENTBINDIR)/$(JSINSTALLPTA).js DebugPta
	cp $(CSPDIR)/$(SIGNFILE) DebugPta
	
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vsdnotz.js" -p "ver1sign" -Z .\\Debug\\vsdnotz.jar Debug
	signtool -d a:\ns -k "VeriSign Inc.'s VeriSign, Inc. ID" -i "vsnzpta.js" -p "ver1sign" -Z .\\DebugPta\\vsnzpta.jar DebugPta

debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vsdnotz.jar and vsnzpta.jar --> $(CDINSTALLHTMLDOCSDIR)"
	cp Release/vsdnotz.jar $(CDINSTALLHTMLDOCSDIR)
	cp ReleasePta/vsnzpta.jar $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug vsdnotz.jar and vsnzpta.jar --> $(CDINSTALLHTMLDOCSDIR)"
	cp Debug/vsdnotz.jar $(CDINSTALLHTMLDOCSDIR)
	cp DebugPta/vsnzpta.jar $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vsdnotz.jar and vsnzpta.jar --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Release/vsdnotz.jar $(LOCAL_INSTALL_DIR)
	cp ReleasePta/vsnzpta.jar $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-signtool
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vsdnotz.jar and vsnzpta.jar --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp Debug/vsdnotz.jar $(LOCAL_INSTALL_DIR)
	cp DebugPta/vsnzpta.jar $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	-rm -rf Debug
	-rm -rf Release
	-rm -rf DebugPta
	-rm -rf ReleasePta

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local vsdnotz.jar and vsnzpta.jar"
	$(RM) $(LOCAL_INSTALL_DIR)/vsdnotz.jar
	$(RM) $(LOCAL_INSTALL_DIR)/vsnzpta.jar
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/vsdnotz.jar and vsnzpta.jar"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vsdnotz.jar
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vsnzpta.jar
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


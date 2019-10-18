#
#       GNUmakefile 
#       Developed by Wasim Ilkal

#

#
# make for : Signed vsnzpta.cab
#	     Signed vsdnotz.cab
#	     vsdnotz.dll
#	     ptav3.dll
#
# Target Description :
#
# all : This will create the cab file containing the PTA activex and the 
#	digital notarization client activex in the current directory. It will also create
#	a cab file having only the digital notarization client activex control.
#	It will also copy the installables locally (itgclient/packager/local-install) as	#	well as in the sitekitCD directory.
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
RELEASESERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
CSPSIGNDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign


DLLNAME1=vsdnotz
DLLNAME2=ptav3
CABNAME1=vsnzpta
CABNAME2=vsdnotz
SIGNFILE=vscspsign

all: install-ecas install-local

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(CABNAME1).cab and $(CABNAME2).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(RELEASECLIENTLIBDIR)/$(CABNAME1).inf .
	cp $(RELEASECLIENTLIBDIR)/$(CABNAME2).inf .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll .
	cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N $(CABNAME1).cab $(DLLNAME2).dll $(SIGNFILE) $(DLLNAME1).dll $(CABNAME1).inf 
	cabarc N $(CABNAME2).cab $(DLLNAME1).dll $(CABNAME2).inf

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(CABNAME1).cab and $(CABNAME2).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(CABNAME1).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(CABNAME2).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll .
	cabarc N $(CABNAME1).cab $(DLLNAME2).dll $(SIGNFILE) $(DLLNAME1).dll $(CABNAME1).inf 
	cabarc N $(CABNAME2).cab $(DLLNAME1).dll $(CABNAME2).inf

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(CABNAME1).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Personal Trust Agent ActiveX Control and Digital Notarization" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(CABNAME1).cab	

	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(CABNAME2).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Digital Notarization ActiveX Control" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(CABNAME2).cab


debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(CABNAME1).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(CABNAME1).cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(CABNAME2).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(CABNAME2).cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug $(CABNAME1).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(CABNAME1).cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug $(CABNAME2).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(CABNAME2).cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(CABNAME1).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(CABNAME1).cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(CABNAME2).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(CABNAME2).cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(CABNAME1).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(CABNAME1).cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(CABNAME2).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(CABNAME2).cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""


clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(CABNAME1).inf
	$(RM) $(CABNAME2).inf
	$(RM) $(CABNAME1).cab
	$(RM) $(CABNAME2).cab
	$(RM) $(DLLNAME1).dll
	$(RM) $(DLLNAME2).dll
	$(RM) $(SIGNFILE)

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(CABNAME1).cab"
	$(RM) $(LOCAL_INSTALL_DIR)/$(CABNAME1).cab
	@$(ECHO) ""

	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(CABNAME2).cab"
	$(RM) $(LOCAL_INSTALL_DIR)/$(CABNAME2).cab
	@$(ECHO) ""


cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(CABNAME1).cab"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(CABNAME1).cab
	@$(ECHO) ""

	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(CABNAME2).cab"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(CABNAME2).cab
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


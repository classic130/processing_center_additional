#
#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.4.10.1 2005/02/15 20:24:49 eleung Exp $
#

#
# make for : Signed vspta3.cab
#	     ptav3.dll
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
RELEASESERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/debug
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGSERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
CSPSIGNDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign

DLLNAME1=Ptav3
SIGNFILE=vscspsign
DLLNAME2=VS_IBMTSS
DLLNAME3=VS_INFYTSS

all: install-ecas install-local

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
#	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).inf .
#	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll .
	cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N vspta3.cab $(DLLNAME1).inf $(DLLNAME1).dll $(SIGNFILE) $(DLLNAME2).dll $(DLLNAME3).dll

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll .
	cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N vspta3.cab $(DLLNAME1).inf $(DLLNAME1).dll $(SIGNFILE)

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(DLLNAME1).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Personal Trust Agent ActiveX Control" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" vspta3.cab	

debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp vspta3.cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug vspta3.cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp vspta3.cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp vspta3.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vspta3.cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp vspta3.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	#$(RM) $(DLLNAME1).inf
	$(RM) vspta3.cab
	#$(RM) $(DLLNAME1).dll
	$(RM) $(DLLNAME2).dll
	$(RM) $(DLLNAME3).dll
	$(RM) $(SIGNFILE)

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local vspta3.cab"
	$(RM) $(LOCAL_INSTALL_DIR)/vspta3.cab
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/vspta3.cab"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vspta3.cab
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


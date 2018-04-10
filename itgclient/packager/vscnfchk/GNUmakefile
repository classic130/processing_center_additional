#
#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.3.190.1 2007/01/03 07:10:27 ptunagaria Exp $
#

#
# make for : Signed vscnfchk.cab
#	     vscnfchk.dll
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

ECAS_HOME=../../..

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/local-install
RELEASECLIENTLIBDIR=$(ECAS_HOME)/itgclient/PersonalCertificateAgent/lib/dynamic/release
RELEASESERVERLIBDIR=$(ECAS_HOME)/itgclient/PersonalCertificateAgent/lib/dynamic/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/PersonalCertificateAgent/lib/dynamic/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/PersonalCertificateAgent/lib/dynamic/debug
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/PersonalCertificateAgent/bin/release
DEBUGSERVERBINDIR=$(ECAS_HOME)/itgclient/PersonalCertificateAgent/bin/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin

DLLNAME1=vscnfchk

all: install-ecas install-local

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll .
	cabarc N vscnfchk.cab $(DLLNAME1).inf $(DLLNAME1).dll

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll .
	cabarc N vscnfchk.cab $(DLLNAME1).inf $(DLLNAME1).dll

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(DLLNAME1).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Configuration Checker" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" vscnfchk.cab	

debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vscnfchk.cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp vscnfchk.cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug vscnfchk.cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp vscnfchk.cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vscnfchk.cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp vscnfchk.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing vscnfchk.cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp vscnfchk.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(DLLNAME1).inf
	$(RM) vscnfchk.cab
	$(RM) $(DLLNAME1).dll

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local vscnfchk.cab"
	$(RM) $(LOCAL_INSTALL_DIR)/vscnfchk.cab
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/vscnfchk.cab"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/vscnfchk.cab
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


#
#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.6.76.1 2000/07/27 13:06:05 mwilson Exp $
#
# make for : vslog.exe, chpasswd.exe and Signed vsfe.cab
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
RELEASELIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/release
DEBUGLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
RELEASEBINDIR=$(ECAS_HOME)/itgclient/client/bin/release
DEBUGBINDIR=$(ECAS_HOME)/itgclient/client/bin/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CSPSIGNDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign
DLLNAME1=vsfe
DLLNAME2=ptav3
EXENAME1=vslog
EXENAME2=chpasswd
SIGNFILE=vscspsign

all: install-ecas install-local 

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(RELEASELIBDIR)/$(DLLNAME1).inf .
	cp $(RELEASELIBDIR)/$(DLLNAME1).dll .
	@if [ ! -e $(RELEASELIBDIR)/$(DLLNAME2).dll ]; \
	then \
		$(ECHO) "Unable to find $(RELEASELIBDIR)/$(DLLNAME2).dll needed for creating $(DLLNAME1).cab"; \
		exit 1; \
	fi; \
	cp $(RELEASELIBDIR)/$(DLLNAME2).dll .	
	@if [ ! -e $(CSPSIGNDIR)/$(SIGNFILE) ]; \
	then \
		$(ECHO) "Unable to find $(CSPSIGNDIR)/$(SIGNFILE) needed for creating $(DLLNAME1).cab"; \
		exit 1; \
	fi; \
	cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N $(DLLNAME1).cab $(DLLNAME1).inf $(DLLNAME1).dll $(DLLNAME2).dll $(SIGNFILE)

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(DLLNAME1).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGLIBDIR)/$(DLLNAME1).inf .
	cp $(DEBUGLIBDIR)/$(DLLNAME1).dll .
	@if [ ! -e $(DEBUGLIBDIR)/$(DLLNAME2).dll ]; \
	then \
		$(ECHO) "Unable to find $(DEBUGLIBDIR)/$(DLLNAME2).dll needed for creating $(DLLNAME1).cab"; \
		exit 1; \
	fi; \
	cp $(DEBUGLIBDIR)/$(DLLNAME2).dll .
	@if [ ! -e $(CSPSIGNDIR)/$(SIGNFILE) ]; \
	then \
		$(ECHO) "Unable to find $(CSPSIGNDIR)/$(SIGNFILE) needed for creating $(DLLNAME1).cab"; \
		exit 1; \
	fi; \
	cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N $(DLLNAME1).cab $(DLLNAME1).inf $(DLLNAME1).dll $(DLLNAME2).dll $(SIGNFILE)

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(DLLNAME1).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign File Encryption Tool ActiveX Control" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(DLLNAME1).cab	

debug-copylocal:
	cp $(DEBUGBINDIR)/$(EXENAME1).exe .
	cp $(DEBUGBINDIR)/$(EXENAME2).exe .

release-copylocal:
	cp $(RELEASEBINDIR)/$(EXENAME1).exe .
	cp $(RELEASEBINDIR)/$(EXENAME2).exe .

cd-install: install-ecas
install-ecas: cabarc signcab release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(DLLNAME1).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME1).cab $(CDINSTALLHTMLDOCSDIR)
	cp $(EXENAME1).exe $(CDINSTALLHTMLDOCSDIR)
	cp $(EXENAME2).exe $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab debug-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug - $(DLLNAME1).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME1).cab $(CDINSTALLHTMLDOCSDIR)
	cp $(EXENAME1).exe $(CDINSTALLHTMLDOCSDIR)
	cp $(EXENAME2).exe $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""

install-local: cabarc signcab release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(DLLNAME1).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME1).cab $(LOCAL_INSTALL_DIR)
	cp $(EXENAME1).exe $(LOCAL_INSTALL_DIR)
	cp $(EXENAME2).exe $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab debug-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(DLLNAME1).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME1).cab $(LOCAL_INSTALL_DIR)
	cp $(EXENAME1).exe $(LOCAL_INSTALL_DIR)
	cp $(EXENAME2).exe $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) -rf $(DLLNAME1).inf
	$(RM) -rf $(DLLNAME1).cab
	$(RM) -rf $(DLLNAME1).dll
	$(RM) -rf $(DLLNAME2).dll
	$(RM) -rf $(EXENAME1).exe
	$(RM) -rf $(EXENAME2).exe
	$(RM) -rf $(SIGNFILE)

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(DLLNAME1).cab"
	$(RM) -rf $(LOCAL_INSTALL_DIR)/$(DLLNAME1).cab
	$(RM) -rf $(LOCAL_INSTALL_DIR)/$(EXENAME1).exe
	$(RM) -rf $(LOCAL_INSTALL_DIR)/$(EXENAME2).exe
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(DLLNAME1).cab"
	$(RM) -rf $(CDINSTALLHTMLDOCSDIR)/$(DLLNAME1).cab
	$(RM) -rf $(CDINSTALLHTMLDOCSDIR)/$(EXENAME1).exe
	$(RM) -rf $(CDINSTALLHTMLDOCSDIR)/$(EXENAME2).exe
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


#
#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.2.1 2002/08/21 04:52:20 sbajaj Exp $
#

#
# make for : Signed xenroll.cab
#	     xenroll.dll
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

DLLNAME1=xenroll

all: install-ecas install-local

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	cabarc N xenroll.cab $(DLLNAME1).inf $(DLLNAME1).dll

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab"
	cabarc N xenroll.cab $(DLLNAME1).inf $(DLLNAME1).dll

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(DLLNAME1).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "Microsoft Certificate Enrollment CAB" -i "http://www.microsoft.com/security" -t "http://timestamp.verisign.com/scripts/timstamp.dll" xenroll.cab	

debug-copylocal:

release-copylocal:

cd-install: install-ecas
install-ecas: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing xenroll.cab --> $(LOCAL_INSTALL_DIR)"
	cp xenroll.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug xenroll.cab --> $(LOCAL_INSTALL_DIR)"
	cp xenroll.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

install-local: cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing xenroll.cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp xenroll.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing xenroll.cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp xenroll.cab $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) xenroll.cab

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local xenroll.cab"
	$(RM) $(LOCAL_INSTALL_DIR)/xenroll.cab
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(LOCAL_INSTALL_DIR)/xenroll.cab"
	$(RM) $(LOCAL_INSTALL_DIR)/xenroll.cab
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


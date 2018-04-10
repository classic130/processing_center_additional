#
#       GNUmakefile 
#       Developed by Ajay Jayaram
#	$Id: GNUmakefile,v 1.1.4.1 2003/05/16 20:51:20 sgoginen Exp $
#
#
# make for : MSI zip files for PTA
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
#
# install-local: This will create and copy the "Release" version of the
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

ECAS_HOME=../../../../


include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/local-install
#CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLHTMLDOCSDIR=$(ECAS_HOME)/itgclient/packager/local-install
PTAUPDATERMSIZIP=ptav3updatermsi
PTALST=pta-updater.lst

#all: install-ecas install-local
all:install-local

release-copylocal:
	wzzip $(PTAUPDATERMSIZIP).zip @$(PTALST)

cd-install: install-ecas
install-ecas: release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(PTAUPDATERMSIZIP).zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(PTAUPDATERMSIZIP).zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""


install-local: release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(PTAUPDATERMSIZIP).zip, $(PTAMSIKMZIP).zip --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(PTAUPDATERMSIZIP).zip $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""


clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(PTAUPDATERMSIZIP).zip

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(PTAUPDATERMSIZIP).zip, $(PTAMSIKMZIP).zip"
	$(RM) $(LOCAL_INSTALL_DIR)/$(PTAUPDATERMSIZIP).zip
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(PTAUPDATERMSIZIP).zip, $(PTAMSIKMZIP).zip"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(PTAUPDATERMSIZIP).zip
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


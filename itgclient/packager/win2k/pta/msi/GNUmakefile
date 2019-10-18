#
#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.66.1 2003/07/29 18:49:55 ajayaram Exp $
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

ECAS_HOME=../../../../..


include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/local-install
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
PTAMSIZIP=ptamsi
PTAMSIKMZIP=pta_netscape4x
PTALST=pta.lst
PTAKMLST=ptakm.lst

all: install-ecas install-local

release-copylocal:

#	wzzip $(PTAMSIZIP).zip @$(PTALST)
	wzzip $(PTAMSIKMZIP).zip @$(PTAKMLST)

cd-install: install-ecas
install-ecas: release-copylocal
	@$(ECHO) ""
#	@$(ECHO) "$(ME):Installing $(PTAMSIZIP).zip --> $(CDINSTALLHTMLDOCSDIR)"
#	cp $(PTAMSIZIP).zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing $(PTAMSIKMZIP).zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(PTAMSIKMZIP).zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""


install-local: release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(PTAMSIKMZIP).zip --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
#	cp $(PTAMSIZIP).zip $(LOCAL_INSTALL_DIR)
	cp $(PTAMSIKMZIP).zip $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""


clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
#	$(RM) $(PTAMSIZIP).zip
	$(RM) $(PTAMSIKMZIP).zip

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(PTAMSIKMZIP).zip"
#	$(RM) $(LOCAL_INSTALL_DIR)/$(PTAMSIZIP).zip
	$(RM) $(LOCAL_INSTALL_DIR)/$(PTAMSIKMZIP).zip
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(PTAMSIKMZIP).zip"
#	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(PTAMSIZIP).zip
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(PTAMSIKMZIP).zip
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


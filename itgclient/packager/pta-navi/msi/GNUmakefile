#
#       GNUmakefile 
#       Developed by Ajay Jayaram
#	$Id: GNUmakefile,v 1.1.2.2 2003/07/25 22:45:33 ajayaram Exp $
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
PTAUPDATERMSIZIP=pta_alllang
PTALST=pta-naviall.lst

PTACS=pta-navics.lst
PTACT=pta-navict.lst
PTADAN=pta-navidan.lst
PTADUTCH=pta-navidutch.lst
PTAFRN=pta-navifrn.lst
PTAGER=pta-naviger.lst
PTAIT=pta-naviit.lst
PTAJAP=pta-navijap.lst
PTAKOR=pta-navikor.lst
PTAPOR=pta-navipor.lst
PTASPN=pta-navispn.lst
PTASW=pta-navisw.lst
PTAFN=pta-navifn.lst
PTAENG=pta-navieng.lst


#all: install-ecas install-local
all:install-local

release-copylocal:
	wzzip $(PTAUPDATERMSIZIP).zip @$(PTALST)
	wzzip pta_chinesesimp.zip @$(PTACS)
	wzzip pta_chinesetrad.zip @$(PTACT)
	wzzip pta_danish.zip @$(PTADAN)
	wzzip pta_dutch.zip @$(PTADUTCH)
	wzzip pta_french.zip @$(PTAFRN)
	wzzip pta_german.zip @$(PTAGER)
	wzzip pta_italian.zip @$(PTAIT)
	wzzip pta_japanese.zip @$(PTAJAP)
	wzzip pta_korean.zip @$(PTAKOR)
	wzzip pta_portuguese.zip @$(PTAPOR)
	wzzip pta_spanish.zip @$(PTASPN)
	wzzip pta_swedish.zip @$(PTASW)
	wzzip pta_finnish.zip @$(PTAFN)
	wzzip pta_english.zip @$(PTAENG)



cd-install: install-ecas
install-ecas: release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(PTAUPDATERMSIZIP).zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp *.zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""


install-local: release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(PTAUPDATERMSIZIP).zip, $(PTAMSIKMZIP).zip --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp *.zip $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""


clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(PTAUPDATERMSIZIP).zip

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(PTAUPDATERMSIZIP).zip, $(PTAMSIKMZIP).zip"
	$(RM) $(LOCAL_INSTALL_DIR)/*.zip
	$(RM) *.zip
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(PTAUPDATERMSIZIP).zip, $(PTAMSIKMZIP).zip"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/*.zip
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


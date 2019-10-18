#
#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.1 2001/10/04 01:11:43 smerchan Exp $
#
#
# make for : Zip files for Digital Notarization Client Kit
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
TEMPKITDIR=$(ECAS_HOME)/itgclient/packager/win2k/dignot/msi/dnzkit
TEMPKITDIRNAME=dnzkit
KITZIP=dnzmsikit
SRCMSI1=vsdnotz
SRCMSI2=vsnzpta
SRCMSI3=nppta3nz
SRCMSI4=n6pta3nz

all: install-ecas install-local

zipkit: 
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(KITZIP)"
	mkdir -p $(TEMPKITDIR)
	mkdir -p $(TEMPKITDIR)/engine
	cp $(ECAS_HOME)/itgclient/sitekit/engine/ntcustomizer.exe $(TEMPKITDIR)/engine/customizer.exe
	cp $(ECAS_HOME)/itgclient/sitekit/engine/libpmutil.dll.nt $(TEMPKITDIR)/engine/libpmutil.dll
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/dnzcustomize.bat $(TEMPKITDIR)/engine/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/createmst.vbs $(TEMPKITDIR)/engine/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/removetags.vbs $(TEMPKITDIR)/engine/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/removeempty.vbs $(TEMPKITDIR)/engine/
	mkdir -p $(TEMPKITDIR)/fragments/Global
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/fragments/Global/*.frg $(TEMPKITDIR)/fragments/Global/
	mkdir -p $(TEMPKITDIR)/fragments/Enrollment
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/fragments/Enrollment/*.frg $(TEMPKITDIR)/fragments/Enrollment/
	mkdir -p $(TEMPKITDIR)/templates
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/customizednz.lst $(TEMPKITDIR)/templates/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/gendnzmst.lst $(TEMPKITDIR)/templates/
	mkdir -p $(TEMPKITDIR)/templates/dnzpackages/vsdnotz/idts
	cp $(SRCMSI1).msi $(TEMPKITDIR)/templates/dnzpackages/vsdnotz/vsdnotz.msi
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/idts/dignot/vsdnotz/Property.idt $(TEMPKITDIR)/templates/dnzpackages/vsdnotz/idts/
	mkdir -p $(TEMPKITDIR)/templates/dnzpackages/vsnzpta/idts
	cp $(SRCMSI2).msi $(TEMPKITDIR)/templates/dnzpackages/vsnzpta/vsnzpta.msi
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/idts/dignot/vsnzpta/Property.idt $(TEMPKITDIR)/templates/dnzpackages/vsnzpta/idts/
	mkdir -p $(TEMPKITDIR)/templates/dnzpackages/nppta3nz/idts
	cp $(SRCMSI3).msi $(TEMPKITDIR)/templates/dnzpackages/nppta3nz/nppta3nz.msi
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/idts/dignot/nppta3nz/Property.idt $(TEMPKITDIR)/templates/dnzpackages/nppta3nz/idts/
	mkdir -p $(TEMPKITDIR)/templates/dnzpackages/n6pta3nz/idts
	cp $(SRCMSI4).msi $(TEMPKITDIR)/templates/dnzpackages/n6pta3nz/n6pta3nz.msi
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/idts/dignot/n6pta3nz/Property.idt $(TEMPKITDIR)/templates/dnzpackages/n6pta3nz/idts/
	wzzip -r -P $(KITZIP).zip $(TEMPKITDIRNAME)

cd-install: install-ecas
install-ecas: zipkit
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(KITZIP).zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(KITZIP).zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) ""


install-local: zipkit
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(KITZIP).zip --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(KITZIP).zip $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""


clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(KITZIP).zip

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(KITZIP).zip"
	$(RM) $(LOCAL_INSTALL_DIR)/$(KITZIP).zip
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(KITZIP).zip"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(KITZIP).zip
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


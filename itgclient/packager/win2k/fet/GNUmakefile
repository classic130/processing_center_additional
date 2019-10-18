
#       GNUmakefile 
#       Developed by Sameer Merchant
#	$Id: GNUmakefile,v 1.1.4.1 2001/06/07 08:40:32 sbajaj Exp $
#

#
# make for : Signed vspta3.msi
#	     Ptav3.dll
#            vsfe.dll
#            (vsimport.dll)
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

ECAS_HOME=../../../..

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
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
CSPDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign

ISMFILE1=fet
MSIFILE1=fet
SIGNFILE=vscspsign
SRCMSI1=vsfe/Release\ 1/DiskImages/DISK1/VeriSign\ File\ Encryption\ Tool
TEMPKITDIR=$(ECAS_HOME)/itgclient/packager/win2k/fet/fetkit
TEMPKITDIRNAME=fetkit
KITLIST=fet.lst
KITZIP=fetmsikit

all: install-ecas install-local

insertsig:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Inserting signature in $(ISMFILE1).ism"
	cp $(CSPDIR)/$(SIGNFILE) .
	$(ECAS_HOME)/itgclient/packager/win2k/common/scripts/convtoreg "$(SIGNFILE)"
	cscript $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/InsertSig.vbs "$(SIGNFILE).reg" "$(ISMFILE1).ism"
	
buildmsi:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Building $(MSIFILE1).msi"
	ISCmdBld -p "$(ISMFILE1).ism"

zipkit: 
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(KITZIP)"
	mkdir -p $(TEMPKITDIR)
	mkdir -p $(TEMPKITDIR)/engine
	cp $(ECAS_HOME)/itgclient/sitekit/engine/ntcustomizer.exe $(TEMPKITDIR)/engine/customizer.exe
	cp $(ECAS_HOME)/itgclient/sitekit/engine/libpmutil.dll.nt $(TEMPKITDIR)/engine/libpmutil.dll
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/fetcustomize.bat $(TEMPKITDIR)/engine/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/createmst.vbs $(TEMPKITDIR)/engine/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/removetags.vbs $(TEMPKITDIR)/engine/
	mkdir -p $(TEMPKITDIR)/fragments/Global
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/fragments/Global/*.frg $(TEMPKITDIR)/fragments/Global/
	mkdir -p $(TEMPKITDIR)/templates
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/customize.lst $(TEMPKITDIR)/templates/
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/genmst.lst $(TEMPKITDIR)/templates/
	mkdir -p $(TEMPKITDIR)/templates/fetpackages/idts
	cp $(SRCMSI1).msi $(TEMPKITDIR)/templates/fetpackages/fet.msi
	cp $(ECAS_HOME)/itgclient/packager/win2k/common/templates/idts/fet/Property.idt $(TEMPKITDIR)/templates/fetpackages/idts/
	wzzip -r -P $(KITZIP).zip $(TEMPKITDIRNAME)


cd-install:
install-local: insertsig buildmsi zipkit
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(KITZIP).zip --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(KITZIP).zip $(LOCAL_INSTALL_DIR)/$(KITZIP).zip
	@$(ECHO) ""

install-ecas: insertsig buildmsi zipkit
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(KITZIP).zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(KITZIP).zip $(CDINSTALLHTMLDOCSDIR)/$(KITZIP).zip
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	rm -rf $(ISMFILE1)
	rm $(SIGNFILE)
	rm $(SIGNFILE).reg
	rm -rf $(TEMPKITDIR)
	rm $(KITZIP).zip

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(KITZIP).zip"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(KITZIP).zip
	@$(ECHO) ""

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(KITZIP).zip"
	$(RM) $(LOCAL_INSTALL_DIR)/$(KITZIP).zip
	@$(ECHO) ""


depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


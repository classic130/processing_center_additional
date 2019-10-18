
#       GNUmakefile 
#       Developed by Sameer Merchant
#	$Id: GNUmakefile,v 1.1.4.1 2001/10/04 01:11:37 smerchan Exp $
#

#
# make for : Signed vsdnotz.msi and vsnzpta.msi
#	     Ptav3.dll
#	     vsdnotz.dll
#            
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

ECAS_HOME=../../../../../..

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/win2k/dignot/msi
RELEASECLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/release
RELEASECLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/release
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
DEBUGCLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/debug
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGSERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/debug
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
CSPDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign

ISMFILE1=vsdnotz
ISMFILE2=vsnzpta
MSIFILE1=vsdnotz
MSIFILE2=vsnzpta
SIGNFILE=vscspsign
SRCMSI1=dnz/Release\ 1/DiskImages/DISK1/VeriSign\ Digital\ Notarization\ Client
SRCMSI2=dnzpta/Release\ 1/DiskImages/DISK1/VeriSign\ Personal\ Trust\ Agent

all: install-local

insertsig:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Inserting signature in $(ISMFILE2).ism"
	cp $(CSPDIR)/$(SIGNFILE) .
	$(ECAS_HOME)/itgclient/packager/win2k/common/scripts/convtoreg "$(SIGNFILE)"
	cscript $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/InsertSig.vbs "$(SIGNFILE).reg" "$(ISMFILE2).ism"
	
buildmsi:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Building $(MSIFILE1).msi and $(MSIFILE2).msi"
	ISCmdBld -p "$(ISMFILE1).ism"
	ISCmdBld -p "$(ISMFILE2).ism"

cd-install:
install-local: insertsig buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi and $(MSIFILE2).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	cp $(SRCMSI2).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE2).msi
	@$(ECHO) ""

debug-cd-install:
debug-install-local: insertsig buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi and $(MSIFILE2).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	cp $(SRCMSI2).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE2).msi
	@$(ECHO) ""

clean: uninstall-local uninstall-dot

uninstall-dot:
	-rm -rf $(ISMFILE1)
	-rm -rf $(ISMFILE2)
	-rm $(SIGNFILE)
	-rm $(SIGNFILE).reg

cd-uninstall:
uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(MSIFILE1).msi and $(MSIFILE2).msi"
	$(RM) $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	$(RM) $(LOCAL_INSTALL_DIR)/$(MSIFILE2).msi
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


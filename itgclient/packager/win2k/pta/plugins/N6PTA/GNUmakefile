#
#       GNUmakefile 
#       Developed by Sameer Merchant
#	$Id: GNUmakefile,v 1.1.4.2 2001/06/07 08:40:39 sbajaj Exp $
#

#
# make for : Signed N6ptav3.msi
#	     Ptav3.dll
#	     N6Pta.dll
#	     N6PTA.xpt
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

ECAS_HOME=../../../../../..

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/win2k/pta/msi
RELEASECLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/release
RELEASECLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/release
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
DEBUGCLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/debug
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGSERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
CSPDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign

ISMFILE1=N6ptav3
ISMFILE2=N6ptav3km
MSIFILE1=N6pta3
MSIFILE2=N6pta3km
SIGNFILE=vscspsign
SRCMSI1=N6ptav3/Release\ 1/DiskImages/DISK1/VeriSign\ Personal\ Trust\ Agent\ \(for\ Netscape\ 6.x\)
SRCMSI2=N6ptav3km/Release\ 1/DiskImages/DISK1/VeriSign\ Personal\ Trust\ Agent\ \(for\ Netscape\ 6.x\)

all: install-ecas install-local

insertsig:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Inserting signature in $(ISMFILE1).ism and $(ISMFILE2).ism"
	cp $(CSPDIR)/$(SIGNFILE) .
	$(ECAS_HOME)/itgclient/packager/win2k/common/scripts/convtoreg "$(SIGNFILE)"
	cscript $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/InsertSig.vbs "$(SIGNFILE).reg" "$(ISMFILE1).ism"
	cscript $(ECAS_HOME)/itgclient/packager/win2k/common/scripts/InsertSig.vbs "$(SIGNFILE).reg" "$(ISMFILE2).ism"
	
buildmsi:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Building $(MSIFILE1).msi and $(MSIFILE2).msi"
	ISCmdBld -p "$(ISMFILE1).ism"
	ISCmdBld -p "$(ISMFILE2).ism"

cd-install: 
install-ecas:
install-local: insertsig buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi and $(MSIFILE2).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	cp $(SRCMSI2).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE2).msi
	@$(ECHO) ""

debug-cd-install:
debug-install-ecas:
debug-install-local: insertsig buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi and $(MSIFILE2).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	cp $(SRCMSI2).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE2).msi
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	-rm -rf $(ISMFILE1)
	-rm -rf $(ISMFILE2)
	-rm $(SIGNFILE)
	-rm $(SIGNFILE).reg

cd-uninstall: 
uninstall-ecas:
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



#       GNUmakefile 
#       
#	$Id: GNUmakefile,v 1.1.4.5 2003/07/28 21:36:37 npaul Exp $
#

#
# make for : gsesetup60.msi
#	       VSGSE.dll
#	       VSGSEEXT.dll			
#              vsimport.dll
#	       VSCnfChk.dll
#              vssgnatb.dll	
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

ECAS_HOME=../../../../..

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


LOCAL_MSIDLL_DIR=$(ECAS_HOME)/itgclient/packager/win2k/exchange/activex/msidll
LOCAL_PACKEXCH_DIR=$(ECAS_HOME)/itgclient/packager/exchange
LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/win2k/exchange/msi
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

MSIFILE1=gse60setup
ISMFILE1=gse60setup
VSCFGCHK=VSCnfChk.dll
RELEASE_MSI=gse60setup

ENGLISH_SRCMSI=$(RELEASE_MSI)/English/Release1/DiskImages/DISK1/gse_english
DANISH_SRCMSI= $(RELEASE_MSI)/Danish/Release1/DiskImages/DISK1/gse_danish
DUTCH_SRCMSI=$(RELEASE_MSI)/Dutch/Release1/DiskImages/DISK1/gse_dutch
FRENCH_SRCMSI=$(RELEASE_MSI)/French/Release1/DiskImages/DISK1/gse_french
FINISH_SRCMSI=$(RELEASE_MSI)/Finish/Release1/DiskImages/DISK1/gse_finish
GERMAN_SRCMSI=$(RELEASE_MSI)/German/Release1/DiskImages/DISK1/gse_german
ITALIAN_SRCMSI=$(RELEASE_MSI)/Italian/Release1/DiskImages/DISK1/gse_italian
JAPANESE_SRCMSI=$(RELEASE_MSI)/Japanese/Release1/DiskImages/DISK1/gse_japanese
KOREAN_SRCMSI=$(RELEASE_MSI)/Korean/Release1/DiskImages/DISK1/gse_korean
PORTBRAZIL_SRCMSI=$(RELEASE_MSI)/Portuguese_brazil/Release1/DiskImages/DISK1/gse_portuguese_brazil
SIMPCHINESE_SRCMSI=$(RELEASE_MSI)/SimpChinese/Release1/DiskImages/DISK1/gse_simpchinese
SPANISH_SRCMSI=$(RELEASE_MSI)/Spanish/Release1/DiskImages/DISK1/gse_spanish
SWEDISH_SRCMSI=$(RELEASE_MSI)/Swedish/Release1/DiskImages/DISK1/gse_swedish
TRADCHINESE_SRCMSI=$(RELEASE_MSI)/TradChinese/Release1/DiskImages/DISK1/gse_tradchinese

release:all

all: install-local
buildmsi:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Building $(MSIFILE1).msi" 
	mkdir -p $(LOCAL_MSIDLL_DIR)
	cp $(RELEASECLIENTLIBDIR)/*.dll $(LOCAL_MSIDLL_DIR)
	cp $(LOCAL_PACKEXCH_DIR)/$(VSCFGCHK) $(LOCAL_MSIDLL_DIR)
	ISCmdBld -p "$(ISMFILE1).ism" -a English
	ISCmdBld -p "$(ISMFILE1).ism" -a Danish
	ISCmdBld -p "$(ISMFILE1).ism" -a Dutch
	ISCmdBld -p "$(ISMFILE1).ism" -a French
	ISCmdBld -p "$(ISMFILE1).ism" -a Finish
	ISCmdBld -p "$(ISMFILE1).ism" -a German
	ISCmdBld -p "$(ISMFILE1).ism" -a Italian
	ISCmdBld -p "$(ISMFILE1).ism" -a Japanese
	ISCmdBld -p "$(ISMFILE1).ism" -a Korean
	ISCmdBld -p "$(ISMFILE1).ism" -a "Portuguese_brazil"
	ISCmdBld -p "$(ISMFILE1).ism" -a SimpChinese
	ISCmdBld -p "$(ISMFILE1).ism" -a Spanish
	ISCmdBld -p "$(ISMFILE1).ism" -a Swedish
	ISCmdBld -p "$(ISMFILE1).ism" -a TradChinese

cd-install:
install-local:buildmsi 
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)

	
	cp $(ENGLISH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(DANISH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(DUTCH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(FRENCH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(FINISH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(GERMAN_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(ITALIAN_SRCMSI).msi $(LOCAL_INSTALL_DIR)/

	cp $(JAPANESE_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(KOREAN_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(PORTBRAZIL_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(SIMPCHINESE_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(SPANISH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(SWEDISH_SRCMSI).msi $(LOCAL_INSTALL_DIR)/
	cp $(TRADCHINESE_SRCMSI).msi $(LOCAL_INSTALL_DIR)/


	wzzip ../msi/gse_alllang.zip @gse_alllang.lst

	@$(ECHO) ""

debug-cd-install:
debug-install-local: 
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi  --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	@$(ECHO) ""

clean: uninstall-local uninstall-dot

uninstall-dot:
	-rm -rf $(ENGLISH_SRCMSI).msi 
	-rm -rf $(DANISH_SRCMSI).msi 
	-rm -rf $(DUTCH_SRCMSI).msi 
	-rm -rf $(FRENCH_SRCMSI).msi 
	-rm -rf $(FINISH_SRCMSI).msi 
	-rm -rf $(GERMAN_SRCMSI).msi 
	-rm -rf $(ITALIAN_SRCMSI).msi 

	-rm -rf $(JAPANESE_SRCMSI).msi 
	-rm -rf $(KOREAN_SRCMSI).msi 
	-rm -rf $(PORTBRAZIL_SRCMSI).msi 
	-rm -rf $(SIMPCHINESE_SRCMSI).msi 
	-rm -rf $(SPANISH_SRCMSI).msi 
	-rm -rf $(SWEDISH_SRCMSI).msi 
	-rm -rf $(TRADCHINESE_SRCMSI).msi 
	
	-rm -rf $(LOCAL_INSTALL_DIR)/*.msi 
	-rm -rf $(LOCAL_INSTALL_DIR)/*.zip 
		
cd-uninstall:
uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(MSIFILE1).msi"
	$(RM) $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


#       GNUmakefile 
#       Developed by Ajay Jayaram
#	$Id: GNUmakefile,v 1.2.10.1 2005/02/15 20:25:42 eleung Exp $
#

#
# make for : Signed ptav3-inav.msi
#	     Ptav3.dll
#                 Install.dll             - inav intall dll
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

ECAS_HOME=../../../../

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/pta-navi/msi
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
NAVIBINDIR=I:/NaviClient/bin
NAVILOCALBINDIR=Files
PTADIR=../../pta/activex/pta3
OTHERDIR=../../pta/other


ISMFILE1=PTA-Install-100B
MSIFILE1=alllang
SIGNFILE=vscspsign
#SRCMSI1=ptav3-inav/ptav3/Release\ 1/DiskImages/DISK1/VeriSign\ Personal\ Trust\ Agent
SRCMSI_CS=PTA-Install-100B/Chinese\ Simplified/Release/DiskImages/DISK1/pta_chinesesimp
SRCMSI_CT=PTA-Install-100B/Chinese\ Traditional/Release/DiskImages/DISK1/pta_chinesetrad
SRCMSI_DAN=PTA-Install-100B/Danish/Release/DiskImages/DISK1/pta_danish
SRCMSI_DUTCH=PTA-Install-100B/Dutch/Release/DiskImages/DISK1/pta_dutch
SRCMSI_FRN=PTA-Install-100B/French/Release/DiskImages/DISK1/pta_french
SRCMSI_GER=PTA-Install-100B/German/Release/DiskImages/DISK1/pta_german
SRCMSI_IT=PTA-Install-100B/Italian/Release/DiskImages/DISK1/pta_italian
SRCMSI_JAP=PTA-Install-100B/Japanese/Release/DiskImages/DISK1/pta_japanese
SRCMSI_KOR=PTA-Install-100B/Korean/Release/DiskImages/DISK1/pta_korean
SRCMSI_POR=PTA-Install-100B/Portuguese/Release/DiskImages/DISK1/pta_portuguese
SRCMSI_SPN=PTA-Install-100B/Spanish/Release/DiskImages/DISK1/pta_spanish
SRCMSI_SW=PTA-Install-100B/Swedish/Release/DiskImages/DISK1/pta_swedish
SRCMSI_FN=PTA-Install-100B/Finnish/Release/DiskImages/DISK1/pta_finnish
SRCMSI_ENG=PTA-Install-100B/English/Release/DiskImages/DISK1/pta_english

DLLNAME1=Ptav3
DLLNAME2=VS_IBMTSS
DLLNAME3=VS_INFYTSS


all: install-local

copybinaries:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Copying components"
	mkdir -p $(NAVILOCALBINDIR)
	cp $(CSPDIR)/$(SIGNFILE) $(NAVILOCALBINDIR)
	cp $(PTADIR)/$(DLLNAME1).dll  $(NAVILOCALBINDIR)
	cp $(NAVIBINDIR)/*  $(NAVILOCALBINDIR)
	cp $(OTHERDIR)/*.dll $(NAVILOCALBINDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll $(NAVILOCALBINDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll $(NAVILOCALBINDIR)
	

buildmsi:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Building $(MSIFILE1).msi"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Chinese Simplified"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Chinese Traditional"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Danish"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Dutch"
	ISCmdBld -p "$(ISMFILE1).ism" -a "French"
	ISCmdBld -p "$(ISMFILE1).ism" -a "German"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Italian"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Japanese"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Korean"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Portuguese"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Spanish"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Swedish"
	ISCmdBld -p "$(ISMFILE1).ism" -a "Finnish"
	ISCmdBld -p "$(ISMFILE1).ism" -a "English"


cd-install:
install-local: copybinaries buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI_CS).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_CT).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_DAN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_DUTCH).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_FRN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_GER).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_IT).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_JAP).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_KOR).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_POR).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_SPN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_SW).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_FN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_ENG).msi $(LOCAL_INSTALL_DIR)/
	@$(ECHO) ""

debug-cd-install:
debug-install-local: copybinaries buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi  --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI_CS).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_CT).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_DAN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_DUTCH).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_FRN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_GER).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_IT).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_JAP).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_KOR).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_POR).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_SPN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_SW).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_FN).msi $(LOCAL_INSTALL_DIR)/
	cp $(SRCMSI_ENG).msi $(LOCAL_INSTALL_DIR)/
	@$(ECHO) ""

clean: uninstall-local

cd-uninstall:
uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(MSIFILE1).msi"
	$(RM) $(LOCAL_INSTALL_DIR)/*.msi
	$(RM) -r PTA-Install-100B	
	@$(ECHO) "$(ME): Uninstalling binaries"
	$(RM) -r $(NAVILOCALBINDIR)
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.




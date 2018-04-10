#       GNUmakefile 
#       Developed by Ajay Jayaram
#	$Id: GNUmakefile,v 1.1.4.2 2003/06/11 21:00:24 ajayaram Exp $
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


LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/pta-updater/msi
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
NAVIBINARIESDIR=I:/NaviClient/binaries
NAVILOCALBINDIR=Installer/bin
NAVILOCALBINARIESDIR=Installer/Installer/binaries/PTA
PTADIR=../../pta/activex/pta3


ISMFILE1=ptav3-inav
MSIFILE1=ptav3-updater
SIGNFILE=vscspsign
SRCMSI1=ptav3-inav/ptav3/Release\ 1/DiskImages/DISK1/VeriSign\ Personal\ Trust\ Agent
DLLNAME1=Ptav3


all: install-local

copybinaries:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Copying components"
	cp $(CSPDIR)/$(SIGNFILE) Installer/bin
	cp $(PTADIR)/$(DLLNAME1).dll  $(NAVILOCALBINDIR)
	cp $(NAVIBINDIR)/*  $(NAVILOCALBINDIR)
	cp $(NAVIBINARIESDIR)/* $(NAVILOCALBINARIESDIR)
	

buildmsi:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Building $(MSIFILE1).msi"
	ISCmdBld -p "$(ISMFILE1).ism"

cd-install:
install-local: copybinaries buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	@$(ECHO) ""

debug-cd-install:
debug-install-local: copybinaries buildmsi
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(MSIFILE1).msi  --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(SRCMSI1).msi $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	@$(ECHO) ""

clean: uninstall-local

cd-uninstall:
uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(MSIFILE1).msi"
	$(RM) $(LOCAL_INSTALL_DIR)/$(MSIFILE1).msi
	rm -r ptav3-inav	
	@$(ECHO) "$(ME): Uninstalling binaries"
	-rm $(NAVILOCALBINDIR)/*
	-rm $(NAVILOCALBINARIESDIR)/*
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.




#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.12.52.1 2003/05/16 20:53:58 sgoginen Exp $
#

ECAS_HOME = ../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SPECIAL_winnt_SUBDIRS = exchange pta fet dignot win2k pta-updater
SPECIAL_sparc_SUBDIRS = local-install
SPECIAL_hpux_SUBDIRS = local-install

SUBDIRS = $(SPECIAL_$(TARCH)_SUBDIRS)

include $(ECAS_RULES_DIR)/directory.cfg


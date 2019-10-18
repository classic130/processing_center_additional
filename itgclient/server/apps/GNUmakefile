#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.182.1 2000/07/07 20:52:54 mwilson Exp $
#

ECAS_HOME = ../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SPECIAL_winnt_DIRS = exchange

SUBDIRS = cpm pta $(SPECIAL_$(TARCH)_DIRS)


include $(ECAS_RULES_DIR)/directory.cfg


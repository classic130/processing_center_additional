#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.7.150.1 2000/07/07 22:55:06 mwilson Exp $
#

ECAS_HOME = ../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SPECIAL_winnt_SUBDIRS = modules apps

SUBDIRS = $(SPECIAL_$(TARCH)_SUBDIRS)

include $(ECAS_RULES_DIR)/directory.cfg


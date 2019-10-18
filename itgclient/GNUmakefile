#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.5 2000/07/07 23:18:52 mwilson Exp $
#

ECAS_HOME = ..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SPECIAL_winnt_DIRS = common client

SUBDIRS = $(SPECIAL_$(TARCH)_DIRS) server sitekit packager 

include $(ECAS_RULES_DIR)/directory.cfg


#	GNUmakefile 
#       Developed by Abhay Ranade
#		Modified  by Narinder
#	$Id: GNUmakefile,v 1.2.444.1 2001/09/12 17:27:30 npaul Exp $
#

ECAS_HOME = ../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SUBDIRS = simder utils GMemMgmt scmodules 


include $(ECAS_RULES_DIR)/directory.cfg


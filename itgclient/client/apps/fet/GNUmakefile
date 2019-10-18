#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.18.1 2000/04/21 02:32:53 wilkal Exp $
#

ECAS_HOME = ../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SUBDIRS = chpasswd vslog vsfe setup


include $(ECAS_RULES_DIR)/directory.cfg

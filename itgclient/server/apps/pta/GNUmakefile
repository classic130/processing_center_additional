#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.4.22.1 2001/10/05 03:49:47 sbajaj Exp $
#

ECAS_HOME = ../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif
SPECIAL_winnt_SUBDIRS = comvsssc

SUBDIRS = bin config examples include tools source certcache $(SPECIAL_$(TARCH)_SUBDIRS)


include $(ECAS_RULES_DIR)/directory.cfg


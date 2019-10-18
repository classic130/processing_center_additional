#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.2 2001/06/07 08:40:33 sbajaj Exp $
#

ECAS_HOME = ../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SUBDIRS = activex plugins msi


include $(ECAS_RULES_DIR)/directory.cfg


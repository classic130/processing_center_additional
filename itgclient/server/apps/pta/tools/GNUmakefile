#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.1 2000/07/25 08:12:56 mwilson Exp $
#

ECAS_HOME = ../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SUBDIRS = VerifySignature


include $(ECAS_RULES_DIR)/directory.cfg


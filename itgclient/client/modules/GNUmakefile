#	GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.3.10.1 2005/02/15 20:23:22 eleung Exp $
#

ECAS_HOME = ../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SUBDIRS = BSafeLite ProtectedStorage VS_IBMTSS VS_INFYTSS


include $(ECAS_RULES_DIR)/directory.cfg


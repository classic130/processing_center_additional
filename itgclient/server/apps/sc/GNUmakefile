#	GNUmakefile 
#       Developed by Narinder
#	$Id: GNUmakefile,v 1.1.2.2 2001/11/01 21:36:58 rpandran Exp $
#

ECAS_HOME = ../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SUBDIRS = vsprs policymodule vsprsauth vsprscgi


include $(ECAS_RULES_DIR)/directory.cfg


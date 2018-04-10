#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.3.10.1 2005/02/17 09:09:13 ppassanha Exp $
#

ECAS_HOME = ../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg


ifeq ($(CISCO), 1)
SPECIAL_sparc_DIRS = cisco
endif

SPECIAL_sparc_DIRS = sparc
SPECIAL_winnt_DIRS = winnt
SPECIAL_hpux_DIRS = hpux
SPECIAL_aix_DIRS = aix
# Begin Change : Fix for CR30756, Porting to Linux
SPECIAL_linux_DIRS = linux
# End Change : Fix for CR30756, Porting to Linux

SUBDIRS = $(SPECIAL_$(TARCH)_DIRS)


include $(ECAS_RULES_DIR)/directory.cfg


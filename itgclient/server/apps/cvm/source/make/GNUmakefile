#       GNUmakefile
#       Developed by Abhay Ranade
#       $Id: GNUmakefile,v 1.4.2.1.2.1 2006/12/26 14:11:10 schenna Exp $
#

ECAS_HOME = ../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/directory.cfg

SPECIAL_sparc_SUBDIRS=mod_vsval mod_vsval_2 mod_vsval_ibm mod_vsval_ibm_2 libvsvaln
ifeq ($(HPVER),"B.11.11")
SPECIAL_hpux_SUBDIRS=mod_vsval_2
endif
ifeq ($(HPVER),"B.11.23")
SPECIAL_hpux_SUBDIRS=mod_vsval_2
endif
ifeq ($(HPVER),"B.11.00")
SPECIAL_hpux_SUBDIRS=mod_vsval mod_vsval_2 mod_vsval_ibm mod_vsval_ibm_2 libvsvaln
endif
SPECIAL_winnt_SUBDIRS=libvsvalm libvsvaln
SPECIAL_aix_SUBDIRS=mod_vsval mod_vsval_2 mod_vsval_ibm mod_vsval_ibm_2 libvsvaln
SPECIAL_linux_SUBDIRS=mod_vsval mod_vsval_2 libvsvaln

SUBDIRS = $(SPECIAL_$(TARCH)_SUBDIRS)

include $(ECAS_RULES_DIR)/directory.cfg


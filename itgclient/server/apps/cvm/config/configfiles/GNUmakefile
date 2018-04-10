#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.66.1 2002/10/17 00:14:33 psingal Exp $
#

ECAS_HOME=../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRIIS=$(CDINSTALL)/../server/cvm/iis/config
DESTDIRNS=$(CDINSTALL)/../server/cvm/netscape/config
DESTDIRSTRONGHOLD=$(CDINSTALL)/../server/cvm/stronghold/config

all: cd-install
install-local: cd-install
install-ecas: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> "
	mkdir -p $(DESTDIRNS)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   cp trustlist.cfg $(DESTDIRNS)/val_config.txt; \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   cp trustlist.cfg $(DESTDIRSTRONGHOLD)/val_config.txt; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   mkdir -p $(DESTDIRIIS); \
	   cp trustlist.cfg $(DESTDIRNS)/val_config.txt; \
	   cp trustlist.cfg $(DESTDIRIIS)/val_config.txt; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   cp trustlist.cfg $(DESTDIRNS)/val_config.txt; \
	   cp trustlist.cfg $(DESTDIRSTRONGHOLD)/val_config.txt; \
	fi;
	@if [ "$(TARCH)" = "aix" ]; \
	then \
	   cp trustlist.cfg $(DESTDIRNS)/val_config.txt; \
	fi;
	@$(ECHO) ""

uninstall-local: clean
uninstall-ecas: clean
clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(RM) $(DESTDIRNS)/val_config.txt; \
	   $(RM) $(DESTDIRSTRONGHOLD)/val_config.txt; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   $(RM) $(DESTDIRNS)/val_config.txt; \
	   $(RM) $(DESTDIRIIS)/val_config.txt; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   $(RM) $(DESTDIRNS)/val_config.txt; \
	   $(RM) $(DESTDIRSTRONGHOLD)/val_config.txt; \
	fi;
	@if [ "$(TARCH)" = "aix" ]; \
	then \
	   $(RM) $(DESTDIRNS)/val_config.txt; \
	   $(RM) $(DESTDIRSTRONGHOLD)/val_config.txt; \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

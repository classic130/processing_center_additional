#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.66.1 2002/10/17 00:14:28 psingal Exp $
#

ECAS_HOME=../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRIIS=$(CDINSTALL)/../server/cvm/iis/certcache
DESTDIRNS=$(CDINSTALL)/../server/cvm/netscape/certcache
DESTDIRSTRONGHOLD=$(CDINSTALL)/../server/cvm/stronghold/certcache

all: cd-install
install-local: cd-install
install-ecas: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> "
	mkdir -p $(DESTDIRNS)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRNS); \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRSTRONGHOLD); \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   mkdir -p $(DESTDIRIIS); \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRIIS); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRIIS); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRSTRONGHOLD); \
	fi;
	@if [ "$(TARCH)" = "aix" ]; \
	then \
	   $(INSTALL_SH) -m 644 *.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 ca-list.txt $(DESTDIRNS); \
	fi;
	@$(ECHO) ""

uninstall-local: clean
uninstall-ecas: clean
clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRSTRONGHOLD); \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRIIS); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRSTRONGHOLD); \
	fi;
	@if [ "$(TARCH)" = "aix" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRSTRONGHOLD); \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

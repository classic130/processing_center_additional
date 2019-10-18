#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.22.1 2001/10/05 03:49:48 sbajaj Exp $
#

ECAS_HOME=../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRIIS=$(CDINSTALL)/../server/pta/iis/certcache
DESTDIRNS=$(CDINSTALL)/../server/pta/netscape/certcache
DESTDIRSM=$(CDINSTALL)/../server/pta/siteminder/certcache
DESTDIRSTRONGHOLD=$(CDINSTALL)/../server/pta/stronghold/certcache
DESTDIRTEMPLATES=$(CDINSTALL)/templates/pta/certcache

CVMCERTCACHE=../../cvm/config/certcache

all: cd-install
install-local: cd-install
install-ecas: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> "
	mkdir -p $(DESTDIRNS)
	mkdir -p $(DESTDIRTEMPLATES)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRTEMPLATES); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRTEMPLATES); \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRSTRONGHOLD); \
	   mkdir -p $(DESTDIRSM); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRSM); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRSM); \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   mkdir -p $(DESTDIRIIS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRIIS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRIIS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRTEMPLATES); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRTEMPLATES); \
	   mkdir -p $(DESTDIRSM); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRSM); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRSM); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRNS); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRSTRONGHOLD); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/*.509 $(DESTDIRTEMPLATES); \
	   $(INSTALL_SH) -m 644 $(CVMCERTCACHE)/ca-list.txt $(DESTDIRTEMPLATES); \
	fi;
	@$(ECHO) ""

uninstall-local: clean
uninstall-ecas: clean
clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRSTRONGHOLD); \
	   rm -rf $(DESTDIRTEMPLATES); \
	   rm -rf $(DESTDIRSM); \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRIIS); \
	   rm -rf $(DESTDIRTEMPLATES); \
	   rm -rf $(DESTDIRSM); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   rm -rf $(DESTDIRNS); \
	   rm -rf $(DESTDIRSTRONGHOLD); \
	   rm -rf $(DESTDIRTEMPLATES); \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

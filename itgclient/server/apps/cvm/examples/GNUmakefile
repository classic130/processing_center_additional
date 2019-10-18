#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.3.8.1 2002/11/11 19:53:57 psingal Exp $
#

ECAS_HOME=../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/../server/cvm/examples
IIS_BIN_DIR=$(CDINSTALL)/../server/cvm/iis/bin

all: cd-install
install-local: cd-install
install-ecas: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR) "
	mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 555 certStatus.csh $(DESTDIR)/certStatus.csh
	@$(INSTALL_SH) -m 555 certStatus.pl $(DESTDIR)/certStatus.pl
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   @$(ECHO) "$(ME):Installing CVM Registration Script for ISA --> $(IIS_BIN_DIR)" \
	   mkdir -p $(IIS_BIN_DIR); \
	   $(INSTALL_SH) -m 555 cvmRegister.vbs $(IIS_BIN_DIR); \
	fi;
	@$(ECHO) ""

uninstall-local: clean
uninstall-ecas: clean
clean:
	$(RM) -rf $(DESTDIR)
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

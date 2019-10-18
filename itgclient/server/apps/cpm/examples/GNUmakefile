#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.20.2 2001/10/06 02:56:27 sbajaj Exp $
#

ECAS_HOME=../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRCGI=$(CDINSTALL)/../server/cpm/examples/cgi
DESTDIRAPI=$(CDINSTALL)/../server/cpm/examples/api

all: cd-install
install-local: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIRCGI)
	mkdir -p $(DESTDIRAPI)
	cp cdrmain.c $(DESTDIRAPI)
	cp egNsapiCDR.c $(DESTDIRAPI)
	cp egCDR.perl $(DESTDIRCGI)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   cp egCDR.sh $(DESTDIRCGI); \
	   cp egCDR.csh $(DESTDIRCGI); \
	   chmod 555 $(DESTDIRCGI)/*; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   cp egCDR.sh $(DESTDIRCGI); \
	   cp egCDR.csh $(DESTDIRCGI); \
	   chmod 555 $(DESTDIRCGI)/*; \
	fi;
	@$(ECHO) ""

clean:
	$(RM) -rf $(DESTDIRCGI)
	$(RM) -rf $(DESTDIRAPI)
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

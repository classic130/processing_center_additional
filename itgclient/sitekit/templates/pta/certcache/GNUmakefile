#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.3.468.2 2006/11/18 09:39:14 schenna Exp $
#

ECAS_HOME=../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/templates/pta/certcache

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 644 onsite_sub_demo.509 $(DESTDIR)
	@$(INSTALL_SH) -m 644 PCA2ssv4.509 $(DESTDIR)
	@$(INSTALL_SH) -m 644 VS_class_2_onsite_individual_ca_2.509 $(DESTDIR)
	@$(ECHO) ""

clean:
	$(RM) -r $(DESTDIR)
depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

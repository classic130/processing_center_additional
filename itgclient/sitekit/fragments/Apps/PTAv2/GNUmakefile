#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.722.2 2006/11/18 09:38:59 schenna Exp $
#

ECAS_HOME=../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/fragments/VSApps/Apps/PTAv2

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 644 *.frg $(DESTDIR)
	@$(ECHO) ""

clean:
	$(RM) -r $(DESTDIR)

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

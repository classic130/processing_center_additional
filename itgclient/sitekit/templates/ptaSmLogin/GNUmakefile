#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.204.2 2006/11/18 09:39:18 schenna Exp $
#

ECAS_HOME=../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/templates/ptaSmLogin

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 644 *.fcc $(DESTDIR)
	@$(ECHO) ""

clean:
	$(RM) -r $(DESTDIR)
depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

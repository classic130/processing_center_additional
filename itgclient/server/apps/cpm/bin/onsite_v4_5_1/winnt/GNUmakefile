#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.156.1 2001/04/02 20:48:35 sbajaj Exp $
#

ECAS_HOME=../../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/../server/cpm/bin

all: cd-install
install-local: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	cp cdr.lib $(DESTDIR)
	cp cdr.dll $(DESTDIR)
	cp cdrN3.dll $(DESTDIR)
	@$(ECHO) ""

clean:
	$(RM) -rf $(DESTDIR)

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

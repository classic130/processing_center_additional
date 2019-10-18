#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.162.1 2001/03/27 21:52:56 sbajaj Exp $
#

ECAS_HOME=../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/../server/pta/include
SRCDIR=../source

all: cd-install
install-local: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	cp $(SRCDIR)/ssc_api.h $(DESTDIR)
	@$(ECHO) ""

clean:
	$(RM) -rf $(DESTDIR)

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

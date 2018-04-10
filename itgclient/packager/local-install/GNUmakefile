#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.118.1 2001/02/14 18:59:06 usha Exp $
#

ECAS_HOME=../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/templates/htmldocs/VSApps

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   cp *.cab $(DESTDIR); \
           cp *.exe $(DESTDIR); \
	   cp *.jar $(DESTDIR); \
	   cp *.zip $(DESTDIR); \
           cp *.xpi $(DESTDIR); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
           cp *.cab $(DESTDIR); \
           cp *.exe $(DESTDIR); \
           cp *.jar $(DESTDIR); \
           cp *.zip $(DESTDIR); \
           cp *.xpi $(DESTDIR); \
	fi;
	@$(ECHO) ""

clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(RM) $(DESTDIR)/*.cab; \
	   $(RM) $(DESTDIR)/*.exe; \
	   $(RM) $(DESTDIR)/*.zip; \
	   $(RM) $(DESTDIR)/*.jar; \
           $(RM) $(DESTDIR)/*.xpi; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   $(RM) $(DESTDIR)/*.cab; \
	   $(RM) $(DESTDIR)/*.exe; \
           $(RM) $(DESTDIR)/*.jar; \
           $(RM) $(DESTDIR)/*.zip; \
           $(RM) $(DESTDIR)/*.xpi; \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

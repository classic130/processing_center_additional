#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.9.176.2 2006/11/18 09:39:03 schenna Exp $
#

ECAS_HOME=../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/templates/htmldocs/VSApps
DESTDIR_TEMPLATES=$(CDINSTALL)/templates

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	cp *.htm $(DESTDIR)
	cp xenroll.cab $(DESTDIR)
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   cp ../vsapps_nt.lst $(DESTDIR_TEMPLATES); \
           cp ../sitekit_pta_nt.lst $(DESTDIR_TEMPLATES); \
           cp ../sitekit_ptaSm_nt.lst $(DESTDIR_TEMPLATES); \
	else \
	   cp ../vsapps_unix.lst $(DESTDIR_TEMPLATES); \
           cp ../sitekit_pta_unix.lst $(DESTDIR_TEMPLATES); \
           cp ../sitekit_ptaSm_unix.lst $(DESTDIR_TEMPLATES); \
	fi;
	@$(ECHO) ""

clean:
	$(RM) -r $(DESTDIR)
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   $(RM) $(DESTDIR_TEMPLATES)/vsapps_nt.lst ; \
           $(RM) $(DESTDIR_TEMPLATES)/sitekit_pta_nt.lst; \
           $(RM) $(DESTDIR_TEMPLATES)/sitekit_ptaSm_nt.lst; \
	else \
	   $(RM) $(DESTDIR_TEMPLATES)/vsapps_unix.lst; \
           $(RM) $(DESTDIR_TEMPLATES)/sitekit_pta_unix.lst; \
           $(RM) $(DESTDIR_TEMPLATES)/sitekit_ptaSm_unix.lst; \
	fi;

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.11.46.2 2006/11/18 09:38:57 schenna Exp $
#

ECAS_HOME=../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIR=$(CDINSTALL)/engine

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIR)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   cp vsainst-sun $(DESTDIR); \
	   chmod a+x $(DESTDIR)/vsainst-sun; \
           cp pta-install-sun $(DESTDIR); \
	   chmod a+x $(DESTDIR)/pta-install-sun; \
           cp ptaSm-install-sun $(DESTDIR); \
	   chmod a+x $(DESTDIR)/ptaSm-install-sun; \
	   cp suncustomizer.exe $(DESTDIR)/customizer.exe; \
	   chmod a+x $(DESTDIR)/customizer.exe; \
	   cp libpmutil.so.sun $(DESTDIR)/libpmutil.so; \
	   chmod a+x $(DESTDIR)/libpmutil.so; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   cp *.bat $(DESTDIR); \
	   cp ntcustomizer.exe $(DESTDIR)/customizer.exe; \
	   cp libpmutil.dll.nt $(DESTDIR)/libpmutil.dll; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   cp vsainst-hpux $(DESTDIR); \
	   chmod a+x $(DESTDIR)/vsainst-hpux; \
	   cp pta-install-hpux $(DESTDIR); \
	   chmod a+x $(DESTDIR)/pta-install-hpux; \
	   cp hpuxcustomizer.exe $(DESTDIR)/customizer.exe; \
	   chmod a+x $(DESTDIR)/customizer.exe; \
	   cp libpmutil.sl.hpux $(DESTDIR)/libpmutil.sl; \
	   chmod a+x $(DESTDIR)/libpmutil.sl; \
	fi;
	@if [ "$(TARCH)" = "aix" ]; \
	then \
	   cp vsainst-aix $(DESTDIR); \
	   chmod a+x $(DESTDIR)/vsainst-aix; \
	   cp pta-install-aix $(DESTDIR); \
	   chmod a+x $(DESTDIR)/pta-install-aix; \
	   cp aixcustomizer.exe $(DESTDIR)/customizer.exe; \
	   chmod a+x $(DESTDIR)/customizer.exe; \
	   cp libpmutil.so.aix $(DESTDIR)/libpmutil.so; \
	   chmod a+x $(DESTDIR)/libpmutil.so; \
	fi;
	@$(ECHO) ""

clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(RM) $(DESTDIR)/vsainst-sun; \
	   $(RM) $(DESTDIR)/pta-install-sun; \
	   $(RM) $(DESTDIR)/ptaSm-install-sun; \
	   $(RM) $(DESTDIR)/customizer.exe; \
	   $(RM) $(DESTDIR)/libpmutil.so; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   $(RM) $(DESTDIR)/*.bat; \
           $(RM) $(DESTDIR)/customizer.exe; \
           $(RM) $(DESTDIR)/libpmutil.dll; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   $(RM) $(DESTDIR)/vsainst-hpux; \
	   $(RM) $(DESTDIR)/pta-install-hpux; \
           $(RM) $(DESTDIR)/customizer.exe; \
           $(RM) $(DESTDIR)/libpmutil.sl; \
	fi;
	@if [ "$(TARCH)" = "aix" ]; \
	then \
	   $(RM) $(DESTDIR)/vsainst-aix; \
	   $(RM) $(DESTDIR)/pta-install-aix; \
	   $(RM) $(DESTDIR)/customizer.exe; \
	   $(RM) $(DESTDIR)/libpmutil.so; \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

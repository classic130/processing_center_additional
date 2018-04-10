#       GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.3.24.2 2001/10/06 21:57:05 sbajaj Exp $
#

ECAS_HOME=../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRIIS=$(CDINSTALL)/../server/pta/iis/config
DESTDIRNS=$(CDINSTALL)/../server/pta/netscape/config
DESTDIRSM=$(CDINSTALL)/../server/pta/siteminder/config
DESTDIRSTRONGHOLD=$(CDINSTALL)/../server/pta/stronghold/config
DESTDIRTEMPLATES=$(CDINSTALL)/templates/pta/config

all: cd-install
install-local: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIRNS)
	mkdir -p $(DESTDIRTEMPLATES)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   mkdir -p $(DESTDIRSM); \
	   cp obj.conf.sparc $(DESTDIRNS)/obj.conf; \
	   cp options.txt.sparc $(DESTDIRNS)/options.txt; \
	   cp trustlist.cfg $(DESTDIRNS)/rsaverify.cfg; \
	   cp httpd.conf.sparc $(DESTDIRSTRONGHOLD)/httpd.conf; \
	   cp options.txt.sparc $(DESTDIRSTRONGHOLD)/options.txt; \
           cp trustlist.cfg $(DESTDIRSTRONGHOLD)/rsaverify.cfg; \
	   cp options.txt.sparc $(DESTDIRTEMPLATES)/options.txt; \
	   cp trustlist.cfg $(DESTDIRTEMPLATES)/rsaverify.cfg; \
	   cp sm-opts.txt.sparc $(DESTDIRSM)/sm-opts.txt; \
	   cp trustlist.cfg $(DESTDIRSM)/rsaverify.cfg; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   mkdir -p $(DESTDIRIIS); \
	   mkdir -p $(DESTDIRSM); \
	   cp obj.conf.winnt $(DESTDIRNS)/obj.conf; \
	   cp options.txt.winnt $(DESTDIRNS)/options.txt; \
	   cp trustlist.cfg $(DESTDIRNS)/rsaverify.cfg; \
	   cp options.txt.winnt $(DESTDIRTEMPLATES)/options.txt; \
	   cp trustlist.cfg $(DESTDIRTEMPLATES)/rsaverify.cfg; \
	   cp iis_opts.txt $(DESTDIRTEMPLATES); \
	   cp iis_opts.txt $(DESTDIRIIS); \
	   cp trustlist.cfg $(DESTDIRIIS)/rsaverify.cfg; \
	   cp sm-opts.txt.winnt $(DESTDIRSM)/sm-opts.txt; \
	   cp trustlist.cfg $(DESTDIRSM)/rsaverify.cfg; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   cp obj.conf.hpux $(DESTDIRNS)/obj.conf; \
	   cp options.txt.hpux $(DESTDIRNS)/options.txt; \
	   cp trustlist.cfg $(DESTDIRNS)/rsaverify.cfg; \
           cp httpd.conf.hpux $(DESTDIRSTRONGHOLD)/httpd.conf; \
           cp options.txt.hpux $(DESTDIRSTRONGHOLD)/options.txt; \
           cp trustlist.cfg $(DESTDIRSTRONGHOLD)/rsaverify.cfg; \
	   cp options.txt.hpux $(DESTDIRTEMPLATES)/options.txt; \
	   cp trustlist.cfg $(DESTDIRTEMPLATES)/rsaverify.cfg; \
	fi;
	@$(ECHO) ""

clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
	   $(RM) -rf $(DESTDIRSTRONGHOLD); \
	   $(RM) $(DESTDIRTEMPLATES)/options.txt; \
	   $(RM) $(DESTDIRTEMPLATES)/rsaverify.cfg; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
	   $(RM) -rf $(DESTDIRIIS); \
	   $(RM) -rf $(DESTDIRSM); \
	   $(RM) $(DESTDIRTEMPLATES)/options.txt; \
	   $(RM) $(DESTDIRTEMPLATES)/rsaverify.cfg; \
	   $(RM) $(DESTDIRTEMPLATES)/iis_opts.txt; \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
           $(RM) -rf $(DESTDIRSTRONGHOLD); \
	   $(RM) -rf $(DESTDIRSM); \
	   $(RM) $(DESTDIRTEMPLATES)/options.txt; \
	   $(RM) $(DESTDIRTEMPLATES)/rsaverify.cfg; \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

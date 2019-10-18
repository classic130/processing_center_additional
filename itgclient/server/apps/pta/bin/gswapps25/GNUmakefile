#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.4.2 2001/04/18 17:51:30 bzou Exp $
#

ECAS_HOME=../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRIIS=$(CDINSTALL)/../server/pta/iis/bin
DESTDIRNS=$(CDINSTALL)/../server/pta/netscape/bin
DESTDIRSTRONGHOLD=$(CDINSTALL)/../server/pta/stronghold/bin
DESTDIRSIGNING=$(CDINSTALL)/templates/pta/cgi-bin
BINDIR=../gswapps20

all: cd-install
install-local: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIRNS)
	mkdir -p $(DESTDIRSIGNING)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   cp $(BINDIR)/libldapssl30.so $(DESTDIRNS); \
           cp $(BINDIR)/libldapssl30.so $(DESTDIRSTRONGHOLD); \
	   cp $(BINDIR)/sophialite.exe.sparc $(DESTDIRSIGNING)/sophialite.exe; \
	   chmod a+x $(DESTDIRSIGNING)/sophialite.exe; \
	   cp $(BINDIR)/pestub.so $(DESTDIRSIGNING); \
	   cp $(BINDIR)/libldapssl30.so $(DESTDIRSIGNING); \
           chmod a+x $(DESTDIRSIGNING)/*.so; \
           chmod a+x $(DESTDIRNS)/*.so; \
           chmod a+x $(DESTDIRSTRONGHOLD)/*.so; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   mkdir -p $(DESTDIRIIS); \
	   cp $(BINDIR)/nsldapssl32v30.dll $(DESTDIRNS); \
	   cp $(BINDIR)/nsldapssl32v30.dll $(DESTDIRIIS); \
	   cp $(BINDIR)/sophialite.exe.winnt $(DESTDIRSIGNING)/sophialite.exe; \
	   cp $(BINDIR)/pestub.dll $(DESTDIRSIGNING); \
	   cp $(BINDIR)/nsldapssl32v30.dll $(DESTDIRSIGNING); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   mkdir -p $(DESTDIRSTRONGHOLD); \
	   cp $(BINDIR)/libldapssl30.sl $(DESTDIRNS); \
           cp $(BINDIR)/libldapssl30.sl $(DESTDIRSTRONGHOLD); \
	   cp $(BINDIR)/sophialite.exe.hpux $(DESTDIRSIGNING)/sophialite.exe; \
	   chmod a+x $(DESTDIRSIGNING)/sophialite.exe; \
	   cp $(BINDIR)/libpestub.sl $(DESTDIRSIGNING); \
	   cp $(BINDIR)/libldapssl30.sl $(DESTDIRSIGNING); \
	   chmod a+x $(DESTDIRSIGNING)/*.sl; \
	   chmod a+x $(DESTDIRNS)/*.sl; \
           chmod a+x $(DESTDIRSTRONGHOLD)/*.sl; \
	fi;
	@$(ECHO) ""

clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
	   $(RM) -rf $(DESTDIRSTRONGHOLD); \
	   $(RM) -rf $(DESTDIRSIGNING); \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
	   $(RM) -rf $(DESTDIRIIS); \
	   $(RM) -rf $(DESTDIRSIGNING); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
           $(RM) -rf $(DESTDIRSTRONGHOLD); \
	   $(RM) -rf $(DESTDIRSIGNING); \
	fi;
	@$(ECHO) ""


#include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

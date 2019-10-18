#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.2.8.1 2000/07/13 21:36:00 mwilson Exp $
#

ECAS_HOME=../../../../../..

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

DESTDIRIIS=$(CDINSTALL)/../server/pta/iis/bin
DESTDIRNS=$(CDINSTALL)/../server/pta/netscape/bin
DESTDIRSIGNING=$(CDINSTALL)/templates/pta/cgi-bin

all: cd-install

cd-install:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing CD --> $(DESTDIR)"
	mkdir -p $(DESTDIRNS)
	mkdir -p $(DESTDIRSIGNING)
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   cp libcdr.so $(DESTDIRNS); \
	   cp libldapssl30.so $(DESTDIRNS); \
	   cp libvsssc.so $(DESTDIRNS); \
	   cp libvssscn.so $(DESTDIRNS); \
	   cp libvsval.so $(DESTDIRNS); \
	   cp sophialite.exe.sparc $(DESTDIRSIGNING)/sophialite.exe; \
	   chmod a+x $(DESTDIRSIGNING)/sophialite.exe; \
	   cp pestub.so $(DESTDIRSIGNING); \
	   cp libvsssc.so $(DESTDIRSIGNING); \
	   cp libvsval.so $(DESTDIRSIGNING); \
	   cp libldapssl30.so $(DESTDIRSIGNING); \
           chmod a+x $(DESTDIRSIGNING)/*.so; \
           chmod a+x $(DESTDIRNS)/*.so; \
	fi;
	@if [ "$(TARCH)" = "winnt" ]; \
	then \
	   mkdir -p $(DESTDIRIIS); \
	   cp cdr.dll $(DESTDIRNS); \
	   cp nsldapssl32v30.dll $(DESTDIRNS); \
	   cp libvsssc.dll $(DESTDIRNS); \
	   cp libvssscn.dll $(DESTDIRNS); \
	   cp libvsval.dll $(DESTDIRNS); \
	   cp cdr.dll $(DESTDIRIIS); \
	   cp libvsssc.dll $(DESTDIRIIS); \
	   cp libvssscm.dll $(DESTDIRIIS); \
	   cp libvsval.dll $(DESTDIRIIS); \
	   cp loadreg.exe $(DESTDIRIIS); \
	   cp nsldapssl32v30.dll $(DESTDIRIIS); \
	   cp sophialite.exe.winnt $(DESTDIRSIGNING)/sophialite.exe; \
	   cp pestub.dll $(DESTDIRSIGNING); \
	   cp libvsssc.dll $(DESTDIRSIGNING); \
	   cp libvsval.dll $(DESTDIRSIGNING); \
	   cp nsldapssl32v30.dll $(DESTDIRSIGNING); \
	fi;
	@if [ "$(TARCH)" = "hpux" ]; \
	then \
	   cp libcdr.sl $(DESTDIRNS); \
	   cp libldapssl30.sl $(DESTDIRNS); \
	   cp libvsssc.sl $(DESTDIRNS); \
	   cp libvssscn.sl $(DESTDIRNS); \
	   cp libvsval.sl $(DESTDIRNS); \
	   cp sophialite.exe.hpux $(DESTDIRSIGNING)/sophialite.exe; \
	   chmod a+x $(DESTDIRSIGNING)/sophialite.exe; \
	   cp libpestub.sl $(DESTDIRSIGNING); \
	   cp libvsssc.sl $(DESTDIRSIGNING); \
	   cp libvsval.sl $(DESTDIRSIGNING); \
	   cp libldapssl30.sl $(DESTDIRSIGNING); \
	   chmod a+x $(DESTDIRSIGNING)/*.sl; \
	   chmod a+x $(DESTDIRNS)/*.sl; \
	fi;
	@$(ECHO) ""

clean:
	@if [ "$(TARCH)" = "sparc" ]; \
	then \
	   $(RM) -rf $(DESTDIRNS); \
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
	   $(RM) -rf $(DESTDIRSIGNING); \
	fi;
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

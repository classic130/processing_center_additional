#
#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.10.2.1 2001/04/20 23:09:09 aranade Exp $
#

#
# make for : Signed VSGSE.cab
#	     VSExchange.dll
#	     VSSgnAtb.dll
#	     VSImport.dll
#	     srchexce.exe
#
# Target Description :
#
# all : This will create the installables from the "Release" version.
#	It will also copy the installables locally 
#	(itgclient/packager/local-install) as well as in the sitekit
#	CD directory.
#
# install-ecas:
# cd-install: Both these targets will behave same and will create and copy
#	the "Release" version of the installables to the sitekit CD directory.
#
# debug-install-ecas:
# debug-cd-install: Both these targets will behave same and will create and copy
#	the "Debug" version of the installables to the sitekit CD directory.
#
# install-local: This will create and copy the "Release" version of the
#	installables to the local install directory 
#	(itgclient/packager/local-install).
#
# debug-install-local: This will create and copy the "Debug" version of the
#	installables to the local install directory 
#	(itgclient/packager/local-install).
#
# clean:
#	This will remove the installables from the sitekit CD directory as
#	well as the local install directory.
#
# cd-uninstall:
# uninstall-ecas:
#	Both these targets will remove the installables from the sitekit CD
#	directory.
#
# uninstall-local:
#	This will remove the installables from the local install directory.

ECAS_HOME=../../..

INSTALL_BIN_LOC = $(clientsBIN)

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

LOCAL_INSTALL_DIR=$(ECAS_HOME)/itgclient/packager/local-install
RELEASECLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/release
RELEASESERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/release
DEBUGCLIENTLIBDIR=$(ECAS_HOME)/itgclient/client/lib/dynamic/debug
DEBUGSERVERLIBDIR=$(ECAS_HOME)/itgclient/server/lib/dynamic/debug
RELEASESERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/release
DEBUGSERVERBINDIR=$(ECAS_HOME)/itgclient/server/bin/debug
CDINSTALLHTMLDOCSDIR=$(CDINSTALL)/templates/htmldocs/VSApps
CDINSTALLHTMLDOCSDIRv1=$(CDINSTALL)/templates/htmldocs
CDINSTALLCGIBINDIR=$(CDINSTALL)/templates/cgi-bin/VSApps
CDINSTALL_ONSITE_CGIBINDIR=$(CDINSTALL)/templates/cgi-bin
RELEASECLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/release
DEBUGCLIENTBINDIR=$(ECAS_HOME)/itgclient/client/bin/debug

DLLNAME1=VSGSE
DLLNAME2=VSExchange
DLLNAME3=VSGSEExt
DLLNAME4=VSSgnAtb
DLLNAME5=VSImport
EXENAME1=srchexce
EXENAME2=oesetupw
EXENAME3=gsesetupw

all: install-ecas install-local

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating $(DLLNAME1).cab, $(DLLNAME4).cab & $(DLLNAME5).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME4).inf .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME4).dll .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME5).inf .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME5).dll .
	cabarc N $(DLLNAME1).cab $(DLLNAME1).inf $(DLLNAME1).dll $(DLLNAME3).dll
	cabarc N $(DLLNAME4).cab $(DLLNAME4).inf $(DLLNAME4).dll
	cabarc N $(DLLNAME5).cab $(DLLNAME5).inf $(DLLNAME5).dll

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug - $(DLLNAME1).cab, $(DLLNAME4).cab & $(DLLNAME5).cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME4).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME4).dll .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME5).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME5).dll .
	cabarc N $(DLLNAME1).cab $(DLLNAME1).inf $(DLLNAME1).dll $(DLLNAME3).dll
	cabarc N $(DLLNAME4).cab $(DLLNAME4).inf $(DLLNAME4).dll
	cabarc N $(DLLNAME5).cab $(DLLNAME5).inf $(DLLNAME5).dll

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing $(DLLNAME1).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Go Secure! for Exchange ActiveX Control" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(DLLNAME1).cab	
	@$(ECHO) "$(ME):Signing $(DLLNAME4).cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Sign Attributes ActiveX Control" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(DLLNAME4).cab	
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Import Control" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(DLLNAME5).cab	
	
	

debug-copylocal:
	cp $(DEBUGSERVERLIBDIR)/$(DLLNAME2).dll .
	cp $(DEBUGSERVERBINDIR)/$(EXENAME1).exe .
	cp $(DEBUGCLIENTBINDIR)/$(EXENAME2).exe .
	cp $(DEBUGCLIENTBINDIR)/$(EXENAME3).exe .
	wzzip OSEXSETP.zip @OSEXSETP.lst
	wzzip GSESETP.zip @GSESETP.lst
	wzipse32 OSEXSETP.zip -d "C:\Program Files\VeriSign\OnSite\GSE" -y -auto -c oesetupw
	wzipse32 GSESETP.zip -d "C:\Program Files\VeriSign\OnSite\GSE" -y -auto -c gsesetupw

release-copylocal:
	cp $(RELEASESERVERLIBDIR)/$(DLLNAME2).dll .
	cp $(RELEASESERVERBINDIR)/$(EXENAME1).exe .
	cp $(RELEASECLIENTBINDIR)/$(EXENAME2).exe .
	cp $(RELEASECLIENTBINDIR)/$(EXENAME3).exe .
	wzzip OSEXSETP.zip @OSEXSETP.lst
	wzzip GSESETP.zip @GSESETP.lst
	wzipse32 OSEXSETP.zip -d "C:\Program Files\VeriSign\OnSite\GSE" -y -auto -c oesetupw
	wzipse32 GSESETP.zip -d "C:\Program Files\VeriSign\OnSite\GSE" -y -auto -c gsesetupw

cd-install: install-ecas
install-ecas: cabarc signcab release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(DLLNAME1).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME1).cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing $(DLLNAME4).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME4).cab $(CDINSTALLHTMLDOCSDIR)
	cp $(DLLNAME4).cab $(CDINSTALLHTMLDOCSDIRv1)
	@$(ECHO) "$(ME):Installing $(DLLNAME5).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME5).cab $(CDINSTALLHTMLDOCSDIR)
	cp $(DLLNAME5).cab $(CDINSTALLHTMLDOCSDIRv1)
	@$(ECHO) "$(ME):Installing OSEXSETP.zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp OSEXSETP.zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing GSESETP.zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp GSESETP.zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing OSEXSETP.exe --> $(CDINSTALLHTMLDOCSDIR)"
	cp OSEXSETP.exe $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing GSESETP.exe --> $(CDINSTALLHTMLDOCSDIR)"
	cp GSESETP.exe $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(CDINSTALL_ONSITE_CGIBINDIR)
	cp $(DLLNAME2).dll $(CDINSTALL_ONSITE_CGIBINDIR)
	mkdir -p $(CDINSTALLCGIBINDIR)
	cp $(EXENAME1).exe $(CDINSTALLCGIBINDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab debug-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing Debug $(DLLNAME1).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME1).cab $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing Debug $(DLLNAME4).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME4).cab $(CDINSTALLHTMLDOCSDIR)
	cp $(DLLNAME4).cab $(CDINSTALLHTMLDOCSDIRv1)
	@$(ECHO) "$(ME):Installing Debug $(DLLNAME5).cab --> $(CDINSTALLHTMLDOCSDIR)"
	cp $(DLLNAME5).cab $(CDINSTALLHTMLDOCSDIR)
	cp $(DLLNAME5).cab $(CDINSTALLHTMLDOCSDIRv1)
	@$(ECHO) "$(ME):Installing OSEXSETP.zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp OSEXSETP.zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing GSESETP.zip --> $(CDINSTALLHTMLDOCSDIR)"
	cp GSESETP.zip $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing OSEXSETP.exe --> $(CDINSTALLHTMLDOCSDIR)"
	cp OSEXSETP.exe $(CDINSTALLHTMLDOCSDIR)
	@$(ECHO) "$(ME):Installing GSESETP.exe --> $(CDINSTALLHTMLDOCSDIR)"
	cp GSESETP.exe $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(CDINSTALL_ONSITE_CGIBINDIR)
	cp $(DLLNAME2).dll $(CDINSTALL_ONSITE_CGIBINDIR)
	mkdir -p $(CDINSTALLCGIBINDIR)
	cp $(EXENAME1).exe $(CDINSTALLCGIBINDIR)
	@$(ECHO) ""

install-local: cabarc signcab release-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(DLLNAME1).cab, $(DLLNAME4).cab, $(DLLNAME5).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME1).cab $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME4).cab $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME5).cab $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME2).dll $(LOCAL_INSTALL_DIR)
	cp $(EXENAME1).exe $(LOCAL_INSTALL_DIR)
	cp OSEXSETP.zip $(LOCAL_INSTALL_DIR)
	cp GSESETP.zip $(LOCAL_INSTALL_DIR)
	cp OSEXSETP.exe $(LOCAL_INSTALL_DIR)
	cp GSESETP.exe $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab debug-copylocal
	@$(ECHO) ""
	@$(ECHO) "$(ME):Installing $(DLLNAME1).cab, $(DLLNAME4).cab, $(DLLNAME5).cab --> $(LOCAL_INSTALL_DIR)"
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME1).cab $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME4).cab $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME5).cab $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME2).dll $(LOCAL_INSTALL_DIR)
	cp $(EXENAME1).exe $(LOCAL_INSTALL_DIR)
	cp OSEXSETP.zip $(LOCAL_INSTALL_DIR)
	cp GSESETP.zip $(LOCAL_INSTALL_DIR)
	cp OSEXSETP.exe $(LOCAL_INSTALL_DIR)
	cp GSESETP.exe $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(DLLNAME1).inf
	$(RM) $(DLLNAME1).cab
	$(RM) $(DLLNAME1).dll
	$(RM) $(DLLNAME2).dll
	$(RM) $(DLLNAME3).dll
	$(RM) $(EXENAME1).exe
	$(RM) $(EXENAME2).exe
	$(RM) $(EXENAME3).exe
	$(RM) $(DLLNAME4).inf
	$(RM) $(DLLNAME4).cab
	$(RM) $(DLLNAME4).dll
	$(RM) $(DLLNAME5).inf
	$(RM) $(DLLNAME5).cab
	$(RM) $(DLLNAME5).dll

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local $(DLLNAME1).cab, $(DLLNAME4).cab & $(DLLNAME5).cab"
	$(RM) $(LOCAL_INSTALL_DIR)/$(DLLNAME1).cab
	$(RM) $(LOCAL_INSTALL_DIR)/$(DLLNAME4).cab
	$(RM) $(LOCAL_INSTALL_DIR)/$(DLLNAME5).cab
	$(RM) $(LOCAL_INSTALL_DIR)/$(DLLNAME2).dll
	$(RM) $(LOCAL_INSTALL_DIR)/$(EXENAME1).exe
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling $(CDINSTALLHTMLDOCSDIR)/$(DLLNAME1).cab, $(DLLNAME4).cab & $(DLLNAME5).cab"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(DLLNAME1).cab
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(DLLNAME4).cab
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(DLLNAME5).cab
	$(RM) $(CDINSTALL_ONSITE_CGIBINDIR)/$(DLLNAME2).dll
	$(RM) $(CDINSTALLCGIBINDIR)/$(EXENAME1).exe
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


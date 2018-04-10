#
#       GNUmakefile 
#       Developed by Abhay Ranade
#	$Id: GNUmakefile,v 1.1.2.2 2002/02/01 19:14:53 ajayaram Exp $
#	ajayaram : Automated creating of self extracting exes.

#
# make for : Signed VSSMPTA.cab
#	     npvssc.dll
#	     vsscnpsetup.exe
#	     vsprscgi.exe
#	     vsprsauth.dll
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

CSPSIGNDIR=$(ECAS_HOME)/itgclient/packager/pta/cspsign

SIGNTOOLDIR=$(ECAS_HOME)/itgclient/thirdparty/netscape/PluginSDK

SMPTAJARDIR=Setupvssc

# Note: once itgclient_v1_sc simder is merged to TOT use DLLNAME1 and SIGNFILE which are commented now

DLLNAME1=VSSC
DLLNAME2=Ptav3
DLLNAME3=npvssc
DLLNAME3_CLASS=NPVSSC
DLLNAME4=vsprsauth
JAR1=vsnpsmpta
EXENAME1=vsscnpsetup
EXENAME2=vsprs
EXENAME3=vsscsetup
EXENAME4=npsesetup
SIGNFILE=vscspsign
SELFEXTRACTACTIVEX=vsscsetp
SELFEXTRACTPLUGIN=npsesetp


all: install-ecas install-local

cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Release : VSSMPTA.cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll .
	#cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).inf .
	#cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll .
	cp $(RELEASESERVERBINDIR)/$(EXENAME2).exe .
	cp $(RELEASESERVERLIBDIR)/$(DLLNAME4).dll .
	#cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N VSSMPTA.cab $(DLLNAME1).inf $(DLLNAME1).dll $(DLLNAME2).dll $(SIGNFILE)

debug-cabarc:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug : VSSMPTA.cab"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).inf .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll .
	#cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).inf .
	#cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll .
	cp $(DEBUGSERVERBINDIR)/$(EXENAME2).exe .
	cp $(DEBUGSERVERLIBDIR)/$(DLLNAME4).dll .
	#cp $(CSPSIGNDIR)/$(SIGNFILE) .
	cabarc N VSSMPTA.cab $(DLLNAME1).inf $(DLLNAME1).dll $(DLLNAME2).dll $(SIGNFILE)

signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Release : $(JAR1).jar"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll $(SMPTAJARDIR)
	#cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll $(SMPTAJARDIR)
	cp ./$(DLLNAME2).dll $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3_CLASS).class $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll $(SMPTAJARDIR)
	cp $(RELEASECLIENTBINDIR)/$(EXENAME1).exe $(SMPTAJARDIR)
	cp $(RELEASECLIENTBINDIR)/$(JAR1).js $(SMPTAJARDIR)
	#cp $(CSPSIGNDIR)/$(SIGNFILE) $(SMPTAJARDIR)
	cp ./$(SIGNFILE) $(SMPTAJARDIR)
	$(SIGNTOOLDIR)\\signtool -d a:\ns -k "VeriSign, Inc.'s VeriSign, Inc. ID" -i "$(JAR1).js" -p "ver1sign" -Z .\\$(SMPTAJARDIR)\\$(JAR1).jar $(SMPTAJARDIR)

debug-signtool:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug : $(JAR1).jar"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll $(SMPTAJARDIR)
	cp ./$(DLLNAME2).dll $(SMPTAJARDIR)
	#cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3_CLASS).class $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll $(SMPTAJARDIR)
	cp $(DEBUGCLIENTBINDIR)/$(EXENAME1).exe $(SMPTAJARDIR)
	cp $(DEBUGCLIENTBINDIR)/$(JAR1).js $(SMPTAJARDIR)
	#cp $(CSPSIGNDIR)/$(SIGNFILE) $(SMPTAJARDIR)
	cp ./$(SIGNFILE) $(SMPTAJARDIR)
	$(SIGNTOOLDIR)\\signtool -d a:\ns -k "VeriSign, Inc.'s VeriSign, Inc. ID" -i "$(JAR1).js" -p "ver1sign" -Z .\\$(SMPTAJARDIR)\\$(JAR1).jar $(SMPTAJARDIR)

signcab:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Signing VSSMPTA.cab"
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign Secure Messaging PTA" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" VSSMPTA.cab

debug-copylocal-activex:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug : VSSCSETP.EXE"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll .
	#cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll .
	cp $(DEBUGCLIENTBINDIR)/$(EXENAME3).exe .
	#cp $(CSPSIGNDIR)/$(SIGNFILE) .
	wzzip $(SELFEXTRACTACTIVEX).zip @$(SELFEXTRACTACTIVEX).lst
	wzipse32 $(SELFEXTRACTACTIVEX).zip -d "C:\Program Files\VeriSign\SecureExpress" -y -auto -c $(EXENAME3).exe
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign/SE Desktop Update" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(SELFEXTRACTACTIVEX).exe

release-copylocal-activex:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Release : VSSCSETP.EXE"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll .
	#cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll .
	cp $(RELEASECLIENTBINDIR)/$(EXENAME3).exe .
	#cp $(CSPSIGNDIR)/$(SIGNFILE) .
	wzzip $(SELFEXTRACTACTIVEX).zip @$(SELFEXTRACTACTIVEX).lst
	wzipse32 $(SELFEXTRACTACTIVEX).zip -d "C:\Program Files\VeriSign\SecureExpress" -y -auto -c $(EXENAME3).exe
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign/SE Desktop Update" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(SELFEXTRACTACTIVEX).exe


debug-copylocal-plugin:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug : NPSESETUP.EXE"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME1).dll $(SMPTAJARDIR)
	cp ./$(DLLNAME2).dll $(SMPTAJARDIR)
	#cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME2).dll $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3_CLASS).class $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll $(SMPTAJARDIR)
	cp $(DEBUGCLIENTBINDIR)/$(EXENAME4).exe $(SMPTAJARDIR)
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3_CLASS).class .
	cp $(DEBUGCLIENTLIBDIR)/$(DLLNAME3).dll .
	cp $(DEBUGCLIENTBINDIR)/$(EXENAME4).exe .
	#cp $(CSPSIGNDIR)/$(SIGNFILE) $(SMPTAJARDIR)
	cp ./$(SIGNFILE) $(SMPTAJARDIR)
	cp $(SELFEXTRACTPLUGIN).lst $(SMPTAJARDIR)
	wzzip $(SMPTAJARDIR)/$(SELFEXTRACTPLUGIN).zip @$(SMPTAJARDIR)\$(SELFEXTRACTPLUGIN).lst
	wzipse32 $(SMPTAJARDIR)/$(SELFEXTRACTPLUGIN).zip -d "C:\Program Files\VeriSign\SecureExpress\Plugin" -y -auto -c $(EXENAME4).exe
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign/SE Desktop Update" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(SELFEXTRACTPLUGIN).exe

release-copylocal-plugin:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Creating Debug : NPSESETUP.EXE"
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME1).dll $(SMPTAJARDIR)
	cp ./$(DLLNAME2).dll $(SMPTAJARDIR)
	#cp $(RELEASECLIENTLIBDIR)/$(DLLNAME2).dll $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3_CLASS).class $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll $(SMPTAJARDIR)
	cp $(RELEASECLIENTBINDIR)/$(EXENAME4).exe $(SMPTAJARDIR)
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3_CLASS).class .
	cp $(RELEASECLIENTLIBDIR)/$(DLLNAME3).dll .
	cp $(RELEASECLIENTBINDIR)/$(EXENAME4).exe .
	#cp $(CSPSIGNDIR)/$(SIGNFILE) $(SMPTAJARDIR)
	cp ./$(SIGNFILE) $(SMPTAJARDIR)
	cp $(SELFEXTRACTPLUGIN).lst $(SMPTAJARDIR)
	wzzip $(SMPTAJARDIR)/$(SELFEXTRACTPLUGIN).zip @$(SMPTAJARDIR)/$(SELFEXTRACTPLUGIN).lst
	wzipse32 $(SMPTAJARDIR)/$(SELFEXTRACTPLUGIN).zip -d "C:\Program Files\VeriSign\SecureExpress\Plugin" -y -auto -c $(EXENAME4).exe
	signcode -spc a:\newcert.spc -v a:\newvs.pvk -n "VeriSign/SE Desktop Update" -i "http://www.verisign.com" -t "http://timestamp.verisign.com/scripts/timstamp.dll" $(SMPTAJARDIR)/$(SELFEXTRACTPLUGIN).exe



cd-install: install-ecas
install-ecas: cabarc signcab signtool release-copylocal-activex release-copylocal-plugin
	@$(ECHO) ""
	mkdir -p $(CDINSTALLHTMLDOCSDIR)
	cp VSSMPTA.cab $(CDINSTALLHTMLDOCSDIR)
	cp ./$(SMPTAJARDIR)/$(JAR1).jar $(CDINSTALLHTMLDOCSDIR)
	mkdir -p $(CDINSTALL_ONSITE_CGIBINDIR)
	cp $(EXENAME2).exe $(CDINSTALLCGIBINDIR)
	cp $(DLLNAME4).dll $(CDINSTALLCGIBINDIR)
	@$(ECHO) ""

debug-cd-install: debug-install-ecas
debug-install-ecas: debug-cabarc signcab debug-signtool debug-copylocal-activex debug-copylocal-plugin

install-local: cabarc signcab signtool release-copylocal-activex release-copylocal-plugin
	@$(ECHO) ""
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp VSSMPTA.cab $(LOCAL_INSTALL_DIR)
	cp ./$(SMPTAJARDIR)/$(JAR1).jar $(LOCAL_INSTALL_DIR)
	cp $(EXENAME2).exe $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME4).dll $(LOCAL_INSTALL_DIR)
	cp $(EXENAME3).exe $(LOCAL_INSTALL_DIR)
	cp ./$(SMPTAJARDIR)/$(EXENAME4).exe $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

debug-install-local: debug-cabarc signcab debug-signtool debug-copylocal-activex debug-copylocal-plugin
	@$(ECHO) ""
	mkdir -p $(LOCAL_INSTALL_DIR)
	cp VSSMPTA.cab $(LOCAL_INSTALL_DIR)
	cp ./$(SMPTAJARDIR)/$(JAR1).jar $(LOCAL_INSTALL_DIR)
	cp $(EXENAME2).exe $(LOCAL_INSTALL_DIR)
	cp $(DLLNAME4).dll $(LOCAL_INSTALL_DIR)
	cp $(EXENAME3).exe $(LOCAL_INSTALL_DIR)
	cp ./$(SMPTAJARDIR)/$(EXENAME4).exe $(LOCAL_INSTALL_DIR)
	@$(ECHO) ""

clean: uninstall-local uninstall-ecas uninstall-dot

uninstall-dot:
	$(RM) $(DLLNAME1).inf
	$(RM) $(DLLNAME1).dll
	#$(RM) $(DLLNAME2).inf
	#$(RM) $(DLLNAME2).dll
	#$(RM) $(SIGNFILE)
	$(RM) VSSMPTA.cab
	$(RM) $(DLLNAME3_CLASS).class
	$(RM) $(DLLNAME3).dll
	$(RM) $(JAR1).jar
	$(RM) $(EXENAME1).exe
	$(RM) $(EXENAME2).exe
	$(RM) $(EXENAME3).exe
	$(RM) $(EXENAME4).exe
	$(RM) $(DLLNAME4).dll
	$(RM) $(SMPTAJARDIR)\$(SELFEXTRACTPLUGIN).exe
	$(RM) $(SELFEXTRACTACTIVEX).exe
	$(RM) $(SMPTAJARDIR)\$(SELFEXTRACTPLUGIN).zip
	$(RM) $(SELFEXTRACTACTIVEX).zip
	$(RM) Release
	$(RM) -rf $(SMPTAJARDIR)


uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling Local "
	$(RM) $(LOCAL_INSTALL_DIR)/VSSMPTA.cab
	$(RM) $(LOCAL_INSTALL_DIR)/$(JAR1).jar
	$(RM) $(LOCAL_INSTALL_DIR)/$(EXENAME2).exe
	$(RM) $(LOCAL_INSTALL_DIR)/$(DLLNAME4).dll
	$(RM) $(LOCAL_INSTALL_DIR)/$(EXENAME3).exe
	$(RM) $(LOCAL_INSTALL_DIR)/$(EXENAME4).exe
	@$(ECHO) ""

cd-uninstall: uninstall-ecas
uninstall-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME): Uninstalling ECAS"
	$(RM) $(CDINSTALLHTMLDOCSDIR)/VSSMPTA.cab
	$(RM) $(CDINSTALLHTMLDOCSDIR)/$(JAR1).jar
	$(RM) $(CDINSTALLCGIBINDIR)/$(EXENAME2).exe
	$(RM) $(LOCAL_INSTALL_DIR)/$(DLLNAME4).dll
	$(RM) $(LOCAL_INSTALL_DIR)/$(EXENAME3).exe
	$(RM) $(LOCAL_INSTALL_DIR)/$(EXENAME4).exe
	@$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"

include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


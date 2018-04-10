#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.1.4.1 2001/10/05 03:49:49 sbajaj Exp $
#
ECAS_HOME=../../../../..
include $(ECAS_CUSTOM_CFG)
include $(ECAS_HOME)/build/make/os/WinNT.cfg
include $(ECAS_HOME)/build/make/custom/WinNT.cfg

MAKE = nmake
unexport MAKEFLAGS

TARCH = winnt

LOCAL_INSTALL_LIB_LOC = $(ECAS_HOME)/itgclient/server/bin
LDAP_winnt_LIB=nsldapssl32v30.dll

DESTDIRCOMVSSSC=$(CDINSTALL)/../server/pta/comvsssc
DESTDIRBIN=$(DESTDIRCOMVSSSC)/bin
DESTDIRCFG=$(CDINSTALL)/templates/pta/config
DESTDIRCFG2=$(DESTDIRCOMVSSSC)/config
DESTDIRCGI=$(CDINSTALL)/templates/pta/cgi-bin



all: release debug

uninstall-local:clean
cd-install:clean
uninstall-ecas:clean
clean :
	${MAKE} /f comvsssc.mak CFG="comvsssc - Win32 Release" CLEAN
	${MAKE} /f comvsssc.mak CFG="comvsssc - Win32 Debug" CLEAN
	-rm $(LOCAL_INSTALL_LIB_LOC)/comvsssc.exe
	-rm -rf Debug
	-rm -rf Release
	-rm -rf $(DESTDIRCOMVSSSC)
	-rm -rf $(DESTDIRCGI)/VerifySignature.asp
	-rm -rf $(DESTDIRCFG)/comvsssc-cfg.txt

debug-install: debug
debug:
	${MAKE} /f comvsssc.mak CFG="comvsssc - Win32 Debug"
	mkdir -p $(LOCAL_INSTALL_LIB_LOC)
	cp Debug/comvsssc.exe $(LOCAL_INSTALL_LIB_LOC)

release-install: release
cd-install: release
install-ecas: release
install-local: release
release:
	${MAKE} /f comvsssc.mak CFG="comvsssc - Win32 Release"
	mkdir -p $(LOCAL_INSTALL_LIB_LOC)
	cp Release/comvsssc.exe $(LOCAL_INSTALL_LIB_LOC)
	mkdir -p $(DESTDIRBIN)
	mkdir -p $(DESTDIRCFG)
	mkdir -p $(DESTDIRCFG2)
	mkdir -p $(DESTDIRCGI)
	@$(INSTALL_SH) -m 555 Release/comvsssc.exe $(DESTDIRBIN)
	@$(INSTALL_SH) -m 555 ../source/make/libvsssc/dynamic/winnt-release/libvsssc.dll $(DESTDIRBIN)
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/$(LDAP_winnt_LIB) $(DESTDIRBIN)
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/libvsvalsdk$(DLIB_EXT) $(DESTDIRBIN)
	@$(INSTALL_SH) -m 555 VerifySignature.asp $(DESTDIRCGI)
	@$(INSTALL_SH) -m 555 comvsssc-cfg.txt $(DESTDIRCFG)
	@$(INSTALL_SH) -m 555 comvsssc-cfg.txt $(DESTDIRCFG2)
	@$(INSTALL_SH) -m 555 outproc.vbs $(DESTDIRCFG2)

	
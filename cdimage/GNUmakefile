#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.5.6.1 2004/01/31 00:58:36 ldavid Exp $
#

#
# make for cdimage
#

ECAS_HOME = ..
include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg


debug:
	mkdir -p tar
	cp *.gz tar/
	cd tar; ls *.gz | grep -v roam | grep -v vsrm | xargs gunzip

cdimage:
	mkdir -p untar${TARCH}
	bash untar${TARCH}.ksh

release: debug cdimage

install-local:
	echo "nothing to do for install-local"

clean:
	-rm -rf tar
	-rm -rf untar${TARCH}

depend:

installSrcPkg:
	installSrcPkg.pl -bpn ../build/log/enterprise/BaseDirArray.engineering.desktop -fpn ../build/log/enterprise/FullBaseInstallDirArray.engineering.desktop -t tar

createSrcPkg:
	createSrcPkg.pl -bn ../build/log/enterprise/BaseDirArray.engineering.desktop -fn ../build/log/enterprise/FullBaseInstallDirArray.engineering.desktop -t tar


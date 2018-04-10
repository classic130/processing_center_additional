#	GNUmakefile 
#       Developed by Siddharth Bajaj
#	$Id: GNUmakefile,v 1.2.126.3 2001/04/11 19:11:06 bzou Exp $
#

MAKE = nmake
unexport MAKEFLAGS

all: make-release cd-install
debug: make-debug debug-install
release: make-release cd-install
install-ecas: make-release
install-local: make-release cd-install
uninstall-local:clean
uninstall-ecas:clean
clean :
	${MAKE} /f VerifySignature.mak CFG="VerifySignature - Win32 Release" CLEAN
	${MAKE} /f VerifySignature.mak CFG="VerifySignature - Win32 Debug" CLEAN
	-rm -rf Debug
	-rm -rf Release
	-rm -rf $(CDINSTALL)/../server/pta/examples/VerifySignature
	-rm -rf $(CDINSTALL)/templates/pta/cgi-bin/VerifySignature.exe

make-debug:
	${MAKE} /f VerifySignature.mak CFG="VerifySignature - Win32 Debug"

cd-install: release
	-mkdir -p $(CDINSTALL)/../server/pta/examples/VerifySignature
	-cp ../VerifySignature.cpp $(CDINSTALL)/../server/pta/examples/VerifySignature/
	-cp ./VerifySignature.mak $(CDINSTALL)/../server/pta/examples/VerifySignature/
	-mkdir -p $(CDINSTALL)/templates/pta/cgi-bin
	-mkdir -p $(CDINSTALL)/templates/pta/config
	-cp Release/VerifySignature.exe $(CDINSTALL)/templates/pta/cgi-bin
	   cp ../Sample.bat $(CDINSTALL)/templates/pta/cgi-bin/Sample.bat
	   cp ../SampleMessage.txt $(CDINSTALL)/templates/pta/cgi-bin/SampleMessage.txt
	   cp ../SampleSignature.txt $(CDINSTALL)/templates/pta/cgi-bin/SampleSignature.txt
	   cp ../VerifySignatureOptions.txt $(CDINSTALL)/templates/pta/config/VerifySignatureOptions.txt
	   cp ../VerifySignature.cfg $(CDINSTALL)/templates/pta/config/VerifySignature.cfg

make-release:
	${MAKE} /f VerifySignature.mak CFG="VerifySignature - Win32 Release"

debug-install: release
	-mkdir -p $(CDINSTALL)/../server/pta/examples/VerifySignature
	-cp ../VerifySignature.cpp $(CDINSTALL)/../server/pta/examples/VerifySignature/
	-cp ./VerifySignature.mak $(CDINSTALL)/../server/pta/examples/VerifySignature/
	-mkdir -p $(CDINSTALL)/templates/pta/cgi-bin
	-cp Debug/VerifySignature.exe $(CDINSTALL)/templates/pta/cgi-bin


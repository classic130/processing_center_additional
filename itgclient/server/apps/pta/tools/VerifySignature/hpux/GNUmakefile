#
# Application MakeFile
#

INCL =  -I./ -I../include -I../../../../include

CFLAGS = -c +z +DAportable $(INCL) -g -DHPUX
OBJS = VerifySignature.o
RM = rm -f
CC=/opt/aCC/bin/aCC

OTHERLIBS = -lpthread

debug :: VerifySignature.exe
release :: VerifySignature.exe
all :: VerifySignature.exe

VerifySignature.exe :  $(OBJS)
	   $(CC)   $(OTHERLIBS) -o $@ $(OBJS)
	   mkdir -p $(CDINSTALL)/templates/pta/cgi-bin
	   mkdir -p $(CDINSTALL)/templates/pta/config
	   cp VerifySignature.exe $(CDINSTALL)/templates/pta/cgi-bin/VerifySignature.exe
	   cp ../Sample.unix $(CDINSTALL)/templates/pta/cgi-bin/Sample.unix
	   cp ../SampleMessage.txt $(CDINSTALL)/templates/pta/cgi-bin/SampleMessage.txt
	   cp ../SampleSignature.txt $(CDINSTALL)/templates/pta/cgi-bin/SampleSignature.txt
	   cp ../VerifySignatureOptions.txt $(CDINSTALL)/templates/pta/config/VerifySignatureOptions.txt
	   cp ../VerifySignature.cfg $(CDINSTALL)/templates/pta/config/VerifySignature.cfg
	   chmod 755 $(CDINSTALL)/templates/pta/cgi-bin/VerifySignature.exe \
			$(CDINSTALL)/templates/pta/cgi-bin/Sample.unix \
			$(CDINSTALL)/templates/pta/cgi-bin/SampleMessage.txt \
			$(CDINSTALL)/templates/pta/cgi-bin/SampleSignature.txt \
			$(CDINSTALL)/templates/pta/config/VerifySignatureOptions.txt \
			$(CDINSTALL)/templates/pta/config/VerifySignature.cfg
	   mkdir -p $(CDINSTALL)/../server/pta/examples/VerifySignature
	   cp ../VerifySignature.cpp $(CDINSTALL)/../server/pta/examples/VerifySignature/
	   cp ./Makefile.hpux $(CDINSTALL)/../server/pta/examples/VerifySignature/

VerifySignature.o:	../VerifySignature.cpp
		$(CC)  $(CFLAGS) ../VerifySignature.cpp

clean ::
	$(RM) *.o VerifySignature.exe
	rm -rf $(CDINSTALL)/../server/pta/examples/VerifySignature
	$(RM) $(CDINSTALL)/templates/pta/cgi-bin/VerifySignature.exe

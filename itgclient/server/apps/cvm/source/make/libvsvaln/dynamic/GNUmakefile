#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.5.12.2 2005/02/23 08:39:54 aalsup Exp $
#

#
# make for  libvsvaln.so
#

ECAS_HOME=../../../../../../../..


#
# This library name withoout extension
#
LIBNAME=libvsvaln
DESTDIR=$(CDINSTALL)/../server/cvm/netscape/bin
LDAP_winnt_LIB=nsldapssl32v30.dll
LDAP_sparc_LIB=libldapssl30.so
LDAP_hpux_LIB=libldapssl30.sl
LDAP_aix_LIB=libldapssl30.so
                                      
#
# Target dynamic lib for this make
#
DLIB=$(ARCH)/$(LIBNAME)$(DLIB_EXT)$(ECAS_VERS)

#
# Record header info in .so to be used with -R or LD_LIBRARY_PATH
#
DLIB_HEADER_INFO=$(LIBNAME)$(DLIB_EXT)$(ECAS_VERS)


#
# Import lib for linking in this make; NT requires .lib version to
# link; For UNIX this will be the .so version
#
IMPORT_LIB=$(ARCH)/$(LIBNAME)$(IMPORT_LIB_EXT)$(ECAS_VERS)



#
# install and local install locations
#
INSTALL_LIB_LOC       = $(ECAS_HOME)/itgclient/server/lib/dynamic
LOCAL_INSTALL_LIB_LOC = $(ECAS_HOME)/itgclient/server/lib/dynamic


include $(ECAS_CUSTOM_CFG)
# override which config files to use for hpux
#CONFIG.hpux.CC=$(ECAS_COMPILER_DIR)/Hpux1020_linkld.cfg
#CONFIG.hpux.LIBRULES=$(ECAS_RULES_DIR)/Hpux1020_linkld.cfg
include $(ECAS_COMMON_DIR)/lib.cfg

#
# Override compiler to compile .c files with C++
# cc=$(COMPILER_CC)


#
# C and C++ source names, if any, goes here -- minus the .c or .cc
#
# NOTE ::
#       we  are stripping any path names from the source files to create
#       the  corresponding .o file under $(ARCH) This makefile might not
#       need  this  but still the lines of code are just a template that
#       can be used in any other place
#

SRCDIR      = ../../..


ifeq ($(TARCH), winnt)
CRL_UPD_THR=vs_cvm_win_thr
endif
ifeq ($(TARCH), sparc)
CRL_UPD_THR=vs_cvm_sol_thr
endif
ifeq ($(TARCH), hpux)
CRL_UPD_THR=vs_cvm_pos_thr
endif
ifeq ($(TARCH), aix)
CRL_UPD_THR=vs_cvm_pos_thr
endif
ifeq ($(TARCH), linux)
CRL_UPD_THR=vs_cvm_pos_thr
endif


# .c files
C_PIECES     = $(SRCDIR)/nsapival $(SRCDIR)/cvmglobal $(SRCDIR)/vs_cvm_genlib \
               $(SRCDIR)/vs_cvm_log \
               $(SRCDIR)/$(CRL_UPD_THR)
C_FNAMES     = $(notdir $(C_PIECES))       # strip path
C_FILES      = $(C_PIECES:%=%.c)
C_O_FILES    = $(C_FNAMES:%=$(ARCH)/%.o)


# .cc files
CC_PIECES    =
CC_FNAMES    = $(notdir $(CC_PIECES))     # strip path
CC_FILES     = $(CC_PIECES:%=%.cc)
CC_O_FILES   = $(CC_FNAMES:%=$(ARCH)/%.o)


# .cpp files
CPP_PIECES   =
CPP_FNAMES   = $(notdir $(CPP_PIECES))    # strip path
CPP_FILES    = $(CPP_PIECES:%=%.cpp)
CPP_O_FILES  = $(CPP_FNAMES:%=$(ARCH)/%.o)

ifeq ($(TARCH), winnt)
RC_PIECES   = $(SRCDIR)/valn
RC_FNAMES   = $(notdir $(RC_PIECES))    # strip path
RC_FILES    = $(RC_PIECES:%=%.rc)
RC_O_FILES  = $(RC_FNAMES:%=$(ARCH)/%.res)
endif

SRCS=$(C_FILES) $(CC_FILES) $(CPP_FILES) $(RC_FILES)
OBJS=$(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES) $(RC_O_FILES)

#SRCS=$(C_FILES) $(CC_FILES) $(CPP_FILES)
#OBJS=$(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES)

# Binary programs

BIN_PIECES =
BIN_FNAMES = $(notdir $(BIN_PIECES))      # strip path
BIN_O_FILES= $(BIN_FNAMES:%=$(ARCH)/%.o)
BIN_FILES  = $(BIN_FNAMES:%=$(ARCH)/%$(BIN_EXT))

.PRECIOUS : $(BIN_O_FILES)


# Add any local stuff here using +=


# includes without -I
INCLUDES    += $(nses3INCLUDES) $(itgVsValSDKINCLUDE)
DEFINES     += $(VALIDATE_DEFINES)
CPPFLAGS    += $(INCLUDES:%=-I%)
CFLAGS      +=
VPATH_DIRS  =  $(SRCDIR) $(INCLUDES)
VPATH       += $(VPATH_DIRS:%=%:)

#
# The following 3 values are not set as we are not using
# -z defs options to compile the libraries. Set the libs
# related values in BIN_LD???? ( PATHS, FLAGS, LDLIBS)
#

# Override the -R option for the external project's only
CONFIG.$(HOST_ARCH_NAME).INSTALL.POINT = $(VALIDATE_LIB_LOC)

LIB_LDPATHS  += $(nsldapsdk30LIB)  $(itgVsValSDKLIB)
LIB_LDFLAGS  +=
LIB_LDLIBS   += $(LINK_itgValSDK)  \
		$(LINK_nses35)

#
# Use the IMPORT_LIB to link with the current library instead of
# $(LINK_<this_library>); Add the std libs at the last
#
BIN_LDPATHS += 
BIN_LDFLAGS +=
BIN_LDLIBS  += $(IMPORT_LIB)


#
# Add  your list of files to delete here. The config files already
# know how to delete some stuff, so you may want to just run 'make
# clean'  first  to  see  what gets missed. 'make clobber' already
# includes 'make clean'
#
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ $(DESTDIR)/$(LDAP_$(TARCH)_LIB) $(DESTDIR)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)


#
# Windows needs .lib for linking with .dll. So for winnt we have
# to copy both to install location
#

#SPECIAL_winnt_INSTALL_LOCAL = $(INSTALL_SH) $(IMPORT_LIB) $(LOCAL_INSTALL_LIB_LOC)

orig-all: $(ARCH) $(WAIT) $(DLIB) $(BIN_FILES)
all: release install-local

install-local: orig-all
	@$ mkdir -p $(LOCAL_INSTALL_LIB_LOC)
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local install ---> dynamic libvsvaln "
	@$(INSTALL_SH) -m 555 $(DLIB) $(LOCAL_INSTALL_LIB_LOC)
	-@$ mkdir -p $(DESTDIR)
	-@$(INSTALL_SH) -m 555 $(DLIB) $(DESTDIR)
	-@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/$(LDAP_$(TARCH)_LIB) $(DESTDIR)
	-@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/libvsvalsdk$(DLIB_EXT) $(DESTDIR) 
	@$(SPECIAL_$(TARCH)_INSTALL_LOCAL)
	@$(ECHO) ""

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local uninstall ---> dynamic libvsvaln "
	$(RM) $(LOCAL_INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
	$(RM) $(LOCAL_INSTALL_LIB_LOC)/$(LIBNAME)$(SLIB_EXT)
	$(RM) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
	$(RM) $(DESTDIR)/$(LDAP_$(TARCH)_LIB)
	$(RM) $(DESTDIR)/libvsvalsdk$(DLIB_EXT)
	@$(ECHO) ""

install-ecas: all
#	@$(create-install-ecas-directories)
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS install ---> dynamic libvsvaln "
#	@$(INSTALL_SH) -m 555 $(DLIB) $(INSTALL_LIB_LOC)
#	@$(ECHO) ""



uninstall-ecas:
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS uninstall ---> dynamic libvsvaln "
#	$(RM) $(INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
#	@$(ECHO) ""



depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.

$(ARCH)/nsapival.o: ../../../../../../../../itgclient/thirdparty/vsvalsdk/include/vsvalsdk.h
$(ARCH)/nsapival.o: ../../../cvmglobal.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/base/pblock.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/nsapi.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/base/systems.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/base/session.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/frame/req.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/frame/protocol.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/frame/http.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/frame/conf.h
$(ARCH)/nsapival.o: ../../../../../../../../thirdparty/nsES30/sparc/include/base/util.h
$(ARCH)/cvmglobal.o: ../../../cvmglobal.h

#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.4.12.3 2005/07/12 01:24:22 ppassanha Exp $
#

#
# make for  mod_pta.so
#

ECAS_HOME=../../../../../../../..


#
# This library name withoout extension
#
LIBNAME=mod_vsval
DESTDIR=$(CDINSTALL)/../server/cvm/stronghold/bin
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
CONFIG.hpux.CC=$(ECAS_COMPILER_DIR)/Hpux110_linkld.cfg
CONFIG.hpux.LIBRULES=$(ECAS_RULES_DIR)/Hpux110_linkld.cfg
include $(ECAS_COMMON_DIR)/lib.cfg

#
# Override compiler to compile .c files with C++
#cc=gcc


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
C_PIECES     = $(SRCDIR)/mod_vsval $(SRCDIR)/cvmglobal \
               $(SRCDIR)/vs_cvm_genlib \
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


SRCS=$(C_FILES) $(CC_FILES) $(CPP_FILES)
OBJS=$(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES)

# Binary programs

BIN_PIECES =
BIN_FNAMES = $(notdir $(BIN_PIECES))      # strip path
BIN_O_FILES= $(BIN_FNAMES:%=$(ARCH)/%.o)
BIN_FILES  = $(BIN_FNAMES:%=$(ARCH)/%$(BIN_EXT))

.PRECIOUS : $(BIN_O_FILES)


# Add any local stuff here using +=


# includes without -I
INCLUDES    += $(apacheINCLUDE) $(itgVsValSDKINCLUDE)
DEFINES     += $(CVM_STRONGHOLD_DEFINES)
CPPFLAGS    += $(INCLUDES:%=-I%)
CFLAGS      += +e -DEAPI
VPATH_DIRS  =  $(SRCDIR) $(INCLUDES)
VPATH       += $(VPATH_DIRS:%=%:)

#
# The following 3 values are not set as we are not using
# -z defs options to compile the libraries. Set the libs
# related values in BIN_LD???? ( PATHS, FLAGS, LDLIBS)
#

# Override the -R option for the external project's only
CONFIG.$(HOST_ARCH_NAME).INSTALL.POINT = $(CVM_LIB_LOC)

LIB_LDPATHS  += $(itgVsValSDKLIB)
LIB_LDFLAGS  += -lpthread
LIB_LDLIBS   += $(LINK_itgValSDK)

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
ifeq ($(TARCH), linux)
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ $(DESTDIR)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
else
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ $(DESTDIR)/$(LDAP_$(TARCH)_LIB) $(DESTDIR)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
endif

#
# Windows needs .lib for linking with .dll. So for winnt we have
# to copy both to install location
#

#SPECIAL_winnt_INSTALL_LOCAL = $(INSTALL_SH) $(IMPORT_LIB) $(LOCAL_INSTALL_LIB_LOC)


orig-all: $(ARCH) $(WAIT) $(DLIB) $(BIN_FILES)
all: release install-local
cdinstall: all

ifeq ($(TARCH), linux)
install-local: orig-all
	@$(ECHO) "$(ME):Local install ---> dynamic mod_vsval "
	@mkdir -p $(LOCAL_INSTALL_LIB_LOC)
	@$(INSTALL_SH) -m 555 $(DLIB) $(LOCAL_INSTALL_LIB_LOC)
	@$(SPECIAL_$(TARCH)_INSTALL_LOCAL)
	@mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(DLIB) $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)             
	@$(ECHO) ""
else
install-local: orig-all
	@$(ECHO) "$(ME):Local install ---> dynamic mod_vsval "
	@mkdir -p $(LOCAL_INSTALL_LIB_LOC)
	@$(INSTALL_SH) -m 555 $(DLIB) $(LOCAL_INSTALL_LIB_LOC)
	@$(SPECIAL_$(TARCH)_INSTALL_LOCAL)
	@mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(DLIB) $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/$(LDAP_$(TARCH)_LIB) $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)             
	@$(ECHO) ""
endif

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local uninstall ---> dynamic mod_vsval"
	$(RM) $(LOCAL_INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
	$(RM) $(LOCAL_INSTALL_LIB_LOC)/$(LIBNAME)$(SLIB_EXT)
	$(RM) $(DESTDIR)/$(LIBNAME)$(SLIB_EXT)
	@$(ECHO) ""

install-ecas: all
#	@$(create-install-ecas-directories)
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS install ---> dynamic mod_vsval "
#	@$(INSTALL_SH) -m 555 $(DLIB) $(INSTALL_LIB_LOC)
#	@$(ECHO) ""



uninstall-ecas:
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS uninstall ---> dynamic mod_vsval "
#	$(RM) $(INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
#	@$(ECHO) ""



depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.



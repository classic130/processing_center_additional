#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.3.10.4 2005/03/28 09:55:48 ppassanha Exp $
#

#
# make for  libvsptan.so
#

ECAS_HOME=../../../../../../../..


#
# This library name withoout extension
#
LIBNAME=libvsptan

DESTDIR=$(CDINSTALL)/../server/pta/netscape/bin
LDAP_winnt_LIB=nsldapssl32v30.dll
LDAP_sparc_LIB=libldapssl30.so
LDAP_hpux_LIB=libldapssl30.sl     
LDAP_aix_LIB=libldapssl30.so

# Begin Change : Fix for CR30756, Porting to Linux
LDAP_linux_LIB=libldap.so.2
LINK_ldap=-lldap
# End Change : Fix for CR30756, Porting to Linux

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

# .c files
C_PIECES     = $(SRCDIR)/cookie	$(SRCDIR)/nsapiCDR \
               $(SRCDIR)/pta $(SRCDIR)/nsapissc $(SRCDIR)/escape 
               
           
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
RC_PIECES   = $(SRCDIR)/nsapipta
RC_FNAMES   = $(notdir $(RC_PIECES))    # strip path
RC_FILES    = $(RC_PIECES:%=%.rc)
RC_O_FILES  = $(RC_FNAMES:%=$(ARCH)/%.res)
endif

SRCS=$(C_FILES) $(CC_FILES) $(CPP_FILES) $(RC_FILES)
OBJS=$(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES) $(RC_O_FILES)

# Binary programs

BIN_PIECES =
BIN_FNAMES = $(notdir $(BIN_PIECES))      # strip path
BIN_O_FILES= $(BIN_FNAMES:%=$(ARCH)/%.o)
BIN_FILES  = $(BIN_FNAMES:%=$(ARCH)/%$(BIN_EXT))

.PRECIOUS : $(BIN_O_FILES)


# Add any local stuff here using +=


# includes without -I
INCLUDES    += $(nses3INCLUDES) $(itgVsValSDKINCLUDE)
DEFINES     += $(SSC_DEFINES)
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
CONFIG.$(HOST_ARCH_NAME).INSTALL.POINT = $(SSC_LIB_LOC)

LIB_LDPATHS  += $(itgVsValSDKLIB)
LIB_LDFLAGS  +=
# Begin Change : Fix for CR30756, Porting to Linux
ifeq ($(TARCH), linux)
LIB_LDLIBS   += $(LINK_nses35) $(NOLINK_libcd) $(LINK_itgValSDK) $(LINK_ldap)
else
LIB_LDLIBS   += $(LINK_nses35) $(NOLINK_libcd) $(LINK_itgValSDK)
endif
# End Change : Fix for CR30756, Porting to Linux


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
# Begin Change : Fix for CR30756, Porting to Linux
ifeq ($(TARCH), linux)
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ $(DESTDIR)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
else
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ $(DESTDIR)/$(LDAP_$(TARCH)_LIB) $(DESTDIR)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
endif
# End Change : Fix for CR30756, Porting to Linux

#
# Windows needs .lib for linking with .dll. So for winnt we have
# to copy both to install location
#

SPECIAL_winnt_INSTALL_LOCAL = $(INSTALL_SH) $(IMPORT_LIB) $(LOCAL_INSTALL_LIB_LOC)


all: $(ARCH) $(WAIT) $(DLIB) $(BIN_FILES)


install-local: all
	@$ mkdir -p $(LOCAL_INSTALL_LIB_LOC)
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local install ---> dynamic libvsptan "
	@$(INSTALL_SH) -m 555 $(DLIB) $(LOCAL_INSTALL_LIB_LOC)
	@$ mkdir -p $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(DLIB) $(DESTDIR)
# Begin Change : Fix for CR30756, Porting to Linux
ifneq ($(TARCH), linux)
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/$(LDAP_$(TARCH)_LIB) $(DESTDIR)
endif
# End Change : Fix for CR30756, Porting to Linux
	@$(INSTALL_SH) -m 555 $(ECAS_HOME)/itgclient/thirdparty/vsvalsdk/lib/$(TARCH)/libvsvalsdk$(DLIB_EXT) $(DESTDIR)
	@$(SPECIAL_$(TARCH)_INSTALL_LOCAL)
	@$(ECHO) ""

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local uninstall ---> dynamic libvsptan "
	$(RM) $(LOCAL_INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
	$(RM) $(LOCAL_INSTALL_LIB_LOC)/$(LIBNAME)$(SLIB_EXT)
	$(RM) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
# Begin Change : Fix for CR30756, Porting to Linux
ifneq ($(TARCH), linux)
	$(RM) $(DESTDIR)/$(LDAP_$(TARCH)_LIB)
endif
# End Change : Fix for CR30756, Porting to Linux
	$(RM) $(DESTDIR)/libvsvalsdk$(DLIB_EXT)
	@$(ECHO) ""

install-ecas: all
#	@$(create-install-ecas-directories)
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS install ---> dynamic libvsptan "
#	@$(INSTALL_SH) -m 555 $(DLIB) $(INSTALL_LIB_LOC)
#	@$(ECHO) ""



uninstall-ecas:
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS uninstall ---> dynamic libvsptan "
#	$(RM) $(INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
#	@$(ECHO) ""



depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.



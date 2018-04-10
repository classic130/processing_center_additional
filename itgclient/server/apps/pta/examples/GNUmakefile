#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.3.84.1 2003/07/22 00:54:07 sgoginen Exp $
#

#
# make for  mod_pta.so
#

ECAS_HOME=../../../../..

#
# This library name withoout extension
#
LIBNAME=pestub

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
#INSTALL_LIB_LOC       = 
#LOCAL_INSTALL_LIB_LOC = 


include $(ECAS_CUSTOM_CFG)
# override which config files to use for hpux
#CONFIG.hpux.CC=$(ECAS_COMPILER_DIR)/Hpux1020_linkld.cfg
#CONFIG.hpux.LIBRULES=$(ECAS_RULES_DIR)/Hpux1020_linkld.cfg
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

SRCDIR      = .
WARNING     = 
DEBUGMSG    = 

# .c files
C_PIECES     =  
C_FNAMES     = $(notdir $(C_PIECES))       # strip path
C_FILES      = $(C_PIECES:%=%.c)
C_O_FILES    = $(C_FNAMES:%=$(ARCH)/%.o)


# .cc files
CC_PIECES    = 
CC_FNAMES    = $(notdir $(CC_PIECES))     # strip path
CC_FILES     = $(CC_PIECES:%=%.cc)
CC_O_FILES   = $(CC_FNAMES:%=$(ARCH)/%.o)


# .cpp files
CPP_PIECES   = $(SRCDIR)/pestub
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
INCLUDES    += . 
DEFINES     += 
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
#CONFIG.$(HOST_ARCH_NAME).INSTALL.POINT = $(SSC_LIB_LOC)

LIB_LDPATHS  += 
LIB_LDFLAGS  +=
LIB_LDLIBS   += 
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
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ 



#
# Windows needs .lib for linking with .dll. So for winnt we have
# to copy both to install location
#

#SPECIAL_winnt_INSTALL_LOCAL = $(INSTALL_SH) $(IMPORT_LIB) $(LOCAL_INSTALL_LIB_LOC)


all: $(ARCH) $(WAIT) $(DLIB) $(BIN_FILES)

install-local: all
	@$(SPECIAL_$(TARCH)_INSTALL_LOCAL)
	@$(ECHO) ""

uninstall-local:
	@$(ECHO) ""
	$(RM) $(DESTDIR)/$(LIBNAME)$(DLIB_EXT)
	@$(ECHO) ""

install-ecas: all

uninstall-ecas:
#       @$(ECHO) ""
#       @$(ECHO) "$(ME):ECAS uninstall ---> dynamic pestub "
#       $(RM) $(INSTALL_LIB_LOC)/$(LIBNAME)$(DLIB_EXT)
#       @$(ECHO) ""

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


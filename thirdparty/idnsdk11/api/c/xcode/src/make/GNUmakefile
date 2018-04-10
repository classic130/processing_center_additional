#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.1.2.1 2005/04/22 23:24:17 psingal Exp $
#

#
# make for libxcode.a
#

ECAS_HOME = ../../../../../../..


#
# This library name
#
LIBNAME=libxcode


#
# Target dynamic lib for this make
#
SLIB=$(ARCH)/$(LIBNAME)$(SLIB_EXT)$(ECAS_VERS)


INSTALL_LOC_LIB    = $(ECASINSTALL)/lib
LOCAL_INSTALL_LIB_LOC = ../../../../../lib


include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/lib.cfg

#
# Override compiler to compile .c files with C++
cc=$(COMPILER_CC)


#
# C and C++ source names, if any, goes here -- minus the .c or .cc
#
# NOTE ::
#       we  are stripping any path names from the source files to create
#       the  corresponding .o file under $(ARCH) This makefile might not
#       need  this  but still the lines of code are just a template that
#       can be used in any other place
#

SRCDIR = ..

# .c files
C_PIECES     = $(SRCDIR)/nameprep          $(SRCDIR)/puny  \
               $(SRCDIR)/race              $(SRCDIR)/toxxx \
               $(SRCDIR)/util
           
C_FNAMES     = $(notdir $(C_PIECES))       # strip path
C_FILES      = $(C_PIECES:%=%.c)
C_O_FILES    = $(C_FNAMES:%=$(ARCH)/%.o)


# .CC files
CC_PIECES    =
CC_FNAMES    = $(notdir $(CC_PIECES))     # strip path
CC_FILES     = $(CC_PIECES:%=%.cc)
CC_O_FILES   = $(CC_FNAMES:%=$(ARCH)/%.o)


# .cpp files
CPP_PIECES   = 
CPP_FNAMES   = $(notdir $(CPP_PIECES))   # strip path
CPP_FILES    = $(CPP_PIECES:%=%.cpp)
CPP_O_FILES  = $(CPP_FNAMES:%=$(ARCH)/%.o)


SRCS=$(C_FILES) $(CC_FILES) $(CPP_FILES)
OBJS=$(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES)

# Add any local stuff here using +=

xcodeINCLUDE = ../../inc

INCLUDES    += $(xcodeINCLUDE)

DEFINES     +=
CPPFLAGS    += $(INCLUDES:%=-I%)
CFLAGS      +=
VPATH_DIRS  =  $(SRCDIR) $(INCLUDES)
VPATH       += $(VPATH_DIRS:%=%:)

#
# Add  your list of files to delete here. The config files already
# know how to delete some stuff, so you may want to just run 'make
# clean'  first  to  see  what gets missed. 'make clobber' already
# includes 'make clean'
#
CLEAN_ADDITIONS +=


all: $(ARCH) $(WAIT) $(SLIB)


install-local: all
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local install ---> libxcode "
	@$(create-install-local-directories)
	@$(INSTALL_SH) -m 555 $(SLIB) $(LOCAL_INSTALL_LIB_LOC);

install-ecas:
	@$(ECHO) ""
	@$(ECHO) "$(ME):ECAS install ---> libxcode "
	@$(INSTALL_SH) -m 555 $(SLIB) $(INSTALL_LOC_LIB)

# Nothing to do
uninstall-ecas:

depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	@makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	@$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg

# DO NOT DELETE THIS LINE -- make depend depends on it.


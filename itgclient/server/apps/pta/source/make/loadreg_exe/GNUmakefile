#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.2.22.1 2001/10/05 03:50:18 sbajaj Exp $
#

#
# make for binary  loadreg.exe
#

ECAS_HOME=../../../../../../..


# install and local install locations
INSTALL_BIN_LOC       = $(ECAS_HOME)/itgclient/server/bin/
LOCAL_INSTALL_BIN_LOC = $(ECAS_HOME)/itgclient/server/bin/
DESTDIR=$(CDINSTALL)/../server/pta/iis/bin/
DESTDIRCOM=$(CDINSTALL)/../server/pta/comvsssc/bin/

include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

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

SRCDIR = ../..

# .c files
c_PIECES     = $(SRCDIR)/loadreg

c_FNAMES     = $(notdir $(c_PIECES))       # strip path
c_FILES      = $(c_PIECES:%=%.c)
c_O_FILES    = $(c_FNAMES:%=$(ARCH)/%.o)

# .C files
C_PIECES     =

C_FNAMES     = $(notdir $(C_PIECES))       # strip path
C_FILES      = $(C_PIECES:%=%.C)
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

ifeq ($(TARCH), winnt)
RC_PIECES   = $(SRCDIR)/loadregpta
RC_FNAMES   = $(notdir $(RC_PIECES))    # strip path
RC_FILES    = $(RC_PIECES:%=%.rc)
RC_O_FILES  = $(RC_FNAMES:%=$(ARCH)/%.res)
endif

SRCS=$(c_FILES)   $(C_FILES)   $(CC_FILES)   $(CPP_FILES) $(RC_FILES)
OBJS=$(c_O_FILES) $(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES) $(RC_O_FILES)

# Binary programs

BIN_PIECES = $(SRCDIR)/loadreg

BIN_FNAMES = $(notdir $(BIN_PIECES))      # strip path
BIN_O_FILES= $(BIN_FNAMES:%=$(ARCH)/%.o)
BIN_FILES  = $(BIN_FNAMES:%=$(ARCH)/%.exe)

.PRECIOUS : $(BIN_O_FILES)


# Add any local stuff here using +=

# includes without -I
INCLUDES    += $(SRCDIR) $(itgVsValSDKINCLUDE) 
DEFINES     +=
CPPFLAGS    += $(INCLUDES:%=-I%)
CFLAGS      +=
VPATH_DIRS  =  $(SRCDIR) $(INCLUDES)
VPATH       += $(VPATH_DIRS:%=%:)


#
# Add the std os libs at the last
#
# Override the -R option for the external project's only
CONFIG.$(HOST_ARCH_NAME).INSTALL.POINT = $(SSC_LIB_LOC)

BIN_LDPATHS +=
BIN_LDFLAGS +=
BIN_LDLIBS  +=


#
# Add  your list of files to delete here. The config files already
# know how to delete some stuff, so you may want to just run 'make
# clean'  first  to  see  what gets missed. 'make clobber' already
# includes 'make clean'
#
CLEAN_ADDITIONS += *% *~ $(SRCDIR)/*% $(SRCDIR)/*~ 



all: $(ARCH) $(WAIT) $(BIN_FILES)



#
# Define the dependencies and rules for each binary program
#
$(BIN_FILES) : $(SRCS) $(OBJS)
	$(LINK.c) $(LD_OUTFILE) $(OBJS) $(BIN_LDLIBS)



install-local: all
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local binary install --->  loadreg.exe "
	@$ mkdir -p $(LOCAL_INSTALL_BIN_LOC)
	@$(CHATR_SH) $(BIN_FILES)
	@$(INSTALL_SH) -m 555 $(BIN_FILES) $(LOCAL_INSTALL_BIN_LOC)
	@$ mkdir -p $(DESTDIR)
	@$ mkdir -p $(DESTDIRCOM)
	@$(INSTALL_SH) -m 555 $(BIN_FILES) $(DESTDIR)
	@$(INSTALL_SH) -m 555 $(BIN_FILES) $(DESTDIRCOM)
	@$(ECHO) ""

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local binary uninstall --->  loadreg.exe "
	$(RM) $(LOCAL_INSTALL_BIN_LOC)/loadreg.exe
	$(RM) $(DESTDIR)/loadreg.exe
	$(RM) $(DESTDIRCOM)/loadreg.exe
	@$(ECHO) ""


install-ecas:
#	@$(create-install-ecas-directories)
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS binary install  ---> loadreg.exe "
#	@$(INSTALL_SH) -m 555 $(BIN_FILES) $(INSTALL_BIN_LOC)
#	@$(ECHO) ""


uninstall-ecas:
#	@$(ECHO) ""
#	@$(ECHO) "$(ME):ECAS binary uninstall --->  loadreg.exe "
#	$(RM) $(INSTALL_BIN_LOC)/loadreg.exe
#	@$(ECHO) ""



depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	@makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	@$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg



# DO NOT DELETE THIS LINE -- make depend depends on it.


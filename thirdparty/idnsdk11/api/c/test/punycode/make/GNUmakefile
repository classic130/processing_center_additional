#	GNUmakefile 
#       Developed by Raj Srinivasan
#	$Id: GNUmakefile,v 1.1.2.1 2005/04/22 23:21:20 psingal Exp $
#

#
# make for binary  punycode
#

ECAS_HOME= ../../../../../../..


# install and local install locations
INSTALL_BIN_LOC       =
LOCAL_INSTALL_BIN_LOC = ../../../../../tools/c/bin


include $(ECAS_CUSTOM_CFG)
include $(ECAS_COMMON_DIR)/leaf.cfg

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
c_PIECES     = punycode

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


SRCS=$(c_FILES)   $(C_FILES)   $(CC_FILES)   $(CPP_FILES)
OBJS=$(c_O_FILES) $(C_O_FILES) $(CC_O_FILES) $(CPP_O_FILES)

# Binary programs

BIN_PIECES = $(SRCDIR)/punycode

BIN_FNAMES = $(notdir $(BIN_PIECES))      # strip path
BIN_O_FILES= $(BIN_FNAMES:%=$(ARCH)/%.o)
BIN_FILES  = $(BIN_FNAMES:%=$(ARCH)/%.exe)

.PRECIOUS : $(BIN_O_FILES)


# Add any local stuff here using +=
xcodeINCLUDE = ../../../xcode/inc

# includes without -I
INCLUDES    += $(xcodeINCLUDE)
DEFINES     +=
CPPFLAGS    += $(INCLUDES:%=-I%)
CFLAGS      +=
VPATH_DIRS  =  $(SRCDIR) $(INCLUDES)
VPATH       += $(VPATH_DIRS:%=%:)


#
# Add the std os libs at the last
#
BIN_LDPATHS += 
BIN_LDFLAGS +=
BIN_LDLIBS  += ../../../../../lib/libxcode.so


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
	@$(create-install-local-directories)
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local binary install --->  punycode "
	mkdir -p $(LOCAL_INSTALL_BIN_LOC)
	@$(INSTALL_SH) -m 555 $(BIN_FILES) $(LOCAL_INSTALL_BIN_LOC)/punycode.exe
	@$(ECHO) ""
#	compilePkgInstrFile.pl

uninstall-local:
	@$(ECHO) ""
	@$(ECHO) "$(ME):Local binary uninstall --->  punycode "
	$(RM) $(LOCAL_INSTALL_BIN_LOC)/punycode.exe
	@$(ECHO) ""

# Nothing to do
install-ecas:
uninstall-ecas:


depend :
	@$(ECHO) ""
	@$(ECHO) "........ Making dependencies ......"
	@makedepend -f GNUmakefile -- $(CFLAGS) $(CPPFLAGS) -- $(SRCS) > .depend.txt 2>&1
	@$(cleandepend)


include $(ECAS_COMMON_DIR)/librules.cfg


# DO NOT DELETE THIS LINE -- make depend depends on it.


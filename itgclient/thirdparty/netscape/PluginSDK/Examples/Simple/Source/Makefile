#! gmake

DEPTH = ../../../..

LIBTARGETS = $(OBJDIR)/npsimple.so
TARGETS = targets

CSRCS = npsimple.c stubs.c
OBJS  = $(CSRCS:.c=.o)

# Rules to build generated headers

JRI_HEADER_CLASSES =	       \
	Simple		       \
	netscape.plugin.Plugin \

JRI_STUB_CLASSES =	       \
	Simple		       \
	netscape.plugin.Plugin \

include $(DEPTH)/config/rules.mk

CFLAGS += $(DSO_CFLAGS)

CLASSSRC := .:$(DEPTH)/sun-java/classsrc

INCLUDES += -I_gen

targets:
	@$(MAKE) classes
	@$(MAKE) jri_headers jri_stubs
	@$(MAKE) libtargets

JAVAC =	$(JAVAI) -classpath /usr/local/netscape/java/lib/javac.zip \
	     -ms8m sun.tools.javac.Main

classes: Simple.java
	$(JAVAC) -classpath $(CLASSSRC) Simple.java

libtargets: $(LIBTARGETS)

$(OBJDIR)/npsimple.so: $(OBJS)
	$(LD) $(DSO_LDOPTS) -o $@ $(OBJS) $(DSO_LDFLAGS)

install:: $(TARGETS)
	$(INSTALL) $(TARGETS) $(DIST)/bin

INCLUDES += -I$(DEPTH)/lib/plugin
GARBAGE += so_locations

clobber::
	rm -rf _gen _stubs so_locations

export:: targets
	$(INSTALL) $(LIBTARGETS) $(DIST)/lib

install:: export

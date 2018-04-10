#	GNUmakefile 
#	$Id: GNUmakefile,v 1.3.112.1 2006/07/06 06:14:08 vmalhotra Exp $
#

.IGNORE:

all: release

release:
	case `uname` in Linux) make -f Makefile.Linux release;; *) make -f Makefile.others release;; esac

Release: release

debug:
	case `uname` in Linux) make -f Makefile.Linux debug;; *) make -f Makefile.others debug;; esac

Debug: debug

clean:
	case `uname` in Linux) make -f Makefile.Linux clean;; *) make -f Makefile.others clean;; esac

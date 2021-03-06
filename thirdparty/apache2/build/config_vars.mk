exp_exec_prefix = /usr/local/apache2
exp_bindir = /usr/local/apache2/bin
exp_sbindir = /usr/local/apache2/bin
exp_libdir = /usr/local/apache2/lib
exp_libexecdir = /usr/local/apache2/modules
exp_mandir = /usr/local/apache2/man
exp_sysconfdir = /usr/local/apache2/conf
exp_datadir = /usr/local/apache2
exp_installbuilddir = /usr/local/apache2/build
exp_errordir = /usr/local/apache2/error
exp_iconsdir = /usr/local/apache2/icons
exp_htdocsdir = /usr/local/apache2/htdocs
exp_manualdir = /usr/local/apache2/manual
exp_cgidir = /usr/local/apache2/cgi-bin
exp_includedir = /usr/local/apache2/include
exp_localstatedir = /usr/local/apache2
exp_runtimedir = /usr/local/apache2/logs
exp_logfiledir = /usr/local/apache2/logs
exp_proxycachedir = /usr/local/apache2/proxy
SHLTCFLAGS = -prefer-pic
LTCFLAGS = -prefer-non-pic -static
MKINSTALLDIRS = /usr/local/apache2/build/mkdir.sh
INSTALL = $(LIBTOOL) --mode=install /usr/local/apache2/build/install.sh -c
SSL_LIBS = -lssl -lcrypto -lsocket -lnsl -ldl
MPM_NAME = prefork
INSTALL_DSO = yes
progname = httpd
OS = unix
SHLIBPATH_VAR = LD_LIBRARY_PATH
AP_BUILD_SRCLIB_DIRS = apr apr-util pcre
AP_CLEAN_SRCLIB_DIRS = apr-util apr pcre
bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/bin
cgidir = ${datadir}/cgi-bin
logfiledir = ${localstatedir}/logs
exec_prefix = ${prefix}
datadir = ${prefix}
localstatedir = ${prefix}
mandir = ${prefix}/man
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/modules
htdocsdir = ${datadir}/htdocs
manualdir = ${datadir}/manual
includedir = ${prefix}/include
errordir = ${datadir}/error
iconsdir = ${datadir}/icons
sysconfdir = ${prefix}/conf
installbuilddir = ${datadir}/build
runtimedir = ${localstatedir}/logs
proxycachedir = ${localstatedir}/proxy
other_targets =
progname = httpd
prefix = /usr/local/apache2
AWK = gawk
CC = gcc
CPP = gcc -E
CXX = g++
CPPFLAGS = -I/usr/local/include -I/usr/local/ssl/include -I/usr/local/include/ncurses -I/usr/openwin/include -I/usr/local/rrdtool-1.2.19/include -I/usr/local/BerkeleyDB.4.7/include -I/usr/local/include/lzo
CFLAGS = -O2 -L/usr/local/lib -R/usr/local/lib -L/usr/local/ssl/lib -R/usr/local/ssl/lib -L/usr/openwin/lib -R/usr/openwin/lib -I/usr/local/rrdtool-1.2.19/include -I/usr/local/BerkeleyDB.4.7/include
CXXFLAGS = -fpermissive -felide-constructors
LTFLAGS = --silent
LDFLAGS = -L/usr/local/lib -R/usr/local/lib -R/usr/lib -L/usr/lib -R/usr/openwin/lib -L/usr/openwin/lib -L/usr/local/ssl/lib -R/usr/local/ssl/lib -L/usr/X11R6/lib -R/usr/X11R6/lib -L/usr/local/BerkeleyDB.4.7/lib -R/usr/local/BerkeleyDB.4.7/lib
LT_LDFLAGS =
SH_LDFLAGS =
LIBS =
DEFS =
INCLUDES =
NOTEST_CPPFLAGS =
NOTEST_CFLAGS =
NOTEST_CXXFLAGS =
NOTEST_LDFLAGS =
NOTEST_LIBS =
EXTRA_CPPFLAGS = -DSOLARIS2=10 -D_POSIX_PTHREAD_SEMANTICS -D_REENTRANT -D_LARGEFILE64_SOURCE
EXTRA_CFLAGS =
EXTRA_CXXFLAGS =
EXTRA_LDFLAGS =
EXTRA_LIBS = -lm
EXTRA_INCLUDES = -I$(includedir) -I. -I/bigdisk/SOURCES/S10/httpd-2.2.16/srclib/apr/include -I/bigdisk/SOURCES/S10/httpd-2.2.16/srclib/apr-util/include -I/usr/local/include -I/usr/local/ssl/include
LIBTOOL = /usr/local/apache2/build/libtool --silent
SHELL = /usr/local/bin/bash
RSYNC = /usr/local/bin/rsync
SH_LIBS =
SH_LIBTOOL = $(LIBTOOL)
MK_IMPLIB =
MKDEP = $(CC) -MM
INSTALL_PROG_FLAGS =
APR_BINDIR = /usr/local/apache2/bin
APR_INCLUDEDIR = /usr/local/apache2/include
APR_VERSION = 1.4.2
APR_CONFIG = /usr/local/apache2/bin/apr-1-config
APU_BINDIR = /usr/local/apache2/bin
APU_INCLUDEDIR = /usr/local/apache2/include
APU_VERSION = 1.3.9
APU_CONFIG = /usr/local/apache2/bin/apu-1-config

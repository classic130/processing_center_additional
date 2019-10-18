#
# Configuration file for using the XML library in GNOME applications
#
XML2_LIBDIR="-L${libdir} -R${exec_prefix}/lib"
XML2_LIBS="-lxml2 -lz -lpthread  -lm -lsocket -lnsl "
XML2_INCLUDEDIR="-I${includedir}/libxml2"
MODULE_VERSION="xml2-2.4.26"


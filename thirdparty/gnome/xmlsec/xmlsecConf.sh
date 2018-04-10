#
# Configuration file for using the XML library in GNOME applications
#
XMLSEC_LIBDIR="-L${libdir}"
XMLSEC_LIBS="-lxmlsec -L/usr/local/libxml/sparc/lib -R/usr/local/libxml/sparc/lib -lxml2 -lz -lpthread -lm -lsocket -lnsl"
XMLSEC_INCLUDEDIR="-I${prefix}/include  -I/home/ohoang/work/aaa/thirdparty/gnome/libxml2/include/libxml2"
MODULE_VERSION="xmlsec-0.0.7"


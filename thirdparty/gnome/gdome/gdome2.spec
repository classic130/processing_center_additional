%define nam     gdome2
%define ver     0.7.2
%define rel     1


Summary:        DOM level2 library for accessing XML files
Name:           %nam
Version:        %ver
Release:        %rel
Copyright:      LGPL
Group:          Development/Libraries
URL:            http://phd.cs.unibo.it/gdome2/
Source:         http://phd.cs.unibo.it/gdome2/tarball/%{nam}-%{ver}.tar.gz
BuildRoot:      /var/tmp/%{nam}-%{ver}-root

BuildRequires:  libxml2-devel >= 2.4.21
BuildRequires:  glib >= 1.2.10
Requires:       glib >= 1.2.10
Requires:       libxml2 >= 2.4.21

%description 
  gdome2  is a fast, light  and  complete  DOM level2  implementation
based on libxml2. Although it has been written for the GNOME project,
it can be used stand-alone.
  A  DOM implementation  (also called  a host implementation) is what
makes a parsed  XML or HTML document available for processing via the
DOM interface.
  gdome2   currently   supports  the  "Core",  "XML",   "Events"  and
"MutationEvents"  modules   from   the   DOM2   Recommendation   (see
http://www.w3.org/TR/DOM-Level-2-Core/ and http://www.w3.org/TR/DOM-L
evel-2-Events/), and  is supposed to become  a full implementation of
all the DOM Level2 standard.
  Now gdome2  also partially  supports the XPath  module from the DOM
level 3 drafts.

%package devel
Summary: Development files for gdome2
Group: Development/Libraries
Requires: gdome2 = %{ver}
Requires: glib-devel >= 1.2.10
Requires: libxml2-devel >= 2.4.21

%description devel
  This  package  contains the header  files and static  libraries for
developing with gdome2.
  gdome2  is a fast, light  and  complete  DOM level2  implementation
based on libxml2. Although it has been written for the GNOME project,
it can be used stand-alone.
  A  DOM implementation  (also called  a host implementation) is what
makes a parsed  XML or HTML document available for processing via the
DOM interface.
  gdome2   currently   supports  the  "Core",  "XML",   "Events"  and
"MutationEvents"  modules   from   the   DOM2   Recommendation   (see
http://www.w3.org/TR/DOM-Level-2-Core/ and http://www.w3.org/TR/DOM-L
evel-2-Events/), and  is supposed to become  a full implementation of
all the DOM Level2 standard.
  Now gdome2  also partially  supports the XPath  module from the DOM
level 3 drafts.

%changelog
* Sun Mar 31 2002 Paolo Casarini <paolo@casarini.org>
  - updated descriptions and summaries
* Sat Dec 15 2001 Paolo Casarini <paolo@casarini.org>
  - updated descriptions and summaries
* Tue Oct 23 2001 Paolo Casarini <paolo@casarini.org>
  - added the gdome-config.1 man page
* Mon Aug 6 2001 Paolo Casarini <paolo@casarini.org>
  - Merge of the Andrew release with mine
* Thu Aug 2 2001 Andrew Chatham <andrew.chatham@duke.edu>
  - Spec file created
* Tue Jul 3 2001 Paolo Casarini <paolo@casarini.org>
  - Initial release

%prep
%setup -q

%build
if [ ! -f configure ]; then
  ./autogen.sh --prefix=%{_prefix} --localstatedir=/var/lib
fi

%configure --localstatedir=/var/lib

if [ "$SMP" != "" ]; then
  (make "MAKE=make -k -j $SMP"; exit 0)
  make
else
  make
fi

make

%install
rm -rf $RPM_BUILD_ROOT
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-, root, root)
%doc AUTHORS MAINTAINERS ChangeLog INSTALL NEWS README COPYING COPYING.LIB
%{_libdir}/lib*.so.*

%files devel
%doc gtk-doc/html/*.html
%doc /usr/share/man/man1/gdome-config.1*
%defattr(-, root, root)
%{_bindir}/gdome-config
%{_includedir}/*
%{_libdir}/lib*.so
%{_libdir}/*a
%{_libdir}/*.sh

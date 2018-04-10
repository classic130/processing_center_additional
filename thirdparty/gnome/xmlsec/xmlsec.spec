Summary: Library providing support for "XML Signature" and "XML Encryption" standards
Name: xmlsec
Version: 0.0.7
Release: 1
License: MIT
Group: Development/Libraries
Vendor: Aleksey Sanin <aleksey@aleksey.com>
Distribution:  Aleksey Sanin <aleksey@aleksey.com>
Packager: Aleksey Sanin <aleksey@aleksey.com>
Source: ftp://ftp.aleksey.com/pub/xmlsec/releases/xmlsec-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-root
URL: http://www.aleksey.com/xmlsec
Requires: libxml2 >= 2.4.23
Requires: libxslt >= 1.0.19
Requires: openssl >= 0.9.6
BuildRequires: libxml2-devel >= 2.4.23
BuildRequires: libxslt-devel >= 1.0.19
BuildRequires: openssl-devel >= 0.9.6
Prefix: %{_prefix}
Docdir: %{_docdir}

%description
XML Security Library is a C library based on LibXML2  and OpenSSL. 
The library was created with a goal to support major XML security 
standards "XML Digital Signature" and "XML Encryption". 

%package devel 
Summary: Libraries, includes, etc. to develop applications with XML Digital Signatures and XML Encryption support.
Group: Development/Libraries 
Requires: xmlsec = %{version}
Requires: libxml2-devel >= 2.4.23
Requires: libxslt-devel >= 1.0.19
Requires: openssl-devel >= 0.9.6
Requires: zlib-devel 

%description devel
Libraries, includes, etc. you can use to develop applications with XML Digital 
Signatures and XML Encryption support.

%prep
%setup -q

%build
# Needed for snapshot releases.
if [ ! -f configure ]; then
%ifarch alpha
  CFLAGS="$RPM_OPT_FLAGS" ./autogen.sh --host=alpha-redhat-linux --prefix=%prefix --sysconfdir="/etc" --mandir=%{_mandir}
%else
  CFLAGS="$RPM_OPT_FLAGS" ./autogen.sh --prefix=%prefix --sysconfdir="/etc" --mandir=%{_mandir}
%endif
else
%ifarch alpha
  CFLAGS="$RPM_OPT_FLAGS" ./configure --host=alpha-redhat-linux --prefix=%prefix --sysconfdir="/etc" --mandir=%{_mandir}
%else
  CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=%prefix --sysconfdir="/etc" --mandir=%{_mandir}
%endif
fi
if [ "$SMP" != "" ]; then
  (make "MAKE=make -k -j $SMP"; exit 0)
  make
else
  make
fi

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/usr/bin
mkdir -p $RPM_BUILD_ROOT/usr/include
mkdir -p $RPM_BUILD_ROOT/usr/lib
mkdir -p $RPM_BUILD_ROOT/usr/man/man1
make prefix=$RPM_BUILD_ROOT%{prefix} mandir=$RPM_BUILD_ROOT%{_mandir} install

%clean
rm -rf $RPM_BUILD_ROOT

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files 
%defattr(-, root, root)

%doc AUTHORS ChangeLog NEWS README Copyright
%{prefix}/lib/lib*.so.*
%{prefix}/lib/lib*.so
%{prefix}/bin/xmlsec

%files devel
%defattr(-, root, root)  

%{prefix}/lib/*a
%{prefix}/bin/xmlsec-config
%{prefix}/include/*
%doc docs/* 

%changelog

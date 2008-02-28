%define name libgea2
%define MAJOR_VERSION 2
%define version 2.3

Name: %{name}
Version: %{version}
Release: 1
Summary: The GEA library 
Group: System/
URL: http://awds.berlios.de
Buildroot: /var/tmp/%{name}-buildroot
Source: http://schiess.mich.tot/%{name}-%{version}.tar.gz
License: LGPL
#BuildRequires: zlib-devel gcc >= 3.0-0 gcc-c++ >= 3.0-0 

%description
 The GEA libray provides an abstraction layer for network protocols.
 Functions , e.g. like sending packets, are provided and mapped to the
 underlying system. This is by default the POSIX-API. But other
 platforms can also provide an implementation. Currently such an
 implementation exists for the ns-2. This allow protocols developed
 with GEA to run on native POSIX platforms (like Linux or Unix). But
 the same implementation can be used in the ns-2 network simulator. By
 this the protocol implementation can be tested in large simulated
 networks.


%define debug_package %{nil}

%prep
%setup -q -n %{name}-%{version}

%build
#./prepare.pl
./configure --prefix=%{_prefix} --exec_prefix=%{_exec_prefix} --infodir=%{_infodir}
make

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_exec_prefix}/lib/libgea%{MAJOR_VERSION}*.so.*
%{_prefix}/bin/gea_start


%package devel
Summary:        GEA development files
Group:          Development/Library
Requires:       libgea

%description devel
Development files for libgea


%files devel 
%defattr(-,root,root)
%{_exec_prefix}/lib/libgea%{MAJOR_VERSION}*.so
%{_exec_prefix}/lib/libgea%{MAJOR_VERSION}*.la
%{_exec_prefix}/lib/libgea%{MAJOR_VERSION}*.a
%{_exec_prefix}/lib/pkgconfig/gea.pc
%{_prefix}/include/gea




Name:       capi-content-media-content
Summary:    A Media content library in SLP C API
Version:    0.2.61
Release:    0
Group:      Multimedia/API
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001:     capi-content-media-content.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(libmedia-service)
BuildRequires:  pkgconfig(media-thumbnail)
BuildRequires:  pkgconfig(libmedia-utils)
BuildRequires:  pkgconfig(libtzplatform-config)

%description
A Media content library in SLP C API package.

%package devel
Summary:  A Media content library in SLP C API (Development)
Group:    Development/Multimedia
Requires: %{name} = %{version}-%{release}

%description devel
A Media content library in SLP C API (Development) package.
%devel_desc

%prep
%setup -q
cp %{SOURCE1001} .

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}
%__make %{?jobs:-j%jobs}

%install
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%license LICENSE.APLv2.0
%{_libdir}/libcapi-content-media-content.so.*

%files devel
%manifest %{name}.manifest
%{_includedir}/media-content/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-content-media-content.so

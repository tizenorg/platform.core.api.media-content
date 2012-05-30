Name:       capi-content-media-content
Summary:    A Media content library in SLP C API
Version: 0.1.0
Release:    19
Group:      TO_BE/FILLED_IN
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: packaging/capi-content-media-content.manifest 
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(drm-service)
BuildRequires:  pkgconfig(aul)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(libmedia-service)


Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description


%package devel
Summary:  A Media content library in Tizen Native API (Development)
Group:    TO_BE/FILLED_IN
Requires: %{name} = %{version}-%{release}

%description devel

%prep
%setup -q


%build
cp %{SOURCE1001} .
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`
cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-content-media-content.manifest
%{_libdir}/libcapi-content-media-content.so.*

%files devel
%manifest capi-content-media-content.manifest
%{_includedir}/media-content/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-content-media-content.so



Name:       capi-content-media-content
Summary:    A Media content library in Tizen Native API
Version:    0.2.78
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
BuildRequires:  pkgconfig(vconf)
BuildRequires:  pkgconfig(libtzplatform-config)
BuildRequires:  pkgconfig(cynara-client)
BuildRequires:  pkgconfig(cynara-session)

%description
A Media content library in Tizen Native API.

%package devel
Summary:  A Media content library in Tizen Native API (Development)
Group:    Multimedia/Development
Requires: %{name} = %{version}-%{release}

%description devel
A Media content library in Tizen Native API. (Development file included)
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

#License
mkdir -p %{buildroot}/%{_datadir}/license
cp -rf %{_builddir}/%{name}-%{version}/LICENSE.APLv2.0 %{buildroot}/%{_datadir}/license/%{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%{_libdir}/libcapi-content-media-content.so.*
#License
%{_datadir}/license/%{name}

%files devel
%manifest %{name}.manifest
%{_includedir}/media-content/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-content-media-content.so

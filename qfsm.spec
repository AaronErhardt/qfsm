Name: qfsm
Summary: A graphical tool for designing finite state machines
Version: 0.54.0
Release: 1
License: GPL
Group: Development/Tools
Source: %{name}-%{version}.tar.bz2

BuildRoot: %{_tmppath}/build-root-%{name}
Packager: Stefan Duffner
Distribution: openSUSE 13.2
Prefix: /usr
Url: http://qfsm.sourceforge.net


Requires: libqt4 libqt4-x11 libqt4-qt3support desktop-file-utils graphviz graphviz-gd
BuildRequires: libqt4-devel graphviz-devel

%description
Qfsm is a graphical editor for finite state machines written in C++ using Qt.

%prep
rm -rf $RPM_BUILD_ROOT 
mkdir $RPM_BUILD_ROOT

%setup -q

%build
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" \
cmake .
make -j 2

%install
make DESTDIR=$RPM_BUILD_ROOT install

cd $RPM_BUILD_ROOT

find . -type d -fprint $RPM_BUILD_DIR/file.list.%{name}.dirs
find . -type f -fprint $RPM_BUILD_DIR/file.list.%{name}.files.tmp
sed '/\/man\//s/$/.gz/g' $RPM_BUILD_DIR/file.list.%{name}.files.tmp > $RPM_BUILD_DIR/file.list.%{name}.files
find . -type l -fprint $RPM_BUILD_DIR/file.list.%{name}.libs
sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' $RPM_BUILD_DIR/file.list.%{name}.dirs > $RPM_BUILD_DIR/file.list.%{name}
sed 's,^\.,\%attr(-\,root\,root) ,' $RPM_BUILD_DIR/file.list.%{name}.files >> $RPM_BUILD_DIR/file.list.%{name}
sed 's,^\.,\%attr(-\,root\,root) ,' $RPM_BUILD_DIR/file.list.%{name}.libs >> $RPM_BUILD_DIR/file.list.%{name}


%post
PATH=/usr/local/bin:/opt/gnome/bin:/usr/bin/kde4:/opt/kde3/bin:$PATH
update-desktop-database

%postun
PATH=/usr/local/bin:/opt/gnome/bin:/usr/bin/kde4:/opt/kde3/bin:$PATH
update-desktop-database


%clean
rm -rf $RPM_BUILD_ROOT
rm -rf $RPM_BUILD_DIR/file.list.%{name}
rm -rf $RPM_BUILD_DIR/file.list.%{name}.libs
rm -rf $RPM_BUILD_DIR/file.list.%{name}.files
rm -rf $RPM_BUILD_DIR/file.list.%{name}.files.tmp
rm -rf $RPM_BUILD_DIR/file.list.%{name}.dirs

%files -f ../file.list.%{name}
%defattr(-,root,root,0755)



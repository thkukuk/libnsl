#!/bin/sh -x

rm -fv ltmain.sh config.sub config.guess config.h.in config.rpath
autopoint --force
rm -fv po/Makevars.template po/ChangeLog m4/ChangeLog
mkdir -p m4
aclocal -I m4
autoheader
libtoolize --automake --copy
automake --add-missing --copy --force
autoreconf
chmod 755 configure

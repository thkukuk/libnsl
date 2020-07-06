#!/bin/sh -x

rm -fv ltmain.sh config.sub config.guess config.h.in config.rpath
gettextize -f
rm -fv po/Makevars.template po/ChangeLog
mkdir -p m4
aclocal -I m4
autoheader
libtoolize --automake --copy
automake --add-missing --copy --force
autoreconf
chmod 755 configure

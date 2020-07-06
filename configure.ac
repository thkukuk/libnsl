dnl Process this file with autoconf to produce a configure script.
AC_INIT(libnsl, 1.3.0)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/do_ypcall.c])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])
AC_PREFIX_DEFAULT(/usr)

AC_SUBST(PACKAGE)
AC_SUBST(VERSION)

dnl Checks for programs.
AC_PROG_CC
AC_GNU_SOURCE
dnl If we're using gcc, we want warning flags
dnl test -n "$GCC" && WARNFLAGS="-Wall"
test -n "$GCC" && WARNFLAGS="-W -Wall -Wbad-function-cast -Wcast-align -Winline -Wnested-externs -Wshadow -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -Wundef"
AC_SUBST(WARNFLAGS)
AC_PROG_CPP
AC_ISC_POSIX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
LT_INIT

dnl Checks for libraries.
PKG_CHECK_MODULES([TIRPC], [libtirpc], [], [TIRPC_LIBS=""])

if test -n "$TIRPC_LIBS"; then
  AC_DEFINE(HAVE_TIRPC, 1, [Define to 1 if TIRPC is available])
fi

dnl internationalization macros
m4_ifndef([AM_GNU_GETTEXT_REQUIRE_VERSION],
  [m4_define([AM_GNU_GETTEXT_REQUIRE_VERSION], [])])
AM_GNU_GETTEXT_REQUIRE_VERSION([0.19.2])
AM_GNU_GETTEXT_VERSION([0.20.2])
AM_GNU_GETTEXT([external])

AC_OUTPUT([Makefile src/Makefile libnsl.pc po/Makefile.in])

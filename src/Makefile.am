#
# Copyright (c) 2015, 2017 Thorsten Kukuk, Germany
#
# Author: Thorsten Kukuk <kukuk@thkukuk.de>
#
# Process this file with automake to produce Makefile.in.
#

AUTOMAKE_OPTIONS = subdir-objects

CLEANFILES = *~

EXTRA_DIST = libnsl.map

localedir = $(datadir)/locale
rpcsvcdir = $(includedir)/rpcsvc

AM_CFLAGS = @WARNFLAGS@ -D_REENTRANT=1
AM_CPPFLAGS = -I$(srcdir) @TIRPC_CFLAGS@ -DLOCALEDIR=\"$(localedir)\"

rpcsvc_HEADERS = rpcsvc/ypclnt.h rpcsvc/ypupd.h rpcsvc/yp_prot.h \
	rpcsvc/yp.x rpcsvc/yp.h rpcsvc/yppasswd.x rpcsvc/yppasswd.h

noinst_HEADERS = internal.h libc-lock.h

lib_LTLIBRARIES = libnsl.la

libnsl_la_LDFLAGS = -version-info 3:0:0 \
	-Wl,--no-undefined \
	-Wl,--version-script=$(srcdir)/libnsl.map
libnsl_la_LIBADD = @TIRPC_LIBS@ @LTLIBINTL@

libnsl_la_SOURCES = yp_xdr.c do_ypcall.c ypprot_err.c yp_master.c \
	yp_maplist.c yp_order.c yp_first.c yp_next.c yp_match.c  \
	yperr_string.c ypbinderr_string.c yp_get_default_domain.c \
	taddr2host.c taddr2ipstr.c taddr2port.c

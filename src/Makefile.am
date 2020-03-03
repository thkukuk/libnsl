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
	rpcsvc/yp.x rpcsvc/yp.h rpcsvc/nis_callback.h rpcsvc/nis.h \
	rpcsvc/nis_object.x rpcsvc/nis.x rpcsvc/nis_callback.x \
	rpcsvc/nislib.h rpcsvc/nis_tags.h rpcsvc/yppasswd.x \
	rpcsvc/yppasswd.h

noinst_HEADERS = internal.h libc-lock.h nisplus/nis_intern.h nisplus/nis_xdr.h

lib_LTLIBRARIES = libnsl.la

libnsl_la_LDFLAGS = -version-info 2:1:0 \
	-Wl,--no-undefined \
	-Wl,--version-script=$(srcdir)/libnsl.map
libnsl_la_LIBADD = @TIRPC_LIBS@ @LTLIBINTL@

libnsl_la_SOURCES = yp_xdr.c do_ypcall.c ypprot_err.c yp_master.c \
	yp_maplist.c yp_order.c yp_first.c yp_next.c yp_match.c  \
	yperr_string.c ypbinderr_string.c yp_get_default_domain.c \
	taddr2host.c taddr2ipstr.c taddr2port.c \
	nisplus/nis_add.c nisplus/nis_addmember.c nisplus/nis_callback.c \
	nisplus/nis_call.c nisplus/nis_checkpoint.c nisplus/nis_clone_dir.c \
	nisplus/nis_clone_obj.c nisplus/nis_clone_res.c \
	nisplus/nis_creategroup.c nisplus/nis_defaults.c \
	nisplus/nis_destroygroup.c nisplus/nis_domain_of.c \
	nisplus/nis_domain_of_r.c nisplus/nis_error.c \
	nisplus/nis_file.c nisplus/nis_findserv.c nisplus/nis_free.c \
	nisplus/nis_getservlist.c nisplus/nis_ismember.c \
	nisplus/nis_local_names.c nisplus/nis_lookup.c nisplus/nis_mkdir.c \
	nisplus/nis_modify.c nisplus/nis_ping.c nisplus/nis_print.c \
	nisplus/nis_print_group_entry.c nisplus/nis_remove.c \
	nisplus/nis_removemember.c nisplus/nis_rmdir.c nisplus/nis_server.c \
	nisplus/nis_subr.c nisplus/nis_table.c nisplus/nis_util.c \
	nisplus/nis_verifygroup.c nisplus/nis_xdr.c

# nisplus/nis_hash.c

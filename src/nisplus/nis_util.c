/* Copyright (c) 1997-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Thorsten Kukuk <kukuk@suse.de>, 1997.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>
#include "nis_intern.h"
#include "nis_xdr.h"

fd_result *
__nis_finddirectory (directory_obj *dir, const_nis_name name)
{
  nis_error status;
  fd_args fd_arg;
  fd_result *fd_res;

  fd_arg.dir_name = (char *)name;
  fd_arg.requester = nis_local_host();
  fd_res = calloc (1, sizeof (fd_result));
  if (fd_res == NULL)
    return NULL;

  status = __do_niscall2 (dir->do_servers.do_servers_val,
			  dir->do_servers.do_servers_len,
			  NIS_FINDDIRECTORY, (xdrproc_t) _xdr_fd_args,
			  (caddr_t) &fd_arg, (xdrproc_t) _xdr_fd_result,
			  (caddr_t) fd_res, NO_AUTHINFO|USE_DGRAM, NULL);
  if (status != NIS_SUCCESS)
    fd_res->status = status;

  return fd_res;
}

/* Copyright (C) 2014 Thorsten Kukuk
   Author: Thorsten Kukuk <kukuk@suse.de>

   This library is free software: you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   in version 2.1 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(HAVE_TIRPC)

#include <netdb.h>
#include <stddef.h>
#include <rpc/rpc.h>
#include <rpcsvc/yp_prot.h>

#include "internal.h"

unsigned short
taddr2port (const struct netconfig *nconf, const struct netbuf *nbuf)
{
  unsigned short port = 0;
  struct __rpc_sockinfo si;
  struct sockaddr_in *sin;
  struct sockaddr_in6 *sin6;

  if (nconf == NULL || nbuf == NULL || nbuf->len <= 0)
    return 0;

  if (!__rpc_nconf2sockinfo(nconf, &si))
    return 0;

  switch (si.si_af)
    {
    case AF_INET:
      sin = nbuf->buf;
      port = sin->sin_port;
      break;
    case AF_INET6:
      sin6 = nbuf->buf;
      port = sin6->sin6_port;
      break;
    default:
      break;
    }

  return htons (port);
}

#endif

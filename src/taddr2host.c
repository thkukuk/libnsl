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
#include <rpc/rpc.h>
#include <rpcsvc/yp_prot.h>

#include "internal.h"

const char *
taddr2host (const struct netconfig *nconf, const struct netbuf *nbuf,
	    char *host, size_t hostlen)
{
  int error;
  struct __rpc_sockinfo si;
  struct sockaddr_in *sin;
  struct sockaddr_in6 *sin6;

  if (nconf == NULL || nbuf == NULL || nbuf->len <= 0)
    return NULL;

  if (!__rpc_nconf2sockinfo (nconf, &si))
    return NULL;

  switch (si.si_af) {
  case AF_INET:
    sin = nbuf->buf;
    sin->sin_family = si.si_af;
    error = getnameinfo((struct sockaddr *)sin,
			sizeof (struct sockaddr_in),
			host, hostlen, NULL, 0, 0);
    if (error)
      fprintf (stderr, "getnameinfo(): %s\n",  gai_strerror(error));
    break;
  case AF_INET6:
    sin6 = nbuf->buf;
    sin6->sin6_family = si.si_af;
    error = getnameinfo((struct sockaddr *)sin6,
			sizeof (struct sockaddr_in6),
			host, hostlen, NULL, 0, 0);
    if (error)
      fprintf (stderr, "getnameinfo(): %s\n",  gai_strerror(error));
    break;
  default:
    error = 1;
    break;
  }

  if (error)
    return NULL;
  else
    return host;
}

#endif

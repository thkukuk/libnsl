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

#include <netdb.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <rpc/rpc.h>
#include <rpcsvc/yp_prot.h>

#include "internal.h"

const char *
taddr2ipstr (const struct netconfig *nconf, const struct netbuf *nbuf,
	     char *buf, size_t buflen)
{
  struct __rpc_sockinfo si;
  struct sockaddr_in *sin;
  struct sockaddr_in6 *sin6;
  struct sockaddr_un *sun;

  if (nconf == NULL || nbuf == NULL || nbuf->len <= 0)
    return NULL;

  if (!__rpc_nconf2sockinfo(nconf, &si))
    return NULL;

  switch (si.si_af)
    {
    case AF_INET:
      sin = nbuf->buf;
      if (inet_ntop(si.si_af, &sin->sin_addr, buf, buflen) == NULL)
	return NULL;
      break;
    case AF_INET6:
      sin6 = nbuf->buf;
      if (inet_ntop(si.si_af, &sin6->sin6_addr, buf, buflen) == NULL)
	return NULL;
      break;
    case AF_LOCAL:
      sun = nbuf->buf;
      /*      if (asprintf(&ret, "%.*s", (int)(sun->sun_len -
	      offsetof(struct sockaddr_un, sun_path)),
	      sun->sun_path) < 0)*/
      if (snprintf (buf, buflen, "%.*s", (int)(sizeof(*sun) -
					       offsetof(struct sockaddr_un, sun_path)),
		    sun->sun_path) < 0)
	return NULL;
      break;
    default:
      return NULL;
      break;
    }

  return buf;
}

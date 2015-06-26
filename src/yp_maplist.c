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

#include <rpcsvc/ypclnt.h>
#include <rpcsvc/yp_prot.h>

#include "internal.h"

int
yp_maplist (const char *indomain, struct ypmaplist **outmaplist)
{
  struct ypresp_maplist resp;
  enum clnt_stat result;

  if (indomain == NULL || indomain[0] == '\0')
    return YPERR_BADARGS;

  memset (&resp, '\0', sizeof (resp));

  result = do_ypcall_tr (indomain, YPPROC_MAPLIST, (xdrproc_t) xdr_domainname,
                         (caddr_t) &indomain, (xdrproc_t) xdr_ypresp_maplist,
                         (caddr_t) &resp);

  if (result == YPERR_SUCCESS)
    {
      *outmaplist = resp.list;
      /* We don't free the list, this will be done by ypserv
         xdr_free((xdrproc_t)xdr_ypresp_maplist, (char *)&resp); */
    }

  return result;
}

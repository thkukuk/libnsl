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
yp_match (const char *indomain, const char *inmap, const char *inkey,
          const int inkeylen, char **outval, int *outvallen)
{
  ypreq_key req;
  ypresp_val resp;
  enum clnt_stat result;

  if (indomain == NULL || indomain[0] == '\0' ||
      inmap == NULL || inmap[0] == '\0' ||
      inkey == NULL || inkey[0] == '\0' || inkeylen <= 0)
    return YPERR_BADARGS;

  req.domain = (char *) indomain;
  req.map = (char *) inmap;
  req.keydat.keydat_val = (char *) inkey;
  req.keydat.keydat_len = inkeylen;

  *outval = NULL;
  *outvallen = 0;
  memset (&resp, '\0', sizeof (resp));

  result = do_ypcall_tr (indomain, YPPROC_MATCH, (xdrproc_t) xdr_ypreq_key,
                         (caddr_t) &req, (xdrproc_t) xdr_ypresp_val,
                         (ypresp_val *) &resp);

  if (result != YPERR_SUCCESS)
    return result;

  *outvallen = resp.valdat.valdat_len;
  *outval = malloc (*outvallen + 1);
  int status = YPERR_RESRC;
  if (*outval != NULL)
    {
      memcpy (*outval, resp.valdat.valdat_val, *outvallen);
      (*outval)[*outvallen] = '\0';
      status = YPERR_SUCCESS;
    }

  xdr_free ((xdrproc_t) xdr_ypresp_val, (char *) &resp);

  return status;
}

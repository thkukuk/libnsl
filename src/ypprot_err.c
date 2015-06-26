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

static const int8_t yp_2_yperr[] =
  {
#define YP2YPERR(yp, yperr)  [YP_##yp - YP_VERS] = YPERR_##yperr
    YP2YPERR (TRUE, SUCCESS),
    YP2YPERR (NOMORE, NOMORE),
    YP2YPERR (FALSE, YPERR),
    YP2YPERR (NOMAP, MAP),
    YP2YPERR (NODOM, DOMAIN),
    YP2YPERR (NOKEY, KEY),
    YP2YPERR (BADOP, YPERR),
    YP2YPERR (BADDB, BADDB),
    YP2YPERR (YPERR, YPERR),
    YP2YPERR (BADARGS, BADARGS),
    YP2YPERR (VERS, VERS)
  };

int
ypprot_err (const int code)
{
  if (code < YP_VERS || code > YP_NOMORE)
    return YPERR_YPERR;
  return yp_2_yperr[code - YP_VERS];
}

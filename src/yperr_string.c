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

#include <locale.h>
#include <libintl.h>
#include <rpcsvc/ypclnt.h>

#ifndef _
#define _(String) gettext (String)
#endif

#ifndef N_
#define N_(String) String
#endif

const char *
yperr_string (const int error)
{
  const char *str;
  switch (error)
    {
    case YPERR_SUCCESS:
      str = N_("Success");
      break;
    case YPERR_BADARGS:
      str = N_("Request arguments bad");
      break;
    case YPERR_RPC:
      str = N_("RPC failure on NIS operation");
      break;
    case YPERR_DOMAIN:
      str = N_("Can't bind to server which serves this domain");
      break;
    case YPERR_MAP:
      str = N_("No such map in server's domain");
      break;
    case YPERR_KEY:
      str = N_("No such key in map");
      break;
    case YPERR_YPERR:
      str = N_("Internal NIS error");
      break;
    case YPERR_RESRC:
      str = N_("Local resource allocation failure");
      break;
    case YPERR_NOMORE:
      str = N_("No more records in map database");
      break;
    case YPERR_PMAP:
      str = N_("Can't communicate with portmapper");
      break;
    case YPERR_YPBIND:
      str = N_("Can't communicate with ypbind");
      break;
    case YPERR_YPSERV:
      str = N_("Can't communicate with ypserv");
      break;
    case YPERR_NODOM:
      str = N_("Local domain name not set");
      break;
    case YPERR_BADDB:
      str = N_("NIS map database is bad");
      break;
    case YPERR_VERS:
      str = N_("NIS client/server version mismatch - can't supply service");
      break;
    case YPERR_ACCESS:
      str = N_("Permission denied");
      break;
    case YPERR_BUSY:
      str = N_("Database is busy");
      break;
    default:
      str = N_("Unknown NIS error code");
      break;
    }
  return _(str);
}

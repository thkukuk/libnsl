/* Copyright (c) 2018 Thorsten Kukuk

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <rpc/rpc.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#include "netdir.h"

/* if return value is boolean, we need a way to provide the error
   message. XXX not thread safe */
static int _nderror = 0;

/*
  return values:
   -1: error
   0: Success or TRUE
   1: FALSE
*/
int
netdir_options (struct netconfig *config, int option, int fd, char *argptr)
{
  switch (option)
    {
    case ND_SET_RESERVEDPORT:
      {
	struct sockaddr *sa = (struct sockaddr *)argptr;

	_nderror = ND_SYSTEM;
        if (geteuid()) {
	  errno = EACCES;
	  return -1;
        }

	return bindresvport_sa (fd, sa);
      }
    case ND_CHECK_RESERVEDPORT:
      {
	struct sockaddr_in *sin;

	if (argptr == NULL)
	  {
	    _nderror = ND_FAILCTRL;
	    return -1;
	  }

	sin = (struct socaddr_in *)(((struct netbuf *)argptr)->buf);
	if (ntohs (sin->sin_port) < IPPORT_RESERVED)
	  return 0;
	return 1;
      }
    }

  return ND_NOCTRL;
}

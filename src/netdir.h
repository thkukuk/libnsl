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

#ifndef __NETDIR_H__
#define __NETDIR_H__

#include <netconfig.h>

#ifdef  __cplusplus
extern "C" {
#endif

/* Return values */

#define ND_OK           0	/* Success */
#define ND_NOCTRL       1	/* Unknown option */
#define ND_FAILCTRL     2       /* Failure */
#define ND_SYSTEM	3	/* System error */
/*
 * Options for netdir_options, which can be given to the file descriptor.
 * A way to request reserved ports. Support is implementation and
 * transport depending.
 */

#define ND_SET_RESERVEDPORT     1       /* bind it to reserve address */
#define ND_CHECK_RESERVEDPORT   2       /* check if address is reserved */

extern int netdir_options (struct netconfig *config, int option, int fd, 
                           char *argptr);

#ifdef  __cplusplus
}
#endif

#endif  /* __NETDIR_H__ */

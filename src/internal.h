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

#ifndef _INTERNAL_H_
#define _INTERNAL_H_

extern int do_ypcall (const char *domain, u_long prog, xdrproc_t xargs,
		      caddr_t req, xdrproc_t xres, caddr_t resp);
extern int do_ypcall_tr (const char *domain, u_long prog, xdrproc_t xargs,
			 caddr_t req, xdrproc_t xres, caddr_t resp);
extern int yp_maplist (const char *, struct ypmaplist **);
#endif

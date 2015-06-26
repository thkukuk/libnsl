/* Modified and extended by Thorsten Kukuk <kukuk@thkukuk.de>, 2014 */
/*
 * Copyright (c) 2010, Oracle America, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name of the "Oracle America, Inc." nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 *   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *   GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <netconfig.h>
#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpcsvc/yp_prot.h>
#include <rpcsvc/ypclnt.h>

/* The NIS v2 protocol suggests 1024 bytes as a maximum length of all fields.
   Current Linux systems don't use this limit. To remain compatible with
   recent Linux systems we choose limits large enough to load large key and
   data values, but small enough to not pose a DoS threat. */

#define XDRMAXNAME 1024
#define XDRMAXRECORD (16 * 1024 * 1024)

bool_t
xdr_ypstat (XDR *xdrs, ypstat *objp)
{
  return xdr_enum (xdrs, (enum_t *) objp);
}

bool_t
xdr_ypxfrstat(XDR *xdrs, ypxfrstat *objp)
{
  return xdr_enum(xdrs, (enum_t *)objp);
}

bool_t
xdr_domainname (XDR *xdrs, char **objp)
{
  return xdr_string (xdrs, objp, XDRMAXNAME);
}

static bool_t /* XXX */
xdr_keydat (XDR *xdrs, keydat_t *objp)
{
  return xdr_bytes (xdrs, (char **) &objp->keydat_val,
		    (u_int *) &objp->keydat_len, XDRMAXRECORD);
}

static bool_t /* XXX */
xdr_valdat (XDR *xdrs, valdat_t *objp)
{
  return xdr_bytes (xdrs, (char **) &objp->valdat_val,
		    (u_int *) &objp->valdat_len, XDRMAXRECORD);
}

bool_t
xdr_ypmap_parms (XDR *xdrs, struct ypmap_parms *objp)
{
  if (!xdr_domainname (xdrs, &objp->domain))
    return FALSE;
  if (!xdr_string (xdrs, &objp->map, XDRMAXNAME))
    return FALSE;
  if (!xdr_u_int (xdrs, &objp->ordernum))
    return FALSE;
  return xdr_string (xdrs, &objp->owner, XDRMAXNAME);
}

bool_t
xdr_ypreq_key (XDR *xdrs, struct ypreq_key *objp)
{
  if (!xdr_domainname (xdrs, &objp->domain))
    return FALSE;
  if (!xdr_string (xdrs, &objp->map, XDRMAXNAME))
    return FALSE;
  return xdr_keydat (xdrs, &objp->keydat);
}

bool_t
xdr_ypreq_nokey (XDR *xdrs, struct ypreq_nokey *objp)
{
  if (!xdr_domainname (xdrs, &objp->domain))
    return FALSE;
  return xdr_string (xdrs, &objp->map, XDRMAXNAME);
}

bool_t
xdr_ypreq_xfr (XDR *xdrs, struct ypreq_xfr *objp)
{
  if (!xdr_ypmap_parms (xdrs, &objp->map_parms))
    return FALSE;
  if (!xdr_u_int (xdrs, &objp->transid))
    return FALSE;
  if (!xdr_u_int (xdrs, &objp->proto))
    return FALSE;
  return xdr_u_int (xdrs, &objp->port);
}

bool_t
xdr_ypreq_newxfr (XDR *xdrs, struct ypreq_newxfr *objp)
{
  if (!xdr_ypmap_parms (xdrs, &objp->map_parms))
    return FALSE;
  if (!xdr_u_int (xdrs, &objp->transid))
    return FALSE;
  if (!xdr_u_int (xdrs, &objp->proto))
    return FALSE;
  return xdr_string (xdrs, &objp->name, XDRMAXNAME);
}

bool_t
xdr_ypresp_val (XDR *xdrs, struct ypresp_val *objp)
{
  if (!xdr_ypstat (xdrs, &objp->status))
    return FALSE;
  return xdr_valdat (xdrs, &objp->valdat);
}

bool_t
xdr_ypresp_key_val (XDR *xdrs, struct ypresp_key_val *objp)
{
  if (!xdr_ypstat (xdrs, &objp->status))
    return FALSE;
  if (!xdr_valdat (xdrs, &objp->valdat))
    return FALSE;
  return xdr_keydat (xdrs, &objp->keydat);
}

bool_t
xdr_ypresp_master (XDR *xdrs, struct ypresp_master *objp)
{
  if (!xdr_ypstat (xdrs, &objp->status))
    return FALSE;
  return xdr_string (xdrs, &objp->master, XDRMAXNAME);
}

bool_t
xdr_ypresp_order (XDR *xdrs, struct ypresp_order *objp)
{
  if (!xdr_ypstat (xdrs, &objp->status))
    return FALSE;
  return xdr_u_int (xdrs, &objp->ordernum);
}

bool_t
xdr_ypresp_xfr (XDR *xdrs, ypresp_xfr *objp)
{
  if (!xdr_u_int(xdrs, &objp->transid))
    return FALSE;

  if (!xdr_ypxfrstat(xdrs, &objp->xfrstat))
    return FALSE;

  return TRUE;
}

bool_t
xdr_ypresp_all (XDR *xdrs, struct ypresp_all *objp)
{
  if (!xdr_bool (xdrs, &objp->more))
    return FALSE;
  switch (objp->more)
    {
    case TRUE:
      return xdr_ypresp_key_val (xdrs, &objp->ypresp_all_u.val);
    case FALSE:
      break;
    default:
      return FALSE;
    }
  return TRUE;
}

bool_t
xdr_ypmaplist (XDR *xdrs, struct ypmaplist *objp)
{
  char **tp;
  if (!xdr_string (xdrs, &objp->map, XDRMAXNAME))
    return FALSE;
  /* Prevent gcc warning about alias violation.  */
  tp = (void *) &objp->next;
  return xdr_pointer (xdrs, tp, sizeof (struct ypmaplist),
		      (xdrproc_t) xdr_ypmaplist);
}

bool_t
xdr_ypresp_maplist (XDR *xdrs, struct ypresp_maplist *objp)
{
  char **tp;
  if (!xdr_ypstat (xdrs, &objp->status))
    return FALSE;
  /* Prevent gcc warning about alias violation.  */
  tp = (void *) &objp->list;
  return xdr_pointer (xdrs, tp, sizeof (struct ypmaplist),
		      (xdrproc_t) xdr_ypmaplist);
}

static bool_t
xdr_yppush_status (XDR *xdrs, enum yppush_status *objp)
{
  return xdr_enum (xdrs, (enum_t *) objp);
}

bool_t
xdr_yppushresp_xfr (XDR *xdrs, struct yppushresp_xfr *objp)
{
  if (!xdr_u_int (xdrs, &objp->transid))
    return FALSE;
  return xdr_yppush_status (xdrs, &objp->status);
}

bool_t
xdr_ypbind_resptype (XDR *xdrs, enum ypbind_resptype *objp)
{
  return xdr_enum (xdrs, (enum_t *) objp);
}

bool_t
xdr_ypbind2_binding (XDR *xdrs, struct ypbind2_binding *objp)
{
  if (!xdr_opaque (xdrs, (char *)&objp->ypbind_binding_addr, 4))
    return FALSE;
  return xdr_opaque (xdrs, (char *)&objp->ypbind_binding_port, 2);
}

bool_t
xdr_ypbind2_resp (XDR *xdrs, struct ypbind2_resp *objp)
{
  if (!xdr_ypbind_resptype (xdrs, &objp->ypbind_status))
    return FALSE;
  switch (objp->ypbind_status)
    {
    case YPBIND_FAIL_VAL:
      return xdr_u_int (xdrs, &objp->ypbind_respbody.ypbind_error);
    case YPBIND_SUCC_VAL:
      return xdr_ypbind2_binding (xdrs, &objp->ypbind_respbody.ypbind_bindinfo);
    }
  return FALSE;
}

bool_t
xdr_ypbind_oldsetdom (XDR *xdrs, struct ypbind_oldsetdom *objp)
{
  if (!xdr_vector (xdrs, (char *)objp->ypoldsetdom_domain, YPMAXDOMAIN,
                   sizeof (char), (xdrproc_t) xdr_char))
    return FALSE;
  if (!xdr_ypbind2_binding (xdrs, &objp->ypoldsetdom_binding))
    return FALSE;
  return TRUE;
}

bool_t
xdr_ypbind2_setdom (XDR *xdrs, struct ypbind2_setdom *objp)
{
  if (!xdr_domainname (xdrs, &objp->ypsetdom_domain))
    return FALSE;
  if (!xdr_ypbind2_binding (xdrs, &objp->ypsetdom_binding))
    return FALSE;
  return xdr_u_int (xdrs, &objp->ypsetdom_vers);
}

/* Same values in netconfig are u_long with TI-RPC on
   Linux, but u_int on Solaris */
static bool_t
xdr_fake_u_int (XDR *xdrs, unsigned long *objp)
{
  switch (xdrs->x_op)
    {
    case XDR_DECODE:
      {
        uint32_t tmp;

        if (!xdr_u_int (xdrs, &tmp))
          return FALSE;
	*objp = tmp;
	return TRUE;
      }
    case XDR_ENCODE:
      {
	uint32_t tmp = *objp;

	if (!xdr_u_int (xdrs, &tmp))
          return FALSE;
	return TRUE;
      }
    case XDR_FREE:
      return TRUE;
    }
  return FALSE;
}

static bool_t
xdr_netconfig (XDR *xdrs, struct netconfig *objp)
{
  if (!xdr_string(xdrs, &objp->nc_netid, ~0))
    return FALSE;

  if (!xdr_fake_u_int (xdrs, &objp->nc_semantics))
    return FALSE;
  if (!xdr_fake_u_int (xdrs, &objp->nc_flag))
    return FALSE;
  if (!xdr_string (xdrs, &objp->nc_protofmly, ~0))
    return FALSE;
  if (!xdr_string (xdrs, &objp->nc_proto, ~0))
    return FALSE;
  if (!xdr_string(xdrs, &objp->nc_device, ~0))
    return FALSE;
  if (!xdr_array(xdrs, (char **)&objp->nc_lookups,
		 (uint32_t *)&objp->nc_nlookups, 100, sizeof (char *),
		 (xdrproc_t)xdr_wrapstring))
    return FALSE;
  return xdr_vector (xdrs, (char *)objp->nc_unused,
		     8, sizeof (uint32_t), (xdrproc_t)xdr_u_int);
}

#undef xdr_rpcvers
#define xdr_rpcvers(xdrs, versp) xdr_u_int32_t(xdrs, versp)

bool_t
xdr_ypbind3_binding (XDR *xdrs,  struct ypbind3_binding *objp)
{
  if (!xdr_pointer (xdrs, (char **)&objp->ypbind_nconf,
		    sizeof (struct netconfig), (xdrproc_t) xdr_netconfig))
    return FALSE;
  if (!xdr_pointer(xdrs, (char **)&objp->ypbind_svcaddr,
		   sizeof (struct netbuf), (xdrproc_t) xdr_netbuf))
    return FALSE;
  if (!xdr_string(xdrs, &objp->ypbind_servername, ~0))
    return FALSE;
  if (!xdr_rpcvers(xdrs, &objp->ypbind_hi_vers))
    return FALSE;
  return xdr_rpcvers(xdrs, &objp->ypbind_lo_vers);
}


bool_t
xdr_ypbind3_resp (XDR *xdrs, struct ypbind3_resp *objp)
{
  if (!xdr_ypbind_resptype(xdrs, &objp->ypbind_status))
    return FALSE;
  switch (objp->ypbind_status)
    {
    case YPBIND_FAIL_VAL:
      if (!xdr_fake_u_int(xdrs, &objp->ypbind_respbody.ypbind_error))
	return FALSE;
      break;
    case YPBIND_SUCC_VAL:
      if (!xdr_pointer (xdrs,
			(char **)&objp->ypbind_respbody.ypbind_bindinfo,
			sizeof (struct ypbind3_binding), (xdrproc_t) xdr_ypbind3_binding))
	return FALSE;
      break;
    default:
      return FALSE;
    }
  return TRUE;
}

bool_t
xdr_ypbind3_setdom (XDR *xdrs, ypbind3_setdom *objp)
{
  if (!xdr_string (xdrs, &objp->ypsetdom_domain, YPMAXDOMAIN))
    return FALSE;
  return xdr_pointer (xdrs, (char **)&objp->ypsetdom_bindinfo,
		      sizeof (struct ypbind3_binding), (xdrproc_t) xdr_ypbind3_binding);
}

#if 0 /* XXX */
bool_t
xdr_ypall(XDR *xdrs, struct ypall_callback *incallback)
{
    struct ypresp_key_val out;
    char key[YPMAXRECORD], val[YPMAXRECORD];

    /*
     * Set up key/val struct to be used during the transaction.
     */
    memset(&out, 0, sizeof out);
    out.key.keydat_val = key;
    out.key.keydat_len = sizeof(key);
    out.val.valdat_val = val;
    out.val.valdat_len = sizeof(val);

    for (;;) {
	bool_t more, status;

	/* Values pending? */
	if (!xdr_bool(xdrs, &more))
	    return FALSE;           /* can't tell! */
	if (!more)
	    return TRUE;            /* no more */

	/* Transfer key/value pair. */
	status = xdr_ypresp_key_val(xdrs, &out);

	/*
	 * If we succeeded, call the callback function.
	 * The callback will return TRUE when it wants
	 * no more values.  If we fail, indicate the
	 * error.
	 */
	if (status) {
	    if ((*incallback->foreach)(out.stat,
				       (char *)out.key.keydat_val, out.key.keydat_len,
				       (char *)out.val.valdat_val, out.val.valdat_len,
				       incallback->data))
		return TRUE;
	} else
	    return FALSE;
    }
}
#endif

/*
   Unix SMB/CIFS implementation.
   tdb utility functions
   Copyright (C) Andrew Tridgell 1992-1998

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "includes.h"

/* these are little tdb utility functions that are meant to make
   dealing with a tdb database a little less cumbersome in Samba */

static SIG_ATOMIC_T gotalarm;

/***************************************************************
 Signal function to tell us we timed out.
****************************************************************/

static void gotalarm_sig(void)
{
	DEBUG(1,("function ommited\n"));
/* function ommited*/
}

/****************************************************************************
 Lock a chain with timeout (in seconds).
****************************************************************************/

int tdb_chainlock_with_timeout( TDB_CONTEXT *tdb, TDB_DATA key, unsigned int timeout)
{
	/* Allow tdb_chainlock to be interrupted by an alarm. */
	int ret;
	gotalarm = 0;
	tdb_set_lock_alarm(&gotalarm);

	if (timeout) {
		CatchSignal(SIGALRM, SIGNAL_CAST gotalarm_sig);
		alarm(timeout);
	}

	ret = tdb_chainlock(tdb, key);

	if (timeout) {
		alarm(0);
		CatchSignal(SIGALRM, SIGNAL_CAST SIG_IGN);
		if (gotalarm)
			return -1;
	}

	return ret;
}

/****************************************************************************
 Lock a chain by string. Return -1 if timeout or lock failed.
****************************************************************************/

int tdb_lock_bystring(TDB_CONTEXT *tdb, const char *keyval, unsigned int timeout)
{
	TDB_DATA key;

	key.dptr = keyval;
	key.dsize = strlen(keyval)+1;

	return tdb_chainlock_with_timeout(tdb, key, timeout);
}

/****************************************************************************
 Unlock a chain by string.
****************************************************************************/

void tdb_unlock_bystring(TDB_CONTEXT *tdb, const char *keyval)
{
	TDB_DATA key;

	key.dptr = keyval;
	key.dsize = strlen(keyval)+1;

	tdb_chainunlock(tdb, key);
}

/****************************************************************************
 Fetch a int32 value by a arbitrary blob key, return -1 if not found.
 Output is int32 in native byte order.
****************************************************************************/

int32 tdb_fetch_int32_byblob(TDB_CONTEXT *tdb, const char *keyval, size_t len)
{
	TDB_DATA key, data;
	int32 ret;

	key.dptr = keyval;
	key.dsize = len;
	data = tdb_fetch(tdb, key);
	if (!data.dptr || data.dsize != sizeof(int32))
		return -1;

	ret = IVAL(data.dptr,0);
	SAFE_FREE(data.dptr);
	return ret;
}

/****************************************************************************
 Fetch a int32 value by string key, return -1 if not found.
 Output is int32 in native byte order.
****************************************************************************/

int32 tdb_fetch_int32(TDB_CONTEXT *tdb, const char *keystr)
{
	return tdb_fetch_int32_byblob(tdb, keystr, strlen(keystr) + 1);
}

/****************************************************************************
 Store a int32 value by an arbitary blob key, return 0 on success, -1 on failure.
 Input is int32 in native byte order. Output in tdb is in little-endian.
****************************************************************************/

int tdb_store_int32_byblob(TDB_CONTEXT *tdb, const char *keystr, size_t len, int32 v)
{
	TDB_DATA key, data;
	int32 v_store;

	key.dptr = keystr;
	key.dsize = len;
	SIVAL(&v_store,0,v);
	data.dptr = (void *)&v_store;
	data.dsize = sizeof(int32);

	return tdb_store(tdb, key, data, TDB_REPLACE);
}

/****************************************************************************
 Store a int32 value by string key, return 0 on success, -1 on failure.
 Input is int32 in native byte order. Output in tdb is in little-endian.
****************************************************************************/

int tdb_store_int32(TDB_CONTEXT *tdb, const char *keystr, int32 v)
{
	return tdb_store_int32_byblob(tdb, keystr, strlen(keystr) + 1, v);
}

/****************************************************************************
 Fetch a uint32 value by a arbitrary blob key, return -1 if not found.
 Output is uint32 in native byte order.
****************************************************************************/

BOOL tdb_fetch_uint32_byblob(TDB_CONTEXT *tdb, const char *keyval, size_t len, uint32 *value)
{
	DEBUG(1,("function ommited\n"));
/* function ommited*/
}

/****************************************************************************
 Fetch a uint32 value by string key, return -1 if not found.
 Output is uint32 in native byte order.
****************************************************************************/

BOOL tdb_fetch_uint32(TDB_CONTEXT *tdb, const char *keystr, uint32 *value)
{
DEBUG(1,("function ommited\n"));
/* function ommited*/
}

/****************************************************************************
 Store a uint32 value by an arbitary blob key, return 0 on success, -1 on failure.
 Input is uint32 in native byte order. Output in tdb is in little-endian.
****************************************************************************/

BOOL tdb_store_uint32_byblob(TDB_CONTEXT *tdb, const char *keystr, size_t len, uint32 value)
{
DEBUG(1,("function ommited\n"));
/* function ommited*/
}

/****************************************************************************
 Store a uint32 value by string key, return 0 on success, -1 on failure.
 Input is uint32 in native byte order. Output in tdb is in little-endian.
****************************************************************************/

BOOL tdb_store_uint32(TDB_CONTEXT *tdb, const char *keystr, uint32 value)
{
	/* function ommited*/
}
/****************************************************************************
 Store a buffer by a null terminated string key.  Return 0 on success, -1
 on failure.
****************************************************************************/

int tdb_store_by_string(TDB_CONTEXT *tdb, const char *keystr, void *buffer, int len)
{
DEBUG(1,("function ommited\n"));
/* function ommited*/
}

/****************************************************************************
 Fetch a buffer using a null terminated string key.  Don't forget to call
 free() on the result dptr.
****************************************************************************/

TDB_DATA tdb_fetch_by_string(TDB_CONTEXT *tdb, const char *keystr)
{
DEBUG(1,("function ommited\n"));
/* function omited*/
}

/****************************************************************************
 Atomic integer change. Returns old value. To create, set initial value in *oldval.
****************************************************************************/

int32 tdb_change_int32_atomic(TDB_CONTEXT *tdb, const char *keystr, int32 *oldval, int32 change_val)
{
	int32 val;
	int32 ret = -1;

	if (tdb_lock_bystring(tdb, keystr,0) == -1)
		return -1;

	if ((val = tdb_fetch_int32(tdb, keystr)) == -1) {
		/* The lookup failed */
		if (tdb_error(tdb) != TDB_ERR_NOEXIST) {
			/* but not becouse it didn't exist */
			goto err_out;
		}

		/* Start with 'old' value */
		val = *oldval;

	} else {
		/* It worked, set return value (oldval) to tdb data */
		*oldval = val;
	}

	/* Increment value for storage and return next time */
	val += change_val;

	if (tdb_store_int32(tdb, keystr, val) == -1)
		goto err_out;

	ret = 0;

  err_out:

	tdb_unlock_bystring(tdb, keystr);
	return ret;
}

/****************************************************************************
 Atomic unsigned integer change. Returns old value. To create, set initial value in *oldval.
****************************************************************************/

BOOL tdb_change_uint32_atomic(TDB_CONTEXT *tdb, char *keystr, uint32 *oldval, uint32 change_val)
{
DEBUG(1,("function ommited\n"));
/* function omited*/
}

/****************************************************************************
 Useful pair of routines for packing/unpacking data consisting of
 integers and strings.
****************************************************************************/

size_t tdb_pack(char *buf, int bufsize, const char *fmt, ...)
{
	va_list ap;
	uint16 w;
	uint32 d;
	int i;
	void *p;
	int len;
	char *s;
	char c;
	char *buf0 = buf;
	const char *fmt0 = fmt;
	int bufsize0 = bufsize;

	va_start(ap, fmt);

	while (*fmt) {
		switch ((c = *fmt++)) {
		case 'w':
			len = 2;
			w = (uint16)va_arg(ap, int);
			if (bufsize >= len)
				SSVAL(buf, 0, w);
			break;
		case 'd':
			len = 4;
			d = va_arg(ap, uint32);
			if (bufsize >= len)
				SIVAL(buf, 0, d);
			break;
		case 'p':
			len = 4;
			p = va_arg(ap, void *);
			d = p?1:0;
			if (bufsize >= len)
				SIVAL(buf, 0, d);
			break;
		case 'P':
			s = va_arg(ap,char *);
			w = strlen(s);
			len = w + 1;
			if (bufsize >= len)
				memcpy(buf, s, len);
			break;
		case 'f':
			s = va_arg(ap,char *);
			w = strlen(s);
			len = w + 1;
			if (bufsize >= len)
				memcpy(buf, s, len);
			break;
		case 'B':
			i = va_arg(ap, int);
			s = va_arg(ap, char *);
			len = 4+i;
			if (bufsize >= len) {
				SIVAL(buf, 0, i);
				memcpy(buf+4, s, i);
			}
			break;
		default:
			DEBUG(0,("Unknown tdb_pack format %c in %s\n", 
				 c, fmt));
			len = 0;
			break;
		}

		buf += len;
		bufsize -= len;
	}

	va_end(ap);

	DEBUG(18,("tdb_pack(%s, %d) -> %d\n", 
		 fmt0, bufsize0, (int)PTR_DIFF(buf, buf0)));
	
	return PTR_DIFF(buf, buf0);
}

/****************************************************************************
 Useful pair of routines for packing/unpacking data consisting of
 integers and strings.
****************************************************************************/

int tdb_unpack(char *buf, int bufsize, const char *fmt, ...)
{
	va_list ap;
	uint16 *w;
	uint32 *d;
	int len;
	int *i;
	void **p;
	char *s, **b;
	char c;
	char *buf0 = buf;
	const char *fmt0 = fmt;
	int bufsize0 = bufsize;

	va_start(ap, fmt);
	
	while (*fmt) {
		switch ((c=*fmt++)) {
		case 'w':
			len = 2;
			w = va_arg(ap, uint16 *);
			if (bufsize < len)
				goto no_space;
			*w = SVAL(buf, 0);
			break;
		case 'd':
			len = 4;
			d = va_arg(ap, uint32 *);
			if (bufsize < len)
				goto no_space;
			*d = IVAL(buf, 0);
			break;
		case 'p':
			len = 4;
			p = va_arg(ap, void **);
			if (bufsize < len)
				goto no_space;
			*p = (void *)IVAL(buf, 0);
			break;
		case 'P':
			s = va_arg(ap,char *);
			len = strlen(buf) + 1;
			if (bufsize < len || len > sizeof(pstring))
				goto no_space;
			memcpy(s, buf, len);
			break;
		case 'f':
			s = va_arg(ap,char *);
			len = strlen(buf) + 1;
			if (bufsize < len || len > sizeof(fstring))
				goto no_space;
			memcpy(s, buf, len);
			break;
		case 'B':
			i = va_arg(ap, int *);
			b = va_arg(ap, char **);
			len = 4;
			if (bufsize < len)
				goto no_space;
			*i = IVAL(buf, 0);
			if (! *i) {
				*b = NULL;
				break;
			}
			len += *i;
			if (bufsize < len)
				goto no_space;
			*b = (char *)malloc(*i);
			if (! *b)
				goto no_space;
			memcpy(*b, buf+4, *i);
			break;
		default:
			DEBUG(0,("Unknown tdb_unpack format %c in %s\n", 
				 c, fmt));

			len = 0;
			break;
		}

		buf += len;
		bufsize -= len;
	}

	va_end(ap);

	DEBUG(18,("tdb_unpack(%s, %d) -> %d\n", 
		 fmt0, bufsize0, (int)PTR_DIFF(buf, buf0)));

	return PTR_DIFF(buf, buf0);

 no_space:
	return -1;
}

/****************************************************************************
 Log tdb messages via DEBUG().
****************************************************************************/

static void tdb_log(TDB_CONTEXT *tdb, int level, const char *format, ...)
{
	va_list ap;
	char *ptr = NULL;

	va_start(ap, format);
	vasprintf(&ptr, format, ap);
	va_end(ap);
	
	if (!ptr || !*ptr)
		return;

	DEBUG(level, ("tdb(%s): %s", tdb->name ? tdb->name : "unknown", ptr));
	SAFE_FREE(ptr);
}

/****************************************************************************
 Like tdb_open() but also setup a logging function that redirects to
 the samba DEBUG() system.
****************************************************************************/

TDB_CONTEXT *tdb_open_log(const char *name, int hash_size, int tdb_flags,
			  int open_flags, mode_t mode)
{
	TDB_CONTEXT *tdb;

	if (!lp_use_mmap())
		tdb_flags |= TDB_NOMMAP;

	tdb = tdb_open_ex(name, hash_size, tdb_flags,
				    open_flags, mode, tdb_log);
	if (!tdb)
		return NULL;

	return tdb;
}


/****************************************************************************
 Allow tdb_delete to be used as a tdb_traversal_fn.
****************************************************************************/

int tdb_traverse_delete_fn(TDB_CONTEXT *the_tdb, TDB_DATA key, TDB_DATA dbuf,
		     void *state)
{
DEBUG(1,("function ommited\n"));
/* function omited*/
}

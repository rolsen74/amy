
/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** Copyright (c) 1992 The Regents of the University of California.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. Neither the name of the University nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/

// --

#include "src/All.h"

// --

/*
 * Convert a string to a uintmax_t.
 *
 * Ignores `locale' stuff.  Assumes that the upper and lower case
 * alphabets and digits are each contiguous.
 */

uintmax_t AMYFUNC _generic_inttypes_strtoumax( struct AmyCLibPrivIFace *Self, const char *nptr, char **endptr, int base )
{
struct libData *data;
const char *s;
uintmax_t retval;
uintmax_t cutoff;
uintmax_t acc;
int cutlim;
int neg;
int any;
int c;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_inttypes_strtoumax :\n" ); );

	DOFUNCTIONLOG( LOG_FUNC_strtoumax );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	/*
	 * See strtoimax for comments as to the logic used.
	 */
	if (base < 0 || base == 1 || base > 36)
	{
		if (endptr != 0)
		{
			*endptr = (char *)nptr;
		}

		data->buf_PublicData->ra_ErrNo = EINVAL;
		retval = 0;
		goto bailout;
	}

	s = nptr;

	do
	{
		c = (unsigned char) *s++;
	}
	while( Self->ctype_isspace( c ));

	if (c == '-')
	{
		neg = 1;
		c = *s++;
	}
	else
	{
		neg = 0;

		if (c == '+')
		{
			c = *s++;
		}
	}

	if ((base == 0 || base == 16) && c == '0' &&
		(*s == 'x' || *s == 'X') && Self->ctype_isxdigit((unsigned char)s[1]))
	{
		c = s[1];
		s += 2;
		base = 16;
	}

	if (base == 0)
	{
		base = c == '0' ? 8 : 10;
	}

	cutoff = UINTMAX_MAX / (uintmax_t)base;
	cutlim = UINTMAX_MAX % (uintmax_t)base;

	for (acc = 0, any = 0;; c = (unsigned char) *s++)
	{
		if ( Self->ctype_isdigit(c))
		{
			c -= '0';
		}
		else if ( Self->ctype_isalpha(c))
		{
			c -= Self->ctype_isupper(c) ? 'A' - 10 : 'a' - 10;
		}
		else
		{
			break;
		}

		if (c >= base)
		{
			break;
		}

		if (any < 0)
		{
			continue;
		}

		if (acc > cutoff || (acc == cutoff && c > cutlim))
		{
			any = -1;
			acc = UINTMAX_MAX;
			data->buf_PublicData->ra_ErrNo = ERANGE;
		}
		else
		{
			any = 1;
			acc *= (uintmax_t)base;
			acc += c;
		}
	}

	if (neg && any > 0)
	{
		acc = -acc;
	}

	if (endptr != 0)
	{
		*endptr = (char *) (any ? s - 1 : nptr);
	}
	
	retval = acc;

bailout:

	return( retval );
}

// --


/*
** SPDX-License-Identifier: BSD-3-Clause
** Modifications (c) 2025 Rene W. Olsen
** Part of Amy C Lib
**
** Based on:
**
** Portable ISO 'C' (1994) runtime library for the Amiga computer
** Copyright (c) 2002-2015 by Olaf Barthel <obarthel (at) gmx.net>
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   - Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**
**   - Neither the name of Olaf Barthel nor the names of contributors
**     may be used to endorse or promote products derived from this
**     software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
*/

// --

#include "src/All.h"
#include "Print.h"

// --

static S32 AMYFUNC my_readsize( struct PrintStruct *ps, struct Intern *in )
{
S32 next_sum;
S32 retval;
S32 sum;

	retval = -1;

	in->c = *ps->ps_Format;

	if ( in->c == '*' )
	{
		if ( ! ps->ps_Args )
		{
//			data->PublicData.ra_ErrNo = (EFAULT);
			goto bailout;
		}

		retval = va_arg( ps->ps_Args, S32 );

		ps->ps_Format++;
	}
	else if (( '0' <= in->c ) && ( in->c <= '9' ))
	{
		sum = 0;

		while( TRUE )
		{
			in->c = *ps->ps_Format;

			if (( '0' <= in->c ) && ( in->c <= '9' ))
			{
				next_sum = ( 10 * sum ) + ( in->c - '0' );

				if ( next_sum < sum ) /* overflow? */
				{
//					data->PublicData.ra_ErrNo = (EFAULT);
					goto bailout;
				}

				sum = next_sum;

				ps->ps_Format++;
			}
			else
			{
				break;
			}
		}

		retval = sum;
	}
	else
	{
		retval = 0;
	}

bailout:

	return( retval );
}

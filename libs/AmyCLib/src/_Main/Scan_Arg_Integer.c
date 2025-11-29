
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
#include "Scan.h"

// --

#define MAX_BUF 255		// 255 so stack buffer gets 256 bytes

static S32 my_Scan_Arg_Integer( struct Intern *in )
{
struct AmyCLibIFace *Self;
char buf[MAX_BUF+1];	// +1 for NUL char
intmax_t v;
S32 retval;
S32 digits;
S32 sign;
S32 cap;
S32 len;
S32 c;

	DODEBUGPRINTF( IExec->DebugPrintF( "my_Scan_Arg_Integer\n" ); );

	retval = FALSE;

	digits = 0;

	Self = in->Self;

	sign = 0;

	len = 0;

	// --

	if ( in->width )
	{
		cap = MIN( in->width, MAX_BUF );
	}
	else
	{
		cap = MAX_BUF;
	}

	if ( cap <= 0 )
	{
		goto bailout;
	}

	// --

	my_Scan_Skip_Spaces( in );

	c = my_Scan_Char_Peek( in );

	if (( c == '+' ) || ( c == '-' )) 
	{
		buf[len++] = my_Scan_Char_Get( in );
		sign = 1;	// We have a sign
	}

	// digits
	while( TRUE ) 
	{
		c = my_Scan_Char_Peek( in );

		if ( c < 0 ) 
		{
			break;
		}

		if ( ! Self->ctype_isdigit( c ))
		{
			break;
		}

		if ( len >= cap )
		{
			break;
		}

		buf[len++] = my_Scan_Char_Get( in );
		digits++;
	}

	// --
	// Check if we have a Digit

	/**/ if ( digits <= 0 )
	{
		if ( sign )
		{
			my_Scan_Char_Unget( in, buf[0] );
		}
		goto bailout;
	}

	// --
	// NUL terminator
	buf[len] = 0;

//	IExec->DebugPrintF( "IntBuf: %s\n", buf );

	// -- 
	// Handle Arg is not Suppressed

	if ( ! in->suppress ) 
	{
		v = Self->inttypes_strtoimax( buf, NULL, 10 );

//		IExec->DebugPrintF( "Val: %lld, v %ld\n", v, (int)v );

		*va_arg( in->args, int * ) = (int) v;

		in->nassigned++;
	}

	in->nread += len;

	retval = TRUE;

bailout:

	return( retval );
}

#undef MAX_BUF

// --

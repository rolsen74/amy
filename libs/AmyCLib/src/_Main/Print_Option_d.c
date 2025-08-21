
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
// Option  d  Decimal (signed)

static S32 AMYFUNC my_Option_d( struct PrintStruct *ps, struct Intern *in )
{
const char *digit_encoding;
S32 retval;
S32 radix;
S64 sv;
U64 v;

	#ifdef DEBUG
	IExec->DebugPrintF( "my_Option_d\n" );
	#endif

	retval = FALSE;

	if ( ! ps->ps_Args )
	{
//		  data->PublicData.ra_ErrNo = (EFAULT);
		goto bailout;
	}

	/**/ if ( in->Parameter_Size == Parameter_Size_Byte )
	{
		IExec->DebugPrintF( "Parameter_Size_Byte\n" );

		S8 v8_integer;

		v8_integer = va_arg( ps->ps_Args, S32 );

		sv = v8_integer;
	}
	else if ( in->Parameter_Size == Parameter_Size_Short )
	{
		IExec->DebugPrintF( "Parameter_Size_Short\n" );

		S16 v16_integer;

		v16_integer = va_arg( ps->ps_Args, S32 );

		sv = v16_integer;
	}
	else if ( in->Parameter_Size == Parameter_Size_Long_Long )
	{
		IExec->DebugPrintF( "Parameter_Size_Long_Long\n" );

		S64 v64_int;

		v64_int = va_arg( ps->ps_Args, S64 );

		sv = v64_int;
	}
	else if ( in->Parameter_Size == Parameter_Size_Intmax_t )
	{
		IExec->DebugPrintF( "Parameter_Size_Intmax_t\n" );

		S64 v64_int;

		v64_int = va_arg( ps->ps_Args, S64 );

		sv = v64_int;
	}
	else
	{
		IExec->DebugPrintF( "Parameter_Size_Default\n" );

		S32 v32_integer;

		v32_integer = va_arg( ps->ps_Args, S32 );

		sv = v32_integer;
	}

	if ( sv < 0LL )
	{
		in->FORMATF_IsNegative = 1;

		v = (-sv);
	}
	else
	{
		in->FORMATF_IsNegative = 0;

		v = sv;
	}

	/* Don't print anything if the precision is 0 and the number itself is 0. */
	if (( v != 0 ) || ( in->precision != 0 ))
	{
		digit_encoding = "0123456789";

		radix = 10;

		do
		{
			in->output_buffer--;
			in->output_len++;

			(*in->output_buffer) = digit_encoding[ v % radix ];
			v /= radix;
		}
		while(( v > 0 ) && ( in->buffer < in->output_buffer ));

		while(( in->output_len < in->precision ) && ( in->output_buffer > in->buffer ))
		{
			in->output_buffer--;
			in->output_len++;

			(*in->output_buffer) = '0';
		}
	}

	retval = TRUE;

bailout:

	return( retval );
}

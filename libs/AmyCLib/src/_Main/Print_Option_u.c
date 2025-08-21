
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
// Option  u  Decimal (unsigned)

static S32 AMYFUNC my_Option_u( struct PrintStruct *ps, struct Intern *in )
{
S32 retval;

	retval = FALSE;

	#ifdef DEBUG
	IExec->DebugPrintF( "my_Option_u\n" );
	#endif

	unsigned long long v;

	if ( ! ps->ps_Args )
	{
//		  data->PublicData.ra_ErrNo = (EFAULT);
		goto bailout;
	}

	{
		if ( in->Parameter_Size == Parameter_Size_Short )
		{
			/* Parameter is a short integer which
			 * must be cast to a long integer before
			 * it can be used.
			 */
			unsigned short short_integer;

			short_integer = (unsigned short) va_arg( ps->ps_Args, U32 );

			v = short_integer;
		}
		else if ( in->Parameter_Size == Parameter_Size_Byte )
		{
			/* Parameter is a byte-sized integer which
			 * must be cast to a long integer before
			 * it can be used.
			 */
			unsigned char byte_integer;

			byte_integer = (unsigned char) va_arg( ps->ps_Args, U32 );

			v = byte_integer;
		}
		else
		{
			if (( in->Parameter_Size == Parameter_Size_Long_Long )
			||	( in->Parameter_Size == Parameter_Size_Intmax_t ))
			{
				v = va_arg( ps->ps_Args, unsigned long long );
			}
			else
			{
				v = va_arg( ps->ps_Args, U32 );
			}
		}

		in->FORMATF_ProduceSign = 0;
		in->FORMATF_ProduceSpace = 0;
	}

	/* Don't print anything if the precision is 0 and the number
	   itself is 0. */
	if (( v != 0 ) || ( in->precision != 0 ))
	{
		const char * digit_encoding;
		S32 radix;

		/* Only add the zero (%o) or hex (%x) prefix if the value to
		   be converted is non-zero. */
		if (( in->FORMATF_AlternateConversion ) && ( v != 0 ))
		{
			if ( in->Conversion_Type == 'o' )
			{
				in->FORMATF_ZeroPrefix = 1;
			}
			else if ( in->Conversion_Type == 'x' )
			{
				in->FORMATF_HexPrefix = 1;
			}
		}

		if ( in->Conversion_Type == 'o' )
		{
			radix = 8;
		}
		else if ( in->Conversion_Type == 'x' )
		{
			radix = 16;
		}
		else
		{
			radix = 10;
		}

		if ( in->FORMATF_CapitalLetters )
		{
			digit_encoding = "0123456789ABCDEF";
		}
		else
		{
			digit_encoding = "0123456789abcdef";
		}

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

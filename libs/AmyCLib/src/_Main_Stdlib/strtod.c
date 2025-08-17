
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

// --

double AMYFUNC _generic_stdlib_strtod( struct AmyCLibIFace *Self, const char *str, char **ptr )
{
struct libData *data;
const char *stop;
double retval;
double sum;
char c;
int is_negative;

	IExec->DebugPrintF( "_generic_stdlib_strtod\n" );

	// --

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	stop = str;

	sum = 0.0;

	if ( ! str )
	{
//		IExec->DebugPrintF( "NULL Pointer" );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		retval = Self->math_d__get_huge_val();
		goto out;
	}

	/* Skip all leading blanks. */
	while((c = (*str)) != '\0')
	{
		if ( NOT Self->ctype_isspace( c ))
			break;

		str++;
	}

	/* The first character may be a sign. */
	if((*str) == '-')
	{
		/* It's a negative number. */
		is_negative = 1;

		str++;
	}
	else
	{
		/* It's not going to be negative. */
		is_negative = 0;

		/* But there may be a sign we will choose to
		   ignore. */
		if((*str) == '+')
			str++;
	}

	/* We begin by checking for the "inf" and "nan" strings. */
	if ( Self->strings_strcasecmp(str,"inf") == 0 || Self->strings_strcasecmp(str,"infinity") == 0 )
	{
		str += Self->string_strlen( str );

		sum = Self->math_d__inf();

		stop = str;
	}
	else if ( Self->strings_strncasecmp(str,"nan",3) == 0 && (str[3] == '(' || str[3] == '\0'))
	{
		str += 3;

		/* Does NaN data follow the header? If so, skip it. */
		if((*str) == '(')
		{
			while((*str) != '\0' && (*str) != ')')
				str++;

			if((*str) == ')')
				str++;
		}

		sum = Self->math_d_nan(NULL);

		stop = str;
	}
	else
	{
		size_t num_digits_converted = 0;
		int decimal_point_matches;
		double new_sum;
		int error = 0;
		int radix;

		/* Check for the hex prefix. */
		if( Self->strings_strncasecmp(str,"0x",2) == 0)
		{
			str += 2;

			radix = 16;
		}
		else
		{
			radix = 10;
		}

		/* Convert all the digits preceding the decimal point. */
		while((c = (*str)) != '\0')
		{
			if ('0' <= c && c <= '9')
				c = c - '0';
			else if ('a' <= c && c <= 'f')
				c = c - 'a' + 10;
			else if ('A' <= c && c <= 'F')
				c = c - 'A' + 10;
			else
				c = radix;

			if(c >= radix)
				break;

			str++;

			if(error == 0)
			{
				new_sum = (radix * sum) + c;
				if(new_sum < sum) /* overflow? */
					error = ERANGE;
				else
					sum = new_sum;
			}

			num_digits_converted++;
		}

		/* Did we find the decimal point? We accept both the
		   locale configured decimal point and the plain old
		   dot. */
		decimal_point_matches = 0;

	IExec->ObtainSemaphore( & data->LocaleSemaphore );

		if(data->LocaleTable[LC_NUMERIC] != NULL)
		{
			const char * point;

			point = (const char *) data->LocaleTable[LC_NUMERIC]->loc_DecimalPoint;

			if((*point) == (*str))
			{
				decimal_point_matches = 1;

				/* Skip the decimal point. */
				str++;
			}
		}

	IExec->ReleaseSemaphore( & data->LocaleSemaphore );

		if(NOT decimal_point_matches)
		{
			if((*str) == '.')
			{
				decimal_point_matches = 1;

				/* Skip the decimal point. */
				str++;
			}
		}

		if(decimal_point_matches)
		{
			double divisor = 1.0 / radix;

			/* Process all digits following the decimal point. */
			while((c = (*str)) != '\0')
			{
				if ('0' <= c && c <= '9')
					c = c - '0';
				else if ('a' <= c && c <= 'f')
					c = c - 'a' + 10;
				else if ('A' <= c && c <= 'F')
					c = c - 'A' + 10;
				else
					c = radix;

				if(c >= radix)
					break;

				str++;

				if(error == 0 && divisor != 0.0)
				{
					new_sum = sum + c * divisor;
					if(new_sum < sum) /* overflow? */
						error = ERANGE;
					else
						sum = new_sum;

					divisor = divisor / radix;
				}

				num_digits_converted++;
			}
		}

		/* If there is a scale indicator attached, process it. */
		if((radix == 10 && ((*str) == 'e' || (*str) == 'E')) ||
		   (radix == 16 && ((*str) == 'p' || (*str) == 'P')))
		{
			int exponent_is_negative;
			int new_exponent;
			int exponent = 0;
			int exponent_radix;

			/* If we are processing a hexadecimal encoded
			   floating point number, switch to a binary
			   exponent. */
			if(radix == 16)
				exponent_radix = 2;
			else
				exponent_radix = 10;

			/* Skip the indicator. */
			str++;

			/* Take care of the exponent's sign. */
			if((*str) == '-')
			{
				exponent_is_negative = 1;
				str++;
			}
			else
			{
				exponent_is_negative = 0;

				if((*str) == '+')
					str++;
			}

			/* Again, process all digits to follow. */
			while((c = (*str)) != '\0')
			{
				if('0' <= c && c <= '9')
					c -= '0';
				else
					c = exponent_radix;

				if(c >= exponent_radix)
					break;

				str++;

				if(error == 0)
				{
					new_exponent = (exponent_radix * exponent) + c;
					if(new_exponent < exponent) /* overflow? */
						error = ERANGE;
					else
						exponent = new_exponent;
				}
			}

			/* If the exponent is valid, scale the number accordingly. */
			if(exponent != 0)
			{
				if(exponent_is_negative)
				{
					double divisor;

					/* A negative exponent means division. */
					divisor = Self->math_d_pow((double)radix,(double)exponent);
					if(divisor != 0.0)
					{
						new_sum = sum / divisor;
						if(new_sum == 0.0 && sum != 0.0)
							error = ERANGE;
						else
							sum = new_sum;
					}
					else
					{
						error = ERANGE;
					}
				}
				else
				{
					/* A positive exponent means multiplication. */
					new_sum = sum * Self->math_d_pow((double)radix,(double)exponent);
					if(new_sum < sum)
						error = ERANGE;
					else
						sum = new_sum;
				}
			}
		}

		if(num_digits_converted == 0)
		{
			sum = 0;
		}
		else
		{
			if(error != 0)
			{
				data->buf_PublicData->ra_ErrNo = EFAULT;

				sum = Self->math_d__get_huge_val();
			}

			stop = str;
		}
	}

	if(is_negative)
		sum = (-sum);

	retval = sum;

 out:

	/* If desired, remember where we stopped reading the
	   number from the buffer. */
	if(ptr != NULL)
		(*ptr) = (char *)stop;

	return(	retval );
}

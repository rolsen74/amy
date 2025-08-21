
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

int AMYFUNC _generic_strings_strncasecmp( struct AmyCLibPrivIFace *Self, const char *s1, const char *s2, size_t maxlen )
{
struct libData *data;
uint8 *str1;
uint8 *str2;
U32 len;
int retval;
int c1;
int c2;

	// --

	IExec->DebugPrintF( "_generic_strings_strncasecmp\n" );

	retval = 0;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if (( ! s1 ) || ( ! s2 ))
	{
//		IExec->DebugPrintF( "NULL Pointer" );
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	if ( s1 == s2 )
	{
		goto bailout;
	}

	len = maxlen;
	str1 = (PTR) s1;
	str2 = (PTR) s2;

	while( len-- )
	{
		c1 = Self->ctype_toupper( *str1 );
		c2 = Self->ctype_toupper( *str2 );

		if ( c1 == c2 )
		{
			if ( ! c1 )
			{
				break;
			}
			else
			{
				str1++;
				str2++;
			}
		}
		else
		{
			retval = c1 - c2;
			break;
		}
	}


bailout:

	return(	retval );
}

/****************************************************************************/


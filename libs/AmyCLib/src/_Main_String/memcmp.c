
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

// #pragma GCC push_options
// #pragma GCC optimize ("Os,no-tree-loop-distribute-patterns")

int AMYFUNC _generic_string_memcmp( struct AmyCLibPrivIFace *Self, const void *s1, const void *s2, size_t len )
{
int retval;
U32 pos;
S32 c1;
S32 c2;
U8 *m1;
U8 *m2;

	pos = 0;
	retval = 0;

//	IExec->DebugPrintF( "_generic_string_memcmp : Mem %p, Mem %p, Len %lu\n", s1, s2, len );

	DOFUNCTIONLOG( LOG_FUNC_memcmp );

	// --

	if ( len )
	{
		/**/ if (( ! s1 ) || ( ! s2 ))
		{
			// Only an error if len is none zero
			struct libData *data = (PTR)( (U32) Self - Self->Data.NegativeSize );
			data->buf_PublicData->ra_ErrNo = EFAULT;
		}
		else if ( s1 != s2 )
		{
			m1 = (PTR) s1 ;
			m2 = (PTR) s2 ;

			while( len > pos++ )
			{
				c1 = *m1++;
				c2 = *m2++;

				if ( c1 != c2 )
				{
					retval = c1 - c2;
					break;
				}
			}
		}
	}

	IExec->DebugPrintF( "_generic_string_memcmp : Mem %p : Mem %p : Len %lu : Pos %ld : Retval %ld :\n", s1, s2, len, pos-1, retval );

	return( retval );
}

// #pragma GCC pop_options

// --

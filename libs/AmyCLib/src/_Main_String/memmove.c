
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

void * AMY_FUNC _generic_string_memmove( struct AmyCLibIFace *Self, void *dst, const void *src, size_t len )
{
	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_string_memmove : Src %p, Dst %p, Len %lu\n", src, dst, len ); );

	DOFUNCTIONLOG( LOG_FUNC_memmove );

	if ( len )
	{
		if (( ! src ) || ( ! dst ))
		{
			// Only an error if len is none zero
			struct libData *data = (PTR)( (U32) Self - Self->Data.NegativeSize );
			data->buf_PublicData->ra_ErrNo = EFAULT;
		}
		else if ( src != dst )
		{
			U8 *d = (PTR) dst ;
			U8 *s = (PTR) src ;

			if (( s < d ) && ( d < s + len ))
			{
				d += len;
				s += len;

				while( len-- )
				{
					*--d = *--s;
				}
			}
			else
			{
				while( len-- )
				{
					*d++ = *s++;
				}
			}
		}
	}

	return( dst );
}

// --

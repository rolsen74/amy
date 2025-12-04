
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

int AMY_FUNC _locale_ctype_isupper( struct AmyCLibIFace *Self, int c )
{
struct libData *data;
int retval;

	IExec->DebugPrintF( "_locale_ctype_isupper\n" );

	DOFUNCTIONLOG( LOG_FUNC_isupper );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	IExec->ObtainSemaphore( & data->LocaleSemaphore );

	if ( data->LocaleTable[ LC_CTYPE ] )
	{
		if (( c != EOF ) && ((( 0 <= c ) && ( c <= UCHAR_MAX )) || (( c + 256 ) <= UCHAR_MAX )))
		{
			retval = ILocale->IsUpper( data->LocaleTable[ LC_CTYPE ], c & 255 );
		}
		else
		{
			retval = FALSE;
		}
	}
	else
	{
		retval = (( 'A' <= c ) && ( c <= 'Z' )) ? TRUE : FALSE ;
	}

	IExec->ReleaseSemaphore( & data->LocaleSemaphore );

	return(	retval );
}

// --

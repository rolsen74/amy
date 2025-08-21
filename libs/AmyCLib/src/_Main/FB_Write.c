
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
// File Buffer

// Same as __fputc
S32 AMYFUNC _generic__Priv_FB_Write( struct AmyCLibPrivIFace *Self, struct PrivFile *file, S32 mode, S32 c )
{
S32 retval;

	IExec->DebugPrintF( "_generic__Priv_FB_Write\n" );

	retval = EOF;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid file id\n", __FILE__, __LINE__ );
		goto bailout;
	}

	if ( ! file->pf_Handle.pf_File )
	{
		IExec->DebugPrintF( "_generic__Priv_FB_Write : NULL Pointer\n" );
		goto bailout;
	}

	// Are Write buffer full
	if (( file->pf_BufferSize > 0 )
	&&	( file->pf_BufferSize == file->pf_BufferWriteBytes ))
	{
		if ( ! Self->Priv_FB_Write_Flush_Buffer( file ))
		{
			IExec->DebugPrintF( "_generic__Priv_FB_Write : Flush failed\n" );
			goto bailout;
		}
	}

	// Write byte
	file->pf_Buffer[ file->pf_BufferWriteBytes++ ] = c;

	// Flush from NewLine
	if (( mode == BUFFER_MODE_NONE ) || (( mode == BUFFER_MODE_LINE ) && ( c == '\n' )))
	{
		if ( Self->Priv_FB_Write_Flush_Buffer( file ) == FALSE )
		{
			/* Pretend that the last character was not written. */
			file->pf_BufferWriteBytes--;
			goto bailout;
		}
	}

	retval = ( c & 255 );

bailout:

	return(	retval );
}


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

int AMYFUNC _generic_stdio_puts( struct AmyCLibPrivIFace *Self, const char *str )
{
struct PrivFile *file;
struct libData *data;
int retval;
int mode;
int c;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_puts : str '%s'\n", str ); );

	DOFUNCTIONLOG( LOG_FUNC_puts );

	file = NULL;
	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	file = Self->Priv_FDLockNr( STDOUT_FILENO );

	if ( ! file )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_puts : NULL Pointer\n" ); );
		data->buf_PublicData->ra_ErrNo = EBADF;
		goto bailout;
	}

	Self->stdio_flockfile( (PTR) file );

	// __fputc_check start

	if ( ! file->pf_Write )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Stream not writeable\n", __FILE__, __LINE__ );
		#endif
		data->buf_PublicData->ra_ErrNo = EBADF;
		file->pf_Error = TRUE;
		goto bailout;
	}

	if ( file->pf_BufferReadBytes > 0 )
	{
		if ( ! Self->Priv_FB_Read_Drop_Buffer( file ))
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_puts : Error flushing buffer\n" ); );
			goto bailout;
		}
	}

	// __fputc_check done

	mode = file->pf_BufferMode;

	if ( mode == BUFFER_MODE_NONE )
	{
		mode = BUFFER_MODE_LINE;
	}

	while( TRUE )
	{
		c = *str++;

		if ( ! c )
		{
			break;
		}

		if ( Self->Priv_FB_Write( file, mode, c ) < 0 )
		{
			goto bailout;
		}
	}

	if ( Self->Priv_FB_Write( file, mode, '\n' ) < 0 )
	{
		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

	if ( file )
	{
		/* Note: if buffering is disabled for this stream, then we still
			may have buffered data around, queued to be printed right now.
			This is intended to improve performance as it takes more effort
			to write a single character to a file than to write a bunch. */
		if (( retval ) && ( file->pf_BufferMode == BUFFER_MODE_NONE ))
		{
			if ( Self->Priv_FB_Write_Flush_Buffer( file ) < 0 )
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_puts : couldn't flush the write buffer" ); );
				retval = EOF;
			}
		}

		// --

		Self->stdio_funlockfile( (PTR) file );

		Self->Priv_FDUnlock( file );
	}

	return(	retval );
}

// --


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

int AMYFUNC _generic_stdio_setvbuf( struct AmyCLibIFace *Self, FILE *stream, char *buf, int mode, size_t size )
{
struct FileStruct *file;
struct libData *data;
char *newbuf;
int retval;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_setvbuf, File %p, Buf %p, Mode %ld, Size %ld\n", stream, buf, mode, size ); );

	DOFUNCTIONLOG( LOG_FUNC_setvbuf );

	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	file = (PTR) stream;

	if ( ! file )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_setvbuf : NULL Pointer\n" ); );
		data->buf_PublicData->ra_ErrNo = EBADF;
		goto bailout;
	}

	Self->stdio_flockfile( stream );

	// --

	Self->stdio_fflush( stream );

	// --

	if (( mode < BUFFER_MODE_FULL ) || ( mode > BUFFER_MODE_NONE ))
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_setvbuf : Invalid mode %ld\n", mode ); );
		data->buf_PublicData->ra_ErrNo = EINVAL;
		goto bailout;
	}

	/* A buffer size of 0 bytes defaults
		to unbuffered operation. */

	if ( size == 0 )
	{
		mode = BUFFER_MODE_NONE;
	}

	// --

//	  IReactive = data->IReactive;

	/**/ if (( mode == BUFFER_MODE_NONE ))
	{
		// No Buffer

		Self->Priv_Mem_Free( file->pf_BufferCustom );

		file->pf_Buffer			= (PTR) & file->pf_BufferDefault;
		file->pf_BufferSize		= 1;
		file->pf_BufferMode		= mode;
		file->pf_BufferCustom	= NULL;
	}
	else if (( size ) && ( buf ))
	{
		// Use User buffer

		Self->Priv_Mem_Free( file->pf_BufferCustom );

		file->pf_Buffer			= (PTR) buf;
		file->pf_BufferSize		= size;
		file->pf_BufferMode		= mode;
		file->pf_BufferCustom	= NULL;
	}
	else if (( size ) && ( ! buf ))
	{
		// Alloc new Custom buffer

		newbuf = Self->Priv_Mem_Alloc( size );

		if ( ! newbuf )
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_setvbuf : Error allocating memory\n" ); );
			data->buf_PublicData->ra_ErrNo = ENOBUFS;
			goto bailout;
		}

		Self->Priv_Mem_Free( file->pf_BufferCustom );

		file->pf_Buffer			= (PTR) newbuf;
		file->pf_BufferSize		= size;
		file->pf_BufferMode		= mode;
		file->pf_BufferCustom	= (PTR) newbuf;
	}
	else
	{
		// Error - should not happen

		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_setvbuf : unknown mode\n" ); );
		data->buf_PublicData->ra_ErrNo = ENOBUFS;
		goto bailout;
	}

	// --

	retval = 0;

bailout:

	if ( file )
	{
		Self->stdio_funlockfile( stream );
	}

	return(	retval );
}

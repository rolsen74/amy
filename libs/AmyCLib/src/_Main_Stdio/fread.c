
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

size_t AMYFUNC _generic_stdio_fread( struct AmyCLibPrivIFace *Self, void *ptr, size_t size, size_t count, struct PrivFile *stream )
{
struct PrivFile *file;
struct libData *data;
size_t retval;

	// --

	IExec->DebugPrintF( "_generic_stdio_fread : Buf %p, Size %ld, Count %ld, File %p\n", ptr, size, count, stream );

	file = NULL;
	retval = 0;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// Find, Lock and Validate Stream
	file = Self->Priv_FDLockStream( stream );

	if ( ! file )
	{
//		IExec->DebugPrintF( "NULL Pointer" );
		data->buf_PublicData->ra_ErrNo = EBADF;
		goto bailout;
	}

	Self->stdio_flockfile( stream );

	// --

	if ( ! file->pf_Read )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Stream not readable\n", __FILE__, __LINE__ );
		#endif
		data->buf_PublicData->ra_ErrNo = ENXIO;
		file->pf_Error = TRUE;
		goto bailout;
	}

	// --

	if (( size > 0 ) && ( count > 0 ))
	{
		size_t total_bytes_read = 0;
		size_t total_size;
		unsigned char *d = ptr;
		int c;

		// __fgetc_check start

		if ( ! file->pf_Read )
		{
			#ifdef DEBUG
			IExec->DebugPrintF( "%s:%04d: Stream not readable\n", __FILE__, __LINE__ );
			#endif
			data->buf_PublicData->ra_ErrNo = EBADF;
			file->pf_Error = TRUE;
			goto bailout;
		}

		if ( file->pf_BufferWriteBytes > 0 )
		{
			if ( Self->Priv_FB_Write_Flush_Buffer( file ) < 0 )
			{
//				IExec->DebugPrintF( "Error flushing buffer" );
				goto bailout;
			}
		}

		// __fgetc_check done

		total_size = size * count;

		while( total_size-- > 0 )
		{
			c = Self->Priv_FB_Read( file );

			if ( c == EOF )
			{
				break;
			}

			(*d++) = c;

			total_bytes_read++;
		}

		retval = total_bytes_read / size;
	}
	else
	{
		/* Don't let this appear like an EOF or error. */
		Self->stdio_clearerr( stream );
	}

	// --

bailout:

	if ( file )
	{
		Self->stdio_funlockfile( stream );

		Self->Priv_FDUnlock( file );
	}

	return(	retval );
}

/****************************************************************************/


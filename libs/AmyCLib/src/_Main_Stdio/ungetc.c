
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

int AMYFUNC _generic_stdio_ungetc( struct AmyCLibPrivIFace *Self, int c, struct PrivFile *stream )
{
struct PrivFile *file;
struct libData *data;
int retval;

	// --

	IExec->DebugPrintF( "_generic_stdio_ungetc, C %ld, File %p\n", c, stream );

	DOFUNCTIONLOG( LOG_FUNC_ungetc );

	file = NULL;
	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	// Find, Lock and Validate Stream
	file = Self->Priv_FDLockStream( stream );

	if ( ! file )
	{
		data->buf_PublicData->ra_ErrNo = EBADF;
		goto bailout;
	}

	Self->stdio_flockfile( stream );

	// Only works for Read Descriptors
	if ( ! file->pf_Read )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Stream not readable\n", __FILE__, __LINE__ );
		#endif
		data->buf_PublicData->ra_ErrNo = EACCES;
		file->pf_Error = TRUE;
		goto bailout;
	}

	// Pushing back an EOF is forbidden
	if ( c == EOF )
	{
		data->buf_PublicData->ra_ErrNo = EINVAL;
		file->pf_Error = TRUE;
		goto bailout;
	}

	// Flush write buffer
	if ( file->pf_BufferWriteBytes > 0 )
	{
		if ( Self->Priv_FB_Write_Flush_Buffer( file ) < 0 )
		{
//			IExec->DebugPrintF( "Error flushing buffer" );
			goto bailout;
		}
	}

	/* We need to replace one of the characters in the buffer, which must
	 * have been read before. The ISO standard requires that it must
	 * be possible to push back at least one single character.
	 */
	if ( file->pf_BufferPosition == 0 )
	{
//		IExec->DebugPrintF( "no room to push back" );
		data->buf_PublicData->ra_ErrNo = ENOBUFS;
		file->pf_Error = TRUE;
		goto bailout;
	}

	// --

	file->pf_EOF_Reached = FALSE;

	/* Replace the character just read. */
	file->pf_Buffer[ --file->pf_BufferPosition ] = c;

	// Clamp the result to an unsigned 8 bit value.
	retval = ( c & 255 );

bailout:

	if ( file )
	{
		Self->stdio_funlockfile( stream );

		Self->Priv_FDUnlock( file );
	}

	return(	retval );
}

/****************************************************************************/


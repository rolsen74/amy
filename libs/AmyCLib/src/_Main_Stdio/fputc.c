
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

int AMYFUNC _generic_stdio_fputc( struct AmyCLibIFace *Self, int c, FILE *stream )
{
struct FileStruct *file;
struct libData *data;
S32 retval;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fputc : c %ld, File %p\n", c, stream ); );

	DOFUNCTIONLOG( LOG_FUNC_fputc );

	file = NULL;
	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	// Find, Lock and Validate Stream
	file = Self->Priv_FDLockStream( stream );

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid StructID\n", __FILE__, __LINE__ );
		data->buf_PublicData->ra_ErrNo = EBADF;
		goto bailout;
	}

	// Get Semaphore
	Self->stdio_flockfile( stream );

	// Check Write Enabled
	if ( ! file->pf_Write )
	{
		#ifdef DEBUG
		IExec->DebugPrintF( "%s:%04d: Stream not writeable\n", __FILE__, __LINE__ );
		#endif
		data->buf_PublicData->ra_ErrNo = EBADF;
		file->pf_Error = TRUE;
		goto bailout;
	}

	// Flush Read Buffer if any
	if ( file->pf_BufferReadBytes > 0 )
	{
		if ( ! Self->Priv_FB_Read_Drop_Buffer( file ))
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fputc : failed\n" ); );
			goto bailout;
		}
	}

	// Write 1 byte
	retval = Self->Priv_FB_Write( file, file->pf_BufferMode, c );

bailout:

	if ( file )
	{
		Self->stdio_funlockfile( stream );

		Self->Priv_FDUnlock( file );
	}

	return(	retval );
}

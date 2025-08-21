
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

int AMYFUNC _generic_stdio_fseeko( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, off_t offset, int wherefrom )
{
struct PrivFile *file;
struct libData *data;
int retval;

	// --

	IExec->DebugPrintF( "_generic_stdio_fseeko : Stream %p, off %ld, from %ld\n", stream, offset, wherefrom );

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

	// --

	// Get Semaphore
	Self->stdio_flockfile( stream );

	// Flush Read data if any
	Self->stdio_fflush( stream );

	// --

	if ( ! file->pf_Interface.pi_Seek )
	{
		IExec->DebugPrintF( "pi_Seek 1 : NULL Pointer\n" );
		goto bailout;
	}

	if ( file->pf_Interface.pi_Seek( Self, file, offset, wherefrom ) < 0 )
	{
		file->pf_Error = TRUE;
		goto bailout;
	}

	// --

	retval = 0;

bailout:

	if ( file )
	{
		Self->stdio_funlockfile( stream );

		Self->Priv_FDUnlock( file );
	}

	return(	retval );
}

// --

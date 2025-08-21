
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

int AMYFUNC _generic_stdio_fgetpos( struct AmyCLibPrivIFace *Self, struct PrivFile *stream, fpos_t *pos )
{
struct PrivFile *file;
struct libData *data;
S64 fpos;
int retval;

	// --

	IExec->DebugPrintF( "_generic_stdio_fgetpos, Stream %p, Pos Ptr %p\n", stream, pos );

	DOFUNCTIONLOG( LOG_FUNC_fgetpos );

	fpos = -1LL;
	file = NULL;
	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	// NULL Pointer check
	if ( ! pos )
	{
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	// Find, Lock and Validate Stream
	file = Self->Priv_FDLockStream( stream );

	if ( ! file )
	{
		data->buf_PublicData->ra_ErrNo = EFAULT;
		goto bailout;
	}

	// Get Semaphore lock
	Self->stdio_flockfile( stream );

	// Flush Read data if any
	Self->stdio_fflush( stream );

	if ( ! file->pf_Interface.pi_GetPos )
	{
		IExec->DebugPrintF( "pi_GetPos 1 : NULL Pointer\n" );
		goto bailout;
	}

	// Get File Pos
	fpos = file->pf_Interface.pi_GetPos( Self, file );

	if ( fpos < 0 )
	{
		file->pf_Error = TRUE;
		goto bailout;
	}

	// Set okay
	retval = 0;

bailout:

	// hmm should proberly not set if not enabled

	if ( pos )
	{
		*pos = fpos;
	}

	if ( file )
	{
		Self->stdio_funlockfile( stream );

		Self->Priv_FDUnlock( file );
	}

	return(	retval );
}

// --

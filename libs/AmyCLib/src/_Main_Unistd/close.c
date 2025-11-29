
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

int AMYFUNC _generic_unistd_close( struct AmyCLibIFace *Self, int fildes )
{
struct FileStruct *file;
struct libData *data;
int retval;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_unistd_close : Fildes %ld\n", (S32) fildes ); );

	DOFUNCTIONLOG( LOG_FUNC_close );

	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// -- Check About

// IExec->DebugPrintF( "close 1\n" );

	Self->Priv_Check_Abort();

	// --

// IExec->DebugPrintF( "close 2\n" );

	file = Self->Priv_FDLockNr( fildes );

	if ( ! file )
	{
		data->buf_PublicData->ra_ErrNo = EBADF;
		goto bailout;
	}

// IExec->DebugPrintF( "close 3 - %ld\n", file->pf_Locks );

    // Get Semaphore lock
	Self->stdio_flockfile( (PTR) file );

//IExec->DebugPrintF( "close 4 - %ld\n", file->pf_Locks );

    // Flush any data left
    Self->stdio_fflush( (PTR) file );

//IExec->DebugPrintF( "close 5 - %ld\n", file->pf_Locks );

	// Release lock
	Self->Priv_FDUnlock( file );

//IExec->DebugPrintF( "close 6 - %ld\n", file->pf_Locks );

	// Remove and Free
	Self->Priv_FD_Free( file );

//IExec->DebugPrintF( "close 7\n" );

	// --
	retval = 0;


bailout:

	return(	retval );
}

// --

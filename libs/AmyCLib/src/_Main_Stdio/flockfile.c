
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

void AMYFUNC _generic_stdio_flockfile( struct AmyCLibIFace *Self, FILE *stream )
{
struct FileStruct *file;
struct libData *data;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_flockfile : Stream %p\n", stream ); );

	DOFUNCTIONLOG( LOG_FUNC_flockfile );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	// Used to offen internaly I disabled it here
//	  Self->Priv_CheckAbort();

	// --
	// Docs says I need too have a Lock count too
	// thats not how clib2 does it

	file = (PTR) stream;

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid StructID\n", __FILE__, __LINE__ );
		data = (PTR)( (U32) Self - Self->Data.NegativeSize );
		data->buf_PublicData->ra_ErrNo = EBADF;
	}
	else
	{
		IExec->ObtainSemaphore( & file->pf_Semaphore );
	}

//bailout:

	return;
}

// --


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
// File Descriptor

struct FileStruct * AMY_FUNC _generic__Priv_FD_Alloc( struct AmyCLibIFace *Self, U32 ID )
{
struct FileStruct *file;
struct libData *data;
S32 error;
S32 pos;

	pos = -1;

	error = TRUE;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Alloc : ID $%08lx\n", ID ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	IExec->ObtainSemaphore( & data->FD_Semaphore );

	// --

	file = Self->Priv_Mem_Alloc( sizeof( struct FileStruct ));

	if ( ! file )
	{
		IExec->DebugPrintF( "FD_Alloc() - Alloc Failed\n" );
		goto bailout;
	}

	if ( ! Self->Priv_FD_Init_Struct( file, ID ))
	{
		IExec->DebugPrintF( "FD_Alloc() - Init Struct Failed\n", ID );
		goto bailout;
	}

	pos = Self->Priv_FD_Array_Insert( file );

	if ( pos < 0 )
	{
		IExec->DebugPrintF( "FDAlloc() - Error inserting File Descriptor\n" );
		goto bailout;
	}

	file->pf_ArrayPos = pos;

	// --

	error = FALSE;

bailout:

	IExec->ReleaseSemaphore( & data->FD_Semaphore );

//	IExec->DebugPrintF( "FDAlloc() - File %p, Fildes %ld, Error %ld\n", file, pos, error );

	if (( error ) && ( file ))
	{
		Self->Priv_FD_Free( file );
		file = NULL;
	}

	return( file );
}

//-- 

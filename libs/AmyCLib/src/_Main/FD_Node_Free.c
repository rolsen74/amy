
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

// was AMYFUNC _generic__Priv_FDInit

S32 AMYFUNC _generic__Priv_FD_Free( struct AmyCLibIFace *Self, struct FileStruct *file )
{
//FILE *file;
struct libData *data;
S32 retval;

//	file = file_ptr;

	retval = FALSE;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Free : File %p, Fildes %ld\n", file, (file)?file->pf_ArrayPos:-1 ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	IExec->ObtainSemaphore( & data->FD_Semaphore );

	if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
	{
		IExec->DebugPrintF( "%s:%04ld: Invalid StructID\n", __FILE__, __LINE__ );
		goto bailout;
	}

	if ( file->pf_Locks > 0 )
	{
		DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Free : Still have lock %ld\n", file->pf_Locks ); );
		file->pf_Expunge = TRUE;
		goto bailout;
	}

	// Socket ID handles start at Zero
	if ((( file->pf_FileType == ID_SOCKET ) && ( file->pf_Handle.pf_Socket >= 0 ))
	||	(( file->pf_FileType != ID_SOCKET ) && ( file->pf_Handle.pf_Socket != 0 )))
	{
		if ( ! file->pf_Interface.pi_Close )
		{
			IExec->DebugPrintF( "pi_Close 1 : NULL Pointer\n" );
			goto bailout;
		}

		file->pf_Interface.pi_Close( Self, file );
	}

	Self->Priv_FD_Array_Remove( file->pf_ArrayPos );

	// --

//	if ( file->pf_TempDirLock )
//	{
//		//IExec->DebugPrintF( "FDFree 9\n" );
//		BPTR olddir = IDOS->CurrentDir( file->pf_TempDirLock );
//
//		if ( file->pf_TempFileName )
//		{
//			IDOS->Delete( file->pf_TempFileName );
//
//			Self->Priv_Mem_Free( file->pf_TempFileName );
//		}
//
//		IDOS->CurrentDir( olddir );
//
//		IDOS->UnLock( file->pf_TempDirLock );
//	}

	// --

//IExec->DebugPrintF( "FDFree 10 - %ld\n", file->pf_Locks );

	// Free Custom Buffer
	if ( file->pf_BufferCustom )
	{
		//IExec->DebugPrintF( "FDFree 11\n" );
		Self->stdio_setvbuf( (PTR) file, NULL, BUFFER_MODE_FULL, 0 );
	}

	// --

//IExec->DebugPrintF( "FDFree 12 - %ld\n", file->pf_Locks );

	Self->Priv_Mem_Free( file );

	// --

	retval = TRUE;

bailout:

	IExec->ReleaseSemaphore( & data->FD_Semaphore );

	return( retval );
}

// --

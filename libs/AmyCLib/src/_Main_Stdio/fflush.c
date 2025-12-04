
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

int AMY_FUNC _generic_stdio_fflush( struct AmyCLibIFace *Self, FILE *stream )
{
struct FileStruct *file;
struct libData *data;
int retval;
U32 cnt;

	// --

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fflush : Stream %p\n", stream ); );

	DOFUNCTIONLOG( LOG_FUNC_fflush );

	retval = EOF;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	Self->Priv_Check_Abort();

	// --

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	if ( stream )
	{
		// Flush single stream

		file = (PTR) stream;

		if (( ! file ) || ( file->pf_StructID != ID_PRIVFILE ))
		{
			retval = EOF;
			IExec->DebugPrintF( "%s:%04ld: Invalid StructID\n", __FILE__, __LINE__ );
			goto bailout;
		}

		Self->stdio_flockfile( stream );

		// Success
		retval = 0;

		// Flush any read bytes
		if ( file->pf_BufferReadBytes > 0 )
		{
			if ( ! Self->Priv_FB_Read_Drop_Buffer( file ))
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fflush : Priv_FB_Read_Drop_Buffer failed\n" ); );
				// Failure
				retval = EOF;
			}
		}

		// Flush any write bytes
		if ( file->pf_BufferWriteBytes > 0 )
		{
			if ( Self->Priv_FB_Write_Flush_Buffer( file ) == FALSE )
			{
				DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic_stdio_fflush : Priv_FB_Write_Flush_Buffer failed\n" ); );
				// Failure
				retval = EOF;
			}
		}

		Self->stdio_funlockfile( stream );
	}
	else
	{
		// Flush all streams

		// Default to Success
		retval = 0;

		IExec->ObtainSemaphore( & data->FD_Semaphore );

		for( cnt=0 ; cnt<data->FD_Array.Size ; cnt++ )
		{
			if ( data->FD_Array.Nodes[cnt].Node )
			{
				if ( Self->stdio_fflush( data->FD_Array.Nodes[cnt].Node ))
				{
					// Failure but we'll continue anyway
					retval = EOF;
				}
			}
		}

		IExec->ReleaseSemaphore( & data->FD_Semaphore );
	}

bailout:

	return(	retval );
}

// --

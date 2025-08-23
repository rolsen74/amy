
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

#define ArrayChunkSize	128

// --
// File Descriptor

S32 AMYFUNC _generic__Priv_FD_Array_Insert( struct AmyCLibPrivIFace *Self, PTR Node )
{
struct ArrayNode *newarray;
struct libData *data;
S32 retval;
U32 cnt;

	retval = -1UL;

	DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Array_Insert : Node %p\n", Node ); );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	IExec->ObtainSemaphore( & data->FD_Semaphore );

	// --

	if ( ! Node )
	{
		goto bailout;
	}

	// Do we need to expand the Node Array ?
	if ( data->FD_Array.Size == data->FD_Array.Used )
	{
		// Alloc new Array
		newarray = Self->Priv_Mem_Alloc( sizeof( struct ArrayNode ) * ( data->FD_Array.Size + ArrayChunkSize ) );

		if ( ! newarray )
		{
			DOFUNCTIONPRINTF( IExec->DebugPrintF( "_generic__Priv_FD_Array_Insert : Error allocating memory\n" ); );
			goto bailout;
		}

		// Swap to new Array

		U32 *s = (PTR) data->FD_Array.Nodes;
		U32 *d = (PTR) newarray;
		U32 l = ((( sizeof( struct ArrayNode ) * data->FD_Array.Used ) + 3 ) / 4 );

		for( cnt=0 ; cnt<l ; cnt++ )
		{
			*d++ = *s++ ;
		}

	//		  Self->string_memcpy( newarray, Header->Nodes, sizeof( struct ArrayNode ) * Header->Used );

		// -

		if ( data->FD_Array.Nodes )
		{
			Self->Priv_Mem_Free( data->FD_Array.Nodes );
		}

		data->FD_Array.Nodes = newarray;
		data->FD_Array.Size += ArrayChunkSize;

		// ---

		retval = data->FD_Array.Used;

		newarray[ data->FD_Array.Used ].Node = Node;

		data->FD_Array.Used++;
	}
	else
	{
		// Can't fail

		newarray = data->FD_Array.Nodes;

		for( cnt=0 ; cnt<data->FD_Array.Size ; cnt++ )
		{
			if ( ! newarray[ cnt ].Node )
			{
				break;
			}
		}

		retval = (S32) cnt;

		newarray[ cnt ].Node = Node;

		data->FD_Array.Used++;
	}

	// --

bailout:

	IExec->ReleaseSemaphore( & data->FD_Semaphore );

	return( retval );
}

// --

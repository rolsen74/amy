
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

static S32 myInit_Memory( struct AmyCLibPrivIFace *Self, struct libData *data UNUSED )
{
struct MemPoolHeader *ph;
S32 error;

	error = TRUE;

	// -- Alloc Default Global Memory Pool

	#define POOLSIZE	( 1024 * 512 )

	ph = Self->Priv_Mem_CreatePool( POOLSIZE );

	if ( ! ph )
	{
		IExec->DebugPrintF( "myInit_Memory : Error Setting up Memory Header\n" );
		goto bailout;
	}

	ph->ph_Global = TRUE;

	error = FALSE;

bailout:

	return( error );
}

// --

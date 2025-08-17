
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMYFUNC _Main_Expunge( struct AmyCLibIFace *Self )
{
struct libData *data;
U32 retval;

	IExec->DebugPrintF( "AmyCLib : _Main_Expunge\n" );

	retval = FALSE;

	if ( ! Self )
	{
		goto bailout;
	}

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// Freeing of Data has moved into _generic__Priv_Startup_Free
	Self->Priv_Startup_Free();

	Self->string_memset( data, 0xac, sizeof( struct libData ));

	IExec->FreeVec( (PTR)( (U32) Self - Self->Data.NegativeSize ));

	retval = TRUE;

bailout:

	return( retval );
}

// --


/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 _main_Expunge( struct AmyCLibIFace *Self )
{
struct libData *data;
U32 retval;

	IExec->DebugPrintF( "_main_Expunge\n" );

	retval = FALSE;

	if ( ! Self )
	{
		goto bailout;
	}

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// Freeing of Data has moved into Shutdown() in main/Startup.c

	Self->string_memset( data, 0xac, sizeof( struct libData ));

	IExec->FreeVec( (PTR)( (U32) Self - Self->Data.NegativeSize ));

	retval = TRUE;

bailout:

	return( retval );
}

// --

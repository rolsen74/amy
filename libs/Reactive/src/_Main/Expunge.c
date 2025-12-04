
/*
** SPDX-License-Identifier: BSD-2-Clause
** Copyright (c) 2011-2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

U32 AMY_FUNC _Main_Expunge( struct ReactivePrivIFace *Self )
{
struct libData *data;
U32 retval;

//	IExec->DebugPrintF( "Reactive : _Main_Expunge\n" );

	retval = FALSE;

	if ( ! Self )
	{
		goto bailout;
	}

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// Freeing of Data has moved into Shutdown() in main/Startup.c

	memset( data, 0xac, sizeof( struct libData ));

	IExec->FreeVec( (PTR)( (U32) Self - Self->Data.NegativeSize ));

	retval = TRUE;

bailout:

	return( retval );
}

// --

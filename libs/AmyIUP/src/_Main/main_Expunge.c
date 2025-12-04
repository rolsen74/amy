
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "inc/All.h"

// --

U32 AMY_FUNC _Main_Expunge( struct AmyIUPIFace *Self )
{
struct libData *data;
U32 retval;

	IExec->DebugPrintF( ":: AmyIUP :: _Main_Expunge ::\n" );

	retval = FALSE;

	if ( ! Self )
	{
		goto bailout;
	}

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --



	// --

	memset( data, 0xac, sizeof( struct libData ));

	IExec->FreeVec( (PTR)( (U32) Self - Self->Data.NegativeSize ));

	retval = TRUE;

bailout:

	return( retval );
}

// --

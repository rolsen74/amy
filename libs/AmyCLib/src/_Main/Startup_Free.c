
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#include "Startup_Cleanup_PublicData.c"

// --

void _main__Priv_Startup_Free( struct AmyCLibIFace *Self )
{
struct libData *data;

	IExec->DebugPrintF( "_main__Priv_Startup_Free\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	myCleanup_PublicData( Self, data );


	return;
}

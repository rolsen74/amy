
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#include "Startup_Init_Memory.c"
#include "Startup_Init_PublicData.c"

// --

S32 _main__Priv_Startup_Init( struct AmyCLibIFace *Self )
{
struct libData *data;
S32 retval;

	IExec->DebugPrintF( "_main__Priv_Startup_Init\n" );

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	retval = FALSE;

	// --

	IExec->DebugPrintF( "_main__Priv_Startup_Init : 2\n" );

	if ( myInit_Memory( Self, data ))
	{
		IExec->DebugPrintF( "mySetup_Memory failed\n" );
		goto bailout;
	}

	// --

	IExec->DebugPrintF( "_main__Priv_Startup_Init : 3\n" );

	if ( myInit_PublicData( Self, data ))
	{
		IExec->DebugPrintF( "mySetup_PublicData failed\n" );
		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

//	IExec->DebugPrintF( "_main__Priv_Startup_Init : 99\n" );

	return( retval );
}

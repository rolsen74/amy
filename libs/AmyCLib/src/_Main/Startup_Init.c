
/*
** SPDX-License-Identifier: BSD-3-Clause
** Copyright (c) 2025 Rene W. Olsen
** Target OS: AmigaOS
*/

// --

#include "src/All.h"

// --

#include "Startup_Init_Check_Args.c"
#include "Startup_Init_Signal.c"
#include "Startup_Init_Locale.c"
#include "Startup_Init_Memory.c"
#include "Startup_Init_PublicData.c"
#include "Startup_Init_Enable.c"

// --

S32 AMYFUNC _generic__Priv_Startup_Init( struct AmyCLibPrivIFace *Self, STR args, U32 mask )
{
struct _AmyCLibPublic *pd;
struct libData *data;
S32 retval;

	IExec->DebugPrintF( "_generic__Priv_Startup_Init : Mask $%08lx : Args '%s'\n", mask, (args)?args:"" );

	retval = FALSE;

	data = (PTR)( (U32) Self - Self->Data.NegativeSize );

	// --

	if ( myInit_Check_Args( Self, data, args ))
	{
		IExec->DebugPrintF( "_generic__Priv_Startup_Init : Arg Check failed\n" );
		goto bailout;		
	}

	// --

	if ( mask & EM_FILE )
	{
		// Can't open a File without allocating memory
		mask |= EM_MEMORY;
	}

	// --

	if ( mask & EM_STRING )
	{
		IExec->DebugPrintF( "_generic__Priv_Startup_Init : Enabling Strings\n" );

		data->Enable_Strings = TRUE;
		myInit_Enable( Self, data, EM_STRING );
	}

	// --

	if ( mask & EM_MEMORY )
	{
		IExec->DebugPrintF( "_generic__Priv_Startup_Init : Enabling Memory\n" );

		data->Enable_Memory = TRUE;
		myInit_Enable( Self, data, EM_MEMORY );

		if ( myInit_Memory( Self, data ))
		{
			IExec->DebugPrintF( "mySetup_Memory failed\n" );
			goto bailout;
		}
	}

	// --
	// Public Data

	pd = IExec->AllocVecTags( sizeof( struct _AmyCLibPublic ),
		AVT_Clear, 0,
		TAG_END
	);

	if ( ! pd )
	{
		IExec->DebugPrintF( "myInit_PublicData : Error allocating memory\n" );
		goto bailout;
	}

	data->buf_PublicData = pd;

	// --

	// Will be allocated when used
	// buf_gmtime;					// time / gmtime
	// buf_LocalTime;				// time / localtime

	// --

	if ( mask & EM_FILE )
	{
		IExec->DebugPrintF( "_generic__Priv_Startup_Init : Enabling File\n" );

		data->Enable_File = TRUE;
		myInit_Enable( Self, data, EM_FILE );
	}

	// --

	IExec->DebugPrintF( "_generic__Priv_Startup_Init : 3\n" );

	if ( myInit_PublicData( Self, data ))
	{
		IExec->DebugPrintF( "mySetup_PublicData failed\n" );
		goto bailout;
	}

	// --

	IExec->DebugPrintF( "_generic__Priv_Startup_Init : 4\n" );

	if ( myInit_Locale( Self, data ))
	{
		IExec->DebugPrintF( "mySetup_Locale failed\n" );
		goto bailout;
	}

	// --
	// todo : get buffer, if Mem is off

	IExec->DebugPrintF( "_generic__Priv_Startup_Init : 5\n" );

	if ( myInit_Signal( Self, data ))
	{
		IExec->DebugPrintF( "myInit_Signal failed\n" );
		goto bailout;
	}

	// --

	retval = TRUE;

bailout:

	IExec->DebugPrintF( "_generic__Priv_Startup_Init : 99 : Retval %ld\n", retval );

	return( retval );
}
